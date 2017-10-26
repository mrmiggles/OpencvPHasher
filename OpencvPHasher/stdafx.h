// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

//define 
#define DECLDIR __declspec(dllexport)
#define DLL_EXPORT


// Windows Header Files:
#include <windows.h>


//Opencv 3.3 specific
#include <opencv2/opencv.hpp>

//custom headers
#include "FeatureExtractor.h"
#include "Subject.h"
#include "HashComparitor.h"


using namespace std;
using namespace cv;

extern "C"
{

}
