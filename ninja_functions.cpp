//UNUSED
//i had this for ShadowTest
#include "ninja_functions.h"
void  njCalcVector(NJS_VECTOR *a1, NJS_VECTOR *a2, NJS_MATRIX_PTR a3)
{
	Float v3; // ST00_4
	Float v4; // ST04_4

	v3 = a3[M10] * a1->x + a3[M11] * a1->y + a3[M12] * a1->z;
	v4 = a3[M20] * a1->x + a3[M21] * a1->y + a3[M22] * a1->z;
	a2->x = a3[M01] * a1->y + *a3 * a1->x + a3[M02] * a1->z;
	a2->y = v3;
	a2->z = v4;
}

void  njRotateY(NJS_MATRIX_PTR matrixPtr, signed int a2)
{
	__asm
	{
		push a2
		mov ebx, matrixPtr
		call njRotateYPtr
		add esp, 4
	}

}

void  njTranslate(float *a1, float a2, float a3, float a4)
{
	__asm
	{
		push a4
		push a3
		push a2
		mov eax, a1
		call njTranslatePtr
		add esp, 12
	}
}

void  njTranslateV(NJS_VECTOR *a1)
{
	__asm
	{
		mov eax, a1
		call njTranslateVPtr
	}
}