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
		Vertice (const double, const double, const double, const UnicodeString&);
		Vertice (const Vertice&);
		~Vertice();

		inline double getX() const;
		inline double getY() const;
		inline double getZ() const;
		inline double getAug() const;

		inline void setX(const double);
		inline void setY(const double);
		inline void setZ(const double);
		inline void setAug(const double);

		inline void applyTransform (Matrix*);
		inline void applyRotation (const double, const double);

		UnicodeString tag;
};
//---------------------------------------------------------------------------
Vertice::Vertice (const double x, const double y, const double z, const UnicodeString& _tag)
	: tag(_tag)
{
	coords = new Matrix(1, 4);
	setX(x);
	setY(y);
	setZ(z);
	setAug(1);
}

Vertice::Vertice (const Vertice& src)
	: tag(src.tag)
{
	coords = new Matrix(*src.coords);
}

Vertice::~Vertice()
{
	delete coords;
}

inline double Vertice::getX() const { return coords->values[0][0]; }
inline double Vertice::getY() const { return coords->values[0][1]; }
inline double Vertice::getZ() const { return coords->values[0][2]; }
inline double Vertice::getAug() const { return coords->values[0][3]; }

inline void Vertice::setX(const double value) { coords->values[0][0] = value; }
inline void Vertice::setY(const double value) { coords->values[0][1] = value; }
inline void Vertice::setZ(const double value) { coords->values[0][2] = value; }
inline void Vertice::setAug(const double value) { coords->values[0][3] = value; }

inline void Vertice::applyTransform (Matrix* transform)
{
	*coords *= *transform;
}

inline void Vertice::applyRotation (const double phi, const double theta)
{
	const double cx = getX();
	const double cy = getY();
	const double cz = getZ();

	setX(cx * cos(theta) - (cz * cos(phi) - cy * sin(phi)) * sin(theta));
	setY(cy * cos(phi) + cz * sin(phi));
	setZ(cos(theta) * (cz * cos(phi) - cy * sin(phi)) + cx * sin(theta));
}
#endif
