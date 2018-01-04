#pragma once

#include <boost/graph/connected_components.hpp>

#include "Data_Pt.h"

void Output_Graph ( vector<pair<vector<Data_Pt>, int>>& cluster, vector<Point2d>const& cluster_vertex, double min_comp_size, Graph& output_graph )
{
    size_t num_clusters = cluster.size();
    vector<Graph::vertex_descriptor> v;
    vector<pair<Graph::edge_descriptor, bool>> e;
    v.clear();
    e.clear();
    
    for (int counter = 0; counter < num_clusters; ++counter)
    {
        v.push_back( boost::add_vertex( output_graph ) );
        output_graph[v[counter]].pt = cluster_vertex[counter];
    }
    
    int num_edges = 0;
    
    for (int counter_1 = 0; counter_1 < num_clusters; ++counter_1)
    {
        for (int counter_2 = counter_1 + 1; counter_2 < num_clusters; ++counter_2)
        {
            if (cluster[counter_2].second != cluster[counter_1].second + 1 && cluster[counter_2].second != cluster[counter_1].second - 1) continue;
            
            else
            {
                size_t cluster_size_1 = cluster[counter_1].first.size();
                size_t cluster_size_2 = cluster[counter_2].first.size();
                int copy_num_edges = num_edges;
                
                for (int counter_3 = 0; counter_3 < cluster_size_1; ++counter_3)
                {
                    for (int counter_4 = 0; counter_4 < cluster_size_2; ++counter_4)
                    {
                        if (cluster[counter_1].first[counter_3].index == cluster[counter_2].first[counter_4].index)
                        {
                            e.push_back( boost::add_edge( v[counter_1], v[counter_2], output_graph ) );
                            Point2d source = output_graph[boost::source( e[num_edges].first, output_graph )].pt;
                            Point2d target = output_graph[boost::target( e[num_edges].first, output_graph )].pt;
                            double length = norm( target - source );
                            boost::put( boost::edge_weight_t(), output_graph, e[num_edges].first, length );
                            ++num_edges;
                            
                            break;
                        }
                    }
                    
                    if (copy_num_edges != num_edges) break;
                }
            }
        }
    }
    
    vector<int> comp(num_clusters);
    int num_comps = boost::connected_components( output_graph, &comp[0] ); // Assigns each vertex to its connected component.
    
    if (num_comps > 1)
    {
        vector<int> comp_size(num_comps, 0);
        vector<vector<int>> conn_comp_vertices(num_comps);
        
        for (int counter = 0; counter < num_clusters; ++counter)
        {
            comp_size[comp[counter]] += cluster[counter].first.size();
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
                    vector<Graph::vertex_descriptor> v_2;
                    v_2.clear();
                    
                    for (int counter_2 = 0; counter_2 < num_comp_vertices; ++counter_2)
                    {
                        v_2.push_back( boost::add_vertex( output_graph_2 ) );
                        output_graph_2[v_2[counter_2]].pt = output_graph[v[conn_comp_vertices[counter_1][counter_2]]].pt;
                    }
                    
                    num_edges = 0;
                    e.clear();
                    
                    for (int counter_2 = 0; counter_2 < num_comp_vertices; ++counter_2)
                    {
                        for (int counter_3 = counter_2 + 1; counter_3 < num_comp_vertices; ++counter_3)
                        {
                            if (boost::edge( conn_comp_vertices[counter_1][counter_2], conn_comp_vertices[counter_1][counter_3], output_graph ).second)
                            {
                                e.push_back( boost::add_edge( v_2[counter_2], v_2[counter_3], output_graph_2 ) );
                                Point2d source = output_graph_2[boost::source( e[num_edges].first, output_graph_2 )].pt;
                                Point2d target = output_graph_2[boost::target( e[num_edges].first, output_graph_2 )].pt;
                                double length = norm( target - source );
                                boost::put( boost::edge_weight_t(), output_graph_2, e[num_edges].first, length );
                                ++num_edges;
                            }
                        }
                    }
                    
                    output_graph = output_graph_2;
                }
            }
        }
    }
}
