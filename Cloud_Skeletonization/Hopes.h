#pragma once

#include "Graph_H.h"
#include "Single_Edge_Clustering.h"
#include "Find_Diagonal_Gaps.h"

void Hopes ( vector<P2>& cloud, Graph_H& hopes_graph, double& noise )
{
    vector<vector<P2>> clouds;
    clouds.assign( 1, cloud );
    
    Single_Edge_Clustering( 3, clouds );
    
    size_t cloud_size = clouds.size();
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        cloud = clouds[counter];
        
        if (clouds[counter].size() < 9) continue;
        
        Filtration filtration( clouds[counter] );
        
        filtration.Persistence1d( );
        
        int num_dots = (int)filtration.persistence.size(), index_above_gap;
        vector<int> graph_edges = filtration.negative_edges;
        vector<IndexValue> diagonal_gaps( num_dots );
        
        if (filtration.persistence.size())
        {
            Find_Diagonal_Gaps( filtration.persistence, index_above_gap, diagonal_gaps );
            
            for (int i = index_above_gap; i < filtration.persistence.size(); ++i)
            {
                graph_edges.push_back( filtration.persistence[i].edge );
                if (filtration.persistence[i].birth > noise) noise = filtration.persistence[i].birth;
            }
        }
        
        hopes_graph.Initialise_Graph( filtration.edges, graph_edges, (int)filtration.delaunay.number_of_vertices() );
    }
}
