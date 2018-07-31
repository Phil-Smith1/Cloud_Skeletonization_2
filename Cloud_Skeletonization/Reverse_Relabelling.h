#pragma once

#include <vector>

void Reverse_Relabelling ( vector<int>& relabelling )
{
    size_t relabelling_size = relabelling.size();
    vector<int> copy_relabelling = relabelling;
    
    for (int counter = 0; counter < relabelling_size; ++counter)
    {
        relabelling[copy_relabelling[counter]] = counter;
    }
}
