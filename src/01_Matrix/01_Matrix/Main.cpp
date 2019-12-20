#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>

#include "TMatrix.h"

using namespace std;

void main()
{
	TVector<int> v1(6), v2(5), v3(6);
	TMatrix<int> A(5), B(3), C(5);

	//Vectors filling and output

	srand((unsigned int)time(NULL));

	for (int i = 0; i < v1.GetSize(); i++)
		v1[i] = rand() % 10 + 1;

	for (int i = 0; i < v2.GetSize(); i++)
		v2[i] = rand() % 10 + 1;

	for (int i = 0; i < v3.GetSize(); i++)
		v3[i] = rand() % 10 + 1;

	try
	{
		cout << "        Vectors" << endl << endl;
		cout << " v1 = " << v1 << endl;
		cout << " v2 = " << v2 << endl;
		cout << " v3 = " << v3 << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	cout << "        Vector Test" << endl << endl;

	try
	{
		cout << " v1 + 5 = ";
		cout << v1 + 5 << endl << endl;
		cout << " v2 - 7 = ";
		cout << v2 - 7 << endl << endl;
		cout << " v3 * 9 = ";
		cout << v3 * 9 << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << " v1 + v3 = ";
		cout << v1 + v3 << endl << endl;
		cout << " v1 + v2 = ";
		cout << v1 + v2 << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << " v1 - v3 = ";
		cout << v1 - v3 << endl << endl;
		cout << " v1 - v2 = ";
		cout << v1 - v2 << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << " v1 * v3 = ";
		cout << v1 * v3 << endl << endl;
		cout << " v1 * v2 = ";
		cout << v1 * v2 << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << "        Length of vectors" << endl << endl;
		cout << " |v1| = ";
		cout << v1.Length() << endl << endl;
		cout << " |v2| = ";
		cout << v2.Length() << endl << endl;
		cout << " |v3| = ";
		cout << v3.Length() << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << "        Vector Comparison:" << endl;
		cout << "Comment:" << endl;
		cout << "If the answer is true then 1 otherwise 0!" << endl << endl;
		cout << "v1 == v2 ? : ";
		cout << (v1 == v2) << endl << endl;
		cout << "v2 == v3 ? : ";
		cout << (v3 == v3) << endl << endl;
		cout << "v1 != v3 ? : ";
		cout << (v1 != v3) << endl << endl;
		cout << "v2 != v2 ? : ";
		cout << (v2 != v2) << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << "        Vector Copy" << endl << endl;
		cout << " Vector v1: " << endl;
		cout << v1 << endl << endl;
		cout << " Vector v4(v1): " << endl;
		TVector<int> v4(v1);
		cout << v4 << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	cout << "   The End of Vector Test" << endl << endl;
	cout << "///////////////////////////////////////" << endl << endl;

	//Matrix filling and output

	for (int i = 0; i < A.GetSize(); i++)
		for (int j = 0; j < A.GetSize() - i; j++)
			A[i][j] = rand() % 10 + 1;

	for (int i = 0; i < B.GetSize(); i++)
		for (int j = 0; j < B.GetSize() - i; j++)
			B[i][j] = rand() % 10 + 1;

	for (int i = 0; i < C.GetSize(); i++)
		for (int j = 0; j < C.GetSize() - i; j++)
			C[i][j] = rand() % 10 + 1;

	try
	{

		cout << "        Matrices:" << endl;
		cout << " Matrix A:" << endl;
		cout << A << endl;
		cout << " Matrix B:" << endl;
		cout << B << endl;
		cout << " Matrix C:" << endl;
		cout << C << endl << endl;

	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	cout << "        Matrix Test" << endl << endl;

	try
	{
		cout << " A + B:" << endl;
		cout << A + B << endl << endl;
		cout << " A + C:" << endl;
		cout << A + C << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << " A - B:" << endl;
		cout << A - B << endl << endl;
		cout << " A - C:" << endl;
		cout << A - C << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << " A * C:" << endl;
		cout << A * C << endl << endl;
		cout << " B * C:" << endl;
		cout << B * C << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << " A + 5:" << endl;
		cout << A + 5 << endl << endl;
		cout << " B - 3:" << endl;
		cout << B - 3 << endl << endl;
		cout << " C * 10:" << endl;
		cout << C * 10 << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << " A * v1:" << endl;
		cout << A * v1 << endl << endl;
		cout << " A * v2:" << endl;
		cout << A * v2 << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << "        Matrix Copy" << endl << endl;
		cout << " Matrix A: " << endl;
		cout << A << endl << endl;
		cout << " Matrix D(A): " << endl;
		TMatrix<int> D(A);
		cout << D << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	try
	{
		cout << "        Matrix Comparison:" << endl;
		cout << "Comment:" << endl;
		cout << "If the answer is true then 1 otherwise 0!" << endl << endl;
		cout << "A == B ? : ";
		cout << (A == B) << endl << endl;
		cout << "A == A ? : ";
		cout << (A == A) << endl << endl;
		cout << "A != B ? : ";
		cout << (A != B) << endl << endl;
	}
	catch (Exception exc)
	{
		cout << exc.what() << endl << endl;
	}

	int c = _getch();
}