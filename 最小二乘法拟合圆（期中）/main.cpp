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
#include<random>
#include <math.h>
#include <array>
#include "../basic/bas_matrix.h"
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
const double pi = 3.1415926;

const unsigned n = 10000000;
array<double,n> x, y;
int main()
{
	srand(unsigned(time(NULL)));
	FILE *input, *output; //没用的指针... ...
	freopen_s(&output, "out.txt", "w", stdout);
	LARGE_INTEGER t1, t2, t3,tc;
	QueryPerformanceFrequency(&tc);
	try {
		/*主函数*/
		thread_num = 1;//关闭多线程。
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<double> uniform(0, 2 * pi);
		normal_distribution<double> normal(0, 0.1);
		re(i,n)
		{
			auto d = uniform(gen);
			x[i] = cos(d) + normal(gen);
			y[i] = sin(d) + normal(gen);
		}
		Matrix<double> A(n, 3),B(n, 1);
		re(i,n)
		{
			B[i][0] = -x[i] * x[i] - y[i] * y[i];
			A[i][0] = x[i];
			A[i][1] = y[i];
			A[i][2] = 1;
		}
		QueryPerformanceCounter(&t1);
		auto ans2 = (A.transform()*A).inverse()*A.transform()*B;
		QueryPerformanceCounter(&t2);
		auto ans = A.qr(B);
		QueryPerformanceCounter(&t3);
		cout << ans << endl;
		cout << ans2 << endl;
		cout << ans2 - ans << endl;
		auto a = ans[0][0], b = ans[1][0], c = ans[2][0];
		cout << a / -2 << endl << b / -2 <<endl<< sqrt(a*a + b*b - 4 * c) / 2 << endl;
	}
	catch (const char * error) { cout << error << endl; }
	printf("Use Time:%fms\n", 1e3*(t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
	printf("Use Time:%fms\n", 1e3*(t3.QuadPart - t2.QuadPart)*1.0 / tc.QuadPart);

	return 0;
}