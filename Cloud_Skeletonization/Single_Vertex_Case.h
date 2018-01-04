#pragma once

#include "Data_Pt.h"

void Single_Vertex_Case ( Data_Pt const& vertex, Graph& g )
{
	Graph::vertex_descriptor v = boost::add_vertex( g );
	g[v].pt = vertex.pt;
}
