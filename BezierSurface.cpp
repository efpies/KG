//---------------------------------------------------------------------------
#pragma hdrstop

#include "BezierSurface.h"

#include <vcl.h>
#include <algorithm>
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define irand(n) random(n / 2.0) - random(n / 2.0)
#define knotTag(i, j) tagWithName(L"knot", i, j)
#define pointTag(i, j) tagWithName(L"point", i, j)
//---------------------------------------------------------------------------
// Lifecycle
//---------------------------------------------------------------------------
BezierSurface::BezierSurface(const BezierSurface& src)
	: gridHidden(src.gridHidden), ptsPerUnit(src.ptsPerUnit)
{
	grid = new GraphicObject(*src.grid);
	surface.reserve(src.surface.size());

	for(cObjIt i = src.surface.begin(); i != src.surface.end(); ++i) {
		surface.push_back(new GraphicObject(**i));
    }
}
//---------------------------------------------------------------------------
BezierSurface::BezierSurface(const unsigned rows,
							 const unsigned cols,
							 const unsigned detalization,
							 const bool _gridHidden)
	: gridHidden(_gridHidden),
	  ptsPerUnit(detalization)
{
	points_container knots = points_container(rows, vector<Vertice *>(cols, 0));
	points_container points = points_container(ptsPerUnit + 1, vector<Vertice *>(ptsPerUnit + 1, 0));
	surface.reserve(2 * ptsPerUnit * ptsPerUnit);

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
			GraphicObject *triangle1 = new GraphicObject;

			Vertice *vert1 = points[i][j];
			Vertice *vert2 = points[i][j + 1];
			Vertice *vert3 = points[i + 1][j];
			Vertice *vert4 = points[i + 1][j + 1];

			Edge *edge1 = new Edge(vert1->tag, vert2->tag);
			Edge *edge2 = new Edge(vert1->tag, vert3->tag);
			Edge *edge3 = new Edge(vert2->tag, vert3->tag);

			triangle1->addVertice(vert1);
			triangle1->addVertice(vert2);
			triangle1->addVertice(vert3);

			triangle1->addEdge(edge1);
			triangle1->addEdge(edge2);
			triangle1->addEdge(edge3);

			surface.push_back(triangle1);

			GraphicObject *triangle2 = new GraphicObject;

			Edge *edge4 = new Edge(vert2->tag, vert4->tag);
			Edge *edge5 = new Edge(vert3->tag, vert4->tag);
			Edge *edge6 = new Edge(vert2->tag, vert3->tag);

			triangle2->addVertice(vert2);
			triangle2->addVertice(vert3);
			triangle2->addVertice(vert4);

			triangle2->addEdge(edge4);
			triangle2->addEdge(edge5);
			triangle2->addEdge(edge6);

			surface.push_back(triangle2);
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
void BezierSurface::draw (TCanvas *canvas)
{
	if(!gridHidden) {
		grid->draw(canvas);
	}

	for(objIt i = surface.begin(); i != surface.end(); ++i) {
		(*i)->draw(canvas);
	}
}

//---------------------------------------------------------------------------
// Transformations
//---------------------------------------------------------------------------
void BezierSurface::applyTransform(Matrix *transform)
{
	grid->applyTransform(transform);

	for(objIt i = surface.begin(); i != surface.end(); ++i) {
		(*i)->applyTransform(transform);
	}
}
//---------------------------------------------------------------------------
void BezierSurface::applyRotation(const double ax, const double ay)
{
	grid->applyRotation(ax, ay);

	for(objIt i = surface.begin(); i != surface.end(); ++i) {
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
