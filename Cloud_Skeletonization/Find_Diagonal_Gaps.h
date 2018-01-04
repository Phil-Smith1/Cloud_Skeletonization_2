#pragma once

#include "Life.h"
#include "IndexValue.h"

bool IncreasingSpans ( Life const& l1, Life const& l2 )
{
    return l1.span < l2.span;
}

bool DecreasingValues ( IndexValue const& p1, IndexValue const& p2 )
{
    return p1.value > p2.value;
}

void Find_Diagonal_Gaps ( vector<Life>& Persistence, vector<int>& IndicesAbove, vector<IndexValue>& DiagonalGaps )
{
    size_t nDots = Persistence.size();
    
    sort( Persistence.begin(), Persistence.end(), IncreasingSpans );
    
    DiagonalGaps[0] = IndexValue( 0, Persistence[0].span ); // Smallest gap.
    
    for (int i = 1; i < nDots; ++i)
    {
        DiagonalGaps[i] = IndexValue( i, Persistence[i].span - Persistence[i-1].span );
    }
    
    sort( DiagonalGaps.begin(), DiagonalGaps.end(), DecreasingValues );
    
    IndicesAbove[0] = DiagonalGaps[0].index; // Index of dots above the 1st widest diagonal gap.
    
    for (size_t i = 1; i < nDots; ++i)
    {
        IndicesAbove[i] = min( DiagonalGaps[i].index, IndicesAbove[i-1] );
    }
}
