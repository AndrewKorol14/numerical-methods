#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;

double method_trap(double a, double b, double eps);
double Simpson_method_1(double a, double b, double eps);
double Simpson_method_2(double a, double b, double c, double d, double eps);

double func(double x)
{
	return (pow(sin(x), 2))/sqrt(1+pow(x, 3));
}
double func1(double x, double y)
{
	return sin(x + y);
}

int main()
{
	double a=0.0, b=1.234;
	double a1 = 0.0, b1 = 1.570796, c = 0.0, d = 0.785398;
	double eps = 0.00001; 
	cout << "WolframAlfa #1: " << endl;
	cout << " I = 0.34942" << endl;
	cout << "Method of trapeze: " << endl;
	cout << " I = " << method_trap(a, b, eps) << endl;
	cout << "Simpson method #1: " << endl;
	cout << " I = " << Simpson_method_1(a, b, eps) << endl;
	cout << "WolframAlfa #2" << endl;
	cout << " I = 1" << endl;
	cout << "Simpson method #2: " << endl;
	cout << " I = " << Simpson_method_2(a1, b1, c, d, eps) << endl;	
    return 0;
}

