//---------------------------------------------------------------------------
#ifndef GraphicObjectH
#define GraphicObjectH

#include <vector>
#include <vcl.h>
#include <map>
#include "Vertice.h"
#include "Edge.h"
#include "Constants.h"
//---------------------------------------------------------------------------
using namespace std;

class Matrix;

class GraphicObject
{
	private :
		vector<Edge *> edges;
		vector<Vertice *> points;
		map<UnicodeString, Vertice *> allVertices;

	public :
		GraphicObject ();
		GraphicObject (const GraphicObject&);

		inline void addVertice (Vertice *);
		inline void addEdge (const Edge *);

		void applyTransform (Matrix *);
		void applyRotation (const double, const double);
		void draw (TCanvas*);

		bool hidden;
};
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
inline void GraphicObject::addVertice(Vertice *src)
{
    allVertices[src->tag] = new Vertice(*src);
}
//---------------------------------------------------------------------------
inline void GraphicObject::addEdge (const Edge* srcEdge)
{
	Edge *edge = new Edge(*srcEdge);
	edges.push_back(edge);
}
//---------------------------------------------------------------------------
#endif
