#pragma once

#include <string>
#include <iostream>

#include "Graph.h"

void Original_Graph ( string const& pattern_type, int pattern_size_1, int pattern_size_2, string const& diagonal_edges, Graph& g )
{
    if (pattern_type == "wheel")
    {
        for (int counter = 0; counter < pattern_size_1 + 1; ++counter)
        {
            boost::add_vertex( g );
        }
        
        for (int counter = 1; counter < pattern_size_1 + 1; ++counter)
        {
            boost::add_edge( 0, counter, g );
        }
        
        for (int counter = 1; counter < pattern_size_1; ++counter)
        {
            boost::add_edge( counter, counter + 1, g );
        }
        
        boost::add_edge( 1, pattern_size_1, g );
    }
    
    else if (pattern_type == "grid")
    {
        for (int counter = 0; counter < (pattern_size_1 + 1) * (pattern_size_2 + 1); ++counter)
        {
            boost::add_vertex( g );
        }
        
        for (int counter_1 = 0; counter_1 < pattern_size_1 + 1; ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < pattern_size_2; ++counter_2)
            {
                int vertex_1 = counter_2 + counter_1 * (pattern_size_2 + 1);
                int vertex_2 = counter_2 + 1 + counter_1 * (pattern_size_2 + 1);
                
                boost::add_edge( vertex_1, vertex_2, g );
            }
        }
        
        for (int counter_1 = 0; counter_1 < pattern_size_2 + 1; ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < pattern_size_1; ++counter_2)
            {
                int vertex_1 = counter_1 + counter_2 * (pattern_size_2 + 1);
                int vertex_2 = counter_1 + (counter_2 + 1) * (pattern_size_2 + 1);
                
                boost::add_edge( vertex_1, vertex_2, g );
            }
        }
    }
    
    else if (pattern_type == "squares")
    {
        for (int counter = 0; counter < pattern_size_1 * 4; ++counter)
        {
            boost::add_vertex( g );
        }
        
        for (int counter_1 = 0; counter_1 < pattern_size_1; ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < 3; ++counter_2)
            {
                int vertex_1 = counter_2 + counter_1 * 4;
                int vertex_2 = vertex_1 + 1;
                
                boost::add_edge( vertex_1, vertex_2, g );
            }
            
            boost::add_edge( 4 * counter_1, 4 * counter_1 + 3, g );
        }
        
        if (pattern_size_1 < 6)
        {
            for (int counter = 0; counter < 4; ++counter)
            {
                char c = diagonal_edges.at( counter );
                int i = c - '0';
                
                if (i == 1) boost::add_edge( counter, counter + 4, g );
            }
        }
        
        else
        {
            for (int counter = 0; counter < 8; ++counter)
            {
                char c = diagonal_edges.at( counter );
                int i = c - '0';
                
                if (i == 1) boost::add_edge( counter, counter + 4, g );
            }
        }
    }
}
