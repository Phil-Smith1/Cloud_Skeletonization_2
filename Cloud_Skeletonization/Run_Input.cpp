#include "Run_Input.h"

Run_Input::Run_Input ( vector<int>const& w_r, vector<int>const& g_c_r, vector<int>const& g_r_r, bool reg, vector<int> s_r, bool g_d_c_s, int c_s_p, string const& n_t, vector<double> n_p_r, bool aR, bool m, bool h, int r )
{
    wheel_range = w_r;
    grid_cols_range = g_c_r;
    grid_rows_range = g_r_r;
    regular = reg;
    squares_range = s_r;
    graph_dependent_cloud_size = g_d_c_s;
    cloud_size_parameter = c_s_p;
    noise_type = n_t;
    noise_parameter_range = n_p_r;
    alphaReeb = aR;
    mapper = m;
    hopes = h;
    repetitions = r;
}

Run_Input::Run_Input(){}
Run_Input::~Run_Input(){}
