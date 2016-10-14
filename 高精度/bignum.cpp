#include "bignum.h"
#include <iostream>
#include <vector>
const int ten[6] = { 1,10,100,1000,10000,100000 };
bignum Plus(const bignum& a, const bignum& b)
{
	bignum ans;
	ans.length = (a.length > b.length ? a.length : b.length) + 1;
	ans.data = new int[ans.length];
	ans.sign = a.sign;
	memset(ans.data, 0, sizeof(int)*ans.length);
	memcpy(ans.data, a.data, sizeof(int)*a.length);
	re(i, b.length)
		ans.data[i] += b.data[i];
	re(i, ans.length - 1)
	{
		if (ans.data[i]>10000)
		{
			++ans.data[i + 1];
			ans.data[i] %= 10000;
		}
	}
	if (ans.data[ans.length - 1] == 0)
		ans.length--;
	if (ans.length == 0)ans.sign = false;
	return ans;
}
		
bignum Subtract(const bignum& a, const bignum& b)
{
	bignum ans;
	ans.sign = a.sign;
	ans.length = a.length > b.length ? a.length : b.length;
	int origin_len = ans.length;
	ans.data = new int[ans.length];
	memset(ans.data, 0, sizeof(int)*ans.length);
	//相减（data
	memcpy(ans.data, a.data, sizeof(int)*a.length);
	re(i, b.length)
	{
		ans.data[i] -= b.data[i];
	}
	//调整符号（sign
	re(i, ans.length)//找到第一个不为零的数，
	{
		if (ans.data[ans.length - i - 1] > 0)
		{
			ans.length -= i;
			break;//正数，直接退出
		}
		if (ans.data[ans.length - i - 1] < 0)//负数，
		{
			ans.length -= i;
			ans.sign = !ans.sign;//修改符号
			re(j, ans.length)//全部取负
				ans.data[j] *= -1;
			break;
		}
	}
	re(i, ans.length)
	{
		if (ans.data[i]<0)
		{
			ans.data[i] += 10000;
			ans.data[i + 1]--;
		}
	}
	//调整length
	re(i, ans.length)
	{
		if (ans.data[ans.length - i - 1] > 0)
		{
			ans.length -= i;
			if(origin_len>ans.length)//大小改变了，调整节省空间。
			{
				int *temp_data = new int[ans.length];
				memcpy(temp_data, ans.data, sizeof(int)*ans.length);
				delete[]ans.data;
				ans.data = temp_data;
			}
			return ans;
		}
		if (i == ans.length - 1)//全部皆为0
		{
			delete[]ans.data;
			ans.data = nullptr;
			ans.sign = false;
			ans.length = 0;
		}
	}
	return ans;
}

bignum operator+(const bignum&a, const bignum&b) {
	if (a.sign == b.sign)
		return Plus(a, b);
	return Subtract(a, b);
}
bignum operator-(const bignum&a, const bignum&b) {
	if (a.sign == b.sign)
		return Subtract(a, b);
	//if (b.sign == true)
	return Plus(a, b);
}

bignum operator-(const bignum&a, const bignum&b);

bignum operator*(const bignum& a, const bignum& b)
{
	static const bignum one("1"),zero("0");
	if (a.length == 0 || b.length == 0)
		return bignum();
	bignum ans;
	ans.length = a.length + b.length;
	ans.data = new int[ans.length];
	ans.sign = a.sign^b.sign;
	memset(ans.data, 0, sizeof(int)*ans.length);
	re(i,a.length)
		re(j,b.length)
	{
		ans.data[i + j] += a.data[i] * b.data[j];
		if (ans.data[i + j] > 10000)
		{
			ans.data[i + j + 1] += ans.data[i + j] / 10000;
			ans.data[i + j] %= 10000;
		}
	}
	re(i, ans.length)
	{
		if (ans.data[ans.length - i - 1] > 0)
		{
			ans.length -= i;
			int *temp_data = new int[ans.length];
			memcpy(temp_data, ans.data, sizeof(int)*ans.length);
			delete[]ans.data;
			ans.data = temp_data;
			break;
		}
		//不会出现为0的情况。
	}
	return ans;
}

bignum operator/(bignum a, bignum b)//TODO 除法的符号。
{
	static const bignum zero, one("1"), neg("-1"),two("2");
	if (b == zero)throw "can't / zero!";
	if (b == one)return a;
	if (b == neg)return a.negative();
	if (cmp_abs_smaller(a, b))return zero;
	bool sign = (a.sign != b.sign);
	b.sign = a.sign = false;
	bignum ans,temp("1"),temp_b;
	static vector<bignum> two_arr(1,temp);
	int len=two_arr.size();
	if (two_arr[len - 1] < a)
	{
		while (two_arr[two_arr.size() - 1] < a)
			two_arr.push_back(two_arr[two_arr.size() - 1] * two);
		len = two_arr.size();
	}
	else
	{
		len--;
		while (two_arr[len - 1] >= a)
			len--;
	}
	temp_b = two_arr[len - 1] * b;
	re(i,len)
	{
		if (temp_b == a)
			return sign ? (ans + two_arr[len - i - 1]).negative() : (ans + two_arr[len - i - 1]);
		if(temp_b<a)
		{
			a -= temp_b;
			ans += two_arr[len - i - 1];
		}
		temp_b.half();
	}
	return sign ? ans.negative() : ans;
}

bool cmp_abs_smaller(const bignum & a, const bignum & b)
{
	if (a.length < b.length)return true;
	if (a.length > b.length)return false;
	re(i, a.length)
	{
		if (a.data[a.length - i - 1] == b.data[b.length - i - 1])continue;
		return a.data[a.length - i - 1] < b.data[b.length - i - 1];
	}
	return false;
}
bool operator==(const bignum & a, const bignum & b)
{
	if (a.sign != b.sign)		return false;
	if (a.length != b.length)	return false;
	re(i, a.length)
		if (a.data[i] != b.data[i])
			return false;
	return true;
	//return equal(a.data, a.data + a.length, b.data);
}
bool operator!=(const bignum & a, const bignum & b)
{
	return !(a == b);
}
bool operator<(const bignum & a, const bignum & b)
{
	if (a.sign != b.sign)return a.sign == true;
	return a.sign != cmp_abs_smaller(a, b);//+,false <  ||||| -,true >=
}
bool operator<=(const bignum & a, const bignum & b)
{
	if (a.sign != b.sign)return a.sign == true;
	if (a.length != b.length)return (a.length < b.length) != a.sign;
	re(i,a.length)
	{
		if (a.data[a.length - i - 1] == b.data[b.length - i - 1])continue;
		return (a.data[a.length - i - 1] < b.data[b.length - i - 1])!=a.sign;
	}
	return true;
}
bool operator>(const bignum & a, const bignum & b)
{
	return !(a <= b);
}
bool operator>=(const bignum & a, const bignum & b)
{
	return !(a < b);
}
bignum::bignum(const string& num) :
	length(0),
	data(nullptr),
	sign(false)
{
	if (num.length() == 0)
		return;
	if(num[0]=='-')
	{
		sign = true;
		length = (num.length() - 1) / 4 + ((num.length() - 1) % 4 != 0);
		data = new int[length];
		memset(data, 0, sizeof(int)*length);
		re(i,num.length()-1)
		{
			if ((num[m - i ] - '0') != 0)
				data[i / 4] += ten[i % 4] * (num[m - i] - '0');
		}

	}
	else
	{
		length = num.length() / 4 + (num.length() % 4 != 0);
		data = new int[length];
		memset(data, 0, sizeof(int)*length);
		re(i, num.length())
		{
			if ((num[m - i - 1] - '0') != 0)
				data[i / 4] += ten[i % 4] * (num[m - i - 1] - '0');
		}
	}		

}

bignum::bignum(int num):
	data(nullptr),sign(num<0),length(0)
{
	if (num == 0)return;
	if(sign)num *= -1;
	if(num<10000)
	{
		length = 1;
		data = new int[1];
		data[0] = num;
	}
	else if(num<100000000)
	{
		length = 2;
		data = new int[2];
		data[0] = num % 10000;
		data[1] = num / 10000;
	}
	else
	{
		length = 3;
		data = new int[3];
		data[0] = num % 10000;
		data[1] = (num / 10000) % 10000;
		data[2] = num / 100000000;
	}
}

bignum::bignum(const bignum & other):
	data(nullptr),
	length(other.length),
	sign(other.sign)
{
	if(length>0)
	{
		data = new int[length];
		memcpy(data, other.data, sizeof(int)*length);
	}
}

bignum & bignum::operator=(const bignum & other)
{
	if (this == &other)	return*this;
	if (data != nullptr)//TODO 优化内存的申请。
		delete[]data;
	length = other.length;
	sign = other.sign;
	if (length > 0)
	{
		data = new int[length];
		memcpy(data, other.data, sizeof(int)*length);
	}
	else
		data = nullptr;
	return *this;
}

bignum& bignum::half() 
{
	re(i,length-1)
		if (data[length - i - 1] % 2 != 0)
			data[length - i - 2] += 10000;
	re(i, length)
		data[i] /= 2;
	if (data[length - 1] == 0)
		length--;
	if (length == 0)
	{
		delete[]data;
		sign = false;
		data = nullptr;
	}
	return *this;
}

ostream & operator<<(ostream & out, const bignum & other)
{
	if (other.sign)out << '-';
	if (other.length > 0)
		out << other.data[other.length - 1];
	else
		return out << 0;
	re(i, other.length - 1)//后面补零即可正常输出
	{
		if (other.data[m - i - 1] < 10)
			out << "000";
		else if (other.data[m - i - 1] < 100)
			out << "00";
		else if (other.data[m - i - 1] < 1000)
			out << "0";
		out << other.data[m - i - 1];
	}
	return out;
}


bignum gcd(bignum a, bignum b)
{
	static bignum two("2");
	bignum ans("1");
	ans.sign = a.sign&&b.sign;
	a.sign = b.sign = false;
	while(true)
	{
		if (a.length == 0)return b*ans;
		if (b.length == 0)return a*ans;
		if (a.data[0] % 2 == 0 && b.data[0] % 2 == 0)
			a.half(), b.half(),ans=ans*two;
		else if (a.data[0] % 2 == 0)
			a.half();
		else if (b.data[0] % 2 == 0)
			b.half();
		else
		{
			if (cmp_abs_smaller(a, b))
				b = b - a;
			else
				a = a - b;
		}
	}
}
