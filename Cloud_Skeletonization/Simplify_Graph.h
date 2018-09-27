#pragma once

#include <boost/graph/connected_components.hpp>

#include "Graph.h"
#include "Geometric_Centre_Of_Cloud.h"

void Simplify_Graph ( double threshold, Graph& g )
{
    vector<pair<int, int>> removed_edges;
    
    bool remove = true;
    int not_removed = 0;
    
    while (remove)
    {
        remove = false;
        
        auto ei = boost::edges( g ).first;
        advance( ei, not_removed );
        
        for (; ei != boost::edges( g ).second; ++ei)
        {
            if (get( boost::edge_weight_t(), g, *ei ) > threshold)
            {
                int source = (int)boost::source( *ei, g ), target = (int)boost::target( *ei, g );
                
                removed_edges.push_back( pair<int, int>( source, target ) );
                
                boost::remove_edge( *ei, g );
                
                remove = true;
                
                break;
            }
            
            else ++not_removed;
        }
    }
    
    size_t num_vertices = boost::num_vertices( g );
    
    vector<int> comp( num_vertices );
    
    int num_comps = boost::connected_components( g, &comp[0] );
    
    vector<vector<Data_Pt>> conn_comp_cloud( num_comps );
    
    for (int counter = 0; counter < num_vertices; ++counter)
    {
        conn_comp_cloud[comp[counter]].push_back( Data_Pt( g[counter].pt ) );
    }
    
    Graph simplified_graph;
    
    for (int counter = 0; counter < num_comps; ++counter)
    {
        boost::add_vertex( simplified_graph );
        simplified_graph[counter].pt = Geometric_Centre_Of_Cloud( conn_comp_cloud[counter] );
    }
    
    vector<pair<Graph::edge_descriptor, bool>> e;
    
    for (auto re : removed_edges)
    {
        e.push_back( boost::add_edge( comp[re.first], comp[re.second], simplified_graph ) );
        Point2d source = simplified_graph[boost::source( e.back().first, simplified_graph )].pt;
        Point2d target = simplified_graph[boost::target( e.back().first, simplified_graph )].pt;
        double length = norm( target - source );
        boost::put( boost::edge_weight_t(), simplified_graph, e.back().first, length );
    }
    
    g = simplified_graph;
}
