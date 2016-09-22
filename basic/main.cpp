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
#define DEBUG


void test()
{
	Matrix<double> one,two;
	cin >> one>>two;
	cout << one << endl;
	cout << two << endl;
	cout << one << endl;
	Matrix<double> ans = one.solve(two);
	cout << ans << endl;

}

int main()
{
	clock_t BeginTime = clock();
	srand(unsigned(time(NULL)));
#ifdef DEBUG
	FILE *input, *output; //û�õ�ָ��... ...
	freopen_s(&input, "in.txt", "r", stdin);
	freopen_s(&output, "out.txt", "w", stdout);
#endif
	try {
		/*������*/
		//test();
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
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}