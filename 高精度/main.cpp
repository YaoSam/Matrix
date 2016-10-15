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
#include"big_int.h"
#include "natnum.h"
#include <vector>
#include "../basic/bas_matrix.h"
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG


void test()
{
	const unsigned n = 40;
	Matrix<q> A(n, n);
	//cout << A << endl;
	Matrix<q> B(n, 1);
	B[0][0] = big_int(7);
	re(i, n)
	{
		A[i][i] = big_int(6);
		if (i > 0)
		{
			A[i - 1][i] = big_int(1);
			A[i][i - 1] = big_int(8);
			B[0][i] = big_int(15);
		}
	}
	B[0][n - 1] = big_int(14);
	//cout << A << endl;
	//cout << A.inverse()*B << endl;
	//cout<<A.ChosenLU()<<endl;
	//cout << A << endl;
	auto temp = A.inverse();
	//cout << temp << endl;
	cout << temp*A << endl;
	//auto P(A.ChosenLU());
	//cout << A.ChosenLU() << endl;
	//cout << A << endl;
	//cout << A.LU_solve(P*B) << endl;;
	//cout << B << endl;
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
		//string a,b;
		//vector<big_int> num;
		//while (cin >> a >> b)
		//	cout << a << " " << b << " " << natnum(a, b) << endl;
	}
	catch (const char * error) { cout << error << endl; }
	cout << "运行时间：" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}