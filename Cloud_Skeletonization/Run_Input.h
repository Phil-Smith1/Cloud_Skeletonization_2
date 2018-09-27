#pragma once

#include <string>
#include <vector>

using namespace std;

class Run_Input
{
    public:
    
    bool graph_dependent_cloud_size, regular, alphaReeb, mapper, hopes;
    int cloud_size_parameter, repetitions;
    string noise_type;
    vector<int> wheel_range, grid_cols_range, grid_rows_range, squares_range;
    vector<double> noise_parameter_range;
    
    Run_Input ( vector<int>const& w_r, vector<int>const& g_c_r, vector<int>const& g_r_r, bool reg, vector<int> s_r, bool g_d_c_s, int c_s_p, string const& n_t, vector<double> n_p_r, bool aR, bool m, bool h, int r );
    
    Run_Input();
    ~Run_Input();
};
