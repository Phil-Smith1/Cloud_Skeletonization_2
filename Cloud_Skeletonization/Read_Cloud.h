#pragma once

#include <fstream>
#include <sstream>

#include "Data_Pt.h"
#include "Cloud_File_Name.h"

void Read_Cloud ( bool test, string const& cloud_directory, Input const& input, int iteration, int& expected_Betti_num, double& graph_length, vector<Data_Pt>& cloud )
{
    string cloud_file;
    Cloud_File_Name( test, cloud_directory, input, iteration, cloud_file );
    
    ifstream ifs( cloud_file );
    
    stringstream stream;
    string line_data, a, b, c, d, e, f;
    double x, y;
    
    getline( ifs, line_data );
    getline( ifs, line_data );
    
    stream << line_data;
    stream >> a >> b >> c >> d >> e >> f >> expected_Betti_num >> graph_length;
    
    while (getline( ifs, line_data ))
    {
        stream.clear();
        stream << line_data;
        
        if (stream >> x >> y)
        {
            cloud.push_back( Data_Pt(Point2d(x, y)) );
        }
    }
    
    size_t c_s = cloud.size();
    
    for (int counter = 0; counter < c_s; ++counter)
    {
        cloud[counter].index = counter;
    }
}
