#ifndef ConstantsH
#define ConstantsH

#include <vector>
#include <map>

extern double scale;

class Vertice;

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

#endif
