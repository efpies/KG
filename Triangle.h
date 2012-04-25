//---------------------------------------------------------------------------
#ifndef TriangleH
#define TriangleH

#include "Object3D.h"
#include "Vertice.h"

#define X 0
#define Y 1
#define Z 2
//---------------------------------------------------------------------------
class Matrix;

class Triangle : virtual public Object3D
{
	private :
		inline void   normalized(TPoint, double &, double &);
		inline double *makeVector(double *, double *);
		inline double *crossProduct(double *, double *);
		inline void   swap(double *, double *);

		void sort(double [3][3], unsigned);

	public :
		Triangle() {}
		Triangle(const Triangle&);
		~Triangle();

		void applyTransform(Matrix *);
		void applyRotation(const double, const double);
		void draw(TCanvas *);

		void draw(TCanvas *, float **, TColor, TColor);

		Vertice *a;
		Vertice *b;
		Vertice *c;
};
//---------------------------------------------------------------------------
// Lifecycle
//---------------------------------------------------------------------------
Triangle::Triangle(const Triangle &src)
{
	a = new Vertice(*src.a);
	b = new Vertice(*src.b);
	c = new Vertice(*src.c);
}
//---------------------------------------------------------------------------
Triangle::~Triangle()
{
	delete a;
	delete b;
	delete c;
}
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
inline double *Triangle::makeVector(double *a, double *b)
{
	double *c = new double[3];
	c[0] = b[0] - a[0];
	c[1] = b[1] - a[1];
	c[2] = b[2] - a[2];
	return c;
}
//---------------------------------------------------------------------------
inline double *Triangle::crossProduct(double *a, double *b)
{
	double *cross = new double[3];
	cross[X] = a[Y] * b[Z] - a[Z] * b[Y];
	cross[Y] = -a[X] * b[Z] + a[Z] * b[X];
	cross[Z] = a[X] * b[Y] - a[Y] * b[X];
	return cross;
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
	t[X] = a[X];
	t[Y] = a[Y];
	t[Z] = a[Z];

	a[X] = b[X];
	a[Y] = b[Y];
	a[Z] = b[Z];

	b[X] = t[X];
	b[Y] = t[Y];
	b[Z] = t[Z];
}
//---------------------------------------------------------------------------
#endif
