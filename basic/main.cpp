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
#include "bas_matrix.h"
#include <iomanip>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG


void test()
{
	Matrix<double> temp;
	cin >> temp;
	cout << (temp * temp) << endl;
	unsigned m = 1024, n = 1024;
	Matrix<double> one(m,n),two(n,m);
	re(i, m)
		re(j, n)
	{
		one[i][j] = rand();
		two[j][i] = rand();
	}
	clock_t BeginTime = clock();
	one = one*two;
	cout << "测试时间:::" << clock() - BeginTime << endl;
	cout << m << " " << n << " " << m*n*m << endl;
	//cout << one<< endl;
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
		test();
		const unsigned n = 3;
		Matrix<double> A(n, n);
		Matrix<double> B(n, 1);
		B[0][0] = 7;
		re(i,n)
		{
			A[i][i] = 6;
			if (i > 0)
			{
				A[i - 1][i] = 1;
				A[i][i - 1] = 8;
				B[0][i] = 15;
			}
		}
		B[0][n-1] = 14;
		cout << A << endl;
		//A.LU();
		cout << A.inverse()*A << endl;
		//matrix P(A.ChosenLU());
		//cout << A.ChosenLU() << endl;
		//cout << A << endl;
		//cout <<setprecision(15)<< A.LU_solve(P*B) << endl;;
		//cout << B << endl;
	}
	catch (const char * error) { cout << error << endl; }
	cout << "运行时间：" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}