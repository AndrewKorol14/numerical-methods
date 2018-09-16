#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

double func(double x);

double integral_Simpson1(double a, double b, int n);

double Simpson_method_1(double a, double b, double eps)
{
	int n = 1, k = 0;
	double I_h_2, I_h;
	cout << "k" << "          " << "I_h_2" << "          " << "I_h" << endl;
	do
	{
		I_h_2 = integral_Simpson1(a, b, n);
		n *= 2;
		I_h = integral_Simpson1(a, b, n);
		cout << k++ << "          " << I_h_2 << "          " << I_h << endl;
	} while (abs(I_h_2 - I_h) > 15 * eps);
	return I_h;
}
double integral_Simpson1(double a, double b, int n)
{
	double h = (b - a) / (2*n);
	double integr = func(b) + func(a);
	for (int i = 1; i <= n; i++)
	{
		integr += 4 * func(a + h*(2 * i - 1));
	}
	for (int i = 1; i <= n-1; i++)
	{
		integr += 2 * func(a + h*2*i);
	}
	integr *= h / 3;
	return integr;
}