//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#pragma warning(disable : 8123)

#include "Main.h"
#include "Vertice.h"
#include "Edge.h"
#include "GraphicMatrix.h"
#include "GraphicObject.h"

#include <vector>
#include <DBXJSON.hpp>
#include <cmath>

#include "BezierSurface.h"

#define INTVALARR(array, index) array->Get(index)->Value().ToInt()
#define STRVALARR(array, index) array->Get(index)->Value()
#define STRVALOBJ(object, key) object->Get(key)->JsonValue->Value()
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TMainForm *MainForm;

double scale;
BezierSurface *surf;

typedef enum {
	JSONObjectUndefined,
	JSONObjectPoints,
	JSONObjectAxis,
	JSONObjectObject
} JSONObjectType;

//---------------------------------------------------------------------------
TJSONObject *parseJsonValue (TJSONValue *value)
{
	TJSONObject *jsonObj = new TJSONObject;
	TBytes jsonBytes = TEncoding::UTF8->GetBytes(value->ToString());
	jsonObj->Parse(jsonBytes, 0);
	return jsonObj;
}

TJSONArray *jsonArrayFromPair (TJSONPair *pair)
{
	return (TJSONArray *)pair->JsonValue;
}

void __fastcall TMainForm::ParseJSON (const UnicodeString& fileName)
{
	TStringList *jsonText = new TStringList;
	jsonText->LoadFromFile(fileName);

	TBytes jsonBytes = TEncoding::UTF8->GetBytes(jsonText->Text);
	delete jsonText;

	TJSONObject *json = new TJSONObject;
	json->Parse(jsonBytes, 0);

	TJSONObject *topObjectValueObj;

	// Points
	topObjectValueObj = parseJsonValue(json->Get("points")->JsonValue);

	for (int i = 0; i < topObjectValueObj->Size(); ++i) {
		TJSONPair *pair = topObjectValueObj->Get(i);
		TJSONArray *array = jsonArrayFromPair(pair);
//		Vertice *point = new Vertice(INTVALARR(array, 0),
//											 INTVALARR(array, 1),
//											 INTVALARR(array, 2));
//
//		points[pair->JsonString->Value()] = point;
	}

	delete topObjectValueObj;

	// Edges
	topObjectValueObj = parseJsonValue(json->Get("edges")->JsonValue);

	map<UnicodeString, TColor> *colors = new map<UnicodeString, TColor>;
	(*colors)["red"] = clRed;
	(*colors)["black"] = clBlack;
	(*colors)["green"] = clGreen;
	(*colors)["blue"] = clBlue;
	(*colors)["fuchsia"] = clFuchsia;
	(*colors)["lime"] = clLime;

	for (int i = 0; i < topObjectValueObj->Size(); ++i) {
		TJSONPair *pair = topObjectValueObj->Get(i);
		TJSONObject *object = parseJsonValue(pair->JsonValue);
		TJSONArray *array = jsonArrayFromPair(object->Get("vertices"));
//		Edge *edge = new Edge (points[STRVALARR(array, 0)], points[STRVALARR(array, 1)]);
//
//		if (object->Get("color")) {
//			edge->setPen((*colors)[STRVALOBJ(object, "color")], 1, psSolid);
//		}
//
//		edges[pair->JsonString->Value()] = edge;
	}

	delete colors;
	delete topObjectValueObj;

	// Objects
	topObjectValueObj = parseJsonValue(json->Get("objects")->JsonValue);

	for (int i = 0; i < topObjectValueObj->Size(); ++i) {
		TJSONPair *pair = topObjectValueObj->Get(i);
		TJSONObject *object = parseJsonValue(pair->JsonValue);
		TJSONArray *array = jsonArrayFromPair(object->Get("edges"));

		GraphicObject *graphicObject = new GraphicObject;

		for (int j = 0; j < array->Size(); ++j) {
			graphicObject->addEdge(edges[STRVALARR(array, j)]);
		}

		objects[pair->JsonString->Value()] = graphicObject;
	}

	delete topObjectValueObj;
}

void FillCanvasWithColor (TCanvas *canvas, TColor color)
{
	canvas->Brush->Color = color;
	canvas->FillRect(canvas->ClipRect);
}

__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner), isRotating(false)
{
	FillCanvasWithColor(ColorX->Canvas, clRed);
	FillCanvasWithColor(ColorY->Canvas, clGreen);
	FillCanvasWithColor(ColorZ->Canvas, clBlue);

	scale = 4;
	ScaleEdit->Value = scale;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawBtnClick(TObject *Sender)
{
//	delete objects["flippedmodel"];
//	objects["flippedmodel"] = new GraphicObject (*objects["model"]);
//
//	GraphicObject *flippedmodel = objects["flippedmodel"];
//
//	flippedmodel->hidden = ReflectionSurfaceSelect->ItemIndex == 0;
//
//	if (!flippedmodel->hidden) {
//		Matrix *flip;
//
//		switch (ReflectionSurfaceSelect->ItemIndex) {
//			case 1 :
//				flip = GetReflectionMatrix(AxisX, AxisY);
//				break;
//
//			case 2 :
//				flip = GetReflectionMatrix(AxisY, AxisZ);
//				break;
//
//			case 3 :
//				flip = GetReflectionMatrix(AxisX, AxisZ);
//				break;
//        }
//
//		flippedmodel->applyTransform(flip);
//		delete flip;
//	}
//
//	objects["flippedmodel"] = flippedmodel;

	drawObjects(Graph->Canvas, true);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::drawObjects(TCanvas *destCanvas, bool erase)
{
//	if (objects.size())
	{
//		if (erase) {
//			destCanvas->Brush->Color = clWhite;
//			destCanvas->FillRect(destCanvas->ClipRect);
//		}

//		Matrix *rotate = GetStandardRotationMatrix(angleX, angleY);

		scale = ScaleEdit->Value;

		Graphics::TBitmap *pic = new Graphics::TBitmap;
		pic->Height = destCanvas->ClipRect.Height();
		pic->Width = destCanvas->ClipRect.Width();

//		for (objectsIt i = objects.begin(); i != objects.end(); ++i) {
//			if (!i->second->hidden) {
//				GraphicObject *toDraw = new GraphicObject(*(i->second));
//				toDraw->applyRotation(angleY, angleX);
//				toDraw->draw(pic->Canvas);
//				delete toDraw;
//			}
//		}


				BezierSurface *toDraw = new BezierSurface(*surf);
				toDraw->applyRotation(angleY, angleX);
				toDraw->draw(pic->Canvas);
				delete toDraw;
//                                        surf->draw(pic->Canvas);
		destCanvas->Draw(0, 0, pic);
//		BitBlt(destCanvas->Handle,0,0,pic->Width,pic->Height,
//			pic->Canvas->Handle,0,0,SRCCOPY);
		delete pic;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenExecute(TObject *Sender)
{
	if (OpenJSON->Execute()) {
		if (FileExists(OpenJSON->FileName, true)) {
			points.clear();
			edges.clear();
			objects.clear();
			angleX = 0.6154797142073631;
			angleY = -M_PI/4.0;
			ParseJSON(OpenJSON->FileName);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::rotateByAngle(const Axis axis, const double angle)
{
	if (axis == AxisX) {
		angleX = angle;
	}
	else if (axis == AxisY) {
		angleY = angle;
	}

	drawObjects(Graph->Canvas, true);
}

int xc, yc;
double baseanglex, baseangley;

void __fastcall TMainForm::GraphMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	isRotating = true;
	baseanglex = angleX;
	baseangley = angleY;
	xc = X;
	yc = Y;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GraphMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	isRotating = false;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GraphMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	if (isRotating) {
		angleX = baseanglex+(double)(Y-yc)/180.0/10.0*M_PI;
		angleY = baseangley+(double)(X-xc)/180.0/10.0*M_PI;

		drawObjects (Graph->Canvas, true);
	}
}
//---------------------------------------------------------------------------


Matrix *getT(double t, int n)
{
	Matrix *T = new Matrix(1,n+1);

	for(int i = n; i > 0; --i)
		T->values[0][n-i] =  pow(t, i);
	T->values[0][n] = 1;
	return T;
}

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
//	unsigned pts = 3;
//	Matrix *T, *N, *B;
//
//	N = getN(pts);
//
//	B = new Matrix(4,2);
//	B->values[0][0] = 1;//00/2;
//	B->values[0][1] = 1;//00/2;
//	B->values[1][0] = 2;//00/2;
//	B->values[1][1] = 3;//00/2;
//	B->values[2][0] = 4;//00/2;
//	B->values[2][1] = 3;//00/2;
//	B->values[3][0] = 3;//00/2;
//	B->values[3][1] = 1;//00;
//
//	for(float i = 0; i <= 1; i += 0.0) {
//		T = getT(i, pts);
//
//		Matrix P = *T * *N * *B;
//
//		Graph->Canvas->Pixels[P.values[0][0]*50][350-P.values[0][1]*50]= clBlack;
//
//		delete T;
//	}
	surf = new BezierSurface(4,4);
}
//---------------------------------------------------------------------------
