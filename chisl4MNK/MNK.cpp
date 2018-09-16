#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void Gauss_method(double **a, double *x, double* b, int n, int m);
double func1(double* koef, double x);

void mnk(double* x, double* y, double* a, double* y1, double* y2, double* a1, int N, int m)   //график доделать!!!!!!!!!!!
{
	double* POWERX = new double[2 * m+1];
	double* PRAW = new double[m+1];
	double** SUMX = new double*[m + 1];
	for (int i = 0; i < m + 1; i++)
	{
		SUMX[i] = new double[m + 1];
	}
	for (int i = 0; i < 2 * m+1; i++)        //суммы x[i] в степени k
	{
		POWERX[i] = 0;
		for (int j = 0; j < N; j++)
		{
			POWERX[i] += pow(x[j], i);
		}
	}
	for (int i = 0; i < m + 1; i++)          //матрица коэффициентов сумм x[i]
	{
		for (int j = 0; j < m + 1; j++)
		{
			SUMX[i][j] = POWERX[i + j];
		}
	}
	
	for (int i = 0; i < m + 1; i++)           //правая часть
	{
		PRAW[i] = 0;
		for (int j = 0; j < N; j++)
		{
			PRAW[i] += log(y[j]) * pow(x[j], i);  
		}
	}
	Gauss_method(SUMX, a, PRAW, m + 1, m + 1);
	double S_tmp=0;
	for (int i = 0; i < N; i++)              //остаточная дисперсия
	{
		S_tmp += (log(y[i])-a[0]-a[1]*x[i]);  
	}
    double S_2 = (S_tmp*S_tmp) / (N - m - 1);
	cout << "S^2:   " << S_2<< endl;
	cout << "Sigma:   " << sqrt(S_2) << endl;   //среднеквадратичное отклонение
	for (int i = 0; i < N; i++)
	{
		y1[i] = a[0] + a[1] * x[i];
	}
	a1[0] = exp(a[0]);
	a1[1] = a[1];
	for (int i = 0; i < N; i++)
	{
		y2[i] = exp(y1[i]);
	}
		delete[]POWERX;
	delete[]PRAW;
	for (int i = 0; i < m + 1; i++)
		delete SUMX[i];
	delete[]SUMX;
}
void Gauss_method(double **a, double *x, double *b, int n, int m)
{
	for (int k = 0, l = 0; k<n; k++, l++)
	{
		double max = a[k][l]; int max_ind = k;
		for (int i = k; i < n; i++)               // поиск максимального элемента в 0-ом столбце
		{
			if (abs(a[i][l]) > abs(max) && a[i][l] != 0)
			{
				max = a[i][l]; max_ind = i;
			}
		}
		for (int j = l; j < n; j++)               // замена k-ой строки на строку с максимальным элементом
		{
			double tmp = a[max_ind][j]; a[max_ind][j] = a[k][j]; a[k][j] = tmp;
		}
		double tmp1 = b[max_ind]; b[max_ind] = b[k]; b[k] = tmp1;
		double q = a[k][l];                      //приведение диагонали к 1, а всё что ниже неё к 0
		b[k] = b[k] / q;
		for (int j = l; j < n; j++)
		{
			a[k][j] = a[k][j] / q;               //деление первой строки на первый элемент
		}
		
		for (int i = k + 1; i < n; i++)
		{
			double perv = a[i][l];
			for (int j = l; j < n; j++)
			{
				a[i][j] = a[i][j] - a[k][j] * perv;  // непосредственно приведение диагонали к 1
			}
			b[i] = b[i] - b[k] * perv;
		}
	}
	x[n - 1] = b[n - 1];               //обратный ход Гаусса
	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = b[i];
		for (int j = n - 1; j>i; j--)
		{
			x[i] -= (x[j] * a[i][j]);
		}
	}
}
double func1(double* koef, double x)
{
	return koef[0] * exp(-koef[1] * x);
}
