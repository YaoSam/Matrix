#include "matrix.h"
matrix::matrix(double *Data, unsigned r, unsigned c):
	data(nullptr), row(r), col(c)
{
	if (Data == nullptr)return;
	data = new double*[row];
	re(i, row)
	{
		data[i] = new double[col];
		memcpy(data[i], Data + i*row, sizeof(double)*col);
	}
}
					  
matrix::matrix(double  ** Data, unsigned r, unsigned c) :
	data(nullptr), row(r), col(c)
{
	if (Data == nullptr)return;
	data = new double*[row];
	re(i, row)
	{
		data[i] = new double[col];
		memcpy(data[i], Data[i], sizeof(double)*col);
	}
}

matrix::matrix(const matrix& other):
	row(other.row),col(other.col),
	data(new double*[other.row])
{
	re(i, row)
	{
		data[i] = new double[other.col];
		memcpy(data[i], other.data[i], sizeof(double)*col);
	}
}

void matrix::del()const
{
	re(i, row)
		delete[] data[i];
	delete[] data;
}

void matrix::ExchangeC(unsigned c1, unsigned c2)const
{
	re(i, row)
		swap(data[i][c1], data[i][c2]);
}

void matrix::RowAmutiply(unsigned a, double coefficient)const
{
	re(i, col)
		data[a][i] *= coefficient;
}

void matrix::RowAplusRowB(unsigned a, unsigned b, double coefficient,unsigned after)const
{
	for (unsigned i = after; i < col; i++)
		data[a][i] += data[b][i] * coefficient;
}

unsigned matrix::find_MaxInCol(unsigned c, unsigned under)const
{
	unsigned ans = under;
	double current_max = data[under][c];
	for (unsigned i = under+1; i < row; i++)
		if(abs(data[i][c])>abs(current_max))
		{
			current_max = data[i][c];
			ans = i;
		}
	return ans;
}

matrix& matrix::operator+=(const matrix& other)
{
	if (other.col != col || other.row != row)
		throw"sizes are not equal";
	re(i, row)
		re(j, col)
		data[i][j] += other.data[i][j];
	return *this;
}

matrix& matrix::operator*=(const matrix& other)
{
	double** temp_data;
	if (other.row != col)
		throw "size is not right!!!";
	temp_data = new double*[row];
	re(i, row)
	{
		temp_data[i] = new double[other.col];
		re(j, other.col)
		{
			temp_data[i][j] = 0;
			re(k, col)
				temp_data[i][j] += data[i][k] * other.data[k][j];
		}
	}
	del();
	data = temp_data;
	col = other.col;
	return *this;
}


matrix matrix::operator*(const matrix& other)const
{
	matrix ans;
	if (other.row != col)
		throw "size is not right!!!";
	ans.row = row;
	ans.col = other.col;
	ans.data = new double*[row];
	re(i,row)
	{
		ans.data[i] = new double[other.col];
		re(j, other.col)
		{
			ans.data[i][j] = 0;
			re(k, col)
				ans.data[i][j] += data[i][k] * other.data[k][j];
		}
	}
	return ans;
}

matrix matrix::LU()
{
	unsigned min = (row < col ? row : col) - 1;
	double coefficient = 0;
	re(i,min)
	{
		for (unsigned j = i + 1; j < row; j++)
		{
			coefficient = -data[j][i] / data[i][i];
			RowAplusRowB(j, i, coefficient);
			data[j][i] = coefficient;
		}
	}
	return matrix();
}


matrix::~matrix()
{
	del();
	data = nullptr;
}

ostream& operator<<(ostream& out, const matrix& me)
{
	re(i, me.row)
	{
		re(j, me.col)
			out << me.data[i][j] << " ";
		out << endl;
	}
	return out;
}

istream& operator >> (istream& in, matrix& other)
{
	if (other.row > 0)
		other.del();
	in >> other.row >> other.col;
	other.data = new double*[other.row];
	re(i,other.row)
	{
		other.data[i] = new double[other.col];
		re(j, other.col)
			in >> other.data[i][j];
	}
	return in;
}
