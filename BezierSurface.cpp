//---------------------------------------------------------------------------
#pragma hdrstop

#include "BezierSurface.h"
#include <fstream>

#include <vcl.h>
#include "DebugHelpers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define irand(n) random(n/2.0)-random(n/2.0)

const ptsPerUnit = 15;

long fact(int n)
{
	return n == 0L ? 1 : n * fact (n-1);
}

unsigned Binom(int n, int i)
{
	return fact(n)/(fact(i)*fact(n-i));
}

Matrix *BezierSurface::getN(int n)
{
	Matrix *N = new Matrix(n+1,n+1);

	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= n; ++j)
			N->values[i][j] = (0 <= i + j && i + j <= n) ? Binom(n, j) * Binom(n-j, n-i-j) * pow(-1, n-i-j) : 0;

	return N;
}

Matrix *BezierSurface::getU (double u, int n)
{
	Matrix *T = new Matrix(1,n+1);

	for(int i = n; i > 0; --i)
		T->values[0][n-i] =  pow(u, i);
	T->values[0][n] = 1;
	return T;
}

Matrix *BezierSurface::getW (double w, int n)
{
	Matrix *T = new Matrix(n+1,1);

	for(int i = n; i > 0; --i)
		T->values[n-i][0] =  pow(w, i);
	T->values[n][0] = 1;
	return T;
}

BezierSurface::BezierSurface(unsigned rows, unsigned cols) :
	knots(points_container(rows, vector<Vertice *>(cols, 0))),
	points(points_container(ptsPerUnit+1, vector<Vertice *>(ptsPerUnit+1, 0)))
{

	int x0 = irand(30);
	int y0 = irand(30);
	int z0 = irand(30);
	int lastx, lasty = y0, lastz = z0;

	for (unsigned i = 0; i < rows; ++i)
	{
		lastx = x0;

		int maxy = 0;

		for (unsigned j = 0; j < cols; ++j)
		{
			lastx += (j) ? irand(15) + 10 : irand(50);

			int x = lastx;
			int y = lasty + irand(15) + 1;
			int z = lastz + irand(30);

			Vertice *point = new Vertice (x, y, z);
			knots[i][j] = point;
		}

		lasty += 10 + random(20);
	}

	grid = new GraphicObject();

	for(poIt i = knots.begin(); i != knots.end(); ++i) {
		for(pIt j = (*i).begin(); j != (*i).end(); ++j) {
			grid->addPoint(*j);
        }
	}

	for (unsigned i = 0; i < rows; ++i)
	{
		for (unsigned j = 0; j < cols - 1; ++j)
		{
			Edge *edge = new Edge(knots[i][j], knots[i][j+1]);
			edge->setPen(clBlue, 3, psSolid);
			grid->addEdge(edge);
		}
	}

	for (unsigned j = 0; j < cols; ++j)
	{
		for (unsigned i = 0; i < rows - 1; ++i)
		{
			Edge *edge = new Edge(knots[i][j], knots[i+1][j]);
			edge->setPen(clBlue, 3, psSolid);
			grid->addEdge(edge);
		}
	}

	// Surfacing

	Matrix *U, *W, *N, *M, *B, *UN, *MW;
	N = BezierSurface::getN(rows-1);
	M = BezierSurface::getN(cols-1);

    int row, col = 0;


	ofstream dbg(L"D:\\debug.txt", ios::out);
	for(float u = 0; u <= 1; u += 1.0/(float)ptsPerUnit, ++col) {
		U = getU(u, rows-1);
		UN = new Matrix(*U * *N);

		row = 0;

//		dbg<< points.size() << " " << points[0].size() << endl;

		for(float w = 0; w <= 1; w += 1.0/(float)ptsPerUnit, ++row) {
			W = getW(w, cols-1);
			MW = new Matrix(*M * *W);

			B = new Matrix(rows, cols);

			double x;
			double y;
			double z;

			for(int i = 0; i < rows; ++i) {
				for(int j = 0; j < cols; ++j) {
                    B->values[i][j] = knots[i][j]->getX();
                }
			}

			Matrix Q1 = *UN * *B * *MW;
			x = Q1.values[0][0];

			for(int i = 0; i < rows; ++i) {
				for(int j = 0; j < cols; ++j) {
					B->values[i][j] = knots[i][j]->getY();
                }
			}

			Matrix Q2 = *UN * *B * *MW;
			y = Q2.values[0][0];
			for(int i = 0; i < rows; ++i) {
				for(int j = 0; j < cols; ++j) {
					B->values[i][j] = knots[i][j]->getZ();
                }
			}

			Matrix Q3 = *U * *N * *B * *M * *W;
			z = Q3.values[0][0];

			Vertice *pt = new Vertice(x, y, z);

			delete W;
			delete B;

//		dbg << endl << "{ " << row << " ; " << col << " }";
//if(row<ptsPerUnit)
			points[row][col] = pt;
		}

		delete U;
		delete UN;
//		dbg<< u << endl;
	}

	delete N;
	delete M;

	surface = new GraphicObject();

	for (unsigned i = 0; i < ptsPerUnit; ++i)
	{
		for (unsigned j = 0; j < ptsPerUnit - 1; ++j)
		{
			Edge *edge = new Edge(points[i][j], points[i][j+1]);
			edge->setPen(clRed, 1, psSolid);
			surface->addEdge(edge);
		}
	}

	for (unsigned j = 0; j < ptsPerUnit; ++j)
	{
		for (unsigned i = 0; i < ptsPerUnit - 1; ++i)
		{
			Edge *edge = new Edge(points[i][j], points[i+1][j]);
			edge->setPen(clRed, 1, psSolid);
			surface->addEdge(edge);
		}
	}
}

void BezierSurface::draw (TCanvas *canvas)
{
	grid->draw(canvas);
//	surface->draw(canvas);
}

void BezierSurface::applyTransform(Matrix *transform)
{
	grid->applyTransform(transform);
	surface->applyTransform(transform);
}

void BezierSurface::applyRotation(const double ax, const double ay)
{
	grid->applyRotation(ax, ay);
//	surface->applyRotation(ax, ay);
}
