#pragma once

#include "../../Engine/Engine.h"
#include "../../SDK/Recv.hpp"
#include "../../Sounds.h"
#include "../../SDK/LagComp.h"

#include <ctime>
#include <iostream>
#include <algorithm>

#include <d3dx9.h>

#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib") 

#define TICK_INTERVAL			(Interfaces::GlobalVars()->interval_per_tick)
#define TICKS_TO_TIME( t )		( Interfaces::GlobalVars()->interval_per_tick *( t ) )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

namespace Engine
{
	class CBaseEntity;
	class APlayer;
}

using namespace Engine;

struct Sound_s
{
	ULONGLONG dwTime;
	Vector vOrigin;
};

class AEsp
{
public:

	AEsp();
//[swap_lines]

	Color CT_HP_ColorM;
	Color TT_HP_ColorM;

	Color CT_AR_ColorM;
	Color TT_AR_ColorM;

	IMaterial* visible_flat;
	IMaterial* visible_tex;
	IMaterial* hidden_flat;
	IMaterial* hidden_tex;

	float fExplodeC4Timer;
	float fC4Timer;

	Color GetPlayerColor( APlayer* pPlayer );
	Color GetPlayerVisibleColor( APlayer* pPlayer );

	bool CheckPlayerTeam( APlayer* pPlayer );

	inline float CSGO_Armor(float flDamage, int ArmorValue)
	{
		float flArmorRatio = 0.5f;
		float flArmorBonus = 0.5f;
		if (ArmorValue > 0) {
			float flNew = flDamage * flArmorRatio;
			float flArmor = (flDamage - flNew) * flArmorBonus;

			if (flArmor > static_cast<float>(ArmorValue)) {
				flArmor = static_cast<float>(ArmorValue) * (1.f / flArmorBonus);
				flNew = flDamage - flArmor;
			}

			flDamage = flNew;
		}
		return flDamage;
	}

	void junk1();
	void junk2();
	void junk3();
	void junk4();
	void junk5();
	void junk6();
	void junk7();
	void junk8();
	void junk9();
	void junk10();
	void junk11();
	void junk12();
	void junk13();
	void junk14();

	void Junk();
	void Junk2();
	void Junk3();

	void DrawBombPlanted();

	void OnRender();
	void OnCreateMove( CUserCmd* pCmd );
	void OnReset();
	void OnEvents( IGameEvent* pEvent );
	void OnDrawModelExecute( IMatRenderContext* ctx , const DrawModelState_t &state , const ModelRenderInfo_t &pInfo , matrix3x4_t *pCustomBoneToWorld = NULL );
	//[/swap_lines]
private:
//[swap_lines]
	IClientEntity *BombCarrier;
	void DrawPlayerEsp( APlayer* pPlayer );
	void DrawPlayerSkeleton( APlayer* pPlayer );
	void DrawPlayerBulletTrace( APlayer* pPlayer );

	void DrawHitBoxLine( Vector* vHitBoxArray , Color color );
//[/swap_lines]
};