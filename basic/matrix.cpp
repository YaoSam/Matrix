#include "matrix.h"
matrix::matrix(unsigned r, unsigned c) :
	data(nullptr), row_p(nullptr), row(r), col(c)
{
	if (row == 0 && col == 0)return;
	data = new double[row*col];
	memset(data, 0, sizeof(double)*row*col);
	row_p = new double*[row];
	re(i, row)
		row_p[i] = data + col*i;
}


matrix::matrix(double *Data, unsigned r, unsigned c) :
	data(nullptr), row_p(nullptr), row(r), col(c)
{
	if (Data == nullptr)return;
	data = new double[row*col];
	row_p = new double*[row];
	memcpy(data, Data, sizeof(double)*r*c);
	re(i, row)
		row_p[i] = data + col*i;
}
					  
matrix::matrix(double  ** Data, unsigned r, unsigned c) :
	data(nullptr), row_p(nullptr), row(r), col(c)
{
	if (row == 0 || col == 0)return;
	data = new double[row*col];
	row_p = new double*[row];
	re(i, row)
	{
		row_p[i] = data + i*col;
		memcpy(row_p[i], Data[i], sizeof(double)*col);
	}
}

matrix::matrix(const matrix& other):
	data(nullptr), row_p(nullptr), row(other.row), col(other.col)
{
	data = new double[row*col];
	memcpy(data, other.data, sizeof(double)*row*col);
	row_p = new double*[row];
	re(i, row)
		row_p[i] = data + col*i;
}

matrix& matrix::operator=(const matrix& other)
{
	if (this == &other)
		return *this;
	release();
	row = other.row;
	col = other.col;
	data = new double[row*col];
	row_p = new double*[row];
	memcpy(data, other.data, sizeof(double)*row*col);
	re(i, row)
		row_p[i] = data + col*i;
	return*this;
}

void matrix::apply_unsafe(unsigned m, unsigned n)
{
	row = m, col = n;
	data = new double[row*col];
	memset(data, 0, sizeof(double)*col*row);
	row_p = new double*[row];
	re(i, row)
		row_p[i] = data + col*i;
}

void matrix::release()
{
	if(data!=nullptr)
	{
		delete[]row_p;
		delete[]data;
	}
	data = nullptr;
	row_p = nullptr;
}

void matrix::ExchangeC(unsigned c1, unsigned c2)const
{
	re(i, row)
		swap(row_p[i], row_p[i]);
}

void matrix::RowAmutiply(unsigned a, double coefficient)const
{
	re(i, col)
		row_p[a][i] *= coefficient;
}

void matrix::RowAplusRowB(unsigned a, unsigned b, double coefficient,unsigned after)const
{
	for (unsigned i = after; i < col; i++)
		row_p[a][i] += row_p[b][i] * coefficient;
}

unsigned matrix::find_MaxInCol(unsigned c, unsigned under)const
{
	unsigned ans = under;
	double current_max = row_p[under][c];
	for (unsigned i = under + 1; i < row; i++)
		if(abs(row_p[i][c])>abs(current_max))
		{
			current_max = row_p[i][c];
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
		row_p[i][j] += other.row_p[i][j];
	return *this;
}

matrix& matrix::operator*=(const matrix& other)
{
	if (other.row != col)
		throw "size is not right!!!";
	double* temp_data= new double[row*col];
	double** temp_row_p = new double*[row];
	re(i, row)
	{
		temp_row_p[i] = temp_data + col*i;
		re(j, other.col)
		{
			temp_row_p[i][j] = 0;
			re(k, col)
				temp_row_p[i][j] += row_p[i][k] * other.row_p[k][j];
		}
	}
	release();
	data = temp_data;
	row_p = temp_row_p;
	col = other.col;
	return *this;
}

matrix matrix::operator+(const matrix& other)const
{
	if (other.col != col || other.row != row)
		throw"sizes are not equal";
	matrix ans(row,col);
	re(i,row)
		re(j, col)
			ans.row_p[i][j] = row_p[i][j] + other.row_p[i][j];
	return ans;
}

matrix matrix::operator*(const matrix& other)const
{
	if (other.row != col)
		throw "size is not right!!!";
	matrix ans(row,other.col);
	re(i,row)
		re(j, other.col)
			re(k, col)
				ans.row_p[i][j] += row_p[i][k] * other.row_p[k][j];
	return ans;
}

matrix& matrix::LU()
{
	unsigned min = (row < col ? row : col) - 1;
	double coefficient = 0;
	re(i,min)
	{
		for (unsigned j = i + 1; j < row; j++)
		{
			coefficient = -row_p[j][i] / row_p[i][i];
			if (coefficient == 0)
				throw "can't be 0";
			RowAplusRowB(j, i, coefficient);
			row_p[j][i] = coefficient;
		}
	}
	return *this;
}

matrix matrix::ChosenLU()//TODO
{
	matrix P(row,row);
	unsigned min = (row < col ? row : col) - 1;
	double coefficient = 0;
	re(i, min)
	{
		for (unsigned j = i + 1; j < row; j++)
		{
			coefficient = -row_p[j][i] / row_p[i][i];
			if (coefficient == 0)
				throw "can't be 0";
			RowAplusRowB(j, i, coefficient);
			row_p[j][i] = coefficient;
		}
	}
	return P;
}


matrix::~matrix()
{
	release();
}

ostream& operator<<(ostream& out, const matrix& me)
{
	re(i, me.row)
	{
		re(j, me.col)
			out << me.row_p[i][j] << " ";
		out << endl;
	}
	return out;
}

istream& operator >> (istream& in, matrix& other)
{
	if (other.row > 0)
		other.release();
	in >> other.row >> other.col;
	if (other.row*other.col == 0)return in;
	other.data = new double[other.row*other.col];
	other.row_p = new double*[other.row];
	re(i,other.row)
	{
		other.row_p[i] = other.data + i*other.col;
		re(j, other.col)
			in >> other.row_p[i][j];
	}
	return in;
}
