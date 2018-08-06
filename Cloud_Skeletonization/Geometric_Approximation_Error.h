#pragma once

#include "Extract_Edges.h"

double Geometric_Approximation_Error ( Graph const& g, vector<P2>const& cloud )
{
    vector<pair<P2, P2>> lines;
    
    Extract_Edges( g, lines );
    
    double gae = 0;
    
    for (int counter = 0; counter < cloud.size(); ++counter)
    {
        double min_dist = 1e10;
        
        for (auto l : lines)
        {
            L2 line( l.first, l.second );
            
            L2 perp = line.perpendicular( cloud[counter] );
            
            bool same_side = false;
            
            if (perp.oriented_side( l.first ) == perp.oriented_side( l.second )) same_side = true;
            
            double distance;
            
            if (!same_side) distance = sqrt( CGAL::squared_distance( cloud[counter], line ) );
            
            else distance = min( sqrt( CGAL::squared_distance( cloud[counter], l.first ) ), sqrt( CGAL::squared_distance( cloud[counter], l.second ) ) );
            
            if (distance < min_dist) min_dist = distance;
        }
        
        if (min_dist > gae) gae = min_dist;
    }
    
    return gae;
}
