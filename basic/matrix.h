#pragma once
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#include <iostream>
#include "bas_matrix.h"
using namespace std;

class matrix:public bas_matrix<matrix,double>
{
public:
	matrix(unsigned r, unsigned c);
	matrix(double **Data = nullptr, unsigned r = 0, unsigned c = 0);
	matrix(double *Data, unsigned r = 0, unsigned c = 0);
	matrix(const matrix& other);
	~matrix(){};
};
