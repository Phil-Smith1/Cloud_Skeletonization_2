#pragma once

#include "AlphaReeb_Parameters.h"
#include "Split_Into_Conn_Comps.h"
#include "Dijkstra.h"
#include "Generate_Subclouds.h"
#include "Generate_Subgraphs.h"
#include "Group_Subgraphs.h"
#include "Connect_Clusters.h"
#include "Generate_AlphaReeb_Graph.h"
#include "Combine_Comps.h"

void AlphaReeb_Algorithm ( Graph const& input_graph, AlphaReeb_Parameters const& parameters, Graph& alphaReeb_graph )
{
    int num_comps;
    vector<vector<Data_Pt>> conn_comp_cloud;
    vector<Graph> conn_comp;
    
    Split_Into_Conn_Comps( input_graph, num_comps, conn_comp_cloud, conn_comp ); // Splitting the input graph into connected components.
    
    vector<Graph> alphaReeb_comp( num_comps );
    
    double min_comp_size = boost::num_vertices( input_graph ) * parameters.mcsf;
    
    for (int counter = 0; counter < num_comps; ++counter) // Looping over connected components.
    {
        if (conn_comp_cloud[counter].size() < min_comp_size) continue; // Disregards components with fewer vertices than the value of min_comp_size.
        
        if (conn_comp_cloud[counter].size() == 1)
        {
            Graph::vertex_descriptor v = boost::add_vertex( alphaReeb_comp[counter] );
            alphaReeb_comp[counter][v].pt = conn_comp_cloud[counter][0].pt;
            continue;
        }
        
        Graph intermediate_graph;
        vector<vector<Data_Pt>> subcloud;
        vector<Graph> subgraph;
        vector<Cluster> cluster;
        multimap<double, int> dijkstra_multimap; // Key = distance, value = index.
        
        Dijkstra( conn_comp[counter], dijkstra_multimap ); // Assigning filter values to each point.
        
        Generate_Subclouds( conn_comp_cloud[counter], dijkstra_multimap, parameters.alpha, subcloud );
        
        Generate_Subgraphs( conn_comp[counter], subcloud, subgraph );
        
        Group_Subgraphs( subgraph, subcloud, cluster );
        
        Connect_Clusters( cluster, intermediate_graph );
        
        Graph g;
        
        Graph::vertex_descriptor v1 = boost::add_vertex( g );
        g[v1].pt = Point2d(0,0);
        g[v1].interval = 0;
        g[v1].index = 0;
        Graph::vertex_descriptor v2 = boost::add_vertex( g );
        g[v2].pt = Point2d(1,1);
        g[v2].interval = 1;
        g[v2].index = 1;
        Graph::vertex_descriptor v3 = boost::add_vertex( g );
        g[v3].pt = Point2d(-1,1);
        g[v3].interval = 1;
        g[v3].index = 2;
        Graph::vertex_descriptor v4 = boost::add_vertex( g );
        g[v4].pt = Point2d(1,2);
        g[v4].interval = 2;
        g[v4].index = 3;
        Graph::vertex_descriptor v5 = boost::add_vertex( g );
        g[v5].pt = Point2d(-1,2);
        g[v5].interval = 2;
        g[v5].index = 4;
        Graph::vertex_descriptor v6 = boost::add_vertex( g );
        g[v6].pt = Point2d(0,3);
        g[v6].interval = 3;
        g[v6].index = 5;
        Graph::vertex_descriptor v7 = boost::add_vertex( g );
        g[v7].pt = Point2d(0,4);
        g[v7].interval = 4;
        g[v7].index = 6;
        
        boost::add_edge( 0 , 1, g);
        boost::add_edge( 0 , 2, g);
        boost::add_edge( 1 , 3, g);
        boost::add_edge( 2 , 4, g);
        boost::add_edge( 3 , 5, g);
        boost::add_edge( 4 , 5, g);
        boost::add_edge( 5 , 6, g);
        
        //intermediate_graph = g;
        
        Generate_AlphaReeb_Graph( intermediate_graph, parameters.alpha, alphaReeb_comp[counter] );
        alphaReeb_comp[counter] = intermediate_graph;
    }
    
    if (num_comps > 1) Combine_Comps( alphaReeb_comp, alphaReeb_graph ); // Combining the components into a single graph.
    
    else alphaReeb_graph = alphaReeb_comp[0];
}
