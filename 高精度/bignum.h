#pragma once
#include <string>
#undef re
#define re(i,n) for(unsigned int i=0,m=n;i<m;i++)
using namespace std;
class natnum;
class bignum
{
	friend class natnum;
	int* data;
	int length;
	bool sign;
	bignum& negative() { sign = true; return *this; }
	friend bignum Plus(const bignum& a, const bignum& b);
	friend bignum Subtract(const bignum& a, const bignum& b);
public:
	bignum():data(nullptr),length(0),sign(false){}
	bignum(const string& num);
	bignum(int num);
	bignum(const bignum &other);
	bignum& operator=(const bignum& other);
	~bignum()
	{
		if (data != nullptr)
			delete[]data;
	}
	bignum &half();
	friend ostream& operator<<(ostream& out, const bignum&other);
	friend bool cmp_abs_smaller(const bignum&a, const bignum&b);
	friend bool   operator==     (const bignum&a, const bignum&b);//正数的相加
	friend bool   operator!=     (const bignum&a, const bignum&b);
	friend bool   operator<	   (const bignum&a, const bignum&b);
	friend bool   operator<=     (const bignum&a, const bignum&b);
	friend bool   operator>	   (const bignum&a, const bignum&b);
	friend bool   operator>=     (const bignum&a, const bignum&b);
	friend bignum operator+    (const bignum&a, const bignum&b);
	friend bignum operator-    (const bignum&a, const bignum&b);
	friend bignum operator*    (const bignum&a, const bignum&b);
	friend bignum operator/(bignum a, const bignum&b);
	friend bignum gcd(bignum a, bignum b);
	friend bignum abs(const bignum&a);
	friend bool abs_cmp(const natnum& a, const natnum& b);
};
bignum Plus     (const bignum& a, const bignum& b);//正数的相加
bignum Subtract (const bignum& a, const bignum& b);
bignum operator+(const bignum&a, const bignum&b);
bignum operator-(const bignum&a, const bignum&b);
bignum operator*(const bignum&a, const bignum&b);
bignum operator/(bignum a, const bignum&b);

bool operator== (const bignum & a, const bignum & b);
bool operator!= (const bignum & a, const bignum & b);
bool operator<  (const bignum & a, const bignum & b);
bool operator<= (const bignum & a, const bignum & b);
bool operator>  (const bignum & a, const bignum & b);
bool operator>= (const bignum & a, const bignum & b);

bool cmp_abs_smaller(const bignum&a, const bignum&b);
bignum gcd(bignum a, bignum b);
template<class T> T& operator+=(T& a, const T& b) { a = a + b; return a; }
template<class T> T& operator*=(T& a, const T& b) { a = a * b; return a; }
template<class T> T& operator-=(T& a, const T& b) { a = a - b; return a; }
template<class T> T& operator/=(T& a, const T& b) { a = a / b; return a; }
bignum abs(const bignum&a);


class natnum
{
	bignum up, down;
public:
	natnum(const bignum &a = 0, const bignum &b = 1) :up(0), down(1)
	{
		create(a, b);
	}
	void create(const bignum&a = 0, const bignum&b = 1)
	{
		bignum temp = gcd(a, b);
		up = a / temp;
		down = b / temp;
		fix_sign();
	}
	void fix_sign()
	{
		if (down.sign)
		{
			up.sign=!up.sign;
			down.sign = !down.sign;
		}
	}
	friend ostream& operator<<(ostream& out, const natnum& me)
	{
		static bignum one("1");
		return me.down == one ? (out << me.up) : (out << me.up << '/' << me.down);
	}
	natnum& operator+=(const natnum& other)
	{
		create(up*other.down + down*other.up, down*other.down);
		return *this;
	}
	natnum& operator-=(const natnum& other)
	{
		create(up*other.down - down*other.up, down*other.down);
		return *this;
	}
	natnum& operator*=(const natnum& other)
	{
		create(up*other.up, down*other.down);
		return *this;
	}
	natnum& operator/=(const natnum& other)
	{
		if (other.up == 0)
			throw "不能除";
		create(up*other.down, down*other.up);
		return *this;
	}
	friend natnum operator+(const natnum& a, const natnum& other) { return natnum(a) += other; }
	friend natnum operator-(const natnum& a, const natnum& other) { return natnum(a) -= other; }
	friend natnum operator*(const natnum& a, const natnum& other) { return natnum(a) *= other; }
	friend natnum operator/(const natnum& a, const natnum& other) { return natnum(a) /= other; }
	bool operator==(const natnum& other)const
	{
		return up == other.up&&down == other.down;
	}
	bool operator>(const natnum& other)const
	{
		return up*other.down > other.up*down;
	}
	friend bool abs_cmp(const natnum& a,const natnum& b)
	{
		if (a.up.sign == b.up.sign)
		{
			if (a.up.sign == false)
				return a.up*b.down > b.up*a.down;
			return a.up*b.down < b.up*a.down;
		}
		if (a.up.sign == false)
			return a.up*b.down > (b.up*a.down).negative();
		return (a.up*b.down).negative() > b.up*a.down;
		//return abs(double(other.up) / double(other.down));
	}
};