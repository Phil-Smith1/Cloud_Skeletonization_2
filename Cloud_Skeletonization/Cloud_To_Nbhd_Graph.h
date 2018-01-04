#pragma once

#include "Data_Pt.h"

void Cloud_To_Nbhd_Graph ( vector<Data_Pt>const& cloud, double epsilon, Graph& g )
{
	size_t cloud_size = cloud.size();

	vector<Graph::vertex_descriptor> v;
	vector<pair<Graph::edge_descriptor, bool>> e;
	v.clear();
	e.clear();

	for (int counter = 0; counter < cloud_size; ++counter)
	{
		v.push_back( boost::add_vertex( g ) );
		g[v[counter]].pt = cloud[counter].pt;
	}

	// Adding edges between vertices a distance less than epsilon apart.

	int num_edges = 0;
	double dist;

	for (int iter_1 = 0; iter_1 < cloud_size; ++iter_1)
	{
		for (int iter_2 = iter_1 + 1; iter_2 < cloud_size; ++iter_2)
		{
			dist = norm( cloud[iter_2].pt - cloud[iter_1].pt );

			if (dist < epsilon)
			{
				e.push_back( boost::add_edge( iter_1, iter_2, g ) );
                boost::put( boost::edge_weight_t(), g, e[num_edges].first, dist );
				++num_edges;
			}
		}
	}
}
