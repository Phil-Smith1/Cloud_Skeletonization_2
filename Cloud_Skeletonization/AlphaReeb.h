#pragma once
#include <iostream>
#include "Betti_Num.h"
#include "AlphaReeb_Parameters.h"
#include "Dijkstra_Filter.h"
#include "Single_Vertex_Case.h"
#include "Generate_Subclouds.h"
#include "Generate_Subgraphs.h"
#include "Group_Subgraphs.h"
#include "Generate_AlphaReeb_Graph.h"
#include "Extra_Step.h"
#include "Combine_Comps.h"

void AlphaReeb_Algorithm ( Graph const& input_graph, AlphaReeb_Parameters const& parameters, Graph& alphaReeb )
{
    // Splitting the input graph into connected components.
    
    int num_comps;
    vector<vector<Data_Pt>> conn_comp_cloud;
    vector<Graph> conn_comp;
    
    Conn_Comps( input_graph, num_comps, conn_comp_cloud, conn_comp );
    
    vector<Graph> alphaReeb_comp( num_comps );
    
    double min_comp_size = boost::num_vertices( input_graph ) * parameters.mcsf;
    
    for (int counter = 0; counter < num_comps; ++counter) // Looping over connected components.
    {
        if (conn_comp_cloud[counter].size() < min_comp_size) continue; // Disregards components with fewer vertices than the value of min_comp_size.
        
        // Assigning filter values to each point.
        
        multimap<double, int> filter_multimap; // Key = distance, value = index.
        
        Dijkstra_Filter( conn_comp[counter], filter_multimap );
        
        // Generating the alpha-Reeb graph.
        
        if (conn_comp_cloud[counter].size() == 1) Single_Vertex_Case( conn_comp_cloud[counter][0], alphaReeb_comp[counter] );
        
        else
        {
            vector<vector<Data_Pt>> subcloud;
            vector<Graph> subgraph;
            vector<pair<vector<Data_Pt>, int>> cluster;
            vector<Point2d> cluster_vertex;
            
            Generate_Subclouds( conn_comp_cloud[counter], filter_multimap, parameters.alpha, subcloud );
            
            Generate_Subgraphs( conn_comp[counter], subcloud, subgraph );
            
            Group_Subgraphs( subgraph, subcloud, cluster, cluster_vertex );
            
            Generate_AlphaReeb_Graph( cluster, cluster_vertex, alphaReeb_comp[counter] );
            
            Graph extra_step;
            
            Extra_Step( alphaReeb_comp[counter], parameters.alpha, extra_step );
            
            alphaReeb_comp[counter] = extra_step;
        }
    }
    
    // Combining the components into a single graph.
    
    Combine_Comps( alphaReeb_comp, alphaReeb );
}
