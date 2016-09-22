#pragma once
#include <iostream>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#undef ll
#define ll long long

template<class T>
T gcd(T a, T b)
{
	static T temp;
	while (a%b != T())
	{
		temp = a;
		a = b;
		b = temp%a;
	}
	return b;
}
template<class T> bool operator<(const T&a, const T&b) { return !(a > b || a == b); }
template<class T> bool operator>=(const T&a, const T&b) { return (a > b || a == b); }
template<class T> bool operator<=(const T&a, const T&b) { return !a > b; }
template<class T> bool operator!=(const T&a, const T&b) { return !a == b; }

class natural_num
{
	long long up, down;
public:
	natural_num(const ll &a=0,const ll &b=1):up(0),down(0)
	{
		create(a, b);
		fix_sign();
	}
	void create(const ll&a=0,const ll&b=1)
	{
		ll temp = gcd(a, b);
		up = a / temp;
		down = b / temp;
	}
	void fix_sign()
	{
		if(down<0)
		{
			up *= -1;
			down *= -1;
		}
	}
	friend ostream& operator<<(ostream& out, const natural_num& me)
	{
		return me.down==1?(out<<me.up):(out << me.up << '/' << me.down);
	}
	friend istream& operator >> (istream& in, natural_num& me)
	{
		ll a, b;
		in >> a >> b;
		me.create(a, b);
		me.fix_sign();
		return in;
	}
	natural_num& operator+=(const natural_num& other)
	{
		create(up*other.down + down*other.up, down*other.down);
		return *this;
	}
	natural_num& operator-=(const natural_num& other)
	{
		create(up*other.down - down*other.up, down*other.down);
		return *this;
	}
	natural_num& operator*=(const natural_num& other)
	{
		create(up*other.up, down*other.down);
		return *this;
	}
	natural_num& operator/=(const natural_num& other)
	{
		if (other.up == 0)
			throw "²»ÄÜ³ý";
		create(up*other.down, down*other.up);
		fix_sign();
		return *this;
	}
	friend natural_num inline operator+(const natural_num& a,const natural_num& other);
	friend natural_num inline operator-(const natural_num& a,const natural_num& other);
	friend natural_num inline operator*(const natural_num& a,const natural_num& other);
	friend natural_num inline operator/(const natural_num& a,const natural_num& other);
	bool operator==(const natural_num& other)const
	{
		return up == other.up&&down == other.down;
	}
	bool operator>(const natural_num& other)const
	{
		return up*other.down > other.up*down;
	}
	friend double abs(const natural_num& other)
	{
		return double(other.up) / double(other.down);
	}
};

natural_num inline operator+(const natural_num& a, const natural_num& other)
{
	natural_num ans(a);
	return ans += other;
}
natural_num inline operator-(const natural_num& a, const natural_num& other)
{
	natural_num ans(a);
	return  ans -= other;
}
natural_num inline operator*(const natural_num& a, const natural_num& other)
{
	natural_num ans(a);
	return ans *= other;
}
natural_num inline operator/(const natural_num& a, const natural_num& other)
{
	natural_num ans(a);
	return ans /= other;
}
typedef natural_num N;