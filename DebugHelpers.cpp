//---------------------------------------------------------------------------
#pragma hdrstop

#pragma warn -8123
#include "DebugHelpers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void debugOutWithStringAndDouble (const wchar_t *str, double number)
{
	UnicodeString ustr = "";
	ustr.printf (L"[%s : %lf]", str, number);
	OutputDebugString(ustr.c_str());
}
//---------------------------------------------------------------------------
void debugOutArray (double **array, int rows, int cols)
{
	OutputDebugString (L"Array =====>");
	for (int i = 0; i < rows; ++i) {
		UnicodeString ustr = "";

		for (int j = 0; j < cols; ++j) {
			ustr.cat_printf (L"%.2lf ", array[i][j]);
		}
		OutputDebugString(ustr.c_str());
	}
	OutputDebugString (L"Array <=====");
}
//---------------------------------------------------------------------------
void debugOutVector (vector< vector<double> > vect)
{
	OutputDebugString (L"Vector =====>");

	typedef vector< vector<double> >::iterator vIt;
	typedef vector<double>::iterator dIt;

	for (vIt i = vect.begin(); i != vect.end(); ++i) {
		UnicodeString ustr = "";

		for (dIt j = (*i).begin(); j != (*i).end(); ++j) {
			ustr.cat_printf (L"%.2lf ", *j);
		}
		OutputDebugString(ustr.c_str());
	}
	OutputDebugString (L"Vector <=====");
}
//---------------------------------------------------------------------------
void debugOutTime (time_t time)
{
	OutputDebugString (L"Time =====>");

	UnicodeString ustr = "";
	ustr.cat_printf(L"%lf", time);
	OutputDebugString(ustr.c_str());
}
//---------------------------------------------------------------------------
