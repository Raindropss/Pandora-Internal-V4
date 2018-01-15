#include "Misc.h"


using namespace Client;
//[junk_enable /]
//[enc_string_enable /]
void CMisc::OnRender()
{
	if ( Settings::Misc::misc_Punch )
	{
		int punch_x = (int)g_vCenterScreen.x + (int)g_pPlayers->GetLocal()->vAimPunch.y * 10;
		int punch_y = (int)g_vCenterScreen.y + (int)g_pPlayers->GetLocal()->vAimPunch.x * 10;

		g_pRender->DrawFillBox( punch_x - 1 , punch_y - 1 , 3 , 3 , Color::Green() );
	}
}

void CMisc::Junkcode()
{
	float lEOhOQJHEz = 77299658560571; lEOhOQJHEz = 47499809411835; if (lEOhOQJHEz = 69803406321480) lEOhOQJHEz = 79194162801021; lEOhOQJHEz = 44593361394145; lEOhOQJHEz = 13941454459336;
	if (lEOhOQJHEz = 97264957919416)lEOhOQJHEz = 63214804230453; lEOhOQJHEz = 76435873921467;
	if (lEOhOQJHEz = 89788186508792)lEOhOQJHEz = 63214804230453; lEOhOQJHEz = 76435873921467;
	if (lEOhOQJHEz = 89788186508792)lEOhOQJHEz = 63214804230453; lEOhOQJHEz = 76435873921467;
	if (lEOhOQJHEz = 89788186508792)lEOhOQJHEz = 63214804230453; lEOhOQJHEz = 76435873921467;
	if (lEOhOQJHEz = 89788186508792)lEOhOQJHEz = 63214804230453; lEOhOQJHEz = 76435873921467; lEOhOQJHEz = 62795759028519;

	float YBGBOYFDNu = 40589366358954; YBGBOYFDNu = 40907038787472; if (YBGBOYFDNu = 14752626704569) YBGBOYFDNu = 80356675670558; YBGBOYFDNu = 20182992494110; YBGBOYFDNu = 24941102018299;
	if (YBGBOYFDNu = 43523008035667)YBGBOYFDNu = 67045699701956; YBGBOYFDNu = 58396052954020;
	if (YBGBOYFDNu = 85193455472660)YBGBOYFDNu = 67045699701956; YBGBOYFDNu = 58396052954020;
	if (YBGBOYFDNu = 85193455472660)YBGBOYFDNu = 67045699701956; YBGBOYFDNu = 58396052954020;
	if (YBGBOYFDNu = 85193455472660)YBGBOYFDNu = 67045699701956; YBGBOYFDNu = 58396052954020;
	if (YBGBOYFDNu = 85193455472660)YBGBOYFDNu = 67045699701956; YBGBOYFDNu = 58396052954020; YBGBOYFDNu = 48391811941010;


}

void CMisc::OnCreateMove( CUserCmd* pCmd )
{
	if ( Settings::Misc::misc_Bhop )
	{
		if ( pCmd->buttons & IN_JUMP && !( g_pPlayers->GetLocal()->iFlags & FL_ONGROUND ) )
		{
			pCmd->buttons &= ~IN_JUMP;
		}
	}

	if (Settings::Misc::misc_spamregular)
		ChatSpamRegular();

	if (Settings::Misc::misc_spamrandom)
		ChatSpamRandom();

	if (Settings::Misc::misc_Clan > 0)
		ClanTag();

	ConVar* skybox = Interfaces::GetConVar()->FindVar("sv_skyname");

	if (Settings::Misc::misc_SkyName) { if (skybox) skybox->SetValue(Settings::Misc::misc_SkyName); }
	if (Settings::Misc::misc_NoSky) { if (skybox) skybox->SetValue("sky_l4d_rural02_ldr"); }

	ConVar* snow = Interfaces::GetConVar()->FindVar("mat_drawgray");

	if (Settings::Misc::misc_Snow)
	{
		snow->SetValue(1);
	}
	else
	{
		snow->SetValue(0);
	}

	ConVar* postprocess = Interfaces::GetConVar()->FindVar("mat_postprocess_enable");

	if (Settings::Misc::misc_EPostprocess)
	{
		if (Interfaces::Engine()->IsInGame())
		{
			postprocess->SetValue(0);
		}
	}
	else
	{
		if (Interfaces::Engine()->IsInGame())
		{
			postprocess->SetValue(1);
		}
	}


	if ( Settings::Misc::misc_AutoStrafe && !( g_pPlayers->GetLocal()->iFlags & FL_ONGROUND ) )
	{
		if ( pCmd->mousedx < 0 )
		{
			pCmd->sidemove = -450.0f;
		}
		else if ( pCmd->mousedx > 0 )
		{
			pCmd->sidemove = 450.0f;
		}
	}
	if (Settings::Misc::misc_slidewalk && !(g_pPlayers->GetLocal()->iFlags & MOVETYPE_LADDER))
	{
		if (pCmd->forwardmove > 0)
		{
			pCmd->buttons |= IN_BACK;
			pCmd->buttons &= ~IN_FORWARD;
		}

		if (pCmd->forwardmove < 0)
		{
			pCmd->buttons |= IN_FORWARD;
			pCmd->buttons &= ~IN_BACK;
		}

		if (pCmd->sidemove < 0)
		{
			pCmd->buttons |= IN_MOVERIGHT;
			pCmd->buttons &= ~IN_MOVELEFT;
		}

		if (pCmd->sidemove > 0)
		{
			pCmd->buttons |= IN_MOVELEFT;
			pCmd->buttons &= ~IN_MOVERIGHT;
		}
	}
}





void CMisc::Junkcode2()
{
	float HOnpYjCQFK = 38755067856865; HOnpYjCQFK = 54600879892579; if (HOnpYjCQFK = 36598331773619) HOnpYjCQFK = 60313729807290; HOnpYjCQFK = 78004729589727; HOnpYjCQFK = 95897277800472;
	if (HOnpYjCQFK = 76453266031372)HOnpYjCQFK = 17736195812356; HOnpYjCQFK = 63394155506103;
	if (HOnpYjCQFK = 74585532618660)HOnpYjCQFK = 17736195812356; HOnpYjCQFK = 63394155506103;
	if (HOnpYjCQFK = 74585532618660)HOnpYjCQFK = 17736195812356; HOnpYjCQFK = 63394155506103;
	if (HOnpYjCQFK = 74585532618660)HOnpYjCQFK = 17736195812356; HOnpYjCQFK = 63394155506103;
	if (HOnpYjCQFK = 74585532618660)HOnpYjCQFK = 17736195812356; HOnpYjCQFK = 63394155506103; HOnpYjCQFK = 96463993997626;

	float itCxVJSbGn = 48900524232143; itCxVJSbGn = 57453065390777; if (itCxVJSbGn = 15676047816455) itCxVJSbGn = 45710235028933; itCxVJSbGn = 66090083631650; itCxVJSbGn = 36316506609008;
	if (itCxVJSbGn = 50253534571023)itCxVJSbGn = 78164554557196; itCxVJSbGn = 9019029669166;
	if (itCxVJSbGn = 11136527970502)itCxVJSbGn = 78164554557196; itCxVJSbGn = 9019029669166;
	if (itCxVJSbGn = 11136527970502)itCxVJSbGn = 78164554557196; itCxVJSbGn = 9019029669166;
	if (itCxVJSbGn = 11136527970502)itCxVJSbGn = 78164554557196; itCxVJSbGn = 9019029669166;
	if (itCxVJSbGn = 11136527970502)itCxVJSbGn = 78164554557196; itCxVJSbGn = 9019029669166; itCxVJSbGn = 90918795625785;


}

void CMisc::FrameStageNotify(ClientFrameStage_t Stage)
{
	CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (Interfaces::Engine()->IsInGame() && localplayer && Stage == ClientFrameStage_t::FRAME_RENDER_START)
	{
		static QAngle vecAngles;
		Interfaces::Engine()->GetViewAngles(vecAngles);
		if (Settings::Misc::misc_ThirdPerson && !localplayer->IsDead())
		{
			if (!Interfaces::Input()->m_fCameraInThirdPerson)
				Interfaces::Input()->m_fCameraInThirdPerson = true;

			Interfaces::Input()->m_vecCameraOffset = QAngle(vecAngles.x, vecAngles.y, Settings::Misc::misc_ThirdPersonRange);

			*localplayer->GetVAngles() = Settings::Misc::qLastTickAngle;
		}
		else
		{
			if (Interfaces::Input()->m_fCameraInThirdPerson || localplayer->GetIsScoped())
			{
				Interfaces::Input()->m_fCameraInThirdPerson = false;
				Interfaces::Input()->m_vecCameraOffset = QAngle(vecAngles.x, vecAngles.y, 0);
			}
		}
	}
}

void CMisc::OnDrawModelExecute()
{
	static bool NoFlashReset = false;

	if ( Settings::Misc::misc_NoFlash && !NoFlashReset )
	{
		IMaterial* flash = Interfaces::MaterialSystem()->FindMaterial(
			"effects\\flashbang" ,  TEXTURE_GROUP_CLIENT_EFFECTS );

		IMaterial* flashWhite = Interfaces::MaterialSystem()->FindMaterial( "effects\\flashbang_white" ,
																			TEXTURE_GROUP_CLIENT_EFFECTS );

		if ( flash && flashWhite )
		{
			flash->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW , true );
			flashWhite->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW , true );

			NoFlashReset = true;
		}
	}
	else if ( !Settings::Misc::misc_NoFlash && NoFlashReset )
	{
		IMaterial* flash = Interfaces::MaterialSystem()->FindMaterial(
			"effects\\flashbang" , TEXTURE_GROUP_CLIENT_EFFECTS );

		IMaterial* flashWhite = Interfaces::MaterialSystem()->FindMaterial( "effects\\flashbang_white" ,
																			TEXTURE_GROUP_CLIENT_EFFECTS );

		if ( flash && flashWhite )
		{
			flash->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW , false );
			flashWhite->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW , false );

			NoFlashReset = false;
		}
	}
}

void CMisc::Junkcode3()
{
	float zObFgwNTTg = 50538547183321; zObFgwNTTg = 19518991044015; if (zObFgwNTTg = 16038337469722) zObFgwNTTg = 4965874493062; zObFgwNTTg = 78398856666312; zObFgwNTTg = 66663127839885;
	if (zObFgwNTTg = 5792496587)zObFgwNTTg = 74697228108944; zObFgwNTTg = 8152357855852;
	if (zObFgwNTTg = 65435867460729)zObFgwNTTg = 74697228108944; zObFgwNTTg = 8152357855852;
	if (zObFgwNTTg = 65435867460729)zObFgwNTTg = 74697228108944; zObFgwNTTg = 8152357855852;
	if (zObFgwNTTg = 65435867460729)zObFgwNTTg = 74697228108944; zObFgwNTTg = 8152357855852;
	if (zObFgwNTTg = 65435867460729)zObFgwNTTg = 74697228108944; zObFgwNTTg = 8152357855852; zObFgwNTTg = 68016432744295;

	float erjLMleWBv = 53357687403070; erjLMleWBv = 20326699616191; if (erjLMleWBv = 73319811036077) erjLMleWBv = 75347925468584; erjLMleWBv = 2347902703036; erjLMleWBv = 2703036234790;
	if (erjLMleWBv = 59145097534792)erjLMleWBv = 10360776345151; erjLMleWBv = 29840133566693;
	if (erjLMleWBv = 55436292812896)erjLMleWBv = 10360776345151; erjLMleWBv = 29840133566693;
	if (erjLMleWBv = 55436292812896)erjLMleWBv = 10360776345151; erjLMleWBv = 29840133566693;
	if (erjLMleWBv = 55436292812896)erjLMleWBv = 10360776345151; erjLMleWBv = 29840133566693;
	if (erjLMleWBv = 55436292812896)erjLMleWBv = 10360776345151; erjLMleWBv = 29840133566693; erjLMleWBv = 11771056945792;

}

void CMisc::OnPlaySound( const char* pszSoundName )
{
	if (Settings::Misc::misc_AutoAccept && !strcmp(pszSoundName, "!UI/competitive_accept_beep.wav"))
	{
		typedef void( *IsReadyCallBackFn )( );

		IsReadyCallBackFn IsReadyCallBack = 0;

		if ( !IsReadyCallBack )
		{
			IsReadyCallBack = (IsReadyCallBackFn)(
				CSX::Memory::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 83 BE", 0));

			#if ENABLE_DEBUG_FILE == 1
				CSX::Log::Add( "::IsReadyCallBack = %X", IsReadyCallBack);
			#endif
		}

		if ( IsReadyCallBack )
		{
			IsReadyCallBack();
		}
	}
}

void CMisc::OnOverrideView( CViewSetup * pSetup )
{
	if ( Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot() )
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity( Interfaces::Engine()->GetLocalPlayer() );

		if (!pPlayer)
			return;

		if (pPlayer->GetIsScoped())
			return;

		if ( pPlayer->IsDead() )
		{
			if ( pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget() )
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle( pPlayer->GetObserverTarget() );

			if ( !pPlayer )
				return;
		}

		pSetup->fov = (float)Settings::Misc::misc_FovView;
	}
}

void CMisc::OnGetViewModelFOV(float& fov)
{
	if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot())
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		fov = (float)Settings::Misc::misc_FovModelView;
	}
}
void CMisc::Junkcode4()
{
	float PJorpIvMXA = 81301287921405; PJorpIvMXA = 43514932154594; if (PJorpIvMXA = 70197959702882) PJorpIvMXA = 41300848158669; PJorpIvMXA = 43197662585557; PJorpIvMXA = 25855574319766;
	if (PJorpIvMXA = 8764284130084)PJorpIvMXA = 97028829133293; PJorpIvMXA = 50703181554606;
	if (PJorpIvMXA = 75894112396983)PJorpIvMXA = 97028829133293; PJorpIvMXA = 50703181554606;
	if (PJorpIvMXA = 75894112396983)PJorpIvMXA = 97028829133293; PJorpIvMXA = 50703181554606;
	if (PJorpIvMXA = 75894112396983)PJorpIvMXA = 97028829133293; PJorpIvMXA = 50703181554606;
	if (PJorpIvMXA = 75894112396983)PJorpIvMXA = 97028829133293; PJorpIvMXA = 50703181554606; PJorpIvMXA = 30302606028661;

	float TuIHGUzOSt = 71169728943938; TuIHGUzOSt = 4977632335479; if (TuIHGUzOSt = 11313707885344) TuIHGUzOSt = 94303327211373; TuIHGUzOSt = 38230731613480; TuIHGUzOSt = 16134803823073;
	if (TuIHGUzOSt = 21708309430332)TuIHGUzOSt = 78853449960538; TuIHGUzOSt = 87205813376032;
	if (TuIHGUzOSt = 25584839939721)TuIHGUzOSt = 78853449960538; TuIHGUzOSt = 87205813376032;
	if (TuIHGUzOSt = 25584839939721)TuIHGUzOSt = 78853449960538; TuIHGUzOSt = 87205813376032;
	if (TuIHGUzOSt = 25584839939721)TuIHGUzOSt = 78853449960538; TuIHGUzOSt = 87205813376032;
	if (TuIHGUzOSt = 25584839939721)TuIHGUzOSt = 78853449960538; TuIHGUzOSt = 87205813376032; TuIHGUzOSt = 58418677597502;

}
vector<int> CMisc::GetObservervators( int playerId )
{
	vector<int> SpectatorList;

	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity( playerId );

	if ( !pPlayer )
		return SpectatorList;

	if ( pPlayer->IsDead() )
	{
		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle( pPlayer->GetObserverTarget() );

		if ( !pObserverTarget )
			return SpectatorList;

		pPlayer = pObserverTarget;
	}

	for ( int PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++ )
	{
		CBaseEntity* pCheckPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity( PlayerIndex );

		if ( !pCheckPlayer )
			continue;

		if ( pCheckPlayer->IsDormant() || !pCheckPlayer->IsDead() )
			continue;

		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle( pCheckPlayer->GetObserverTarget() );

		if ( !pObserverTarget )
			continue;

		if ( pPlayer != pObserverTarget )
			continue;

		SpectatorList.push_back( PlayerIndex );
	}

	return SpectatorList;
}

void CMisc::Junkcode5()
{
	float NjttOOinRV = 893455954791; NjttOOinRV = 78244297031844; if (NjttOOinRV = 64422953714339) NjttOOinRV = 5691002442448; NjttOOinRV = 33596527895098; NjttOOinRV = 78950983359652;
	if (NjttOOinRV = 7682922569100)NjttOOinRV = 37143393558407; NjttOOinRV = 66991627691021;
	if (NjttOOinRV = 36113198537804)NjttOOinRV = 37143393558407; NjttOOinRV = 66991627691021;
	if (NjttOOinRV = 36113198537804)NjttOOinRV = 37143393558407; NjttOOinRV = 66991627691021;
	if (NjttOOinRV = 36113198537804)NjttOOinRV = 37143393558407; NjttOOinRV = 66991627691021;
	if (NjttOOinRV = 36113198537804)NjttOOinRV = 37143393558407; NjttOOinRV = 66991627691021; NjttOOinRV = 79668003228318;

	float eciOYpyFbh = 76093045823285; eciOYpyFbh = 76095223194544; if (eciOYpyFbh = 8409037492707) eciOYpyFbh = 7930524433236; eciOYpyFbh = 38864612231421; eciOYpyFbh = 22314213886461;
	if (eciOYpyFbh = 28240087930524)eciOYpyFbh = 4927076231144; eciOYpyFbh = 57589152912888;
	if (eciOYpyFbh = 94923504817)eciOYpyFbh = 4927076231144; eciOYpyFbh = 57589152912888;
	if (eciOYpyFbh = 94923504817)eciOYpyFbh = 4927076231144; eciOYpyFbh = 57589152912888;
	if (eciOYpyFbh = 94923504817)eciOYpyFbh = 4927076231144; eciOYpyFbh = 57589152912888;
	if (eciOYpyFbh = 94923504817)eciOYpyFbh = 4927076231144; eciOYpyFbh = 57589152912888; eciOYpyFbh = 13071433699232;

}

void CMisc::OnRenderSpectatorList() // Roshly#7550
{
	if (Settings::Misc::misc_Spectators)
	{
		int specs = 0;
		int modes = 0;
		std::string spect = "";
		std::string mode = "";
		int DrawIndex = 1;
		for (int playerId : GetObservervators(Interfaces::Engine()->GetLocalPlayer()))
		{
			if (playerId == Interfaces::Engine()->GetLocalPlayer())
				continue;
			CBaseEntity * pPlayer = (CBaseEntity *)Interfaces::EntityList()->GetClientEntity(playerId);
			if (!pPlayer)
				continue;
			PlayerInfo Pinfo;
			Interfaces::Engine()->GetPlayerInfo(playerId, &Pinfo);
			if (Pinfo.m_bIsFakePlayer)
				continue;
			if (g_pRender)
			{
				spect += Pinfo.m_szPlayerName;
				spect += "\n";
				specs++;
				if (spect!= "")
				{
					Color PlayerObsColor;
					// [junk_disable /] 
					switch (pPlayer->GetObserverMode())
					{
					case ObserverMode_t::OBS_MODE_IN_EYE:
						mode += ("Perspective");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_CHASE:
						mode += ("3rd Person");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_ROAMING:
						mode += ("Free look");
						PlayerObsColor = Color::Red();
						break;
					case ObserverMode_t::OBS_MODE_DEATHCAM:
						mode += ("Deathcam");
						PlayerObsColor = Color::Yellow();
						break;
					case ObserverMode_t::OBS_MODE_FREEZECAM:
						mode += ("Freezecam");
						PlayerObsColor = Color::LimeGreen();
						break;
					case ObserverMode_t::OBS_MODE_FIXED:
						mode += ("Fixed");
						PlayerObsColor = Color::Orange();
						break;
					default:
						break;
					}
					mode += "\n";
					modes++;
				}
			}
		}
		if (ImGui::Begin("Spectator List", &Settings::Misc::misc_Spectators, ImVec2(200, 100), 0.9f, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders))
		{
			if (specs> 0) spect += "\n";
			if (modes> 0) mode += "\n";
			ImVec2 size = ImGui::CalcTextSize(spect.c_str());
			ImGui::Columns(2);
			ImGui::Text("Name");
			ImGui::NextColumn();
			ImGui::Text("Mode");
			ImGui::NextColumn();
			ImGui::Separator();
			ImGui::Text(spect.c_str());
			ImGui::NextColumn();
			ImGui::Text(mode.c_str());
			ImGui::Columns(1);
			DrawIndex++;
		}
		ImGui::End();
	}
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class mvzsusb {
public:
	bool mkyqphttqfxbq;
	int eosifoawarkdsvv;
	bool tgrrvwd;
	mvzsusb();
	bool hfcdzjfchiekpptmv(double rcoydgilnv, string hmglnuyjzyfsta);
	void cpldavprlqkaifi(int gzmcos, double tgccnbqqp);
	string rmpwgeblfwocdfrvidj(bool czhjqantkh);
	string fnaoarumxftjjgsc(double jstrwtayh, string uosigvyvzz);

protected:
	bool yaugyoufhjvhhs;
	int eljaczrsoufr;
	double nbcmrqr;
	int kvzodndwkiqj;

	void mnjfkkvckehcoirlbzzjvcniy(string vnvow, bool ogqugvdfupydkzu, string lqbasr, int htoay, string nzcdonfycz);
	void wxsfwoifztv(double flfqghudtleom, double tkeiq, bool yznnjx, double wlhhp, int vkokjue, double pufqoozukssixeo);
	int qvqpyswnmcsjuhegvqmk(double wmkakigm, int klidjteymtmitbf);
	string tbwkllwuxzmpg(string cakfcxes);
	double empnrmcchngxsxddxfpf(bool wermqxl, string dfpebkuvs, bool huzrtyr);
	bool ejyuqlpcrcvpcumgj(string oewhh, bool kwljbuecf, bool xvyvlfspy);
	bool qdzqpewrgddpkcc(string iybfzxwjimxfpgm);
	void jqltxnhypkrznodyxoxeistvh(bool vfldpceyhxeb, bool ukzvk, bool isvhvp, bool ajnmltk, double rrphl, double ncitlgy, bool sfuyquij, int gdvkkdo, string uaslglxzqmtbpz);

private:
	string rlimkkijaqy;

	string yyxsfubtoendrgoaoxaumnp(double ncxlhqspueqjnmd, int bkjlt, double cgynyeujkm, int jxrez);
	string khxojvbuofjbpzfd(string jydewdoil);
	string loygqfjtbtnwvwdfgr(string cynoibopp);
	double zjapqtsdywfztkaof(string yjzqjgoizm, string xgbzcy, double mvrxxqdraajtfun);
	double thwcgtmbpnyggohxla(int ggqmobd, bool tloihbduoe, string uymptmeuvmrtoi);
	string rqkzdntcrvaxxlqd(int nfksufhbgnwdoh);
	double ynklpagfzfdhgxzrsdgmtxckd();

};


string mvzsusb::yyxsfubtoendrgoaoxaumnp(double ncxlhqspueqjnmd, int bkjlt, double cgynyeujkm, int jxrez) {
	bool irldyhynz = false;
	int ggzpwh = 2710;
	string kfjuxbqpmiaqw = "aieresntrcwuuhrubpufajswgvstburdccejakdpeziiodfeccatdhqipceeu";
	bool xopmbuqjvteicyj = false;
	string myuqhpxugix = "qgghvqwqnxpczxtfnjkdzfhjoqulxntmmacuglqrgxkhnmzbfq";
	string mhdwvfnsillwc = "exawkntyunnlphnzk";
	int zirqspu = 4754;
	double kwwfcdqatjk = 18041;
	bool vsxvqllghi = true;
	int uloqal = 2430;
	if (false != false) {
		int lvivqs;
		for (lvivqs = 4; lvivqs > 0; lvivqs--) {
			continue;
		}
	}
	if (false == false) {
		int ojsjuzdx;
		for (ojsjuzdx = 59; ojsjuzdx > 0; ojsjuzdx--) {
			continue;
		}
	}
	return string("upjbj");
}

string mvzsusb::khxojvbuofjbpzfd(string jydewdoil) {
	bool hacowmpkrneoijd = true;
	int kywlkazcbdttv = 3097;
	bool lljkkvcfd = true;
	string pvecsbbtef = "ytadslnjbuvzxtzjwiyjclbrmhefbfycolbkifzhxewibdvzgb";
	double hrjmdgwx = 33768;
	double uqihuucp = 6079;
	bool brtayjfmcktadv = false;
	if (3097 != 3097) {
		int tk;
		for (tk = 7; tk > 0; tk--) {
			continue;
		}
	}
	if (33768 != 33768) {
		int jabf;
		for (jabf = 29; jabf > 0; jabf--) {
			continue;
		}
	}
	if (33768 != 33768) {
		int hkrsryiar;
		for (hkrsryiar = 19; hkrsryiar > 0; hkrsryiar--) {
			continue;
		}
	}
	if (true != true) {
		int phwecnyzxy;
		for (phwecnyzxy = 83; phwecnyzxy > 0; phwecnyzxy--) {
			continue;
		}
	}
	if (3097 != 3097) {
		int nmq;
		for (nmq = 22; nmq > 0; nmq--) {
			continue;
		}
	}
	return string("exu");
}

string mvzsusb::loygqfjtbtnwvwdfgr(string cynoibopp) {
	int icbaf = 1528;
	string bfjvsryuiay = "tvorendmmxdpjhoapabvkijzzryovylqohdxysalkixbyyhmcituztgkolmpoxmnprwp";
	bool deospduuewmqde = true;
	bool hqqntmfe = true;
	string adrvbdmjnh = "woreecmjkxrzbazupqfzfkwxjqrlykytckweolvuetsvbmjwrzmzgujeumjdfmxjdjpqimofaihuyormwaauxghvr";
	string osxvxdn = "ha";
	double pbgtk = 12526;
	if (true == true) {
		int ubw;
		for (ubw = 17; ubw > 0; ubw--) {
			continue;
		}
	}
	if (string("ha") != string("ha")) {
		int unixdk;
		for (unixdk = 5; unixdk > 0; unixdk--) {
			continue;
		}
	}
	if (string("tvorendmmxdpjhoapabvkijzzryovylqohdxysalkixbyyhmcituztgkolmpoxmnprwp") != string("tvorendmmxdpjhoapabvkijzzryovylqohdxysalkixbyyhmcituztgkolmpoxmnprwp")) {
		int xa;
		for (xa = 90; xa > 0; xa--) {
			continue;
		}
	}
	if (1528 != 1528) {
		int hlulnk;
		for (hlulnk = 9; hlulnk > 0; hlulnk--) {
			continue;
		}
	}
	return string("zkocyctp");
}

double mvzsusb::zjapqtsdywfztkaof(string yjzqjgoizm, string xgbzcy, double mvrxxqdraajtfun) {
	string bqmpjfv = "o";
	string xxxvpf = "luqobfiwyoigjocvhafgroaaoacbeepfzkvdovvzfqorwfzhmgtkjjhsixxusr";
	string iardkzfb = "vtyzrlpbfzjchkeimkskmbtzwakjfpjptchnofklyxwrudcqijldiwhkkvzyvvcqbvztpvzad";
	double ysvqq = 33002;
	bool cnjqkypdb = true;
	int gtljolfnpd = 2440;
	bool bncmchucjbobiz = true;
	string qowrqoleijurox = "vnlgujduohcypwxmgvvxrirfgfjkbwwqhdsm";
	if (string("luqobfiwyoigjocvhafgroaaoacbeepfzkvdovvzfqorwfzhmgtkjjhsixxusr") == string("luqobfiwyoigjocvhafgroaaoacbeepfzkvdovvzfqorwfzhmgtkjjhsixxusr")) {
		int wzjvicmad;
		for (wzjvicmad = 24; wzjvicmad > 0; wzjvicmad--) {
			continue;
		}
	}
	if (string("luqobfiwyoigjocvhafgroaaoacbeepfzkvdovvzfqorwfzhmgtkjjhsixxusr") == string("luqobfiwyoigjocvhafgroaaoacbeepfzkvdovvzfqorwfzhmgtkjjhsixxusr")) {
		int dpbo;
		for (dpbo = 85; dpbo > 0; dpbo--) {
			continue;
		}
	}
	if (2440 != 2440) {
		int mdmgroi;
		for (mdmgroi = 42; mdmgroi > 0; mdmgroi--) {
			continue;
		}
	}
	if (string("vtyzrlpbfzjchkeimkskmbtzwakjfpjptchnofklyxwrudcqijldiwhkkvzyvvcqbvztpvzad") == string("vtyzrlpbfzjchkeimkskmbtzwakjfpjptchnofklyxwrudcqijldiwhkkvzyvvcqbvztpvzad")) {
		int xqdclh;
		for (xqdclh = 44; xqdclh > 0; xqdclh--) {
			continue;
		}
	}
	if (string("luqobfiwyoigjocvhafgroaaoacbeepfzkvdovvzfqorwfzhmgtkjjhsixxusr") == string("luqobfiwyoigjocvhafgroaaoacbeepfzkvdovvzfqorwfzhmgtkjjhsixxusr")) {
		int rwtqchfzm;
		for (rwtqchfzm = 4; rwtqchfzm > 0; rwtqchfzm--) {
			continue;
		}
	}
	return 81863;
}

double mvzsusb::thwcgtmbpnyggohxla(int ggqmobd, bool tloihbduoe, string uymptmeuvmrtoi) {
	double yeslivzybz = 26472;
	double euaxgygjt = 44428;
	int apdig = 2555;
	string ejyekksmincvvv = "erfvyhreeqpgmkiue";
	return 16262;
}

string mvzsusb::rqkzdntcrvaxxlqd(int nfksufhbgnwdoh) {
	string ksfhdbiofepfb = "arjmcmhbjbvhoekbmzdtmlrvzorykfwrwkcvccvpwrqjusesskyoybbmubxbxznyboomidv";
	double fqxfjrkvbwluooq = 15402;
	int etcnybgoqvhhz = 1594;
	int xsbseejx = 1597;
	bool vqqznddamvdcw = true;
	double ibafwqsfecn = 43611;
	string knavlcft = "hrxwhdpmdtnevakmporhdigxzoydkoqmsnbjlpwvoskszgvabcqiuobsnaflsyldqruxfmjxlvfqjtfp";
	if (true == true) {
		int ymacryyon;
		for (ymacryyon = 2; ymacryyon > 0; ymacryyon--) {
			continue;
		}
	}
	if (1597 != 1597) {
		int apimukgwa;
		for (apimukgwa = 62; apimukgwa > 0; apimukgwa--) {
			continue;
		}
	}
	if (1597 == 1597) {
		int gloyzgd;
		for (gloyzgd = 45; gloyzgd > 0; gloyzgd--) {
			continue;
		}
	}
	if (1594 != 1594) {
		int xproxexoq;
		for (xproxexoq = 89; xproxexoq > 0; xproxexoq--) {
			continue;
		}
	}
	return string("fnatjnsybpvfgqxcmekr");
}

double mvzsusb::ynklpagfzfdhgxzrsdgmtxckd() {
	string gzxobxdu = "aobolnvdjsgmxdk";
	double fyifgunnjiyrmej = 9147;
	double sfppgoche = 43351;
	string abjxmchj = "zjxiqgcuvzfqvwewynsbsmoyxgdokhyqpdfizwrrnvuq";
	bool wusdpijmyk = false;
	int cytmjadwrnkj = 1823;
	int qqyeihsd = 1504;
	int sjgkrvjnqmxiyn = 523;
	int kvpgcroyhcigsjd = 1525;
	int idkkncgziv = 2270;
	if (1823 != 1823) {
		int egicgwvdsw;
		for (egicgwvdsw = 9; egicgwvdsw > 0; egicgwvdsw--) {
			continue;
		}
	}
	return 7645;
}

void mvzsusb::mnjfkkvckehcoirlbzzjvcniy(string vnvow, bool ogqugvdfupydkzu, string lqbasr, int htoay, string nzcdonfycz) {
	bool jydwxpswbbdh = false;
	int lztfder = 5999;
	double mzaxmdju = 7801;
	double btgefaghpcaba = 6454;
	bool rcvqktrbcmd = false;
	double yvutbzgppr = 40133;
	bool bjrpoakxsdux = false;
	string fufnoxlbll = "qlvhwobitojbmudsvknhqwyoywjutjplkxmqzvifuojdbbiijoacsvoryghroopwjwcdppwnzfqpaedywtptgouaatczq";
	bool blopwtazx = true;
	int njmrrijve = 5984;
	if (40133 != 40133) {
		int rotsjtmia;
		for (rotsjtmia = 14; rotsjtmia > 0; rotsjtmia--) {
			continue;
		}
	}
	if (false != false) {
		int igez;
		for (igez = 51; igez > 0; igez--) {
			continue;
		}
	}

}

void mvzsusb::wxsfwoifztv(double flfqghudtleom, double tkeiq, bool yznnjx, double wlhhp, int vkokjue, double pufqoozukssixeo) {
	int jcjufk = 991;
	int kmlkhrggs = 1546;
	if (991 != 991) {
		int ign;
		for (ign = 23; ign > 0; ign--) {
			continue;
		}
	}
	if (1546 != 1546) {
		int kjpsq;
		for (kjpsq = 56; kjpsq > 0; kjpsq--) {
			continue;
		}
	}
	if (1546 != 1546) {
		int zc;
		for (zc = 10; zc > 0; zc--) {
			continue;
		}
	}
	if (1546 != 1546) {
		int hupfuooowp;
		for (hupfuooowp = 59; hupfuooowp > 0; hupfuooowp--) {
			continue;
		}
	}
	if (991 != 991) {
		int jjjnkoslt;
		for (jjjnkoslt = 59; jjjnkoslt > 0; jjjnkoslt--) {
			continue;
		}
	}

}

int mvzsusb::qvqpyswnmcsjuhegvqmk(double wmkakigm, int klidjteymtmitbf) {
	string ubzzr = "kmklvupqk";
	string tztkmpl = "edmawmlguxhtefmdlfvd";
	int efyrsajmujczrej = 887;
	double jsmazdxen = 23102;
	double fpqhkdsvec = 25477;
	string miudjobsl = "kdzkkvqjjavxxbblugojpotemjqnpxdvvmdtvvsal";
	string ltddsmg = "rudfbdeyfqvmlcsezzjwyrikzjsdqplfuzvikibmmeqvnivujybigryfdqvhnbkytgktxcnfcjbfqwq";
	if (887 == 887) {
		int ncz;
		for (ncz = 94; ncz > 0; ncz--) {
			continue;
		}
	}
	if (string("kmklvupqk") != string("kmklvupqk")) {
		int mlh;
		for (mlh = 38; mlh > 0; mlh--) {
			continue;
		}
	}
	if (string("kmklvupqk") != string("kmklvupqk")) {
		int asjya;
		for (asjya = 10; asjya > 0; asjya--) {
			continue;
		}
	}
	return 91975;
}

string mvzsusb::tbwkllwuxzmpg(string cakfcxes) {
	bool gxgoqndldc = false;
	double elzdqshra = 28114;
	int cumdcoazpfgqpp = 1225;
	string utzjj = "nswbxogvcgidfclsretiadtpwfbwtpnafsbedfhbmgmwqnztljkcymtwjkvkegmcpwfhdswzaluwrhtkuwidypnn";
	double hmyeuuinhpy = 71258;
	string nxdgfdb = "pykdmwtqzqiaiufgrbzrszyciztpm";
	if (false != false) {
		int oufwsgiucu;
		for (oufwsgiucu = 57; oufwsgiucu > 0; oufwsgiucu--) {
			continue;
		}
	}
	if (1225 == 1225) {
		int isbod;
		for (isbod = 85; isbod > 0; isbod--) {
			continue;
		}
	}
	return string("g");
}

double mvzsusb::empnrmcchngxsxddxfpf(bool wermqxl, string dfpebkuvs, bool huzrtyr) {
	double bvfbpil = 46735;
	string mmoce = "ovwxjfupjvbrqfyzjw";
	string zwidnyzajdwbw = "xbjejaodpcslxtxrqwtsacgprrxypxkylrtcpbjidpffxmmpbngypbdcssuutmoclyocwtwjzcp";
	double trkmm = 43959;
	if (string("ovwxjfupjvbrqfyzjw") != string("ovwxjfupjvbrqfyzjw")) {
		int rkxnsh;
		for (rkxnsh = 7; rkxnsh > 0; rkxnsh--) {
			continue;
		}
	}
	return 41862;
}

bool mvzsusb::ejyuqlpcrcvpcumgj(string oewhh, bool kwljbuecf, bool xvyvlfspy) {
	bool lgafrhclhvzukm = true;
	int dfvyhe = 323;
	if (true != true) {
		int vezpxrqh;
		for (vezpxrqh = 73; vezpxrqh > 0; vezpxrqh--) {
			continue;
		}
	}
	if (true == true) {
		int ckxha;
		for (ckxha = 4; ckxha > 0; ckxha--) {
			continue;
		}
	}
	if (true == true) {
		int kqz;
		for (kqz = 40; kqz > 0; kqz--) {
			continue;
		}
	}
	if (true == true) {
		int xcu;
		for (xcu = 73; xcu > 0; xcu--) {
			continue;
		}
	}
	if (true == true) {
		int seywffub;
		for (seywffub = 93; seywffub > 0; seywffub--) {
			continue;
		}
	}
	return false;
}

bool mvzsusb::qdzqpewrgddpkcc(string iybfzxwjimxfpgm) {
	string firxpbegcuzowjq = "clwlkvqnukmdhrnypjuutcvoczkfdcttclrnfysxzvxatizreebnafgqdousttocitpatfbazjzqdynvceimxpinykcrkxurfnw";
	double siskvzmfuagffd = 19940;
	string syyivsi = "kdavmsyuahqjimstabgkpecjifmvadhtuudgkcdyvuzipgvetruiupogffoeip";
	string gwgejy = "ihqcuvwprfupljennzrkmnakspgmfnsxvssifskbahpegouiseaqyljaialacaenajwrhmqk";
	bool qkbqergayafq = false;
	string bgrqnsq = "wcmypjpqgychauqauuiisvpuenkceezpspajglamwipdnidfbwvrnadntvemotwqhewnj";
	bool jziwbcrgfcpfm = true;
	double waihbhpsmcbklo = 6243;
	int jlrewxvoni = 5783;
	int fyxncb = 3518;
	return true;
}

void mvzsusb::jqltxnhypkrznodyxoxeistvh(bool vfldpceyhxeb, bool ukzvk, bool isvhvp, bool ajnmltk, double rrphl, double ncitlgy, bool sfuyquij, int gdvkkdo, string uaslglxzqmtbpz) {
	int ljczxik = 2227;
	int npprscobghurohc = 5604;

}

bool mvzsusb::hfcdzjfchiekpptmv(double rcoydgilnv, string hmglnuyjzyfsta) {
	int pudiksmcwgkw = 2577;
	int tillvlwprl = 1526;
	string zjnzh = "wjznwqzjbujwicryykvllrjtargtcychqpjbabufklcaefstqvcunzfmmiryliyftzmfvpissxtupadnimthrks";
	int saglsnlrotgdx = 1313;
	int vparsueqwyid = 1877;
	if (1526 == 1526) {
		int dm;
		for (dm = 54; dm > 0; dm--) {
			continue;
		}
	}
	return true;
}

void mvzsusb::cpldavprlqkaifi(int gzmcos, double tgccnbqqp) {
	bool mfmst = false;
	double jkdmffezgzc = 48862;
	string kgdnvknzf = "ynwhibkvwxqzcutxksxavyzragcxnhnigzmqeufvhgvyolhpgoehrvaouojpbqawtcuzlkazikloehkqefcvsppyfcxwbglxosz";
	bool rhkorgzcid = false;
	if (string("ynwhibkvwxqzcutxksxavyzragcxnhnigzmqeufvhgvyolhpgoehrvaouojpbqawtcuzlkazikloehkqefcvsppyfcxwbglxosz") != string("ynwhibkvwxqzcutxksxavyzragcxnhnigzmqeufvhgvyolhpgoehrvaouojpbqawtcuzlkazikloehkqefcvsppyfcxwbglxosz")) {
		int na;
		for (na = 74; na > 0; na--) {
			continue;
		}
	}
	if (string("ynwhibkvwxqzcutxksxavyzragcxnhnigzmqeufvhgvyolhpgoehrvaouojpbqawtcuzlkazikloehkqefcvsppyfcxwbglxosz") != string("ynwhibkvwxqzcutxksxavyzragcxnhnigzmqeufvhgvyolhpgoehrvaouojpbqawtcuzlkazikloehkqefcvsppyfcxwbglxosz")) {
		int vofse;
		for (vofse = 23; vofse > 0; vofse--) {
			continue;
		}
	}
	if (string("ynwhibkvwxqzcutxksxavyzragcxnhnigzmqeufvhgvyolhpgoehrvaouojpbqawtcuzlkazikloehkqefcvsppyfcxwbglxosz") != string("ynwhibkvwxqzcutxksxavyzragcxnhnigzmqeufvhgvyolhpgoehrvaouojpbqawtcuzlkazikloehkqefcvsppyfcxwbglxosz")) {
		int eo;
		for (eo = 31; eo > 0; eo--) {
			continue;
		}
	}
	if (false != false) {
		int fcrdfqlwu;
		for (fcrdfqlwu = 79; fcrdfqlwu > 0; fcrdfqlwu--) {
			continue;
		}
	}

}

string mvzsusb::rmpwgeblfwocdfrvidj(bool czhjqantkh) {
	bool lbqcvfldlpc = true;
	if (true != true) {
		int mjculnpt;
		for (mjculnpt = 10; mjculnpt > 0; mjculnpt--) {
			continue;
		}
	}
	if (true == true) {
		int gujaulygmu;
		for (gujaulygmu = 26; gujaulygmu > 0; gujaulygmu--) {
			continue;
		}
	}
	if (true == true) {
		int vbsxumye;
		for (vbsxumye = 17; vbsxumye > 0; vbsxumye--) {
			continue;
		}
	}
	if (true != true) {
		int usvmwr;
		for (usvmwr = 36; usvmwr > 0; usvmwr--) {
			continue;
		}
	}
	return string("vkkgrresc");
}

string mvzsusb::fnaoarumxftjjgsc(double jstrwtayh, string uosigvyvzz) {
	return string("fyjwixmd");
}

mvzsusb::mvzsusb() {
	this->hfcdzjfchiekpptmv(12722, string("cjnxjnzrulrkfvmcbmpgzyggrfovpcrqgtoehzechng"));
	this->cpldavprlqkaifi(320, 3680);
	this->rmpwgeblfwocdfrvidj(false);
	this->fnaoarumxftjjgsc(13079, string("ckprquynzogjwjbubdvouvwmdxeojsozskcelwokfsblkyvbwcnlbhdvnpbinnfyamjwqdmjozptazleizbvpfs"));
	this->mnjfkkvckehcoirlbzzjvcniy(string("zvilwingzcccsmdqewteiaopsgwqfzovfzatbldmvonxxaccotcteonoyubqvawyyoqgmdwxaafrgbmt"), true, string("yalb"), 3036, string("grjmbncnuvxrrnmswpbpauvkuvfssprqcogwarkwuqpgglyxrmwqgyztacgmkjyp"));
	this->wxsfwoifztv(7463, 2063, false, 45302, 493, 1302);
	this->qvqpyswnmcsjuhegvqmk(50199, 221);
	this->tbwkllwuxzmpg(string("iinzifvxpftcxqubaozbmgwgfltmsqgezsgoubxagzqegdxstnrsld"));
	this->empnrmcchngxsxddxfpf(true, string("azagljabmjtux"), false);
	this->ejyuqlpcrcvpcumgj(string("tjmqwnzvyjooznwacijbyddskxcjzdkvnlahctpmwagdpyefqakaawimtlzye"), true, false);
	this->qdzqpewrgddpkcc(string("xshbakjudj"));
	this->jqltxnhypkrznodyxoxeistvh(false, false, true, true, 17071, 5285, true, 4434, string("dckgynztgjgmepjxtpgubsujmdtjluzvnnebvt"));
	this->yyxsfubtoendrgoaoxaumnp(2538, 2441, 25446, 7385);
	this->khxojvbuofjbpzfd(string("vnxmgmhjoglhlufehixlonfhdasmvmbmureenmcjyqmju"));
	this->loygqfjtbtnwvwdfgr(string("ddyogllozapizqqtllgqafeeavodrlchomgtxanhnwmueiinpmsdehpbbxklxmnnkmqtgqtfyptviomqpknv"));
	this->zjapqtsdywfztkaof(string("zhrzfuzxmydqcimjytouwijbsvpgnbelpuwcawzrnjvcczjmyyryfbcfhzhxsmzlkdhtbzwyaxvahqrpcepacwnqtzabcfqk"), string("ubbamlpajiewsmlowzkpjcdnpumpdegnlystccevdjqybmnibcxfhlhpnreiihnlywbepqrsgi"), 75331);
	this->thwcgtmbpnyggohxla(1746, true, string("wtlmxtcyenayokpggpbzofkntqlabqdodvqsnwshqewatbajpyqbavmtiapjcrndvukntojvymt"));
	this->rqkzdntcrvaxxlqd(949);
	this->ynklpagfzfdhgxzrsdgmtxckd();
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class cisaufs {
public:
	bool svniitec;
	double nzoreeowki;
	bool ngkyedusizdaamh;
	cisaufs();
	bool lgfvjwtiilevfnyoqcww(bool krfokj, bool dcjrovvauhjgd, bool ynaulprc, bool ljyotaitbsuy, int hgkpeaj, double mqacmhjhceoktg, bool rgvzfzelislfsh);
	string nmilcmdartamgtarghob(int odtncneuhdq, bool uferchv, double kndaabl, string aqcftqpzhopbde, double ndaifn);
	bool bitoooozlotbdiaqliltja(bool qqpxodylm, int ujomhscvtyorel, string rvjuclroryrc, string cvysh);
	string brspmolerid(int rxstaopoix, double hbzjf);

protected:
	string ezarilzvy;

	int ysteiczvotjfl(bool xwoexb, double qdewfjxwdka, int biizn);
	int scgzrjmknbxhkhkpretgr(double ospsqxxo, double nynbn);
	bool uuksliesdqgzkskay(bool tcrwdo, bool jzzotphj, double kppvqxmtt, int iwaubjq, int rcfbeyxbajzt, bool fzeutorta, int wwpbwecf, int rmffgpw, bool ljiszskw, string cpbhkp);
	bool ocxvhsifnrpgvrxnjcnru(int ddroqgchdkwmda, string hvgtxvzmprrnxi, double grbqd, int kzlmojglr, string xwwoviip);
	int opdhxfmeipxxhle();
	double yhogeaphfjct(string qbnid, double ntulswycxy, int omcjwstrfir, bool jqlnth, bool uocyepjzy, double aevap, double rfjwq, string tmavshmgpsodupd);
	double negabirevlzl(string ifmojrsrdiz, int iayok);
	string eikbeyxdpfbfvv(int rknshbk, string lwplslwcvemil, bool apdwlyfgxnpgq, bool ejgtgqlp, double ujwuvpeco, string rfmpcmgamnjn, string bycjijr, string lqritlx, double plxnh, bool ulirynnx);
	string guvmoxbqpqervrrca(int lmlvksyogdszw, bool cvmofmxxfdnpozf, int lyrywclghfkt, bool fczwyltsyro, double vsazfsqsaggsron, bool fwqdbrhcamls, string xnxeiduzuyzjn, bool grmobsz, bool mrvamo);

private:
	string dphdroqfojs;
	double uomwfhfmvs;

	int ybefvnrmxegftbivaicxd(string tijtvxo);
	double orwnrbokstcg();
	string bdeatpwwmbycqfzu(bool htkrgcitlfndfxp, bool rtistxdscqca, bool yyoelacncx, int flfqvgigeyu, double zcscjftwykp, double byyajccfexg, string ydtnbbeavwmfst, string omufddk);
	bool thylmbzupzelxbcjpbtgki(double qvmzql, double tccswprsv, int rihckbfdauncpgh, int utspbvcktfq, double amdlxflgwprthf);
	bool zyrqpddgpwusf(double unhmieuwtic, int rxzhamdbeukr, int cdsgudmnpkwls, double onkdyr, bool vlfzxnlozqpeit, int zffatcisguldbci, string ywzvkfzqzokyjto);
	void alisiuadswryhulk();
	double receaonvsnfgjppotaqdwhljx(string wepqhzdv, bool kfflskpqwxzgtz, bool tsudw, string fmqxwaur, double zxyeox, double eervuhzkbrryy, bool gybrdybgcw);
	string qzeeolnsoyxudcdrnyraqly(bool smtjpmuelklqr, int kftwwiupickzmc, int uzqnxltsvkgpbj, int dalszitylwrne, double qlezblkbu, double eerplzyudrthtts, double zorhhcpjlpdirjc, double szqyw);
	bool moudvcjcchp(double fnvulq);
	int ujomwtfhplperc(bool itzcnixhkobagqe);

};


int cisaufs::ybefvnrmxegftbivaicxd(string tijtvxo) {
	return 9697;
}

double cisaufs::orwnrbokstcg() {
	double yvgwlzg = 33607;
	bool cjixalyutkqsmql = false;
	if (false != false) {
		int fbybr;
		for (fbybr = 37; fbybr > 0; fbybr--) {
			continue;
		}
	}
	if (33607 == 33607) {
		int jdfu;
		for (jdfu = 7; jdfu > 0; jdfu--) {
			continue;
		}
	}
	return 91942;
}

string cisaufs::bdeatpwwmbycqfzu(bool htkrgcitlfndfxp, bool rtistxdscqca, bool yyoelacncx, int flfqvgigeyu, double zcscjftwykp, double byyajccfexg, string ydtnbbeavwmfst, string omufddk) {
	bool nkcvqq = false;
	double clcnewkreggckmp = 7658;
	string csohb = "wvbihheyetpqsdvcckhluurcifkglaafvsjceyjisonalcxjsmfmblovikejvccxrirxbbakrn";
	int mbojacyyd = 2889;
	string zzyhjklldpygpdj = "kvcpvz";
	bool jwzcxrzahlviuee = true;
	bool vtkkxdlgxmhp = false;
	return string("npqmgvrnfxvatul");
}

bool cisaufs::thylmbzupzelxbcjpbtgki(double qvmzql, double tccswprsv, int rihckbfdauncpgh, int utspbvcktfq, double amdlxflgwprthf) {
	double tefmltiizmjo = 11846;
	double audqxqev = 47779;
	int mhailwsnov = 983;
	string ndyjit = "uahimlwsbxogvhohkmmlixzcxlxxmwskroyppjppzprrinokbpnonpvoceikhbnbucuxuws";
	bool ejrswvzcqjdw = true;
	double vpjgtgwy = 35069;
	string gprkrioamw = "juocazwyyqritgrcibkdnjotagaucbkharnswckudyzytuatnzyzxhsrdrkyhpnxzzwurasak";
	if (true == true) {
		int ubzetgvihn;
		for (ubzetgvihn = 78; ubzetgvihn > 0; ubzetgvihn--) {
			continue;
		}
	}
	if (string("juocazwyyqritgrcibkdnjotagaucbkharnswckudyzytuatnzyzxhsrdrkyhpnxzzwurasak") == string("juocazwyyqritgrcibkdnjotagaucbkharnswckudyzytuatnzyzxhsrdrkyhpnxzzwurasak")) {
		int obpkudm;
		for (obpkudm = 53; obpkudm > 0; obpkudm--) {
			continue;
		}
	}
	if (11846 == 11846) {
		int ekihb;
		for (ekihb = 3; ekihb > 0; ekihb--) {
			continue;
		}
	}
	if (11846 == 11846) {
		int iljyeaysgr;
		for (iljyeaysgr = 38; iljyeaysgr > 0; iljyeaysgr--) {
			continue;
		}
	}
	if (47779 != 47779) {
		int tlvatspt;
		for (tlvatspt = 55; tlvatspt > 0; tlvatspt--) {
			continue;
		}
	}
	return true;
}

bool cisaufs::zyrqpddgpwusf(double unhmieuwtic, int rxzhamdbeukr, int cdsgudmnpkwls, double onkdyr, bool vlfzxnlozqpeit, int zffatcisguldbci, string ywzvkfzqzokyjto) {
	double gnhaaopkmeqiwfv = 23317;
	bool lgbjqefswkk = false;
	double ujkzzyf = 19072;
	string gmlbwy = "ehhpcvwtgvzahsxrcgzldnkazfjxpxezsmrgdstbfcgaltmdgukdhnrsdawkimiosqvuevayzgebyhdfhlnjmwdv";
	bool nmhpgema = true;
	int petmmyqtc = 2661;
	string lptyn = "eqlxnftjjbfkfsuhjeiktoukvwqwkhhdymzmzbtuiikrgfgigp";
	int mytlpvyqkylpg = 1581;
	bool nkvzuiogsmnqkvs = false;
	if (string("ehhpcvwtgvzahsxrcgzldnkazfjxpxezsmrgdstbfcgaltmdgukdhnrsdawkimiosqvuevayzgebyhdfhlnjmwdv") != string("ehhpcvwtgvzahsxrcgzldnkazfjxpxezsmrgdstbfcgaltmdgukdhnrsdawkimiosqvuevayzgebyhdfhlnjmwdv")) {
		int fi;
		for (fi = 3; fi > 0; fi--) {
			continue;
		}
	}
	if (false != false) {
		int fgmigwut;
		for (fgmigwut = 4; fgmigwut > 0; fgmigwut--) {
			continue;
		}
	}
	return true;
}

void cisaufs::alisiuadswryhulk() {
	bool scjrdupqovppxj = false;
	bool wgbexuoutj = true;
	double lheqgyy = 8309;
	string zypbqkub = "myvsukzqjvduhabztmtsladpcbvneupumlaxhziuhkubonefnmzhhg";
	if (true == true) {
		int takqmpask;
		for (takqmpask = 93; takqmpask > 0; takqmpask--) {
			continue;
		}
	}
	if (8309 != 8309) {
		int zy;
		for (zy = 5; zy > 0; zy--) {
			continue;
		}
	}
	if (string("myvsukzqjvduhabztmtsladpcbvneupumlaxhziuhkubonefnmzhhg") == string("myvsukzqjvduhabztmtsladpcbvneupumlaxhziuhkubonefnmzhhg")) {
		int calhsbatie;
		for (calhsbatie = 32; calhsbatie > 0; calhsbatie--) {
			continue;
		}
	}
	if (true == true) {
		int aznx;
		for (aznx = 49; aznx > 0; aznx--) {
			continue;
		}
	}
	if (string("myvsukzqjvduhabztmtsladpcbvneupumlaxhziuhkubonefnmzhhg") != string("myvsukzqjvduhabztmtsladpcbvneupumlaxhziuhkubonefnmzhhg")) {
		int mr;
		for (mr = 48; mr > 0; mr--) {
			continue;
		}
	}

}

double cisaufs::receaonvsnfgjppotaqdwhljx(string wepqhzdv, bool kfflskpqwxzgtz, bool tsudw, string fmqxwaur, double zxyeox, double eervuhzkbrryy, bool gybrdybgcw) {
	bool koqbndypveq = false;
	int vgttnbmzxdqakvr = 2126;
	string cyotdvet = "xmiqcxsmqddvhyyautmfldvctuakswvswwnaibzzzoeh";
	bool yijyiba = false;
	string pqgroxthbyn = "cngeklptchtc";
	double bzwiodh = 12984;
	int aysjhpotgmmclt = 4215;
	int aswupsgmlq = 959;
	bool irtwsmxnxiq = false;
	int mbyqrcxjbwl = 4164;
	if (4164 == 4164) {
		int gvu;
		for (gvu = 37; gvu > 0; gvu--) {
			continue;
		}
	}
	if (4164 == 4164) {
		int qze;
		for (qze = 45; qze > 0; qze--) {
			continue;
		}
	}
	return 12970;
}

string cisaufs::qzeeolnsoyxudcdrnyraqly(bool smtjpmuelklqr, int kftwwiupickzmc, int uzqnxltsvkgpbj, int dalszitylwrne, double qlezblkbu, double eerplzyudrthtts, double zorhhcpjlpdirjc, double szqyw) {
	return string("hvmgwijluqyntnjpe");
}

bool cisaufs::moudvcjcchp(double fnvulq) {
	double wqimiqmobbdr = 9164;
	double wbfeheichu = 80030;
	int stmjd = 3687;
	double pkhkrdgazf = 5076;
	bool prdqbgxojfneai = true;
	double vhalqku = 69979;
	bool giukmhdhohywfgm = true;
	double zuftqtgpb = 46563;
	double ixfkrnih = 22258;
	if (5076 == 5076) {
		int cxwifa;
		for (cxwifa = 99; cxwifa > 0; cxwifa--) {
			continue;
		}
	}
	if (3687 == 3687) {
		int kjjvcv;
		for (kjjvcv = 61; kjjvcv > 0; kjjvcv--) {
			continue;
		}
	}
	if (22258 == 22258) {
		int jszrzsu;
		for (jszrzsu = 39; jszrzsu > 0; jszrzsu--) {
			continue;
		}
	}
	if (true != true) {
		int geirmzvy;
		for (geirmzvy = 53; geirmzvy > 0; geirmzvy--) {
			continue;
		}
	}
	if (80030 != 80030) {
		int ogzaj;
		for (ogzaj = 89; ogzaj > 0; ogzaj--) {
			continue;
		}
	}
	return false;
}

int cisaufs::ujomwtfhplperc(bool itzcnixhkobagqe) {
	bool jhvdcwdxql = false;
	double ibqaehtp = 39824;
	string fyxzbkzndup = "ovgudsrsvpipksiocwlxypdtzoznylabpvwmggvyjerzwxjlfimxq";
	return 83274;
}

int cisaufs::ysteiczvotjfl(bool xwoexb, double qdewfjxwdka, int biizn) {
	string yacxxsbajkb = "amyvcrtzgqpfxhaxgngqccvtgwxzxobqmlnjztealifqalgmb";
	if (string("amyvcrtzgqpfxhaxgngqccvtgwxzxobqmlnjztealifqalgmb") != string("amyvcrtzgqpfxhaxgngqccvtgwxzxobqmlnjztealifqalgmb")) {
		int jczwnof;
		for (jczwnof = 57; jczwnof > 0; jczwnof--) {
			continue;
		}
	}
	if (string("amyvcrtzgqpfxhaxgngqccvtgwxzxobqmlnjztealifqalgmb") == string("amyvcrtzgqpfxhaxgngqccvtgwxzxobqmlnjztealifqalgmb")) {
		int chlymsty;
		for (chlymsty = 50; chlymsty > 0; chlymsty--) {
			continue;
		}
	}
	if (string("amyvcrtzgqpfxhaxgngqccvtgwxzxobqmlnjztealifqalgmb") == string("amyvcrtzgqpfxhaxgngqccvtgwxzxobqmlnjztealifqalgmb")) {
		int ouhbej;
		for (ouhbej = 68; ouhbej > 0; ouhbej--) {
			continue;
		}
	}
	return 12353;
}

int cisaufs::scgzrjmknbxhkhkpretgr(double ospsqxxo, double nynbn) {
	string psacx = "gkradgbmxaiwqkmykqxxle";
	string ctfmiqqpc = "wumnjpi";
	int ermjdkbkfrpwski = 4487;
	string qqxkzqfxzejjpxr = "riuzuoucjlcuysbtrngn";
	double ajaqgxaziyr = 50631;
	int akdkpnuqwf = 3608;
	string inihgjkb = "ptihqggktdtrmobcjnmfpeyryreqhreqtpxlmklnvkhr";
	int tmdrhu = 95;
	if (string("riuzuoucjlcuysbtrngn") != string("riuzuoucjlcuysbtrngn")) {
		int khgetndn;
		for (khgetndn = 24; khgetndn > 0; khgetndn--) {
			continue;
		}
	}
	if (3608 == 3608) {
		int ixedfmbhyz;
		for (ixedfmbhyz = 1; ixedfmbhyz > 0; ixedfmbhyz--) {
			continue;
		}
	}
	if (string("wumnjpi") == string("wumnjpi")) {
		int qtoawkfno;
		for (qtoawkfno = 16; qtoawkfno > 0; qtoawkfno--) {
			continue;
		}
	}
	if (95 == 95) {
		int wefoeiwlgn;
		for (wefoeiwlgn = 68; wefoeiwlgn > 0; wefoeiwlgn--) {
			continue;
		}
	}
	if (4487 == 4487) {
		int wcd;
		for (wcd = 72; wcd > 0; wcd--) {
			continue;
		}
	}
	return 54298;
}

bool cisaufs::uuksliesdqgzkskay(bool tcrwdo, bool jzzotphj, double kppvqxmtt, int iwaubjq, int rcfbeyxbajzt, bool fzeutorta, int wwpbwecf, int rmffgpw, bool ljiszskw, string cpbhkp) {
	bool slvnq = false;
	string rinxoyqmdlfb = "ktikhsblzfogshvbkmafcbehs";
	bool powrvyjvt = true;
	string ratkfs = "yhgyss";
	double gcvbjbklrsubhmr = 40748;
	bool zstssbdoqh = true;
	string yvdchb = "xsgvkdeebcspcerzugrdllqfawbvebqjyvdeiauiqsdacndgnsopogtaouqjgibqaxieczeuhmvpnkzmufeusqaegqqyn";
	string dfyizpvwuc = "glhhaxjdyqpxopujjqmvhyfmpwmqmwjdhwgtdubrumwjdosjvoapbseybnqgrldjcrtbwrklrfyes";
	if (string("xsgvkdeebcspcerzugrdllqfawbvebqjyvdeiauiqsdacndgnsopogtaouqjgibqaxieczeuhmvpnkzmufeusqaegqqyn") != string("xsgvkdeebcspcerzugrdllqfawbvebqjyvdeiauiqsdacndgnsopogtaouqjgibqaxieczeuhmvpnkzmufeusqaegqqyn")) {
		int mnzpub;
		for (mnzpub = 4; mnzpub > 0; mnzpub--) {
			continue;
		}
	}
	if (string("glhhaxjdyqpxopujjqmvhyfmpwmqmwjdhwgtdubrumwjdosjvoapbseybnqgrldjcrtbwrklrfyes") != string("glhhaxjdyqpxopujjqmvhyfmpwmqmwjdhwgtdubrumwjdosjvoapbseybnqgrldjcrtbwrklrfyes")) {
		int scfutkcl;
		for (scfutkcl = 16; scfutkcl > 0; scfutkcl--) {
			continue;
		}
	}
	if (string("ktikhsblzfogshvbkmafcbehs") == string("ktikhsblzfogshvbkmafcbehs")) {
		int yuoy;
		for (yuoy = 78; yuoy > 0; yuoy--) {
			continue;
		}
	}
	if (true != true) {
		int idw;
		for (idw = 67; idw > 0; idw--) {
			continue;
		}
	}
	return false;
}

bool cisaufs::ocxvhsifnrpgvrxnjcnru(int ddroqgchdkwmda, string hvgtxvzmprrnxi, double grbqd, int kzlmojglr, string xwwoviip) {
	string tlwhfzosqmugc = "qtspybsvsefcdbwpsftxm";
	bool bxhjewx = false;
	string yrfzioxc = "nlppafcovkkhqrmsfofimiidqcnsgjsp";
	string xjxgftgupsx = "ixveegableblycirbhddirqpduyuzbujsmhwzkddgqeweokcukufbhpkdtfvc";
	int ljskubjw = 2229;
	int ptwwtqjndahswx = 4729;
	int scvhwuqyvmbu = 269;
	if (2229 != 2229) {
		int yzgmormah;
		for (yzgmormah = 51; yzgmormah > 0; yzgmormah--) {
			continue;
		}
	}
	if (269 == 269) {
		int wgrkxivlr;
		for (wgrkxivlr = 16; wgrkxivlr > 0; wgrkxivlr--) {
			continue;
		}
	}
	if (string("qtspybsvsefcdbwpsftxm") == string("qtspybsvsefcdbwpsftxm")) {
		int ybevbmp;
		for (ybevbmp = 11; ybevbmp > 0; ybevbmp--) {
			continue;
		}
	}
	if (string("ixveegableblycirbhddirqpduyuzbujsmhwzkddgqeweokcukufbhpkdtfvc") == string("ixveegableblycirbhddirqpduyuzbujsmhwzkddgqeweokcukufbhpkdtfvc")) {
		int szqxddd;
		for (szqxddd = 35; szqxddd > 0; szqxddd--) {
			continue;
		}
	}
	if (2229 == 2229) {
		int qskqkqug;
		for (qskqkqug = 69; qskqkqug > 0; qskqkqug--) {
			continue;
		}
	}
	return true;
}

int cisaufs::opdhxfmeipxxhle() {
	int kwasromwsiphks = 2009;
	int ckobusb = 4180;
	int kegdpvewc = 1262;
	if (1262 != 1262) {
		int vn;
		for (vn = 66; vn > 0; vn--) {
			continue;
		}
	}
	if (1262 == 1262) {
		int akwj;
		for (akwj = 14; akwj > 0; akwj--) {
			continue;
		}
	}
	if (1262 != 1262) {
		int ldm;
		for (ldm = 60; ldm > 0; ldm--) {
			continue;
		}
	}
	if (1262 != 1262) {
		int ixiuxblqlr;
		for (ixiuxblqlr = 2; ixiuxblqlr > 0; ixiuxblqlr--) {
			continue;
		}
	}
	return 25053;
}

double cisaufs::yhogeaphfjct(string qbnid, double ntulswycxy, int omcjwstrfir, bool jqlnth, bool uocyepjzy, double aevap, double rfjwq, string tmavshmgpsodupd) {
	double jbdfxdhmjopkz = 19618;
	int dqscrkb = 945;
	int ojhieelpre = 3869;
	double craih = 35372;
	string rvrtindokhu = "nklnnmcrzsftnofbpkcsjvckpvjsmkdwddwxnhnibysensfvebixthfpatsagohcllzunnfxgnzp";
	bool utcfylqtnca = true;
	return 86446;
}

double cisaufs::negabirevlzl(string ifmojrsrdiz, int iayok) {
	double yailcaiow = 45851;
	string wxnoous = "ilxtbxepejzgzeks";
	string vcuvuwha = "rlpeihwuavxnhfoglda";
	double gmlnsnbdi = 38218;
	string bvtopflwcsikav = "xmamurv";
	double avpwc = 5038;
	double auwpsuxlfnyzc = 9794;
	bool nfmrl = true;
	int ustfd = 2659;
	double srfgtxx = 2791;
	if (38218 != 38218) {
		int pbrb;
		for (pbrb = 88; pbrb > 0; pbrb--) {
			continue;
		}
	}
	if (38218 != 38218) {
		int keuqxfq;
		for (keuqxfq = 0; keuqxfq > 0; keuqxfq--) {
			continue;
		}
	}
	if (5038 != 5038) {
		int acblmawrfk;
		for (acblmawrfk = 81; acblmawrfk > 0; acblmawrfk--) {
			continue;
		}
	}
	return 68985;
}

string cisaufs::eikbeyxdpfbfvv(int rknshbk, string lwplslwcvemil, bool apdwlyfgxnpgq, bool ejgtgqlp, double ujwuvpeco, string rfmpcmgamnjn, string bycjijr, string lqritlx, double plxnh, bool ulirynnx) {
	bool nmxobnprxslgt = false;
	bool lumxxwlsup = false;
	double zxjzntcbeqgdhmp = 32723;
	int fcdgocykystq = 2069;
	bool ratnjttasht = false;
	string pyvcwllhfpschqa = "kpuefasvbwjboqrunsrtyoebktswcwtsovrcfqhqfyawvzzcy";
	if (false == false) {
		int rl;
		for (rl = 49; rl > 0; rl--) {
			continue;
		}
	}
	if (false != false) {
		int pdvuqqygg;
		for (pdvuqqygg = 97; pdvuqqygg > 0; pdvuqqygg--) {
			continue;
		}
	}
	if (false == false) {
		int qmxx;
		for (qmxx = 5; qmxx > 0; qmxx--) {
			continue;
		}
	}
	return string("zt");
}

string cisaufs::guvmoxbqpqervrrca(int lmlvksyogdszw, bool cvmofmxxfdnpozf, int lyrywclghfkt, bool fczwyltsyro, double vsazfsqsaggsron, bool fwqdbrhcamls, string xnxeiduzuyzjn, bool grmobsz, bool mrvamo) {
	return string("ftqinolvgsuh");
}

bool cisaufs::lgfvjwtiilevfnyoqcww(bool krfokj, bool dcjrovvauhjgd, bool ynaulprc, bool ljyotaitbsuy, int hgkpeaj, double mqacmhjhceoktg, bool rgvzfzelislfsh) {
	int zktphbdhy = 143;
	string dutwcljiqrmx = "gxiognybgfmrfxxistcybvdigdrlbhgmjuikrktnibwwxfzkbyz";
	bool bllwoylkuhuvto = true;
	if (143 == 143) {
		int gkvjalu;
		for (gkvjalu = 17; gkvjalu > 0; gkvjalu--) {
			continue;
		}
	}
	if (string("gxiognybgfmrfxxistcybvdigdrlbhgmjuikrktnibwwxfzkbyz") == string("gxiognybgfmrfxxistcybvdigdrlbhgmjuikrktnibwwxfzkbyz")) {
		int ptsfpawn;
		for (ptsfpawn = 49; ptsfpawn > 0; ptsfpawn--) {
			continue;
		}
	}
	return false;
}

string cisaufs::nmilcmdartamgtarghob(int odtncneuhdq, bool uferchv, double kndaabl, string aqcftqpzhopbde, double ndaifn) {
	return string("yiv");
}

bool cisaufs::bitoooozlotbdiaqliltja(bool qqpxodylm, int ujomhscvtyorel, string rvjuclroryrc, string cvysh) {
	string skfwluq = "viqifbvwhwmwohii";
	string ikzgxcoiqu = "lxo";
	double cqcqnbuqscd = 4480;
	string fagbwmufkrnju = "jmxpgshuw";
	bool kvzjmxrph = false;
	double kefsazoyhjic = 53269;
	string yuelldbhpi = "lysssgflgfqbxtqpwemoetembwgpcahryddtlbzdeqqitxsdfriwpvnx";
	int mbzopfqzxp = 3738;
	return false;
}

string cisaufs::brspmolerid(int rxstaopoix, double hbzjf) {
	string jaiukkmaoyj = "gejqnzissmxpiz";
	string wasujekrytiadru = "xycnjcfaeki";
	bool jiyap = true;
	int eusruvitpgvu = 1225;
	if (string("gejqnzissmxpiz") == string("gejqnzissmxpiz")) {
		int qlboumoz;
		for (qlboumoz = 62; qlboumoz > 0; qlboumoz--) {
			continue;
		}
	}
	if (string("xycnjcfaeki") == string("xycnjcfaeki")) {
		int gzypfe;
		for (gzypfe = 86; gzypfe > 0; gzypfe--) {
			continue;
		}
	}
	return string("lidqniqycyktyjqwcmh");
}

cisaufs::cisaufs() {
	this->lgfvjwtiilevfnyoqcww(true, true, false, false, 7374, 8433, true);
	this->nmilcmdartamgtarghob(1207, false, 73665, string("ldnfzlruaikyolfjavmxkldbjbldkncwytsuxfubzjaktimuoyvdzauxlbxjdm"), 4660);
	this->bitoooozlotbdiaqliltja(true, 3699, string("uowxtow"), string("bnlro"));
	this->brspmolerid(2939, 43402);
	this->ysteiczvotjfl(true, 30592, 1712);
	this->scgzrjmknbxhkhkpretgr(1891, 49996);
	this->uuksliesdqgzkskay(false, false, 17940, 207, 1588, false, 5960, 3592, false, string("mnbiulivxgoeejrgtoqzdkjkwxwlcgfgzoxsaiohlidrnwqortraergdkfhkmutrhzzfmpchljeayauabigqppwacm"));
	this->ocxvhsifnrpgvrxnjcnru(1882, string("njydltrpzllektyfxkisprsmryjyxisutnpopoewqbzigeaajgookwdasjugybitbcdmlfdfydngblvge"), 21521, 3540, string("jwscfxlbipdskytasdfwievtmeicralwwihntnhnplfcxtegugprhujzclyrgxvscigaskofcaxxgcgzmycajm"));
	this->opdhxfmeipxxhle();
	this->yhogeaphfjct(string("zeijcodeugmdnltnpolt"), 40227, 2446, false, false, 49060, 9877, string("rfcikdmu"));
	this->negabirevlzl(string("vvmslkruaxi"), 1686);
	this->eikbeyxdpfbfvv(1411, string("bgwhtmlpeylpimfxezfctglldihtljqjzzwruulvicbahanvmyztgxuwlumasuoustvojcuyajpksxjcwypjwtwegnmpqhyt"), false, true, 29767, string("paiv"), string("xjvmeopgfznhyordpiwjtyrcrjhmimcilchf"), string("sashixwpkszqexzkvfqhnatyoxkljfoanulbiykim"), 57638, false);
	this->guvmoxbqpqervrrca(3697, true, 133, true, 37769, true, string("jrwkpcuclkgiamjemgupyyszbvut"), false, true);
	this->ybefvnrmxegftbivaicxd(string("qbsxjwjulvtftuivujnpqpwbhgfxpnajn"));
	this->orwnrbokstcg();
	this->bdeatpwwmbycqfzu(false, false, false, 511, 1734, 665, string("dpohdybghxjkqxiiyhhhzsduvrjowsmtvygnlhzwvsuxvscjfdpvaeeqdnloqsyfffxqmtokywjsoswirbsdcgcupyqppwyljq"), string("uyfzdogaaqbkunlkwllslfihouyekwytrsqibhhsaqnzgnfxrvwyyuoherowu"));
	this->thylmbzupzelxbcjpbtgki(32630, 31993, 5457, 366, 51919);
	this->zyrqpddgpwusf(30749, 3292, 390, 6578, true, 3010, string("kevfjqxedhzpqbemzvctsykhlbvaatterghhuexcsjmprrhmdjgiskzhkvwvkkacy"));
	this->alisiuadswryhulk();
	this->receaonvsnfgjppotaqdwhljx(string("g"), true, true, string("wjybfgulkhhzztxbjrgiccobprdzhjbdgdnjthvtvydfrbcbbssgoztbsbgigvvhijc"), 2809, 19681, true);
	this->qzeeolnsoyxudcdrnyraqly(false, 2425, 9057, 7726, 97765, 8454, 29956, 14475);
	this->moudvcjcchp(59160);
	this->ujomwtfhplperc(true);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class bjvknqy {
public:
	double snxkndnlwf;
	bool nlarkoocy;
	bool fzpgbcatecz;
	double dcnsydgqy;
	bjvknqy();
	bool jzhdxhbdrfzzrmmdivzada(int omrfzzthfkpag, string mwyrjocaonhch, bool iuyauopqanf, string ohmqqpaxqqyn, string qtyvbxcgz, string ynfvysdqwhyxcn, string ashvmepwrdive, string txdpeia, bool zdnkkdcwafumi, bool lmodnlhiomaxi);
	int qjacewvuvbxbntivgwdvbsduy(double gfqmxk, double nazykqevspdddz, double cqhzwsjd, bool tulncuzlhv, string papku, string cgakqbveuirppii, double kcbvezyxsaumao, int azlmwpzfmojffff, string vpjhaatgs);
	void nacqvpwvebgj();
	string plkynmfmnmwhorsqshgksn(int hknmn, double fzkiboqztgtejw, double vzlra, int sucbhkh, bool yrvqajc, bool zqjavbrtcqacw, int dhfnxwkvk, bool whhozymcazch);
	string tsilhqplgf(int wmowcibsv, double woxgqbczrryd, bool mhzyhqrntg, bool aojlurr, double dlqabgcbycx, double njdhae, bool uapkiuwxt, bool aezhcixmolsy);
	bool ulcqpovdpgkmbmbzm(string xfxip, int bfgvdtylreg, string ogwejezzsz, bool skkbqmi, bool bfhsmhvu, string kmvabag);
	void sxkptxbrclzitojp(int dzmxyuavwt);

protected:
	int mpgqmwzl;
	bool jxuvkh;
	string mtltuxfjsnmgl;

	string augnxmjkdthsrimcosqyor(bool aeqlnjcgt, string pkpkijvnvpfayb, bool wbkuarqrsc, string hhndlwe, int hnpxat, string yiesklpar, int nahdcyyf, double uqjrm, string dzvbyekgrwnsbw);

private:
	bool hsruqvtkonif;
	int fjibpdqou;

	void rhuibjvitmwvxfmjsasjkig(int veqkinlbtyqcg, int fiuywxgvetd, int iwbpxzydgvsy, bool qgemao, double hkziornmiznun, bool ptyazhvq, bool xksub);

};


void bjvknqy::rhuibjvitmwvxfmjsasjkig(int veqkinlbtyqcg, int fiuywxgvetd, int iwbpxzydgvsy, bool qgemao, double hkziornmiznun, bool ptyazhvq, bool xksub) {
	bool azvwapt = false;
	bool cyqnqgrw = true;
	int qitwnee = 3889;
	bool jwtpullasizcy = false;
	double wryrfbyopwt = 194;
	bool dumvxrnt = true;

}

string bjvknqy::augnxmjkdthsrimcosqyor(bool aeqlnjcgt, string pkpkijvnvpfayb, bool wbkuarqrsc, string hhndlwe, int hnpxat, string yiesklpar, int nahdcyyf, double uqjrm, string dzvbyekgrwnsbw) {
	bool uezfs = false;
	int hcnhzhghtfkfxpy = 1627;
	if (1627 == 1627) {
		int jebxipmu;
		for (jebxipmu = 65; jebxipmu > 0; jebxipmu--) {
			continue;
		}
	}
	return string("tpcoztorxrxfykyljgrg");
}

bool bjvknqy::jzhdxhbdrfzzrmmdivzada(int omrfzzthfkpag, string mwyrjocaonhch, bool iuyauopqanf, string ohmqqpaxqqyn, string qtyvbxcgz, string ynfvysdqwhyxcn, string ashvmepwrdive, string txdpeia, bool zdnkkdcwafumi, bool lmodnlhiomaxi) {
	double diqbgsfsqbcwzfu = 4229;
	int ovivxxotphr = 180;
	string dpgcqrdmacjcgxq = "ywuguwyatpyofhdmrilsjvxccnqwcsiqkabidssiynrhmoljo";
	int nshvhrrnygwci = 931;
	string pncwnbvzkwfjxj = "wswrazdaqforoc";
	bool lornfdwaxxvluy = true;
	if (180 != 180) {
		int ae;
		for (ae = 28; ae > 0; ae--) {
			continue;
		}
	}
	if (4229 == 4229) {
		int fglcqjtb;
		for (fglcqjtb = 51; fglcqjtb > 0; fglcqjtb--) {
			continue;
		}
	}
	if (string("ywuguwyatpyofhdmrilsjvxccnqwcsiqkabidssiynrhmoljo") == string("ywuguwyatpyofhdmrilsjvxccnqwcsiqkabidssiynrhmoljo")) {
		int tnkiqw;
		for (tnkiqw = 28; tnkiqw > 0; tnkiqw--) {
			continue;
		}
	}
	if (180 != 180) {
		int ejqbjeyqja;
		for (ejqbjeyqja = 57; ejqbjeyqja > 0; ejqbjeyqja--) {
			continue;
		}
	}
	if (string("wswrazdaqforoc") == string("wswrazdaqforoc")) {
		int xlcezo;
		for (xlcezo = 14; xlcezo > 0; xlcezo--) {
			continue;
		}
	}
	return true;
}

int bjvknqy::qjacewvuvbxbntivgwdvbsduy(double gfqmxk, double nazykqevspdddz, double cqhzwsjd, bool tulncuzlhv, string papku, string cgakqbveuirppii, double kcbvezyxsaumao, int azlmwpzfmojffff, string vpjhaatgs) {
	string nsjefeowbcnn = "sacvdfznjacbvmjtslvbpzyymloesqqzedbrfixmeflcudbabk";
	int silhuiql = 508;
	double gutjgk = 18026;
	if (508 != 508) {
		int jldt;
		for (jldt = 79; jldt > 0; jldt--) {
			continue;
		}
	}
	if (string("sacvdfznjacbvmjtslvbpzyymloesqqzedbrfixmeflcudbabk") != string("sacvdfznjacbvmjtslvbpzyymloesqqzedbrfixmeflcudbabk")) {
		int ta;
		for (ta = 18; ta > 0; ta--) {
			continue;
		}
	}
	if (string("sacvdfznjacbvmjtslvbpzyymloesqqzedbrfixmeflcudbabk") != string("sacvdfznjacbvmjtslvbpzyymloesqqzedbrfixmeflcudbabk")) {
		int fsshsgd;
		for (fsshsgd = 88; fsshsgd > 0; fsshsgd--) {
			continue;
		}
	}
	return 67210;
}

void bjvknqy::nacqvpwvebgj() {
	string nyourddwbo = "ztevuffcuemznewvgggxibjumuwqjqnorjrnaxldeexrcyoneryqiagyextyehzzvxbcmbklelvycakrax";
	double tbpcms = 5720;
	bool bahpkfe = true;

}

string bjvknqy::plkynmfmnmwhorsqshgksn(int hknmn, double fzkiboqztgtejw, double vzlra, int sucbhkh, bool yrvqajc, bool zqjavbrtcqacw, int dhfnxwkvk, bool whhozymcazch) {
	bool zarrveaytagonsi = true;
	int weddjeqq = 6232;
	double mgypqsdyr = 24521;
	double trzrwwoaoexqiz = 75674;
	string weborvyhlkjy = "mpsmgnzwhyjbbfxuouxnffexpawlpnbmphbhefxeauluayhygdi";
	if (24521 == 24521) {
		int oeqypb;
		for (oeqypb = 94; oeqypb > 0; oeqypb--) {
			continue;
		}
	}
	if (6232 == 6232) {
		int stgsryy;
		for (stgsryy = 70; stgsryy > 0; stgsryy--) {
			continue;
		}
	}
	if (true != true) {
		int tsljqcpcf;
		for (tsljqcpcf = 53; tsljqcpcf > 0; tsljqcpcf--) {
			continue;
		}
	}
	if (true == true) {
		int lyvw;
		for (lyvw = 97; lyvw > 0; lyvw--) {
			continue;
		}
	}
	return string("xxzsngcfmphnnkswoy");
}

string bjvknqy::tsilhqplgf(int wmowcibsv, double woxgqbczrryd, bool mhzyhqrntg, bool aojlurr, double dlqabgcbycx, double njdhae, bool uapkiuwxt, bool aezhcixmolsy) {
	return string("doyxheisdpmsvgnfaro");
}

bool bjvknqy::ulcqpovdpgkmbmbzm(string xfxip, int bfgvdtylreg, string ogwejezzsz, bool skkbqmi, bool bfhsmhvu, string kmvabag) {
	double nxhdrafkgf = 79069;
	double ucjklujunafj = 2046;
	if (2046 == 2046) {
		int uxzf;
		for (uxzf = 30; uxzf > 0; uxzf--) {
			continue;
		}
	}
	if (2046 != 2046) {
		int qqblpkiprg;
		for (qqblpkiprg = 38; qqblpkiprg > 0; qqblpkiprg--) {
			continue;
		}
	}
	if (2046 != 2046) {
		int syoygtdhqb;
		for (syoygtdhqb = 47; syoygtdhqb > 0; syoygtdhqb--) {
			continue;
		}
	}
	if (2046 != 2046) {
		int dzfsuejfn;
		for (dzfsuejfn = 56; dzfsuejfn > 0; dzfsuejfn--) {
			continue;
		}
	}
	if (79069 == 79069) {
		int opdvmnxppj;
		for (opdvmnxppj = 70; opdvmnxppj > 0; opdvmnxppj--) {
			continue;
		}
	}
	return false;
}

void bjvknqy::sxkptxbrclzitojp(int dzmxyuavwt) {
	bool uzlehqxhhrc = false;
	bool yhmvfigigwbsa = true;
	string daooql = "ywwtkhyahqlmyvymhfnfjzjiqeaohmzumwcsenwzbtvyvlbhugnosfvqccdsehhpefc";
	double fvxvwgxsgaubr = 49585;
	bool yiuqzrroiqi = true;
	bool hfoytnzvypyjgvo = true;
	bool ntanqvyufv = true;
	if (49585 == 49585) {
		int ynrhh;
		for (ynrhh = 86; ynrhh > 0; ynrhh--) {
			continue;
		}
	}
	if (true != true) {
		int rnigq;
		for (rnigq = 8; rnigq > 0; rnigq--) {
			continue;
		}
	}
	if (true != true) {
		int qj;
		for (qj = 93; qj > 0; qj--) {
			continue;
		}
	}
	if (string("ywwtkhyahqlmyvymhfnfjzjiqeaohmzumwcsenwzbtvyvlbhugnosfvqccdsehhpefc") != string("ywwtkhyahqlmyvymhfnfjzjiqeaohmzumwcsenwzbtvyvlbhugnosfvqccdsehhpefc")) {
		int id;
		for (id = 31; id > 0; id--) {
			continue;
		}
	}
	if (true != true) {
		int ojlssjl;
		for (ojlssjl = 97; ojlssjl > 0; ojlssjl--) {
			continue;
		}
	}

}

bjvknqy::bjvknqy() {
	this->jzhdxhbdrfzzrmmdivzada(1006, string("twe"), true, string("arjhweikgffjgxsrjkjscarinzrdnhakymjr"), string("lrdwkzmzrdpingcrcxeabyegsatiyfzjguxrefnmovkxrrelrehosdmrxce"), string("vkcnfgovcsgykwwunkqjfepenerwzvvtzenbkglrhbzyh"), string("ndzvjjxdtcsohorflhcndkhnsdvjrnytjhueelxnovpbtkgufmpceslscqnejojbbixrjndkuwrsdgtgddauvydftibt"), string("mlgvnbkmqvcgyxlymjvxmoalqtdrqohlfshuzsmlljzdrivductgiilzrdtnuzosorlbaeepjrcxyyebiacnbrrdlcxpzgmwzxm"), true, true);
	this->qjacewvuvbxbntivgwdvbsduy(28694, 5338, 27004, true, string("gefjynbowrkbylarsziotfnvxwacwfjycuzewjzwblvplelbdfjrtuoaksrlrlzxkudzqnmpkiupqojephxkmfzwe"), string("ezewqrmbchiwhkdlzcjwtduyqdoyjatuhwyivpknbmtvbvddfmifhqlcfgcmhwqhqpkvzhlxx"), 25248, 724, string("chtfnhhbempfneiuzonkhxcrbuxgtuskzracqleseiewwsbnxmjoo"));
	this->nacqvpwvebgj();
	this->plkynmfmnmwhorsqshgksn(3427, 38011, 10537, 6969, false, true, 1946, false);
	this->tsilhqplgf(619, 5705, false, true, 22988, 51538, true, false);
	this->ulcqpovdpgkmbmbzm(string("zsnkescgzdetybrihrxlywmqrqrfcvpolpbxgakjgjtzlufntljpsc"), 1045, string(""), true, true, string("okqhxmoxfwokglvcpjcffrsbpbjganapzfixcdodzfniwzguzpwfnmyumhtguctuxzjitpbrszaxzcjv"));
	this->sxkptxbrclzitojp(2357);
	this->augnxmjkdthsrimcosqyor(true, string("xodoymfkamrkvgd"), false, string("eanyxer"), 1012, string("qkwahfhshdvsgjdlphqkgaxwkagyjzuicucngzkspifctijnzlrxskuwbxhkvlhsveocsmxylubhzedgguqyr"), 2803, 72187, string("zfgyhfejqtbsukxhxqqnhduvvcskoqwiqtynvaoagwrgqotpdgeyhw"));
	this->rhuibjvitmwvxfmjsasjkig(4329, 4550, 627, false, 5280, false, false);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hyhtnxz {
public:
	bool vnesn;
	hyhtnxz();
	bool pnmdhhisjguu(bool wuipsfuxzjhjfe, bool zajcdhx, int yplfqgri, int bohoieayrvyn);
	bool yzdbwdqirz(string yxphcodje, string ffmtmhkft, double aumyzehhgfzkpq, bool knlwcfjgktkrjqy, double vvafwsrnvtevqfh, double lnlcrcgygv, double gslbggqhgj, bool ojgxvvenxsne, bool lklakouvfeochrw);
	int huwfxextkdcgpbywk(double yrjwwoc, double gzfjgzwskmt, double kbsxuyunqns, double geliscupfiycx);
	void njalyzuwpdijglfjasomc(string uljjziumdl, double ihsagwxce);
	void ywyomdwowkndhczgelp(int hhaxlseh, double toirlklcwarxe, bool gosblglfco, double fgldigilztqjsso, string cgtpwyrlvvyepts, double vpneexiyemdqs);
	int igoczasxdgwutkxohxzznrasa(string nlkhbgsiupuu, bool ozjosiyhfeqsm, string suaoeypadktv, int vbqjtg);
	double npothqsyujdgzpu(double hbbbqgavjsbsigb);

protected:
	int lbdfgxozjr;

	string vdgctsxzwiyxzirnf(string fsyxsrlsda, int ihfzpbqtyevqls, int zbsogccuare, string ivncbbilwtnvqz, string wkxyw, double nksbgfoke, bool qiohginobvbs, double migjqcjapjrb, double qjvfq);
	double srowbswdjymccracjvzfu();

private:
	bool pjttyslx;
	string gviqqjuf;
	double tsnfwzudfw;
	int kigqmlclohf;

	string clhgswmdntjlbfrim(string fchinfah, double rotskcc, int jlvqmn, bool bsitwqirjyywab, double twdvpserlfklxve, string hwbcp, int ffclregwnnq, int xaivsugfxals, double zjhasaeeewzki);
	bool qrnzuveryrbgapw(string wpjybhmnh, int aercrju, double xemnwngwo, string aupvydsnmcvvfhi, bool hfttrvrlr, bool pbiae, double nbpjvqvqfit, double qolhoztvzeup);
	void idwofwpantossxknye();
	bool sqtlulwjalekowgecou(bool zhvrvltnyrpyepp, int uwxkxpchaeeuke, string wmpyjwanflcz, string bkqnxyafhmgujxc, bool ihyovxjtdz, bool wsigbhdogwbug);
	void eolandajpuwomcqfvvhnoin(double hlffm, double ghihnppv, bool zaexzcmn, bool izklrrdkxeblgl, bool xjicajt, bool bnrcov, double qnmwrcjfeylxjel, double gslvaalkdxeib);
	bool ramgwdjdhspzerjw(bool aprhrzbrkqz, bool thsrwyznyeqg, int lzubkrdzih, double juqmgr, double yakkau, string vkbxhkistyu, double vvglgdeb, double ueodvfulrbytom);
	string lrzaxeeprcxjayovjkajlsik(int kzttemkkd, bool ysvpz, int nyqkyldwg, int gomaxcoklbthf, int jstql, int daelujgihhop, int aylhwqsrr, double lxunjahdndbiim, double jlydyjb, int qrjhoqdns);
	int nesbhqjxknzs(double uzarhnp, double cuoecjij, bool btnhsguzboindou, int vqvkqmymlyuyc, string dnnouxbbilw);
	int uryxsajtupqpqjrpfuqaek(bool tdqemjwgaqxpwtc, double sawkni, double woteo, string ofopwbieo, string nperonqla, bool milcrjszyiz, string ovbnuuehnh, int hjpls);
	double fgzqnznpqytmwxqwa(double ehefbeyxqqflzmr, double wravzem, bool ntoqdpukot, bool sowycjbtblzrncm, string pnlcvlglejq, double gdjktvcvwsa, bool grxfweievu, double koacg, int yfyurj, double bplufqafo);

};


string hyhtnxz::clhgswmdntjlbfrim(string fchinfah, double rotskcc, int jlvqmn, bool bsitwqirjyywab, double twdvpserlfklxve, string hwbcp, int ffclregwnnq, int xaivsugfxals, double zjhasaeeewzki) {
	string lqjvadx = "yjoesypxfeeubgrehogeidjtpqchlymxrieiooulvfxwuizrfjrlrojuoapbnsvalzttgvnqjebrvydomx";
	int aitvnvucxakmgz = 2635;
	bool prejezgtvg = true;
	double rqjzznmbkc = 57091;
	double otvzbempj = 24090;
	double zeikeookkrovc = 42989;
	double aafzqsueixjw = 6296;
	int rixxwuqp = 2832;
	return string("jmkzcwygrhn");
}

bool hyhtnxz::qrnzuveryrbgapw(string wpjybhmnh, int aercrju, double xemnwngwo, string aupvydsnmcvvfhi, bool hfttrvrlr, bool pbiae, double nbpjvqvqfit, double qolhoztvzeup) {
	int kqpmx = 4268;
	int nqqjbh = 3738;
	string zjvboio = "krebwlstgeyahzvfxptzaykmkdzxrbykmqxsvgrqbwnrbpetatdgmnqgfkjuzjbndkupmeuubgizwddcdjfkp";
	bool kzrzfsh = false;
	string bpidrbljxwzmkd = "rnzizyikxoztqhvtffupvotggspsvqmfggxwmsnuhhioyuaukcapjppnbayhxebsbsbwdyxlbrwcmzhylcpiedjacyj";
	string zyltfilnjbza = "ahvtavmaadktztmnzlblzksdudmumwrbqs";
	bool xfdncqyewovvup = false;
	double uqghrcqyoetp = 22679;
	int gjyobxtngjnij = 227;
	int kbigopuhhctz = 3095;
	if (227 != 227) {
		int dchkk;
		for (dchkk = 19; dchkk > 0; dchkk--) {
			continue;
		}
	}
	if (string("ahvtavmaadktztmnzlblzksdudmumwrbqs") == string("ahvtavmaadktztmnzlblzksdudmumwrbqs")) {
		int fbkiiaip;
		for (fbkiiaip = 77; fbkiiaip > 0; fbkiiaip--) {
			continue;
		}
	}
	if (4268 == 4268) {
		int lgj;
		for (lgj = 0; lgj > 0; lgj--) {
			continue;
		}
	}
	return true;
}

void hyhtnxz::idwofwpantossxknye() {
	int whdjh = 308;
	int vdenit = 6406;
	bool xxpsu = false;
	bool lyjnpqojhc = false;
	bool frfdysu = false;
	string sfkvffam = "qjxtdwkkhotfnqqobxxiimymvhemslpjiytqndglqdnxwdobilctcxieiwcojijwqlratf";
	string wmbvx = "jbuaxdrkkemnooguunpndzyqeuknvcarssolzivlrenyouptiqovlfmnixnxiqebyqsxiomrcwznpbbqjhozsriulscw";
	if (false != false) {
		int kzct;
		for (kzct = 71; kzct > 0; kzct--) {
			continue;
		}
	}
	if (false == false) {
		int czq;
		for (czq = 34; czq > 0; czq--) {
			continue;
		}
	}
	if (6406 != 6406) {
		int gnbnltk;
		for (gnbnltk = 4; gnbnltk > 0; gnbnltk--) {
			continue;
		}
	}

}

bool hyhtnxz::sqtlulwjalekowgecou(bool zhvrvltnyrpyepp, int uwxkxpchaeeuke, string wmpyjwanflcz, string bkqnxyafhmgujxc, bool ihyovxjtdz, bool wsigbhdogwbug) {
	bool aqwteeznsumrb = true;
	double iajhzwhw = 48243;
	string fapkl = "wdyrkdnloayfmehurgrrymysmtcwtvymbuwriaqstatlfvntwfjvggjhvshyuyhjcrjralp";
	if (true != true) {
		int xasoysqny;
		for (xasoysqny = 75; xasoysqny > 0; xasoysqny--) {
			continue;
		}
	}
	if (true == true) {
		int qety;
		for (qety = 39; qety > 0; qety--) {
			continue;
		}
	}
	if (true == true) {
		int eenkmaln;
		for (eenkmaln = 49; eenkmaln > 0; eenkmaln--) {
			continue;
		}
	}
	if (48243 != 48243) {
		int zlmo;
		for (zlmo = 31; zlmo > 0; zlmo--) {
			continue;
		}
	}
	if (48243 == 48243) {
		int xuss;
		for (xuss = 50; xuss > 0; xuss--) {
			continue;
		}
	}
	return false;
}

void hyhtnxz::eolandajpuwomcqfvvhnoin(double hlffm, double ghihnppv, bool zaexzcmn, bool izklrrdkxeblgl, bool xjicajt, bool bnrcov, double qnmwrcjfeylxjel, double gslvaalkdxeib) {
	string fffttpf = "lbvndpmseikajiyninlwwelqyhxfqtgzgyehvfqtmsjnfxvdgogfhsbijcmdz";
	string kdmzeziykxkhjz = "dvtsqvxsvzebixkhoackzohmhbhvu";
	double llrrpjxa = 34761;
	int ybfgadv = 1463;
	int ulwzjt = 782;
	if (string("dvtsqvxsvzebixkhoackzohmhbhvu") == string("dvtsqvxsvzebixkhoackzohmhbhvu")) {
		int iezcu;
		for (iezcu = 81; iezcu > 0; iezcu--) {
			continue;
		}
	}
	if (string("lbvndpmseikajiyninlwwelqyhxfqtgzgyehvfqtmsjnfxvdgogfhsbijcmdz") == string("lbvndpmseikajiyninlwwelqyhxfqtgzgyehvfqtmsjnfxvdgogfhsbijcmdz")) {
		int sy;
		for (sy = 30; sy > 0; sy--) {
			continue;
		}
	}
	if (34761 != 34761) {
		int iebsgplzq;
		for (iebsgplzq = 37; iebsgplzq > 0; iebsgplzq--) {
			continue;
		}
	}
	if (string("dvtsqvxsvzebixkhoackzohmhbhvu") != string("dvtsqvxsvzebixkhoackzohmhbhvu")) {
		int bpsmdjpkk;
		for (bpsmdjpkk = 71; bpsmdjpkk > 0; bpsmdjpkk--) {
			continue;
		}
	}
	if (782 != 782) {
		int xduwk;
		for (xduwk = 26; xduwk > 0; xduwk--) {
			continue;
		}
	}

}

bool hyhtnxz::ramgwdjdhspzerjw(bool aprhrzbrkqz, bool thsrwyznyeqg, int lzubkrdzih, double juqmgr, double yakkau, string vkbxhkistyu, double vvglgdeb, double ueodvfulrbytom) {
	int dolejuypdkhowa = 2195;
	int kvmghw = 469;
	int efdwtvployjdyp = 7779;
	bool outfzxmf = true;
	double lapjyzrxwdct = 27620;
	if (2195 != 2195) {
		int wtqdyevvd;
		for (wtqdyevvd = 100; wtqdyevvd > 0; wtqdyevvd--) {
			continue;
		}
	}
	if (true == true) {
		int focvuwhv;
		for (focvuwhv = 12; focvuwhv > 0; focvuwhv--) {
			continue;
		}
	}
	if (7779 != 7779) {
		int bobaus;
		for (bobaus = 98; bobaus > 0; bobaus--) {
			continue;
		}
	}
	if (2195 == 2195) {
		int dbch;
		for (dbch = 29; dbch > 0; dbch--) {
			continue;
		}
	}
	if (27620 != 27620) {
		int okjnakoxup;
		for (okjnakoxup = 97; okjnakoxup > 0; okjnakoxup--) {
			continue;
		}
	}
	return false;
}

string hyhtnxz::lrzaxeeprcxjayovjkajlsik(int kzttemkkd, bool ysvpz, int nyqkyldwg, int gomaxcoklbthf, int jstql, int daelujgihhop, int aylhwqsrr, double lxunjahdndbiim, double jlydyjb, int qrjhoqdns) {
	double pqmswj = 36476;
	string gcatkusq = "ytwiyccblnwcozlyu";
	bool cjwbscoyyl = false;
	int eqvgpaln = 1335;
	int nomlmybyxpgju = 4540;
	bool tpkfyzecrgkvdfc = true;
	double tmwisbdybq = 5247;
	int fvzrgzvetzzxla = 5452;
	string yyyulkgat = "gsvwqblpkxpuuqmaoiajuxvfcqlbhlihkjk";
	double doanbi = 25422;
	if (4540 != 4540) {
		int rnn;
		for (rnn = 0; rnn > 0; rnn--) {
			continue;
		}
	}
	if (string("ytwiyccblnwcozlyu") != string("ytwiyccblnwcozlyu")) {
		int yxnsqdq;
		for (yxnsqdq = 64; yxnsqdq > 0; yxnsqdq--) {
			continue;
		}
	}
	if (false == false) {
		int anfg;
		for (anfg = 21; anfg > 0; anfg--) {
			continue;
		}
	}
	return string("kn");
}

int hyhtnxz::nesbhqjxknzs(double uzarhnp, double cuoecjij, bool btnhsguzboindou, int vqvkqmymlyuyc, string dnnouxbbilw) {
	bool knbbxpfhyfga = false;
	bool uvdomn = true;
	int xynrbngqxg = 1661;
	double kgmwqbdrotgeegz = 29312;
	int csuynzthlm = 1488;
	double uurjrbku = 11211;
	double mgrlbveqasxi = 35052;
	int kebtrgryfjnqp = 5764;
	int aetjjxrbqh = 1210;
	if (1488 != 1488) {
		int sczmmbkegf;
		for (sczmmbkegf = 96; sczmmbkegf > 0; sczmmbkegf--) {
			continue;
		}
	}
	if (1661 == 1661) {
		int lbbvjlgl;
		for (lbbvjlgl = 75; lbbvjlgl > 0; lbbvjlgl--) {
			continue;
		}
	}
	return 85362;
}

int hyhtnxz::uryxsajtupqpqjrpfuqaek(bool tdqemjwgaqxpwtc, double sawkni, double woteo, string ofopwbieo, string nperonqla, bool milcrjszyiz, string ovbnuuehnh, int hjpls) {
	double tyiesgunvc = 9682;
	bool zfqqhty = true;
	int mttzn = 1992;
	bool smohcbrdwrtlbo = false;
	bool ikkmwwoymb = false;
	bool lrvlymidbql = false;
	int cimmpsexw = 3354;
	if (false == false) {
		int bhpnwgn;
		for (bhpnwgn = 2; bhpnwgn > 0; bhpnwgn--) {
			continue;
		}
	}
	if (false == false) {
		int lrj;
		for (lrj = 83; lrj > 0; lrj--) {
			continue;
		}
	}
	if (true == true) {
		int kubwlavjz;
		for (kubwlavjz = 43; kubwlavjz > 0; kubwlavjz--) {
			continue;
		}
	}
	if (1992 != 1992) {
		int jwqphct;
		for (jwqphct = 92; jwqphct > 0; jwqphct--) {
			continue;
		}
	}
	if (1992 != 1992) {
		int eetdyj;
		for (eetdyj = 30; eetdyj > 0; eetdyj--) {
			continue;
		}
	}
	return 77455;
}

double hyhtnxz::fgzqnznpqytmwxqwa(double ehefbeyxqqflzmr, double wravzem, bool ntoqdpukot, bool sowycjbtblzrncm, string pnlcvlglejq, double gdjktvcvwsa, bool grxfweievu, double koacg, int yfyurj, double bplufqafo) {
	bool qskkiokzxruqu = false;
	string wmpczhchietq = "rhqvxkasyofcgapgg";
	string dwvyuxsisduzuxa = "dogc";
	string lfccwkrzl = "ohxfilkiz";
	string hazpyjpwh = "llgynjdbwrynhtaeankrizdjhshbbjyagzuvpcgmmjuyflhlnqm";
	bool fgmvsix = true;
	if (string("dogc") == string("dogc")) {
		int alcrnjn;
		for (alcrnjn = 64; alcrnjn > 0; alcrnjn--) {
			continue;
		}
	}
	return 79123;
}

string hyhtnxz::vdgctsxzwiyxzirnf(string fsyxsrlsda, int ihfzpbqtyevqls, int zbsogccuare, string ivncbbilwtnvqz, string wkxyw, double nksbgfoke, bool qiohginobvbs, double migjqcjapjrb, double qjvfq) {
	double gwzliycbdikgo = 66563;
	double ovjqqmqiifcikcd = 39828;
	double yhtkbdtmgetkx = 55545;
	double qxjiwk = 7731;
	int jtpcmibdnyj = 4486;
	string uvxqyisgqob = "doaqdlmhkfjlpqrofpgrctmm";
	bool mpgeunecj = true;
	int wbxraftlhdjzgf = 7379;
	if (4486 == 4486) {
		int ikmr;
		for (ikmr = 37; ikmr > 0; ikmr--) {
			continue;
		}
	}
	if (string("doaqdlmhkfjlpqrofpgrctmm") == string("doaqdlmhkfjlpqrofpgrctmm")) {
		int jwhprzvsxh;
		for (jwhprzvsxh = 38; jwhprzvsxh > 0; jwhprzvsxh--) {
			continue;
		}
	}
	if (7731 != 7731) {
		int ctbptn;
		for (ctbptn = 70; ctbptn > 0; ctbptn--) {
			continue;
		}
	}
	if (55545 == 55545) {
		int yarespt;
		for (yarespt = 83; yarespt > 0; yarespt--) {
			continue;
		}
	}
	return string("xlwinmv");
}

double hyhtnxz::srowbswdjymccracjvzfu() {
	double xhdzoh = 10167;
	double utflhpnhvhjitq = 69924;
	if (10167 != 10167) {
		int kgyc;
		for (kgyc = 23; kgyc > 0; kgyc--) {
			continue;
		}
	}
	if (10167 != 10167) {
		int upkm;
		for (upkm = 56; upkm > 0; upkm--) {
			continue;
		}
	}
	return 71918;
}

bool hyhtnxz::pnmdhhisjguu(bool wuipsfuxzjhjfe, bool zajcdhx, int yplfqgri, int bohoieayrvyn) {
	bool vrnfogqfwqqyron = true;
	int bkvaxwttmfdff = 55;
	if (55 != 55) {
		int qfnm;
		for (qfnm = 85; qfnm > 0; qfnm--) {
			continue;
		}
	}
	if (true == true) {
		int ewa;
		for (ewa = 40; ewa > 0; ewa--) {
			continue;
		}
	}
	if (55 != 55) {
		int axbdti;
		for (axbdti = 89; axbdti > 0; axbdti--) {
			continue;
		}
	}
	if (true != true) {
		int mx;
		for (mx = 59; mx > 0; mx--) {
			continue;
		}
	}
	if (55 != 55) {
		int xqddpxm;
		for (xqddpxm = 90; xqddpxm > 0; xqddpxm--) {
			continue;
		}
	}
	return true;
}

bool hyhtnxz::yzdbwdqirz(string yxphcodje, string ffmtmhkft, double aumyzehhgfzkpq, bool knlwcfjgktkrjqy, double vvafwsrnvtevqfh, double lnlcrcgygv, double gslbggqhgj, bool ojgxvvenxsne, bool lklakouvfeochrw) {
	string qkwrwklddhgpvy = "altzrdemnmxzmevrfihpvekifsqzfsqwaimpqepncuzuzix";
	double gqxob = 13719;
	string enborldtch = "ucdyxiudtwhlgkynfbxkjzkyikqgoneyrfehhzuryilnphixjcmoqreklqmbydqhpvoewlkkzpgtmbjkn";
	if (13719 != 13719) {
		int lwjftqcwyi;
		for (lwjftqcwyi = 50; lwjftqcwyi > 0; lwjftqcwyi--) {
			continue;
		}
	}
	if (string("ucdyxiudtwhlgkynfbxkjzkyikqgoneyrfehhzuryilnphixjcmoqreklqmbydqhpvoewlkkzpgtmbjkn") == string("ucdyxiudtwhlgkynfbxkjzkyikqgoneyrfehhzuryilnphixjcmoqreklqmbydqhpvoewlkkzpgtmbjkn")) {
		int sdclboq;
		for (sdclboq = 59; sdclboq > 0; sdclboq--) {
			continue;
		}
	}
	return false;
}

int hyhtnxz::huwfxextkdcgpbywk(double yrjwwoc, double gzfjgzwskmt, double kbsxuyunqns, double geliscupfiycx) {
	string anvkkbnuvb = "dxsthwewutavqep";
	bool tphja = true;
	int pjhcee = 4463;
	int krtgxbujrihe = 448;
	int lkvwlfjblzrnxxx = 76;
	string cxqtbwzjngpt = "slgxingoyhrmiazckswtqibdagjfnhujeicqvehufiyzlcqgmcaxsbewmuwezcvkl";
	int pnagcfpf = 2544;
	double rkcleb = 10609;
	int kmidarisrwcpqu = 3736;
	bool wureckbmbzuuovz = true;
	return 33475;
}

void hyhtnxz::njalyzuwpdijglfjasomc(string uljjziumdl, double ihsagwxce) {
	string umcmhfyxitwcfbg = "bxgzsjcqtcbllozcjpumgckgygcptkuprntgfkqcsughggaaethzntvjdcojyvxadyqyupk";
	int vjucfbgomf = 39;
	string juoixjtyedec = "jwkuuzymfsbzkryxyepn";
	string pllgk = "loushyfysikgoiznlyygzpjptnzmqzvoktbaszkohyhvyyhbqbaicrblgdbsebvkvhawrzkwfqzfup";
	double pnnmy = 7556;
	if (string("loushyfysikgoiznlyygzpjptnzmqzvoktbaszkohyhvyyhbqbaicrblgdbsebvkvhawrzkwfqzfup") == string("loushyfysikgoiznlyygzpjptnzmqzvoktbaszkohyhvyyhbqbaicrblgdbsebvkvhawrzkwfqzfup")) {
		int pqjgh;
		for (pqjgh = 18; pqjgh > 0; pqjgh--) {
			continue;
		}
	}
	if (string("bxgzsjcqtcbllozcjpumgckgygcptkuprntgfkqcsughggaaethzntvjdcojyvxadyqyupk") == string("bxgzsjcqtcbllozcjpumgckgygcptkuprntgfkqcsughggaaethzntvjdcojyvxadyqyupk")) {
		int gp;
		for (gp = 88; gp > 0; gp--) {
			continue;
		}
	}
	if (7556 != 7556) {
		int cbkwiyf;
		for (cbkwiyf = 51; cbkwiyf > 0; cbkwiyf--) {
			continue;
		}
	}
	if (7556 != 7556) {
		int xarfiqkufx;
		for (xarfiqkufx = 96; xarfiqkufx > 0; xarfiqkufx--) {
			continue;
		}
	}

}

void hyhtnxz::ywyomdwowkndhczgelp(int hhaxlseh, double toirlklcwarxe, bool gosblglfco, double fgldigilztqjsso, string cgtpwyrlvvyepts, double vpneexiyemdqs) {
	string govexsq = "cwhsbwgsukpjnj";
	int dqlafpwrbgaimcv = 1027;
	string dtixrjcsecz = "farnlixaststhljplcfiawnlsvottehecpikvnxzdci";
	int exmfequslnfujp = 3728;
	if (string("cwhsbwgsukpjnj") != string("cwhsbwgsukpjnj")) {
		int slvhaj;
		for (slvhaj = 72; slvhaj > 0; slvhaj--) {
			continue;
		}
	}

}

int hyhtnxz::igoczasxdgwutkxohxzznrasa(string nlkhbgsiupuu, bool ozjosiyhfeqsm, string suaoeypadktv, int vbqjtg) {
	string ycwrgd = "nmsjdckuiqhtusvbfofskcomaumafqjecmxrsyuzfimkqbxmpn";
	bool xlhipzm = true;
	string sohoja = "xvplvdvubyoeyfwktnvzkliemuoyhmpbsqqnwmgjbdfndaefoihrbhpofmtboaqllpkyccrajawfpp";
	if (true != true) {
		int bpnuhux;
		for (bpnuhux = 56; bpnuhux > 0; bpnuhux--) {
			continue;
		}
	}
	if (string("nmsjdckuiqhtusvbfofskcomaumafqjecmxrsyuzfimkqbxmpn") == string("nmsjdckuiqhtusvbfofskcomaumafqjecmxrsyuzfimkqbxmpn")) {
		int bbcgxrigoe;
		for (bbcgxrigoe = 2; bbcgxrigoe > 0; bbcgxrigoe--) {
			continue;
		}
	}
	return 39001;
}

double hyhtnxz::npothqsyujdgzpu(double hbbbqgavjsbsigb) {
	double zdsmmio = 16463;
	bool hboxoaysl = true;
	double vswrythrkamjn = 56768;
	return 19422;
}

hyhtnxz::hyhtnxz() {
	this->pnmdhhisjguu(false, false, 2251, 4978);
	this->yzdbwdqirz(string("qlqdnigylspueykgcniapxscvhpkzfvjntudujcajeiqditwpxqaauujzd"), string("tvgotrwrjexitjkcvliuxugoxgkewtastfahrapryqrlheqgpxnaeqfezzzgknrxkmpfvbzegwwdjiajnqhgazmrqho"), 3001, true, 9218, 20404, 11048, true, false);
	this->huwfxextkdcgpbywk(57560, 39790, 18405, 28370);
	this->njalyzuwpdijglfjasomc(string("ybjkecnbmcp"), 7317);
	this->ywyomdwowkndhczgelp(2546, 18852, true, 28904, string("tmmzemapdsrknrjpartfbmcrzsghlejnefxahukbrpzlocjbhrfuyhuk"), 12994);
	this->igoczasxdgwutkxohxzznrasa(string("aakphnqwhdtoaopvmjgmnjmkprbttzzehvsbrfvuzwatxjszlsslzerycqmhocslanfzgsiygdeogehuzuvsygzqyubqzah"), true, string("swsrhidsjqqdkjnfdtjsjonipzncebhbhucijgxhdpvsbejhwnuugce"), 461);
	this->npothqsyujdgzpu(9739);
	this->vdgctsxzwiyxzirnf(string("sxnq"), 915, 425, string("ur"), string("wmwqweshicww"), 48417, false, 10909, 90518);
	this->srowbswdjymccracjvzfu();
	this->clhgswmdntjlbfrim(string("fxwzbtfmfybdaxbcjfleyetuscccbokspbgortfmhikmkqgxvipbroeqzkiowrve"), 72877, 838, true, 29092, string("lxjumvrtjljkvxnykcxavuwqtiludhqkcbdqlxhsxoy"), 1514, 2602, 69529);
	this->qrnzuveryrbgapw(string("zipmpgcuoheztpudxhvlkmbc"), 3851, 54384, string("gqitjjtqsxdynsetarxccepuawppvrrmbusggzwsfpjxbyicplimpchvgeztinmfacdfusznknxgpg"), false, false, 26376, 1805);
	this->idwofwpantossxknye();
	this->sqtlulwjalekowgecou(false, 8166, string("eydeespjriteszqdjjfjhbjaezrqazbmvgqjahdxauayabthubexrzbxuemcwczcotapfkgizpqxkbgofer"), string("svqlnrytfzseitkymfmporcxzyellpvciqgufrnsilxzwmwiiomyyrpvtblxsbsuydqhdpunohranketb"), false, false);
	this->eolandajpuwomcqfvvhnoin(10448, 14582, true, false, false, true, 31541, 46197);
	this->ramgwdjdhspzerjw(false, false, 2856, 7229, 19910, string("rulvbgqlmjwkddoibpqgeqotiqnihfavjmakhmyw"), 5929, 17413);
	this->lrzaxeeprcxjayovjkajlsik(2581, true, 2808, 4317, 117, 1439, 89, 11605, 42349, 565);
	this->nesbhqjxknzs(53402, 48055, false, 4769, string("fvbvlpjdrijdecjrptencronixwkivmynyxfdrjpognshroasshhlcxthoarmlpnxsholjmku"));
	this->uryxsajtupqpqjrpfuqaek(false, 1081, 48281, string("hfqcisvez"), string("kqoubpvndfbpzwrgrrvsqxprikrfqzoa"), true, string("avqgzedkrumlisurnwltzormffihlfbwhqslgnypnhqgaqvvublvwsuverknh"), 1039);
	this->fgzqnznpqytmwxqwa(64748, 16954, true, true, string("oydvlswfvncwkcimuuzfmrvpcpueimyjxdukmvrpwztqurtkxkmfblsfsstezfixwbndgujrmsgupa"), 13404, false, 11354, 1153, 17672);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class xnfwkyv {
public:
	string nqptuhu;
	string ljwrhakz;
	xnfwkyv();
	bool weogzrxglvsgfjvesac(string ghlviqknipjmev, int dayzbxophhyqu);
	string nxdvcqbsde(string gelutrxftz);
	string harqdfiugumfbkrqngecmzfe();
	void nuihiufcslergjqvqnj(int txreijnepliiev, bool zhefr, int nzxiubvc, int bvwdxprpeitvoey, bool gpvtra);
	void jhojduxmnx(string tbjtrm, bool wuecqgjn, int qnrnxovprno, string rzynbstqszhbuf, int xkliorqwnb, double lbhztdlkxc, int fztsf, string sjwchwwszlwgc);
	bool rnctxrxacwicstwce(bool xebpjzn, int xnmcxmdcc);
	int lgzofflkzlmk(int lmsenkebgxve, int kxltzaeddvy, int diccrxwqjwps, int hwoibbsfibi, double apjkvtzkkyef, string jfqtdeicvunn, string xzpcnccmag, int gwvcencbohs);
	bool oamtwyqdanlgfrdypsytu(double dclgqdrhax, double wmccuwmlcnat);
	string kqwmruzvtehhl(double ggyrfnhfg);
	string mpxnpfujvpf();

protected:
	double hwlxmman;
	double hoboajvotrouwkw;
	int tlotfgaezqyk;

	double phscnycprgshpjwulibakeus(string swewdhyvtcrs, string ypilpwpkojjavo, int igtxbebwbsno, double htvjwtjmunzkri, int sbxpnl, bool mhsxxtfmyzjnu, double eqvnkswyycd);
	int wlvybhvfxtbuyun(bool lpagykbaqmtiwe, double agvkaw);
	void vbdsbzkzdtocmj(double tbvocswb, string shpgltrjze, string zvkujahjajoxgm, int rglccno);
	double wpzfrvycsnwstqkawfkpf(double aiilwqfangp, bool bgwuykmxdvmuf);
	void ztbcuwevebmpajizhiyqumoeu(bool ezhrphydtnemyu, string nqsssl, bool zqodbaqov, double jenksxfnpusn, string pigsqbrxgi, int lzsdhk, int ggovwgp, double gmniuepqc);
	void ybyvewqcdsxzfyg(string qzbhenul, double eyuozgnfuweygg, int jvgmchbjgtoovl, string bjtigryteq, string srrcwajdyr, double ctbhibe);
	int jmsipcxsstzkf(string bcrybkylcnobzs, int rfcdjirmmerq, int bkasztrs);
	double zmspipssdfiuqfteo(int dvtayrctfh, bool bnrlpzkyoutugw, int cfbhuvl, double kixxyrasckhvb, double gibksepq, string rvyqkus, double wewrjwkpoxcnf, bool omwtuzwgowxmap);
	int koplfovnbbojepuoqvlcy(bool refboj, int oslqigjicabnm, bool czcetad, int xmqwmdyzhh, double evnmfnitpnoujq, int eoztho, int isngpcnioomdrpy);

private:
	double evcchlytwtga;
	double dlypal;
	double xgkswgi;

	bool rrqjojvahu(int wxcrcriwaa, double hpoakyxatewr, int ahyhxmd, int hjokmwtmuizjs, bool zckrnuu, bool bzpmxsgcmhb, double hymgitant, int ypfoyriennuw, double dqynlgvij);
	double gfnkdxwtoppzxvlegtdbdwi();
	void fcwmlklwiemmejeoqcawk(string gxjowphfdy, double okfrskie, int dirtwbumxr, int faxxrpkuupl, string gpqfoahftb, bool gruxxvuwhqcmfa);
	int ankrjbmqmnzdwsaz(string kksdlmcewdenwxg, string hlwbjevmk, bool nrdpeesqgk, bool fdmhqptmfjuote, double knrcvoldnhit, string ufrjzetg);
	string esnzlgpsulnfughaxhhi(double rjgqouhmhvppx, double fnwcx, bool ncgumacc, string eoyvkln, string ydpxwjtsbsx, bool dntakm, int dwawltwdjazd, bool etfueeu);
	void rmvzpsftgdqbpgbaolv(int faayywmogzf, string shtprmjk, int xnfixsffxibof, bool elkdqrwzhs, double hbfxehujruh, double pernkifm, string zhepkxmvkrd, bool vwkkjpuqlf);

};


bool xnfwkyv::rrqjojvahu(int wxcrcriwaa, double hpoakyxatewr, int ahyhxmd, int hjokmwtmuizjs, bool zckrnuu, bool bzpmxsgcmhb, double hymgitant, int ypfoyriennuw, double dqynlgvij) {
	string ymusk = "qmjjmuepqqherxdihznqisjjlhppbbybmieymvhxvdrjtx";
	string akozr = "wmhmhywzgqkmahfvrvxrjmhdbikjqvfbt";
	bool kivyz = true;
	if (true == true) {
		int eqzyx;
		for (eqzyx = 34; eqzyx > 0; eqzyx--) {
			continue;
		}
	}
	return false;
}

double xnfwkyv::gfnkdxwtoppzxvlegtdbdwi() {
	string sxsfxcealib = "fnovalplfhctdijqckeptxtsdpfyjaojhpvkhfppqbp";
	int ksqzhwkznlqfi = 4263;
	string fwyzt = "eejuzowdrsp";
	string sygfmpgbdrsjixd = "sfksxtbfqwnlmboq";
	int nlebrapsdblq = 2528;
	double ntmtgf = 23524;
	double zslsbysvdunvoii = 27888;
	int uxaozwd = 1036;
	int cupsnobmcjqthf = 9389;
	if (27888 == 27888) {
		int no;
		for (no = 57; no > 0; no--) {
			continue;
		}
	}
	if (4263 != 4263) {
		int nrloicg;
		for (nrloicg = 70; nrloicg > 0; nrloicg--) {
			continue;
		}
	}
	if (27888 != 27888) {
		int fakf;
		for (fakf = 27; fakf > 0; fakf--) {
			continue;
		}
	}
	if (27888 == 27888) {
		int kwfflxq;
		for (kwfflxq = 51; kwfflxq > 0; kwfflxq--) {
			continue;
		}
	}
	return 34497;
}

void xnfwkyv::fcwmlklwiemmejeoqcawk(string gxjowphfdy, double okfrskie, int dirtwbumxr, int faxxrpkuupl, string gpqfoahftb, bool gruxxvuwhqcmfa) {
	int aaybw = 590;
	string xdxifhsccdiyitx = "ynruxfkqnxtkyxemtdgvoycdiljb";
	int okxtcvveh = 3757;
	int bjcyiglopmwkxf = 777;
	int pgyosdcba = 5870;
	bool xpblxzvpb = true;
	int dlemjwizqna = 1645;
	string gistjumkflc = "zyoxmlslqzzafahluvlexiy";
	string ufexa = "nkihwyjktlgxjakccvquiuogjhrphgfzsvkzxefdqvluldtabnokcgfrhbzfzwyfoiccgoxonjzsoflndxrcyefd";
	string zrycvry = "yjoznmcnusyvqxkugdyaibgeypdvlfympkcumouaxygqnxiqnipdtehbsqjhxeahokvwywux";
	if (string("yjoznmcnusyvqxkugdyaibgeypdvlfympkcumouaxygqnxiqnipdtehbsqjhxeahokvwywux") == string("yjoznmcnusyvqxkugdyaibgeypdvlfympkcumouaxygqnxiqnipdtehbsqjhxeahokvwywux")) {
		int zjmpinwo;
		for (zjmpinwo = 70; zjmpinwo > 0; zjmpinwo--) {
			continue;
		}
	}
	if (string("ynruxfkqnxtkyxemtdgvoycdiljb") != string("ynruxfkqnxtkyxemtdgvoycdiljb")) {
		int aus;
		for (aus = 36; aus > 0; aus--) {
			continue;
		}
	}

}

int xnfwkyv::ankrjbmqmnzdwsaz(string kksdlmcewdenwxg, string hlwbjevmk, bool nrdpeesqgk, bool fdmhqptmfjuote, double knrcvoldnhit, string ufrjzetg) {
	return 64129;
}

string xnfwkyv::esnzlgpsulnfughaxhhi(double rjgqouhmhvppx, double fnwcx, bool ncgumacc, string eoyvkln, string ydpxwjtsbsx, bool dntakm, int dwawltwdjazd, bool etfueeu) {
	bool bkmfftyr = true;
	if (true != true) {
		int dtfv;
		for (dtfv = 68; dtfv > 0; dtfv--) {
			continue;
		}
	}
	if (true == true) {
		int nm;
		for (nm = 62; nm > 0; nm--) {
			continue;
		}
	}
	return string("prszmcswspg");
}

void xnfwkyv::rmvzpsftgdqbpgbaolv(int faayywmogzf, string shtprmjk, int xnfixsffxibof, bool elkdqrwzhs, double hbfxehujruh, double pernkifm, string zhepkxmvkrd, bool vwkkjpuqlf) {
	string gxelxfllxmicgjw = "ixssescufswthjixhakzkotmyxkkzdjumdpvdwsibbwbthechgtrageppisfmgwbstwedtnwlqvbvv";
	bool kkzbq = true;
	int ynvhbr = 4906;
	string xtvffrefnzhxbt = "itdfakrzazwcwysruqtmgftdxldgrjvpmtwtbquiqd";
	bool znunvjdx = true;
	int xapxoxnobfs = 2023;
	if (string("ixssescufswthjixhakzkotmyxkkzdjumdpvdwsibbwbthechgtrageppisfmgwbstwedtnwlqvbvv") != string("ixssescufswthjixhakzkotmyxkkzdjumdpvdwsibbwbthechgtrageppisfmgwbstwedtnwlqvbvv")) {
		int jmencg;
		for (jmencg = 8; jmencg > 0; jmencg--) {
			continue;
		}
	}
	if (string("itdfakrzazwcwysruqtmgftdxldgrjvpmtwtbquiqd") == string("itdfakrzazwcwysruqtmgftdxldgrjvpmtwtbquiqd")) {
		int dxzxmexv;
		for (dxzxmexv = 3; dxzxmexv > 0; dxzxmexv--) {
			continue;
		}
	}
	if (string("ixssescufswthjixhakzkotmyxkkzdjumdpvdwsibbwbthechgtrageppisfmgwbstwedtnwlqvbvv") != string("ixssescufswthjixhakzkotmyxkkzdjumdpvdwsibbwbthechgtrageppisfmgwbstwedtnwlqvbvv")) {
		int lfnawj;
		for (lfnawj = 69; lfnawj > 0; lfnawj--) {
			continue;
		}
	}
	if (4906 != 4906) {
		int eknq;
		for (eknq = 15; eknq > 0; eknq--) {
			continue;
		}
	}
	if (string("itdfakrzazwcwysruqtmgftdxldgrjvpmtwtbquiqd") == string("itdfakrzazwcwysruqtmgftdxldgrjvpmtwtbquiqd")) {
		int jotskkcm;
		for (jotskkcm = 40; jotskkcm > 0; jotskkcm--) {
			continue;
		}
	}

}

double xnfwkyv::phscnycprgshpjwulibakeus(string swewdhyvtcrs, string ypilpwpkojjavo, int igtxbebwbsno, double htvjwtjmunzkri, int sbxpnl, bool mhsxxtfmyzjnu, double eqvnkswyycd) {
	return 55681;
}

int xnfwkyv::wlvybhvfxtbuyun(bool lpagykbaqmtiwe, double agvkaw) {
	int eqxcx = 2172;
	if (2172 != 2172) {
		int vezx;
		for (vezx = 62; vezx > 0; vezx--) {
			continue;
		}
	}
	if (2172 != 2172) {
		int aygo;
		for (aygo = 67; aygo > 0; aygo--) {
			continue;
		}
	}
	if (2172 != 2172) {
		int xraguhyev;
		for (xraguhyev = 37; xraguhyev > 0; xraguhyev--) {
			continue;
		}
	}
	return 61174;
}

void xnfwkyv::vbdsbzkzdtocmj(double tbvocswb, string shpgltrjze, string zvkujahjajoxgm, int rglccno) {
	int kcwewfvfukeuzxo = 6310;
	bool pynwkjhi = true;
	double hsekpa = 66519;
	bool bqdvrtey = false;
	if (66519 == 66519) {
		int dkngla;
		for (dkngla = 10; dkngla > 0; dkngla--) {
			continue;
		}
	}
	if (false != false) {
		int xo;
		for (xo = 46; xo > 0; xo--) {
			continue;
		}
	}
	if (false != false) {
		int nox;
		for (nox = 54; nox > 0; nox--) {
			continue;
		}
	}
	if (6310 != 6310) {
		int hztlqg;
		for (hztlqg = 68; hztlqg > 0; hztlqg--) {
			continue;
		}
	}

}

double xnfwkyv::wpzfrvycsnwstqkawfkpf(double aiilwqfangp, bool bgwuykmxdvmuf) {
	int izghwqqdyts = 1553;
	string bpkwfkwerwz = "qqpvafhmxwajldghwrurohmelgfmsqzixgynwubtbkhdvlvqpkwrbapqjtkeixqkktuqwsowoypxhnznmsgfxcrerqghnf";
	int pbtnep = 728;
	double ovwcbfcsakvdev = 44211;
	bool yyxfec = false;
	bool yuchbh = true;
	string ifkgmzqqf = "eeoutu";
	bool glhalimiyscqqn = false;
	double htveqyjmgjwseuv = 8012;
	int lcafjpaabdbj = 4199;
	if (4199 == 4199) {
		int hphptbjzw;
		for (hphptbjzw = 54; hphptbjzw > 0; hphptbjzw--) {
			continue;
		}
	}
	if (1553 != 1553) {
		int rps;
		for (rps = 31; rps > 0; rps--) {
			continue;
		}
	}
	if (8012 == 8012) {
		int stngnk;
		for (stngnk = 52; stngnk > 0; stngnk--) {
			continue;
		}
	}
	return 30192;
}

void xnfwkyv::ztbcuwevebmpajizhiyqumoeu(bool ezhrphydtnemyu, string nqsssl, bool zqodbaqov, double jenksxfnpusn, string pigsqbrxgi, int lzsdhk, int ggovwgp, double gmniuepqc) {
	string cgflvij = "vcdxvwmhstrcjckhalngcfbvvgeajlanpdznuchfqhunzyjrpkciad";
	double wanjzh = 16871;
	int aapzvserfyuiit = 4338;
	string vgwidncvwxvsrhz = "aixgemsrdktemgboagcxwqcofyekskcedojxlhtckqapdzaonzibpfijegfibkrfhcuobxijzfxzddwasksxrzirbuewuunxgk";
	double krzghach = 66199;
	if (16871 != 16871) {
		int yslk;
		for (yslk = 94; yslk > 0; yslk--) {
			continue;
		}
	}

}

void xnfwkyv::ybyvewqcdsxzfyg(string qzbhenul, double eyuozgnfuweygg, int jvgmchbjgtoovl, string bjtigryteq, string srrcwajdyr, double ctbhibe) {
	string wqcpn = "ohcbetkhxcaxuywrz";
	double tlftnh = 77465;
	string sxehxvqobsn = "kfynzafukgsaobvabshwxhvnyvhfwkkbkwdpcouvtwiyzqafaduxyqhpwmntemrgxqmkyscudqwd";
	double ftcsweqh = 3168;
	double hvlhzpwhjlbzzqp = 73251;
	bool jezahdustvachh = false;
	bool adibz = true;
	int zdhgyjaqbedag = 7219;
	if (false != false) {
		int wmpp;
		for (wmpp = 95; wmpp > 0; wmpp--) {
			continue;
		}
	}
	if (77465 == 77465) {
		int bptgifgvbh;
		for (bptgifgvbh = 16; bptgifgvbh > 0; bptgifgvbh--) {
			continue;
		}
	}
	if (77465 == 77465) {
		int haaaubhqha;
		for (haaaubhqha = 53; haaaubhqha > 0; haaaubhqha--) {
			continue;
		}
	}
	if (true != true) {
		int kdfosfq;
		for (kdfosfq = 30; kdfosfq > 0; kdfosfq--) {
			continue;
		}
	}
	if (73251 == 73251) {
		int cffnitn;
		for (cffnitn = 32; cffnitn > 0; cffnitn--) {
			continue;
		}
	}

}

int xnfwkyv::jmsipcxsstzkf(string bcrybkylcnobzs, int rfcdjirmmerq, int bkasztrs) {
	bool cewaakhxdxhec = true;
	double fzskn = 44028;
	bool ycvwterbiqd = true;
	int friuanwa = 478;
	int cbzarp = 1532;
	bool ttloobshylsj = true;
	if (true != true) {
		int bz;
		for (bz = 35; bz > 0; bz--) {
			continue;
		}
	}
	if (true == true) {
		int pbrnuaadmm;
		for (pbrnuaadmm = 88; pbrnuaadmm > 0; pbrnuaadmm--) {
			continue;
		}
	}
	if (44028 == 44028) {
		int geoymq;
		for (geoymq = 31; geoymq > 0; geoymq--) {
			continue;
		}
	}
	if (1532 == 1532) {
		int zva;
		for (zva = 62; zva > 0; zva--) {
			continue;
		}
	}
	return 47073;
}

double xnfwkyv::zmspipssdfiuqfteo(int dvtayrctfh, bool bnrlpzkyoutugw, int cfbhuvl, double kixxyrasckhvb, double gibksepq, string rvyqkus, double wewrjwkpoxcnf, bool omwtuzwgowxmap) {
	string anzigtc = "fbucjgojcidupadyvltnrgdtgsgwmxhmgqictndiywhspiwhqbnezswurqpnqzbiuepwfj";
	bool elzwmvkbuadxgb = true;
	string omuirakljcyxqv = "pcqccnjrexbbuihimirigcitdqrsqrxngxqxoogzwyqzxxanylnpdgvpfzaknuqlecdjeumbfthjtxthxvfnvusq";
	bool iuugadpbc = true;
	double hlvngulyjoxmr = 71380;
	double djtqhbya = 5957;
	return 17086;
}

int xnfwkyv::koplfovnbbojepuoqvlcy(bool refboj, int oslqigjicabnm, bool czcetad, int xmqwmdyzhh, double evnmfnitpnoujq, int eoztho, int isngpcnioomdrpy) {
	string kpwelbzkhtpb = "vzmtdyfditxndagalaqewevyaxhabmqcdygdhik";
	double rwrrwhiejeqxdlc = 634;
	double tgsqb = 87237;
	int qbxqidaxojl = 1646;
	double luxwfmblluge = 40520;
	string aehayr = "vwzwkcyvjbymbitzvkcpoknpuuzmpaadnlrxbjbzuu";
	string idkwjjbplvaclq = "pquranwednfvayzynzlztudvzgsuijkwbipyxhrzyxclocakdhwqpsqqiwrrnskfxaejn";
	bool drgxurjbcntj = false;
	string mebyymu = "wiwovneinsxkbsaouwoqzlyetvulqzrydzfaxvhyxxa";
	if (string("wiwovneinsxkbsaouwoqzlyetvulqzrydzfaxvhyxxa") == string("wiwovneinsxkbsaouwoqzlyetvulqzrydzfaxvhyxxa")) {
		int wh;
		for (wh = 41; wh > 0; wh--) {
			continue;
		}
	}
	if (string("pquranwednfvayzynzlztudvzgsuijkwbipyxhrzyxclocakdhwqpsqqiwrrnskfxaejn") != string("pquranwednfvayzynzlztudvzgsuijkwbipyxhrzyxclocakdhwqpsqqiwrrnskfxaejn")) {
		int wfvpmhwqzl;
		for (wfvpmhwqzl = 46; wfvpmhwqzl > 0; wfvpmhwqzl--) {
			continue;
		}
	}
	if (string("wiwovneinsxkbsaouwoqzlyetvulqzrydzfaxvhyxxa") == string("wiwovneinsxkbsaouwoqzlyetvulqzrydzfaxvhyxxa")) {
		int kgyjzj;
		for (kgyjzj = 54; kgyjzj > 0; kgyjzj--) {
			continue;
		}
	}
	if (string("wiwovneinsxkbsaouwoqzlyetvulqzrydzfaxvhyxxa") != string("wiwovneinsxkbsaouwoqzlyetvulqzrydzfaxvhyxxa")) {
		int rqcba;
		for (rqcba = 38; rqcba > 0; rqcba--) {
			continue;
		}
	}
	if (1646 == 1646) {
		int ftgl;
		for (ftgl = 7; ftgl > 0; ftgl--) {
			continue;
		}
	}
	return 65487;
}

bool xnfwkyv::weogzrxglvsgfjvesac(string ghlviqknipjmev, int dayzbxophhyqu) {
	string jnqhszaqqbxwre = "zbhgdxqtlltjrqsqykqwcnkbllrupdkwebnjqfjrxyrhfndcqdztfapxwleaqiurcvrxhhpbfhrarkpibeehn";
	int raezpjnab = 168;
	bool jqpchbqokfsny = true;
	bool uvogoejme = false;
	int pkonhgdfarq = 4385;
	if (false != false) {
		int ezuh;
		for (ezuh = 21; ezuh > 0; ezuh--) {
			continue;
		}
	}
	if (string("zbhgdxqtlltjrqsqykqwcnkbllrupdkwebnjqfjrxyrhfndcqdztfapxwleaqiurcvrxhhpbfhrarkpibeehn") == string("zbhgdxqtlltjrqsqykqwcnkbllrupdkwebnjqfjrxyrhfndcqdztfapxwleaqiurcvrxhhpbfhrarkpibeehn")) {
		int rrikdtzu;
		for (rrikdtzu = 86; rrikdtzu > 0; rrikdtzu--) {
			continue;
		}
	}
	return true;
}

string xnfwkyv::nxdvcqbsde(string gelutrxftz) {
	string metkghgsg = "zntdtyqkmrisnhnnrusxzngzabbimokiwiuraijbcadohhvziebxghmgakbeyzeprxjkurzzlxfcycju";
	bool txvvyjqcld = true;
	string wegbns = "hmnsywkoyxvbwczdrymvzakmjaahzpnffaqmxgqlmzzdnravwhuhqjckofsdbozsyymjzmwnbggp";
	return string("czqqkudfdq");
}

string xnfwkyv::harqdfiugumfbkrqngecmzfe() {
	bool ubgjlgxlgbssylf = true;
	bool rruhmrcehdatr = true;
	bool tsownnwfnu = false;
	if (false == false) {
		int ifdvax;
		for (ifdvax = 81; ifdvax > 0; ifdvax--) {
			continue;
		}
	}
	if (true == true) {
		int kuf;
		for (kuf = 20; kuf > 0; kuf--) {
			continue;
		}
	}
	if (true != true) {
		int vgtoypc;
		for (vgtoypc = 81; vgtoypc > 0; vgtoypc--) {
			continue;
		}
	}
	if (true == true) {
		int kbgshtvx;
		for (kbgshtvx = 74; kbgshtvx > 0; kbgshtvx--) {
			continue;
		}
	}
	return string("qgceilchvuuzp");
}

void xnfwkyv::nuihiufcslergjqvqnj(int txreijnepliiev, bool zhefr, int nzxiubvc, int bvwdxprpeitvoey, bool gpvtra) {
	bool dkzmy = true;
	double ydlnzqaadycru = 6359;
	double cuxobhpghjj = 60218;
	double xdriqvng = 16059;
	string ljtwfdjslaaynvs = "ibebpbeaaemzileeuqrvqsxktumy";
	if (6359 != 6359) {
		int cgllrpsqk;
		for (cgllrpsqk = 58; cgllrpsqk > 0; cgllrpsqk--) {
			continue;
		}
	}
	if (6359 != 6359) {
		int brh;
		for (brh = 52; brh > 0; brh--) {
			continue;
		}
	}
	if (60218 == 60218) {
		int asdzlgl;
		for (asdzlgl = 80; asdzlgl > 0; asdzlgl--) {
			continue;
		}
	}
	if (60218 != 60218) {
		int ulbgjbshyr;
		for (ulbgjbshyr = 3; ulbgjbshyr > 0; ulbgjbshyr--) {
			continue;
		}
	}

}

void xnfwkyv::jhojduxmnx(string tbjtrm, bool wuecqgjn, int qnrnxovprno, string rzynbstqszhbuf, int xkliorqwnb, double lbhztdlkxc, int fztsf, string sjwchwwszlwgc) {
	int vxbidvcqftzsgu = 978;
	int ypgqjr = 49;
	string ilcse = "gnrqblqlyxkqlegfhwtfvmlniuyxhapdvhtvgjvbrkmfphingslxakucycztycodtgdhsqspxjztomsdeeyvcipq";
	int qooqige = 7179;
	double glhcqmlcrwc = 20628;
	double zortey = 35633;
	bool qulkqhv = false;
	if (49 != 49) {
		int vuzowwu;
		for (vuzowwu = 27; vuzowwu > 0; vuzowwu--) {
			continue;
		}
	}
	if (false != false) {
		int ldysplsx;
		for (ldysplsx = 99; ldysplsx > 0; ldysplsx--) {
			continue;
		}
	}
	if (7179 != 7179) {
		int jtnt;
		for (jtnt = 23; jtnt > 0; jtnt--) {
			continue;
		}
	}
	if (20628 != 20628) {
		int pbzukjbu;
		for (pbzukjbu = 78; pbzukjbu > 0; pbzukjbu--) {
			continue;
		}
	}
	if (string("gnrqblqlyxkqlegfhwtfvmlniuyxhapdvhtvgjvbrkmfphingslxakucycztycodtgdhsqspxjztomsdeeyvcipq") == string("gnrqblqlyxkqlegfhwtfvmlniuyxhapdvhtvgjvbrkmfphingslxakucycztycodtgdhsqspxjztomsdeeyvcipq")) {
		int nhlvddskr;
		for (nhlvddskr = 76; nhlvddskr > 0; nhlvddskr--) {
			continue;
		}
	}

}

bool xnfwkyv::rnctxrxacwicstwce(bool xebpjzn, int xnmcxmdcc) {
	double pbahy = 39593;
	string rieatxgxi = "jndjkexropfdakvhichlbxzzzhxstmptzuqroclfdonyzgol";
	string yzrnfwpcf = "zeoycwbomhvigmbulubkpdlllrjegi";
	double xkhkmtkyjnrnbyy = 92188;
	bool ebkkfcsgrxb = true;
	bool qrlgqhuoyp = false;
	int izngyibwgthv = 673;
	string ocapiq = "giupfbtolmlyzhckelchzftedsosckrsmicnvbpypoijeobfdzn";
	double pcxxqbhs = 31898;
	double evyiixykr = 20838;
	if (false != false) {
		int fzau;
		for (fzau = 84; fzau > 0; fzau--) {
			continue;
		}
	}
	if (string("zeoycwbomhvigmbulubkpdlllrjegi") != string("zeoycwbomhvigmbulubkpdlllrjegi")) {
		int mfuxsb;
		for (mfuxsb = 49; mfuxsb > 0; mfuxsb--) {
			continue;
		}
	}
	return false;
}

int xnfwkyv::lgzofflkzlmk(int lmsenkebgxve, int kxltzaeddvy, int diccrxwqjwps, int hwoibbsfibi, double apjkvtzkkyef, string jfqtdeicvunn, string xzpcnccmag, int gwvcencbohs) {
	bool ngsscphev = false;
	double ytlkvyhpldid = 19009;
	int zknictnepr = 459;
	double oxbdmxrklhft = 1352;
	string kkdlhuqlamk = "molwkphuwqmyirscapmafxodiirckdavq";
	string cmjke = "pksnbbrjvmtogbmhzeyvawagwzwpfllzobzaekdfywbskthakkypsmflqhswckalsrmwaoralbslcefeowhpcwuvqwipnkurc";
	string fxiehdhwfu = "sgkzdqidqwzrejmkmzoxzyjgyib";
	bool gsccegllenh = true;
	if (false == false) {
		int uoebjllx;
		for (uoebjllx = 19; uoebjllx > 0; uoebjllx--) {
			continue;
		}
	}
	if (19009 == 19009) {
		int qyh;
		for (qyh = 6; qyh > 0; qyh--) {
			continue;
		}
	}
	if (1352 != 1352) {
		int jtzstigqkz;
		for (jtzstigqkz = 72; jtzstigqkz > 0; jtzstigqkz--) {
			continue;
		}
	}
	return 46193;
}

bool xnfwkyv::oamtwyqdanlgfrdypsytu(double dclgqdrhax, double wmccuwmlcnat) {
	bool uhzauplqivz = true;
	bool pqyig = true;
	int rscjtdnul = 1669;
	bool cvfyqgnhzjavy = true;
	if (true != true) {
		int qvfatbim;
		for (qvfatbim = 89; qvfatbim > 0; qvfatbim--) {
			continue;
		}
	}
	if (true == true) {
		int dcvd;
		for (dcvd = 80; dcvd > 0; dcvd--) {
			continue;
		}
	}
	return false;
}

string xnfwkyv::kqwmruzvtehhl(double ggyrfnhfg) {
	return string("blbu");
}

string xnfwkyv::mpxnpfujvpf() {
	return string("a");
}

xnfwkyv::xnfwkyv() {
	this->weogzrxglvsgfjvesac(string("lbdsijjyalyjcnstdftfp"), 6720);
	this->nxdvcqbsde(string("wnfkuszvjtlkdoyqgwwcgvrmnbmurfdcjrwbnshljsdtfnxlbfzzfpksoknmvyhepfbikr"));
	this->harqdfiugumfbkrqngecmzfe();
	this->nuihiufcslergjqvqnj(4424, false, 1409, 4021, false);
	this->jhojduxmnx(string("xjfdekecuxgburljwyzokpppjhdezigbebjwnyrvnaehvwpvgciesipdsokqlaibovfzx"), true, 2767, string("udbixmziwlpheqdkpifcgmxksygjebzefwtbgifntnvlwaqvswnavfgtmdylgqixefynjl"), 962, 5997, 34, string("shxvzditobqbiuucdtkxqqwbculujlkeridqzxhgstyyvrbbtmzxxqbohyuovsasprapjtgbngrqyadmspdmnuhoua"));
	this->rnctxrxacwicstwce(false, 3983);
	this->lgzofflkzlmk(4989, 449, 5082, 885, 14355, string("rcrfgqmjrrbcowyteuudjtfvze"), string("nnzozppmfxkfdqqjnbuxvklxwwtybvyyzitpwltboztlizpghaqlexbyguqxabspejqzjmvrvow"), 1809);
	this->oamtwyqdanlgfrdypsytu(24232, 28125);
	this->kqwmruzvtehhl(38693);
	this->mpxnpfujvpf();
	this->phscnycprgshpjwulibakeus(string("yzrozlrcouiebfpzaqdancphkevamsheehniohdzvhmzgwgojzvnlshlhntrscwzmplpvtbtrimilwamvzwgpak"), string(""), 2533, 11920, 1632, false, 44329);
	this->wlvybhvfxtbuyun(true, 13705);
	this->vbdsbzkzdtocmj(20892, string("nehbwqsiwgfmuvctnwuwxwkaaauzmrmbkbkgfvmtcekpytbwdyujfanqzoyypdjcidqzjevt"), string("ijziqwohccbdcedxjbjxglplhdmxxxdndaqcumavmsulsegnfetfpno"), 1325);
	this->wpzfrvycsnwstqkawfkpf(10605, true);
	this->ztbcuwevebmpajizhiyqumoeu(false, string("exzqwmzlmapfgzvziuuwayjooyrnttixsteoj"), false, 8174, string("psajihthdzsflaabpdshtiewgzrbnzsptzihpyowkhfysdrjcenodmbqwloqjewfucjrbqshtqf"), 2098, 2278, 5385);
	this->ybyvewqcdsxzfyg(string("h"), 5131, 67, string("lrnyjeekixtszusrqyzeamknlyjprrwraqskgnjazocbtxzdvjorzch"), string("s"), 63803);
	this->jmsipcxsstzkf(string("voisbvmqmhmvrdqclunltsxjkqyapemwtyzuqyrveoszqzacbabmnibwskavvanoivfakczcwd"), 1077, 2616);
	this->zmspipssdfiuqfteo(5102, false, 5819, 1308, 16766, string("hmsjhbaieouwptpgflvoulimgziggprvqapatymb"), 42597, true);
	this->koplfovnbbojepuoqvlcy(true, 1351, true, 2033, 26709, 3436, 2157);
	this->rrqjojvahu(4697, 46608, 2251, 3041, true, false, 2002, 220, 5928);
	this->gfnkdxwtoppzxvlegtdbdwi();
	this->fcwmlklwiemmejeoqcawk(string("tzmrcayerqeinynxbkvztivctkmnfvragaxspyggjiovpdawhtfsikstjoeun"), 34477, 3869, 7910, string("mrcffesaujrkrnzkzrdtaazgqcuozqbmbdtgsgcywxvauvdizdevirgcfoifdjwqckikzrbtofdttuqkdojpl"), false);
	this->ankrjbmqmnzdwsaz(string("qaydenzoaljojuchfrxnmgrtodtpclbfyynitrzphhxhrsdescljhjimbtkslvduzdrurytdpdkwyfzwjetetsosrffsjj"), string("eagrxifyupmhimusneponlmbjfihhpfhpcrthxdstqzoppnezediexgiqcprilsjdrlfqupuzlmnpdbqnpj"), false, false, 29334, string("mttifijukfjn"));
	this->esnzlgpsulnfughaxhhi(52517, 20151, false, string("yvavjbmeirbffibgswrduylhcvgp"), string("epomzpcmkxylsqcbxgtvvhzocacaeqovvwfwbtzzacqaephfasqbjtjuyjxcclszywihdxuqnjl"), false, 581, false);
	this->rmvzpsftgdqbpgbaolv(513, string("semgypimvlqjwimmdlkyswmmfhrwsfdyagmszcedmvkmtpvtjrkdqimrgskrjbyqdgegumbxysqpeukxm"), 1274, false, 2812, 2113, string("xvgfpyinupqboiwlcwgbzzeznbqjlenclvgaacfvpahlhhii"), false);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class vnhjdab {
public:
	double krlxuoe;
	vnhjdab();
	void jlojanbmgdyazilahzmbgqnxb(string ndxuvopnkja, bool spzzuhg);
	int qamkshssvvnewqk(int ipdvmr, double sxwalabk, double fglzoxsozdiks, string gztfu, double qbdhpgugavsmsgq, bool alckjhtdly, string rfnxtrxrddwns);
	string xgflcmyjuvrlgon(int ylrkuaeihczfcve, double bkwxgziecrbiasb);
	double snbsvaudqkvm(string zcczutwrdxjf, bool qpajhcvxclbm, string hryjaejea, double wirpgqiqae, double gqvgsvlzl, double ajcyjbeuqtxn, double omrhtah, string mrdksfmn, int xconnkwb);

protected:
	string rikzriilx;

	double kurcsfvreuuhprw(double fncchqqyfi, double dlyfz, int xygmhtwltdrtjqq);

private:
	double ywjyp;
	int iftattwoknmavyg;

	int kgrglxdoaibtqixybecjle(bool nszjixk, string ihrin, int qxlyvzww, int peaboo, int kudjtmaz, string tdxtbhra, bool wjecy, bool upplwwyapmpn);
	bool bkcfbnkvyajwuhuil(bool lgjhickzjs, bool hsffrlrlozbe, string theiypeg, int qchvw);
	void gnvyxldkeucf(bool msupxjowgpiwh, bool jbylbcbm, double reyifokra, bool smgffwsbodr, bool cohipczvgqhj, double ccnzcactmtoiphp);

};


int vnhjdab::kgrglxdoaibtqixybecjle(bool nszjixk, string ihrin, int qxlyvzww, int peaboo, int kudjtmaz, string tdxtbhra, bool wjecy, bool upplwwyapmpn) {
	bool sbqfsvlw = true;
	double xalmcjtgf = 18398;
	if (true != true) {
		int fjhazvof;
		for (fjhazvof = 55; fjhazvof > 0; fjhazvof--) {
			continue;
		}
	}
	if (18398 == 18398) {
		int plbvvwycx;
		for (plbvvwycx = 88; plbvvwycx > 0; plbvvwycx--) {
			continue;
		}
	}
	if (18398 == 18398) {
		int zxzeew;
		for (zxzeew = 4; zxzeew > 0; zxzeew--) {
			continue;
		}
	}
	return 54223;
}

bool vnhjdab::bkcfbnkvyajwuhuil(bool lgjhickzjs, bool hsffrlrlozbe, string theiypeg, int qchvw) {
	int hfhqvcncyvdmxhy = 3001;
	double ubgofsehftkgqu = 4626;
	int uwyvabmawrjc = 4836;
	double qjgdvst = 6290;
	string cfeokpufr = "cevbaazyffdraavokekqcrbitefydpujnxxqhthgyydqpbnqhgwwshdnhiocxortefnbgbnkzswkyfeczotrtoxkh";
	bool yszmqc = false;
	if (4836 == 4836) {
		int mgpfe;
		for (mgpfe = 72; mgpfe > 0; mgpfe--) {
			continue;
		}
	}
	if (4626 == 4626) {
		int xgyuzyokp;
		for (xgyuzyokp = 15; xgyuzyokp > 0; xgyuzyokp--) {
			continue;
		}
	}
	return true;
}

void vnhjdab::gnvyxldkeucf(bool msupxjowgpiwh, bool jbylbcbm, double reyifokra, bool smgffwsbodr, bool cohipczvgqhj, double ccnzcactmtoiphp) {
	bool gptouxbkbhsibwb = true;
	string dxrbzpq = "abncuzhitvqcsavuwpyxrejarxhdeumsprkarplgcrkie";
	int dxjqlpfcjjo = 1564;
	bool wiftglhx = true;
	double bwntsrvlopa = 1401;
	bool kxzjkps = false;
	int ncmcozyggbwgviv = 1340;
	string fscquzdqoknv = "xhuiufwjoayqaolbxsfzbbrgsqopqdxelmeydmfemrhlgmwroaoyytreyfhtlkcqdvgvkhripmookxevgxkjmblpvjhyndd";
	int bcckbvq = 3085;
	bool pjhdncenkkqbyao = false;
	if (1564 != 1564) {
		int kcgn;
		for (kcgn = 99; kcgn > 0; kcgn--) {
			continue;
		}
	}
	if (false != false) {
		int ntbtb;
		for (ntbtb = 49; ntbtb > 0; ntbtb--) {
			continue;
		}
	}

}

double vnhjdab::kurcsfvreuuhprw(double fncchqqyfi, double dlyfz, int xygmhtwltdrtjqq) {
	bool tzdyvfxshz = true;
	int jwkqbov = 2110;
	int cietjca = 1315;
	string lcqap = "hpwqhvsnkfcbkipygdgcwmptctjseecodzxxiyrftzkjkmsndsnhcigpjroogzycyzulqqzlkxapx";
	if (string("hpwqhvsnkfcbkipygdgcwmptctjseecodzxxiyrftzkjkmsndsnhcigpjroogzycyzulqqzlkxapx") == string("hpwqhvsnkfcbkipygdgcwmptctjseecodzxxiyrftzkjkmsndsnhcigpjroogzycyzulqqzlkxapx")) {
		int rwdkmzbgqb;
		for (rwdkmzbgqb = 65; rwdkmzbgqb > 0; rwdkmzbgqb--) {
			continue;
		}
	}
	if (true != true) {
		int iuaa;
		for (iuaa = 8; iuaa > 0; iuaa--) {
			continue;
		}
	}
	if (true == true) {
		int rerfqhkeyi;
		for (rerfqhkeyi = 51; rerfqhkeyi > 0; rerfqhkeyi--) {
			continue;
		}
	}
	if (string("hpwqhvsnkfcbkipygdgcwmptctjseecodzxxiyrftzkjkmsndsnhcigpjroogzycyzulqqzlkxapx") != string("hpwqhvsnkfcbkipygdgcwmptctjseecodzxxiyrftzkjkmsndsnhcigpjroogzycyzulqqzlkxapx")) {
		int xqryx;
		for (xqryx = 36; xqryx > 0; xqryx--) {
			continue;
		}
	}
	if (string("hpwqhvsnkfcbkipygdgcwmptctjseecodzxxiyrftzkjkmsndsnhcigpjroogzycyzulqqzlkxapx") == string("hpwqhvsnkfcbkipygdgcwmptctjseecodzxxiyrftzkjkmsndsnhcigpjroogzycyzulqqzlkxapx")) {
		int cslj;
		for (cslj = 96; cslj > 0; cslj--) {
			continue;
		}
	}
	return 12962;
}

void vnhjdab::jlojanbmgdyazilahzmbgqnxb(string ndxuvopnkja, bool spzzuhg) {
	string mxrbbhfjtmnuu = "jtakkouvhdwzmydynimzzmiapawcitilsxbahxswzhdap";
	int zfndvpy = 1167;
	bool ckckmhifvgn = true;
	int ghfbgajhhbjikc = 5696;
	double jemucbyiuarcvub = 23447;
	string dmjyllzzw = "odkuwermusqqptlspftsrvxpdykxz";
	int smfhjhkxfxaegk = 2714;
	bool cdvgqkxoodextm = true;
	if (string("odkuwermusqqptlspftsrvxpdykxz") != string("odkuwermusqqptlspftsrvxpdykxz")) {
		int ugajq;
		for (ugajq = 94; ugajq > 0; ugajq--) {
			continue;
		}
	}
	if (true != true) {
		int ddhn;
		for (ddhn = 68; ddhn > 0; ddhn--) {
			continue;
		}
	}

}

int vnhjdab::qamkshssvvnewqk(int ipdvmr, double sxwalabk, double fglzoxsozdiks, string gztfu, double qbdhpgugavsmsgq, bool alckjhtdly, string rfnxtrxrddwns) {
	string kcmaocxvyfnlrq = "gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj";
	if (string("gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj") == string("gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj")) {
		int rsarjgvk;
		for (rsarjgvk = 82; rsarjgvk > 0; rsarjgvk--) {
			continue;
		}
	}
	if (string("gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj") != string("gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj")) {
		int gruhmlvh;
		for (gruhmlvh = 83; gruhmlvh > 0; gruhmlvh--) {
			continue;
		}
	}
	if (string("gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj") == string("gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj")) {
		int spelvyqk;
		for (spelvyqk = 25; spelvyqk > 0; spelvyqk--) {
			continue;
		}
	}
	if (string("gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj") == string("gxrkxsawmnkzrdczneohnoxzpmacjfrrvspxpevzdtioknlcgqj")) {
		int lbejgzkbrd;
		for (lbejgzkbrd = 51; lbejgzkbrd > 0; lbejgzkbrd--) {
			continue;
		}
	}
	return 56537;
}

string vnhjdab::xgflcmyjuvrlgon(int ylrkuaeihczfcve, double bkwxgziecrbiasb) {
	string gypxfygwtr = "feognddhnyxajbnlrtlmhscjiwapubqaeislrzyyulsmlllneuhtbdmetweuzlatr";
	double ohpjqwaop = 2401;
	string odfztocdikfnc = "kvzaewvlcqzckcprheznqmhxqucaagbnbyqlltsekeiubwrvk";
	string ffkyqes = "cgthgbjsojirhnqamaknyticvjglyivcdevqwagwvobiqtrrluxelrbsnrnogxkxvvamhtsnlxrcygwvltqdcxhfv";
	string dovlielpd = "gzstvkamqoqlmadvggdndqadrfkqrrmcp";
	return string("kirxlpwhyhqwi");
}

double vnhjdab::snbsvaudqkvm(string zcczutwrdxjf, bool qpajhcvxclbm, string hryjaejea, double wirpgqiqae, double gqvgsvlzl, double ajcyjbeuqtxn, double omrhtah, string mrdksfmn, int xconnkwb) {
	bool nhmrpashkxjmr = false;
	bool gtyyltnja = true;
	int cmedtb = 6124;
	string ajbdp = "tqghlsfpxfvokgxqjrhwstqqwqsiecovxngbgjusaacycnfzjxdpgbdwfffqdvzmhezofsxythdojsispiquazehmjwrkqfrajbx";
	string lhjgipwaykbial = "zvdahihkqbobdnhvrgzmbrsxgkehygekevtfjcxasjurjtbhhxzkeqosqrguuyabmrutnipkkuufyipduevfgbuaajmtmcvozoc";
	string qmpjwdshh = "tloplvnnaldhpdxfeeqj";
	bool kmeaxne = false;
	return 13800;
}

vnhjdab::vnhjdab() {
	this->jlojanbmgdyazilahzmbgqnxb(string("uzwnhjlr"), true);
	this->qamkshssvvnewqk(1887, 19, 2487, string("ialqpavwqjtlxlpwarrykrnxgsyskboubpnfyafgydkimeblgsuqgpuvhxigowmqmozprkdcjijpivxuoz"), 16430, true, string("bosqsxcseoetregvcxtubsglghmhwvlmxmbrcoqrskmljwwevuppgjalerpktwwnmriejctvzvsjgvvwxbwfylzjmkdgahnlvhaa"));
	this->xgflcmyjuvrlgon(3259, 17248);
	this->snbsvaudqkvm(string("vppsrvdbbwwhpok"), true, string("hykedebpzehx"), 10482, 56834, 22745, 40735, string("jhduwygwltphptjhgshgqpkmzqybajrbwjybilacsbdkniszoawylqinurkhhzosdnfruaff"), 8024);
	this->kurcsfvreuuhprw(28991, 6531, 1016);
	this->kgrglxdoaibtqixybecjle(true, string("fmeyefcfpvwilbihzwmtxxeizlnravaascgrqkdzdwdeix"), 1611, 379, 72, string("iwjguspyyrrroqywsugirhvdrkfinfrzvjddlfbwp"), true, true);
	this->bkcfbnkvyajwuhuil(false, true, string("fkicwevnpsaxbmyguppjhybryhjbuwhfhcrcosiwawxjlmservazgkseisguyelxqnmrkgzlsuanurkmxjgez"), 172);
	this->gnvyxldkeucf(false, true, 7701, true, true, 15349);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class xtvazzk {
public:
	bool iiypncfrxkurhxa;
	double lyzfuvdlurcur;
	xtvazzk();
	int rnvhfeplwzwaabgcyf(string xjeqbvvxjtcq, string pfcfmu, string rqoqhjapif, string jqawbsvzbiuaim, int sozoshwvic, bool awlqgrpssy, int dtwzgmtpsq, double ditsrqjfwusraf);
	void gkoayetcrpy(bool rigqascihjh);

protected:
	string ltprefqkhgqx;
	string dsxmtgpnl;
	double ufxklxyjfnzjin;
	bool zgpncl;

	int ciuswslmqkkug(int etgmulbintw, bool oecdbtua, bool xvrvjeqy, string vssuwjo, int jjnhexpfnn, int xovxsnzhlc);
	int ekvyorvjjvammq(int kzkctyohwqjrv, int kzurhmctayymoq, bool kbgbvbfjzfytz, double bmlaxvurf, int luaqs, double ppmfiqusicg, bool zxsga);
	int kwnhegdhopqzxqwjexqwcrhts();
	int orlpupexnyujowempfy(bool cndwzzbmvpa, string htrmn, bool metknnoxteuvz, string moyoahsne, double vqkvdqeecvz, bool jbehjgh, int okicqgzmpzdxa);
	bool bglsbyassvwgccjyyskp(double hsnggus, string kvyybpenbbk, string feqzo, string lpdbbwlrb, bool ldzazkuwbpd, double juoalao);
	void ijulyicezrxnkvhdzwaxxz(int waomvdhdylwjl, int jbloeylmvygtg, int eeqqhlojzsotc, double wcctdqcxbwuuu);
	double gvqosrbxstnoxkondbpmz(int tamrgeiuvxwxgqj, bool vxrepabiuncn, bool nviuhboshqnrr);
	double uixivswsilxomupvzsbgo(int bhwmpasgdlvnnoq, bool zdzqkgillorl, bool auhydaoctoelym, int uxyrozmgjv, string lkkbrzukte);

private:
	bool xayovusxepllfx;
	double zpehia;
	int jcniwkkig;
	string xbtpxpe;
	bool lwdpwnla;

	double pmcttnwiwhlfejrkiinsst(bool evmnuedimz, string urrziuchoplj, string yabwgqoydnor, string irmduz);
	void tskzxjkyasapl(double tjunmcgszgo, bool kvxsycfp, string niapbpdfgdc, int ncksfsvkvax, double vjvjnbqejitf, double bzhmjjstl, int dnukujiusyfgc, int pcxfn, bool aolce);
	void litipxybpiewpn(string frdpkpadhecggar);
	bool xymccclsdcsbea(string afdmglsu);
	int krdxetxzhysnojzp(int lptqmfvkylnlg, string lzuncknnd, int toabrdqaqnv);
	bool tftfoqndbyqaazyjpprn(bool fxhyzigmpvz, int ycksj, int olskgegk, string jclxbpqds, bool ccbepyoswoihxlz, int jkbltkzkmbucw, string yyckyjpvxrncyl);
	string yjhtbuhpvkqdqiuf(double uaelxhhjchv);
	double tkrdqcnnrgedunvtfbuiivlz(double lnletpfj, int vjxlmggyyxjnbz, bool vtmxdp, int hgfrxtlmsf, double vnflpc, string olkjmr, double jwxbhehbccuzz, bool gouxcmnlrpmv, string zdnlspxdqly);
	bool gmnwnugczbtthj(bool ckewepgrdhvox);

};


double xtvazzk::pmcttnwiwhlfejrkiinsst(bool evmnuedimz, string urrziuchoplj, string yabwgqoydnor, string irmduz) {
	int omvtzzkkmvxicv = 1477;
	if (1477 == 1477) {
		int uazt;
		for (uazt = 67; uazt > 0; uazt--) {
			continue;
		}
	}
	if (1477 != 1477) {
		int ntl;
		for (ntl = 49; ntl > 0; ntl--) {
			continue;
		}
	}
	return 44517;
}

void xtvazzk::tskzxjkyasapl(double tjunmcgszgo, bool kvxsycfp, string niapbpdfgdc, int ncksfsvkvax, double vjvjnbqejitf, double bzhmjjstl, int dnukujiusyfgc, int pcxfn, bool aolce) {
	double ohfubyelber = 2713;

}

void xtvazzk::litipxybpiewpn(string frdpkpadhecggar) {
	double llkxtymaaxlvmdt = 41583;
	if (41583 != 41583) {
		int jnchqfjxg;
		for (jnchqfjxg = 74; jnchqfjxg > 0; jnchqfjxg--) {
			continue;
		}
	}
	if (41583 != 41583) {
		int ysmfiwcnj;
		for (ysmfiwcnj = 32; ysmfiwcnj > 0; ysmfiwcnj--) {
			continue;
		}
	}

}

bool xtvazzk::xymccclsdcsbea(string afdmglsu) {
	return false;
}

int xtvazzk::krdxetxzhysnojzp(int lptqmfvkylnlg, string lzuncknnd, int toabrdqaqnv) {
	double gmcwymhzmps = 61764;
	string czdvg = "hmkcxwldpaujayfjfydnrbpmkrlvmmvalgceccpzznhfriissssgiien";
	int xzugjoobqljfv = 7206;
	double cayrakhwpx = 39788;
	double odyavhjf = 38340;
	bool upbeijkbjrjc = true;
	string gighpuirzlhna = "zjfoitdtwjybhdnlhsbulpkivilhgr";
	int bztbafgizoalsxs = 735;
	if (61764 == 61764) {
		int lvhzqc;
		for (lvhzqc = 99; lvhzqc > 0; lvhzqc--) {
			continue;
		}
	}
	if (7206 == 7206) {
		int mqlre;
		for (mqlre = 60; mqlre > 0; mqlre--) {
			continue;
		}
	}
	if (true != true) {
		int ga;
		for (ga = 42; ga > 0; ga--) {
			continue;
		}
	}
	return 60499;
}

bool xtvazzk::tftfoqndbyqaazyjpprn(bool fxhyzigmpvz, int ycksj, int olskgegk, string jclxbpqds, bool ccbepyoswoihxlz, int jkbltkzkmbucw, string yyckyjpvxrncyl) {
	return true;
}

string xtvazzk::yjhtbuhpvkqdqiuf(double uaelxhhjchv) {
	bool wgxbpsshouauesb = true;
	bool lsypwghkijywxd = true;
	bool nzepcynbvu = true;
	bool xbeto = false;
	if (false == false) {
		int xxkr;
		for (xxkr = 18; xxkr > 0; xxkr--) {
			continue;
		}
	}
	if (true != true) {
		int lnlqohnzu;
		for (lnlqohnzu = 12; lnlqohnzu > 0; lnlqohnzu--) {
			continue;
		}
	}
	if (true != true) {
		int rbfie;
		for (rbfie = 97; rbfie > 0; rbfie--) {
			continue;
		}
	}
	if (true != true) {
		int lcj;
		for (lcj = 87; lcj > 0; lcj--) {
			continue;
		}
	}
	return string("lv");
}

double xtvazzk::tkrdqcnnrgedunvtfbuiivlz(double lnletpfj, int vjxlmggyyxjnbz, bool vtmxdp, int hgfrxtlmsf, double vnflpc, string olkjmr, double jwxbhehbccuzz, bool gouxcmnlrpmv, string zdnlspxdqly) {
	double xnfdyjgdzljy = 53567;
	bool sdqrtl = false;
	double ecoyhyzwsl = 12708;
	if (false == false) {
		int tvoyifwby;
		for (tvoyifwby = 42; tvoyifwby > 0; tvoyifwby--) {
			continue;
		}
	}
	if (12708 != 12708) {
		int allfis;
		for (allfis = 33; allfis > 0; allfis--) {
			continue;
		}
	}
	if (false != false) {
		int zjlcgfhcaw;
		for (zjlcgfhcaw = 88; zjlcgfhcaw > 0; zjlcgfhcaw--) {
			continue;
		}
	}
	if (false != false) {
		int serthzrjzz;
		for (serthzrjzz = 66; serthzrjzz > 0; serthzrjzz--) {
			continue;
		}
	}
	return 27540;
}

bool xtvazzk::gmnwnugczbtthj(bool ckewepgrdhvox) {
	double mqktonjwcn = 22077;
	double prazlcewc = 44543;
	int fupvbgxxwqf = 70;
	string gdxopdosziwcvxc = "hkveknsxtrzyypauulxodtlyxwlscmidbvbdftdkzvdzqnuprbhrzzepgugjufxmnehumxtp";
	string ltkbuchwofzt = "yeyzbjqzuvxmrdjaqr";
	int yskbottymrwdsv = 1900;
	if (string("yeyzbjqzuvxmrdjaqr") != string("yeyzbjqzuvxmrdjaqr")) {
		int uhxpnm;
		for (uhxpnm = 90; uhxpnm > 0; uhxpnm--) {
			continue;
		}
	}
	if (1900 == 1900) {
		int qjypkqfyt;
		for (qjypkqfyt = 58; qjypkqfyt > 0; qjypkqfyt--) {
			continue;
		}
	}
	if (1900 == 1900) {
		int cdesj;
		for (cdesj = 33; cdesj > 0; cdesj--) {
			continue;
		}
	}
	if (44543 == 44543) {
		int yjxkc;
		for (yjxkc = 58; yjxkc > 0; yjxkc--) {
			continue;
		}
	}
	if (string("hkveknsxtrzyypauulxodtlyxwlscmidbvbdftdkzvdzqnuprbhrzzepgugjufxmnehumxtp") != string("hkveknsxtrzyypauulxodtlyxwlscmidbvbdftdkzvdzqnuprbhrzzepgugjufxmnehumxtp")) {
		int gy;
		for (gy = 44; gy > 0; gy--) {
			continue;
		}
	}
	return false;
}

int xtvazzk::ciuswslmqkkug(int etgmulbintw, bool oecdbtua, bool xvrvjeqy, string vssuwjo, int jjnhexpfnn, int xovxsnzhlc) {
	double sgrdlgyegfmngff = 5710;
	double sywcpexdj = 23070;
	bool yzbxtix = false;
	int oyknyggyxoolskz = 2984;
	double asohepg = 38899;
	string ucbtjuibzzxsqvd = "xohdpscldnysplxrqtuflmipxtrddbfcanyfmrnoabdubqoksumuxrltornqjqwzzzje";
	bool aqshfwnbskx = false;
	bool kclkryayfrx = false;
	int goquka = 4846;
	int niumqbw = 662;
	if (false != false) {
		int worb;
		for (worb = 52; worb > 0; worb--) {
			continue;
		}
	}
	if (23070 != 23070) {
		int hf;
		for (hf = 100; hf > 0; hf--) {
			continue;
		}
	}
	if (false == false) {
		int gu;
		for (gu = 16; gu > 0; gu--) {
			continue;
		}
	}
	if (5710 != 5710) {
		int qyuleqft;
		for (qyuleqft = 60; qyuleqft > 0; qyuleqft--) {
			continue;
		}
	}
	return 9847;
}

int xtvazzk::ekvyorvjjvammq(int kzkctyohwqjrv, int kzurhmctayymoq, bool kbgbvbfjzfytz, double bmlaxvurf, int luaqs, double ppmfiqusicg, bool zxsga) {
	string rfkuxghemzhtaeo = "jdqlagxrxkipqrkeioupxomsejvmxhiptvsxvbvrlqudsjolhzqpeabrslthsgpttmbmwmwqrfowtl";
	string ljmio = "rfstbtwfbmjjdjfewsqjqkhbkgnnouoqwjryokuflnqclbzsebf";
	bool dhrtlo = true;
	int prnpcsxqdrl = 887;
	int nbvzqdga = 774;
	if (true != true) {
		int ru;
		for (ru = 6; ru > 0; ru--) {
			continue;
		}
	}
	if (774 != 774) {
		int ei;
		for (ei = 44; ei > 0; ei--) {
			continue;
		}
	}
	if (string("jdqlagxrxkipqrkeioupxomsejvmxhiptvsxvbvrlqudsjolhzqpeabrslthsgpttmbmwmwqrfowtl") == string("jdqlagxrxkipqrkeioupxomsejvmxhiptvsxvbvrlqudsjolhzqpeabrslthsgpttmbmwmwqrfowtl")) {
		int xigdamkuhp;
		for (xigdamkuhp = 2; xigdamkuhp > 0; xigdamkuhp--) {
			continue;
		}
	}
	if (string("jdqlagxrxkipqrkeioupxomsejvmxhiptvsxvbvrlqudsjolhzqpeabrslthsgpttmbmwmwqrfowtl") != string("jdqlagxrxkipqrkeioupxomsejvmxhiptvsxvbvrlqudsjolhzqpeabrslthsgpttmbmwmwqrfowtl")) {
		int cqziz;
		for (cqziz = 35; cqziz > 0; cqziz--) {
			continue;
		}
	}
	if (true != true) {
		int cbfqlzmt;
		for (cbfqlzmt = 96; cbfqlzmt > 0; cbfqlzmt--) {
			continue;
		}
	}
	return 70441;
}

int xtvazzk::kwnhegdhopqzxqwjexqwcrhts() {
	int scmrnpp = 775;
	string vxcfmcfdw = "vlqznjtwvascey";
	bool faakmhf = true;
	string pnpurjar = "pbmbx";
	double ciylqanqcercrh = 27468;
	double uatjusqmaszk = 48819;
	bool wmoqnl = false;
	bool bkushw = false;
	if (false == false) {
		int et;
		for (et = 52; et > 0; et--) {
			continue;
		}
	}
	if (48819 != 48819) {
		int hokqw;
		for (hokqw = 30; hokqw > 0; hokqw--) {
			continue;
		}
	}
	return 36867;
}

int xtvazzk::orlpupexnyujowempfy(bool cndwzzbmvpa, string htrmn, bool metknnoxteuvz, string moyoahsne, double vqkvdqeecvz, bool jbehjgh, int okicqgzmpzdxa) {
	bool bzqtmficywvos = false;
	double bddqgycyt = 16731;
	if (16731 == 16731) {
		int jcx;
		for (jcx = 64; jcx > 0; jcx--) {
			continue;
		}
	}
	return 66870;
}

bool xtvazzk::bglsbyassvwgccjyyskp(double hsnggus, string kvyybpenbbk, string feqzo, string lpdbbwlrb, bool ldzazkuwbpd, double juoalao) {
	bool uuzjwqyfapextp = false;
	if (false != false) {
		int yuapioy;
		for (yuapioy = 97; yuapioy > 0; yuapioy--) {
			continue;
		}
	}
	if (false == false) {
		int glqd;
		for (glqd = 81; glqd > 0; glqd--) {
			continue;
		}
	}
	if (false != false) {
		int yh;
		for (yh = 69; yh > 0; yh--) {
			continue;
		}
	}
	if (false != false) {
		int rqqj;
		for (rqqj = 57; rqqj > 0; rqqj--) {
			continue;
		}
	}
	if (false == false) {
		int doqcle;
		for (doqcle = 66; doqcle > 0; doqcle--) {
			continue;
		}
	}
	return true;
}

void xtvazzk::ijulyicezrxnkvhdzwaxxz(int waomvdhdylwjl, int jbloeylmvygtg, int eeqqhlojzsotc, double wcctdqcxbwuuu) {
	double ysztmgfbhiejc = 23492;
	int yyaywnykuh = 468;
	double jyangadgvgxjea = 22794;
	double ecxhepmmlje = 9126;

}

double xtvazzk::gvqosrbxstnoxkondbpmz(int tamrgeiuvxwxgqj, bool vxrepabiuncn, bool nviuhboshqnrr) {
	double dlsnnqtdoiofxd = 84282;
	bool bovlz = true;
	string ocxiel = "fsqaohintspnxlykrls";
	double yzwpunpczhdf = 23986;
	int dwrzgqpigairol = 7115;
	int nhjhlkdajursxju = 2816;
	int ullockztxkanm = 8153;
	if (true == true) {
		int iulkdq;
		for (iulkdq = 35; iulkdq > 0; iulkdq--) {
			continue;
		}
	}
	if (84282 == 84282) {
		int gnker;
		for (gnker = 26; gnker > 0; gnker--) {
			continue;
		}
	}
	return 17737;
}

double xtvazzk::uixivswsilxomupvzsbgo(int bhwmpasgdlvnnoq, bool zdzqkgillorl, bool auhydaoctoelym, int uxyrozmgjv, string lkkbrzukte) {
	double jqynngfogi = 53810;
	double jybaosepi = 7443;
	string obfyd = "sbmdcdcsrmdcyveotjgziejftogbcfzdkpjnihiilgimvzuikjsdnurtjrjwxqgvdhpysoyyzbbvcpcixvpibfkyfgqwbwvheu";
	if (53810 != 53810) {
		int ycqhteiwf;
		for (ycqhteiwf = 88; ycqhteiwf > 0; ycqhteiwf--) {
			continue;
		}
	}
	if (string("sbmdcdcsrmdcyveotjgziejftogbcfzdkpjnihiilgimvzuikjsdnurtjrjwxqgvdhpysoyyzbbvcpcixvpibfkyfgqwbwvheu") != string("sbmdcdcsrmdcyveotjgziejftogbcfzdkpjnihiilgimvzuikjsdnurtjrjwxqgvdhpysoyyzbbvcpcixvpibfkyfgqwbwvheu")) {
		int hjebhr;
		for (hjebhr = 93; hjebhr > 0; hjebhr--) {
			continue;
		}
	}
	if (string("sbmdcdcsrmdcyveotjgziejftogbcfzdkpjnihiilgimvzuikjsdnurtjrjwxqgvdhpysoyyzbbvcpcixvpibfkyfgqwbwvheu") != string("sbmdcdcsrmdcyveotjgziejftogbcfzdkpjnihiilgimvzuikjsdnurtjrjwxqgvdhpysoyyzbbvcpcixvpibfkyfgqwbwvheu")) {
		int kf;
		for (kf = 39; kf > 0; kf--) {
			continue;
		}
	}
	return 97821;
}

int xtvazzk::rnvhfeplwzwaabgcyf(string xjeqbvvxjtcq, string pfcfmu, string rqoqhjapif, string jqawbsvzbiuaim, int sozoshwvic, bool awlqgrpssy, int dtwzgmtpsq, double ditsrqjfwusraf) {
	int dakcuvscptgjwk = 6084;
	int kgqgmbtq = 987;
	bool yyvlm = true;
	int cazucfjupelbyjh = 1335;
	bool qmhrxf = false;
	double mamklsffysxs = 18701;
	string nefcnh = "sxrmhaaalivrscmmqburbdgkvtbncbffeauqnbgtqsqyikjyiudzacshfqtkqqtre";
	if (6084 != 6084) {
		int ox;
		for (ox = 43; ox > 0; ox--) {
			continue;
		}
	}
	if (987 == 987) {
		int hfex;
		for (hfex = 0; hfex > 0; hfex--) {
			continue;
		}
	}
	if (6084 == 6084) {
		int efkqcx;
		for (efkqcx = 30; efkqcx > 0; efkqcx--) {
			continue;
		}
	}
	if (string("sxrmhaaalivrscmmqburbdgkvtbncbffeauqnbgtqsqyikjyiudzacshfqtkqqtre") != string("sxrmhaaalivrscmmqburbdgkvtbncbffeauqnbgtqsqyikjyiudzacshfqtkqqtre")) {
		int grvsarmawg;
		for (grvsarmawg = 46; grvsarmawg > 0; grvsarmawg--) {
			continue;
		}
	}
	return 93145;
}

void xtvazzk::gkoayetcrpy(bool rigqascihjh) {
	int dkhpnduseiwpkb = 8361;
	string nyxietzcsryam = "vtnpswfkhfpulqxovdujhavprszvcaouabheckuazoyxsbcssgjhbhpapscgjjxou";
	bool ftiacvfuuujfy = true;
	bool jdjuml = true;
	bool dcaajkpsrfyfyb = false;
	double mszmlnpbfhj = 12067;
	string xmxgizkjgx = "vmgppephahdupcknwhhhcfpkkiwylchyohqhcftdigrdhsmpjiykiqbiegckfqxgeceemojnhlppgsnvmctbparkmvtxagonogwl";
	if (true == true) {
		int kiw;
		for (kiw = 8; kiw > 0; kiw--) {
			continue;
		}
	}
	if (12067 != 12067) {
		int reja;
		for (reja = 15; reja > 0; reja--) {
			continue;
		}
	}
	if (string("vtnpswfkhfpulqxovdujhavprszvcaouabheckuazoyxsbcssgjhbhpapscgjjxou") == string("vtnpswfkhfpulqxovdujhavprszvcaouabheckuazoyxsbcssgjhbhpapscgjjxou")) {
		int zbh;
		for (zbh = 43; zbh > 0; zbh--) {
			continue;
		}
	}
	if (8361 != 8361) {
		int whx;
		for (whx = 24; whx > 0; whx--) {
			continue;
		}
	}

}

xtvazzk::xtvazzk() {
	this->rnvhfeplwzwaabgcyf(string("acqhaevgdikbmamvsqegqktykfegksauthzdiy"), string("ljqxduksebtetudiycjwqlbovrfhmbddxfyqeffyigtucnmructanxpcazbcjnrwceitxixj"), string("eovmrfelahzehbfgdqypfhjeqyuvguvwhydtkgxdguhoaveejololndttepkbbewehgiloixfcj"), string("zfevtdbjfzrflcvsrkjoedgqkrhxropsjnxakfwjjydnvtfzbwnknutetkrkacny"), 4018, false, 4269, 55848);
	this->gkoayetcrpy(false);
	this->ciuswslmqkkug(4191, true, false, string("uzfdafunyanqu"), 2582, 1824);
	this->ekvyorvjjvammq(3118, 7043, true, 19591, 2678, 45930, true);
	this->kwnhegdhopqzxqwjexqwcrhts();
	this->orlpupexnyujowempfy(false, string("jgqabilfeeuszfgegmtikqirtcyvputtlrazmfucpkosodvcacujauqxtgsbcuqocdxqwfjllsqgtpgmrmafgstsmuwdkeqojvz"), false, string("oksilugmvwkjnzxtppnvnvougmtvhwjnczmclrhfxmviqzfkhfhjmmcqmxyjgzgoameabwddfojvlvojbafudeqdglbwcxgbc"), 13897, true, 7232);
	this->bglsbyassvwgccjyyskp(22092, string("rhqixpmeoxurwfvmzks"), string("ufwxcybtuecxecdu"), string("lhewylnwrepgwmigdfsbxnddeajidvevdvjjzsupwyzlqmmlfckmoodqcihbdzxojldmxphhcjypgvkke"), false, 19608);
	this->ijulyicezrxnkvhdzwaxxz(1218, 338, 433, 895);
	this->gvqosrbxstnoxkondbpmz(5702, true, false);
	this->uixivswsilxomupvzsbgo(5192, true, false, 925, string("ujkqhaoxhtthmtsonkfslcnattbaaxegodngtmrfpzufzedarkxlvofegzbeabfmmqlti"));
	this->pmcttnwiwhlfejrkiinsst(false, string("qljrrgwensdpbxalukhmmderzucbtemrcfckxhlgdpxlwufekcmydggantbaizwmvymbkhzvzumuldbkiztnmq"), string("rvvvrxywjxqtyyoeiotwwbjqyymoxfcxfztpthiojeuafzqriqzvlckdlcaqtjmzsprf"), string("rtxidbhtkhrtmapoqwyyghbdpdnlhmxxpmlwwgdrmtgrqdrtltgrumwqkhtgmewbmejnendbrjmlibdmpih"));
	this->tskzxjkyasapl(14663, true, string("eiauzorckeyezgniumjiopcqkdpwxyxbeuvpxgknfucghqfyodvtjemumllgyqbkkvetwisarrxb"), 2254, 66044, 3198, 1200, 2606, true);
	this->litipxybpiewpn(string("bxkrnlyvtitzpcfyaugdgdatiutohlfqfoau"));
	this->xymccclsdcsbea(string("egltfwmkdv"));
	this->krdxetxzhysnojzp(1038, string("mgmwxgogngdipehyrfukbqsecjgnsqzpohytcrzwilsegbkrcmxoxkiwzwvxjqlrcarlglsyrcayjgtrquibsbijxdbanazx"), 1848);
	this->tftfoqndbyqaazyjpprn(true, 6573, 2118, string("ujoqazirffnpcvqegrkiblzpjrctqdblhcckgwymhvuxgbknhmossitkdf"), true, 129, string("frhbjwfpejuavoqmmdzllnkcgsjjsayfsqisvavgasexemgrzqglmmxowspgxqmuawdpxuklvspfmuoaekjdimaadezueq"));
	this->yjhtbuhpvkqdqiuf(25031);
	this->tkrdqcnnrgedunvtfbuiivlz(37913, 3045, true, 3792, 15575, string("soktorinpzcqpjeexhmcqpkiarpgllzlwukt"), 24710, false, string("amemtitwppjrclwvdchwdbwcefjwrakrgfmfknuwzqhlibgmdehdee"));
	this->gmnwnugczbtthj(false);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class qmjwycm {
public:
	int bemcosr;
	int mykpdetragv;
	double uqchkzj;
	qmjwycm();
	string fiwipsxbjzynfghpjdt(int meixffyqzqhd, bool qmzimkmgh, string hexnqp);
	void vlxetgphqyhspyybfuhw(string nyalmqronegdv, int mvmyirkgs);
	string vehbsoxanbbczry(int mttedrreszlby);

protected:
	double qphzjwy;
	string tzdldkfpnzffp;
	double lgxarwzpod;
	int jvmiuoq;

	double unvskpjxqxybkfhrsycmuofm();
	void empkzgguxyxmgcrtalehhee(string svsuesyvtdiaj, string xlpzxhrzvanrztn);
	int fzwgxevidsbtatswulmyoslg(bool ddhxtnidgrgtoov, int imergqzestz, int epkpyvefqbffyme, double plvplgknsctt);
	string frumuclfoyvwwxg(bool gapgladaa, double ofikxkub, string qrtrzjtpjzodlr, double kltvyvrsumxbz, int ewbwu);
	string nlnjzlumheiunbpvdq(int cdpsue, double ucmuxkjmedax, string zivtpqzuj, int azptssqdcdfqcx, string jiryiclpbtjymk, bool pwbxmbzdoksr, string znjhsxc, bool bsivwtl, int xzwhxsaprtsw, string kickwg);
	int zhootrlqdhywucgbjmwgss(string weiokh, bool hyxnh, bool ivdlbxehgnkyrbz, bool okgqqlicoid, bool nawzzb, bool gyywy, bool zdaolh, double wizesiulgmjwr, bool pgukjhpv);
	string uyxqiczpzvepsyxsfckns(bool rcrsslrjmqptupo, bool mvrbvx, int srbennrer, double edmsdgcjwyvnm, double nzbtw, bool sqqtn, bool lwnfmzlsdxp, string jbsnejikhsokl, string gjvfevwxavz, string pptukjgh);
	int cqkqjbqjcqtcefrlwi(string julxiznk, int djsznwonkbe);
	string xraihgwkgesgo(string ysglqllus, double fnjtvcwhtk, int gjepyimgdqnlp, double jnvxvufutcuwbem, int tbwxkltx);
	double nsjfhepguhfkugblhh(string njatppb, double tegar, string anbqeve, int wwlsztr, double erfvubrnaauix, string hxmqptozwkf, string gwuytjlvesuivh);

private:
	double thcear;
	bool xkhaspfeqgsr;
	double hwajymh;

	bool hzicqfkmwd(string tjemlilud, double fokjysbc, double txklrayzpeacber, string kzhtoaty, bool jcjvmtvmzrbgz);
	bool gguudcmmxn(string lbhzupysrcxosel, string zznqmm);
	void djtuztxmrumw(bool lyqnddu);
	int urwkjnqfpoavedx(int dvftrvc, double hcjvsuiaenoggy, int xkqkcyqeqpshnhc, int ssqumyabwbxmrd, string akedhtuo);
	int vhlbaghopoehzehikjxqn(double sbskzhvczoecuc, bool kvvlelxxx, bool dkmewgozhbzcxqe, double cipxpxouzkgb);
	double zbmaosllqrplqmlddja(bool ekgzpambmmndvh, bool aclnyxvcbl, double jkkhowxg, double tcnmq);
	double nshyczpywspxtrgwcvefzk(string scvowx, int jtrgg, double wnjbdcgtsxlzxj, double akjxeqxwlwe, bool dvatk, bool fbhag, bool nfvycmhpqnvvp, double jxbyszfzxhp, bool lpbpnkrryuxxzf, string zjtqayjvgzcnpko);
	string bisgjdvasbiriykm(int goatv, double krllbhnvfs, double txsmsqsjszmlsgu);
	void zawrfpgwfpcfwbvh(bool hqkqmqzdhm, string hgjqqdtzskmdz, double ifjykpxamu, double jmzirmeyz, string cedqmjtyhiyevom, int iklprcovaocvsoc);
	double myvuolpxkrxxbdoqbmepykbo(int aggrzlocmkjix);

};


bool qmjwycm::hzicqfkmwd(string tjemlilud, double fokjysbc, double txklrayzpeacber, string kzhtoaty, bool jcjvmtvmzrbgz) {
	bool gdkogjlvzrrrx = false;
	double jzsnsecu = 30833;
	int ljxiijx = 1202;
	double xceaucppmrowkvt = 10445;
	return false;
}

bool qmjwycm::gguudcmmxn(string lbhzupysrcxosel, string zznqmm) {
	string fifppzde = "xlzzsvtvpvglelcrelyvp";
	int jlisfov = 6457;
	int vuhzbtvi = 533;
	return true;
}

void qmjwycm::djtuztxmrumw(bool lyqnddu) {
	bool sxzhiexzjlklr = true;
	double vwtyourwiywr = 37958;
	double tsuuxoffc = 13207;
	bool gobon = true;
	double kpvjlzmhapla = 82789;
	if (true != true) {
		int tr;
		for (tr = 70; tr > 0; tr--) {
			continue;
		}
	}
	if (true != true) {
		int kzrrdktp;
		for (kzrrdktp = 68; kzrrdktp > 0; kzrrdktp--) {
			continue;
		}
	}
	if (true == true) {
		int aifgmxank;
		for (aifgmxank = 28; aifgmxank > 0; aifgmxank--) {
			continue;
		}
	}
	if (82789 != 82789) {
		int wbr;
		for (wbr = 69; wbr > 0; wbr--) {
			continue;
		}
	}
	if (13207 != 13207) {
		int aciuwq;
		for (aciuwq = 4; aciuwq > 0; aciuwq--) {
			continue;
		}
	}

}

int qmjwycm::urwkjnqfpoavedx(int dvftrvc, double hcjvsuiaenoggy, int xkqkcyqeqpshnhc, int ssqumyabwbxmrd, string akedhtuo) {
	bool akjavbet = false;
	int qemmyaxmwlzo = 5961;
	if (false != false) {
		int zne;
		for (zne = 84; zne > 0; zne--) {
			continue;
		}
	}
	return 98692;
}

int qmjwycm::vhlbaghopoehzehikjxqn(double sbskzhvczoecuc, bool kvvlelxxx, bool dkmewgozhbzcxqe, double cipxpxouzkgb) {
	int irooanuxgzbzu = 2522;
	double kqdqfghpxmcnx = 28196;
	string ycozd = "sxboebxdcddosqwcovdvlvdxtckahmtjgvhfsrlsebdqdtxcpihiufybowulylxxrdxevddhnrjrxzesejofsmxsxxiim";
	bool hhtlafxeidpysza = true;
	if (true != true) {
		int pc;
		for (pc = 11; pc > 0; pc--) {
			continue;
		}
	}
	if (true == true) {
		int tkig;
		for (tkig = 4; tkig > 0; tkig--) {
			continue;
		}
	}
	if (string("sxboebxdcddosqwcovdvlvdxtckahmtjgvhfsrlsebdqdtxcpihiufybowulylxxrdxevddhnrjrxzesejofsmxsxxiim") != string("sxboebxdcddosqwcovdvlvdxtckahmtjgvhfsrlsebdqdtxcpihiufybowulylxxrdxevddhnrjrxzesejofsmxsxxiim")) {
		int rkdytwo;
		for (rkdytwo = 75; rkdytwo > 0; rkdytwo--) {
			continue;
		}
	}
	if (string("sxboebxdcddosqwcovdvlvdxtckahmtjgvhfsrlsebdqdtxcpihiufybowulylxxrdxevddhnrjrxzesejofsmxsxxiim") == string("sxboebxdcddosqwcovdvlvdxtckahmtjgvhfsrlsebdqdtxcpihiufybowulylxxrdxevddhnrjrxzesejofsmxsxxiim")) {
		int bmstjwfe;
		for (bmstjwfe = 11; bmstjwfe > 0; bmstjwfe--) {
			continue;
		}
	}
	return 1975;
}

double qmjwycm::zbmaosllqrplqmlddja(bool ekgzpambmmndvh, bool aclnyxvcbl, double jkkhowxg, double tcnmq) {
	return 40607;
}

double qmjwycm::nshyczpywspxtrgwcvefzk(string scvowx, int jtrgg, double wnjbdcgtsxlzxj, double akjxeqxwlwe, bool dvatk, bool fbhag, bool nfvycmhpqnvvp, double jxbyszfzxhp, bool lpbpnkrryuxxzf, string zjtqayjvgzcnpko) {
	bool mqimtfizcjimq = false;
	string spajkjo = "tysntxcfedpsdakyfpgnnyhmqetqqeuzckympdgwcoaysdsrwrgndjyhaodkxnimsuehkbhffagmabzubot";
	double rubjiplyelvz = 16163;
	bool xynibadjqhyughl = true;
	string rmdpjqwxdjbtxkv = "hpsesjtsyqjdjrhsuxehvqzqtytnlydbjpgjlqgpribprytybdlqkdtunfldspluvujsduokgysrvbvibtywovmykuuuwmu";
	bool isdqzklk = true;
	int ximpz = 5347;
	string hmpoftwtphx = "riyvmroyysopbyyjdbmuut";
	bool vhfwucp = true;
	if (true != true) {
		int ufzplc;
		for (ufzplc = 83; ufzplc > 0; ufzplc--) {
			continue;
		}
	}
	if (false == false) {
		int liiypgyyba;
		for (liiypgyyba = 42; liiypgyyba > 0; liiypgyyba--) {
			continue;
		}
	}
	if (true != true) {
		int ga;
		for (ga = 21; ga > 0; ga--) {
			continue;
		}
	}
	if (5347 == 5347) {
		int vtffh;
		for (vtffh = 97; vtffh > 0; vtffh--) {
			continue;
		}
	}
	if (true != true) {
		int rwqqz;
		for (rwqqz = 61; rwqqz > 0; rwqqz--) {
			continue;
		}
	}
	return 63088;
}

string qmjwycm::bisgjdvasbiriykm(int goatv, double krllbhnvfs, double txsmsqsjszmlsgu) {
	bool cfoaczssift = true;
	bool rsskfgwsfpjfde = true;
	string qqrforixqouq = "lvuoaohikorhrnuzaprvnhzauukdbkdj";
	int jlpvr = 2006;
	int gofxfxis = 5368;
	double qnmrtteephyaea = 57023;
	bool ggdmdisamrwn = true;
	string nbykpzfe = "wseihhcndpzrumitjupziposhryhurftgdbhtzcabpxhnstlikbgauxzizkuylpa";
	double szarx = 24210;
	if (5368 == 5368) {
		int lrpp;
		for (lrpp = 24; lrpp > 0; lrpp--) {
			continue;
		}
	}
	if (true != true) {
		int xwqkzagif;
		for (xwqkzagif = 9; xwqkzagif > 0; xwqkzagif--) {
			continue;
		}
	}
	return string("vlf");
}

void qmjwycm::zawrfpgwfpcfwbvh(bool hqkqmqzdhm, string hgjqqdtzskmdz, double ifjykpxamu, double jmzirmeyz, string cedqmjtyhiyevom, int iklprcovaocvsoc) {
	double obhwd = 7263;
	string tqenttnsgcsrqjd = "kzisyzzzela";
	string bgbuvftddmzdmup = "sjcbimfejfioeemxsuksjvxcjmyvrtovnvtjwavdpetfhqeqyzasolbjdmwjpuojwzxdovwzlkbqtfwqyrdhenmu";
	string wqiytelrw = "tdiqrikbruekiqmrmvxezzrgnwyvehxljweagpyiejugyr";
	if (7263 != 7263) {
		int we;
		for (we = 33; we > 0; we--) {
			continue;
		}
	}
	if (string("kzisyzzzela") != string("kzisyzzzela")) {
		int cavltlvvc;
		for (cavltlvvc = 60; cavltlvvc > 0; cavltlvvc--) {
			continue;
		}
	}
	if (7263 == 7263) {
		int oiymbtpxv;
		for (oiymbtpxv = 38; oiymbtpxv > 0; oiymbtpxv--) {
			continue;
		}
	}

}

double qmjwycm::myvuolpxkrxxbdoqbmepykbo(int aggrzlocmkjix) {
	int ilaxrav = 1097;
	if (1097 == 1097) {
		int acj;
		for (acj = 35; acj > 0; acj--) {
			continue;
		}
	}
	if (1097 != 1097) {
		int pucxpds;
		for (pucxpds = 83; pucxpds > 0; pucxpds--) {
			continue;
		}
	}
	if (1097 == 1097) {
		int zv;
		for (zv = 47; zv > 0; zv--) {
			continue;
		}
	}
	if (1097 == 1097) {
		int no;
		for (no = 73; no > 0; no--) {
			continue;
		}
	}
	if (1097 != 1097) {
		int xfosebt;
		for (xfosebt = 34; xfosebt > 0; xfosebt--) {
			continue;
		}
	}
	return 44073;
}

double qmjwycm::unvskpjxqxybkfhrsycmuofm() {
	double hvqmmrwmglbhv = 64233;
	double ktapne = 22162;
	double iekdm = 12841;
	int eirfgh = 1932;
	double tqxduras = 8756;
	int kaeewsjnvbnj = 5433;
	if (1932 != 1932) {
		int xxsotf;
		for (xxsotf = 43; xxsotf > 0; xxsotf--) {
			continue;
		}
	}
	if (64233 != 64233) {
		int qouelzxmge;
		for (qouelzxmge = 51; qouelzxmge > 0; qouelzxmge--) {
			continue;
		}
	}
	if (8756 == 8756) {
		int irhxz;
		for (irhxz = 45; irhxz > 0; irhxz--) {
			continue;
		}
	}
	if (1932 != 1932) {
		int lyag;
		for (lyag = 92; lyag > 0; lyag--) {
			continue;
		}
	}
	if (5433 != 5433) {
		int yfbxgbijdz;
		for (yfbxgbijdz = 77; yfbxgbijdz > 0; yfbxgbijdz--) {
			continue;
		}
	}
	return 35658;
}

void qmjwycm::empkzgguxyxmgcrtalehhee(string svsuesyvtdiaj, string xlpzxhrzvanrztn) {
	double fkicdw = 40747;
	double mxukhi = 69;
	int fhnxucvdewxvk = 6063;
	string gbxkths = "kyhipipixzmfuspmhkigfscljnrglpwlqkmaxucfbelevsmsdgxgaqmxfjfepvxsx";
	if (6063 != 6063) {
		int zf;
		for (zf = 75; zf > 0; zf--) {
			continue;
		}
	}
	if (6063 == 6063) {
		int vgz;
		for (vgz = 22; vgz > 0; vgz--) {
			continue;
		}
	}
	if (69 != 69) {
		int qjtkzuwjfa;
		for (qjtkzuwjfa = 84; qjtkzuwjfa > 0; qjtkzuwjfa--) {
			continue;
		}
	}
	if (40747 == 40747) {
		int twtieidgc;
		for (twtieidgc = 5; twtieidgc > 0; twtieidgc--) {
			continue;
		}
	}

}

int qmjwycm::fzwgxevidsbtatswulmyoslg(bool ddhxtnidgrgtoov, int imergqzestz, int epkpyvefqbffyme, double plvplgknsctt) {
	string jxwynjg = "wsbnjtrxecsjulcbczctsndlzctrklpzmferggbwbytszumxtyjjfudcbvbadugmexrofqt";
	double pbeezbsjyrjycrb = 83276;
	string qlahsfzglhpdxu = "asujqgubcveugzqgeo";
	bool qoprjy = true;
	double pmzkwe = 11012;
	string ruxtjwocss = "etesokmncrwqhxbuxkncwofsckwulqwxbteyuxfalre";
	double hoxltblckxvuj = 23641;
	string vejeubyejezbdtb = "vrjopmqvckasoyrxlxizliviykmqpayhfqzwsazbpobhlmyji";
	string wduyppscxo = "flrviwxzbcxafvrtcwzhutlpalqckuuujzbeuvsdpzsdflh";
	string ywksxpap = "owdk";
	if (string("vrjopmqvckasoyrxlxizliviykmqpayhfqzwsazbpobhlmyji") == string("vrjopmqvckasoyrxlxizliviykmqpayhfqzwsazbpobhlmyji")) {
		int fxnbpl;
		for (fxnbpl = 79; fxnbpl > 0; fxnbpl--) {
			continue;
		}
	}
	return 59663;
}

string qmjwycm::frumuclfoyvwwxg(bool gapgladaa, double ofikxkub, string qrtrzjtpjzodlr, double kltvyvrsumxbz, int ewbwu) {
	int sjxamgshclculal = 1050;
	string kmbnxtogmokch = "ycmfaixrbkncybvdyozrncntbzgutxiqcglhtmhutgyzlrfqcrqtqjdcgjfjrhrqkysuruunmlhxkfogeojlza";
	bool advpljojjct = false;
	int fdacyvqjzzbosa = 2919;
	bool taktwixv = true;
	if (2919 != 2919) {
		int ek;
		for (ek = 25; ek > 0; ek--) {
			continue;
		}
	}
	if (false == false) {
		int vexjj;
		for (vexjj = 47; vexjj > 0; vexjj--) {
			continue;
		}
	}
	if (false == false) {
		int yuxbelkq;
		for (yuxbelkq = 72; yuxbelkq > 0; yuxbelkq--) {
			continue;
		}
	}
	if (false == false) {
		int akulne;
		for (akulne = 59; akulne > 0; akulne--) {
			continue;
		}
	}
	if (true != true) {
		int xuykm;
		for (xuykm = 6; xuykm > 0; xuykm--) {
			continue;
		}
	}
	return string("jv");
}

string qmjwycm::nlnjzlumheiunbpvdq(int cdpsue, double ucmuxkjmedax, string zivtpqzuj, int azptssqdcdfqcx, string jiryiclpbtjymk, bool pwbxmbzdoksr, string znjhsxc, bool bsivwtl, int xzwhxsaprtsw, string kickwg) {
	int ypgkwbbmjwgi = 488;
	string yfadhkqyvqltfl = "qzxhdjwiomqylwlbgtivqoythgfdtyhvobvkmbyiffbtdzcvccfxga";
	if (string("qzxhdjwiomqylwlbgtivqoythgfdtyhvobvkmbyiffbtdzcvccfxga") != string("qzxhdjwiomqylwlbgtivqoythgfdtyhvobvkmbyiffbtdzcvccfxga")) {
		int rmnwvznk;
		for (rmnwvznk = 58; rmnwvznk > 0; rmnwvznk--) {
			continue;
		}
	}
	if (string("qzxhdjwiomqylwlbgtivqoythgfdtyhvobvkmbyiffbtdzcvccfxga") != string("qzxhdjwiomqylwlbgtivqoythgfdtyhvobvkmbyiffbtdzcvccfxga")) {
		int fcfcefmprg;
		for (fcfcefmprg = 99; fcfcefmprg > 0; fcfcefmprg--) {
			continue;
		}
	}
	return string("piqai");
}

int qmjwycm::zhootrlqdhywucgbjmwgss(string weiokh, bool hyxnh, bool ivdlbxehgnkyrbz, bool okgqqlicoid, bool nawzzb, bool gyywy, bool zdaolh, double wizesiulgmjwr, bool pgukjhpv) {
	int kjeomkxbabp = 401;
	return 97236;
}

string qmjwycm::uyxqiczpzvepsyxsfckns(bool rcrsslrjmqptupo, bool mvrbvx, int srbennrer, double edmsdgcjwyvnm, double nzbtw, bool sqqtn, bool lwnfmzlsdxp, string jbsnejikhsokl, string gjvfevwxavz, string pptukjgh) {
	int hwdsim = 2352;
	bool rbxrzfdiauy = true;
	if (true == true) {
		int wumqmgpkv;
		for (wumqmgpkv = 9; wumqmgpkv > 0; wumqmgpkv--) {
			continue;
		}
	}
	if (true == true) {
		int girttzbudz;
		for (girttzbudz = 43; girttzbudz > 0; girttzbudz--) {
			continue;
		}
	}
	if (true != true) {
		int jnm;
		for (jnm = 29; jnm > 0; jnm--) {
			continue;
		}
	}
	return string("qe");
}

int qmjwycm::cqkqjbqjcqtcefrlwi(string julxiznk, int djsznwonkbe) {
	string darjfdz = "cxlqadvfijabcsogufzvnyfncidf";
	bool vwbsytcovlnkkoj = true;
	bool ldcjzspuw = false;
	double tmzkwnof = 1770;
	string ehgmzxoycnifack = "wzbkkfouixgghyljexddywwbjmddgdibwiydkobyvqm";
	double whhbixcvrrytfqy = 66374;
	int zicmllx = 4714;
	int pbudynee = 4308;
	return 88138;
}

string qmjwycm::xraihgwkgesgo(string ysglqllus, double fnjtvcwhtk, int gjepyimgdqnlp, double jnvxvufutcuwbem, int tbwxkltx) {
	return string("");
}

double qmjwycm::nsjfhepguhfkugblhh(string njatppb, double tegar, string anbqeve, int wwlsztr, double erfvubrnaauix, string hxmqptozwkf, string gwuytjlvesuivh) {
	bool bgmnbsmdvcyyua = true;
	string gqbxpwrbwmcpua = "yovhacdvholfgbfjgesdwawcknknphaxbvhthmxp";
	string obmuis = "kybzhjvuxhnbprvpikowzeiqkuoudwbryfousvwsrtpvsuwjmg";
	int rkgaewtqy = 1213;
	string oodnqsozgfbz = "dyfxyhrkrpxcgecwoeahciehmrtylierlndvhmdsohfswmipffvuluohlgfneabmbgdnlioeyimb";
	string xbknipigudwswbv = "kjsghac";
	double dzyngoryfyunl = 48945;
	int wvvqjnytarki = 1355;
	bool utfmq = true;
	if (1213 != 1213) {
		int edpum;
		for (edpum = 70; edpum > 0; edpum--) {
			continue;
		}
	}
	if (1213 != 1213) {
		int zjspvkph;
		for (zjspvkph = 70; zjspvkph > 0; zjspvkph--) {
			continue;
		}
	}
	return 13606;
}

string qmjwycm::fiwipsxbjzynfghpjdt(int meixffyqzqhd, bool qmzimkmgh, string hexnqp) {
	bool pgxkjxzn = true;
	string yhemcabmd = "xkgajqrddozxlfbxsvtgwxqqlddejiprzscurfwjhjlhdngkkgsazys";
	bool muwos = true;
	string udwpkjtrc = "pubfszpydggrfojuqcnbqcdbyljaznrrjlffzhwewnrxforjlrafhtqcfwuznjkoptxcymf";
	double zmopevu = 41586;
	if (true == true) {
		int dibkdujw;
		for (dibkdujw = 40; dibkdujw > 0; dibkdujw--) {
			continue;
		}
	}
	if (true == true) {
		int ecxegze;
		for (ecxegze = 51; ecxegze > 0; ecxegze--) {
			continue;
		}
	}
	return string("oqffdcegsbd");
}

void qmjwycm::vlxetgphqyhspyybfuhw(string nyalmqronegdv, int mvmyirkgs) {
	double yqfyksrcfdf = 67765;
	if (67765 == 67765) {
		int pohbmgcjl;
		for (pohbmgcjl = 74; pohbmgcjl > 0; pohbmgcjl--) {
			continue;
		}
	}

}

string qmjwycm::vehbsoxanbbczry(int mttedrreszlby) {
	double pnuhguqrhew = 5643;
	if (5643 == 5643) {
		int thme;
		for (thme = 54; thme > 0; thme--) {
			continue;
		}
	}
	return string("lxruntbqzex");
}

qmjwycm::qmjwycm() {
	this->fiwipsxbjzynfghpjdt(3214, true, string("xktgbmjzegdtegaowfwyojjpzqhdyslokpcggxqvlfgnbuxwbaxclrqbfrcvzrhvmvdhdqagejcynns"));
	this->vlxetgphqyhspyybfuhw(string("fomuqmuxhzhquzgsolyqoqsiwplmstyrfayefaytpynbglfrwphycoqupomfwbptecxptypfilkabirm"), 1626);
	this->vehbsoxanbbczry(1211);
	this->unvskpjxqxybkfhrsycmuofm();
	this->empkzgguxyxmgcrtalehhee(string("jpifqtfymbidezmuvezikdyj"), string("dpiidizugrpeccovrbwgmfxhdhiuvfkahhxasflnqhablwrzmawbugnaukozaepo"));
	this->fzwgxevidsbtatswulmyoslg(false, 1235, 1537, 45305);
	this->frumuclfoyvwwxg(false, 81801, string("cedptcpfhveyqmwhdxmejgjhfumikiktbxwlxshrmuyjqqepnbiurlgvmcgt"), 18581, 8165);
	this->nlnjzlumheiunbpvdq(3680, 46996, string("srbkegdhbmwvpsppkffujfjbe"), 2970, string("ogifqvupejfxvkjlaeppmttmyfofxcidbaqjbwtacbrqzhzhrjhckcxusjyhwmuztztqwlpa"), false, string("mfmghwdigypnruybtshfterzndakqnvzhbmopyowrpylhcgvghciwzzoumebvatsnfusmxffescccnmlcjb"), false, 511, string("taeutjplclaugizivfqqcvlspbyfibkgzqwodxfemtbenchpszzzyokojtjsvmtqqglqzpucdiya"));
	this->zhootrlqdhywucgbjmwgss(string("yphkvtldedqfweiooiasjjlmrmpathsapcxjqmkjuvpyzhgcxkfpt"), true, true, true, false, false, true, 75660, false);
	this->uyxqiczpzvepsyxsfckns(true, true, 105, 45132, 7040, false, false, string("japnleywulmejrkmvdwtqkgyiblg"), string("rurrudmvthadauedpxurk"), string("kzlsqigvniblaeoonmjgpwdghklesqvasjbnapdzmcjwjqdtdqiaibxqyaxoomyb"));
	this->cqkqjbqjcqtcefrlwi(string("qskiqdoakgcfyjxdphoyvgvucxctncslshgvvxtoecrwbcopybvfpsenujcihffumvxihubdlrmaduxsoqz"), 391);
	this->xraihgwkgesgo(string("myjnth"), 7043, 160, 39906, 1178);
	this->nsjfhepguhfkugblhh(string("zumthpmqfnh"), 8517, string("qjoyrwhfzwdxwoqjswdbtrq"), 1493, 5659, string("esghkjznzxshlezgrogpvyifrtduoxchxldhxomrvwzendizugowwgqbttsfndhhofbuodsvtdxzald"), string("ahdspypueglwzozoyibnxaeexjmdexaaeanmarrwtzgdknvdcxqxenyniazqcacvtnysrkgfsormijburhojjofnetkyxque"));
	this->hzicqfkmwd(string("sictkilznhiihygdnusmvfykyinepwcajygnijmuoynmueqtvxslfediruakvncqjewicvqqpejtucvjlknjpv"), 15872, 10622, string("esodsarxcjaokcfwnragtvedmauygpm"), true);
	this->gguudcmmxn(string("gctkephtmzpvcpopjfriykeeugcdwogqzoixxvflhteahibultyydvtpcgtdvvqmlhwzurrdjzibfmhytattxsrrqxxdfybh"), string("qqrxevndntrkjqzblxyebxzuhqrghkwjoxujhdkkjalkukqytsgqfmbecgzvwarbnqsbdzymijtelzjqmgijeumhpq"));
	this->djtuztxmrumw(true);
	this->urwkjnqfpoavedx(2027, 6619, 7587, 1313, string("iorhxbqvpcfpzclcrbvslgksnaukmihyrd"));
	this->vhlbaghopoehzehikjxqn(7618, false, false, 33912);
	this->zbmaosllqrplqmlddja(true, true, 43197, 46287);
	this->nshyczpywspxtrgwcvefzk(string("zxnmejbosydqkqzlcfugxicszamrraqbtlsoaxgchzmbuhrrjrkoavgqjmgvulvnyrojvllyltjfbvsppx"), 165, 87348, 41257, true, true, false, 1562, false, string("ieynkqmankamvyvdgfkn"));
	this->bisgjdvasbiriykm(2342, 12246, 52165);
	this->zawrfpgwfpcfwbvh(false, string("ichgbvjtbjzkdogleecqzlyhgdmrdyicxjnyrqzhgybaxnzwonmyiifravdhasweztrcarjugllou"), 3594, 50020, string("azefqothyzumfxtqtuxykgjxhmfuxwxm"), 498);
	this->myvuolpxkrxxbdoqbmepykbo(4507);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class omerdop {
public:
	int gpuiuwzmds;
	double knrbxepun;
	double ggblsbwgspfy;
	string zlpqpgesc;
	omerdop();
	string nloejrtiexkiqsvvxb(bool edydrfc, int ewfhgtg, bool ocpwnok, int uifsmgrlbl, int vhsgnrcguz);

protected:
	string xsxoijuwwxkpi;
	double lojkukqofamebyb;

	double rffucibxyii(double tsyuq, int pcmmghmgl, string pdthkpgwtyda, string cpmvirqpegocq, double ksspmgbgla, bool yymmmgalk);
	string pcyuzacsoibsziwbqf(bool xtxiqczolsmqjmm, string ywkmvgmpqzd, int gjdvoekpl, string xiraptaokst, bool ihrmriijq, string ufyhlycbkerlzx, string frftdv, int gyopk, bool gplpixayyxyojzy);
	string tpzbskgbeeztwhy(double lknqezjtvbddk, int maacfdbtwukmiwm, string trvvctpncc, string eovczxcy, bool ifhysycnam, bool llchpqawrab, string qbvedsm, double yzbhx);
	string zxhmsguuiijlhgcwcchdzkr(double zznjxpjd, bool ipjyuinuivgbj, double trbomywzavzc, int porfqfjaianrgm, string fwbcuyahzy, int rhkuti, int enpaxhlq, string fouaoix, bool ntzkztdfe);
	void pxhokaeojinpqpprjlynvsx(double gszqfyxi, bool ptleblgpzcuk, bool vwtqkicd, string jvbujhmzwl, string unsxl, bool bundjn, double jgvul, bool gjxfxr);
	int hbtxmoyyrnflbftvglhqow(string dguyog, double cqwttb);

private:
	double yovmqmiye;
	string mewvqygtzzxioex;
	double hldooutbfncx;
	bool vwbpozxbletrkzv;

	int qgxkyvtuzsjjcm(int zfndujfkfncnv, string vcdcsoyfineaizc, double czvyww, bool gvejwbocmnetav, int pnlxmzczblatei, bool kshbc);
	int gqudfeugcdgzs(int dqjhyaokmhuwwf, double fvsnpdiu, string yfrskdxwgqpei, int zwmwnahlsc);
	int nnnqvsoiinfbunjwobwcb(string xrmkz, int ugolmymai, bool fpxazvgee, int iebevrsnx);
	bool jxlcowrvmmyfqtnwiw(bool srfpjcq, int kojvlaiqzrnwrvv);
	string oitkcwwnejf(bool qrgjpdnssyit, string qxapiornibtl, bool shhcmfvfnnoavtw);
	void vphkinxahuqr(string fqvoum, int wpsli, bool zmceboisnftslv, string dymamacltljjgf, string hdvogfaazfphqw, string zyekm, double rccumiupqmhmkoh);
	double ffuefgscsvdmedr();
	double gnalsstuofdpsvmgasuti(string rghrlrer, bool lozbhzoueydfxtz, string jjdzk, bool tmogws, string hnsmd, string eongehpmoyft);
	string fahegchdzqpldjtgxnh(double fvznscfjgqd, string dxitisfqll, int kuuxq, string blnldvaqslnlpmu, int gdbvruuenqjdt);
	string tufzvluxmzbhfyyc(string noglkmkohnn, bool eqyjqqxwxqfb, bool qaqmznmmql, int fprll, bool hiyzzu, string ijankn, double cbdmrjapd);

};


int omerdop::qgxkyvtuzsjjcm(int zfndujfkfncnv, string vcdcsoyfineaizc, double czvyww, bool gvejwbocmnetav, int pnlxmzczblatei, bool kshbc) {
	string vsgmdvpdy = "jgfllgfjhevmkmhmpgjmcyftynjaqrrgnan";
	double kztcxxdj = 63234;
	double ewjlhvtv = 6170;
	double mnjurxpznfakgyq = 56556;
	int zakqashixupfkxg = 708;
	bool lszjdhp = false;
	return 56537;
}

int omerdop::gqudfeugcdgzs(int dqjhyaokmhuwwf, double fvsnpdiu, string yfrskdxwgqpei, int zwmwnahlsc) {
	double ypflklaqptfcsoq = 39017;
	int rijep = 2139;
	bool elukb = false;
	string iqnpwoeegjh = "wycfwrzzetszlzdontiosxpawkcpswdnxsvqxllapbpazewkopnayflevhpvclxhmcvosqrxabwcbwtboj";
	string orkkzt = "nlytyptceibkfdxhzpjjwibmkuikwmkhjwkxvllwfxaycxewkw";
	double ayxmc = 8608;
	string slybn = "eurtadudapbwhowxwcxofwnkdhgwnujkabhvkpxhozmp";
	int atuowekx = 2691;
	int bpvebwbn = 5164;
	if (false == false) {
		int vmzsyp;
		for (vmzsyp = 99; vmzsyp > 0; vmzsyp--) {
			continue;
		}
	}
	if (false != false) {
		int weoc;
		for (weoc = 39; weoc > 0; weoc--) {
			continue;
		}
	}
	if (false == false) {
		int hlqzun;
		for (hlqzun = 10; hlqzun > 0; hlqzun--) {
			continue;
		}
	}
	if (string("eurtadudapbwhowxwcxofwnkdhgwnujkabhvkpxhozmp") != string("eurtadudapbwhowxwcxofwnkdhgwnujkabhvkpxhozmp")) {
		int isyjnpby;
		for (isyjnpby = 41; isyjnpby > 0; isyjnpby--) {
			continue;
		}
	}
	return 74436;
}

int omerdop::nnnqvsoiinfbunjwobwcb(string xrmkz, int ugolmymai, bool fpxazvgee, int iebevrsnx) {
	double qnxbfqc = 10512;
	int fpdkaotspdbiq = 3122;
	double gltlwwha = 9425;
	bool yvwgklngocqnj = true;
	double zsdekkpniltfnd = 75699;
	string apkgxufrxf = "fkvknyx";
	int dnkshbojoqnlwas = 1188;
	double tzryhgkh = 32898;
	string lzkrzlsuvvn = "osvynascdyacqedlevudjekkuqjdmiccxdopeacssjzjsvvdfarhwqor";
	return 39469;
}

bool omerdop::jxlcowrvmmyfqtnwiw(bool srfpjcq, int kojvlaiqzrnwrvv) {
	bool vnpwfmgw = false;
	double skkitkiowj = 358;
	string hehxstfphlictpl = "lpzmvpalakpvtfcpzxmmnhguxleswdiynbxyclcmlkvuaqmfmsteaapzxihsjprjjadjgpzfkywgmhvnfnihuq";
	int fdyybuabv = 1850;
	double ldzlwqpouje = 13855;
	int eqdkfny = 1422;
	string moiqzmoghfount = "rdvevufvpckilzkjj";
	double qdvegusfjnwdyfj = 52677;
	string hrpzcmhyulssgkl = "chxigdubwsatuobkrrejapvqylofkimdz";
	return false;
}

string omerdop::oitkcwwnejf(bool qrgjpdnssyit, string qxapiornibtl, bool shhcmfvfnnoavtw) {
	string xmdhridsilt = "rdljjryqzjtq";
	bool ttkadinixsppgl = false;
	if (string("rdljjryqzjtq") != string("rdljjryqzjtq")) {
		int snvddd;
		for (snvddd = 65; snvddd > 0; snvddd--) {
			continue;
		}
	}
	if (string("rdljjryqzjtq") != string("rdljjryqzjtq")) {
		int evfim;
		for (evfim = 79; evfim > 0; evfim--) {
			continue;
		}
	}
	if (string("rdljjryqzjtq") != string("rdljjryqzjtq")) {
		int mgiqpstud;
		for (mgiqpstud = 41; mgiqpstud > 0; mgiqpstud--) {
			continue;
		}
	}
	if (false == false) {
		int ov;
		for (ov = 81; ov > 0; ov--) {
			continue;
		}
	}
	if (string("rdljjryqzjtq") != string("rdljjryqzjtq")) {
		int pmisayk;
		for (pmisayk = 13; pmisayk > 0; pmisayk--) {
			continue;
		}
	}
	return string("sxfdwjdpaxzjhfqafua");
}

void omerdop::vphkinxahuqr(string fqvoum, int wpsli, bool zmceboisnftslv, string dymamacltljjgf, string hdvogfaazfphqw, string zyekm, double rccumiupqmhmkoh) {
	string lomxflajqemb = "qydixfxwuqntkypibhozobjkhepayglbubgbrnbqtvnznobmwcbvssplhesldeapgtlinzzkrrgjoybtlpzrlihnowzb";
	double zmnxsk = 15565;
	int ueggkkbs = 315;
	if (string("qydixfxwuqntkypibhozobjkhepayglbubgbrnbqtvnznobmwcbvssplhesldeapgtlinzzkrrgjoybtlpzrlihnowzb") == string("qydixfxwuqntkypibhozobjkhepayglbubgbrnbqtvnznobmwcbvssplhesldeapgtlinzzkrrgjoybtlpzrlihnowzb")) {
		int gv;
		for (gv = 78; gv > 0; gv--) {
			continue;
		}
	}
	if (string("qydixfxwuqntkypibhozobjkhepayglbubgbrnbqtvnznobmwcbvssplhesldeapgtlinzzkrrgjoybtlpzrlihnowzb") == string("qydixfxwuqntkypibhozobjkhepayglbubgbrnbqtvnznobmwcbvssplhesldeapgtlinzzkrrgjoybtlpzrlihnowzb")) {
		int fxnxfrt;
		for (fxnxfrt = 34; fxnxfrt > 0; fxnxfrt--) {
			continue;
		}
	}
	if (string("qydixfxwuqntkypibhozobjkhepayglbubgbrnbqtvnznobmwcbvssplhesldeapgtlinzzkrrgjoybtlpzrlihnowzb") == string("qydixfxwuqntkypibhozobjkhepayglbubgbrnbqtvnznobmwcbvssplhesldeapgtlinzzkrrgjoybtlpzrlihnowzb")) {
		int ypzpel;
		for (ypzpel = 77; ypzpel > 0; ypzpel--) {
			continue;
		}
	}

}

double omerdop::ffuefgscsvdmedr() {
	bool fjesbwcnxbeahcp = true;
	bool bdmxbqt = true;
	string eaymed = "vogcsqlrhrdaxbkcuviwqqnltfblfvgtcbyxwhkxlonqhhcvdx";
	string lvytwfg = "gvrytlbikbvkgfnsbqredeszvbomhnjjzlypwbyomesysuzzbhsghfusyazhwnnvpre";
	int efcjcicbgk = 7840;
	string ybwwiv = "lcalcnilktakxvgippphifbarpywcaglpaczhbygtlwvowmcddvhfbyhhtdlh";
	string jhpypemumjdg = "okakbzujeildwxxcfsuwwwbkzfileqwohqbcqgegfithwibibstnywfshujfkygymsucevbcqdsfehnouexv";
	if (true != true) {
		int pnsvi;
		for (pnsvi = 90; pnsvi > 0; pnsvi--) {
			continue;
		}
	}
	if (true == true) {
		int roxjzatmok;
		for (roxjzatmok = 68; roxjzatmok > 0; roxjzatmok--) {
			continue;
		}
	}
	return 3531;
}

double omerdop::gnalsstuofdpsvmgasuti(string rghrlrer, bool lozbhzoueydfxtz, string jjdzk, bool tmogws, string hnsmd, string eongehpmoyft) {
	double xevxvigygyj = 5964;
	int bcrwr = 1239;
	double idvpmdjfsszxfxl = 3960;
	string svczrtutzh = "hqgdgkvethckiopxfzasehxdqywgfmcnowevlxsebudspfqsmhartzbbomxzstjttznh";
	int gwzmvycwxdyiger = 2777;
	int saxpsyecf = 6424;
	double tewlhchj = 47337;
	bool rptnfbkhcamgqr = false;
	int qpntvqgxtaninjq = 841;
	return 18553;
}

string omerdop::fahegchdzqpldjtgxnh(double fvznscfjgqd, string dxitisfqll, int kuuxq, string blnldvaqslnlpmu, int gdbvruuenqjdt) {
	string cwqwmdjvzn = "mnmfnefpfmfmgdrthytsbiwznuskietdcbxjrqkxcbrvjtvzyrgv";
	int rayakfpfyaflx = 180;
	int fxpwmjdrdn = 536;
	bool vkfaxatsmj = true;
	if (string("mnmfnefpfmfmgdrthytsbiwznuskietdcbxjrqkxcbrvjtvzyrgv") == string("mnmfnefpfmfmgdrthytsbiwznuskietdcbxjrqkxcbrvjtvzyrgv")) {
		int kdsxfzqqmv;
		for (kdsxfzqqmv = 17; kdsxfzqqmv > 0; kdsxfzqqmv--) {
			continue;
		}
	}
	if (180 != 180) {
		int ubbd;
		for (ubbd = 78; ubbd > 0; ubbd--) {
			continue;
		}
	}
	if (180 == 180) {
		int aubq;
		for (aubq = 93; aubq > 0; aubq--) {
			continue;
		}
	}
	return string("ecqukwrdzrbbwcecm");
}

string omerdop::tufzvluxmzbhfyyc(string noglkmkohnn, bool eqyjqqxwxqfb, bool qaqmznmmql, int fprll, bool hiyzzu, string ijankn, double cbdmrjapd) {
	double ecbytrvaleprr = 45626;
	string ebqfmnyinx = "cnufnvpezkeltdqoqufacqifubiysitbiepetpuixmgiacyrwnavbp";
	int arldasefbbjnsth = 3994;
	bool cdfuwcups = true;
	if (45626 == 45626) {
		int ffuksyt;
		for (ffuksyt = 77; ffuksyt > 0; ffuksyt--) {
			continue;
		}
	}
	if (true != true) {
		int ejxbfme;
		for (ejxbfme = 38; ejxbfme > 0; ejxbfme--) {
			continue;
		}
	}
	if (45626 != 45626) {
		int arxgeekmbt;
		for (arxgeekmbt = 88; arxgeekmbt > 0; arxgeekmbt--) {
			continue;
		}
	}
	if (3994 == 3994) {
		int kyotoxr;
		for (kyotoxr = 79; kyotoxr > 0; kyotoxr--) {
			continue;
		}
	}
	return string("otl");
}

double omerdop::rffucibxyii(double tsyuq, int pcmmghmgl, string pdthkpgwtyda, string cpmvirqpegocq, double ksspmgbgla, bool yymmmgalk) {
	return 43416;
}

string omerdop::pcyuzacsoibsziwbqf(bool xtxiqczolsmqjmm, string ywkmvgmpqzd, int gjdvoekpl, string xiraptaokst, bool ihrmriijq, string ufyhlycbkerlzx, string frftdv, int gyopk, bool gplpixayyxyojzy) {
	bool hihjzgxkwafqh = true;
	string qofdqwkr = "vnhroznpmrhgnuozggieqsvsdtzkavwmcqxdchjhsoronzndhvklqsq";
	double fmpnm = 19251;
	double zzakyfmuusxy = 39596;
	bool qozjx = true;
	string vhdyqyp = "zhenstuas";
	bool rlfxa = true;
	double cmteqodobtqknye = 11213;
	double hcetbckysj = 41958;
	if (true != true) {
		int oyzugsfa;
		for (oyzugsfa = 75; oyzugsfa > 0; oyzugsfa--) {
			continue;
		}
	}
	if (41958 == 41958) {
		int jcwblzwpnn;
		for (jcwblzwpnn = 8; jcwblzwpnn > 0; jcwblzwpnn--) {
			continue;
		}
	}
	return string("ccpcwcokebdd");
}

string omerdop::tpzbskgbeeztwhy(double lknqezjtvbddk, int maacfdbtwukmiwm, string trvvctpncc, string eovczxcy, bool ifhysycnam, bool llchpqawrab, string qbvedsm, double yzbhx) {
	bool tqzvanpry = true;
	bool nminn = true;
	string wmuewapvcrixlro = "guklnuyzbwkhmjnppehwruqdxdubvplufawfxkrwigsiapaojhgfbexyvbcqszaslwpsbvufvztbedvmkvzglavponjbmqg";
	if (string("guklnuyzbwkhmjnppehwruqdxdubvplufawfxkrwigsiapaojhgfbexyvbcqszaslwpsbvufvztbedvmkvzglavponjbmqg") == string("guklnuyzbwkhmjnppehwruqdxdubvplufawfxkrwigsiapaojhgfbexyvbcqszaslwpsbvufvztbedvmkvzglavponjbmqg")) {
		int zplyh;
		for (zplyh = 44; zplyh > 0; zplyh--) {
			continue;
		}
	}
	if (true == true) {
		int igztmt;
		for (igztmt = 81; igztmt > 0; igztmt--) {
			continue;
		}
	}
	if (true != true) {
		int jo;
		for (jo = 33; jo > 0; jo--) {
			continue;
		}
	}
	if (true == true) {
		int jzixvja;
		for (jzixvja = 8; jzixvja > 0; jzixvja--) {
			continue;
		}
	}
	return string("ddjqsdbfbt");
}

string omerdop::zxhmsguuiijlhgcwcchdzkr(double zznjxpjd, bool ipjyuinuivgbj, double trbomywzavzc, int porfqfjaianrgm, string fwbcuyahzy, int rhkuti, int enpaxhlq, string fouaoix, bool ntzkztdfe) {
	string etlefjeygjr = "jhxczzehyofzdlrolipsoxwu";
	bool rmyhjjlkcqjc = false;
	double ppgxzn = 23913;
	int kezaigzlfusix = 862;
	int ngulxpgbm = 4289;
	int pjsbjxph = 234;
	double fkypwdvhddajsv = 2190;
	int vhokwqwsyoxr = 1506;
	string bdkcsdsdg = "zktiksmxuhfsxjvdokewoomlqkyosxgbisorxkppptznwqzoguigseiltugqkgjnq";
	if (string("zktiksmxuhfsxjvdokewoomlqkyosxgbisorxkppptznwqzoguigseiltugqkgjnq") != string("zktiksmxuhfsxjvdokewoomlqkyosxgbisorxkppptznwqzoguigseiltugqkgjnq")) {
		int ycwtci;
		for (ycwtci = 61; ycwtci > 0; ycwtci--) {
			continue;
		}
	}
	if (string("jhxczzehyofzdlrolipsoxwu") == string("jhxczzehyofzdlrolipsoxwu")) {
		int vf;
		for (vf = 64; vf > 0; vf--) {
			continue;
		}
	}
	if (string("jhxczzehyofzdlrolipsoxwu") != string("jhxczzehyofzdlrolipsoxwu")) {
		int lcrc;
		for (lcrc = 100; lcrc > 0; lcrc--) {
			continue;
		}
	}
	if (23913 == 23913) {
		int ybymt;
		for (ybymt = 48; ybymt > 0; ybymt--) {
			continue;
		}
	}
	return string("lqgbijcdbzxfi");
}

void omerdop::pxhokaeojinpqpprjlynvsx(double gszqfyxi, bool ptleblgpzcuk, bool vwtqkicd, string jvbujhmzwl, string unsxl, bool bundjn, double jgvul, bool gjxfxr) {
	double mtdjsfotfdlpuq = 5424;
	if (5424 == 5424) {
		int epb;
		for (epb = 61; epb > 0; epb--) {
			continue;
		}
	}
	if (5424 == 5424) {
		int fceubzhcn;
		for (fceubzhcn = 64; fceubzhcn > 0; fceubzhcn--) {
			continue;
		}
	}
	if (5424 != 5424) {
		int vn;
		for (vn = 22; vn > 0; vn--) {
			continue;
		}
	}

}

int omerdop::hbtxmoyyrnflbftvglhqow(string dguyog, double cqwttb) {
	return 11966;
}

string omerdop::nloejrtiexkiqsvvxb(bool edydrfc, int ewfhgtg, bool ocpwnok, int uifsmgrlbl, int vhsgnrcguz) {
	int cmydk = 325;
	if (325 == 325) {
		int gxa;
		for (gxa = 39; gxa > 0; gxa--) {
			continue;
		}
	}
	if (325 == 325) {
		int tfkg;
		for (tfkg = 75; tfkg > 0; tfkg--) {
			continue;
		}
	}
	if (325 == 325) {
		int bc;
		for (bc = 95; bc > 0; bc--) {
			continue;
		}
	}
	return string("uszkrlgrvope");
}

omerdop::omerdop() {
	this->nloejrtiexkiqsvvxb(false, 2702, true, 1027, 4458);
	this->rffucibxyii(1629, 3354, string("utpaoikguzfsfzvjasaitjfawfhfeefcsyimdrgfksyqwishccqzwjuvkvupwce"), string("jpoxzvnjy"), 24791, false);
	this->pcyuzacsoibsziwbqf(false, string("jqtsolggesww"), 1103, string("szoapdegbzcqffztalbnrbytslolreugtsoxwcffxgtmijaalihimxdqlgptmhszazktjjlcspwokmuaphgfqgkgd"), true, string("umymogkizmddqipabvohwwfmkcvqcntvkhtsrdffejycsirseetrjhtbfsyxyypmobpobduigtiadtsswmthe"), string("puoleomfeoxjphtxknvufifxldyidralnqsjrzhdbfaytxabkvoanqcljwvicrncyheclsbaywdysqplvaxhavb"), 5538, false);
	this->tpzbskgbeeztwhy(40673, 2508, string("pyxiewxlfznvjfbeyrbfoljlnihyauqdravwrvvwnrjmlmcprgkkmywpwrinjglepaewyyawhythp"), string("qjnnmcmbeiqxybcgwryqsawnhhylijxbscznacghffkmamhwlmjrldlljjdvbgelcxdkaubiuscajvdwtderkwnyuodxc"), true, true, string("reofcyimdbkvqnvhxfogrbohtmeadilnueeremmcipnwtjunbgte"), 14422);
	this->zxhmsguuiijlhgcwcchdzkr(22451, false, 42046, 614, string("ohfkiuqobppojihbmtevscfwipvkggunejzhtfdladcjnuqkkehvafydunpjkbywldtwfehtggoldgopixvdye"), 996, 267, string("xjwphsusnwyldvvxlyynqmcpqusbesgiyskvqnfwgkpenzjjeswaohqzhnosgikvrhdrdlksiuhiudcb"), true);
	this->pxhokaeojinpqpprjlynvsx(5674, false, false, string("vicjevxqjwjrwcdnrkrzxjuihytfwbarcaoalatukfzojmhiuywclgojwajdvioouwtluhlutsd"), string("zwekjvyzwrvxuokmlexhzrpwabyhvpehjttogqqncuotmu"), false, 39844, true);
	this->hbtxmoyyrnflbftvglhqow(string("pnelsvtktrhdgzolgwgbhowxcolenvwqjikptcoecpurxplhvlvhibbrqpua"), 15110);
	this->qgxkyvtuzsjjcm(1979, string("fkchsmwkzlfdftctitw"), 15114, false, 2750, false);
	this->gqudfeugcdgzs(1514, 34683, string("rqdxldvxzhsutddst"), 674);
	this->nnnqvsoiinfbunjwobwcb(string("ahzqdxjfsyoxvcjdirqkldnkxsxstbllnfcozmfpbgd"), 248, false, 1901);
	this->jxlcowrvmmyfqtnwiw(true, 24);
	this->oitkcwwnejf(true, string("tvjphaakgsofytnhxazvlyxmccqdorxumzscxeawvwjflltiqgmguwbowsnksupecmqpxz"), false);
	this->vphkinxahuqr(string("xazggdafaevbstjbfmyzeqecvfcqikunktdgbnpkjmxrnjzlu"), 2324, true, string("unqqdlixjmmvdehuhlsoqtcubbpppphexdcnzileywharxgqietpnfvgjldcls"), string("yomizswpghtbwknhenxxqxawnijbujwuftpnrpfprnhpfdztlvfhqysjfiib"), string("xjehsxknsywybkjbohzcmpmvjjufndhuirpngalivfmwhssczxlipgiqxceb"), 92532);
	this->ffuefgscsvdmedr();
	this->gnalsstuofdpsvmgasuti(string("sftxnkqogbzubfswosrbivezydrprhyfeziwljkytgliqjbrpdqpuegbyhodtbojjyqtphtczlfvbtqoerpaauimq"), false, string("txzzvwljmcqmrudlcxeuxooedasakkwfuvth"), false, string("ipvsqkhmxrmacbpjhdntqerkcgjrupojj"), string("wkzbuioviwousawihjuulxcfqidnmjhrycvdwaycatchsgrkpiygqfafbmmcpuohnjkvsmojtxptpgpnr"));
	this->fahegchdzqpldjtgxnh(1174, string("idlptrdeajmvudeprrpbkvrvensaqbohwxscwaqcrcmnexrgxztbomdveepptfctyahxpjspkroriqmxma"), 8312, string("bqtibmweyxuzcrzmcfeanlediwlobmufvkneljhaarxlefsmestlatvzdworuxcefdevjoevrvsw"), 5086);
	this->tufzvluxmzbhfyyc(string("rcshuv"), true, false, 3639, false, string("wa"), 73180);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class bzhsjnm {
public:
	string pszosw;
	double qhaoottpkkwog;
	bool cmyfwsw;
	bool iblupu;
	bzhsjnm();
	int bhetesmlvmivemoecfiekmaf(int xpqlkqhxyowy, double eebacyvayvpnbkp, int ibkkr, bool xcedowsrb, string wtlqbvyg, bool fttxtemwz, int mdpuazegs, int qzbjvxokaziw, double jjxmxn);
	double dtxmayrudea(bool bcqhpt, double pitbq, int hmlqfs, double rkiznmt, bool geyjbebcrtn, string fmknawsdxq);
	int cvzhmunhcrntoqvuntty(bool ztozcwn, bool qsaflbgigh);
	bool wbyjdcjenm(string ntqareawwktfugz, bool pqrmskiy, bool fsgsofc, int nvmzsgom, double bshmiknyulnkdpn, string pvwupbg, int cqslypty);
	int mdqryoflxbovorkgsdvbel(double tblxtg, string knmxfdlznssrzs, int nmkgcn, int wxsnbxh, string dirzlckvqsehk, string qtlmqz, bool joojrbydwmpoee, double jscwgu, string pikvpyrcmxnpcbb, double bekiiluq);
	bool kismsrqibwwnayoqcsd();

protected:
	bool ibrswcqw;
	double pwelkyjy;
	double gbfyqpyx;
	int pgdzld;
	double qsgzqbg;

	bool cndzenvymockjrngw(double zoyuflwofbqzx, string pvceysw, int anxmepa, int uqghka, string qczybco, double cutkxkocz, double lgvucb, int xjwsrc, string galswiokfcjzcev, double upmnlevhd);
	void kyqagzynlmyihan(int zvnoqoojdxb, bool fjxbcd);
	int mrrnjlriyivtdpnkyxg(double fcxvtaluaqdigfs, string odeexzzjnzsl, bool aqvkgg, int kwqyhvzsa, double vevsmhbfbwbxwk, double dwvjz, double ccxgpwqa, int vajgk, string vtjugyu);
	int wklvvnwltglloipbnqhw(bool wvzivfdxivcr, string bhwvsqpiomf, bool mfhvetzhm, string srfjztymhxdhtzc, double vefjhscebfc, int tqfhifbmrcqo, bool vtcnnpib);
	double lzacamrduqlbdiplesrfk(double xitclmmnhn, double gqacyjzhomg);
	string sbpjyfsenl(double actks);
	bool oybypgneyfioxinyjwpeajjsz(double xfprntj, int lsycygxua, bool jmikvzhv, bool jtrqjyh, int bmaxdjou, int yprukv, string ngntwrtwj);
	double ujiuencrqxjdkeczscmo(int wnhyjpwdtswejz, string dtydoiegclmvx, bool jlmyius, int wjyiftmgzi, double venrvjkjmlry, int tzrmwdt, string xtzgwshgsihcg, double ldixcbvlsuhpvn);
	int ggeqpuzfscywknjwapikey(bool lyxgyvhvty);

private:
	double usqycrdealfqx;
	string wqujaqdaxo;
	int unezhhakrrw;

	double dwddimijydzhkuf(string psbwzufevzv, double uykokdrrfffzc);
	double frlgrapzszljouzfb(double tsbsikyduefcf, bool guostsrcwokhroo, string rwssgpjufamqbms, string dgrjrrshwxzgoas, double fprbth, int amgrsozozxfd, int ehnvrwpzqk, bool knydmfrk, string pbbwdglf, string gqtonnqosctvbnn);
	void gqjieinnhudjszyruzuyn(int gjwuapw, string icnxdj, double plmtowpgxvtbwa, string xetdq, string tgblgsjkqmv);
	bool lhcxlboybykopz(int xoatyqnlxxjsdet, double ixehmmao, bool teobnocabjdobf, string xhoizwiloodnntd, string rzwbyorx, double esealvxayrdrfl, bool xmfffumoviyp, string bqemc);

};


double bzhsjnm::dwddimijydzhkuf(string psbwzufevzv, double uykokdrrfffzc) {
	return 92356;
}

double bzhsjnm::frlgrapzszljouzfb(double tsbsikyduefcf, bool guostsrcwokhroo, string rwssgpjufamqbms, string dgrjrrshwxzgoas, double fprbth, int amgrsozozxfd, int ehnvrwpzqk, bool knydmfrk, string pbbwdglf, string gqtonnqosctvbnn) {
	string cecbueiacje = "vlriejxfhvarfwnymbdojukhhmljucxfaibycmukynooxnwhapbwpebuttdscqcunabaxloqjmlrcznb";
	bool efvibrcsqg = true;
	if (true == true) {
		int lkva;
		for (lkva = 66; lkva > 0; lkva--) {
			continue;
		}
	}
	return 49100;
}

void bzhsjnm::gqjieinnhudjszyruzuyn(int gjwuapw, string icnxdj, double plmtowpgxvtbwa, string xetdq, string tgblgsjkqmv) {
	int gxtvurrapv = 3893;
	bool vkxjaknbw = false;
	double sffiywkufmhryz = 6987;

}

bool bzhsjnm::lhcxlboybykopz(int xoatyqnlxxjsdet, double ixehmmao, bool teobnocabjdobf, string xhoizwiloodnntd, string rzwbyorx, double esealvxayrdrfl, bool xmfffumoviyp, string bqemc) {
	double fmrhwghhna = 16236;
	int zrmfimgxdnz = 5592;
	bool jaxcxntqtvo = false;
	int hevdp = 734;
	string isbgxlvagbt = "gotrtlzbyhmyfghmstydyfshlqdplejdxssbvfchoqang";
	int wnrkdoqxovkx = 1580;
	int hwakyhwatqrpe = 3919;
	double vvrvwh = 43755;
	string asbhebwik = "kohztqsblaacdptxwpvuqsglxskfnacssnwsxvmovwvdwuifroafbgclpagiwfijlmeaccqvlkcnusq";
	int luelyinom = 4049;
	if (43755 != 43755) {
		int fysxqd;
		for (fysxqd = 25; fysxqd > 0; fysxqd--) {
			continue;
		}
	}
	if (43755 != 43755) {
		int zfpw;
		for (zfpw = 79; zfpw > 0; zfpw--) {
			continue;
		}
	}
	if (5592 == 5592) {
		int ndlzaa;
		for (ndlzaa = 2; ndlzaa > 0; ndlzaa--) {
			continue;
		}
	}
	if (string("gotrtlzbyhmyfghmstydyfshlqdplejdxssbvfchoqang") != string("gotrtlzbyhmyfghmstydyfshlqdplejdxssbvfchoqang")) {
		int ndygwj;
		for (ndygwj = 53; ndygwj > 0; ndygwj--) {
			continue;
		}
	}
	return false;
}

bool bzhsjnm::cndzenvymockjrngw(double zoyuflwofbqzx, string pvceysw, int anxmepa, int uqghka, string qczybco, double cutkxkocz, double lgvucb, int xjwsrc, string galswiokfcjzcev, double upmnlevhd) {
	return true;
}

void bzhsjnm::kyqagzynlmyihan(int zvnoqoojdxb, bool fjxbcd) {
	double qzatx = 25186;
	bool xnwyvsa = false;
	string dqvgjnwrnqgz = "jlnratzlwfjzsfpxmzjuohrjbbewapkzypztkcrxiysxkxnkqtrmmkcgezkyuyjlgokdteijriqyomdhptcueoyftkktrspgfqbo";
	int hisyl = 151;
	int wyqmrbmbierwp = 3144;
	double dksbnjgnredl = 5530;
	double xuvbuw = 8749;
	bool zswdl = false;
	double tltvao = 81335;

}

int bzhsjnm::mrrnjlriyivtdpnkyxg(double fcxvtaluaqdigfs, string odeexzzjnzsl, bool aqvkgg, int kwqyhvzsa, double vevsmhbfbwbxwk, double dwvjz, double ccxgpwqa, int vajgk, string vtjugyu) {
	bool heyagqk = false;
	int zxypveaqqqwwpt = 8617;
	string rrhjmfhrrovrof = "gecnwecjjsmhrwvvsmylapzb";
	bool pedyr = false;
	int ezbbcpkhjrrh = 8069;
	bool eopfdhedqmhvboh = true;
	if (8617 == 8617) {
		int pqxwo;
		for (pqxwo = 74; pqxwo > 0; pqxwo--) {
			continue;
		}
	}
	if (false != false) {
		int wkw;
		for (wkw = 89; wkw > 0; wkw--) {
			continue;
		}
	}
	return 59601;
}

int bzhsjnm::wklvvnwltglloipbnqhw(bool wvzivfdxivcr, string bhwvsqpiomf, bool mfhvetzhm, string srfjztymhxdhtzc, double vefjhscebfc, int tqfhifbmrcqo, bool vtcnnpib) {
	return 82225;
}

double bzhsjnm::lzacamrduqlbdiplesrfk(double xitclmmnhn, double gqacyjzhomg) {
	int xfakvqe = 6901;
	bool wodnivympiy = true;
	double safzhzzampn = 8016;
	string ubyudkpueji = "zkkwcwbqdwdrnyxqagazgseqcskkqdprfoqmcihututumqmrrjnmuuynyl";
	int ateovhphcaoybd = 1216;
	bool ekadqk = false;
	string jltvfpvoacb = "bmbnpouqtlufeautgmvamgnvreyuovkikbjksrtriosggjbithz";
	if (true != true) {
		int daq;
		for (daq = 91; daq > 0; daq--) {
			continue;
		}
	}
	if (6901 != 6901) {
		int bdnydn;
		for (bdnydn = 16; bdnydn > 0; bdnydn--) {
			continue;
		}
	}
	return 29599;
}

string bzhsjnm::sbpjyfsenl(double actks) {
	bool daitp = false;
	int lpxgtnnivekll = 3214;
	bool brksnkeyswsfv = false;
	if (3214 == 3214) {
		int sylplfjxmn;
		for (sylplfjxmn = 98; sylplfjxmn > 0; sylplfjxmn--) {
			continue;
		}
	}
	if (false == false) {
		int vwji;
		for (vwji = 28; vwji > 0; vwji--) {
			continue;
		}
	}
	if (3214 == 3214) {
		int mmpnix;
		for (mmpnix = 63; mmpnix > 0; mmpnix--) {
			continue;
		}
	}
	if (false != false) {
		int sbi;
		for (sbi = 6; sbi > 0; sbi--) {
			continue;
		}
	}
	return string("vdaphsqxtmfxacl");
}

bool bzhsjnm::oybypgneyfioxinyjwpeajjsz(double xfprntj, int lsycygxua, bool jmikvzhv, bool jtrqjyh, int bmaxdjou, int yprukv, string ngntwrtwj) {
	string qccvxhjhd = "wqfhrtgepiweqfaeazkflqmqfjcuqnbuktthmegkjuddjceiuiwbtssvcziabjymuqrwkjnbgeg";
	bool iemcku = false;
	double ftwrlepno = 27316;
	double vspvqmaxcjw = 65497;
	bool ykoahseg = false;
	bool ataegesjd = true;
	if (27316 == 27316) {
		int hk;
		for (hk = 21; hk > 0; hk--) {
			continue;
		}
	}
	return true;
}

double bzhsjnm::ujiuencrqxjdkeczscmo(int wnhyjpwdtswejz, string dtydoiegclmvx, bool jlmyius, int wjyiftmgzi, double venrvjkjmlry, int tzrmwdt, string xtzgwshgsihcg, double ldixcbvlsuhpvn) {
	int qomwhwtxsktmklq = 2501;
	int jikwshdlesxx = 1021;
	double bejjntccylrbqpv = 6719;
	bool wsecltfpp = true;
	string nqjvulnsnudsqq = "juksdnuaezianascjcgdzeunjxdfkgyndxuessmhvwzm";
	bool qozoela = false;
	string fmskdo = "liehtdnpwgzyundycjtdxcndcelzfxjyoacwpphthgspnbfblldcmgnavlmtcxfzubcdoirtzcxsgkelwxxczvnjxcbuwbnpche";
	string jylamm = "nwqdkkebpvhmpxmmzyeefzlnntnfcnrvhetbmjjaftdwbaoenbhdkajpldcpizgznptgshragloapngjxieohlookepxyro";
	double akoucrpialog = 6033;
	int smjwqrgdygiwwe = 7649;
	if (false != false) {
		int pawogj;
		for (pawogj = 93; pawogj > 0; pawogj--) {
			continue;
		}
	}
	if (string("juksdnuaezianascjcgdzeunjxdfkgyndxuessmhvwzm") == string("juksdnuaezianascjcgdzeunjxdfkgyndxuessmhvwzm")) {
		int talktmou;
		for (talktmou = 98; talktmou > 0; talktmou--) {
			continue;
		}
	}
	if (6033 == 6033) {
		int ilwawabeb;
		for (ilwawabeb = 91; ilwawabeb > 0; ilwawabeb--) {
			continue;
		}
	}
	if (1021 == 1021) {
		int llvk;
		for (llvk = 79; llvk > 0; llvk--) {
			continue;
		}
	}
	if (string("juksdnuaezianascjcgdzeunjxdfkgyndxuessmhvwzm") == string("juksdnuaezianascjcgdzeunjxdfkgyndxuessmhvwzm")) {
		int ftbfnmhs;
		for (ftbfnmhs = 23; ftbfnmhs > 0; ftbfnmhs--) {
			continue;
		}
	}
	return 34461;
}

int bzhsjnm::ggeqpuzfscywknjwapikey(bool lyxgyvhvty) {
	double zytaqnvwi = 5933;
	bool jlcfywkcwpwja = true;
	double fkbvvpmuw = 14747;
	double qmoxjcmkuhj = 4903;
	string arzobuhpfyt = "mmktrymuqdqbyziymyavaephzolvvynnfxaaewuymxscxfavljfngjesxqfdcjbwjude";
	double rwfhvfurmv = 4180;
	double vpdxotqztxydl = 34558;
	if (true == true) {
		int qov;
		for (qov = 24; qov > 0; qov--) {
			continue;
		}
	}
	if (34558 != 34558) {
		int qderiorzsb;
		for (qderiorzsb = 49; qderiorzsb > 0; qderiorzsb--) {
			continue;
		}
	}
	if (string("mmktrymuqdqbyziymyavaephzolvvynnfxaaewuymxscxfavljfngjesxqfdcjbwjude") == string("mmktrymuqdqbyziymyavaephzolvvynnfxaaewuymxscxfavljfngjesxqfdcjbwjude")) {
		int agobkwvng;
		for (agobkwvng = 82; agobkwvng > 0; agobkwvng--) {
			continue;
		}
	}
	if (14747 == 14747) {
		int hbtoii;
		for (hbtoii = 29; hbtoii > 0; hbtoii--) {
			continue;
		}
	}
	return 37117;
}

int bzhsjnm::bhetesmlvmivemoecfiekmaf(int xpqlkqhxyowy, double eebacyvayvpnbkp, int ibkkr, bool xcedowsrb, string wtlqbvyg, bool fttxtemwz, int mdpuazegs, int qzbjvxokaziw, double jjxmxn) {
	bool aiibgtybxefocfn = false;
	string mfjhhjgp = "wwgzfxxnojqagwhhvjxjianhhhrwgmwfwcykjqnpsvaojdmlbjlqwiifkxofofracjcfpmi";
	string uqldqxjzpl = "wzkinzccxtfmcchuvptpyeaegplpybetdgfuiibsxw";
	bool dirfjjvdiblkgl = false;
	if (false == false) {
		int xcmsv;
		for (xcmsv = 38; xcmsv > 0; xcmsv--) {
			continue;
		}
	}
	if (string("wzkinzccxtfmcchuvptpyeaegplpybetdgfuiibsxw") == string("wzkinzccxtfmcchuvptpyeaegplpybetdgfuiibsxw")) {
		int bp;
		for (bp = 10; bp > 0; bp--) {
			continue;
		}
	}
	if (false == false) {
		int frgofa;
		for (frgofa = 5; frgofa > 0; frgofa--) {
			continue;
		}
	}
	return 38812;
}

double bzhsjnm::dtxmayrudea(bool bcqhpt, double pitbq, int hmlqfs, double rkiznmt, bool geyjbebcrtn, string fmknawsdxq) {
	string rseyulpzfdacbh = "ptpyrtfkxsmxexltttclcfghknowkiwutfniyviweqhqujkaxiqyuycsafnmprxgoyphymwazllp";
	int qdahav = 1707;
	int dbaedp = 3009;
	string wyecxzr = "kxydnijqiqnqpryltfeorgfsw";
	int cukkot = 2583;
	double fqlalbvkdps = 1624;
	bool ffhdommkqjwseo = false;
	string lmeaxxhcgkjspp = "nqyvwqosxvufuf";
	if (string("kxydnijqiqnqpryltfeorgfsw") != string("kxydnijqiqnqpryltfeorgfsw")) {
		int lubvnryr;
		for (lubvnryr = 11; lubvnryr > 0; lubvnryr--) {
			continue;
		}
	}
	if (3009 != 3009) {
		int vyoxkpssm;
		for (vyoxkpssm = 57; vyoxkpssm > 0; vyoxkpssm--) {
			continue;
		}
	}
	if (3009 == 3009) {
		int gaawsfd;
		for (gaawsfd = 88; gaawsfd > 0; gaawsfd--) {
			continue;
		}
	}
	if (string("kxydnijqiqnqpryltfeorgfsw") == string("kxydnijqiqnqpryltfeorgfsw")) {
		int nqcgyxvp;
		for (nqcgyxvp = 46; nqcgyxvp > 0; nqcgyxvp--) {
			continue;
		}
	}
	if (string("kxydnijqiqnqpryltfeorgfsw") == string("kxydnijqiqnqpryltfeorgfsw")) {
		int gxe;
		for (gxe = 44; gxe > 0; gxe--) {
			continue;
		}
	}
	return 5558;
}

int bzhsjnm::cvzhmunhcrntoqvuntty(bool ztozcwn, bool qsaflbgigh) {
	int ngykrvy = 4841;
	bool odqurgeuszfme = false;
	int belgxigjty = 6203;
	double qyethcvbvkzsutr = 6008;
	int wxoqinaayrduja = 385;
	string vadnarrfkzjf = "pzbflvtufmuaodpuiomzzigbuzzyls";
	string gkerwcwqqnpnuf = "lutsyama";
	return 62986;
}

bool bzhsjnm::wbyjdcjenm(string ntqareawwktfugz, bool pqrmskiy, bool fsgsofc, int nvmzsgom, double bshmiknyulnkdpn, string pvwupbg, int cqslypty) {
	bool vsrxzd = false;
	int zceacvcmokwimqe = 826;
	int hzdndaghsuoz = 6918;
	string uuhlkhip = "addjcojpy";
	bool fenotyrbsxaym = false;
	return true;
}

int bzhsjnm::mdqryoflxbovorkgsdvbel(double tblxtg, string knmxfdlznssrzs, int nmkgcn, int wxsnbxh, string dirzlckvqsehk, string qtlmqz, bool joojrbydwmpoee, double jscwgu, string pikvpyrcmxnpcbb, double bekiiluq) {
	double pdxstp = 25386;
	bool aikrzf = false;
	string qqamdutwzkbtd = "zdaqxudwtptfstqrlbimxfjfd";
	string qbbuwip = "ocofvrwdrcfbphpnvreswosryeognelyzjzemgxagpytlwxhvepsivctlbrfftokqhxow";
	int tuwtfhqlxqyxzbv = 850;
	double ehchl = 2860;
	double wqqgl = 19293;
	string gwxqcx = "nggpfhf";
	if (2860 != 2860) {
		int hubpjv;
		for (hubpjv = 92; hubpjv > 0; hubpjv--) {
			continue;
		}
	}
	if (string("zdaqxudwtptfstqrlbimxfjfd") != string("zdaqxudwtptfstqrlbimxfjfd")) {
		int muytfl;
		for (muytfl = 13; muytfl > 0; muytfl--) {
			continue;
		}
	}
	if (850 == 850) {
		int txxyokvhto;
		for (txxyokvhto = 45; txxyokvhto > 0; txxyokvhto--) {
			continue;
		}
	}
	if (false != false) {
		int zxokdmjxt;
		for (zxokdmjxt = 92; zxokdmjxt > 0; zxokdmjxt--) {
			continue;
		}
	}
	return 19890;
}

bool bzhsjnm::kismsrqibwwnayoqcsd() {
	double dqkkcivigcl = 5849;
	int ogtsoctdcr = 3588;
	bool wqetzdqk = true;
	bool obidddpznxmzlx = true;
	bool lkepwmq = true;
	int iwqwdlsjxuj = 159;
	int jqgwt = 4866;
	if (true == true) {
		int vwlwpyz;
		for (vwlwpyz = 100; vwlwpyz > 0; vwlwpyz--) {
			continue;
		}
	}
	if (5849 != 5849) {
		int fymea;
		for (fymea = 47; fymea > 0; fymea--) {
			continue;
		}
	}
	if (3588 == 3588) {
		int vq;
		for (vq = 98; vq > 0; vq--) {
			continue;
		}
	}
	return true;
}

bzhsjnm::bzhsjnm() {
	this->bhetesmlvmivemoecfiekmaf(7336, 67529, 5810, false, string("rdkf"), true, 8406, 1835, 1543);
	this->dtxmayrudea(false, 84343, 3162, 62236, false, string("xgbbikjjfkytrsphdmbl"));
	this->cvzhmunhcrntoqvuntty(false, false);
	this->wbyjdcjenm(string("yufctsuzaetbrkwkfcolbyonyuierpgztbqtxfznbkhlebelfh"), true, true, 1421, 13725, string("jialcopkelvfwakfacixbuufuclfpphxuqvgnpzjwpejyzgtztzfoaotvgxtlkiavgckrfvttervznnbbbczsf"), 2566);
	this->mdqryoflxbovorkgsdvbel(6255, string("kimmd"), 1669, 594, string("ldrzygstkzfwtdmedalbvhfzwbvyccikxiptictbyckuyclpnswchsnuccdreusjeulyrgxjxjqzbhwirqy"), string("ogstgwstriprlfjqdgxhqjieodmmqbyeplbnyjxpedkdv"), false, 17001, string("jddycqbtpxcfoowgpvgvoucuzujtxeszdearzbovukvyksxabengrsxqyjuvns"), 6072);
	this->kismsrqibwwnayoqcsd();
	this->cndzenvymockjrngw(21032, string("ajpijsyjwvlnzaapahkcrzvlrdjupv"), 5687, 1707, string("gjxosh"), 7143, 32691, 6776, string("mvslby"), 34077);
	this->kyqagzynlmyihan(934, true);
	this->mrrnjlriyivtdpnkyxg(8845, string("lndesplrcnhyqjrntwbzdgeiztrlodpgfjiklooskjcgrrbvefvyopohopdwfbtuwqnlikjvnkkriequqgpdiko"), true, 3855, 26941, 11119, 6468, 6250, string("hrxuifvnvkcctqwbftycqdajtidvzwycynidpgldmiqvrivnpc"));
	this->wklvvnwltglloipbnqhw(true, string("dzshzqhrjauqlaiqmgwoaoivmrfqoregmzvrtexsoimavbdojjtmxyyvwondfskzkutffoksbhhghmbwhsztucf"), false, string("uekppjjwzjjkngcngpxmdtgyworqpmlfitjjyvqecgvahfqnwpahpexvlpebliwpguvqdueovzkpclr"), 67209, 6, true);
	this->lzacamrduqlbdiplesrfk(5719, 7835);
	this->sbpjyfsenl(799);
	this->oybypgneyfioxinyjwpeajjsz(8285, 166, true, false, 2896, 2206, string("eipzoswfvhiefqofytgqfaab"));
	this->ujiuencrqxjdkeczscmo(7273, string("pvauwuiyznanobezaqqgojubzhpvowlpebikyiyelbabawxqapemuhuu"), false, 5084, 5526, 520, string("klnymkennfkielplfhlpgliczfnkpwjngaqttfuslhkgbeqervhpy"), 15385);
	this->ggeqpuzfscywknjwapikey(false);
	this->dwddimijydzhkuf(string("bzglbysoqwebgayfxfyvqpavxqvhfwbepquziggyqhdzojvheepmeburguxnimtx"), 3160);
	this->frlgrapzszljouzfb(82707, true, string("erdhtltbutpiwfgxilwirjmprtuvtptoqduwvssgurhlrqlkmxhjzyopullsqxhvmaky"), string("fppzznexdpsevmmwojpbyuicrqkeowkkiwwutzffh"), 6521, 4049, 1756, true, string("urkfya"), string("hepqldfjynzwfasnganyfvxivxbfjydkdmn"));
	this->gqjieinnhudjszyruzuyn(2549, string("etbcnvpmzydxxoybleghargbdezaivctdaofzfejvzdfagyrclqhhxxyfuogxunmnantpbhgegghaompkvvdgmocnxr"), 4449, string("acamkrawpnqbvdrvfqcripp"), string("yvpciifxntyjxrouecyohxkhqinheogevprdwzqihbls"));
	this->lhcxlboybykopz(2171, 22967, true, string("tikmtpzbwhwjpnbuaflreecddkiqlhkujzxroccyseuvhthgjuheeugbcuhvaxnapdafrnosundiaevsujizvl"), string("jglibkoyhuhpxtnngruszsjgnqmbimxmrbahcpjikfbtjbgmvlmzhucrduldvxdsdhczrzubnuuzprrzexumogmtrkutjcoa"), 54289, false, string("sbvxzifyyxjjgbhejssnicerioijqhfbcc"));
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ntsjpac {
public:
	string mkbdkmnyjidbouc;
	int cdgdff;
	string tgrkjbypi;
	ntsjpac();
	bool rdjrfpsoobndjcrclvobiiu(string vmhozv);
	bool zribjtvicneofvq(string dkfrbxczedzww, string pqgorfirnovyudo, bool uyifylqsuae, string vxxgnnzugzb, bool swchutgzl, bool tteqhrgfldke);
	double wquzfhuxclukpazr(double kbjscth, string jmimmozueorlpq, int spcryvebg, int gqixadvay, string ewpbnoyxyxdatzm, int hdkbbcvzhr);
	bool zbxyyjovwfqzw(string aounaxeascmeco, int ubbrnnomm, bool jrgzyboiexlgmzb, string ondrpla, double vwpexkuqztih, string aeqjbkmxxehbr);
	double ssnqinezqloqv();

protected:
	bool xurogwd;

	void nmmzszvxuyuiia(double yyzakgh, bool dyajbm, double yahwhpt, int ssebmyxom);
	double jjujokmvyvzwelzxerlnwmz(bool fbgdlszzxpxixnd);
	bool nkuhumkpqgakkiihfabqjby(bool hebrqfizsq, bool kaeswfwls, string kkbjlnupznoa, bool mvygxln, int qecddnrsu, bool xthvw);
	int behqoharinwyzhkyx(bool vfgzbeqjmglrywn, bool dptinseza, string igjpxstuuc, string xssdca, int ydvvz, double vyuaqylbsd, int sgzpqhtfvyc);

private:
	bool kzoqepacwmnfkv;
	bool ociaje;
	bool zunuhuizgzynn;
	bool lxilrbh;

	void jepgikcwodkpwu(double dpnpxmezft, bool gogeocrxoqrbvx, string luhfprqakbm, bool znztuvumykt, double yygzvslcxj, bool dkkfpw, double zdmvvfkek, int lsmnhshs, bool gcyypiql);
	string bjydmobrvyjjlc(string sbhmehikhoprfqe, string olvzvu, bool kbslfpzxcs, int mqjplvrbcgnzrd);

};


void ntsjpac::jepgikcwodkpwu(double dpnpxmezft, bool gogeocrxoqrbvx, string luhfprqakbm, bool znztuvumykt, double yygzvslcxj, bool dkkfpw, double zdmvvfkek, int lsmnhshs, bool gcyypiql) {
	bool anbuucnhuaubjby = false;
	string nmjujgrngsw = "noufhbnjjurnlyglpugnqoetmnvdt";
	double xnoqnwdg = 7347;
	int mqdkiosxmz = 975;
	int ghbbu = 1984;
	int yjfcnyltojyxe = 2203;
	string gilqmoxmp = "enhithlsmcvkyyhmrkntwfznetnpxzum";
	bool kxvbwne = false;

}

string ntsjpac::bjydmobrvyjjlc(string sbhmehikhoprfqe, string olvzvu, bool kbslfpzxcs, int mqjplvrbcgnzrd) {
	string bsgiwhkwjxiicdh = "qzcyobnnjzptelqligii";
	string mkcfxgllxwlipom = "pdcynsvdibuiicxeqqiboiozgztbdrhxmeuilfibvszlklxvyzgddnhegjvcjmikztevloty";
	int umeisxfbx = 2547;
	int mmyelpfkgthb = 769;
	int weyjsed = 203;
	bool oxwnymqml = false;
	bool huzehw = false;
	double eohsn = 5312;
	return string("pgovnjxywgmal");
}

void ntsjpac::nmmzszvxuyuiia(double yyzakgh, bool dyajbm, double yahwhpt, int ssebmyxom) {
	string zbamoi = "vjmlbnmnkbyzgfolvfdmvrfjgfagqinoggvznzcbnyeo";
	bool rzvcsgr = false;
	string xqqpti = "esdpsqxpuiashndkwrbnyjlakdotwzjkyzlvxmxivheqvxbwrcwlhwjdcbnrbos";
	double jssyld = 17565;

}

double ntsjpac::jjujokmvyvzwelzxerlnwmz(bool fbgdlszzxpxixnd) {
	int psfwgstdpt = 6381;
	string ccgozmbotyu = "celnankubjs";
	if (string("celnankubjs") == string("celnankubjs")) {
		int syw;
		for (syw = 99; syw > 0; syw--) {
			continue;
		}
	}
	if (string("celnankubjs") != string("celnankubjs")) {
		int uvoiow;
		for (uvoiow = 26; uvoiow > 0; uvoiow--) {
			continue;
		}
	}
	if (6381 == 6381) {
		int erwyxwcx;
		for (erwyxwcx = 16; erwyxwcx > 0; erwyxwcx--) {
			continue;
		}
	}
	if (string("celnankubjs") != string("celnankubjs")) {
		int mfy;
		for (mfy = 5; mfy > 0; mfy--) {
			continue;
		}
	}
	return 58327;
}

bool ntsjpac::nkuhumkpqgakkiihfabqjby(bool hebrqfizsq, bool kaeswfwls, string kkbjlnupznoa, bool mvygxln, int qecddnrsu, bool xthvw) {
	string giucbbbrrzhsx = "pdozgwgmnszddthbnxhommoiuwarnsvpsdelevl";
	int fczzxoeabodfwrh = 660;
	return false;
}

int ntsjpac::behqoharinwyzhkyx(bool vfgzbeqjmglrywn, bool dptinseza, string igjpxstuuc, string xssdca, int ydvvz, double vyuaqylbsd, int sgzpqhtfvyc) {
	bool fkcsmz = false;
	double kmodmhzjpusa = 17418;
	bool nwrhl = true;
	bool nxtjoqplt = false;
	string bgclcbrha = "qkmgklefkzectybjdadzbrpwuorqzokeuxswzmagctxurdfowdllpbsmapwaoyrpdmsomfajkgaeof";
	int ukxzr = 1388;
	double idpupqw = 50539;
	if (1388 == 1388) {
		int jyao;
		for (jyao = 38; jyao > 0; jyao--) {
			continue;
		}
	}
	if (1388 == 1388) {
		int kr;
		for (kr = 81; kr > 0; kr--) {
			continue;
		}
	}
	return 93200;
}

bool ntsjpac::rdjrfpsoobndjcrclvobiiu(string vmhozv) {
	double cxxflnhzbi = 10242;
	int hnpobkxyzpql = 6976;
	int mnuic = 3575;
	double pycrdr = 27956;
	return false;
}

bool ntsjpac::zribjtvicneofvq(string dkfrbxczedzww, string pqgorfirnovyudo, bool uyifylqsuae, string vxxgnnzugzb, bool swchutgzl, bool tteqhrgfldke) {
	string catphpfk = "gxhzgbjsdxjascbxgjgygteqvatnyptyqhlfacbil";
	int dxevqkdbvgeiz = 4904;
	string zlojxpjg = "zvruqkbqeqkmbuhvnxwphlqubuscebxqjsvlilatbtpfmcpnefuykxyls";
	bool cciax = true;
	return false;
}

double ntsjpac::wquzfhuxclukpazr(double kbjscth, string jmimmozueorlpq, int spcryvebg, int gqixadvay, string ewpbnoyxyxdatzm, int hdkbbcvzhr) {
	double lgtikmua = 47678;
	bool megobopl = false;
	double etowirnlxg = 40348;
	int hsrlqgmxjq = 1516;
	int tarat = 1587;
	string opzvulxnr = "ynndiabnbnobtimwawccisykiavhsydzpywrwxrvytyasablcafnkgknpzccuhopd";
	bool vcvyszdvsn = false;
	int akbbknsgpbqvw = 4970;
	bool ktrsddehz = true;
	int iliccdvpgrwgvz = 3921;
	if (string("ynndiabnbnobtimwawccisykiavhsydzpywrwxrvytyasablcafnkgknpzccuhopd") != string("ynndiabnbnobtimwawccisykiavhsydzpywrwxrvytyasablcafnkgknpzccuhopd")) {
		int zezwrfufo;
		for (zezwrfufo = 49; zezwrfufo > 0; zezwrfufo--) {
			continue;
		}
	}
	if (1587 == 1587) {
		int pojvua;
		for (pojvua = 56; pojvua > 0; pojvua--) {
			continue;
		}
	}
	if (false == false) {
		int qgavbfi;
		for (qgavbfi = 48; qgavbfi > 0; qgavbfi--) {
			continue;
		}
	}
	return 58050;
}

bool ntsjpac::zbxyyjovwfqzw(string aounaxeascmeco, int ubbrnnomm, bool jrgzyboiexlgmzb, string ondrpla, double vwpexkuqztih, string aeqjbkmxxehbr) {
	double lylbgtvbqnyfp = 51149;
	if (51149 != 51149) {
		int zdy;
		for (zdy = 70; zdy > 0; zdy--) {
			continue;
		}
	}
	if (51149 == 51149) {
		int dboxk;
		for (dboxk = 36; dboxk > 0; dboxk--) {
			continue;
		}
	}
	return true;
}

double ntsjpac::ssnqinezqloqv() {
	bool stkkwpcgyl = true;
	double plxhbvvxytjd = 52701;
	bool ggchqgtdllrq = false;
	int wasfufzpmue = 2216;
	int hudack = 2052;
	string drmqpu = "jfbhlihiuflzpvbtqgerhxjcfmxbskxkblpgpznzdsdzloijbjzumaovkjrcgerbzuwhqwxbnaxjsnwktrsjbtzyrwskofrspscn";
	if (2052 == 2052) {
		int czrsnvc;
		for (czrsnvc = 11; czrsnvc > 0; czrsnvc--) {
			continue;
		}
	}
	if (52701 != 52701) {
		int ytmng;
		for (ytmng = 86; ytmng > 0; ytmng--) {
			continue;
		}
	}
	if (2052 == 2052) {
		int ffqwarfi;
		for (ffqwarfi = 6; ffqwarfi > 0; ffqwarfi--) {
			continue;
		}
	}
	return 1365;
}

ntsjpac::ntsjpac() {
	this->rdjrfpsoobndjcrclvobiiu(string("aawslmuxxgabfherreotedibpgihmhtkjebjlteuinrweoghdslhqjfvvdqiis"));
	this->zribjtvicneofvq(string("emugdxehjqenssoqrtgckajqemimggxfkdojtylhgznacdtynlooycesqseppndlkxgvmtnkvaxabym"), string("i"), true, string("pgkvpzqtkjcbb"), true, true);
	this->wquzfhuxclukpazr(26662, string("bewuqbtdxacpbikxkmkpqnkvf"), 665, 4985, string("hmkovfsmsworvuxllwejjamkj"), 3862);
	this->zbxyyjovwfqzw(string("ndoyerosfrvnvhcoocvdlgdzmnkzmeriimsftvrewcryvqhvjdmvz"), 3913, false, string(""), 6157, string("jclzisiikuxjuuqa"));
	this->ssnqinezqloqv();
	this->nmmzszvxuyuiia(50789, true, 13745, 971);
	this->jjujokmvyvzwelzxerlnwmz(true);
	this->nkuhumkpqgakkiihfabqjby(true, true, string("qetgucphpyanlopbsllqmvzfcyrgnlvmhivsercgfqqquhugkxivgypqbphsmxoaimp"), true, 3114, false);
	this->behqoharinwyzhkyx(false, false, string("nrfsbrgxuovvufbncgmfzvuiivangvmuwlm"), string("gpwcetkyayoldernnbfnpfodmkcreyhyijsotdwwo"), 2766, 33207, 4445);
	this->jepgikcwodkpwu(25084, true, string("afhfkuladtkgylfp"), true, 35963, true, 21679, 748, false);
	this->bjydmobrvyjjlc(string("kqchbajjkdhhecovsiimsarlwxafqqrctyssnkcapnfffegzojsjkrcwmbpusuzbnytebjyjpazg"), string("cpmvoahppwflsedibgscdcnjhiqrrrvkkfnk"), false, 2581);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class vpmmheu {
public:
	bool swkteefu;
	int uegkvo;
	string xgmfwzqfsbp;
	double nfqwrm;
	vpmmheu();
	string hownntdebrvvxvumndd(string uxkbdepmdrgmuf, int uthvgtyejitczqz, string dkhibt, bool veblhbrvbjmumv);
	void svxtfdmaghhpvnekbcfgwpyyj(string mplcjt);

protected:
	string jolxe;
	bool qxdxojvtn;
	string ovhocxtcakzhan;

	string bvflexskkzljwskyz(double aazuqrccev);
	string mhwkjdfbobplsrorbnivfgk(int zlcjmqrubl, double esgpnmjoi, double vrvpkyrqnpwfze, bool qszeixekdbgf, bool qzofks);
	int hvaaenyaywueiurxanc(string hlshm, double nqxwmfcqrbfpr, double odeutd, string anarokpkrwfvlyf);
	string khmgdsgtjrtynpwpyib(bool rfwqkmvm, bool wzypkcszoayxeor);
	string oriqwjnxxnrspymsdjmsnlfo(bool nsvinqz, double fxutws, bool gmchqwvisumlo, int oihjfdvvocvb, bool gpxgeaynmb);

private:
	string nszyedej;
	string aohmsbfdiuljm;
	bool ykqtpqwu;
	int cnuwwkmlanwc;

	string xxmqhvehhwhnq(int mmgaabgqsjcc);
	bool fikhfxxtmpvgi(int zzoheefuhykxdkc, double avbofehh, int omwgqh);
	double wbaartngfnpzglh(string vpprgm, string nlmymlisrzq, int wlyktxovei, double vnfviunurkmbe, int ojgslh, bool rjrodlpntc, bool qjinrksy, string ljvivpfveum);
	string adowlahqtnioi(double vlqxpiluf, double dwfyo, double ghuapucvzyhjq);
	void oexlfuvxdlfb(bool vollhxfikavc, string efoounlcandvlgf, bool tptlqhegeapkqbk, bool gvyzq);

};


string vpmmheu::xxmqhvehhwhnq(int mmgaabgqsjcc) {
	int jroomxy = 3883;
	bool tmdbzfpzwd = false;
	int prkqonkp = 6890;
	bool hwwchxapogugv = true;
	double ubtvler = 80107;
	int xnqtjoxkmv = 8474;
	if (80107 != 80107) {
		int vr;
		for (vr = 91; vr > 0; vr--) {
			continue;
		}
	}
	if (80107 != 80107) {
		int uhjjsriy;
		for (uhjjsriy = 36; uhjjsriy > 0; uhjjsriy--) {
			continue;
		}
	}
	return string("");
}

bool vpmmheu::fikhfxxtmpvgi(int zzoheefuhykxdkc, double avbofehh, int omwgqh) {
	int kdxbuvbdw = 5468;
	bool afdjn = false;
	bool lvsizwtywkroxv = true;
	if (true != true) {
		int lfor;
		for (lfor = 13; lfor > 0; lfor--) {
			continue;
		}
	}
	if (true != true) {
		int elbnk;
		for (elbnk = 45; elbnk > 0; elbnk--) {
			continue;
		}
	}
	if (5468 != 5468) {
		int witosa;
		for (witosa = 98; witosa > 0; witosa--) {
			continue;
		}
	}
	if (false != false) {
		int bijebl;
		for (bijebl = 80; bijebl > 0; bijebl--) {
			continue;
		}
	}
	return false;
}

double vpmmheu::wbaartngfnpzglh(string vpprgm, string nlmymlisrzq, int wlyktxovei, double vnfviunurkmbe, int ojgslh, bool rjrodlpntc, bool qjinrksy, string ljvivpfveum) {
	double dztsifpadgf = 14164;
	string cypkb = "desvafhjumsxftziiesljzcilzglofhlspjxbgthkxfxxzfdvlcjcjehvrsvxfikurourthsaqfgztseczvusfeadxoev";
	int gyhcy = 6254;
	if (6254 != 6254) {
		int chqx;
		for (chqx = 5; chqx > 0; chqx--) {
			continue;
		}
	}
	if (14164 != 14164) {
		int njrcnxa;
		for (njrcnxa = 13; njrcnxa > 0; njrcnxa--) {
			continue;
		}
	}
	if (6254 != 6254) {
		int fmhmoono;
		for (fmhmoono = 100; fmhmoono > 0; fmhmoono--) {
			continue;
		}
	}
	if (6254 != 6254) {
		int nxzifc;
		for (nxzifc = 68; nxzifc > 0; nxzifc--) {
			continue;
		}
	}
	return 88694;
}

string vpmmheu::adowlahqtnioi(double vlqxpiluf, double dwfyo, double ghuapucvzyhjq) {
	double kbijenainzimatb = 55714;
	int qoitaqadr = 7661;
	int pairxdncm = 5511;
	bool lpgtmgcqqmang = false;
	if (55714 != 55714) {
		int akrlv;
		for (akrlv = 50; akrlv > 0; akrlv--) {
			continue;
		}
	}
	return string("tgdkrgbbyem");
}

void vpmmheu::oexlfuvxdlfb(bool vollhxfikavc, string efoounlcandvlgf, bool tptlqhegeapkqbk, bool gvyzq) {
	string uedsjlobylty = "heoubbbgvaiwlhoocalxoozgsfwzxkgbhcyatwrzlevxhyijyonxtmkkhecsjjnomftmacquyvuw";

}

string vpmmheu::bvflexskkzljwskyz(double aazuqrccev) {
	string zvadu = "ncsievixbzhfhnkkq";
	if (string("ncsievixbzhfhnkkq") == string("ncsievixbzhfhnkkq")) {
		int hfa;
		for (hfa = 5; hfa > 0; hfa--) {
			continue;
		}
	}
	return string("dwmcxuuhmix");
}

string vpmmheu::mhwkjdfbobplsrorbnivfgk(int zlcjmqrubl, double esgpnmjoi, double vrvpkyrqnpwfze, bool qszeixekdbgf, bool qzofks) {
	double msasoqvqp = 22073;
	string rqaun = "nnusfm";
	bool hnemei = true;
	string qsliayyb = "twspjgrfmvjbxwmudggrfrxvnyzvbpjsvkxitzudeqvmzzfb";
	int jnjhe = 1941;
	int scqxmqp = 2784;
	string tavxyb = "oiolxotklgsatrwedpouhjgtizosswldiefusprtjjpaqwhdnccxorycsdvjjlrzpfyyfpvcdxoiabnfuqa";
	string kgwznpvh = "pmjjfz";
	int klpxru = 3254;
	int ztetlqnyjfeazol = 836;
	if (string("pmjjfz") == string("pmjjfz")) {
		int boxl;
		for (boxl = 6; boxl > 0; boxl--) {
			continue;
		}
	}
	if (string("twspjgrfmvjbxwmudggrfrxvnyzvbpjsvkxitzudeqvmzzfb") != string("twspjgrfmvjbxwmudggrfrxvnyzvbpjsvkxitzudeqvmzzfb")) {
		int hutdjpokk;
		for (hutdjpokk = 94; hutdjpokk > 0; hutdjpokk--) {
			continue;
		}
	}
	return string("tyiq");
}

int vpmmheu::hvaaenyaywueiurxanc(string hlshm, double nqxwmfcqrbfpr, double odeutd, string anarokpkrwfvlyf) {
	double ogvtehebegqdji = 61011;
	string veeloarqbnfyjup = "fwcwugsssqmhcklvgalpdyoogkze";
	string wnkpd = "cpqdxirgizguifcsttudwkiuxkofzvllruvtlmmcuoizgfhollydzmraemgmxdozhvion";
	double bzrgnibax = 12311;
	if (12311 == 12311) {
		int cf;
		for (cf = 77; cf > 0; cf--) {
			continue;
		}
	}
	if (12311 != 12311) {
		int vnltfjinxo;
		for (vnltfjinxo = 76; vnltfjinxo > 0; vnltfjinxo--) {
			continue;
		}
	}
	if (string("fwcwugsssqmhcklvgalpdyoogkze") != string("fwcwugsssqmhcklvgalpdyoogkze")) {
		int gygprxv;
		for (gygprxv = 68; gygprxv > 0; gygprxv--) {
			continue;
		}
	}
	if (12311 != 12311) {
		int uokuomwzk;
		for (uokuomwzk = 84; uokuomwzk > 0; uokuomwzk--) {
			continue;
		}
	}
	if (12311 != 12311) {
		int pk;
		for (pk = 95; pk > 0; pk--) {
			continue;
		}
	}
	return 67769;
}

string vpmmheu::khmgdsgtjrtynpwpyib(bool rfwqkmvm, bool wzypkcszoayxeor) {
	string jcedz = "lkmwskzitvxvnzboziykcbtipzlpmdotbviesjtnorspzzfrqxljypygnaobmwuplynyccoobatop";
	string cnxshhwqdmauijj = "gfwtgazcvxstysdupdipmxqxpbkncninmdfpatqzwndvnlqpmpzhzjfguhqkmxkkyox";
	if (string("lkmwskzitvxvnzboziykcbtipzlpmdotbviesjtnorspzzfrqxljypygnaobmwuplynyccoobatop") == string("lkmwskzitvxvnzboziykcbtipzlpmdotbviesjtnorspzzfrqxljypygnaobmwuplynyccoobatop")) {
		int ktcufnlp;
		for (ktcufnlp = 39; ktcufnlp > 0; ktcufnlp--) {
			continue;
		}
	}
	if (string("gfwtgazcvxstysdupdipmxqxpbkncninmdfpatqzwndvnlqpmpzhzjfguhqkmxkkyox") == string("gfwtgazcvxstysdupdipmxqxpbkncninmdfpatqzwndvnlqpmpzhzjfguhqkmxkkyox")) {
		int eyvvyqw;
		for (eyvvyqw = 92; eyvvyqw > 0; eyvvyqw--) {
			continue;
		}
	}
	if (string("lkmwskzitvxvnzboziykcbtipzlpmdotbviesjtnorspzzfrqxljypygnaobmwuplynyccoobatop") == string("lkmwskzitvxvnzboziykcbtipzlpmdotbviesjtnorspzzfrqxljypygnaobmwuplynyccoobatop")) {
		int ucutv;
		for (ucutv = 70; ucutv > 0; ucutv--) {
			continue;
		}
	}
	return string("mnuja");
}

string vpmmheu::oriqwjnxxnrspymsdjmsnlfo(bool nsvinqz, double fxutws, bool gmchqwvisumlo, int oihjfdvvocvb, bool gpxgeaynmb) {
	bool jjzbpcbgcscbxf = false;
	double hmbnwacdmtdpme = 1748;
	string ptzofdjnpgto = "kuunmencbcitvfuryauyoghsowjsyxxfdwpoxuxdvlvqbswmo";
	bool hckzixz = true;
	bool cqnhflndz = false;
	if (false != false) {
		int rwqzlgutv;
		for (rwqzlgutv = 51; rwqzlgutv > 0; rwqzlgutv--) {
			continue;
		}
	}
	if (true == true) {
		int zagqvud;
		for (zagqvud = 34; zagqvud > 0; zagqvud--) {
			continue;
		}
	}
	if (false != false) {
		int cxjgbfaelk;
		for (cxjgbfaelk = 11; cxjgbfaelk > 0; cxjgbfaelk--) {
			continue;
		}
	}
	if (false == false) {
		int ddwcsfc;
		for (ddwcsfc = 14; ddwcsfc > 0; ddwcsfc--) {
			continue;
		}
	}
	if (1748 == 1748) {
		int kqg;
		for (kqg = 16; kqg > 0; kqg--) {
			continue;
		}
	}
	return string("hsw");
}

string vpmmheu::hownntdebrvvxvumndd(string uxkbdepmdrgmuf, int uthvgtyejitczqz, string dkhibt, bool veblhbrvbjmumv) {
	double kbvcaf = 39457;
	string muwcyzskue = "zymeunoblzmhrxnbsfwrgayrwprepxqsvdndhawflzeugmhaijwfxa";
	bool ckpqlec = false;
	double xiroun = 48188;
	bool tlbbn = false;
	bool pvjyhlpywa = true;
	string ilcaq = "waaigfjeugkgowavybdpwnclbttcpeothlirvcvnunvrmxrtydrdjkaiyukinuzztdzavbaoftjjiwnnqjklhq";
	string qflyztekmjudefa = "ybwnirvjqmvexyteqnrykgkwhrbvdbaxijafuhtytgdszjp";
	int knjrn = 620;
	if (620 == 620) {
		int jue;
		for (jue = 64; jue > 0; jue--) {
			continue;
		}
	}
	if (string("waaigfjeugkgowavybdpwnclbttcpeothlirvcvnunvrmxrtydrdjkaiyukinuzztdzavbaoftjjiwnnqjklhq") == string("waaigfjeugkgowavybdpwnclbttcpeothlirvcvnunvrmxrtydrdjkaiyukinuzztdzavbaoftjjiwnnqjklhq")) {
		int jswwkizuy;
		for (jswwkizuy = 49; jswwkizuy > 0; jswwkizuy--) {
			continue;
		}
	}
	if (false != false) {
		int flvk;
		for (flvk = 13; flvk > 0; flvk--) {
			continue;
		}
	}
	if (false == false) {
		int hjbgxwrs;
		for (hjbgxwrs = 9; hjbgxwrs > 0; hjbgxwrs--) {
			continue;
		}
	}
	if (string("zymeunoblzmhrxnbsfwrgayrwprepxqsvdndhawflzeugmhaijwfxa") != string("zymeunoblzmhrxnbsfwrgayrwprepxqsvdndhawflzeugmhaijwfxa")) {
		int ithuryym;
		for (ithuryym = 9; ithuryym > 0; ithuryym--) {
			continue;
		}
	}
	return string("gizdhdscfem");
}

void vpmmheu::svxtfdmaghhpvnekbcfgwpyyj(string mplcjt) {
	string tctabnuvn = "uffxznrgqsstglvedxtnnsijhoyfxszvugaqbpxlxohbrqdisnytqebutmgdrlzjoxkdohn";
	double swkrnxh = 47215;
	string yotaxff = "hfrkuzdyfsnyinomwjqvherkehayehasbqylpexb";
	if (string("hfrkuzdyfsnyinomwjqvherkehayehasbqylpexb") != string("hfrkuzdyfsnyinomwjqvherkehayehasbqylpexb")) {
		int dd;
		for (dd = 29; dd > 0; dd--) {
			continue;
		}
	}
	if (string("hfrkuzdyfsnyinomwjqvherkehayehasbqylpexb") != string("hfrkuzdyfsnyinomwjqvherkehayehasbqylpexb")) {
		int ebscvn;
		for (ebscvn = 13; ebscvn > 0; ebscvn--) {
			continue;
		}
	}
	if (47215 == 47215) {
		int ynewhu;
		for (ynewhu = 1; ynewhu > 0; ynewhu--) {
			continue;
		}
	}
	if (string("uffxznrgqsstglvedxtnnsijhoyfxszvugaqbpxlxohbrqdisnytqebutmgdrlzjoxkdohn") == string("uffxznrgqsstglvedxtnnsijhoyfxszvugaqbpxlxohbrqdisnytqebutmgdrlzjoxkdohn")) {
		int yimae;
		for (yimae = 41; yimae > 0; yimae--) {
			continue;
		}
	}
	if (string("uffxznrgqsstglvedxtnnsijhoyfxszvugaqbpxlxohbrqdisnytqebutmgdrlzjoxkdohn") != string("uffxznrgqsstglvedxtnnsijhoyfxszvugaqbpxlxohbrqdisnytqebutmgdrlzjoxkdohn")) {
		int usgtt;
		for (usgtt = 9; usgtt > 0; usgtt--) {
			continue;
		}
	}

}

vpmmheu::vpmmheu() {
	this->hownntdebrvvxvumndd(string("imvihyiz"), 3995, string("czrutcxbkulvuwidmtxpuqlodxdiocydrvvfgshwff"), true);
	this->svxtfdmaghhpvnekbcfgwpyyj(string("dndhuwmijqubvpdipdpzvnwgdfzokyierdfcnvfwubbqtrqifvacoioangd"));
	this->bvflexskkzljwskyz(31192);
	this->mhwkjdfbobplsrorbnivfgk(3877, 35105, 70558, true, false);
	this->hvaaenyaywueiurxanc(string("zxwu"), 44787, 27396, string("eulk"));
	this->khmgdsgtjrtynpwpyib(false, false);
	this->oriqwjnxxnrspymsdjmsnlfo(false, 47396, false, 457, false);
	this->xxmqhvehhwhnq(3047);
	this->fikhfxxtmpvgi(1412, 11573, 2186);
	this->wbaartngfnpzglh(string("fdjeiepzirursurxazinkdlwcrdrqhcnplpfrsemtpcxjjlpbrnlhoxtqpzhemf"), string("mtuawmzztblpdmgcqnlwbzlsggaxmljfheljawdzincoqfhgpvzvnbvfrfoxkhjrxmehoxfyrzuzfea"), 2900, 16413, 3086, false, false, string("hjzaidvdlintwkecxqcwqdtumnylqgjbksnqdoatxelqevrofykehqlajzyinpx"));
	this->adowlahqtnioi(67997, 11420, 8479);
	this->oexlfuvxdlfb(true, string("poygaugfkaikt"), true, false);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class tyaxjgr {
public:
	double kjcssombv;
	int xhuvy;
	tyaxjgr();
	int zqqcwcvjkpyguzlbvkctec(int dgnobxxtkdg, double xuwkzwmdcfpws);
	double ygljzwuezfetsdgra(double gsznshazrftr, double ujcyvtj, int dirxllvyop, int tatmuhnkugmdium, double qoxjfuqh);

protected:
	int oyffaeyy;
	string ilmsogyrzsfv;
	string skbkdnigyaohoug;

	bool otwxyztxxosax(int scxkytycy, string mqiitcmfls);
	void iegwyqipqjyncoiwvq(bool zltxgthgy, string utcxlmjemjgtmd, string nllnfdezdcyz, int lwjmjoahwx, bool iahhvfiikvt, double eimnh);
	double fhxtdxcquxaeelxgxrhto();
	string yhyaofyavrfvkjmrkbqxku(double ghdmhqoyn, double pwohpuwofo, string dpoqhpyvapvgn, bool zwdews, double ezkiiyr, double ftwlvfqqa, int rcpkne, double kvvjdovearahkb, string ognafugmvsuzcb);

private:
	double qukxiowvarbdnrb;
	int lwwwm;
	int evjxsmcvsetj;
	int qdoseqljsycjujl;

	int gtuymxqvafgpblfqx();
	string iwyykhegenzztqbawhbjtgq();
	bool xuewxjpnal(double uyzhkutlass, bool hqgpmvni, int vntlzymcsc, string amdsrmod, string ulgaeb, double ouzcj, string uzaxzurpdeklc, int xoovjxxs);
	int lofnizgisrjxbdkplprq(bool ytwcpebflc, double wavlqt, int yekwsg, string hpfgizwzdm, int ghnbzfjhlknqwyi, double rjboauohb, bool vsmctzqubogaqg);
	int yxfdkfvpvddvjmqd();
	double bgfyiyxtjqkwelosdvfokjjb(bool pjtsbdujrccd);
	string nivsldlwvltxatkkw(bool ibyzgvwbsf, bool jurzjynmr, int spgsxxlxz, double ltnia, double gijeqg, string cugjnylurmqhss, double bdjbrngi, int oooebnseyrgzynv, string ubbedxnwxrlt, string qblxxtdgcknv);
	void zytnervaitj(bool mbnsbkio, int ukycmn);
	int uqchecrgoqxxsuzs(int fccoyuhv, double qnbxeqtmevghm, string sznsyn, double qxuvnawkq);
	string phusvarrvwsluynxscqotgpd(string uakowjeaa, int yelhmtkyup, bool lnmchvsfw);

};


int tyaxjgr::gtuymxqvafgpblfqx() {
	double olfzleipcxm = 54712;
	if (54712 == 54712) {
		int xsq;
		for (xsq = 88; xsq > 0; xsq--) {
			continue;
		}
	}
	if (54712 == 54712) {
		int nrc;
		for (nrc = 92; nrc > 0; nrc--) {
			continue;
		}
	}
	if (54712 != 54712) {
		int zkziwpqwua;
		for (zkziwpqwua = 9; zkziwpqwua > 0; zkziwpqwua--) {
			continue;
		}
	}
	return 9909;
}

string tyaxjgr::iwyykhegenzztqbawhbjtgq() {
	double ggravpp = 40929;
	int ioxrmleyx = 1654;
	bool nferkyewb = false;
	int kjrips = 1639;
	int cyvbkvdhpazx = 1135;
	bool lzfzdkomdg = true;
	string bsbpy = "pinfnpqyqrugcyaflytvwsbaqgkqxooa";
	string uaeqcadpkce = "stjanvvsumwftgycyxipufbrlubprckfableogonceqniqfxiocdboquzsgegnxpexdiialgoeayvqsyqlvpcadj";
	if (string("pinfnpqyqrugcyaflytvwsbaqgkqxooa") != string("pinfnpqyqrugcyaflytvwsbaqgkqxooa")) {
		int bdt;
		for (bdt = 64; bdt > 0; bdt--) {
			continue;
		}
	}
	if (1135 != 1135) {
		int mjw;
		for (mjw = 56; mjw > 0; mjw--) {
			continue;
		}
	}
	if (1135 != 1135) {
		int jqdalx;
		for (jqdalx = 42; jqdalx > 0; jqdalx--) {
			continue;
		}
	}
	if (1654 != 1654) {
		int sppikewx;
		for (sppikewx = 47; sppikewx > 0; sppikewx--) {
			continue;
		}
	}
	return string("");
}

bool tyaxjgr::xuewxjpnal(double uyzhkutlass, bool hqgpmvni, int vntlzymcsc, string amdsrmod, string ulgaeb, double ouzcj, string uzaxzurpdeklc, int xoovjxxs) {
	string cedmdtj = "crwnlliodgvvhnsajdhljgfjgtsufdhfconbtiwswtevtzpukdrjixxfys";
	double glbssn = 6927;
	if (6927 == 6927) {
		int uvzpc;
		for (uvzpc = 97; uvzpc > 0; uvzpc--) {
			continue;
		}
	}
	if (6927 != 6927) {
		int wwkxm;
		for (wwkxm = 53; wwkxm > 0; wwkxm--) {
			continue;
		}
	}
	if (6927 == 6927) {
		int acigb;
		for (acigb = 22; acigb > 0; acigb--) {
			continue;
		}
	}
	if (string("crwnlliodgvvhnsajdhljgfjgtsufdhfconbtiwswtevtzpukdrjixxfys") != string("crwnlliodgvvhnsajdhljgfjgtsufdhfconbtiwswtevtzpukdrjixxfys")) {
		int osoljpvq;
		for (osoljpvq = 83; osoljpvq > 0; osoljpvq--) {
			continue;
		}
	}
	if (6927 != 6927) {
		int imut;
		for (imut = 70; imut > 0; imut--) {
			continue;
		}
	}
	return true;
}

int tyaxjgr::lofnizgisrjxbdkplprq(bool ytwcpebflc, double wavlqt, int yekwsg, string hpfgizwzdm, int ghnbzfjhlknqwyi, double rjboauohb, bool vsmctzqubogaqg) {
	string ntbsyfdnv = "zxzitzfpoajonuyovbgygilqshiflcoggwr";
	bool undhwouu = false;
	double gnzfk = 2826;
	double huqvdkyddywj = 9075;
	bool dyynqhi = true;
	double azgoqbnfwsh = 41082;
	if (9075 == 9075) {
		int aa;
		for (aa = 44; aa > 0; aa--) {
			continue;
		}
	}
	if (41082 == 41082) {
		int bxtmixptcd;
		for (bxtmixptcd = 26; bxtmixptcd > 0; bxtmixptcd--) {
			continue;
		}
	}
	if (2826 == 2826) {
		int hnzlqg;
		for (hnzlqg = 7; hnzlqg > 0; hnzlqg--) {
			continue;
		}
	}
	if (string("zxzitzfpoajonuyovbgygilqshiflcoggwr") == string("zxzitzfpoajonuyovbgygilqshiflcoggwr")) {
		int mkx;
		for (mkx = 7; mkx > 0; mkx--) {
			continue;
		}
	}
	return 46425;
}

int tyaxjgr::yxfdkfvpvddvjmqd() {
	int qbckeqjidcgl = 2022;
	string kpthtvlntd = "bfhxldmleigeezi";
	if (string("bfhxldmleigeezi") == string("bfhxldmleigeezi")) {
		int glwmntcenx;
		for (glwmntcenx = 73; glwmntcenx > 0; glwmntcenx--) {
			continue;
		}
	}
	if (2022 == 2022) {
		int whakylhwz;
		for (whakylhwz = 23; whakylhwz > 0; whakylhwz--) {
			continue;
		}
	}
	return 10875;
}

double tyaxjgr::bgfyiyxtjqkwelosdvfokjjb(bool pjtsbdujrccd) {
	double yjbfzuest = 42712;
	if (42712 != 42712) {
		int kalyympha;
		for (kalyympha = 31; kalyympha > 0; kalyympha--) {
			continue;
		}
	}
	if (42712 != 42712) {
		int vktvxl;
		for (vktvxl = 2; vktvxl > 0; vktvxl--) {
			continue;
		}
	}
	if (42712 == 42712) {
		int mav;
		for (mav = 49; mav > 0; mav--) {
			continue;
		}
	}
	return 5131;
}

string tyaxjgr::nivsldlwvltxatkkw(bool ibyzgvwbsf, bool jurzjynmr, int spgsxxlxz, double ltnia, double gijeqg, string cugjnylurmqhss, double bdjbrngi, int oooebnseyrgzynv, string ubbedxnwxrlt, string qblxxtdgcknv) {
	int znmbwbc = 1948;
	bool qtyxwqj = true;
	double rplnqnjysjyjns = 547;
	bool rmdnybbjpe = false;
	int onexzumiqqsal = 28;
	bool frwbmgtwknfnu = true;
	if (28 == 28) {
		int vbmnlzvu;
		for (vbmnlzvu = 2; vbmnlzvu > 0; vbmnlzvu--) {
			continue;
		}
	}
	if (true == true) {
		int dxfstoi;
		for (dxfstoi = 47; dxfstoi > 0; dxfstoi--) {
			continue;
		}
	}
	if (true != true) {
		int vhnwvlue;
		for (vhnwvlue = 100; vhnwvlue > 0; vhnwvlue--) {
			continue;
		}
	}
	return string("vxycmwuvfi");
}

void tyaxjgr::zytnervaitj(bool mbnsbkio, int ukycmn) {
	bool eyaxwpt = true;
	double cokhwxfwe = 10588;
	bool arhvrvnuojv = true;
	int uuemdgg = 2119;
	bool zpdrntovrrudlr = true;
	bool grhndbxkxmjkl = true;
	string dkixguf = "ttbbonlmoqnsazewguswbsuhvvsbj";
	bool xwaakxuguyhsx = true;

}

int tyaxjgr::uqchecrgoqxxsuzs(int fccoyuhv, double qnbxeqtmevghm, string sznsyn, double qxuvnawkq) {
	bool tvigllsbqaz = false;
	int mhngfqrexyk = 1826;
	double trldzbqtdj = 426;
	double jrlukqkscwaraxx = 34620;
	bool yfuukwezfjqwzap = true;
	int xbfxqxie = 3933;
	int eiougqonfwzcj = 4780;
	if (false != false) {
		int owhv;
		for (owhv = 47; owhv > 0; owhv--) {
			continue;
		}
	}
	return 7161;
}

string tyaxjgr::phusvarrvwsluynxscqotgpd(string uakowjeaa, int yelhmtkyup, bool lnmchvsfw) {
	string iheksgnuxusvl = "qrxniqtxas";
	bool bjpwcxh = true;
	double uucoryyaeyncxy = 29345;
	double lmplqwckunxvnka = 72250;
	int xaiovf = 7985;
	string ilhgmylmqdxfuyk = "kbltqdbrybaxrgfikyuabjqorjikpwcdethx";
	bool lzvdabhoydujgmm = true;
	string tkfbr = "dpfxdncnqjflbfhipswyertevxbdrgdgcnizftdfnicfnazmuwjyxgvadgqsqcrxuumtutnzbdxmoofwsslbeoqlgtpsgpsts";
	bool wevmz = true;
	string dixelsdop = "upkelejwlnoajogdtmqvkaihu";
	if (true != true) {
		int anxagygiq;
		for (anxagygiq = 89; anxagygiq > 0; anxagygiq--) {
			continue;
		}
	}
	if (string("qrxniqtxas") != string("qrxniqtxas")) {
		int khduqeyzrm;
		for (khduqeyzrm = 6; khduqeyzrm > 0; khduqeyzrm--) {
			continue;
		}
	}
	return string("wlcegcsxvuyvqgkmfsmu");
}

bool tyaxjgr::otwxyztxxosax(int scxkytycy, string mqiitcmfls) {
	int sfjkgly = 4450;
	int rxbxqqcysiootlx = 892;
	string ygcvccwxkos = "oiysmlasbatixddgtvebeqssbbkbpxu";
	bool towtkckumdltbpm = true;
	if (892 == 892) {
		int kcage;
		for (kcage = 10; kcage > 0; kcage--) {
			continue;
		}
	}
	if (true == true) {
		int nbapqggjy;
		for (nbapqggjy = 15; nbapqggjy > 0; nbapqggjy--) {
			continue;
		}
	}
	if (true == true) {
		int oschnefjry;
		for (oschnefjry = 34; oschnefjry > 0; oschnefjry--) {
			continue;
		}
	}
	return false;
}

void tyaxjgr::iegwyqipqjyncoiwvq(bool zltxgthgy, string utcxlmjemjgtmd, string nllnfdezdcyz, int lwjmjoahwx, bool iahhvfiikvt, double eimnh) {
	double wixlwknbddqez = 27774;
	string zefpwsg = "kkednafsryftslshxrgjfawkryndfsefawipq";
	string pwqscgiegz = "tjcklhrufsxpvhwmwgmlxuefmirxshyhomlcxykrofisodhlvaesilpzebnksvvuupmajgitnexnvonxjcoiyonnxeujraygrpt";
	double zudah = 5897;
	int xqgptdcelxnjqwb = 7538;
	int awwrdwkcxec = 2754;
	string pursuflotgwob = "jrqivccovctanfgcotacxgirtczdgwgqblrvcwcchikmqhmzeqyzpisxnipgflrmnqyllxaruidplmgzisoaexjaofqusrvgraj";
	string ptdttbszytvq = "ajvbcergvvtlsrmzigmfgxfnpwkqfhecghraomuswpuailqv";
	int itskkmixflzc = 3456;
	double madywauegou = 2282;
	if (3456 == 3456) {
		int kd;
		for (kd = 13; kd > 0; kd--) {
			continue;
		}
	}
	if (2754 == 2754) {
		int si;
		for (si = 87; si > 0; si--) {
			continue;
		}
	}
	if (string("ajvbcergvvtlsrmzigmfgxfnpwkqfhecghraomuswpuailqv") != string("ajvbcergvvtlsrmzigmfgxfnpwkqfhecghraomuswpuailqv")) {
		int doctlk;
		for (doctlk = 3; doctlk > 0; doctlk--) {
			continue;
		}
	}
	if (string("tjcklhrufsxpvhwmwgmlxuefmirxshyhomlcxykrofisodhlvaesilpzebnksvvuupmajgitnexnvonxjcoiyonnxeujraygrpt") != string("tjcklhrufsxpvhwmwgmlxuefmirxshyhomlcxykrofisodhlvaesilpzebnksvvuupmajgitnexnvonxjcoiyonnxeujraygrpt")) {
		int nbmxvja;
		for (nbmxvja = 17; nbmxvja > 0; nbmxvja--) {
			continue;
		}
	}

}

double tyaxjgr::fhxtdxcquxaeelxgxrhto() {
	string aptaezrq = "obxokshvcxcylfkghknnymiaoigoecnnkjcmvqvhxftsvbbyqenohffzyqfwcuwkfhvcfirfptk";
	string ghwtnfupwf = "pfxnqngqsiggftzsmgrwtdrvuifobyclwomshkmevljyvw";
	if (string("obxokshvcxcylfkghknnymiaoigoecnnkjcmvqvhxftsvbbyqenohffzyqfwcuwkfhvcfirfptk") == string("obxokshvcxcylfkghknnymiaoigoecnnkjcmvqvhxftsvbbyqenohffzyqfwcuwkfhvcfirfptk")) {
		int exwh;
		for (exwh = 84; exwh > 0; exwh--) {
			continue;
		}
	}
	if (string("obxokshvcxcylfkghknnymiaoigoecnnkjcmvqvhxftsvbbyqenohffzyqfwcuwkfhvcfirfptk") != string("obxokshvcxcylfkghknnymiaoigoecnnkjcmvqvhxftsvbbyqenohffzyqfwcuwkfhvcfirfptk")) {
		int ubvhvqzmbj;
		for (ubvhvqzmbj = 17; ubvhvqzmbj > 0; ubvhvqzmbj--) {
			continue;
		}
	}
	return 16602;
}

string tyaxjgr::yhyaofyavrfvkjmrkbqxku(double ghdmhqoyn, double pwohpuwofo, string dpoqhpyvapvgn, bool zwdews, double ezkiiyr, double ftwlvfqqa, int rcpkne, double kvvjdovearahkb, string ognafugmvsuzcb) {
	bool rllkczt = true;
	double lzirwp = 54584;
	double ojooo = 44065;
	string telww = "xauzttlruyakryjtogclfdloewmuqoqduebygnpbzqsbrzvrsoblmakmqnxgtksljkqpv";
	bool bwmouwfkcyyaq = false;
	string joeuxhabic = "yytvkwinxqjitumbcuhzkomoabmzqpiwclegncbsazwvinjizumvqsgqbwitjnymdounjdymczgizockrlp";
	double nxoqp = 18479;
	double zzmgbixan = 42452;
	int uvbzkpxnc = 4683;
	int lbzsrvzrevxo = 6176;
	if (42452 == 42452) {
		int yel;
		for (yel = 4; yel > 0; yel--) {
			continue;
		}
	}
	if (54584 == 54584) {
		int dfwbzyf;
		for (dfwbzyf = 75; dfwbzyf > 0; dfwbzyf--) {
			continue;
		}
	}
	if (44065 != 44065) {
		int gslmv;
		for (gslmv = 65; gslmv > 0; gslmv--) {
			continue;
		}
	}
	return string("oplocamcqg");
}

int tyaxjgr::zqqcwcvjkpyguzlbvkctec(int dgnobxxtkdg, double xuwkzwmdcfpws) {
	string huwqw = "scuixplgertsjwyghyncvhtxflncpveixvhcdnvfhpldmrkpppyrztthlifekgetcfffzdyb";
	bool iilxgg = true;
	string rlhskegpba = "jtoqlft";
	if (string("jtoqlft") != string("jtoqlft")) {
		int vf;
		for (vf = 38; vf > 0; vf--) {
			continue;
		}
	}
	if (string("scuixplgertsjwyghyncvhtxflncpveixvhcdnvfhpldmrkpppyrztthlifekgetcfffzdyb") == string("scuixplgertsjwyghyncvhtxflncpveixvhcdnvfhpldmrkpppyrztthlifekgetcfffzdyb")) {
		int rg;
		for (rg = 39; rg > 0; rg--) {
			continue;
		}
	}
	if (string("jtoqlft") != string("jtoqlft")) {
		int dxctlulwv;
		for (dxctlulwv = 20; dxctlulwv > 0; dxctlulwv--) {
			continue;
		}
	}
	return 63163;
}

double tyaxjgr::ygljzwuezfetsdgra(double gsznshazrftr, double ujcyvtj, int dirxllvyop, int tatmuhnkugmdium, double qoxjfuqh) {
	return 30311;
}

tyaxjgr::tyaxjgr() {
	this->zqqcwcvjkpyguzlbvkctec(1092, 51133);
	this->ygljzwuezfetsdgra(22259, 12065, 3687, 489, 38535);
	this->otwxyztxxosax(6297, string("nrgblstndtapgkfrxiciboophwuccaqou"));
	this->iegwyqipqjyncoiwvq(false, string("jonwztnkwcjspwur"), string("gouohbwik"), 4293, true, 8679);
	this->fhxtdxcquxaeelxgxrhto();
	this->yhyaofyavrfvkjmrkbqxku(22219, 4012, string("nacamafwlsrsrd"), false, 74309, 30973, 730, 256, string("gvhu"));
	this->gtuymxqvafgpblfqx();
	this->iwyykhegenzztqbawhbjtgq();
	this->xuewxjpnal(26693, false, 5631, string("ixagpoumffqymejehwbursqylloqncsnsgcqyitenwgvlfigpdncwghlgklpjzbtexusnvikokienkimsmkunzhnhuogeoxnlwyb"), string(""), 29565, string("yiitypcludaaqjj"), 2517);
	this->lofnizgisrjxbdkplprq(false, 79871, 1389, string("xkgmgdwebnwsgpwaxtnvqmzrwieicuxzdj"), 4201, 45711, false);
	this->yxfdkfvpvddvjmqd();
	this->bgfyiyxtjqkwelosdvfokjjb(false);
	this->nivsldlwvltxatkkw(true, false, 455, 42348, 57754, string("fzlbiwjapnqumdiqhvhuinpsolvolttsixrmcl"), 52269, 1067, string("suqdi"), string("eikyrpdxsmfkxlgwxhminfhnpyqqfuvzdaneerpcnsvzptmuxot"));
	this->zytnervaitj(false, 1853);
	this->uqchecrgoqxxsuzs(2513, 1923, string("tchup"), 22024);
	this->phusvarrvwsluynxscqotgpd(string("ovpwxbgmsxxfwmoyacnczjydpfhjjqgynckn"), 3295, true);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class vvszrac {
public:
	bool bisudy;
	int catcibkophx;
	string arcchkdhsmavar;
	int essakrz;
	vvszrac();
	double hkmpzbrfuliiahzehxpaztj(bool rhwuxfae, bool mznghwmh, bool mrtzifeidqyxvj, bool bbyvvdiukpu, bool acbokeajchx, string sjyfkzc, int arigkpv, bool vsckvisfxwoqgno);
	double wabsefnkrc(double didjavwvw, double oaexjj, bool dhzzsqlzpdsko, double jsxzsyqlqwdoef, bool uthdunifm, int uwscq, int bkctxchqhpr, double epwqbstfrtxo);
	int elbqfufuclxqqrabxbsaexzj(int zjosymmfuwgk, bool ojynh, double yaqiclzmlgtdf, double smfpsy, int qlmgjmgszgtc, bool ifzsqixxmuqtut);
	void fyjandvsrewg(bool tcvjosmkktwpbba, bool cguncpexo, double klxcqbvjtuv, int islnevy, bool imtupp, string xjofr, string voqskf, bool qmkvxsovilt);
	void nkxyhyqjnmnoelgjekuyzwpsf(double nfdjrmo, double twktlgtzmvgdonz, string wdwomqtxfy, double qshmbfjuvl, int oslfislmszd, string vtejmtnv, int cuavbnq, int lmdghvbgj, double wztdr);
	bool fkpaaejhiufggnkaim(string istbjz, string tfwlasp, bool ypvgymtuijo, double umrdkmkraxq, double cumeconrcvmh, int unrjdgf, int znpetbbdnej, string nbbygo, int bwhbuwdsgct);
	int ngohxkygxyextxenppcueeub(string tfakucgeoderh, double xwypzfytwffop, double bzjilr, int xyplkynip, double ilgwvjmcheqgw, int obagz, int jzpic, int lmplihuvb);
	int zqwwehvlxrrbusboijcfw(int xnskqv, double wtqqmiptpksx, int iziycsxz);
	void rxockcfwsdarambainest(int nriwxzmmvo, bool tjiluu);
	double wfinyxylsvmwxtdg(double yooxn, int hyryli, double fehxofuvcvjtemo, int lgascuw, int fvijuftc);

protected:
	int guhddp;
	bool rcuvb;
	string ilgsxazapcdjuwa;
	double dpyalpcilzyd;
	string tbqdijjicspfb;

	void vhguaxtlkpbgaavyvxm(double ydquhcjaks, int hadaobrwdhaub, bool pseginoqr);
	double qetmkjrroyutjqjyio(string srwhdsdzhfjchaq, int wwuibpec);
	double wxrmfycxfzx(bool qemnljkhz);
	string majhpskxcmgebjyydztnju(string yuqtqucr);
	double sflxuigrgdy(bool isynavcg, bool vsifuzis);
	bool nhjjjgtcbbx(bool jwzvl, double akanwznao, int lisptxgdxjg, string chbvxz, string fxzwccyeqocj, double mhzpf, bool zthpvfmlzqglbt);

private:
	int prtgzf;
	string bvnjbpkxoa;

	int ficydmatinnurrqqrbej(int posna, string ruqerlijjjeai, string gkiwwtpezpwab, string vcffqbpyhj, int eoemej, bool sygrctsjpiuhdks);
	double cnotsymwbjhtpdqvz(string sizdupcj, double lvqvlgnihlgzhh, int jzhbp, bool tfuwaoe, double bbwprcuuiflyho);
	string jthuwivosbeswiaj(bool qaymfecisa, int brgpsmfcfyemtv, bool yeftvcynxox, double zlspbcstmijg, double amvqmnxov, bool ztyxjoy);
	int nxxmotatpfuyevixygrmuwuj(double kzpogxdhc, bool czwdhaiwyrl, bool rnavyg, string mmwadjjmefqtmrh, double sffsmfhhzeqf, bool hmuvu, string sqyji);
	string wdkcgzlusteabwtqcwc(bool huxsngcqvvf, int eeqvrazje, string zcbdbrv, bool etojdb, double svueb, double mqljkacwplkbrh, int tinmslghu);
	void iyvaalqbgoush();

};


int vvszrac::ficydmatinnurrqqrbej(int posna, string ruqerlijjjeai, string gkiwwtpezpwab, string vcffqbpyhj, int eoemej, bool sygrctsjpiuhdks) {
	string onzyohusehdcoak = "bgtcmxztgqilayfzccjncbpbtmatktevjdzankdpxtbgsebikfpetdiqfcfwtlouuxkcwe";
	double nnfkppobxrefzpf = 20369;
	double cbhwprj = 5567;
	double lguagsowsgpckwa = 43446;
	int uupiyczvokl = 4189;
	string tvfst = "zhvwkbyoctxpclwehsfdsloohtprbrqpovqvudvcbwakxcyjupxexztkofvmjfvidacmkylegeqdnadrrtuuvgnqtbynvaekdmvt";
	int jbmpcn = 125;
	if (5567 != 5567) {
		int zd;
		for (zd = 4; zd > 0; zd--) {
			continue;
		}
	}
	if (43446 == 43446) {
		int awgzixf;
		for (awgzixf = 85; awgzixf > 0; awgzixf--) {
			continue;
		}
	}
	if (125 == 125) {
		int kbqlnbba;
		for (kbqlnbba = 30; kbqlnbba > 0; kbqlnbba--) {
			continue;
		}
	}
	if (string("bgtcmxztgqilayfzccjncbpbtmatktevjdzankdpxtbgsebikfpetdiqfcfwtlouuxkcwe") == string("bgtcmxztgqilayfzccjncbpbtmatktevjdzankdpxtbgsebikfpetdiqfcfwtlouuxkcwe")) {
		int zsp;
		for (zsp = 76; zsp > 0; zsp--) {
			continue;
		}
	}
	return 45550;
}

double vvszrac::cnotsymwbjhtpdqvz(string sizdupcj, double lvqvlgnihlgzhh, int jzhbp, bool tfuwaoe, double bbwprcuuiflyho) {
	string jrkyxqitdcijp = "mrscjsinugmmmcaaujjtdwhhfnhgxeefnwrpuoqtkxcxwfyzafygvhivitqotlmbelvzlxunldlh";
	bool emdtb = false;
	int lkfeyegd = 1166;
	int ihhtfk = 751;
	bool wvcvhyhbktr = true;
	int uuyupjf = 3624;
	double kpysjmetedilh = 13400;
	bool iccmd = true;
	int abnuvr = 4829;
	int ivadsirvw = 9;
	return 33482;
}

string vvszrac::jthuwivosbeswiaj(bool qaymfecisa, int brgpsmfcfyemtv, bool yeftvcynxox, double zlspbcstmijg, double amvqmnxov, bool ztyxjoy) {
	int nasnqxnf = 1552;
	string zbhweq = "mdspziopfrquphswtgfrtspkbkfkbezmel";
	double dolqcjnr = 26996;
	double ayiawwt = 3164;
	double iellyw = 2679;
	int kocjts = 1511;
	if (26996 != 26996) {
		int evnp;
		for (evnp = 6; evnp > 0; evnp--) {
			continue;
		}
	}
	if (1511 != 1511) {
		int lnbjenfyp;
		for (lnbjenfyp = 66; lnbjenfyp > 0; lnbjenfyp--) {
			continue;
		}
	}
	return string("hwagitndkfijfz");
}

int vvszrac::nxxmotatpfuyevixygrmuwuj(double kzpogxdhc, bool czwdhaiwyrl, bool rnavyg, string mmwadjjmefqtmrh, double sffsmfhhzeqf, bool hmuvu, string sqyji) {
	return 96742;
}

string vvszrac::wdkcgzlusteabwtqcwc(bool huxsngcqvvf, int eeqvrazje, string zcbdbrv, bool etojdb, double svueb, double mqljkacwplkbrh, int tinmslghu) {
	bool nouwnuef = true;
	int ypboec = 1583;
	double qjrtpklgqvj = 15359;
	bool tqlytvyb = false;
	int xfknwqifa = 2763;
	if (15359 == 15359) {
		int fqcxyneit;
		for (fqcxyneit = 20; fqcxyneit > 0; fqcxyneit--) {
			continue;
		}
	}
	if (15359 != 15359) {
		int knpzgctv;
		for (knpzgctv = 11; knpzgctv > 0; knpzgctv--) {
			continue;
		}
	}
	if (true != true) {
		int tkvvi;
		for (tkvvi = 99; tkvvi > 0; tkvvi--) {
			continue;
		}
	}
	return string("wfdfplowsxcrflvg");
}

void vvszrac::iyvaalqbgoush() {
	bool ljxcvwacgpo = true;
	string uucmhkhxdindqrb = "tgisqpbzugeytarryetlovcrxqltvqxexzymvxzmrscwxfmtvyxig";
	bool lxikyrmrjvgnxub = true;
	int bwdudigpfigl = 693;
	if (true != true) {
		int fkz;
		for (fkz = 40; fkz > 0; fkz--) {
			continue;
		}
	}
	if (true != true) {
		int jk;
		for (jk = 11; jk > 0; jk--) {
			continue;
		}
	}
	if (true == true) {
		int wdsdfsqoac;
		for (wdsdfsqoac = 39; wdsdfsqoac > 0; wdsdfsqoac--) {
			continue;
		}
	}

}

void vvszrac::vhguaxtlkpbgaavyvxm(double ydquhcjaks, int hadaobrwdhaub, bool pseginoqr) {
	string owsjagjmamazj = "zacbrbmyonhnncmltrdnqysydxuoksvxhlyxnxfkhckpcsvtwcmprjxwedvdeumucebiexanuqerlvvbvzlyipnr";
	int czizxwxmc = 4587;
	double vhjqnccuysm = 890;
	int msxkbapsrhkdrav = 1951;
	string adqxelepvtrr = "wttqvuks";
	int ddazyjof = 2455;
	bool edibkbaqc = true;
	double zhjqbiqxnxu = 27119;
	double pzgrlhuqrl = 92196;
	double cobxpbga = 16752;
	if (string("wttqvuks") != string("wttqvuks")) {
		int fqbkdwg;
		for (fqbkdwg = 10; fqbkdwg > 0; fqbkdwg--) {
			continue;
		}
	}
	if (true != true) {
		int rermfi;
		for (rermfi = 9; rermfi > 0; rermfi--) {
			continue;
		}
	}
	if (string("wttqvuks") == string("wttqvuks")) {
		int czuanzfk;
		for (czuanzfk = 62; czuanzfk > 0; czuanzfk--) {
			continue;
		}
	}
	if (string("wttqvuks") == string("wttqvuks")) {
		int dzfvecdx;
		for (dzfvecdx = 10; dzfvecdx > 0; dzfvecdx--) {
			continue;
		}
	}

}

double vvszrac::qetmkjrroyutjqjyio(string srwhdsdzhfjchaq, int wwuibpec) {
	bool xlcymiigie = false;
	string yzuyqyqtoatlru = "obcg";
	bool narxkrffllq = false;
	double jeplvcnncuze = 15807;
	bool nlbple = true;
	bool urxpogekivdv = true;
	double prvyouwttiyc = 22391;
	string receymiymwu = "mmsbuhbiuykkavprzsnyraijuoxrvul";
	double ryvhqvsdbqxi = 35331;
	string dzhjcsywy = "avhmzrjgy";
	if (false == false) {
		int elfrohwiq;
		for (elfrohwiq = 90; elfrohwiq > 0; elfrohwiq--) {
			continue;
		}
	}
	if (15807 != 15807) {
		int oowzthb;
		for (oowzthb = 63; oowzthb > 0; oowzthb--) {
			continue;
		}
	}
	if (string("mmsbuhbiuykkavprzsnyraijuoxrvul") != string("mmsbuhbiuykkavprzsnyraijuoxrvul")) {
		int hodio;
		for (hodio = 14; hodio > 0; hodio--) {
			continue;
		}
	}
	return 31602;
}

double vvszrac::wxrmfycxfzx(bool qemnljkhz) {
	bool tkyivkocr = false;
	if (false == false) {
		int svn;
		for (svn = 14; svn > 0; svn--) {
			continue;
		}
	}
	if (false == false) {
		int lsuukdqyf;
		for (lsuukdqyf = 28; lsuukdqyf > 0; lsuukdqyf--) {
			continue;
		}
	}
	if (false == false) {
		int zsvk;
		for (zsvk = 10; zsvk > 0; zsvk--) {
			continue;
		}
	}
	if (false == false) {
		int czpjblryxf;
		for (czpjblryxf = 12; czpjblryxf > 0; czpjblryxf--) {
			continue;
		}
	}
	if (false != false) {
		int pcmxtudokh;
		for (pcmxtudokh = 58; pcmxtudokh > 0; pcmxtudokh--) {
			continue;
		}
	}
	return 47863;
}

string vvszrac::majhpskxcmgebjyydztnju(string yuqtqucr) {
	string ksnrljckh = "eofcfcwmvptwjmcnlqypzkntacaluyvvizkifo";
	bool mvzekjpijeuih = false;
	bool nfhprl = true;
	bool wynxzzvnxqjta = false;
	if (true != true) {
		int mv;
		for (mv = 17; mv > 0; mv--) {
			continue;
		}
	}
	if (string("eofcfcwmvptwjmcnlqypzkntacaluyvvizkifo") != string("eofcfcwmvptwjmcnlqypzkntacaluyvvizkifo")) {
		int ixxwgu;
		for (ixxwgu = 21; ixxwgu > 0; ixxwgu--) {
			continue;
		}
	}
	if (false == false) {
		int hvdqt;
		for (hvdqt = 69; hvdqt > 0; hvdqt--) {
			continue;
		}
	}
	if (false != false) {
		int cfonx;
		for (cfonx = 43; cfonx > 0; cfonx--) {
			continue;
		}
	}
	return string("yktmug");
}

double vvszrac::sflxuigrgdy(bool isynavcg, bool vsifuzis) {
	int kpbywuyl = 5884;
	int joijtgkyq = 2706;
	bool aurjxidfxab = false;
	string pmmiumo = "ldtuuiqbuwvqymehpoehhnyucsw";
	bool vhsrgt = true;
	int zpdqprhd = 5684;
	bool hqzlueo = false;
	bool ttjewqf = false;
	if (false == false) {
		int uqymehfui;
		for (uqymehfui = 28; uqymehfui > 0; uqymehfui--) {
			continue;
		}
	}
	if (false != false) {
		int yiw;
		for (yiw = 64; yiw > 0; yiw--) {
			continue;
		}
	}
	if (false != false) {
		int hkxgyx;
		for (hkxgyx = 92; hkxgyx > 0; hkxgyx--) {
			continue;
		}
	}
	return 45621;
}

bool vvszrac::nhjjjgtcbbx(bool jwzvl, double akanwznao, int lisptxgdxjg, string chbvxz, string fxzwccyeqocj, double mhzpf, bool zthpvfmlzqglbt) {
	string irkyiedfp = "wf";
	bool wuptevdkzouv = false;
	string qmhrtdtitykofy = "spdlreckrdjrzhihuzsyhpirxurvqyk";
	double lemexgmbfxcd = 40804;
	string fwjrldfibpznagb = "nuvjfmimzdhasgsovcanhgjarccmfneyyyiobrhxvbrvcwymtftcftdlckrotkctaelsepexligqyaexkhxti";
	string wdtuvyu = "kpnfelgiqo";
	if (40804 != 40804) {
		int svcqf;
		for (svcqf = 5; svcqf > 0; svcqf--) {
			continue;
		}
	}
	if (string("nuvjfmimzdhasgsovcanhgjarccmfneyyyiobrhxvbrvcwymtftcftdlckrotkctaelsepexligqyaexkhxti") == string("nuvjfmimzdhasgsovcanhgjarccmfneyyyiobrhxvbrvcwymtftcftdlckrotkctaelsepexligqyaexkhxti")) {
		int rbhas;
		for (rbhas = 43; rbhas > 0; rbhas--) {
			continue;
		}
	}
	if (string("nuvjfmimzdhasgsovcanhgjarccmfneyyyiobrhxvbrvcwymtftcftdlckrotkctaelsepexligqyaexkhxti") != string("nuvjfmimzdhasgsovcanhgjarccmfneyyyiobrhxvbrvcwymtftcftdlckrotkctaelsepexligqyaexkhxti")) {
		int qb;
		for (qb = 51; qb > 0; qb--) {
			continue;
		}
	}
	if (string("wf") != string("wf")) {
		int pclyo;
		for (pclyo = 58; pclyo > 0; pclyo--) {
			continue;
		}
	}
	if (string("spdlreckrdjrzhihuzsyhpirxurvqyk") != string("spdlreckrdjrzhihuzsyhpirxurvqyk")) {
		int kj;
		for (kj = 32; kj > 0; kj--) {
			continue;
		}
	}
	return false;
}

double vvszrac::hkmpzbrfuliiahzehxpaztj(bool rhwuxfae, bool mznghwmh, bool mrtzifeidqyxvj, bool bbyvvdiukpu, bool acbokeajchx, string sjyfkzc, int arigkpv, bool vsckvisfxwoqgno) {
	double tmpgnsfcqnmhxs = 13119;
	int bjvely = 8450;
	int hsyqaytvpnqlr = 4763;
	double fzxoqgyg = 12702;
	return 685;
}

double vvszrac::wabsefnkrc(double didjavwvw, double oaexjj, bool dhzzsqlzpdsko, double jsxzsyqlqwdoef, bool uthdunifm, int uwscq, int bkctxchqhpr, double epwqbstfrtxo) {
	int pnlqfg = 2316;
	bool qnmdeziphyoicc = false;
	string mprhni = "tfrfxyv";
	int uersj = 353;
	int klohjyx = 2003;
	bool ocypuoheqzmck = false;
	bool lnpkxvj = false;
	string ljxsfvwea = "zqbdgqmkkidqiqeczdlmiacrdoiyututhhymsaaamvnyuxlgoyjnvzcjpbi";
	if (string("zqbdgqmkkidqiqeczdlmiacrdoiyututhhymsaaamvnyuxlgoyjnvzcjpbi") == string("zqbdgqmkkidqiqeczdlmiacrdoiyututhhymsaaamvnyuxlgoyjnvzcjpbi")) {
		int gq;
		for (gq = 50; gq > 0; gq--) {
			continue;
		}
	}
	if (false != false) {
		int dpshxxuf;
		for (dpshxxuf = 53; dpshxxuf > 0; dpshxxuf--) {
			continue;
		}
	}
	if (false == false) {
		int yeptbrdfwl;
		for (yeptbrdfwl = 64; yeptbrdfwl > 0; yeptbrdfwl--) {
			continue;
		}
	}
	if (false != false) {
		int bw;
		for (bw = 86; bw > 0; bw--) {
			continue;
		}
	}
	if (false != false) {
		int og;
		for (og = 50; og > 0; og--) {
			continue;
		}
	}
	return 82219;
}

int vvszrac::elbqfufuclxqqrabxbsaexzj(int zjosymmfuwgk, bool ojynh, double yaqiclzmlgtdf, double smfpsy, int qlmgjmgszgtc, bool ifzsqixxmuqtut) {
	double kgkrihyxx = 932;
	if (932 != 932) {
		int udfx;
		for (udfx = 84; udfx > 0; udfx--) {
			continue;
		}
	}
	return 80773;
}

void vvszrac::fyjandvsrewg(bool tcvjosmkktwpbba, bool cguncpexo, double klxcqbvjtuv, int islnevy, bool imtupp, string xjofr, string voqskf, bool qmkvxsovilt) {
	int akhifzskuhhjj = 2387;
	int rggppnmc = 409;

}

void vvszrac::nkxyhyqjnmnoelgjekuyzwpsf(double nfdjrmo, double twktlgtzmvgdonz, string wdwomqtxfy, double qshmbfjuvl, int oslfislmszd, string vtejmtnv, int cuavbnq, int lmdghvbgj, double wztdr) {
	double jcmidc = 24631;
	string aykxsbq = "ajnarlwewcaiiqkdogijklfhqxydgyztskoynqzkxmw";
	double dybjdbbrtan = 66857;
	if (string("ajnarlwewcaiiqkdogijklfhqxydgyztskoynqzkxmw") == string("ajnarlwewcaiiqkdogijklfhqxydgyztskoynqzkxmw")) {
		int rvlefg;
		for (rvlefg = 86; rvlefg > 0; rvlefg--) {
			continue;
		}
	}
	if (string("ajnarlwewcaiiqkdogijklfhqxydgyztskoynqzkxmw") == string("ajnarlwewcaiiqkdogijklfhqxydgyztskoynqzkxmw")) {
		int nk;
		for (nk = 42; nk > 0; nk--) {
			continue;
		}
	}
	if (24631 == 24631) {
		int mptoh;
		for (mptoh = 75; mptoh > 0; mptoh--) {
			continue;
		}
	}

}

bool vvszrac::fkpaaejhiufggnkaim(string istbjz, string tfwlasp, bool ypvgymtuijo, double umrdkmkraxq, double cumeconrcvmh, int unrjdgf, int znpetbbdnej, string nbbygo, int bwhbuwdsgct) {
	double mwqgweltbnvwxb = 29246;
	if (29246 != 29246) {
		int blwqlp;
		for (blwqlp = 68; blwqlp > 0; blwqlp--) {
			continue;
		}
	}
	if (29246 == 29246) {
		int jsj;
		for (jsj = 42; jsj > 0; jsj--) {
			continue;
		}
	}
	return false;
}

int vvszrac::ngohxkygxyextxenppcueeub(string tfakucgeoderh, double xwypzfytwffop, double bzjilr, int xyplkynip, double ilgwvjmcheqgw, int obagz, int jzpic, int lmplihuvb) {
	string gybnc = "zbsedyqcrqyjzwfdzylbdjctgpiyachyqwfpbxifuxyuofvsawmiygxx";
	bool bgayjgmxdvgkay = true;
	string zuqqkbwo = "djswkipwkilhqyfmzoaffcwtmnuxucpaqbyvfnpmoddvbjgucbdcpybovu";
	string nktzrzidnf = "oamltpga";
	bool ghxkle = false;
	double olvcwlyapmlndff = 11414;
	if (string("djswkipwkilhqyfmzoaffcwtmnuxucpaqbyvfnpmoddvbjgucbdcpybovu") != string("djswkipwkilhqyfmzoaffcwtmnuxucpaqbyvfnpmoddvbjgucbdcpybovu")) {
		int slbemgzupu;
		for (slbemgzupu = 37; slbemgzupu > 0; slbemgzupu--) {
			continue;
		}
	}
	if (string("zbsedyqcrqyjzwfdzylbdjctgpiyachyqwfpbxifuxyuofvsawmiygxx") == string("zbsedyqcrqyjzwfdzylbdjctgpiyachyqwfpbxifuxyuofvsawmiygxx")) {
		int ji;
		for (ji = 13; ji > 0; ji--) {
			continue;
		}
	}
	if (string("oamltpga") != string("oamltpga")) {
		int golua;
		for (golua = 38; golua > 0; golua--) {
			continue;
		}
	}
	return 3037;
}

int vvszrac::zqwwehvlxrrbusboijcfw(int xnskqv, double wtqqmiptpksx, int iziycsxz) {
	int rnmpdmmheywb = 296;
	bool iqsrtsokbowdzex = true;
	double uvcusnsqvsssmtg = 25480;
	int tyxrjud = 3067;
	int rswwgb = 4368;
	string dgrmchcrb = "cuorlvwxuqwmoiezygsbisuqavndlzxkduvyhtuzuwgifiipwmkixvdjcvvjwkizfwgxbadzhdurwhahlbfzbtuhcwjugvtndwd";
	string gsuybgpqnwea = "skfwyvqfkwixdpthbsexaxoryoscapvjafyfmcpopigfpkisdifesgyajmtwtheldjnvosmpovndrlhuegdcfsbwftjkgv";
	if (string("cuorlvwxuqwmoiezygsbisuqavndlzxkduvyhtuzuwgifiipwmkixvdjcvvjwkizfwgxbadzhdurwhahlbfzbtuhcwjugvtndwd") == string("cuorlvwxuqwmoiezygsbisuqavndlzxkduvyhtuzuwgifiipwmkixvdjcvvjwkizfwgxbadzhdurwhahlbfzbtuhcwjugvtndwd")) {
		int xqbadiero;
		for (xqbadiero = 18; xqbadiero > 0; xqbadiero--) {
			continue;
		}
	}
	if (296 != 296) {
		int otmgcl;
		for (otmgcl = 66; otmgcl > 0; otmgcl--) {
			continue;
		}
	}
	if (true != true) {
		int pkihcivd;
		for (pkihcivd = 25; pkihcivd > 0; pkihcivd--) {
			continue;
		}
	}
	if (3067 == 3067) {
		int nbkd;
		for (nbkd = 64; nbkd > 0; nbkd--) {
			continue;
		}
	}
	return 43528;
}

void vvszrac::rxockcfwsdarambainest(int nriwxzmmvo, bool tjiluu) {
	bool yazutt = false;
	int ojeqmxcxg = 1188;

}

double vvszrac::wfinyxylsvmwxtdg(double yooxn, int hyryli, double fehxofuvcvjtemo, int lgascuw, int fvijuftc) {
	return 97709;
}

vvszrac::vvszrac() {
	this->hkmpzbrfuliiahzehxpaztj(true, false, false, true, false, string("zximwgvfjxvozavklpktzybw"), 5290, true);
	this->wabsefnkrc(33393, 77608, true, 11830, true, 5174, 946, 24360);
	this->elbqfufuclxqqrabxbsaexzj(650, false, 3399, 56426, 1149, true);
	this->fyjandvsrewg(false, false, 18353, 554, true, string("fzgcjkxvozeuozzgtyenbtqixtnbpkpdafbsyqwjgwfrelzgbtwkmxpchocmtcnvadpue"), string("pymjloruijypgdasmgpnogdkamanfpwvrfbcwhmmeqmxkmqxrnjcahi"), true);
	this->nkxyhyqjnmnoelgjekuyzwpsf(63228, 35865, string("djygyjdhnnvjsmzalirxgq"), 6185, 4210, string("lznbyopwsefxzicsokuhwdoqzrdlbhzzgnrtohhimiojmxsgboewntxwvm"), 4500, 3423, 23348);
	this->fkpaaejhiufggnkaim(string("pyxsfjgqlziweygnxnbrqaibqprkummuqetbr"), string("ejwqqdnicigkqszdslqtoclnnzcgcxfjgrfwimhuxgicwzcgnv"), false, 85651, 52708, 5470, 3174, string("qagjytrikakqiafadcscpfhwvvgkuhpvjcvdzvrqhvuiptwxrwbwozyhhnkldc"), 3939);
	this->ngohxkygxyextxenppcueeub(string("cinyxvtgpgjbdvgbufnfsbnwunvitpa"), 42163, 30989, 4950, 16634, 712, 4521, 188);
	this->zqwwehvlxrrbusboijcfw(2834, 68735, 5932);
	this->rxockcfwsdarambainest(1494, false);
	this->wfinyxylsvmwxtdg(74466, 3741, 15407, 37, 3937);
	this->vhguaxtlkpbgaavyvxm(9936, 1318, true);
	this->qetmkjrroyutjqjyio(string("phqyymjlvrbgqmjrcioyxpabklcrizfucshtrakrgpdwjdprvkpbdocaoasiantlplvmzovciuokkiyodfos"), 402);
	this->wxrmfycxfzx(true);
	this->majhpskxcmgebjyydztnju(string("pfstiaapecsxgssppbzzbibdrquddondeedfrbksapywcogroszfgwqg"));
	this->sflxuigrgdy(true, false);
	this->nhjjjgtcbbx(false, 27221, 3403, string("zrpuykrmbkhxyhsnjljkbrpntfajqjbrvksdwuygdpqibsnwqywqugezgphjiwzyioagrj"), string("ffkmknsqgzpzuhodsrruggvbupnfyzwgfusdz"), 56847, true);
	this->ficydmatinnurrqqrbej(2729, string("brbffuyzslllccrafqxopamcpssrznvrhbczcseqhahtorbfmnzezhqibfxtyimvsbsgmhikdvterrvggz"), string("ul"), string("axejdxtpdwbmtopuehyxxsenhjhaczfjyxkqpsodaymwbrmlpcupasrcbdomgp"), 6650, true);
	this->cnotsymwbjhtpdqvz(string("afqssynshyqjfdnwiaqkqjptaetjnkfqscmddnzmzfulamfnpzhnlptlsqlzolxcmrhwz"), 3653, 1985, true, 29082);
	this->jthuwivosbeswiaj(true, 99, false, 48533, 23292, true);
	this->nxxmotatpfuyevixygrmuwuj(47606, false, false, string("uxlddouromywcrg"), 50576, true, string("lyhjexpkqkdmvexwqvzesvmhyzphkwiphgysszsqjzwqowlflodtvrwltvyybcdgierommvnkcxgfkfbpmzpvndaeypfnuxcxsn"));
	this->wdkcgzlusteabwtqcwc(false, 4425, string(""), true, 95606, 5265, 1952);
	this->iyvaalqbgoush();
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class tkyvyvb {
public:
	int tjwvlfrv;
	tkyvyvb();
	string geonyntkba(bool dspjogmpxn, double ejzqazovnwnhvv, bool rtizdchu, double jemvk, bool jemglgngvch, string dryxrne, int nitiolzeht, int mzptbmfwbts, double wwnhljlswtilgn);
	void alfqwyipjeybhmmephauss(bool oqfeygaqzw, string ujriomrnabeitn, double xiuct, string miedlpfayke, double rwladdaw);

protected:
	string kfmketpmftdfbhc;
	string yvekgkhqhfokh;
	double tqndvkr;
	int diusf;
	double foulcnm;

	void ceimhpavamqtjdsnwolqrx(string xzxxiexaydoaq, double pltsjfzfkvxf, double zifpigorapyua);
	string zfdpphjnrx(double epybkiro, bool ttpgyfekowwciyg);
	double tfucqokcaehiegfpoeit();
	void xkwfoqhkyawhjffgrx(double vnnvd);
	void hudfnwqbaam(int iqwgvmcv, bool vhocppbm, double winixqnhl);
	void lvnwhqoysymcklebjci(double jznwgst, int kkekaik, int stjdu, string meovkswhzb, int nrnrvnu, string eijswusdxx, double sffjayxdiju);
	int ytlbdtdayihbqj(string yfzls, string zoyxudhmy, string kydrqncmesknwrf, bool hyjtdxadpqsvcmt, string oilxzohoua, double ajppxfqodrx);
	int jknzjtapuadlpsnnhk(int orpszd, bool hlcwxtp, double sbabwixnnygx, bool bqbnxfcoykn, int oaxofrrxdcuvh, double rzyssiiuxvdh, string cmthkifx, double rfuvggvtquy, string nrmiqfalxv, bool qksrjonrvjwb);

private:
	int lilqwwnj;
	int lkcytdjvm;
	bool aftpdqpdioiwko;
	string ffplvuxbnbskqx;
	string lgwjanbc;

	string xbimjueaxbysjecclhtyzujgs(double bgfxbqac, bool nzpeusqxjgiuvgr, string eloiah, double beixlm, bool yowxkh, string slandixey, int gaxturpqkaa, int ieyltmcfs);
	int qhkesfimemsfkyah(string oyvqm, string hnkhykenidjl, bool hifws, bool maiurstlhqyodsl, bool mwccws, string sbwtrqfvkj, string ncwrrok, double fmtpy, bool hgzbnndb, int cruqwoodbfb);
	string ybjfsuffftl(bool anxqsx, bool myrpdmd, int kcydhz);
	string oxgnccazkynvduha(bool zkywfpkli, string drrplvzhfnjxgg, int pgkzqzr, int ebjgctyhxkuk, bool mitxd, double paopdfcioavg, int ezamgagljwhcmw);
	double hddseftrkhwbqluxmpdzjj(int voilrbmk, double jkkwkv, int fxceuowgvvj, string ugxfhaulbizw, double xdreinafgaifu, bool sxozpfqhdffmp);
	bool jmdlgmavobxbsr(bool teehtiqzn, string qcakam, bool vnmmnwwywttdlzp, bool qsyihcaoqxscy, int csmjzosrmkvd, string jdkwruzmvtcbfjb, string zdfsdgdgaodeukd, bool pciyrw);
	int ooxftmsxfbkakeryb(string znwlp, string fpvylqzrkortmz, bool zrpitacjt, double shqlv, int bobovxyt);
	int taejpvhopiujtlrohu();
	double vzsgargwajr(int lvggpzrnygbxjlj, int edtrmfsjdfiezi, double tmechcf, int qulmnrqrccsf, int tcuvgzldtobadb, string krthcdfkgi, double vhkqunbevq, string nojpgzy, int oxtzsp);
	int xgagrorerdblxst(string xnqhyxjh, double vywuacpmb, double buhgpf, string ubdsqaoqc, double wzjjnnahktktubv);

};


string tkyvyvb::xbimjueaxbysjecclhtyzujgs(double bgfxbqac, bool nzpeusqxjgiuvgr, string eloiah, double beixlm, bool yowxkh, string slandixey, int gaxturpqkaa, int ieyltmcfs) {
	double lgdarpk = 43256;
	bool jidfgmhxkvktkq = true;
	int odpmrzkr = 286;
	bool zvuxetqx = true;
	if (286 != 286) {
		int anbbb;
		for (anbbb = 66; anbbb > 0; anbbb--) {
			continue;
		}
	}
	if (43256 == 43256) {
		int iphkw;
		for (iphkw = 34; iphkw > 0; iphkw--) {
			continue;
		}
	}
	if (true == true) {
		int zrgxafq;
		for (zrgxafq = 62; zrgxafq > 0; zrgxafq--) {
			continue;
		}
	}
	if (true == true) {
		int ckyktcfzqh;
		for (ckyktcfzqh = 22; ckyktcfzqh > 0; ckyktcfzqh--) {
			continue;
		}
	}
	return string("uncab");
}

int tkyvyvb::qhkesfimemsfkyah(string oyvqm, string hnkhykenidjl, bool hifws, bool maiurstlhqyodsl, bool mwccws, string sbwtrqfvkj, string ncwrrok, double fmtpy, bool hgzbnndb, int cruqwoodbfb) {
	double dqelftkrrdopacr = 19640;
	double dtmrwvtiminxzi = 12830;
	int xdcrllm = 2349;
	if (19640 == 19640) {
		int owxxkl;
		for (owxxkl = 30; owxxkl > 0; owxxkl--) {
			continue;
		}
	}
	if (2349 == 2349) {
		int ukmbm;
		for (ukmbm = 24; ukmbm > 0; ukmbm--) {
			continue;
		}
	}
	return 21437;
}

string tkyvyvb::ybjfsuffftl(bool anxqsx, bool myrpdmd, int kcydhz) {
	string ieirxckcoqvjcb = "qokaxgjfezlligdgiozporjkzctyiqenmywjdzhragcuazmafybeaezfzzammiwkpxggrdnicjfwutbhaawogziosrux";
	bool lmuvnjyovtzgpfx = true;
	bool keexxkj = false;
	int hnmjvaj = 3438;
	double vnushuojeadlyv = 60262;
	if (true == true) {
		int ljux;
		for (ljux = 69; ljux > 0; ljux--) {
			continue;
		}
	}
	if (60262 != 60262) {
		int asn;
		for (asn = 76; asn > 0; asn--) {
			continue;
		}
	}
	if (3438 == 3438) {
		int ppntfbatm;
		for (ppntfbatm = 72; ppntfbatm > 0; ppntfbatm--) {
			continue;
		}
	}
	if (false == false) {
		int elia;
		for (elia = 17; elia > 0; elia--) {
			continue;
		}
	}
	if (true == true) {
		int vc;
		for (vc = 27; vc > 0; vc--) {
			continue;
		}
	}
	return string("skhxnsaatklhjvadpevf");
}

string tkyvyvb::oxgnccazkynvduha(bool zkywfpkli, string drrplvzhfnjxgg, int pgkzqzr, int ebjgctyhxkuk, bool mitxd, double paopdfcioavg, int ezamgagljwhcmw) {
	bool yheozxfpy = false;
	bool kfzrgmxrzzpx = true;
	double qzntcaxai = 46638;
	if (true == true) {
		int zukmrioh;
		for (zukmrioh = 7; zukmrioh > 0; zukmrioh--) {
			continue;
		}
	}
	if (46638 == 46638) {
		int ulenu;
		for (ulenu = 69; ulenu > 0; ulenu--) {
			continue;
		}
	}
	if (false == false) {
		int fcqkjot;
		for (fcqkjot = 70; fcqkjot > 0; fcqkjot--) {
			continue;
		}
	}
	if (false == false) {
		int wnzbrlt;
		for (wnzbrlt = 98; wnzbrlt > 0; wnzbrlt--) {
			continue;
		}
	}
	if (true != true) {
		int xzzpnbmp;
		for (xzzpnbmp = 40; xzzpnbmp > 0; xzzpnbmp--) {
			continue;
		}
	}
	return string("mlycot");
}

double tkyvyvb::hddseftrkhwbqluxmpdzjj(int voilrbmk, double jkkwkv, int fxceuowgvvj, string ugxfhaulbizw, double xdreinafgaifu, bool sxozpfqhdffmp) {
	double eitopevulgyfsew = 38163;
	int gjpoaxir = 1006;
	if (38163 == 38163) {
		int bzr;
		for (bzr = 4; bzr > 0; bzr--) {
			continue;
		}
	}
	if (38163 != 38163) {
		int kfxuwwf;
		for (kfxuwwf = 17; kfxuwwf > 0; kfxuwwf--) {
			continue;
		}
	}
	if (1006 != 1006) {
		int yhtbxtqrp;
		for (yhtbxtqrp = 67; yhtbxtqrp > 0; yhtbxtqrp--) {
			continue;
		}
	}
	if (1006 == 1006) {
		int qswklqgx;
		for (qswklqgx = 44; qswklqgx > 0; qswklqgx--) {
			continue;
		}
	}
	return 6688;
}

bool tkyvyvb::jmdlgmavobxbsr(bool teehtiqzn, string qcakam, bool vnmmnwwywttdlzp, bool qsyihcaoqxscy, int csmjzosrmkvd, string jdkwruzmvtcbfjb, string zdfsdgdgaodeukd, bool pciyrw) {
	double rcyoqelmxqlkys = 9639;
	bool teosdhdc = true;
	double iceallsor = 31468;
	bool qpgnufoiyc = true;
	int rrhsswvrkqknvxs = 2912;
	double ovefwacunn = 26959;
	int hdzhtznlm = 6030;
	int xmawzrdh = 978;
	int jzjegirgrjyskcg = 1713;
	if (978 == 978) {
		int cail;
		for (cail = 47; cail > 0; cail--) {
			continue;
		}
	}
	if (6030 != 6030) {
		int crujss;
		for (crujss = 20; crujss > 0; crujss--) {
			continue;
		}
	}
	if (true != true) {
		int ouxosn;
		for (ouxosn = 41; ouxosn > 0; ouxosn--) {
			continue;
		}
	}
	if (978 == 978) {
		int zqinmn;
		for (zqinmn = 20; zqinmn > 0; zqinmn--) {
			continue;
		}
	}
	if (9639 == 9639) {
		int ydkyyrq;
		for (ydkyyrq = 94; ydkyyrq > 0; ydkyyrq--) {
			continue;
		}
	}
	return true;
}

int tkyvyvb::ooxftmsxfbkakeryb(string znwlp, string fpvylqzrkortmz, bool zrpitacjt, double shqlv, int bobovxyt) {
	string tdgsdntacir = "jsjqzddhwjraycoitmlmelgitvrfdrsrsutfeiggbsbbcbnbtugyvqqlzifansydnthlhlzjr";
	string ckzftelhgiohcjj = "xryfwciozrdmwdynzfojbbsnwjxxfguywmz";
	bool hshcvnvjvkxo = false;
	bool pmbhixejbwfneq = true;
	string vzgfiltaqbnoa = "djzsidtwjbkanlbfydaqhoezzzzitoaiidyzlhoqsubwjylauhhslcsbfcojyjbnbpsayctsgbfvxrbalpyvifhhnmfld";
	return 81213;
}

int tkyvyvb::taejpvhopiujtlrohu() {
	int grnmx = 2763;
	string kjgdbfqeytp = "zqxmchcazpgdwifopvjogjujbvexjlynukgwytgijfmyrxiqosrbvaktehtbrnulcpywjfwiawlljnwkantbulfdf";
	if (string("zqxmchcazpgdwifopvjogjujbvexjlynukgwytgijfmyrxiqosrbvaktehtbrnulcpywjfwiawlljnwkantbulfdf") == string("zqxmchcazpgdwifopvjogjujbvexjlynukgwytgijfmyrxiqosrbvaktehtbrnulcpywjfwiawlljnwkantbulfdf")) {
		int fu;
		for (fu = 54; fu > 0; fu--) {
			continue;
		}
	}
	return 18589;
}

double tkyvyvb::vzsgargwajr(int lvggpzrnygbxjlj, int edtrmfsjdfiezi, double tmechcf, int qulmnrqrccsf, int tcuvgzldtobadb, string krthcdfkgi, double vhkqunbevq, string nojpgzy, int oxtzsp) {
	int tlbelsdiix = 1523;
	bool mzjilmh = true;
	bool anhfroxe = true;
	bool iwhmonockakq = false;
	double hilmoamofyndxzj = 2595;
	bool vfqbgfagkk = false;
	double byoimwazoheqhpr = 881;
	if (true == true) {
		int bhwtej;
		for (bhwtej = 44; bhwtej > 0; bhwtej--) {
			continue;
		}
	}
	if (true == true) {
		int dmlfu;
		for (dmlfu = 71; dmlfu > 0; dmlfu--) {
			continue;
		}
	}
	if (false != false) {
		int jbfdm;
		for (jbfdm = 85; jbfdm > 0; jbfdm--) {
			continue;
		}
	}
	return 85827;
}

int tkyvyvb::xgagrorerdblxst(string xnqhyxjh, double vywuacpmb, double buhgpf, string ubdsqaoqc, double wzjjnnahktktubv) {
	double lsesded = 44339;
	int nlrtdhkhmgcbu = 486;
	string eturicqgtbcvqof = "wthjnuqjdifqotihgcgiiychqibmnfrzrzbhfvkuzkbcntqsmrseayeiyivcvknssigomvmvhmxrfot";
	double njubkdklxnodfv = 57172;
	if (string("wthjnuqjdifqotihgcgiiychqibmnfrzrzbhfvkuzkbcntqsmrseayeiyivcvknssigomvmvhmxrfot") == string("wthjnuqjdifqotihgcgiiychqibmnfrzrzbhfvkuzkbcntqsmrseayeiyivcvknssigomvmvhmxrfot")) {
		int pxrm;
		for (pxrm = 29; pxrm > 0; pxrm--) {
			continue;
		}
	}
	if (57172 == 57172) {
		int lfgxkramgq;
		for (lfgxkramgq = 19; lfgxkramgq > 0; lfgxkramgq--) {
			continue;
		}
	}
	return 79230;
}

void tkyvyvb::ceimhpavamqtjdsnwolqrx(string xzxxiexaydoaq, double pltsjfzfkvxf, double zifpigorapyua) {
	string hxlnyxwmbwltm = "cpxdjfhyenzfwxzknpijfriunylpckymlsxdvjvsvlfnshvxaptmgofluwqlmpmdsswtdfwaxjeefb";
	double wrbpyiv = 63942;
	int ydbxfousplba = 2321;
	string matuybf = "rrgbsvhweflrythddscyywpfdwwrdjgltspdpymsavwqjdpqpvxpelqtrwlpslripvhmgaqfxtxgfzxptbc";
	int hsqjx = 3147;
	string eafnzcuif = "jhwmjdsxfjzedudpjkjbahpuhugudmwpzcroybgsvctwunuyvcwmtkwcwvbvzfmzsllzzatquhqfnewpkfymyqbpmqbnkhvh";
	int atavqosezguut = 215;
	if (63942 != 63942) {
		int fl;
		for (fl = 77; fl > 0; fl--) {
			continue;
		}
	}

}

string tkyvyvb::zfdpphjnrx(double epybkiro, bool ttpgyfekowwciyg) {
	double lmhwksxpbvt = 12147;
	string llfpjnixub = "yelyxvbbcemgfixbjjoiiqnswfcosmthtkrlterhebtxwttlfp";
	if (12147 != 12147) {
		int dl;
		for (dl = 77; dl > 0; dl--) {
			continue;
		}
	}
	return string("gjpidji");
}

double tkyvyvb::tfucqokcaehiegfpoeit() {
	int ertljnjqleajku = 3396;
	double eidvtufu = 73543;
	int jnlkdsl = 3306;
	int cbgiyg = 7486;
	int lasioqqn = 685;
	int kdiyekqdquhuhx = 181;
	double ytyyaguyvsk = 7896;
	string sjprrcrcqgzdj = "unfyrhmehwfxcgrgmhulbcxzka";
	string hshgmzdddu = "xwpnbfwynkitsamodvaxoybyfaxahmvjlicwbcwvykokqcdgaqzkctdzpertyszhboyclyqsirqhygzvvatodv";
	if (3306 == 3306) {
		int dwecl;
		for (dwecl = 59; dwecl > 0; dwecl--) {
			continue;
		}
	}
	if (string("xwpnbfwynkitsamodvaxoybyfaxahmvjlicwbcwvykokqcdgaqzkctdzpertyszhboyclyqsirqhygzvvatodv") == string("xwpnbfwynkitsamodvaxoybyfaxahmvjlicwbcwvykokqcdgaqzkctdzpertyszhboyclyqsirqhygzvvatodv")) {
		int hlvsoahj;
		for (hlvsoahj = 95; hlvsoahj > 0; hlvsoahj--) {
			continue;
		}
	}
	if (3396 == 3396) {
		int fwmuubkv;
		for (fwmuubkv = 70; fwmuubkv > 0; fwmuubkv--) {
			continue;
		}
	}
	if (181 != 181) {
		int ksemdu;
		for (ksemdu = 87; ksemdu > 0; ksemdu--) {
			continue;
		}
	}
	return 80170;
}

void tkyvyvb::xkwfoqhkyawhjffgrx(double vnnvd) {
	bool bvsljfwblrhvakn = false;
	double euxyfseqyy = 47753;
	int eqlzrvkwp = 1616;
	if (1616 != 1616) {
		int tkbn;
		for (tkbn = 21; tkbn > 0; tkbn--) {
			continue;
		}
	}
	if (1616 == 1616) {
		int glzmgebve;
		for (glzmgebve = 31; glzmgebve > 0; glzmgebve--) {
			continue;
		}
	}
	if (47753 != 47753) {
		int hnhv;
		for (hnhv = 67; hnhv > 0; hnhv--) {
			continue;
		}
	}
	if (false != false) {
		int buvbvjrp;
		for (buvbvjrp = 99; buvbvjrp > 0; buvbvjrp--) {
			continue;
		}
	}
	if (47753 != 47753) {
		int iorphab;
		for (iorphab = 96; iorphab > 0; iorphab--) {
			continue;
		}
	}

}

void tkyvyvb::hudfnwqbaam(int iqwgvmcv, bool vhocppbm, double winixqnhl) {
	double fqjkoxfjl = 7000;
	string uqvgyz = "odqcjfzjshiodmgihxrqjakjgnebbmmckcrp";
	bool rtkchmgyi = true;
	bool oxxvaxldiysyz = true;
	bool padzwakm = false;
	if (string("odqcjfzjshiodmgihxrqjakjgnebbmmckcrp") == string("odqcjfzjshiodmgihxrqjakjgnebbmmckcrp")) {
		int be;
		for (be = 29; be > 0; be--) {
			continue;
		}
	}
	if (true == true) {
		int uehnzwwug;
		for (uehnzwwug = 40; uehnzwwug > 0; uehnzwwug--) {
			continue;
		}
	}
	if (true == true) {
		int xgboprz;
		for (xgboprz = 11; xgboprz > 0; xgboprz--) {
			continue;
		}
	}
	if (true == true) {
		int ictfzlgy;
		for (ictfzlgy = 33; ictfzlgy > 0; ictfzlgy--) {
			continue;
		}
	}

}

void tkyvyvb::lvnwhqoysymcklebjci(double jznwgst, int kkekaik, int stjdu, string meovkswhzb, int nrnrvnu, string eijswusdxx, double sffjayxdiju) {
	string jckqnxeimgdew = "t";
	double tcfzrwnvw = 168;
	int odwvki = 3325;
	bool wjtgkpnsfntpxti = true;
	bool unhky = true;
	string tzaonsplpclla = "yxmpwoulwmhkjzipkniyirmzkckrnzucikjlkvmbdlqkqurkpeapbrguwiowa";
	double lytawxizvhtmjjp = 30104;
	string tvgcbigsyrwsl = "kwqugjzsdbymimfwueeqkd";
	bool qcduwluoxu = false;
	string jhzmbuixnk = "ntxtnlvqclbwbccilluejbappoqgwfkvpzcblhtdqffuwdcdfyw";
	if (true == true) {
		int gvgz;
		for (gvgz = 89; gvgz > 0; gvgz--) {
			continue;
		}
	}
	if (string("kwqugjzsdbymimfwueeqkd") != string("kwqugjzsdbymimfwueeqkd")) {
		int zxeknyiytr;
		for (zxeknyiytr = 35; zxeknyiytr > 0; zxeknyiytr--) {
			continue;
		}
	}
	if (3325 == 3325) {
		int lbqxwnf;
		for (lbqxwnf = 72; lbqxwnf > 0; lbqxwnf--) {
			continue;
		}
	}
	if (true != true) {
		int gubw;
		for (gubw = 16; gubw > 0; gubw--) {
			continue;
		}
	}

}

int tkyvyvb::ytlbdtdayihbqj(string yfzls, string zoyxudhmy, string kydrqncmesknwrf, bool hyjtdxadpqsvcmt, string oilxzohoua, double ajppxfqodrx) {
	int ovrtuzgcaiaf = 4046;
	string xqltxgfeym = "pvsnfmbmqeytulzirdtapgoajxxdvibftbvamuhcykfjtriktufikucbojpjprlnqorudsafxoveyxecif";
	double zwfirhlnwla = 13573;
	double swyuwda = 13796;
	double melfdlkeff = 7207;
	return 58744;
}

int tkyvyvb::jknzjtapuadlpsnnhk(int orpszd, bool hlcwxtp, double sbabwixnnygx, bool bqbnxfcoykn, int oaxofrrxdcuvh, double rzyssiiuxvdh, string cmthkifx, double rfuvggvtquy, string nrmiqfalxv, bool qksrjonrvjwb) {
	string bdastxxxyel = "pfnf";
	double wzrksgyqkm = 40770;
	double xisporrnw = 5403;
	bool dmtixefqxufbbg = true;
	double ishkirsayajrkcx = 17672;
	string djtqc = "vibqynoboxfckbqxnaspyuxobnwdhlmptnqyutpzujtoyknutabmadcavrjiavcocovyvuplaheq";
	string ziumgmynkehwq = "ghcuygcyfsrpaxvynfofduzjslzkcngxiknkwnqokmeybdlldarpuwelyptetxpldwtonkkexwhohkistjduncvavgsczmgivwd";
	double psogxz = 41519;
	if (string("vibqynoboxfckbqxnaspyuxobnwdhlmptnqyutpzujtoyknutabmadcavrjiavcocovyvuplaheq") == string("vibqynoboxfckbqxnaspyuxobnwdhlmptnqyutpzujtoyknutabmadcavrjiavcocovyvuplaheq")) {
		int otcf;
		for (otcf = 50; otcf > 0; otcf--) {
			continue;
		}
	}
	if (5403 != 5403) {
		int fhgunop;
		for (fhgunop = 58; fhgunop > 0; fhgunop--) {
			continue;
		}
	}
	if (5403 != 5403) {
		int sl;
		for (sl = 81; sl > 0; sl--) {
			continue;
		}
	}
	if (string("ghcuygcyfsrpaxvynfofduzjslzkcngxiknkwnqokmeybdlldarpuwelyptetxpldwtonkkexwhohkistjduncvavgsczmgivwd") != string("ghcuygcyfsrpaxvynfofduzjslzkcngxiknkwnqokmeybdlldarpuwelyptetxpldwtonkkexwhohkistjduncvavgsczmgivwd")) {
		int jshren;
		for (jshren = 44; jshren > 0; jshren--) {
			continue;
		}
	}
	if (5403 != 5403) {
		int itlwuxwg;
		for (itlwuxwg = 100; itlwuxwg > 0; itlwuxwg--) {
			continue;
		}
	}
	return 92138;
}

string tkyvyvb::geonyntkba(bool dspjogmpxn, double ejzqazovnwnhvv, bool rtizdchu, double jemvk, bool jemglgngvch, string dryxrne, int nitiolzeht, int mzptbmfwbts, double wwnhljlswtilgn) {
	string limhw = "lyswmddnrvapjdqezpzxtpjqaznrmljbjlnayssautalimuadlgdmccjz";
	int ievsho = 7529;
	string cttslvyizw = "yqpxqhtlbvoagyduyvbguctgxijqaclepmaecgjtvpuoppzdkjbnqefksyukiqqpfnicoyknfiqyad";
	int zxmvkata = 2871;
	double osfzdazzc = 48065;
	double uiajcl = 2482;
	if (48065 != 48065) {
		int liuzqf;
		for (liuzqf = 75; liuzqf > 0; liuzqf--) {
			continue;
		}
	}
	return string("wbychphbosa");
}

void tkyvyvb::alfqwyipjeybhmmephauss(bool oqfeygaqzw, string ujriomrnabeitn, double xiuct, string miedlpfayke, double rwladdaw) {
	double vvqba = 10448;
	if (10448 != 10448) {
		int craqalvf;
		for (craqalvf = 68; craqalvf > 0; craqalvf--) {
			continue;
		}
	}
	if (10448 != 10448) {
		int ozbe;
		for (ozbe = 5; ozbe > 0; ozbe--) {
			continue;
		}
	}

}

tkyvyvb::tkyvyvb() {
	this->geonyntkba(true, 8328, true, 50381, true, string("geqwmgpkeywxkmdnmosemhwvcagfrktjkrbnsztakfgqbeohavjjleossgftlrhqidfileydgzkhkhp"), 1593, 100, 10445);
	this->alfqwyipjeybhmmephauss(true, string("mhbektcwcrkzwobrmuyosyuihfuxxbkebkojbehvg"), 4699, string("bhlpslpujaydodjubeipkunmjgddzcdzerna"), 23626);
	this->ceimhpavamqtjdsnwolqrx(string("thxmzhemgnrwhbdnkkfrscdzsjyqncflkpnggoqjjiilukwmljwwefjl"), 20041, 24672);
	this->zfdpphjnrx(55972, false);
	this->tfucqokcaehiegfpoeit();
	this->xkwfoqhkyawhjffgrx(16673);
	this->hudfnwqbaam(5226, true, 15718);
	this->lvnwhqoysymcklebjci(1003, 5126, 577, string("dhcucocmakvjqbifowjuktpzyljacmtkqbpxfpgefvdclgtwlfssgqvdqlxyaf"), 3235, string("jxbxtmwzbdfetmtmpvackryhzbjnhoktuaerolh"), 37123);
	this->ytlbdtdayihbqj(string("bnqndrqguguyckxmoqujylotmxmiak"), string("ovquwgjvtycdpbcvotzmvxzubunjkxwkqbmmponnenkcgbrfqkqwrmwhrbwrjxivlgfpplyysygogvmnrvnwqgcojuupqagwzud"), string("obofcodfpwzcmaucdvagyiwnsxjhhhhbbollxucsecrdguwiajkaphmryhkjmzqjbvvntszmfxvwibb"), true, string("kubejqdbfkwtspjihhvaaewwfsctydgklmyctsdbyoeizxpdyvp"), 19529);
	this->jknzjtapuadlpsnnhk(1924, true, 43570, true, 4377, 82054, string("pqlqnzppjqllwgsvheskzgrkfrfuwwzpyjiptybgkbbe"), 37285, string("iuwskvyllptwfrnimkictjctxfjonsrzgfagpummtdixqgsfoudcyuwtksxnonniaafjyxuzeeufudsbjgxggxks"), false);
	this->xbimjueaxbysjecclhtyzujgs(16925, true, string("jbjwowehjpbzp"), 29321, true, string("ciwcpbio"), 129, 1372);
	this->qhkesfimemsfkyah(string("qlwajxlivtvfrjxdrjpjgnpjerkolxwtqbyxfscueeorfzpxrswtoinxruzyfkqla"), string("lctiuumgdaxbimlyksytdesmturm"), true, true, true, string("wcwuylwuwtlruwqtpaidrmbtblgldqezptw"), string("bdlwhskxxzhpm"), 11511, true, 1784);
	this->ybjfsuffftl(false, true, 7020);
	this->oxgnccazkynvduha(false, string("alxcxcpxsvpxoomknpcthghmyzlumm"), 502, 1729, false, 83667, 8186);
	this->hddseftrkhwbqluxmpdzjj(1544, 38561, 486, string("rxaivycyjdhehkymxhzbzndngqviaqduikiefpn"), 41729, false);
	this->jmdlgmavobxbsr(true, string("ipngsrr"), false, false, 1793, string("vowamioktx"), string("akecdixvldviugnkms"), false);
	this->ooxftmsxfbkakeryb(string("ztfck"), string("ipvnclxdcdvifwffsswoubvxxqvporyseyxfymvrinaehwzppbjkmpnwfsrtfwfy"), false, 21311, 5198);
	this->taejpvhopiujtlrohu();
	this->vzsgargwajr(3486, 1824, 10795, 1483, 1955, string("xdxnnogffevcsftuydslqsdvsddmicrmppfrqshnzurssefxxctoxqbbyiuankgadferznuinygsajndzmxdoaqjwodnxwqaes"), 30585, string("cuzuvwizbcuegndpglbjgjakxbmydsdifcekjroiuzwcfaymnuzpbyi"), 2048);
	this->xgagrorerdblxst(string("jumehqzkrusqlftusn"), 47507, 18904, string("azggqqwsydqpqjcgvhysmyshcfcjvspdzsnxoumnxlyhjlqmzlibndyxuqbamrstellkhmsjpverlhlvp"), 12413);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class zaizjii {
public:
	bool tbgnw;
	int yzfiietchwd;
	zaizjii();
	void hgkzxjcpxsyer(string gwikcbevh, string bdmwqbmbbtqd, double qbsbdlwqxp, string rbbsezuvhjqpli, string ezqcqkwoz, double cbkvubmxxp, bool epihimsksqdjfne);
	string tjkvphhirdwjhuzzkryy(int fszfzgq);
	int aeooleszuomj(double vafgiadn, int tivfiykd, bool ydofrimqy, string vwznejvzovjjip, bool ahundbdp, string ltshmmxm, double bggceybmv, double woxrkmdjdro);
	int crxblxaatgyvznvqqwxbk(bool mljmojzxnoyqmca);
	bool xqkyimxzertavqaowhcecsnvs(int qvpdwislkyepmog, double fikwemmiwen, int xgthdiwfejutqd, double svuakrddo, double xekmmee, int rrbywe, bool rmjodup, bool bnauefa, int ujdzzhnt, bool kdtqx);
	string pnjrztmwpxbxwutwdpvjwxtum();
	void zaswkdzrvsz(double bevyusl, string bmtadp, string kuzpef, double qzwamltab, double flbysihwczhpcr, double kzkllx, double vnxwnbmpka, bool ciupaeeyokul, bool humuugekglcqw);
	void gaceeotncnq(string tzplwl);
	string bmegcvkxfowvtlhuzv();
	void kqzqokcefkasswttweskuo(int afburpcvuup, int slfvxpsdqm, int bhcxdhvbisc, bool mdunzaajsayreiz, string iyrtmzhczwbdm);

protected:
	int gstkocwpbnmib;
	double fslewblkr;

	bool xlognpqmqx(bool tasauqlomrla, double dlfqude, bool wirdmxgnfwm, double nsolqdhxscwmx, string awpnq);

private:
	int anhvhlmjbogos;
	string fkrsdct;
	double qyyeoan;
	double bacbtsdppibcb;
	string rmyqyjzfuiqcymw;

	int okyynpnawclf(double kpcsdhrurk, int qwlakscpwqishea, double rdtkjssfsstka, double ywhqrkgmbueraws, int uwdqo, double pbqmmhvawbtqr, int xqsgnumzurcujzl, bool dfnpsjbedwn);
	int tbqfybpyaggu(bool gmdzrojdej, double wqjwzfnyds, double drqhdtwsxgi, int dttyelsr, int okvqqgsmzwlsngd, double wwyeexqlenjyp, bool gkpcwuwuttgfke, double bnbpnqeclcyuai, int mdqjx);
	string ijnhphbnfxmpbdvhn(string gxpxtwpmxlauk, bool khgdkpkrhjjbcr);
	bool melsschxihziiwvrzso(bool lbadlxkioajtdoy, string uozdz);

};


int zaizjii::okyynpnawclf(double kpcsdhrurk, int qwlakscpwqishea, double rdtkjssfsstka, double ywhqrkgmbueraws, int uwdqo, double pbqmmhvawbtqr, int xqsgnumzurcujzl, bool dfnpsjbedwn) {
	int pvkcga = 2390;
	double dblnddr = 34415;
	double qaqkbhcemmxmcur = 11185;
	bool bvabhbmlirryhqh = false;
	bool vjojxpddsstysv = false;
	bool rbopytiod = true;
	double cgmlaesfxuwed = 20507;
	double hbnifxgtwvi = 2768;
	string fvyrmsubdchned = "gyukeqmgnvtzwdmcncytuweiytoeqtjaxfigazuhmcjlmqglzewphm";
	if (false == false) {
		int znt;
		for (znt = 23; znt > 0; znt--) {
			continue;
		}
	}
	if (string("gyukeqmgnvtzwdmcncytuweiytoeqtjaxfigazuhmcjlmqglzewphm") == string("gyukeqmgnvtzwdmcncytuweiytoeqtjaxfigazuhmcjlmqglzewphm")) {
		int fcx;
		for (fcx = 63; fcx > 0; fcx--) {
			continue;
		}
	}
	return 35068;
}

int zaizjii::tbqfybpyaggu(bool gmdzrojdej, double wqjwzfnyds, double drqhdtwsxgi, int dttyelsr, int okvqqgsmzwlsngd, double wwyeexqlenjyp, bool gkpcwuwuttgfke, double bnbpnqeclcyuai, int mdqjx) {
	string khqvudakasat = "aiweajzdhdoaljskubyfjhlxaaufwfjahjvmxkfeggtksufsidkpqipc";
	return 36491;
}

string zaizjii::ijnhphbnfxmpbdvhn(string gxpxtwpmxlauk, bool khgdkpkrhjjbcr) {
	bool eqydbwnbla = true;
	bool rbziouqvtz = true;
	bool hxizzdcl = false;
	bool wftibqhcaiv = false;
	int apvwmom = 1177;
	return string("uezlnhiqvjxdqd");
}

bool zaizjii::melsschxihziiwvrzso(bool lbadlxkioajtdoy, string uozdz) {
	int jssbyl = 8177;
	if (8177 == 8177) {
		int eypci;
		for (eypci = 59; eypci > 0; eypci--) {
			continue;
		}
	}
	if (8177 != 8177) {
		int epqv;
		for (epqv = 25; epqv > 0; epqv--) {
			continue;
		}
	}
	if (8177 != 8177) {
		int harxqi;
		for (harxqi = 6; harxqi > 0; harxqi--) {
			continue;
		}
	}
	if (8177 == 8177) {
		int eddimwruj;
		for (eddimwruj = 20; eddimwruj > 0; eddimwruj--) {
			continue;
		}
	}
	if (8177 != 8177) {
		int atws;
		for (atws = 57; atws > 0; atws--) {
			continue;
		}
	}
	return false;
}

bool zaizjii::xlognpqmqx(bool tasauqlomrla, double dlfqude, bool wirdmxgnfwm, double nsolqdhxscwmx, string awpnq) {
	return true;
}

void zaizjii::hgkzxjcpxsyer(string gwikcbevh, string bdmwqbmbbtqd, double qbsbdlwqxp, string rbbsezuvhjqpli, string ezqcqkwoz, double cbkvubmxxp, bool epihimsksqdjfne) {
	string eihfpjuijraamc = "pajoyxqzgonrdckwirnuft";
	bool yztzumsr = false;
	string qkgzh = "xinsgipuhosnsxajzkygojmrdewzqwjlnqcdvtgrkktxraqgbhsffspoy";
	string eofllorgecgx = "npaocebghbnxdlbgqkclzpojwgqgvviigolmrkuzwirq";
	double zdjipffqsnpdci = 39754;
	bool wtlogatwanymoyf = true;

}

string zaizjii::tjkvphhirdwjhuzzkryy(int fszfzgq) {
	return string("csxrhfprgqg");
}

int zaizjii::aeooleszuomj(double vafgiadn, int tivfiykd, bool ydofrimqy, string vwznejvzovjjip, bool ahundbdp, string ltshmmxm, double bggceybmv, double woxrkmdjdro) {
	int ucblwjftvvo = 5518;
	string ctrbflteuzao = "rcjslmisvpivdmvcgilvfduxcusfmzprrgdpwtachndzfajngqwukcocenp";
	string ikedwybkkbquy = "nokqhlxyztgbpykylzkdhzksqezrjxgfepbhqsaptombcphbimrwagle";
	bool xjidomnm = false;
	string aiojxxxriterfft = "tacqwsuryukqtxfzyzvseteaoprdcfrbpdvueluwzcu";
	if (string("tacqwsuryukqtxfzyzvseteaoprdcfrbpdvueluwzcu") != string("tacqwsuryukqtxfzyzvseteaoprdcfrbpdvueluwzcu")) {
		int rop;
		for (rop = 6; rop > 0; rop--) {
			continue;
		}
	}
	if (5518 != 5518) {
		int ohivh;
		for (ohivh = 74; ohivh > 0; ohivh--) {
			continue;
		}
	}
	return 11248;
}

int zaizjii::crxblxaatgyvznvqqwxbk(bool mljmojzxnoyqmca) {
	string irzomobqoaptuw = "ziwbuylgzqjwoattzubtywmkdwvocnubovujwfoyezzsjjfgra";
	string dtdan = "gktsgnxbpmapwtafcixwchyuejjroefboulorfjsmpkvv";
	double olmuytldigxws = 33267;
	return 40713;
}

bool zaizjii::xqkyimxzertavqaowhcecsnvs(int qvpdwislkyepmog, double fikwemmiwen, int xgthdiwfejutqd, double svuakrddo, double xekmmee, int rrbywe, bool rmjodup, bool bnauefa, int ujdzzhnt, bool kdtqx) {
	double hhoeskjxtdr = 23278;
	bool ybchuau = false;
	string xzjpdg = "deiywlofqmxasaxddbxeixcrlpxjhaqkizmgyfjapbeerykspanlaysittfzijbhmtwevrszcqxdpvtjovrqezbliazma";
	bool rpzeiimjq = true;
	double rwsozelhc = 61166;
	double zeskwarvd = 11284;
	double lnhyhccuobgwdv = 48966;
	if (11284 != 11284) {
		int ff;
		for (ff = 93; ff > 0; ff--) {
			continue;
		}
	}
	if (48966 != 48966) {
		int fyhoqqmie;
		for (fyhoqqmie = 89; fyhoqqmie > 0; fyhoqqmie--) {
			continue;
		}
	}
	if (48966 == 48966) {
		int bobxc;
		for (bobxc = 46; bobxc > 0; bobxc--) {
			continue;
		}
	}
	if (11284 == 11284) {
		int uuxbegbfs;
		for (uuxbegbfs = 3; uuxbegbfs > 0; uuxbegbfs--) {
			continue;
		}
	}
	return false;
}

string zaizjii::pnjrztmwpxbxwutwdpvjwxtum() {
	string bcvzlwdzomvn = "fpvvvcayvrsnroymf";
	bool dcvzuwgz = true;
	int yeszqsrpwku = 671;
	bool ajnwpsouryu = true;
	if (true == true) {
		int tqgxqmvh;
		for (tqgxqmvh = 69; tqgxqmvh > 0; tqgxqmvh--) {
			continue;
		}
	}
	if (true == true) {
		int fga;
		for (fga = 95; fga > 0; fga--) {
			continue;
		}
	}
	if (string("fpvvvcayvrsnroymf") != string("fpvvvcayvrsnroymf")) {
		int yvkkidlfds;
		for (yvkkidlfds = 46; yvkkidlfds > 0; yvkkidlfds--) {
			continue;
		}
	}
	if (true == true) {
		int pxuu;
		for (pxuu = 89; pxuu > 0; pxuu--) {
			continue;
		}
	}
	if (string("fpvvvcayvrsnroymf") == string("fpvvvcayvrsnroymf")) {
		int okcipnuz;
		for (okcipnuz = 61; okcipnuz > 0; okcipnuz--) {
			continue;
		}
	}
	return string("qffrlztaigzmaqtbwzx");
}

void zaizjii::zaswkdzrvsz(double bevyusl, string bmtadp, string kuzpef, double qzwamltab, double flbysihwczhpcr, double kzkllx, double vnxwnbmpka, bool ciupaeeyokul, bool humuugekglcqw) {
	int bofziz = 1506;
	string yyezvgy = "ypecczcc";
	bool nmcfuyvkye = true;
	int qwilvqczpfrmdc = 1219;
	bool uhmnyxb = true;
	bool gdxlkufdhcaai = true;
	bool hiuowjltyc = true;
	double qasyvnzaibtpan = 38560;
	int kbwkle = 901;
	if (string("ypecczcc") != string("ypecczcc")) {
		int zkec;
		for (zkec = 35; zkec > 0; zkec--) {
			continue;
		}
	}

}

void zaizjii::gaceeotncnq(string tzplwl) {
	double qxmnghj = 12613;
	int gxqwkzacmufng = 1160;
	bool ujitc = true;
	bool qgyvjylvkoofcq = false;
	double pfrzkdk = 86098;
	double fmygzkf = 8470;
	if (12613 != 12613) {
		int nry;
		for (nry = 34; nry > 0; nry--) {
			continue;
		}
	}

}

string zaizjii::bmegcvkxfowvtlhuzv() {
	return string("vouzffv");
}

void zaizjii::kqzqokcefkasswttweskuo(int afburpcvuup, int slfvxpsdqm, int bhcxdhvbisc, bool mdunzaajsayreiz, string iyrtmzhczwbdm) {
	bool mooxnatdjcedarn = true;
	bool krjxiqcamdemm = false;
	bool ektowcctvdc = false;
	bool bohgodrgroyg = true;
	string ldpaxfbsoe = "kytsgnwxxaavkrpxohuqazijfqalgoesczecsfenqssevhqsghbrfslpoxfhgzhkwibqfamjxfniycxvmsqylopx";
	int mmrzxnsszj = 1921;
	string dsjiadxbujbqfy = "ofhzcdlhidkcz";
	int yvlqofsmstoiv = 4234;
	double uikzx = 30206;
	bool xzepnrmcr = true;
	if (1921 != 1921) {
		int rrlncrhi;
		for (rrlncrhi = 77; rrlncrhi > 0; rrlncrhi--) {
			continue;
		}
	}
	if (string("ofhzcdlhidkcz") == string("ofhzcdlhidkcz")) {
		int tzjxntae;
		for (tzjxntae = 89; tzjxntae > 0; tzjxntae--) {
			continue;
		}
	}
	if (string("ofhzcdlhidkcz") != string("ofhzcdlhidkcz")) {
		int vgdxspy;
		for (vgdxspy = 63; vgdxspy > 0; vgdxspy--) {
			continue;
		}
	}
	if (false != false) {
		int zpbax;
		for (zpbax = 25; zpbax > 0; zpbax--) {
			continue;
		}
	}
	if (true == true) {
		int datwc;
		for (datwc = 16; datwc > 0; datwc--) {
			continue;
		}
	}

}

zaizjii::zaizjii() {
	this->hgkzxjcpxsyer(string("ufnsqrgxpoct"), string("hhczieyvjgbjafzxxmswfoitpnxrvieqizqytugbpecbqugfrgnqsxrfvyupfcvchvdxms"), 26704, string("komlweqhlmgahlbmdmdpuaou"), string("ibolxszxhxpmbtxd"), 10278, true);
	this->tjkvphhirdwjhuzzkryy(2547);
	this->aeooleszuomj(13149, 6100, false, string("evokpkifbyxwstrlijrqdtqxsxbzpvjeikpzuis"), true, string("johayazqphqbicmwluziiflptnbzlsivhlgsgcsmobonumwncaolcwbyzvtdqulnclpwmgarpch"), 12261, 25258);
	this->crxblxaatgyvznvqqwxbk(true);
	this->xqkyimxzertavqaowhcecsnvs(4185, 53781, 6651, 24716, 18007, 5614, true, true, 1557, true);
	this->pnjrztmwpxbxwutwdpvjwxtum();
	this->zaswkdzrvsz(43221, string("jcejodhkwsadekmgfuujidrpndtjvrvvdprcgvy"), string("ogdykydzbokjoijfulorrhmubhwwhvkgxcdeencxurokbkrczxioftnkjpcoht"), 9636, 19243, 1761, 28246, true, true);
	this->gaceeotncnq(string("pdanuizfocbndqhxvvducivsssfuhowzacnxexbzqdvxdzsreevrkhmmbzmafh"));
	this->bmegcvkxfowvtlhuzv();
	this->kqzqokcefkasswttweskuo(1587, 2148, 854, false, string("bfaquutyqvyrrmqdhvlxaxkqumquiiultcxdsupsbbyoeevmekx"));
	this->xlognpqmqx(false, 3480, false, 31763, string("zmhnzqhpdxmprqfogvgmvuouamlvjvjkclhz"));
	this->okyynpnawclf(3361, 4835, 14956, 64641, 759, 12202, 2629, false);
	this->tbqfybpyaggu(true, 8785, 26244, 1252, 4767, 28807, false, 572, 6832);
	this->ijnhphbnfxmpbdvhn(string("gcedwvkligefjbbjagzhdltowvpjxdczes"), false);
	this->melsschxihziiwvrzso(false, string("guuviwbqibgleytceojlmpgeorxpotiajuffwcxcfnczvsmzxz"));
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class vorvonh {
public:
	int xiqcfevae;
	double fcvgp;
	vorvonh();
	bool azwilxzcdtma(int ayjrxsonshf, double gbogazgcnhlhzls, int kqplrsi, double lopiahcp, double loxhypirzipm, double mewxtipfqs, bool xalthgsvm, string xjuzulnbpsvpc, bool vicoeyanyxbxyd, bool gkfbmcosrfgixyo);
	bool mjgtoutrybhthrwj(int bzsmzaqpuamqmi, bool yhumqnanfgajtw, string ieqendldocve, double kwzgnzjpxp, double mowilw, bool pwrmhyfmh, double bzoypvqr, int onvvtrsyq);
	double leborusmeza(double cnglaypbmkk, bool tohgamkgau, string uolwwhptouovhtu, int nsphvti, double olbbvicdwclrakz);
	int bnihqpnqdechnzswoe(bool mpuinbgedznm, bool rvnlhgt);
	double knblmdrifnkdnmjq();
	bool udzfzptjmxvdhadg(int srmryryffesesh, string jxvvnlviitab, bool habzepl, string fiuoienvp, bool jtplpvllsj);
	void qqhbtlwquwfgfkcdm(string xxdvmgl, string iwumgipuymy, double fnpgxhpbyyx, string yvijsgt, bool ppzzpitnkv, bool ztihsux, bool zsmbxeqysgwpp, bool oqkocownf);
	bool xvjxisaepkwen(bool aakvffuasiobka, int anqkusvwrkh);

protected:
	double hzyxwwkwvhst;
	bool mxvkyjtci;
	double avqbonxcypzq;
	int hvsjmkl;

	string jhcljhrkivjy(double xjtiftdyixmq, int rjvmd, string vrvoexotzcrf, int dzvqezfu, int dzdhskor, int qpjimz, bool jqtlyahhgd, string lygvjiesltwmbs, bool rsyidbvzgflotrp);
	bool qpnagitpszcruzazipf(int ageuuuhftmxvbd, double mlmdctbbznvhq, double aixlsrbiyifug, double wvvvyxycuj, double otscqv, double nzgtjrymlasujal, string majki, bool uqknxvcqp, string sxrbzuphuiuj, string hiwgygqns);
	int sfbohelvampmojsjqe(double gdzqeyefhpuhies, double kcyfxbiiesjtzwo, double fubqkku, bool nckdmweffcg, string sboohchowrw, string enbfswxkkobgcd, string ztcomgkxyyo);
	double nbnlgwqtslnywxg(double bxylgvenorem, string qcrhwyiaq, int vmalm, int dzvjq, double xcfelizijxcjrq, int ybehwzuhqwtzyj, double yhzmen, int mlqty, bool wdexyxcesyoy);
	bool xzsukoozctztkongkca(double rxbpbllmnictx, string nwojvxbsgso, int opqogzlzsok);
	int glyeotvlnlcnqnvfqw(int kkxuozwwuujzew, double yuqmppfub, double spacbvogekkw, bool fojeiugdvdrjltu, bool lkzedhepowzmoe, bool zqwronxdww, bool pxogsdzip, int gycjis, double clcjtjq, bool vxkrvinihmleftd);
	string ttlmxyxdlmi(bool buorx, string borsgnlauu, double xrzuqgqzc, bool ktmbjdyhmxq, string esxtoyecbwo, bool tnksff, bool xpasivnkh);
	int kganqnempjvspmmji(bool mknjclipjabqtnt, int dxbdxojeczpjdwk, bool kvshi);

private:
	bool taugjpx;
	int moizxxrktu;
	double rfcjsvggbhfu;
	string veaqdia;

	string agdqqsuaucp(bool xtuemgjgtcqyv, bool brccwj, double dizhqkvhygjie, bool vkgjq, string ivpfjsruidelv);
	bool xrmqliunepbumpvvuye(bool nkvkne, bool qwippehen, int mqybiseqjsgnfdy);

};


string vorvonh::agdqqsuaucp(bool xtuemgjgtcqyv, bool brccwj, double dizhqkvhygjie, bool vkgjq, string ivpfjsruidelv) {
	bool fehxamsiawvc = false;
	double qafivadl = 33512;
	string iodtr = "vlrhvdufqemzpeznmqpzsbmtprwmnbonmtowjfjnzjzbcsbwklsgamhqpviv";
	double mqfuryuczcvoog = 467;
	double amgghluqoul = 33418;
	return string("klsvb");
}

bool vorvonh::xrmqliunepbumpvvuye(bool nkvkne, bool qwippehen, int mqybiseqjsgnfdy) {
	int piyywkwnupw = 286;
	int tjvri = 246;
	int axnekzzskmxrg = 4466;
	string onxitrpcubeeq = "imwydfbmusswgevqgcytccyfpzbu";
	int gazegoai = 6790;
	if (6790 != 6790) {
		int tpaica;
		for (tpaica = 4; tpaica > 0; tpaica--) {
			continue;
		}
	}
	if (286 != 286) {
		int vsxijpsf;
		for (vsxijpsf = 97; vsxijpsf > 0; vsxijpsf--) {
			continue;
		}
	}
	if (string("imwydfbmusswgevqgcytccyfpzbu") == string("imwydfbmusswgevqgcytccyfpzbu")) {
		int vrggv;
		for (vrggv = 44; vrggv > 0; vrggv--) {
			continue;
		}
	}
	if (286 == 286) {
		int kyqq;
		for (kyqq = 100; kyqq > 0; kyqq--) {
			continue;
		}
	}
	return false;
}

string vorvonh::jhcljhrkivjy(double xjtiftdyixmq, int rjvmd, string vrvoexotzcrf, int dzvqezfu, int dzdhskor, int qpjimz, bool jqtlyahhgd, string lygvjiesltwmbs, bool rsyidbvzgflotrp) {
	string jzpqb = "wdqj";
	bool wldybzjpoq = false;
	if (string("wdqj") != string("wdqj")) {
		int nrwyghrsiq;
		for (nrwyghrsiq = 78; nrwyghrsiq > 0; nrwyghrsiq--) {
			continue;
		}
	}
	return string("sknrnybdhwkelpxskmvi");
}

bool vorvonh::qpnagitpszcruzazipf(int ageuuuhftmxvbd, double mlmdctbbznvhq, double aixlsrbiyifug, double wvvvyxycuj, double otscqv, double nzgtjrymlasujal, string majki, bool uqknxvcqp, string sxrbzuphuiuj, string hiwgygqns) {
	string iwyhxbasrzvhxwr = "dixdeuspwxdcjuwnfysvbshpomorlitdygxegnxmvzbtzslwjdtbppehma";
	double phwepkkrcl = 38752;
	double zdbvwgnsrem = 12516;
	int wimtocmmytnfyyx = 923;
	double onswpgciolsow = 4402;
	string xcflrqmvwszwn = "ghblauzrug";
	double sdortbnvugf = 45956;
	bool bxgqmqsdcb = false;
	int ugfugfjqhddauj = 468;
	int xiibzhykyfjcb = 8450;
	if (8450 != 8450) {
		int mo;
		for (mo = 4; mo > 0; mo--) {
			continue;
		}
	}
	if (38752 == 38752) {
		int mgjj;
		for (mgjj = 16; mgjj > 0; mgjj--) {
			continue;
		}
	}
	if (string("ghblauzrug") == string("ghblauzrug")) {
		int xlf;
		for (xlf = 80; xlf > 0; xlf--) {
			continue;
		}
	}
	return true;
}

int vorvonh::sfbohelvampmojsjqe(double gdzqeyefhpuhies, double kcyfxbiiesjtzwo, double fubqkku, bool nckdmweffcg, string sboohchowrw, string enbfswxkkobgcd, string ztcomgkxyyo) {
	return 80864;
}

double vorvonh::nbnlgwqtslnywxg(double bxylgvenorem, string qcrhwyiaq, int vmalm, int dzvjq, double xcfelizijxcjrq, int ybehwzuhqwtzyj, double yhzmen, int mlqty, bool wdexyxcesyoy) {
	bool mnuhwctrmdx = true;
	string tsqrdcwquxgbbl = "teyqeqhepccfxpajdwhjrncxdjkvvkaieqm";
	bool whhvbpyiuszyi = false;
	int jphkojkbrcb = 2981;
	bool jemvqalfhnou = true;
	return 59179;
}

bool vorvonh::xzsukoozctztkongkca(double rxbpbllmnictx, string nwojvxbsgso, int opqogzlzsok) {
	bool nebdpe = true;
	string nzkdklinmf = "xyidbxoyzxynfiuxnpnkcyteaxggryesteo";
	bool hbqmzkxzzkuzvu = true;
	return true;
}

int vorvonh::glyeotvlnlcnqnvfqw(int kkxuozwwuujzew, double yuqmppfub, double spacbvogekkw, bool fojeiugdvdrjltu, bool lkzedhepowzmoe, bool zqwronxdww, bool pxogsdzip, int gycjis, double clcjtjq, bool vxkrvinihmleftd) {
	int murshkuacjeopdi = 675;
	bool mfoqdqgrsvgmqy = true;
	int kusjevmwtom = 1259;
	string lzmprnqvfwwxwow = "ykjculswkfpbqlrxbqmcftxczwojqmnptgfgohhnpnnfwqikrfgdwpurxtidkuabdscz";
	if (true != true) {
		int wleaary;
		for (wleaary = 29; wleaary > 0; wleaary--) {
			continue;
		}
	}
	if (true != true) {
		int chppk;
		for (chppk = 90; chppk > 0; chppk--) {
			continue;
		}
	}
	if (true != true) {
		int zgbpbfu;
		for (zgbpbfu = 9; zgbpbfu > 0; zgbpbfu--) {
			continue;
		}
	}
	if (675 == 675) {
		int uopbegovo;
		for (uopbegovo = 28; uopbegovo > 0; uopbegovo--) {
			continue;
		}
	}
	return 21392;
}

string vorvonh::ttlmxyxdlmi(bool buorx, string borsgnlauu, double xrzuqgqzc, bool ktmbjdyhmxq, string esxtoyecbwo, bool tnksff, bool xpasivnkh) {
	int ajvlhlizd = 544;
	int sghsphm = 7618;
	string zinxawjgfuzok = "jgfbylzwjfaebvmfq";
	if (544 == 544) {
		int xh;
		for (xh = 57; xh > 0; xh--) {
			continue;
		}
	}
	if (string("jgfbylzwjfaebvmfq") == string("jgfbylzwjfaebvmfq")) {
		int rrdjernnvm;
		for (rrdjernnvm = 96; rrdjernnvm > 0; rrdjernnvm--) {
			continue;
		}
	}
	if (7618 == 7618) {
		int om;
		for (om = 39; om > 0; om--) {
			continue;
		}
	}
	if (string("jgfbylzwjfaebvmfq") != string("jgfbylzwjfaebvmfq")) {
		int cfw;
		for (cfw = 59; cfw > 0; cfw--) {
			continue;
		}
	}
	if (string("jgfbylzwjfaebvmfq") == string("jgfbylzwjfaebvmfq")) {
		int gdgweekf;
		for (gdgweekf = 25; gdgweekf > 0; gdgweekf--) {
			continue;
		}
	}
	return string("nmal");
}

int vorvonh::kganqnempjvspmmji(bool mknjclipjabqtnt, int dxbdxojeczpjdwk, bool kvshi) {
	double pdtjsrtgwvuivn = 27615;
	int ymjkwebzkjtxy = 1798;
	int eqlqm = 4896;
	if (27615 != 27615) {
		int ywqok;
		for (ywqok = 93; ywqok > 0; ywqok--) {
			continue;
		}
	}
	return 28563;
}

bool vorvonh::azwilxzcdtma(int ayjrxsonshf, double gbogazgcnhlhzls, int kqplrsi, double lopiahcp, double loxhypirzipm, double mewxtipfqs, bool xalthgsvm, string xjuzulnbpsvpc, bool vicoeyanyxbxyd, bool gkfbmcosrfgixyo) {
	int xxkkazi = 1506;
	if (1506 != 1506) {
		int lzgoacnq;
		for (lzgoacnq = 26; lzgoacnq > 0; lzgoacnq--) {
			continue;
		}
	}
	if (1506 == 1506) {
		int ugmdl;
		for (ugmdl = 57; ugmdl > 0; ugmdl--) {
			continue;
		}
	}
	if (1506 == 1506) {
		int tdth;
		for (tdth = 50; tdth > 0; tdth--) {
			continue;
		}
	}
	return false;
}

bool vorvonh::mjgtoutrybhthrwj(int bzsmzaqpuamqmi, bool yhumqnanfgajtw, string ieqendldocve, double kwzgnzjpxp, double mowilw, bool pwrmhyfmh, double bzoypvqr, int onvvtrsyq) {
	bool aqjwfipfvteoi = false;
	double bmkupsnhslmbq = 30984;
	bool igxihvjttk = false;
	if (30984 == 30984) {
		int wujy;
		for (wujy = 42; wujy > 0; wujy--) {
			continue;
		}
	}
	if (30984 == 30984) {
		int qjd;
		for (qjd = 21; qjd > 0; qjd--) {
			continue;
		}
	}
	if (false != false) {
		int wocsayjat;
		for (wocsayjat = 56; wocsayjat > 0; wocsayjat--) {
			continue;
		}
	}
	return true;
}

double vorvonh::leborusmeza(double cnglaypbmkk, bool tohgamkgau, string uolwwhptouovhtu, int nsphvti, double olbbvicdwclrakz) {
	string hcdblxngzoulut = "jdslkbraeznxlonffuwokkxuwexaxtiekecuraqrgfsfvczrchnfizgozebnifitznopprlrdmevjbhtfugrtnblunnpvobp";
	int sstgjgu = 5691;
	int eridrvprpmsazvh = 792;
	string ldnxihyyvxumkw = "ppmpbvrshzpykwavrnnvmqzwhxacdnxaldbdcsnadteuyycwerskv";
	string xpcpjaepqc = "llvekpufszlgscnmyzsrqbxbovtujklaahkrufcfpm";
	int kwonhkdrr = 2475;
	int bpnduybr = 2523;
	int vjajsltx = 5165;
	string kqljlztvseyfa = "rkhnlopvdgttxhwnkgcluheccsdysnlqgyoztolspouljzwcwowbskqagdxdolxe";
	bool bzihqigbf = false;
	if (string("jdslkbraeznxlonffuwokkxuwexaxtiekecuraqrgfsfvczrchnfizgozebnifitznopprlrdmevjbhtfugrtnblunnpvobp") != string("jdslkbraeznxlonffuwokkxuwexaxtiekecuraqrgfsfvczrchnfizgozebnifitznopprlrdmevjbhtfugrtnblunnpvobp")) {
		int yagzdwgy;
		for (yagzdwgy = 43; yagzdwgy > 0; yagzdwgy--) {
			continue;
		}
	}
	if (string("rkhnlopvdgttxhwnkgcluheccsdysnlqgyoztolspouljzwcwowbskqagdxdolxe") != string("rkhnlopvdgttxhwnkgcluheccsdysnlqgyoztolspouljzwcwowbskqagdxdolxe")) {
		int creelxfd;
		for (creelxfd = 31; creelxfd > 0; creelxfd--) {
			continue;
		}
	}
	if (string("llvekpufszlgscnmyzsrqbxbovtujklaahkrufcfpm") == string("llvekpufszlgscnmyzsrqbxbovtujklaahkrufcfpm")) {
		int pyszdaw;
		for (pyszdaw = 79; pyszdaw > 0; pyszdaw--) {
			continue;
		}
	}
	return 48560;
}

int vorvonh::bnihqpnqdechnzswoe(bool mpuinbgedznm, bool rvnlhgt) {
	string ukzdskrdp = "ovjjucjiejwxpydhny";
	string hgydcvpfbcgnxj = "r";
	double hqmfuidcglvpkg = 9225;
	bool jzxxlmzazxuq = true;
	int kulmmf = 7613;
	bool zsmzjylijyxsaz = true;
	double didelyhdykx = 942;
	int bzwlpstk = 7381;
	double ggzsuvyqd = 9698;
	if (true == true) {
		int dmk;
		for (dmk = 67; dmk > 0; dmk--) {
			continue;
		}
	}
	return 37017;
}

double vorvonh::knblmdrifnkdnmjq() {
	double rnfqnujwgrwl = 81403;
	bool hhzckmni = true;
	bool fexssblkxuo = true;
	double erpiiquc = 3048;
	double xyniuq = 1846;
	if (81403 != 81403) {
		int iaohccsp;
		for (iaohccsp = 83; iaohccsp > 0; iaohccsp--) {
			continue;
		}
	}
	if (true != true) {
		int sxwb;
		for (sxwb = 17; sxwb > 0; sxwb--) {
			continue;
		}
	}
	if (81403 == 81403) {
		int fssajuug;
		for (fssajuug = 1; fssajuug > 0; fssajuug--) {
			continue;
		}
	}
	if (81403 != 81403) {
		int tsgcsbz;
		for (tsgcsbz = 16; tsgcsbz > 0; tsgcsbz--) {
			continue;
		}
	}
	return 33090;
}

bool vorvonh::udzfzptjmxvdhadg(int srmryryffesesh, string jxvvnlviitab, bool habzepl, string fiuoienvp, bool jtplpvllsj) {
	string zefxigkdwe = "qokqxxpkcjywzsumrberjcqezfgcyzjhycgaacrxoazzmhmrwhupdbbhqtvwuemfvspsataiefhyhpuskxdaguuuubzqkyc";
	int zrfllvnm = 6756;
	int zxooczimczqe = 3024;
	if (string("qokqxxpkcjywzsumrberjcqezfgcyzjhycgaacrxoazzmhmrwhupdbbhqtvwuemfvspsataiefhyhpuskxdaguuuubzqkyc") != string("qokqxxpkcjywzsumrberjcqezfgcyzjhycgaacrxoazzmhmrwhupdbbhqtvwuemfvspsataiefhyhpuskxdaguuuubzqkyc")) {
		int gisnusvuwt;
		for (gisnusvuwt = 75; gisnusvuwt > 0; gisnusvuwt--) {
			continue;
		}
	}
	if (6756 == 6756) {
		int vknbvrpf;
		for (vknbvrpf = 44; vknbvrpf > 0; vknbvrpf--) {
			continue;
		}
	}
	if (6756 != 6756) {
		int vhlfcc;
		for (vhlfcc = 26; vhlfcc > 0; vhlfcc--) {
			continue;
		}
	}
	return false;
}

void vorvonh::qqhbtlwquwfgfkcdm(string xxdvmgl, string iwumgipuymy, double fnpgxhpbyyx, string yvijsgt, bool ppzzpitnkv, bool ztihsux, bool zsmbxeqysgwpp, bool oqkocownf) {
	double qrnrg = 13835;
	int brtfafxvogxde = 7557;
	bool ozqprmoywz = false;
	double gofad = 33055;
	string djoym = "luhycpuhprrbuscrubqposwssbbefxdbbmsrgrdpceabseovxmexdmkgnwowtgzyttcrdhfhvouqzdqhdfpeypfdhw";
	double pxtoibzqz = 16004;
	string vspdykole = "gygqspmbnayqtxusivwuuduahqbdbjegnwlzxonfqhmatjdmbaxbahbupvghsnoutfxotvaikfmmkupvycmllzffourvvakymv";
	int dmixfhucmj = 4652;
	string xobxzybzlguav = "znjdosfxdvtkxtlhqdxoyruhcfozhxqwcubxskvtudzcbhauoxxwbvlrspzouszxiydykvwiwxl";
	if (string("gygqspmbnayqtxusivwuuduahqbdbjegnwlzxonfqhmatjdmbaxbahbupvghsnoutfxotvaikfmmkupvycmllzffourvvakymv") == string("gygqspmbnayqtxusivwuuduahqbdbjegnwlzxonfqhmatjdmbaxbahbupvghsnoutfxotvaikfmmkupvycmllzffourvvakymv")) {
		int klkkgzkep;
		for (klkkgzkep = 41; klkkgzkep > 0; klkkgzkep--) {
			continue;
		}
	}
	if (string("znjdosfxdvtkxtlhqdxoyruhcfozhxqwcubxskvtudzcbhauoxxwbvlrspzouszxiydykvwiwxl") == string("znjdosfxdvtkxtlhqdxoyruhcfozhxqwcubxskvtudzcbhauoxxwbvlrspzouszxiydykvwiwxl")) {
		int mrm;
		for (mrm = 72; mrm > 0; mrm--) {
			continue;
		}
	}
	if (33055 != 33055) {
		int nxqaalbwi;
		for (nxqaalbwi = 22; nxqaalbwi > 0; nxqaalbwi--) {
			continue;
		}
	}
	if (string("znjdosfxdvtkxtlhqdxoyruhcfozhxqwcubxskvtudzcbhauoxxwbvlrspzouszxiydykvwiwxl") == string("znjdosfxdvtkxtlhqdxoyruhcfozhxqwcubxskvtudzcbhauoxxwbvlrspzouszxiydykvwiwxl")) {
		int re;
		for (re = 95; re > 0; re--) {
			continue;
		}
	}
	if (false != false) {
		int afuignrj;
		for (afuignrj = 22; afuignrj > 0; afuignrj--) {
			continue;
		}
	}

}

bool vorvonh::xvjxisaepkwen(bool aakvffuasiobka, int anqkusvwrkh) {
	int ndmpgwxvxjob = 687;
	bool wzhzp = false;
	bool olgldzyjlujfljp = false;
	string brenygokrnpdc = "lqworvfblhckziirfnqhzxqjm";
	bool imouvfbpom = true;
	if (false != false) {
		int dqyrekxvb;
		for (dqyrekxvb = 43; dqyrekxvb > 0; dqyrekxvb--) {
			continue;
		}
	}
	if (false == false) {
		int dckpsdtqb;
		for (dckpsdtqb = 82; dckpsdtqb > 0; dckpsdtqb--) {
			continue;
		}
	}
	if (false == false) {
		int msbsmn;
		for (msbsmn = 3; msbsmn > 0; msbsmn--) {
			continue;
		}
	}
	if (true != true) {
		int gv;
		for (gv = 89; gv > 0; gv--) {
			continue;
		}
	}
	return false;
}

vorvonh::vorvonh() {
	this->azwilxzcdtma(4566, 43216, 1719, 17303, 27170, 42471, true, string("kfpudhgcfyvqlpdqwdvurlz"), false, true);
	this->mjgtoutrybhthrwj(1795, false, string("ljpmlngfcuklaizegvdpnjvpjajoiamvgbgmkrzrmuihamncefxurawlpnejtyfpuxlvnhsinvlhhjoenpbeu"), 52534, 12394, true, 1303, 3487);
	this->leborusmeza(19374, true, string("mxlvmhqtivixhzbeezffqvwccnkztoxsjexmipklwuehn"), 4674, 13152);
	this->bnihqpnqdechnzswoe(false, true);
	this->knblmdrifnkdnmjq();
	this->udzfzptjmxvdhadg(168, string("navtlksxhjmfmahxasqnjifcrngomtoewudmvtyuinwqmkodaxyasqqwbgutukzzjxvslukhzhpfj"), true, string("grlktlidcoanzlyidlzggrruapngooimoqseznyebrdxjilkpyitjemdpahalwyzqxiojgwkpuxoqpnozycitclumaydhjaqe"), true);
	this->qqhbtlwquwfgfkcdm(string("vqcpvmafzgcbyosuhxsdanmxouhuamol"), string("ieyrviodecrybkorzwduatrxohfdrqkgpgdaepucgqvkdbtzvfezuwvkenbyqcpilzrhtpkyzvg"), 21141, string("tzk"), true, true, false, false);
	this->xvjxisaepkwen(true, 981);
	this->jhcljhrkivjy(45605, 6553, string("powbwrtqbmudxohbxanshvckbnpsdtbumcurjopywcgqgtzcdjejx"), 658, 140, 1809, false, string("dbdqeviaybfkkjrkliypksazxfwzwvzslijakuniehimcqdnkyibvehkgytzrvzxnwjguzkizescwazffcdkpzcv"), true);
	this->qpnagitpszcruzazipf(5077, 334, 32733, 65056, 45137, 23553, string("yyomyabfmjzbroxjbdajpexhfqmfticpppqraf"), false, string("dbajttrjjazjbpyvpmkbpcsxqiiydbcikntkrqqcgncoc"), string("nfryrhbbtqldkrzuyktzjbxbppuwwtzvnxeesswypakcrwcmimdhjrgopcskpcfa"));
	this->sfbohelvampmojsjqe(1605, 36953, 34943, true, string("zuwxefx"), string("vgzytxcohiihpkfzkjqzyjtgboxtswuhitncpypkjbshgebsmjxxchorujxhqxc"), string("vsecsijwoshlilepzvyrtevmnvraepfasmiugqkqzgbwzhvkyjgsdvsydusitrspmugosaqfeahphapyitfpyp"));
	this->nbnlgwqtslnywxg(34432, string("asyqwmnsfcnnfwbidvofezkrybwwfrcfliymmzxquyzvzeynrnlezavgztdni"), 1433, 4710, 15706, 4560, 419, 1700, true);
	this->xzsukoozctztkongkca(27633, string("fzxppgoxowcaxikltefxctkuwqncdxdwcagtump"), 973);
	this->glyeotvlnlcnqnvfqw(1900, 10943, 16408, true, false, true, true, 4388, 57465, true);
	this->ttlmxyxdlmi(true, string("xswwgvxwhpaqffyvzdfusvypnfpxgvsoqygxeolmcvydwdzhmfudylf"), 6978, false, string("jahniubqhsfqx"), true, true);
	this->kganqnempjvspmmji(true, 2753, false);
	this->agdqqsuaucp(false, true, 14545, true, string("pfejnvahxnkfswnktlbxoawuedbrppypdcfzcnrlbojgtwyslwhclcdkcbrosorrtvaklmmtjmo"));
	this->xrmqliunepbumpvvuye(true, false, 5251);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class mtcwljy {
public:
	string ibnfnfrpffqjrfk;
	double libvmdecngwhdf;
	string gkojdcrwpw;
	mtcwljy();
	void jlpvrutgkbgtxndjvc(string jnfjvxfxyaiosw, bool gbbcug);
	double ajbnqpauwt();
	double wytubjulfgifghllbfwcef(bool wxuvpyieoo, string usqrzal, int hhknwtsgw, string nymkjuebbwljmx, int dtwxcwitihrc, int vtcubgwjmwbt, double szkqocqidpvhr, bool ecdmxywevgjyhcd, string qleklve, int ywvthypxtuay);
	bool rhcqlgqwifl(int cksgbsrknrb, string tsywwvhrerpxgou, bool sdnhjvk, string ajqmjadmkoxeilg, bool ijzsndexc);
	string rlukszshtxrlyrmhfamjgspcw(double kpezi, bool znsupxx, bool lhqjq, double cvruiiqqja, bool ckmrolqvidclq);
	string hdeazaiphachjebyevnj();
	double tcuwwcbccst(string obwajldu, string jjjjbnwlgolym, int inoojnwv, string vkogkekiyslk);

protected:
	string bxysxayapl;

	void xiovrbtkpfgrfat(bool rrudzvxr, string jcwaob, double vmeego);
	bool sjzauuzhmcbqkewefhg(double tqbrz, bool zuszvcoos, bool dgotcwnzdguicd, string vimltsfpvpzkxe, bool eaigyhohmftd);
	double ltqhwsyjytzsxrpdafwxmh(string tyvhietsugbkoz, string fqkjzgoblkuh, string crzpushrqqeb, double wxktehsfvrpap, string xgbtrblhrlcq, double xqrrye, double lqnvejsq, bool ytjci, double kckpo, double svtpqlgykumid);
	string cnrvjhmmfqbnphgowvhngygfn(double wbxmgopnynbdwit);
	bool pgsnvrqoachl(int ltnbrnjr, string icamddhbx, bool kkwcjqmmr, string abktymd, string pkniinnhseevj, int jjqlmi, double bqvljobqrqndvs);
	bool zjldpznacbhcvojufleltyh(string hasuxhnz, string pwwykipsh);

private:
	string lcqxcbuwfesds;
	int hvfkyopn;
	double wntvdtvhqwkfatt;
	string vbhqqlszkcs;
	bool cwzizd;

	double kqmihstnrrvuhu(int evrznphi, double ihtbtxbgxksazif, int rrcaqhplxzuvmts);
	bool hmgrupjgjd(int uldxt, bool trnzpdxddcsyul, int fmqaez, double fmfdxmmcdsgigh);

};


double mtcwljy::kqmihstnrrvuhu(int evrznphi, double ihtbtxbgxksazif, int rrcaqhplxzuvmts) {
	bool atezalpm = true;
	int qazouovguve = 800;
	bool vyzwxir = true;
	int ovipqz = 6666;
	int rjusudrfmrf = 5581;
	bool ykcsagxownuzp = true;
	if (true == true) {
		int xgxylat;
		for (xgxylat = 11; xgxylat > 0; xgxylat--) {
			continue;
		}
	}
	if (true != true) {
		int xuxmrdzb;
		for (xuxmrdzb = 33; xuxmrdzb > 0; xuxmrdzb--) {
			continue;
		}
	}
	if (800 != 800) {
		int nzrqxg;
		for (nzrqxg = 65; nzrqxg > 0; nzrqxg--) {
			continue;
		}
	}
	if (true != true) {
		int kvdeucn;
		for (kvdeucn = 45; kvdeucn > 0; kvdeucn--) {
			continue;
		}
	}
	if (6666 == 6666) {
		int jkbaq;
		for (jkbaq = 83; jkbaq > 0; jkbaq--) {
			continue;
		}
	}
	return 89012;
}

bool mtcwljy::hmgrupjgjd(int uldxt, bool trnzpdxddcsyul, int fmqaez, double fmfdxmmcdsgigh) {
	return false;
}

void mtcwljy::xiovrbtkpfgrfat(bool rrudzvxr, string jcwaob, double vmeego) {
	double abvrkjorkoy = 15707;
	string vljijazcrvf = "agbkexyuvwaiwfnaknxlmj";
	string civlrwlggh = "hnatkcuzwyqybklkxlviqxzbwtvheywvtzhgytecrthpiampznqbopemgirjwiwzsyjjgdltkveahtookecxxubteguzn";
	int rciheveytpo = 868;
	bool nlrigljapvyima = false;
	double ckgdljrf = 66800;
	string axbmsunnai = "bhxazzrsbqructpqrwfrnebsuwbwfomsmvwfmmmnxcfwgvttpdtonsergugjutppbmihbub";
	if (15707 != 15707) {
		int xayudf;
		for (xayudf = 39; xayudf > 0; xayudf--) {
			continue;
		}
	}
	if (66800 == 66800) {
		int kkqlyoo;
		for (kkqlyoo = 82; kkqlyoo > 0; kkqlyoo--) {
			continue;
		}
	}

}

bool mtcwljy::sjzauuzhmcbqkewefhg(double tqbrz, bool zuszvcoos, bool dgotcwnzdguicd, string vimltsfpvpzkxe, bool eaigyhohmftd) {
	bool kgkrs = true;
	string xywzjbbmzrx = "ykxfmprzypvrcxzyybpgqpeipulmnfugziniqyghrvcpfgevdlyydksglgwou";
	string ximje = "algdbeepuitwtdwmcdbhbxinpomqshkrboejsbblihmdosztfjunzinbpvstiidbbpgcgunyrlvxwblqblmjifezxgulcfgplvyy";
	bool dbynvmgny = false;
	if (string("ykxfmprzypvrcxzyybpgqpeipulmnfugziniqyghrvcpfgevdlyydksglgwou") != string("ykxfmprzypvrcxzyybpgqpeipulmnfugziniqyghrvcpfgevdlyydksglgwou")) {
		int rimfpourl;
		for (rimfpourl = 43; rimfpourl > 0; rimfpourl--) {
			continue;
		}
	}
	if (string("ykxfmprzypvrcxzyybpgqpeipulmnfugziniqyghrvcpfgevdlyydksglgwou") != string("ykxfmprzypvrcxzyybpgqpeipulmnfugziniqyghrvcpfgevdlyydksglgwou")) {
		int cqzyeuhv;
		for (cqzyeuhv = 44; cqzyeuhv > 0; cqzyeuhv--) {
			continue;
		}
	}
	return true;
}

double mtcwljy::ltqhwsyjytzsxrpdafwxmh(string tyvhietsugbkoz, string fqkjzgoblkuh, string crzpushrqqeb, double wxktehsfvrpap, string xgbtrblhrlcq, double xqrrye, double lqnvejsq, bool ytjci, double kckpo, double svtpqlgykumid) {
	string ebxekkyj = "yqzugdcjkwckzsdbzwgwhirglkrxu";
	double iyljtqjzx = 40588;
	double pcjxsixdtfz = 15054;
	if (15054 != 15054) {
		int jgkqkroame;
		for (jgkqkroame = 3; jgkqkroame > 0; jgkqkroame--) {
			continue;
		}
	}
	if (15054 != 15054) {
		int uzvkh;
		for (uzvkh = 82; uzvkh > 0; uzvkh--) {
			continue;
		}
	}
	if (15054 != 15054) {
		int imrj;
		for (imrj = 34; imrj > 0; imrj--) {
			continue;
		}
	}
	if (15054 != 15054) {
		int hwn;
		for (hwn = 62; hwn > 0; hwn--) {
			continue;
		}
	}
	return 40412;
}

string mtcwljy::cnrvjhmmfqbnphgowvhngygfn(double wbxmgopnynbdwit) {
	bool gnhectmgwjeib = false;
	bool bilej = false;
	double zlmla = 43785;
	double almpekmjam = 32201;
	string bmspnqpl = "lyktdwptywigydsacogqqabscdthjjjfykvbszcgbttbftcphmxqthfjubmctmwjlxuwtjkntpcqwqausjyvkhunlsfxj";
	string spdsjcluagivx = "utaymkihxxlozweqiyqgfheduqhklnbyzhwalctgphnnqrhmeckdsjyyryyaokcqedho";
	string rvwmsrjfn = "crdchixskehmuywomnkcwpwtewyi";
	bool wmocuyvlhzium = true;
	string mibcjnqfdjud = "";
	if (string("") != string("")) {
		int bhmsvovwpz;
		for (bhmsvovwpz = 47; bhmsvovwpz > 0; bhmsvovwpz--) {
			continue;
		}
	}
	if (true == true) {
		int wkavxus;
		for (wkavxus = 62; wkavxus > 0; wkavxus--) {
			continue;
		}
	}
	if (string("") != string("")) {
		int odqralto;
		for (odqralto = 86; odqralto > 0; odqralto--) {
			continue;
		}
	}
	return string("uscpvzblbxh");
}

bool mtcwljy::pgsnvrqoachl(int ltnbrnjr, string icamddhbx, bool kkwcjqmmr, string abktymd, string pkniinnhseevj, int jjqlmi, double bqvljobqrqndvs) {
	double cxdkqpjpqfgor = 23922;
	bool owtlrrjwaufvg = true;
	if (true != true) {
		int xsg;
		for (xsg = 11; xsg > 0; xsg--) {
			continue;
		}
	}
	if (23922 == 23922) {
		int tylan;
		for (tylan = 51; tylan > 0; tylan--) {
			continue;
		}
	}
	if (23922 == 23922) {
		int jvunrwrmm;
		for (jvunrwrmm = 72; jvunrwrmm > 0; jvunrwrmm--) {
			continue;
		}
	}
	if (23922 == 23922) {
		int vmgkzsatex;
		for (vmgkzsatex = 14; vmgkzsatex > 0; vmgkzsatex--) {
			continue;
		}
	}
	if (23922 == 23922) {
		int uxirs;
		for (uxirs = 46; uxirs > 0; uxirs--) {
			continue;
		}
	}
	return false;
}

bool mtcwljy::zjldpznacbhcvojufleltyh(string hasuxhnz, string pwwykipsh) {
	string govsczn = "bxzitftcobfryxycliztfo";
	string uqwnpb = "wkewlomyyhqvlovueylfogqkbjutozsazzyqeqyuqwksbqmiu";
	string bmjoutxrmdcyv = "elskxzquwwsqmjoldnyjkbtptwlqnbacywgtizeuvjgjbsabybpegncqslhcfrohdkpasvsjsyxgxhbiymwunwxykuvspymwpcg";
	double wepjve = 16035;
	bool wqnrexniaqjvvn = true;
	string vbgfysp = "cpyzujcxavelzknwupuovtqcvjjfpqabxkknuseijkmlferhqjmfvfdxucwy";
	int syxrytfzxze = 2054;
	if (string("bxzitftcobfryxycliztfo") == string("bxzitftcobfryxycliztfo")) {
		int qwvupj;
		for (qwvupj = 88; qwvupj > 0; qwvupj--) {
			continue;
		}
	}
	if (2054 == 2054) {
		int nntunnqpfl;
		for (nntunnqpfl = 60; nntunnqpfl > 0; nntunnqpfl--) {
			continue;
		}
	}
	if (true != true) {
		int tan;
		for (tan = 23; tan > 0; tan--) {
			continue;
		}
	}
	if (string("wkewlomyyhqvlovueylfogqkbjutozsazzyqeqyuqwksbqmiu") == string("wkewlomyyhqvlovueylfogqkbjutozsazzyqeqyuqwksbqmiu")) {
		int daippba;
		for (daippba = 12; daippba > 0; daippba--) {
			continue;
		}
	}
	if (16035 != 16035) {
		int joiaopgh;
		for (joiaopgh = 99; joiaopgh > 0; joiaopgh--) {
			continue;
		}
	}
	return true;
}

void mtcwljy::jlpvrutgkbgtxndjvc(string jnfjvxfxyaiosw, bool gbbcug) {
	double mdmiro = 56924;
	bool oundvaedizqgxtu = false;
	if (false == false) {
		int czjf;
		for (czjf = 68; czjf > 0; czjf--) {
			continue;
		}
	}
	if (false == false) {
		int nuxo;
		for (nuxo = 74; nuxo > 0; nuxo--) {
			continue;
		}
	}
	if (56924 != 56924) {
		int srihyab;
		for (srihyab = 34; srihyab > 0; srihyab--) {
			continue;
		}
	}
	if (false == false) {
		int ys;
		for (ys = 85; ys > 0; ys--) {
			continue;
		}
	}

}

double mtcwljy::ajbnqpauwt() {
	string colhkapjpliyutj = "yvpzqhunxwnfziutatxqnydgguoamvqnvtozaisdbcywgmmlwrfrnsutgwsopakpgrovizkiecspswfeuajcijueydb";
	double evoqvqtt = 22162;
	int akzrbgmjg = 3150;
	double fanjucxprknf = 35587;
	int hcjtkpp = 2617;
	if (string("yvpzqhunxwnfziutatxqnydgguoamvqnvtozaisdbcywgmmlwrfrnsutgwsopakpgrovizkiecspswfeuajcijueydb") != string("yvpzqhunxwnfziutatxqnydgguoamvqnvtozaisdbcywgmmlwrfrnsutgwsopakpgrovizkiecspswfeuajcijueydb")) {
		int qsw;
		for (qsw = 45; qsw > 0; qsw--) {
			continue;
		}
	}
	if (22162 == 22162) {
		int oa;
		for (oa = 48; oa > 0; oa--) {
			continue;
		}
	}
	if (2617 == 2617) {
		int kpxsect;
		for (kpxsect = 89; kpxsect > 0; kpxsect--) {
			continue;
		}
	}
	if (22162 != 22162) {
		int gs;
		for (gs = 75; gs > 0; gs--) {
			continue;
		}
	}
	return 41338;
}

double mtcwljy::wytubjulfgifghllbfwcef(bool wxuvpyieoo, string usqrzal, int hhknwtsgw, string nymkjuebbwljmx, int dtwxcwitihrc, int vtcubgwjmwbt, double szkqocqidpvhr, bool ecdmxywevgjyhcd, string qleklve, int ywvthypxtuay) {
	int vbpmyesyxyb = 395;
	int uxzyhwdoosorn = 1713;
	if (395 == 395) {
		int yhojy;
		for (yhojy = 37; yhojy > 0; yhojy--) {
			continue;
		}
	}
	if (1713 != 1713) {
		int xdxmdmpj;
		for (xdxmdmpj = 28; xdxmdmpj > 0; xdxmdmpj--) {
			continue;
		}
	}
	if (395 != 395) {
		int aaxyj;
		for (aaxyj = 54; aaxyj > 0; aaxyj--) {
			continue;
		}
	}
	return 63305;
}

bool mtcwljy::rhcqlgqwifl(int cksgbsrknrb, string tsywwvhrerpxgou, bool sdnhjvk, string ajqmjadmkoxeilg, bool ijzsndexc) {
	string jrfkrptefezmv = "aiwintaawsjbccyyhsnkgiqsavcehcknrikfrwkf";
	string cbwtmycmw = "exxprrxloydnlnrltearzjuymaffmilpgzrzlmsmutmechezrpwvtxjzbehbpobjuuqjwcnvotkjhawwdsghjbghzmcywq";
	bool mzges = false;
	double yuvnywwfvobgxox = 21501;
	int kqkvzlq = 3909;
	int qqzsromxnoi = 6542;
	if (string("aiwintaawsjbccyyhsnkgiqsavcehcknrikfrwkf") == string("aiwintaawsjbccyyhsnkgiqsavcehcknrikfrwkf")) {
		int piafbj;
		for (piafbj = 87; piafbj > 0; piafbj--) {
			continue;
		}
	}
	if (21501 != 21501) {
		int nc;
		for (nc = 5; nc > 0; nc--) {
			continue;
		}
	}
	if (false == false) {
		int mbkuik;
		for (mbkuik = 45; mbkuik > 0; mbkuik--) {
			continue;
		}
	}
	if (3909 != 3909) {
		int ambvjcwbyo;
		for (ambvjcwbyo = 12; ambvjcwbyo > 0; ambvjcwbyo--) {
			continue;
		}
	}
	if (string("aiwintaawsjbccyyhsnkgiqsavcehcknrikfrwkf") == string("aiwintaawsjbccyyhsnkgiqsavcehcknrikfrwkf")) {
		int pkgswcr;
		for (pkgswcr = 65; pkgswcr > 0; pkgswcr--) {
			continue;
		}
	}
	return true;
}

string mtcwljy::rlukszshtxrlyrmhfamjgspcw(double kpezi, bool znsupxx, bool lhqjq, double cvruiiqqja, bool ckmrolqvidclq) {
	string obpeazlne = "qjurazcfbqzigdguclwqfhm";
	string zzheiafjsn = "b";
	int srszifjmhauy = 2480;
	if (2480 == 2480) {
		int lo;
		for (lo = 31; lo > 0; lo--) {
			continue;
		}
	}
	return string("lpthhcjwmkfeqnrolz");
}

string mtcwljy::hdeazaiphachjebyevnj() {
	int gunnub = 957;
	string iwdqviyrgonwaa = "vbfeeiysiybxgxvzmdelfxohmeymxlwpzccemkaq";
	bool obyvfso = true;
	bool spkjwq = true;
	string qqzckcacqvwce = "ajmoaidnzujwcnwmpsrpfmel";
	double fgihptpndepj = 294;
	int epehwazx = 5610;
	double pgsllqxcexdythp = 6989;
	bool rtooplygvip = true;
	if (string("vbfeeiysiybxgxvzmdelfxohmeymxlwpzccemkaq") != string("vbfeeiysiybxgxvzmdelfxohmeymxlwpzccemkaq")) {
		int imlnq;
		for (imlnq = 23; imlnq > 0; imlnq--) {
			continue;
		}
	}
	if (true != true) {
		int nw;
		for (nw = 47; nw > 0; nw--) {
			continue;
		}
	}
	if (294 != 294) {
		int cdlwejtpgr;
		for (cdlwejtpgr = 6; cdlwejtpgr > 0; cdlwejtpgr--) {
			continue;
		}
	}
	if (294 != 294) {
		int tovss;
		for (tovss = 14; tovss > 0; tovss--) {
			continue;
		}
	}
	return string("gotfh");
}

double mtcwljy::tcuwwcbccst(string obwajldu, string jjjjbnwlgolym, int inoojnwv, string vkogkekiyslk) {
	string fweyzsixdzfywq = "gnpwsupojapsgjnxghqowwdtfiwizpzhmmcdegpydvgsrnynbuefqkyyjjpf";
	double aomfbfeyesyujcx = 5402;
	int yvdfpd = 2858;
	double opvnhoklg = 45224;
	int oovzgsczusiso = 2270;
	if (string("gnpwsupojapsgjnxghqowwdtfiwizpzhmmcdegpydvgsrnynbuefqkyyjjpf") != string("gnpwsupojapsgjnxghqowwdtfiwizpzhmmcdegpydvgsrnynbuefqkyyjjpf")) {
		int fwoiwzzjuu;
		for (fwoiwzzjuu = 74; fwoiwzzjuu > 0; fwoiwzzjuu--) {
			continue;
		}
	}
	return 25938;
}

mtcwljy::mtcwljy() {
	this->jlpvrutgkbgtxndjvc(string("ekybjgydtglhxwidxltgyktygztdnjzjulqbluzmhmmhtsexliddtekvc"), false);
	this->ajbnqpauwt();
	this->wytubjulfgifghllbfwcef(false, string(""), 4479, string("inbgdqtzjdonqcqmkxqaaxdovhnoyjuczvykwnjeejkjscocsczzsonbxvodbrrbajsdmqdkusieyfxwobjimcvrqgiefj"), 3285, 4075, 14287, true, string("bnxuprihzpwihqgmadkcdnbjtcfwruenz"), 969);
	this->rhcqlgqwifl(676, string("hiowujtsvlelzwjwejfjcpzbvbjwmhqcxyfaomyloraetteoxygituprqtegrnjdhgdyrtilebtjoivffmfsywtplmutyz"), false, string("qjojvlaqmbmhmgoidigieajviugjtvulywxvgwhxfjqcqnycihuumvmvyvprc"), false);
	this->rlukszshtxrlyrmhfamjgspcw(24501, true, false, 14977, false);
	this->hdeazaiphachjebyevnj();
	this->tcuwwcbccst(string("xaaijceohbugfzqwydvpqqcqmlhtgzciiajdsblthzjlsmc"), string("vjdacx"), 1178, string("tjprngcbifgrwvhige"));
	this->xiovrbtkpfgrfat(true, string("xmrogmfh"), 29170);
	this->sjzauuzhmcbqkewefhg(10580, true, false, string("ozwmuoyhlmqygfjazfdcjqziyeocxysjmsxuskbuygzmspazvyqnvthgovjctmzpxtjrpweskwtlbxvlkbubfjhwxdatybyx"), true);
	this->ltqhwsyjytzsxrpdafwxmh(string("rxfigceywwklmwfapvpsvkugrhtyrlpsf"), string("kmvwklhblr"), string("tnzgtvpjphrmbmdzbnmrvidicysbaeprrfbrolvbhnxcmogcgcaatwksbooxopyqyimmyxvkdltviwuwtnjescfbzxg"), 35105, string("lhkxualenlqemifnjdkbj"), 9769, 10585, false, 21107, 42588);
	this->cnrvjhmmfqbnphgowvhngygfn(9300);
	this->pgsnvrqoachl(1358, string("yydiag"), true, string("jajqtlznvayndlaaofjvopjwazxpaumysucvpnbfllxfqcnljqqhatmnhktrvsxypgxhehrmh"), string("pvgdbemlzoqeualmwodwbmjmgaqpurvjfucpuyaobtvmphzaroaupqubxdsbwyauztpucuvcpuohkgbdnih"), 3151, 4280);
	this->zjldpznacbhcvojufleltyh(string("xralpyjgiyvtazxqcxmzjsexqxwasdpgmnlylbfighvwomzhbkmvpfetauzyjwjalywpbirlrkrhwbjtmpjswtkezjnnmwp"), string("dknndnbaoxdupslvuhjsxaiifqgezitbwsrwufnhqqxyefinzpue"));
	this->kqmihstnrrvuhu(8283, 33272, 1162);
	this->hmgrupjgjd(2629, false, 5555, 28508);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class pfstuoj {
public:
	double zzuztozzizwz;
	string spagxhgvfidsaq;
	bool tzckih;
	bool kjysgppvyoinury;
	int thsvo;
	pfstuoj();
	void abwsdpnuxddefpkfdnuu(bool bbrclb, int emobld);
	bool nqwherjyppqqvkyxwailm(double sggyx, string dhmzdkzdrk, int ccreiwvuev, double mmzivamjpsrm, double fifitlxftuhglu, bool iyvudfemczdd, double uwhstfxqpssr, int vkwlgep, string upzmsrhclu);
	void aklaywtnumkrsnsmlvrmzegz(bool vkyaedzqvioj, string rjrzvwr, int cfqxz, double ytkddeedcyt, double awaoduoaaqkbzx, bool fybbuzvdut, string psfpov, bool uueeminkqq, int przzwdwtoit);
	void dudmbjxgmgwakgdkucve(bool ghjnxsldvj, bool nqonjymjdjk, double rzvoiohrb, bool mqtigrhurifmjg, bool wwauvhbgqzz);
	bool ibuaozlwsxilmlozubhtldvm(string oxeyrneull, int gvkvki, bool wgeoz, double msgqms, int hqclhckocm, string vbndubdcxvzmd, double pahlp);
	int lfnplomjovv(bool aobhbjtp, int mupclbgvqbpbr, int nojif, double qlnbqb, string cqpmysez, bool qpfchmwpbywdab, double brdjgpdkqxrm, int kofumvwrcpmywbs, bool fltbha, double asriczslsy);

protected:
	int ccwgeojm;

	double epqqchgjcwxfnr(string ngxcggjhmfr, double icbtafxknwfhm);
	double ainhgcxqcknnrljal(int bjnscfg);
	void rzvaugoevcmgfwcuvelbq();
	double xsvsbmpkulmcshhhhz(string apcxkbtoaud, double knewzq, double ehgcsqszvv, bool pweacpbgxy, string tlcxhz, int tbxbyx, double bcrepv);

private:
	double khzdvhzhophevlr;
	double jmwiiynzuv;
	string fufjmoqvw;

	void zesagwrijnmwo(bool gbnxw, double suzwhkpequjkl, string zbsqoqt, bool peicvzzyddxnv, double qaxcyr, int vbwrtukuigl);
	void hgbxxynmgnwx();
	void cqheqhllsmazzjfcxbzql(bool liooh, string luovvi, double mruxgkdwpjapyl, double erzqewusrxl, int khitw, int rgmmltwnwzi, string yxgtsrvb, bool povxifdfgvu, bool sfqkneztxpyqsqt, int ypnrelwcvot);

};


void pfstuoj::zesagwrijnmwo(bool gbnxw, double suzwhkpequjkl, string zbsqoqt, bool peicvzzyddxnv, double qaxcyr, int vbwrtukuigl) {
	double xwpgc = 24849;
	double zkjoushf = 39264;
	bool tirbl = false;
	bool mtttjx = false;
	bool dpaoywe = false;
	double anaqiatkp = 21277;
	int fwgrvineujxwhl = 1100;
	double huogcgbdqufxelp = 37117;
	bool fzkzlexefv = true;
	if (37117 == 37117) {
		int ytfd;
		for (ytfd = 92; ytfd > 0; ytfd--) {
			continue;
		}
	}

}

void pfstuoj::hgbxxynmgnwx() {
	int vddvivtrnxjvlsy = 2432;
	double ctlvjcknypgegr = 69852;
	string wkamqkq = "kjkjvpzaxcjiitirgwyiyvnmmxhmzwhlgkuypcvzemdykqyeszqhfjngepeimobnkiqpxellmpfrpuiyvlytezdafhqmi";
	int yiaudimcurvxbf = 1084;
	bool rsblwwvyoaws = false;
	if (string("kjkjvpzaxcjiitirgwyiyvnmmxhmzwhlgkuypcvzemdykqyeszqhfjngepeimobnkiqpxellmpfrpuiyvlytezdafhqmi") != string("kjkjvpzaxcjiitirgwyiyvnmmxhmzwhlgkuypcvzemdykqyeszqhfjngepeimobnkiqpxellmpfrpuiyvlytezdafhqmi")) {
		int pmyyzzlhb;
		for (pmyyzzlhb = 89; pmyyzzlhb > 0; pmyyzzlhb--) {
			continue;
		}
	}
	if (false != false) {
		int oblhyjag;
		for (oblhyjag = 85; oblhyjag > 0; oblhyjag--) {
			continue;
		}
	}
	if (1084 == 1084) {
		int sctpxthe;
		for (sctpxthe = 76; sctpxthe > 0; sctpxthe--) {
			continue;
		}
	}
	if (false == false) {
		int toenco;
		for (toenco = 61; toenco > 0; toenco--) {
			continue;
		}
	}

}

void pfstuoj::cqheqhllsmazzjfcxbzql(bool liooh, string luovvi, double mruxgkdwpjapyl, double erzqewusrxl, int khitw, int rgmmltwnwzi, string yxgtsrvb, bool povxifdfgvu, bool sfqkneztxpyqsqt, int ypnrelwcvot) {
	double xxbptweteohu = 3385;
	bool dzoojmf = true;
	double jutqmlzmtu = 11697;
	bool qgnlrafiayws = false;
	int drfjmwnhjj = 1755;
	bool aodjjpbpv = false;

}

double pfstuoj::epqqchgjcwxfnr(string ngxcggjhmfr, double icbtafxknwfhm) {
	int qlpfaqfsp = 788;
	int dcagzkonydgavaj = 791;
	bool ruerj = false;
	int iwzdph = 1993;
	int rknkivmotogqf = 521;
	double aekoiievzhi = 64264;
	if (false == false) {
		int og;
		for (og = 11; og > 0; og--) {
			continue;
		}
	}
	return 41354;
}

double pfstuoj::ainhgcxqcknnrljal(int bjnscfg) {
	string binomevhyu = "ehceyhghdzbqrouzgaothfjdkzflrmxcodgiuwibvyjs";
	string gjtuqmd = "evgpptfavdfiqyqlykddxoifiahkqqblahtgixlvnjkrainyhzhsgysqaifybkjukvu";
	string vgxcrya = "qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf";
	if (string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf") == string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf")) {
		int ipvd;
		for (ipvd = 46; ipvd > 0; ipvd--) {
			continue;
		}
	}
	if (string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf") == string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf")) {
		int wsyovvby;
		for (wsyovvby = 49; wsyovvby > 0; wsyovvby--) {
			continue;
		}
	}
	if (string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf") != string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf")) {
		int igyqtft;
		for (igyqtft = 9; igyqtft > 0; igyqtft--) {
			continue;
		}
	}
	if (string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf") != string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf")) {
		int bplmxnze;
		for (bplmxnze = 70; bplmxnze > 0; bplmxnze--) {
			continue;
		}
	}
	if (string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf") != string("qqktzvskyqqepggetdrwpkppnssaxgrstcwlwdcf")) {
		int hqozbgg;
		for (hqozbgg = 57; hqozbgg > 0; hqozbgg--) {
			continue;
		}
	}
	return 38630;
}

void pfstuoj::rzvaugoevcmgfwcuvelbq() {
	string wfomnpcfd = "erjcdsvgmnpyprjofhoqibhaqmoecjvruwtgghfjdcprwuetlhxbvmgnvprvnhjqgzdvuxonvmalk";
	string rsotr = "nxmacgbhvqqqsggwjkbeleglembpqytdcknbgzgsszwnzgabxwcpcfrovkufpwnrerqjvztkvrxtduogxxoepgkgndbrimuowziv";
	double cngttrkakwxxata = 27951;
	string mwrep = "rpgpohwnxfverzfgkgkbyludlzyuzumnerixajudxlzidikcmubeckqyczwvuolppzftgrxcuubnu";
	string zotvrkfftingyt = "";
	if (27951 != 27951) {
		int kwrpeoh;
		for (kwrpeoh = 28; kwrpeoh > 0; kwrpeoh--) {
			continue;
		}
	}
	if (string("") != string("")) {
		int zxgozy;
		for (zxgozy = 29; zxgozy > 0; zxgozy--) {
			continue;
		}
	}
	if (string("rpgpohwnxfverzfgkgkbyludlzyuzumnerixajudxlzidikcmubeckqyczwvuolppzftgrxcuubnu") != string("rpgpohwnxfverzfgkgkbyludlzyuzumnerixajudxlzidikcmubeckqyczwvuolppzftgrxcuubnu")) {
		int wbwg;
		for (wbwg = 95; wbwg > 0; wbwg--) {
			continue;
		}
	}

}

double pfstuoj::xsvsbmpkulmcshhhhz(string apcxkbtoaud, double knewzq, double ehgcsqszvv, bool pweacpbgxy, string tlcxhz, int tbxbyx, double bcrepv) {
	return 30408;
}

void pfstuoj::abwsdpnuxddefpkfdnuu(bool bbrclb, int emobld) {
	double bbsmfbikcrd = 6819;
	string glsjhtjgj = "gsaaukclphwemqftcrtujlusgjjrpsavuibcrhzkmbrfujziektp";
	bool rqymksfqq = true;
	string onntkfl = "sodnrmfrggusmevnzwlirfnhkpcoceuembatzpfihhofixemdubucwffwwexcjhjbpngzxdjrkjmzrtioyfdea";
	int zmnitca = 3657;
	bool efjkn = true;
	string ewimmcvkgzcqx = "pznxqnysvaypkqsijympsjxmqeshtfaexmherxhtrpbycfgnofsxskdtnjjtexxoaavhyafpocfibcaqqpizezlx";
	bool gvsvddvaiq = true;
	int ehalykmbh = 6445;

}

bool pfstuoj::nqwherjyppqqvkyxwailm(double sggyx, string dhmzdkzdrk, int ccreiwvuev, double mmzivamjpsrm, double fifitlxftuhglu, bool iyvudfemczdd, double uwhstfxqpssr, int vkwlgep, string upzmsrhclu) {
	bool jawxiruijyowe = true;
	int gdvsphnnwmi = 6826;
	bool peeagfsvnn = false;
	bool jonltgrfonc = false;
	bool acxjeuduxsi = true;
	if (false == false) {
		int que;
		for (que = 2; que > 0; que--) {
			continue;
		}
	}
	if (false != false) {
		int hbnkitzy;
		for (hbnkitzy = 7; hbnkitzy > 0; hbnkitzy--) {
			continue;
		}
	}
	if (true != true) {
		int jqubk;
		for (jqubk = 76; jqubk > 0; jqubk--) {
			continue;
		}
	}
	return true;
}

void pfstuoj::aklaywtnumkrsnsmlvrmzegz(bool vkyaedzqvioj, string rjrzvwr, int cfqxz, double ytkddeedcyt, double awaoduoaaqkbzx, bool fybbuzvdut, string psfpov, bool uueeminkqq, int przzwdwtoit) {
	double roney = 40655;
	int gfqveugjqor = 441;
	bool vhmtlrcljtm = true;
	bool gvspurwqpdq = false;
	string dqvmcpdocnkps = "gmhefvabyhxthsfognrdsdjnyyvzvyzbwwivgfenpv";
	double ongzznmyerh = 39024;
	int acrevygjasuh = 1895;
	bool ixqalprwkx = true;
	double bggqwdrhccopivi = 5908;
	if (1895 == 1895) {
		int ywdavewe;
		for (ywdavewe = 43; ywdavewe > 0; ywdavewe--) {
			continue;
		}
	}

}

void pfstuoj::dudmbjxgmgwakgdkucve(bool ghjnxsldvj, bool nqonjymjdjk, double rzvoiohrb, bool mqtigrhurifmjg, bool wwauvhbgqzz) {
	string sitomtrzqryd = "jsc";
	double vsopiddqwf = 2505;
	int fdwhjssn = 817;
	double zdwplizmyidb = 10225;
	double ccisihrdo = 12420;
	double quqtte = 86604;
	if (2505 == 2505) {
		int mjfslq;
		for (mjfslq = 35; mjfslq > 0; mjfslq--) {
			continue;
		}
	}

}

bool pfstuoj::ibuaozlwsxilmlozubhtldvm(string oxeyrneull, int gvkvki, bool wgeoz, double msgqms, int hqclhckocm, string vbndubdcxvzmd, double pahlp) {
	bool yranxuooaogsx = true;
	string jphkqrlrphrkm = "uoleokiwzmizswuwotrayklwygehlebankwawnozskasmgpgydzmdcsppeljoc";
	double diojl = 5495;
	bool nkqrulhitcg = true;
	string kpeigsiwea = "bhljmllofhyotfizjytugpeosjwvitngffjlhkaetyvmeihzgiyqneiabaucrgtamlniksmhseaesfuhckeouh";
	bool apqdteaywvgizds = true;
	double mlgyxffrh = 77862;
	if (true != true) {
		int pmzspba;
		for (pmzspba = 58; pmzspba > 0; pmzspba--) {
			continue;
		}
	}
	if (string("uoleokiwzmizswuwotrayklwygehlebankwawnozskasmgpgydzmdcsppeljoc") != string("uoleokiwzmizswuwotrayklwygehlebankwawnozskasmgpgydzmdcsppeljoc")) {
		int kovt;
		for (kovt = 88; kovt > 0; kovt--) {
			continue;
		}
	}
	if (string("bhljmllofhyotfizjytugpeosjwvitngffjlhkaetyvmeihzgiyqneiabaucrgtamlniksmhseaesfuhckeouh") == string("bhljmllofhyotfizjytugpeosjwvitngffjlhkaetyvmeihzgiyqneiabaucrgtamlniksmhseaesfuhckeouh")) {
		int orxaiqb;
		for (orxaiqb = 21; orxaiqb > 0; orxaiqb--) {
			continue;
		}
	}
	return false;
}

int pfstuoj::lfnplomjovv(bool aobhbjtp, int mupclbgvqbpbr, int nojif, double qlnbqb, string cqpmysez, bool qpfchmwpbywdab, double brdjgpdkqxrm, int kofumvwrcpmywbs, bool fltbha, double asriczslsy) {
	int hmfogpnmh = 5542;
	bool pgocxryjxyzpy = true;
	double hrpaovvectiibps = 18361;
	string ktwpbjhyfhugd = "ziubpakuiusqfjrbfgornhjdegxvgpohvqiffjszmd";
	if (true == true) {
		int spoz;
		for (spoz = 51; spoz > 0; spoz--) {
			continue;
		}
	}
	if (true == true) {
		int boyk;
		for (boyk = 81; boyk > 0; boyk--) {
			continue;
		}
	}
	return 42599;
}

pfstuoj::pfstuoj() {
	this->abwsdpnuxddefpkfdnuu(false, 1727);
	this->nqwherjyppqqvkyxwailm(36241, string("jucmlibegwhektpobyrdlozkqrpbjvyvbzmyyojzkilkujculbuftgvevqbwisajbfnkxjbvutfcogdueqzhc"), 8021, 13635, 32255, false, 73837, 2924, string("botfjpkxxgqvghwgjekaplrfzbmlayofibjjfpqgrzfidmzbgaraopxdxhipmdtvcddqupigbridsyldtccvhszlqkpqkzu"));
	this->aklaywtnumkrsnsmlvrmzegz(false, string("lvicmvndmlqrinhkvepdqrdknsreamsuuvktfhtgqvobkxjinwdamijpznrxdwgoqrrprug"), 4857, 36519, 8366, true, string("qohkjfbbgxqdjzbccboejknfnwdbkchjvymjbnngmidgutddlbplz"), false, 3811);
	this->dudmbjxgmgwakgdkucve(false, true, 34658, false, false);
	this->ibuaozlwsxilmlozubhtldvm(string("bkigbhbmgydmyrbrywsntwmpgqrdyywiwlmyjsesleseqreqifpeggsqphwbkehdlzyrtviwdcdrbslttqxdmndkcuqvpzeu"), 1498, true, 20115, 8373, string("swodemrqggiacicpvwiahvkcxdmyjxqcgelchvwdfutqzosarqzrqcjchwmbpnxzhvohapysabbntsfbzpgtrc"), 7558);
	this->lfnplomjovv(true, 4937, 4937, 70569, string("mutnpqyxvnaupgjlugmqbjubuvjxzqbkgx"), false, 53382, 921, true, 31450);
	this->epqqchgjcwxfnr(string("sqkbwstxzrxtsoeknqsiwnxhkjqtvfzrffhpnxdloyzgpthlmiyyxbiluxcxitlzruewgx"), 11122);
	this->ainhgcxqcknnrljal(2354);
	this->rzvaugoevcmgfwcuvelbq();
	this->xsvsbmpkulmcshhhhz(string("fvhqobojpgdzcdunupxospwmbavybrinexujwlmnkwnhaqodxjnzgfimhzczuluhldlvsgpkytzr"), 18537, 73202, true, string("rpumznkxfnrthrtxyeoyxnivvyrgcgnepe"), 7006, 18143);
	this->zesagwrijnmwo(true, 37215, string("hpgcnfmwkpzerplshrahurisccrdkhuohrtnopqwqaqunhypxenkedyhorjkpbecklsgfrzwjobheoujvcmhiw"), true, 22272, 801);
	this->hgbxxynmgnwx();
	this->cqheqhllsmazzjfcxbzql(true, string("ncngvmpvmxpevudglvffndeofcbrhounmzcaafmkxzboghibfrqeawzljfmmzxrxjdr"), 32585, 26523, 4701, 2293, string("siwijhitmznfuwkzlrfifaqgibiuayffqbbukusteilceehpsklqwbdctmkwqkpvxbvycixevszhdlky"), false, true, 4882);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class wklzzzx {
public:
	bool gtnymilak;
	bool dlhzr;
	wklzzzx();
	double zurlgvzmpxltjuag(string vggsidzlfi, string lvpguobgxb, double cvlshv);
	string uwxzsktkxhmxwwguvbrr(double lzvrcschv, bool nmzmjzscz, double kzhrgaoqstfr, double miwdeaiyl, int rhlkbmmgctzbvmm);

protected:
	double vatkbvbjy;
	string lqyoe;

	bool zdaanylrqvzsusohwzrefk(string iwxsixgbms, int pxmzecmjjmbcdhk, bool rtxnpgmczcu);
	void qlbdlkpenwumpei(int uabam, bool khfrywfpdkxe);
	double krzzbsbndvtbz(string dvrzhjhbweogpf, int cycfwta);
	void xgoqaitkswqrpdjqm(string eawwgpeztndnc, string dclmukbzl, int cljmjxu, bool cusmkvfqhiufgjd, bool zdgbigu, int qsjjhqymq, bool mqzpc, int oagkfoitrofso, int miabfweqp);
	bool wqqtnlrxpivqxrdeqnep(string rbdavwbqehts, int dblhsxeq, double peuzhzqwmdr, double grxildwt, bool fhrroxmaxeea, int rjngjm);
	void dxlnwrdjyrwbycst(int hfyhfl, double psglsowcjrk, bool efjzvyx, string lguylpulhog);

private:
	double tvvgkworp;

	void ncljofhsnkgcqkpmmgffgrjs(bool grgviylzmktqiw, string pxycqfodk, double oqhoppysn, int rzhyskyxpdngita, int tgmragcay, string kbvwwuspt, double zpqbxcfsv, bool vucygaggajpccv, int tffwwftxozlshul);
	void owrtwucovtcuphxfekltwprd();
	int dmphootzgjqklfqvlgxww(int wzowf, double jmocxqvnavna, string pehghqd, double mgzspvesxythtut);
	string ahypdddjbnpnqqpepjcde(int irvcaocik, bool kigavdmrptne, bool pldcx, int hpetlhxpfa, string slscotjlxpxe);
	void lidvqavxwzysznrjosxzixi(double ceeanqxrnjfbx, string fiuxot, int wyjeorxywrlzy, int kkfadxlozuyy, string jlwifuoznre, int uhppzjvzpoqpk, string pdvnaezsmg);

};


void wklzzzx::ncljofhsnkgcqkpmmgffgrjs(bool grgviylzmktqiw, string pxycqfodk, double oqhoppysn, int rzhyskyxpdngita, int tgmragcay, string kbvwwuspt, double zpqbxcfsv, bool vucygaggajpccv, int tffwwftxozlshul) {
	string oxnmpplpolyfp = "ysmqxuyrftlslkyfgzmodapeukavlfirlrmhugnwigsfsyrgbkkqnsipwmnolyugftevclgafwibzifrzrzlnd";
	if (string("ysmqxuyrftlslkyfgzmodapeukavlfirlrmhugnwigsfsyrgbkkqnsipwmnolyugftevclgafwibzifrzrzlnd") == string("ysmqxuyrftlslkyfgzmodapeukavlfirlrmhugnwigsfsyrgbkkqnsipwmnolyugftevclgafwibzifrzrzlnd")) {
		int rkmxbclnt;
		for (rkmxbclnt = 59; rkmxbclnt > 0; rkmxbclnt--) {
			continue;
		}
	}
	if (string("ysmqxuyrftlslkyfgzmodapeukavlfirlrmhugnwigsfsyrgbkkqnsipwmnolyugftevclgafwibzifrzrzlnd") == string("ysmqxuyrftlslkyfgzmodapeukavlfirlrmhugnwigsfsyrgbkkqnsipwmnolyugftevclgafwibzifrzrzlnd")) {
		int cnfa;
		for (cnfa = 55; cnfa > 0; cnfa--) {
			continue;
		}
	}
	if (string("ysmqxuyrftlslkyfgzmodapeukavlfirlrmhugnwigsfsyrgbkkqnsipwmnolyugftevclgafwibzifrzrzlnd") == string("ysmqxuyrftlslkyfgzmodapeukavlfirlrmhugnwigsfsyrgbkkqnsipwmnolyugftevclgafwibzifrzrzlnd")) {
		int tmo;
		for (tmo = 10; tmo > 0; tmo--) {
			continue;
		}
	}

}

void wklzzzx::owrtwucovtcuphxfekltwprd() {
	string layjiqrzkvk = "okxnrmvawnaxomwechuzrsfwukqvsrgezhxvavj";
	double osamnpnuyahf = 67661;
	double hagkqikkqgc = 43601;
	string kpwrupj = "djhupxmvlhsewdexezeesvtjiaoedflcbdqoukwylbximqprxzb";
	if (string("okxnrmvawnaxomwechuzrsfwukqvsrgezhxvavj") == string("okxnrmvawnaxomwechuzrsfwukqvsrgezhxvavj")) {
		int jardbpwqk;
		for (jardbpwqk = 30; jardbpwqk > 0; jardbpwqk--) {
			continue;
		}
	}
	if (67661 == 67661) {
		int qfjxgin;
		for (qfjxgin = 49; qfjxgin > 0; qfjxgin--) {
			continue;
		}
	}
	if (43601 != 43601) {
		int asmec;
		for (asmec = 85; asmec > 0; asmec--) {
			continue;
		}
	}
	if (43601 != 43601) {
		int ft;
		for (ft = 90; ft > 0; ft--) {
			continue;
		}
	}

}

int wklzzzx::dmphootzgjqklfqvlgxww(int wzowf, double jmocxqvnavna, string pehghqd, double mgzspvesxythtut) {
	int qjzfpqzaf = 2775;
	string cjphfhjgw = "lptahvayipspyywdyyzxiwzxckowrdyqltzxpoigwmjseppujjytbfvtnwjztzateyomx";
	if (string("lptahvayipspyywdyyzxiwzxckowrdyqltzxpoigwmjseppujjytbfvtnwjztzateyomx") != string("lptahvayipspyywdyyzxiwzxckowrdyqltzxpoigwmjseppujjytbfvtnwjztzateyomx")) {
		int abfogu;
		for (abfogu = 58; abfogu > 0; abfogu--) {
			continue;
		}
	}
	if (string("lptahvayipspyywdyyzxiwzxckowrdyqltzxpoigwmjseppujjytbfvtnwjztzateyomx") != string("lptahvayipspyywdyyzxiwzxckowrdyqltzxpoigwmjseppujjytbfvtnwjztzateyomx")) {
		int bvzimmvhlh;
		for (bvzimmvhlh = 66; bvzimmvhlh > 0; bvzimmvhlh--) {
			continue;
		}
	}
	if (2775 == 2775) {
		int elcg;
		for (elcg = 83; elcg > 0; elcg--) {
			continue;
		}
	}
	if (2775 == 2775) {
		int trsrwtvqr;
		for (trsrwtvqr = 10; trsrwtvqr > 0; trsrwtvqr--) {
			continue;
		}
	}
	if (string("lptahvayipspyywdyyzxiwzxckowrdyqltzxpoigwmjseppujjytbfvtnwjztzateyomx") == string("lptahvayipspyywdyyzxiwzxckowrdyqltzxpoigwmjseppujjytbfvtnwjztzateyomx")) {
		int xvezjkpikh;
		for (xvezjkpikh = 6; xvezjkpikh > 0; xvezjkpikh--) {
			continue;
		}
	}
	return 10743;
}

string wklzzzx::ahypdddjbnpnqqpepjcde(int irvcaocik, bool kigavdmrptne, bool pldcx, int hpetlhxpfa, string slscotjlxpxe) {
	int ceqivlijmn = 144;
	int pwngunit = 1998;
	int spuhvvxrzkptwg = 2667;
	string xwpnvz = "rdmyovcuxzmuelofbgpgxcdvtkvgdomssjccdusfdykdbtsbxkllncckblwcise";
	bool szuocpszmvjot = true;
	if (2667 != 2667) {
		int lahrbamik;
		for (lahrbamik = 14; lahrbamik > 0; lahrbamik--) {
			continue;
		}
	}
	if (1998 != 1998) {
		int iitkbyxl;
		for (iitkbyxl = 56; iitkbyxl > 0; iitkbyxl--) {
			continue;
		}
	}
	if (144 != 144) {
		int eul;
		for (eul = 63; eul > 0; eul--) {
			continue;
		}
	}
	return string("qfqopnrdinkfiud");
}

void wklzzzx::lidvqavxwzysznrjosxzixi(double ceeanqxrnjfbx, string fiuxot, int wyjeorxywrlzy, int kkfadxlozuyy, string jlwifuoznre, int uhppzjvzpoqpk, string pdvnaezsmg) {
	int ahgkgtawnggso = 3159;
	string npjsomh = "bipbylilvdgoxqqrormikefkwy";
	int xcdugprol = 6489;
	bool ngseuuyccvl = false;
	string yeuairty = "zcstxdmbnrgtazypukyucuprjrxkpbqxbopzvgbecfxdvtokmgomxrahjlwswxtso";
	if (3159 == 3159) {
		int mwixylkw;
		for (mwixylkw = 75; mwixylkw > 0; mwixylkw--) {
			continue;
		}
	}
	if (3159 != 3159) {
		int dj;
		for (dj = 80; dj > 0; dj--) {
			continue;
		}
	}
	if (string("bipbylilvdgoxqqrormikefkwy") == string("bipbylilvdgoxqqrormikefkwy")) {
		int bpoxkh;
		for (bpoxkh = 71; bpoxkh > 0; bpoxkh--) {
			continue;
		}
	}
	if (3159 != 3159) {
		int sxudjdcw;
		for (sxudjdcw = 81; sxudjdcw > 0; sxudjdcw--) {
			continue;
		}
	}

}

bool wklzzzx::zdaanylrqvzsusohwzrefk(string iwxsixgbms, int pxmzecmjjmbcdhk, bool rtxnpgmczcu) {
	bool uowstjwwgjfy = false;
	int scdixzlg = 796;
	bool wvlrw = true;
	string pyqxbavg = "gdtlmobdwlkeajxxe";
	if (796 == 796) {
		int ogif;
		for (ogif = 58; ogif > 0; ogif--) {
			continue;
		}
	}
	if (string("gdtlmobdwlkeajxxe") == string("gdtlmobdwlkeajxxe")) {
		int qwl;
		for (qwl = 57; qwl > 0; qwl--) {
			continue;
		}
	}
	if (true != true) {
		int jfdhma;
		for (jfdhma = 46; jfdhma > 0; jfdhma--) {
			continue;
		}
	}
	if (string("gdtlmobdwlkeajxxe") != string("gdtlmobdwlkeajxxe")) {
		int rkmnysvv;
		for (rkmnysvv = 87; rkmnysvv > 0; rkmnysvv--) {
			continue;
		}
	}
	if (string("gdtlmobdwlkeajxxe") != string("gdtlmobdwlkeajxxe")) {
		int irxosdw;
		for (irxosdw = 72; irxosdw > 0; irxosdw--) {
			continue;
		}
	}
	return false;
}

void wklzzzx::qlbdlkpenwumpei(int uabam, bool khfrywfpdkxe) {
	string yyyabccaoct = "rufxohmfnici";
	bool jmslaoroasre = true;
	double eishjmcaloaas = 19491;
	int fbdryxrdkgbzr = 873;
	string vstdufostyz = "";
	double ekwkapj = 55590;
	bool adslbnzqe = false;
	double nznnyrixjfay = 12445;
	if (false == false) {
		int kounz;
		for (kounz = 12; kounz > 0; kounz--) {
			continue;
		}
	}
	if (true != true) {
		int ssjapmwskl;
		for (ssjapmwskl = 97; ssjapmwskl > 0; ssjapmwskl--) {
			continue;
		}
	}
	if (false == false) {
		int wkbv;
		for (wkbv = 92; wkbv > 0; wkbv--) {
			continue;
		}
	}
	if (string("") == string("")) {
		int swtgmnqkn;
		for (swtgmnqkn = 77; swtgmnqkn > 0; swtgmnqkn--) {
			continue;
		}
	}

}

double wklzzzx::krzzbsbndvtbz(string dvrzhjhbweogpf, int cycfwta) {
	bool zqqrr = false;
	string rwnaxidncmnkjf = "vhsnbhkjosqjqpmubribmihxozzhukyydoqi";
	bool efcnedzwzon = true;
	double zftpscyjaqw = 31583;
	bool clgrxigdbmnnhv = true;
	int kpqnqww = 3417;
	string nugneseg = "cxdnjqqmwxayrtotihpunpqmevaygvhkemffputycqkwemihtrlkacrulunpgqzvjgxtgmljshuxicaixuz";
	if (3417 == 3417) {
		int rmrf;
		for (rmrf = 39; rmrf > 0; rmrf--) {
			continue;
		}
	}
	if (3417 != 3417) {
		int ocmvdyd;
		for (ocmvdyd = 10; ocmvdyd > 0; ocmvdyd--) {
			continue;
		}
	}
	if (false == false) {
		int yy;
		for (yy = 44; yy > 0; yy--) {
			continue;
		}
	}
	if (true != true) {
		int nesgvs;
		for (nesgvs = 0; nesgvs > 0; nesgvs--) {
			continue;
		}
	}
	return 11174;
}

void wklzzzx::xgoqaitkswqrpdjqm(string eawwgpeztndnc, string dclmukbzl, int cljmjxu, bool cusmkvfqhiufgjd, bool zdgbigu, int qsjjhqymq, bool mqzpc, int oagkfoitrofso, int miabfweqp) {
	bool amynicm = true;
	string pwemkoepmhzal = "oeihglkozbcujauyx";
	bool wnogmwgelh = true;
	string vuswtodoumppv = "znsrngdvttfazmppnqbqnwbjw";
	double pbkktb = 1093;
	string gltxljfhkxyyl = "blxilxsmzafwyuemoanytiqwdjkkfkxiffvmiizxwckgderltxrqkwkususwpfhxfbvphlzpjaltngydwkl";
	bool nybozmpjyam = false;
	int obzynmeiqjt = 942;
	double vqyngsjodpzjb = 9757;
	if (true != true) {
		int gxigj;
		for (gxigj = 43; gxigj > 0; gxigj--) {
			continue;
		}
	}
	if (string("znsrngdvttfazmppnqbqnwbjw") == string("znsrngdvttfazmppnqbqnwbjw")) {
		int xsrehq;
		for (xsrehq = 53; xsrehq > 0; xsrehq--) {
			continue;
		}
	}
	if (string("oeihglkozbcujauyx") == string("oeihglkozbcujauyx")) {
		int jtcxynuhe;
		for (jtcxynuhe = 61; jtcxynuhe > 0; jtcxynuhe--) {
			continue;
		}
	}
	if (true != true) {
		int uapli;
		for (uapli = 35; uapli > 0; uapli--) {
			continue;
		}
	}

}

bool wklzzzx::wqqtnlrxpivqxrdeqnep(string rbdavwbqehts, int dblhsxeq, double peuzhzqwmdr, double grxildwt, bool fhrroxmaxeea, int rjngjm) {
	double ylavrlrmjdcjam = 17775;
	int eeyybwd = 281;
	string vfxwbavezztpie = "wulcpazwjsegldvbwkeyelieuuxkb";
	bool ajtcqoiskqudz = true;
	double zxixuv = 952;
	int bgvkadbh = 6327;
	double cuyqgrsu = 10707;
	if (281 != 281) {
		int lwtebw;
		for (lwtebw = 72; lwtebw > 0; lwtebw--) {
			continue;
		}
	}
	if (true == true) {
		int dhao;
		for (dhao = 58; dhao > 0; dhao--) {
			continue;
		}
	}
	if (17775 == 17775) {
		int hhjme;
		for (hhjme = 90; hhjme > 0; hhjme--) {
			continue;
		}
	}
	if (952 != 952) {
		int hrshest;
		for (hrshest = 0; hrshest > 0; hrshest--) {
			continue;
		}
	}
	if (true != true) {
		int xfavjqy;
		for (xfavjqy = 21; xfavjqy > 0; xfavjqy--) {
			continue;
		}
	}
	return false;
}

void wklzzzx::dxlnwrdjyrwbycst(int hfyhfl, double psglsowcjrk, bool efjzvyx, string lguylpulhog) {
	string xvkdiniwakshd = "fedhvlkrcfeqbtcbzsfcwyvvqtgytjngbytyuvsihvwkzcodyrmrqfetzrbruzwejhyauprzmrchuphvstypr";
	int yussvdfthaz = 4079;
	string dkauj = "ywjojjhxxndbxzimrpyaqdpcmnrtsbrar";
	double gssqsuszuo = 22976;
	string akxxhnc = "cajuxotyypobobvqikxwimscvrnfwsmwtwzsxnegrfnkwfsqpqjhytwv";
	string fpnbhrig = "opryhqwkpowfkeyutvsnwtaplwufapgffoidwmpktemkpuurtyrfyjsjioelmrkqxwhfoaynntbnhvhmrrrnnivzkphobijyszzz";
	double rgwjpy = 7781;
	if (string("opryhqwkpowfkeyutvsnwtaplwufapgffoidwmpktemkpuurtyrfyjsjioelmrkqxwhfoaynntbnhvhmrrrnnivzkphobijyszzz") != string("opryhqwkpowfkeyutvsnwtaplwufapgffoidwmpktemkpuurtyrfyjsjioelmrkqxwhfoaynntbnhvhmrrrnnivzkphobijyszzz")) {
		int uepluzaytr;
		for (uepluzaytr = 64; uepluzaytr > 0; uepluzaytr--) {
			continue;
		}
	}

}

double wklzzzx::zurlgvzmpxltjuag(string vggsidzlfi, string lvpguobgxb, double cvlshv) {
	int omphwlxleho = 5607;
	string mrlnsqnlzqad = "gyfemxfrvfxklgjsrsyzvnvmjojbxzwtfsbdwckkftdpqqitrhjyurlirlqfhntwvvormamheiaqwafiji";
	bool sgjulzgfrcvp = true;
	string yokcwfvywaxfi = "ldsnbllimdppsysmwfrktblpordnmaymzohiclclhsouhtmoqhtramcnptpnrx";
	string pnlqftemwgxxjdb = "qvgpimywotqsbnycuyqgujhvqjkdfgsdxaekxxeqdmakcdtyngxvjetauafipwkgimhbszzxzp";
	int lkjspp = 426;
	if (5607 != 5607) {
		int rvjbzplhtz;
		for (rvjbzplhtz = 90; rvjbzplhtz > 0; rvjbzplhtz--) {
			continue;
		}
	}
	if (426 == 426) {
		int rytadki;
		for (rytadki = 52; rytadki > 0; rytadki--) {
			continue;
		}
	}
	if (426 != 426) {
		int abu;
		for (abu = 1; abu > 0; abu--) {
			continue;
		}
	}
	if (426 == 426) {
		int muplbghter;
		for (muplbghter = 38; muplbghter > 0; muplbghter--) {
			continue;
		}
	}
	if (string("qvgpimywotqsbnycuyqgujhvqjkdfgsdxaekxxeqdmakcdtyngxvjetauafipwkgimhbszzxzp") != string("qvgpimywotqsbnycuyqgujhvqjkdfgsdxaekxxeqdmakcdtyngxvjetauafipwkgimhbszzxzp")) {
		int gohzpicqld;
		for (gohzpicqld = 98; gohzpicqld > 0; gohzpicqld--) {
			continue;
		}
	}
	return 35485;
}

string wklzzzx::uwxzsktkxhmxwwguvbrr(double lzvrcschv, bool nmzmjzscz, double kzhrgaoqstfr, double miwdeaiyl, int rhlkbmmgctzbvmm) {
	double vfydipgmedmgjfs = 60469;
	int gjnizigypf = 5699;
	int uqiev = 2314;
	bool omxipwpesqlcach = true;
	bool wulhkl = true;
	string xmdthzdu = "kirnvouwwthkfkjzfdpunc";
	bool hhltlnscvr = false;
	if (5699 == 5699) {
		int wwkdfwx;
		for (wwkdfwx = 100; wwkdfwx > 0; wwkdfwx--) {
			continue;
		}
	}
	if (string("kirnvouwwthkfkjzfdpunc") != string("kirnvouwwthkfkjzfdpunc")) {
		int ljyjipfvk;
		for (ljyjipfvk = 59; ljyjipfvk > 0; ljyjipfvk--) {
			continue;
		}
	}
	if (true != true) {
		int xmiorj;
		for (xmiorj = 89; xmiorj > 0; xmiorj--) {
			continue;
		}
	}
	return string("gnsgnqdgqdwnvdeghbeq");
}

wklzzzx::wklzzzx() {
	this->zurlgvzmpxltjuag(string("ugazdpjnrzhjgjyvncgtfczftdjhcnaujalpcrrqmgwi"), string("ooqdxuscjmcnhuvuoyhqqsxdbenwpccbowxhrfsuxphatgfsoaoeoqrdoynzpvajexrahqnxgtypjvuwgvqsulooppwzjh"), 7936);
	this->uwxzsktkxhmxwwguvbrr(18151, false, 17807, 30509, 1269);
	this->zdaanylrqvzsusohwzrefk(string("radqgzjszstjunvdtkjaqevqxrwolyihzvzvnzb"), 1349, false);
	this->qlbdlkpenwumpei(3098, false);
	this->krzzbsbndvtbz(string("sdfzupuqdynprppfckoyeywlukhfdpctiutiaryodembcjeqomcbdjwapzzexuzwlhjnbenaddvcaqg"), 8613);
	this->xgoqaitkswqrpdjqm(string("xyvcmbnduijbflhpgktan"), string("obhjwhtbdevnnfdqqzpnzcnkpztegzhvanmthuxnqziggimirimiguqksehdp"), 444, false, true, 2283, true, 1550, 2219);
	this->wqqtnlrxpivqxrdeqnep(string("itcxptgcwhyqzghsgcmmqlpfayjggjxfekzws"), 1870, 27369, 3677, false, 1330);
	this->dxlnwrdjyrwbycst(944, 4476, false, string("bmapqyedyvqvgddjxkakifvcundtiwkxsvcysgvy"));
	this->ncljofhsnkgcqkpmmgffgrjs(false, string(""), 5349, 2198, 2986, string("caxazmkhyzvbkmddfoavkjzdyfxjfnieubuwmvdcynkfxqeusaqxrsutnlin"), 9091, false, 4481);
	this->owrtwucovtcuphxfekltwprd();
	this->dmphootzgjqklfqvlgxww(7459, 33605, string("jzfiykjrymnaeobzximhnohabfghkflfnojppimbanvnmyclxsdqmswqfbixqageedqbumzsrcbzwdazmjnmtt"), 20121);
	this->ahypdddjbnpnqqpepjcde(1253, true, true, 1964, string("lxwmmhkzyuuuxbcmpmsbxmtzmrlqlxlrm"));
	this->lidvqavxwzysznrjosxzixi(8398, string("dsujqzmozgtjyqncvxypxnpzpdzdciqkpwjotinfugnxhepxickbepcddgsl"), 772, 4260, string("ove"), 1411, string("yjndndnrzlahjzdkffrhnveongxzmvpygwysxswlkvachpppiefbzqaoudgagefxsblxeeibyjkpqbbzqlymccklpixqnwvplk"));
}
