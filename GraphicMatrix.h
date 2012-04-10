//---------------------------------------------------------------------------
#ifndef GraphicMatrixH
#define GraphicMatrixH

#include "Matrix.h"
#include "Constants.h"
#include <cmath>
#include "DebugHelpers.h"

using namespace std;

//---------------------------------------------------------------------------
inline Matrix *GetRotationMatrixForAxis (const Axis, const double);
inline Matrix *GetMoveMatrix (const double, const double, const double);
inline Matrix *GetProjectionMatrix ();
inline Matrix *GetIsometryMatrix ();
inline Matrix *GetReflectionMatrix (const Axis, const Axis);

inline Matrix *GetStandardRotationMatrix(const double anglex, const double angley)
{
	Matrix *rotationMatrix = new Matrix (4, 4);

			rotationMatrix->values[0][0] = cos(angley);
			rotationMatrix->values[0][1] = sin(angley)*sin(anglex);
			rotationMatrix->values[0][2] = 0;

			rotationMatrix->values[1][0] = 0;
			rotationMatrix->values[1][1] = cos(anglex);
			rotationMatrix->values[1][2] = 0;

			rotationMatrix->values[2][0] = sin(angley);
			rotationMatrix->values[2][1] = -cos(angley)*sin(anglex);
			rotationMatrix->values[2][2] = 0;

	rotationMatrix->values[0][3] = 0;
	rotationMatrix->values[1][3] = 0;
	rotationMatrix->values[2][3] = 0;
	rotationMatrix->values[3][0] = 0;
	rotationMatrix->values[3][1] = 0;
	rotationMatrix->values[3][2] = 0;
	rotationMatrix->values[3][3] = 1;

	return rotationMatrix;
}

inline Matrix *GetRotationMatrixForAxis (const Axis axis, const double angle)
{
	Matrix *rotationMatrix = new Matrix (4, 4);

	double cosAngle = cos(angle);
	double sinAngle = sin(angle);

	switch (axis) {
		case AxisX: {
			rotationMatrix->values[0][0] = 1;
			rotationMatrix->values[0][1] = 0;
			rotationMatrix->values[0][2] = 0;

			rotationMatrix->values[1][0] = 0;
			rotationMatrix->values[1][1] = cosAngle;
			rotationMatrix->values[1][2] = sinAngle;

			rotationMatrix->values[2][0] = 0;
			rotationMatrix->values[2][1] = -sinAngle;
			rotationMatrix->values[2][2] = cosAngle;
			break;
		}

		case AxisY: {
			rotationMatrix->values[0][0] = cosAngle;
			rotationMatrix->values[0][1] = 0;
			rotationMatrix->values[0][2] = -sinAngle;

			rotationMatrix->values[1][0] = 0;
			rotationMatrix->values[1][1] = 1;
			rotationMatrix->values[1][2] = 0;

			rotationMatrix->values[2][0] = sinAngle;
			rotationMatrix->values[2][1] = 0;
			rotationMatrix->values[2][2] = cosAngle;
			break;
		}

		case AxisZ:{
			rotationMatrix->values[0][0] = cosAngle;
			rotationMatrix->values[0][1] = sinAngle;
			rotationMatrix->values[0][2] = 0;

			rotationMatrix->values[1][0] = -sinAngle;
			rotationMatrix->values[1][1] = cosAngle;
			rotationMatrix->values[1][2] = 0;

			rotationMatrix->values[2][0] = 0;
			rotationMatrix->values[2][1] = 0;
			rotationMatrix->values[2][2] = 1;
			break;
		}
	}

	rotationMatrix->values[0][3] = 0;
	rotationMatrix->values[1][3] = 0;
	rotationMatrix->values[2][3] = 0;
	rotationMatrix->values[3][0] = 0;
	rotationMatrix->values[3][1] = 0;
	rotationMatrix->values[3][2] = 0;
	rotationMatrix->values[3][3] = 1;

	return rotationMatrix;
}

inline Matrix *GetMoveMatrix (const double x, const double y, const double z)
{
	Matrix *moveMatrix = new Matrix (4, 4);

	moveMatrix->fillDiagWithValue (1);

	moveMatrix->values[3][0] = x;
	moveMatrix->values[3][1] = y;
	moveMatrix->values[3][2] = z;

	return moveMatrix;
}

inline Matrix *GetProjectionMatrix ()
{
	Matrix *projectionMatrix = new Matrix (4, 4);

	projectionMatrix->fillDiagWithValue (1);
	projectionMatrix->values[2][2] = 0;

	return projectionMatrix;
}

inline Matrix *GetIsometryMatrix ()
{
	static Matrix *isometryMatrix = NULL;

	if (!isometryMatrix) {
		isometryMatrix = GetRotationMatrixForAxis (AxisY, -M_PI / 4.0);
		*isometryMatrix *= *GetRotationMatrixForAxis (AxisX, 0.6154797142073631);
	}

	return isometryMatrix;
}

inline Matrix *GetReflectionMatrix (const Axis first, const Axis second)
{
	Matrix *reflectionMatrix = new Matrix (4, 4);
	reflectionMatrix->values[0][0] = (first == AxisX || second == AxisX) ? 1 : -1;
	reflectionMatrix->values[1][1] = (first == AxisY || second == AxisY) ? 1 : -1;
	reflectionMatrix->values[2][2] = (first == AxisZ || second == AxisZ) ? 1 : -1;
	reflectionMatrix->values[3][3] = 1;
	debugOutVector(reflectionMatrix->values);
	return reflectionMatrix;
}
#endif
