/*
*������������������������������+ +
*�������������������ߩ��������ߩ� + +
*�������������������������������� ��
*�������������������������������� ++ + + +
*������������ ������������������ ��+
*�������������������������������� +
*�����������������������ߡ�������
*�������������������������������� + +
*��������������������������������
*��������������������������������������������������
*���������������������������� + + + +
*������������������������������������Code is far away from bug with the animal protecting��������������
*���������������������������� + �����������ޱ���,������bug����
*����������������������������
*��������������������������������+������������������
*���������������������� �������������� + +
*�������������������� ���������������ǩ�
*�������������������� ������������������
*�����������������������������ש����� + + + +
*�����������������������ϩϡ����ϩ�
*�����������������������ߩ������ߩ�+ + + +
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
	unsigned m = 512, n = 512;
	Matrix<double> one(m,n),two(n,m);
	re(i, m)
		re(j, n)
	{
		one[i][j] = rand();
		two[j][i] = rand();
	}
	clock_t BeginTime = clock();
	one = one*two;
	cout << "����ʱ��:::" << clock() - BeginTime << endl;
	cout << m << " " << n << " " << m*n*m << endl;
	//cout << one<< endl;
}
extern unsigned thread_num;
int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef _DEBUG
	FILE *input, *output; //û�õ�ָ��... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try {
		/*������*/
		//Matrix<double> temp;
		//cin >> temp;
		//cout << (temp * temp) << endl;
		cout << thread_num << endl;
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
	cout << "����ʱ�䣺" << clock() - BeginTime << endl;
#ifndef _DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}