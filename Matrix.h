//---------------------------------------------------------------------------
#ifndef MatrixH
#define MatrixH

#include <vector>
using namespace std;

typedef vector< vector<double> > matrix_values;
typedef vector< vector<double> >::iterator mvIt;
typedef vector<double>::iterator dIt;
//---------------------------------------------------------------------------
class Matrix {
	protected :
		void alloc();
		void dealloc();

	public :
		Matrix (unsigned, unsigned);
		Matrix (const Matrix&);

		void print();
		void fillWithValue(const double);
 inline void fillWithZeros();
		void fillDiagWithValue (const double);

		void   Transpose    ();
		Matrix getTransposed();

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
inline unsigned Matrix::rows() const { return values.size(); }
inline unsigned Matrix::cols() const { return values[0].size(); }
inline void Matrix::fillWithZeros() { fillWithValue(0); }
#endif
