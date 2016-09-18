#include "matrix.h"
matrix::matrix(unsigned r, unsigned c) :bas_matrix(r,c){}

matrix::matrix(double *Data, unsigned r, unsigned c) :bas_matrix(Data,r,c){}
					  
matrix::matrix(double  ** Data, unsigned r, unsigned c) :bas_matrix(Data,r,c){}

matrix::matrix(const matrix& other):bas_matrix(other){}

