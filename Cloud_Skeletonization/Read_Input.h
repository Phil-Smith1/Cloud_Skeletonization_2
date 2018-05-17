#pragma once

#include <sstream>

#include "Input.h"

void Read_Input ( string const& line_data, Input& input )
{
    bool g_d_c_s, aR, m, h;
    int p_s_1, p_s_2, c_s_p, r;
    double n_p;
    string p_t, n_t;
    stringstream stream;
    
    stream << line_data;
    
    stream >> p_t >> p_s_1 >> p_s_2 >> g_d_c_s >> c_s_p >> n_t >> n_p >> aR >> m >> h >> r;
    
    Input inp( p_t, p_s_1, p_s_2, g_d_c_s, c_s_p, n_t, n_p, aR, m, h, r );
    
    input = inp;
}
