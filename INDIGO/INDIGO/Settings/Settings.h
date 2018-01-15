#pragma once

#include "../Main/Main.h"

#define FIX_MIN_FOV_HEAD	30
#define FIX_MIN_FOV_CHEST	50
#define FOV_BASE_DISTANCE	200

namespace Settings
{
	extern QAngle qLastTickAngle;
	extern float hitmarkerAlpha;

	void LoadSettings( string szIniFile );
	void SaveSettings( string szIniFile );

	extern bool legitTab;
	extern bool visualsTab;
	extern bool miscTab;
	extern bool colorsTab;
	extern bool configTab;

	namespace Aimbot
	{
		struct weapon_aim_s
		{
			//[swap_lines]
			bool aim_Active;
			int aim_Smooth;
			int aim_Fov;
			int aim_FovType;
			int aim_BestHit;
			int aim_Spot;
			int aim_Delay;
			int aim_Rcs;
			int aim_RcsFov;
			int aim_RcsSmooth;
			int aim_RcsClampType;
			bool aim_AutoPistol;
			//[/swap_lines]
		};
		//[swap_lines]
		extern bool aim_Deathmatch;
		extern bool aim_WallAttack;
		extern bool aim_CheckSmoke;
		extern bool aim_AntiJump;
		extern int aim_RcsType;
		extern bool aim_DrawFov;
		extern bool aim_DrawSpot;
		
		extern weapon_aim_s weapon_aim_settings[33];
		//[/swap_lines]
	}

	namespace Esp
	{
		//[swap_lines]
		extern int esp_Style; // 0 - Box 1 - CoalBox
		extern int esp_Size;
		extern bool esp_Outline; // Box ( 0 - Box 1 - OutlineBox ) ,
						  // CoalBox ( 0 - CoalBox 1 - OutlineCoalBox )	

		extern bool esp_Name;
		extern bool esp_Rank;
		extern int esp_Health;
		extern bool esp_Weapon;
		extern bool esp_Time;
		extern bool esp_Rainbow;
		extern float esp_RainbowSpeed;

		extern bool esp_Radar;
		extern bool esp_Team;
		extern bool esp_Enemy;
		extern int esp_Visible;
		extern bool esp_HitMarker;
		extern int esp_HitMarkerSound;
		extern float esp_HitMarkerColor[3];
		extern float esp_DilightColor[3];

		extern int esp_Chams;
		extern bool esp_Bomb;
		extern int esp_BombTimer;
		extern bool esp_WorldWeapons;
		extern bool esp_WorldGrenade;

		extern float esp_Color_CT[3];
		extern float esp_Color_TT[3];
		extern float esp_Color_VCT[3];
		extern float esp_Color_VTT[3];

		extern float chams_Color_CT[3];
		extern float chams_Color_TT[3];
		extern float chams_Color_VCT[3];
		extern float chams_Color_VTT[3];
		//[/swap_lines]
	}

	namespace Skin
	{
		//[swap_lines]
		extern int knf_ct_model;
		extern int knf_ct_skin;
		extern int knf_tt_model;
		extern int knf_tt_skin;
		extern int gloves_skin;
		//[/swap_lines]
	}

	namespace Misc
	{
		//[swap_lines]
		extern bool misc_Bhop;
		extern bool misc_AutoStrafe;
		extern int misc_ArmMaterialsList;
		extern bool misc_ArmMaterials;
		extern int misc_ChamsMaterialsList;
		extern bool misc_ChamsMaterials;
		extern int misc_ArmMaterialsType;
		extern const char* misc_SkyName;
		extern int misc_CurrentSky;
		extern bool misc_SkyboxChanger;
		extern bool misc_BacktrackDraw;
		extern float misc_BacktrackTicks;
		extern bool misc_RainbowMenu;
		extern float misc_RainbowSpeed;
		extern bool misc_EPostprocess;
		extern bool misc_NameStealer;
		extern bool misc_Fakelag;
		extern bool misc_FakelagAdaptive;
		extern int misc_FakelagAmount;
		extern bool misc_ThirdPerson;
		extern float misc_ThirdPersonRange;
		extern bool misc_sv_cheats;
		extern int misc_PostEnableValue;
		extern bool misc_SkinChanger;
		extern bool misc_KnifeChanger;
		extern bool misc_Backtrack;
		extern bool misc_NoHands;
		extern bool misc_WireHands;
		extern bool misc_NoWeapon;
		extern bool misc_AwpAim;		
		extern bool misc_FovChanger;
		extern int misc_FovView;
		extern float misc_AwpAimColor[3];
		extern float misc_MenuColor[3];
		extern float misc_TextColor[3];
		//[/swap_lines]
	}

}

//[enc_string_enable /]

#define LEGITBOT_TEXT "Legit"
#define TRIGGER_TEXT "Triggerbot"
#define CONFIG_TEXT "Config"
#define VISUAL_TEXT "Visuals"
#define SKIN_TEXT "Skins"
#define MISC_TEXT "Misc"
#define COLORS_TEXT "Colors"

#define CVAR_AIMBOT_DEATHMATCH "aim_Deathmatch"
#define CVAR_AIMBOT_WALLATTACK "aim_WallAttack"
#define CVAR_AIMBOT_CHECKSMOKE "aim_CheckSmoke"
#define CVAR_AIMBOT_ANTIJUMP	"aim_IgnoreJump"
#define CVAR_AIMBOT_RCSTYPE "aim_RcsType"
#define CVAR_AIMBOT_DRAWFOV "aim_DrawFov"
#define CVAR_AIMBOT_DRAWSPOT "aim_DrawSpot"

#define CVAR_AIMBOT_ACTIVE "aim_Active"
#define CVAR_AIMBOT_SMOOTH "aim_Smooth"
#define CVAR_AIMBOT_FOV "aim_Fov"
#define CVAR_AIMBOT_FOVTYPE "aim_FovType"
#define CVAR_AIMBOT_BESTHIT "aim_BestHit"
#define CVAR_AIMBOT_SPOT "aim_Spot"
#define CVAR_AIMBOT_DELAY "aim_Delay"

#define CVAR_AIMBOT_RCS "aim_Rcs"
#define CVAR_AIMBOT_RCSFOV "aim_RcsFov"
#define CVAR_AIMBOT_RCSSMOOTH "aim_RcsSmooth"
#define CVAR_AIMBOT_RCSCLAMPTYPE "aim_RcsClampType"
#define CVAR_AIMBOT_AUTOPISTOL "aim_AutoPistol"

#define CVAR_TRIGGER_ENABLED "triggerbot: enabled"
#define CVAR_TRIGGER_DISABLED "triggerbot: disabled"

#define CVAR_TRIGGER_ENABLE "trigger_Enable"
#define CVAR_TRIGGER_DEATHMATCH "trigger_Deathmatch"
#define CVAR_TRIGGER_WALLATTACK "trigger_WallAttack"
#define CVAR_TRIGGER_FASTZOOM "trigger_FastZoom"
#define CVAR_TRIGGER_KEY "trigger_Key"
#define CVAR_TRIGGER_KEYMODE "trigger_KeyMode"
#define CVAR_TRIGGER_SMOKCHECK "trigger_SmokCheck"
#define CVAR_TRIGGER_DRAWFOV "trigger_DrawFov"
#define CVAR_TRIGGER_DRAWSPOT "trigger_DrawSpot"
#define CVAR_TRIGGER_DRAWFOVASSIST "trigger_DrawFovAssist"

#define CVAR_TRIGGER_DISTANCEMIN "trigger_DistanceMin"
#define CVAR_TRIGGER_DISTANCEMAX "trigger_DistanceMax"
#define CVAR_TRIGGER_FOV "trigger_Fov"
#define CVAR_TRIGGER_DELAYBEFORE "trigger_DelayBefore"
#define CVAR_TRIGGER_DELAYAFTER "trigger_DelayAfter"
#define CVAR_TRIGGER_HEADONLY "trigger_HeadOnly"
#define CVAR_TRIGGER_HITGROUP "trigger_HitGroup"
#define CVAR_TRIGGER_ASSIST "trigger_Assist"
#define CVAR_TRIGGER_ASSISTRCS "trigger_AssistRcs"
#define CVAR_TRIGGER_ASSISTFOV "trigger_AssistFov"
#define CVAR_TRIGGER_ASSISTFOVTYPE "trigger_AssistFovType"
#define CVAR_TRIGGER_ASSISTSMOOTH "trigger_AssistSmooth"

#define CVAR_KEY_MOUSE3 "MOUSE3"
#define CVAR_KEY_MOUSE4 "MOUSE4"
#define CVAR_KEY_MOUSE5 "MOUSE5"

#define CVAR_ESP_STYLE "esp_Style"
#define CVAR_ESP_SIZE "esp_Size"
#define CVAR_ESP_OUTLINE "esp_Outline"
#define CVAR_ESP_NAME "esp_Name"
#define CVAR_ESP_RANK "esp_Rank"

#define CVAR_ESP_HEALTH "esp_Health"
#define CVAR_ESP_WEAPON "esp_Weapon"

#define CVAR_ESP_RADAR "esp_Radar"
#define CVAR_ESP_TEAM "esp_Team"
#define CVAR_ESP_ENEMY "esp_Enemy"
#define CVAR_ESP_VISIBLE "esp_Visible"

#define CVAR_ESP_CHAMS "esp_Chams"
#define CVAR_ESP_BOMB "esp_Bomb"
#define CVAR_ESP_BOMBTIMER "esp_BombTimer"
#define CVAR_ESP_WORLDWEAPONS "esp_WorldWeapons"
#define CVAR_ESP_WORLDGRENADE "esp_WorldGrenade"

#define CVAR_ESP_COLOR_CT "esp_Color_CT"
#define CVAR_ESP_COLOR_TT "esp_Color_TT"
#define CVAR_ESP_COLOR_VCT "esp_Color_VCT"
#define CVAR_ESP_COLOR_VTT "esp_Color_VTT"

#define CVAR_CHAMS_COLOR_CT "chams_Color_CT"
#define CVAR_CHAMS_COLOR_TT "chams_Color_TT"
#define CVAR_CHAMS_COLOR_VCT "chams_Color_VCT"
#define CVAR_CHAMS_COLOR_VTT "chams_Color_VTT"

#define C4_TIMER_STRING "Bomb: %0.2f"

#define CVAR_SKIN_CT_MODEL "knf_ct_model"
#define CVAR_SKIN_CT_SKIN "knf_ct_skin"
#define CVAR_SKIN_TT_MODEL "knf_tt_model"
#define CVAR_SKIN_TT_SKIN "knf_tt_skin"
#define CVAR_SKIN_GLOVES "gloves_skin"

#define CVAR_MISC_EPOSTPROCESS "misc_EPostprocess"
#define CVAR_MISC_SKINCHANGER "misc_SkinChanger"
#define CVAR_MISC_KNIFECHANGER "misc_KnifeChanger"
#define CVAR_MISC_BACKTRACK "aim_Backtrack"
#define CVAR_MISC_NO_HANDS "misc_NoHands"
#define CVAR_MISC_AWPAIM "misc_AwpAim"
#define CVAR_MISC_FOV_CHANGER "misc_FovChanger"
#define CVAR_MISC_FOV_VIEW "misc_FovView"
#define CVAR_MISC_AWPAIM_COLOR "misc_AwpAimColor"
#define CVAR_MISC_MENU_COLOR "misc_MenuColor"
#define CVAR_MISC_TEXT_COLOR "misc_TextColor"