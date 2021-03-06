//---------------------------------------------------------------------------
#pragma hdrstop

#include "Triangle.h"
#include "Matrix.h"

#include <cstdlib>

#include "Constants.h"
#include <float.h>
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Custom methods
//---------------------------------------------------------------------------
void Triangle::drawWithColor(Graphics::TBitmap *bmp, float **zBuffer, double tri[3][3], TRGBTriple pixelColor)
{
	TRect clipRect = bmp->Canvas->ClipRect;

	double *p1 = tri[0];
	double *p2 = tri[1];
	double *p3 = tri[2];
	double *p4 = p1;

	double p3x_p1x = p3[_X] - p1[_X];
	double p3y_p1y = p3[_Y] - p1[_Y];
	double p3z_p1z = p3[_Z] - p1[_Z];

	double p2x_p4x = p2[_X] - p4[_X];
	double p2y_p4y = p2[_Y] - p4[_Y];
	double p2z_p4z = p2[_Z] - p4[_Z];

	for(int y = max(1.0, tri[0][_Y]); p3y_p1y && y <= tri[2][_Y]; ++y) {
		if(y <= clipRect.Height()) {
			if(y > p2[_Y]) {
				p4 = p3;
				p2x_p4x = p2[_X] - p4[_X];
				p2y_p4y = p2[_Y] - p4[_Y];
				p2z_p4z = p2[_Z] - p4[_Z];
			}

			if(p2y_p4y) {
				double xa;
				double xb;
				double za;
				double zb;

				xa = p4[_X] + (p2x_p4x) * (y - p4[_Y]) / (p2y_p4y);
				xb = p1[_X] + (p3x_p1x) * (y - p1[_Y]) / (p3y_p1y);
				za = p4[_Z] + (p2z_p4z) * (y - p4[_Y]) / (p2y_p4y);
				zb = p1[_Z] + (p3z_p1z) * (y - p1[_Y]) / (p3y_p1y);

				if(xa > xb) {
					std::swap(xa, xb);
				}

				TRGBTriple *data = reinterpret_cast<TRGBTriple *>(bmp->ScanLine[y - 1]);

				double xb_xa = xb - xa;
				double zb_za = zb - za;

				for(int x = xa; x <= xb; ++x) {
					if(clipRect.Contains(TPoint(x, y))) {
						if(xb_xa) {
							double z = za + (zb_za) * (x - xa) / (xb_xa);

							if(z > zBuffer[y - 1][x - 1]) {
								zBuffer[y - 1][x - 1] = z;
								data[x - 1] = pixelColor;
							}
						}
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void Triangle::draw(Graphics::TBitmap *bmp, float **zBuffer, TColor frontColor, TColor backColor)
{
	TRect clipRect = bmp->Canvas->ClipRect;
	TPoint canvasCenter = clipRect.CenterPoint();

	double tri[3][3];

	tri[0][0] = av->getX();
	tri[0][1] = av->getY();
	tri[0][2] = av->getZ();
	normalized(canvasCenter, tri[0][_X], tri[0][_Y]);

	tri[1][0] = bv->getX();
	tri[1][1] = bv->getY();
	tri[1][2] = bv->getZ();
	normalized(canvasCenter, tri[1][_X], tri[1][_Y]);

	tri[2][0] = cv->getX();
	tri[2][1] = cv->getY();
	tri[2][2] = cv->getZ();
	normalized(canvasCenter, tri[2][_X], tri[2][_Y]);

	sort(tri, 1);

	vector3D src;
	src.x = MainForm->sourcePositionAtAxis[AxisX];
	src.y = MainForm->sourcePositionAtAxis[AxisY];
	src.z = MainForm->sourcePositionAtAxis[AxisZ];
	normalized(canvasCenter, src.x, src.y);

	vector3D dest;
	dest.x = 0.0;
	dest.y = 0.0;
	dest.z = 0.0;
	normalized(canvasCenter, dest.x, dest.y);

	vector3D head;
	head.x = av->getX();
	head.y = av->getY();
	head.z = av->getZ();
	normalized(canvasCenter, head.x, head.y);

	vector3D second;
	second.x = bv->getX();
	second.y = bv->getY();
	second.z = bv->getZ();
	normalized(canvasCenter, second.x, second.y);

	vector3D third;
	third.x = cv->getX();
	third.y = cv->getY();
	third.z = cv->getZ();
	normalized(canvasCenter, third.x, third.y);

	vector3D vecA;
	makevector3D(head, second, vecA);

	vector3D vecB;
	makevector3D(head, third, vecB);

	vector3D cross;
	crossProduct(vecA, vecB, cross);

	bool isFront = cross.z >= head.z;

	if(MainForm->drawStyle == DrawStyleFill) {
		TColor drawColor = (isFront) ? frontColor : backColor;

		if(!isFront) {
			cross.x = -cross.x;
			cross.y = -cross.y;
			cross.z = -cross.z;
		}

		vector3D vecLight;
		makevector3D(src, dest, vecLight);

		vector3D vecInvBeam;
		makevector3D(head, src, vecInvBeam);

		double distance = vectorLength(vecInvBeam) * 0.01;

		normalizeVec(cross);
		normalizeVec(vecInvBeam);

		vector3D mirrored;
		double dotProductCrossVecInvBeam = dotProduct(cross, vecInvBeam);
		mirrored.x = cross.x * 2.0 * dotProductCrossVecInvBeam - vecInvBeam.x;
		mirrored.y = cross.y * 2.0 * dotProductCrossVecInvBeam - vecInvBeam.y;
		mirrored.z = cross.z * 2.0 * dotProductCrossVecInvBeam - vecInvBeam.z;
		normalizeVec(mirrored);

		vector3D spectator;
		spectator.x = 0.0;
		spectator.y = 0.0;
		spectator.z = 1.0;

		TRGBTriple Isrc = RGBTripleFromColor(MainForm->sourceLightColor);
		TRGBTriple Iamb = RGBTripleFromColor(MainForm->ambientLightColor);
		TRGBTriple Im   = RGBTripleFromColor(clWhite);

		double kAmb = MainForm->shouldUseAmbientLightModel * MainForm->ambientIntensityCoeff;
		double kD   = MainForm->materialDiffusionCoeff;
		double k =  (MainForm->shouldUseDiffusionLightModel) ? kD * max(0.0, dotProduct(cross, vecInvBeam)) / distance : 1;
		double kM = MainForm->shouldUseReflectionLightModel * max(0.0, pow(dotProduct(mirrored, spectator), 5));

		double Ired   = min(Iamb.rgbtRed   * kAmb + Isrc.rgbtRed   * k + Im.rgbtRed   * kM, 255.0);
		double Igreen = min(Iamb.rgbtGreen * kAmb + Isrc.rgbtGreen * k + Im.rgbtGreen * kM, 255.0);
		double Iblue  = min(Iamb.rgbtBlue  * kAmb + Isrc.rgbtBlue  * k + Im.rgbtBlue  * kM, 255.0);

		TRGBTriple pixelColor;
		pixelColor.rgbtRed   = GetRValue(drawColor) * Ired   * 0.0039215686274509803921568627451;
		pixelColor.rgbtBlue  = GetBValue(drawColor) * Iblue  * 0.0039215686274509803921568627451;
		pixelColor.rgbtGreen = GetGValue(drawColor) * Igreen * 0.0039215686274509803921568627451;

		drawWithColor(bmp, zBuffer, tri, pixelColor);
	}
	else if (MainForm->drawStyle == DrawStyleWire) {
		drawWithColor(bmp, zBuffer, tri, RGBTripleFromColor(clWhite));

		TCanvas *canvas = bmp->Canvas;
		canvas->Pen->Color = clRed;
		canvas->Pen->Width = 1;

		canvas->PenPos = TPoint(tri[0][_X], tri[0][_Y]);
		canvas->LineTo(tri[1][_X], tri[1][_Y]);

		canvas->PenPos = TPoint(tri[1][_X], tri[1][_Y]);
		canvas->LineTo(tri[2][_X], tri[2][_Y]);

		canvas->PenPos = TPoint(tri[2][_X], tri[2][_Y]);
		canvas->LineTo(tri[0][_X], tri[0][_Y]);
    }
}
//---------------------------------------------------------------------------
void Triangle::sort(double array[3][3], unsigned by)
{
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			if(array[j][by] > array[j + 1][by]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}
//---------------------------------------------------------------------------
