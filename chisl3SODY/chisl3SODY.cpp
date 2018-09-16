#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void yavn_Eyler(double *u, int n, double* eps, double t_max, int NIT, double T);
void neyavn_Eyler(double* u, int n, double t_min, int NIT, double* eps, double t_max, double T);

void func(double* f, double *y, double t)     //система уравнений
{
	f[0] = (1/1.25)*y[1]*y[2];
	f[1] = (3.5/2.25)*y[0]*y[2];
	f[2] = -(1 / 1.25)*y[0] * y[1];
}
int main()
{
	double T = 1.0;
	double eps1 = 0.001;
	double eps2 = 0.00001;
	double t_max = 0.005;
	double t_min = 0.001;
	int NIT = 3000;
	int n = 3;
	
	double* U0 = new double[n];
		U0[0] = 1;
		U0[1] = 1;
		U0[2] = 1;
	double* eps = new double[n];
		eps[0] = 0.001;
		eps[1] = 0.001;
		eps[2] = 0.001;
	
		int K=0;
		cout << "1 - yavnEyler" << endl;
		cout << "2 - neyavnEyler" << endl;
		cout << "3 - exit" << endl;
		while (K != 3)
		{
			cin >> K;
			system("cls");
			switch (K)
			{
			case 1: {yavn_Eyler(U0, n, eps, t_max, NIT, T); break; }
			case 2: {neyavn_Eyler(U0, n, t_min, NIT, eps, t_max, T); break; }
			}
		}
	delete[]U0;
	delete[]eps;
    return 0;
}

