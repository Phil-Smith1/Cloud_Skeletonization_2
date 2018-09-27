#pragma once

#include "Results.h"

void Initialise_Results ( vector<Results>& alphaReeb_results, vector<double>const& alpha_values, vector<Results>& mapper_results, vector<double>const& num_intervals_parameter, Results& hopes_results, double repetitions )
{
    for (int counter = 0; counter < alpha_values.size(); ++counter)
    {
        alphaReeb_results[counter].parameter = alpha_values[counter];
        alphaReeb_results[counter].time = 0;
        alphaReeb_results[counter].Betti_success.reserve( repetitions );
        alphaReeb_results[counter].homeo_success.reserve( repetitions );
        alphaReeb_results[counter].geom_approx_error.reserve( repetitions );
        alphaReeb_results[counter].rms.reserve( repetitions );
    }
    
    for (int counter = 0; counter < num_intervals_parameter.size(); ++counter)
    {
        mapper_results[counter].parameter = num_intervals_parameter[counter];
        mapper_results[counter].time = 0;
        mapper_results[counter].Betti_success.reserve( repetitions );
        mapper_results[counter].homeo_success.reserve( repetitions );
        mapper_results[counter].geom_approx_error.reserve( repetitions );
        mapper_results[counter].rms.reserve( repetitions );
    }
    
    hopes_results.time = 0;
    hopes_results.Betti_success.reserve( repetitions );
    hopes_results.homeo_success.reserve( repetitions );
    hopes_results.geom_approx_error.reserve( repetitions );
    hopes_results.rms.reserve( repetitions );
}
