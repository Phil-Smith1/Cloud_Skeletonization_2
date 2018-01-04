#pragma once

#include "Input.h"
#include "Num_To_String.h"

void Directory ( bool test, string const& initial_directory, Input const& input, string const& algorithm, string& directory )
{
    if (test)
    {
        directory = initial_directory + algorithm + "/Test";
    }
    
    else
    {
        if (input.graph_dependent_cloud_size)
        {
            directory = initial_directory + algorithm + "/Graph_Dependent_Cloud_Size/" + Num_To_String( input.cloud_size_parameter ) + "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/" + input.pattern_type + "/Size_" + Num_To_String( input.pattern_size );
        }

        else
        {
            directory = initial_directory + algorithm + "/Cloud_" + Num_To_String( input.cloud_size_parameter ) + "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/" + input.pattern_type + "/Size_" + Num_To_String( input.pattern_size );
        }

        if (algorithm == "AlphaReeb")
        {
            directory = directory + "/Alpha_" + Num_To_String( input.alpha );
        }

        if (algorithm == "Mapper")
        {
            if (input.graph_dependent_num_intervals)
            {
                directory = directory + "/Graph_Dependent_Num_Intervals/" + Num_To_String( input.num_intervals_param );
            }
            
            else directory = directory + "/" + Num_To_String( input.num_intervals ) + "_intervals";
        }
    }
}
