#pragma once

#include <vector>

using namespace std;

class Results
{
    public:
    
    double parameter, time, mean_time, Betti_success_rate, homeo_success_rate, mgae;
    vector<bool> Betti_success, homeo_success;
    vector<double> geom_approx_error;
    
    Results();
    ~Results();
};
