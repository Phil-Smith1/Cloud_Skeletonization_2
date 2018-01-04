#pragma once

#include "Mapper_Parameters.h"
#include "Gauss_Density_Filter.h"
#include "Distance_Filter.h"
#include "Generate_Subclouds.h"
#include "MST.h"
#include "Clustering.h"
#include "Output_Graph.h"

void Mapper ( vector<Data_Pt>const& cloud, Mapper_Parameters const& parameters, Graph& mapper_graph )
{
    // Assigning the filter value to each point.
    
    multimap<double, int> filter_multimap; // Key = Gaussian density, value = index.
    filter_multimap.clear();
    
    if (parameters.filter_function == "Gauss_Density") Gauss_Density_Filter( cloud, parameters.sigma, filter_multimap );
    
    else if (parameters.filter_function == "Distance") Distance_Filter( cloud, filter_multimap );
    
    // Assigning points to subclouds.
    
    vector<vector<Data_Pt>> subcloud;
    subcloud.clear();
    subcloud.resize( parameters.num_intervals );
    
    Generate_Subclouds( cloud, filter_multimap, parameters.num_intervals, parameters.overlap_ratio, subcloud );
    
    // Creating the MST for each subcloud.
    
    vector<Graph> mst;
    mst.clear();
    mst.resize( parameters.num_intervals );
    
    MST( subcloud, mst );
    
    // Clustering.
    
    vector<pair<vector<Data_Pt>, int>> cluster;
    vector<Point2d> cluster_vertex;
    cluster.clear();
    cluster_vertex.clear();
    
    Clustering( subcloud, mst, cluster, cluster_vertex );
    
    // Producing the output graph.
    
    double min_comp_size = cloud.size() * parameters.min_comp_size_fraction;
    
    Output_Graph( cluster, cluster_vertex, min_comp_size, mapper_graph );
}
