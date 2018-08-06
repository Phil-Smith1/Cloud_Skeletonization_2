#pragma once

#include <fstream>
#include <iomanip>

#include "Input.h"
#include "Results.h"

void Analysis ( string const& result_directory, Input const& input, size_t mean_cloud_size, vector<Results>& alphaReeb_results, vector<Results>& mapper_results, Results& hopes_results )
{
    if (input.alphaReeb)
    {
        double best_Betti_success_rate = 0, optimal_parameter = 0;
        
        for (int counter = 0; counter < alphaReeb_results.size(); ++counter)
        {
            size_t attempts = alphaReeb_results[counter].Betti_success.size();
            int Betti_successes = 0, homeo_successes = 0;
            double gae = 0;
            
            for (auto r : alphaReeb_results[counter].Betti_success) if (r) ++Betti_successes;
            
            for (auto r : alphaReeb_results[counter].homeo_success) if (r) ++homeo_successes;
            
            for (auto r : alphaReeb_results[counter].geom_approx_error) gae += r;
            
            double Betti_success_rate = 100 * Betti_successes / (double)attempts;
            double homeo_success_rate = 100 * homeo_successes / (double)attempts;
            
            alphaReeb_results[counter].Betti_success_rate = Betti_success_rate;
            alphaReeb_results[counter].homeo_success_rate = homeo_success_rate;
            alphaReeb_results[counter].mgae = gae / (double)attempts;
            
            if (Betti_success_rate >= best_Betti_success_rate)
            {
                best_Betti_success_rate = Betti_success_rate;
                optimal_parameter = counter;
            }
        }
        
        alphaReeb_results[optimal_parameter].mean_time = alphaReeb_results[optimal_parameter].time / (double)input.repetitions;
        
        string result_file = result_directory + "AlphaReeb/AlphaReeb.txt";
        
        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 14 ) << input.pattern_type;
        ofs << left << setw( 16 ) << input.pattern_size_1;
        ofs << left << setw( 16 ) << input.pattern_size_2;
        ofs << left << setw( 6 ) << input.graph_dependent_cloud_size;
        ofs << left << setw( 10 ) << input.cloud_size_parameter;
        ofs << left << setw( 9 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 12 ) << input.repetitions;
        ofs << left << setw( 15 ) << alphaReeb_results[optimal_parameter].parameter;
        ofs << left << setw( 23 ) << alphaReeb_results[optimal_parameter].Betti_success_rate;
        ofs << left << setw( 23 ) << alphaReeb_results[optimal_parameter].homeo_success_rate;
        ofs << left << setw( 11 ) << alphaReeb_results[optimal_parameter].mgae;
        ofs << left << setw( 8 ) << alphaReeb_results[optimal_parameter].mean_time << endl;
        
        ofs.close();
    }
    
    if (input.mapper)
    {
        double best_Betti_success_rate = 0, optimal_parameter = 0;
        
        for (int counter = 0; counter < mapper_results.size(); ++counter)
        {
            size_t attempts = mapper_results[counter].Betti_success.size();
            int Betti_successes = 0, homeo_successes = 0;
            double gae = 0;
            
            for (auto r : mapper_results[counter].Betti_success) if (r) ++Betti_successes;
            
            for (auto r : mapper_results[counter].homeo_success) if (r) ++homeo_successes;
            
            for (auto r : mapper_results[counter].geom_approx_error) gae += r;
            
            double Betti_success_rate = 100 * Betti_successes / (double)attempts;
            double homeo_success_rate = 100 * homeo_successes / (double)attempts;
            
            mapper_results[counter].Betti_success_rate = Betti_success_rate;
            mapper_results[counter].homeo_success_rate = homeo_success_rate;
            mapper_results[counter].mgae = gae / (double)attempts;
            
            if (Betti_success_rate >= best_Betti_success_rate)
            {
                best_Betti_success_rate = Betti_success_rate;
                optimal_parameter = counter;
            }
        }
        
        mapper_results[optimal_parameter].mean_time = mapper_results[optimal_parameter].time / (double)input.repetitions;
        
        string result_file = result_directory + "Mapper/Mapper.txt";
        
        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 14 ) << input.pattern_type;
        ofs << left << setw( 16 ) << input.pattern_size_1;
        ofs << left << setw( 16 ) << input.pattern_size_2;
        ofs << left << setw( 6 ) << input.graph_dependent_cloud_size;
        ofs << left << setw( 10 ) << input.cloud_size_parameter;
        ofs << left << setw( 9 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 12 ) << input.repetitions;
        ofs << left << setw( 29 ) << mapper_results[optimal_parameter].parameter;
        ofs << left << setw( 23 ) << mapper_results[optimal_parameter].Betti_success_rate;
        ofs << left << setw( 23 ) << mapper_results[optimal_parameter].homeo_success_rate;
        ofs << left << setw( 11 ) << mapper_results[optimal_parameter].mgae;
        ofs << left << setw( 8 ) << mapper_results[optimal_parameter].mean_time << endl;
        
        ofs.close();
    }
    
    if (input.hopes)
    {
        size_t attempts = hopes_results.Betti_success.size();
        int Betti_successes = 0, homeo_successes = 0;
        double gae = 0;
        
        for (auto r : hopes_results.Betti_success) if (r) ++Betti_successes;
        
        for (auto r : hopes_results.homeo_success) if (r) ++homeo_successes;
        
        for (auto r : hopes_results.geom_approx_error) gae += r;
        
        double Betti_success_rate = 100 * Betti_successes / (double)attempts;
        double homeo_success_rate = 100 * homeo_successes / (double)attempts;
        
        hopes_results.Betti_success_rate = Betti_success_rate;
        hopes_results.homeo_success_rate = homeo_success_rate;
        hopes_results.mgae = gae / (double)attempts;
        
        hopes_results.mean_time = hopes_results.time / (double)input.repetitions;
        
        string result_file = result_directory + "Hopes/Hopes.txt";

        ofstream ofs( result_file, ios::app );
        
        ofs << left << setw( 14 ) << input.pattern_type;
        ofs << left << setw( 16 ) << input.pattern_size_1;
        ofs << left << setw( 16 ) << input.pattern_size_2;
        ofs << left << setw( 6 ) << input.graph_dependent_cloud_size;
        ofs << left << setw( 10 ) << input.cloud_size_parameter;
        ofs << left << setw( 9 ) << mean_cloud_size;
        ofs << left << setw( 12 ) << input.noise_type;
        ofs << left << setw( 13 ) << input.noise_parameter;
        ofs << left << setw( 12 ) << attempts;
        ofs << left << setw( 23 ) << hopes_results.Betti_success_rate;
        ofs << left << setw( 23 ) << hopes_results.homeo_success_rate;
        ofs << left << setw( 11 ) << hopes_results.mgae;
        ofs << left << setw( 8 ) << hopes_results.mean_time << endl;
        
        ofs.close();
    }
}
