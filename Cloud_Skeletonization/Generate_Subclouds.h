#pragma once

#include "Data_Pt.h"

// Alpha-Reeb.

void Intervals ( double alpha, double max, vector<pair<double, double>>& interval_endpoints )
{
	double interval_start = 0, interval_end;

	for (int counter = 0; interval_start < max; ++counter)
	{
		interval_start = 0.5 * counter * alpha;
		interval_end = (0.5 * counter + 1) * alpha;
		interval_endpoints.push_back(make_pair(interval_start, interval_end));
		interval_start += 0.5 * alpha;
	}
}

// Mapper.

void Intervals ( multimap<double, int>& filter_multimap, int num_intervals, double overlap_ratio, vector<pair<double, double>>& interval_endpts )
{
    auto it_1 = filter_multimap.begin();
    double min = it_1->first;
    auto it_2 = filter_multimap.rbegin();
    double max = it_2->first;
    double range = max - min;
    
    double length_interval = range / (double)(1 + (num_intervals - 1) * (1 - overlap_ratio));
    
    double interval_start, interval_end;
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        interval_start = min + counter * length_interval * (1 - overlap_ratio);
        interval_end = interval_start + length_interval;
        
        interval_endpts.push_back( make_pair( interval_start, interval_end ) );
    }
}

// Alpha-Reeb.

void Generate_Subclouds ( vector<Data_Pt> const& cloud, multimap<double, int>& filter_multimap, double alpha, vector<vector<Data_Pt>>& subcloud )
{
	// Finding interval endpoints.

	vector<pair<double, double>> interval_endpoints;
	interval_endpoints.clear();

	auto it = filter_multimap.rbegin();
	double max_dist_from_root = it->first;

	Intervals( alpha, max_dist_from_root, interval_endpoints );
    
    size_t num_intervals = interval_endpoints.size();
	
	subcloud.resize( num_intervals );

	// Splitting multimap according to interval endpoints.

	multimap<double, int>::iterator it_start, it_end;

	vector<pair<multimap<double, int>::iterator, multimap<double, int>::iterator>> pointers;
	pointers.clear();

	for (int counter = 0; counter < num_intervals; ++counter)
	{
		it_start = filter_multimap.lower_bound(interval_endpoints[counter].first);
		it_end = filter_multimap.upper_bound(interval_endpoints[counter].second);

		pointers.push_back(make_pair(it_start, it_end));
	}

	// Assigning points to subclouds.

	for (int counter = 0; counter < num_intervals; ++counter)
	{
		for (multimap<double, int>::iterator it = pointers[counter].first; it != pointers[counter].second; ++it)
		{
			subcloud[counter].push_back(cloud[it->second]);
		}
	}
}

// Mapper.

void Generate_Subclouds ( vector<Data_Pt>const& cloud, multimap<double, int>& filter_multimap, int num_intervals, double overlap_ratio, vector<vector<Data_Pt>>& subcloud )
{
    vector<pair<double, double>> interval_endpts;
    interval_endpts.clear();
    
    Intervals( filter_multimap, num_intervals, overlap_ratio, interval_endpts );
    
    // Splitting multimap according to interval endpoints.
    
    multimap<double, int>::iterator it_start, it_end;
    
    vector<pair<multimap<double, int>::iterator, multimap<double, int>::iterator>> pointers;
    pointers.clear();
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        it_start = filter_multimap.lower_bound( interval_endpts[counter].first );
        it_end = filter_multimap.upper_bound( interval_endpts[counter].second );
        
        pointers.push_back(make_pair(it_start, it_end));
    }
    
    // Assigning points to subclouds.
    
    for (int counter = 0; counter < num_intervals; ++counter)
    {
        for (auto it = pointers[counter].first; it != pointers[counter].second; ++it)
        {
            subcloud[counter].push_back( cloud[it->second] );
        }
    }
}

