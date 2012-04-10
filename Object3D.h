//---------------------------------------------------------------------------
#ifndef Object3DH
#define Object3DH

#include <vector>
#include "CustomPoint.h"
//---------------------------------------------------------------------------
using namespace std;
class Edge;

class Object3D
{
	private :
		vector<CustomPoint*> vertices;
		vector<Edge*>		 edges;

	public :
		Object3D ();
		Object3D (const Object3D &);
		~Object3D();
};
//---------------------------------------------------------------------------
#endif
