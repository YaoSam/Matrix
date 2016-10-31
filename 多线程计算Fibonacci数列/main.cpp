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
#include "../�߾���/big_int.h"
#include<vector>
#include <Windows.h>
#include <thread>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)

double x_n(double x, int n)
{
	double ans = 1;
	re(i, n)
		ans *= x;
	return ans;
}
const unsigned int thread_num = 8;
big_int Fib[100000];
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
		vector<thread> Thread;
		int n = 70000;
		unsigned int T_n = 2*thread_num;
		Fib[0] = 0;
		Fib[1] = 1;
		if(thread_num==1)
		{
			re(i, n - 2)
				Fib[i + 2] = Fib[i] + Fib[i + 1];
		}
		else
		{
			re(i, 4* thread_num)
				Fib[i + 2] = Fib[i] + Fib[i + 1];
			for (int i = 0; i<thread_num; i++)
			{
				Thread.push_back(thread([i, T_n, n]()
				{
					for (int j = 2*(i + T_n); j<n; j +=T_n)
					{
						Fib[j] = Fib[j - T_n] * Fib[T_n - 1] + Fib[j - T_n + 1] * Fib[T_n];
						Fib[j + 1] = Fib[j - T_n] * Fib[T_n] + Fib[j - T_n + 1] * Fib[T_n + 1];
					}
				}));
			}
			for (auto & i : Thread)
				i.join();
		}

		QueryPerformanceCounter(&t2);
		//re(i, n)
		//	cout << Fib[i]<<endl;

	}
	catch (const char * error) { cout << error << endl; }
	printf("Use Time:%fms\n", 1e3*(t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
	return 0;
}