#pragma once

#include "Data_Pt.h"
#include "Filtration.h"

void Convert_Graph ( Graph_H const& initial_graph, Graph& converted_graph )
{
    vector<Graph::vertex_descriptor> v;
    vector<pair<Graph::edge_descriptor, bool>> e;
    
    int counter = 0;
    
    for (auto it = initial_graph.vertices.begin(); it != initial_graph.vertices.end(); ++it, ++counter)
    {
        v.push_back( boost::add_vertex( converted_graph ) );
        converted_graph[v[counter]].pt = Point2d( it->x(), it->y() );
    }
    
    int num_edges = 0;
    
    for (auto it = initial_graph.edges.begin(); it != initial_graph.edges.end(); ++it)
    {
        e.push_back( boost::add_edge( it->first, it->second, converted_graph ) );
        Point2d source = converted_graph[boost::source( e[num_edges].first, converted_graph )].pt;
        Point2d target = converted_graph[boost::target( e[num_edges].first, converted_graph )].pt;
        double length = norm( target - source );
        boost::put( boost::edge_weight_t(), converted_graph, e[num_edges].first, length );
        ++num_edges;
    }
}
