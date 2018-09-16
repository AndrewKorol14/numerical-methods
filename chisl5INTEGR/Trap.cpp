#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

double func(double x);

double integral_trap(int n, double a, double b);

double method_trap(double a, double b, double eps)
{
	int n = 1, k=0;
	double I_h_2, I_h;
	cout << "k" << "          " << "I_h_2" << "          " << "I_h" << endl;
	do
	{
		I_h_2 = integral_trap(n, a, b);
		n *= 2;
		I_h = integral_trap(n, a, b);
		cout << k++<< "          " << I_h_2 << "          " << I_h << endl;
	} 
	while (abs(I_h_2 - I_h) > 3 * eps);
	return I_h;
}

double integral_trap(int n, double a, double b)
{
	double h = (b - a) / n;
	double integr = func(b) + func(a);
	for (int i = 1; i <= n; i++)
	{
		integr += 2 * func(a + h*i);
	}
	integr *= h / 2;
	return integr;
}