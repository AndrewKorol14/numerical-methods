#include "stdafx.h"
#include <iostream>
#include <iomanip>
using namespace std;

void jacobian(double **J, double *x);
void equations(double *x, double *f);
void output1(double **a, int n, int m);
void output2(double *b, int n);
void Newton(double **J, double *f, double *x, double* delx, int NIT, int n, double eps);
void Gauss_method(double **J, double *delx, double *f, int n, int m);
int main()
{
	int n, m; 
	double eps1 = 0.000000001, eps2 = 0.000000001;
	int NIT = 100;
	cout << "Enter the number of variables..." << endl;
	cin >> n;                                                             //2
	cout << "Enter the number of equations..." << endl;
	cin >> m;                                                             //2 
	double **J = new double*[n];
	for (int i = 0; i < n; i++)
		J[i] = new double[m];
	double *X = new double[n];
	double *F = new double[m];
	double *delX = new double[n];
	cout << "Enter the initial approximation..." << endl;                 //1; 1
	for(int i=0; i<n; i++)                                                //2; 1,5     
	cin >> X[i];                                                          //-3; -1,5   
	Newton(J, F, X, delX, NIT, n, eps1);
	cout << "X: " << endl;
	output2(X, n);

	for (int i = 0; i < n; i++)
		delete J[i];
	delete[]J;
	delete[]X;
	delete[]F;
	return 0;
}

