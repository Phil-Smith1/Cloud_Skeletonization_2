#pragma once

#include <iostream>

void Print_Experiment_Summary ( clock_t start_experiment, int experiment_iter, Input input )
{
    int num_algorithms = 0;
    if (input.alphaReeb) num_algorithms += input.alpha_values.size();
    if (input.mapper) ++num_algorithms;
    if (input.hopes) ++num_algorithms;
    
    clock_t end_experiment = clock();
    double elapsed_time = (end_experiment - start_experiment) * 1000 / (double)(CLOCKS_PER_SEC);
    double mean_iter_time = elapsed_time / (double)(input.repetitions * num_algorithms);
    
    cout << "Experiment "  << experiment_iter << ":" << endl;
    cout << "  Experiment duration: " << elapsed_time << " ms." << endl;
    cout << "  Mean iteration time: " << mean_iter_time << " ms." << endl << endl;
}

void Print_Summary ( clock_t start_time, int experiment_iter )
{
    clock_t end_time = clock();
    double elapsed_time = (end_time - start_time) * 1000 / (double)(CLOCKS_PER_SEC);
    double mean_experiment_time = elapsed_time / (double)experiment_iter;
    
    cout << "Summary:" << endl;
    cout << "  Code duration: " << elapsed_time << " ms." << endl;
    cout << "  Number of experiments: " << experiment_iter << "." << endl;
    cout << "  Mean experiment time: " << mean_experiment_time << " ms." << endl << endl;
}
