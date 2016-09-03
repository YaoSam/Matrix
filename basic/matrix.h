#pragma once

#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#include <iostream>
using namespace std;
class matrix
{
	double** data;
	unsigned row, col;
	void ExchangeR(unsigned r1, unsigned r2)const
	{
		swap(data[r1], data[r2]);
	}
	void ExchangeC(unsigned c1, unsigned c2);
	void RowAplusRowB(unsigned a, unsigned b, double coefficient = 1);
	void RowAmutiply(unsigned a, double coefficient = 1);
	void del()const;
public:
	matrix(double **Data = nullptr, unsigned r = 0, unsigned c = 0);
	matrix(double *Data, unsigned r = 0, unsigned c = 0);
	matrix(const matrix& other);
	friend ostream& operator<<(ostream& out, const matrix& me);
	matrix& operator+=(const matrix& other);
	matrix& operator*=(const matrix& other);
	matrix operator*(const matrix& other)const;
	~matrix();
};

ostream& operator<<(ostream& out, const matrix& me);
