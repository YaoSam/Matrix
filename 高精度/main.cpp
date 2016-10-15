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
#include"bignum.h"
#include <vector>
#include "../basic/bas_matrix.h"
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG

int kgcd(int a,int b)
{
	if (a == 0)return b;
	if (b == 0)return a;
	if ((a % 2 == 0) && b % 2 == 0)
		return kgcd(a / 2, b / 2) * 2;
	if (b % 2 == 0)
		return kgcd(a, b / 2);
	if (a % 2 == 0)
		return kgcd(a / 2, b);
	return kgcd(abs(a - b), a > b ? b : a);
}
void test()
{
	const unsigned n = 50;
	Matrix<natnum> A(n, n);
	//cout << A << endl;
	Matrix<natnum> B(n, 1);
	B[0][0] = bignum(7);
	re(i, n)
	{
		A[i][i] = bignum(6);
		if (i > 0)
		{
			A[i - 1][i] = bignum(1);
			A[i][i - 1] = bignum(8);
			B[0][i] = bignum(15);
		}
	}
	B[0][n - 1] = bignum(14);
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
		//vector<bignum> num;
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