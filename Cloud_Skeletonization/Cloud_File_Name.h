#pragma once

#include "Input.h"
#include "Num_To_String.h"

void Cloud_File_Name ( bool test, string const& directory, Input const& input, int iteration, string& file_name )
{
    if (test)
    {
        file_name = directory + "Test/Cloud_" + Num_To_String( iteration + 1 ) + ".txt";
    }
    
    else if (input.graph_dependent_cloud_size)
    {
        file_name = directory + "Graph_Dependent_Cloud_Size/" + Num_To_String( input.cloud_size_parameter ) +
        "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/" + input.pattern_type + "/Size_" + Num_To_String( input.pattern_size ) + "/Cloud_" + Num_To_String( iteration + 1 ) + ".txt";
    }
    
    else
    {
        file_name = directory + "/Cloud_" + Num_To_String( input.cloud_size_parameter ) + "/" + input.noise_type + "/" + Num_To_String( input.noise_parameter ) + "/" + input.pattern_type + "/Size_" + Num_To_String( input.pattern_size ) + "/Cloud_" + Num_To_String( iteration + 1 ) + ".txt";
    }
}
