#pragma once

#include <boost/graph/connected_components.hpp>

#include "Data_Pt.h"

void Recover_Comps ( Graph const& g, vector<Data_Pt>const& cloud, Graph& component )
{
	size_t cloud_size = cloud.size();
	vector<Graph::vertex_descriptor> v;
	vector<pair<Graph::edge_descriptor, bool>> e;
	v.clear();
	e.clear();

	for (int counter = 0; counter < cloud_size; ++counter)
	{
		v.push_back( boost::add_vertex( component ) );
		component[v[counter]].pt = cloud[counter].pt;
	}

	int num_edges = 0;

	for (int iter_1 = 0; iter_1 < cloud_size; ++iter_1)
	{
		for (int iter_2 = iter_1 + 1; iter_2 < cloud_size; ++iter_2)
		{
			if (boost::edge( cloud[iter_1].index, cloud[iter_2].index, g ).second)
			{
				e.push_back( boost::add_edge( iter_1, iter_2, component ) );
				Point2d source = component[boost::source( e[num_edges].first, component )].pt;
				Point2d target = component[boost::target( e[num_edges].first, component )].pt;
                double length = norm( target - source );
                boost::put( boost::edge_weight_t(), component, e[num_edges].first, length );
				++num_edges;
			}
		}
	}
}

void Conn_Comps ( Graph const& g, vector<Data_Pt>const& cloud, int& num_comps, vector<vector<Data_Pt>>& conn_comp_cloud, vector<Graph>& conn_comp )
{
	size_t num_vertices = boost::num_vertices( g );

	vector<int> comp(num_vertices);
    
	num_comps = boost::connected_components( g, &comp[0] ); // Assigns each vertex to its connected component.
	
    conn_comp_cloud.resize( num_comps );
	conn_comp.resize( num_comps );

	for (int counter = 0; counter < num_vertices; ++counter)
	{
		conn_comp_cloud[comp[counter]].push_back( cloud[counter] );
	}

	for (int counter = 0; counter < num_comps; ++counter)
	{
		Recover_Comps( g, conn_comp_cloud[counter], conn_comp[counter] ); // Assigns an edge between two vertices in each component if an edge exists in the input graph.
	}

	for (int iter_1 = 0; iter_1 < num_comps; ++iter_1)
	{
		size_t cloud_size = conn_comp_cloud[iter_1].size();

		for (int iter_2 = 0; iter_2 < cloud_size; ++iter_2)
		{
			conn_comp_cloud[iter_1][iter_2].index = iter_2;
		}
	}
}
