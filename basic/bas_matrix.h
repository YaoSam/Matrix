#pragma once
#include <iostream>
#include <vector>
#include<thread>
#include <windows.h>
#include <iomanip>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#undef Template
#define Template(return_type)  \
	template<class deri_matrix, class value_type> \
	return_type bas_matrix<deri_matrix, value_type>:: 
inline unsigned process_num()
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
}
extern unsigned thread_num;

template<class T> class sys_matrix;
template<class deri_matrix, class value_type>
class bas_matrix
{
private:

protected:
	typedef value_type T;
	T*data;
	T**row_p;
	unsigned row, col;
	void static dot_product(T &ans, T *  a, T** b, unsigned c, unsigned num);
	void static dot_product(T &ans, T ** a,        unsigned ac, T** b, unsigned bc, unsigned num);
	void static dot_product(T &ans, T *  a, T* b,  unsigned num);
	void static two_norm   (T &ans, T *  a,        unsigned num);
	void static two_norm   (T &ans, T ** a,        unsigned c, unsigned num);
	void ExchangeR		  (unsigned r1, unsigned r2)const//交换r1,r1行
	{
		swap(row_p[r1], row_p[r2]);
	}
	void ExchangeC        (unsigned c1, unsigned c2)const;//交换c1,c2列
	void RowAplusRowB     (unsigned a, unsigned b, T coefficient = 1, unsigned after = 0)const;//a行+=b行*coefficient
	void RowAmutiply      (unsigned a, T coefficient = 0)const;
	unsigned find_MaxInCol(unsigned c, unsigned under = 0)const;//从under开始找某列的最大值。
	void release          ();
	void apply_unsafe     (unsigned m, unsigned n);//change the shape.
	void clear()const//make all zero.
	{
		re(i, row)
			memset(row_p[i], 0, sizeof(T)*col);
	}
public:
	deri_matrix static one(unsigned n);
	bas_matrix                (unsigned r, unsigned c);
	bas_matrix                (T **Data = nullptr, unsigned r = 0, unsigned c = 0);
	bas_matrix                (const bas_matrix& other);
	bas_matrix                (bas_matrix&&other)noexcept
	{
		data = other.data;
		row_p = other.row_p;
		row = other.row;
		col = other.col;
		other.data = nullptr;
		other.row_p = nullptr;
		other.row = other.col = 0;
	}
	deri_matrix& operator=    (const deri_matrix & other);
	deri_matrix& operator=    (deri_matrix&& other)noexcept
	{
		if (this == &other)return *this;
		if (data)	delete[]data;
		if (row_p)	delete[]row_p;
		data = other.data;
		row_p = other.row_p;
		row = other.row;
		col = other.col;
		other.data = nullptr;
		other.row_p = nullptr;
		other.row = other.col = 0;
		return *this;
	}
	T *const operator[]       (unsigned r)      { return row_p[r]; }
	const T*const operator[]  (unsigned r)const { return row_p[r]; }
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
		me.data  = new T[me.row*me.col];
		me.row_p = new T*[me.row];
		re(i, me.row)
		{
			me.row_p[i] = me.data + i*me.col;
			re(j, me.col)
				in >> me.row_p[i][j];
		}
		return in;
	}
	unsigned Row           ()const { return row; }
	unsigned Col           ()const { return col; }
	deri_matrix& operator+=(const deri_matrix& other);
	deri_matrix& operator*=(const deri_matrix& other);
	deri_matrix  operator+ (const deri_matrix& other)const;
	deri_matrix  operator- (const deri_matrix& other)const;
	deri_matrix  operator* (const deri_matrix& other)const;
	bool         operator==(const deri_matrix& other)const;
	deri_matrix transform  ()const;
	deri_matrix& LU        ();
	deri_matrix ChosenLU   ();
	deri_matrix solve      (const deri_matrix& input)const;
	deri_matrix LU_solve   (const deri_matrix& input)const;//当矩阵已经进行LU分解时直接用来求解。
	deri_matrix inverse    ()const;//基于ChosenLU()的求逆。
	void QR                (deri_matrix& Q,deri_matrix& R)const;
	static void House      (const deri_matrix& mat, unsigned r, unsigned c,T* ans);
	void qr                (deri_matrix& Q, deri_matrix& R)const;
	deri_matrix qr         (const deri_matrix& b)const;
	virtual ~bas_matrix();
};

Template(void) dot_product(T(&ans), T* a, T** b, unsigned c, unsigned num)
{
	ans = T();
	re(i, num)
		ans += a[i] * b[i][c];
}

Template(void) dot_product(T(&ans), T** a, unsigned ac, T** b, unsigned bc, unsigned num)
{
	ans = T();
	re(i, num)
		ans += a[i][ac] * b[i][bc];
}

Template(void) dot_product(T(&ans), T* a, T* b, unsigned num)
{
	ans = T();
	re(i, num)
		ans += a[i] * b[i];
}

Template(void) two_norm(T & ans, T *a, unsigned num)
{
	ans = T();
	re(i, num)
		ans += a[i] * a[i];
	ans=sqrt(ans);
}

Template(void) two_norm(T & ans, T **a, unsigned c, unsigned num)
{
	ans = T();
	re(i, num)
		ans += a[i][c] * a[i][c];
	ans = sqrt(ans);
}

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
template<class T>
bool abs_cmp(const T& a,const T&b)
{
	return abs(a) > abs(b);
}
Template(unsigned) find_MaxInCol(unsigned c, unsigned under) const//必须定义abs
{
	unsigned ans = under;
	T current_max = row_p[under][c];
	for (unsigned i = under + 1; i < row; i++)
		if(abs_cmp(row_p[i][c], current_max))
		//if (abs(row_p[i][c])>abs(current_max))
		{
			current_max = row_p[i][c];
			ans         = i;
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
}

Template(void) apply_unsafe(unsigned m, unsigned n)
{
	row = m, col = n;
	data = new T[row*col];
	re(i, row*col)
		data[i] = T();
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

Template() bas_matrix(unsigned r, unsigned c):
	data(nullptr), row_p(nullptr), row(r), col(c)
{
	if (row == 0 && col == 0)return;
	data = new T[row*col];
	re(i, row*col)data[i] = T();
	row_p = new T*[row];
	re(i, row)
		row_p[i] = data + col*i;
}

Template() bas_matrix(T ** Data, unsigned r, unsigned c) :
	data(nullptr), row_p(nullptr), row(r), col(c)
{
	if (row == 0 || col == 0)return;
	data = new T[row*col];
	row_p = new T*[row];
	re(i, row)
	{
		row_p[i] = data + i*col;
		re(j, col)
			row_p[i][j] = Data[i][j];
		//memcpy(row_p[i], Data[i], sizeof(T)*row);
	}
}

Template() bas_matrix(const bas_matrix & other) :
	data(nullptr), row_p(nullptr), row(other.row), col(other.col)
{
	if (row == 0 || col == 0)
		return;
	data = new T[row*col];
	row_p = new T*[row];
	re(i, row*col)
		data[i] = other.data[i];
	//memcpy(data, other.data, sizeof(T)*row*col);
	re(i, row)//整体位移。
		row_p[i] = data + (other.row_p[i] - other.data);
}

Template(deri_matrix &) operator=(const deri_matrix & other)
{
	if (this == &other)
		return static_cast<deri_matrix&>(*this);
	if (row != other.row || col != other.col)//形状相同的时候直接复制即可。
	{
		release();
		row = other.row;
		col = other.col;
		if(row!=0&&col!=0)
		{
			data  = new T[row*col];
			row_p = new T*[row];
		}
	}
	//memcpy(data, other.data, sizeof(T)*row*col);
	re(i, row*col)
		data[i]  = other.data[i];
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
	T*  temp_data     = new T[row*other.col];
	T** temp_row_p    = new T*[row];
	re(i,row)
		temp_row_p[i] = temp_data + other.col*i;
	//多线程
	vector<thread> Thread;
	const unsigned &n = thread_num;
	re(i,thread_num)
		Thread.push_back(thread([this,&other,temp_row_p,temp_data,i,n]()
	{
		for (unsigned j = i; j < row; j += n)
			re(k, other.col)
				dot_product(temp_row_p[j][k], row_p[j], other.row_p, k, col);
				//re(l, col)
					//temp_row_p[j][k] = row_p[j][l] * other.row_p[l][k];
	}));
	for (auto& i : Thread)
		i.join();
	release();
	data  = temp_data;
	row_p = temp_row_p;
	col   = other.col;
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
Template(deri_matrix) operator-(const deri_matrix & other) const
{
	if (other.col != col || other.row != row)
		throw"sizes are not equal";
	deri_matrix ans(row, col);
	re(i, row)
		re(j, col)
		ans.row_p[i][j] = row_p[i][j] - other.row_p[i][j];
	return ans;
}

Template(deri_matrix) operator*(const deri_matrix & other) const
{
	if (other.row != col)
		throw "size is not right!!!";
	deri_matrix ans(row, other.col);
	vector<thread> Thread;
	const unsigned &n = thread_num;
	re(i, thread_num)
		Thread.push_back(thread([this, &other,&ans, i, n]()
	{
		for (int j = i; j < row; j += n)
		{
			re(k, other.col)
				dot_product(ans.row_p[j][k], row_p[j], other.row_p, k, col);
				//re(l, col)
				//ans.row_p[j][k] += row_p[j][l] * other.row_p[l][k];
		}
	}));
	for (auto& i : Thread)
		i.join();
	return ans;
}

Template(bool) operator==(const deri_matrix& other)const
{
	if (other.row != row || col != other.col)
		return false;
	re(i,row)
		re(j,col)
		if (other.row_p[i][j] != row_p[i][j])
			return false;
	return true;
}

Template(deri_matrix &) LU()//必须定义除法
{
	unsigned min = (row < col ? row : col) - 1;//提前-1.最后一行不用处理。
	T coefficient = T(0);
	re(i, min)
	{
		if (row_p[i][i] == T(0))
			throw "can't be 0";
		for (unsigned j = i + 1; j < row; j++)
		{
			if (row_p[j][i] == T(0))
				continue;
			coefficient = T(0) - row_p[j][i] / row_p[i][i];
			RowAplusRowB(j, i, coefficient, i);
			row_p[j][i] = T(0) - coefficient;
		}
	}
	return static_cast<deri_matrix&>(*this);
}

Template(deri_matrix) ChosenLU()
{
	deri_matrix P(row, row);
	re(i, row)
		P.row_p[i][i] = T(1);
	unsigned min = (row < col ? row : col) - 1, max = 0;//max:最大的行的序号。
	T coefficient = 0;
	re(i, min)
	{
		//相对于LU多了这一部分。
		max = find_MaxInCol(i, i);
		if (max != i)
		{
			P.ExchangeR(i, max);
			ExchangeR(i, max);
		}
		if (row_p[i][i] == T(0))
			throw "can't be 0";
		for (unsigned j = i + 1; j < row; j++)
		{
			if (row_p[j][i] == T(0))
				continue;
			coefficient = T(0) - row_p[j][i] / row_p[i][i];
			RowAplusRowB(j, i, coefficient, i);
			row_p[j][i] = T(0) - coefficient;
		}
	}
	return P;
}

Template(deri_matrix) LU_solve(const deri_matrix & input) const
{
	if (input.row != row||row==0||col==0)
		throw "error";
	deri_matrix ans(input.row, 1);
	T temp = 0;//先累加，减少误差。
	re(i, row)
	{
		dot_product(temp, row_p[i], ans.data, i);
		//for (unsigned k = 0; k < i; k++)
			//temp += row_p[i][k] * ans.data[k];
		ans.data[i] = input.data[i] - temp;
		//temp        = T();//temp不能忘了重置。
	}
	for (int i = row - 1; i >= 0; i--, temp = T())
	{
		dot_product(temp, row_p[i] + i + 1, ans.data + i + 1, row - i - 1);
		//for (unsigned k = i + 1; k < row; k++)
			//temp += row_p[i][k] * ans.data[k];
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
		dot_product(temp, me.row_p[i], ans.data, i);
		//temp = T(0);
		//for (unsigned k = 0; k + 1 <= i; k++)
			//temp += me.row_p[i][k] * ans.data[k];
		ans.data[i] = b.data[i] - temp;
	}
	for (int i = row - 1; i >= 0; i--)
	{
		dot_product(temp, me.row_p[i] + i + 1, ans.data + i + 1, row - i - 1);
		//temp = T(0);
		//for (unsigned k = i + 1; k < row; k++)
			//temp += me.row_p[i][k] * ans.data[k];
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
	unsigned & n = thread_num;
	vector<thread> Thread;
	re(thread_i,thread_num)
	Thread.push_back(thread([this,thread_i,n,&ans,&me,&b]()
	{
		T temp = T();//先累加，减少误差。
		for (int j = thread_i; j < row; j += n)
		{
			re(i, row)
			{
				dot_product(temp, me.row_p[i], ans.row_p, j, i);
				//temp = T();
				//for (unsigned k = 0; k + 1 <= i; k++)
				//	temp += me.row_p[i][k] * ans.row_p[k][j];
				ans.row_p[i][j] = b.row_p[i][j] - temp;
			}
			for (int i = row - 1; i >= 0; i--)
			{
				dot_product(temp, me.row_p[i] + i + 1, ans.row_p + i + 1, j, row - i - 1);
				//temp = T();
				//for (unsigned k = i + 1; k < row; k++)
				//	temp += me.row_p[i][k] * ans.row_p[k][j];
				(ans.row_p[i][j] -= temp) /= me.row_p[i][i];
			}
		}
	}));
	for (auto& i : Thread)
		i.join();
	return ans;
}

Template(void) QR(deri_matrix& Q, deri_matrix& R)const
{
	if (&Q == &R)throw"Q，R不能用同一个矩阵啊……";
	Q = static_cast<const deri_matrix&>(*this);
	R = deri_matrix(col, col);
	T temp = T();
	re(i,col)
	{
		re(k, row)
			Q.row_p[k][i] = row_p[k][i];
		for (int j = 0; j  < i; j++)
		{
			dot_product(R.row_p[j][i], Q.row_p, j, row_p, i, row);
			//re(k, row)
				//R.row_p[j][i] += Q.row_p[k][j] * row_p[k][i];
			re(k,row)
				Q.row_p[k][i] -= R.row_p[j][i] * Q.row_p[k][j];
		}

		two_norm(R.row_p[i][i], Q.row_p, i, row);
		//re(k, row)
			//R.row_p[i][i] += Q.row_p[k][i] * Q.row_p[k][i];
		//R.row_p[i][i] = sqrt(R.row_p[i][i]);//必须定义求根号。
		if (R.row_p[i][i]==T())
			throw"three must be something wrong";
		re(k, row)
			Q.row_p[k][i] /= R.row_p[i][i];
	}
}

Template(void) House(const deri_matrix& mat, unsigned r, unsigned c, T* ans)
{
	T temp;
	two_norm(temp, mat.row_p + r, c, mat.row - r);
	ans[0] = mat.row_p[r][c] + ((mat.row_p[r][c] > 0) ? temp : T() - temp);
	for (int i = 1; i+r< mat.row; i++)
		ans[i] = mat.row_p[r + i][c];
}

Template(void) qr(deri_matrix& Q, deri_matrix& R) const
{
	if (row < col)throw "Not Supported yet(^_^";
	deri_matrix temp_q(row,row);
	Q = deri_matrix(row, col);
	deri_matrix  temp_r(row, col);
	R = deri_matrix(col, col);
	re(i, row)//单位矩阵。
		temp_q.row_p[i][i] = 1;
	temp_r = static_cast<const deri_matrix&>(*this);
	T* temp = new T[row];
	T *u = new T[row];
	T norm;
	re(i, col)
	{
		//计算u和||u||
		House(temp_r, i, i, u + i);
		dot_product(norm, u + i, u + i, row - i);
		//计算R
		//先算u'*A
		for (int j = i; j < col; j++)
			dot_product(temp[j], u + i, temp_r.row_p + i, j, row - i);
		//再算u*A
		for (int k = i; k < col; k++)//手动展开循环。j=i的时候。填入R。
			R.row_p[i][k] = (temp_r.row_p[i][k] -= 2 * u[i] * temp[k] / norm);
		for (int j = i + 1; j < row; j++)//该列默认为0不用算。
			 temp_r.row_p[j][i] = 0;
		for (int j = i + 1; j < row; j++)
			for (int k = i + 1; k < col; k++)
				temp_r.row_p[j][k] -= 2 * u[j] * temp[k] / norm;
		//开始计算Q
		//先算P*u
		for (int j = 0; j < row; j++)
			dot_product(temp[j], u + i, temp_q.row_p[j] + i, row - i);
		//再算P*u'
		for (int j = 0; j < row; j++)//手动展开循环。k=i的时候，填入Q。
			Q.row_p[j][i] = temp_q.row_p[j][i] -= 2 * u[i] * temp[j] / norm;
		for (int k = i + 1; k < row; k++)
			for (int j = 0; j < row; j++)
				temp_q.row_p[j][k] -= 2 * u[k] * temp[j] / norm;
	}
	delete[] temp;
	delete[] u;
}

Template(deri_matrix) qr(const deri_matrix& b) const
{
	if (row < col)throw "Not Supported yet(^_^";
	deri_matrix  temp_r(row, col), temp_ans(b), ans(col, 1);
	temp_r  = static_cast<const deri_matrix&>(*this);
	T* temp = new T[row];
	T *u    = new T[row];
	T norm, temp_y;
	re(i, col)
	{
		//计算u和||u||
		House(temp_r, i, i, u + i);
		dot_product(norm, u + i, u + i, row - i);
		//计算R
		//先算u'*A
		for (int j = i; j < col; j++)
			dot_product(temp[j], u + i, temp_r.row_p + i, j, row - i);
		//再算u*A
		for (int k = i; k < col; k++)//省略掉了一列。因为都是0，不会用到。
			temp_r.row_p[i][k] -= 2 * u[i] * temp[k] / norm;
		for (int j = i + 1; j < row; j++)
			for (int k = i + 1; k < col; k++)
				temp_r.row_p[j][k] -= 2 * u[j] * temp[k] / norm;
		//求Q'*b
		dot_product(temp_y, u + i, temp_ans.row_p + i, 0, row - i);
		for (int j = i; j < row; j++)
			temp_ans.row_p[j][0] -= 2 * temp_y*u[j] / norm;
	}
	//求R^-1*b，由于R是上三角。
	for (int i = col - 1; i >= 0; i--)
	{
		dot_product(temp_y, temp_r.row_p[i] + i + 1, temp_ans.row_p + i + 1, 0, col- i - 1);
		ans.row_p[i][0] = (temp_ans.row_p[i][0] -= temp_y) /= temp_r.row_p[i][i];
	}
	delete[] temp;
	delete[] u;
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
	//Matrix(T *Data, unsigned r = 0, unsigned c = 0) :bas_matrix(Data, r, c) {}
	Matrix(const Matrix& other) :bas_matrix(other) {}
	Matrix& operator=(const Matrix& other)
	{
		static_cast<bas_matrix<Matrix<value_type>, value_type>&>(*this).operator=(other); 
		return *this;
	}
	~Matrix() {};
};

Template(deri_matrix) transform() const
{
	deri_matrix ans(col, row);
	re(i, row)
		re(j, col)
		ans.row_p[j][i] = row_p[i][j];
	return ans;
}
