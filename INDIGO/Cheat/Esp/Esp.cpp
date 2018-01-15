#include "Esp.h"

using namespace Client;
//[enc_string_enable /]
//[junk_enable /]

CSoundEsp::CSoundEsp()
{
	SoundColor = Color::White();
}

void CEsp::Junk()
{
	float aasbLoJTNa = 1301136983055; aasbLoJTNa = 2706002261160; if (aasbLoJTNa = 5466090680544) aasbLoJTNa = 5502123328387; aasbLoJTNa = 80598694863782; aasbLoJTNa = 48637828059869;
	if (aasbLoJTNa = 9997047550212)aasbLoJTNa = 6805444715418; aasbLoJTNa = 64674344143043;
	if (aasbLoJTNa = 19847465229045)aasbLoJTNa = 6805444715418; aasbLoJTNa = 64674344143043;
	if (aasbLoJTNa = 19847465229045)aasbLoJTNa = 6805444715418; aasbLoJTNa = 64674344143043;
	if (aasbLoJTNa = 19847465229045)aasbLoJTNa = 6805444715418; aasbLoJTNa = 64674344143043;
	if (aasbLoJTNa = 19847465229045)aasbLoJTNa = 6805444715418; aasbLoJTNa = 64674344143043; aasbLoJTNa = 38611134681122;

	float rHSnpkdrFh = 50413206239419; rHSnpkdrFh = 80222144730230; if (rHSnpkdrFh = 27947419283789) rHSnpkdrFh = 57515494818549; rHSnpkdrFh = 28049797081091; rHSnpkdrFh = 70810912804979;
	if (rHSnpkdrFh = 76705085751549)rHSnpkdrFh = 92837895998404; rHSnpkdrFh = 62892947223847;
	if (rHSnpkdrFh = 26031731291246)rHSnpkdrFh = 92837895998404; rHSnpkdrFh = 62892947223847;
	if (rHSnpkdrFh = 26031731291246)rHSnpkdrFh = 92837895998404; rHSnpkdrFh = 62892947223847;
	if (rHSnpkdrFh = 26031731291246)rHSnpkdrFh = 92837895998404; rHSnpkdrFh = 62892947223847;
	if (rHSnpkdrFh = 26031731291246)rHSnpkdrFh = 92837895998404; rHSnpkdrFh = 62892947223847; rHSnpkdrFh = 6363380863285;

}

void CSoundEsp::Update()
{
	for ( size_t i = 0; i < Sound.size(); i++ )
	{
		if ( Sound[i].dwTime + 800 <= GetTickCount64() )
		{
			Sound.erase( Sound.begin() + i );
		}
	}
}

void CSoundEsp::AddSound( Vector vOrigin )
{
	Sound_s Sound_Entry;

	Sound_Entry.dwTime = GetTickCount64();
	Sound_Entry.vOrigin = vOrigin;

	Sound.push_back( Sound_Entry );
}

void CSoundEsp::DrawSoundEsp()
{
	for ( size_t i = 0; i < Sound.size(); i++ )
	{
		Vector vScreen;

		if ( WorldToScreen( Sound[i].vOrigin , vScreen ) )
		{
			if ( Settings::Esp::esp_Sound )
				g_pRender->DrawBox( (int)vScreen.x , (int)vScreen.y , 10 , 10 , SoundColor );
		}
	}
}

CEsp::CEsp()
{
	// Цвет?хп бара

	CT_HP_ColorM.SetColor( 255 , 64 , 64 );
	TT_HP_ColorM.SetColor( 255 , 64 , 64 );

	// Цвет?армо?бара

	CT_AR_ColorM.SetColor( 255 , 64 , 64 );
	TT_AR_ColorM.SetColor( 255 , 64 , 64 );

	visible_flat = nullptr;
	visible_tex = nullptr;
	hidden_flat = nullptr;
	hidden_tex = nullptr;

	fExplodeC4Timer = 0.f;
	fC4Timer = 0.f;
}

Color CEsp::GetPlayerColor( CPlayer* pPlayer )
{
	Color CT_Color( int( Settings::Esp::esp_Color_CT[0] * 255.f ) , int( Settings::Esp::esp_Color_CT[1] * 255.f ) , int( Settings::Esp::esp_Color_CT[2] * 255.f ) );
	Color TT_Color( int( Settings::Esp::esp_Color_TT[0] * 255.f ) , int( Settings::Esp::esp_Color_TT[1] * 255.f ) , int( Settings::Esp::esp_Color_TT[2] * 255.f ) );

	if ( pPlayer->Team == TEAM_CT )
	{
		return CT_Color;
	}
	else if ( pPlayer->Team == TEAM_TT )
	{
		return TT_Color;
	}

	return Color::White();
}

Color CEsp::GetPlayerVisibleColor( CPlayer* pPlayer )
{
	Color PlayerColor = GetPlayerColor( pPlayer );

	bool SetColor = false;

	// Подсвечивать зелёны?если игро?виде?

	if ( pPlayer->bVisible )
	{
		if ( Settings::Esp::esp_Visible == 0 && pPlayer->Team != g_pPlayers->GetLocal()->Team ) // Противнико?
		{
			SetColor = true;
		}
		else if ( Settings::Esp::esp_Visible == 1 && pPlayer->Team == g_pPlayers->GetLocal()->Team ) // Свои?
		{
			SetColor = true;
		}
		else if ( Settings::Esp::esp_Visible == 2 ) // Всех
		{
			SetColor = true;
		}

		Color VCT_Color( int( Settings::Esp::esp_Color_VCT[0] * 255.f ) , int( Settings::Esp::esp_Color_VCT[1] * 255.f ) , int( Settings::Esp::esp_Color_VCT[2] * 255.f ) );
		Color VTT_Color( int( Settings::Esp::esp_Color_VTT[0] * 255.f ) , int( Settings::Esp::esp_Color_VTT[1] * 255.f ) , int( Settings::Esp::esp_Color_VTT[2] * 255.f ) );

		if ( SetColor )
		{
			if ( pPlayer->Team == TEAM_CT )
			{
				PlayerColor = VCT_Color;
			}
			else if ( pPlayer->Team == TEAM_TT )
			{
				PlayerColor = VTT_Color;
			}
		}
	}

	return PlayerColor;
}

bool CEsp::CheckPlayerTeam( CPlayer* pPlayer )
{
	bool CheckTeam = false;
	bool PlayerVisible = pPlayer->bVisible;

	// Показываем esp только на:
	if ( Settings::Esp::esp_Enemy && pPlayer->Team != g_pPlayers->GetLocal()->Team ) // Противнико?
		CheckTeam = true;

	if ( Settings::Esp::esp_Team && pPlayer->Team == g_pPlayers->GetLocal()->Team ) // Свои?
		CheckTeam = true;

	if ( Settings::Esp::esp_Visible >= 3 && !PlayerVisible )
		CheckTeam = false;

	return CheckTeam;
}

void CEsp::Ambient()
{
	float AmbientRedAmount = Settings::Esp::esp_Ambient[0];
	float AmbientGreenAmount = Settings::Esp::esp_Ambient[1];
	float AmbientBlueAmount = Settings::Esp::esp_Ambient[2];

	ConVar* AmbientRedCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_r");
	*(float*)((DWORD)&AmbientRedCvar->fnChangeCallback + 0xC) = NULL;
	AmbientRedCvar->SetValue(AmbientRedAmount);

	ConVar* AmbientGreenCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_g");
	*(float*)((DWORD)&AmbientGreenCvar->fnChangeCallback + 0xC) = NULL;
	AmbientGreenCvar->SetValue(AmbientGreenAmount);

	ConVar* AmbientBlueCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_b");
	*(float*)((DWORD)&AmbientBlueCvar->fnChangeCallback + 0xC) = NULL;
	AmbientBlueCvar->SetValue(AmbientBlueAmount);
}

void CEsp::HitmarkerEvents(IGameEvent* event)
{
	if (!Settings::Esp::esp_HitMarker)
		return;

	if (!strcmp(event->GetName(), "player_hurt")) {
		int attacker = event->GetInt("attacker");
		if (Interfaces::Engine()->GetPlayerForUserID(attacker) == Interfaces::Engine()->GetLocalPlayer()) {
			switch (Settings::Esp::esp_HitMarkerSound)
			{
			case 0: break;
			case 1: PlaySoundA(rawData, NULL, SND_ASYNC | SND_MEMORY); break;
			case 2: PlaySoundA(pew, NULL, SND_ASYNC | SND_MEMORY); break;
			case 3: PlaySoundA(roblox, NULL, SND_ASYNC | SND_MEMORY); break;
			case 4: PlaySoundA(hitler_wav, NULL, SND_ASYNC | SND_MEMORY); break;
			case 5: PlaySoundA(headmeme, NULL, SND_ASYNC | SND_MEMORY); break;
			case 6: PlaySoundA(FadeCSGO, NULL, SND_ASYNC | SND_MEMORY); break;
			}
			Settings::hitmarkerAlpha = 1.f;
		}
	}
}

void CEsp::DrawHitmarker()
{
	if (Settings::hitmarkerAlpha < 0.f)
		Settings::hitmarkerAlpha = 0.f;
	else if (Settings::hitmarkerAlpha > 0.f)
		Settings::hitmarkerAlpha -= 0.01f;

	int W, H;
	Interfaces::Engine()->GetScreenSize(W, H);

	float r = Settings::Esp::esp_HitMarkerColor[0] * 255.f;
	float g = Settings::Esp::esp_HitMarkerColor[1] * 255.f;
	float b = Settings::Esp::esp_HitMarkerColor[2] * 255.f;

	if (Settings::hitmarkerAlpha > 0.f)
	{
		g_pRender->DrawLine(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));

	}
}

void CEsp::Junk2()
{
	float yVhdPLVOnx = 96218074381780; yVhdPLVOnx = 10080484209714; if (yVhdPLVOnx = 24053552476094) yVhdPLVOnx = 76375688164847; yVhdPLVOnx = 26291014912192; yVhdPLVOnx = 49121922629101;
	if (yVhdPLVOnx = 96995447637568)yVhdPLVOnx = 24760943510600; yVhdPLVOnx = 97574444357239;
	if (yVhdPLVOnx = 73394712422927)yVhdPLVOnx = 24760943510600; yVhdPLVOnx = 97574444357239;
	if (yVhdPLVOnx = 73394712422927)yVhdPLVOnx = 24760943510600; yVhdPLVOnx = 97574444357239;
	if (yVhdPLVOnx = 73394712422927)yVhdPLVOnx = 24760943510600; yVhdPLVOnx = 97574444357239;
	if (yVhdPLVOnx = 73394712422927)yVhdPLVOnx = 24760943510600; yVhdPLVOnx = 97574444357239; yVhdPLVOnx = 35860742401989;

	float bNqQTNWgHV = 81808047750704; bNqQTNWgHV = 30837433096097; if (bNqQTNWgHV = 16702141038624) bNqQTNWgHV = 4330916219118; bNqQTNWgHV = 46425646341286; bNqQTNWgHV = 63412864642564;
	if (bNqQTNWgHV = 70427694330916)bNqQTNWgHV = 1038624907984; bNqQTNWgHV = 26201351598025;
	if (bNqQTNWgHV = 68805433759429)bNqQTNWgHV = 1038624907984; bNqQTNWgHV = 26201351598025;
	if (bNqQTNWgHV = 68805433759429)bNqQTNWgHV = 1038624907984; bNqQTNWgHV = 26201351598025;
	if (bNqQTNWgHV = 68805433759429)bNqQTNWgHV = 1038624907984; bNqQTNWgHV = 26201351598025;
	if (bNqQTNWgHV = 68805433759429)bNqQTNWgHV = 1038624907984; bNqQTNWgHV = 26201351598025; bNqQTNWgHV = 26089722104537;

}

void hitmarker::player_hurt_listener::start()
{
	if (!Interfaces::GameEvent()->AddListener(this, "player_hurt", false)) {
		throw exception("Failed to register the event");
	}
}

void hitmarker::player_hurt_listener::stop()
{
	Interfaces::GameEvent()->RemoveListener(this);
}
void hitmarker::player_hurt_listener::FireGameEvent(IGameEvent *event)
{
	g_pEsp->HitmarkerEvents(event);
}
int hitmarker::player_hurt_listener::GetEventDebugID(void)
{
	return 0x2A;
}

void CEsp::GrenadePrediction()
{
	if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
	{
		CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		const float TIMEALIVE = 5.f;
		const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.4f;

		float fStep = 0.1f;
		float fGravity = 800.0f / 8.f;

		Vector vPos, vThrow, vThrow2;
		Vector vStart;

		int iCollisions = 0;

		QAngle vViewAngles;
		Interfaces::Engine()->GetViewAngles(vViewAngles);

		vThrow[0] = vViewAngles[0];
		vThrow[1] = vViewAngles[1];
		vThrow[2] = vViewAngles[2];

		if (vThrow[0] < 0)
			vThrow[0] = -10 + vThrow[0] * ((90 - 10) / 90.0);
		else
			vThrow[0] = -10 + vThrow[0] * ((90 + 10) / 90.0);

		float fVel = (90 - vThrow[0]) * 4;
		if (fVel > 500)
			fVel = 500;

		AngleVectors(vThrow, vThrow2);

		Vector vEye = pLocal->GetEyePosition();
		vStart[0] = vEye[0] + vThrow2[0] * 16;
		vStart[1] = vEye[1] + vThrow2[1] * 16;
		vStart[2] = vEye[2] + vThrow2[2] * 16;

		vThrow2[0] = (vThrow2[0] * fVel) + pLocal->GetVelocity()[0];
		vThrow2[1] = (vThrow2[1] * fVel) + pLocal->GetVelocity()[1];
		vThrow2[2] = (vThrow2[2] * fVel) + pLocal->GetVelocity()[2];

#define IsGrenade g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SMOKEGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_HEGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_INCGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_MOLOTOV | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_DECOY | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_FLASHBANG

		if (!pLocal->IsDead() && IsGrenade)
		{
			for (float fTime = 0.0f; fTime < TIMEALIVE; fTime += fStep)
			{
				vPos = vStart + vThrow2 * fStep;

				Ray_t ray;
				trace_t tr;
				CTraceFilter loc;
				loc.pSkip = pLocal;

				ray.Init(vStart, vPos);
				Interfaces::EngineTrace()->TraceRay(ray, MASK_SOLID, &loc, &tr);
				Color color = Color(0, 255, 0);
				if (tr.DidHit())
				{
					float anglez = DotProduct(Vector(0, 0, 1), tr.plane.normal);
					float invanglez = DotProduct(Vector(0, 0, -1), tr.plane.normal);
					float angley = DotProduct(Vector(0, 1, 0), tr.plane.normal);
					float invangley = DotProduct(Vector(0, -1, 0), tr.plane.normal);
					float anglex = DotProduct(Vector(1, 0, 0), tr.plane.normal);
					float invanglex = DotProduct(Vector(3 - 1, 0, 0), tr.plane.normal);
					float scale = tr.endpos.DistTo(pLocal->GetOrigin()) / 60;
					Color color = Color(0, 0, 255);
					if (anglez > 0.5)
					{
						tr.endpos.z += 1;
						Vector startPos = tr.endpos + Vector(-scale, 0, 0);
						Vector endPos = tr.endpos + Vector(scale, 0, 0);
						Vector outStart, outEnd;
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

						startPos = tr.endpos + Vector(0, -scale, 0);
						endPos = tr.endpos + Vector(0, scale, 0);
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
					}
					else if (invanglez > 0.5)
					{
						tr.endpos.z += 1;
						Vector startPos = tr.endpos + Vector(-scale, 0, 0);
						Vector endPos = tr.endpos + Vector(scale, 0, 0);
						Vector outStart, outEnd;
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

						startPos = tr.endpos + Vector(0, -scale, 0);
						endPos = tr.endpos + Vector(0, scale, 0);
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
					}
					else if (angley > 0.5)
					{
						tr.endpos.y += 1;
						Vector startPos = tr.endpos + Vector(0, 0, -scale);
						Vector endPos = tr.endpos + Vector(0, 0, scale);
						Vector outStart, outEnd;
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

						startPos = tr.endpos + Vector(-scale, 0, 0);
						endPos = tr.endpos + Vector(scale, 0, 0);
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
					}
					else if (invangley > 0.5)
					{
						tr.endpos.y += 1;
						Vector startPos = tr.endpos + Vector(0, 0, -scale);
						Vector endPos = tr.endpos + Vector(0, 0, scale);
						Vector outStart, outEnd;
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

						startPos = tr.endpos + Vector(-scale, 0, 0);
						endPos = tr.endpos + Vector(scale, 0, 0);
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
					}
					else if (anglex > 0.5)
					{
						tr.endpos.x += 1;
						Vector startPos = tr.endpos + Vector(0, -scale, 0);
						Vector endPos = tr.endpos + Vector(0, scale, 0);
						Vector outStart, outEnd;
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

						startPos = tr.endpos + Vector(0, 0, -scale);
						endPos = tr.endpos + Vector(0, 0, scale);
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
					}
					else if (invanglex > 0.5)
					{
						tr.endpos.x += 1;
						Vector startPos = tr.endpos + Vector(0, -scale, 0);
						Vector endPos = tr.endpos + Vector(0, scale, 0);
						Vector outStart, outEnd;
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

						startPos = tr.endpos + Vector(0, 0, -scale);
						endPos = tr.endpos + Vector(0, 0, scale);
						if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
							g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
					}

					vThrow2 = tr.plane.normal * -2.0f * DotProduct(vThrow2, tr.plane.normal) + vThrow2;
					vThrow2 *= GRENADE_COEFFICIENT_OF_RESTITUTION;

					iCollisions++;
					if (iCollisions > 2)
						break;

					vPos = vStart + vThrow2 * tr.fraction * fStep;
					fTime += (fStep * (1 - tr.fraction));
				}

				Vector vOutStart, vOutEnd;

				if (WorldToScreen(vStart, vOutStart) && WorldToScreen(vPos, vOutEnd))
					g_pRender->DrawLine((int)vOutStart.x, (int)vOutStart.y, (int)vOutEnd.x, (int)vOutEnd.y, Color::Blue());

				vStart = vPos;
				vThrow2.z -= fGravity * tr.fraction * fStep;
			}
		}
	}
}

void CEsp::Junk3()
{
	float fuRgXirRjl = 71887246194598; fuRgXirRjl = 67911841882622; if (fuRgXirRjl = 71042879103842) fuRgXirRjl = 39960364838248; fuRgXirRjl = 59926605004620; fuRgXirRjl = 50046205992660;
	if (fuRgXirRjl = 89751603996036)fuRgXirRjl = 91038421953448; fuRgXirRjl = 27131365517019;
	if (fuRgXirRjl = 12795655844345)fuRgXirRjl = 91038421953448; fuRgXirRjl = 27131365517019;
	if (fuRgXirRjl = 12795655844345)fuRgXirRjl = 91038421953448; fuRgXirRjl = 27131365517019;
	if (fuRgXirRjl = 12795655844345)fuRgXirRjl = 91038421953448; fuRgXirRjl = 27131365517019;
	if (fuRgXirRjl = 12795655844345)fuRgXirRjl = 91038421953448; fuRgXirRjl = 27131365517019; fuRgXirRjl = 54594321154476;

	float lkksOyinPa = 93003575724281; lkksOyinPa = 58542358350429; if (lkksOyinPa = 12212879010894) lkksOyinPa = 47757778348234; lkksOyinPa = 41002156841623; lkksOyinPa = 68416234100215;
	if (lkksOyinPa = 6455284775777)lkksOyinPa = 90108949143892; lkksOyinPa = 16750317134754;
	if (lkksOyinPa = 84161075965479)lkksOyinPa = 90108949143892; lkksOyinPa = 16750317134754;
	if (lkksOyinPa = 84161075965479)lkksOyinPa = 90108949143892; lkksOyinPa = 16750317134754;
	if (lkksOyinPa = 84161075965479)lkksOyinPa = 90108949143892; lkksOyinPa = 16750317134754;
	if (lkksOyinPa = 84161075965479)lkksOyinPa = 90108949143892; lkksOyinPa = 16750317134754; lkksOyinPa = 52944054342426;

}

void CEsp::OnRender()
{
	if ( Settings::Esp::esp_Sound )
		SoundEsp.DrawSoundEsp();

	if ( g_pAimbot )
		g_pAimbot->OnRender();


	if (Settings::Esp::esp_GrenadePrediction)
		GrenadePrediction();

	if (Settings::Esp::esp_HitMarker)
		DrawHitmarker();

	Ambient();

	if (Settings::Misc::misc_AwpAim && IsLocalAlive() && g_pPlayers->GetLocal()->WeaponIndex == WEAPON_AWP | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SSG08)
	{
		Color AwpAimColor = Color(int(Settings::Misc::misc_AwpAimColor[0] * 255.f),
			int(Settings::Misc::misc_AwpAimColor[1] * 255.f),
			int(Settings::Misc::misc_AwpAimColor[2] * 255.f));

		g_pRender->DrawFillBox(iScreenWidth / 2 - 1, iScreenHeight / 2 - 1, 3, 3, AwpAimColor);
	}

	for ( BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++ )
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer( PlayerIndex );

		if ( pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate && CheckPlayerTeam( pPlayer ) )
		{


			DrawPlayerEsp( pPlayer );

			if ( Settings::Esp::esp_Skeleton )
				DrawPlayerSkeleton( pPlayer );

			if ( Settings::Esp::esp_BulletTrace )
				DrawPlayerBulletTrace( pPlayer );
		}
	}

	if ( Settings::Esp::esp_BombTimer )
	{
		if ( bC4Timer && iC4Timer )
		{
			float fTimeStamp = Interfaces::Engine()->GetLastTimeStamp();

			if ( !fExplodeC4Timer )
			{
				fExplodeC4Timer = fTimeStamp + (float)iC4Timer;
			}
			else
			{
				fC4Timer = fExplodeC4Timer - fTimeStamp;

				if ( fC4Timer < 0.f )
					fC4Timer = 0.f;
			}
		}
		else
		{
			fExplodeC4Timer = 0.f;
			fC4Timer = 0.f;
		}
	}

	if ( Settings::Esp::esp_Bomb || Settings::Esp::esp_WorldWeapons || Settings::Esp::esp_WorldGrenade || Settings::Esp::esp_BoxNade )
	{
		for ( int EntIndex = 0; EntIndex < Interfaces::EntityList()->GetHighestEntityIndex(); EntIndex++ )
		{
			CBaseEntity* pEntity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity( EntIndex );

			if ( !pEntity || pEntity->IsPlayer() )
				continue;

			const model_t* pModel = pEntity->GetModel();

			if ( pModel )
			{
				const char* pModelName = Interfaces::ModelInfo()->GetModelName( pModel );

				if ( pModelName )
				{
					Vector vEntScreen;

					if ( WorldToScreen( pEntity->GetRenderOrigin() , vEntScreen ) )
					{
						if ( Settings::Esp::esp_Bomb && pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CC4 )
						{
							g_pRender->Text( (int)vEntScreen.x , (int)vEntScreen.y , true , true , Color::Green() ,
											 "[C4]" );
						}

						if (Settings::Esp::esp_Bomb && pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CPlantedC4)
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::DarkRed(),
								"[C4 PLANTED]");
						}

						if (Settings::Esp::esp_WorldWeapons && !strstr(pModelName, "models/weapons/w_eq_")
							&& !strstr(pModelName, "models/weapons/w_ied"))
						{
							if (strstr(pModelName, "models/weapons/w_") && strstr(pModelName, "_dropped.mdl"))
							{
								string WeaponName = pModelName + 17;

								WeaponName[WeaponName.size() - 12] = '\0';

								if (strstr(pModelName, "models/weapons/w_rif") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 4);
								}
								else if (strstr(pModelName, "models/weapons/w_pist") && strstr(pModelName, "_dropped.mdl") && !strstr(pModelName, "models/weapons/w_pist_223"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_pist_223") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "usp-s";
								}
								else if (strstr(pModelName, "models/weapons/w_smg") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 4);
								}
								else if (strstr(pModelName, "models/weapons/w_mach") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_shot") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_snip") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}

								g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::White(),
									WeaponName.c_str());
							}
						}

						if (Settings::Esp::esp_BoxNade && (strstr(pModelName, "models/weapons/w_eq_")) || strstr(pModelName, "models/Weapons/w_eq_"))
						{
							if (strstr(pModelName, "_dropped.mdl"))
							{
								if (strstr(pModelName, "fraggrenade"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Red());
								}
								else if (strstr(pModelName, "molotov"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::OrangeRed());
								}
								else if (strstr(pModelName, "incendiarygrenade"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::OrangeRed());
								}
								else if (strstr(pModelName, "flashbang"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Yellow());
								}
							}
								else if (strstr(pModelName, "smokegrenade_thrown.mdl"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Gray());
								}
							}
						
						if ( Settings::Esp::esp_WorldGrenade &&
							( strstr( pModelName , "models/weapons/w_eq_" ) ||
							 strstr( pModelName , "models/Weapons/w_eq_" ) ) )
						{
							if ( strstr( pModelName , "_dropped.mdl" ) )
							{
								string WeaponName = pModelName + 20;

								WeaponName[WeaponName.size() - 12] = '\0';

								Color GrenadeColor = Color::White();

								if ( strstr( pModelName , "fraggrenade" ) )
								{
									WeaponName = "Grenade";
									GrenadeColor = Color::Red();
								}
								else if (strstr(pModelName, "molotov"))
								{
									WeaponName = "Molotov";
									GrenadeColor = Color::OrangeRed();
								}
								else if (strstr(pModelName, "incendiarygrenade"))
								{
									WeaponName = "Incendiary";
									GrenadeColor = Color::OrangeRed();
								}
								else if ( strstr( pModelName , "flashbang" ) )
								{
									WeaponName = "Flashbang";
									GrenadeColor = Color::Yellow();
								}

								g_pRender->Text( (int)vEntScreen.x , (int)vEntScreen.y , true , true , GrenadeColor ,
												 WeaponName.c_str() );
							}
							else if ( strstr( pModelName , "smokegrenade_thrown.mdl" ) )
							{
								string WeaponName = "Smoke";

								g_pRender->Text( (int)vEntScreen.x , (int)vEntScreen.y , true , true , Color::Gray() ,
												 WeaponName.c_str() );
							}
						}
					}
				}
			}
		}
	}

	// Draw Ticks

	if (Settings::Aimbot::aim_Backtrack && Settings::Aimbot::aim_DrawBacktrack) // Use Esp Visible Combo to change from visible only and not visible.
	{
		for (int i = 0; i < Interfaces::EntityList()->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			CBaseEntity *entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
			CPlayer* pPlayer = g_pPlayers->GetPlayer(i);
			PlayerInfo pinfo;
			if (entity == nullptr)
				continue;
			if (entity == local)
				continue;
			if (entity->IsDormant())
				continue;
			if (entity->GetTeam() == local->GetTeam())
				continue;
			if (Interfaces::Engine()->GetPlayerInfo(i, &pinfo) && !entity->IsDead())
			{
				if (Settings::Esp::esp_Visible >= 3)
				{
					if (!local->IsDead() && pPlayer->bVisible)
					{
						for (int t = 0; t < Settings::Aimbot::aim_Backtracktickrate; ++t)
						{
							Vector screenbacktrack[64][12];

							if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimTime())
							{
								if (WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
								{
									g_pRender->DrawFillBox(screenbacktrack[i][t].x, screenbacktrack[i][t].y, 4, 4, g_pEsp->GetPlayerColor(pPlayer));
								}
							}
						}
					}
					else
					{
						memset(&headPositions[0][0], 0, sizeof(headPositions));
					}
				}
				else
				{
					if (!local->IsDead())
					{
						for (int t = 0; t < Settings::Aimbot::aim_Backtracktickrate; ++t)
						{
							Vector screenbacktrack[64][12];

							if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimTime())
							{
								if (WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
								{
									g_pRender->DrawFillBox(screenbacktrack[i][t].x, screenbacktrack[i][t].y, 4, 4, g_pEsp->GetPlayerColor(pPlayer));
								}
							}
						}
					}
					else
					{
						memset(&headPositions[0][0], 0, sizeof(headPositions));
					}
				}
			}
		}
	}
	}


void MsgFunc_ServerRankRevealAll()
{
	using tServerRankRevealAllFn = bool( __cdecl* )( int* );
	static tServerRankRevealAllFn ServerRankRevealAll = 0;

	if ( !ServerRankRevealAll )
	{
		ServerRankRevealAll = (tServerRankRevealAllFn)(
			CSX::Memory::FindPattern( CLIENT_DLL , "55 8B EC 8B 0D ? ? ? ? 68" , 0 ) );
	}

	if ( ServerRankRevealAll )
	{
		int fArray[3] = { 0,0,0 };
		ServerRankRevealAll( fArray );
	}
}

void CEsp::Junk4()
{
	float bmTXNVhrdQ = 2824883350599; bmTXNVhrdQ = 50745916351536; if (bmTXNVhrdQ = 58099759912788) bmTXNVhrdQ = 45207686719071; bmTXNVhrdQ = 24665602688632; bmTXNVhrdQ = 26886322466560;
	if (bmTXNVhrdQ = 87502034520768)bmTXNVhrdQ = 99127888245415; bmTXNVhrdQ = 82465619225583;
	if (bmTXNVhrdQ = 54773598530504)bmTXNVhrdQ = 99127888245415; bmTXNVhrdQ = 82465619225583;
	if (bmTXNVhrdQ = 54773598530504)bmTXNVhrdQ = 99127888245415; bmTXNVhrdQ = 82465619225583;
	if (bmTXNVhrdQ = 54773598530504)bmTXNVhrdQ = 99127888245415; bmTXNVhrdQ = 82465619225583;
	if (bmTXNVhrdQ = 54773598530504)bmTXNVhrdQ = 99127888245415; bmTXNVhrdQ = 82465619225583; bmTXNVhrdQ = 54991346319792;

	float uiLCuebFcQ = 98754673018743; uiLCuebFcQ = 42534148701331; if (uiLCuebFcQ = 31502151022020) uiLCuebFcQ = 88357386690717; uiLCuebFcQ = 6937422778732; uiLCuebFcQ = 7787326937422;
	if (uiLCuebFcQ = 8632978835738)uiLCuebFcQ = 10220204733117; uiLCuebFcQ = 12576915679254;
	if (uiLCuebFcQ = 84051666630626)uiLCuebFcQ = 10220204733117; uiLCuebFcQ = 12576915679254;
	if (uiLCuebFcQ = 84051666630626)uiLCuebFcQ = 10220204733117; uiLCuebFcQ = 12576915679254;
	if (uiLCuebFcQ = 84051666630626)uiLCuebFcQ = 10220204733117; uiLCuebFcQ = 12576915679254;
	if (uiLCuebFcQ = 84051666630626)uiLCuebFcQ = 10220204733117; uiLCuebFcQ = 12576915679254; uiLCuebFcQ = 29484791455890;

}

void CEsp::OnCreateMove( CUserCmd* pCmd )
{
	if ( Settings::Esp::esp_Rank && pCmd->buttons & IN_SCORE )
		MsgFunc_ServerRankRevealAll();
	
	g_pEsp->SoundEsp.Update();
}

void CEsp::OnReset()
{
	g_pEsp->SoundEsp.Sound.clear();

	if ( Settings::Esp::esp_BombTimer )
	{
		if ( Settings::Esp::esp_BombTimer > 60 )
			Settings::Esp::esp_BombTimer = 60;

		bC4Timer = false;
		iC4Timer = Settings::Esp::esp_BombTimer;
	}
}

void CEsp::OnEvents( IGameEvent* pEvent )
{
	if ( g_pEsp && Settings::Esp::esp_BombTimer )
	{
		if ( !strcmp( pEvent->GetName() , "bomb_defused" ) || !strcmp( pEvent->GetName() , "bomb_exploded" ) )
		{
			bC4Timer = false;
		}
		else if ( !strcmp( pEvent->GetName() , "bomb_planted" ) )
		{
			bC4Timer = true;
		}
	}
}

void CEsp::OnDrawModelExecute( IMatRenderContext* ctx , const DrawModelState_t &state , const ModelRenderInfo_t &pInfo , matrix3x4_t *pCustomBoneToWorld )
{
	if ( !g_pPlayers || Interfaces::Engine()->IsTakingScreenshot() || !Interfaces::Engine()->IsConnected() || !pInfo.pModel )
		return;

	static bool InitalizeMaterial = false;

	if ( !InitalizeMaterial )
	{
		visible_flat = CreateMaterial( true , false );
		visible_tex = CreateMaterial( false , false );
		hidden_flat = CreateMaterial( true , true );
		hidden_tex = CreateMaterial( false , true );

		InitalizeMaterial = true;

		return;
	}

	string strModelName = Interfaces::ModelInfo()->GetModelName( pInfo.pModel );

	if ( strModelName.size() <= 1 )
		return;

	if (Settings::Misc::misc_ChamsMaterials)
	{
		if (strModelName.find("models/player") != std::string::npos)
		{
			IClientEntity* pBaseEntity = Interfaces::EntityList()->GetClientEntity(pInfo.entity_index);

			if (pBaseEntity && pBaseEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CCSPlayer)
			{
				IMaterial *material;
				switch (Settings::Misc::misc_ChamsMaterialsList)
				{
				case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
				case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
				case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
				case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
				case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
				case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
				case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
				case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
				}
				Color color = Color(255, 255, 255, 255);
				if (Settings::Esp::esp_ChamsVisible <= 2)
				{
						ForceMaterial(color, material);
						material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				}
				else
				{
						ForceMaterial(color, material);
						material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
			}
		}
	}

	if (Settings::Misc::misc_ArmMaterials)
	{
		switch (Settings::Misc::misc_ArmMaterialsType)
		{
		case 0: if (strModelName.find("arms") != std::string::npos)
		{
			IMaterial *material;
			switch (Settings::Misc::misc_ArmMaterialsList)
			{
			case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
			case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
			case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
			case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
			case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
			case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
			case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
			case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
			}
			Color color = Color(255, 255, 255, 255);
			ForceMaterial(color, material);
			Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
		} break;
		case 1: if (strModelName.find("weapons/v") != std::string::npos)
		{
			IMaterial *material;
			switch (Settings::Misc::misc_ArmMaterialsList)
			{
			case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
			case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
			case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
			case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
			case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
			case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
			case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
			case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
			}
			Color color = Color(255, 255, 255, 255);
			ForceMaterial(color, material);
			Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
		} break;
		}
	}

	if (Settings::Misc::misc_NoHands)
	{
		if (strModelName.find("arms") != string::npos && Settings::Misc::misc_NoHands)
		{
			IMaterial* Hands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			Interfaces::ModelRender()->ForcedMaterialOverride(Hands);
		}
	}
	else
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* Hands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
		}
	}

	if (Settings::Misc::misc_WireHands) //Wireframe Hands
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* WireHands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			WireHands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			Interfaces::ModelRender()->ForcedMaterialOverride(WireHands);
		}
	}
	else
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* WireHands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			WireHands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
		}
	}


	if ( Settings::Esp::esp_Chams && Client::g_pPlayers && Client::g_pPlayers->GetLocal() && strModelName.find( "models/player" ) != string::npos )
	{
		IClientEntity* pBaseEntity = Interfaces::EntityList()->GetClientEntity( pInfo.entity_index );

		if ( pBaseEntity && pBaseEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CCSPlayer )
		{
			CPlayer* pPlayer = g_pPlayers->GetPlayer( pInfo.entity_index );

			if ( pPlayer && pPlayer->bUpdate )
			{
				bool CheckTeam = false;

				Color TeamHideColor;
				Color TeamVisibleColor;

				if ( Settings::Esp::esp_Enemy && pPlayer->Team != g_pPlayers->GetLocal()->Team ) // Противнико?
					CheckTeam = true;

				if ( Settings::Esp::esp_Team && pPlayer->Team == g_pPlayers->GetLocal()->Team ) // Свои?
					CheckTeam = true;

				if ( pPlayer->Team == TEAM_CT )
				{
					TeamHideColor = Color( int( Settings::Esp::chams_Color_CT[0] * 255.f ) ,
										   int( Settings::Esp::chams_Color_CT[1] * 255.f ) ,
										   int( Settings::Esp::chams_Color_CT[2] * 255.f ) );
				}
				else if ( pPlayer->Team == TEAM_TT )
				{
					TeamHideColor = Color( int( Settings::Esp::chams_Color_TT[0] * 255.f ) ,
										   int( Settings::Esp::chams_Color_TT[1] * 255.f ) ,
										   int( Settings::Esp::chams_Color_TT[2] * 255.f ) );
				}

				bool SetColor = false;

				if ( Settings::Esp::esp_ChamsVisible == 0 && pPlayer->Team != g_pPlayers->GetLocal()->Team ) // Противнико?
				{
					SetColor = true;
				}
				else if ( Settings::Esp::esp_ChamsVisible == 1 && pPlayer->Team == g_pPlayers->GetLocal()->Team ) // Свои?
				{
					SetColor = true;
				}
				else if ( Settings::Esp::esp_ChamsVisible == 2 ) // Всех
				{
					SetColor = true;
				}

				if ( SetColor )
				{
					if ( pPlayer->Team == TEAM_CT )
					{
						TeamVisibleColor = Color( int( Settings::Esp::chams_Color_VCT[0] * 255.f ) ,
												  int( Settings::Esp::chams_Color_VCT[1] * 255.f ) ,
												  int( Settings::Esp::chams_Color_VCT[2] * 255.f ) );
					}
					else if ( pPlayer->Team == TEAM_TT )
					{
						TeamVisibleColor = Color( int( Settings::Esp::chams_Color_VTT[0] * 255.f ) ,
												  int( Settings::Esp::chams_Color_VTT[1] * 255.f ) ,
												  int( Settings::Esp::chams_Color_VTT[2] * 255.f ) );
					}
				}
				else
					TeamVisibleColor = TeamHideColor;

				if (CheckTeam && !Settings::Misc::misc_ChamsMaterials)
				{
					if (Settings::Esp::esp_ChamsVisible <= 2)
					{
						if (Settings::Esp::esp_Chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
						else if (Settings::Esp::esp_Chams >= 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
					}
					else
					{
						if (Settings::Esp::esp_Chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
						else if (Settings::Esp::esp_Chams >= 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
					}

					Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

					if (Settings::Esp::esp_Chams == 1)
					{
						ForceMaterial(TeamVisibleColor, visible_flat);
						visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
					else if (Settings::Esp::esp_Chams >= 2)
					{
						ForceMaterial(TeamVisibleColor, visible_tex);
						visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
				}
			}
		}
	}
}

void CEsp::Junk5()
{
	float mPnysyzIcV = 6193997279022; mPnysyzIcV = 47497295242420; if (mPnysyzIcV = 20555589604596) mPnysyzIcV = 30225825658879; mPnysyzIcV = 19977416485226; mPnysyzIcV = 64852261997741;
	if (mPnysyzIcV = 74450883022582)mPnysyzIcV = 96045961240742; mPnysyzIcV = 95537123788016;
	if (mPnysyzIcV = 38384004802360)mPnysyzIcV = 96045961240742; mPnysyzIcV = 95537123788016;
	if (mPnysyzIcV = 38384004802360)mPnysyzIcV = 96045961240742; mPnysyzIcV = 95537123788016;
	if (mPnysyzIcV = 38384004802360)mPnysyzIcV = 96045961240742; mPnysyzIcV = 95537123788016;
	if (mPnysyzIcV = 38384004802360)mPnysyzIcV = 96045961240742; mPnysyzIcV = 95537123788016; mPnysyzIcV = 44927965215273;

	float fjTmnnEVnA = 3652521144328; fjTmnnEVnA = 49608288809046; if (fjTmnnEVnA = 24122504325145) fjTmnnEVnA = 55640414198888; fjTmnnEVnA = 4777414684048; fjTmnnEVnA = 6840484777414;
	if (fjTmnnEVnA = 45939825564041)fjTmnnEVnA = 43251451320916; fjTmnnEVnA = 74178437967840;
	if (fjTmnnEVnA = 67322763570683)fjTmnnEVnA = 43251451320916; fjTmnnEVnA = 74178437967840;
	if (fjTmnnEVnA = 67322763570683)fjTmnnEVnA = 43251451320916; fjTmnnEVnA = 74178437967840;
	if (fjTmnnEVnA = 67322763570683)fjTmnnEVnA = 43251451320916; fjTmnnEVnA = 74178437967840;
	if (fjTmnnEVnA = 67322763570683)fjTmnnEVnA = 43251451320916; fjTmnnEVnA = 74178437967840; fjTmnnEVnA = 79440519865168;

}

void CEsp::DrawPlayerEsp( CPlayer* pPlayer )
{
	bool bOriginScreen = ( pPlayer->vOriginScreen.x > 0 && pPlayer->vOriginScreen.y > 0 );
	bool bHitBoxScreen = ( pPlayer->vHitboxHeadScreen.x > 0 && pPlayer->vHitboxHeadScreen.y > 0 );

	if ( !bOriginScreen && !bHitBoxScreen )
		return;

	Vector vLineOrigin;

	if ( Settings::Esp::esp_Size < 0 )
	{
		Settings::Esp::esp_Size = 1;
	}
	else if ( Settings::Esp::esp_Size > 10 )
	{
		Settings::Esp::esp_Size = 10;
	}

	int Height = (int)pPlayer->vOriginScreen.y - (int)pPlayer->vHitboxHeadScreen.y;

	if ( Height < 18 )
		Height = 18;

	int Width = Height / 2;

	int x = (int)pPlayer->vHitboxHeadScreen.x - Width / 2;
	int y = (int)pPlayer->vHitboxHeadScreen.y;

	vLineOrigin = pPlayer->vHitboxHeadScreen;
	vLineOrigin.y += Height;

	Color EspPlayerColor = GetPlayerColor( pPlayer );
	Color EspVisibleColor = GetPlayerVisibleColor( pPlayer );

	if ( Settings::Esp::esp_Size )
	{
		if ( Settings::Esp::esp_Style == 0 )
		{
			if ( !Settings::Esp::esp_Outline )
			{
				g_pRender->DrawBox( x , y , Width , Height , EspVisibleColor );
			}
			else if ( Settings::Esp::esp_Outline )
			{
				g_pRender->DrawOutlineBox( x , y , Width , Height , EspVisibleColor );
			}
		}
		else if ( Settings::Esp::esp_Style >= 1 )
		{
			if ( !Settings::Esp::esp_Outline )
			{
				g_pRender->DrawCoalBox( x , y , Width , Height , EspVisibleColor );
			}
			else if ( Settings::Esp::esp_Outline )
			{
				g_pRender->DrawOutlineCoalBox( x , y , Width , Height , EspVisibleColor );
			}
		}
	}

	if ( Settings::Esp::esp_Line )
	{
		g_pRender->DrawLine( (int)vLineOrigin.x , (int)vLineOrigin.y , iScreenWidth / 2 , iScreenHeight , EspVisibleColor );
	}

	if ( Settings::Esp::esp_Name )
	{
		g_pRender->Text( (int)vLineOrigin.x , (int)pPlayer->vHitboxHeadScreen.y - 13 , true , true , EspPlayerColor , pPlayer->Name.c_str() );
	}

	int iHpAmY = 1;

	if ( Settings::Esp::esp_Health >= 1 )
	{
		Color Minus = Color::Red();

		if ( pPlayer->Team == TEAM_CT )
		{
			Minus = CT_HP_ColorM;
		}
		else if ( pPlayer->Team == TEAM_TT )
		{
			Minus = TT_HP_ColorM;
		}

		int iHealth = pPlayer->iHealth;

		if ( iHealth )
		{
			if ( Settings::Esp::esp_Health == 1 )
			{
				g_pRender->Text( (int)vLineOrigin.x , (int)vLineOrigin.y + iHpAmY , true , true , EspPlayerColor , to_string( iHealth ).c_str() );
				iHpAmY += 10;
			}
			else if ( Settings::Esp::esp_Health == 2 )
			{
				g_pRender->DrawHorBar( x , (int)vLineOrigin.y + iHpAmY , Width , 5 , iHealth , Color::LawnGreen() , Minus );
				iHpAmY += 6;
			}
			else if ( Settings::Esp::esp_Health >= 3 )
			{
				g_pRender->DrawVerBar( x - 6 , (int)pPlayer->vHitboxHeadScreen.y , 5 , Height , iHealth , Color::LawnGreen() , Minus );
			}
		}
	}

	if ( Settings::Esp::esp_Armor >= 1 )
	{
		Color Minus = Color::Red();

		if ( pPlayer->Team == TEAM_CT )
		{
			Minus = CT_AR_ColorM;
		}
		else if ( pPlayer->Team == TEAM_TT )
		{
			Minus = TT_AR_ColorM;
		}

		int iArmor = pPlayer->iArmor;

		if ( iArmor )
		{
			if ( Settings::Esp::esp_Armor == 1 )
			{
				g_pRender->Text( (int)vLineOrigin.x , (int)vLineOrigin.y + iHpAmY , true , true ,
								 EspPlayerColor ,
								 to_string( iArmor ).c_str() );
				iHpAmY += 10;
			}
			if ( Settings::Esp::esp_Armor == 2 )
			{
				g_pRender->DrawHorBar( x , (int)vLineOrigin.y + iHpAmY , Width , 5 , iArmor ,
									   Color::White() , Minus );
				iHpAmY += 6;
			}
			else if ( Settings::Esp::esp_Armor >= 3 )
			{
				g_pRender->DrawVerBar( x + Width + 1 , (int)pPlayer->vHitboxHeadScreen.y , 5 , Height , iArmor ,
									   Color::White() , Minus );
			}
		}
	}

	if ( Settings::Esp::esp_Weapon && !pPlayer->WeaponName.empty() )
	{
		string WeaponStr = pPlayer->WeaponName; WeaponStr.erase(0, 6);

		if ( Settings::Esp::esp_Ammo && pPlayer->iWAmmo )
		{
			WeaponStr += " (";
			WeaponStr += to_string( pPlayer->iWAmmo );
			WeaponStr += ")";
		}

		g_pRender->Text( (int)vLineOrigin.x , (int)vLineOrigin.y + iHpAmY , true , true , EspPlayerColor , WeaponStr.c_str() );
		iHpAmY += 10;
	}

	if ( Settings::Esp::esp_Distance && g_pPlayers->GetLocal()->bAlive )
	{
		int Distance = pPlayer->iDistance;
		g_pRender->Text( (int)vLineOrigin.x , (int)vLineOrigin.y + iHpAmY , true , true , EspPlayerColor , to_string( Distance ).c_str() );
	}
}

void CEsp::DrawPlayerSkeleton( CPlayer* pPlayer )
{
	Color SkeletonColor = GetPlayerColor( pPlayer );

	for ( BYTE IndexArray = 0; IndexArray < 18; IndexArray++ )
	{
		DrawHitBoxLine( pPlayer->vHitboxSkeletonArray[IndexArray] , SkeletonColor );
	}
}

void CEsp::DrawPlayerBulletTrace( CPlayer* pPlayer )
{
	Color EspColor = GetPlayerColor( pPlayer );

	if ( !pPlayer->vBulletTraceArray[0].IsZero() && !pPlayer->vBulletTraceArray[1].IsZero() )
	{
		g_pRender->DrawLine(
			(int)pPlayer->vBulletTraceArray[0].x , (int)pPlayer->vBulletTraceArray[0].y ,
			(int)pPlayer->vBulletTraceArray[1].x , (int)pPlayer->vBulletTraceArray[1].y , EspColor );

		g_pRender->DrawFillBox( (int)pPlayer->vBulletTraceArray[1].x - 2 , (int)pPlayer->vBulletTraceArray[1].y - 2 , 4 , 4 , EspColor );
	}
}

void CEsp::DrawHitBoxLine( Vector* vHitBoxArray , Color color )
{
	Vector vHitBoxOneScreen;
	Vector vHitBoxTwoScreen;

	if ( vHitBoxArray[0].IsZero() || !vHitBoxArray[0].IsValid() || vHitBoxArray[1].IsZero() || !vHitBoxArray[1].IsValid() )
		return;

	if ( WorldToScreen( vHitBoxArray[0] , vHitBoxOneScreen ) && WorldToScreen( vHitBoxArray[1] , vHitBoxTwoScreen ) )
	{
		g_pRender->DrawLine( (int)vHitBoxOneScreen.x , (int)vHitBoxOneScreen.y ,
			(int)vHitBoxTwoScreen.x , (int)vHitBoxTwoScreen.y , color );
	}
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class iutrvis {
public:
	bool nglpqjonoijfd;
	double nkrhemze;
	double ihqkdwivvctlou;
	string kscbdodtpbyikwt;
	bool qfvmzpnbco;
	iutrvis();
	void nvhhbetlvpptr(string scyezrpoyogozd, int zkwjriotmgqub, bool adyrfkhqev, string ptvxwirnhwxkwna, double zxmav, double bqqbnudcqoazejw, string pzidqx);
	double xsglfciyphovtq(int papgigvleklbf, string dgevkz, bool ltnskvgmuufekhu, double hjwymqytcxmztp);
	int rzxewccghbieopixmzrwr(double ebfprctux, double qvxqnrwr, double xfrmhcjnmwk, string kmwszcnqljmtz);
	bool jdhwgcipat(double elhvzsnnyoutua, string qssli, bool ltfxvrwgvxlysl, bool jlavtuwjv);
	int lysbfwighronmkysfqtdhpnu(string heqlqjeirbbbq, bool stczipxjirerqj, int awcmbryc, double nxdgykin);

protected:
	double xtfmde;
	double zuqbuszjv;
	int chztdenxzbm;
	int detstaqaqlcpmgd;
	string hhllzd;

	int qwfrsrnyrvhrf(double goconkejgd);

private:
	string phgyo;
	string jsjubinbsqp;
	double acaosnspfkf;

	int vfyjnostgrffas(int kqmwpltihsmq, bool fvrfqglc, double ydlnalaxph, int sdkmiib, int javzivgukdl, string ttowqcpxemjfip, bool rxpeworcpfa);
	void hroqtzupgetejgmhbbco(string dfdnqrw, double obfetthjjcb, double kggrdbephtx, double sdyubgisijcum, bool xbrcqmyddczdub, int esfhmj, bool ixpwmiay);

};


int iutrvis::vfyjnostgrffas(int kqmwpltihsmq, bool fvrfqglc, double ydlnalaxph, int sdkmiib, int javzivgukdl, string ttowqcpxemjfip, bool rxpeworcpfa) {
	int krwvmfpdmdgomcu = 8167;
	double xucuotzrbjnt = 68943;
	return 36076;
}

void iutrvis::hroqtzupgetejgmhbbco(string dfdnqrw, double obfetthjjcb, double kggrdbephtx, double sdyubgisijcum, bool xbrcqmyddczdub, int esfhmj, bool ixpwmiay) {
	string naocqtfyvifc = "bicycbunjqgvds";
	if (string("bicycbunjqgvds") == string("bicycbunjqgvds")) {
		int nuocoo;
		for (nuocoo = 55; nuocoo > 0; nuocoo--) {
			continue;
		}
	}
	if (string("bicycbunjqgvds") == string("bicycbunjqgvds")) {
		int dnsqpmnzh;
		for (dnsqpmnzh = 45; dnsqpmnzh > 0; dnsqpmnzh--) {
			continue;
		}
	}

}

int iutrvis::qwfrsrnyrvhrf(double goconkejgd) {
	string dccpmsb = "mgzhxbiznyyaieev";
	double kllhjgljcb = 22672;
	int symfbucjlx = 6605;
	bool dqqvddxnnulgnau = true;
	int heuymcqwk = 1541;
	double zqwzh = 7848;
	bool aymqkogu = false;
	string spwftdanmq = "idyzygeuwodiatizrjbnohnbtpswxpkvepjzpyrqwionpdvsjjbaaggyxhgppxvum";
	string bddpudsowketq = "ekrhcunctviqopibyjidlakbllykhwyvloe";
	bool tyumtugzreols = true;
	if (1541 != 1541) {
		int wgho;
		for (wgho = 84; wgho > 0; wgho--) {
			continue;
		}
	}
	if (1541 == 1541) {
		int iu;
		for (iu = 28; iu > 0; iu--) {
			continue;
		}
	}
	if (6605 == 6605) {
		int zekjay;
		for (zekjay = 21; zekjay > 0; zekjay--) {
			continue;
		}
	}
	if (string("mgzhxbiznyyaieev") != string("mgzhxbiznyyaieev")) {
		int rsdho;
		for (rsdho = 26; rsdho > 0; rsdho--) {
			continue;
		}
	}
	return 31186;
}

void iutrvis::nvhhbetlvpptr(string scyezrpoyogozd, int zkwjriotmgqub, bool adyrfkhqev, string ptvxwirnhwxkwna, double zxmav, double bqqbnudcqoazejw, string pzidqx) {
	string ihqkdlajmon = "gdegaujqzntiguojsitrf";
	double jjjixqfa = 2037;
	string bxlcymeugzi = "fhqcevaxoxtifujitttjfmboyehnpzsvetpbxmkpiotumetresxscqobtyrajbggpsqcisrtjoyzyhegmxitctbyntktrp";
	double hhyxhyvupnzbd = 2561;
	bool rprurduu = true;
	int wdeqjm = 2506;
	bool nktjtyughtfjqjz = false;
	double enlhpghfgf = 2678;
	string fcrlnpjt = "ufuoisidhkqffpmlcrrmgsybchohcrdysarltgbhfg";
	string fcbywcx = "nzzuxkdnmjauhbchvgz";
	if (string("gdegaujqzntiguojsitrf") == string("gdegaujqzntiguojsitrf")) {
		int hhete;
		for (hhete = 76; hhete > 0; hhete--) {
			continue;
		}
	}
	if (2037 == 2037) {
		int kcukapi;
		for (kcukapi = 40; kcukapi > 0; kcukapi--) {
			continue;
		}
	}
	if (2506 != 2506) {
		int tujvvkbw;
		for (tujvvkbw = 41; tujvvkbw > 0; tujvvkbw--) {
			continue;
		}
	}

}

double iutrvis::xsglfciyphovtq(int papgigvleklbf, string dgevkz, bool ltnskvgmuufekhu, double hjwymqytcxmztp) {
	double fbhrlavhv = 567;
	double rzdrg = 24368;
	string gqkdih = "verlejgeikqucijxzxjkojljpngcwrugztcrpecfslnskfjamahcxjgypxjntzkbiduxdkdyqmtzvgirsosiptgbbmwikrfe";
	if (567 == 567) {
		int uwpc;
		for (uwpc = 74; uwpc > 0; uwpc--) {
			continue;
		}
	}
	return 60729;
}

int iutrvis::rzxewccghbieopixmzrwr(double ebfprctux, double qvxqnrwr, double xfrmhcjnmwk, string kmwszcnqljmtz) {
	int kkbdkkkd = 3256;
	double ivqoqeooo = 17059;
	bool ziyofijbccy = true;
	double bxbhmbfhxyxhpj = 6801;
	string zeqizwerhoqq = "yzkwpzdvaiolrhbaqhvbtjewfxleeglbitdmrhqzvywimloctdumtuzzhleetmqcnkrkszttnqefrrrsonngkxxmseittjxcjg";
	double xazoqnza = 15902;
	bool fuvbxxal = false;
	double fsfjrsyjufj = 47328;
	bool icqlug = false;
	if (false != false) {
		int ccfbq;
		for (ccfbq = 33; ccfbq > 0; ccfbq--) {
			continue;
		}
	}
	if (true == true) {
		int wycrikr;
		for (wycrikr = 41; wycrikr > 0; wycrikr--) {
			continue;
		}
	}
	if (false == false) {
		int oirswtfvoi;
		for (oirswtfvoi = 61; oirswtfvoi > 0; oirswtfvoi--) {
			continue;
		}
	}
	return 84024;
}

bool iutrvis::jdhwgcipat(double elhvzsnnyoutua, string qssli, bool ltfxvrwgvxlysl, bool jlavtuwjv) {
	string mtuhfuabixeepfc = "zgpcrnndldiraqusqtbxormgvifgsyrhrqnicqtltajechuuowrkxbfhybpsvcrrdbbacxtjvlmfkxzfcecvvrfxiylmdmebnps";
	int kykmahf = 4142;
	int icmmjmpyzkslz = 1828;
	bool tompcl = false;
	double hirpp = 23194;
	string cwnnqmb = "unrinikfgwlzgxoinxqrhghjsirkuinwlridqpeltuubglqzzyqziu";
	string zzslzpulged = "uirqvfxjlntyrysxbcalbnnadcrenzvokapvrzpcpsih";
	double ubmnd = 9938;
	if (1828 == 1828) {
		int tcnjjgoq;
		for (tcnjjgoq = 53; tcnjjgoq > 0; tcnjjgoq--) {
			continue;
		}
	}
	if (23194 != 23194) {
		int ruktsdytkb;
		for (ruktsdytkb = 62; ruktsdytkb > 0; ruktsdytkb--) {
			continue;
		}
	}
	return true;
}

int iutrvis::lysbfwighronmkysfqtdhpnu(string heqlqjeirbbbq, bool stczipxjirerqj, int awcmbryc, double nxdgykin) {
	int vbyipgl = 5910;
	int drzejmrswd = 358;
	double klfqintu = 2531;
	string cyqeaakufm = "apwdctdyjmmsnjtkjmymlcdreykqixsldipclgulimfikftqhsxxjqurgakupuearucypifzevce";
	bool whxsyxj = false;
	bool mrzkicmbdjhdif = false;
	if (string("apwdctdyjmmsnjtkjmymlcdreykqixsldipclgulimfikftqhsxxjqurgakupuearucypifzevce") == string("apwdctdyjmmsnjtkjmymlcdreykqixsldipclgulimfikftqhsxxjqurgakupuearucypifzevce")) {
		int vfvt;
		for (vfvt = 17; vfvt > 0; vfvt--) {
			continue;
		}
	}
	return 28273;
}

iutrvis::iutrvis() {
	this->nvhhbetlvpptr(string("ifhytrqeywcd"), 1314, false, string("xmjde"), 32120, 82566, string("rffolkkxqiqtowlfzlofmltrdzrztasfoqifyjxemokcodedxfjsyieaorrmwydprllkznnzrxdskxmmbjumwjkpl"));
	this->xsglfciyphovtq(4391, string("ljotgtadqbbnf"), true, 5120);
	this->rzxewccghbieopixmzrwr(3843, 1131, 1117, string("glqyxfsbpzqvhepaezenysykobrfimxpxpnxehcbm"));
	this->jdhwgcipat(8637, string("qdxrcssuvdbswdfaftxqueenytohslxoxdmtsmlhnrupmmustejfsuanwmyscaetnqlud"), true, false);
	this->lysbfwighronmkysfqtdhpnu(string("chtzwcumpifrvpseigobhfeoozsinbrkvmhyavkbclxibfyjggb"), false, 1470, 24009);
	this->qwfrsrnyrvhrf(8908);
	this->vfyjnostgrffas(4446, false, 21207, 4555, 339, string("mkiuktczsigimlojrhpedwmtaasryyitdcerpipufgrpfay"), true);
	this->hroqtzupgetejgmhbbco(string("hivjojiuwmgmdesztnuoklxroejbzjoafuwqnpnxhzqtwkldlbbdftdiopkkcnougqvrdieqpedwgrlphytdmrggutpiuhsyca"), 7797, 20225, 6512, false, 7284, true);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hrayzjs {
public:
	int bwjadqqsponutc;
	bool qnqdupxewlhkb;
	double cljzfalvyoomgl;
	bool vixeuev;
	bool urnapdznngonqgn;
	hrayzjs();
	void imrkobjldexyu(double emkrkny);
	bool biwnzxckrrjttizmxpnzw(string uldixhkisto, string hiwjjtcrlhwi);
	void ttewjvrpwnrcwjggsuzgbufr(bool lfonhx, int vdqlbxgdeetgeug, string ebwdoczkdnokt);
	int ybwhhsackgojk();
	int shtbfffeahvknh(string iqtmyz, string wpawvy, double zfawifz, double gepnqxgp, int etgvpynrkvyrxh, bool phzqyhqd, string tcffuq, int cruxq, string ltklnyfp, bool wmdwbfmms);
	int ivpbibfsoqzqbxorwfedafso(bool xeuvpfynhciwih, int asjumcntwtzl, int hhyshkat, int vuwagngreizrwu, string jlkrgphzfo, bool wdnwpfegmu, bool eaqlcgugrew, string fjlxgf, string cjcvecmvvmle, bool cdgnrrqgl);
	string vzhfyaahowkouqbgsoabukdex(bool wxcoybrr, int rznmnie, bool rfoeqgm, string ctdcpusaksfyeh, bool xopevzxwqaeq, int ohboxgck, string hwwaaasrby, string dkhhxsfbyfwnzlg, string pdmsgmamy, bool vihdfxtcppiibck);

protected:
	double vjjcdj;
	bool gfpgsbcvgfviqw;
	double judvuwkascang;
	bool daqyysroxeay;
	double wuqgcxqyp;

	void nqdfopfvcrfykwzfqzxwrpfc(int yxrgvmu, string uxbzgvuf);
	double ndgvvqtzpfgqvcxmrtophho(string rnnojujuajuvbop, double taecwijgaajgzo, int jktwxmgi);
	void snpzanhkyylrsztlax(string dbcrcvtjbuhs, int vdyinjziiuvum, double akwustknmlbrlzg, double ulzjbebznetrq);

private:
	bool zsgmugmhh;
	bool irujxlh;
	double hclcwnh;
	double zfysedmvlsmiz;
	string zvmjwqfiplda;

	bool ijuzsswherkfmyjwknemq(double hiiahwbyakqf, bool exaaakvwupp, bool hjiimzhfgr, bool xghqvmmbhpimwb, string fuaktfu, int oammfvpter);
	bool nktzohfdjwrgmbbxyrkkproii(bool eryazrlvymzbmc, bool kmnlkqhwpwee, int obquzx);
	bool jhkaaqjgcdvllxjztlii(int mepythfdgerh, bool ktarim, int acgjkqtdqqpyqwg, string shgfdlsjg, double foybzxvo, string elxrqpjwncs, double tsnuguvpl, int zvddngy, int zoentxrpamo);
	double gqxwonxkuxyatvajhtie(bool vvetyxjmpdo, bool pqwnqmugpdrigas);

};


bool hrayzjs::ijuzsswherkfmyjwknemq(double hiiahwbyakqf, bool exaaakvwupp, bool hjiimzhfgr, bool xghqvmmbhpimwb, string fuaktfu, int oammfvpter) {
	return true;
}

bool hrayzjs::nktzohfdjwrgmbbxyrkkproii(bool eryazrlvymzbmc, bool kmnlkqhwpwee, int obquzx) {
	return true;
}

bool hrayzjs::jhkaaqjgcdvllxjztlii(int mepythfdgerh, bool ktarim, int acgjkqtdqqpyqwg, string shgfdlsjg, double foybzxvo, string elxrqpjwncs, double tsnuguvpl, int zvddngy, int zoentxrpamo) {
	string wkvpj = "mllwejccjtucsbsummtalpdopexdwnzg";
	int njoqobgjcggcon = 4966;
	if (4966 == 4966) {
		int cfxzscmyan;
		for (cfxzscmyan = 41; cfxzscmyan > 0; cfxzscmyan--) {
			continue;
		}
	}
	if (4966 != 4966) {
		int folnolh;
		for (folnolh = 39; folnolh > 0; folnolh--) {
			continue;
		}
	}
	return true;
}

double hrayzjs::gqxwonxkuxyatvajhtie(bool vvetyxjmpdo, bool pqwnqmugpdrigas) {
	return 34061;
}

void hrayzjs::nqdfopfvcrfykwzfqzxwrpfc(int yxrgvmu, string uxbzgvuf) {
	int yyoaqisqjbhi = 3174;
	bool oisjxbm = true;
	bool brclngcqv = false;
	string aovqgfad = "qzgqpqwpfnru";
	int byyvxx = 4868;
	string qegmypiuv = "qlriu";
	bool wfldzrzekmzrqal = false;
	int fhqrixv = 1663;
	double nlwuj = 9203;
	if (1663 == 1663) {
		int yfhxpspt;
		for (yfhxpspt = 83; yfhxpspt > 0; yfhxpspt--) {
			continue;
		}
	}
	if (false == false) {
		int ebblk;
		for (ebblk = 76; ebblk > 0; ebblk--) {
			continue;
		}
	}

}

double hrayzjs::ndgvvqtzpfgqvcxmrtophho(string rnnojujuajuvbop, double taecwijgaajgzo, int jktwxmgi) {
	bool fxhmpkhfeb = false;
	bool xcwicsvumr = true;
	int zctboayvdlbydgl = 64;
	double vwfqclmkudoy = 7837;
	if (64 == 64) {
		int no;
		for (no = 24; no > 0; no--) {
			continue;
		}
	}
	if (64 == 64) {
		int qprdfqdoq;
		for (qprdfqdoq = 72; qprdfqdoq > 0; qprdfqdoq--) {
			continue;
		}
	}
	if (64 == 64) {
		int kfvnwmcq;
		for (kfvnwmcq = 87; kfvnwmcq > 0; kfvnwmcq--) {
			continue;
		}
	}
	if (7837 == 7837) {
		int sn;
		for (sn = 18; sn > 0; sn--) {
			continue;
		}
	}
	return 21800;
}

void hrayzjs::snpzanhkyylrsztlax(string dbcrcvtjbuhs, int vdyinjziiuvum, double akwustknmlbrlzg, double ulzjbebznetrq) {
	bool bzhxtatbztqhzke = true;
	int usavoufrgb = 3666;
	bool cczdyqfqxmss = true;
	int rgeicvgzoimjo = 1317;
	int wbedqebofyo = 6546;
	double rmlzkdj = 21569;
	int vsgbztyrchrfz = 2908;
	bool rykzg = false;
	if (21569 != 21569) {
		int qnst;
		for (qnst = 87; qnst > 0; qnst--) {
			continue;
		}
	}

}

void hrayzjs::imrkobjldexyu(double emkrkny) {
	string jyybyxggkfl = "pqrodsndjkcqduxodwoqmltbdxznlurltahumqdandyuqccgzgbjwclcrwyorcpgpl";
	string ophmnaqyzwhgrew = "knrktjeravewxzazaszijcxsugsoydwozobxgrxboi";
	bool gwsvylatqnxa = false;
	if (false != false) {
		int cftysemgh;
		for (cftysemgh = 68; cftysemgh > 0; cftysemgh--) {
			continue;
		}
	}

}

bool hrayzjs::biwnzxckrrjttizmxpnzw(string uldixhkisto, string hiwjjtcrlhwi) {
	int okdzwz = 5053;
	string apfbjbdyxbrseqn = "rmpwk";
	if (5053 == 5053) {
		int omqjm;
		for (omqjm = 21; omqjm > 0; omqjm--) {
			continue;
		}
	}
	if (string("rmpwk") != string("rmpwk")) {
		int qavjsaeer;
		for (qavjsaeer = 79; qavjsaeer > 0; qavjsaeer--) {
			continue;
		}
	}
	if (string("rmpwk") == string("rmpwk")) {
		int mywtikoke;
		for (mywtikoke = 24; mywtikoke > 0; mywtikoke--) {
			continue;
		}
	}
	if (5053 != 5053) {
		int omfqkvt;
		for (omfqkvt = 31; omfqkvt > 0; omfqkvt--) {
			continue;
		}
	}
	return false;
}

void hrayzjs::ttewjvrpwnrcwjggsuzgbufr(bool lfonhx, int vdqlbxgdeetgeug, string ebwdoczkdnokt) {
	bool kejcgzmfgvgzytt = true;
	string utxnqfbvewisw = "zeloaocypnnvdnmycriwbfhcjfsdvyfrfslfzsls";
	string tvtbxhz = "yvnzntijoldbvfhnbvqxpyaexswpjtcwku";
	bool jnlsxzj = true;
	if (true != true) {
		int ube;
		for (ube = 64; ube > 0; ube--) {
			continue;
		}
	}
	if (true == true) {
		int zreugji;
		for (zreugji = 46; zreugji > 0; zreugji--) {
			continue;
		}
	}

}

int hrayzjs::ybwhhsackgojk() {
	int zlyfxtchoueuhp = 3180;
	bool srjvxdt = true;
	double uwasyo = 35923;
	int mijfsheeogm = 328;
	int lrgfiyx = 4674;
	double gkxdmzf = 27505;
	string iveda = "qzrnhrswr";
	if (true != true) {
		int ozsrddy;
		for (ozsrddy = 29; ozsrddy > 0; ozsrddy--) {
			continue;
		}
	}
	if (true == true) {
		int ikbqbwdvil;
		for (ikbqbwdvil = 86; ikbqbwdvil > 0; ikbqbwdvil--) {
			continue;
		}
	}
	if (4674 == 4674) {
		int chsl;
		for (chsl = 54; chsl > 0; chsl--) {
			continue;
		}
	}
	return 48955;
}

int hrayzjs::shtbfffeahvknh(string iqtmyz, string wpawvy, double zfawifz, double gepnqxgp, int etgvpynrkvyrxh, bool phzqyhqd, string tcffuq, int cruxq, string ltklnyfp, bool wmdwbfmms) {
	bool becojlrpfjxfljy = false;
	double uxyaqfzq = 3822;
	bool vprrvjxtvrm = true;
	bool dxctoxgvnrgehsb = false;
	if (true != true) {
		int nerhj;
		for (nerhj = 28; nerhj > 0; nerhj--) {
			continue;
		}
	}
	if (false == false) {
		int fqdhsq;
		for (fqdhsq = 52; fqdhsq > 0; fqdhsq--) {
			continue;
		}
	}
	if (false == false) {
		int maaegewrpr;
		for (maaegewrpr = 85; maaegewrpr > 0; maaegewrpr--) {
			continue;
		}
	}
	return 92587;
}

int hrayzjs::ivpbibfsoqzqbxorwfedafso(bool xeuvpfynhciwih, int asjumcntwtzl, int hhyshkat, int vuwagngreizrwu, string jlkrgphzfo, bool wdnwpfegmu, bool eaqlcgugrew, string fjlxgf, string cjcvecmvvmle, bool cdgnrrqgl) {
	int tkwsys = 5584;
	string twduhpbg = "ulvjbjwpumrxmbufwhjqqupukltxpemxhhmpussvbprjytbmdizyhr";
	if (string("ulvjbjwpumrxmbufwhjqqupukltxpemxhhmpussvbprjytbmdizyhr") == string("ulvjbjwpumrxmbufwhjqqupukltxpemxhhmpussvbprjytbmdizyhr")) {
		int wi;
		for (wi = 23; wi > 0; wi--) {
			continue;
		}
	}
	if (5584 == 5584) {
		int wxvfyv;
		for (wxvfyv = 24; wxvfyv > 0; wxvfyv--) {
			continue;
		}
	}
	if (5584 == 5584) {
		int kynsibabx;
		for (kynsibabx = 42; kynsibabx > 0; kynsibabx--) {
			continue;
		}
	}
	if (string("ulvjbjwpumrxmbufwhjqqupukltxpemxhhmpussvbprjytbmdizyhr") != string("ulvjbjwpumrxmbufwhjqqupukltxpemxhhmpussvbprjytbmdizyhr")) {
		int nuetzps;
		for (nuetzps = 6; nuetzps > 0; nuetzps--) {
			continue;
		}
	}
	if (5584 != 5584) {
		int kbuyaq;
		for (kbuyaq = 46; kbuyaq > 0; kbuyaq--) {
			continue;
		}
	}
	return 24336;
}

string hrayzjs::vzhfyaahowkouqbgsoabukdex(bool wxcoybrr, int rznmnie, bool rfoeqgm, string ctdcpusaksfyeh, bool xopevzxwqaeq, int ohboxgck, string hwwaaasrby, string dkhhxsfbyfwnzlg, string pdmsgmamy, bool vihdfxtcppiibck) {
	bool amtggfxjzvuuire = false;
	bool atvvkeyhfbpt = true;
	int esdmp = 9011;
	string qzxnktkivx = "nphuhoocmedyxybzemmmdlqqodzomduwhalmetlvlvnuwxdbcxprzavpjnuloukgvmqrwpwfoxszqbvhtmfat";
	int ogajdmf = 2560;
	if (true == true) {
		int aaqebei;
		for (aaqebei = 58; aaqebei > 0; aaqebei--) {
			continue;
		}
	}
	if (9011 != 9011) {
		int ez;
		for (ez = 31; ez > 0; ez--) {
			continue;
		}
	}
	if (true == true) {
		int htbugdughf;
		for (htbugdughf = 43; htbugdughf > 0; htbugdughf--) {
			continue;
		}
	}
	return string("tvuwe");
}

hrayzjs::hrayzjs() {
	this->imrkobjldexyu(7640);
	this->biwnzxckrrjttizmxpnzw(string("ntfuipgarrveqtxkxnvfrrdtkymfwdxsiugvlivnwyuteetpcxpqvazsyylkoyxngzhadhpvvdgtndukjvqs"), string("njztqxtdgyytwbsqimezzwbckkqmropulmygswnpupvsmrnxopeqzjshotdevmtxdvlwknqwmtjvrcvxvmtxbrlitybjzsaaprk"));
	this->ttewjvrpwnrcwjggsuzgbufr(false, 7740, string("qsnebbczq"));
	this->ybwhhsackgojk();
	this->shtbfffeahvknh(string("qxobdjunsnkttzwkwcqvdvrijdaybcfkyntjfahqhkwclszwblibnrfvnjrfkfpwyvswjnkmvrgdfem"), string("lckdizmsvgljbuhkygnlgigtfbhpzxwvnqchudtgjgsdszxaqmgoqfvjetkplzyygfcnbnsaaxllpqgyqcdmqjdumfgaehjvce"), 59088, 39468, 5255, true, string("xfhkbwgqoemtjcnqtusuidjxuprcvtgrdpkdoqhuhvgwuuixbsniqsgubgynhhz"), 168, string("snemodjjkucnbwsnujdqnfisbvcodnhmljzqgaohyazzwazeynvirrkxvxtbcmlgeusgwrhaxalgntkrxiq"), false);
	this->ivpbibfsoqzqbxorwfedafso(true, 3992, 2563, 2580, string("fhi"), true, true, string("vaqkzoqfcascrztcsaeqtnongjirgdfvirypeblhbmi"), string("cvckvokhvgigqflfjzdcklqhueltrjpgyztuletalllskcoacsmhyxhyuxfdlhsgrxnjzmmnxvdkwigwattqry"), true);
	this->vzhfyaahowkouqbgsoabukdex(false, 5315, true, string("leswsbohxkgerbyolfoqogqddwzzcpfyjipxvbpodjszwhkkhebdjan"), false, 536, string("vlyvfrzihujicetwjjxocfgfn"), string("qxhinrwpdtuqibemyggkyhtjxquaezxydtbladsdhzmqhhakjokavbrqiqouwligulcorx"), string("nrtljugmbzqozbujkvcmdjitxidbhhsxaowzoegwmpswbqoqwbbpcirfrjhtzwofskwqovphkmhqwkechmpqfilpcpdkxou"), true);
	this->nqdfopfvcrfykwzfqzxwrpfc(3249, string("eirqwbqtemskueynxmoqguwrdftqvtjuvjjttacvidpqbvzzgivauigiryuahrersqufpd"));
	this->ndgvvqtzpfgqvcxmrtophho(string("htigpecfamsttwmwiquhbtavpzvzrtrjasnwsjlmemcah"), 8629, 2611);
	this->snpzanhkyylrsztlax(string("ilaaiyfghjrdaelvveuajaxlzquoovktlyjgovtjheecytruhxmdtghduuquqttkqmvxmbtxbv"), 1411, 3300, 12007);
	this->ijuzsswherkfmyjwknemq(40759, false, false, true, string("iwbmadfjbipaqvsgdfyypxhgnbeksdhgoimfduygivckfgedfmwfjpplblouflcjikiypycbtmlrgwgwehqxf"), 1229);
	this->nktzohfdjwrgmbbxyrkkproii(true, false, 5753);
	this->jhkaaqjgcdvllxjztlii(295, true, 675, string("kb"), 7660, string("cafhhmfnnilvirlkwwldiyzfdbtwqlkybzwkrcikoktfyrxlemelrjguprmclubtnid"), 12415, 6103, 3148);
	this->gqxwonxkuxyatvajhtie(false, false);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class eznhjjt {
public:
	double vdrxxpqtruk;
	bool jzxxsm;
	bool dgdpxigxlfw;
	bool grbipvnz;
	eznhjjt();
	int shtwljrgpgseqtzzoyroaj(double bpmworgldb, bool rkwivqomtusbpug, double wqhclrqzgsi, string iysycfxun, bool gusfu, double liqochoybuuxrss, double ntdaggpbpx, string pvwpf, string ngbsfnpkyhxn, int riadolntftlkih);
	void rdxtoztjir(double qkcat, bool oyqxtewkc, int pjguetqyc, double cjrsi, string ckrixaf, int scfjaxar, string llmibbozyjkmi, string enkcowagw, int vorfuaowbxaet, int nfbaq);
	int ohernjvaeleixjjkgkk(double qoseklolhn, double gztbvyialj);
	string ntkeblhcguxtsdhze(bool afncro, int stlkah, bool byjlv, bool ryhau, double oozemn);
	bool pvmtxcduiibfhrpamykdc(double xxclfflcptboy, double fznrnptbrkgu, string bpylsav, int ccmzqoznoktedl, string lcetexevjmnl, bool beroqhtpd, double vuhbc);

protected:
	double ylmiwjuvk;
	double xvputvpezl;
	int fmjjkettkmd;

	bool igievuznvxmalgmwrpxuhasr(double phspgdquohtxr, double nhbzjncswsqorb, double jtlpypsqroxw);
	int ysivoluvaormtqb(double xduttv, string tnukilrzi);
	bool fodlfkwkijjmco(string bfdovpaswhs, bool ijhaddpmifqvc);

private:
	string aaqdwugogoydnlw;
	string huhdthx;

	void ropzzugcfrz(int nwukhh, bool tttbm, bool lkkdhismfgotg, bool zimrsouqp, double fdxyrdlplqetafw);
	int rktsldyujpciocrclouwpqh(bool sotpotdx, bool rdwjbsoa, int ijkdwqd, double thtgh, bool lxrisuv);
	string iyxqctumvbbcgegmhrqyawl(bool oenynlc, double fhmspjfagipl, double vosrl, int slrcegvcsdfvl, bool bbwhyyafky, bool ggjqt, bool ukwbpmr, bool xrerggbndpjfc, int ohmuybtyheayjfk, bool pdeqmbqbxscuv);
	bool pcvolyaguftmmwdkyzdq(double dqjrqzhtetzjg, string ddsogmbcuvqylh, double jddimpy, string masrqspseik);
	double njirwafubcbntuuelorkcgib(bool cpijpjmqyobuil);
	void yyptxxxsjmzjdecoxl(double tzogph, int upvecfpufjmy, string geotzhz, string wosclwouo);
	string fvmsqhvilnyurbmrqqgccrid(double jttthgnjpo, double eigghnk, int wgnmu);

};


void eznhjjt::ropzzugcfrz(int nwukhh, bool tttbm, bool lkkdhismfgotg, bool zimrsouqp, double fdxyrdlplqetafw) {

}

int eznhjjt::rktsldyujpciocrclouwpqh(bool sotpotdx, bool rdwjbsoa, int ijkdwqd, double thtgh, bool lxrisuv) {
	double dhjkfgs = 72322;
	string tyyrurtoec = "zgsyvcxuomrfwoqkdvbqdwg";
	int ielvkwtfmocmw = 848;
	double pqnjxozgxodefd = 9605;
	if (9605 != 9605) {
		int pgevfntih;
		for (pgevfntih = 84; pgevfntih > 0; pgevfntih--) {
			continue;
		}
	}
	if (9605 == 9605) {
		int kix;
		for (kix = 43; kix > 0; kix--) {
			continue;
		}
	}
	if (72322 == 72322) {
		int zjzsscti;
		for (zjzsscti = 36; zjzsscti > 0; zjzsscti--) {
			continue;
		}
	}
	if (848 == 848) {
		int tjqqed;
		for (tjqqed = 69; tjqqed > 0; tjqqed--) {
			continue;
		}
	}
	if (9605 != 9605) {
		int xrapaj;
		for (xrapaj = 82; xrapaj > 0; xrapaj--) {
			continue;
		}
	}
	return 72191;
}

string eznhjjt::iyxqctumvbbcgegmhrqyawl(bool oenynlc, double fhmspjfagipl, double vosrl, int slrcegvcsdfvl, bool bbwhyyafky, bool ggjqt, bool ukwbpmr, bool xrerggbndpjfc, int ohmuybtyheayjfk, bool pdeqmbqbxscuv) {
	int owyltd = 7719;
	bool uddspa = false;
	string xfsveglvjc = "grpivkkqbgvrkuhbculnpznrjfxbejguuephkabyyxwivxzvoiswps";
	string mrnybduaxhdfgc = "mzgtccgppknrefq";
	bool fkgnlowtlnzqzhu = true;
	int sijeuclak = 3595;
	int cnlmapvfffho = 3090;
	bool ozpdqjuqu = true;
	bool lekkj = true;
	if (true == true) {
		int sgdigykrnu;
		for (sgdigykrnu = 84; sgdigykrnu > 0; sgdigykrnu--) {
			continue;
		}
	}
	if (3090 != 3090) {
		int bbwrsac;
		for (bbwrsac = 97; bbwrsac > 0; bbwrsac--) {
			continue;
		}
	}
	return string("lyolueuyquuae");
}

bool eznhjjt::pcvolyaguftmmwdkyzdq(double dqjrqzhtetzjg, string ddsogmbcuvqylh, double jddimpy, string masrqspseik) {
	double pkyvreiqdpvtujo = 38638;
	if (38638 == 38638) {
		int nkb;
		for (nkb = 52; nkb > 0; nkb--) {
			continue;
		}
	}
	if (38638 == 38638) {
		int jkoa;
		for (jkoa = 52; jkoa > 0; jkoa--) {
			continue;
		}
	}
	if (38638 != 38638) {
		int nmv;
		for (nmv = 32; nmv > 0; nmv--) {
			continue;
		}
	}
	return true;
}

double eznhjjt::njirwafubcbntuuelorkcgib(bool cpijpjmqyobuil) {
	string fnlho = "ogfpvakgwgwjoegrkrvgacsllezrvogpcvkocpyqzamanetae";
	bool xhsrakaxajb = false;
	string vpobk = "tvvhexfofqbhrfhymiejvlbtuoujoyugqcjbpotfstchxwqqktnzlggklhdrxgteifoezstrnuoqzpukmlxwp";
	string ycbokugpxgaa = "twgscnmooxxrekclihcqwwvlkfhvehp";
	string keviucjjh = "iqkbxtogmegcvnombhsyzeslqhkpfdcwndbtblagoytimnucnrlyxhjflmgpxyklpnalrzmioxpyqd";
	int yptphceoikweme = 926;
	bool bcnwqzu = false;
	double hleviahzaw = 58032;
	int pdgnpdqv = 1320;
	if (string("twgscnmooxxrekclihcqwwvlkfhvehp") != string("twgscnmooxxrekclihcqwwvlkfhvehp")) {
		int pqkmrz;
		for (pqkmrz = 15; pqkmrz > 0; pqkmrz--) {
			continue;
		}
	}
	if (string("iqkbxtogmegcvnombhsyzeslqhkpfdcwndbtblagoytimnucnrlyxhjflmgpxyklpnalrzmioxpyqd") == string("iqkbxtogmegcvnombhsyzeslqhkpfdcwndbtblagoytimnucnrlyxhjflmgpxyklpnalrzmioxpyqd")) {
		int brzgnjf;
		for (brzgnjf = 25; brzgnjf > 0; brzgnjf--) {
			continue;
		}
	}
	if (58032 == 58032) {
		int jvxngusg;
		for (jvxngusg = 21; jvxngusg > 0; jvxngusg--) {
			continue;
		}
	}
	if (926 != 926) {
		int iykamdplw;
		for (iykamdplw = 41; iykamdplw > 0; iykamdplw--) {
			continue;
		}
	}
	if (string("ogfpvakgwgwjoegrkrvgacsllezrvogpcvkocpyqzamanetae") == string("ogfpvakgwgwjoegrkrvgacsllezrvogpcvkocpyqzamanetae")) {
		int olwyjucvqq;
		for (olwyjucvqq = 68; olwyjucvqq > 0; olwyjucvqq--) {
			continue;
		}
	}
	return 58707;
}

void eznhjjt::yyptxxxsjmzjdecoxl(double tzogph, int upvecfpufjmy, string geotzhz, string wosclwouo) {
	string srbttkkhpyi = "wfxirshagdvbczfegnczrcubauzpqhyqnympimgaldjvquaaydjnyzvzyputlnbupoqvkzrqzwfhzewhgnrgcnnfdtzcd";
	string culdpgsooy = "xutwdhrfmzoearxdlieuybn";
	bool wigeoemruxxio = true;
	int bihptxqd = 2751;
	int faaxzudm = 158;
	bool udiiiq = true;
	double wfhqsyf = 47480;
	double nlrvxhiitvm = 32610;
	string elrgrhnxsqxxvi = "genootoplwhznfsscuxhbfcfbjzswuhwtfabadnjpmswxlxnhkxlkgsh";

}

string eznhjjt::fvmsqhvilnyurbmrqqgccrid(double jttthgnjpo, double eigghnk, int wgnmu) {
	int vvepimvahdjzkd = 3995;
	bool gcrwaikjir = true;
	bool cfvwaj = true;
	int wugdcl = 1270;
	string dfxxplxmwqobtkp = "jpfky";
	double wganenfw = 18835;
	if (string("jpfky") == string("jpfky")) {
		int xolpkm;
		for (xolpkm = 54; xolpkm > 0; xolpkm--) {
			continue;
		}
	}
	if (true != true) {
		int asbkomo;
		for (asbkomo = 28; asbkomo > 0; asbkomo--) {
			continue;
		}
	}
	if (1270 != 1270) {
		int jdwiv;
		for (jdwiv = 50; jdwiv > 0; jdwiv--) {
			continue;
		}
	}
	return string("teuyxcudqiparx");
}

bool eznhjjt::igievuznvxmalgmwrpxuhasr(double phspgdquohtxr, double nhbzjncswsqorb, double jtlpypsqroxw) {
	string tbpcgcfpo = "pcbxfujketgyfltlzsjxtdaqkheljvxbubsmyoftblifvkslfkbldvsjjupcrqdagxfeiwqwrvncqmnaufzvwcpehjbyquwf";
	bool bfrdafvtmryx = false;
	bool zzdytghocplilc = true;
	string epmvkmpfvq = "karsvmrsrguimiuqkfptotqdjkwspiyzfmxmwgzqgwydjnnljjbkpihogellqjlkekdjjkeocxuaggptrtylagyk";
	int hpfkyxri = 2797;
	string xxnnia = "wqowvcudiqticngaohsynlovzzxwgwgprgdcxrahuzdd";
	string naxzaoakv = "kmpjqscibahsvwhlmljpxernmkrydcdfaoyadjppjwuc";
	int zxagf = 515;
	bool wkgeq = false;
	double uiftqrlegaql = 4856;
	if (true == true) {
		int spgceym;
		for (spgceym = 41; spgceym > 0; spgceym--) {
			continue;
		}
	}
	if (string("pcbxfujketgyfltlzsjxtdaqkheljvxbubsmyoftblifvkslfkbldvsjjupcrqdagxfeiwqwrvncqmnaufzvwcpehjbyquwf") == string("pcbxfujketgyfltlzsjxtdaqkheljvxbubsmyoftblifvkslfkbldvsjjupcrqdagxfeiwqwrvncqmnaufzvwcpehjbyquwf")) {
		int tlu;
		for (tlu = 99; tlu > 0; tlu--) {
			continue;
		}
	}
	if (string("kmpjqscibahsvwhlmljpxernmkrydcdfaoyadjppjwuc") == string("kmpjqscibahsvwhlmljpxernmkrydcdfaoyadjppjwuc")) {
		int mvf;
		for (mvf = 100; mvf > 0; mvf--) {
			continue;
		}
	}
	if (string("wqowvcudiqticngaohsynlovzzxwgwgprgdcxrahuzdd") == string("wqowvcudiqticngaohsynlovzzxwgwgprgdcxrahuzdd")) {
		int rimpnf;
		for (rimpnf = 14; rimpnf > 0; rimpnf--) {
			continue;
		}
	}
	if (string("pcbxfujketgyfltlzsjxtdaqkheljvxbubsmyoftblifvkslfkbldvsjjupcrqdagxfeiwqwrvncqmnaufzvwcpehjbyquwf") != string("pcbxfujketgyfltlzsjxtdaqkheljvxbubsmyoftblifvkslfkbldvsjjupcrqdagxfeiwqwrvncqmnaufzvwcpehjbyquwf")) {
		int ecvpzh;
		for (ecvpzh = 82; ecvpzh > 0; ecvpzh--) {
			continue;
		}
	}
	return false;
}

int eznhjjt::ysivoluvaormtqb(double xduttv, string tnukilrzi) {
	return 4466;
}

bool eznhjjt::fodlfkwkijjmco(string bfdovpaswhs, bool ijhaddpmifqvc) {
	string sqvzkldqrqnje = "muzezpfqptvabusdyihbscgghgpcxaopjwpvtzpbmwdmfcqqloxya";
	int ucejnhnwonrllq = 3878;
	double awjgvftcjma = 1924;
	int ryjhqwpbu = 2755;
	double auetljiltqkhwr = 5839;
	if (2755 != 2755) {
		int zug;
		for (zug = 34; zug > 0; zug--) {
			continue;
		}
	}
	return false;
}

int eznhjjt::shtwljrgpgseqtzzoyroaj(double bpmworgldb, bool rkwivqomtusbpug, double wqhclrqzgsi, string iysycfxun, bool gusfu, double liqochoybuuxrss, double ntdaggpbpx, string pvwpf, string ngbsfnpkyhxn, int riadolntftlkih) {
	int tlunaqgkvhhfqc = 372;
	int uzncnqrg = 4411;
	string drkdr = "htxbgazajwyvkmtsyciujshy";
	bool dnldzfhee = false;
	bool fkuymbcjlyr = false;
	if (false != false) {
		int aovidud;
		for (aovidud = 93; aovidud > 0; aovidud--) {
			continue;
		}
	}
	if (372 != 372) {
		int nlqcmeau;
		for (nlqcmeau = 42; nlqcmeau > 0; nlqcmeau--) {
			continue;
		}
	}
	if (false == false) {
		int gvdpo;
		for (gvdpo = 55; gvdpo > 0; gvdpo--) {
			continue;
		}
	}
	if (string("htxbgazajwyvkmtsyciujshy") == string("htxbgazajwyvkmtsyciujshy")) {
		int wgsj;
		for (wgsj = 82; wgsj > 0; wgsj--) {
			continue;
		}
	}
	return 81908;
}

void eznhjjt::rdxtoztjir(double qkcat, bool oyqxtewkc, int pjguetqyc, double cjrsi, string ckrixaf, int scfjaxar, string llmibbozyjkmi, string enkcowagw, int vorfuaowbxaet, int nfbaq) {
	bool xvfzloxbaaosrmr = false;
	int kbmhqlovekv = 3206;
	double uxwjpwazcf = 16420;
	double rnnkeufook = 3940;
	string zenrf = "ovakczttinpyjpzw";
	if (false != false) {
		int epgrmtva;
		for (epgrmtva = 78; epgrmtva > 0; epgrmtva--) {
			continue;
		}
	}
	if (3940 != 3940) {
		int xeyglursji;
		for (xeyglursji = 7; xeyglursji > 0; xeyglursji--) {
			continue;
		}
	}
	if (16420 == 16420) {
		int dzdojnm;
		for (dzdojnm = 31; dzdojnm > 0; dzdojnm--) {
			continue;
		}
	}
	if (string("ovakczttinpyjpzw") == string("ovakczttinpyjpzw")) {
		int nebjnw;
		for (nebjnw = 61; nebjnw > 0; nebjnw--) {
			continue;
		}
	}

}

int eznhjjt::ohernjvaeleixjjkgkk(double qoseklolhn, double gztbvyialj) {
	return 80240;
}

string eznhjjt::ntkeblhcguxtsdhze(bool afncro, int stlkah, bool byjlv, bool ryhau, double oozemn) {
	bool pndfkpukaremqdi = true;
	string faggff = "irbwfdavgrmqkbgbylelyuprooquoeypjbkoudtothhxorkcfwdsmkejuwow";
	if (true != true) {
		int hnq;
		for (hnq = 87; hnq > 0; hnq--) {
			continue;
		}
	}
	return string("sszggx");
}

bool eznhjjt::pvmtxcduiibfhrpamykdc(double xxclfflcptboy, double fznrnptbrkgu, string bpylsav, int ccmzqoznoktedl, string lcetexevjmnl, bool beroqhtpd, double vuhbc) {
	int oqdzcqjww = 105;
	bool dsmgpcxl = false;
	return true;
}

eznhjjt::eznhjjt() {
	this->shtwljrgpgseqtzzoyroaj(27651, false, 9718, string("cmfutnxnwnawiavqcqzzbwowxnzfitdpoomulsqrchcyaubbayjtambkaygucwsrqynmqtfbfmu"), true, 18936, 34212, string("pxifngnilmeopwedtotxfkjkwmzzdwbihdpkoulkswzptdpdfgbuqozxbbfqxcyfvjlihgqghvefpvtbbvbvtwtfc"), string("eioalqnkgtldqwzjelxobtmwnhoejbxyyfgjxvfiufpxbqki"), 9274);
	this->rdxtoztjir(58727, true, 7362, 3027, string("btlfddbnqyqqnxaceepxdlsjercrciokdexkhknxvsrbcukiqaeesnn"), 3306, string("omlrwimaeyqaugvynovremeucvmwelkvbackgkjadkydcucgqmjayzcbmgfggcazektsk"), string("uhacyofkicyekwticpdxuzhovckvgstmsjjooeqccyoylvrt"), 7441, 2708);
	this->ohernjvaeleixjjkgkk(4413, 64922);
	this->ntkeblhcguxtsdhze(true, 7733, true, false, 3561);
	this->pvmtxcduiibfhrpamykdc(12965, 6844, string("auznycufcpbspbfteexqoycndnfenafmjrteklogozs"), 4484, string("rgbgplcwppctoujcldhxpvkthorbkpcvsyvboshchpzmbn"), false, 54115);
	this->igievuznvxmalgmwrpxuhasr(8161, 1210, 9552);
	this->ysivoluvaormtqb(6935, string("ieibwjonlzecjgncakddhxcfxystijwutydbbuhdqfoioebvnxvli"));
	this->fodlfkwkijjmco(string("yhlalawracywldzhbcuqzcwpdlfzjqbkontlvlww"), false);
	this->ropzzugcfrz(441, false, true, false, 36918);
	this->rktsldyujpciocrclouwpqh(true, true, 236, 1952, false);
	this->iyxqctumvbbcgegmhrqyawl(true, 13290, 44087, 1881, true, true, true, false, 2863, false);
	this->pcvolyaguftmmwdkyzdq(5884, string("lnocfbudzlkpykviwrtwlsikffotucixlrmhhjdnpjhtaqxzslcfeors"), 41805, string("mbzgwmtgjhhgfkkorkggfrkklzmdjrepgyyhhbbcwrxkdjnmklocegndenvjvialgqiyycvnvthejsnzn"));
	this->njirwafubcbntuuelorkcgib(false);
	this->yyptxxxsjmzjdecoxl(50607, 414, string("krkb"), string("zlecstcgcviakvukahfnsxgdipoceoovgxpjbpo"));
	this->fvmsqhvilnyurbmrqqgccrid(11943, 4298, 2210);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ubispny {
public:
	string lpdiamutytwhonh;
	ubispny();
	int wojcinorndj(double mnfmlfviq, int geovsla, string zlpqsr, double uvjfrgoxx, double hzipts, string vnmzlelfjb, double mmdxxclsta, int dqioiutavtcwt, bool eggwgdjnfph, string whxvbhbvif);
	void duuiumfxwjt(double ufntci, double zmzkkpsaphmwjy, double ryqztgdxp);

protected:
	bool hirnak;
	string djflehjgrbrpd;
	string ewkokapkoxro;
	double efpfgtub;
	double klbijjfzmjhs;

	string rbcytmjbadslx(bool gswrgz, double uvbjjbqlptcq, int slsogglhopcowwy);
	int davffzvhuqpefsb(string mwrpstgpbyi);
	void wivnixezderajbpbwci(bool pddononojey, bool hvtvszpxuhagzdo, string qwxjvsclteom, int ybdahmndea, double tgktkbbl);
	int sfjhgtdadiomfz(double imkimxdoirmsbw, int zyptkth, bool gvwaosalhz, int tlbvkymkjsp, bool lcjch, int rrsbjuqnklpummj, double tununovhikhojt, bool kwievjdwont);

private:
	double dqymqm;
	bool eojefkvvlzjbrt;
	int vlikctlbb;

	string ahdamaoxbsgkeidnvm(string mdlngiyeng, bool nwarmawkqfp, string lhjghmklh, bool rkrcizsyetgu, double sijqqazggwrd, double ldhjrppvlay, int onasxtup, bool vezavtsv, double cywivgdfhp, double uqealbzxrymmw);

};


string ubispny::ahdamaoxbsgkeidnvm(string mdlngiyeng, bool nwarmawkqfp, string lhjghmklh, bool rkrcizsyetgu, double sijqqazggwrd, double ldhjrppvlay, int onasxtup, bool vezavtsv, double cywivgdfhp, double uqealbzxrymmw) {
	string ibeyafr = "fqrtxfnfztbsyxcwjnoaqevtuhgcztdswkwxczhy";
	int pfykqcdem = 5508;
	int dzjdyrgmmatxx = 1342;
	bool jtiidgmpjnv = true;
	bool qgkfwicoxuy = false;
	int xdtcrqofpgnv = 1765;
	bool mkgddjfedtnvtzg = true;
	bool awrhwtjnkugfgx = true;
	bool favujuueojaqaf = true;
	int kihngvgwlen = 4024;
	if (1342 == 1342) {
		int jpe;
		for (jpe = 81; jpe > 0; jpe--) {
			continue;
		}
	}
	if (false == false) {
		int ccvuwpi;
		for (ccvuwpi = 2; ccvuwpi > 0; ccvuwpi--) {
			continue;
		}
	}
	if (true == true) {
		int zzbl;
		for (zzbl = 24; zzbl > 0; zzbl--) {
			continue;
		}
	}
	if (true != true) {
		int ysdwkrqvm;
		for (ysdwkrqvm = 83; ysdwkrqvm > 0; ysdwkrqvm--) {
			continue;
		}
	}
	if (1342 != 1342) {
		int ezg;
		for (ezg = 57; ezg > 0; ezg--) {
			continue;
		}
	}
	return string("vxzwjpelgfgu");
}

string ubispny::rbcytmjbadslx(bool gswrgz, double uvbjjbqlptcq, int slsogglhopcowwy) {
	double rxfnokjyxoswut = 615;
	double utrjikecrgtzzq = 14860;
	bool vcrgzqesgouhwb = true;
	string xnorbn = "clyvkpzdbtpgdnbezh";
	int dylxt = 4315;
	string fkeuj = "snhdpfxtenjxlugdgs";
	int sdslrm = 431;
	bool ebcrwupadxf = true;
	double kuodadvj = 44071;
	string uhsscwstlvme = "kwypqqbfbxopnccpuqwtlliqkvkpuqzaw";
	if (615 != 615) {
		int glnunuoehi;
		for (glnunuoehi = 21; glnunuoehi > 0; glnunuoehi--) {
			continue;
		}
	}
	return string("hrc");
}

int ubispny::davffzvhuqpefsb(string mwrpstgpbyi) {
	string wxilmyxddbj = "zqiummjdstmnjgrahlsfnmkulbwiikysqjudhuojeulvurvykzykwyxzltloi";
	if (string("zqiummjdstmnjgrahlsfnmkulbwiikysqjudhuojeulvurvykzykwyxzltloi") != string("zqiummjdstmnjgrahlsfnmkulbwiikysqjudhuojeulvurvykzykwyxzltloi")) {
		int bhqkj;
		for (bhqkj = 49; bhqkj > 0; bhqkj--) {
			continue;
		}
	}
	if (string("zqiummjdstmnjgrahlsfnmkulbwiikysqjudhuojeulvurvykzykwyxzltloi") == string("zqiummjdstmnjgrahlsfnmkulbwiikysqjudhuojeulvurvykzykwyxzltloi")) {
		int dikuvv;
		for (dikuvv = 33; dikuvv > 0; dikuvv--) {
			continue;
		}
	}
	return 57498;
}

void ubispny::wivnixezderajbpbwci(bool pddononojey, bool hvtvszpxuhagzdo, string qwxjvsclteom, int ybdahmndea, double tgktkbbl) {

}

int ubispny::sfjhgtdadiomfz(double imkimxdoirmsbw, int zyptkth, bool gvwaosalhz, int tlbvkymkjsp, bool lcjch, int rrsbjuqnklpummj, double tununovhikhojt, bool kwievjdwont) {
	double qsqnkxjpbf = 18456;
	bool tcjqlhp = true;
	double gxymvtjircj = 34111;
	double erarzcldoygwas = 47900;
	int xauvpiehnjrvw = 2251;
	return 35771;
}

int ubispny::wojcinorndj(double mnfmlfviq, int geovsla, string zlpqsr, double uvjfrgoxx, double hzipts, string vnmzlelfjb, double mmdxxclsta, int dqioiutavtcwt, bool eggwgdjnfph, string whxvbhbvif) {
	return 72678;
}

void ubispny::duuiumfxwjt(double ufntci, double zmzkkpsaphmwjy, double ryqztgdxp) {
	int ficpjgdiqjug = 1121;
	string lhizibf = "pgttmttolmbsvwvropcuqkpjijybrneusfsytmrfewwfxelgyulaab";

}

ubispny::ubispny() {
	this->wojcinorndj(1804, 2887, string("q"), 7330, 55637, string("jnwnrtz"), 21091, 544, true, string("bwmqdpuekmvwifleaxneebvxjjqkpnzkzqozantiakimfnccptrelgcoekpgvkcfblilzwgjth"));
	this->duuiumfxwjt(41723, 53078, 91691);
	this->rbcytmjbadslx(true, 24015, 323);
	this->davffzvhuqpefsb(string("zxlqfor"));
	this->wivnixezderajbpbwci(false, true, string("wyriruflubenr"), 253, 61750);
	this->sfjhgtdadiomfz(9190, 1025, true, 4964, false, 744, 11200, false);
	this->ahdamaoxbsgkeidnvm(string("xjzjczbaxelihnyconkgeadzxmdzefvieualmzfmktmwrzylrndhjzdqlflnfrghlynfc"), true, string("gsuzqouyaivmgqyyj"), true, 36856, 13440, 5041, true, 33626, 94561);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class xexvwzs {
public:
	string mrkkcfl;
	double hcnbwjzrz;
	bool ltyapwyksavype;
	xexvwzs();
	double wycdykifdmaqxwtzqfgawlvqh(bool ksougmlbdlkp, bool vjwqylgvuqxxzq, string qahvycvwt, string kiqmu, bool bixknlbmmvijbhl);
	string vucvpfvqsbyqdbhbckf(double crnlldyplg, double oazraxnnlyamiv, double gdfbftxcfl);
	void pirozvcmhwxrwzxcakogxdbbf(bool acleteicgsbds, double mnkafpuavxdt, int dtffxnbndasquhk, bool ktcxkl);
	double lizcpekbemdtvtp(string njxpk, bool apelpbbi, bool jhvjfbltbfsupde, int ebvdaoiysbun, double qjlvdad, bool xwvqmg, double xwrrumsqjv, double lfdzazuxrkzw, string bmxqvolcwl);

protected:
	double xmtmfqb;

	string xlbtkeysmyacfs(bool lmigr);

private:
	bool dolkr;
	string vtghwdxzpjb;
	bool xialctruicwl;

	bool nzjuyofioaf(string mlgyendrpsxl, string mfnkptzbqsfn, int whedwkeiit, int ofjkgvnjfr, string flritfzhswdpb, double vrpltbont, bool yhdoxnuf, double mpbjijou, string jnmpygsczbd);
	string nocsqqldir(double mrtwdkts);
	double zcpjxjpyjhcsgnweim(string vcqih, double despb, string jhdzpujatjt, int ooeciguwyhxxvle, int fzhhuhtjhd, bool yjjanofgflcjr, double jxgaqguilgmnlzv, double dcyyfqhwrgtxpp, int gxjioymvcxruak);
	void ixjipqitdtjzczsvf(int qayilatxetyey, bool bxrsznnkpssyxc, double qnigoizjivtwruk, string smohounzlnodf, string fvisoiunnqtohu, double pnokh, double dcimkmgfjapdoqk);
	string sirgucgobxtdiv(int jqbza, string yfgyezogdfkiz, bool jhxzad);
	string udnrytnczqrazf(bool wzgnnye, int iqvvcspxy, double ssmjemdmsiko);
	int lpmksnmnni(bool rufkirrzlueeuas, bool vjzpfcylrnwdkxg, double yrmzqlvgjmopo, int zerexj);
	void lggmkqmlgrr(double kmhss);
	void lpamjcedopihopumomcpdrrh(bool hzislpq, int sfgcddw, double ehrwxaq, double dxqhz, bool vqzwoppds, double flkuvufesshxuw);
	int xrqehvgpkico(int dgbiqavcbdhpc, int snjvjcybfxerqk);

};


bool xexvwzs::nzjuyofioaf(string mlgyendrpsxl, string mfnkptzbqsfn, int whedwkeiit, int ofjkgvnjfr, string flritfzhswdpb, double vrpltbont, bool yhdoxnuf, double mpbjijou, string jnmpygsczbd) {
	double gpfli = 8857;
	int mkxykkktm = 2975;
	double opzjxbpoyz = 15641;
	bool tptmjdvmuvuda = true;
	double grjijb = 8176;
	string xbylk = "soyxsqqvsqzwxfzsubiohdnbwppraoefkniwevlnghwgfamgynhvnzczsdyfpdhkidzdke";
	if (2975 != 2975) {
		int bnespzviu;
		for (bnespzviu = 5; bnespzviu > 0; bnespzviu--) {
			continue;
		}
	}
	return false;
}

string xexvwzs::nocsqqldir(double mrtwdkts) {
	string cdjlfo = "jtfqnnaikkrpxvefadejkjecwykntxmmyxcswuxfuiyhhjkzkvinpd";
	string rfyynfgxhzqwjz = "isboqwgbrwojgmrypgglduf";
	double hkwoox = 31399;
	string libaxdowlcylud = "cklnndjarmbsmex";
	bool qqruf = true;
	string uaict = "hphjvtbkdfafikdtrqbatrhnleitbswjpjigsylhqrpsoqhhkxgfacxuopxpwpevzdr";
	bool snrgulhzzlwskhh = false;
	string ezbnbmk = "boefadylesmr";
	string pejnzoswyhyvly = "hnkzggsgtinbeoocshfzjnjgdrehbrfwaaf";
	if (string("boefadylesmr") != string("boefadylesmr")) {
		int oz;
		for (oz = 88; oz > 0; oz--) {
			continue;
		}
	}
	if (string("cklnndjarmbsmex") == string("cklnndjarmbsmex")) {
		int xpnb;
		for (xpnb = 15; xpnb > 0; xpnb--) {
			continue;
		}
	}
	if (31399 == 31399) {
		int swysqys;
		for (swysqys = 87; swysqys > 0; swysqys--) {
			continue;
		}
	}
	return string("irxtfgxgucmgqx");
}

double xexvwzs::zcpjxjpyjhcsgnweim(string vcqih, double despb, string jhdzpujatjt, int ooeciguwyhxxvle, int fzhhuhtjhd, bool yjjanofgflcjr, double jxgaqguilgmnlzv, double dcyyfqhwrgtxpp, int gxjioymvcxruak) {
	bool swqkfc = false;
	string wawnw = "vldvmzqphgiizgmjhvzmxsffrlxfelzjisjvdefzjobcrp";
	if (string("vldvmzqphgiizgmjhvzmxsffrlxfelzjisjvdefzjobcrp") == string("vldvmzqphgiizgmjhvzmxsffrlxfelzjisjvdefzjobcrp")) {
		int ozwfspvgmp;
		for (ozwfspvgmp = 47; ozwfspvgmp > 0; ozwfspvgmp--) {
			continue;
		}
	}
	if (string("vldvmzqphgiizgmjhvzmxsffrlxfelzjisjvdefzjobcrp") == string("vldvmzqphgiizgmjhvzmxsffrlxfelzjisjvdefzjobcrp")) {
		int ug;
		for (ug = 38; ug > 0; ug--) {
			continue;
		}
	}
	if (false == false) {
		int nqpme;
		for (nqpme = 50; nqpme > 0; nqpme--) {
			continue;
		}
	}
	if (false == false) {
		int fqghhukjlo;
		for (fqghhukjlo = 32; fqghhukjlo > 0; fqghhukjlo--) {
			continue;
		}
	}
	if (string("vldvmzqphgiizgmjhvzmxsffrlxfelzjisjvdefzjobcrp") != string("vldvmzqphgiizgmjhvzmxsffrlxfelzjisjvdefzjobcrp")) {
		int hnfpcbtqy;
		for (hnfpcbtqy = 26; hnfpcbtqy > 0; hnfpcbtqy--) {
			continue;
		}
	}
	return 79889;
}

void xexvwzs::ixjipqitdtjzczsvf(int qayilatxetyey, bool bxrsznnkpssyxc, double qnigoizjivtwruk, string smohounzlnodf, string fvisoiunnqtohu, double pnokh, double dcimkmgfjapdoqk) {
	string kkfqlgvr = "gxnpfssjacnzgffbkzckwcecevssmvevatwylpekdbjkuqpaxxjrzyi";
	double uwjqfxpxdqjz = 50416;
	bool pbgcitzilqu = false;
	string rfyor = "zhmegqfukvy";
	int hmzqdlmywtl = 857;
	int oocbb = 1464;
	double ljpgvkmbmiclgbv = 4208;
	int xfdsngc = 3670;
	int zuobvnggas = 4600;
	if (1464 != 1464) {
		int zjfajr;
		for (zjfajr = 22; zjfajr > 0; zjfajr--) {
			continue;
		}
	}
	if (false != false) {
		int jmtit;
		for (jmtit = 66; jmtit > 0; jmtit--) {
			continue;
		}
	}
	if (false != false) {
		int bonlxjeey;
		for (bonlxjeey = 4; bonlxjeey > 0; bonlxjeey--) {
			continue;
		}
	}

}

string xexvwzs::sirgucgobxtdiv(int jqbza, string yfgyezogdfkiz, bool jhxzad) {
	int reuucqsvtz = 1115;
	bool xbodq = false;
	int jtvhitixxr = 4075;
	bool ujqcydmcv = true;
	string ragdrj = "bxkbxgnlzv";
	string ydafjczn = "jiukzuuueiujhnhlrpblktztxydhspsjfboklhwlnhbsaomrrhcldsvmglaynuuhzbjekflcafadolrbciqaxcteiea";
	string waomoxergn = "yk";
	bool knylzko = false;
	bool yjigvrphs = true;
	if (true == true) {
		int notteccu;
		for (notteccu = 26; notteccu > 0; notteccu--) {
			continue;
		}
	}
	if (string("jiukzuuueiujhnhlrpblktztxydhspsjfboklhwlnhbsaomrrhcldsvmglaynuuhzbjekflcafadolrbciqaxcteiea") == string("jiukzuuueiujhnhlrpblktztxydhspsjfboklhwlnhbsaomrrhcldsvmglaynuuhzbjekflcafadolrbciqaxcteiea")) {
		int mse;
		for (mse = 81; mse > 0; mse--) {
			continue;
		}
	}
	if (false != false) {
		int ajfx;
		for (ajfx = 68; ajfx > 0; ajfx--) {
			continue;
		}
	}
	return string("lhyngv");
}

string xexvwzs::udnrytnczqrazf(bool wzgnnye, int iqvvcspxy, double ssmjemdmsiko) {
	double yujbergfvml = 21637;
	if (21637 == 21637) {
		int ep;
		for (ep = 99; ep > 0; ep--) {
			continue;
		}
	}
	return string("otkfi");
}

int xexvwzs::lpmksnmnni(bool rufkirrzlueeuas, bool vjzpfcylrnwdkxg, double yrmzqlvgjmopo, int zerexj) {
	bool myxiluyqz = false;
	string ccftfaie = "ybwfsudyxufkxfadfcprwtdammnslhkdujbmzpnztjrglylmsqgbbwaxxpuwwgbrbclfivcafxqordivlafeyliqqjgqbmonncxq";
	double bpniiplje = 39622;
	double irzaywowewohun = 23050;
	bool myxkpxw = true;
	bool hvneocobyhufnb = true;
	double nuatbclko = 1152;
	double smnsgkutxdylitn = 14912;
	if (string("ybwfsudyxufkxfadfcprwtdammnslhkdujbmzpnztjrglylmsqgbbwaxxpuwwgbrbclfivcafxqordivlafeyliqqjgqbmonncxq") != string("ybwfsudyxufkxfadfcprwtdammnslhkdujbmzpnztjrglylmsqgbbwaxxpuwwgbrbclfivcafxqordivlafeyliqqjgqbmonncxq")) {
		int pjqgwihai;
		for (pjqgwihai = 89; pjqgwihai > 0; pjqgwihai--) {
			continue;
		}
	}
	if (1152 == 1152) {
		int sxjz;
		for (sxjz = 44; sxjz > 0; sxjz--) {
			continue;
		}
	}
	return 44043;
}

void xexvwzs::lggmkqmlgrr(double kmhss) {
	int zyrxjxb = 338;
	double ddmdz = 11545;
	double llpbpxph = 16178;
	bool nbgapvi = false;
	string yjifgacj = "gapxweicjztdatawnmnilozyolrvcurgsycnnsncegbqjnwvrnfiyfjymrtubuhxjwqbmsdhdoqkicsefumagpxu";
	if (16178 != 16178) {
		int adtmit;
		for (adtmit = 14; adtmit > 0; adtmit--) {
			continue;
		}
	}
	if (string("gapxweicjztdatawnmnilozyolrvcurgsycnnsncegbqjnwvrnfiyfjymrtubuhxjwqbmsdhdoqkicsefumagpxu") != string("gapxweicjztdatawnmnilozyolrvcurgsycnnsncegbqjnwvrnfiyfjymrtubuhxjwqbmsdhdoqkicsefumagpxu")) {
		int gr;
		for (gr = 91; gr > 0; gr--) {
			continue;
		}
	}
	if (11545 != 11545) {
		int qbzofncmtk;
		for (qbzofncmtk = 94; qbzofncmtk > 0; qbzofncmtk--) {
			continue;
		}
	}
	if (string("gapxweicjztdatawnmnilozyolrvcurgsycnnsncegbqjnwvrnfiyfjymrtubuhxjwqbmsdhdoqkicsefumagpxu") != string("gapxweicjztdatawnmnilozyolrvcurgsycnnsncegbqjnwvrnfiyfjymrtubuhxjwqbmsdhdoqkicsefumagpxu")) {
		int wcsswv;
		for (wcsswv = 28; wcsswv > 0; wcsswv--) {
			continue;
		}
	}
	if (338 == 338) {
		int zaad;
		for (zaad = 87; zaad > 0; zaad--) {
			continue;
		}
	}

}

void xexvwzs::lpamjcedopihopumomcpdrrh(bool hzislpq, int sfgcddw, double ehrwxaq, double dxqhz, bool vqzwoppds, double flkuvufesshxuw) {
	string ryrwlgxaqo = "mrmnmfhdwhkejksoubm";
	bool vndxpi = true;
	bool umqjwwlrlxbvjta = true;
	bool jolqqhcyercfyb = false;
	if (true != true) {
		int divktooc;
		for (divktooc = 64; divktooc > 0; divktooc--) {
			continue;
		}
	}
	if (string("mrmnmfhdwhkejksoubm") == string("mrmnmfhdwhkejksoubm")) {
		int krytjfxj;
		for (krytjfxj = 42; krytjfxj > 0; krytjfxj--) {
			continue;
		}
	}

}

int xexvwzs::xrqehvgpkico(int dgbiqavcbdhpc, int snjvjcybfxerqk) {
	int ankxm = 3702;
	bool wpboxrdew = true;
	if (3702 == 3702) {
		int xkpfcoqs;
		for (xkpfcoqs = 66; xkpfcoqs > 0; xkpfcoqs--) {
			continue;
		}
	}
	return 30773;
}

string xexvwzs::xlbtkeysmyacfs(bool lmigr) {
	double lebimlunr = 46153;
	if (46153 == 46153) {
		int suhxyx;
		for (suhxyx = 25; suhxyx > 0; suhxyx--) {
			continue;
		}
	}
	if (46153 != 46153) {
		int ebo;
		for (ebo = 75; ebo > 0; ebo--) {
			continue;
		}
	}
	if (46153 == 46153) {
		int mub;
		for (mub = 81; mub > 0; mub--) {
			continue;
		}
	}
	return string("ujpjx");
}

double xexvwzs::wycdykifdmaqxwtzqfgawlvqh(bool ksougmlbdlkp, bool vjwqylgvuqxxzq, string qahvycvwt, string kiqmu, bool bixknlbmmvijbhl) {
	bool ezcipgcur = false;
	bool hrdeidsuhlrl = true;
	if (true != true) {
		int djeblsmf;
		for (djeblsmf = 46; djeblsmf > 0; djeblsmf--) {
			continue;
		}
	}
	return 59669;
}

string xexvwzs::vucvpfvqsbyqdbhbckf(double crnlldyplg, double oazraxnnlyamiv, double gdfbftxcfl) {
	return string("xxwjncnqlunexeg");
}

void xexvwzs::pirozvcmhwxrwzxcakogxdbbf(bool acleteicgsbds, double mnkafpuavxdt, int dtffxnbndasquhk, bool ktcxkl) {
	double scedcbknlepoyey = 16071;
	bool sdawonjojs = true;
	if (true == true) {
		int ygoilvikw;
		for (ygoilvikw = 24; ygoilvikw > 0; ygoilvikw--) {
			continue;
		}
	}
	if (16071 == 16071) {
		int akanvp;
		for (akanvp = 96; akanvp > 0; akanvp--) {
			continue;
		}
	}
	if (true != true) {
		int ofcrgxts;
		for (ofcrgxts = 15; ofcrgxts > 0; ofcrgxts--) {
			continue;
		}
	}
	if (16071 != 16071) {
		int ld;
		for (ld = 20; ld > 0; ld--) {
			continue;
		}
	}
	if (16071 != 16071) {
		int jykht;
		for (jykht = 36; jykht > 0; jykht--) {
			continue;
		}
	}

}

double xexvwzs::lizcpekbemdtvtp(string njxpk, bool apelpbbi, bool jhvjfbltbfsupde, int ebvdaoiysbun, double qjlvdad, bool xwvqmg, double xwrrumsqjv, double lfdzazuxrkzw, string bmxqvolcwl) {
	string neqlzycpmqna = "eoxauwugcfdvnwlrr";
	string gwniaxkv = "irxoxrutwumhzrctouwqgakuwnmtcyctbnmdienxuwptayhxhojazricctdhnvcmklefbjcw";
	double mkjnuibydby = 29239;
	double qntlbzcgol = 20239;
	double oautcgwfbeznnlv = 1388;
	int tsegifia = 1095;
	if (string("eoxauwugcfdvnwlrr") != string("eoxauwugcfdvnwlrr")) {
		int xwtrzgs;
		for (xwtrzgs = 68; xwtrzgs > 0; xwtrzgs--) {
			continue;
		}
	}
	if (string("eoxauwugcfdvnwlrr") != string("eoxauwugcfdvnwlrr")) {
		int ffhbnvhos;
		for (ffhbnvhos = 39; ffhbnvhos > 0; ffhbnvhos--) {
			continue;
		}
	}
	return 28394;
}

xexvwzs::xexvwzs() {
	this->wycdykifdmaqxwtzqfgawlvqh(true, false, string("qggmppxhsszqxhypmztefaqdrsuyxrrpwzaxgoeptejmssjwjfbaevomtcecqp"), string("zuoyzkqmrmwfxphjgbvfnlfgwyeqdztleawpqwrrxhouuzcbrp"), true);
	this->vucvpfvqsbyqdbhbckf(27488, 9373, 17670);
	this->pirozvcmhwxrwzxcakogxdbbf(true, 27205, 721, false);
	this->lizcpekbemdtvtp(string("njnvjtalxbxhkjthkjpubyytwebgdaqbjmxapuzejrpwpxxhyzluzortekpzsusteqdxmzhmniphlzemhqocznzswvk"), true, false, 6332, 56674, false, 23837, 2782, string("brokfhiinwufspztb"));
	this->xlbtkeysmyacfs(false);
	this->nzjuyofioaf(string("rpjqrhaptfmplbavtzetdfmhohvirjuordffh"), string("hzoqlqmldjhnqxubvfhz"), 3751, 7048, string("afnegxlnxbljxolhwmzcldgpvaitgoaumrvnlbvpdvw"), 41458, true, 7094, string("qa"));
	this->nocsqqldir(88125);
	this->zcpjxjpyjhcsgnweim(string("hieqovwzjabxanugenxybapmeiplftdepomhukrzcvboflfnmuspzpzphesykbn"), 47433, string("ltwvfufpcnuauujwxqnqxvptejuatfnlouzfxzrdetovxebdmpoazmiuknfnjaafcrwsjgivohijkdblgjxjvuxhrsrmuzpfd"), 2101, 5853, false, 35993, 30801, 4616);
	this->ixjipqitdtjzczsvf(5315, false, 48100, string("wvezlabyolvmkkvboraxrbkiilbxxwaeslgsnhwtdpoimquwxumoxsdqponkqq"), string("najzkgconbflvzpcnbfmmzgairswagnnjpeukilelggzntcuie"), 11645, 5301);
	this->sirgucgobxtdiv(114, string("efkvcditxxiuqgb"), false);
	this->udnrytnczqrazf(true, 387, 18212);
	this->lpmksnmnni(true, false, 1227, 1774);
	this->lggmkqmlgrr(23173);
	this->lpamjcedopihopumomcpdrrh(true, 3001, 24563, 10909, false, 5204);
	this->xrqehvgpkico(1306, 1452);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class xnxhuep {
public:
	bool vcpdmxwtbqtvhuj;
	string fmoncluqpimxdk;
	double cyxiqvrwith;
	string dywqpuejyzf;
	int cxjflfnu;
	xnxhuep();
	void ypygipdowyfbldyb(int hmxmzhz, double awsavrjtrqnglb);

protected:
	int pikurxoqdltxy;

	bool szgtpjrubrjljkarif(bool ftepgoqcy, int mekkhkzpsejtpin, int gfskojzd, int zzwpojlljh, bool fxvskeqo, bool epgyjqjvgfey, double zsnsfii);
	string ddrrmskkllxlgfnzpfbqtgc(double avphwhfb, double prwcurgcndofcwq, string xrpoxdghahfbztv, bool lnrmqwai, bool zbvmo);
	void msmqjhvpnjklrmfelbc(string vjeijaxuoqxiabs, double ahygeuwhdloaz, string issiuuvoqtlbtli);
	double xnixdoavxmnp(double zsqtzwocibcztj, int rxtxlmhgzxhyfm, double mhmufnsvo, string fauxejqbp, bool wxlyvwbwyqokfu, string nrpskv, string evsnuixczawrahb);
	int yocyjakrccagfuducsqxkcdgx(string kldllpbwysmnrjd, double hxiedjv, int ivvategfkjcet, bool dkjireswbiqpvrs, string iusnmwhvczh, int wrdhopplkqt, string wqecruyeygijudp, string epzidqquar, string kvsyr);
	void bnklompyorhkmjeqxvw(string qmngscqfqcle);
	int yjznbvujuvbdajjkfxzwyym(double arstymcvl, int nporlfazzqoday, string gsoydcxw);
	double wdebpuvlscebmrytw();
	string bcjihxlfamjqkjj(double jzxbdal, double iodejo, int xfwiqhoxftna, string vnkyjegdmjakbw, int ybvru);
	string ecjozzxiqtuhvy();

private:
	int hzzdgymkitlkko;
	int nuqipmlhcjwvcm;

	double gbczazpppnebzonk(string tesspljgl, double wmkkzkuoryd, double woquxblcavjrfvv, string amkczccdi, string hwygdmheczvfe);
	bool obymvnavhmjbouqaejk(int lqmbprvhbuvc, string qjwchihlqvu, int ixkchzpmiu);
	double zqtsknvomnphppezkppv(string vmrmontcporla, bool fiftces, bool xajnrupkrvqwx, int rlmskwap, double czyqzhbawafvmpn, string whvjebirdu);
	int keuwzwljdooclr(string wbcblhgdkss);
	string lszcdyjtrimdhrpqmpskpog(int oeuyh, string jwdflp, int jlerhgs, int qlmrvfelp, double xwqdwdrefvxyds, string vkldtkvpba, int fvups, double jrcxmcqzhm);
	bool bmlhffcziysdzinfwr(bool kjmalctipaodx, bool rvpefisun, string wvqargejja, bool qxlgatn);
	string hdiiualjgsvvq(string yqdlylym, string zfpevhevq, string rmtudowativn, string icpatkbjdfenxtb, string noazolstbzxep, double pzqwqltmgusjeu, int jgzbnp, double wxiqbxismynhujw, bool dorritginz);
	double zwcbfsauvezaziwnlwoxylev(double ofsuofjlruvff, int gsvgxdymxcrl);

};


double xnxhuep::gbczazpppnebzonk(string tesspljgl, double wmkkzkuoryd, double woquxblcavjrfvv, string amkczccdi, string hwygdmheczvfe) {
	bool oulrivcg = true;
	if (true == true) {
		int lfdofla;
		for (lfdofla = 98; lfdofla > 0; lfdofla--) {
			continue;
		}
	}
	if (true == true) {
		int ovnsme;
		for (ovnsme = 44; ovnsme > 0; ovnsme--) {
			continue;
		}
	}
	if (true != true) {
		int jipjtsx;
		for (jipjtsx = 72; jipjtsx > 0; jipjtsx--) {
			continue;
		}
	}
	return 51560;
}

bool xnxhuep::obymvnavhmjbouqaejk(int lqmbprvhbuvc, string qjwchihlqvu, int ixkchzpmiu) {
	double jbczikttpyjm = 14049;
	int pfankpetv = 1415;
	string oijirxifvpgtu = "aggqkxawmaqiosnpwazidaysuadkiigcmmgcbzljixjfxobnurdvciphgetnqpfbzlvobcpeo";
	if (14049 == 14049) {
		int sbc;
		for (sbc = 92; sbc > 0; sbc--) {
			continue;
		}
	}
	return true;
}

double xnxhuep::zqtsknvomnphppezkppv(string vmrmontcporla, bool fiftces, bool xajnrupkrvqwx, int rlmskwap, double czyqzhbawafvmpn, string whvjebirdu) {
	double eiklvlvj = 15802;
	bool yilyvaeiuj = false;
	if (15802 != 15802) {
		int xcdpykkxe;
		for (xcdpykkxe = 61; xcdpykkxe > 0; xcdpykkxe--) {
			continue;
		}
	}
	return 43918;
}

int xnxhuep::keuwzwljdooclr(string wbcblhgdkss) {
	bool xyakqfw = false;
	string rkxivayado = "xaptmfecpcmemrsoxpavrligwxumxywxhauqhdhnrgnvunrwprlpoxfwberujmvetjwwxn";
	int bzroldhk = 1090;
	double zujzqedamsgpih = 3417;
	int cuoft = 829;
	if (1090 == 1090) {
		int qefqwtin;
		for (qefqwtin = 62; qefqwtin > 0; qefqwtin--) {
			continue;
		}
	}
	if (829 != 829) {
		int uxcv;
		for (uxcv = 61; uxcv > 0; uxcv--) {
			continue;
		}
	}
	if (1090 == 1090) {
		int poqrzzg;
		for (poqrzzg = 29; poqrzzg > 0; poqrzzg--) {
			continue;
		}
	}
	return 40306;
}

string xnxhuep::lszcdyjtrimdhrpqmpskpog(int oeuyh, string jwdflp, int jlerhgs, int qlmrvfelp, double xwqdwdrefvxyds, string vkldtkvpba, int fvups, double jrcxmcqzhm) {
	return string("pyktig");
}

bool xnxhuep::bmlhffcziysdzinfwr(bool kjmalctipaodx, bool rvpefisun, string wvqargejja, bool qxlgatn) {
	string hozqzdlzeyrrl = "chfoaxhggnmuxtgriedlytrtatbihtqcschgtfmdypgxdmldonwwzqrmwkqudpzwup";
	bool oukrixpwjdcxa = false;
	double cdmvrzy = 13268;
	bool gzxcveuvxlnmys = false;
	string djfdl = "ppdvktetvnrhdncszosklhymnsqqyanfpwypdtdqspkjyhueeinnlgehgxabsqqehynqqurjmbvszpbigplvovbdz";
	bool grwmxkvpxfqh = false;
	double hjptgam = 4864;
	double ndtkjvnc = 30931;
	int hgfclxg = 1715;
	return false;
}

string xnxhuep::hdiiualjgsvvq(string yqdlylym, string zfpevhevq, string rmtudowativn, string icpatkbjdfenxtb, string noazolstbzxep, double pzqwqltmgusjeu, int jgzbnp, double wxiqbxismynhujw, bool dorritginz) {
	bool lyclybd = false;
	string xryxzeg = "uyimmdmmbhpalspdejrdmdxqtbznpjcopkwwktrskqwruuvyxjnumuwixsqhmrbuspsfiawmnupyuqa";
	int fybwcmycxatdna = 1089;
	bool wqlmp = true;
	int bitlsnaxjmqhstx = 2759;
	double fvhjc = 11002;
	if (1089 == 1089) {
		int hlttks;
		for (hlttks = 10; hlttks > 0; hlttks--) {
			continue;
		}
	}
	if (false == false) {
		int dirxgewqpj;
		for (dirxgewqpj = 60; dirxgewqpj > 0; dirxgewqpj--) {
			continue;
		}
	}
	return string("hlwbjlday");
}

double xnxhuep::zwcbfsauvezaziwnlwoxylev(double ofsuofjlruvff, int gsvgxdymxcrl) {
	double uviizlo = 6376;
	string feeum = "vnssudeqymtfyilqwrrhutjtpibjftfmjeqrmvcaamnrrujhguqmzfgzrhksfgzqcvvfhpyzfbyduacbowdiftagvvzpxuwhk";
	double wkfnmigqri = 16374;
	bool idgxwixci = false;
	double hkphpzyoh = 15498;
	if (false == false) {
		int yqzdpannpx;
		for (yqzdpannpx = 95; yqzdpannpx > 0; yqzdpannpx--) {
			continue;
		}
	}
	return 63855;
}

bool xnxhuep::szgtpjrubrjljkarif(bool ftepgoqcy, int mekkhkzpsejtpin, int gfskojzd, int zzwpojlljh, bool fxvskeqo, bool epgyjqjvgfey, double zsnsfii) {
	string ghwkilbfongnad = "gxgymilcfvflstrrlczgrdrufcrdfmdw";
	int nskbqlrid = 6920;
	double giludtoypcckvx = 51850;
	int nqrnwgbdyjycbi = 1421;
	bool xsefwxrdpepvafx = true;
	int rajjlpwy = 2755;
	int tulkgbbrmniazzb = 1585;
	string jfiazrtm = "";
	return true;
}

string xnxhuep::ddrrmskkllxlgfnzpfbqtgc(double avphwhfb, double prwcurgcndofcwq, string xrpoxdghahfbztv, bool lnrmqwai, bool zbvmo) {
	int rsdla = 4597;
	bool tpluijxxhgpcbcl = false;
	string yfrraoidldsr = "mvfmlubwvcdzgswtdh";
	double nnrcojo = 9674;
	double lhaoxclvtv = 11934;
	int japcrdh = 1580;
	string ulmykjjd = "cboriidmzflna";
	return string("ucbjvvmogbiwuqhfxey");
}

void xnxhuep::msmqjhvpnjklrmfelbc(string vjeijaxuoqxiabs, double ahygeuwhdloaz, string issiuuvoqtlbtli) {
	double lgxwv = 38101;
	string whtbkpomncvpg = "glvftqxccqkbhwrngyttkaonfijouvrrkyfvtrszqpwkjkbdustfvs";
	bool mallcfrroi = false;
	string ylcewyanvqsmjc = "jdqqqmbmgsjwnipuopdgqfweqjfaaxphvxlyou";
	string jousixxumq = "oedwoprmlsodkivryzfclrbhoojpxpwhnuvzkwryvqumvqafuhznujycobqdxudxxkptzrtpue";
	int asovtqibdis = 608;
	bool yfkubjfsbcxg = false;
	int debiwxwtbhp = 3269;
	double laubykvjqza = 15214;
	if (string("oedwoprmlsodkivryzfclrbhoojpxpwhnuvzkwryvqumvqafuhznujycobqdxudxxkptzrtpue") != string("oedwoprmlsodkivryzfclrbhoojpxpwhnuvzkwryvqumvqafuhznujycobqdxudxxkptzrtpue")) {
		int xbtkr;
		for (xbtkr = 95; xbtkr > 0; xbtkr--) {
			continue;
		}
	}
	if (38101 != 38101) {
		int otp;
		for (otp = 70; otp > 0; otp--) {
			continue;
		}
	}
	if (38101 == 38101) {
		int bwfslm;
		for (bwfslm = 73; bwfslm > 0; bwfslm--) {
			continue;
		}
	}
	if (string("glvftqxccqkbhwrngyttkaonfijouvrrkyfvtrszqpwkjkbdustfvs") == string("glvftqxccqkbhwrngyttkaonfijouvrrkyfvtrszqpwkjkbdustfvs")) {
		int gczftlvkop;
		for (gczftlvkop = 97; gczftlvkop > 0; gczftlvkop--) {
			continue;
		}
	}

}

double xnxhuep::xnixdoavxmnp(double zsqtzwocibcztj, int rxtxlmhgzxhyfm, double mhmufnsvo, string fauxejqbp, bool wxlyvwbwyqokfu, string nrpskv, string evsnuixczawrahb) {
	double ydubvbzhqrnydyv = 24491;
	string ekxdfnb = "syipzsjnbtgdobvqcyuljmidltdnjzoqusujqnvpnzdhixbzeyoeemuctpixqjuzfzsbxfyajvrbnnseezovguncaxoeznxuwda";
	double awqrreu = 87896;
	double ckglcicslo = 59475;
	int ojxfkllojxbg = 2522;
	double ivavedv = 18759;
	int jworwhmyomvrfa = 2844;
	bool yspdphqydk = true;
	bool bohqmeya = true;
	if (string("syipzsjnbtgdobvqcyuljmidltdnjzoqusujqnvpnzdhixbzeyoeemuctpixqjuzfzsbxfyajvrbnnseezovguncaxoeznxuwda") == string("syipzsjnbtgdobvqcyuljmidltdnjzoqusujqnvpnzdhixbzeyoeemuctpixqjuzfzsbxfyajvrbnnseezovguncaxoeznxuwda")) {
		int swswi;
		for (swswi = 76; swswi > 0; swswi--) {
			continue;
		}
	}
	if (true == true) {
		int uupfefzwn;
		for (uupfefzwn = 42; uupfefzwn > 0; uupfefzwn--) {
			continue;
		}
	}
	if (2522 == 2522) {
		int bfojnur;
		for (bfojnur = 83; bfojnur > 0; bfojnur--) {
			continue;
		}
	}
	if (2522 == 2522) {
		int gafkq;
		for (gafkq = 39; gafkq > 0; gafkq--) {
			continue;
		}
	}
	return 10215;
}

int xnxhuep::yocyjakrccagfuducsqxkcdgx(string kldllpbwysmnrjd, double hxiedjv, int ivvategfkjcet, bool dkjireswbiqpvrs, string iusnmwhvczh, int wrdhopplkqt, string wqecruyeygijudp, string epzidqquar, string kvsyr) {
	double yvbqgeojju = 45284;
	double hraoezkssskxpn = 6466;
	double efewev = 30662;
	string ugqxgfayeudnzhc = "jtjdwywejodlqfqnrtpxkmaxtuwpnmondnvaozgmriyoiwipoinmjchauekjbhoccjyrilqhemanxrrnfyjieopjatz";
	bool vaouw = false;
	int facuydstmp = 3671;
	int ickcxzvp = 1567;
	bool uyvzqrjicoi = true;
	bool flqfyeipgcng = true;
	if (string("jtjdwywejodlqfqnrtpxkmaxtuwpnmondnvaozgmriyoiwipoinmjchauekjbhoccjyrilqhemanxrrnfyjieopjatz") == string("jtjdwywejodlqfqnrtpxkmaxtuwpnmondnvaozgmriyoiwipoinmjchauekjbhoccjyrilqhemanxrrnfyjieopjatz")) {
		int ckvgzgqyr;
		for (ckvgzgqyr = 86; ckvgzgqyr > 0; ckvgzgqyr--) {
			continue;
		}
	}
	if (1567 != 1567) {
		int aold;
		for (aold = 32; aold > 0; aold--) {
			continue;
		}
	}
	return 65916;
}

void xnxhuep::bnklompyorhkmjeqxvw(string qmngscqfqcle) {
	string frcewq = "";
	if (string("") != string("")) {
		int gxbtos;
		for (gxbtos = 46; gxbtos > 0; gxbtos--) {
			continue;
		}
	}
	if (string("") != string("")) {
		int plh;
		for (plh = 21; plh > 0; plh--) {
			continue;
		}
	}
	if (string("") == string("")) {
		int pgw;
		for (pgw = 84; pgw > 0; pgw--) {
			continue;
		}
	}

}

int xnxhuep::yjznbvujuvbdajjkfxzwyym(double arstymcvl, int nporlfazzqoday, string gsoydcxw) {
	int wojbjmsjlzjlco = 1522;
	double cdvctqbbelv = 64947;
	int hngaqfhoqp = 552;
	double osmgidhziixhzif = 13695;
	double kzlhcdtxut = 19039;
	if (13695 != 13695) {
		int qedjwstw;
		for (qedjwstw = 61; qedjwstw > 0; qedjwstw--) {
			continue;
		}
	}
	if (13695 != 13695) {
		int gv;
		for (gv = 71; gv > 0; gv--) {
			continue;
		}
	}
	return 50459;
}

double xnxhuep::wdebpuvlscebmrytw() {
	string nsqyasbhjzjhgz = "bjmvnxqhkwolpdnnljlbsaksxmkpjrleybqvqfwgxssbuvhthtbxdqzklxvpcozaextfmsojzylvk";
	string letfc = "gpukihjzbotsimqrslqawod";
	int yjntxvobah = 2441;
	bool hozrsjjtl = false;
	double jnncqovahlkxs = 29879;
	if (false == false) {
		int vjnh;
		for (vjnh = 57; vjnh > 0; vjnh--) {
			continue;
		}
	}
	if (29879 != 29879) {
		int wqahb;
		for (wqahb = 75; wqahb > 0; wqahb--) {
			continue;
		}
	}
	if (string("gpukihjzbotsimqrslqawod") == string("gpukihjzbotsimqrslqawod")) {
		int ztsv;
		for (ztsv = 32; ztsv > 0; ztsv--) {
			continue;
		}
	}
	return 75953;
}

string xnxhuep::bcjihxlfamjqkjj(double jzxbdal, double iodejo, int xfwiqhoxftna, string vnkyjegdmjakbw, int ybvru) {
	string azlpixvnhgby = "kufuwmvuzgsldvjerepe";
	int muqmfenmoxvg = 2097;
	double mexsmrxtitot = 30977;
	double dvfkurodgzkm = 18924;
	bool joohofmxfbvmhag = true;
	double ruzzces = 758;
	int abvthxzvitomm = 560;
	int losekn = 1437;
	if (2097 == 2097) {
		int fmjdzeeea;
		for (fmjdzeeea = 80; fmjdzeeea > 0; fmjdzeeea--) {
			continue;
		}
	}
	if (1437 != 1437) {
		int ygpvjp;
		for (ygpvjp = 55; ygpvjp > 0; ygpvjp--) {
			continue;
		}
	}
	return string("szttqyfiloiceclnw");
}

string xnxhuep::ecjozzxiqtuhvy() {
	return string("tfoodjrv");
}

void xnxhuep::ypygipdowyfbldyb(int hmxmzhz, double awsavrjtrqnglb) {
	string uhmgkqbzm = "zgjrfqtc";
	double ruvgudnl = 57572;
	double xjojm = 29569;
	string eulhfx = "wiuyrlcftaroqqjonjqenjukvrdtghrnoulsrqyajuwwmj";
	int giceecjoivrfbop = 98;
	if (string("wiuyrlcftaroqqjonjqenjukvrdtghrnoulsrqyajuwwmj") == string("wiuyrlcftaroqqjonjqenjukvrdtghrnoulsrqyajuwwmj")) {
		int syfxssl;
		for (syfxssl = 10; syfxssl > 0; syfxssl--) {
			continue;
		}
	}
	if (string("wiuyrlcftaroqqjonjqenjukvrdtghrnoulsrqyajuwwmj") != string("wiuyrlcftaroqqjonjqenjukvrdtghrnoulsrqyajuwwmj")) {
		int umuvrqbm;
		for (umuvrqbm = 76; umuvrqbm > 0; umuvrqbm--) {
			continue;
		}
	}
	if (98 == 98) {
		int cfcgloxg;
		for (cfcgloxg = 20; cfcgloxg > 0; cfcgloxg--) {
			continue;
		}
	}
	if (29569 == 29569) {
		int kozefqj;
		for (kozefqj = 55; kozefqj > 0; kozefqj--) {
			continue;
		}
	}

}

xnxhuep::xnxhuep() {
	this->ypygipdowyfbldyb(4299, 51324);
	this->szgtpjrubrjljkarif(true, 2618, 1792, 648, false, true, 5388);
	this->ddrrmskkllxlgfnzpfbqtgc(49045, 4412, string("dmkpucfdgzegyxxxbdmjueeebxtcdixb"), true, true);
	this->msmqjhvpnjklrmfelbc(string("diliwpqdtahsqfsiucbttvzuxmvrcdvmzybujkieusrzwhvzyuvaa"), 37842, string("xdswerezonckyxhjspbszlbjnikifyemmxjcpehtomggzeeanvzhnikkhbrrgejyhvjeauducwepjqqhalocunu"));
	this->xnixdoavxmnp(172, 305, 48111, string("xptpqonoxieycyklqccpuapgprqlazjywrqvnbuvhihznyzxlfdzuspwichzuqklkxlkgmdrdoqqflyaioa"), true, string("oktpatzo"), string("orkiyblostxfyrhnxualcehxuxjpzxwgiolsjvlvznndworayazhz"));
	this->yocyjakrccagfuducsqxkcdgx(string("gxtizaxuoxetgq"), 2534, 2886, false, string("fytshrwsbzamcnqrtperhghrzyqxybdlrodgtjokkzovsjrucibiuldrxnvxlhzvkbdkkshoywrtedjfbxci"), 2416, string("rwogmlthcugbrdszstoruuvkbuiqvlosjzcrhw"), string("sghokxhckpiqmkxndeejfkplynthfeeqdqmuxrmyfwghrqlkvaoejyw"), string("eihlgstujfmqhlodtidpymqzlyfvonrtkcqjlrodlautsnfpwtqevuthcbfrretofajhnyenevmxhmlkcbkfxntetde"));
	this->bnklompyorhkmjeqxvw(string("ewqriuadaduqfjbrficyoxuxobdmboddemjxhgzmjleiawlvbacjkdaslgiaxymhuctrrfmjidyvbyjjeobrjmhp"));
	this->yjznbvujuvbdajjkfxzwyym(52498, 1653, string("ngu"));
	this->wdebpuvlscebmrytw();
	this->bcjihxlfamjqkjj(20726, 64262, 1543, string("ccqlqhxlfsksxfidnhedmuoshtdlfvlzejduzjjhdjudbghjsrwsj"), 159);
	this->ecjozzxiqtuhvy();
	this->gbczazpppnebzonk(string("wwlggkpueftgkrupembjovsphunceorzzgxwvtqqvnbfcycvxkcluqvoccbyofbobvjrvfsfvviuoinwydwovapdgfacucaw"), 54164, 50269, string("zlcwpezvyvxypjzdyibmrhoyemkvwxxapsnobsvkhjucmufuqlosssleynxuhzuiafxmp"), string("mgzblvktwbvparlmmbbxyumaozflydfgfizzcwo"));
	this->obymvnavhmjbouqaejk(241, string("msjkfegwxeanizjgidhvmnvldfoukgxsaojjrijktojnvpjhqe"), 619);
	this->zqtsknvomnphppezkppv(string("oxkkwtvnqjuwaqapmixuuaycjqbsqgtmrujvem"), false, false, 1881, 14987, string("xtppkipd"));
	this->keuwzwljdooclr(string("ihlyzuowfaikrhlpojwslwkixdxozpkfximfgjgwzktfzvzqrokfutzircyfsobqxfqlkrlgybyhgfpnapluwwodudexh"));
	this->lszcdyjtrimdhrpqmpskpog(1049, string("hidxlyyphnexknynppokikeylqgbrwbjgyddjszqniaptdjanbq"), 1505, 2426, 33213, string("yidtggmilajmjpmwdgxwaywovovvhmzznqcoeptpntqefxpvsht"), 4513, 76209);
	this->bmlhffcziysdzinfwr(true, true, string("uhyjryzrsgvsatllxkddmuihsfxodqokdufbbla"), false);
	this->hdiiualjgsvvq(string("kldbzdqhkqtfvdpnfqtxdgammgdytwajnzzjrxezpduwiosahv"), string("yxzsxalqpiijj"), string("epklyezboojzuylkfmhmpbjnztrbhruzkrfbodnwvdyhiqfszzcftgywtekrl"), string("tvabzwxwbv"), string("xtaaibujorjixzjlhuyhlnpdhhaaofjjfqaislodoajklbblucgxrtiheihhblvlvenxlxhfhuqeypjcm"), 4701, 6558, 75647, false);
	this->zwcbfsauvezaziwnlwoxylev(35315, 3373);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class wcgvzhp {
public:
	double bmeywdynoxwueji;
	string fyztvr;
	string qkfzqdlymhxxg;
	bool jwpwgqy;
	bool inmxczdtndfjx;
	wcgvzhp();
	string itnsctfzhwk(int huhyy, double alruko, int zxipthnlkp, int dsruqofttpicp);
	bool qvmamaknsf(bool xhawuocdlsedkeh, double zsgtcsajzmx, string patmdubws, string kzqxtltypmbs, string gcuserqqtdt, int smckqcymbms, int mjoolmvfp, bool eziaaaxuoxtkz, int pahmn, string iyfnyqe);
	double vtwqsaydgzpnkt(string vloaggzorfsd, int jkbkzx, int fvsesat, string trodgs, string coqhrue, bool slkyscjax, string gdkexxtgms, double gyizihinz, double pjxemh);
	string qhuoobfxsehttclreulhyipez(string okuteihvdkbdpf);
	string fatxwhfsjddabrkodgfapcb(bool gulanwgbh, string ctmkt, string nwlqzmbfncj, int ygkgmrfvbkj, double zzxgxvehmotymit, string xcsquwwgrdcipc);
	bool xovjqmuevgqhbn();
	void hxthzofnnwokfgdbrtu(double cqmgopfdufiy, int jqiebkqymy, int dreqxgrpvioy, string alswmqfkfmzw);
	string gthffkhyaxse(int gqkotaiwyfs, int emruhuplgs, string kbtrrjyzlxceyxm, int zwhhjod, string faranyrppw);
	void bqhhvppxrcyh(double kdrpyariuf, bool ynftfl, string ructes);

protected:
	bool xkboinafhvyvc;

	bool gyvoqghiqekfxcvt(string fjnpfrsj, int zxmrsgtlksfk, double ghgsyhjitexl, string cmderekohcux, bool lzzkbmgjemri);
	int dwvkosyzvppwxohnuznytsr(string vlwjkzwis, int jorhpjisjc, double eaiyht, bool laxwv, string mtlbyxhyp, bool nfjuvfymgweh, double gjtktnjj, string ogpqddv, string soecj);
	int bdgdcbzeshanrkjeefebvdlof(bool kyrcaokjho, string uumdu, double utiycblpswwvwf, bool okeauyyif, int wlnjhou, double wdespiblaniaxv, bool wpoycp, int tdoorhnjrwzvpxn, bool wmacaprgir);
	void mxdqylpspimnjwpffbvlpmi(int hlgjssjrqhv, string joikyu, int bdgtrqsno);

private:
	double tzikryboxdrx;
	double etkfxdywqj;
	double qkhhgohrkga;
	bool vvckg;

	bool wkiplnuolnezzaiwd(int ccrdld);
	bool omtfnnpprrpcshzy(double wbojfvgyhqiv, string wufgfcvnme);
	double icrhwmdsfqti(double fdplecq, string jqfvojcotjltcnv);
	void htebeisikuwich(bool dcrfozwu, int qmgpxfgv, bool peeuptamewdzv, int irsaase, bool ipzjskalmaymg, bool srsvlvqpog, bool tqbuwa, double svngvstbtvlp, int gxwbsp);
	int ixxebqukpqp(double pyosgkocjtu, bool ddoqnobmd);
	bool vakeeckmwnjmurlc(bool koelmxefcrrf, int selrr, double blybqdorjbrwcwz, string zxgukuejjlo, int julszbqjrrt, string omddax, string jblfinsuzgcpr, double nvlkasmdyqcco, int lieidyerimqv, bool ogdcdycgm);
	bool pgclnftpjkpsmgqifuj(bool satcphauhddkzc, string mnavqejwezi, bool nexsjrlxvuzhzw, bool uhocwwlbey, bool hldoyrki, bool jvuymtdjvvuzoyw, bool ephpzluwt, int qzdkpkucgqosum, int fvdbixqgc, double lepihthgwydvh);
	bool ovtsmqrbzhohlpwdig(double qsphjejc, int ssgduc, double wtbfvofus, int zojjvuwxafkkbwb, bool ywinojomujspt, bool bkjngahlg);
	int pbbiycgxkcbyhml(double ipywvq, double zcphvglmmnagnhw);

};


bool wcgvzhp::wkiplnuolnezzaiwd(int ccrdld) {
	return false;
}

bool wcgvzhp::omtfnnpprrpcshzy(double wbojfvgyhqiv, string wufgfcvnme) {
	bool ysgtol = false;
	double nmukyymjoomq = 38134;
	if (false != false) {
		int ydgsjx;
		for (ydgsjx = 79; ydgsjx > 0; ydgsjx--) {
			continue;
		}
	}
	if (38134 == 38134) {
		int agjqy;
		for (agjqy = 35; agjqy > 0; agjqy--) {
			continue;
		}
	}
	if (false == false) {
		int uee;
		for (uee = 76; uee > 0; uee--) {
			continue;
		}
	}
	return false;
}

double wcgvzhp::icrhwmdsfqti(double fdplecq, string jqfvojcotjltcnv) {
	string ofmowxvtt = "pgklczgrfmyfuuykfitzpkzxxrvxbn";
	double muqjnyhlk = 41239;
	double wcbnigpt = 23573;
	bool zbkdjvvehn = false;
	string vrkveiirwh = "bmftcerkkiaawfwgagsdnuyhjicnbsdfzsksmgkiqrtecttvzmvwzgiihirktoerotaixzawgjycrhpivrauaflmcpothqfvgqsy";
	string uyhfkasejarhuy = "usuzoncmpuvprhkimzdbkqt";
	int yixxwawuwjvylj = 5445;
	double kpowgeqnf = 69112;
	double wcwdurvtxsnmvav = 5338;
	if (5445 != 5445) {
		int jgui;
		for (jgui = 38; jgui > 0; jgui--) {
			continue;
		}
	}
	return 11561;
}

void wcgvzhp::htebeisikuwich(bool dcrfozwu, int qmgpxfgv, bool peeuptamewdzv, int irsaase, bool ipzjskalmaymg, bool srsvlvqpog, bool tqbuwa, double svngvstbtvlp, int gxwbsp) {
	int klbmuvsog = 2730;
	double hxkyz = 11680;
	double tvbhwlkufoixz = 42289;
	string ljskvlu = "pnfnzmkmkiovwdlyyyfslmlwslpwvejuoeukuqqmymqgwzuyrksulcdypattetoqdpytfrnssclqlhvmqxp";
	bool lfpoheo = false;
	double beqkw = 5502;
	bool stfnjfytmvimt = false;
	if (42289 != 42289) {
		int kdgq;
		for (kdgq = 88; kdgq > 0; kdgq--) {
			continue;
		}
	}
	if (false == false) {
		int lyte;
		for (lyte = 32; lyte > 0; lyte--) {
			continue;
		}
	}

}

int wcgvzhp::ixxebqukpqp(double pyosgkocjtu, bool ddoqnobmd) {
	double lxjqmyywf = 2484;
	int wcnpvwiyqxy = 11;
	int bxiqcsgvtuimxn = 1297;
	int cpksoc = 7210;
	double qtcwwoacussvlds = 29083;
	bool uewklkco = true;
	double ackqcrqvqfq = 83409;
	if (true != true) {
		int nyemkvanvo;
		for (nyemkvanvo = 23; nyemkvanvo > 0; nyemkvanvo--) {
			continue;
		}
	}
	if (true != true) {
		int usz;
		for (usz = 51; usz > 0; usz--) {
			continue;
		}
	}
	if (2484 == 2484) {
		int sr;
		for (sr = 20; sr > 0; sr--) {
			continue;
		}
	}
	if (true == true) {
		int oanqm;
		for (oanqm = 59; oanqm > 0; oanqm--) {
			continue;
		}
	}
	return 40494;
}

bool wcgvzhp::vakeeckmwnjmurlc(bool koelmxefcrrf, int selrr, double blybqdorjbrwcwz, string zxgukuejjlo, int julszbqjrrt, string omddax, string jblfinsuzgcpr, double nvlkasmdyqcco, int lieidyerimqv, bool ogdcdycgm) {
	int qrjifxcvtxcqpr = 3760;
	string wdihseekgucg = "yfwngexyamlpovcqjehlmktvhawizhlg";
	bool uffin = false;
	int ciyaudaojw = 2902;
	int lzvtamqwo = 2330;
	if (2902 == 2902) {
		int mhre;
		for (mhre = 26; mhre > 0; mhre--) {
			continue;
		}
	}
	return true;
}

bool wcgvzhp::pgclnftpjkpsmgqifuj(bool satcphauhddkzc, string mnavqejwezi, bool nexsjrlxvuzhzw, bool uhocwwlbey, bool hldoyrki, bool jvuymtdjvvuzoyw, bool ephpzluwt, int qzdkpkucgqosum, int fvdbixqgc, double lepihthgwydvh) {
	return false;
}

bool wcgvzhp::ovtsmqrbzhohlpwdig(double qsphjejc, int ssgduc, double wtbfvofus, int zojjvuwxafkkbwb, bool ywinojomujspt, bool bkjngahlg) {
	double knkkebwovmltqf = 6101;
	int aobsby = 4930;
	string jfwbwizviw = "gljxpzzogfipbpvoyluadylhvssqbfifmunsytpcbwocvsrrfhadqdbptwighhogthrhrmzgextpfdhnuzwhis";
	if (4930 != 4930) {
		int kg;
		for (kg = 63; kg > 0; kg--) {
			continue;
		}
	}
	if (string("gljxpzzogfipbpvoyluadylhvssqbfifmunsytpcbwocvsrrfhadqdbptwighhogthrhrmzgextpfdhnuzwhis") == string("gljxpzzogfipbpvoyluadylhvssqbfifmunsytpcbwocvsrrfhadqdbptwighhogthrhrmzgextpfdhnuzwhis")) {
		int fdyt;
		for (fdyt = 46; fdyt > 0; fdyt--) {
			continue;
		}
	}
	if (4930 != 4930) {
		int tcgvai;
		for (tcgvai = 30; tcgvai > 0; tcgvai--) {
			continue;
		}
	}
	return false;
}

int wcgvzhp::pbbiycgxkcbyhml(double ipywvq, double zcphvglmmnagnhw) {
	double oxlfrhm = 11622;
	double gxxaonoh = 55742;
	if (55742 != 55742) {
		int swzsnhep;
		for (swzsnhep = 9; swzsnhep > 0; swzsnhep--) {
			continue;
		}
	}
	if (11622 == 11622) {
		int sbknshaeiy;
		for (sbknshaeiy = 1; sbknshaeiy > 0; sbknshaeiy--) {
			continue;
		}
	}
	if (11622 != 11622) {
		int hiihwhxeao;
		for (hiihwhxeao = 39; hiihwhxeao > 0; hiihwhxeao--) {
			continue;
		}
	}
	if (11622 != 11622) {
		int vlakada;
		for (vlakada = 16; vlakada > 0; vlakada--) {
			continue;
		}
	}
	if (11622 != 11622) {
		int rsxbfg;
		for (rsxbfg = 86; rsxbfg > 0; rsxbfg--) {
			continue;
		}
	}
	return 40867;
}

bool wcgvzhp::gyvoqghiqekfxcvt(string fjnpfrsj, int zxmrsgtlksfk, double ghgsyhjitexl, string cmderekohcux, bool lzzkbmgjemri) {
	return false;
}

int wcgvzhp::dwvkosyzvppwxohnuznytsr(string vlwjkzwis, int jorhpjisjc, double eaiyht, bool laxwv, string mtlbyxhyp, bool nfjuvfymgweh, double gjtktnjj, string ogpqddv, string soecj) {
	double ssjufgrbk = 7645;
	double xxpeycoveoxd = 18574;
	bool sbmwjoa = false;
	bool kfrwsqvjsfzk = false;
	bool kxisnuomeyxka = false;
	double myrvpwmprmfepaf = 40296;
	bool ywaxkovnuzm = false;
	bool cemjsufdfuotiqq = true;
	double bdfkp = 15632;
	bool zxgurqfu = false;
	if (18574 == 18574) {
		int osmgghluo;
		for (osmgghluo = 7; osmgghluo > 0; osmgghluo--) {
			continue;
		}
	}
	if (false == false) {
		int jayebrckxk;
		for (jayebrckxk = 48; jayebrckxk > 0; jayebrckxk--) {
			continue;
		}
	}
	if (false != false) {
		int braacsd;
		for (braacsd = 60; braacsd > 0; braacsd--) {
			continue;
		}
	}
	if (true != true) {
		int onhexggcw;
		for (onhexggcw = 83; onhexggcw > 0; onhexggcw--) {
			continue;
		}
	}
	return 57063;
}

int wcgvzhp::bdgdcbzeshanrkjeefebvdlof(bool kyrcaokjho, string uumdu, double utiycblpswwvwf, bool okeauyyif, int wlnjhou, double wdespiblaniaxv, bool wpoycp, int tdoorhnjrwzvpxn, bool wmacaprgir) {
	int iluvajnvtt = 125;
	double vjjrswyklfca = 19942;
	string wxndmvckmjkuehy = "dcbecjqgyjlkthhuwjmmnkgiqocjybbkbagbmpxmrkyeamfc";
	int qwbjfxrlgty = 5911;
	string rtdhxynznlgpy = "dsvbnqk";
	string dhcjo = "irmmvyuezmluuzhprynsrmptbwjpzpnmblaaciuqxthqoxqbxzvxxqwysbxshorvftseoo";
	if (string("dcbecjqgyjlkthhuwjmmnkgiqocjybbkbagbmpxmrkyeamfc") == string("dcbecjqgyjlkthhuwjmmnkgiqocjybbkbagbmpxmrkyeamfc")) {
		int qdxllfgowu;
		for (qdxllfgowu = 64; qdxllfgowu > 0; qdxllfgowu--) {
			continue;
		}
	}
	if (string("dsvbnqk") != string("dsvbnqk")) {
		int kl;
		for (kl = 68; kl > 0; kl--) {
			continue;
		}
	}
	return 41221;
}

void wcgvzhp::mxdqylpspimnjwpffbvlpmi(int hlgjssjrqhv, string joikyu, int bdgtrqsno) {
	string uficjvlwi = "lcpcpaylplkvymhowamaqbfzjqaafcxjrwxihwjsjltsvbgvafsfexexycrydyfcrcvnulbjvyjsegql";
	if (string("lcpcpaylplkvymhowamaqbfzjqaafcxjrwxihwjsjltsvbgvafsfexexycrydyfcrcvnulbjvyjsegql") == string("lcpcpaylplkvymhowamaqbfzjqaafcxjrwxihwjsjltsvbgvafsfexexycrydyfcrcvnulbjvyjsegql")) {
		int gssbirew;
		for (gssbirew = 27; gssbirew > 0; gssbirew--) {
			continue;
		}
	}

}

string wcgvzhp::itnsctfzhwk(int huhyy, double alruko, int zxipthnlkp, int dsruqofttpicp) {
	return string("pyfdhekticvxpowacgqr");
}

bool wcgvzhp::qvmamaknsf(bool xhawuocdlsedkeh, double zsgtcsajzmx, string patmdubws, string kzqxtltypmbs, string gcuserqqtdt, int smckqcymbms, int mjoolmvfp, bool eziaaaxuoxtkz, int pahmn, string iyfnyqe) {
	bool wilxjvn = false;
	string tczcs = "jjjjbrpducfjvktwteovkil";
	if (false == false) {
		int ovmxaqrj;
		for (ovmxaqrj = 28; ovmxaqrj > 0; ovmxaqrj--) {
			continue;
		}
	}
	if (false == false) {
		int yic;
		for (yic = 96; yic > 0; yic--) {
			continue;
		}
	}
	if (string("jjjjbrpducfjvktwteovkil") != string("jjjjbrpducfjvktwteovkil")) {
		int clw;
		for (clw = 16; clw > 0; clw--) {
			continue;
		}
	}
	if (false == false) {
		int yvlbbi;
		for (yvlbbi = 79; yvlbbi > 0; yvlbbi--) {
			continue;
		}
	}
	if (false == false) {
		int rmo;
		for (rmo = 52; rmo > 0; rmo--) {
			continue;
		}
	}
	return true;
}

double wcgvzhp::vtwqsaydgzpnkt(string vloaggzorfsd, int jkbkzx, int fvsesat, string trodgs, string coqhrue, bool slkyscjax, string gdkexxtgms, double gyizihinz, double pjxemh) {
	string xxsohgpqlmxslov = "crvbjfrcizqhpoezsltgmbpidvraghjhoaoynrdqwblgsgebwkklbnxahcfbqgooarcxmdsbhtoufrcanknevrpisyqd";
	int bhcfeis = 3290;
	bool rqqikzbw = true;
	bool tzizsljtespi = true;
	bool mijkpavfar = false;
	int iwzpykrpeu = 2956;
	double bpjkvhfzzhn = 36738;
	if (3290 == 3290) {
		int rmylmrtzlv;
		for (rmylmrtzlv = 98; rmylmrtzlv > 0; rmylmrtzlv--) {
			continue;
		}
	}
	if (false == false) {
		int pqrywlarq;
		for (pqrywlarq = 36; pqrywlarq > 0; pqrywlarq--) {
			continue;
		}
	}
	if (3290 == 3290) {
		int jh;
		for (jh = 84; jh > 0; jh--) {
			continue;
		}
	}
	return 5367;
}

string wcgvzhp::qhuoobfxsehttclreulhyipez(string okuteihvdkbdpf) {
	int rywsipulvftwz = 6789;
	string oxjjtqzaops = "fysqagolflobudfczeehgbyozkdtyevdgjqhhgmqxqfryxlu";
	string wvtbacgongpxgnp = "jrfpnpezivjofqfibwcgozzjrvijpauojihttj";
	double bstzhctxleh = 1536;
	bool qlhohurvnhidzih = true;
	string bnhksfux = "qvlnhyuqxgfzfhvtdhmiymusknlnqvoxsgjvdwtqnmainlskaupsysqqajcudsbebuecvgtwonmyhodqmphgyjkhzw";
	int obxjx = 6690;
	bool cwgqscyk = true;
	if (string("qvlnhyuqxgfzfhvtdhmiymusknlnqvoxsgjvdwtqnmainlskaupsysqqajcudsbebuecvgtwonmyhodqmphgyjkhzw") == string("qvlnhyuqxgfzfhvtdhmiymusknlnqvoxsgjvdwtqnmainlskaupsysqqajcudsbebuecvgtwonmyhodqmphgyjkhzw")) {
		int mvoxhvo;
		for (mvoxhvo = 37; mvoxhvo > 0; mvoxhvo--) {
			continue;
		}
	}
	if (string("fysqagolflobudfczeehgbyozkdtyevdgjqhhgmqxqfryxlu") != string("fysqagolflobudfczeehgbyozkdtyevdgjqhhgmqxqfryxlu")) {
		int vrweekeam;
		for (vrweekeam = 44; vrweekeam > 0; vrweekeam--) {
			continue;
		}
	}
	if (6789 == 6789) {
		int tp;
		for (tp = 79; tp > 0; tp--) {
			continue;
		}
	}
	return string("udnuexnxpnjdiyh");
}

string wcgvzhp::fatxwhfsjddabrkodgfapcb(bool gulanwgbh, string ctmkt, string nwlqzmbfncj, int ygkgmrfvbkj, double zzxgxvehmotymit, string xcsquwwgrdcipc) {
	int rjiyllyedtrr = 393;
	if (393 == 393) {
		int phiooiu;
		for (phiooiu = 4; phiooiu > 0; phiooiu--) {
			continue;
		}
	}
	return string("zjwfsvhzabnjadvqjknb");
}

bool wcgvzhp::xovjqmuevgqhbn() {
	double adxltuofnin = 42596;
	int gvnzch = 595;
	double ixfwvxbfgshxrid = 20755;
	double atbzd = 64450;
	int qslkkumwqbriiks = 624;
	string ktgcc = "qvkgbhoiwvmjqzoiqvvgtgixxfgojdwqpsmpzxudadajlmfjlchifhxadypbyeuzkcilhzygrrflkfdbesriyjphzjkkhdquhahr";
	bool cmimblereotqpxa = true;
	double mmocnqtndoevn = 35307;
	if (42596 != 42596) {
		int adclikk;
		for (adclikk = 18; adclikk > 0; adclikk--) {
			continue;
		}
	}
	if (624 == 624) {
		int mqs;
		for (mqs = 21; mqs > 0; mqs--) {
			continue;
		}
	}
	if (true != true) {
		int driehxx;
		for (driehxx = 82; driehxx > 0; driehxx--) {
			continue;
		}
	}
	if (true != true) {
		int cgxxpf;
		for (cgxxpf = 28; cgxxpf > 0; cgxxpf--) {
			continue;
		}
	}
	return true;
}

void wcgvzhp::hxthzofnnwokfgdbrtu(double cqmgopfdufiy, int jqiebkqymy, int dreqxgrpvioy, string alswmqfkfmzw) {
	string ndfhltfx = "cfsazznyzccsgeibqieduniycvro";
	bool buodflqqq = false;
	string odifqnjxeijzrk = "ifpjcjlthyfsdcxkykdnsotxyictvl";
	string cehtwgnvxsjqlm = "qwwwgchgfsm";
	double cedpirxxihavwp = 26476;
	double dsuqacrjzc = 75514;
	int jubeickx = 3740;
	bool cikwekcq = false;
	bool ntzbtjvm = false;
	string kkkfygxhfudsg = "";
	if (string("qwwwgchgfsm") == string("qwwwgchgfsm")) {
		int bk;
		for (bk = 19; bk > 0; bk--) {
			continue;
		}
	}
	if (false == false) {
		int szunpta;
		for (szunpta = 93; szunpta > 0; szunpta--) {
			continue;
		}
	}
	if (string("") == string("")) {
		int ydqzmuqa;
		for (ydqzmuqa = 13; ydqzmuqa > 0; ydqzmuqa--) {
			continue;
		}
	}
	if (string("ifpjcjlthyfsdcxkykdnsotxyictvl") != string("ifpjcjlthyfsdcxkykdnsotxyictvl")) {
		int wm;
		for (wm = 75; wm > 0; wm--) {
			continue;
		}
	}

}

string wcgvzhp::gthffkhyaxse(int gqkotaiwyfs, int emruhuplgs, string kbtrrjyzlxceyxm, int zwhhjod, string faranyrppw) {
	int kbkne = 1568;
	int ithrvauitjukjza = 3212;
	int jesxrthpqedjujq = 2084;
	bool xoauwbuhru = false;
	bool kyomdeiamcwwloj = false;
	double dpejvgp = 10063;
	bool cqqhptg = true;
	string waypex = "xeyqnmjtszxmguownrtwyfeqhkzyuzuraaqzfrgebtgwoglpyntgpirdsptgpcronvllifplqe";
	double lpfytx = 49546;
	return string("pamnafp");
}

void wcgvzhp::bqhhvppxrcyh(double kdrpyariuf, bool ynftfl, string ructes) {
	string jvkhim = "iqdbnrvrkotxylegnriadzijwscpbdkohztkjmwyqbknqx";
	bool ogyby = false;
	int tcnaxdnvygizmnh = 1826;
	int auqzlvl = 6655;
	if (string("iqdbnrvrkotxylegnriadzijwscpbdkohztkjmwyqbknqx") != string("iqdbnrvrkotxylegnriadzijwscpbdkohztkjmwyqbknqx")) {
		int lqixju;
		for (lqixju = 0; lqixju > 0; lqixju--) {
			continue;
		}
	}

}

wcgvzhp::wcgvzhp() {
	this->itnsctfzhwk(183, 36211, 5304, 4098);
	this->qvmamaknsf(false, 22054, string("qjdjewyltbzrydk"), string("fqhpuigsendqeprtpxuxmvshnugylzlxlhspldjhkcejlgofrhyqnzqssynczavrveuqsqevdbadhe"), string("heedmhotjfvfofuiqlyhvscypnotizhytpdwwvwktssuoqdkmcw"), 1730, 358, true, 1006, string("zckaraalxtcgibbgrpppeysiyjjasjcxodhzzefzwxcwbfwfrhpffmbeyoy"));
	this->vtwqsaydgzpnkt(string("ontdrlspzqxkeelwynykbqffycrmrmzewunsjztoklxipqyupnkkbxtgapnqkegrouvayukpqubqmrdaokrzhzhxramrjntwjacn"), 653, 448, string("cwnvujni"), string("rpyfbzacmdrubdlcpnflsgbdafkoxeckflhlwnuvfnul"), false, string("dastlm"), 27428, 52184);
	this->qhuoobfxsehttclreulhyipez(string("bvenizngie"));
	this->fatxwhfsjddabrkodgfapcb(false, string("wjguhwwswkswrdiyhekwvzpoxoxiztj"), string("scpowgcoyloixspqltobszbskovijewfhbemmugftvaqzguyqfqijakkgexpwutzhlgmjbzxi"), 4004, 54265, string("qtayskklvtgtlbkxvipotpdrnohltuxcrgjifjcmihxgxu"));
	this->xovjqmuevgqhbn();
	this->hxthzofnnwokfgdbrtu(82281, 194, 2544, string("zasa"));
	this->gthffkhyaxse(1130, 1887, string("lwmlbuaqaimbmlfwdnhqt"), 3459, string("lkjvempvkalucswywblkdflivhwlcrtw"));
	this->bqhhvppxrcyh(29682, true, string("wicyoikxjactgtintyflktojcqndafxz"));
	this->gyvoqghiqekfxcvt(string("jbgdaewjtjecznqppgpeapnacmrraqegarbafmlrnixudpddkugxlbmemvimjlqlnmdvbsvzohnnh"), 293, 37823, string("nhaqiapwgcmuxwkucymchzjyenprxk"), false);
	this->dwvkosyzvppwxohnuznytsr(string("qbnyeabujrlvtjwetsfiufxsztsaxmrxafse"), 2223, 5587, false, string("ojzuumyktaszspsyokuypbdllmn"), true, 93342, string("cmkmxexjcijfdi"), string("klkfhrjdcdnroqyofkishhyffxzcckkckjoqeqvdkjy"));
	this->bdgdcbzeshanrkjeefebvdlof(true, string("uphurdxwrenyqzbhszlejgovitruosxxgfabfmssbxvjaraqhefsnbowtfczhisvxwzqdvppaxttrtphn"), 4345, false, 1729, 14127, false, 606, false);
	this->mxdqylpspimnjwpffbvlpmi(361, string("wqaloahstlfwogcjqewaouqdjqaxeitteckmaj"), 29);
	this->wkiplnuolnezzaiwd(5788);
	this->omtfnnpprrpcshzy(19458, string("jjwzelxwamnizgrfyreneeurakmjlamskmuuvgkmkahuunigplvtsimzzjrwqoaidovudyavszhckvziimtyhxsfeldgyw"));
	this->icrhwmdsfqti(32577, string("jegzglpqimcflvrnqdvovhfueqbjshyfjrmloitkjnethklqzexoihfjjjtnbnosiworjmqrzlfbvkaeaqvujtraopagrwzhjvm"));
	this->htebeisikuwich(true, 5588, false, 471, false, false, true, 952, 1290);
	this->ixxebqukpqp(16482, false);
	this->vakeeckmwnjmurlc(false, 1998, 34368, string("zzbmxprqvymsjwzalfwnwornlnrinokhtbsfyviqwnvpbclheenoizqne"), 878, string("klszkngqgbufnnggiabssdygnrmfuovfwrqwiobv"), string("uywosthtzallsgcrsbdutrdflnpdlzwxeytqnpvpxewksxsyvbiqeqogljfzf"), 10434, 65, false);
	this->pgclnftpjkpsmgqifuj(true, string("oiftuquryq"), true, true, false, false, false, 1305, 2903, 3083);
	this->ovtsmqrbzhohlpwdig(85982, 3146, 5960, 821, true, false);
	this->pbbiycgxkcbyhml(4591, 1945);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class vpfjfsf {
public:
	double yilbwzdswokiyqi;
	string ihnhnmo;
	bool rbgjsc;
	vpfjfsf();
	bool nrupspovdhadgwcul(bool wwthooysxck, bool jwxjpvwghu, string udivzacamygccly, string xmayay, string jjxtqrou);
	bool hzacbxffpeomvybgcth();
	bool karktylbpizsmgkkgizcb(string xsfqy, bool jndfzzp, double cxmaojocg, double oiijtunpmoozgfz, int yvtqkvynkcvsd);
	double cebjmgrwfkcdjmsyyxssqx(int lgnwaz, int ofzcrlijbyd, int wqjinvfxujnkgv, bool fgforhww, string gczqyyrk, bool dkkcdvvzbophoi, string napyclbfvyggug, double zsymhxhwaeyoke, bool vliccyrxsb);
	int iwaqncvpky();
	int ycksaqjvuzlhap(int zevohrj, string liofpl, bool ephcjepafjggfc, string dcexdbzwwwlnvnb, int txgoyxdpo, bool wextfj, bool jltcea, bool nsijvjpdv, string wtjamefpwm, string nowgbpqzv);
	void sguekfidhzyvghtyarybqtg(double dfvpor, string nsgse, string njeuyjcufnhtpa, int xxpeba, bool vpziosjtepz, bool kjaznfooaib);
	void eafuwjufjhgtochk(double vsliqqpbr, bool eyzrsvgh, double gmlacitvh, bool uudzfpcicv, bool ublrbvr, bool pxlhbbvjmsyir);
	string yleumgfgfabgybgawl(bool zudmdxmxrhkk, string bbhlanc, string cfismbp);
	bool wjjwpkejpxprqavcbssumnouf(string feygypgb, bool rbbpnvkch, double mgbxyvsbmccnfq, double eymipsbh, bool pvfvwxwfbxyeox, bool mtlldrgikdwmsz, bool zlbvmbtustb, double wlesjvwl, int ywsaww);

protected:
	string cletkfsuwds;
	double qdkxboj;
	bool rpmwlseiobzbsom;

	void ledxicrahpaflncvomclmmhlp(double amyxxi, bool efrauydjgnxcbie, double ihrzdjihayffwu, string rvezksjt, string jvxyshikajfr, bool qirzlfpwqxmzc, bool bnfkbgj, string igjvxaokpzackai, int rxjyumc, int jzpkw);
	int asynshuokrykxxxjqzs(string imtrkwmrsajta, string tecjloqvirwlf, int uhjlyupxleqideu, bool puxzojrjr, int mfekhmmvfac, bool kciaoajn, int ohwvasgej, string fwswfc, double uoivhj, bool koihtw);
	string vcacbjmbosahncjqwzcbytn(bool krpbk, int uxlbfpwma, string ifqivmmo);
	bool qdmbuhrzxbpvcsppq(string wulvmzfhnicwbhp, string cetvmnukzxtp, bool cwodxnppsomsqhh, double qtbeywaucrbxo);
	void fzzxfvkkqithrrwbxlsjmxd(string dfejnqjon);
	double hjeztsqvxwguftftatdzcx(double kqcwyirhsb, double zcqggimmgjnjdz, bool ikbdtratdl, int whqkbtr, bool agndrx, string wjgcbkd, double fcmhtngwaveojxz, int zojgjikb, string xkwrpjze, bool dsthscbzx);
	int uycajyywhzonglymuhj(int hlsaspeuuxorek, int pdfebwyfjglaa, string oinjndczloz);
	bool ztixtkwfbchx();
	string qmvzkmyermtw();

private:
	int wofebrajaf;

	double jzevvvogciuifyjtvhcswxcu(double ezbodchvi, double uukkqbg, bool ajmppshse, int mheqarmr);
	double aucitbjidjttwltdtxozyv(bool osivorlzxzae, double aaammcjxrnhkwpq, double slucrpcvdnr, string yybjdx, double katvyonh, string qlujbjevfezctfb, int njwqqe, double iktwkeiuwie, bool owefukqpivrucau);

};


double vpfjfsf::jzevvvogciuifyjtvhcswxcu(double ezbodchvi, double uukkqbg, bool ajmppshse, int mheqarmr) {
	int mybmzoud = 2329;
	int kcxoeicaw = 7831;
	if (7831 != 7831) {
		int yakwwv;
		for (yakwwv = 1; yakwwv > 0; yakwwv--) {
			continue;
		}
	}
	if (7831 != 7831) {
		int nswwdrw;
		for (nswwdrw = 58; nswwdrw > 0; nswwdrw--) {
			continue;
		}
	}
	if (2329 != 2329) {
		int jzrig;
		for (jzrig = 87; jzrig > 0; jzrig--) {
			continue;
		}
	}
	return 68879;
}

double vpfjfsf::aucitbjidjttwltdtxozyv(bool osivorlzxzae, double aaammcjxrnhkwpq, double slucrpcvdnr, string yybjdx, double katvyonh, string qlujbjevfezctfb, int njwqqe, double iktwkeiuwie, bool owefukqpivrucau) {
	bool pzgfkrbk = true;
	int quffkwkwfpfge = 1644;
	double ofuwhyywznhdlr = 471;
	string bevwdvqofl = "ynsuyckapggt";
	int jidavlbchxknjmt = 8504;
	double bnlmddzk = 12841;
	string xewrhaoh = "usrglyjenuot";
	if (8504 != 8504) {
		int ivqb;
		for (ivqb = 79; ivqb > 0; ivqb--) {
			continue;
		}
	}
	return 78161;
}

void vpfjfsf::ledxicrahpaflncvomclmmhlp(double amyxxi, bool efrauydjgnxcbie, double ihrzdjihayffwu, string rvezksjt, string jvxyshikajfr, bool qirzlfpwqxmzc, bool bnfkbgj, string igjvxaokpzackai, int rxjyumc, int jzpkw) {

}

int vpfjfsf::asynshuokrykxxxjqzs(string imtrkwmrsajta, string tecjloqvirwlf, int uhjlyupxleqideu, bool puxzojrjr, int mfekhmmvfac, bool kciaoajn, int ohwvasgej, string fwswfc, double uoivhj, bool koihtw) {
	string khirwidonag = "ubovofaphdyjaizmgbxavczbxgupjwayxopaincxvsz";
	if (string("ubovofaphdyjaizmgbxavczbxgupjwayxopaincxvsz") != string("ubovofaphdyjaizmgbxavczbxgupjwayxopaincxvsz")) {
		int le;
		for (le = 53; le > 0; le--) {
			continue;
		}
	}
	if (string("ubovofaphdyjaizmgbxavczbxgupjwayxopaincxvsz") == string("ubovofaphdyjaizmgbxavczbxgupjwayxopaincxvsz")) {
		int vjzfdppi;
		for (vjzfdppi = 91; vjzfdppi > 0; vjzfdppi--) {
			continue;
		}
	}
	return 84690;
}

string vpfjfsf::vcacbjmbosahncjqwzcbytn(bool krpbk, int uxlbfpwma, string ifqivmmo) {
	double kfkpueks = 17214;
	bool njiibcrxmv = true;
	double zeojxthf = 3240;
	bool bexlwlugcrux = false;
	double qhebsuogxhk = 50560;
	int gihjlwkvuox = 673;
	double rwdgrwkccfkh = 65773;
	return string("klpzlonojyouye");
}

bool vpfjfsf::qdmbuhrzxbpvcsppq(string wulvmzfhnicwbhp, string cetvmnukzxtp, bool cwodxnppsomsqhh, double qtbeywaucrbxo) {
	bool cczqovcdvimokmb = false;
	int zrgzzmznmbb = 2212;
	int trpgadny = 1012;
	bool ogfcbzegjbopslt = true;
	string iomyzxjpunqrhp = "mrokynxemthqlgfolhmwhnhygpotbmpenktvikfthloyfder";
	string ltggiswxniucqsd = "olborklzslwrxtiunrnugdkhxoqdhwbqdrsyidnfqfvpvpdbdqgwleunfknwf";
	int pyriaawirqskn = 5713;
	double cebdgaab = 66610;
	if (1012 != 1012) {
		int slj;
		for (slj = 70; slj > 0; slj--) {
			continue;
		}
	}
	if (string("mrokynxemthqlgfolhmwhnhygpotbmpenktvikfthloyfder") != string("mrokynxemthqlgfolhmwhnhygpotbmpenktvikfthloyfder")) {
		int mt;
		for (mt = 45; mt > 0; mt--) {
			continue;
		}
	}
	if (2212 == 2212) {
		int jiominw;
		for (jiominw = 90; jiominw > 0; jiominw--) {
			continue;
		}
	}
	if (1012 != 1012) {
		int ocrsqhtazs;
		for (ocrsqhtazs = 43; ocrsqhtazs > 0; ocrsqhtazs--) {
			continue;
		}
	}
	if (2212 != 2212) {
		int aguxjmyr;
		for (aguxjmyr = 100; aguxjmyr > 0; aguxjmyr--) {
			continue;
		}
	}
	return false;
}

void vpfjfsf::fzzxfvkkqithrrwbxlsjmxd(string dfejnqjon) {
	bool lfekhlqrpvg = true;
	bool nnfxols = true;
	double dpketmitjjanld = 2925;

}

double vpfjfsf::hjeztsqvxwguftftatdzcx(double kqcwyirhsb, double zcqggimmgjnjdz, bool ikbdtratdl, int whqkbtr, bool agndrx, string wjgcbkd, double fcmhtngwaveojxz, int zojgjikb, string xkwrpjze, bool dsthscbzx) {
	int jytxeoazwfw = 5313;
	double krlcxqtyffssdey = 7492;
	int qdaotjzcfdzapy = 4609;
	bool ndnotzgqmf = false;
	int kqmdaitwy = 4619;
	int bvoccu = 2471;
	bool eywzaloaazsak = false;
	string uyosgtp = "sjreuzrpayfoi";
	string kaduttzftqnj = "mcxskyaiakgyiejt";
	if (string("sjreuzrpayfoi") == string("sjreuzrpayfoi")) {
		int nfednonqj;
		for (nfednonqj = 91; nfednonqj > 0; nfednonqj--) {
			continue;
		}
	}
	if (false == false) {
		int lnm;
		for (lnm = 57; lnm > 0; lnm--) {
			continue;
		}
	}
	if (string("sjreuzrpayfoi") == string("sjreuzrpayfoi")) {
		int fzihr;
		for (fzihr = 75; fzihr > 0; fzihr--) {
			continue;
		}
	}
	if (false != false) {
		int zndsymvi;
		for (zndsymvi = 28; zndsymvi > 0; zndsymvi--) {
			continue;
		}
	}
	if (7492 == 7492) {
		int kjmw;
		for (kjmw = 94; kjmw > 0; kjmw--) {
			continue;
		}
	}
	return 82417;
}

int vpfjfsf::uycajyywhzonglymuhj(int hlsaspeuuxorek, int pdfebwyfjglaa, string oinjndczloz) {
	string kbhbvqaom = "z";
	string ilvsianzis = "zrgfchzbyczwmiysaatmewwiykrcjpnvyfrqnalskmukcsslqftrkkkzliszzysetxjbqt";
	string zfjqkbzxrum = "iewyeuvwq";
	string pqymznaugqmxbe = "vqrhngakzgmcxnefbutycuasgtgglahobrilstjfbmyfwkhxqclbvzkqfqsdkerwjfqt";
	bool wrhrdtqz = false;
	int nbzchcbbx = 333;
	bool snmpxoz = false;
	int owbobkqaspiulh = 7794;
	if (false != false) {
		int sew;
		for (sew = 11; sew > 0; sew--) {
			continue;
		}
	}
	return 7560;
}

bool vpfjfsf::ztixtkwfbchx() {
	double ssdonqogngeny = 31827;
	string szhdl = "rasrddkppngafapgqtnvpbjfmadronkjtr";
	string vwuon = "wyvrllqyinwsfmugrdnxpuaittyrdbiejocqlytxwckjlfknbcnlptdsydkbaao";
	if (string("wyvrllqyinwsfmugrdnxpuaittyrdbiejocqlytxwckjlfknbcnlptdsydkbaao") == string("wyvrllqyinwsfmugrdnxpuaittyrdbiejocqlytxwckjlfknbcnlptdsydkbaao")) {
		int oehtb;
		for (oehtb = 44; oehtb > 0; oehtb--) {
			continue;
		}
	}
	if (31827 != 31827) {
		int zyg;
		for (zyg = 75; zyg > 0; zyg--) {
			continue;
		}
	}
	return true;
}

string vpfjfsf::qmvzkmyermtw() {
	string bakfzhsktbx = "bmysiivdmqlsryluvukkfupwvnvqmbwyhgplvmvalexfcsumtthpvlwewfbykekfwhdqzrcc";
	double jmpdc = 7600;
	int appljhpux = 4917;
	double lqxcxq = 18504;
	bool ibcguuuiurrvb = false;
	bool jrobhzumwnxvr = false;
	int mxdzzlbsysrqvs = 2480;
	int lpginhvleskevu = 5788;
	bool xxfrjkvy = true;
	bool pqhvtptpwp = true;
	if (false != false) {
		int izzofvjugr;
		for (izzofvjugr = 91; izzofvjugr > 0; izzofvjugr--) {
			continue;
		}
	}
	return string("bi");
}

bool vpfjfsf::nrupspovdhadgwcul(bool wwthooysxck, bool jwxjpvwghu, string udivzacamygccly, string xmayay, string jjxtqrou) {
	double yugca = 5868;
	int pgjsxz = 5151;
	int bnpjilemcaybe = 224;
	string wfysghbldnff = "ri";
	if (string("ri") != string("ri")) {
		int bsyhyakmg;
		for (bsyhyakmg = 1; bsyhyakmg > 0; bsyhyakmg--) {
			continue;
		}
	}
	return false;
}

bool vpfjfsf::hzacbxffpeomvybgcth() {
	double wnhqupcveroyb = 19315;
	string vcupyxfy = "mxjfziddximmotqvbbetzmnwdunoddyvlnhxfggyyndnbtdg";
	string ecorvggltwd = "lq";
	if (string("mxjfziddximmotqvbbetzmnwdunoddyvlnhxfggyyndnbtdg") == string("mxjfziddximmotqvbbetzmnwdunoddyvlnhxfggyyndnbtdg")) {
		int zbadyrzg;
		for (zbadyrzg = 94; zbadyrzg > 0; zbadyrzg--) {
			continue;
		}
	}
	if (string("lq") != string("lq")) {
		int mimgkhftdl;
		for (mimgkhftdl = 63; mimgkhftdl > 0; mimgkhftdl--) {
			continue;
		}
	}
	if (string("lq") == string("lq")) {
		int jascjzmk;
		for (jascjzmk = 65; jascjzmk > 0; jascjzmk--) {
			continue;
		}
	}
	if (string("mxjfziddximmotqvbbetzmnwdunoddyvlnhxfggyyndnbtdg") != string("mxjfziddximmotqvbbetzmnwdunoddyvlnhxfggyyndnbtdg")) {
		int hw;
		for (hw = 90; hw > 0; hw--) {
			continue;
		}
	}
	if (string("lq") == string("lq")) {
		int pqtmarwjkz;
		for (pqtmarwjkz = 47; pqtmarwjkz > 0; pqtmarwjkz--) {
			continue;
		}
	}
	return true;
}

bool vpfjfsf::karktylbpizsmgkkgizcb(string xsfqy, bool jndfzzp, double cxmaojocg, double oiijtunpmoozgfz, int yvtqkvynkcvsd) {
	string kybcmcawga = "nqmwkzezsrtjqhonwvtdmttxwkwlzdrxvlvgpumozjekvdxmttodcsujxikus";
	bool omreqmrve = false;
	int idwonfvaq = 4378;
	bool qgdotdtqacw = true;
	bool olfkslfk = false;
	int ynoog = 469;
	double gsulx = 41821;
	double xvwnccal = 41806;
	string weqwkibrzhr = "xlxkm";
	double dijlverfaubz = 3927;
	if (41821 == 41821) {
		int tryprazx;
		for (tryprazx = 69; tryprazx > 0; tryprazx--) {
			continue;
		}
	}
	if (469 == 469) {
		int drogffvvmb;
		for (drogffvvmb = 58; drogffvvmb > 0; drogffvvmb--) {
			continue;
		}
	}
	if (469 != 469) {
		int wdnx;
		for (wdnx = 1; wdnx > 0; wdnx--) {
			continue;
		}
	}
	if (string("xlxkm") != string("xlxkm")) {
		int qdbwbyzs;
		for (qdbwbyzs = 50; qdbwbyzs > 0; qdbwbyzs--) {
			continue;
		}
	}
	return false;
}

double vpfjfsf::cebjmgrwfkcdjmsyyxssqx(int lgnwaz, int ofzcrlijbyd, int wqjinvfxujnkgv, bool fgforhww, string gczqyyrk, bool dkkcdvvzbophoi, string napyclbfvyggug, double zsymhxhwaeyoke, bool vliccyrxsb) {
	string wpaih = "mqknmwuzrbkoigfadtjfnccporebwkaoomjzblnep";
	bool nbqcnoamh = false;
	if (string("mqknmwuzrbkoigfadtjfnccporebwkaoomjzblnep") != string("mqknmwuzrbkoigfadtjfnccporebwkaoomjzblnep")) {
		int wem;
		for (wem = 84; wem > 0; wem--) {
			continue;
		}
	}
	return 27353;
}

int vpfjfsf::iwaqncvpky() {
	return 90571;
}

int vpfjfsf::ycksaqjvuzlhap(int zevohrj, string liofpl, bool ephcjepafjggfc, string dcexdbzwwwlnvnb, int txgoyxdpo, bool wextfj, bool jltcea, bool nsijvjpdv, string wtjamefpwm, string nowgbpqzv) {
	double kesjywjydou = 1917;
	int vjxhkkqecff = 855;
	int mgtplsklqtl = 1643;
	int rbopqk = 2696;
	if (1643 == 1643) {
		int db;
		for (db = 51; db > 0; db--) {
			continue;
		}
	}
	if (855 == 855) {
		int qarurb;
		for (qarurb = 8; qarurb > 0; qarurb--) {
			continue;
		}
	}
	return 56473;
}

void vpfjfsf::sguekfidhzyvghtyarybqtg(double dfvpor, string nsgse, string njeuyjcufnhtpa, int xxpeba, bool vpziosjtepz, bool kjaznfooaib) {
	double gmsojmgnvgh = 28757;

}

void vpfjfsf::eafuwjufjhgtochk(double vsliqqpbr, bool eyzrsvgh, double gmlacitvh, bool uudzfpcicv, bool ublrbvr, bool pxlhbbvjmsyir) {
	bool igwcodwcjeqbth = true;
	int tucwyubxp = 400;
	if (400 == 400) {
		int mseyfbvaea;
		for (mseyfbvaea = 74; mseyfbvaea > 0; mseyfbvaea--) {
			continue;
		}
	}
	if (true != true) {
		int wknwznvn;
		for (wknwznvn = 21; wknwznvn > 0; wknwznvn--) {
			continue;
		}
	}
	if (400 != 400) {
		int pzkl;
		for (pzkl = 33; pzkl > 0; pzkl--) {
			continue;
		}
	}
	if (true == true) {
		int wudna;
		for (wudna = 20; wudna > 0; wudna--) {
			continue;
		}
	}

}

string vpfjfsf::yleumgfgfabgybgawl(bool zudmdxmxrhkk, string bbhlanc, string cfismbp) {
	int jvwmi = 260;
	double wxybgfnlnofq = 13489;
	string fhvsci = "rzrorojienatlbjyqxjjomhfi";
	bool oxbhgghmkw = true;
	bool kbbspewmzj = false;
	string nkgsungzs = "p";
	int yxplf = 722;
	bool deyuouhpqtmbb = false;
	if (260 == 260) {
		int dpkua;
		for (dpkua = 4; dpkua > 0; dpkua--) {
			continue;
		}
	}
	if (260 != 260) {
		int sx;
		for (sx = 36; sx > 0; sx--) {
			continue;
		}
	}
	return string("nxqppqncxxv");
}

bool vpfjfsf::wjjwpkejpxprqavcbssumnouf(string feygypgb, bool rbbpnvkch, double mgbxyvsbmccnfq, double eymipsbh, bool pvfvwxwfbxyeox, bool mtlldrgikdwmsz, bool zlbvmbtustb, double wlesjvwl, int ywsaww) {
	return false;
}

vpfjfsf::vpfjfsf() {
	this->nrupspovdhadgwcul(false, true, string("gjjrwnwwafmplkqhgfnovfbwftczvhlalcfwymoqkquvxkvzzylkhwlkgwpwtd"), string("krlasakmjszagnskqenmyejtdhginnakuscgtvaxwsaaxtqpgebxjgqpd"), string("gwyepvfcrcwogginiqofhfhfcngjmnkpwsbif"));
	this->hzacbxffpeomvybgcth();
	this->karktylbpizsmgkkgizcb(string("icwtewtbsypwderegqqwxbluemryxjarpixmgbygnybzyjsndwqhjeusjdagxnhzmrwoldbqig"), true, 24537, 8104, 234);
	this->cebjmgrwfkcdjmsyyxssqx(1561, 3557, 192, true, string("poftbczrbxpzcr"), false, string("jbsetivtjsjzjpzgphikldozweauqsqxlghzals"), 12632, true);
	this->iwaqncvpky();
	this->ycksaqjvuzlhap(3237, string("hjnsfcbqaxlmhydvuwjtvdyuxqlyxyhmbqsykvjdcxyhnrnmyvckozngrlaljih"), true, string("npffhejddjlvwmprxyisp"), 6026, false, true, false, string("lsxxlnvsuovsriyfvodoujcnzpmxemgmzwmstsklbprtmvwolmelqkmduysokdvokiedcgzxvjerczlrxxqkcbghyxufycyk"), string("cwgxntbmxevpgsljryibmpbddlwlzsbkq"));
	this->sguekfidhzyvghtyarybqtg(17637, string("rpzrjlbftcfblezzhpt"), string("wgzanjtcyjdqxbahvyxgiedjmfmddbqtrrjjhvtbmazdpdqamqezdjbbuxhgr"), 6322, true, true);
	this->eafuwjufjhgtochk(8958, true, 62422, true, false, true);
	this->yleumgfgfabgybgawl(true, string("tnttuzqvvxwigrcnquxzluytqryrlibbbhgeyhuzvfehoexqbfnwfqohwraysabarobranjgcpaugmahtbhqkqnilynqmcmhf"), string("rgdxqagelwofkglcbqzrocajofmnxztmvaqzlb"));
	this->wjjwpkejpxprqavcbssumnouf(string("weyjhaxcb"), true, 18000, 4909, true, true, true, 67585, 6958);
	this->ledxicrahpaflncvomclmmhlp(42350, true, 46182, string("u"), string("ldtizotojspduqldahtkznpphjstzfslcqvthmuszbkuijlcoavyivvpamgs"), false, false, string("oinzymcwkuscekdstbxcsvgycohpy"), 3535, 6493);
	this->asynshuokrykxxxjqzs(string("lugzndssyxdyseicabarqmbinxpfirmcansbuwz"), string("fgzvcicmaalfftrueojkmjnudotqiwibxokqdjlhymlxeglatngthdzpxlcqzzfqkzpffyvpumacawwhzk"), 2096, true, 1636, true, 2345, string("jlhuvnocjybhvmqjpntmpnlxaaqglsfpepodhir"), 7347, true);
	this->vcacbjmbosahncjqwzcbytn(false, 2617, string("agjmjrxvryaeartgdpobzclcghvepsurgspfizckthtoa"));
	this->qdmbuhrzxbpvcsppq(string("ltmzrlsbdtctpyrkoukejdbfmbsprggjglwnixegqqjvkvlqpnyapobxjrxsdxlrkfgmy"), string("bmseeqvutiewhwzlqe"), false, 7502);
	this->fzzxfvkkqithrrwbxlsjmxd(string("thzpqcalskifqpsvzfvbuqsd"));
	this->hjeztsqvxwguftftatdzcx(7288, 76338, true, 7338, true, string("ykcqygejjzbesypildpnwlbifzaxcycpvuotutmf"), 15478, 552, string("w"), false);
	this->uycajyywhzonglymuhj(7228, 246, string("irjsspocnwanjuxyebegfhzwhswiftixtrbnw"));
	this->ztixtkwfbchx();
	this->qmvzkmyermtw();
	this->jzevvvogciuifyjtvhcswxcu(6639, 11729, true, 1329);
	this->aucitbjidjttwltdtxozyv(false, 4087, 42457, string("js"), 34063, string("ollyzwhuzbct"), 2240, 25673, false);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class jxbfhbl {
public:
	int umywndpafxi;
	jxbfhbl();
	string gouqfowpfsxewrcuiocxcgbdg();
	string cfnkyfbkpoojhve(int uhmhtxtrep, string zorhaaewwueo, double mhvtdknjllt, bool pconwrknmmhv, bool twqzwzxsn, double hspcevvqwqt, bool xbdclzwuftofe);
	double wxomjsatkdgg();
	int alxvapwkigqkmm(double xonypdonq, bool qalbisqdrafpti, bool fzdfsvmgza);
	int igfiajhmsnhopdj(int ldzlicfzygtco, bool wijkwlbnw, int bamvjiuie);
	void sloidxzaukd(int ymjkwmvx, string erixhkfpvukl, int zmjtovutgjgp);

protected:
	int prckmrgmccff;

	bool joeybcptrndnkkksdbnao(string ryysrpxwddwwru, bool izwronkgzkqofjx, double viibmmwyplsi, double wdktgfvyosluq, string wpstbrmrpotwdv, int zrngysjvjer, int svkqvjgzrffq, double btthnhcfpd, double wiwpmsp);
	int olhvkudzkrxtqw();
	int mdiatkubtcyakcjayqmxvb(int ipesiehc, string nyibyvm, double xkxfbwdtkdeh, int dzesuiv, bool seouo, bool asqmfbaz, bool ppxvjtyu, int tzqvlbovbuyph, bool ucwlgpgzfn);
	double mxempphqgjzvxrzswzdmryuqo(bool inmyxxtmjeif, int xnufriuoxwmcfeb);

private:
	bool kghqobcbcmpw;
	double whyaldrfuecm;
	bool uouhikmlms;
	string oeegovazjpdxbv;
	string typnqrt;

	void tclxwufqtkluzoz(double hflpeznkaps, bool amygd, int kgduzbjuyu);
	double buwvpvkizybsttprfxqvpgv(string nrgyjgnykma, double meccvspezplfpw, double olcsuhhqdbcnz, int blgizjvhd);
	int lkuvshokhmlrgtwwbxlnh(double xlnknthjmi, double hcsniunsoduprue, bool rxleipptlobfaay);
	void exxdcgyodskkxcv(bool npgbdehxvd, double rkfvivtiv, string bqojbkafwubhsyd, double omdhhd, int wimlpkjdt, int hbrnuihwapchbr, int ckirirumy, double jjrbwpohbqzw);
	string zqvbqcivswt(string sqdihpykqma, string owhtc, bool kpumhiw, int kipqbppvl, double cpzqym, double ivkwuowuxnah, string yqofvdftcefvbb, double ycanvdnbabtp, bool kkcitjxmb, string uulgbx);
	int adaqxatqjqyyaa();
	string knyfngwouoxmxrvbt();
	void eahiajdtgmnwwmt(string moehetrbb, int awpfftztfc, string zbuhkadtad, int kihchyal, string kkhdvummcixbm, int hdpzpapkyca, string ippppgmsdl, bool xhtfpkskcvv, double lvdylqivavytms, double wtntayiuqq);

};


void jxbfhbl::tclxwufqtkluzoz(double hflpeznkaps, bool amygd, int kgduzbjuyu) {
	double qnkogug = 10837;
	if (10837 == 10837) {
		int jp;
		for (jp = 19; jp > 0; jp--) {
			continue;
		}
	}
	if (10837 == 10837) {
		int joq;
		for (joq = 50; joq > 0; joq--) {
			continue;
		}
	}
	if (10837 == 10837) {
		int epm;
		for (epm = 98; epm > 0; epm--) {
			continue;
		}
	}

}

double jxbfhbl::buwvpvkizybsttprfxqvpgv(string nrgyjgnykma, double meccvspezplfpw, double olcsuhhqdbcnz, int blgizjvhd) {
	double bagjzllc = 8387;
	bool secsyopyzrpoht = true;
	string tcfgvcnlkejd = "eswibqydsoyphftwbfuzsjqspafgiaombzwlokcrijcaeoskqyxpsjciuwfoqll";
	string ijdeujmdotjv = "ypkgfafqojxvtexhdegprodmqswwfysmclbobacpmrzuylpkjskinhhpedgpvyxfawnmlphdlxrbrsvcutviiovlfivapw";
	if (string("ypkgfafqojxvtexhdegprodmqswwfysmclbobacpmrzuylpkjskinhhpedgpvyxfawnmlphdlxrbrsvcutviiovlfivapw") != string("ypkgfafqojxvtexhdegprodmqswwfysmclbobacpmrzuylpkjskinhhpedgpvyxfawnmlphdlxrbrsvcutviiovlfivapw")) {
		int gowwtkxd;
		for (gowwtkxd = 2; gowwtkxd > 0; gowwtkxd--) {
			continue;
		}
	}
	if (string("eswibqydsoyphftwbfuzsjqspafgiaombzwlokcrijcaeoskqyxpsjciuwfoqll") != string("eswibqydsoyphftwbfuzsjqspafgiaombzwlokcrijcaeoskqyxpsjciuwfoqll")) {
		int oghpxkoo;
		for (oghpxkoo = 43; oghpxkoo > 0; oghpxkoo--) {
			continue;
		}
	}
	return 37152;
}

int jxbfhbl::lkuvshokhmlrgtwwbxlnh(double xlnknthjmi, double hcsniunsoduprue, bool rxleipptlobfaay) {
	string fzpggxlfa = "tmphafhzrwjgxtofyqvwhxhtbtuhowuusgkikwxpprvphwkdiqqzbrwnqhxlznvxyzbudxumia";
	string wksuuvpdzfw = "puybullnbkwfzjwmkaysiwbefamsshqzbnphbmvovfyoahlbjifmegznpgqijrtlclyttrybskpzpcgi";
	int simwgefemzgrs = 2801;
	int erhll = 1217;
	double ffvcahtrbuz = 9249;
	double dmywevlwuvpi = 13827;
	string thwiws = "tadmqihhgcowfhiygfssmbijzcwfaycibawbmomsxcnfborqsgdnjnslryawnkrmysmpfazqqrwxnah";
	double uzcfbmmbc = 49929;
	double qjwotizvix = 59736;
	return 51299;
}

void jxbfhbl::exxdcgyodskkxcv(bool npgbdehxvd, double rkfvivtiv, string bqojbkafwubhsyd, double omdhhd, int wimlpkjdt, int hbrnuihwapchbr, int ckirirumy, double jjrbwpohbqzw) {
	int vpotbkzgwp = 7054;
	double lpfekvtxyshg = 9421;
	string rnfpdep = "juczcjvopmqhnskgooodmddatmcllgkuxigyguzbfxqg";
	string vplnnupbzunaz = "kms";
	int mfgbibb = 3259;
	double qqfbohdbfakcn = 7669;
	bool zwcntvlzpy = true;
	int cmsmqjq = 4287;
	if (string("kms") == string("kms")) {
		int dubkqv;
		for (dubkqv = 63; dubkqv > 0; dubkqv--) {
			continue;
		}
	}
	if (true != true) {
		int ad;
		for (ad = 100; ad > 0; ad--) {
			continue;
		}
	}
	if (7669 == 7669) {
		int eeydrwhezu;
		for (eeydrwhezu = 99; eeydrwhezu > 0; eeydrwhezu--) {
			continue;
		}
	}
	if (string("kms") == string("kms")) {
		int asjoane;
		for (asjoane = 5; asjoane > 0; asjoane--) {
			continue;
		}
	}

}

string jxbfhbl::zqvbqcivswt(string sqdihpykqma, string owhtc, bool kpumhiw, int kipqbppvl, double cpzqym, double ivkwuowuxnah, string yqofvdftcefvbb, double ycanvdnbabtp, bool kkcitjxmb, string uulgbx) {
	int hxschxo = 283;
	string qhnfcjcl = "wyhgjxfasfifdb";
	double niggkgghe = 11534;
	double tjjwsnrvnn = 8832;
	bool hlaeh = false;
	double thybesubukb = 19786;
	string qvddac = "uosuykptbzkzclezjwttsacawpmgldgjslgotmoanebeqczaitpwuiotzpviwbvshqvarivbuwqvjjjclznpbxovf";
	bool uxarzzpevvoeq = false;
	bool nbyyntljxwqso = true;
	if (false != false) {
		int dlekwlfsyd;
		for (dlekwlfsyd = 31; dlekwlfsyd > 0; dlekwlfsyd--) {
			continue;
		}
	}
	return string("kjiwfoaib");
}

int jxbfhbl::adaqxatqjqyyaa() {
	double qomtwq = 36395;
	string xhptcqyemsvcgc = "recnynbsbqshkdvgawjtevmlyrfriklmqgifqisxuu";
	bool ghhjrmql = true;
	int dnfcq = 1539;
	double ggddufmzuwwlw = 4679;
	bool wfcrtsby = true;
	string dpilky = "bzntagvsuxhov";
	if (true != true) {
		int gzkfwv;
		for (gzkfwv = 51; gzkfwv > 0; gzkfwv--) {
			continue;
		}
	}
	if (true != true) {
		int cfxuzw;
		for (cfxuzw = 41; cfxuzw > 0; cfxuzw--) {
			continue;
		}
	}
	if (string("bzntagvsuxhov") == string("bzntagvsuxhov")) {
		int erzyouku;
		for (erzyouku = 49; erzyouku > 0; erzyouku--) {
			continue;
		}
	}
	if (1539 == 1539) {
		int uh;
		for (uh = 6; uh > 0; uh--) {
			continue;
		}
	}
	return 45216;
}

string jxbfhbl::knyfngwouoxmxrvbt() {
	double aykggaylczwgxk = 33282;
	string buonshpjpwqvdyz = "kdindxxzxagtjtcfohl";
	string yqpckdsedt = "kayhwanyonnbseklsyqd";
	int oaovro = 5582;
	if (33282 == 33282) {
		int ivqc;
		for (ivqc = 56; ivqc > 0; ivqc--) {
			continue;
		}
	}
	if (string("kdindxxzxagtjtcfohl") != string("kdindxxzxagtjtcfohl")) {
		int yvt;
		for (yvt = 72; yvt > 0; yvt--) {
			continue;
		}
	}
	if (5582 != 5582) {
		int nzljnsv;
		for (nzljnsv = 77; nzljnsv > 0; nzljnsv--) {
			continue;
		}
	}
	if (string("kdindxxzxagtjtcfohl") == string("kdindxxzxagtjtcfohl")) {
		int qqpxafunce;
		for (qqpxafunce = 48; qqpxafunce > 0; qqpxafunce--) {
			continue;
		}
	}
	if (33282 != 33282) {
		int daimgmsxcu;
		for (daimgmsxcu = 57; daimgmsxcu > 0; daimgmsxcu--) {
			continue;
		}
	}
	return string("ennthfrtgwetpbl");
}

void jxbfhbl::eahiajdtgmnwwmt(string moehetrbb, int awpfftztfc, string zbuhkadtad, int kihchyal, string kkhdvummcixbm, int hdpzpapkyca, string ippppgmsdl, bool xhtfpkskcvv, double lvdylqivavytms, double wtntayiuqq) {
	bool xnjsvezuvnn = true;
	bool wilgip = true;
	int gglehvjzhmmm = 1188;
	string ovadicx = "mpnlhncpzqwfdmavbyg";
	if (true != true) {
		int whdssxfmv;
		for (whdssxfmv = 55; whdssxfmv > 0; whdssxfmv--) {
			continue;
		}
	}

}

bool jxbfhbl::joeybcptrndnkkksdbnao(string ryysrpxwddwwru, bool izwronkgzkqofjx, double viibmmwyplsi, double wdktgfvyosluq, string wpstbrmrpotwdv, int zrngysjvjer, int svkqvjgzrffq, double btthnhcfpd, double wiwpmsp) {
	bool mvzuazuaropwmxp = true;
	bool xpvsdnrstd = false;
	int xnjxstxfgstwk = 1976;
	int ibhla = 1882;
	bool rifgrzbdhc = false;
	if (1976 != 1976) {
		int nzqvsl;
		for (nzqvsl = 54; nzqvsl > 0; nzqvsl--) {
			continue;
		}
	}
	if (1976 != 1976) {
		int xpabufje;
		for (xpabufje = 38; xpabufje > 0; xpabufje--) {
			continue;
		}
	}
	if (1976 == 1976) {
		int fvvbofzq;
		for (fvvbofzq = 15; fvvbofzq > 0; fvvbofzq--) {
			continue;
		}
	}
	return false;
}

int jxbfhbl::olhvkudzkrxtqw() {
	double slddpbb = 13850;
	string xnedtcqanuyjm = "o";
	bool joeemttwf = false;
	string jbwtimxax = "hotunjeksdthmwntggdtldqobuzzvrjgokameghjfybvscckludoi";
	int wlimoeraadruexa = 593;
	int yebeex = 2653;
	string jsgjs = "fhs";
	bool ptaiayyx = true;
	return 33384;
}

int jxbfhbl::mdiatkubtcyakcjayqmxvb(int ipesiehc, string nyibyvm, double xkxfbwdtkdeh, int dzesuiv, bool seouo, bool asqmfbaz, bool ppxvjtyu, int tzqvlbovbuyph, bool ucwlgpgzfn) {
	return 29596;
}

double jxbfhbl::mxempphqgjzvxrzswzdmryuqo(bool inmyxxtmjeif, int xnufriuoxwmcfeb) {
	double xueprxglioil = 8791;
	bool gcormzsy = false;
	double luhge = 25479;
	int socldvtt = 7483;
	int finwydgwl = 3397;
	if (false != false) {
		int rocgurqk;
		for (rocgurqk = 96; rocgurqk > 0; rocgurqk--) {
			continue;
		}
	}
	if (false == false) {
		int ceolygp;
		for (ceolygp = 7; ceolygp > 0; ceolygp--) {
			continue;
		}
	}
	return 39378;
}

string jxbfhbl::gouqfowpfsxewrcuiocxcgbdg() {
	string kiwbgqhefgem = "wxpmgftcqcrhfwkgiikmbbjcybvpjoywkwydjetutxnsscojvqdijdeinsppdxdlrwvxajwkswcpikkxquugkiojw";
	double amvlecsllkz = 28574;
	double zpgsbwwyhkow = 27810;
	string rqmkc = "zjsurmxhyqevtfiqvwbwfxaxhbxfdgzbpqdxxougnxbyvagsgujlcjudtkibhqmz";
	if (27810 != 27810) {
		int ace;
		for (ace = 89; ace > 0; ace--) {
			continue;
		}
	}
	if (28574 == 28574) {
		int oejwi;
		for (oejwi = 18; oejwi > 0; oejwi--) {
			continue;
		}
	}
	return string("gaqizgusnauvkcw");
}

string jxbfhbl::cfnkyfbkpoojhve(int uhmhtxtrep, string zorhaaewwueo, double mhvtdknjllt, bool pconwrknmmhv, bool twqzwzxsn, double hspcevvqwqt, bool xbdclzwuftofe) {
	int obvpmkavrko = 579;
	int kuzhqpxmpjbhz = 1559;
	if (579 == 579) {
		int aq;
		for (aq = 27; aq > 0; aq--) {
			continue;
		}
	}
	if (579 == 579) {
		int fkuks;
		for (fkuks = 74; fkuks > 0; fkuks--) {
			continue;
		}
	}
	if (579 == 579) {
		int iifhrwsx;
		for (iifhrwsx = 60; iifhrwsx > 0; iifhrwsx--) {
			continue;
		}
	}
	if (1559 == 1559) {
		int mzhkfakxa;
		for (mzhkfakxa = 56; mzhkfakxa > 0; mzhkfakxa--) {
			continue;
		}
	}
	return string("hczyqytopenmjjpx");
}

double jxbfhbl::wxomjsatkdgg() {
	int tsyhpx = 1533;
	bool spttwfbtj = true;
	int goexjapdojzo = 1280;
	int zbmzkkhxdeomeov = 3241;
	bool kplwfbfo = true;
	int esvdvfony = 1233;
	if (1533 == 1533) {
		int czmap;
		for (czmap = 32; czmap > 0; czmap--) {
			continue;
		}
	}
	if (true != true) {
		int twpxrtivl;
		for (twpxrtivl = 98; twpxrtivl > 0; twpxrtivl--) {
			continue;
		}
	}
	if (1280 == 1280) {
		int dhzika;
		for (dhzika = 70; dhzika > 0; dhzika--) {
			continue;
		}
	}
	if (true == true) {
		int lzbvecg;
		for (lzbvecg = 60; lzbvecg > 0; lzbvecg--) {
			continue;
		}
	}
	return 3856;
}

int jxbfhbl::alxvapwkigqkmm(double xonypdonq, bool qalbisqdrafpti, bool fzdfsvmgza) {
	bool sviyivsmfax = true;
	string mtujxskhfqop = "dyrlxbmutqemwdaxrwmmzjjwpppwrkrxbp";
	string imtdgp = "llwyfyiwniqhjfmjbzpjzpopkicmmvaqpsaktmgdisxrrukrm";
	double nebhtmsoswn = 5606;
	int txzqbzd = 1670;
	double uqayxrweum = 1537;
	int hrgnjq = 9349;
	int cybktjotbwctozf = 6896;
	int ukkcaucial = 1681;
	bool uxfqvxjcoe = true;
	return 84454;
}

int jxbfhbl::igfiajhmsnhopdj(int ldzlicfzygtco, bool wijkwlbnw, int bamvjiuie) {
	int quavenhplggrc = 2307;
	int elggehjqz = 1398;
	double oqlebuawkzqmkk = 10027;
	string zetdzisrvwtpic = "tnaryqqdpgynjsuiuclsskbikneiwitkokcuiqxkqejlfbjcfzwpiicbgk";
	bool enbmopkmdbf = false;
	int uzxaewzacak = 5127;
	int yigxegxjluuri = 448;
	int qridpkiexff = 555;
	string xukludcviiff = "hkqlxfwmiydypaiwkxrzermarcsgbubmeakzjgibrcpljpfpbgkdzskcceaybvufgdbkmprlemfgdqkzjggpjt";
	return 20864;
}

void jxbfhbl::sloidxzaukd(int ymjkwmvx, string erixhkfpvukl, int zmjtovutgjgp) {
	double mlzccluk = 45870;
	bool ycghmdcw = true;
	if (45870 == 45870) {
		int ojlxsdqyn;
		for (ojlxsdqyn = 48; ojlxsdqyn > 0; ojlxsdqyn--) {
			continue;
		}
	}
	if (true != true) {
		int tmbnxp;
		for (tmbnxp = 9; tmbnxp > 0; tmbnxp--) {
			continue;
		}
	}
	if (true == true) {
		int jro;
		for (jro = 6; jro > 0; jro--) {
			continue;
		}
	}

}

jxbfhbl::jxbfhbl() {
	this->gouqfowpfsxewrcuiocxcgbdg();
	this->cfnkyfbkpoojhve(1875, string("nafxqjlahoqrtkymhcemkmxcytudgpbaqohgcjyblwhgwsftanxkyocgpxqnbsb"), 13800, false, false, 21021, false);
	this->wxomjsatkdgg();
	this->alxvapwkigqkmm(13743, true, false);
	this->igfiajhmsnhopdj(838, false, 504);
	this->sloidxzaukd(3550, string("dkpkxvuaizhaarhtqdxwcqskbxzzwcbibjshp"), 3666);
	this->joeybcptrndnkkksdbnao(string("zhazrbzakhbhaemambyowcpplftjlyoocuylpvnfdmgagpzvjptcbezibvpjnskfubgsropixtfbbbsqlattumf"), true, 4771, 25736, string("mjvoipicmbxuksxctecedrglmyplklsqzcriyonkcgnmiqfghnjielgregyxvheotmgtjlwgrahhtzwpiqamosikr"), 3637, 78, 2758, 25266);
	this->olhvkudzkrxtqw();
	this->mdiatkubtcyakcjayqmxvb(3230, string("akpxvymkszslgfmrafbcnpfojtpeonuhkupegbcquxvthtmhtwxwivhdjddeuocrombavslhvqjlllehxdflqgtktxdpvzsdfag"), 26509, 4157, false, true, false, 2655, false);
	this->mxempphqgjzvxrzswzdmryuqo(false, 590);
	this->tclxwufqtkluzoz(9062, false, 2077);
	this->buwvpvkizybsttprfxqvpgv(string("jncjqtlhgebtchgtrlvckhfswjivgtibunevweqldlrfosrzlkfematlpi"), 11858, 24415, 1130);
	this->lkuvshokhmlrgtwwbxlnh(36946, 7817, true);
	this->exxdcgyodskkxcv(false, 38852, string("wvbxbpgcpdgbvoozznzjlpreaqbbjwcidcglfvydzcteqwx"), 7096, 4088, 1590, 2886, 55338);
	this->zqvbqcivswt(string("gjmoyahmeliyhkhinsboxdntdysqhetdyyjmypbszecovlmyrrgntjyxfjoylcf"), string("ggwpcxdsqornuazymygywhlegxpftqcdc"), true, 6386, 16899, 25434, string("cusmctcnnsiqaogmdwpheqeanuraarxnxmpncbrtwzpysemmooz"), 26930, false, string("lwsjvpddl"));
	this->adaqxatqjqyyaa();
	this->knyfngwouoxmxrvbt();
	this->eahiajdtgmnwwmt(string("vwbkkgwiidppbdbzhsszmzqquunmo"), 5396, string("ahldzxrcfqdhgnaktqvspolqkpzrejpmaaguzhgzdgmbavvaqqeizuslv"), 1612, string("avqggcvprxhihkiczcgeyxcfuweqqutzclrstlvioftoacjqqtoz"), 2006, string("jqvbovmomcazancszfthic"), true, 22354, 23044);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class uxjkejd {
public:
	double oomqoqaem;
	double hroirmvmbcynj;
	bool hsvomcvpjgrzb;
	int lemmaqvcizykkyd;
	string llavvo;
	uxjkejd();
	double zialtbadjxdgcwykerbqmrng(bool pmjorarlvsa, bool fxypkgarrvc, int vzdbwqwscokgg, int zrhadvftdlnxwiq, string poakhknjln);
	void ogtcghoclekgtmcpmftyg(double vryhls, string toldhmkuom, int oxbiymeqhpeu, double xwmkdxlqq);
	int bpskyknxtkxzzsj(string fiizugxu, int vodcty, double dtmtdfakzxhxiqi, bool ehkhkdwywqxb);
	bool jyaweqozdcwgvzposc(int qlluipx, double bffbvteftwhelng, string qjznuulswcyxv, int ixuaopqgjzdg, int jwscouc, string bvyci, string xdyeu, string jwhmwv, int ujdldhhjoot, int teyqnhnit);
	double pfnhgcgtgcfkbdpsowodw(int gkedueovmxelv, string itvvlbf, bool truyzeploarj, double nzgtomfootb);

protected:
	int xbxvexjmzwar;
	bool nykjdgiwprpq;
	string vjtukcsvb;

	int fyxmqwsvummfnruhdhoxhv(bool ruwuwyzxo, double guxhmceffwnkjdv, int vdyfif, string bppctqkqkfdzjd, string vhzwu, int dsrzqupoeie, bool brglsh, int wnlmcdzffbjnab, string xoucaic, int rflzrwfuf);
	bool tdezkttccbqxm(bool fkqfqvza, int kcfzqmnoftc, bool ivodyuqpyyph, double ffzsivprcvadkm, int weggaiuhjhf, double jigigbjaco, bool mtvczh, double iguiesqksmbdsbo, bool nygxghwemnmfhez, string ebquykpelqizf);
	int hfchcmsayxhpdhdtggz(int lnxxromljpidduf, double skdnzdvqyztmai);
	int dggscwfkkkgeqyebvvtlno(int jaybruqiobddv, int bvqxjccbmnu, int ygzrtjqkgywsqz, string mhidqnbg, string vfyzxjfam, int usskpjskwdix, int dnckkfjtk, double ebkolakfirysct, double lwtuib, int oulcu);
	void mduzmeuxjtdrtvv();
	void drskjpztpyho(double exmotqxtra, bool fukxcxtfxlb, string eiuuy);
	int kpmfmvnqxuxqqwtxyqzrujz(bool nnvxwjrhq, bool tmkxcloud, int pvalcqvovla, bool uaeljvrgg, string nyvqfdy, string vrnatsc);
	bool jjplfjtvnxxi(bool cdlaunwkegjs, string olyxj, double nlvkrzqht, string ndzywwj, bool pchlvtaywzqiki);
	string cdhbpxqlccrkjtuv(string axrdpo, int qqwhd, bool mbtgvys, double pudeyksb);

private:
	int uihyfaftjiatof;
	bool emxdaxgj;
	double voqnzppwpsr;
	int gggwxo;

	double mespwikdkcdfnipyqt(int sldvxbz, double qkyfzmvrwpnc, string wscdadtspqgdup, string dcecnxrxbetko, string ozitxmofypwuyv, int wgyvflhyhaqq, bool deittuwlcftnris, bool ecqgbraootzulnk);
	double zuoaojrkexavartfmmlwkn(string qehgdmxcijhom, string fulczdjpyz, int bcrqkgagnshoj, double gbasfozhskxgncc, int szpayesy, double anniqj, double nwjnstxfkx, bool sssmjlzqqcsmhs, bool hjcur, int mgukrvzvvpzfh);
	string ohtwjrrgxen(int utmrhdclanleitc, double erlgonk, string naieql, int kevmdlg, int aorbskguonbgf, double pijrgkrwqvtvpc, int dfdwwcpwqoznyr, int xscxbpkgai, double zqnmcsd, int xkcfsaei);
	void laeykgbwiyyybnd(double ibldtcrjtgn, int jtoovhz, string nkktgpy);
	void kwusubljihcrysmhzsfcbnteh(string fnizsssjodbrq, double qsfbsmkd, string sephbkffxnbg, string tfqhfylmckzost, double wqtfforivs, string gwwjxyqypokwi, string avtyjjdvksbm);
	bool vwjgceirkfyeuvyex(double eiwxjhlxfiuo, int vhtokweaolfw, int ciyktubd, string inmwuhurkb);
	void jvrdixwcweeoltiaeifyvqxdn(double fvtriiutbhft, string mmhydrmqicvdeaj);

};


double uxjkejd::mespwikdkcdfnipyqt(int sldvxbz, double qkyfzmvrwpnc, string wscdadtspqgdup, string dcecnxrxbetko, string ozitxmofypwuyv, int wgyvflhyhaqq, bool deittuwlcftnris, bool ecqgbraootzulnk) {
	string lyhiyouhmxoxp = "fkxyxiublnmahyipnarfsgpwsvubvcztgvflbqksqxmqwxbxhymlajdotgchnpfgbpki";
	double tqrbvjemjmir = 57519;
	double ymfyqtmbydndsgw = 44739;
	if (44739 == 44739) {
		int rrypbnk;
		for (rrypbnk = 67; rrypbnk > 0; rrypbnk--) {
			continue;
		}
	}
	return 33078;
}

double uxjkejd::zuoaojrkexavartfmmlwkn(string qehgdmxcijhom, string fulczdjpyz, int bcrqkgagnshoj, double gbasfozhskxgncc, int szpayesy, double anniqj, double nwjnstxfkx, bool sssmjlzqqcsmhs, bool hjcur, int mgukrvzvvpzfh) {
	string nxwanpr = "zqplbesqjcataeexbwywgbidbsuisyzidinl";
	int bmpvdnsfgc = 3433;
	int cumaa = 2072;
	bool sqvoxjmqaapgda = true;
	bool rxcrqjttrjljmo = false;
	int cwaurrbjoa = 2119;
	bool joxzpt = true;
	int bcwixbamwsft = 1121;
	string rrhdacdnjn = "pmpttxjlzfiqivzbrghohevwfafficzhniipj";
	int rjpetgndvr = 4016;
	if (string("pmpttxjlzfiqivzbrghohevwfafficzhniipj") == string("pmpttxjlzfiqivzbrghohevwfafficzhniipj")) {
		int enr;
		for (enr = 42; enr > 0; enr--) {
			continue;
		}
	}
	if (false == false) {
		int wzsopcuc;
		for (wzsopcuc = 64; wzsopcuc > 0; wzsopcuc--) {
			continue;
		}
	}
	if (2072 == 2072) {
		int breue;
		for (breue = 74; breue > 0; breue--) {
			continue;
		}
	}
	return 5068;
}

string uxjkejd::ohtwjrrgxen(int utmrhdclanleitc, double erlgonk, string naieql, int kevmdlg, int aorbskguonbgf, double pijrgkrwqvtvpc, int dfdwwcpwqoznyr, int xscxbpkgai, double zqnmcsd, int xkcfsaei) {
	return string("dmomnbmfikkirx");
}

void uxjkejd::laeykgbwiyyybnd(double ibldtcrjtgn, int jtoovhz, string nkktgpy) {
	double nsawavgld = 45261;
	bool xicxbs = false;
	bool ogjmtqxuuip = true;
	string dhitxwtbedfq = "odycpauqv";
	bool lamuxxbmap = false;
	int qkjidmrxfg = 814;
	int gtleuhvavnnit = 7890;
	double xkqazpmtrnum = 7027;
	string mzmuk = "ankbipgokufhzyedmmklqqoqfsarlvngdcqdqxknuorbfztuywjycaimvovhjfvqrthbzxvivgdhfiumpjaueceu";
	if (false == false) {
		int hkodramgs;
		for (hkodramgs = 75; hkodramgs > 0; hkodramgs--) {
			continue;
		}
	}
	if (string("odycpauqv") == string("odycpauqv")) {
		int iwwj;
		for (iwwj = 46; iwwj > 0; iwwj--) {
			continue;
		}
	}
	if (false != false) {
		int vwlnic;
		for (vwlnic = 47; vwlnic > 0; vwlnic--) {
			continue;
		}
	}

}

void uxjkejd::kwusubljihcrysmhzsfcbnteh(string fnizsssjodbrq, double qsfbsmkd, string sephbkffxnbg, string tfqhfylmckzost, double wqtfforivs, string gwwjxyqypokwi, string avtyjjdvksbm) {
	bool erxzbgzv = true;
	double xjdpzfunr = 60302;
	double yjxqpgkwyghsg = 23451;
	int mekjfwnchis = 1037;
	bool exzbrohbd = false;
	bool fyednoju = true;
	int dbwysleuwatvss = 2605;
	bool rhiiwgv = true;
	if (23451 == 23451) {
		int hpbxcyp;
		for (hpbxcyp = 7; hpbxcyp > 0; hpbxcyp--) {
			continue;
		}
	}
	if (1037 != 1037) {
		int omwz;
		for (omwz = 64; omwz > 0; omwz--) {
			continue;
		}
	}

}

bool uxjkejd::vwjgceirkfyeuvyex(double eiwxjhlxfiuo, int vhtokweaolfw, int ciyktubd, string inmwuhurkb) {
	int lijkdoxmgcydoj = 0;
	int khnxtgkxqsiov = 91;
	bool vkccvuzszyicgd = false;
	int cssbkdvesazvoa = 4773;
	if (4773 == 4773) {
		int wxpies;
		for (wxpies = 29; wxpies > 0; wxpies--) {
			continue;
		}
	}
	if (4773 == 4773) {
		int xpwws;
		for (xpwws = 21; xpwws > 0; xpwws--) {
			continue;
		}
	}
	return true;
}

void uxjkejd::jvrdixwcweeoltiaeifyvqxdn(double fvtriiutbhft, string mmhydrmqicvdeaj) {

}

int uxjkejd::fyxmqwsvummfnruhdhoxhv(bool ruwuwyzxo, double guxhmceffwnkjdv, int vdyfif, string bppctqkqkfdzjd, string vhzwu, int dsrzqupoeie, bool brglsh, int wnlmcdzffbjnab, string xoucaic, int rflzrwfuf) {
	string obzanhmskcwpspp = "dfrn";
	string riasz = "jnvnfcqeapljzowvvbojbcbntndffmtwqqmgzbtpvbydtohlmwlrypkugbzrcvtzkoqgdsysfesrhvlkkbefcetdfazwq";
	bool pvwvf = true;
	int ycyfyjk = 8510;
	string xedhl = "oycrfgyzxyfiyyfqtralpxhbmpjtfabywdfvcyqscqwqgrtfwrbwbbjtvitraianioxrizldnepgscehsadlj";
	double jciesa = 21287;
	bool wqrfq = false;
	double wfdsfaem = 7313;
	if (string("oycrfgyzxyfiyyfqtralpxhbmpjtfabywdfvcyqscqwqgrtfwrbwbbjtvitraianioxrizldnepgscehsadlj") == string("oycrfgyzxyfiyyfqtralpxhbmpjtfabywdfvcyqscqwqgrtfwrbwbbjtvitraianioxrizldnepgscehsadlj")) {
		int kwjmtkrxtu;
		for (kwjmtkrxtu = 16; kwjmtkrxtu > 0; kwjmtkrxtu--) {
			continue;
		}
	}
	if (8510 == 8510) {
		int eivox;
		for (eivox = 4; eivox > 0; eivox--) {
			continue;
		}
	}
	if (true == true) {
		int rcvgt;
		for (rcvgt = 79; rcvgt > 0; rcvgt--) {
			continue;
		}
	}
	if (string("oycrfgyzxyfiyyfqtralpxhbmpjtfabywdfvcyqscqwqgrtfwrbwbbjtvitraianioxrizldnepgscehsadlj") == string("oycrfgyzxyfiyyfqtralpxhbmpjtfabywdfvcyqscqwqgrtfwrbwbbjtvitraianioxrizldnepgscehsadlj")) {
		int pp;
		for (pp = 21; pp > 0; pp--) {
			continue;
		}
	}
	return 77674;
}

bool uxjkejd::tdezkttccbqxm(bool fkqfqvza, int kcfzqmnoftc, bool ivodyuqpyyph, double ffzsivprcvadkm, int weggaiuhjhf, double jigigbjaco, bool mtvczh, double iguiesqksmbdsbo, bool nygxghwemnmfhez, string ebquykpelqizf) {
	int emwksiicebjav = 717;
	double orqsyxotptxmvjm = 12250;
	int fdxalyhmhux = 1889;
	string cslsunskhb = "wlzix";
	int psztqypbbbf = 676;
	double ntxkpjycp = 14517;
	int tnpfldryqj = 1916;
	if (676 != 676) {
		int zv;
		for (zv = 51; zv > 0; zv--) {
			continue;
		}
	}
	if (12250 == 12250) {
		int vffc;
		for (vffc = 37; vffc > 0; vffc--) {
			continue;
		}
	}
	return true;
}

int uxjkejd::hfchcmsayxhpdhdtggz(int lnxxromljpidduf, double skdnzdvqyztmai) {
	string ltzfau = "hrugdptvajbiffry";
	bool pokmwbhhtzf = true;
	bool bzednv = true;
	int xkwvxfwd = 1126;
	string yimombwhcpyiius = "fdophhashhxotrfqumgkfirjespowgjavqburvpenlpddgrzcmuptoawbefvygcbyrhndvvvcjbozfodaryzyxkeiklsymmyxu";
	int yjekfwghx = 1551;
	double brlgh = 12285;
	if (string("fdophhashhxotrfqumgkfirjespowgjavqburvpenlpddgrzcmuptoawbefvygcbyrhndvvvcjbozfodaryzyxkeiklsymmyxu") == string("fdophhashhxotrfqumgkfirjespowgjavqburvpenlpddgrzcmuptoawbefvygcbyrhndvvvcjbozfodaryzyxkeiklsymmyxu")) {
		int qu;
		for (qu = 28; qu > 0; qu--) {
			continue;
		}
	}
	if (true != true) {
		int jsbska;
		for (jsbska = 62; jsbska > 0; jsbska--) {
			continue;
		}
	}
	if (1126 != 1126) {
		int jmdykf;
		for (jmdykf = 5; jmdykf > 0; jmdykf--) {
			continue;
		}
	}
	if (12285 == 12285) {
		int hyvkcyo;
		for (hyvkcyo = 37; hyvkcyo > 0; hyvkcyo--) {
			continue;
		}
	}
	return 70990;
}

int uxjkejd::dggscwfkkkgeqyebvvtlno(int jaybruqiobddv, int bvqxjccbmnu, int ygzrtjqkgywsqz, string mhidqnbg, string vfyzxjfam, int usskpjskwdix, int dnckkfjtk, double ebkolakfirysct, double lwtuib, int oulcu) {
	double advqbbduoks = 67926;
	string tjahjmvlodmvnsc = "bvtjtooaqqahudyhcjqvwhnbumicrjguvwyzvgntoflvtbxzmgrkxkgxdvh";
	string zwlnfqdil = "ilcpwojokghexbvycezjlwnuixnyawpivjmahzxhhmckpydqaufprwhnkyfkrxyrkdqwtdehpnwohqbcrmmvv";
	int adnqsexpqgs = 128;
	if (string("ilcpwojokghexbvycezjlwnuixnyawpivjmahzxhhmckpydqaufprwhnkyfkrxyrkdqwtdehpnwohqbcrmmvv") == string("ilcpwojokghexbvycezjlwnuixnyawpivjmahzxhhmckpydqaufprwhnkyfkrxyrkdqwtdehpnwohqbcrmmvv")) {
		int ubwwcre;
		for (ubwwcre = 60; ubwwcre > 0; ubwwcre--) {
			continue;
		}
	}
	return 21818;
}

void uxjkejd::mduzmeuxjtdrtvv() {
	string qbmpjrwfu = "lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs";
	if (string("lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs") == string("lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs")) {
		int qzyknr;
		for (qzyknr = 51; qzyknr > 0; qzyknr--) {
			continue;
		}
	}
	if (string("lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs") == string("lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs")) {
		int cljahsj;
		for (cljahsj = 49; cljahsj > 0; cljahsj--) {
			continue;
		}
	}
	if (string("lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs") != string("lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs")) {
		int wihc;
		for (wihc = 81; wihc > 0; wihc--) {
			continue;
		}
	}
	if (string("lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs") != string("lxbjzlalxijwxlmigmlqrirfegzetyrjwkpwazsmggjreepoqxnqxengksrbbrxnfexnarvkgcsnvioowcs")) {
		int oik;
		for (oik = 1; oik > 0; oik--) {
			continue;
		}
	}

}

void uxjkejd::drskjpztpyho(double exmotqxtra, bool fukxcxtfxlb, string eiuuy) {
	string ssencua = "wqzyrttmfkdapfypcydydandkxumaogzlhkofsiidztzduvvqhghydthzcgnwqpkeleqndmlezlsxhxdjkkfehbes";
	double uhlvnxbfkjpam = 34973;
	bool ibjzlzepjjtbaot = true;
	bool ewyyuclbjtaxsvd = true;
	int jiarxtvuak = 734;
	bool egbtvkrodqzbb = true;
	if (string("wqzyrttmfkdapfypcydydandkxumaogzlhkofsiidztzduvvqhghydthzcgnwqpkeleqndmlezlsxhxdjkkfehbes") == string("wqzyrttmfkdapfypcydydandkxumaogzlhkofsiidztzduvvqhghydthzcgnwqpkeleqndmlezlsxhxdjkkfehbes")) {
		int jnfuzpsfw;
		for (jnfuzpsfw = 27; jnfuzpsfw > 0; jnfuzpsfw--) {
			continue;
		}
	}
	if (true == true) {
		int yyvpvhcbtz;
		for (yyvpvhcbtz = 51; yyvpvhcbtz > 0; yyvpvhcbtz--) {
			continue;
		}
	}
	if (734 != 734) {
		int tqcmyygfsn;
		for (tqcmyygfsn = 34; tqcmyygfsn > 0; tqcmyygfsn--) {
			continue;
		}
	}
	if (34973 == 34973) {
		int cvauqkyfw;
		for (cvauqkyfw = 9; cvauqkyfw > 0; cvauqkyfw--) {
			continue;
		}
	}

}

int uxjkejd::kpmfmvnqxuxqqwtxyqzrujz(bool nnvxwjrhq, bool tmkxcloud, int pvalcqvovla, bool uaeljvrgg, string nyvqfdy, string vrnatsc) {
	int tyzzqxvl = 8181;
	bool kdqpufbqyq = false;
	string honeyvnfiereq = "btssdcskzckohatiykgautrtzmrpeviefvzkmddtmyeaiaklgbhfvcrmebrdtdolnjpwdajygwbyzze";
	bool zynsipkr = true;
	bool itazn = false;
	double tjpihxikgkqwsqm = 18746;
	bool wkxzb = true;
	bool byjva = false;
	int sikerhwfr = 2055;
	if (false == false) {
		int kkp;
		for (kkp = 11; kkp > 0; kkp--) {
			continue;
		}
	}
	if (18746 != 18746) {
		int jezipy;
		for (jezipy = 12; jezipy > 0; jezipy--) {
			continue;
		}
	}
	if (false != false) {
		int cja;
		for (cja = 49; cja > 0; cja--) {
			continue;
		}
	}
	if (true == true) {
		int vihygzhkno;
		for (vihygzhkno = 35; vihygzhkno > 0; vihygzhkno--) {
			continue;
		}
	}
	return 473;
}

bool uxjkejd::jjplfjtvnxxi(bool cdlaunwkegjs, string olyxj, double nlvkrzqht, string ndzywwj, bool pchlvtaywzqiki) {
	int wdrjtqibsc = 4179;
	int gzzdzbzi = 147;
	int mwqvovhgjewa = 1505;
	bool gcnzujuc = false;
	bool vtqfpowcuql = false;
	if (false == false) {
		int urupk;
		for (urupk = 100; urupk > 0; urupk--) {
			continue;
		}
	}
	if (147 != 147) {
		int nxx;
		for (nxx = 23; nxx > 0; nxx--) {
			continue;
		}
	}
	if (false == false) {
		int yp;
		for (yp = 98; yp > 0; yp--) {
			continue;
		}
	}
	if (4179 != 4179) {
		int yopgjfd;
		for (yopgjfd = 55; yopgjfd > 0; yopgjfd--) {
			continue;
		}
	}
	return false;
}

string uxjkejd::cdhbpxqlccrkjtuv(string axrdpo, int qqwhd, bool mbtgvys, double pudeyksb) {
	int djhykuyjn = 3461;
	int krhnofp = 5311;
	int inttushsyfdj = 2478;
	bool lqesirwc = false;
	bool svajiq = true;
	string mhxbncfbv = "siv";
	bool uvlglkkq = false;
	int owkjwezcdpnals = 3092;
	double trhmd = 51794;
	double aplmdw = 30812;
	if (3461 != 3461) {
		int makegki;
		for (makegki = 20; makegki > 0; makegki--) {
			continue;
		}
	}
	return string("xznkrtdbh");
}

double uxjkejd::zialtbadjxdgcwykerbqmrng(bool pmjorarlvsa, bool fxypkgarrvc, int vzdbwqwscokgg, int zrhadvftdlnxwiq, string poakhknjln) {
	int omovdssgpun = 1265;
	double pjswzefpdepeqlm = 29409;
	if (1265 != 1265) {
		int yxrpqan;
		for (yxrpqan = 94; yxrpqan > 0; yxrpqan--) {
			continue;
		}
	}
	if (29409 == 29409) {
		int kamdiwezw;
		for (kamdiwezw = 76; kamdiwezw > 0; kamdiwezw--) {
			continue;
		}
	}
	if (1265 != 1265) {
		int uyo;
		for (uyo = 97; uyo > 0; uyo--) {
			continue;
		}
	}
	if (29409 == 29409) {
		int nvzscfv;
		for (nvzscfv = 32; nvzscfv > 0; nvzscfv--) {
			continue;
		}
	}
	if (1265 != 1265) {
		int nkmbnwi;
		for (nkmbnwi = 35; nkmbnwi > 0; nkmbnwi--) {
			continue;
		}
	}
	return 53672;
}

void uxjkejd::ogtcghoclekgtmcpmftyg(double vryhls, string toldhmkuom, int oxbiymeqhpeu, double xwmkdxlqq) {
	double ifwbbbyttfuxd = 53567;
	bool hfnjkmhp = true;
	string hbnuajswopwo = "wzsfuakrrgrjtgiy";
	double tdwwnqqaki = 6044;
	string dqntqdxwgdvs = "hprw";
	string citcolajqhb = "lopcgbbfjmrkkpenenttwpujnnumitosmsnhvwfgfhwgdfrnxeuxgjgzbopq";
	if (string("wzsfuakrrgrjtgiy") != string("wzsfuakrrgrjtgiy")) {
		int lwujzuawdk;
		for (lwujzuawdk = 75; lwujzuawdk > 0; lwujzuawdk--) {
			continue;
		}
	}
	if (string("lopcgbbfjmrkkpenenttwpujnnumitosmsnhvwfgfhwgdfrnxeuxgjgzbopq") != string("lopcgbbfjmrkkpenenttwpujnnumitosmsnhvwfgfhwgdfrnxeuxgjgzbopq")) {
		int veiwnnjdq;
		for (veiwnnjdq = 24; veiwnnjdq > 0; veiwnnjdq--) {
			continue;
		}
	}
	if (6044 != 6044) {
		int ptdktdcj;
		for (ptdktdcj = 81; ptdktdcj > 0; ptdktdcj--) {
			continue;
		}
	}

}

int uxjkejd::bpskyknxtkxzzsj(string fiizugxu, int vodcty, double dtmtdfakzxhxiqi, bool ehkhkdwywqxb) {
	string tfqbwojmlpqjqo = "rr";
	int zohuurlkrcaq = 3256;
	string lnmkawtvbo = "clqmfddmxdhcruqaacnmfgojfhyuzerirerztwzswfcoauikwqrhugyqvwbyhllvmqexhqawlcazrhmbtuhrfuuclyysv";
	int ndarkczjfgas = 975;
	return 71451;
}

bool uxjkejd::jyaweqozdcwgvzposc(int qlluipx, double bffbvteftwhelng, string qjznuulswcyxv, int ixuaopqgjzdg, int jwscouc, string bvyci, string xdyeu, string jwhmwv, int ujdldhhjoot, int teyqnhnit) {
	int phtmllbokoo = 8427;
	double zasxfdzykpbsocf = 28993;
	string jpzst = "krdmllnahfwfueqeqfwbbmenmnwbqlogep";
	bool thstwpmf = false;
	int opkcsveujot = 2946;
	if (string("krdmllnahfwfueqeqfwbbmenmnwbqlogep") != string("krdmllnahfwfueqeqfwbbmenmnwbqlogep")) {
		int povoipavr;
		for (povoipavr = 39; povoipavr > 0; povoipavr--) {
			continue;
		}
	}
	if (28993 != 28993) {
		int sttjdlwf;
		for (sttjdlwf = 87; sttjdlwf > 0; sttjdlwf--) {
			continue;
		}
	}
	if (28993 == 28993) {
		int tyzahlkmxe;
		for (tyzahlkmxe = 42; tyzahlkmxe > 0; tyzahlkmxe--) {
			continue;
		}
	}
	return true;
}

double uxjkejd::pfnhgcgtgcfkbdpsowodw(int gkedueovmxelv, string itvvlbf, bool truyzeploarj, double nzgtomfootb) {
	int kpynfw = 5751;
	double qrlsemjwntyz = 24908;
	bool lfmtvfmzj = false;
	string gmyeuamo = "jzmuhytjmijciirztzutxmwbktudlbgxfzyfzxougvcoloylfgqdonfmmbcshlmhmhjsdhmgkishnaoyxlvzhqqgn";
	int hwxnymxne = 4863;
	if (5751 == 5751) {
		int xwqgvm;
		for (xwqgvm = 97; xwqgvm > 0; xwqgvm--) {
			continue;
		}
	}
	return 62115;
}

uxjkejd::uxjkejd() {
	this->zialtbadjxdgcwykerbqmrng(true, true, 3441, 1480, string("qibtxhbldcqgzkasusqjxlyixllvkokuacfvqzcfnnqxbaggtdttwkwqujfrvbniohvaledpnosvmwafwqzcq"));
	this->ogtcghoclekgtmcpmftyg(33104, string("zxlqlzvpcdvoqemsjrlfaoiiykotrcqfzcgtyuh"), 8192, 13875);
	this->bpskyknxtkxzzsj(string("tagsmjibfhuiispewnuexvwejrogtymbxxdleaspksisbhkkiitriyptsxfefiilccvldkaftehwcdxyfuzuei"), 3985, 5826, false);
	this->jyaweqozdcwgvzposc(4509, 15970, string("ntccxbtjznxrdmwonnvcyempnijkemlwuueaykl"), 1434, 3290, string("vjshxpeniaxzrqwehfhcidqyhmcsbbgmxcywcnvldprukvqsqaacgppaoimnaelbxmyehvrvwghrrklsecw"), string("muqgyz"), string("icyeqjqoomylv"), 292, 4906);
	this->pfnhgcgtgcfkbdpsowodw(417, string("gdvracsutunapwnghyvjsqfbxeollzwxjadgyrvwydcozrpwwkyasdbmzxueecsjkmuwdodgyviyfhhrkixfawame"), true, 68077);
	this->fyxmqwsvummfnruhdhoxhv(false, 42098, 2343, string(""), string("oourbz"), 2338, true, 993, string("lriqbsnpjqhlxjbsyggzlejnyjguolfncqctfrsnizvfkplhdbplaoypedyqisikdwqyd"), 1234);
	this->tdezkttccbqxm(false, 2368, true, 47681, 2337, 54903, false, 17840, false, string("uupgfahxliqnrduqxivqirrowolntsmxsmfobuuqvlhognygooqvi"));
	this->hfchcmsayxhpdhdtggz(7581, 12508);
	this->dggscwfkkkgeqyebvvtlno(363, 566, 1365, string("csvdasoprtrmihzntuuhxekwdpcsagtnmpivwblcftscjenuqwgsiuplwky"), string("cyfdtnpaibbqpeglrwlbxcpmwrxdvkuqhnljbywuiytaktgjglae"), 3964, 69, 91565, 10121, 428);
	this->mduzmeuxjtdrtvv();
	this->drskjpztpyho(21821, false, string("oprvnrfwjpmdtpyjhrebpcoxmyucutzrcyfgknmqsfuefulnzfs"));
	this->kpmfmvnqxuxqqwtxyqzrujz(true, true, 5680, false, string("gvfdlbtzeifijzoqdlpzdobebyjnozzxplifbtiychulvhhzomafnj"), string("pevmgvvoprnlktudxqbmduymwsikgycjnfriqziyibdjipyoaxmqqollbahtanwgiuewpoxdklyapyjoiwwdwzgudtwuist"));
	this->jjplfjtvnxxi(false, string("bnslr"), 4508, string("cvjtzjlkgesmccyisdvhbxdqvdrjdo"), false);
	this->cdhbpxqlccrkjtuv(string("nkxtynzgsmyziwclmrjqkjyxjjwplzcmptjtwjvdhqbyesajfvqybnjsb"), 7387, false, 21345);
	this->mespwikdkcdfnipyqt(2215, 7986, string("vgnacfgelrbclzde"), string("ptxgnxrktyanppqtyskorteloafvxtyamzyqxpj"), string("figcsdlykksrzdybdkb"), 1291, false, false);
	this->zuoaojrkexavartfmmlwkn(string("fbzmquwrf"), string("xpjnkoxxozqauwbaguattohcwqxquugmzqwgcaokvqrjbkapxzsjmebdmbeuacmjjvgne"), 4813, 66711, 741, 27697, 8394, false, false, 641);
	this->ohtwjrrgxen(3232, 22558, string(""), 4368, 2612, 54953, 7, 401, 70090, 5966);
	this->laeykgbwiyyybnd(9542, 5959, string("xygznhtxjahyclkqnshxbmtngmfkqhqfgrkrycsknpekchffwasqifck"));
	this->kwusubljihcrysmhzsfcbnteh(string(""), 11249, string("fopcetghziecgrqfenddwwoukgeltotfuktkgvujhwaiwa"), string("aioplbgysokcvqismullbwiupvznrjzlympclthayuphaqnhbshgewpukyjkznbfwj"), 21725, string("iaaucroivdfhfvgflrmatrrxppquxjfgoxkhtayohvtccspawpflvwktgpeokdnkusksuwfcvjiuyalusrfubytgxrfum"), string("qglijgyydwrbskzfnot"));
	this->vwjgceirkfyeuvyex(78095, 4524, 5249, string("fpxllblrbkfsbnqgcadiceeewssrcadntoqyxzcndghvlfuhpjonqe"));
	this->jvrdixwcweeoltiaeifyvqxdn(51466, string("kqqfhljjtglx"));
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class gnpxjac {
public:
	string saiyi;
	bool geosppsfkcqiqw;
	int kjfieoym;
	int qvaxmgxbniivwr;
	gnpxjac();
	void slnqoznozkr(double qxkenmkctt, bool kctcqtbbkm, double hszyjzycgtfscq, double gmikgcq, bool calhpm, int hozyfwlkybdc, double ghksa, double xxuysbz, double pzemeok);
	string lqokmbhapaauirdwdpenfeef(double fvekijxoxzmoso, bool qejsflh, string sdlpahnohkvdcdu, string aebsuyljnpzriu, string oruehmdkmxujb, int ojdwfg, bool dguvxerjpqxzxm, double fbjpesq, int xauiwvh);
	int hsvnuzgahndqvmjrrohe(int bnqjf, double sjubq, int trfsmyjojz, bool teepdackxdzsnd, int gybts, int xsaiqfaikqhg, double xhoqlka);
	void muekqokvkjidemulktd(double hqtucghbaqqfnnv, bool zpuqccaqubzlb, bool wtpgfg, bool dvkykmbckd, bool rnwpjfzdtcforb);
	double filewxgcvexiega(double budkuo, int ynoatycla, string qhxsycqeg, bool rpkmhylrceou, bool pafzw, string jzwan, double tpzklixvwigggq, string agkrztlz, int qqypxg);

protected:
	int bwodmvmhuatvz;
	double mhwagbuck;
	double tnqoiohxti;
	double gmingoxm;
	double ouvrbdluj;

	void egzpsslanse(bool xjopbkdkcbftd, int neenclcc, bool ajlagdgk, int vafapoci, string odebfelpv, string moiwfhksgei, string lqekzfacvrravdh);
	string rblitubwcovmt(double qmppyfii, string wumgzgijmito, int tzpdyxgzazuvf, string enytckaqymjjkh, double ruzasegls);
	bool slufnqskwkn(bool qxlcrepusojb, bool hcbrlzxkiutvawk, bool negorvx, double iqcxxzarpxg, int reicqpywxdj);
	double mchatjkepdtvmyqquupikvaym(bool mqgqcfkqobjij, double bxnajxaptu, double ykvluipvm, int btrgaazuxeg, string rdpuino, string aowwteijorav, int vpwugikuicd);
	bool cppzbnmxmyxwuoynbfnr(double jqykfqb, string cghjbv, string goayvuqizvplg, double iltlbgvqx, double bgravyul);
	string xeyipzvfhstmtiwgbktajoplv(string keaqb, int xdfjekwtpmq, bool rdvoqeqqsziozy, string lgofp, bool dvugp, int ntkco, bool ukmvwrwjlxrj);

private:
	string pffcxdskzp;
	bool yyctplhldprf;
	string rhcrr;
	bool tlcvfujiqxv;
	string qcnspwf;

	int hgdxczijtgegstpipze(bool hcwhjmfq);
	string ppuuxbxlayhwjzf(int ysgwlxwbachmao, bool ynljyirp, double eojohafbhlbdw, string dpfvvkvrfdkqo, double uukfaksrnrzftt, bool uhjfcsyhyinocci, string mrmianozkxtno, string dhwky);
	void fguwsgdoidqndrxgheexztp(string perie);
	int wkmcbfgmpj(bool xdyxysjxcp, double sbofniwwwi);
	void bxavjcepuhyvz(bool pchbusxz, string rmbenhkrhpqdbb, double eewzy);
	bool ahieravlqrxuvdfxoxdzcul(double abxjaecohrmcjkl, string sdarium, string qdsshkfi, double zjvfxsk, bool wpisauymi, bool uqflhqwcpowbb, int bcxgvmwfawxp, double hiizmkxjmax);

};


int gnpxjac::hgdxczijtgegstpipze(bool hcwhjmfq) {
	double vpamlpu = 3260;
	double zvwdryryrfy = 31687;
	int wjagbh = 8633;
	int zruday = 7705;
	if (3260 == 3260) {
		int nlc;
		for (nlc = 30; nlc > 0; nlc--) {
			continue;
		}
	}
	if (8633 != 8633) {
		int bjeu;
		for (bjeu = 36; bjeu > 0; bjeu--) {
			continue;
		}
	}
	if (31687 != 31687) {
		int dycqzwke;
		for (dycqzwke = 25; dycqzwke > 0; dycqzwke--) {
			continue;
		}
	}
	return 17543;
}

string gnpxjac::ppuuxbxlayhwjzf(int ysgwlxwbachmao, bool ynljyirp, double eojohafbhlbdw, string dpfvvkvrfdkqo, double uukfaksrnrzftt, bool uhjfcsyhyinocci, string mrmianozkxtno, string dhwky) {
	double urptmmsszep = 40457;
	double melgvgqaubxho = 64875;
	string jbsuzmpd = "knhmqwovaqarnpwarqqvyhljgwswylcncohmgdffj";
	bool qsqwdwflxohtbrz = true;
	double qmnizsgyt = 65227;
	int mytvbegbqbqboz = 2290;
	if (40457 != 40457) {
		int pqcheoth;
		for (pqcheoth = 87; pqcheoth > 0; pqcheoth--) {
			continue;
		}
	}
	if (40457 == 40457) {
		int febles;
		for (febles = 9; febles > 0; febles--) {
			continue;
		}
	}
	if (true == true) {
		int fpabvvcp;
		for (fpabvvcp = 15; fpabvvcp > 0; fpabvvcp--) {
			continue;
		}
	}
	if (true != true) {
		int qlvjirvm;
		for (qlvjirvm = 86; qlvjirvm > 0; qlvjirvm--) {
			continue;
		}
	}
	return string("xvlaexcoebwfemwduqw");
}

void gnpxjac::fguwsgdoidqndrxgheexztp(string perie) {
	double ybjlrfuyehsegb = 7547;
	string bdisef = "uswzaihpkktspsnitwgwboivwyxxcajiptiusinyshrgpuwknqqdjihtjunugpetluzdhymcuijiurmwkygik";
	bool tlbhqjvcfknuna = true;
	bool scupxyaexfefl = true;
	double xnnooqeklvkgepl = 10520;
	string jqxtotlghwdoyt = "jnmbmklmxanhwktjg";
	bool jsqxcpyih = false;
	bool rbtnzslcsjjet = false;
	string ayykilirmje = "lizeehqishcicoywp";
	if (10520 != 10520) {
		int cygzeka;
		for (cygzeka = 56; cygzeka > 0; cygzeka--) {
			continue;
		}
	}
	if (string("uswzaihpkktspsnitwgwboivwyxxcajiptiusinyshrgpuwknqqdjihtjunugpetluzdhymcuijiurmwkygik") != string("uswzaihpkktspsnitwgwboivwyxxcajiptiusinyshrgpuwknqqdjihtjunugpetluzdhymcuijiurmwkygik")) {
		int kbcmpyxe;
		for (kbcmpyxe = 19; kbcmpyxe > 0; kbcmpyxe--) {
			continue;
		}
	}
	if (string("jnmbmklmxanhwktjg") == string("jnmbmklmxanhwktjg")) {
		int qtigppb;
		for (qtigppb = 30; qtigppb > 0; qtigppb--) {
			continue;
		}
	}

}

int gnpxjac::wkmcbfgmpj(bool xdyxysjxcp, double sbofniwwwi) {
	bool nsygkycpekh = false;
	string nvosiqtqn = "gissyzkvjzewnezukxmvhgvjvwfrcnvlomdzdsbhhvhhazuahf";
	bool dzwxpzxnrkeho = false;
	string vhbwkxzmeqipx = "qaevlwjlanpuazdbvlgngbpckfpnjgnxochhufyevwhhbkeiywzjfexrwxt";
	double lskctgzjrk = 32248;
	bool sbumuo = false;
	double hbqecuvjcf = 18717;
	int zbzbngtlsmmyihb = 1629;
	if (false == false) {
		int ttach;
		for (ttach = 74; ttach > 0; ttach--) {
			continue;
		}
	}
	return 53360;
}

void gnpxjac::bxavjcepuhyvz(bool pchbusxz, string rmbenhkrhpqdbb, double eewzy) {
	string kvenh = "ovrxpolavwwlnxybhbrpqkhyslgwzmsmvkbucolrqtqyamtkxqtzwujmaypewejqy";
	if (string("ovrxpolavwwlnxybhbrpqkhyslgwzmsmvkbucolrqtqyamtkxqtzwujmaypewejqy") != string("ovrxpolavwwlnxybhbrpqkhyslgwzmsmvkbucolrqtqyamtkxqtzwujmaypewejqy")) {
		int avtm;
		for (avtm = 78; avtm > 0; avtm--) {
			continue;
		}
	}
	if (string("ovrxpolavwwlnxybhbrpqkhyslgwzmsmvkbucolrqtqyamtkxqtzwujmaypewejqy") != string("ovrxpolavwwlnxybhbrpqkhyslgwzmsmvkbucolrqtqyamtkxqtzwujmaypewejqy")) {
		int hvyt;
		for (hvyt = 70; hvyt > 0; hvyt--) {
			continue;
		}
	}
	if (string("ovrxpolavwwlnxybhbrpqkhyslgwzmsmvkbucolrqtqyamtkxqtzwujmaypewejqy") == string("ovrxpolavwwlnxybhbrpqkhyslgwzmsmvkbucolrqtqyamtkxqtzwujmaypewejqy")) {
		int pps;
		for (pps = 49; pps > 0; pps--) {
			continue;
		}
	}

}

bool gnpxjac::ahieravlqrxuvdfxoxdzcul(double abxjaecohrmcjkl, string sdarium, string qdsshkfi, double zjvfxsk, bool wpisauymi, bool uqflhqwcpowbb, int bcxgvmwfawxp, double hiizmkxjmax) {
	double iveamuhltoxuil = 80584;
	string etdnmgljpavvrrb = "eajjjosyzrxuaeziosckjefalfkzvlnkopqihfezumpzhaxlwghbwqgtilvayoz";
	bool vbatnru = true;
	string onefaxidmgoj = "zljjyrdfldmrfoofnskqtlouv";
	string lmcabwv = "uevcuorblrtykvcaykzffjleqnjkdayxdwvfbiozcprbrijhdaibhapetolcxtzhtbfgskntames";
	int tvoeoxkrhtgrxiy = 5051;
	double hkppjesvmpzf = 13025;
	bool lwaesobykprjzt = false;
	if (true != true) {
		int oelpmrlwol;
		for (oelpmrlwol = 28; oelpmrlwol > 0; oelpmrlwol--) {
			continue;
		}
	}
	if (false != false) {
		int bwgd;
		for (bwgd = 89; bwgd > 0; bwgd--) {
			continue;
		}
	}
	if (string("eajjjosyzrxuaeziosckjefalfkzvlnkopqihfezumpzhaxlwghbwqgtilvayoz") == string("eajjjosyzrxuaeziosckjefalfkzvlnkopqihfezumpzhaxlwghbwqgtilvayoz")) {
		int gmvdpscf;
		for (gmvdpscf = 55; gmvdpscf > 0; gmvdpscf--) {
			continue;
		}
	}
	if (string("uevcuorblrtykvcaykzffjleqnjkdayxdwvfbiozcprbrijhdaibhapetolcxtzhtbfgskntames") != string("uevcuorblrtykvcaykzffjleqnjkdayxdwvfbiozcprbrijhdaibhapetolcxtzhtbfgskntames")) {
		int ufpcveypx;
		for (ufpcveypx = 1; ufpcveypx > 0; ufpcveypx--) {
			continue;
		}
	}
	return true;
}

void gnpxjac::egzpsslanse(bool xjopbkdkcbftd, int neenclcc, bool ajlagdgk, int vafapoci, string odebfelpv, string moiwfhksgei, string lqekzfacvrravdh) {
	int vlrgef = 9157;
	double kvlttgyjmqy = 22249;
	int ffmrtocebo = 2114;
	if (22249 != 22249) {
		int ceojtc;
		for (ceojtc = 98; ceojtc > 0; ceojtc--) {
			continue;
		}
	}
	if (2114 != 2114) {
		int odee;
		for (odee = 96; odee > 0; odee--) {
			continue;
		}
	}
	if (2114 != 2114) {
		int bcsdds;
		for (bcsdds = 36; bcsdds > 0; bcsdds--) {
			continue;
		}
	}

}

string gnpxjac::rblitubwcovmt(double qmppyfii, string wumgzgijmito, int tzpdyxgzazuvf, string enytckaqymjjkh, double ruzasegls) {
	int ctodhzallidymg = 2283;
	string gnuvrg = "phneztmlylnsajlwrhtcgowqugxyhbpjettpyjo";
	return string("yljkdr");
}

bool gnpxjac::slufnqskwkn(bool qxlcrepusojb, bool hcbrlzxkiutvawk, bool negorvx, double iqcxxzarpxg, int reicqpywxdj) {
	int qxrmdlq = 4140;
	int bwohhv = 175;
	string tyixsge = "bfyfgygluuzbextwjinhpgbznrkobjvaonsgcctjlfntezgqnjxkjkymsnhkkmvukdgqqqrimubqirpykgkejyavk";
	double ysusznickwqgjj = 37860;
	int gqglsoejgjee = 3276;
	if (4140 == 4140) {
		int cmvq;
		for (cmvq = 85; cmvq > 0; cmvq--) {
			continue;
		}
	}
	if (string("bfyfgygluuzbextwjinhpgbznrkobjvaonsgcctjlfntezgqnjxkjkymsnhkkmvukdgqqqrimubqirpykgkejyavk") != string("bfyfgygluuzbextwjinhpgbznrkobjvaonsgcctjlfntezgqnjxkjkymsnhkkmvukdgqqqrimubqirpykgkejyavk")) {
		int swq;
		for (swq = 19; swq > 0; swq--) {
			continue;
		}
	}
	if (4140 == 4140) {
		int qa;
		for (qa = 63; qa > 0; qa--) {
			continue;
		}
	}
	return true;
}

double gnpxjac::mchatjkepdtvmyqquupikvaym(bool mqgqcfkqobjij, double bxnajxaptu, double ykvluipvm, int btrgaazuxeg, string rdpuino, string aowwteijorav, int vpwugikuicd) {
	int dgxixswywemhhm = 5668;
	bool jknfuirc = false;
	bool skvtbhk = false;
	int nkcyzuvtmhxyvfx = 825;
	double xjursiv = 9390;
	double jgfthmf = 61295;
	int thpvroypgt = 1218;
	bool dmwuiiexgxvy = true;
	int wnanatt = 7129;
	if (false != false) {
		int cou;
		for (cou = 98; cou > 0; cou--) {
			continue;
		}
	}
	if (1218 == 1218) {
		int xwomn;
		for (xwomn = 8; xwomn > 0; xwomn--) {
			continue;
		}
	}
	if (5668 != 5668) {
		int injr;
		for (injr = 49; injr > 0; injr--) {
			continue;
		}
	}
	return 51131;
}

bool gnpxjac::cppzbnmxmyxwuoynbfnr(double jqykfqb, string cghjbv, string goayvuqizvplg, double iltlbgvqx, double bgravyul) {
	int hrvyczilk = 2106;
	double pvulqw = 37564;
	int golwvzzdjoqqkfh = 145;
	if (145 == 145) {
		int myk;
		for (myk = 16; myk > 0; myk--) {
			continue;
		}
	}
	if (37564 == 37564) {
		int oymrryp;
		for (oymrryp = 29; oymrryp > 0; oymrryp--) {
			continue;
		}
	}
	if (145 == 145) {
		int ucnx;
		for (ucnx = 45; ucnx > 0; ucnx--) {
			continue;
		}
	}
	return false;
}

string gnpxjac::xeyipzvfhstmtiwgbktajoplv(string keaqb, int xdfjekwtpmq, bool rdvoqeqqsziozy, string lgofp, bool dvugp, int ntkco, bool ukmvwrwjlxrj) {
	int mvgbrtsqd = 6744;
	double ioimq = 28470;
	double qtmtexvsmneg = 66989;
	string arlgnopotjdlv = "ywvysmmnvtlyfo";
	bool sbhixqob = true;
	if (string("ywvysmmnvtlyfo") != string("ywvysmmnvtlyfo")) {
		int tkndgdf;
		for (tkndgdf = 90; tkndgdf > 0; tkndgdf--) {
			continue;
		}
	}
	if (6744 == 6744) {
		int bulls;
		for (bulls = 88; bulls > 0; bulls--) {
			continue;
		}
	}
	if (true == true) {
		int jbwdnxpz;
		for (jbwdnxpz = 80; jbwdnxpz > 0; jbwdnxpz--) {
			continue;
		}
	}
	if (28470 == 28470) {
		int kc;
		for (kc = 77; kc > 0; kc--) {
			continue;
		}
	}
	return string("tdobctt");
}

void gnpxjac::slnqoznozkr(double qxkenmkctt, bool kctcqtbbkm, double hszyjzycgtfscq, double gmikgcq, bool calhpm, int hozyfwlkybdc, double ghksa, double xxuysbz, double pzemeok) {
	int jmoahoypxmfg = 2929;
	int plqtutga = 3247;
	bool ufdyttbheqywj = true;
	bool trlwrzdxsiuyds = true;
	string jwgnnt = "dylwnwtyrsjyj";
	double zyocxvbknseoja = 60036;
	int xxpzahcxztvx = 4681;
	double wytkqmrrhfnge = 69210;
	string iqogguzmfudmhx = "iizhalalqwe";
	string xmcsyuenb = "korsntgphdtgnbfrmgydlrgjdwhpaominauypyfghtrqyqulztpvns";
	if (string("korsntgphdtgnbfrmgydlrgjdwhpaominauypyfghtrqyqulztpvns") != string("korsntgphdtgnbfrmgydlrgjdwhpaominauypyfghtrqyqulztpvns")) {
		int lqtz;
		for (lqtz = 20; lqtz > 0; lqtz--) {
			continue;
		}
	}
	if (string("iizhalalqwe") != string("iizhalalqwe")) {
		int yxzmtmwi;
		for (yxzmtmwi = 35; yxzmtmwi > 0; yxzmtmwi--) {
			continue;
		}
	}
	if (4681 != 4681) {
		int mvms;
		for (mvms = 46; mvms > 0; mvms--) {
			continue;
		}
	}
	if (2929 != 2929) {
		int qmbufkep;
		for (qmbufkep = 35; qmbufkep > 0; qmbufkep--) {
			continue;
		}
	}
	if (string("korsntgphdtgnbfrmgydlrgjdwhpaominauypyfghtrqyqulztpvns") == string("korsntgphdtgnbfrmgydlrgjdwhpaominauypyfghtrqyqulztpvns")) {
		int ayzxso;
		for (ayzxso = 27; ayzxso > 0; ayzxso--) {
			continue;
		}
	}

}

string gnpxjac::lqokmbhapaauirdwdpenfeef(double fvekijxoxzmoso, bool qejsflh, string sdlpahnohkvdcdu, string aebsuyljnpzriu, string oruehmdkmxujb, int ojdwfg, bool dguvxerjpqxzxm, double fbjpesq, int xauiwvh) {
	int plyckcpcjeuto = 4029;
	int crnhqttislgiwf = 2614;
	string aielfmullbwos = "zjqawuydqupbzdrl";
	bool thtgvw = false;
	int bsaoficuoefgsmb = 165;
	if (165 != 165) {
		int gju;
		for (gju = 81; gju > 0; gju--) {
			continue;
		}
	}
	return string("");
}

int gnpxjac::hsvnuzgahndqvmjrrohe(int bnqjf, double sjubq, int trfsmyjojz, bool teepdackxdzsnd, int gybts, int xsaiqfaikqhg, double xhoqlka) {
	bool stzbcpgj = false;
	double evlwuedml = 63974;
	int ykyydrdftkvgi = 3299;
	string sczdjbl = "iozlngufieqvvzsubsgzhsouusosdhbmuirhwurnanymjbesiyrfibvhudyxcehzfwmkezhkbadcqklnggpxmenqbmleqaxvi";
	string qzrmlvunjtgabt = "qiddffzosxkujsvcawxnwxeprkazdyxhaejbnlfmexkiyxkawuczwjqkqcecttacurefoyccsgllddyvzpcmautfbzoxelzvfr";
	string polojyk = "pybfbuahxqbjlhb";
	string ieskvubmrx = "mmqjwhqanxeltcxclwzzyfpsbfchtwtbiaagynhqacwczteiwoxfkvrvrcxyqj";
	if (3299 != 3299) {
		int xrfvca;
		for (xrfvca = 100; xrfvca > 0; xrfvca--) {
			continue;
		}
	}
	if (63974 != 63974) {
		int mqulhk;
		for (mqulhk = 19; mqulhk > 0; mqulhk--) {
			continue;
		}
	}
	if (3299 == 3299) {
		int kpbikj;
		for (kpbikj = 20; kpbikj > 0; kpbikj--) {
			continue;
		}
	}
	if (string("pybfbuahxqbjlhb") != string("pybfbuahxqbjlhb")) {
		int fy;
		for (fy = 43; fy > 0; fy--) {
			continue;
		}
	}
	if (false != false) {
		int zox;
		for (zox = 0; zox > 0; zox--) {
			continue;
		}
	}
	return 88843;
}

void gnpxjac::muekqokvkjidemulktd(double hqtucghbaqqfnnv, bool zpuqccaqubzlb, bool wtpgfg, bool dvkykmbckd, bool rnwpjfzdtcforb) {
	int tcxkux = 8007;
	string ebcqnbmeoipuw = "uabhgffzpmjhlgdeogrlzwjnrjwbtsladtymnvccfvnqxduutvwksvzwcuaebrjjkjgsxeruwkxhddilqhhhdoiwkfhwkwnmnloc";
	bool ytmtzazrgtess = false;
	string zmyxmi = "nyhtcuwukgphllyvocypccsnzovonpksezwkjgrbkmaqpxsobyqmbdiwqxuhbdgtfkwsuhi";
	bool scvczdiekchqe = true;
	bool ymumarszkmsmxa = true;
	bool ljuanbdtjdkt = true;
	bool nyddql = true;
	bool ccvkgwo = true;
	string zkyqc = "gkgaxtxclvltdkbkskouujqaqmnuahtpfarojsyfyvuyrmdyqmsubnqddpprhpjjxhmj";
	if (true != true) {
		int rudg;
		for (rudg = 65; rudg > 0; rudg--) {
			continue;
		}
	}
	if (8007 != 8007) {
		int sjg;
		for (sjg = 100; sjg > 0; sjg--) {
			continue;
		}
	}
	if (true == true) {
		int pvykraovb;
		for (pvykraovb = 77; pvykraovb > 0; pvykraovb--) {
			continue;
		}
	}
	if (true == true) {
		int lwubloqg;
		for (lwubloqg = 82; lwubloqg > 0; lwubloqg--) {
			continue;
		}
	}

}

double gnpxjac::filewxgcvexiega(double budkuo, int ynoatycla, string qhxsycqeg, bool rpkmhylrceou, bool pafzw, string jzwan, double tpzklixvwigggq, string agkrztlz, int qqypxg) {
	bool nxjgu = false;
	bool slknrsbpaz = false;
	if (false != false) {
		int qwtgfgru;
		for (qwtgfgru = 82; qwtgfgru > 0; qwtgfgru--) {
			continue;
		}
	}
	if (false != false) {
		int iaqophn;
		for (iaqophn = 61; iaqophn > 0; iaqophn--) {
			continue;
		}
	}
	if (false == false) {
		int wajl;
		for (wajl = 16; wajl > 0; wajl--) {
			continue;
		}
	}
	if (false != false) {
		int jcipj;
		for (jcipj = 67; jcipj > 0; jcipj--) {
			continue;
		}
	}
	return 22643;
}

gnpxjac::gnpxjac() {
	this->slnqoznozkr(27918, true, 39590, 8587, false, 7134, 67548, 7814, 3375);
	this->lqokmbhapaauirdwdpenfeef(39089, true, string("psgqqducpenphhssposawnibzkbhwfoqsaprgzbqcvcequtrpfmyexlivgzhciiwxsawasrnvxufosbjuhhhwcwapufqkejc"), string("xbhuwyqxweuvrdnueagkqzdcenhafsqmtykdmpspghvbsckiswlqutdkcnidtqvpkugtgxqfqjo"), string("frqmxwywwdcndiicbilynlpqlnbatqspobjvqlrphcqmszdxzluinbkaigxrluslaupaheajwryspzyfuozqdoefdgcebfy"), 1204, false, 3900, 9726);
	this->hsvnuzgahndqvmjrrohe(4505, 16003, 711, false, 1083, 2094, 20562);
	this->muekqokvkjidemulktd(78717, true, false, true, false);
	this->filewxgcvexiega(5880, 127, string("yjfctyybkubixwtaoniyrzsflvzbkpegsitpkkzqgfmulsknozibtxwjnycvvnytasgpsoqobaitbsjaiwlr"), true, false, string("zteifrwumirkwygutvaukuznfodwcjtjbsdvoaasnzdhqcsdmklyvpha"), 34716, string("zkodorcbjdbjqzmbakcsj"), 550);
	this->egzpsslanse(false, 3244, true, 2484, string("xynlmwhrvpovzhctiywhaefzypefbwkgdcjioqrucqdxgrhxutkeagznojkvbatonfzmllznfsprwswyhcbzlilmsyde"), string("izxtjmsfonuwixskcfgfiexsbkg"), string("xzpshdvqdmfniizxcmmmoizsslrncetvecpocksryjwpuywjoyc"));
	this->rblitubwcovmt(7306, string("vbrkhmzvarubfziqhatcaynvqgkwtqqitoegtotrwsrfaqfnpuvjdxozbrxz"), 1130, string("qlmwmttzlhbaaxbixwjtpprybodhtprlq"), 2971);
	this->slufnqskwkn(true, false, false, 2080, 2022);
	this->mchatjkepdtvmyqquupikvaym(true, 17079, 49730, 3544, string("uptjiyghapccvqwudvsdbnpmzpdmpwyainydyyhxzajeuglldjdygzxjrdgbrwfiszwggxeuuhcwpgeuanphkesslkeypnsgujgw"), string("nfiixibrhqykfsemuhdwyuhirmwavpbqhmwjvqmudwmaqlwexfwavsviofkwmhybzwukosmn"), 3553);
	this->cppzbnmxmyxwuoynbfnr(4806, string("kvtfsznxizbjbguwwaomzudkmspuzdmtigopkjladbbzgvbwqmfhrbhppndilenmmdxyfik"), string(""), 9713, 1636);
	this->xeyipzvfhstmtiwgbktajoplv(string("rbcmrsyrfogtg"), 810, true, string("zcjchjrzfouyosaaksvxjogjmwdrzeuwviaolixunodjdhxhaptixebutr"), false, 739, true);
	this->hgdxczijtgegstpipze(true);
	this->ppuuxbxlayhwjzf(2480, true, 3564, string("juotfeqdjetqanibuhmzxbfgoyelghyltaafpwwuyxvkjpxxoepflaacpnwbshwmobspjhdjsrompihptfrkjjwquinbbbha"), 1536, false, string("gdelgohhijdbufboqilaqwiyqiprvqfksqtazjwontsmoplhtgxxcrnmx"), string("fcrnfvwsnxxmizydctaeioxslcdxdnwexdcxdcoujwfrkbrc"));
	this->fguwsgdoidqndrxgheexztp(string("ructqskalxdejhfhcvxuumwwqwdnwyqcyxbgdfeekkoamtlodgbbakuukgrarugfqfbpoqbijgihubebfmlyqnk"));
	this->wkmcbfgmpj(false, 26985);
	this->bxavjcepuhyvz(false, string("zxiuxzneshrqkseemcdlsz"), 32003);
	this->ahieravlqrxuvdfxoxdzcul(23125, string("zoakshdrzilfuojfqklhdxrbfwyzsxedeyoosxcwfd"), string("aesytamzcuadassdaxmsrhbafychbemvfbvjdzwbfdffjnalliktuntzfehnxneeaavsppzjefakfyvsimfcxzfoeblwx"), 17831, false, false, 2346, 41452);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class fwwzkdi {
public:
	double jeengkujypv;
	int czoppnfraj;
	int ywaki;
	fwwzkdi();
	double pvhmzjoovh(double xkszztsbsrqafwu, double kfcncofulljged, int csjuyryfdajm, double ryngqmhfuejcgh, double uozmvvefgnffskc, double utkya, double yrchchhbtqne, double quyrws, bool ygacygbtsdf);
	bool ksymemawrgpvktohodsrj();
	void astmeyykmsifjcplaalrqfh(string erhzlga, int iddypczyujsj, string isuqodlseid, string ulhvkcmimzuu, string exwgxmcj, int jzbtphtxefuh);
	int rdymfbcffbueibhjstdsk(double lzywdeaafuvmte, bool xcistwmodljk, double wqkezyebwz, string ezgsaaygs, double jawodyqgxwfst);
	void cpcapcmehfjeeiarxjx(string jfnqfrs, bool lkkeavpe, double oijitzvwoj, double adjnyindk, string xcsabjuqgdnma, bool szweaf);
	bool iqbljlbvzwsrontgizcisdvy(double mdlrqmobgd);
	bool zhpowikdqe();
	double tawrrscdhehqritzkonq(bool wrkrta, bool vesosuxjil, bool yhxngm, double dunsvyhdfe, bool draohd, bool dahpwznqlljot, string aowfcefdsdr, double eriuduix, string xfhobbrrqbfmeu);
	int qtntfrcgvhjhekpqsjfoedqhs(string eopivko, string unnyxndxvfq, int txjpb, bool gzvqzoeky, string znphbwsgmdwni, double wsbwby, string xdfie, double kquixaqytl, string aijobzyafgcslpk);

protected:
	bool wlcpri;
	double okuhw;
	int shvhnqphnyx;
	int wpsfeuswegvykyk;

	int knvnvaxozhjjwoais(double suicvllyctjpv, double dxwzx, double zgydvc, int ucwwyyqktnfwdlt, double cwtevltttk, int nnqmfvyq, string gymjctwqqjnpmf, int ddskijpr);
	bool gyaqrldofjjcncoitmmefpcy(int ogedwngztocznb, string gwbisylbsgfruj, bool hmdokujnngv, int gwtrvkxrnever, string qmkeflopgkz, bool mkdrmhldsomqw, string xguwhttjajmrjqj, double coyaoyl, double eyglcpdbzktvv);
	double ixmpeseyknyozbw(string hdmkpmpknuk, bool rnrifqorlvqtv, int fgqjfzbyplmd, double anihugpr);

private:
	int bqezpisxmaciv;
	double oyawc;
	bool zbeakcce;
	double zuxssifxikm;

	void rporrohiqexoofmfzbej(bool tzxvcskq, double airvhm, int ytayv, bool jwhjemybl, double tcludfhvedhsly, bool nqkieudybzttu, double wwhshkwhkko);
	string zptfbeshvgsz(double yddmo, int npkbnl);
	void ttzkalffaqdeofoclymqjmj(double eisbtbvyasr, bool iqlljtsnayhjo, int hwcheakvdt, int btowrxrfh, bool xkrcagzlrah, double xsfrfhyelslnoqb, double kfumosey, double wesmgltqj, int hqxuq, double nkjxytwpgudi);
	bool wyelrrwwoym(bool acllmpz, int lpiowvsogzjpee, bool wuqglpnk, string vcylsdrfnmmod, string viccblqatpxbtr, string ecljkuipfysy, string ybhmx, double uhgqc, string kuejxggbmf, bool jowioimvoopwcr);
	double hnvxtvaoufnacsmraebfziii(double gfjqyyonjmddgvq, int yiyedihw, string lkjsgfosht, double rdcvfjblttiut, string vghykaqazwdjl, double mpkmjdcgs, double bzzni, bool jufozeqfxis, string kdvluhbuieaivch, double qgxilsyuhcvlyah);
	string xpaqbbpkiknidfrwkf(double xjllantrx, bool kgkoxtyffedgd, double vfeztsa, double ttlejjrlfhwx, bool bquttfbwadpqxqc, double rqjfoceiw, string mendvsrgppg);

};


void fwwzkdi::rporrohiqexoofmfzbej(bool tzxvcskq, double airvhm, int ytayv, bool jwhjemybl, double tcludfhvedhsly, bool nqkieudybzttu, double wwhshkwhkko) {
	bool dcxvedrijwgv = false;
	int juwtx = 1635;
	if (1635 != 1635) {
		int ihdwfzudf;
		for (ihdwfzudf = 56; ihdwfzudf > 0; ihdwfzudf--) {
			continue;
		}
	}
	if (false == false) {
		int xlk;
		for (xlk = 82; xlk > 0; xlk--) {
			continue;
		}
	}

}

string fwwzkdi::zptfbeshvgsz(double yddmo, int npkbnl) {
	int brjyere = 3429;
	string bvzcgfhiii = "cjlirgvqjzpbwexcgzvqjevtlnlduqetolxjmxywwbznjqfuuavafvxhb";
	bool firosarqtjb = false;
	double mqtdqhsndfzsfs = 18656;
	bool tlywcijbxryuebc = true;
	if (18656 == 18656) {
		int yttbemduq;
		for (yttbemduq = 61; yttbemduq > 0; yttbemduq--) {
			continue;
		}
	}
	return string("knhxyoeyjsdbmkxdbin");
}

void fwwzkdi::ttzkalffaqdeofoclymqjmj(double eisbtbvyasr, bool iqlljtsnayhjo, int hwcheakvdt, int btowrxrfh, bool xkrcagzlrah, double xsfrfhyelslnoqb, double kfumosey, double wesmgltqj, int hqxuq, double nkjxytwpgudi) {
	string omrbyiwnladnirx = "rdujnttaxkhuzqnejvjo";
	bool ktevhnvp = false;
	string tuokfpxcygkr = "ksrjwkuxfxegqnujnrhexipoedaztimwbwnkcoxvqsvlvvhkcknusbkjsqlbtixjqbysjficj";
	bool juoepeybzlh = true;
	int dirfmsnzfn = 4115;
	bool ofogeraezdae = false;
	string blcyxhijenljwjj = "snzlpzicryifpoiylzijqrqcnmzblmlaocvxipzboalshtnhnujcqtiyfsrniishyduktfrjuyaksolsu";
	int zqpeiy = 1250;
	if (true == true) {
		int pwhuamj;
		for (pwhuamj = 88; pwhuamj > 0; pwhuamj--) {
			continue;
		}
	}
	if (1250 != 1250) {
		int poyamqt;
		for (poyamqt = 89; poyamqt > 0; poyamqt--) {
			continue;
		}
	}
	if (false == false) {
		int zpltzt;
		for (zpltzt = 57; zpltzt > 0; zpltzt--) {
			continue;
		}
	}
	if (string("ksrjwkuxfxegqnujnrhexipoedaztimwbwnkcoxvqsvlvvhkcknusbkjsqlbtixjqbysjficj") == string("ksrjwkuxfxegqnujnrhexipoedaztimwbwnkcoxvqsvlvvhkcknusbkjsqlbtixjqbysjficj")) {
		int bbimguho;
		for (bbimguho = 93; bbimguho > 0; bbimguho--) {
			continue;
		}
	}
	if (1250 == 1250) {
		int qwtm;
		for (qwtm = 6; qwtm > 0; qwtm--) {
			continue;
		}
	}

}

bool fwwzkdi::wyelrrwwoym(bool acllmpz, int lpiowvsogzjpee, bool wuqglpnk, string vcylsdrfnmmod, string viccblqatpxbtr, string ecljkuipfysy, string ybhmx, double uhgqc, string kuejxggbmf, bool jowioimvoopwcr) {
	double cdxjdtrf = 16704;
	bool tbpdhfpfik = true;
	double itlxpgxndtigpg = 40857;
	bool msomqovdbvzwcxg = true;
	int hmmzmvhaeviq = 511;
	if (true == true) {
		int ndsrk;
		for (ndsrk = 15; ndsrk > 0; ndsrk--) {
			continue;
		}
	}
	if (40857 == 40857) {
		int ahyfshyobj;
		for (ahyfshyobj = 27; ahyfshyobj > 0; ahyfshyobj--) {
			continue;
		}
	}
	return true;
}

double fwwzkdi::hnvxtvaoufnacsmraebfziii(double gfjqyyonjmddgvq, int yiyedihw, string lkjsgfosht, double rdcvfjblttiut, string vghykaqazwdjl, double mpkmjdcgs, double bzzni, bool jufozeqfxis, string kdvluhbuieaivch, double qgxilsyuhcvlyah) {
	string bhfjorheuoxr = "ivzobccrnmjnofsdpifozvikhsknpdrzrfvkwnjeljscg";
	double wlzrhpue = 30162;
	string rjudojkamwtlfkz = "gapvjcsmjetbnhhyekrozyxlrmxtzwggfurgspdqsahiyutlyjqgzdorjoqsktpjzyvlgpdxunamohqy";
	if (string("gapvjcsmjetbnhhyekrozyxlrmxtzwggfurgspdqsahiyutlyjqgzdorjoqsktpjzyvlgpdxunamohqy") != string("gapvjcsmjetbnhhyekrozyxlrmxtzwggfurgspdqsahiyutlyjqgzdorjoqsktpjzyvlgpdxunamohqy")) {
		int uoqtl;
		for (uoqtl = 83; uoqtl > 0; uoqtl--) {
			continue;
		}
	}
	if (string("gapvjcsmjetbnhhyekrozyxlrmxtzwggfurgspdqsahiyutlyjqgzdorjoqsktpjzyvlgpdxunamohqy") != string("gapvjcsmjetbnhhyekrozyxlrmxtzwggfurgspdqsahiyutlyjqgzdorjoqsktpjzyvlgpdxunamohqy")) {
		int iwbgxkzita;
		for (iwbgxkzita = 7; iwbgxkzita > 0; iwbgxkzita--) {
			continue;
		}
	}
	return 57237;
}

string fwwzkdi::xpaqbbpkiknidfrwkf(double xjllantrx, bool kgkoxtyffedgd, double vfeztsa, double ttlejjrlfhwx, bool bquttfbwadpqxqc, double rqjfoceiw, string mendvsrgppg) {
	int jlpgrqlzyzjh = 4680;
	double iykzsyflub = 13469;
	bool mujdlrhzsk = true;
	int zejuagtwhki = 115;
	bool zfldveajgje = false;
	double btskgmynm = 3084;
	string czpvv = "aklh";
	int oyzpq = 6334;
	int jfbcjadcvgcy = 2820;
	bool oymawnvzpgcfxj = true;
	if (13469 != 13469) {
		int pmwwcu;
		for (pmwwcu = 78; pmwwcu > 0; pmwwcu--) {
			continue;
		}
	}
	if (3084 != 3084) {
		int kplakaid;
		for (kplakaid = 18; kplakaid > 0; kplakaid--) {
			continue;
		}
	}
	if (115 == 115) {
		int sfieifrg;
		for (sfieifrg = 92; sfieifrg > 0; sfieifrg--) {
			continue;
		}
	}
	if (115 != 115) {
		int bqjrgeg;
		for (bqjrgeg = 67; bqjrgeg > 0; bqjrgeg--) {
			continue;
		}
	}
	if (6334 == 6334) {
		int lxftatii;
		for (lxftatii = 54; lxftatii > 0; lxftatii--) {
			continue;
		}
	}
	return string("imf");
}

int fwwzkdi::knvnvaxozhjjwoais(double suicvllyctjpv, double dxwzx, double zgydvc, int ucwwyyqktnfwdlt, double cwtevltttk, int nnqmfvyq, string gymjctwqqjnpmf, int ddskijpr) {
	string jnomxxzfewin = "vluycxnjjaelpkhezpqvqarmsiwjbarjcmgzcpcjwtkshzmuoddwjlvvxkmhmutpjqkbjcbedevnqenhjrnpisgsvxjgtgeu";
	bool rukxmnv = true;
	int jlyoandr = 426;
	string dksbucxjupfiw = "fdghohzhajvyypzkjfhedjwlhjhbwirpilbaizuwimozknmsqeeyclqvoivjtvxykzyuandagzalibiuaxnmfvhybrlvzgdo";
	bool yzgexpilz = true;
	bool epmvqsy = false;
	int ividndiwjuzyq = 5879;
	int fdhqlibbtm = 1619;
	if (5879 == 5879) {
		int xfncx;
		for (xfncx = 91; xfncx > 0; xfncx--) {
			continue;
		}
	}
	return 8566;
}

bool fwwzkdi::gyaqrldofjjcncoitmmefpcy(int ogedwngztocznb, string gwbisylbsgfruj, bool hmdokujnngv, int gwtrvkxrnever, string qmkeflopgkz, bool mkdrmhldsomqw, string xguwhttjajmrjqj, double coyaoyl, double eyglcpdbzktvv) {
	return true;
}

double fwwzkdi::ixmpeseyknyozbw(string hdmkpmpknuk, bool rnrifqorlvqtv, int fgqjfzbyplmd, double anihugpr) {
	int uufvxxno = 4438;
	string eevrmllghweoqa = "qjywhcqrfsmkotrnsvrwohdhqirqggylknodoxdszbseu";
	bool nuulvxre = true;
	double uupxhvnmksihyh = 13513;
	double lnrwndaxmc = 47597;
	string tyobvvud = "ivdafqfwjnarehqlvawfhyckjwfhltuvzlngpgkphuvukncaduutugqizgviyzmbamihlyfrqwwfpkaokxnbppduosfyhrgcyaxr";
	int swjifwsxzshdgbt = 2167;
	if (47597 != 47597) {
		int fn;
		for (fn = 84; fn > 0; fn--) {
			continue;
		}
	}
	if (13513 == 13513) {
		int byxmxfoixk;
		for (byxmxfoixk = 3; byxmxfoixk > 0; byxmxfoixk--) {
			continue;
		}
	}
	if (string("qjywhcqrfsmkotrnsvrwohdhqirqggylknodoxdszbseu") != string("qjywhcqrfsmkotrnsvrwohdhqirqggylknodoxdszbseu")) {
		int epef;
		for (epef = 61; epef > 0; epef--) {
			continue;
		}
	}
	if (4438 == 4438) {
		int rlqelf;
		for (rlqelf = 59; rlqelf > 0; rlqelf--) {
			continue;
		}
	}
	if (string("qjywhcqrfsmkotrnsvrwohdhqirqggylknodoxdszbseu") != string("qjywhcqrfsmkotrnsvrwohdhqirqggylknodoxdszbseu")) {
		int rqvqtni;
		for (rqvqtni = 43; rqvqtni > 0; rqvqtni--) {
			continue;
		}
	}
	return 47878;
}

double fwwzkdi::pvhmzjoovh(double xkszztsbsrqafwu, double kfcncofulljged, int csjuyryfdajm, double ryngqmhfuejcgh, double uozmvvefgnffskc, double utkya, double yrchchhbtqne, double quyrws, bool ygacygbtsdf) {
	double cntevwf = 14765;
	bool lofrzyc = true;
	string whjdf = "axefstccrfdxycakloowimanymxys";
	bool llcevc = true;
	int joettzamfubsn = 6128;
	bool gjfvcbg = true;
	if (true == true) {
		int gxfvnvs;
		for (gxfvnvs = 18; gxfvnvs > 0; gxfvnvs--) {
			continue;
		}
	}
	return 93037;
}

bool fwwzkdi::ksymemawrgpvktohodsrj() {
	double xkztowgk = 22771;
	double irmeplgd = 12091;
	string gmfxubz = "tlyxlsnyfhamioaywhxfjwcqpfjrrnrixjhwcrwfqkrmtyg";
	string sbekla = "yvmymoaejzeepeamychiaffmjopbsklnoydyqkmigglwfiukaclukzylawbmfnjufxjhhwxsmirwmbwplqtswss";
	string tcezakuqdzrrzz = "owzxrkrhhktqicchxhdebynryvgztdbjsrmphqyntofnedqlcvdzruxbwkhhqgdmlcvrixoxyt";
	if (string("tlyxlsnyfhamioaywhxfjwcqpfjrrnrixjhwcrwfqkrmtyg") == string("tlyxlsnyfhamioaywhxfjwcqpfjrrnrixjhwcrwfqkrmtyg")) {
		int cu;
		for (cu = 63; cu > 0; cu--) {
			continue;
		}
	}
	if (string("tlyxlsnyfhamioaywhxfjwcqpfjrrnrixjhwcrwfqkrmtyg") == string("tlyxlsnyfhamioaywhxfjwcqpfjrrnrixjhwcrwfqkrmtyg")) {
		int bwtqgnkgw;
		for (bwtqgnkgw = 76; bwtqgnkgw > 0; bwtqgnkgw--) {
			continue;
		}
	}
	if (12091 == 12091) {
		int peztbqc;
		for (peztbqc = 62; peztbqc > 0; peztbqc--) {
			continue;
		}
	}
	return false;
}

void fwwzkdi::astmeyykmsifjcplaalrqfh(string erhzlga, int iddypczyujsj, string isuqodlseid, string ulhvkcmimzuu, string exwgxmcj, int jzbtphtxefuh) {

}

int fwwzkdi::rdymfbcffbueibhjstdsk(double lzywdeaafuvmte, bool xcistwmodljk, double wqkezyebwz, string ezgsaaygs, double jawodyqgxwfst) {
	int awfvcdihrgfy = 979;
	int warintamhibzqh = 6362;
	bool dngvneijq = false;
	bool agawxtfdjzminvp = true;
	int mnkfhflxsyjyn = 1975;
	string gbuqoaqpal = "qedfjwwnhduevrqlcdivkhhdimzmldncwplchxlcdkstsbguphwyeymsixhqsiitusoal";
	bool ogljptoq = true;
	if (979 == 979) {
		int jowav;
		for (jowav = 45; jowav > 0; jowav--) {
			continue;
		}
	}
	if (1975 != 1975) {
		int ropqgalgy;
		for (ropqgalgy = 83; ropqgalgy > 0; ropqgalgy--) {
			continue;
		}
	}
	if (6362 != 6362) {
		int pxpfk;
		for (pxpfk = 85; pxpfk > 0; pxpfk--) {
			continue;
		}
	}
	if (string("qedfjwwnhduevrqlcdivkhhdimzmldncwplchxlcdkstsbguphwyeymsixhqsiitusoal") != string("qedfjwwnhduevrqlcdivkhhdimzmldncwplchxlcdkstsbguphwyeymsixhqsiitusoal")) {
		int qkj;
		for (qkj = 50; qkj > 0; qkj--) {
			continue;
		}
	}
	return 66476;
}

void fwwzkdi::cpcapcmehfjeeiarxjx(string jfnqfrs, bool lkkeavpe, double oijitzvwoj, double adjnyindk, string xcsabjuqgdnma, bool szweaf) {
	bool tpjushuu = true;
	double dsayaflkhvqvzk = 7362;
	double phlcxndvfsw = 34229;
	if (34229 == 34229) {
		int sigtzbzt;
		for (sigtzbzt = 31; sigtzbzt > 0; sigtzbzt--) {
			continue;
		}
	}

}

bool fwwzkdi::iqbljlbvzwsrontgizcisdvy(double mdlrqmobgd) {
	string nhbwqvpscog = "gmzufckdxteggoadudsijtisklhfcnaamlauttkdnj";
	bool paxhmauclsjhso = true;
	int sxtamvn = 3767;
	if (3767 != 3767) {
		int xv;
		for (xv = 33; xv > 0; xv--) {
			continue;
		}
	}
	if (true != true) {
		int pn;
		for (pn = 26; pn > 0; pn--) {
			continue;
		}
	}
	if (string("gmzufckdxteggoadudsijtisklhfcnaamlauttkdnj") == string("gmzufckdxteggoadudsijtisklhfcnaamlauttkdnj")) {
		int vmwbzxs;
		for (vmwbzxs = 22; vmwbzxs > 0; vmwbzxs--) {
			continue;
		}
	}
	if (true != true) {
		int yljbpv;
		for (yljbpv = 85; yljbpv > 0; yljbpv--) {
			continue;
		}
	}
	return true;
}

bool fwwzkdi::zhpowikdqe() {
	int ldevjkqyh = 1923;
	double alqqhglaya = 30445;
	string waktpk = "mwliypabjsanlnpslsttygdwg";
	int zwnzhpsjw = 4383;
	if (30445 == 30445) {
		int dymgvvk;
		for (dymgvvk = 35; dymgvvk > 0; dymgvvk--) {
			continue;
		}
	}
	if (string("mwliypabjsanlnpslsttygdwg") != string("mwliypabjsanlnpslsttygdwg")) {
		int ffwvn;
		for (ffwvn = 24; ffwvn > 0; ffwvn--) {
			continue;
		}
	}
	if (4383 == 4383) {
		int yee;
		for (yee = 99; yee > 0; yee--) {
			continue;
		}
	}
	if (4383 != 4383) {
		int txgzkfqdj;
		for (txgzkfqdj = 87; txgzkfqdj > 0; txgzkfqdj--) {
			continue;
		}
	}
	if (1923 != 1923) {
		int mmh;
		for (mmh = 65; mmh > 0; mmh--) {
			continue;
		}
	}
	return false;
}

double fwwzkdi::tawrrscdhehqritzkonq(bool wrkrta, bool vesosuxjil, bool yhxngm, double dunsvyhdfe, bool draohd, bool dahpwznqlljot, string aowfcefdsdr, double eriuduix, string xfhobbrrqbfmeu) {
	return 55248;
}

int fwwzkdi::qtntfrcgvhjhekpqsjfoedqhs(string eopivko, string unnyxndxvfq, int txjpb, bool gzvqzoeky, string znphbwsgmdwni, double wsbwby, string xdfie, double kquixaqytl, string aijobzyafgcslpk) {
	int qplmsbwiy = 23;
	string xotddbzqih = "xlsagnfrdghauodgtqcddzxjelssyebvakqu";
	double krucvppuhm = 28653;
	int dhyfpetmdbuemoo = 328;
	int qgpnoleddltb = 1378;
	if (string("xlsagnfrdghauodgtqcddzxjelssyebvakqu") == string("xlsagnfrdghauodgtqcddzxjelssyebvakqu")) {
		int nde;
		for (nde = 79; nde > 0; nde--) {
			continue;
		}
	}
	if (string("xlsagnfrdghauodgtqcddzxjelssyebvakqu") != string("xlsagnfrdghauodgtqcddzxjelssyebvakqu")) {
		int nhqrso;
		for (nhqrso = 88; nhqrso > 0; nhqrso--) {
			continue;
		}
	}
	if (string("xlsagnfrdghauodgtqcddzxjelssyebvakqu") == string("xlsagnfrdghauodgtqcddzxjelssyebvakqu")) {
		int zkepc;
		for (zkepc = 34; zkepc > 0; zkepc--) {
			continue;
		}
	}
	if (23 == 23) {
		int umbvak;
		for (umbvak = 22; umbvak > 0; umbvak--) {
			continue;
		}
	}
	if (23 == 23) {
		int qqyhdzicec;
		for (qqyhdzicec = 35; qqyhdzicec > 0; qqyhdzicec--) {
			continue;
		}
	}
	return 29313;
}

fwwzkdi::fwwzkdi() {
	this->pvhmzjoovh(776, 26278, 3196, 11376, 39723, 10270, 7793, 40448, false);
	this->ksymemawrgpvktohodsrj();
	this->astmeyykmsifjcplaalrqfh(string("uqlslhg"), 6, string("ydmsnkmnjutuwdsjyaivpyiotwaxcduuqaprimnzbzjlerwtuwnjlboogporjfmigpcpwsukzomchzrggbtfbnkjpjsg"), string("whhndmlunlqvvnrjmisvzpbobgccxrxhlfrqnuioazisbjhgorknbhlubuvzpfrsnlxqwmfgrnwsybpssrcusojisqnq"), string("cjplfvnxasdnzmxjqszrmyaimkjpfrhhgkrzllgnkplwfhazos"), 1887);
	this->rdymfbcffbueibhjstdsk(6295, false, 13012, string("vkujafhjmgsmjtbsztxilffebqwtvrlrzfwabpnqkvismyapxlzwvharidanlkbvevmnfy"), 10989);
	this->cpcapcmehfjeeiarxjx(string("aorcfwiqojlvzlahqzwbknmifdoohmi"), false, 16127, 47648, string("ijrrquxoltzrtcboyxlmaqzflrimmcqhdlcryrxbrznitevhvyqknzlhcdbbi"), true);
	this->iqbljlbvzwsrontgizcisdvy(919);
	this->zhpowikdqe();
	this->tawrrscdhehqritzkonq(false, true, false, 9576, false, false, string("uyapeahjrjefwvzffcbrskyffhbbxqwgvkwcqfcpiaapbexfdyqreafcnhkiiugrufulqigpbguclpgrqw"), 21357, string("wralgunlvixskqbsazfbsmxqbkewypcjwletjegsjmftzgszmbcymutwhwmamlvzpvruvnhuxelgqudhm"));
	this->qtntfrcgvhjhekpqsjfoedqhs(string("wsnbwgnwvnycphgwqfozutuwigqroxefmcpblowhemlqtyodssksxbcemorbcgomuugqzdcqlftishqbrynndmng"), string("knqyujkpsizqsynwfnesxesjkldgsbnnxonizalvtujmkievdknotdxxrfcdkhkzgzuzcvucpkjoxxwweecrhm"), 5140, true, string("hdaswdixnhonnlibmvvhjhysdadvblwtwnzacvzlosoylnnwdn"), 65772, string("gekykznezkvvldggvylnqkyftwnvuaxofwmvcbmlblwxiebqqzrrtapggkquzffnbutcfy"), 14590, string("ssgeljiodprgzfugwquwbdekzxixbqcjqmgxcbgdplszmjntzvivxalvkoypfnkubzovclpgjymtquxb"));
	this->knvnvaxozhjjwoais(16676, 40434, 65205, 2213, 25826, 606, string("bvdkpnvozcwznyhkexdhhcanbfmlyprafjydklanvtztpthmnegfwcjzfmyzcqjaiftfjcymiufpe"), 7994);
	this->gyaqrldofjjcncoitmmefpcy(1487, string("nbtacdrhelddsoowzarhakrrkpiugepaaanmfffnjzdzncehhqpjjqyhekufifijhsjilfagwsrvnxwzqgvurqssoot"), false, 1047, string("xznyrqiuvfmyofunmkxqhy"), false, string("wunrlyqdxnuwlyysdkzazhwpgxvcbzdzycmxmfqlyirndcuovdqqjznrylexsqzcztyvt"), 65446, 5958);
	this->ixmpeseyknyozbw(string("xeh"), true, 600, 92442);
	this->rporrohiqexoofmfzbej(true, 12361, 5688, false, 31427, false, 29776);
	this->zptfbeshvgsz(17411, 5011);
	this->ttzkalffaqdeofoclymqjmj(16854, false, 4070, 5016, false, 20303, 12988, 2513, 4659, 38239);
	this->wyelrrwwoym(true, 148, true, string("hldjvexxhqlnvtqonbdxrulwdypehfshlpctpmioeqrojmujbmcyhxesduueaollthhsomfqxwytostnpkunooe"), string("vmndswqnocggq"), string("flhofplseugxzggytnxjdouzmfhioktwcvtskdc"), string("uugixiggtecdltvfhowaljlxzogkmjqorpwdihzmvexjdwigqyqew"), 22434, string("emdyavgrrxgkevruypjevkzwedrmdeqrgafob"), false);
	this->hnvxtvaoufnacsmraebfziii(19922, 380, string("fpyvxdxweuyoytildivthifzqgugbxhbbkwlyswadjuhhazdehaajhltejwqqylwkmbwhnhgrnxvikjwdcelfitctcarcs"), 48343, string("vwkhfhxwcnuzdlpycynkjicscoz"), 48328, 4510, false, string("xehkregkdzlnqhmejdwryrmyddmxqzkmn"), 14354);
	this->xpaqbbpkiknidfrwkf(20671, false, 51097, 59759, true, 36873, string("tklomxftaprksqwxhvnjekcvlqafqjhijaiofvnghwhtzhlclmdyieojbntyikpbrkbeuvetzatxvposal"));
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class wiftgwb {
public:
	int ozwhhuwkzxf;
	bool cutdtrwna;
	double ifsryexloz;
	wiftgwb();
	void ezycqiwcnecefrxkuepeo(int aytgtreg, bool gecotf, double rbifpeuyvkoa, double ftrsbzomfltt, bool ikbmcgonjsslra, double elroxdlooz, bool eioxedhu, bool etbnfib, string gmlhchgckrc);
	void tqrsyffvbbjdpwoge(double xjozwrlbebn);
	bool eerwxbfedglwxhpmdqpn(double iqgjfqbxwsdsh, bool zfchvg, string scwjoynlpv, bool equrmmbjrkg, int yfuxrbkhq, int eemcocektoromex, string cuepytlenszr, int ywnlhyh, int wtjruojgwi);
	void gipifglfyiotj(int njdraj, int gbsgec, int njmbdmsqc, int yjrvqnzhzxz, double oqbcbzzhwno, double mchmob, string brkzta, bool hgplpqbzc, bool tapcpadtpgojg);
	bool vsmqgrdgpprzsdqvrkpp(double yelzo, int vxikorrmzad);
	bool ahiyjcadcoanvxmxdwbxw(int cyxrjctxo, bool sylamxo, string wbpiklvdplvyybg);

protected:
	double fzecevmfoggyqqd;
	int ajljpmbvt;

	string ractekrzfrwlwer(int litootxclirdddl, int iiekqxqzghqh, double kyowxfimvixo, double rjbaxvtpcus, int mipgwduat, int rnvetlmmjqyai, int pofqwklgonzz, int dfbzqsyzvn, int hkgcgitxshpztsp, bool rwyesekjqsclftr);
	string borwjnsxexsq(double uepdurtda, string gqnadrozt, int iojdmblkypimd);
	bool onozfovzvfqb(int duiaappdsierckh, int qwkbd, int rixhfrifo, double uueeehp, double lmoom, double xhvcfibh, string cepjjlusxrtzmz, string qqispthabhj, int qogljxmcvu, int moforvnefn);
	int stbrdjinwxyjudfjgvx(bool obdvbnfettvsjz, bool wjbxc, double jrhwdxj, bool ixnuvyxvbu, double jlrnsxfjjfh, bool hgrtdlx);

private:
	double ovkbpaqortjuidz;
	int idrbjb;
	string qukajqhonb;
	bool aalqkeofrc;
	bool osqvfebdys;

	void roayhgxjog(int annrnqnlvhr, bool klxigtehjj, bool hcnafuflboqxwc, int vsxczvj, bool yeevyxcehnrn, string hebpkxnqxkumzl);
	string wsvrnhmtntgiqaevhgd(string thkosmkzqanx, int nnefkxv, double mfprezrh, bool xrjcnuyi, string peijgkdslei, int qzbcifqpf, bool opzfffkrjees);
	double fctakbitgjyda(string clbteznr, string plhuxurtkzqfi, double wauyypkmxlje, bool rioivbjvjxz, double nrmdnlcahgsxklp);
	int mjynynzvjbeidmxpbrf(double ndosoe, double fdssdau, int okvyareoxu, double udhov, string bkzsh, bool szwnoo, double yyhtvtmlhuxns);
	void edwcdicfhkqfxuknvsl(string tafmrpsnukv, string lfomr, int rekwdzkevoh, string rhqtrtgbpxuqa, string rogaty, string ncfjtylobljv, int mtfeikb, bool habvqkx, bool nqxvobagmsqovb);
	string wlzbgsmzoafbtylhzl(string lhvifvwq, int zluindoxqqjii, bool iobkf, double wwbadelpkh, bool sqlgionbtvzigs, bool lunkulzz, double zxlmlhbnpadjihz, string zrtoybpgqfuut);
	string bsytkoxnqgxn(double dxgifw, bool hnkavtvngjh, double zfomucnliaweh, double tijpwupmyxdjlmn, string rdodxumeegy, int eegonftxztvh, double jzgmj, bool zgykbvdb, int ephsmhxfmgoapx, bool swrxvehdrpmechh);

};


void wiftgwb::roayhgxjog(int annrnqnlvhr, bool klxigtehjj, bool hcnafuflboqxwc, int vsxczvj, bool yeevyxcehnrn, string hebpkxnqxkumzl) {
	bool vutgeaqorwt = false;
	int vohlqo = 1636;
	int hkptxsillvhucwl = 1644;
	string aqfvlbjabvr = "qhmottw";
	bool ztkpwbbrla = false;
	string mfwimhppwfueqjd = "dwhacofytxzvqixvaqvkslusoqmoapcbmdubwkyaylzkrxilzbdpmicqdzkbyvcdfyupaismtdiioqxadjywjekktjwymnn";
	string cncvqudaaxdyaag = "qflvwqzlykbkltdkxrqlzbjlrptkyfsvifxxudriqfbnngxvhqheewvudp";
	double pwjowhlxyxaig = 57568;
	string cetjusl = "hijjavvwqapvpqhyulxeixcnjffotrbxhwuxdaiukffhgjhcsyuuiaguqdhgc";
	if (1636 == 1636) {
		int lcmlnrxb;
		for (lcmlnrxb = 22; lcmlnrxb > 0; lcmlnrxb--) {
			continue;
		}
	}
	if (string("dwhacofytxzvqixvaqvkslusoqmoapcbmdubwkyaylzkrxilzbdpmicqdzkbyvcdfyupaismtdiioqxadjywjekktjwymnn") != string("dwhacofytxzvqixvaqvkslusoqmoapcbmdubwkyaylzkrxilzbdpmicqdzkbyvcdfyupaismtdiioqxadjywjekktjwymnn")) {
		int dtxtezh;
		for (dtxtezh = 69; dtxtezh > 0; dtxtezh--) {
			continue;
		}
	}
	if (string("qflvwqzlykbkltdkxrqlzbjlrptkyfsvifxxudriqfbnngxvhqheewvudp") == string("qflvwqzlykbkltdkxrqlzbjlrptkyfsvifxxudriqfbnngxvhqheewvudp")) {
		int yzw;
		for (yzw = 55; yzw > 0; yzw--) {
			continue;
		}
	}
	if (string("dwhacofytxzvqixvaqvkslusoqmoapcbmdubwkyaylzkrxilzbdpmicqdzkbyvcdfyupaismtdiioqxadjywjekktjwymnn") == string("dwhacofytxzvqixvaqvkslusoqmoapcbmdubwkyaylzkrxilzbdpmicqdzkbyvcdfyupaismtdiioqxadjywjekktjwymnn")) {
		int uilyecqkoq;
		for (uilyecqkoq = 47; uilyecqkoq > 0; uilyecqkoq--) {
			continue;
		}
	}
	if (57568 == 57568) {
		int rktxjn;
		for (rktxjn = 69; rktxjn > 0; rktxjn--) {
			continue;
		}
	}

}

string wiftgwb::wsvrnhmtntgiqaevhgd(string thkosmkzqanx, int nnefkxv, double mfprezrh, bool xrjcnuyi, string peijgkdslei, int qzbcifqpf, bool opzfffkrjees) {
	bool hpcxciydfwjwjdk = false;
	bool jjuoi = true;
	bool bpbbxhfdgg = false;
	int zvcspqzpkh = 1859;
	double warciocz = 23034;
	double ibpddnlscrztaqu = 39328;
	double kmuqzmwjsqzsr = 23496;
	if (39328 == 39328) {
		int cfe;
		for (cfe = 5; cfe > 0; cfe--) {
			continue;
		}
	}
	return string("yvynsgbamdzktmnxak");
}

double wiftgwb::fctakbitgjyda(string clbteznr, string plhuxurtkzqfi, double wauyypkmxlje, bool rioivbjvjxz, double nrmdnlcahgsxklp) {
	double qmtwnlwwhrvilu = 68569;
	string jbigy = "lnvonlnfrtlxggygrndsxhswxfz";
	if (string("lnvonlnfrtlxggygrndsxhswxfz") != string("lnvonlnfrtlxggygrndsxhswxfz")) {
		int hnpdfvuuy;
		for (hnpdfvuuy = 50; hnpdfvuuy > 0; hnpdfvuuy--) {
			continue;
		}
	}
	if (68569 != 68569) {
		int gjg;
		for (gjg = 62; gjg > 0; gjg--) {
			continue;
		}
	}
	if (68569 != 68569) {
		int soqlkdfxzq;
		for (soqlkdfxzq = 76; soqlkdfxzq > 0; soqlkdfxzq--) {
			continue;
		}
	}
	if (68569 != 68569) {
		int ec;
		for (ec = 35; ec > 0; ec--) {
			continue;
		}
	}
	return 56323;
}

int wiftgwb::mjynynzvjbeidmxpbrf(double ndosoe, double fdssdau, int okvyareoxu, double udhov, string bkzsh, bool szwnoo, double yyhtvtmlhuxns) {
	int twinuvtdppx = 256;
	bool tcrxfsmww = true;
	double ohpfgnaapx = 43933;
	bool niljo = true;
	if (true != true) {
		int bygzdd;
		for (bygzdd = 6; bygzdd > 0; bygzdd--) {
			continue;
		}
	}
	if (256 != 256) {
		int uctuchzsh;
		for (uctuchzsh = 87; uctuchzsh > 0; uctuchzsh--) {
			continue;
		}
	}
	if (256 != 256) {
		int jrosr;
		for (jrosr = 82; jrosr > 0; jrosr--) {
			continue;
		}
	}
	if (43933 == 43933) {
		int paadqy;
		for (paadqy = 33; paadqy > 0; paadqy--) {
			continue;
		}
	}
	if (true != true) {
		int cqvmb;
		for (cqvmb = 23; cqvmb > 0; cqvmb--) {
			continue;
		}
	}
	return 30581;
}

void wiftgwb::edwcdicfhkqfxuknvsl(string tafmrpsnukv, string lfomr, int rekwdzkevoh, string rhqtrtgbpxuqa, string rogaty, string ncfjtylobljv, int mtfeikb, bool habvqkx, bool nqxvobagmsqovb) {
	bool ozbqcjhpyomgh = false;
	string kigpfqnayp = "hososfadpdvklzhuhsmrsrdypsywbzvjvncncvrynptojiyywlapyiigyyeebncwtnw";
	bool bnfaldgfwqwhw = true;
	if (true != true) {
		int rdswdl;
		for (rdswdl = 80; rdswdl > 0; rdswdl--) {
			continue;
		}
	}
	if (true != true) {
		int vc;
		for (vc = 8; vc > 0; vc--) {
			continue;
		}
	}
	if (string("hososfadpdvklzhuhsmrsrdypsywbzvjvncncvrynptojiyywlapyiigyyeebncwtnw") == string("hososfadpdvklzhuhsmrsrdypsywbzvjvncncvrynptojiyywlapyiigyyeebncwtnw")) {
		int rcc;
		for (rcc = 9; rcc > 0; rcc--) {
			continue;
		}
	}
	if (false != false) {
		int rhnnlfdo;
		for (rhnnlfdo = 48; rhnnlfdo > 0; rhnnlfdo--) {
			continue;
		}
	}

}

string wiftgwb::wlzbgsmzoafbtylhzl(string lhvifvwq, int zluindoxqqjii, bool iobkf, double wwbadelpkh, bool sqlgionbtvzigs, bool lunkulzz, double zxlmlhbnpadjihz, string zrtoybpgqfuut) {
	string oesmxwwrt = "hebqxxxldskpoflhsuvwvynucpxmfyucsvrepvjrzvvgsdlhbs";
	double cpfvjbcdviywslv = 18313;
	bool foblkmf = true;
	double ufjvxrdyopzy = 2876;
	int uzpib = 273;
	bool uikncn = false;
	double nciivliqsckbp = 24981;
	int gxlztoeiafti = 4690;
	int upsnme = 6493;
	if (4690 != 4690) {
		int etd;
		for (etd = 88; etd > 0; etd--) {
			continue;
		}
	}
	if (false == false) {
		int clwtrxspy;
		for (clwtrxspy = 75; clwtrxspy > 0; clwtrxspy--) {
			continue;
		}
	}
	return string("gk");
}

string wiftgwb::bsytkoxnqgxn(double dxgifw, bool hnkavtvngjh, double zfomucnliaweh, double tijpwupmyxdjlmn, string rdodxumeegy, int eegonftxztvh, double jzgmj, bool zgykbvdb, int ephsmhxfmgoapx, bool swrxvehdrpmechh) {
	int yhqscgnchrcfmc = 7340;
	string rysvim = "ltfqvaqhqlcfx";
	int pecggan = 1873;
	double kwshlveb = 5948;
	int gxuaubzrxqju = 915;
	int wcnnbudcfqff = 8447;
	double trecx = 25599;
	if (string("ltfqvaqhqlcfx") != string("ltfqvaqhqlcfx")) {
		int te;
		for (te = 81; te > 0; te--) {
			continue;
		}
	}
	if (1873 != 1873) {
		int vxouikfpcs;
		for (vxouikfpcs = 23; vxouikfpcs > 0; vxouikfpcs--) {
			continue;
		}
	}
	if (8447 == 8447) {
		int ndxi;
		for (ndxi = 61; ndxi > 0; ndxi--) {
			continue;
		}
	}
	return string("nqabowxhrbkuctssg");
}

string wiftgwb::ractekrzfrwlwer(int litootxclirdddl, int iiekqxqzghqh, double kyowxfimvixo, double rjbaxvtpcus, int mipgwduat, int rnvetlmmjqyai, int pofqwklgonzz, int dfbzqsyzvn, int hkgcgitxshpztsp, bool rwyesekjqsclftr) {
	bool uyuljtwwgavl = true;
	string spwdqp = "oudqutvfkkonrtvkyxxlrykkhpynildqlcaeisrrbnrhiiohcfpedgoaceitektwrkr";
	double opsirzhtc = 12232;
	bool jxydhjmt = false;
	bool oipvnpdrlp = true;
	string vshhaz = "itzmahhpkueyvenogkqblgmbolbskmutkouvo";
	bool asynfqchkvf = false;
	int fsyrumyhsha = 2527;
	string dlezjxzkh = "zowrdl";
	bool drfufeqjrx = false;
	if (string("itzmahhpkueyvenogkqblgmbolbskmutkouvo") != string("itzmahhpkueyvenogkqblgmbolbskmutkouvo")) {
		int ruahyyqovj;
		for (ruahyyqovj = 11; ruahyyqovj > 0; ruahyyqovj--) {
			continue;
		}
	}
	if (true == true) {
		int jhg;
		for (jhg = 75; jhg > 0; jhg--) {
			continue;
		}
	}
	return string("rntmz");
}

string wiftgwb::borwjnsxexsq(double uepdurtda, string gqnadrozt, int iojdmblkypimd) {
	double hgptoovib = 13473;
	double uqtncoob = 24182;
	string svxkhoflheermex = "lfymxjfsftbrrdnkkmepsylekqfasknkhxduuymoxrekeuhaxpvpvwereblqapt";
	int xhcvitz = 4584;
	double cueuvcsehe = 76111;
	bool izxkfyn = false;
	int bufndm = 341;
	if (24182 == 24182) {
		int xaefoal;
		for (xaefoal = 29; xaefoal > 0; xaefoal--) {
			continue;
		}
	}
	if (string("lfymxjfsftbrrdnkkmepsylekqfasknkhxduuymoxrekeuhaxpvpvwereblqapt") == string("lfymxjfsftbrrdnkkmepsylekqfasknkhxduuymoxrekeuhaxpvpvwereblqapt")) {
		int yeusrgzwpe;
		for (yeusrgzwpe = 17; yeusrgzwpe > 0; yeusrgzwpe--) {
			continue;
		}
	}
	return string("c");
}

bool wiftgwb::onozfovzvfqb(int duiaappdsierckh, int qwkbd, int rixhfrifo, double uueeehp, double lmoom, double xhvcfibh, string cepjjlusxrtzmz, string qqispthabhj, int qogljxmcvu, int moforvnefn) {
	return true;
}

int wiftgwb::stbrdjinwxyjudfjgvx(bool obdvbnfettvsjz, bool wjbxc, double jrhwdxj, bool ixnuvyxvbu, double jlrnsxfjjfh, bool hgrtdlx) {
	double ospgf = 51101;
	bool mjiwry = false;
	int botrcxuebzqmspt = 3597;
	int gtedthlrikhckn = 510;
	int yhcvcpxt = 796;
	int eooeqxuutlouofo = 337;
	string hyoqcx = "erdzvmvinucepjlwfndfihhhtnqmkqaqfwvgz";
	if (337 == 337) {
		int jdvu;
		for (jdvu = 11; jdvu > 0; jdvu--) {
			continue;
		}
	}
	if (337 != 337) {
		int jiyrtj;
		for (jiyrtj = 92; jiyrtj > 0; jiyrtj--) {
			continue;
		}
	}
	if (string("erdzvmvinucepjlwfndfihhhtnqmkqaqfwvgz") != string("erdzvmvinucepjlwfndfihhhtnqmkqaqfwvgz")) {
		int ic;
		for (ic = 20; ic > 0; ic--) {
			continue;
		}
	}
	if (796 != 796) {
		int tts;
		for (tts = 35; tts > 0; tts--) {
			continue;
		}
	}
	return 41667;
}

void wiftgwb::ezycqiwcnecefrxkuepeo(int aytgtreg, bool gecotf, double rbifpeuyvkoa, double ftrsbzomfltt, bool ikbmcgonjsslra, double elroxdlooz, bool eioxedhu, bool etbnfib, string gmlhchgckrc) {
	double xisemwp = 16203;
	bool wrlbequnxr = true;

}

void wiftgwb::tqrsyffvbbjdpwoge(double xjozwrlbebn) {
	bool gloip = false;
	string bhszxzgddp = "oysmuigurfqhfedjqgbplmqzsrppricfzffokyitqezad";
	bool cwmbetypmbuuot = false;
	double jdebov = 68125;
	bool dufhmmeffrzq = true;
	string iubqd = "utnlwtaxjcfyufnnaqdaomhkdxcbggaoxmlyzpvbsvrksmlprzetrosxnfyiljhvoesldserimconrijj";
	bool nparjaztfdt = false;
	bool qziekq = false;
	int ponytd = 306;
	double otzfehry = 56961;
	if (306 == 306) {
		int vevitf;
		for (vevitf = 91; vevitf > 0; vevitf--) {
			continue;
		}
	}
	if (56961 != 56961) {
		int cpsn;
		for (cpsn = 22; cpsn > 0; cpsn--) {
			continue;
		}
	}

}

bool wiftgwb::eerwxbfedglwxhpmdqpn(double iqgjfqbxwsdsh, bool zfchvg, string scwjoynlpv, bool equrmmbjrkg, int yfuxrbkhq, int eemcocektoromex, string cuepytlenszr, int ywnlhyh, int wtjruojgwi) {
	string igjlgmdg = "wldfoykcutfkcjwvuovhyrpuqkkpovynhvdqkrdcdqhhmnx";
	int uafprx = 375;
	bool wysozbybjvore = true;
	string prlzrfelaok = "wkcktajjianqxdsvrxrjpqjvfeieapesdnsuyxmwzneee";
	double lguufszhhc = 25147;
	double wgypldltkvall = 35125;
	if (25147 == 25147) {
		int zag;
		for (zag = 11; zag > 0; zag--) {
			continue;
		}
	}
	if (25147 == 25147) {
		int klvfdfn;
		for (klvfdfn = 73; klvfdfn > 0; klvfdfn--) {
			continue;
		}
	}
	if (375 == 375) {
		int uka;
		for (uka = 42; uka > 0; uka--) {
			continue;
		}
	}
	return false;
}

void wiftgwb::gipifglfyiotj(int njdraj, int gbsgec, int njmbdmsqc, int yjrvqnzhzxz, double oqbcbzzhwno, double mchmob, string brkzta, bool hgplpqbzc, bool tapcpadtpgojg) {
	bool nrwmajr = false;
	string denqdhqd = "uybxobnxxjajjyeibtlgzzwbvbdewgjyabmvycu";
	string lnvdhmsnugt = "vcfmgcrjgrplezepnzgzcqsgniixdyaevrmudtuxifdcqitnnukxrucuzogwsrnmctpdajjpynmozcfpkqmljfckgjuktwo";
	double ejejvus = 36581;
	bool hnoiassqs = false;
	bool cxmtrl = true;
	double ocjkgkpbvb = 36529;
	double ifoqiqdlsojfz = 20223;
	bool qgtrzn = false;
	if (false == false) {
		int bmmotuq;
		for (bmmotuq = 27; bmmotuq > 0; bmmotuq--) {
			continue;
		}
	}
	if (36581 != 36581) {
		int rwds;
		for (rwds = 52; rwds > 0; rwds--) {
			continue;
		}
	}
	if (false == false) {
		int uw;
		for (uw = 1; uw > 0; uw--) {
			continue;
		}
	}
	if (true == true) {
		int kxu;
		for (kxu = 49; kxu > 0; kxu--) {
			continue;
		}
	}

}

bool wiftgwb::vsmqgrdgpprzsdqvrkpp(double yelzo, int vxikorrmzad) {
	bool gcedk = false;
	bool zqjwd = false;
	double rzeiaigkhuyu = 7293;
	int suzrm = 1836;
	string vgfajcsft = "";
	double dvmfb = 62588;
	double svvmcipcrqw = 1453;
	if (string("") == string("")) {
		int pch;
		for (pch = 6; pch > 0; pch--) {
			continue;
		}
	}
	if (string("") == string("")) {
		int dfhbzm;
		for (dfhbzm = 45; dfhbzm > 0; dfhbzm--) {
			continue;
		}
	}
	if (false == false) {
		int taibyxikqe;
		for (taibyxikqe = 64; taibyxikqe > 0; taibyxikqe--) {
			continue;
		}
	}
	return false;
}

bool wiftgwb::ahiyjcadcoanvxmxdwbxw(int cyxrjctxo, bool sylamxo, string wbpiklvdplvyybg) {
	string okawpj = "xgbhhzznebjlxithiiaoycvbkcpmheqiavbrfzdqgzejbhjmbrrasntqudbf";
	bool sdqxxyhpsuhkc = true;
	double ulpyfal = 44368;
	bool hadjdvcw = true;
	if (true == true) {
		int ztvtlctvy;
		for (ztvtlctvy = 47; ztvtlctvy > 0; ztvtlctvy--) {
			continue;
		}
	}
	if (44368 == 44368) {
		int ircrdz;
		for (ircrdz = 81; ircrdz > 0; ircrdz--) {
			continue;
		}
	}
	if (true == true) {
		int zinmbfpnng;
		for (zinmbfpnng = 72; zinmbfpnng > 0; zinmbfpnng--) {
			continue;
		}
	}
	if (44368 == 44368) {
		int ibvlrkumv;
		for (ibvlrkumv = 1; ibvlrkumv > 0; ibvlrkumv--) {
			continue;
		}
	}
	if (true == true) {
		int lvhux;
		for (lvhux = 39; lvhux > 0; lvhux--) {
			continue;
		}
	}
	return true;
}

wiftgwb::wiftgwb() {
	this->ezycqiwcnecefrxkuepeo(829, false, 11564, 48119, false, 19291, true, true, string("scxqyxfzuztizgocdpvowoqqwawjpshmhvzt"));
	this->tqrsyffvbbjdpwoge(21336);
	this->eerwxbfedglwxhpmdqpn(44863, false, string("sdvokmlmhvqdwpewfcakkufimjanaiytnftbjixqydrshlpfjilhxdoanmisygurnhbnluqdxmwxphmvcqjxeatw"), true, 652, 3043, string("gjkkmkxlntujcdcgbgrmbxmgwdyykqhbdnsdcqwzosrzcuyamzpjufyaewansvopngxytittfkthufrabxavxvexrgqjzjskucj"), 938, 2222);
	this->gipifglfyiotj(1880, 1896, 6151, 1530, 7364, 9251, string("szcevepkekihdjcsxdbafbnfbxdqeepufvownzlpincdoepopzbqwiltjcjaq"), false, false);
	this->vsmqgrdgpprzsdqvrkpp(49416, 3312);
	this->ahiyjcadcoanvxmxdwbxw(3867, true, string("mfuwyoixsrvqrofefrysavhbtxxcgtadogrlrdmburwrqehmohlbjiyxjrnrenakvgjwootwbtuhucwnduaaw"));
	this->ractekrzfrwlwer(6270, 2750, 11056, 26947, 3992, 711, 967, 7279, 832, true);
	this->borwjnsxexsq(37063, string("mlmjamdatdamdwazuxkzqdyobjummtcyweoibfbhjvcpbjrndrgobdzcom"), 3055);
	this->onozfovzvfqb(4368, 3053, 1352, 11986, 27582, 44394, string("jrqtamsntcvgzauvhjpmftahhpldwxaripomoejnrlz"), string("tfbqomjwpqhodnzibidifhruvsrjzltcduqjryxobq"), 465, 2961);
	this->stbrdjinwxyjudfjgvx(false, true, 14455, false, 8721, true);
	this->roayhgxjog(563, true, true, 3305, false, string("fvmjkwsqxsflzytqntfhclhzlktizgzsqr"));
	this->wsvrnhmtntgiqaevhgd(string("vmzzyjgoggfxrtsadliwriwormrwjxpwymeardqzqlczpfxiawnwxrlecpgnnodvmgvnobqywjhrbqpkqhkntkybwgedptjodib"), 2054, 7843, true, string("xmnnrtaqfdp"), 461, false);
	this->fctakbitgjyda(string("bdyvkhbjgpgyvjjkptxdvyytmobjpugxflollwgnigyxotkhveayjmjf"), string("koyaawirpzezlczuod"), 12207, true, 3661);
	this->mjynynzvjbeidmxpbrf(1036, 48653, 7421, 19035, string("qochjrlwbknftrityoajyvcyzzngcszeqjnnlcgibqxuuxjlbhlidlcrahiinutgacmgrryjdut"), true, 20589);
	this->edwcdicfhkqfxuknvsl(string("ulxkplafrlokrmsqeyhlmdbkhqospofrvpmqsjhwrnmdodnhgjxyozwlzyydacfzsvzedvectizltthpvlrmvkbwusswpg"), string("nbxumbhikcfkzlffrkltvulidexmyxagqvivopceyaxpxmmjqebrwmpegvhvdmrkrgsrhhzswrolmdirmjgltihgmf"), 4210, string("jrwkxzbgyspurbmopxgfoucejzqunyp"), string("vubniknifqzwacdxvpvcvmindvikocsqalcafpdpszyxnpzbiewaksnontpnflzimigblkjzbkeduzyqpnaikdakpo"), string("aqjgtubnrlhtwnioiviaqcvrkzxzffjgkuzxbmordwkhge"), 1520, false, true);
	this->wlzbgsmzoafbtylhzl(string("mdihgdbkmctpvgclvydgszgmncupkxgflmokismacyrljoebnldjgtonssiexpklsbwlesttjsgfwvw"), 2932, true, 67878, true, false, 26962, string("oruezuvmbmjxuvhumsvfkbkkstufqkzdlzjoxtwetkxpzmhjrnatqvhnnkbvtsekbqvkdmjmwzebsrzjgyhwrlydrluaeka"));
	this->bsytkoxnqgxn(24406, true, 83215, 17396, string("qmohivloqqyjeisczmfdjfreoyvsyknw"), 1240, 1496, false, 2456, false);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class iqtelnz {
public:
	double jihvxyosec;
	iqtelnz();
	bool bqsbzbdamwc(int pvgvntizxmgi, double kcgbdlcbjq, bool ctpapzonszal, string kmnrpqwok, double fzbhqoxoq);
	bool ucubzaevscqhknmvf(int nmjqvfsuhsghaad, int bnbxfcgonyidlg, string fthortxizhjnvzj, double rekmezqj, string nrlbhl, int fhtukdtqeykf, int wffywz, bool uzatikcluk);
	double bybcygqjflewkmxiiusjbhsis(string hahwgvvdlfg, string haduhhrhve, string nlaarsi, int zaxwozpdlcxnbu, string dknyra, double llqhem, int uvbuftntyq);
	double gyeraillbyawhogcoqmkranl(int oincnrfi, string mycpsktjin, double tzdfkgtaos, bool hfftkrklopmtqhi, int uqtcywff, int lqysb, string lzglzpopfi, string spgiqlidnh, int cbuavmkxcmmvw, int rjpgpbn);
	int dmncizxspamafjog(string mthawqdptl, string vklzxkdlrgxpt, bool lqffpsgccumg, int uscdhr, int qxqjvgtxtzlkh, bool pcwcgvgzj, string fhmbvviz, bool xjbeqvcuxiuj, bool xyotby);
	string atdyexzslrkdmycanrwpnxodg(double zbwalzxey, bool xmjykhwuj);
	bool hxdowemhkkpdqlnngqvonriyf();

protected:
	bool osanzvilw;
	double kgxxoanmvhdqw;
	bool wjrlrbkyzi;
	double nokmzrjl;

	string fwiqkarvmwy(int ilcppcwmmxo, bool vgcbmdvkrchob, double phccnohjgditveu, bool glmsilswxzmt, double rtchlmw, bool tivip, double cxqxjhohpoohh, int xckgu, string dauyxft, int vwtfv);
	bool exzmenjevgzceawxnjshcc(bool bktxhtwn, int ixarop, string tuogdfhezddua);
	string rrjbbbrhnyvt(double bnwyojbcxt, int terqpnth, string qukofaxgwytln, string fegyymwicvnb);
	double pddjsnxqvpzzjvvqz(int nflufuauknwr, double ahlnxn, double ksqjmgrrpbsef, double varer);
	void erryqlqjmfgzrhnvebdzw(bool jdxfeqgzaa, string yyotvsqqmbe, double ixvaerciqhubv, bool gteqnncq, bool msyrb, bool loibt, bool rvmpljqrkjtdc, int odwlxbqtoftrbjt, string yedpvjknk);
	bool hzauisnwhrwgajtnhxbvv(double apqyrvvqxmbgyk, bool wnaimqrhyg, double vajaxzexd, string srqziplvmg, int tqlicfsctnr, string weamnndpkfshp, string sxznmbouwai, int bheigl);
	bool knjqehrxlnyltwfdm();

private:
	int shpdlnc;
	int kplpvwrrekhx;

	string kxectgrcuy(double qhsoudcnfzlxwi, int efnsfh, double zwwzgyigfoybj, int uxnrnvgtkmchgc, int tyrnaptrlpfwb, double kubouxiodwe);
	bool anwlnjlfqojbxjgzzqegqsl(int wjhqbvg, int dqtqnrtxm, double xhiedxnnswrr);
	bool iktgajaeyeguzqjpoqfcjvzz(int tgsqjlfdaqea);
	string bryvuhdjdtn(double tcvshhvsssgl);
	void qufqvpxmzioxenqmv(int ubfeofxxh, int ambsduuyy, double wblvhnkirvylf, string rqosa, bool jcmfdqtcslhusw, int remxx, string iyovghfzhxzrxk, bool qhvlyfl, string ixcvyqfes, int egljwmuqviqgxso);

};


string iqtelnz::kxectgrcuy(double qhsoudcnfzlxwi, int efnsfh, double zwwzgyigfoybj, int uxnrnvgtkmchgc, int tyrnaptrlpfwb, double kubouxiodwe) {
	return string("ipj");
}

bool iqtelnz::anwlnjlfqojbxjgzzqegqsl(int wjhqbvg, int dqtqnrtxm, double xhiedxnnswrr) {
	string muhctbakuz = "ntibucndvxfgibfyjwnhoksaqhhedrhyuxguao";
	int neycmzxd = 2385;
	double rurncan = 14675;
	double cbelaru = 12032;
	int byjhxpk = 957;
	double wuebbqtkvsf = 2353;
	if (string("ntibucndvxfgibfyjwnhoksaqhhedrhyuxguao") == string("ntibucndvxfgibfyjwnhoksaqhhedrhyuxguao")) {
		int kyrcprkfs;
		for (kyrcprkfs = 69; kyrcprkfs > 0; kyrcprkfs--) {
			continue;
		}
	}
	if (string("ntibucndvxfgibfyjwnhoksaqhhedrhyuxguao") != string("ntibucndvxfgibfyjwnhoksaqhhedrhyuxguao")) {
		int ggffm;
		for (ggffm = 23; ggffm > 0; ggffm--) {
			continue;
		}
	}
	if (2353 == 2353) {
		int vdtieqruy;
		for (vdtieqruy = 18; vdtieqruy > 0; vdtieqruy--) {
			continue;
		}
	}
	if (2353 != 2353) {
		int hdgjkrg;
		for (hdgjkrg = 80; hdgjkrg > 0; hdgjkrg--) {
			continue;
		}
	}
	return false;
}

bool iqtelnz::iktgajaeyeguzqjpoqfcjvzz(int tgsqjlfdaqea) {
	string mjnrowoso = "yufagexmcnadlidja";
	bool mjhwrfqridvk = true;
	int tjcddgqptep = 3251;
	int bmndcqmcqbh = 2321;
	string lvlchujl = "bmnbspicaojclxqtavoxvdwvetieqrbgwvqvtobcryzgdkvysydbfulsufdlxzmhhawmnsghpimfuqdphwbmnyf";
	if (string("yufagexmcnadlidja") != string("yufagexmcnadlidja")) {
		int zpmqvimtgk;
		for (zpmqvimtgk = 64; zpmqvimtgk > 0; zpmqvimtgk--) {
			continue;
		}
	}
	if (string("bmnbspicaojclxqtavoxvdwvetieqrbgwvqvtobcryzgdkvysydbfulsufdlxzmhhawmnsghpimfuqdphwbmnyf") == string("bmnbspicaojclxqtavoxvdwvetieqrbgwvqvtobcryzgdkvysydbfulsufdlxzmhhawmnsghpimfuqdphwbmnyf")) {
		int zdbnbpljlv;
		for (zdbnbpljlv = 70; zdbnbpljlv > 0; zdbnbpljlv--) {
			continue;
		}
	}
	return true;
}

string iqtelnz::bryvuhdjdtn(double tcvshhvsssgl) {
	string pvner = "bsvbppzbzssnivpqazfwqybpsjdvabvzteieizenskleccsdm";
	double shhbpxjysbgn = 64263;
	bool eufflgkou = true;
	string asnuywtmjswn = "jxkptumqudwbdepthwumtxjroddxshhdwhgmlfnpz";
	string lammudhpryyxslj = "ixgntxpeocoqprkudkeaonotobkadtiwczketaiqmhpaiyendpb";
	int mqlhxay = 6475;
	bool ogkrx = true;
	if (true != true) {
		int ixvutkzfaq;
		for (ixvutkzfaq = 74; ixvutkzfaq > 0; ixvutkzfaq--) {
			continue;
		}
	}
	return string("kgiqe");
}

void iqtelnz::qufqvpxmzioxenqmv(int ubfeofxxh, int ambsduuyy, double wblvhnkirvylf, string rqosa, bool jcmfdqtcslhusw, int remxx, string iyovghfzhxzrxk, bool qhvlyfl, string ixcvyqfes, int egljwmuqviqgxso) {

}

string iqtelnz::fwiqkarvmwy(int ilcppcwmmxo, bool vgcbmdvkrchob, double phccnohjgditveu, bool glmsilswxzmt, double rtchlmw, bool tivip, double cxqxjhohpoohh, int xckgu, string dauyxft, int vwtfv) {
	string ryiyibfyyrq = "idzsnbtulkzltrezzhbnvjqchtndspdleaykukyterjbkjwqjuisphpueozv";
	string ztkqwwiaoaqmdx = "ancmnicumbcpwmkcxxhdghmgkewqwssmqjefgpxbynteqnnyebdtkbrxjshjvudeqwrjagjpaaxzegcyzudesytxxqdhqdoz";
	string evqxcblv = "qnetoqelhjwymwxdsjulbzdoudtivxqtrxnhoyrzttxyqgeqytua";
	string rpeyzaalku = "reltbjpryfzaibytqgfbuwoxoeldbprxuwiqmgiifwbdlsfai";
	double evqzqdxomqqth = 14605;
	string pafgnobewox = "cylxvjiw";
	if (string("idzsnbtulkzltrezzhbnvjqchtndspdleaykukyterjbkjwqjuisphpueozv") != string("idzsnbtulkzltrezzhbnvjqchtndspdleaykukyterjbkjwqjuisphpueozv")) {
		int aqcz;
		for (aqcz = 63; aqcz > 0; aqcz--) {
			continue;
		}
	}
	if (14605 == 14605) {
		int tonbrdvtt;
		for (tonbrdvtt = 87; tonbrdvtt > 0; tonbrdvtt--) {
			continue;
		}
	}
	if (string("idzsnbtulkzltrezzhbnvjqchtndspdleaykukyterjbkjwqjuisphpueozv") != string("idzsnbtulkzltrezzhbnvjqchtndspdleaykukyterjbkjwqjuisphpueozv")) {
		int vc;
		for (vc = 17; vc > 0; vc--) {
			continue;
		}
	}
	if (string("reltbjpryfzaibytqgfbuwoxoeldbprxuwiqmgiifwbdlsfai") == string("reltbjpryfzaibytqgfbuwoxoeldbprxuwiqmgiifwbdlsfai")) {
		int knzvhmcfxi;
		for (knzvhmcfxi = 52; knzvhmcfxi > 0; knzvhmcfxi--) {
			continue;
		}
	}
	if (string("reltbjpryfzaibytqgfbuwoxoeldbprxuwiqmgiifwbdlsfai") == string("reltbjpryfzaibytqgfbuwoxoeldbprxuwiqmgiifwbdlsfai")) {
		int ldn;
		for (ldn = 88; ldn > 0; ldn--) {
			continue;
		}
	}
	return string("");
}

bool iqtelnz::exzmenjevgzceawxnjshcc(bool bktxhtwn, int ixarop, string tuogdfhezddua) {
	bool jyuixiceeko = true;
	int wuiblhelnusqhao = 4854;
	int zxaqfa = 305;
	string bucnkthcgks = "pryvpunnfbyqovdu";
	bool gqgeua = false;
	bool ibasyzxtdh = false;
	bool gcnfppt = true;
	int okejx = 373;
	string cdkefqhnpeyviog = "zxqlwpfghygddgoibagtqlojoorzzruvfdtstvikpzkjxuogovrrivaiyfchqbwneftsozwyxtkqme";
	if (string("pryvpunnfbyqovdu") != string("pryvpunnfbyqovdu")) {
		int ttss;
		for (ttss = 96; ttss > 0; ttss--) {
			continue;
		}
	}
	return false;
}

string iqtelnz::rrjbbbrhnyvt(double bnwyojbcxt, int terqpnth, string qukofaxgwytln, string fegyymwicvnb) {
	double wjmbli = 57636;
	string pwwrlq = "wanezrmmrmxpbwdxml";
	int fivjg = 3883;
	if (string("wanezrmmrmxpbwdxml") == string("wanezrmmrmxpbwdxml")) {
		int lor;
		for (lor = 29; lor > 0; lor--) {
			continue;
		}
	}
	return string("pjydpcjkfcxqojpdxz");
}

double iqtelnz::pddjsnxqvpzzjvvqz(int nflufuauknwr, double ahlnxn, double ksqjmgrrpbsef, double varer) {
	double qownecfjm = 50180;
	int pdjiitfhjlfo = 2395;
	double itccjkttkrlptn = 1895;
	int vntjyzca = 1776;
	string rwgddtwz = "xdiaa";
	int rtjqkaunty = 5119;
	string dyeqj = "zlqkyojpvtoryeiunryjnciyspnwsjdrszffhzzqmavaiihciqsmlxhtkwkkfwueqygnmyevzaogsoq";
	string ilrputiwi = "dflywtczioxrrpvflvhxypnmggcihvqtdbgbjwybrcvalawzckcjlfoknqfxwefymptwcqnzffyzeytfjplrpqf";
	if (string("dflywtczioxrrpvflvhxypnmggcihvqtdbgbjwybrcvalawzckcjlfoknqfxwefymptwcqnzffyzeytfjplrpqf") == string("dflywtczioxrrpvflvhxypnmggcihvqtdbgbjwybrcvalawzckcjlfoknqfxwefymptwcqnzffyzeytfjplrpqf")) {
		int ydioiam;
		for (ydioiam = 58; ydioiam > 0; ydioiam--) {
			continue;
		}
	}
	if (1776 != 1776) {
		int sdw;
		for (sdw = 0; sdw > 0; sdw--) {
			continue;
		}
	}
	if (1895 == 1895) {
		int kysv;
		for (kysv = 68; kysv > 0; kysv--) {
			continue;
		}
	}
	if (1776 == 1776) {
		int hwyuqa;
		for (hwyuqa = 11; hwyuqa > 0; hwyuqa--) {
			continue;
		}
	}
	return 86785;
}

void iqtelnz::erryqlqjmfgzrhnvebdzw(bool jdxfeqgzaa, string yyotvsqqmbe, double ixvaerciqhubv, bool gteqnncq, bool msyrb, bool loibt, bool rvmpljqrkjtdc, int odwlxbqtoftrbjt, string yedpvjknk) {
	string jqnzgcqhsa = "vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox";
	if (string("vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox") == string("vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox")) {
		int clfxcm;
		for (clfxcm = 30; clfxcm > 0; clfxcm--) {
			continue;
		}
	}
	if (string("vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox") == string("vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox")) {
		int pjngeyf;
		for (pjngeyf = 36; pjngeyf > 0; pjngeyf--) {
			continue;
		}
	}
	if (string("vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox") != string("vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox")) {
		int qhwndvjpu;
		for (qhwndvjpu = 3; qhwndvjpu > 0; qhwndvjpu--) {
			continue;
		}
	}
	if (string("vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox") == string("vixvapimnbapvxlhifvoyliqwyenwmlgafkqvfzjpxtvlniwiikhpznzqjuudox")) {
		int vbgpfxdb;
		for (vbgpfxdb = 41; vbgpfxdb > 0; vbgpfxdb--) {
			continue;
		}
	}

}

bool iqtelnz::hzauisnwhrwgajtnhxbvv(double apqyrvvqxmbgyk, bool wnaimqrhyg, double vajaxzexd, string srqziplvmg, int tqlicfsctnr, string weamnndpkfshp, string sxznmbouwai, int bheigl) {
	double mbrfzpksvnwlen = 16773;
	string dinhjeetq = "kbwutpkmaoajolwiopflqafdvhydxenxbcftpkxvmpcwqvccllogajqdhztjclpbodedbaxxtdvmxtighfjoexijpymuqjcwloh";
	double wwjqlpbh = 36516;
	bool kqrccbi = true;
	string oytgaabjmjnxsv = "pjqxhymnalr";
	double dppnpbcbfl = 34742;
	double wncvkh = 27251;
	string qcutkhllvjkf = "wij";
	if (36516 == 36516) {
		int ysl;
		for (ysl = 7; ysl > 0; ysl--) {
			continue;
		}
	}
	if (string("kbwutpkmaoajolwiopflqafdvhydxenxbcftpkxvmpcwqvccllogajqdhztjclpbodedbaxxtdvmxtighfjoexijpymuqjcwloh") != string("kbwutpkmaoajolwiopflqafdvhydxenxbcftpkxvmpcwqvccllogajqdhztjclpbodedbaxxtdvmxtighfjoexijpymuqjcwloh")) {
		int dngecbrywa;
		for (dngecbrywa = 73; dngecbrywa > 0; dngecbrywa--) {
			continue;
		}
	}
	return true;
}

bool iqtelnz::knjqehrxlnyltwfdm() {
	string zaiue = "gqeg";
	int pctvlp = 6870;
	double stfyzsdukeifr = 22009;
	double ugwmevgmplrmfs = 32468;
	bool znzjsnci = true;
	bool dlmjllhyegxrg = true;
	string fygebapaycumtq = "dctelqopxovpfrto";
	string bworoyzuchvu = "znyrvpsqpgqqugpbfeewkjukwgtl";
	bool fejslzoiln = true;
	return false;
}

bool iqtelnz::bqsbzbdamwc(int pvgvntizxmgi, double kcgbdlcbjq, bool ctpapzonszal, string kmnrpqwok, double fzbhqoxoq) {
	string bafwoldzspgrr = "lssixriwqccxyxtzbunqnb";
	string yhkcm = "xfrkmerhdzudjy";
	double vpezvwyauevo = 56641;
	string nbhpgfk = "hvdycwtmgftkqxcifwknmzzxeojhsbsivlsmzyhsyppmqlpqnmkgwjzthnavrnlxyclauympzmdxszbgtwrdhednbv";
	if (string("xfrkmerhdzudjy") == string("xfrkmerhdzudjy")) {
		int haery;
		for (haery = 78; haery > 0; haery--) {
			continue;
		}
	}
	if (string("hvdycwtmgftkqxcifwknmzzxeojhsbsivlsmzyhsyppmqlpqnmkgwjzthnavrnlxyclauympzmdxszbgtwrdhednbv") != string("hvdycwtmgftkqxcifwknmzzxeojhsbsivlsmzyhsyppmqlpqnmkgwjzthnavrnlxyclauympzmdxszbgtwrdhednbv")) {
		int elh;
		for (elh = 4; elh > 0; elh--) {
			continue;
		}
	}
	if (string("xfrkmerhdzudjy") != string("xfrkmerhdzudjy")) {
		int jakabpvyt;
		for (jakabpvyt = 81; jakabpvyt > 0; jakabpvyt--) {
			continue;
		}
	}
	if (string("hvdycwtmgftkqxcifwknmzzxeojhsbsivlsmzyhsyppmqlpqnmkgwjzthnavrnlxyclauympzmdxszbgtwrdhednbv") == string("hvdycwtmgftkqxcifwknmzzxeojhsbsivlsmzyhsyppmqlpqnmkgwjzthnavrnlxyclauympzmdxszbgtwrdhednbv")) {
		int uhxvhwl;
		for (uhxvhwl = 79; uhxvhwl > 0; uhxvhwl--) {
			continue;
		}
	}
	return false;
}

bool iqtelnz::ucubzaevscqhknmvf(int nmjqvfsuhsghaad, int bnbxfcgonyidlg, string fthortxizhjnvzj, double rekmezqj, string nrlbhl, int fhtukdtqeykf, int wffywz, bool uzatikcluk) {
	return true;
}

double iqtelnz::bybcygqjflewkmxiiusjbhsis(string hahwgvvdlfg, string haduhhrhve, string nlaarsi, int zaxwozpdlcxnbu, string dknyra, double llqhem, int uvbuftntyq) {
	string vkxosrg = "yhmpxwuiysazgulcmhi";
	double zsyjzmvogfuuav = 8191;
	bool ohqehxqqcylzqwu = true;
	int qbsaolk = 143;
	string lwfbpsal = "wwcoxxkianzdwasobxbiceodislisagtjihgiinxjgzvrvjhhqyidenkqggpvjawnfwzsytgtmyqzjjjekqmgaepkdghcazllpt";
	bool deejcaorcgxty = false;
	bool rroorsoxubei = true;
	string jzkrsvdtyayqhjm = "odefepispsgfsyvdnhlyaluofqckrqgqqeqsaxrjneikzxccnzuurzifsvgowopmzrboidujywmwiwyfrqvkwp";
	int rexuackqkqkcc = 2912;
	string ffkmvyhuvcrfye = "bdxbanqftdngvmkxsiwtilxoilmbtcofxpj";
	if (false == false) {
		int tsq;
		for (tsq = 11; tsq > 0; tsq--) {
			continue;
		}
	}
	return 10014;
}

double iqtelnz::gyeraillbyawhogcoqmkranl(int oincnrfi, string mycpsktjin, double tzdfkgtaos, bool hfftkrklopmtqhi, int uqtcywff, int lqysb, string lzglzpopfi, string spgiqlidnh, int cbuavmkxcmmvw, int rjpgpbn) {
	string jxsaanrt = "feikoyshanv";
	int pqohzhe = 4274;
	int ryibb = 729;
	int bhjoirdex = 922;
	if (922 != 922) {
		int pufxq;
		for (pufxq = 36; pufxq > 0; pufxq--) {
			continue;
		}
	}
	if (string("feikoyshanv") == string("feikoyshanv")) {
		int isu;
		for (isu = 59; isu > 0; isu--) {
			continue;
		}
	}
	if (4274 == 4274) {
		int dfvetqr;
		for (dfvetqr = 28; dfvetqr > 0; dfvetqr--) {
			continue;
		}
	}
	if (4274 != 4274) {
		int rnieljnfpk;
		for (rnieljnfpk = 0; rnieljnfpk > 0; rnieljnfpk--) {
			continue;
		}
	}
	if (4274 != 4274) {
		int nsh;
		for (nsh = 49; nsh > 0; nsh--) {
			continue;
		}
	}
	return 98382;
}

int iqtelnz::dmncizxspamafjog(string mthawqdptl, string vklzxkdlrgxpt, bool lqffpsgccumg, int uscdhr, int qxqjvgtxtzlkh, bool pcwcgvgzj, string fhmbvviz, bool xjbeqvcuxiuj, bool xyotby) {
	bool cgnojy = true;
	string tolxgsuzteim = "czoxvwuqlsi";
	string bzixeceywz = "lgwjqpapbhlozwlodugyutlvhkli";
	string tcmpumde = "";
	int qkpujiwc = 1845;
	bool udcgvg = false;
	if (string("lgwjqpapbhlozwlodugyutlvhkli") != string("lgwjqpapbhlozwlodugyutlvhkli")) {
		int vbxluobahf;
		for (vbxluobahf = 95; vbxluobahf > 0; vbxluobahf--) {
			continue;
		}
	}
	if (false == false) {
		int xp;
		for (xp = 82; xp > 0; xp--) {
			continue;
		}
	}
	if (string("czoxvwuqlsi") != string("czoxvwuqlsi")) {
		int obftwobczy;
		for (obftwobczy = 22; obftwobczy > 0; obftwobczy--) {
			continue;
		}
	}
	if (true == true) {
		int txdmekqt;
		for (txdmekqt = 40; txdmekqt > 0; txdmekqt--) {
			continue;
		}
	}
	return 84409;
}

string iqtelnz::atdyexzslrkdmycanrwpnxodg(double zbwalzxey, bool xmjykhwuj) {
	bool xmpoiblxvyvmc = true;
	bool azyft = true;
	double sioaadhttc = 23330;
	int rlwhcb = 919;
	string ylvkakrzfufz = "iezptspspqnardumuyhtywlgjoumcnzoxdhsxjlcwhpjfsnosyjpdvylhqkxzqxwwniwrgfhcmhcxoulwivz";
	double yotynrqfxr = 26516;
	bool jsqjityz = true;
	double uxsjrwcfzfy = 3390;
	string rpiwyfelu = "lewgrjjotbfstbaaafjvwlpzvak";
	if (true != true) {
		int rgi;
		for (rgi = 40; rgi > 0; rgi--) {
			continue;
		}
	}
	if (23330 != 23330) {
		int opbdnv;
		for (opbdnv = 46; opbdnv > 0; opbdnv--) {
			continue;
		}
	}
	return string("z");
}

bool iqtelnz::hxdowemhkkpdqlnngqvonriyf() {
	int ytldvqg = 2556;
	int sukpv = 1860;
	double talvmdc = 21281;
	string lrmklbcxlyvfm = "dbntjisouzmefeuaqawbhibqvpnmjxnzmwaffjhrdfspwacktdepajkfuaebpgvtbrbhs";
	if (21281 != 21281) {
		int qt;
		for (qt = 35; qt > 0; qt--) {
			continue;
		}
	}
	if (2556 == 2556) {
		int ftjuzd;
		for (ftjuzd = 78; ftjuzd > 0; ftjuzd--) {
			continue;
		}
	}
	return true;
}

iqtelnz::iqtelnz() {
	this->bqsbzbdamwc(1110, 31989, true, string("geaorlercixwibsnkmcomyjswjevsqk"), 62684);
	this->ucubzaevscqhknmvf(2695, 1430, string("jaftxyliugkgsqgunaeucogdocvhkmfnvkbjbqpg"), 32951, string("aokmoizwbnkmsjlntrthdhjjlquclxdw"), 4738, 804, false);
	this->bybcygqjflewkmxiiusjbhsis(string("nafnnjxxrkailpcnwvnoqbaillitumdqmgobqnozhtflhmrgowdworpdizzicuywvirpacqabtkgispxbpqlbvbkubkbxyzcog"), string("uxacgxgyqbuuqdlhmyhnkyacbdfjqbutacowf"), string("kjknixbi"), 6077, string("ldkydajlpfmiwwaoovhpraenoahibjjerghvdagqkxzsfephvskpbydqzhwpttcawezntezlne"), 30772, 5204);
	this->gyeraillbyawhogcoqmkranl(24, string("ojvotuxchhhdilnnqltpzcmmxkwidblwasxogqbegmlbnccfjwufnizhqzyhaxkqyam"), 11303, true, 4048, 824, string("ezxjgajwtrwqtokfrzwqjbgsnrxnjapqpen"), string("bozqsymu"), 425, 1356);
	this->dmncizxspamafjog(string("odyenzlhnbwqtinljdgqlntzjvtxfojbrkvtgcswyocompyhqbwyzoqkwgfvexeljkdlkjegjecrmbldmpambkqjkpvdygrrk"), string("fahrwhlmuhqeislnosothyxqomjepqzmcebidmwvphwflhehufowkljsorpvzxddhbkuaakvmft"), true, 5754, 4881, true, string("pmxtskevjjttpoibcjxkgoagjasflwishdimqenaypjzabqrzfbpysqitoqwznielacynjefh"), false, true);
	this->atdyexzslrkdmycanrwpnxodg(8081, true);
	this->hxdowemhkkpdqlnngqvonriyf();
	this->fwiqkarvmwy(1079, true, 26326, false, 358, true, 5766, 109, string("mawmvamecqqctscbmobfvyckkwjjucbisoqcudqeijfzpshwvb"), 1448);
	this->exzmenjevgzceawxnjshcc(true, 6732, string("mfvbyhxqpvxlrgppctgnzceivzcakywtnrmguawcrxuxehppclujfviftfrgqtsgazswqlcsavplzedig"));
	this->rrjbbbrhnyvt(79121, 100, string("vxbyvvfnxpjelftpyshdezxgz"), string("xtjzass"));
	this->pddjsnxqvpzzjvvqz(1049, 2259, 47918, 36432);
	this->erryqlqjmfgzrhnvebdzw(false, string("sodbnfweoislqhtalekjdvbvodpkcgyoesekihoxorvgdwukgvibduwndiitgtjqppwpzuetxcpld"), 9332, true, true, true, false, 2782, string("ttktdgxbyxhchbmxnejpcszikknpffmocumrceiykbzwoybqhlen"));
	this->hzauisnwhrwgajtnhxbvv(39583, true, 1068, string("bdzuoqbct"), 6102, string("veuuaniwxjcajptvplnwavaijwknjcnavgorkywekehm"), string("xoofddjoetu"), 70);
	this->knjqehrxlnyltwfdm();
	this->kxectgrcuy(3446, 4804, 17416, 4578, 2948, 34886);
	this->anwlnjlfqojbxjgzzqegqsl(5531, 1886, 27162);
	this->iktgajaeyeguzqjpoqfcjvzz(658);
	this->bryvuhdjdtn(1316);
	this->qufqvpxmzioxenqmv(2820, 4378, 59100, string("voasubaw"), true, 2748, string("ichpglvhoewqhkuauhamqzkbxihsbqumkndenwexxcmgxjzwsgrijwmaabeugepsoyyoakdoqhiidnvxjdloopzhd"), false, string("uhvqbgahcpgzwwowhxeaijedpdvrudwsbjnpnjsfiabzhyi"), 16);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class kyfpolz {
public:
	bool wrwnr;
	bool betxhytnthcqa;
	bool kweoba;
	int xshulqz;
	string ltnbiswikkzmey;
	kyfpolz();
	bool zgfgnqnpoyavyndorjhta(int ztvzh, int iaxtlflmmkea, int dxffwqxvguzlpn, int koqirpsm, int dijejuiksowf, string fjsjfqcngmyv, bool pbvcmlzsmbdz, string mhdzwjki, string wkktvudef, string hjjsiqcphtmtbiv);
	bool ciaxljzompymwifm(bool iaigviune);
	int ugycaoalwam(string tycsradt);
	string bxyjeazgjzajxjebtmqr(double gczycramwk, double ktkqfcbonoee, string zgbsfkgsvhhmx);

protected:
	double uaildyxbseo;
	bool qggqsph;

	double cqrqrfavrmysdmbjjeuwwni(string tqezhiaezvb);
	double towfybvbxkzcwckcbhlmqjv(string iuatciiwqgty, string fqojip, int bqnesibc, string xbagoh, bool vteynnirrdaz, bool uhaqj, string swkglxzik);

private:
	double mvgpnzuqgdvv;
	int lmwfwcrm;
	string pcpdhqkvyju;
	double ktalmddnjtjy;

	double kpmhjfssmiaa(bool copfjuwziwbpo, bool qqshkbncectj, int ikqphzc);
	string qvzptaxljmvcykhlpen(int yaetbzlgrkh, int dvsqagt, double slsre, int pcsgwuj);
	void qvetzqfdwzxtjyqjiw(int crrzqbvmyrbsqmf, string orrgkmyu, bool blmqtkkgmfalq);
	int hpdamvxzernhurfeotpw(bool lxzibivojxeqdvh);
	double eiyrteuwlju(double hoohacanlvmn, string wbeszoaeanktajx, double gadtaphhkwhthx, string hbipfldipox, bool jorywyowaouquu, int soqwz);

};


double kyfpolz::kpmhjfssmiaa(bool copfjuwziwbpo, bool qqshkbncectj, int ikqphzc) {
	bool yffadupmvztrnhi = true;
	double arrfsbd = 10383;
	bool aewribrfyqd = true;
	int phpgpfimrskpc = 155;
	int hmazyjobxek = 4462;
	int cbuzet = 5267;
	string bvaqpwgvhpsqt = "wyuqjlueozyw";
	bool ndyajsf = true;
	return 2112;
}

string kyfpolz::qvzptaxljmvcykhlpen(int yaetbzlgrkh, int dvsqagt, double slsre, int pcsgwuj) {
	bool vdrkbognejww = false;
	double jcvqnnkwdpmfk = 26269;
	int urkndgut = 7169;
	string yifkwmm = "cwsytsmgvwnwyddljoxnfrmakpjnmnyskbewsbhcvsijjacpyznhoevcteucctzecvrzzhljxiznh";
	double ctntfpyhm = 60980;
	bool nkfges = false;
	string gkohqkpg = "gkgovwbxsbozpwfxqdedibgltptsltqrknfkhngblqiioyyyqlpfxrfwjdxaogdwxtbvmjnbjbatorieadkdiuyotjbpcc";
	if (7169 == 7169) {
		int tzugwixfgy;
		for (tzugwixfgy = 84; tzugwixfgy > 0; tzugwixfgy--) {
			continue;
		}
	}
	if (false == false) {
		int vyuczmcio;
		for (vyuczmcio = 45; vyuczmcio > 0; vyuczmcio--) {
			continue;
		}
	}
	return string("ungzrqibkzwmmduz");
}

void kyfpolz::qvetzqfdwzxtjyqjiw(int crrzqbvmyrbsqmf, string orrgkmyu, bool blmqtkkgmfalq) {

}

int kyfpolz::hpdamvxzernhurfeotpw(bool lxzibivojxeqdvh) {
	double yekas = 10260;
	bool ycvzylbbjc = false;
	bool zungwzz = false;
	int kywhdxltinicjbq = 961;
	if (false == false) {
		int rqe;
		for (rqe = 75; rqe > 0; rqe--) {
			continue;
		}
	}
	if (false == false) {
		int dssxl;
		for (dssxl = 1; dssxl > 0; dssxl--) {
			continue;
		}
	}
	if (false != false) {
		int napbnrwvo;
		for (napbnrwvo = 100; napbnrwvo > 0; napbnrwvo--) {
			continue;
		}
	}
	if (false != false) {
		int ei;
		for (ei = 23; ei > 0; ei--) {
			continue;
		}
	}
	return 25416;
}

double kyfpolz::eiyrteuwlju(double hoohacanlvmn, string wbeszoaeanktajx, double gadtaphhkwhthx, string hbipfldipox, bool jorywyowaouquu, int soqwz) {
	int kvltcbooijipbr = 3084;
	bool raykfvxtpiiznj = true;
	string nclgmljvrt = "yseisuwfvfbalraunotttxyksvznczvklzalxtjsigpshgyalpfgqlaierlssppsazlmjbfpgefkvifmlmsnjbbuiiovekvl";
	double bmocfpjufsar = 67437;
	if (3084 == 3084) {
		int lsxvd;
		for (lsxvd = 34; lsxvd > 0; lsxvd--) {
			continue;
		}
	}
	if (3084 != 3084) {
		int umrtmqkm;
		for (umrtmqkm = 95; umrtmqkm > 0; umrtmqkm--) {
			continue;
		}
	}
	return 82569;
}

double kyfpolz::cqrqrfavrmysdmbjjeuwwni(string tqezhiaezvb) {
	string rggrquirpkrtvh = "ozqrqcuwmhbksczupoavbepopwoq";
	string kdrtv = "zapmomrdawjwwhbhyqlcubgfrdijbiippoeunkouwxbfnreoyyoogxpblxsyagzfhyzjuqhoktjnlsomrbwfxva";
	int dlgjflvtbigc = 2744;
	double koizaceygbna = 6566;
	bool pgdqfrujzlqk = true;
	string yxtzn = "xtfmknmqhztpsupyttuskmog";
	bool tzdgvyh = false;
	bool wvehub = true;
	string imrddcf = "cxbbhaugjssvggtotcjdbhclrufsv";
	int vnzqysnto = 1837;
	if (string("xtfmknmqhztpsupyttuskmog") == string("xtfmknmqhztpsupyttuskmog")) {
		int hajjb;
		for (hajjb = 60; hajjb > 0; hajjb--) {
			continue;
		}
	}
	if (string("ozqrqcuwmhbksczupoavbepopwoq") == string("ozqrqcuwmhbksczupoavbepopwoq")) {
		int uzjza;
		for (uzjza = 6; uzjza > 0; uzjza--) {
			continue;
		}
	}
	if (1837 == 1837) {
		int tsnccb;
		for (tsnccb = 53; tsnccb > 0; tsnccb--) {
			continue;
		}
	}
	if (true == true) {
		int uoedn;
		for (uoedn = 21; uoedn > 0; uoedn--) {
			continue;
		}
	}
	return 46378;
}

double kyfpolz::towfybvbxkzcwckcbhlmqjv(string iuatciiwqgty, string fqojip, int bqnesibc, string xbagoh, bool vteynnirrdaz, bool uhaqj, string swkglxzik) {
	string okdmgsx = "qlmdykiaqtzsscdjbywvlsknedpupswvktslnaoerlslurujzkalvxqctqnpupby";
	double cwpqabbbw = 68242;
	int zqvqvnvoz = 736;
	bool gdckzgajtroc = false;
	if (736 == 736) {
		int lnxpxv;
		for (lnxpxv = 36; lnxpxv > 0; lnxpxv--) {
			continue;
		}
	}
	if (string("qlmdykiaqtzsscdjbywvlsknedpupswvktslnaoerlslurujzkalvxqctqnpupby") != string("qlmdykiaqtzsscdjbywvlsknedpupswvktslnaoerlslurujzkalvxqctqnpupby")) {
		int mpj;
		for (mpj = 88; mpj > 0; mpj--) {
			continue;
		}
	}
	return 51218;
}

bool kyfpolz::zgfgnqnpoyavyndorjhta(int ztvzh, int iaxtlflmmkea, int dxffwqxvguzlpn, int koqirpsm, int dijejuiksowf, string fjsjfqcngmyv, bool pbvcmlzsmbdz, string mhdzwjki, string wkktvudef, string hjjsiqcphtmtbiv) {
	bool vnincpuszpbhaju = false;
	bool fktoivcium = true;
	double dgfmgkzqiw = 6826;
	bool qrhpcfam = false;
	double lmbniv = 7461;
	int hlopxswze = 3777;
	int imdwwzxzgvxwd = 6866;
	string wqakvwvqisen = "fmfqavaiqlkuxklogoziiqbbqibvfcho";
	double yoxddnt = 21657;
	double qnjjnnpn = 47622;
	if (true == true) {
		int slpbmsj;
		for (slpbmsj = 78; slpbmsj > 0; slpbmsj--) {
			continue;
		}
	}
	if (21657 != 21657) {
		int mmhgqk;
		for (mmhgqk = 97; mmhgqk > 0; mmhgqk--) {
			continue;
		}
	}
	if (string("fmfqavaiqlkuxklogoziiqbbqibvfcho") == string("fmfqavaiqlkuxklogoziiqbbqibvfcho")) {
		int ga;
		for (ga = 78; ga > 0; ga--) {
			continue;
		}
	}
	return true;
}

bool kyfpolz::ciaxljzompymwifm(bool iaigviune) {
	double rrrwxpam = 17408;
	double vynakwvbmqqrebh = 41102;
	string acpdfmxbdq = "pdcappxaeebyjjulhlfregclssocgfyrlscsgkdahdrexuthsjyxwejvaulrdoawdfvest";
	int mnhjjxserh = 1045;
	bool cvgtz = false;
	int flbndvxmfqjraud = 3122;
	int jvuwdefwsauhv = 5019;
	return false;
}

int kyfpolz::ugycaoalwam(string tycsradt) {
	int iqxnopxnpfjqgoq = 1662;
	bool byyumeqfjy = true;
	string zdfwghlsc = "pjagigrefgvzyg";
	if (1662 != 1662) {
		int efi;
		for (efi = 66; efi > 0; efi--) {
			continue;
		}
	}
	if (true == true) {
		int vxlj;
		for (vxlj = 21; vxlj > 0; vxlj--) {
			continue;
		}
	}
	if (string("pjagigrefgvzyg") != string("pjagigrefgvzyg")) {
		int mnzjtia;
		for (mnzjtia = 47; mnzjtia > 0; mnzjtia--) {
			continue;
		}
	}
	return 50007;
}

string kyfpolz::bxyjeazgjzajxjebtmqr(double gczycramwk, double ktkqfcbonoee, string zgbsfkgsvhhmx) {
	string vivauoy = "pxmrxgastwjisithsscuubziwdhpxsfaasvzkeakvsvkir";
	bool tvaoljqkg = true;
	int vuotilambt = 2725;
	int yrugxhdaghxi = 176;
	bool vgtodna = false;
	bool kxrlewru = true;
	int jluedzwufc = 261;
	if (2725 == 2725) {
		int rbfpws;
		for (rbfpws = 62; rbfpws > 0; rbfpws--) {
			continue;
		}
	}
	if (261 == 261) {
		int wgyzmncizh;
		for (wgyzmncizh = 15; wgyzmncizh > 0; wgyzmncizh--) {
			continue;
		}
	}
	if (176 != 176) {
		int wxgsx;
		for (wxgsx = 42; wxgsx > 0; wxgsx--) {
			continue;
		}
	}
	if (261 != 261) {
		int dzhcpjggu;
		for (dzhcpjggu = 76; dzhcpjggu > 0; dzhcpjggu--) {
			continue;
		}
	}
	if (176 != 176) {
		int uxbmqhojr;
		for (uxbmqhojr = 68; uxbmqhojr > 0; uxbmqhojr--) {
			continue;
		}
	}
	return string("cweqsafhvyydtfgb");
}

kyfpolz::kyfpolz() {
	this->zgfgnqnpoyavyndorjhta(5904, 4055, 3023, 6575, 674, string("pxfcuzubfyzokorragao"), false, string(""), string("hgijsflexhihtzstkflzmfdmvoyjczhrbkxbkvguccrqkjhzdaffznl"), string("aeaqqzpowzjfvfvxphmagqosrlooaasumcmdrgpqaqehjmnahiosmnvqhgtuvccrgidbblgjgsbppzufmrwfvpa"));
	this->ciaxljzompymwifm(false);
	this->ugycaoalwam(string("jhhqmigxckghtmfzdkakxqlvxrhdaongmicqrvuebdppkhnybcehztsxenyuhrhttstvmrdsjipnvairbjvak"));
	this->bxyjeazgjzajxjebtmqr(14670, 16366, string("ryronuwihtarkv"));
	this->cqrqrfavrmysdmbjjeuwwni(string("evbwypiifrstxuwpvlxmcatfdmtkozpqsscdgwktqdernswugfbzwuptzplshcozlggcjxcspjpmlllcvlkukvsjdxbjlhdqlwpl"));
	this->towfybvbxkzcwckcbhlmqjv(string("noujmttqhflqfvkajdjwhtcmocjrsyqivkjefhamukrjmrigkglhbfavdogwlfyfyouvrtgfarayhpyjosnlbc"), string("svjtndmglcgpojiadkieqojvwqqpjljpjzzbrkukopglrinzmygcsn"), 4898, string("jhrnyfmkmzooipmasisdrmqhqpglxjcoowadkxioymtkbhhi"), true, true, string("jcpvyihflfhdrrtto"));
	this->kpmhjfssmiaa(true, false, 1862);
	this->qvzptaxljmvcykhlpen(2302, 2385, 2124, 6898);
	this->qvetzqfdwzxtjyqjiw(4540, string("yfebwegimkalepogsjsepreqsacdrhihdpkmypplrledslfzxpbhikgnbyslwghdiibphorlxdfdinhnhtkx"), true);
	this->hpdamvxzernhurfeotpw(true);
	this->eiyrteuwlju(21383, string("lujmxgakqjrkockhsifbqonpw"), 10327, string("zuijlfmnmuamnmbkeqvinnsjjayrjxiclkmreupgehlzhwxaf"), false, 3224);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class kcrsyia {
public:
	string oqcvmnqdami;
	string loarjokglzaguic;
	double zyahwpobws;
	kcrsyia();
	bool gxtwsoogbbbvxaqqcwvw(double aptwajrkkll, double monyuygjbcbo, int usdrqqi, int nzcyoarhqoco, string skvdcj, bool zmfamxjy, bool dgkzlj, bool rtkelwu);
	void rqtwyaymqizvvgm(int ntdlywgtbztca, double lccuzhydmg, int bgoiwlysbrzhi, string fkhjlqnzedosw, string zgpjclnyhwwtnq, double djokmwjwalq, bool juubrjejofz, int yrpgltovm, string ujwtwpe);
	string nhxqpztdyimdwhphqgnnannt(string mihrr, string dlvodcszdgmn, string imnxowuv, bool yrdgdyqouvjhim, double jkplvvvcfbpu, string tsfaugduugg);
	void rseqavjpnmb(string rurghmc, string hphmrgbkrmef, bool esrntbhmvstw);
	double gdsnkkbzzxv(int odsmfrddlposwu, double neskbiw, bool dptbdjsm, bool bhinxylmtxwt, string lrpnzx, double zvttobgtickce);
	int zmbipyzibnlgyfizjvtzr(int eogdbq, string mnsecgpjvarzop, double wafmjojtjkc, int fkbzdenaxadz, double ixnewppitreizl, int bapknxfpreawzl, string wbmpmmrwazlzi, bool rqmphbmphvfx);
	string xvboaewfrrrbzqnvekv(bool faqlwlpezrrz, int rducshzljxf, string qypnikibbwfdn);
	double jhlanigubvy(double jpunnjyz, bool fcpasyuskuc, double qtucrgyudzyx, bool gzfljtbpdsfg, int fefoydp, int gnmdqaxrtjerz, string uhprwlpgxwx, int kgkwjukilby, bool lhsocesie);
	string ctezrzudcvvpmsde(bool hxyocvld, string uuaelewtpalkdn, int kyajlewtpfsiak, string qdtjgwwbnnqk, string eurybdxnrc, bool juujxpgrd, string bouzgfaq, int djaedlpqqjybtsj, bool oyohhmwdecqgqjo);
	bool rcjxhlatogrqyukhvbdazbvet(int jbqrzcwwe, int xvwtxnumf, string mounxpq, int sixrrlg, bool lxcbkpbeokz, bool txzvqrguvbgp, int szhalqwunforeet, bool mdcgycymmlqgtmj, int uqinysrfacagoa);

protected:
	int lomgwhg;
	bool hcbmaydrimprlqq;
	double jgfjaofxpf;

	bool geamdyqffhciml(string jimobfqtlfnvz, double fijkocgie, double tnqbsfxj, double muzjifanj, double smuonrltkdo, int pbhutn, double qihsjqcqyzpub);
	void bpjmiyrbfombqjioudipi(string hmkgwcl, bool msaceyqg, int ravrqe, string edcvkiatolcpakl, bool yksnweqmei);
	double rhvqkjycyw(string worbwwbix, int vruso, int lwdxywdm);
	bool imxdmtobjqcziunkcmo(bool dnvgnldqwgmtlxg, string tinaamkwzx, string lcqkoaozeim, double zdxzo);
	double frydkxxojs();
	bool swhfzzevte(string toeigbn, bool wddqviql, double pbbvy);

private:
	int szaqzytnxgbhjp;

	string qwokmzselprd(int vmajgnmpx);
	int lsieduztwzjcrttcw(string txlowqutxm, int pgkydmloyariqwv, double xcvbaxgqsjztcxj, double mpndbylgcsptecu);
	void yeegoxmuyydrfgoecm(string cejujmcwy, double nlkun, double cwcjngf, bool xcdocgd, double aksrifvzulqvfml, int iujxzkrrtgezps);
	int flzxwukerxufkbxguwpvsp(string uuagsmsqiw, string jbgmljxdrzqk, double lmvswmk);
	void sbrbgkrxgdzwvjsmdojiqw(bool ltcrtzlwgrcndj, double xrydmlqhgcb, int xwqikgsjgpjufl, bool qlqhhstyzzhfx, int cmxjcjely);

};


string kcrsyia::qwokmzselprd(int vmajgnmpx) {
	bool lpskxvzzi = false;
	if (false != false) {
		int pkewxnczuq;
		for (pkewxnczuq = 4; pkewxnczuq > 0; pkewxnczuq--) {
			continue;
		}
	}
	if (false != false) {
		int yvfu;
		for (yvfu = 92; yvfu > 0; yvfu--) {
			continue;
		}
	}
	if (false != false) {
		int rt;
		for (rt = 19; rt > 0; rt--) {
			continue;
		}
	}
	if (false == false) {
		int qgs;
		for (qgs = 89; qgs > 0; qgs--) {
			continue;
		}
	}
	return string("pmmobimopmn");
}

int kcrsyia::lsieduztwzjcrttcw(string txlowqutxm, int pgkydmloyariqwv, double xcvbaxgqsjztcxj, double mpndbylgcsptecu) {
	string ujhgfwjcvinbhl = "xykrxiktmkeekakjgjvegaxwnzzlkylgueidfejobbaqkmwrlooerspmqwfpkykmdy";
	string woriktkquf = "scu";
	bool cfsdaoxk = true;
	double joclpsab = 3892;
	string glfngw = "sqglboezx";
	double qjalr = 38089;
	double ermngm = 9737;
	double jxoioyccdqvpwu = 5910;
	bool ptpzakyzulvxo = true;
	return 10930;
}

void kcrsyia::yeegoxmuyydrfgoecm(string cejujmcwy, double nlkun, double cwcjngf, bool xcdocgd, double aksrifvzulqvfml, int iujxzkrrtgezps) {
	int kvjjrvafynagt = 7659;
	double ahwvywyxzov = 9780;
	double lbjuiozhyg = 15395;
	if (9780 == 9780) {
		int sdovlcg;
		for (sdovlcg = 50; sdovlcg > 0; sdovlcg--) {
			continue;
		}
	}

}

int kcrsyia::flzxwukerxufkbxguwpvsp(string uuagsmsqiw, string jbgmljxdrzqk, double lmvswmk) {
	string jeeptnuao = "lk";
	string mzzivv = "myaydqgwdpqqztgpjnumqbvim";
	bool yahxotlichvpl = false;
	if (string("myaydqgwdpqqztgpjnumqbvim") == string("myaydqgwdpqqztgpjnumqbvim")) {
		int hm;
		for (hm = 47; hm > 0; hm--) {
			continue;
		}
	}
	if (string("myaydqgwdpqqztgpjnumqbvim") != string("myaydqgwdpqqztgpjnumqbvim")) {
		int nkkyqihc;
		for (nkkyqihc = 77; nkkyqihc > 0; nkkyqihc--) {
			continue;
		}
	}
	if (string("lk") != string("lk")) {
		int fewkw;
		for (fewkw = 45; fewkw > 0; fewkw--) {
			continue;
		}
	}
	return 18446;
}

void kcrsyia::sbrbgkrxgdzwvjsmdojiqw(bool ltcrtzlwgrcndj, double xrydmlqhgcb, int xwqikgsjgpjufl, bool qlqhhstyzzhfx, int cmxjcjely) {
	int vpbwzgjmh = 713;
	string gxutgl = "nuokjvjtuiwzkpbcdavxbzpxqfoknnkfukwrnpjwjrbazyzapmtegyplwdrycyxfviemnmfysceapbha";
	double fmaxeo = 11636;
	int bkojkzdry = 4729;
	string oenqyumch = "xo";
	if (11636 == 11636) {
		int uospr;
		for (uospr = 3; uospr > 0; uospr--) {
			continue;
		}
	}
	if (713 != 713) {
		int vwvrqzulon;
		for (vwvrqzulon = 96; vwvrqzulon > 0; vwvrqzulon--) {
			continue;
		}
	}
	if (string("nuokjvjtuiwzkpbcdavxbzpxqfoknnkfukwrnpjwjrbazyzapmtegyplwdrycyxfviemnmfysceapbha") == string("nuokjvjtuiwzkpbcdavxbzpxqfoknnkfukwrnpjwjrbazyzapmtegyplwdrycyxfviemnmfysceapbha")) {
		int ybe;
		for (ybe = 73; ybe > 0; ybe--) {
			continue;
		}
	}
	if (string("nuokjvjtuiwzkpbcdavxbzpxqfoknnkfukwrnpjwjrbazyzapmtegyplwdrycyxfviemnmfysceapbha") == string("nuokjvjtuiwzkpbcdavxbzpxqfoknnkfukwrnpjwjrbazyzapmtegyplwdrycyxfviemnmfysceapbha")) {
		int frwib;
		for (frwib = 0; frwib > 0; frwib--) {
			continue;
		}
	}
	if (4729 != 4729) {
		int hmqdoplk;
		for (hmqdoplk = 2; hmqdoplk > 0; hmqdoplk--) {
			continue;
		}
	}

}

bool kcrsyia::geamdyqffhciml(string jimobfqtlfnvz, double fijkocgie, double tnqbsfxj, double muzjifanj, double smuonrltkdo, int pbhutn, double qihsjqcqyzpub) {
	bool azsebxanfgsj = true;
	string bwwrjqyu = "usbbqpnknhljnguaboxfyperpvztpymnkyooyvevpa";
	int afdugmjoilgx = 5778;
	int riukdsrfxidlm = 350;
	bool cfunmny = false;
	if (5778 != 5778) {
		int anwbwzfd;
		for (anwbwzfd = 30; anwbwzfd > 0; anwbwzfd--) {
			continue;
		}
	}
	if (string("usbbqpnknhljnguaboxfyperpvztpymnkyooyvevpa") == string("usbbqpnknhljnguaboxfyperpvztpymnkyooyvevpa")) {
		int mhbnqfq;
		for (mhbnqfq = 73; mhbnqfq > 0; mhbnqfq--) {
			continue;
		}
	}
	return true;
}

void kcrsyia::bpjmiyrbfombqjioudipi(string hmkgwcl, bool msaceyqg, int ravrqe, string edcvkiatolcpakl, bool yksnweqmei) {
	int qzhzzwpd = 3502;
	string htavxuru = "dxxnqntsoywbcsxelfwvleqzhahcnkzngpurhjngujeambkmpju";
	string xoaok = "wynbaneuuvhbqlbbbfqgfnyveyiyckvoxihqdrnlrbdbwdlzygvbusnrrjjdspzqnsjnhfkgebotxqsrf";
	int mypdxm = 7968;
	string bovzfqs = "kjvmtbbrvtzquwgczhgvaijavvwsd";
	bool zykxcsv = false;
	string ppptdkxppil = "prclfskwxwbyheyvzjcxlgglorcaihfztgyabcocvudolmejcianunracddldiwvsfwpwfewhixjhqiocxzomlhtmrwnuoasjqmr";
	string tlhlwr = "frhkxbwxdfnoespxxzoxqicqyoaxqxabywdbtrsluzakmqihepsu";
	string pqogpsd = "fjuoxqarmjmwatxrlkgkbtehzrfcepovfzekziohkmpshaipyrixddkbopdelxwhzbacgpvhbuhkiqjnoabsfrdyxgwsaqh";
	string yiprdwutrlcbvi = "eavidjuaslnbccfqotptjfmmggnvpzrxapblplkcsfmjlhsgxkufezc";
	if (false == false) {
		int amy;
		for (amy = 53; amy > 0; amy--) {
			continue;
		}
	}
	if (string("fjuoxqarmjmwatxrlkgkbtehzrfcepovfzekziohkmpshaipyrixddkbopdelxwhzbacgpvhbuhkiqjnoabsfrdyxgwsaqh") != string("fjuoxqarmjmwatxrlkgkbtehzrfcepovfzekziohkmpshaipyrixddkbopdelxwhzbacgpvhbuhkiqjnoabsfrdyxgwsaqh")) {
		int cwie;
		for (cwie = 87; cwie > 0; cwie--) {
			continue;
		}
	}

}

double kcrsyia::rhvqkjycyw(string worbwwbix, int vruso, int lwdxywdm) {
	string yklkxgmcqwubee = "zunrzjnysamknhjmpkjfxffcgdplafetcyboqwaqywyqkghkhqktccgdrt";
	double tcxujttrtuhm = 41835;
	bool gheqcvasxyq = true;
	return 78354;
}

bool kcrsyia::imxdmtobjqcziunkcmo(bool dnvgnldqwgmtlxg, string tinaamkwzx, string lcqkoaozeim, double zdxzo) {
	return false;
}

double kcrsyia::frydkxxojs() {
	string etujwhhvlvz = "odnnlesbyanurpvpowbmvbaat";
	string bwbhkkdn = "zmjzhlrjrxrdswwtxcsazfkokmntaugjrrykkvomwbwmlwzmer";
	int xuxtcszrvcmef = 1964;
	double ahuxqbw = 66858;
	string fvphkzx = "icpwxwvbnvzhnnxqurkjhbsoddyfwiredominqlxctzmrdnvyseamunnypgpybalestrj";
	double agufdcgwmrornnd = 62071;
	string bxvqtoeo = "iqjyz";
	bool towxxbvxoz = true;
	if (true == true) {
		int snvjkgp;
		for (snvjkgp = 2; snvjkgp > 0; snvjkgp--) {
			continue;
		}
	}
	if (true != true) {
		int ckj;
		for (ckj = 48; ckj > 0; ckj--) {
			continue;
		}
	}
	if (1964 != 1964) {
		int hckp;
		for (hckp = 93; hckp > 0; hckp--) {
			continue;
		}
	}
	if (66858 != 66858) {
		int nxdnos;
		for (nxdnos = 46; nxdnos > 0; nxdnos--) {
			continue;
		}
	}
	if (string("zmjzhlrjrxrdswwtxcsazfkokmntaugjrrykkvomwbwmlwzmer") == string("zmjzhlrjrxrdswwtxcsazfkokmntaugjrrykkvomwbwmlwzmer")) {
		int nyp;
		for (nyp = 37; nyp > 0; nyp--) {
			continue;
		}
	}
	return 49608;
}

bool kcrsyia::swhfzzevte(string toeigbn, bool wddqviql, double pbbvy) {
	bool ymvudteqn = true;
	string qaollaf = "bacigwciynohzfrptpmojnflhbtgsnpaybrlppkltkfmbjbcdreqpsultgvouqczufxpcbivtrmiqmxeeylhand";
	string pegbcucppm = "xaewvuvwvzqlfingqvxrbpcususuzbieftrpnbygrdthvzkgzsfbyayywdcdrwcjmxrmoatfvhewmthszwozmryurxec";
	int tvvwso = 1633;
	int pnolyhrrjx = 1562;
	string tghvxvzky = "bqsccnilklijhuzilnnohkyvy";
	string aparnfbnlhizaa = "hlazucuz";
	bool ldxty = false;
	return false;
}

bool kcrsyia::gxtwsoogbbbvxaqqcwvw(double aptwajrkkll, double monyuygjbcbo, int usdrqqi, int nzcyoarhqoco, string skvdcj, bool zmfamxjy, bool dgkzlj, bool rtkelwu) {
	return false;
}

void kcrsyia::rqtwyaymqizvvgm(int ntdlywgtbztca, double lccuzhydmg, int bgoiwlysbrzhi, string fkhjlqnzedosw, string zgpjclnyhwwtnq, double djokmwjwalq, bool juubrjejofz, int yrpgltovm, string ujwtwpe) {
	bool wepnqufhllljb = true;
	int ishul = 4720;
	if (4720 != 4720) {
		int byltgab;
		for (byltgab = 9; byltgab > 0; byltgab--) {
			continue;
		}
	}
	if (true != true) {
		int yi;
		for (yi = 95; yi > 0; yi--) {
			continue;
		}
	}
	if (true != true) {
		int cp;
		for (cp = 51; cp > 0; cp--) {
			continue;
		}
	}

}

string kcrsyia::nhxqpztdyimdwhphqgnnannt(string mihrr, string dlvodcszdgmn, string imnxowuv, bool yrdgdyqouvjhim, double jkplvvvcfbpu, string tsfaugduugg) {
	int ffsdpdi = 329;
	string lgtssbvmvefd = "svzwygvoearzrv";
	int bssspf = 1193;
	double wamatnbktxpgp = 8718;
	if (8718 == 8718) {
		int qiey;
		for (qiey = 23; qiey > 0; qiey--) {
			continue;
		}
	}
	if (string("svzwygvoearzrv") == string("svzwygvoearzrv")) {
		int xo;
		for (xo = 61; xo > 0; xo--) {
			continue;
		}
	}
	if (8718 != 8718) {
		int rrzapyj;
		for (rrzapyj = 30; rrzapyj > 0; rrzapyj--) {
			continue;
		}
	}
	if (1193 == 1193) {
		int lwlhahihal;
		for (lwlhahihal = 34; lwlhahihal > 0; lwlhahihal--) {
			continue;
		}
	}
	return string("dsqszlxqrwusjam");
}

void kcrsyia::rseqavjpnmb(string rurghmc, string hphmrgbkrmef, bool esrntbhmvstw) {

}

double kcrsyia::gdsnkkbzzxv(int odsmfrddlposwu, double neskbiw, bool dptbdjsm, bool bhinxylmtxwt, string lrpnzx, double zvttobgtickce) {
	bool rpwyxesi = false;
	return 23145;
}

int kcrsyia::zmbipyzibnlgyfizjvtzr(int eogdbq, string mnsecgpjvarzop, double wafmjojtjkc, int fkbzdenaxadz, double ixnewppitreizl, int bapknxfpreawzl, string wbmpmmrwazlzi, bool rqmphbmphvfx) {
	double wfcia = 8963;
	double tlnuvyinh = 42489;
	string redzhlxim = "dyxdgmbsnuihlbybuesdgvahnoxdysyvxspxkiowidfvqmyojkaapwxqyffbkzuht";
	string ikqstlpi = "yssckbabay";
	int ngtnjcyiecxhqn = 8416;
	string kvcjhliawtfk = "cpzmersimoetxtzwexlwuicxno";
	bool tsronvfpnlpvx = true;
	int thpagscnkad = 3647;
	if (8963 != 8963) {
		int uvxiv;
		for (uvxiv = 38; uvxiv > 0; uvxiv--) {
			continue;
		}
	}
	if (8963 != 8963) {
		int bokk;
		for (bokk = 51; bokk > 0; bokk--) {
			continue;
		}
	}
	return 42532;
}

string kcrsyia::xvboaewfrrrbzqnvekv(bool faqlwlpezrrz, int rducshzljxf, string qypnikibbwfdn) {
	string kmvlwnc = "hsmflbturllqcehnpnvwsfksses";
	int vxiusmik = 2211;
	bool emzhwef = false;
	int gnnonkkxsag = 4241;
	int jqsanbubeeokl = 162;
	double vdavps = 11247;
	double ieqkoyulquvutd = 16619;
	string lhlgpabrvsyyq = "ymmbnvftvtdgwwwdyxtialuyivesydkmndkzrhylqorgqtlppjaxvlvsxezgnm";
	double esebivxdz = 15211;
	double fptpoxdnilmfpj = 94114;
	if (false == false) {
		int ujv;
		for (ujv = 96; ujv > 0; ujv--) {
			continue;
		}
	}
	if (16619 != 16619) {
		int hhjezvk;
		for (hhjezvk = 56; hhjezvk > 0; hhjezvk--) {
			continue;
		}
	}
	if (4241 == 4241) {
		int ok;
		for (ok = 91; ok > 0; ok--) {
			continue;
		}
	}
	if (162 != 162) {
		int ic;
		for (ic = 36; ic > 0; ic--) {
			continue;
		}
	}
	return string("n");
}

double kcrsyia::jhlanigubvy(double jpunnjyz, bool fcpasyuskuc, double qtucrgyudzyx, bool gzfljtbpdsfg, int fefoydp, int gnmdqaxrtjerz, string uhprwlpgxwx, int kgkwjukilby, bool lhsocesie) {
	bool wjshenpihc = false;
	double glzmanrvhquof = 17731;
	string ntowrlkpmputsw = "qqa";
	int vzspxbvlljq = 1753;
	string hjtlmbmsaohjc = "wqqukeynr";
	string hodyynpffjt = "fpyyopkasqhoqesnkzqaiahznzpjcjwzswvrz";
	int plrwovobmc = 1655;
	int otdpfzalvn = 527;
	bool wmgztc = false;
	bool dudjfusqwnalky = true;
	if (string("qqa") == string("qqa")) {
		int tvhlyhoiac;
		for (tvhlyhoiac = 66; tvhlyhoiac > 0; tvhlyhoiac--) {
			continue;
		}
	}
	if (true == true) {
		int wiqvqnj;
		for (wiqvqnj = 61; wiqvqnj > 0; wiqvqnj--) {
			continue;
		}
	}
	if (false != false) {
		int jcrjymec;
		for (jcrjymec = 15; jcrjymec > 0; jcrjymec--) {
			continue;
		}
	}
	if (string("fpyyopkasqhoqesnkzqaiahznzpjcjwzswvrz") != string("fpyyopkasqhoqesnkzqaiahznzpjcjwzswvrz")) {
		int ojyta;
		for (ojyta = 77; ojyta > 0; ojyta--) {
			continue;
		}
	}
	if (17731 != 17731) {
		int gxx;
		for (gxx = 25; gxx > 0; gxx--) {
			continue;
		}
	}
	return 11420;
}

string kcrsyia::ctezrzudcvvpmsde(bool hxyocvld, string uuaelewtpalkdn, int kyajlewtpfsiak, string qdtjgwwbnnqk, string eurybdxnrc, bool juujxpgrd, string bouzgfaq, int djaedlpqqjybtsj, bool oyohhmwdecqgqjo) {
	bool iioscyuee = false;
	bool qxsasakniaz = true;
	int vkigdth = 973;
	bool owacur = true;
	int wlsjfeszksbvt = 1870;
	double jwxkc = 34330;
	string sfyoqutjinoiown = "cohhurpxkzraiiq";
	return string("mg");
}

bool kcrsyia::rcjxhlatogrqyukhvbdazbvet(int jbqrzcwwe, int xvwtxnumf, string mounxpq, int sixrrlg, bool lxcbkpbeokz, bool txzvqrguvbgp, int szhalqwunforeet, bool mdcgycymmlqgtmj, int uqinysrfacagoa) {
	int oruvycsuboo = 7280;
	double lopjhettbcak = 1984;
	int xcgnpuagb = 268;
	string dpgnc = "bxjeytmxbggohdmoqufatrhwmmhbcgyctnhqtorcbmxwf";
	double lihxnjfeiq = 69430;
	if (7280 != 7280) {
		int sdmrtzur;
		for (sdmrtzur = 93; sdmrtzur > 0; sdmrtzur--) {
			continue;
		}
	}
	if (1984 != 1984) {
		int uohdwiod;
		for (uohdwiod = 59; uohdwiod > 0; uohdwiod--) {
			continue;
		}
	}
	if (69430 == 69430) {
		int hmeroyje;
		for (hmeroyje = 63; hmeroyje > 0; hmeroyje--) {
			continue;
		}
	}
	return true;
}

kcrsyia::kcrsyia() {
	this->gxtwsoogbbbvxaqqcwvw(23637, 16918, 106, 775, string("sganvlbaroslbgtpwrmvcgjugwfiwqjydakulmnnabhrprejyxkcbyoawwwcb"), false, true, false);
	this->rqtwyaymqizvvgm(5497, 83554, 682, string("nqwefxvmkbdjnzptypeibyulk"), string("wmcwfljashxemnaed"), 7622, false, 182, string("yxcmnzzsfznktdrwvqttvsfhamwcdbgscghljgwrqgqopmjcdfbutgrqpjozeeijswtxhfklnrxzjxagwxhrdgllgyi"));
	this->nhxqpztdyimdwhphqgnnannt(string("dhlrvwruchqylvhcilwiokjgdwpgzvbigcklkqrchmksuodcajg"), string("azcukamjyxgqywiybz"), string("nqvfwiuheozhnuscuiqqhlytueklzzwmxwryihfckxndzxkrgpcxvptyhzidxfpudfcnwcgynjhvmq"), true, 26209, string("sftqdjfwubdtydsybnzxxlagnseycwqpeoyvzgsbqlwyuqobiwyqmbbcetjrikeohtbpdbngkzbzoblkdh"));
	this->rseqavjpnmb(string("pvzlimeofxuwyjvtusdwoqxuuxsambdkdtvtnjtqvnoocpdnjkpparttnljvefowd"), string("mmjbufjvugngqrcmixmiskbvzlefbqoeyrtbswzgogzfdwovpdtamukhldsvzgflpvpligptxkpaspotyovlvgmp"), true);
	this->gdsnkkbzzxv(267, 5965, false, false, string("uyxtxqszgefblocfwxyhiculjamhgdzzfmdjrdomrkbmrmnqirauyvjaimszfzeyvcocw"), 5841);
	this->zmbipyzibnlgyfizjvtzr(3714, string("edmmaknwolvekahgcwbomnduoriwloug"), 15177, 3866, 8702, 7546, string("hkmolulwpvlqmvadhwxbgumgnevngaqlyavxhllnqrckaqehuwebacvbtjmcnpkqqtsmwkawqkjkfirbvis"), false);
	this->xvboaewfrrrbzqnvekv(true, 447, string("xsfyearxslqygwgdanoyziiptdtkkczlzfzrrtbalmvdylookrufpqnftihfwueuwyjkwwlfukdiupysxvzhakv"));
	this->jhlanigubvy(58080, false, 62877, false, 1116, 1489, string("rzmpwptrnyxfnbgzqldnrrkblsxiaogakyjptjgtqoicrellufmhsexwxlpx"), 3555, false);
	this->ctezrzudcvvpmsde(true, string("qisnbkshjwozxblaiaffxsgrpswrgaliwzhnvlznnjuk"), 2999, string("lvjvkvtcicgzlskdssrjljqohzqgxztkruksxfhkwubxswhqldmaizdd"), string("fwgpnojpdqtjwchzfyitksoabytpajgdjbzut"), true, string("lqwmgqsbfbuswuileihpazyzzzyqermrwjkumsnxhkuzxfweqntjhkaonnjcjirxyrdbptsedtgdzu"), 2339, false);
	this->rcjxhlatogrqyukhvbdazbvet(2300, 1636, string("obhyplmettn"), 1917, true, false, 3712, true, 1463);
	this->geamdyqffhciml(string("smaghgtirqptvhg"), 10136, 5374, 27066, 53561, 8637, 24093);
	this->bpjmiyrbfombqjioudipi(string("odkvelrgokbnfmtzxsmcawemznfqdzqwumuhpfraitukphxqlthaaspuilwhhhbatvuewhljclmgrikczuofzywh"), true, 925, string("lbhenhojrritjjayvjogkwkwbuceyznekhkhazmpglczbaqxifzvzrzvnfjqbacelxvtkliabdeepvu"), false);
	this->rhvqkjycyw(string("cglwywshnkorhbeqshoavcdqkjwoziykpmlcutnjdkhggsmihvokvcykoxayidqlnpbnjbxablubcfbsxomlyauljk"), 4406, 4025);
	this->imxdmtobjqcziunkcmo(true, string("tvvauhflerxaftgpbaimsfsigxxshocgguotmtuilshxmchxmjdqcnewlkkxind"), string("mvdqodasgsnzdzvabrxpvkfblhpqtmxjohhswjjrpffcyzgzuksoorwtakdhrwrgtnncsfkitcnajszekzolcyyopkjxslldjad"), 11860);
	this->frydkxxojs();
	this->swhfzzevte(string("eeuypwczrrfvbvptpzafkijqsevsocilvkwudlvdrdvjhdhwjtqexszqkcdjah"), true, 23917);
	this->qwokmzselprd(6245);
	this->lsieduztwzjcrttcw(string("ckkwqlpetyyoyetnandiyfjpnzjvofbpmpzzijpothxnzladggqmucjsxlmudqwfnwkfbiawnjphgndizpuarsa"), 1163, 77758, 959);
	this->yeegoxmuyydrfgoecm(string("ogqhtmtwrgdolqs"), 60124, 48980, true, 27467, 2192);
	this->flzxwukerxufkbxguwpvsp(string("my"), string("seihrhrgmjcbezmbanzqcthdekjdylepsmnnt"), 9361);
	this->sbrbgkrxgdzwvjsmdojiqw(true, 24607, 4153, true, 6297);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class wmxygcw {
public:
	int vvvyuyxlqoac;
	wmxygcw();
	double lbftntxjfunwzbijdtfa(string avrhrwf, bool fjybdhupu, bool luhojuss, bool nfqmp, bool lgeqj, bool racxyldqnhfnn, string zxtnhcymvm, int wilulswomw);
	bool nfheganosavoqvxuujxcdw(string vlxzqoj, int nryqcjh, string cwdomksrenr, double ouymcuqqh);
	void jrxsteicvceglxj();
	double uwldpxtjpgfauywuyiky(string wdcxbmfxf, string cmhzcwk, double fauulqap, bool bvqjnmwzfh, string muzpkw, int ujbdsghxdbbhveh, double cqsmfcj, bool hlwuilzh, string whmhvrpfcac);
	void tyisojxtruwckzyax(double vwbrjvsugkjjg, bool mlrczlb, int agoheht, double qzscusagplqguk, double fnhbuqih, double pfmvw, double wrcjm, bool ueisupvgsqnjyp, double vjwtlbprbyl);
	double gisvwusyqgma(int ldtvcpcuwwq);
	void fxyrzplxci(bool qkhcapslya, bool sfljnrzllds, string rncvk, int ykiwzk, bool ptlldsw);

protected:
	int wryeiotuampb;
	int xkzkupmonwzqbl;
	bool kwchlxwzqwlzub;

	double dpvelykxsysbfkreqwxmos(string psrodlqew, double knjokpngpdotfk, double vxbxmkbyqjwg, double obdfnrwcpn, double kmzgsc, string mrmunaykxj);
	void boonoauwtalpjqcuqhmhgfg(string nmbhlaxcf, string hjuxhpzchishzpf, int ucbndooizyjrx, int neejf);
	string nrkyknynbtmqdjprmlm(bool lxwjl, int qemugxempw, double ehphiqxggh, double qtmnypmffvncdba, double stxfqzfd, bool yvuwjtijfpvmus, int txfgihuxwezxlpe, bool fjrpkibxjedkil, int ippbdfnu, double ytiitt);
	int jgvthihhacgybwmwaxlwrqpf();
	void sjvwsxobspxreewtd(int igllxm, bool mipplmssz, double sxjeaukehvst, double oegzbtxdv, bool ssslqdnlaa, int hjduaiwasiy, bool ohzwqkmfbogq, bool nbmmaowul, bool bbqjxrm, bool ffklo);
	string bfqqckhufe(bool udnovecrypfeass, bool tgjztkh, bool zdtcojajbj);

private:
	string olgplmhuxxqbx;
	int ocduqgvxbx;
	bool hdmzzlq;

	void devcfeehlqvzkkqgxaiuyuipk(int sxziumpvisr, int fwhcfxsaaqzoy, string mhjixuk, string jazka, bool tadsjansmfqlt, bool tgpvck);
	string tdcskjavvguoco(double esvfui, string hojlstw, bool hsuspbrczp);
	int guudemqbvazymgcau();
	void sgdnrskjvxigzpqgx(int uemxjzjh, bool vxqof);
	int uefqrnhtbzpjxcfgrvqc(int bsqfhbpmkynvpva, int iqtfrga, int iepqb, string mvuezdvm);
	string ggcxzkvtas(bool eysyehfb, bool smbaemkag, string szaicrzlurpjzx, string cdqhbuqgktucwv, double jvojilxvazsw);
	void vklnkzjtqwercvajnbmmh(int zxbxqgny, bool gswnob, double jddkditgurq, double qkqopu);
	double scaubdqugjtxypihfvv(string vwqkuglonaukfjs, double nheaajlicxbjchs, double nyqekmauxop, int jxdpb);
	int llnhwqculhmcfogep(double fhqewucegextk, double micofekavn, int qyxxhlsa, bool pwqcqhy, int rbcqpxlziqy, double tjkeivrctwgcrjp);

};


void wmxygcw::devcfeehlqvzkkqgxaiuyuipk(int sxziumpvisr, int fwhcfxsaaqzoy, string mhjixuk, string jazka, bool tadsjansmfqlt, bool tgpvck) {
	double teabni = 22787;
	double wrvlegu = 57663;
	bool ysuicciledeb = true;
	int eufxzvjjkhmoro = 872;
	bool mzdslcglfccvs = false;
	string zehbdzo = "xamivdomzlecglsvbfacrdofldnenfaotrtacmrrdsivapywygbhndhubnhdbrnsihzjppqlasiwnirylkncymqxlkyvr";
	int nvfhfzea = 1126;
	if (22787 != 22787) {
		int jwlsn;
		for (jwlsn = 59; jwlsn > 0; jwlsn--) {
			continue;
		}
	}
	if (true == true) {
		int cyv;
		for (cyv = 14; cyv > 0; cyv--) {
			continue;
		}
	}

}

string wmxygcw::tdcskjavvguoco(double esvfui, string hojlstw, bool hsuspbrczp) {
	string wrgdqly = "gotossrwqgehfwdh";
	int nrzsfdppaphf = 2118;
	double mljkltkfrxgjty = 13353;
	string exkprxsxbtam = "wkixjcwvqopihzvfgnfpttjyyshxrvfvkeambfpdmmflavwasneewgsgvsixhvwfotifghcegqfqnjoxywthpxdaxdpwttltxa";
	int nmmmcszgeahm = 4727;
	string gornvxsdxuy = "rinbluxaoiwvrhfsbrdvamkdiwcpxmsxiwmlrpkfqsmgkxzrpakqjtalkagnqzdqq";
	double vpyswjwlt = 10573;
	double hqdnpfivypmxs = 33900;
	bool efqqkhpxuclraa = true;
	if (33900 != 33900) {
		int vtnsapm;
		for (vtnsapm = 28; vtnsapm > 0; vtnsapm--) {
			continue;
		}
	}
	if (string("rinbluxaoiwvrhfsbrdvamkdiwcpxmsxiwmlrpkfqsmgkxzrpakqjtalkagnqzdqq") != string("rinbluxaoiwvrhfsbrdvamkdiwcpxmsxiwmlrpkfqsmgkxzrpakqjtalkagnqzdqq")) {
		int pqoqpgojbb;
		for (pqoqpgojbb = 52; pqoqpgojbb > 0; pqoqpgojbb--) {
			continue;
		}
	}
	if (string("gotossrwqgehfwdh") != string("gotossrwqgehfwdh")) {
		int bqtjlggxg;
		for (bqtjlggxg = 54; bqtjlggxg > 0; bqtjlggxg--) {
			continue;
		}
	}
	return string("gwayqpoazwuiq");
}

int wmxygcw::guudemqbvazymgcau() {
	bool kmxehmdyyqq = false;
	if (false != false) {
		int ecihvyu;
		for (ecihvyu = 41; ecihvyu > 0; ecihvyu--) {
			continue;
		}
	}
	return 53495;
}

void wmxygcw::sgdnrskjvxigzpqgx(int uemxjzjh, bool vxqof) {
	bool fnsoh = true;
	bool adobaan = true;
	int iwttohdgwcmxka = 625;
	string rgycctyutlm = "qyqajqaywfhpjtfjjjaqvufgjwoctgfjtwmmtexhczmqwmkktrdqxriehlffiodbd";
	string dexqwkby = "sgjxwqgcryllueioyvtkqtkvjibpdvvvhdrthfgbvrbvugmnagjoyyobzblrernmciyw";

}

int wmxygcw::uefqrnhtbzpjxcfgrvqc(int bsqfhbpmkynvpva, int iqtfrga, int iepqb, string mvuezdvm) {
	string uzngqp = "ocdbhtwfcejxqqegdnraeddhfhyeosklxapbsblmppdqgzjjabkubrzjddbt";
	double fdlmjkypamiq = 20705;
	int blhfnsojco = 2628;
	double rxnklqgzat = 56427;
	bool kvyiog = true;
	string fdmql = "zlubcesvaltobdhtunvisgfqtoqlhjxoeihfqsgqrpgukufwslkzyoluzcjqzzdwogranumcsugbohxpmnqfcjndezaznqolh";
	double dqdmykviukda = 11698;
	if (11698 != 11698) {
		int drur;
		for (drur = 48; drur > 0; drur--) {
			continue;
		}
	}
	if (11698 == 11698) {
		int tgaast;
		for (tgaast = 59; tgaast > 0; tgaast--) {
			continue;
		}
	}
	return 41927;
}

string wmxygcw::ggcxzkvtas(bool eysyehfb, bool smbaemkag, string szaicrzlurpjzx, string cdqhbuqgktucwv, double jvojilxvazsw) {
	bool hnjgxnk = true;
	bool pejsfojdncpz = false;
	bool zpnpzvrryqxm = true;
	if (true == true) {
		int aio;
		for (aio = 61; aio > 0; aio--) {
			continue;
		}
	}
	if (true == true) {
		int qmha;
		for (qmha = 10; qmha > 0; qmha--) {
			continue;
		}
	}
	if (true == true) {
		int mjny;
		for (mjny = 52; mjny > 0; mjny--) {
			continue;
		}
	}
	if (true != true) {
		int iih;
		for (iih = 30; iih > 0; iih--) {
			continue;
		}
	}
	return string("ak");
}

void wmxygcw::vklnkzjtqwercvajnbmmh(int zxbxqgny, bool gswnob, double jddkditgurq, double qkqopu) {
	string gqdwexpqiijjtfp = "bftvfgptslbqhuxroqubaiebuekooeoguuyknagblxtluxcwqixgzpkvfynbrmu";
	if (string("bftvfgptslbqhuxroqubaiebuekooeoguuyknagblxtluxcwqixgzpkvfynbrmu") != string("bftvfgptslbqhuxroqubaiebuekooeoguuyknagblxtluxcwqixgzpkvfynbrmu")) {
		int yjrgfgdyk;
		for (yjrgfgdyk = 24; yjrgfgdyk > 0; yjrgfgdyk--) {
			continue;
		}
	}

}

double wmxygcw::scaubdqugjtxypihfvv(string vwqkuglonaukfjs, double nheaajlicxbjchs, double nyqekmauxop, int jxdpb) {
	string dviatrpbo = "glpdlrhsczviuywjugbimntwwxcz";
	double ymbzyznof = 16568;
	if (string("glpdlrhsczviuywjugbimntwwxcz") == string("glpdlrhsczviuywjugbimntwwxcz")) {
		int rx;
		for (rx = 92; rx > 0; rx--) {
			continue;
		}
	}
	if (16568 != 16568) {
		int pihxeaps;
		for (pihxeaps = 21; pihxeaps > 0; pihxeaps--) {
			continue;
		}
	}
	if (string("glpdlrhsczviuywjugbimntwwxcz") == string("glpdlrhsczviuywjugbimntwwxcz")) {
		int mchmqnhb;
		for (mchmqnhb = 0; mchmqnhb > 0; mchmqnhb--) {
			continue;
		}
	}
	if (string("glpdlrhsczviuywjugbimntwwxcz") == string("glpdlrhsczviuywjugbimntwwxcz")) {
		int xaympbdx;
		for (xaympbdx = 32; xaympbdx > 0; xaympbdx--) {
			continue;
		}
	}
	return 27997;
}

int wmxygcw::llnhwqculhmcfogep(double fhqewucegextk, double micofekavn, int qyxxhlsa, bool pwqcqhy, int rbcqpxlziqy, double tjkeivrctwgcrjp) {
	string rpkyj = "zrtmkuhzcujvgshmcahihmqpppurdrnooycxxpczuctadhrq";
	bool bwuoxpdncwig = true;
	int bqbwxslfutj = 313;
	string kprfpyq = "xabgakonogikhvbtaxqawxajsldwc";
	int hafupr = 2281;
	if (string("xabgakonogikhvbtaxqawxajsldwc") != string("xabgakonogikhvbtaxqawxajsldwc")) {
		int khhugf;
		for (khhugf = 7; khhugf > 0; khhugf--) {
			continue;
		}
	}
	if (string("zrtmkuhzcujvgshmcahihmqpppurdrnooycxxpczuctadhrq") == string("zrtmkuhzcujvgshmcahihmqpppurdrnooycxxpczuctadhrq")) {
		int fuepu;
		for (fuepu = 39; fuepu > 0; fuepu--) {
			continue;
		}
	}
	if (string("xabgakonogikhvbtaxqawxajsldwc") == string("xabgakonogikhvbtaxqawxajsldwc")) {
		int cn;
		for (cn = 80; cn > 0; cn--) {
			continue;
		}
	}
	if (string("zrtmkuhzcujvgshmcahihmqpppurdrnooycxxpczuctadhrq") == string("zrtmkuhzcujvgshmcahihmqpppurdrnooycxxpczuctadhrq")) {
		int jraccd;
		for (jraccd = 56; jraccd > 0; jraccd--) {
			continue;
		}
	}
	return 24307;
}

double wmxygcw::dpvelykxsysbfkreqwxmos(string psrodlqew, double knjokpngpdotfk, double vxbxmkbyqjwg, double obdfnrwcpn, double kmzgsc, string mrmunaykxj) {
	string auzczyril = "sulciv";
	int tiuamyyiftxcbnt = 255;
	int gtdndiqyp = 5106;
	int qfndmapm = 3355;
	string ujytnpizkxu = "mbebkwjltdkfigjltqrcfijfprybkkldasxffitqcbpcrjweccprpkjbextom";
	bool azwiqfufqxml = true;
	double jkzcjvxzfikukbu = 4374;
	string sxgnkudwdadepxz = "gtoxmnkoyokmabjt";
	double ilnzo = 4790;
	string uyyzar = "voqlhnudumlnltcixnewjegegvnxjedphyurakisqnwwfxvpmokpixiexxzzqyzl";
	if (string("voqlhnudumlnltcixnewjegegvnxjedphyurakisqnwwfxvpmokpixiexxzzqyzl") == string("voqlhnudumlnltcixnewjegegvnxjedphyurakisqnwwfxvpmokpixiexxzzqyzl")) {
		int kakmioruww;
		for (kakmioruww = 67; kakmioruww > 0; kakmioruww--) {
			continue;
		}
	}
	if (3355 == 3355) {
		int atumx;
		for (atumx = 44; atumx > 0; atumx--) {
			continue;
		}
	}
	return 35790;
}

void wmxygcw::boonoauwtalpjqcuqhmhgfg(string nmbhlaxcf, string hjuxhpzchishzpf, int ucbndooizyjrx, int neejf) {

}

string wmxygcw::nrkyknynbtmqdjprmlm(bool lxwjl, int qemugxempw, double ehphiqxggh, double qtmnypmffvncdba, double stxfqzfd, bool yvuwjtijfpvmus, int txfgihuxwezxlpe, bool fjrpkibxjedkil, int ippbdfnu, double ytiitt) {
	return string("mykcmwgmfmpia");
}

int wmxygcw::jgvthihhacgybwmwaxlwrqpf() {
	double balufnuk = 16459;
	bool zvrerbgkut = false;
	string entrvhsh = "osphxmyqgwkzqgfbytyzdjirmghwspednitlclthklzeqhphwmmujpmbpztycrspajqifvtqtonuaczbzlmvgbg";
	string ftdxpm = "igkrxovylyssukgtoqdluxlxa";
	string uawjld = "ymhrnblljiyqmcgmhpagxnklntujsrnegzqpzrcuwownxnmfflzmbwvrxoltkoebpkjfabnvgijjnczihakjphqpl";
	if (string("igkrxovylyssukgtoqdluxlxa") == string("igkrxovylyssukgtoqdluxlxa")) {
		int qfowzo;
		for (qfowzo = 76; qfowzo > 0; qfowzo--) {
			continue;
		}
	}
	if (string("igkrxovylyssukgtoqdluxlxa") != string("igkrxovylyssukgtoqdluxlxa")) {
		int qwr;
		for (qwr = 70; qwr > 0; qwr--) {
			continue;
		}
	}
	if (string("igkrxovylyssukgtoqdluxlxa") == string("igkrxovylyssukgtoqdluxlxa")) {
		int uebmp;
		for (uebmp = 34; uebmp > 0; uebmp--) {
			continue;
		}
	}
	if (false == false) {
		int rsvrnm;
		for (rsvrnm = 97; rsvrnm > 0; rsvrnm--) {
			continue;
		}
	}
	if (string("osphxmyqgwkzqgfbytyzdjirmghwspednitlclthklzeqhphwmmujpmbpztycrspajqifvtqtonuaczbzlmvgbg") == string("osphxmyqgwkzqgfbytyzdjirmghwspednitlclthklzeqhphwmmujpmbpztycrspajqifvtqtonuaczbzlmvgbg")) {
		int whayv;
		for (whayv = 7; whayv > 0; whayv--) {
			continue;
		}
	}
	return 23984;
}

void wmxygcw::sjvwsxobspxreewtd(int igllxm, bool mipplmssz, double sxjeaukehvst, double oegzbtxdv, bool ssslqdnlaa, int hjduaiwasiy, bool ohzwqkmfbogq, bool nbmmaowul, bool bbqjxrm, bool ffklo) {
	bool qsdhmezwtfrmj = false;
	if (false == false) {
		int wbsz;
		for (wbsz = 27; wbsz > 0; wbsz--) {
			continue;
		}
	}

}

string wmxygcw::bfqqckhufe(bool udnovecrypfeass, bool tgjztkh, bool zdtcojajbj) {
	double txgefkkrgym = 11204;
	double rukzqzgdgcvp = 17249;
	double aymqvkcy = 22386;
	int dtwyggz = 1711;
	bool dhhqs = true;
	int jbycslsgsigjbk = 5179;
	if (17249 != 17249) {
		int pg;
		for (pg = 81; pg > 0; pg--) {
			continue;
		}
	}
	if (11204 == 11204) {
		int yumwzrhg;
		for (yumwzrhg = 38; yumwzrhg > 0; yumwzrhg--) {
			continue;
		}
	}
	if (17249 != 17249) {
		int gmknih;
		for (gmknih = 33; gmknih > 0; gmknih--) {
			continue;
		}
	}
	if (22386 == 22386) {
		int taj;
		for (taj = 91; taj > 0; taj--) {
			continue;
		}
	}
	return string("oolxhkbfepewmgn");
}

double wmxygcw::lbftntxjfunwzbijdtfa(string avrhrwf, bool fjybdhupu, bool luhojuss, bool nfqmp, bool lgeqj, bool racxyldqnhfnn, string zxtnhcymvm, int wilulswomw) {
	string fjpxejgwbygo = "uzoilppxlwliujtleufjslyagrlqxffohemzgndugydbzhxybpvgxcgepwcflwdturynewayooxjj";
	int ggdgbitkpdth = 2457;
	string vkzlgrccpmxbrk = "xelbmentetcfrqidvppdiiookztzdlpflyxlwbgoumnitlrmppxggwuvmzljcmcyzjlzmsv";
	int yjgfaxeggbruvml = 1570;
	bool skgyykmzmgjm = true;
	return 50121;
}

bool wmxygcw::nfheganosavoqvxuujxcdw(string vlxzqoj, int nryqcjh, string cwdomksrenr, double ouymcuqqh) {
	int tvmusedz = 2154;
	double uzansh = 45465;
	double mkaciwekavhzpl = 38044;
	if (45465 != 45465) {
		int pwwsqo;
		for (pwwsqo = 16; pwwsqo > 0; pwwsqo--) {
			continue;
		}
	}
	if (38044 == 38044) {
		int oggnzhpbg;
		for (oggnzhpbg = 29; oggnzhpbg > 0; oggnzhpbg--) {
			continue;
		}
	}
	if (38044 == 38044) {
		int cwwqqdjvtc;
		for (cwwqqdjvtc = 100; cwwqqdjvtc > 0; cwwqqdjvtc--) {
			continue;
		}
	}
	if (2154 != 2154) {
		int jaep;
		for (jaep = 12; jaep > 0; jaep--) {
			continue;
		}
	}
	if (45465 == 45465) {
		int gfkjiwcsdm;
		for (gfkjiwcsdm = 5; gfkjiwcsdm > 0; gfkjiwcsdm--) {
			continue;
		}
	}
	return true;
}

void wmxygcw::jrxsteicvceglxj() {
	bool dvofxhoolytvh = false;
	int mryfybybgwpm = 168;
	double meqfvzpzao = 27821;
	bool ioiczewenxj = true;
	string jvfcwnazvbadmay = "ozomwmbzwxxkqlbpfaxsclknmlxudwtjijdthxzukybtahgjllmmbxctadkzvluklblvrplkczymmkgfaquvyhu";
	if (false != false) {
		int fzbkom;
		for (fzbkom = 57; fzbkom > 0; fzbkom--) {
			continue;
		}
	}
	if (string("ozomwmbzwxxkqlbpfaxsclknmlxudwtjijdthxzukybtahgjllmmbxctadkzvluklblvrplkczymmkgfaquvyhu") != string("ozomwmbzwxxkqlbpfaxsclknmlxudwtjijdthxzukybtahgjllmmbxctadkzvluklblvrplkczymmkgfaquvyhu")) {
		int ja;
		for (ja = 15; ja > 0; ja--) {
			continue;
		}
	}
	if (false != false) {
		int gflk;
		for (gflk = 41; gflk > 0; gflk--) {
			continue;
		}
	}
	if (27821 != 27821) {
		int loqpfocp;
		for (loqpfocp = 5; loqpfocp > 0; loqpfocp--) {
			continue;
		}
	}
	if (true == true) {
		int nrat;
		for (nrat = 19; nrat > 0; nrat--) {
			continue;
		}
	}

}

double wmxygcw::uwldpxtjpgfauywuyiky(string wdcxbmfxf, string cmhzcwk, double fauulqap, bool bvqjnmwzfh, string muzpkw, int ujbdsghxdbbhveh, double cqsmfcj, bool hlwuilzh, string whmhvrpfcac) {
	double gozoypy = 4423;
	bool crepkyi = false;
	int ruebzoe = 998;
	bool ziqstwjmzeejqmf = true;
	int yqskxxznezrdyrs = 2193;
	bool npdrbn = false;
	if (4423 == 4423) {
		int nqdth;
		for (nqdth = 81; nqdth > 0; nqdth--) {
			continue;
		}
	}
	if (false != false) {
		int evacxaa;
		for (evacxaa = 36; evacxaa > 0; evacxaa--) {
			continue;
		}
	}
	if (false == false) {
		int uoiuglx;
		for (uoiuglx = 16; uoiuglx > 0; uoiuglx--) {
			continue;
		}
	}
	if (true == true) {
		int lp;
		for (lp = 46; lp > 0; lp--) {
			continue;
		}
	}
	return 34582;
}

void wmxygcw::tyisojxtruwckzyax(double vwbrjvsugkjjg, bool mlrczlb, int agoheht, double qzscusagplqguk, double fnhbuqih, double pfmvw, double wrcjm, bool ueisupvgsqnjyp, double vjwtlbprbyl) {
	double hrjja = 36127;
	double ldmlulhuvqrvjsm = 52539;
	string rsoykx = "mpfucznupqejgnurowurzidpncurrstmhrhcrebjsmqlereaybqrrhxemizzdtbztgdfwvjok";
	double mdckpgf = 2247;
	string obgrbhbmeubw = "rgvuncbhlzpcsoiyxupfdrfioexqjqaukoml";
	bool omlnwbynxafznkl = true;
	double ezsfvokxqgllalj = 14772;
	if (2247 == 2247) {
		int wzfwihre;
		for (wzfwihre = 59; wzfwihre > 0; wzfwihre--) {
			continue;
		}
	}
	if (string("rgvuncbhlzpcsoiyxupfdrfioexqjqaukoml") != string("rgvuncbhlzpcsoiyxupfdrfioexqjqaukoml")) {
		int scjbxqszif;
		for (scjbxqszif = 56; scjbxqszif > 0; scjbxqszif--) {
			continue;
		}
	}
	if (14772 == 14772) {
		int rjaa;
		for (rjaa = 11; rjaa > 0; rjaa--) {
			continue;
		}
	}
	if (true != true) {
		int ezwqi;
		for (ezwqi = 41; ezwqi > 0; ezwqi--) {
			continue;
		}
	}
	if (true == true) {
		int huavdgafns;
		for (huavdgafns = 70; huavdgafns > 0; huavdgafns--) {
			continue;
		}
	}

}

double wmxygcw::gisvwusyqgma(int ldtvcpcuwwq) {
	string vaqim = "xymxafvp";
	double tozzfgnfexrfbfg = 31784;
	int mbixoxxjwyesypw = 2144;
	int tahjewnssrehct = 1455;
	double gwajqjjyct = 85156;
	bool vwtvkjaqpyekmkw = true;
	string obaexb = "agbzmjwwpggfpssi";
	bool rzgrfupucnxub = true;
	if (true != true) {
		int yngxkiuth;
		for (yngxkiuth = 69; yngxkiuth > 0; yngxkiuth--) {
			continue;
		}
	}
	if (true != true) {
		int kpp;
		for (kpp = 81; kpp > 0; kpp--) {
			continue;
		}
	}
	return 79495;
}

void wmxygcw::fxyrzplxci(bool qkhcapslya, bool sfljnrzllds, string rncvk, int ykiwzk, bool ptlldsw) {
	double fqinntptomhhii = 30349;
	int akfpkbfijac = 201;
	double wypiptnwkhsoe = 43906;
	bool vcihgzrdosu = false;
	bool gxypxehbwxoetvd = false;
	double frnpmzwmu = 45005;
	double mxbgcpbye = 71654;
	double qhlofal = 16454;
	string flwoxnwmvaczdyx = "yeuuqhibumuuivtbiodwqkhsuxmtmyjwwzyiqwxvuzlqzwrpnmbqqznqorazvjzzcccczczklsai";

}

wmxygcw::wmxygcw() {
	this->lbftntxjfunwzbijdtfa(string("jiedk"), true, false, false, true, false, string("oszbcvbryaccvmgfwuedysothbmmcoeedsqjigvobmeoiglqlwqzzvvpbgotmvx"), 4971);
	this->nfheganosavoqvxuujxcdw(string("oxtqqorbokrqfyrnxmkdzqxygkejjlvwdplduggumfygmklvoumtqrqghtwhjbydsnejancewnmlaszheboeozvdjkaokamwbv"), 3929, string("dacjwgnqofluolluuwyyfnnrtwnulkkeivcduyfjlakggbhuitifdxszqgssqbvbwslktcrrysyuitgp"), 20693);
	this->jrxsteicvceglxj();
	this->uwldpxtjpgfauywuyiky(string("srvxpskjglrwvktgmbclwjbfjadqzkebbmnzppfijbxvl"), string("amfbujgur"), 48134, false, string("vgklxxnpfidaqgbzqhyjjumjpou"), 1922, 31231, false, string("mzsmalzigerfvenwmxnhairptwkbfezazwjznfojircikbtzxslxrbrazbxuofbjzwna"));
	this->tyisojxtruwckzyax(16982, false, 4893, 11495, 5037, 19371, 18494, true, 18487);
	this->gisvwusyqgma(2763);
	this->fxyrzplxci(false, true, string("bwlzbuzxhthvidmyhjiysuuumjhslijrastdysfrplmkqprrvbteqbvhoyjzjyevxhevhqqaaxiaaru"), 44, false);
	this->dpvelykxsysbfkreqwxmos(string("uujrtuxbasqpqfjtcjoymydtqnv"), 5736, 3019, 88949, 33595, string("lcf"));
	this->boonoauwtalpjqcuqhmhgfg(string("pycu"), string("vosdmqmairyopjuyaaqnbatmenzbrygebejxwfeafgagxlvrdhzouwkehcyva"), 6343, 1350);
	this->nrkyknynbtmqdjprmlm(false, 30, 18829, 3451, 35240, false, 1154, true, 3646, 2922);
	this->jgvthihhacgybwmwaxlwrqpf();
	this->sjvwsxobspxreewtd(1030, false, 15074, 7300, true, 890, false, true, false, true);
	this->bfqqckhufe(true, false, true);
	this->devcfeehlqvzkkqgxaiuyuipk(6122, 1012, string("kiwgpupcdgihdtpzmgdmggdaubhxzxhmrblxsccjlpkbwviqiwbcwwzlodgdkuwdbatxrqvngvyfwzqfonzahfvejjinwn"), string("luykamdrjzzsebmontdlzrefesmpxnwezirmmdzmguktynivvcdefuhohdqbadjrhiklrwxsokzlfpmnwrjloeyqtmzirzgaf"), true, true);
	this->tdcskjavvguoco(8539, string("bawprmhumdtubnxixteqcdqwftullxazicysyknainxtdjagojslgtgzvvglhvzsxqtzdbfhtt"), false);
	this->guudemqbvazymgcau();
	this->sgdnrskjvxigzpqgx(2207, false);
	this->uefqrnhtbzpjxcfgrvqc(1662, 1090, 7689, string("lvsdtdwvrulymxtbaklbjlzizgleihnvifirbkjajjvtnvnvnpszpbiwfoiajvqbrh"));
	this->ggcxzkvtas(true, false, string("qnvcwasyhlbuwhzqwwzfyunuptagdzpclxjihf"), string("swbiahunqzbvhzvspafmbeiihdtythxomfqrecfxqbkhktmwvokysxiqjxqokptsxmeyxllgehbyynpqnaxgipuagej"), 15239);
	this->vklnkzjtqwercvajnbmmh(1609, false, 5408, 43048);
	this->scaubdqugjtxypihfvv(string("glynhqpnbg"), 2036, 41763, 5726);
	this->llnhwqculhmcfogep(27511, 12433, 2185, false, 2030, 13150);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class bvhvdqd {
public:
	double zbkruyfeauu;
	double rlozbgsjtj;
	int oyjycn;
	bvhvdqd();
	bool cvgagspvpuomtenwedjs(double czjdcrmz, bool hlnkjxwg, string evcvnwnxtxxm, bool mjnkqqbrxxaigbr, bool rqxmkxcw);
	int qzbbefhdklspqin(string ozrbbpvuoezyl, double fdhgkranfbpc, double xqzzpwoud, bool wnnybvgzgmrz, int tyyverzjxzcsrxg, string nhmxinpzrsqnm, int xkvtabwmlmjatp, bool bdeqayvp);
	void btobbblnzevxfaanlezs(double zfjcld, int pnesxkvjisks, double hjyvwpctvkqercr, bool auieoktiiyupazl);
	double mxjzldkzryqim(string hwgeb, bool aglsphnfkftes, double cxfuxyvvshudhtv, string uvyffp, double qjzywrmmopgpa, int ruvsgxl, double ddudv, int koalofkash);

protected:
	double cebbewtskao;
	int dagbdkcupepnuxg;
	string inxeoqumryul;
	bool ifgccrosstrwst;

	string yzupeovhquktsmwcheo();
	void fbdhlblwegwregslfqq(string iuacbuw, string hbghnjzbq, double xhfpgdeiqeubq, string dhkjnxyesw, double sdxjmdqfjzxx, int wzaevp);

private:
	double tvlfjtlsydqo;

	int kcdtvnbipkwkruayswhc(double yxwddppnjwnzfit);
	double umuxgwyodnvxhyj(string cmnztq, bool twypsp, double dxamqomwrmaa, int gdfyrcghylef);
	void cgajjawobw(string dfdfdbdpk, string mhaaunltf, bool hbtystmxczfrfss);
	void bkahomvxhyukepaz(int qoshutgfnkpaye, string odmpxzahdy, double zfadymomw, string triaavafyxej, bool uibojqhueb, int uamncll, string erhylpiugur, int jfhasyclnjlw, int gizzor);
	string obicxqhxkpxyjvysptafg(bool jvlvbzllytepq, int wfkajzodwtknbbr);
	void rpgmzuwmhumshsv(double ejtkekf, bool hkvtdqmkcfrw);
	double udlwqsrklookuyohd(string dzlhddkchyi);
	double dsxnnonihxlxfvayqrymm(string xkhwcxprgisent, int xmavektibdqpfo);
	int fulqozwvegttbpff(bool ozihid);
	double sswfxskmbstxfrpggbrz(int gefsovfwkb);

};


int bvhvdqd::kcdtvnbipkwkruayswhc(double yxwddppnjwnzfit) {
	double asqcywobbmn = 5808;
	int dwshs = 8747;
	if (5808 != 5808) {
		int ufscnw;
		for (ufscnw = 83; ufscnw > 0; ufscnw--) {
			continue;
		}
	}
	if (8747 != 8747) {
		int ca;
		for (ca = 61; ca > 0; ca--) {
			continue;
		}
	}
	if (8747 != 8747) {
		int bv;
		for (bv = 16; bv > 0; bv--) {
			continue;
		}
	}
	if (5808 != 5808) {
		int rilcfg;
		for (rilcfg = 21; rilcfg > 0; rilcfg--) {
			continue;
		}
	}
	return 50725;
}

double bvhvdqd::umuxgwyodnvxhyj(string cmnztq, bool twypsp, double dxamqomwrmaa, int gdfyrcghylef) {
	double mojmusneagvo = 32306;
	int wsxqzjwo = 294;
	int ueztypchl = 4523;
	double ltxavcxep = 18097;
	bool ffdgj = false;
	int cqdaslf = 1334;
	int yjshpfvqyznzrjz = 1273;
	string wqgzwezsajjzcjx = "zgoniqxetbwqygyrbxebkvnvbqwjspncbcrildhxtfzwoahlseeniettsgfnrrvglgwbrsvpjleuqw";
	double vhoazqmj = 60954;
	string bcblhkfxeiwkero = "rxeldoomauqepiwiyfpxufodttudnyecwwukfayomweufpbanbugthh";
	return 99040;
}

void bvhvdqd::cgajjawobw(string dfdfdbdpk, string mhaaunltf, bool hbtystmxczfrfss) {
	string eecllactgmftghd = "gbaoqjfticpnld";
	if (string("gbaoqjfticpnld") == string("gbaoqjfticpnld")) {
		int kagwjhoo;
		for (kagwjhoo = 5; kagwjhoo > 0; kagwjhoo--) {
			continue;
		}
	}

}

void bvhvdqd::bkahomvxhyukepaz(int qoshutgfnkpaye, string odmpxzahdy, double zfadymomw, string triaavafyxej, bool uibojqhueb, int uamncll, string erhylpiugur, int jfhasyclnjlw, int gizzor) {

}

string bvhvdqd::obicxqhxkpxyjvysptafg(bool jvlvbzllytepq, int wfkajzodwtknbbr) {
	double zjquksvrqjm = 17736;
	string pjlkyhgepg = "jfyblzvgpyysjhpdjonblgdrfdzyswshuietuaiazpllteukfmzpzpxedmwanhadcafblcfydrlsgpiuaruan";
	bool sswfvlrs = true;
	string mcfuybxeqkupzcp = "uisvpvgozlhfxbuftsdpchlaulueqjvtbq";
	int qfsikuensbf = 2976;
	if (true != true) {
		int vpiapkx;
		for (vpiapkx = 89; vpiapkx > 0; vpiapkx--) {
			continue;
		}
	}
	return string("n");
}

void bvhvdqd::rpgmzuwmhumshsv(double ejtkekf, bool hkvtdqmkcfrw) {
	bool rwwidrfz = true;
	int sxbbmitzshwnisl = 1187;
	string habtr = "yfamvtgtpvabgycrsfatrfvp";
	double ortffbase = 14729;
	bool huydhvhfpblaoo = true;
	bool ozrfst = true;
	bool pvulvvrhmzu = true;
	string gxaomnk = "xiqjpytoxyaohmetctxsbkodzjjgodfwnwvvchntzuodnhkpgxhcwmcsupubyerrournnqtnonomezapsblkbis";
	string awvimbuuefwirx = "manigmqrdnayxfojbdcypjnvqbbmhijodqkalfdfxkzogqpfbuopmyzlipbwcpbomttekwgitfd";
	if (true != true) {
		int sbgtzyidcw;
		for (sbgtzyidcw = 33; sbgtzyidcw > 0; sbgtzyidcw--) {
			continue;
		}
	}
	if (string("manigmqrdnayxfojbdcypjnvqbbmhijodqkalfdfxkzogqpfbuopmyzlipbwcpbomttekwgitfd") == string("manigmqrdnayxfojbdcypjnvqbbmhijodqkalfdfxkzogqpfbuopmyzlipbwcpbomttekwgitfd")) {
		int fisy;
		for (fisy = 87; fisy > 0; fisy--) {
			continue;
		}
	}
	if (string("manigmqrdnayxfojbdcypjnvqbbmhijodqkalfdfxkzogqpfbuopmyzlipbwcpbomttekwgitfd") == string("manigmqrdnayxfojbdcypjnvqbbmhijodqkalfdfxkzogqpfbuopmyzlipbwcpbomttekwgitfd")) {
		int drmcwfsbe;
		for (drmcwfsbe = 75; drmcwfsbe > 0; drmcwfsbe--) {
			continue;
		}
	}

}

double bvhvdqd::udlwqsrklookuyohd(string dzlhddkchyi) {
	int nmqtcthqiwznyzr = 9676;
	int nizuq = 3040;
	if (3040 == 3040) {
		int ushuycv;
		for (ushuycv = 78; ushuycv > 0; ushuycv--) {
			continue;
		}
	}
	if (9676 == 9676) {
		int vx;
		for (vx = 42; vx > 0; vx--) {
			continue;
		}
	}
	if (9676 == 9676) {
		int luzjdut;
		for (luzjdut = 68; luzjdut > 0; luzjdut--) {
			continue;
		}
	}
	if (3040 == 3040) {
		int ttin;
		for (ttin = 63; ttin > 0; ttin--) {
			continue;
		}
	}
	if (9676 == 9676) {
		int gw;
		for (gw = 2; gw > 0; gw--) {
			continue;
		}
	}
	return 97277;
}

double bvhvdqd::dsxnnonihxlxfvayqrymm(string xkhwcxprgisent, int xmavektibdqpfo) {
	return 35117;
}

int bvhvdqd::fulqozwvegttbpff(bool ozihid) {
	double sotcekcjhb = 24930;
	int jmjpejtinhqty = 4637;
	double ypohbnk = 32381;
	int tosyrjlu = 593;
	double xfvweuz = 65169;
	double vphwanidzkeykls = 39816;
	string muiwhhwam = "evzeskdovwsiyxknwxutrigaomajgdqkhcnzlzjuvqyi";
	bool vlpkuyv = false;
	int ktjqjsiicap = 1415;
	double uiplrqwdhmrf = 4834;
	if (32381 == 32381) {
		int gwbaeblovi;
		for (gwbaeblovi = 20; gwbaeblovi > 0; gwbaeblovi--) {
			continue;
		}
	}
	return 90150;
}

double bvhvdqd::sswfxskmbstxfrpggbrz(int gefsovfwkb) {
	bool ilfwspqwmhg = true;
	string oklgsmolxu = "mwrosmlafha";
	if (true == true) {
		int usjmyfu;
		for (usjmyfu = 82; usjmyfu > 0; usjmyfu--) {
			continue;
		}
	}
	return 72976;
}

string bvhvdqd::yzupeovhquktsmwcheo() {
	string ufniua = "pzpvhrynzurnzmvi";
	int sdiyhatrplvrop = 1111;
	string meautxkdli = "ykvp";
	double ezieiei = 41805;
	if (1111 != 1111) {
		int jqie;
		for (jqie = 20; jqie > 0; jqie--) {
			continue;
		}
	}
	if (string("ykvp") != string("ykvp")) {
		int hvpgy;
		for (hvpgy = 86; hvpgy > 0; hvpgy--) {
			continue;
		}
	}
	if (string("pzpvhrynzurnzmvi") == string("pzpvhrynzurnzmvi")) {
		int pqeckas;
		for (pqeckas = 55; pqeckas > 0; pqeckas--) {
			continue;
		}
	}
	if (41805 != 41805) {
		int dfj;
		for (dfj = 81; dfj > 0; dfj--) {
			continue;
		}
	}
	if (string("ykvp") != string("ykvp")) {
		int aaigysjrpi;
		for (aaigysjrpi = 5; aaigysjrpi > 0; aaigysjrpi--) {
			continue;
		}
	}
	return string("ivpbzxtottosnon");
}

void bvhvdqd::fbdhlblwegwregslfqq(string iuacbuw, string hbghnjzbq, double xhfpgdeiqeubq, string dhkjnxyesw, double sdxjmdqfjzxx, int wzaevp) {
	int frrryii = 4112;
	string wbijrpe = "jettpjpcqgnsyuwufcmotw";
	string moyalpoggbtg = "kcnlcsxlacuvulnmsrndpcegdqunyw";
	double fqecyam = 903;
	if (string("kcnlcsxlacuvulnmsrndpcegdqunyw") == string("kcnlcsxlacuvulnmsrndpcegdqunyw")) {
		int mvwgsgw;
		for (mvwgsgw = 4; mvwgsgw > 0; mvwgsgw--) {
			continue;
		}
	}
	if (string("kcnlcsxlacuvulnmsrndpcegdqunyw") != string("kcnlcsxlacuvulnmsrndpcegdqunyw")) {
		int jcioi;
		for (jcioi = 99; jcioi > 0; jcioi--) {
			continue;
		}
	}
	if (string("kcnlcsxlacuvulnmsrndpcegdqunyw") == string("kcnlcsxlacuvulnmsrndpcegdqunyw")) {
		int urzzg;
		for (urzzg = 9; urzzg > 0; urzzg--) {
			continue;
		}
	}
	if (string("jettpjpcqgnsyuwufcmotw") != string("jettpjpcqgnsyuwufcmotw")) {
		int jdjz;
		for (jdjz = 87; jdjz > 0; jdjz--) {
			continue;
		}
	}

}

bool bvhvdqd::cvgagspvpuomtenwedjs(double czjdcrmz, bool hlnkjxwg, string evcvnwnxtxxm, bool mjnkqqbrxxaigbr, bool rqxmkxcw) {
	double kokrvdbe = 4266;
	double gkvreqlgehdfx = 11063;
	string nhjqprkowkcanee = "sudonndwkzmmyyyfhccdqqlcvbugsjlwkqdcpdavaeeyfmitncnabgayarpldx";
	string imlgrkrflpb = "u";
	int ryugipvvjlnnw = 1250;
	if (11063 == 11063) {
		int ohbboxpunn;
		for (ohbboxpunn = 37; ohbboxpunn > 0; ohbboxpunn--) {
			continue;
		}
	}
	return true;
}

int bvhvdqd::qzbbefhdklspqin(string ozrbbpvuoezyl, double fdhgkranfbpc, double xqzzpwoud, bool wnnybvgzgmrz, int tyyverzjxzcsrxg, string nhmxinpzrsqnm, int xkvtabwmlmjatp, bool bdeqayvp) {
	bool qhjtcfynzbhic = true;
	bool ibmcfzoyworhtgh = true;
	string rvzbnc = "uughczklghqgwtwponcxyek";
	string brahsi = "ukpimttjlhkqydhvedvpygyczkhifxvfzunrmcddnhbwiyvteltpmhcwyjjmtdbbmdnlddyfbsfzedjvuijmrwkoexmcsxaoc";
	if (string("uughczklghqgwtwponcxyek") == string("uughczklghqgwtwponcxyek")) {
		int rr;
		for (rr = 64; rr > 0; rr--) {
			continue;
		}
	}
	return 88658;
}

void bvhvdqd::btobbblnzevxfaanlezs(double zfjcld, int pnesxkvjisks, double hjyvwpctvkqercr, bool auieoktiiyupazl) {
	bool dxyrzaxkoxi = false;
	bool cpoxk = true;
	bool nhxim = false;
	int wjndysmdjmk = 2516;
	int stcdugztphzksk = 4760;
	int kebpkfcerkp = 169;
	int vksqpedpeoh = 939;
	double zubgccsplcr = 33314;
	string nomfiildzn = "dkcgdaldyogvgmfupiordhoggwxuficowhecfdqjkqchitcwwyxyopcgjdlkmsbrhutsuztevwbzrodkaxvruw";
	if (169 == 169) {
		int orwcsrzy;
		for (orwcsrzy = 47; orwcsrzy > 0; orwcsrzy--) {
			continue;
		}
	}
	if (4760 != 4760) {
		int opatg;
		for (opatg = 57; opatg > 0; opatg--) {
			continue;
		}
	}
	if (169 == 169) {
		int natfgwtm;
		for (natfgwtm = 79; natfgwtm > 0; natfgwtm--) {
			continue;
		}
	}
	if (string("dkcgdaldyogvgmfupiordhoggwxuficowhecfdqjkqchitcwwyxyopcgjdlkmsbrhutsuztevwbzrodkaxvruw") == string("dkcgdaldyogvgmfupiordhoggwxuficowhecfdqjkqchitcwwyxyopcgjdlkmsbrhutsuztevwbzrodkaxvruw")) {
		int pndxw;
		for (pndxw = 27; pndxw > 0; pndxw--) {
			continue;
		}
	}

}

double bvhvdqd::mxjzldkzryqim(string hwgeb, bool aglsphnfkftes, double cxfuxyvvshudhtv, string uvyffp, double qjzywrmmopgpa, int ruvsgxl, double ddudv, int koalofkash) {
	double bvukli = 20808;
	bool nzwosqegqmhwx = false;
	int zbonnqqo = 1316;
	string jrujjahklqkbwjv = "xhqvxwdzorsssmygsaeuza";
	double mhdjlridpi = 24165;
	double qivvlpcxvakwz = 6351;
	if (24165 != 24165) {
		int ftqebztxtz;
		for (ftqebztxtz = 47; ftqebztxtz > 0; ftqebztxtz--) {
			continue;
		}
	}
	if (1316 != 1316) {
		int jkfafisqh;
		for (jkfafisqh = 77; jkfafisqh > 0; jkfafisqh--) {
			continue;
		}
	}
	if (1316 != 1316) {
		int xnykzfbl;
		for (xnykzfbl = 77; xnykzfbl > 0; xnykzfbl--) {
			continue;
		}
	}
	if (false != false) {
		int qqaxf;
		for (qqaxf = 65; qqaxf > 0; qqaxf--) {
			continue;
		}
	}
	return 13832;
}

bvhvdqd::bvhvdqd() {
	this->cvgagspvpuomtenwedjs(1847, false, string("gltfstklccfioptonzxlhywra"), true, true);
	this->qzbbefhdklspqin(string("xdjeyuhuyowfzvodnicutmbhqusohlw"), 30703, 2655, false, 7098, string("mklxasanxfskaovfgambwdftemebzmtjmgfxrjlgyibrxqxiivkeyosnyfckmjcqvpu"), 3120, true);
	this->btobbblnzevxfaanlezs(24209, 589, 21171, false);
	this->mxjzldkzryqim(string("pxxxinubxkqmjccxunjxxhllewawrdylegiwdnyzzwmhg"), false, 13030, string("jouzky"), 57075, 4304, 22729, 3148);
	this->yzupeovhquktsmwcheo();
	this->fbdhlblwegwregslfqq(string("hcgxjkmavcuizvpaazwkwoeoikgbmzqfqwgkkgutvtzeuubskncdvyjrrmeuyln"), string("dxotvqwhftpsvfondnsadyvkdkopgemjayhqatzbahkwzjqbtlqqip"), 17642, string("drwvukimquslnozbhgtydmx"), 92305, 4124);
	this->kcdtvnbipkwkruayswhc(23041);
	this->umuxgwyodnvxhyj(string("mhnzyowqqjhrpuvxbspoprvctxvfctorfwrklowxkrjmjtgwkhkmbynelfeaopmpkqxumvvcwxmgfhpqrphraqiicuxia"), false, 17457, 981);
	this->cgajjawobw(string("cgulmzsxryeghkqflkzobcmf"), string("rsbnmdgpsvfaenvmwmekyxptznjyqzdmfenuzgytnbgcoqqgoutyzcfdeqgjzdvzajvvaliifxzzf"), true);
	this->bkahomvxhyukepaz(3013, string("dxgeiulochfafvsizfzcjpsrhikmlvkyokzglzxmwfcxaxsoubqaft"), 40142, string("uphqcyfgxatijrefuutezzsbcondkhhempciymernazkjfngeirbrozksekzywwkcqjwzcihltoagisjenymxoilcqafutwuipe"), true, 6504, string("nwwbllvqlqgvofqoupiukdsqwatlcdwxwgpjq"), 2661, 3839);
	this->obicxqhxkpxyjvysptafg(false, 692);
	this->rpgmzuwmhumshsv(39590, false);
	this->udlwqsrklookuyohd(string("tzwhzbnffswptllkqjnpbgodaflpazhgzdmwceffvwifecaqmjyssmispnzaxerezxlbubnkfypavflnnv"));
	this->dsxnnonihxlxfvayqrymm(string("cnyxcailuwrfvvj"), 363);
	this->fulqozwvegttbpff(true);
	this->sswfxskmbstxfrpggbrz(6455);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class jduqofz {
public:
	double mccllgqnjt;
	jduqofz();
	void kpfmampnzbjjqmzjmvgwow(bool vceqaioz, int gkvorehcgexfs, int yscrzvzyqoy, double ouptjkuchmida, double nuylsbnevyu, bool sqsrjjqzswkamk, double nqamhjtu, string fpugvwjmvkmtwd, string htmnvoyj);
	double bnhggcvbpldfptybrrfv(string zzlijmqal, int dveaq, int zhledifgy, bool hehbxtqvuqt, bool rypjfkvftjkx, double gmobdb, double ejrbrhq);
	bool nehdqcmuriuxp(double lcccddkoqbbhjp, string hkigrpktuyvhj, double hkfkmklof, bool yzvarqkjfpwsvry);
	bool fngmpfeildl(string jdnoqy, bool tgabop);
	int sqeverjnjkpyvetodjjcxx(string wmegyew, bool wjdqiumgsr, bool qyymeuaobfbed, string xnyhvlkvgv, double bavlodqpyg, double ytivqajqhhugx, double nctpgwnqhqqaw);
	bool bqjyfzlfrxj(bool lwnvnuqfpocijgy, bool uzjhwqiafb, double numumkiqtmfitwe, int xlehoxdzysvd, string ochraytuexuxd, bool jvwyx, bool msptvndq, int jbjnaqwp, string jdgogcvvzmhiema, double cgsukkyixkbnpt);
	bool webfpwikbz(bool wunagnetcdacw, string ekgdhgyujflpzam, bool qafzs, int ttiwv, double zduffyzydjgg, int puggpfmdxylqscy, int dbkvdhhon);

protected:
	int svonyinkmimhczw;

	int ftjxolxdivpoz(bool imousitgy, double kexxbycfpflse, int krughtjrko, double ivrfvsalztflp, string ndtir, int eknvpgkisx, bool imgqbstfz, bool hcquh);
	double kticxhpilywsdpwhotlxwuni(string fpossmwad, bool ojjzfifuycmam);
	string jbnfslkjtqpggaquzqyjz();
	void xsyfiiziwsv(int ikamv);
	string nxpwzgqvkthtnaepehmhffzq(bool ajmgbu, int pcjap, double xquykjwllmer, int afkmd, double hkdfzysehhrxm, bool esnpabh);
	void xefffnqmgubcwu(string lssbc, bool zddxdvxlwz, int ayttaenfuqsm);
	bool itgopjwpidcsbwb(double lakxewskfvzgz, double hvupwyqmaxaeckw, bool mnaostaeswrvkmf);
	void ktutmtyujjrivaebbufslfmi(int rxdvcbnqiswxwfz, bool yjokiojrvaqbrok, bool iivbzenahlfpkgb, int slyqzu, double rttxxfjwoxo, double xhtbaatnkhg, int nwmexaifp, int eaflrv, bool qtzaqgyimquifra, int wvyms);
	string ngunpxorsihlbeeannjvxxnrv(int guhtbfqweczge, bool hvwznyny, string cxwbnv, bool eccrogowdhb, int etnlyn, string dyugwlx, double aebkanmsnblfp, int mmuexljjcpnke);
	int hhfqjrcslngku(bool jmvogycwec, int mepcioqoemh, bool naahemylvi, int sivxjk, double ztqffhsfl, string wykkcazporhw, string blsvlivjmnhfw, double pjoaimkmma, string bvpmrphiillufa, bool qmqfounzdrpitt);

private:
	bool eodzgkmqomokprf;
	bool ydyoqyw;
	bool ziulywzkgxz;

	int qzywszysdcyfamtaepbxy(string qmnrerrakpzh, bool yttyjryaiyiv, double egtehva, string lcvmt, string vmjkgarkrtfuv, int xdqud, int qvpyurk);
	double xweigjkpgwqafsi(int vterdiryhqk, double qhfsj, string xkzfhcpmovcl, int ythbnccp, string iskyk, bool gajrrnoyui, string ljmaykdiqwgo);
	string ugdcykhxoy();
	double fbiqhdtquegaemj(bool gdqbakbavwotmbd, bool rpytwnahckixfsu, double citbecdyy);
	int zadyqqvkgjim(double evuawhzneemd, string jhpzgqvf, string xgboumh, string vpfxcvajwjfhr, int ecjlcksxtvnuugr);

};


int jduqofz::qzywszysdcyfamtaepbxy(string qmnrerrakpzh, bool yttyjryaiyiv, double egtehva, string lcvmt, string vmjkgarkrtfuv, int xdqud, int qvpyurk) {
	bool hmmauyzv = true;
	double ivalmfca = 26440;
	int lsmdljpdpbjcyy = 4723;
	double xouygkteoohvk = 43000;
	double osxhb = 3996;
	int kazskca = 5389;
	string sfmnluujrqtrlnh = "njscsyaeyxvuzwtglqykxhdllzidxkiqbndqexhporrbilbdeynzievcnovitehzhyggsfvtsbslgeiunwfsjfem";
	string javysnjlbdxzzpr = "xrhbtnextpfodmohncvadqedkpvgmjbiswuhk";
	if (43000 == 43000) {
		int rtz;
		for (rtz = 20; rtz > 0; rtz--) {
			continue;
		}
	}
	if (string("njscsyaeyxvuzwtglqykxhdllzidxkiqbndqexhporrbilbdeynzievcnovitehzhyggsfvtsbslgeiunwfsjfem") == string("njscsyaeyxvuzwtglqykxhdllzidxkiqbndqexhporrbilbdeynzievcnovitehzhyggsfvtsbslgeiunwfsjfem")) {
		int ytm;
		for (ytm = 79; ytm > 0; ytm--) {
			continue;
		}
	}
	if (5389 != 5389) {
		int euzgj;
		for (euzgj = 17; euzgj > 0; euzgj--) {
			continue;
		}
	}
	if (5389 != 5389) {
		int mbgy;
		for (mbgy = 98; mbgy > 0; mbgy--) {
			continue;
		}
	}
	if (3996 == 3996) {
		int syxrfdl;
		for (syxrfdl = 7; syxrfdl > 0; syxrfdl--) {
			continue;
		}
	}
	return 31800;
}

double jduqofz::xweigjkpgwqafsi(int vterdiryhqk, double qhfsj, string xkzfhcpmovcl, int ythbnccp, string iskyk, bool gajrrnoyui, string ljmaykdiqwgo) {
	string wgmaxssd = "wybwapjatvbxfjhmbdahaublurobmmctbifuzazqnmukmxcbufjkznndvgazxmffirsdppdpfigcdpeix";
	double nvahda = 79706;
	string xjxsgmz = "rwssoxfcsebcibircfzjglv";
	string zbzvguslfc = "kgydppvyrqiaznfnxsccrfaoxeiubzcgcswzfvmh";
	string uznfznf = "uzdslshnnlxgdnhpftboejbjmeqldfbgsakocfiqwavijrdjflhoivvtypbnmb";
	if (string("kgydppvyrqiaznfnxsccrfaoxeiubzcgcswzfvmh") == string("kgydppvyrqiaznfnxsccrfaoxeiubzcgcswzfvmh")) {
		int cx;
		for (cx = 73; cx > 0; cx--) {
			continue;
		}
	}
	if (string("wybwapjatvbxfjhmbdahaublurobmmctbifuzazqnmukmxcbufjkznndvgazxmffirsdppdpfigcdpeix") == string("wybwapjatvbxfjhmbdahaublurobmmctbifuzazqnmukmxcbufjkznndvgazxmffirsdppdpfigcdpeix")) {
		int ave;
		for (ave = 70; ave > 0; ave--) {
			continue;
		}
	}
	return 22651;
}

string jduqofz::ugdcykhxoy() {
	string hbsihkkjhmj = "bhqbwinpzntnpsahrojylhurlj";
	bool avkmk = true;
	double flbvmsilrpb = 29154;
	bool mvrueuvwlg = false;
	string xwriwmfozbf = "mexhgvjkykgsbfngjrtmddjadcomyttxobupbhhflmdnjdivmgwcputptamvjduhmmjugdyldikcpbvtzskilcfr";
	int pumxnxam = 828;
	int qldqebmwpohqf = 3764;
	string pqnzq = "sfpnuurpesxixqnzhicmvhmchymnmwzjzpekxvbdotoxxsuwrjqbstpmoxqjylkujotpdimbuonncuiimipcmdbrrxmceaeaqch";
	bool svbyjqzgdqa = true;
	return string("dsebu");
}

double jduqofz::fbiqhdtquegaemj(bool gdqbakbavwotmbd, bool rpytwnahckixfsu, double citbecdyy) {
	string xmgompglioafybs = "vrywovpvaeayhcffnnmlbkmctrltxisbyuuyhvqniadfepgkzhooylomhmvnt";
	if (string("vrywovpvaeayhcffnnmlbkmctrltxisbyuuyhvqniadfepgkzhooylomhmvnt") == string("vrywovpvaeayhcffnnmlbkmctrltxisbyuuyhvqniadfepgkzhooylomhmvnt")) {
		int mm;
		for (mm = 63; mm > 0; mm--) {
			continue;
		}
	}
	return 60874;
}

int jduqofz::zadyqqvkgjim(double evuawhzneemd, string jhpzgqvf, string xgboumh, string vpfxcvajwjfhr, int ecjlcksxtvnuugr) {
	string qglfysjnejqo = "vmewa";
	int faslk = 4126;
	int cqbmhrxnwelji = 6583;
	if (4126 != 4126) {
		int qjwezd;
		for (qjwezd = 53; qjwezd > 0; qjwezd--) {
			continue;
		}
	}
	if (string("vmewa") != string("vmewa")) {
		int vflld;
		for (vflld = 64; vflld > 0; vflld--) {
			continue;
		}
	}
	if (4126 != 4126) {
		int ixaymsxagr;
		for (ixaymsxagr = 89; ixaymsxagr > 0; ixaymsxagr--) {
			continue;
		}
	}
	if (4126 != 4126) {
		int cm;
		for (cm = 17; cm > 0; cm--) {
			continue;
		}
	}
	return 64874;
}

int jduqofz::ftjxolxdivpoz(bool imousitgy, double kexxbycfpflse, int krughtjrko, double ivrfvsalztflp, string ndtir, int eknvpgkisx, bool imgqbstfz, bool hcquh) {
	bool uzqtq = false;
	return 24322;
}

double jduqofz::kticxhpilywsdpwhotlxwuni(string fpossmwad, bool ojjzfifuycmam) {
	string aqnlnfsgss = "khqqgpynegmzqjnktmcpnnzjbplldyzcqntbuzjob";
	int ikyggfxtypawhf = 1612;
	if (string("khqqgpynegmzqjnktmcpnnzjbplldyzcqntbuzjob") != string("khqqgpynegmzqjnktmcpnnzjbplldyzcqntbuzjob")) {
		int svaxfbyln;
		for (svaxfbyln = 53; svaxfbyln > 0; svaxfbyln--) {
			continue;
		}
	}
	return 43212;
}

string jduqofz::jbnfslkjtqpggaquzqyjz() {
	int nqvtlb = 7339;
	string bzfqjxrj = "idauvhciacpqfjtkewwqopiqcsqvamcuowfphqijfjaiuposyuhwwakhyavhstaszlbxqdkcdytfkozk";
	if (7339 != 7339) {
		int nocrafbeb;
		for (nocrafbeb = 11; nocrafbeb > 0; nocrafbeb--) {
			continue;
		}
	}
	if (7339 == 7339) {
		int lq;
		for (lq = 61; lq > 0; lq--) {
			continue;
		}
	}
	return string("zvpiwalgd");
}

void jduqofz::xsyfiiziwsv(int ikamv) {
	string rkkohvbt = "rhjqrzokfljnltbrsmcpingubqrejskdqbjkozhxhobhfqafjtmyzamsihjzrnxkyvwnpjjkineeenvdcvfgd";
	string bvcnxzgw = "bbxkakuybgqnwfwwaoxtgbhussbedanqcnzljxw";
	int xhcsztaj = 2662;
	string xykerdlpicq = "eljaxjvafamxbehsbxncrf";
	string nckvupoujkd = "zputwerdigztlyhcelnxsszbujajsavdydofjrwewcajrztxgmnsphhxzlpqzcmhtfrfblvbznxcgzoarjadmzhcls";
	double qntonpo = 20806;
	int hyzjvrygffm = 3813;
	if (string("zputwerdigztlyhcelnxsszbujajsavdydofjrwewcajrztxgmnsphhxzlpqzcmhtfrfblvbznxcgzoarjadmzhcls") == string("zputwerdigztlyhcelnxsszbujajsavdydofjrwewcajrztxgmnsphhxzlpqzcmhtfrfblvbznxcgzoarjadmzhcls")) {
		int frm;
		for (frm = 41; frm > 0; frm--) {
			continue;
		}
	}
	if (string("bbxkakuybgqnwfwwaoxtgbhussbedanqcnzljxw") == string("bbxkakuybgqnwfwwaoxtgbhussbedanqcnzljxw")) {
		int nz;
		for (nz = 89; nz > 0; nz--) {
			continue;
		}
	}
	if (2662 != 2662) {
		int ugvabssi;
		for (ugvabssi = 67; ugvabssi > 0; ugvabssi--) {
			continue;
		}
	}
	if (20806 == 20806) {
		int fpscmx;
		for (fpscmx = 64; fpscmx > 0; fpscmx--) {
			continue;
		}
	}
	if (20806 == 20806) {
		int wgbrnpi;
		for (wgbrnpi = 89; wgbrnpi > 0; wgbrnpi--) {
			continue;
		}
	}

}

string jduqofz::nxpwzgqvkthtnaepehmhffzq(bool ajmgbu, int pcjap, double xquykjwllmer, int afkmd, double hkdfzysehhrxm, bool esnpabh) {
	string kxgdukioq = "lequapdukeweyjeykdbldggqhzdidxkxdasiccppgcgautcbeduqzejqxp";
	double dxxfdmjbndhso = 1262;
	int eofoyhtrp = 1958;
	string wmprgtnhryadhxh = "ioukvhdyidiuofbaubjpabbpgptuukzxuqiuxoooxquko";
	double wvuvclnwgsmjmd = 18084;
	string quvsfxmaeufzgv = "ymqdgmmptdiofuorillhdricbco";
	return string("iudjrv");
}

void jduqofz::xefffnqmgubcwu(string lssbc, bool zddxdvxlwz, int ayttaenfuqsm) {

}

bool jduqofz::itgopjwpidcsbwb(double lakxewskfvzgz, double hvupwyqmaxaeckw, bool mnaostaeswrvkmf) {
	bool mhumwnuplbk = true;
	double izvjppw = 21134;
	return true;
}

void jduqofz::ktutmtyujjrivaebbufslfmi(int rxdvcbnqiswxwfz, bool yjokiojrvaqbrok, bool iivbzenahlfpkgb, int slyqzu, double rttxxfjwoxo, double xhtbaatnkhg, int nwmexaifp, int eaflrv, bool qtzaqgyimquifra, int wvyms) {

}

string jduqofz::ngunpxorsihlbeeannjvxxnrv(int guhtbfqweczge, bool hvwznyny, string cxwbnv, bool eccrogowdhb, int etnlyn, string dyugwlx, double aebkanmsnblfp, int mmuexljjcpnke) {
	bool bzwemkbwoylqhze = false;
	double lgkbn = 11822;
	string naezzbatdumfgf = "ntyzvoskusbzlmyscjtdboftjzzohhbtwnvpdjhuzaibpheokuiqjhbqyfavvscjgshfywtqhunxfaa";
	string huyhq = "npwbaamawpvhqtnngxjbn";
	double zcpctnjjiaxr = 4003;
	double jjcqyksuf = 2679;
	if (false != false) {
		int hcircj;
		for (hcircj = 33; hcircj > 0; hcircj--) {
			continue;
		}
	}
	return string("zcdvzddvzpqhdzwzeruy");
}

int jduqofz::hhfqjrcslngku(bool jmvogycwec, int mepcioqoemh, bool naahemylvi, int sivxjk, double ztqffhsfl, string wykkcazporhw, string blsvlivjmnhfw, double pjoaimkmma, string bvpmrphiillufa, bool qmqfounzdrpitt) {
	string cqlvfijujgmhr = "puktene";
	int vyrinzgtiulv = 2533;
	if (string("puktene") == string("puktene")) {
		int phxjlk;
		for (phxjlk = 34; phxjlk > 0; phxjlk--) {
			continue;
		}
	}
	if (string("puktene") != string("puktene")) {
		int iixpk;
		for (iixpk = 90; iixpk > 0; iixpk--) {
			continue;
		}
	}
	return 44813;
}

void jduqofz::kpfmampnzbjjqmzjmvgwow(bool vceqaioz, int gkvorehcgexfs, int yscrzvzyqoy, double ouptjkuchmida, double nuylsbnevyu, bool sqsrjjqzswkamk, double nqamhjtu, string fpugvwjmvkmtwd, string htmnvoyj) {
	string bkkptbkngvha = "hxicioysnanafgtqlfohckpbfvpuqcrowysnrpjfjjhlygpznj";
	int gaysp = 4676;
	double xoubnjvyi = 1519;
	if (1519 != 1519) {
		int authkeyr;
		for (authkeyr = 71; authkeyr > 0; authkeyr--) {
			continue;
		}
	}
	if (string("hxicioysnanafgtqlfohckpbfvpuqcrowysnrpjfjjhlygpznj") == string("hxicioysnanafgtqlfohckpbfvpuqcrowysnrpjfjjhlygpznj")) {
		int scmorwbbz;
		for (scmorwbbz = 49; scmorwbbz > 0; scmorwbbz--) {
			continue;
		}
	}
	if (string("hxicioysnanafgtqlfohckpbfvpuqcrowysnrpjfjjhlygpznj") == string("hxicioysnanafgtqlfohckpbfvpuqcrowysnrpjfjjhlygpznj")) {
		int cwogbq;
		for (cwogbq = 68; cwogbq > 0; cwogbq--) {
			continue;
		}
	}
	if (4676 != 4676) {
		int hmz;
		for (hmz = 43; hmz > 0; hmz--) {
			continue;
		}
	}
	if (1519 != 1519) {
		int leuly;
		for (leuly = 98; leuly > 0; leuly--) {
			continue;
		}
	}

}

double jduqofz::bnhggcvbpldfptybrrfv(string zzlijmqal, int dveaq, int zhledifgy, bool hehbxtqvuqt, bool rypjfkvftjkx, double gmobdb, double ejrbrhq) {
	int biclquidxi = 1538;
	double iexrpr = 24676;
	double ulouegetl = 45148;
	int comvoy = 289;
	bool rxkjiqbuxu = true;
	int aoaftbmmcugrt = 2585;
	int kylmelcaiblzrgq = 537;
	int rbpyvahu = 814;
	return 70503;
}

bool jduqofz::nehdqcmuriuxp(double lcccddkoqbbhjp, string hkigrpktuyvhj, double hkfkmklof, bool yzvarqkjfpwsvry) {
	return false;
}

bool jduqofz::fngmpfeildl(string jdnoqy, bool tgabop) {
	return false;
}

int jduqofz::sqeverjnjkpyvetodjjcxx(string wmegyew, bool wjdqiumgsr, bool qyymeuaobfbed, string xnyhvlkvgv, double bavlodqpyg, double ytivqajqhhugx, double nctpgwnqhqqaw) {
	bool sbhdmlq = true;
	if (true == true) {
		int sqr;
		for (sqr = 18; sqr > 0; sqr--) {
			continue;
		}
	}
	if (true != true) {
		int dqlqejygh;
		for (dqlqejygh = 96; dqlqejygh > 0; dqlqejygh--) {
			continue;
		}
	}
	if (true == true) {
		int kvnp;
		for (kvnp = 70; kvnp > 0; kvnp--) {
			continue;
		}
	}
	if (true != true) {
		int kyoixco;
		for (kyoixco = 36; kyoixco > 0; kyoixco--) {
			continue;
		}
	}
	if (true != true) {
		int zgvv;
		for (zgvv = 23; zgvv > 0; zgvv--) {
			continue;
		}
	}
	return 43824;
}

bool jduqofz::bqjyfzlfrxj(bool lwnvnuqfpocijgy, bool uzjhwqiafb, double numumkiqtmfitwe, int xlehoxdzysvd, string ochraytuexuxd, bool jvwyx, bool msptvndq, int jbjnaqwp, string jdgogcvvzmhiema, double cgsukkyixkbnpt) {
	double lmfzuj = 67079;
	bool awbbqctw = false;
	int bcetkmi = 3741;
	int pilido = 6363;
	if (67079 == 67079) {
		int dgvdjx;
		for (dgvdjx = 75; dgvdjx > 0; dgvdjx--) {
			continue;
		}
	}
	if (6363 != 6363) {
		int onvqlze;
		for (onvqlze = 89; onvqlze > 0; onvqlze--) {
			continue;
		}
	}
	if (67079 == 67079) {
		int rgqv;
		for (rgqv = 43; rgqv > 0; rgqv--) {
			continue;
		}
	}
	return false;
}

bool jduqofz::webfpwikbz(bool wunagnetcdacw, string ekgdhgyujflpzam, bool qafzs, int ttiwv, double zduffyzydjgg, int puggpfmdxylqscy, int dbkvdhhon) {
	bool dwtthin = true;
	bool msselipz = false;
	int izicnemtws = 514;
	string rmcaatvwb = "belmzrbsqoitolhfiussbwamzaeodberailrdaujonlfumoef";
	if (false != false) {
		int awe;
		for (awe = 5; awe > 0; awe--) {
			continue;
		}
	}
	if (false != false) {
		int cmedo;
		for (cmedo = 48; cmedo > 0; cmedo--) {
			continue;
		}
	}
	if (false == false) {
		int lre;
		for (lre = 47; lre > 0; lre--) {
			continue;
		}
	}
	if (string("belmzrbsqoitolhfiussbwamzaeodberailrdaujonlfumoef") == string("belmzrbsqoitolhfiussbwamzaeodberailrdaujonlfumoef")) {
		int pjsjby;
		for (pjsjby = 23; pjsjby > 0; pjsjby--) {
			continue;
		}
	}
	return false;
}

jduqofz::jduqofz() {
	this->kpfmampnzbjjqmzjmvgwow(false, 804, 6497, 7891, 54298, false, 680, string("jmktzsfnoqkrfkdwvocvkgfss"), string("ypvvfogwiejvwiycukjpswovnttsudwdidwgxbvdbqfxzhitouvtyuqowrcsxbjsmnjmcb"));
	this->bnhggcvbpldfptybrrfv(string("cpvcnfjcefpwhvqqtrmztcqqmcgqlhrdomgmkjshh"), 215, 4931, true, false, 52395, 81224);
	this->nehdqcmuriuxp(27660, string("ytadnqdobjhzmcju"), 46842, false);
	this->fngmpfeildl(string("rzzrgithwjhkwtwvhkoklmvnqucrvjibcikzbvcsleutivuypgfsugtopbtokrwdaosldtzbyoxtoqwcdtgtzcdahl"), true);
	this->sqeverjnjkpyvetodjjcxx(string("jgqubkvpfsmnezvkircywxcmfsapehijerajspwffluwhyktpzgendpsgtjnsjzbz"), true, true, string("xicolmdiciflojxywcmiockrbooisrsmckttgiagukzutnwbckbikjnqdblkkhsoxfukevsfwfuwho"), 6915, 6655, 5020);
	this->bqjyfzlfrxj(false, true, 22704, 7712, string("cixlntitvxeg"), false, true, 5638, string("dooznoqoacyjhkncksiqdeloiwgtzvknfdfvmrshxeecqivoaggiwpcaxlcrbjhljcmhgrnqoybsjwydpjszxzjjkgwzsylzpqdd"), 16583);
	this->webfpwikbz(false, string("hzkcve"), false, 1934, 42969, 5045, 4250);
	this->ftjxolxdivpoz(true, 35969, 2285, 36733, string("xfjzjemrzmcbtcpvzkyeaeoqywneprghdqzalbsonwwqpnptfqerfalnfqwllup"), 2288, false, true);
	this->kticxhpilywsdpwhotlxwuni(string("gfwqzxfkehdxsbgfdkgbdgnqmitxhudqdeejdfackiagg"), true);
	this->jbnfslkjtqpggaquzqyjz();
	this->xsyfiiziwsv(2151);
	this->nxpwzgqvkthtnaepehmhffzq(true, 4828, 35670, 813, 11213, false);
	this->xefffnqmgubcwu(string("tmsxltkobji"), true, 1246);
	this->itgopjwpidcsbwb(19386, 7351, false);
	this->ktutmtyujjrivaebbufslfmi(2315, false, true, 1331, 54132, 38683, 6698, 2727, false, 5722);
	this->ngunpxorsihlbeeannjvxxnrv(1126, false, string("vxkqsktxfinonnzbwagtfojwdksrocedqdqfurwhxqngmzvmjpbdhoxkrmacxyaqnaibdarodnvlpj"), false, 5046, string("uiofyvwkiarmnviaggzejepqfthuuomzweopoqlftgknlffqscibnxicyhr"), 2890, 4351);
	this->hhfqjrcslngku(true, 876, false, 756, 21952, string("gehfiaqagjyjfwyjbrpkxwirmcxfpq"), string("puidxazwotakclcimgrscoiqzuabpcub"), 78614, string("fshydunfgnjvpkmrfgdnwtklevwcbqaeqbyrdnqztbfaqkzrflmgsafvxrichdpy"), true);
	this->qzywszysdcyfamtaepbxy(string("aeyvfbddbestkmjysdzhpzarqhjkhsrpicctplcjkehy"), true, 7959, string("bccppikxqwmkefaasrhghmgvebsfwwsancfbrvzlymdaerrtkgjfrxdfiivhrigc"), string("nqerdxrvhfcm"), 2209, 3751);
	this->xweigjkpgwqafsi(744, 10498, string("uvqijtvzlgijzyufgvcjbgdesdspbtugegrelqsposeroiqsiihhdoyhpqtuxvrhfvexjzkosoxfnvgkyjekbahxbx"), 2378, string("vgwqkpgdywyotlam"), false, string("fiaozlalcwynvxbdxksqlcremoapruvlrmljwxxyrsggqzdpdvswtqbtiuian"));
	this->ugdcykhxoy();
	this->fbiqhdtquegaemj(false, true, 30939);
	this->zadyqqvkgjim(8946, string("yvdlqifattfrispeheajsynjiwimxbcikohymzxcaxuxzjvycalfjmcnbf"), string("kebyucvwudyjx"), string("digzloyyfelpxvxsyiu"), 8615);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class jhawllq {
public:
	double tdsktbh;
	jhawllq();
	int tkyecsqaqrrjixalnjjiezc(bool ahhcafuabdvc, string solgse);
	int cfesavkrdt(int stzdjibtvvsu, double tysbkn, int judeyajvlttwzhg, double eyfsaplsaepalqq, double ahbptyktrktyz, double vjxykupuwhn, int brjlkejfqhjfpbt);
	bool fsrhctdnbgvvdohoalgrbj(int wonegnciv, int cnrfxnszlvuf, int lrkzbqrnemfhm, double baxfiuekpr, string iblplre, bool pelpdvz, double ppbfogbgmmujf);
	string yqkhwmeykr(int tklzygatosdz, int csdowcxobd, string oyqoc, int mcwcsaniqoeroc, int iflaveeuzxs, int eycljcgzxw, int ydbgks, bool fypjewlqrsebfe, bool npnmltwsag);
	double ixfzdivckilcajhvqstey();
	void autuiaamottkaaee(double umrlrcktgcvevyv, bool oxxdlmswqnojjq, int bzygcys);
	void dbvvbshbihan(int gdxoxxw, int mwmgkchezt, bool gogxj, string snndissybvj, int eaayguvhtjvmo, string gndhrtgwzuisd, string ykfmnjkpyfojlt, bool nfycg, string dtrcken, bool qwqepqgjnll);
	double teovhlslowb(int xuvjnyjbswwca, bool rinkvc, string eejkunf);

protected:
	string casiaxekzsrw;

	int zertmnphdlylgoovua(bool fwalhyrql, int jkhsdwt, int arrwoateagejcm, double xkenzup, double aqyeptzmvhkh);
	int btzrvbhffatpyl(int quzriszqk, string bhbxgfkde, int mcjpjdfusth, bool ixbwd, int lmovnc, bool makycplcc, string jhhohprja, bool txijalyb);
	string buzzfbreieb(string hmsnji, int mxmwigescztik, bool ukxtcvx, bool fwdbobpmzyeuc, int eyhymd, bool iyamdgshw);
	double lddpkuahcm();
	int avsqjjhixwigldoihiofdzmec(string yprphuvrabwnd, int ddjswsjhyj, string pbmzhzajdidhw, bool oizeoyhyvo, double jzjlysw, double shjdb, int jminpne, double vucgfpqribid);
	double rmkpionomo(int slmkzmymwdq, string ofejyapeigv, double bhbyihm, string hijfihwizvikrmj);

private:
	double zrivylfionsocw;
	double ayouuyvfq;
	int xyzmzugfs;

	bool jjdfxvuofbtxxyax(bool gvqtzsabobj, bool cmouxxvxs, double hfpnxkuwbhg, double nhwacwrgftm, bool dgfzsm);

};


bool jhawllq::jjdfxvuofbtxxyax(bool gvqtzsabobj, bool cmouxxvxs, double hfpnxkuwbhg, double nhwacwrgftm, bool dgfzsm) {
	double sdnri = 10691;
	bool kmmpozkltj = false;
	int jxleuntjfthrkih = 4309;
	double nxwegkvbwqpmc = 15192;
	string lrplu = "pjppufnfkzjeiwsooikjtqhxiqbwapvfezvdbgugvzinrplveharxnutkvdvehcofmixdextmrluqwcockfhodzkbrdg";
	string cguekmvamqa = "bhbqhzfbwamuikk";
	bool glnjhjtdidjf = false;
	if (4309 == 4309) {
		int dzlifxfh;
		for (dzlifxfh = 10; dzlifxfh > 0; dzlifxfh--) {
			continue;
		}
	}
	if (10691 == 10691) {
		int eecf;
		for (eecf = 32; eecf > 0; eecf--) {
			continue;
		}
	}
	if (string("pjppufnfkzjeiwsooikjtqhxiqbwapvfezvdbgugvzinrplveharxnutkvdvehcofmixdextmrluqwcockfhodzkbrdg") == string("pjppufnfkzjeiwsooikjtqhxiqbwapvfezvdbgugvzinrplveharxnutkvdvehcofmixdextmrluqwcockfhodzkbrdg")) {
		int asjqtf;
		for (asjqtf = 95; asjqtf > 0; asjqtf--) {
			continue;
		}
	}
	return true;
}

int jhawllq::zertmnphdlylgoovua(bool fwalhyrql, int jkhsdwt, int arrwoateagejcm, double xkenzup, double aqyeptzmvhkh) {
	string roffzopelpaprv = "tksuyybmquxssspgdnjljdalpvesuaecdojwddjjkflihzbyjuwwxvxxzbdiiaacsjhchdqflcnomxtljhccryddgznws";
	bool ljxmmvedizgro = false;
	string wumsyli = "jjehaxe";
	bool opnihsuuhp = true;
	int azfqvbrxihxo = 6882;
	bool ixumxjlymxrjce = false;
	return 24057;
}

int jhawllq::btzrvbhffatpyl(int quzriszqk, string bhbxgfkde, int mcjpjdfusth, bool ixbwd, int lmovnc, bool makycplcc, string jhhohprja, bool txijalyb) {
	string qycxwhfrpzffckw = "vyawjjcrjercickijkpldpwiuaqhgltxhyrycbzqjipwcccakxtewrzsxjwpwllumkrxgxafkmognilljgntssshvhmnsrp";
	bool tobtsorz = true;
	int xkdgjaz = 1711;
	double mdrnfwqyxiza = 10034;
	bool kvjscufm = true;
	int jkkpyhrfsiekwjn = 3223;
	double bwknef = 10776;
	if (string("vyawjjcrjercickijkpldpwiuaqhgltxhyrycbzqjipwcccakxtewrzsxjwpwllumkrxgxafkmognilljgntssshvhmnsrp") == string("vyawjjcrjercickijkpldpwiuaqhgltxhyrycbzqjipwcccakxtewrzsxjwpwllumkrxgxafkmognilljgntssshvhmnsrp")) {
		int waudv;
		for (waudv = 92; waudv > 0; waudv--) {
			continue;
		}
	}
	if (3223 == 3223) {
		int ndxccfica;
		for (ndxccfica = 44; ndxccfica > 0; ndxccfica--) {
			continue;
		}
	}
	if (string("vyawjjcrjercickijkpldpwiuaqhgltxhyrycbzqjipwcccakxtewrzsxjwpwllumkrxgxafkmognilljgntssshvhmnsrp") == string("vyawjjcrjercickijkpldpwiuaqhgltxhyrycbzqjipwcccakxtewrzsxjwpwllumkrxgxafkmognilljgntssshvhmnsrp")) {
		int ilt;
		for (ilt = 86; ilt > 0; ilt--) {
			continue;
		}
	}
	if (true != true) {
		int xxovmm;
		for (xxovmm = 95; xxovmm > 0; xxovmm--) {
			continue;
		}
	}
	return 23746;
}

string jhawllq::buzzfbreieb(string hmsnji, int mxmwigescztik, bool ukxtcvx, bool fwdbobpmzyeuc, int eyhymd, bool iyamdgshw) {
	int fhqtcoypqckv = 1435;
	double lkpsbeclkakamzm = 11116;
	int edsxqs = 2430;
	double liwwymnxij = 43559;
	double jkplnid = 14575;
	bool hanzvbhy = false;
	double dtgjxggob = 9374;
	double sdodok = 11740;
	if (43559 != 43559) {
		int emulubnboo;
		for (emulubnboo = 56; emulubnboo > 0; emulubnboo--) {
			continue;
		}
	}
	if (9374 != 9374) {
		int ivhx;
		for (ivhx = 38; ivhx > 0; ivhx--) {
			continue;
		}
	}
	if (14575 != 14575) {
		int npddpu;
		for (npddpu = 57; npddpu > 0; npddpu--) {
			continue;
		}
	}
	return string("dmjjoaf");
}

double jhawllq::lddpkuahcm() {
	int kspucautm = 1026;
	double canfqmxpney = 6372;
	bool czpyyvmfqskrnji = true;
	double urztzdyhip = 61084;
	int oiqwixx = 5328;
	if (5328 == 5328) {
		int oriz;
		for (oriz = 41; oriz > 0; oriz--) {
			continue;
		}
	}
	if (61084 != 61084) {
		int fjjdxpmvh;
		for (fjjdxpmvh = 5; fjjdxpmvh > 0; fjjdxpmvh--) {
			continue;
		}
	}
	if (true != true) {
		int mi;
		for (mi = 57; mi > 0; mi--) {
			continue;
		}
	}
	if (true != true) {
		int rujdrnfq;
		for (rujdrnfq = 26; rujdrnfq > 0; rujdrnfq--) {
			continue;
		}
	}
	return 77748;
}

int jhawllq::avsqjjhixwigldoihiofdzmec(string yprphuvrabwnd, int ddjswsjhyj, string pbmzhzajdidhw, bool oizeoyhyvo, double jzjlysw, double shjdb, int jminpne, double vucgfpqribid) {
	bool azjfmr = false;
	string ilpdtnx = "ttevdlikeyjwgdiuaeljohfndqmqnyyvusuluxjucjucjhki";
	double gqjpm = 757;
	string xspzmgf = "lymkxtvdbbtzwozclofznhxkocbiaviloxascpwmmcgwfwzcqgphycafixq";
	int yclkog = 4901;
	double sslffktkv = 56781;
	if (false != false) {
		int njoltl;
		for (njoltl = 13; njoltl > 0; njoltl--) {
			continue;
		}
	}
	if (false == false) {
		int oersu;
		for (oersu = 50; oersu > 0; oersu--) {
			continue;
		}
	}
	if (string("ttevdlikeyjwgdiuaeljohfndqmqnyyvusuluxjucjucjhki") != string("ttevdlikeyjwgdiuaeljohfndqmqnyyvusuluxjucjucjhki")) {
		int vhzqeufh;
		for (vhzqeufh = 65; vhzqeufh > 0; vhzqeufh--) {
			continue;
		}
	}
	return 63573;
}

double jhawllq::rmkpionomo(int slmkzmymwdq, string ofejyapeigv, double bhbyihm, string hijfihwizvikrmj) {
	int cqrqhpioqdcii = 2983;
	bool qysxkvmgqhwkz = true;
	double xqadoxbtpppmylf = 86467;
	string gjqgkmkxfyziz = "hfpvefmtvhfwmvobuxsuwquaqmsncoyzksxu";
	return 30942;
}

int jhawllq::tkyecsqaqrrjixalnjjiezc(bool ahhcafuabdvc, string solgse) {
	bool cdhytsuu = true;
	if (true == true) {
		int sjli;
		for (sjli = 60; sjli > 0; sjli--) {
			continue;
		}
	}
	return 52251;
}

int jhawllq::cfesavkrdt(int stzdjibtvvsu, double tysbkn, int judeyajvlttwzhg, double eyfsaplsaepalqq, double ahbptyktrktyz, double vjxykupuwhn, int brjlkejfqhjfpbt) {
	bool phiqezeipgqf = false;
	bool ighozlaakuefd = true;
	bool kdbyqqkg = true;
	bool bvllebsmpjiq = false;
	double uwappludynl = 13453;
	int cystjojlsgps = 507;
	int opcczatbcvkh = 904;
	bool iizwqepwzfn = false;
	string adxkajhufsrua = "nyioqlbqenhpakpwpkeuwbgcajvtmulrp";
	double qbctemmxbr = 18545;
	if (18545 != 18545) {
		int ovzmmqjvfh;
		for (ovzmmqjvfh = 22; ovzmmqjvfh > 0; ovzmmqjvfh--) {
			continue;
		}
	}
	return 91015;
}

bool jhawllq::fsrhctdnbgvvdohoalgrbj(int wonegnciv, int cnrfxnszlvuf, int lrkzbqrnemfhm, double baxfiuekpr, string iblplre, bool pelpdvz, double ppbfogbgmmujf) {
	bool tvhznnzorjrtl = false;
	int kvjea = 668;
	bool svqtfgrpzz = true;
	bool fftkiqebuexhqf = false;
	int oxhwrgd = 1084;
	double aunzfonmios = 2132;
	bool ipfexvkteybsv = true;
	return false;
}

string jhawllq::yqkhwmeykr(int tklzygatosdz, int csdowcxobd, string oyqoc, int mcwcsaniqoeroc, int iflaveeuzxs, int eycljcgzxw, int ydbgks, bool fypjewlqrsebfe, bool npnmltwsag) {
	double jsqjtzbp = 32959;
	bool dfjwt = true;
	string scbbzijeidlhs = "avvbhmwucfnbjgiqwxpjopbeqgwrtijpgsvgtsddnfpuukdhbbcxlbg";
	double rqbjhmlsgfagmkn = 19793;
	string jywju = "lursyljqtzpmufnvhvncuamdekgbvdfxpwsatehkjgibbbfhcrukpuqrgcwemwrldufhdpltiegutpgyomv";
	double dfdukmk = 46510;
	if (19793 == 19793) {
		int dm;
		for (dm = 87; dm > 0; dm--) {
			continue;
		}
	}
	return string("azsypz");
}

double jhawllq::ixfzdivckilcajhvqstey() {
	string nafoquhiadmh = "zpeunfnauouubvtoskzzgpazidrtbsxmspdntfvfdlnfl";
	double wtxwfi = 37214;
	string yhbzmamnen = "njcywgputdqqhdpvqvpuqfglvviueezadnelfrpnngsdszhgczpgeeuphrzaixbbfxv";
	if (37214 == 37214) {
		int sy;
		for (sy = 43; sy > 0; sy--) {
			continue;
		}
	}
	if (37214 == 37214) {
		int nvynhjaal;
		for (nvynhjaal = 14; nvynhjaal > 0; nvynhjaal--) {
			continue;
		}
	}
	if (37214 == 37214) {
		int icfcm;
		for (icfcm = 3; icfcm > 0; icfcm--) {
			continue;
		}
	}
	return 34274;
}

void jhawllq::autuiaamottkaaee(double umrlrcktgcvevyv, bool oxxdlmswqnojjq, int bzygcys) {
	string ccvcbxviwwmtxb = "jjxumqkgptojiwplvyctrizlbiegknimbtqqmtumqsnnuwwjbfhpyiupwgn";
	double bhrbkyyaqsssrtv = 36412;
	double znpximmzxps = 10102;
	string vjrvmwmeksgzm = "imeudnkydgtcrivmghewvguhqbnemlmscqkyoypfwhcytrvhrnmpcgqjnlabgocqs";
	int tphngrwtr = 1902;
	int priainpvwbk = 4884;
	if (36412 != 36412) {
		int wrvwlyv;
		for (wrvwlyv = 38; wrvwlyv > 0; wrvwlyv--) {
			continue;
		}
	}
	if (4884 != 4884) {
		int jbc;
		for (jbc = 96; jbc > 0; jbc--) {
			continue;
		}
	}
	if (4884 == 4884) {
		int ztnedbpzl;
		for (ztnedbpzl = 24; ztnedbpzl > 0; ztnedbpzl--) {
			continue;
		}
	}

}

void jhawllq::dbvvbshbihan(int gdxoxxw, int mwmgkchezt, bool gogxj, string snndissybvj, int eaayguvhtjvmo, string gndhrtgwzuisd, string ykfmnjkpyfojlt, bool nfycg, string dtrcken, bool qwqepqgjnll) {
	bool zivzcszosnxeex = true;
	int uurebykgsn = 4025;
	string dusqlzybmfle = "rrlawuwegvnzkgccafvsscsxkem";
	string yptea = "qaerofqiyqkyqucauzywuqrmuorugozbfcsfemxpkrrmotiojrjtdpbkipgacuzznpucveyrgdzktlmulzugkkdqpyabv";
	double lclpjjyxv = 47280;
	bool dhuqpgfifcqyp = true;
	double fstgynmkwowjke = 694;
	if (47280 == 47280) {
		int xgb;
		for (xgb = 87; xgb > 0; xgb--) {
			continue;
		}
	}
	if (true != true) {
		int flqr;
		for (flqr = 85; flqr > 0; flqr--) {
			continue;
		}
	}
	if (694 != 694) {
		int xmaot;
		for (xmaot = 98; xmaot > 0; xmaot--) {
			continue;
		}
	}

}

double jhawllq::teovhlslowb(int xuvjnyjbswwca, bool rinkvc, string eejkunf) {
	string bahiuy = "dpuplvlglirztnll";
	string lqwybgkcwraddv = "nsvmvzgpodkskfztzsibbbgigucdwziumxuzefnludkiwz";
	string xgvwzac = "kfnikrfycecfbvdnakqiixonucpqyuzxuxcitqbrhnfucljfkvnhbsb";
	string xtpnemcmczdpi = "shbdtroyezalwopvwemgakacytfsvemfyxinbsxaebnbbgflqzyhldauxiflxbeqnhiopehukuknxqdsxcbrpzpdkvfziumu";
	int fwrqyxygyv = 5872;
	int gupzh = 7255;
	int xmpdhz = 8334;
	if (7255 != 7255) {
		int vxpoaat;
		for (vxpoaat = 54; vxpoaat > 0; vxpoaat--) {
			continue;
		}
	}
	if (string("kfnikrfycecfbvdnakqiixonucpqyuzxuxcitqbrhnfucljfkvnhbsb") != string("kfnikrfycecfbvdnakqiixonucpqyuzxuxcitqbrhnfucljfkvnhbsb")) {
		int oedgijv;
		for (oedgijv = 25; oedgijv > 0; oedgijv--) {
			continue;
		}
	}
	if (string("nsvmvzgpodkskfztzsibbbgigucdwziumxuzefnludkiwz") == string("nsvmvzgpodkskfztzsibbbgigucdwziumxuzefnludkiwz")) {
		int ggegjqtu;
		for (ggegjqtu = 21; ggegjqtu > 0; ggegjqtu--) {
			continue;
		}
	}
	if (8334 != 8334) {
		int ichjw;
		for (ichjw = 61; ichjw > 0; ichjw--) {
			continue;
		}
	}
	if (8334 == 8334) {
		int cjpvrqbsv;
		for (cjpvrqbsv = 88; cjpvrqbsv > 0; cjpvrqbsv--) {
			continue;
		}
	}
	return 4374;
}

jhawllq::jhawllq() {
	this->tkyecsqaqrrjixalnjjiezc(true, string("bpwgoqfbmvzjxqxcrpawsivbpkhakfolsjqtopgwegqgfdbqjaogaddsjrceysdnpvbno"));
	this->cfesavkrdt(3750, 16411, 1337, 9754, 69600, 5359, 547);
	this->fsrhctdnbgvvdohoalgrbj(1858, 2581, 1340, 33324, string("dukrkyexaxcwxoc"), true, 22436);
	this->yqkhwmeykr(9636, 3940, string("bgoekrmciaeeqxdvyizcwbnbahcofbjvzclovneniivnomgsaptjqcoqajkggmlfpcvtpnuknntwehbd"), 4695, 1160, 1806, 6673, false, true);
	this->ixfzdivckilcajhvqstey();
	this->autuiaamottkaaee(38536, true, 3605);
	this->dbvvbshbihan(650, 1857, false, string("wuunfkwikpnpkoopgibwo"), 2897, string("gtzpillweplvcqbj"), string("sgftuwibvgzggbgrsochjznxopkmjxxw"), true, string("sdyfkyajyrefkytadwndivpojflyfljtjzqisupuqtpkjtgypbgfelohdshnltblypnzldiqaoclckp"), false);
	this->teovhlslowb(699, false, string("rripxqfvlorhhhjuduzynhnvhpncpbuegwwlqjqtcnplctjiotmlbnnufcjnpizneagbsrpxyekfoeqm"));
	this->zertmnphdlylgoovua(true, 2866, 4329, 42194, 28375);
	this->btzrvbhffatpyl(1562, string("vqhlrzcnhuucjehujkpwxpjychyjdfjgtlygfctntjasnjipwhmliqgiwqhkmbuqwbvflhwidtmyjotgsewezi"), 2061, true, 4218, false, string("upvvygdleaecwtucitocgwwguarvihgdpssbwkneehgiarmdkykstrbycajkcyidmeqnletohcmkrabpfpxkcsqzoapcvavsetll"), false);
	this->buzzfbreieb(string("avcufrddhwqrlvhyjnaertemguyzgmdpteslahmoptslrju"), 650, false, false, 512, true);
	this->lddpkuahcm();
	this->avsqjjhixwigldoihiofdzmec(string("piisvfstztpkwqrgqvfwqefmwrimv"), 3759, string("pcfywnkhnndvedfmwbelhvijebunerlvgtytjgssrxvrrlffiaryipgibedtrnbffwdvcr"), true, 48942, 31498, 448, 14964);
	this->rmkpionomo(5668, string("thvynfioskrrcchuouhmwqctzyrwoplxxkftjiozbzlerkpjxecoowfrojmkzhglxmwg"), 11692, string("eqaskikqtamqgfouizboimqyvilmezrjrcdjizitguoehjtuva"));
	this->jjdfxvuofbtxxyax(false, false, 33738, 24498, true);
}
