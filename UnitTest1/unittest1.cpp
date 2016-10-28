#include "stdafx.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
double x_n(double x, int n)
{
	double ans = 1;
	re(i, n)
		ans *= x;
	return ans;
}
void debug(const char * errorInfo)
{
	Logger::WriteMessage(errorInfo);
	Assert::Fail();
}
namespace UnitTest1
{		
	extern unsigned thread_num;
	TEST_CLASS(Matrix_QR)
	{
	public:
		TEST_METHOD(basic)
		{
			fstream in("in.txt", ios::in);
			fstream out("out.txt", ios::out);
			Matrix<double> b, A;
			in >> A>>b;
			out << A << endl << b << endl;
			in.close();
			out.close();
		}
		TEST_METHOD(A_equal_QR_withHouseholder)
		{
			fstream in("in.txt", ios::in);
			fstream out("out.txt", ios::out);
			Matrix<double> b, A;
			in >> A >> b;
			Matrix<double> q, r;
			A.qr(q, r);
			Matrix<double> ans = (A - q*r);
			re(i,ans.Row())
				re(j,ans.Col())
					if(abs(ans[i][j])>1e-10)
					{
						out << ans;
						Assert::Fail();
					}
			in.close();
			out.close();
		}
		TEST_METHOD(QTQ_equal_I)
		{
			fstream in("in.txt", ios::in);
			fstream out("out.txt", ios::out);
			Matrix<double> b, A;
			in >> A >> b;
			Matrix<double> q, r;
			A.qr(q, r);
			Matrix<double> ans = (q.transform()*q);
			re(i, ans.Row())
				re(j, ans.Col())
			{
				if (((i == j)&&(abs(abs(ans[i][i])-1)>1e-10))
					||((i!=j)&&(abs(ans[i][j]) > 1e-10)))
					{
						out << ans;
						Assert::Fail();
					}
			}
			in.close();
			out.close();
		}
		TEST_METHOD(Ans_Matrix)
		{
			fstream in("in.txt", ios::in);
			fstream out("out.txt", ios::out);
			Matrix<double> b, A;
			in >> A >> b;
			Matrix<double> q, r;
			A.qr(q, r);
			Matrix<double> ans = r.inverse()*q.transform() - (A.transform()*A).inverse()*A.transform();
			re(i, ans.Row())
				re(j, ans.Col())
			{
				if (abs(ans[i][j])>1e-10) 
				{
					out << ans;
					Assert::Fail();
				}
			}
			in.close();
			out.close();
		}		
		TEST_METHOD(Householder_GramSchmidt)
		{
			fstream in("in.txt", ios::in);
			fstream out("out.txt", ios::out);
			Matrix<double> b, A;
			in >> A >> b;
			Matrix<double> q, r, Q, R;
			A.qr(q, r);
			A.QR(Q, R);
			Matrix<double> ans = r.inverse()*q.transform() - R.inverse()*Q.transform();
			re(i, ans.Row())
				re(j, ans.Col())
			{
				if (abs(ans[i][j])>1e-10)
				{
					out << ans;
					Assert::Fail();
				}
			}
			in.close();
			out.close();
		}
		TEST_METHOD(Polyfit)
		{
			fstream in("in.txt", ios::in);
			fstream out("out.txt", ios::out);
			Matrix<double> b, A;
			in >> A >> b;
			Matrix<double> q, r;
			re(i,A.Row())
				re(j,A.Col())
					A[i][j] = x_n(i + 1, j);
			A.qr(q, r);
			auto ans = r.inverse()*q.transform()*b;
			double ANS[4] = {
				15.6,
				-17.1190476190476,
				6.21428571428573,
				-0.666666666666668
			};
			re(i,4)
				if(abs(ans[i][0]-ANS[i])>1e-13)
				{
					out << ans << endl;
					Assert::Fail();
				}
			in.close();
			out.close();
		}
		TEST_METHOD(Polyfit_direct)
		{
			fstream in("in.txt", ios::in);
			fstream out("out.txt", ios::out);
			Matrix<double> b, A;
			in >> A >> b;
			Matrix<double> q, r;
			re(i, A.Row())
				re(j, A.Col())
				A[i][j] = x_n(i + 1, j);
			auto ans = A.qr(b);
			double ANS[4] = {
				15.6,
				-17.1190476190476,
				6.21428571428573,
				-0.666666666666668
			};
			re(i, 4)
				if (abs(ans[i][0] - ANS[i])>1e-13)
				{
					out << ans << endl;
					Assert::Fail();
				}
			in.close();
			out.close();
		}
	};
}