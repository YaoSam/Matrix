#pragma once
#include <iostream>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#undef Template
#define Template(return_type)  \
	template<class deri_matrix, class value_type> \
	return_type bas_matrix<deri_matrix, value_type>:: 


template<class deri_matrix, class value_type>
class bas_matrix
{
protected:
	typedef value_type T;
	T*data;
	T**row_p;
	unsigned row, col;
	void ExchangeR(unsigned r1, unsigned r2)const//交换r1,r1行
	{
		swap(row_p[r1], row_p[r2]);
	}
	void ExchangeC(unsigned c1, unsigned c2)const;//交换c1,c2列
	void RowAplusRowB(unsigned a, unsigned b, T coefficient = 1, unsigned after = 0)const;//a行+=b行*coefficient
	void RowAmutiply(unsigned a, T coefficient = 0)const;
	unsigned find_MaxInCol(unsigned c, unsigned under = 0)const;//从under开始找某列的最大值。
	void release();
	void apply_unsafe(unsigned m, unsigned n);//change the shape.
	void clear()const//make all zero.
	{
		re(i, row)
			memset(row_p[i], 0, sizeof(T)*col);
	}
	deri_matrix static one(unsigned n);
public:
	bas_matrix(unsigned r, unsigned c);
	bas_matrix(T **Data = nullptr, unsigned r = 0, unsigned c = 0);
	bas_matrix(T *Data, unsigned r = 0, unsigned c = 0);
	bas_matrix(const bas_matrix& other);
	deri_matrix& operator=(const deri_matrix &other);
	T *const operator[](unsigned r) { return row_p[r]; }
	const T*const operator[](unsigned r)const { return row_p[r]; }
	friend ostream& operator<<(ostream& out, const deri_matrix& me)
	{
		re(i, me.row)
		{
			re(j, me.col)
				out << me.row_p[i][j] << " ";
			out << endl;
		}
		return out;
	}
	friend istream& operator >> (istream& in, deri_matrix& me)
	{
		if (me.row > 0)
			me.release();
		in >> me.row >> me.col;
		if (me.row*me.col == 0)return in;
		me.data = new T[me.row*me.col];
		me.row_p = new T*[me.row];
		re(i, me.row)
		{
			me.row_p[i] = me.data + i*me.col;
			re(j, me.col)
				in >> me.row_p[i][j];
		}
		return in;
	}

	deri_matrix& operator+=(const deri_matrix& other);
	deri_matrix& operator*=(const deri_matrix& other);
	deri_matrix operator+(const deri_matrix& other)const;
	deri_matrix operator*(const deri_matrix& other)const;
	deri_matrix& LU();
	deri_matrix ChosenLU();
	deri_matrix solve(const deri_matrix& input)const;
	deri_matrix LU_solve(const deri_matrix& input)const;//当矩阵已经进行LU分解时直接用来求解。
	deri_matrix inverse()const;//基于ChosenLU()的求逆。
	virtual ~bas_matrix();
};

Template(void) ExchangeC(unsigned c1, unsigned c2) const
{
	re(i, row)
		swap(row_p[i], row_p[i]);
}

Template(void) RowAplusRowB(unsigned a, unsigned b, T coefficient, unsigned after) const
{
	for (unsigned i = after; i < col; i++)
		row_p[a][i] += row_p[b][i] * coefficient;
}

Template(void) RowAmutiply(unsigned a, T coefficient) const
{
	re(i, col)
		row_p[a][i] *= coefficient;
}

Template(unsigned) find_MaxInCol(unsigned c, unsigned under) const//必须定义abs
{
	unsigned ans = under;
	T current_max = row_p[under][c];
	for (unsigned i = under + 1; i < row; i++)
		if (abs(row_p[i][c])>abs(current_max))
		{
			current_max = row_p[i][c];
			ans = i;
		}
	return ans;
}

Template(void)release()
{
	if (data != nullptr)
	{
		delete[]row_p;
		delete[]data;
	}
	data = nullptr;
	row_p = nullptr;
}

Template(void) apply_unsafe(unsigned m, unsigned n)
{
	row = m, col = n;
	data = new T[row*col];
	memset(data, 0, sizeof(T)*col*row);
	row_p = new T*[row];
	re(i, row)
		row_p[i] = data + col*i;
}

Template(deri_matrix) one(unsigned n)
{
	deri_matrix ans(n, n);
	re(i, n)
		ans.row_p[i][i] = 1;
	return ans;
}

Template( ) bas_matrix(unsigned r, unsigned c):
	data(nullptr), row_p(nullptr), row(r), col(c)
{
	if (row == 0 && col == 0)return;
	data = new T[row*col];
	memset(data, 0, sizeof(T)*row*col);
	row_p = new T*[row];
	re(i, row)
		row_p[i] = data + col*i;
}

Template( ) bas_matrix(T ** Data, unsigned r, unsigned c) :
	data(nullptr), row_p(nullptr), row(r), col(c)
{
	if (row == 0 || col == 0)return;
	data = new T[row*col];
	row_p = new T*[row];
	re(i, row)
	{
		row_p[i] = data + i*col;
		memcpy(row_p[i], Data[i], sizeof(T)*row);
	}
}

Template( ) bas_matrix(T * Data, unsigned r, unsigned c) :
	data(nullptr), row_p(nullptr), row(r), col(c)
{
	if (Data == nullptr)return;
	data = new T[row*col];
	row_p = new T*[row];
	memcpy(data, Data, sizeof(T)*r*c);
	re(i, row)
		row_p[i] = data + col*i;
}

Template( ) bas_matrix(const bas_matrix & other) :
	data(nullptr), row_p(nullptr), row(other.row), col(other.col)
{
	data = new T[row*col];
	row_p = new T*[row];
	memcpy(data, other.data, sizeof(T)*row*col);
	re(i, row)//整体位移。
		row_p[i] = data + (other.row_p[i] - other.data);
}

Template(deri_matrix &) operator=(const deri_matrix & other)
{
	if (this == &other)
		return *this;
	if (row != other.row || col != other.col)//形状相同的时候直接复制即可。
	{
		release();
		row = other.row;
		col = other.col;
		data = new T[row*col];
		row_p = new T*[row];
	}
	memcpy(data, other.data, sizeof(T)*row*col);
	re(i, row)
		row_p[i] = data + (other.row_p[i] - other.data);
	return static_cast<deri_matrix&>(*this);
}

Template(deri_matrix &) operator+=(const deri_matrix & other)
{
	if (other.col != col || other.row != row)
		throw"sizes are not equal";
	re(i, row)
		re(j, col)
		row_p[i][j] += other.row_p[i][j];
	return static_cast<deri_matrix&>(*this);
}

Template(deri_matrix &) operator*=(const deri_matrix & other)
{
	if (other.row != col)
		throw "size is not right!!!";
	T* temp_data = new T[row*col];
	T** temp_row_p = new T*[row];
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
	return static_cast<deri_matrix&>(*this);
}

Template(deri_matrix) operator+(const deri_matrix & other) const
{
	if (other.col != col || other.row != row)
		throw"sizes are not equal";
	deri_matrix ans(row, col);
	re(i, row)
		re(j, col)
		ans.row_p[i][j] = row_p[i][j] + other.row_p[i][j];
	return ans;
}

Template(deri_matrix) operator*(const deri_matrix & other) const
{
	if (other.row != col)
		throw "size is not right!!!";
	deri_matrix ans(row, other.col);
	re(i, row)
		re(j, other.col)
			re(k, col)
				ans.row_p[i][j] += row_p[i][k] * other.row_p[k][j];
	return ans;
}

Template(deri_matrix &) LU()//必须定义除法
{
	unsigned min = (row < col ? row : col) - 1;//提前-1.最后一行不用处理。
	T coefficient = 0;
	re(i, min)
	{
		for (unsigned j = i + 1; j < row; j++)
		{
			if (row_p[i][i] == 0)
				throw "can't be 0";
			if (row_p[j][i] == 0)
				continue;
			coefficient = 0 - row_p[j][i] / row_p[i][i];
			RowAplusRowB(j, i, coefficient, i);
			row_p[j][i] = 0-coefficient;
		}
	}
	return static_cast<deri_matrix&>(*this);
}

Template(deri_matrix) ChosenLU()
{
	deri_matrix P(row, row);
	re(i, row)
		P.row_p[i][i] = 1;
	unsigned min = (row < col ? row : col) - 1, max = 0;//max:最大的行的序号。
	T coefficient = 0;
	re(i, min)
		for (unsigned j = i + 1; j < row; j++)
		{
			max = find_MaxInCol(i, i);
			if (max != i)
			{
				P.ExchangeR(i, max);
				ExchangeR(i, max);
			}
			if (row_p[i][i] == 0)
				throw "can't be 0";
			if (row_p[j][i] == 0)
				continue;
			coefficient = 0 - row_p[j][i] / row_p[i][i];
			RowAplusRowB(j, i, coefficient, i);
			row_p[j][i] = 0-coefficient;
		}
	return P;
}

Template(deri_matrix)LU_solve(const deri_matrix & input) const
{
	if (input.row != row)
		throw "error";
	deri_matrix ans(input.row, 1);
	T temp = 0;//先累加，减少误差。
	re(i, row)
	{
		for (unsigned k = 0; k + 1 <= i; k++)
			temp += row_p[i][k] * ans.data[k];
		ans.data[i] = input.data[i] - temp;
		temp = 0;//temp不能忘了重置。
	}
	for (int i = row - 1; i >= 0; i--, temp = 0)
	{
		for (unsigned k = i + 1; k < row; k++)
			temp += row_p[i][k] * ans.data[k];
		(ans.data[i] -= temp) /= row_p[i][i];
	}
	return ans;
}

Template(deri_matrix) solve(const deri_matrix & input) const
{
	if (input.row != row)
		throw "error";
	deri_matrix ans(input.row, 1), me(static_cast<const deri_matrix&>(*this));
	deri_matrix P(me.ChosenLU());
	deri_matrix b(P*input);
	T temp = 0;//先累加，减少误差。
	re(i, row)
	{
		for (unsigned k = 0; k + 1 <= i; k++)
			temp += me.row_p[i][k] * ans.data[k];
		ans.data[i] = b.data[i] - temp;
		temp = 0;//temp不能忘了重置。
	}
	for (int i = row - 1; i >= 0; i--, temp = 0)
	{
		for (unsigned k = i + 1; k < row; k++)
			temp += me.row_p[i][k] * ans.data[k];
		(ans.data[i] -= temp) /= me.row_p[i][i];
	}
	return ans;
}
Template(deri_matrix) inverse() const
{
	if (col != row)
		throw "行列不同，无法求逆。";
	deri_matrix ans(row, row), me(static_cast<const deri_matrix&>(*this));
	deri_matrix b(me.ChosenLU());
	T temp = 0;//先累加，减少误差。
	re(j,row)
	{
		re(i, row)
		{
			for (unsigned k = 0; k + 1 <= i; k++)
				temp += me.row_p[i][k] * ans.row_p[k][j];
			ans.row_p[i][j] = b.row_p[i][j] - temp;
			temp = 0;//temp不能忘了重置。
		}
		for (int i = row - 1; i >= 0; i--, temp = 0)
		{
			for (unsigned k = i + 1; k < row; k++)
				temp += me.row_p[i][k] * ans.row_p[k][j];
			(ans.row_p[i][j] -= temp) /= me.row_p[i][i];
		}
	}
	return ans;
}

Template()~bas_matrix()
{
	release();
}

template<class value_type>
class Matrix:public bas_matrix<Matrix<value_type>,value_type>
{
	typedef value_type T;
public:
	Matrix(unsigned r, unsigned c) :bas_matrix(r, c) {}
	Matrix(T **Data = nullptr, unsigned r = 0, unsigned c = 0) :bas_matrix(Data, r, c) {}
	Matrix(T *Data, unsigned r = 0, unsigned c = 0) :bas_matrix(Data, r, c) {}
	Matrix(const Matrix& other) :bas_matrix(other) {}
	~Matrix() {};
};