#pragma once

#include "Data_Pt.h"

void Generate_AlphaReeb_Graph ( vector<pair<vector<Data_Pt>, int>>const& cluster, vector<Point2d>const& cluster_vertex, Graph& alpha_Reeb )
{
	size_t num_clusters = cluster.size();

	vector<Graph::vertex_descriptor> v;
	vector<pair<Graph::edge_descriptor, bool>> e;
	v.clear();
	e.clear();

	for (int counter = 0; counter < num_clusters; ++counter)
	{
		v.push_back( boost::add_vertex( alpha_Reeb ) );
		alpha_Reeb[v[counter]].pt = cluster_vertex[counter];
	}

	int num_edges = 0;

	for (int counter = 0; counter < num_clusters; ++counter)
	{
		for (int counter1 = counter + 1; counter1 < num_clusters; ++counter1)
		{
			if (cluster[counter1].second != cluster[counter].second + 1 && cluster[counter1].second != cluster[counter].second - 1) continue;

			else
			{
				size_t cluster_size1 = cluster[counter].first.size();
				size_t cluster_size2 = cluster[counter1].first.size();
				int copy_num_edges = num_edges;

				for (int counter2 = 0; counter2 < cluster_size1; ++counter2)
				{
					for (int counter3 = 0; counter3 < cluster_size2; ++counter3)
					{
						if (cluster[counter].first[counter2].index == cluster[counter1].first[counter3].index)
						{
							e.push_back( boost::add_edge( v[counter], v[counter1], alpha_Reeb ) );
							Point2d source = alpha_Reeb[boost::source( e[num_edges].first, alpha_Reeb )].pt;
							Point2d target = alpha_Reeb[boost::target( e[num_edges].first, alpha_Reeb )].pt;
                            double length = norm( target - source );
                            boost::put( boost::edge_weight_t(), alpha_Reeb, e[num_edges].first, length );
							++num_edges;

							break;
						}
					}

					if (copy_num_edges != num_edges) break;
				}
			}
		}		
	}
}
