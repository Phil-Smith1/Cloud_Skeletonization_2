#pragma once

class AlphaReeb_Parameters
{
    public:
    
    double min_comp_size_fraction, epsilon, alpha;
    
    AlphaReeb_Parameters ( double e, double a, double m_c_s_f );
    
    AlphaReeb_Parameters ();
    
    ~AlphaReeb_Parameters ();
};
