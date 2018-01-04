#pragma once

#include <boost/graph/kruskal_min_spanning_tree.hpp>

#include "Complete_Graph.h"

void MST_Of_Graph ( vector<Data_Pt>const& cloud, Graph& g, Graph& mst )
{
    vector<boost::graph_traits<Graph>::edge_descriptor> spanning_tree;
    spanning_tree.clear();
    
    boost::kruskal_minimum_spanning_tree( g, back_inserter( spanning_tree ) );
    
    vector<Graph::vertex_descriptor> v;
    vector<pair<Graph::edge_descriptor, bool>> e;
    size_t cloud_size = cloud.size();
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        v.push_back( boost::add_vertex( mst ) );
        mst[v[counter]].pt = cloud[counter].pt;
    }
    
    int num_edges = 0;
    
    for (auto it = spanning_tree.begin(); it != spanning_tree.end(); ++it)
    {
        e.push_back( boost::add_edge( source( *it, g ), target( *it, g ), mst ) );
        Point2d source = g[boost::source( e[num_edges].first, g )].pt;
        Point2d target = g[boost::target( e[num_edges].first, g )].pt;
        double length = norm( target - source );
        boost::put( boost::edge_weight_t(), mst, e[num_edges].first, length );
        ++num_edges;
    }
}

void MST ( vector<vector<Data_Pt>>const& subcloud, vector<Graph>& mst )
{
    size_t num_intervals = subcloud.size();
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        Graph g;
        g.clear();
        
        Complete_Graph( subcloud[counter], g );
        
        MST_Of_Graph( subcloud[counter], g, mst[counter] );
    }
}
