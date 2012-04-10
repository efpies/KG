//---------------------------------------------------------------------------
#ifndef DebugHelpersH
#define DebugHelpersH

#include <vcl.h>
#include <windows.h>
#include <vector>
#include <ctime>
using namespace std;
//---------------------------------------------------------------------------
void debugOutWithStringAndDouble (const wchar_t*, double);
void debugOutArray (double**, int rows, int cols);
void debugOutVector (vector< vector<double> > vect);
void debugOutTime (time_t);
//---------------------------------------------------------------------------
#endif
