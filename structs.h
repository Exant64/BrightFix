#pragma once
#include "SA2ModLoader.h"

struct  WeirdChunkTexIndexThing
{
	int texturePointer;
	int a3;
	int a2;
	int tes3;
	int tes4;
	int tes5;
	int tspparambuffer;
};
struct  RenderEngineThing
{
	void *vtable;
	char field_4[52];
	IDirect3DDevice9 *pointerToDevice;
	char field_3C[70];

};
struct  ShaderLight
{
	NJS_VECTOR LightPos;
	NJS_VECTOR lightDir;
	NJS_ARGB lightColor;
	NJS_ARGB lightAttenA;
	NJS_ARGB lightAttenK;
};
struct  DisplayData
{
	char byte0;
	char gap1[3];
	int Width;
	int Height;
	int dwordC;
	int dword10;
	int dword14;
	char byte18;
};
struct SamplerData
{
	int dword0;
	int dword4;
	int dword8;
	int dwordC;
	int dword10;
	int dword14;
	int dword18;
};
struct ShaderD3DPointerThing
{
	char gap0[12];
	void *shaderData;
};
struct ShaderData
{
	int field_0;
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	int field_24[20];
	int field_74;
	int field_78;
	int field_7C;
	int field_80;
	int field_84;
	int field_88;
	int field_8C;
	int field_90;
	int field_94;
	int field_98;
	int field_9C;
	int field_A0;
	int field_A4;
	int field_A8;
	int field_AC;
	int field_B0;
	int field_B4;
	int field_B8;
	int field_BC;
	int field_C0;
	int field_C4;
	int field_C8;
	int field_CC;
	int field_D0;
	int field_D4;
	int field_D8;
	int field_DC;
	int field_E0;
	int field_E4;
	int field_E8;
	ShaderD3DPointerThing *VertexShader;
	int field_F0;
	ShaderD3DPointerThing *PixelShader;
};
//I called it struc_36asd because struc_36 was already a thing and I didn't want to edit my copy of the headers since then people would have trouble compiling
struct  struc_36asd
{
	int field_0;
	char field_4;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
	int field_18;
	int FogParamA;
	float FogParamG;
	float FogParamR;
	NJS_ARGB FogColor;
	ShaderLight *gap38[1];
	char gap3C[68];
	NJS_MATRIX field_80;
	NJS_VECTOR field_C0[4];
	int field_F0;
	int field_F4;
	int field_F8;
	int field_FC;
	int field_100;
	int field_104;
	int field_108;
	int field_10C;
	int field_110;
	int field_114;
	int field_118;
	int field_11C;
	int field_120;
	int field_124;
	int field_128;
	int field_12C;
	int field_130;
	int field_134;
	int field_138;
	int field_13C;
	int field_140;
	int field_144;
	float field_148;
	int field_14C;
	int field_150;
	int field_154;
	int field_158;
	int field_15C;
	int field_160;
	int field_164;
	int field_168;
	int field_16C;
	int field_170;
	int field_174;
	int field_178;
	int field_17C;
	int field_180;
	int field_184;
	int field_188;
	int field_18C;
	int field_190;
	int field_194;
	int field_198;
	int field_19C;
	int field_1A0;
	int field_1A4;
	int field_1A8;
	float field_1AC;
	int field_1B0;
	int field_1B4;
	int field_1B8;
	int field_1BC;
	int field_1C0;
	int field_1C4;
	int field_1C8;
	int field_1CC;
	int field_1D0;
	int field_1D4;
	int field_1D8;
	int field_1DC;
	int field_1E0;
	float field_1E4;
	int field_1E8;
	float field_1EC;
	float field_1F0;
	int field_1F4;
	int field_1F8;
	int field_1FC;
	int field_200;
	int field_204;
	int field_208;
	float field_20C;
	int field_210;
	int field_214;
	int field_218;
	int field_21C;
	int field_220;
	int field_224;
	int field_228;
	int field_22C;
	int field_230;
	int field_234;
	float field_238;
	int field_23C;
	int field_240;
	int field_244;
	int field_248;
	int field_24C;
	int field_250;
	int field_254;
	float MaterialSrcType[4];
	float AmbientSrcType[4];
	float DiffAttenSelect[4];
	float LightFuncEnable[4];
	float AttnFunc[4];
	NJS_ARGB LightMasks[6];
	NJS_ARGB SomeColorArray[2];
	NJS_MATRIX field_328;
	NJS_MATRIX ProjMatrix;
	NJS_MATRIX field_3A8;
	NJS_MATRIX TexMatrices[4];
	int field_4E8;
	int field_4EC;
	int field_4F0;
	int field_4F4;
	int field_4F8;
	int field_4FC;
	int field_500;
	int field_504;
	int field_508;
	int field_50C;
	int field_510;
	int field_514;
	int field_518;
	int field_51C;
	int field_520;
	float field_524;
	int field_528;
	int field_52C;
	int field_530;
	int field_534;
	int field_538;
	int field_53C;
	int field_540;
	int field_544;
	int field_548;
	int field_54C;
	int field_550;
	int field_554;
	int field_558;
	int field_55C;
	int field_560;
	int field_564;
	int field_568;
	int field_56C;
	int field_570;
	int field_574;
	int field_578;
	int field_57C;
	char gap580[128];
	int field_5E8;
	int field_5EC;
	D3DVIEWPORT9 Viewport;
	SamplerData samplerData;
	float field_63C;
	int field_640;
	char ReloadShaders;
	ShaderData *Shaders[1];
	int field_64C;
	int field_650;
	int TexturePointer;
	int gap640;
	int NeedToLoadShaders;
	int ShaderData;
	int field_664;
	int field_668;
	int field_66C;
	int field_670;
	int field_674;
	int field_678;
	DisplayData DisplayDataThing;
	int field_698;
	int field_69C;
	int field_6A0;
};
