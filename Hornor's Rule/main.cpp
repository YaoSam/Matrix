/*
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include <iomanip>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG

double an[10] = { 1,9,36,84,126,126,84,36,9,1 };
double f_simple(const double &x)
{
	double ans = 0, X = 1;
	for(const auto& An:an)
	{
		ans += An*X;
		X *= x;
	}
	return ans;
}

double f_correct(const double &x)
{
	const double delta = -2;
	double ans = x + delta;
	re(i, 8)
		ans *= x+delta;
	return  ans;
}

double f_hornor(const double &x)
{
	double X = x, P = 0;
	for (int i = 9; i >= 0; i--)
	{
		P = an[i] + P * X;
	}
	return P;
}

double find_root(double (*f)(const double&),double const &a,double const & b)//范围【a,b】
{
	if (f(a)*f(b) > 0 || b < a)
		return NAN;
	double l = a, r = b, mid = (a + b) / 2, error = 1e-10, temp = 0;
	if(f(a)>0)
		while (r - l>error)
		{
			temp = f(mid);
			if (temp > 0)
				l = mid;
			else if (temp < 0)
				r = mid;
			else 
				return mid;
			mid = (l + r) / 2;
			//cout << mid << endl;
		}
	else 
		while(r-l>error)
		{
			temp = f(mid);
			if (temp > 0)
				r = mid;
			else if (temp < 0)
				l = mid;
			else
				return mid;
			mid = (l + r) / 2;
			//cout << mid << endl;
		}
	return  mid;
}


int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //没用的指针... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try {
		/*主函数*/
		double delta = 1;
		re(i, 10)
		{
			an[9 - i] *= delta;
			delta *= -2;
		}
		re(i, 10)
			cout << setprecision(16) << f_simple(i) << " : " << f_hornor(i) << endl;
		double a = 1, b = 4;
		cout << "用两种方法求根: " << endl;
		//cout << find_root(f_simple, a, b)<<endl;
		cout << find_root(f_hornor, a, b)<<endl;
		cout << find_root(f_correct, a, b) << endl;
		unsigned count = 0;
		double temp = 0;
		re(i, 100000)
		{
			temp = f_hornor(2 + double(i) / 1000000);
			if(i%100==0)
				cout << temp << endl;
			if (temp == 0)
				count++;
		}
		cout << count<<endl;


	}
	catch (const char * error) { cout << error << endl; }
	cout << "运行时间：" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}