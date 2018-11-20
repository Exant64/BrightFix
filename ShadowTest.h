//UNUSED
//you can read it through though if you want, basically I was researching how the game does shadows


#pragma once
#include "stdafx.h"
#include "SA2ModLoader.h"
#include "ninja_functions.h"


void ShadowHook_Chao_Display2C(ObjectMaster* a1);
ObjectMaster* ShadowHook_CreateChao(ChaoData *chaoData, int a2, void *a3, NJS_VECTOR *position, Angle angle);
void ShadowHook_Init();