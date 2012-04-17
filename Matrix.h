//---------------------------------------------------------------------------
#ifndef MatrixH
#define MatrixH

#include <vector>
#include "Constants.h"
//---------------------------------------------------------------------------
using namespace std;

class Matrix {
	protected :
		void alloc();
		void dealloc();

	public :
		Matrix (unsigned, unsigned);
		Matrix (const Matrix&);

		void fillWithValue(const double);
 inline void fillWithZeros();
		void fillDiagWithValue (const double);

		void   Transpose    ();
 inline	Matrix getTransposed();

		Matrix& operator=  (const Matrix&);
		Matrix& operator+= (const Matrix&);
		Matrix& operator-= (const Matrix&);
		Matrix& operator*= (const Matrix&);
		Matrix& operator*= (const double);
		Matrix& operator^= (const double);
 friend Matrix  operator+  (const Matrix&, const Matrix&);
 friend Matrix  operator-  (const Matrix&, const Matrix&);
 friend Matrix  operator*  (const Matrix&, const Matrix&);
 friend Matrix  operator*  (const Matrix&, const double);
 friend Matrix  operator*  (const double, const Matrix&);
 friend Matrix  operator^  (const Matrix&, const double);
		double* operator[] (const unsigned);

		matrix_values values;

		inline unsigned rows() const;
		inline unsigned cols() const;
};
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
inline unsigned Matrix::rows() const { return values.size(); }
//---------------------------------------------------------------------------
inline unsigned Matrix::cols() const { return values[0].size(); }
//---------------------------------------------------------------------------
inline void Matrix::fillWithZeros() { fillWithValue(0); }
//---------------------------------------------------------------------------
// Transformations
//---------------------------------------------------------------------------
inline Matrix Matrix::getTransposed ()
{
	Matrix result(*this);
	result.Transpose();
	return result;
}
//---------------------------------------------------------------------------
#endif
