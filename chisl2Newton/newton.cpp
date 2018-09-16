#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cfloat>
#include <iomanip>
using namespace std;

void jacobian(double **J, double *x)      //вычисление матрицы якоби
{
	J[0][0] = 6 * pow(x[0], 2);
	J[0][1] = -2 *x[1];
	J[1][0] = pow(x[1], 3);
	J[1][1] = 3*pow(x[1], 2)*x[0]-1;
}
void equations(double *x, double *f)
{
	f[0] = (2*pow(x[0], 3) - pow(x[1], 2) - 1);
	f[1] = (x[0]*pow(x[1], 3) - x[1] - 4);
}
void output1(double **a, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(5) << a[i][j]<<"     ";
		}
		cout << endl;
	}
}
void output2(double *b, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << setw(5) << b[i]<<"     ";
	}
	cout << endl;
}
void Gauss_method(double **J, double *delx, double *f, int n, int m)
{
	for (int i = 0; i < n; i++)
		f[i] = -f[i];
	for (int k = 0, l = 0; k<n; k++, l++)
	{
		double max = J[k][l]; int max_ind = k;
		for (int i = k; i < n; i++)               // поиск максимального элемента в 0-ом столбце
		{
			if (abs(J[i][l]) > abs(max) && J[i][l] != 0)
			{
				max = J[i][l]; max_ind = i;
			}
		}
		for (int j = l; j < m; j++)               // замена k-ой строки на строку с максимальным элементом
		{
			double tmp = J[max_ind][j]; J[max_ind][j] = J[k][j]; J[k][j] = tmp;
			double tmp1 = f[max_ind]; f[max_ind] = f[k]; f[k] = tmp1;
		}
		double q = J[k][l];                      //приведение диагонали к 1, а всЄ что ниже неЄ к 0
		for (int j = l; j < m; j++)
		{
			J[k][j] = J[k][j] / q;               //деление первой строки на первый элемент
		}
		f[k] = f[k] / q;
		for (int i = k + 1; i < n; i++)
		{
			double perv = J[i][l];
			for (int j = l; j < m; j++)
			{
				J[i][j] = J[i][j] - J[k][j] * perv;  // непосредственно приведение диагонали к 1
			}
			f[i] = f[i] - f[k] * perv;
		}
	}
	delx[n - 1] = f[n - 1];               //обратный ход √аусса    
	for (int i = n - 2; i >= 0; i--)
	{
		delx[i] = f[i];
		for (int j = n-1; j>i; j--)
		{
			delx[i] -= (delx[j] * J[i][j]);
		}
	}
}
void Newton(double **J, double *f, double *x, double* delx, int NIT, int n, double eps)    //метод Ќьютона
{
	cout << setw(3) << "k" << setw(9) << "del1" << setw(18) << "del2" << endl;
	cout << "---------------------------------" << endl;
	for (int k = 1; k <= NIT; k++)
	{
		cout << setw(3) << k;
		double del1, del2, xk;
		for (int i = 0; i < n; i++)
		{
			jacobian(J, x);                                               //матрица якоби
			equations(x, f);                                              //вектор нев€зки
			Gauss_method(J, delx, f, n, n);
			xk = x[i];
			x[i] = delx[i] + x[i];                                        //увеличение X на dX
			del1 = abs(f[0]);
			for (int g = 0; g < n; g++)
			{
				if (del1 < abs(f[i]))                                     //поиск del1 и del2
				{
					double tmp = del1; del1 = abs(f[i]); f[i] = tmp;
				}
			}
			if (x[i] < 1) del2 = abs(x[i] - xk);
			if (x[i] >= 1) del2 = abs((x[i] - xk) / x[i]);
		}
		cout << "     " << del1;
		cout << "          " << del2<<endl;
		if (k == NIT) { cout << " Limit NIT" << endl; break; }         //условие выхода через предельное число итераций
	    if ((del1 <= eps)&&(del2<=eps)) break;                        //условие выхода из метода через del1 и del2
	}
}