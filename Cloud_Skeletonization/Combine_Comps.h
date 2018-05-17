#pragma once

#include "Graph.h"

void Combine_Comps ( vector<Graph>const& conn_comp, Graph& g )
{
	for (auto c_c : conn_comp)
	{
		vector<Graph::vertex_descriptor> v;
		vector<pair<Graph::edge_descriptor, bool>> e;
        
        size_t num_vertices = boost::num_vertices( c_c );

		for (auto vi = boost::vertices( c_c ).first; vi != boost::vertices( c_c ).second; ++vi)
		{
			v.push_back( boost::add_vertex( g ) );
			g[v.back()].pt = c_c[*vi].pt;
		}
        
        for (int counter_1 = 0; counter_1 < num_vertices; ++counter_1)
        {
            for (int counter_2 = counter_1 + 1; counter_2 < num_vertices; ++ counter_2)
            {
                if (boost::edge( counter_1, counter_2, c_c ).second)
                {
                    e.push_back( boost::add_edge( v[counter_1], v[counter_2], g ) );
                    Point2d source = g[boost::source( e.back().first, g )].pt;
                    Point2d target = g[boost::target( e.back().first, g )].pt;
                    double length = norm( target - source );
                    boost::put( boost::edge_weight_t(), g, e.back().first, length );
                }

            }
        }
	}
}
