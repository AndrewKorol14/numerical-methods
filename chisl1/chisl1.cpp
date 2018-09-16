#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

void input(double **a, int n, int m)
{
	for (int i = 0; i < n; i++)
		for(int j=0; j<m; j++)
		cin >> a[i][j];
	system("cls");
}
void output2(double **a, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << setw(5) << a[i][j]<<"     ";
		cout << endl;
	}
}
void Gauss_method(double **a, double *x, int n, int m)
{
	for(int k=0, l=0; k<n; k++, l++)
	{
		double max = a[k][l]; int max_ind = k;
		for (int i = k; i < n; i++)               // поиск максимального элемента в 0-ом столбце
		{
			if (abs(a[i][l]) > abs(max) && a[i][l] != 0)
			{
				max = a[i][l]; max_ind = i;
			}
		}
		for (int j = l; j < m; j++)               // замена k-ой строки на строку с максимальным элементом
		{
			double tmp = a[max_ind][j]; a[max_ind][j] = a[k][j]; a[k][j] = tmp; 
		}
		double q = a[k][l];                      //приведение диагонали к 1, а всё что ниже неё к 0
		for (int j = l; j < m; j++)
		{
			a[k][j] = a[k][j] / q;               //деление первой строки на первый элемент
		}
		for (int i = k+1; i < n; i++)
		{
			double perv = a[i][l];
			for (int j = l; j < m; j++)      
			{
				a[i][j] = a[i][j] - a[k][j] * perv;  // непосредственно приведение диагонали к 1
			}
		}		
	}
	x[n - 1] = a[n - 1][m - 1];               //обратный ход Гаусса
	for (int i = n-2; i >= 0; i--)
	{
		for (int j=n-1; j>i; j--)
		{
			x[i]+=(x[j]*a[i][j]);
		}
		x[i] = a[i][m - 1] - x[i];
	}
}
void copy(double **a, double **a1, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)            //копирование системы
		{
			a1[i][j] = a[i][j];
		}
	}
}
void output1(double *x, int n)
{
	for (int i = 0; i<n; i++)
		cout << setw(5) << x[i] << "       ";
	cout << endl;
}
double nevyazka(double *f, double **a, double *x, int n, int m)
{
	for (int i = 0; i < n; i++)              //вектор невязки
	{
		f[i] -= a[i][m - 1];
		for (int j = 0; j < m-1; j++)
		{
			f[i] += a[i][j] * x[j];
		}
	}
	double d = abs(f[0]);                    //норма
	for (int i = 0; i < n; i++)
	{
		if (abs(d) > abs(f[i]))
			d = abs(f[i]);
	}
	return d;
}
int main()
{
	int n; 
	cout << "Enter the number of variables, please..." << endl;
	cin >> n; int m = n + 1;
	double**A = new double*[n];
	for (int i = 0; i < n; i++)
		A[i] = new double[m];
	double**A1 = new double*[n];
	for (int i = 0; i < n; i++)
		A1[i] = new double[m];
	double *X = new double[n];
	double *F = new double[n];
	for (int i = 0; i < n; i++)
	{
		X[i] = 0;
		F[i] = 0;
	}
	cout << "Enter the system of linear equations, please..." << endl;
	input(A, n, m);
	copy(A, A1, n, m);
	cout << "The system of linear equations:" << endl;
	output2(A, n, m);
	Gauss_method(A, X, n, m);
	cout << "The system of linear equations after transformation:" << endl;
	output2(A, n, m);
	cout << "Answers of the system of linear equations:" << endl;
	output1(X, n);
	double d=nevyazka(F, A1, X, n, m);
	cout << "Error vector:" << endl;
	output1(F, n);
	cout << "Norm:" << endl;
	cout << d << endl;
	for (int i = 0; i < n; i++)
		delete A[i];
	delete[]A;
	for (int i = 0; i < n; i++)
		delete A1[i];
	delete[]A1;
	delete[]X;
	delete[]F;
	return 0;
}