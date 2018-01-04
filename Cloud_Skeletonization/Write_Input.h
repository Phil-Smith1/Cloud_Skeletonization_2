#pragma once

#include <fstream>

#include "Custom.h"

void Write_Input ( string const& input_file, string const& alphaReeb_p_file, string const& alpha_values_file, string const& mapper_p_file, string const& num_intervals_parameter_file, Custom const& custom )
{
    ofstream ofs( input_file );
    
    ofs << "Pattern_Type Pattern_Size Graph_Dependent_Cloud_Size Cloud_Size_Parameter Noise_Type Noise_Parameter AlphaReeb Mapper Hopes Repetitions" << endl;
    
    for (auto it = custom.wheel_range.begin(); it != custom.wheel_range.end(); ++it)
    {
        ofs << "Wheel" << " " << *it << " " << custom.graph_dependent_cloud_size << " " << custom.cloud_size_parameter << " " << custom.noise_type << " " << custom.noise_parameter << " " << custom.alphaReeb << " " << custom.mapper << " " << custom.hopes << " " << custom.repetitions << endl;
    }
    
    for (auto it = custom.lattice_range.begin(); it != custom.lattice_range.end(); ++it)
    {
        ofs << "Lattice" << " " << *it << " " << custom.graph_dependent_cloud_size << " " << custom.cloud_size_parameter << " " << custom.noise_type << " " << custom.noise_parameter << " " << custom.alphaReeb << " " << custom.mapper << " " << custom.hopes << " " << custom.repetitions << endl;
    }
    
    for (auto it = custom.row_range.begin(); it != custom.row_range.end(); ++it)
    {
       ofs << "Row" << " " << *it << " " << custom.graph_dependent_cloud_size << " " << custom.cloud_size_parameter << " " << custom.noise_type << " " << custom.noise_parameter << " " << custom.alphaReeb << " " << custom.mapper << " " << custom.hopes << " " << custom.repetitions << endl;
    }
    
    for (auto it = custom.concentric_squares_range.begin(); it != custom.concentric_squares_range.end(); ++it)
    {
        ofs << "Concentric_Squares" << " " << *it << " " << custom.graph_dependent_cloud_size << " " << custom.cloud_size_parameter << " " << custom.noise_type << " " << custom.noise_parameter << " " << custom.alphaReeb << " " << custom.mapper << " " << custom.hopes << " " << custom.repetitions << endl;
    }
    
    ofs.close();
    
    size_t num_lines = custom.wheel_range.size() + custom.lattice_range.size() + custom.row_range.size() + custom.concentric_squares_range.size();
    
    if (custom.alphaReeb)
    {
        ofstream ofs_1( alphaReeb_p_file );
        
        ofs_1 << "Epsilon Min_Comp_Size_Fraction" << endl;
        
        for (int counter = 0; counter < num_lines; ++counter)
        {
            ofs_1 << custom.epsilon << " " << custom.min_comp_size_fraction << endl;
        }
        
        ofs_1.close();
        
        ofstream ofs_2( alpha_values_file );
        
        for (auto it = custom.alpha_values.begin(); it != custom.alpha_values.end(); ++it)
        {
            ofs_2 << *it << endl;
        }
        
        ofs_2.close();
    }
    
    if (custom.mapper)
    {
        ofstream ofs_1( mapper_p_file );
        
        ofs_1 << "Graph_Dependent_Num_Intervals Overlap_Ratio Filter_Function Sigma Min_Comp_Size_Fraction" << endl;
        
        for (int counter = 0; counter < num_lines; ++counter)
        {
            ofs_1 << custom.graph_dependent_num_intervals << " " << custom.overlap_ratio << " " << custom.filter_function << " " << custom.sigma << " " << custom.min_comp_size_fraction << endl;
        }
        
        ofs_1.close();
        
        ofstream ofs_2( num_intervals_parameter_file );
        
        for (auto it = custom.num_intervals_parameter.begin(); it != custom.num_intervals_parameter.end(); ++it)
        {
            ofs_2 << *it << endl;
        }
        
        ofs_2.close();
    }
}
