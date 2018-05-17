#pragma once

#include "Input.h"
#include "Num_To_String.h"

void Directory ( string const& initial_directory, Input const& input, string const& algorithm, string& directory )
{
    if (input.graph_dependent_cloud_size)
    {
        if (input.pattern_type == "grid")
        {
            directory = initial_directory + algorithm + "/Graph_Dependent_Cloud_Size/" + Num_To_String( input.cloud_size_parameter ) + "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/" + input.pattern_type + "/" + Num_To_String( input.pattern_size_1 ) + "," + Num_To_String( input.pattern_size_2 );
        }
        
        else
        {
            directory = initial_directory + algorithm + "/Graph_Dependent_Cloud_Size/" + Num_To_String( input.cloud_size_parameter ) + "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/" + input.pattern_type + "/" + Num_To_String( input.pattern_size_1 );
        }
    }

    else
    {
        if (input.pattern_type == "grid")
        {
            directory = initial_directory + algorithm + "/Cloud_" + Num_To_String( input.cloud_size_parameter ) + "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/" + input.pattern_type + "/" + Num_To_String( input.pattern_size_1 ) + "," + Num_To_String( input.pattern_size_2 );
        }
        
        else
        {
            directory = initial_directory + algorithm + "/Cloud_" + Num_To_String( input.cloud_size_parameter ) + "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/" + input.pattern_type + "/" + Num_To_String( input.pattern_size_1 );
        }
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
        
        else directory = directory + "/" + Num_To_String( input.num_intervals ) + "_Intervals";
    }
}
