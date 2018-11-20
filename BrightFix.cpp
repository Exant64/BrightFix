#pragma once
#include "SA2ModLoader.h"
#include "d3d9.h"
#include "d3dx9.h"
#include <string>
#include "structs.h"

//So a little explanation on some stuff
//The reason i replaced all shaders is because initially when I tried only changing the chao shader, if it uses pallettes it overwrote it. I figured out by now how to work around this too
//but after all the shit I went through I'm not gonna redo it, maybe a loooot later, i'm just happy i got the project off my back, i'll need to come back to it to add support for
//bright and shiny twotone coexistence because a lot of people requested
enum ShaderFlags
{
	None = 0x0,
	UseShadow = 0x1,
	UseFog = 0x2,
	UsePallette = 0x4,
};

enum ChunkMaterialFlagsEnum
{
	DontUseTexture = 0x1,
	HasSecondTexture = 0x2,
	SecondTextureEnvironmentMap = 0x4,
	UseChunkObjectColor = 0x8,
};

extern "C"
{
	DataPointer(WeirdChunkTexIndexThing, WeirdChunkTexIndex, 0x01A275A8);
	DataPointer(int, ShaderFlags, 0x01AF1960);
	DataPointer(char, LightIndex, 0x01DE4664);
	DataPointer(char, LightIndexBackupMaybe, 0x01DE4400);
	DataPointer(int, ChunkMatEnable, 0x01AED2CC);
	DataPointer(int, ChunkMatFlag, 0x01A27594);
	DataPointer(int, ChunkObjectColor, 0x01A275A4);
	DataPointer(int, dword_1A55828, 0x1A55828);
	DataPointer(int, dword_1A5582C, 0x1A5582C);
	DataPointer(int, ShaderBackup, 0x01A5579C);
	DataPointer(struc_36asd*, struc_36Instance, 0x01A557BC);
	DataPointer(RenderEngineThing*, dword_1A557C0, 0x1A557C0);
	DataPointer(NJS_TEXLIST, AL_BODY, 0x013669FC);

	DataArray(int, dword_1298448, 0x01298448, 20);
	DataArray(int, dword_1298414, 0x1298414, 12);
	DataArray(int, dword_12983DC, 0x12983DC, 12);
	DataArray(int, dword_12983A8, 0x12983A8, 12);

	FunctionPointer(int, __cdecl sub_56E1E0, (int a1), 0x56E1E0);
	FunctionPointer(void, sub_496310, (), 0x496310);
	FunctionPointer(int, __cdecl SetPixelShaderFloatAlmostAlwaysTEVMode, (int a1, int a2), 0x0041FCA0);
	FunctionPointer(void, sub_56DF50, (NJS_OBJECT* a1), 0x56DF50);
	StdcallFunctionPointer(void, SetAndLoadShader, (int a1), 0x00424050);
	ThiscallFunctionPointer(void, __thiscall LoadShaders, (struc_36asd *a1), 0x004248B0);

	const int SetShadersPtr = 0x0041B1F0;
	void SetShaders(int result)
	{
		__asm
		{
			mov eax, result
			call SetShadersPtr
		}
	}

	IDirect3DPixelShader9 *chaoPixelSimpleShader;
	IDirect3DPixelShader9 *chaoPixelPalletteShader;
	IDirect3DDevice9* device = NULL;

	void SetFlagOn() //i named them the opposite of what they are basically lol but that's ok for now I guess
	{
		float _test[4] = { 1,1,1,1 };
		device->SetPixelShaderConstantF(74, _test, 1);
	}
	void SetFlagOff()
	{
		float _test[4] = { 0,0,0,0 };
		device->SetPixelShaderConstantF(74, _test, 1);
	}
	const int sub_41FA60Ptr = 0x41FA60;
	void  sub_41FA60(WeirdChunkTexIndexThing *a1, signed int a2)
	{
		__asm
		{
			mov edi, a1
			push a2
			call sub_41FA60Ptr
			add esp, 4
		}
	}
	void  SetChunkTexIndexNull()
	{
		WeirdChunkTexIndex.texturePointer = 0;
		WeirdChunkTexIndex.tspparambuffer = -1;

		WeirdChunkTexIndex.tes3 = 1;
		WeirdChunkTexIndex.tes4 = 1;
		WeirdChunkTexIndex.a2 = 1;
		WeirdChunkTexIndex.a3 = 1;
		WeirdChunkTexIndex.tes5 = 0;
		//sub_41FA60(&WeirdChunkTexIndex, 0);
		sub_41FA60(&WeirdChunkTexIndex, 2);
	}
	void  SetChunkTexIndexNullZero()
	{

		WeirdChunkTexIndex.texturePointer = 0;
		WeirdChunkTexIndex.tspparambuffer = -1;

		WeirdChunkTexIndex.tes3 = 1;
		WeirdChunkTexIndex.tes4 = 1;
		WeirdChunkTexIndex.a2 = 1;
		WeirdChunkTexIndex.a3 = 1;
		WeirdChunkTexIndex.tes5 = 0;
		//sub_41FA60(&WeirdChunkTexIndex, 0);
		sub_41FA60(&WeirdChunkTexIndex, 0);
	}

	void SetChunkTexIndexReplace(int index, int a2, int a3)
	{
		int v3; // esi
		int index_; // ecx
		Uint32 v5; // eax
		int v6; // edx
		int v7; // ecx

		v3 = Has_texlist_batadvPlayerChara_in_it[8];
		index_ = 12 * index;
		v5 = *(int *)(*(int *)(*(int *)v3 + 12 * index + 8) + 12) + 4;
		v6 = *(int *)(v5 + 24) >> 31;
		if (*(int *)(v5 + 24) & 0x8000)
		{
			v7 = *(int *)(*(int *)(*(int *)v3 + index_ + 8) + 8);
			WeirdChunkTexIndex.texturePointer = *(int *)(v5 + 28);
			WeirdChunkTexIndex.tspparambuffer = v7;
		}
		else
		{
			WeirdChunkTexIndex.texturePointer = *(int *)(v5 + 28);
			WeirdChunkTexIndex.tspparambuffer = -1;
		}
		WeirdChunkTexIndex.tes3 = 1;
		WeirdChunkTexIndex.tes4 = 1;
		WeirdChunkTexIndex.a2 = a2;
		WeirdChunkTexIndex.a3 = a3;
		WeirdChunkTexIndex.tes5 = v6 != 0;
		//sub_41FA60(&WeirdChunkTexIndex, 0);

		sub_41FA60(&WeirdChunkTexIndex, 2);
	}

	const int DoLightingPtr = 0x00487060;
	void DoLighting(int a1)
	{
		__asm
		{
			mov eax, a1
			call DoLightingPtr
		}
	}

	void EggStartShaderHook()
	{
		SetFlagOn();
		DoLighting(LightIndex);
		SetFlagOff();

	}
	void EggEndHook()
	{
		SetFlagOn();
		DoLighting(LightIndexBackupMaybe);
		SetChunkTexIndexNull();

	}
	static void __declspec(naked) SetChunkTexIndex()
	{
		__asm
		{
			push[esp + 04h] // a3
			push ebx // a2
			push eax // index

			// Call your __cdecl function here:
			call SetChunkTexIndexReplace

			pop eax // index
			pop ebx // a2
			add esp, 4 // a3
			retn
		}
	}
	const int GetChunkTexIndexPtr = 0x0056D1F0;
	unsigned int GetChunkTexIndex(int a1)
	{
		int ret;
		__asm
		{
			mov eax, a1
			call GetChunkTexIndexPtr
			mov ret, eax
		}
		return ret;
	}
	const int SetChunkTexIndexOrigPtr = 0x0056E3D0;
	void  SetChunkTexIndexOriginal(int index, int a2, int a3)
	{
		__asm
		{
			push a3
			mov ebx, a2
			mov eax, index
			call SetChunkTexIndexOrigPtr
			add esp, 4
		}
	}

	void SetChunkTexIndexTempDisableFlag(int a1, int a2, int a3)
	{
		SetFlagOff();
		SetChunkTexIndexOriginal(a1, a2, a3);
		SetFlagOn();
	}


	void  ChaoColoringPatch(int texture, int color, int shiny, int highlights, int model)
	{
		signed int v5; // esi
		unsigned __int16 v6; // ax
		int v7; // eax
		bool v8; // zf
		unsigned __int16 v9; // ax

		/*
		if (shiny && texture && highlights) // lil extra I added, maybe will resurrect later
		{
			int flag = SecondTextureEnvironmentMap | HasSecondTexture | DontUseTexture;
			ChunkMatEnable = 1;
			SetChunkTexIndexTempDisableFlag(17 + texture, 1, 1);
			SetChunkTexIndexReplace(34, 0, 1);
			if (color)
			{
				flag |= UseChunkObjectColor;
				ChunkObjectColor = dword_1298448[color]; //dword_1298448 = chaoColors
			}
			ChunkMatFlag = flag;
			return;
		}
		*/
		v5 = 0;
		if (!model)
		{
			return;
		}
		if (shiny)
		{
			v5 = 6;
			v6 = GetChunkTexIndex(model);
			SetChunkTexIndexOriginal(v6, 1, 1);
			v7 = 34;
		LABEL_6:
			if (highlights && !texture) //HACK: !texture is to fix a problem regarding Shiny jewel monotones
				SetChunkTexIndexTempDisableFlag(v7, 1, 1);
			else SetChunkTexIndexReplace(v7, 1, 1);
			//if(highlights && !texture) //HACK: !texture is to fix a problem regarding Shiny jewel monotones
				//SetChunkTexIndexTempDisableFlag(v7, 1, 1);
			//else SetChunkTexIndexReplace(texture + 17, 0, 1);
			v8 = texture == 0;
			goto LABEL_7;
		}
		v8 = texture == 0;
		if (texture > 0)
		{
			ChunkObjectColor = -1;
			v5 = 12;
			v7 = texture + 17;
			SetChunkTexIndexTempDisableFlag(v7, 1, 1);
			//SetChunkTexIndexNullZero();
			v8 = texture == 0;
			goto LABEL_7;
		}
	LABEL_7:
		if (v8)
		{
			if (color > 0)
			{
				v5 |= 8u;
				ChunkObjectColor = dword_1298448[color];
			}
			if (highlights)
			{
				v5 |= 1u;
			}
			else
			{
				v9 = GetChunkTexIndex(model);
				SetChunkTexIndexOriginal(v9, 1, 1);
			}
		}
		if (v5)
		{
			ChunkMatEnable = 1;
			ChunkMatFlag = v5;
		}
		else
		{
			ChunkMatEnable = 0;
			ChunkMatFlag = 0;
		}
		//float test[4] = { 1,1,1,1 };
		//device->SetPixelShaderConstantF(74, test, 1);

	}

	void OverwriteSetShaders()
	{
		__asm
		{
			call SetShadersPtr
			call SetChunkTexIndexNull
		}
	}

	static void __declspec(naked) ChaoColoring()
	{
		__asm
		{
			push[esp + 10h] // model
			push[esp + 10h] // highlights
			push[esp + 10h] // shiny
			push[esp + 10h] // color
			push edi // texture

			// Call your __cdecl function here:
			call ChaoColoringPatch

			pop edi // texture
			add esp, 4 // color
			add esp, 4 // shiny
			add esp, 4 // highlights
			add esp, 4 // model
			retn
		}
	}
	void PatchEyelidEyeIssue()
	{
		SetChunkTexIndexNull();
		ChunkMatEnable = 0;
	}

	void LoadNewShaders()
	{
		//ShaderFlags |= UseShadow;
		//SetAndLoadShader(2);
		SetFlagOn();
		SetShaders(1);
		SetFlagOff();
		//if(ShaderFlags == None) //my old attempts at doing this without replacing them altogether
			//device->SetPixelShader(chaoPixelSimpleShader);
		//if(chaoVertexShader)
		//device->SetVertexShader(chaoVertexShader);
		//if (chaoPixelPalletteShader)
		//if(ShaderFlags & 2)
			//device->SetPixelShader(chaoPixelPalletteShader);
		//device->SetPixelShader(chaoPixelSimpleShader);
	}
	void CancelNewShaders()
	{
		SetFlagOn();
		SetShaders(ShaderBackup);
		SetFlagOn();//idk how pixelshaderconstantf works, is it specific to a shader?

		//SetPixelShaderFloatAlmostAlwaysTEVMode(74, 0);
		//if(chaoVertexShader)
		//device->SetVertexShader(chaoVertexShader);
		//if (chaoPixelPalletteShader)
		//if(ShaderFlags & 2)
			//device->SetPixelShader(chaoPixelPalletteShader);
		//device->SetPixelShader(chaoPixelSimpleShader);
	}

	std::wstring towstring(const std::string& v) //got this from some microsoft forum thing lol 
	{
		std::wstring out(v.size() + 1, L'\0');

		int size = MultiByteToWideChar(CP_UTF8, 0, v.c_str(), -1, &out[0], out.size());

		out.resize(size - 1);
		return out;
	}

	void ToyFix(NJS_OBJECT* obj)
	{
		SetFlagOn();
		sub_56DF50(obj);
		SetFlagOff();
	}

	void MedalWrap(NJS_OBJECT *object, int(__cdecl *callback)(NJS_CNK_MODEL *))
	{
		SetFlagOn();
		ProcessChunkModelsWithCallback(object, ProcessChunkModel);
		SetFlagOff();
	}

	void  EggColoring(int result, int a2)
	{
		int v2; // edx
		unsigned __int16 v3; // ax
		unsigned __int16 v4; // ax
		int v5; // ecx
		int v6; // ecx

		switch (a2)
		{
		case SA2BEggColour_Normal:
			ChunkMatEnable = 0;
			return;
		case SA2BEggColour_Yellow_MonoTone:
		case SA2BEggColour_White_MonoTone:
		case SA2BEggColour_Brown_MonoTone:
		case SA2BEggColour_SkyBlue_MonoTone:
		case SA2BEggColour_Pink_MonoTone:
		case SA2BEggColour_Blue_MonoTone:
		case SA2BEggColour_Grey_MonoTone:
		case SA2BEggColour_Green_MonoTone:
		case SA2BEggColour_Red_MonoTone:
		case SA2BEggColour_LimeGreen_MonoTone:
		case SA2BEggColour_Purple_MonoTone:
		case SA2BEggColour_Orange_MonoTone:
		case SA2BEggColour_Black_MonoTone:
			v2 = dword_1298448[a2];
			ChunkMatEnable = 1;
			ChunkMatFlag = 9;
			ChunkObjectColor = v2;
			return;
		case SA2BEggColour_Yellow_TwoTone:
		case SA2BEggColour_White_TwoTone:
		case SA2BEggColour_Brown_TwoTone:
		case SA2BEggColour_SkyBlue_TwoTone:
		case SA2BEggColour_Pink_TwoTone:
		case SA2BEggColour_Blue_TwoTone:
		case SA2BEggColour_Grey_TwoTone:
		case SA2BEggColour_Green_TwoTone:
		case SA2BEggColour_Red_TwoTone:
		case SA2BEggColour_LimeGreen_TwoTone:
		case SA2BEggColour_Purple_TwoTone:
		case SA2BEggColour_Orange_TwoTone:
		case SA2BEggColour_Black_TwoTone:
			ChunkMatEnable = 1;
			ChunkMatFlag = UseChunkObjectColor;
			v3 = GetChunkTexIndex(result);
			SetChunkTexIndexOriginal(v3, 1, 1);
			ChunkObjectColor = dword_1298414[a2];
			return;
		case SA2BEggColour_NormalShiny:
			ChunkMatFlag = SecondTextureEnvironmentMap | HasSecondTexture;
			Has_texlist_batadvPlayerChara_in_it[8] = (int)&AL_BODY;
			goto LABEL_6;
		case SA2BEggColour_YellowShiny_MonoTone:
		case SA2BEggColour_WhiteShiny_MonoTone:
		case SA2BEggColour_BrownShiny_MonoTone:
		case SA2BEggColour_SkyBlueShiny_MonoTone:
		case SA2BEggColour_PinkShiny_MonoTone:
		case SA2BEggColour_BlueShiny_MonoTone:
		case SA2BEggColour_GreyShiny_MonoTone:
		case SA2BEggColour_GreenShiny_MonoTone:
		case SA2BEggColour_RedShiny_MonoTone:
		case SA2BEggColour_LimeGreenShiny_MonoTone:
		case SA2BEggColour_PurpleShiny_MonoTone:
		case SA2BEggColour_OrangeShiny_MonoTone:
		case SA2BEggColour_BlackShiny_MonoTone:
			Has_texlist_batadvPlayerChara_in_it[8] = (int)&AL_BODY;
			v5 = dword_12983DC[a2];
			ChunkMatFlag = UseChunkObjectColor | SecondTextureEnvironmentMap | HasSecondTexture | DontUseTexture;
			ChunkObjectColor = v5;
			ChunkMatEnable = 1;
			v4 = GetChunkTexIndex(result);
			//SetChunkTexIndexOriginal(v4, 1, 1);
			SetChunkTexIndexTempDisableFlag(34, 1, 1);
			break;
		case SA2BEggColour_YellowShiny_TwoTone:
		case SA2BEggColour_WhiteShiny_TwoTone:
		case SA2BEggColour_BrownShiny_TwoTone:
		case SA2BEggColour_SkyBlueShiny_TwoTone:
		case SA2BEggColour_PinkShiny_TwoTone:
		case SA2BEggColour_BlueShiny_TwoTone:
		case SA2BEggColour_GreyShiny_TwoTone:
		case SA2BEggColour_GreenShiny_TwoTone:
		case SA2BEggColour_RedShiny_TwoTone:
		case SA2BEggColour_LimeGreenShiny_TwoTone:
		case SA2BEggColour_PurpleShiny_TwoTone:
		case SA2BEggColour_OrangeShiny_TwoTone:
		case SA2BEggColour_BlackShiny_TwoTone:
			Has_texlist_batadvPlayerChara_in_it[8] = (int)&AL_BODY;
			v6 = dword_12983A8[a2];
			ChunkMatFlag = UseChunkObjectColor | SecondTextureEnvironmentMap | HasSecondTexture;
			ChunkObjectColor = v6;
		LABEL_6:
			ChunkMatEnable = 1;
			v4 = GetChunkTexIndex(result);
			SetChunkTexIndexOriginal(v4, 1, 1);
			SetChunkTexIndexReplace(34, 1, 1);
			break;
		case SA2BEggColour_GlitchyNormal:										//nice IDA thing lol
		case SA2BEggColour_GlitchyNormal | SA2BEggColour_Yellow_MonoTone:
		case SA2BEggColour_GreenShiny_TwoTone | SA2BEggColour_Green_MonoTone:
		case SA2BEggColour_RedShiny_TwoTone | SA2BEggColour_Green_MonoTone:
		case SA2BEggColour_LimeGreenShiny_TwoTone | SA2BEggColour_Green_MonoTone:
		case SA2BEggColour_PurpleShiny_TwoTone | SA2BEggColour_Green_MonoTone:
		case SA2BEggColour_OrangeShiny_TwoTone | SA2BEggColour_Green_MonoTone:
		case SA2BEggColour_BlackShiny_TwoTone | SA2BEggColour_Green_MonoTone:
		case SA2BEggColour_GlitchyNormal | SA2BEggColour_Green_MonoTone:
		case SA2BEggColour_GlitchyNormal | SA2BEggColour_Red_MonoTone:
		case 0x40:
		case 0x41:
		case 0x42:
		case SA2BEggColour_Brown_MonoTone | 0x40:
		case 0x44:
			ChunkObjectColor = -1;
			ChunkMatEnable = 1;
			ChunkMatFlag = 12; //also fixed the egg problem , i made a patch for this before but now it's "baked" into this.
			Has_texlist_batadvPlayerChara_in_it[8] = (int)&AL_BODY;
			SetChunkTexIndexTempDisableFlag(a2 - 36, 1, 1);
			break;
		default:
			return;
		}
	}
	static void __declspec(naked) EggColoringHook()
	{
		__asm
		{
			push esi // a2
			push eax // result

			// Call your __cdecl function here:
			call EggColoring

			pop eax // result
			pop esi // a2
			retn
		}
	}

	void  HookReloadShaders()
	{
		LoadShaders(struc_36Instance);
		struc_36Instance->Shaders[1]->PixelShader->shaderData = chaoPixelSimpleShader; //replace shaders
		struc_36Instance->Shaders[5]->PixelShader->shaderData = chaoPixelPalletteShader;
	}

	__declspec(dllexport) void __cdecl Init(const char *path) 
	{
		device = dword_1A557C0->pointerToDevice;
		LPD3DXBUFFER  pSimpleShaderBuffer;
		LPD3DXBUFFER  pPalletteShaderBuffer;

		std::string pSimpleShaderString = std::string(path);
		std::string pPalletteShaderString = std::string(path);
		pSimpleShaderString.append("\\SimpleShader.hlsl");
		pPalletteShaderString.append("\\PalletteShader.hlsl");
	
		D3DXAssembleShaderFromFile(towstring(pSimpleShaderString).c_str(), 0, 0, 0, &pSimpleShaderBuffer, 0);
		D3DXAssembleShaderFromFile(towstring(pPalletteShaderString).c_str(), 0, 0, 0, &pPalletteShaderBuffer, 0);

		WriteCall((void*)0x0053FE8A, ToyFix); //same as the model wrap below 
		WriteCall((void*)0x00424063, HookReloadShaders);
		//WriteCall((void*)0x0042D4F0, HackSetShadersDrawCnkModel);
		WriteCall((void*)0x005401FD, MedalWrap); //because of the flag and the medals drawing in the same place as chao, they looked blank so I had to make this hack to fix them
		WriteCall((void*)0x057B6C5, EggStartShaderHook); //egg
		WriteJump((void*)0x0057B979, EggEndHook);
		WriteCall((void*)0x0054A13D, EggStartShaderHook); //eggshell
		WriteJump((void*)0x0054A4EA, EggEndHook);
		device->CreatePixelShader((DWORD*)pSimpleShaderBuffer->GetBufferPointer(), &chaoPixelSimpleShader); //creates shaders
		device->CreatePixelShader((DWORD*)pPalletteShaderBuffer->GetBufferPointer(), &chaoPixelPalletteShader);
		struc_36Instance->Shaders[1]->PixelShader->shaderData = chaoPixelSimpleShader; //replace shaders
		struc_36Instance->Shaders[5]->PixelShader->shaderData = chaoPixelPalletteShader;
		WriteJump((void*)0x0056D2A0, EggColoringHook); //hooks eggcoloring
		WriteCall((void*)0x054FFA1, LoadNewShaders); //chao setshaders hook
		WriteCall((void*)0x0055017E, CancelNewShaders);
		WriteCall((void*)0x0056D54D, LoadNewShaders); //eggcoloring general hook
		WriteJump((void*)0x0056D58A, CancelNewShaders);
		WriteData((char*)0x56DC17, (char)0); //hack tevmode so brightness doesnt happen
		WriteData((char*)0x56DC71, (char)0); //reenable environment map
		WriteJump((void*)0x0056D470, ChaoColoring); //chaocoloring hook
		WriteJump((void*)0x0056D58A, OverwriteSetShaders); //i dont know why im WriteJump onto it again but as long as it works im leaving it like this
		WriteCall((void*)0x00540402, PatchEyelidEyeIssue); //fixes the "Everything is shiny" glitch
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}

