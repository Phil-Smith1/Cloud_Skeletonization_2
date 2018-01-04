#pragma once

#include <sstream>
#include <string>

using namespace std;

string Num_To_String ( int num )
{
	stringstream ss;
	ss << num;
	string str = ss.str();
	return str;
}

string Num_To_String ( double num )
{
	stringstream ss;
	ss << num;
	string str = ss.str();
	return str;
}
