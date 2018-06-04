#pragma once

#include <boost/graph/connected_components.hpp>

#include "Data_Pt.h"
#include "Connect_Clusters.h"

void Output_Graph ( vector<Cluster>const& cluster, double min_comp_size, Graph& output_graph )
{
    Connect_Clusters( cluster, output_graph );
    
    size_t num_clusters = cluster.size();
    
    vector<int> comp( num_clusters );
    
    int num_comps = boost::connected_components( output_graph, &comp[0] ); // Assigns each vertex to its connected component.
    
    if (num_comps > 1)
    {
        vector<int> comp_size( num_comps, 0 );
        vector<vector<int>> conn_comp_vertices( num_comps );
        
        for (int counter = 0; counter < num_clusters; ++counter)
        {
            comp_size[comp[counter]] += cluster[counter].cloud.size();
            conn_comp_vertices[comp[counter]].push_back( counter );
        }
        
        bool need_to_discard = false;
        
        for (int counter = 0; counter < num_comps; ++counter)
        {
            if (comp_size[counter] < min_comp_size) need_to_discard = true;
        }
        
        if (need_to_discard)
        {
            Graph output_graph_2;
            
            for (int counter_1 = 0; counter_1 < num_comps; ++counter_1)
            {
                if (comp_size[counter_1] < min_comp_size) continue;
        
                else
                {
                    size_t num_comp_vertices = conn_comp_vertices[counter_1].size();
                    vector<Graph::vertex_descriptor> v;
                    vector<pair<Graph::edge_descriptor, bool>> e;
                    
                    for (int counter_2 = 0; counter_2 < num_comp_vertices; ++counter_2)
                    {
                        v.push_back( boost::add_vertex( output_graph_2 ) );
                        output_graph_2[v[counter_2]].pt = output_graph[conn_comp_vertices[counter_1][counter_2]].pt;
                    }
                    
                    for (int counter_2 = 0; counter_2 < num_comp_vertices; ++counter_2)
                    {
                        for (int counter_3 = counter_2 + 1; counter_3 < num_comp_vertices; ++counter_3)
                        {
                            if (boost::edge( conn_comp_vertices[counter_1][counter_2], conn_comp_vertices[counter_1][counter_3], output_graph ).second)
                            {
                                e.push_back( boost::add_edge( v[counter_2], v[counter_3], output_graph_2 ) );
                                Point2d source = output_graph_2[boost::source( e.back().first, output_graph_2 )].pt;
                                Point2d target = output_graph_2[boost::target( e.back().first, output_graph_2 )].pt;
                                double length = norm( target - source );
                                boost::put( boost::edge_weight_t(), output_graph_2, e.back().first, length );
                            }
                        }
                    }
                    
                    output_graph = output_graph_2;
                }
            }
        }
    }
}
