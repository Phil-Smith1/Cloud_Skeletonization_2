#pragma once

#include <string>

using namespace std;

class Mapper_Parameters
{
    public:
    
    int num_intervals;
    double min_comp_size_fraction, overlap_ratio, sigma;
    string filter_function;
    
    
    Mapper_Parameters ( int n_i, double o_r, string const& f_f, double s, double m_c_s_f );
    
    Mapper_Parameters ();
    
    ~Mapper_Parameters ();
};
