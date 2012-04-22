//---------------------------------------------------------------------------
#ifndef BezierSurfaceH
#define BezierSurfaceH
//---------------------------------------------------------------------------
#include "GraphicObject.h"
#include "Edge.h"
#include "Vertice.h"
#include "Matrix.h"
#include <cstdlib>

#include <map>

#include "Constants.h"
//---------------------------------------------------------------------------
using namespace std;

class BezierSurface
{
	private :
		GraphicObject *grid;
		vector<GraphicObject *> surface;

		const unsigned ptsPerUnit;

		static Matrix *getU(double, int);
		static Matrix *getN(int);
		static Matrix *getW(double, int);

		static inline long fact(int);
		static inline unsigned Binom(int, int);

		static inline UnicodeString tagWithName(const wchar_t *, int, int);

	public :
		BezierSurface(const unsigned, const unsigned, const unsigned, const bool);
		BezierSurface(const BezierSurface&);
		~BezierSurface();

		void applyTransform(Matrix *);
		void applyRotation(const double, const double);
		void draw(TCanvas *);

		bool gridHidden;
};
//---------------------------------------------------------------------------
// Helpers
//---------------------------------------------------------------------------
inline UnicodeString BezierSurface::tagWithName(const wchar_t *name, int i, int j)
{
	UnicodeString tag = L"";
	tag.printf(L"%s{%d;%d}", name, i, j);
	return tag;
}
//---------------------------------------------------------------------------
inline long BezierSurface::fact(int n)
{
	return n == 0L ? 1L : n * fact (n - 1);
}
//---------------------------------------------------------------------------
inline unsigned BezierSurface::Binom(int n, int i)
{
	return fact(n)/(fact(i) * fact(n - i));
}
//---------------------------------------------------------------------------
#endif
