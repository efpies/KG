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
		TPen *pen;

	public :
		UnicodeString tagA;
		UnicodeString tagB;

		Edge (const UnicodeString&, const UnicodeString&);
		Edge (const Edge&);
		~Edge();

		void setPen(TColor, int, TPenStyle);
		inline void draw  (TCanvas *, const Vertice *, const Vertice *);
};
//---------------------------------------------------------------------------
Edge::Edge (const Edge& src)
	: tagA(src.tagA), tagB(src.tagB)
{
	pen = new TPen;
	pen->Color = src.pen->Color;
	pen->Width = src.pen->Width;
	pen->Style = src.pen->Style;
}

Edge::Edge (const UnicodeString& _tagA, const UnicodeString& _tagB)
	: tagA(_tagA), tagB(_tagB)
{
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

inline void Edge::draw (TCanvas *canvas, const Vertice *a, const Vertice *b)
{
	canvas->Pen = pen;
	TPoint canvasCenter = TPoint (canvas->ClipRect.Width() / 2.0, canvas->ClipRect.Height() / 2.0);
	canvas->PenPos = TPoint (canvasCenter.x + a->getX()*scale, canvasCenter.y - a->getY()*scale);
	canvas->LineTo(canvasCenter.x + b->getX()*scale, canvasCenter.y - b->getY()*scale);
}

//---------------------------------------------------------------------------
#endif
