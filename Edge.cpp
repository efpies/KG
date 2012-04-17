//---------------------------------------------------------------------------
#pragma hdrstop

#include "Edge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Lifecycle
//---------------------------------------------------------------------------
Edge::Edge(const Edge& src)
	: tagA(src.tagA), tagB(src.tagB)
{
	pen = new TPen;
	pen->Color = src.pen->Color;
	pen->Width = src.pen->Width;
	pen->Style = src.pen->Style;
}
//---------------------------------------------------------------------------
Edge::Edge(const UnicodeString& _tagA, const UnicodeString& _tagB)
	: tagA(_tagA), tagB(_tagB)
{
	pen = new TPen;
	pen->Color = clBlack;
	pen->Width = 1;
	pen->Style = psSolid;
}
//---------------------------------------------------------------------------
Edge::~Edge()
{
	delete pen;
}
//---------------------------------------------------------------------------
