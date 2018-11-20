//UNUSED
//i had this for ShadowTest
#pragma once
#include "stdafx.h"
#include "SA2ModLoader.h"
FastcallFunctionPointer(double, __fastcall njCos, (signed int a1), 0x042AC30);
FastcallFunctionPointer(signed int, __fastcall njPushMatrix, (NJS_MATRIX_PTR a1), 0x0077FE10);
FastcallFunctionPointer(double, __fastcall njSin, (signed int a1), 0x0042AAB0);
FunctionPointer(signed int, njPushMatrixEx, (), 0x00429710);
FunctionPointer(signed int, njPopMatrixEx, (), 0x00429000);
DataPointer(float*, MatrixBase, 0x01A557FC);
void  njCalcVector(NJS_VECTOR *a1, NJS_VECTOR *a2, NJS_MATRIX_PTR a3);

const int njRotateYPtr = 0x004275B0;
void  njRotateY(NJS_MATRIX_PTR matrixPtr, signed int a2);

const int njTranslatePtr = 0x00427470;
void  njTranslate(float *a1, float a2, float a3, float a4);

const int njTranslateVPtr = 0x00428A30;
void  njTranslateV(NJS_VECTOR *a1);