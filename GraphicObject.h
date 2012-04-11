//---------------------------------------------------------------------------
#ifndef GraphicObjectH
#define GraphicObjectH

#include <vector>
#include <vcl.h>
#include <map>
#include "Vertice.h"
#include "Constants.h"

using namespace std;
//---------------------------------------------------------------------------
class Edge;
class Matrix;

typedef vector<Edge *>::iterator EdgeIt;
typedef vector<Edge *>::const_iterator cEdgeIt;

class GraphicObject
{
	private :
		vector<Edge *> edges;
		vector<Vertice *> points;
		map<UnicodeString, Vertice *> allVertices;

	public :
		GraphicObject ();
		GraphicObject (const GraphicObject&);
		~GraphicObject();

		void addEdge (const Edge *);
		void addVertice (Vertice *);
		void applyTransform (Matrix *);
		void applyRotation (const double, const double);
		void draw (TCanvas*);

		bool hidden;
};
//---------------------------------------------------------------------------
GraphicObject::GraphicObject() { hidden = false; }
GraphicObject::~GraphicObject(){}

void GraphicObject::addVertice(Vertice *src)
{
    allVertices[src->tag] = new Vertice(*src);
}

#endif
