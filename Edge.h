//---------------------------------------------------------------------------
#ifndef EdgeH
#define EdgeH

#include <vcl.h>
#include "Vertice.h"
#include "Constants.h"
#include "GraphicMatrix.h"
//---------------------------------------------------------------------------

class Edge
{
	private :
		Vertice *a;
		Vertice *b;

		TPen *pen;

	public :
		Edge (Vertice*, Vertice*);
		Edge (const int, const int);
		Edge (const Edge&);
		~Edge();

		void setPen(TColor, int, TPenStyle);
		inline void draw  (TCanvas *);
		inline void applyTransform (Matrix*);
		inline void applyRotation (const double, const double);
};
//---------------------------------------------------------------------------
Edge::Edge (const Edge& src)
{
	a = new Vertice(*src.a);
	b = new Vertice(*src.b);

	pen = new TPen;
	pen->Color = src.pen->Color;
	pen->Width = src.pen->Width;
	pen->Style = src.pen->Style;
}

Edge::Edge (Vertice *pointA, Vertice *pointB)
{
//	a = new CustomPoint (*pointA);
//	b = new CustomPoint (*pointB);

	a = pointA;
	b = pointB;

	pen = new TPen;
	pen->Color = clBlack;
	pen->Width = 1;
	pen->Style = psSolid;
}

Edge::~Edge ()
{
	delete pen;
}

void Edge::setPen (TColor penColor, int penWidth, TPenStyle penStyle)
{
	delete pen;
	pen = new TPen;
	pen->Color = penColor;
	pen->Width = penWidth;
	pen->Style = penStyle;
}

inline void Edge::draw (TCanvas *canvas)
{
	canvas->Pen = pen;
	TPoint canvasCenter = TPoint (canvas->ClipRect.Width() / 2.0, canvas->ClipRect.Height() / 2.0);
	canvas->PenPos = TPoint (canvasCenter.x + a->getX()*scale, canvasCenter.y - a->getY()*scale);
	canvas->LineTo(canvasCenter.x + b->getX()*scale, canvasCenter.y - b->getY()*scale);
}

inline void Edge::applyTransform (Matrix* transform)
{
	a->applyTransform(transform);
	b->applyTransform(transform);
}

inline void Edge::applyRotation (const double ax, const double ay)
{
	a->applyRotation(ax, ay);
	b->applyRotation(ax, ay);
}
//---------------------------------------------------------------------------
#endif
