//---------------------------------------------------------------------------
#ifndef TriangleH
#define TriangleH

#include "Object3D.h"
#include "Vertice.h"

#define _X 0
#define _Y 1
#define _Z 2
//---------------------------------------------------------------------------
class Matrix;

struct vector3D {
	double x;
	double y;
	double z;
};

class Triangle : virtual public Object3D
{
	private :
		inline void normalized(TPoint, double &, double &);
		inline void makevector3D(const vector3D, const vector3D, vector3D &);
		inline void crossProduct(const vector3D, const vector3D, vector3D &);
		inline void swap(double *, double *);

		void sort(double [3][3], unsigned);
		inline double dotProduct(const vector3D, const vector3D);
		inline double vectorLength(const vector3D);
		inline double angle(const vector3D, const vector3D);
		inline void   normalizeVec(vector3D &);

	public :
		Triangle() {}
		Triangle(const Triangle&);
		~Triangle();

		inline void applyTransform(Matrix *);
		inline void applyRotation(const double, const double);
		void draw(Graphics::TBitmap *) {}

		void draw(Graphics::TBitmap *, float **, TColor, TColor);

		Vertice *av;
		Vertice *bv;
		Vertice *cv;
};
//---------------------------------------------------------------------------
// Lifecycle
//---------------------------------------------------------------------------
Triangle::Triangle(const Triangle &src)
{
	av = new Vertice(*src.av);
	bv = new Vertice(*src.bv);
	cv = new Vertice(*src.cv);
}
//---------------------------------------------------------------------------
Triangle::~Triangle()
{
	delete av;
	delete bv;
	delete cv;
}
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
inline void Triangle::makevector3D(const vector3D a, const vector3D b, vector3D &result)
{
	result.x = b.x - a.x;
	result.y = b.y - a.y;
	result.z = b.z - a.z;
}
//---------------------------------------------------------------------------
inline void Triangle::crossProduct(const vector3D a, const vector3D b, vector3D &result)
{
	result.x = a.y * b.z - a.z * b.y;
	result.y = -a.x * b.z + a.z * b.x;
	result.z = a.x * b.y - a.y * b.x;
}
//---------------------------------------------------------------------------
inline void Triangle::normalized(TPoint center, double &x, double &y)
{
	x = center.x + x * scale;
	y = center.y - y * scale;
}
//---------------------------------------------------------------------------
inline void Triangle::swap(double *a, double *b)
{
	double t[3];
	t[_X] = a[_X];
	t[_Y] = a[_Y];
	t[_Z] = a[_Z];

	a[_X] = b[_X];
	a[_Y] = b[_Y];
	a[_Z] = b[_Z];

	b[_X] = t[_X];
	b[_Y] = t[_Y];
	b[_Z] = t[_Z];
}
//---------------------------------------------------------------------------
inline double Triangle::dotProduct(const vector3D a, const vector3D b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
//---------------------------------------------------------------------------
inline double Triangle::vectorLength(const vector3D v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
//---------------------------------------------------------------------------
inline double Triangle::angle(const vector3D a, const vector3D b)
{
	return acos(dotProduct(a, b) / (vectorLength(a) * vectorLength(b)));
}
//---------------------------------------------------------------------------
inline void Triangle::normalizeVec(vector3D &v)
{
	double length = vectorLength(v);
	length = (length) ? length : 0.00001;
	v.x /= length;
	v.y /= length;
	v.z /= length;
}
//---------------------------------------------------------------------------
inline void Triangle::applyTransform(Matrix *transform)
{
	av->applyTransform(transform);
	bv->applyTransform(transform);
	cv->applyTransform(transform);
}
//---------------------------------------------------------------------------
inline void Triangle::applyRotation(const double ax, const double ay)
{
	av->applyRotation(ax, ay);
	bv->applyRotation(ax, ay);
	cv->applyRotation(ax, ay);
}
//---------------------------------------------------------------------------
#endif
