#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

double func1(double x, double y);

double integral_Simpson2(double a, double b, double c, double d, int n);

double Simpson_method_2(double a, double b, double c, double d, double eps)
{
	int n = 1, k = 0;
	double I_h_2, I_h;
	cout << "k" << "          " << "I_h_2" << "          " << "I_h" << endl;
	do
	{
		I_h_2 = integral_Simpson2(a, b, c, d, n);
		n *= 2;
		I_h = integral_Simpson2(a, b, c, d, n);
		cout << k++ << "          " << I_h_2 << "          " << I_h << endl;
	} while (abs(I_h_2 - I_h) > 15 * eps);
	return I_h;
}
double integral_Simpson2(double a, double b, double c, double d, int n)
{
	double h_x = (b - a) / (2 * n);
	double h_y = (d - c) / (2 * n);
	double integr = 0.0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			integr += func1(a + h_x * 2 * i, c + h_y * 2 * j) + 4 * func1(a + h_x*(2 * i + 1), c + h_y * 2 * j) + func1(a + h_x*(2 * i + 2), c + h_y * 2 * j) +
				4 * func1(a + h_x * 2 * i, c + h_y*(2 * j + 1)) + 16 * func1(a + h_x*(2 * i + 1), c + h_y*(2 * j + 1)) + 4 * func1(a + h_x*(2 * i + 2), c + h_y*(2 * j + 1)) +
				func1(a + h_x * 2 * i, c + h_y*(2 * j + 2)) + 4 * func1(a + h_x*(2 * i + 1), c + h_y*(2 * j + 2)) + func1(a + h_x*(2 * i + 2), c + h_y*(2 * j + 2));
		}
	}
	integr *= (h_x*h_y) / 9;
	return integr;
}