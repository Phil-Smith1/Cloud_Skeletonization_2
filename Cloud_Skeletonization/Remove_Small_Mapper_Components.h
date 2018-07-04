#pragma once

#include <boost/graph/connected_components.hpp>

#include "Graph.h"
#include "Cluster.h"

void Remove_Small_Mapper_Components ( Graph& g, vector<Cluster>const& cluster, double min_comp_size )
{
    size_t num_clusters = cluster.size();
    
    vector<int> comp( num_clusters );
    
    int num_comps = boost::connected_components( g, &comp[0] ); // Assigns each vertex to its connected component.
    
    if (num_comps > 1)
    {
        vector<int> comp_size( num_comps, 0 );
        vector<vector<int>> conn_comp_vertices( num_comps );
        
        for (int counter = 0; counter < num_clusters; ++counter)
        {
            comp_size[comp[counter]] += cluster[counter].cloud.size();
            conn_comp_vertices[comp[counter]].push_back( counter );
        }
        
        bool need_to_remove = false;
        
        for (int counter = 0; counter < num_comps; ++counter)
        {
            if (comp_size[counter] < min_comp_size) need_to_remove = true;
        }
        
        if (need_to_remove)
        {
            Graph g_2;
            
            for (int counter_1 = 0; counter_1 < num_comps; ++counter_1)
            {
                if (comp_size[counter_1] < min_comp_size) continue;
                
                else
                {
                    vector<Graph::vertex_descriptor> v;
                    vector<pair<Graph::edge_descriptor, bool>> e;
                    size_t num_vertices = conn_comp_vertices[counter_1].size();
                    
                    for (int counter_2 = 0; counter_2 < num_vertices; ++counter_2)
                    {
                        v.push_back( boost::add_vertex( g_2 ) );
                        g_2[v[counter_2]].pt = g[conn_comp_vertices[counter_1][counter_2]].pt;
                    }
                    
                    for (int counter_2 = 0; counter_2 < num_vertices; ++counter_2)
                    {
                        for (int counter_3 = counter_2 + 1; counter_3 < num_vertices; ++counter_3)
                        {
                            if (boost::edge( conn_comp_vertices[counter_1][counter_2], conn_comp_vertices[counter_1][counter_3], g ).second)
                            {
                                e.push_back( boost::add_edge( v[counter_2], v[counter_3], g_2 ) );
                                Point2d source = g_2[boost::source( e.back().first, g_2 )].pt;
                                Point2d target = g_2[boost::target( e.back().first, g_2 )].pt;
                                double length = norm( target - source );
                                boost::put( boost::edge_weight_t(), g_2, e.back().first, length );
                            }
                        }
                    }
                }
            }
            
            g = g_2;
        }
    }
}
