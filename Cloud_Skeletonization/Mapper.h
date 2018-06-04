#pragma once

#include "Filter_Function.h"
#include "Generate_Subclouds.h"
#include "Finding_MSTs.h"
#include "Clustering.h"
#include "Output_Graph.h"

void Mapper ( vector<Data_Pt>const& cloud, Mapper_Parameters const& parameters, Graph& mapper_graph )
{
    multimap<double, int> filter_multimap; // Key = filter value, value = index.
    
    Filter_Function( cloud, parameters, filter_multimap ); // Assigning the filter value to each point.
    
    vector<vector<Data_Pt>> subcloud;
    
    Generate_Subclouds( cloud, filter_multimap, parameters.num_intervals, parameters.overlap_ratio, subcloud ); // Assigning points to subclouds.
    
    vector<Graph> mst;
    
    Finding_MSTs( subcloud, mst ); // Creating the MST for each subcloud.
    
    vector<Cluster> cluster;
    
    Clustering( subcloud, mst, cluster );
    
    double min_comp_size = cloud.size() * parameters.mcsf;
    
    Output_Graph( cluster, min_comp_size, mapper_graph ); // Producing the output graph.
}
