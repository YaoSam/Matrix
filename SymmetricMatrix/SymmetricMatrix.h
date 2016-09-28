#pragma once
#include "../basic/bas_matrix.h"


template <class T>
class sys_matrix:public bas_matrix<sys_matrix<T>,T>
{
	friend class bas_matrix<sys_matrix<T>, T>;
	sys_matrix(unsigned r, unsigned c):bas_matrix(r,c){}//默认是上三角输入。
public:
	using bas_matrix<sys_matrix<T>, T>::data;
	using bas_matrix<sys_matrix<T>, T>::row_p;
	using bas_matrix<sys_matrix<T>, T>::row;
	using bas_matrix<sys_matrix<T>, T>::col;
	sys_matrix(const T* data, unsigned n);//默认是上三角输入。
	sys_matrix(unsigned n=0) :bas_matrix(n, n){}
	sys_matrix& Cholesky();
};
template <class T>
sys_matrix<T>::sys_matrix(const T* data, unsigned n):bas_matrix(n,n)
{
	for (int i = 0; i < n; i++)
	{
		row_p[i][i] = data[(i)*(2 * n - i + 1) / 2];
		re(j,n-i-1)
		{
			row_p[i + j + 1][i] =
			row_p[i][i + j + 1] = 
				data[(i)*(2 * n - i + 1) / 2 + j + 1];
		}
	}
}

template<class T>
sys_matrix<T>& sys_matrix<T>::Cholesky()
{
	vector<T> v(col);
	sys_matrix<T> ans(*this);
	T temp=T(0);
	re(j,col)
	{
		re(i,j)
		{
			v[i] = row_p[j][i] * row_p[i][i];
			temp += row_p[j][i] * v[i];
		}
		row_p[j][j] -= temp;
		temp = T(0);
		for (int i = j + 1; i < row; i++, temp = T(0))
		{
			for (int k = 0; k < j; k++)
				temp += row_p[i][k] * v[k];
			row_p[i][j] = (row_p[i][j] - temp) / row_p[j][j];
		}
	}
	return (*this);
}
