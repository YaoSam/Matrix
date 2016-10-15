#pragma once
#include "big_int.h"
class natnum
{
	big_int up, down;
public:
	natnum(const big_int &a = 0, const big_int &b = 1) :up(0), down(1)
	{
		create(a, b);
	}
	void create(const big_int&a = 0, const big_int&b = 1)
	{
		big_int temp = gcd(a, b);
		up = a / temp;
		down = b / temp;
		fix_sign();
	}
	void fix_sign()
	{
		if (down.sign)
		{
			up.sign = !up.sign;
			down.sign = !down.sign;
		}
	}
	friend ostream& operator<<(ostream& out, const natnum& me)
	{
		static big_int one("1");
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
			throw "²»ÄÜ³ý";
		create(up*other.down, down*other.up);
		return *this;
	}
	friend natnum operator+(const natnum& a, const natnum& b) { return natnum(a.up*b.down + a.down*b.up, a.down*b.down); }
	friend natnum operator-(const natnum& a, const natnum& b) { return natnum(a.up*b.down - a.down*b.up, a.down*b.down); }
	friend natnum operator*(const natnum& a, const natnum& b) { return natnum(a.up*b.up, a.down*b.down); }
	friend natnum operator/(const natnum& a, const natnum& b) { return natnum(a.up*b.down, a.down*b.up); }
	bool operator==(const natnum& other)const
	{
		return up == other.up&&down == other.down;
	}
	bool operator>(const natnum& other)const
	{
		return up*other.down > other.up*down;
	}
	friend bool abs_cmp(const natnum& a, const natnum& b)
	{
		if (a.up.sign == b.up.sign)
		{
			if (a.up.sign == false)
				return a.up*b.down > b.up*a.down;
			return a.up*b.down < b.up*a.down;
		}
		if (a.up.sign == false)
			return a.up*b.down >(b.up*a.down).negative();
		return (a.up*b.down).negative() > b.up*a.down;
		//return abs(double(other.up) / double(other.down));
	}
};

typedef natnum q;