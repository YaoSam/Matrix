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
#include <math.h>
#include <iomanip>
using namespace std;
#undef re
#define re(i,n) for(unsigned int i=0;i<n;i++)
#define DEBUG
union
{
	int i;
	double d;
}wtf;
double R = numeric_limits<double>::max();//���double
double r = numeric_limits<double>::min();//��С����double
double B, b, S, s, E;

double n_two(int n)
{
	double ans = 1;
	if (n > 0)
		re(i, n)
		ans *= 2;
	else
		re(i, -n)
		ans /= 2;
	return ans;
}
void initial()
{
	cout << r << endl;
	wtf.i = 1;
	r = wtf.d;
	cout << r << endl;
	const int emin = -1024, emax = 1024, t = 53;//�����ɱ��뻷��ȷ����
	b = n_two((emin - 1) / 2);
	B = n_two((emax - t + 1) / 2);
	s = b;
	S = n_two((emax + t - 1) / 2);
	E = n_two(1 - t);
	//cout << b << endl << B << endl << s << endl << S << endl << E << endl;
}
inline double sqr(const double &a) { return a*a; }
double two_norm(double X[],unsigned n)
{
	double ans = 0;
	if (n == 0)return ans;
	double small = 0, medium = 0, big = 0;
	re(i,n)
	{
		if (X[i] > B)big += sqr(X[i]/S);
		else if (X[i] < b) small += sqr(X[i] / s);
		else medium += sqr(X[i]);
	}
	double min = 0, max = 0;

	if(big!=0)
	{	
		if (sqrt(big) > R / S)
			return numeric_limits<double>::infinity();
		if(medium!=0)
		{
			if (sqrt(medium) < S*sqrt(big))
				min = sqrt(medium), max = S*sqrt(big);
			else
				min = S*sqrt(big), max = sqrt(medium);
		}
		else return S*sqrt(big);
	}
	else if(small!=0)
	{
		if (medium != 0)
		{
			if (sqrt(medium) < s*sqrt(small))
				min = sqrt(medium), max = s*sqrt(small);
			else
				min = s*sqrt(small), max = sqrt(medium);
		}
		else return s*sqrt(small);
	}
	else return sqrt(medium);
	if (min < max*E) return max;
	return max*sqrt(1 + sqr(min / max));

}
/*Sample Input*/
/*
4
1.29e+308  123 1.18e+308 1
4
1.29e-308  1.18e-308 1.18e-308 1.18e-308
*/

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
		initial();
		/*������*/
		unsigned n;
		cin >> n;
		double* x = new double[n];
		re(i, n)
			cin >> x[i];
		cout <<setprecision(16)<< two_norm(x, n);
	}
	catch (const char * error) { cout << error << endl; }
	cout << "����ʱ�䣺" << clock() - BeginTime << endl;
#ifndef DEBUG
	system("pause");
#endif // !DEBUG
	return 0;
}