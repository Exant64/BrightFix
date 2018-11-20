//UNUSED
//you can read it through though if you want, basically I was researching how the game does shadows

#include "ShadowTest.h"

const int sub_6BD4C0Ptr = 0x6BD4C0;
void  sub_6BD4C0(int a1, int a2)
{
	//int result;
	__asm
	{
		mov edi, a1
		mov esi, a2
		call sub_6BD4C0Ptr
		//mov result, eax
	}
	//return result;
}

const int sub_6BD1E0Ptr = 0x6BD1E0;
void sub_6BD1E0(int a1, float a2, float a3, float a4, NJS_VECTOR *a5)
{
	__asm
	{
		push a5
		push a4
		push a3
		push a2
		mov ebx, a1
		call sub_6BD1E0Ptr
		add esp, 16
	}
}
FunctionPointer(void, sub_6BD450, (), 0x6BD450);

FunctionPointer(void, __cdecl sub_495D20, (int a1, float a2, int a3, int a4, int a5),0x495D20);

void ShadowHook_Chao_Display2C(ObjectMaster* a1)
{
	sub_6BD1E0((int)&a1->field_4C, 2.5, 1.0, 0.0, &a1->Data1.Entity->Position);

	//insert drawing code here
	njPushMatrixEx();

	njTranslateV(&a1->Data1.Entity->Position);
	*(int*)((int)Has_texlist_batadvPlayerChara_in_it + 0x20) = 0x01366AFC;
	ProcessChunkModelsWithCallback((NJS_OBJECT *)0x125BF74, ProcessChunkModel);
	njPopMatrixEx();
	//end drawing code here
	int v3 = (int)a1->field_4C;
	sub_6BD450();
	sub_495D20(2, 90, v3 + 112, *(int *)(v3 + 144), v3 + 148);
}
void ShadowHook_Radio_Display2C(ObjectMaster* a1)
{
	sub_6BD1E0((int)&a1->EntityData2->WeirdStructures[0].field_14.z, 2.5, 1.0, 0.0, &a1->Data1.Entity->Position);

	//insert drawing code here
	njPushMatrixEx();

	njTranslateV(&a1->Data1.Entity->Position);
	*(int*)((int)Has_texlist_batadvPlayerChara_in_it + 0x20) = 0x01366AFC;
	ProcessChunkModelsWithCallback((NJS_OBJECT *)0x125BF74, ProcessChunkModel);
	njPopMatrixEx();
	//end drawing code here
	
	sub_6BD450();
	sub_495D20(
		2,
		90.0,
		(int)&a1->EntityData2->WeirdStructures[2].gap_4[8],
		(int)(a1->EntityData2->WeirdStructures[3].field_10),
		(int)&a1->EntityData2->WeirdStructures[0].field_14.z);
}
void ALO_RadicaseExecutor_LoadEdit(NJS_VECTOR *a1)
{
	/*
	ObjectMaster* v1 = LoadObject(4, "ALO_RadicaseExecutor", ALO_RadicaseExecutor_Main, LoadObj_Data1);
	//AllocatedMem* v12 = (AllocatedMem *)MemoryManager->Allocate(356, "..\\..\\src\\stg13_cityescape\\o_ce_car.c", 3089);
	//int v13 = (int)&v12->Data;
	//v12->Cookie = 305419896;
	//memset(&v12->Data, 0, 0x160u);
	//v1->EntityData2 = (UnknownData2 *)v13;
	ALO_RadicaseExecutor_ptr = v1;
	//int v22 = (int)&v1->EntityData2->WeirdStructures[0].field_14.z;
	//sub_6BD4C0(32, v22);
	//v1->field_2C = ShadowHook_Radio_Display2C;
	InitCollision(v1, (CollisionData*)0x008A5810, 1, 4u);
	AddToGlobalChaoThingMaybe(6u, v1, 3, 0);
	v1->Data1.Entity->Position = *a1;
	v1->Data1.Entity->Rotation.y = 4096;
	v1->DisplaySub = ALO_RadicaseExecutor_Display;
	v1->DeleteSub = ALO_RadicaseExecutor_Delete;
	*/
}


ObjectMaster* ShadowHook_CreateChao(ChaoData *chaoData, int a2, void *a3, NJS_VECTOR *position, Angle angle)
{
	ObjectMaster* ret = CreateChao(chaoData, a2, a3, position, angle);
	AllocatedMem* allocatedMem = (AllocatedMem *)MemoryManager->Allocate(92, "..\\..\\src\\ShadowTest.cpp", 24); //code originally taken from meteorherd
	void* v2 = &allocatedMem->Data;
	allocatedMem->Cookie = 0x12345678;
	memset(&allocatedMem->Data, 0, 0x58u);
	ret->field_4C = v2;
	if (ret->field_4C)
	{
		sub_6BD4C0(64, (int)ret->field_4C);
		ret->field_2C = ShadowHook_Chao_Display2C;
	}
	return ret;
}

void ShadowHook_Init()
{
	//NJS_OBJECT** chaoModels = (NJS_OBJECT**)GetDllData("AL_RootObject");
	//*chaoModels[0] = object_00004B84;
	//WriteData((short*)0x0054B995, (short)0x9090);
	//WriteJump((void*)0x0057CCA0, ALO_RadicaseExecutor_LoadEdit);
	//WriteCall((void*)0x00531D91, ShadowHook_CreateChao);
}