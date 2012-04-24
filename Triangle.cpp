//---------------------------------------------------------------------------
#pragma hdrstop

#include "Triangle.h"
#include "Matrix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void Triangle::applyTransform(Matrix *transform)
{
	a->applyTransform(transform);
	b->applyTransform(transform);
	c->applyTransform(transform);
}
//---------------------------------------------------------------------------
void Triangle::applyRotation(const double ax, const double ay)
{
	a->applyRotation(ax, ay);
	b->applyRotation(ax, ay);
	c->applyRotation(ax, ay);
}
//---------------------------------------------------------------------------
void Triangle::draw(TCanvas *)
{

}
//---------------------------------------------------------------------------
