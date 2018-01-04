#pragma once

#include <boost/graph/connected_components.hpp>

#include "Data_Pt.h"
#include "Geometric_Centre_Of_Cloud.h"

void Grouping ( Graph const& g, vector<Data_Pt>const& cloud, int subgraph_iter, vector<pair<vector<Data_Pt>, int>>& cluster, vector<Point2d>& cluster_vertex )
{
	size_t num_vertices = boost::num_vertices( g );

	if (num_vertices != 0)
	{
		vector<int> comp(num_vertices);
		int num_comps = boost::connected_components( g, &comp[0] );

		vector<Data_Pt> list;

		for (int comp_iter = 0; comp_iter < num_comps; ++comp_iter)
		{
			list.clear();

			for (int counter = 0; counter < num_vertices; ++counter)
			{
				if (comp[counter] == comp_iter) list.push_back( cloud[counter] );
			}

			cluster.push_back( make_pair( list, subgraph_iter ) );
			cluster_vertex.push_back( Geometric_Centre_Of_Cloud( list ) );
		}
	}
}

void Group_Subgraphs ( vector<Graph> const& subgraph, vector<vector<Data_Pt>> const& subcloud, vector<pair<vector<Data_Pt>, int>>& cluster, vector<Point2d>& cluster_vertex )
{
	size_t num_subgraphs = subgraph.size();

	for (int subgraph_iter = 0; subgraph_iter < num_subgraphs; ++subgraph_iter)
	{
		if (boost::num_vertices( subgraph[subgraph_iter]) == 0 ) continue;

		Grouping( subgraph[subgraph_iter], subcloud[subgraph_iter], subgraph_iter, cluster, cluster_vertex );
	}
}
