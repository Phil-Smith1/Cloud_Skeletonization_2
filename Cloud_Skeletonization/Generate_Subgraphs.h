#pragma once

#include "Data_Pt.h"

void Generate_Subgraphs ( Graph const& g, vector<vector<Data_Pt>>& subcloud, vector<Graph>& subgraph )
{
	size_t num_subclouds = subcloud.size();
    
    subgraph.resize( num_subclouds );

	for (int counter = 0; counter < num_subclouds; ++counter)
	{
		size_t cloud_size = subcloud[counter].size();

		vector<Graph::vertex_descriptor> v;
		vector<pair<Graph::edge_descriptor, bool>> e;
		v.clear();
		e.clear();

		for (int counter1 = 0; counter1 < cloud_size; ++counter1)
		{
			v.push_back( boost::add_vertex( subgraph[counter] ) );
			subgraph[counter][v[counter1]].pt = subcloud[counter][counter1].pt;
		}

		int num_edges = 0;

		for (int counter2 = 0; counter2 < cloud_size; ++counter2)
		{
			for (int counter3 = counter2 + 1; counter3 < cloud_size; ++counter3)
			{
				if (boost::edge( subcloud[counter][counter2].index, subcloud[counter][counter3].index, g ).second)
				{
					e.push_back( boost::add_edge( v[counter2], v[counter3], subgraph[counter] ) );
					Point2d source = subgraph[counter][boost::source( e[num_edges].first, subgraph[counter] )].pt;
					Point2d target = subgraph[counter][boost::target( e[num_edges].first, subgraph[counter] )].pt;
                    double length = norm( target - source );
                    boost::put( boost::edge_weight_t(), subgraph[counter], e[num_edges].first, length );
					++num_edges;
				}
			}
		}
	}
}
