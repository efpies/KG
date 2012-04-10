//---------------------------------------------------------------------------
#pragma hdrstop

#pragma warn -8123

#include "GraphicObject.h"
#include "Edge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

GraphicObject::GraphicObject(const GraphicObject& src)
{
	edges.reserve(src.edges.size());
	points.reserve(src.points.size());
	hidden = false;

	for (cEdgeIt i = src.edges.begin(); i != src.edges.end(); ++i) {
		Edge *newEdge = new Edge (**i);
		edges.push_back (newEdge);
	}

	for(pcIt i = src.points.begin(); i != src.points.end(); ++i) {
		Vertice *newPoint = new Vertice(**i);
		points.push_back(newPoint);
    }
}

void GraphicObject::addEdge (const Edge* srcEdge)
{
	Edge *edge = new Edge(*srcEdge);
	edges.push_back(edge);
}

void GraphicObject::addPoint (Vertice* srcPoint)
{
	points.push_back(srcPoint);
}

void GraphicObject::applyTransform (Matrix *transform)
{
	for (EdgeIt i = edges.begin(); i != edges.end(); ++i) {
		(*i)->applyTransform (transform);
	}
}

void GraphicObject::applyRotation (const double ax, const double ay)
{
//	for (EdgeIt i = edges.begin(); i != edges.end(); ++i) {
//		(*i)->applyRotation (ax,ay);
//	}
	for (pIt i = points.begin(); i != points.end(); ++i) {
		(*i)->applyRotation (ax,ay);
	}
}

void GraphicObject::draw (TCanvas* canvas)
{
	for (EdgeIt i = edges.begin(); i != edges.end(); ++i) {
		(*i)->draw (canvas);
	}
}
