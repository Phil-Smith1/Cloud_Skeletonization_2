#include "Custom.h"

Custom::Custom ( bool t, vector<int>const& w_r, vector<int>const& l_r, vector<int>const& r_r, vector<int> c_s_r, bool g_d_c_s, int c_s_p, string const& n_t, double n_p, bool aR, bool m, bool h, int r, vector<double> a_v, double e, bool g_d_n_i, vector<double> n_i_p, double o_r, string const& f_f, double s, double m_c_s_f )
{
    test = t;
    wheel_range = w_r;
    lattice_range = l_r;
    row_range = r_r;
    concentric_squares_range = c_s_r;
    graph_dependent_cloud_size = g_d_c_s;
    cloud_size_parameter = c_s_p;
    noise_type = n_t;
    noise_parameter = n_p;
    alphaReeb = aR;
    mapper = m;
    hopes = h;
    repetitions = r;
    alpha_values = a_v;
    epsilon = e;
    graph_dependent_num_intervals = g_d_n_i;
    num_intervals_parameter = n_i_p;
    overlap_ratio = o_r;
    filter_function = f_f;
    sigma = s;
    min_comp_size_fraction = m_c_s_f;
    
    if (test == true)
    {
        graph_dependent_cloud_size = false;
        cloud_size_parameter = 1000;
        repetitions = 10;
        alpha_values.clear();
        alpha_values.push_back( 0.3 );
        epsilon = 0.1;
        graph_dependent_num_intervals = false;
        num_intervals_parameter.clear();
        num_intervals_parameter.push_back( 15 );
        overlap_ratio = 0.5;
        filter_function = "Distance";
        sigma = 0.1;
        min_comp_size_fraction = 0.01;
    }
}

Custom::Custom(){}
Custom::~Custom(){}
