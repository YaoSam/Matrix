#pragma once
#include <iostream>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
struct complex
{
	double x, y;
	complex(double X=0,double Y=0):x(X),y(Y){}
	complex& operator+=(const complex& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	complex& operator-=(const complex& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	complex& operator*=(const complex& other)
	{
		double ansx = x*other.x - y*other.y;
		y = x*other.y + y*other.x;
		x = ansx;
		return *this;
	}
	complex& operator/=(const complex& other)
	{
		double temp = other.norm();
		double ansx = (x*other.x + y*other.y)/temp;
		y = (y*other.x - x*other.y)/temp;
		x = ansx;
		return*this;
	}
	double norm()const
	{
		return x*x + y*y;
	}
	bool operator==(const complex& other)const
	{
		return x == other.x&&y == other.y;
	}
};
inline complex operator+(const complex& a, const complex& b)
{
	return complex(a.x + b.x, a.y + b.y);
}
inline complex operator-(const complex& a, const complex& b)
{
	return complex(a.x - b.x, a.y - b.y);
}
inline complex operator*(const complex& a, const complex& b)
{
	return complex(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}
inline complex operator/(const complex& a, const complex& b)
{
	double temp=b.norm();
	return complex((a.x*b.x + a.y*b.y) / temp, (a.y*b.x - a.x*b.y) / temp);
}
double abs(const complex& a)
{
	return sqrt(a.norm());
}

inline ostream& operator<<(ostream& out, const complex & x)
{
	if (x.y == 0)
		return out << x.x;
	return out << x.x << '+' << x.y << 'i';
}

inline istream& operator>>(istream& in, complex & x)
{
	return in >> x.x >> x.y;
}
