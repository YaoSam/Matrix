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
#include "SymmetricMatrix.h"
#include "../��Ȼ��/n.h"
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG


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
		ll data[1000];
		N Data[1000];
		unsigned n;
		cin >> n;
		re(i, n*(n+1)/2)
		{
			cin >> data[i];
			Data[i] = N(data[i], 1);
		}
		//for (auto&i : data)
			//cout<<(i = &i-data+1)<<" ";

		//re(i, 10)
		{
			sys_matrix<N> one(Data, n);
			cout << one << endl;
			sys_matrix<N> two(one);
			cout << two.LU() << endl;
			cout<<one.Cholesky()<<endl;
		}
	}
	catch (const char * error) { cout << error << endl; }
	cout << "����ʱ�䣺" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}