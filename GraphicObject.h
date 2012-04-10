//---------------------------------------------------------------------------
#ifndef GraphicObjectH
#define GraphicObjectH

#include <vector>
#include <vcl.h>

using namespace std;
//---------------------------------------------------------------------------
class Edge;
class Vertice;
class Matrix;

typedef vector<Edge *>::iterator EdgeIt;
typedef vector<Edge *>::const_iterator cEdgeIt;
typedef vector<Vertice *>::iterator pIt;
typedef vector<Vertice *>::const_iterator pcIt;

class GraphicObject
{
	private :
		vector<Edge *> edges;
		vector<Vertice *> points;

	public :
		GraphicObject ();
		GraphicObject (const GraphicObject&);
		~GraphicObject();

		void addEdge (const Edge *);
		void addPoint (Vertice *);
		void applyTransform (Matrix *);
		void applyRotation (const double, const double);
		void draw (TCanvas*);

		bool hidden;
};
//---------------------------------------------------------------------------
GraphicObject::GraphicObject() { hidden = false; }
GraphicObject::~GraphicObject(){}

#endif
