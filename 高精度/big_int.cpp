#include "big_int.h"
#include <iostream>
#include <vector>
#undef re
#define re(i,n) for(int i=0,m=n;i<m;i++)
const int ten[6] = { 1,10,100,1000,10000,100000 };
big_int::big_int(const string& num) :
	length(0),
	data(nullptr),
	sign(false),
	size(0)
{
	if (num.length() == 0 || num == "0" || num == "-0")
		return;
	if (num[0] == '-')
	{
		sign = true;
		length = (num.length() - 1) / 4 + ((num.length() - 1) % 4 != 0);
		size = length * 2;
		apply_memory(data,size);
		re(i, num.length() - 1)
		{
			if ((num[m - i] - '0') != 0)
				data[i / 4] += ten[i % 4] * (num[m - i] - '0');
		}

	}
	else
	{
		length = num.length() / 4 + (num.length() % 4 != 0);
		size = length * 2;
		apply_memory(data,size);
		re(i, num.length())
		{
			if ((num[m - i - 1] - '0') != 0)
				data[i / 4] += ten[i % 4] * (num[m - i - 1] - '0');
		}
	}

}

big_int::big_int(const int &num) :
	data(nullptr), sign(num < 0), length(0), size(0)
{
	if (num == 0)return;
	int n = num;
	if (sign)n *= -1;
	if (num<10000)
	{
		size    = length = 1;
		data    = new int[1];
		data[0] = n;
	}
	else if (num<100000000)
	{
		size    = length = 2;
		data    = new int[2];
		data[0] = n % 10000;
		data[1] = n / 10000;
	}
	else
	{
		size    = length = 3;
		data    = new int[3];
		data[0] = n % 10000;
		data[1] = (n / 10000) % 10000;
		data[2] = n / 100000000;
	}
}

big_int::big_int(const big_int & other) :
	data(nullptr),
	length(other.length),
	sign(other.sign),
	size(2*other.length)//并没有用other的size
{
	if(length>0)
	{
		apply_memory(data, size);
		memcpy(data, other.data, sizeof(int)*length);
	}
}

big_int & big_int::operator=(const big_int & other)
{
	if (this == &other)	return*this;
	if (size < other.length)
	{
		if (size != 0)
			delete[]data;
		size = 2 * other.length;
		apply_memory(data, size);
		memcpy(data, other.data, sizeof(int)*other.length);
	}
	else
	{
		if (other.length == 0 && size != 0)
		{
			delete[] data;
			size = 0;
			data = nullptr;
		}
		else
		{
			memset(data, 0, sizeof(int)*size);//这里内存会浪费一些。
			memcpy(data, other.data, sizeof(int)*other.length);
		}
	}
	length = other.length;
	sign = other.sign;
	return *this;
}

big_int Plus(const big_int& a, const big_int& b)
{
	big_int ans;
	ans.length = (a.length > b.length ? a.length : b.length) + 1;
	ans.size   = ans.length;
	ans.apply_memory(ans.data, ans.size);
	ans.sign   = a.sign;
	memcpy(ans.data, a.data, sizeof(int)*a.length);
	re(i, b.length)
		ans.data[i] += b.data[i];
	re(i,ans.length)
		if (ans.data[i] >= 10000)
		{
			ans.data[i + 1]++;
			ans.data[i] %= 10000;
		}
	if (ans.data[ans.length - 1] == 0)
		ans.length--;
	if (ans.length == 0) {
		ans.sign = false;
		ans.size = 0;
		delete[]ans.data;
		ans.data = nullptr;
	}
	return ans;
}
	
big_int& big_int::Plus(const big_int& other)
{
	static const big_int zero;
	if (other.length == 0) return *this;
	int origin_len = length;
	length = (length > other.length ? length : other.length) + 1;
	if (size < length)
	{
		size = length * 2 ;
		int *temp_data = new int[size];
		memset(temp_data, 0, sizeof(int)*size);
		memcpy(temp_data, data, sizeof(int)*origin_len);
		delete[]data;
		data = temp_data;
	}
	re(i, other.length)
		data[i] += other.data[i];
	re(i,length)
		if(data[i]>=10000)
		{
			data[i + 1]++;
			data[i] %= 10000;
		}
	if (data[length - 1] == 0)
		length--;
	if(length==0)
	{
		sign = false;
		size = 0;
		delete[]data;
		data = nullptr;
	}
	return *this;
}

big_int Subtract(const big_int& a, const big_int& b)
{
	big_int ans;
	ans.sign   = a.sign;
	ans.length = a.length > b.length ? a.length : b.length;
	ans.size   = ans.length;
	ans.apply_memory(ans.data, ans.size);
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

			ans.length -= i;//这里内存会浪费些。
			break;
		}			
		if (i == ans.length - 1)//全部皆为0
		{
			delete[]ans.data;
			ans.data = nullptr;
			ans.sign = false;
			ans.length = 0;
			ans.size = 0;
			return ans;
		}
	}
	return ans;
}

big_int& big_int::Subtract(const big_int& other)
{
	static const big_int zero;
	if (other == zero)return *this;
	if (size < other.length)
	{
		size = other.length * 2 + 1;
		int *temp_data = new int[size];
		memset(temp_data, 0, sizeof(int)*size);
		memcpy(temp_data, data, sizeof(int)*length);
		delete[]data;
		data = temp_data;
	}
	length = length > other.length ? length : other.length;
	re(i, other.length)
		data[i] -= other.data[i];
	//调整符号（sign
	re(i, length)//找到第一个不为零的数，
	{
		if (data[length - i - 1] > 0)
		{
			length -= i;
			break;//正数，直接退出
		}
		if (data[length - i - 1] < 0)//负数，
		{
			length -= i;
			sign = !sign;//修改符号
			re(j, length)//全部取负
				data[j] *= -1;
			break;
		}
	}
	re(i, length)
	{
		if (data[i]<0)
		{
			data[i] += 10000;
			data[i + 1]--;
		}
	}
	//调整length
	re(i, length)
	{
		if (data[length - i - 1] > 0)
		{

			length -= i;//这里内存会浪费些。
			break;
		}
		if (i == length - 1)//全部皆为0
		{
			delete[]data;
			data = nullptr;
			sign = false;
			length = 0;
			size = 0;
			return *this;
		}
	}
	return *this;
}

big_int operator+(const big_int&a, const big_int&b) {
	return a.sign == b.sign ? Plus(a, b) : Subtract(a, b);
}

big_int& big_int::operator+=(const big_int& other)
{
	return sign == other.sign ? Plus(other) : Subtract(other);
}

big_int operator-(const big_int&a, const big_int&b) {
	return a.sign != b.sign ? Plus(a, b) : Subtract(a, b);
}

big_int& big_int::operator-=(const big_int& other)
{
	return sign != other.sign ? Plus(other) : Subtract(other);
}

big_int operator*(const big_int& a, const big_int& b)
{
	static const big_int one("1");
	if (a.length == 0 || b.length == 0)
		return big_int();
	if (b == one)return a;
	if (a == one)return b;
	big_int ans;
	ans.length = a.length + b.length;
	ans.data = new int[ans.length];
	ans.size = ans.length;
	ans.sign = a.sign^b.sign;
	memset(ans.data, 0, sizeof(int)*ans.length);
	re(i,a.length)
		re(j,b.length)
	{
		ans.data[i + j] += a.data[i] * b.data[j];
		if (ans.data[i + j] >= 10000)
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
			ans.size = ans.length;
			memcpy(temp_data, ans.data, sizeof(int)*ans.length);
			delete[]ans.data;
			ans.data = temp_data;
			break;
		}
		//不会出现为0的情况。
	}
	return ans;
}

big_int operator/(big_int a, const big_int&b)//TODO 除法的符号。
{
	static const big_int zero("0"), one("1"), two("2");
	if (b == zero)throw "can't / zero!";
	if (b == one)return a;
	if (cmp_abs_smaller(a, b))return zero;
	bool sign = (a.sign != b.sign);
	if(b.length==1)
	{
		big_int ans(a);
		re(i,ans.length-1)
		{
			ans.data[m - i - 1] += (ans.data[m - i] % b.data[0]) * 10000;
			ans.data[m - i] /= b.data[0];
		}
		ans.data[0] /= b.data[0];
		if (ans.data[ans.length - 1] == 0)
			ans.length--;
		if(ans.length==0)
		{
			ans.size = 0;
			delete[]ans.data;
			ans.data = nullptr;
		}
		return sign ? ans.negative() : ans;
	}
	big_int ans,temp("1"),temp_b;
	static vector<big_int> two_arr(1,temp);
	static const float coef = log2(10);
	int len = int(coef*(4*a.length + 1));
	while (two_arr.size() < len)
			two_arr.push_back(two_arr[two_arr.size() - 1] * two);
	while (!cmp_abs_smaller(two_arr[len - 1],a))
		len--;
	temp_b = two_arr[len - 1] * b;
	a.sign=temp_b.sign = false;
	re(i, len)
	{
		if (temp_b == a)
			return sign ? (ans + two_arr[len - i - 1]).negative() : (ans + two_arr[len - i - 1]);
		if (temp_b<a)
		{
			a -= temp_b;
			ans += two_arr[len - i - 1];
		}
		temp_b.half();
	}
	return sign ? ans.negative() : ans;
}

bool cmp_abs_smaller(const big_int & a, const big_int & b)
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
bool operator==(const big_int & a, const big_int & b)
{
	if (a.sign   != b.sign)		return false;
	if (a.length != b.length)	return false;
	re(i, a.length)
		if (a.data[i] != b.data[i])
			return false;
	return true;
	//return equal(a.data, a.data + a.length, b.data);
}
bool operator<(const big_int & a, const big_int & b)
{
	if (a.sign != b.sign)return a.sign == true;
	return a.sign != cmp_abs_smaller(a, b);//+,false <  ||||| -,true >=
}
bool operator<=(const big_int & a, const big_int & b)
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

big_int& big_int::half() 
{
	if (length == 0)return *this;
	re(i, length - 1)
	{
		if (data[m - i] % 2 != 0)
			data[m - i - 1] += 10000;
		data[m - i] /= 2;
	}
	data[0] /= 2;
	if (data[length - 1] == 0)
		length--;
	if (length == 0)
	{
		delete[]data;
		size = 0;
		sign = false;
		data = nullptr;
	}
	return *this;
}

ostream & operator<<(ostream & out, const big_int & other)
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

big_int gcd(big_int a, big_int b)
{
	//整数情况下的算法。
	//int kgcd(int a, int b)
	//{
	//	if (a == 0)return b;
	//	if (b == 0)return a;
	//	if ((a % 2 == 0) && b % 2 == 0)
	//		return kgcd(a / 2, b / 2) * 2;
	//	if (b % 2 == 0)
	//		return kgcd(a, b / 2);
	//	if (a % 2 == 0)
	//		return kgcd(a / 2, b);
	//	return kgcd(abs(a - b), a > b ? b : a);
	//}
	
	static big_int two("2");
	big_int ans("1");
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
				b -= a;
			else
				a -= b;
		}
	}
}
