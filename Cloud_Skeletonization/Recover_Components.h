#pragma once

#include "Data_Pt.h"

void Recover_Components ( Graph const& g, vector<Data_Pt>const& cloud, Graph& component )
{
    vector<Graph::vertex_descriptor> v;
    vector<pair<Graph::edge_descriptor, bool>> e;
    
    size_t cloud_size = cloud.size();
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        v.push_back( boost::add_vertex( component ) );
        component[v[counter]].pt = cloud[counter].pt;
    }
    
    for (int iter_1 = 0; iter_1 < cloud_size; ++iter_1)
    {
        for (int iter_2 = iter_1 + 1; iter_2 < cloud_size; ++iter_2)
        {
            if (boost::edge( cloud[iter_1].index, cloud[iter_2].index, g ).second)
            {
                e.push_back( boost::add_edge( iter_1, iter_2, component ) );
                Point2d source = component[boost::source( e.back().first, component )].pt;
                Point2d target = component[boost::target( e.back().first, component )].pt;
                double length = norm( target - source );
                boost::put( boost::edge_weight_t(), component, e.back().first, length );
            }
        }
    }
}
