//---------------------------------------------------------------------------
#ifndef VerticeH
#define VerticeH

#include "Matrix.h"
#include "DebugHelpers.h"
#include <vcl.h>

class Vertice {
	private :

	public :
		Matrix *coords;
		Vertice (const double, const double, const double);
		Vertice (const Vertice&);
		~Vertice();

		inline double getX ();
		inline double getY ();
		inline double getZ ();

		inline void applyTransform (Matrix*);
		inline void applyRotation (const double, const double);
};
//---------------------------------------------------------------------------
Vertice::Vertice (const double x, const double y, const double z)
{
	coords = new Matrix(1, 4);
	coords->values[0][0] = x;
	coords->values[0][1] = y;
	coords->values[0][2] = z;
	coords->values[0][3] = 1;
}

Vertice::Vertice (const Vertice& src)
{
	coords = new Matrix(*src.coords);
}

Vertice::~Vertice()
{
	delete coords;
}

inline double Vertice::getX () { return coords->values[0][0]; }
inline double Vertice::getY () { return coords->values[0][1]; }
inline double Vertice::getZ () { return coords->values[0][2]; }

inline void Vertice::applyTransform (Matrix* transform)
{
	*coords *= *transform;
}

inline void Vertice::applyRotation (const double phi, const double theta)
{
	double cx = coords->values[0][0];
	double cy = coords->values[0][1];
	double cz = coords->values[0][2];

	coords->values[0][0] = cx*cos(phi)+cz*sin(phi);
	coords->values[0][1] = cx*sin(phi)*sin(theta)+cy*cos(theta)-cz*cos(phi)*sin(theta);
	coords->values[0][2] = 0;
}
#endif
