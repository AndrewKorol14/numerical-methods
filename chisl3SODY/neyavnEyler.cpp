#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void Newton(double **y, int n, int NIT, double tau_k, double t_k, double *f, double t_k1, double eps);    //метод Ньютона

void func1(double* f, double **y, double t)
{
	f[0] = (1 / 1.25)*y[2][1] * y[2][2];
	f[1] = (3.5 / 2.25)*y[2][0] * y[2][2];
	f[2] = -(1 / 1.25)*y[2][0] * y[2][1];
}
void neyavn_Eyler(double* u, int n, double t_min, int NIT, double* eps, double t_max, double T)
{
	double t_k = 0, t_k1 = 0, tau_k_1=t_min, tau_k=t_min, tau_k1=0; int m = 3;
	double **Y = new double*[m];
	for (int i = 0; i < 3; i++)
	{
		Y[i] = new double[n];
	}
	double *F = new double[n];
	double *EPS = new double[n];
	double *TAU = new double[n];

	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++)
		{
			Y[i][j] = u[j];
		}
	}

	cout << setw(3) << "k" << setw(9) << "Y" << setw(28) << "t" << endl;
	cout << "--------------------------------------------" << endl;
	bool flag = false;
	for (int k = 0; t_k<T; k++)
	{
		t_k1 = t_k + tau_k;
		Newton(Y, n, NIT, tau_k, t_k, F, t_k1, 0.001);   //y_k+1 методом Ньютона
		for (int i = 0; i < n; i++)
		{
			EPS[i] = -(tau_k / (tau_k + tau_k_1))*(Y[2][i] - Y[1][i] - (tau_k / tau_k_1)*(Y[1][i] - Y[0][i]));  //локальная погрешность
		}
		for (int i = 0; i < n; i++)
		{
			if (abs(EPS[i]) > eps[i])            //если модуль лок. погрешности превышает eps_доп, то выполняются следующие инструкции с возращением в начало цикла
			{
				tau_k = tau_k / 2;
				t_k1 = t_k;
				for (int j = 0; j < n; j++) { Y[2][j] = Y[1][j]; }
				flag = true;
			}
			if (flag) break;
			TAU[i] = sqrt(eps[i] / abs(EPS[i]))*tau_k;     //шаг тау
		}
		if (flag) continue;
		tau_k1 = TAU[0];
		for (int i = 1; i < n; i++)
		{
			if (tau_k1 > TAU[i]) tau_k1 = TAU[i];          //минимальный среди шагов тау
		}
		if (tau_k1 > t_max) tau_k1 = t_max;
		cout << setw(3) << k << "      " << Y[2][0] << " ; " << Y[2][1] << setw(18) <<Y[2][2]<<"             "<< t_k1 << endl;
		for (int i = 0; i < n; i++)
		{
			Y[0][i] = Y[1][i]; Y[1][i] = Y[2][i];
		}
		tau_k_1 = tau_k;
		tau_k = tau_k1;
		t_k = t_k1;
	}
	for (int i = 0; i < n; i++)
	{
		delete Y[i];
	}
	delete[]Y;
	delete[]F;
	delete[]EPS;
	delete[]TAU;
}
void Newton(double **y, int n, int NIT, double tau_k, double t_k, double *f, double t_k1, double eps)    //метод Ньютона
{
	for (int k = 1; k <= NIT; k++)
	{
		double del1, del2, xk;
		for (int i = 0; i < n; i++)
		{
			func1(f, y, t_k1);
			xk = y[1][i];
			y[2][i] = y[1][i] + tau_k*f[i];                                        //увеличение X на dX
			del1 = abs(f[0]);
			for (int g = 0; g < n; g++)
			{
				if (del1 < abs(f[i]))                                     //поиск del1 и del2
				{
					del1 = abs(f[i]); 
				}
			}
			if (abs(y[2][i]) < 1) del2 = abs(y[2][i] - xk);
			if (abs(y[2][i]) >= 1) del2 = abs((y[2][i] - xk) / y[2][i]);
		}

		if (k == NIT) {/* cout << " Limit NIT 111" << endl;*/ break; }         //условие выхода через предельное число итераций
		if ((del1 <= eps) && (del2 <= eps)) break;                        //условие выхода из метода через del1 и del2
	}
}