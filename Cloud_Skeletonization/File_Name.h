#pragma once

#include "Num_To_String.h"

void File_Name ( string const& directory, string const& item, int iteration, string const& ext, string& file_name )
{
    file_name = directory + "/" + item + "_" + Num_To_String( iteration + 1 ) + ext;
}
