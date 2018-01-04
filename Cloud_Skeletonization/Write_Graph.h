#pragma once

#include <fstream>

#include <boost/filesystem.hpp>

#include "Graph.h"
#include "Directory.h"
#include "File_Name.h"

void Write_Graph ( bool test, string const& graph_directory, Input const& input, string const& algorithm, int iteration, Graph const& g )
{
    string directory;
    Directory( test, graph_directory, input, algorithm, directory );
    
    if (!boost::filesystem::is_directory( directory ))
    {
        boost::filesystem::create_directories( directory );
    }
    
	string graph_file;
	File_Name( directory, "Graph", iteration, ".txt", graph_file );

	ofstream ofs( graph_file );

    ofs << "Pattern_Type Pattern_Size Graph_Dependent_Cloud_Size Cloud_Size_Parameter Noise_Type Noise_Parameter" << endl;
    
    ofs << input.pattern_type << " " << input.pattern_size << " " << input.graph_dependent_cloud_size << " " << input.cloud_size_parameter << " " << input.noise_type << " " << input.noise_parameter << endl;
    
	size_t num_vertices = boost::num_vertices( g );

    ofs << "Num_Vertices" << endl;
	ofs << num_vertices << endl;

	for (auto VertexPair = boost::vertices( g ); VertexPair.first != VertexPair.second; ++VertexPair.first)
	{
		ofs << g[*VertexPair.first].pt.x << " " << g[*VertexPair.first].pt.y << endl;
	}

	for (auto EdgePair = boost::edges( g ); EdgePair.first != EdgePair.second; ++EdgePair.first)
	{
		Graph::vertex_descriptor s, t;

		s = source( *EdgePair.first, g );
		t = target( *EdgePair.first, g );

		ofs << s << " " << t << endl;
	}
    
    ofs.close();
}
