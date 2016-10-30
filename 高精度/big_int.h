#pragma once
#include <string>
#undef re
#define re(i,n) for(unsigned int i=0,m=n;i<m;i++)
using namespace std;
class natnum;
class big_int
{
	friend class natnum;
	int* data;
	bool sign;
	int length;
	int size;
	       big_int& negative() { sign = true; return *this; }
	friend big_int	Plus    (const big_int& a, const big_int& b);
	       big_int& Plus    (const big_int& other);
	       big_int& Subtract(const big_int& other);
	friend big_int Subtract (const big_int& a, const big_int& b);
	static void apply_memory(int* &pointer,int Size)
	{
		pointer = new int[Size];
		memset(pointer, 0, sizeof(int)*Size);
	}
public:
	big_int():data(nullptr),length(0),sign(false),size(0){}
	big_int(const string& num);
	big_int(const int &num);
	big_int(const big_int &other);
	big_int& operator=(const big_int& other);
	~big_int()
	{
		if (data != nullptr)
			delete[]data;
	}
	big_int &half();
	friend ostream& operator<<  (ostream& out, const big_int&other);
	friend bool cmp_abs_smaller (const big_int&a, const big_int&b);
	friend bool    operator==   (const big_int&a, const big_int&b);//正数的相加
	friend bool    operator!=   (const big_int&a, const big_int&b) { return !(a == b); }
	friend bool    operator<	(const big_int&a, const big_int&b);
	friend bool    operator<=   (const big_int&a, const big_int&b);
	friend bool    operator>	(const big_int&a, const big_int&b) { return !(a <= b); }
	friend bool    operator>=   (const big_int&a, const big_int&b) { return !(a < b); }
	big_int&       operator+=   (const big_int& other);
	big_int&       operator-=   (const big_int& other);
	big_int&	   operator*=   (const big_int& other) { return *this = *this+other; }
	big_int&	   operator/=   (const big_int& other) { return *this = *this/other; }
	friend big_int operator+    (const big_int&a, const big_int&b);
	friend big_int operator-    (const big_int&a, const big_int&b);
	friend big_int operator*    (const big_int&a, const big_int&b);
	friend big_int operator/    (big_int a, const big_int&b);
	friend big_int gcd          (big_int a, big_int b);
	friend big_int abs          (const big_int&a);
	friend bool abs_cmp         (const natnum& a, const natnum& b);
};
big_int Plus     (const big_int& a, const big_int& b);//正数的相加
big_int Subtract (const big_int& a, const big_int& b);
big_int operator+(const big_int&a, const big_int&b);
big_int operator-(const big_int&a, const big_int&b);
big_int operator*(const big_int&a, const big_int&b);
big_int operator/(big_int a, const big_int&b);

bool operator== (const big_int & a, const big_int & b);
bool operator!= (const big_int & a, const big_int & b);
bool operator<  (const big_int & a, const big_int & b);
bool operator<= (const big_int & a, const big_int & b);
bool operator>  (const big_int & a, const big_int & b);
bool operator>= (const big_int & a, const big_int & b);

bool cmp_abs_smaller(const big_int&a, const big_int&b);
big_int gcd(big_int a, big_int b);