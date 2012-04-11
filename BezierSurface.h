//---------------------------------------------------------------------------
#ifndef BezierSurfaceH
#define BezierSurfaceH
//---------------------------------------------------------------------------
#include "GraphicObject.h"
#include "Edge.h"
#include "Vertice.h"
#include "Matrix.h"
#include <cstdlib>

#include <vector>
#include <map>

#include "Constants.h"

using namespace std;

class BezierSurface {
	private :
		GraphicObject *grid;
		GraphicObject *surface;

		map<UnicodeString, Vertice *> allVertices;

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
}

BezierSurface::~BezierSurface()
{
	delete grid;
	delete surface;
}
//---------------------------------------------------------------------------
#endif
