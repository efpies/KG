//---------------------------------------------------------------------------
#pragma hdrstop

#pragma warn -8123

#include "Matrix.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Helpers.h"

using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)

Matrix::Matrix (unsigned r, unsigned c)
	: values(matrix_values(r, vector<double>(c, 0)))
{ }

Matrix::Matrix(const Matrix& src)
	: values(src.values)
{ }

void Matrix::print()
{
	puts("");

	for (mvIt i = values.begin(); i != values.end(); ++i, puts(""))
		for (dIt j = (*i).begin(); j != (*i).end(); ++j)
			printf("%.2lf ", *j);
}

void Matrix::fillWithValue(const double value)
{
	for (mvIt i = values.begin(); i != values.end(); ++i)
		for (dIt j = (*i).begin(); j != (*i).end(); ++j)
			*j = value;
}

void Matrix::fillDiagWithValue (const double value)
{
	for (unsigned i = 0; i < values.size(); ++i)
		values[i][i] = value;
}

Matrix& Matrix::operator=(const Matrix& right)
{
	if (&right != this)
	{
		values = right.values;
	}

	return *this;
}

Matrix operator+ (const Matrix& left, const Matrix& right)
{
	Matrix result(left);
	return result += right;
}

Matrix& Matrix::operator+=(const Matrix& right)
{
	if (rows() == right.rows() && cols() == right.cols())
	{
		for (unsigned i = 0; i < rows(); ++i)
			for (unsigned j = 0; j < cols(); ++j)
				values[i][j] += right.values[i][j];
	}

	return *this;
}

Matrix operator* (const Matrix& left, const Matrix& right)
{
	Matrix result(left);
	return result *= right;
}

Matrix& Matrix::operator*=(const Matrix& right)
{
	if (cols() == right.rows())
	{
		Matrix temp(rows(), right.cols());

		for (unsigned i = 0; i < rows(); ++i)
			for (unsigned j = 0; j < right.cols(); ++j)
				for (unsigned k = 0; k < right.rows(); ++k)
					temp.values[i][j] += values[i][k] * right.values[k][j];

		values = temp.values;
	}

	return *this;
}

Matrix operator* (const Matrix& left, const double right)
{
	Matrix result(left);
	return (result *= right);
}

Matrix operator* (const double left, const Matrix& right)
{
	Matrix result(right);
	return (result *= left);
}

Matrix& Matrix::operator*= (const double right)
{
	for (mvIt i = values.begin(); i != values.end(); ++i)
		for (dIt j = (*i).begin(); j != (*i).end(); ++j)
			*j *= right;

	return *this;
}

//double* Matrix::operator[] (const unsigned index)
//{
//	return values[index];
//}
void Matrix::Transpose ()
{
	matrix_values newvalues = matrix_values(cols(), vector<double>(rows(), 0));

	for (unsigned i = 0; i < cols(); i++)
		for (unsigned j = 0; j < rows(); j++)
			newvalues[i][j] = values[j][i];

	values = newvalues;
}

Matrix Matrix::getTransposed ()
{
	Matrix result(*this);
	result.Transpose();
	return result;
}

Matrix operator- (const Matrix& left, const Matrix& right)
{
	Matrix result(left);
	return result -= right;
}

Matrix& Matrix::operator-=(const Matrix& right)
{
	return *this += (-1)*right;
}

Matrix operator^ (const Matrix& left, const double right)
{
	Matrix result(left);
	return (result ^= right);
}

Matrix& Matrix::operator^= (const double right)
{
	for (mvIt i = values.begin(); i != values.end(); ++i)
		for (dIt j = (*i).begin(); j != (*i).end(); ++j)
			*j = pow(*j, right);

	return *this;
}
