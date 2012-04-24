//---------------------------------------------------------------------------
#ifndef TriangleH
#define TriangleH

#include "Object3D.h"
#include "Vertice.h"
//---------------------------------------------------------------------------
class Matrix;

class Triangle : virtual public Object3D
{
	public :
		Triangle() {}
		Triangle(const Triangle&);
		~Triangle();

		void applyTransform(Matrix *);
		void applyRotation(const double, const double);
		void draw(TCanvas *);

		Vertice *a;
		Vertice *b;
		Vertice *c;
};
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
#endif
