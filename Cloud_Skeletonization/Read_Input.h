#pragma once

#include <sstream>

#include "Input.h"
#include "Go_To_Line.h"

void Read_Input ( string const& line_data, string const& alphaReeb_parameter_file, string const& alpha_values_file, string const& mapper_parameter_file, string const& num_intervals_parameter_file, int experiment_iter, Input& input )
{
    stringstream stream;
    string n_t, p_t, f_f;
    bool g_d_c_s, aR, m, h, g_d_n_i;
    int c_s_p, p_s, r;
    double n_p, e, o_r, s, m_c_s_f;
    vector<double> a_v, n_i_p;
    
    stream << line_data;
    
    stream >> p_t >> p_s >> g_d_c_s >> c_s_p >> n_t >> n_p >> aR >> m >> h >> r;
    
    if (aR)
    {
        ifstream ifs_1( alphaReeb_parameter_file );
        
        Go_To_Line( ifs_1, experiment_iter + 1 );
        
        string line_data_2;
        getline( ifs_1, line_data_2 );
        
        stream.clear();
        stream << line_data_2;
        
        stream >> e >> m_c_s_f;
        
        ifs_1.close();
        
        ifstream ifs_2( alpha_values_file );
        
        double alpha;
        
        while (getline( ifs_2, line_data_2 ))
        {
            stream.clear();
            stream << line_data_2;
            stream >> alpha;
            a_v.push_back( alpha );
        }
        
        ifs_2.close();
    }
    
    else
    {
        e = 0;
        m_c_s_f = 0;
    }
    
    if (m)
    {
        ifstream ifs_3( mapper_parameter_file );
        
        Go_To_Line( ifs_3, experiment_iter + 1 );
        
        string line_data_2;
        getline( ifs_3, line_data_2 );
        
        stream.clear();
        stream << line_data_2;
        
        stream >> g_d_n_i >> o_r >> f_f >> s >> m_c_s_f;
        
        ifs_3.close();
        
        ifstream ifs_4( num_intervals_parameter_file );
        
        double n_i;
        
        while (getline( ifs_4, line_data_2 ))
        {
            stream.clear();
            stream << line_data_2;
            stream >> n_i;
            n_i_p.push_back( n_i );
        }
        
        ifs_4.close();
    }
    
    else
    {
        g_d_n_i = false;
        o_r = 0;
        f_f = "n/a";
        s = 0;
    }
    
    Input inp( g_d_c_s, c_s_p, n_t, n_p, p_t, p_s, aR, m, h, r, a_v, e, g_d_n_i, n_i_p, o_r, f_f, s, m_c_s_f );
    
    input = inp;
}
