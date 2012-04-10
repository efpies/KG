//---------------------------------------------------------------------------
#ifndef GraphicObjectH
#define GraphicObjectH

#include <vector>
#include <vcl.h>

using namespace std;
//---------------------------------------------------------------------------
class Edge;
class CustomPoint;
class Matrix;

typedef vector<Edge *>::iterator EdgeIt;
typedef vector<Edge *>::const_iterator cEdgeIt;
typedef vector<CustomPoint *>::iterator pIt;
typedef vector<CustomPoint *>::const_iterator pcIt;

class GraphicObject
{
	private :
		vector<Edge *> edges;
		vector<CustomPoint *> points;

	public :
		GraphicObject ();
		GraphicObject (const GraphicObject&);
		~GraphicObject();

		void addEdge (const Edge *);
		void addPoint (CustomPoint *);
		void applyTransform (Matrix *);
		void applyRotation (const double, const double);
		void draw (TCanvas*);

		bool hidden;
};
//---------------------------------------------------------------------------
GraphicObject::GraphicObject() { hidden = false; }
GraphicObject::~GraphicObject(){}

#endif
