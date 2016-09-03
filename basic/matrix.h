#pragma once

#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#include <iostream>
using namespace std;
class matrix
{
	double** data;
	unsigned row, col;
public:
	void ExchangeR(unsigned r1, unsigned r2)const//����r1,r1��
	{
		swap(data[r1], data[r2]);
	}
	void ExchangeC(unsigned c1, unsigned c2)const;//����c1,c2��
	void RowAplusRowB(unsigned a, unsigned b, double coefficient = 1, unsigned after = 0)const;//a��+=b��*coefficient
	void RowAmutiply(unsigned a, double coefficient = 0)const;
	unsigned find_MaxInCol(unsigned c, unsigned under = 0)const;//��under��ʼ��ĳ�е����ֵ��
	void del()const;
public:
	matrix(double **Data = nullptr, unsigned r = 0, unsigned c = 0);
	matrix(double *Data, unsigned r = 0, unsigned c = 0);
	matrix(const matrix& other);
	matrix& operator=(const matrix &other);
	friend ostream& operator<<(ostream& out, const matrix& me);
	friend istream& operator >> (istream& in, matrix& me);
	matrix& operator+=(const matrix& other);
	matrix& operator*=(const matrix& other);
	matrix operator+(const matrix& other)const;
	matrix operator*(const matrix& other)const;
	matrix& LU();//return U;
	~matrix();
};

ostream& operator<<(ostream& out, const matrix& me);
istream& operator >> (istream& in, matrix& me);