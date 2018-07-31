#pragma once

#include "Graph.h"

void Simplify_Boost_Graph( Graph& g )
{
    bool simplify = true;
    size_t num_vertices = boost::num_vertices( g );
    vector<double> depth( num_vertices, 0 );
    
    while (simplify)
    {
        simplify = false;
        
        for (int v1 = 0; v1 < num_vertices; ++v1)
        {
            if (boost::degree( v1, g ) == 1)
            {
                simplify = true;
                
                int v2;
                auto edge = boost::out_edges( v1, g ).first;
                
                if (boost::source( *edge, g ) == v1) v2 = (int)boost::target( *edge, g );
                
                else v2 = (int)boost::source( *edge, g );
                
                double d = depth[v1] + get( boost::edge_weight_t(), g, *edge );
                
                if (d > depth[v2]) depth[v2] = d;
                
                boost::remove_edge( *edge, g );
                
                boost::remove_vertex( v1, g );
            }
        }
    }
}
