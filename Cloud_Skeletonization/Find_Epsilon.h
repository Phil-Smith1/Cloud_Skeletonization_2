#pragma once

#include "Convert_Cloud.h"
#include "Hopes.h"

void Find_Epsilon ( vector<Data_Pt>const& cloud, double& epsilon )
{
    vector<P2> converted_cloud;
    
    Convert_Cloud_1( cloud, converted_cloud ); // Converting points of type Data_Pt to type P2.
    
    Graph_H hopes_graph;
    double noise = 0;
    
    Hopes( converted_cloud, hopes_graph, noise ); // Generating the Hopes graph.
    
    epsilon = noise;
}
