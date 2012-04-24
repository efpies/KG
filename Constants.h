#ifndef ConstantsH
#define ConstantsH

#include <vector>
#include <map>
#include <vcl.h>

extern double scale;

class Vertice;
class Edge;
class GraphicObject;
class Triangle;
class Object3D;

typedef enum {
	AxisX,
	AxisY,
	AxisZ
} Axis;

typedef std::vector< std::vector<double> > matrix_values;
typedef std::vector< std::vector<double> >::iterator mvIt;
typedef std::vector<double>::iterator dIt;

typedef std::vector< std::vector<Vertice *> > points_container;
typedef std::vector< std::vector<Vertice *> >::iterator poIt;
typedef std::vector<Vertice *>::iterator pIt;

typedef std::map<UnicodeString, Vertice *>::iterator vertIt;
typedef std::map<UnicodeString, Vertice *>::const_iterator vertIt_const;

typedef std::vector<Edge *>::iterator EdgeIt;
typedef std::vector<Edge *>::const_iterator cEdgeIt;

typedef std::vector<GraphicObject *>::iterator objIt;
typedef std::vector<GraphicObject *>::const_iterator cObjIt;

typedef std::vector<Triangle *>::iterator triIt;
typedef std::vector<Triangle *>::const_iterator cTriIt;

typedef std::vector<Object3D *>::iterator obj3dIt;
typedef std::vector<Object3D *>::const_iterator cObj3dIt;

#endif
