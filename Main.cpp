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
int xc, yc;
double baseanglex, baseangley;

//---------------------------------------------------------------------------
// JSON parsing
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
TJSONArray *jsonArrayFromPair (TJSONPair *pair)
{
	return (TJSONArray *)pair->JsonValue;
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
// Mouse handling
//---------------------------------------------------------------------------
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
		angleX = (double)(Y - yc) / 180.0 * M_PI;
		angleY = (double)(X - xc) / 180.0 * M_PI;

		xc = X;
		yc = Y;

		drawObjects (Graph->Canvas, true);
	}
}
//---------------------------------------------------------------------------
// Buttons handling
//---------------------------------------------------------------------------
void __fastcall TMainForm::LabsTabsChange(TObject *Sender)
{
	refreshCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseProgramExecute(TObject *Sender)
{
	MainForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BezierHidePolysClick(TObject *Sender)
{
	if(surface) {
		surface->gridHidden = BezierHidePolys->Checked;
		drawObjects (Graph->Canvas, true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenClick(TObject *Sender)
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
void __fastcall TMainForm::GenerateBezierClick(TObject *Sender)
{
	delete surface;
	angleX = 0;
	angleY = 0;

	surface = new BezierSurface(BezierRowsField->Text.ToInt(),
								BezierColsField->Text.ToInt(),
								BezierDetalizationField->Text.ToInt(),
								BezierHidePolys->Checked,
								LabsTabs->TabIndex == 1);

	drawObjects (Graph->Canvas, true);
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
// Custom methods
//---------------------------------------------------------------------------
void __fastcall TMainForm::drawObjects(TCanvas *destCanvas, bool erase)
{
	if(surface) {
		scale = ScaleEdit->Value;

		Graphics::TBitmap *buffer = new Graphics::TBitmap;
		buffer->Width = destCanvas->ClipRect.Width();
		buffer->Height = destCanvas->ClipRect.Height();

		surface->applyRotation(angleX, angleY);
		surface->draw(buffer->Canvas);

		destCanvas->Draw(0, 0, buffer);

		delete buffer;

		angleX = angleY = 0;
	}
}
//---------------------------------------------------------------------------

