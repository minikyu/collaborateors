#pragma once
#include<iostream>
#include<sstream>
using namespace std;

double str_to_dou(string str)
{
	double dou;
	stringstream sstr(str);
	sstr >> dou;
	return dou;
}

int str_to_int(string str)
{
	int in;
	stringstream sstr(str);
	sstr >> in;
	return in;
}

int keep_window_open()
{
	char chr;
	cout << "Enter a character to quit...";
	cin >> chr;
	return 0;
}

