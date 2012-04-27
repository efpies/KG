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

				triangle1->av = new Vertice(*a);
				triangle1->bv = new Vertice(*b);
				triangle1->cv = new Vertice(*c);

				surfaceTriangles.push_back(triangle1);

				Triangle *triangle2 = new Triangle;

				Vertice *verts2[3] = {vert2, vert3, vert4};

				a = verts2[1];
				b = verts2[0];
				c = verts2[2];

				triangle2->av = new Vertice(*a);
				triangle2->bv = new Vertice(*b);
				triangle2->cv = new Vertice(*c);

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
void BezierSurface::draw (Graphics::TBitmap *bmp)
{
	if(!gridHidden) {
		grid->draw(bmp);
	}

	refreshZbuffer(bmp->Canvas->ClipRect.Size);

	for(triIt i = surfaceTriangles.begin(); i != surfaceTriangles.end(); ++i) {
		(*i)->draw(bmp, zBuffer, frontColor, backColor);
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
