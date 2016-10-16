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
void test()
{
	thread_num = 16;
	unsigned m = 512, n = 512;
	Matrix<double> one(m,n),two(n,m);
	re(i, m)
		re(j, n)
	{
		one[i][j] = rand();
		two[j][i] = rand();
	}
	cout << "线程数目::" << thread_num << endl;
	clock_t BeginTime = clock();
	one =one*two;
	cout << "运行时间::" << clock() - BeginTime << endl;
	cout << "矩阵大小::" << m << " " << n << endl;
}

double x_n(double x,int n)
{
	double ans = 1;
	re(i, n)
		ans *= x;
	return ans;
}

extern unsigned thread_num;
int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
//#ifdef _DEBUG
	FILE *input, *output; //没用的指针... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
	//Matrix<double> temp;
	//cin >> temp;
	//cout << (temp*temp) << endl;
	//cout << (temp *= temp) << endl;
	//cout << thread_num << endl;
//#endif
	try {
		/*主函数*/
		//test();
		//const unsigned n = 3;
		Matrix<double> A;
		cin >> A;
		cout << A << endl;
		Matrix<double> q, r;
		A.QR(q, r);
		cout << q << endl << r << endl;
		cout << A - q*r << endl;
		cout << q.transform()*q << endl;
		cout << r.inverse()*q.transform() << endl;
		cout << (A.transform()*A).inverse()*A.transform() << endl;
		Matrix<double> b;
		cin >> b;
		re(i, 5)
			re(j, 5)
			A[i][j] = x_n(i+1, j);
		cout << A << endl;
		A.QR(q, r);
		cout << (A.transform()*A).inverse()*A.transform()*b<<endl;
		cout << r.inverse()*q.transform()*b<<endl;
	}
	catch (const char * error) { cout << error << endl; }
	cout << "运行时间：" << clock() - BeginTime << endl;
#ifndef _DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}