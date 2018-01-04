#pragma once

#include <string>
#include <vector>

using namespace std;

class Custom
{
    public:
    
    string filter_function, noise_type;
    bool test, alphaReeb, mapper, hopes, graph_dependent_cloud_size, graph_dependent_num_intervals;
    int repetitions, cloud_size_parameter;
    double epsilon, overlap_ratio, sigma, min_comp_size_fraction, noise_parameter;
    vector<int> wheel_range, lattice_range, row_range, concentric_squares_range;
    vector<double> alpha_values, num_intervals_parameter;
    
    Custom ( bool t, vector<int>const& w_r, vector<int>const& l_r, vector<int>const& r_r, vector<int> c_s_r, bool g_d_c_s, int c_s_p, string const& n_t, double n_p, bool aR, bool m, bool h, int r, vector<double> a_v, double e, bool g_d_n_i, vector<double> n_i_p, double o_r, string const& f_f, double s, double m_c_s_f );
    
    Custom();
    ~Custom();
};
