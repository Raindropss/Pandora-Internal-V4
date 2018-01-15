#include "Hook.h"
#include <ctime>
#include <Windows.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <conio.h>
#include <vector>

//[enc_string_enable /]
//[junk_enable /]

AMisc* g_pMisc;

bool once = true;
bool once1 = false;
int width1 = 0;
int height1 = 0;

namespace Engine
{
	namespace Hook
	{
		CSX::Hook::VTable IDirect3DDevice9Table;
		CSX::Hook::VTable ClientModeTable;
		CSX::Hook::VTable GameEventTable;
		CSX::Hook::VTable ModelRenderTable;
		CSX::Hook::VTable ClientTable;
		CSX::Hook::VTable SurfaceTable;

		IDirect3DDevice9* g_pDevice = nullptr;

		typedef HRESULT( WINAPI* Present_t )( IDirect3DDevice9* pDevice , CONST RECT* pSourceRect , CONST RECT* pDestRect , HWND hDestWindowOverride , CONST RGNDATA* pDirtyRegion );
		Present_t Present_o;

		typedef HRESULT( WINAPI* Reset_t )( LPDIRECT3DDEVICE9 pDevice , D3DPRESENT_PARAMETERS* pPresentationParameters );
		Reset_t Reset_o;

		HRESULT WINAPI Hook_Present( IDirect3DDevice9* pDevice , CONST RECT* pSourceRect , CONST RECT* pDestRect , HWND hDestWindowOverride , CONST RGNDATA* pDirtyRegion )
		{
			Client::OnRender();
			return Present_o( pDevice , pSourceRect , pDestRect , hDestWindowOverride , pDirtyRegion );
		}

		HRESULT WINAPI Hook_Reset( LPDIRECT3DDEVICE9 pDevice , D3DPRESENT_PARAMETERS* pPresentationParameters )
		{		
			Client::OnLostDevice();
			
			HRESULT hRes = Reset_o( pDevice , pPresentationParameters );
			
			Client::OnResetDevice();
			
			return hRes;
		}

		bool WINAPI Hook_CreateMove( float flInputSampleTime , CUserCmd* pCmd )
		{
			ClientModeTable.UnHook();

			if (Interfaces::Engine()->IsConnected() || Interfaces::Engine()->IsInGame() && Settings::Misc::misc_ThirdPerson)
			{
				PVOID pebp;

				__asm mov pebp, ebp;

				bool* pbSendPacket = (bool*)(*(DWORD*)pebp - 0x1C);
				bool& bSendPacket = *pbSendPacket;

				if (bSendPacket)
					Settings::qLastTickAngle = pCmd->viewangles;
			}

			Client::OnCreateMove( pCmd );
			
			bool ret = Interfaces::ClientMode()->CreateMove( flInputSampleTime , pCmd );

			ClientModeTable.ReHook();
			return ret;
		}

		bool WINAPI Hook_OverrideView( CViewSetup* pSetup )
		{
			Client::OnOverrideView( pSetup );

			ClientModeTable.UnHook();
			bool ret = Interfaces::ClientMode()->OverrideView( pSetup );
			ClientModeTable.ReHook();
			return ret;
		}

		bool WINAPI Hook_FireEventClientSideThink( IGameEvent* pEvent )
		{
			bool ret = false;
			
			if ( !pEvent )
			{
				GameEventTable.UnHook();
				ret = Interfaces::GameEvent()->FireEventClientSide( pEvent );
				GameEventTable.ReHook();
				return ret;
			}
			
			Client::OnFireEventClientSideThink( pEvent );
			
			GameEventTable.UnHook();
			ret = Interfaces::GameEvent()->FireEventClientSide( pEvent );
			GameEventTable.ReHook();
			
			return ret;
		}

		void WINAPI Hook_FrameStageNotify(ClientFrameStage_t Stage)
		{
			Client::OnFrameStageNotify(Stage);

			ClientTable.UnHook();
			Interfaces::Client()->FrameStageNotify(Stage);
			ClientTable.ReHook();
		}

		void junk2924892807264103() {
			return;
			float mh6rpk;
			float qc7dre;
			float ge8ixe;
			while (qc7dre == 4707911105792498)
			{
				qc7dre = 6501597454705227;
			}
			mh6rpk = 4904669471838694;
			if (qc7dre == 5289349581413675)
				qc7dre = 4458028482381693;
			ge8ixe = 9577834880633460;
			if (mh6rpk == 6107252675211120)
				mh6rpk = 5829250007805290;
			mh6rpk = 147436324720007.53;
		}
		void junk3842358212273137() {
			return;
			float rel4wo;
			float yktus;
			float pdor8t;
			pdor8t = 8304093533799171;
			yktus = 5084950030591507;
			for (int mxdhpa = 0; mxdhpa > 100; mxdhpa++)
			{
				rel4wo = 6700642110503399;
			}
			rel4wo = 6333717230195325;
		}
		void junk8923323598610622() {
			return;
			float h9toor;
			float xvutze;
			float xmqqwc;
			if (xvutze == 2682748798251333)
				xvutze = 7621481710957748;
			xvutze = 1719872113518176.8;
			while (h9toor == 1704314001867776)
			{
				h9toor = 2313556910686231.5;
			}
			xmqqwc = 8120035605494103;
			for (int fgl7hb = 0; fgl7hb > 100; fgl7hb++)
			{
				h9toor = 687531332060831.5;
			}
			xmqqwc = 9713768368882552;
		}
		void junk7201131302496908() {
			return;
			float ry2wo;
			float g82w7;
			float w1uvv;
			for (int ty3bb8 = 0; ty3bb8 > 100; ty3bb8++)
			{
				ry2wo = 5548375580563772;
			}
			w1uvv = 7492587202275287;
			for (int jwi85c = 0; jwi85c > 100; jwi85c++)
			{
				ry2wo = 4616978964445775;
			}
			w1uvv = 9444296692158596;
			for (int y8qvov = 0; y8qvov > 100; y8qvov++)
			{
				ry2wo = 7742481807308670;
			}
			g82w7 = 6615662766008338;
		}
		void junk6076883333228007() {
			return;
			float aeynne;
			float azel2g;
			float qiyx2;
			while (aeynne == 3342180013718761.5)
			{
				aeynne = 6135416350021436;
			}
			aeynne = 8669890448555288;
			if (qiyx2 == 5289516143592964)
				qiyx2 = 9228879586476080;
			qiyx2 = 10091688295782722;
			if (azel2g == 3286046169745757.5)
				azel2g = 6479620388252939;
			qiyx2 = 1793113751606210;
		}
		void junk7218906731186566() {
			return;
			float wzez8;
			float rrp42b;
			float kzn7ce;
			while (kzn7ce == 8853493127972056)
			{
				kzn7ce = 1817219730488390.8;
			}
			kzn7ce = 9099264050576776;
			while (wzez8 == 4876807434607207)
			{
				wzez8 = 8801933018069904;
			}
			kzn7ce = 4425528711655583;
			rrp42b = 1702256297853311.8;
		}
		void junk1969242126081483() {
			return;
			float wlmf4y;
			float r4u6s;
			float l5n48b;
			if (l5n48b == 2039350259163623.2)
				l5n48b = 5781858099956055;
			l5n48b = 10043179446462506;
			for (int k87vq = 0; k87vq > 100; k87vq++)
			{
				wlmf4y = 3451394456760298;
			}
			l5n48b = 7729844849908934;
			for (int jls2vl = 0; jls2vl > 100; jls2vl++)
			{
				wlmf4y = 1203649117435693;
			}
			l5n48b = 4737771066724989;
		}
		void junk6772161010268382() {
			return;
			float mjc6ah;
			float cmx6ok;
			float xnbdj6;
			while (mjc6ah == 4996550139890524)
			{
				mjc6ah = 7540938470127806;
			}
			cmx6ok = 5510279986005835;
			while (mjc6ah == 807580516096075.8)
			{
				mjc6ah = 7375957999493440;
			}
			xnbdj6 = 4072756607544045;
			cmx6ok = 7930882457915106;
		}
		void junk7251967585151089() {
			return;
			float cujyk;
			float vh8h8j;
			float kly8ul;
			for (int s907ei = 0; s907ei > 100; s907ei++)
			{
				cujyk = 7637573831146632;
			}
			cujyk = 8314378589698559;
			if (kly8ul == 653916862838205.4)
				kly8ul = 6666351366006708;
			kly8ul = 4103322007563944;
			kly8ul = 632925968143334.5;
		}
		void junk781867128847778() {
			return;
			float u6520p;
			float ld1h1;
			float moputa;
			u6520p = 4260877946110030;
			if (ld1h1 == 3947262049109767.5)
				ld1h1 = 2184544650765078.2;
			ld1h1 = 7010786667908557;
			while (u6520p == 2362236576979909.5)
			{
				u6520p = 9555525148333750;
			}
			ld1h1 = 2439727027459575.5;
		}
		void junk8883112312885516() {
			return;
			float vylzyi;
			float ohs7j;
			float vi04v;
			ohs7j = 7551166459963832;
			if (vylzyi == 5045332138641650)
				vylzyi = 193729598942644.16;
			vi04v = 4317430946267989.5;
			while (vi04v == 2982030428959562)
			{
				vi04v = 1273670465817982.8;
			}
			vi04v = 10133886750927738;
		}
		void junk9409252796110602() {
			return;
			float dv3lzc;
			float gw8q2o;
			float mpmymo;
			if (mpmymo == 8012058196663836)
				mpmymo = 3681060957291531;
			gw8q2o = 8967429280972543;
			while (gw8q2o == 2172676041574745)
			{
				gw8q2o = 5995280938912902;
			}
			dv3lzc = 1624249077442533.8;
			while (gw8q2o == 8186011855413281)
			{
				gw8q2o = 4538792859339449;
			}
			mpmymo = 3269294343391274.5;
		}
		void junk5179295748494885() {
			return;
			float lxtff;
			float k6ueo;
			float h3aoxq;
			lxtff = 5281827048143518;
			while (lxtff == 6239836903737756)
			{
				lxtff = 7765731383187559;
			}
			k6ueo = 1436680599009872.2;
			k6ueo = 1326680972135089;
		}
		void junk3227232369667892() {
			return;
			float bczirx;
			float vxeln9;
			float aoeffx;
			if (vxeln9 == 3456922046992967.5)
				vxeln9 = 4505440516656544;
			aoeffx = 4789709330090254;
			while (vxeln9 == 3196821628774385.5)
			{
				vxeln9 = 8423479175064879;
			}
			bczirx = 5182758109166104;
			bczirx = 5355698647170753;
		}

		void WINAPI Hook_DrawModelExecute( IMatRenderContext* ctx , const DrawModelState_t &state , 
										   const ModelRenderInfo_t &pInfo , matrix3x4_t *pCustomBoneToWorld = NULL )
		{			
			ModelRenderTable.UnHook();
			
			if ( ctx && pCustomBoneToWorld )
				Client::OnDrawModelExecute( ctx , state , pInfo , pCustomBoneToWorld );

			Interfaces::ModelRender()->DrawModelExecute( ctx , state , pInfo , pCustomBoneToWorld );

			if ( ctx && pCustomBoneToWorld && Client::g_pEsp && Settings::Esp::esp_Chams )
			{
				Interfaces::ModelRender()->ForcedMaterialOverride( 0 );
			}
			
			ModelRenderTable.ReHook();			
		}

		bool Initialize()
		{	
			if ( !CSX::Utils::IsModuleLoad( D3D9_DLL ) )
				return false;

			if ( !CSX::Utils::IsModuleLoad( SHADERPIDX9_DLL ) )
				return false;

			if ( !CSX::Utils::IsModuleLoad( GAMEOVERLAYRENDERER_DLL ) )
				return false;

			DWORD d3d9TablePtrPtr = CSX::Memory::FindPattern( SHADERPIDX9_DLL , D3D9_PATTERN , D3D9_MASK , 1 );
			DWORD_PTR** dwPresent_o = (DWORD_PTR**)CSX::Memory::FindPattern( GAMEOVERLAYRENDERER_DLL , GMOR_PATTERN , GMOR_MASK , 1 );

			if ( d3d9TablePtrPtr && dwPresent_o )
			{				
				g_pDevice = (IDirect3DDevice9*)( **(PDWORD*)d3d9TablePtrPtr );
				
				if ( IDirect3DDevice9Table.InitTable( g_pDevice ) )
				{					
					DWORD_PTR* dwAddress = *dwPresent_o;
					Present_o = (Present_t)( *dwAddress );
					*dwAddress = (DWORD_PTR)( &Hook_Present );

					Reset_o = (Reset_t)IDirect3DDevice9Table.GetHookIndex( D3D9::TABLE::Reset , Hook_Reset );

					if ( !ClientModeTable.InitTable( Interfaces::ClientMode() ) )
						return false;

					ClientModeTable.HookIndex( TABLE::IClientMode::CreateMove , Hook_CreateMove );
					ClientModeTable.HookIndex( TABLE::IClientMode::OverrideView , Hook_OverrideView );

					if ( !GameEventTable.InitTable( Interfaces::GameEvent() ) )
						return false;

					GameEventTable.HookIndex( TABLE::IGameEventManager2::FireEventClientSide , Hook_FireEventClientSideThink );

					if ( !ClientTable.InitTable( Interfaces::Client() ) )
						return false;

					ClientTable.HookIndex(TABLE::IBaseClientDLL::FrameStageNotify, Hook_FrameStageNotify);

					if ( !ModelRenderTable.InitTable( Interfaces::ModelRender() ) )
						return false;

					ModelRenderTable.HookIndex( TABLE::IVModelRender::DrawModelExecute , Hook_DrawModelExecute );

					if ( !SurfaceTable.InitTable( Interfaces::Surface() ) )
						return false;

					if ( Client::Initialize( g_pDevice ) )
						return true;
				}
			}

			return false;
		}

		void Shutdown()
		{
			IDirect3DDevice9Table.UnHook();
			ClientModeTable.UnHook();
			GameEventTable.UnHook();
			ModelRenderTable.UnHook();
			ClientTable.UnHook();
		}
}
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class airxwqp {
public:
	bool ngjhcrhk;
	double wlwfdybuhidkd;
	bool ejptlnumoh;
	airxwqp();
	bool mibcjxwbuzxjjsl(int rcdqvnyzepdv, double yaypheoercq, string dppeabihc, bool bdyptbuoequp);
	double ymtibcdkpcgbwnkyhurunbs(bool ilfsnlkktqbwg);
	bool jqwqqjnwooyojtmhhutyn();
	bool tbxytotbpcgxi(bool sjsdggrdb, int domncn, double ajdubcxfzdwpvk, int pyjtilkzhixnbo, double pjwiporvd, int kktkxgkzsha, double fyvcbrtry, bool gseclwylxwdpz, double pjssfwsa);
	int volafhyphgohjyeulbgsblyl(int lmzrtphokursp, bool wgowfwxxfntm, string nctebeacqb, string qltguayfim, int kdiosmasggc, bool nynbolfaewfl);

protected:
	string iuezozudu;

	int qufomgpghhporejxoegedxfn(bool eiavvhyu, bool xdndk, string gkqmgdyybrfn);
	double iqvhwcproqhahuwfql(int lxehw, double qxkhntfeibni, string uepjwelia, bool mvlzrvturgcwwa);
	double jkuvzedchqyinctm(int ancyruxtznkk, bool ccryrqapoh);
	double tjbicnkyfcxmgtjbcrrbdo(bool zhylxxo, double ngaebbyze, string jbnqvbr, bool osjncmaaay, bool qucsoiiicox, double gvtjad);
	int ofskqfzqohhennz(bool lewhdhjvessbho, int uftonvqi, bool adlzlnhsduarph, int utrvkolhw, bool huviz);
	double avyowdoiyplhxo(string omauzpfdzgmmnn, string pzzojjoahyhyjz, int kbummktvampha, double groenfflalrxc, int xnorygmll, int iwnpke, int scthhvgithjfbi, int qblnpukpjy);
	double nofjvuzaowsrzor(int lkipxeolubqry, bool sokgf, string izfeukftcfi, int ewdlevtcfvfr, int luoyzzdiyevg, bool rwcjigkmsya);
	bool vgrxillfvwuqatdz(string ribkna, bool ofkyd);
	int vkfwsgbzgt(double mkhxypx, int pymutubtngdui, double txccra);

private:
	string pmfdtzqez;

	string rjxadfwbmepjrwnknknuo(double uwqqp, int ftfge, double tqeayfymnbmko, string javanhwdw, int belxuodvprkie, bool dwhsaxgna, string lgglzpux, bool azhoezgtqlmjopc, double pwuifhxlwcqs, int ctvnienrfyhvidz);
	void ahzsejnqqgqqqaajsabv(bool ifjtdrqmpqqwkjv, double occsevsrngzsux, bool wsuufylgpatm, string jipcdzny, string ifatskkuts, string jvzlmna, double wglzupmemb, string bdoxmljtxqsj);
	string gdpjgphiedrpfafwm(string zotznmvzooh, string yisnoxr, bool pdvba, string szsjq, double hwypfmoyzhft, bool iyrinrdygmzhwl, string jnudibutyrfily, bool cxnrpwxyehxv, string bgknmvzg);

};


string airxwqp::rjxadfwbmepjrwnknknuo(double uwqqp, int ftfge, double tqeayfymnbmko, string javanhwdw, int belxuodvprkie, bool dwhsaxgna, string lgglzpux, bool azhoezgtqlmjopc, double pwuifhxlwcqs, int ctvnienrfyhvidz) {
	string apprewqlvhagg = "eyvyemiikkysytp";
	int bxbdokxkt = 734;
	bool jqvqrajjsc = false;
	string obljzr = "ohffpzxujcyytixfnjdwsdcfczgdcaucklalpfvejqohuqw";
	double dsgeivzvmlc = 54916;
	bool ohggikhor = true;
	if (false == false) {
		int itsyayntok;
		for (itsyayntok = 96; itsyayntok > 0; itsyayntok--) {
			continue;
		}
	}
	if (string("eyvyemiikkysytp") != string("eyvyemiikkysytp")) {
		int tywjejv;
		for (tywjejv = 39; tywjejv > 0; tywjejv--) {
			continue;
		}
	}
	if (734 == 734) {
		int aycirlp;
		for (aycirlp = 17; aycirlp > 0; aycirlp--) {
			continue;
		}
	}
	if (true == true) {
		int szxsfzujw;
		for (szxsfzujw = 94; szxsfzujw > 0; szxsfzujw--) {
			continue;
		}
	}
	return string("qenijclagxhhgbiohcw");
}

void airxwqp::ahzsejnqqgqqqaajsabv(bool ifjtdrqmpqqwkjv, double occsevsrngzsux, bool wsuufylgpatm, string jipcdzny, string ifatskkuts, string jvzlmna, double wglzupmemb, string bdoxmljtxqsj) {

}

string airxwqp::gdpjgphiedrpfafwm(string zotznmvzooh, string yisnoxr, bool pdvba, string szsjq, double hwypfmoyzhft, bool iyrinrdygmzhwl, string jnudibutyrfily, bool cxnrpwxyehxv, string bgknmvzg) {
	string daywpsgyhp = "ncdqysezxrgezihbnhaahysqlnjowrlantqvwihdcmaurxxwayhlhvxisuzrgnbqemsczskrvmicuobbzfxj";
	int bimco = 894;
	bool zfcqxeid = true;
	int vygbfcpiqdpcaaj = 3368;
	bool tnblvkmlc = true;
	int rjpxkiiwlbd = 227;
	int tdivpkhdayhe = 350;
	int gxfalb = 1351;
	if (true == true) {
		int igbrpa;
		for (igbrpa = 33; igbrpa > 0; igbrpa--) {
			continue;
		}
	}
	if (1351 == 1351) {
		int xw;
		for (xw = 95; xw > 0; xw--) {
			continue;
		}
	}
	if (894 == 894) {
		int srqqccxopd;
		for (srqqccxopd = 32; srqqccxopd > 0; srqqccxopd--) {
			continue;
		}
	}
	return string("krduu");
}

int airxwqp::qufomgpghhporejxoegedxfn(bool eiavvhyu, bool xdndk, string gkqmgdyybrfn) {
	double vszfvyy = 13025;
	string cndoglcyo = "klnjiks";
	int jslirzibm = 3310;
	double vwqhhuaysjovy = 2488;
	if (2488 == 2488) {
		int eiw;
		for (eiw = 64; eiw > 0; eiw--) {
			continue;
		}
	}
	if (13025 != 13025) {
		int qrwg;
		for (qrwg = 35; qrwg > 0; qrwg--) {
			continue;
		}
	}
	if (13025 == 13025) {
		int kzdd;
		for (kzdd = 21; kzdd > 0; kzdd--) {
			continue;
		}
	}
	if (2488 != 2488) {
		int dqzqp;
		for (dqzqp = 44; dqzqp > 0; dqzqp--) {
			continue;
		}
	}
	return 68688;
}

double airxwqp::iqvhwcproqhahuwfql(int lxehw, double qxkhntfeibni, string uepjwelia, bool mvlzrvturgcwwa) {
	double qesqt = 27368;
	int vthnkyfjxdma = 2239;
	double dcoydjihbjm = 66481;
	if (2239 == 2239) {
		int leudsulla;
		for (leudsulla = 44; leudsulla > 0; leudsulla--) {
			continue;
		}
	}
	if (66481 != 66481) {
		int drggab;
		for (drggab = 88; drggab > 0; drggab--) {
			continue;
		}
	}
	if (66481 == 66481) {
		int fnato;
		for (fnato = 81; fnato > 0; fnato--) {
			continue;
		}
	}
	return 68514;
}

double airxwqp::jkuvzedchqyinctm(int ancyruxtznkk, bool ccryrqapoh) {
	return 12687;
}

double airxwqp::tjbicnkyfcxmgtjbcrrbdo(bool zhylxxo, double ngaebbyze, string jbnqvbr, bool osjncmaaay, bool qucsoiiicox, double gvtjad) {
	string gclyehllfrnza = "feymmiwduwawttuxpegl";
	int fshljnzpp = 2557;
	double dytxlqni = 64831;
	if (64831 == 64831) {
		int cf;
		for (cf = 76; cf > 0; cf--) {
			continue;
		}
	}
	if (2557 != 2557) {
		int pmbvv;
		for (pmbvv = 34; pmbvv > 0; pmbvv--) {
			continue;
		}
	}
	if (64831 != 64831) {
		int hddghvlcwz;
		for (hddghvlcwz = 18; hddghvlcwz > 0; hddghvlcwz--) {
			continue;
		}
	}
	if (2557 != 2557) {
		int bvuvi;
		for (bvuvi = 41; bvuvi > 0; bvuvi--) {
			continue;
		}
	}
	return 60721;
}

int airxwqp::ofskqfzqohhennz(bool lewhdhjvessbho, int uftonvqi, bool adlzlnhsduarph, int utrvkolhw, bool huviz) {
	string ljkbv = "inzdtghjetmaeiobuixswbwwibwpmucaaooworlllstsgoxdjfschgzzsochvcgzojclgvswlklzoelccvqxqhtxixkq";
	string eiixfruoo = "nowtxwioclrokmpdgb";
	double qtdsgif = 18770;
	double lkytdr = 957;
	return 67769;
}

double airxwqp::avyowdoiyplhxo(string omauzpfdzgmmnn, string pzzojjoahyhyjz, int kbummktvampha, double groenfflalrxc, int xnorygmll, int iwnpke, int scthhvgithjfbi, int qblnpukpjy) {
	return 2292;
}

double airxwqp::nofjvuzaowsrzor(int lkipxeolubqry, bool sokgf, string izfeukftcfi, int ewdlevtcfvfr, int luoyzzdiyevg, bool rwcjigkmsya) {
	int igcamnj = 2414;
	double udxsga = 19220;
	bool lrcuslky = true;
	string sqkgiv = "uujzmfdbazkpivwzsushnjnpz";
	string nmmwvgiolbotl = "cjmzyhpufqqebrglyuqucqzokjlpjhfndwctwfh";
	if (string("cjmzyhpufqqebrglyuqucqzokjlpjhfndwctwfh") == string("cjmzyhpufqqebrglyuqucqzokjlpjhfndwctwfh")) {
		int oxqeuiil;
		for (oxqeuiil = 61; oxqeuiil > 0; oxqeuiil--) {
			continue;
		}
	}
	if (2414 == 2414) {
		int gfnfkvy;
		for (gfnfkvy = 34; gfnfkvy > 0; gfnfkvy--) {
			continue;
		}
	}
	if (string("uujzmfdbazkpivwzsushnjnpz") != string("uujzmfdbazkpivwzsushnjnpz")) {
		int moouq;
		for (moouq = 87; moouq > 0; moouq--) {
			continue;
		}
	}
	if (true != true) {
		int mycy;
		for (mycy = 41; mycy > 0; mycy--) {
			continue;
		}
	}
	return 15345;
}

bool airxwqp::vgrxillfvwuqatdz(string ribkna, bool ofkyd) {
	string uegwflcve = "yelrnsgb";
	int hoczdmitdpob = 6136;
	int nbjkhrxy = 685;
	string ksiqajh = "sqnihmrekgpnbxdkekhdwlzsdzpgzuqbnqkcfcxkdlcqzbxdjayhvgeunqslekuuakywzzjklyhxkvpphvvollhd";
	double cqsbjnszvsxyzvo = 2233;
	double yqzre = 21167;
	int trgmbs = 4172;
	string dfinvvhqu = "xxdcysndvkysvbzvudrlxpkhepykauyowkhzvqqozssgfghsc";
	if (685 == 685) {
		int mircws;
		for (mircws = 83; mircws > 0; mircws--) {
			continue;
		}
	}
	if (4172 != 4172) {
		int muzv;
		for (muzv = 19; muzv > 0; muzv--) {
			continue;
		}
	}
	if (6136 == 6136) {
		int wgar;
		for (wgar = 70; wgar > 0; wgar--) {
			continue;
		}
	}
	if (4172 != 4172) {
		int unaamcknqs;
		for (unaamcknqs = 30; unaamcknqs > 0; unaamcknqs--) {
			continue;
		}
	}
	if (string("sqnihmrekgpnbxdkekhdwlzsdzpgzuqbnqkcfcxkdlcqzbxdjayhvgeunqslekuuakywzzjklyhxkvpphvvollhd") != string("sqnihmrekgpnbxdkekhdwlzsdzpgzuqbnqkcfcxkdlcqzbxdjayhvgeunqslekuuakywzzjklyhxkvpphvvollhd")) {
		int vtdqce;
		for (vtdqce = 10; vtdqce > 0; vtdqce--) {
			continue;
		}
	}
	return false;
}

int airxwqp::vkfwsgbzgt(double mkhxypx, int pymutubtngdui, double txccra) {
	string hgndzcjpog = "pynzdcskyxxrzwhuhwviizefzeybcketoefvajgfloohuqrrseiwbtwtpgfvppgruahyoidfhvhyinfpxuljsmvtrxzhmbtpkwb";
	double asraqll = 20195;
	int rsogiead = 3443;
	if (string("pynzdcskyxxrzwhuhwviizefzeybcketoefvajgfloohuqrrseiwbtwtpgfvppgruahyoidfhvhyinfpxuljsmvtrxzhmbtpkwb") == string("pynzdcskyxxrzwhuhwviizefzeybcketoefvajgfloohuqrrseiwbtwtpgfvppgruahyoidfhvhyinfpxuljsmvtrxzhmbtpkwb")) {
		int adbtfrvlq;
		for (adbtfrvlq = 95; adbtfrvlq > 0; adbtfrvlq--) {
			continue;
		}
	}
	if (3443 == 3443) {
		int eymgupve;
		for (eymgupve = 38; eymgupve > 0; eymgupve--) {
			continue;
		}
	}
	if (3443 == 3443) {
		int xwbwmv;
		for (xwbwmv = 75; xwbwmv > 0; xwbwmv--) {
			continue;
		}
	}
	return 19455;
}

bool airxwqp::mibcjxwbuzxjjsl(int rcdqvnyzepdv, double yaypheoercq, string dppeabihc, bool bdyptbuoequp) {
	int kvysuwp = 2352;
	bool ngxgknvdka = true;
	double osqgfmzp = 3177;
	double yfpllvgdp = 82058;
	string nsjombxpwfkooe = "pjnxherjnkdqoplgezpbadvvwdga";
	bool zdciiqlhyed = true;
	bool bokuiwfyoftzsu = false;
	double vmksk = 14512;
	return false;
}

double airxwqp::ymtibcdkpcgbwnkyhurunbs(bool ilfsnlkktqbwg) {
	string tsnzvrrya = "vuvdbskmnbadivgzxsefsgyvbknetzojrfeakjebewfvbmtpukqquiiwxevjuaxidgysl";
	bool wwbiqulln = false;
	int yccghaxexqti = 5066;
	string jqfdsrj = "hdswtgqqjakwkuskpxcupdvnbjvzdhiufipzkzivpctitfkhnrgeassalojgmcztnhpspajhnkpxcil";
	bool xhkicoiebjmkw = true;
	int ucvwztvr = 6586;
	int odqquxq = 1924;
	double ghmxrwgvguh = 14290;
	bool rnfic = true;
	bool ehdxwyouhpv = false;
	return 72497;
}

bool airxwqp::jqwqqjnwooyojtmhhutyn() {
	int rotykgdysfswd = 2957;
	int hdzra = 6127;
	string focwemaiikhacw = "qrdvgisfrsxsfkvkehaeayjaoiipfskhta";
	bool gjieokiw = false;
	bool nmxivqgm = false;
	bool nccutvbzouifnmo = true;
	bool ftpfy = true;
	bool axtrgspssttz = false;
	if (true != true) {
		int ds;
		for (ds = 90; ds > 0; ds--) {
			continue;
		}
	}
	if (false == false) {
		int ynh;
		for (ynh = 78; ynh > 0; ynh--) {
			continue;
		}
	}
	return true;
}

bool airxwqp::tbxytotbpcgxi(bool sjsdggrdb, int domncn, double ajdubcxfzdwpvk, int pyjtilkzhixnbo, double pjwiporvd, int kktkxgkzsha, double fyvcbrtry, bool gseclwylxwdpz, double pjssfwsa) {
	string awrrqmfvioxzi = "tvybtkjkbavmuxzcjivgnkmuimyzbhpgjzinheskdhdr";
	int plbojcteotf = 330;
	bool hasxpfpvrvwuel = true;
	double demubrgxqdcsebu = 40463;
	double uzadoecsphz = 7196;
	bool snrknxqpopx = false;
	string hcfafd = "mnvagjdducmbijam";
	int ywkjff = 5771;
	double bbwkqrnkspqd = 8429;
	if (false != false) {
		int ta;
		for (ta = 100; ta > 0; ta--) {
			continue;
		}
	}
	if (string("tvybtkjkbavmuxzcjivgnkmuimyzbhpgjzinheskdhdr") == string("tvybtkjkbavmuxzcjivgnkmuimyzbhpgjzinheskdhdr")) {
		int vemami;
		for (vemami = 33; vemami > 0; vemami--) {
			continue;
		}
	}
	if (string("tvybtkjkbavmuxzcjivgnkmuimyzbhpgjzinheskdhdr") != string("tvybtkjkbavmuxzcjivgnkmuimyzbhpgjzinheskdhdr")) {
		int gwxznq;
		for (gwxznq = 24; gwxznq > 0; gwxznq--) {
			continue;
		}
	}
	if (7196 != 7196) {
		int uqt;
		for (uqt = 90; uqt > 0; uqt--) {
			continue;
		}
	}
	return false;
}

int airxwqp::volafhyphgohjyeulbgsblyl(int lmzrtphokursp, bool wgowfwxxfntm, string nctebeacqb, string qltguayfim, int kdiosmasggc, bool nynbolfaewfl) {
	string sbgcncl = "ugymvsdyfqfscopzquirirpomqitsrvvqzqnmbeu";
	if (string("ugymvsdyfqfscopzquirirpomqitsrvvqzqnmbeu") != string("ugymvsdyfqfscopzquirirpomqitsrvvqzqnmbeu")) {
		int upxja;
		for (upxja = 70; upxja > 0; upxja--) {
			continue;
		}
	}
	if (string("ugymvsdyfqfscopzquirirpomqitsrvvqzqnmbeu") == string("ugymvsdyfqfscopzquirirpomqitsrvvqzqnmbeu")) {
		int wmndyxiig;
		for (wmndyxiig = 4; wmndyxiig > 0; wmndyxiig--) {
			continue;
		}
	}
	return 47054;
}

airxwqp::airxwqp() {
	this->mibcjxwbuzxjjsl(3886, 9241, string("bafxzvquyjeopizidoogntuokojtjvvrwnjhypyudlhjdlnndglngzifjziz"), true);
	this->ymtibcdkpcgbwnkyhurunbs(false);
	this->jqwqqjnwooyojtmhhutyn();
	this->tbxytotbpcgxi(false, 1772, 38346, 3591, 68213, 782, 728, true, 30047);
	this->volafhyphgohjyeulbgsblyl(8078, false, string("oaxymhqnthacjzkjsdxvoslhqrnqtfpucagwpqumzvqywuyo"), string("vlkhjpdpfhaelihqhddrauplffejuneqsqhsuzr"), 1908, false);
	this->qufomgpghhporejxoegedxfn(true, false, string("bfiisifzdydyyjcmwzbmatxfvznuxzetsvfpnbqjkiexhvcmwradknkjtxbsgvlgin"));
	this->iqvhwcproqhahuwfql(608, 3120, string("xzdumiwgxdwblmrwfciioavdrzimtmpjxorwyu"), true);
	this->jkuvzedchqyinctm(7251, false);
	this->tjbicnkyfcxmgtjbcrrbdo(true, 51052, string("wbstihenqxpdmutficch"), false, true, 11001);
	this->ofskqfzqohhennz(true, 1510, false, 2978, false);
	this->avyowdoiyplhxo(string("irdewlq"), string("casctr"), 661, 18133, 2042, 2358, 8269, 2913);
	this->nofjvuzaowsrzor(2944, true, string("cnqghahzvznzytfughtikislysadwtbmttzskoaxsngcmvpmwjiokmcwrcocgnmftiyekmkyuryzeaptxswppsbrewblzg"), 1102, 3, true);
	this->vgrxillfvwuqatdz(string("cyexxprch"), false);
	this->vkfwsgbzgt(32670, 1571, 18207);
	this->rjxadfwbmepjrwnknknuo(69465, 1761, 57266, string("hkfwgboomlshdajuddwkssiazqaifeyxrkeix"), 5603, true, string("xmtppepkoyivccbhjmkflwbtotfcixkcnjjvfzkzunykrudptejjlpjjpgbaljuafkhnlaupcggbgafdzfo"), true, 25907, 3852);
	this->ahzsejnqqgqqqaajsabv(false, 28907, false, string("umzzkcjkmcdhopawmkpowurekjqsledgbhvicfskeqqtoaqpnchyjodndfgiju"), string("e"), string("wnhqzfedtuqgjzcfooomnytymtkrfevdlxzoczoqoogqkwcdeczxkwmxdkcjjnduhguphxehcvkycuvqvxyvnzrvlxfntl"), 22652, string("deyiqwwpvrohrwkksylbmaikovepreypghahfiqbjqvfrluxcgvphxggnoq"));
	this->gdpjgphiedrpfafwm(string("ojarlsyipcysjmkvsebvlsruafwznwveiiqunaczqgxntoyssylrfgmr"), string("clsxgrudaykhsvyemxcekdgjrnctnbthahxhcfuibyfznrrlnfbghkkbqkqtftpuclpzefxkpfdmlmjzoch"), false, string("dsyhtbilgnzzfanvnmkcxqvwyyscenaftspiizgzuqmqszxbcwixgopaiolugzfuoeanxfecajabviivorvrcmugu"), 46179, false, string("duqxfbbzmjxtlcrqrcdd"), false, string("edzzogqmaybvqelulzrkji"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class otkahcc {
public:
	bool dtjncgixgzsba;
	double xozxhdh;
	otkahcc();
	string tyacriviouxbt();
	void iqxveafdifmcycdg(bool xvrcyexm, int fidwilsopx);
	bool ndqafgxhurumatfsxwqufmd(int ispoo, double ejpjbul, int fntikckdfgk, string opbuhhegn);
	bool hanfjxfpkwkvjydbfjq(int thvvxgtgry, bool xvknpcmsdfmcis);

protected:
	double hstudavzkglx;
	bool qvwmeoie;
	double cenzaem;
	double ontshmrie;
	int tnfxkvpxpd;

	double kokkgllwcbbltkhewptiaqw(int kwoztvfeybu, int icgbpdosgqaewk, double xuelukzrrp, int wxjzslmybb, double jdikssvokgqs, string srhwcpwsv, double rlvzvraclhkyn, double kxshv, int jqhqjuyu, bool pytdmql);
	double pgeytacuwltxdijspj(string exrcb, bool vgmugsnam);

private:
	int jadtcbtebvl;
	string nfgkwnv;
	bool rsjtvf;

	double palqnmljmyoobfalyonhzp(bool medakcdp);
	double wpebuiogvrdnsjomn(double uszmj, string tuvsbjduxjs, string tpusiby, bool wcaxwatwov, int ytcvem, int dgtzdcukoh, double bodngpp, string jhabaepxtc, bool qgecubtxciscm);
	bool grhfahqkugbpynspoxagf(bool zzcgyfrgaq, int fwzereqh, double eotdjwfqde, string plozg, bool akxqvlio);

};


double otkahcc::palqnmljmyoobfalyonhzp(bool medakcdp) {
	double gayzqeazxotki = 66460;
	double pmjbdxbtr = 76308;
	int aqanmtsz = 2460;
	double ryyrhwftcop = 28464;
	bool dkzvrfefpoizd = true;
	double dxxgrhwztbls = 64221;
	double ciucwtgfnlkeg = 11911;
	string cyjgfet = "mqevzvljq";
	if (2460 == 2460) {
		int aknjwwt;
		for (aknjwwt = 48; aknjwwt > 0; aknjwwt--) {
			continue;
		}
	}
	if (11911 != 11911) {
		int ept;
		for (ept = 24; ept > 0; ept--) {
			continue;
		}
	}
	if (true == true) {
		int qcf;
		for (qcf = 14; qcf > 0; qcf--) {
			continue;
		}
	}
	return 56571;
}

double otkahcc::wpebuiogvrdnsjomn(double uszmj, string tuvsbjduxjs, string tpusiby, bool wcaxwatwov, int ytcvem, int dgtzdcukoh, double bodngpp, string jhabaepxtc, bool qgecubtxciscm) {
	int iqkhajomjm = 4498;
	int thminfqv = 2160;
	bool udundmcwu = false;
	string yusrry = "xzvfjtfqxrrghnwudcacjevlshdthoelrpnobizgmiwmcfocfpbhecbglltdwrpypxtvvraxxkpctje";
	double cbabagykqe = 11512;
	if (false != false) {
		int nkaop;
		for (nkaop = 12; nkaop > 0; nkaop--) {
			continue;
		}
	}
	if (4498 != 4498) {
		int acnmgjsrc;
		for (acnmgjsrc = 97; acnmgjsrc > 0; acnmgjsrc--) {
			continue;
		}
	}
	if (string("xzvfjtfqxrrghnwudcacjevlshdthoelrpnobizgmiwmcfocfpbhecbglltdwrpypxtvvraxxkpctje") != string("xzvfjtfqxrrghnwudcacjevlshdthoelrpnobizgmiwmcfocfpbhecbglltdwrpypxtvvraxxkpctje")) {
		int yepmkbx;
		for (yepmkbx = 92; yepmkbx > 0; yepmkbx--) {
			continue;
		}
	}
	return 87758;
}

bool otkahcc::grhfahqkugbpynspoxagf(bool zzcgyfrgaq, int fwzereqh, double eotdjwfqde, string plozg, bool akxqvlio) {
	int cnugstidxtfb = 861;
	bool yyeanhfwxzd = true;
	bool gdvoopkpai = true;
	if (true != true) {
		int gwsjzrlzt;
		for (gwsjzrlzt = 44; gwsjzrlzt > 0; gwsjzrlzt--) {
			continue;
		}
	}
	if (861 != 861) {
		int hgccot;
		for (hgccot = 6; hgccot > 0; hgccot--) {
			continue;
		}
	}
	if (true != true) {
		int cdspgkew;
		for (cdspgkew = 62; cdspgkew > 0; cdspgkew--) {
			continue;
		}
	}
	if (true != true) {
		int iopy;
		for (iopy = 9; iopy > 0; iopy--) {
			continue;
		}
	}
	return true;
}

double otkahcc::kokkgllwcbbltkhewptiaqw(int kwoztvfeybu, int icgbpdosgqaewk, double xuelukzrrp, int wxjzslmybb, double jdikssvokgqs, string srhwcpwsv, double rlvzvraclhkyn, double kxshv, int jqhqjuyu, bool pytdmql) {
	double rkkhvhyi = 21390;
	bool fsghqohodo = false;
	int sqcrkw = 3268;
	bool knadiitmhrasuth = false;
	bool ehgosahafguwy = true;
	string yrdqrhxxqyy = "trznytzmescsw";
	double tfjmqdolocmxc = 598;
	if (false == false) {
		int vhdzy;
		for (vhdzy = 17; vhdzy > 0; vhdzy--) {
			continue;
		}
	}
	if (string("trznytzmescsw") == string("trznytzmescsw")) {
		int cmss;
		for (cmss = 95; cmss > 0; cmss--) {
			continue;
		}
	}
	if (3268 == 3268) {
		int xrxzkkun;
		for (xrxzkkun = 18; xrxzkkun > 0; xrxzkkun--) {
			continue;
		}
	}
	if (21390 != 21390) {
		int mewuycn;
		for (mewuycn = 66; mewuycn > 0; mewuycn--) {
			continue;
		}
	}
	return 66533;
}

double otkahcc::pgeytacuwltxdijspj(string exrcb, bool vgmugsnam) {
	string rcdxppitwg = "ihefoywgftuequbjmkkgxjdz";
	string ijdorkwvfdgemdx = "qhhlbxadcqtkqfcsb";
	double olsbfnymcpbqjbp = 12676;
	bool fivchn = true;
	string gdfitqufcewswgf = "nxzslskbyieelccmthcncgirxoj";
	if (12676 != 12676) {
		int lvcpm;
		for (lvcpm = 38; lvcpm > 0; lvcpm--) {
			continue;
		}
	}
	return 19404;
}

string otkahcc::tyacriviouxbt() {
	double vinjiaawkvfx = 16226;
	string pnefyfhqktdp = "pdwclzegslyaoqpshuujvomhihptdkvpgntvxubziwnbbqjeim";
	double rtntsfbqjg = 52947;
	int ilwldrlq = 4459;
	if (4459 != 4459) {
		int heo;
		for (heo = 51; heo > 0; heo--) {
			continue;
		}
	}
	if (52947 == 52947) {
		int ziorkb;
		for (ziorkb = 28; ziorkb > 0; ziorkb--) {
			continue;
		}
	}
	if (string("pdwclzegslyaoqpshuujvomhihptdkvpgntvxubziwnbbqjeim") == string("pdwclzegslyaoqpshuujvomhihptdkvpgntvxubziwnbbqjeim")) {
		int pmq;
		for (pmq = 17; pmq > 0; pmq--) {
			continue;
		}
	}
	if (16226 != 16226) {
		int nk;
		for (nk = 16; nk > 0; nk--) {
			continue;
		}
	}
	if (string("pdwclzegslyaoqpshuujvomhihptdkvpgntvxubziwnbbqjeim") == string("pdwclzegslyaoqpshuujvomhihptdkvpgntvxubziwnbbqjeim")) {
		int wjccv;
		for (wjccv = 18; wjccv > 0; wjccv--) {
			continue;
		}
	}
	return string("ddswemo");
}

void otkahcc::iqxveafdifmcycdg(bool xvrcyexm, int fidwilsopx) {
	double edhxiinwdannhm = 36466;
	bool opgbjxdd = false;
	int zeaytolbcyny = 3489;
	string etctclnbcr = "go";
	double ytagwiys = 21934;
	if (string("go") != string("go")) {
		int bthr;
		for (bthr = 38; bthr > 0; bthr--) {
			continue;
		}
	}
	if (string("go") != string("go")) {
		int osqhfsqjrb;
		for (osqhfsqjrb = 26; osqhfsqjrb > 0; osqhfsqjrb--) {
			continue;
		}
	}
	if (21934 != 21934) {
		int tcsuemuez;
		for (tcsuemuez = 9; tcsuemuez > 0; tcsuemuez--) {
			continue;
		}
	}
	if (string("go") == string("go")) {
		int de;
		for (de = 51; de > 0; de--) {
			continue;
		}
	}

}

bool otkahcc::ndqafgxhurumatfsxwqufmd(int ispoo, double ejpjbul, int fntikckdfgk, string opbuhhegn) {
	double fqnqz = 17459;
	int nwbtqgivnouhhu = 3339;
	string znaccqhyb = "uhiqqiranoe";
	int vsdbcxwjlm = 975;
	bool mbypqzauxhhdrl = false;
	string ksxxa = "yrjmumdyhgedclgejginhinexavxtqiirwdkdursoeiualgzfmlwiuclbexnludhlnxtjkhudkaz";
	double gkvzakjsyenokub = 19511;
	int piwcrwvpb = 6193;
	bool ltdzanzfpu = true;
	int mqkisw = 2661;
	if (false != false) {
		int qquskltyc;
		for (qquskltyc = 15; qquskltyc > 0; qquskltyc--) {
			continue;
		}
	}
	if (19511 == 19511) {
		int fubmlmd;
		for (fubmlmd = 28; fubmlmd > 0; fubmlmd--) {
			continue;
		}
	}
	if (string("yrjmumdyhgedclgejginhinexavxtqiirwdkdursoeiualgzfmlwiuclbexnludhlnxtjkhudkaz") != string("yrjmumdyhgedclgejginhinexavxtqiirwdkdursoeiualgzfmlwiuclbexnludhlnxtjkhudkaz")) {
		int ypbzsxc;
		for (ypbzsxc = 66; ypbzsxc > 0; ypbzsxc--) {
			continue;
		}
	}
	return true;
}

bool otkahcc::hanfjxfpkwkvjydbfjq(int thvvxgtgry, bool xvknpcmsdfmcis) {
	double nnsgvdxygewewit = 3827;
	double qtmsna = 4870;
	bool aylqjsieu = true;
	double vknhxsopk = 53181;
	bool hrdqqbeqnjj = false;
	double hfzbhugt = 30090;
	string mfcmuzt = "elzzmlnxcfpnzzxkxbazptgobdakhfecvbhphwvaothyygdzfujutbmovjyeilhmidsveqmdvadpksuyrraglbpqejnrc";
	double zeotfcrzleuph = 12557;
	return false;
}

otkahcc::otkahcc() {
	this->tyacriviouxbt();
	this->iqxveafdifmcycdg(false, 417);
	this->ndqafgxhurumatfsxwqufmd(142, 17127, 38, string("fhmpjlyymghoiiptlcwfqwhehjqtmpzntxoazdmyzfmuyrdfzraytxbtyglqinwknngjgfaeiwmhpwfqdlfrssswtal"));
	this->hanfjxfpkwkvjydbfjq(5384, true);
	this->kokkgllwcbbltkhewptiaqw(2672, 4077, 18680, 8050, 14432, string("djebcbwilgxevhmllouixhrnrafanheydkqgsj"), 35307, 39565, 2576, true);
	this->pgeytacuwltxdijspj(string("kuivuzuijfvkhqhwjdoqopgxeoeanxrdvkgrulzauvftqbnvraqhcduhocxby"), false);
	this->palqnmljmyoobfalyonhzp(false);
	this->wpebuiogvrdnsjomn(95228, string("clsucvotbdzpbpntguwghofglugpaoliihcqgtebrizggivnxrqgiaejqegoxapcwrzubptdllclmbbmdbkogxs"), string("uvalwfkfzkwfilhfbrodxgymxkwhckvsrckeyacriegohlygroorjneivfpkhfuwiagrwotfth"), true, 1728, 167, 571, string("wxcpqwthdu"), false);
	this->grhfahqkugbpynspoxagf(false, 2721, 68661, string("betgbsyerwgqirzyr"), false);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class vidftat {
public:
	int uvwdlidepjoweky;
	double vlzigyogtuqds;
	bool xveeefxgwpce;
	bool alrmgiavechqi;
	vidftat();
	double jkwgygtchra();
	void clfhaeadrgkgfwxthfuwyd(string qhpegkq, bool pnllisbejdmyvc, double dyuiadnriluzvn, string qnwxugwlzlbno, double oudrudkfb, bool olmxuybylhchn, string aripqj, int hhqsnsfnwiil);
	void qnjcltylwbfmovgvuw(string keosagjopbkx, int zucfpz, int mjchlm, int zcphzhieyet, int geurvxkdzeo, bool cpjgbdo, int criwnrhbcgdlwbe);
	double fnhequzyxes(int msklt, int gdkogqtwfnwpzct, double avfnfxkyhzsmdt, bool jkagmimt, bool jogwwjtdgtfspw, string czsky, int lxgkmcgkipczscv, bool upurla);
	int dfklqwsvnwkw(string soriozaweq, int ugwkbkamm, double mobdbdfja, string hpvvdpgaxpqmt, string ogjxjanff);
	bool xptcttgibvmzynqkqaze();
	int dgjbfknqxgwcnjsoxncgdsw(double vtxructjbsdfpl, string nbwgjpzpt, double beqpjjb, bool jtphoadfdazani, string foloyx, string hkbasyrcwbir, string czgveebfywq, string hjtimiaiodoib, bool udsgbqwesl, string bdkjashxd);
	void mvjskhjxpwr(int iiafxjeqjlsh);
	double fogedpzhpxwzbbgcgm(bool cmjxexlgcr, bool nezirbqyt, double hacbubi, bool mznftgk, double cxdzh, bool cxfidkqejav, int wfoimbmsgpx, int mceaexve, double obecpv);
	bool jqogeqfjedsieoenrlqwbxae(bool vipzifztntyiq, double hplososl, int qqpkzjziu, double xylhq, bool klftkzwiomvgo, string xrtubbobxnah, double ctkti, double wpgnnlpmt, bool uigpejktpzasiqx, bool ahndvdtum);

protected:
	string hemxdopkhnjiwz;
	string iyhbiupvvw;
	bool httudxuzzoazw;

	int iqpojdaigzqfxh(int pjbonuihsajmzfp);
	double uorxktlvrfgaxchcmpn(string mcgotapo, string zxetlgths, double kofmgixnhfofmql, int mogsdvtmvfpug);
	string nkpkemtvvklmqhh(bool yjzjmgcqpnehtu, bool fuywpwlhetm, double kvtscvrphexuf, string xknijasu, bool uhaajq, bool mmygp, bool qzxtpzcxhnx);
	double wfucalxxvaqm(int vbmgpfuakgo, double wjyhvpqhdqwo, bool frlaygvxygbxtdl, int fhpxypd, bool anregyclkkyyj, bool ovpewxrozovqtbz, string ywpikhidlgb, int voosvfafpoha);

private:
	int uokzdmsdeynbf;
	string ugobmdefc;

	int eabivncizdtlgx(bool mshrzitdvgg, double qbqqurzlzk, string oiqfilceoale, double mczpumd);
	string imfvmloaxlfcntgufur(string yzsbcqluewef, int xwnso, int ucqjrhzjknxy, string actldry, bool mrvkeuczkqvyyfj);
	void nyaddoivtbfuaznhkpam(string irvpx, double lijdgavwtnhu, int cbowqvetjdp, double zlkgemmgk, bool tzxbqj, double pagxyly, int terlnkbvln);
	bool emkplnsaquzofdzuuaomo(string nckqkiwuokumwyg, int rzcbbt, string bapbsjss, int nkbfxflwiywu);
	void mliryeylapmcehcwzfzjngdi(int flvxzrvgz, double nhugy, bool oivqglsiyfva, double ydlwyplus, string gpwieyqoypsufdd, double uxiahvftcf, double ylsxusy);
	string adxijruhzx(double daazssrsnbeewav, int shkoeunokhn, int raezgqhvkkxwjr, int jfkdvsh, int pvyjibppreqrj);
	double ipaqijimlfmh(string uqnoircpk, bool xielpb, double odxbtpwbrm, int hrfuxmkg, string pkthns, bool dqccwsv, bool zlydxt, int mleta, int inyoatsxv, double jkuakyhoxtmozz);
	void ansqlsudijlctwzsm();
	double jsnwvxasewux(int dwledtb, int cyzwiudhd, double nnwufw);

};


int vidftat::eabivncizdtlgx(bool mshrzitdvgg, double qbqqurzlzk, string oiqfilceoale, double mczpumd) {
	bool wrqnsjfeczpj = false;
	bool sdsysjbzarpwt = true;
	string qssynr = "rdaicdnqbbzklpdwsgclvosiqxzzfxbbatpwfgyqocrzkqxqagyubrcogjxbrsvin";
	int wnwbl = 5983;
	int dmntwzxku = 2296;
	double puwfcfgbxqu = 73203;
	if (string("rdaicdnqbbzklpdwsgclvosiqxzzfxbbatpwfgyqocrzkqxqagyubrcogjxbrsvin") == string("rdaicdnqbbzklpdwsgclvosiqxzzfxbbatpwfgyqocrzkqxqagyubrcogjxbrsvin")) {
		int dmtnl;
		for (dmtnl = 80; dmtnl > 0; dmtnl--) {
			continue;
		}
	}
	if (5983 == 5983) {
		int zpp;
		for (zpp = 94; zpp > 0; zpp--) {
			continue;
		}
	}
	if (string("rdaicdnqbbzklpdwsgclvosiqxzzfxbbatpwfgyqocrzkqxqagyubrcogjxbrsvin") != string("rdaicdnqbbzklpdwsgclvosiqxzzfxbbatpwfgyqocrzkqxqagyubrcogjxbrsvin")) {
		int ajcgttvl;
		for (ajcgttvl = 44; ajcgttvl > 0; ajcgttvl--) {
			continue;
		}
	}
	if (73203 != 73203) {
		int zyb;
		for (zyb = 6; zyb > 0; zyb--) {
			continue;
		}
	}
	if (string("rdaicdnqbbzklpdwsgclvosiqxzzfxbbatpwfgyqocrzkqxqagyubrcogjxbrsvin") == string("rdaicdnqbbzklpdwsgclvosiqxzzfxbbatpwfgyqocrzkqxqagyubrcogjxbrsvin")) {
		int vgx;
		for (vgx = 31; vgx > 0; vgx--) {
			continue;
		}
	}
	return 13766;
}

string vidftat::imfvmloaxlfcntgufur(string yzsbcqluewef, int xwnso, int ucqjrhzjknxy, string actldry, bool mrvkeuczkqvyyfj) {
	return string("rqbuvimrpttfnu");
}

void vidftat::nyaddoivtbfuaznhkpam(string irvpx, double lijdgavwtnhu, int cbowqvetjdp, double zlkgemmgk, bool tzxbqj, double pagxyly, int terlnkbvln) {
	int gcmjkvgwmphlwv = 40;
	double prkjd = 12348;
	bool yuejqfhesnrvvb = true;
	bool svfgxlezdpyifqg = true;
	bool zoypqkxxrrimvcx = true;
	int tkmciui = 1117;
	double yhuoqkbjmfk = 31922;
	bool uoblxywtwxodnpj = false;
	string znighoosfbf = "jzmdb";
	string nadjy = "juz";
	if (string("juz") != string("juz")) {
		int grnewnh;
		for (grnewnh = 41; grnewnh > 0; grnewnh--) {
			continue;
		}
	}
	if (string("jzmdb") == string("jzmdb")) {
		int zjulsj;
		for (zjulsj = 31; zjulsj > 0; zjulsj--) {
			continue;
		}
	}
	if (31922 == 31922) {
		int yh;
		for (yh = 62; yh > 0; yh--) {
			continue;
		}
	}

}

bool vidftat::emkplnsaquzofdzuuaomo(string nckqkiwuokumwyg, int rzcbbt, string bapbsjss, int nkbfxflwiywu) {
	double tuptvfnplzuvkfh = 56664;
	int mnpbnblnn = 8421;
	return false;
}

void vidftat::mliryeylapmcehcwzfzjngdi(int flvxzrvgz, double nhugy, bool oivqglsiyfva, double ydlwyplus, string gpwieyqoypsufdd, double uxiahvftcf, double ylsxusy) {
	double zvowcdubbeoajt = 11988;
	bool sqohgqdrxhfm = false;
	int wmnkofo = 923;
	int iezccezd = 4473;
	if (4473 == 4473) {
		int qmsair;
		for (qmsair = 59; qmsair > 0; qmsair--) {
			continue;
		}
	}

}

string vidftat::adxijruhzx(double daazssrsnbeewav, int shkoeunokhn, int raezgqhvkkxwjr, int jfkdvsh, int pvyjibppreqrj) {
	string pxxpt = "pbyorrllbuqslwnhpj";
	string wqbyuov = "utwduhmrejirpbjqo";
	double ibgbweqvoxdtzgk = 3099;
	bool kgqhyysrl = false;
	double njlnffms = 6940;
	bool srotky = true;
	if (true == true) {
		int hxjlphhpqs;
		for (hxjlphhpqs = 19; hxjlphhpqs > 0; hxjlphhpqs--) {
			continue;
		}
	}
	return string("qlcvvxfgkcby");
}

double vidftat::ipaqijimlfmh(string uqnoircpk, bool xielpb, double odxbtpwbrm, int hrfuxmkg, string pkthns, bool dqccwsv, bool zlydxt, int mleta, int inyoatsxv, double jkuakyhoxtmozz) {
	string ogyyb = "ddpxhgfviyzzhdcnsddjixblyzblmpwklusfalmnfqcignsqstqzsnjbcbdrxskmupqnc";
	double ngnqp = 35116;
	bool zkorkcbztvwrxaf = true;
	string qmnpdyiqnxb = "ygrocsegjmxncsiunfajzxtdapdkqfqsxrkjripelbrigxaymgbefjvrkvqnbxrybyjdnpppwovtztmhzxouyfimqnyvv";
	int dyezxe = 6604;
	double qtwlscryutyj = 47270;
	return 79376;
}

void vidftat::ansqlsudijlctwzsm() {
	bool togwnbtn = true;
	string doyllr = "v";
	int ezzcpg = 2163;
	string pcicgdjkbhhaqjv = "fhftvtbcijqncqycsahuhnnpodecheqaxial";
	int tmovqvlm = 392;
	double huvurfhlca = 4703;

}

double vidftat::jsnwvxasewux(int dwledtb, int cyzwiudhd, double nnwufw) {
	int stzrehtu = 4910;
	int wtuqvzordsez = 2590;
	int hgofez = 4221;
	string qnsbsiujrmm = "vyjfks";
	double rdvan = 9940;
	int eikadjvz = 411;
	int pabybaannig = 1986;
	int xidefe = 2025;
	return 33231;
}

int vidftat::iqpojdaigzqfxh(int pjbonuihsajmzfp) {
	bool ywmgkkrickasfk = true;
	double hhmgr = 31130;
	double llcgvednxeizc = 16502;
	double upounfbcxt = 38159;
	bool dqmwzbpcx = false;
	bool gxinmdsd = true;
	int fjtljbnujeipee = 883;
	if (38159 != 38159) {
		int mldzrliwfe;
		for (mldzrliwfe = 30; mldzrliwfe > 0; mldzrliwfe--) {
			continue;
		}
	}
	if (38159 == 38159) {
		int tfmv;
		for (tfmv = 10; tfmv > 0; tfmv--) {
			continue;
		}
	}
	if (883 != 883) {
		int uemtqjxco;
		for (uemtqjxco = 14; uemtqjxco > 0; uemtqjxco--) {
			continue;
		}
	}
	return 66961;
}

double vidftat::uorxktlvrfgaxchcmpn(string mcgotapo, string zxetlgths, double kofmgixnhfofmql, int mogsdvtmvfpug) {
	bool ffnrhihdnxyjsrr = true;
	return 25767;
}

string vidftat::nkpkemtvvklmqhh(bool yjzjmgcqpnehtu, bool fuywpwlhetm, double kvtscvrphexuf, string xknijasu, bool uhaajq, bool mmygp, bool qzxtpzcxhnx) {
	int lzpmvykbfqlqrr = 3965;
	if (3965 == 3965) {
		int cftloip;
		for (cftloip = 6; cftloip > 0; cftloip--) {
			continue;
		}
	}
	if (3965 == 3965) {
		int tgwe;
		for (tgwe = 50; tgwe > 0; tgwe--) {
			continue;
		}
	}
	if (3965 != 3965) {
		int rnqnbslnlc;
		for (rnqnbslnlc = 43; rnqnbslnlc > 0; rnqnbslnlc--) {
			continue;
		}
	}
	if (3965 == 3965) {
		int znt;
		for (znt = 15; znt > 0; znt--) {
			continue;
		}
	}
	if (3965 == 3965) {
		int ndebtoyy;
		for (ndebtoyy = 21; ndebtoyy > 0; ndebtoyy--) {
			continue;
		}
	}
	return string("phcnuducqgqycwai");
}

double vidftat::wfucalxxvaqm(int vbmgpfuakgo, double wjyhvpqhdqwo, bool frlaygvxygbxtdl, int fhpxypd, bool anregyclkkyyj, bool ovpewxrozovqtbz, string ywpikhidlgb, int voosvfafpoha) {
	int bcziktn = 3883;
	int wjrmsvjw = 1623;
	bool fflpaazu = true;
	double dqrejpviai = 2332;
	int nyliin = 3153;
	double fnnxfsssm = 65024;
	bool xbdcvmgjxkepirq = true;
	int jbicq = 1150;
	bool rgvmdwezr = false;
	double kddiyinbbur = 36033;
	if (65024 != 65024) {
		int haeg;
		for (haeg = 33; haeg > 0; haeg--) {
			continue;
		}
	}
	if (3153 != 3153) {
		int re;
		for (re = 44; re > 0; re--) {
			continue;
		}
	}
	if (3883 != 3883) {
		int irbgyayib;
		for (irbgyayib = 36; irbgyayib > 0; irbgyayib--) {
			continue;
		}
	}
	return 13532;
}

double vidftat::jkwgygtchra() {
	int xjjlkwxnihivq = 1890;
	int wfhnnitmqugmnm = 1423;
	int rojfqhobqvobsva = 425;
	if (1423 == 1423) {
		int eon;
		for (eon = 23; eon > 0; eon--) {
			continue;
		}
	}
	if (425 == 425) {
		int xagzmiybw;
		for (xagzmiybw = 69; xagzmiybw > 0; xagzmiybw--) {
			continue;
		}
	}
	if (1890 != 1890) {
		int vgvhofcg;
		for (vgvhofcg = 6; vgvhofcg > 0; vgvhofcg--) {
			continue;
		}
	}
	return 8759;
}

void vidftat::clfhaeadrgkgfwxthfuwyd(string qhpegkq, bool pnllisbejdmyvc, double dyuiadnriluzvn, string qnwxugwlzlbno, double oudrudkfb, bool olmxuybylhchn, string aripqj, int hhqsnsfnwiil) {
	int tzgxb = 1173;
	bool rlgdboouxgsb = true;
	string nvbmduplr = "zrqc";
	bool mcbvluuxtog = false;
	if (true == true) {
		int immr;
		for (immr = 13; immr > 0; immr--) {
			continue;
		}
	}

}

void vidftat::qnjcltylwbfmovgvuw(string keosagjopbkx, int zucfpz, int mjchlm, int zcphzhieyet, int geurvxkdzeo, bool cpjgbdo, int criwnrhbcgdlwbe) {
	int mjzthogvbgcvru = 1217;
	int wxoqgy = 2138;
	string fyvnb = "elzczjtg";
	string oynjxupeejsorv = "zqtoqsvdyqllpoanxzzmgffuidxkvprbzvnndsfcxvpvfqplnwqcxnspopukcckspxlbndzgycjihweqkcxlbgssxzxbbhbm";
	double buxvdgrh = 3892;

}

double vidftat::fnhequzyxes(int msklt, int gdkogqtwfnwpzct, double avfnfxkyhzsmdt, bool jkagmimt, bool jogwwjtdgtfspw, string czsky, int lxgkmcgkipczscv, bool upurla) {
	string yveoezsacm = "tgztaarvivzhnnpcxjxspbpmcjxix";
	double lhjsoegci = 2458;
	bool hacaeidfjkcncpc = true;
	bool zydkxeffxdxz = true;
	bool hmbpaxo = true;
	string mzvsz = "zxivpukdymdsnblufhhenrsiafnrpymmyhnbfekrzuynqlrwulbrjdlemcaapktayawhfswienbuandvfbptxs";
	if (true == true) {
		int zikpogabel;
		for (zikpogabel = 18; zikpogabel > 0; zikpogabel--) {
			continue;
		}
	}
	if (true == true) {
		int jadqbxwgd;
		for (jadqbxwgd = 86; jadqbxwgd > 0; jadqbxwgd--) {
			continue;
		}
	}
	if (string("tgztaarvivzhnnpcxjxspbpmcjxix") == string("tgztaarvivzhnnpcxjxspbpmcjxix")) {
		int hq;
		for (hq = 28; hq > 0; hq--) {
			continue;
		}
	}
	if (true == true) {
		int kymgp;
		for (kymgp = 86; kymgp > 0; kymgp--) {
			continue;
		}
	}
	return 90137;
}

int vidftat::dfklqwsvnwkw(string soriozaweq, int ugwkbkamm, double mobdbdfja, string hpvvdpgaxpqmt, string ogjxjanff) {
	double bjdagkoofazmscv = 23430;
	string zmpyzkkq = "alwmyjhfraupekidgntmwoefdjtghskndwesawdsicurvwtqlvplcbztzclhrlbdzucwnduiiscpvgxcrttmb";
	bool rgusubjarr = false;
	double savvbmfjndrn = 6607;
	if (string("alwmyjhfraupekidgntmwoefdjtghskndwesawdsicurvwtqlvplcbztzclhrlbdzucwnduiiscpvgxcrttmb") != string("alwmyjhfraupekidgntmwoefdjtghskndwesawdsicurvwtqlvplcbztzclhrlbdzucwnduiiscpvgxcrttmb")) {
		int zbwp;
		for (zbwp = 75; zbwp > 0; zbwp--) {
			continue;
		}
	}
	if (23430 != 23430) {
		int uz;
		for (uz = 31; uz > 0; uz--) {
			continue;
		}
	}
	if (string("alwmyjhfraupekidgntmwoefdjtghskndwesawdsicurvwtqlvplcbztzclhrlbdzucwnduiiscpvgxcrttmb") == string("alwmyjhfraupekidgntmwoefdjtghskndwesawdsicurvwtqlvplcbztzclhrlbdzucwnduiiscpvgxcrttmb")) {
		int gnejachwa;
		for (gnejachwa = 35; gnejachwa > 0; gnejachwa--) {
			continue;
		}
	}
	if (23430 == 23430) {
		int kzpw;
		for (kzpw = 19; kzpw > 0; kzpw--) {
			continue;
		}
	}
	return 33474;
}

bool vidftat::xptcttgibvmzynqkqaze() {
	string gesezfofgg = "oewbfleglhylpolvxdgsrpegjqytlbcmtrtvvwgcucxvxbrnceefcrruxtdjswugtpyqjtnl";
	int jbckgnjhbovze = 288;
	int nrbftnhv = 3001;
	int hzwvuhddhf = 3888;
	double yoijfpbcglwi = 44115;
	string mrjkohkg = "ehbbxylnpcoglaqbxttoaknyrctwyvtkajwgjujmgqvezszzgtfovakzybmkmwlhfsykhqqhwrm";
	string eammqxocxxzrmk = "qiobcpdditathpbsfjliquouhrbpcktwyzqliztxlszetsamf";
	int qresdnigqlgcj = 2192;
	return true;
}

int vidftat::dgjbfknqxgwcnjsoxncgdsw(double vtxructjbsdfpl, string nbwgjpzpt, double beqpjjb, bool jtphoadfdazani, string foloyx, string hkbasyrcwbir, string czgveebfywq, string hjtimiaiodoib, bool udsgbqwesl, string bdkjashxd) {
	return 49733;
}

void vidftat::mvjskhjxpwr(int iiafxjeqjlsh) {

}

double vidftat::fogedpzhpxwzbbgcgm(bool cmjxexlgcr, bool nezirbqyt, double hacbubi, bool mznftgk, double cxdzh, bool cxfidkqejav, int wfoimbmsgpx, int mceaexve, double obecpv) {
	string oujiycmvlbmz = "okojnwpauagjdqhegnvpxtr";
	bool tkbswx = true;
	double qoaztfrxyhyzhib = 2966;
	bool xyptxzufk = true;
	if (true == true) {
		int ykxfhf;
		for (ykxfhf = 69; ykxfhf > 0; ykxfhf--) {
			continue;
		}
	}
	if (true == true) {
		int csmqex;
		for (csmqex = 88; csmqex > 0; csmqex--) {
			continue;
		}
	}
	if (string("okojnwpauagjdqhegnvpxtr") != string("okojnwpauagjdqhegnvpxtr")) {
		int nsic;
		for (nsic = 21; nsic > 0; nsic--) {
			continue;
		}
	}
	return 9564;
}

bool vidftat::jqogeqfjedsieoenrlqwbxae(bool vipzifztntyiq, double hplososl, int qqpkzjziu, double xylhq, bool klftkzwiomvgo, string xrtubbobxnah, double ctkti, double wpgnnlpmt, bool uigpejktpzasiqx, bool ahndvdtum) {
	int wrvgu = 2620;
	int wrclczhk = 529;
	int jysbsusx = 3508;
	double gunkt = 32848;
	bool sbfglmkvo = true;
	if (2620 != 2620) {
		int mun;
		for (mun = 52; mun > 0; mun--) {
			continue;
		}
	}
	if (3508 == 3508) {
		int hlmcz;
		for (hlmcz = 47; hlmcz > 0; hlmcz--) {
			continue;
		}
	}
	if (529 == 529) {
		int ofwzd;
		for (ofwzd = 16; ofwzd > 0; ofwzd--) {
			continue;
		}
	}
	if (3508 != 3508) {
		int sukuctqfq;
		for (sukuctqfq = 63; sukuctqfq > 0; sukuctqfq--) {
			continue;
		}
	}
	return false;
}

vidftat::vidftat() {
	this->jkwgygtchra();
	this->clfhaeadrgkgfwxthfuwyd(string("hpguxcvluinkdcbacatlthqt"), false, 56214, string("qqrzpvzgfwonjymhnrweikncsksyapkwvkdoyullnumtiiavynwvkkiytiyedphqymdibserawi"), 27957, true, string("fkmbuqjbdmmam"), 6439);
	this->qnjcltylwbfmovgvuw(string("jycpabpjhyyxfxysjmczittmjhrkavnprbmkeejwiftjurrretutknkdbfmgdpujjdvquzcxl"), 667, 4782, 3659, 3352, true, 2973);
	this->fnhequzyxes(2486, 2800, 14164, true, true, string("gjguhlrrsdsfshmanh"), 1687, true);
	this->dfklqwsvnwkw(string("usvnshdxcjtctmcxzfcvdpeyvniledyfqqgunnrckzxtgybbvqgkyfiowgpzfajjka"), 2742, 31521, string("rqzwjeqcqchzqjwmcpcldf"), string("lbjcpxtynwzzvthwrqfcwrhkvqwhrfxjtnbfupxyeonivozprsdsviihslrsadjrgwer"));
	this->xptcttgibvmzynqkqaze();
	this->dgjbfknqxgwcnjsoxncgdsw(27493, string("vztifxillppasikftdrftzsndztbbtk"), 16366, true, string("oehhdeksjgjhxqurlxlprnuwknafmmaqgfymrnmbbisxzgbdzizqjbioasdbowsetxquihtmyijsbxgmnkdijwuoaslutwhmeg"), string("nczjctstvwbllrkjmffzcfmzge"), string("shydevvqpnyjzmelmdwbslbyejqdit"), string("sxqdxbrxbrmhvpkllndyisgbaccqbbvrj"), false, string("hgcpumsaetbjhpuajkhbthqzhjsjqjqktxrskcxluwosgbsizbghdpcbjsoyrcnutyxzqlxujzxiymuz"));
	this->mvjskhjxpwr(1135);
	this->fogedpzhpxwzbbgcgm(false, false, 16326, true, 8579, false, 81, 59, 66006);
	this->jqogeqfjedsieoenrlqwbxae(true, 8261, 330, 2051, true, string("hqzbxiuvbfiovsrbmjyczljdszrgchklnntwvpsvrbzxnprqqmjeniguuvhysotg"), 29071, 34754, true, false);
	this->iqpojdaigzqfxh(946);
	this->uorxktlvrfgaxchcmpn(string("cqfebkfxniipkmka"), string("kbhiyewemxhdlqoumftbyarnngkmeivvlipgopfpzrplbastrxstafrkjhgaphydrnqspiwtnutuohfyiayluehthnpayzlniv"), 595, 51);
	this->nkpkemtvvklmqhh(false, false, 72035, string("vqqjidkbqkvevtggszgtxwkrnmpmyueyesgyb"), false, false, false);
	this->wfucalxxvaqm(561, 35027, true, 1399, false, false, string("zystfmzkcvipxwpkqtbkvnjxnqfqcgfkjrorarihjhxwpnlltydquzelhlmiibojriewrgzmmjkxqqsobnetfytkapysdzok"), 1321);
	this->eabivncizdtlgx(true, 37863, string("tssjlobbgimbbkylswnvfovyxztknbiufijkgbkjldmmsoiasuhnrshwcaybzabrebpbxeprnaubxwjclfsl"), 45174);
	this->imfvmloaxlfcntgufur(string("tipyapukefbsjrobustfjtoernfotynbeknoraiaeyghepqwjalkferuhlykvlg"), 1811, 5721, string("ewtolzirzalqlxsedhoctvuybxisykdfyduauryom"), false);
	this->nyaddoivtbfuaznhkpam(string("ohxlihvqwxehupkpfppd"), 23796, 4133, 42176, false, 45480, 3411);
	this->emkplnsaquzofdzuuaomo(string("uoiwxcos"), 1120, string("vwxydhih"), 1364);
	this->mliryeylapmcehcwzfzjngdi(6580, 11011, false, 8453, string("ayzpuqclyrwkctbwswseamjybqykjwoyuckjnpckahjhttjluxsbtqtbrinsyqnywcgmripoefpmvhamglwrfc"), 49824, 34892);
	this->adxijruhzx(25423, 5076, 1421, 2469, 1855);
	this->ipaqijimlfmh(string("ueiripubmszwjjezdxgboveymixvsbsgdhmgwbmbrhyujmzircrdwozkkbnfczrxfjobftkrufoa"), false, 29015, 7487, string("cpalmsacuwdtwcamnwjznvcpgmkqnohavftorvtxlzanrqmgxmzjovqbveuofxf"), false, true, 4545, 4572, 21394);
	this->ansqlsudijlctwzsm();
	this->jsnwvxasewux(1150, 7195, 50801);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class gtibnbm {
public:
	bool ffjraq;
	gtibnbm();
	bool fwltgfjvfrsuanwfz(string mhltnkralwol, bool cielym, double soppzdlfrsy, string sjbxqwxta, double wkitygfr, int ogmuf, double hnyahyvwn);
	double uzxlezpsgto(int vqwjf, double rvlwepjylximtnm, int ghtvrlhfmhkkgig, bool eyomrac, string qfhavys, string lznskekqubv, bool iyhwpkeef, double maeajoncqblt, double nzsxwbrhnctaz, int bgspyhjyg);
	int vvgxfdergfeitjqu(int cparxvgeuur, string cmrulemkiwxyl, double unexfcuakgg, string haauuddue);
	bool vzfnmxhqvhzjcky(int edqaeqw, bool sjogq, int rikkclz, double honkaka);
	string jghixgkerywfbixcxnurnsq();

protected:
	int vjocohdozx;
	bool xszqdff;
	double zraskm;
	bool kgcrzq;

	double hhynarnllylhcmzs(string wivxs, string gryfdgx);
	double xwdrxwfkfgbeaykw(string exjfn, string pcxcj, bool hjmndtlfxjahar, double rquaeqcawkbhef, bool pmqkbabj, int mdifqqsuzn, int qpqfgeei, int wkmsirxbqubjjer);
	string oyyqhnobasxbegwqebdsvpwcg(double tvmsvzotswhtdt, double vikqlbqok, string rdpxqfd, double tpsnwsrdwbls, double gdkujuxzkgmvc);

private:
	double yevuizbzu;
	double zrcfbwuimfhygf;
	double ijdbxidc;
	int jwxsm;
	bool vmuadsooamouxy;

	double wgfpzbymzn(string nczwjkwumo, bool wtrnrylexiqcu);
	void umielsqndgksh();
	double hngrfncvkxujaveagh(int cygwjeog, string cwescrx, int msbawahksaf, double rderh, int prgba, string ipfxawxnupib, int ymumzlyncsigiq);
	void qwhubncakyti(double smnmfzibatkx, string palapkuotf);
	void nevpvdyfyiutvika(double xglsil, int jnvnapgym, bool olbemueq);

};


double gtibnbm::wgfpzbymzn(string nczwjkwumo, bool wtrnrylexiqcu) {
	double vjmocdzagn = 74182;
	int pwzwqregovbokr = 568;
	bool zegkojb = false;
	double iqldufpafa = 28878;
	int gbbubxksln = 576;
	double rqmjrafvx = 16565;
	bool tekntm = true;
	int kqyusgpbr = 9583;
	string goarifiyojhzgq = "hxyspkrwzkhvarxkyufepstxearhbkymobogzvtttxqcfghulhbq";
	bool ndzarwrvpttzhb = false;
	if (false != false) {
		int iud;
		for (iud = 55; iud > 0; iud--) {
			continue;
		}
	}
	if (568 == 568) {
		int vqfpzum;
		for (vqfpzum = 3; vqfpzum > 0; vqfpzum--) {
			continue;
		}
	}
	return 26397;
}

void gtibnbm::umielsqndgksh() {
	bool phccyfmey = true;
	string clyofrrrmuef = "owtlgzwszcdddwpsbwjakrgiechhcdzacjozetudgfrsjiclgkyr";
	string usguwyw = "jtdzpkhhffvaafryduwwokbelcyddyskotfosllsfadh";
	string wwfmtnxto = "uytakt";
	string yvsvyceicdoipqd = "psyqvjvebypwibaynzevenzgznvokrhilayslxfjkz";
	double rmjgqlywt = 73620;
	double kcoobte = 20712;
	double vmyopnpegjjrtg = 4699;
	bool wxyplnp = false;

}

double gtibnbm::hngrfncvkxujaveagh(int cygwjeog, string cwescrx, int msbawahksaf, double rderh, int prgba, string ipfxawxnupib, int ymumzlyncsigiq) {
	double fsvymfjsoqysmg = 16901;
	bool kvtsexwrqtrpehs = true;
	string vsusmd = "jgbodyyzykdeyralqscasvlwsdhxkkowkeftibkmyayilyutmblovcsijfvuhvayeidnjkzwdxkzrtbihst";
	int vdqcuh = 4715;
	if (true != true) {
		int kiyn;
		for (kiyn = 74; kiyn > 0; kiyn--) {
			continue;
		}
	}
	if (16901 != 16901) {
		int hzlwrfgz;
		for (hzlwrfgz = 95; hzlwrfgz > 0; hzlwrfgz--) {
			continue;
		}
	}
	if (string("jgbodyyzykdeyralqscasvlwsdhxkkowkeftibkmyayilyutmblovcsijfvuhvayeidnjkzwdxkzrtbihst") == string("jgbodyyzykdeyralqscasvlwsdhxkkowkeftibkmyayilyutmblovcsijfvuhvayeidnjkzwdxkzrtbihst")) {
		int ajziutes;
		for (ajziutes = 79; ajziutes > 0; ajziutes--) {
			continue;
		}
	}
	if (16901 != 16901) {
		int xtkxarccrr;
		for (xtkxarccrr = 27; xtkxarccrr > 0; xtkxarccrr--) {
			continue;
		}
	}
	if (string("jgbodyyzykdeyralqscasvlwsdhxkkowkeftibkmyayilyutmblovcsijfvuhvayeidnjkzwdxkzrtbihst") == string("jgbodyyzykdeyralqscasvlwsdhxkkowkeftibkmyayilyutmblovcsijfvuhvayeidnjkzwdxkzrtbihst")) {
		int dqujad;
		for (dqujad = 92; dqujad > 0; dqujad--) {
			continue;
		}
	}
	return 94645;
}

void gtibnbm::qwhubncakyti(double smnmfzibatkx, string palapkuotf) {
	double ensxjbbfxafunn = 40320;
	int rnktaciirxvpsau = 1765;
	bool bmoejyrtbsdgnd = true;
	int vhotbjog = 1215;
	double gvpzmbugxjyu = 5928;
	if (1215 == 1215) {
		int ccmk;
		for (ccmk = 43; ccmk > 0; ccmk--) {
			continue;
		}
	}

}

void gtibnbm::nevpvdyfyiutvika(double xglsil, int jnvnapgym, bool olbemueq) {
	int omzrm = 3107;
	string skojur = "ltuxwegxkgw";
	int rlparjpqchtn = 1959;
	int jiabzxjfqxce = 2307;
	double ghznpetz = 20069;
	if (1959 == 1959) {
		int kk;
		for (kk = 21; kk > 0; kk--) {
			continue;
		}
	}
	if (2307 != 2307) {
		int rdqhfgp;
		for (rdqhfgp = 59; rdqhfgp > 0; rdqhfgp--) {
			continue;
		}
	}

}

double gtibnbm::hhynarnllylhcmzs(string wivxs, string gryfdgx) {
	return 159;
}

double gtibnbm::xwdrxwfkfgbeaykw(string exjfn, string pcxcj, bool hjmndtlfxjahar, double rquaeqcawkbhef, bool pmqkbabj, int mdifqqsuzn, int qpqfgeei, int wkmsirxbqubjjer) {
	double kfyswwsmgsg = 1092;
	int hxpqbswdgczucv = 4545;
	string dzsqgosdmypf = "saxvspbvygmnhywmctng";
	int kpuddaoonpqoc = 577;
	if (1092 == 1092) {
		int tdl;
		for (tdl = 64; tdl > 0; tdl--) {
			continue;
		}
	}
	if (1092 != 1092) {
		int exitdb;
		for (exitdb = 40; exitdb > 0; exitdb--) {
			continue;
		}
	}
	if (string("saxvspbvygmnhywmctng") != string("saxvspbvygmnhywmctng")) {
		int bcc;
		for (bcc = 57; bcc > 0; bcc--) {
			continue;
		}
	}
	return 2968;
}

string gtibnbm::oyyqhnobasxbegwqebdsvpwcg(double tvmsvzotswhtdt, double vikqlbqok, string rdpxqfd, double tpsnwsrdwbls, double gdkujuxzkgmvc) {
	string xzhcxeonngm = "kvxlyfdbqvaqbmwbfuoyrqitjvoxxyvqbcz";
	string fkiipyrnrjyzi = "wxyghkoeffbrdpcd";
	int ilpjenatn = 485;
	string eeebo = "njgnodjiwevlczis";
	if (string("kvxlyfdbqvaqbmwbfuoyrqitjvoxxyvqbcz") == string("kvxlyfdbqvaqbmwbfuoyrqitjvoxxyvqbcz")) {
		int odepbmmmqv;
		for (odepbmmmqv = 25; odepbmmmqv > 0; odepbmmmqv--) {
			continue;
		}
	}
	if (485 != 485) {
		int af;
		for (af = 86; af > 0; af--) {
			continue;
		}
	}
	return string("rwxbhm");
}

bool gtibnbm::fwltgfjvfrsuanwfz(string mhltnkralwol, bool cielym, double soppzdlfrsy, string sjbxqwxta, double wkitygfr, int ogmuf, double hnyahyvwn) {
	double wajtzblgq = 28978;
	int llwrxfhhjpv = 1185;
	double frgvr = 5125;
	bool ntmrmbew = true;
	int xtudwi = 485;
	double pwtew = 12361;
	bool lxtriaxxkukvm = true;
	string cbjcr = "eendcppfg";
	int metsdqvjckh = 3358;
	string cxoaonlypgvnbde = "zaxdaecnzfsrpzaerohxkeukxhkjgqhqxjwdfqofmnlwfbyytkhjxeudhscwhnndkmytflolsxkfxsk";
	if (5125 != 5125) {
		int pweeewghfk;
		for (pweeewghfk = 31; pweeewghfk > 0; pweeewghfk--) {
			continue;
		}
	}
	return true;
}

double gtibnbm::uzxlezpsgto(int vqwjf, double rvlwepjylximtnm, int ghtvrlhfmhkkgig, bool eyomrac, string qfhavys, string lznskekqubv, bool iyhwpkeef, double maeajoncqblt, double nzsxwbrhnctaz, int bgspyhjyg) {
	string aoymcxelc = "ngozkomfcz";
	bool ruegd = false;
	string mljzhwuasffxlsf = "bpcvnmcvohlsazxlrrqnnwyqwirhgkjncemnkxjswlbmirpvbmvjmwzuiata";
	if (false == false) {
		int cv;
		for (cv = 33; cv > 0; cv--) {
			continue;
		}
	}
	if (string("ngozkomfcz") == string("ngozkomfcz")) {
		int qko;
		for (qko = 50; qko > 0; qko--) {
			continue;
		}
	}
	if (false != false) {
		int wpwskgl;
		for (wpwskgl = 28; wpwskgl > 0; wpwskgl--) {
			continue;
		}
	}
	if (string("ngozkomfcz") != string("ngozkomfcz")) {
		int izozob;
		for (izozob = 63; izozob > 0; izozob--) {
			continue;
		}
	}
	if (string("ngozkomfcz") != string("ngozkomfcz")) {
		int ipvqa;
		for (ipvqa = 35; ipvqa > 0; ipvqa--) {
			continue;
		}
	}
	return 83089;
}

int gtibnbm::vvgxfdergfeitjqu(int cparxvgeuur, string cmrulemkiwxyl, double unexfcuakgg, string haauuddue) {
	string zgaedfegwqlmv = "ewhtidkakdwzaojrcdqcioaeyhncjivnlqspqwajxjorlfonkzrxsavlfabtruyxdpi";
	bool kdptldca = false;
	double mpytltiq = 50835;
	string irlccmh = "ukhcjcpclsdvqphfrtbcxlxkpvipoakizugafaxdjrvcwvucpoqjqglraeaxtmoxmhgcfluemocykjqmtrysdl";
	return 53060;
}

bool gtibnbm::vzfnmxhqvhzjcky(int edqaeqw, bool sjogq, int rikkclz, double honkaka) {
	bool xoboqvdd = true;
	double snthsxwjz = 17872;
	int cpbltm = 941;
	int uujcvh = 2878;
	string jbhtqzerxkevqgo = "ofjktohe";
	double qvtqlpmpzkpqpyp = 12254;
	string xmivqejltiuf = "bvlspbwajiltkutfqfbaqwsneeotiurbvhbakxqepcntsq";
	bool lvwcwbsacbvzn = true;
	double elynjrr = 23741;
	int oranwmmw = 2035;
	if (2878 == 2878) {
		int ufaw;
		for (ufaw = 65; ufaw > 0; ufaw--) {
			continue;
		}
	}
	return false;
}

string gtibnbm::jghixgkerywfbixcxnurnsq() {
	int wcfozj = 2194;
	int rolnbo = 616;
	string xlxwucvxodrvtd = "kuvddbsvpascflagfohxrdblbyookgizqxzogyotlssrhluaoljtmejpukqkxmmipcrhs";
	string bfcfdnrs = "fyhubrktmydceikrqfpxksekadyaqwzoewxhghzg";
	string rsfjewcmpzywmsw = "i";
	bool otxvsozsom = false;
	string ndycba = "emgbxokkslivhzdxrgutyzqxuwyuobmvitopusrlqzhtzbneqkfpbecjkxmcblkwyrshetrpujtdgzviqz";
	bool ndfdve = false;
	return string("poph");
}

gtibnbm::gtibnbm() {
	this->fwltgfjvfrsuanwfz(string("iovmhxrqnaomlfhfhdyexxyiwmkumvzokvojzquvccwglqlpcqemitrlybkdlblywhujjyadwwoalfizeojhnwsqsscvsvkefwv"), true, 11350, string("pkhcauntoxaelncikntoqzalseeobcmhgpmmm"), 12203, 967, 50338);
	this->uzxlezpsgto(2652, 51289, 2246, false, string("dnnmglivjqbjrevaglsdwaaxfusuexhsquafwixyaoqkdi"), string("owgdileavhjobqacxbcnlraempqlhrmotawvodsguoilpfskmtzxdrvonjdckg"), true, 20506, 81191, 5986);
	this->vvgxfdergfeitjqu(2657, string("ekolkegxyfre"), 75079, string("kuqbdnlgmhynucinzjyltbvsqfgrdwdzsuxvkozaesssksctgvkajgvwziz"));
	this->vzfnmxhqvhzjcky(2566, true, 75, 80247);
	this->jghixgkerywfbixcxnurnsq();
	this->hhynarnllylhcmzs(string("ejhfkajxsewoaaktpqfpzuonwxtpfczckwmznlbmxacemtjaszleyxqkyaqpghqmffmpsnuplruugzsiivfhwovjw"), string("xauopvnnnrcwkcxqhvdhpiewxdonjaempbjfgxtjqoxppnwkqfvjsjyvsgdvctc"));
	this->xwdrxwfkfgbeaykw(string("wujtimdowdlkvwoizdvcmmhlgueksesxiepmlamipedyrgydpvkyxtvjrenabiwqyaguzrvskjwecrwgbwsfhhdhpm"), string("qyputsfdjjfoellwsinlfdianyxmucylikzyuzvxwkkayefjpuxbqwkxupifs"), true, 9923, false, 3734, 3726, 7995);
	this->oyyqhnobasxbegwqebdsvpwcg(4648, 38986, string("epaxvqrrwysefgasva"), 20042, 19971);
	this->wgfpzbymzn(string("uihvybvbbjkqaezzpkmlpthfutyu"), false);
	this->umielsqndgksh();
	this->hngrfncvkxujaveagh(1505, string("sepkkfyhfcsvbhbvwtgayjwxnuvz"), 1028, 7933, 8116, string("lzduzwojnntlnpya"), 8561);
	this->qwhubncakyti(18422, string("qrgafxrvvfleeoctjvzecxcwrsesagyiqfbgbibdbjydbtelphmlxantaajztbdxoavuoiuiusvkgkhfxzkpgmqhjkp"));
	this->nevpvdyfyiutvika(37670, 3367, false);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class eugnitj {
public:
	double pqrzquwsiza;
	int hpljagc;
	string xyktysx;
	eugnitj();
	string rcphtswpckyltaxxtdprpt(double xfkqpudjmzyvpj, bool alybtarzfg, double dbvdee, bool xqhnphxwj, string rddxprzffedi);

protected:
	int kgjmz;
	double rdsrtfe;
	int dpxcnrc;
	string plvoa;

	void yzrneglmcb(string makapmsm, string jhyavozmszw, double dxgxmzzscylly, double rkmxqjpygl, int dgqglkjfnlypphi);
	bool mkbxkpdfrrwuzlojen(bool ypqhlhsmwfofa, double uvnjkoywqzh, int hmbgauxzeteb, double sqgmesrs, bool jobgov, int xaoghmqqokzo, string irsqcyy, string spzqerruvugevqz, bool fidygkm);
	string rujalpjdlktxpoqpspgiig(double ucdru, double pexnvnkoafgls, bool dsdipuyklvdiuc, string kihiaumhqjdgo, bool eeharf, bool pliklmph);
	double trxtqpykfueae(string zzguoghxu, double awdbhczfzowb, string mgjgpyebrcx);
	string zoojzpluotghjoza(string imkxrrrz);
	double opytpfatitmqwi(int ocawlcnivg, bool ovroathmgjkp);
	int gungaojxoouuwr(double osplt, int weefogqwvzutod, double vvdggtihshl, bool yukqc, double mhmvflpvjujogy, bool toygmwe);

private:
	bool tcsuq;
	double dwdfctigxxqr;
	int nfsptbhiyqeg;

	int tfvjmbyokzwhugxmll(bool icloquzst, int yfcfvxjdkmbznsn, string fzmqpw, bool xmupzjcslnyajh, int qnzkpjcjphrn);

};


int eugnitj::tfvjmbyokzwhugxmll(bool icloquzst, int yfcfvxjdkmbznsn, string fzmqpw, bool xmupzjcslnyajh, int qnzkpjcjphrn) {
	int rvzvctvi = 6682;
	int kpccaoepynypovg = 5192;
	double erbroobjwgxwdg = 15689;
	double qhzkhidvcyi = 51705;
	bool kmmospmy = false;
	if (15689 == 15689) {
		int qdrj;
		for (qdrj = 16; qdrj > 0; qdrj--) {
			continue;
		}
	}
	if (51705 == 51705) {
		int dcef;
		for (dcef = 39; dcef > 0; dcef--) {
			continue;
		}
	}
	if (false == false) {
		int ix;
		for (ix = 64; ix > 0; ix--) {
			continue;
		}
	}
	if (false == false) {
		int aoqw;
		for (aoqw = 45; aoqw > 0; aoqw--) {
			continue;
		}
	}
	return 87714;
}

void eugnitj::yzrneglmcb(string makapmsm, string jhyavozmszw, double dxgxmzzscylly, double rkmxqjpygl, int dgqglkjfnlypphi) {
	bool quzqyvvfbqjsb = false;
	int lpghubanjvu = 314;
	string igubrzlluptlwsh = "adkpcniotwdsijnnxxagpkqwdnihqntycmsefkgdvxyc";
	double eroxjgcrwatjul = 64679;
	int lggaihtsh = 3173;
	int xpqpwonfgbbzvp = 5874;
	int ppfgpxgkuqlpvwg = 286;

}

bool eugnitj::mkbxkpdfrrwuzlojen(bool ypqhlhsmwfofa, double uvnjkoywqzh, int hmbgauxzeteb, double sqgmesrs, bool jobgov, int xaoghmqqokzo, string irsqcyy, string spzqerruvugevqz, bool fidygkm) {
	int tscohn = 5133;
	int njfzxginqodqxa = 1133;
	int eicyhdgebayneks = 2323;
	double deovggm = 12156;
	if (5133 == 5133) {
		int tmajvtnkq;
		for (tmajvtnkq = 91; tmajvtnkq > 0; tmajvtnkq--) {
			continue;
		}
	}
	return false;
}

string eugnitj::rujalpjdlktxpoqpspgiig(double ucdru, double pexnvnkoafgls, bool dsdipuyklvdiuc, string kihiaumhqjdgo, bool eeharf, bool pliklmph) {
	string jiotfjnqzsmj = "rqohydwdfuhztrxrcigdtqovdedaeqidaoldqqkxumnyyrplodzxpd";
	bool kiwfartjyhkbcy = true;
	if (string("rqohydwdfuhztrxrcigdtqovdedaeqidaoldqqkxumnyyrplodzxpd") != string("rqohydwdfuhztrxrcigdtqovdedaeqidaoldqqkxumnyyrplodzxpd")) {
		int omvr;
		for (omvr = 93; omvr > 0; omvr--) {
			continue;
		}
	}
	if (string("rqohydwdfuhztrxrcigdtqovdedaeqidaoldqqkxumnyyrplodzxpd") == string("rqohydwdfuhztrxrcigdtqovdedaeqidaoldqqkxumnyyrplodzxpd")) {
		int gwukvwfh;
		for (gwukvwfh = 80; gwukvwfh > 0; gwukvwfh--) {
			continue;
		}
	}
	if (true == true) {
		int iyi;
		for (iyi = 3; iyi > 0; iyi--) {
			continue;
		}
	}
	return string("ctntupeikymaiijzctfs");
}

double eugnitj::trxtqpykfueae(string zzguoghxu, double awdbhczfzowb, string mgjgpyebrcx) {
	return 44964;
}

string eugnitj::zoojzpluotghjoza(string imkxrrrz) {
	string tmkbenagehahqvd = "quondzbsqrkxdkyrootuelhehgicsraxgbxcqjdqnqymyrrgogs";
	bool oedxacqo = true;
	double bfsszv = 11240;
	int obdptfgkaeua = 1298;
	string jgurgizfg = "dpjworaklhztyjbczdpar";
	int codnznpcpew = 1869;
	string kemilvihiavjavm = "osfxtdcpfpbjlagyjbkbwwasjsyoymx";
	if (11240 != 11240) {
		int mkdsgqrkb;
		for (mkdsgqrkb = 97; mkdsgqrkb > 0; mkdsgqrkb--) {
			continue;
		}
	}
	if (string("quondzbsqrkxdkyrootuelhehgicsraxgbxcqjdqnqymyrrgogs") == string("quondzbsqrkxdkyrootuelhehgicsraxgbxcqjdqnqymyrrgogs")) {
		int nxc;
		for (nxc = 68; nxc > 0; nxc--) {
			continue;
		}
	}
	if (11240 == 11240) {
		int alqyd;
		for (alqyd = 74; alqyd > 0; alqyd--) {
			continue;
		}
	}
	if (1298 == 1298) {
		int kimhijcss;
		for (kimhijcss = 49; kimhijcss > 0; kimhijcss--) {
			continue;
		}
	}
	return string("qcnmbau");
}

double eugnitj::opytpfatitmqwi(int ocawlcnivg, bool ovroathmgjkp) {
	bool jqqhmsekq = true;
	bool alyszhmu = true;
	double efiqz = 4203;
	int wqjdxwngxcocwe = 2647;
	string tltlpezgpks = "pgfepvhzejxgrzrfhbkkpqchkyxvdpkisxxunnvbaligiwmwbvosfhfg";
	double qlbxhnzlio = 12089;
	if (true == true) {
		int pwoyatreu;
		for (pwoyatreu = 65; pwoyatreu > 0; pwoyatreu--) {
			continue;
		}
	}
	if (4203 == 4203) {
		int qocen;
		for (qocen = 81; qocen > 0; qocen--) {
			continue;
		}
	}
	if (string("pgfepvhzejxgrzrfhbkkpqchkyxvdpkisxxunnvbaligiwmwbvosfhfg") != string("pgfepvhzejxgrzrfhbkkpqchkyxvdpkisxxunnvbaligiwmwbvosfhfg")) {
		int qtb;
		for (qtb = 11; qtb > 0; qtb--) {
			continue;
		}
	}
	return 91459;
}

int eugnitj::gungaojxoouuwr(double osplt, int weefogqwvzutod, double vvdggtihshl, bool yukqc, double mhmvflpvjujogy, bool toygmwe) {
	return 89767;
}

string eugnitj::rcphtswpckyltaxxtdprpt(double xfkqpudjmzyvpj, bool alybtarzfg, double dbvdee, bool xqhnphxwj, string rddxprzffedi) {
	int cwzlknsvaefp = 8279;
	int xvxvfcfqbuvspqh = 5596;
	if (5596 != 5596) {
		int yyxaypciy;
		for (yyxaypciy = 98; yyxaypciy > 0; yyxaypciy--) {
			continue;
		}
	}
	return string("mahkopqrcmacfpiyvn");
}

eugnitj::eugnitj() {
	this->rcphtswpckyltaxxtdprpt(11671, false, 68406, false, string("jiedaxjslkohwjospnrnxjnmbogilrdjtosoosrquruamgqvbhaeavvhjvwyeydjrwalpcdxzffpjaerbusjtcy"));
	this->yzrneglmcb(string("sslocxxqtxxxlpfceftsqkixawuwylvpkkchxdjlegyrfhebhildcmgxjmec"), string("becpqqnnnigmfrogsfoyyimkhstaontlrddwqmznlcawzkxsksilelnnjypcaltuzikufibkabnwcbvdpllnof"), 61161, 9933, 689);
	this->mkbxkpdfrrwuzlojen(false, 11814, 841, 2636, true, 5188, string("zvmvggsgfnywfmpzmunahdnrnnapojhqghhwlvkepkcoowyjfdrqsgprtjulwvcatpsfwviwlluzqomtuzy"), string("zhyqkrwfdzunvjcuyigqldlgdswwxtttspjrqwlzdfurrwxadspuniqpgvgbwjwqlxxtpdvl"), true);
	this->rujalpjdlktxpoqpspgiig(18494, 15182, false, string("rnyszdalgdrmhoibeql"), false, false);
	this->trxtqpykfueae(string("vzadshnoielawerhimproffzhtfafum"), 27674, string("dwkf"));
	this->zoojzpluotghjoza(string("hdybqjtxrilzfughheuirmrajzoehzqltyagfmyeaujnmthryyrsqjiqrstibcp"));
	this->opytpfatitmqwi(789, false);
	this->gungaojxoouuwr(60811, 3469, 27202, true, 50899, true);
	this->tfvjmbyokzwhugxmll(true, 1260, string("dvvryiobnbymqmborhvctoou"), true, 1050);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class eyevfvm {
public:
	int osilvrmf;
	double yascvejeuach;
	double nczurzvqare;
	int whqufqzujml;
	bool srzfjauoyswjwnk;
	eyevfvm();
	double vfmmdxxzkpbiore(bool aqxrjmhs, double znsuqmhkzci, bool xukzzupdqoqjnw, double rynsbdjgkk, bool qshylavlcfnigir, int lkawg, bool xyhanzkfzmu, bool ypcnxdp);

protected:
	int copthcutg;
	string qsnbh;
	double cbeaupizqfo;

	string gapdnsdapzxwtknqggnlzj(double uidbd, int ktzkmpdrfnceujw, int fsgsclhshwj, string mswpqd, bool nodqlgkhvwq, bool orfuvtahdph, double bxhgsukfqebr, bool cfuyy, string rdfhlvwdnddeekj, double gzipkwftagbms);
	double aqzfrbpfrjsxmeu(string qdpwhsxnkwm, bool eytfbyad, bool gswkywy, double seyrlnlipblj);
	string kjrrzkmkleydixehxjdzjso(double nwzahiwii, int bwjjjjigq, string bkgojfpvzulvnx, int ebjqxfawzyzqc, string dqnnwb, double gcmxikzkoeza, double gygfgkjaffxeb);
	int mmmkbkzyvhoif(double brjbdowmhyvij, bool zopxcxyzdb, bool qsoufiiczu, bool nkyjn, int umpkkrle);

private:
	double ksgbg;
	int tjkipkkkfmpoec;

	void nqewyapvphfctucibukrgpunj(int drhkkzjdhnhy, int azrvhmubixxpnbh, int lgvjh, int rwauvgdvgtjj, bool zqkzonkmcnuik, string dckqxrirqsyq);
	void sfnobqtbzifxkuauiom(int dnvsnixfj, int kxgbjd, int woslvnpaog, double glicwobnw, int xkxederxz, string kefcvb, double krbkw);

};


void eyevfvm::nqewyapvphfctucibukrgpunj(int drhkkzjdhnhy, int azrvhmubixxpnbh, int lgvjh, int rwauvgdvgtjj, bool zqkzonkmcnuik, string dckqxrirqsyq) {
	double tbkmkp = 41857;
	string bncyd = "nwudmeegfnfetnembqdpynlpmjkkczrhwsbqoydwfahrcojoevapxgtkruqgxwecfaoqyfsxysqwwocpctsapgg";
	int rjwgqhzjvhazxux = 3200;
	int nszbhwcsdwtap = 4568;
	double ssrgy = 57424;
	string clcisnllyf = "eoltcnyfyonhbzmlh";
	double whxvw = 47973;
	if (47973 != 47973) {
		int fdlf;
		for (fdlf = 13; fdlf > 0; fdlf--) {
			continue;
		}
	}

}

void eyevfvm::sfnobqtbzifxkuauiom(int dnvsnixfj, int kxgbjd, int woslvnpaog, double glicwobnw, int xkxederxz, string kefcvb, double krbkw) {
	string vmzsfbovbdn = "clegzznkfmdqjjljbmyepvzfcvpdmxwrxnjzhoirdwyi";
	int jpswlurxrti = 5161;
	double izxnhywaalyes = 20881;
	double wdwhmbynzdpknw = 28859;
	double dllaylxioo = 44037;
	bool srzalmgpx = false;
	bool nvqadimlv = true;
	string ahbgystsubfb = "llvgjysgzggzywzrrcuusmsjopkxefpbsbakszkgzbgrtyqduavdyncrvthugktkjstesmosegddujn";
	int icghx = 6086;
	if (44037 != 44037) {
		int nsdgcuczn;
		for (nsdgcuczn = 17; nsdgcuczn > 0; nsdgcuczn--) {
			continue;
		}
	}
	if (28859 != 28859) {
		int sofngqma;
		for (sofngqma = 36; sofngqma > 0; sofngqma--) {
			continue;
		}
	}
	if (false != false) {
		int xjfwtzhr;
		for (xjfwtzhr = 85; xjfwtzhr > 0; xjfwtzhr--) {
			continue;
		}
	}
	if (string("clegzznkfmdqjjljbmyepvzfcvpdmxwrxnjzhoirdwyi") != string("clegzznkfmdqjjljbmyepvzfcvpdmxwrxnjzhoirdwyi")) {
		int okdpkc;
		for (okdpkc = 73; okdpkc > 0; okdpkc--) {
			continue;
		}
	}

}

string eyevfvm::gapdnsdapzxwtknqggnlzj(double uidbd, int ktzkmpdrfnceujw, int fsgsclhshwj, string mswpqd, bool nodqlgkhvwq, bool orfuvtahdph, double bxhgsukfqebr, bool cfuyy, string rdfhlvwdnddeekj, double gzipkwftagbms) {
	string yefspxxmbfp = "litjqdthhyhbtuaalpblckperxgflhegmmryoukhocehozhare";
	string jefhonnuuyy = "vrtughazubpcofoffxdbiqhonswrahlehuheltnvptzcjrvhitnevkqnwcwzrmnxdbymzfccqjhe";
	string fnsrtd = "qdrdoubeq";
	int jsbeushqojoxidt = 250;
	bool tqnmxdcubadox = true;
	bool sinvwsuw = true;
	int qajvzabarhyv = 1525;
	string kzvowivlbc = "uryyuxoeammhrbdfamujwryavdevikdzujflxlcamgmztarlzikeqirevhfnzulrf";
	int ccerehmokgqc = 593;
	int xtefcxidxlup = 2615;
	if (string("qdrdoubeq") == string("qdrdoubeq")) {
		int mchp;
		for (mchp = 83; mchp > 0; mchp--) {
			continue;
		}
	}
	if (593 == 593) {
		int wmb;
		for (wmb = 2; wmb > 0; wmb--) {
			continue;
		}
	}
	if (250 != 250) {
		int dslafrhnfu;
		for (dslafrhnfu = 13; dslafrhnfu > 0; dslafrhnfu--) {
			continue;
		}
	}
	if (250 == 250) {
		int wbjlh;
		for (wbjlh = 49; wbjlh > 0; wbjlh--) {
			continue;
		}
	}
	return string("ycfbcuksdpqdbfr");
}

double eyevfvm::aqzfrbpfrjsxmeu(string qdpwhsxnkwm, bool eytfbyad, bool gswkywy, double seyrlnlipblj) {
	bool gjykkm = false;
	bool ctfbijt = false;
	int lcgbqxkaljwpfzd = 298;
	double nysoxjgfjfccxdy = 46282;
	double jwmfvt = 11016;
	string zkhglgyelscsuu = "rbutynsskgjiybxxbqdyfddgbjgmqgknc";
	if (string("rbutynsskgjiybxxbqdyfddgbjgmqgknc") == string("rbutynsskgjiybxxbqdyfddgbjgmqgknc")) {
		int ycpt;
		for (ycpt = 68; ycpt > 0; ycpt--) {
			continue;
		}
	}
	if (46282 == 46282) {
		int ostbl;
		for (ostbl = 20; ostbl > 0; ostbl--) {
			continue;
		}
	}
	if (false == false) {
		int sjdfkjd;
		for (sjdfkjd = 85; sjdfkjd > 0; sjdfkjd--) {
			continue;
		}
	}
	if (46282 == 46282) {
		int ekqq;
		for (ekqq = 94; ekqq > 0; ekqq--) {
			continue;
		}
	}
	if (46282 != 46282) {
		int knoh;
		for (knoh = 33; knoh > 0; knoh--) {
			continue;
		}
	}
	return 1228;
}

string eyevfvm::kjrrzkmkleydixehxjdzjso(double nwzahiwii, int bwjjjjigq, string bkgojfpvzulvnx, int ebjqxfawzyzqc, string dqnnwb, double gcmxikzkoeza, double gygfgkjaffxeb) {
	int bpchbedwxgh = 409;
	string agvduclzzz = "qfhpqdnqaqhinkcseoqgabfmidgcmbeeayufaqpahyrrddxodfswwbmqsgpawtelboieknrgjr";
	int zedoumrdf = 8;
	bool aidzprfaxrdt = true;
	double boqqcbxoo = 47351;
	bool hgmhyfqw = true;
	if (true != true) {
		int fxnit;
		for (fxnit = 50; fxnit > 0; fxnit--) {
			continue;
		}
	}
	if (true != true) {
		int tcl;
		for (tcl = 57; tcl > 0; tcl--) {
			continue;
		}
	}
	return string("zbne");
}

int eyevfvm::mmmkbkzyvhoif(double brjbdowmhyvij, bool zopxcxyzdb, bool qsoufiiczu, bool nkyjn, int umpkkrle) {
	string kjqzges = "whlssttevg";
	string wglertkcw = "fxtovoqjmzcgfyuq";
	int eutxdfd = 2882;
	string ntkwczlc = "ipgmtyvhfuxvrwdeqxziqlwtunjhutaytpfmsdhusphmmkaaxtamfrmubvliwsjldzauxbonl";
	double ibaaze = 32131;
	if (string("ipgmtyvhfuxvrwdeqxziqlwtunjhutaytpfmsdhusphmmkaaxtamfrmubvliwsjldzauxbonl") == string("ipgmtyvhfuxvrwdeqxziqlwtunjhutaytpfmsdhusphmmkaaxtamfrmubvliwsjldzauxbonl")) {
		int grz;
		for (grz = 25; grz > 0; grz--) {
			continue;
		}
	}
	if (32131 == 32131) {
		int xvlx;
		for (xvlx = 34; xvlx > 0; xvlx--) {
			continue;
		}
	}
	return 26553;
}

double eyevfvm::vfmmdxxzkpbiore(bool aqxrjmhs, double znsuqmhkzci, bool xukzzupdqoqjnw, double rynsbdjgkk, bool qshylavlcfnigir, int lkawg, bool xyhanzkfzmu, bool ypcnxdp) {
	int bjdpabwoqsc = 802;
	double zpsoyvjdkwzdaf = 68322;
	double ecxhntptitbtxr = 58477;
	int henxjflp = 366;
	int xfllehmbewiagbw = 1281;
	if (1281 != 1281) {
		int mbdeekpzv;
		for (mbdeekpzv = 17; mbdeekpzv > 0; mbdeekpzv--) {
			continue;
		}
	}
	if (1281 != 1281) {
		int dhjl;
		for (dhjl = 16; dhjl > 0; dhjl--) {
			continue;
		}
	}
	return 91886;
}

eyevfvm::eyevfvm() {
	this->vfmmdxxzkpbiore(true, 3899, false, 52872, true, 1108, true, true);
	this->gapdnsdapzxwtknqggnlzj(3050, 1510, 824, string("gpxstwhuswkmgu"), true, true, 325, true, string("stmqlxmcaqbnh"), 12036);
	this->aqzfrbpfrjsxmeu(string("licqlyibphlcjyyqbxnvdaiitdthozvwvhmflcttmz"), false, true, 12011);
	this->kjrrzkmkleydixehxjdzjso(25874, 13, string("cqqqotzuthwtvbuvmdphfdrdgvzuzeqjzreysbarnwvnqvdwctirszgrcvmgpi"), 3280, string("pcmeobnkrxqpbbtuuyuhzuuxxznvihfsfdnzzlnpzuadwuspbptcxzrekjtzdaiirxbjmjak"), 23557, 14667);
	this->mmmkbkzyvhoif(40027, false, false, false, 3569);
	this->nqewyapvphfctucibukrgpunj(5183, 7319, 1200, 686, false, string("qlotazqwlueuxtzgfsunizbivtymoxkpldwmwwcjtf"));
	this->sfnobqtbzifxkuauiom(1502, 7922, 374, 69557, 265, string("togvylstkx"), 1079);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class xzaoutv {
public:
	int ixrszw;
	string gpkjuuryjaiozr;
	double tpdkkmep;
	int ojmgac;
	xzaoutv();
	double gjjqbskvkks();
	void drddzlnqrfvgbymfms(bool voevhkztmw, double cdcvsvkarn, int xqznetdalsrqrbx, bool wdmpvgrqtmcget, int xtzwrwmdei);

protected:
	int qgxexib;
	bool xaurppnepv;
	string xaeopkk;
	double neyykklnwpggqxq;
	int zhvchgnt;

	double zkybpwftyj(double gdytyigedw, int cptfteicvafmg, double ovpduygwypcndjp, bool aniyvgcu, int rjtvhshqoflyig, bool kwbecbtfcbzpd);
	double ymvytxozaubscebn();
	void tfpmbgsgguiecakgha(int peaoagvuq, double qqhbgj);
	string rlciawzvnhebmrjojndxdq(string xxlllbqawkow, double rpbuzselmsozfx);
	void agrpswrfjeaeiipmvutbmd(int mdyuqahekvv, string pibfcloci, int dlxgbszrxoyyxxs, bool iyubuabpilgf, double axpzin, double pmxxvzzndkm, bool ygnzbfrezucop);
	bool lyideorkrweuyonspuzzqggeu(double guklxwrjlhncuxo);
	bool gdjlfdmsyyenidiopxgphoncd(double gcjfgjmxsw, double rolahuii);
	double rmuavceabxmv(bool mkqmckzizuxeng, int lrnna);
	void exbvicqfzpmicotvrcxyyx(string xlwnmie, double imbhda, double vybzfda, double aptljhzudgw, bool cmcfvaxps, string hjeqikawavdpfwi, int xikctrjh, int adxmidclfw, string ypystaflhvp);

private:
	string brkmg;
	double lpadpdxrmefl;

	string ohbrhqkhpkgqcx(double wiegnhncqqv, int cfgcpvaqkqlomhv, double irtsodmasjbr, double weqbvmcvq);
	bool ufisnjxdaqinkph(int fjnoei, double chlduefxphjgeq, int mesctbnvajea, double qckaudtqbmjvwz, bool jjgkbtfxao, double ntunnxfhscbub, string vxsvenxcewfdfay, int xbkruktwxqopiat);
	void pczcbjlinnqnmevkvdjrgb(int rhqvyyjim, string thobkqc, double zyudgx);
	void yugcrnyadamug(int jhcrngsioyia, double xhsilqjmv, string rdkmullu, double tnmpu, string mqkytcoqiug);
	string jpwnamcavcwkegllhzi(double fihrlzld, string jzbkxdy);
	double zjqfugewxfrgkqsmmjwlay();
	double fkpgkngfakwpssrqikkbqfrsw(int cempislik, double misqtxhooj, double akkypsbrxw, double azvzjthixmzlhh, bool wxqwwlv, bool ediypgwmaumtah, bool rfybvgdhgoepj, double tozyhmeaciddojm);
	string xqvpivdgwqdxdg(bool ehxccdcppihou, bool qtzrzv, bool gouofkyngqjv, string ajkicll, string uihjqgmratjqchm, string ofkutwx);
	void byabywjyhqnuymrwdeplkyuh(bool ykpkuft);

};


string xzaoutv::ohbrhqkhpkgqcx(double wiegnhncqqv, int cfgcpvaqkqlomhv, double irtsodmasjbr, double weqbvmcvq) {
	double ssqzbojvbpcl = 20869;
	double zbyaoinydpjwl = 25088;
	double aumvzw = 12276;
	if (12276 != 12276) {
		int nn;
		for (nn = 7; nn > 0; nn--) {
			continue;
		}
	}
	if (25088 != 25088) {
		int jkssmgiy;
		for (jkssmgiy = 17; jkssmgiy > 0; jkssmgiy--) {
			continue;
		}
	}
	if (20869 == 20869) {
		int gncdtbac;
		for (gncdtbac = 2; gncdtbac > 0; gncdtbac--) {
			continue;
		}
	}
	if (12276 != 12276) {
		int tjmilml;
		for (tjmilml = 70; tjmilml > 0; tjmilml--) {
			continue;
		}
	}
	if (20869 == 20869) {
		int ucwzdte;
		for (ucwzdte = 37; ucwzdte > 0; ucwzdte--) {
			continue;
		}
	}
	return string("kalmsqffoanzyanmpkob");
}

bool xzaoutv::ufisnjxdaqinkph(int fjnoei, double chlduefxphjgeq, int mesctbnvajea, double qckaudtqbmjvwz, bool jjgkbtfxao, double ntunnxfhscbub, string vxsvenxcewfdfay, int xbkruktwxqopiat) {
	bool mknqbnmnd = true;
	double aelvuiu = 22504;
	bool llexvdeltgttfjx = true;
	bool suiregegeijamgl = false;
	string dzwgsfzk = "noyvhklgelaialduskjbjfcuxcyxzytogkafclxeqwlyvduwfcgnwsyhilb";
	bool foecncbht = true;
	int soezrb = 4160;
	int cqyjkvrlf = 4719;
	double expycvsvjhvrtkh = 43648;
	if (43648 == 43648) {
		int ocpoods;
		for (ocpoods = 85; ocpoods > 0; ocpoods--) {
			continue;
		}
	}
	if (22504 != 22504) {
		int hf;
		for (hf = 65; hf > 0; hf--) {
			continue;
		}
	}
	if (true == true) {
		int fgbxgdow;
		for (fgbxgdow = 59; fgbxgdow > 0; fgbxgdow--) {
			continue;
		}
	}
	if (22504 != 22504) {
		int bccdglkdf;
		for (bccdglkdf = 55; bccdglkdf > 0; bccdglkdf--) {
			continue;
		}
	}
	return false;
}

void xzaoutv::pczcbjlinnqnmevkvdjrgb(int rhqvyyjim, string thobkqc, double zyudgx) {

}

void xzaoutv::yugcrnyadamug(int jhcrngsioyia, double xhsilqjmv, string rdkmullu, double tnmpu, string mqkytcoqiug) {
	double ezofey = 8514;
	double avrwmlbhcv = 51127;
	int mtqph = 972;
	double ruxfllpc = 47387;
	if (47387 == 47387) {
		int gcupjf;
		for (gcupjf = 26; gcupjf > 0; gcupjf--) {
			continue;
		}
	}

}

string xzaoutv::jpwnamcavcwkegllhzi(double fihrlzld, string jzbkxdy) {
	return string("fadbmnsqoq");
}

double xzaoutv::zjqfugewxfrgkqsmmjwlay() {
	return 19983;
}

double xzaoutv::fkpgkngfakwpssrqikkbqfrsw(int cempislik, double misqtxhooj, double akkypsbrxw, double azvzjthixmzlhh, bool wxqwwlv, bool ediypgwmaumtah, bool rfybvgdhgoepj, double tozyhmeaciddojm) {
	bool gztxrlauuuy = false;
	string spiqwzdleqmzuhu = "qdlbxybiwlklibxbbdarwceepduhagvbogjpjeckvuoycqxlfibwvcswmbsfbztjifqoemvbclcbctzshtzoyvhbvqy";
	string mxdgfnkeumm = "fhtafjklmuehwuljiklylqqdutvdyqiobcujsfkfcfzfatukfiswiignoogoyjqkwjmbptaorugfosojomaazgdxtrrlnfae";
	bool jxomv = true;
	if (false == false) {
		int ggdmexk;
		for (ggdmexk = 69; ggdmexk > 0; ggdmexk--) {
			continue;
		}
	}
	if (true == true) {
		int alfhopfuuk;
		for (alfhopfuuk = 19; alfhopfuuk > 0; alfhopfuuk--) {
			continue;
		}
	}
	if (string("fhtafjklmuehwuljiklylqqdutvdyqiobcujsfkfcfzfatukfiswiignoogoyjqkwjmbptaorugfosojomaazgdxtrrlnfae") == string("fhtafjklmuehwuljiklylqqdutvdyqiobcujsfkfcfzfatukfiswiignoogoyjqkwjmbptaorugfosojomaazgdxtrrlnfae")) {
		int kgoqs;
		for (kgoqs = 63; kgoqs > 0; kgoqs--) {
			continue;
		}
	}
	if (false == false) {
		int ibb;
		for (ibb = 1; ibb > 0; ibb--) {
			continue;
		}
	}
	return 57056;
}

string xzaoutv::xqvpivdgwqdxdg(bool ehxccdcppihou, bool qtzrzv, bool gouofkyngqjv, string ajkicll, string uihjqgmratjqchm, string ofkutwx) {
	int dmvxnbadfxtih = 2228;
	int dnuqmntsvgfosp = 4276;
	bool ivetuny = true;
	double vnecvstabulf = 1844;
	string gfpcyxtvwktwdox = "xjudzqeatdugyqlwrgsdifbdchefkmtjhlfjkjmbjwj";
	string jiekotnwpnvb = "lmezpzhvmhnonmoviqrscjgvjgwpyywaeluyiauvgxlhwcvsjnbfjmdpuhxz";
	bool geakgbwsjbnzvwy = false;
	bool cpiznmmlmof = false;
	if (false != false) {
		int ytxpwtogt;
		for (ytxpwtogt = 40; ytxpwtogt > 0; ytxpwtogt--) {
			continue;
		}
	}
	if (string("xjudzqeatdugyqlwrgsdifbdchefkmtjhlfjkjmbjwj") != string("xjudzqeatdugyqlwrgsdifbdchefkmtjhlfjkjmbjwj")) {
		int efi;
		for (efi = 75; efi > 0; efi--) {
			continue;
		}
	}
	if (1844 == 1844) {
		int cipqmkppk;
		for (cipqmkppk = 1; cipqmkppk > 0; cipqmkppk--) {
			continue;
		}
	}
	return string("invcasixc");
}

void xzaoutv::byabywjyhqnuymrwdeplkyuh(bool ykpkuft) {
	string ylxryeit = "keujeirecxihcugpxwlplsbcrjwygskbfmsfrdthbjaanoeievcoufcijmwhubiwzagdongmfvwbf";
	bool krefwwesqbfzjj = true;
	string rtshuxlm = "gvjoywzrsmfotyidtmqujvldghhqnqvqecxwxsgigjwduzhzm";
	double sqxjvihzjyiulf = 46558;
	int albvjnddfqdyl = 4691;
	if (string("gvjoywzrsmfotyidtmqujvldghhqnqvqecxwxsgigjwduzhzm") != string("gvjoywzrsmfotyidtmqujvldghhqnqvqecxwxsgigjwduzhzm")) {
		int ejzimrino;
		for (ejzimrino = 95; ejzimrino > 0; ejzimrino--) {
			continue;
		}
	}
	if (4691 != 4691) {
		int ftr;
		for (ftr = 76; ftr > 0; ftr--) {
			continue;
		}
	}
	if (string("gvjoywzrsmfotyidtmqujvldghhqnqvqecxwxsgigjwduzhzm") == string("gvjoywzrsmfotyidtmqujvldghhqnqvqecxwxsgigjwduzhzm")) {
		int jfvfsumb;
		for (jfvfsumb = 98; jfvfsumb > 0; jfvfsumb--) {
			continue;
		}
	}
	if (string("gvjoywzrsmfotyidtmqujvldghhqnqvqecxwxsgigjwduzhzm") == string("gvjoywzrsmfotyidtmqujvldghhqnqvqecxwxsgigjwduzhzm")) {
		int tuzyofjfaf;
		for (tuzyofjfaf = 98; tuzyofjfaf > 0; tuzyofjfaf--) {
			continue;
		}
	}

}

double xzaoutv::zkybpwftyj(double gdytyigedw, int cptfteicvafmg, double ovpduygwypcndjp, bool aniyvgcu, int rjtvhshqoflyig, bool kwbecbtfcbzpd) {
	double mvvpm = 9583;
	bool yqwijhdrvafilbw = true;
	string zusxlrqic = "jxgozzcagjwauxnrvepeeogylvoyggjpossdlyozwksqhdczrexbeqgoxvjqwiscrsxescvglgjooutewfz";
	if (9583 != 9583) {
		int olobs;
		for (olobs = 86; olobs > 0; olobs--) {
			continue;
		}
	}
	if (string("jxgozzcagjwauxnrvepeeogylvoyggjpossdlyozwksqhdczrexbeqgoxvjqwiscrsxescvglgjooutewfz") == string("jxgozzcagjwauxnrvepeeogylvoyggjpossdlyozwksqhdczrexbeqgoxvjqwiscrsxescvglgjooutewfz")) {
		int bwstitdc;
		for (bwstitdc = 35; bwstitdc > 0; bwstitdc--) {
			continue;
		}
	}
	if (true != true) {
		int zapzgwepba;
		for (zapzgwepba = 12; zapzgwepba > 0; zapzgwepba--) {
			continue;
		}
	}
	if (string("jxgozzcagjwauxnrvepeeogylvoyggjpossdlyozwksqhdczrexbeqgoxvjqwiscrsxescvglgjooutewfz") != string("jxgozzcagjwauxnrvepeeogylvoyggjpossdlyozwksqhdczrexbeqgoxvjqwiscrsxescvglgjooutewfz")) {
		int ihgpvkye;
		for (ihgpvkye = 73; ihgpvkye > 0; ihgpvkye--) {
			continue;
		}
	}
	return 48658;
}

double xzaoutv::ymvytxozaubscebn() {
	return 29577;
}

void xzaoutv::tfpmbgsgguiecakgha(int peaoagvuq, double qqhbgj) {
	bool ikczozb = true;
	string pymddcer = "jedjvrgrtwmkxmhmx";
	int dbwsqgtablls = 3289;
	int emsyyfoo = 3509;
	double mphovlurtgbiazx = 20465;
	string xudbd = "wmfouamlgqwkyxlccayrnnvhtmllkmqgktjktvzuxqjqsrbyepyrdwu";
	bool xxhstn = false;
	if (3289 == 3289) {
		int gcwwj;
		for (gcwwj = 47; gcwwj > 0; gcwwj--) {
			continue;
		}
	}
	if (string("jedjvrgrtwmkxmhmx") != string("jedjvrgrtwmkxmhmx")) {
		int mvvcne;
		for (mvvcne = 92; mvvcne > 0; mvvcne--) {
			continue;
		}
	}
	if (false == false) {
		int yfztlbssix;
		for (yfztlbssix = 53; yfztlbssix > 0; yfztlbssix--) {
			continue;
		}
	}
	if (true != true) {
		int mdxe;
		for (mdxe = 25; mdxe > 0; mdxe--) {
			continue;
		}
	}

}

string xzaoutv::rlciawzvnhebmrjojndxdq(string xxlllbqawkow, double rpbuzselmsozfx) {
	double zwueqolgmef = 18181;
	bool dqwxhhtidsmg = false;
	string enjelkoohkjs = "hlcwudqepfypojyezguhzlwdcmsvcctwpbkdtvwxnkiozppzpcursziyywmyceyefdljvfstwnotezvfxxlvvbeece";
	bool xstiwfyepghwf = true;
	int ekfqyfabz = 826;
	bool bwzrxkka = false;
	bool vtlkn = true;
	string ynwkf = "gfclhckpzitkpkufclsbmjgwxyipgpupenksbpslnkuqrrcv";
	string nqlvhzvbrtcfj = "nmbgsidjvpcundlkahvmkqk";
	if (string("gfclhckpzitkpkufclsbmjgwxyipgpupenksbpslnkuqrrcv") == string("gfclhckpzitkpkufclsbmjgwxyipgpupenksbpslnkuqrrcv")) {
		int fkjbdf;
		for (fkjbdf = 23; fkjbdf > 0; fkjbdf--) {
			continue;
		}
	}
	if (string("nmbgsidjvpcundlkahvmkqk") != string("nmbgsidjvpcundlkahvmkqk")) {
		int nszlpd;
		for (nszlpd = 74; nszlpd > 0; nszlpd--) {
			continue;
		}
	}
	if (string("gfclhckpzitkpkufclsbmjgwxyipgpupenksbpslnkuqrrcv") == string("gfclhckpzitkpkufclsbmjgwxyipgpupenksbpslnkuqrrcv")) {
		int npwdxhoo;
		for (npwdxhoo = 78; npwdxhoo > 0; npwdxhoo--) {
			continue;
		}
	}
	if (18181 != 18181) {
		int famq;
		for (famq = 81; famq > 0; famq--) {
			continue;
		}
	}
	if (false != false) {
		int mk;
		for (mk = 77; mk > 0; mk--) {
			continue;
		}
	}
	return string("");
}

void xzaoutv::agrpswrfjeaeiipmvutbmd(int mdyuqahekvv, string pibfcloci, int dlxgbszrxoyyxxs, bool iyubuabpilgf, double axpzin, double pmxxvzzndkm, bool ygnzbfrezucop) {
	string lsuqxga = "txvlrzuxvbtyieprm";
	if (string("txvlrzuxvbtyieprm") == string("txvlrzuxvbtyieprm")) {
		int wdk;
		for (wdk = 78; wdk > 0; wdk--) {
			continue;
		}
	}
	if (string("txvlrzuxvbtyieprm") != string("txvlrzuxvbtyieprm")) {
		int elp;
		for (elp = 7; elp > 0; elp--) {
			continue;
		}
	}
	if (string("txvlrzuxvbtyieprm") == string("txvlrzuxvbtyieprm")) {
		int usigtyjoyo;
		for (usigtyjoyo = 30; usigtyjoyo > 0; usigtyjoyo--) {
			continue;
		}
	}

}

bool xzaoutv::lyideorkrweuyonspuzzqggeu(double guklxwrjlhncuxo) {
	double mhglaginrh = 79523;
	bool zcpvjojbqtcwcwr = false;
	bool zmfgxebrz = false;
	double kmmnm = 7331;
	bool aibuzm = true;
	double ezbcrwgeahmuzle = 10306;
	if (10306 == 10306) {
		int unze;
		for (unze = 82; unze > 0; unze--) {
			continue;
		}
	}
	if (10306 != 10306) {
		int hklymia;
		for (hklymia = 16; hklymia > 0; hklymia--) {
			continue;
		}
	}
	if (false != false) {
		int ttj;
		for (ttj = 82; ttj > 0; ttj--) {
			continue;
		}
	}
	if (79523 != 79523) {
		int boecycv;
		for (boecycv = 69; boecycv > 0; boecycv--) {
			continue;
		}
	}
	if (false != false) {
		int gxunuatdep;
		for (gxunuatdep = 19; gxunuatdep > 0; gxunuatdep--) {
			continue;
		}
	}
	return true;
}

bool xzaoutv::gdjlfdmsyyenidiopxgphoncd(double gcjfgjmxsw, double rolahuii) {
	int nzajuqws = 1082;
	string easzjshelhzovtz = "twmidxygugktgflwitvylbrldaonzxoox";
	int rqfspwwzsmpokmt = 1324;
	string bcsodvhesibnr = "ylfwvywzvvrkcyxvylnbabavsozzfjwcwartdvfeudfcihiavbsmbqxothtvftnocsrjyeuipjgnezbjdmpcvdcqhvzpohjtvp";
	if (1082 == 1082) {
		int alms;
		for (alms = 36; alms > 0; alms--) {
			continue;
		}
	}
	if (1082 != 1082) {
		int dwottstip;
		for (dwottstip = 84; dwottstip > 0; dwottstip--) {
			continue;
		}
	}
	return false;
}

double xzaoutv::rmuavceabxmv(bool mkqmckzizuxeng, int lrnna) {
	int iucpntj = 2431;
	string vkkjgh = "wmqckdpbcxghfchitfposjpzuxpuwvvwwutuvvrcdwixwtyksouhsjstfzairovfooujerctlvsgovemv";
	int fkzdvjmgmw = 3990;
	double xbegfnksc = 34974;
	string sujamtc = "oddeergtzvkosjagdfiktxzhvfcwcygcnzxgsizmczwjmoiiwdzkknznundvfgojgnoznrdikpwpbniirzgnsfhszgox";
	if (string("oddeergtzvkosjagdfiktxzhvfcwcygcnzxgsizmczwjmoiiwdzkknznundvfgojgnoznrdikpwpbniirzgnsfhszgox") != string("oddeergtzvkosjagdfiktxzhvfcwcygcnzxgsizmczwjmoiiwdzkknznundvfgojgnoznrdikpwpbniirzgnsfhszgox")) {
		int qvrhtb;
		for (qvrhtb = 25; qvrhtb > 0; qvrhtb--) {
			continue;
		}
	}
	if (string("oddeergtzvkosjagdfiktxzhvfcwcygcnzxgsizmczwjmoiiwdzkknznundvfgojgnoznrdikpwpbniirzgnsfhszgox") != string("oddeergtzvkosjagdfiktxzhvfcwcygcnzxgsizmczwjmoiiwdzkknznundvfgojgnoznrdikpwpbniirzgnsfhszgox")) {
		int nd;
		for (nd = 41; nd > 0; nd--) {
			continue;
		}
	}
	if (2431 != 2431) {
		int vgtyfnhxk;
		for (vgtyfnhxk = 0; vgtyfnhxk > 0; vgtyfnhxk--) {
			continue;
		}
	}
	if (3990 != 3990) {
		int keumy;
		for (keumy = 27; keumy > 0; keumy--) {
			continue;
		}
	}
	if (34974 == 34974) {
		int ss;
		for (ss = 36; ss > 0; ss--) {
			continue;
		}
	}
	return 76276;
}

void xzaoutv::exbvicqfzpmicotvrcxyyx(string xlwnmie, double imbhda, double vybzfda, double aptljhzudgw, bool cmcfvaxps, string hjeqikawavdpfwi, int xikctrjh, int adxmidclfw, string ypystaflhvp) {
	double ysxfijnx = 12355;
	bool ahdrnvbpcahwvgf = true;
	double pbaivlykreanaqc = 41318;
	int ygkug = 4677;
	double ziuqythbsqo = 46105;
	if (41318 != 41318) {
		int exufqg;
		for (exufqg = 48; exufqg > 0; exufqg--) {
			continue;
		}
	}

}

double xzaoutv::gjjqbskvkks() {
	double xtdrtie = 44307;
	double jeirpavp = 6036;
	bool wlbvjvlbbu = false;
	if (false != false) {
		int stccyh;
		for (stccyh = 21; stccyh > 0; stccyh--) {
			continue;
		}
	}
	if (6036 != 6036) {
		int my;
		for (my = 36; my > 0; my--) {
			continue;
		}
	}
	if (44307 != 44307) {
		int vyzpekniyr;
		for (vyzpekniyr = 67; vyzpekniyr > 0; vyzpekniyr--) {
			continue;
		}
	}
	if (44307 == 44307) {
		int fh;
		for (fh = 2; fh > 0; fh--) {
			continue;
		}
	}
	return 52649;
}

void xzaoutv::drddzlnqrfvgbymfms(bool voevhkztmw, double cdcvsvkarn, int xqznetdalsrqrbx, bool wdmpvgrqtmcget, int xtzwrwmdei) {
	string zolvpnpwbgt = "bqcvennoggmqgarzpcxznfuwpkverpdnaxpagpmnvvspzhwjeey";
	string idotjgkp = "dlytqwvmkwuwlob";
	string uabrcjp = "mbsbxjeemjsoaarpdlfvgtabfjgwlaknoxflxmwbqlvrslivcsazjaqqoixeqxwcnqivopebdjhzysgvlfzfpulqnzwzmo";
	double umdjjucyqgjsrbs = 19987;
	double bfmzzcpedkfc = 15617;
	if (19987 != 19987) {
		int cjqwgk;
		for (cjqwgk = 14; cjqwgk > 0; cjqwgk--) {
			continue;
		}
	}
	if (string("dlytqwvmkwuwlob") == string("dlytqwvmkwuwlob")) {
		int nfewjrie;
		for (nfewjrie = 3; nfewjrie > 0; nfewjrie--) {
			continue;
		}
	}
	if (string("dlytqwvmkwuwlob") == string("dlytqwvmkwuwlob")) {
		int rk;
		for (rk = 46; rk > 0; rk--) {
			continue;
		}
	}
	if (string("dlytqwvmkwuwlob") != string("dlytqwvmkwuwlob")) {
		int xroszbxoiu;
		for (xroszbxoiu = 12; xroszbxoiu > 0; xroszbxoiu--) {
			continue;
		}
	}

}

xzaoutv::xzaoutv() {
	this->gjjqbskvkks();
	this->drddzlnqrfvgbymfms(false, 40130, 842, false, 2410);
	this->zkybpwftyj(10628, 5334, 76054, false, 2399, false);
	this->ymvytxozaubscebn();
	this->tfpmbgsgguiecakgha(1156, 31938);
	this->rlciawzvnhebmrjojndxdq(string("vrlismatuozjpkbvyuxvfhktyalxrkofcallhfztnfyxfnqrjnfmljfgjdfsbokqirfgxlmlkwd"), 43528);
	this->agrpswrfjeaeiipmvutbmd(2512, string("bbotrtwrgvdfhujpzukizkkhtfpbfpnrnjmysldtqgwzcwtcfpazyyvlkgmghwtfgtiuvydswef"), 565, false, 14712, 4212, true);
	this->lyideorkrweuyonspuzzqggeu(34594);
	this->gdjlfdmsyyenidiopxgphoncd(16958, 22612);
	this->rmuavceabxmv(false, 2111);
	this->exbvicqfzpmicotvrcxyyx(string(""), 9231, 1563, 7196, false, string("yaboexapnorlkcxjhcxztyvhzzgngmgzhntlwsfeceqzmenkzmskbccytzfmseexacachbvcrofsuktjiayeakczogeev"), 6851, 742, string("iznctiqfesyuszniltakarhwqgmrhckxwygvkabvlfwjkpyhgxrntdwjusmhhaavrjehgiglnhkyuwxv"));
	this->ohbrhqkhpkgqcx(5514, 2412, 40784, 3270);
	this->ufisnjxdaqinkph(7624, 11619, 8780, 17678, false, 21562, string("xpddxikbezlzwnxqetcjrschlgwley"), 4081);
	this->pczcbjlinnqnmevkvdjrgb(1186, string("nmooslcfyqoysvstvruphorzmrcgjgqzifufgzhrxsfpgykigvfhptevqplqhcckrnswppttecqvzzqxf"), 367);
	this->yugcrnyadamug(601, 9786, string("uqtnhrckeuwejquzmdtnrrnvtetkdnoxictejrlcblvyyqhiftnicqlpufljwrziqhefmajoliwltbxsknefuaacmmboncucxp"), 8146, string("pnzxfttqriigoelzsivq"));
	this->jpwnamcavcwkegllhzi(632, string("eyaijygvfblhhciqkqkmigdhdfqctcncobtstqyhhicdathfrbr"));
	this->zjqfugewxfrgkqsmmjwlay();
	this->fkpgkngfakwpssrqikkbqfrsw(5329, 5006, 17071, 9534, false, true, false, 31048);
	this->xqvpivdgwqdxdg(true, true, true, string("wdvfwkrzsvyievsktfmpniokfprincjtflhotvxfhgldvgasnmugrmnglxeoikjghqpwezwnfcwsipmrzgcnbcr"), string("wariimehwbrjpuvcpeagqotwvbslynwfchlyyxpisdnwdsqthftrjlbzbxlmrspkqadxuppqxzu"), string("stlibtgjfipkxwnsonzitqx"));
	this->byabywjyhqnuymrwdeplkyuh(false);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class qmsrqym {
public:
	int wokfdajhchwx;
	qmsrqym();
	string oeibsyxnzcxvnxkmgnof(bool mriktqbnozzw, bool lhmbmaj, int qphitlprtjc);
	double mblscwprdjkhejzpwloletl(bool ravgeavs, double eplunwravdq, double nmbqfwpdne, double nhsiupfwvrsf, double rgqrpctfinska);
	void acmyuwmfmkmp(string evbrvvspev, double gbctpi);
	bool bjhllxhnax(double hlxnpjxquvqtx, int qorffkpgpinsrwr, double hjqsrgmzcadi, double jpeyxxp, bool qupilwpeq, string csgzdazodca, int nlaentxist);
	double krgmncpukhiephvo(int ktloaohhuqszue, string jmhleipt, string xxqvw, double ftmlbjdnc, bool pnhbzlcpaj, double kdnhoqwkqfacav, bool hwkvsrwne, bool qoiaxnytijs);
	int bkewvykfwafdgciulmgdecgb(bool mzzbwhgom, string hlcvlivdr, double rxjspozjddms, double hhoxodwraujx, string yqpra, bool vnfpuelan);
	string qadfwbakkyznb();
	int ceccroabdvpepdurahejzwb(string zozysu, double hmxog);

protected:
	bool kqsrmgkshklcddy;
	double oidynosu;

	string qhxcmoitikifqhytdz(bool iikxpgwfce, bool soxxaeeoqrhbm, int lovyel, bool xgiav, bool ehqrvyv, double qjdowchvbvmzhhf, int hxhzhxa);
	int qkkxtfiggqslzwffjttvtnm(bool eskmmsrqtwo, bool hawcgfcrpnnlloj, int xfbhjmhxp);
	string bcfwseatdxfofspzypjxveqda(double tgqth);
	int hqzmvpurezn(int hdmanrhcsnslga, int skpkqsqbhhvsyr, int cfuzivyvatlva, bool hwhdwtolsjj, string lpvubkipkhuqxbn, string vunfwdcjyfgsrt, bool vjpagiw);
	int wtddddtkhnesqn(bool zckrbqdcbfwtpxx, double yhuvdsqplxlpsg, bool babrtzclay, int onzekmikfl, int rtghonnkt, double tkuxndaarolgprg, string eabnweafnz, string uemhvevxuzr);
	void gkomyjsgpcfevqfvqxhvkpup(bool padzaxrz, double zftwznodpkyasds, double dtxdbfyay, bool ltcma, int muibsuswc, string zcchpmglwe, int iwesutfwzkba, string gxawgwpybzasgj, bool pambjgjbixytboo);
	bool nmnyfyzdrkyjpctkzxz(double umxwwnjhawmgvh, double ohwdwvwyoweyzr, bool jcpxkwsiqiiqjl, string gsphkzonsuziz, string lambyejsmtmw, int wksym, string yontfjwvfdmwh, bool pyjcnogujru);
	void vzdzxerjmb(int mbcmjpxahbxyt);

private:
	double lkgvetboku;
	string bkcdtiwgw;

	int bkwtxfzlbvgqcbas(bool kustaqxu, int gzcgzxxyvszur, int dftbm, bool tsqrdorphad, int rtvlxclwwx, int tnrnxfobjjljmro, string gyfpxctmbmnktq, bool acvifxkmd, bool iejhhcwuomqxl, string ydvrohe);
	int ecamjndwoboqhb(bool krualdh, string nesbgobxxoacx, double mhhrcxtcgdpsue, double osyqaxes, bool ktklchfarmkpbcl, bool exbxlodfvchnw, string vwfwpwgfjsbtk);
	double uweabtbmoprk(string pyxjuynj, int eslonhnoc);

};


int qmsrqym::bkwtxfzlbvgqcbas(bool kustaqxu, int gzcgzxxyvszur, int dftbm, bool tsqrdorphad, int rtvlxclwwx, int tnrnxfobjjljmro, string gyfpxctmbmnktq, bool acvifxkmd, bool iejhhcwuomqxl, string ydvrohe) {
	int miycroiart = 125;
	bool ocxdbbzg = true;
	string jtfadnb = "obojmqjjumwf";
	if (125 != 125) {
		int aexueidb;
		for (aexueidb = 24; aexueidb > 0; aexueidb--) {
			continue;
		}
	}
	return 83495;
}

int qmsrqym::ecamjndwoboqhb(bool krualdh, string nesbgobxxoacx, double mhhrcxtcgdpsue, double osyqaxes, bool ktklchfarmkpbcl, bool exbxlodfvchnw, string vwfwpwgfjsbtk) {
	return 85373;
}

double qmsrqym::uweabtbmoprk(string pyxjuynj, int eslonhnoc) {
	string uoifdofhwye = "rmqkeyumefgwjxygrfkgitfwvgmapqrlhtbmnjyizwfh";
	if (string("rmqkeyumefgwjxygrfkgitfwvgmapqrlhtbmnjyizwfh") == string("rmqkeyumefgwjxygrfkgitfwvgmapqrlhtbmnjyizwfh")) {
		int tirc;
		for (tirc = 78; tirc > 0; tirc--) {
			continue;
		}
	}
	if (string("rmqkeyumefgwjxygrfkgitfwvgmapqrlhtbmnjyizwfh") != string("rmqkeyumefgwjxygrfkgitfwvgmapqrlhtbmnjyizwfh")) {
		int xhfndndd;
		for (xhfndndd = 64; xhfndndd > 0; xhfndndd--) {
			continue;
		}
	}
	if (string("rmqkeyumefgwjxygrfkgitfwvgmapqrlhtbmnjyizwfh") != string("rmqkeyumefgwjxygrfkgitfwvgmapqrlhtbmnjyizwfh")) {
		int ealcwfz;
		for (ealcwfz = 89; ealcwfz > 0; ealcwfz--) {
			continue;
		}
	}
	return 71300;
}

string qmsrqym::qhxcmoitikifqhytdz(bool iikxpgwfce, bool soxxaeeoqrhbm, int lovyel, bool xgiav, bool ehqrvyv, double qjdowchvbvmzhhf, int hxhzhxa) {
	int gdltoqhdasws = 263;
	string ydbiirnjnjil = "rwrtdzarwkxdsaniwhefqwdgydtbfkrmujydfibylvmqkvimuicbjhdwfymgxizbkarydaqosthvypbjues";
	int igfcdelldytfch = 4719;
	bool tqvrrnlfg = false;
	int rlednp = 1151;
	double quigmzag = 682;
	bool wcqmefyqk = true;
	string maynfhux = "eypjdubzkjdmmqasjrrhlaekznaqukcepnpuvqfpdchvwpggmlwuqubgewayrapygiavidflvmk";
	double owzyosvyalauhxl = 20428;
	string cdbbkl = "th";
	if (false == false) {
		int xx;
		for (xx = 25; xx > 0; xx--) {
			continue;
		}
	}
	if (682 != 682) {
		int qfksbpy;
		for (qfksbpy = 91; qfksbpy > 0; qfksbpy--) {
			continue;
		}
	}
	return string("vyfuaqpeuct");
}

int qmsrqym::qkkxtfiggqslzwffjttvtnm(bool eskmmsrqtwo, bool hawcgfcrpnnlloj, int xfbhjmhxp) {
	bool vbskqf = true;
	string bfoqchahyuobcg = "connprdiiyjynkjwnwoqkphyaliwiydqahiujxawtzhpncduxribggvalavfyxzxxpzrqnjxkfcyxysrgzxc";
	double tyiwaywazjm = 97525;
	string fudftrflljdzmti = "hfwziiclpmdunlzbkxwfijoxkhnckdzagntsznak";
	bool vtrwrjkbt = false;
	bool kryij = false;
	if (string("connprdiiyjynkjwnwoqkphyaliwiydqahiujxawtzhpncduxribggvalavfyxzxxpzrqnjxkfcyxysrgzxc") != string("connprdiiyjynkjwnwoqkphyaliwiydqahiujxawtzhpncduxribggvalavfyxzxxpzrqnjxkfcyxysrgzxc")) {
		int dyvyeudpwe;
		for (dyvyeudpwe = 18; dyvyeudpwe > 0; dyvyeudpwe--) {
			continue;
		}
	}
	if (false != false) {
		int uxnckr;
		for (uxnckr = 83; uxnckr > 0; uxnckr--) {
			continue;
		}
	}
	if (false != false) {
		int cwquu;
		for (cwquu = 28; cwquu > 0; cwquu--) {
			continue;
		}
	}
	return 10340;
}

string qmsrqym::bcfwseatdxfofspzypjxveqda(double tgqth) {
	return string("hzdiqhu");
}

int qmsrqym::hqzmvpurezn(int hdmanrhcsnslga, int skpkqsqbhhvsyr, int cfuzivyvatlva, bool hwhdwtolsjj, string lpvubkipkhuqxbn, string vunfwdcjyfgsrt, bool vjpagiw) {
	string ypcbfmuqkbzuvof = "mf";
	string wdzmdwajdlyixy = "wlwpnisiiolbedsxjdamnnebnsjkeqqlvebxexlhmmijhnbnlhockcbazlcwlzzhgrlbwqvotvvjucyjevsuefyvjyodsh";
	bool xbtaxcdsyezayjk = true;
	double wyaelpyziakgaf = 80009;
	bool pbmchlt = false;
	string cwpzpellh = "ekxwpxwuqjrbgcrngsnygmyvizi";
	double oxnxbkjx = 5500;
	if (5500 == 5500) {
		int rpufzxel;
		for (rpufzxel = 52; rpufzxel > 0; rpufzxel--) {
			continue;
		}
	}
	if (string("ekxwpxwuqjrbgcrngsnygmyvizi") == string("ekxwpxwuqjrbgcrngsnygmyvizi")) {
		int bsptw;
		for (bsptw = 13; bsptw > 0; bsptw--) {
			continue;
		}
	}
	if (string("mf") == string("mf")) {
		int mdxkgc;
		for (mdxkgc = 3; mdxkgc > 0; mdxkgc--) {
			continue;
		}
	}
	if (80009 != 80009) {
		int gdum;
		for (gdum = 60; gdum > 0; gdum--) {
			continue;
		}
	}
	return 44263;
}

int qmsrqym::wtddddtkhnesqn(bool zckrbqdcbfwtpxx, double yhuvdsqplxlpsg, bool babrtzclay, int onzekmikfl, int rtghonnkt, double tkuxndaarolgprg, string eabnweafnz, string uemhvevxuzr) {
	bool dnqqnqapz = true;
	if (true != true) {
		int gqlkfq;
		for (gqlkfq = 55; gqlkfq > 0; gqlkfq--) {
			continue;
		}
	}
	if (true == true) {
		int fxuu;
		for (fxuu = 42; fxuu > 0; fxuu--) {
			continue;
		}
	}
	if (true == true) {
		int ydjnygk;
		for (ydjnygk = 6; ydjnygk > 0; ydjnygk--) {
			continue;
		}
	}
	return 31853;
}

void qmsrqym::gkomyjsgpcfevqfvqxhvkpup(bool padzaxrz, double zftwznodpkyasds, double dtxdbfyay, bool ltcma, int muibsuswc, string zcchpmglwe, int iwesutfwzkba, string gxawgwpybzasgj, bool pambjgjbixytboo) {
	string ipottzoin = "jehy";
	string jjafwsluec = "yauihrqwujwehxvuxtkwkfmfkmgrosufykedzttwexvs";
	bool tzalmbjlkv = false;
	string yoexrrfdygyckts = "pskffbhmbiparnnpolblgqfpgsukikzmburkeoqocdwxhkxedvdpejeeawmtthohtmbyjrohewbapvtpsrzqfvcchh";
	int ougfkiogrorbp = 2706;
	double lpmqrujutqglpb = 83433;
	string ifztigerqxjkvg = "hiebpywcjpcnzdvpbbqujogpntncfxmqwytcfudjraugwwymvp";
	string catepep = "tzhkrdpiuxirddcsjmppfcutrbhgyqiwgznijozfipswqjciikrloszqsbp";
	if (83433 == 83433) {
		int wqblkhi;
		for (wqblkhi = 94; wqblkhi > 0; wqblkhi--) {
			continue;
		}
	}
	if (string("hiebpywcjpcnzdvpbbqujogpntncfxmqwytcfudjraugwwymvp") != string("hiebpywcjpcnzdvpbbqujogpntncfxmqwytcfudjraugwwymvp")) {
		int pcqzjjmgh;
		for (pcqzjjmgh = 68; pcqzjjmgh > 0; pcqzjjmgh--) {
			continue;
		}
	}
	if (false == false) {
		int uz;
		for (uz = 42; uz > 0; uz--) {
			continue;
		}
	}
	if (string("yauihrqwujwehxvuxtkwkfmfkmgrosufykedzttwexvs") == string("yauihrqwujwehxvuxtkwkfmfkmgrosufykedzttwexvs")) {
		int nfpy;
		for (nfpy = 22; nfpy > 0; nfpy--) {
			continue;
		}
	}
	if (string("pskffbhmbiparnnpolblgqfpgsukikzmburkeoqocdwxhkxedvdpejeeawmtthohtmbyjrohewbapvtpsrzqfvcchh") != string("pskffbhmbiparnnpolblgqfpgsukikzmburkeoqocdwxhkxedvdpejeeawmtthohtmbyjrohewbapvtpsrzqfvcchh")) {
		int vlvlhvwejv;
		for (vlvlhvwejv = 65; vlvlhvwejv > 0; vlvlhvwejv--) {
			continue;
		}
	}

}

bool qmsrqym::nmnyfyzdrkyjpctkzxz(double umxwwnjhawmgvh, double ohwdwvwyoweyzr, bool jcpxkwsiqiiqjl, string gsphkzonsuziz, string lambyejsmtmw, int wksym, string yontfjwvfdmwh, bool pyjcnogujru) {
	bool aeevf = true;
	double nkyylqizhkhclq = 42304;
	string brhyzu = "vyiryckmuuapygtimzvyhwmayhdixavgrfsmrftjfkkihvutbouujxrilxmysnkfqhqgtidxohdlzrdwf";
	bool ssjfwtfmrr = true;
	string wqqbggjv = "ygxevsezcjhmnadszqnkfgsjzbgkamvcleecpsarzcnkcohakefssoxaqavbmngdzkddseebyxxfgmekslri";
	double upztskhv = 25358;
	string rvmfgkz = "couzytsuqixqznrvfbypulnlmuiwljiybriwejizmvlmrjqmbcyuoshwvjvzehrukovazwkrvulclukqizlocrwhheg";
	string pidscdiygiv = "dzbtmoxnvzdaspggtvgotnisdtpkcpibammysytrfdzveflifbktlp";
	bool vkgvp = true;
	if (string("vyiryckmuuapygtimzvyhwmayhdixavgrfsmrftjfkkihvutbouujxrilxmysnkfqhqgtidxohdlzrdwf") != string("vyiryckmuuapygtimzvyhwmayhdixavgrfsmrftjfkkihvutbouujxrilxmysnkfqhqgtidxohdlzrdwf")) {
		int gmreypvra;
		for (gmreypvra = 19; gmreypvra > 0; gmreypvra--) {
			continue;
		}
	}
	if (true == true) {
		int tjwoc;
		for (tjwoc = 34; tjwoc > 0; tjwoc--) {
			continue;
		}
	}
	if (42304 != 42304) {
		int vznx;
		for (vznx = 55; vznx > 0; vznx--) {
			continue;
		}
	}
	if (42304 == 42304) {
		int swrlk;
		for (swrlk = 47; swrlk > 0; swrlk--) {
			continue;
		}
	}
	if (42304 != 42304) {
		int dyxljff;
		for (dyxljff = 27; dyxljff > 0; dyxljff--) {
			continue;
		}
	}
	return false;
}

void qmsrqym::vzdzxerjmb(int mbcmjpxahbxyt) {
	string jcolxjl = "okdlafixcetidpgnlfmhkaelffebaxmlhtzulongjyvixsyurdhtrjlykzgqrhsyhovvepfvavcqa";
	int gadtjehenoaasc = 3554;
	int ukjyzrwhjzrugrl = 2380;
	if (string("okdlafixcetidpgnlfmhkaelffebaxmlhtzulongjyvixsyurdhtrjlykzgqrhsyhovvepfvavcqa") == string("okdlafixcetidpgnlfmhkaelffebaxmlhtzulongjyvixsyurdhtrjlykzgqrhsyhovvepfvavcqa")) {
		int ciu;
		for (ciu = 60; ciu > 0; ciu--) {
			continue;
		}
	}

}

string qmsrqym::oeibsyxnzcxvnxkmgnof(bool mriktqbnozzw, bool lhmbmaj, int qphitlprtjc) {
	bool viclpcnvc = false;
	string wlhvykotljmyf = "qoiuwmhpkwogqzzaceevovsunrfkzzpbxvgmoylqoolmptudaubiwijsosxfepnhwkmixftkupnmnmsuitbiklcjlevoopullul";
	double qjponkznqf = 17616;
	int plstgc = 48;
	string igmfkqgefp = "zyyprpliwqesrclqsslle";
	bool qjozgkwgpnouv = false;
	bool nufqsvhv = true;
	int baphvpoucpylwdi = 1068;
	string hjzwlb = "xmieykmleefvjpjcbcb";
	bool mdphsoxtdvxsinl = true;
	if (string("xmieykmleefvjpjcbcb") == string("xmieykmleefvjpjcbcb")) {
		int ovxdu;
		for (ovxdu = 59; ovxdu > 0; ovxdu--) {
			continue;
		}
	}
	if (true != true) {
		int ff;
		for (ff = 32; ff > 0; ff--) {
			continue;
		}
	}
	if (string("qoiuwmhpkwogqzzaceevovsunrfkzzpbxvgmoylqoolmptudaubiwijsosxfepnhwkmixftkupnmnmsuitbiklcjlevoopullul") == string("qoiuwmhpkwogqzzaceevovsunrfkzzpbxvgmoylqoolmptudaubiwijsosxfepnhwkmixftkupnmnmsuitbiklcjlevoopullul")) {
		int nkjw;
		for (nkjw = 97; nkjw > 0; nkjw--) {
			continue;
		}
	}
	if (true != true) {
		int deohzx;
		for (deohzx = 91; deohzx > 0; deohzx--) {
			continue;
		}
	}
	if (string("zyyprpliwqesrclqsslle") != string("zyyprpliwqesrclqsslle")) {
		int fs;
		for (fs = 34; fs > 0; fs--) {
			continue;
		}
	}
	return string("xhtnbmsigdvjtaizqlk");
}

double qmsrqym::mblscwprdjkhejzpwloletl(bool ravgeavs, double eplunwravdq, double nmbqfwpdne, double nhsiupfwvrsf, double rgqrpctfinska) {
	string ugjhztisn = "ldlnffdtijvlqvrkjwxydqdrajzridbsirursfhmgeecsudiqqiqhnazkcwrcvetkzibdmoyrcbqnu";
	return 32815;
}

void qmsrqym::acmyuwmfmkmp(string evbrvvspev, double gbctpi) {
	double hgmfoiuawcjvww = 1527;

}

bool qmsrqym::bjhllxhnax(double hlxnpjxquvqtx, int qorffkpgpinsrwr, double hjqsrgmzcadi, double jpeyxxp, bool qupilwpeq, string csgzdazodca, int nlaentxist) {
	bool sohlpf = true;
	string qpqwblxsfuxk = "mmybzjaleewyvivxptbvtzvbfzmyizognohxmibbciesdhndmxsxzadly";
	string oabzvjjdsjitg = "ertlxyjhfaxbsnisksfcgycfplsagbqmceylndkplxefvixeeswtwvcghjxnpscrhrjmtoex";
	if (string("mmybzjaleewyvivxptbvtzvbfzmyizognohxmibbciesdhndmxsxzadly") == string("mmybzjaleewyvivxptbvtzvbfzmyizognohxmibbciesdhndmxsxzadly")) {
		int basfqhx;
		for (basfqhx = 9; basfqhx > 0; basfqhx--) {
			continue;
		}
	}
	if (true == true) {
		int hstgzjm;
		for (hstgzjm = 94; hstgzjm > 0; hstgzjm--) {
			continue;
		}
	}
	return false;
}

double qmsrqym::krgmncpukhiephvo(int ktloaohhuqszue, string jmhleipt, string xxqvw, double ftmlbjdnc, bool pnhbzlcpaj, double kdnhoqwkqfacav, bool hwkvsrwne, bool qoiaxnytijs) {
	string bmbsvunbanz = "frmhiflegzqffuvimviellzmlezkwbnvrcqvap";
	string pntzr = "zxaqntnqqspbxvzdgzgwljgiiugepctidrycyoktirhujcgvrovrgjcyzikkll";
	int twjnjebns = 3008;
	string hyvfavoxayzrmo = "khyjtyhsshhkwzz";
	bool posyne = false;
	string opodhzlnutzzt = "ctkfulfqppwtfwwzogmwnspfhcuroatjcqxblsjajdndnfxcsucvqwxaapmocidnigpzkrsxzxzfagp";
	int shncauoqqhua = 1497;
	double sgqrylgsn = 4660;
	string ykirrrevrebmluc = "f";
	if (string("ctkfulfqppwtfwwzogmwnspfhcuroatjcqxblsjajdndnfxcsucvqwxaapmocidnigpzkrsxzxzfagp") != string("ctkfulfqppwtfwwzogmwnspfhcuroatjcqxblsjajdndnfxcsucvqwxaapmocidnigpzkrsxzxzfagp")) {
		int chqckpiw;
		for (chqckpiw = 58; chqckpiw > 0; chqckpiw--) {
			continue;
		}
	}
	if (string("khyjtyhsshhkwzz") == string("khyjtyhsshhkwzz")) {
		int urwidk;
		for (urwidk = 91; urwidk > 0; urwidk--) {
			continue;
		}
	}
	if (string("frmhiflegzqffuvimviellzmlezkwbnvrcqvap") == string("frmhiflegzqffuvimviellzmlezkwbnvrcqvap")) {
		int cxiv;
		for (cxiv = 41; cxiv > 0; cxiv--) {
			continue;
		}
	}
	if (string("frmhiflegzqffuvimviellzmlezkwbnvrcqvap") == string("frmhiflegzqffuvimviellzmlezkwbnvrcqvap")) {
		int itcyjysyvs;
		for (itcyjysyvs = 22; itcyjysyvs > 0; itcyjysyvs--) {
			continue;
		}
	}
	if (string("frmhiflegzqffuvimviellzmlezkwbnvrcqvap") != string("frmhiflegzqffuvimviellzmlezkwbnvrcqvap")) {
		int yxzb;
		for (yxzb = 1; yxzb > 0; yxzb--) {
			continue;
		}
	}
	return 59214;
}

int qmsrqym::bkewvykfwafdgciulmgdecgb(bool mzzbwhgom, string hlcvlivdr, double rxjspozjddms, double hhoxodwraujx, string yqpra, bool vnfpuelan) {
	int yqpkbphgob = 1759;
	double blgfvemfwvntds = 13344;
	bool qqijctyqrzyxb = false;
	double smgmgq = 79847;
	double etkommmrljavr = 35586;
	string uvguamkj = "bfybezizaditathnnqhonvijctyyenimeyvqgxqzuypmasghsmxgcjcluboanmzgpnxtka";
	if (string("bfybezizaditathnnqhonvijctyyenimeyvqgxqzuypmasghsmxgcjcluboanmzgpnxtka") != string("bfybezizaditathnnqhonvijctyyenimeyvqgxqzuypmasghsmxgcjcluboanmzgpnxtka")) {
		int ifgzsavdgc;
		for (ifgzsavdgc = 99; ifgzsavdgc > 0; ifgzsavdgc--) {
			continue;
		}
	}
	return 315;
}

string qmsrqym::qadfwbakkyznb() {
	int eodnt = 799;
	bool kdewjfbre = false;
	string upodkc = "hpnzooezyjcxrukahdreyzktnzrqtwtadgiykqcphqukfcpdjjhhfpagoioeyciateoskuu";
	int ykidu = 3419;
	bool urbeurfdin = false;
	int ggeptviadh = 1636;
	int wutiloiofphw = 5660;
	double sfglttiyidfoddy = 33345;
	if (1636 != 1636) {
		int es;
		for (es = 100; es > 0; es--) {
			continue;
		}
	}
	if (3419 == 3419) {
		int jiz;
		for (jiz = 87; jiz > 0; jiz--) {
			continue;
		}
	}
	return string("");
}

int qmsrqym::ceccroabdvpepdurahejzwb(string zozysu, double hmxog) {
	bool imjntoze = true;
	string mwnwzzktkf = "dhmtrmnvisgpmcoqremfniixt";
	int brzwl = 361;
	string iaqupvwcodh = "fflbtsaadarzduspnwakzscmkzqnapmoxtkngmwgtinbbsoh";
	int iffjtfmtchvwrhe = 1321;
	if (true != true) {
		int nxienrbix;
		for (nxienrbix = 77; nxienrbix > 0; nxienrbix--) {
			continue;
		}
	}
	if (1321 != 1321) {
		int qmxave;
		for (qmxave = 5; qmxave > 0; qmxave--) {
			continue;
		}
	}
	if (1321 == 1321) {
		int uhjzqqjzk;
		for (uhjzqqjzk = 88; uhjzqqjzk > 0; uhjzqqjzk--) {
			continue;
		}
	}
	if (true == true) {
		int jqos;
		for (jqos = 48; jqos > 0; jqos--) {
			continue;
		}
	}
	if (string("dhmtrmnvisgpmcoqremfniixt") == string("dhmtrmnvisgpmcoqremfniixt")) {
		int byntqkpvx;
		for (byntqkpvx = 58; byntqkpvx > 0; byntqkpvx--) {
			continue;
		}
	}
	return 19492;
}

qmsrqym::qmsrqym() {
	this->oeibsyxnzcxvnxkmgnof(true, false, 1090);
	this->mblscwprdjkhejzpwloletl(true, 78, 40472, 305, 3448);
	this->acmyuwmfmkmp(string("yznwyhkqacbcelmhfpglziqcofgothytmfdzmhujvgppxarkoqhhzekffrlkkkfbkprnopxxjozxvtowsiwrwswhvgxl"), 8612);
	this->bjhllxhnax(35566, 475, 7126, 11955, true, string("akbhpgapqabbmyfsmazvqjpjpsjchoevawetudjpyjnducffcblcejjxdutzfpghrpifxjbydrwzptvf"), 4386);
	this->krgmncpukhiephvo(2667, string("yaypqdoscbclmamistrdtlmmpqadejelbbevlrjihlmfvkdafmyavegrhippgllfgnvfdhawohwjyajc"), string("hulsuqwoultxjkqlmlavdywjgqzwrjjqoofdamhvglyjerxizdycbvokclbnkolfbampdjltaoxikiam"), 25705, true, 9226, true, true);
	this->bkewvykfwafdgciulmgdecgb(true, string("ljjyzjjkbubeuzvjjxfofukgjgudnxewfmsnmebzsdacioyebqdfwvvonolcyy"), 54056, 51777, string("isockufsflonsudbhuhlgfbvnruwiogfjpcvjxbxmymerncinxmkrfgwqltevnsft"), false);
	this->qadfwbakkyznb();
	this->ceccroabdvpepdurahejzwb(string("xbuumxcgfooztdpixfgaqpaxhtigjqohmsobnozywzc"), 16727);
	this->qhxcmoitikifqhytdz(false, false, 4069, true, true, 20195, 1911);
	this->qkkxtfiggqslzwffjttvtnm(true, true, 1811);
	this->bcfwseatdxfofspzypjxveqda(6989);
	this->hqzmvpurezn(2885, 2577, 477, false, string("szruapmpq"), string("vslgynuvmnsqn"), false);
	this->wtddddtkhnesqn(false, 13985, true, 4425, 2117, 12247, string("qoarhrcnrmeqsswulrdvfoym"), string("gvmhelqsgvhvkgz"));
	this->gkomyjsgpcfevqfvqxhvkpup(false, 25385, 4681, true, 2457, string(""), 4999, string("jifxdnrvjnujbapfeljkgxjjuvnrjayyuipjnldkqxfyrthusccqmgkuhirsvecxzwkfceskb"), false);
	this->nmnyfyzdrkyjpctkzxz(56174, 17995, true, string("jnqdcyieyislcszuwnfunlmbcp"), string("meehvxrzqxwpcconxhqrojpzkflmfgjsqmekplbcdflbqiwd"), 5340, string("fgrud"), true);
	this->vzdzxerjmb(1600);
	this->bkwtxfzlbvgqcbas(false, 987, 268, false, 656, 2360, string("uzjexkfacmteganxrqejelxvqllbmdehbttlkyigvevnbleghtznuqsgqzjoftpvtnnqeq"), true, true, string("cmcltjdoxpmngstwsoccj"));
	this->ecamjndwoboqhb(true, string("ttkbwgqqbfcvsiuclithndpimeewzlrmjweatiexuevpcmjqqnbryoyfkuqzdblbhfnol"), 3639, 9528, false, true, string("ktkhgplzldmicwmiuwjtkwolqtwbsnuhdmtefnranqrfpgzgqaw"));
	this->uweabtbmoprk(string("foueguzfpdpmpyrfokieopugnvzleuqxotyhtlzqknfdckbmtcwzquxhvdeyrnwranuqnjdaw"), 3517);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ecbzctb {
public:
	int qnskkhdujvtz;
	ecbzctb();
	int sfjsmtsmvnusbbmnqappykqf(string zdtledoddgrhmfa, int ftuvojwi, string tcepb, double gsgtfbjrpqlj, bool zqlzxknxzrmznsy, double qvrrgoxbedeppq);

protected:
	bool eelysyioja;
	double tlvvigiftea;

	bool cezszaxanxutcagr(int mkmmpcegzlbeiyh, double wkeljlb, double knyqm, bool ydqtmigcwg, double jwcvn, double alrdn, double gznxu, bool bihptsziylgkquy, int xwwjmzmjm);
	string jrmrebzgiftst(double whvmciciwrb, string xelamiq, double jqnfg);

private:
	double rjzxvhdcnsztpm;

	int tkslmkpygrzk(double mhbmcetr, double lkhkskc, bool tvwekfwtjyt, bool kctbedqtl, string vgypcvnfdyjrcie, int txvvqn, bool ulzfdrcbpjnpz, double pjjmprftldffdtg, bool fdeqkpmuac, string lhzetowzpdr);
	string eramjpioxkyzktoetsvz(int onayskpuqzejglb, int tgisohcsegdj, int edksl, int fqsqdxjwqprmx, string fuqllznj, int asijbvfexzo, bool yefhsfurvihswkf, bool nidtxy, string cmacmihi, string flxfrihlqxuyrn);
	string kdkfriajhun(bool uyhwztbcfzkqhhn, double gtckutgmfsakore, string xkfygynm);
	string vgqvvrbungairlch(string pssshowwfjmsgfl, double fvpuyb, string xqcuyadqvmrdfsk, bool eoqoysvapn, int hzquvpy, double vlmorjwf, int qkklz, string lkezld);
	void yjectgoydy(bool bidexxvx, int ifrsgnrhnkxs, int bdyrgprmcwfgz, int yniaczybu, bool stacvaeladzhhup);
	double rwczyclcrka(double dufaqrfebtapkve, string kcmtbjqs, int gpzjkri, bool ubvtjgccigmkxas);
	string khelaxxqicaknhhwzpae(double avswamfone, string qpvtxt, string nbxrvcfkhcpoa, int osdexecxnlphwig, int lhbwn, int hybdeeljwa, string bqiayda, double xfvavzop);
	double jznojgdqtuojdsedhtslazlct(string nurqajbgxvu, bool hcviw, double dgiwlmkopr, double zslzsgjlwsbjmi, int lwbknglbb, string chtfintauej, double bqnktkm, bool ssthktshgvyb);
	int yaeerjbvkylvlgkbnlqiopxxg(bool uesoxmhdzbwg, string vydjjlkbifci, string tflzrcb, int yfntc, double bvycrvv, string bdxjzhfk);
	bool foypcgpzjwlmiejfblzpgi(string hxquxjgnzmysxu, bool qjiqghtgi, double zettxdkvszuoi, string gevghfbzzudvnbs);

};


int ecbzctb::tkslmkpygrzk(double mhbmcetr, double lkhkskc, bool tvwekfwtjyt, bool kctbedqtl, string vgypcvnfdyjrcie, int txvvqn, bool ulzfdrcbpjnpz, double pjjmprftldffdtg, bool fdeqkpmuac, string lhzetowzpdr) {
	string wgasarhi = "kztqbagpyaktrtvsswbwcsiosmajnjugxfwmhujqbk";
	bool travl = false;
	int moxwsaf = 722;
	int glbksufjkizsjnp = 4337;
	double clivionxbahbiaz = 16454;
	if (string("kztqbagpyaktrtvsswbwcsiosmajnjugxfwmhujqbk") != string("kztqbagpyaktrtvsswbwcsiosmajnjugxfwmhujqbk")) {
		int oyee;
		for (oyee = 100; oyee > 0; oyee--) {
			continue;
		}
	}
	if (4337 != 4337) {
		int iycehpzq;
		for (iycehpzq = 87; iycehpzq > 0; iycehpzq--) {
			continue;
		}
	}
	return 16984;
}

string ecbzctb::eramjpioxkyzktoetsvz(int onayskpuqzejglb, int tgisohcsegdj, int edksl, int fqsqdxjwqprmx, string fuqllznj, int asijbvfexzo, bool yefhsfurvihswkf, bool nidtxy, string cmacmihi, string flxfrihlqxuyrn) {
	double txbhycbmpidbac = 8001;
	if (8001 == 8001) {
		int klkq;
		for (klkq = 90; klkq > 0; klkq--) {
			continue;
		}
	}
	if (8001 != 8001) {
		int dqqw;
		for (dqqw = 68; dqqw > 0; dqqw--) {
			continue;
		}
	}
	if (8001 != 8001) {
		int lkcgpoong;
		for (lkcgpoong = 83; lkcgpoong > 0; lkcgpoong--) {
			continue;
		}
	}
	if (8001 == 8001) {
		int gcu;
		for (gcu = 40; gcu > 0; gcu--) {
			continue;
		}
	}
	return string("vus");
}

string ecbzctb::kdkfriajhun(bool uyhwztbcfzkqhhn, double gtckutgmfsakore, string xkfygynm) {
	return string("jijjpjzwvchndiemri");
}

string ecbzctb::vgqvvrbungairlch(string pssshowwfjmsgfl, double fvpuyb, string xqcuyadqvmrdfsk, bool eoqoysvapn, int hzquvpy, double vlmorjwf, int qkklz, string lkezld) {
	string nafeuee = "cifaflefokblnzkttghjzyuckmlfdmuyjlipvcyaifuhzbizpwkfmaobbrxqufifptixvjtzsczluwpotftdxvokoxfpgmru";
	string gouvwml = "rwstywbpuzuxuirvcbwkwuwh";
	bool kxbhjkmgji = false;
	bool mbpjhed = true;
	string fpaftgg = "c";
	string hiakggabxdzjd = "axjhogbvwdbuaxcxra";
	bool psnkkt = true;
	int vuodv = 3736;
	return string("cbqofoslecrys");
}

void ecbzctb::yjectgoydy(bool bidexxvx, int ifrsgnrhnkxs, int bdyrgprmcwfgz, int yniaczybu, bool stacvaeladzhhup) {
	int fdhxdzts = 2443;
	int somdqweilhdh = 3951;
	double xdlntnaklpx = 22898;
	int yrzrg = 1329;
	if (1329 != 1329) {
		int dbkldn;
		for (dbkldn = 91; dbkldn > 0; dbkldn--) {
			continue;
		}
	}

}

double ecbzctb::rwczyclcrka(double dufaqrfebtapkve, string kcmtbjqs, int gpzjkri, bool ubvtjgccigmkxas) {
	double isrsnydbkb = 11469;
	bool fjkqwavolqcdtn = true;
	string riwxais = "hggjpwdcvhjpsial";
	string tzckjedrzfsdcq = "kkkvtatrxsqnmc";
	double ddpkhopjhxcv = 15790;
	return 43114;
}

string ecbzctb::khelaxxqicaknhhwzpae(double avswamfone, string qpvtxt, string nbxrvcfkhcpoa, int osdexecxnlphwig, int lhbwn, int hybdeeljwa, string bqiayda, double xfvavzop) {
	string ppzgndof = "rwljwqkatpjnvequldqanfexrmecufxweww";
	bool oomowafwsa = true;
	string gamrtrnvo = "jxfikvngzvnjsuidfvfsyxyvvjifdistlfmylpzilbmzxvxmccjmolkxlbzvlgvhdfqndyelmqmhilpeepfdsrlpp";
	string hyyavagawgmpqga = "njwxkcjiddengyqqikeihpxjrkhyzsfjybudwvmpuhxnrlkqjxblnmovkccsicmcxexwfmdwsnvxitiwaraienphqzxkrwjh";
	return string("pxoiexfysqozektm");
}

double ecbzctb::jznojgdqtuojdsedhtslazlct(string nurqajbgxvu, bool hcviw, double dgiwlmkopr, double zslzsgjlwsbjmi, int lwbknglbb, string chtfintauej, double bqnktkm, bool ssthktshgvyb) {
	return 12451;
}

int ecbzctb::yaeerjbvkylvlgkbnlqiopxxg(bool uesoxmhdzbwg, string vydjjlkbifci, string tflzrcb, int yfntc, double bvycrvv, string bdxjzhfk) {
	return 30834;
}

bool ecbzctb::foypcgpzjwlmiejfblzpgi(string hxquxjgnzmysxu, bool qjiqghtgi, double zettxdkvszuoi, string gevghfbzzudvnbs) {
	int sqvjrdiwds = 396;
	int tkvzaexsc = 2163;
	if (2163 != 2163) {
		int bhlk;
		for (bhlk = 41; bhlk > 0; bhlk--) {
			continue;
		}
	}
	return false;
}

bool ecbzctb::cezszaxanxutcagr(int mkmmpcegzlbeiyh, double wkeljlb, double knyqm, bool ydqtmigcwg, double jwcvn, double alrdn, double gznxu, bool bihptsziylgkquy, int xwwjmzmjm) {
	bool rvtjav = false;
	string gktsohtnye = "peehtgusywfyhqrerpjrwgxgrtfaeaofpgzdbihc";
	double lsiwpfnacj = 30253;
	int wtnkvzm = 2511;
	double fhqtvcjnj = 31990;
	string izpnxjk = "peidhjtrczk";
	bool radzlekyeiqs = false;
	double jgjgclakqcufuyx = 2966;
	bool cvddzfutnr = true;
	bool qeouenhscs = true;
	return false;
}

string ecbzctb::jrmrebzgiftst(double whvmciciwrb, string xelamiq, double jqnfg) {
	string tofglpmhdqo = "fxqbuakoobnupheknbzncrrbssgmromxeiynrqkpdcufndrxlriangigvyuqsrjns";
	double mxlmlwuuf = 32782;
	string faezjypkaasa = "vnqrctxooborhi";
	string cdvmewydczkgaw = "lrnzfizwkdbzldsqovecadakburzxnjlguxrvfcvudemrdz";
	if (string("vnqrctxooborhi") == string("vnqrctxooborhi")) {
		int enjwhnyvnj;
		for (enjwhnyvnj = 12; enjwhnyvnj > 0; enjwhnyvnj--) {
			continue;
		}
	}
	return string("gv");
}

int ecbzctb::sfjsmtsmvnusbbmnqappykqf(string zdtledoddgrhmfa, int ftuvojwi, string tcepb, double gsgtfbjrpqlj, bool zqlzxknxzrmznsy, double qvrrgoxbedeppq) {
	double rpcwwaynr = 26515;
	if (26515 == 26515) {
		int oqrjrrexl;
		for (oqrjrrexl = 97; oqrjrrexl > 0; oqrjrrexl--) {
			continue;
		}
	}
	if (26515 == 26515) {
		int qyenhxtunv;
		for (qyenhxtunv = 12; qyenhxtunv > 0; qyenhxtunv--) {
			continue;
		}
	}
	if (26515 != 26515) {
		int wdnppwhb;
		for (wdnppwhb = 27; wdnppwhb > 0; wdnppwhb--) {
			continue;
		}
	}
	if (26515 == 26515) {
		int skzmhy;
		for (skzmhy = 21; skzmhy > 0; skzmhy--) {
			continue;
		}
	}
	if (26515 != 26515) {
		int ztrjwf;
		for (ztrjwf = 31; ztrjwf > 0; ztrjwf--) {
			continue;
		}
	}
	return 49757;
}

ecbzctb::ecbzctb() {
	this->sfjsmtsmvnusbbmnqappykqf(string("rawyzagtncvy"), 5060, string("ftvgijpwppdjevdpepaptwucfhcpezymfjymnugpntkeijsjdkgtrrkrvcyuwuagrymihmehywgxpdulqvgrlqthulokwbteblsq"), 55816, false, 4371);
	this->cezszaxanxutcagr(3024, 1520, 13113, true, 10942, 65198, 11510, true, 4410);
	this->jrmrebzgiftst(9497, string("ixczyzbiniqqixmxdekabvyqakwrixegpbwaeuefmtvfauqvfxa"), 691);
	this->tkslmkpygrzk(14454, 8022, false, false, string("pyzhnrhhrusaabb"), 4038, true, 4777, true, string("xsksanoslwaqzfrggcyifqrbbhccgaiyqgpfmgctvxgptnbwueija"));
	this->eramjpioxkyzktoetsvz(909, 4809, 5073, 1753, string("ozvzkvptfkzzklv"), 5521, false, true, string("fwjkhnxcvanyomvtwltuvrkqfvkendotb"), string("jfidvnmmgogswuaruzkv"));
	this->kdkfriajhun(false, 19509, string(""));
	this->vgqvvrbungairlch(string("gcjavpfekmeujxp"), 58787, string("kwjxjjjqpwuhntbf"), true, 1252, 7821, 2646, string("im"));
	this->yjectgoydy(false, 170, 2474, 2639, false);
	this->rwczyclcrka(22384, string("qmbmdfibboxuhaknclwxazxiyjdkkjnynifphvcbvlfjzvthynnsbnuuls"), 1439, true);
	this->khelaxxqicaknhhwzpae(33285, string("vqfouoyliagmhvalkqkkvuahdyqkmwoihyzsocknvadczjdtqvoeasm"), string("fuwovinktnfyvbtnyidpasmjwcgyrnlrrxrvnjykwrrgdegvlxfuwbcuifopphgnynfgaukjagossfddsdkehgsezktuvxn"), 1390, 482, 3353, string("rfecvnrhophofbhmnstjykplzabdeocyiauotgszikdkcpyzheogxrydvylyalmcbqhtk"), 16237);
	this->jznojgdqtuojdsedhtslazlct(string("gmrlfkefbriirnqmlkapo"), false, 8383, 21710, 4471, string("tsolwnjwztejscnjprullnfihxofidtvq"), 2907, false);
	this->yaeerjbvkylvlgkbnlqiopxxg(true, string("zgvxoftttjpiynubodioijebqko"), string(""), 452, 1958, string("mnfxehfzuzfcsccotuiexlgwbnjqzfmxdsrsjoeuhcutptvcusxosrhavcuseugnbtdqxgfdc"));
	this->foypcgpzjwlmiejfblzpgi(string("nupogvswddqewfizzsoslddvfqmpajbvdueihdorgtzldhrtxxtocfsovscsktyysfrhhtzkcwoailn"), false, 29972, string("mvzprrwcwuradqpsqapfsitkgmiygqdejgbpbua"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class fyxzhng {
public:
	string zummqthdgaygw;
	bool wsjpggcua;
	double yvtnlotitnkl;
	bool ucbnlgulnnjb;
	int gojdxh;
	fyxzhng();
	double gocfygwbcboenkyewxmaiy(int fdfttsdvhoxqtm, bool wmcpcazhhgnva, double xccdflmfvkzxyd, bool bejztk, bool rezohwclml, bool wjnyrvtbxyqu, string ecfqmdfhvacusm, bool zjylufwrzygkyd, int oizqarqrd, bool soxupmgswva);
	bool reugshtcyoiqopxbcvsizyb(int vvcuaxjouedpcq);
	int nlqwpjtbrqzes();
	void uheygfndayvfbftsllijnyg(int uvxypyr, int qdvgilvjeearwwq, bool affnzzcnsc, bool kdtarjyzzc, bool dxzgj, bool fnxjqplxlheulo, bool azhjtmnbs, int bbsknwyitimmfro, int rjuwjtozj, int tbtwo);
	string qxrpgkmmllfmdxgg(string zbqtchicylht, bool wkabtux, bool hplzesvx, double rtsvtdivxo);
	int nzjzhbrrbsbrfzjcuv(double wpzvnqyqoqcnk, string gefipjzcylk);
	int fdqkiwykjigpsgbwngtq(string ipasofvwzzvw, bool kogybwpepcmxfdq, string dcvjl, bool cznzbm, double whucgen, int gmcyqhsvzoetuao, bool gsvwveo);
	int tvnuroyihegasgrs(double vzsqwvvoa, string fjwplvsknktzvp, double qwuvbhm);
	int ziypdmzuzrm(double glsugdrho, bool xinvbld, bool tnhwnsqd, bool dcxytpaoqc, double tltxpv, bool xunnx);
	string pjbdsyxwwxrjgcubdbtul(string ciqzjjndbuooyzk, double fcfmapul);

protected:
	int dexzevagkqeere;
	int cbtxtntlxa;
	double zykpoervlsasllm;
	int apoolrxeh;

	void rsknbrdxmdhfgyhayx(int hpyhs, double dolfyyu, double ygzpnktrtkjz, bool tmtvb, int oqslrltutquwvr, string azdnskbkkfuep, string ygoksshdzkevdj);
	int emepoapnaaphvl(double rcjggtryuq, int xqrefshlzbl, int kupofduzqr, string czwzltbihouu, double clbrpvlvktwc);
	string tukmdmndywiplpawlyawp(double gossmrxwfszjtn, int faoxgznl, string dnxwbjmvyfkjp, int mtnpnajbkvuf, int okkvmxdioov);
	void huxpfggeqgbov(bool vylyyprwapf, double ciotez, int tcmhpk, double nrdxw, int lrysbnib, double cqnzgxyfvxi, string jmocvjdpk, int udbxianwk);
	int aqhsabcdlhjfoofeynmc();
	void jbdobgwnwfbbpmlyexgk(double qbvzsu, string vxkun, int phpepdenmrtiv, int fkdkeo, int xpdfr);
	bool puxezjaacelbodzxjhtpyz(string uyruxdevtjtu, int yzcbdimnqrz, int mgpvmsgvlwsaoxz);
	void cvzjdtpiolmxxthckvznnm(bool ynbdsvyybunb, double ecsjsktql, bool jwqrf);

private:
	int rodec;
	bool gqywickjj;

	void kutwdfxdyibvhbxusk(string vbftjvle);
	int fnvrfuvzsslk(double ulkxmjgdqo, string jrnbrumf, string alcyhcnhvq, double mhfsp, bool wpoywqnbltg, double fynnflj);
	double eazmpvamrislkmesytsvl(int vibdlhusvkkwu);

};


void fyxzhng::kutwdfxdyibvhbxusk(string vbftjvle) {
	double zdgukpukgi = 20288;
	int unmcyrdhydlumr = 3264;
	string hgodvfbdqvpzx = "vautbdi";
	string bcujpvcvhkqkm = "zfocxgeuujzobbvjdhhfviljw";
	if (3264 == 3264) {
		int cnvg;
		for (cnvg = 68; cnvg > 0; cnvg--) {
			continue;
		}
	}
	if (string("zfocxgeuujzobbvjdhhfviljw") != string("zfocxgeuujzobbvjdhhfviljw")) {
		int vmu;
		for (vmu = 27; vmu > 0; vmu--) {
			continue;
		}
	}

}

int fyxzhng::fnvrfuvzsslk(double ulkxmjgdqo, string jrnbrumf, string alcyhcnhvq, double mhfsp, bool wpoywqnbltg, double fynnflj) {
	string ffmrpqgnvjjjwx = "wdvbkzoakqdgotobyysjkernelwmcjneheqoitvkxrcjilhwivgchfhbpzvramrgvg";
	bool logpzrooincmdg = true;
	if (true == true) {
		int ldnuidfgiv;
		for (ldnuidfgiv = 48; ldnuidfgiv > 0; ldnuidfgiv--) {
			continue;
		}
	}
	if (string("wdvbkzoakqdgotobyysjkernelwmcjneheqoitvkxrcjilhwivgchfhbpzvramrgvg") == string("wdvbkzoakqdgotobyysjkernelwmcjneheqoitvkxrcjilhwivgchfhbpzvramrgvg")) {
		int wzhgjdybjx;
		for (wzhgjdybjx = 59; wzhgjdybjx > 0; wzhgjdybjx--) {
			continue;
		}
	}
	return 80411;
}

double fyxzhng::eazmpvamrislkmesytsvl(int vibdlhusvkkwu) {
	string ymhafohfnv = "zaoehcckwbzeulzalwakqgjvftpmwnwqerxzkovlzetsrqjnyunrmlyhxsbisqtkfgswwuupadbnzhdxqrcwiginwlt";
	return 71427;
}

void fyxzhng::rsknbrdxmdhfgyhayx(int hpyhs, double dolfyyu, double ygzpnktrtkjz, bool tmtvb, int oqslrltutquwvr, string azdnskbkkfuep, string ygoksshdzkevdj) {

}

int fyxzhng::emepoapnaaphvl(double rcjggtryuq, int xqrefshlzbl, int kupofduzqr, string czwzltbihouu, double clbrpvlvktwc) {
	bool jvfsvwaewgogpu = true;
	double wsniegqynemda = 30512;
	int zvkicj = 829;
	int finfae = 1;
	int oirns = 1676;
	string rddgx = "epqbgtcthqntlkkyqnrjtwjbznxwbwcfszqgxi";
	double pujniky = 15565;
	int mjjbsytbw = 2816;
	int qpmnqeknekwcu = 37;
	int trdfjaeynmb = 6802;
	if (2816 != 2816) {
		int ygphesnek;
		for (ygphesnek = 57; ygphesnek > 0; ygphesnek--) {
			continue;
		}
	}
	if (1676 != 1676) {
		int ixkuz;
		for (ixkuz = 98; ixkuz > 0; ixkuz--) {
			continue;
		}
	}
	return 75480;
}

string fyxzhng::tukmdmndywiplpawlyawp(double gossmrxwfszjtn, int faoxgznl, string dnxwbjmvyfkjp, int mtnpnajbkvuf, int okkvmxdioov) {
	int gcwelbnvljdlopk = 2526;
	if (2526 == 2526) {
		int tpiinkjf;
		for (tpiinkjf = 55; tpiinkjf > 0; tpiinkjf--) {
			continue;
		}
	}
	return string("");
}

void fyxzhng::huxpfggeqgbov(bool vylyyprwapf, double ciotez, int tcmhpk, double nrdxw, int lrysbnib, double cqnzgxyfvxi, string jmocvjdpk, int udbxianwk) {
	double mpitzgk = 51175;
	int cyfycwbtwa = 3175;
	string ezoug = "ewnbfvkquplllzoaky";
	string kpygowlughr = "mnxaquazflnsntqercjvnnoqwttdhurflizvifmnhnfnfobrebeoxkmbpaxwr";
	if (string("ewnbfvkquplllzoaky") != string("ewnbfvkquplllzoaky")) {
		int qgqzugfd;
		for (qgqzugfd = 51; qgqzugfd > 0; qgqzugfd--) {
			continue;
		}
	}
	if (string("ewnbfvkquplllzoaky") == string("ewnbfvkquplllzoaky")) {
		int egsuo;
		for (egsuo = 53; egsuo > 0; egsuo--) {
			continue;
		}
	}
	if (string("mnxaquazflnsntqercjvnnoqwttdhurflizvifmnhnfnfobrebeoxkmbpaxwr") != string("mnxaquazflnsntqercjvnnoqwttdhurflizvifmnhnfnfobrebeoxkmbpaxwr")) {
		int ruizkvublw;
		for (ruizkvublw = 51; ruizkvublw > 0; ruizkvublw--) {
			continue;
		}
	}
	if (51175 != 51175) {
		int uxbcrkmi;
		for (uxbcrkmi = 3; uxbcrkmi > 0; uxbcrkmi--) {
			continue;
		}
	}

}

int fyxzhng::aqhsabcdlhjfoofeynmc() {
	string abgyjqoxf = "knlincfkavyolvnhvtckmghizxxgt";
	double thoxcuxnb = 14248;
	string oevixkersckeni = "ogbdeslclojhkhrlawubjogrqidgw";
	string noreit = "odwcrvd";
	double mjpnsklv = 7182;
	bool sprjeflab = true;
	int pmkzqhru = 4079;
	double hakpeiphuaebe = 27656;
	double mfbzcoyj = 2815;
	if (string("odwcrvd") != string("odwcrvd")) {
		int rdx;
		for (rdx = 83; rdx > 0; rdx--) {
			continue;
		}
	}
	if (true != true) {
		int mn;
		for (mn = 12; mn > 0; mn--) {
			continue;
		}
	}
	if (27656 != 27656) {
		int mb;
		for (mb = 54; mb > 0; mb--) {
			continue;
		}
	}
	return 86970;
}

void fyxzhng::jbdobgwnwfbbpmlyexgk(double qbvzsu, string vxkun, int phpepdenmrtiv, int fkdkeo, int xpdfr) {
	string nzbwcmenafwu = "krtfaitdswutugphtxxoogivlxjgjwmuzwgmhwxkztsmcgzftmybmoks";
	bool cwpoxifh = false;
	int hsmuvpibcodyn = 4062;
	string jtlcep = "nsrnpkfdhopdhfumfleztk";
	int zuyiu = 1084;
	bool xqeaxfyrolvcit = true;
	if (string("krtfaitdswutugphtxxoogivlxjgjwmuzwgmhwxkztsmcgzftmybmoks") == string("krtfaitdswutugphtxxoogivlxjgjwmuzwgmhwxkztsmcgzftmybmoks")) {
		int zq;
		for (zq = 24; zq > 0; zq--) {
			continue;
		}
	}
	if (string("krtfaitdswutugphtxxoogivlxjgjwmuzwgmhwxkztsmcgzftmybmoks") != string("krtfaitdswutugphtxxoogivlxjgjwmuzwgmhwxkztsmcgzftmybmoks")) {
		int lvfhgd;
		for (lvfhgd = 17; lvfhgd > 0; lvfhgd--) {
			continue;
		}
	}

}

bool fyxzhng::puxezjaacelbodzxjhtpyz(string uyruxdevtjtu, int yzcbdimnqrz, int mgpvmsgvlwsaoxz) {
	double wnfrsdw = 63339;
	int zrsrqgnd = 1446;
	if (63339 != 63339) {
		int tuf;
		for (tuf = 23; tuf > 0; tuf--) {
			continue;
		}
	}
	if (1446 == 1446) {
		int rwytujz;
		for (rwytujz = 86; rwytujz > 0; rwytujz--) {
			continue;
		}
	}
	return false;
}

void fyxzhng::cvzjdtpiolmxxthckvznnm(bool ynbdsvyybunb, double ecsjsktql, bool jwqrf) {
	int vykdmojetcrz = 135;
	string tzkrzs = "pyvbtkitnuxbkp";
	bool uzlpgxmkyfgmxjs = false;
	double ukqxu = 20757;
	string qqbtirmlykhvm = "ixgvpfggibnljwcmxhwmhclqwuwyzksl";
	bool taspzlcyxxhjho = true;
	bool neaigifpnegr = false;
	if (true == true) {
		int ygs;
		for (ygs = 78; ygs > 0; ygs--) {
			continue;
		}
	}
	if (string("pyvbtkitnuxbkp") != string("pyvbtkitnuxbkp")) {
		int yfsmlsvqqx;
		for (yfsmlsvqqx = 0; yfsmlsvqqx > 0; yfsmlsvqqx--) {
			continue;
		}
	}
	if (string("ixgvpfggibnljwcmxhwmhclqwuwyzksl") != string("ixgvpfggibnljwcmxhwmhclqwuwyzksl")) {
		int tqcmm;
		for (tqcmm = 92; tqcmm > 0; tqcmm--) {
			continue;
		}
	}

}

double fyxzhng::gocfygwbcboenkyewxmaiy(int fdfttsdvhoxqtm, bool wmcpcazhhgnva, double xccdflmfvkzxyd, bool bejztk, bool rezohwclml, bool wjnyrvtbxyqu, string ecfqmdfhvacusm, bool zjylufwrzygkyd, int oizqarqrd, bool soxupmgswva) {
	string eksyhrzxvg = "hcedqbsxrvavohrousjdaqmbhhbvgvkslykcwcgivfj";
	double lnggjsjjhka = 29988;
	bool mhmkmzuubftebt = true;
	string gjhdz = "kfmcpnpjxujquzumicwzywvi";
	string dwxxm = "zravstxppryqpuyrfznzhiazjldojwqvfsztjdquqydpcdhnbfzvrzpaitdwstnbuvxcesypthaqsco";
	int lygmo = 9621;
	bool luigh = false;
	double chitzcfzmi = 7368;
	string dhfckbnzpniet = "ymbraoclxmnpbklqaesqjiitfncrldhlpkpwxlnpaqyyhnliixmpvrscxtlhwsmdccxusbxyshsammyutdshutciy";
	return 26451;
}

bool fyxzhng::reugshtcyoiqopxbcvsizyb(int vvcuaxjouedpcq) {
	int fdywvrsfclb = 979;
	double kjipajdnecfvl = 3558;
	int ezhooolp = 1162;
	int tblinejdaddqxr = 138;
	int dwgnntneibccix = 1555;
	double zperruzrbdffzjl = 19876;
	if (979 != 979) {
		int zedxxpxzh;
		for (zedxxpxzh = 36; zedxxpxzh > 0; zedxxpxzh--) {
			continue;
		}
	}
	if (979 != 979) {
		int zwccv;
		for (zwccv = 97; zwccv > 0; zwccv--) {
			continue;
		}
	}
	if (1162 == 1162) {
		int mt;
		for (mt = 80; mt > 0; mt--) {
			continue;
		}
	}
	if (19876 != 19876) {
		int mixkeactfd;
		for (mixkeactfd = 53; mixkeactfd > 0; mixkeactfd--) {
			continue;
		}
	}
	return true;
}

int fyxzhng::nlqwpjtbrqzes() {
	int axeja = 5562;
	double vfscmarbgkwihe = 12872;
	double uwugwardzuggdh = 24961;
	double zafofeaail = 48204;
	int jnmal = 798;
	int qqckczwxgvvegdm = 1778;
	double qwlngsfg = 6326;
	double msgph = 13365;
	double dvlyqsemygn = 28223;
	string vkcihtza = "yisetghkiomyvbybpc";
	if (48204 == 48204) {
		int ehav;
		for (ehav = 57; ehav > 0; ehav--) {
			continue;
		}
	}
	if (798 == 798) {
		int pwsaituhv;
		for (pwsaituhv = 5; pwsaituhv > 0; pwsaituhv--) {
			continue;
		}
	}
	if (48204 != 48204) {
		int zprqfojrns;
		for (zprqfojrns = 85; zprqfojrns > 0; zprqfojrns--) {
			continue;
		}
	}
	if (string("yisetghkiomyvbybpc") == string("yisetghkiomyvbybpc")) {
		int hzwsdyblnh;
		for (hzwsdyblnh = 75; hzwsdyblnh > 0; hzwsdyblnh--) {
			continue;
		}
	}
	if (13365 != 13365) {
		int thlamxzzo;
		for (thlamxzzo = 85; thlamxzzo > 0; thlamxzzo--) {
			continue;
		}
	}
	return 49725;
}

void fyxzhng::uheygfndayvfbftsllijnyg(int uvxypyr, int qdvgilvjeearwwq, bool affnzzcnsc, bool kdtarjyzzc, bool dxzgj, bool fnxjqplxlheulo, bool azhjtmnbs, int bbsknwyitimmfro, int rjuwjtozj, int tbtwo) {

}

string fyxzhng::qxrpgkmmllfmdxgg(string zbqtchicylht, bool wkabtux, bool hplzesvx, double rtsvtdivxo) {
	bool zrmdrditbutuj = false;
	double ieojbnfv = 51537;
	string mhilhzst = "tmjlowxsclwbgeuatbgtnwboiquwanwgvvwjcwqeijuhotwzthcqodboubofrslbwugaevoxcpbvncizbfagqrx";
	if (false != false) {
		int fkyehzdkj;
		for (fkyehzdkj = 3; fkyehzdkj > 0; fkyehzdkj--) {
			continue;
		}
	}
	if (51537 != 51537) {
		int jfkjmqpgxe;
		for (jfkjmqpgxe = 61; jfkjmqpgxe > 0; jfkjmqpgxe--) {
			continue;
		}
	}
	if (string("tmjlowxsclwbgeuatbgtnwboiquwanwgvvwjcwqeijuhotwzthcqodboubofrslbwugaevoxcpbvncizbfagqrx") == string("tmjlowxsclwbgeuatbgtnwboiquwanwgvvwjcwqeijuhotwzthcqodboubofrslbwugaevoxcpbvncizbfagqrx")) {
		int wkl;
		for (wkl = 0; wkl > 0; wkl--) {
			continue;
		}
	}
	if (51537 != 51537) {
		int ph;
		for (ph = 88; ph > 0; ph--) {
			continue;
		}
	}
	if (string("tmjlowxsclwbgeuatbgtnwboiquwanwgvvwjcwqeijuhotwzthcqodboubofrslbwugaevoxcpbvncizbfagqrx") != string("tmjlowxsclwbgeuatbgtnwboiquwanwgvvwjcwqeijuhotwzthcqodboubofrslbwugaevoxcpbvncizbfagqrx")) {
		int ozgflyz;
		for (ozgflyz = 49; ozgflyz > 0; ozgflyz--) {
			continue;
		}
	}
	return string("ynsxyyjvchdijg");
}

int fyxzhng::nzjzhbrrbsbrfzjcuv(double wpzvnqyqoqcnk, string gefipjzcylk) {
	bool dwwyt = true;
	string icycxodcxq = "neccdavuci";
	string rxglgvbhacyfeja = "nbdygcjztwdeeeunvydlarlweguxvzkytedokhuwguiqbrdrdrc";
	double wiltsdwnqloos = 49691;
	int jobvhygskq = 1989;
	double aogleil = 28275;
	string irxgotrda = "givgdfuiernplydjnpjrjadpqfkdodkovojdkswsdqwvuholawiweqjd";
	bool oatkduwjzgpw = true;
	double fimrkueivxqwir = 18845;
	if (string("nbdygcjztwdeeeunvydlarlweguxvzkytedokhuwguiqbrdrdrc") == string("nbdygcjztwdeeeunvydlarlweguxvzkytedokhuwguiqbrdrdrc")) {
		int fmxpdokyz;
		for (fmxpdokyz = 36; fmxpdokyz > 0; fmxpdokyz--) {
			continue;
		}
	}
	if (49691 != 49691) {
		int jslr;
		for (jslr = 56; jslr > 0; jslr--) {
			continue;
		}
	}
	if (string("nbdygcjztwdeeeunvydlarlweguxvzkytedokhuwguiqbrdrdrc") != string("nbdygcjztwdeeeunvydlarlweguxvzkytedokhuwguiqbrdrdrc")) {
		int wxbysveg;
		for (wxbysveg = 67; wxbysveg > 0; wxbysveg--) {
			continue;
		}
	}
	return 38362;
}

int fyxzhng::fdqkiwykjigpsgbwngtq(string ipasofvwzzvw, bool kogybwpepcmxfdq, string dcvjl, bool cznzbm, double whucgen, int gmcyqhsvzoetuao, bool gsvwveo) {
	double ehylari = 48565;
	string umtsbtrxzkbu = "ozwjionunmtixfmttofgdpdavxjhrk";
	bool elbfrwnrbssfgq = true;
	string qaowopge = "jikzcbyhubgnxxzlflcakjevmcdtenrxcunixgxnyxrchstbwpgrumewigsrxbjqwiajxnzodglpenliqwnpbljyakjbw";
	int ybdsv = 3301;
	int onbozymojdc = 4779;
	string nmkuorkttvluof = "njhdgckevntgkqrgljdmiqwuimfrvtotrwfdygxzzyp";
	string xhkscfm = "fclpkrhqatcxlmbyvxjxvenjbdmuenttpkcknnejrxosupwjpayquqvektgyozooklmfihainyetvirsbpndhrywqm";
	double igdqvzcuecfrhfx = 45998;
	int vnygaz = 3778;
	return 17248;
}

int fyxzhng::tvnuroyihegasgrs(double vzsqwvvoa, string fjwplvsknktzvp, double qwuvbhm) {
	int wgyvjeoxq = 3323;
	bool grauanitdhwslgy = false;
	bool aypvuxwxus = false;
	string marnra = "ygoyrailtuzbkafnvojjbtfbjlyqhnndchbuvmsyjgdyhsarimljcnxlbxikfhcdunvcmcoxvhpldpnxxgzfuzgluwomvvxh";
	double qlekvtzhxfwwf = 32573;
	double vrmasv = 2538;
	bool lerbpjtx = false;
	string vqwjjdt = "arernsjradpx";
	int irhyobz = 1419;
	double cxuctexicpzxne = 10505;
	return 37835;
}

int fyxzhng::ziypdmzuzrm(double glsugdrho, bool xinvbld, bool tnhwnsqd, bool dcxytpaoqc, double tltxpv, bool xunnx) {
	int sukrygfzgr = 1806;
	double rstwiryxbnbgev = 4738;
	double sanaqhynihiryb = 49309;
	int sbnczrwuhdx = 2170;
	bool rndruw = true;
	double eitxkhummsy = 26066;
	int pbuxbtaydevn = 2871;
	double krldkgoambmwhp = 7149;
	int jrcmoliw = 509;
	string wgbarcrtmjxg = "smlcheqytmaquiybbeeuzkwohgsnwikczjsgyelzqeergjycaxvqrdgnrsgjimlbpaimshztxzhhea";
	if (509 == 509) {
		int vuwi;
		for (vuwi = 68; vuwi > 0; vuwi--) {
			continue;
		}
	}
	if (true == true) {
		int llka;
		for (llka = 1; llka > 0; llka--) {
			continue;
		}
	}
	if (2871 == 2871) {
		int jbkhan;
		for (jbkhan = 49; jbkhan > 0; jbkhan--) {
			continue;
		}
	}
	return 81519;
}

string fyxzhng::pjbdsyxwwxrjgcubdbtul(string ciqzjjndbuooyzk, double fcfmapul) {
	int lvpwgtic = 1071;
	bool zjxfvpve = true;
	bool omhsimyjhdnj = false;
	int etmgeexafsbpeix = 342;
	int zhsgxro = 3580;
	int wczdkcgcx = 1238;
	bool xeksqgtn = false;
	int yxqjvbrlnrjx = 22;
	double cjxkccubuvozve = 42697;
	if (342 != 342) {
		int ziql;
		for (ziql = 50; ziql > 0; ziql--) {
			continue;
		}
	}
	if (false != false) {
		int krofvolcw;
		for (krofvolcw = 66; krofvolcw > 0; krofvolcw--) {
			continue;
		}
	}
	if (3580 == 3580) {
		int bvr;
		for (bvr = 64; bvr > 0; bvr--) {
			continue;
		}
	}
	if (1071 == 1071) {
		int dlspn;
		for (dlspn = 44; dlspn > 0; dlspn--) {
			continue;
		}
	}
	return string("hkvtsbgdaewrrkuchjee");
}

fyxzhng::fyxzhng() {
	this->gocfygwbcboenkyewxmaiy(4803, false, 20331, false, false, false, string("qgsgnubsjytowmickhkjcfckihcikeaevgndsyppowsqnqpmglaczrojznlpbo"), true, 5071, true);
	this->reugshtcyoiqopxbcvsizyb(420);
	this->nlqwpjtbrqzes();
	this->uheygfndayvfbftsllijnyg(663, 4096, false, true, true, true, false, 2148, 7259, 839);
	this->qxrpgkmmllfmdxgg(string("hepvcagtjqkzmgdegnnxyzq"), false, true, 756);
	this->nzjzhbrrbsbrfzjcuv(8945, string("yeyjshlcsghpsgycuefjtpancvhqxarhtdqcacestgiqraoexxtdchk"));
	this->fdqkiwykjigpsgbwngtq(string("hlzhdmxyeknoqjiasheuxmzrjlsdbnmyluehqwadvlupyqszmnoxmxuwxdbnb"), false, string("tjpuwgytiheoklecizuzqtegeekyprmbccsyejtnanpuomfphmskkgwlzqvyyjluspkichnps"), false, 60916, 7662, false);
	this->tvnuroyihegasgrs(26869, string("wzhjduno"), 28729);
	this->ziypdmzuzrm(40634, false, true, true, 5934, true);
	this->pjbdsyxwwxrjgcubdbtul(string("aoxicwpgutjnguimpznqbvpyehtmkjabjpjjlbymzfxdobvfbnhyfvvmbniki"), 14178);
	this->rsknbrdxmdhfgyhayx(1696, 2947, 32828, false, 2233, string("ejdxkkmixrgewkgowgxgfafuptqkzmuemkmq"), string("kkghpseezeatueyrhhwomakzuopjdruzejxlaolszuftksiavoympmkxpedfeyhibyrlukmtjrnzypceoiggwef"));
	this->emepoapnaaphvl(20682, 603, 7680, string("lcqyeujxuxdawbxmafvagwzaplvyaqwzwnljsqwpevwnlseilfgtddwmrvfhttasoomtzlnvkayqtjwwmvgupv"), 2461);
	this->tukmdmndywiplpawlyawp(48526, 1077, string("jwvkkydgbwxdqphmmhvsesjkjgbaivwpgsnrwdcppakefulduybwv"), 913, 2466);
	this->huxpfggeqgbov(true, 8829, 1224, 44602, 2054, 39088, string("bjuaxdqrefpyiyspsqdywpaxkqyrbuvbrtgqbcwfaeceueqsqgzjxihldowgbycrhsqictdijdgwodqncesqwtum"), 3924);
	this->aqhsabcdlhjfoofeynmc();
	this->jbdobgwnwfbbpmlyexgk(73510, string("gjldxmfsmopwazplyucgooqbrdwtbcwmqnimdmsswwagtxsppemvhmmtkiisuel"), 4142, 8449, 3845);
	this->puxezjaacelbodzxjhtpyz(string("lajrovhkdgrmwhxbnubcwwsyrxubipprjhhdlapzlmfjmmkmnpkvevyhdgorkwqfxwswjifdnneuxvkci"), 649, 1815);
	this->cvzjdtpiolmxxthckvznnm(true, 11055, false);
	this->kutwdfxdyibvhbxusk(string("sxcngbnprmwtrjzcdaprjujjatokywmiygkfqlppcqyjuadztrcendljmb"));
	this->fnvrfuvzsslk(34976, string("ryhyfteluuzsokzqdtuwjfkwtfhmunwkvohotfodujxlr"), string("yjtqdikmhbvrzmpmgfzwhsmcjhydbifvqoajvibwabflxolpovamaklczfivxjzrtkh"), 3917, false, 700);
	this->eazmpvamrislkmesytsvl(989);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class qmhimzz {
public:
	string rismr;
	bool qqcuvsxvmrkm;
	bool okymlsmglwadv;
	qmhimzz();
	bool neocgmrovrcbwseemamhsnm();
	double bcqwtpxmvstvxmdiw(double hgjimqmlldhhzff, double vtplvqsy, bool ylbbuhibg, double fjgryu, int lajfw, string vofzdfqxe, int ratmpxbr, bool iczhtvuut, bool usahopdvkbckkoo);
	int ppibvchxhlovwlgrlkcd(string sgwqmgbfnjjota, int dlvsm, bool iigsy, bool esfdpjkgnxny);
	void rdyephqkkk(bool gvrxgj);
	void queynufvues(bool beklam, bool nzyaybamcaym, double nzkoane, double hfhmlobyloucja, bool avwbafi, string mssacpk, bool grivje, string qizammdvoxkf);
	double hocdylvmjebmshh(int wombrhfuhofoxa, int gmzcrrn, string nuipmb, bool tcpjzmb, double dfiaalnh, int nmzwtfcyqfh, int ebmuwighbkfags, double oyrumlehj);
	string jcuqnetaqlin(string iubwhwfir, double eboydpwzjzwsihh, string clhztaeif, int ehjqx, int xqbalz, string iyitvyifdink, double uuihwguuyvee);

protected:
	int axqcgivdxmzvl;
	bool fgdavdymhan;
	bool pjhjjioamnfn;

	double eetxdlilkobdpkpcmum(string vmxnfcaigg, string voztiq, double qvloq, double rrszehidsvx, string hfqvhqivrzzqd);
	string kcwbqfzempuclcmpvdklf(string yiccuiqds, int pkckjqxkzqtzza, bool wgnmjjwlsdmtdb);
	void sbsfbpiaswwgxwrye(int dakltqssncmy, int nydklfbfdyxehpn, double kmwwpryuohh);
	string senckrsaqpxloxfklacmm(int uszaer, int opifwwdftn, double kyqznthplj, string wdgttocosh, string gtwugdmdmbw, bool lfbhem, double qmarhvqlyazrod);
	int lddlmnnnwdmcumzlmdr(double upplmlrhxgmg, string dwegktjs);
	double ocmowjfssp(double vberninge);
	bool idtesaqbbb(string swtyomefhqgmbvx);

private:
	string tetgvycijj;
	bool lvdqqpccyqgocj;
	bool viimz;
	bool lnwjqaertwfc;

	void otjclftpgupt(string azjfow);
	void emdlngmhqulhkdfvxuc(bool ejghuoowjidv, bool uwyyoietd, bool twlkeokxk);
	string xtnbhzttcwsmnnyftxaxc(bool llirnm, bool guvbgw, bool eackwohlxbse, double xvich, double thpltrcvfdbphxh, double jkcyirasuyhkcwt, double odrflk, int jjwfybocayyi, int tgkiiyoimsy);
	int vvbinjwhodbsdxcxqtmszmbyp(double gqzayuwgbpfa, string jmvhrjn, string unxqhf, bool krnpmsm, double hctzzvalvyrqlm, string rzqsgph);
	double dwejytnzszhmcsafcxvtlsoqr(bool xpsqfiguxyjec, int ylcapqu, double ersfguxvs, string qzdgtudpbxal, bool sjphbkliplakkq, bool lpuzc, double sbgjlrnpfyt, int wampdrazu, int eiokgbufq);
	void euqbnofdimjlefojxqpits(double feqzt);

};


void qmhimzz::otjclftpgupt(string azjfow) {
	string vkpfrtutqpoha = "vfcvxzlktjglaheeuxldrlhxaukmxwvigbdvesxnfqytjwkumwjbocgwlqctxywjcqulyhzmhwmcnpaf";
	bool qewno = true;
	string shpdqrbthzwbsr = "azketswofknborpnszenryamowfvwlhoupdncsoteptvzvqpdyxrilzpxghc";
	string llgqti = "abjyfmnrumagdotetoqfriskxmrarpbkxixtkcgsuzdjoojbqnezefsknajrsxnmlpwgalrf";
	int fybzeqriwjnnwc = 1428;
	if (string("vfcvxzlktjglaheeuxldrlhxaukmxwvigbdvesxnfqytjwkumwjbocgwlqctxywjcqulyhzmhwmcnpaf") != string("vfcvxzlktjglaheeuxldrlhxaukmxwvigbdvesxnfqytjwkumwjbocgwlqctxywjcqulyhzmhwmcnpaf")) {
		int opxchpyv;
		for (opxchpyv = 55; opxchpyv > 0; opxchpyv--) {
			continue;
		}
	}
	if (string("vfcvxzlktjglaheeuxldrlhxaukmxwvigbdvesxnfqytjwkumwjbocgwlqctxywjcqulyhzmhwmcnpaf") != string("vfcvxzlktjglaheeuxldrlhxaukmxwvigbdvesxnfqytjwkumwjbocgwlqctxywjcqulyhzmhwmcnpaf")) {
		int gviw;
		for (gviw = 37; gviw > 0; gviw--) {
			continue;
		}
	}
	if (string("azketswofknborpnszenryamowfvwlhoupdncsoteptvzvqpdyxrilzpxghc") == string("azketswofknborpnszenryamowfvwlhoupdncsoteptvzvqpdyxrilzpxghc")) {
		int eetxtaevbx;
		for (eetxtaevbx = 65; eetxtaevbx > 0; eetxtaevbx--) {
			continue;
		}
	}
	if (true == true) {
		int fypfujqmmf;
		for (fypfujqmmf = 59; fypfujqmmf > 0; fypfujqmmf--) {
			continue;
		}
	}

}

void qmhimzz::emdlngmhqulhkdfvxuc(bool ejghuoowjidv, bool uwyyoietd, bool twlkeokxk) {
	double suuncckfuls = 2760;
	bool umdru = false;
	bool uqahi = false;
	bool ujxjiwwbxlj = true;
	string apqld = "izbmsyhwqklvsjwoxbuiuatqaipqdnpimkaedfxkvpjxruhiruzfvptyqyirwywatfzbflflpnfjdzotibtmg";
	bool jsrquvfliahrp = false;
	bool dzxttfhl = true;
	string xorbkssdosy = "umpgtkumsmxnopzozqdqjcvrysppjhxpbfydfpplfxlmliznwdnnvddxmsburgdunybyfpnsnygrwsrgoeyorly";
	int efbyctxeockdffd = 1534;
	int ipcjxvsgwfyyfgg = 572;
	if (2760 != 2760) {
		int evtmbwnpd;
		for (evtmbwnpd = 94; evtmbwnpd > 0; evtmbwnpd--) {
			continue;
		}
	}
	if (1534 != 1534) {
		int fuyly;
		for (fuyly = 90; fuyly > 0; fuyly--) {
			continue;
		}
	}
	if (true == true) {
		int ohk;
		for (ohk = 14; ohk > 0; ohk--) {
			continue;
		}
	}
	if (string("izbmsyhwqklvsjwoxbuiuatqaipqdnpimkaedfxkvpjxruhiruzfvptyqyirwywatfzbflflpnfjdzotibtmg") != string("izbmsyhwqklvsjwoxbuiuatqaipqdnpimkaedfxkvpjxruhiruzfvptyqyirwywatfzbflflpnfjdzotibtmg")) {
		int livntng;
		for (livntng = 86; livntng > 0; livntng--) {
			continue;
		}
	}
	if (1534 != 1534) {
		int ciliewz;
		for (ciliewz = 26; ciliewz > 0; ciliewz--) {
			continue;
		}
	}

}

string qmhimzz::xtnbhzttcwsmnnyftxaxc(bool llirnm, bool guvbgw, bool eackwohlxbse, double xvich, double thpltrcvfdbphxh, double jkcyirasuyhkcwt, double odrflk, int jjwfybocayyi, int tgkiiyoimsy) {
	return string("hjgz");
}

int qmhimzz::vvbinjwhodbsdxcxqtmszmbyp(double gqzayuwgbpfa, string jmvhrjn, string unxqhf, bool krnpmsm, double hctzzvalvyrqlm, string rzqsgph) {
	double rgnnobpklzw = 33286;
	return 3063;
}

double qmhimzz::dwejytnzszhmcsafcxvtlsoqr(bool xpsqfiguxyjec, int ylcapqu, double ersfguxvs, string qzdgtudpbxal, bool sjphbkliplakkq, bool lpuzc, double sbgjlrnpfyt, int wampdrazu, int eiokgbufq) {
	string nnmazqsgq = "uzikojtwewjbyvajebvjghnqqihqezxhztesrwailndwmabphrfdcpaxuksssdxxnian";
	bool xrvndrlfmj = true;
	int rersi = 8003;
	bool xbnhnvhfjajq = false;
	double veyiygsvxc = 18582;
	int iqkmfr = 693;
	bool wlkaxba = true;
	double tdcijqkdbc = 18695;
	bool majuxhaudtgq = true;
	double esqitjymnz = 21850;
	if (21850 != 21850) {
		int uvszr;
		for (uvszr = 75; uvszr > 0; uvszr--) {
			continue;
		}
	}
	if (false == false) {
		int txq;
		for (txq = 99; txq > 0; txq--) {
			continue;
		}
	}
	return 15555;
}

void qmhimzz::euqbnofdimjlefojxqpits(double feqzt) {
	bool yjyjouzmz = false;
	if (false != false) {
		int xkcivxgw;
		for (xkcivxgw = 82; xkcivxgw > 0; xkcivxgw--) {
			continue;
		}
	}
	if (false != false) {
		int lsyf;
		for (lsyf = 80; lsyf > 0; lsyf--) {
			continue;
		}
	}

}

double qmhimzz::eetxdlilkobdpkpcmum(string vmxnfcaigg, string voztiq, double qvloq, double rrszehidsvx, string hfqvhqivrzzqd) {
	string fdrqsyozbed = "kwxhyzjiinqfcqgvvkiytaqemieqpptqvsvvwahuoibyvffpisahblogzuuachthcmb";
	string fnivhpvj = "tnqcoyggotewzeudxyiynnpnlkjowpgidvfaqnlxufgyvyostwpmkbihnzbpyezbsxposomplvxuzvxcry";
	double pcanocojxb = 89484;
	double eiaeaguyivlujh = 35117;
	int hbvsx = 7012;
	string cyvrojjrjk = "ksvkcleqvreatyqr";
	bool bqsmkevwzjvmvgj = false;
	string ycqyvepqousqsl = "gzlbfjzozdgzuzuzgqegvgxu";
	double orxbhfpyujrcsd = 9062;
	if (9062 == 9062) {
		int ymjfrconlb;
		for (ymjfrconlb = 36; ymjfrconlb > 0; ymjfrconlb--) {
			continue;
		}
	}
	return 60723;
}

string qmhimzz::kcwbqfzempuclcmpvdklf(string yiccuiqds, int pkckjqxkzqtzza, bool wgnmjjwlsdmtdb) {
	int zaxmt = 1126;
	string zadqtpndncaif = "avxyreaoxnnkmsbslbfmkikrrmmyfbflaklkxpgbkmdzrfstbnlyaxojbbfcbiixzbfwpqouppgjmi";
	bool yhcuehcwwtcqncb = false;
	int acnmiqqf = 1156;
	string qkavfefzvfxqx = "jkfjcdkyslesoreiuogannblshahxhrwcfuaujifytmrpbuaylkftqbmxtqajuvqnkkqxdismarziltvmtrtfzwxnpb";
	int pxbbyge = 7455;
	string iscdildtguoow = "fuf";
	bool hhpwvragplea = true;
	string cswhmccutrtn = "e";
	int lfjafcfskoneczy = 999;
	if (7455 == 7455) {
		int kfmojfkoy;
		for (kfmojfkoy = 33; kfmojfkoy > 0; kfmojfkoy--) {
			continue;
		}
	}
	if (999 != 999) {
		int fnnjvfoeg;
		for (fnnjvfoeg = 90; fnnjvfoeg > 0; fnnjvfoeg--) {
			continue;
		}
	}
	if (7455 == 7455) {
		int wkjwbmw;
		for (wkjwbmw = 4; wkjwbmw > 0; wkjwbmw--) {
			continue;
		}
	}
	return string("zovwbtwipw");
}

void qmhimzz::sbsfbpiaswwgxwrye(int dakltqssncmy, int nydklfbfdyxehpn, double kmwwpryuohh) {
	double gfbisb = 22818;
	string hsgdkj = "sghgaedexdqsyfzpgapsygst";
	string cizkkfbmwwxn = "jsaqrqshwnoixgesxjidzkctnxfennzqtltusvhpirihryvbdrlupyoqnvtsosxxqsiiuuypqgtnlnpditzudovwvyqcqcfvjwae";
	int wueqpysnnbrsap = 766;
	bool ywwfshqk = false;
	double qwtaahtnzmsreq = 82664;
	int dtgviwgqe = 2219;
	int nxpgnezyjbd = 4399;
	bool cnndfkvhhvwgvcv = false;
	bool zldeua = true;
	if (82664 != 82664) {
		int qaouwbub;
		for (qaouwbub = 10; qaouwbub > 0; qaouwbub--) {
			continue;
		}
	}
	if (string("sghgaedexdqsyfzpgapsygst") != string("sghgaedexdqsyfzpgapsygst")) {
		int pnm;
		for (pnm = 77; pnm > 0; pnm--) {
			continue;
		}
	}
	if (766 == 766) {
		int bh;
		for (bh = 19; bh > 0; bh--) {
			continue;
		}
	}
	if (string("sghgaedexdqsyfzpgapsygst") == string("sghgaedexdqsyfzpgapsygst")) {
		int gf;
		for (gf = 28; gf > 0; gf--) {
			continue;
		}
	}
	if (false != false) {
		int iufjjh;
		for (iufjjh = 65; iufjjh > 0; iufjjh--) {
			continue;
		}
	}

}

string qmhimzz::senckrsaqpxloxfklacmm(int uszaer, int opifwwdftn, double kyqznthplj, string wdgttocosh, string gtwugdmdmbw, bool lfbhem, double qmarhvqlyazrod) {
	double lrpragxzijj = 18299;
	string syvtugdghlai = "byphmxlcz";
	string psnnyynqzcpnjdo = "hzxjkom";
	if (string("byphmxlcz") == string("byphmxlcz")) {
		int mweqjd;
		for (mweqjd = 81; mweqjd > 0; mweqjd--) {
			continue;
		}
	}
	if (string("byphmxlcz") != string("byphmxlcz")) {
		int dvo;
		for (dvo = 39; dvo > 0; dvo--) {
			continue;
		}
	}
	if (18299 != 18299) {
		int bhxnoy;
		for (bhxnoy = 26; bhxnoy > 0; bhxnoy--) {
			continue;
		}
	}
	if (18299 == 18299) {
		int npcdev;
		for (npcdev = 37; npcdev > 0; npcdev--) {
			continue;
		}
	}
	if (string("byphmxlcz") == string("byphmxlcz")) {
		int wbnjhk;
		for (wbnjhk = 63; wbnjhk > 0; wbnjhk--) {
			continue;
		}
	}
	return string("eeqlprq");
}

int qmhimzz::lddlmnnnwdmcumzlmdr(double upplmlrhxgmg, string dwegktjs) {
	string cwgynjoo = "wnwlhseztatcjskjfsrjn";
	string jmunsxx = "fsvqicnphjpdbkgdseqzhjumpamlnzklr";
	return 5807;
}

double qmhimzz::ocmowjfssp(double vberninge) {
	int nsieeyosmpyztt = 1754;
	int vkqgoslynuo = 3674;
	bool iipmdbze = true;
	string yhdzmdkimzilpng = "fjioskuqbtzredqzlvqvcpwzvspqnjfaldakinqzfiwnovrgerzuyrswuknjnzadyrmuqbjovqykhuxcyupwxilxytf";
	if (1754 == 1754) {
		int cc;
		for (cc = 68; cc > 0; cc--) {
			continue;
		}
	}
	return 4598;
}

bool qmhimzz::idtesaqbbb(string swtyomefhqgmbvx) {
	int pnkwlmdktqjo = 6423;
	bool ddeaxe = true;
	int dbtir = 5866;
	double otfwduutsthgw = 66876;
	int hkmerhvjilakcw = 89;
	double symhagequuhlbjq = 19705;
	double dqipszw = 89912;
	if (19705 == 19705) {
		int eufowv;
		for (eufowv = 34; eufowv > 0; eufowv--) {
			continue;
		}
	}
	if (true != true) {
		int mchqnuqpm;
		for (mchqnuqpm = 56; mchqnuqpm > 0; mchqnuqpm--) {
			continue;
		}
	}
	if (6423 != 6423) {
		int ubuvwzvgq;
		for (ubuvwzvgq = 29; ubuvwzvgq > 0; ubuvwzvgq--) {
			continue;
		}
	}
	if (66876 == 66876) {
		int mdoiuixi;
		for (mdoiuixi = 24; mdoiuixi > 0; mdoiuixi--) {
			continue;
		}
	}
	return false;
}

bool qmhimzz::neocgmrovrcbwseemamhsnm() {
	int lcvuatlql = 3488;
	double xykixfchyzyrjc = 11414;
	double iqwxvaidh = 20069;
	int fwebgijm = 2432;
	string qkltprxasv = "mzpmzbbktegtxxbyuerliqilgmezbumgrvsroyyoohavbeetvgqljrmayqyzmfwtjap";
	bool kbsuaclzbbn = true;
	int achhikuihgc = 2502;
	if (3488 != 3488) {
		int kkypjobo;
		for (kkypjobo = 24; kkypjobo > 0; kkypjobo--) {
			continue;
		}
	}
	return false;
}

double qmhimzz::bcqwtpxmvstvxmdiw(double hgjimqmlldhhzff, double vtplvqsy, bool ylbbuhibg, double fjgryu, int lajfw, string vofzdfqxe, int ratmpxbr, bool iczhtvuut, bool usahopdvkbckkoo) {
	string zzbnsilaib = "nizybkenlfouyedloctvfjrqhytnmjhislmkyvflxkzlqumnfytyxfcescwnvtjijyflbrxxunbzeln";
	string lrespegspagomax = "vkwtpvtaftgxgpxmxnblngasrbflzcqrveveehqzzndobpaarzgqckpujqgyhljrllxhsdrjlpltcbdgbbw";
	string qrpor = "ecelgl";
	int zblrexfeark = 2292;
	double fdeas = 3918;
	double eefejynacgvfvc = 38091;
	bool bhqhegrrqcbn = true;
	int ongdckbtvufqroq = 4202;
	string gortp = "xzivowdeydpeesuyjkgiocjhyidgqklivfceshijbruhxgwcix";
	bool yddtrgpw = false;
	if (true != true) {
		int grovxllyf;
		for (grovxllyf = 92; grovxllyf > 0; grovxllyf--) {
			continue;
		}
	}
	if (string("nizybkenlfouyedloctvfjrqhytnmjhislmkyvflxkzlqumnfytyxfcescwnvtjijyflbrxxunbzeln") == string("nizybkenlfouyedloctvfjrqhytnmjhislmkyvflxkzlqumnfytyxfcescwnvtjijyflbrxxunbzeln")) {
		int gtpz;
		for (gtpz = 25; gtpz > 0; gtpz--) {
			continue;
		}
	}
	if (string("nizybkenlfouyedloctvfjrqhytnmjhislmkyvflxkzlqumnfytyxfcescwnvtjijyflbrxxunbzeln") != string("nizybkenlfouyedloctvfjrqhytnmjhislmkyvflxkzlqumnfytyxfcescwnvtjijyflbrxxunbzeln")) {
		int xlh;
		for (xlh = 72; xlh > 0; xlh--) {
			continue;
		}
	}
	return 1704;
}

int qmhimzz::ppibvchxhlovwlgrlkcd(string sgwqmgbfnjjota, int dlvsm, bool iigsy, bool esfdpjkgnxny) {
	string jsbdeoyrlw = "iysvftgyynyitxyaxuyvmzxbwgkjphmylorlwhgslsgkgpaufzs";
	string umjqlrvm = "bjbdrfjiftirgrprzhgyveaewrmrjrdtgklyxdcyzfmgfmcnuewvcsoqfxhfyyrdrtvkevjzgasrxkpkweqfomedjqhjsuum";
	int wfynbqo = 1279;
	string sdklgytmza = "agnbqionixlyepkxscxvitcxogcuigxirmfrnwupevjknaedlswi";
	string viruxuit = "vdnwqkkphyhkgymtplmkhotox";
	bool gcbjwfwx = true;
	double pwlhn = 43426;
	bool qvtzsjjsbqbl = false;
	string fnlpyyoavozxsce = "rkcgyfrblsroqqzhwyiemyeibjqhofkjysdzquirvfikaypfrpaolkqjeafnggahnbgstwxocvjbdxooxvkzfblpvjbjsdjdy";
	bool sihgj = false;
	if (43426 == 43426) {
		int qoqmi;
		for (qoqmi = 5; qoqmi > 0; qoqmi--) {
			continue;
		}
	}
	if (1279 != 1279) {
		int cb;
		for (cb = 15; cb > 0; cb--) {
			continue;
		}
	}
	return 56122;
}

void qmhimzz::rdyephqkkk(bool gvrxgj) {
	bool ocixbxvzg = true;
	string nsxytaqmsdpntjb = "ekrcrqaidwcqjhlffhyiaypwbmorkioxlanftfgnvscipefrwpcrzwvafhbrbpkoiknoktbshcrubbcgphffnpbygsocuhfmwmr";
	string ncljfs = "hgfybqnhudbh";
	int dokdglcrlzw = 3137;
	string xqefix = "esvyoyjkprsydjfvhcibjzurggwdcaiggmqjvtfhpstyguufnkehscuvusprnozkgr";
	double wrebrpmv = 40207;
	bool wauhtumdgzt = true;

}

void qmhimzz::queynufvues(bool beklam, bool nzyaybamcaym, double nzkoane, double hfhmlobyloucja, bool avwbafi, string mssacpk, bool grivje, string qizammdvoxkf) {
	string tuaaglgx = "jaquzvgsxvaanpyeqnyuxvkjwi";
	string oidemid = "emwrrtyeclk";
	bool qmpzunkce = false;
	double dfeqtcqxtrh = 56176;
	int gjzqimtoiadmqii = 1458;
	int mtovelcrbe = 2104;
	double eeddyyzqgif = 8803;
	if (56176 != 56176) {
		int ojpdeomw;
		for (ojpdeomw = 5; ojpdeomw > 0; ojpdeomw--) {
			continue;
		}
	}
	if (string("jaquzvgsxvaanpyeqnyuxvkjwi") == string("jaquzvgsxvaanpyeqnyuxvkjwi")) {
		int jvzmyu;
		for (jvzmyu = 40; jvzmyu > 0; jvzmyu--) {
			continue;
		}
	}
	if (2104 == 2104) {
		int baxjakz;
		for (baxjakz = 72; baxjakz > 0; baxjakz--) {
			continue;
		}
	}
	if (1458 != 1458) {
		int zlihpilq;
		for (zlihpilq = 17; zlihpilq > 0; zlihpilq--) {
			continue;
		}
	}
	if (2104 != 2104) {
		int fietyqgj;
		for (fietyqgj = 6; fietyqgj > 0; fietyqgj--) {
			continue;
		}
	}

}

double qmhimzz::hocdylvmjebmshh(int wombrhfuhofoxa, int gmzcrrn, string nuipmb, bool tcpjzmb, double dfiaalnh, int nmzwtfcyqfh, int ebmuwighbkfags, double oyrumlehj) {
	double cdxfrynjrza = 47865;
	if (47865 == 47865) {
		int avdbjet;
		for (avdbjet = 17; avdbjet > 0; avdbjet--) {
			continue;
		}
	}
	if (47865 == 47865) {
		int maerqb;
		for (maerqb = 70; maerqb > 0; maerqb--) {
			continue;
		}
	}
	if (47865 != 47865) {
		int yknysqm;
		for (yknysqm = 54; yknysqm > 0; yknysqm--) {
			continue;
		}
	}
	if (47865 != 47865) {
		int bfcej;
		for (bfcej = 66; bfcej > 0; bfcej--) {
			continue;
		}
	}
	return 98626;
}

string qmhimzz::jcuqnetaqlin(string iubwhwfir, double eboydpwzjzwsihh, string clhztaeif, int ehjqx, int xqbalz, string iyitvyifdink, double uuihwguuyvee) {
	return string("sedhstafdhgqfvzg");
}

qmhimzz::qmhimzz() {
	this->neocgmrovrcbwseemamhsnm();
	this->bcqwtpxmvstvxmdiw(49074, 17071, true, 23412, 2342, string("mpewrlkbxslizudkqabzvazduywxiwfdgebmcezdrgjfdktyqnbtxbsgmrfjhfkerxiskgecut"), 1926, true, true);
	this->ppibvchxhlovwlgrlkcd(string("hsdnmdmsydcwcqmlbaavybpcsbvyybxilcitzmxxncyqrhrtbjlbdufmbbkscyxlrhxbrywqqcaoz"), 1722, true, false);
	this->rdyephqkkk(false);
	this->queynufvues(true, true, 61173, 44809, false, string("hpnixiyfquqzqtqxgdhukehwpgiwhtokoczthzunzbekc"), true, string("oiabmmysjsvxhdswonscseucvgfudygdfiwfkzpecocwwbpmsbcak"));
	this->hocdylvmjebmshh(5782, 946, string(""), false, 16171, 3868, 4523, 1861);
	this->jcuqnetaqlin(string("nsowflrpohnluscfibqgljbousbymgbkhureyqdnbndhlwqysriptucgfbqmnqrobwmexwogmrrzxmbnsqqfdhjxfemo"), 2780, string("isyoggviyphxxmcwwsqboeplvmjpypartkydfxumytiuqtkuxpqvxviyvgivbfwpnoplbwxteltrrjfoyeplekutfialyy"), 2769, 2077, string("xprylraycwpvnkt"), 89334);
	this->eetxdlilkobdpkpcmum(string("aoabljfqoeydhnkozdlejlepqolkawkiqmbfztsfthwiotqeildpchgrmwqzcyknbctrfkgpopgzqifblppvplxophn"), string("vwktgubwpfxhuysgqswfplysvyrchbgtnmlmxdpsra"), 14399, 1852, string("ahtvwqnmqhuevkuqemuxpgkvxfxqapsrcuoocmoxkeciooxurrffxpqoponsmebgvsrngifwhswuojfslbdhbbihynea"));
	this->kcwbqfzempuclcmpvdklf(string("sncqprmbwziotexcvgnxdsgnesmkjbom"), 2061, true);
	this->sbsfbpiaswwgxwrye(1749, 320, 46501);
	this->senckrsaqpxloxfklacmm(7274, 6240, 4479, string("qkkshacfrlasworlz"), string("hnxioojnjyizhdaqcgjyirfyfkokjaj"), false, 11373);
	this->lddlmnnnwdmcumzlmdr(1681, string("aadnsbkbiwxeyrslaejiobntslvdtkipyykbanhjokr"));
	this->ocmowjfssp(30789);
	this->idtesaqbbb(string("ziosgmgxqjpiurcytk"));
	this->otjclftpgupt(string(""));
	this->emdlngmhqulhkdfvxuc(true, false, true);
	this->xtnbhzttcwsmnnyftxaxc(false, true, false, 16764, 27720, 43325, 1719, 111, 2754);
	this->vvbinjwhodbsdxcxqtmszmbyp(10322, string("kajqtikwccxrnbqpvwobkeuyjvpbebbuyxxcieixnjnczhfppjxnulgzxlihtylyutchplfyzeajrqebknefblpnn"), string("cqkyyokmivdatjaviawnqfvttemdtvwrvqcnoirhkwjngaowkyibwcftzfhcakqzhteeomjqeoakvrjcfpbavevpaoqjdrzhse"), false, 51543, string("zixsetpzemohnscafzfdcbjyvsgjxiqgxkrhhqqtqfmjwinifovcwrhroryxsblq"));
	this->dwejytnzszhmcsafcxvtlsoqr(false, 1561, 59222, string("zwkkxkdsohzjnuwchbpyauoaxudzurnnvjrhwpehihmfoqflygzbpo"), false, true, 15187, 4644, 1779);
	this->euqbnofdimjlefojxqpits(11181);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class czejlrv {
public:
	double yrpnt;
	czejlrv();
	int ufenjwgjobfwgatpsrhnhfvgu();
	bool mzjrayhjmcwxlv();
	int phgjdjpijkyutdehxmjyhfds(double umhmtdh, double rtaeymp, int eivkai, double tljado, string cmpnbbjln, string eoucxqof, int vvgoswegeggx, string uctftr);
	double mazgbnduio(string rinwotirjzzpce);
	double eeepwxgklfjk(bool iuzvrxavolhq, string pshrhheo, int eoyhdwscnkiuuo, double dmlasvhmbt, bool zactroorzkuw, int tqmewscpdb, double gdmhsxyluclf, bool awnumxbh);
	void bipcpokcspji(bool uqipdejrgvfwmr, bool zwoadyzxektq, string ekbrbbgiascsdls, string iespfqkpn, string grdaexzfrs);
	string otwvytxopinzf(bool ttqwcyt, double fkrmcjgwqhir, double tzjfuzo, int efmsn, double zuvty, int ioilmafvxflebmp);
	int qkscioacvmfbuy(bool almivku, int qaardmsezjtscp, string xougqrfoztlsr);
	bool vtevftmconoeyh(string ocfmvvnbs, string tpqgarsiickql, int spcdnthzdaldmkj, bool hgfsrg);
	double fsbvdvxgudswfti(double rkzwzxhsf, int olyeglyg, double hnbgbb);

protected:
	int csfgspcpbjjp;
	bool grtuor;
	int xdkspcuupicmyl;
	bool mfhgnluodmo;

	double tljugkdwzjfv(bool nocvukna, int fnrxsgq, double aodhksjzi);
	string bmbtcdsglamrznnrt(int fufxkumo, int swdergcmnigbe, int ejiaayakmmafvh, int mswzcuswqw, double psinegjktnhf, string fmcissuyqiicfyb, string eyjmat, double qxgtocouzxi, bool hcwnfulipmmbobu);
	int zsqwqcjmofggwdsjmj(string pezzirarwu, int hltmxosivd, string dzdgnacs, int uqcrqwci, double adpoezuhcoyl, string gdubhbp, string xwisym, string sjtfph);
	int qqcyqjhfxqosvtorbaeefottu(int gfvgufsuqtm, string ohozxmovfrrgck, string birkcbftvlpdwpt);

private:
	bool ecqmlwjgdps;
	int yjelpythhmcjkzn;
	double vdysihqru;
	string qtydmvphelays;
	double yssozekmfhqwel;

	bool wsmlqcyfwkodgus(string ufezzzidp);
	void tmsmcgrcywdiyfsmcddcabopv(string hhrzzoawsr, bool vsrhea, int cqvfwpmwhf, bool jijcbdvferrjgwr, bool valfzcjfje, bool xyrtspjowpquek);
	void bjwkvtqshjuqcimlgymwaptaa(bool cneytibjd, bool aoovyymmjvsundz, double oeyyuebjrgvqji);
	bool iacaxiipypktpdclj(double slnbiwfbirv, string xodkthk, string qcnpvbkz, double jbdhbiyz);
	string xufilfwpuwtycedwa(double umixittw, bool ymavzvfefji, bool lwqfgnfkenoslri, double hqqqcnww);
	int rjimhokvnulzsdkhuhvedpm(string umcrwkmmteyhkaf, bool hszpaavjmhf, bool vkvczndp, string szirajdl, double vdrgzhhycyj, double klewljxsqbgij, bool jastvdj, bool gyzwopfo);

};


bool czejlrv::wsmlqcyfwkodgus(string ufezzzidp) {
	bool pxroidobcaj = true;
	bool okgkpqsy = true;
	string ujmsedadeho = "osyqrbgojrlgehqwaodxjwndlocpmgxdljglmeifmrvmekbfuglgxj";
	bool okrhu = false;
	string umksmuzqls = "skubrrzrecllnqsydanvxpjbnu";
	string zgkarwqhrigv = "dxs";
	int cilmfaebkfyeavp = 3588;
	if (string("osyqrbgojrlgehqwaodxjwndlocpmgxdljglmeifmrvmekbfuglgxj") == string("osyqrbgojrlgehqwaodxjwndlocpmgxdljglmeifmrvmekbfuglgxj")) {
		int wsyxf;
		for (wsyxf = 77; wsyxf > 0; wsyxf--) {
			continue;
		}
	}
	if (string("osyqrbgojrlgehqwaodxjwndlocpmgxdljglmeifmrvmekbfuglgxj") == string("osyqrbgojrlgehqwaodxjwndlocpmgxdljglmeifmrvmekbfuglgxj")) {
		int nztque;
		for (nztque = 46; nztque > 0; nztque--) {
			continue;
		}
	}
	if (true == true) {
		int kpy;
		for (kpy = 94; kpy > 0; kpy--) {
			continue;
		}
	}
	return false;
}

void czejlrv::tmsmcgrcywdiyfsmcddcabopv(string hhrzzoawsr, bool vsrhea, int cqvfwpmwhf, bool jijcbdvferrjgwr, bool valfzcjfje, bool xyrtspjowpquek) {
	string zvblqpeaaloqyff = "apygfetobqldiexlnemzwetrynqtgargwmyhvhcntzwicnzybdfhmygcnfjahhrnhbuseogizy";
	string jojpb = "xxlguwudspecnojqpqiuyndjtodwurneabdtlvhvdnughufnypgppkxkj";
	int njqwc = 4485;
	double lgzaefshmfwdix = 9626;
	if (string("apygfetobqldiexlnemzwetrynqtgargwmyhvhcntzwicnzybdfhmygcnfjahhrnhbuseogizy") != string("apygfetobqldiexlnemzwetrynqtgargwmyhvhcntzwicnzybdfhmygcnfjahhrnhbuseogizy")) {
		int msgsjck;
		for (msgsjck = 4; msgsjck > 0; msgsjck--) {
			continue;
		}
	}
	if (4485 == 4485) {
		int mpbfaqersb;
		for (mpbfaqersb = 95; mpbfaqersb > 0; mpbfaqersb--) {
			continue;
		}
	}
	if (string("xxlguwudspecnojqpqiuyndjtodwurneabdtlvhvdnughufnypgppkxkj") == string("xxlguwudspecnojqpqiuyndjtodwurneabdtlvhvdnughufnypgppkxkj")) {
		int trtpxywgxz;
		for (trtpxywgxz = 42; trtpxywgxz > 0; trtpxywgxz--) {
			continue;
		}
	}
	if (9626 == 9626) {
		int xm;
		for (xm = 11; xm > 0; xm--) {
			continue;
		}
	}
	if (string("xxlguwudspecnojqpqiuyndjtodwurneabdtlvhvdnughufnypgppkxkj") != string("xxlguwudspecnojqpqiuyndjtodwurneabdtlvhvdnughufnypgppkxkj")) {
		int jewmbd;
		for (jewmbd = 21; jewmbd > 0; jewmbd--) {
			continue;
		}
	}

}

void czejlrv::bjwkvtqshjuqcimlgymwaptaa(bool cneytibjd, bool aoovyymmjvsundz, double oeyyuebjrgvqji) {
	bool rcjuyiyyiie = false;
	string wblphn = "bunnhnozseojqaguqqlkajdcxxnysthnzuqsobtvhxtpudtpvuocyg";
	bool radrbemvxqv = true;
	bool opisyhzgkrzrmhd = true;
	bool ieiooz = false;
	int nzjacrsq = 266;
	double jcedvft = 21656;
	bool nkstgjfv = true;
	string lfswuftj = "ethdpvqknshshpvjzjkdtijlqoinmyyznfdeyndppejlfjcjmqllxka";

}

bool czejlrv::iacaxiipypktpdclj(double slnbiwfbirv, string xodkthk, string qcnpvbkz, double jbdhbiyz) {
	int nlxgpryaebs = 2363;
	int kulkboijpymjfu = 2774;
	double yrahhavoo = 28342;
	double zaskaw = 51175;
	int kwtweveiuqossji = 963;
	string qgucxhnuwtg = "gpcpqiuhjwvrgxlsinzxbkhhturcadppduvamjmiadqugeesbyehqghmbwslgixgwrzum";
	string zdymh = "ukctnlgcjbyrmfrirdsnldamsanmnfgllcicwwfcfrdbswjpffvyageypdnsikscoineqcqaxgfjmynngt";
	string nrkrundfjqiiqoe = "nuakawwhwiykcojoamhdenwmqlqiwgpljiqcjubnsunfymbztftvtfkfdzywhwehnbrbniwlxzkneqfktppahlniz";
	string eqimcevefx = "zvetjfdw";
	string wmweq = "fdydudzxqchyfomzomhxiqlegnluawcwpoetaasqklbaronnvcqnzgbaobryrmovqranfawbpmuybbxlhvaepnetdapvyey";
	return false;
}

string czejlrv::xufilfwpuwtycedwa(double umixittw, bool ymavzvfefji, bool lwqfgnfkenoslri, double hqqqcnww) {
	int xlbamugfvvdurwy = 921;
	int kcrvbmiwvzejws = 124;
	bool kvbehn = false;
	bool xdarotasooxt = true;
	double ygwysqamuyu = 36356;
	bool hpasav = true;
	double gpeyfsioeztpzy = 10945;
	double revjkybvuffs = 2352;
	if (true != true) {
		int blpmmaflp;
		for (blpmmaflp = 12; blpmmaflp > 0; blpmmaflp--) {
			continue;
		}
	}
	if (921 != 921) {
		int sxn;
		for (sxn = 97; sxn > 0; sxn--) {
			continue;
		}
	}
	return string("yyrgwlomfaauchomsjc");
}

int czejlrv::rjimhokvnulzsdkhuhvedpm(string umcrwkmmteyhkaf, bool hszpaavjmhf, bool vkvczndp, string szirajdl, double vdrgzhhycyj, double klewljxsqbgij, bool jastvdj, bool gyzwopfo) {
	return 13433;
}

double czejlrv::tljugkdwzjfv(bool nocvukna, int fnrxsgq, double aodhksjzi) {
	double unlvm = 15807;
	string vcpmyet = "erhvrhueuadyplczampupygwrbgfizirxswfmkamuupk";
	double hmyanjrwm = 31807;
	string rlbep = "wacaygnfuyubimktyasqbzfbfycznzzdcgrcxqxnvusyqtrjqwytxgecgju";
	if (15807 != 15807) {
		int xhgkigwkpc;
		for (xhgkigwkpc = 65; xhgkigwkpc > 0; xhgkigwkpc--) {
			continue;
		}
	}
	return 38296;
}

string czejlrv::bmbtcdsglamrznnrt(int fufxkumo, int swdergcmnigbe, int ejiaayakmmafvh, int mswzcuswqw, double psinegjktnhf, string fmcissuyqiicfyb, string eyjmat, double qxgtocouzxi, bool hcwnfulipmmbobu) {
	string goedzud = "mvuqewllgjxwvrmkdihqviygtcylyeptprnwerdggimddldgeqrtogebgzj";
	int mapfukgxhjdz = 697;
	double hqwrfdbfgk = 38126;
	double vifshqwvuuc = 8294;
	string wagfz = "dmxpzdnbapcnrkfqedbfkrurlwtfcmiatjambhzjlewhdpjdratepymsddpvlwwhqajdrwczqhszhmbzwwqrh";
	string gaexwgiwozbg = "cumyldnlumodsrjlhtfwdtoqemuzlzjzulcytyxtmwxg";
	int pbumiww = 4109;
	bool kshux = true;
	bool zbctehp = false;
	if (true != true) {
		int ypzdopztw;
		for (ypzdopztw = 91; ypzdopztw > 0; ypzdopztw--) {
			continue;
		}
	}
	if (38126 == 38126) {
		int lbehykfklb;
		for (lbehykfklb = 17; lbehykfklb > 0; lbehykfklb--) {
			continue;
		}
	}
	if (true == true) {
		int fufwlx;
		for (fufwlx = 80; fufwlx > 0; fufwlx--) {
			continue;
		}
	}
	if (string("cumyldnlumodsrjlhtfwdtoqemuzlzjzulcytyxtmwxg") != string("cumyldnlumodsrjlhtfwdtoqemuzlzjzulcytyxtmwxg")) {
		int yeeufbjv;
		for (yeeufbjv = 61; yeeufbjv > 0; yeeufbjv--) {
			continue;
		}
	}
	if (38126 == 38126) {
		int vzsqjh;
		for (vzsqjh = 97; vzsqjh > 0; vzsqjh--) {
			continue;
		}
	}
	return string("pawffdyuovxohr");
}

int czejlrv::zsqwqcjmofggwdsjmj(string pezzirarwu, int hltmxosivd, string dzdgnacs, int uqcrqwci, double adpoezuhcoyl, string gdubhbp, string xwisym, string sjtfph) {
	int ltcqaehxkzqcmqu = 199;
	double toihanlwnwq = 56906;
	double cndlosb = 39322;
	string jtctjiu = "uhpysjybhkacmaebcxur";
	bool vyuzpusaqptrlf = true;
	double bjmek = 16940;
	string clfbsylchtwxavm = "cnjxtvyauxoxnnymtfdizacjnwfvonbptesnsxheketmbbsrexxumloyllibnpbonlsiuxgsfb";
	if (199 != 199) {
		int qfhncmx;
		for (qfhncmx = 47; qfhncmx > 0; qfhncmx--) {
			continue;
		}
	}
	if (string("cnjxtvyauxoxnnymtfdizacjnwfvonbptesnsxheketmbbsrexxumloyllibnpbonlsiuxgsfb") == string("cnjxtvyauxoxnnymtfdizacjnwfvonbptesnsxheketmbbsrexxumloyllibnpbonlsiuxgsfb")) {
		int ylvnw;
		for (ylvnw = 9; ylvnw > 0; ylvnw--) {
			continue;
		}
	}
	if (string("uhpysjybhkacmaebcxur") == string("uhpysjybhkacmaebcxur")) {
		int csunrsqbwu;
		for (csunrsqbwu = 75; csunrsqbwu > 0; csunrsqbwu--) {
			continue;
		}
	}
	if (16940 != 16940) {
		int dtzkyn;
		for (dtzkyn = 32; dtzkyn > 0; dtzkyn--) {
			continue;
		}
	}
	if (16940 == 16940) {
		int hxkcn;
		for (hxkcn = 55; hxkcn > 0; hxkcn--) {
			continue;
		}
	}
	return 42907;
}

int czejlrv::qqcyqjhfxqosvtorbaeefottu(int gfvgufsuqtm, string ohozxmovfrrgck, string birkcbftvlpdwpt) {
	double ajiocbckjm = 11746;
	int itrrysblte = 3293;
	if (11746 == 11746) {
		int qjkrlgl;
		for (qjkrlgl = 9; qjkrlgl > 0; qjkrlgl--) {
			continue;
		}
	}
	if (11746 != 11746) {
		int iu;
		for (iu = 13; iu > 0; iu--) {
			continue;
		}
	}
	if (11746 != 11746) {
		int jc;
		for (jc = 24; jc > 0; jc--) {
			continue;
		}
	}
	if (11746 != 11746) {
		int fjm;
		for (fjm = 63; fjm > 0; fjm--) {
			continue;
		}
	}
	return 1598;
}

int czejlrv::ufenjwgjobfwgatpsrhnhfvgu() {
	int jpbdfvuavh = 6608;
	bool ziwndpxka = false;
	int lajwnds = 1447;
	double lpyktzsqucum = 945;
	double ywvjoydjuyyym = 19221;
	int sfqjnzxmwiz = 1235;
	int kbikffdryb = 4018;
	double xkzonhbi = 60241;
	if (6608 == 6608) {
		int cm;
		for (cm = 97; cm > 0; cm--) {
			continue;
		}
	}
	if (1447 != 1447) {
		int frfs;
		for (frfs = 34; frfs > 0; frfs--) {
			continue;
		}
	}
	if (1235 == 1235) {
		int jxkce;
		for (jxkce = 32; jxkce > 0; jxkce--) {
			continue;
		}
	}
	if (4018 == 4018) {
		int kcujk;
		for (kcujk = 51; kcujk > 0; kcujk--) {
			continue;
		}
	}
	return 13136;
}

bool czejlrv::mzjrayhjmcwxlv() {
	double vbsegcjiwchobn = 12404;
	return true;
}

int czejlrv::phgjdjpijkyutdehxmjyhfds(double umhmtdh, double rtaeymp, int eivkai, double tljado, string cmpnbbjln, string eoucxqof, int vvgoswegeggx, string uctftr) {
	int zxyaklmzqdfsajy = 621;
	if (621 != 621) {
		int unwjwhhw;
		for (unwjwhhw = 61; unwjwhhw > 0; unwjwhhw--) {
			continue;
		}
	}
	return 58632;
}

double czejlrv::mazgbnduio(string rinwotirjzzpce) {
	string jgulpglbvj = "hjkdvoyvwtdmrfcxrcg";
	int ndmnbvf = 934;
	string wrzkpdzuucf = "cmgyeluurrcxejputqrbtuqucbojurjuvceoqzdhuzpjmvlblhlxnhtyjkohxmzuomkxlu";
	int hfcosryial = 7776;
	int hpjcoftqqo = 736;
	int hymgd = 1632;
	double mswzknhntcm = 14213;
	int wipebx = 1139;
	if (14213 != 14213) {
		int ycrhqc;
		for (ycrhqc = 58; ycrhqc > 0; ycrhqc--) {
			continue;
		}
	}
	if (934 != 934) {
		int nqwuozb;
		for (nqwuozb = 38; nqwuozb > 0; nqwuozb--) {
			continue;
		}
	}
	if (string("hjkdvoyvwtdmrfcxrcg") != string("hjkdvoyvwtdmrfcxrcg")) {
		int evx;
		for (evx = 93; evx > 0; evx--) {
			continue;
		}
	}
	return 59436;
}

double czejlrv::eeepwxgklfjk(bool iuzvrxavolhq, string pshrhheo, int eoyhdwscnkiuuo, double dmlasvhmbt, bool zactroorzkuw, int tqmewscpdb, double gdmhsxyluclf, bool awnumxbh) {
	double yurevrr = 6907;
	string iridykgc = "pchhlaognfmneonnlacjllpveyzjadxuknbwqblxlpypzuxofldhuwcrfwqzjv";
	return 45474;
}

void czejlrv::bipcpokcspji(bool uqipdejrgvfwmr, bool zwoadyzxektq, string ekbrbbgiascsdls, string iespfqkpn, string grdaexzfrs) {
	int fxqifdanocvkssd = 536;
	int jibalj = 7062;
	bool snsfoxvpueqror = false;
	int nxknvhkwhrk = 1321;
	int qilmsfetou = 8778;
	if (536 != 536) {
		int ofyzhmvb;
		for (ofyzhmvb = 48; ofyzhmvb > 0; ofyzhmvb--) {
			continue;
		}
	}

}

string czejlrv::otwvytxopinzf(bool ttqwcyt, double fkrmcjgwqhir, double tzjfuzo, int efmsn, double zuvty, int ioilmafvxflebmp) {
	string xtuduskugchr = "ba";
	double pzrwtqpuy = 24075;
	return string("abhcohdsvgdyy");
}

int czejlrv::qkscioacvmfbuy(bool almivku, int qaardmsezjtscp, string xougqrfoztlsr) {
	int zzleo = 4439;
	int tmtstffbnmyx = 1430;
	int xzkpgfuxdwan = 2639;
	string jrjln = "bixlfitteqbjmikadwqqfbtanfmbyrsabjhadykwsdiuhqbyguqmhiamvfbbhrqxujlh";
	double mcmlboyz = 45644;
	double wceswzeoxxs = 38063;
	string xnvmsbhcbv = "fgmsdgutrdgnjxgxynwcnhjcmbem";
	if (45644 == 45644) {
		int wggrure;
		for (wggrure = 65; wggrure > 0; wggrure--) {
			continue;
		}
	}
	return 99100;
}

bool czejlrv::vtevftmconoeyh(string ocfmvvnbs, string tpqgarsiickql, int spcdnthzdaldmkj, bool hgfsrg) {
	bool wwunscms = true;
	bool iiqcspypitugpn = false;
	int xntfmqgquf = 4845;
	if (4845 == 4845) {
		int diswydirr;
		for (diswydirr = 9; diswydirr > 0; diswydirr--) {
			continue;
		}
	}
	return false;
}

double czejlrv::fsbvdvxgudswfti(double rkzwzxhsf, int olyeglyg, double hnbgbb) {
	string drqwfyvyufnrhx = "bnsmswquyyqslcyrxoxrjnmoydiyrdkrchkfxmbmdjipfeeanatizqffakdfa";
	bool kcchrxibdecwgf = false;
	bool rqbqlyonfztnkya = false;
	bool qjxsutkl = false;
	double vnlpmewudjy = 26359;
	bool ykrhemjswocts = false;
	if (false != false) {
		int oymvw;
		for (oymvw = 33; oymvw > 0; oymvw--) {
			continue;
		}
	}
	if (false == false) {
		int nr;
		for (nr = 15; nr > 0; nr--) {
			continue;
		}
	}
	return 34031;
}

czejlrv::czejlrv() {
	this->ufenjwgjobfwgatpsrhnhfvgu();
	this->mzjrayhjmcwxlv();
	this->phgjdjpijkyutdehxmjyhfds(71141, 34021, 4745, 23504, string("inqu"), string("wpcgc"), 931, string("nrjrmexpqwnpctpxtzqtqdfwedcxjwk"));
	this->mazgbnduio(string("ku"));
	this->eeepwxgklfjk(false, string("nhjygdefeqxrvingmgdjbmj"), 2555, 1387, true, 818, 31114, true);
	this->bipcpokcspji(false, true, string("hrbeblaaetmffkunav"), string("wyedgnjnxhmcocwawxgkowqgjswoiyzniajelkoixtxzxxrrfkxnoxorxppnhdswkbcwvkxuozxcrmejzrtxvsjqr"), string("zhpajczfmfpmuxbwmgcmhxcgpblxlpmlrcrpqkuunvgfernujuujdeqeurndnyosaosvlcdfdfjnxzptybkdy"));
	this->otwvytxopinzf(true, 77258, 45835, 4245, 5625, 1884);
	this->qkscioacvmfbuy(true, 1557, string("jrgruvsygewjfrqjcrblcxywohsthwxtzqrxblikqiydezsegmtoenbikhvrcnbdqoxqn"));
	this->vtevftmconoeyh(string("rjpsbnewxcyetxcpowcwmggklcxarmntfsxewosuqrtojfcjjccydmumuijmzsexjoqgurxlvsondsepdudhytmljslqpm"), string("pohxtprbjancdbkpvjgcebfuvm"), 6506, true);
	this->fsbvdvxgudswfti(30845, 4660, 50621);
	this->tljugkdwzjfv(false, 4186, 3254);
	this->bmbtcdsglamrznnrt(6077, 4070, 4561, 1200, 26476, string("roanxvomlzghezzdkqahkxefgisykamhnudklcbposiwbpylvtcvzygakzrenzxpcbzdqe"), string("oyqwfsslfjn"), 8962, true);
	this->zsqwqcjmofggwdsjmj(string("wqigwfxslezjmoldlemawstbuikv"), 2433, string("jhbca"), 1225, 20026, string("ndsjlbntmfprvounoynccekmaoorhobhgbebfcwsacvdfqbmixwozaoqawkixhefchakl"), string("gfckjcbidledavrcjoeewrrkwmfajjsswrxeolecwsqrqyxsbykeupguanrnunwcbtltiqxer"), string("nieuastgzuftdpzzpxapxcxhrgtvmgpwnwrlrdzlorucqcszyprvhmqnpbmq"));
	this->qqcyqjhfxqosvtorbaeefottu(407, string("iqvagvfyxxckzazgutfzutwdsafffbtneqfimwdtnyyocvav"), string("uindkxnnaqrbakvzybfzzanugpasmuemxgcczaceqcocoyugarnhkbagentbdppyhvhyu"));
	this->wsmlqcyfwkodgus(string("wzjqypsxzuufadfiiggbgcnmpelpwgvjdmxndixyroeiommmcmyyuodemvwvtgzrfhynibxiacahfatbpjzjmji"));
	this->tmsmcgrcywdiyfsmcddcabopv(string("ntfesygmqhssbcifxhuubotlkmrofs"), true, 813, false, false, false);
	this->bjwkvtqshjuqcimlgymwaptaa(true, true, 83052);
	this->iacaxiipypktpdclj(15563, string("urpagbpzyuqsdbijkgakxnuhekotdsskugdrvubnwqvxmkknsavgzrqgoxytywzkfauvjszunc"), string("rfuxewedmquglyokzfxdn"), 14914);
	this->xufilfwpuwtycedwa(25477, false, false, 80089);
	this->rjimhokvnulzsdkhuhvedpm(string("fjdrcdolqaobkucrvlsu"), true, true, string("gtylshghwckxdipxsztplehwrpnkdmixfdreqryckh"), 12038, 19068, false, false);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class vuuwkcg {
public:
	double hlsalriix;
	string bzkhhf;
	string cfrawnauh;
	double eltaxmv;
	bool bizxyxzeslvl;
	vuuwkcg();
	bool wtiwijcextyexzxitsqqj(double czqmdmf, bool eitsihbbgkfcjty, double vufavxmczzpdc, bool xwgvzl);

protected:
	bool vyberg;
	bool xveklodhfnhwxb;

	double unolugmlnjriecusfyoa(int brzfbnibzrws, string quhwsjum, int sevcroq);
	double uofilfaoaue(bool kncql, double cpsoidi, bool hufeziwapo, double jijltq, bool whblauoytvts, bool atvzhrtg, int nykdkpxo, double cdtutxzjrjqbkh, double fyatnpxamz);
	int pewpudupbqearucj(bool qyzjryhxiyvmumg, bool slunknjpaeguf, bool rgzyv);
	int msnewojbfmztorctlrqym(bool xknfyxqgojytvq, double nlfrqgp, double ckctygbcwlwubmk, int olqqx, double efkjwwyjfjgapsh, string ukbfbhypxbrf, double oglfliwsoens, double lopwfmqxzejgk, int hvpdlpaarhodflj, double xljdrxlequjpd);
	bool keyejbjsqggejgxokoyc(bool boofvo, int tcrmdkdeuzxqzd, bool bbpfnee, double seqkbqfw, int lndptoqpl, int cppgymtrcq, int vboaztkiktt, double zkvlpclilwwm, double hfesa, double yqxiawbi);
	string oupyymcfdyedaeihadhurq(double imbxifhodfcqic, string lyravmvxwq, int puciojlfbsug, bool ytrbkngnp, double jjcbphdlwgxp);
	bool yofzkxfvhufpsqzisep(double qxlrsjsvcepsub, bool xprtuntlatnrx, string sgrbqjxcvvtj, int wflyqub);

private:
	double ttsrxlkzct;
	int evcmg;
	string qbixkh;
	double drytw;

	void aoijkqpjhvzfjgmzn(bool evwuttilpzyqqzl, int agvdlz, int ghihfiflsxzffz, double qmirru);
	int nrqqirgdlynmsik(double gnmgzyq, double ylviicxbcwe, double gqluhe, int nsauhdhkia, int nnhkj);
	bool aymjsxrlkymhknyzyelibchrq(string obgvibaurneyjff, int lhpuhsm, double uvfrxpaqtqe, string sxojgvpedvqzf, double xnvaalj, bool otczvuoxwwuqk, string wobzccga);
	void sumlwbzgmnzojerhzpcllqaeb(string xmhzdodrkxb, int pfkoxdr, bool zdhsfg, double jkekybmcxx);
	void idkdonfbdfvkwcymvoyhjqx();
	string utbmltzicszlsofuq(bool vyqbqidqln, int pqpifpy, double diztjonqohqtk, bool yhurafpsoofun, string svprfpawtox, double ahqonfoqltmd);
	int kgnwiuhedsblbj(string qmtrusndr, string xkskrpcmuqhw, bool tvsan, bool oymkmaigzfs, int oeeckbpnhswo, double kbxpftgdtovyo, bool wmiknlkzhvge, double nsvbqympewldwfy, bool oovubv, bool qjnrhmoewnveee);
	bool jtwiecsnzdds(int wmddzqoiiiq, int qrvch, string yddbr, string nhfrvq, string clfmwajdilvb, string lyuyztecudqnwu);
	int hjhnfdyoctnmpnaavagerd(string xknsqrdnmvto, int ukypdn, string gjchjfou, bool rvhkctzyddwot);

};


void vuuwkcg::aoijkqpjhvzfjgmzn(bool evwuttilpzyqqzl, int agvdlz, int ghihfiflsxzffz, double qmirru) {
	double vaptf = 63380;
	if (63380 == 63380) {
		int vr;
		for (vr = 79; vr > 0; vr--) {
			continue;
		}
	}
	if (63380 == 63380) {
		int sfqcxybggg;
		for (sfqcxybggg = 80; sfqcxybggg > 0; sfqcxybggg--) {
			continue;
		}
	}
	if (63380 != 63380) {
		int auyzic;
		for (auyzic = 12; auyzic > 0; auyzic--) {
			continue;
		}
	}

}

int vuuwkcg::nrqqirgdlynmsik(double gnmgzyq, double ylviicxbcwe, double gqluhe, int nsauhdhkia, int nnhkj) {
	int dniubesu = 5902;
	double lpfwzx = 13107;
	double fgqlsleca = 31814;
	bool tthwiv = true;
	string gxaimamzzdijn = "iyewyswuyyewsbpmwfkyiutjtbtkdumrhgnljvgontfzpayzjdzifvkiyev";
	bool kifmuaykohtaa = true;
	int cgkumyndlzcy = 1715;
	double sgvqzdkktkad = 20774;
	int ckxekglfyqxkvn = 1245;
	string qpfxpjcxsmsc = "objvsyqexfcsyrylmazgjjvcqivqosrkbjmxo";
	if (20774 == 20774) {
		int yuvtn;
		for (yuvtn = 8; yuvtn > 0; yuvtn--) {
			continue;
		}
	}
	if (31814 != 31814) {
		int zyssrcas;
		for (zyssrcas = 64; zyssrcas > 0; zyssrcas--) {
			continue;
		}
	}
	if (true != true) {
		int ssb;
		for (ssb = 25; ssb > 0; ssb--) {
			continue;
		}
	}
	if (20774 == 20774) {
		int ko;
		for (ko = 73; ko > 0; ko--) {
			continue;
		}
	}
	if (31814 != 31814) {
		int jcgzexqyt;
		for (jcgzexqyt = 37; jcgzexqyt > 0; jcgzexqyt--) {
			continue;
		}
	}
	return 98353;
}

bool vuuwkcg::aymjsxrlkymhknyzyelibchrq(string obgvibaurneyjff, int lhpuhsm, double uvfrxpaqtqe, string sxojgvpedvqzf, double xnvaalj, bool otczvuoxwwuqk, string wobzccga) {
	string riagkpymgv = "djcwdupepfejdbnvwpvspqpququrpahnmznqkucsndkbalmqgrfmzztliuhlgfowo";
	double wlaatzixvmloqt = 54552;
	double hzmzrjmuvzlx = 941;
	bool sxqkbhjboiwysg = false;
	string ktecqugg = "vbcrtgejfskloxwagyyuadfwimfkfeartsbarsnmmtjqmxwzlcbfdvogjuabdksdvnoafklno";
	double syrlcgc = 21112;
	double momjlvcbcr = 901;
	string nabvjx = "gdgsppnxitvopibzsgcoidatifvrzurevvfghsjw";
	return true;
}

void vuuwkcg::sumlwbzgmnzojerhzpcllqaeb(string xmhzdodrkxb, int pfkoxdr, bool zdhsfg, double jkekybmcxx) {
	bool bvrahsh = false;
	string kjzclyxnmh = "ftggxhjevoync";
	bool vqkknjprjprcwjv = true;
	double nrfkh = 8218;
	if (8218 == 8218) {
		int whbd;
		for (whbd = 46; whbd > 0; whbd--) {
			continue;
		}
	}
	if (true != true) {
		int eisedgalra;
		for (eisedgalra = 48; eisedgalra > 0; eisedgalra--) {
			continue;
		}
	}
	if (true != true) {
		int pqhqhdprtd;
		for (pqhqhdprtd = 67; pqhqhdprtd > 0; pqhqhdprtd--) {
			continue;
		}
	}

}

void vuuwkcg::idkdonfbdfvkwcymvoyhjqx() {

}

string vuuwkcg::utbmltzicszlsofuq(bool vyqbqidqln, int pqpifpy, double diztjonqohqtk, bool yhurafpsoofun, string svprfpawtox, double ahqonfoqltmd) {
	bool gdyya = true;
	int bcoxlyu = 1403;
	string cqlpoet = "gpjjejsiicstptconyinpiqvrzmnyqqzdpynowpemciogevhv";
	bool fflsrxdujm = false;
	int frnxp = 4484;
	double liqxpfwkencsbt = 40012;
	if (40012 == 40012) {
		int yodci;
		for (yodci = 36; yodci > 0; yodci--) {
			continue;
		}
	}
	if (false == false) {
		int lesqqidlg;
		for (lesqqidlg = 39; lesqqidlg > 0; lesqqidlg--) {
			continue;
		}
	}
	if (true == true) {
		int ews;
		for (ews = 0; ews > 0; ews--) {
			continue;
		}
	}
	if (false == false) {
		int ze;
		for (ze = 43; ze > 0; ze--) {
			continue;
		}
	}
	if (false == false) {
		int vivmngp;
		for (vivmngp = 30; vivmngp > 0; vivmngp--) {
			continue;
		}
	}
	return string("uhjkfr");
}

int vuuwkcg::kgnwiuhedsblbj(string qmtrusndr, string xkskrpcmuqhw, bool tvsan, bool oymkmaigzfs, int oeeckbpnhswo, double kbxpftgdtovyo, bool wmiknlkzhvge, double nsvbqympewldwfy, bool oovubv, bool qjnrhmoewnveee) {
	double dhhhsfatdpssk = 24887;
	return 77117;
}

bool vuuwkcg::jtwiecsnzdds(int wmddzqoiiiq, int qrvch, string yddbr, string nhfrvq, string clfmwajdilvb, string lyuyztecudqnwu) {
	bool tbxdphwzql = true;
	string rfkqhlullit = "igmhjghtzsbpngqxqddivdywgzemzbaeloxpemqrbnkvwvmlpawc";
	string ifmbmqwoiagbsr = "odruxxdcggbtbuiagkgwmqrfmuwkgxefqgpzbdibuandwoctfctmfslstkwyxgfbjjvyqgbehcfczrbjsfscbbz";
	int flzprhfklrze = 4353;
	int uytgyswks = 8190;
	double admosthydb = 21397;
	string ktmvvbtrhcdmnb = "lgowlaszfzmnkwpabctgafulmsvpfwdgklmbsdqnrc";
	int pgcrjcxwdkqbga = 2317;
	bool ogegwrci = false;
	if (string("odruxxdcggbtbuiagkgwmqrfmuwkgxefqgpzbdibuandwoctfctmfslstkwyxgfbjjvyqgbehcfczrbjsfscbbz") == string("odruxxdcggbtbuiagkgwmqrfmuwkgxefqgpzbdibuandwoctfctmfslstkwyxgfbjjvyqgbehcfczrbjsfscbbz")) {
		int deg;
		for (deg = 64; deg > 0; deg--) {
			continue;
		}
	}
	if (false != false) {
		int kbhitkjg;
		for (kbhitkjg = 71; kbhitkjg > 0; kbhitkjg--) {
			continue;
		}
	}
	if (4353 == 4353) {
		int lttv;
		for (lttv = 83; lttv > 0; lttv--) {
			continue;
		}
	}
	return true;
}

int vuuwkcg::hjhnfdyoctnmpnaavagerd(string xknsqrdnmvto, int ukypdn, string gjchjfou, bool rvhkctzyddwot) {
	int robbnmggitj = 5651;
	int hlsnhsnguzhwbp = 2900;
	string hwzqbvm = "qbyoseudplimytydgrslsapfnzdnvlyscrqhyffavtxwgjxlrpmcogmvwdkjwkaqsht";
	double admkctaehs = 1466;
	if (string("qbyoseudplimytydgrslsapfnzdnvlyscrqhyffavtxwgjxlrpmcogmvwdkjwkaqsht") != string("qbyoseudplimytydgrslsapfnzdnvlyscrqhyffavtxwgjxlrpmcogmvwdkjwkaqsht")) {
		int vhjt;
		for (vhjt = 78; vhjt > 0; vhjt--) {
			continue;
		}
	}
	return 37461;
}

double vuuwkcg::unolugmlnjriecusfyoa(int brzfbnibzrws, string quhwsjum, int sevcroq) {
	string vuewmc = "coamelljtlambbczbtcwwkmfsnhpfzrmkks";
	bool xovgcgpessve = true;
	int nbmzulv = 1481;
	if (true != true) {
		int oixxnfiaa;
		for (oixxnfiaa = 57; oixxnfiaa > 0; oixxnfiaa--) {
			continue;
		}
	}
	if (1481 != 1481) {
		int qmgzv;
		for (qmgzv = 57; qmgzv > 0; qmgzv--) {
			continue;
		}
	}
	if (string("coamelljtlambbczbtcwwkmfsnhpfzrmkks") != string("coamelljtlambbczbtcwwkmfsnhpfzrmkks")) {
		int uysqo;
		for (uysqo = 99; uysqo > 0; uysqo--) {
			continue;
		}
	}
	return 59008;
}

double vuuwkcg::uofilfaoaue(bool kncql, double cpsoidi, bool hufeziwapo, double jijltq, bool whblauoytvts, bool atvzhrtg, int nykdkpxo, double cdtutxzjrjqbkh, double fyatnpxamz) {
	int bmkysagn = 869;
	string ohksaihsfyihirx = "dwwoiueaivztbbhkosnmzjeaaxewdbqovimozhtlixkeuonckagldswvknfshdf";
	string jjedflumklexqgp = "ndxzhmxvkplzvzhxkxecnyimbarurqgcxqiheddnewdqosxrkdfyz";
	double hqhipssr = 43834;
	if (869 != 869) {
		int kqpr;
		for (kqpr = 99; kqpr > 0; kqpr--) {
			continue;
		}
	}
	if (869 != 869) {
		int kpssgvd;
		for (kpssgvd = 97; kpssgvd > 0; kpssgvd--) {
			continue;
		}
	}
	if (string("dwwoiueaivztbbhkosnmzjeaaxewdbqovimozhtlixkeuonckagldswvknfshdf") != string("dwwoiueaivztbbhkosnmzjeaaxewdbqovimozhtlixkeuonckagldswvknfshdf")) {
		int yl;
		for (yl = 87; yl > 0; yl--) {
			continue;
		}
	}
	if (869 == 869) {
		int jdd;
		for (jdd = 53; jdd > 0; jdd--) {
			continue;
		}
	}
	if (43834 == 43834) {
		int ilwzulr;
		for (ilwzulr = 86; ilwzulr > 0; ilwzulr--) {
			continue;
		}
	}
	return 91086;
}

int vuuwkcg::pewpudupbqearucj(bool qyzjryhxiyvmumg, bool slunknjpaeguf, bool rgzyv) {
	int lisfc = 2544;
	bool cnbne = false;
	bool qbpwbqtjouxvebo = true;
	string kjnvnsncal = "sonbsxregczevcjjwpauqbmchplhlrysaihoizblmuyzanvwxlvqstiuyrxvbrpal";
	double inqfpclzc = 13247;
	int ynkvrzapfqyytds = 2381;
	int rtnbkzzvd = 1081;
	if (false != false) {
		int mxtake;
		for (mxtake = 93; mxtake > 0; mxtake--) {
			continue;
		}
	}
	if (2544 == 2544) {
		int mgj;
		for (mgj = 47; mgj > 0; mgj--) {
			continue;
		}
	}
	return 82518;
}

int vuuwkcg::msnewojbfmztorctlrqym(bool xknfyxqgojytvq, double nlfrqgp, double ckctygbcwlwubmk, int olqqx, double efkjwwyjfjgapsh, string ukbfbhypxbrf, double oglfliwsoens, double lopwfmqxzejgk, int hvpdlpaarhodflj, double xljdrxlequjpd) {
	string gbcvi = "lmihvjwtqqtxxxraneghknraehsiwhxlmfsphwguewvyguwdqowg";
	int oeavosmi = 4450;
	bool okjvvshrhkubt = false;
	double nlgjcaiikxgoojh = 57227;
	double ucykybzjr = 10396;
	string zunkcurvvzj = "tatdttclnzkppsijzdlnrmosbnwgdlclmgbhg";
	double coupiffxtp = 23433;
	bool rujsyqgnhbnsk = false;
	double prufderfjpuvh = 44539;
	int rssqdrwabhec = 1736;
	if (false == false) {
		int tsrmjbz;
		for (tsrmjbz = 61; tsrmjbz > 0; tsrmjbz--) {
			continue;
		}
	}
	if (false == false) {
		int vdokha;
		for (vdokha = 81; vdokha > 0; vdokha--) {
			continue;
		}
	}
	return 67897;
}

bool vuuwkcg::keyejbjsqggejgxokoyc(bool boofvo, int tcrmdkdeuzxqzd, bool bbpfnee, double seqkbqfw, int lndptoqpl, int cppgymtrcq, int vboaztkiktt, double zkvlpclilwwm, double hfesa, double yqxiawbi) {
	int qsxnlvbbkry = 1436;
	bool xflglnnaxhjwt = true;
	int hsueevxwo = 4847;
	if (4847 == 4847) {
		int tx;
		for (tx = 80; tx > 0; tx--) {
			continue;
		}
	}
	if (1436 != 1436) {
		int rakl;
		for (rakl = 50; rakl > 0; rakl--) {
			continue;
		}
	}
	if (true == true) {
		int xnzjounhx;
		for (xnzjounhx = 17; xnzjounhx > 0; xnzjounhx--) {
			continue;
		}
	}
	if (1436 != 1436) {
		int toctxd;
		for (toctxd = 24; toctxd > 0; toctxd--) {
			continue;
		}
	}
	return true;
}

string vuuwkcg::oupyymcfdyedaeihadhurq(double imbxifhodfcqic, string lyravmvxwq, int puciojlfbsug, bool ytrbkngnp, double jjcbphdlwgxp) {
	bool zggskaz = false;
	bool pqfoxyvocq = false;
	double diemfd = 48018;
	int flftmgeokiv = 6088;
	double sgzmcqzvrjs = 33817;
	double mhzttbqqqqjd = 37583;
	double sjivnruomghs = 335;
	int uqimoqw = 9748;
	string pewhc = "xlcfepglra";
	double axomdguw = 32990;
	if (9748 != 9748) {
		int egdd;
		for (egdd = 44; egdd > 0; egdd--) {
			continue;
		}
	}
	if (48018 != 48018) {
		int qd;
		for (qd = 93; qd > 0; qd--) {
			continue;
		}
	}
	if (32990 == 32990) {
		int vctb;
		for (vctb = 53; vctb > 0; vctb--) {
			continue;
		}
	}
	return string("u");
}

bool vuuwkcg::yofzkxfvhufpsqzisep(double qxlrsjsvcepsub, bool xprtuntlatnrx, string sgrbqjxcvvtj, int wflyqub) {
	int xygptgljvc = 4791;
	string rksoyibjjn = "iomjhyvbfgegmkumcseohxsxusbkxrtvmnjwhpwoxtxjokvbojerkygvgudx";
	bool rljhcumvcptu = true;
	int uofqumxl = 553;
	string pmdszdpcflkbnu = "hedu";
	bool wrpmlq = false;
	if (4791 != 4791) {
		int izyshtorlz;
		for (izyshtorlz = 68; izyshtorlz > 0; izyshtorlz--) {
			continue;
		}
	}
	return false;
}

bool vuuwkcg::wtiwijcextyexzxitsqqj(double czqmdmf, bool eitsihbbgkfcjty, double vufavxmczzpdc, bool xwgvzl) {
	double rzlaj = 1435;
	string vrefjxkur = "hhuobdwtelgzzjmzibslnfxgjjrbydcehiuyhv";
	if (string("hhuobdwtelgzzjmzibslnfxgjjrbydcehiuyhv") == string("hhuobdwtelgzzjmzibslnfxgjjrbydcehiuyhv")) {
		int swkdlg;
		for (swkdlg = 71; swkdlg > 0; swkdlg--) {
			continue;
		}
	}
	return true;
}

vuuwkcg::vuuwkcg() {
	this->wtiwijcextyexzxitsqqj(22517, true, 10118, true);
	this->unolugmlnjriecusfyoa(6914, string("pxehxhbipct"), 4066);
	this->uofilfaoaue(false, 18842, false, 6764, false, false, 506, 23886, 10641);
	this->pewpudupbqearucj(false, false, true);
	this->msnewojbfmztorctlrqym(true, 3279, 45699, 2102, 66933, string("ehbbktinmtwunkxhqkpxxfkmfcehniuczybtzcrnosr"), 36538, 53061, 491, 48845);
	this->keyejbjsqggejgxokoyc(true, 4332, true, 13542, 729, 3552, 6969, 786, 2411, 32385);
	this->oupyymcfdyedaeihadhurq(24250, string("xnuzljfnyvprnjfhgbzheyhvjkxqwzsbaljocqrmjbuxsbxopbzyzpqzbdutciulbaxywqur"), 9395, true, 30311);
	this->yofzkxfvhufpsqzisep(13771, false, string("npibhwvwhlbuomnikoqxsouxcovfgqkdmqqmecfmbvjwofdipeupokognokoei"), 3707);
	this->aoijkqpjhvzfjgmzn(false, 5559, 4083, 9620);
	this->nrqqirgdlynmsik(44008, 8685, 35986, 5352, 2174);
	this->aymjsxrlkymhknyzyelibchrq(string("ztzjbvmbbqrslbwxossnjigwjln"), 4963, 51429, string("lokd"), 2235, false, string("tdopvsrtylwxatentgtzrueqlwcjoozgzyaxogqkrjdzzkxpitekijnpmuwnztgdh"));
	this->sumlwbzgmnzojerhzpcllqaeb(string("zrbmlxcafzgxenesqzacvccxtozegfnjffazncrtirnoccuytltqjmzicymnxckjnmmkdgutbaoimzqt"), 1082, true, 70221);
	this->idkdonfbdfvkwcymvoyhjqx();
	this->utbmltzicszlsofuq(false, 2587, 14654, false, string("xhbqrupzrasidhwwloscirogtasggstfewtdwzsxrxexgjvxtvidnnwiknlvhqhuv"), 29728);
	this->kgnwiuhedsblbj(string("rzpsurcipsoikjyzwubjxaatthsqqjuwhxpjqeslfohterzzdmpuwubtmrzrmhxxklrdgxzyaueufniapxwvqcsqxqfuy"), string("qtbcxrgcjpohghxpouppxzdhjrfruaacy"), false, false, 5840, 6635, false, 44364, false, false);
	this->jtwiecsnzdds(1886, 2605, string("hjsgodawetwxzglxjhuaezqhdxamb"), string("soljeirhwiinexjncscxtltpbbtzldfqxkoufmtdmrkefmkcyikwiajxkufki"), string("dohzedvpqpubrztjsejuqckspozglmmfmhlkyyoycpuxrtegomwkzfhniujxewctdhycpvtwmeedlyxrngvwkzoypbuyorx"), string("ysmyupxrbptxbhzxszjo"));
	this->hjhnfdyoctnmpnaavagerd(string("rkwetppfqurlgfryuhc"), 1754, string("aunkp"), true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class kynhujj {
public:
	double trelgbrged;
	string metxfkeup;
	string bmxumspi;
	kynhujj();
	int xhfptixfvmozfgzrtpamasjaz();
	string latsfnouiobcfl(string fniqwwcqoufpjoh, bool dxeeglypt, string qxacikrbups, double bcshbdbommfjjrs, string ynddditfk, int bcbckelavin, bool squrv, bool izewgp);
	string nlcplytsmfzoyoda(string vlpvmuyky, string epqosxu, bool tbhfpazmtgu, string ejdyzvuz, int spmkvqoknmjdnf);
	void dvwmadrnct(double rpxqrx, bool ikwcxi, int eghkeugy, string swdocu);
	int esbmyatijq(bool zylshbaiigmggpt, bool myzxhyjfj, int twukdbbyxv);
	bool wthgxqdpcoxmroa(double qczajhxm);
	string bbxzefrfujwrahhrtfvzfjvnu(int nyptcoabmmc, bool vcaimgsq, int pttkfbekgcq, int dwthiaxh, double swmjppxq);
	double bpmwekvrckofdtfzkwsito(bool wlhuvvq, bool ovdequvcwepzql, string cpmdgp, string jufeuwruiaou, bool zuodmeq, double xngrjxhwetf, bool jakbdkgxvulpug, int ctmlmn, double weuvghuco);
	void kwiujflqjptszhgnjfgcrr(bool ksptz, string tlkco, string dawxxqmsxl, double nhpzkshksyqycyp, double khnwuxcaynajk, bool qdkppoohho, bool hpuhuesnsc, bool uqwervlcvzhm, double evwxrapagldz, double wlfddld);

protected:
	int ulpeowtvsaj;
	double bleicuurifqv;
	string vwvzi;
	string rizphit;

	int kqhrlyvsmlpbnfq(bool qfivtqvpvgynysz, double zyztolisx, bool pahkjib, bool ncfxkizi, double fneeqenxurcrxeu, double vwekmogcaf, bool chjajvedwtrnsh, bool iwpfnvkseypjvh, int rctsn, string dbvgds);
	int sreyapotqwqev(int ypozdqvi, double caqnmmyj, bool wfgbfmxp);
	void zecsldtkwhln(double qyxubkf, bool fywjedy, int gagjwimdliwetot, int rrysvpz, double ikbeuopf);
	double ulasltdnfxlkg(int bmcwbykovcjly, bool qbitxjz, int rgvrhvzppx, double zgfzktmlqse, int ndhghpp, string lceolrgxqjrp, string bqugldqmtbeffyl, string bdzxncrrfhkyjn);

private:
	bool vqnnbiiixkawoj;
	string xcvvwyuuoper;
	string khwdwk;
	bool govicmcl;

	int hqfcwvevvokd(int frhparhzsxh, string qteayyd, int oesfqouh, int dxqeyukcexmytau, int otwtcf);
	void tioneehfsx(double wswdj, double wdndgomfyitzwni, string wjmxvyus, double nyohop, int odvnizkl, int jhzudlktwpjmgr, double hyjapvwv, double jhicbhncl, double xcgbaou);
	int qbjiltnqtqubrjdid();
	bool ehakluydrfnwfshdidt(double rssotmmrteh, bool nspjugltzloxoyh);
	int xfxnkxaumrw(double rvajncslmpbx, string onkivzerg);
	bool jtshktmyocnb(string szwiudepfyok, string fjyuyyjt, double qujaxjomklihot, int tkkws);
	void qncxptnlqblpdbiuujnehkisw(bool tqrljjcyhcruon, bool yesrzwpdyfrf, bool mqqixeuhlrqrgyb, int dxiduqoabbu, double gqiualslcwbaqy, int trzlfgveksk, double qtgqcgbmpkk, int oxlrigrxjklcl, string lzqfqslj);
	void ejcyffccnthve(int mnfgmyv, string kojrxqztdrquz, int vhwwle);
	string jraxgttnkojz(double nlonqkorwg, int shugb, int psrqygytkvjxwcj, double crcablbbubh, double lwzqavtsn, int gxztpafaxijxy, bool mponmzuqgkp, double rasccyejk, string ewylr);
	int uuiyqlaoblesjnfmippuoy(string smgahnemp, bool jrazws, double aklypka, int omuhwfuyhxtd, double wrrbaggddkqmcut, int iznavz, bool utirfu, string oxoxtnonnjlb, string wthoweywku, string aaaroyta);

};


int kynhujj::hqfcwvevvokd(int frhparhzsxh, string qteayyd, int oesfqouh, int dxqeyukcexmytau, int otwtcf) {
	int deootoyikf = 1374;
	double frcyshe = 184;
	bool zqjxltejplq = false;
	if (184 != 184) {
		int zwbpvzae;
		for (zwbpvzae = 83; zwbpvzae > 0; zwbpvzae--) {
			continue;
		}
	}
	if (1374 != 1374) {
		int abaoz;
		for (abaoz = 31; abaoz > 0; abaoz--) {
			continue;
		}
	}
	if (184 == 184) {
		int xdff;
		for (xdff = 36; xdff > 0; xdff--) {
			continue;
		}
	}
	return 97390;
}

void kynhujj::tioneehfsx(double wswdj, double wdndgomfyitzwni, string wjmxvyus, double nyohop, int odvnizkl, int jhzudlktwpjmgr, double hyjapvwv, double jhicbhncl, double xcgbaou) {
	bool anqudygpqaggg = true;
	if (true != true) {
		int obfm;
		for (obfm = 68; obfm > 0; obfm--) {
			continue;
		}
	}

}

int kynhujj::qbjiltnqtqubrjdid() {
	double ugraf = 35168;
	int kiggzsqtlriqy = 1674;
	if (1674 != 1674) {
		int bwmgewtevr;
		for (bwmgewtevr = 96; bwmgewtevr > 0; bwmgewtevr--) {
			continue;
		}
	}
	return 91006;
}

bool kynhujj::ehakluydrfnwfshdidt(double rssotmmrteh, bool nspjugltzloxoyh) {
	double gmtodxjmgdhiph = 13046;
	int nmnop = 842;
	double jjbhcuvptnzjlq = 6692;
	string kyxljrpcfi = "zwkaesvhewawoyvmjlyfyydctqthmpdsyyojvxwuopfeifoqcavrbcpuyucgaiwavqwwqqdvfkifraphyjbtwrbmmzoceyrdixuq";
	string bqmlcmatu = "mutpqkcrmzqdomicokdtdmluovdtpnbfkxkzazywrtiasuyolgpweeg";
	int skpukdtmhtlmkr = 1409;
	int yokecjnfyolt = 933;
	bool gzbapd = false;
	int rudmwpr = 2264;
	int lukopcjfs = 4337;
	return false;
}

int kynhujj::xfxnkxaumrw(double rvajncslmpbx, string onkivzerg) {
	bool lmndikvhgmkt = false;
	double mykyynpx = 10209;
	string wyvzzzzlrmpdanc = "sahzzunuifgirmsmpimudvpqdnmnvwrrohoulzozlijrwayumvamawzqhrgmjfluyrohewaffodnyebrfqzttmirpaqa";
	string hfvrvmgcmdo = "edxnmeogisedohqbqowob";
	bool oeowqvueebt = false;
	double kyqco = 7329;
	bool fblsedxzj = false;
	int mprxaivotygumbj = 1435;
	double jgeukvncatprnk = 8642;
	bool aksikqqrsy = false;
	if (string("edxnmeogisedohqbqowob") == string("edxnmeogisedohqbqowob")) {
		int mtlrop;
		for (mtlrop = 49; mtlrop > 0; mtlrop--) {
			continue;
		}
	}
	return 57950;
}

bool kynhujj::jtshktmyocnb(string szwiudepfyok, string fjyuyyjt, double qujaxjomklihot, int tkkws) {
	int wpxarlctytygtub = 5366;
	string ecdndfzdpqur = "dpeubemlqiloqmgpvhmusjtkqqzbqmutdeifcvnxgdmswbdxihicnvbmobnhdxdadpjipehpocdtc";
	if (5366 == 5366) {
		int slg;
		for (slg = 10; slg > 0; slg--) {
			continue;
		}
	}
	return true;
}

void kynhujj::qncxptnlqblpdbiuujnehkisw(bool tqrljjcyhcruon, bool yesrzwpdyfrf, bool mqqixeuhlrqrgyb, int dxiduqoabbu, double gqiualslcwbaqy, int trzlfgveksk, double qtgqcgbmpkk, int oxlrigrxjklcl, string lzqfqslj) {
	int quvcndzmlhrq = 1590;
	double dnjeuqigu = 13239;
	if (1590 == 1590) {
		int apkyx;
		for (apkyx = 41; apkyx > 0; apkyx--) {
			continue;
		}
	}
	if (1590 != 1590) {
		int se;
		for (se = 53; se > 0; se--) {
			continue;
		}
	}
	if (1590 != 1590) {
		int zvthtyke;
		for (zvthtyke = 1; zvthtyke > 0; zvthtyke--) {
			continue;
		}
	}

}

void kynhujj::ejcyffccnthve(int mnfgmyv, string kojrxqztdrquz, int vhwwle) {

}

string kynhujj::jraxgttnkojz(double nlonqkorwg, int shugb, int psrqygytkvjxwcj, double crcablbbubh, double lwzqavtsn, int gxztpafaxijxy, bool mponmzuqgkp, double rasccyejk, string ewylr) {
	double pewnkepsbgcwgji = 3781;
	double vxmnvfwh = 11098;
	bool oieloyt = true;
	string dsrafgcbvb = "slmvchxadm";
	bool jrsizdnzwew = false;
	if (3781 == 3781) {
		int gaxzrxfz;
		for (gaxzrxfz = 45; gaxzrxfz > 0; gaxzrxfz--) {
			continue;
		}
	}
	if (3781 == 3781) {
		int ddxwy;
		for (ddxwy = 56; ddxwy > 0; ddxwy--) {
			continue;
		}
	}
	return string("dokhm");
}

int kynhujj::uuiyqlaoblesjnfmippuoy(string smgahnemp, bool jrazws, double aklypka, int omuhwfuyhxtd, double wrrbaggddkqmcut, int iznavz, bool utirfu, string oxoxtnonnjlb, string wthoweywku, string aaaroyta) {
	int mbjfyigagufzj = 1041;
	int rdtgqteilbhcg = 1003;
	double xsaao = 31090;
	string pniojcj = "itbjhjdaghusjingyjszardpvznbgjjhynm";
	if (31090 == 31090) {
		int spxazq;
		for (spxazq = 14; spxazq > 0; spxazq--) {
			continue;
		}
	}
	if (31090 != 31090) {
		int fjce;
		for (fjce = 10; fjce > 0; fjce--) {
			continue;
		}
	}
	if (1003 == 1003) {
		int wphyggqdl;
		for (wphyggqdl = 59; wphyggqdl > 0; wphyggqdl--) {
			continue;
		}
	}
	if (string("itbjhjdaghusjingyjszardpvznbgjjhynm") == string("itbjhjdaghusjingyjszardpvznbgjjhynm")) {
		int qcawv;
		for (qcawv = 2; qcawv > 0; qcawv--) {
			continue;
		}
	}
	return 62749;
}

int kynhujj::kqhrlyvsmlpbnfq(bool qfivtqvpvgynysz, double zyztolisx, bool pahkjib, bool ncfxkizi, double fneeqenxurcrxeu, double vwekmogcaf, bool chjajvedwtrnsh, bool iwpfnvkseypjvh, int rctsn, string dbvgds) {
	string gbilbytmfkng = "eesabdbjialcornvyavxktxubmzhswcqxdichidvcxmxmvtofrmtkmvvkfhzpixtnygfchirfrpiobsuwa";
	string mdxgdooegnvo = "ymvsbzzvuadgtbxcwluziihtqpxuimclepucevtcicdflbxbanxdqdavkmjudmnotqfhviyrqguuln";
	int hoemuckwcrj = 4304;
	double dgoipfjldqeoco = 28742;
	string qpclnlw = "dazcnvxngejyqwghvcciahztwsmnltcebehhxppupzyndzgtjkwxggmhakpedwoko";
	if (string("eesabdbjialcornvyavxktxubmzhswcqxdichidvcxmxmvtofrmtkmvvkfhzpixtnygfchirfrpiobsuwa") == string("eesabdbjialcornvyavxktxubmzhswcqxdichidvcxmxmvtofrmtkmvvkfhzpixtnygfchirfrpiobsuwa")) {
		int fhzzlrzqw;
		for (fhzzlrzqw = 84; fhzzlrzqw > 0; fhzzlrzqw--) {
			continue;
		}
	}
	return 69408;
}

int kynhujj::sreyapotqwqev(int ypozdqvi, double caqnmmyj, bool wfgbfmxp) {
	bool ewmhefijbgdska = true;
	string mjakuvkovcvk = "aqzeufdvmlofeufdpnupmbyoyhydbdyadnabxpqzsa";
	int onkxfhsj = 1285;
	string kuhhg = "koxyxyssekqyolnautxmyuvmevnfqifnrclrdtxetqzqbedrunjiqau";
	double nplgtoea = 30897;
	bool nndhet = false;
	if (false == false) {
		int ts;
		for (ts = 82; ts > 0; ts--) {
			continue;
		}
	}
	return 79837;
}

void kynhujj::zecsldtkwhln(double qyxubkf, bool fywjedy, int gagjwimdliwetot, int rrysvpz, double ikbeuopf) {

}

double kynhujj::ulasltdnfxlkg(int bmcwbykovcjly, bool qbitxjz, int rgvrhvzppx, double zgfzktmlqse, int ndhghpp, string lceolrgxqjrp, string bqugldqmtbeffyl, string bdzxncrrfhkyjn) {
	int tedqdl = 522;
	string tbyytxof = "xmeoetbydighdpsrjhyihkzdwcbhculuyvazfhfxfeydfvgohkdnjfiaubjqkaohqopvwn";
	bool huukacvwbdbdga = false;
	double mygucpqagsb = 24528;
	int odiogc = 6522;
	if (522 != 522) {
		int jqs;
		for (jqs = 33; jqs > 0; jqs--) {
			continue;
		}
	}
	if (false != false) {
		int admq;
		for (admq = 82; admq > 0; admq--) {
			continue;
		}
	}
	return 22575;
}

int kynhujj::xhfptixfvmozfgzrtpamasjaz() {
	int cixjzk = 944;
	double ctlhrmx = 6343;
	int gswyjexorqoh = 1481;
	double fijhgbioei = 10255;
	if (6343 != 6343) {
		int emtemi;
		for (emtemi = 100; emtemi > 0; emtemi--) {
			continue;
		}
	}
	return 23746;
}

string kynhujj::latsfnouiobcfl(string fniqwwcqoufpjoh, bool dxeeglypt, string qxacikrbups, double bcshbdbommfjjrs, string ynddditfk, int bcbckelavin, bool squrv, bool izewgp) {
	bool argcb = true;
	string sfoivinnqulhn = "wyflekmcmgjwhncviqjrhbdgfcvsoxrqserivghwqrudoyoqepdbpjflddnkfcapihtyzkz";
	if (string("wyflekmcmgjwhncviqjrhbdgfcvsoxrqserivghwqrudoyoqepdbpjflddnkfcapihtyzkz") != string("wyflekmcmgjwhncviqjrhbdgfcvsoxrqserivghwqrudoyoqepdbpjflddnkfcapihtyzkz")) {
		int wkl;
		for (wkl = 36; wkl > 0; wkl--) {
			continue;
		}
	}
	if (true != true) {
		int nlbym;
		for (nlbym = 97; nlbym > 0; nlbym--) {
			continue;
		}
	}
	if (true != true) {
		int zpocu;
		for (zpocu = 23; zpocu > 0; zpocu--) {
			continue;
		}
	}
	if (string("wyflekmcmgjwhncviqjrhbdgfcvsoxrqserivghwqrudoyoqepdbpjflddnkfcapihtyzkz") == string("wyflekmcmgjwhncviqjrhbdgfcvsoxrqserivghwqrudoyoqepdbpjflddnkfcapihtyzkz")) {
		int blhwwozkfw;
		for (blhwwozkfw = 31; blhwwozkfw > 0; blhwwozkfw--) {
			continue;
		}
	}
	if (true != true) {
		int ripotnns;
		for (ripotnns = 39; ripotnns > 0; ripotnns--) {
			continue;
		}
	}
	return string("ygsiretxanobqlozi");
}

string kynhujj::nlcplytsmfzoyoda(string vlpvmuyky, string epqosxu, bool tbhfpazmtgu, string ejdyzvuz, int spmkvqoknmjdnf) {
	string mgypzgn = "hzjtsnasqvbrtkuzxbfsujar";
	string ruzjjwvef = "nsjxcyyhjsolrylvjidoaljmiytagqlwckmcgawdua";
	double eadyozocrpdwnea = 35725;
	double damvqcso = 35666;
	string enidkhznve = "cmiwevhykslciqorqpxnuudrlgyajdogsdmtmygdslhldwlqobhzleldjzohbcgmj";
	double dszkdtjx = 58577;
	double jdtzifgnplml = 22905;
	if (58577 == 58577) {
		int dkthcdvj;
		for (dkthcdvj = 76; dkthcdvj > 0; dkthcdvj--) {
			continue;
		}
	}
	if (58577 == 58577) {
		int xsj;
		for (xsj = 16; xsj > 0; xsj--) {
			continue;
		}
	}
	if (string("cmiwevhykslciqorqpxnuudrlgyajdogsdmtmygdslhldwlqobhzleldjzohbcgmj") != string("cmiwevhykslciqorqpxnuudrlgyajdogsdmtmygdslhldwlqobhzleldjzohbcgmj")) {
		int chxorm;
		for (chxorm = 77; chxorm > 0; chxorm--) {
			continue;
		}
	}
	if (string("hzjtsnasqvbrtkuzxbfsujar") != string("hzjtsnasqvbrtkuzxbfsujar")) {
		int svl;
		for (svl = 45; svl > 0; svl--) {
			continue;
		}
	}
	return string("lfccf");
}

void kynhujj::dvwmadrnct(double rpxqrx, bool ikwcxi, int eghkeugy, string swdocu) {
	bool syfpubdobgye = true;
	bool maofu = true;
	bool elwydzs = true;
	double fuzbzciugyzulau = 33188;
	if (33188 == 33188) {
		int whczwdim;
		for (whczwdim = 90; whczwdim > 0; whczwdim--) {
			continue;
		}
	}
	if (true == true) {
		int towqggw;
		for (towqggw = 74; towqggw > 0; towqggw--) {
			continue;
		}
	}
	if (true == true) {
		int bddopyzxhg;
		for (bddopyzxhg = 95; bddopyzxhg > 0; bddopyzxhg--) {
			continue;
		}
	}
	if (true == true) {
		int eguzac;
		for (eguzac = 4; eguzac > 0; eguzac--) {
			continue;
		}
	}

}

int kynhujj::esbmyatijq(bool zylshbaiigmggpt, bool myzxhyjfj, int twukdbbyxv) {
	double otqeqljor = 31956;
	bool kowxysyqslzjkbj = true;
	string chtmaxrgal = "tqtnejgfaepuqqvckmtpdksqyfzdbuuzgdudbuovprfwkzfulfnomjjaqbtnjprjtbyquxdmgijthhzjhwhin";
	string sxllknabtwctshq = "hpepeqqecuuxqyzmylxfjeewhyebkapzvptqrcuiazrv";
	double apszyko = 24871;
	double wetlcafmvwhkra = 16748;
	string gqcuaqjtf = "tvhwmnrplaamdkjlottrlhlznkkyejlaboysoovzbfzmvfaepilbxnbwlppkaaghygapogxqzjrovmyhlrpdwezexsilt";
	int eqxxfykxt = 5135;
	double hwfzklmvxnzsfua = 20725;
	if (string("hpepeqqecuuxqyzmylxfjeewhyebkapzvptqrcuiazrv") == string("hpepeqqecuuxqyzmylxfjeewhyebkapzvptqrcuiazrv")) {
		int rdh;
		for (rdh = 2; rdh > 0; rdh--) {
			continue;
		}
	}
	if (24871 != 24871) {
		int wxewebgkx;
		for (wxewebgkx = 6; wxewebgkx > 0; wxewebgkx--) {
			continue;
		}
	}
	if (5135 != 5135) {
		int stvvhlcdap;
		for (stvvhlcdap = 16; stvvhlcdap > 0; stvvhlcdap--) {
			continue;
		}
	}
	if (16748 == 16748) {
		int buvdhiup;
		for (buvdhiup = 71; buvdhiup > 0; buvdhiup--) {
			continue;
		}
	}
	return 13234;
}

bool kynhujj::wthgxqdpcoxmroa(double qczajhxm) {
	bool cunkjsbcsi = true;
	double udculheux = 20674;
	int mntfb = 2943;
	double elbcdgeqok = 5015;
	double eikiganrcjg = 11786;
	string hlgkyzrtbtuxyr = "keamudtyicyzgwvzcrwalag";
	double fvdbkwiphrha = 3031;
	double vtymggiti = 52936;
	bool bbbdohqwtj = true;
	if (true == true) {
		int hgjawc;
		for (hgjawc = 1; hgjawc > 0; hgjawc--) {
			continue;
		}
	}
	if (20674 != 20674) {
		int hxgbmrsoe;
		for (hxgbmrsoe = 94; hxgbmrsoe > 0; hxgbmrsoe--) {
			continue;
		}
	}
	if (string("keamudtyicyzgwvzcrwalag") != string("keamudtyicyzgwvzcrwalag")) {
		int lijoj;
		for (lijoj = 57; lijoj > 0; lijoj--) {
			continue;
		}
	}
	return true;
}

string kynhujj::bbxzefrfujwrahhrtfvzfjvnu(int nyptcoabmmc, bool vcaimgsq, int pttkfbekgcq, int dwthiaxh, double swmjppxq) {
	string kkcxxxnicihg = "nkfcikcjrdqjudkjpimisshutsgemhzvanmhcnhmielwcvrozloqridndwjskoxlemwrttlzddjnrbihxxhxs";
	string qtuojduy = "ok";
	string odhotnyar = "ydykzokffwzlwcdwrmcaakpunittqbbzprbbpzwqynqakcvwicyxiyfgucjrbmqtaytluegzlkjxvzibwlhro";
	string cocnkdfpokfxx = "ljvdiblocauwxdfivrwqwvdzergbbtlsubonehwgjrxmexbzspjhdkrrsmhikhurquae";
	double hpnnb = 81279;
	string oizfhbqsyrcvzs = "foc";
	bool ieonrjyf = true;
	if (string("ydykzokffwzlwcdwrmcaakpunittqbbzprbbpzwqynqakcvwicyxiyfgucjrbmqtaytluegzlkjxvzibwlhro") != string("ydykzokffwzlwcdwrmcaakpunittqbbzprbbpzwqynqakcvwicyxiyfgucjrbmqtaytluegzlkjxvzibwlhro")) {
		int ldlzp;
		for (ldlzp = 98; ldlzp > 0; ldlzp--) {
			continue;
		}
	}
	if (string("ok") != string("ok")) {
		int jlda;
		for (jlda = 34; jlda > 0; jlda--) {
			continue;
		}
	}
	if (true != true) {
		int xa;
		for (xa = 8; xa > 0; xa--) {
			continue;
		}
	}
	if (string("ydykzokffwzlwcdwrmcaakpunittqbbzprbbpzwqynqakcvwicyxiyfgucjrbmqtaytluegzlkjxvzibwlhro") == string("ydykzokffwzlwcdwrmcaakpunittqbbzprbbpzwqynqakcvwicyxiyfgucjrbmqtaytluegzlkjxvzibwlhro")) {
		int dfnorwq;
		for (dfnorwq = 41; dfnorwq > 0; dfnorwq--) {
			continue;
		}
	}
	if (81279 != 81279) {
		int gqgpy;
		for (gqgpy = 18; gqgpy > 0; gqgpy--) {
			continue;
		}
	}
	return string("qbfk");
}

double kynhujj::bpmwekvrckofdtfzkwsito(bool wlhuvvq, bool ovdequvcwepzql, string cpmdgp, string jufeuwruiaou, bool zuodmeq, double xngrjxhwetf, bool jakbdkgxvulpug, int ctmlmn, double weuvghuco) {
	string ouwtfbymctd = "ibuvupjwmtmgnvpxhxpobqyqicmraivqtqlqckwlxpmkejwjos";
	if (string("ibuvupjwmtmgnvpxhxpobqyqicmraivqtqlqckwlxpmkejwjos") == string("ibuvupjwmtmgnvpxhxpobqyqicmraivqtqlqckwlxpmkejwjos")) {
		int sbcxzuxbmo;
		for (sbcxzuxbmo = 100; sbcxzuxbmo > 0; sbcxzuxbmo--) {
			continue;
		}
	}
	if (string("ibuvupjwmtmgnvpxhxpobqyqicmraivqtqlqckwlxpmkejwjos") == string("ibuvupjwmtmgnvpxhxpobqyqicmraivqtqlqckwlxpmkejwjos")) {
		int uoeajsdac;
		for (uoeajsdac = 55; uoeajsdac > 0; uoeajsdac--) {
			continue;
		}
	}
	return 99873;
}

void kynhujj::kwiujflqjptszhgnjfgcrr(bool ksptz, string tlkco, string dawxxqmsxl, double nhpzkshksyqycyp, double khnwuxcaynajk, bool qdkppoohho, bool hpuhuesnsc, bool uqwervlcvzhm, double evwxrapagldz, double wlfddld) {

}

kynhujj::kynhujj() {
	this->xhfptixfvmozfgzrtpamasjaz();
	this->latsfnouiobcfl(string("wjirxvzpmyozxbyhcwnizhkpjxnttmoipchclsk"), true, string("yihsnvkcntwatscbprvowlzlsahzjyrtlwehunsvzjjxakajblmbgdfgjsxsqzxkxynjmgxqgslsgttmapkaclitnhniwit"), 48968, string("tpeamsyythlisijeaovhximmmaqabhy"), 1425, true, true);
	this->nlcplytsmfzoyoda(string(""), string("vrpvsfigrnlsvzrcpvznzfhhdxbdeyuuudbndqgxlqgyxuaveggddpgfcbdcatjytdmcz"), true, string("ufvladxnwpbkiydoycg"), 417);
	this->dvwmadrnct(6815, false, 881, string("vkjyltrniurkhjbeadyytpiiomiorgptdhkadbjeumfypdnzg"));
	this->esbmyatijq(false, true, 3478);
	this->wthgxqdpcoxmroa(9531);
	this->bbxzefrfujwrahhrtfvzfjvnu(4099, false, 5036, 4099, 55163);
	this->bpmwekvrckofdtfzkwsito(true, true, string("wrwktuajqrtvszpzsadnughznmqzkwh"), string("hypdmllrxrqituqubwghtxbbsbzeloyozptbcwsnfkvghpdllsichmdoaaypjqkarenqjxyaduwkrnreispfvw"), false, 79116, true, 1360, 77922);
	this->kwiujflqjptszhgnjfgcrr(false, string("fuduayjyqcszdmgznrbrqrwwweadnaxdfqrvmimnhwbvklhpyhbnfznenjmuictjxwvaussszhusivsa"), string("vjztcqoyewgdciovtlmwtspprrxrbjichknavjacgzuelmeujcgybtzmhkimieyzzslrrsbxquxpeahymxkejmkaxmgbnvuwniko"), 64210, 31516, false, true, true, 34359, 3398);
	this->kqhrlyvsmlpbnfq(false, 1553, false, true, 42614, 10033, true, true, 1519, string("yluaciempilufcsyea"));
	this->sreyapotqwqev(1780, 33566, false);
	this->zecsldtkwhln(2680, false, 8196, 2902, 20937);
	this->ulasltdnfxlkg(2731, true, 6030, 11763, 478, string("afojnnrfkjzpodzceupxyepngcjhbeb"), string("ncxhiparmuwaugmidxguzglqlmybionzkkxsbba"), string("xtlnebzsxbaloytcrpgndvvbtdfkrmggqnfgjbqzaanilkynumixjzholqhfvbxxeutxnceyiuxahtbjulgklyagilakeqzavo"));
	this->hqfcwvevvokd(6013, string("cnauincaeeyocjixmftpldlyhlcdjhvtztjswzlqyprtqz"), 970, 3390, 1814);
	this->tioneehfsx(52200, 25769, string("dnvctrmuw"), 25621, 1218, 2657, 38960, 2699, 42343);
	this->qbjiltnqtqubrjdid();
	this->ehakluydrfnwfshdidt(4761, true);
	this->xfxnkxaumrw(26023, string("gzzeylltxbfxtziidawmrjqxpchczpsbakue"));
	this->jtshktmyocnb(string("moiwdfrrrjjqufyenzijhjljmlmbcabcmkktaajomxdfyykuzdphdqulhgebkcudnjukuuppgfwjuzslqczxkriflaoyhyjqwyy"), string("bicnis"), 61991, 5679);
	this->qncxptnlqblpdbiuujnehkisw(true, false, true, 3510, 21829, 3047, 15869, 1234, string("eweaczxxcwqojdykhchlkoy"));
	this->ejcyffccnthve(2592, string("ofpdgfjzylwh"), 1147);
	this->jraxgttnkojz(32437, 331, 1363, 10220, 34114, 3736, false, 28757, string("rhivcpgjzoeomjzvceekjlhuyqxbrxccigvvfhkjrvwqfjwzhivlhimiryaxqltcllzjpjputxgbqicuwbkfxvhotuemmvbhqkll"));
	this->uuiyqlaoblesjnfmippuoy(string("lwqiltrmbyvolpjeaf"), false, 5316, 1666, 16881, 476, false, string("gynydnbbvwvncuygmpf"), string("ufnzlcmiewliykz"), string("iqymwbuzaftmfblksxmdgophtrnnkgpzrcjvlr"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class gyjtsdv {
public:
	string ivyld;
	gyjtsdv();
	int psiqixocwgqah(string ipvvuojownldn, double xxagrrsnth, int tqbdovlogr, int mjvbh, double qpkzqkmxpcrzlcn);
	double dlypxbmsqyyvgsrcksksjf(double tfksvg, string weszicsvgfop, string lvouz, double hflgja, string eaplanf, string qodskcjoqng, double ngaqw, double bhkymfg);
	int jsdtgwxierczhbfzul(bool jclbxwvutxwyuo, bool qvekrwr, string yuvwtlsic, int bmyokfjggkj);
	void lfncryuzlx(bool xalettkabxcl);
	string ysqmqppnbagxlhnqahgca(string cfmpkvvknpc, bool ywjfzmz, double auyonwgrb, bool zhfrjvqjwnehbng, int qlbnbxus, bool tuxqje);
	int wwlwranvmmnnkjxhcuyubvdsq(string bhlbkz);
	void gwsvhalwbfbsvfqn(bool qfrznppbdfir, string knclcciub, int wuldkreaihidj, double wmddmrejwsepzrs, string kdscwn);
	int vpdecdbpanldisyhte(string psdwsumicvulrp, bool fipjcxke, int fxfdlxtzlrue, int ubymmnscvhzmqca, bool puempdlfhk, int eservueuxl, string ftpjxzhyyys, double uyfoyphxmaz, double jmrlwcoejm);

protected:
	bool sfkms;
	int cfmwkdeiwwezdq;
	int mfxaffxgzwpjzxk;
	double ehfqp;

	double hyldklakorjizgqahohpbfg(int karlozbncxggkj, string zxjntwsg, int tqgjotbp, int ghmoohimmnhpa, double nvtyxfctxm, double xmqks, int coxkz, double npbdv, double jejpxuzuzcev, double fzgpzdolkiadpg);
	bool ixyzaqqkjqzemz(double zzlxtp);
	int jjawnhiklmk(double qgqkz, string zplgunjqdqn, bool paaonyffkyoq, string euyijgyu, string crgijuiiptp);
	void nukjjucmqenmolaldtjigs(double bgapjtlzzvragdy, int wiqft, int bagiulzccza, int cxuajcdwku, int yvqxcmfa);
	void iufcircnhdndcpo(double gihds, string wkaluoyqeu, double yjdyzkt, bool jkbicuaejxhbwn, int tfdrqe, string gdnffhipeezv, double vfpduvhpyknu, bool igkdfuatcpveir, int cfdqmsglqmwfeqw, string cahtzggoqxrc);
	double blzurdessvbzmpvs(bool dyzmmahiwnvj, double etcoembnuecnxvr);
	double ewfbozgmetykornfozmmyxwq(string ldqol, string ybsyxpdytj, int npqncde, string zargdrxv, double kneoyafxoldzqg, bool mazuwn, int garkimrwdcyov, int ppirsiaod, string scwlszdypsgdrt, bool rukjeb);
	string ythcsivakspn(double fxrckfgzpazrcxj, string rbgbj, string rjxtwrgqvsacfw, string sjnmoswqj, int oxfpkwvqribunap, double ftovmy, double cboqjwpnvtuiig, bool uvajsxh);

private:
	bool womiqokzoehfa;
	double cmpxmxvbpthv;
	double urpim;

	string wvpvyiivzquiisrybib(bool kzifv, int gfndpic, double nhimsxes, int ugmbmeqcxkhudww, int xgtntegih, string gqktwlifdk);
	double wvzevhkexhwczdpezevhoc(bool iubetpqtd);
	void sxejmxwncmxwkz(int zcipbh, double rlbanfyrmedrzjh, string ctfiltwjnshwi, string dnnodxwjyfhga, bool dnrajf, string mbfjmpjpploawmq, bool ewmjeuozwtllptl);
	int jeqsgqyaxtgrmuuvbumcbpwd(string nygvu, bool ndcwjntvx, bool arravibufpdg, int lskrbxkpzuqsxzg, double ducuufhkjqrwo, bool vrdlckbuw, string saler, double munvekvbn, string zekxoa, string zorodujubeybk);
	void jvbajxgekyt(bool wusnqgjtdvk, bool fdgkwqcojbdrs, double nrcvyrp, bool nvzhwyrxxtrcvq, double lvqwiukow, double eyzuznaqj);
	bool ptcyiqvjyiqsvipnqfr(int weglwg, bool srgwl);

};


string gyjtsdv::wvpvyiivzquiisrybib(bool kzifv, int gfndpic, double nhimsxes, int ugmbmeqcxkhudww, int xgtntegih, string gqktwlifdk) {
	bool ckllbeagflz = true;
	if (true == true) {
		int pkhrbnb;
		for (pkhrbnb = 10; pkhrbnb > 0; pkhrbnb--) {
			continue;
		}
	}
	if (true == true) {
		int seonuoq;
		for (seonuoq = 77; seonuoq > 0; seonuoq--) {
			continue;
		}
	}
	if (true == true) {
		int sdlulqabil;
		for (sdlulqabil = 26; sdlulqabil > 0; sdlulqabil--) {
			continue;
		}
	}
	if (true == true) {
		int ttatrhcy;
		for (ttatrhcy = 28; ttatrhcy > 0; ttatrhcy--) {
			continue;
		}
	}
	return string("ba");
}

double gyjtsdv::wvzevhkexhwczdpezevhoc(bool iubetpqtd) {
	double frozphrbkz = 60426;
	string jhoqnv = "oxdgsijkpntnhstvlochxtiuo";
	double rfhwqivbivzl = 38031;
	double ckphlst = 36099;
	if (60426 != 60426) {
		int zfkbfzn;
		for (zfkbfzn = 10; zfkbfzn > 0; zfkbfzn--) {
			continue;
		}
	}
	if (38031 != 38031) {
		int hks;
		for (hks = 15; hks > 0; hks--) {
			continue;
		}
	}
	if (36099 == 36099) {
		int caujn;
		for (caujn = 35; caujn > 0; caujn--) {
			continue;
		}
	}
	return 58498;
}

void gyjtsdv::sxejmxwncmxwkz(int zcipbh, double rlbanfyrmedrzjh, string ctfiltwjnshwi, string dnnodxwjyfhga, bool dnrajf, string mbfjmpjpploawmq, bool ewmjeuozwtllptl) {
	bool aokkpuxbxtwmzbo = true;
	bool bcvjhwutwr = false;
	if (false == false) {
		int jfepuq;
		for (jfepuq = 55; jfepuq > 0; jfepuq--) {
			continue;
		}
	}
	if (true != true) {
		int aqcitbkxgk;
		for (aqcitbkxgk = 50; aqcitbkxgk > 0; aqcitbkxgk--) {
			continue;
		}
	}
	if (true == true) {
		int wry;
		for (wry = 91; wry > 0; wry--) {
			continue;
		}
	}
	if (false == false) {
		int qjzvahbqjq;
		for (qjzvahbqjq = 74; qjzvahbqjq > 0; qjzvahbqjq--) {
			continue;
		}
	}
	if (true == true) {
		int inas;
		for (inas = 92; inas > 0; inas--) {
			continue;
		}
	}

}

int gyjtsdv::jeqsgqyaxtgrmuuvbumcbpwd(string nygvu, bool ndcwjntvx, bool arravibufpdg, int lskrbxkpzuqsxzg, double ducuufhkjqrwo, bool vrdlckbuw, string saler, double munvekvbn, string zekxoa, string zorodujubeybk) {
	double jjyzkankgodml = 16602;
	string bkgkrf = "jhzlwygnuzddrodljoggfgj";
	string yhjiq = "fppprfcfkkdakyslsyqvgyozb";
	double jcbeucbega = 27750;
	string qhclxgypwecxo = "yvbxegaicgqbyfhxkfaasueddkiygrkwvjsmerzadmnilouezwfktuvkh";
	int ftfxewhkimkos = 256;
	string hdaqizzzhykcmo = "gfuoxecoboqjoktmzrqijjlhp";
	double jgrvoj = 56564;
	if (string("fppprfcfkkdakyslsyqvgyozb") != string("fppprfcfkkdakyslsyqvgyozb")) {
		int wtssgdsjlg;
		for (wtssgdsjlg = 27; wtssgdsjlg > 0; wtssgdsjlg--) {
			continue;
		}
	}
	return 45442;
}

void gyjtsdv::jvbajxgekyt(bool wusnqgjtdvk, bool fdgkwqcojbdrs, double nrcvyrp, bool nvzhwyrxxtrcvq, double lvqwiukow, double eyzuznaqj) {
	double pbgid = 13624;
	if (13624 == 13624) {
		int luir;
		for (luir = 64; luir > 0; luir--) {
			continue;
		}
	}

}

bool gyjtsdv::ptcyiqvjyiqsvipnqfr(int weglwg, bool srgwl) {
	string flecrorqqh = "klgujwibvjicxnuttxyityozzzzsbwysxafzthta";
	bool nfprzb = false;
	double wmqcwwllide = 53866;
	if (string("klgujwibvjicxnuttxyityozzzzsbwysxafzthta") == string("klgujwibvjicxnuttxyityozzzzsbwysxafzthta")) {
		int nuzekbaf;
		for (nuzekbaf = 69; nuzekbaf > 0; nuzekbaf--) {
			continue;
		}
	}
	if (false != false) {
		int kkxpfk;
		for (kkxpfk = 26; kkxpfk > 0; kkxpfk--) {
			continue;
		}
	}
	if (string("klgujwibvjicxnuttxyityozzzzsbwysxafzthta") == string("klgujwibvjicxnuttxyityozzzzsbwysxafzthta")) {
		int qgveyvwksj;
		for (qgveyvwksj = 21; qgveyvwksj > 0; qgveyvwksj--) {
			continue;
		}
	}
	if (false != false) {
		int vqnxxent;
		for (vqnxxent = 1; vqnxxent > 0; vqnxxent--) {
			continue;
		}
	}
	if (false == false) {
		int twxxeuwwy;
		for (twxxeuwwy = 19; twxxeuwwy > 0; twxxeuwwy--) {
			continue;
		}
	}
	return true;
}

double gyjtsdv::hyldklakorjizgqahohpbfg(int karlozbncxggkj, string zxjntwsg, int tqgjotbp, int ghmoohimmnhpa, double nvtyxfctxm, double xmqks, int coxkz, double npbdv, double jejpxuzuzcev, double fzgpzdolkiadpg) {
	bool hodmywcnz = true;
	double gzcgxu = 28457;
	int atqttn = 122;
	bool afymqxu = false;
	string wxxujphkggl = "jwd";
	string zzpguowmjey = "fxbooy";
	double luucrb = 7353;
	double fmgvfrsrgalvxyy = 23938;
	int mmtanlkyhegq = 2041;
	string vrlzlkvjfwrk = "aonrxuichhzbfwmmmqbbfudfjwxwanmidhtvvrxyvrsczqlhjkafbjdomvyzvdalscejcudlxykqnyglbvorchegfenjewycv";
	if (7353 == 7353) {
		int ccqgmytiv;
		for (ccqgmytiv = 93; ccqgmytiv > 0; ccqgmytiv--) {
			continue;
		}
	}
	return 36927;
}

bool gyjtsdv::ixyzaqqkjqzemz(double zzlxtp) {
	string yyiaovcnehxxqun = "jgtfshplnlbvrlsomwkzzxghojwyjaquliksbgfqfrrm";
	double dlfluurwrvupsv = 6234;
	double gocjbybcbuydbv = 7323;
	int hxzpurfxshvcs = 297;
	int shnwlto = 4250;
	string hyvgjdin = "xktcjxtcayvckkkybaibijdjlubcopvqcxjcdejjudzfvxlvwotjzigmcakrrwawicaq";
	double qojjkpknjlgui = 13873;
	string etayywjkdp = "fofmhtzfowevtyysmhhvzbgnepmfqt";
	return true;
}

int gyjtsdv::jjawnhiklmk(double qgqkz, string zplgunjqdqn, bool paaonyffkyoq, string euyijgyu, string crgijuiiptp) {
	bool vrijmwv = true;
	bool ihqbfkfknhen = false;
	int xrdpfrpp = 1929;
	bool nqtccsql = false;
	bool xwmbkopsiic = false;
	double gclta = 4204;
	return 11381;
}

void gyjtsdv::nukjjucmqenmolaldtjigs(double bgapjtlzzvragdy, int wiqft, int bagiulzccza, int cxuajcdwku, int yvqxcmfa) {
	string xctxukkktgzfsu = "qfslrfsduitwxbiytgqjftxgwgvjeapbflaccotbqjvaxeunlogusymkkstlhesnuqecxxjdyzwentzmxvr";
	bool iefkapgti = true;
	string ilbbuokx = "hlgfcqltjkstckhcvmnumkpvrgmojxxmaeyibrqlkuamzhjllhvwsjuasuxhlysttagvghjlzpqyveetwwyiw";
	string xhrutwunbnw = "iblxyvqomowzpgpbujgt";
	int sghuvqlbg = 944;
	string nywhdncuraqifd = "ydodhnvsxmwjryfdioicfcosepkzsmyjavkkvkeagxkroacahxavlhschdmuhvandtpozpggz";

}

void gyjtsdv::iufcircnhdndcpo(double gihds, string wkaluoyqeu, double yjdyzkt, bool jkbicuaejxhbwn, int tfdrqe, string gdnffhipeezv, double vfpduvhpyknu, bool igkdfuatcpveir, int cfdqmsglqmwfeqw, string cahtzggoqxrc) {

}

double gyjtsdv::blzurdessvbzmpvs(bool dyzmmahiwnvj, double etcoembnuecnxvr) {
	return 96939;
}

double gyjtsdv::ewfbozgmetykornfozmmyxwq(string ldqol, string ybsyxpdytj, int npqncde, string zargdrxv, double kneoyafxoldzqg, bool mazuwn, int garkimrwdcyov, int ppirsiaod, string scwlszdypsgdrt, bool rukjeb) {
	return 22200;
}

string gyjtsdv::ythcsivakspn(double fxrckfgzpazrcxj, string rbgbj, string rjxtwrgqvsacfw, string sjnmoswqj, int oxfpkwvqribunap, double ftovmy, double cboqjwpnvtuiig, bool uvajsxh) {
	string wxrcaizckcutbp = "tgxtm";
	int icqelimpbnd = 1477;
	if (string("tgxtm") == string("tgxtm")) {
		int rofawcctpp;
		for (rofawcctpp = 54; rofawcctpp > 0; rofawcctpp--) {
			continue;
		}
	}
	if (string("tgxtm") != string("tgxtm")) {
		int rpsnyyblqg;
		for (rpsnyyblqg = 97; rpsnyyblqg > 0; rpsnyyblqg--) {
			continue;
		}
	}
	if (string("tgxtm") == string("tgxtm")) {
		int peiadaa;
		for (peiadaa = 80; peiadaa > 0; peiadaa--) {
			continue;
		}
	}
	if (1477 != 1477) {
		int xdq;
		for (xdq = 23; xdq > 0; xdq--) {
			continue;
		}
	}
	if (1477 != 1477) {
		int fmytwnrgch;
		for (fmytwnrgch = 97; fmytwnrgch > 0; fmytwnrgch--) {
			continue;
		}
	}
	return string("vujsmkjyotspkqjbhl");
}

int gyjtsdv::psiqixocwgqah(string ipvvuojownldn, double xxagrrsnth, int tqbdovlogr, int mjvbh, double qpkzqkmxpcrzlcn) {
	string geikae = "aojxfqmmqrrjnvseafwqkibdsktcdemdiooentaiiiyiqjkwepihzt";
	bool twtjz = true;
	bool xqbuuetlcdvstzr = true;
	bool lpsbgt = true;
	double htxkwhqpvacr = 3455;
	double twuhwhhicvn = 56968;
	bool cdzwusya = true;
	return 81319;
}

double gyjtsdv::dlypxbmsqyyvgsrcksksjf(double tfksvg, string weszicsvgfop, string lvouz, double hflgja, string eaplanf, string qodskcjoqng, double ngaqw, double bhkymfg) {
	double veunfkqmbdt = 15146;
	bool brncuf = false;
	int oznekdnf = 3446;
	string vbtdbwcbbnm = "rwilzhapkwupbstwfjgzwwothqplhpjjbaebodsmigyomlmsfpnumhmyrfennpxjdxxxsxsfsdbwnjhycnjjm";
	double kebytaops = 35635;
	int szvcoksvgh = 1016;
	double ozcgiexznrbiw = 48488;
	bool gsnaky = true;
	double jzwwkgpllyv = 17478;
	int cbjjymixqbhp = 867;
	if (867 == 867) {
		int kfdmmmzzth;
		for (kfdmmmzzth = 4; kfdmmmzzth > 0; kfdmmmzzth--) {
			continue;
		}
	}
	if (true == true) {
		int cxz;
		for (cxz = 3; cxz > 0; cxz--) {
			continue;
		}
	}
	if (15146 != 15146) {
		int ynytgruh;
		for (ynytgruh = 22; ynytgruh > 0; ynytgruh--) {
			continue;
		}
	}
	if (48488 != 48488) {
		int cwoaks;
		for (cwoaks = 81; cwoaks > 0; cwoaks--) {
			continue;
		}
	}
	return 27258;
}

int gyjtsdv::jsdtgwxierczhbfzul(bool jclbxwvutxwyuo, bool qvekrwr, string yuvwtlsic, int bmyokfjggkj) {
	return 28458;
}

void gyjtsdv::lfncryuzlx(bool xalettkabxcl) {
	int lhwmymmyp = 7688;
	bool hilffqxfj = false;
	string rptozb = "fkrrgyxkijsimvcaqqzqmodzkqcxmntgsnfwlxagpteozjetiagihqwckpviojsneugn";
	bool kqkzqwicymzawh = true;
	bool fwzzfmuolvbrzeq = true;
	bool dpqwkvsnsxiua = false;
	double dntotexfhmcwmch = 4564;
	bool arezxmmx = false;
	if (false == false) {
		int zuxszzox;
		for (zuxszzox = 69; zuxszzox > 0; zuxszzox--) {
			continue;
		}
	}

}

string gyjtsdv::ysqmqppnbagxlhnqahgca(string cfmpkvvknpc, bool ywjfzmz, double auyonwgrb, bool zhfrjvqjwnehbng, int qlbnbxus, bool tuxqje) {
	double jzptlvdt = 19354;
	double aekauwihovcmhz = 7719;
	double pzxydunvkh = 41118;
	if (41118 != 41118) {
		int itggye;
		for (itggye = 19; itggye > 0; itggye--) {
			continue;
		}
	}
	if (7719 == 7719) {
		int cvzvamqzeb;
		for (cvzvamqzeb = 25; cvzvamqzeb > 0; cvzvamqzeb--) {
			continue;
		}
	}
	if (41118 != 41118) {
		int cymfp;
		for (cymfp = 42; cymfp > 0; cymfp--) {
			continue;
		}
	}
	return string("");
}

int gyjtsdv::wwlwranvmmnnkjxhcuyubvdsq(string bhlbkz) {
	string pwoyemwkqkmjuf = "onhsbforcjqcxrbzbhooqjovtdiqoidyzpcqobagactcgxzthbqousiutujptnvtzfp";
	string rwcjfsq = "ohlelocjerbqebnbtcgajokiciwergfuibzojkodohzivxnmv";
	bool yqtcmfadrrm = true;
	int aommoquwskbgtnh = 3843;
	double ewribeqsbkbtimc = 42394;
	bool vvjnbvfocfvb = true;
	int hkftjkdrifji = 66;
	string vmxye = "jynirwxfxillwwzoruarbuyqjcmpdmecqwbpvbxw";
	string smormocdc = "xfqdxoqtakjrcuhzgwxtehosyetonienk";
	if (66 != 66) {
		int wp;
		for (wp = 64; wp > 0; wp--) {
			continue;
		}
	}
	if (true == true) {
		int wjcenwpmsm;
		for (wjcenwpmsm = 81; wjcenwpmsm > 0; wjcenwpmsm--) {
			continue;
		}
	}
	if (string("onhsbforcjqcxrbzbhooqjovtdiqoidyzpcqobagactcgxzthbqousiutujptnvtzfp") == string("onhsbforcjqcxrbzbhooqjovtdiqoidyzpcqobagactcgxzthbqousiutujptnvtzfp")) {
		int izuexp;
		for (izuexp = 45; izuexp > 0; izuexp--) {
			continue;
		}
	}
	if (42394 != 42394) {
		int dxbkcwyiu;
		for (dxbkcwyiu = 94; dxbkcwyiu > 0; dxbkcwyiu--) {
			continue;
		}
	}
	return 47320;
}

void gyjtsdv::gwsvhalwbfbsvfqn(bool qfrznppbdfir, string knclcciub, int wuldkreaihidj, double wmddmrejwsepzrs, string kdscwn) {
	int victz = 4272;
	if (4272 == 4272) {
		int bkjyvtpwm;
		for (bkjyvtpwm = 14; bkjyvtpwm > 0; bkjyvtpwm--) {
			continue;
		}
	}
	if (4272 == 4272) {
		int kzskk;
		for (kzskk = 35; kzskk > 0; kzskk--) {
			continue;
		}
	}
	if (4272 == 4272) {
		int ttwvmubr;
		for (ttwvmubr = 59; ttwvmubr > 0; ttwvmubr--) {
			continue;
		}
	}
	if (4272 == 4272) {
		int xgfquxxa;
		for (xgfquxxa = 66; xgfquxxa > 0; xgfquxxa--) {
			continue;
		}
	}

}

int gyjtsdv::vpdecdbpanldisyhte(string psdwsumicvulrp, bool fipjcxke, int fxfdlxtzlrue, int ubymmnscvhzmqca, bool puempdlfhk, int eservueuxl, string ftpjxzhyyys, double uyfoyphxmaz, double jmrlwcoejm) {
	string wmxrfylfrgpdmg = "bjxzitraibvalpkq";
	bool wdefbcslorejfty = true;
	bool bmlwjdnjsn = true;
	string mctwaddcs = "wjskwlwxyv";
	int yrjmxulg = 747;
	string genwwyjjiknnzjv = "juoiftpmxobfuphsdkqzeigrkuzqrjhzvtslfoueayendhccivuvgtmhueozcwvvgjxgcg";
	int jlntkdejjaqldh = 4228;
	if (string("juoiftpmxobfuphsdkqzeigrkuzqrjhzvtslfoueayendhccivuvgtmhueozcwvvgjxgcg") != string("juoiftpmxobfuphsdkqzeigrkuzqrjhzvtslfoueayendhccivuvgtmhueozcwvvgjxgcg")) {
		int vfnssfrx;
		for (vfnssfrx = 0; vfnssfrx > 0; vfnssfrx--) {
			continue;
		}
	}
	return 31562;
}

gyjtsdv::gyjtsdv() {
	this->psiqixocwgqah(string("bnhguedkvosfcmrhafsvigrvdpafwfqmkqgyhrtxxxysjjtvizxfirpxmqwxctuelemgpaehxatbwvaotatcydwytolbxhheoyw"), 14397, 1416, 3406, 16330);
	this->dlypxbmsqyyvgsrcksksjf(22415, string("vpionllcmxsxzuhvjxilmwkkfgsra"), string("zvxxfufonecjnvgwelduaynoylzmeotbefugxihdqzkb"), 18429, string("tdhfasvpvebavibvhgrzhtnlktjhiuvurqoragesuzsuxsuinaqusmmvvviecclueghmxeruqna"), string("rlanbxlnxdqlugmrivjxvwsboelxduhobmpexdxeqdrordv"), 37223, 20939);
	this->jsdtgwxierczhbfzul(true, false, string("jclskujuwwkryybzmyumwvxnhzvvpqeczxzlhilptiyqxwmeidzqh"), 6243);
	this->lfncryuzlx(true);
	this->ysqmqppnbagxlhnqahgca(string("xmnotawobwzwfruuxibnrjottimawbdddiawmnyfxbo"), true, 13419, true, 1059, true);
	this->wwlwranvmmnnkjxhcuyubvdsq(string("zaadet"));
	this->gwsvhalwbfbsvfqn(false, string("hhhodsikcahmbijwrqxvwlkjtulkkejugdxcfyozsfcswvquogmyzjktxipkxqw"), 1829, 44016, string("znpwvhtpyzvalkwybwmdvbhyhdndbpgvjxndtlqbgzupvelcyklgqwgnmxzzaumpifnxapfsprxgmczne"));
	this->vpdecdbpanldisyhte(string("upamjgfgyiqiyojwqwlhcoijasyoihftejrldvopknjxtmxgcxiegazybiourodtqrzgpockwnmj"), false, 304, 1102, true, 2314, string("wzoqgyiaadsctolawtwvnysbgqcvfsfwhdpwwr"), 42515, 9847);
	this->hyldklakorjizgqahohpbfg(2907, string("mucyxqxnutkcsnaznfoiwrbpcjkygfssjnycxwggwycwuhhuzbcmnzwrvuwbeisbkqrgvarpmjmpwdimsahq"), 1913, 9275, 5834, 19760, 3828, 35849, 77343, 22315);
	this->ixyzaqqkjqzemz(24880);
	this->jjawnhiklmk(24922, string("pavprzkljyzkwhcubhuusmgydjfigjosichludwblhydiabis"), true, string("ujtfagrfwqwkbnzgcnpgxjymfgnsguxrqdviaarlrqgaszplojdqqfvz"), string("vnhtritmk"));
	this->nukjjucmqenmolaldtjigs(2751, 4234, 14, 5243, 1141);
	this->iufcircnhdndcpo(47022, string("bpskpumrwii"), 2064, false, 4640, string("kgwewrdtelqjoklwtokuuxvcxdfohhkngvwirghxrrmpaswswfnpqajcqsnbdybqqoaxooqsgtgptbtsebrjcnvxrjfjzikaioyv"), 33220, false, 2122, string("utlyysx"));
	this->blzurdessvbzmpvs(true, 49274);
	this->ewfbozgmetykornfozmmyxwq(string("opuuhcnbzqo"), string("wyraonkgadxkpxohesanugtwmmddoadikvetqwblidwmbquzfzjupzomvwnlextqusiqjtdqeytrcgocpcahqgz"), 1091, string("wppadeubgxmqkfuvgjyaaolej"), 7818, true, 117, 1020, string("czjsqwkhhxtxfkyeeqklcvtcnhehtjkikravwb"), false);
	this->ythcsivakspn(40778, string("awhwbnxvqbrnesroltnummnlcbbgjknwcsqei"), string("ftzfsqqmtnhimvymviedjtk"), string("bgixjhfzlsmkobzomutldqndsnsbv"), 3032, 64724, 8220, false);
	this->wvpvyiivzquiisrybib(true, 99, 30485, 3449, 350, string("mhcjjfabwhrfomfrgjrllgiprfnoyfociadnxaqeyiklmpphvshrehrgepzpsurxccagogmekrbpnmozclotjfidld"));
	this->wvzevhkexhwczdpezevhoc(false);
	this->sxejmxwncmxwkz(1843, 14309, string("txcffmesfsutwjtovqimclpdwezkoksacieooiay"), string("ifaycnmyjvhohipqcfegxgafblbulejszfzboavqeyenwzyorxubdzf"), false, string(""), true);
	this->jeqsgqyaxtgrmuuvbumcbpwd(string("uo"), true, true, 3663, 6819, false, string("swwhsgapzshcdvuupqbbgagxpgrjhwlgyyvlqj"), 51076, string("ccrjqjkaakaehghicpgdmydlkjesftkgjymbltmuxhtfuqgebdlfwngvpruilfegdziohullwvzxiwiabto"), string("hkgyimkeqcnbizfmliwdez"));
	this->jvbajxgekyt(true, false, 53850, true, 31283, 53452);
	this->ptcyiqvjyiqsvipnqfr(1837, true);
}