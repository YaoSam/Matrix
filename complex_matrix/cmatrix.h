#pragma once
#include "complex.h"
#include "../basic/bas_matrix.h"
class cmatrix :public bas_matrix<cmatrix, complex>
{
public:
	cmatrix(unsigned r, unsigned c):bas_matrix(r,c){}
	cmatrix(complex **Data = nullptr, unsigned r = 0, unsigned c = 0):bas_matrix(Data,r,c){}
	cmatrix(complex *Data, unsigned r = 0, unsigned c = 0):bas_matrix(Data,r,c){}
	cmatrix(const cmatrix& other):bas_matrix(other){}
	~cmatrix() {};
};
