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
#include <iomanip>
#include "../basic/bas_matrix.h"
#include "../�߾���/big_int.h"
#include "../�߾���/natnum.h"
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
	cout << "�߳���Ŀ::" << thread_num << endl;
	clock_t BeginTime = clock();
	one = one*two;
	cout << "����ʱ��::" << clock() - BeginTime << endl;
	cout << "�����С::" << m << " " << n << endl;
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
	FILE *input, *output; //û�õ�ָ��... ...
	freopen_s(&output, "out.txt", "w", stdout);
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	try {
		/*������*/
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