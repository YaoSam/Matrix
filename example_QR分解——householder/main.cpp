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
#include "../basic/bas_matrix.h"
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG
extern unsigned thread_num;
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
		cout << thread_num << endl;
		const int m=3, n=3;
		Matrix<double> A(m, n);
		Matrix<double> q, r;
		re(i, m)
			re(j, n)
			A[i][j] = rand() % 100;
		A.qr(q, r);
		cout << "A:" << endl<< A << endl
			 << "q:" << endl << q << endl
		     << "r:" << endl << r <<endl
		     << "A-q*r" <<endl<< A - q*r << endl
		     << "q'*q:" << endl << q.transform()*q;

	}
	catch (const char * error) { cout << error << endl; }
	cout << "����ʱ�䣺" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}