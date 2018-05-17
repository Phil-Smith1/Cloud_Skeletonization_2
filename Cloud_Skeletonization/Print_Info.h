#pragma once

#include <iostream>

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
