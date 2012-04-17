//---------------------------------------------------------------------------
#ifndef EdgeH
#define EdgeH

#include <vcl.h>
#include "Vertice.h"
#include "Constants.h"
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

		inline void setPen(TColor, int, TPenStyle);
		inline void draw  (TCanvas *, const Vertice *, const Vertice *);
};
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
inline void Edge::setPen (TColor penColor, int penWidth, TPenStyle penStyle)
{
	delete pen;
	pen = new TPen;
	pen->Color = penColor;
	pen->Width = penWidth;
	pen->Style = penStyle;
}
//---------------------------------------------------------------------------
inline void Edge::draw (TCanvas *canvas, const Vertice *a, const Vertice *b)
{
	canvas->Pen = pen;
	TPoint canvasCenter = TPoint (canvas->ClipRect.Width() / 2.0, canvas->ClipRect.Height() / 2.0);
	canvas->PenPos = TPoint (canvasCenter.x + a->getX()*scale, canvasCenter.y - a->getY()*scale);
	canvas->LineTo(canvasCenter.x + b->getX()*scale, canvasCenter.y - b->getY()*scale);
}

//---------------------------------------------------------------------------
#endif
