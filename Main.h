//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
#pragma warning(disable : 8123)
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include "cspin.h"
#include <Vcl.ComCtrls.hpp>
#include <map>
#include "Constants.h"
//---------------------------------------------------------------------------
class GraphicObject;
class Vertice;
class Edge;
class BezierSurface;

using namespace std;

typedef map<UnicodeString, GraphicObject *>::iterator objectsIt;

class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TActionManager *ActionManager1;
	TActionMainMenuBar *ActionMainMenuBar1;
	TButton *DrawBtn;
	TImage *Graph;
	TOpenDialog *OpenJSON;
	TRadioGroup *ReflectionSurfaceSelect;
	TGroupBox *GroupBox1;
	TImage *ColorX;
	TImage *ColorY;
	TImage *ColorZ;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label10;
	TCSpinEdit *ScaleEdit;
	TLabel *Label1;
	TButton *GenerateBezier;
	TButton *Open;
	TAction *CloseProgram;
	TPageControl *LabsTabs;
	TTabSheet *Lab1;
	TTabSheet *Lab2;
	TEdit *BezierRowsField;
	TLabel *Label2;
	TEdit *BezierColsField;
	TLabel *Label3;
	TLabeledEdit *BezierDetalizationField;
	TCheckBox *BezierHidePolys;
	void __fastcall DrawBtnClick(TObject *Sender);
	void __fastcall GraphMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall GraphMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall GraphMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall GenerateBezierClick(TObject *Sender);
	void __fastcall OpenClick(TObject *Sender);
	void __fastcall CloseProgramExecute(TObject *Sender);
	void __fastcall BezierHidePolysClick(TObject *Sender);
	void __fastcall LabsTabsChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
	void __fastcall drawObjects(TCanvas *, bool);
	void __fastcall ParseJSON (const UnicodeString&);

	bool isRotating;
	double angleX;
	double angleY;
	BezierSurface *surface;

	// Custom methods
	void __fastcall rotateByAngle(const Axis, const double);
	void __fastcall refreshCaption();
	void __fastcall FillCanvasWithColor(TCanvas *, TColor);

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	map<UnicodeString, Vertice *> points;
	map<UnicodeString, Edge *> edges;
	map<UnicodeString, GraphicObject *> objects;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
// Form lifecycle
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner), isRotating(false), surface(NULL), angleX(0.0), angleY(0.0)
{
	FillCanvasWithColor(ColorX->Canvas, clRed);
	FillCanvasWithColor(ColorY->Canvas, clGreen);
	FillCanvasWithColor(ColorZ->Canvas, clBlue);

	scale = 4;
	ScaleEdit->Value = scale;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	refreshCaption();
}
//---------------------------------------------------------------------------
// Custom
//---------------------------------------------------------------------------
void __fastcall TMainForm::refreshCaption()
{
	Caption = UnicodeString(L"") + L"Лабораторная работа №" + (LabsTabs->TabIndex + 1) + L" | Яснов Николай гр. 8306";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FillCanvasWithColor(TCanvas *destCanvas, TColor fillColor)
{
	destCanvas->Brush->Color = fillColor;
	destCanvas->FillRect(destCanvas->ClipRect);
}
//---------------------------------------------------------------------------
#endif
