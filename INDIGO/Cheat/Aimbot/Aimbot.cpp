#include "Aimbot.h"

using namespace Client;

#pragma warning(disable:4244)
//[junk_enable /]
//[enc_string_enable /]
byte tt_ct_best_hit_1[6] =
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
};

#define TT_CT_BEST_HIT_SIZE_1 ( sizeof( tt_ct_best_hit_1 ) / sizeof( *tt_ct_best_hit_1 ) )

CAimbot::CAimbot()
{
	m_pLocal = nullptr;

	m_iBestPreTarget = -1;

	m_iBestTarget = -1;
	m_iBestHitbox = -1;

	m_bClamp = false;
	m_bAttack = false;
	m_bAimShot = false;
	m_bTargetFov = false;
	m_bTargetChange = false;
	m_bAutoPistolEn = false;

	m_pShotDelay = new CTimer();

	m_vAimBestHitboxScreen.Zero();
}

void CAimbot::pJunk()
{
	float hqxBIKBNHd = 70583108027213; hqxBIKBNHd = 73301306369813; if (hqxBIKBNHd = 62943321047646) hqxBIKBNHd = 24512045404913; hqxBIKBNHd = 45199783994198; hqxBIKBNHd = 39941984519978;
	if (hqxBIKBNHd = 72995172451204)hqxBIKBNHd = 10476463285856; hqxBIKBNHd = 53698641883994;
	if (hqxBIKBNHd = 4171689965960)hqxBIKBNHd = 10476463285856; hqxBIKBNHd = 53698641883994;
	if (hqxBIKBNHd = 4171689965960)hqxBIKBNHd = 10476463285856; hqxBIKBNHd = 53698641883994;
	if (hqxBIKBNHd = 4171689965960)hqxBIKBNHd = 10476463285856; hqxBIKBNHd = 53698641883994;
	if (hqxBIKBNHd = 4171689965960)hqxBIKBNHd = 10476463285856; hqxBIKBNHd = 53698641883994; hqxBIKBNHd = 20691352493579;

	float fIOvaAmrTX = 31901705490502; fIOvaAmrTX = 96193657518525; if (fIOvaAmrTX = 86221865702584) fIOvaAmrTX = 58747396757320; fIOvaAmrTX = 68433685492045; fIOvaAmrTX = 54920456843368;
	if (fIOvaAmrTX = 77159975874739)fIOvaAmrTX = 57025841995345; fIOvaAmrTX = 97932458722493;
	if (fIOvaAmrTX = 8257422218020)fIOvaAmrTX = 57025841995345; fIOvaAmrTX = 97932458722493;
	if (fIOvaAmrTX = 8257422218020)fIOvaAmrTX = 57025841995345; fIOvaAmrTX = 97932458722493;
	if (fIOvaAmrTX = 8257422218020)fIOvaAmrTX = 57025841995345; fIOvaAmrTX = 97932458722493;
	if (fIOvaAmrTX = 8257422218020)fIOvaAmrTX = 57025841995345; fIOvaAmrTX = 97932458722493; fIOvaAmrTX = 40102882086380;

}

bool CAimbot::IsEnable()
{
	if ( !m_pLocal || !m_pCmd )
		return false;

	if ( !Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Active )
		return false;

	if ( !m_pLocal->WeaponAmmo || m_pLocal->bInReload )
		return false;

	if ( m_pLocal->WeaponType > WEAPON_TYPE_SNIPER )
		return false;


	return true;
}

int CAimbot::GetPlayerFov( CPlayer * pPlayer )
{
	int iFov = 0;
	int iFovVal = 0;

	if ( m_pLocal->iShotsFired > 1 && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN )
	{
		iFovVal = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov;
	}
	else
	{
		iFovVal = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov;
	}

	int base_fov = pow( iFovVal + FIX_MIN_FOV_HEAD , 2 ) * 90;

	if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType <= 0 )
	{
		iFov = (int)( base_fov / ( pPlayer->iDistance * m_pLocal->iFov ) );
	}
	else
	{
		iFov = (int)( base_fov / ( FOV_BASE_DISTANCE * m_pLocal->iFov ) );
	}

	return iFov;
}

int CAimbot::GetBestTarget()
{
	float ScreenDistanceBase = 1000.f;

	int m_lBestTarget = -1;

	for ( BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize() /*&& g_pPlayers->bActive*/; PlayerIndex++ )
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer( PlayerIndex );

		if ( pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate )
		{
			if ( !Settings::Aimbot::aim_Deathmatch && pPlayer->Team == m_pLocal->Team )
				continue;

			if ( !Settings::Aimbot::aim_WallAttack && !pPlayer->bVisible )
				continue;

			Vector vHitbox;
			Vector vHitboxScreen;

			if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit >= 1 )
			{
				vHitbox = pPlayer->m_pEntity->GetHitboxPosition( HITBOX_BODY );
			}
			else
			{
				vHitbox = pPlayer->m_pEntity->GetHitboxPosition( tt_ct_best_hit_1[Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot] );
			}

			if ( WorldToScreen( vHitbox , vHitboxScreen ) )
			{
				Vector2D vPlayerScr = Vector2D( vHitboxScreen.x , vHitboxScreen.y );

				float fDistanceScreen = DistanceScreen( g_vCenterScreen , vPlayerScr );

				if ( fDistanceScreen < ScreenDistanceBase )
				{
					ScreenDistanceBase = fDistanceScreen;
					m_lBestTarget = PlayerIndex;
				}
			}
		}
	}

	return m_lBestTarget;
}

void CAimbot::pJunk2()
{
	float KoQHvyysYH = 38744374367638; KoQHvyysYH = 68695414441071; if (KoQHvyysYH = 52127204684538) KoQHvyysYH = 97015681805734; KoQHvyysYH = 75711337933996; KoQHvyysYH = 79339967571133;
	if (KoQHvyysYH = 65541709701568)KoQHvyysYH = 46845386724374; KoQHvyysYH = 10807798938263;
	if (KoQHvyysYH = 41933251320595)KoQHvyysYH = 56481654815515; KoQHvyysYH = 10807798938263;
	if (KoQHvyysYH = 41933251320595)KoQHvyysYH = 46845386724374; KoQHvyysYH = 10807798938263;
	if (KoQHvyysYH = 41933251320595)KoQHvyysYH = 46845386724374; KoQHvyysYH = 97865468658444;
	if (KoQHvyysYH = 45342345323243)KoQHvyysYH = 46845386724374; KoQHvyysYH = 10807798938263; KoQHvyysYH = 40697702758765;

	float xdNrSfwyDC = 23551845687044; xdNrSfwyDC = 16104074563607; if (xdNrSfwyDC = 79408086400691) xdNrSfwyDC = 6531423703572; xdNrSfwyDC = 26827206200309; xdNrSfwyDC = 62003092682720;
	if (xdNrSfwyDC = 4550775653142)xdNrSfwyDC = 64006915244259; xdNrSfwyDC = 75459726737504;
	if (xdNrSfwyDC = 51481548654815)xdNrSfwyDC = 64006915244259; xdNrSfwyDC = 75459726737504;
	if (xdNrSfwyDC = 67111273520605)xdNrSfwyDC = 15487946548514; xdNrSfwyDC = 75459726737504;
	if (xdNrSfwyDC = 67111273520605)xdNrSfwyDC = 64006915244259; xdNrSfwyDC = 51648488154654;
	if (xdNrSfwyDC = 67111273520605)xdNrSfwyDC = 64006915244259; xdNrSfwyDC = 75459726737504; xdNrSfwyDC = 70485319816133;

}

int CAimbot::GetBestHitBox()
{
	float ScreenDistanceBase = 1000.f;

	int m_lBestHitbox = -1;

	if ( m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN )
	{
		if ( m_iBestHitbox && m_bAttack && !m_bTargetChange )
			m_lBestHitbox = m_iBestHitbox;
	}

	CPlayer* pPlayer = g_pPlayers->GetPlayer( m_iBestTarget );

	if ( pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate )
	{
		if ( m_lBestHitbox == -1 )
		{
			if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit >= 1 )
			{
				for ( byte bHitbox = 0; bHitbox < TT_CT_BEST_HIT_SIZE_1; bHitbox++ )
				{
					Vector vHitBox = pPlayer->m_pEntity->GetHitboxPosition( tt_ct_best_hit_1[bHitbox] );
					Vector vHitBoxScreen;

					if ( !WorldToScreen( vHitBox , vHitBoxScreen ) )
						continue;

					Vector2D vHitboxSrc = Vector2D( vHitBoxScreen.x , vHitBoxScreen.y );

					float fDistanceScreen = DistanceScreen( g_vCenterScreen , vHitboxSrc );

					if ( fDistanceScreen < ScreenDistanceBase )
					{
						ScreenDistanceBase = fDistanceScreen;
						m_lBestHitbox = tt_ct_best_hit_1[bHitbox];
					}
				}
			}
			else
			{
				m_lBestHitbox = tt_ct_best_hit_1[Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot];
			}
		}

		Vector vHitBox = pPlayer->m_pEntity->GetHitboxPosition( m_lBestHitbox );

		if ( vHitBox.IsValid() && WorldToScreen( vHitBox , m_vAimBestHitboxScreen ) )
		{
			m_vAimBestHitbox = vHitBox;
			return m_lBestHitbox;
		}
		else
		{
			m_vAimBestHitbox.Zero();
			m_vAimBestHitboxScreen.Zero();
			return -1;
		}
	}

	return m_lBestHitbox;
}

void CAimbot::OnRender()
{	
	if ( !IsEnable() || m_iBestTarget == -1 || m_iBestHitbox == -1 )
		return;

	if ( m_vAimBestHitboxScreen.x <= 0.f || m_vAimBestHitboxScreen.y <= 0.f )
		return;

	CPlayer* pTargetPlayer = g_pPlayers->GetPlayer( m_iBestTarget );

	if ( Settings::Aimbot::aim_DrawSpot )
	{
		g_pRender->DrawFillBox( m_vAimBestHitboxScreen.x , m_vAimBestHitboxScreen.y ,
								2 , 2 , g_pEsp->GetPlayerColor( pTargetPlayer ) );
	}

	if ( Settings::Aimbot::aim_DrawFov )
	{
		int iPlayerFov = GetPlayerFov( pTargetPlayer );

		Color TargetFovColor = g_pEsp->GetPlayerColor( pTargetPlayer );

		if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType <= 0 )
		{
			g_pRender->DrawBox( m_vAimBestHitboxScreen.x - iPlayerFov , m_vAimBestHitboxScreen.y - iPlayerFov ,
								iPlayerFov * 2 , iPlayerFov * 2 , TargetFovColor );
		}
		else
		{
			g_pRender->DrawBox( g_vCenterScreen.x - iPlayerFov , g_vCenterScreen.y - iPlayerFov , iPlayerFov * 2 , iPlayerFov * 2 , TargetFovColor );
		}
	}
}

void CAimbot::pJunk3()
{
	float RokoTtWXRw = 56656633647272; RokoTtWXRw = 38554847638957; if (RokoTtWXRw = 3426037549322) RokoTtWXRw = 82540928235002; RokoTtWXRw = 96393919801730; RokoTtWXRw = 98017309639391;
	if (RokoTtWXRw = 57829788254092)RokoTtWXRw = 549322376218; RokoTtWXRw = 85800212091169;
	if (RokoTtWXRw = 40327035158172)RokoTtWXRw = 564865151521; RokoTtWXRw = 85800212091169;
	if (RokoTtWXRw = 40327035158172)RokoTtWXRw = 549322376218; RokoTtWXRw = 85800212091169;
	if (RokoTtWXRw = 15468564514511)RokoTtWXRw = 549322376218; RokoTtWXRw = 85800212091169;
	if (RokoTtWXRw = 40327035158172)RokoTtWXRw = 549322376218; RokoTtWXRw = 21548521151514; RokoTtWXRw = 35590023862601;

	float wpARFHiEHu = 64840162686011; wpARFHiEHu = 25967153188870; if (wpARFHiEHu = 86134761956187) wpARFHiEHu = 22594538347102; wpARFHiEHu = 70031924570679; wpARFHiEHu = 45706797003192;
	if (wpARFHiEHu = 31726432259453)wpARFHiEHu = 19561871887778; wpARFHiEHu = 9123904766916;
	if (wpARFHiEHu = 19869058351231)wpARFHiEHu = 19561871887778; wpARFHiEHu = 9123904766916;
	if (wpARFHiEHu = 19869058351231)wpARFHiEHu = 19561871887778; wpARFHiEHu = 9123904766916;
	if (wpARFHiEHu = 19869058351231)wpARFHiEHu = 19561871887778; wpARFHiEHu = 9123904766916;
	if (wpARFHiEHu = 19869058351231)wpARFHiEHu = 19561871887778; wpARFHiEHu = 9123904766916; wpARFHiEHu = 61784451829468;

}

void CAimbot::Aimbot()
{
	m_bAimShot = false;
	m_bTargetFov = false;

	if ( !IsEnable() )
		return;

	m_bAttack = ( m_pCmd->buttons & IN_ATTACK );

	if ( !g_pPlayers->GetPlayer( m_iBestTarget )->bUpdate )
	{
		m_iBestPreTarget = -1;
		m_iBestTarget = -1;
		m_iBestHitbox = -1;
	}

	m_iBestPreTarget = m_iBestTarget;
	m_iBestTarget = GetBestTarget();

	if ( m_bAttack )
	{
		if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && !m_bAutoPistolEn )
		{
			AutoPistol();
		}
	}

	if ( m_iBestTarget == -1 )
		return;

	if ( m_iBestPreTarget != m_iBestTarget && m_bAttack )
	{
		m_bTargetChange = true;
	}
	else
	{
		m_bTargetChange = false;
	}

	m_iBestHitbox = GetBestHitBox();

	if ( m_iBestHitbox == -1 )
		return;

	CPlayer* pPreTargetPlayer = g_pPlayers->GetPlayer( m_iBestPreTarget );
	CPlayer* pTargetPlayer = g_pPlayers->GetPlayer( m_iBestTarget );

	int iPlayerFov = GetPlayerFov( pTargetPlayer );

	if ( CheckPlayerFov( m_vAimBestHitboxScreen , iPlayerFov ) )
		m_bTargetFov = true;

	static bool bLockDelay = false;
	static bool bLockAttack = false;

	if ( !m_bAttack )
	{
		m_bClamp = true;
		bLockDelay = false;
		bLockAttack = false;
		m_pShotDelay->reset();
	}

	if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL )
	{
		if ( m_bTargetFov && !m_bAttack )
		{
			m_bAutoPistolEn = true;
		}
		else if ( !m_bTargetFov && !m_bAttack )
		{
			m_bAutoPistolEn = false;
		}
		else if ( !m_bTargetFov && m_bAttack )
		{
			m_bAutoPistolEn = false;
		}
	}

	if ( !Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL )
	{
		if ( m_pLocal->iShotsFired == 1 && bLockDelay )
			return;
	}

	AIM_ATTACK_TYPE AttackType = AA_SHOTGUN;

	if ( m_pLocal->WeaponType == WEAPON_TYPE_SNIPER || m_pLocal->WeaponType == WEAPON_TYPE_PISTOL )
		AttackType = AA_SNIPER_PISTOL;

	static bool bAimAttack = false;
	static bool bAimCheckAttack = false;

	if ( AttackType == AA_SHOTGUN )
	{
		if ( m_bAttack && m_bTargetFov )
		{
			bAimCheckAttack = true;
		}
		else
		{
			bAimCheckAttack = false;
		}
	}
	else if ( AttackType == AA_SNIPER_PISTOL )
	{
		if ( !Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol )
		{
			if ( m_bTargetFov && !m_bAttack )
			{
				bAimAttack = true;
			}
			else if ( !m_bTargetFov && m_bAttack )
			{
				bAimAttack = false;
			}
			else if ( !m_bTargetFov && !m_bAttack )
			{
				bAimAttack = false;
			}
			
			if ( m_bAttack && bAimAttack && m_bTargetFov )
			{
				bAimCheckAttack = true;
			}
			else
			{
				bAimCheckAttack = false;
			}
		}
		else
		{
			if ( m_bAttack && m_bTargetFov )
			{
				bAimCheckAttack = true;
			}
			else
			{
				bAimCheckAttack = false;
				m_bClamp = true;
			}
		}
	}

	if ( m_pLocal->WeaponType == WEAPON_TYPE_SNIPER || m_pLocal->WeaponType == WEAPON_TYPE_PISTOL )
		Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType = 2;

	if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType >= 1 && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN )
	{
		if ( !bLockAttack )
		{
			if ( m_bTargetFov && !m_bAttack )
			{
				bAimAttack = true;
			}
			else if ( !m_bTargetFov && m_bAttack )
			{
				bAimAttack = false;
			}
			else if ( !m_bTargetFov && !m_bAttack )
			{
				bAimAttack = false;
			}
		}

		if ( m_bAttack && bAimAttack && m_bTargetFov && !bLockAttack )
		{
			bAimCheckAttack = true;
			bLockAttack = true;
		}
		else if ( m_bAttack && m_bTargetFov && bLockAttack )
		{
			bAimCheckAttack = true;
			bLockAttack = true;
		}
		else
			bAimCheckAttack = false;
	}

	if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType >= 2 )
	{
		if ( m_bClamp && m_bTargetChange )
			m_bClamp = false;
	}

	if ( !( pTargetPlayer->m_pEntity->GetFlags() & FL_ONGROUND ) && Settings::Aimbot::aim_AntiJump )
		return;

	if ( bAimCheckAttack )
	{
		int AimDelay = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Delay;

		if ( AimDelay )
		{
			float fDistanceAimScreen = DistanceScreen( g_vCenterScreen , Vector2D( m_vAimBestHitboxScreen.x , m_vAimBestHitboxScreen.y ) );

			if ( m_pShotDelay->delay( AimDelay ) )
				m_bAimShot = true;

			if ( fDistanceAimScreen <= 3.5f && !bLockDelay )
			{
				m_bAimShot = true;
				bLockDelay = true;
			}
			else if ( bLockDelay )
			{
				m_bAimShot = true;
			}
		}
		else
		{
			m_bAimShot = true;
		}

		if ( m_bClamp )
		{
			if ( Settings::Aimbot::aim_CheckSmoke )
			{
				if ( LineGoesThroughSmoke( m_pLocal->vEyeOrigin , m_vAimBestHitbox ) )
					return;
			}

			AimbotSet();
		}

		if ( m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN || !Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol )
		{
			if ( m_bAimShot )
			{
				m_pCmd->buttons |= IN_ATTACK;
			}
			else
			{
				m_pCmd->buttons &= ~IN_ATTACK;
			}
		}

		if ( m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_bAutoPistolEn )
		{
			if ( m_bAimShot )
			{
				m_pCmd->buttons |= IN_ATTACK;
				m_bAutoPistolEn = false;
			}
			else
				m_pCmd->buttons &= ~IN_ATTACK;
		}
	}
}

void CAimbot::pJunk4()
{
	float NFKNmtIwWv = 54708146417706; NFKNmtIwWv = 13406654285873; if (NFKNmtIwWv = 65185894837996) NFKNmtIwWv = 82064283109562; NFKNmtIwWv = 10726652881060; NFKNmtIwWv = 28810601072665;
	if (NFKNmtIwWv = 63627328206428)NFKNmtIwWv = 48379965387630; NFKNmtIwWv = 22637389122295;
	if (NFKNmtIwWv = 49424957669274)NFKNmtIwWv = 48379965387630; NFKNmtIwWv = 25679845145154;
	if (NFKNmtIwWv = 15641254865485)NFKNmtIwWv = 25468154661454; NFKNmtIwWv = 22637389122295;
	if (NFKNmtIwWv = 49424957669274)NFKNmtIwWv = 48379965387630; NFKNmtIwWv = 22637389122295;
	if (NFKNmtIwWv = 49424957669274)NFKNmtIwWv = 48379965387630; NFKNmtIwWv = 25467845489454; NFKNmtIwWv = 37535431493089;

	float OXbmFkUSoA = 57542938889538; OXbmFkUSoA = 11433066912043; if (OXbmFkUSoA = 39014388784790) OXbmFkUSoA = 34418471158792; OXbmFkUSoA = 84462455270819; OXbmFkUSoA = 52708198446245;
	if (OXbmFkUSoA = 20834993441847)OXbmFkUSoA = 23148651415154; OXbmFkUSoA = 1526836450333;
	if (OXbmFkUSoA = 87237652779322)OXbmFkUSoA = 87847908716954; OXbmFkUSoA = 2564865148515;
	if (OXbmFkUSoA = 21548652146215)OXbmFkUSoA = 24679841514551; OXbmFkUSoA = 1526836450333;
	if (OXbmFkUSoA = 87237652779322)OXbmFkUSoA = 87847908716954; OXbmFkUSoA = 5648154511454;
	if (OXbmFkUSoA = 87237652779322)OXbmFkUSoA = 25484518451745; OXbmFkUSoA = 1526836450333; OXbmFkUSoA = 62947833580061;

}

void CAimbot::AimbotSet()
{
	if ( !m_vAimBestHitbox.IsValid() )
		return;

	Vector vAimAngle , vSmoothAimAngle;

	VectorAngles( m_vAimBestHitbox - m_pLocal->vEyeOrigin , vAimAngle );

	bool bEnableRcs = false;

	if ( Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcs )
	{
		if ( m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN && m_pLocal->iShotsFired > 1 )
			bEnableRcs = true;

		if ( m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && m_pLocal->iShotsFired <= 1 )
			bEnableRcs = true;
	}

	if ( bEnableRcs )
	{
		float MulVar = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcs * 0.02f;

		if ( Settings::Aimbot::aim_RcsType <= 0 )
		{
			vAimAngle -= m_pLocal->vAimPunch * MulVar;
		}
		else if ( Settings::Aimbot::aim_RcsType == 1 )
		{
			vAimAngle -= ( m_pLocal->vPunch + m_pLocal->vAimPunch ) * MulVar;
		}
		else if ( Settings::Aimbot::aim_RcsType >= 2 )
		{
			vAimAngle -= ( m_pLocal->vPunch + ( m_pLocal->vAimPunch * 2 * 0.5f ) ) * MulVar;
		}
	}

	float fSmooth = 10.f;

	if ( bEnableRcs && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN )
	{
		fSmooth = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth;
	}
	else
	{
		fSmooth = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth;
	}

	AngleNormalize( vAimAngle );

	if ( fSmooth < 10.f )
		fSmooth = 10.f;

	fSmooth = fSmooth / 10.f;

	SmoothAngles( m_pCmd->viewangles , vAimAngle , vSmoothAimAngle , fSmooth );

	m_pCmd->viewangles = vSmoothAimAngle;
}

void CAimbot::pJunk5()
{
	float cjDPiUhHtF = 59824396321221; cjDPiUhHtF = 66392866237794; if (cjDPiUhHtF = 76222355491880) cjDPiUhHtF = 91636967734537; cjDPiUhHtF = 59035002780645; cjDPiUhHtF = 27806455903500;
	if (cjDPiUhHtF = 85999169163696)cjDPiUhHtF = 54918803934915; cjDPiUhHtF = 36611921040771;
	if (cjDPiUhHtF = 83545497430671)cjDPiUhHtF = 54918803934915; cjDPiUhHtF = 36611921040771;
	if (cjDPiUhHtF = 83545497430671)cjDPiUhHtF = 54918803934915; cjDPiUhHtF = 36611921040771;
	if (cjDPiUhHtF = 83545497430671)cjDPiUhHtF = 54918803934915; cjDPiUhHtF = 36611921040771;
	if (cjDPiUhHtF = 83545497430671)cjDPiUhHtF = 54918803934915; cjDPiUhHtF = 36611921040771; cjDPiUhHtF = 9946692596747;

	float OIMxFJPpXI = 80788335356716; OIMxFJPpXI = 64914617620086; if (OIMxFJPpXI = 83916401760853) OIMxFJPpXI = 46042878818300; OIMxFJPpXI = 55717159556028; OIMxFJPpXI = 95560285571715;
	if (OIMxFJPpXI = 40222404604287)OIMxFJPpXI = 17608534650274; OIMxFJPpXI = 40168938488075;
	if (OIMxFJPpXI = 92194258965681)OIMxFJPpXI = 17608534650274; OIMxFJPpXI = 40168938488075;
	if (OIMxFJPpXI = 92194258965681)OIMxFJPpXI = 17608534650274; OIMxFJPpXI = 40168938488075;
	if (OIMxFJPpXI = 92194258965681)OIMxFJPpXI = 17608534650274; OIMxFJPpXI = 40168938488075;
	if (OIMxFJPpXI = 92194258965681)OIMxFJPpXI = 17608534650274; OIMxFJPpXI = 40168938488075; OIMxFJPpXI = 77213351299919;

}

void CAimbot::AutoPistol()
{
	float NextAttack = m_pLocal->m_pWeaponEntity->GetNextPrimaryAttack();
	float Tick = m_pLocal->m_pEntity->GetTickBase() * Interfaces::GlobalVars()->interval_per_tick;

	if ( NextAttack < Tick )
		return;

	if ( *m_pLocal->m_pWeaponEntity->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_REVOLVER )
	{
		m_pCmd->buttons &= ~IN_ATTACK2;
	}
	else
	{
		m_pCmd->buttons &= ~IN_ATTACK;
	}
}

void CAimbot::OnCreateMove( CUserCmd * pCmd , CMe * pLocal )
{
	m_pLocal = pLocal;
	m_pCmd = pCmd;

	Aimbot();
}
