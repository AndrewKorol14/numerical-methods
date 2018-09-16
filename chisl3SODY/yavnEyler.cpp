#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void func(double* f, double* y, double t);

double min_TAU(double* tau, int n)
{
	double min = tau[0];
	for (int i = 1; i < n; i++)
	{
		if (min > tau[i]) min = tau[i];
	}
	return min;
}
void yavn_Eyler(double *u, int n, double* eps, double t_max, int NIT, double T)
{
	double t = 0.000001, tk = 0; int k = 0;     
	double* Y = new double[n];
	double* F = new double[n];
	double* TAU = new double[n];
	for (int i = 0; i < n; i++)
	{
		Y[i] = u[i];
	}
	cout << setw(3) << "k" << setw(9) << "Y" << setw(28) << "t" << endl;
	cout << "--------------------------------------------" << endl;
	bool g = false;
	while (k<NIT)
	{
		func(F, Y, t);                           //вектор f
		for (int i = 0; i < n; i++)
		{
			TAU[i] = eps[i] / (abs(F[i]) + eps[i] / t_max);     //шаг итерации
		}
		tk = min_TAU(TAU, n);     //минимальный шаг
			for (int i = 0; i < n; i++)
			{
				Y[i] = Y[i] + tk*F[i];        //увеличиваем y на шаг
				t = t + tk;
				if (t >= T) { g = true; break; }     //проверка выхода за границы t
			if (g) break;
			cout << setw(3) << k << "      " << Y[0] << " ; " << Y[1] << setw(18) <<Y[2]<<"                "<< t << endl;
			k++;
			if (k >= NIT) { cout << "Limit NIT" << endl; break; }
		}
	}
	delete[]Y;
	delete[]F;
	delete[]TAU;
}