#pragma once

#include "Engine.h"

#define MAX_PLAYERS_SIZE 64

namespace Engine
{
	enum PLAYER_TEAM;
	enum WEAPON_TYPE;

	class CBaseEntity;

	class CMe
	{
	public:
//[swap_lines]
		bool			bAlive;
		bool			bInReload;

		int				iIndex;
		int				iFov;
		int				iFlags;
		int				iShotsFired;

		Vector			vAimPunch;
		Vector			vPunch;

		Vector			vEyeOrigin;

		string			WeaponName;
		WEAPON_TYPE		WeaponType;
		int				WeaponIndex;
		int				WeaponAmmo;

		PLAYER_TEAM		Team;

		CBaseEntity*	m_pEntity;
		ABaseWeapon*	m_pWeaponEntity;
//[/swap_lines]
	};

	class APlayer
	{
	public:
//[swap_lines]
		Vector			vHitboxHead;
		Vector			vHitboxHeadScreen;

		Vector			vTriggerHeadPos;
		Vector			vTriggerChestPos;

		Vector			vAssistTriggerHead;
		Vector			vAssistTriggerChest;

		Vector			vOrigin;
		Vector			vOriginScreen;

		Vector			vHitboxSkeletonArray[18][2];
		Vector			vBulletTraceArray[2];

		string			Name;
		string			WeaponName;

		PLAYER_TEAM		Team;

		int				iHealth;
		int				iArmor;
		int				iWAmmo;
		int				iDistance;

		float			fDistanceHead;
		float			fDistanceChest;

		bool			bUpdate;
		bool			bVisible;

		bool			bAssistFov;
		bool			bTriggerFov;

		CBaseEntity*	m_pEntity;
//[/swap_lines]
	};

	class APlayers
	{
	public:
		APlayers();
		~APlayers();
//[swap_lines]
		CMe*		GetLocal();
		APlayer*	GetPlayer( BYTE Index );
		BYTE		GetSize();

		bool		UpdateLocal();
		void		Update();
		void		Clear();

		void		GetHitBoxSkeleton( int nHitBoxOne , int nHitBoxTwo , CBaseEntity* pEntity , Vector* vOut );
//[/swap_lines]
	private:
		CMe*		m_pMe;
		APlayer*	m_pPlayers;
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
	};
}