#pragma once

#include <string>
#include <vector>

using namespace std;

class Input
{
public:
    
    string noise_type, pattern_type, filter_function;
    bool graph_dependent_cloud_size, alphaReeb, mapper, hopes, graph_dependent_num_intervals;
    int cloud_size_parameter, pattern_size, repetitions, num_intervals = 0;
    double noise_parameter, alpha = 0, epsilon, num_intervals_param = 0, overlap_ratio, sigma, min_comp_size_fraction;
    vector<double> alpha_values, num_intervals_parameter;
    
    Input ( bool g_d_c_s, int c_s_p, string const& n_t, double n_p, string const& p_t, int p_s, bool aR, bool m, bool h, int r, vector<double> a_v, double e, bool g_d_n_i, vector<double> n_i_p, double o_r, string const& f_f, double s, double m_c_s_f );
    
    Input();
    ~Input();
};
