#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

void mnk(double* x, double* y, double* a, double* y1, double* y2, double* a1, int N, int m);
void write_file(ofstream &out, double* y1, int N);
void read_file(ifstream &in, ofstream &out1, int N);
int main()
{
	int n = 7, m = 1, N=7;
	double* X = new double[n] { 60, 70, 80, 90, 100, 110, 120 };
	double* Y = new double[n] {0.0148, 0.0124, 0.0102, 0.0085, 0.0071, 0.0059, 0.0051};
	double* A = new double[m + 1];
	double* Y1 = new double[n];
	double* Y2 = new double[n];
	double* A1 = new double[m + 1];
	for (int i = 0; i < m + 1; i++)
		A[i] = 0;
	mnk(X, Y, A, Y1, Y2, A1, N, m);
	cout << "X:   ";
	for (int i = 0; i < N; i++)
		cout << X[i] << "     ";
	cout << endl;
	cout << "Y:   ";
	for (int i = 0; i < N; i++)
		cout << Y[i] << "     ";
	cout << endl;
	cout << "Y1:   ";
	for (int i = 0; i < N; i++)
		cout << Y1[i] << "     ";
	cout << endl;
	cout << "exp(Y1):   ";
	for (int i = 0; i < N; i++)
		cout << Y2[i] << "     ";
	cout << endl;
	cout << "A:   ";
	for (int i = 0; i < m + 1; i++)
		cout << A[i] << "     ";
	cout << endl;
	cout << "A':   ";
	for (int i = 0; i < m + 1; i++)
		cout << A1[i] << "     ";
	cout << endl;	
	ofstream out("pol_y1.txt");
	if (!out)
	{
		cout << "ERROR #1" << endl;
		return 1;
	}
	ofstream out2("pol_y2.txt");
	if (!out)
	{
		cout << "ERROR #2" << endl;
		return 1;
	}
	write_file(out, Y1, N);
	write_file(out2, Y2, N);
	out.close();
	out2.close();
	ifstream in("pol_y1.txt");
	if (!in)
		{
			cout << "ERROR #3" << endl;
			return 1;
	    }
	ofstream out1("tochka.txt");
	if (!out1)
	{
		cout << "ERROR #4" << endl;
		return 1;
	}
	read_file(in, out1, N);
	out1.close();
	in.close();
	ifstream in2("pol_y2.txt");
	if (!in2)
	{
		cout << "ERROR #5" << endl;
		return 1;
	}
	ofstream out3("tochka1.txt");
	if (!out3)
	{
		cout << "ERROR #6" << endl;
		return 1;
	}
	read_file(in2, out3, N);
	out3.close();
	in2.close();
	delete[]X;
	delete[]Y;
	delete[]A;
	delete[]Y1;
	delete[]Y2;
	delete[]A1;
    return 0;
}

void write_file(ofstream &out, double* y1, int N)
{
	for (int i = 0; i < N; i++)
	{
		double tmp = y1[i];
		out << tmp << endl;
	}
}
void read_file(ifstream &in, ofstream&out1, int N)
{
	char tmp[20]; char *p;
	in >> tmp;
	while (!in.eof())
	{
		int j=0, n;
		while (tmp[j] != '\0')
		{
			p = strchr(tmp, '.');
			if (p != NULL)
			{
				n = (p - tmp);
			}
			tmp[n] = ',';
			j++;
		}
		out1 << tmp << endl;
		in >> tmp;
	}
}