#pragma once

#include "Graph.h"

void Combine_Comps ( vector<Graph>const& conn_comp, Graph& g )
{
	for (auto graph : conn_comp)
	{
		vector<Graph::vertex_descriptor> v;
		vector<pair<Graph::edge_descriptor, bool>> e;
		v.clear();
		e.clear();

		pair<vertex_iter, vertex_iter> VertexPair_1, VertexPair_2;
		int counter = 0;

		for (VertexPair_1 = boost::vertices( graph ); VertexPair_1.first != VertexPair_1.second; ++VertexPair_1.first)
		{
			v.push_back( boost::add_vertex( g ) );
			g[v[counter]].pt = graph[*VertexPair_1.first].pt;
			++counter;
		}

		int num_edges = 0;
		int counter_1 = 0, counter_2;

		for (VertexPair_1 = boost::vertices( graph ); VertexPair_1.first != VertexPair_1.second; ++VertexPair_1.first)
		{
			VertexPair_2 = VertexPair_1;
			++VertexPair_2.first;
			counter_2 = counter_1;
			++counter_2;

			for (; VertexPair_2.first != VertexPair_2.second; ++VertexPair_2.first)
			{
				if (boost::edge( *VertexPair_1.first, *VertexPair_2.first, graph ).second)
				{
					e.push_back( boost::add_edge( v[counter_1], v[counter_2], g ) );
					Point2d source = g[boost::source( e[num_edges].first, g )].pt;
					Point2d target = g[boost::target( e[num_edges].first, g )].pt;
                    double length = norm( target - source );
                    boost::put( boost::edge_weight_t(), g, e[num_edges].first, length );
					++num_edges;
				}

				++counter_2;
			}

			++counter_1;
		}
	}
}
