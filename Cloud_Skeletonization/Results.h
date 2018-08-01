#pragma once

#include <vector>

using namespace std;

class Results
{
    public:
    
    double parameter, time, mean_time, Betti_success_rate, homeo_success_rate;
    vector<bool> Betti_success, homeo_success;
    
    Results();
    ~Results();
};
