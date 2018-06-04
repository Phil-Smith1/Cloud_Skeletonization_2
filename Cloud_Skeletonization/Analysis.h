#pragma once

#include <fstream>
#include <iomanip>

#include "Input.h"

void Analysis ( string const& result_directory, Input const& input, size_t mean_cloud_size, vector<pair<pair<double, double>, vector<bool>>>const& alphaReeb_results, vector<pair<pair<double, double>, vector<bool>>>const& mapper_results, vector<bool>const& hopes_results, double hopes_time )
{
    if (input.alphaReeb)
    {
        double best_success_rate = 0;
        double optimal_alpha = 0;
        double aR_time = 0;
        
        for (int counter = 0; counter < alphaReeb_results.size(); ++counter)
        {
            int successes = 0;
            size_t attempts = alphaReeb_results[counter].second.size();
            
            for (auto r : alphaReeb_results[counter].second)
            {
                if (r) ++successes;
            }
            
            double success_rate = 100 * successes / (double)attempts;
            
            if (success_rate >= best_success_rate)
            {
                best_success_rate = success_rate;
                optimal_alpha = alphaReeb_results[counter].first.first;
                aR_time = alphaReeb_results[counter].first.second;
            }
        }
        
        double time = aR_time / (double)input.repetitions;
        
        string result_file = result_directory + "AlphaReeb/AlphaReeb.txt";
        
        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 14 ) << input.pattern_type;
        ofs << left << setw( 16 ) << input.pattern_size_1;
        ofs << left << setw( 16 ) << input.pattern_size_2;
        ofs << left << setw( 22 ) << input.graph_dependent_cloud_size;
        ofs << left << setw( 18 ) << input.cloud_size_parameter;
        ofs << left << setw( 17 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 15 ) << optimal_alpha;
        ofs << left << setw( 15 ) << input.repetitions;
        ofs << left << setw( 17 ) << best_success_rate;
        ofs << left << setw( 8 ) << time << endl;
        
        ofs.close();
    }
    
    if (input.mapper)
    {
        double best_success_rate = 0;
        double optimal_num_intervals = 0;
        double m_time = 0;
        
        for (int counter = 0; counter < mapper_results.size(); ++counter)
        {
            int successes = 0;
            size_t attempts = mapper_results[counter].second.size();
            
            for (auto r : mapper_results[counter].second)
            {
                if (r) ++successes;
            }
            
            double success_rate = 100 * successes / (double)attempts;
            
            if (success_rate >= best_success_rate)
            {
                best_success_rate = success_rate;
                optimal_num_intervals = mapper_results[counter].first.first;
                m_time = mapper_results[counter].first.second;
            }
        }
        
        double time = m_time / (double)input.repetitions;
        
        string result_file = result_directory + "Mapper/Mapper.txt";
        
        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 14 ) << input.pattern_type;
        ofs << left << setw( 16 ) << input.pattern_size_1;
        ofs << left << setw( 16 ) << input.pattern_size_2;
        ofs << left << setw( 22 ) << input.graph_dependent_cloud_size;
        ofs << left << setw( 18 ) << input.cloud_size_parameter;
        ofs << left << setw( 17 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 21 ) << optimal_num_intervals;
        ofs << left << setw( 15 ) << input.repetitions;
        ofs << left << setw( 17 ) << best_success_rate;
        ofs << left << setw( 8 ) << time << endl;
        
        ofs.close();
    }
    
    if (input.hopes)
    {
        int successes = 0;
        size_t attempts = hopes_results.size();
        
        for (auto r : hopes_results)
        {
            if (r) ++successes;
        }
        
        double success_rate = 100 * successes / (double)attempts;
        
        double time = hopes_time / (double)input.repetitions;
        
        string result_file = result_directory + "Hopes/Hopes.txt";

        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 14 ) << input.pattern_type;
        ofs << left << setw( 16 ) << input.pattern_size_1;
        ofs << left << setw( 16 ) << input.pattern_size_2;
        ofs << left << setw( 22 ) << input.graph_dependent_cloud_size;
        ofs << left << setw( 18 ) << input.cloud_size_parameter;
        ofs << left << setw( 17 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 15 ) << attempts;
        ofs << left << setw( 17 ) << success_rate;
        ofs << left << setw( 8 ) << time << endl;
        
        ofs.close();
    }
}
