#include "Mapper_Parameters.h"

Mapper_Parameters::Mapper_Parameters ( int n_i, double o_r, string const& f_f, double s, double m_c_s_f )
{
    num_intervals = n_i;
    overlap_ratio = o_r;
    filter_function = f_f;
    sigma = s;
    min_comp_size_fraction = m_c_s_f;
}

Mapper_Parameters::Mapper_Parameters(){}

Mapper_Parameters::~Mapper_Parameters(){}

