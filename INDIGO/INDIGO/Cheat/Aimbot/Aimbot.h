#pragma once

#include "../../Engine/Engine.h"

class CTimer;

namespace Engine
{
	class CMe;
	class APlayer;
}

using namespace Engine;

enum AIM_ATTACK_TYPE
{
	AA_SHOTGUN ,
	AA_SNIPER_PISTOL
};

class AAimbot
{
public:

	AAimbot();
//[swap_lines]
	bool	IsEnable();

	int		GetPlayerFov( APlayer* pPlayer );

	int		GetBestTarget();
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
	int		GetBestHitBox();
	void Junk();
	void Junk2();
	void Junk3();

	void	OnRender();

	void	Aimbot();
	void	AimbotSet();

	void	AutoPistol();
	void aimAtPlayer(CUserCmd * pCmd);
	void	OnCreateMove( CUserCmd* pCmd , CMe* pLocal );
//[/swap_lines]
private:

	CMe*		m_pLocal;
	CUserCmd*	m_pCmd;

	int		m_iBestPreTarget;

	int		m_iBestTarget;
	int		m_iBestHitbox;

	bool	m_bClamp;
	bool	m_bAttack;
	bool	m_bAimShot;
	bool	m_bTargetFov;
	bool	m_bTargetChange;
	bool	m_bAutoPistolEn;

	CTimer*	m_pShotDelay;

	Vector	m_vAimBestHitbox;
	Vector  m_vAimBestHitboxScreen;
};