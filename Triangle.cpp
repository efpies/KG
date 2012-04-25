//---------------------------------------------------------------------------
#pragma hdrstop

#include "Triangle.h"
#include "Matrix.h"

#include <cstdlib>

#include "Constants.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Custom methods
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
void Triangle::draw(TCanvas *canvas, float **zBuffer, TColor frontColor, TColor backColor)
{
	TPoint canvasCenter = canvas->ClipRect.CenterPoint();

	double tri[3][3];

	tri[0][0] = a->getX();
	tri[0][1] = a->getY();
	tri[0][2] = a->getZ();
	normalized(canvasCenter, tri[0][0], tri[0][1]);

	tri[1][0] = b->getX();
	tri[1][1] = b->getY();
	tri[1][2] = b->getZ();
	normalized(canvasCenter, tri[1][X], tri[1][Y]);

	tri[2][0] = c->getX();
	tri[2][1] = c->getY();
	tri[2][2] = c->getZ();
	normalized(canvasCenter, tri[2][X], tri[2][Y]);

	double head[3] = {a->getX(),
					  a->getY(),
					  a->getZ() };

	normalized(canvasCenter, head[X], head[Y]);

	double second[3] = {b->getX(),
						b->getY(),
						b->getZ() };

	normalized(canvasCenter, second[X], second[Y]);

	double third[3] = {c->getX(),
					   c->getY(),
					   c->getZ() };

	normalized(canvasCenter, third[X], third[Y]);

	double *vecA;
	double *vecB;

	vecA = makeVector(head, second);
	vecB = makeVector(head, third);

	double *cross = crossProduct(vecA, vecB);

	bool isFront = cross[Z] >= head[Z];

	delete [] vecA;
	delete [] vecB;
	delete [] cross;

	sort(tri, 1);

	double *p1 = tri[0];
	double *p2 = tri[1];
	double *p3 = tri[2];
	double *p4 = p1;

	for(int y = tri[0][Y]; y <= tri[2][Y]; ++y) {
		if(y >= 0 && y <= canvas->ClipRect.Height()) {
			if(y > p2[Y]) {
				p4 = p3;
			}

			if(p2[Y] - p4[Y] && p3[Y] - p1[Y]) {
				double xa;
				double xb;
				double za;
				double zb;

				xa = p4[X] + (p2[X] - p4[X]) * (y - p4[Y]) / (p2[Y] - p4[Y]);
				xb = p1[X] + (p3[X] - p1[X]) * (y - p1[Y]) / (p3[Y] - p1[Y]);
				za = p4[Z] + (p2[Z] - p4[Z]) * (y - p4[Y]) / (p2[Y] - p4[Y]);
				zb = p1[Z] + (p3[Z] - p1[Z]) * (y - p1[Y]) / (p3[Y] - p1[Y]);

				if(xa > xb) {
					std::swap(xa, xb);
				}

				for(int x = xa; x <= xb; ++x) {
					if(canvas->ClipRect.Contains(TPoint(x, y))) {
						if(xb - xa) {
							double z = za + (zb - za) * (x - xa) / (xb - xa);

							if(z > zBuffer[y - 1][x - 1]) {
								zBuffer[y - 1][x - 1] = z;
								canvas->Pixels[x][y] = isFront ? frontColor : backColor;
							}
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void Triangle::sort(double array[3][3], unsigned by)
{
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			if(array[j][by] > array[j + 1][by]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}
//---------------------------------------------------------------------------
