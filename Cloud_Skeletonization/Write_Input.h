#pragma once

#include <fstream>

#include "Run_Input.h"

void Write_Input ( string const& input_file, Run_Input const& run_input )
{
    ofstream ofs( input_file );
    
    ofs << "Pattern_Type Pattern_Size Graph_Dependent_Cloud_Size Cloud_Size_Parameter Noise_Type Noise_Parameter AlphaReeb Mapper Hopes Repetitions" << endl;
    
    for (auto it_1 = run_input.noise_parameter_range.begin(); it_1 != run_input.noise_parameter_range.end(); ++it_1)
    {
        for (auto it_2 = run_input.wheel_range.begin(); it_2 != run_input.wheel_range.end(); ++it_2)
        {
            ofs << "wheel " << *it_2 << " " << 0 << " " << run_input.graph_dependent_cloud_size << " " << run_input.cloud_size_parameter << " " << run_input.noise_type << " " << *it_1 << " " << run_input.alphaReeb << " " << run_input.mapper << " " << run_input.hopes << " " << run_input.repetitions << endl;
        }
        
        for (auto it_2 = run_input.grid_cols_range.begin(); it_2 != run_input.grid_cols_range.end(); ++it_2)
        {
            for (auto it_3 = run_input.grid_rows_range.begin(); it_3 != run_input.grid_rows_range.end(); ++it_3)
            {
                if (*it_3 < *it_2) continue;
                
                ofs << "grid " << *it_2 << " " << *it_3 << " " << run_input.graph_dependent_cloud_size << " " << run_input.cloud_size_parameter << " " << run_input.noise_type << " " << *it_1 << " " << run_input.alphaReeb << " " << run_input.mapper << " " << run_input.hopes << " " << run_input.repetitions << endl;
            }
        }
        
        for (auto it_2 = run_input.squares_range.begin(); it_2 != run_input.squares_range.end(); ++it_2)
        {
            ofs << "squares " << *it_2 << " " << 0 << " " << run_input.graph_dependent_cloud_size << " " << run_input.cloud_size_parameter << " " << run_input.noise_type << " " << *it_1 << " " << run_input.alphaReeb << " " << run_input.mapper << " " << run_input.hopes << " " << run_input.repetitions << endl;
        }
    }
    
    ofs.close();
}
