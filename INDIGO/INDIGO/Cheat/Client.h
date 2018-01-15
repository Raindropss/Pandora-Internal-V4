#pragma once

#define DELETE_MOD(name) delete name; name = nullptr

#include "../Gui/Gui.h"
#include "../Engine/Engine.h"

#include "Aimbot/Aimbot.h"
#include "TriggerBot/Triggerbot.h"
#include "Esp/Esp.h"
#include "Misc/Misc.h"
#include "Skin/Skin.h"

#include "RageBot\RageBot.h"

#include "../Spoofed.h"

class AGui;

class AAimbot;
class AEsp;
class AMisc;
class ASkin;
class CRageBot;

namespace Engine
{
	class CRender;
	class APlayers;
}

using namespace Engine;

namespace Client
{
//[swap_lines]
	extern int iScreenWidth;
	extern int iScreenHeight;

	extern string BaseDir;
	extern string LogFile;
	extern string GuiFile;
	extern string IniFile;

	extern Vector2D		g_vCenterScreen;

	extern APlayers*	g_pPlayers;
	extern CRender*		g_pRender;
	extern AGui*		g_pGui;

	extern AAimbot*		g_pAimbot;
	extern ASkin*		g_pSkin;
	extern AEsp*		g_pEsp;
	extern AMisc*		g_pMisc;
	extern CRageBot*	g_pRageBot;

	extern bool			bC4Timer;
	extern int			iC4Timer;

	extern int			iWeaponID;
	extern int			iWeaponSelectSkinIndex;
	extern int			iWeaponSelectIndex;

	bool Initialize( IDirect3DDevice9* pDevice );
	void Shutdown();

	void OnRender();
	void OnLostDevice();
	void OnResetDevice();
	void OnCreateMove( CUserCmd* pCmd );
	void OnFireEventClientSideThink( IGameEvent* pEvent );
	void OnFrameStageNotify(ClientFrameStage_t Stage);
	void OnDrawModelExecute( IMatRenderContext* ctx , const DrawModelState_t &state , const ModelRenderInfo_t &pInfo , matrix3x4_t *pCustomBoneToWorld = NULL );
	void OnOverrideView( CViewSetup* pSetup );
	void OnRenderGUI();
//[/swap_lines]
}