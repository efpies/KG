//---------------------------------------------------------------------------
#ifndef BezierSurfaceH
#define BezierSurfaceH
//---------------------------------------------------------------------------
#include "GraphicObject.h"
#include "Edge.h"
#include "CustomPoint.h"
#include "Matrix.h"
#include <cstdlib>

#include <vector>
using namespace std;

typedef vector< vector<double> > matrix_values;
typedef vector< vector<double> >::iterator mvIt;
typedef vector<double>::iterator dIt;

typedef vector< vector<CustomPoint *> > points_container;
typedef vector< vector<CustomPoint *> >::iterator poIt;
typedef vector<CustomPoint *>::iterator pIt;

class BezierSurface {
	private :
		GraphicObject *grid;
		GraphicObject *surface;

		points_container knots;
		points_container points;

	public :
		BezierSurface(unsigned, unsigned);
		BezierSurface(const BezierSurface&);
		~BezierSurface();

		void applyTransform(Matrix*);
		void applyRotation (const double, const double);
		void draw (TCanvas*);

		static Matrix *getU (double, int);
		static Matrix *getN (int);
		static Matrix *getW (double, int);
};

BezierSurface::BezierSurface(const BezierSurface& src)
{
	grid = new GraphicObject(*src.grid);
	surface = new GraphicObject(*src.surface);
//	knots = src.knots;
}

BezierSurface::~BezierSurface()
{
	delete grid;
	delete surface;
}
//---------------------------------------------------------------------------
#endif
