//---------------------------------------------------------------------------
#ifndef CustomPointH
#define CustomPointH

#include "Matrix.h"
#include "Helpers.h"
#include <vcl.h>

class CustomPoint {
	private :

	public :
		Matrix *coords;
		CustomPoint (const double, const double, const double);
		CustomPoint (const CustomPoint&);
		~CustomPoint();

		inline double getX ();
		inline double getY ();
		inline double getZ ();

		inline void applyTransform (Matrix*);
		inline void applyRotation (const double, const double);
};
//---------------------------------------------------------------------------
CustomPoint::CustomPoint (const double x, const double y, const double z)
{
	coords = new Matrix(1, 4);
	coords->values[0][0] = x;
	coords->values[0][1] = y;
	coords->values[0][2] = z;
	coords->values[0][3] = 1;
}

CustomPoint::CustomPoint (const CustomPoint& src)
{
	coords = new Matrix(*src.coords);
}

CustomPoint::~CustomPoint()
{
	delete coords;
}

inline double CustomPoint::getX () { return coords->values[0][0]; }
inline double CustomPoint::getY () { return coords->values[0][1]; }
inline double CustomPoint::getZ () { return coords->values[0][2]; }

inline void CustomPoint::applyTransform (Matrix* transform)
{
	*coords *= *transform;
}

inline void CustomPoint::applyRotation (const double phi, const double theta)
{
	double cx = coords->values[0][0];
	double cy = coords->values[0][1];
	double cz = coords->values[0][2];

	coords->values[0][0] = cx*cos(phi)+cz*sin(phi);
	coords->values[0][1] = cx*sin(phi)*sin(theta)+cy*cos(theta)-cz*cos(phi)*sin(theta);
	coords->values[0][2] = 0;
}
#endif
