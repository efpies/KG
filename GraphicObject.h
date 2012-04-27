//---------------------------------------------------------------------------
#ifndef GraphicObjectH
#define GraphicObjectH

#include <vector>
#include <vcl.h>
#include <map>
#include "Vertice.h"
#include "Edge.h"
#include "Constants.h"
#include "Object3D.h"
//---------------------------------------------------------------------------
using namespace std;

class Matrix;

class GraphicObject : virtual public Object3D
{
	private :
		vector<Edge *> edges;

	public :
		map<UnicodeString, Vertice *> allVertices;
		GraphicObject();
		GraphicObject(const GraphicObject&);

		inline void addVertice(const Vertice *);
		inline void addEdge(const Edge *);

		void applyTransform(Matrix *);
		void applyRotation(const double, const double);
		void draw(Graphics::TBitmap *);

		Vertice *a;
		Vertice *b;
		Vertice *c;
};
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
inline void GraphicObject::addVertice(const Vertice *src)
{
    allVertices[src->tag] = new Vertice(*src);
}
//---------------------------------------------------------------------------
inline void GraphicObject::addEdge (const Edge *srcEdge)
{
	Edge *edge = new Edge(*srcEdge);
	edges.push_back(edge);
}
//---------------------------------------------------------------------------
#endif
