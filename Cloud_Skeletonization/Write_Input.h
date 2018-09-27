#pragma once

#include <fstream>
#include <iomanip>

#include "Run_Input.h"

void Write_Input ( string const& input_file, Run_Input const& run_input )
{
    ofstream ofs( input_file );
    
    ofs << "Pattern_Type  Pattern_Size_1  Pattern_Size_2  Regular  Graph_Dependent_Cloud_Size  Cloud_Size_Parameter  Noise_Type  Noise_Parameter  AlphaReeb  Mapper  Hopes  Repetitions" << endl;
    
    for (auto it_1 = run_input.noise_parameter_range.begin(); it_1 != run_input.noise_parameter_range.end(); ++it_1)
    {
        for (auto it_2 = run_input.wheel_range.begin(); it_2 != run_input.wheel_range.end(); ++it_2)
        {
            ofs << left << setw( 14 ) << "wheel";
            ofs << left << setw( 16 ) << *it_2;
            ofs << left << setw( 16 ) << 0;
            ofs << left << setw( 9 ) << run_input.regular;
            ofs << left << setw( 28 ) << run_input.graph_dependent_cloud_size;
            ofs << left << setw( 22 ) << run_input.cloud_size_parameter;
            ofs << left << setw( 12 ) << run_input.noise_type;
            ofs << left << setw( 17 ) << *it_1;
            ofs << left << setw( 11 ) << run_input.alphaReeb;
            ofs << left << setw( 8 ) << run_input.mapper;
            ofs << left << setw( 7 ) << run_input.hopes;
            ofs << left << setw( 13 ) << run_input.repetitions << endl;
        }
        
        for (auto it_2 = run_input.grid_cols_range.begin(); it_2 != run_input.grid_cols_range.end(); ++it_2)
        {
            for (auto it_3 = run_input.grid_rows_range.begin(); it_3 != run_input.grid_rows_range.end(); ++it_3)
            {
                if (*it_3 < *it_2) continue;
                
                ofs << left << setw( 14 ) << "grid";
                ofs << left << setw( 16 ) << *it_2;
                ofs << left << setw( 16 ) << *it_3;
                ofs << left << setw( 9 ) << run_input.regular;
                ofs << left << setw( 28 ) << run_input.graph_dependent_cloud_size;
                ofs << left << setw( 22 ) << run_input.cloud_size_parameter;
                ofs << left << setw( 12 ) << run_input.noise_type;
                ofs << left << setw( 17 ) << *it_1;
                ofs << left << setw( 11 ) << run_input.alphaReeb;
                ofs << left << setw( 8 ) << run_input.mapper;
                ofs << left << setw( 7 ) << run_input.hopes;
                ofs << left << setw( 13 ) << run_input.repetitions << endl;
            }
        }
        
        for (auto it_2 = run_input.squares_range.begin(); it_2 != run_input.squares_range.end(); ++it_2)
        {
            ofs << left << setw( 14 ) << "squares";
            ofs << left << setw( 16 ) << *it_2;
            ofs << left << setw( 16 ) << 0;
            ofs << left << setw( 9 ) << run_input.regular;
            ofs << left << setw( 28 ) << run_input.graph_dependent_cloud_size;
            ofs << left << setw( 22 ) << run_input.cloud_size_parameter;
            ofs << left << setw( 12 ) << run_input.noise_type;
            ofs << left << setw( 17 ) << *it_1;
            ofs << left << setw( 11 ) << run_input.alphaReeb;
            ofs << left << setw( 8 ) << run_input.mapper;
            ofs << left << setw( 7 ) << run_input.hopes;
            ofs << left << setw( 13 ) << run_input.repetitions << endl;
        }
    }
    
    ofs.close();
}
