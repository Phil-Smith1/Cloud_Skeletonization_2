#include "AlphaReeb_Parameters.h"

AlphaReeb_Parameters::AlphaReeb_Parameters ( double a, double e, double m_c_s_f )
{
    alpha = a;
    epsilon = e;
    min_comp_size_fraction = m_c_s_f;
}

AlphaReeb_Parameters::AlphaReeb_Parameters(){}

AlphaReeb_Parameters::~AlphaReeb_Parameters(){}
