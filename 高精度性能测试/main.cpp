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
#include "../basic/bas_matrix.h"
#include "../高精度/big_int.h"
#include "../高精度/natnum.h"
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
void test()
{
	thread_num = 16;
	unsigned m = 512, n = 512;
	Matrix<double> one(m, n), two(n, m);
	re(i, m)
		re(j, n)
	{
		one[i][j] = rand();
		two[j][i] = rand();
	}
	cout << "线程数目::" << thread_num << endl;
	clock_t BeginTime = clock();
	one = one*two;
	cout << "运行时间::" << clock() - BeginTime << endl;
	cout << "矩阵大小::" << m << " " << n << endl;
}

double x_n(double x, int n)
{
	double ans = 1;
	re(i, n)
		ans *= x;
	return ans;
}

extern unsigned thread_num;
int main()
{
	srand(unsigned(time(NULL)));
	FILE *input, *output; //没用的指针... ...
	freopen_s(&output, "out.txt", "w", stdout);
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	try {
		/*主函数*/
		const unsigned n = 80;
		Matrix<natnum> A(n, n);
		re(i, n)
		{
			A[i][i] = 6;
			if (i > 0)
			{
				A[i - 1][i] = 1;
				A[i][i - 1] = 8;
			}
		}
		auto ans = A.inverse()*A;
		QueryPerformanceCounter(&t2);
		cout << ans << endl;
	}
	catch (const char * error) { cout << error << endl; }
	printf("Use Time:%fms\n", 1e3*(t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
	return 0;
}