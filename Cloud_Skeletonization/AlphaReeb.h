#pragma once

#include "AlphaReeb_Parameters.h"
#include "Cloud_To_Nbhd_Graph.h"
#include "Conn_Comps.h"
#include "Dijkstra_Filter.h"
#include "Single_Vertex_Case.h"
#include "Generate_Subclouds.h"
#include "Generate_Subgraphs.h"
#include "Group_Subgraphs.h"
#include "Generate_AlphaReeb_Graph.h"
#include "Combine_Comps.h"

void AlphaReeb ( vector<Data_Pt>const& cloud, AlphaReeb_Parameters const& parameters, Graph& alphaReeb )
{
    // Generating the neighbourhood graph for the cloud.
    
    Graph nbhd_graph;
    nbhd_graph.clear();
    
    Cloud_To_Nbhd_Graph( cloud, parameters.epsilon, nbhd_graph );
    
    // Splitting the neighbourhood graph into connected components.
    
    int num_comps;
    vector<Graph> conn_comp;
    vector<vector<Data_Pt>> conn_comp_cloud;
    conn_comp.clear();
    conn_comp_cloud.clear();
    
    Conn_Comps( nbhd_graph, cloud, num_comps, conn_comp_cloud, conn_comp );
    
    vector<Graph> alphaReeb_comp;
    alphaReeb_comp.clear();
    alphaReeb_comp.resize( num_comps );
    
    double min_comp_size = cloud.size() * parameters.min_comp_size_fraction;
    
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
            
            subgraph.clear();
            subcloud.clear();
            cluster.clear();
            cluster_vertex.clear();
            
            Generate_Subclouds( conn_comp_cloud[counter], filter_multimap, parameters.alpha, subcloud );
            
            Generate_Subgraphs( conn_comp[counter], subcloud, subgraph );
            
            Group_Subgraphs( subgraph, subcloud, cluster, cluster_vertex );
            
            Generate_AlphaReeb_Graph( cluster, cluster_vertex, alphaReeb_comp[counter] );
        }
    }
    
    // Combining the components into a single graph.
    
    Combine_Comps( alphaReeb_comp, alphaReeb );
}
