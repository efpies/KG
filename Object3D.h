//---------------------------------------------------------------------------
#ifndef Object3DH
#define Object3DH

#include <vcl.h>
//---------------------------------------------------------------------------
class Matrix;

class Object3D
{
	public :
		virtual void draw(TCanvas *) = 0;
		virtual void applyTransform(Matrix *) = 0;
		virtual void applyRotation(const double, const double) = 0;

		bool hidden;
};
//---------------------------------------------------------------------------
#endif
