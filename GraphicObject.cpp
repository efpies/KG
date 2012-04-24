//---------------------------------------------------------------------------
#pragma hdrstop

#include "GraphicObject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Lifecycle
//---------------------------------------------------------------------------
GraphicObject::GraphicObject() : Object3D() { hidden = false; }
//---------------------------------------------------------------------------
GraphicObject::GraphicObject(const GraphicObject& src)
	 : Object3D(src)
{
	edges.reserve(src.edges.size());
	hidden = false;

	for (cEdgeIt i = src.edges.begin(); i != src.edges.end(); ++i) {
		Edge *newEdge = new Edge (**i);
		edges.push_back (newEdge);
	}

	for(vertIt_const i = src.allVertices.begin(); i != src.allVertices.end(); ++i) {
		Vertice *newPoint = new Vertice(*(*i).second);
		allVertices[newPoint->tag] = newPoint;
	}
}
//---------------------------------------------------------------------------
// Transformations
//---------------------------------------------------------------------------
void GraphicObject::applyTransform (Matrix *transform)
{
	for(vertIt i = allVertices.begin(); i != allVertices.end(); ++i) {
		(*i).second->applyTransform (transform);
	}
}
//---------------------------------------------------------------------------
void GraphicObject::applyRotation(const double ax, const double ay)
{
	for(vertIt i = allVertices.begin(); i != allVertices.end(); ++i) {
		(*i).second->applyRotation (ax, ay);
	}
}
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
void GraphicObject::draw(TCanvas* canvas)
{
	for (EdgeIt i = edges.begin(); i != edges.end(); ++i) {
		(*i)->draw (canvas, allVertices[(*i)->tagA], allVertices[(*i)->tagB]);
	}
}
//---------------------------------------------------------------------------
