#pragma once

#include "Graph_H.h"
#include "Convert_Cloud.h"
#include "Single_Edge_Clustering.h"
#include "Find_Diagonal_Gaps.h"

void Hopes ( vector<Data_Pt>const& initial_cloud, Graph_H& hopes_graph )
{
    // Converting the cloud from Data_Pt to P2.
    
    vector<P2> cloud;
    
    Convert_Cloud_1( initial_cloud, cloud );
    
    vector<vector<P2>> clouds;
    clouds.assign( 1, cloud );
    
    Single_Edge_Clustering( 3, clouds );
    
    size_t cloud_size = clouds.size();
    
    for (int counter = 0; counter < cloud_size; ++counter)
    {
        cloud = clouds[ counter ];
        
        if ( clouds[ counter ].size() < 9 ) continue;
        
        Filtration filtration( clouds[ counter ] );
        
        filtration.Persistence1d( );
        
        // Find k-th widest diagonal gap in Persistence, k = DiagGap.
        
        int num_dots = (int)filtration.persistence.size();
        vector<int> indices_above_gap( num_dots, 0 );
        vector<IndexValue> diagonal_gaps( num_dots );
        vector<int> graph_edges = filtration.negative_edges;
        
        if ( filtration.persistence.size() )
        {
            Find_Diagonal_Gaps( filtration.persistence, indices_above_gap, diagonal_gaps );
            
            for (int i = indices_above_gap[0]; i < filtration.persistence.size(); ++i)
            {
                graph_edges.push_back( filtration.persistence[ i ].edge );
            }
        }
        
        hopes_graph.Initialise_Graph( filtration.edges, graph_edges, (int)filtration.delaunay.number_of_vertices() );
    }
}
