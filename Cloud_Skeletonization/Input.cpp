#include "Input.h"

Input::Input ( bool g_d_c_s, int c_s_p, string const& n_t, double n_p, string const& p_t, int p_s, bool aR, bool m, bool h, int r, vector<double> a_v, double e, bool g_d_n_i, vector<double> n_i_p, double o_r, string const& f_f, double s, double m_c_s_f )
{
    graph_dependent_cloud_size = g_d_c_s;
    cloud_size_parameter = c_s_p;
    noise_type = n_t;
    noise_parameter = n_p;
    pattern_type = p_t;
    pattern_size = p_s;
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
}

Input::Input(){}

Input::~Input(){}
