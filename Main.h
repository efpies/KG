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
	TActionManager *ActionMgr;
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
	TTabSheet *Lab3;
	TRadioGroup *DrawStyleRadioGroup;
	TImage *FrontColorPicker;
	TImage *BackColorPicker;
	TLabel *Label6;
	TLabel *Label7;
	TGroupBox *GroupBox2;
	TColorDialog *PickColor;
	TEdit *SourcePosXTextField;
	TEdit *SourcePosYTextField;
	TEdit *SourcePosZTextField;
	TTabSheet *Lab4;
	TGroupBox *GroupBox3;
	TImage *SourceLightColorPicker;
	TLabel *Label8;
	TGroupBox *GroupBox4;
	TLabel *Label9;
	TLabel *Label11;
	TLabel *Label12;
	TButton *SourcePosXIncrementButton;
	TButton *SourcePosXDecrementButton;
	TButton *SourcePosYDecrementButton;
	TButton *SourcePosYIncrementButton;
	TButton *SourcePosZIncrementButton;
	TButton *SourcePosZDecrementButton;
	TImage *AmbientLightColorPicker;
	TLabel *Label13;
	TGroupBox *GroupBoxSourceLight;
	TGroupBox *GroupBoxAmbientLight;
	TTrackBar *AmbientLightIntensityTrackBar;
	TLabel *Label14;
	TTrackBar *DiffusionCoeffTrackBar;
	TLabel *Label15;
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
	void __fastcall FrontColorPickerClick(TObject *Sender);
	void __fastcall BackColorPickerClick(TObject *Sender);
	void __fastcall SourceLightColorPickerClick(TObject *Sender);
	void __fastcall SourcePosXIncrementButtonClick(TObject *Sender);
	void __fastcall SourcePosXDecrementButtonClick(TObject *Sender);
	void __fastcall SourcePosYIncrementButtonClick(TObject *Sender);
	void __fastcall SourcePosYDecrementButtonClick(TObject *Sender);
	void __fastcall SourcePosZIncrementButtonClick(TObject *Sender);
	void __fastcall SourcePosZDecrementButtonClick(TObject *Sender);
	void __fastcall AmbientLightColorPickerClick(TObject *Sender);
	void __fastcall AmbientLightIntensityTrackBarChange(TObject *Sender);

private:	// User declarations
	void __fastcall drawObjects(TCanvas *, bool);
	void __fastcall ParseJSON (const UnicodeString&);

	bool isRotating;
	double angleX;
	double angleY;
	BezierSurface *surface;

	// Custom methods
	void __fastcall refreshCaption();
	void __fastcall FillCanvasWithColor(TCanvas *, TColor);
	TColor __fastcall getPickerColor(TImage *);
	TColor __fastcall getSourceLightColor();
	double __fastcall getSourceLightPositionAtAxis(const Axis);
	TColor __fastcall getAmbientLightColor();
	double __fastcall getAmbientIntensityCoeff();
	double __fastcall getMaterialDiffusionCoeff();
	void __fastcall incrementTextField(TEdit *, const int);

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	map<UnicodeString, Vertice *> points;
	map<UnicodeString, Edge *> edges;
	map<UnicodeString, GraphicObject *> objects;

	__property TColor sourceLightColor = {read=getSourceLightColor};
	__property TColor ambientLightColor = {read=getAmbientLightColor};
	__property double sourcePositionAtAxis[const Axis axis] = {read=getSourceLightPositionAtAxis};
	__property double ambientIntensityCoeff = {read=getAmbientIntensityCoeff};
	__property double materialDiffusionCoeff = {read=getMaterialDiffusionCoeff};
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

	FillCanvasWithColor(FrontColorPicker->Canvas, clRed);
	FillCanvasWithColor(BackColorPicker->Canvas, clBlack);
	FillCanvasWithColor(SourceLightColorPicker->Canvas, clWhite);
	FillCanvasWithColor(AmbientLightColorPicker->Canvas, clWhite);

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
	destCanvas->Rectangle(destCanvas->ClipRect);
}
//---------------------------------------------------------------------------
TColor __fastcall TMainForm::getPickerColor(TImage *picker)
{
  	return picker->Canvas->Pixels[1][1];
}
//---------------------------------------------------------------------------
TColor __fastcall TMainForm::getSourceLightColor()
{
	return getPickerColor(SourceLightColorPicker);
}
//---------------------------------------------------------------------------
TColor __fastcall TMainForm::getAmbientLightColor()
{
	return getPickerColor(AmbientLightColorPicker);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::incrementTextField(TEdit *field, const int value)
{
	field->Text = field->Text.ToInt() + value;
}
//---------------------------------------------------------------------------
double __fastcall TMainForm::getSourceLightPositionAtAxis(const Axis axis)
{
	TEdit *axisTextField;

	switch(axis) {
		case AxisX :
			axisTextField = SourcePosXTextField;
			break;

		case AxisY :
			axisTextField = SourcePosYTextField;
			break;

		case AxisZ :
			axisTextField = SourcePosZTextField;
			break;
    }

	return axisTextField->Text.ToDouble();
}
//---------------------------------------------------------------------------
double __fastcall TMainForm::getAmbientIntensityCoeff()
{
	return (double)AmbientLightIntensityTrackBar->Position / (double)AmbientLightIntensityTrackBar->Max;
}
//---------------------------------------------------------------------------
double __fastcall TMainForm::getMaterialDiffusionCoeff()
{
	return (double)DiffusionCoeffTrackBar->Position / (double)DiffusionCoeffTrackBar->Max;
}
//---------------------------------------------------------------------------
#endif
