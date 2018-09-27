#include "Input.h"

Input::Input ( string const& p_t, int p_s_1, int p_s_2, bool reg, bool g_d_c_s, int c_s_p, string const& n_t, double n_p, bool aR, bool m, bool h, int r )
{
    pattern_type = p_t;
    pattern_size_1 = p_s_1;
    pattern_size_2 = p_s_2;
    regular = reg;
    graph_dependent_cloud_size = g_d_c_s;
    cloud_size_parameter = c_s_p;
    noise_type = n_t;
    noise_parameter = n_p;
    alphaReeb = aR;
    mapper = m;
    hopes = h;
    repetitions = r;
}

Input::Input(){}
Input::~Input(){}
