//---------------------------------------------------------------------------
#pragma hdrstop

#include "BezierSurface.h"

#include <vcl.h>
#include <algorithm>
#include <vector>
#include <float.h>
#include <cstdlib>
#include "Triangle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define irand(n) random(n / 2.0) - random(n / 2.0)
#define knotTag(i, j) tagWithName(L"knot", i, j)
#define pointTag(i, j) tagWithName(L"point", i, j)

double dotProduct(double *a, double *b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

double angle(double *a, double *b)
{
	double dpa = dotProduct(a, a);
	dpa = (dpa) ? dpa : 0.00000001;
	double dpb = dotProduct(b, b);
	dpb = (dpb) ? dpb : 0.00000001;
	return acos(dotProduct(a, b) / sqrt(dpa * dpb));
}

double troj(Vertice *a, Vertice *b, Vertice *c)
{
	double first = a->getX() * (b->getY() * c->getZ() - c->getY() * b->getZ());
	double second = a->getY() * (b->getX() * c->getZ() - c->getX() * b->getZ());
	double third = a->getZ() * (b->getX() * c->getY() - c->getX() * b->getY());
	return first - second + third;
}

Vertice **SortDots(Vertice *a, Vertice *b, Vertice *c)
{
	Vertice *anew, *bnew, *cnew;

	if((a->getY()<=b->getY())&&(a->getY()<=c->getY()))
	{
		anew = a;
		if(b->getY()<=c->getY())
		{
			bnew = b;
			cnew = c;
		}
		else
		{
			bnew = c;
			cnew = b;
        }
	}
	else
	{
		if((b->getY()<=a->getY())&&(b->getY()<=c->getY()))
		{
			anew = b;
			if(a->getY()<=c->getY())
			{
				bnew = a;
				cnew = c;
			}
			else
			{
				bnew = c;
				cnew = a;
			}
		}
		else
		{
			anew = c;
			if(a->getY()<=b->getY())
			{
				bnew = a;
				cnew = b;
			}
			else
			{
				bnew = b;
				cnew = a;
            }
        }
	}

	a = anew;
	b = bnew;
	c = cnew;

	Vertice **lol = new Vertice*[3];
	lol[0] = a;
	lol[1] = b;
	lol[2] = c;
	return lol;
}
//---------------------------------------------------------------------------
// Lifecycle
//---------------------------------------------------------------------------
BezierSurface::BezierSurface(const BezierSurface& src)
	: gridHidden(src.gridHidden),
	  ptsPerUnit(src.ptsPerUnit),
	  useFilling(src.useFilling),
	  lastCanvasSize(TSize(0, 0)),
	  zBuffer(NULL)
{
	grid = new GraphicObject(*src.grid);

	if(useFilling) {
		surfaceTriangles.reserve(src.surfaceTriangles.size());

		for(cTriIt i = src.surfaceTriangles.begin(); i != src.surfaceTriangles.end(); ++i) {
			surfaceTriangles.push_back(new Triangle(**i));
		}
	}
	else {
		surfaceWire.reserve(src.surfaceWire.size());

		for(cObjIt i = src.surfaceWire.begin(); i != src.surfaceWire.end(); ++i) {
			surfaceWire.push_back(new GraphicObject(**i));
		}
	}
}
//---------------------------------------------------------------------------
BezierSurface::BezierSurface(const unsigned rows,
							 const unsigned cols,
							 const unsigned detalization,
							 const bool _gridHidden,
							 const bool _useFilling = true)
	: gridHidden(_gridHidden),
	  useFilling(_useFilling),
	  ptsPerUnit(detalization),
	  lastCanvasSize(TSize(0, 0)),
	  zBuffer(NULL)
{
	frontColor = clRed;
	backColor = clBlack;

	points_container knots = points_container(rows, vector<Vertice *>(cols, 0));
	points_container points = points_container(ptsPerUnit + 1, vector<Vertice *>(ptsPerUnit + 1, 0));

	if(useFilling) {
		surfaceTriangles.reserve(2 * ptsPerUnit * ptsPerUnit);
	}
	else {
		surfaceWire.reserve(2 * ptsPerUnit * ptsPerUnit);
	}

	randomize();
	int x0 = irand(30);
	int y0 = -random(50);
	int z0 = irand(30);
	int lastx, lasty = y0, lastz = z0;

	for (unsigned i = 0; i < rows; ++i)
	{
		lastx = x0;

		for (unsigned j = 0; j < cols; ++j)
		{
			lastx += (j) ? irand(15) + 10 : irand(50);

			int x = lastx;
			int y = lasty + irand(30) + 1;
			int z = lastz + irand(60);

			UnicodeString tag = knotTag(i, j);
			Vertice *point = new Vertice (x, y, z, tag);

			knots[i][j] = point;
		}

		lasty += 10 + random(20);
	}

	grid = new GraphicObject();

	for(poIt i = knots.begin(); i != knots.end(); ++i) {
		for(pIt j = (*i).begin(); j != (*i).end(); ++j) {
			grid->addVertice(*j);
		}
	}

	for (unsigned i = 0; i < rows; ++i)
	{
		for (unsigned j = 0; j < cols - 1; ++j)
		{
			Edge *edge = new Edge(knotTag(i, j), knotTag(i, j + 1));
			edge->setPen(clBlue, 2, psSolid);
			grid->addEdge(edge);
		}
	}

	for (unsigned j = 0; j < cols; ++j)
	{
		for (unsigned i = 0; i < rows - 1; ++i)
		{
			Edge *edge = new Edge(knotTag(i, j), knotTag(i + 1, j));
			edge->setPen(clBlue, 2, psSolid);
			grid->addEdge(edge);
		}
	}

	// Surfacing

	Matrix *U, *W, *N, *M, *B, *UN, *MW;
	N = BezierSurface::getN(rows - 1);
	M = BezierSurface::getN(cols - 1);

	int row, col = 0;

	for(float u = 0; u <= 1; u += 1.0/(float)ptsPerUnit, ++col) {
		U = getU(u, rows - 1);
		UN = new Matrix(*U * *N);

		row = 0;

		for(float w = 0; w <= 1; w += 1.0/(float)ptsPerUnit, ++row) {
			W = getW(w, cols - 1);
			MW = new Matrix(*M * *W);

			B = new Matrix(rows, cols);

			double x;
			double y;
			double z;

			for(unsigned i = 0; i < rows; ++i) {
				for(unsigned j = 0; j < cols; ++j) {
                    B->values[i][j] = knots[i][j]->getX();
                }
			}

			Matrix Q1 = *UN * *B * *MW;
			x = Q1.values[0][0];

			for(unsigned i = 0; i < rows; ++i) {
				for(unsigned j = 0; j < cols; ++j) {
					B->values[i][j] = knots[i][j]->getY();
                }
			}

			Matrix Q2 = *UN * *B * *MW;
			y = Q2.values[0][0];
			for(unsigned i = 0; i < rows; ++i) {
				for(unsigned j = 0; j < cols; ++j) {
					B->values[i][j] = knots[i][j]->getZ();
                }
			}

			Matrix Q3 = *U * *N * *B * *M * *W;
			z = Q3.values[0][0];

			UnicodeString tag = pointTag(row, col);
			Vertice *pt = new Vertice(x, y, z, tag);

			points[row][col] = pt;

			delete W;
			delete B;
		}

		delete U;
		delete UN;
	}

	delete N;
	delete M;

	for(unsigned i = 0; i < ptsPerUnit; ++i) {
		for(unsigned j = 0; j < ptsPerUnit; ++j) {
			Vertice *vert1 = points[i][j];
			Vertice *vert2 = points[i][j + 1];
			Vertice *vert3 = points[i + 1][j];
			Vertice *vert4 = points[i + 1][j + 1];

			if(useFilling) {
				Triangle *triangle1 = new Triangle;

				Vertice *a, *b, *c;
				Vertice *verts[3] = {vert1, vert2, vert3};

				a = verts[0];
				b = verts[1];
				c = verts[2];

				triangle1->a = new Vertice(*a);
				triangle1->b = new Vertice(*b);
				triangle1->c = new Vertice(*c);

				surfaceTriangles.push_back(triangle1);

				Triangle *triangle2 = new Triangle;

				Vertice *verts2[3] = {vert2, vert3, vert4};

				a = verts2[1];
				b = verts2[0];
				c = verts2[2];

				triangle2->a = new Vertice(*a);
				triangle2->b = new Vertice(*b);
				triangle2->c = new Vertice(*c);

				surfaceTriangles.push_back(triangle2);
			}
        }
	}
}
//---------------------------------------------------------------------------
BezierSurface::~BezierSurface()
{
	delete grid;
}
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
void swap(double *a, double *b)
{
	double *t = new double[3];
	t[0] = a[0];
	t[1] = a[1];
	t[2] = a[2];

	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];

	b[0] = t[0];
	b[1] = t[1];
	b[2] = t[2];

	delete [] t;
}

#define X 0
#define Y 1
#define Z 2

void swap(double &a, double &b)
{
	double t = a;
	a = b;
	b = t;
}

void sort(double **array, unsigned by)
{
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			if(array[j][by] > array[j+1][by]) {
                swap(array[j], array[j+1]);
            }
        }
    }
}

double *getVec(double *a, double *b)
{
	double *c = new double[3];
	c[0] = b[0] - a[0];
	c[1] = b[1] - a[1];
	c[2] = b[2] - a[2];
	return c;
}

double *crossProduct(double *a, double *b)
{
	double *cross = new double[3];
	cross[X] = a[Y] * b[Z] - a[Z] * b[Y];
	cross[Y] = -a[X] * b[Z] + a[Z] * b[X];
	cross[Z] = a[X] * b[Y] - a[Y] * b[X];
	return cross;
}

void normalize(double *v)
{
	double mag = sqrt (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	mag = (mag) ? mag : 0.01;
	v[0] /= mag;
	v[1] /= mag;
	v[2] /= mag;
}

double troj(double *a, double *b, double *c)
{
	double first = a[X] * (b[Y] * c[Z] - c[Y] * b[Z]);
	double second = a[Y] * (b[X] * c[Z] - c[X] * b[Z]);
	double third = a[Z] * (b[X] * c[Y] - c[X] * b[Y]);
	return first - second + third;
}

void normalized(TPoint center, double &x, double &y)
{
	x = center.x + x * scale;
	y = center.y - y * scale;
}

void BezierSurface::drawTriangle(const Triangle *triangle, TCanvas *canvas, TColor color)
{
	TPoint canvasCenter = canvas->ClipRect.CenterPoint();

	double *tri[3];

	tri[0] = new double[3];
	tri[0][0] = triangle->a->getX();
	tri[0][1] = triangle->a->getY();
	tri[0][2] = triangle->a->getZ();
	normalized(canvasCenter, tri[0][0], tri[0][1]);
	tri[1] = new double[3];
	tri[1][0] = triangle->b->getX();
	tri[1][1] = triangle->b->getY();
	tri[1][2] = triangle->b->getZ();
	normalized(canvasCenter, tri[1][0], tri[1][1]);
	tri[2] = new double[3];
	tri[2][0] = triangle->c->getX();
	tri[2][1] = triangle->c->getY();
	tri[2][2] = triangle->c->getZ();
	normalized(canvasCenter, tri[2][0], tri[2][1]);

	double head[3] = {triangle->a->getX(),
					  triangle->a->getY(),
					  triangle->a->getZ() };

	normalized(canvasCenter, head[0], head[1]);

	double second[3] = {triangle->b->getX(),
						triangle->b->getY(),
						triangle->b->getZ() };

	normalized(canvasCenter, second[0], second[1]);

	double third[3] = {triangle->c->getX(),
					   triangle->c->getY(),
					   triangle->c->getZ() };

	normalized(canvasCenter, third[0], third[1]);

	double *vecA;
	double *vecB;

	vecA = getVec(head, second);
	vecB = getVec(head, third);

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

	for(int y = tri[0][1]; y <= tri[2][1]; y += 1) {
			if(y > p2[1]) {
				p4 = p3;
			}

			if(p2[1] - p4[1] && p3[1] - p1[1]) {
				double xa;
				double xb;
				double za;
				double zb;

				xa = p4[0] + (p2[0] - p4[0]) * (y - p4[1]) / (p2[1] - p4[1]);
				xb = p1[0] + (p3[0] - p1[0]) * (y - p1[1]) / (p3[1] - p1[1]);
				za = p4[2] + (p2[2] - p4[2]) * (y - p4[1]) / (p2[1] - p4[1]);
				zb = p1[2] + (p3[2] - p1[2]) * (y - p1[1]) / (p3[1] - p1[1]);

				if(xa > xb) {
					swap(xa, xb);
				}

				for(int x = xa; x <= xb; x+=1) {
					if(canvas->ClipRect.Contains(TPoint(x, y))) {
						if(xb - xa) {
							double z = za + (zb - za) * (x - xa) / (xb - xa);

							if(z > zBuffer[y-1][x-1]) {
								zBuffer[y-1][x-1] = z;
								canvas->Pixels[x][y] = isFront ? frontColor : backColor;
							}
						}
					}
				}
			}
	}

	for (int i = 0; i < 3; ++i) {
		delete [] tri[i];
	}
}
//---------------------------------------------------------------------------
void BezierSurface::draw (TCanvas *canvas)
{
	if(!gridHidden) {
		grid->draw(canvas);
	}

	refreshZbuffer(canvas->ClipRect.Size);

	for(triIt i = surfaceTriangles.begin(); i != surfaceTriangles.end(); ++i) {
//		(*i)->draw(canvas);
		drawTriangle(*i, canvas, clRed);
	}
}
//---------------------------------------------------------------------------
void BezierSurface::refreshZbuffer(TSize currentCanvasSize)
{
	if(currentCanvasSize != lastCanvasSize) {
		for (int row = 0; row < lastCanvasSize.cy; ++row) {
			free(zBuffer[row]);
		}
		free(zBuffer);

		zBuffer = (float **)malloc(currentCanvasSize.cy * sizeof(float *));
		for (int row = 0; row < currentCanvasSize.cy; ++row) {
			zBuffer[row] = (float *)malloc(currentCanvasSize.cx * sizeof(float));
		}

		lastCanvasSize = currentCanvasSize;
	}

	for (int row = 0; row < currentCanvasSize.cy; ++row) {
		memset(zBuffer[row], 0xFE, currentCanvasSize.cx * sizeof(float));
	}
}
//---------------------------------------------------------------------------
// Transformations
//---------------------------------------------------------------------------
void BezierSurface::applyTransform(Matrix *transform)
{
	grid->applyTransform(transform);

	for(triIt i = surfaceTriangles.begin(); i != surfaceTriangles.end(); ++i) {
		(*i)->applyTransform(transform);
	}
}
//---------------------------------------------------------------------------
void BezierSurface::applyRotation(const double ax, const double ay)
{
	grid->applyRotation(ax, ay);

	for(triIt i = surfaceTriangles.begin(); i != surfaceTriangles.end(); ++i) {
		(*i)->applyRotation(ax, ay);
	}
}
//---------------------------------------------------------------------------
// Helpers
//---------------------------------------------------------------------------
Matrix *BezierSurface::getN(int n)
{
	Matrix *N = new Matrix(n + 1, n + 1);

	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= n; ++j) {
			N->values[i][j] = (0 <= i + j && i + j <= n)
								? Binom(n, j) * Binom(n - j, n - i - j) * pow(-1, n - i - j)
								: 0;
        }
	}

	return N;
}
//---------------------------------------------------------------------------
Matrix *BezierSurface::getU (double u, int n)
{
	Matrix *T = new Matrix(1, n + 1);

	for(int i = n; i > 0; --i) {
		T->values[0][n-i] =  pow(u, i);
	}

	T->values[0][n] = 1;

	return T;
}
//---------------------------------------------------------------------------
Matrix *BezierSurface::getW (double w, int n)
{
	Matrix *T = new Matrix(n + 1, 1);

	for(int i = n; i > 0; --i) {
		T->values[n-i][0] =  pow(w, i);
	}

	T->values[n][0] = 1;

	return T;
}
//---------------------------------------------------------------------------
