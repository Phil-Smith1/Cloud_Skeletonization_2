#pragma once

#include <string>

using namespace std;

class Input
{
    public:
    
    bool graph_dependent_cloud_size, alphaReeb, mapper, hopes, graph_dependent_num_intervals;
    int pattern_size_1, pattern_size_2, cloud_size_parameter, repetitions, num_intervals = 0;
    double noise_parameter, alpha = 0, num_intervals_param = 0;
    string pattern_type, noise_type;
    
    Input ( string const& p_t, int p_s_1, int p_s_2, bool g_d_c_s, int c_s_p, string const& n_t, double n_p, bool aR, bool m, bool h, int r );
    
    Input();
    ~Input();
};
