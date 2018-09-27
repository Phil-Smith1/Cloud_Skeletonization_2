#pragma once

#include "Convert_Cloud.h"
#include "Hopes.h"

void Find_Epsilon ( vector<P2>const& cloud, double& epsilon )
{
    Graph_H hopes_graph;
    double max_birth = 0, min_death = 1e10;
    
    Hopes( cloud, hopes_graph, max_birth, min_death );
    
    epsilon = 2 * max_birth + 0.0001;
}
