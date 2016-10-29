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
	const double MAX_ERROR = 1e-10;
	extern unsigned thread_num;
	TEST_CLASS(Matrix_QR)
	{
	public:
		TEST_METHOD(HelloWorld)
		{
			fstream in("in.txt", ios::in);
			fstream out("out.txt", ios::out);
			Matrix<double> b, A;
			in >> A>>b;
			out << A << endl << b << endl;
			in.close();
			out.close();
		}
		TEST_METHOD(HouseholderQR�ֽ��Ƿ���A���)
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
					if(abs(ans[i][j])>MAX_ERROR)
					{
						out << ans;
						Assert::Fail();
					}
			in.close();
			out.close();
		}
		TEST_METHOD(Q�Ƿ�Ϊ������)
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
				if (((i == j)&&(abs(abs(ans[i][i])-1)>MAX_ERROR))
					||((i!=j)&&(abs(ans[i][j]) > MAX_ERROR)))
					{
						out << ans;
						Assert::Fail();
					}
			}
			in.close();
			out.close();
		}
		TEST_METHOD(Householder����ͨ���Ա�)
		{
			try
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
					if (abs(ans[i][j]) > MAX_ERROR)
					{
						out << ans;
						Assert::Fail();
					}
				}
				in.close();
				out.close();
			}
			catch (const char * error) { debug(error); }

		}		
		TEST_METHOD(Householder��GramSchmidt�Ա�)
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
				if (abs(ans[i][j])>MAX_ERROR)
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
	TEST_CLASS(��ͨ����)
	{
	public:
		TEST_METHOD(inverse)
		{
			fstream out("out.txt", ios::out);
			const unsigned n = 34;
			Matrix<double> A(n, n);
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
			re(i, n)
				re(j, n)
				if ((i == j && !(abs(ans[i][i]-1)<MAX_ERROR)
					|| (i != j && !(abs(ans[i][j])<MAX_ERROR))))
				{
					out << A.inverse() << endl << ans << endl;
					Assert::Fail();
				}

			out.close();
		}
		TEST_METHOD(random_inverse)
		{
			fstream out("out.txt", ios::out);
			srand(time(nullptr));//ÿ�ζ���ͬһ������
			const unsigned Test_size = 50;
			const unsigned Test_case = 100;
			Matrix<double> A(Test_size, Test_size);
			Matrix<double> b(Test_size, 1);
			re(t, Test_case)
			{
				re(i, Test_size)
				{
					b[i][0] = rand() % (Test_size);
					re(j, Test_size)
						A[i][j] = rand() % (Test_size);
				}
				auto ans = A.inverse()*b;
				auto delta = A*ans - b;
				re(i, delta.Row())
				{
					if (abs(delta[i][0]) > MAX_ERROR)
					{
						out << "test_case: " << t << endl;
						out << A << endl << b << endl << ans << endl << A*ans << endl << delta << endl;
						Assert::Fail();
					}
				}
			}
			out.close();
		}
		TEST_METHOD(solve)
		{
			fstream out("out.txt", ios::out);
			const unsigned n = 54;
			Matrix<double> A(n, n);
			Matrix<double> B(n, 1);
			B[0][0] = 7;
			re(i, n)
			{
				A[i][i] = 6;
				if (i > 0)
				{
					A[i - 1][i] = 1;
					A[i][i - 1] = 8;
					B[0][i] = 15;
				}
			}
			B[0][n - 1] = 14;
			auto ans = A.solve(B);
			re(i, ans.Row())
			{
				if (!(abs(ans[i][0]-1)<MAX_ERROR))
				{
					out << ans << endl;
					Assert::Fail();
				}

			}
			out.close();
		}
		TEST_METHOD(random_solve)
		{
			fstream out("out.txt", ios::out);
			//srand(time(nullptr));//ÿ�ζ���ͬһ������
			const unsigned Test_size = 100;
			const unsigned Test_case = 100;
			Matrix<double> A(Test_size, Test_size);
			Matrix<double> b(Test_size, 1);
			re(t, Test_case)
			{
				re(i, Test_size)
				{
					b[i][0] = rand() % (Test_size);
					re(j, Test_size)
						A[i][j] = rand() % (Test_size);
				}
				auto ans = A.solve(b);
				auto delta = A*ans - b;
				re(i, delta.Row())
				{
					if (abs(delta[i][0]) > MAX_ERROR)
					{
						out << "test_case: " << t << endl;
						out << A << endl << b << endl << ans << endl << A*ans << endl << delta << endl;
						Assert::Fail();
					}
				}
			}
			out.close();
		}
		TEST_METHOD(LU_solve)
		{
			fstream out("out.txt", ios::out);
			const unsigned n = 54;
			Matrix<double> A(n, n);
			Matrix<double> B(n, 1);
			B[0][0] = 7;
			re(i, n)
			{
				A[i][i] = 6;
				if (i > 0)
				{
					A[i - 1][i] = 1;
					A[i][i - 1] = 8;
					B[0][i] = 15;
				}
			}
			B[0][n - 1] = 14;
			auto P = A.ChosenLU();
			auto ans = A.LU_solve(P*B);
			re(i, ans.Row())
			{
				if (!(abs(ans[i][0] - 1)<MAX_ERROR))
				{
					out << ans << endl;
					Assert::Fail();
				}

			}
			out.close();
		}
	};
	TEST_CLASS(�߾���)
	{
	public:
		TEST_METHOD(inverse)
		{
			fstream out("out.txt", ios::out);
			const unsigned n = 40;
			Matrix<q> A(n, n);
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
			re(i, n)
				re(j, n)
				if ((i == j && !(ans[i][i] == 1) 
					|| (i != j && !(ans[i][j] == 0))))
				{
					out << A.inverse()<< endl << ans << endl;
					Assert::Fail();
				}

			out.close();
		}
		TEST_METHOD(solve)
		{
			fstream out("out.txt", ios::out);
			const unsigned n = 40;
			Matrix<q> A(n, n);
			Matrix<q> B(n, 1);
			B[0][0] = 7;
			re(i, n)
			{
				A[i][i] = 6;
				if (i > 0)
				{
					A[i - 1][i] =1;
					A[i][i - 1] =8;
					B[0][i] = 15;
				}
			}
			B[0][n - 1] = 14;
			auto ans = A.solve(B);
			re(i,ans.Row())
			{
				if(!(ans[i][0]==1))
				{
					out << ans << endl;
					Assert::Fail();
				}
			}
			out.close();
		}
		TEST_METHOD(LU_solve)
		{
			fstream out("out.txt", ios::out);
			const unsigned n = 40;
			Matrix<q> A(n, n);
			Matrix<q> B(n, 1);
			B[0][0] = 7;
			re(i, n)
			{
				A[i][i] = 6;
				if (i > 0)
				{
					A[i - 1][i] = 1;
					A[i][i - 1] = 8;
					B[0][i] = 15;
				}
			}
			B[0][n - 1] = 14;
			auto P = A.ChosenLU();
			auto ans = A.LU_solve(P*B);
			re(i, ans.Row())
			{
				if (!(ans[i][0] == 1))
				{
					out << ans << endl;
					Assert::Fail();
				}
			}
			out.close();
		}

	};
}