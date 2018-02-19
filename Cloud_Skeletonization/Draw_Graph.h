#pragma once

#include <opencv2/imgproc/imgproc.hpp>

#include "Scaling_Parameters.h"

#include "Filtration.h"

void Draw_Vertices ( Graph const& g, double scale, Point2d& shift, int radius_vertices, bool fill, Scalar const& colour, Mat& image )
{
	int thickness = 1;
	if (fill) thickness = -1;

	pair<vertex_iter, vertex_iter> VertexPair;

	for (VertexPair = boost::vertices( g ); VertexPair.first != VertexPair.second; ++VertexPair.first)
	{
		circle( image, Point(scale * g[*VertexPair.first].pt + shift), radius_vertices, colour, thickness );
	}
}

void Draw_Edges ( Graph const& g, double scale, Point2d& shift, int thickness_edge, Scalar const& colour, Mat& image )
{
	pair<Graph::edge_iterator, Graph::edge_iterator> edgeIteratorRange = boost::edges( g );

	for (Graph::edge_iterator edge_iter = edgeIteratorRange.first; edge_iter != edgeIteratorRange.second; ++edge_iter)
	{
		line( image, Point(scale * g[boost::source(*edge_iter, g)].pt + shift), Point(scale * g[boost::target(*edge_iter, g)].pt + shift), colour, thickness_edge );
	}
}

void Draw_Graph ( Graph const& g, int radius_vertices, bool fill, int thickness_edge, Scalar const& colour, Mat& image )
{
    Point image_sizes( image.cols, image.rows );
    double scale;
    Point2d shift;
    
    Scaling_Parameters( g, image_sizes, scale, shift );
    
	Draw_Vertices( g, scale, shift, radius_vertices, fill, colour, image );

	Draw_Edges( g, scale, shift, thickness_edge, colour, image );
}

void Draw_Graph ( Graph_H& g, Scalar const& colour_1, Scalar const& colour_2, Mat& image )
{
    Point image_sizes( image.cols, image.rows );
    double scale;
    Point2d shift;
    
    Scaling_Parameters( g, image_sizes, scale, shift );
    
    g.Draw( scale, shift, colour_1, colour_2, 1, image );
}
