#include "stdafx.h"
#include <iostream>
using namespace std;

struct st
{
	char X;
	st *ptr;
};
int add(st *&top, char x);
int pop(st *&top);
void out(st *top);
int main()
{
	st *top1 = NULL;
	st *top2 = NULL;
	int i;
	char vr[100], y, vr2[101]; double V[101];
	cout << "Enter a notation: ";
	cin >> vr;
	add(top2, '=');
	for (i = 0; vr[i] != '\0'; i++)
	{
		switch (vr[i])
		{
		case '*': {
			if (top2->X == '='||top2->X=='('|| top2->X == '+' || top2->X == '-')
				add(top2, vr[i]);
			if (top2->X == '/')
			{
				add(top1, pop(top2));
				add(top2, vr[i]);
			}
		}break;
		case '/': {
			if (top2->X == '='||top2->X=='('||top2->X=='+'||top2->X=='-')
				add(top2, vr[i]);
			if (top2->X == '*')
			{
				add(top1, pop(top2));
				add(top2, vr[i]);
			}
		}break;
		case '+': {
			if (top2->X == '(' || top2->X=='='|| top2->X == '+')
				add(top2, vr[i]);
			if (top2->X == '*' || top2->X == '/'||top2->X == '-')
			{
				add(top1, pop(top2));
				add(top2, vr[i]);
			}
			}break;
		case '-': {
			if (top2->X == '(' || top2->X == '='||top2->X=='-')
			add(top2, vr[i]);
			if (top2->X == '*' || top2->X == '/'|| top2->X == '+')
			{
				add(top1, pop(top2));
				add(top2, vr[i]);
			}
		}break;
		case '(': {add(top2, vr[i]); }break;
		case ')': {
			while (top2->X !='(')
				add(top1, pop(top2));
			pop(top2);
		}break;
		default: {
			add(top1, vr[i]);
		}
}
	}
	while(top2)
	add(top1, pop(top2));
	st *head = NULL;
	while(top1)
	add(head, pop(top1));
	cout << "RPN: ";
	out(head);
	out(top2);
	for (i = 0; head; i++)
	{
		vr2[i] = pop(head);
	}
	int n = i;
	for (i = 0; i < n; i++)
		cout << vr2[i]<<"   ";
	cout << endl;
	for (i = 0; i < n; i++)
	{
		if (vr2[i] == '*' || vr2[i] == '/' || vr2[i] == '+' || vr2[i] == '-' || vr2[i]=='=')
			V[i] = 0;
		else
		{
			cout << vr2[i] << " = "; cin >> V[i];
		}
	}
	for (i = 0; i < n; i++)
	{
		switch(vr2[i])
		{
		case '*': {V[i - 2] = V[i - 2] * V[i - 1];
			for (int j = i - 1; j < n; j++)
			{
				if (V[j + 2] != 0) V[j] = V[j + 2]; 
				else V[j] = V[j + 1];
				vr2[j] = vr2[j + 2];
			} i = 0;
		}break;
		case '/': {V[i - 2] = V[i - 2] / V[i - 1];
			for (int j = i - 1; j < n; j++)
			{
				if (V[j + 2] != 0) V[j] = V[j + 2];
				else V[j] = V[j + 1];
				vr2[j] = vr2[j + 2];
			} i = 0;
		}break;
		case '+': {V[i - 2] = V[i - 2] + V[i - 1];
			for (int j = i - 1; j < n; j++)
			{
				if (V[j + 2] != 0) V[j] = V[j + 2]; 
				else V[j] = V[j + 1];
				vr2[j] = vr2[j + 2]; 
			} i = 0;
		}break;
		case '-': {V[i - 2] = V[i - 2] - V[i - 1];
			for (int j = i - 1; j < n; j++)
			{
				if (V[j + 2] != 0) V[j] = V[j + 2];
				else V[j] = V[j + 1];
				vr2[j] = vr2[j + 2];
			} i = 0;
		}break;
		}
	}
		cout <<"Answer:  "<< V[0] << endl;
    return 0;
}
int add(st *&top, char x)
{
	st* pv;
	pv = new st;
	pv->X = x;
	pv->ptr = top;
	top = pv;
	return 0;
}
int pop(st *&top)
{
	st *pv;
	char temp;
	temp = top->X;
	pv = top;
	top = top->ptr;
	delete pv;
	return temp;
}
void out(st *top)
{
	while (top)
	{
		cout << top->X << "  ";
		top = top->ptr;
	}
	cout << endl;
}