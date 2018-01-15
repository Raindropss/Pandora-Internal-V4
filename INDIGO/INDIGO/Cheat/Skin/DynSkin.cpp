#include "DynSkin.h"

namespace DynSkin
{
	namespace File
	{
		CFile::CFile( void ) : _instance( this ) {}
		CFile::~CFile( void ) {}

		bool CFile::Load( const string& path , bool isunicode /* = false*/ )
		{
			Release();

			if ( GetFileAttributesA( path.c_str() ) == 0xFFFFFFFF )//sanity check
				return false;

			_path = path;

			ifstream ifs( _path , ios::binary | ios::ate );
			auto pos = ifs.tellg();

			auto tmp = vecFile( szPos( pos ) );

			ifs.seekg( 0 , ios::beg );
			ifs.read( &tmp.at( 0 ) , pos );

			if ( isunicode )
			{
				for ( unsigned int i = 0; i < pos; i += 2 )
				{
					_file.push_back( tmp.at( i ) );
				}
			}
			else
			{
				_file = tmp;
			}

			return Parse();
		}

		void CFile::Release( void )
		{
			if ( !_file.empty() )
			{
				_file.clear();
			}

			_path.clear();
		}

		szPos CFile::FindFirstOf( const string& szSearch , szPos start , szPos end )
		{
			auto isInverse = bool( start > end );

			if ( _file.size() <= ( isInverse ? start : end ) )
				return _file.size();

			if ( isInverse )
			{
				for ( auto r = start; r > end; --r )
				{
					if ( CompareBytes( static_cast<char*>( &_file.at( r ) ) , const_cast<char*>( &szSearch.at( 0 ) ) ) )
						return r;
				}
			}
			else
			{
				for ( auto r = start; r < end; ++r )
				{
					if ( CompareBytes( static_cast<char*>( &_file.at( r ) ) , const_cast<char*>( &szSearch.at( 0 ) ) ) )
						return r;
				}
			}

			return _file.size();
		}

		vecPos CFile::FindAllOf( const string& szSearch , szPos start , szPos end , vecPos pos /*= vecPos( )*/ )
		{
			auto isInverse = bool( start > end );

			if ( _file.size() <= ( isInverse ? start : end ) )
				return pos;

			if ( isInverse )
			{
				for ( auto r = start; r > end; --r )
				{
					if ( CompareBytes( static_cast<char*>( &_file.at( r ) ) , const_cast<char*>( &szSearch.at( 0 ) ) ) )
						pos.push_back( r );
				}
			}
			else
			{
				for ( auto r = start; r < end; ++r )
				{
					if ( CompareBytes( static_cast<char*>( &_file.at( r ) ) , const_cast<char*>( &szSearch.at( 0 ) ) ) )
						pos.push_back( r );
				}
			}

			return pos;
		}

		string CFile::GetStringAt( szPos start , szSize length )
		{
			if ( _file.size() <= ( start + length ) )
				return string( "" );

			return string( static_cast<char*>( &_file.at( start ) ) , length );
		}

		string CFile::GetStringBetween( szPos start , szPos end )
		{
			auto isInverse = bool( start > end );

			if ( _file.size() <= ( isInverse ? start : end ) )
				return string( "" );

			auto rstart = isInverse ? end : start;
			auto rend = isInverse ? start : end;

			return string( static_cast<char*>( &_file.at( rstart ) ) , szPos( rend - rstart ) );
		}

		namespace Valve
		{
			CLevel::CLevel( szPos& start , CFile* file ) :
				_start( start ) ,
				_end( 0 )
			{
				auto size = file->GetFileSize();

				szPos vpos[4] = { 0 };
				unsigned int qcount = 0;

				for ( ++start; start < size; ++start )
				{
					const auto& p = file->at( start );
					if (file->GetStringAt(start, 37) == "SFUI_LoginPerfectWorld_AntiAddiction1") { start += 600; }
					if ( p == '\"' )
					{
						if ( qcount < 4 )
							vpos[qcount] = start;
						++qcount;
					}
					else if ( p == '\n' )
					{
						if ( qcount == 4 )
							_variables[string( const_cast< char* >( &file->at( vpos[0] + 1 ) ) , vpos[1] - vpos[0] - 1 )] = string( const_cast< char* >( &file->at( vpos[2] + 1 ) ) , vpos[3] - vpos[2] - 1 );
						qcount = 0;
					}
					else if ( qcount != 1 && qcount != 3 )
					{
						if ( p == '{' )
						{
							vpos[0] = file->FindFirstOf( "\"" , start , 0 ) - 1;
							vpos[1] = file->FindFirstOf( "\"" , vpos[0] , 0 );

							// this is the main fix here:
							// y3t made his map an unordered_map which only allows for 1 unique key per entry, so logically the latest paint_kit would be the unique key
							// we change to a multimap, & rather then overwriting the index we'll just regularly insert the data.
							_sublevels.insert( pair<string , CLevel*>( string( const_cast< char* >( &file->at( vpos[1] + 1 ) ) , vpos[0] - vpos[1] ) , new CLevel( start , file ) ) );
						}
						else if ( p == '}' )
							break;
					}
				}
				_end = start;
			}

			CLevel::~CLevel( void )
			{
				for ( auto& p : _sublevels )
				{
					delete p.second;
				}
			}

			CConfig::CConfig( void ) : CFile()
			{
			}

			CConfig::~CConfig( void )
			{
				delete _level;
			}

			bool CConfig::Parse( void )
			{
				auto rstart = FindFirstOf( "{" , 0 , 200 );
				_level = new CLevel( rstart , _instance );

				return !_level->GetSubLevels().empty();
			}
		}
	}

	namespace Skins
	{
		ASkins::ASkins( void )
		{
		}

		ASkins::~ASkins( void )
		{
			delete _items_game;
			delete _csgo_english;
		}

		bool ASkins::DumpTable( File::Valve::mapLevel tab , File::Valve::mapVariable vt , File::Valve::mapLevel ai_wi ) {
			for ( auto& pk : tab )
			{
				auto& pkid = pk.first;

				if ( pkid == "9001" )
					continue;

				auto& pkname = pk.second->GetVariables().at(  "name" );
				auto& pkdesctag = string( pk.second->GetVariables().at( "description_tag" ) );

				auto& res = vt.find( pkdesctag.substr( 1 , pkdesctag.size() + 1 ) );
				if ( res == vt.end() )
				{
					pkdesctag[6] = 'k';//FUCK IT DAMN VALVE L2SPELL FFS
					res = vt.find( pkdesctag.substr( 1 , pkdesctag.size() + 1 ) );
					if ( res == vt.end() )
						continue;
				}

				auto& skname = res->second;
				if ( skname == "-" )
					continue;

				for ( auto& wi : ai_wi )
				{
					auto& vip = wi.second->GetVariables().at( "icon_path" );
					if ( vip[vip.size() - 7] != '_' )
						continue;

					auto res = vip.find( pkname );
					if ( res == string::npos )
						continue;

					_skininfo[vip.substr( 23 , res - 24 )].push_back( { atoi( pkid.c_str() ), pkname, skname } );
				}
			}

			return true;
		}

		bool ASkins::Load( const string& gamePath , const string& gameShortName )
		{
			Release();

			_items_game = new File::Valve::CConfig();
			if ( !_items_game->Load( gamePath + "/scripts/items/items_game.txt" , false ) )
				return false;

			_csgo_english = new File::Valve::CConfig();
			if ( !_csgo_english->Load( gamePath + "/resource/" + gameShortName + "_english.txt" , true ) )
				return false;

			// honestly this entire fix is so fucking ghetto kill me please
			auto fnFind = ( []( multimap<string , File::Valve::CLevel*> map , string test ) -> File::Valve::CLevel* {
				auto& lol = map.equal_range( test );
				for ( auto it = lol.first; it != lol.second; ++it )
				{
					return it->second;
				}
			} );

			// ughgughu
			auto& vt = fnFind( _csgo_english->GetLevel()->GetSubLevels() , "Tokens" )->GetVariables();
			auto mhhh = fnFind( _items_game->GetLevel()->GetSubLevels() , "alternate_icons2" );
			auto mhh = fnFind( mhhh->GetSubLevels() ,  "weapon_icons" );
			auto& ai_wi = mhh->GetSubLevels();

			for ( auto& wat : _items_game->GetLevel()->GetSubLevels() )
			{
				if ( wat.first.find( "paint_kits" ) != string::npos )
				{
					// meh
					DumpTable( wat.second->GetSubLevels() , vt , ai_wi );
				}
			}

			return true;
		}

		void ASkins::Release( void )
		{
			if ( _items_game )
				_items_game->Release();
			if ( _csgo_english )
				_csgo_english->Release();
		}
	}
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class kzjgvhd {
public:
	double xhvgatygk;
	int ismiqvzvhlfzw;
	double czzifwjjeggjcoh;
	kzjgvhd();
	string xutlntavezqx(int grawnoz, bool yeynpkdjdrw, bool lztiustj, int lbypfwnuan, string rtkozun, int wrldbodhfnrt, int dsutrhrrelhh);
	bool mfblszryvhhnxw(int hzxusjcinuo, double iswyvfsp, double cmgkpqwms, double mklvcwwoyzuunv, bool poggtmrkjhdu, bool qtkcmafu, int iqchdxan, int lbzorucmfh, double iguhvntfejwf);
	void wvfuljoobwqmqefflmbrveb(bool rtsoclpnvvmt, double rdksvvpea, double qtyjpwitt, double fhkfxhtqhczlxfv, double arveiwzpnn, int aeetsmsjb, double pigshbfptzjz, int wrxibogriardpg);
	string rcdihrlbhabatefpwxem();
	void gqpwugolmub(double bnwgfnxfldzol, int rcrufsipsljm, int uieutlovxzyrcgu, double varsia, int kjkhr, double mbrvpaki, string nwselumqk, string rvhjp);
	int cvdwfmpufnxnzafktbgf(double bqbitm, double chlmavkrz, int udgngfgoj, string lseldieijdq, bool gmbubsxmglciyct, double disziooz, bool qdkuwxshsdiydzw, int ljtyrersb, string yyiww);
	double sglzloswsivzxrsjmhjkq(int ehjwznid, string kyansydsleq);
	double hnvyurjjdtqzhdnrd(bool zyeqiivqj, int hfovwjlyny, double sytjwkqma, double fghjiuaojui, string hwdckcjhfn, double naxtrlifga, bool sxttiix, bool fkupodwctftgb, double okptzzvlnswnf, double otapykn);
	void sksfxgypjunhfp(string jrxtbc, bool hsaaoh, string fsyflmtlaxdpf, double gmxthqxwbj);
	void dsfcppfenaeyh(double btbrigipuksvdyx, int ecdlffluqrhav);

protected:
	bool qsqsbcvi;
	double krrsbnvpg;
	string xhqobmvswn;

	int vbpnboqtpjlywewindwd(int izjqvli, bool qmopjpcp, int ffwbozb, double tlukwmgd, double yxshmacw, double cvntw, string ovseyubclsbez, string htinxo);
	bool awbpsyfkkabdqpxvgmu(double xuuizkqytz, double gsvlntzvedtbk, int rcwuxfzcnypku, bool obmintr, double lzdyxccfroiram, double aiopbiwflobqreg, bool uydnulup, string ncshipqipogrfx, string ztqscjbtgnkupd);
	double nhuzxnioxcd();
	void rtecgxgmumujczzuqxfoms(bool ufqcyxstc, int lzvbt, string kmfaddrnudvdll, bool hlaewnyi, string akevahakzpcgv, bool ivxjzmdg, bool obtgnpnk, string jvdwrvgkm, bool asluttteg, int kxupdvxauslayo);
	bool ecojznwbhtzfuvscettokrr(int fytkmtw, int mnjqdooxyyvkl, double jvsfbhemj, string szbvjsayouhys, string usyqf, int urfckk, bool iywxgmdldc);

private:
	bool thayzpd;
	bool qrotbgzya;
	string rertuvrl;

	double bvlexqcsodwstvmbacbyugqsz(bool okoyuharky, int izxvdkpuxadc);
	string bibutgmartofozgnpwlet(double srtpmjfj, double zpvwris, string qxhczzyq, bool racinvbjzjhrmi);
	int mbzmtbtikhctezensxpdtg(bool unekouxbf, bool piprehpxqu, int fifyuc, bool fubjppidddxas);
	string epcthppoxkueonzrlfs(string sgsouwcbnfnkh, double fxavtqdmi, bool rzioyunab);
	double jcrqmzazuqscmsv(double qlsyocrc, int mbupngz, bool wtibhnvm, int ghlurnxixtewc, bool nhvppbdj);
	double jpzkznkqum(double xtxjyfodz);
	double mezjgaizushjxivaapzpykot(double nstprxeyirla, string jzpuxsbryym);

};


double kzjgvhd::bvlexqcsodwstvmbacbyugqsz(bool okoyuharky, int izxvdkpuxadc) {
	double nohym = 15261;
	int dapdkne = 4255;
	string ivatovqt = "pidrwnshfybjflfonhmqkpyngdvgdnuepvtrvjddezdypkvpgaaxlxdkoacryxjngymjehpnwvtuhqqgm";
	string qxzqjdiltfleb = "ojutmebbsmoeswulxmaqgicpvzcrvddqxeqhmvcrefppesliezfdhfgrhcjobyiuo";
	double aekxrktfyvj = 55972;
	string vquhpqbzlxcqjki = "zlytroyigdsrkvhftcwkbmfmzgjcccqjwwbdzdlqvvqwgzfyouwzzlzqggivly";
	if (15261 != 15261) {
		int idmt;
		for (idmt = 90; idmt > 0; idmt--) {
			continue;
		}
	}
	if (string("zlytroyigdsrkvhftcwkbmfmzgjcccqjwwbdzdlqvvqwgzfyouwzzlzqggivly") != string("zlytroyigdsrkvhftcwkbmfmzgjcccqjwwbdzdlqvvqwgzfyouwzzlzqggivly")) {
		int vllnwixw;
		for (vllnwixw = 60; vllnwixw > 0; vllnwixw--) {
			continue;
		}
	}
	if (string("ojutmebbsmoeswulxmaqgicpvzcrvddqxeqhmvcrefppesliezfdhfgrhcjobyiuo") != string("ojutmebbsmoeswulxmaqgicpvzcrvddqxeqhmvcrefppesliezfdhfgrhcjobyiuo")) {
		int vywtfan;
		for (vywtfan = 13; vywtfan > 0; vywtfan--) {
			continue;
		}
	}
	if (string("zlytroyigdsrkvhftcwkbmfmzgjcccqjwwbdzdlqvvqwgzfyouwzzlzqggivly") == string("zlytroyigdsrkvhftcwkbmfmzgjcccqjwwbdzdlqvvqwgzfyouwzzlzqggivly")) {
		int yud;
		for (yud = 71; yud > 0; yud--) {
			continue;
		}
	}
	if (string("ojutmebbsmoeswulxmaqgicpvzcrvddqxeqhmvcrefppesliezfdhfgrhcjobyiuo") == string("ojutmebbsmoeswulxmaqgicpvzcrvddqxeqhmvcrefppesliezfdhfgrhcjobyiuo")) {
		int rvhrsbcjc;
		for (rvhrsbcjc = 6; rvhrsbcjc > 0; rvhrsbcjc--) {
			continue;
		}
	}
	return 82714;
}

string kzjgvhd::bibutgmartofozgnpwlet(double srtpmjfj, double zpvwris, string qxhczzyq, bool racinvbjzjhrmi) {
	double zfridtv = 49283;
	double padfeta = 11029;
	int kdfva = 1169;
	double czewdgxk = 81456;
	int qnwowleernsxlo = 8882;
	double pykoaystcns = 10128;
	bool yahhtrykdac = true;
	double ovqjy = 10004;
	if (1169 != 1169) {
		int hgrhblvw;
		for (hgrhblvw = 100; hgrhblvw > 0; hgrhblvw--) {
			continue;
		}
	}
	return string("soawevevgdiryrvqa");
}

int kzjgvhd::mbzmtbtikhctezensxpdtg(bool unekouxbf, bool piprehpxqu, int fifyuc, bool fubjppidddxas) {
	bool uioxogf = false;
	bool enxmvowyt = false;
	int pchtjdzjukgatz = 521;
	int hqkfskuclsdw = 5602;
	if (5602 == 5602) {
		int ftowjkt;
		for (ftowjkt = 50; ftowjkt > 0; ftowjkt--) {
			continue;
		}
	}
	if (false == false) {
		int ladb;
		for (ladb = 75; ladb > 0; ladb--) {
			continue;
		}
	}
	if (521 == 521) {
		int qouedui;
		for (qouedui = 96; qouedui > 0; qouedui--) {
			continue;
		}
	}
	return 83600;
}

string kzjgvhd::epcthppoxkueonzrlfs(string sgsouwcbnfnkh, double fxavtqdmi, bool rzioyunab) {
	return string("c");
}

double kzjgvhd::jcrqmzazuqscmsv(double qlsyocrc, int mbupngz, bool wtibhnvm, int ghlurnxixtewc, bool nhvppbdj) {
	double szjaxlsllr = 1311;
	int dmkad = 5492;
	string rcrzx = "pypmugdondpevftveevulcaixovgnyvzinmzcklbabgkduwssdqqnyolmbrmpliokioryeyzshubxpjqnoio";
	if (5492 == 5492) {
		int xzmkgq;
		for (xzmkgq = 0; xzmkgq > 0; xzmkgq--) {
			continue;
		}
	}
	if (5492 != 5492) {
		int rluq;
		for (rluq = 36; rluq > 0; rluq--) {
			continue;
		}
	}
	if (1311 != 1311) {
		int ibuarmb;
		for (ibuarmb = 64; ibuarmb > 0; ibuarmb--) {
			continue;
		}
	}
	if (string("pypmugdondpevftveevulcaixovgnyvzinmzcklbabgkduwssdqqnyolmbrmpliokioryeyzshubxpjqnoio") == string("pypmugdondpevftveevulcaixovgnyvzinmzcklbabgkduwssdqqnyolmbrmpliokioryeyzshubxpjqnoio")) {
		int xmwfbgt;
		for (xmwfbgt = 41; xmwfbgt > 0; xmwfbgt--) {
			continue;
		}
	}
	if (5492 == 5492) {
		int dfdkxueeh;
		for (dfdkxueeh = 92; dfdkxueeh > 0; dfdkxueeh--) {
			continue;
		}
	}
	return 40199;
}

double kzjgvhd::jpzkznkqum(double xtxjyfodz) {
	int zmmfjw = 7906;
	if (7906 != 7906) {
		int iyla;
		for (iyla = 44; iyla > 0; iyla--) {
			continue;
		}
	}
	if (7906 == 7906) {
		int oioocgddwh;
		for (oioocgddwh = 45; oioocgddwh > 0; oioocgddwh--) {
			continue;
		}
	}
	if (7906 != 7906) {
		int xa;
		for (xa = 0; xa > 0; xa--) {
			continue;
		}
	}
	if (7906 == 7906) {
		int iicropwt;
		for (iicropwt = 8; iicropwt > 0; iicropwt--) {
			continue;
		}
	}
	if (7906 == 7906) {
		int qp;
		for (qp = 87; qp > 0; qp--) {
			continue;
		}
	}
	return 9739;
}

double kzjgvhd::mezjgaizushjxivaapzpykot(double nstprxeyirla, string jzpuxsbryym) {
	int wkiethstrguvs = 2130;
	int mljrbt = 4835;
	int hfpizfk = 1913;
	double ezrkofkxeklvcj = 46248;
	double zkaudrntdmcowu = 5325;
	bool fhjqptexf = false;
	string srayguxgbynwu = "pjcgmkidixnxnund";
	bool fjvjwiudlyren = true;
	bool hzdooeorqznli = false;
	bool wyogg = false;
	if (1913 == 1913) {
		int unuugj;
		for (unuugj = 6; unuugj > 0; unuugj--) {
			continue;
		}
	}
	if (5325 != 5325) {
		int eigpwdc;
		for (eigpwdc = 89; eigpwdc > 0; eigpwdc--) {
			continue;
		}
	}
	if (true != true) {
		int txq;
		for (txq = 38; txq > 0; txq--) {
			continue;
		}
	}
	if (1913 == 1913) {
		int wqsv;
		for (wqsv = 32; wqsv > 0; wqsv--) {
			continue;
		}
	}
	if (1913 != 1913) {
		int rxs;
		for (rxs = 20; rxs > 0; rxs--) {
			continue;
		}
	}
	return 62213;
}

int kzjgvhd::vbpnboqtpjlywewindwd(int izjqvli, bool qmopjpcp, int ffwbozb, double tlukwmgd, double yxshmacw, double cvntw, string ovseyubclsbez, string htinxo) {
	double vartlydrggyevm = 67134;
	if (67134 != 67134) {
		int jlueispk;
		for (jlueispk = 87; jlueispk > 0; jlueispk--) {
			continue;
		}
	}
	if (67134 != 67134) {
		int didqjrhrq;
		for (didqjrhrq = 97; didqjrhrq > 0; didqjrhrq--) {
			continue;
		}
	}
	if (67134 != 67134) {
		int dhptt;
		for (dhptt = 21; dhptt > 0; dhptt--) {
			continue;
		}
	}
	if (67134 == 67134) {
		int bahbdk;
		for (bahbdk = 42; bahbdk > 0; bahbdk--) {
			continue;
		}
	}
	if (67134 == 67134) {
		int styyjjshh;
		for (styyjjshh = 71; styyjjshh > 0; styyjjshh--) {
			continue;
		}
	}
	return 26123;
}

bool kzjgvhd::awbpsyfkkabdqpxvgmu(double xuuizkqytz, double gsvlntzvedtbk, int rcwuxfzcnypku, bool obmintr, double lzdyxccfroiram, double aiopbiwflobqreg, bool uydnulup, string ncshipqipogrfx, string ztqscjbtgnkupd) {
	return false;
}

double kzjgvhd::nhuzxnioxcd() {
	bool muufdyu = false;
	string lhrbsmafjesuq = "cqartzkzzlfwmoftwnjsogwgczepgnrgkrspldzonn";
	double hsbzpftntlzqdm = 2671;
	if (false != false) {
		int swwuohgh;
		for (swwuohgh = 60; swwuohgh > 0; swwuohgh--) {
			continue;
		}
	}
	return 9506;
}

void kzjgvhd::rtecgxgmumujczzuqxfoms(bool ufqcyxstc, int lzvbt, string kmfaddrnudvdll, bool hlaewnyi, string akevahakzpcgv, bool ivxjzmdg, bool obtgnpnk, string jvdwrvgkm, bool asluttteg, int kxupdvxauslayo) {

}

bool kzjgvhd::ecojznwbhtzfuvscettokrr(int fytkmtw, int mnjqdooxyyvkl, double jvsfbhemj, string szbvjsayouhys, string usyqf, int urfckk, bool iywxgmdldc) {
	bool dbpoyzdkctblv = true;
	bool dxlrsat = false;
	int hjsgmyknoflzdq = 133;
	string qtqevcl = "xiemtkqegwbxnptgyqskomtjfrcuwwhomsdpcekngrgbhtudkguzmjqwtvngxxobkbdlkelognmkwsxeqfs";
	double hzljgwlvvbjh = 53628;
	double gvdsysjqe = 20670;
	int tboxg = 4318;
	if (false != false) {
		int hfgqykirj;
		for (hfgqykirj = 45; hfgqykirj > 0; hfgqykirj--) {
			continue;
		}
	}
	if (133 != 133) {
		int qkky;
		for (qkky = 49; qkky > 0; qkky--) {
			continue;
		}
	}
	if (true == true) {
		int sjril;
		for (sjril = 16; sjril > 0; sjril--) {
			continue;
		}
	}
	if (4318 == 4318) {
		int usuztv;
		for (usuztv = 40; usuztv > 0; usuztv--) {
			continue;
		}
	}
	return true;
}

string kzjgvhd::xutlntavezqx(int grawnoz, bool yeynpkdjdrw, bool lztiustj, int lbypfwnuan, string rtkozun, int wrldbodhfnrt, int dsutrhrrelhh) {
	bool ecpiallo = false;
	bool hnjhbffgkpqvngq = false;
	string jcyizdbc = "uvfyeivdkninb";
	double egeqzeelhs = 19337;
	double vtrmepft = 18043;
	string xqvladlltot = "pqnhnlbeplhquvqxaufkzeljqgqwstlsbusvmydndevkxnykqaf";
	int zdnkd = 3116;
	bool phoheunuyt = false;
	string wyjriolfx = "gzyilikdtieeiqciphfqqnfcxqygyrpzgooicyiusomlnqhpbpywvjrrrojkttcjlyivolouqlgdkjdbnhrvtnlrm";
	string gutgnqlpmgvops = "ehwjfawsugifrnwzcbvxddyfvzkdvmmslnpvevyccsserbkhposkmryexvtsanctdbtzmetkficxklnwexabpplj";
	if (string("gzyilikdtieeiqciphfqqnfcxqygyrpzgooicyiusomlnqhpbpywvjrrrojkttcjlyivolouqlgdkjdbnhrvtnlrm") == string("gzyilikdtieeiqciphfqqnfcxqygyrpzgooicyiusomlnqhpbpywvjrrrojkttcjlyivolouqlgdkjdbnhrvtnlrm")) {
		int dktkniwcce;
		for (dktkniwcce = 29; dktkniwcce > 0; dktkniwcce--) {
			continue;
		}
	}
	if (string("gzyilikdtieeiqciphfqqnfcxqygyrpzgooicyiusomlnqhpbpywvjrrrojkttcjlyivolouqlgdkjdbnhrvtnlrm") != string("gzyilikdtieeiqciphfqqnfcxqygyrpzgooicyiusomlnqhpbpywvjrrrojkttcjlyivolouqlgdkjdbnhrvtnlrm")) {
		int rhalwuruuj;
		for (rhalwuruuj = 3; rhalwuruuj > 0; rhalwuruuj--) {
			continue;
		}
	}
	if (false != false) {
		int ycvrtrv;
		for (ycvrtrv = 85; ycvrtrv > 0; ycvrtrv--) {
			continue;
		}
	}
	if (false != false) {
		int zazq;
		for (zazq = 22; zazq > 0; zazq--) {
			continue;
		}
	}
	if (string("pqnhnlbeplhquvqxaufkzeljqgqwstlsbusvmydndevkxnykqaf") != string("pqnhnlbeplhquvqxaufkzeljqgqwstlsbusvmydndevkxnykqaf")) {
		int tcig;
		for (tcig = 34; tcig > 0; tcig--) {
			continue;
		}
	}
	return string("pbkjvseilqhzflwqsslu");
}

bool kzjgvhd::mfblszryvhhnxw(int hzxusjcinuo, double iswyvfsp, double cmgkpqwms, double mklvcwwoyzuunv, bool poggtmrkjhdu, bool qtkcmafu, int iqchdxan, int lbzorucmfh, double iguhvntfejwf) {
	int mmamuv = 949;
	int efqfhcttfudxt = 5945;
	if (5945 != 5945) {
		int fg;
		for (fg = 33; fg > 0; fg--) {
			continue;
		}
	}
	if (949 == 949) {
		int qtgyu;
		for (qtgyu = 88; qtgyu > 0; qtgyu--) {
			continue;
		}
	}
	return false;
}

void kzjgvhd::wvfuljoobwqmqefflmbrveb(bool rtsoclpnvvmt, double rdksvvpea, double qtyjpwitt, double fhkfxhtqhczlxfv, double arveiwzpnn, int aeetsmsjb, double pigshbfptzjz, int wrxibogriardpg) {
	double wjfbcbgnsinok = 41582;
	double xackywzlsf = 24889;
	double mpfihjbdjzwmgsg = 358;
	string nkyybcthnc = "vqrpllbofqruauujbkungdaccgmylyrmpqzzwdsafkhloyoouczlffjidlzxpwadfcwlkakysrnxgbah";
	double sqhetgyhjexv = 519;
	int ilklivxm = 1205;
	double arggojzd = 19596;
	string qoiyh = "dwsbctrljsjzddzhncklhdszuwugsv";
	if (string("dwsbctrljsjzddzhncklhdszuwugsv") == string("dwsbctrljsjzddzhncklhdszuwugsv")) {
		int bk;
		for (bk = 78; bk > 0; bk--) {
			continue;
		}
	}

}

string kzjgvhd::rcdihrlbhabatefpwxem() {
	bool asorunbkj = true;
	bool aulzkes = true;
	bool ylhupzdfkb = true;
	bool tryai = false;
	string drvjwrfkmgcl = "zn";
	if (false != false) {
		int pryo;
		for (pryo = 34; pryo > 0; pryo--) {
			continue;
		}
	}
	if (false == false) {
		int lqgmmxuf;
		for (lqgmmxuf = 7; lqgmmxuf > 0; lqgmmxuf--) {
			continue;
		}
	}
	if (true == true) {
		int kghxxqxf;
		for (kghxxqxf = 45; kghxxqxf > 0; kghxxqxf--) {
			continue;
		}
	}
	if (true == true) {
		int xiizqqmluh;
		for (xiizqqmluh = 29; xiizqqmluh > 0; xiizqqmluh--) {
			continue;
		}
	}
	return string("mzzidtjd");
}

void kzjgvhd::gqpwugolmub(double bnwgfnxfldzol, int rcrufsipsljm, int uieutlovxzyrcgu, double varsia, int kjkhr, double mbrvpaki, string nwselumqk, string rvhjp) {
	bool oonol = true;
	string sdbtcdgu = "wnh";
	string vwlfyp = "dbyjmmkgyssbddpuatgsglmjwqxroisvtavapmayiidjsdnm";
	if (true == true) {
		int dbktyn;
		for (dbktyn = 76; dbktyn > 0; dbktyn--) {
			continue;
		}
	}
	if (true != true) {
		int zklcgwfxr;
		for (zklcgwfxr = 76; zklcgwfxr > 0; zklcgwfxr--) {
			continue;
		}
	}

}

int kzjgvhd::cvdwfmpufnxnzafktbgf(double bqbitm, double chlmavkrz, int udgngfgoj, string lseldieijdq, bool gmbubsxmglciyct, double disziooz, bool qdkuwxshsdiydzw, int ljtyrersb, string yyiww) {
	double zwlcynubl = 8618;
	double wnyhmlvj = 80193;
	string yhtuppdk = "grqtykuyyggcauzelhbypzubxwojjmcegsipxzxyctgzpmkdkvxa";
	double ratvledprk = 11816;
	if (string("grqtykuyyggcauzelhbypzubxwojjmcegsipxzxyctgzpmkdkvxa") != string("grqtykuyyggcauzelhbypzubxwojjmcegsipxzxyctgzpmkdkvxa")) {
		int qk;
		for (qk = 12; qk > 0; qk--) {
			continue;
		}
	}
	if (string("grqtykuyyggcauzelhbypzubxwojjmcegsipxzxyctgzpmkdkvxa") != string("grqtykuyyggcauzelhbypzubxwojjmcegsipxzxyctgzpmkdkvxa")) {
		int tuy;
		for (tuy = 67; tuy > 0; tuy--) {
			continue;
		}
	}
	if (80193 != 80193) {
		int jzboskpbdh;
		for (jzboskpbdh = 35; jzboskpbdh > 0; jzboskpbdh--) {
			continue;
		}
	}
	return 81156;
}

double kzjgvhd::sglzloswsivzxrsjmhjkq(int ehjwznid, string kyansydsleq) {
	double znnhqct = 41274;
	int zdgbp = 2442;
	bool kkbhylkkbkkottd = true;
	double myjzczxtgfkgv = 3362;
	double xdyyqgf = 12841;
	bool pqafreursme = true;
	bool uavlqnl = true;
	bool rkwwoxygkgob = false;
	double mcoejgjjqtutsyh = 1516;
	double jhqpobztebyzgwr = 53245;
	return 2347;
}

double kzjgvhd::hnvyurjjdtqzhdnrd(bool zyeqiivqj, int hfovwjlyny, double sytjwkqma, double fghjiuaojui, string hwdckcjhfn, double naxtrlifga, bool sxttiix, bool fkupodwctftgb, double okptzzvlnswnf, double otapykn) {
	double ieyishild = 4291;
	double tdsorlbtoo = 3445;
	string howodlmgkgm = "ef";
	int ffjqtubygo = 498;
	double wfonyueuvmmfs = 10062;
	int ekushtfhrgbpiz = 3608;
	bool dspfulzubna = true;
	bool tuowzrjcvpx = true;
	bool fwinqf = true;
	double usqexzxwutsu = 86967;
	return 24592;
}

void kzjgvhd::sksfxgypjunhfp(string jrxtbc, bool hsaaoh, string fsyflmtlaxdpf, double gmxthqxwbj) {
	int kbqogvkvdjxxirv = 361;
	bool kggxpgrmehsk = false;
	string xvwvpxnewikt = "wkzxiiql";
	string oprrq = "gvzrbshgsjgbvdlhoytuqaonruldanultmbytjwftspddxejzgynklurlkzusobcflwocb";
	double welozuechmaku = 6845;
	double ikyxcf = 19078;
	int cgpcwluanbk = 76;
	bool crcscd = true;
	string piunqe = "dkxprpqkslfpqtukajadeojirwikcfikkclctvuohpmgkumhlnqfgsdejvuhjksczthrctwdhylwtyineoqflqsx";
	int rurcqakapkt = 3954;
	if (361 != 361) {
		int ajnuhlybu;
		for (ajnuhlybu = 2; ajnuhlybu > 0; ajnuhlybu--) {
			continue;
		}
	}
	if (true != true) {
		int rxu;
		for (rxu = 86; rxu > 0; rxu--) {
			continue;
		}
	}
	if (string("wkzxiiql") != string("wkzxiiql")) {
		int utbnzbvlb;
		for (utbnzbvlb = 19; utbnzbvlb > 0; utbnzbvlb--) {
			continue;
		}
	}
	if (string("dkxprpqkslfpqtukajadeojirwikcfikkclctvuohpmgkumhlnqfgsdejvuhjksczthrctwdhylwtyineoqflqsx") == string("dkxprpqkslfpqtukajadeojirwikcfikkclctvuohpmgkumhlnqfgsdejvuhjksczthrctwdhylwtyineoqflqsx")) {
		int yrkjc;
		for (yrkjc = 18; yrkjc > 0; yrkjc--) {
			continue;
		}
	}

}

void kzjgvhd::dsfcppfenaeyh(double btbrigipuksvdyx, int ecdlffluqrhav) {

}

kzjgvhd::kzjgvhd() {
	this->xutlntavezqx(2235, true, true, 4213, string("ui"), 1788, 689);
	this->mfblszryvhhnxw(1785, 47103, 6585, 627, true, false, 2603, 1591, 8624);
	this->wvfuljoobwqmqefflmbrveb(false, 23539, 13686, 12531, 60879, 366, 50747, 5930);
	this->rcdihrlbhabatefpwxem();
	this->gqpwugolmub(29652, 329, 803, 7304, 239, 4750, string("tsgnmroxmvcrixsbvqdkpfvrlscsvmlengqwsligzicludxortfkgipaftywnrggtlobthvwfdosqa"), string("zvjdykrirvbsgrnbkuokpyrchfigojunggcczwkfgndbjgfcwuozlzsmatjyqhgryqpt"));
	this->cvdwfmpufnxnzafktbgf(18367, 28427, 581, string("tribjkkfaoqyfbnpcduuwnbvpquvprmubnplylggufyfxdmrdydpllklbqrnenysyxcwzypzzpqswqkwuqufg"), true, 1664, true, 1521, string("yqhrthfvmumqvvmhqgehbhdqwqpslw"));
	this->sglzloswsivzxrsjmhjkq(4780, string("qszhmgtdahfggzbvfkkbafcpcbiicwertmikyjcsmkrvunotuqsgqamgrqakttvulvbhv"));
	this->hnvyurjjdtqzhdnrd(false, 5339, 8150, 81771, string("jrmjrjwsrbg"), 37246, false, false, 43900, 10100);
	this->sksfxgypjunhfp(string("dfeumsypfm"), true, string("xkivepyfnrftxgmbshhyyvbvpurcxuzrrdqqrjumigicstsivusblrijp"), 25831);
	this->dsfcppfenaeyh(9367, 1042);
	this->vbpnboqtpjlywewindwd(4487, false, 1550, 18414, 538, 2385, string("zsktkjtbacupjnzlhkoxxmhbgsqnulmzpdlrbgxbqnjvtiyoluulaivdlevtqcqprofkgakwuduejnhhzmpmnmicahokddxq"), string("jsoncstyhcbzhhcfgytuglvlycdbmlwioxcxwnafqhtyyfmkqcxhnpbtfplhodyywmxo"));
	this->awbpsyfkkabdqpxvgmu(6822, 6920, 910, false, 23767, 33282, true, string("fvkaqslnlebketpajklzccwygptddrengasmcotarambidgusdcj"), string("rwuqeczgoaarblvcokmusgltppncpemoidxcbiasp"));
	this->nhuzxnioxcd();
	this->rtecgxgmumujczzuqxfoms(true, 874, string("mfgtsyx"), false, string("lnckvymkgdcertujlgguemjxfvpjuylunldjdfpfuadmibscvfbpkqwlclpteldmpxwkujztsffskbqyygrolkczkgwaa"), true, true, string("wdvsqgwrd"), true, 99);
	this->ecojznwbhtzfuvscettokrr(136, 14, 4622, string("fdgweovpwsyipxsxgjkfnbpgvbnoukyfyensutfsskpcpxgfuxnys"), string("ybrhqfkghb"), 2030, true);
	this->bvlexqcsodwstvmbacbyugqsz(false, 2357);
	this->bibutgmartofozgnpwlet(18546, 21879, string("tvqtjninhslqkbnqjanmmt"), true);
	this->mbzmtbtikhctezensxpdtg(false, true, 3421, false);
	this->epcthppoxkueonzrlfs(string("zsn"), 47241, false);
	this->jcrqmzazuqscmsv(1052, 1756, true, 4340, true);
	this->jpzkznkqum(70651);
	this->mezjgaizushjxivaapzpykot(54887, string("ahiynepxkybggbphydbmwjzqlxhkyk"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class bvksana {
public:
	bool lktfibyhfm;
	int mdhgphqaryji;
	double fhpco;
	string qhripf;
	bvksana();
	bool ravomnvtkbwxmvcxtyii(string mbcscnad, int xqxsdkywuogeun, string pqymh, bool ddagkv, bool jsgiuxcfz);
	void qjrcnxnafmfjhnot(double csvnasyatymqo, bool wkqsxwplrmdi, bool xsnjhue);
	bool vxqtoeoiwkccrbsjbcp(string lkhlqdxwuwno, int xzgmxxkwp, bool ijlnhjbcmsxjaz, bool jnzmitrrvf, bool cxqlky, int sjcmlcnxwkqqjda, double ubqtfl, double qhcqpnmzsepzhgq, string llvem, string vmtcigslmoomlqr);
	bool wnifxbujbvyq(string acwphgxjduk, double noghtnp, string qebbm, string vrrqvboycg, string hfujticsopbvfzi, double kkfxgsjcb, string zwdxneqkmxhem, double johghicbuccasnm);
	double xsmnzldzwu(double biayqbgdpgnfi, int rbgmyfb, bool ozxbnikxxqb, double yiqqquaivxenta, double tgrxyhggqeniq, double kqywnrczq, string hnkopmfbd);
	int xcjlybbkaytukntlhqrdfepi(double jxcwmrwlexveb, string heiwrcobfnor);
	bool qaerahqgxarlgwgqlnolnjqx(int uezxtxwhhhw, bool eqrfdpgrrd, double fbpkajmctkcatlp, double ngiyqsx);
	string wnmwezgkqlmtd(double atafidbot, string hwqwtndrsi, bool fzcpfoxr);
	int jrucuhqayiwbirnnw(string swxycxkre, int xlhspszqlsygl, bool eymelpehydnxbv, string oeabjzjmacd, bool drvgjphbf, string ybhaqkz);

protected:
	int wuuepbg;
	double caucnwbcztvjl;

	int yhiovshwkueu(bool mocjwzmx);
	bool salqqvfiqnsfrsgtubr(double ebltojfqzvcxg, int nhdedzg, double ryvmxre);
	double wvjbeevlfficfddidtryfzc(string rfhqccnzm);
	void qwimjyikwdmyzhpqoc(double jkjbacrx, int ctxackvjp, bool lgjsdchsfkotmgc, string sirse, int fqxdemuho);
	int fafgzlltlyy(double oabbeqgf, string klgkb, string bwiagnwrtmemr, int bdzfomdzrma, int tjoyhicvxcjea, double jwhgkaed, int zssbdktpvogbvj, double ejetqliiptl, int zmwsmyumvd, string prnozlwdepn);
	int zlxxpigltin();
	bool llgkeymjyxn(int ywdkv, bool tkwxno, int vdiqw, int hkknqbrqmta, int zjrvjrhteh, bool oukymfxnbbelmjn);
	int izwyvltsvmswmcwpevedeo(int zndrn, double pqrgosxd);
	int kealuurhsoswoh(bool lludjshxosvxut, int ohmdhqowaseojc, int uflfxcrdwqlpeu, string cgldhcaxndnfy, int ptnhjld, string npkgjewxicx, bool xbxprhb, int kagkq, string ohtvohnlyuzq, double cxtxluaftbxgfu);

private:
	double acygthc;
	int vkgcskiegdmoc;
	string yxdmwsgtupu;
	bool nyomtnxydigtn;
	bool phenwnavwt;

	int nzkariikhlhlulegnoxrap(bool oytxre, int iwdtukx, int bcalj, double mgybubxwt, bool fwhiagrniv, double qesieka);
	void waiouglniqwevf();
	void wolfwzqefalbpqmius(string xpdjhcnrgpn, double cicxxzroiv);
	bool znlfewnhhl(int avmscs, double pnanqxoi, bool uzxatqwfueljbx);
	int kyxshrhtrjsffyrqzaxfs(double meraamt, double yxnbgmjuhicqlh, double djmbdqjbirth, string oquby);

};


int bvksana::nzkariikhlhlulegnoxrap(bool oytxre, int iwdtukx, int bcalj, double mgybubxwt, bool fwhiagrniv, double qesieka) {
	string kezznuk = "thvrbetujadxbfnqlcqrnygnxdfcawnz";
	bool kukmbpuya = true;
	bool jfkgyhpi = false;
	bool ylxhnu = false;
	int qetxxjq = 1970;
	string kxvfr = "gjcbfewenvjtmudctjfafmplvfqdsebdlathyrec";
	int becmt = 2400;
	string pacupzngmloycp = "ypufhametpowlvzjphpfbht";
	return 92451;
}

void bvksana::waiouglniqwevf() {
	int nhxirasahy = 563;
	int ydigwjndutp = 4337;
	string ibcdbnw = "qkzaxuevjyzhlawxfratpjfqsbetxetjmsxhejceyksxvilfelfmlbibyxtl";
	double wmjzxmkijz = 35493;
	int wtfuldotc = 199;
	bool emsemmzvktydt = false;
	string ssvzxxjqugt = "csdueztwzlhvvopcnblwuvcrbthzmfyxrlamyfxgpmawqwzvnxqowahoxcivbdrxfjcy";
	string yqmnznjsowy = "gooyvsstmuxdkaaghcpsshlhrnvivsxiljrlpcexqbgotccngzsyhszucistcwukztrmixjdntgfvdbrrnpfkbhc";
	double bezqjlt = 12109;
	int gqokd = 2671;
	if (2671 != 2671) {
		int uwildfnnrc;
		for (uwildfnnrc = 81; uwildfnnrc > 0; uwildfnnrc--) {
			continue;
		}
	}
	if (false == false) {
		int gyu;
		for (gyu = 51; gyu > 0; gyu--) {
			continue;
		}
	}
	if (563 == 563) {
		int vbra;
		for (vbra = 77; vbra > 0; vbra--) {
			continue;
		}
	}
	if (4337 == 4337) {
		int sec;
		for (sec = 32; sec > 0; sec--) {
			continue;
		}
	}
	if (string("csdueztwzlhvvopcnblwuvcrbthzmfyxrlamyfxgpmawqwzvnxqowahoxcivbdrxfjcy") != string("csdueztwzlhvvopcnblwuvcrbthzmfyxrlamyfxgpmawqwzvnxqowahoxcivbdrxfjcy")) {
		int jzmsgn;
		for (jzmsgn = 34; jzmsgn > 0; jzmsgn--) {
			continue;
		}
	}

}

void bvksana::wolfwzqefalbpqmius(string xpdjhcnrgpn, double cicxxzroiv) {
	bool xdukhe = false;
	double pfxxo = 3490;
	double uanccgmlnlfyehi = 46736;
	double sxtcrtngc = 8230;
	bool bessrgo = false;
	int nhckh = 2214;
	bool zbubhplrx = true;
	if (46736 == 46736) {
		int xvwwnkkj;
		for (xvwwnkkj = 26; xvwwnkkj > 0; xvwwnkkj--) {
			continue;
		}
	}
	if (3490 != 3490) {
		int myu;
		for (myu = 97; myu > 0; myu--) {
			continue;
		}
	}

}

bool bvksana::znlfewnhhl(int avmscs, double pnanqxoi, bool uzxatqwfueljbx) {
	double jxneapuq = 78965;
	double dfxsvgxmq = 4308;
	int ybxsqehiifjpwp = 3416;
	bool tcwzxytrkk = false;
	int zvqxvtcjr = 6715;
	bool rfjlzpq = true;
	bool fztcieywotutm = false;
	if (false != false) {
		int hfbpztizzt;
		for (hfbpztizzt = 13; hfbpztizzt > 0; hfbpztizzt--) {
			continue;
		}
	}
	if (false == false) {
		int ge;
		for (ge = 13; ge > 0; ge--) {
			continue;
		}
	}
	return true;
}

int bvksana::kyxshrhtrjsffyrqzaxfs(double meraamt, double yxnbgmjuhicqlh, double djmbdqjbirth, string oquby) {
	string niophlmqhs = "mqkgfposgtlixdoxgbpgqiglbgzqywpufyequuxfhzqqpdcxebqgllmyrkvniuccwdblflxcndzv";
	int tawrpjivsn = 4567;
	if (4567 == 4567) {
		int yhxnpsux;
		for (yhxnpsux = 66; yhxnpsux > 0; yhxnpsux--) {
			continue;
		}
	}
	if (4567 != 4567) {
		int nvegtwueqn;
		for (nvegtwueqn = 72; nvegtwueqn > 0; nvegtwueqn--) {
			continue;
		}
	}
	if (4567 != 4567) {
		int evtuqmo;
		for (evtuqmo = 13; evtuqmo > 0; evtuqmo--) {
			continue;
		}
	}
	if (string("mqkgfposgtlixdoxgbpgqiglbgzqywpufyequuxfhzqqpdcxebqgllmyrkvniuccwdblflxcndzv") != string("mqkgfposgtlixdoxgbpgqiglbgzqywpufyequuxfhzqqpdcxebqgllmyrkvniuccwdblflxcndzv")) {
		int zmonoyfkm;
		for (zmonoyfkm = 27; zmonoyfkm > 0; zmonoyfkm--) {
			continue;
		}
	}
	if (string("mqkgfposgtlixdoxgbpgqiglbgzqywpufyequuxfhzqqpdcxebqgllmyrkvniuccwdblflxcndzv") != string("mqkgfposgtlixdoxgbpgqiglbgzqywpufyequuxfhzqqpdcxebqgllmyrkvniuccwdblflxcndzv")) {
		int cexbyi;
		for (cexbyi = 32; cexbyi > 0; cexbyi--) {
			continue;
		}
	}
	return 9696;
}

int bvksana::yhiovshwkueu(bool mocjwzmx) {
	string jgmvrbczgb = "souaa";
	double fhaxjlf = 28544;
	bool oaluitirakv = true;
	double hmqpysahjuloo = 5463;
	double vnewnzgqbwhe = 9472;
	return 90208;
}

bool bvksana::salqqvfiqnsfrsgtubr(double ebltojfqzvcxg, int nhdedzg, double ryvmxre) {
	return true;
}

double bvksana::wvjbeevlfficfddidtryfzc(string rfhqccnzm) {
	string zibbsrvy = "yvhotmwxnokzbzplpcjtlmiihwexfmqcygyhsggjnzddlawwfwvk";
	double qdqiljzpbuewgla = 45681;
	string dmejjztfmep = "lgbsjvcquxguuqixgqoesewajfytwatrhxkozqbithfawhixbqnbdwpmiutcstiabviopazu";
	int pwkpdwfaa = 6932;
	string pufpegoff = "isymxlinbcflkucniedooewvwwundpyhenvomagmqdqlzgwkoymkwposmouoclcjbumfhqbecueaned";
	string sxolodc = "qgvudsnjddwujfufepawbzhbkbpavuoylhitzqkapibzvyswl";
	if (string("lgbsjvcquxguuqixgqoesewajfytwatrhxkozqbithfawhixbqnbdwpmiutcstiabviopazu") == string("lgbsjvcquxguuqixgqoesewajfytwatrhxkozqbithfawhixbqnbdwpmiutcstiabviopazu")) {
		int gpzo;
		for (gpzo = 61; gpzo > 0; gpzo--) {
			continue;
		}
	}
	if (string("lgbsjvcquxguuqixgqoesewajfytwatrhxkozqbithfawhixbqnbdwpmiutcstiabviopazu") != string("lgbsjvcquxguuqixgqoesewajfytwatrhxkozqbithfawhixbqnbdwpmiutcstiabviopazu")) {
		int cdfojvqv;
		for (cdfojvqv = 67; cdfojvqv > 0; cdfojvqv--) {
			continue;
		}
	}
	if (string("isymxlinbcflkucniedooewvwwundpyhenvomagmqdqlzgwkoymkwposmouoclcjbumfhqbecueaned") == string("isymxlinbcflkucniedooewvwwundpyhenvomagmqdqlzgwkoymkwposmouoclcjbumfhqbecueaned")) {
		int bqtsmkmnac;
		for (bqtsmkmnac = 67; bqtsmkmnac > 0; bqtsmkmnac--) {
			continue;
		}
	}
	return 6997;
}

void bvksana::qwimjyikwdmyzhpqoc(double jkjbacrx, int ctxackvjp, bool lgjsdchsfkotmgc, string sirse, int fqxdemuho) {
	double mjynuo = 56061;
	double ytkpxz = 38151;
	int fumanxt = 734;
	string wjpdi = "sajjakoserpefpfgfeeqernotcnpxztplzqxmzouzczkffkqybfthmdrijrzthxvthshzxrkuniio";
	bool aliferlgoka = false;
	if (string("sajjakoserpefpfgfeeqernotcnpxztplzqxmzouzczkffkqybfthmdrijrzthxvthshzxrkuniio") == string("sajjakoserpefpfgfeeqernotcnpxztplzqxmzouzczkffkqybfthmdrijrzthxvthshzxrkuniio")) {
		int ndcnbcl;
		for (ndcnbcl = 36; ndcnbcl > 0; ndcnbcl--) {
			continue;
		}
	}

}

int bvksana::fafgzlltlyy(double oabbeqgf, string klgkb, string bwiagnwrtmemr, int bdzfomdzrma, int tjoyhicvxcjea, double jwhgkaed, int zssbdktpvogbvj, double ejetqliiptl, int zmwsmyumvd, string prnozlwdepn) {
	bool xielefxal = false;
	int twlrb = 262;
	string vtpuekctl = "vjtiai";
	double ccgpdifkgeigjae = 33160;
	int kvkactcngv = 1507;
	if (1507 == 1507) {
		int uyepwbifn;
		for (uyepwbifn = 37; uyepwbifn > 0; uyepwbifn--) {
			continue;
		}
	}
	if (1507 == 1507) {
		int bsvpgkdi;
		for (bsvpgkdi = 30; bsvpgkdi > 0; bsvpgkdi--) {
			continue;
		}
	}
	if (string("vjtiai") == string("vjtiai")) {
		int adjxa;
		for (adjxa = 27; adjxa > 0; adjxa--) {
			continue;
		}
	}
	if (33160 == 33160) {
		int llpw;
		for (llpw = 76; llpw > 0; llpw--) {
			continue;
		}
	}
	if (33160 == 33160) {
		int tylpisf;
		for (tylpisf = 62; tylpisf > 0; tylpisf--) {
			continue;
		}
	}
	return 24401;
}

int bvksana::zlxxpigltin() {
	string mnnoaeeekms = "jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh";
	double ohsggiswigxu = 73578;
	if (73578 != 73578) {
		int dvetbd;
		for (dvetbd = 39; dvetbd > 0; dvetbd--) {
			continue;
		}
	}
	if (string("jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh") != string("jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh")) {
		int fdbtkxqsdn;
		for (fdbtkxqsdn = 10; fdbtkxqsdn > 0; fdbtkxqsdn--) {
			continue;
		}
	}
	if (string("jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh") == string("jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh")) {
		int gx;
		for (gx = 41; gx > 0; gx--) {
			continue;
		}
	}
	if (string("jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh") == string("jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh")) {
		int yl;
		for (yl = 98; yl > 0; yl--) {
			continue;
		}
	}
	if (string("jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh") != string("jftwdskdgcvpbtadybnfxjugotvkmfszaepufylsesiydxphasxpuohdzzesdqsngerkohbydsvvqudhfnqhffkoboyh")) {
		int th;
		for (th = 98; th > 0; th--) {
			continue;
		}
	}
	return 73192;
}

bool bvksana::llgkeymjyxn(int ywdkv, bool tkwxno, int vdiqw, int hkknqbrqmta, int zjrvjrhteh, bool oukymfxnbbelmjn) {
	int cjebeyhjat = 242;
	bool bqbrncfesxqqy = false;
	bool tdoijbnqesv = true;
	double kljsqlqvhta = 63409;
	if (true == true) {
		int smk;
		for (smk = 18; smk > 0; smk--) {
			continue;
		}
	}
	if (242 != 242) {
		int ryjzu;
		for (ryjzu = 20; ryjzu > 0; ryjzu--) {
			continue;
		}
	}
	if (false == false) {
		int ddateptegw;
		for (ddateptegw = 46; ddateptegw > 0; ddateptegw--) {
			continue;
		}
	}
	if (true == true) {
		int tevugxlwe;
		for (tevugxlwe = 77; tevugxlwe > 0; tevugxlwe--) {
			continue;
		}
	}
	return false;
}

int bvksana::izwyvltsvmswmcwpevedeo(int zndrn, double pqrgosxd) {
	return 24282;
}

int bvksana::kealuurhsoswoh(bool lludjshxosvxut, int ohmdhqowaseojc, int uflfxcrdwqlpeu, string cgldhcaxndnfy, int ptnhjld, string npkgjewxicx, bool xbxprhb, int kagkq, string ohtvohnlyuzq, double cxtxluaftbxgfu) {
	int rtqbmmxshagula = 3187;
	string uyqcviz = "nwmhrrgihvtymofjqwlcxo";
	string kpomj = "xkqosgibcdjvmidfcatyvuwbifpdjtoqhciweandmpqkqprqimhulwtnpbtoyswnfqzejclazkxkizmgyqqbtsbjrspvxn";
	string fwhnswjadzpf = "lnrrbucpgbzcdydvvdswplkssirpcsjspgrqgazhevwgaxjlygntsdtzmadutrbjosezpprqjcsmynbgyeosjxcoopxyex";
	if (string("nwmhrrgihvtymofjqwlcxo") == string("nwmhrrgihvtymofjqwlcxo")) {
		int ymrkokl;
		for (ymrkokl = 11; ymrkokl > 0; ymrkokl--) {
			continue;
		}
	}
	if (string("lnrrbucpgbzcdydvvdswplkssirpcsjspgrqgazhevwgaxjlygntsdtzmadutrbjosezpprqjcsmynbgyeosjxcoopxyex") == string("lnrrbucpgbzcdydvvdswplkssirpcsjspgrqgazhevwgaxjlygntsdtzmadutrbjosezpprqjcsmynbgyeosjxcoopxyex")) {
		int qkpgbrtbn;
		for (qkpgbrtbn = 28; qkpgbrtbn > 0; qkpgbrtbn--) {
			continue;
		}
	}
	if (3187 != 3187) {
		int xhn;
		for (xhn = 83; xhn > 0; xhn--) {
			continue;
		}
	}
	if (string("lnrrbucpgbzcdydvvdswplkssirpcsjspgrqgazhevwgaxjlygntsdtzmadutrbjosezpprqjcsmynbgyeosjxcoopxyex") == string("lnrrbucpgbzcdydvvdswplkssirpcsjspgrqgazhevwgaxjlygntsdtzmadutrbjosezpprqjcsmynbgyeosjxcoopxyex")) {
		int oitweocsml;
		for (oitweocsml = 92; oitweocsml > 0; oitweocsml--) {
			continue;
		}
	}
	if (string("lnrrbucpgbzcdydvvdswplkssirpcsjspgrqgazhevwgaxjlygntsdtzmadutrbjosezpprqjcsmynbgyeosjxcoopxyex") != string("lnrrbucpgbzcdydvvdswplkssirpcsjspgrqgazhevwgaxjlygntsdtzmadutrbjosezpprqjcsmynbgyeosjxcoopxyex")) {
		int jy;
		for (jy = 25; jy > 0; jy--) {
			continue;
		}
	}
	return 98053;
}

bool bvksana::ravomnvtkbwxmvcxtyii(string mbcscnad, int xqxsdkywuogeun, string pqymh, bool ddagkv, bool jsgiuxcfz) {
	double msldezltypipsmc = 20772;
	string ufwrzjjbzcidyt = "klaeughyrslphcvdhxxlykuvktdevtxjbvkntdelzqfihgulhskkgjdzvtsnzbwipuqqkj";
	double gczuoc = 7612;
	int qfcwixemejoji = 3303;
	int gtlvrzc = 8054;
	string phjmffccejd = "lxmfaswfndejehnjrkrqvehqmzlcpmpjrshaennwuzbizjuxsgkaliortbpb";
	int snkzczjzmqvq = 1124;
	string lsnlbid = "blchrqbeestf";
	int rogzodiized = 2030;
	if (1124 == 1124) {
		int evmihwgcmv;
		for (evmihwgcmv = 95; evmihwgcmv > 0; evmihwgcmv--) {
			continue;
		}
	}
	if (1124 != 1124) {
		int ef;
		for (ef = 52; ef > 0; ef--) {
			continue;
		}
	}
	if (2030 == 2030) {
		int ebcxxe;
		for (ebcxxe = 84; ebcxxe > 0; ebcxxe--) {
			continue;
		}
	}
	if (1124 != 1124) {
		int scadajbitg;
		for (scadajbitg = 76; scadajbitg > 0; scadajbitg--) {
			continue;
		}
	}
	if (8054 == 8054) {
		int uqpy;
		for (uqpy = 9; uqpy > 0; uqpy--) {
			continue;
		}
	}
	return false;
}

void bvksana::qjrcnxnafmfjhnot(double csvnasyatymqo, bool wkqsxwplrmdi, bool xsnjhue) {
	int lfmmkoncyjoio = 1923;
	if (1923 == 1923) {
		int ipjvpwhght;
		for (ipjvpwhght = 49; ipjvpwhght > 0; ipjvpwhght--) {
			continue;
		}
	}

}

bool bvksana::vxqtoeoiwkccrbsjbcp(string lkhlqdxwuwno, int xzgmxxkwp, bool ijlnhjbcmsxjaz, bool jnzmitrrvf, bool cxqlky, int sjcmlcnxwkqqjda, double ubqtfl, double qhcqpnmzsepzhgq, string llvem, string vmtcigslmoomlqr) {
	string pgpvn = "hjyqbpenwyhxbnwvdkynn";
	bool zlkijalxatopm = false;
	bool ddvgdpb = true;
	bool pjbumpkvgmr = true;
	bool lvqfrjkokmldv = false;
	string losgridx = "saoxtqojjruqpknyigqnanejpu";
	bool htvejfc = false;
	if (false != false) {
		int nylyma;
		for (nylyma = 5; nylyma > 0; nylyma--) {
			continue;
		}
	}
	if (true != true) {
		int ww;
		for (ww = 21; ww > 0; ww--) {
			continue;
		}
	}
	return true;
}

bool bvksana::wnifxbujbvyq(string acwphgxjduk, double noghtnp, string qebbm, string vrrqvboycg, string hfujticsopbvfzi, double kkfxgsjcb, string zwdxneqkmxhem, double johghicbuccasnm) {
	double nggzkhzza = 43480;
	bool acezlekwahvagt = true;
	int bzkkg = 319;
	if (43480 == 43480) {
		int ptqsnkw;
		for (ptqsnkw = 2; ptqsnkw > 0; ptqsnkw--) {
			continue;
		}
	}
	return true;
}

double bvksana::xsmnzldzwu(double biayqbgdpgnfi, int rbgmyfb, bool ozxbnikxxqb, double yiqqquaivxenta, double tgrxyhggqeniq, double kqywnrczq, string hnkopmfbd) {
	string phkicsexx = "qnuqiumwrkaowjzuovoiqgvkbamzjaynlgysivesaqzqbporitmcaqsqhdaimrhossnxhecblukxnbnoeychnqmuxxt";
	int dtawxpo = 1875;
	int hfitgjzha = 2368;
	double pmrywv = 23504;
	double umwwfc = 4601;
	if (23504 != 23504) {
		int wxkapeu;
		for (wxkapeu = 23; wxkapeu > 0; wxkapeu--) {
			continue;
		}
	}
	if (1875 == 1875) {
		int ahg;
		for (ahg = 7; ahg > 0; ahg--) {
			continue;
		}
	}
	if (string("qnuqiumwrkaowjzuovoiqgvkbamzjaynlgysivesaqzqbporitmcaqsqhdaimrhossnxhecblukxnbnoeychnqmuxxt") != string("qnuqiumwrkaowjzuovoiqgvkbamzjaynlgysivesaqzqbporitmcaqsqhdaimrhossnxhecblukxnbnoeychnqmuxxt")) {
		int hlgbtzfkk;
		for (hlgbtzfkk = 77; hlgbtzfkk > 0; hlgbtzfkk--) {
			continue;
		}
	}
	if (4601 != 4601) {
		int nwlr;
		for (nwlr = 53; nwlr > 0; nwlr--) {
			continue;
		}
	}
	if (2368 == 2368) {
		int lyiuqvzej;
		for (lyiuqvzej = 58; lyiuqvzej > 0; lyiuqvzej--) {
			continue;
		}
	}
	return 84653;
}

int bvksana::xcjlybbkaytukntlhqrdfepi(double jxcwmrwlexveb, string heiwrcobfnor) {
	int pzkuxsaofxa = 967;
	bool tzeemqa = false;
	string fggbuvwsg = "cbdcaqmcymsvtmojxvuuiakzdyhqgubqpyvoiahzfatrsrvagqgrtqmehhldlcqlhapkcwziryd";
	if (967 != 967) {
		int vnjncjsu;
		for (vnjncjsu = 14; vnjncjsu > 0; vnjncjsu--) {
			continue;
		}
	}
	if (string("cbdcaqmcymsvtmojxvuuiakzdyhqgubqpyvoiahzfatrsrvagqgrtqmehhldlcqlhapkcwziryd") != string("cbdcaqmcymsvtmojxvuuiakzdyhqgubqpyvoiahzfatrsrvagqgrtqmehhldlcqlhapkcwziryd")) {
		int svnkqqfig;
		for (svnkqqfig = 17; svnkqqfig > 0; svnkqqfig--) {
			continue;
		}
	}
	if (false != false) {
		int nbjuauuyz;
		for (nbjuauuyz = 18; nbjuauuyz > 0; nbjuauuyz--) {
			continue;
		}
	}
	if (false != false) {
		int ccxwxjxded;
		for (ccxwxjxded = 71; ccxwxjxded > 0; ccxwxjxded--) {
			continue;
		}
	}
	if (967 == 967) {
		int ncb;
		for (ncb = 44; ncb > 0; ncb--) {
			continue;
		}
	}
	return 88260;
}

bool bvksana::qaerahqgxarlgwgqlnolnjqx(int uezxtxwhhhw, bool eqrfdpgrrd, double fbpkajmctkcatlp, double ngiyqsx) {
	int kxubmawgzzcl = 494;
	double mhdph = 52494;
	string jkwxsligtdllcrn = "zmzjejqokegvwoiwbtaqqhehukcocbjivpgzukpifvpcjzuufxdmuamzqjenpcvzlsrguknufpxjpxxcvtkjreoennjbhqijsbid";
	string ekxfnnhpfwgubsc = "unwpnmwxwolklsqmfcqjqnfobum";
	int rpqrsv = 1110;
	return true;
}

string bvksana::wnmwezgkqlmtd(double atafidbot, string hwqwtndrsi, bool fzcpfoxr) {
	bool qjzxpltbjmghktp = false;
	double ibpvag = 13608;
	double bmdgtams = 88705;
	if (13608 == 13608) {
		int viqsdvew;
		for (viqsdvew = 43; viqsdvew > 0; viqsdvew--) {
			continue;
		}
	}
	if (13608 == 13608) {
		int iboavfjdhc;
		for (iboavfjdhc = 15; iboavfjdhc > 0; iboavfjdhc--) {
			continue;
		}
	}
	if (false == false) {
		int sxyft;
		for (sxyft = 84; sxyft > 0; sxyft--) {
			continue;
		}
	}
	return string("klzikwjjfepwxhqgh");
}

int bvksana::jrucuhqayiwbirnnw(string swxycxkre, int xlhspszqlsygl, bool eymelpehydnxbv, string oeabjzjmacd, bool drvgjphbf, string ybhaqkz) {
	int dtsgeunfme = 933;
	int nqiwq = 1612;
	double wynyjvjvf = 9595;
	int znhrfbeasxeiuw = 5294;
	bool bzmvndrue = true;
	string hxbdt = "oouxjijuczfhqmywrxivzaceecknqelkgjjiesqgcxuvcxnhgybfxvrvcsvznyqopukkmweniqkororeoznnmdetxqkdzxuzda";
	bool qwocgaobnehhupy = false;
	double gmassrdfngz = 14024;
	if (5294 != 5294) {
		int pnizargu;
		for (pnizargu = 7; pnizargu > 0; pnizargu--) {
			continue;
		}
	}
	if (14024 == 14024) {
		int dtvsd;
		for (dtvsd = 90; dtvsd > 0; dtvsd--) {
			continue;
		}
	}
	return 49133;
}

bvksana::bvksana() {
	this->ravomnvtkbwxmvcxtyii(string("jgpdljplavwkakogiffhombihhzcbjsyokamqoaerpfrkfdulvcdmjtj"), 5879, string("zkbolieltrghqogcqdtioxlkzmcawdkgzbkzrzkegdk"), false, true);
	this->qjrcnxnafmfjhnot(9031, true, false);
	this->vxqtoeoiwkccrbsjbcp(string("loiewxoxcjmeauloxewdxywxjyenelhnzepahimesqqjz"), 2921, false, true, true, 2951, 7245, 5562, string("znshrcjgrvimlrlbtffuajsaslv"), string("vqychozmeybwrrfjztbioknnngthlsqiyternxdqmlyticjthqegphvcnmgkanpqqalr"));
	this->wnifxbujbvyq(string("ymgdfgjrhgspllwavnvdceehnnhytqldswhmjylbhmravmncnwtomltsllvn"), 17899, string("tyfztfwuysphcwbbemzlspibzafifbdunsfuafrilotobmdmzufzvvbopyguryeeixuxdqwusnyiwwsaltnweipwfzmdvcp"), string("evcmrdyxstftjfzqxxttgxpsmbouhixmaxqybgyoajodjdaqigjhcltx"), string("dohvllalqntwvsyfssaclkmbjgjkflsdvuisuzjomnit"), 2204, string("ofxmaecrbtlbicatmebybdmqmhxug"), 31046);
	this->xsmnzldzwu(29714, 2070, true, 8648, 4641, 48712, string("kpmxoeeyheprhsrbultzlanxygwrbzlsmmtlmbtipogvsfhvfymmvwamclxzpjevbmmpretqnulgfdeacyisveqyfw"));
	this->xcjlybbkaytukntlhqrdfepi(6668, string("sofrzhwgkzgnygakmejkgvtnyhwrwrkcawzjwpgqkel"));
	this->qaerahqgxarlgwgqlnolnjqx(29, false, 4698, 13769);
	this->wnmwezgkqlmtd(47993, string("kdfxqdyydqvddtxqjmvcfczmt"), true);
	this->jrucuhqayiwbirnnw(string("rnidmwtnnkofvegzdrqwshlgghwpeoditxqwmghbltvjdxphcnff"), 58, true, string("fyzqugtktiaxibvllpwzixvojomcqwybcezuwhyfxnabvypglqiypkifwntxamsqtyearicnwwbkvbpugjsqppg"), false, string("iqjuzhahxhbklyzkhlzxslqenyvoaunueameqjpvobmdqiupvc"));
	this->yhiovshwkueu(false);
	this->salqqvfiqnsfrsgtubr(19306, 631, 38162);
	this->wvjbeevlfficfddidtryfzc(string("mhlzftobrkucivpwsqiksokgwxsjepnxwvmcrizjlklcragakueeaofxibfznuvvgapvmgmnhxqzpj"));
	this->qwimjyikwdmyzhpqoc(27977, 3271, true, string("yocvaehfbnqpxatnfiernjemfwxzichixgnadrbtbbnznglvkovgjmxucbsb"), 2626);
	this->fafgzlltlyy(11145, string("xkiafziocosabxsfugzrhdootegcwufddnfwtofjy"), string("ytqwvabmwqdkxozydruaczyakybosntaxozwszsyljpkpf"), 1659, 4894, 36337, 7017, 42502, 1705, string("agzvozpjlvenopicbesoffxllziddzi"));
	this->zlxxpigltin();
	this->llgkeymjyxn(27, false, 1263, 3540, 4387, true);
	this->izwyvltsvmswmcwpevedeo(179, 23287);
	this->kealuurhsoswoh(true, 3744, 1494, string("hwbsvgyukzhkewyijtyaplkdrtsmpnmlvidmlondvtnutrkkbaoqddgnmfoezrwwsyycnrsh"), 4500, string("wejwpybvniskmqjsdnnlaetnqndvuwurgwxspvjykdlbvekqvefgprxqqmpzkwpvjlnogzhchdhpnxteykzostidjxlfkvyoxj"), false, 196, string("kpvxtgpbtpnshkflexvikhyljxrnxiyzmzgdfcfooxvufhgwgukpqfxsnmqpsviajprtalhxbjllyuz"), 7370);
	this->nzkariikhlhlulegnoxrap(true, 43, 814, 10955, false, 11168);
	this->waiouglniqwevf();
	this->wolfwzqefalbpqmius(string("diclzwlfcknyxkfxdjduwgfdrvggsbvduhtmfd"), 3194);
	this->znlfewnhhl(1117, 2648, false);
	this->kyxshrhtrjsffyrqzaxfs(80216, 29429, 23497, string("hvcedzmkjrgttnjnmweysqmhuqvsqgetjzlpfswlepifczxkcmvyypizzfgqtmlimkiwicufwklmcmfubrwgnhzbavk"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class dmimykl {
public:
	bool gmgepwwkyzxuvz;
	int hlsmgclofnnper;
	bool drxvyvzix;
	dmimykl();
	void ieraxjoexwx(string spxhklllivjastd, int zhbagmgvr, int rygpnwsgyicksrl, string bjccmcal, bool cbqymfzwuiby, bool cmietdfrnx);
	bool nwehetcaujkktjwe(int ouhggyoh, bool dvzkpslimqgljuo);

protected:
	string wacqghwrmptthss;

	bool dorvrnatvwdhfxeg(int pctuiqfvpnhvta, double zhzrt, int qtehpnhhyvrxp, int luegkulcextpo, double uyddruw, int amtntrrhsjta, int frzcgyyl);
	string aqfghywpgfdxvh(string ccprnstjdzdrlv, int qqyrm, bool twhxsazkdtfdc, string wqzxktwuezxgil, int ibfcgqeccf);
	string dmjnpulxyavmmjunbzx(bool qrflxdzvx, int dulczjystpho, double ctankkgowrte, string hftaa, string rqnik, string wqbuavbxo, bool btwwrzx, int stxgbdzhpdzr);
	string bqcacfgkozjsywsg(int oepijxvzwrhaqh);
	int hugprcmzxabyvxdw(double hifejqpqxvwpysw);
	int tskoesmrvuzz(string eafonhzyyelnav, bool vsxlksimx, int nvjhmkodvuxdxc, double bcizfsbpastrs, bool tkksugcjxqbdj, int jtgtwkbfnexc, double tiwravstfhrs, bool hrbiiafxibcse);
	bool gdhyrtecmcybzdo(double yjuaewnbcwj);
	void pkmadsmdaujbstyztp(bool aspgbalmm, string znjgasidnpyu, string qrvddfum, int kdentpana, bool greitpgm, double wajrtaowlwfn);
	int rgocnaxzrrdykibnkgur(bool qchjyxu, string xejkzm, int zyiubethoa, int iebqnmpjup, int vqyfqnobsp, int wotzorcirdy, string nilnsjhiytj, double wdztfqc, int hjrwnapkvhzezmg, int rrhegofgkb);
	string hvmxcanbskbwirpr(int pbivfv, bool prxewwb, int zasapvbrffstm, bool mlfscvgalgmho, string tcynjgj);

private:
	string ubgnhayxcropbn;
	double qvrxc;
	bool ilaew;

	double gxtczipvprxovxgqrbrrb(bool mylfsyqdjh, bool bqdrfznoznruqh, int odfyi, int rfafklepgxa, int rbrsagzvq);

};


double dmimykl::gxtczipvprxovxgqrbrrb(bool mylfsyqdjh, bool bqdrfznoznruqh, int odfyi, int rfafklepgxa, int rbrsagzvq) {
	string byuhxo = "bpzvcokyavzvesgodpasxvppaljmxvvmzjwreancsihwiiigk";
	bool pztfotbn = true;
	string jpojbftqb = "tnhbghhrgkvofsnlmlwrlgygbswplieat";
	string nnxeiafivuqcx = "jqvmkbokzumsabnbtvhvmtvdriymemfxhjvjbbvbcjdvqloirertsulkehwrzbtqfvcurmelicvdcmbgc";
	if (string("bpzvcokyavzvesgodpasxvppaljmxvvmzjwreancsihwiiigk") == string("bpzvcokyavzvesgodpasxvppaljmxvvmzjwreancsihwiiigk")) {
		int lfnzxisslj;
		for (lfnzxisslj = 91; lfnzxisslj > 0; lfnzxisslj--) {
			continue;
		}
	}
	return 73402;
}

bool dmimykl::dorvrnatvwdhfxeg(int pctuiqfvpnhvta, double zhzrt, int qtehpnhhyvrxp, int luegkulcextpo, double uyddruw, int amtntrrhsjta, int frzcgyyl) {
	double zyokoako = 1353;
	bool qwuqql = true;
	return true;
}

string dmimykl::aqfghywpgfdxvh(string ccprnstjdzdrlv, int qqyrm, bool twhxsazkdtfdc, string wqzxktwuezxgil, int ibfcgqeccf) {
	int vdtudtxqxpdik = 1957;
	int hwawgvrpvuzd = 2468;
	bool esiwbvqi = true;
	string cxpqjgx = "vsexhmazuuckwf";
	int vksdmoos = 1075;
	double ssabglhrx = 19719;
	string isfzq = "zvjqalivc";
	if (19719 != 19719) {
		int myoyk;
		for (myoyk = 38; myoyk > 0; myoyk--) {
			continue;
		}
	}
	if (1075 != 1075) {
		int ubhitsmq;
		for (ubhitsmq = 80; ubhitsmq > 0; ubhitsmq--) {
			continue;
		}
	}
	if (string("vsexhmazuuckwf") != string("vsexhmazuuckwf")) {
		int hjquvsqlj;
		for (hjquvsqlj = 20; hjquvsqlj > 0; hjquvsqlj--) {
			continue;
		}
	}
	return string("ksriyuopdzvyrykjafm");
}

string dmimykl::dmjnpulxyavmmjunbzx(bool qrflxdzvx, int dulczjystpho, double ctankkgowrte, string hftaa, string rqnik, string wqbuavbxo, bool btwwrzx, int stxgbdzhpdzr) {
	double ddchivxxpwcs = 18032;
	int aahzbyxealq = 1495;
	int exregnrr = 5180;
	int qbtrzrsfgu = 1865;
	string etvpawfid = "wcjfdtzpjmflprgzrtxcrdrxsyvtgtybknedepifkprnbifarwmswecsmitppaxmwvmracwwigcbmwfbxejvueeutinnv";
	double qaaptmzxczvx = 46517;
	int ynaabmi = 3032;
	if (3032 != 3032) {
		int tlzvt;
		for (tlzvt = 87; tlzvt > 0; tlzvt--) {
			continue;
		}
	}
	if (string("wcjfdtzpjmflprgzrtxcrdrxsyvtgtybknedepifkprnbifarwmswecsmitppaxmwvmracwwigcbmwfbxejvueeutinnv") != string("wcjfdtzpjmflprgzrtxcrdrxsyvtgtybknedepifkprnbifarwmswecsmitppaxmwvmracwwigcbmwfbxejvueeutinnv")) {
		int ohfk;
		for (ohfk = 40; ohfk > 0; ohfk--) {
			continue;
		}
	}
	if (1495 == 1495) {
		int nqlzqby;
		for (nqlzqby = 14; nqlzqby > 0; nqlzqby--) {
			continue;
		}
	}
	return string("wimfumdgqpticmsmgjg");
}

string dmimykl::bqcacfgkozjsywsg(int oepijxvzwrhaqh) {
	string buqvmk = "bvrswlibcsrxeklzuxyoxyzqfkidlycfdlkv";
	int dzkikcwcsrttix = 704;
	bool ronmbbbqetjgw = true;
	int gopcbxghaukfms = 1959;
	int scodhkbgpkxk = 5037;
	int yzopmqdjqgp = 7962;
	int fxdtzlc = 444;
	int dzumzi = 2996;
	int rjpwpwdpuczuj = 6370;
	if (5037 != 5037) {
		int xr;
		for (xr = 25; xr > 0; xr--) {
			continue;
		}
	}
	if (7962 == 7962) {
		int fzskwqsupe;
		for (fzskwqsupe = 96; fzskwqsupe > 0; fzskwqsupe--) {
			continue;
		}
	}
	if (704 != 704) {
		int pyq;
		for (pyq = 94; pyq > 0; pyq--) {
			continue;
		}
	}
	return string("zfgnjkntlenamqwehq");
}

int dmimykl::hugprcmzxabyvxdw(double hifejqpqxvwpysw) {
	bool wizsxmlll = false;
	double avaltag = 79918;
	string wvdprgtm = "fewybczvewxvonsehoh";
	if (string("fewybczvewxvonsehoh") == string("fewybczvewxvonsehoh")) {
		int lciu;
		for (lciu = 20; lciu > 0; lciu--) {
			continue;
		}
	}
	if (false != false) {
		int bxmzzryfb;
		for (bxmzzryfb = 45; bxmzzryfb > 0; bxmzzryfb--) {
			continue;
		}
	}
	if (79918 == 79918) {
		int bzlbrzewa;
		for (bzlbrzewa = 20; bzlbrzewa > 0; bzlbrzewa--) {
			continue;
		}
	}
	if (79918 == 79918) {
		int vrgbm;
		for (vrgbm = 29; vrgbm > 0; vrgbm--) {
			continue;
		}
	}
	return 46974;
}

int dmimykl::tskoesmrvuzz(string eafonhzyyelnav, bool vsxlksimx, int nvjhmkodvuxdxc, double bcizfsbpastrs, bool tkksugcjxqbdj, int jtgtwkbfnexc, double tiwravstfhrs, bool hrbiiafxibcse) {
	double sokniu = 27126;
	int lcrvscl = 914;
	int gpstdesvcr = 209;
	double edmmwty = 20978;
	double lrzphykbhuz = 855;
	bool qcvgexxs = true;
	int ysyizi = 1447;
	if (1447 != 1447) {
		int wjbyuz;
		for (wjbyuz = 53; wjbyuz > 0; wjbyuz--) {
			continue;
		}
	}
	if (914 == 914) {
		int ifevnu;
		for (ifevnu = 90; ifevnu > 0; ifevnu--) {
			continue;
		}
	}
	return 73990;
}

bool dmimykl::gdhyrtecmcybzdo(double yjuaewnbcwj) {
	int ctrwpessye = 7425;
	int cgfrhnnyyq = 1608;
	int qiqiobignbc = 2078;
	int mfnbquujjh = 967;
	string ffdupmivhmaf = "qilqyqiu";
	string pouyiftgwtj = "dqklokhgbghsuiypepjweebxdnahptuistycsrryo";
	bool fnoznqpijqll = false;
	string ddqagnxbzmlur = "bkhftoidf";
	return false;
}

void dmimykl::pkmadsmdaujbstyztp(bool aspgbalmm, string znjgasidnpyu, string qrvddfum, int kdentpana, bool greitpgm, double wajrtaowlwfn) {
	string fihblgx = "qaqixfolxnokrjn";
	string tmarylhpc = "pcttrfsgtpveorkaymlcmsqltgxmjergtcuydmndhtsqcqamaehtfsconqajwpnderxzuxsqbhajjegpeof";
	double woukiryxlsnw = 7540;
	bool dcrgu = true;
	double rgdkrhek = 1461;
	string davtdjom = "lnvgajcywxarrwdctupkyxkuwtldbqsjfopawuezqvxgqbannqkyijjjmqciqahybnlmgqzizdrknpatxwul";
	int vertftcbni = 77;
	if (string("qaqixfolxnokrjn") == string("qaqixfolxnokrjn")) {
		int auninclptg;
		for (auninclptg = 72; auninclptg > 0; auninclptg--) {
			continue;
		}
	}

}

int dmimykl::rgocnaxzrrdykibnkgur(bool qchjyxu, string xejkzm, int zyiubethoa, int iebqnmpjup, int vqyfqnobsp, int wotzorcirdy, string nilnsjhiytj, double wdztfqc, int hjrwnapkvhzezmg, int rrhegofgkb) {
	string zoysoxrtckgnscc = "qnxmsxdyznngicckaywipxgasciczrokuret";
	bool chlpxitwglxxja = true;
	double pjtagg = 818;
	bool glhatpiwxbd = false;
	int fdqqojj = 1693;
	int uvevkcaskoiao = 737;
	int mqjgpvh = 106;
	if (818 == 818) {
		int nvrkgo;
		for (nvrkgo = 61; nvrkgo > 0; nvrkgo--) {
			continue;
		}
	}
	if (string("qnxmsxdyznngicckaywipxgasciczrokuret") != string("qnxmsxdyznngicckaywipxgasciczrokuret")) {
		int dhpd;
		for (dhpd = 41; dhpd > 0; dhpd--) {
			continue;
		}
	}
	if (737 != 737) {
		int fifcqovpim;
		for (fifcqovpim = 88; fifcqovpim > 0; fifcqovpim--) {
			continue;
		}
	}
	if (106 == 106) {
		int zmdx;
		for (zmdx = 60; zmdx > 0; zmdx--) {
			continue;
		}
	}
	return 16774;
}

string dmimykl::hvmxcanbskbwirpr(int pbivfv, bool prxewwb, int zasapvbrffstm, bool mlfscvgalgmho, string tcynjgj) {
	string tdxvckndxeovwe = "unpkjl";
	double ajkefajbmdwpzm = 17482;
	int ofaxeu = 2405;
	string wrnnsanhxpxfb = "iqtpowznlmcapolcmrjzmqzewyokfeppnzlahmudcrvcij";
	bool acpoph = false;
	double scxjmxvx = 28561;
	string fiwfmsyfotsb = "ukqprjvzxkejptaiadqdgckgoysndmcddmhtaahebpyluelkwcvvmycrqvjvewmyzvqknyhltyalufdq";
	bool udwiybnzr = false;
	double zejcmdfvdgm = 46694;
	if (false == false) {
		int wfkqe;
		for (wfkqe = 38; wfkqe > 0; wfkqe--) {
			continue;
		}
	}
	if (false != false) {
		int mktwiamghs;
		for (mktwiamghs = 65; mktwiamghs > 0; mktwiamghs--) {
			continue;
		}
	}
	if (string("ukqprjvzxkejptaiadqdgckgoysndmcddmhtaahebpyluelkwcvvmycrqvjvewmyzvqknyhltyalufdq") != string("ukqprjvzxkejptaiadqdgckgoysndmcddmhtaahebpyluelkwcvvmycrqvjvewmyzvqknyhltyalufdq")) {
		int plqog;
		for (plqog = 24; plqog > 0; plqog--) {
			continue;
		}
	}
	if (string("unpkjl") == string("unpkjl")) {
		int cho;
		for (cho = 38; cho > 0; cho--) {
			continue;
		}
	}
	return string("wyhymtcalbtxavgdset");
}

void dmimykl::ieraxjoexwx(string spxhklllivjastd, int zhbagmgvr, int rygpnwsgyicksrl, string bjccmcal, bool cbqymfzwuiby, bool cmietdfrnx) {
	bool jigtgmnchd = true;
	if (true == true) {
		int bukeuxpiu;
		for (bukeuxpiu = 27; bukeuxpiu > 0; bukeuxpiu--) {
			continue;
		}
	}

}

bool dmimykl::nwehetcaujkktjwe(int ouhggyoh, bool dvzkpslimqgljuo) {
	bool uyznonbffinbh = true;
	double uerqkq = 3577;
	int xgreyb = 2039;
	int nrpeinnpqc = 200;
	int wtbrujibnbkj = 5049;
	bool jcylnstrvrzaur = false;
	double aeeifiakhdhqctx = 16485;
	if (5049 == 5049) {
		int xy;
		for (xy = 4; xy > 0; xy--) {
			continue;
		}
	}
	if (16485 != 16485) {
		int teksevyd;
		for (teksevyd = 86; teksevyd > 0; teksevyd--) {
			continue;
		}
	}
	if (3577 == 3577) {
		int qke;
		for (qke = 98; qke > 0; qke--) {
			continue;
		}
	}
	if (200 == 200) {
		int tfto;
		for (tfto = 83; tfto > 0; tfto--) {
			continue;
		}
	}
	if (false == false) {
		int tfgis;
		for (tfgis = 6; tfgis > 0; tfgis--) {
			continue;
		}
	}
	return true;
}

dmimykl::dmimykl() {
	this->ieraxjoexwx(string("hggvkdchkrznsvmkwrwsvkwrjryutjhtabjxlyehrvjnuvqthtizzkkhitzzegydfpb"), 3697, 749, string("volcgxujodiryszbgzaiqhrtdbab"), true, true);
	this->nwehetcaujkktjwe(7383, false);
	this->dorvrnatvwdhfxeg(4283, 72486, 7170, 3980, 73704, 3197, 4019);
	this->aqfghywpgfdxvh(string("rdzfdcvzqpkckrzlmnfpgtgtllrryxiondikoxhpqefeefgsto"), 5116, true, string("amkkrbfrlbzuewwpckbfvu"), 1000);
	this->dmjnpulxyavmmjunbzx(false, 4381, 91039, string("pkkjtqucfzcttlbnxbhcjirfcryyzygowiqqmwjbumkjqhhktalwyhchicakoyztpbzptryuoxipszbnszddeggp"), string("fzmguhsoukysqrivoqvhpkzpfvylhebdlwbekjbjfstujmcytzhmprjdozoda"), string("hspdtpmplozsdoxm"), true, 266);
	this->bqcacfgkozjsywsg(4728);
	this->hugprcmzxabyvxdw(10747);
	this->tskoesmrvuzz(string("lwntgvtkfxtickhwdqwlsogyxwtamab"), false, 2276, 42831, false, 1950, 6571, true);
	this->gdhyrtecmcybzdo(4617);
	this->pkmadsmdaujbstyztp(false, string("nofmquidyumwljbzolulmjtlyxktucogxkekjtupwjccawqvobgrlu"), string("ajskhjlecefplcetoivnjkfhbvtwvymd"), 1772, false, 3003);
	this->rgocnaxzrrdykibnkgur(false, string(""), 3928, 191, 1904, 3683, string("ytrdkzllemzlnvtcffmwdrctajdzafgbepdduvakcbi"), 11493, 1842, 4661);
	this->hvmxcanbskbwirpr(5299, false, 1, false, string("kztzikgtdhoshc"));
	this->gxtczipvprxovxgqrbrrb(true, true, 1012, 1095, 2952);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class mwefyxi {
public:
	bool rfewrqnyx;
	string otcadvmw;
	string xdmwoxtbuviwkrj;
	bool ndoxaqncib;
	int ydrocvrwzeuact;
	mwefyxi();
	int kcskkbfsbcvzcatgbxbv(double ueiwlbbhrfij, bool putngnluvgx, bool mnpxd, bool zhatnuunkr, int omhbftwtld, bool rbllb, double jypumnzbdfhkwj, double kqraslkodhmcq);
	string zxpysxzrvkfujci();
	void upfgrhnnlbybzp(string jxhsgos, int ykvtggmoxxodwq, double pcvoxon, bool evfqxjsulvf, bool bujwuh, double csytzow, double xcviqkmqtz, string psfrlcimhtrepg, bool uevqmqertyi, bool hkhnwd);
	string tzrjpmuiush(double nfqcfeiqvz);
	bool ctnzexjqnmvptic(double dvcweekzfu, string rjbdfjaylzyj, int wmzgvn, double hylfcqdfyvepni, string equyccegl, string fkyji, string gzysvmr, double bhyzt, double xmmqoccsx, bool dagcd);
	void hyjmhbvycmrwrcs(bool saxqzev, double ygtsba, bool bqmztnhvxvbcsn, bool osvfshwvn, double wyaihmgb, string yfugyclylhhqgrv);

protected:
	double ltxsvotxanwuges;
	int hswhjcajkqw;
	string nhijqdejfoyxec;
	bool ofqgvke;
	double pzdlmehqglth;

	bool osdtglvarxhbvr(bool wwhexcyfigx, double zklzmxydrkslko, string hxuevdlfx, string whadefsar);
	string ipqnhimwllochyezn(string czdgm, int kbvluhg);
	string mofrfiznian(bool iofezpfi, bool ktgfcgoaokzmct);
	double pxknmiecborspe(double xiepcjccll, double thzaztabjgr, int xzmqnpzyyniq, string vmkkltfgiv, double spoebfyswsio, double dzqsxoztaxd, bool lpmkypjenxkzm, bool zndmbhygjw);
	int woygwycmwksfpimcbhwyvznt(string cavtahhsrjqgsw, bool evcakidpmip, string ghiagpokk, bool mbtlwreigt);
	bool dleqtcwxbewesavi();
	double exhozxwcdumdwdreqkwhrff(bool cmblctjse, bool hkcnbg, double vgxtnvl, int iwfitxtdyjwwbix);

private:
	int ghpsab;
	string xfskspupineqwo;
	string nucqbryteosrrwt;

	int hdbxtutzovgajpaqbjey();
	string xbondiggqldojigpb(int eklytwbwxanenv);
	void dlsshfkoyq(bool tgxythqgb, int lizsrxlzzuaie, double ndlluwfsbavrvnm, bool zczzl);
	int wqcqudwacytlyoigfctcoa(double cdcsed, double oqfmdiwsyrixg, int djngfqvzkmgko);
	int uxtxqakwqgffkhfqpk(double fkrkjfoovmrolbb, int ngvtlskbkgczmn, string jpbfqdkcrqiuguu, string rilcwrwylv, int usmuzqf, bool ndjvlum, bool cvyculpggdvsc, double qkvcmomcqufag, double iuwtlmpnfdkxy);
	string hmbquigztggsvvrmisoefhe(int jkogopkqmsa, bool mzcnkgoatrxv, string fudnk, bool pxbhwug, double zvztbqwsfatgkmk, bool hethow, int mmspsqd, int llbaghkzgrqdguv, double fxatfxc);
	void plzxweozohhuhpvsf(int qzzefzagvcpawc, bool dqlqsjwphd, double jpifzyahwsie, bool egytcw, int gzchbimpprhhi, int fmptjsdzhpuktll, double jecae, double uzyppnq);

};


int mwefyxi::hdbxtutzovgajpaqbjey() {
	double chasmfplf = 30558;
	bool huemiefyzynq = true;
	double ugqriniz = 22451;
	bool khcheiswhdm = false;
	bool ratcotzhchqp = true;
	bool mdxgketdmu = false;
	string etiplitm = "ebqmxuwafmsvjctgchkxmwbmszghnjvwxsmptgiphwpnhjid";
	double vyqtaikh = 37204;
	string frffrcawbwdchew = "rfvlszy";
	int tkuvpadghvqbeyj = 2030;
	if (2030 != 2030) {
		int kplxnmwn;
		for (kplxnmwn = 84; kplxnmwn > 0; kplxnmwn--) {
			continue;
		}
	}
	if (false == false) {
		int rjuw;
		for (rjuw = 43; rjuw > 0; rjuw--) {
			continue;
		}
	}
	if (false != false) {
		int kza;
		for (kza = 42; kza > 0; kza--) {
			continue;
		}
	}
	if (false != false) {
		int sdlfwnhe;
		for (sdlfwnhe = 73; sdlfwnhe > 0; sdlfwnhe--) {
			continue;
		}
	}
	if (37204 != 37204) {
		int zh;
		for (zh = 6; zh > 0; zh--) {
			continue;
		}
	}
	return 27109;
}

string mwefyxi::xbondiggqldojigpb(int eklytwbwxanenv) {
	double dbsexjom = 19744;
	double mgyxbyqbuecocw = 65679;
	string dypzfxbexqnakcc = "vuevqpltmjwhaoroznscoolopnwfyreoyrmmxtxsvybopgseclolfomgotxlvvztkxadigmpvbpfbcbxndlcbrjajg";
	string wpnoxfjlz = "nyikppmbigesriccxsrbtgpfruttawtjwjnudokin";
	double qublyib = 1454;
	string wkhopzqkg = "jbvierkzgksadlzklpcaxxfvgfuyszxcnucaxhgadzycffilr";
	bool oojmgn = false;
	double bjmaoz = 50842;
	if (19744 == 19744) {
		int gimcceftdj;
		for (gimcceftdj = 79; gimcceftdj > 0; gimcceftdj--) {
			continue;
		}
	}
	return string("tcruqkqtriisveyx");
}

void mwefyxi::dlsshfkoyq(bool tgxythqgb, int lizsrxlzzuaie, double ndlluwfsbavrvnm, bool zczzl) {
	int aengqhrcsqfv = 421;
	double zqerfknfyewanip = 76433;
	int repekqtbglaa = 5608;
	string fccqjuwhya = "fjrfgnoczoeqpacem";
	bool bmwivcxctvpjs = false;
	if (76433 != 76433) {
		int chyoehrv;
		for (chyoehrv = 73; chyoehrv > 0; chyoehrv--) {
			continue;
		}
	}
	if (string("fjrfgnoczoeqpacem") == string("fjrfgnoczoeqpacem")) {
		int qjudcqc;
		for (qjudcqc = 8; qjudcqc > 0; qjudcqc--) {
			continue;
		}
	}
	if (421 == 421) {
		int aobzpshp;
		for (aobzpshp = 77; aobzpshp > 0; aobzpshp--) {
			continue;
		}
	}

}

int mwefyxi::wqcqudwacytlyoigfctcoa(double cdcsed, double oqfmdiwsyrixg, int djngfqvzkmgko) {
	int jigcntptfc = 5235;
	int ytnogytkyxdfki = 1439;
	int bqfmkv = 1714;
	string twqydycy = "vnefhroexypiqfwptbrodxwabdoef";
	double yqllzpcvwm = 5386;
	string xuugqcuxt = "iuprdflgbmpismmalwomixgdnsmjhxycvxosbowktgfqvqsjzhkoiadphayeeqxdpaayimiqzsjbsewikockjcxepkildffvo";
	int jibkryskvhunlws = 407;
	if (1714 == 1714) {
		int lvge;
		for (lvge = 68; lvge > 0; lvge--) {
			continue;
		}
	}
	if (1439 != 1439) {
		int xgsqdoue;
		for (xgsqdoue = 87; xgsqdoue > 0; xgsqdoue--) {
			continue;
		}
	}
	return 38726;
}

int mwefyxi::uxtxqakwqgffkhfqpk(double fkrkjfoovmrolbb, int ngvtlskbkgczmn, string jpbfqdkcrqiuguu, string rilcwrwylv, int usmuzqf, bool ndjvlum, bool cvyculpggdvsc, double qkvcmomcqufag, double iuwtlmpnfdkxy) {
	return 23633;
}

string mwefyxi::hmbquigztggsvvrmisoefhe(int jkogopkqmsa, bool mzcnkgoatrxv, string fudnk, bool pxbhwug, double zvztbqwsfatgkmk, bool hethow, int mmspsqd, int llbaghkzgrqdguv, double fxatfxc) {
	bool nkwnwie = true;
	bool fongxr = true;
	int etxnghhbcqcvar = 7492;
	bool wzrxc = true;
	string calcswv = "sfzpefqxxhqhezxwa";
	int jxvurqyef = 1934;
	string owhejv = "xxxbmijfupsixfcaxloc";
	int oigpie = 479;
	double drcczjti = 36688;
	if (36688 != 36688) {
		int lajunkluao;
		for (lajunkluao = 22; lajunkluao > 0; lajunkluao--) {
			continue;
		}
	}
	if (true != true) {
		int waidexkjoa;
		for (waidexkjoa = 52; waidexkjoa > 0; waidexkjoa--) {
			continue;
		}
	}
	return string("");
}

void mwefyxi::plzxweozohhuhpvsf(int qzzefzagvcpawc, bool dqlqsjwphd, double jpifzyahwsie, bool egytcw, int gzchbimpprhhi, int fmptjsdzhpuktll, double jecae, double uzyppnq) {
	int qndxnt = 1627;
	double uinlwnxdhseawg = 26713;
	double unahljbxvc = 4472;
	if (4472 != 4472) {
		int fbrre;
		for (fbrre = 40; fbrre > 0; fbrre--) {
			continue;
		}
	}

}

bool mwefyxi::osdtglvarxhbvr(bool wwhexcyfigx, double zklzmxydrkslko, string hxuevdlfx, string whadefsar) {
	string uakdbbntsteyds = "nzblwvxhk";
	double zheenrbtfj = 4683;
	bool imqxwypbudpxf = false;
	double kkgpwutncfae = 37609;
	bool imtep = true;
	string dsjkatlm = "cpayrytiglwdlcrifznppxroarxzwwtzrxxjn";
	double xnjetj = 7753;
	bool zmfnsmgu = true;
	string gudinykbjdhdpmi = "uyvloxopmdxiinyosypehivnkfnnjihivuxvldlbgvbefflnygijuhszieskksbsex";
	return false;
}

string mwefyxi::ipqnhimwllochyezn(string czdgm, int kbvluhg) {
	double pxzijptlzladey = 47031;
	double zawaicpvzs = 31120;
	double jdildlold = 14837;
	double aoves = 40383;
	double grlolepjzjtr = 11364;
	bool pxpqr = false;
	bool juzbw = true;
	bool aizjfllovfldhqz = true;
	double jrwkhb = 31700;
	int waznzmjuwh = 3779;
	if (false == false) {
		int cgazrmf;
		for (cgazrmf = 91; cgazrmf > 0; cgazrmf--) {
			continue;
		}
	}
	if (31700 != 31700) {
		int nkkwyappqu;
		for (nkkwyappqu = 89; nkkwyappqu > 0; nkkwyappqu--) {
			continue;
		}
	}
	if (11364 != 11364) {
		int ijynvrrxpi;
		for (ijynvrrxpi = 7; ijynvrrxpi > 0; ijynvrrxpi--) {
			continue;
		}
	}
	if (false != false) {
		int uf;
		for (uf = 7; uf > 0; uf--) {
			continue;
		}
	}
	return string("xameikcggikiotqsuf");
}

string mwefyxi::mofrfiznian(bool iofezpfi, bool ktgfcgoaokzmct) {
	int rdqlye = 7132;
	bool wqobbzjikkpa = false;
	double hafwxh = 93725;
	bool pwhwpj = true;
	double hhjzhafvqkfaiie = 19860;
	int ynbqiqitckifssq = 3315;
	bool vstakrvss = true;
	double ktzkzsccmxth = 13470;
	double dzyohytbyfciyy = 9912;
	if (19860 == 19860) {
		int mvdwbzplx;
		for (mvdwbzplx = 51; mvdwbzplx > 0; mvdwbzplx--) {
			continue;
		}
	}
	return string("wboozypqffmthoprtlqj");
}

double mwefyxi::pxknmiecborspe(double xiepcjccll, double thzaztabjgr, int xzmqnpzyyniq, string vmkkltfgiv, double spoebfyswsio, double dzqsxoztaxd, bool lpmkypjenxkzm, bool zndmbhygjw) {
	bool axgoiupvu = true;
	return 92238;
}

int mwefyxi::woygwycmwksfpimcbhwyvznt(string cavtahhsrjqgsw, bool evcakidpmip, string ghiagpokk, bool mbtlwreigt) {
	bool sdmhuccokdvob = false;
	string sywjwelm = "eyvlprwrqbqbgktedrhbwqcahgjqvehrtkvykwlugqysngbdxqdcdnocmjp";
	if (false == false) {
		int hz;
		for (hz = 18; hz > 0; hz--) {
			continue;
		}
	}
	if (string("eyvlprwrqbqbgktedrhbwqcahgjqvehrtkvykwlugqysngbdxqdcdnocmjp") != string("eyvlprwrqbqbgktedrhbwqcahgjqvehrtkvykwlugqysngbdxqdcdnocmjp")) {
		int fphsdck;
		for (fphsdck = 47; fphsdck > 0; fphsdck--) {
			continue;
		}
	}
	return 88199;
}

bool mwefyxi::dleqtcwxbewesavi() {
	string qoydiwsu = "abjrevsyjmhuzhtvleazukadmpkuffqorrfsynoqkrwbbnupctjobqfneldategdfwjtyvoq";
	double xfvnvh = 45201;
	int azcmeuyug = 4233;
	return false;
}

double mwefyxi::exhozxwcdumdwdreqkwhrff(bool cmblctjse, bool hkcnbg, double vgxtnvl, int iwfitxtdyjwwbix) {
	double sqvkqqj = 11279;
	double usmdsln = 13483;
	if (11279 == 11279) {
		int ncjuxuuj;
		for (ncjuxuuj = 82; ncjuxuuj > 0; ncjuxuuj--) {
			continue;
		}
	}
	if (13483 == 13483) {
		int izoc;
		for (izoc = 26; izoc > 0; izoc--) {
			continue;
		}
	}
	if (13483 == 13483) {
		int phlhh;
		for (phlhh = 77; phlhh > 0; phlhh--) {
			continue;
		}
	}
	return 87739;
}

int mwefyxi::kcskkbfsbcvzcatgbxbv(double ueiwlbbhrfij, bool putngnluvgx, bool mnpxd, bool zhatnuunkr, int omhbftwtld, bool rbllb, double jypumnzbdfhkwj, double kqraslkodhmcq) {
	return 27586;
}

string mwefyxi::zxpysxzrvkfujci() {
	double zbttcyxghnesqbe = 7961;
	double bncon = 7515;
	string mpydyxvyebfxqo = "yedawhnrqhnvvtuwznhepwwxvpiyiwwzjotjbvqsbwatdkooltuuthaluxusfxijq";
	int tcldipxppqb = 2856;
	bool skptxj = true;
	bool hkogzjwt = true;
	string infhl = "hxqdklkfwvpk";
	string ndvgvjkhcnlpa = "bzhdgpcmytzhyyafrajglsvzkminjubyegomegbdorpufrfdytpvwdzhengbtoovmevjjhlnqjdaekhnnvotbmwfl";
	double qdcgipj = 33284;
	if (true != true) {
		int qihq;
		for (qihq = 17; qihq > 0; qihq--) {
			continue;
		}
	}
	if (string("hxqdklkfwvpk") == string("hxqdklkfwvpk")) {
		int opdn;
		for (opdn = 64; opdn > 0; opdn--) {
			continue;
		}
	}
	if (true == true) {
		int qqpzdvck;
		for (qqpzdvck = 20; qqpzdvck > 0; qqpzdvck--) {
			continue;
		}
	}
	return string("fxxmiwjdqeqtsjaoe");
}

void mwefyxi::upfgrhnnlbybzp(string jxhsgos, int ykvtggmoxxodwq, double pcvoxon, bool evfqxjsulvf, bool bujwuh, double csytzow, double xcviqkmqtz, string psfrlcimhtrepg, bool uevqmqertyi, bool hkhnwd) {
	int xpajf = 1366;
	double bljly = 31858;
	bool znnoeodzeu = false;
	string tyumifidghfgzn = "rykrbrsnzy";
	double xfoluhoguie = 25299;
	string znhnndrwbusmwh = "pvkeuhrmhuwzqfmryjgyzxzgueskquqsntsqrhfufyfdbkrkqfbohuptnynmufajkmdfddwodvxslsoznvyavsihqtocmqcvru";
	string jzktnll = "tswaijfbtagexszjfpojtogrnztzwgrtyhjvzgdlhxptqhuccyxgmbksbhcrhjv";
	string lauykcyl = "cimbtadhakpnskjunslgyaxyyjkmdgmualzzyxzpxvefephdfwdnarjyyejgpziu";
	if (false == false) {
		int vfsjcqsdf;
		for (vfsjcqsdf = 44; vfsjcqsdf > 0; vfsjcqsdf--) {
			continue;
		}
	}
	if (false == false) {
		int gmficxayi;
		for (gmficxayi = 88; gmficxayi > 0; gmficxayi--) {
			continue;
		}
	}
	if (string("tswaijfbtagexszjfpojtogrnztzwgrtyhjvzgdlhxptqhuccyxgmbksbhcrhjv") != string("tswaijfbtagexszjfpojtogrnztzwgrtyhjvzgdlhxptqhuccyxgmbksbhcrhjv")) {
		int phntj;
		for (phntj = 58; phntj > 0; phntj--) {
			continue;
		}
	}

}

string mwefyxi::tzrjpmuiush(double nfqcfeiqvz) {
	string neuzmlabfa = "q";
	int vxcpfebsuxmyf = 3148;
	bool kdtgb = false;
	int jmgvgbtyiteb = 4851;
	double ezizfcjie = 59391;
	if (4851 == 4851) {
		int wpjpap;
		for (wpjpap = 35; wpjpap > 0; wpjpap--) {
			continue;
		}
	}
	if (3148 == 3148) {
		int qcbgynbjdf;
		for (qcbgynbjdf = 20; qcbgynbjdf > 0; qcbgynbjdf--) {
			continue;
		}
	}
	if (false == false) {
		int dqfd;
		for (dqfd = 74; dqfd > 0; dqfd--) {
			continue;
		}
	}
	return string("b");
}

bool mwefyxi::ctnzexjqnmvptic(double dvcweekzfu, string rjbdfjaylzyj, int wmzgvn, double hylfcqdfyvepni, string equyccegl, string fkyji, string gzysvmr, double bhyzt, double xmmqoccsx, bool dagcd) {
	int qsutruc = 2780;
	double krpycxox = 15490;
	bool vxevieoaaxikf = false;
	double ozhjbhubt = 22423;
	string fpdmmghrbwqbp = "dzyponpevwbfvldkyrkpqqfgjlgfevukzjiqpqcslbxtokwfdiqbysowwmdwldsgwbzjmmurllnnsdehzubxnewjficjnjzssf";
	string tccvvwol = "edmraflxjfefzubyxfmrwcwsfxsfhsttehugbnnrospn";
	if (22423 != 22423) {
		int kyyzenabnh;
		for (kyyzenabnh = 18; kyyzenabnh > 0; kyyzenabnh--) {
			continue;
		}
	}
	if (22423 != 22423) {
		int iir;
		for (iir = 31; iir > 0; iir--) {
			continue;
		}
	}
	return true;
}

void mwefyxi::hyjmhbvycmrwrcs(bool saxqzev, double ygtsba, bool bqmztnhvxvbcsn, bool osvfshwvn, double wyaihmgb, string yfugyclylhhqgrv) {

}

mwefyxi::mwefyxi() {
	this->kcskkbfsbcvzcatgbxbv(10525, true, false, true, 508, false, 15160, 4807);
	this->zxpysxzrvkfujci();
	this->upfgrhnnlbybzp(string("dezfpfeinntvmpgqdguijpggvdsicwftmyseudgakjcxjexektozeengdqcrdnnrybz"), 1206, 27183, false, false, 14681, 10486, string("slqrjxyxtnfhfedupuczrpustwhvqlelyeohpwifa"), true, true);
	this->tzrjpmuiush(1055);
	this->ctnzexjqnmvptic(27931, string("qfhavzemqksjtxtyrqaberckpxnszytxajiiapdavktvocgdroezpkserykisjnjbntzmwsftbrjubnm"), 1541, 48400, string("tcmggnxcmhohagmlsobxdmtejiypobortsejhpqktonhurbfwvhhgroeibzjxvbnsimhyerbpmfvygelfeqpvzqqcf"), string("mpzknhwoffcflstdjbbwsyqcktlyrjjkdsmyafryivhvvlxcfzixsaneerwskddwklu"), string("ttntthhjldsaefdswfsdmzaybzdtxllltgfdwpchbkudttrtfzobqxtfrdpsieimrmqfinpcyacgcesxuytmyz"), 43254, 24581, false);
	this->hyjmhbvycmrwrcs(false, 3535, false, false, 13955, string("xapueasuztxunaiuhwtauxvvlztdfnkflinsknmrteppmcmjhqggcpvgmizljqggzgjkfftuxfc"));
	this->osdtglvarxhbvr(false, 49557, string("rxy"), string("ulv"));
	this->ipqnhimwllochyezn(string("vspynviktalryfjadfbzxjmdudfjnjhopyjlrtgyvahxmapcybyfrcphnkcjgridtcthljrqeelftwvjbtcckkjcyslpq"), 2034);
	this->mofrfiznian(false, false);
	this->pxknmiecborspe(13224, 9662, 688, string("ugpnxknepvdoupigvhxythbrzvorsfqqepuqhybzydmqzzdcmsgctrskdbhjv"), 13519, 10338, true, false);
	this->woygwycmwksfpimcbhwyvznt(string("dxotcnywvbjxxtkhjpzgtlmacswttwmeacusqohadoqrrsxlfuyxedrvthcjp"), false, string("oynrebmfuftmnlafrgvggrwylnklnmjiykmiqg"), false);
	this->dleqtcwxbewesavi();
	this->exhozxwcdumdwdreqkwhrff(false, true, 38554, 6390);
	this->hdbxtutzovgajpaqbjey();
	this->xbondiggqldojigpb(718);
	this->dlsshfkoyq(false, 3242, 1000, false);
	this->wqcqudwacytlyoigfctcoa(37475, 17281, 1548);
	this->uxtxqakwqgffkhfqpk(4566, 5108, string("gznecpbugdgcdmizdawtmogmeeuxtrzonpcauaapycwzrbvbkluwnnvdayzaxrjqbvpavhrjxbevnookhhtd"), string("eghvtmundknwquuwdfezvyuwncaicxyvdmeyozqcaqagdfdicvilffogjbpprchjxvbiyfaup"), 275, false, true, 60969, 21862);
	this->hmbquigztggsvvrmisoefhe(5915, false, string("tvasgcqewo"), false, 10471, false, 1997, 1757, 29279);
	this->plzxweozohhuhpvsf(2262, false, 23512, false, 499, 1081, 6537, 9604);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class qmnpxmk {
public:
	int bozhwcgcbmy;
	string fyqzhwwcoachw;
	string llxdwgtubqr;
	qmnpxmk();
	string ihfeyxwykrtmsmugs(int lwjvim, int jpnrmmc, double dvbibvashszq, double kakfcakvxsgw, bool ieolpfqytyprms, int dqnmgb, string ywjpsfgvj, string manyaglxxcshale);
	string arhaqdifuxfhgiapg(double pcjhyireebwg, int srludshx, int buyjfou, bool itmmv, string zompkvabmze, string zypymhunnbwovhf, double uzejsxyb);
	int ttuaffdzoiyoqdvzfb(string quviz, double cexuqfmw, bool ejugaqffx);
	void tyojlopdvc(int uzraukud, double fbuvrrssmwmzntw);
	bool dxwkvtjpmvgkykxgxpzxq(int lqfeaui, double srhqohdwfprmlry);
	int uazadtinakmisyjeia(string yfbiokhihjcn);
	bool khwcbevkgotxqf(double jwysawtjwx, bool anuucyxbw, int upxqrxxd, string tdcvj, string krsknpkawdgve);
	string ehwhfnhqyntxgkpclyxv(double gentiqyo, double xhlho, double ytiifplwofapq, bool jdsqtukbdqo, int ekizjklcj, string rimxozuef, int cjxreuvateexqsc, int ddvyfvsm, int pqcruounn);
	string hmyiagpareqw();
	string nmijnmpysfd(double jfdjjad, int lptmm);

protected:
	string khhlk;

	int pzofgkeksqcofwkisqor(double wzriodiyxkm);
	double gtyzxrhbxpqyoqupgomkpsmi(int gamlu, string tdiahwqi, string mlufsp, string vsuwuj, string sftmncbx, string vmdfq, double qceekzcqbdzjpu, double bhdvfqu, int vltuf);
	bool zksbyumdnv(int kxwyvqbbhlzv, double sxbxhennb, int ufgsoxogupenb, double ryubrtazd, double ubrtbkqiowzon, bool wxqyagn, int ljqmpjwxvrx, int pkdij, int cjsyi, int visjwgzzobf);
	double uebbpninoazzspwzpmul(double xfiaewzuwva, string ykbdorjehydqc, double uvhmmjbs, int wvfmedg);
	int dfozqnvcepizummctpzr(double asbiastpj, int gvtuzfzlhzlfd, string mzdintsiklur, string xyggwcn, bool pmncpq, int tjxnieplqdnu, bool oaixdyjwcvbtir, bool ntduluxo, string pftuvmwdhqfxl, int iqgjpalgkx);
	string krfheaglxktrntihjgo(double korstnkgtngou, bool umhkrjivwta, bool hcbfbzkyocfuprl, int osflwsixpvwfl, bool prjrtecxjy, int irpcm, string fiqttsqxyj, double xljvvfsd, string iwqocqf);
	int zcsdpssxolptqasbzcjchr(string cllnpzqxuosjn, int iwypuwpzido, string zesfyduhucvmwf, string knrxyxs, bool vvfls, double mqwhtb, string txtzqfessq);
	int ztxyaxxcvtd(int wphfqttgaglyqy, string fuuplsakzekhr, double nnfkstdfcdk, int fcrzlfbkvfoirbk, double fwesjzv, double xfxhyyzuebe);
	double etuzvqjfvpmcqjutoqzttfn(double fpbwaazgsrhdd, string oloiiiplachp, int kxhibrgtvkmuk, int miavhbowuxogmgp);
	int ubctunuqhrrjddoixd(int sjeuvhses);

private:
	double mvgjvrtpbjytxe;
	string rhitzteyj;
	bool xiasb;
	double oxrjprckidli;

	int wigapiimqlrndrhdynb(int nwvjjkcewgefcj, int kialjicwtuisgo, double eprrn, bool grgxfg);

};


int qmnpxmk::wigapiimqlrndrhdynb(int nwvjjkcewgefcj, int kialjicwtuisgo, double eprrn, bool grgxfg) {
	int kkdcszbtfm = 1351;
	string orwwsjh = "ybdxptyooplcgbxyonnwkizwkucbqpwgzfhnniptf";
	bool zucimlkdxcae = true;
	bool roefhtrh = true;
	string hanbbru = "rahtwpqalenvujamwd";
	return 27413;
}

int qmnpxmk::pzofgkeksqcofwkisqor(double wzriodiyxkm) {
	string jsazpdlchd = "uyvhwxaqdtacjilnmoutxmdgfwzoygtqebupzwjrjfrgfxihf";
	string incezimopf = "zzrdnlablfvowqtpbofrngkseyqrivlozgka";
	string sboxmohxur = "ncfqmdxsqiuhmkbogdqxixcstpjjwtcvclgrxeqyjvig";
	bool dfuhizceeaw = true;
	bool bjitxuzvgtrvj = true;
	bool cwurbmlkwo = false;
	string yqmwtcahb = "oukuqinoonbgef";
	bool nrpbzjke = false;
	double ahjrthxap = 14267;
	if (string("ncfqmdxsqiuhmkbogdqxixcstpjjwtcvclgrxeqyjvig") != string("ncfqmdxsqiuhmkbogdqxixcstpjjwtcvclgrxeqyjvig")) {
		int zphtammfp;
		for (zphtammfp = 70; zphtammfp > 0; zphtammfp--) {
			continue;
		}
	}
	if (true == true) {
		int qq;
		for (qq = 17; qq > 0; qq--) {
			continue;
		}
	}
	if (true == true) {
		int rkhbzkeetw;
		for (rkhbzkeetw = 56; rkhbzkeetw > 0; rkhbzkeetw--) {
			continue;
		}
	}
	if (string("zzrdnlablfvowqtpbofrngkseyqrivlozgka") == string("zzrdnlablfvowqtpbofrngkseyqrivlozgka")) {
		int bf;
		for (bf = 54; bf > 0; bf--) {
			continue;
		}
	}
	return 10023;
}

double qmnpxmk::gtyzxrhbxpqyoqupgomkpsmi(int gamlu, string tdiahwqi, string mlufsp, string vsuwuj, string sftmncbx, string vmdfq, double qceekzcqbdzjpu, double bhdvfqu, int vltuf) {
	string tuyehuxoufre = "gsiaqeofcuhwdutbrumzewhlvoujrxbfpxgxdsprpmwcnnfkpcswcylctshhldzggmdivmzwuqatnogbhyyqbaczsoav";
	bool wazqplisf = false;
	int xvowedgc = 2860;
	int iokwd = 936;
	bool mbplcvlne = false;
	string fdsypgacctpmr = "gtwcjwkvlniuohzeccdweeysztjtolsgautbqpxyvpjbvphdpvyvfqlrelvrwwpleodfxtosreudlxnpnwvxnlkfhqx";
	string uvolrgmgoqhthfl = "flykjbwdepmexpjrelyxvzulhlilvxvoqhjfpphdrjuqhdltbpkiarmiaqtnayhnndejkzjudqfknsdkci";
	int ldqmkgzrqlti = 4419;
	double wlxbhragdzlvt = 86892;
	string nhnengpcrxu = "ijqdzgvnbiwuiciitazbtnoks";
	if (string("ijqdzgvnbiwuiciitazbtnoks") == string("ijqdzgvnbiwuiciitazbtnoks")) {
		int ngepbhpvl;
		for (ngepbhpvl = 34; ngepbhpvl > 0; ngepbhpvl--) {
			continue;
		}
	}
	return 18084;
}

bool qmnpxmk::zksbyumdnv(int kxwyvqbbhlzv, double sxbxhennb, int ufgsoxogupenb, double ryubrtazd, double ubrtbkqiowzon, bool wxqyagn, int ljqmpjwxvrx, int pkdij, int cjsyi, int visjwgzzobf) {
	bool yerotjcgexcrs = false;
	double efkhoyslofqzqsa = 14801;
	if (false != false) {
		int xfylykbqsy;
		for (xfylykbqsy = 42; xfylykbqsy > 0; xfylykbqsy--) {
			continue;
		}
	}
	if (14801 == 14801) {
		int hixazlktis;
		for (hixazlktis = 56; hixazlktis > 0; hixazlktis--) {
			continue;
		}
	}
	if (14801 == 14801) {
		int mrsxmyefx;
		for (mrsxmyefx = 50; mrsxmyefx > 0; mrsxmyefx--) {
			continue;
		}
	}
	if (14801 == 14801) {
		int ynpdo;
		for (ynpdo = 53; ynpdo > 0; ynpdo--) {
			continue;
		}
	}
	return true;
}

double qmnpxmk::uebbpninoazzspwzpmul(double xfiaewzuwva, string ykbdorjehydqc, double uvhmmjbs, int wvfmedg) {
	bool rlpjasy = true;
	string wuelcvyfkusamzq = "buwbnzglaigckhozhfsygcpvywsqvfywcecymxfmbzvwfjmqlrrekyzilahhznnv";
	int azcubqwux = 4294;
	string ijhttqyaglgs = "easnhzhffusmatovvbodcljpeopgqspm";
	bool wurqa = true;
	bool jvwbduulwfcyz = true;
	if (4294 != 4294) {
		int kcdmfp;
		for (kcdmfp = 44; kcdmfp > 0; kcdmfp--) {
			continue;
		}
	}
	if (4294 == 4294) {
		int etxnhgauk;
		for (etxnhgauk = 88; etxnhgauk > 0; etxnhgauk--) {
			continue;
		}
	}
	if (true == true) {
		int kyxxqcar;
		for (kyxxqcar = 8; kyxxqcar > 0; kyxxqcar--) {
			continue;
		}
	}
	if (true != true) {
		int na;
		for (na = 24; na > 0; na--) {
			continue;
		}
	}
	return 55816;
}

int qmnpxmk::dfozqnvcepizummctpzr(double asbiastpj, int gvtuzfzlhzlfd, string mzdintsiklur, string xyggwcn, bool pmncpq, int tjxnieplqdnu, bool oaixdyjwcvbtir, bool ntduluxo, string pftuvmwdhqfxl, int iqgjpalgkx) {
	int jaatceedrbnjsja = 5966;
	int pylarrvnexvhlyx = 124;
	double ipxydppgoz = 2363;
	bool fozvxcqbjkqici = true;
	if (2363 != 2363) {
		int nqqvbjjmqa;
		for (nqqvbjjmqa = 14; nqqvbjjmqa > 0; nqqvbjjmqa--) {
			continue;
		}
	}
	if (true == true) {
		int tiuz;
		for (tiuz = 92; tiuz > 0; tiuz--) {
			continue;
		}
	}
	if (true != true) {
		int qwtnlqbvl;
		for (qwtnlqbvl = 93; qwtnlqbvl > 0; qwtnlqbvl--) {
			continue;
		}
	}
	if (5966 == 5966) {
		int iwbxfhayrd;
		for (iwbxfhayrd = 44; iwbxfhayrd > 0; iwbxfhayrd--) {
			continue;
		}
	}
	return 93869;
}

string qmnpxmk::krfheaglxktrntihjgo(double korstnkgtngou, bool umhkrjivwta, bool hcbfbzkyocfuprl, int osflwsixpvwfl, bool prjrtecxjy, int irpcm, string fiqttsqxyj, double xljvvfsd, string iwqocqf) {
	double yjagi = 13581;
	if (13581 != 13581) {
		int squmnpmk;
		for (squmnpmk = 13; squmnpmk > 0; squmnpmk--) {
			continue;
		}
	}
	if (13581 != 13581) {
		int iywgmvej;
		for (iywgmvej = 7; iywgmvej > 0; iywgmvej--) {
			continue;
		}
	}
	if (13581 == 13581) {
		int hjgly;
		for (hjgly = 0; hjgly > 0; hjgly--) {
			continue;
		}
	}
	return string("pwrizjyhvqflny");
}

int qmnpxmk::zcsdpssxolptqasbzcjchr(string cllnpzqxuosjn, int iwypuwpzido, string zesfyduhucvmwf, string knrxyxs, bool vvfls, double mqwhtb, string txtzqfessq) {
	double doxpc = 1086;
	int eejga = 2041;
	string kjagq = "ccmivxnffpvz";
	double ikdyl = 27764;
	double ewdeiq = 6008;
	bool jnhaxvdbcrd = false;
	double hyydulnkxxxknt = 78047;
	int gvhcgtmr = 6275;
	if (6008 != 6008) {
		int uu;
		for (uu = 87; uu > 0; uu--) {
			continue;
		}
	}
	if (1086 != 1086) {
		int ml;
		for (ml = 5; ml > 0; ml--) {
			continue;
		}
	}
	if (string("ccmivxnffpvz") != string("ccmivxnffpvz")) {
		int ldvn;
		for (ldvn = 88; ldvn > 0; ldvn--) {
			continue;
		}
	}
	return 73598;
}

int qmnpxmk::ztxyaxxcvtd(int wphfqttgaglyqy, string fuuplsakzekhr, double nnfkstdfcdk, int fcrzlfbkvfoirbk, double fwesjzv, double xfxhyyzuebe) {
	string fpgzkhmkfm = "nekydxcyngevlwwpuupxlhjul";
	double ssvfly = 13448;
	bool iazqshtsdraw = true;
	double hqfavnxagfu = 29442;
	double ufdmuygkvqfyuye = 6708;
	int rhsgokfxipyexj = 8664;
	string xvchspnjpvathd = "";
	double gbbmp = 42640;
	if (string("nekydxcyngevlwwpuupxlhjul") != string("nekydxcyngevlwwpuupxlhjul")) {
		int pyablcylmf;
		for (pyablcylmf = 69; pyablcylmf > 0; pyablcylmf--) {
			continue;
		}
	}
	return 66243;
}

double qmnpxmk::etuzvqjfvpmcqjutoqzttfn(double fpbwaazgsrhdd, string oloiiiplachp, int kxhibrgtvkmuk, int miavhbowuxogmgp) {
	double jgbdlys = 8058;
	if (8058 == 8058) {
		int dlcrdmp;
		for (dlcrdmp = 82; dlcrdmp > 0; dlcrdmp--) {
			continue;
		}
	}
	if (8058 != 8058) {
		int qq;
		for (qq = 63; qq > 0; qq--) {
			continue;
		}
	}
	if (8058 == 8058) {
		int tswyw;
		for (tswyw = 66; tswyw > 0; tswyw--) {
			continue;
		}
	}
	if (8058 != 8058) {
		int ufsjhgc;
		for (ufsjhgc = 2; ufsjhgc > 0; ufsjhgc--) {
			continue;
		}
	}
	return 17627;
}

int qmnpxmk::ubctunuqhrrjddoixd(int sjeuvhses) {
	string gifovdbyjmp = "egzyaubdkvjzfkkvbnlagclnafjkoxsgukhhfdbghorluchikfvsitcggzejpczdkvvanzuvgfziochhyvarmxdxhfis";
	bool fbfrjngwyytv = false;
	string jzzfzujajwgjys = "lvjhyliisircjejzmduzhhbspedmuicqohqqxnrvxmpdqgawgzkgtxfhdolkzfgrwycxrvlnqmuswdzlqqaekbgn";
	string tuahyvezvszcrx = "jvexacviukdwpxgwnhmosncealuxgnbievbtiejxwtmptiglxrvsxeflstiwapzsjlqzortvpmldknhkjmdwcadu";
	double mamabxxwh = 36144;
	int uwcbdtiyggumnk = 1702;
	int gmnnmmmyh = 821;
	bool jchkod = true;
	if (false != false) {
		int crrcldo;
		for (crrcldo = 7; crrcldo > 0; crrcldo--) {
			continue;
		}
	}
	if (string("lvjhyliisircjejzmduzhhbspedmuicqohqqxnrvxmpdqgawgzkgtxfhdolkzfgrwycxrvlnqmuswdzlqqaekbgn") == string("lvjhyliisircjejzmduzhhbspedmuicqohqqxnrvxmpdqgawgzkgtxfhdolkzfgrwycxrvlnqmuswdzlqqaekbgn")) {
		int wrzbrois;
		for (wrzbrois = 95; wrzbrois > 0; wrzbrois--) {
			continue;
		}
	}
	if (string("jvexacviukdwpxgwnhmosncealuxgnbievbtiejxwtmptiglxrvsxeflstiwapzsjlqzortvpmldknhkjmdwcadu") == string("jvexacviukdwpxgwnhmosncealuxgnbievbtiejxwtmptiglxrvsxeflstiwapzsjlqzortvpmldknhkjmdwcadu")) {
		int ign;
		for (ign = 59; ign > 0; ign--) {
			continue;
		}
	}
	if (string("jvexacviukdwpxgwnhmosncealuxgnbievbtiejxwtmptiglxrvsxeflstiwapzsjlqzortvpmldknhkjmdwcadu") != string("jvexacviukdwpxgwnhmosncealuxgnbievbtiejxwtmptiglxrvsxeflstiwapzsjlqzortvpmldknhkjmdwcadu")) {
		int imq;
		for (imq = 93; imq > 0; imq--) {
			continue;
		}
	}
	if (true == true) {
		int dnkdvbvz;
		for (dnkdvbvz = 13; dnkdvbvz > 0; dnkdvbvz--) {
			continue;
		}
	}
	return 6354;
}

string qmnpxmk::ihfeyxwykrtmsmugs(int lwjvim, int jpnrmmc, double dvbibvashszq, double kakfcakvxsgw, bool ieolpfqytyprms, int dqnmgb, string ywjpsfgvj, string manyaglxxcshale) {
	string qdqrkjngy = "qyynifrmz";
	int hjqlcsoifwnhejn = 4333;
	bool vjofprsl = false;
	int edtjm = 2584;
	if (false != false) {
		int jp;
		for (jp = 84; jp > 0; jp--) {
			continue;
		}
	}
	if (4333 == 4333) {
		int ocnultaov;
		for (ocnultaov = 97; ocnultaov > 0; ocnultaov--) {
			continue;
		}
	}
	if (2584 != 2584) {
		int fowdnhut;
		for (fowdnhut = 81; fowdnhut > 0; fowdnhut--) {
			continue;
		}
	}
	if (2584 == 2584) {
		int me;
		for (me = 72; me > 0; me--) {
			continue;
		}
	}
	return string("tcxwgiekatbfxuo");
}

string qmnpxmk::arhaqdifuxfhgiapg(double pcjhyireebwg, int srludshx, int buyjfou, bool itmmv, string zompkvabmze, string zypymhunnbwovhf, double uzejsxyb) {
	double usdbejslc = 49092;
	double wqroyz = 3990;
	int rpmeecattsnech = 1846;
	bool isjwendbgtahf = true;
	string yseanbxmeorfk = "hibdukkqvaqqkhacbckgcquklsvmmkbvomankwdwwybgaabetcqaplgdacytvbuiaariimyuwb";
	int zbpamwizgnlbrj = 224;
	double tdfjqzxqjewkcn = 30147;
	if (1846 == 1846) {
		int gsrlut;
		for (gsrlut = 95; gsrlut > 0; gsrlut--) {
			continue;
		}
	}
	if (3990 != 3990) {
		int hhuifr;
		for (hhuifr = 90; hhuifr > 0; hhuifr--) {
			continue;
		}
	}
	return string("xqiyefvowcrr");
}

int qmnpxmk::ttuaffdzoiyoqdvzfb(string quviz, double cexuqfmw, bool ejugaqffx) {
	double wkddo = 5568;
	bool uyzfhnhdhvf = true;
	bool ziiwbmdm = true;
	double nqgcwyvzrxno = 18247;
	double odsxhmksongke = 1284;
	bool ugwqiado = true;
	int qooucduvx = 3556;
	bool nuoxqiexuq = true;
	bool bbykkg = false;
	int reysy = 1618;
	if (true != true) {
		int zzo;
		for (zzo = 81; zzo > 0; zzo--) {
			continue;
		}
	}
	if (true != true) {
		int ynyywchih;
		for (ynyywchih = 82; ynyywchih > 0; ynyywchih--) {
			continue;
		}
	}
	if (true != true) {
		int drirangzoh;
		for (drirangzoh = 90; drirangzoh > 0; drirangzoh--) {
			continue;
		}
	}
	if (true == true) {
		int ambwvzkpkt;
		for (ambwvzkpkt = 46; ambwvzkpkt > 0; ambwvzkpkt--) {
			continue;
		}
	}
	if (5568 != 5568) {
		int uiqkfrj;
		for (uiqkfrj = 55; uiqkfrj > 0; uiqkfrj--) {
			continue;
		}
	}
	return 80435;
}

void qmnpxmk::tyojlopdvc(int uzraukud, double fbuvrrssmwmzntw) {
	string nslhkcsziuiv = "ziwpvueleqbsldssllywswllrjwptopdpnknluiqytmyr";
	string wkpvkpjarkywll = "jopservwgnpfbznsepgoyjzvobdpsehgkkjxrggeambajdeexfnlppiwdvgmcsevnobmpkqrlaat";
	string fniekopenscgv = "wuypexltcxmnbckrzazwlbhhhpyehsmk";
	string ijhxmrhjl = "voegcijpcxpdvlerkh";
	string dahvoev = "cxrfdttiomduyfkybkltgdcruzvirlmamikucxuvdjcjibygk";
	int ovlfaytzkudpb = 1617;
	bool gburyj = false;
	string khjfdao = "cgavmeergzuqrpsimvwbfytyvsronlnwsazmfxmreyzjilqngxmchyimbhiwidviydvnpikeilruecuxzeyacrcnazs";
	if (false != false) {
		int ei;
		for (ei = 36; ei > 0; ei--) {
			continue;
		}
	}
	if (string("wuypexltcxmnbckrzazwlbhhhpyehsmk") != string("wuypexltcxmnbckrzazwlbhhhpyehsmk")) {
		int tuwnjmdlhf;
		for (tuwnjmdlhf = 94; tuwnjmdlhf > 0; tuwnjmdlhf--) {
			continue;
		}
	}

}

bool qmnpxmk::dxwkvtjpmvgkykxgxpzxq(int lqfeaui, double srhqohdwfprmlry) {
	double yjywkuborpr = 18912;
	int gveqkq = 260;
	int tcptosncv = 882;
	double uzakg = 21119;
	double exhxdqalukfj = 19917;
	string zorkwrduhpkagqw = "htxgkyackbfclrzdtmqfrksessjdaayntjslghfuurvypohdaffzjljxumvngrgwvrjmvczeulzlnaifrcs";
	if (260 != 260) {
		int nfv;
		for (nfv = 10; nfv > 0; nfv--) {
			continue;
		}
	}
	if (19917 == 19917) {
		int yqxksqx;
		for (yqxksqx = 68; yqxksqx > 0; yqxksqx--) {
			continue;
		}
	}
	if (260 == 260) {
		int gkghsjf;
		for (gkghsjf = 66; gkghsjf > 0; gkghsjf--) {
			continue;
		}
	}
	if (21119 != 21119) {
		int be;
		for (be = 36; be > 0; be--) {
			continue;
		}
	}
	return true;
}

int qmnpxmk::uazadtinakmisyjeia(string yfbiokhihjcn) {
	int fzssgbj = 3915;
	double otxmkltevnf = 81323;
	double ohcwcibaubktm = 42337;
	bool vijixevr = false;
	int spddmmzsqvjoq = 1271;
	bool lhvzdxcqdesfqfq = false;
	string vssqgleojytav = "kwapzbuzvfxwgpmfqeblafqfhutadzyenucbujheytifcfpt";
	int fwapxohtshkiyf = 1366;
	bool ijqemaejwkotfj = true;
	bool fmotusjiq = false;
	return 60686;
}

bool qmnpxmk::khwcbevkgotxqf(double jwysawtjwx, bool anuucyxbw, int upxqrxxd, string tdcvj, string krsknpkawdgve) {
	bool yajgrwxfoewduxp = false;
	string snqvhdagfyfjc = "invmcewdbcrdcjqxoxobdadqykccdktuysmcovyajzyvydmvtkizvlplupnsflsc";
	string akovpuocvmdzahy = "ehoenwoyycxszaovic";
	string ivcqwqf = "ircripeobrfqzhyntuozmxcrrdhqzdxdigmyrhevcchvtteaeaxvbvotqcajgkwthscyegcmkpypheypfzhihzysseuh";
	string mkwsnbwzzbyfbhl = "yloqobjwrpndvrazlvygrytzrwklhytrtjbtteqpzhprevki";
	double nyjtdxyiipukox = 15251;
	bool znmesrfqaajarfh = true;
	bool amslwsooxelsg = false;
	string slfxur = "jclstzjsnsymdqljslcicmdrleytejiclerboprwzxrakfkmlahfzfhnpztujtjqlfigathfpdrgcfvshaqzrypnjcsllyyk";
	bool cwkthoknys = true;
	if (string("ehoenwoyycxszaovic") != string("ehoenwoyycxszaovic")) {
		int clvy;
		for (clvy = 70; clvy > 0; clvy--) {
			continue;
		}
	}
	return true;
}

string qmnpxmk::ehwhfnhqyntxgkpclyxv(double gentiqyo, double xhlho, double ytiifplwofapq, bool jdsqtukbdqo, int ekizjklcj, string rimxozuef, int cjxreuvateexqsc, int ddvyfvsm, int pqcruounn) {
	double rqqjtbkdfx = 19793;
	double huoqputgawess = 5118;
	return string("srnkmwbbbkjqrongozz");
}

string qmnpxmk::hmyiagpareqw() {
	return string("clfmvhcrlvddapsyjz");
}

string qmnpxmk::nmijnmpysfd(double jfdjjad, int lptmm) {
	return string("gzfj");
}

qmnpxmk::qmnpxmk() {
	this->ihfeyxwykrtmsmugs(536, 2703, 6882, 10273, false, 2793, string("wmqecffirpvgschwnoemqzk"), string("ozjvbun"));
	this->arhaqdifuxfhgiapg(13533, 1141, 2258, false, string("qnzzrxugvdbngqhutghhotcprckalmbjqyomnijqzyzgbjntzvuowavicdiv"), string("njxpdhlkrvngsswftrneigz"), 38044);
	this->ttuaffdzoiyoqdvzfb(string("vhqgjcvnmxsoqettwpabyxjswwvjarzwgisbpuircefpnmlbx"), 45182, false);
	this->tyojlopdvc(1604, 30564);
	this->dxwkvtjpmvgkykxgxpzxq(562, 68045);
	this->uazadtinakmisyjeia(string("rixmffixkkfxfznlxdsgwbujqqxsbiriflahtduzvvrsxuohuhnrxwybgxjxzjdxdkixxcgeayiwchrxgbnyrfxhyspsjgfopeyn"));
	this->khwcbevkgotxqf(19750, true, 3137, string("xsxfyzrajxzfbyqaaygwstwvetfwazgfodifcxwitksafyxdhnqvgpcqfzdwyrhkuzugunyzojsxzmzfrppyhhem"), string("ihexskxjcapxonboorkafrxzieqjlxtwrhphafawasarzatsgjhnspitfohbzgsiyztjmogkfwoolwbzjhclfqhajvpemjuw"));
	this->ehwhfnhqyntxgkpclyxv(69965, 5767, 17978, true, 3616, string("rqmaiunbocfcgnwibxtaaicktirwuyaaobnzbpsrsycdytjrewwziithirngxoloiybpnjmgr"), 2916, 3004, 134);
	this->hmyiagpareqw();
	this->nmijnmpysfd(13467, 6895);
	this->pzofgkeksqcofwkisqor(9315);
	this->gtyzxrhbxpqyoqupgomkpsmi(1890, string("enpbehnfbszxcuzgwjkzjqlb"), string("imzrlpqgkkhjqotdfzzuzozoxnyfovejedlqtlvehayihzdqolilvxv"), string("wtfpnzzmgwnubncxuldaqkgrxnbfmizmaqloxlycjpjphvqbolobzcfllgopxjeqlvyueackumytuvcpajjbslxgbepz"), string("slgiqtrhrjmtdreoebvjkoxfswmwaiqulomfwgegdlkihsylqh"), string("jljvshkasiidiqlrrrcnhlngkhisfpmpktbrljdwuusvtplejpjhdbmyltgfjzwdaufwexvppbtorbeczkkqpdkzmjyeeodhif"), 12696, 14760, 6744);
	this->zksbyumdnv(953, 8592, 738, 21216, 47180, false, 5523, 561, 836, 2531);
	this->uebbpninoazzspwzpmul(4847, string("ahevotdcifwasvyuzinw"), 40323, 683);
	this->dfozqnvcepizummctpzr(4445, 3950, string("jdvvprexvcjtxnluvugkppvicvduupjbbrluacsxfnhomsrsgdy"), string("oqqepsmfwpusarqgonjsgionllumncclnayhvvrqqbmwqomtmxvgxxaqrmwgacqpjcxzhwbctlwaalyaesffuxprckanzzyb"), false, 4501, true, true, string("vrltxjaeoytbpgezonuljxmzshydgmfqgxnzgaxeipfgrlctrvaczlssyt"), 6808);
	this->krfheaglxktrntihjgo(81412, false, false, 4923, true, 2083, string("alxoyhhiwseatzffiaohcjubiqwttwip"), 56465, string("jrdbrxleuhhelwxmauultnuxvll"));
	this->zcsdpssxolptqasbzcjchr(string("rknrtygzaeoch"), 2304, string("mdeidwgdgqoyeymfppsbdpdnmknjxwwciitlqzwmvuikxnnhmcijzytvcuqtkdtdtrnsvgyh"), string("lsnimilmrqflbqygxqi"), false, 289, string("ypckqjrjzczoveueoqoogjvxephcawnlynekryvqlllhzuwlbumltgqponysqqb"));
	this->ztxyaxxcvtd(5217, string("xjwkkqjnspldnyuo"), 6909, 2626, 17081, 10122);
	this->etuzvqjfvpmcqjutoqzttfn(6448, string("udatrivrxzakzbrvrdimhdi"), 1029, 7573);
	this->ubctunuqhrrjddoixd(3452);
	this->wigapiimqlrndrhdynb(1142, 3730, 2989, false);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class lbaqlpu {
public:
	bool rfsfvgrqxjkkx;
	int qrtmmbbhgvwydym;
	int tkcxeowrndlw;
	lbaqlpu();
	double olyjyfqrhw(int pclul, int uqbob, double cqghnqd, double prstiwfldgsesrr, double tckmy, double vdsxat, string qtmclbqf, int xmzhulrbnl, string slfxnbaoxaew);
	double pzfuleoibnfqkcztbyly(string ioubuugbcl, string rflgggtgbmh, double bwdwocvf);
	double hgqsdiwqgxeylwe();
	string siqbmsxijibeelutwbxetch(string nqdonk);
	bool nqmkytadoseqyxikylxbp(string vvkvcial, bool aprrgqi, string vtiikjzzyy, string qdtnhjnuehooymn, bool rwvaejmhfigwvw, bool gjxzonlkwmhwone);
	double gqkdnwhwywwd(double hnkcij);

protected:
	int acyzrhrghvec;
	double ukyzlewr;

	bool skzogidtpf(string lydlbhdhdeibys, bool nxgxfqjdpm);
	bool ueeuusqgkuojcut();
	double pgfxdvbfljbrz(double mhwframrnjaeu, double exyxjtevly, string irkmdjsc, double hbgezbgvbmkbzt, string xcaeoyl, int cheglhaoe);
	string gezineqotrsxhoogpkktzxry(string zikolxjr, double cpdluowixrzd, double uimvnvpgqvjxne, string obqdisbji, bool rxklppuxhr, string vaxcljewgbfq);
	int qidqynzidaqpyhcq(double qgjinulwv, double lrqgxmko, bool jwlcetlbsuqsbfr, bool waeyibcvxr, bool iatohydr, double utvpsqpujnwer);
	double vrbxwipchaqkwzvuv(string vhbdcbkrrr, bool ydvfvxxkkwmiy, string akplpbbr, string clqdcafrga, double nnmtolbctfghkp, double qgxnc, string eujvlvczlaxx, bool vplizalxnakvx, int mxvfxit);
	void ryepjctkmocaedpgbwr(bool qgwwwrkfo, int qpmpv, bool gtdheoxpkbhperb, int ybatroo, double kxiepipn, bool bqumocfkay, double onmmflivoft, int sjiqi, string momtlispzng, double tieenjtku);

private:
	bool gafkhvtkwunuvk;
	bool pcaccvwifuftbht;

	bool isejgilwalku(string uzshducyxtbsjlm, string uuldvwee, string jpnisonmugvbhb, bool cofszhcaauqo, int jlanxhapmiz, int vgrdviv);
	void acmtjvpsin();
	void ckyahxzjqwyboxmvakwdn(bool kxksybysspj, string dhjzqy);
	int uxdwkmjdinlmdeuioyqh(string onbesxvekmvcfcb, double lqbugtq, int mnyogcy, int mplgqjdktulz, bool dfvuz, int hsiesu, string cbyjnox);
	string cpjjhseidhmgedkqjwism();
	bool zmawzdcgtfzyelvxkof(string vprnhcido, double utxzipuycjm, string pyrptfnqu, string ydrdgaiegod, int algbaaweb);
	int ipvsbhsfkfphjtwkzpgtb(double bmcszmkslebs, double ybfwlhjm, string roogjmtpynm, double yarzjaypkhafu, int nobrzcqlgeqztl, double nhwklvzeukc, bool uqhixsj, bool odocozye);
	double pylhbyaicjafjdpspfjdcgoo(bool qsqvnta, int ywzqod, bool rctkuoeay);
	bool aekifwisrzghtl(double oattlvoo, int ujsvn, double urxefnjf, bool ziqsefdfqq, int irfqwtriebtc, double rqeorjllhmpsvc, string ermfmzlvshrml);
	int dmddztjpvgxzkytnxcmvut(bool xuqrtkluzn, double itekswyksuh, double mmpapbnyctpxp, double dfoloqdvjahectj, string hfharlc, double juptvoyjtk, int avcibtssh, bool tamyvnhvskn, string gpvlhdcyeksglcr);

};


bool lbaqlpu::isejgilwalku(string uzshducyxtbsjlm, string uuldvwee, string jpnisonmugvbhb, bool cofszhcaauqo, int jlanxhapmiz, int vgrdviv) {
	bool vauhodtmaiayf = true;
	string ulgksx = "tejmuonkjlqrehrkawozzpjfvygvetdwxakqxgumhvigclpdrgctasximszbhjxg";
	if (string("tejmuonkjlqrehrkawozzpjfvygvetdwxakqxgumhvigclpdrgctasximszbhjxg") != string("tejmuonkjlqrehrkawozzpjfvygvetdwxakqxgumhvigclpdrgctasximszbhjxg")) {
		int pvhibibvw;
		for (pvhibibvw = 27; pvhibibvw > 0; pvhibibvw--) {
			continue;
		}
	}
	if (true == true) {
		int gfm;
		for (gfm = 3; gfm > 0; gfm--) {
			continue;
		}
	}
	return false;
}

void lbaqlpu::acmtjvpsin() {
	string ukvcmidf = "dcwnhgsqmyznrjrfnmf";
	bool jbsbofulkllklbv = false;
	double vglmvkjxbqmzsli = 67830;
	bool dypbsu = false;
	double plrazktqznexelg = 21021;
	bool qgujmwlfk = false;
	string einqksqjpcxjond = "xlgaykpcbaubqahgllwgntgmelhtjtcrnjebjcfiquxxudaemeuewkmealifwqunqubbjhrjrrqolzrckctuupsiqgjvuow";
	string bnlbpi = "nbwcjykfijsessryukprototsmiyynnoexdidhulwjorfh";
	if (false == false) {
		int dbjvro;
		for (dbjvro = 8; dbjvro > 0; dbjvro--) {
			continue;
		}
	}
	if (21021 == 21021) {
		int nkorseoda;
		for (nkorseoda = 74; nkorseoda > 0; nkorseoda--) {
			continue;
		}
	}
	if (false == false) {
		int icnb;
		for (icnb = 37; icnb > 0; icnb--) {
			continue;
		}
	}
	if (21021 != 21021) {
		int pyhtqz;
		for (pyhtqz = 38; pyhtqz > 0; pyhtqz--) {
			continue;
		}
	}
	if (string("xlgaykpcbaubqahgllwgntgmelhtjtcrnjebjcfiquxxudaemeuewkmealifwqunqubbjhrjrrqolzrckctuupsiqgjvuow") == string("xlgaykpcbaubqahgllwgntgmelhtjtcrnjebjcfiquxxudaemeuewkmealifwqunqubbjhrjrrqolzrckctuupsiqgjvuow")) {
		int lucblccw;
		for (lucblccw = 45; lucblccw > 0; lucblccw--) {
			continue;
		}
	}

}

void lbaqlpu::ckyahxzjqwyboxmvakwdn(bool kxksybysspj, string dhjzqy) {
	double xcmqf = 6950;
	bool syvjivmve = true;
	bool nlvdvqzj = false;
	string lzsynb = "gmuprezakiuutwbsxprrvswlborjylwcofweduzcoxaiykvtszlrtpmwcy";
	double ndnsk = 20449;
	bool vvssuawlbcpnmbk = false;
	bool vyiqpoloellq = false;
	bool swneyyda = true;
	bool ykaufb = false;
	if (true == true) {
		int ghr;
		for (ghr = 23; ghr > 0; ghr--) {
			continue;
		}
	}

}

int lbaqlpu::uxdwkmjdinlmdeuioyqh(string onbesxvekmvcfcb, double lqbugtq, int mnyogcy, int mplgqjdktulz, bool dfvuz, int hsiesu, string cbyjnox) {
	bool ihnunnswnosbe = false;
	bool nrwrjgmdtm = false;
	int zzihrcbl = 2637;
	string saaywt = "rxgjfkocmllqzyzqqlabqoy";
	double twqholcaejr = 37475;
	string nxcjist = "ymaukwwnfzhxcscszzfzhcwlnzflyevilnqbnigjthwwohwqmdqhpweztnyxxpfixtxtmvhli";
	int jieikct = 606;
	double xxygx = 4107;
	bool nccpwyyy = false;
	bool eswgkrj = false;
	if (2637 == 2637) {
		int ifac;
		for (ifac = 65; ifac > 0; ifac--) {
			continue;
		}
	}
	if (false == false) {
		int ngejjfiw;
		for (ngejjfiw = 32; ngejjfiw > 0; ngejjfiw--) {
			continue;
		}
	}
	if (2637 == 2637) {
		int jtkdrwqt;
		for (jtkdrwqt = 99; jtkdrwqt > 0; jtkdrwqt--) {
			continue;
		}
	}
	if (false == false) {
		int lsxfevcptb;
		for (lsxfevcptb = 80; lsxfevcptb > 0; lsxfevcptb--) {
			continue;
		}
	}
	return 73459;
}

string lbaqlpu::cpjjhseidhmgedkqjwism() {
	int norbevbbkftxkp = 1020;
	bool pgiaehpaqu = false;
	string vxjnyjvirkrob = "wlzjeyhgfgsewatdknkbtwkesxwolrsknvynxnhqhfxxunjrhxchmocgdxgpkryrrzofhebfxuhzvcuzoygfymoi";
	double odlyx = 34841;
	return string("z");
}

bool lbaqlpu::zmawzdcgtfzyelvxkof(string vprnhcido, double utxzipuycjm, string pyrptfnqu, string ydrdgaiegod, int algbaaweb) {
	string vtgsjcwse = "mhjcoypffehtkttwmzcgl";
	int biqqbkfgmxm = 1069;
	if (string("mhjcoypffehtkttwmzcgl") == string("mhjcoypffehtkttwmzcgl")) {
		int rdyzg;
		for (rdyzg = 3; rdyzg > 0; rdyzg--) {
			continue;
		}
	}
	return false;
}

int lbaqlpu::ipvsbhsfkfphjtwkzpgtb(double bmcszmkslebs, double ybfwlhjm, string roogjmtpynm, double yarzjaypkhafu, int nobrzcqlgeqztl, double nhwklvzeukc, bool uqhixsj, bool odocozye) {
	double yxdmywtdlj = 61907;
	bool etvjwcoux = true;
	string yfpkvlnvmypqeb = "ytqygcuenwifqffsuuibqzsiodiryggmqlzrmkmlnndwdtyzialkmyjrlykpxwbbbmxnjhnpxoeemjanxntmiswwbljlun";
	if (61907 != 61907) {
		int fm;
		for (fm = 60; fm > 0; fm--) {
			continue;
		}
	}
	if (61907 != 61907) {
		int qoodlx;
		for (qoodlx = 16; qoodlx > 0; qoodlx--) {
			continue;
		}
	}
	if (61907 != 61907) {
		int upwnfttec;
		for (upwnfttec = 1; upwnfttec > 0; upwnfttec--) {
			continue;
		}
	}
	if (61907 != 61907) {
		int lcwwij;
		for (lcwwij = 68; lcwwij > 0; lcwwij--) {
			continue;
		}
	}
	return 13650;
}

double lbaqlpu::pylhbyaicjafjdpspfjdcgoo(bool qsqvnta, int ywzqod, bool rctkuoeay) {
	double hbxrz = 37312;
	double gxdmrdaxbmkttad = 7347;
	double lwklykvuvla = 10343;
	bool mjhuzo = false;
	string ueggcmovmuuqf = "tsguvecbwwpqxlluuaznhoshhhjlmrpgipexopcgwxwkoxpebcdzrhuhjbduvgcozzecsbxepvofzyxqa";
	int ugbosjskwkb = 548;
	double fwxzff = 70840;
	bool njgxyq = true;
	double nazako = 85272;
	string lbxjkelx = "tpjpzjbahchqqmbngkaxuyzhzhgliteddikyqtmvaezaau";
	if (7347 == 7347) {
		int bkac;
		for (bkac = 8; bkac > 0; bkac--) {
			continue;
		}
	}
	if (string("tsguvecbwwpqxlluuaznhoshhhjlmrpgipexopcgwxwkoxpebcdzrhuhjbduvgcozzecsbxepvofzyxqa") != string("tsguvecbwwpqxlluuaznhoshhhjlmrpgipexopcgwxwkoxpebcdzrhuhjbduvgcozzecsbxepvofzyxqa")) {
		int vqsrschja;
		for (vqsrschja = 15; vqsrschja > 0; vqsrschja--) {
			continue;
		}
	}
	if (85272 == 85272) {
		int tdadbrk;
		for (tdadbrk = 81; tdadbrk > 0; tdadbrk--) {
			continue;
		}
	}
	return 27641;
}

bool lbaqlpu::aekifwisrzghtl(double oattlvoo, int ujsvn, double urxefnjf, bool ziqsefdfqq, int irfqwtriebtc, double rqeorjllhmpsvc, string ermfmzlvshrml) {
	string zoljtdisp = "gpoullvtyjgsxtlmvwkbkhnmlneij";
	double bnjpicgyxjhizcy = 51236;
	int tcjsqgvdq = 1782;
	bool cxyrltwxmfb = true;
	double eaagclzovnz = 31971;
	string sbfzz = "htotmjnvjypkoylfretwdeltvgipxpzaxeixjkioyitwthbauohdryetnmwhwkgnb";
	bool azave = false;
	if (false != false) {
		int vifyeojpmk;
		for (vifyeojpmk = 72; vifyeojpmk > 0; vifyeojpmk--) {
			continue;
		}
	}
	return false;
}

int lbaqlpu::dmddztjpvgxzkytnxcmvut(bool xuqrtkluzn, double itekswyksuh, double mmpapbnyctpxp, double dfoloqdvjahectj, string hfharlc, double juptvoyjtk, int avcibtssh, bool tamyvnhvskn, string gpvlhdcyeksglcr) {
	double wzyovzjjkextmyl = 8743;
	int hertedi = 2146;
	if (2146 != 2146) {
		int ryam;
		for (ryam = 33; ryam > 0; ryam--) {
			continue;
		}
	}
	if (8743 != 8743) {
		int ytv;
		for (ytv = 33; ytv > 0; ytv--) {
			continue;
		}
	}
	if (2146 == 2146) {
		int tfe;
		for (tfe = 79; tfe > 0; tfe--) {
			continue;
		}
	}
	if (8743 == 8743) {
		int czx;
		for (czx = 67; czx > 0; czx--) {
			continue;
		}
	}
	if (2146 == 2146) {
		int xlka;
		for (xlka = 60; xlka > 0; xlka--) {
			continue;
		}
	}
	return 44377;
}

bool lbaqlpu::skzogidtpf(string lydlbhdhdeibys, bool nxgxfqjdpm) {
	bool mddjdsmrswmgnpb = true;
	string wpmjjc = "bielnhvmtwoafisjp";
	string bnpzrupsvpiiz = "pdueitlihrnegmnqdgrpmuqrzrzppwomjiicpntoiqcqwqddzwgssayuxlpealigcmqcafnemfjxdjzn";
	string gsrqglj = "ynsluxym";
	string dqoobwdwrg = "yvyxgxzthazktquywumewplhefgvziwkojqzfilssrjvolprsxpipqjbshrcfigxtsed";
	int zoxkhug = 1743;
	int wfvkwukgpof = 4895;
	int kiibix = 1771;
	if (4895 != 4895) {
		int ixmpuyjt;
		for (ixmpuyjt = 18; ixmpuyjt > 0; ixmpuyjt--) {
			continue;
		}
	}
	if (4895 == 4895) {
		int kbpfla;
		for (kbpfla = 62; kbpfla > 0; kbpfla--) {
			continue;
		}
	}
	if (string("bielnhvmtwoafisjp") == string("bielnhvmtwoafisjp")) {
		int putddyc;
		for (putddyc = 95; putddyc > 0; putddyc--) {
			continue;
		}
	}
	if (4895 == 4895) {
		int mbf;
		for (mbf = 16; mbf > 0; mbf--) {
			continue;
		}
	}
	return true;
}

bool lbaqlpu::ueeuusqgkuojcut() {
	return true;
}

double lbaqlpu::pgfxdvbfljbrz(double mhwframrnjaeu, double exyxjtevly, string irkmdjsc, double hbgezbgvbmkbzt, string xcaeoyl, int cheglhaoe) {
	string tnestzie = "gghoqabxpvhfvtrpospdfmbnziqtirvpwo";
	double ptzhojihznas = 3950;
	return 48194;
}

string lbaqlpu::gezineqotrsxhoogpkktzxry(string zikolxjr, double cpdluowixrzd, double uimvnvpgqvjxne, string obqdisbji, bool rxklppuxhr, string vaxcljewgbfq) {
	double tyydqmsblqizhsu = 20774;
	string wxdpqw = "zaxomfsnjbhdaaarpevhujqaumj";
	int wwyeeymudqi = 5274;
	string vxgcecvdagp = "ppwoomkkrbusbninfksgnbexpoguorlxtdaftvgtlmcekjboxsmjlmuwtbgfwjxwaumakgwckjygqwjmktuurqfjabjpzhlaj";
	int mwszaonx = 1794;
	return string("soqhtpcvsfqamvfedy");
}

int lbaqlpu::qidqynzidaqpyhcq(double qgjinulwv, double lrqgxmko, bool jwlcetlbsuqsbfr, bool waeyibcvxr, bool iatohydr, double utvpsqpujnwer) {
	string orsjjixyofyr = "nvwycsthtuboglsmyrymkq";
	int nzebbkhmstfub = 1342;
	string cdrrxmos = "tbomorikmsklxxozuexfwdqlvenyslihwwhs";
	if (string("tbomorikmsklxxozuexfwdqlvenyslihwwhs") == string("tbomorikmsklxxozuexfwdqlvenyslihwwhs")) {
		int gcg;
		for (gcg = 78; gcg > 0; gcg--) {
			continue;
		}
	}
	if (string("nvwycsthtuboglsmyrymkq") != string("nvwycsthtuboglsmyrymkq")) {
		int enbiqktqkm;
		for (enbiqktqkm = 27; enbiqktqkm > 0; enbiqktqkm--) {
			continue;
		}
	}
	if (1342 != 1342) {
		int zfiw;
		for (zfiw = 52; zfiw > 0; zfiw--) {
			continue;
		}
	}
	if (string("tbomorikmsklxxozuexfwdqlvenyslihwwhs") != string("tbomorikmsklxxozuexfwdqlvenyslihwwhs")) {
		int hezhkith;
		for (hezhkith = 59; hezhkith > 0; hezhkith--) {
			continue;
		}
	}
	return 35708;
}

double lbaqlpu::vrbxwipchaqkwzvuv(string vhbdcbkrrr, bool ydvfvxxkkwmiy, string akplpbbr, string clqdcafrga, double nnmtolbctfghkp, double qgxnc, string eujvlvczlaxx, bool vplizalxnakvx, int mxvfxit) {
	bool nksuxa = true;
	string gctqdk = "cdziwczomywgprwabthtmehyafnkfqpmrabwmokfkahabzsbgvqzohtgnaqqjfscgfdrt";
	bool ethcbnh = true;
	int hbkzgaj = 783;
	bool pehjnuulgmbclbz = true;
	double aapffqklm = 32560;
	double kmqro = 834;
	string fggoq = "mlqsnregkoaicggyspxkxmhbszqzkljzdkjzizbvwcnqvyegraybsnlbpqbqaybgdozdwasamzawhjde";
	double rghfky = 25286;
	string yhkntutw = "xdihdqxnfvijdeoysgnyiotyqrgyrsojejaipwdhgxd";
	if (true == true) {
		int fjvbtqcfd;
		for (fjvbtqcfd = 17; fjvbtqcfd > 0; fjvbtqcfd--) {
			continue;
		}
	}
	if (string("mlqsnregkoaicggyspxkxmhbszqzkljzdkjzizbvwcnqvyegraybsnlbpqbqaybgdozdwasamzawhjde") != string("mlqsnregkoaicggyspxkxmhbszqzkljzdkjzizbvwcnqvyegraybsnlbpqbqaybgdozdwasamzawhjde")) {
		int kkmpcjtq;
		for (kkmpcjtq = 62; kkmpcjtq > 0; kkmpcjtq--) {
			continue;
		}
	}
	if (25286 == 25286) {
		int xy;
		for (xy = 73; xy > 0; xy--) {
			continue;
		}
	}
	if (834 == 834) {
		int lz;
		for (lz = 98; lz > 0; lz--) {
			continue;
		}
	}
	return 65631;
}

void lbaqlpu::ryepjctkmocaedpgbwr(bool qgwwwrkfo, int qpmpv, bool gtdheoxpkbhperb, int ybatroo, double kxiepipn, bool bqumocfkay, double onmmflivoft, int sjiqi, string momtlispzng, double tieenjtku) {
	string rkixzoj = "nqmjadxhhnlteoisfaiwohcaddkxqbygjniideceetijsyupypuxkmcjushxbes";
	bool exqzvbcpw = false;
	if (string("nqmjadxhhnlteoisfaiwohcaddkxqbygjniideceetijsyupypuxkmcjushxbes") != string("nqmjadxhhnlteoisfaiwohcaddkxqbygjniideceetijsyupypuxkmcjushxbes")) {
		int dfbqi;
		for (dfbqi = 13; dfbqi > 0; dfbqi--) {
			continue;
		}
	}
	if (false != false) {
		int zw;
		for (zw = 96; zw > 0; zw--) {
			continue;
		}
	}
	if (string("nqmjadxhhnlteoisfaiwohcaddkxqbygjniideceetijsyupypuxkmcjushxbes") == string("nqmjadxhhnlteoisfaiwohcaddkxqbygjniideceetijsyupypuxkmcjushxbes")) {
		int idimofkzoi;
		for (idimofkzoi = 58; idimofkzoi > 0; idimofkzoi--) {
			continue;
		}
	}
	if (false != false) {
		int ysgferncj;
		for (ysgferncj = 96; ysgferncj > 0; ysgferncj--) {
			continue;
		}
	}
	if (false == false) {
		int sknciu;
		for (sknciu = 6; sknciu > 0; sknciu--) {
			continue;
		}
	}

}

double lbaqlpu::olyjyfqrhw(int pclul, int uqbob, double cqghnqd, double prstiwfldgsesrr, double tckmy, double vdsxat, string qtmclbqf, int xmzhulrbnl, string slfxnbaoxaew) {
	string rgxcennet = "phehhixokjanlsphdgowhxfxwkfsivedyvdelwivpuklasivzttjepqayyigrv";
	int dtumuzpemx = 875;
	int llfthpbgam = 228;
	string whuypjqasw = "ggyfbgmoejcgpwinavlfehogpuguamolsgpdudckgyjecsrhxq";
	if (228 != 228) {
		int ilwbt;
		for (ilwbt = 33; ilwbt > 0; ilwbt--) {
			continue;
		}
	}
	if (string("ggyfbgmoejcgpwinavlfehogpuguamolsgpdudckgyjecsrhxq") == string("ggyfbgmoejcgpwinavlfehogpuguamolsgpdudckgyjecsrhxq")) {
		int vhgxqhnqg;
		for (vhgxqhnqg = 100; vhgxqhnqg > 0; vhgxqhnqg--) {
			continue;
		}
	}
	if (string("ggyfbgmoejcgpwinavlfehogpuguamolsgpdudckgyjecsrhxq") != string("ggyfbgmoejcgpwinavlfehogpuguamolsgpdudckgyjecsrhxq")) {
		int sb;
		for (sb = 50; sb > 0; sb--) {
			continue;
		}
	}
	if (string("phehhixokjanlsphdgowhxfxwkfsivedyvdelwivpuklasivzttjepqayyigrv") == string("phehhixokjanlsphdgowhxfxwkfsivedyvdelwivpuklasivzttjepqayyigrv")) {
		int ik;
		for (ik = 14; ik > 0; ik--) {
			continue;
		}
	}
	return 28615;
}

double lbaqlpu::pzfuleoibnfqkcztbyly(string ioubuugbcl, string rflgggtgbmh, double bwdwocvf) {
	double utehpaufqtxrhm = 6283;
	if (6283 != 6283) {
		int opjspl;
		for (opjspl = 25; opjspl > 0; opjspl--) {
			continue;
		}
	}
	return 92104;
}

double lbaqlpu::hgqsdiwqgxeylwe() {
	string swoksotwhqmi = "kfasizdwggxdvyduxsqgeyluwqxviwuko";
	int bseqlfnefhyicto = 425;
	int agwqacvkxnudbe = 949;
	int hwwucfkj = 1085;
	if (949 != 949) {
		int ccqa;
		for (ccqa = 50; ccqa > 0; ccqa--) {
			continue;
		}
	}
	if (string("kfasizdwggxdvyduxsqgeyluwqxviwuko") != string("kfasizdwggxdvyduxsqgeyluwqxviwuko")) {
		int fbiid;
		for (fbiid = 44; fbiid > 0; fbiid--) {
			continue;
		}
	}
	if (425 != 425) {
		int ciflwxc;
		for (ciflwxc = 83; ciflwxc > 0; ciflwxc--) {
			continue;
		}
	}
	if (949 == 949) {
		int ipeiffn;
		for (ipeiffn = 80; ipeiffn > 0; ipeiffn--) {
			continue;
		}
	}
	if (425 == 425) {
		int glg;
		for (glg = 63; glg > 0; glg--) {
			continue;
		}
	}
	return 50533;
}

string lbaqlpu::siqbmsxijibeelutwbxetch(string nqdonk) {
	string bmtbubwypzydj = "sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn";
	bool ekekuqbgqir = false;
	if (string("sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn") != string("sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn")) {
		int mqydxdfbu;
		for (mqydxdfbu = 97; mqydxdfbu > 0; mqydxdfbu--) {
			continue;
		}
	}
	if (string("sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn") != string("sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn")) {
		int zlgfen;
		for (zlgfen = 76; zlgfen > 0; zlgfen--) {
			continue;
		}
	}
	if (string("sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn") != string("sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn")) {
		int an;
		for (an = 9; an > 0; an--) {
			continue;
		}
	}
	if (string("sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn") == string("sxtjcgkcydcrzhwqinftoklmbxsabfsvrxvmsefzotqcmqqfpzrdclxnnbymuolytuclmpwckjytaunsfdenybmxicxn")) {
		int zbgls;
		for (zbgls = 29; zbgls > 0; zbgls--) {
			continue;
		}
	}
	if (false == false) {
		int uefzkdj;
		for (uefzkdj = 78; uefzkdj > 0; uefzkdj--) {
			continue;
		}
	}
	return string("gonlquvljphaxtudzepa");
}

bool lbaqlpu::nqmkytadoseqyxikylxbp(string vvkvcial, bool aprrgqi, string vtiikjzzyy, string qdtnhjnuehooymn, bool rwvaejmhfigwvw, bool gjxzonlkwmhwone) {
	int qevswrzys = 1833;
	if (1833 == 1833) {
		int kssnuadxn;
		for (kssnuadxn = 78; kssnuadxn > 0; kssnuadxn--) {
			continue;
		}
	}
	if (1833 == 1833) {
		int yzsyjgmqr;
		for (yzsyjgmqr = 11; yzsyjgmqr > 0; yzsyjgmqr--) {
			continue;
		}
	}
	return false;
}

double lbaqlpu::gqkdnwhwywwd(double hnkcij) {
	string dwnjfvfd = "ozoteyfnzigmkqpugkkxjldeztbhffqihkzqhsxbkglvelhrolpypqhjxccfnmxuxmfpjnjdztplhcpjh";
	bool goyppk = true;
	bool hksfolyixs = false;
	int xncnu = 6319;
	double gynpvrlyppnyjp = 42266;
	bool apzvdowceydq = false;
	if (true == true) {
		int dexgxdz;
		for (dexgxdz = 30; dexgxdz > 0; dexgxdz--) {
			continue;
		}
	}
	if (false == false) {
		int tggyc;
		for (tggyc = 14; tggyc > 0; tggyc--) {
			continue;
		}
	}
	if (42266 != 42266) {
		int zkwyaklf;
		for (zkwyaklf = 27; zkwyaklf > 0; zkwyaklf--) {
			continue;
		}
	}
	if (false == false) {
		int ljxs;
		for (ljxs = 1; ljxs > 0; ljxs--) {
			continue;
		}
	}
	return 57095;
}

lbaqlpu::lbaqlpu() {
	this->olyjyfqrhw(2365, 153, 31198, 41953, 53173, 3054, string("mlhlizpgridyepxzpsjucxj"), 2497, string("qttczmaxtsdxg"));
	this->pzfuleoibnfqkcztbyly(string("dbubjhxrhifhbucmzxzfxjpkegjitfwifhnzqnjkcemxqwyebadptaqpwp"), string("rwhcstbwdhikobicebrzhabokbfnnpxalytuygyoa"), 25906);
	this->hgqsdiwqgxeylwe();
	this->siqbmsxijibeelutwbxetch(string("beixupntdnespyhnevzpgcypyydqaewmhoqxhaxiajn"));
	this->nqmkytadoseqyxikylxbp(string("piqhharhfrdumqdeagxmyebdnpjtigbor"), false, string("ieaaqygzmhafniwlpfjwdobdgpqpvzrpkazmjipnodforzlwpialfvqyvbrbnnvchvgna"), string("qajyoueiblksqowlcjbp"), true, true);
	this->gqkdnwhwywwd(15306);
	this->skzogidtpf(string("rchcytqvzjpoetyvkhbecp"), false);
	this->ueeuusqgkuojcut();
	this->pgfxdvbfljbrz(8625, 15394, string("dhxvpdyjbszpqxhjfeicteglzndaylwkceeulxqwhsbxvojilkxmgs"), 3331, string("i"), 1427);
	this->gezineqotrsxhoogpkktzxry(string("vnmofuaieaqtnnbkhxafuocfdrfqxkuapaseuofvgpkdzjqeorpjggqzufnssaq"), 5330, 26802, string("dtiqtnpwngsreedebyodqelsrmkoyxblcuweazsbxhik"), false, string("bnztmytmkxavlfbvdmiawbhhpehqzzpiclrrzdhfc"));
	this->qidqynzidaqpyhcq(4556, 6906, false, false, true, 57090);
	this->vrbxwipchaqkwzvuv(string("rucnhicvoswfvugzagrdnsufuvjkplzbxchmrpwpfddtzodnlbzwdimmcqeljnxmxzrvtqskj"), true, string("ewhbksizhfutlitkvaexormqoukzjmbshmkvebcmplim"), string("jbibgqjfjiuhattbzuayzmneqdfpjxqxocevxpvsxbdqafhyjsnqbjxiqlhrtskwaqxzehyzbhpxkgxukfcbmgs"), 34630, 11862, string("nwxghfbwhlyajhcmqcefqhduouxzyrgeajlbgxfrnhqxfeutmxjsflmcyqayqvmoktjtpaudspmkqyzjjcfdczenmtvo"), false, 1012);
	this->ryepjctkmocaedpgbwr(false, 6250, true, 873, 41038, false, 9972, 1160, string("oozsifpcwgaewaodyd"), 69614);
	this->isejgilwalku(string("camhblsyjvrczscvukjcwzlxzntfpafebzqmv"), string("dlpjllrjolnstblislbmjkyspiyqikhrcwduqqecdfcaptnxoejlvczqezhgzvnftqezn"), string("tlwfjipbvgeurwagrkeszgjwtorbmuamxahusnhulkuugnuogxkrgeuwxnqucejhuoumgyiyiolkjdmpdgme"), false, 1652, 1629);
	this->acmtjvpsin();
	this->ckyahxzjqwyboxmvakwdn(false, string("eynblmkrirufqncoqrgdfxjoexghwjxwuvpysoeolynmmgmgccartrymirilanpbfyhwxbxcpdwscxlaoqbvqqejpxf"));
	this->uxdwkmjdinlmdeuioyqh(string("mfutdqfftfresjukcmsptvuedj"), 73974, 5243, 3125, false, 2254, string("zpxekjbwdsqnyrxxjbllicwathkkcjejxycjruzwkozwxilka"));
	this->cpjjhseidhmgedkqjwism();
	this->zmawzdcgtfzyelvxkof(string("lzaqmzrmimaqazjnsdhvcmgwqvlbbrddpscoaqlarjj"), 4626, string("nyfkgzsqypeocwnyxpsuhkihqyauuktfnzyqvymngjeallaftupmktejvhfynvg"), string("qkytmeljshvrgijzgdj"), 350);
	this->ipvsbhsfkfphjtwkzpgtb(12608, 43677, string("jxpvhzrtponmehddwkavkrdfgpsmszjjfu"), 7025, 1152, 15316, false, true);
	this->pylhbyaicjafjdpspfjdcgoo(false, 703, false);
	this->aekifwisrzghtl(33424, 2700, 37866, true, 3193, 29820, string("tsijywktkvsqbadnmrbuwypiyuuiofdqfqyybrwzxyqkmgslgpftqrdxtdikw"));
	this->dmddztjpvgxzkytnxcmvut(true, 4730, 9752, 14954, string("gzswpmpomjauhsiebfwapmorhkyjfcfhyjmwmtzrnybckcnkcvvytligjsfhtjandpsmhhm"), 1944, 512, false, string("xkjsmqnqjjwtfujsaeeisqnhqckicnvaawwpbtlabdkkfkuhflhnsyhpyuxcunceftlxuccjfnazqxr"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class zmyfqma {
public:
	bool hdcoqeairkfc;
	bool yrjorzpzrrbik;
	zmyfqma();
	int exnqzarezqzx(double ekplenxguvahxqn, double pdlmuqcntohfr, double jhouvavifvcjyn, double eftlyt, string qvvtfuokfefqgbv, bool zdijbxmwghjd);
	int jlikvtfyehfazz(double etpdkbekxiohhbt, double qxxpkja, double pidzobps, bool inplmwgeram, double xwxacujmoiwuecz, int vctdzw, int feumouslt, bool ozbqlfl, bool chzohc);
	double ixgbnhzomdpilaaqsqzkmu(bool pqkbfvi, string hpscwpcnlyztqvi, double feyfjm, bool abmopi, int syarwrnljuklqg, double hulqwzvpkjcs, int ymwelxxmiocyhfn, bool akkjgtpfdq, int gqturks, double wfdfvoggzxrws);
	string zbqxzqitfqahnet(int eykeunfbjxvrk, bool sabvmmxxndmjnd, double ymtyvtmbhiafw);
	void fqsfhhichahvnxe(int sxftzolyxzjrbh, int idzrcp, int farcjpr, string fzcdtthbkwblmau);
	void brhawdsyrrnnsnthirojfk(double dzbuybox, string veutlnncvuo);
	void npopsyofcasieefyukcnyph(string xuxyiwq, int akpsmbffwskakkf, double gupygazek, string azrfi, bool euywvzrplyflv, string upmeowalpyeyfhg, double qncbgmekjcrg, string tebbnyi, string prfhgjlepdjggks);

protected:
	int btrepbqnyb;
	double ryvfvvxyv;

	int sbibklpnsxw(string fjapg, int iszqvmkhjcsan);
	double cemelzemdlxkundoyahfxlsky(int olgzzdddtkbmyl);
	bool nylqougorgtcznzl();
	double sjolzfqacfqcf(double easjydw, bool llkzxeshul, double lfevramsmqx, bool hsdkrqjeexcz, string tvmkcm, double vthgrkt, string wtbziuhzl);
	bool wkmxuxzchqaebkbzdsnwsr(bool nyplywyby, double erdquc, int leeqvpuyxa, double uklbtkeyvoca, double dhqtsvbjzaxoyf);

private:
	double qvhplmlija;
	int lwhbw;
	string xrsjwiggybwjvy;

	void oguhztespftzqwctiq(int sltdxlppj, int ambnvjrqu);
	int rkuwfrfkzklaprih(int lzbxzgo, int oejpvsyhsxh);
	double odgzqkoeygdfulk(double apggmvkgbqe, double igxab, int idzdj, bool ozlfpqpk, string mwmzm, string aqhpnunoedahbzx, int xlndtyxjtvwb, bool wixxejolgzaxmb);
	double iprhcxpeirxtczkuioe(int jwtcdaibgryfc, string rxuriohzwannt, string knjnozrt, string ycuseokjl, double wmjkxvw, double vkdpcexl);
	string jzowycwgfagmdipoon();
	bool uflcwgxgwdqgtblj(int udyswtzwycr, double vxnynah, double szrzacwl, bool gnkatdziakwrgoi, int ygogymfafsnrju, int bzlyns, bool mmtmoql);

};


void zmyfqma::oguhztespftzqwctiq(int sltdxlppj, int ambnvjrqu) {
	string zxymkka = "vznnhbxmhnpstzeoyktpqznlxuoqyqphdxtkehwwbqzgqgrvmrypckolowxgxexbxobobmgiqbtavganhsied";
	string xfbdsaxfvosjgfs = "rz";
	bool rddlvy = true;
	double bnxdpkefh = 8422;
	double mwthsqmq = 340;
	if (string("vznnhbxmhnpstzeoyktpqznlxuoqyqphdxtkehwwbqzgqgrvmrypckolowxgxexbxobobmgiqbtavganhsied") == string("vznnhbxmhnpstzeoyktpqznlxuoqyqphdxtkehwwbqzgqgrvmrypckolowxgxexbxobobmgiqbtavganhsied")) {
		int xn;
		for (xn = 32; xn > 0; xn--) {
			continue;
		}
	}

}

int zmyfqma::rkuwfrfkzklaprih(int lzbxzgo, int oejpvsyhsxh) {
	double ivimnoghlnrmvgc = 2326;
	int btqear = 842;
	double axqkbk = 730;
	int cslogyfffd = 1066;
	int akzkjfdib = 1077;
	string qiwzs = "xhfcuwqagodujkgfksnlzonesmymscebqvvpxnvgeqhgasg";
	int yvumgi = 2579;
	bool gjiuzcopgv = false;
	if (1066 == 1066) {
		int exrr;
		for (exrr = 18; exrr > 0; exrr--) {
			continue;
		}
	}
	return 16095;
}

double zmyfqma::odgzqkoeygdfulk(double apggmvkgbqe, double igxab, int idzdj, bool ozlfpqpk, string mwmzm, string aqhpnunoedahbzx, int xlndtyxjtvwb, bool wixxejolgzaxmb) {
	string ewyppwxxtry = "lzdjkunnhjkr";
	double molutb = 17612;
	bool vpfmlrdyq = true;
	bool pjkmtobkg = false;
	bool arzdruqf = true;
	if (true == true) {
		int wn;
		for (wn = 26; wn > 0; wn--) {
			continue;
		}
	}
	return 31764;
}

double zmyfqma::iprhcxpeirxtczkuioe(int jwtcdaibgryfc, string rxuriohzwannt, string knjnozrt, string ycuseokjl, double wmjkxvw, double vkdpcexl) {
	int jwptntlu = 5800;
	string xbvuyyexaw = "gbjwsjqqopcrxtaxhdyvniblytxgnleemdilyzneqlisqvqzyvrkskwrtdmgohaojpqzesaoomqxmvizzmmworuz";
	if (string("gbjwsjqqopcrxtaxhdyvniblytxgnleemdilyzneqlisqvqzyvrkskwrtdmgohaojpqzesaoomqxmvizzmmworuz") != string("gbjwsjqqopcrxtaxhdyvniblytxgnleemdilyzneqlisqvqzyvrkskwrtdmgohaojpqzesaoomqxmvizzmmworuz")) {
		int drdpf;
		for (drdpf = 51; drdpf > 0; drdpf--) {
			continue;
		}
	}
	if (string("gbjwsjqqopcrxtaxhdyvniblytxgnleemdilyzneqlisqvqzyvrkskwrtdmgohaojpqzesaoomqxmvizzmmworuz") == string("gbjwsjqqopcrxtaxhdyvniblytxgnleemdilyzneqlisqvqzyvrkskwrtdmgohaojpqzesaoomqxmvizzmmworuz")) {
		int cdripesqa;
		for (cdripesqa = 49; cdripesqa > 0; cdripesqa--) {
			continue;
		}
	}
	if (5800 != 5800) {
		int iwmeha;
		for (iwmeha = 12; iwmeha > 0; iwmeha--) {
			continue;
		}
	}
	if (5800 != 5800) {
		int pvijzz;
		for (pvijzz = 22; pvijzz > 0; pvijzz--) {
			continue;
		}
	}
	if (5800 != 5800) {
		int bj;
		for (bj = 16; bj > 0; bj--) {
			continue;
		}
	}
	return 78957;
}

string zmyfqma::jzowycwgfagmdipoon() {
	bool odwst = false;
	bool ppuxuk = true;
	string tytnkdrnwh = "xyufbbedghcvtpmnbkxhxzkqvvazheeecqyhislgrrqrqjjp";
	string mcbhehekfsd = "orndfrtjkasowkegvswewnfwfmpntkwezpr";
	bool ebueruoor = true;
	string vdrjrtf = "pymoypbootuitxzpmsla";
	int mfkcruvfmwyjcfw = 6312;
	int lernflmurrq = 4185;
	int gwzyfyybkbbm = 4605;
	string ddzaitagrqney = "qxfodgsyiyvcozwvg";
	return string("rvwwut");
}

bool zmyfqma::uflcwgxgwdqgtblj(int udyswtzwycr, double vxnynah, double szrzacwl, bool gnkatdziakwrgoi, int ygogymfafsnrju, int bzlyns, bool mmtmoql) {
	string msannkqjvtxmu = "btxftvdvicwhcylhimxsqqwvdzaicagynkrid";
	int qtqznzqjubjn = 3978;
	bool nwdkwmlguvtg = true;
	return false;
}

int zmyfqma::sbibklpnsxw(string fjapg, int iszqvmkhjcsan) {
	bool kztfhrpeoibjx = true;
	int abpuyjbuvzmb = 183;
	int movnjxoqwp = 5488;
	string twlzd = "amfypdifibmauwbiziwhpdfdizufkqteciihusgtxgbfuqvmefikmtfkkmoho";
	bool zaytm = false;
	int puykfdelueolc = 1014;
	bool nkcysadrdo = false;
	string xjyhbgosub = "vwlxvtqxgfyiacdxceycdluezmrmhlujke";
	if (5488 != 5488) {
		int dmrca;
		for (dmrca = 23; dmrca > 0; dmrca--) {
			continue;
		}
	}
	if (183 == 183) {
		int aacy;
		for (aacy = 0; aacy > 0; aacy--) {
			continue;
		}
	}
	if (false == false) {
		int ueacaupbr;
		for (ueacaupbr = 57; ueacaupbr > 0; ueacaupbr--) {
			continue;
		}
	}
	if (1014 != 1014) {
		int ajjztncev;
		for (ajjztncev = 52; ajjztncev > 0; ajjztncev--) {
			continue;
		}
	}
	return 51284;
}

double zmyfqma::cemelzemdlxkundoyahfxlsky(int olgzzdddtkbmyl) {
	double elqypofjlxqmwjm = 25920;
	double ilbjg = 34646;
	bool bsqxgnrw = false;
	string junmlxpguh = "upytktgjnbbbzhssehfokpyiyrickskpaduoxbffjxtmhcyulhmhzkigzoxbdeupkzfhbocp";
	bool flddcdtmdvs = true;
	if (34646 == 34646) {
		int kekhm;
		for (kekhm = 32; kekhm > 0; kekhm--) {
			continue;
		}
	}
	if (25920 != 25920) {
		int vceujuncoz;
		for (vceujuncoz = 37; vceujuncoz > 0; vceujuncoz--) {
			continue;
		}
	}
	if (false == false) {
		int mtgbxijn;
		for (mtgbxijn = 35; mtgbxijn > 0; mtgbxijn--) {
			continue;
		}
	}
	return 55930;
}

bool zmyfqma::nylqougorgtcznzl() {
	return false;
}

double zmyfqma::sjolzfqacfqcf(double easjydw, bool llkzxeshul, double lfevramsmqx, bool hsdkrqjeexcz, string tvmkcm, double vthgrkt, string wtbziuhzl) {
	return 84176;
}

bool zmyfqma::wkmxuxzchqaebkbzdsnwsr(bool nyplywyby, double erdquc, int leeqvpuyxa, double uklbtkeyvoca, double dhqtsvbjzaxoyf) {
	int inmqbdqvzbq = 2417;
	int ekhcf = 2713;
	string uniwjuwrv = "bfqxnlrcwckyiokxewrogsbylsjiyrjwfowxkcn";
	string gfnsdf = "vfnircabjvtrfncacirclwqcqhbcyvaoobrscahlqnepsxhfmdggzfyjijrryjzvlshedzoilxyeddpjfnysmemutcakrjk";
	int wwofqygfuwspziv = 1007;
	if (2417 == 2417) {
		int wxgqamzqua;
		for (wxgqamzqua = 22; wxgqamzqua > 0; wxgqamzqua--) {
			continue;
		}
	}
	if (2713 != 2713) {
		int ce;
		for (ce = 16; ce > 0; ce--) {
			continue;
		}
	}
	if (string("vfnircabjvtrfncacirclwqcqhbcyvaoobrscahlqnepsxhfmdggzfyjijrryjzvlshedzoilxyeddpjfnysmemutcakrjk") != string("vfnircabjvtrfncacirclwqcqhbcyvaoobrscahlqnepsxhfmdggzfyjijrryjzvlshedzoilxyeddpjfnysmemutcakrjk")) {
		int ydpj;
		for (ydpj = 18; ydpj > 0; ydpj--) {
			continue;
		}
	}
	if (1007 == 1007) {
		int wyrkagyp;
		for (wyrkagyp = 11; wyrkagyp > 0; wyrkagyp--) {
			continue;
		}
	}
	if (2713 != 2713) {
		int ts;
		for (ts = 59; ts > 0; ts--) {
			continue;
		}
	}
	return true;
}

int zmyfqma::exnqzarezqzx(double ekplenxguvahxqn, double pdlmuqcntohfr, double jhouvavifvcjyn, double eftlyt, string qvvtfuokfefqgbv, bool zdijbxmwghjd) {
	int kufxfkjsiisrfxt = 3712;
	string vlfqknrehwq = "ppluiqqtyhwzpqukkyaf";
	double ertugmmr = 72088;
	string pjgbqwj = "lllzfxiowyoengqbyeqyeistpweeisuwjrxylxmylbrgzncakwdkroawzevebxcvhufjwtfnrirtgffxnjzgzbtbxozgvdqox";
	bool ytmbqle = true;
	int zzfeouqvg = 4434;
	if (true == true) {
		int zv;
		for (zv = 5; zv > 0; zv--) {
			continue;
		}
	}
	if (true != true) {
		int crgpyk;
		for (crgpyk = 62; crgpyk > 0; crgpyk--) {
			continue;
		}
	}
	if (72088 == 72088) {
		int ithudarg;
		for (ithudarg = 99; ithudarg > 0; ithudarg--) {
			continue;
		}
	}
	if (4434 == 4434) {
		int kflggtgfdt;
		for (kflggtgfdt = 47; kflggtgfdt > 0; kflggtgfdt--) {
			continue;
		}
	}
	return 22859;
}

int zmyfqma::jlikvtfyehfazz(double etpdkbekxiohhbt, double qxxpkja, double pidzobps, bool inplmwgeram, double xwxacujmoiwuecz, int vctdzw, int feumouslt, bool ozbqlfl, bool chzohc) {
	string vdrjrvykaz = "cyvlaqofkhwieqjljcdxiegauawklaavaxjd";
	double rdbdkqtfuz = 37425;
	return 18608;
}

double zmyfqma::ixgbnhzomdpilaaqsqzkmu(bool pqkbfvi, string hpscwpcnlyztqvi, double feyfjm, bool abmopi, int syarwrnljuklqg, double hulqwzvpkjcs, int ymwelxxmiocyhfn, bool akkjgtpfdq, int gqturks, double wfdfvoggzxrws) {
	string yydmwn = "ebsifqtqoqanjphibvkwcdlwpleuacneusticbptwbwfakksymyehuskktzlxrgxwcpyfutnuneeowrmzop";
	int rxgsurovosucat = 2655;
	bool clvacptktx = false;
	double gvjdrpw = 9797;
	int fgxvhhuxummt = 2803;
	int tbtkkrgkze = 5637;
	int golqpnds = 2925;
	return 23433;
}

string zmyfqma::zbqxzqitfqahnet(int eykeunfbjxvrk, bool sabvmmxxndmjnd, double ymtyvtmbhiafw) {
	double orjetyfqzlbgaq = 66002;
	string nbgacaxm = "vwrxnwpxeldyyujlyxiltrbfchopejcupuyemfwtcfxdppaseiwvqswhjdnm";
	double xfrik = 11762;
	bool qkqgx = false;
	double zoimxnjgxhxv = 73991;
	int uqurzmfayqjaj = 2878;
	bool ltlsumqwonih = false;
	string oodamjhysxavt = "nqwbljldtozdrqbwlctuishtcnlpjxy";
	if (false != false) {
		int yjct;
		for (yjct = 88; yjct > 0; yjct--) {
			continue;
		}
	}
	if (string("nqwbljldtozdrqbwlctuishtcnlpjxy") != string("nqwbljldtozdrqbwlctuishtcnlpjxy")) {
		int uvjch;
		for (uvjch = 1; uvjch > 0; uvjch--) {
			continue;
		}
	}
	if (string("nqwbljldtozdrqbwlctuishtcnlpjxy") != string("nqwbljldtozdrqbwlctuishtcnlpjxy")) {
		int kr;
		for (kr = 70; kr > 0; kr--) {
			continue;
		}
	}
	if (66002 == 66002) {
		int vhvsoswpqe;
		for (vhvsoswpqe = 88; vhvsoswpqe > 0; vhvsoswpqe--) {
			continue;
		}
	}
	return string("ujs");
}

void zmyfqma::fqsfhhichahvnxe(int sxftzolyxzjrbh, int idzrcp, int farcjpr, string fzcdtthbkwblmau) {
	bool jxyjhsw = false;
	double iubfwjyf = 59569;
	int ddzflecpaursclb = 936;
	bool virpxomwrtyxce = false;
	bool sksqv = false;
	int iggpwkgitkjxhym = 1294;
	bool qarnb = true;
	bool kznsytsl = false;
	if (false == false) {
		int tgsk;
		for (tgsk = 68; tgsk > 0; tgsk--) {
			continue;
		}
	}

}

void zmyfqma::brhawdsyrrnnsnthirojfk(double dzbuybox, string veutlnncvuo) {
	bool qfcdxbo = true;
	bool wfgkktwrqfbgjv = true;
	string vvspvuau = "fcmexxbqlylxfagobtvdcfendqsuyqesambjywfzldlopptrxrriclthrrxqa";
	double wcihxl = 8883;
	bool stqaxymxfccalb = false;
	bool tbffepzobgpyu = true;
	double oajppiitsjezq = 6735;
	int psorkg = 4058;
	string quojerzbxccy = "pivtlpbvddqgdexxxzyetvsmxkvjilnoblwfkamxspfxtwpkianfdtiw";
	if (false == false) {
		int eycfogth;
		for (eycfogth = 50; eycfogth > 0; eycfogth--) {
			continue;
		}
	}
	if (true == true) {
		int mpxzzpp;
		for (mpxzzpp = 13; mpxzzpp > 0; mpxzzpp--) {
			continue;
		}
	}
	if (string("fcmexxbqlylxfagobtvdcfendqsuyqesambjywfzldlopptrxrriclthrrxqa") == string("fcmexxbqlylxfagobtvdcfendqsuyqesambjywfzldlopptrxrriclthrrxqa")) {
		int djpk;
		for (djpk = 50; djpk > 0; djpk--) {
			continue;
		}
	}
	if (true != true) {
		int squatvcucy;
		for (squatvcucy = 29; squatvcucy > 0; squatvcucy--) {
			continue;
		}
	}

}

void zmyfqma::npopsyofcasieefyukcnyph(string xuxyiwq, int akpsmbffwskakkf, double gupygazek, string azrfi, bool euywvzrplyflv, string upmeowalpyeyfhg, double qncbgmekjcrg, string tebbnyi, string prfhgjlepdjggks) {
	int fryjkjq = 8135;
	int paotjhivmlfnxr = 3004;
	int ovaowydptdsgqa = 4498;
	int gkghdrz = 4980;
	if (4980 != 4980) {
		int hrdsxamt;
		for (hrdsxamt = 10; hrdsxamt > 0; hrdsxamt--) {
			continue;
		}
	}
	if (4498 == 4498) {
		int gqfdkyfv;
		for (gqfdkyfv = 24; gqfdkyfv > 0; gqfdkyfv--) {
			continue;
		}
	}
	if (4980 == 4980) {
		int ieyrultj;
		for (ieyrultj = 72; ieyrultj > 0; ieyrultj--) {
			continue;
		}
	}
	if (3004 == 3004) {
		int hhtft;
		for (hhtft = 28; hhtft > 0; hhtft--) {
			continue;
		}
	}

}

zmyfqma::zmyfqma() {
	this->exnqzarezqzx(32090, 3203, 66363, 32588, string("pxlukbuefptxskazymytqrzlxunyqg"), false);
	this->jlikvtfyehfazz(83392, 7438, 36738, false, 32979, 3622, 4473, true, false);
	this->ixgbnhzomdpilaaqsqzkmu(true, string("otusybkknidjvrxoffi"), 87100, true, 998, 75996, 2800, false, 308, 3281);
	this->zbqxzqitfqahnet(3169, false, 41713);
	this->fqsfhhichahvnxe(2656, 1088, 879, string("ltjzhfranlfkickiopfqfdjuanloghywdyfgnknaxpmhpxmyedvjzdaigbsswuvzmjzmwmkpbushrxzcdhs"));
	this->brhawdsyrrnnsnthirojfk(31451, string("ecvjfcxizncfybpvpgmvdsytfapnlhfvaleows"));
	this->npopsyofcasieefyukcnyph(string("lhncyxofmmylkf"), 733, 14341, string("vzxnxgszngwmiowlluzruawoesfmwerlcfjcgdzmlhysutdmkqeeezaafetimvuvdzjpwqwbkyhdcavo"), true, string("ivcuqaizcbihpqkyneuktcywspiabielgtupfaxehnoimihckdkzrgaenwpnhkfzlsieilwfpynezttdimetfdkebrsxbzo"), 21179, string("jjbushcvqmiyfwhtfmcomrtsjwostiurabkg"), string("qqjctggtfaaoocrjnbfraxqkqedakdgmfozrremxopkptnenrhiiguajxdmyprnaeqefvgflluhufvodckvahvxza"));
	this->sbibklpnsxw(string("tnwtahxwwlylmlxqlnckjacvvrlbavjggpqodxykrjyc"), 61);
	this->cemelzemdlxkundoyahfxlsky(668);
	this->nylqougorgtcznzl();
	this->sjolzfqacfqcf(32639, true, 15420, true, string("obpamabvlfiphvhvcodzjmsfcljehwdqckmfnnjfvfcaafpvl"), 5395, string("zrwgvysylthqkrsivlvpmbataamgrvukgvaxcnloopur"));
	this->wkmxuxzchqaebkbzdsnwsr(false, 32584, 2263, 49492, 13739);
	this->oguhztespftzqwctiq(8808, 2855);
	this->rkuwfrfkzklaprih(8015, 498);
	this->odgzqkoeygdfulk(19262, 67396, 4288, false, string("fdlfwvppibboqrislfsprsdgmm"), string("seebstkjqgblkaqunhbwcezjuycudnbyfdmyrorrobfqixwsohrubmdqmrpflhqye"), 2431, true);
	this->iprhcxpeirxtczkuioe(2803, string("ekeivcjburiqzwoldgiarirgiauvtjerrvmiazb"), string("almsisttfmawnajgmd"), string("kflpipixqgfhyiojdpc"), 36740, 33864);
	this->jzowycwgfagmdipoon();
	this->uflcwgxgwdqgtblj(2825, 13101, 7872, true, 319, 4590, true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class gbqltxh {
public:
	int ptyrwbryctvfqbt;
	gbqltxh();
	string yqzeerjnqkwtlbuoewyhv(string kbmfwk, int sumjicabwnspnta, bool vbyucdxx, bool mokyk, int varvppsdqditxq, bool jjmjvzmc, bool eqlwebaodtn, int euenzwtnzxr);
	int qsbjnqjdsepainnc(bool jfsiqii, string hjbypzfdgoy, double wggazws, double fwklfrvgd, bool zpxesv, double aznrkgxggmej, double niwfy, double tomzdgchrvnvdt);
	void dtwcklrfywzfnxjzphqoqvxsu(double mjltkkjmq);
	bool inqiguzwqvjvt();
	string qdxcmupxnaojobe(bool ndsxjxnrtzz, string waceo, int qgxxaamhhivhx, string ntevhalisr, bool stoie, string pfeuk, bool drbsxkocacdhexj, int ntcmkybbtiu, double icxrrfrmfwxtjvq, int nfbqrubwpfiqzoq);
	bool zzfwwdlicxbpfvcyitew(string wmefndvtylvb, double yorcd, double mzgkor, bool olpfcnvupiburs, string ysjnywfgod);
	double qdbwuxdzczytjxaxmljvmfqfc();
	int rwxefdbiuddfjhc(double ybgiwzb, string kgkzklssixojgdk);

protected:
	string tqutop;
	double rgsriixxxd;
	string rfmfjpaa;
	double duhymweijcwzjm;

	int zptzokehqeuxkjdtpcwulkuh(bool efyyrvyptv, string yvidewtetqgjs, double zssspptuqvdu, double kdtuxpfpusc, bool cuclnrwvtb, bool jynyt, string cslrjhqz, string bvskhrpd, string uicofkhgophe, double ydrqzzzxelriaq);
	bool ndawxoncce(string brugjvygx, string okbmwlh, string czavlzdrs, int vejqvtpuqhdfb, double pksetjfggvmahc);
	string ionoarjxzhqjjrb(double mrapwvbr, string wejqbthqwu, bool byridcqwbv, bool juverfgvwdeu, bool zcqwpupnxlfz, bool slhgepgcbuidkyt, int cyuxtyawtqfo);
	bool rcgfguugafxmtwrh(int jkgcrbgulxwiene, bool cedkpkktysjbaq, string kgvywowheqtp, int yxfowuw, double fgvzavn, int ifprcitk, string mwygf, string dvlwknfy, double btjikv, bool hhkyxxkevhi);
	string flydyvqwjgtydqhbuhjjpyotj(string iwcokwavdercu, double rjkmp);
	int rnmzqglihkpfsygs(double snuaslxjnnil, bool tygmxpasv, double jgswzoqc, double srpkdxwlptols, bool qzifkwdlmu, double xnyfn, bool zhursipyqps, int rndwouxmt);
	bool jtvpkfnawdzrfb(string quufkh, int ozdsyowc, double bovkldzwuvw, string tsweddsdofsatmr, string umaxjcqgnjmyrd, string ucpuxeulrmh, int mxezh, double ggbikhmmxnqrx);

private:
	int wwxkvcpqw;
	int mmaxvexfw;
	int pkjiidugvxfjmt;
	double crmilnzonrm;
	string vonnzasipgh;

	void hduhpiozcuzgypplzoditdaoa(double dcpqqcytab, bool tkjwbp, string kifpgroanufta, string lvisrdtirziqgp, string khjgps, string caldtuxbrej, int otnrwyzcfagojoh, bool ilomarf, string tyqfdpjpmv);
	int naqarxgzaqrtlq(string dmmhbyqkhs, double xqliurxvj, int sxjzc, int ftpklqbk, double bqymqwa, bool byjodteengeai, bool bqypdbmpdni);
	string divpqqpclb();
	string nwlgahvgteglwdndjkxdl(string gbwzvg, double jsnoisutp, bool pweji, string fpsuwathnwstmp);
	string dogoufobsuiycejaabhsf(double fzakkfrnzv, int yltsipfyvmx, bool mibtgmcvjxiw, double nhlosnrqtnxehki, string zepicyfdjlyjiek, double dvnurv, int nqunbqvybwb, bool esnruasf, string omrhzsh);
	double uiujztqfobyuemfukg(string ahzpoana, double nknjtpjxkal, int sfxhzeqnmyr, double swauqygulmck, bool ziuoelbpqcjbkcn, bool rrjzvzsatrhwr, double vgdovryzbkjuxt, double rfrgavdjh);
	double hgywxtahmwgvyrhqy(int xbetmzi, double ygkbuvhke, string jgsimznrtfru, double fjeudg, string qnnamu, int vlcmtetqptc, bool stqgdjok);
	bool xakhjiwngcrdvvdfqr(double rcigib, string pqflxrtx, double mutayksdp, double xuafdyvsfamcb, string fbumzjt, double poxcl, string zgktgkrks, bool tklpshx, int eghmwfcgscj);

};


void gbqltxh::hduhpiozcuzgypplzoditdaoa(double dcpqqcytab, bool tkjwbp, string kifpgroanufta, string lvisrdtirziqgp, string khjgps, string caldtuxbrej, int otnrwyzcfagojoh, bool ilomarf, string tyqfdpjpmv) {
	int furvfsfva = 5212;
	string uyanfogex = "aohfbudmnpetmpgzjprdbfsqtabzwdvhxshksatwdgljgwakpxdlysuhkyaisjr";
	bool erxzbludzpeqoh = true;
	bool xrcbhruuknzlkq = false;
	double nhranhbp = 32109;
	int tigpgwkx = 3853;
	int moikd = 1411;
	string fypscmyxv = "duxdwozmyavhjesioqfvzqrmdxzdtyzusnxptpyfjowveinyhdi";
	if (32109 == 32109) {
		int gmt;
		for (gmt = 28; gmt > 0; gmt--) {
			continue;
		}
	}
	if (true != true) {
		int xsecd;
		for (xsecd = 50; xsecd > 0; xsecd--) {
			continue;
		}
	}
	if (false != false) {
		int ywcrtvovw;
		for (ywcrtvovw = 44; ywcrtvovw > 0; ywcrtvovw--) {
			continue;
		}
	}
	if (true == true) {
		int uu;
		for (uu = 3; uu > 0; uu--) {
			continue;
		}
	}
	if (5212 == 5212) {
		int netdpiyhz;
		for (netdpiyhz = 39; netdpiyhz > 0; netdpiyhz--) {
			continue;
		}
	}

}

int gbqltxh::naqarxgzaqrtlq(string dmmhbyqkhs, double xqliurxvj, int sxjzc, int ftpklqbk, double bqymqwa, bool byjodteengeai, bool bqypdbmpdni) {
	int nijbe = 8589;
	int pkutozaduuv = 854;
	string pbaaum = "bchqvamvzcjib";
	bool yxbzignwxuftr = true;
	int zyznqtcfijvazjb = 725;
	string tivthqvjnn = "lwcrzhegrvzfizpxggkpfcyykqolplsbfb";
	if (8589 == 8589) {
		int nhpbhengh;
		for (nhpbhengh = 46; nhpbhengh > 0; nhpbhengh--) {
			continue;
		}
	}
	if (8589 != 8589) {
		int snz;
		for (snz = 63; snz > 0; snz--) {
			continue;
		}
	}
	if (8589 == 8589) {
		int tflxewvk;
		for (tflxewvk = 48; tflxewvk > 0; tflxewvk--) {
			continue;
		}
	}
	return 67822;
}

string gbqltxh::divpqqpclb() {
	bool bmdvgvz = true;
	string ylcrssguolse = "unglxdzsruexyhtreqxomgsqvqchbubvnmonfhetiyujwethivpyphbmenfywnvkadhggvftwhioplslclwtoprqccsw";
	double dqpnngmpshvg = 51942;
	double jikvvqgj = 60824;
	bool rcuos = false;
	string hqdwxzb = "yjbcfscnrseiexftml";
	bool oznpaeipwekpoze = true;
	int ssyvblesneocw = 444;
	bool prwbm = false;
	bool xeuojfntyrjabs = true;
	if (false != false) {
		int zf;
		for (zf = 34; zf > 0; zf--) {
			continue;
		}
	}
	if (string("unglxdzsruexyhtreqxomgsqvqchbubvnmonfhetiyujwethivpyphbmenfywnvkadhggvftwhioplslclwtoprqccsw") == string("unglxdzsruexyhtreqxomgsqvqchbubvnmonfhetiyujwethivpyphbmenfywnvkadhggvftwhioplslclwtoprqccsw")) {
		int icyukfqb;
		for (icyukfqb = 90; icyukfqb > 0; icyukfqb--) {
			continue;
		}
	}
	if (string("yjbcfscnrseiexftml") != string("yjbcfscnrseiexftml")) {
		int xyguiclupf;
		for (xyguiclupf = 71; xyguiclupf > 0; xyguiclupf--) {
			continue;
		}
	}
	if (60824 != 60824) {
		int zrnfls;
		for (zrnfls = 0; zrnfls > 0; zrnfls--) {
			continue;
		}
	}
	if (true != true) {
		int vugr;
		for (vugr = 27; vugr > 0; vugr--) {
			continue;
		}
	}
	return string("tppe");
}

string gbqltxh::nwlgahvgteglwdndjkxdl(string gbwzvg, double jsnoisutp, bool pweji, string fpsuwathnwstmp) {
	bool czsgot = false;
	return string("tuymlwslytm");
}

string gbqltxh::dogoufobsuiycejaabhsf(double fzakkfrnzv, int yltsipfyvmx, bool mibtgmcvjxiw, double nhlosnrqtnxehki, string zepicyfdjlyjiek, double dvnurv, int nqunbqvybwb, bool esnruasf, string omrhzsh) {
	int thckwr = 5412;
	int iaxod = 1254;
	bool xzwrpmsyds = false;
	if (5412 != 5412) {
		int kqgqxhlokh;
		for (kqgqxhlokh = 88; kqgqxhlokh > 0; kqgqxhlokh--) {
			continue;
		}
	}
	if (5412 == 5412) {
		int cogshjezut;
		for (cogshjezut = 27; cogshjezut > 0; cogshjezut--) {
			continue;
		}
	}
	if (5412 == 5412) {
		int pknzleiybu;
		for (pknzleiybu = 27; pknzleiybu > 0; pknzleiybu--) {
			continue;
		}
	}
	return string("dduinatchrzwhhqpcd");
}

double gbqltxh::uiujztqfobyuemfukg(string ahzpoana, double nknjtpjxkal, int sfxhzeqnmyr, double swauqygulmck, bool ziuoelbpqcjbkcn, bool rrjzvzsatrhwr, double vgdovryzbkjuxt, double rfrgavdjh) {
	return 17298;
}

double gbqltxh::hgywxtahmwgvyrhqy(int xbetmzi, double ygkbuvhke, string jgsimznrtfru, double fjeudg, string qnnamu, int vlcmtetqptc, bool stqgdjok) {
	return 75119;
}

bool gbqltxh::xakhjiwngcrdvvdfqr(double rcigib, string pqflxrtx, double mutayksdp, double xuafdyvsfamcb, string fbumzjt, double poxcl, string zgktgkrks, bool tklpshx, int eghmwfcgscj) {
	int hjwdruajukfr = 361;
	double codcug = 14140;
	double xkixppqt = 65651;
	bool nkkmp = false;
	int vsosjfummodx = 197;
	double lhdzo = 19125;
	int gldpzgzwul = 6701;
	bool tynvtbxtkzp = true;
	int hkiddcjtrsd = 1626;
	if (false != false) {
		int uhnpk;
		for (uhnpk = 82; uhnpk > 0; uhnpk--) {
			continue;
		}
	}
	return false;
}

int gbqltxh::zptzokehqeuxkjdtpcwulkuh(bool efyyrvyptv, string yvidewtetqgjs, double zssspptuqvdu, double kdtuxpfpusc, bool cuclnrwvtb, bool jynyt, string cslrjhqz, string bvskhrpd, string uicofkhgophe, double ydrqzzzxelriaq) {
	bool opufqg = false;
	bool lhsbdjo = false;
	double wunyudqc = 78437;
	double rxjgsofbqrrbdns = 19870;
	double ejdfou = 32101;
	string cptinpxdsyxmwd = "xonlopuebnadrmiglefokbxvo";
	string pehcbqpvcwmgmo = "zlhucylbnlkavgbrrkeittprhoqojuezclpulqvludgerdbpwlpfxjgyewfexwxjhrsyexmqraxi";
	double wsygivxjq = 58779;
	bool gopbsgi = false;
	if (32101 == 32101) {
		int un;
		for (un = 58; un > 0; un--) {
			continue;
		}
	}
	if (58779 != 58779) {
		int jc;
		for (jc = 70; jc > 0; jc--) {
			continue;
		}
	}
	if (false == false) {
		int ixxegbnvd;
		for (ixxegbnvd = 55; ixxegbnvd > 0; ixxegbnvd--) {
			continue;
		}
	}
	if (58779 != 58779) {
		int dci;
		for (dci = 71; dci > 0; dci--) {
			continue;
		}
	}
	if (32101 == 32101) {
		int bmi;
		for (bmi = 84; bmi > 0; bmi--) {
			continue;
		}
	}
	return 21763;
}

bool gbqltxh::ndawxoncce(string brugjvygx, string okbmwlh, string czavlzdrs, int vejqvtpuqhdfb, double pksetjfggvmahc) {
	double xyyupx = 462;
	int orroxdivjro = 584;
	if (462 != 462) {
		int bcfby;
		for (bcfby = 85; bcfby > 0; bcfby--) {
			continue;
		}
	}
	if (462 != 462) {
		int mdj;
		for (mdj = 88; mdj > 0; mdj--) {
			continue;
		}
	}
	return true;
}

string gbqltxh::ionoarjxzhqjjrb(double mrapwvbr, string wejqbthqwu, bool byridcqwbv, bool juverfgvwdeu, bool zcqwpupnxlfz, bool slhgepgcbuidkyt, int cyuxtyawtqfo) {
	double abfgj = 730;
	double fxetzrrqwjr = 43639;
	bool izviygt = true;
	double fxedik = 34912;
	if (43639 != 43639) {
		int mnrqhq;
		for (mnrqhq = 34; mnrqhq > 0; mnrqhq--) {
			continue;
		}
	}
	if (730 == 730) {
		int vwjxpp;
		for (vwjxpp = 13; vwjxpp > 0; vwjxpp--) {
			continue;
		}
	}
	return string("ayh");
}

bool gbqltxh::rcgfguugafxmtwrh(int jkgcrbgulxwiene, bool cedkpkktysjbaq, string kgvywowheqtp, int yxfowuw, double fgvzavn, int ifprcitk, string mwygf, string dvlwknfy, double btjikv, bool hhkyxxkevhi) {
	int taekfkmeidlb = 3238;
	int flehac = 776;
	int klyebzubuc = 7487;
	bool cqcxkp = true;
	bool kkfkiuekje = false;
	double dnqattxxid = 21091;
	if (21091 == 21091) {
		int lwwe;
		for (lwwe = 13; lwwe > 0; lwwe--) {
			continue;
		}
	}
	if (776 != 776) {
		int lbtarx;
		for (lbtarx = 66; lbtarx > 0; lbtarx--) {
			continue;
		}
	}
	if (3238 != 3238) {
		int avnr;
		for (avnr = 28; avnr > 0; avnr--) {
			continue;
		}
	}
	if (false == false) {
		int jwrpg;
		for (jwrpg = 50; jwrpg > 0; jwrpg--) {
			continue;
		}
	}
	return false;
}

string gbqltxh::flydyvqwjgtydqhbuhjjpyotj(string iwcokwavdercu, double rjkmp) {
	double silmvlmjtembqu = 22950;
	double ijatdqbz = 18648;
	double qtbrbmuuuwnr = 72464;
	bool lgrhhw = true;
	double agdyeumzdykzbzu = 44945;
	bool xtbezywx = false;
	int idnbohsincrem = 1700;
	string yxfcwl = "dnwridugcicerxxcjdpxeixatpqfdamzprsqfooboxgypzhjuhiyyprcgigjewxheloffyxgpgxzugr";
	string lgnudi = "kbnzthrabxawechvgbsjjmcilyluelfvfvpthousmpaibwxgiykpwvkjskgscoqugsnennlyohoswwx";
	if (1700 != 1700) {
		int apfca;
		for (apfca = 73; apfca > 0; apfca--) {
			continue;
		}
	}
	if (string("dnwridugcicerxxcjdpxeixatpqfdamzprsqfooboxgypzhjuhiyyprcgigjewxheloffyxgpgxzugr") != string("dnwridugcicerxxcjdpxeixatpqfdamzprsqfooboxgypzhjuhiyyprcgigjewxheloffyxgpgxzugr")) {
		int gsjvhun;
		for (gsjvhun = 92; gsjvhun > 0; gsjvhun--) {
			continue;
		}
	}
	if (string("kbnzthrabxawechvgbsjjmcilyluelfvfvpthousmpaibwxgiykpwvkjskgscoqugsnennlyohoswwx") != string("kbnzthrabxawechvgbsjjmcilyluelfvfvpthousmpaibwxgiykpwvkjskgscoqugsnennlyohoswwx")) {
		int mztbnrs;
		for (mztbnrs = 65; mztbnrs > 0; mztbnrs--) {
			continue;
		}
	}
	if (18648 != 18648) {
		int euhrwn;
		for (euhrwn = 17; euhrwn > 0; euhrwn--) {
			continue;
		}
	}
	if (string("kbnzthrabxawechvgbsjjmcilyluelfvfvpthousmpaibwxgiykpwvkjskgscoqugsnennlyohoswwx") == string("kbnzthrabxawechvgbsjjmcilyluelfvfvpthousmpaibwxgiykpwvkjskgscoqugsnennlyohoswwx")) {
		int itwyzjbdi;
		for (itwyzjbdi = 58; itwyzjbdi > 0; itwyzjbdi--) {
			continue;
		}
	}
	return string("lbdsxi");
}

int gbqltxh::rnmzqglihkpfsygs(double snuaslxjnnil, bool tygmxpasv, double jgswzoqc, double srpkdxwlptols, bool qzifkwdlmu, double xnyfn, bool zhursipyqps, int rndwouxmt) {
	return 33301;
}

bool gbqltxh::jtvpkfnawdzrfb(string quufkh, int ozdsyowc, double bovkldzwuvw, string tsweddsdofsatmr, string umaxjcqgnjmyrd, string ucpuxeulrmh, int mxezh, double ggbikhmmxnqrx) {
	double quiqyrwukvq = 10189;
	string nxdeurvevsb = "mfigobulevprtcofdsiytodgkwykijcyjymgkkqfnezljrlbajgjtikggfozetzrhhduw";
	bool tocvl = true;
	string umhlbpjvjgve = "qegreecircieqntdhzvzpqtmmlvjipplnlrssudtmdrmnilqpjriautkshtrzpdswygpyh";
	double zjmebjraogvsg = 25879;
	double cdnmjwkmaf = 12947;
	double wpyqrgqvger = 32243;
	string edddtbsjtzz = "mgqheojjmejgjdoceuxfxqooipbnkkhkjegebgkhimfpbqeepcpwryolhunmspflwmghyjijxfyyqvutplzmxtcsqewzyxpfuz";
	double ulxplng = 37106;
	double srojp = 28543;
	if (string("mfigobulevprtcofdsiytodgkwykijcyjymgkkqfnezljrlbajgjtikggfozetzrhhduw") == string("mfigobulevprtcofdsiytodgkwykijcyjymgkkqfnezljrlbajgjtikggfozetzrhhduw")) {
		int sdxqk;
		for (sdxqk = 9; sdxqk > 0; sdxqk--) {
			continue;
		}
	}
	if (37106 != 37106) {
		int eqkqjm;
		for (eqkqjm = 52; eqkqjm > 0; eqkqjm--) {
			continue;
		}
	}
	if (25879 != 25879) {
		int matxsroktu;
		for (matxsroktu = 48; matxsroktu > 0; matxsroktu--) {
			continue;
		}
	}
	return false;
}

string gbqltxh::yqzeerjnqkwtlbuoewyhv(string kbmfwk, int sumjicabwnspnta, bool vbyucdxx, bool mokyk, int varvppsdqditxq, bool jjmjvzmc, bool eqlwebaodtn, int euenzwtnzxr) {
	double uxjqxubpmgn = 6082;
	string ffrwqqfszp = "uwndnrldqosgpxnokkmlirvtgconlfghcmymthsedyqzibxisqoupvjtgjwushecfbspigpbdyuikelhrigdao";
	if (6082 != 6082) {
		int ju;
		for (ju = 44; ju > 0; ju--) {
			continue;
		}
	}
	if (string("uwndnrldqosgpxnokkmlirvtgconlfghcmymthsedyqzibxisqoupvjtgjwushecfbspigpbdyuikelhrigdao") != string("uwndnrldqosgpxnokkmlirvtgconlfghcmymthsedyqzibxisqoupvjtgjwushecfbspigpbdyuikelhrigdao")) {
		int umrop;
		for (umrop = 20; umrop > 0; umrop--) {
			continue;
		}
	}
	if (string("uwndnrldqosgpxnokkmlirvtgconlfghcmymthsedyqzibxisqoupvjtgjwushecfbspigpbdyuikelhrigdao") != string("uwndnrldqosgpxnokkmlirvtgconlfghcmymthsedyqzibxisqoupvjtgjwushecfbspigpbdyuikelhrigdao")) {
		int dvdgwlv;
		for (dvdgwlv = 31; dvdgwlv > 0; dvdgwlv--) {
			continue;
		}
	}
	return string("jgwr");
}

int gbqltxh::qsbjnqjdsepainnc(bool jfsiqii, string hjbypzfdgoy, double wggazws, double fwklfrvgd, bool zpxesv, double aznrkgxggmej, double niwfy, double tomzdgchrvnvdt) {
	bool webiyge = false;
	bool mccxjumc = false;
	string exyne = "qggtfpfosqnwbrehiscmjjyexkyahxovexhxeaolemyahrorwwzzwglcydurqwazkgejhdafwlskiswnrjxibu";
	double fzain = 3488;
	int nfiqckb = 4296;
	int euskv = 41;
	bool oljgyx = true;
	string hgsexqpgopdnq = "";
	int zobqj = 4772;
	double aokppblmujees = 20810;
	if (41 != 41) {
		int qr;
		for (qr = 4; qr > 0; qr--) {
			continue;
		}
	}
	if (4772 != 4772) {
		int qhwdnzp;
		for (qhwdnzp = 64; qhwdnzp > 0; qhwdnzp--) {
			continue;
		}
	}
	if (41 != 41) {
		int bxlt;
		for (bxlt = 43; bxlt > 0; bxlt--) {
			continue;
		}
	}
	if (3488 != 3488) {
		int iuws;
		for (iuws = 11; iuws > 0; iuws--) {
			continue;
		}
	}
	if (false != false) {
		int zvscwfzmdl;
		for (zvscwfzmdl = 27; zvscwfzmdl > 0; zvscwfzmdl--) {
			continue;
		}
	}
	return 74188;
}

void gbqltxh::dtwcklrfywzfnxjzphqoqvxsu(double mjltkkjmq) {
	int svqzzfouixoe = 3543;
	double vucjusx = 17270;
	bool llnrc = true;
	double lxeikm = 7793;
	int ngtnntakpbn = 1448;
	bool aoyubozr = false;

}

bool gbqltxh::inqiguzwqvjvt() {
	string dtnkpnhvyxj = "aio";
	int sroebn = 5523;
	bool quhgjfmo = true;
	int ntfwvcmtadis = 208;
	int psdzfqcrb = 897;
	double gkhlwvoxgytj = 7717;
	bool jccujp = false;
	string czzflumcm = "vqbfooohg";
	if (208 == 208) {
		int dbnymo;
		for (dbnymo = 91; dbnymo > 0; dbnymo--) {
			continue;
		}
	}
	return true;
}

string gbqltxh::qdxcmupxnaojobe(bool ndsxjxnrtzz, string waceo, int qgxxaamhhivhx, string ntevhalisr, bool stoie, string pfeuk, bool drbsxkocacdhexj, int ntcmkybbtiu, double icxrrfrmfwxtjvq, int nfbqrubwpfiqzoq) {
	bool isulzljktrzwrzg = false;
	string lbapxgruqg = "goxbnextivfbdlzqihqgnkmhkyavfgtyjawlwdnmaxxwqwqcanb";
	double iyvtkj = 33680;
	string gwyzvd = "atdtjdcsksdaudeylnuwmydpqbgvozkxntogstvnueundsuljqrpqeohouduymyu";
	if (string("goxbnextivfbdlzqihqgnkmhkyavfgtyjawlwdnmaxxwqwqcanb") == string("goxbnextivfbdlzqihqgnkmhkyavfgtyjawlwdnmaxxwqwqcanb")) {
		int ic;
		for (ic = 24; ic > 0; ic--) {
			continue;
		}
	}
	if (string("goxbnextivfbdlzqihqgnkmhkyavfgtyjawlwdnmaxxwqwqcanb") != string("goxbnextivfbdlzqihqgnkmhkyavfgtyjawlwdnmaxxwqwqcanb")) {
		int amk;
		for (amk = 44; amk > 0; amk--) {
			continue;
		}
	}
	if (33680 != 33680) {
		int lsanwa;
		for (lsanwa = 25; lsanwa > 0; lsanwa--) {
			continue;
		}
	}
	return string("vctlkvkdhlgqmbubb");
}

bool gbqltxh::zzfwwdlicxbpfvcyitew(string wmefndvtylvb, double yorcd, double mzgkor, bool olpfcnvupiburs, string ysjnywfgod) {
	int zlxstefmhwbvo = 83;
	string sczwwdxhvccdct = "bddexjegpejjkdiplkejdbjaetlxwaiizbdknenjakqvlcaqjobzymvrjlnpwqjcbapoem";
	string fbbcxpbbxhej = "emeiyubivya";
	return false;
}

double gbqltxh::qdbwuxdzczytjxaxmljvmfqfc() {
	bool jrjsddywnhvj = true;
	int dtkiu = 4333;
	int jjcqoxoqrrt = 5774;
	int lphfz = 2981;
	string kzjvahsldfxwmrk = "amxmnqxfpzravsznoxyiftcanbkkbafeijwccmpghhnhwrcvteeshlwhmtxafnpazwitvyqlghdonnhdcewoyapzwchoplygzfcv";
	int nugwvmn = 2372;
	if (true != true) {
		int rqoyb;
		for (rqoyb = 54; rqoyb > 0; rqoyb--) {
			continue;
		}
	}
	return 90593;
}

int gbqltxh::rwxefdbiuddfjhc(double ybgiwzb, string kgkzklssixojgdk) {
	string hvpkunbdxfmx = "mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr";
	if (string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr") == string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr")) {
		int cfs;
		for (cfs = 89; cfs > 0; cfs--) {
			continue;
		}
	}
	if (string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr") != string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr")) {
		int pay;
		for (pay = 25; pay > 0; pay--) {
			continue;
		}
	}
	if (string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr") == string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr")) {
		int khjnji;
		for (khjnji = 78; khjnji > 0; khjnji--) {
			continue;
		}
	}
	if (string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr") != string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr")) {
		int spqlwux;
		for (spqlwux = 85; spqlwux > 0; spqlwux--) {
			continue;
		}
	}
	if (string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr") == string("mvlxwfcxxmhyaxdwgkftrpywhwgpgtwzofvcegucwjkygmnslr")) {
		int nz;
		for (nz = 44; nz > 0; nz--) {
			continue;
		}
	}
	return 64916;
}

gbqltxh::gbqltxh() {
	this->yqzeerjnqkwtlbuoewyhv(string("nkxgkfclhb"), 1455, false, false, 507, false, true, 4260);
	this->qsbjnqjdsepainnc(true, string("cjzcsffsbcwehmvffpvvxbsfmksjvguawvbloobhrdutmwixaoluzghfddsccrvqzhaszxtxx"), 42101, 28906, false, 8640, 3458, 41658);
	this->dtwcklrfywzfnxjzphqoqvxsu(29175);
	this->inqiguzwqvjvt();
	this->qdxcmupxnaojobe(true, string("jmzbimolukidlzdwibsvicuovspuzrrsakxvvbvguiriickdxtukbfxpesaedaanmhjflffnygycyukq"), 361, string("yowyvwfumgphxryuysbfnnmvffenravnoyhj"), false, string("lzhvicwakfbhqjpvxwbdhiplfqrsqnuxltbhsyzivqcnrvoctevpbgukypqooydnvspmuedqfffpwnxzczkl"), false, 1226, 25594, 1328);
	this->zzfwwdlicxbpfvcyitew(string("abzrhxhkkpmwwhgcroywemzkkirtwnyknikqyrgsikjyznoutdolxxaktllwhayzvzp"), 39508, 35805, false, string("vawgbmxdgv"));
	this->qdbwuxdzczytjxaxmljvmfqfc();
	this->rwxefdbiuddfjhc(42, string("klntdmgdyfhwjaqwltsgynzrpyklelfphabjwbiauezvwwdpfg"));
	this->zptzokehqeuxkjdtpcwulkuh(false, string("zqvhkyiffmicfdpqukjocehkyckxaunycdefoawmpvfdaaeewwcdvzbowlerkrbktbfwkidejdcdgazopkdctamwywjebbxksyl"), 37551, 14334, true, true, string("ucztlhkmkjzqyaxpwfnlstkarcelftfudbhfunsquixstvjdgrbmkmacgknkduylhgdsvqtdvsgit"), string("hwcjbpxaobolvlxzaqnsbesvfvkszmutpvlvnwhmekkmlourrtt"), string("yfghczllwetd"), 46638);
	this->ndawxoncce(string("zuezzbewvdealabzpwvrjzqsalpqtyzxxbtdkwposzjxxjeuaasggjzhxwivfajhihnaeyggqqjihvqbcmpsweutjxek"), string("gcstcppntdpgfuhckkvelnqrugsfjdkiirfoxnopjluthqigtyrxumuqgacay"), string("tkdgbyiagmryjlwshctyqpeztspbhulltijhjhivkwzvfsebbbhgizcltjnysvdhtyzarlwzhseptrrqjaqvryausn"), 1788, 8877);
	this->ionoarjxzhqjjrb(40088, string("kvrfonpvllacoivhqogldxbzvylgkvsuauahryulttdoswwocvhvhfwbggxboalmivohtuxgzabzyiqxrkjrocm"), false, true, true, true, 6456);
	this->rcgfguugafxmtwrh(1959, true, string("rjffrqwexywduikyekhcdmwzzowniago"), 2202, 59422, 6317, string("dolwwrkysrvxtatduvchfszeineuypjxqijyupbhpyizjwnibctnetmboqhqqm"), string("kbfxesfdvnutjzvdrchxhxmhcgbkbaipvcxaiugvxezsbdquzmslqhxgqdqkddbqtsgyzotllcvajhbulkyeaswmrwqceyn"), 23659, false);
	this->flydyvqwjgtydqhbuhjjpyotj(string("yrhgzvlepwhianxjrymvhgucigxloldvxfslbyebtjlocxsyzfnyloixjbyskackivoruvysu"), 24755);
	this->rnmzqglihkpfsygs(7308, true, 19395, 15831, false, 4225, true, 2812);
	this->jtvpkfnawdzrfb(string("vfozrnj"), 5858, 7682, string("pnjmdckqtqcxvwrniucrmaovggrejjnpbygbxtb"), string("xqkxuibbsiwcghbtiazlekrrdybjdgbisrnamwiqqlfjfvnuyqwjfoyrcrmarhbkhcdsgsoovgprtvb"), string("rnpprrcrmzdvajquqxweujzvyp"), 3450, 812);
	this->hduhpiozcuzgypplzoditdaoa(47916, true, string("ynvlevqmzqnboyyrbbk"), string("rbcnxdvwlzpnsmiewdegejoagi"), string("reqproqmovcuphjdaaodpacgzrrewvedigckvnayumfvrtu"), string("aajdyukspccxyacsxgifafpbukkmaosntxgupxigoqrfqsoitdqkcsmiunwtvyzlbhafavyyvrz"), 180, true, string("nrnonqtstljxovsihgboxxqprnsecmnfwtszxoglqtucuvtxqhobcfpqydpuslhxwrpzzlmwnayegefgaywluheg"));
	this->naqarxgzaqrtlq(string("znhsaaoadknhugsddxhgnidksorkqsczsaraqlursafilpmaiusooomvbrjcagrxavxhstfygm"), 27221, 4390, 1171, 56430, true, false);
	this->divpqqpclb();
	this->nwlgahvgteglwdndjkxdl(string("rgitktjdoevslqxicwyozifahsstdawreanwobipwwrpclkqnuduuhawqmneuqy"), 32513, true, string("yex"));
	this->dogoufobsuiycejaabhsf(31217, 45, true, 15317, string("eqmqqlfgjgdbpnqmv"), 69337, 5957, true, string("ihcgvwfnhsbgrdkw"));
	this->uiujztqfobyuemfukg(string("wponnjqzzfocaibcpqizmxyfzvsmvrmvg"), 7857, 3772, 84893, false, true, 43, 39087);
	this->hgywxtahmwgvyrhqy(152, 31004, string("ro"), 46302, string("gmsdgdpkpckgahvganranorowxpddltoulkxp"), 7119, true);
	this->xakhjiwngcrdvvdfqr(44524, string("ncwwe"), 75489, 27294, string("etlzjxtzmpidymgosdjlxcpdmlsemujdpayblwpaqamvbtrifhgenhltenjsmynxplcgfglfgzouxanfyboczt"), 31841, string("rclrbkndxoziopzdfqqnrcgzxcjgxjrpcqohgttdnbyufcklrbgywcdqndgyrabnfgoglnfbtlcrbqkohspsfuwfyfie"), false, 3853);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class oocakwj {
public:
	bool gsklof;
	double eritlpbndsiltg;
	int sksrwza;
	oocakwj();
	string xmlcjkmqwoszgumg(bool pdzlyluhzrvf, bool zjhteatrbae, bool ykuezmxsdufdxx, bool tryqc);
	int hejrmjcjxkqu(int mzoigkqv, double kvdxeehbu, int swrjwtx, double mdjnorbnnpl, string ynlvurqx);
	void fpfgdpsxwjrv(string xtcijtsuspyzqp);
	bool lntajryitc(string takowpcczydhhy, int wtznanqzyomhk, string ygggtvxzrfz, double jjrtrtzgpis, bool ufubs, double uhwkryyozbsy, double izflo, bool dfhkxgjox, string hfyxgypwgv, int shstpc);
	bool wdbrotoukf(double lhkxjwlsjewxm, bool nexsqtuefeenepj, int nqqdwyq);
	double mfgjamxjjlacditpmqpvrli(string dsnckmmyye, int dezmwsconjl);
	int kktbykbpgnp(string rityozgyladxmwh, string qxungt, bool tekddglkz, string cfxau);

protected:
	int kjyhwklkn;
	double pidxeoab;

	double xahzinqemed(bool dutqzltzxvzmc, bool ojaxp, double eopidl, bool lohvujxiqi, bool wcwnxweifm, string eeesuuozjw);
	double xlfvcrmbisfsodhdpacqj(string sanktyj);
	bool gltgmasugnzktbt(int ziqixieigxg, bool dfzasmbsfud);
	double jqbfgpnumhykzof(bool burmzxmfiniiyap, bool byslanvdkb, double wvnyvyuqfwg, int fbjipksiesvgtv, double hcbfcdvdqdyty, double ferigfvk, string vbvwrmyvvbs, string xzfrmkomdlx, string zbauwezbvtk, bool oabzpwb);
	int rojiruhaezorfytbiptqpdrua(double jsexmbcup, double mqlbst, string zrzymnqr, bool ooapqcinpce, double ikagvbrkdord, int hyxkrwhww, double xditddzmqdpgqdv, double wabepniiphdou, bool hvyunyr);
	void xnibhvhtfjauovw(double mueebtdozpbzkk, int jwejt, bool jchnkucil, bool cgsjka, bool lgjppchmju, bool apckhxixx);
	string polegbaxbtesd(double jpmztrepvbnmlw);

private:
	int cpewougmovzr;
	string ylhdlczereq;

	bool nwdosryklafvmpywzi(string ggqpodhwuwubolj, double htlcofirczqs, string pjgsod, string lyjiwdaq, bool ifadoflcnzmmqyo, bool asilwxtjz, string xbfvkwtiwf, int xubyynz, int bdqqzxnf, string tgdffry);
	bool ahcbggrnxfesafegsnlpg(int cixzsqtfxwu, int slogodacg, string lhmlo, string jolixbyxkutbs);
	string hjjysuudvttpzr(string kvtpykl, double blkzgrrb, int dhoqiqotmmybj, string etuzexxhp, int hepftxkbgy, double adqheykoxfyhy, bool kqsuoaebalch, double gcnsc, int jkieyqqphdqqf);
	int sanfcrtsnfpfgoulvgzrbz(string bhdqpqtbmexkyb, double iyzmrcpcjr, string xjpqv, string lfafqwxxu, bool jhjwtmbatov, bool kpulqgneba, double plymykryidjtp);

};


bool oocakwj::nwdosryklafvmpywzi(string ggqpodhwuwubolj, double htlcofirczqs, string pjgsod, string lyjiwdaq, bool ifadoflcnzmmqyo, bool asilwxtjz, string xbfvkwtiwf, int xubyynz, int bdqqzxnf, string tgdffry) {
	int ajnrsjsjl = 1470;
	double vrkftkapykwxqau = 23321;
	bool pyvtblafglwcijj = true;
	int eeefwux = 4363;
	bool fquks = true;
	bool dahrxmx = false;
	int glnndulm = 3267;
	bool bgnsokrh = false;
	string smsqo = "xsjafonrdfjxaypboooyghghhlumgftwvpsulkjvuwpfcofhqvmqhpseqszuswpjqzqjt";
	if (string("xsjafonrdfjxaypboooyghghhlumgftwvpsulkjvuwpfcofhqvmqhpseqszuswpjqzqjt") != string("xsjafonrdfjxaypboooyghghhlumgftwvpsulkjvuwpfcofhqvmqhpseqszuswpjqzqjt")) {
		int nnai;
		for (nnai = 41; nnai > 0; nnai--) {
			continue;
		}
	}
	if (1470 != 1470) {
		int fmocnky;
		for (fmocnky = 74; fmocnky > 0; fmocnky--) {
			continue;
		}
	}
	if (3267 != 3267) {
		int wdkbnwwn;
		for (wdkbnwwn = 14; wdkbnwwn > 0; wdkbnwwn--) {
			continue;
		}
	}
	if (true == true) {
		int raqaaagrrp;
		for (raqaaagrrp = 79; raqaaagrrp > 0; raqaaagrrp--) {
			continue;
		}
	}
	return true;
}

bool oocakwj::ahcbggrnxfesafegsnlpg(int cixzsqtfxwu, int slogodacg, string lhmlo, string jolixbyxkutbs) {
	double gtxmykykihk = 74367;
	double vcxnpqv = 5589;
	string gvsfjcgpg = "ottpyrpqlpcllgmsywhmlghxgojdeclvcgnxbluhcjrzytnjfmrpgkduunryfgolsuwjjmguxly";
	bool pgozpizacm = false;
	bool wxcwbspuvheut = true;
	if (5589 != 5589) {
		int uclkq;
		for (uclkq = 99; uclkq > 0; uclkq--) {
			continue;
		}
	}
	return true;
}

string oocakwj::hjjysuudvttpzr(string kvtpykl, double blkzgrrb, int dhoqiqotmmybj, string etuzexxhp, int hepftxkbgy, double adqheykoxfyhy, bool kqsuoaebalch, double gcnsc, int jkieyqqphdqqf) {
	double ewhgfjgvjfad = 48230;
	int qfqiaufazwszrl = 2770;
	if (2770 == 2770) {
		int faeyq;
		for (faeyq = 81; faeyq > 0; faeyq--) {
			continue;
		}
	}
	if (2770 != 2770) {
		int gprr;
		for (gprr = 68; gprr > 0; gprr--) {
			continue;
		}
	}
	if (2770 == 2770) {
		int mgdm;
		for (mgdm = 100; mgdm > 0; mgdm--) {
			continue;
		}
	}
	return string("qkskdxveu");
}

int oocakwj::sanfcrtsnfpfgoulvgzrbz(string bhdqpqtbmexkyb, double iyzmrcpcjr, string xjpqv, string lfafqwxxu, bool jhjwtmbatov, bool kpulqgneba, double plymykryidjtp) {
	int zmjsx = 2090;
	bool rdytgazujeh = false;
	bool fvppiutfc = true;
	double mubogcvfj = 21796;
	bool tbpevpvjnblnk = true;
	if (true == true) {
		int alfnehx;
		for (alfnehx = 27; alfnehx > 0; alfnehx--) {
			continue;
		}
	}
	if (2090 == 2090) {
		int kl;
		for (kl = 61; kl > 0; kl--) {
			continue;
		}
	}
	return 89315;
}

double oocakwj::xahzinqemed(bool dutqzltzxvzmc, bool ojaxp, double eopidl, bool lohvujxiqi, bool wcwnxweifm, string eeesuuozjw) {
	return 54931;
}

double oocakwj::xlfvcrmbisfsodhdpacqj(string sanktyj) {
	string uzvjogetqit = "ndzqvpwbwwcdj";
	double ypqmjdzlzw = 25444;
	double yfffnpxzfnhi = 25131;
	string fwzjjwnrpi = "gwwhygneplawv";
	double debqfcowsnxbwhu = 11686;
	bool exithkcyq = true;
	if (string("gwwhygneplawv") != string("gwwhygneplawv")) {
		int qarvycgsa;
		for (qarvycgsa = 90; qarvycgsa > 0; qarvycgsa--) {
			continue;
		}
	}
	if (string("ndzqvpwbwwcdj") != string("ndzqvpwbwwcdj")) {
		int kycr;
		for (kycr = 17; kycr > 0; kycr--) {
			continue;
		}
	}
	if (true == true) {
		int gnlcxgzn;
		for (gnlcxgzn = 98; gnlcxgzn > 0; gnlcxgzn--) {
			continue;
		}
	}
	return 10267;
}

bool oocakwj::gltgmasugnzktbt(int ziqixieigxg, bool dfzasmbsfud) {
	bool gajvoqx = true;
	double dlbxsgex = 14232;
	double gggcawa = 43533;
	bool kbhjlmfudzho = true;
	string kkrbovpewvtii = "uigegclbxfaedmrmmeslabcgbqzlvugagvzostdilhavopjewixhrrhwqyjfzjjkpjrkdz";
	int zqyorntgunewow = 2712;
	string xiuqwrvzk = "pzrazpodowkilyhsriphllmnnlvdrbfhszscnoemktnxhngmhlltdb";
	double czimybkjolrjaa = 26742;
	if (true == true) {
		int lecp;
		for (lecp = 13; lecp > 0; lecp--) {
			continue;
		}
	}
	if (string("uigegclbxfaedmrmmeslabcgbqzlvugagvzostdilhavopjewixhrrhwqyjfzjjkpjrkdz") != string("uigegclbxfaedmrmmeslabcgbqzlvugagvzostdilhavopjewixhrrhwqyjfzjjkpjrkdz")) {
		int wvzmmsweb;
		for (wvzmmsweb = 100; wvzmmsweb > 0; wvzmmsweb--) {
			continue;
		}
	}
	if (string("pzrazpodowkilyhsriphllmnnlvdrbfhszscnoemktnxhngmhlltdb") != string("pzrazpodowkilyhsriphllmnnlvdrbfhszscnoemktnxhngmhlltdb")) {
		int dg;
		for (dg = 83; dg > 0; dg--) {
			continue;
		}
	}
	if (14232 == 14232) {
		int tlvtkbvt;
		for (tlvtkbvt = 9; tlvtkbvt > 0; tlvtkbvt--) {
			continue;
		}
	}
	return false;
}

double oocakwj::jqbfgpnumhykzof(bool burmzxmfiniiyap, bool byslanvdkb, double wvnyvyuqfwg, int fbjipksiesvgtv, double hcbfcdvdqdyty, double ferigfvk, string vbvwrmyvvbs, string xzfrmkomdlx, string zbauwezbvtk, bool oabzpwb) {
	double fmtyhiwkraqxy = 30072;
	double ienbcdez = 69120;
	double hislx = 14810;
	bool oqactjf = true;
	double ivldhkd = 3483;
	return 95651;
}

int oocakwj::rojiruhaezorfytbiptqpdrua(double jsexmbcup, double mqlbst, string zrzymnqr, bool ooapqcinpce, double ikagvbrkdord, int hyxkrwhww, double xditddzmqdpgqdv, double wabepniiphdou, bool hvyunyr) {
	string mbcdjrrbcynoai = "lluxysznqojvpsjqjdgixqtjpxjrjbfdmsecibfkfchjbvzmgfcpmixhnsfxmqzfrvvvpimqvgtkdglku";
	string uxlfrzfjuqeh = "iuxzcapljcighvakgoeuqwojk";
	bool eyqwfxt = false;
	double xvsatbewxral = 52241;
	string cswaky = "mpfxbwfnutekifeveeqepsyxompgiqphfnpqapsnmt";
	bool ybafcxuyet = true;
	string ieriuboulagino = "dyjwhqdndaahsiakncf";
	bool gtfhk = true;
	if (52241 != 52241) {
		int nnyi;
		for (nnyi = 60; nnyi > 0; nnyi--) {
			continue;
		}
	}
	if (string("dyjwhqdndaahsiakncf") == string("dyjwhqdndaahsiakncf")) {
		int bfx;
		for (bfx = 12; bfx > 0; bfx--) {
			continue;
		}
	}
	if (string("mpfxbwfnutekifeveeqepsyxompgiqphfnpqapsnmt") == string("mpfxbwfnutekifeveeqepsyxompgiqphfnpqapsnmt")) {
		int qydntzun;
		for (qydntzun = 49; qydntzun > 0; qydntzun--) {
			continue;
		}
	}
	if (string("iuxzcapljcighvakgoeuqwojk") == string("iuxzcapljcighvakgoeuqwojk")) {
		int fpswcfwvbh;
		for (fpswcfwvbh = 93; fpswcfwvbh > 0; fpswcfwvbh--) {
			continue;
		}
	}
	if (string("dyjwhqdndaahsiakncf") != string("dyjwhqdndaahsiakncf")) {
		int ncfol;
		for (ncfol = 55; ncfol > 0; ncfol--) {
			continue;
		}
	}
	return 44658;
}

void oocakwj::xnibhvhtfjauovw(double mueebtdozpbzkk, int jwejt, bool jchnkucil, bool cgsjka, bool lgjppchmju, bool apckhxixx) {
	double ihtpevqwey = 3370;
	string gnrxl = "ocwyterkxfoonqaa";
	double wdfigrufl = 50148;
	bool sfmapisahz = true;
	string gefpto = "mgnzddslcjtispcxkzwsrjpmfoutggrbipyevshiivvtdiewjjqissqyzbfnvzzmhxfmtbwwxhcawdmshbwnluukvleis";
	bool ogdiemstddf = true;
	if (string("mgnzddslcjtispcxkzwsrjpmfoutggrbipyevshiivvtdiewjjqissqyzbfnvzzmhxfmtbwwxhcawdmshbwnluukvleis") == string("mgnzddslcjtispcxkzwsrjpmfoutggrbipyevshiivvtdiewjjqissqyzbfnvzzmhxfmtbwwxhcawdmshbwnluukvleis")) {
		int ecczg;
		for (ecczg = 48; ecczg > 0; ecczg--) {
			continue;
		}
	}
	if (true != true) {
		int xlebqd;
		for (xlebqd = 79; xlebqd > 0; xlebqd--) {
			continue;
		}
	}
	if (string("mgnzddslcjtispcxkzwsrjpmfoutggrbipyevshiivvtdiewjjqissqyzbfnvzzmhxfmtbwwxhcawdmshbwnluukvleis") == string("mgnzddslcjtispcxkzwsrjpmfoutggrbipyevshiivvtdiewjjqissqyzbfnvzzmhxfmtbwwxhcawdmshbwnluukvleis")) {
		int bcklufmxxe;
		for (bcklufmxxe = 25; bcklufmxxe > 0; bcklufmxxe--) {
			continue;
		}
	}

}

string oocakwj::polegbaxbtesd(double jpmztrepvbnmlw) {
	bool zsavrqaeadfsnt = true;
	double ureqswkzdijm = 72683;
	double wiyjoymyhftx = 23346;
	string bwttko = "reolje";
	string hogpmcbflwd = "nvfrmvyjwbigmncxdrxyblxiqapkhgpsmvhjdasjflfoyygzzopelrriarwpw";
	int rycvia = 2713;
	double vhhcakmfuaddo = 18020;
	if (72683 == 72683) {
		int hm;
		for (hm = 27; hm > 0; hm--) {
			continue;
		}
	}
	if (string("reolje") != string("reolje")) {
		int lq;
		for (lq = 24; lq > 0; lq--) {
			continue;
		}
	}
	return string("ihjccoakeijashonzt");
}

string oocakwj::xmlcjkmqwoszgumg(bool pdzlyluhzrvf, bool zjhteatrbae, bool ykuezmxsdufdxx, bool tryqc) {
	int ykpuqwkseezkvy = 3806;
	int ajvjyod = 6138;
	string palindxwbdc = "bvdfpfaqmritku";
	double srzliuitjzylvuy = 38341;
	bool fnwdk = true;
	int allrecyqfsxa = 1215;
	int weljnf = 415;
	bool dzptzipkul = false;
	double zwblxgzilmc = 41341;
	double pvpfsphuftwbjei = 20916;
	return string("vsiofmt");
}

int oocakwj::hejrmjcjxkqu(int mzoigkqv, double kvdxeehbu, int swrjwtx, double mdjnorbnnpl, string ynlvurqx) {
	bool vosglgvgsotws = true;
	if (true != true) {
		int opak;
		for (opak = 49; opak > 0; opak--) {
			continue;
		}
	}
	if (true != true) {
		int xkgyhlrvp;
		for (xkgyhlrvp = 91; xkgyhlrvp > 0; xkgyhlrvp--) {
			continue;
		}
	}
	if (true == true) {
		int jmxicmcjd;
		for (jmxicmcjd = 100; jmxicmcjd > 0; jmxicmcjd--) {
			continue;
		}
	}
	if (true != true) {
		int pdgxnixr;
		for (pdgxnixr = 61; pdgxnixr > 0; pdgxnixr--) {
			continue;
		}
	}
	return 13244;
}

void oocakwj::fpfgdpsxwjrv(string xtcijtsuspyzqp) {
	double zchetk = 59507;
	bool qlfgxcyyx = true;
	double ulvph = 9244;
	bool idnfkwgkfp = true;
	double pcwhoimnm = 14329;

}

bool oocakwj::lntajryitc(string takowpcczydhhy, int wtznanqzyomhk, string ygggtvxzrfz, double jjrtrtzgpis, bool ufubs, double uhwkryyozbsy, double izflo, bool dfhkxgjox, string hfyxgypwgv, int shstpc) {
	bool xmpmjmqnmtba = true;
	double exwhpfeh = 19168;
	bool dtefyzprmtgg = false;
	int wmqilnhwc = 2788;
	double frzakwanuw = 12338;
	double jcjqkmkcje = 23398;
	int pfedegel = 723;
	bool akbrwpqugxhcatf = false;
	if (false == false) {
		int bhx;
		for (bhx = 22; bhx > 0; bhx--) {
			continue;
		}
	}
	if (723 != 723) {
		int fmszjhqluj;
		for (fmszjhqluj = 66; fmszjhqluj > 0; fmszjhqluj--) {
			continue;
		}
	}
	if (12338 == 12338) {
		int ggdgemlln;
		for (ggdgemlln = 67; ggdgemlln > 0; ggdgemlln--) {
			continue;
		}
	}
	return false;
}

bool oocakwj::wdbrotoukf(double lhkxjwlsjewxm, bool nexsqtuefeenepj, int nqqdwyq) {
	double lqsbtlcvkp = 22246;
	int oxzubtybn = 2924;
	int hyhfsrzam = 1453;
	double evaduotmo = 60925;
	int tnpfgaqo = 5887;
	bool mhuhdykyxpgl = false;
	int cnbmbgxqj = 1131;
	double gdrbjusxzwb = 26896;
	string uoeypdipg = "p";
	if (26896 != 26896) {
		int bogitck;
		for (bogitck = 4; bogitck > 0; bogitck--) {
			continue;
		}
	}
	return false;
}

double oocakwj::mfgjamxjjlacditpmqpvrli(string dsnckmmyye, int dezmwsconjl) {
	double mbjjcdvfrap = 46663;
	string bappuggkb = "usesvvlyhbobtrzefqsvyafkzuoplrcpkpaduhvdkiryrbzrkrkehavrktgbdghizdqsjimmtyogcetwfylzxxnkmc";
	bool uoxlhfxpwvb = false;
	string bgkfunz = "gugtdtfqabcccmovvxzgryqatchsigtwwnqnfythonvinhkmvgozggyqucmgqbhtekxbmd";
	return 83770;
}

int oocakwj::kktbykbpgnp(string rityozgyladxmwh, string qxungt, bool tekddglkz, string cfxau) {
	bool cptozscyr = false;
	int kgwlehtl = 1204;
	return 8056;
}

oocakwj::oocakwj() {
	this->xmlcjkmqwoszgumg(true, true, true, false);
	this->hejrmjcjxkqu(3321, 66150, 1077, 5274, string("zfsawxmthdwyrrolewzdyzauqvvdvjsgmdjrh"));
	this->fpfgdpsxwjrv(string("jueftjbrgzhprwqwwwrdjxbftgfqbrvgbxxhhmvkpnripsjdacinftukubc"));
	this->lntajryitc(string("uvibwdvblvulehjwsldlbtsk"), 3139, string("audbbsabnk"), 2364, true, 8472, 22739, true, string("dvgouhnyxqrafvvevptjqnvipsxkbtizjghgssjogi"), 676);
	this->wdbrotoukf(35722, false, 7043);
	this->mfgjamxjjlacditpmqpvrli(string("lmiduacxgahbytncdaesxddaxsishwvtdszwatpqeacpvvthwpjnxabwxuwkfzbuduwmubyglgatpdwglbifl"), 4207);
	this->kktbykbpgnp(string("lqsyugusahzlcdxffpizrugmrkyrvxqrqzfmxf"), string(""), true, string("yjqvcpsomdqyhahcipeemcufotjdmmpgioefvcwtpzhjjrfqwysyezgmemrcchveidwwnqzvdzexwqplspiucilwku"));
	this->xahzinqemed(false, true, 14402, true, true, string("mhgpkzahmyyauyeuzzfsnnttfhdjzrmm"));
	this->xlfvcrmbisfsodhdpacqj(string("ckwuxmpfhnydfvqnldlxpbebvskkdqoijlrrtmsihfexojcpghaznelwjoattmxt"));
	this->gltgmasugnzktbt(1364, true);
	this->jqbfgpnumhykzof(true, false, 17142, 960, 35123, 57326, string("uozkebvfyckjwacobugpjqzjldlqofgjabuyyrjimokktslp"), string("irttyvieuplkjqotltoybriocvztvdetxfrynzfhsutnmblescflvconjedkhovs"), string("nzqsxiopdhctnibhbbwedyropbooxs"), false);
	this->rojiruhaezorfytbiptqpdrua(33057, 24480, string("qgbcbauofhnrhlvsspkg"), true, 14684, 1389, 57407, 14237, true);
	this->xnibhvhtfjauovw(876, 2494, false, false, true, true);
	this->polegbaxbtesd(91179);
	this->nwdosryklafvmpywzi(string("nmkhhtwoxixjudzvlcftcclyjmxfdhpktuasgjgpjafhkhivgzugfmgkv"), 43328, string("esywxc"), string("imgg"), true, true, string("irckljrxjynvafnetibxzgydlswxukbzqnjxsqatpljlqmcimjyspvfrfjdgntkwveiewmybbbdulheyawtfyzqsvlneijlsex"), 4394, 1681, string("zsnfnjvytfdsfcwwqqmfonaobimukapydutqvymblucwmxbaolnizmigmceyfiqanyhhi"));
	this->ahcbggrnxfesafegsnlpg(6348, 323, string("olhwhdimoidnapogfcewhrobomsjqrkupposvisywhavsuhhqpjltohudwrhehlpdgmgmyhsaqexiqxfhkkkvqcgmegdhlhs"), string("qogzxzouidbdrngiiiquaanhctktnzehuepwjfrveeuinovfwizzdatiflomkwebcfllorhbdyduubkdlqsickhrpdbqhyfuyfj"));
	this->hjjysuudvttpzr(string("hbgkyjqtoyhdxv"), 4818, 811, string("lfxbgmdnwhtaeepqqzelkdfcsnrvtvwhtabzepbmktngasqqiqtlownfwsovhxwkrpvpecdwnneaaxszanzom"), 2093, 58251, true, 14028, 678);
	this->sanfcrtsnfpfgoulvgzrbz(string("aivkz"), 21472, string("ctwqoanylhykcpbmrryqofedrfzjcjzvvfuwgxl"), string("tuiqqzrajhgcrxsnlxneajbtlwuzlktukydjm"), false, true, 58358);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class aukimvz {
public:
	string oodms;
	string vsbkb;
	aukimvz();
	bool zeelbsrhsskkrkyeulkoqsugi();

protected:
	string qumngr;
	int evutkigxm;
	string plfthvnxettptu;
	int qfbxvtdftnqgkfd;
	string gejmpn;

	int tyobdbjcahtdalp(bool xtfelul, double agowwyinxqhszet, bool wysnfta, double tspridve, string nngzgl, double tbjyslsw, string uurrptyati);
	int hnbylspyashsuww(double ejhzcnut);
	string okgzprleehuqfzjyxmtrig(double lacqswiwurad, string pnxvmo, bool zxxasrebvgg, int lpiqowb, string csfgd, int sxxulj, double zesherxosll);
	int vuugpevajyphsktnjqobshz(bool jdnlebpk, int zrcsd);

private:
	double azxddljlhwcqmzj;
	bool ireqmydszw;

	int oacqixbsiorlc(double mfjzycwnielfyi, bool dgtgrskukcccpqp, int mvysdck, double jnlfwxvbgksn, bool hnzewh, int ioplvdmnubrz, int rvwatpfm, double lyquagjri);
	int vfcxksttvaeuwndpzzug(double xnzkozyhqxwtnxa, int ghytsrgwxofqpn, bool qnavyhxcntg, double qtqnlis, double tendfhqmmy, int gkmqtplqbnm, bool xujdlugietin, double euzgjs, bool qqmeysnow);
	void vgitoffrzaldtzneoi(double ubrgx, int ksjlc, string skfcqa, int xjmlf, double ecxux, int gfccydplmjtixw, int xvrfsvz, double pknegas, bool fseushigqfxavma, string rbdsoxrvfnfbxl);
	double ewkshxaxkdo(bool ttmhl, int dloppuvh, int zffztqxhk, bool grtfflkd, double eijef, int ygohox, string ueyczkwhqgzh, int wrcsumsp);
	string wyavqrxhonu(double rtgepm, int lnqpwvhncmk);

};


int aukimvz::oacqixbsiorlc(double mfjzycwnielfyi, bool dgtgrskukcccpqp, int mvysdck, double jnlfwxvbgksn, bool hnzewh, int ioplvdmnubrz, int rvwatpfm, double lyquagjri) {
	double zpqajlaxuaz = 6531;
	double pkurnth = 38079;
	int cmbycugzjttnf = 2113;
	double eyolcstffdpwum = 31049;
	double zkuvbz = 77442;
	int tdxrzy = 6384;
	bool tvyzqcunf = false;
	bool hbhapktmkbpqqj = false;
	int jwstvhyrxwnagvt = 6016;
	if (6016 != 6016) {
		int hu;
		for (hu = 44; hu > 0; hu--) {
			continue;
		}
	}
	if (38079 == 38079) {
		int oj;
		for (oj = 51; oj > 0; oj--) {
			continue;
		}
	}
	if (77442 == 77442) {
		int rb;
		for (rb = 50; rb > 0; rb--) {
			continue;
		}
	}
	return 76990;
}

int aukimvz::vfcxksttvaeuwndpzzug(double xnzkozyhqxwtnxa, int ghytsrgwxofqpn, bool qnavyhxcntg, double qtqnlis, double tendfhqmmy, int gkmqtplqbnm, bool xujdlugietin, double euzgjs, bool qqmeysnow) {
	bool zrnqmojejjyhnq = false;
	int oqeuiusosi = 985;
	bool xwookrxvwbdyhkp = false;
	double bofzjftdbqpvcun = 15631;
	if (15631 == 15631) {
		int by;
		for (by = 47; by > 0; by--) {
			continue;
		}
	}
	if (15631 != 15631) {
		int ihcn;
		for (ihcn = 96; ihcn > 0; ihcn--) {
			continue;
		}
	}
	if (15631 == 15631) {
		int dqsytugu;
		for (dqsytugu = 76; dqsytugu > 0; dqsytugu--) {
			continue;
		}
	}
	if (985 == 985) {
		int vf;
		for (vf = 93; vf > 0; vf--) {
			continue;
		}
	}
	return 31666;
}

void aukimvz::vgitoffrzaldtzneoi(double ubrgx, int ksjlc, string skfcqa, int xjmlf, double ecxux, int gfccydplmjtixw, int xvrfsvz, double pknegas, bool fseushigqfxavma, string rbdsoxrvfnfbxl) {
	int lajrjw = 6085;
	string elbgqha = "fedwxrijlkncaqrugypkresumcpgqcaywwbceempwsgsqzldgpzezvrliba";
	if (string("fedwxrijlkncaqrugypkresumcpgqcaywwbceempwsgsqzldgpzezvrliba") == string("fedwxrijlkncaqrugypkresumcpgqcaywwbceempwsgsqzldgpzezvrliba")) {
		int ilpsx;
		for (ilpsx = 82; ilpsx > 0; ilpsx--) {
			continue;
		}
	}
	if (string("fedwxrijlkncaqrugypkresumcpgqcaywwbceempwsgsqzldgpzezvrliba") != string("fedwxrijlkncaqrugypkresumcpgqcaywwbceempwsgsqzldgpzezvrliba")) {
		int iws;
		for (iws = 91; iws > 0; iws--) {
			continue;
		}
	}

}

double aukimvz::ewkshxaxkdo(bool ttmhl, int dloppuvh, int zffztqxhk, bool grtfflkd, double eijef, int ygohox, string ueyczkwhqgzh, int wrcsumsp) {
	string zqnlfxqh = "ksnfpvnntvqjavcyoaltuvugaahirbzntyhkuucaucxxlgkougdvvkoiosdhlbljfyectrnisamrjoauxvozcpuvbgyuwwsvgfxx";
	int lroscqbjpw = 319;
	bool uvqibgvznhal = false;
	int yfgiqvnxuj = 3629;
	if (319 == 319) {
		int xodk;
		for (xodk = 6; xodk > 0; xodk--) {
			continue;
		}
	}
	if (3629 == 3629) {
		int uadamhgc;
		for (uadamhgc = 98; uadamhgc > 0; uadamhgc--) {
			continue;
		}
	}
	if (false == false) {
		int taqqtvzoh;
		for (taqqtvzoh = 91; taqqtvzoh > 0; taqqtvzoh--) {
			continue;
		}
	}
	return 23202;
}

string aukimvz::wyavqrxhonu(double rtgepm, int lnqpwvhncmk) {
	double hqtgiskwphmdbde = 9377;
	double tncdpqlnbxorr = 18384;
	int yfnoxglid = 198;
	string ljtvcdjuexafk = "ioszcqukegxgdcjtewizjekzfzadljtcfkncvts";
	string wlpqdyzpezwbtb = "uierkmzeadedsloqnjliovabautbdjxffzfvuallzuwjciscnrol";
	int khczhwtzwdglpyk = 1011;
	if (9377 != 9377) {
		int wnvuhafqa;
		for (wnvuhafqa = 25; wnvuhafqa > 0; wnvuhafqa--) {
			continue;
		}
	}
	return string("wdipnafp");
}

int aukimvz::tyobdbjcahtdalp(bool xtfelul, double agowwyinxqhszet, bool wysnfta, double tspridve, string nngzgl, double tbjyslsw, string uurrptyati) {
	double gttoctrirm = 12177;
	double aowcdilkckgyv = 68784;
	bool ohpmdvdwmijwoj = true;
	return 37900;
}

int aukimvz::hnbylspyashsuww(double ejhzcnut) {
	double okgjwoo = 27648;
	string nugkp = "wjkfkjsfibwlpswhgojfvihtmimdqlziadlekwpevaetatnfwhhdij";
	double pwhiephvynhkqmr = 6514;
	bool zablffhgzarlal = false;
	if (false != false) {
		int iufocn;
		for (iufocn = 39; iufocn > 0; iufocn--) {
			continue;
		}
	}
	if (27648 != 27648) {
		int owwpq;
		for (owwpq = 15; owwpq > 0; owwpq--) {
			continue;
		}
	}
	return 68803;
}

string aukimvz::okgzprleehuqfzjyxmtrig(double lacqswiwurad, string pnxvmo, bool zxxasrebvgg, int lpiqowb, string csfgd, int sxxulj, double zesherxosll) {
	string qvhvdnxniepwux = "haekqpihjyaquinkamnxnhrjiuswjaywamqtumwnwiybrldvysxrnfgqdlzhlfxuofvwdvvnggevghsvichbsdh";
	double yjaoyhkbrjtdija = 10727;
	string eongveyuprr = "cffguarwrzhqnxrcjdebiodrcdoxyewbligxlbaaiziolsaglaernuvznlgibqwoenzttfqsrdpeoefpucwoofeknrbrvsa";
	double xyeoqhazzewrv = 26783;
	if (26783 != 26783) {
		int jhkvg;
		for (jhkvg = 20; jhkvg > 0; jhkvg--) {
			continue;
		}
	}
	return string("avadqzuriihrhuosscbd");
}

int aukimvz::vuugpevajyphsktnjqobshz(bool jdnlebpk, int zrcsd) {
	bool dhofiimkxflljys = false;
	int lpkdesuxpnqc = 4948;
	int kfgxsv = 7124;
	double jxswll = 22200;
	string qrptuixmrpdje = "hknzluzoetufaktiy";
	string lhrngm = "bptgwohkcxlkmkqwqhuoip";
	int gudwvxptcqfv = 2319;
	int rrlnxut = 6565;
	int rybowhb = 1988;
	if (string("bptgwohkcxlkmkqwqhuoip") == string("bptgwohkcxlkmkqwqhuoip")) {
		int jcykvlkmuk;
		for (jcykvlkmuk = 27; jcykvlkmuk > 0; jcykvlkmuk--) {
			continue;
		}
	}
	if (22200 == 22200) {
		int nrypkbg;
		for (nrypkbg = 47; nrypkbg > 0; nrypkbg--) {
			continue;
		}
	}
	return 17228;
}

bool aukimvz::zeelbsrhsskkrkyeulkoqsugi() {
	double bmhqgnfa = 10069;
	string invsmikcrvlarsm = "nqwchskokmopuezkilhmqfpsh";
	string dvrpddfmtbcowbf = "bxqhxpywx";
	return false;
}

aukimvz::aukimvz() {
	this->zeelbsrhsskkrkyeulkoqsugi();
	this->tyobdbjcahtdalp(false, 2825, true, 46559, string("reqbwtdjhglvvbqgsglerptrsuzonuvoeugpjuxdyopfzpxuqwdinpylirfrxkvqbn"), 41368, string("tiglhsykrfruknkwycoyrvnwxxawdbtpebvtxdcscqsjgmcedxijppecerdhveirzekyhukhfjobwgfdwrk"));
	this->hnbylspyashsuww(23895);
	this->okgzprleehuqfzjyxmtrig(22843, string("dcllqhgzcclpa"), false, 6995, string("nbipbhvrppujuksqgyawmgdkhtdamdilyinssebxpzejcvokvpfofemcumrhddsgomrhuogjjcibbdssmat"), 1965, 2115);
	this->vuugpevajyphsktnjqobshz(true, 4501);
	this->oacqixbsiorlc(14747, false, 1762, 15188, false, 2228, 878, 5589);
	this->vfcxksttvaeuwndpzzug(46148, 1259, true, 25129, 49365, 7677, true, 5771, true);
	this->vgitoffrzaldtzneoi(39307, 46, string("ssvsxdwlroxyaltumkguhrguhmsgxfnnnsdqj"), 3835, 23751, 3324, 6108, 11572, true, string("qocdekpqlkkinmebmhjtceplmctzkhuisankbcodyhjjmgkgtkclvtlvxfwpwsrdezrvyhbrlejpddndxyliajfsaobx"));
	this->ewkshxaxkdo(true, 4735, 4108, false, 17099, 3921, string("pktkhzxkxypbmysl"), 7581);
	this->wyavqrxhonu(14973, 2890);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ubaptvn {
public:
	double eqtpf;
	string mqriqwsqfqrnfmw;
	string larxwnerojgfcc;
	ubaptvn();
	void ocehycizonaglxpadbn(int gfmejugowzxix, string mbofgf, int xphsgnsppxmp, double ofgakz, bool yysoyivqr, bool ylojyqjragmfji, bool vfxztzn, string rhbivuqjt, int lxnam);
	int musctqprdrchdmonjatowf(double nvniitrl, int lvfhis, string utmdppqi, double wkezzikffsj, bool kyyoiwc, string mfqscyav, double ekevkwgrvpnmlq, string jlswawf);
	bool njwsmxzeuicd(bool gwejkag);
	string heqqugvyiwmegch(int xlhasfmuf, bool wblsunvb, string rvjeyxikdbggoy, double aueht, bool hwcswmnt);

protected:
	bool caisbajx;
	string eoozdjxyhdlv;
	double ykfowypr;
	double beegfscxrpprbql;
	int nsvpwfi;

	bool iddzhtobqdnaamey(double vsgsi, string iivmntaokigzeeq, bool zxrazimgpq, double ffcpmhntgrnux, double wztafgirzd);
	bool rcvbxblzbhorvvufxniuu();
	void lmwehzyzcwxfujh(double uzdcmukpfwqg, double bfpbo);
	int zlufpjwuabosahfexzo(int nhfubch, double plxgfdjyyba, double vckxssgporgbujz, string bhevxhdsz, double pgcfumorgag, double wbgiqi, bool llhsycocz, int xjpbtfvlw);
	int xlspasoncdfnnrg(int qcclwnechm, string qypvcw, double iyuhd, string kjxuhxtrnl, bool ywswpoeukzhclp, int tdixsjifgpzhrq, double torbpvp, int ualla);
	bool fanmiqhlxk(string cmzbzzzizykwj, bool ytcntbswai, string jcokslcdjge, int ntkosseapeiq, int bnllc, string xhvvm, bool wdplhlnbd, string hjjuxbxstijiche, int irdbfoxwx);
	string smpsaeemxbnbskdxncfbi(string onsmojjkh, bool zbxope, double hijghob, bool oyckkrivby, string veuqdy, double urjybxsvutxim);
	void towauxcauwoxhjexomsgy(double krovj, bool gfrqmte, string crahlcihcb, int ypkkebppx);

private:
	int jjqjivnxxu;

	bool yhettkoqbtisoqtahn(string ohyjsbm, string losonllydrsvbz, string kgrvhbdbgkpbzr, string ohtix, bool prlkxoint);

};


bool ubaptvn::yhettkoqbtisoqtahn(string ohyjsbm, string losonllydrsvbz, string kgrvhbdbgkpbzr, string ohtix, bool prlkxoint) {
	bool ygeqf = false;
	if (false != false) {
		int xjynuohwpa;
		for (xjynuohwpa = 43; xjynuohwpa > 0; xjynuohwpa--) {
			continue;
		}
	}
	if (false == false) {
		int ggavdmpqw;
		for (ggavdmpqw = 23; ggavdmpqw > 0; ggavdmpqw--) {
			continue;
		}
	}
	if (false != false) {
		int wqv;
		for (wqv = 43; wqv > 0; wqv--) {
			continue;
		}
	}
	return true;
}

bool ubaptvn::iddzhtobqdnaamey(double vsgsi, string iivmntaokigzeeq, bool zxrazimgpq, double ffcpmhntgrnux, double wztafgirzd) {
	bool wataxawan = true;
	double wvqarmfv = 371;
	bool edhtbbmadsr = true;
	bool beujh = true;
	int fmeueymuvzjsdbu = 39;
	bool japvuapyy = false;
	if (39 == 39) {
		int xq;
		for (xq = 30; xq > 0; xq--) {
			continue;
		}
	}
	if (true == true) {
		int khept;
		for (khept = 92; khept > 0; khept--) {
			continue;
		}
	}
	if (true != true) {
		int fkrftils;
		for (fkrftils = 5; fkrftils > 0; fkrftils--) {
			continue;
		}
	}
	if (true != true) {
		int ca;
		for (ca = 92; ca > 0; ca--) {
			continue;
		}
	}
	return true;
}

bool ubaptvn::rcvbxblzbhorvvufxniuu() {
	double kmzwjtwsbuxhgpl = 8829;
	string zljgxejzyvrgq = "ydrmyuaqodiqrxntidlbftbaxgekgzddnfiqxeaylvfynxeoznygickvuzevgzsoqnyigczfaelajizwhagftthgrgo";
	int nyeizzbjgcrrt = 445;
	string aifgbf = "yesodqtedtveyybjxawqgjunhazubv";
	bool fdldgmqzrpf = true;
	double bowlxoheod = 5251;
	double ajjtv = 32682;
	string vcjfzmhjwopxnaf = "xwmjsanxmsgvmuhcmtdsuvexikohfctpw";
	double cmyccncr = 42006;
	string defrdkhqg = "fopsnirdlpkojlafucoudhuwfsidtrpkytdusyzwifpdwxcpzbun";
	if (string("ydrmyuaqodiqrxntidlbftbaxgekgzddnfiqxeaylvfynxeoznygickvuzevgzsoqnyigczfaelajizwhagftthgrgo") == string("ydrmyuaqodiqrxntidlbftbaxgekgzddnfiqxeaylvfynxeoznygickvuzevgzsoqnyigczfaelajizwhagftthgrgo")) {
		int xuiviog;
		for (xuiviog = 83; xuiviog > 0; xuiviog--) {
			continue;
		}
	}
	return true;
}

void ubaptvn::lmwehzyzcwxfujh(double uzdcmukpfwqg, double bfpbo) {
	bool eguzomczmmep = false;
	int zxiqbvm = 3942;
	bool kczvcwuev = false;
	if (false != false) {
		int ytnz;
		for (ytnz = 40; ytnz > 0; ytnz--) {
			continue;
		}
	}
	if (false != false) {
		int lveusfgg;
		for (lveusfgg = 13; lveusfgg > 0; lveusfgg--) {
			continue;
		}
	}
	if (false == false) {
		int nasykb;
		for (nasykb = 76; nasykb > 0; nasykb--) {
			continue;
		}
	}

}

int ubaptvn::zlufpjwuabosahfexzo(int nhfubch, double plxgfdjyyba, double vckxssgporgbujz, string bhevxhdsz, double pgcfumorgag, double wbgiqi, bool llhsycocz, int xjpbtfvlw) {
	return 46706;
}

int ubaptvn::xlspasoncdfnnrg(int qcclwnechm, string qypvcw, double iyuhd, string kjxuhxtrnl, bool ywswpoeukzhclp, int tdixsjifgpzhrq, double torbpvp, int ualla) {
	double dnhvlezr = 83858;
	bool kqyovuxckpudygr = false;
	int vzrfrunyh = 2895;
	int bviwyo = 3697;
	bool pnsjrwssxvyyuav = false;
	double olzrngqag = 46302;
	int hcfweviidivwt = 2137;
	bool watnuexwwtlqos = true;
	if (2137 == 2137) {
		int ljqrgtfmtj;
		for (ljqrgtfmtj = 8; ljqrgtfmtj > 0; ljqrgtfmtj--) {
			continue;
		}
	}
	if (true == true) {
		int xvodpaxy;
		for (xvodpaxy = 18; xvodpaxy > 0; xvodpaxy--) {
			continue;
		}
	}
	if (2137 != 2137) {
		int plqtjwj;
		for (plqtjwj = 0; plqtjwj > 0; plqtjwj--) {
			continue;
		}
	}
	return 71298;
}

bool ubaptvn::fanmiqhlxk(string cmzbzzzizykwj, bool ytcntbswai, string jcokslcdjge, int ntkosseapeiq, int bnllc, string xhvvm, bool wdplhlnbd, string hjjuxbxstijiche, int irdbfoxwx) {
	return true;
}

string ubaptvn::smpsaeemxbnbskdxncfbi(string onsmojjkh, bool zbxope, double hijghob, bool oyckkrivby, string veuqdy, double urjybxsvutxim) {
	double mhglxhejkk = 40174;
	int jqclaij = 7069;
	int tevoppbc = 1686;
	double mphsrcfbsnbim = 39540;
	int actgdrtbpdx = 8396;
	double mfzuo = 7868;
	if (40174 != 40174) {
		int wloits;
		for (wloits = 13; wloits > 0; wloits--) {
			continue;
		}
	}
	if (7868 == 7868) {
		int uhzz;
		for (uhzz = 35; uhzz > 0; uhzz--) {
			continue;
		}
	}
	return string("rzieskcj");
}

void ubaptvn::towauxcauwoxhjexomsgy(double krovj, bool gfrqmte, string crahlcihcb, int ypkkebppx) {

}

void ubaptvn::ocehycizonaglxpadbn(int gfmejugowzxix, string mbofgf, int xphsgnsppxmp, double ofgakz, bool yysoyivqr, bool ylojyqjragmfji, bool vfxztzn, string rhbivuqjt, int lxnam) {
	int throgvtj = 1653;
	double opztnqtdmf = 23528;
	string pixsidch = "bgaqxgfqgf";
	bool rrlpuanprm = false;
	int yqdgfgavhxse = 932;
	if (false == false) {
		int fblcoxf;
		for (fblcoxf = 4; fblcoxf > 0; fblcoxf--) {
			continue;
		}
	}
	if (1653 == 1653) {
		int ufoet;
		for (ufoet = 81; ufoet > 0; ufoet--) {
			continue;
		}
	}
	if (1653 != 1653) {
		int gyfwihf;
		for (gyfwihf = 77; gyfwihf > 0; gyfwihf--) {
			continue;
		}
	}
	if (932 != 932) {
		int sp;
		for (sp = 8; sp > 0; sp--) {
			continue;
		}
	}
	if (23528 == 23528) {
		int dwoth;
		for (dwoth = 11; dwoth > 0; dwoth--) {
			continue;
		}
	}

}

int ubaptvn::musctqprdrchdmonjatowf(double nvniitrl, int lvfhis, string utmdppqi, double wkezzikffsj, bool kyyoiwc, string mfqscyav, double ekevkwgrvpnmlq, string jlswawf) {
	int cxqzgqbl = 677;
	int vaxrqxzu = 3224;
	if (3224 == 3224) {
		int ijpvk;
		for (ijpvk = 5; ijpvk > 0; ijpvk--) {
			continue;
		}
	}
	if (677 != 677) {
		int uucja;
		for (uucja = 66; uucja > 0; uucja--) {
			continue;
		}
	}
	return 8615;
}

bool ubaptvn::njwsmxzeuicd(bool gwejkag) {
	string aufvnbmtsymp = "okjuixtoylsgjsfdxtunmestbfobbzaxcvlhermiuu";
	bool wnxibb = false;
	double nqlnwwvx = 30584;
	double oydwkonrcsbwpv = 19915;
	int jnucmrqbcja = 3009;
	string duoltndwwzlxui = "cairkoybblygwquqtoogxidrntplfzvrubhhxrhwvtwyrgxcdaj";
	string zektipxo = "rqbbrdvgswmvqfzlschegwaxjcmupdtrnpkzbfsuzsdfeglthpwpmiw";
	if (19915 != 19915) {
		int srpnlhzs;
		for (srpnlhzs = 49; srpnlhzs > 0; srpnlhzs--) {
			continue;
		}
	}
	if (string("rqbbrdvgswmvqfzlschegwaxjcmupdtrnpkzbfsuzsdfeglthpwpmiw") == string("rqbbrdvgswmvqfzlschegwaxjcmupdtrnpkzbfsuzsdfeglthpwpmiw")) {
		int zx;
		for (zx = 14; zx > 0; zx--) {
			continue;
		}
	}
	return false;
}

string ubaptvn::heqqugvyiwmegch(int xlhasfmuf, bool wblsunvb, string rvjeyxikdbggoy, double aueht, bool hwcswmnt) {
	string lyufp = "vrnypvlaqwyppmgvrojicuqcaccwqtti";
	double iubddzeln = 11573;
	double pgriqpdjad = 88457;
	int lpdslsaszk = 1828;
	bool xwdgw = true;
	double haucdngnwvijv = 61786;
	if (61786 == 61786) {
		int uapjmjyfc;
		for (uapjmjyfc = 57; uapjmjyfc > 0; uapjmjyfc--) {
			continue;
		}
	}
	if (string("vrnypvlaqwyppmgvrojicuqcaccwqtti") == string("vrnypvlaqwyppmgvrojicuqcaccwqtti")) {
		int deg;
		for (deg = 79; deg > 0; deg--) {
			continue;
		}
	}
	if (11573 == 11573) {
		int ypuxss;
		for (ypuxss = 51; ypuxss > 0; ypuxss--) {
			continue;
		}
	}
	return string("svecggdddg");
}

ubaptvn::ubaptvn() {
	this->ocehycizonaglxpadbn(10, string("ilmmhtnggfjwkcsccqisthgoyiecfjpppijfevjdpytdgtdwin"), 6996, 678, false, true, true, string("uytfaezxzzoxqbjicwcvbhzhfpcpinxujatbrkqkpslbjtt"), 3571);
	this->musctqprdrchdmonjatowf(33380, 1346, string("azyaubswuoe"), 19341, true, string("knytkvfepbbzswasurkkgdwo"), 55756, string("wzxeqiwghtvuxlcjvewsmorlbpkzsfggjyhwuvfbjothdvbqiisrugorjkhgbkojmlnqzhtilfvvyzocxypeuczgpzb"));
	this->njwsmxzeuicd(false);
	this->heqqugvyiwmegch(1367, false, string("fyurnbrefsjuuvgcddtzfsdryxvvcxhlcrbcxvnzboemzbitchqymhynkiiydseglsufgzluyutjcbgjkdyjeibgqygtaouwnrb"), 36343, false);
	this->iddzhtobqdnaamey(11919, string("promkxxnfiujlqimxximvxodpcjdbolpgpwlkunhsclittvwwdppcmbwu"), false, 32484, 3794);
	this->rcvbxblzbhorvvufxniuu();
	this->lmwehzyzcwxfujh(61544, 51417);
	this->zlufpjwuabosahfexzo(7388, 1207, 78253, string("ukezcvu"), 9464, 20082, false, 7905);
	this->xlspasoncdfnnrg(1701, string("lwshwakxbhaukhfyvegywi"), 14526, string("ccunltytucjslxrezgorlcfqahwrqnikuwlofbrjeaueamglyhqulcpnxcdviswmnudgyhqevrglxkxmzknuqgwnxsafwbzbnf"), false, 8945, 40772, 3571);
	this->fanmiqhlxk(string("pvqydsqsmhk"), false, string("nxvdueczdlwvwttfjhatgiykpvexqqbzb"), 3738, 644, string("njzwpqmmzzlowfvhtouammqmklfoydpxybpaflwlxnhgfvwmickyorarvyavul"), true, string("yhjjhmtzdbsiorkqfastdlsgncdjwodokoekqdzpktcehsbohifnhgovuojubkip"), 1300);
	this->smpsaeemxbnbskdxncfbi(string("bszqqrfbmfqxqeuhxbuobyxoltwojimsyftqg"), true, 3529, false, string("fjapfvkchbrtdurvzufhiyhyqgju"), 67571);
	this->towauxcauwoxhjexomsgy(35631, true, string("bf"), 868);
	this->yhettkoqbtisoqtahn(string("fixvwpzcqqjmwvxykwzyycmiddsailosav"), string("sirjitchjxnqkmefygzyzptakrjoaan"), string("qrvionaddadcwhjvqqbogapq"), string("oibuawiisesjmqqyacvtvcpkqbmfibdsmctqdahennlfqcodgbpwmunesnabgamfsub"), false);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class arwkvkp {
public:
	double axljinsbdanz;
	int dtfhguwpzpn;
	int rvjlfheu;
	bool csfuz;
	arwkvkp();
	double iadtmdqqfdepaxkdpu(string qabjwqjpbswb, string upzbkefs, int yfyuzff);
	bool gwoyqevbwcafygpgn(double puohwdhzmyuttm, int fkqfqzuy, string ebumls, double mffxcaoyamqdy);
	void abxbipyabudylzknan(int ekejuryg, bool nafhb, bool cvmjslcas, bool nmvkgqzcnhhwbd, bool zubywxudyacw, int rxytuuatj, string wqmged, bool vgftjrhvvujtnxe, double zgtzafzhcmg, string oiaubbp);
	string srxltvssgoowf(double cbrhsszjt, double sddyjjzuzx, string eqrwnbnsl, double vcqweuxkvlgrgcp, string hnfyg, string ibfhqsxq, bool gjfex, bool pefpquwnhxzfn, int zfwjgxljanhzy);
	double ztvmdvzvqoyorbtcomeuolzmu(bool ohhgxzgrel, double kijlabsrhaahgr, double cysroimgzpcp, int urfde, int wpkxwevcksm, bool olcqzstsb, string npzisqpi, int labkmjddbxbbd);
	void setsrppqza(string xuirzvidjjcqvy, double cksnccsx, bool kyphubah);
	double prgmfrcqzbzysojkbc(string raxogoy);

protected:
	int gpryhrjgaknfdhc;
	bool ibsoeismtgalvft;
	double dbrjittmowuz;
	string xenvhuttuaoqay;
	string ypcfxn;

	bool bjbaeziabkzfrgvpcxfifjuw(int fxleqogzmtx, bool nozjehtxkjctvw, bool vrypf, int ipqlqgknstmydmz, int hndty, int ukmrpj, bool kwbmbhxjmb, int bkopekictnsffwi, double slgnlorn, string znqxqjqfyoazk);
	bool yxzqgpxuazhbktoaadfqhcbyq(bool imzsfcchpze);
	bool lrpymxtiwcgc(string azniuyv, int lehsiqw, string npyiqsid, int zawsutrlonquo, int pyldwyeofcr, double zenblugvowymo, bool muwkmzusht, int kiuhjbk);
	bool sizpenrdzrm(bool wzjkke, int yqpqrjzxhk, bool tihzrwsvvhuk, int uixsbmncp, bool swggvrfvh);
	double wcriwssrygewhrpl(string jzsulwmcrgphgav, double yjkfqfqenmdpy, bool rcgwdkcacljqhp, double cgrmzvimqyzvqbx, int jqijql, string sfqfyoypsu, int nvefthlvhs, bool sepbbzpwsdjydyt, double pdrkupatunfzwo, bool sbkne);

private:
	string ddtqobjzc;
	string vacdtexymjshal;
	int roisiifclyeswz;

	double huglnyoknizirvhnmkqxxlrwe(string xvuiijk, string nmvesnhrkzbjcyg);
	string luzdxqtmhgckhkurkdeusu();
	bool lzhkkrtsgweruivvurxt(double eauvwlvuv, double jfwycspyutbdz, double alczc, int tifve, int ebrwogi, int qonhvdhm);
	void zykksgximxzdk(string czwgyk, string dqwvqwilppenp);
	string ginovxktwggwknxec(double ueregqqblk, bool qiqahrhjratelh, int orainaeotruj, bool aizvp, string hwkwt, int adytya);
	int yupyvnrjrtkvdfrmrvvo(string mvowtkgithkvaov);

};


double arwkvkp::huglnyoknizirvhnmkqxxlrwe(string xvuiijk, string nmvesnhrkzbjcyg) {
	int lcqbzemj = 901;
	int qqhktlzglvym = 2207;
	if (901 == 901) {
		int oabde;
		for (oabde = 74; oabde > 0; oabde--) {
			continue;
		}
	}
	return 75650;
}

string arwkvkp::luzdxqtmhgckhkurkdeusu() {
	double bxsbdyqkknzlrm = 36395;
	string ckctzimlhqqo = "kxwivdbtqmpmriilnril";
	string zikimdxrchigih = "rolrryavonunwfzalyot";
	if (36395 != 36395) {
		int xvpfxrmo;
		for (xvpfxrmo = 98; xvpfxrmo > 0; xvpfxrmo--) {
			continue;
		}
	}
	if (36395 != 36395) {
		int rzydzajevl;
		for (rzydzajevl = 11; rzydzajevl > 0; rzydzajevl--) {
			continue;
		}
	}
	if (string("kxwivdbtqmpmriilnril") == string("kxwivdbtqmpmriilnril")) {
		int rm;
		for (rm = 94; rm > 0; rm--) {
			continue;
		}
	}
	return string("ubtjofetsfkxgerbmpop");
}

bool arwkvkp::lzhkkrtsgweruivvurxt(double eauvwlvuv, double jfwycspyutbdz, double alczc, int tifve, int ebrwogi, int qonhvdhm) {
	string ganzngrq = "yesvimkhgjqyzbdcrdusrprxifggnnsknzamfmm";
	string fidxk = "ygrqibbfigvfygkppruwwfxgbpahulcvxkpyvojqzjmmxqfnilggmivaihraaqhopvebbjmnhmtecvtywtesurkd";
	bool jodrugmfqkeills = true;
	bool twrvrqorykdk = true;
	string jgwss = "kccvpvfcj";
	if (string("kccvpvfcj") != string("kccvpvfcj")) {
		int qlltkzycsz;
		for (qlltkzycsz = 88; qlltkzycsz > 0; qlltkzycsz--) {
			continue;
		}
	}
	if (string("ygrqibbfigvfygkppruwwfxgbpahulcvxkpyvojqzjmmxqfnilggmivaihraaqhopvebbjmnhmtecvtywtesurkd") == string("ygrqibbfigvfygkppruwwfxgbpahulcvxkpyvojqzjmmxqfnilggmivaihraaqhopvebbjmnhmtecvtywtesurkd")) {
		int qldsseljci;
		for (qldsseljci = 32; qldsseljci > 0; qldsseljci--) {
			continue;
		}
	}
	if (string("yesvimkhgjqyzbdcrdusrprxifggnnsknzamfmm") == string("yesvimkhgjqyzbdcrdusrprxifggnnsknzamfmm")) {
		int dmeywcwzpv;
		for (dmeywcwzpv = 40; dmeywcwzpv > 0; dmeywcwzpv--) {
			continue;
		}
	}
	if (string("ygrqibbfigvfygkppruwwfxgbpahulcvxkpyvojqzjmmxqfnilggmivaihraaqhopvebbjmnhmtecvtywtesurkd") == string("ygrqibbfigvfygkppruwwfxgbpahulcvxkpyvojqzjmmxqfnilggmivaihraaqhopvebbjmnhmtecvtywtesurkd")) {
		int vd;
		for (vd = 83; vd > 0; vd--) {
			continue;
		}
	}
	if (string("yesvimkhgjqyzbdcrdusrprxifggnnsknzamfmm") != string("yesvimkhgjqyzbdcrdusrprxifggnnsknzamfmm")) {
		int pzjbtfoj;
		for (pzjbtfoj = 33; pzjbtfoj > 0; pzjbtfoj--) {
			continue;
		}
	}
	return true;
}

void arwkvkp::zykksgximxzdk(string czwgyk, string dqwvqwilppenp) {
	string evvrktbzh = "eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq";
	if (string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq") != string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq")) {
		int wrznubqi;
		for (wrznubqi = 83; wrznubqi > 0; wrznubqi--) {
			continue;
		}
	}
	if (string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq") == string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq")) {
		int rud;
		for (rud = 45; rud > 0; rud--) {
			continue;
		}
	}
	if (string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq") != string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq")) {
		int absss;
		for (absss = 34; absss > 0; absss--) {
			continue;
		}
	}
	if (string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq") != string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq")) {
		int lqyxgfyoyj;
		for (lqyxgfyoyj = 97; lqyxgfyoyj > 0; lqyxgfyoyj--) {
			continue;
		}
	}
	if (string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq") != string("eyqatgovagoqedcmghplmmqohmiqlanvqjxwuzoeddcxjubxjrxluuq")) {
		int iucqoeq;
		for (iucqoeq = 70; iucqoeq > 0; iucqoeq--) {
			continue;
		}
	}

}

string arwkvkp::ginovxktwggwknxec(double ueregqqblk, bool qiqahrhjratelh, int orainaeotruj, bool aizvp, string hwkwt, int adytya) {
	bool qsmoewzkyhofqc = false;
	bool upeqbvouobgg = false;
	int nrfyuxzfgjaf = 3246;
	string crqsnrjaxe = "ppdzodareidistmnqtcibwmqompxkfihmliawjavywjfxhxxxnfvtgnpwsukyerkzlvuqwmamepoc";
	double fcopypbdok = 42095;
	bool ilbufr = true;
	int cijhfmb = 2531;
	if (true != true) {
		int sjtvo;
		for (sjtvo = 99; sjtvo > 0; sjtvo--) {
			continue;
		}
	}
	return string("xdjbhzzfjnoohlghy");
}

int arwkvkp::yupyvnrjrtkvdfrmrvvo(string mvowtkgithkvaov) {
	string rowsds = "skagefclllrblrjdybj";
	bool julwhirgchpuyh = false;
	int zctyysagkcml = 585;
	int jlcdoqwv = 1849;
	int iydjzni = 946;
	bool anavnjwpc = true;
	string ebzwgrsk = "gyhqrrriibskbornvkbytldejqzudjpufszzrercmjampcdce";
	bool rsulpevctrxvvbr = false;
	int ukwqgejsjxmvtwe = 1804;
	if (585 == 585) {
		int fmsg;
		for (fmsg = 23; fmsg > 0; fmsg--) {
			continue;
		}
	}
	if (946 == 946) {
		int sjpwv;
		for (sjpwv = 66; sjpwv > 0; sjpwv--) {
			continue;
		}
	}
	if (string("skagefclllrblrjdybj") == string("skagefclllrblrjdybj")) {
		int ghfjuxy;
		for (ghfjuxy = 90; ghfjuxy > 0; ghfjuxy--) {
			continue;
		}
	}
	return 7956;
}

bool arwkvkp::bjbaeziabkzfrgvpcxfifjuw(int fxleqogzmtx, bool nozjehtxkjctvw, bool vrypf, int ipqlqgknstmydmz, int hndty, int ukmrpj, bool kwbmbhxjmb, int bkopekictnsffwi, double slgnlorn, string znqxqjqfyoazk) {
	double qbzkkbndvwm = 11010;
	string dqsesy = "mquhgafrkzrkgqesyorgkvhvigemnxtsnusraswupjuhrgyovwzkxfsealmkkwlvnjj";
	double wunmqfv = 18315;
	string atnqpkwob = "olmvohlwymqdkuurajngreeczbaqwgfgschsmjzztnnexoayvgmhcfsiyzndscunqkwjyhogjgjjxi";
	bool omowuasxilubfp = false;
	double hhyvqki = 20934;
	double bhywypoks = 10534;
	bool fcpezz = false;
	bool dbusxbvnftn = false;
	string mrzhbbuvckjvm = "dluymfeyyecgidnrsy";
	if (string("olmvohlwymqdkuurajngreeczbaqwgfgschsmjzztnnexoayvgmhcfsiyzndscunqkwjyhogjgjjxi") == string("olmvohlwymqdkuurajngreeczbaqwgfgschsmjzztnnexoayvgmhcfsiyzndscunqkwjyhogjgjjxi")) {
		int uk;
		for (uk = 38; uk > 0; uk--) {
			continue;
		}
	}
	if (10534 == 10534) {
		int ulichsrrc;
		for (ulichsrrc = 86; ulichsrrc > 0; ulichsrrc--) {
			continue;
		}
	}
	if (string("dluymfeyyecgidnrsy") != string("dluymfeyyecgidnrsy")) {
		int uvsvlcl;
		for (uvsvlcl = 42; uvsvlcl > 0; uvsvlcl--) {
			continue;
		}
	}
	if (string("mquhgafrkzrkgqesyorgkvhvigemnxtsnusraswupjuhrgyovwzkxfsealmkkwlvnjj") == string("mquhgafrkzrkgqesyorgkvhvigemnxtsnusraswupjuhrgyovwzkxfsealmkkwlvnjj")) {
		int nz;
		for (nz = 2; nz > 0; nz--) {
			continue;
		}
	}
	return true;
}

bool arwkvkp::yxzqgpxuazhbktoaadfqhcbyq(bool imzsfcchpze) {
	bool zohhnopowdy = true;
	string swdrdofg = "gdhaomhluua";
	bool odqppbqpehp = true;
	int aknbwmoubgu = 2087;
	bool jkyht = true;
	double vnrolhvm = 27777;
	double ujemwddd = 13572;
	if (13572 == 13572) {
		int aylubonvfa;
		for (aylubonvfa = 83; aylubonvfa > 0; aylubonvfa--) {
			continue;
		}
	}
	if (13572 == 13572) {
		int tcddqv;
		for (tcddqv = 7; tcddqv > 0; tcddqv--) {
			continue;
		}
	}
	return true;
}

bool arwkvkp::lrpymxtiwcgc(string azniuyv, int lehsiqw, string npyiqsid, int zawsutrlonquo, int pyldwyeofcr, double zenblugvowymo, bool muwkmzusht, int kiuhjbk) {
	string pqaugwzxqaenc = "ayxbgtpwpixnokfgswkbhavnquerjjnhydydcvncnrrlxyyjmyfigmycynbdcqpvogfuejfmkdpifmjrcpsyxivcrljohsxe";
	int gqtgee = 2100;
	int dyppnkfnxaqemz = 904;
	string zcumwkfzdvoroyj = "rktlnmfrssdxyoiprdfggjruphkmuolctzgmkjhzfrg";
	return false;
}

bool arwkvkp::sizpenrdzrm(bool wzjkke, int yqpqrjzxhk, bool tihzrwsvvhuk, int uixsbmncp, bool swggvrfvh) {
	int llmkaksv = 3056;
	if (3056 != 3056) {
		int dn;
		for (dn = 17; dn > 0; dn--) {
			continue;
		}
	}
	if (3056 != 3056) {
		int pciey;
		for (pciey = 55; pciey > 0; pciey--) {
			continue;
		}
	}
	if (3056 == 3056) {
		int usr;
		for (usr = 81; usr > 0; usr--) {
			continue;
		}
	}
	if (3056 != 3056) {
		int vjzdgmgldw;
		for (vjzdgmgldw = 16; vjzdgmgldw > 0; vjzdgmgldw--) {
			continue;
		}
	}
	return true;
}

double arwkvkp::wcriwssrygewhrpl(string jzsulwmcrgphgav, double yjkfqfqenmdpy, bool rcgwdkcacljqhp, double cgrmzvimqyzvqbx, int jqijql, string sfqfyoypsu, int nvefthlvhs, bool sepbbzpwsdjydyt, double pdrkupatunfzwo, bool sbkne) {
	string ktbyuzigtgfuov = "fapiyyrboesurrtrhdtte";
	if (string("fapiyyrboesurrtrhdtte") == string("fapiyyrboesurrtrhdtte")) {
		int lndir;
		for (lndir = 30; lndir > 0; lndir--) {
			continue;
		}
	}
	if (string("fapiyyrboesurrtrhdtte") == string("fapiyyrboesurrtrhdtte")) {
		int pvye;
		for (pvye = 13; pvye > 0; pvye--) {
			continue;
		}
	}
	if (string("fapiyyrboesurrtrhdtte") == string("fapiyyrboesurrtrhdtte")) {
		int izi;
		for (izi = 37; izi > 0; izi--) {
			continue;
		}
	}
	return 57140;
}

double arwkvkp::iadtmdqqfdepaxkdpu(string qabjwqjpbswb, string upzbkefs, int yfyuzff) {
	return 16155;
}

bool arwkvkp::gwoyqevbwcafygpgn(double puohwdhzmyuttm, int fkqfqzuy, string ebumls, double mffxcaoyamqdy) {
	int hraasjofzjq = 2611;
	string zppimotgseob = "uxygsrtcffaxgtammmuvbpnlencjshnppdmqgyaudgirkebmyjsifkmiunpuobqifcocnorqsuxpyp";
	double irgmw = 16549;
	string zscklnbbe = "gcjkhhaykwkiedgccynbnddlfqbkrfkflyjtvoxklxbfvxfimebtdrjzgnrpeihtfytuutjfjnjjcvpoxluftdvffjoorvvomee";
	if (string("gcjkhhaykwkiedgccynbnddlfqbkrfkflyjtvoxklxbfvxfimebtdrjzgnrpeihtfytuutjfjnjjcvpoxluftdvffjoorvvomee") == string("gcjkhhaykwkiedgccynbnddlfqbkrfkflyjtvoxklxbfvxfimebtdrjzgnrpeihtfytuutjfjnjjcvpoxluftdvffjoorvvomee")) {
		int temprt;
		for (temprt = 40; temprt > 0; temprt--) {
			continue;
		}
	}
	if (string("gcjkhhaykwkiedgccynbnddlfqbkrfkflyjtvoxklxbfvxfimebtdrjzgnrpeihtfytuutjfjnjjcvpoxluftdvffjoorvvomee") == string("gcjkhhaykwkiedgccynbnddlfqbkrfkflyjtvoxklxbfvxfimebtdrjzgnrpeihtfytuutjfjnjjcvpoxluftdvffjoorvvomee")) {
		int zjadc;
		for (zjadc = 4; zjadc > 0; zjadc--) {
			continue;
		}
	}
	if (16549 != 16549) {
		int awhbit;
		for (awhbit = 87; awhbit > 0; awhbit--) {
			continue;
		}
	}
	if (16549 != 16549) {
		int rkjfjeflyd;
		for (rkjfjeflyd = 94; rkjfjeflyd > 0; rkjfjeflyd--) {
			continue;
		}
	}
	if (2611 == 2611) {
		int hnwani;
		for (hnwani = 80; hnwani > 0; hnwani--) {
			continue;
		}
	}
	return true;
}

void arwkvkp::abxbipyabudylzknan(int ekejuryg, bool nafhb, bool cvmjslcas, bool nmvkgqzcnhhwbd, bool zubywxudyacw, int rxytuuatj, string wqmged, bool vgftjrhvvujtnxe, double zgtzafzhcmg, string oiaubbp) {
	string tjvoezxrautlsd = "rjuk";
	double ylicdm = 8203;
	string ihkaoqwvo = "tcnhvaeuiozu";
	string nnrtutnirrs = "sbhujxwjplijslxfeutjvroppxafdafwhyeuttrmdbkkdtqncnnogezpoeniibihykiuseoiuavrtjqhsfeyxnyv";
	int gkuxrzlknio = 1437;
	double qwbyeqxvlhzta = 30187;
	int hctgwdbzwhtuev = 61;
	string tdhhtvrbjfn = "oargsfvlnxajxwemzqnd";
	if (string("sbhujxwjplijslxfeutjvroppxafdafwhyeuttrmdbkkdtqncnnogezpoeniibihykiuseoiuavrtjqhsfeyxnyv") != string("sbhujxwjplijslxfeutjvroppxafdafwhyeuttrmdbkkdtqncnnogezpoeniibihykiuseoiuavrtjqhsfeyxnyv")) {
		int kyxe;
		for (kyxe = 81; kyxe > 0; kyxe--) {
			continue;
		}
	}
	if (string("rjuk") == string("rjuk")) {
		int psz;
		for (psz = 53; psz > 0; psz--) {
			continue;
		}
	}
	if (30187 == 30187) {
		int gjemijv;
		for (gjemijv = 58; gjemijv > 0; gjemijv--) {
			continue;
		}
	}
	if (string("oargsfvlnxajxwemzqnd") == string("oargsfvlnxajxwemzqnd")) {
		int fifjudqbz;
		for (fifjudqbz = 10; fifjudqbz > 0; fifjudqbz--) {
			continue;
		}
	}

}

string arwkvkp::srxltvssgoowf(double cbrhsszjt, double sddyjjzuzx, string eqrwnbnsl, double vcqweuxkvlgrgcp, string hnfyg, string ibfhqsxq, bool gjfex, bool pefpquwnhxzfn, int zfwjgxljanhzy) {
	double nudvwci = 10745;
	if (10745 == 10745) {
		int gid;
		for (gid = 97; gid > 0; gid--) {
			continue;
		}
	}
	if (10745 == 10745) {
		int fowxl;
		for (fowxl = 14; fowxl > 0; fowxl--) {
			continue;
		}
	}
	if (10745 != 10745) {
		int ajqd;
		for (ajqd = 1; ajqd > 0; ajqd--) {
			continue;
		}
	}
	return string("rdykqp");
}

double arwkvkp::ztvmdvzvqoyorbtcomeuolzmu(bool ohhgxzgrel, double kijlabsrhaahgr, double cysroimgzpcp, int urfde, int wpkxwevcksm, bool olcqzstsb, string npzisqpi, int labkmjddbxbbd) {
	double tqmwlcnqeeyzw = 28242;
	string httrgnygzxjnv = "ocrmbywuicdifldqmfmvsyrifqklebsepwdfkfhjxgogzzxzuuzucjbxmyasamhxferqarurhvbnov";
	int vxbktbdls = 4102;
	string ovgwqxeyxnomhcp = "mwyxxzbuqqqonpzdljggjuzcqiwnzovljvronsmuljd";
	string brablk = "uyjpobzhujfhxjqrwnuwfwuygyyluzxcajifwtbjsyfwbwcujydigztphjhbwjvrcsprkgqxybolyglfvnxtlkkecibafbsbjnp";
	double rjvtoy = 1202;
	double nnxweqij = 26464;
	double teisapjjtfox = 1793;
	double etbdicyimu = 5210;
	string uybdaloazw = "nakbkzqagqsoxfzyvihrwv";
	if (string("mwyxxzbuqqqonpzdljggjuzcqiwnzovljvronsmuljd") != string("mwyxxzbuqqqonpzdljggjuzcqiwnzovljvronsmuljd")) {
		int kyjxpquj;
		for (kyjxpquj = 12; kyjxpquj > 0; kyjxpquj--) {
			continue;
		}
	}
	if (string("mwyxxzbuqqqonpzdljggjuzcqiwnzovljvronsmuljd") == string("mwyxxzbuqqqonpzdljggjuzcqiwnzovljvronsmuljd")) {
		int ituyb;
		for (ituyb = 74; ituyb > 0; ituyb--) {
			continue;
		}
	}
	return 81117;
}

void arwkvkp::setsrppqza(string xuirzvidjjcqvy, double cksnccsx, bool kyphubah) {
	bool kzssmdlzlgekun = false;
	bool rzyixa = false;
	string ekwjitszpz = "nyzihjdajevbybtmmvtclvivrbfatsxicuzfuzxsipkdnjxhsgaxalrdqzqevxoy";
	string cbignbkmfhuix = "hvewbcgyvlmjztgpswmifebazvkwimfjclbaknhfwybxrqtiytwbggufdigfxixzcjhdnphormryksxmdgdadvw";
	string shyxjtpwurjjnyd = "bli";
	bool mhvafoyghtftrt = false;
	if (false != false) {
		int qxyuy;
		for (qxyuy = 8; qxyuy > 0; qxyuy--) {
			continue;
		}
	}
	if (false == false) {
		int nvtphnvi;
		for (nvtphnvi = 59; nvtphnvi > 0; nvtphnvi--) {
			continue;
		}
	}
	if (string("hvewbcgyvlmjztgpswmifebazvkwimfjclbaknhfwybxrqtiytwbggufdigfxixzcjhdnphormryksxmdgdadvw") == string("hvewbcgyvlmjztgpswmifebazvkwimfjclbaknhfwybxrqtiytwbggufdigfxixzcjhdnphormryksxmdgdadvw")) {
		int yleimckko;
		for (yleimckko = 56; yleimckko > 0; yleimckko--) {
			continue;
		}
	}

}

double arwkvkp::prgmfrcqzbzysojkbc(string raxogoy) {
	bool zjpwhgvqbj = false;
	if (false == false) {
		int xdiink;
		for (xdiink = 77; xdiink > 0; xdiink--) {
			continue;
		}
	}
	if (false != false) {
		int xihppystwo;
		for (xihppystwo = 67; xihppystwo > 0; xihppystwo--) {
			continue;
		}
	}
	if (false == false) {
		int xy;
		for (xy = 94; xy > 0; xy--) {
			continue;
		}
	}
	if (false == false) {
		int pvpmwxfar;
		for (pvpmwxfar = 16; pvpmwxfar > 0; pvpmwxfar--) {
			continue;
		}
	}
	if (false == false) {
		int gpkusoye;
		for (gpkusoye = 10; gpkusoye > 0; gpkusoye--) {
			continue;
		}
	}
	return 19610;
}

arwkvkp::arwkvkp() {
	this->iadtmdqqfdepaxkdpu(string("shdfhoevvgbfvgkpmejvsxwdiqi"), string("doaxispcbagxiyhxxkiqranvpfyhxfkcjrekhbqzcyysltctpa"), 1396);
	this->gwoyqevbwcafygpgn(28947, 65, string("ujkqsadexdtxifathwgjrgthfd"), 36696);
	this->abxbipyabudylzknan(4124, false, true, true, false, 2599, string("zqpjrysbsxjkmhowthgmhgdliklpmxq"), false, 28222, string("hkuthkxtnahoufcjlvl"));
	this->srxltvssgoowf(16696, 6841, string("xapkszfjmxtzgrcoalycpqazbammklorwunliinrovrgbsloqlxvckagflgreib"), 10194, string("qfdenaktmtocdgqcxmvdkwelocrjbrsyvdfsgrrbwxqwjpsfykgesux"), string("wckkuqnbunvdkozjtbpybdefoazxdpvznjvlfpss"), true, true, 2448);
	this->ztvmdvzvqoyorbtcomeuolzmu(false, 38990, 63961, 895, 1260, false, string("zuskhpubkwmdqkiuxdktjcfbwycbhzjabfbgfzasjaugjuzpaakksvhmdsodvwwbajxyxxnceywuohgumsqnfnrntkuzwxdmbm"), 1920);
	this->setsrppqza(string("aihgekgzywpbmgpupvtwiuyelwhm"), 18303, false);
	this->prgmfrcqzbzysojkbc(string("zkfgvykqjxkfqnxnxramdrxzxmtrabpyycbtgdkbchfk"));
	this->bjbaeziabkzfrgvpcxfifjuw(826, false, true, 3750, 2449, 2523, true, 6589, 64092, string("knvwfjcmyeeosgmpwaxcreilcfnbbdvijsydwljlomuwjsuiwdlbgpiwpqgntmxsyxrsgxwnlsdqdxuzpnxlmqssxlczv"));
	this->yxzqgpxuazhbktoaadfqhcbyq(true);
	this->lrpymxtiwcgc(string("xjnmucxpzuhpljtueiderhxklrulsrkefqucmxatotixgvmiegmsnltyxqrbamzltse"), 7171, string("nkarjtpzssfltrtfknwbvwnhvlrsnehvrkiopueundnklsrygorwxikzimqwttckzinfnghy"), 1588, 8827, 33418, true, 675);
	this->sizpenrdzrm(true, 178, false, 1969, false);
	this->wcriwssrygewhrpl(string("bshvhsqehikhvlviysvujzvhsodbgtfcyqjxttuqbmkdrwmfkjunspiucxosrmlmrdubgipgwknvsapwtfltxzkovlzgdrph"), 8483, false, 35344, 4400, string("luovswrdxdwcahmigirhrzghnftqafucybizlxywmzbzebmnkzcfrtaakbdmeqkmylvfhj"), 3195, false, 81553, true);
	this->huglnyoknizirvhnmkqxxlrwe(string("rpwwottp"), string("afhhlejmdwyycynqzwdralbipgzwakvkxswcomxkrtqbwgfzmed"));
	this->luzdxqtmhgckhkurkdeusu();
	this->lzhkkrtsgweruivvurxt(24975, 5146, 18696, 1048, 963, 6043);
	this->zykksgximxzdk(string("ncjgdqyjlgxnyetayegmotabis"), string("nlwgrbcgmsfbsyrsstbanifkfhhchvejxndq"));
	this->ginovxktwggwknxec(14029, true, 127, false, string("esraieybiejjdwxyrvldrjshkguktphmsusytgifsydljvempjlgpulhajkakrqeuoijrvghpwmqjqbajadzlfajtijd"), 3231);
	this->yupyvnrjrtkvdfrmrvvo(string("ffmuimyjwtzcuxhbxqwkydbbtyqcu"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class isysjzu {
public:
	double owumzotic;
	double wfdzr;
	int tniqosfrtvs;
	int vtxydw;
	isysjzu();
	string gbjpqrgakhj();
	int axxevmiwahpgfo(string nmnor, double wibnfuizjhzhjyq, double sqkaldubyleo);
	double nvhwlpgcoatdv();
	string zpfqobqasvaguxae(int twqcifepytdpel, bool neubxhuynateofy, double cqcqqxuwhqfxvd);
	bool vnqhdhoeiejjbalzbpwu(string hrcihwnh, string okzcstvfyaejajz, string wyvbuxrlij, double zgtthxgtu, string wsych, string rzbfb);

protected:
	int nwtoiuhbq;

	double kymwbsgwmm(string knibmp, int arhltaxkv, int mkhmhqmfoiq);
	double compmuvfetlkkx(int iouzfrnytoj, int vgbjhtvhxdkmgn);
	int vqhbpqqcumyfiutlxleuv(string rfqpnfpvt, int kajjn, int fpazpfyejbjwltt, double hlfmftzefdzdspg, int npmeztc, bool ouvcjsvfnf, int dasoj, int joewrvqcdap, int jedxanjimicm, bool ipxxkzylmqe);
	bool juqwsnitarprz(double fvnvhznwqpval, string nsbxcq);

private:
	double bimcn;
	int toqysedandrix;

	double yqvnvgrtbilkxfbprbls(int tesnzmmkr, double asmzpncbjoijd, int wikgneonfnvvt, string rmetyk);

};


double isysjzu::yqvnvgrtbilkxfbprbls(int tesnzmmkr, double asmzpncbjoijd, int wikgneonfnvvt, string rmetyk) {
	string yagncs = "iyukyrxpzoxewclpicqjlxzxmnrwynfvsuwqikfodmhzlkxbb";
	int guwxzeiotswr = 984;
	string qmubnmqo = "incrnz";
	string vptoxvmzlvofp = "mdzvvctmxsigkxcqrtphjyjvhnstpnqiumruxqgtonmapgkuqk";
	int zidaqqezi = 1357;
	double ovfdfkhpbh = 34175;
	int ythrsnsspmvsfea = 5585;
	if (5585 == 5585) {
		int qbhxm;
		for (qbhxm = 84; qbhxm > 0; qbhxm--) {
			continue;
		}
	}
	if (34175 == 34175) {
		int sbh;
		for (sbh = 53; sbh > 0; sbh--) {
			continue;
		}
	}
	if (5585 == 5585) {
		int qourpzxlis;
		for (qourpzxlis = 76; qourpzxlis > 0; qourpzxlis--) {
			continue;
		}
	}
	if (984 != 984) {
		int aauyozojmi;
		for (aauyozojmi = 44; aauyozojmi > 0; aauyozojmi--) {
			continue;
		}
	}
	return 65457;
}

double isysjzu::kymwbsgwmm(string knibmp, int arhltaxkv, int mkhmhqmfoiq) {
	double yfadxabnv = 712;
	string emzbkgbt = "oumwk";
	double tjwrcbllcbyg = 34081;
	string lmciieqeidpm = "obgot";
	string iknyvgacfpvqx = "ljgftymujwszusmxiqquaeaoopnnbntftexpfhnwamhurjjwayecbjdubjmtnnajgswbhrzswcvaotdfkswouszma";
	int eyqlabbx = 6977;
	bool ykjcbyqdtzhw = false;
	bool jqptkdmxqy = false;
	bool bxekfoyquickri = true;
	bool xtabahgjjjya = true;
	return 14415;
}

double isysjzu::compmuvfetlkkx(int iouzfrnytoj, int vgbjhtvhxdkmgn) {
	int gdebzxxm = 2618;
	double ytmkkuojhykvruq = 87892;
	string ommiolpwkg = "umiisgwwedfsfpnltkewqhnunlompfkdomdcagctxxzy";
	bool cyvhmwryybf = true;
	double vnshysicpibn = 6656;
	int oyfrmlduuu = 354;
	string vtwhtgbvyjxfeek = "vaylfwzxpipxbsnhrmgbkarozrahshjlpxsospytolbhirppbjwcpmuumpeicm";
	string uhcvrkzannci = "csjg";
	int rmlbgyeki = 1777;
	if (354 == 354) {
		int ike;
		for (ike = 46; ike > 0; ike--) {
			continue;
		}
	}
	if (string("vaylfwzxpipxbsnhrmgbkarozrahshjlpxsospytolbhirppbjwcpmuumpeicm") == string("vaylfwzxpipxbsnhrmgbkarozrahshjlpxsospytolbhirppbjwcpmuumpeicm")) {
		int aowg;
		for (aowg = 54; aowg > 0; aowg--) {
			continue;
		}
	}
	if (1777 == 1777) {
		int ctzbcoauh;
		for (ctzbcoauh = 48; ctzbcoauh > 0; ctzbcoauh--) {
			continue;
		}
	}
	if (87892 != 87892) {
		int jjczuvdxs;
		for (jjczuvdxs = 37; jjczuvdxs > 0; jjczuvdxs--) {
			continue;
		}
	}
	if (true == true) {
		int ieqcclp;
		for (ieqcclp = 4; ieqcclp > 0; ieqcclp--) {
			continue;
		}
	}
	return 26818;
}

int isysjzu::vqhbpqqcumyfiutlxleuv(string rfqpnfpvt, int kajjn, int fpazpfyejbjwltt, double hlfmftzefdzdspg, int npmeztc, bool ouvcjsvfnf, int dasoj, int joewrvqcdap, int jedxanjimicm, bool ipxxkzylmqe) {
	int akhkl = 3398;
	double ymqsnvz = 978;
	bool ipzwkbwywf = false;
	bool shwsrrdklkrsuuy = true;
	int gagmzskhgbf = 1637;
	bool rogtthiepccxckl = true;
	int zaxpkxzek = 1699;
	int lothnbci = 3823;
	double sckufoptygse = 9074;
	if (true != true) {
		int vovfy;
		for (vovfy = 70; vovfy > 0; vovfy--) {
			continue;
		}
	}
	if (3823 != 3823) {
		int ssmlplvy;
		for (ssmlplvy = 8; ssmlplvy > 0; ssmlplvy--) {
			continue;
		}
	}
	if (978 != 978) {
		int svosbtv;
		for (svosbtv = 86; svosbtv > 0; svosbtv--) {
			continue;
		}
	}
	return 32882;
}

bool isysjzu::juqwsnitarprz(double fvnvhznwqpval, string nsbxcq) {
	string ykicbczmbemvlw = "rtbmoutghbnotgbcwjszbmosvuepdiswiwwssmczwdhmvjahzddmlgmyqzrbzuoixvfsbwmeltqqkvejkejcuyfkbsrvjv";
	int inoydie = 9587;
	bool hgvwrdbwzowwgq = true;
	int vubzdipzfmqmnbo = 5747;
	int ryiowmbvseppo = 1627;
	int catdz = 3864;
	if (5747 == 5747) {
		int njnorvtjle;
		for (njnorvtjle = 81; njnorvtjle > 0; njnorvtjle--) {
			continue;
		}
	}
	if (3864 != 3864) {
		int rnaqtlrcxo;
		for (rnaqtlrcxo = 29; rnaqtlrcxo > 0; rnaqtlrcxo--) {
			continue;
		}
	}
	return true;
}

string isysjzu::gbjpqrgakhj() {
	double wsumhenvmra = 14640;
	double ltiaewuqohds = 4554;
	double gtpkf = 21271;
	double ccxozrlubfl = 26406;
	string btxfcxakfvmurte = "eiegbfwjvtgrqufapspnk";
	if (4554 == 4554) {
		int mh;
		for (mh = 99; mh > 0; mh--) {
			continue;
		}
	}
	if (4554 == 4554) {
		int fzxiy;
		for (fzxiy = 4; fzxiy > 0; fzxiy--) {
			continue;
		}
	}
	if (4554 == 4554) {
		int jqvjxy;
		for (jqvjxy = 40; jqvjxy > 0; jqvjxy--) {
			continue;
		}
	}
	return string("lolihjcrwvrjqzcey");
}

int isysjzu::axxevmiwahpgfo(string nmnor, double wibnfuizjhzhjyq, double sqkaldubyleo) {
	double yxgweticnq = 32850;
	bool jjeoj = true;
	bool nwjntjlew = false;
	return 48223;
}

double isysjzu::nvhwlpgcoatdv() {
	double jibmv = 18114;
	string gdwqabaeju = "ewjamvftivonqxjtknzis";
	double vjtkhdjkqxf = 28290;
	double lwiotyyk = 13671;
	bool vrgkucl = false;
	if (18114 != 18114) {
		int zphf;
		for (zphf = 55; zphf > 0; zphf--) {
			continue;
		}
	}
	if (13671 == 13671) {
		int fi;
		for (fi = 4; fi > 0; fi--) {
			continue;
		}
	}
	return 59459;
}

string isysjzu::zpfqobqasvaguxae(int twqcifepytdpel, bool neubxhuynateofy, double cqcqqxuwhqfxvd) {
	int zyojrlbzle = 740;
	int fcmtbps = 2440;
	bool vievfp = true;
	string iklmgezlcopaz = "cxxzqhqvqpjhqurtetrocbyetoiyvglywjhfrdx";
	double qemxdfhr = 25114;
	bool wrouoicoe = false;
	return string("zyfcfxlpncrliqlncvy");
}

bool isysjzu::vnqhdhoeiejjbalzbpwu(string hrcihwnh, string okzcstvfyaejajz, string wyvbuxrlij, double zgtthxgtu, string wsych, string rzbfb) {
	int lcnlv = 848;
	string qbbpsc = "usqgfraexeaslxzenkcehcwtyjmlwzsukczluq";
	string kwqyigelwbvmc = "zffbhlkokbruytwrhcvwrdtgayyfbetezynspexfwqnkvkthidaxrebdguakidizgnaubsnilufyqbkbdfijydujkjgwt";
	bool yeutdotrvezkxeb = true;
	double xbuhybapi = 6724;
	if (848 == 848) {
		int qjpg;
		for (qjpg = 91; qjpg > 0; qjpg--) {
			continue;
		}
	}
	if (string("usqgfraexeaslxzenkcehcwtyjmlwzsukczluq") == string("usqgfraexeaslxzenkcehcwtyjmlwzsukczluq")) {
		int hkx;
		for (hkx = 19; hkx > 0; hkx--) {
			continue;
		}
	}
	return false;
}

isysjzu::isysjzu() {
	this->gbjpqrgakhj();
	this->axxevmiwahpgfo(string("ceihdimdcdkipcujmrpqoujjziztorrmwjjkdtsztujvkzuguidpdyv"), 9753, 47362);
	this->nvhwlpgcoatdv();
	this->zpfqobqasvaguxae(970, true, 8432);
	this->vnqhdhoeiejjbalzbpwu(string("tsydzgkmcnvhjapfcehorqvidyengmhqhydlcpqbsebpdpxkrgdndooeqkbsvfdyxcdziv"), string("ofgvkbicyupzfbvgggskxnnvdpvoaszjloysbptfjqkmrrxftlgebztunxkggx"), string("obtppelhkcrzufuqpsyztfokbkcyiuyigemxfewjcsbiiwgrlsccpszrwstfdajhkrtmqtkatvzlmybclcxgfhqksf"), 72910, string("re"), string("vardlqxeupgjppjxknpcmiydknjlgudbydwqnjaqmjbrkuyxzdixmygiixcsiahfsxitgxwabndooyxpb"));
	this->kymwbsgwmm(string("qqbbavgfqz"), 6048, 1831);
	this->compmuvfetlkkx(1156, 5715);
	this->vqhbpqqcumyfiutlxleuv(string("domekwoeupoigjj"), 6174, 4675, 13787, 3837, true, 799, 269, 6735, true);
	this->juqwsnitarprz(38859, string("lahrhkmhbqifoduqbhomjrqfabefl"));
	this->yqvnvgrtbilkxfbprbls(274, 73943, 186, string("zyrznbvgddxybxdhyfktisvxvokanwsbcfutgdirjerkoymejjdctxfzakbannkzvzaosjzwczjhuy"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class dxjpoer {
public:
	double gwuwbhm;
	string fsrjhfkvbavlpe;
	dxjpoer();
	int kfaouktlxfdgudmrvo();

protected:
	string qtepinbjzax;
	string beeuky;

	int julyzvixnefuro(double vguqdhztkglb, int ccgvn);
	double rkkgyiiarovtr(int rruacpzmg, string pwqsfzbgbcgl, bool elmpxkrxbcvjrsq, int gylnuuylbimgr, double gfxupzkyjwum, double hxnkcaq, string hixhs, string tsiztyliaualfi, string fcjcno, bool vvescuagvtcale);
	int ambudchqavafzumplat(int mibyrxgqdcedruw, string byrauuy, string xiknqfpsdi, int mqxmcrghstrtev, bool ekljzougkl, string lpqodtasu, int mnsauvgqgnzfyni, int kqkfvjbwrqxost);
	bool hjweolsfmimbbt(bool yriamvlzbll);
	int czmuyxmtua(string xicseley, bool xscaiwtdwynkxi, double miaerjkr, int mflkydppwn, double yhfbpgo, double wtpyigtpuw, bool wdeis, bool fggcyzutzloqwdj, string yzfxewhsaw);
	double qaaixinwmkystogqyuyzxrd(int yyesmkrmpxreij, bool gnfxhddqi, string vliurxgls, bool jedenckaggbuji, bool jacyemcb, bool oxkyzvckpxq);
	double hecvqojijxbyylts();
	int iftjmargoggimkerf(int mcjrqfmypoagtjs, bool ppzbavaezb, bool fvhgv, string bseosotbghnu, int asqfevw, int rljglquiqw);
	bool sgyokjlijzqlcmdggqadwbys(bool jgyigd, bool rykjihkjjdextx, string qwlrkzzhi, bool wwgeorbajjxoao, string doztwxbtaxnl, int dfdoktyhomy, string kzksn, double nqdnpki);

private:
	bool ixadgdsxl;
	int pikazzql;
	int osuiukmus;
	int rycqho;
	bool rcqrdvulszyx;

	int tfwxgzplaubvvorpzupequo(int siahitslkioe);
	void gqoantkfpzbuc();

};


int dxjpoer::tfwxgzplaubvvorpzupequo(int siahitslkioe) {
	string rmryknqeuqomwug = "kexkbghyezshfkcoikgmbioulbp";
	bool dtehv = true;
	bool krdflfecmssaf = false;
	bool syqacegjdvxn = true;
	double ethuaaxuqy = 11490;
	double hexrxafzlgebew = 27560;
	string hbpst = "ykwcvhjxewsydrbhwfvlharyuafhebdixygpowqhygpockrylaragvqfujjbddu";
	if (string("kexkbghyezshfkcoikgmbioulbp") != string("kexkbghyezshfkcoikgmbioulbp")) {
		int zffdg;
		for (zffdg = 84; zffdg > 0; zffdg--) {
			continue;
		}
	}
	return 53376;
}

void dxjpoer::gqoantkfpzbuc() {
	int mekdmlmksx = 655;
	double siygugitftbyg = 13986;
	bool fxtpg = false;
	string yaldrex = "repqpbigdcnlpfbrofsouyqycugt";
	string ijcetu = "iyhpfcqecbsspsztnzvckairxa";
	string remptpcestybey = "ptwymmqgmvivlvuairyzefyajzlraovtmtlvantlpujazkbbxhihfukryseopffijwuxhglpolcwxlaxgxyiibgtsdepx";
	if (string("repqpbigdcnlpfbrofsouyqycugt") != string("repqpbigdcnlpfbrofsouyqycugt")) {
		int lcr;
		for (lcr = 21; lcr > 0; lcr--) {
			continue;
		}
	}
	if (13986 != 13986) {
		int ixcatc;
		for (ixcatc = 14; ixcatc > 0; ixcatc--) {
			continue;
		}
	}
	if (false == false) {
		int yyuvvgbr;
		for (yyuvvgbr = 27; yyuvvgbr > 0; yyuvvgbr--) {
			continue;
		}
	}

}

int dxjpoer::julyzvixnefuro(double vguqdhztkglb, int ccgvn) {
	int tynoop = 2342;
	double wdguqxkmuitqaj = 30097;
	int cirxghvkceocj = 197;
	int rqvaxgulhgrxl = 1633;
	int crcbalrnqx = 549;
	double njbdzhi = 20463;
	string idlzxjkltkh = "hpxzgempmnrkiyeatxzpzojvxevkflksgiuj";
	if (30097 == 30097) {
		int canfhpcdqi;
		for (canfhpcdqi = 4; canfhpcdqi > 0; canfhpcdqi--) {
			continue;
		}
	}
	if (197 != 197) {
		int swr;
		for (swr = 36; swr > 0; swr--) {
			continue;
		}
	}
	if (string("hpxzgempmnrkiyeatxzpzojvxevkflksgiuj") == string("hpxzgempmnrkiyeatxzpzojvxevkflksgiuj")) {
		int hvuvxh;
		for (hvuvxh = 89; hvuvxh > 0; hvuvxh--) {
			continue;
		}
	}
	if (197 != 197) {
		int vflw;
		for (vflw = 49; vflw > 0; vflw--) {
			continue;
		}
	}
	return 67725;
}

double dxjpoer::rkkgyiiarovtr(int rruacpzmg, string pwqsfzbgbcgl, bool elmpxkrxbcvjrsq, int gylnuuylbimgr, double gfxupzkyjwum, double hxnkcaq, string hixhs, string tsiztyliaualfi, string fcjcno, bool vvescuagvtcale) {
	string jiwuoqjdfttnddp = "esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm";
	if (string("esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm") == string("esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm")) {
		int kozrwgnb;
		for (kozrwgnb = 94; kozrwgnb > 0; kozrwgnb--) {
			continue;
		}
	}
	if (string("esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm") != string("esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm")) {
		int ittui;
		for (ittui = 66; ittui > 0; ittui--) {
			continue;
		}
	}
	if (string("esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm") == string("esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm")) {
		int wlhykpipt;
		for (wlhykpipt = 20; wlhykpipt > 0; wlhykpipt--) {
			continue;
		}
	}
	if (string("esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm") != string("esjzdizpruhnghhautzymmeiqztodxbkrksggivjzpjlgpmyyddapvrrdbkbrbjhzyswclsbtdm")) {
		int lcfcmm;
		for (lcfcmm = 12; lcfcmm > 0; lcfcmm--) {
			continue;
		}
	}
	return 33070;
}

int dxjpoer::ambudchqavafzumplat(int mibyrxgqdcedruw, string byrauuy, string xiknqfpsdi, int mqxmcrghstrtev, bool ekljzougkl, string lpqodtasu, int mnsauvgqgnzfyni, int kqkfvjbwrqxost) {
	double mjwsbpp = 17289;
	double ycftvnhgeiifz = 24159;
	bool zjjvapriwlli = true;
	bool vnsuofskqn = false;
	if (true != true) {
		int przxqjvu;
		for (przxqjvu = 61; przxqjvu > 0; przxqjvu--) {
			continue;
		}
	}
	if (true == true) {
		int ojlfti;
		for (ojlfti = 21; ojlfti > 0; ojlfti--) {
			continue;
		}
	}
	if (17289 != 17289) {
		int hl;
		for (hl = 13; hl > 0; hl--) {
			continue;
		}
	}
	if (17289 == 17289) {
		int wh;
		for (wh = 98; wh > 0; wh--) {
			continue;
		}
	}
	return 47287;
}

bool dxjpoer::hjweolsfmimbbt(bool yriamvlzbll) {
	bool gmjfoxqcs = true;
	string njcyaqdccmsk = "czvoelbmytlkdniizwcu";
	double rnrgusydgoofmwm = 10997;
	string fvhjmrqrlrqjz = "lnadubotcbpcymabnjknnfoyrikwwfilfwotnsckyvxvueddviejnaaewza";
	bool vxpmewgmju = true;
	string dkfxtphyj = "cvsjfyokruaagnnogcmtdhvdajjexwhzcpoxmzptvxvywjbhcqvmtlbld";
	int tdpujcexwqj = 2814;
	int rngoeztqbcoppc = 6715;
	double rnpqihnnhpls = 83509;
	if (true != true) {
		int pauwm;
		for (pauwm = 85; pauwm > 0; pauwm--) {
			continue;
		}
	}
	if (83509 != 83509) {
		int dpuq;
		for (dpuq = 66; dpuq > 0; dpuq--) {
			continue;
		}
	}
	if (83509 == 83509) {
		int njqueh;
		for (njqueh = 75; njqueh > 0; njqueh--) {
			continue;
		}
	}
	return false;
}

int dxjpoer::czmuyxmtua(string xicseley, bool xscaiwtdwynkxi, double miaerjkr, int mflkydppwn, double yhfbpgo, double wtpyigtpuw, bool wdeis, bool fggcyzutzloqwdj, string yzfxewhsaw) {
	int hjjxvpkhrrcr = 32;
	bool vsmvbmiaap = false;
	int ulrwuczlhoeu = 4611;
	string xlxfbnicigjgztd = "tvaplpduwjtmxsomdzkto";
	return 65086;
}

double dxjpoer::qaaixinwmkystogqyuyzxrd(int yyesmkrmpxreij, bool gnfxhddqi, string vliurxgls, bool jedenckaggbuji, bool jacyemcb, bool oxkyzvckpxq) {
	string wfshh = "laqmoyneqcfqwyrvzkxmq";
	int qugugrcdmv = 1388;
	int dvefnlyfnzqk = 2989;
	int acdksuplpxn = 2974;
	double fxtchij = 10791;
	if (10791 == 10791) {
		int sdyeolj;
		for (sdyeolj = 3; sdyeolj > 0; sdyeolj--) {
			continue;
		}
	}
	return 81519;
}

double dxjpoer::hecvqojijxbyylts() {
	string wwjqb = "ncdqgydptrscwdtavoriyapvvfirtuykvxrpvoeckcbsxlxydoyaarptmuropbzlcngnzhpugjuqzhitpioprqeqyswib";
	int mktocwx = 321;
	bool bscjocvlos = false;
	int djphwtkhrylvsip = 2284;
	bool jxzhhqkubeqvnb = false;
	if (321 == 321) {
		int oudva;
		for (oudva = 12; oudva > 0; oudva--) {
			continue;
		}
	}
	if (false == false) {
		int hqyqkulf;
		for (hqyqkulf = 94; hqyqkulf > 0; hqyqkulf--) {
			continue;
		}
	}
	if (321 != 321) {
		int tpvlgtg;
		for (tpvlgtg = 9; tpvlgtg > 0; tpvlgtg--) {
			continue;
		}
	}
	if (false != false) {
		int gbgcdlei;
		for (gbgcdlei = 74; gbgcdlei > 0; gbgcdlei--) {
			continue;
		}
	}
	return 63797;
}

int dxjpoer::iftjmargoggimkerf(int mcjrqfmypoagtjs, bool ppzbavaezb, bool fvhgv, string bseosotbghnu, int asqfevw, int rljglquiqw) {
	int phwmqkmkyaky = 699;
	bool mzujmkjzayb = false;
	string gahedclv = "yqdrtvbqsjg";
	double phdlqcuk = 8640;
	if (false != false) {
		int gkursmofwl;
		for (gkursmofwl = 94; gkursmofwl > 0; gkursmofwl--) {
			continue;
		}
	}
	if (699 != 699) {
		int ng;
		for (ng = 28; ng > 0; ng--) {
			continue;
		}
	}
	return 3563;
}

bool dxjpoer::sgyokjlijzqlcmdggqadwbys(bool jgyigd, bool rykjihkjjdextx, string qwlrkzzhi, bool wwgeorbajjxoao, string doztwxbtaxnl, int dfdoktyhomy, string kzksn, double nqdnpki) {
	bool ycdvyodzrxgh = true;
	int yszvvkih = 1164;
	bool zznaokufovzol = false;
	int likshudchnfdal = 770;
	if (1164 != 1164) {
		int nw;
		for (nw = 82; nw > 0; nw--) {
			continue;
		}
	}
	if (1164 != 1164) {
		int btlhdad;
		for (btlhdad = 43; btlhdad > 0; btlhdad--) {
			continue;
		}
	}
	return true;
}

int dxjpoer::kfaouktlxfdgudmrvo() {
	bool tiugvbvsfycxlwy = false;
	bool gfwqmuufs = true;
	double dlxynwubxfa = 11035;
	bool wevyvghoijpejnl = true;
	string fbjhwovqgxejhbb = "rzbkkyajwpydpimhbfw";
	bool kyewriabwp = false;
	double zhpnaqztavn = 32611;
	if (false == false) {
		int fbgvc;
		for (fbgvc = 3; fbgvc > 0; fbgvc--) {
			continue;
		}
	}
	return 30345;
}

dxjpoer::dxjpoer() {
	this->kfaouktlxfdgudmrvo();
	this->julyzvixnefuro(8266, 459);
	this->rkkgyiiarovtr(3741, string("qztpm"), false, 2620, 65703, 30009, string("sapbewsfvttudlhwabdmnkfwmscgbpzgqmsjjiwgijbolivndmnlr"), string("qgucmxczchjlconzbmnsctabgtxrwlmxlkgoezefevxblkuvdqkgkdotbziyashsxobywxkgxlxugvxtzwoy"), string("qysqzgcbyljusrbioma"), false);
	this->ambudchqavafzumplat(5028, string("zffngnoonaooeiniyfiebumanjuymfyhypfhasxlyuvvlxhrdjlaklprwsyrkcukwpjppzenwprvhwitdfsqgnojveuzek"), string("cjtwsopwysscauzracadsqzlloxawzbjvcijhytqw"), 4895, false, string("smnqciapqlueblwvzqnbfcsaylgnvcsnahwpzrwyibdcumnflpgvdwjqzyusfigjujbbwncazjcogkkmfnvxqcdkl"), 1437, 6079);
	this->hjweolsfmimbbt(false);
	this->czmuyxmtua(string("mqmpuzisevpqjyfvtidgyrhpietcivxuobzhdbnilmcsahoyadavkdxlzjchbgtqzdohkffwfjimjep"), true, 11359, 4621, 17625, 1906, false, false, string("okxdqedavgcujudwkgzhagrboxjbincmjuqqwrn"));
	this->qaaixinwmkystogqyuyzxrd(975, false, string("ajikqvl"), true, true, false);
	this->hecvqojijxbyylts();
	this->iftjmargoggimkerf(3618, false, false, string("eplakzbqtziygfyrisxyvxuveetsodonotnxrsocdkxvun"), 846, 3332);
	this->sgyokjlijzqlcmdggqadwbys(true, true, string("iqrdorxdwhwnmcvctafpachujaliu"), false, string("qljfgnjyjkgwylavhjxidnyuucdhlunebfvqdyoyf"), 2379, string("ccluhsidogakesltdpooxzxyhxdyoain"), 37591);
	this->tfwxgzplaubvvorpzupequo(2295);
	this->gqoantkfpzbuc();
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class esqxcgs {
public:
	int qjqvs;
	esqxcgs();
	bool dmekzgbqrzlvqsd();

protected:
	string njytawuc;
	bool afhgsximljssp;
	int rhfuz;

	string tvzxrtzdnelmmvybbaqzt(double ywkzfzi, double dzsfgsvrxey);
	double qkzcksxwaaqxovtltr(string ofqcwbfjupt, double zejonbdekxi, bool hliqtnyrnymv, bool odfaihvafzstx, string vtllxrhohe);
	bool sdrxsquivucqf(bool pyvgjndix, string jzdhq, int soyyvizrvgofh, string ifqvtzqxyachg);
	double vgpgxskspa(string xqfinterjnzd, int yzolhtf, double uaammlkxlmuxosv, double bqedabiunjfcy, bool ievxejrpsjx, double vigtmce, double ihufpqxnmukvo, bool apuaxfjvmf);
	bool khnsjqhkrmzefjb(int tptal, bool pcpte, double pwhmlqxuyurkmob, double ctrpzgmlibzflol, double gxjioqphytkm, double ungtxchxccqx, double xejekjdgh, double nacbgu);
	string pemfmyzqqrtozvwhqaapk(string uqnqvau, string nckulpyzlifs, int pqyppxhjodugff, string qxcagewo, bool rtahwfafxiy, double smwgftcjjad, double xrclgaorrquhu, string caprhfqdtc, int lewngxvt, bool jdkjxvwbudedtj);
	void vwrhhvjvtvot(double tsimssmqfxqfn, double iqbuc, double txzczcl, bool cymwpxxyhiavnj, bool nemseq);
	bool drdheppclqebel(double tyghahdgzdflij, string elsjgujdbe);
	double qafgoedravgekwrcw(double sxoay, string wrgvrrrfpeelrny, string inkcqo);

private:
	double awkxfcjoi;

	bool hqgrqugoiqmjweyklprgw(double aszjkq, double jyovp, int hgateq, string thevmir);
	int jpmnengnaepbnlhodwyrtfr(bool wovrtudnpbr, double jrpwlpzyjo, string qqifyetwwph, bool qnlstoxydh, int klqtm, double sypprvvz, string wiuxstnaabeuww, string bghokrqi, string urdtjulqfvijj);
	void tsrrmthgqjkaqc(int noxijeltbxl, string bvkwtmmdnrlkw, bool ecgizfygtpy);
	double afpjtwpxdhoocoiehqvidjnoi(double aooao, int cqmcya, string jdmkqzqqjlntwgi, double fxuyk, bool lydqn, string yffinwvm, bool dsitiyuqigtq);
	int shcgozbvepygrolardmqwj(double qvuuymdtrusyhc, bool jzuvyetd, string qkwcjnufhb, bool pxixq, bool ytanjhf, int jnqyoxctxwafeqz, int qsaogsr, string uhewfaqkql, double aivdkltsdmh, int zkloro);
	double uounnvfaraogmszcego(bool txzdd, int mdaidpew, int hfhyir, int pbknptynjie, double pcduhzuaztkf, int jrswlmlmga);
	bool lbsfaderphzqiojamckts(int rhfevuhcgjlcdc, int uvvafde, int rzzeyvw, bool ujdsiecgguv, int ayufvhcfpqlcamc);

};


bool esqxcgs::hqgrqugoiqmjweyklprgw(double aszjkq, double jyovp, int hgateq, string thevmir) {
	return false;
}

int esqxcgs::jpmnengnaepbnlhodwyrtfr(bool wovrtudnpbr, double jrpwlpzyjo, string qqifyetwwph, bool qnlstoxydh, int klqtm, double sypprvvz, string wiuxstnaabeuww, string bghokrqi, string urdtjulqfvijj) {
	return 69431;
}

void esqxcgs::tsrrmthgqjkaqc(int noxijeltbxl, string bvkwtmmdnrlkw, bool ecgizfygtpy) {
	double ifdjxc = 11830;
	double pkunxocaylzur = 29107;
	bool gntmiwqyzfwuutt = false;
	bool kkqhwpff = false;
	bool mxysifwy = false;
	string fvljhzkbikwrn = "ykphliprjauhjwbmgmer";
	bool fvifhjvww = false;
	int yeaurfr = 1223;
	if (string("ykphliprjauhjwbmgmer") != string("ykphliprjauhjwbmgmer")) {
		int zdl;
		for (zdl = 20; zdl > 0; zdl--) {
			continue;
		}
	}
	if (1223 == 1223) {
		int rveulg;
		for (rveulg = 44; rveulg > 0; rveulg--) {
			continue;
		}
	}
	if (false == false) {
		int xvih;
		for (xvih = 77; xvih > 0; xvih--) {
			continue;
		}
	}

}

double esqxcgs::afpjtwpxdhoocoiehqvidjnoi(double aooao, int cqmcya, string jdmkqzqqjlntwgi, double fxuyk, bool lydqn, string yffinwvm, bool dsitiyuqigtq) {
	int ojqhuwha = 1116;
	double utyjlskkkcn = 5028;
	int yiwsxxnqsouaht = 1144;
	int nduyrdnga = 11;
	string woqhbzbbdlwpw = "wsdtbazruxpiyipiuymumghhkvsawaqweudorjlsioboxchfgmyejbbzvbmhglkfpjlhwgawippopoahyp";
	double tqixm = 22163;
	if (5028 == 5028) {
		int bpggihggy;
		for (bpggihggy = 18; bpggihggy > 0; bpggihggy--) {
			continue;
		}
	}
	if (1144 == 1144) {
		int rkmqysiu;
		for (rkmqysiu = 48; rkmqysiu > 0; rkmqysiu--) {
			continue;
		}
	}
	return 1282;
}

int esqxcgs::shcgozbvepygrolardmqwj(double qvuuymdtrusyhc, bool jzuvyetd, string qkwcjnufhb, bool pxixq, bool ytanjhf, int jnqyoxctxwafeqz, int qsaogsr, string uhewfaqkql, double aivdkltsdmh, int zkloro) {
	double klzioeefks = 28154;
	int ewxicdcltxk = 1347;
	double ilmzc = 6649;
	int nxceggdfyfzdox = 2583;
	string hbkytee = "x";
	double cfvgn = 13299;
	double ppawbuwsjdtj = 15443;
	string rtwhkpvnrnnw = "ciyvvjqdacigwnofepqudzrkubbvxfjjipzrxgiwyuibbxylebsjck";
	double xhnzcdpelsrltca = 30105;
	int cfixxkwy = 265;
	if (2583 == 2583) {
		int pm;
		for (pm = 3; pm > 0; pm--) {
			continue;
		}
	}
	if (265 != 265) {
		int xoqpr;
		for (xoqpr = 40; xoqpr > 0; xoqpr--) {
			continue;
		}
	}
	if (28154 == 28154) {
		int zsrxipy;
		for (zsrxipy = 43; zsrxipy > 0; zsrxipy--) {
			continue;
		}
	}
	return 4113;
}

double esqxcgs::uounnvfaraogmszcego(bool txzdd, int mdaidpew, int hfhyir, int pbknptynjie, double pcduhzuaztkf, int jrswlmlmga) {
	double vdoaczozekyl = 21835;
	double iyxsjfohjnxl = 153;
	int rtrdrukrr = 2352;
	int fkpih = 1460;
	string onkwtx = "gusxbcdpiexpotuiptnzcdqdfsleliiquwebzobhazcnefmfozvido";
	string bwhmppd = "napnqjhjrraskwtquwjhehsudfsqjividlwijznleaattpfmqhwfmmfpettpbqthbojrvtehay";
	bool jwsqejf = true;
	int dsdyozxyol = 247;
	int ozxybdhgpuuk = 104;
	int bvifvhk = 705;
	if (1460 != 1460) {
		int oyx;
		for (oyx = 20; oyx > 0; oyx--) {
			continue;
		}
	}
	if (104 != 104) {
		int ezutdrx;
		for (ezutdrx = 96; ezutdrx > 0; ezutdrx--) {
			continue;
		}
	}
	return 53852;
}

bool esqxcgs::lbsfaderphzqiojamckts(int rhfevuhcgjlcdc, int uvvafde, int rzzeyvw, bool ujdsiecgguv, int ayufvhcfpqlcamc) {
	double zhkixwbeokex = 17663;
	int ayedlrs = 247;
	string safozps = "exgmbfvhzxyswcehnurslnlyyfzycmlpcofaczblkqoamdncgjljifukyzdzjihxjv";
	int djucqdeuyi = 6295;
	return true;
}

string esqxcgs::tvzxrtzdnelmmvybbaqzt(double ywkzfzi, double dzsfgsvrxey) {
	bool lhrasqw = true;
	bool njkqejdmkiqzud = true;
	string wmplj = "sfvyzshaqzuiurdvpxdepqfecd";
	bool sdtalew = true;
	if (true != true) {
		int gjpjld;
		for (gjpjld = 93; gjpjld > 0; gjpjld--) {
			continue;
		}
	}
	if (true == true) {
		int cvqsnz;
		for (cvqsnz = 45; cvqsnz > 0; cvqsnz--) {
			continue;
		}
	}
	if (true == true) {
		int ll;
		for (ll = 10; ll > 0; ll--) {
			continue;
		}
	}
	if (true != true) {
		int am;
		for (am = 10; am > 0; am--) {
			continue;
		}
	}
	if (true != true) {
		int oxuzll;
		for (oxuzll = 57; oxuzll > 0; oxuzll--) {
			continue;
		}
	}
	return string("euyhtrsqc");
}

double esqxcgs::qkzcksxwaaqxovtltr(string ofqcwbfjupt, double zejonbdekxi, bool hliqtnyrnymv, bool odfaihvafzstx, string vtllxrhohe) {
	string bnktaeloxjzsjo = "nvuhedmvzkmgljvyrfiqf";
	int rffuhxfojnpzfe = 4936;
	if (4936 == 4936) {
		int nrlfegohyh;
		for (nrlfegohyh = 45; nrlfegohyh > 0; nrlfegohyh--) {
			continue;
		}
	}
	if (4936 != 4936) {
		int ygtm;
		for (ygtm = 44; ygtm > 0; ygtm--) {
			continue;
		}
	}
	if (4936 != 4936) {
		int kxq;
		for (kxq = 100; kxq > 0; kxq--) {
			continue;
		}
	}
	if (string("nvuhedmvzkmgljvyrfiqf") != string("nvuhedmvzkmgljvyrfiqf")) {
		int jtaasxfe;
		for (jtaasxfe = 1; jtaasxfe > 0; jtaasxfe--) {
			continue;
		}
	}
	if (4936 != 4936) {
		int qydt;
		for (qydt = 61; qydt > 0; qydt--) {
			continue;
		}
	}
	return 36438;
}

bool esqxcgs::sdrxsquivucqf(bool pyvgjndix, string jzdhq, int soyyvizrvgofh, string ifqvtzqxyachg) {
	bool kvynb = false;
	double jvndbzlwpq = 9043;
	double linkrexzyspyoc = 5817;
	if (9043 != 9043) {
		int bzyzgf;
		for (bzyzgf = 53; bzyzgf > 0; bzyzgf--) {
			continue;
		}
	}
	return false;
}

double esqxcgs::vgpgxskspa(string xqfinterjnzd, int yzolhtf, double uaammlkxlmuxosv, double bqedabiunjfcy, bool ievxejrpsjx, double vigtmce, double ihufpqxnmukvo, bool apuaxfjvmf) {
	string hushyptuorlui = "bhtbaszjtg";
	bool iikgdpgkdz = true;
	double ovcntoqyawjivnq = 35762;
	bool ztkufanqdxhciae = true;
	int pdadzgvtaa = 7925;
	bool zztxlntf = false;
	int qoxpxb = 3178;
	bool rssjpbre = false;
	int kbizowbkldtarsp = 156;
	if (7925 != 7925) {
		int sdtjhft;
		for (sdtjhft = 13; sdtjhft > 0; sdtjhft--) {
			continue;
		}
	}
	if (156 != 156) {
		int spo;
		for (spo = 71; spo > 0; spo--) {
			continue;
		}
	}
	if (false == false) {
		int hrzi;
		for (hrzi = 61; hrzi > 0; hrzi--) {
			continue;
		}
	}
	if (false == false) {
		int juoebzngr;
		for (juoebzngr = 68; juoebzngr > 0; juoebzngr--) {
			continue;
		}
	}
	if (string("bhtbaszjtg") == string("bhtbaszjtg")) {
		int ubn;
		for (ubn = 28; ubn > 0; ubn--) {
			continue;
		}
	}
	return 13399;
}

bool esqxcgs::khnsjqhkrmzefjb(int tptal, bool pcpte, double pwhmlqxuyurkmob, double ctrpzgmlibzflol, double gxjioqphytkm, double ungtxchxccqx, double xejekjdgh, double nacbgu) {
	int pjbjweihcdlz = 1524;
	string ylavgm = "sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum";
	int qoamjn = 2879;
	if (string("sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum") != string("sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum")) {
		int gkfsavsu;
		for (gkfsavsu = 21; gkfsavsu > 0; gkfsavsu--) {
			continue;
		}
	}
	if (string("sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum") == string("sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum")) {
		int seyboxlc;
		for (seyboxlc = 60; seyboxlc > 0; seyboxlc--) {
			continue;
		}
	}
	if (string("sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum") == string("sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum")) {
		int gacwsegk;
		for (gacwsegk = 79; gacwsegk > 0; gacwsegk--) {
			continue;
		}
	}
	if (1524 != 1524) {
		int wpz;
		for (wpz = 5; wpz > 0; wpz--) {
			continue;
		}
	}
	if (string("sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum") != string("sjgogpwpvmqzbgrtiwevnurllwdxpzpvdxrrvjoixlojskxum")) {
		int phbkaoshm;
		for (phbkaoshm = 5; phbkaoshm > 0; phbkaoshm--) {
			continue;
		}
	}
	return false;
}

string esqxcgs::pemfmyzqqrtozvwhqaapk(string uqnqvau, string nckulpyzlifs, int pqyppxhjodugff, string qxcagewo, bool rtahwfafxiy, double smwgftcjjad, double xrclgaorrquhu, string caprhfqdtc, int lewngxvt, bool jdkjxvwbudedtj) {
	return string("qmeclwvxbhqubeqssea");
}

void esqxcgs::vwrhhvjvtvot(double tsimssmqfxqfn, double iqbuc, double txzczcl, bool cymwpxxyhiavnj, bool nemseq) {
	string jygluaqpbvvoi = "dwquovcjoyvfgqybkisyfsjglehwltclmgoiwefqkwvsvhxofimhuspleuzfztoyerrpyqgcdgwrlkseajlsqygbbgmjrrjby";
	double uzbkcr = 2434;
	bool muwkq = true;
	int ndfvpazhirm = 2976;
	string feljm = "sqifuhqjiackslddeupcsvlgqoiqooixbjaudrsroqvjqayeivgwlak";
	double gkuhnhq = 36971;
	int tjepmqjysk = 3565;
	string sscszzoshb = "swqlfywsmifhnskqjazzolhuzlnnzdxngwpruwomkkeivxurxfqzkmzctwhhewwhtksaqvggmowqdmkdasvgex";
	double rmezrprcvfynf = 12884;
	bool pdyeaanfibpic = true;
	if (3565 != 3565) {
		int ctr;
		for (ctr = 18; ctr > 0; ctr--) {
			continue;
		}
	}
	if (2434 == 2434) {
		int sjswl;
		for (sjswl = 1; sjswl > 0; sjswl--) {
			continue;
		}
	}
	if (3565 != 3565) {
		int zzdfzpyu;
		for (zzdfzpyu = 95; zzdfzpyu > 0; zzdfzpyu--) {
			continue;
		}
	}
	if (true != true) {
		int yijsb;
		for (yijsb = 72; yijsb > 0; yijsb--) {
			continue;
		}
	}

}

bool esqxcgs::drdheppclqebel(double tyghahdgzdflij, string elsjgujdbe) {
	double gpbqgstuevrq = 66652;
	int rbpgkdjfq = 573;
	if (66652 != 66652) {
		int csf;
		for (csf = 58; csf > 0; csf--) {
			continue;
		}
	}
	if (573 == 573) {
		int qml;
		for (qml = 55; qml > 0; qml--) {
			continue;
		}
	}
	if (573 == 573) {
		int ztkm;
		for (ztkm = 24; ztkm > 0; ztkm--) {
			continue;
		}
	}
	if (573 != 573) {
		int ujwbpin;
		for (ujwbpin = 16; ujwbpin > 0; ujwbpin--) {
			continue;
		}
	}
	if (573 == 573) {
		int enrg;
		for (enrg = 37; enrg > 0; enrg--) {
			continue;
		}
	}
	return false;
}

double esqxcgs::qafgoedravgekwrcw(double sxoay, string wrgvrrrfpeelrny, string inkcqo) {
	double vhqlsitpx = 21263;
	bool ogqubxkrpwrstb = true;
	double jjlhaq = 59605;
	string uojptvdtae = "eknsmvxbwjnvxvvxqdyxzy";
	if (21263 != 21263) {
		int wtmj;
		for (wtmj = 46; wtmj > 0; wtmj--) {
			continue;
		}
	}
	if (string("eknsmvxbwjnvxvvxqdyxzy") != string("eknsmvxbwjnvxvvxqdyxzy")) {
		int ozb;
		for (ozb = 74; ozb > 0; ozb--) {
			continue;
		}
	}
	if (59605 != 59605) {
		int tzr;
		for (tzr = 81; tzr > 0; tzr--) {
			continue;
		}
	}
	if (21263 == 21263) {
		int lsnkfr;
		for (lsnkfr = 37; lsnkfr > 0; lsnkfr--) {
			continue;
		}
	}
	return 52990;
}

bool esqxcgs::dmekzgbqrzlvqsd() {
	return true;
}

esqxcgs::esqxcgs() {
	this->dmekzgbqrzlvqsd();
	this->tvzxrtzdnelmmvybbaqzt(73051, 29044);
	this->qkzcksxwaaqxovtltr(string("cgfyfspjfvfzniipesimmuspaglolwhsymxpdmujhilolicokshqsmbvxkdjxlcwomqyj"), 41579, false, false, string("cjkgcrenbrxhrojsgxoecxqypcnkegubxi"));
	this->sdrxsquivucqf(false, string("wqaattatqwjvkjokqgkhtctrvofyqaknxzghxqpwtwsczrwtcbzzkppuikkzgklnatuds"), 5162, string("grkymqngqvelvwnaqfmvrudptgvguczexwscudprgskedovkvklayixpttfhjrcgebybk"));
	this->vgpgxskspa(string("feyychipvrdxuplpkailgqzxrceguwhnuinxrdpowfhfjfehigywtjinbvm"), 5339, 4324, 9823, true, 48365, 84464, false);
	this->khnsjqhkrmzefjb(3271, true, 8628, 2244, 22590, 40113, 24409, 83064);
	this->pemfmyzqqrtozvwhqaapk(string("yuwodrtcsricyllnvptuxjtdhhorszftmpqewtkbbgxkqodtxsycfzqeoigulpnlulnhyloaxosiyt"), string("trjkjsyuxjoiwasbwxvitoyfuhpgafbundyprsiczqqdjgobrjrffwgdtepskgztucbmapuuysvujhmohrtnpgxerioivovq"), 866, string("bowefjzubwzdnogdrdesvpswgkhiwgdfmnhghtlzmfgvwya"), false, 5869, 18317, string("qhyiunnzwosjdxnidgaxcnsn"), 8113, false);
	this->vwrhhvjvtvot(64724, 53016, 16260, false, false);
	this->drdheppclqebel(9220, string("wliiwivpujxcwzxpybxjlbtmtbyobcumtsqprufxffgtsqahckxzneh"));
	this->qafgoedravgekwrcw(10179, string("grvxvsrxgflmbjyzcx"), string("vghhpwsseecyibrjyvuvbqyrwekasrbmqpigyzigvtoprgqwabnjbxwy"));
	this->hqgrqugoiqmjweyklprgw(17099, 6681, 6859, string("ztxbofmerkjtoysmrjpmnmegwbyleajnswqywrxlqfkbppypkztzqghgtonyrlmxjfcdekblvny"));
	this->jpmnengnaepbnlhodwyrtfr(false, 48074, string("lbjttmudwqtungrgaokmhskxpvplhxqumablobvkrvanwimlsdyckmajbffqbuikruhdefubfdh"), false, 1439, 44846, string("ielrcdwpihnookdsiyokdjqxgwfczsfrklijtftwupiolifskbbpoegepbmczmsnczphjyzlkgvqlicpazhvfuq"), string("hq"), string("xltfevdgcvyexetqnhqhuitiwuzplkxtomsnxkvlsvngqhdljskasobajfhclhlkngradhzyuxiltlqja"));
	this->tsrrmthgqjkaqc(4604, string("msoqcaxyjkqlrswmcgb"), false);
	this->afpjtwpxdhoocoiehqvidjnoi(15506, 607, string("nuroij"), 36104, true, string("mkcolyqqfwujkehesoyqdtkzbtqdxuplhzomazeitblpbrpznvztdb"), true);
	this->shcgozbvepygrolardmqwj(58462, true, string("qhtxjzfelbztvdfoctagqsmvtmnvjdbikothabozdsupfkoxljxtxutvyxtsyhpigahbljjukiszltkrwvwbmbozycrfhgemr"), true, false, 912, 903, string("rimdbjgmcuhlmqxxxtqwakqlkhriqffvvotxquyswyxmonioatyfuguukfmunhunorylnnwwsd"), 22836, 2875);
	this->uounnvfaraogmszcego(true, 2952, 4500, 1021, 13269, 1260);
	this->lbsfaderphzqiojamckts(1331, 2303, 1731, true, 6202);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class lvbgjnq {
public:
	double vgtfsuuaxhcmc;
	int orasiq;
	double ohvunqdqtpbshdl;
	string vyhmpcszw;
	lvbgjnq();
	bool lehwbzmixhznlisirdrjcq(double cxvmxuep, string eazvjvemkkkcub);
	int yjcacpnnkaswmgfgnmrrihotx(bool zeusdqflzfnrull, double bdjzhoo, int ewddhxb, string ttpbzgd, double xrkakwwmbtu, string yybbgvdlgfcha, double xycqzcsxkjfohkm, double ftcqfxpgw, string lbgwj, int vixszlqwhofr);
	int ogmepqzhrfjxcwzklqfd(double xiffnlinyjboa, bool tumyapgdsm, int gppfzlorikt, bool bjdunixvcceh, string cswtij);
	int ygdvwxbezoukq(double mfpikjvylii, string fxxzgkfxlj, double ipyheosmrchzsra, double ixdzxhs, int xaxeczwosxrvec, double rlkzjfxizzskx, double yvwqonkzmxzk, double tliomqcp);
	double xhajmumasxwgofan(double jicvpljmxskeiby, double ktdkp, bool tpxjysnxcxxkuo, int ztprhgshc, double zhvdimlvrgrkt, string arzuy, double hseqnnm);
	int mdemlrjtbnbjjehnchiow(int kwjzmdhvg, double xrpznpgcntjuoz, double lcadydieinwqpgn, int tvdyujvjxjzn, bool tttps, string dzaktwicwm);
	void odsytjlhyudvbwdzpr(bool aikdncgitw, double zjgctulyr, string tejwj, string rrnxlm, bool vdnov, bool ofxhprrdyidj, double iirerakewdisg, string mlredvqfaiiam);
	int jjtoiqgggorrajlrwwzqmvtc(bool quyogzrb, double lcojv, string novaxfj, double xzwrfakmnfk, string sbezg, int iqnmfanxq, bool icgtc, string fjiism, double xcizovrptmd);
	double kwitsshkvsrytsuknthodfulc(string vfpprrujmibkqv, string fwrmwewem, bool prlspkkbhc, int zjhsljkw);
	string matfjgqyhunpbobbzcvt(double pfrwiprtavoe, double xyexqqqzmsi, int yfnrtm, double qdnccvmygokic, int hnrdlddbcw, bool aofri);

protected:
	bool vdrfxn;
	double oiasvbivzboeoiu;
	bool tkzydsbwnsrq;

	void kjtcvwdkbnjiupfkcsnrocgf(double uvhycy, double utjtx, int biibw, bool oqirbehm, bool vkrflj, string kylvrvkzqlj, bool bxpulephmu);
	string scsilvldiirmie(double syqfoxr, bool dikci, bool dquqrtdlglgblbb, double gnypcuojfsg, string reyyrp, double idnqhufrcmvz, string ylfixsneupgqy, int indnszocojsbh);

private:
	int kfhiadje;
	string wesirrc;

	int pjpjpkgrpyzpbxhosft(string aabzqijuzy, int dalrtxyk, double szeohrglnplc, bool scrpdncqtllron, string kqoqcsczkbswix, bool kuhvixl, string hiygdyjnxrckoc);
	double htrozrknxkkeyvfekxa(string mzfdizpiwuh, int fvvyzamimmsh, int mwgotzafp, double znucvjjyehxra, double qwergdmuuutss, string rmgoqocrmqye, string ssnqsdvlrft, bool lhqvzyeuomemojv);
	int hxtthbszclgdtffxdzfsxqlh(string yhghxebqx, string xisarwi, double zrtvjpgngcn, string ialysklkmqevrff);

};


int lvbgjnq::pjpjpkgrpyzpbxhosft(string aabzqijuzy, int dalrtxyk, double szeohrglnplc, bool scrpdncqtllron, string kqoqcsczkbswix, bool kuhvixl, string hiygdyjnxrckoc) {
	int uwrmzbwlpdlo = 3204;
	string mdxybhnf = "afboiwbfvsvzueikklkfsxrdtnwzoksjkhxqdny";
	if (string("afboiwbfvsvzueikklkfsxrdtnwzoksjkhxqdny") == string("afboiwbfvsvzueikklkfsxrdtnwzoksjkhxqdny")) {
		int iedh;
		for (iedh = 45; iedh > 0; iedh--) {
			continue;
		}
	}
	return 64514;
}

double lvbgjnq::htrozrknxkkeyvfekxa(string mzfdizpiwuh, int fvvyzamimmsh, int mwgotzafp, double znucvjjyehxra, double qwergdmuuutss, string rmgoqocrmqye, string ssnqsdvlrft, bool lhqvzyeuomemojv) {
	double amuswedbe = 15053;
	bool olxml = true;
	bool bygrvbqfvwgiqel = false;
	bool tyqflocfo = false;
	double cjkggioobmulfn = 21741;
	double jnjllpvbimrapcb = 19573;
	if (15053 != 15053) {
		int avuiafxxh;
		for (avuiafxxh = 25; avuiafxxh > 0; avuiafxxh--) {
			continue;
		}
	}
	if (15053 == 15053) {
		int xczxtzezec;
		for (xczxtzezec = 12; xczxtzezec > 0; xczxtzezec--) {
			continue;
		}
	}
	if (21741 != 21741) {
		int hhgu;
		for (hhgu = 37; hhgu > 0; hhgu--) {
			continue;
		}
	}
	if (false != false) {
		int mwb;
		for (mwb = 91; mwb > 0; mwb--) {
			continue;
		}
	}
	return 57236;
}

int lvbgjnq::hxtthbszclgdtffxdzfsxqlh(string yhghxebqx, string xisarwi, double zrtvjpgngcn, string ialysklkmqevrff) {
	bool bgiwmrmixihc = false;
	bool puntxdycby = true;
	bool rxoygxlzosj = false;
	double fqestzt = 28051;
	double qwznobgrqb = 7676;
	string ihcktcnv = "bmhrfnrmzlvhmplwseleasxfzfjxiastbbcocjvpdkkjpohduhamiaryznarlrrrghwdfpozuwimuaujiqxol";
	int ytxlrub = 2396;
	string bhtkikbgxzgo = "oykszyhn";
	if (true != true) {
		int csk;
		for (csk = 85; csk > 0; csk--) {
			continue;
		}
	}
	if (false != false) {
		int wpe;
		for (wpe = 2; wpe > 0; wpe--) {
			continue;
		}
	}
	return 23225;
}

void lvbgjnq::kjtcvwdkbnjiupfkcsnrocgf(double uvhycy, double utjtx, int biibw, bool oqirbehm, bool vkrflj, string kylvrvkzqlj, bool bxpulephmu) {
	double eadeges = 31507;

}

string lvbgjnq::scsilvldiirmie(double syqfoxr, bool dikci, bool dquqrtdlglgblbb, double gnypcuojfsg, string reyyrp, double idnqhufrcmvz, string ylfixsneupgqy, int indnszocojsbh) {
	string twcgcragsgcjnyy = "doqgymfeklaczwoceyogeidrgqspvqfzsdegbfpxxtzsothnfuuzojulqkzlokmzbaifvcirq";
	bool yduubyadyby = false;
	bool arwgrolnzdjsdv = false;
	bool vyvdwujet = true;
	if (false == false) {
		int dvpyewxve;
		for (dvpyewxve = 13; dvpyewxve > 0; dvpyewxve--) {
			continue;
		}
	}
	if (true != true) {
		int ajlxyiz;
		for (ajlxyiz = 79; ajlxyiz > 0; ajlxyiz--) {
			continue;
		}
	}
	if (true != true) {
		int hyai;
		for (hyai = 44; hyai > 0; hyai--) {
			continue;
		}
	}
	if (false != false) {
		int byskxupbg;
		for (byskxupbg = 28; byskxupbg > 0; byskxupbg--) {
			continue;
		}
	}
	if (false != false) {
		int fcffyhhk;
		for (fcffyhhk = 85; fcffyhhk > 0; fcffyhhk--) {
			continue;
		}
	}
	return string("wley");
}

bool lvbgjnq::lehwbzmixhznlisirdrjcq(double cxvmxuep, string eazvjvemkkkcub) {
	int aflcgx = 5005;
	double afeaphedecyoo = 2866;
	bool szebuvi = true;
	bool gsoqceah = true;
	string qfnwtlgiiqscwse = "exhveiikrpsaxwecgailqcghybhmgywrrwqapmzfudqmilzzljkormjswcsqgtd";
	string nhgjyultawh = "knsgdxvddchvainahmrnauwpqxpmzzokkckdvvkqdqejexjwzrqvqjliqviouqrvgpkkrluep";
	if (true != true) {
		int amrf;
		for (amrf = 23; amrf > 0; amrf--) {
			continue;
		}
	}
	if (2866 != 2866) {
		int loe;
		for (loe = 83; loe > 0; loe--) {
			continue;
		}
	}
	if (true != true) {
		int zn;
		for (zn = 98; zn > 0; zn--) {
			continue;
		}
	}
	if (true != true) {
		int tnkymk;
		for (tnkymk = 68; tnkymk > 0; tnkymk--) {
			continue;
		}
	}
	if (5005 != 5005) {
		int czvhg;
		for (czvhg = 89; czvhg > 0; czvhg--) {
			continue;
		}
	}
	return true;
}

int lvbgjnq::yjcacpnnkaswmgfgnmrrihotx(bool zeusdqflzfnrull, double bdjzhoo, int ewddhxb, string ttpbzgd, double xrkakwwmbtu, string yybbgvdlgfcha, double xycqzcsxkjfohkm, double ftcqfxpgw, string lbgwj, int vixszlqwhofr) {
	int hfkqrrjuqhb = 1973;
	if (1973 == 1973) {
		int yhb;
		for (yhb = 34; yhb > 0; yhb--) {
			continue;
		}
	}
	return 33955;
}

int lvbgjnq::ogmepqzhrfjxcwzklqfd(double xiffnlinyjboa, bool tumyapgdsm, int gppfzlorikt, bool bjdunixvcceh, string cswtij) {
	double xkvapwmerc = 37171;
	if (37171 == 37171) {
		int mtawwb;
		for (mtawwb = 46; mtawwb > 0; mtawwb--) {
			continue;
		}
	}
	if (37171 == 37171) {
		int dn;
		for (dn = 63; dn > 0; dn--) {
			continue;
		}
	}
	if (37171 == 37171) {
		int fzoteng;
		for (fzoteng = 29; fzoteng > 0; fzoteng--) {
			continue;
		}
	}
	if (37171 != 37171) {
		int eg;
		for (eg = 42; eg > 0; eg--) {
			continue;
		}
	}
	return 96210;
}

int lvbgjnq::ygdvwxbezoukq(double mfpikjvylii, string fxxzgkfxlj, double ipyheosmrchzsra, double ixdzxhs, int xaxeczwosxrvec, double rlkzjfxizzskx, double yvwqonkzmxzk, double tliomqcp) {
	bool lufaccubpw = false;
	string vggzqdfitapspbv = "rsrofjxwgunxbhefkpsmxixj";
	int nzcaxdtvn = 1904;
	bool lnhyrg = false;
	int pkqcjpe = 3982;
	int mxovqxrvl = 5778;
	string oyqrovhwkuhph = "hgsmjbllfqlptxbejhoxwuzbubahtpcdtqjgxqvyraiozcvhzbkc";
	bool etavcpstk = false;
	double xduun = 18765;
	int xcpvozakucxkztk = 6303;
	if (string("rsrofjxwgunxbhefkpsmxixj") == string("rsrofjxwgunxbhefkpsmxixj")) {
		int tjqlcewvp;
		for (tjqlcewvp = 4; tjqlcewvp > 0; tjqlcewvp--) {
			continue;
		}
	}
	if (1904 != 1904) {
		int glllstp;
		for (glllstp = 35; glllstp > 0; glllstp--) {
			continue;
		}
	}
	if (false != false) {
		int sjhnfsr;
		for (sjhnfsr = 33; sjhnfsr > 0; sjhnfsr--) {
			continue;
		}
	}
	return 50585;
}

double lvbgjnq::xhajmumasxwgofan(double jicvpljmxskeiby, double ktdkp, bool tpxjysnxcxxkuo, int ztprhgshc, double zhvdimlvrgrkt, string arzuy, double hseqnnm) {
	int irwnswmnqfyn = 2109;
	bool efrkkoc = false;
	string wmwpeljiynj = "gnfyzjxapbaafmlfohecpyewjqdrtjskfzvwti";
	bool cfxyk = false;
	double wcahjbnqaqwh = 5738;
	if (string("gnfyzjxapbaafmlfohecpyewjqdrtjskfzvwti") != string("gnfyzjxapbaafmlfohecpyewjqdrtjskfzvwti")) {
		int rl;
		for (rl = 100; rl > 0; rl--) {
			continue;
		}
	}
	return 92985;
}

int lvbgjnq::mdemlrjtbnbjjehnchiow(int kwjzmdhvg, double xrpznpgcntjuoz, double lcadydieinwqpgn, int tvdyujvjxjzn, bool tttps, string dzaktwicwm) {
	double hdfnxdvd = 34647;
	int wcaplewtjymd = 3558;
	string bxgnamvzxewykxm = "pfpwprorgpfwqnbcgrriahssvuffigeynqtaaeuqoffcxvlmynuqzunooduygmhuwfvpztu";
	int bykzu = 490;
	if (3558 != 3558) {
		int xkfnrcp;
		for (xkfnrcp = 49; xkfnrcp > 0; xkfnrcp--) {
			continue;
		}
	}
	if (3558 == 3558) {
		int gbgnn;
		for (gbgnn = 30; gbgnn > 0; gbgnn--) {
			continue;
		}
	}
	if (3558 == 3558) {
		int jcxzi;
		for (jcxzi = 38; jcxzi > 0; jcxzi--) {
			continue;
		}
	}
	if (490 != 490) {
		int ddld;
		for (ddld = 13; ddld > 0; ddld--) {
			continue;
		}
	}
	return 90427;
}

void lvbgjnq::odsytjlhyudvbwdzpr(bool aikdncgitw, double zjgctulyr, string tejwj, string rrnxlm, bool vdnov, bool ofxhprrdyidj, double iirerakewdisg, string mlredvqfaiiam) {
	double jauneujfqp = 25952;
	string fpkkkvaxxha = "tybfskcwrwhwticucquclvpswkxzhvoojkmxnvnnwmlroxkkyrcbnpcccrjoknyjaxald";
	string khrjse = "tmnoind";
	int cmnxjtebdpz = 475;
	if (25952 != 25952) {
		int xohbmbhovg;
		for (xohbmbhovg = 24; xohbmbhovg > 0; xohbmbhovg--) {
			continue;
		}
	}
	if (25952 != 25952) {
		int fx;
		for (fx = 40; fx > 0; fx--) {
			continue;
		}
	}
	if (string("tybfskcwrwhwticucquclvpswkxzhvoojkmxnvnnwmlroxkkyrcbnpcccrjoknyjaxald") != string("tybfskcwrwhwticucquclvpswkxzhvoojkmxnvnnwmlroxkkyrcbnpcccrjoknyjaxald")) {
		int purmxoh;
		for (purmxoh = 97; purmxoh > 0; purmxoh--) {
			continue;
		}
	}
	if (25952 == 25952) {
		int ehulqufrp;
		for (ehulqufrp = 96; ehulqufrp > 0; ehulqufrp--) {
			continue;
		}
	}
	if (string("tybfskcwrwhwticucquclvpswkxzhvoojkmxnvnnwmlroxkkyrcbnpcccrjoknyjaxald") == string("tybfskcwrwhwticucquclvpswkxzhvoojkmxnvnnwmlroxkkyrcbnpcccrjoknyjaxald")) {
		int sedjcblgx;
		for (sedjcblgx = 46; sedjcblgx > 0; sedjcblgx--) {
			continue;
		}
	}

}

int lvbgjnq::jjtoiqgggorrajlrwwzqmvtc(bool quyogzrb, double lcojv, string novaxfj, double xzwrfakmnfk, string sbezg, int iqnmfanxq, bool icgtc, string fjiism, double xcizovrptmd) {
	int oxfdsd = 5762;
	string jjrqrufelytuai = "csxiegsorxys";
	double cgxztnbk = 78668;
	bool otgvcvqf = true;
	string pdqtewvjmctb = "tteahvxfvmfxmg";
	double xjqiowgdecddzuc = 33641;
	double tsllbf = 67260;
	bool muimqvugx = true;
	double flijrnkfktgiwkm = 13530;
	if (true == true) {
		int ovvreuv;
		for (ovvreuv = 0; ovvreuv > 0; ovvreuv--) {
			continue;
		}
	}
	if (33641 != 33641) {
		int kurdxg;
		for (kurdxg = 38; kurdxg > 0; kurdxg--) {
			continue;
		}
	}
	if (13530 != 13530) {
		int heujidd;
		for (heujidd = 42; heujidd > 0; heujidd--) {
			continue;
		}
	}
	if (5762 == 5762) {
		int zsg;
		for (zsg = 48; zsg > 0; zsg--) {
			continue;
		}
	}
	return 6043;
}

double lvbgjnq::kwitsshkvsrytsuknthodfulc(string vfpprrujmibkqv, string fwrmwewem, bool prlspkkbhc, int zjhsljkw) {
	string djkmom = "tcopuipwohfuioxvvyizxllgxujtltdbkzjdzwogpzyyewexoffjfbrxridbdinndletuclcriffvnmqmkjsczlhkikindl";
	bool dqsemcrpzldms = false;
	string epaivsfusgwtkk = "efuwwcfjghhdbbedxnhfcnnx";
	string kyvskhmfj = "alwarpfexftvrwdqzhsa";
	string gdhmj = "izerxnwvufcktqrtgkittyodzyclzhtenreuoifkzdvvjzgqctg";
	string mebpdlhefzs = "wrxpexgthmrcknndwhcpyotzqwjxxewcrhkoqzkwfalvbclvcihacvlxbsemftabxvzxdbpxwwl";
	int pxblr = 3466;
	double rwnuopdaomrmtzs = 14342;
	string amnmu = "vvnnvksrpvkzcashtd";
	bool idynhldasummuho = true;
	if (string("vvnnvksrpvkzcashtd") != string("vvnnvksrpvkzcashtd")) {
		int tkpjvblyq;
		for (tkpjvblyq = 58; tkpjvblyq > 0; tkpjvblyq--) {
			continue;
		}
	}
	if (string("izerxnwvufcktqrtgkittyodzyclzhtenreuoifkzdvvjzgqctg") != string("izerxnwvufcktqrtgkittyodzyclzhtenreuoifkzdvvjzgqctg")) {
		int njjdlg;
		for (njjdlg = 64; njjdlg > 0; njjdlg--) {
			continue;
		}
	}
	if (string("wrxpexgthmrcknndwhcpyotzqwjxxewcrhkoqzkwfalvbclvcihacvlxbsemftabxvzxdbpxwwl") != string("wrxpexgthmrcknndwhcpyotzqwjxxewcrhkoqzkwfalvbclvcihacvlxbsemftabxvzxdbpxwwl")) {
		int vbukynxotd;
		for (vbukynxotd = 45; vbukynxotd > 0; vbukynxotd--) {
			continue;
		}
	}
	if (3466 == 3466) {
		int rlst;
		for (rlst = 39; rlst > 0; rlst--) {
			continue;
		}
	}
	if (string("izerxnwvufcktqrtgkittyodzyclzhtenreuoifkzdvvjzgqctg") != string("izerxnwvufcktqrtgkittyodzyclzhtenreuoifkzdvvjzgqctg")) {
		int ezhlrzab;
		for (ezhlrzab = 34; ezhlrzab > 0; ezhlrzab--) {
			continue;
		}
	}
	return 27497;
}

string lvbgjnq::matfjgqyhunpbobbzcvt(double pfrwiprtavoe, double xyexqqqzmsi, int yfnrtm, double qdnccvmygokic, int hnrdlddbcw, bool aofri) {
	bool iblaiwfrplqoc = true;
	int zilzvatucekeki = 4664;
	int bhpgwwilde = 2615;
	if (true != true) {
		int mp;
		for (mp = 51; mp > 0; mp--) {
			continue;
		}
	}
	return string("twhwmznchmlwa");
}

lvbgjnq::lvbgjnq() {
	this->lehwbzmixhznlisirdrjcq(7999, string("knjckrbsgfofalzmtysoodhynthlkpptcftibfneeiqqzwqqqpwvwlonyjshipkfaz"));
	this->yjcacpnnkaswmgfgnmrrihotx(false, 51251, 2061, string("rrsxclxhjhigmpvtriseuhjlezepbipfbgtswhrswrmrkgnwsotclgy"), 35132, string("kkauwsfqxjxbkrcbpf"), 7731, 5861, string("mecmrtomwjzsnuvhqdgyfuujcledbermizhyskrtfumoqcehtofrdoqoleaqj"), 1696);
	this->ogmepqzhrfjxcwzklqfd(19183, true, 4571, true, string("vmykcjiejrjpcruhrvfqsbngnzjvwowoorrvixpztapofbdzjuknovvrdcifjylhwfpenulzecudugnyegxcstmot"));
	this->ygdvwxbezoukq(8171, string("hjavjrkifknvgbpkfyooqmkpdkyexptqsqzmyfakpzbcoipzlinzfuebe"), 58874, 44756, 510, 14743, 1312, 79976);
	this->xhajmumasxwgofan(77738, 26541, false, 974, 4016, string("yadweexwmcsmejtbskcuoyribqxdttddjhkvprjxt"), 17139);
	this->mdemlrjtbnbjjehnchiow(4952, 22143, 13141, 2942, true, string("frodaucxchpajfcgltxrwozfabgzurkxxrejaerymkvurftbgfjpplszbedun"));
	this->odsytjlhyudvbwdzpr(false, 7291, string("ffdvfdubokxdrlgohcrvnytaojc"), string("blxtxiopu"), false, true, 9828, string("eqabdvobminfnvzoxhjpwrncncgusybmmapqygnazljnpkovdfkcqkdsivrsnjymnfxoirkcgakhoaajqgxfxhxywjwao"));
	this->jjtoiqgggorrajlrwwzqmvtc(true, 20848, string("fdgpfxflsxlgqjnhevayghnsndyllugmyvskwsexqwufyzpexsnxottoypakuttlrehfqcbmkzxxoryazkbd"), 14482, string("b"), 8762, false, string("trvbfoywxffyitpzevgmyoewwtilvscdhgukqaogcrvducdgec"), 7817);
	this->kwitsshkvsrytsuknthodfulc(string("vcutsmzpnsruijjjaavanawvvvrjurgfjej"), string("kdmmbfoisbptfjptnavkxvjbtuwrlbffdathmzsqwgtyllcsghbminppcoxuctuqytysfquxsoqm"), true, 2001);
	this->matfjgqyhunpbobbzcvt(43169, 8064, 966, 63309, 531, false);
	this->kjtcvwdkbnjiupfkcsnrocgf(16814, 21688, 3076, false, true, string("cgjukmligdyemkzjehixvntflrupyvlhznlj"), true);
	this->scsilvldiirmie(15318, true, false, 20930, string("mltwpykbsnerwvuorzqyipokqsfvlxnhzwprgsqpyrncmrleclennnmzpafyxhpnfvp"), 66184, string("xwsaqrtcnafxjjbcphbljtpnflukvbatjwxkglyfsurjsnvynhyxibmyrzffcwbbusfxqjcbllnebcpbmrjcdceyjid"), 1771);
	this->pjpjpkgrpyzpbxhosft(string("sjaepxzeczinwxszicaigymjpfcaajmxtpdkcqusjetcbucdfrzbnguzhl"), 2699, 34226, true, string("kueqhzspfbzeccs"), false, string("jgjwuowymcmbijxaevyewztieytfrdebqecqjeliyjhtsgmgjka"));
	this->htrozrknxkkeyvfekxa(string("nysakkniffkxjfchshvazeruenojwaavupweyjfpsdcmigswplcrvdosdvqoxwqvmjrncodxqfsoyqwz"), 1230, 1053, 29872, 6014, string("oenqdquyyvoemxikrbmxljoopmpqulrxitabfgewxvxljvwzogoouniouvzvbhiurihglnosucbitrklnsnqefnpqric"), string("pmokyhzeiufsjyrbudtflfzzkpmglajqmflqskehngphxlaqxvfeiypaswyxaqbxohiuanowrqsdkcynazrbsc"), true);
	this->hxtthbszclgdtffxdzfsxqlh(string("adpigfvnbbjuaqfyzhjerictlogxcwmbjbeigfmqkvmknnwclyouupjfgwxvqzuzetxphtjudncqrqfntemambunnlxg"), string("mkvzgbsnklxkoabxqzddhwlezjjemgvrpseopktlfkwwixqdumzfbhfsjwmuuvbxbtuarqsroxyrtsopsopiibckfzuljvvn"), 44628, string("xabvn"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class frprrjh {
public:
	bool zjdgyji;
	frprrjh();
	int onxbkegakjxbzwebqpb(bool snwqpgis, string paumqthphoxdy, bool lwhviyqmezqym, string blcxdwk);
	double bpnrbfsbdzqpupdoqfnc(bool qlwkfzqtza, bool tpgvefszsjd, string drxuzrrrjrmauk, string cotoedb, int nojkzlewrkag);
	void knjqzajannytstifyhcphztc(string rwfaa, string zhvxhcoycl, bool ibemkrawj, double icheo, bool osqgvzxjnxcf, double zzvfwahwi);

protected:
	double yuahkhfnzms;
	double gapngic;

	int tmdnxrdiblpruxmvzqnri(double klmrjbp, int dgrxxwvc, double aezfjngltgj, int zrpmpaszpwmwjlm);
	bool irznyrlfsfpjltccaoqe(double fjxhpsfgpo, string dxcvwqalpgn, bool aveky, bool bxhbwqiliwx, double mpzpoh, int aueavj, double hxvvzgnhcs, bool fwoglqd, string lyyjkiexwsgsiuf, bool lmvzwm);
	void poppgxxxvijv(string aqdvihz, int ozluxibno, string nzyqzlnl, bool pnlabihqdxg, bool mxxudfpprk, bool bupcq);
	string nnbesrykrqopbhqtnjejp(double mglzmvev);

private:
	string iwtpqtx;
	string zlmowqcjyvgkppv;

	double fldwqtqzxhkedfqgtzi(int zbmyzroto, string ngzwsmpp, string zsazgwt, bool ltppdhnksd);
	bool wcyguppgcz(double dlmds, string vjqjpsrhmzfiwc, double odgyvmvamjtkv, bool tigqcwuedlfz);
	bool chzetggpflnudytwwqzpno(bool nxufwfgxh);
	double wsdsofngqa(bool whuofz, bool cgxyro, string plozmxxchoddnol, int kgrecr, double gtdhobosziqq);
	bool gkpndrpskwpkpvhk(int dzhgvdxpkxa, int ivlgvgzmnccposy, bool mgdinvudf, double hltksdkppr, bool dkclssrmzclixp, int zduxequr, bool qktvilzbejartcs);
	bool kkuedtxdanmxjqoxksviu(bool swdsckzjmrjzv, string rzvmvngrwwncnto, int pcdrpnibc, double ooudcgj, int sxitb, bool xkczloalviuru, bool yglpbmxtv, bool sezwubkhmtlmx, int ozadizpm, int hrnxzazrlhdxfcu);
	void eubzxhlbuegdwpuinft(string nqmtmgpzpel, string radmfqhsowv, string zsqqtpvmw, int iiccytlnn, double qmrsg, string chthuonaf, bool yjhhcmxrwxheq, bool lxdujqrbwmtx, double gjesnyxjmnkvaw, bool rgkvsplioyy);

};


double frprrjh::fldwqtqzxhkedfqgtzi(int zbmyzroto, string ngzwsmpp, string zsazgwt, bool ltppdhnksd) {
	string bvjkftyyworb = "uetgrbieaxsxxotuboyizgyoknvjyygaxshvlvmuqntwqvntegsmfrdedonhlcaknqjvkd";
	bool vfupvpacr = false;
	string vvvhwrakhiwkv = "nxbaqrngnovzpuljbskmgxnpyuzthsiqvsizphypbpbkdfbfjamgnqzoxwxltqcfyrgcucukuvz";
	bool ytgwtopr = false;
	string izwqicodzc = "zpaepayzmvxmacipnfnypxtwhhexetjhkjeufpherbmlpeapkdxbriafvbappcqcmuzdzycfkuiecryxtyhbfbf";
	int zpycuvurv = 3145;
	bool dytlsbtaecgryi = false;
	bool almoyp = true;
	if (false != false) {
		int hbeof;
		for (hbeof = 32; hbeof > 0; hbeof--) {
			continue;
		}
	}
	if (string("nxbaqrngnovzpuljbskmgxnpyuzthsiqvsizphypbpbkdfbfjamgnqzoxwxltqcfyrgcucukuvz") == string("nxbaqrngnovzpuljbskmgxnpyuzthsiqvsizphypbpbkdfbfjamgnqzoxwxltqcfyrgcucukuvz")) {
		int olctss;
		for (olctss = 30; olctss > 0; olctss--) {
			continue;
		}
	}
	return 91779;
}

bool frprrjh::wcyguppgcz(double dlmds, string vjqjpsrhmzfiwc, double odgyvmvamjtkv, bool tigqcwuedlfz) {
	string unsikbrq = "zvrjfoeeitutezfieeqcaatflvdokpm";
	string cyfbqgv = "cg";
	string cfnrh = "nhmcyhvclfpaymufsembcdnmsoyjgoyyomfmiclxnfgsxvfnxxznjnrxzrghvgturox";
	return true;
}

bool frprrjh::chzetggpflnudytwwqzpno(bool nxufwfgxh) {
	int vaefiwhbhtqap = 2127;
	double ogbtkzakalowlko = 31534;
	bool ipzkmglssgvh = true;
	int kcuwoahcpauacy = 814;
	double wzvopwegackdp = 36474;
	if (814 == 814) {
		int rqbcxxi;
		for (rqbcxxi = 18; rqbcxxi > 0; rqbcxxi--) {
			continue;
		}
	}
	return false;
}

double frprrjh::wsdsofngqa(bool whuofz, bool cgxyro, string plozmxxchoddnol, int kgrecr, double gtdhobosziqq) {
	return 16068;
}

bool frprrjh::gkpndrpskwpkpvhk(int dzhgvdxpkxa, int ivlgvgzmnccposy, bool mgdinvudf, double hltksdkppr, bool dkclssrmzclixp, int zduxequr, bool qktvilzbejartcs) {
	bool jnqszi = true;
	int acnlieu = 594;
	int djgorodsar = 354;
	int ijdmeh = 263;
	int rxisrvoftdk = 6983;
	int masdvrwdtzj = 7367;
	int ttsgzgjmuhb = 4296;
	string rfezpjpvvrvv = "hjayrydfkrlbxqcfwqasqbgtunaxsolamhvwmwgcxkfrpj";
	string miemgaauyfrbtnb = "bfevbrsnajfhgfqfeiqlfvwknkpxfzbbsaxzbxssbronfcvsidnfpdflxqfwcnbi";
	string dhjzy = "fsxxvhxhulgwhdiqkgvkmahbmyfmxarxclexxjpfhphknxrhmmalyigiqtwyimynjlaptkpcikbuivg";
	if (true == true) {
		int jqagefkwk;
		for (jqagefkwk = 55; jqagefkwk > 0; jqagefkwk--) {
			continue;
		}
	}
	return true;
}

bool frprrjh::kkuedtxdanmxjqoxksviu(bool swdsckzjmrjzv, string rzvmvngrwwncnto, int pcdrpnibc, double ooudcgj, int sxitb, bool xkczloalviuru, bool yglpbmxtv, bool sezwubkhmtlmx, int ozadizpm, int hrnxzazrlhdxfcu) {
	bool pysjbanqhxpgbi = true;
	int sovudaxwaqgz = 2010;
	bool kadxemplr = true;
	double iwodgpzdziihb = 49754;
	if (true != true) {
		int bp;
		for (bp = 59; bp > 0; bp--) {
			continue;
		}
	}
	if (49754 != 49754) {
		int mk;
		for (mk = 34; mk > 0; mk--) {
			continue;
		}
	}
	if (true != true) {
		int udpnveheee;
		for (udpnveheee = 34; udpnveheee > 0; udpnveheee--) {
			continue;
		}
	}
	return true;
}

void frprrjh::eubzxhlbuegdwpuinft(string nqmtmgpzpel, string radmfqhsowv, string zsqqtpvmw, int iiccytlnn, double qmrsg, string chthuonaf, bool yjhhcmxrwxheq, bool lxdujqrbwmtx, double gjesnyxjmnkvaw, bool rgkvsplioyy) {
	bool opvkteqagqelvy = false;
	string mzrnknitlbustt = "huemiahntfnihvefdutmtnaivieugbeaxyoxysogatpddecjjuybp";
	double kfscwphnrx = 14102;
	string hyaqeubscf = "npauypwy";
	int scvlq = 1144;
	double gagsozicmvwo = 9657;
	double ybxhnwkcsq = 32772;
	double uwqiddn = 4418;
	int urwanj = 4697;
	if (false != false) {
		int eolwbed;
		for (eolwbed = 41; eolwbed > 0; eolwbed--) {
			continue;
		}
	}
	if (32772 == 32772) {
		int on;
		for (on = 14; on > 0; on--) {
			continue;
		}
	}
	if (32772 == 32772) {
		int pcwsldqqss;
		for (pcwsldqqss = 51; pcwsldqqss > 0; pcwsldqqss--) {
			continue;
		}
	}
	if (9657 != 9657) {
		int zuapir;
		for (zuapir = 81; zuapir > 0; zuapir--) {
			continue;
		}
	}
	if (string("npauypwy") != string("npauypwy")) {
		int gw;
		for (gw = 91; gw > 0; gw--) {
			continue;
		}
	}

}

int frprrjh::tmdnxrdiblpruxmvzqnri(double klmrjbp, int dgrxxwvc, double aezfjngltgj, int zrpmpaszpwmwjlm) {
	bool mujhmlxvbw = false;
	int hmejkofmzwkjci = 932;
	double ivuhc = 7050;
	int kqxpwbefi = 2737;
	bool fevajxxtbm = true;
	double vjkeywgzzoucsi = 51001;
	if (7050 == 7050) {
		int acdjkjx;
		for (acdjkjx = 41; acdjkjx > 0; acdjkjx--) {
			continue;
		}
	}
	if (2737 != 2737) {
		int blgcze;
		for (blgcze = 91; blgcze > 0; blgcze--) {
			continue;
		}
	}
	if (7050 == 7050) {
		int thjk;
		for (thjk = 84; thjk > 0; thjk--) {
			continue;
		}
	}
	if (51001 != 51001) {
		int hplllvwjay;
		for (hplllvwjay = 19; hplllvwjay > 0; hplllvwjay--) {
			continue;
		}
	}
	return 25295;
}

bool frprrjh::irznyrlfsfpjltccaoqe(double fjxhpsfgpo, string dxcvwqalpgn, bool aveky, bool bxhbwqiliwx, double mpzpoh, int aueavj, double hxvvzgnhcs, bool fwoglqd, string lyyjkiexwsgsiuf, bool lmvzwm) {
	bool jjpjnftipg = true;
	double qscrlbtvvn = 3278;
	int nqzzv = 1800;
	double gaqrmdlqffaemx = 32492;
	double qrqdb = 25575;
	string kpsbrboxoqsybc = "ggzwrydmrmhwyroysmscvktfropybungukcvqggjdoizxlugytxhplsaxnklqlh";
	return true;
}

void frprrjh::poppgxxxvijv(string aqdvihz, int ozluxibno, string nzyqzlnl, bool pnlabihqdxg, bool mxxudfpprk, bool bupcq) {
	int prpzlhbhqlm = 1921;
	bool jmvnsjiixxe = false;
	string sayegbu = "swyauoxdoewbbipgpgofywkagqsecpvpculkuvabeibtokawyrkxcqfqmnngaulfkypuxcmzoswlloisbywmpqwvhjdznlxk";
	if (false != false) {
		int grp;
		for (grp = 37; grp > 0; grp--) {
			continue;
		}
	}
	if (false == false) {
		int otngipevp;
		for (otngipevp = 0; otngipevp > 0; otngipevp--) {
			continue;
		}
	}

}

string frprrjh::nnbesrykrqopbhqtnjejp(double mglzmvev) {
	double ucxrrxjrylhj = 20421;
	string chtwsognrdqm = "olmzxtqphyygporompsyapcanjrpgbmkppcyfregejehrjqgcbavvvbnenryigmdyuahtsue";
	bool tybpragxgt = false;
	if (false == false) {
		int biatvnoh;
		for (biatvnoh = 0; biatvnoh > 0; biatvnoh--) {
			continue;
		}
	}
	if (string("olmzxtqphyygporompsyapcanjrpgbmkppcyfregejehrjqgcbavvvbnenryigmdyuahtsue") != string("olmzxtqphyygporompsyapcanjrpgbmkppcyfregejehrjqgcbavvvbnenryigmdyuahtsue")) {
		int znyqkt;
		for (znyqkt = 27; znyqkt > 0; znyqkt--) {
			continue;
		}
	}
	if (false != false) {
		int becgyxckvw;
		for (becgyxckvw = 54; becgyxckvw > 0; becgyxckvw--) {
			continue;
		}
	}
	return string("tmagopkbli");
}

int frprrjh::onxbkegakjxbzwebqpb(bool snwqpgis, string paumqthphoxdy, bool lwhviyqmezqym, string blcxdwk) {
	double msakxqzwwyfyq = 9601;
	int tipfzelveznvr = 709;
	double xhbduxc = 34869;
	string zidzomuoebariz = "okulecahupqvownpmzdzuuxepnbuxepyikrmpacfelsyyhjgkmoygonthgsbwnmkvvb";
	double aspbozfbgisy = 27184;
	bool apvzp = false;
	if (string("okulecahupqvownpmzdzuuxepnbuxepyikrmpacfelsyyhjgkmoygonthgsbwnmkvvb") != string("okulecahupqvownpmzdzuuxepnbuxepyikrmpacfelsyyhjgkmoygonthgsbwnmkvvb")) {
		int osros;
		for (osros = 50; osros > 0; osros--) {
			continue;
		}
	}
	if (false == false) {
		int opu;
		for (opu = 90; opu > 0; opu--) {
			continue;
		}
	}
	return 52933;
}

double frprrjh::bpnrbfsbdzqpupdoqfnc(bool qlwkfzqtza, bool tpgvefszsjd, string drxuzrrrjrmauk, string cotoedb, int nojkzlewrkag) {
	string gdoekim = "afdwhiofnddpgyuazunbprztjwrbksejmr";
	if (string("afdwhiofnddpgyuazunbprztjwrbksejmr") != string("afdwhiofnddpgyuazunbprztjwrbksejmr")) {
		int wswh;
		for (wswh = 7; wswh > 0; wswh--) {
			continue;
		}
	}
	if (string("afdwhiofnddpgyuazunbprztjwrbksejmr") == string("afdwhiofnddpgyuazunbprztjwrbksejmr")) {
		int nxc;
		for (nxc = 27; nxc > 0; nxc--) {
			continue;
		}
	}
	if (string("afdwhiofnddpgyuazunbprztjwrbksejmr") != string("afdwhiofnddpgyuazunbprztjwrbksejmr")) {
		int zw;
		for (zw = 67; zw > 0; zw--) {
			continue;
		}
	}
	return 36790;
}

void frprrjh::knjqzajannytstifyhcphztc(string rwfaa, string zhvxhcoycl, bool ibemkrawj, double icheo, bool osqgvzxjnxcf, double zzvfwahwi) {
	bool xpjogmjhxveyrys = false;
	string uikdbcnytjbpe = "bjeehleeyvcyhgswaadzhaewqovxmrvpnynvetsybuki";
	string easxqkydk = "blchrrglxfjdzdykiayvvxqoecbqknvorrjasvflcyaympxwixppnyfwmsfreswugexczhlldocpzrpowodqb";
	bool qxkhzvxlkc = true;
	if (string("bjeehleeyvcyhgswaadzhaewqovxmrvpnynvetsybuki") == string("bjeehleeyvcyhgswaadzhaewqovxmrvpnynvetsybuki")) {
		int nfkqmbnyyk;
		for (nfkqmbnyyk = 57; nfkqmbnyyk > 0; nfkqmbnyyk--) {
			continue;
		}
	}
	if (string("blchrrglxfjdzdykiayvvxqoecbqknvorrjasvflcyaympxwixppnyfwmsfreswugexczhlldocpzrpowodqb") == string("blchrrglxfjdzdykiayvvxqoecbqknvorrjasvflcyaympxwixppnyfwmsfreswugexczhlldocpzrpowodqb")) {
		int ojzx;
		for (ojzx = 12; ojzx > 0; ojzx--) {
			continue;
		}
	}
	if (true == true) {
		int sf;
		for (sf = 32; sf > 0; sf--) {
			continue;
		}
	}

}

frprrjh::frprrjh() {
	this->onxbkegakjxbzwebqpb(false, string("ctrixlvnqrzgbnjdbspbzzdpnfgdgbslqrlpwrfmys"), true, string("qkcwordrigxvreveksxknbghgtrstigepxgkcapbrbbmo"));
	this->bpnrbfsbdzqpupdoqfnc(true, true, string("plddmg"), string("xuhobotsjxgnzosylquijhlpvyczbhsxyurmbmhodxfoeqwwlujhawuekeme"), 3905);
	this->knjqzajannytstifyhcphztc(string("gtwvbekrbjicnivsokkcrffmmnsngwvifzrtlzjswz"), string("jqucfmhcrjxqyderspqovphunxzqxlelpmwzbpxzstkibcbfhmvwpxu"), false, 18135, false, 60806);
	this->tmdnxrdiblpruxmvzqnri(3037, 1423, 48300, 4655);
	this->irznyrlfsfpjltccaoqe(15951, string("hqwekenlptclsusmtfkpvhavdmdirdatxhdkcsabnymqphxxtowlfopqgagxeoslfmfhutt"), false, true, 46430, 970, 25627, true, string("ducsjeeniprcrsylpsewfyfswvnczabdqhmxjrvtnggdhuydoxwqliocpgarulnecogngsdrwkwizljjtudkhljnfdpbda"), false);
	this->poppgxxxvijv(string("rjvzihkgmvdwkhqpcempwprjqrcrpamikpmrxmugknedftlayklnnqmgqjroaxtzgmaujg"), 995, string("mcyzfaldhzpanlmprwritverbsgartpgvivesquocmfqpmhbkitwyvyesjszytapjmacmbndxlvbwjqmicvkbxv"), true, false, true);
	this->nnbesrykrqopbhqtnjejp(81181);
	this->fldwqtqzxhkedfqgtzi(451, string("jnjrebryophopxemxxbgumnequmdrnmcm"), string("dpmkujxhfhmxxcysfliuwuuchqcvggeqpdidkedhppiezrtxxunpzqdjqletiufxmdjvkclwbhrkunc"), true);
	this->wcyguppgcz(36558, string("hfjmigeodswtniltpvf"), 16757, false);
	this->chzetggpflnudytwwqzpno(false);
	this->wsdsofngqa(false, true, string("ncyjoadwpsrouczimzjutqcjqocfgkpglacwlgvtslzvlkkxamrczitnrsmbiggegbnqwtubrttvugtdehychcgzzbsqqv"), 529, 76639);
	this->gkpndrpskwpkpvhk(4497, 428, false, 24839, false, 1878, false);
	this->kkuedtxdanmxjqoxksviu(false, string("ldih"), 2356, 50992, 4679, false, false, false, 800, 5852);
	this->eubzxhlbuegdwpuinft(string("updsctu"), string("ilhkhowqfvejxjlrnkywvqxbweuolpwlpdlhpwftlrebehxgxgd"), string("qsnnnlpxafdcoatreatxxlburrdtzgsxwhtyzmxsgjqrkhjjcjtnr"), 2603, 38924, string("vzyifbombgyrbnparpdvtqkasojggdodvuwgwezuw"), true, false, 28358, true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class nhqnlfg {
public:
	double nfukdhnhxeqhocq;
	string ofgreqddabwol;
	double txrxknqc;
	bool rpihz;
	int qhdmse;
	nhqnlfg();
	int qzcvndiacfpadlavbdpbscyq(bool icrhg, int dxvnvpomfrh, int gzcqvmg, int oqevmy, bool oedpjjly, double cjyfecjcxnbpk, bool piaaqbmt, string hoxkibz);
	void kfinoomnvwunhnpvapgxjnlz(double dqtluuih);
	double oztmdttgpkzwwblu(string ilatffybhg, string aprjxbbab, string usiukoak, int gvgeo, int ugrxzl, bool omngypcntxzrmns);
	bool hzolaxajmmqvrzi();
	bool qyqjcwtzvabmtlkwiwhrrwjla(string vqdistgggiwygty, string flkiyjfgv, int rfmyw, string fopmra, string rlubadqhlkaems, double etagfbn, bool nouayandcoe, double gjwszde, int gbipwbnbeqmk);
	double qygocmvztlyigyre(bool owlkay, double igbcgrtswdoskpi, int lhzccqodpzrqq, double vsccpiyqfkmdr, int quezfuyt, bool aivehe);
	double lwcfjhgjys(bool kwkklgnnyt, double luwplqjd, double hoqtkx, bool eemeimrnh, string gmbgbv, int ozgupvnvany, int aqwdkdhm, bool djizr, double lwyyfhd);
	bool mpttscwsrbdxdwbweyugxctf();

protected:
	bool oemjshrpst;
	double wjvevih;

	double yyyfsonejxnosuncbhnltu(string iaqwnbsubxssmh, int aslefnfpkxbqni, int ivmviehycpz);
	double smlcrpxqhpvfcv(string ovsajnhbjoyj, double yvlcgdnwrdfczy, double sbgtqeddjpipfzi, int ocfyzipkbvhex, bool iioqpu);
	int tadwnzfbuiwmitzcpnyfezi();
	int phzijspeecysrkeiwhgtcmy(bool vodltqbxxsczr, int wlqevlciwqdk, double xdsiqyhkd, int utuunymfsvwp);
	int gogfnypgcktfjncpvkpug(double ebjjodriymsgj, string lvewemdxgfshyd, int rhxgdaz, string jjazqgg, double mtrjdkjoqgst, double rnrwxab, bool jjzbphqcqsg, bool rlnxmsm, string pyltwhyhsrde, int vlfivfs);
	double yizjhicybbdt(bool hcadp, double fyigw, string sxfbj, double viduwzqcvemg, bool zcjtjw, string wpdbgzjjlmvdygr);
	void efqiovlhjogqospvwe(int gjmdev, bool zpokxskmbmkfq, int widxavszab, string gfomvthte, string hvopjmsuubqqss, bool ffudlm, string ijvdiffnxfxyk, int ekiwyzh, double dbwnumjaxyxzfdd);
	string zzueiewlnlg(string xjicfxrtqwazybn, int qhdtzeev, int xcsgsyhosbpa, int tkvdfqs, int ovlkrtjraqr, int xzfsophwdfsvxc, double datdczzvzkhu, int alotfdhunpofjll, bool tmwuwkgcaxkwx, bool rhabrbvgzwloh);
	void rhsjeudjxrrb(string punbkgb, int kuwpqjmiwec, bool dnfweqljreizpy, bool fnbrwtklpu, double hnoqvizy);
	int tslnlokzeucgleqxq(double flgulkhvtxfbc, int bgdaotdjxv, bool uolnsrnhgbkp, string uwibkgonnqwsy, string zcdjeehusubadh, string ifowkhehdjgcy);

private:
	double gvisblloifsj;
	bool udzgzmrj;
	double ejkvjttvbgm;
	string kgpnwzuj;

	string mvelmgjbqtepoxsp(string vkfifyp, double grxzoythzd, string fzpffjwqn, bool nmoziihlojs, bool dvhlnkzmb, string mvtucsbigo, bool ctzuemdtym, bool yqstemnfdyiw);
	int oczorkicjlvgizpcbfeus(string regysiqxs, bool jdwlnosfvgrauem, bool tbpppxkkign);
	int cqhuoizrqnxzbtl(bool lpkzapsywafiqr, int cfryasicdxnibk);
	void iohenldsiavluebal(int ayiauvt, int slbar, double jjqllesifikqu, bool zshidkrbazdlt, bool jljapqoakmzyrn);
	bool efymsoihnhxw(string xraxoxfnljdyxw, bool janft);
	string irkmspocgtisuivu(int gnezzuyupsehi, bool pfscwkwa, double ubsbiuneozij, int hissuknyoy, bool xiujohvrguyrz, bool ajqlozzhzs, double ivyne, string wzeqtvnny);
	bool fpcpqrbddumz(bool rvxoldfcigqzib, double fzgcadazpcgpz, int apqduorctl, double clazc, int wjymimrqipug, int zqknkxr);
	bool cxksebiintuprvcaf(double pkacdfcsvt, string pbwuzi, string ejgzmdi, int kuoadfarlnitsly, string gkahdbmeeb);

};


string nhqnlfg::mvelmgjbqtepoxsp(string vkfifyp, double grxzoythzd, string fzpffjwqn, bool nmoziihlojs, bool dvhlnkzmb, string mvtucsbigo, bool ctzuemdtym, bool yqstemnfdyiw) {
	bool lknpqkqtanfuv = true;
	double utyazosm = 155;
	double ogupyunzqidhcq = 1162;
	return string("khei");
}

int nhqnlfg::oczorkicjlvgizpcbfeus(string regysiqxs, bool jdwlnosfvgrauem, bool tbpppxkkign) {
	return 65458;
}

int nhqnlfg::cqhuoizrqnxzbtl(bool lpkzapsywafiqr, int cfryasicdxnibk) {
	bool fnzccsdu = true;
	int jkmrjaydr = 2725;
	double wwnausyciiimv = 7954;
	bool geivlicgr = false;
	string zrokid = "tkcmuipukdhgmnbewhcahxrwzweohwnxvbftgsxpjoezjoazuyoqkdbyoml";
	int fznxqa = 235;
	double npsbitsb = 24172;
	string juaxcgwum = "cfhdwyljpfqwmoftwxtofzthbnbeacwaocbbkxfypcwdhmoujcnmgbaihsrhljprjlqcudvgppisu";
	string wfhjbtfgyevqhks = "iawddvsgwfscwpsqhxohnbcfohjbtidqyinaryjoowodqrm";
	return 71837;
}

void nhqnlfg::iohenldsiavluebal(int ayiauvt, int slbar, double jjqllesifikqu, bool zshidkrbazdlt, bool jljapqoakmzyrn) {
	bool eprxuqpdjgghy = true;
	bool vzylgkjzedrjav = true;
	bool ymrez = false;
	bool wtiwprmecwkfcll = true;
	double kixdubhvsquiwnx = 25260;
	bool refqbh = true;
	double xhrobnz = 18332;
	double hfltywddrdfmaly = 18988;
	string hbwzdbzckgm = "ymvhxpagizwlqvhimaxjjvccunriayyvomeouukcrhpnudyqngmdckvcyrzahuddwxfngfpsnktwdlg";
	if (18332 != 18332) {
		int ti;
		for (ti = 17; ti > 0; ti--) {
			continue;
		}
	}

}

bool nhqnlfg::efymsoihnhxw(string xraxoxfnljdyxw, bool janft) {
	bool cgyujejw = true;
	int vbjnpeqjsypgva = 1211;
	string dkiiaiowsie = "agsqydvfwydogzikxxeudqxgtfcgimsjpcannpsy";
	string ekuetct = "qlkztgvrtloaptdvrnxuwbcfcrvzwykouupyghhiwrwdrzvpukxykwunubhwirkvplakywmghztmvtxibwlolkoubppsastqyjz";
	string twcwzyltsxunx = "ueretyxrrjvbnegpmecfpzirobjuuitrccligkkcygamxynnmcjfvg";
	bool yngde = true;
	bool srurccgungyo = false;
	int muubpdpf = 3410;
	double pxpvh = 3985;
	bool nifndsx = true;
	if (false == false) {
		int cmszyj;
		for (cmszyj = 64; cmszyj > 0; cmszyj--) {
			continue;
		}
	}
	if (true == true) {
		int lr;
		for (lr = 38; lr > 0; lr--) {
			continue;
		}
	}
	return false;
}

string nhqnlfg::irkmspocgtisuivu(int gnezzuyupsehi, bool pfscwkwa, double ubsbiuneozij, int hissuknyoy, bool xiujohvrguyrz, bool ajqlozzhzs, double ivyne, string wzeqtvnny) {
	bool xmxkemwiwcbo = false;
	bool yqfxzbf = false;
	bool zdmzbmzium = false;
	double aoxxor = 4586;
	string ecqmeuh = "tkxehnjdbjrunyoahhfvhyswvhkmzikahyigetkutsqfaxhqtkxkgopmhzzomagjogrmcxceekalshnwebqxslkguftadakpme";
	return string("xtabprducisxwmq");
}

bool nhqnlfg::fpcpqrbddumz(bool rvxoldfcigqzib, double fzgcadazpcgpz, int apqduorctl, double clazc, int wjymimrqipug, int zqknkxr) {
	return false;
}

bool nhqnlfg::cxksebiintuprvcaf(double pkacdfcsvt, string pbwuzi, string ejgzmdi, int kuoadfarlnitsly, string gkahdbmeeb) {
	int zakfvcgpzuhblvx = 1035;
	if (1035 != 1035) {
		int vbecmyh;
		for (vbecmyh = 15; vbecmyh > 0; vbecmyh--) {
			continue;
		}
	}
	return false;
}

double nhqnlfg::yyyfsonejxnosuncbhnltu(string iaqwnbsubxssmh, int aslefnfpkxbqni, int ivmviehycpz) {
	double zlomka = 80;
	double autyfl = 57794;
	int refmdanicfvsd = 7264;
	int pofhjrzgicclg = 3759;
	string nznljcbowx = "ckrvwxsyccrzwofawrfpqskywtflvzgcanpvhdr";
	double lkfkj = 19203;
	if (80 == 80) {
		int sogiwi;
		for (sogiwi = 7; sogiwi > 0; sogiwi--) {
			continue;
		}
	}
	if (19203 != 19203) {
		int lyhp;
		for (lyhp = 41; lyhp > 0; lyhp--) {
			continue;
		}
	}
	if (57794 != 57794) {
		int pmgjj;
		for (pmgjj = 4; pmgjj > 0; pmgjj--) {
			continue;
		}
	}
	return 70152;
}

double nhqnlfg::smlcrpxqhpvfcv(string ovsajnhbjoyj, double yvlcgdnwrdfczy, double sbgtqeddjpipfzi, int ocfyzipkbvhex, bool iioqpu) {
	double jcgsrjepzvw = 26250;
	double scylr = 39174;
	string pthgolhtbpe = "qwuqkhxzphfyhsyxkxzaxsvutbrwmopkxhusibhdaylsoohrzyaqkebnlmqzapdtmxaaatpkoxvsype";
	if (39174 != 39174) {
		int detretmu;
		for (detretmu = 48; detretmu > 0; detretmu--) {
			continue;
		}
	}
	if (39174 != 39174) {
		int mwofmv;
		for (mwofmv = 37; mwofmv > 0; mwofmv--) {
			continue;
		}
	}
	if (39174 != 39174) {
		int mhpehyqi;
		for (mhpehyqi = 45; mhpehyqi > 0; mhpehyqi--) {
			continue;
		}
	}
	return 83462;
}

int nhqnlfg::tadwnzfbuiwmitzcpnyfezi() {
	int pdkrccmolzkirg = 2785;
	int fupxwqijfx = 2308;
	bool jiiimpf = true;
	bool ubzexnw = true;
	double okgxbqvbskx = 7438;
	if (true != true) {
		int aodnufpyc;
		for (aodnufpyc = 21; aodnufpyc > 0; aodnufpyc--) {
			continue;
		}
	}
	return 21139;
}

int nhqnlfg::phzijspeecysrkeiwhgtcmy(bool vodltqbxxsczr, int wlqevlciwqdk, double xdsiqyhkd, int utuunymfsvwp) {
	int kvulgi = 5037;
	string lnvinmctsk = "heqbngxbiveeuwrtthxgewvsbhmywfknkzvgmgabyicksvnbryvdvudjkvkcjxyheykgafmmpemlxgvvitboffrftbh";
	int dzgszxj = 1975;
	int sdazh = 4776;
	string zzshxoaez = "htfpmo";
	if (1975 == 1975) {
		int rvlfi;
		for (rvlfi = 45; rvlfi > 0; rvlfi--) {
			continue;
		}
	}
	if (string("heqbngxbiveeuwrtthxgewvsbhmywfknkzvgmgabyicksvnbryvdvudjkvkcjxyheykgafmmpemlxgvvitboffrftbh") == string("heqbngxbiveeuwrtthxgewvsbhmywfknkzvgmgabyicksvnbryvdvudjkvkcjxyheykgafmmpemlxgvvitboffrftbh")) {
		int wa;
		for (wa = 8; wa > 0; wa--) {
			continue;
		}
	}
	return 75500;
}

int nhqnlfg::gogfnypgcktfjncpvkpug(double ebjjodriymsgj, string lvewemdxgfshyd, int rhxgdaz, string jjazqgg, double mtrjdkjoqgst, double rnrwxab, bool jjzbphqcqsg, bool rlnxmsm, string pyltwhyhsrde, int vlfivfs) {
	string ljfjrxwqxvxogl = "zqqhrwpt";
	bool amxeevjfwyzhsk = true;
	if (string("zqqhrwpt") == string("zqqhrwpt")) {
		int jgixsiytm;
		for (jgixsiytm = 85; jgixsiytm > 0; jgixsiytm--) {
			continue;
		}
	}
	if (true != true) {
		int laonbwqhw;
		for (laonbwqhw = 56; laonbwqhw > 0; laonbwqhw--) {
			continue;
		}
	}
	if (string("zqqhrwpt") != string("zqqhrwpt")) {
		int rp;
		for (rp = 57; rp > 0; rp--) {
			continue;
		}
	}
	if (true != true) {
		int kbihb;
		for (kbihb = 28; kbihb > 0; kbihb--) {
			continue;
		}
	}
	if (true == true) {
		int hlubskc;
		for (hlubskc = 69; hlubskc > 0; hlubskc--) {
			continue;
		}
	}
	return 37756;
}

double nhqnlfg::yizjhicybbdt(bool hcadp, double fyigw, string sxfbj, double viduwzqcvemg, bool zcjtjw, string wpdbgzjjlmvdygr) {
	double rivtmj = 23436;
	string zbxcyzirscbfmq = "kzoqchlgcmt";
	string lysnkqwubxopvld = "acwxhieqwinffbptjksefonrzhmdspccdpprwgzwseqptifiitwgilju";
	bool qigtjpr = false;
	if (23436 != 23436) {
		int anoqsh;
		for (anoqsh = 15; anoqsh > 0; anoqsh--) {
			continue;
		}
	}
	if (false == false) {
		int wkvt;
		for (wkvt = 28; wkvt > 0; wkvt--) {
			continue;
		}
	}
	if (string("acwxhieqwinffbptjksefonrzhmdspccdpprwgzwseqptifiitwgilju") != string("acwxhieqwinffbptjksefonrzhmdspccdpprwgzwseqptifiitwgilju")) {
		int fuzfeo;
		for (fuzfeo = 94; fuzfeo > 0; fuzfeo--) {
			continue;
		}
	}
	if (string("acwxhieqwinffbptjksefonrzhmdspccdpprwgzwseqptifiitwgilju") == string("acwxhieqwinffbptjksefonrzhmdspccdpprwgzwseqptifiitwgilju")) {
		int hqmkcuzt;
		for (hqmkcuzt = 5; hqmkcuzt > 0; hqmkcuzt--) {
			continue;
		}
	}
	return 73035;
}

void nhqnlfg::efqiovlhjogqospvwe(int gjmdev, bool zpokxskmbmkfq, int widxavszab, string gfomvthte, string hvopjmsuubqqss, bool ffudlm, string ijvdiffnxfxyk, int ekiwyzh, double dbwnumjaxyxzfdd) {

}

string nhqnlfg::zzueiewlnlg(string xjicfxrtqwazybn, int qhdtzeev, int xcsgsyhosbpa, int tkvdfqs, int ovlkrtjraqr, int xzfsophwdfsvxc, double datdczzvzkhu, int alotfdhunpofjll, bool tmwuwkgcaxkwx, bool rhabrbvgzwloh) {
	bool exhxjvcj = true;
	bool kzeryppzaiav = false;
	double kvrcnuyszubgz = 20205;
	string sszaivxpebgau = "uoluwqtgnyhtdjhnzmil";
	string rnycgssszmgzu = "kqvqtwugaqohhcvdjndcyebcgtvvmwak";
	string tpzzizhi = "nxjogaekfdihnofmiioqslelypuibpupkbukgegboeppeytnrusblavajodcpdzuhumagqposnkjr";
	double hheusawrjkhsyat = 20090;
	string dtgcyr = "ldxgyxuczdztdljoqqvewiinel";
	double qzkqvhf = 29535;
	bool thpzptgsd = true;
	return string("");
}

void nhqnlfg::rhsjeudjxrrb(string punbkgb, int kuwpqjmiwec, bool dnfweqljreizpy, bool fnbrwtklpu, double hnoqvizy) {
	int hbuetcevzx = 1821;
	double unmlyrzbj = 49184;
	bool bmhcxd = true;
	string zrgmi = "mpieilcinejznzsxxqrtvzcccomuuiatzgrtcxvucatouwizdd";

}

int nhqnlfg::tslnlokzeucgleqxq(double flgulkhvtxfbc, int bgdaotdjxv, bool uolnsrnhgbkp, string uwibkgonnqwsy, string zcdjeehusubadh, string ifowkhehdjgcy) {
	string efkbdzdhi = "gbmmbvhckncbjfgpgkcvuvujiylujhucgtiymnuwwijwcozyfmtztnjiiewsqickhiwezdvlhbxqutuuogkdqfejqpihclux";
	string ujubfywxkfjgnz = "fvzaiutzzhhaurapzgnmousbiwecfyecmbmzdcmllozndgrnkrkclrdgvnnlvinvttppuiqvujpjaslayycqopnrzhpko";
	double hghsn = 27645;
	double tmmxaxyyqmckd = 51770;
	double hqprojhbxf = 23619;
	bool iovbh = true;
	double wttlzrsgv = 983;
	bool bcuzmmybfxs = true;
	if (27645 != 27645) {
		int dlv;
		for (dlv = 65; dlv > 0; dlv--) {
			continue;
		}
	}
	if (983 == 983) {
		int beozhbl;
		for (beozhbl = 93; beozhbl > 0; beozhbl--) {
			continue;
		}
	}
	return 71317;
}

int nhqnlfg::qzcvndiacfpadlavbdpbscyq(bool icrhg, int dxvnvpomfrh, int gzcqvmg, int oqevmy, bool oedpjjly, double cjyfecjcxnbpk, bool piaaqbmt, string hoxkibz) {
	bool krypbwz = false;
	bool oopzzaqkohlvp = false;
	if (false == false) {
		int mtzx;
		for (mtzx = 86; mtzx > 0; mtzx--) {
			continue;
		}
	}
	if (false == false) {
		int ctjlnwes;
		for (ctjlnwes = 8; ctjlnwes > 0; ctjlnwes--) {
			continue;
		}
	}
	return 10498;
}

void nhqnlfg::kfinoomnvwunhnpvapgxjnlz(double dqtluuih) {
	string couxtqbhgxbh = "oiminmlqcnkoxqyigxajxrmzrjfmuqsmlvbekzexnfyafpquomcsjckdglusponvo";
	int eutnjcgb = 115;
	double ofamsqakt = 18312;
	int vdefaedvchha = 3685;
	string irvtycuhrmxvh = "bvbek";
	double awxgerwoad = 20415;
	double pjucsprgjjh = 76453;
	bool puctvstwahkxbs = true;
	if (string("oiminmlqcnkoxqyigxajxrmzrjfmuqsmlvbekzexnfyafpquomcsjckdglusponvo") != string("oiminmlqcnkoxqyigxajxrmzrjfmuqsmlvbekzexnfyafpquomcsjckdglusponvo")) {
		int juuv;
		for (juuv = 82; juuv > 0; juuv--) {
			continue;
		}
	}
	if (18312 != 18312) {
		int cq;
		for (cq = 84; cq > 0; cq--) {
			continue;
		}
	}
	if (true != true) {
		int nyfyfw;
		for (nyfyfw = 11; nyfyfw > 0; nyfyfw--) {
			continue;
		}
	}
	if (18312 == 18312) {
		int qzrrhjb;
		for (qzrrhjb = 15; qzrrhjb > 0; qzrrhjb--) {
			continue;
		}
	}
	if (true == true) {
		int xhetxcvlib;
		for (xhetxcvlib = 41; xhetxcvlib > 0; xhetxcvlib--) {
			continue;
		}
	}

}

double nhqnlfg::oztmdttgpkzwwblu(string ilatffybhg, string aprjxbbab, string usiukoak, int gvgeo, int ugrxzl, bool omngypcntxzrmns) {
	int ohsuwpm = 4739;
	string rsplbt = "uqklaaueuqbkdkymajzqkhxgwqvfxxqwmuizofkw";
	bool dxneufkpv = true;
	bool mdrgmuopv = false;
	string iaygf = "folukfdwsphllncvdo";
	if (string("folukfdwsphllncvdo") == string("folukfdwsphllncvdo")) {
		int raftdkym;
		for (raftdkym = 10; raftdkym > 0; raftdkym--) {
			continue;
		}
	}
	return 17538;
}

bool nhqnlfg::hzolaxajmmqvrzi() {
	double pufmrlumhghgm = 15687;
	string jblgalpskj = "zllezavltgizhqvzcuuowoczejccojfrziqnr";
	int okquxevtooleq = 3244;
	bool rwlqbjx = false;
	string hytdodgi = "gxegowuinylitheychaetaytdombxydsexaanzgavjwtryhftqpjvovjenujghyowvpfxocmjotsldqy";
	double qwfxfndf = 37559;
	double drhuruxjide = 8087;
	bool gfpsoqeqx = false;
	if (string("zllezavltgizhqvzcuuowoczejccojfrziqnr") != string("zllezavltgizhqvzcuuowoczejccojfrziqnr")) {
		int uhgmfd;
		for (uhgmfd = 65; uhgmfd > 0; uhgmfd--) {
			continue;
		}
	}
	if (37559 != 37559) {
		int klytwwde;
		for (klytwwde = 43; klytwwde > 0; klytwwde--) {
			continue;
		}
	}
	return true;
}

bool nhqnlfg::qyqjcwtzvabmtlkwiwhrrwjla(string vqdistgggiwygty, string flkiyjfgv, int rfmyw, string fopmra, string rlubadqhlkaems, double etagfbn, bool nouayandcoe, double gjwszde, int gbipwbnbeqmk) {
	return true;
}

double nhqnlfg::qygocmvztlyigyre(bool owlkay, double igbcgrtswdoskpi, int lhzccqodpzrqq, double vsccpiyqfkmdr, int quezfuyt, bool aivehe) {
	string bvuqzgacn = "clgqdpjvpcgtwwqvdzsxbshctqbjbnpbvcubbberslacqsjzjlksgsskhmwbcfb";
	bool pcrucf = false;
	if (false == false) {
		int cbxszjl;
		for (cbxszjl = 51; cbxszjl > 0; cbxszjl--) {
			continue;
		}
	}
	if (string("clgqdpjvpcgtwwqvdzsxbshctqbjbnpbvcubbberslacqsjzjlksgsskhmwbcfb") == string("clgqdpjvpcgtwwqvdzsxbshctqbjbnpbvcubbberslacqsjzjlksgsskhmwbcfb")) {
		int zgsjpi;
		for (zgsjpi = 16; zgsjpi > 0; zgsjpi--) {
			continue;
		}
	}
	if (false != false) {
		int li;
		for (li = 58; li > 0; li--) {
			continue;
		}
	}
	if (string("clgqdpjvpcgtwwqvdzsxbshctqbjbnpbvcubbberslacqsjzjlksgsskhmwbcfb") != string("clgqdpjvpcgtwwqvdzsxbshctqbjbnpbvcubbberslacqsjzjlksgsskhmwbcfb")) {
		int nvvz;
		for (nvvz = 65; nvvz > 0; nvvz--) {
			continue;
		}
	}
	if (false == false) {
		int vvmfcxm;
		for (vvmfcxm = 29; vvmfcxm > 0; vvmfcxm--) {
			continue;
		}
	}
	return 99125;
}

double nhqnlfg::lwcfjhgjys(bool kwkklgnnyt, double luwplqjd, double hoqtkx, bool eemeimrnh, string gmbgbv, int ozgupvnvany, int aqwdkdhm, bool djizr, double lwyyfhd) {
	double niifejjyg = 51503;
	string mahttlhpeycadp = "nftqsiywowaybphcnt";
	double ymihrbzwudi = 70814;
	if (51503 == 51503) {
		int ibvnnnlrsh;
		for (ibvnnnlrsh = 20; ibvnnnlrsh > 0; ibvnnnlrsh--) {
			continue;
		}
	}
	if (51503 == 51503) {
		int qsqso;
		for (qsqso = 16; qsqso > 0; qsqso--) {
			continue;
		}
	}
	if (51503 != 51503) {
		int haamz;
		for (haamz = 14; haamz > 0; haamz--) {
			continue;
		}
	}
	if (string("nftqsiywowaybphcnt") == string("nftqsiywowaybphcnt")) {
		int txcrs;
		for (txcrs = 49; txcrs > 0; txcrs--) {
			continue;
		}
	}
	if (string("nftqsiywowaybphcnt") == string("nftqsiywowaybphcnt")) {
		int hug;
		for (hug = 14; hug > 0; hug--) {
			continue;
		}
	}
	return 83189;
}

bool nhqnlfg::mpttscwsrbdxdwbweyugxctf() {
	bool zrewollet = true;
	bool gxwanxjuqzglv = false;
	double khqexpmilmgvwx = 8760;
	double szazuzkj = 38908;
	int mhaogkwevve = 3211;
	bool ttqscypvacteea = false;
	bool rwmvwlb = true;
	string jmiuh = "cxawjbeoyfrxeoqeqrg";
	if (true != true) {
		int rok;
		for (rok = 70; rok > 0; rok--) {
			continue;
		}
	}
	if (3211 == 3211) {
		int vc;
		for (vc = 12; vc > 0; vc--) {
			continue;
		}
	}
	if (string("cxawjbeoyfrxeoqeqrg") != string("cxawjbeoyfrxeoqeqrg")) {
		int iu;
		for (iu = 10; iu > 0; iu--) {
			continue;
		}
	}
	if (true != true) {
		int voirbrrn;
		for (voirbrrn = 9; voirbrrn > 0; voirbrrn--) {
			continue;
		}
	}
	return true;
}

nhqnlfg::nhqnlfg() {
	this->qzcvndiacfpadlavbdpbscyq(true, 146, 5322, 8420, true, 79949, true, string("gktpomepvfflvkcogbnsroomofwbinibiwmahgslhdirchmnpkm"));
	this->kfinoomnvwunhnpvapgxjnlz(3109);
	this->oztmdttgpkzwwblu(string("bfultbzfjkgoxqihcxkdyqjzbouvfqvolxjfpwrxacqpcthegzurjaionneab"), string("vmmzzhjbkolhmsyfofzaddptyqiwnxykabuikrrrqvcujsspgpninmb"), string("crzuefrzdnqpqnrifhlsii"), 5174, 3196, false);
	this->hzolaxajmmqvrzi();
	this->qyqjcwtzvabmtlkwiwhrrwjla(string("ekttmgceymbfiirmsjbqtocimgucfkhiumdktj"), string("xpjuuqrnmaezrlxzosqumvwmqbwhfroumqipbtjsbvpsafcloekximwchqmiwmazuzlokkmu"), 2085, string("k"), string("lcdjamxdecupdhmmpdjvhfwvchbtbvyyevbiymihjkkqwjxyxrlsopukahjuwsidkpiftecefrwluopohlzqbmsx"), 35302, true, 32918, 3102);
	this->qygocmvztlyigyre(false, 43778, 2163, 49325, 2869, true);
	this->lwcfjhgjys(true, 27347, 46251, true, string("jgjuzzvhipxtaantiyxiqsmqwftaglvlsueiyojyyhwrjifplmlgoljhuoiuaeyglhmlljolslgdvykqt"), 2930, 928, false, 4145);
	this->mpttscwsrbdxdwbweyugxctf();
	this->yyyfsonejxnosuncbhnltu(string("xlwvtpcqwqanpjnfhzoobmtdylpyqiimxlzucaobmbtpqusvsomcwuljvhdwivpvmmdlb"), 1032, 4090);
	this->smlcrpxqhpvfcv(string("rnkozkeidnxmunjyremybfoazvgrrbrkyafldwpyuusycshpfxaqzrtclxccoxrh"), 26842, 9274, 2727, true);
	this->tadwnzfbuiwmitzcpnyfezi();
	this->phzijspeecysrkeiwhgtcmy(true, 1194, 375, 3341);
	this->gogfnypgcktfjncpvkpug(46527, string("hjaouqilhpzl"), 1003, string("trxjzknbusvkjbasvqngkezfemlr"), 3738, 17419, true, true, string("zkqiiyqvfhaodbxdzoamhvkkzlgvcsdofjcxbxagmhxlbefqmrvpszxhwp"), 3019);
	this->yizjhicybbdt(true, 70991, string("eqtszbpoomflullclzclu"), 19298, false, string("rumojnmpzzuviszlgtvudxmoqjgfpoo"));
	this->efqiovlhjogqospvwe(3442, true, 3848, string("gvgyafmppcrdrmjoqmnxmsqfowwwwyrfelpmikqrlcqhsodgutbjilryuohwogfgwmaxbxvxntwfituu"), string("wshrihpyabrsnvnitchaqruegdwjtdufgeyncsqcvmjktioqhpcawxuaaybmjmfqibklyzbkfpyvhdxiunliqsgrf"), false, string("tmndetukbtfvesbhfxujtpvussgedijmdouykdemijgqacbctqmlghpmhojdyoxuuncjqmvyanxfwjmpcxgq"), 856, 11673);
	this->zzueiewlnlg(string("bijerlfrtahglycmcscbhpdazsfjxsvljupkmfwzchvrgcsldrjqcnbgon"), 3104, 758, 445, 4795, 2546, 17618, 4394, false, false);
	this->rhsjeudjxrrb(string("yivhbkootafoawjtvdowhydxyxxakeuvadovbcbqyuorfhjtbpvgkxoqckjjvikikwpmfscfuwbpbyegfpyeb"), 379, false, true, 10833);
	this->tslnlokzeucgleqxq(19597, 1186, false, string("frwhnllrxunxubkyqnya"), string("ihkorngxzwgrzilqtcyhqcptlpzpbakwjp"), string("sjnlvkqscyzhurqxoakbtlwvqjgpdgwyziunyzqytiovaehmjalqwercykginc"));
	this->mvelmgjbqtepoxsp(string("algoixmuxeeaepktmbxejzxpewzperpxierykoxtpj"), 75560, string("tgevjqkdtuxnvsogve"), false, false, string("wqavxfbolfolznlpcsvxobvvmccuh"), true, false);
	this->oczorkicjlvgizpcbfeus(string("gzckmqbffqlehwpqkyyujxardjjzytqyqplzhmxjgduraiumpfhdelrcpzvltgjpzbgdzfdvpglhyusx"), false, false);
	this->cqhuoizrqnxzbtl(true, 7378);
	this->iohenldsiavluebal(849, 6756, 3316, false, false);
	this->efymsoihnhxw(string("dqokjemfpxxttajvjtmvxvplbpurvzvxybbrfgqcvfytckofmnxyzklplvhggbbolohobppuudkfmga"), false);
	this->irkmspocgtisuivu(1315, true, 4563, 1741, false, false, 26720, string("wgxvvdbtpyoukihfmsiftvrlhclq"));
	this->fpcpqrbddumz(true, 22363, 4983, 74154, 1644, 2088);
	this->cxksebiintuprvcaf(11600, string("olwxgtw"), string("sdjswqvjxooswavpbmizhoolnqz"), 944, string("ucrcuorgsmwpecfsgredlyfzbyfvxsljimrwjkiaeznuxhitkcmcqzlacyugxanuuqcpkaxmbnsgnyainukbxuxcrgflsxpgfk"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class btxfolo {
public:
	int ccshowpredhqx;
	btxfolo();
	string mkqnbfejqohblyekjfutlgk(int zzghspbgajdgkjc, double igrieqbwbz);
	double rmyuidbnibhlzntg(double gmoqoxle, bool abxtxuyqemkbbx, string rmencpgb, string nszdffxehs, string zjhsmlfjqtdkgb);
	string owrjpajiyj(int kqjoaa, int ehqophaxyydmv, bool xosfgpvlbqomv, string kfyinoaxstxc, int wuxlukatt, double analcdrdtxnvs, int hfhfxa, bool ctwqvzflhu, double fckrebkmawii);
	string ajuzcdkvkiyvblprzbhgb(double ithmftbuhpdkva, double zzacismmprbdoaa, int yvakcx, double mivbmifcvbbeo, bool ffzzxthdhn, int smlyyggdz);
	int yfaxjinmhk(bool wgmwmqgir, string abztmsqpjusbdb, int rdlkrbofkkrv, bool cdbmyxyr, bool xmhyyvskqn, bool drhqdgysujpg, string itsxtjkoyay, int bcttdfnpiey, double auocvbauel);
	string izefjpuloxxtywrpbglhatk(bool cmkiwnyrszyuebc, int yugdofkefksrzmk);

protected:
	int otbymfjtybjp;
	double erosexdjxivxf;
	bool tqctwanu;
	bool gufppotxs;

	int hhyhvxbrqnhluqvsztgztvf(string pzure, int sljtyhmsztgfep, int xwbbfvstaqkenlh, bool kgbudwbm, bool jvgakqbv);
	string pqhkbnhezhnwghouofzufl();
	string dzlslkdfblshp(double aqowtyhqlortmdu, string iwbeds, bool dtvddqhi);
	double ocgunorrzswwojfoajbgxc(string ampzpjerjilafdy);
	int kxtqugbyzggcqxgwaed(bool usguxctbftdvs, double aymjxixcmyoqwd, int zalavll, string vzjeihmrcz, double ybpcgngbzvsx, string ujspgburccd, string nxulutoe);

private:
	double cowqrpcfonthmq;
	double mwwkpxyh;
	int elzmhpwyjno;
	bool lsrherjfql;
	int rophwld;

	bool ycdxvsycsthbytontzoxsdu(string vbqpjecui, int iejncrz, int chvwettnxgonvk, double ddvswzoguohb, string akyglqef, double gdfhkk, double lpxzakds, string bxxqgnvyoxou);
	double aprikyenefj(double geilaphngbmgpl, bool gmyddwtkyke, int peltbilanybkte, int xnxkuv);
	string lzudmxmwvcqqltenrmhgjnj(double tekwbcbvjfylo, int zklglfjhybjkux, string awklgiejcqwgn, int cvjmbtitwxych);
	void vkpovchgbbninjzds(string obowjduiufj, bool ktzsgorqm);
	bool tqfkdjfzrhmqvciozhcgcyes(int ezstn, string umkcvkyfewhkg, int ehfvll, bool etclpdfi, int ncmwfoluyvtj, string kskomf, double napworhohlktfsm, int juoqityeor);

};


bool btxfolo::ycdxvsycsthbytontzoxsdu(string vbqpjecui, int iejncrz, int chvwettnxgonvk, double ddvswzoguohb, string akyglqef, double gdfhkk, double lpxzakds, string bxxqgnvyoxou) {
	bool vvsyak = true;
	string cjhbwhxsvdfdnb = "gqqkpmxecndquytuqywmyhggvytcmygofqqoginun";
	bool tnqvhyod = false;
	int xfmqpxg = 2607;
	int atwpy = 2607;
	string qqjfemb = "xnkcifhgkajbgqruoierwvtzifhvuyoyqhgsuc";
	bool akagbxqc = true;
	int enpediyszn = 64;
	return true;
}

double btxfolo::aprikyenefj(double geilaphngbmgpl, bool gmyddwtkyke, int peltbilanybkte, int xnxkuv) {
	double gcxvdi = 36845;
	double mfvoiihnpslcjva = 5660;
	bool vrrzqicymhddf = false;
	double ncagllvlfghokb = 48469;
	string zsxgtlt = "azwq";
	if (string("azwq") == string("azwq")) {
		int eeeutm;
		for (eeeutm = 84; eeeutm > 0; eeeutm--) {
			continue;
		}
	}
	if (string("azwq") != string("azwq")) {
		int juevbrcx;
		for (juevbrcx = 71; juevbrcx > 0; juevbrcx--) {
			continue;
		}
	}
	if (string("azwq") != string("azwq")) {
		int etw;
		for (etw = 10; etw > 0; etw--) {
			continue;
		}
	}
	if (48469 != 48469) {
		int nwxgim;
		for (nwxgim = 8; nwxgim > 0; nwxgim--) {
			continue;
		}
	}
	if (48469 == 48469) {
		int iv;
		for (iv = 66; iv > 0; iv--) {
			continue;
		}
	}
	return 74891;
}

string btxfolo::lzudmxmwvcqqltenrmhgjnj(double tekwbcbvjfylo, int zklglfjhybjkux, string awklgiejcqwgn, int cvjmbtitwxych) {
	int jxkxljpz = 166;
	bool iefemsl = true;
	string caoshkqdxq = "hqnctldidlnyoasfijjvcmkhrzfbj";
	double mtrcul = 45871;
	int rydwe = 6562;
	string uhlxjhuyr = "iiyxrdtwzxwzwmcpnicasgzynhbfimradyjoiburmrercgdbiempzoulodngyahuad";
	string qcroxv = "eszcwoyinlegztsedapfrwxicbigqavvpyvmkzyltoeasnggfivzujiqhedactycddylxilbyadsznjnilbuuotksruzaxyca";
	if (string("eszcwoyinlegztsedapfrwxicbigqavvpyvmkzyltoeasnggfivzujiqhedactycddylxilbyadsznjnilbuuotksruzaxyca") != string("eszcwoyinlegztsedapfrwxicbigqavvpyvmkzyltoeasnggfivzujiqhedactycddylxilbyadsznjnilbuuotksruzaxyca")) {
		int paapj;
		for (paapj = 43; paapj > 0; paapj--) {
			continue;
		}
	}
	if (string("hqnctldidlnyoasfijjvcmkhrzfbj") != string("hqnctldidlnyoasfijjvcmkhrzfbj")) {
		int jhwkx;
		for (jhwkx = 18; jhwkx > 0; jhwkx--) {
			continue;
		}
	}
	if (string("hqnctldidlnyoasfijjvcmkhrzfbj") == string("hqnctldidlnyoasfijjvcmkhrzfbj")) {
		int hwedppld;
		for (hwedppld = 99; hwedppld > 0; hwedppld--) {
			continue;
		}
	}
	return string("arjxijz");
}

void btxfolo::vkpovchgbbninjzds(string obowjduiufj, bool ktzsgorqm) {
	int ciwztujjkkidl = 6960;
	bool lgwuuwskvc = true;
	int optugp = 1388;
	int lmhilgrnznnd = 1007;
	if (6960 == 6960) {
		int kkoxouaqt;
		for (kkoxouaqt = 89; kkoxouaqt > 0; kkoxouaqt--) {
			continue;
		}
	}

}

bool btxfolo::tqfkdjfzrhmqvciozhcgcyes(int ezstn, string umkcvkyfewhkg, int ehfvll, bool etclpdfi, int ncmwfoluyvtj, string kskomf, double napworhohlktfsm, int juoqityeor) {
	string gcbmmohjrtfse = "lmwrshygikjqbksjsoffswmfoovnkrnotpsauwgrlfxymavzsfckggbhmskwcqraixbn";
	double ambwnw = 70802;
	int cdkagetgfzmblgc = 714;
	bool dstfbql = true;
	if (true == true) {
		int umzk;
		for (umzk = 46; umzk > 0; umzk--) {
			continue;
		}
	}
	if (714 != 714) {
		int qiqojcktfh;
		for (qiqojcktfh = 36; qiqojcktfh > 0; qiqojcktfh--) {
			continue;
		}
	}
	if (string("lmwrshygikjqbksjsoffswmfoovnkrnotpsauwgrlfxymavzsfckggbhmskwcqraixbn") != string("lmwrshygikjqbksjsoffswmfoovnkrnotpsauwgrlfxymavzsfckggbhmskwcqraixbn")) {
		int aotofm;
		for (aotofm = 84; aotofm > 0; aotofm--) {
			continue;
		}
	}
	if (70802 != 70802) {
		int pgsio;
		for (pgsio = 39; pgsio > 0; pgsio--) {
			continue;
		}
	}
	return true;
}

int btxfolo::hhyhvxbrqnhluqvsztgztvf(string pzure, int sljtyhmsztgfep, int xwbbfvstaqkenlh, bool kgbudwbm, bool jvgakqbv) {
	string zxbga = "imtqzcrithbkeoauoxsoxlyophjoqadfxnujjwutyhbtfubveyunofklcekakyblbgcnlrcqzuxvenfnmtaxrzjdvfcoqqssnqjn";
	string tolhdlblt = "dkvhjzcjlvtwktshirtearrhjhmdguuswkufbgzeiuycmsthbbteiihuvdnlupeegckggzxgnijzqbbxeelppryufqxpl";
	bool xgvvsqfqch = false;
	if (string("dkvhjzcjlvtwktshirtearrhjhmdguuswkufbgzeiuycmsthbbteiihuvdnlupeegckggzxgnijzqbbxeelppryufqxpl") != string("dkvhjzcjlvtwktshirtearrhjhmdguuswkufbgzeiuycmsthbbteiihuvdnlupeegckggzxgnijzqbbxeelppryufqxpl")) {
		int mndq;
		for (mndq = 91; mndq > 0; mndq--) {
			continue;
		}
	}
	if (false == false) {
		int kjanfe;
		for (kjanfe = 74; kjanfe > 0; kjanfe--) {
			continue;
		}
	}
	if (string("imtqzcrithbkeoauoxsoxlyophjoqadfxnujjwutyhbtfubveyunofklcekakyblbgcnlrcqzuxvenfnmtaxrzjdvfcoqqssnqjn") != string("imtqzcrithbkeoauoxsoxlyophjoqadfxnujjwutyhbtfubveyunofklcekakyblbgcnlrcqzuxvenfnmtaxrzjdvfcoqqssnqjn")) {
		int lzqiiu;
		for (lzqiiu = 41; lzqiiu > 0; lzqiiu--) {
			continue;
		}
	}
	return 55200;
}

string btxfolo::pqhkbnhezhnwghouofzufl() {
	return string("tzpazaenkoyfvr");
}

string btxfolo::dzlslkdfblshp(double aqowtyhqlortmdu, string iwbeds, bool dtvddqhi) {
	int ifxratlujw = 2061;
	int scmiwt = 993;
	string zdzlbjn = "nuqtmgcmdvcthnswaonqurizobqozwakndcwrjqswzvvlfegiqalhuyyzgoishwmguewkxnmnzhvulsncjcmzwprhoeltk";
	double utxwkmuscoix = 15382;
	double pmkxelyurif = 33435;
	bool qidmrxgbpoqjr = true;
	bool zxatoyn = true;
	string mpzpxyrpxoae = "bzswkjkzqfqeaavpkljorpqgijowwzcjdftjdqxzesb";
	string olkmzxbjbok = "ojitutuzffraokrhjrsjoqmelrmpyjlqowrqxmhtqcdabqrdtusvmtuecwov";
	if (true != true) {
		int quvfkzytzt;
		for (quvfkzytzt = 10; quvfkzytzt > 0; quvfkzytzt--) {
			continue;
		}
	}
	return string("o");
}

double btxfolo::ocgunorrzswwojfoajbgxc(string ampzpjerjilafdy) {
	bool ifhsuyu = false;
	bool ezjzbzdjn = true;
	string kjgtppbaovbatsv = "xzwffpcfwiqo";
	bool bsgiruqlrcw = true;
	int imnlai = 3485;
	if (true != true) {
		int rfuqfko;
		for (rfuqfko = 52; rfuqfko > 0; rfuqfko--) {
			continue;
		}
	}
	if (true == true) {
		int fhygl;
		for (fhygl = 32; fhygl > 0; fhygl--) {
			continue;
		}
	}
	if (false == false) {
		int tw;
		for (tw = 65; tw > 0; tw--) {
			continue;
		}
	}
	if (false != false) {
		int deiinihtwm;
		for (deiinihtwm = 59; deiinihtwm > 0; deiinihtwm--) {
			continue;
		}
	}
	return 58284;
}

int btxfolo::kxtqugbyzggcqxgwaed(bool usguxctbftdvs, double aymjxixcmyoqwd, int zalavll, string vzjeihmrcz, double ybpcgngbzvsx, string ujspgburccd, string nxulutoe) {
	bool dbeiotzw = true;
	int htaknodpf = 200;
	if (true == true) {
		int de;
		for (de = 66; de > 0; de--) {
			continue;
		}
	}
	return 44629;
}

string btxfolo::mkqnbfejqohblyekjfutlgk(int zzghspbgajdgkjc, double igrieqbwbz) {
	bool vmvujf = false;
	int putlwojddpxjsdk = 1298;
	if (1298 != 1298) {
		int trfqnou;
		for (trfqnou = 52; trfqnou > 0; trfqnou--) {
			continue;
		}
	}
	if (false != false) {
		int dxmbnlpj;
		for (dxmbnlpj = 35; dxmbnlpj > 0; dxmbnlpj--) {
			continue;
		}
	}
	if (false == false) {
		int mqwmtd;
		for (mqwmtd = 72; mqwmtd > 0; mqwmtd--) {
			continue;
		}
	}
	if (false != false) {
		int vdlicmravs;
		for (vdlicmravs = 14; vdlicmravs > 0; vdlicmravs--) {
			continue;
		}
	}
	if (1298 == 1298) {
		int vivw;
		for (vivw = 84; vivw > 0; vivw--) {
			continue;
		}
	}
	return string("vt");
}

double btxfolo::rmyuidbnibhlzntg(double gmoqoxle, bool abxtxuyqemkbbx, string rmencpgb, string nszdffxehs, string zjhsmlfjqtdkgb) {
	bool sqxpmsemcw = true;
	double mlxcrqrhl = 24070;
	double yjusnwqefncfrs = 12425;
	string vtytb = "suitwamtaizugkrhjzstzvgzwpilxscnkcwguxwnxdfehxipqfppaigqizqwksnxjssncpsnytckgnutvwadxquc";
	double ojqhdptwy = 10759;
	bool ahzcskict = true;
	double jtaofh = 5213;
	string eeyditxkhxqd = "zazfqfpgwabzmfqgyjnipgpzzoqqphegnshjnoeqprocajursimryqttyhfwypktxv";
	string bqmhsvs = "spayzwuzuomkljmldrrigtbjwmbstuzztcnbxcdonhjozbxkchtukwfmifmslcrcdjzkrkubvbwmfxzwtwgejs";
	if (string("spayzwuzuomkljmldrrigtbjwmbstuzztcnbxcdonhjozbxkchtukwfmifmslcrcdjzkrkubvbwmfxzwtwgejs") != string("spayzwuzuomkljmldrrigtbjwmbstuzztcnbxcdonhjozbxkchtukwfmifmslcrcdjzkrkubvbwmfxzwtwgejs")) {
		int siy;
		for (siy = 76; siy > 0; siy--) {
			continue;
		}
	}
	if (true != true) {
		int atvpfxdzg;
		for (atvpfxdzg = 80; atvpfxdzg > 0; atvpfxdzg--) {
			continue;
		}
	}
	if (string("spayzwuzuomkljmldrrigtbjwmbstuzztcnbxcdonhjozbxkchtukwfmifmslcrcdjzkrkubvbwmfxzwtwgejs") == string("spayzwuzuomkljmldrrigtbjwmbstuzztcnbxcdonhjozbxkchtukwfmifmslcrcdjzkrkubvbwmfxzwtwgejs")) {
		int qdfmdbykf;
		for (qdfmdbykf = 31; qdfmdbykf > 0; qdfmdbykf--) {
			continue;
		}
	}
	if (string("spayzwuzuomkljmldrrigtbjwmbstuzztcnbxcdonhjozbxkchtukwfmifmslcrcdjzkrkubvbwmfxzwtwgejs") != string("spayzwuzuomkljmldrrigtbjwmbstuzztcnbxcdonhjozbxkchtukwfmifmslcrcdjzkrkubvbwmfxzwtwgejs")) {
		int vwcjm;
		for (vwcjm = 50; vwcjm > 0; vwcjm--) {
			continue;
		}
	}
	if (true != true) {
		int lvlwzqeh;
		for (lvlwzqeh = 18; lvlwzqeh > 0; lvlwzqeh--) {
			continue;
		}
	}
	return 48608;
}

string btxfolo::owrjpajiyj(int kqjoaa, int ehqophaxyydmv, bool xosfgpvlbqomv, string kfyinoaxstxc, int wuxlukatt, double analcdrdtxnvs, int hfhfxa, bool ctwqvzflhu, double fckrebkmawii) {
	return string("seepd");
}

string btxfolo::ajuzcdkvkiyvblprzbhgb(double ithmftbuhpdkva, double zzacismmprbdoaa, int yvakcx, double mivbmifcvbbeo, bool ffzzxthdhn, int smlyyggdz) {
	bool lenbmbrilbdwk = true;
	if (true == true) {
		int tqhlndne;
		for (tqhlndne = 90; tqhlndne > 0; tqhlndne--) {
			continue;
		}
	}
	return string("yvguzhgnlkzju");
}

int btxfolo::yfaxjinmhk(bool wgmwmqgir, string abztmsqpjusbdb, int rdlkrbofkkrv, bool cdbmyxyr, bool xmhyyvskqn, bool drhqdgysujpg, string itsxtjkoyay, int bcttdfnpiey, double auocvbauel) {
	int ixoxqlrfl = 1499;
	int xfqeg = 722;
	int rtvfsppci = 1296;
	bool nrvyj = false;
	if (1296 != 1296) {
		int qjmk;
		for (qjmk = 36; qjmk > 0; qjmk--) {
			continue;
		}
	}
	if (1296 != 1296) {
		int apqu;
		for (apqu = 90; apqu > 0; apqu--) {
			continue;
		}
	}
	if (722 != 722) {
		int kxmiflp;
		for (kxmiflp = 79; kxmiflp > 0; kxmiflp--) {
			continue;
		}
	}
	return 68268;
}

string btxfolo::izefjpuloxxtywrpbglhatk(bool cmkiwnyrszyuebc, int yugdofkefksrzmk) {
	bool tzjyzlddgsik = false;
	int nfjfjeqboyil = 2859;
	string nvkoveuco = "dpxeciblcpkeutbznzqpmjxakjrmuhnhhhcirokfvpodsatyqivgrtrhvohbyrhogahjwriytoqcqxtbpmzys";
	double wczrcvkc = 33184;
	string ftrqq = "kmrtusrrndjibgniabpbjizdnwsizcibqtdboguboiknnnzfffeiwaq";
	string aabnbpxvpgrlkwz = "tnjxyuwc";
	double nlibcavxhaubro = 5637;
	bool uqykfg = true;
	if (5637 != 5637) {
		int mgyzzx;
		for (mgyzzx = 74; mgyzzx > 0; mgyzzx--) {
			continue;
		}
	}
	return string("oglryzuyyepezlwfmhcc");
}

btxfolo::btxfolo() {
	this->mkqnbfejqohblyekjfutlgk(2950, 2984);
	this->rmyuidbnibhlzntg(19939, true, string("famnziozogbfydrsayrhvxmmfdwtr"), string("lniocuymjumclnzkxrfcaivqxqviowoursodsirkfyztibwvoqqfurxawkbqpjkgpkgyfkwbadplyrtvhqejnxydoohyxtkq"), string("lqalsaapxfwhwxxqzhtrhcyrxtcxzfhlhtojadauuvvuer"));
	this->owrjpajiyj(4451, 2844, true, string("alvsuaryktkiohthfqzbbyxhqfyjdbbyprxqwcfixxffxbkhdhzwk"), 1921, 11213, 248, false, 30862);
	this->ajuzcdkvkiyvblprzbhgb(65601, 26669, 4669, 12086, false, 3297);
	this->yfaxjinmhk(false, string("vjvtwzyrmdaakgswticcxvlkuehmwufuyqraxzskknofeztncdynknnvgxmwullrahoyobpylyunmly"), 5391, false, true, false, string("nzdagaeeilrvwmvrzjjxzcztivdpbpgfefgrzbdycugjsmtfxnuojkjtrutdceswntoq"), 4229, 46858);
	this->izefjpuloxxtywrpbglhatk(true, 2757);
	this->hhyhvxbrqnhluqvsztgztvf(string("yyfchufpgeoddwapvmdmmbdvvabaqolejaimdsfiubjxxmfyrqyacalonewtcrsui"), 6623, 4796, false, false);
	this->pqhkbnhezhnwghouofzufl();
	this->dzlslkdfblshp(45146, string("uckgjwlepzqlnffaccdyjmcyxtuctiqlvivkeyshcmvejitiqecxn"), false);
	this->ocgunorrzswwojfoajbgxc(string("wwtavgbzglvqigbeglkzeobimlcdrqmfpnrljayjkfmebynujcicsnvgpzuauxuubk"));
	this->kxtqugbyzggcqxgwaed(false, 21534, 3972, string("ylsjlidnvblaccmmnayzpnvzruilglmmljadlfhftwyiib"), 10023, string("eittfwwnysamcfevmgeiigfduuwricho"), string("onmkdbkiaipfokjigvh"));
	this->ycdxvsycsthbytontzoxsdu(string("uhjykrjwsbmseyttjohnnjyvnwoyehkqvlhlicjnkaiaaubdfjsvwiafwtmizrkzctafvdtougoeztenhlafopzeiitkbgsu"), 5570, 710, 64835, string("xkgpprdvjbalciudzxojcgzvegb"), 19233, 13841, string("irwqvytgkzqmamcxyqlqnxttvjwuxtuippmlqlknuizuyvgxtettadjemdqzcpzqydkldevfmgwjgnfk"));
	this->aprikyenefj(35532, false, 2742, 3441);
	this->lzudmxmwvcqqltenrmhgjnj(846, 1021, string("svklrxpwbttvwwhgnucrrslvspfldqecxpgntkieetzb"), 6784);
	this->vkpovchgbbninjzds(string("hzwdgwmonwdhsvnrrifgcxqgxhziezpezjtbenslfesmhtwvntgejlecipftaeixlqyszxgpedx"), false);
	this->tqfkdjfzrhmqvciozhcgcyes(241, string("pspevsijcnpqpomobfxupwqijtgtfitnkazhyheitcedgjmkbgjftfmxutbvbyfyqkinsjofkhebjhysrkscp"), 2686, true, 1671, string("mdoivuaebigmasrzrkwsisuyekxpxtbgnrw"), 17829, 4713);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class zntefhr {
public:
	string bjgmr;
	double tzgiwlcfaygttio;
	double semeasyyvkek;
	bool zlayekhm;
	zntefhr();
	int ahbqctjpgqhrildmp();
	void rexhmhayjt(string vyojahfoofv);
	string pmnhvkrhemzyeboxxosfqky(bool vwwqiumklg, bool suaimdyg, int jbklhblgizei, int srhfutxdwzltek, string wubtus, bool sdpcnbleuw);
	string gurtnkxeuuuwrmabsgpjc(bool mzzrwfrlqzs, string kjbjvwd, bool htmdtppx);
	bool mijvrsdtjdcga(bool hxsntsxmtwabi, int pqxtfanqmhjqut, bool bqqbsfpbqeymu, double hyojvuwf, bool awpmvsbtcicpo, int yhvsdin, bool fvbpvhqcsjbr, double mygnplyor, int refbauem);
	int vrjvfkanhgvddwq(int ydcwdrixk, string sqlrfso, bool zjcsugjrmftr, int otrytvvyx, string wesownl, bool rqosfljwxat, string xwnfbzvp, bool curombabqsujlzt, int vlliwqqovukmfnl, double dzhesq);
	string avqpvzqomabgzzggmbuyvdh(int fqjxrkffdhkhxsy, bool wbxuxyyoxykdcgx, bool zfsvkuebujzox, string vtozwjwfti, string zulbypjf, double gdabtmaevbdqqf, bool hazuzqfy, string qqrepaey, bool jjqeltdx, string xomugek);

protected:
	double oepur;
	double itdmj;
	int xjqfpg;

	int jdjjfcnblujazvzvofj(string ycxwlpnb, double qdzotd, int xwurbxtznowgae, bool llfyh, double veijx, double ihrmalrxjxrwzr, int kdftmtfh);
	int oeppokaivbyaqibudywnemzym(int lnaglr, string jhwtyupxpx, double rvlyzgkn, bool qkgbmhcuzf, bool lywbrrhncm, string enekrzldkes, int rjqcyolbfy, bool vyckwt, bool cxgsouj, int mwsjg);
	string fenevmpasghmy(bool aieneiqpfpehax, bool kkbytur, string wwowceo, double teokxxqvwz, bool dicrgtxgfg);
	double ykgllkgycpc(bool ajtfd, double rwwfrtczb, int mrwuoqmeea, string tofjcbnwmwwu, int etrrvqpysoqknu, int kivwr);
	double qxeouadybacgkxiurfyotbkod();

private:
	string taqkjgwvx;
	int ixrrdnoc;
	string szonmdg;

	double yznmrslzpsdrro(int ceodddjkmn, bool txfxzuqbq, int qozzk, string zchnfcdjdfpb, double feiai, double niaornyremgfcke);
	bool kmoorueaetgbqqbteypzqqah(string kzbdzz, int orkuzxo, int qofanod, string iehpxnhchxzxwec, double rzqhqn, string rqbqutyjlndwi, string wfercdxhiw, string gkusuqbtqqa, double zpalwvstltvfg);
	int pvpouoxnkdhqtgjdgyrrzx(int xgfotih, double dutozkuofh, bool zhbeitvbvnkg, int cgvwvoltk, double grujpskr);

};


double zntefhr::yznmrslzpsdrro(int ceodddjkmn, bool txfxzuqbq, int qozzk, string zchnfcdjdfpb, double feiai, double niaornyremgfcke) {
	double aozvwmmh = 21205;
	int zdwwhutebec = 1689;
	bool ldtdazrtoed = false;
	bool zaqibezsedv = false;
	int qcteoknzhe = 822;
	int jsxntb = 477;
	string lasijtwcnqgoq = "";
	bool fcisr = true;
	double xlalevhghd = 4759;
	if (21205 != 21205) {
		int eudk;
		for (eudk = 16; eudk > 0; eudk--) {
			continue;
		}
	}
	if (4759 != 4759) {
		int hdomshwee;
		for (hdomshwee = 61; hdomshwee > 0; hdomshwee--) {
			continue;
		}
	}
	if (false != false) {
		int ftcdqpaxiw;
		for (ftcdqpaxiw = 40; ftcdqpaxiw > 0; ftcdqpaxiw--) {
			continue;
		}
	}
	if (true == true) {
		int st;
		for (st = 34; st > 0; st--) {
			continue;
		}
	}
	if (21205 == 21205) {
		int erzjd;
		for (erzjd = 10; erzjd > 0; erzjd--) {
			continue;
		}
	}
	return 71229;
}

bool zntefhr::kmoorueaetgbqqbteypzqqah(string kzbdzz, int orkuzxo, int qofanod, string iehpxnhchxzxwec, double rzqhqn, string rqbqutyjlndwi, string wfercdxhiw, string gkusuqbtqqa, double zpalwvstltvfg) {
	double gldvlpoquga = 65071;
	double vhzxacw = 12934;
	string xcicuejpbtdcrm = "nyzuclrmiybqptnwyafeuuybrdmmvyixqfkqsulersefiuvxiaqxsavlyrsguzkymnssqmfnckvnrtmnbcvyjwzywxiphrbpphky";
	string xiutg = "bmctutvkiaydcokhrkhukxtbmvguejvajwosxwphufcxgtmwgpzlozyxhzoynbveqwxgkdtzpxhwmyebsskgygvfymbteojlsci";
	int ixxxbcel = 4235;
	string lcnsmwbyjtc = "lfrhsedlhbtqwnjojhzaghbqwbajied";
	if (string("nyzuclrmiybqptnwyafeuuybrdmmvyixqfkqsulersefiuvxiaqxsavlyrsguzkymnssqmfnckvnrtmnbcvyjwzywxiphrbpphky") == string("nyzuclrmiybqptnwyafeuuybrdmmvyixqfkqsulersefiuvxiaqxsavlyrsguzkymnssqmfnckvnrtmnbcvyjwzywxiphrbpphky")) {
		int ow;
		for (ow = 86; ow > 0; ow--) {
			continue;
		}
	}
	if (string("lfrhsedlhbtqwnjojhzaghbqwbajied") != string("lfrhsedlhbtqwnjojhzaghbqwbajied")) {
		int bpxhb;
		for (bpxhb = 7; bpxhb > 0; bpxhb--) {
			continue;
		}
	}
	return false;
}

int zntefhr::pvpouoxnkdhqtgjdgyrrzx(int xgfotih, double dutozkuofh, bool zhbeitvbvnkg, int cgvwvoltk, double grujpskr) {
	bool wggirvdkpdk = true;
	bool jgbwwepvcmzrwif = false;
	double pmzuimhfvzquaz = 53485;
	if (false == false) {
		int huxkdv;
		for (huxkdv = 94; huxkdv > 0; huxkdv--) {
			continue;
		}
	}
	return 40674;
}

int zntefhr::jdjjfcnblujazvzvofj(string ycxwlpnb, double qdzotd, int xwurbxtznowgae, bool llfyh, double veijx, double ihrmalrxjxrwzr, int kdftmtfh) {
	double wbluklrlrkqiihs = 5809;
	int fosqbrcs = 2881;
	double icxpxbwyxy = 6094;
	string opdjgsocmb = "lwjybtbwadngaqhmaqgxmfrannhwahfsyohmufs";
	int pgwhiil = 789;
	double fvbgy = 61894;
	bool buvrv = false;
	bool kbieamnvsuotiu = false;
	string ryxeutoxwmra = "";
	string yduwgldtwr = "dafzjqxwdwnfwtxhdkaezxqcdrwsp";
	if (789 != 789) {
		int uwunwg;
		for (uwunwg = 26; uwunwg > 0; uwunwg--) {
			continue;
		}
	}
	if (5809 != 5809) {
		int xrudw;
		for (xrudw = 53; xrudw > 0; xrudw--) {
			continue;
		}
	}
	return 29806;
}

int zntefhr::oeppokaivbyaqibudywnemzym(int lnaglr, string jhwtyupxpx, double rvlyzgkn, bool qkgbmhcuzf, bool lywbrrhncm, string enekrzldkes, int rjqcyolbfy, bool vyckwt, bool cxgsouj, int mwsjg) {
	int qycwudelnglkdk = 2360;
	int hmvdkyrwx = 1086;
	if (1086 == 1086) {
		int zacs;
		for (zacs = 58; zacs > 0; zacs--) {
			continue;
		}
	}
	return 51350;
}

string zntefhr::fenevmpasghmy(bool aieneiqpfpehax, bool kkbytur, string wwowceo, double teokxxqvwz, bool dicrgtxgfg) {
	string nvugmvqxc = "wchfmefxstrrxdspjetqqjdqhzbayxtvjicxkwekuimlzmtbwqfrdrcudmzaugdwsuvigfixhstgdozcgbwahtgnbehdc";
	bool ejest = true;
	string jqrgzwytax = "tyyxsicadrpgmcfpchprjqmlkeivicietwsfetmb";
	bool cjnxvhxyeor = true;
	string pvwgol = "iuwhwbkebqxwmacwtxctxrrqsxzqlcybapuxzxttldeaukugybvaichgfxo";
	bool cgklbqmrjhrkguh = true;
	if (true == true) {
		int rcss;
		for (rcss = 34; rcss > 0; rcss--) {
			continue;
		}
	}
	return string("phiknno");
}

double zntefhr::ykgllkgycpc(bool ajtfd, double rwwfrtczb, int mrwuoqmeea, string tofjcbnwmwwu, int etrrvqpysoqknu, int kivwr) {
	double kgkce = 36541;
	bool hirnqd = false;
	bool brjwqberhbgxwbo = true;
	if (true != true) {
		int xwwpdads;
		for (xwwpdads = 81; xwwpdads > 0; xwwpdads--) {
			continue;
		}
	}
	if (36541 != 36541) {
		int rmcny;
		for (rmcny = 33; rmcny > 0; rmcny--) {
			continue;
		}
	}
	if (36541 != 36541) {
		int ube;
		for (ube = 28; ube > 0; ube--) {
			continue;
		}
	}
	if (true != true) {
		int wljcy;
		for (wljcy = 19; wljcy > 0; wljcy--) {
			continue;
		}
	}
	return 35889;
}

double zntefhr::qxeouadybacgkxiurfyotbkod() {
	bool hbvwst = false;
	bool rnepll = false;
	double huhvnqvbzehgjel = 16605;
	string erwwhiefkhm = "fkqxtgikpyardhutakgfybedthwpzxurjdxfjgowxxbzmbphrsiyszugvwnxahdiuiemusubxgloplvaybhjciqirdeehibexm";
	string cqurbgiamggtnu = "betgjwxjhrtmlzobqgtoycpyopnsd";
	int mdsjdwezpzzu = 802;
	string zowvoncvmujnavb = "hxynysecywmjwtuvcwomgbdewnby";
	bool qcydyepygxihsj = false;
	string nqiplhdf = "qoehbtjwinotzbwspdjrrkkoaqkcpoiqwxjgfanighrasdrtavixtzhkxhgolgtpfoiexiiybmrhlocmdpvhfwwccaetuxpxm";
	string kierrap = "ulintjffajwsnnddcmbqxnvyouvzhwziwynfshjsnfcqatzfbzmevtfwmxryrrwibtgvmljquawszgzpaxaqnvq";
	return 45100;
}

int zntefhr::ahbqctjpgqhrildmp() {
	double jdbzpoyilsj = 11198;
	int vxbedghvtevafvu = 1627;
	string ahscbzps = "op";
	if (1627 == 1627) {
		int qvwjz;
		for (qvwjz = 51; qvwjz > 0; qvwjz--) {
			continue;
		}
	}
	if (11198 != 11198) {
		int hinmnhku;
		for (hinmnhku = 56; hinmnhku > 0; hinmnhku--) {
			continue;
		}
	}
	if (string("op") == string("op")) {
		int vgnw;
		for (vgnw = 30; vgnw > 0; vgnw--) {
			continue;
		}
	}
	if (11198 == 11198) {
		int xpirkiiu;
		for (xpirkiiu = 45; xpirkiiu > 0; xpirkiiu--) {
			continue;
		}
	}
	if (1627 == 1627) {
		int ypgs;
		for (ypgs = 96; ypgs > 0; ypgs--) {
			continue;
		}
	}
	return 78441;
}

void zntefhr::rexhmhayjt(string vyojahfoofv) {
	int mbvsk = 4135;
	double obnhakppntwkxm = 29532;
	bool hxitotdbuyohwi = true;
	bool rtlzfzuicteyr = true;
	int zcjjtbwd = 362;
	bool legqygl = true;
	string zygeinbpadfczu = "chiwhllvkfbctebaqlbagcbzzndygyowfvixuxckd";
	double sqerpydwrjrhq = 7058;
	if (29532 != 29532) {
		int ldipi;
		for (ldipi = 89; ldipi > 0; ldipi--) {
			continue;
		}
	}
	if (362 == 362) {
		int mmjftgw;
		for (mmjftgw = 28; mmjftgw > 0; mmjftgw--) {
			continue;
		}
	}
	if (29532 != 29532) {
		int bqufnmcnze;
		for (bqufnmcnze = 24; bqufnmcnze > 0; bqufnmcnze--) {
			continue;
		}
	}
	if (string("chiwhllvkfbctebaqlbagcbzzndygyowfvixuxckd") == string("chiwhllvkfbctebaqlbagcbzzndygyowfvixuxckd")) {
		int qtmewbme;
		for (qtmewbme = 83; qtmewbme > 0; qtmewbme--) {
			continue;
		}
	}
	if (true == true) {
		int wvcveolxn;
		for (wvcveolxn = 29; wvcveolxn > 0; wvcveolxn--) {
			continue;
		}
	}

}

string zntefhr::pmnhvkrhemzyeboxxosfqky(bool vwwqiumklg, bool suaimdyg, int jbklhblgizei, int srhfutxdwzltek, string wubtus, bool sdpcnbleuw) {
	int pygyrincs = 4694;
	string oydhtfcu = "dimhnavyqzoujbyihlwfgfpjcyoshmbzwacmkqquhmnqevqenpoehfqxvyjpcqmsornnjvwuqs";
	string psrwjwlc = "chtnkemtkxuqkyexedjjbhdpuljgyquefxlpqrxbpxvjxlzffadgfuyovctltgjcnpwigbxhoqubvmxeybwpypwnanlilns";
	double hpvfszqwyut = 7252;
	bool dtubqltazvjsrm = false;
	int ytascgr = 992;
	int ojhcvmqv = 615;
	string zehujsyd = "pssvvclmiysxwakkdofmsnhukvnpcgppgnbgknsr";
	double ozygyetaom = 18503;
	return string("duqb");
}

string zntefhr::gurtnkxeuuuwrmabsgpjc(bool mzzrwfrlqzs, string kjbjvwd, bool htmdtppx) {
	string xzatgspdfjzg = "vbyfwpytueorzkwholawjwmuciinyykxhqwrzwjdf";
	if (string("vbyfwpytueorzkwholawjwmuciinyykxhqwrzwjdf") != string("vbyfwpytueorzkwholawjwmuciinyykxhqwrzwjdf")) {
		int bmrzsrt;
		for (bmrzsrt = 85; bmrzsrt > 0; bmrzsrt--) {
			continue;
		}
	}
	return string("ayv");
}

bool zntefhr::mijvrsdtjdcga(bool hxsntsxmtwabi, int pqxtfanqmhjqut, bool bqqbsfpbqeymu, double hyojvuwf, bool awpmvsbtcicpo, int yhvsdin, bool fvbpvhqcsjbr, double mygnplyor, int refbauem) {
	string kyiytvus = "tahdscmijitifieucdyfzeahvebiymwpmxowrshyduqojxsctiffdfbicavkqymwese";
	bool idjpuyadosuwhmq = false;
	bool qstvywuzpuhe = false;
	bool qqgewbvq = true;
	if (false == false) {
		int lpedex;
		for (lpedex = 4; lpedex > 0; lpedex--) {
			continue;
		}
	}
	if (false == false) {
		int qsppwez;
		for (qsppwez = 33; qsppwez > 0; qsppwez--) {
			continue;
		}
	}
	if (false == false) {
		int bkkqnaldim;
		for (bkkqnaldim = 32; bkkqnaldim > 0; bkkqnaldim--) {
			continue;
		}
	}
	if (true != true) {
		int xdrdg;
		for (xdrdg = 75; xdrdg > 0; xdrdg--) {
			continue;
		}
	}
	if (string("tahdscmijitifieucdyfzeahvebiymwpmxowrshyduqojxsctiffdfbicavkqymwese") != string("tahdscmijitifieucdyfzeahvebiymwpmxowrshyduqojxsctiffdfbicavkqymwese")) {
		int bwghai;
		for (bwghai = 82; bwghai > 0; bwghai--) {
			continue;
		}
	}
	return false;
}

int zntefhr::vrjvfkanhgvddwq(int ydcwdrixk, string sqlrfso, bool zjcsugjrmftr, int otrytvvyx, string wesownl, bool rqosfljwxat, string xwnfbzvp, bool curombabqsujlzt, int vlliwqqovukmfnl, double dzhesq) {
	return 57157;
}

string zntefhr::avqpvzqomabgzzggmbuyvdh(int fqjxrkffdhkhxsy, bool wbxuxyyoxykdcgx, bool zfsvkuebujzox, string vtozwjwfti, string zulbypjf, double gdabtmaevbdqqf, bool hazuzqfy, string qqrepaey, bool jjqeltdx, string xomugek) {
	int gkbwnkgcjdv = 417;
	string wqhpwwlncm = "duxmfwsvgcjpzcaqgmhuzlnblddelehajwaeiqocidwxwkaoddtfytkueehdsfqelwkfntytugvtnmhpokgwxkqlwprtbxvvl";
	bool mvamvodhky = false;
	int dhvpmkbsmoaoywh = 16;
	int oxjxmp = 1780;
	double xfvjindnqd = 39611;
	int qnacplmezkv = 4261;
	int ckesgmvuoepcvxo = 4813;
	double arejo = 24701;
	if (1780 != 1780) {
		int mqw;
		for (mqw = 10; mqw > 0; mqw--) {
			continue;
		}
	}
	if (16 == 16) {
		int gbrqwz;
		for (gbrqwz = 54; gbrqwz > 0; gbrqwz--) {
			continue;
		}
	}
	if (24701 != 24701) {
		int iuihz;
		for (iuihz = 70; iuihz > 0; iuihz--) {
			continue;
		}
	}
	if (4261 != 4261) {
		int hahra;
		for (hahra = 44; hahra > 0; hahra--) {
			continue;
		}
	}
	return string("btwgvurqmh");
}

zntefhr::zntefhr() {
	this->ahbqctjpgqhrildmp();
	this->rexhmhayjt(string("jzzmprysnrpvowrbljpnjrzlqcyxoi"));
	this->pmnhvkrhemzyeboxxosfqky(true, true, 1668, 4460, string("xfcbjdveoknrr"), false);
	this->gurtnkxeuuuwrmabsgpjc(true, string("ewyrvdmsjiqyktr"), false);
	this->mijvrsdtjdcga(false, 473, true, 21943, false, 796, false, 39234, 1959);
	this->vrjvfkanhgvddwq(141, string("mozykywittfor"), false, 3440, string("rrjsnnlwfiqomfsfcndckappgxpxmhajenuskbtxypdkwllazpxolgbtdwcdpyvlddpsvvnfuoe"), true, string("oswpisywvxfecguvntnqengkqrmorkekfinkxnsdadcishlgdncxjdmmuuzvzmtaimwuhotgfusxlmfqoxc"), false, 1870, 20042);
	this->avqpvzqomabgzzggmbuyvdh(17, false, false, string("fscypcdcyxwlpgesikfodbopjldniituutipylhmsxejkrkfrihyxjtwypkzgwjmukqyqjrlaowlrstuhuwiqxbhxwnghcrybnx"), string("ywkukuhggaekbwfwqohkahzktjnfyhdzbfmzjgohiqtvxyehylixtczafeuhlprfpbajrhshkdskelpapawnvbrea"), 8639, true, string("azhvvqmtgxgmsxjydrwonamoefbvpskwgdfenaerysesxsqadlyermzgeezodjtrvdqtylieohjakvcorpofkwrvhxpvmcrc"), false, string("rxcsrzsderlorcuyhxodoeihckjlaabnjxhpjusaldzkayookwsxamroabpekbwuwfoidgostapbzewirzlearseky"));
	this->jdjjfcnblujazvzvofj(string("rlxfin"), 34457, 1943, false, 24816, 88362, 5402);
	this->oeppokaivbyaqibudywnemzym(703, string("osttpajcbexpptfgmjrxmbeijycoylvbtwldsaitjkmfordrxhucjtgbpxidkirwajlvqdccmlvhdunpiakhvynhaoedcxbdck"), 708, false, false, string("cemmgpdbsutimriuvnrityntursgewnvfddnrwwoemrncugdhs"), 920, false, true, 7065);
	this->fenevmpasghmy(true, true, string("spperioyubzsxttatjuhgwvocaqprdyvfpgqgmemisowlifa"), 21369, true);
	this->ykgllkgycpc(false, 10446, 2966, string("ughjtsfbozhwbdqgydpolixqgvmybokjxaazzriymzvnkrsetsaaygqweqo"), 7563, 1918);
	this->qxeouadybacgkxiurfyotbkod();
	this->yznmrslzpsdrro(3786, false, 407, string("rqirxlvnlazmzkyvolrcnkvxeppzri"), 60998, 20449);
	this->kmoorueaetgbqqbteypzqqah(string("nnzwagqguukgbaixpxlqxairezldcltdofmkmsthbcrzveqrhmqpctqnklzguukwt"), 7672, 221, string("lyaseztpvryncpzrazbqwaxbuujhbhsbjd"), 20289, string("ixcubgtayocabcsehprsqprhvtotiggeeftnwhddmcdnojsawuliczpmco"), string("cqidfkjjsfivjcwbbdghpimnozzzgqqizlwniratdiyiberjakuyddjlcbslrwvxgvfufqhfmneccznphwtrjwottdazfx"), string("qpepdknzfewpxsgjadtg"), 701);
	this->pvpouoxnkdhqtgjdgyrrzx(3563, 4346, false, 4058, 17939);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ahrqylm {
public:
	string fbdvto;
	string qeitpbvaqjcr;
	int fjvrtqhde;
	ahrqylm();
	int dvpepvjkerooldydd(bool vkvitdvlia, bool uxjdpjko, string hudcehvknxc, string uxzyiekegz);
	int qwvnpqcyyljgphnumkz(double owpwutlmqerj);
	int lzjxvvtxpht(string seztgmw, double ldvlefd, int gjununbc, double dkaosxjqpyo, bool xpjianrlugw, string jvzfvmpl, double mpltw, int rpoqz, double mzidxdiics, string dsramvjeog);
	bool mlygwczmjyawbgdcknqxerey(bool kpsboalsztdvg, string ymusvklvlx, int tsfefnwckpii, string pbbjcpffl, bool xbglereqqdiinh, int ijxnkqudphtmb, string hzaeoesnwj, string cilaa);

protected:
	double rgbhpzzmls;
	bool vxfsbkziwudq;
	int sllqepvxug;
	int hetshpfrcweap;

	int wtspqvfiqxmadhstsge(int fgwusbhv);
	double aygswjsuflwisqxqdkdhk(double zdvcg, int dpawf);

private:
	string formvxhqt;
	bool abbkyetjmhfvtpr;
	bool aycojzp;
	double kafpcbrx;

	string gcbxlilphpggbynepoqn();
	string pknnctnpvxbwav();
	double vkvlhbsgfsgorywyrrxcbumuo(string rooyufdyufwnlmo, double mnymukerpfp, int qojuigyrhs, string fandmy, int nbbinvzrchem, string btajmm, int voqoifojc, int zpaniijiotqnj, bool sbpunon);
	void lvkoctizwyrrygmymbbogm(bool bgksegnexy, double yzbueekzhgwrkor);
	bool zwupxxkfeulnprbqlxr(double ifumhsu, string nhbgayzpyxtkq, bool lkapc, double zqpaombfjbhtco);
	double gxkdvtmalovftn(int eauwynt, string bwtmpdjerl, string qwxvff, double ppfbzkaf, double wgiutocwes, double dlnlalaegq, double dhmdjksszrpako);
	string tlvycjvtnhavcaxmpbytmrh(double jsffmg, double uskmksznucplrqs, double rwjqty, string fmimmy, bool gmwkvvi, int fhfcsrqehzecnz, string fnhylh, int wwaau, string txqhzfvxi, string sutllfxwy);
	string huuhafkcwgogoarqjui(int kxcpxsee);

};


string ahrqylm::gcbxlilphpggbynepoqn() {
	return string("bsnojzhtgc");
}

string ahrqylm::pknnctnpvxbwav() {
	string jpngfkmlbbnec = "dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx";
	if (string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx") == string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx")) {
		int qwbw;
		for (qwbw = 98; qwbw > 0; qwbw--) {
			continue;
		}
	}
	if (string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx") == string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx")) {
		int pvwshz;
		for (pvwshz = 74; pvwshz > 0; pvwshz--) {
			continue;
		}
	}
	if (string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx") != string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx")) {
		int ngstdnfbgr;
		for (ngstdnfbgr = 47; ngstdnfbgr > 0; ngstdnfbgr--) {
			continue;
		}
	}
	if (string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx") != string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx")) {
		int tklhyvcswn;
		for (tklhyvcswn = 7; tklhyvcswn > 0; tklhyvcswn--) {
			continue;
		}
	}
	if (string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx") == string("dtmhnowugpxjoapvdlymfmgytluzjkchxvhhbx")) {
		int sonig;
		for (sonig = 48; sonig > 0; sonig--) {
			continue;
		}
	}
	return string("izednbsdshapeidix");
}

double ahrqylm::vkvlhbsgfsgorywyrrxcbumuo(string rooyufdyufwnlmo, double mnymukerpfp, int qojuigyrhs, string fandmy, int nbbinvzrchem, string btajmm, int voqoifojc, int zpaniijiotqnj, bool sbpunon) {
	bool nhznavinmayd = false;
	double pmgvzqicwjvpdb = 1669;
	double utnzpjvare = 39262;
	double xykohooehxgne = 7186;
	if (false != false) {
		int urj;
		for (urj = 39; urj > 0; urj--) {
			continue;
		}
	}
	return 81839;
}

void ahrqylm::lvkoctizwyrrygmymbbogm(bool bgksegnexy, double yzbueekzhgwrkor) {
	int qwntxp = 4871;
	if (4871 == 4871) {
		int ww;
		for (ww = 42; ww > 0; ww--) {
			continue;
		}
	}
	if (4871 != 4871) {
		int mqi;
		for (mqi = 90; mqi > 0; mqi--) {
			continue;
		}
	}
	if (4871 == 4871) {
		int ae;
		for (ae = 92; ae > 0; ae--) {
			continue;
		}
	}
	if (4871 == 4871) {
		int di;
		for (di = 94; di > 0; di--) {
			continue;
		}
	}
	if (4871 == 4871) {
		int eje;
		for (eje = 59; eje > 0; eje--) {
			continue;
		}
	}

}

bool ahrqylm::zwupxxkfeulnprbqlxr(double ifumhsu, string nhbgayzpyxtkq, bool lkapc, double zqpaombfjbhtco) {
	bool ojzhxmu = false;
	bool ghoywvdc = true;
	bool imiuwvra = false;
	double bsxyqbbj = 32405;
	string hbxoyogmat = "twaehoujgekebwbopjefwzowf";
	if (false == false) {
		int ekusn;
		for (ekusn = 72; ekusn > 0; ekusn--) {
			continue;
		}
	}
	if (string("twaehoujgekebwbopjefwzowf") == string("twaehoujgekebwbopjefwzowf")) {
		int pfoeeqlaq;
		for (pfoeeqlaq = 76; pfoeeqlaq > 0; pfoeeqlaq--) {
			continue;
		}
	}
	if (true == true) {
		int oc;
		for (oc = 82; oc > 0; oc--) {
			continue;
		}
	}
	return true;
}

double ahrqylm::gxkdvtmalovftn(int eauwynt, string bwtmpdjerl, string qwxvff, double ppfbzkaf, double wgiutocwes, double dlnlalaegq, double dhmdjksszrpako) {
	double axlshwtqxevdukw = 3220;
	return 68843;
}

string ahrqylm::tlvycjvtnhavcaxmpbytmrh(double jsffmg, double uskmksznucplrqs, double rwjqty, string fmimmy, bool gmwkvvi, int fhfcsrqehzecnz, string fnhylh, int wwaau, string txqhzfvxi, string sutllfxwy) {
	string okhmwt = "qjzdsvnbixjjkcgmwaqtehyvascj";
	bool hwtvxvvpmotwncw = true;
	double kymwnjoburnsin = 16469;
	bool caafjaty = true;
	string ytyecngajoyu = "gdtmgsvthayofqzfiqhfduvwqbdzpppnwppwafmzkwggtcoushgppzuwsifrtgylytnwfdlxaf";
	bool ilygrk = false;
	return string("t");
}

string ahrqylm::huuhafkcwgogoarqjui(int kxcpxsee) {
	double whgfv = 8976;
	bool ykfbtghhbtmzw = false;
	if (false != false) {
		int chyckvow;
		for (chyckvow = 89; chyckvow > 0; chyckvow--) {
			continue;
		}
	}
	if (false == false) {
		int xblbkt;
		for (xblbkt = 78; xblbkt > 0; xblbkt--) {
			continue;
		}
	}
	return string("rtowrybizkwrt");
}

int ahrqylm::wtspqvfiqxmadhstsge(int fgwusbhv) {
	int iborugdeaygsnp = 865;
	string jzvylm = "lloqkltrjeqwinqpkamq";
	string cbwrrwdzb = "knhtygrcyltrcwctqhkotktbfzzcqbyojdqgnxaufyfplpyffvijgiohty";
	bool doukxe = true;
	string kcdtjlphrazcej = "gzvscmzjccqhygpikihdaygyppasklkfybgjtisqepocyvagojakuavmulwthohhtedicdyfidncn";
	if (string("lloqkltrjeqwinqpkamq") == string("lloqkltrjeqwinqpkamq")) {
		int uqyuolii;
		for (uqyuolii = 29; uqyuolii > 0; uqyuolii--) {
			continue;
		}
	}
	if (string("gzvscmzjccqhygpikihdaygyppasklkfybgjtisqepocyvagojakuavmulwthohhtedicdyfidncn") != string("gzvscmzjccqhygpikihdaygyppasklkfybgjtisqepocyvagojakuavmulwthohhtedicdyfidncn")) {
		int ruhketnh;
		for (ruhketnh = 39; ruhketnh > 0; ruhketnh--) {
			continue;
		}
	}
	return 23821;
}

double ahrqylm::aygswjsuflwisqxqdkdhk(double zdvcg, int dpawf) {
	string iviycuvp = "vjjjzta";
	string uhlanumz = "goiwiywhphwlzwnmiq";
	bool ugbzz = false;
	bool iuuksn = true;
	string nkgiho = "kpnvarmgywaqcmdztjawgycblglomvvalphnrrfgvyybgvyclcidejvyltnqgwufeore";
	bool olxcxyoihalpib = true;
	double llqqipvyjy = 63178;
	return 56583;
}

int ahrqylm::dvpepvjkerooldydd(bool vkvitdvlia, bool uxjdpjko, string hudcehvknxc, string uxzyiekegz) {
	string jucwskb = "fjbtstkwbzhvhhbksqtjhuessjangfttetzwhoijloilinggkzsmx";
	string abwblth = "mobuuymjnnqayaiercxgesosvcubrkizyogybme";
	int uahjtkvkgav = 3300;
	double chdxsth = 34124;
	double snsimzg = 18461;
	bool ngtjbecxm = false;
	return 94678;
}

int ahrqylm::qwvnpqcyyljgphnumkz(double owpwutlmqerj) {
	bool owybjgoewgaogi = true;
	double qszxheny = 904;
	bool pfptuqmx = true;
	bool ogmlq = true;
	string puvpmqwmsxjfpju = "vwlymoswhqronuipzmqntmxeoxhoyaicjlxqzfeojoyuaeohzxhbmchzuytfgtwlhuhlsiyruuyvrye";
	if (true == true) {
		int nybuq;
		for (nybuq = 50; nybuq > 0; nybuq--) {
			continue;
		}
	}
	if (true != true) {
		int akjqgw;
		for (akjqgw = 35; akjqgw > 0; akjqgw--) {
			continue;
		}
	}
	return 87688;
}

int ahrqylm::lzjxvvtxpht(string seztgmw, double ldvlefd, int gjununbc, double dkaosxjqpyo, bool xpjianrlugw, string jvzfvmpl, double mpltw, int rpoqz, double mzidxdiics, string dsramvjeog) {
	return 52470;
}

bool ahrqylm::mlygwczmjyawbgdcknqxerey(bool kpsboalsztdvg, string ymusvklvlx, int tsfefnwckpii, string pbbjcpffl, bool xbglereqqdiinh, int ijxnkqudphtmb, string hzaeoesnwj, string cilaa) {
	double nxqslwfixkf = 22159;
	double cedwm = 15411;
	if (22159 != 22159) {
		int tivqtxsbts;
		for (tivqtxsbts = 16; tivqtxsbts > 0; tivqtxsbts--) {
			continue;
		}
	}
	if (22159 == 22159) {
		int pt;
		for (pt = 82; pt > 0; pt--) {
			continue;
		}
	}
	if (22159 == 22159) {
		int ltyaor;
		for (ltyaor = 51; ltyaor > 0; ltyaor--) {
			continue;
		}
	}
	if (15411 == 15411) {
		int zkkf;
		for (zkkf = 32; zkkf > 0; zkkf--) {
			continue;
		}
	}
	if (15411 == 15411) {
		int bc;
		for (bc = 95; bc > 0; bc--) {
			continue;
		}
	}
	return false;
}

ahrqylm::ahrqylm() {
	this->dvpepvjkerooldydd(false, false, string("nvwdcwarmpvgxefos"), string("rjizraxwmsdklcjafyumrrmiszijcculywebw"));
	this->qwvnpqcyyljgphnumkz(31855);
	this->lzjxvvtxpht(string("ylyqksnlujdqicoqyahooxpyvhsllrytqijgltxxgwuydkyfkxqstvrvwgpqkqh"), 410, 5220, 17518, true, string("mucahbmfrrvlouhnmpctoobdgtdmcpj"), 87219, 2209, 48672, string("bcfipaqkmriblyqjppbfgkrglvumqadbrt"));
	this->mlygwczmjyawbgdcknqxerey(true, string("uewqephuwqislpuwdutrppmdvcztrdgfgnwgsdrerpezgrwkdac"), 3343, string("hsjxbcnwceumvvzelxzihqhnxgbsjduuahtviafcbadutfhkulvqmuwqjdbzbrlw"), false, 1223, string("qftudkevgyvzk"), string("puxwbpdbfzjkfsmdxweyjuzzcavkrbfosdiluofodnltbvidcmrngerenirimgtjqcfedsqatsiaxgvhlwutmpe"));
	this->wtspqvfiqxmadhstsge(2871);
	this->aygswjsuflwisqxqdkdhk(13194, 1876);
	this->gcbxlilphpggbynepoqn();
	this->pknnctnpvxbwav();
	this->vkvlhbsgfsgorywyrrxcbumuo(string("mkettqfhggbmopqdibvjizlrqwnqzxayjrpmnyxilikbeygcptqdud"), 4601, 1272, string("lyunxylzgoclyjexkwsndzrkgoshijjwbnzrdmirthmqhpbsevtgyrgtoctjyxfoshcemplrhgcwsbsnryib"), 1981, string("lajmzxrlwyrwkqdsspyxyjncgooiwthqjjeodvegjww"), 765, 1589, false);
	this->lvkoctizwyrrygmymbbogm(false, 2609);
	this->zwupxxkfeulnprbqlxr(25118, string("tquhipdw"), false, 1644);
	this->gxkdvtmalovftn(1864, string("cvmmgzrx"), string("yuyvrknqmvwpmvacsdxxqtxdujeujojhwrergnozocp"), 12076, 57644, 28289, 28941);
	this->tlvycjvtnhavcaxmpbytmrh(58816, 16017, 35367, string(""), false, 1094, string("eabsintydrgvtacqjcgspxvzlkxxiyttiezmpqojfxubjihrcjt"), 3232, string("gzeqds"), string("ujwqufhvxtxyfedxftzmwxzlmxoynzfrgdw"));
	this->huuhafkcwgogoarqjui(1807);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class spbbhae {
public:
	int agnirjmo;
	bool bsomhmizytuaac;
	double aqyzz;
	double esarcuxv;
	spbbhae();
	double srxcfxogrfbficovelqwxtmmg(bool kimxaeodncabex, string hkmukjwxvnvcxl, bool zarjhjak);
	bool wlbzqgalpirbqwoglhoj(int hbnghukmiohordu, bool sofmz, string iblixlbcfsvrn, double nxvldu, int ckakkbtscqibv, double klyhazjercqa, int zmmfv, bool ilihn, string sbxfs);
	string kpfzjrhdjnhhpszffoofaqvy(int cjulfaihghdxk, string zljpkshoqsbnn, double mgjpmiswysg, int imzuxnabud, bool vsvue, double ssiqnkueyzr, bool asgyglarja, string ujbexpohm, int ljrredgdleoxb, string luxdyknjuhyhpfi);
	string wphpbtsazmbzpkubnvy(string zcccytsyo, double ywxeqvj, bool femdbpueeepkt, string fwjjmnjrhv, double arislzoxom, double jvgdi, double slwpnbqac, int nnpmttw, int iaqoxdu, int hxkepab);
	bool rtqoacwakoezxryd(bool bqqshork, double uplrjtdlimfvly, int dpmepjgg, string xpbujad, string oyxtendvmpvand, int bfvse, string tkmrmdosjckzfm, int cniwq, double vrknquiht);
	double egiqfpotvsefophuniegdybof(int baqsjnoykliroj, bool vcayfytreih, int mvoqv, int rhxuu, int rrngq, bool dkieepbvvck, bool rawqudqzuxssiyj, string gtyibjdrkvct);
	void mdgslrvathzfpjepbgwom(int jebhrb, bool qawfvfu, int vygqpcenzzcnp, double xjmhxeqvxmt, int xoffbhoimejf, double bemropvecp, double eyepaotfxpwjg, double fffdbg, bool vkmfwx);
	string zseyrgriwfpf(string pvkbrmar, string cfryidyqqvnmzvt, double txrml, string acxjienlsz, double hyxpzyiy, string tprmarw, string ionso, string fjouvaitdeb, string yhwndi);
	void ancrmttjvtlvvuytx(int fliarfvkhncvg, double tngafnrwe, double sbeskcjcdev, double nmtrshg, int tbhezxzlkqco);
	int jdpahjplsggsksfbut(double uizwj, int wijgzatfcnne, bool iutejeujjbsxtur, string eqmachlr, int vknzbvtsxjttncv, int bbgexyusynz, string uisaktfsiux);

protected:
	double qhufwdpqbp;
	string ttaqeqpvzbw;
	bool govonmsra;
	int fihysbbxvueko;

	string hwijpjvvdhkpxjvijcknlcwyd(int cqmvzsyjd, int vrxojtqdxv, double gsfdxrrb);
	bool iulepudktdlqnnmhzvd();
	bool cygkjdvuqfmxmc(double txjjfpabe, bool jpjjhe, double zcqfoikfjiulurw, bool jkjnfk, string vbpprueazvwopef, double dradaktrq);
	int avvsiwmallpippz(double eovglkch, bool dopbmviuikc, string vhvzuepzacstcix, bool xyfgnhpmwpydc, string ebmqkbvh, string hpnjjzanl, string apwmkwogwb);
	double ksynbrlyrd(int bxfsxukaps, int tqtjoivy, double wmbxo, bool focwitqme, string xznyafrwhbsbr, double jozrcjsm);

private:
	double hkerg;
	double bbjoflq;
	bool vpaucmn;

	double yslkjdlfsnzehruaocoicjrpz(bool hymxtmu, int agvgybjqnnlaigd, bool kramxgs, bool yepnghyjzigumd, int uujwdqscjeqd, double utuusryapdu, bool jmwgxsilhh, string ynllootok);
	double urezwgymcnkydsjottx(double rhtqyrd, string hcvbipmyhv, double wrrwfrvuoi, string wdumlq);
	double hcsixuzcawsolrncxumzgj(string rbwtu, double guuxgsfxabu, bool ijjfghceeiq, int fquqzs);
	void xkxmgeooptbxgwf(int fxlkcouz, bool kgttpnelras, bool utkbztvkcbsbara, bool dsbdewotzejr, string ugwyr, int wqruaz, double bvxzam);
	void drmbqbkxxygbncrcrdhl(double kcpgsds, int xzcnbcqf);
	void enbdjgbqtvhxmhmxnlw(string eoxkacqlickut, double nozjnsznnjfcdfh, bool yefzejadcbl, bool yyvdxpwdtk, string oghhalizwrmz, bool aflsv, string bckap, string safvjomevtod, bool quuzvgoxqrjs);
	int lavkgeogzco(string rfllieqpgif);
	string lqulbmxyqzcfnymcrcnx(double skytatrgtr, int aduidkpadg, double nwfgutqqpq, int pwgniuhgdbfpr, bool fqnisyhebwy, double heerilbfzaryy);
	double xjemyifdzv(bool hgyhxh, double kbrql, double npbznrgheoce, string rhbhft, string bvxxeusyd, double jslrzjtdparlgpw, string folxl, string aechueugwemi);

};


double spbbhae::yslkjdlfsnzehruaocoicjrpz(bool hymxtmu, int agvgybjqnnlaigd, bool kramxgs, bool yepnghyjzigumd, int uujwdqscjeqd, double utuusryapdu, bool jmwgxsilhh, string ynllootok) {
	string vwehxs = "ycuoownmuytbxseozzirynltkbrvmtqqrpvryalscatbugkwdtmzzkoaegindoyyg";
	if (string("ycuoownmuytbxseozzirynltkbrvmtqqrpvryalscatbugkwdtmzzkoaegindoyyg") == string("ycuoownmuytbxseozzirynltkbrvmtqqrpvryalscatbugkwdtmzzkoaegindoyyg")) {
		int azbqw;
		for (azbqw = 0; azbqw > 0; azbqw--) {
			continue;
		}
	}
	if (string("ycuoownmuytbxseozzirynltkbrvmtqqrpvryalscatbugkwdtmzzkoaegindoyyg") != string("ycuoownmuytbxseozzirynltkbrvmtqqrpvryalscatbugkwdtmzzkoaegindoyyg")) {
		int gqgumzyint;
		for (gqgumzyint = 21; gqgumzyint > 0; gqgumzyint--) {
			continue;
		}
	}
	if (string("ycuoownmuytbxseozzirynltkbrvmtqqrpvryalscatbugkwdtmzzkoaegindoyyg") != string("ycuoownmuytbxseozzirynltkbrvmtqqrpvryalscatbugkwdtmzzkoaegindoyyg")) {
		int dqkebsh;
		for (dqkebsh = 34; dqkebsh > 0; dqkebsh--) {
			continue;
		}
	}
	return 2407;
}

double spbbhae::urezwgymcnkydsjottx(double rhtqyrd, string hcvbipmyhv, double wrrwfrvuoi, string wdumlq) {
	double qnpgyvrnrcpza = 18581;
	int vudtzmwsibibmzk = 4331;
	bool uwdglwa = true;
	return 14369;
}

double spbbhae::hcsixuzcawsolrncxumzgj(string rbwtu, double guuxgsfxabu, bool ijjfghceeiq, int fquqzs) {
	string fmiopibebyiux = "bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb";
	if (string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb") == string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb")) {
		int qvjfir;
		for (qvjfir = 91; qvjfir > 0; qvjfir--) {
			continue;
		}
	}
	if (string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb") != string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb")) {
		int rcdvni;
		for (rcdvni = 59; rcdvni > 0; rcdvni--) {
			continue;
		}
	}
	if (string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb") == string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb")) {
		int vhzaioydgk;
		for (vhzaioydgk = 7; vhzaioydgk > 0; vhzaioydgk--) {
			continue;
		}
	}
	if (string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb") != string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb")) {
		int gjlph;
		for (gjlph = 49; gjlph > 0; gjlph--) {
			continue;
		}
	}
	if (string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb") == string("bgafvuhkwcjnhgutyqdixngfjuizfoqoqezktwcbubvesirviwocttledhfgfdipkvcavmwhwotehpmtwgqb")) {
		int daxvopxbt;
		for (daxvopxbt = 72; daxvopxbt > 0; daxvopxbt--) {
			continue;
		}
	}
	return 6524;
}

void spbbhae::xkxmgeooptbxgwf(int fxlkcouz, bool kgttpnelras, bool utkbztvkcbsbara, bool dsbdewotzejr, string ugwyr, int wqruaz, double bvxzam) {
	bool mwdijlylypycyf = false;
	int tohywtm = 1319;
	bool hagozr = false;
	bool yhygj = true;
	int yjnegk = 1477;
	int bsebiapqhzoi = 3924;
	double pilumbxpzkbcm = 63079;
	int lrsguw = 2017;
	bool tdomez = true;
	if (true != true) {
		int wltumeyzzj;
		for (wltumeyzzj = 62; wltumeyzzj > 0; wltumeyzzj--) {
			continue;
		}
	}
	if (1319 == 1319) {
		int kmxkwropr;
		for (kmxkwropr = 33; kmxkwropr > 0; kmxkwropr--) {
			continue;
		}
	}
	if (false != false) {
		int jqofz;
		for (jqofz = 57; jqofz > 0; jqofz--) {
			continue;
		}
	}

}

void spbbhae::drmbqbkxxygbncrcrdhl(double kcpgsds, int xzcnbcqf) {
	bool amkusvbbpwmbtde = false;
	double ajyldlo = 4717;
	double hdvaetqsckxt = 3042;
	bool lvxijh = true;
	int yxzlyamqbsz = 602;
	int oeqjy = 4837;
	double idkehabc = 61419;
	bool cqeetqdmm = true;
	int sccxifs = 7385;
	if (false == false) {
		int aad;
		for (aad = 92; aad > 0; aad--) {
			continue;
		}
	}
	if (false == false) {
		int shy;
		for (shy = 49; shy > 0; shy--) {
			continue;
		}
	}
	if (true == true) {
		int jl;
		for (jl = 97; jl > 0; jl--) {
			continue;
		}
	}

}

void spbbhae::enbdjgbqtvhxmhmxnlw(string eoxkacqlickut, double nozjnsznnjfcdfh, bool yefzejadcbl, bool yyvdxpwdtk, string oghhalizwrmz, bool aflsv, string bckap, string safvjomevtod, bool quuzvgoxqrjs) {
	int kgyiekxwojrpwub = 2406;
	bool pdsbpwkuvewpip = true;
	string fabkqwedas = "ikyugcudsxgvtoclktopffprejiqxpezwemxbdmqvqdlwwglwjrhxevcxrfyoozypxafltcwcgbci";
	string jmyzgq = "uomtgunfflamtqcrnimadyyvolavttesjgxdxgg";
	string ctyrsexnmmy = "qifho";
	string yplqczuyc = "aiqppvhxyyyknoqjwzcjcrluwoodzmaaasaklbvkdukgoyoplylxkxadtthcdioamoifb";
	int zkjvexpmibbx = 173;
	int yxvsvcqowc = 1626;
	if (string("aiqppvhxyyyknoqjwzcjcrluwoodzmaaasaklbvkdukgoyoplylxkxadtthcdioamoifb") != string("aiqppvhxyyyknoqjwzcjcrluwoodzmaaasaklbvkdukgoyoplylxkxadtthcdioamoifb")) {
		int ysaplvd;
		for (ysaplvd = 39; ysaplvd > 0; ysaplvd--) {
			continue;
		}
	}
	if (string("aiqppvhxyyyknoqjwzcjcrluwoodzmaaasaklbvkdukgoyoplylxkxadtthcdioamoifb") == string("aiqppvhxyyyknoqjwzcjcrluwoodzmaaasaklbvkdukgoyoplylxkxadtthcdioamoifb")) {
		int firc;
		for (firc = 59; firc > 0; firc--) {
			continue;
		}
	}
	if (string("uomtgunfflamtqcrnimadyyvolavttesjgxdxgg") != string("uomtgunfflamtqcrnimadyyvolavttesjgxdxgg")) {
		int krcphsjx;
		for (krcphsjx = 19; krcphsjx > 0; krcphsjx--) {
			continue;
		}
	}
	if (true == true) {
		int tft;
		for (tft = 99; tft > 0; tft--) {
			continue;
		}
	}

}

int spbbhae::lavkgeogzco(string rfllieqpgif) {
	return 73877;
}

string spbbhae::lqulbmxyqzcfnymcrcnx(double skytatrgtr, int aduidkpadg, double nwfgutqqpq, int pwgniuhgdbfpr, bool fqnisyhebwy, double heerilbfzaryy) {
	string firyuy = "tuvqglhicshlhasyrtqxdwesowcmqiphcwztuvvofdznkfyl";
	int sbjymvuephelbjm = 255;
	int yjufzpyv = 741;
	bool lbyem = true;
	double sodxmpkshaigx = 39879;
	int jydfnbrtt = 1028;
	int ycnccnrbejbqrgs = 2047;
	if (string("tuvqglhicshlhasyrtqxdwesowcmqiphcwztuvvofdznkfyl") != string("tuvqglhicshlhasyrtqxdwesowcmqiphcwztuvvofdznkfyl")) {
		int voqre;
		for (voqre = 25; voqre > 0; voqre--) {
			continue;
		}
	}
	if (2047 != 2047) {
		int gobthcp;
		for (gobthcp = 75; gobthcp > 0; gobthcp--) {
			continue;
		}
	}
	if (741 != 741) {
		int zxfu;
		for (zxfu = 21; zxfu > 0; zxfu--) {
			continue;
		}
	}
	if (39879 != 39879) {
		int mb;
		for (mb = 73; mb > 0; mb--) {
			continue;
		}
	}
	if (true != true) {
		int sbqowk;
		for (sbqowk = 28; sbqowk > 0; sbqowk--) {
			continue;
		}
	}
	return string("vdakqtaphgrhrub");
}

double spbbhae::xjemyifdzv(bool hgyhxh, double kbrql, double npbznrgheoce, string rhbhft, string bvxxeusyd, double jslrzjtdparlgpw, string folxl, string aechueugwemi) {
	double lvmbncjaeindiu = 66830;
	bool coallkhfsrseqq = true;
	bool vjeco = true;
	bool pxtiktz = false;
	double oqowpugcvxtu = 23057;
	bool emzicjihl = false;
	double jxokzncirsnffq = 45964;
	if (23057 == 23057) {
		int mmshfrblt;
		for (mmshfrblt = 1; mmshfrblt > 0; mmshfrblt--) {
			continue;
		}
	}
	if (23057 == 23057) {
		int reu;
		for (reu = 59; reu > 0; reu--) {
			continue;
		}
	}
	if (false != false) {
		int bmhrgabvzk;
		for (bmhrgabvzk = 84; bmhrgabvzk > 0; bmhrgabvzk--) {
			continue;
		}
	}
	if (false == false) {
		int lmrcwkjdet;
		for (lmrcwkjdet = 92; lmrcwkjdet > 0; lmrcwkjdet--) {
			continue;
		}
	}
	return 68990;
}

string spbbhae::hwijpjvvdhkpxjvijcknlcwyd(int cqmvzsyjd, int vrxojtqdxv, double gsfdxrrb) {
	int rgllw = 172;
	double tudact = 56131;
	int afaqcs = 5421;
	int vqhep = 3767;
	int fovsinjqknxwvj = 3692;
	bool jmisavwa = true;
	if (3767 != 3767) {
		int gyv;
		for (gyv = 8; gyv > 0; gyv--) {
			continue;
		}
	}
	return string("zvopichdaqojjya");
}

bool spbbhae::iulepudktdlqnnmhzvd() {
	string fvyvfml = "stclmudqgjeipempuyofajnbenfsaejgjchyvejssjgl";
	double sptyjgikljw = 20996;
	double iunkqkbffpxydp = 50966;
	int xygenjjevwsqxni = 1436;
	int bfbsupio = 566;
	double pfruijufgu = 4639;
	if (566 != 566) {
		int hmbny;
		for (hmbny = 74; hmbny > 0; hmbny--) {
			continue;
		}
	}
	if (4639 != 4639) {
		int sxawq;
		for (sxawq = 48; sxawq > 0; sxawq--) {
			continue;
		}
	}
	return false;
}

bool spbbhae::cygkjdvuqfmxmc(double txjjfpabe, bool jpjjhe, double zcqfoikfjiulurw, bool jkjnfk, string vbpprueazvwopef, double dradaktrq) {
	int vfpxsbicsm = 1603;
	double gdrsjzp = 2329;
	string bybbhk = "jfrllczmyxjkabtitdbokpdwausmjhfdslcinglszminexkxgnmshyanwfkxlgnpdlkaqxxedgwdyralmgiduhfne";
	int yqqwnwwot = 1181;
	bool ikabkoqcaihwkb = false;
	string ldxxkswtmmxisu = "msgbrk";
	double dqimvio = 16514;
	double mzhlprudjqn = 70691;
	double mibtgoy = 34659;
	double orqfgxzhx = 36487;
	if (string("msgbrk") == string("msgbrk")) {
		int taaoail;
		for (taaoail = 92; taaoail > 0; taaoail--) {
			continue;
		}
	}
	if (34659 != 34659) {
		int ebvyqpg;
		for (ebvyqpg = 19; ebvyqpg > 0; ebvyqpg--) {
			continue;
		}
	}
	return false;
}

int spbbhae::avvsiwmallpippz(double eovglkch, bool dopbmviuikc, string vhvzuepzacstcix, bool xyfgnhpmwpydc, string ebmqkbvh, string hpnjjzanl, string apwmkwogwb) {
	double dhpul = 5502;
	if (5502 != 5502) {
		int pjlrn;
		for (pjlrn = 100; pjlrn > 0; pjlrn--) {
			continue;
		}
	}
	if (5502 != 5502) {
		int wwofv;
		for (wwofv = 62; wwofv > 0; wwofv--) {
			continue;
		}
	}
	if (5502 != 5502) {
		int egmblxwdgx;
		for (egmblxwdgx = 65; egmblxwdgx > 0; egmblxwdgx--) {
			continue;
		}
	}
	return 2845;
}

double spbbhae::ksynbrlyrd(int bxfsxukaps, int tqtjoivy, double wmbxo, bool focwitqme, string xznyafrwhbsbr, double jozrcjsm) {
	string bvqmqlu = "xuujmgknnuwpazuqwpbtqgoxvvnnzkggwwhbbdgnbvydofujyrxdttlziipttffaxgvxoiaiznuln";
	int uipzeubh = 895;
	string kahmeub = "fx";
	double aifhgxze = 30936;
	int lqnxhwdchsjro = 158;
	string xacxlfnxkbiz = "uukkylypcljaxvclwofumhldajmzemeccbpxofq";
	bool gqzaueumbv = false;
	int cuvdtr = 3708;
	if (30936 != 30936) {
		int ulaooyz;
		for (ulaooyz = 9; ulaooyz > 0; ulaooyz--) {
			continue;
		}
	}
	if (3708 != 3708) {
		int djxpyeqmh;
		for (djxpyeqmh = 55; djxpyeqmh > 0; djxpyeqmh--) {
			continue;
		}
	}
	if (string("uukkylypcljaxvclwofumhldajmzemeccbpxofq") == string("uukkylypcljaxvclwofumhldajmzemeccbpxofq")) {
		int bupar;
		for (bupar = 17; bupar > 0; bupar--) {
			continue;
		}
	}
	if (string("uukkylypcljaxvclwofumhldajmzemeccbpxofq") != string("uukkylypcljaxvclwofumhldajmzemeccbpxofq")) {
		int xpeynnty;
		for (xpeynnty = 46; xpeynnty > 0; xpeynnty--) {
			continue;
		}
	}
	return 97389;
}

double spbbhae::srxcfxogrfbficovelqwxtmmg(bool kimxaeodncabex, string hkmukjwxvnvcxl, bool zarjhjak) {
	bool pmivtiwcsa = false;
	double argywppvmd = 72909;
	double lpqoyyvfvg = 2639;
	double abnnfootc = 31475;
	int rpukjtfvsxljkrm = 5374;
	string rmlgexvzeldpc = "dluxuvjjfzpgkaxwpxetg";
	if (5374 == 5374) {
		int vjdmk;
		for (vjdmk = 33; vjdmk > 0; vjdmk--) {
			continue;
		}
	}
	if (72909 != 72909) {
		int lap;
		for (lap = 33; lap > 0; lap--) {
			continue;
		}
	}
	if (2639 == 2639) {
		int txwwhbwgd;
		for (txwwhbwgd = 53; txwwhbwgd > 0; txwwhbwgd--) {
			continue;
		}
	}
	return 99645;
}

bool spbbhae::wlbzqgalpirbqwoglhoj(int hbnghukmiohordu, bool sofmz, string iblixlbcfsvrn, double nxvldu, int ckakkbtscqibv, double klyhazjercqa, int zmmfv, bool ilihn, string sbxfs) {
	string qsiewsszvvctp = "wmitxlneykrnpbgxbogzuoyhrjwprelbu";
	double lyhfznsgle = 52935;
	double rujvi = 6753;
	string ksyits = "uloxoifufyjicidbetgrecjxpdedphnzwdeypsrdzlqoruuqofb";
	string affdcehiksqdz = "ltjqieydkamkhryrewjmkmdnpeybripwwhdvwvmccwdjsfnj";
	double zhbbuohwnz = 31743;
	bool zlkwhvc = false;
	string wnmdzhs = "pjazqxjnalmhiyhgwddehqvedcvozvppijprdphpntwuomv";
	if (string("uloxoifufyjicidbetgrecjxpdedphnzwdeypsrdzlqoruuqofb") != string("uloxoifufyjicidbetgrecjxpdedphnzwdeypsrdzlqoruuqofb")) {
		int txtuxk;
		for (txtuxk = 66; txtuxk > 0; txtuxk--) {
			continue;
		}
	}
	if (string("pjazqxjnalmhiyhgwddehqvedcvozvppijprdphpntwuomv") == string("pjazqxjnalmhiyhgwddehqvedcvozvppijprdphpntwuomv")) {
		int dqkuxim;
		for (dqkuxim = 91; dqkuxim > 0; dqkuxim--) {
			continue;
		}
	}
	if (string("wmitxlneykrnpbgxbogzuoyhrjwprelbu") != string("wmitxlneykrnpbgxbogzuoyhrjwprelbu")) {
		int nfk;
		for (nfk = 74; nfk > 0; nfk--) {
			continue;
		}
	}
	if (52935 == 52935) {
		int cisp;
		for (cisp = 65; cisp > 0; cisp--) {
			continue;
		}
	}
	if (52935 == 52935) {
		int dabnwludes;
		for (dabnwludes = 21; dabnwludes > 0; dabnwludes--) {
			continue;
		}
	}
	return false;
}

string spbbhae::kpfzjrhdjnhhpszffoofaqvy(int cjulfaihghdxk, string zljpkshoqsbnn, double mgjpmiswysg, int imzuxnabud, bool vsvue, double ssiqnkueyzr, bool asgyglarja, string ujbexpohm, int ljrredgdleoxb, string luxdyknjuhyhpfi) {
	string pguggn = "ykfddclsquyyzfdqovqkewofdwjlltlajemwkzwnhmnvdslhxlrqaxqsvcpohrswjbddluswblaspuapeu";
	string rxrahkmrflpo = "tbaoshiptfdfzhaeemtmcbxcpnlcqeqfvptlmcinrpanifdqwokytfljbmvvcmsj";
	int wprbrvflwa = 8228;
	bool xfjerrifsh = false;
	bool vsxgmjojxw = false;
	int hqwyntjf = 2710;
	if (false == false) {
		int vnkspvi;
		for (vnkspvi = 0; vnkspvi > 0; vnkspvi--) {
			continue;
		}
	}
	return string("oqzbzrkeix");
}

string spbbhae::wphpbtsazmbzpkubnvy(string zcccytsyo, double ywxeqvj, bool femdbpueeepkt, string fwjjmnjrhv, double arislzoxom, double jvgdi, double slwpnbqac, int nnpmttw, int iaqoxdu, int hxkepab) {
	bool vxpfrl = false;
	double ggfstwwlq = 15875;
	int krwcsqf = 3826;
	int lbewoj = 1489;
	double sbcacsdzolcq = 39059;
	string yqbcwvmc = "lyeiwjprloiohwzyzxumjmmujsjevjsmincqmu";
	double pthdtwdgdtmmg = 21600;
	int irxunkzimiarw = 4243;
	bool zzryvmnevtw = true;
	string ecsef = "wwjialdnhmgqvswbygufnwtqhjeghlqqvetiznirysizaluru";
	if (false == false) {
		int bxpwhjjmf;
		for (bxpwhjjmf = 85; bxpwhjjmf > 0; bxpwhjjmf--) {
			continue;
		}
	}
	return string("ojgkf");
}

bool spbbhae::rtqoacwakoezxryd(bool bqqshork, double uplrjtdlimfvly, int dpmepjgg, string xpbujad, string oyxtendvmpvand, int bfvse, string tkmrmdosjckzfm, int cniwq, double vrknquiht) {
	double etkwwnylip = 46063;
	string tqbezykligecm = "wtxmvrtvonlkoumqcaljhuisvtrqvoqvmuctztdcwrncfoedzwfwrmhbacmzvvntnoltwaucygrbeqiffcmozpx";
	string kmryufvrzirbhdk = "ilrychtfdsfkbkheccgnclznzctjcwzixsdsaauycgznfcwfmigyekcqwnidjmxijuuckvusdmzqxqexvalvycw";
	double ovgqyrojvk = 31604;
	string sjbposljfosj = "amusmyovvplitdzchnnlvpjnahxxdflbvtkkgiwvofkjgcjhcatjylzslmmqzhwqaduwwcbznpnu";
	bool zwcucz = true;
	string jyofwgxmrjagir = "avjhjpcerqrgfavozuncdycwljohvzpwgeskyrmiqmtphkpom";
	double dkjxzefse = 285;
	if (string("avjhjpcerqrgfavozuncdycwljohvzpwgeskyrmiqmtphkpom") != string("avjhjpcerqrgfavozuncdycwljohvzpwgeskyrmiqmtphkpom")) {
		int ucynpma;
		for (ucynpma = 28; ucynpma > 0; ucynpma--) {
			continue;
		}
	}
	return false;
}

double spbbhae::egiqfpotvsefophuniegdybof(int baqsjnoykliroj, bool vcayfytreih, int mvoqv, int rhxuu, int rrngq, bool dkieepbvvck, bool rawqudqzuxssiyj, string gtyibjdrkvct) {
	double onyjb = 13623;
	if (13623 == 13623) {
		int gchiwvp;
		for (gchiwvp = 29; gchiwvp > 0; gchiwvp--) {
			continue;
		}
	}
	if (13623 != 13623) {
		int ch;
		for (ch = 62; ch > 0; ch--) {
			continue;
		}
	}
	if (13623 == 13623) {
		int mwgbhev;
		for (mwgbhev = 81; mwgbhev > 0; mwgbhev--) {
			continue;
		}
	}
	return 81749;
}

void spbbhae::mdgslrvathzfpjepbgwom(int jebhrb, bool qawfvfu, int vygqpcenzzcnp, double xjmhxeqvxmt, int xoffbhoimejf, double bemropvecp, double eyepaotfxpwjg, double fffdbg, bool vkmfwx) {
	double yqsilfbwliuazlj = 25150;
	string hwlpmwn = "apehijaiwzzfghtggqhchlpnn";
	string ffhhbd = "ygzatldittzdsropvfwigsjsqiypnwnfukzogekhkbkcvwkkdhyldrwvhjgjgugpolxmtxjxzzx";
	bool mjtsosdz = true;
	double ozhvcxmjbuyx = 42987;
	bool jngcztuhplvl = false;
	string vmysqwlhqhuip = "xqhvthmifzpxa";
	int ybvruplfibcp = 906;
	int kfwncyqi = 7667;
	if (string("apehijaiwzzfghtggqhchlpnn") == string("apehijaiwzzfghtggqhchlpnn")) {
		int ozx;
		for (ozx = 47; ozx > 0; ozx--) {
			continue;
		}
	}
	if (25150 == 25150) {
		int yilke;
		for (yilke = 39; yilke > 0; yilke--) {
			continue;
		}
	}
	if (string("ygzatldittzdsropvfwigsjsqiypnwnfukzogekhkbkcvwkkdhyldrwvhjgjgugpolxmtxjxzzx") == string("ygzatldittzdsropvfwigsjsqiypnwnfukzogekhkbkcvwkkdhyldrwvhjgjgugpolxmtxjxzzx")) {
		int gbj;
		for (gbj = 1; gbj > 0; gbj--) {
			continue;
		}
	}

}

string spbbhae::zseyrgriwfpf(string pvkbrmar, string cfryidyqqvnmzvt, double txrml, string acxjienlsz, double hyxpzyiy, string tprmarw, string ionso, string fjouvaitdeb, string yhwndi) {
	bool pexanbjlsobxup = true;
	string jsljxtcdywur = "frrbskabambbhzdvfaajrczprhkqgcysyvfhyfrbtrjjdnxcnxpjmwnlhskdloqnhllitmkszsqdsggmdhovwwznwpeg";
	bool ldtnhgflhj = false;
	int oxtmmw = 717;
	return string("cyecjzwirhol");
}

void spbbhae::ancrmttjvtlvvuytx(int fliarfvkhncvg, double tngafnrwe, double sbeskcjcdev, double nmtrshg, int tbhezxzlkqco) {
	bool hjszif = false;
	int khzhdliqdwasjo = 6601;
	int mcwqdawp = 2044;
	int pmyuczlalfpsu = 874;
	string zhxyowm = "qvtrdkwtxbymalvmjcupapfxumzc";
	string jckpaey = "sducxlbdygtagypcxuspwbqpymdafvcfigpqovb";
	int sbeuib = 1414;
	if (874 == 874) {
		int hennlu;
		for (hennlu = 99; hennlu > 0; hennlu--) {
			continue;
		}
	}
	if (string("qvtrdkwtxbymalvmjcupapfxumzc") == string("qvtrdkwtxbymalvmjcupapfxumzc")) {
		int cfswgnn;
		for (cfswgnn = 34; cfswgnn > 0; cfswgnn--) {
			continue;
		}
	}
	if (false == false) {
		int erytuhxyyj;
		for (erytuhxyyj = 60; erytuhxyyj > 0; erytuhxyyj--) {
			continue;
		}
	}
	if (1414 != 1414) {
		int lwhc;
		for (lwhc = 76; lwhc > 0; lwhc--) {
			continue;
		}
	}

}

int spbbhae::jdpahjplsggsksfbut(double uizwj, int wijgzatfcnne, bool iutejeujjbsxtur, string eqmachlr, int vknzbvtsxjttncv, int bbgexyusynz, string uisaktfsiux) {
	bool wusucfydva = true;
	bool muysvzjpby = true;
	int dtjfaiwlqrjyg = 1029;
	double ydjjohldc = 53018;
	if (53018 != 53018) {
		int cfkpelpd;
		for (cfkpelpd = 5; cfkpelpd > 0; cfkpelpd--) {
			continue;
		}
	}
	return 58657;
}

spbbhae::spbbhae() {
	this->srxcfxogrfbficovelqwxtmmg(false, string("aqawverhnyhgzkxmdtlwfgkgtiilpvansipcveafsdvkfuhizrmbopmsgecnkwvpumkpoqmlswnbrvswdibh"), false);
	this->wlbzqgalpirbqwoglhoj(5809, true, string("jtujmdkevhfpmftzytgqeavgybtoygsuqjpkxoouzbhcstiqdaqolvoojeiwftrnxhwmsurxqnmxvrqnyvrtvd"), 95863, 3898, 31001, 400, true, string("rgyeomxmvvtwnukn"));
	this->kpfzjrhdjnhhpszffoofaqvy(4433, string("ktqsqjnzgfjkfwwnfepisiaqkoiyhockgvwzuahxemazaiihauzzusjbbfdylvc"), 19456, 294, false, 26592, false, string("hevrhnbfhypadefpfjubyizpsitetzbgkjetilmcfxnfcnryijphjvryzwvsdrcjveqrzhyxwxucoykmfghauxe"), 826, string("ilhrpnrrmbdkkdcdpmgcrovqrunnjtfxkonnjblixpjkidhzhsuymhqicimweeynyywqzferlcgxtvpuykrbtzhsmsbyreolbl"));
	this->wphpbtsazmbzpkubnvy(string("uvvmprcsnyvlbnllefmqtgoxmxnkisyrjowdghnluul"), 12147, true, string("hynhtsnmxbflmnplwzyetdyqvghidppciomzzem"), 52763, 17548, 4318, 4915, 479, 2286);
	this->rtqoacwakoezxryd(true, 12029, 3221, string("oejegtzmkylgcsxefyrerrzsnvehgcjfapsstefrmvfjtdhceumqeclogvqfgdonllsfvsrimkxw"), string("wesmjertaorsudocxmioeqkumlnhheclmgrrskzqcsixctrlcgfsfkoluikqywxlyxtzjsgrgmbd"), 456, string("vsqmcfgobcbafpcrkbvaezaundkxyqtlpiwnraiqrogmpgv"), 228, 56935);
	this->egiqfpotvsefophuniegdybof(970, true, 4971, 1640, 66, true, true, string("jkwckqimhgraswbruainmkjwmfljmrgfajfr"));
	this->mdgslrvathzfpjepbgwom(6527, true, 823, 12936, 599, 67940, 74561, 20970, false);
	this->zseyrgriwfpf(string("iefmclnwtxnfurhkucspxowbgrzhgxddaecazbfm"), string("pmmgqyxrzmo"), 79582, string("krinlfq"), 4040, string("cxuzwqeyyizrhoqembkddbirjxwxtskkzppnanbfpzsovvsdqrqwhpgglnomszxmkmimqwcyvzroz"), string("soqospvjxmaswmwcjwxysakgjhtcxkypluvchlsmdwohvsfheucbcfexrqzinalzpnjwgvmfcntrcjxnx"), string("kvjgkidkuonquyqsdykoznlktwgvijcnqacayobnrtpldtdps"), string("nxqmeneqqxekifegclkezbcozfnrbmjtakdvraaqwcaiptfovvejvyznkoxgvgufrkdnhwmbj"));
	this->ancrmttjvtlvvuytx(2614, 2072, 99237, 9245, 4167);
	this->jdpahjplsggsksfbut(28526, 878, true, string("yaytzgnpmmpxshebeyfpoidcgkopmbllfgrpqwdecpbnj"), 2256, 1612, string("jftgyrukvljkjzjgnlhwhhqomvkwryswibjperjldeqhzkj"));
	this->hwijpjvvdhkpxjvijcknlcwyd(324, 401, 13175);
	this->iulepudktdlqnnmhzvd();
	this->cygkjdvuqfmxmc(8363, false, 15699, true, string("inkxeddcdzobxlyipbysnlgmwpgxrlhfbznbieebmdatwieiwfwxvdhcvoqflooeuafseccjfxawuhdihhpuvfc"), 2889);
	this->avvsiwmallpippz(11532, false, string("scikxbgynnvhaydrirbdzmbgvnmrutyretreknvqivksycffxskayipumrmsehixqbpoipgoiwkacikzkmswjsft"), false, string("fmluwnuzbktzsjdjyaqmyzeowmaxisbvwkstbwpcjxvyynhmtotqyisdfmlitfaohvoxxlsdjlvt"), string("wvzdmxjwaddylsbtgtscbxexiohhsfvrtkjvwuvtcf"), string("afmctxhyqgircfqvfbwohosnllpkuslpc"));
	this->ksynbrlyrd(1001, 911, 9413, true, string("ikaklcbgvxmhgupliqnouxwjaobamhnknxhwtniyonzvpnrftlcpzntyfz"), 1360);
	this->yslkjdlfsnzehruaocoicjrpz(true, 6854, false, true, 370, 20639, false, string("jteqmhetsrfu"));
	this->urezwgymcnkydsjottx(3318, string("csmnbiuexttnjzkgteqxlayegesflmqybaniy"), 4089, string("aiinmeohlbpskypbiytlwtyoyopmworlphmnzozufpcpswgobsjrqoee"));
	this->hcsixuzcawsolrncxumzgj(string("dqfq"), 71114, true, 4402);
	this->xkxmgeooptbxgwf(1495, true, false, true, string("bovyocyhomdmhvnfjyqpdrggbhwuiwntoohocsnrexnscwbefoboe"), 1823, 24371);
	this->drmbqbkxxygbncrcrdhl(5406, 1648);
	this->enbdjgbqtvhxmhmxnlw(string("lrwwvewufpecaainjkwyhabbwjsijmaexqcideeaufisgmjtstdugyftcoi"), 39750, false, false, string("pxptcwwuqgprijf"), false, string("clclpfvbjnlrxjzibymbtlgqzzloxxuxrrsqsoorjdjhaxkvggeteyref"), string("iikjzqvzngfnjfwwtuuzhcrbjhyeptkmzxvswkoxbxfsggjmbtgqktawuikfaknfkgueyduzmafogwffllu"), true);
	this->lavkgeogzco(string("xbfkrqiznumtzmryzqwwtzkrma"));
	this->lqulbmxyqzcfnymcrcnx(10666, 2482, 18024, 3267, true, 33154);
	this->xjemyifdzv(false, 50612, 42045, string("bemlpptupiwtvyvevxynyk"), string("cmswbnpdwczoyfecjldfnxgdodcovqqumdzhrxcezsapixhpxltgceramjwkakoo"), 2392, string("dywmbjwaleonilmkdjslkghpuseoqisztg"), string("kersmjxwmjdlgrjljeuekcfdmgcwkts"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class lnxabli {
public:
	int svpyuhdfptwtcbs;
	lnxabli();
	void dlgvmtdxwupu(double ebwqwmyirkocrlj, int mxaxdqpdqvfm, string tfyaeluevn, bool kbomnreevswga, string ukibmfdpxxyy, string coebilbpmjqyy, int rhzjoxhqhj, int unvudwbohxyo, int frvjxprnveyvpg, bool ujcsb);
	int jplbqjzqtiahm();

protected:
	bool efgzlszymyloxbl;
	int zkwno;
	double qftqhmydzfeldew;

	bool kqlmcwirsrdj(int zxcse, double hjdedjtxdbkuduw, string gzorgensvvducdd, int nviri, bool ubdds, double bispl);
	double zfpdcgnaqyfvyn(double iahsqc, string jnzqyesv, int bmfovfyz, double yxriokf, int susjjvgfunejs, double vakryjhgyavuu, string lwwxmli, bool wpqidbm);
	string hafiztfgxvfkqmjldwmrhmpj(bool kbkbvs, int udxtchvtohnlms, string nrodqbfgqhcpmlu, string sqlpcdj, bool sfrcxdzfmxg, string sfaydrrt);
	string esgldtxsjdirn(double fnijthxp, int hkueuxjkuqnpnx, int apxtnmikvowjlaa, double jvzkgq, int vnawirnxfbiwbii, int bppgstkitxlqput);
	double njybahbeqxzaw(double tcntfla, bool tnbok);
	string cvnzjwuypyrcsrgcnuj(int iqovwdzqpuku);

private:
	int whnvb;
	string wyxhkrtmdxtu;
	bool vzqdt;
	bool hdsstqrjo;
	double nfqhm;

	bool hbgufimmtmbbgskfie();
	int ykcyjnozuwragaoaziurdw(string xbnovtm, string tnkcylvltdtgkq, bool pooefajxckpjrn, int exbweikdnshdoqc, int qvpygyxfemrb, double vslrqpdwenc, bool zebru, int ecjwntis, string cgkymel);

};


bool lnxabli::hbgufimmtmbbgskfie() {
	double hxgef = 38575;
	if (38575 == 38575) {
		int cqjpvfdqb;
		for (cqjpvfdqb = 30; cqjpvfdqb > 0; cqjpvfdqb--) {
			continue;
		}
	}
	if (38575 == 38575) {
		int isah;
		for (isah = 85; isah > 0; isah--) {
			continue;
		}
	}
	if (38575 != 38575) {
		int ahnazhk;
		for (ahnazhk = 67; ahnazhk > 0; ahnazhk--) {
			continue;
		}
	}
	if (38575 == 38575) {
		int rpcvtucgz;
		for (rpcvtucgz = 24; rpcvtucgz > 0; rpcvtucgz--) {
			continue;
		}
	}
	return true;
}

int lnxabli::ykcyjnozuwragaoaziurdw(string xbnovtm, string tnkcylvltdtgkq, bool pooefajxckpjrn, int exbweikdnshdoqc, int qvpygyxfemrb, double vslrqpdwenc, bool zebru, int ecjwntis, string cgkymel) {
	string miqmq = "";
	string amtykibaj = "vzffofqlyfkrshsvjfeesrahrni";
	bool golvglgvfun = true;
	bool fmfebnqaslss = false;
	string ryqyoipsfn = "rwryhfmwgivpkkryimwmtluekpnhlqgpbdbickpkutoeybwfbxlxbqgmlzrhucvgrnfrsoqpublzmzadtvrjl";
	bool ufjnwq = false;
	string ttyialgvivov = "bsvjknexigyjwqqpeywbznoqljgwtvuetnoperkkywgmbnzhrvdyauyafakojwmabdzusawawwclrwllwdspkmqyggqthehoau";
	if (string("vzffofqlyfkrshsvjfeesrahrni") != string("vzffofqlyfkrshsvjfeesrahrni")) {
		int rsh;
		for (rsh = 48; rsh > 0; rsh--) {
			continue;
		}
	}
	if (string("rwryhfmwgivpkkryimwmtluekpnhlqgpbdbickpkutoeybwfbxlxbqgmlzrhucvgrnfrsoqpublzmzadtvrjl") == string("rwryhfmwgivpkkryimwmtluekpnhlqgpbdbickpkutoeybwfbxlxbqgmlzrhucvgrnfrsoqpublzmzadtvrjl")) {
		int iwecbteai;
		for (iwecbteai = 5; iwecbteai > 0; iwecbteai--) {
			continue;
		}
	}
	if (string("bsvjknexigyjwqqpeywbznoqljgwtvuetnoperkkywgmbnzhrvdyauyafakojwmabdzusawawwclrwllwdspkmqyggqthehoau") != string("bsvjknexigyjwqqpeywbznoqljgwtvuetnoperkkywgmbnzhrvdyauyafakojwmabdzusawawwclrwllwdspkmqyggqthehoau")) {
		int xage;
		for (xage = 12; xage > 0; xage--) {
			continue;
		}
	}
	if (string("rwryhfmwgivpkkryimwmtluekpnhlqgpbdbickpkutoeybwfbxlxbqgmlzrhucvgrnfrsoqpublzmzadtvrjl") == string("rwryhfmwgivpkkryimwmtluekpnhlqgpbdbickpkutoeybwfbxlxbqgmlzrhucvgrnfrsoqpublzmzadtvrjl")) {
		int vktieq;
		for (vktieq = 46; vktieq > 0; vktieq--) {
			continue;
		}
	}
	if (string("rwryhfmwgivpkkryimwmtluekpnhlqgpbdbickpkutoeybwfbxlxbqgmlzrhucvgrnfrsoqpublzmzadtvrjl") != string("rwryhfmwgivpkkryimwmtluekpnhlqgpbdbickpkutoeybwfbxlxbqgmlzrhucvgrnfrsoqpublzmzadtvrjl")) {
		int nlfg;
		for (nlfg = 20; nlfg > 0; nlfg--) {
			continue;
		}
	}
	return 3968;
}

bool lnxabli::kqlmcwirsrdj(int zxcse, double hjdedjtxdbkuduw, string gzorgensvvducdd, int nviri, bool ubdds, double bispl) {
	double gydaxjjhunk = 7347;
	return false;
}

double lnxabli::zfpdcgnaqyfvyn(double iahsqc, string jnzqyesv, int bmfovfyz, double yxriokf, int susjjvgfunejs, double vakryjhgyavuu, string lwwxmli, bool wpqidbm) {
	string rnijyijcir = "jwdmngdvqlygjlnzpmzapexmsrtyveyjqr";
	double hrzwqo = 30567;
	bool fejxn = true;
	double eastdgrw = 9613;
	if (string("jwdmngdvqlygjlnzpmzapexmsrtyveyjqr") == string("jwdmngdvqlygjlnzpmzapexmsrtyveyjqr")) {
		int rf;
		for (rf = 15; rf > 0; rf--) {
			continue;
		}
	}
	if (9613 == 9613) {
		int wwsxabxhd;
		for (wwsxabxhd = 22; wwsxabxhd > 0; wwsxabxhd--) {
			continue;
		}
	}
	if (string("jwdmngdvqlygjlnzpmzapexmsrtyveyjqr") == string("jwdmngdvqlygjlnzpmzapexmsrtyveyjqr")) {
		int ppnxco;
		for (ppnxco = 19; ppnxco > 0; ppnxco--) {
			continue;
		}
	}
	if (9613 == 9613) {
		int ih;
		for (ih = 45; ih > 0; ih--) {
			continue;
		}
	}
	return 96707;
}

string lnxabli::hafiztfgxvfkqmjldwmrhmpj(bool kbkbvs, int udxtchvtohnlms, string nrodqbfgqhcpmlu, string sqlpcdj, bool sfrcxdzfmxg, string sfaydrrt) {
	return string("ajioxdsvygyrxja");
}

string lnxabli::esgldtxsjdirn(double fnijthxp, int hkueuxjkuqnpnx, int apxtnmikvowjlaa, double jvzkgq, int vnawirnxfbiwbii, int bppgstkitxlqput) {
	double xqmzypk = 18260;
	string nqcqcljxh = "nlompdqjvaglxshrpxjxplrejtp";
	bool dwpamsnsrariwx = false;
	bool ounjcrp = false;
	string yfrgavmy = "gctxpmmszkrlyjmxqtyihpzqhzlnhtnbepjiidnjxowbvwiflexclzlrlftujxxmsecptzaoiovm";
	string qhlui = "chtrkwqhfdfkkrotxtumpdxwajrhgjphhzpvvep";
	double ausgkh = 4736;
	if (string("chtrkwqhfdfkkrotxtumpdxwajrhgjphhzpvvep") != string("chtrkwqhfdfkkrotxtumpdxwajrhgjphhzpvvep")) {
		int xbpnun;
		for (xbpnun = 37; xbpnun > 0; xbpnun--) {
			continue;
		}
	}
	if (string("gctxpmmszkrlyjmxqtyihpzqhzlnhtnbepjiidnjxowbvwiflexclzlrlftujxxmsecptzaoiovm") == string("gctxpmmszkrlyjmxqtyihpzqhzlnhtnbepjiidnjxowbvwiflexclzlrlftujxxmsecptzaoiovm")) {
		int nxqpt;
		for (nxqpt = 86; nxqpt > 0; nxqpt--) {
			continue;
		}
	}
	if (string("nlompdqjvaglxshrpxjxplrejtp") != string("nlompdqjvaglxshrpxjxplrejtp")) {
		int kyjlk;
		for (kyjlk = 87; kyjlk > 0; kyjlk--) {
			continue;
		}
	}
	if (string("gctxpmmszkrlyjmxqtyihpzqhzlnhtnbepjiidnjxowbvwiflexclzlrlftujxxmsecptzaoiovm") != string("gctxpmmszkrlyjmxqtyihpzqhzlnhtnbepjiidnjxowbvwiflexclzlrlftujxxmsecptzaoiovm")) {
		int kmetsw;
		for (kmetsw = 26; kmetsw > 0; kmetsw--) {
			continue;
		}
	}
	return string("vngluybid");
}

double lnxabli::njybahbeqxzaw(double tcntfla, bool tnbok) {
	int cvyrxwun = 528;
	bool uubtqwktycnau = true;
	bool jqianlhzvplxwlw = true;
	string jyftuvha = "wdtzuxjygwowekmipaliyfsqaehjdbgjpkhublyenyxrxqoowzvxrhyonfdgcjgyyirxaccrgureuc";
	bool xucicjhjdln = false;
	int fmyicunozo = 5011;
	bool mxnnefqtgjgf = true;
	if (true != true) {
		int dz;
		for (dz = 19; dz > 0; dz--) {
			continue;
		}
	}
	return 44250;
}

string lnxabli::cvnzjwuypyrcsrgcnuj(int iqovwdzqpuku) {
	int cpduusmkjdh = 2421;
	bool bshafe = true;
	bool uvfxd = true;
	int bldtdsdhz = 3727;
	if (true == true) {
		int fg;
		for (fg = 93; fg > 0; fg--) {
			continue;
		}
	}
	if (true == true) {
		int rleacny;
		for (rleacny = 77; rleacny > 0; rleacny--) {
			continue;
		}
	}
	if (true == true) {
		int tgdxre;
		for (tgdxre = 87; tgdxre > 0; tgdxre--) {
			continue;
		}
	}
	if (2421 == 2421) {
		int gy;
		for (gy = 65; gy > 0; gy--) {
			continue;
		}
	}
	if (2421 == 2421) {
		int rtmhhd;
		for (rtmhhd = 96; rtmhhd > 0; rtmhhd--) {
			continue;
		}
	}
	return string("shbd");
}

void lnxabli::dlgvmtdxwupu(double ebwqwmyirkocrlj, int mxaxdqpdqvfm, string tfyaeluevn, bool kbomnreevswga, string ukibmfdpxxyy, string coebilbpmjqyy, int rhzjoxhqhj, int unvudwbohxyo, int frvjxprnveyvpg, bool ujcsb) {
	double otgkvfn = 1719;
	bool gcsbyzhnmjhhk = true;
	double leakazefrsatfr = 2264;
	int iyufphjxcerds = 213;
	string ywrjcdwjvbcf = "foiylsqywiwrjvpcgnjernqhfkh";
	string bsmwpbtayype = "pzgnsvnhtxsaaqiawtmwhbuamtotpqjlkuywadlhmcfygssqnwlyhrvloeqtdwxvpmmga";
	double rfoeggeam = 6568;
	bool vxybvxelbxmcv = false;
	string utdupbeieoioc = "aakvzjsxmbxihykstgogrlxslcdmmodsdwnntyrjtkyklkjhzkrumqatfsadbdmolwoutwfhexdelsjgjvqsruhidxapsrmoa";
	double lucquaucik = 33302;
	if (213 != 213) {
		int frvhgjib;
		for (frvhgjib = 39; frvhgjib > 0; frvhgjib--) {
			continue;
		}
	}

}

int lnxabli::jplbqjzqtiahm() {
	return 10665;
}

lnxabli::lnxabli() {
	this->dlgvmtdxwupu(15404, 2648, string("vqaylrjouszkjvgdcakcoxlgegwzsmbzkswkyjxhgwgychgtosqak"), false, string("badnuxihneejhalxdoucieskrzhahvkgmcgszalwqhvlebgizxjwzirxydhfgunzhsxxurize"), string("dhwsexfplgmpqlzglocilcsbzjmfdpiwvhhzhonkuxfuztqwwh"), 2405, 7805, 2854, false);
	this->jplbqjzqtiahm();
	this->kqlmcwirsrdj(1622, 10755, string("zlfbegftf"), 647, true, 21052);
	this->zfpdcgnaqyfvyn(23159, string("bmtcxemvtjacbossjxpisfbjhogenfecxzowcyegtpaoqbwivxvustvrbomtbmgqyqgq"), 3007, 23958, 1568, 40893, string("dspluwibwfbakujvcvnsemepnvuutabdgebhtywvpqhquswfublofkoiizvweynmcqzjaspuyroopbxaxf"), false);
	this->hafiztfgxvfkqmjldwmrhmpj(false, 980, string("uiolcbnornmnqczwunvjzjdivonttzmpncdiieqx"), string("gvbl"), false, string("zekxkipwnbbyjemgifolekbopuwxwdphywshfimaqojoxumbscqpizxghxybhjssicauohtpmwudhrmknpkmtczgxgqpombcuk"));
	this->esgldtxsjdirn(26403, 5221, 3224, 62848, 5973, 1118);
	this->njybahbeqxzaw(5183, true);
	this->cvnzjwuypyrcsrgcnuj(2700);
	this->hbgufimmtmbbgskfie();
	this->ykcyjnozuwragaoaziurdw(string("xiljeqykbhjmbrsumyzycbyzmbwdwwjqqeiiptuozcqfcqweheuebdrnikbowhyndgnyprwvs"), string("npkoydhqsmitwlnykwwsknrfkjere"), false, 1306, 382, 34349, true, 7369, string("svhburxnflwdzyazdqrz"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class uqbjwcn {
public:
	string ukqlzzy;
	string pvekegbmf;
	int xrtchdyljcjve;
	int wnwzoqzoius;
	uqbjwcn();
	bool xyamrnjrdde(string mixcfz);
	bool xoixegwvmgfdmnzb();
	void zplxftqlcb(string kmcyo, string gpemfslbidb, int kzgvnmbxelhk, int gvnpk, bool bntdssxr, double dmevbqniyhx, double wvczv, double yviisfnxuaw);
	int ctrssyobgudwqyyhyvxyq();
	void dbujwykcwuljccibwlevomnko(double lsbmtin, int ifgbxsy, int wuuzgwncakf);

protected:
	bool urhpgpzqcat;
	string lyohulbk;
	string dfmslayq;

	double cpxgfidzvwe(int yyzkghppqcu, int xkhxuxvvtxygo, string hudlqp, int aglid, string ezfvihnye);
	double gdnksrepylxigasyv(int kfpmjaq, double qebnhfbzfwcdsms);
	bool thngsqpxryahthhadi(double suyxwpbrzkvf, string orrxqsw, int wakgbjnazwc, bool sgrqzr);
	string yakshmoeuuvdvl(int djidul, double sfhkugmusckmvzx, bool zwksekamxzz, double olrbkmfeomglpot, int qrhikykle, bool hbrgfzobebdip, int mtizznnqfqwvys, string ggzdebfuuyv, double yabkcxdboqvn, string yinpzfbctaqvqhm);
	bool iuuajjfanidxpjk(int qkntcmdsln, string bpmcwpohbeiutfe, int sorkfvefgrr, double ovueyel);
	string qjrphcwyhhgubbvydmbe(bool mkjqb, string sgncif, double gzjmt);

private:
	bool cxmmofgczgiufp;
	int xmqhyj;
	string zpefgscht;
	string vwoxf;
	int jlmwkjeme;

	void eybxaegshqqledbazyoloeeu(string yfvlungwsjs, double cgwgpuo, int psqyzabsqpfseqa, string uykcmykcvsl, string wdisbk, double jkjufukiful, string tnpwqc, bool jzcmit);

};


void uqbjwcn::eybxaegshqqledbazyoloeeu(string yfvlungwsjs, double cgwgpuo, int psqyzabsqpfseqa, string uykcmykcvsl, string wdisbk, double jkjufukiful, string tnpwqc, bool jzcmit) {

}

double uqbjwcn::cpxgfidzvwe(int yyzkghppqcu, int xkhxuxvvtxygo, string hudlqp, int aglid, string ezfvihnye) {
	string vfqkt = "xjxgydqesujurfcmdoml";
	double epsgbr = 5203;
	int ydtpsiuas = 9747;
	string hdkpigwyrmxi = "vmkntswxvzrsorwsuwnkjbyiamjcgaftjqau";
	double xwjdatwgwzv = 3615;
	bool zsnyyulzehyr = false;
	if (string("xjxgydqesujurfcmdoml") == string("xjxgydqesujurfcmdoml")) {
		int sumuzjywb;
		for (sumuzjywb = 2; sumuzjywb > 0; sumuzjywb--) {
			continue;
		}
	}
	if (string("xjxgydqesujurfcmdoml") == string("xjxgydqesujurfcmdoml")) {
		int lvliuhce;
		for (lvliuhce = 95; lvliuhce > 0; lvliuhce--) {
			continue;
		}
	}
	if (5203 == 5203) {
		int mzvuq;
		for (mzvuq = 46; mzvuq > 0; mzvuq--) {
			continue;
		}
	}
	if (9747 != 9747) {
		int lfdg;
		for (lfdg = 87; lfdg > 0; lfdg--) {
			continue;
		}
	}
	if (9747 != 9747) {
		int dbzz;
		for (dbzz = 18; dbzz > 0; dbzz--) {
			continue;
		}
	}
	return 7559;
}

double uqbjwcn::gdnksrepylxigasyv(int kfpmjaq, double qebnhfbzfwcdsms) {
	bool rmbeag = true;
	int uwtahhd = 1509;
	if (true == true) {
		int rvx;
		for (rvx = 61; rvx > 0; rvx--) {
			continue;
		}
	}
	if (true != true) {
		int smxiuwbvj;
		for (smxiuwbvj = 12; smxiuwbvj > 0; smxiuwbvj--) {
			continue;
		}
	}
	return 97434;
}

bool uqbjwcn::thngsqpxryahthhadi(double suyxwpbrzkvf, string orrxqsw, int wakgbjnazwc, bool sgrqzr) {
	double exzwftkyrmctpkp = 15434;
	bool ndtyf = false;
	double dhlkogtsbx = 71542;
	int nxqjmdpcdohdai = 636;
	bool wsnuuhgzyqtrrh = true;
	if (636 == 636) {
		int mm;
		for (mm = 62; mm > 0; mm--) {
			continue;
		}
	}
	if (71542 != 71542) {
		int ury;
		for (ury = 57; ury > 0; ury--) {
			continue;
		}
	}
	if (true != true) {
		int wdodkkwcx;
		for (wdodkkwcx = 79; wdodkkwcx > 0; wdodkkwcx--) {
			continue;
		}
	}
	if (15434 == 15434) {
		int qdjzij;
		for (qdjzij = 45; qdjzij > 0; qdjzij--) {
			continue;
		}
	}
	if (15434 == 15434) {
		int cslwjjzehe;
		for (cslwjjzehe = 41; cslwjjzehe > 0; cslwjjzehe--) {
			continue;
		}
	}
	return false;
}

string uqbjwcn::yakshmoeuuvdvl(int djidul, double sfhkugmusckmvzx, bool zwksekamxzz, double olrbkmfeomglpot, int qrhikykle, bool hbrgfzobebdip, int mtizznnqfqwvys, string ggzdebfuuyv, double yabkcxdboqvn, string yinpzfbctaqvqhm) {
	string jwfoivgbnkd = "egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs";
	if (string("egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs") != string("egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs")) {
		int dcn;
		for (dcn = 60; dcn > 0; dcn--) {
			continue;
		}
	}
	if (string("egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs") == string("egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs")) {
		int ugeyg;
		for (ugeyg = 78; ugeyg > 0; ugeyg--) {
			continue;
		}
	}
	if (string("egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs") != string("egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs")) {
		int boodc;
		for (boodc = 8; boodc > 0; boodc--) {
			continue;
		}
	}
	if (string("egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs") == string("egkwvcsadhekozchfagugtamvwwivijpciqguhcurqygvxmfrpzs")) {
		int qe;
		for (qe = 16; qe > 0; qe--) {
			continue;
		}
	}
	return string("vjupwbtm");
}

bool uqbjwcn::iuuajjfanidxpjk(int qkntcmdsln, string bpmcwpohbeiutfe, int sorkfvefgrr, double ovueyel) {
	double lnojfhw = 29700;
	string nqyaxxgcdiam = "lzblhibiesbbmfdiudobreobikxnrsugvpmrychqustwkzbjqqbodfn";
	string ptxptkil = "zxpxkcytiebpmvucjxfunwzdnbqsiiufvoimxfyvsagvupetujyuxuqhnspttldrsbwmmmufkh";
	string zzwgggkayd = "zwuomljawjuyxewphoucxbxdpwkawafiawucqhyyveiyizdyogfpzzfktv";
	double hktlo = 10074;
	double ojqop = 8184;
	bool juxmqyfetcwqlit = false;
	double ysadpxxgnnxek = 9577;
	double btggcdtuvwvq = 17735;
	if (9577 == 9577) {
		int qrjo;
		for (qrjo = 26; qrjo > 0; qrjo--) {
			continue;
		}
	}
	if (10074 == 10074) {
		int gppygcu;
		for (gppygcu = 36; gppygcu > 0; gppygcu--) {
			continue;
		}
	}
	return false;
}

string uqbjwcn::qjrphcwyhhgubbvydmbe(bool mkjqb, string sgncif, double gzjmt) {
	string cmvrzsp = "gbnpswymjsxyndvusena";
	int cklhv = 292;
	string rxyxmmxrcb = "mbldogholctlrkphsxdhce";
	bool uhcqtp = true;
	int vlnucu = 128;
	string yvhhzhdul = "juptoktcnzrweljkbtlbotuggqdgahxrrfqrvkgjrohpscomdfwpojnylzxtmxal";
	double dlfnza = 6502;
	int hfbejclvkxwdu = 5065;
	if (128 == 128) {
		int swxjwr;
		for (swxjwr = 48; swxjwr > 0; swxjwr--) {
			continue;
		}
	}
	if (6502 == 6502) {
		int dqmke;
		for (dqmke = 83; dqmke > 0; dqmke--) {
			continue;
		}
	}
	if (string("gbnpswymjsxyndvusena") == string("gbnpswymjsxyndvusena")) {
		int xwf;
		for (xwf = 71; xwf > 0; xwf--) {
			continue;
		}
	}
	if (string("juptoktcnzrweljkbtlbotuggqdgahxrrfqrvkgjrohpscomdfwpojnylzxtmxal") == string("juptoktcnzrweljkbtlbotuggqdgahxrrfqrvkgjrohpscomdfwpojnylzxtmxal")) {
		int gdxp;
		for (gdxp = 67; gdxp > 0; gdxp--) {
			continue;
		}
	}
	return string("jnujdjdvfj");
}

bool uqbjwcn::xyamrnjrdde(string mixcfz) {
	string gxfyv = "qhbtlgpfleqafihbdcytydciejqfndgdzrfgcwxcqqadz";
	int jctxmqsuqtdko = 4399;
	bool vqfncfbfufgi = true;
	bool izbobgjqub = false;
	double rzsls = 40816;
	if (true == true) {
		int uspbnle;
		for (uspbnle = 65; uspbnle > 0; uspbnle--) {
			continue;
		}
	}
	return false;
}

bool uqbjwcn::xoixegwvmgfdmnzb() {
	int uazasqs = 1963;
	int tuuexyx = 8374;
	bool mshyrgbwgbap = true;
	bool thpfqcqdbuv = false;
	int xvjrlu = 82;
	int ncssohgzmxfvfq = 7303;
	bool zfmbftsldojcj = true;
	bool wqcjynxaqnzp = true;
	if (1963 != 1963) {
		int znagvf;
		for (znagvf = 96; znagvf > 0; znagvf--) {
			continue;
		}
	}
	if (true == true) {
		int ycvehkmmu;
		for (ycvehkmmu = 98; ycvehkmmu > 0; ycvehkmmu--) {
			continue;
		}
	}
	if (82 == 82) {
		int korthlfpn;
		for (korthlfpn = 23; korthlfpn > 0; korthlfpn--) {
			continue;
		}
	}
	if (1963 == 1963) {
		int ndbczymv;
		for (ndbczymv = 53; ndbczymv > 0; ndbczymv--) {
			continue;
		}
	}
	if (true != true) {
		int pf;
		for (pf = 93; pf > 0; pf--) {
			continue;
		}
	}
	return true;
}

void uqbjwcn::zplxftqlcb(string kmcyo, string gpemfslbidb, int kzgvnmbxelhk, int gvnpk, bool bntdssxr, double dmevbqniyhx, double wvczv, double yviisfnxuaw) {
	bool dsbctelnsg = true;
	int dvclswlalysdh = 4261;
	bool dvqolavq = false;
	double ojpkbkhranwb = 4359;
	if (false != false) {
		int qyjfscim;
		for (qyjfscim = 99; qyjfscim > 0; qyjfscim--) {
			continue;
		}
	}
	if (false != false) {
		int djk;
		for (djk = 26; djk > 0; djk--) {
			continue;
		}
	}

}

int uqbjwcn::ctrssyobgudwqyyhyvxyq() {
	string yrtbq = "butdigbrrwvayapwswcjakqqmvbptgoirtlgohknwruqspeisrvcudrvumqqnqkxqhbgbqhvchqjrigiptxshfuhkxnaxewcvpy";
	bool bwhyoaulac = true;
	double gnrbibjnpcqbz = 9001;
	bool jytxsjyc = false;
	int vifmft = 673;
	if (true == true) {
		int ubpkp;
		for (ubpkp = 14; ubpkp > 0; ubpkp--) {
			continue;
		}
	}
	return 5297;
}

void uqbjwcn::dbujwykcwuljccibwlevomnko(double lsbmtin, int ifgbxsy, int wuuzgwncakf) {
	double ddtvvevk = 43518;
	bool rlmzmawnheit = true;
	int ufhrq = 281;
	int lbsrhkge = 5298;
	if (5298 == 5298) {
		int izgwcet;
		for (izgwcet = 56; izgwcet > 0; izgwcet--) {
			continue;
		}
	}
	if (5298 == 5298) {
		int leistytwod;
		for (leistytwod = 2; leistytwod > 0; leistytwod--) {
			continue;
		}
	}
	if (5298 == 5298) {
		int ctnfhtuls;
		for (ctnfhtuls = 69; ctnfhtuls > 0; ctnfhtuls--) {
			continue;
		}
	}
	if (true != true) {
		int brkwgjwcg;
		for (brkwgjwcg = 65; brkwgjwcg > 0; brkwgjwcg--) {
			continue;
		}
	}

}

uqbjwcn::uqbjwcn() {
	this->xyamrnjrdde(string("xxhhksefwfbkjirvynwlorwuhmceiyaqkmkznywpwijxgefiabqllhxprbuoknylqgcwvcvmqhooqjxstihbzorfz"));
	this->xoixegwvmgfdmnzb();
	this->zplxftqlcb(string("hjiwsiyayonrelsscivxswzyvdmf"), string("lpfdvrajvvthiyybuqci"), 1646, 4532, false, 26622, 89009, 45725);
	this->ctrssyobgudwqyyhyvxyq();
	this->dbujwykcwuljccibwlevomnko(10116, 743, 4653);
	this->cpxgfidzvwe(5132, 595, string("kmiwakrkdyubgmykycfhmrsplhrx"), 76, string("rrdpzodcnnggargvfxvdwaxdmtyexjhvbaxnocgjnachghbm"));
	this->gdnksrepylxigasyv(1555, 32527);
	this->thngsqpxryahthhadi(67444, string("eqinxhdmrwxzrdylwgqyhmdyakcldjttrsn"), 1225, true);
	this->yakshmoeuuvdvl(4418, 22320, false, 44149, 1401, false, 1824, string("mfnarwncyverjgyicrgparxbgpifaokeamgksaybuhktgenenqtvulothqotjzvbfoawlfpfibdq"), 9156, string("mwcpneumvfoucfnedfqckyckvxpkmgyvuhhxu"));
	this->iuuajjfanidxpjk(2870, string("bmbptjypegfqxhvecgkjrvyrfbmrdggsaaeeyymrgxylygvptzrahzbxkmarrrsmvawbuhhhzdmzndjbjcemqqcbydfvim"), 3609, 17644);
	this->qjrphcwyhhgubbvydmbe(true, string("knwgtpncithrtevdopsvtsdtlazfgnymryuoroceevlbybjposbgeskochbuty"), 10740);
	this->eybxaegshqqledbazyoloeeu(string("utevhrqkaaei"), 48432, 1570, string("lhwdlllmkavpscmdzxeevtzufnfpopmvjubfeeyctgyvxphsqhqfszvbdrvwyhvqtujjngwpmgfaqrgbebocc"), string("shkgfgcwoedxnppqwubidtuczevbpiyhlkyclexassxobwlmgjcyvgeddljocmodjpxfncujkwrfyxcxtxrusgvptwgj"), 10006, string("ohlodvqsxbsmhs"), true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class rakxxxh {
public:
	string tcbnoifq;
	double sxyimcmryom;
	bool aozsy;
	double dmzjojeeksmw;
	rakxxxh();
	void hnfucljgbfxtqzv(bool lqfqnb, bool zsfimckhhbw, string sukpn, double eiqqpjaapsxp);
	int kaimvzhdfjmpueoyvfitl(double xzdeymdhigpn, double wbfzfqocsmnszqo, string rezjwhlo, double dpmeryxp, string pqvrqil, string hnbmum, double bgpecorra);
	string vbffvkniszafnxreepgpxu();
	bool afuokmszgvaomklvwr(double vfttsswzchkpikh, int zopea, bool jrxkf);
	void jpiyoheczdvigoyqrympl(bool tahifmkalevsno, bool ltbxgtpfbozhmp, bool dcvma, bool tdzpdpmttb, string iomgbdtbyyc, int mevbfbvgjdoyakg);
	string qbbutrqsucsfgfuqpr(string rafduj);
	double ntgrefuojjuremctxmmqangeb(double kldjkp, string suxgibvpipbh, bool wmyphfao, string ongsy);
	bool gdvtavqbzbw(string kbijbjvr, double fvsjja, int dzbaeowreqdg, int tsgxxsmtpp, bool qxyemhydirivd);

protected:
	double pqymiagpgvnrclp;
	double hryogtkcd;

	double zuljbhcjfeufidyysujnkl(double pmcclcgjjokc, double ybbabfmshzpoc, bool aufmd, double ewrxlushfestr);
	bool oaagrtlvykjpvolpkotlsjfi();

private:
	int dfppwc;
	double cwzxtyj;
	int pbojqetyz;
	string pfrwur;

	void oduqrqcthbomlwn(double hutoelbe, int xflwlaasmuxmnzn, bool lyudvyinpls);
	double iveorqdjji(int wacdiczpcyhb, bool gmflq, int gnmbcp, double cplijkbjxxc, bool sbjovygqsks, double afhnvddrf);
	int uutzbcmyxynlouuoifqb(double kbcuth, int pcuksjtq, double tnfgtvrfddmll, string jkhgy, string rxlguozik, double yoscifgvcsqqlt);
	string vpsrkzwhtyoudalw(double lqetp, bool lozyvgfgwnaj, int tjmwo);
	int oncprdfqajmcfgxyuihiqibdj(double ywyig, bool pftmkmdwf, double ylivljt, int fcrnlvnszhr, int yhfoymwrefbupe, string tlipky, string ermswulvqxal, bool dkdoo);
	void ujaivmketob(bool zzjsdpxqjnigiu);

};


void rakxxxh::oduqrqcthbomlwn(double hutoelbe, int xflwlaasmuxmnzn, bool lyudvyinpls) {
	string jvbjluzgqpbhndy = "ensywsdbiprsoujrsvlzrsiykftmtdjfiekcxbyxgblkkdhyuuuimlbivaxneqyxpvvdtdmutruonqttzcbvgrztjdobyzp";
	int hjqsrjblfgy = 5417;
	int qxemjvjcy = 4720;
	bool bhpdoea = false;

}

double rakxxxh::iveorqdjji(int wacdiczpcyhb, bool gmflq, int gnmbcp, double cplijkbjxxc, bool sbjovygqsks, double afhnvddrf) {
	string ptzvhczle = "nuizmflksurwzrzvmwbtnsripgmekgqmzudh";
	double ukwxtw = 27529;
	string grgslzdnsihdqr = "qhmqhucfqtkhtgzbvbnyxpcmjuslfjxonlshrxupq";
	int ixnvfg = 7921;
	bool kjorezrslfgmtw = true;
	int sdgmbyyxhltmx = 210;
	if (27529 == 27529) {
		int uwku;
		for (uwku = 90; uwku > 0; uwku--) {
			continue;
		}
	}
	if (27529 != 27529) {
		int dud;
		for (dud = 15; dud > 0; dud--) {
			continue;
		}
	}
	if (210 == 210) {
		int alw;
		for (alw = 91; alw > 0; alw--) {
			continue;
		}
	}
	if (string("qhmqhucfqtkhtgzbvbnyxpcmjuslfjxonlshrxupq") != string("qhmqhucfqtkhtgzbvbnyxpcmjuslfjxonlshrxupq")) {
		int mujbxtcojz;
		for (mujbxtcojz = 33; mujbxtcojz > 0; mujbxtcojz--) {
			continue;
		}
	}
	if (string("nuizmflksurwzrzvmwbtnsripgmekgqmzudh") == string("nuizmflksurwzrzvmwbtnsripgmekgqmzudh")) {
		int nv;
		for (nv = 32; nv > 0; nv--) {
			continue;
		}
	}
	return 47567;
}

int rakxxxh::uutzbcmyxynlouuoifqb(double kbcuth, int pcuksjtq, double tnfgtvrfddmll, string jkhgy, string rxlguozik, double yoscifgvcsqqlt) {
	int ybptxkdp = 3785;
	int weqce = 867;
	bool ugtak = false;
	int crrpabhzhartref = 1525;
	string bnsedo = "ddqmcqdpnrhhsuselfw";
	string duedbkm = "mrddljmnsxpi";
	if (1525 == 1525) {
		int olbgynjc;
		for (olbgynjc = 43; olbgynjc > 0; olbgynjc--) {
			continue;
		}
	}
	if (string("ddqmcqdpnrhhsuselfw") == string("ddqmcqdpnrhhsuselfw")) {
		int jzmyi;
		for (jzmyi = 65; jzmyi > 0; jzmyi--) {
			continue;
		}
	}
	if (false == false) {
		int vms;
		for (vms = 10; vms > 0; vms--) {
			continue;
		}
	}
	return 62419;
}

string rakxxxh::vpsrkzwhtyoudalw(double lqetp, bool lozyvgfgwnaj, int tjmwo) {
	bool wrwlja = false;
	int pumbajoifnwvazg = 183;
	int jraymdqpfvgsiry = 5730;
	bool jqktxmiohev = true;
	double kxobzbxpvpzyhb = 12883;
	int cvwmueuuosuldd = 71;
	string vkkfgc = "fpwrlxbdiwonpvwhnkdhvzghoiwrcvpnktuiqophgkyxvgrqspe";
	int twheasijlyvu = 1761;
	int arkdnqmlfz = 1234;
	if (1761 == 1761) {
		int qnwatijcfn;
		for (qnwatijcfn = 78; qnwatijcfn > 0; qnwatijcfn--) {
			continue;
		}
	}
	return string("gphjiguvfdtjlqj");
}

int rakxxxh::oncprdfqajmcfgxyuihiqibdj(double ywyig, bool pftmkmdwf, double ylivljt, int fcrnlvnszhr, int yhfoymwrefbupe, string tlipky, string ermswulvqxal, bool dkdoo) {
	return 81748;
}

void rakxxxh::ujaivmketob(bool zzjsdpxqjnigiu) {
	bool enqrxfczw = true;
	int fhlggfecyfeynmz = 4247;
	string kqyhqrzyfsknis = "ygrsxspclevjoiwtggrxmomtwejwlnsguchtzfkwlrooeihyhflsumsskwiepfsmhlzwcxekbes";
	int nzypbhjvvrrfrys = 939;
	int qfdhuygq = 1960;
	double oonrghu = 50867;
	if (50867 == 50867) {
		int rsq;
		for (rsq = 61; rsq > 0; rsq--) {
			continue;
		}
	}
	if (true != true) {
		int hbgxahop;
		for (hbgxahop = 3; hbgxahop > 0; hbgxahop--) {
			continue;
		}
	}
	if (true != true) {
		int rxumwvn;
		for (rxumwvn = 70; rxumwvn > 0; rxumwvn--) {
			continue;
		}
	}
	if (1960 == 1960) {
		int gazherrw;
		for (gazherrw = 38; gazherrw > 0; gazherrw--) {
			continue;
		}
	}
	if (50867 == 50867) {
		int jsceieuu;
		for (jsceieuu = 45; jsceieuu > 0; jsceieuu--) {
			continue;
		}
	}

}

double rakxxxh::zuljbhcjfeufidyysujnkl(double pmcclcgjjokc, double ybbabfmshzpoc, bool aufmd, double ewrxlushfestr) {
	string eqrpexazz = "gfrsmdxsrqtpyxoradihwwmgxgroabkefpmnkrgfpvfwvrr";
	double cdtrpv = 33396;
	string rnbgymjtcjx = "eyixwitonhlcdcmxmnhzvmbxehjtogpyulchofp";
	double urqqtxwc = 47025;
	bool yjgxzccycr = true;
	string qugsmr = "zckjwfourcezmeadiytuezsdtzfjfyyjwmznintftrhicqmkgiwjhhuurnvmvkmojgbxibgqxihynprgb";
	string nyeocxmwk = "yuwbzlgzkhainvrnqzdlhkeqqnylvdvieqgmzirirqxgygqizweckazrsmeibkbvpaycryrilbrlhi";
	bool sfimiey = true;
	if (47025 != 47025) {
		int mhe;
		for (mhe = 59; mhe > 0; mhe--) {
			continue;
		}
	}
	if (true == true) {
		int uekjrgfx;
		for (uekjrgfx = 8; uekjrgfx > 0; uekjrgfx--) {
			continue;
		}
	}
	if (string("gfrsmdxsrqtpyxoradihwwmgxgroabkefpmnkrgfpvfwvrr") != string("gfrsmdxsrqtpyxoradihwwmgxgroabkefpmnkrgfpvfwvrr")) {
		int mn;
		for (mn = 14; mn > 0; mn--) {
			continue;
		}
	}
	if (string("gfrsmdxsrqtpyxoradihwwmgxgroabkefpmnkrgfpvfwvrr") == string("gfrsmdxsrqtpyxoradihwwmgxgroabkefpmnkrgfpvfwvrr")) {
		int fuxe;
		for (fuxe = 24; fuxe > 0; fuxe--) {
			continue;
		}
	}
	if (true == true) {
		int lkweme;
		for (lkweme = 93; lkweme > 0; lkweme--) {
			continue;
		}
	}
	return 1195;
}

bool rakxxxh::oaagrtlvykjpvolpkotlsjfi() {
	bool uchzqyjomzek = false;
	string yinuccayxbg = "pijttbhmvwfkynbeokvtbzygkxivwqyczuxvtshylrw";
	double zuawxjgwkltq = 10413;
	string ogszmgzfe = "vszbqxnzhisvhhrtieclxltsspsljwysgqslwjzzyslrq";
	string mpdodwbbcr = "qyueijswelfxeobxaieqskrczifizyfhsfmleelfucjshvtvaayvmughonnnyvv";
	string hgpquusgtpubjdn = "trhwczapztkkdyrmtluqgwosxjvtjwlcfzkyyiqyufrdvljgzecwlpzjdecyilcjxcqxapkbouarbacffzulozmzlqom";
	double uybayqbjlgoxpkf = 29045;
	bool wdnam = true;
	double pvmmslpgqheuh = 17043;
	bool jlvhpqek = true;
	if (string("qyueijswelfxeobxaieqskrczifizyfhsfmleelfucjshvtvaayvmughonnnyvv") == string("qyueijswelfxeobxaieqskrczifizyfhsfmleelfucjshvtvaayvmughonnnyvv")) {
		int redoucrnbn;
		for (redoucrnbn = 96; redoucrnbn > 0; redoucrnbn--) {
			continue;
		}
	}
	if (true != true) {
		int jvafgbnksn;
		for (jvafgbnksn = 39; jvafgbnksn > 0; jvafgbnksn--) {
			continue;
		}
	}
	return true;
}

void rakxxxh::hnfucljgbfxtqzv(bool lqfqnb, bool zsfimckhhbw, string sukpn, double eiqqpjaapsxp) {
	string ilhsrjxmcfqdtfq = "x";
	string cmvvyjcduuhuiw = "cghrdifevtqadtanvkilgnckoonomdozznzcepjfnnxhxjlndbxzszrofacmkhyxorqcq";
	string rpdlu = "mxxugtcewauixgrjekdeemgonb";
	bool pownhuhq = true;
	double rwxfhjmuatw = 10303;
	int yusgks = 3645;
	string umyxtsswr = "tbmxnglsufkiomx";
	bool oxfcewf = false;
	double cphkqstntdte = 71434;
	int tpnbmhja = 1837;
	if (string("mxxugtcewauixgrjekdeemgonb") != string("mxxugtcewauixgrjekdeemgonb")) {
		int zgsqdnea;
		for (zgsqdnea = 79; zgsqdnea > 0; zgsqdnea--) {
			continue;
		}
	}
	if (string("cghrdifevtqadtanvkilgnckoonomdozznzcepjfnnxhxjlndbxzszrofacmkhyxorqcq") == string("cghrdifevtqadtanvkilgnckoonomdozznzcepjfnnxhxjlndbxzszrofacmkhyxorqcq")) {
		int vrfuowx;
		for (vrfuowx = 88; vrfuowx > 0; vrfuowx--) {
			continue;
		}
	}
	if (string("cghrdifevtqadtanvkilgnckoonomdozznzcepjfnnxhxjlndbxzszrofacmkhyxorqcq") != string("cghrdifevtqadtanvkilgnckoonomdozznzcepjfnnxhxjlndbxzszrofacmkhyxorqcq")) {
		int kmvdb;
		for (kmvdb = 95; kmvdb > 0; kmvdb--) {
			continue;
		}
	}

}

int rakxxxh::kaimvzhdfjmpueoyvfitl(double xzdeymdhigpn, double wbfzfqocsmnszqo, string rezjwhlo, double dpmeryxp, string pqvrqil, string hnbmum, double bgpecorra) {
	bool ipwpfmomdasa = false;
	int vgrumfitjxtcndd = 1936;
	string hswuddavhkjrfuz = "ljopkeylzzlangimqfpymoldyhjynmshvjugllzghxtjkukivwnokxcpeqgkiwxpnlxxowwtztgicxemslkyildekwirjouj";
	bool yiottup = false;
	string gfgapxcy = "qlmiupejttgnfdyjessijjvgtqgwxrikemevwlfwcmsxrwppemlmetomoraabxjm";
	double aspjxhiiuo = 9831;
	if (string("ljopkeylzzlangimqfpymoldyhjynmshvjugllzghxtjkukivwnokxcpeqgkiwxpnlxxowwtztgicxemslkyildekwirjouj") == string("ljopkeylzzlangimqfpymoldyhjynmshvjugllzghxtjkukivwnokxcpeqgkiwxpnlxxowwtztgicxemslkyildekwirjouj")) {
		int thdvczvefa;
		for (thdvczvefa = 30; thdvczvefa > 0; thdvczvefa--) {
			continue;
		}
	}
	if (false != false) {
		int mttchgryc;
		for (mttchgryc = 42; mttchgryc > 0; mttchgryc--) {
			continue;
		}
	}
	return 6279;
}

string rakxxxh::vbffvkniszafnxreepgpxu() {
	int essyw = 2495;
	double iefcnnlgpxrnqm = 2970;
	bool qfnpocmzgzd = false;
	if (2495 != 2495) {
		int ocsrmizvlf;
		for (ocsrmizvlf = 10; ocsrmizvlf > 0; ocsrmizvlf--) {
			continue;
		}
	}
	if (2495 != 2495) {
		int byfpijzljr;
		for (byfpijzljr = 15; byfpijzljr > 0; byfpijzljr--) {
			continue;
		}
	}
	return string("cgeagkrgmzdbhn");
}

bool rakxxxh::afuokmszgvaomklvwr(double vfttsswzchkpikh, int zopea, bool jrxkf) {
	double bjgtryzoxa = 4544;
	string tfqkjetsu = "btzszjfcfrgcjxjyuyfniupooxawhyfelowvscztxhmxqodlntvqogpwzetmdhbkxrudpktncqfodjzzqv";
	int yavyxwaxpowchxg = 1509;
	int mtlkcszfwiepqvu = 294;
	bool vgecnookolmckmq = false;
	int atbqiogovg = 1368;
	bool wipevz = false;
	string asmrodbetkj = "ybullgdqxpdxmszdrmpcnjhjxiukfpciluoejbdtcvmljqcqydwpfktdaign";
	if (false != false) {
		int wj;
		for (wj = 36; wj > 0; wj--) {
			continue;
		}
	}
	if (string("ybullgdqxpdxmszdrmpcnjhjxiukfpciluoejbdtcvmljqcqydwpfktdaign") == string("ybullgdqxpdxmszdrmpcnjhjxiukfpciluoejbdtcvmljqcqydwpfktdaign")) {
		int ysf;
		for (ysf = 14; ysf > 0; ysf--) {
			continue;
		}
	}
	if (294 != 294) {
		int mmghhqrab;
		for (mmghhqrab = 57; mmghhqrab > 0; mmghhqrab--) {
			continue;
		}
	}
	return true;
}

void rakxxxh::jpiyoheczdvigoyqrympl(bool tahifmkalevsno, bool ltbxgtpfbozhmp, bool dcvma, bool tdzpdpmttb, string iomgbdtbyyc, int mevbfbvgjdoyakg) {

}

string rakxxxh::qbbutrqsucsfgfuqpr(string rafduj) {
	double nxlrauapuuc = 46833;
	if (46833 == 46833) {
		int ezunr;
		for (ezunr = 100; ezunr > 0; ezunr--) {
			continue;
		}
	}
	if (46833 != 46833) {
		int ka;
		for (ka = 10; ka > 0; ka--) {
			continue;
		}
	}
	return string("oiloyubdzusadaez");
}

double rakxxxh::ntgrefuojjuremctxmmqangeb(double kldjkp, string suxgibvpipbh, bool wmyphfao, string ongsy) {
	int ropzkhtywwab = 6121;
	double tkkszzuide = 31609;
	string aelrtyo = "vqnqjpo";
	int vdfxfd = 1326;
	int qhlayywpwdzk = 6825;
	double xzfqrdv = 76571;
	int reueb = 4296;
	double nyjxtdqa = 29276;
	if (1326 == 1326) {
		int mhs;
		for (mhs = 9; mhs > 0; mhs--) {
			continue;
		}
	}
	if (6825 == 6825) {
		int przsghldk;
		for (przsghldk = 8; przsghldk > 0; przsghldk--) {
			continue;
		}
	}
	return 21709;
}

bool rakxxxh::gdvtavqbzbw(string kbijbjvr, double fvsjja, int dzbaeowreqdg, int tsgxxsmtpp, bool qxyemhydirivd) {
	return false;
}

rakxxxh::rakxxxh() {
	this->hnfucljgbfxtqzv(true, false, string("eroyqkgarjtdpcptvqikposovrjaqvaqwbspkluhnifzxrsfzynkswjcdycuytduivtcprcce"), 20895);
	this->kaimvzhdfjmpueoyvfitl(22840, 29798, string("ouoxbqqygwekwwwayrhzxlpgmfgwagqhgjmeifxxwtglhwropbmnlavoaqxnbgs"), 29749, string("scoupdxivlxdqtjzkqrhclkovmfogaivfgceyjyy"), string("msmetjfkouvtqzqsbkpewbrzvsssyxfcdpiulwoeluatrxrusvngxizvsceboxwyyuwme"), 77669);
	this->vbffvkniszafnxreepgpxu();
	this->afuokmszgvaomklvwr(637, 174, false);
	this->jpiyoheczdvigoyqrympl(true, false, false, false, string("hdwmtbdhquy"), 6903);
	this->qbbutrqsucsfgfuqpr(string("sropoccglnvnhggtfiyfprowbzgpmpxbeqnowkkpnaccgwnv"));
	this->ntgrefuojjuremctxmmqangeb(3350, string("vyxxqzpawfevazbsunhueklgywktcgkmetcsvtbxzukvlsacmnwwkjwxfbnnztykfzlnhpkuvtlxlf"), false, string("hpydpoxogfigpemaauuufeuumyhbclesvosgysrcyqruteytnxspsoqlmgim"));
	this->gdvtavqbzbw(string("zcpzuplbzjufoyrlvowgdcclgcqmjnukdmmgzwmekgzbbeuwmusboroyastvrwbawlfdpeeucuqbsiuolakjmzpalmsrwesh"), 4387, 7736, 3008, true);
	this->zuljbhcjfeufidyysujnkl(85686, 87186, false, 19634);
	this->oaagrtlvykjpvolpkotlsjfi();
	this->oduqrqcthbomlwn(31047, 834, true);
	this->iveorqdjji(576, true, 1214, 17952, false, 35950);
	this->uutzbcmyxynlouuoifqb(48804, 5860, 33616, string("lctceipxhkvnxzemkfzyokbafjkgzggvbjzcdzpyxwyrgwmhcczkhzjbqcmyhyqkforabcerdodszzplzcisxernas"), string("evpatpkzougfinrqouksmxhlprvigcyungxkpxzgluodg"), 1175);
	this->vpsrkzwhtyoudalw(58286, false, 2905);
	this->oncprdfqajmcfgxyuihiqibdj(21745, true, 12879, 682, 2476, string("locefvnxaoyklfrpxjhlkszlavmwsrwjtmhrujybiiahfkggqabj"), string("inssppcntnzzqmdqnlpucwhwyaxiaizeacedrccgdevvee"), false);
	this->ujaivmketob(true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class zvkovrw {
public:
	bool kmnnxfoydyev;
	zvkovrw();
	int aanqnkpldimpcrpkb(double mluauturuip, string wxnxbbfnxxgrr, int julxdzfzwmtsd, double odpaviltilhbhrp);
	string boaugpsxbk();
	int wgyhsibvywdwh(string mpeyrklxzqh, bool ssmpu, double wpmxc, string telva);
	string uchulsmwutv(string qqlsjpmcctlijmt);
	string dabieiszhysefsxr(bool aljwq);
	int bjhlrgzodfwrh(int jabrvlehgdbbvy, bool vwyli, bool emijbnjepaowh, string fmxzpdnbzxu, int wnxpt, int yojmbhbjehrjzh);

protected:
	bool fswpun;
	double fibzbwdfvevr;
	bool torfcsbvtyajuer;

	bool ygftonydwricjfphugetl(int kvdragghc, double vemtiudibw, bool ndfyqfvwneeg, bool vlekujssgsmboyz, int xlsbhtld, int hayptrcqk, bool bvneha, int odafjjuouaetqfp, bool wpfvdu);
	string rrauoxmmygbhtyp(int wgafilxohqn, bool ozsbnrf, int thxwfmzo, int fpsfoqdvyjqvhl, bool rmceqm, bool oktromvtdlnc, double octdsyswtyybf, int umicngostkwkle, string faqhny);
	string utrtozzhvtrclihgqtvep(int rhfgoxqjzwavzuf, int ytxxtzpvybbgejf, int yjxlrbepfznlcw, double vpoea, bool rcghgc, bool bhxluezcsynz);
	int ptcqjqioobooopdjzzf(bool nrbhlywegy, int pyswvrtxou, double iarasb, double xqmhvdpgcdkumv, string jvkjqqwgwgvfcm, bool elrgl, string pucwmrvks, double yenzodmyanrtw, int wbpnfu);

private:
	bool ebhigctummssuuq;
	int yngsrpiwvlno;

	int jggtklzupltflrouemxz(int lnvetokana, string uvyzw, int powmoezjdcuyr, double mmpvpwpoetqzbph, bool btthghlbi, int qippu, double wrhctgjmobzbxj, int ihdvqepo, int orhqctkmvdb);
	bool cewyyioosmt(string xclxeusapla, double zphkb);
	int iodelaebgztbrhhsomxavkmh(string nuwarytxocleqf, string hflewnjqjyapm, string xumilh, string lmmurlphrhgtox, string zuydephkat, int zjaggpczmam, double fdxwtz, int ruhgunjdfxjk);

};


int zvkovrw::jggtklzupltflrouemxz(int lnvetokana, string uvyzw, int powmoezjdcuyr, double mmpvpwpoetqzbph, bool btthghlbi, int qippu, double wrhctgjmobzbxj, int ihdvqepo, int orhqctkmvdb) {
	bool hwubjgdfzfvw = true;
	int qxpix = 4583;
	int bbyedlq = 804;
	double oljeigprwbozqxw = 32684;
	return 35502;
}

bool zvkovrw::cewyyioosmt(string xclxeusapla, double zphkb) {
	bool pepotzxsyufx = true;
	int cbukfiqjoc = 1245;
	string ckbqffvlidw = "aorcvzmxgotzxbfspahrkmydgwisaldbkwzwpl";
	bool wcrkrv = true;
	int jeqvzivbyzp = 3958;
	if (true == true) {
		int aw;
		for (aw = 44; aw > 0; aw--) {
			continue;
		}
	}
	if (1245 != 1245) {
		int ajgsxod;
		for (ajgsxod = 70; ajgsxod > 0; ajgsxod--) {
			continue;
		}
	}
	return true;
}

int zvkovrw::iodelaebgztbrhhsomxavkmh(string nuwarytxocleqf, string hflewnjqjyapm, string xumilh, string lmmurlphrhgtox, string zuydephkat, int zjaggpczmam, double fdxwtz, int ruhgunjdfxjk) {
	string myjfczxmgafkrn = "pekloiwzvtqrbjhsxgublhzuwkoinkhlupvvzbavmdzhgqpqrejwqbsbfkgvbwvpfcctecihbhugguiehvmjawicrxcman";
	double lfkudxrojs = 20221;
	double dosbcspshi = 8016;
	string usiznmtrpev = "wxigculoizfpjwfxksorxsqlsuwltleuydvicxtxvjjuufdekkpqlypnerfkazijuthzrsnceobyio";
	int hyciixsohn = 992;
	bool imnqtwijdpjfj = false;
	int pdcctpgvcgcpst = 2620;
	int mtmvpjcz = 4183;
	return 66158;
}

bool zvkovrw::ygftonydwricjfphugetl(int kvdragghc, double vemtiudibw, bool ndfyqfvwneeg, bool vlekujssgsmboyz, int xlsbhtld, int hayptrcqk, bool bvneha, int odafjjuouaetqfp, bool wpfvdu) {
	bool bwjoppolauyi = true;
	double enohxcfynprtc = 50413;
	string lrjvkhfu = "neveqhpcbahaxkjartaedsudwoiqwvgnsscgrrfvnjvwtqngixhkh";
	int lxiamkuih = 274;
	if (string("neveqhpcbahaxkjartaedsudwoiqwvgnsscgrrfvnjvwtqngixhkh") == string("neveqhpcbahaxkjartaedsudwoiqwvgnsscgrrfvnjvwtqngixhkh")) {
		int rl;
		for (rl = 18; rl > 0; rl--) {
			continue;
		}
	}
	if (50413 != 50413) {
		int ibbm;
		for (ibbm = 66; ibbm > 0; ibbm--) {
			continue;
		}
	}
	return false;
}

string zvkovrw::rrauoxmmygbhtyp(int wgafilxohqn, bool ozsbnrf, int thxwfmzo, int fpsfoqdvyjqvhl, bool rmceqm, bool oktromvtdlnc, double octdsyswtyybf, int umicngostkwkle, string faqhny) {
	string sezrdqd = "hgyyoqhakrkrbfvajhixsbyaykddwfucympkvlwlftwqjdbbp";
	bool ifewlue = true;
	string djoxppby = "sajzyxbtzjexeypcgsujpyuqeqxavwsdizqtpxkntltknlayxnfmgjgtbvhpuq";
	bool lnccctgociuzyrt = true;
	double valhjjltozlfu = 41535;
	if (true == true) {
		int aijnf;
		for (aijnf = 78; aijnf > 0; aijnf--) {
			continue;
		}
	}
	if (true == true) {
		int jw;
		for (jw = 78; jw > 0; jw--) {
			continue;
		}
	}
	if (41535 != 41535) {
		int gn;
		for (gn = 86; gn > 0; gn--) {
			continue;
		}
	}
	return string("gypyarbbwssjmpsma");
}

string zvkovrw::utrtozzhvtrclihgqtvep(int rhfgoxqjzwavzuf, int ytxxtzpvybbgejf, int yjxlrbepfznlcw, double vpoea, bool rcghgc, bool bhxluezcsynz) {
	string urealxyqohr = "xbkhmanzotvajknnylkjclrlqfiquc";
	string vrldimekpnadk = "emznbnvfxrbqvjrbghmtjnrvxkgwotvejoaarmvoxhznovwcfoulxfyomsafbxxqclvrfiuqgxwjlbsei";
	string ksstolwbg = "edsdmrembwndkhmlsfcbpixgrmujebdwfcefmlsawkapkgxhcwfkywluptcgjeftmlmbmtrfgsghkjov";
	double fwlpw = 70667;
	string gkqqrwbpnsepse = "asaaxefflyayegromiuxphtjsczxqlrpluwmukvsftdlrcvppovteygneckprwlxxwqq";
	double dtetwsv = 30457;
	bool lpqhqtjmkwignxi = false;
	double oijgx = 38049;
	if (string("xbkhmanzotvajknnylkjclrlqfiquc") != string("xbkhmanzotvajknnylkjclrlqfiquc")) {
		int fp;
		for (fp = 71; fp > 0; fp--) {
			continue;
		}
	}
	if (string("edsdmrembwndkhmlsfcbpixgrmujebdwfcefmlsawkapkgxhcwfkywluptcgjeftmlmbmtrfgsghkjov") != string("edsdmrembwndkhmlsfcbpixgrmujebdwfcefmlsawkapkgxhcwfkywluptcgjeftmlmbmtrfgsghkjov")) {
		int mayvmtt;
		for (mayvmtt = 43; mayvmtt > 0; mayvmtt--) {
			continue;
		}
	}
	return string("nmkdmlnorhapjkjq");
}

int zvkovrw::ptcqjqioobooopdjzzf(bool nrbhlywegy, int pyswvrtxou, double iarasb, double xqmhvdpgcdkumv, string jvkjqqwgwgvfcm, bool elrgl, string pucwmrvks, double yenzodmyanrtw, int wbpnfu) {
	int ozypkjsikls = 9285;
	int jemvu = 1725;
	int rbpycl = 273;
	bool ykjpihqywbyf = false;
	int wkgrsidugsh = 2964;
	bool ezmekvy = true;
	bool wlmbnyubxwux = true;
	int giygmhd = 3236;
	int rtyqkqatt = 397;
	if (2964 == 2964) {
		int aqdez;
		for (aqdez = 56; aqdez > 0; aqdez--) {
			continue;
		}
	}
	if (true != true) {
		int qetqzyq;
		for (qetqzyq = 8; qetqzyq > 0; qetqzyq--) {
			continue;
		}
	}
	if (273 == 273) {
		int fvcw;
		for (fvcw = 25; fvcw > 0; fvcw--) {
			continue;
		}
	}
	if (1725 == 1725) {
		int ig;
		for (ig = 51; ig > 0; ig--) {
			continue;
		}
	}
	if (1725 == 1725) {
		int jqniywnugi;
		for (jqniywnugi = 47; jqniywnugi > 0; jqniywnugi--) {
			continue;
		}
	}
	return 41827;
}

int zvkovrw::aanqnkpldimpcrpkb(double mluauturuip, string wxnxbbfnxxgrr, int julxdzfzwmtsd, double odpaviltilhbhrp) {
	double ejoipl = 12419;
	bool zsanweczefkzag = false;
	if (false != false) {
		int qqigaimiq;
		for (qqigaimiq = 89; qqigaimiq > 0; qqigaimiq--) {
			continue;
		}
	}
	if (12419 != 12419) {
		int vmzaz;
		for (vmzaz = 47; vmzaz > 0; vmzaz--) {
			continue;
		}
	}
	if (12419 != 12419) {
		int ub;
		for (ub = 37; ub > 0; ub--) {
			continue;
		}
	}
	if (12419 != 12419) {
		int kw;
		for (kw = 35; kw > 0; kw--) {
			continue;
		}
	}
	if (12419 != 12419) {
		int hf;
		for (hf = 21; hf > 0; hf--) {
			continue;
		}
	}
	return 57156;
}

string zvkovrw::boaugpsxbk() {
	double ebbxpasssfr = 48558;
	string dfcikggtcb = "sfodtxgqhuhhqzc";
	string wsfnwuuv = "nvlrbrxicykwutyvsnrebjrdsqbpzpfdwycagcywkbbnlhcufyfycoznilxdcayympyawhakqruuckmlo";
	int udkuqkerhlqlp = 843;
	int rnnlf = 1053;
	double rdhsjdbdyhi = 26579;
	int rjtekrgwdugqlga = 231;
	double idrarew = 23701;
	double seaddytizgty = 53478;
	if (53478 == 53478) {
		int ymzqhww;
		for (ymzqhww = 60; ymzqhww > 0; ymzqhww--) {
			continue;
		}
	}
	if (string("sfodtxgqhuhhqzc") == string("sfodtxgqhuhhqzc")) {
		int epxjtfg;
		for (epxjtfg = 65; epxjtfg > 0; epxjtfg--) {
			continue;
		}
	}
	return string("lquwxyuabuwthxsi");
}

int zvkovrw::wgyhsibvywdwh(string mpeyrklxzqh, bool ssmpu, double wpmxc, string telva) {
	double sqthsxhlxifscwo = 30159;
	string ftmhpdoupahz = "bxhnufgkxtuoljdkuapgfnmnrmstlqdikayyrgvqneldvlmllzotwvgrvs";
	bool rvohippr = false;
	bool qjmqorjbeohpt = false;
	string bhzibmymepcwjoz = "fzipsotmldzuuzzbhmfxazzrkidsfpcodlnvcipokxumqgspnrjishvnuqlmxtqncnmpm";
	int itruoorkq = 1373;
	double zcooyphpeiga = 36171;
	int meksyqfc = 2460;
	if (false != false) {
		int ytrksx;
		for (ytrksx = 18; ytrksx > 0; ytrksx--) {
			continue;
		}
	}
	if (30159 != 30159) {
		int jq;
		for (jq = 20; jq > 0; jq--) {
			continue;
		}
	}
	if (string("bxhnufgkxtuoljdkuapgfnmnrmstlqdikayyrgvqneldvlmllzotwvgrvs") != string("bxhnufgkxtuoljdkuapgfnmnrmstlqdikayyrgvqneldvlmllzotwvgrvs")) {
		int kimpa;
		for (kimpa = 34; kimpa > 0; kimpa--) {
			continue;
		}
	}
	return 84566;
}

string zvkovrw::uchulsmwutv(string qqlsjpmcctlijmt) {
	double roylhsqllwybmwp = 7500;
	bool kvluaxokayccmo = false;
	bool ukhibdwaiiq = false;
	double wvznn = 38110;
	bool kxeepgn = false;
	bool fkyauxouo = true;
	if (true != true) {
		int eqnl;
		for (eqnl = 51; eqnl > 0; eqnl--) {
			continue;
		}
	}
	if (true != true) {
		int rrbtt;
		for (rrbtt = 4; rrbtt > 0; rrbtt--) {
			continue;
		}
	}
	if (false == false) {
		int tihtpyhue;
		for (tihtpyhue = 86; tihtpyhue > 0; tihtpyhue--) {
			continue;
		}
	}
	return string("garkhssliurqn");
}

string zvkovrw::dabieiszhysefsxr(bool aljwq) {
	int qzxifyvqvwsp = 4091;
	bool dehqaxgc = false;
	int nuvanhmhsfgyzku = 412;
	if (412 != 412) {
		int atipzoitlo;
		for (atipzoitlo = 14; atipzoitlo > 0; atipzoitlo--) {
			continue;
		}
	}
	if (false != false) {
		int avpfdkvos;
		for (avpfdkvos = 5; avpfdkvos > 0; avpfdkvos--) {
			continue;
		}
	}
	if (4091 == 4091) {
		int qlt;
		for (qlt = 8; qlt > 0; qlt--) {
			continue;
		}
	}
	return string("znzbzglkiwsbydunx");
}

int zvkovrw::bjhlrgzodfwrh(int jabrvlehgdbbvy, bool vwyli, bool emijbnjepaowh, string fmxzpdnbzxu, int wnxpt, int yojmbhbjehrjzh) {
	string ubwlwvscqrxh = "gwajyltdfbjkolxbqegaazhlevldwwknqozfezjrqwyrnxyatpvc";
	bool iyqwevbsftdqf = true;
	string tdvbtcfgwignmg = "opnzalgfldhoatvnhvqkspwogxbeefykhbpumaaoecnvndqqrhhjukdlbspsc";
	bool ygnsnccufznh = true;
	bool xpeigeoamjb = false;
	if (string("gwajyltdfbjkolxbqegaazhlevldwwknqozfezjrqwyrnxyatpvc") != string("gwajyltdfbjkolxbqegaazhlevldwwknqozfezjrqwyrnxyatpvc")) {
		int kztswsfo;
		for (kztswsfo = 49; kztswsfo > 0; kztswsfo--) {
			continue;
		}
	}
	return 45529;
}

zvkovrw::zvkovrw() {
	this->aanqnkpldimpcrpkb(7194, string("ohwvrpmlpaplbi"), 5688, 25116);
	this->boaugpsxbk();
	this->wgyhsibvywdwh(string("wwsfjrqjz"), false, 58410, string("kvwiygqwwswkqysfnctetaioxehuerqpjgofontsanp"));
	this->uchulsmwutv(string("atubqynyhumqbwhfcufiacatzdivttfqnqrdjvqpcpjkitgxkcijlarijoeazgsqlpjqwyrixjiomlslhh"));
	this->dabieiszhysefsxr(true);
	this->bjhlrgzodfwrh(3039, true, true, string("ptxswbnhbqdgspifiqopxuiiwdhgwyi"), 2550, 1575);
	this->ygftonydwricjfphugetl(5562, 55125, true, false, 3153, 5317, false, 7621, false);
	this->rrauoxmmygbhtyp(940, true, 6195, 2490, false, true, 16773, 1712, string("wsjtrhvmeiefriwelvydkpxvxradrmbnptdxlux"));
	this->utrtozzhvtrclihgqtvep(3056, 351, 2053, 2165, false, false);
	this->ptcqjqioobooopdjzzf(false, 1669, 32195, 8281, string("u"), false, string("efyksdmhvfoslacrigkaez"), 39436, 206);
	this->jggtklzupltflrouemxz(5307, string("osvytxxyojykwxbzuhvkjtvzjbeoaxwpznstpxvqfbocvyxzpngbunainqwc"), 2879, 22214, true, 651, 93471, 678, 997);
	this->cewyyioosmt(string("flepuotvrdckxkmvqysrrepipytbvbynvhzobztnupnwzgrexodjtgcqpvwvtrsnyrjdgyhpfgjpeczgyzxwadmvxtxryaqdlir"), 5590);
	this->iodelaebgztbrhhsomxavkmh(string("dibzrrgkkrusdbanfkyusarpcnkjxhbgro"), string("uwwctiwrelubrvifpebonphrhtniatoufgrexevlhijcoojagrzcyldobtmmgnndqlbrorgupxhtqbbcyslw"), string("nqjbfcfzymtrbnoqlywzpulzzmlemsqcztgjypwehocuthbohhdxcqaxlprfs"), string("gfuewwfjxxynelmaxyavgnuv"), string("jpxyfmbuzlwtfeudmmsnmkpscezonkvogasyenwaaomubyewdtbuszpswfeazgtnpexxonqfcgbjebirjiiplplwpbierpnj"), 2687, 11995, 207);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class yxxtnot {
public:
	int bzcoq;
	bool cgjtwshmhbh;
	double agfbxc;
	double ytrvincfxvjyqi;
	yxxtnot();
	void wjkypbggdhltmbnjrmv(int epdybamuv, double vwbuhcgfjv, bool rcwjybii, bool phvdypvnb, string elgjgu, bool xdbinnjrfhex);
	string gyunnhqavqnhrixbrik();
	double mqhplbtowexgpofuykeu(string wvvxb, int asgwtdycqdzbb, double uxjqjizj, string evdlkpfaczhzuqm);
	double vbqytijugfqddc(int xtvbn, int edmsbv, int ukfxehonolbodb, string jcsbhbmaarbzvh, double mgkllxcylxliz, double oapgpirfvjzwtha, bool trugaam, double nllwvnhjh, int omsizdbqszdyz, double fnidoatarwwsixd);
	void scjyvvcfnikixwrjaeoywrogj(int fqmnjsjgcxeduvd, string hkshllwz, string jszrpnijqvfgume, int hopccp, int hpmztxepfqgsfg);
	int nkruqltgaftqpisuypalp(double suntspy, int uzcuaiy, string mgqjary, bool tmmkivzbestqkbz, double qxljytgtqbwm, int nzdhyvqteuskok, string kwdqqefwwn);

protected:
	double afrom;
	bool ynvkne;

	string rfvvbphduzs(double inbbwineo, int prcvzrsvqjq, string ldsxrnrhvolz);
	string haqohuqtapnzzcversyk(string qdfntg, bool ascdnyijjmzpu, int poobwfoxcznsgy, int ualhjvqtftcw, double eujahyswdfn, double btwjpywii);
	bool jlcecmlnyfoji(bool fwtokeeysi, string qhxujsarrhgqsi, string sdvuaezi, string crtltyvmflkaaau, string mhjufxotwang, int vlbryclgv, double qlhwlnnbni, double qgoadungs);
	int brerdjvhyjgv(int jnpwu);
	void ekfdvpwpmrcfodnvveq(bool fkshm, bool yfkwghhypqtbizo, int pypjjcwcnos);
	void hvprcdfjhltyfqilekllktx(double dcliedk, string jmckxbtfem, string rguqyimndv, bool ktnlypiwhsxpssl, int bbkjtett, string ztqtqzri, string vfbizolxytmusfz, int rrioxketik, int cgvpuspcvramjba, string jmtpbtjdkpz);
	double lrfxicxytuvseojpwzloj();

private:
	int gsgtogfv;

	void oaqshykwsosovcqlvvw(bool vfqlhykshczcej, int inrnvqspqsij, bool qhgmbhjc, string xittecplxexkjz, int klvdca, string sgteurgb);
	bool scegjbugzrwzdoview(int tmpmexudaqyeshr);
	void daefpauhuritvojqvapnp(bool nbitf, bool srjchhvez, bool opnlifhfe, string tkkuuxc, int zatxsn);
	int wqkbdsiyjmvgophfbevf(string alhfdsonka, bool eacvkakac, int sidcjgpioo, int yjwqkyzmqwtyshq, int oixmwjxyjt, double egxvszecxahhgzu, bool dhfdax, bool dvuyprvqzmmfab);
	string iptnlkmyjrybdctbxnbvhqc(double fyijrbix, int wfkxfrwdyexdonq, bool pwuvhcrpdobu, bool dwhypopqnwcu, double buzirn);
	string ezqpasthncunfgqzswwhav(bool qefzxaqvvihi, string wdrtumknl, string amqlv, double wtqbppcwn);
	double cwdbxywbflpcpsffkozcns(double xrbxdqlnirsvfk, bool tvduofcyudoz, int bfubj);
	string axhdabstsyvydoxxkwzjtgpe(int llrniureggkjuhs, bool ubljszfmlsud, int kcgefh, int hkpja, bool ldimnl);
	int yvwfpchyqszosqybuhhpbpicm(int ukohmxgml, int hjqjlvfiesnslx);

};


void yxxtnot::oaqshykwsosovcqlvvw(bool vfqlhykshczcej, int inrnvqspqsij, bool qhgmbhjc, string xittecplxexkjz, int klvdca, string sgteurgb) {
	string dhlmgcqm = "rhqacissypssafbpbeevzxbtuezjfejojhounukarysk";
	string qsvozek = "iuxrvmxbdfuzwsxrzziizvwhafqzlthlwwzkzxftcmfuyqblnzwhh";
	double amizajjo = 21476;
	bool jrbznjnfstq = false;
	string oftpsih = "qipzvukxdxjgcifkwwfvpnvrsdnaurwdpzqvaeaiqwhvbgqeyddnodlnaqufulavlkdmavgjpnifidkjracytfcaxjhmeczbarh";
	string nxfnkmey = "nlqineyrdiwcqstnmyyylackesslwdrituzfyhpfqmodwny";
	if (string("iuxrvmxbdfuzwsxrzziizvwhafqzlthlwwzkzxftcmfuyqblnzwhh") != string("iuxrvmxbdfuzwsxrzziizvwhafqzlthlwwzkzxftcmfuyqblnzwhh")) {
		int onkppkl;
		for (onkppkl = 6; onkppkl > 0; onkppkl--) {
			continue;
		}
	}

}

bool yxxtnot::scegjbugzrwzdoview(int tmpmexudaqyeshr) {
	int jffrgbluhgykbw = 4583;
	string kwuzbqvxmhss = "znmhhlelzfpgkakcpgnycdjsbwanuqubxbykeywqcdyiegprbogcqpszvdffmmjfqohym";
	string jmgxpyipjlull = "lzl";
	string ezehjxn = "ctwqphverhsarahzoftidabpncfsphqicqvswsnvnumaplmeiqtflldboayglmdjrazzwggcwnozbzdpodkqbepcetrxqmbdacae";
	int rqzcwdqu = 1387;
	if (1387 != 1387) {
		int gdybcfoold;
		for (gdybcfoold = 99; gdybcfoold > 0; gdybcfoold--) {
			continue;
		}
	}
	if (string("znmhhlelzfpgkakcpgnycdjsbwanuqubxbykeywqcdyiegprbogcqpszvdffmmjfqohym") == string("znmhhlelzfpgkakcpgnycdjsbwanuqubxbykeywqcdyiegprbogcqpszvdffmmjfqohym")) {
		int nvfimdk;
		for (nvfimdk = 86; nvfimdk > 0; nvfimdk--) {
			continue;
		}
	}
	if (1387 == 1387) {
		int upqwfwri;
		for (upqwfwri = 31; upqwfwri > 0; upqwfwri--) {
			continue;
		}
	}
	if (string("lzl") != string("lzl")) {
		int rahsxz;
		for (rahsxz = 0; rahsxz > 0; rahsxz--) {
			continue;
		}
	}
	if (string("lzl") != string("lzl")) {
		int rqrtlzpy;
		for (rqrtlzpy = 96; rqrtlzpy > 0; rqrtlzpy--) {
			continue;
		}
	}
	return false;
}

void yxxtnot::daefpauhuritvojqvapnp(bool nbitf, bool srjchhvez, bool opnlifhfe, string tkkuuxc, int zatxsn) {

}

int yxxtnot::wqkbdsiyjmvgophfbevf(string alhfdsonka, bool eacvkakac, int sidcjgpioo, int yjwqkyzmqwtyshq, int oixmwjxyjt, double egxvszecxahhgzu, bool dhfdax, bool dvuyprvqzmmfab) {
	double nvqrexgzewhg = 25980;
	string kaxrcwytpleln = "jmvpgqebbvezjlshgefkmlaabgwmrmvtwjwgqopvhacb";
	bool rzmtmfmhouxopr = true;
	string jfkjnqgiml = "tbpawiiczspgdufsrcyhjstbxmgqdwhttpbqgzffysswfpjgeqxnnimmtujqfijtebwguucnhpugpvnakrdrlkzqvp";
	string pvlosdodqumx = "atnsyk";
	return 86931;
}

string yxxtnot::iptnlkmyjrybdctbxnbvhqc(double fyijrbix, int wfkxfrwdyexdonq, bool pwuvhcrpdobu, bool dwhypopqnwcu, double buzirn) {
	string duftdlckmsuqt = "dwwbouzlqyajxpnrhbuelbltzlxyevlpyvfwfeamrlvydekfrvtcg";
	string mlodpnfct = "kfszgwkmnvbhwnhpmlifzeppvxlhbnhoqutpcbqcbwwqnilegalgfxmfzrxrvjb";
	int kcgytzqugblqfxg = 105;
	int mxkmnpqb = 1614;
	double pbbvkqcf = 7728;
	string hknbpzvru = "simhqehibkkxaqjqjjfjtgqxprasmduecepdkapdgatwlzsilpkssexuggjqkpupyzlwnqyfoviukrwyulsrp";
	string wqmfe = "ofvdiozbarhls";
	bool hztozjv = true;
	bool dgkppkatusel = true;
	bool pkgxruxs = true;
	if (string("dwwbouzlqyajxpnrhbuelbltzlxyevlpyvfwfeamrlvydekfrvtcg") != string("dwwbouzlqyajxpnrhbuelbltzlxyevlpyvfwfeamrlvydekfrvtcg")) {
		int howjrecpzl;
		for (howjrecpzl = 65; howjrecpzl > 0; howjrecpzl--) {
			continue;
		}
	}
	if (1614 == 1614) {
		int jny;
		for (jny = 44; jny > 0; jny--) {
			continue;
		}
	}
	if (true != true) {
		int mdsehxqovp;
		for (mdsehxqovp = 20; mdsehxqovp > 0; mdsehxqovp--) {
			continue;
		}
	}
	if (105 == 105) {
		int ztlsa;
		for (ztlsa = 34; ztlsa > 0; ztlsa--) {
			continue;
		}
	}
	if (105 != 105) {
		int xtpojqmj;
		for (xtpojqmj = 55; xtpojqmj > 0; xtpojqmj--) {
			continue;
		}
	}
	return string("phzjifjazjcwaoqksk");
}

string yxxtnot::ezqpasthncunfgqzswwhav(bool qefzxaqvvihi, string wdrtumknl, string amqlv, double wtqbppcwn) {
	int gymhwthkaysrqom = 3127;
	string midcsezfw = "aszfcyomonfosazhjefdwoebqhmwulpmombwvpemesyuqhemblqgrumopklubszhwnoxabehtdmmkizayylfpinzuoigpmyefwy";
	double mckxfjigdaojqfr = 55075;
	double mcdspyr = 18999;
	if (3127 == 3127) {
		int wkb;
		for (wkb = 63; wkb > 0; wkb--) {
			continue;
		}
	}
	if (3127 != 3127) {
		int zadgifay;
		for (zadgifay = 93; zadgifay > 0; zadgifay--) {
			continue;
		}
	}
	if (3127 != 3127) {
		int wvhu;
		for (wvhu = 84; wvhu > 0; wvhu--) {
			continue;
		}
	}
	if (18999 == 18999) {
		int wxj;
		for (wxj = 55; wxj > 0; wxj--) {
			continue;
		}
	}
	return string("luldgouuui");
}

double yxxtnot::cwdbxywbflpcpsffkozcns(double xrbxdqlnirsvfk, bool tvduofcyudoz, int bfubj) {
	double incpekiyfntdbn = 14372;
	bool bfrpm = true;
	string nazvarrvhk = "faiduntk";
	bool cnpvfpgt = true;
	int rezfixqn = 3197;
	int zeipubquudsynr = 3505;
	double bakgaysw = 43169;
	if (3197 != 3197) {
		int mkvbosnpb;
		for (mkvbosnpb = 4; mkvbosnpb > 0; mkvbosnpb--) {
			continue;
		}
	}
	if (string("faiduntk") == string("faiduntk")) {
		int ejpqnlzaay;
		for (ejpqnlzaay = 72; ejpqnlzaay > 0; ejpqnlzaay--) {
			continue;
		}
	}
	if (true != true) {
		int alkq;
		for (alkq = 66; alkq > 0; alkq--) {
			continue;
		}
	}
	if (true == true) {
		int achc;
		for (achc = 81; achc > 0; achc--) {
			continue;
		}
	}
	return 54864;
}

string yxxtnot::axhdabstsyvydoxxkwzjtgpe(int llrniureggkjuhs, bool ubljszfmlsud, int kcgefh, int hkpja, bool ldimnl) {
	bool hzddvcsfeayo = false;
	if (false != false) {
		int nesxasbr;
		for (nesxasbr = 92; nesxasbr > 0; nesxasbr--) {
			continue;
		}
	}
	return string("rhkhzsdhapwwfxecz");
}

int yxxtnot::yvwfpchyqszosqybuhhpbpicm(int ukohmxgml, int hjqjlvfiesnslx) {
	bool mwjwbuejkwst = false;
	int avbdmmofruyqlqd = 1299;
	double vndyggqfucxg = 8813;
	if (1299 == 1299) {
		int fd;
		for (fd = 25; fd > 0; fd--) {
			continue;
		}
	}
	return 86487;
}

string yxxtnot::rfvvbphduzs(double inbbwineo, int prcvzrsvqjq, string ldsxrnrhvolz) {
	string cvbcvdiameahqzh = "dktoiqvglcttakerbvaabzwdrtjnafwaxwuozahfalsvpjwssrtryzeanpoxtatnizwzeooovrxaohld";
	bool knblmnmwbd = true;
	string vusmxthhzsgp = "wragtaroksgabvigwbwvdbskznkwuwbsgvkqbzsitzhsrqvuamjtvwdante";
	if (string("wragtaroksgabvigwbwvdbskznkwuwbsgvkqbzsitzhsrqvuamjtvwdante") == string("wragtaroksgabvigwbwvdbskznkwuwbsgvkqbzsitzhsrqvuamjtvwdante")) {
		int amdrgtxiig;
		for (amdrgtxiig = 51; amdrgtxiig > 0; amdrgtxiig--) {
			continue;
		}
	}
	if (true == true) {
		int grrtzd;
		for (grrtzd = 62; grrtzd > 0; grrtzd--) {
			continue;
		}
	}
	if (true != true) {
		int wun;
		for (wun = 48; wun > 0; wun--) {
			continue;
		}
	}
	if (string("dktoiqvglcttakerbvaabzwdrtjnafwaxwuozahfalsvpjwssrtryzeanpoxtatnizwzeooovrxaohld") != string("dktoiqvglcttakerbvaabzwdrtjnafwaxwuozahfalsvpjwssrtryzeanpoxtatnizwzeooovrxaohld")) {
		int chgfcfb;
		for (chgfcfb = 91; chgfcfb > 0; chgfcfb--) {
			continue;
		}
	}
	return string("liwip");
}

string yxxtnot::haqohuqtapnzzcversyk(string qdfntg, bool ascdnyijjmzpu, int poobwfoxcznsgy, int ualhjvqtftcw, double eujahyswdfn, double btwjpywii) {
	int kavgaxuqcp = 708;
	double gfvtyjmi = 28601;
	return string("bsagvksjrb");
}

bool yxxtnot::jlcecmlnyfoji(bool fwtokeeysi, string qhxujsarrhgqsi, string sdvuaezi, string crtltyvmflkaaau, string mhjufxotwang, int vlbryclgv, double qlhwlnnbni, double qgoadungs) {
	double awxwk = 69890;
	int ufpvizkqtgogf = 851;
	bool nowzwqa = false;
	int aogqe = 1834;
	int pggapiqifsuimsi = 189;
	bool prwygmzslxpdz = false;
	bool lkvufysqhps = false;
	double imyyhflphdm = 23058;
	if (1834 == 1834) {
		int ea;
		for (ea = 60; ea > 0; ea--) {
			continue;
		}
	}
	if (false != false) {
		int nh;
		for (nh = 35; nh > 0; nh--) {
			continue;
		}
	}
	if (1834 == 1834) {
		int sm;
		for (sm = 74; sm > 0; sm--) {
			continue;
		}
	}
	if (69890 != 69890) {
		int vyti;
		for (vyti = 37; vyti > 0; vyti--) {
			continue;
		}
	}
	if (851 == 851) {
		int tata;
		for (tata = 99; tata > 0; tata--) {
			continue;
		}
	}
	return true;
}

int yxxtnot::brerdjvhyjgv(int jnpwu) {
	int dxzqwvgyvibnk = 2807;
	if (2807 != 2807) {
		int enehx;
		for (enehx = 98; enehx > 0; enehx--) {
			continue;
		}
	}
	if (2807 != 2807) {
		int isserzt;
		for (isserzt = 71; isserzt > 0; isserzt--) {
			continue;
		}
	}
	if (2807 != 2807) {
		int fildwqi;
		for (fildwqi = 48; fildwqi > 0; fildwqi--) {
			continue;
		}
	}
	if (2807 != 2807) {
		int iniawc;
		for (iniawc = 66; iniawc > 0; iniawc--) {
			continue;
		}
	}
	if (2807 == 2807) {
		int lpye;
		for (lpye = 68; lpye > 0; lpye--) {
			continue;
		}
	}
	return 21948;
}

void yxxtnot::ekfdvpwpmrcfodnvveq(bool fkshm, bool yfkwghhypqtbizo, int pypjjcwcnos) {
	string xkzvoddaz = "cwhvcgqzrocxdcdhncpuqfgynejjdi";

}

void yxxtnot::hvprcdfjhltyfqilekllktx(double dcliedk, string jmckxbtfem, string rguqyimndv, bool ktnlypiwhsxpssl, int bbkjtett, string ztqtqzri, string vfbizolxytmusfz, int rrioxketik, int cgvpuspcvramjba, string jmtpbtjdkpz) {
	double duapvwwe = 3573;
	if (3573 == 3573) {
		int qstfdeadn;
		for (qstfdeadn = 72; qstfdeadn > 0; qstfdeadn--) {
			continue;
		}
	}

}

double yxxtnot::lrfxicxytuvseojpwzloj() {
	double tsntsqj = 36074;
	double rtlqdrwq = 5557;
	int cmsxh = 4614;
	bool frcpwmeeoetbrh = true;
	string vxigoexd = "qwilbocgdvnqedoleuihptukqkopdpznzcuqmh";
	string fmztivwgqkk = "oabwkjfy";
	if (36074 == 36074) {
		int tommxa;
		for (tommxa = 45; tommxa > 0; tommxa--) {
			continue;
		}
	}
	if (string("qwilbocgdvnqedoleuihptukqkopdpznzcuqmh") != string("qwilbocgdvnqedoleuihptukqkopdpznzcuqmh")) {
		int tove;
		for (tove = 6; tove > 0; tove--) {
			continue;
		}
	}
	if (4614 == 4614) {
		int qbrxpla;
		for (qbrxpla = 45; qbrxpla > 0; qbrxpla--) {
			continue;
		}
	}
	if (string("qwilbocgdvnqedoleuihptukqkopdpznzcuqmh") == string("qwilbocgdvnqedoleuihptukqkopdpznzcuqmh")) {
		int azkalenz;
		for (azkalenz = 83; azkalenz > 0; azkalenz--) {
			continue;
		}
	}
	if (5557 == 5557) {
		int hlrod;
		for (hlrod = 96; hlrod > 0; hlrod--) {
			continue;
		}
	}
	return 14474;
}

void yxxtnot::wjkypbggdhltmbnjrmv(int epdybamuv, double vwbuhcgfjv, bool rcwjybii, bool phvdypvnb, string elgjgu, bool xdbinnjrfhex) {
	bool bxabfg = false;
	if (false == false) {
		int rd;
		for (rd = 19; rd > 0; rd--) {
			continue;
		}
	}
	if (false == false) {
		int ppf;
		for (ppf = 16; ppf > 0; ppf--) {
			continue;
		}
	}

}

string yxxtnot::gyunnhqavqnhrixbrik() {
	int fpxbgtrny = 1024;
	int uzuapzwgska = 6636;
	bool unuapliwpt = true;
	string fptznlx = "nufrcxwuwydggbnernhqfkxnqnbxifqykhzuewxljsrjdqaehvvcakmlvivobzlapszhltnwyt";
	int sfhdxk = 8077;
	int ukznawri = 2169;
	int lvqveromhxdm = 2672;
	int pzeqn = 1597;
	int tltljmriroh = 1368;
	int kooxayw = 118;
	if (string("nufrcxwuwydggbnernhqfkxnqnbxifqykhzuewxljsrjdqaehvvcakmlvivobzlapszhltnwyt") != string("nufrcxwuwydggbnernhqfkxnqnbxifqykhzuewxljsrjdqaehvvcakmlvivobzlapszhltnwyt")) {
		int soon;
		for (soon = 44; soon > 0; soon--) {
			continue;
		}
	}
	if (1597 != 1597) {
		int oo;
		for (oo = 90; oo > 0; oo--) {
			continue;
		}
	}
	if (8077 == 8077) {
		int ebuny;
		for (ebuny = 9; ebuny > 0; ebuny--) {
			continue;
		}
	}
	if (8077 == 8077) {
		int ufbst;
		for (ufbst = 39; ufbst > 0; ufbst--) {
			continue;
		}
	}
	if (2169 == 2169) {
		int bo;
		for (bo = 72; bo > 0; bo--) {
			continue;
		}
	}
	return string("znwftda");
}

double yxxtnot::mqhplbtowexgpofuykeu(string wvvxb, int asgwtdycqdzbb, double uxjqjizj, string evdlkpfaczhzuqm) {
	string ereyzdfax = "jupcuzsjrnpkvobeybliyzafqmlpgpdgjllcohjnkqxojkbpq";
	bool agebmmpp = false;
	string wpuvsslcmczva = "fhtpiaatkppitksvotfvagxmetuowmzyjazyaoswbkgbprjeoytaecdqpqcznwbtdjzgmhlzkoytun";
	bool jqqcrasayiwg = true;
	bool gdtplnhwq = true;
	bool xgxlltafuwfevxe = false;
	if (string("jupcuzsjrnpkvobeybliyzafqmlpgpdgjllcohjnkqxojkbpq") == string("jupcuzsjrnpkvobeybliyzafqmlpgpdgjllcohjnkqxojkbpq")) {
		int jcvzmhkpvi;
		for (jcvzmhkpvi = 3; jcvzmhkpvi > 0; jcvzmhkpvi--) {
			continue;
		}
	}
	if (true == true) {
		int ttrgfz;
		for (ttrgfz = 73; ttrgfz > 0; ttrgfz--) {
			continue;
		}
	}
	if (false == false) {
		int ak;
		for (ak = 32; ak > 0; ak--) {
			continue;
		}
	}
	if (false == false) {
		int cqawiif;
		for (cqawiif = 35; cqawiif > 0; cqawiif--) {
			continue;
		}
	}
	if (false != false) {
		int ibrqesrqci;
		for (ibrqesrqci = 63; ibrqesrqci > 0; ibrqesrqci--) {
			continue;
		}
	}
	return 88127;
}

double yxxtnot::vbqytijugfqddc(int xtvbn, int edmsbv, int ukfxehonolbodb, string jcsbhbmaarbzvh, double mgkllxcylxliz, double oapgpirfvjzwtha, bool trugaam, double nllwvnhjh, int omsizdbqszdyz, double fnidoatarwwsixd) {
	bool xuphmmdwchklry = true;
	string ezetdxg = "chldllzzswjthhtfgdmydplqfqhmdhovpnzdjzatjennqbijfnyuwrmjzlhsrbyixlcgfmin";
	double yhkpm = 60970;
	bool chemv = false;
	double bxlkkb = 38453;
	string eibasf = "qyybmgvzxvfhkqqthvcxyfrakgoncrdisnyqehl";
	string yfjelkbu = "fkl";
	double ckxedgxxm = 23871;
	if (string("qyybmgvzxvfhkqqthvcxyfrakgoncrdisnyqehl") == string("qyybmgvzxvfhkqqthvcxyfrakgoncrdisnyqehl")) {
		int zzyyjo;
		for (zzyyjo = 7; zzyyjo > 0; zzyyjo--) {
			continue;
		}
	}
	if (false != false) {
		int xt;
		for (xt = 24; xt > 0; xt--) {
			continue;
		}
	}
	if (true == true) {
		int awygwvcoss;
		for (awygwvcoss = 17; awygwvcoss > 0; awygwvcoss--) {
			continue;
		}
	}
	return 14928;
}

void yxxtnot::scjyvvcfnikixwrjaeoywrogj(int fqmnjsjgcxeduvd, string hkshllwz, string jszrpnijqvfgume, int hopccp, int hpmztxepfqgsfg) {
	bool gyzzqoqqxnpx = false;
	bool sdynrzjgg = true;
	bool dmwrsowhqei = true;
	bool zpdszlkgsjzrrhf = false;
	bool bdjihqffiq = false;
	string lwkyuxwleqemcxq = "weimschfeoxgxdsvvwoury";
	bool gwdeljd = true;
	double ackwdp = 6189;

}

int yxxtnot::nkruqltgaftqpisuypalp(double suntspy, int uzcuaiy, string mgqjary, bool tmmkivzbestqkbz, double qxljytgtqbwm, int nzdhyvqteuskok, string kwdqqefwwn) {
	int rliprufrmjhft = 2236;
	double lgcxl = 26081;
	string vzcel = "gxtnoxrdnnayquhmbuckcprbkdidftrpqa";
	bool fpfzm = false;
	double jnqqgav = 56647;
	bool ponng = true;
	bool pbrpoqxducdzsf = false;
	int iscawqelj = 203;
	string xqafdpxblrv = "qohbcpagdxoxqdqxqofrnisdrtdzbbggdafltusbavzsbfayaxqalggeoowiicoqcjzjvaj";
	if (string("gxtnoxrdnnayquhmbuckcprbkdidftrpqa") != string("gxtnoxrdnnayquhmbuckcprbkdidftrpqa")) {
		int dlyqkgpupa;
		for (dlyqkgpupa = 67; dlyqkgpupa > 0; dlyqkgpupa--) {
			continue;
		}
	}
	return 95363;
}

yxxtnot::yxxtnot() {
	this->wjkypbggdhltmbnjrmv(329, 38042, true, true, string("navi"), false);
	this->gyunnhqavqnhrixbrik();
	this->mqhplbtowexgpofuykeu(string("bagpomdqbayhwqxzkakl"), 5516, 5617, string("lsmchcqtfmympwiqxxbckttggqjjjlaknwkohjvhmkyudojykebagom"));
	this->vbqytijugfqddc(5695, 1125, 1609, string("frfizvarxzuabifmcmmjshhxtjusercdtfxhvlumrensbqflyb"), 16534, 44458, true, 84597, 4045, 10868);
	this->scjyvvcfnikixwrjaeoywrogj(1839, string("frqrmkpzmfmxnsplgdciggfqggdoxhtwyxnrp"), string("dikzkiikafwljrczclus"), 866, 2606);
	this->nkruqltgaftqpisuypalp(44731, 551, string("mvttuzbwaxpnfpcipwisxgajkxntsnjfwcdmprlznwpcegcmunqjebac"), true, 36121, 3918, string("legxxybrazmsvipkonkhlvhyks"));
	this->rfvvbphduzs(27752, 6, string("aiccxrmnmnyjzadtvlkqdqxgezbjksygtabphfquffjflseblshehrorzmocptrpzrxnlgqdfjdiegsdhshcwpkuozbzaiojcejo"));
	this->haqohuqtapnzzcversyk(string("tvvbunhdvdasalvgiadsllxldvzfddbjahebunuignbqztsjbhidbwjbrvfvkkpejmwkrntwkiqeqcsqmhxtqqtsppykvvmuki"), true, 4637, 1673, 37035, 62158);
	this->jlcecmlnyfoji(true, string("wetrcijl"), string("zxapshdjhafokkmvtswosnxnavyeofbjhjigamkfcmsskdaruxic"), string("nkiqjeojhvyyxgndqytphquthuiijtdtaedsoxeiaugvbddlrlflknouxmwndqrqsfsemmfohipqavbgf"), string("nceurjjvhwzbjgtxzwomxzujepkarlxmkqicyvtlakbuegokmgsgctjsdkkebxxalmxofobkkyilahlrmkrkj"), 6053, 98, 40494);
	this->brerdjvhyjgv(5825);
	this->ekfdvpwpmrcfodnvveq(false, false, 87);
	this->hvprcdfjhltyfqilekllktx(27094, string("shjuwdgsqvdqgswv"), string("fwkohoippfwbhhtqaqchjcyhe"), false, 712, string("kmgonakldhmam"), string("artyieykymzowmkzmkklogfunzdowmyebeilemxvkjamnvquglnhu"), 6025, 4823, string("gqqqidxttmzzhfvnfzbbcykelvohwicukbnrgzdzqiktfmkkgfiomdwelvxtygwaibiqoimswqyifhrbfmy"));
	this->lrfxicxytuvseojpwzloj();
	this->oaqshykwsosovcqlvvw(true, 756, false, string("nogcadrfuhtszycnzmzuxxmqxszwx"), 6562, string("ghplapejveswdsohhucwdgaluqcjzpnnrfjvebfbcdbgmquwnvijnmlpbccy"));
	this->scegjbugzrwzdoview(5662);
	this->daefpauhuritvojqvapnp(true, false, true, string("hyuelecgvrgsf"), 242);
	this->wqkbdsiyjmvgophfbevf(string("mwaffkklvxgvsaxnqfqnjleqy"), false, 1058, 302, 6067, 5763, false, false);
	this->iptnlkmyjrybdctbxnbvhqc(15287, 2608, false, false, 35369);
	this->ezqpasthncunfgqzswwhav(true, string("vtrshdzegilvyanjxlodxncxmnjwaxhivgwoocolvlovdcp"), string("yuxecqulcsxecjysfw"), 1813);
	this->cwdbxywbflpcpsffkozcns(26241, false, 1369);
	this->axhdabstsyvydoxxkwzjtgpe(466, true, 398, 4048, false);
	this->yvwfpchyqszosqybuhhpbpicm(6280, 3278);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class fqngqqq {
public:
	bool tndqcklfvnrq;
	string rpgygg;
	double saifzqy;
	double xdvacyw;
	bool cqcxoev;
	fqngqqq();
	string zkswmwxqdxzmrqbu(bool xddjxxpii, double wghplm, string vwjarwewlpkhgd, double xtcwhvtnbiabbyb, bool okfkwialuentd);
	bool ixlvwbwdmxxgmogidjpsy(bool iiijrysglc, int isrkqoadima, double pfimx, string tmotjcwxxs, int yukbvoywm);
	string zzfabwmdntjwragfqxxj(string vbbkqsiahtw, string jtadkekuntkzc, int hryeqffxta, bool ekcqzr, string awbukeji, double dhwaavn, int lzrfndsxsltauc, double mqisn);
	double twrblnaaxx(double halffkufa, double twalryyurf, bool xficnjkubuizekt, int ftcqo, string akyak, string obwczsuy, int rkhizmbzrwgr, double pcjrke, double mtsxjwuzgr);

protected:
	int hixvp;
	bool ikneqhfdab;
	int hgzanjqw;

	double xbylunvxpred(bool yipcgl, double bzuhcferw, double pgjufspuulj, bool safpbhadvxa, string ostxhjg);
	void uupfpotdzs(string jkvsmbujwngqfp, string lifofpk, string fkkmvutfunkg, bool rsrnuisih, double qtdvejrhjbp, string uwzxgwzvedyju, string leokjidshwnkut);

private:
	bool laszvdrlnjp;
	double mlxyywmrdxzid;

	string twyztafawykwkqqq();
	double rfxsrwbwom(int fipxbqwcts);
	double onbioseihpnkkpxmvxh(string wqqezdblogeppd, bool fdrhoetwfee, double utcisdxjnzfz, bool qsoxrtsn, bool bytfyory);

};


string fqngqqq::twyztafawykwkqqq() {
	double wbhqajytf = 266;
	int mvqflxiucgnqyza = 999;
	bool jnaqmttgenwwgr = false;
	string xepiardxaf = "eszzzbtvltqddxqokmojhxbyfqtobfohiyromzewecngcitckiouskuddrpgdshrgkpcfaszgzisbypehbxrmckc";
	double iopwqp = 78549;
	int tbhjculwao = 4470;
	double kvawzvx = 24186;
	int wqndqexzey = 7715;
	string uvaoek = "rjtaaqzxndllmesjzasxfywiqadhilftsefypmojrgvw";
	string auxbmmablhm = "dstgifwjwb";
	if (999 != 999) {
		int cehn;
		for (cehn = 63; cehn > 0; cehn--) {
			continue;
		}
	}
	if (string("rjtaaqzxndllmesjzasxfywiqadhilftsefypmojrgvw") != string("rjtaaqzxndllmesjzasxfywiqadhilftsefypmojrgvw")) {
		int keuwfk;
		for (keuwfk = 68; keuwfk > 0; keuwfk--) {
			continue;
		}
	}
	if (string("dstgifwjwb") != string("dstgifwjwb")) {
		int efzfztlefk;
		for (efzfztlefk = 34; efzfztlefk > 0; efzfztlefk--) {
			continue;
		}
	}
	if (999 != 999) {
		int her;
		for (her = 58; her > 0; her--) {
			continue;
		}
	}
	return string("epuydpe");
}

double fqngqqq::rfxsrwbwom(int fipxbqwcts) {
	return 19214;
}

double fqngqqq::onbioseihpnkkpxmvxh(string wqqezdblogeppd, bool fdrhoetwfee, double utcisdxjnzfz, bool qsoxrtsn, bool bytfyory) {
	string uxerhwkkg = "akymyr";
	bool wuzyomvlt = true;
	string ulgrygins = "ikpjwwyexsfnqnobarouvntiszfrmhamhyqtgemkbxw";
	bool ncyipwz = true;
	if (true == true) {
		int zbek;
		for (zbek = 50; zbek > 0; zbek--) {
			continue;
		}
	}
	if (true == true) {
		int mlezrf;
		for (mlezrf = 95; mlezrf > 0; mlezrf--) {
			continue;
		}
	}
	if (string("akymyr") == string("akymyr")) {
		int csmdir;
		for (csmdir = 4; csmdir > 0; csmdir--) {
			continue;
		}
	}
	return 34606;
}

double fqngqqq::xbylunvxpred(bool yipcgl, double bzuhcferw, double pgjufspuulj, bool safpbhadvxa, string ostxhjg) {
	string qcjgxgfjn = "xmgd";
	bool pcgasmusyecshlx = false;
	bool ewktirpphwq = false;
	return 80301;
}

void fqngqqq::uupfpotdzs(string jkvsmbujwngqfp, string lifofpk, string fkkmvutfunkg, bool rsrnuisih, double qtdvejrhjbp, string uwzxgwzvedyju, string leokjidshwnkut) {
	double bbartb = 10797;
	double vvyvbhbdbxgpsh = 6515;
	int yalvepgagsbqgp = 2431;
	string hxtupm = "qmzketrnu";
	int azwjdvfbm = 2996;

}

string fqngqqq::zkswmwxqdxzmrqbu(bool xddjxxpii, double wghplm, string vwjarwewlpkhgd, double xtcwhvtnbiabbyb, bool okfkwialuentd) {
	return string("iblguipdabkxwj");
}

bool fqngqqq::ixlvwbwdmxxgmogidjpsy(bool iiijrysglc, int isrkqoadima, double pfimx, string tmotjcwxxs, int yukbvoywm) {
	bool dvwequgmxa = false;
	bool baljqxcerxa = true;
	if (true != true) {
		int cat;
		for (cat = 6; cat > 0; cat--) {
			continue;
		}
	}
	if (false != false) {
		int jymxnnuwt;
		for (jymxnnuwt = 67; jymxnnuwt > 0; jymxnnuwt--) {
			continue;
		}
	}
	if (false == false) {
		int qe;
		for (qe = 34; qe > 0; qe--) {
			continue;
		}
	}
	if (false != false) {
		int pviclo;
		for (pviclo = 5; pviclo > 0; pviclo--) {
			continue;
		}
	}
	if (false != false) {
		int ctz;
		for (ctz = 94; ctz > 0; ctz--) {
			continue;
		}
	}
	return true;
}

string fqngqqq::zzfabwmdntjwragfqxxj(string vbbkqsiahtw, string jtadkekuntkzc, int hryeqffxta, bool ekcqzr, string awbukeji, double dhwaavn, int lzrfndsxsltauc, double mqisn) {
	bool fcksmohaaiel = false;
	string ydmnharjatgw = "otytmwcfdowq";
	bool sdlstfzqueldjhr = false;
	double xezazjzde = 2876;
	bool wbfcgwcjzlj = false;
	string mmqnxlwms = "dmjaxgluwgaucxbokqafunpynaohwqtthwtxbwwbewmltetiqetxoqpcyktkjlzkhsqvtegng";
	if (string("dmjaxgluwgaucxbokqafunpynaohwqtthwtxbwwbewmltetiqetxoqpcyktkjlzkhsqvtegng") != string("dmjaxgluwgaucxbokqafunpynaohwqtthwtxbwwbewmltetiqetxoqpcyktkjlzkhsqvtegng")) {
		int ufseiqbeg;
		for (ufseiqbeg = 67; ufseiqbeg > 0; ufseiqbeg--) {
			continue;
		}
	}
	if (2876 != 2876) {
		int qqqrlu;
		for (qqqrlu = 24; qqqrlu > 0; qqqrlu--) {
			continue;
		}
	}
	if (false != false) {
		int nyge;
		for (nyge = 97; nyge > 0; nyge--) {
			continue;
		}
	}
	return string("uxvet");
}

double fqngqqq::twrblnaaxx(double halffkufa, double twalryyurf, bool xficnjkubuizekt, int ftcqo, string akyak, string obwczsuy, int rkhizmbzrwgr, double pcjrke, double mtsxjwuzgr) {
	int uitpqpsyojswtil = 727;
	int djomzdekpnrgj = 1932;
	double anlueeqdbwnjodv = 16080;
	double oxibcbkwnt = 39622;
	double mjjwspvxpif = 6084;
	string ighqrbwke = "nqoiegjgpkquy";
	double pwyux = 19892;
	string xsmoupndgf = "wppgcjspngqgnvowdk";
	if (39622 != 39622) {
		int kz;
		for (kz = 85; kz > 0; kz--) {
			continue;
		}
	}
	return 22805;
}

fqngqqq::fqngqqq() {
	this->zkswmwxqdxzmrqbu(true, 32976, string("obsgcadzfvgkenasifhzobfnswlhfzunvxldttuwofhmdqebxsvqpkffbvg"), 9940, false);
	this->ixlvwbwdmxxgmogidjpsy(true, 3572, 13917, string("vovlxobhhsdbltwcmnbccwvwvayrgvowhrgrsgcxlmotjxivimbqasykk"), 1246);
	this->zzfabwmdntjwragfqxxj(string("kqhjjfjgnslgakrflrfegcavroimfayyflyusbbl"), string("vfeymyyreyimcqdarbwiypisn"), 8034, false, string("qpluntewtswxzacrjgtmrvclozuwgvcfmuuadioqdspatzfhjyqpxoojwllvhomejkslflallgdrriabgi"), 30283, 2528, 21413);
	this->twrblnaaxx(51903, 13753, false, 87, string("bmtgonjvygmjsuiyqtzkoaxsnpxhsieiwmxbyveglrvvgwwjluk"), string("yydpwfccpldbuuabluktvozojsqautdjiiibxfkvafnfwcqxbbunzce"), 4877, 20634, 27071);
	this->xbylunvxpred(true, 51475, 6375, false, string("yuhkcjxchptaxraihbqxjnkhtrkxjzcrfaynrxblsolgbwzekktkfqjexkwbbfmigm"));
	this->uupfpotdzs(string("omrkcrztkapemaerochdmsqhrqrzgforatoyvbyqeeeswdixypxdgoyhddjdta"), string("kac"), string("mrgquiogvggvlejbzwogprhtvrzpwgvbwloicyzsvapsqtpdtgzxjycibjnrzyzpqyuhnpjduaqpstmvrqylojgbjnl"), false, 45868, string("rpedkqzvqjaguhalyvusaunnnlcpccsjwllldbdrvilcwjfmmspygytpykdmexshnno"), string("xkhkpuqfuayhoincuxahvytmkfvrlzggrnspabnavtmbitxpqbltpiybcbrcape"));
	this->twyztafawykwkqqq();
	this->rfxsrwbwom(2325);
	this->onbioseihpnkkpxmvxh(string("obkpysibdsgohsjaffxblzjmhqgmtkoi"), false, 33878, false, false);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class wiiynoa {
public:
	double lojypursjt;
	bool lqdxlshemfp;
	int veihibl;
	string lyggj;
	wiiynoa();
	bool zbsxhgwrmnxusptozjmv(bool nnmndau, double zjgkzuyriccsq, double xqvdi, bool kdrfkdfgerd);

protected:
	double tubynqmjvt;
	double pwxjjcidvuv;
	double kvxqmf;
	double kqmbohindbzxyz;

	double zavvzgzectuwtnohzchyhiyhj(string lsucijxqoiyz, bool bqzrfphfmcdepk, int risjbpsn);
	bool lponycplufxyc(double bgozyf, double vikexcdt, bool iansxgtw, int spvojbstmpkuzt, string ofgdja, bool vuwsfu, double mrmadn, double czffzadbj);
	double zngmstfpfelepualzlfwrymm(int donpznsjnklaetw, string dgauhditkmwrsy, double wdjmuulj, double skavzfeyvrhivxe, bool qattbce, bool kywohfhgfit, double zbqxwqizdz);
	double bggwegyznyzejiqnrwnnqq(string aftqcpnw, double zxsvhlgeubrm, int fpndb, string nptzochlrhjq, string jvzqotd, int siffgsxhimdw, double hfwsyojylqu);
	string pkqzrussfbkv(int yqqtadk, bool piknscliphqfqzu, bool hsaacdtgdxgdl, double dghmrld);
	bool chfivpywmgxrfckb(bool tglcvfvyxyeact, bool azzzsavvmfnm, int alffcomgleb, string qktyhhanp, string mwihfenmmdl);
	int gfkspuzfvnvgmbduh(bool fzpqolcppxajjl, string almtweg, string tnesart, int bkixiafkjqsk, double daqjnqnr);
	string fsvxnhzwxcmhujwuluzqekct();
	void fldmxzoixpxffwogoamjso(string lahblx);

private:
	int ymlfmcjfalewfw;

	string fgaxafsoznwxwfrrqfpc(double pamncri, int zqtcb, double njlcacqdvar, string ajycsppir, int khusgtvuap, bool hhmptgy);
	int kaiilqoxzqcjgckqekeshkds(double nrmflndehwzrpy, bool jqaqjl);
	bool diqnpvokcdwjsqhuxrxwzevd(double bcrxijwvxxc, bool fgxfihziiy);
	string udtvehlkhuhofbixrkhmcb(double wyawqc, double nduesinm, bool xdhxlthgaqnm, bool lwtaywzodsqlqk, bool nkdgygfbyewlhh, double rolyo, bool rtghrblbwhxh, bool wsraoqodv);
	double bixvoicavuqwtejqrk(bool xtlqgxbydgzilt, double uekaskkzpgrny, string usmcuwagx);

};


string wiiynoa::fgaxafsoznwxwfrrqfpc(double pamncri, int zqtcb, double njlcacqdvar, string ajycsppir, int khusgtvuap, bool hhmptgy) {
	return string("zomsnlavgh");
}

int wiiynoa::kaiilqoxzqcjgckqekeshkds(double nrmflndehwzrpy, bool jqaqjl) {
	int judhod = 2429;
	double opsafdovv = 16827;
	int gjhwvnkloxhjocm = 568;
	int fwhmsp = 5288;
	if (5288 == 5288) {
		int cnxuqmdp;
		for (cnxuqmdp = 55; cnxuqmdp > 0; cnxuqmdp--) {
			continue;
		}
	}
	if (568 != 568) {
		int ieikhkg;
		for (ieikhkg = 97; ieikhkg > 0; ieikhkg--) {
			continue;
		}
	}
	if (16827 != 16827) {
		int kobnxbvue;
		for (kobnxbvue = 95; kobnxbvue > 0; kobnxbvue--) {
			continue;
		}
	}
	if (2429 != 2429) {
		int ljgipb;
		for (ljgipb = 97; ljgipb > 0; ljgipb--) {
			continue;
		}
	}
	if (2429 != 2429) {
		int eclijizx;
		for (eclijizx = 37; eclijizx > 0; eclijizx--) {
			continue;
		}
	}
	return 35510;
}

bool wiiynoa::diqnpvokcdwjsqhuxrxwzevd(double bcrxijwvxxc, bool fgxfihziiy) {
	bool byvbutqrtspy = false;
	double yygeebo = 10433;
	bool mzijvhwrjyb = true;
	string pnzsh = "eggmhgjkldqmzpoybscsjezhhawnoripsehygitvodplkrpynjlnwmjjftqoaprvbyjdmtxhhxrg";
	double qobacyfucqn = 9483;
	string jtezhyvklqzb = "whgydckislmwtheyhdofxlqbhfdbzqdclkpwbbarnvfrlxbnujeqcarpumzmadmkiyzdchrf";
	bool ymvmyezluu = true;
	string meshy = "vsnzedksnfqnukgpzbwffrangqhvezgjrcodmmkxyfxlmjbirfdyx";
	string tcldmblgjqr = "pkogfzsyrwvzkkrptjewkksscukwokddbietmrbbpdedjexgjfmywkgxaqzoozzfyo";
	int ejnuwfra = 188;
	return false;
}

string wiiynoa::udtvehlkhuhofbixrkhmcb(double wyawqc, double nduesinm, bool xdhxlthgaqnm, bool lwtaywzodsqlqk, bool nkdgygfbyewlhh, double rolyo, bool rtghrblbwhxh, bool wsraoqodv) {
	bool taarkleywiwzyq = true;
	int kprwlpfqgvb = 1423;
	int zscdrabaifyvufi = 4260;
	double xficdcnpmuzt = 23422;
	string mtfmqdpzzxldtjd = "wjarvsqmusynuocysehrqfl";
	int ebadojw = 1874;
	double imiaukqcwzz = 51636;
	bool dbnux = true;
	double lhxwkiqly = 19677;
	double glmgff = 36221;
	return string("ixqinvieldfomlgjdz");
}

double wiiynoa::bixvoicavuqwtejqrk(bool xtlqgxbydgzilt, double uekaskkzpgrny, string usmcuwagx) {
	bool grdscsmyyxu = true;
	int fiacdibduiisf = 4583;
	int xrxnelnqayvoi = 3918;
	int dfsergijl = 3011;
	string axyyorxcftwnf = "oileuslqrsfeflskwynfphbbklnrvbgympjhelmxjuhuyvamimmcneci";
	double vdkyuvftoz = 56888;
	return 90500;
}

double wiiynoa::zavvzgzectuwtnohzchyhiyhj(string lsucijxqoiyz, bool bqzrfphfmcdepk, int risjbpsn) {
	bool ryzlcme = true;
	int vedpbaiufacnc = 870;
	bool gtdqhdqnpz = false;
	double wbnxwctylp = 13269;
	double rigpbnjvrkgj = 33416;
	string hkybfirnmpn = "t";
	string ejmdu = "cudhydsmxwvesmxfbbvaokbt";
	double nuwxf = 55203;
	string onwkxbyusmz = "ivkvilyxpdallmahoguaqzssypjcmvvmesubjpsuiykbuegyducvlzycebeuwfcfexttycqbgzq";
	if (33416 == 33416) {
		int wtcjrwzjs;
		for (wtcjrwzjs = 27; wtcjrwzjs > 0; wtcjrwzjs--) {
			continue;
		}
	}
	return 48708;
}

bool wiiynoa::lponycplufxyc(double bgozyf, double vikexcdt, bool iansxgtw, int spvojbstmpkuzt, string ofgdja, bool vuwsfu, double mrmadn, double czffzadbj) {
	bool mlxkhzozpo = false;
	string ewnvnlq = "aeokbjarmwisbuatvxemfqsbetgvhxxrlvoyukzgmsvchs";
	string eixlkbzekcxcv = "tvregyhputlygqfvfokkrwfgke";
	bool kszlwofyma = true;
	int hqvdw = 1333;
	int jdttowgj = 1543;
	if (true != true) {
		int ewzdj;
		for (ewzdj = 70; ewzdj > 0; ewzdj--) {
			continue;
		}
	}
	return true;
}

double wiiynoa::zngmstfpfelepualzlfwrymm(int donpznsjnklaetw, string dgauhditkmwrsy, double wdjmuulj, double skavzfeyvrhivxe, bool qattbce, bool kywohfhgfit, double zbqxwqizdz) {
	double viiffkaxollbc = 9265;
	double aigniw = 48058;
	bool fbwnuyo = true;
	double ikuyuplukguv = 24233;
	int eqfmjvlgpbjay = 6085;
	int ousmme = 1827;
	return 45226;
}

double wiiynoa::bggwegyznyzejiqnrwnnqq(string aftqcpnw, double zxsvhlgeubrm, int fpndb, string nptzochlrhjq, string jvzqotd, int siffgsxhimdw, double hfwsyojylqu) {
	double sbqsfm = 23811;
	string pldqscfvphw = "fvqrzcsrkhwnkxxopgyekhknfegkcwxwcsditdtwjlojtunstcgmrvdi";
	double oopbcwecaquy = 59372;
	bool xapwhntn = true;
	bool otxgnddrgb = false;
	int attpjfdyljsdfc = 7053;
	int hrtlpeoklxf = 101;
	if (string("fvqrzcsrkhwnkxxopgyekhknfegkcwxwcsditdtwjlojtunstcgmrvdi") != string("fvqrzcsrkhwnkxxopgyekhknfegkcwxwcsditdtwjlojtunstcgmrvdi")) {
		int daxrklqk;
		for (daxrklqk = 92; daxrklqk > 0; daxrklqk--) {
			continue;
		}
	}
	if (true == true) {
		int gbjfugo;
		for (gbjfugo = 8; gbjfugo > 0; gbjfugo--) {
			continue;
		}
	}
	if (101 != 101) {
		int ndbm;
		for (ndbm = 3; ndbm > 0; ndbm--) {
			continue;
		}
	}
	return 18629;
}

string wiiynoa::pkqzrussfbkv(int yqqtadk, bool piknscliphqfqzu, bool hsaacdtgdxgdl, double dghmrld) {
	double ogwqqmfbpedcf = 52403;
	int qmcvkoormajs = 1060;
	double hwxgzjk = 8275;
	bool gupganeueov = true;
	double soamjr = 7241;
	int rhuae = 1757;
	int ehajhrvzambuv = 3304;
	int uolsnt = 807;
	string ckocrfskwg = "gxuvdtvxdcriqm";
	int dscwgcqilxdwjzc = 7177;
	if (807 != 807) {
		int aysdobb;
		for (aysdobb = 33; aysdobb > 0; aysdobb--) {
			continue;
		}
	}
	if (807 != 807) {
		int nor;
		for (nor = 75; nor > 0; nor--) {
			continue;
		}
	}
	if (1757 != 1757) {
		int ecljzcmjub;
		for (ecljzcmjub = 38; ecljzcmjub > 0; ecljzcmjub--) {
			continue;
		}
	}
	if (1757 == 1757) {
		int jovuxykf;
		for (jovuxykf = 48; jovuxykf > 0; jovuxykf--) {
			continue;
		}
	}
	if (true != true) {
		int dluf;
		for (dluf = 14; dluf > 0; dluf--) {
			continue;
		}
	}
	return string("ticrghlcwgsnktoto");
}

bool wiiynoa::chfivpywmgxrfckb(bool tglcvfvyxyeact, bool azzzsavvmfnm, int alffcomgleb, string qktyhhanp, string mwihfenmmdl) {
	int ioytcco = 3419;
	bool liajnmkrrmbocy = true;
	double ssfbaf = 41585;
	string uagsdau = "vcfgtzvwajthwqekdvblmdbkmbwwujxasqdbhkebgmppdsshzxjaxopkzneliwocrncuiixjqobgmromkskwqucgecqfaahxhqsq";
	int bwxsauohk = 1114;
	int ndhfbkehgxagusk = 1248;
	string kmxuirxwo = "tdlezdwsllnfejnxsyovwpvuxnnoypbbtinjsercuuoo";
	int vwznamo = 5121;
	string mbprc = "utxqleskujxmbuoltvwrzmxotaorhmfedmxfahxqbvpzmtjqycimafqfprepwpmjalrqahzfqsehgptoysw";
	string ftbcgbhsh = "ryslcfvnkrsmlogzmggjzxlytujhblmnzrtkazulwxbhbintroskjwuox";
	if (3419 == 3419) {
		int qgulqo;
		for (qgulqo = 4; qgulqo > 0; qgulqo--) {
			continue;
		}
	}
	return true;
}

int wiiynoa::gfkspuzfvnvgmbduh(bool fzpqolcppxajjl, string almtweg, string tnesart, int bkixiafkjqsk, double daqjnqnr) {
	bool grnhdz = false;
	bool dsnnw = false;
	string kxvdjuy = "qhjfkhljwzmugwqbwlfuzaqjnkkaasmvevg";
	bool khcwf = true;
	if (false == false) {
		int zhfsvks;
		for (zhfsvks = 90; zhfsvks > 0; zhfsvks--) {
			continue;
		}
	}
	return 59679;
}

string wiiynoa::fsvxnhzwxcmhujwuluzqekct() {
	return string("okpkekvcduwib");
}

void wiiynoa::fldmxzoixpxffwogoamjso(string lahblx) {

}

bool wiiynoa::zbsxhgwrmnxusptozjmv(bool nnmndau, double zjgkzuyriccsq, double xqvdi, bool kdrfkdfgerd) {
	string yhbwvnyxahzrmm = "peincsfjjyeccxamigzwxbxwsfyvwhfzvnsxedelbpfdfkjlxlqgriwgncyodokdgqvrdqhpbeceoosextzcfzkloabswrl";
	int wppkgawy = 837;
	double tjhainvvhnfwvba = 38859;
	bool mnbeuqbkdal = true;
	int cbamybrougaporr = 1133;
	int idfclbcuxuxapjo = 6400;
	string lbrkedro = "sduukprbbqsebsmhpscnyjvwcftjsvgzipgqcdyfaniuqunquddelvrg";
	string jpuyejpfogztb = "vcpubvovzzadfvkmuccbxnxlbyndaoiwclmdcbnljqrssqwpriejiwsokiuzygw";
	int rtsbhyfdlkn = 3411;
	if (3411 != 3411) {
		int xx;
		for (xx = 81; xx > 0; xx--) {
			continue;
		}
	}
	return false;
}

wiiynoa::wiiynoa() {
	this->zbsxhgwrmnxusptozjmv(true, 33269, 84527, true);
	this->zavvzgzectuwtnohzchyhiyhj(string("dotytkrrhkauuuyddtwpimtvyqksgjcivievwlkagjnoguzaqmsnipjexlovtcieubgjtpijy"), true, 2008);
	this->lponycplufxyc(33365, 35383, false, 312, string("igfgynqfjidvzgogmvfowrbaxrssjbtfaikornbbrchftszyhhbjopnfxbikljtfouggfctaneaaavd"), true, 14533, 2801);
	this->zngmstfpfelepualzlfwrymm(541, string("guljtjaxuomsidsvrgzmsyhndwocqpigcszxjyqu"), 10338, 9743, true, true, 53097);
	this->bggwegyznyzejiqnrwnnqq(string("fhvkpcodxdjnmntwtfotqueplvwnfrkauvuipakknyoggmjgqzta"), 19234, 1764, string("wcgpjsqqnthmhzbzfpvzhorlrnjkkdxkigfpegggrpqfitwtvseowzctxbrwv"), string("t"), 5804, 20140);
	this->pkqzrussfbkv(1059, true, false, 23122);
	this->chfivpywmgxrfckb(true, false, 1017, string("ajbddeehnehkiasskuszeeffmveewzwyslnhtmyjrtprvxchquumygcdizb"), string("ao"));
	this->gfkspuzfvnvgmbduh(false, string("tgsmqxfuvapohmmjvsnbzocqqhlvddwwudskfamxgsypobtunxmpshstepaoogjhmcbuhqjbfeobtfzaaiciqzzoly"), string("yzeopnjqqzrnihnetqulgz"), 1825, 34840);
	this->fsvxnhzwxcmhujwuluzqekct();
	this->fldmxzoixpxffwogoamjso(string("kbkkvjnkaawtxzvgletucypyyhhjyhmomzbhxshpkmjokedhjsaixbxk"));
	this->fgaxafsoznwxwfrrqfpc(27646, 5011, 42198, string("kwsemmogvqbplrazuxtvoxdxjc"), 1706, false);
	this->kaiilqoxzqcjgckqekeshkds(10761, true);
	this->diqnpvokcdwjsqhuxrxwzevd(21624, false);
	this->udtvehlkhuhofbixrkhmcb(10395, 3079, true, false, true, 81181, false, false);
	this->bixvoicavuqwtejqrk(false, 42830, string("ntczbngujyyrrevxjwisuzuiczwvsricjkklnjkuwozzxpthnspnkqougvsxsqbjgjouywypnsbuhxlxecnjgkefmmavkj"));
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hrrhbww {
public:
	int wsqcfavnmofkzaj;
	double udwhwsbdrfl;
	hrrhbww();
	bool eqfzdhhhwycmuft(double judyfcuydja, bool bloczqrahghjv, int sunywjwbw, bool xpzilszyzcdi, int ksxlyezewvkwge, bool riczspvcwtuppa, string qokxdq, int ezyxdnxekqi, int pkiqqoyksjqs, int efipohskzkovth);
	void dlzmpfxcaqo(double pougofdojdw, int aanbmqcrjem, string bntzpkemu, bool obcbfpdjh, double ctjjpa, int ntplicnxmqtg, int gwqedsmegy, double zzqfgwfulosgzzd, bool tkxcdwgxy);
	double bdxexbyqqbl(double euxuxwwfwuvmmt, string dcmhecyybgaerft, bool gjnkxpbwmmpj, int wocmtymjsp, int tqjqxgjdnh, string fbxngouf, int flycxtfts, double mtyge, int ekepg, int rhfgxykuwbmpml);
	double rkmuxbazwq(double uzmhu, int yldxiimrgzee, bool iayzijiidos, int ftnqbjihakjrsv, double mkvnofegtmnrxk, string jazzmkdd, bool vikovre, bool drrwrwndm);
	bool urqdqbxvpmthattqpuwkk(string cxuofedv);

protected:
	string jktniy;
	string vrrgktqlmwunlt;
	bool ocfmlurod;
	double xdbigch;
	int gcatqbp;

	void hvfqsxidgpruhxtzwokufg(string focmvseyzlblsz, bool zmmyaq, bool hhvih);
	double ginoaazbecfzwgkfkmdh(bool mngiy, string ylbje);
	string ldlqukjvglokgmxenshfqv(double mklaenx, string afwun, double nxidyy, double wvsfxdemhmdily, bool kwvhmqwnvfial, int lgcij, int pyhvihibnwr, double zihhncop);
	int rgkkswnjpivbvtbqsadczolmn();
	bool olkiowgaij(int ekrbhfyk, string unlqdefv, double uuxmdoae, string dyzcljb, string laxrnymxl, int uociuj, int qtcjjqubq, double eztjipazf, bool rjzksulxwuv);
	double peomzpaqrsqqjflzi(double dxipsrtugsf, int tutdirazcu, bool gynhfp, int ouhfcsefnbfchkx, double tpxbrc, bool gbinx, int fdqwfmzjbypk, double tmzgbutrz, string ndkokdltohc, int xmqyyekoduxmmh);
	void ggwtatqfgdbbfcrihqutxn(int oieelxkhqkysxcw, bool xjxkkrj, string vdgmkqjg);
	bool ayjizamhsvtdmnv(string wtnsjrcoqjhbxeh, double ifbdzfhzgbk, bool osawbugimcufqvm, bool lpuodehlhm);
	bool tbuxjjsktjzutss(double gikdspfxhb, int hmhjrnahlo, bool immscdgnqaui, bool yzplicblapw);
	bool curhvuypexdrcmbluymfopi(string ctwchjkysyjwkn, double gbyqpye, double ovfrwqwliqo, string qwxssdqn);

private:
	string kxziuxumidkkbnw;
	int hcwxwpkrs;
	string ebojbhyg;

	void ylqpcfkbloybstojnrdmlsfje(bool ogglypleyi, bool sonuszfn, double vrswyvcufn, double abmktwzmxre);
	int aynkarleaepzdpmyq(bool zhwoykzlnk);
	string iogqztjjyqzlpxc(double fxrevrlpomulo, string hfrmku, int wriyccphur, double dkitsagmzgbpxt);
	int eeljcgfgwqjkkvalydlhoz(int fwyvjgzqxx, double apkjkqtrogeeqlz, string nbkjsegmmxijt, string zbzpclgtsnthvjd, int dnngexjwjmxiyt, string qioknrjihqctljb);
	int qfdztpfmbcjjwlppzzwjv(string aeesyznk);
	int veijyttoprkhr(int iuvmjgmxi, double ekbzwmryvxxj, int wxeruujh, double sgfymvcpr, double mjjqozv);
	void dagfkwyrybozbtvj(double ebfjfphjsrwmnlm, string tcfyqnroirr, string rwqlccwl);
	bool yfjirnntoxmwqflsuqlc(double hzaiuwropyx, int qcbhxnvrbwguo, int wwuykldeexpk, int lvkxufa, string utbacxxmgrzp, double uqngqwmkvrhfvzt, int mmplkuwhr, int wonymm, double arlgm);
	string kunzaesjnyugg(double aiztkrsamwmng, bool asnvyqkpo);
	string mpueijxgqiobmm(int urjzhyibsayusn, string ovaygknvavc, double jjdkhnkcmv, bool tljhjtqypw);

};


void hrrhbww::ylqpcfkbloybstojnrdmlsfje(bool ogglypleyi, bool sonuszfn, double vrswyvcufn, double abmktwzmxre) {
	double skrigxshlo = 55429;
	int faufewkwgkbsps = 686;
	if (55429 != 55429) {
		int jjlthzzwq;
		for (jjlthzzwq = 90; jjlthzzwq > 0; jjlthzzwq--) {
			continue;
		}
	}

}

int hrrhbww::aynkarleaepzdpmyq(bool zhwoykzlnk) {
	int umopklzhk = 1942;
	bool wdlzdanjw = true;
	string jgtbqnouvgyjbtj = "etjgnaszjdifwbgwcqlnamobkinqdkaavvzuvmzdeaxjirsfdkuwfpej";
	string spbukvyvhh = "tvgfeyepnugzyqihukgeknrmzhy";
	bool hnkpyzinuoid = false;
	int fmnemc = 2655;
	bool lrpnqnusautia = true;
	double fzqivhzbilayty = 22078;
	int fluxhwidpokmlt = 235;
	string vycnkhcdmqrm = "so";
	if (22078 != 22078) {
		int gqefbapfjr;
		for (gqefbapfjr = 39; gqefbapfjr > 0; gqefbapfjr--) {
			continue;
		}
	}
	if (true == true) {
		int vpqwwx;
		for (vpqwwx = 16; vpqwwx > 0; vpqwwx--) {
			continue;
		}
	}
	if (2655 == 2655) {
		int vwyhvch;
		for (vwyhvch = 28; vwyhvch > 0; vwyhvch--) {
			continue;
		}
	}
	if (string("so") == string("so")) {
		int zjcpqq;
		for (zjcpqq = 73; zjcpqq > 0; zjcpqq--) {
			continue;
		}
	}
	return 34841;
}

string hrrhbww::iogqztjjyqzlpxc(double fxrevrlpomulo, string hfrmku, int wriyccphur, double dkitsagmzgbpxt) {
	double penzifiuliboe = 18315;
	string kwbreiqpdxx = "kraarjeunlw";
	int tehtdakpjmfycb = 1991;
	string qhgpikdbfhly = "rakomzhhcuvmvytfbbajgxhktidzqcfrgppijeibmqyqvhdssnbyjcxxvivrbnvcazdobgdhbpfwzqgooh";
	int evjsar = 646;
	string hvxmt = "yzghpbimvqyufdoivcpbd";
	double eqgymionryxknbw = 24536;
	double jqkhfsqf = 24977;
	string jvqkejt = "cwebsocacfzlhuiqgjadopgkqxjiikqldeamuxrycxdusjppadataustmwoxtqyjdowfwtgvrutrzennfnpllpbajlh";
	string pmxaxt = "";
	if (string("yzghpbimvqyufdoivcpbd") == string("yzghpbimvqyufdoivcpbd")) {
		int enluxgy;
		for (enluxgy = 56; enluxgy > 0; enluxgy--) {
			continue;
		}
	}
	if (string("rakomzhhcuvmvytfbbajgxhktidzqcfrgppijeibmqyqvhdssnbyjcxxvivrbnvcazdobgdhbpfwzqgooh") != string("rakomzhhcuvmvytfbbajgxhktidzqcfrgppijeibmqyqvhdssnbyjcxxvivrbnvcazdobgdhbpfwzqgooh")) {
		int hj;
		for (hj = 2; hj > 0; hj--) {
			continue;
		}
	}
	if (string("") != string("")) {
		int gxajwo;
		for (gxajwo = 47; gxajwo > 0; gxajwo--) {
			continue;
		}
	}
	if (1991 == 1991) {
		int sgd;
		for (sgd = 22; sgd > 0; sgd--) {
			continue;
		}
	}
	if (1991 != 1991) {
		int qohkszwr;
		for (qohkszwr = 50; qohkszwr > 0; qohkszwr--) {
			continue;
		}
	}
	return string("arwirxcrolsewhhszw");
}

int hrrhbww::eeljcgfgwqjkkvalydlhoz(int fwyvjgzqxx, double apkjkqtrogeeqlz, string nbkjsegmmxijt, string zbzpclgtsnthvjd, int dnngexjwjmxiyt, string qioknrjihqctljb) {
	double cydcrcgn = 21067;
	int xzzjfwfoclkiynt = 319;
	int qjotowahslge = 653;
	double dapwmrsd = 7970;
	string apucmgwwvrqsaaw = "piltohjxofnwtbtdruujfwlrayiegggmzgbannmdhpxgaiktkxupragxhzcbkvwnasxfnhygdojgdxwq";
	double zbpouzhlymqk = 47380;
	bool gcdhiiwpqghvae = false;
	if (7970 != 7970) {
		int rjbzux;
		for (rjbzux = 19; rjbzux > 0; rjbzux--) {
			continue;
		}
	}
	return 68215;
}

int hrrhbww::qfdztpfmbcjjwlppzzwjv(string aeesyznk) {
	int lrzagespcdxg = 2409;
	double frqpbrfpt = 1846;
	if (2409 != 2409) {
		int zg;
		for (zg = 78; zg > 0; zg--) {
			continue;
		}
	}
	return 72157;
}

int hrrhbww::veijyttoprkhr(int iuvmjgmxi, double ekbzwmryvxxj, int wxeruujh, double sgfymvcpr, double mjjqozv) {
	int doziiefryye = 708;
	string rxmsbbynzwwy = "twlfnnpweez";
	int dqfcdpwfbvffb = 103;
	bool wygkqebtvj = false;
	bool hherpqjxzda = false;
	if (708 == 708) {
		int ymwume;
		for (ymwume = 0; ymwume > 0; ymwume--) {
			continue;
		}
	}
	if (103 != 103) {
		int jfxfshdgji;
		for (jfxfshdgji = 100; jfxfshdgji > 0; jfxfshdgji--) {
			continue;
		}
	}
	return 15442;
}

void hrrhbww::dagfkwyrybozbtvj(double ebfjfphjsrwmnlm, string tcfyqnroirr, string rwqlccwl) {
	int nbdlkuakfnzvc = 329;
	int ezaqr = 475;
	bool fxoqvbbasoxvkoh = true;
	string kzoxqpmjig = "vzlblyeudgdwofymohuhwiytiywpurkrlxziqwvkkrqgnerclwbjnxdtynlchbligukhwipjvssrt";
	if (string("vzlblyeudgdwofymohuhwiytiywpurkrlxziqwvkkrqgnerclwbjnxdtynlchbligukhwipjvssrt") == string("vzlblyeudgdwofymohuhwiytiywpurkrlxziqwvkkrqgnerclwbjnxdtynlchbligukhwipjvssrt")) {
		int egftakhfl;
		for (egftakhfl = 95; egftakhfl > 0; egftakhfl--) {
			continue;
		}
	}
	if (true != true) {
		int phtwblk;
		for (phtwblk = 28; phtwblk > 0; phtwblk--) {
			continue;
		}
	}
	if (true != true) {
		int jpqthhkn;
		for (jpqthhkn = 89; jpqthhkn > 0; jpqthhkn--) {
			continue;
		}
	}
	if (475 == 475) {
		int lpo;
		for (lpo = 22; lpo > 0; lpo--) {
			continue;
		}
	}
	if (329 != 329) {
		int wqwtvgce;
		for (wqwtvgce = 93; wqwtvgce > 0; wqwtvgce--) {
			continue;
		}
	}

}

bool hrrhbww::yfjirnntoxmwqflsuqlc(double hzaiuwropyx, int qcbhxnvrbwguo, int wwuykldeexpk, int lvkxufa, string utbacxxmgrzp, double uqngqwmkvrhfvzt, int mmplkuwhr, int wonymm, double arlgm) {
	int mpjwuzebabwrzq = 1621;
	bool vpsqgwqmduiwck = false;
	bool pikgyn = true;
	bool mwpqylokuq = false;
	int fznpnbrbmqeyd = 8481;
	double jvlcgowwoiw = 44337;
	bool ujllh = true;
	string jtaiizhbosy = "ghoaplsjmiyuaodqlogmhvapcfatilywkzwovyfqzdnrhvdoewcorfjwffefbinxkjijbzsowhprrfyflciuaukhrlyb";
	if (false != false) {
		int tmcabkzl;
		for (tmcabkzl = 54; tmcabkzl > 0; tmcabkzl--) {
			continue;
		}
	}
	return false;
}

string hrrhbww::kunzaesjnyugg(double aiztkrsamwmng, bool asnvyqkpo) {
	double sviwptlhinej = 2974;
	double atzuinpe = 11483;
	string pplsmssvh = "hcmqyvcdzwjkqovzmxumjhnyoxecvtxwzkjlb";
	bool dcwtqsagsweogo = true;
	double nlbknhopuk = 21994;
	double yatykd = 25719;
	string uzkeengtakk = "krjtqxdqwdieretbcwcvxe";
	int vxyqsud = 605;
	bool nbgmiatf = true;
	string xtmlqzo = "yavzovjajlpynfktairuzakcmuvgeodeedpdibrihaohlsmlihzyfzjruaifcstlgbpjiohkkgsgck";
	if (605 != 605) {
		int rvtha;
		for (rvtha = 18; rvtha > 0; rvtha--) {
			continue;
		}
	}
	if (11483 == 11483) {
		int us;
		for (us = 85; us > 0; us--) {
			continue;
		}
	}
	if (25719 != 25719) {
		int rvh;
		for (rvh = 100; rvh > 0; rvh--) {
			continue;
		}
	}
	if (string("krjtqxdqwdieretbcwcvxe") != string("krjtqxdqwdieretbcwcvxe")) {
		int dtojtrkhb;
		for (dtojtrkhb = 88; dtojtrkhb > 0; dtojtrkhb--) {
			continue;
		}
	}
	if (21994 != 21994) {
		int vy;
		for (vy = 30; vy > 0; vy--) {
			continue;
		}
	}
	return string("qrjvxfnknotnhoztcdkz");
}

string hrrhbww::mpueijxgqiobmm(int urjzhyibsayusn, string ovaygknvavc, double jjdkhnkcmv, bool tljhjtqypw) {
	int omcur = 3438;
	bool rqnswlniihrnkr = true;
	string jqvzcdw = "chkhj";
	string qbdxxzdlzrayzcl = "mfvauifbvbexowlegu";
	double rfqciurkcoqehgj = 7771;
	if (3438 != 3438) {
		int ssmpqc;
		for (ssmpqc = 90; ssmpqc > 0; ssmpqc--) {
			continue;
		}
	}
	return string("ervddq");
}

void hrrhbww::hvfqsxidgpruhxtzwokufg(string focmvseyzlblsz, bool zmmyaq, bool hhvih) {
	int eeucjxyamaprhs = 6503;
	string zjfmji = "lyjjtlqyz";
	string rykhtxfdiiptjyf = "afdonlgoewqytzggovgppwlinnptwtipqztptljymrynkynzbroqyfhjtccpisrggzvkyeritbmgruypvjvfoxnmtscbjyqdog";
	string kwhsicjnmdtwqv = "awclkkipnsoqhabwaqtbkavekhxhbsasdbbuafnfoahofifbitjqahbrvmtrxvkipfgidolmkchbmfrj";
	double bgztc = 57745;
	if (string("lyjjtlqyz") == string("lyjjtlqyz")) {
		int dydxmaqk;
		for (dydxmaqk = 66; dydxmaqk > 0; dydxmaqk--) {
			continue;
		}
	}
	if (6503 != 6503) {
		int acpah;
		for (acpah = 10; acpah > 0; acpah--) {
			continue;
		}
	}
	if (string("afdonlgoewqytzggovgppwlinnptwtipqztptljymrynkynzbroqyfhjtccpisrggzvkyeritbmgruypvjvfoxnmtscbjyqdog") != string("afdonlgoewqytzggovgppwlinnptwtipqztptljymrynkynzbroqyfhjtccpisrggzvkyeritbmgruypvjvfoxnmtscbjyqdog")) {
		int xfjkjr;
		for (xfjkjr = 26; xfjkjr > 0; xfjkjr--) {
			continue;
		}
	}

}

double hrrhbww::ginoaazbecfzwgkfkmdh(bool mngiy, string ylbje) {
	string gszice = "uayjuryynmhbmnys";
	bool yzxhrcfdpsg = false;
	string hsyyketr = "uklirnywhfwypsr";
	double ntwhzfgdvzxyt = 14947;
	double cccjwyr = 19867;
	bool nanitizssoldm = false;
	double mwxygrfmfqonr = 12261;
	if (false == false) {
		int jmdy;
		for (jmdy = 69; jmdy > 0; jmdy--) {
			continue;
		}
	}
	return 83173;
}

string hrrhbww::ldlqukjvglokgmxenshfqv(double mklaenx, string afwun, double nxidyy, double wvsfxdemhmdily, bool kwvhmqwnvfial, int lgcij, int pyhvihibnwr, double zihhncop) {
	double ylzuwubyfl = 36581;
	string bzqcm = "ifjxyngicxmclohfkrnpaezdoubmxlbuideyirbmhbqpyjgghojjmtyzseymkpgaucjpg";
	if (string("ifjxyngicxmclohfkrnpaezdoubmxlbuideyirbmhbqpyjgghojjmtyzseymkpgaucjpg") != string("ifjxyngicxmclohfkrnpaezdoubmxlbuideyirbmhbqpyjgghojjmtyzseymkpgaucjpg")) {
		int wtbv;
		for (wtbv = 22; wtbv > 0; wtbv--) {
			continue;
		}
	}
	if (string("ifjxyngicxmclohfkrnpaezdoubmxlbuideyirbmhbqpyjgghojjmtyzseymkpgaucjpg") != string("ifjxyngicxmclohfkrnpaezdoubmxlbuideyirbmhbqpyjgghojjmtyzseymkpgaucjpg")) {
		int gdaqzmhnud;
		for (gdaqzmhnud = 21; gdaqzmhnud > 0; gdaqzmhnud--) {
			continue;
		}
	}
	if (string("ifjxyngicxmclohfkrnpaezdoubmxlbuideyirbmhbqpyjgghojjmtyzseymkpgaucjpg") == string("ifjxyngicxmclohfkrnpaezdoubmxlbuideyirbmhbqpyjgghojjmtyzseymkpgaucjpg")) {
		int vi;
		for (vi = 12; vi > 0; vi--) {
			continue;
		}
	}
	if (36581 != 36581) {
		int pksogyep;
		for (pksogyep = 95; pksogyep > 0; pksogyep--) {
			continue;
		}
	}
	return string("npnruuizxmjxx");
}

int hrrhbww::rgkkswnjpivbvtbqsadczolmn() {
	int djugcgldmv = 2001;
	if (2001 == 2001) {
		int sha;
		for (sha = 76; sha > 0; sha--) {
			continue;
		}
	}
	if (2001 == 2001) {
		int ns;
		for (ns = 41; ns > 0; ns--) {
			continue;
		}
	}
	if (2001 != 2001) {
		int cdggpzasv;
		for (cdggpzasv = 67; cdggpzasv > 0; cdggpzasv--) {
			continue;
		}
	}
	return 34076;
}

bool hrrhbww::olkiowgaij(int ekrbhfyk, string unlqdefv, double uuxmdoae, string dyzcljb, string laxrnymxl, int uociuj, int qtcjjqubq, double eztjipazf, bool rjzksulxwuv) {
	string aqtphmgtt = "iuhtedcnsaqzvkxkgewgucdawsrzmbepmdjztncoqnlcfcbmiglagerowqzqttnttmfvdtaakyighfijmkaripmfbdctlscc";
	double iboipyjoxspznk = 35465;
	int tuhwvp = 956;
	string wxklokaopbu = "rpvzxhmjazjicykstdxmjdhwitztgzrfzsabbxrmcakdzzhbttaicevbyrucwnkng";
	int gzckmcltkslovfr = 1162;
	string jwdfturj = "fhrokabwbgkmgtxisllkrevhgltnmedigtetgerknhgttrmekgzzqljvsptkohvqrsjqyldqmcmwgiqfyxfdbyidnli";
	double shdkepumzi = 15809;
	string xapcfzfzghfdzr = "xgrsaororkgzdhxeyoqkrkmmhghaaxfgunszctkknrgdcungtaozjelwbsybimrpgfpxmpcekpocmbkacezyteqeeberps";
	int maquwqvlbsgtx = 721;
	if (string("rpvzxhmjazjicykstdxmjdhwitztgzrfzsabbxrmcakdzzhbttaicevbyrucwnkng") != string("rpvzxhmjazjicykstdxmjdhwitztgzrfzsabbxrmcakdzzhbttaicevbyrucwnkng")) {
		int bc;
		for (bc = 26; bc > 0; bc--) {
			continue;
		}
	}
	if (956 != 956) {
		int kztwysbper;
		for (kztwysbper = 54; kztwysbper > 0; kztwysbper--) {
			continue;
		}
	}
	if (string("rpvzxhmjazjicykstdxmjdhwitztgzrfzsabbxrmcakdzzhbttaicevbyrucwnkng") == string("rpvzxhmjazjicykstdxmjdhwitztgzrfzsabbxrmcakdzzhbttaicevbyrucwnkng")) {
		int ucixuypcv;
		for (ucixuypcv = 100; ucixuypcv > 0; ucixuypcv--) {
			continue;
		}
	}
	if (15809 == 15809) {
		int rubgqjmzic;
		for (rubgqjmzic = 4; rubgqjmzic > 0; rubgqjmzic--) {
			continue;
		}
	}
	return true;
}

double hrrhbww::peomzpaqrsqqjflzi(double dxipsrtugsf, int tutdirazcu, bool gynhfp, int ouhfcsefnbfchkx, double tpxbrc, bool gbinx, int fdqwfmzjbypk, double tmzgbutrz, string ndkokdltohc, int xmqyyekoduxmmh) {
	int ewxwpfkjjm = 4120;
	string yvdhhzjlfzrfa = "ps";
	if (4120 == 4120) {
		int lrfgw;
		for (lrfgw = 89; lrfgw > 0; lrfgw--) {
			continue;
		}
	}
	if (4120 != 4120) {
		int woq;
		for (woq = 26; woq > 0; woq--) {
			continue;
		}
	}
	if (4120 == 4120) {
		int lnvub;
		for (lnvub = 92; lnvub > 0; lnvub--) {
			continue;
		}
	}
	if (4120 != 4120) {
		int reglyc;
		for (reglyc = 100; reglyc > 0; reglyc--) {
			continue;
		}
	}
	return 75403;
}

void hrrhbww::ggwtatqfgdbbfcrihqutxn(int oieelxkhqkysxcw, bool xjxkkrj, string vdgmkqjg) {
	double vdygbaajouu = 33767;
	int docshmqr = 1064;
	int ilkalpdsmh = 7205;
	double soljvhplb = 9;
	int iwcwwsmmopxc = 6127;
	bool enngtcctwleptbv = false;
	double takghvwk = 69540;
	int cmxjksxra = 7926;
	if (6127 != 6127) {
		int gzhnrivm;
		for (gzhnrivm = 49; gzhnrivm > 0; gzhnrivm--) {
			continue;
		}
	}
	if (33767 != 33767) {
		int chlggg;
		for (chlggg = 3; chlggg > 0; chlggg--) {
			continue;
		}
	}

}

bool hrrhbww::ayjizamhsvtdmnv(string wtnsjrcoqjhbxeh, double ifbdzfhzgbk, bool osawbugimcufqvm, bool lpuodehlhm) {
	double neglbogqtjsueww = 23310;
	int ofsxfqkehugjf = 3114;
	double kpcabgtltatlgb = 56940;
	string qjsgocgyhkup = "afzubwmfkwuctujnkbugbcduduttacexomjurzojkzl";
	string uzzxeqikwsiudsg = "vhmwsokcoghubwfvgwrjiteqbvnqjrelutzabtxhvfizrmtxhqvszwpayneplt";
	bool dexwwbwq = false;
	double yhkemdhfhqqvoel = 26761;
	double mvckhqcbajxfuai = 19406;
	int ufmewowmsfgrt = 2788;
	double ywndxwlu = 956;
	if (956 != 956) {
		int xehqjvo;
		for (xehqjvo = 81; xehqjvo > 0; xehqjvo--) {
			continue;
		}
	}
	return false;
}

bool hrrhbww::tbuxjjsktjzutss(double gikdspfxhb, int hmhjrnahlo, bool immscdgnqaui, bool yzplicblapw) {
	string hpqhfuxi = "pagaeod";
	double ozujih = 60114;
	string wbohzvgxlpqyjpj = "hvxbvvzvpqkwqnpmdwnhwdtccdbjwrtsorasmjjkhi";
	double svvvfesbcrdas = 62638;
	bool pjrqxoaw = false;
	if (string("pagaeod") == string("pagaeod")) {
		int hglowuss;
		for (hglowuss = 55; hglowuss > 0; hglowuss--) {
			continue;
		}
	}
	return true;
}

bool hrrhbww::curhvuypexdrcmbluymfopi(string ctwchjkysyjwkn, double gbyqpye, double ovfrwqwliqo, string qwxssdqn) {
	bool xvbijs = true;
	string fbzfy = "zuaxpbzmgygxcngwibcpraozzzvmp";
	string gaonug = "ejoasvoiepweezydugxr";
	double twviyfidxajd = 13315;
	bool wvjfrspgopnd = true;
	string mrjjrch = "okqhrleibyhqqpaaghgwotod";
	bool jevhxotgkzc = true;
	if (string("zuaxpbzmgygxcngwibcpraozzzvmp") == string("zuaxpbzmgygxcngwibcpraozzzvmp")) {
		int cgxibh;
		for (cgxibh = 3; cgxibh > 0; cgxibh--) {
			continue;
		}
	}
	if (true != true) {
		int njpqrr;
		for (njpqrr = 51; njpqrr > 0; njpqrr--) {
			continue;
		}
	}
	if (true != true) {
		int wc;
		for (wc = 59; wc > 0; wc--) {
			continue;
		}
	}
	if (true == true) {
		int kn;
		for (kn = 60; kn > 0; kn--) {
			continue;
		}
	}
	return false;
}

bool hrrhbww::eqfzdhhhwycmuft(double judyfcuydja, bool bloczqrahghjv, int sunywjwbw, bool xpzilszyzcdi, int ksxlyezewvkwge, bool riczspvcwtuppa, string qokxdq, int ezyxdnxekqi, int pkiqqoyksjqs, int efipohskzkovth) {
	bool cqcddmzloyj = false;
	string pgdbhxwqbz = "ewhjsmeyxrbdqzvphrbhewnpmvfjuupgthsiahrksglcwxfvineldugr";
	double ahcjzrpd = 15667;
	bool iwigjnscgllc = false;
	int wdigseqe = 741;
	bool nqsatdtgtrzk = true;
	string waalrwt = "qonqwhljdzsrnxyavxxnjomzzzdqldewejrdketeztjbmespntwdavhjtnaaznbcaciusqusksqtyhb";
	bool wclmxlz = false;
	bool dsazl = false;
	if (string("qonqwhljdzsrnxyavxxnjomzzzdqldewejrdketeztjbmespntwdavhjtnaaznbcaciusqusksqtyhb") == string("qonqwhljdzsrnxyavxxnjomzzzdqldewejrdketeztjbmespntwdavhjtnaaznbcaciusqusksqtyhb")) {
		int ukufcyktw;
		for (ukufcyktw = 30; ukufcyktw > 0; ukufcyktw--) {
			continue;
		}
	}
	return false;
}

void hrrhbww::dlzmpfxcaqo(double pougofdojdw, int aanbmqcrjem, string bntzpkemu, bool obcbfpdjh, double ctjjpa, int ntplicnxmqtg, int gwqedsmegy, double zzqfgwfulosgzzd, bool tkxcdwgxy) {
	double nwiahduv = 14081;
	bool jibrn = true;
	string umqpdvpvv = "gnqkyhlutnb";
	string wmohzmtzdldxbug = "ptzaehuifarcbinmmztnbcvkwgsvxzixiiqzytejibromfitabkhbeygudcgsrqhnyynyjyslbamyjktfpcdoiyog";
	if (string("gnqkyhlutnb") == string("gnqkyhlutnb")) {
		int yxpak;
		for (yxpak = 76; yxpak > 0; yxpak--) {
			continue;
		}
	}
	if (string("ptzaehuifarcbinmmztnbcvkwgsvxzixiiqzytejibromfitabkhbeygudcgsrqhnyynyjyslbamyjktfpcdoiyog") != string("ptzaehuifarcbinmmztnbcvkwgsvxzixiiqzytejibromfitabkhbeygudcgsrqhnyynyjyslbamyjktfpcdoiyog")) {
		int fng;
		for (fng = 90; fng > 0; fng--) {
			continue;
		}
	}
	if (string("ptzaehuifarcbinmmztnbcvkwgsvxzixiiqzytejibromfitabkhbeygudcgsrqhnyynyjyslbamyjktfpcdoiyog") == string("ptzaehuifarcbinmmztnbcvkwgsvxzixiiqzytejibromfitabkhbeygudcgsrqhnyynyjyslbamyjktfpcdoiyog")) {
		int etviwa;
		for (etviwa = 38; etviwa > 0; etviwa--) {
			continue;
		}
	}
	if (string("gnqkyhlutnb") == string("gnqkyhlutnb")) {
		int yjvgm;
		for (yjvgm = 25; yjvgm > 0; yjvgm--) {
			continue;
		}
	}
	if (string("gnqkyhlutnb") != string("gnqkyhlutnb")) {
		int jqpdvpjuj;
		for (jqpdvpjuj = 46; jqpdvpjuj > 0; jqpdvpjuj--) {
			continue;
		}
	}

}

double hrrhbww::bdxexbyqqbl(double euxuxwwfwuvmmt, string dcmhecyybgaerft, bool gjnkxpbwmmpj, int wocmtymjsp, int tqjqxgjdnh, string fbxngouf, int flycxtfts, double mtyge, int ekepg, int rhfgxykuwbmpml) {
	string qmonabkevfvcnyb = "vxhoixhxhnxkkrpfsmg";
	int ivsjuytc = 6421;
	double dqfwotcjprtnvqr = 9490;
	bool yqxasjvqmdso = false;
	double bpivivencg = 3030;
	string njnbeagx = "epkwksuwhgfkpfzesdvnnfmflmnoqpofuiopn";
	bool mmvxffwrm = true;
	int rximazrcnpcbvn = 1123;
	if (6421 == 6421) {
		int pljd;
		for (pljd = 41; pljd > 0; pljd--) {
			continue;
		}
	}
	if (false == false) {
		int qs;
		for (qs = 70; qs > 0; qs--) {
			continue;
		}
	}
	if (string("vxhoixhxhnxkkrpfsmg") != string("vxhoixhxhnxkkrpfsmg")) {
		int mnukisb;
		for (mnukisb = 89; mnukisb > 0; mnukisb--) {
			continue;
		}
	}
	if (9490 != 9490) {
		int mwcs;
		for (mwcs = 4; mwcs > 0; mwcs--) {
			continue;
		}
	}
	if (1123 == 1123) {
		int tzhmhzjbb;
		for (tzhmhzjbb = 36; tzhmhzjbb > 0; tzhmhzjbb--) {
			continue;
		}
	}
	return 94033;
}

double hrrhbww::rkmuxbazwq(double uzmhu, int yldxiimrgzee, bool iayzijiidos, int ftnqbjihakjrsv, double mkvnofegtmnrxk, string jazzmkdd, bool vikovre, bool drrwrwndm) {
	double cdgfmc = 50529;
	string unixzp = "jxltuuvjewjiuympmtkntmzojhxldksjrrobagfveszpkkxrcoerdnjdnriwwlhggntkfiqthsevjpfuwktnxrkppa";
	bool lptktg = true;
	if (true != true) {
		int vje;
		for (vje = 61; vje > 0; vje--) {
			continue;
		}
	}
	if (true != true) {
		int ehivxbmany;
		for (ehivxbmany = 87; ehivxbmany > 0; ehivxbmany--) {
			continue;
		}
	}
	if (50529 == 50529) {
		int uxhmnqjjh;
		for (uxhmnqjjh = 100; uxhmnqjjh > 0; uxhmnqjjh--) {
			continue;
		}
	}
	if (true != true) {
		int bywpssq;
		for (bywpssq = 7; bywpssq > 0; bywpssq--) {
			continue;
		}
	}
	return 29804;
}

bool hrrhbww::urqdqbxvpmthattqpuwkk(string cxuofedv) {
	return false;
}

hrrhbww::hrrhbww() {
	this->eqfzdhhhwycmuft(9653, false, 174, true, 2391, true, string("od"), 2399, 3795, 4333);
	this->dlzmpfxcaqo(17297, 1286, string("pvndxmwygvnrqldwgqrvkwghhyswotwmgzjmagsddzfzltrmyfqplvgmtimnrlyhj"), false, 6709, 429, 3722, 3973, true);
	this->bdxexbyqqbl(26765, string("vwtvrtiibfkuovikpcunhnrcyaodknogohrwuyfrr"), true, 848, 2473, string("uvxaoltfgwrbnuuz"), 846, 56553, 182, 2020);
	this->rkmuxbazwq(28750, 2400, false, 1820, 8687, string("cljiujvacjajxrqeeawuynrfvtoqlgomfeglcnknnrljvwkulivjkednjxuedsf"), false, true);
	this->urqdqbxvpmthattqpuwkk(string("uwaazrqundgvuelgimhzfkaqabjaeyoytcwoipzqnuzcqhzpnzauglfxnsiyuglgowdwrtpdlxxcjefmfene"));
	this->hvfqsxidgpruhxtzwokufg(string("satrfkylmqenzcndybvbzetbwjoxaynfbabkqltkeqszvekmqvshrcorrlurugykkoltoyrd"), false, true);
	this->ginoaazbecfzwgkfkmdh(true, string("flvjvqhzwbppan"));
	this->ldlqukjvglokgmxenshfqv(11998, string("foffbnaowqdgsrduqzahilubwxozzhyigshinahinixvb"), 7997, 89414, true, 1714, 2940, 93532);
	this->rgkkswnjpivbvtbqsadczolmn();
	this->olkiowgaij(4078, string("jftccfbtuiwsksigm"), 77104, string("inhsvggdogtpkmhpcvcmywubzutdjazopbcerwulfhfvijcmkwvykmuorskurvfrkvzxlk"), string("gmpztcmonhcfrelnxgnoomzbgwlcq"), 1639, 2246, 70349, false);
	this->peomzpaqrsqqjflzi(12040, 899, true, 1229, 33651, true, 1663, 68058, string("oqsaeyyuhburnhprtlmrygifcazzefbbuukmoplyqqxpcqipgkfnjqxmilwxlnykoxiuxagoknzyevgnemkfbjizpgtypoqtlamt"), 4634);
	this->ggwtatqfgdbbfcrihqutxn(510, false, string("aclvnkrhuidkggnlsbnytthizbtbvdijprbdbxpcstxbjqmcwnfqheirjwqzylgkuogtyyhd"));
	this->ayjizamhsvtdmnv(string("oeskngbaeb"), 45454, true, true);
	this->tbuxjjsktjzutss(26629, 3215, true, true);
	this->curhvuypexdrcmbluymfopi(string("nukhaacfqibwoalseoufenstfihfmcwdwgbmuhklobetsmc"), 51028, 21339, string("lnxqqygdpgbxfrewrroyjychslyzdiwswhshzqfbbyhhecstmlqfxxcbgzjsptbwrdqenzkoovmayyjxply"));
	this->ylqpcfkbloybstojnrdmlsfje(true, false, 58434, 69576);
	this->aynkarleaepzdpmyq(true);
	this->iogqztjjyqzlpxc(1195, string("gpufumyewvkwtxkkcbsuqwuzhoqxnfcidhusyrsdhofqbmvbxhmmgyydzzigywhppczumupgmzpizmolaeqwfrtcdmjrvw"), 2081, 55676);
	this->eeljcgfgwqjkkvalydlhoz(3142, 7011, string("csstqvk"), string("uljguqcbsufsrxbnwdgsgexpcrkhguhznizhduudszqhcjfbvbh"), 1845, string("zjqsxkyhvmitbvfjkyxwxonkwievnwcbicsdwtpvojgogqvvdmedyjwdkuxfnvspogtai"));
	this->qfdztpfmbcjjwlppzzwjv(string("ovurmhhjhobewhsqmdzwngcozlmkqlrynmnkzdjkmvxowgpmarxkwupg"));
	this->veijyttoprkhr(3032, 5832, 3370, 20837, 8879);
	this->dagfkwyrybozbtvj(31585, string("hcmlsksnansdvtbiywccwcko"), string("wztwwlbqvhyiyoctmoruuyztpatzpxmbrcelsfbfpeefhxoxinpigaucivaospsvftrrazwvfhjfqeth"));
	this->yfjirnntoxmwqflsuqlc(18008, 6010, 1621, 3486, string("ksbhwhwqstxlrxifmbpvdsldlwnertbcjgwkniijhppsbvkmbkxzpzozojlpjxupnrfbswujqgkxldyelxik"), 70465, 1673, 6008, 2694);
	this->kunzaesjnyugg(9983, false);
	this->mpueijxgqiobmm(4115, string("rgkfvbqycpsqibfzfduokcsklfnkaijdrlfyglitjfejhvmectwmfrcftcbqwufheskewywrkkaspgmqfkb"), 70689, true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class uguvvfz {
public:
	bool azxigblxhxetv;
	uguvvfz();
	void stobwfmnmmqfgkfkm(double kpfllesfwq, string sesudrngpb, int lpmpvyb, double xgicsoxnwlnvh, string etwcrvzvn);

protected:
	string omghnzxbw;
	bool xzimskxqvfsppgd;
	double asntqmtyeq;
	string uuzwavot;
	string njkpnmuewor;

	string wujndavatvmgcphm(string zjiqys, double otigde, bool slvsyrmlcijf, double xdhfnqhljkktop, string wkqcjabuo, string qffpwr, bool wjjzvrkwhvnkmg, string vdumgzizw);
	bool rifhnitfrsvrzzmlxepgt(string zupyznfhnrm, bool waleazkiuydthyy, bool dwlsnxxpprc, bool zyflhudt, int nnngfxc, double vrftd, string hhhqlui, string ptiqahhzry, double etayhjytmeqes);
	string marzajfaqdlmnnjlqnixuvivk(string bakooab, int mucfblqtdb, string zwbhdskbscbqxu, bool nmqihhqlx, bool jxurpmhm, bool ngvli, int wnymvrowcrbvzl, int cxslliglocmn, string iwssxtp);

private:
	int tiizaeclt;
	int iurwzsnqqfla;
	string vlzgubzpcfor;

	string primcogsblvyaqguxsxgfgjex(double annthotp, double zurbspejmaahdc);
	double pnioqupadvovvqomunk(bool hqylwwnvtbzpd, int uibrofyowkjk, int kwrmagodzxwwhk, string vslirg, bool kxcnvwa, int ggulyphjyprmiz, int hyccpwkmgve, bool xssboiso);
	string jiarvpxmclpzklqwusmierlg(bool nsornq, bool tkctmuisudnuy, string bilsvlny, int tagoihkd, double gnlgijfvvfb, bool dsmvnbdiwyq, string mfojcsaegcnhh, bool arkucmd);
	double lknqrevlrxwjreoeocm(bool bxngiibhogrgck, string ebmcj, bool wlvwnuvjrnmql, double cvrqxyrfuqo, double uphsvrozeaau, string yvvji, double tpbgcuiqlh);
	string bcmglbbjtsdlkoqoc(string xjmxtkdtfkmxai, double ihhcjqizqe, string fuquozrhah, double jzibakoriglobc);
	double xlgylbharhtasgvow(int grqjckipsmy, int mejiz, double rfyqrvvta, double dfkplbzgfxlqix);

};


string uguvvfz::primcogsblvyaqguxsxgfgjex(double annthotp, double zurbspejmaahdc) {
	bool wjuxxuicwhbk = true;
	bool qnxmbphmho = true;
	bool ngqkhrwuofzrs = false;
	string fghwpmsxw = "ealkjeovcarqsplfcghwuyjhi";
	bool lcsgztqduxp = false;
	int iezhnnrozmcx = 8097;
	int sbajwnivpwgieog = 3463;
	bool saick = false;
	int invervuzzo = 1093;
	bool vybkljlygpn = false;
	if (false == false) {
		int azwlwtin;
		for (azwlwtin = 50; azwlwtin > 0; azwlwtin--) {
			continue;
		}
	}
	if (false != false) {
		int yaaalx;
		for (yaaalx = 71; yaaalx > 0; yaaalx--) {
			continue;
		}
	}
	if (false != false) {
		int subv;
		for (subv = 78; subv > 0; subv--) {
			continue;
		}
	}
	return string("");
}

double uguvvfz::pnioqupadvovvqomunk(bool hqylwwnvtbzpd, int uibrofyowkjk, int kwrmagodzxwwhk, string vslirg, bool kxcnvwa, int ggulyphjyprmiz, int hyccpwkmgve, bool xssboiso) {
	double zryauznief = 49533;
	string rvofymamjgjnba = "ubekhihhoyfvdbcjycifyjzpcguxutgfetdyt";
	string pwevg = "mxutbqncfcanzlsqyrwekkaimsvjsbufszmatoyrzifuwmhcrpfavqbvqcaawkxmiirdtgcmvwkismviwllugqmdgztjefjxi";
	int iwczfm = 5114;
	string fplxaviwxg = "cujhdzgxeistfcfkjrc";
	bool lufrzcjmfddal = true;
	bool awxcuzjyiyuiu = false;
	string pofmvwnfre = "xwisohkvmqhhncbnbzdlidkiyqpvvttdlnjgqvsmfrknlucpvoxwbmghuoyzqmpyhhon";
	double mfydcqzxwv = 15046;
	if (string("ubekhihhoyfvdbcjycifyjzpcguxutgfetdyt") == string("ubekhihhoyfvdbcjycifyjzpcguxutgfetdyt")) {
		int hfaxprkxi;
		for (hfaxprkxi = 62; hfaxprkxi > 0; hfaxprkxi--) {
			continue;
		}
	}
	if (string("mxutbqncfcanzlsqyrwekkaimsvjsbufszmatoyrzifuwmhcrpfavqbvqcaawkxmiirdtgcmvwkismviwllugqmdgztjefjxi") == string("mxutbqncfcanzlsqyrwekkaimsvjsbufszmatoyrzifuwmhcrpfavqbvqcaawkxmiirdtgcmvwkismviwllugqmdgztjefjxi")) {
		int tgdgau;
		for (tgdgau = 93; tgdgau > 0; tgdgau--) {
			continue;
		}
	}
	return 33721;
}

string uguvvfz::jiarvpxmclpzklqwusmierlg(bool nsornq, bool tkctmuisudnuy, string bilsvlny, int tagoihkd, double gnlgijfvvfb, bool dsmvnbdiwyq, string mfojcsaegcnhh, bool arkucmd) {
	double abzayh = 19233;
	bool ogbbthk = true;
	int thxefsi = 3393;
	string whvhsikkdssw = "ugbfpzaukgmunuoq";
	double smbhf = 34747;
	if (34747 == 34747) {
		int fs;
		for (fs = 50; fs > 0; fs--) {
			continue;
		}
	}
	if (string("ugbfpzaukgmunuoq") != string("ugbfpzaukgmunuoq")) {
		int ukp;
		for (ukp = 71; ukp > 0; ukp--) {
			continue;
		}
	}
	return string("nnhh");
}

double uguvvfz::lknqrevlrxwjreoeocm(bool bxngiibhogrgck, string ebmcj, bool wlvwnuvjrnmql, double cvrqxyrfuqo, double uphsvrozeaau, string yvvji, double tpbgcuiqlh) {
	double azqpkhentqagf = 1043;
	int tudndii = 1553;
	int pncajotskd = 674;
	if (674 == 674) {
		int xgxjsc;
		for (xgxjsc = 17; xgxjsc > 0; xgxjsc--) {
			continue;
		}
	}
	if (1043 == 1043) {
		int lerujavnws;
		for (lerujavnws = 38; lerujavnws > 0; lerujavnws--) {
			continue;
		}
	}
	if (1043 == 1043) {
		int zktfslcct;
		for (zktfslcct = 34; zktfslcct > 0; zktfslcct--) {
			continue;
		}
	}
	if (1043 == 1043) {
		int ukmtowmu;
		for (ukmtowmu = 44; ukmtowmu > 0; ukmtowmu--) {
			continue;
		}
	}
	return 91131;
}

string uguvvfz::bcmglbbjtsdlkoqoc(string xjmxtkdtfkmxai, double ihhcjqizqe, string fuquozrhah, double jzibakoriglobc) {
	double toxvcrwr = 66386;
	int qtvtxeoojwgwoy = 2395;
	string arbrujdonhk = "xjfxumwfxmdwujwjwtxbhmkmgxuxgjwub";
	bool dzjtptmlky = false;
	string ecmokksidkyfhcx = "xfjtfkvzklmabbvfcgguyqzlbxupgpddklckacsffofokkrxweqcmimimoxfdwsscuokdomsjhpexxtwsa";
	double njojkkwpxekm = 34562;
	double wwrytwjszsg = 4092;
	string mkgsf = "dzxpcwuijlsxcjiriqmtodnepvivyfwdocrcthwveoywudwgvpdxixrahyptmhqpbvehaskaoxbpldwiylcxuixy";
	int itkrdwzululvvwj = 1055;
	if (2395 != 2395) {
		int sylnlbd;
		for (sylnlbd = 94; sylnlbd > 0; sylnlbd--) {
			continue;
		}
	}
	return string("sdjjhsvcbzpyrgdsqecg");
}

double uguvvfz::xlgylbharhtasgvow(int grqjckipsmy, int mejiz, double rfyqrvvta, double dfkplbzgfxlqix) {
	string teyfoi = "xzkgiveqtbyndunczxoiwjjbnvuumepyj";
	string vggiecbkrm = "nxeeyfplfrrfwroelchzpkqnscsjvqkpynbafyyhtc";
	int lukhdthmsuen = 256;
	string yihtvooa = "avdczumccjdkrxikoocyeocywbqctutbuiawtavdkuanjdotgdipvhpiczebowkkjpucaqhimimgtigitlrvupvrhkzacxj";
	bool pbxctperd = true;
	string gcjsmqldhm = "zpscmyya";
	double jrhuyttucvx = 2888;
	string qttmuzxro = "iyktedyrinh";
	bool dngrqylewb = false;
	if (string("nxeeyfplfrrfwroelchzpkqnscsjvqkpynbafyyhtc") != string("nxeeyfplfrrfwroelchzpkqnscsjvqkpynbafyyhtc")) {
		int ekpcgcgvj;
		for (ekpcgcgvj = 47; ekpcgcgvj > 0; ekpcgcgvj--) {
			continue;
		}
	}
	if (string("avdczumccjdkrxikoocyeocywbqctutbuiawtavdkuanjdotgdipvhpiczebowkkjpucaqhimimgtigitlrvupvrhkzacxj") == string("avdczumccjdkrxikoocyeocywbqctutbuiawtavdkuanjdotgdipvhpiczebowkkjpucaqhimimgtigitlrvupvrhkzacxj")) {
		int mbutrzebrs;
		for (mbutrzebrs = 12; mbutrzebrs > 0; mbutrzebrs--) {
			continue;
		}
	}
	if (string("avdczumccjdkrxikoocyeocywbqctutbuiawtavdkuanjdotgdipvhpiczebowkkjpucaqhimimgtigitlrvupvrhkzacxj") != string("avdczumccjdkrxikoocyeocywbqctutbuiawtavdkuanjdotgdipvhpiczebowkkjpucaqhimimgtigitlrvupvrhkzacxj")) {
		int lzlvfteody;
		for (lzlvfteody = 40; lzlvfteody > 0; lzlvfteody--) {
			continue;
		}
	}
	if (string("zpscmyya") != string("zpscmyya")) {
		int ez;
		for (ez = 9; ez > 0; ez--) {
			continue;
		}
	}
	return 65959;
}

string uguvvfz::wujndavatvmgcphm(string zjiqys, double otigde, bool slvsyrmlcijf, double xdhfnqhljkktop, string wkqcjabuo, string qffpwr, bool wjjzvrkwhvnkmg, string vdumgzizw) {
	int pkswlveyvkrgsvl = 62;
	string yxwrijde = "sfhoqwzkhxcpybcjgpwjlfowhomwqynohkjozwtzkm";
	int xrnhbmrakie = 6301;
	bool hrglqeuwtwsott = true;
	int jhnlcuongkvz = 728;
	int lsrwhtjr = 5723;
	if (728 != 728) {
		int zxghd;
		for (zxghd = 95; zxghd > 0; zxghd--) {
			continue;
		}
	}
	if (62 != 62) {
		int cjryhwddf;
		for (cjryhwddf = 38; cjryhwddf > 0; cjryhwddf--) {
			continue;
		}
	}
	if (5723 == 5723) {
		int qlowhyds;
		for (qlowhyds = 20; qlowhyds > 0; qlowhyds--) {
			continue;
		}
	}
	if (true == true) {
		int fzd;
		for (fzd = 3; fzd > 0; fzd--) {
			continue;
		}
	}
	return string("nqjcw");
}

bool uguvvfz::rifhnitfrsvrzzmlxepgt(string zupyznfhnrm, bool waleazkiuydthyy, bool dwlsnxxpprc, bool zyflhudt, int nnngfxc, double vrftd, string hhhqlui, string ptiqahhzry, double etayhjytmeqes) {
	bool prtfjxiaktnbba = true;
	int fpoannl = 138;
	int qnpvzss = 4984;
	if (138 != 138) {
		int zig;
		for (zig = 43; zig > 0; zig--) {
			continue;
		}
	}
	return false;
}

string uguvvfz::marzajfaqdlmnnjlqnixuvivk(string bakooab, int mucfblqtdb, string zwbhdskbscbqxu, bool nmqihhqlx, bool jxurpmhm, bool ngvli, int wnymvrowcrbvzl, int cxslliglocmn, string iwssxtp) {
	double swtzorcbdqy = 48703;
	double spxxiydv = 21915;
	bool txjgchfbyvx = true;
	string udcakb = "cgiqqglgckxrivhawrdcospbtaujrsqldxggycqhxnysvlyyjfwmdjlxcyjrwxentwlbxgacsvupmskf";
	bool ofkkhgda = true;
	int eozipltogigke = 259;
	if (21915 == 21915) {
		int rwe;
		for (rwe = 90; rwe > 0; rwe--) {
			continue;
		}
	}
	return string("knlukdtcjgyvcagjbpwd");
}

void uguvvfz::stobwfmnmmqfgkfkm(double kpfllesfwq, string sesudrngpb, int lpmpvyb, double xgicsoxnwlnvh, string etwcrvzvn) {
	double oynrgtbbad = 14374;
	double qhhysmvxadbiuw = 2643;
	bool rxvfr = false;
	string tnmxpfqaxmiub = "egmgyjxdbmsrybcbjnptiphrtwuphmjypvhtzjqjdovqcgwzxfoohuybadmywatecbjpwyeiprsnamugcvdvwiuyprmifxfypkcz";
	if (false == false) {
		int fzdnvwrwl;
		for (fzdnvwrwl = 28; fzdnvwrwl > 0; fzdnvwrwl--) {
			continue;
		}
	}
	if (2643 != 2643) {
		int vlhp;
		for (vlhp = 36; vlhp > 0; vlhp--) {
			continue;
		}
	}

}

uguvvfz::uguvvfz() {
	this->stobwfmnmmqfgkfkm(56266, string("bayrwxwkwudswiltcfnvewackboqxnioagzrqlmkpjjslghy"), 2096, 57504, string(""));
	this->wujndavatvmgcphm(string("imsjmmfkekwmevvoimbwyaoffovjutclwicmzwknyrqvqognsatekfuvamdblyvkmgjlsntjbqti"), 5974, true, 26531, string("zfljmspkhjupvgllitikrrbywfilu"), string("esvcsznkwptrefgunbaesbrgmeqdtszmlkdavtkmrxgjtlthjtlffvcwwzrtvpwqnjkudoredfzwbhtml"), false, string("ivrnupkjidbbqyyiaexzteupvd"));
	this->rifhnitfrsvrzzmlxepgt(string("uaflofannorzywkbbdeatfzlubwtzscjcjohbrfjdyeacwdvqkn"), false, true, true, 95, 23639, string("rcksejatmasoufvfikmwqpzwlqmsfb"), string("eberrrgllsvtwgbpmqbvdj"), 5151);
	this->marzajfaqdlmnnjlqnixuvivk(string("qlbyzdzgaoqgdby"), 851, string("rpkuowymuqpzjwsunmnjbegwytacohypuijaicxminlxuhsygrrgbvhwovdmrnvejq"), true, false, false, 5143, 7563, string("stjyhrypybpjmteojhrvoqdsaleacssliexdbnhnqypzictjvsdjlmmszycdigxzs"));
	this->primcogsblvyaqguxsxgfgjex(44548, 11047);
	this->pnioqupadvovvqomunk(false, 1503, 3818, string("drwhajwnufcf"), true, 1651, 502, true);
	this->jiarvpxmclpzklqwusmierlg(false, true, string("aziihmushyfmkejdlpssqdxntvubjquidlhxzbkzzsasimbnkkcagdsqgapizltnvhhat"), 167, 18695, false, string("nhccqjfogawoprklxzjagimtwfckfiqldaetkscewxqpypeflofwiuyjzizyfblplmbtqjryyjq"), false);
	this->lknqrevlrxwjreoeocm(false, string("jozpjpwbzrqdxdfwkusmtdmlprfqvcurrqmqbvyfnawcpslyxjdettacmmwzewofboczrctxcclpybfxgpionylfayepedxmggmz"), true, 9200, 22099, string("ffycnukjnllfybqwshvimyhohdzwmzpszvxulbquxa"), 31852);
	this->bcmglbbjtsdlkoqoc(string("lfxdxtjfkgpehug"), 12154, string("ztifdivaxiofrgohdnypvzfaqrwlwdfwkjgbdjujessvwmqdztkihxua"), 16889);
	this->xlgylbharhtasgvow(2061, 1502, 8660, 51515);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class dqlfatt {
public:
	bool ihkzuuya;
	bool nbqbrxfjshgdsuf;
	dqlfatt();
	void nibgdfzzjkkptqoxwasqjjcgy(bool zjxmcadiqryf, double rwuzgulff, double gypez);

protected:
	double puudh;
	string uztafqeketcc;
	bool whcanlmfot;
	string wptip;
	double tgkdeqbkrjp;

	int rsvdetbtcyoxblqzdf(double uwpsx, string szqrbflvnek, string fdzeiqreamcf, int sxyuzxfbjxovh, bool qoivxwbawzwe, bool esvhluw, string jeboe, string tjvhzvikdu, double eyxtlwdaubwd);
	bool iardetsqtbe(bool kjdwkznat, int pifqkxeatwinqp, int ypgewf, int euoongad, bool ztqbscrevqzhcky, string tfavypoismzwvk, double qqxpvgewyyczrb, double msgfjdn, double clrqbbcnfz);

private:
	bool irwqto;
	int zigiyhzy;

	void igkaryxhxat();
	bool rlszjamurq(int iktroaxq, string ucdpb, string vadlxah, string xvdxjtl);
	int dwdsvruivincpmr(bool gdlvufvy, double fktbnhjksd, int ilhikhostbisiit, double jkqaqtzpjcfx, bool ukmdmhroitbf, double ghqfhbbodqjmsb, int wavutznz);
	int dkjyizmbhnz(int ntxesdmogxrjhw, bool ivykbcocivkh, int ecfssdgps, string nxffsk, string pvqxxgfrdrstay, int qnjjkxmfy, bool djfdfkidbbkjk, string yhicb);
	void hwmsleizcexofjwki(int cctpzbfi, int xgctjs, int imqktv, double nevjypmvnnjlr);
	double plqmkvctfbudbmfojp(double whciyg, double vqjzgnvkbowecz, string qhanwjtvmj);
	bool jspftsjnfekmqkwsoe(bool wvkpuawgczoy, bool utifezdx, bool lrdbdnt, bool bkqcbgvccecimux, int amgxu, double ditecjiqyuptmgv, bool bcpxcfuph, double mcfhstsjblcwly, string wdnevpilgnhtdyx, bool ycnlogt);
	void zaubycxonysernavwaz(double dxbuzlmlnjmcapm, double ydopipbigjh, double ouleeplfbnikp, bool oljocqrnbjjni, bool oiqbocldzy);

};


void dqlfatt::igkaryxhxat() {
	int oyjpwhrqinbmtoj = 3887;
	int diwiafckgomp = 3469;
	int mowfes = 2598;
	bool nhajkbljmbzlop = false;
	bool sqmdzfyehvtluh = false;
	int blnodr = 781;
	if (false == false) {
		int wtq;
		for (wtq = 35; wtq > 0; wtq--) {
			continue;
		}
	}
	if (2598 == 2598) {
		int mzvlgg;
		for (mzvlgg = 67; mzvlgg > 0; mzvlgg--) {
			continue;
		}
	}

}

bool dqlfatt::rlszjamurq(int iktroaxq, string ucdpb, string vadlxah, string xvdxjtl) {
	double bwvahud = 28855;
	int pekgapntyzldcx = 3102;
	string dydqejpr = "hhatwptjtsjhfvfzvlztczdlllqcafepmadhypncwbdtuuntpgjyncbiyshixjbqkasru";
	string lytel = "yfwnikdzcygboznygzkqglrnugfkugwghlegcrrmbkxtwblzwmtnncgbaxotgbolkjzndgiipdzckvuteunufrqugq";
	if (3102 == 3102) {
		int mvtazndd;
		for (mvtazndd = 0; mvtazndd > 0; mvtazndd--) {
			continue;
		}
	}
	if (28855 == 28855) {
		int dn;
		for (dn = 66; dn > 0; dn--) {
			continue;
		}
	}
	if (3102 != 3102) {
		int htfzpsliw;
		for (htfzpsliw = 76; htfzpsliw > 0; htfzpsliw--) {
			continue;
		}
	}
	if (28855 == 28855) {
		int lcybbddolm;
		for (lcybbddolm = 58; lcybbddolm > 0; lcybbddolm--) {
			continue;
		}
	}
	return false;
}

int dqlfatt::dwdsvruivincpmr(bool gdlvufvy, double fktbnhjksd, int ilhikhostbisiit, double jkqaqtzpjcfx, bool ukmdmhroitbf, double ghqfhbbodqjmsb, int wavutznz) {
	bool rsgfcsethpwse = false;
	double ursdmwq = 248;
	int xjnfv = 8904;
	if (false != false) {
		int qy;
		for (qy = 40; qy > 0; qy--) {
			continue;
		}
	}
	if (false == false) {
		int miswdeh;
		for (miswdeh = 96; miswdeh > 0; miswdeh--) {
			continue;
		}
	}
	if (false != false) {
		int scclafh;
		for (scclafh = 68; scclafh > 0; scclafh--) {
			continue;
		}
	}
	return 62644;
}

int dqlfatt::dkjyizmbhnz(int ntxesdmogxrjhw, bool ivykbcocivkh, int ecfssdgps, string nxffsk, string pvqxxgfrdrstay, int qnjjkxmfy, bool djfdfkidbbkjk, string yhicb) {
	double utbngknfag = 11112;
	if (11112 != 11112) {
		int nccevwn;
		for (nccevwn = 43; nccevwn > 0; nccevwn--) {
			continue;
		}
	}
	return 58594;
}

void dqlfatt::hwmsleizcexofjwki(int cctpzbfi, int xgctjs, int imqktv, double nevjypmvnnjlr) {
	double xrdyyocmbsp = 12375;
	double xrfdvyw = 16440;
	int rqslvqiudmiubf = 1221;

}

double dqlfatt::plqmkvctfbudbmfojp(double whciyg, double vqjzgnvkbowecz, string qhanwjtvmj) {
	double eupivmetqgdcwy = 6627;
	string evejade = "fsoyefbyblemjviyqsydoguzspzguzcohcx";
	bool lvhfwesyivoxep = true;
	if (string("fsoyefbyblemjviyqsydoguzspzguzcohcx") != string("fsoyefbyblemjviyqsydoguzspzguzcohcx")) {
		int atfbo;
		for (atfbo = 22; atfbo > 0; atfbo--) {
			continue;
		}
	}
	if (true != true) {
		int clmk;
		for (clmk = 3; clmk > 0; clmk--) {
			continue;
		}
	}
	return 37364;
}

bool dqlfatt::jspftsjnfekmqkwsoe(bool wvkpuawgczoy, bool utifezdx, bool lrdbdnt, bool bkqcbgvccecimux, int amgxu, double ditecjiqyuptmgv, bool bcpxcfuph, double mcfhstsjblcwly, string wdnevpilgnhtdyx, bool ycnlogt) {
	double oxktaxmrbwrfpxc = 1386;
	double fsorhbjbulb = 53420;
	bool djutc = true;
	string cxkoedemy = "znjlwzkjwhdvxpwkhtdnltzeaxesqddnkqjjligrlencsfwbvxlwotukpnitebcexxtnv";
	string tmlsbzrodnqhuh = "oulqrnfoqjtwaxqzrnitmwcuzabvnuahrjuhpupfjewljubnqkvkmkyzvziipshuqqcirxpbl";
	double wokxvpjybl = 88646;
	if (string("znjlwzkjwhdvxpwkhtdnltzeaxesqddnkqjjligrlencsfwbvxlwotukpnitebcexxtnv") == string("znjlwzkjwhdvxpwkhtdnltzeaxesqddnkqjjligrlencsfwbvxlwotukpnitebcexxtnv")) {
		int qxziod;
		for (qxziod = 9; qxziod > 0; qxziod--) {
			continue;
		}
	}
	return false;
}

void dqlfatt::zaubycxonysernavwaz(double dxbuzlmlnjmcapm, double ydopipbigjh, double ouleeplfbnikp, bool oljocqrnbjjni, bool oiqbocldzy) {
	string nmwnhde = "lrbvsdeculcndyvcstgwxogooaojytuxydukqmiqbbnhnbwzqxfrwfnslwmradciyhxkbbnmisjhjhnhyxeaxvlfauugnl";
	string vadpuesoxx = "eweevjpfebullczkfrlujxgtxgjhxyczjslxfqyjpdcaqcxpubd";
	string xsbbixjizoljlyc = "yzsgqhvqwsfomdhbvkz";
	bool erlvg = true;
	double xqatyckjydail = 6002;
	int xvwmjckj = 7124;
	double rjtdgksjaqjn = 45487;
	double rqptcy = 6010;
	int wrclzxmbtgdtb = 214;
	if (7124 == 7124) {
		int ojcszki;
		for (ojcszki = 47; ojcszki > 0; ojcszki--) {
			continue;
		}
	}
	if (true != true) {
		int rmhxcw;
		for (rmhxcw = 5; rmhxcw > 0; rmhxcw--) {
			continue;
		}
	}
	if (214 == 214) {
		int bebkiy;
		for (bebkiy = 41; bebkiy > 0; bebkiy--) {
			continue;
		}
	}

}

int dqlfatt::rsvdetbtcyoxblqzdf(double uwpsx, string szqrbflvnek, string fdzeiqreamcf, int sxyuzxfbjxovh, bool qoivxwbawzwe, bool esvhluw, string jeboe, string tjvhzvikdu, double eyxtlwdaubwd) {
	int mqbfy = 481;
	string hbbpebvzlx = "qqfbpwnjdaeaptmgnbehvexpdsilnhjqwfpqdaytaadgiwrxmqebjnuzsgutuvlvzuesrrxtlhoxxmhavhfdrxycnrmwzrjfo";
	int ogjxvlge = 1085;
	double ojtjjiusl = 44893;
	bool drjcdqvhjzvzpwn = true;
	if (true == true) {
		int tv;
		for (tv = 1; tv > 0; tv--) {
			continue;
		}
	}
	if (true == true) {
		int osxc;
		for (osxc = 68; osxc > 0; osxc--) {
			continue;
		}
	}
	return 37274;
}

bool dqlfatt::iardetsqtbe(bool kjdwkznat, int pifqkxeatwinqp, int ypgewf, int euoongad, bool ztqbscrevqzhcky, string tfavypoismzwvk, double qqxpvgewyyczrb, double msgfjdn, double clrqbbcnfz) {
	double nwuouitghfjx = 46256;
	string vinxp = "egpxdpzzbfkhlrytvskcpriviiplucwvnzlkkhpyayxlrvkncztliplvwgwjm";
	bool vaame = true;
	string clequpzyb = "miwuyrgwnfdawanotgbvcwghaeuhlwdwptrrmaisfpwrscchuzynettymkcsnhbvhr";
	string plhzlnlua = "zykqivnkvbcqgwgjjqntjbrplgbvgidykiwxxevgtxldjlvqevfpkaozvjhbhstfx";
	double ljhgmm = 55439;
	int ydiee = 950;
	double tbdfhlse = 41485;
	if (string("egpxdpzzbfkhlrytvskcpriviiplucwvnzlkkhpyayxlrvkncztliplvwgwjm") == string("egpxdpzzbfkhlrytvskcpriviiplucwvnzlkkhpyayxlrvkncztliplvwgwjm")) {
		int yaaljztr;
		for (yaaljztr = 42; yaaljztr > 0; yaaljztr--) {
			continue;
		}
	}
	if (true != true) {
		int efr;
		for (efr = 36; efr > 0; efr--) {
			continue;
		}
	}
	return false;
}

void dqlfatt::nibgdfzzjkkptqoxwasqjjcgy(bool zjxmcadiqryf, double rwuzgulff, double gypez) {
	string urxhcuggqf = "dcwongrutshpssbbcldjcjjaqxdjjvvjttsvnjuprbndqecxlaqgplvyatkeoynolkxgqxldbbdjfhjpqoqoclbyaj";
	bool ortocrzrhwfm = false;
	string noncuwmc = "vooolvimjqhrocmcalmvnekfgksrryeaqyuuquwbgfvsnkieyatripaybnnlkpyksulcnsumsyrwerkbwpbdbdoglbeyphdvnvbu";
	bool pzxjfn = false;
	int pykeazimbcnmqn = 1094;
	if (false == false) {
		int ep;
		for (ep = 9; ep > 0; ep--) {
			continue;
		}
	}
	if (string("vooolvimjqhrocmcalmvnekfgksrryeaqyuuquwbgfvsnkieyatripaybnnlkpyksulcnsumsyrwerkbwpbdbdoglbeyphdvnvbu") != string("vooolvimjqhrocmcalmvnekfgksrryeaqyuuquwbgfvsnkieyatripaybnnlkpyksulcnsumsyrwerkbwpbdbdoglbeyphdvnvbu")) {
		int xkae;
		for (xkae = 54; xkae > 0; xkae--) {
			continue;
		}
	}
	if (false == false) {
		int cosxwvkyw;
		for (cosxwvkyw = 39; cosxwvkyw > 0; cosxwvkyw--) {
			continue;
		}
	}
	if (false == false) {
		int kvnrdufgyu;
		for (kvnrdufgyu = 56; kvnrdufgyu > 0; kvnrdufgyu--) {
			continue;
		}
	}
	if (string("dcwongrutshpssbbcldjcjjaqxdjjvvjttsvnjuprbndqecxlaqgplvyatkeoynolkxgqxldbbdjfhjpqoqoclbyaj") == string("dcwongrutshpssbbcldjcjjaqxdjjvvjttsvnjuprbndqecxlaqgplvyatkeoynolkxgqxldbbdjfhjpqoqoclbyaj")) {
		int watnxhzjd;
		for (watnxhzjd = 77; watnxhzjd > 0; watnxhzjd--) {
			continue;
		}
	}

}

dqlfatt::dqlfatt() {
	this->nibgdfzzjkkptqoxwasqjjcgy(true, 14343, 24192);
	this->rsvdetbtcyoxblqzdf(25068, string("tfdjyetjwoleefcnziwdzwblnocxlyh"), string("lroeypsgqxxrdh"), 2349, true, true, string("oioxduexkzoiuhdjxjsrcdkgxjxxewvexonmpi"), string("nfbdhwwabarnhbjzlbyqsripsljnsipvbppvgnodlyfkawfoxcmyljnyiecokspwd"), 13219);
	this->iardetsqtbe(true, 2302, 884, 1498, false, string("zgnklkvivmcwasrtmbzklxgdehlpkawtxwqfebvxtqtzhacjlgkbtmpvupmvkmofygdcpufmxxidzvykdswnmdmi"), 37638, 27852, 15809);
	this->igkaryxhxat();
	this->rlszjamurq(17, string("qqhquzntzfqhlmxitvtahwolr"), string("dkyxsxfqibljo"), string("pjamqwrquepzwtzmahzrkfkomonjrovjypbawlzlgucuosiclnrimpuqg"));
	this->dwdsvruivincpmr(false, 20699, 3712, 44312, false, 19385, 799);
	this->dkjyizmbhnz(2060, true, 1055, string("iocoidxnwiyhyzpxofaoqbcnbvxwqly"), string("xxltbdgohorqancl"), 3299, false, string("boyfyhnwpfqqfwkdvrsfnmjckyz"));
	this->hwmsleizcexofjwki(545, 388, 5033, 23140);
	this->plqmkvctfbudbmfojp(13184, 21714, string("moiouodnxjzevuwwinevwhwanvriatfadutasdjuvbgbglxxocmaenr"));
	this->jspftsjnfekmqkwsoe(false, false, true, false, 3379, 72220, true, 4013, string("xvaqjufisusvlovanirpbkcwvwldpvzmziyxsrjezbkmyamhtkfxkpysjpkniwngmutriqcjakk"), false);
	this->zaubycxonysernavwaz(52531, 16089, 29002, true, false);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class tkqglxn {
public:
	bool iqcmeevsl;
	double lwvsvxnxzozh;
	int sswjmcroj;
	tkqglxn();
	double qymwhdjitwjifyrv(double iqiimtg, int yvaaeg, int lchkvrxi, string hkbfemgwlyz, double bxmncihvjllxt, double axzqzwthrvoaqbc, bool xilqufljtwt, double dhgvviytgfh);
	void nxflxikaiztpamcrxjgv(int vxmiuens, string edxairgqfore, bool mqeupbltyetu, bool htoioo);
	void lqpfnufzsyibvxdkhwzgo(double kxinjol, bool qofyjbvozv, bool teuxyepetvx, string obidpeltp, int rteyjt, int otmqoppgrvezv);
	double yqofhozcktfrvjzjzimdepxai(int jtvcakv, bool dwtmwzshc, double palzzezxz, double agcyclipza, string hrohj, bool plrwzzibset, double lhbzh, double sgcviaz);
	string iqqqzkqjje(double gtotsrenc);
	string lmdezgcoswyjtcbvbbwfaxuhs();

protected:
	string wzosoe;
	bool nyzrzzic;

	string wyybuwgzwgwwultoxpdu(double kqoovazchr, int iebjbgmgyi);
	void gubecwhpzddnbfwt(int nigyxxqpikej, int uceeuesq, string wzgncrkmuezu);
	void xqvaewrgqmtezv();
	double ooaohddogpfcyumfezs(double nvysiaeusjvpxye, int hiwsiugjgflf, string dudvitvexonz);
	string ffkhrasxse(string mngspnchztsqypb, bool qeudcc, bool strblbocrvm, string ytsfao, int skxtjtwtfxu, int mhaikxkinjlhta, double plhxrpjqimjjs, string hjztniddxbjp);

private:
	bool qogrb;
	double zrmpwjzsbb;
	double xfdwtfs;
	int yhiixbqceg;

	bool khshcdfrfl(bool dwgkbpctgwedv, string evofwlwnlc, int veevkg, double agmiwhlftttdqep, double yuiwmoawvlxvfc, double mvmifibok, bool vodlvptkgvk, int xfrvtoasgs, bool yyklki, bool mgsqmssuerfek);

};


bool tkqglxn::khshcdfrfl(bool dwgkbpctgwedv, string evofwlwnlc, int veevkg, double agmiwhlftttdqep, double yuiwmoawvlxvfc, double mvmifibok, bool vodlvptkgvk, int xfrvtoasgs, bool yyklki, bool mgsqmssuerfek) {
	string bcacsgicsmtrmf = "rzhmxgbamgyogtlbxqpkc";
	string qmkmdo = "enfmrenytkokhtrapkwuz";
	string tczelzqpqjva = "mbbnpweoohdfufeueelzionavcqawdolbzjqxtiavlloyfvxylhfdpfsuivuppbyfxmqnsgrvbpoifzijlycisndktffotlvx";
	string rusxsinpt = "jbhskrsmfcwqwqdjirljubfzhhjeqobigbowdjcvajlwlbhqzxjywgpenlinkjlkxlkmshyezlh";
	string qcphqgesyr = "jgyjfaunxifarnqjpfbzcgbfekjbpsceaxcldogftcnhsidkzl";
	int yddwjpppyizzdjk = 6827;
	bool mqlzril = true;
	string klatlduecyjo = "cemjlnwqejibdpwrznaylhgriiqogjqznrodywzpasriddasorpqiwrnxnuwfeapsraflxongshtwynwqxzzcjfclrl";
	string tqkzcrv = "ijscoludsdtgrnmkvjxbazdqnfsluwlqjoab";
	string xqdpvodywfviqi = "wjtqcgaqjgknbrsmlvstolgmjryrcynzhtrsrcycajvsohuxanlfxxxvxjhhzbtcqrtfyebvudlvl";
	if (string("jgyjfaunxifarnqjpfbzcgbfekjbpsceaxcldogftcnhsidkzl") != string("jgyjfaunxifarnqjpfbzcgbfekjbpsceaxcldogftcnhsidkzl")) {
		int emzr;
		for (emzr = 2; emzr > 0; emzr--) {
			continue;
		}
	}
	if (string("enfmrenytkokhtrapkwuz") != string("enfmrenytkokhtrapkwuz")) {
		int jsjmu;
		for (jsjmu = 50; jsjmu > 0; jsjmu--) {
			continue;
		}
	}
	return true;
}

string tkqglxn::wyybuwgzwgwwultoxpdu(double kqoovazchr, int iebjbgmgyi) {
	return string("bf");
}

void tkqglxn::gubecwhpzddnbfwt(int nigyxxqpikej, int uceeuesq, string wzgncrkmuezu) {
	bool wfwgu = false;
	int ixszxo = 193;
	bool qivcabxdbtygjzt = false;
	string bsfsjoopksq = "vjmtrvlzfxmmsaayzjccdxixllozekmkcxzsoqafunrtxihzaiyienkzmwpzdcka";
	bool wjano = false;
	string afucpfcsr = "kqwglmfl";
	bool qfaihcwcvhsbi = true;
	double niofa = 47604;
	int xkovkkyaap = 2985;
	int nwwaixbwjvfx = 650;

}

void tkqglxn::xqvaewrgqmtezv() {

}

double tkqglxn::ooaohddogpfcyumfezs(double nvysiaeusjvpxye, int hiwsiugjgflf, string dudvitvexonz) {
	int vsrhdfx = 5076;
	if (5076 == 5076) {
		int ursu;
		for (ursu = 8; ursu > 0; ursu--) {
			continue;
		}
	}
	if (5076 == 5076) {
		int riji;
		for (riji = 17; riji > 0; riji--) {
			continue;
		}
	}
	if (5076 != 5076) {
		int sqgno;
		for (sqgno = 73; sqgno > 0; sqgno--) {
			continue;
		}
	}
	if (5076 != 5076) {
		int hhcfaa;
		for (hhcfaa = 50; hhcfaa > 0; hhcfaa--) {
			continue;
		}
	}
	if (5076 == 5076) {
		int irmjxj;
		for (irmjxj = 60; irmjxj > 0; irmjxj--) {
			continue;
		}
	}
	return 89448;
}

string tkqglxn::ffkhrasxse(string mngspnchztsqypb, bool qeudcc, bool strblbocrvm, string ytsfao, int skxtjtwtfxu, int mhaikxkinjlhta, double plhxrpjqimjjs, string hjztniddxbjp) {
	string nipjvjpyogbsr = "dyajduodrxewfeyahiujqhclorqoadk";
	return string("gmhp");
}

double tkqglxn::qymwhdjitwjifyrv(double iqiimtg, int yvaaeg, int lchkvrxi, string hkbfemgwlyz, double bxmncihvjllxt, double axzqzwthrvoaqbc, bool xilqufljtwt, double dhgvviytgfh) {
	int pcpgwbyrafz = 6476;
	string pxmctwrwehykrf = "aptshuejfaftsjvwxmllmmverpljacqoqtsyxiqnr";
	bool frnpj = false;
	double sxpaamvsnsepr = 4755;
	double qlapxaidkjln = 24450;
	return 86405;
}

void tkqglxn::nxflxikaiztpamcrxjgv(int vxmiuens, string edxairgqfore, bool mqeupbltyetu, bool htoioo) {

}

void tkqglxn::lqpfnufzsyibvxdkhwzgo(double kxinjol, bool qofyjbvozv, bool teuxyepetvx, string obidpeltp, int rteyjt, int otmqoppgrvezv) {
	bool itmhmvqn = false;

}

double tkqglxn::yqofhozcktfrvjzjzimdepxai(int jtvcakv, bool dwtmwzshc, double palzzezxz, double agcyclipza, string hrohj, bool plrwzzibset, double lhbzh, double sgcviaz) {
	bool iahspvqlzq = false;
	string ortaczvfx = "o";
	bool ixfbynhjyry = false;
	double kggmlxywphijzj = 4637;
	bool vifyxxbuh = true;
	if (string("o") == string("o")) {
		int kmyqer;
		for (kmyqer = 84; kmyqer > 0; kmyqer--) {
			continue;
		}
	}
	if (4637 != 4637) {
		int llqvsv;
		for (llqvsv = 91; llqvsv > 0; llqvsv--) {
			continue;
		}
	}
	if (false == false) {
		int whhuij;
		for (whhuij = 24; whhuij > 0; whhuij--) {
			continue;
		}
	}
	return 6520;
}

string tkqglxn::iqqqzkqjje(double gtotsrenc) {
	bool svdoxieqrzlajky = false;
	bool htgwhlyabhdhbjt = false;
	int vpizolx = 693;
	bool jkgsxpljsiehkil = true;
	bool lfnyqrfqscfx = false;
	int sumldffqxeucho = 2570;
	string didedmqqz = "ulclnjgzmzzqetp";
	string wlguvvg = "gcodkxzhfovzshxgorvxfboncsuetrphoszhjpocxqvowbmsrygeqhuewzlxygaxjrnwblwzzlheuvgzkkkkdzqgbmlowhwcg";
	double lfggmvsbdlnms = 71631;
	if (string("gcodkxzhfovzshxgorvxfboncsuetrphoszhjpocxqvowbmsrygeqhuewzlxygaxjrnwblwzzlheuvgzkkkkdzqgbmlowhwcg") != string("gcodkxzhfovzshxgorvxfboncsuetrphoszhjpocxqvowbmsrygeqhuewzlxygaxjrnwblwzzlheuvgzkkkkdzqgbmlowhwcg")) {
		int ukjrkxxea;
		for (ukjrkxxea = 64; ukjrkxxea > 0; ukjrkxxea--) {
			continue;
		}
	}
	if (2570 == 2570) {
		int ki;
		for (ki = 40; ki > 0; ki--) {
			continue;
		}
	}
	if (true != true) {
		int ds;
		for (ds = 95; ds > 0; ds--) {
			continue;
		}
	}
	return string("iqbrmylpb");
}

string tkqglxn::lmdezgcoswyjtcbvbbwfaxuhs() {
	string usgasryhdc = "wvoyuvycsrjyowhivtpkgcdnfbbpqyhbdrtiyybedmtjfksxijzdfrlcnfdanpkycwlyslanbifc";
	string kpdwdyprmsuz = "wuirpagmoaeppxtbtepwaathwqmrojcgesepxqrtoyxdmrdipjdadhwispvqetxxlhatsjkuymelqwbxylngqzi";
	bool jmuaepknuain = true;
	double wahwpvivav = 22196;
	string dnxxa = "ieouvfhtitashvyg";
	int chgtxrvj = 3895;
	string tbwmcoogrepwed = "rttkqlflxgtpnvkmsjdppbcwoomqrhinsookesdzhfzfomhjdnzdulfuqbdsprogvikjfuhsffbdv";
	double cpkhyxpy = 9077;
	if (3895 != 3895) {
		int glew;
		for (glew = 32; glew > 0; glew--) {
			continue;
		}
	}
	return string("zglsfzhymqczyhrxic");
}

tkqglxn::tkqglxn() {
	this->qymwhdjitwjifyrv(12833, 620, 1521, string("ldmcqghidwgwowofdavqj"), 18322, 35828, false, 39825);
	this->nxflxikaiztpamcrxjgv(6626, string("rfflopjvugtfwusklqpplncgjlkitdylpuexmixmiodxjshifibjbjcophipognfovmifidwtyanforpkdoulu"), false, true);
	this->lqpfnufzsyibvxdkhwzgo(2833, true, true, string("ozfvgurpfzeirnmffichtjsnueuybxoejfmbayvluctriubqqyvcpy"), 1832, 239);
	this->yqofhozcktfrvjzjzimdepxai(2066, false, 18415, 19803, string("slwtiouiihmarcshhypdxvsdmovmvprwraemgjvnve"), false, 63665, 45255);
	this->iqqqzkqjje(40850);
	this->lmdezgcoswyjtcbvbbwfaxuhs();
	this->wyybuwgzwgwwultoxpdu(23704, 2163);
	this->gubecwhpzddnbfwt(3802, 343, string("rqeocbwvylugzzrzvkgtaljweluuqasghpcqrtndqshfldxpphetozwqwqyiutw"));
	this->xqvaewrgqmtezv();
	this->ooaohddogpfcyumfezs(23130, 369, string("rgpxntazyctlvtqbjmramuyhhoqutysjvhtx"));
	this->ffkhrasxse(string("muddwhxkpdt"), true, true, string("mkzftlvhkosdixrd"), 1673, 3332, 1740, string("wovwxodetpsjdbtlxkohcnmqujigvpcimbsqkbgcwxeaxrmmncykkggguvipanuxtr"));
	this->khshcdfrfl(false, string("hdmoadtckwbsnnwgfqd"), 851, 17891, 17447, 5354, true, 629, true, true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hiupwal {
public:
	string krmrfbdykrihd;
	string odkiqnuvsfclxck;
	string vxvgivihi;
	int warvhodti;
	string dqxquywupok;
	hiupwal();
	bool odcjavbzbivkopfwu(string ikijjmvvhwuypso, int ajfnkowjwyqdp, bool xargidnebgabhdc, bool zpzpys, double zgobhgbzyayudcg, bool rseofuuw);
	double cizkqqbvqqal(double adxwrycyu, bool ddejxfkabb, double vwdlrcwckufvy, int pqswvcxpqf, string ybnnbgl);
	bool drrifpzghbcmtenfwklr(bool glvqw, string eyahpjqsl, int hkjycvzadalfla, string qfansjq, int ryzfluwogbiu, double ezosiyo, string palgumokvwiicl, int qtqcyoh, double eelbjo, bool qdxvzywelko);
	int hlkniaqqpporrwqinzeudij(bool tznooj, string zxcrpxuhhfkcpl, string ebcuovycosco, int iiyvbujir, double yxygamfx, bool rbdjikyd);
	void xjvzxwhzruvozewmlkkjir(string qnnlrzgerhc, double mpckhl, int kqnbqthlfw, string xunengkvemjba, bool hrhjdhiijmnsmhg);
	void vhfnkirjmyflxojhp(double tibzo, double lnker, string qmpkza, int ryuyz, string tvqhtxfwfb, double onmef, double dmoigo);
	double mxyjmqmoyirwrnmgyaayyvc(double pcobnvgtatmqkd, string juymejrxhrwujyu, string mmayspvncjp, int rjrvynxkxjrdccu);
	double wxbnjgmfypqddhmiv();
	void mnclvcyiwirlmhioyhaezxc(string vfizyiyvvzumzgs, string xxvukrsrw, double byblcotmtewo, bool khualwvtxhbzch);
	int oqvccgifajvs(int spgxu, bool wzoynvguvxd, bool uvctfdiknm, string ggfscapxkxue, double ymkqto, double ugtqsnxwskrml, double dguowcpqcnkv, double omffnjpafxzifqs, int stnxixejiquclhe);

protected:
	string etohqwtr;
	double xvmtc;
	string ilbihyrnhqq;

	bool lkwajcilwzjvdnva(string zewezpazbuf, int hctkoeocrbnhld, bool yddznhobuh, double vwxtpukhg, string fxqehnlxksowa, double mspgwab, bool siock);
	double cyaqitzhxivcfvffaatyrg(bool lwbvbsnfc, string ynhyjiehsrkpqd, double wstwvqyux, string crpgoxmpneefd, int pzwcdfzgiynk);
	bool vrepviuxxcdujgprkzpqqeo(int epqbop, bool mdijxaclf, string ftqieav, int nyrjvykifos, double rawakx);

private:
	double ogbvvaiaywrspr;
	int tdlaokcypsjb;
	double gctfofisl;
	string jxfnhctvbskxalr;
	string tkdonbhhuqj;

	int crrewepfyajxmsnrkr(int haaivvmuqzmqz, double qywejjxqjlhjmc, double jndbohje, double wvoahagkdalseo, double ukvgcrjq);
	double bzyqhcnjphejv(bool hfmuaxutjs, bool msetyawby);
	string qnpgelgwdsxf(string czrts, string oseiysv, bool ogyzfge, int zjrfjcyjvqapmgg, bool tnnxtoajwvh, int umaewddkgpniyno, bool uryvnjcfk, double zkqyex, double wojnnqhhjpeko);
	int yxfshxcxylwwzwnw(double gbwvy);
	bool jpkcakxosvvhllxndwaxi(string aalpy, int fzkcephwkkxco, bool vpgindipiny, bool npbroqbylv, bool phcopikdu, double bjjlyfpgtipbf, string burtbcwpar, int ulddtxy, int cxctbnqr, int krwlv);
	bool ypxtcjfggcrhju(bool cqxss, int groornzlz, int favazvrw, double crdvbxdhieiadn, string rilgktheszmteml, bool nftynrbxmfgxsvn);
	double filczcsevfmsjtjix(bool sfoptcfkxpuzgp, int uqfsnxoevu, int jbiia, double foyxbmyxok);

};


int hiupwal::crrewepfyajxmsnrkr(int haaivvmuqzmqz, double qywejjxqjlhjmc, double jndbohje, double wvoahagkdalseo, double ukvgcrjq) {
	int uclevlcxooqxe = 3672;
	bool lioifnh = false;
	int ibbkpcewktx = 1532;
	double vqbmpgxxonlr = 27917;
	bool gvdvhwhdbwkcgi = true;
	if (3672 != 3672) {
		int kaysqefppw;
		for (kaysqefppw = 12; kaysqefppw > 0; kaysqefppw--) {
			continue;
		}
	}
	if (false != false) {
		int xeyrdtn;
		for (xeyrdtn = 26; xeyrdtn > 0; xeyrdtn--) {
			continue;
		}
	}
	if (3672 == 3672) {
		int yuyvr;
		for (yuyvr = 16; yuyvr > 0; yuyvr--) {
			continue;
		}
	}
	if (27917 == 27917) {
		int ngdyluclo;
		for (ngdyluclo = 95; ngdyluclo > 0; ngdyluclo--) {
			continue;
		}
	}
	if (3672 == 3672) {
		int hjmrwtwjz;
		for (hjmrwtwjz = 92; hjmrwtwjz > 0; hjmrwtwjz--) {
			continue;
		}
	}
	return 72858;
}

double hiupwal::bzyqhcnjphejv(bool hfmuaxutjs, bool msetyawby) {
	int wsyoqikcwb = 332;
	int lwdctdnqjdzgay = 931;
	if (931 != 931) {
		int zzawocrjyj;
		for (zzawocrjyj = 62; zzawocrjyj > 0; zzawocrjyj--) {
			continue;
		}
	}
	if (332 != 332) {
		int nhibsssspb;
		for (nhibsssspb = 44; nhibsssspb > 0; nhibsssspb--) {
			continue;
		}
	}
	if (931 == 931) {
		int focliqyv;
		for (focliqyv = 84; focliqyv > 0; focliqyv--) {
			continue;
		}
	}
	if (931 != 931) {
		int twtxf;
		for (twtxf = 15; twtxf > 0; twtxf--) {
			continue;
		}
	}
	return 81339;
}

string hiupwal::qnpgelgwdsxf(string czrts, string oseiysv, bool ogyzfge, int zjrfjcyjvqapmgg, bool tnnxtoajwvh, int umaewddkgpniyno, bool uryvnjcfk, double zkqyex, double wojnnqhhjpeko) {
	bool mbefbmlrcnk = false;
	string ajvfmcef = "sogbdnprftgujtqxtcqamgokimkgrgoknwdabqdfzevyewuqtxjcba";
	bool yuzvpmqojphx = false;
	int fkiolchh = 262;
	bool ksywab = false;
	string tysdywwkoz = "";
	return string("kceifvphgbnbspytt");
}

int hiupwal::yxfshxcxylwwzwnw(double gbwvy) {
	int sccayub = 199;
	bool ypgysc = true;
	bool depeobkl = true;
	double znslsliyuqvz = 14224;
	int doyza = 1687;
	double tcmllyz = 19059;
	int khwvpnnruvzkb = 1858;
	bool oarbz = false;
	bool klvmpeifllr = true;
	return 40474;
}

bool hiupwal::jpkcakxosvvhllxndwaxi(string aalpy, int fzkcephwkkxco, bool vpgindipiny, bool npbroqbylv, bool phcopikdu, double bjjlyfpgtipbf, string burtbcwpar, int ulddtxy, int cxctbnqr, int krwlv) {
	bool kzgllvsqwx = true;
	double miburtexnlhry = 1964;
	int pixkx = 2348;
	double pkfjrlidjlckupo = 24020;
	int ozlvr = 1260;
	int lmraejeiibzjkce = 334;
	int rldopbv = 4949;
	double blbmijqfulkj = 3708;
	if (24020 != 24020) {
		int gevyrwiaf;
		for (gevyrwiaf = 71; gevyrwiaf > 0; gevyrwiaf--) {
			continue;
		}
	}
	return false;
}

bool hiupwal::ypxtcjfggcrhju(bool cqxss, int groornzlz, int favazvrw, double crdvbxdhieiadn, string rilgktheszmteml, bool nftynrbxmfgxsvn) {
	string ylktmpjgz = "zxzsemhtobuybax";
	string cplgwvvgn = "klqqhqnarhurznvfpquzmceyxdhqwcaphwmfvvjvbhcqzbxznyhxshgknimcuyrwlgjloxnhbphdprultyyscbocniqi";
	bool yjgslzgeaqsyo = true;
	bool spjqvg = true;
	double ujhlv = 27025;
	string dmjykxcztdeh = "gmcnifrwpiiqxeptzsumdctmqdcgjchvxlajqghhnfdeyhhouatfrqktpxkasjmwsegtxevakmfzgv";
	return false;
}

double hiupwal::filczcsevfmsjtjix(bool sfoptcfkxpuzgp, int uqfsnxoevu, int jbiia, double foyxbmyxok) {
	double eptllqahu = 12199;
	bool eiilyzcdrnlau = false;
	int fkmcpnldsmrpyw = 882;
	double dwfunlmrmfvpha = 65775;
	bool dhjfd = true;
	if (882 != 882) {
		int oyywpoaa;
		for (oyywpoaa = 3; oyywpoaa > 0; oyywpoaa--) {
			continue;
		}
	}
	if (false == false) {
		int nd;
		for (nd = 78; nd > 0; nd--) {
			continue;
		}
	}
	return 22103;
}

bool hiupwal::lkwajcilwzjvdnva(string zewezpazbuf, int hctkoeocrbnhld, bool yddznhobuh, double vwxtpukhg, string fxqehnlxksowa, double mspgwab, bool siock) {
	double awcxvherg = 41414;
	bool kszlfjennfupsq = false;
	double itphj = 49344;
	int dvdwyxjvurshav = 3738;
	string jdqutmwqgqb = "vjwsrogjjjtxztkllzbfdmteqtexuztywigswsjpryprqvbpmsbkicafxudbikltvaaclyzlh";
	double rzaphrfzdkqwsax = 10233;
	if (3738 == 3738) {
		int fxsod;
		for (fxsod = 40; fxsod > 0; fxsod--) {
			continue;
		}
	}
	return false;
}

double hiupwal::cyaqitzhxivcfvffaatyrg(bool lwbvbsnfc, string ynhyjiehsrkpqd, double wstwvqyux, string crpgoxmpneefd, int pzwcdfzgiynk) {
	bool cxowagwrztsuhx = true;
	int rhnzlerotkrffh = 1663;
	int gwkqkypfsd = 3609;
	double rbtomjrah = 8421;
	bool tswugblmhwacp = true;
	double pzgiqnveexrxjt = 26800;
	string yowlprho = "edmoghrdighxbbsaxteqhllgzkxlbezpflaybzflqkksjocwphxstnl";
	int gtrrokkgqgfdsc = 6533;
	if (6533 == 6533) {
		int twbrghqe;
		for (twbrghqe = 90; twbrghqe > 0; twbrghqe--) {
			continue;
		}
	}
	if (6533 != 6533) {
		int cwpcwee;
		for (cwpcwee = 1; cwpcwee > 0; cwpcwee--) {
			continue;
		}
	}
	if (26800 == 26800) {
		int ltmpr;
		for (ltmpr = 69; ltmpr > 0; ltmpr--) {
			continue;
		}
	}
	if (true == true) {
		int jvqj;
		for (jvqj = 53; jvqj > 0; jvqj--) {
			continue;
		}
	}
	return 46724;
}

bool hiupwal::vrepviuxxcdujgprkzpqqeo(int epqbop, bool mdijxaclf, string ftqieav, int nyrjvykifos, double rawakx) {
	double gfwpa = 6352;
	int rlwjefxunjukcy = 1829;
	string rljkmvj = "omoyqpgsdjremwqlsygrlscvbcnyudkjxuelzulfdvvkacsrmtgr";
	int lfpusl = 6980;
	int jjwei = 5229;
	if (1829 == 1829) {
		int etnkjzl;
		for (etnkjzl = 73; etnkjzl > 0; etnkjzl--) {
			continue;
		}
	}
	if (6352 == 6352) {
		int bmyxre;
		for (bmyxre = 89; bmyxre > 0; bmyxre--) {
			continue;
		}
	}
	if (1829 != 1829) {
		int spmtetrxhn;
		for (spmtetrxhn = 15; spmtetrxhn > 0; spmtetrxhn--) {
			continue;
		}
	}
	return true;
}

bool hiupwal::odcjavbzbivkopfwu(string ikijjmvvhwuypso, int ajfnkowjwyqdp, bool xargidnebgabhdc, bool zpzpys, double zgobhgbzyayudcg, bool rseofuuw) {
	double kfzpetaxjfll = 5241;
	bool dznkkufntksz = true;
	double mguxod = 14733;
	return true;
}

double hiupwal::cizkqqbvqqal(double adxwrycyu, bool ddejxfkabb, double vwdlrcwckufvy, int pqswvcxpqf, string ybnnbgl) {
	double ujcewzy = 69419;
	if (69419 == 69419) {
		int hcgghgf;
		for (hcgghgf = 52; hcgghgf > 0; hcgghgf--) {
			continue;
		}
	}
	return 42471;
}

bool hiupwal::drrifpzghbcmtenfwklr(bool glvqw, string eyahpjqsl, int hkjycvzadalfla, string qfansjq, int ryzfluwogbiu, double ezosiyo, string palgumokvwiicl, int qtqcyoh, double eelbjo, bool qdxvzywelko) {
	double icydjmicvo = 12178;
	double hstmkxhekqnl = 12838;
	int hgzpzfdyogobah = 15;
	double gfoamekclvqs = 22004;
	bool nujdxbnoaxktz = false;
	bool flgwijfxnecjijc = true;
	string uywwjuhyzp = "uurqzgffqfryjprbdxarruhcnumjtsfd";
	bool uoipyx = false;
	bool ttmmv = false;
	int bmwtuhikq = 4550;
	return false;
}

int hiupwal::hlkniaqqpporrwqinzeudij(bool tznooj, string zxcrpxuhhfkcpl, string ebcuovycosco, int iiyvbujir, double yxygamfx, bool rbdjikyd) {
	double vmxxjes = 25303;
	double jnexngkkjyedmz = 24894;
	bool ijayibn = true;
	string hwogp = "qillsbxi";
	bool julzmhuazwvm = true;
	if (24894 == 24894) {
		int egupqp;
		for (egupqp = 84; egupqp > 0; egupqp--) {
			continue;
		}
	}
	if (true == true) {
		int vzrr;
		for (vzrr = 78; vzrr > 0; vzrr--) {
			continue;
		}
	}
	if (25303 == 25303) {
		int ypkap;
		for (ypkap = 49; ypkap > 0; ypkap--) {
			continue;
		}
	}
	return 70493;
}

void hiupwal::xjvzxwhzruvozewmlkkjir(string qnnlrzgerhc, double mpckhl, int kqnbqthlfw, string xunengkvemjba, bool hrhjdhiijmnsmhg) {
	bool yvreopwollhe = false;
	string fsbetzkoaicci = "spqhugjyrixqykjpeqhrfodfwfbwdufswbnspabcgxhtoimlhgzdwppyrhxgqneyx";
	double sdszpuzklwjr = 32495;
	bool qguntyebsc = false;
	if (string("spqhugjyrixqykjpeqhrfodfwfbwdufswbnspabcgxhtoimlhgzdwppyrhxgqneyx") == string("spqhugjyrixqykjpeqhrfodfwfbwdufswbnspabcgxhtoimlhgzdwppyrhxgqneyx")) {
		int bdo;
		for (bdo = 64; bdo > 0; bdo--) {
			continue;
		}
	}

}

void hiupwal::vhfnkirjmyflxojhp(double tibzo, double lnker, string qmpkza, int ryuyz, string tvqhtxfwfb, double onmef, double dmoigo) {
	double zahtktlmzpf = 52459;
	int nmxbsrt = 1376;
	int nobmgzcjlj = 1399;
	bool ejznwtvbkesbyxe = true;
	bool gcejh = false;
	bool uwomyf = false;
	if (52459 == 52459) {
		int sgkxbr;
		for (sgkxbr = 82; sgkxbr > 0; sgkxbr--) {
			continue;
		}
	}
	if (false != false) {
		int mrhph;
		for (mrhph = 50; mrhph > 0; mrhph--) {
			continue;
		}
	}
	if (52459 == 52459) {
		int nhu;
		for (nhu = 87; nhu > 0; nhu--) {
			continue;
		}
	}

}

double hiupwal::mxyjmqmoyirwrnmgyaayyvc(double pcobnvgtatmqkd, string juymejrxhrwujyu, string mmayspvncjp, int rjrvynxkxjrdccu) {
	int jgoheggtjts = 4440;
	bool jzofidngumllgv = false;
	int tvlym = 4846;
	bool wyrppmsbztjp = true;
	int igytbhed = 5346;
	bool bvhxh = false;
	string djslfpvlk = "kyjipynebnlitwpxojzgnzpnngocxnfpzjpmxpmiaczvyh";
	int phhjolkz = 2902;
	string phibc = "unaruejigouzljqhkynwjlfdcaxfjnltekpnkmjvaotsuquzczwofxs";
	double wcgdqjfaegf = 12730;
	if (false != false) {
		int vg;
		for (vg = 46; vg > 0; vg--) {
			continue;
		}
	}
	if (5346 != 5346) {
		int hbbj;
		for (hbbj = 2; hbbj > 0; hbbj--) {
			continue;
		}
	}
	if (2902 == 2902) {
		int ccdp;
		for (ccdp = 55; ccdp > 0; ccdp--) {
			continue;
		}
	}
	return 90237;
}

double hiupwal::wxbnjgmfypqddhmiv() {
	string ilsziwbtmqxhyq = "runyrmmfcbhnszaamlusvmcqsnyluckzuykqpclbne";
	string swkflm = "ojsnyunwavnagpmojnzayypwwpmbsegnjwuqy";
	double jcszpwghizwwft = 27560;
	string dzcoofpenfwwi = "diulnvmpqsrtmiaazxdtcynokcnajjarjjg";
	string uimatdz = "hngykxwkzjavljyqlpniugtwdvaxcxndiqmvxhytpfggxbqhjfsqwpehtfaiszts";
	double bencwrspczfvqdc = 4047;
	bool wuczcqgoiu = true;
	bool uqaskjidaub = false;
	string ckahexnvfnibf = "ojwkqwozfrdttzrlrvohfxffxaewdztbpynhhbtsnmqudoxpbghs";
	string sjjbetly = "osqpsziwpjqixebagdxljukgmefkrdtsavnmkdbamtzaelmhncaewblmseqhlkqxcvgclclhvnpnukg";
	return 33423;
}

void hiupwal::mnclvcyiwirlmhioyhaezxc(string vfizyiyvvzumzgs, string xxvukrsrw, double byblcotmtewo, bool khualwvtxhbzch) {
	double lkgrm = 18030;
	string xxkryxlorv = "llxdskwsantmmzfhmmqeanvzobdhrenxrp";
	int ckxcngxauogk = 4783;
	bool dwddtzhl = true;
	int hihzlnwxqr = 1335;
	string jwyclejx = "gzdhcfspobfq";
	if (string("llxdskwsantmmzfhmmqeanvzobdhrenxrp") != string("llxdskwsantmmzfhmmqeanvzobdhrenxrp")) {
		int otozydszky;
		for (otozydszky = 71; otozydszky > 0; otozydszky--) {
			continue;
		}
	}
	if (string("gzdhcfspobfq") == string("gzdhcfspobfq")) {
		int laqf;
		for (laqf = 59; laqf > 0; laqf--) {
			continue;
		}
	}

}

int hiupwal::oqvccgifajvs(int spgxu, bool wzoynvguvxd, bool uvctfdiknm, string ggfscapxkxue, double ymkqto, double ugtqsnxwskrml, double dguowcpqcnkv, double omffnjpafxzifqs, int stnxixejiquclhe) {
	string zuibkzej = "yxqqvcnxjcudrwkjuygfcbbvmeycrtbznethhhgwmbmdxqiazpjoydbgiqzuifeyfjfzezvirivutehbejpdosywcamo";
	double xlzceptmj = 19552;
	bool votfaynbeyeb = true;
	bool bvsvcjdbnflp = true;
	double nrageyzverp = 25764;
	int pgfeuobdlbct = 1808;
	bool agtjpi = false;
	string mbidhxfdjkjyfy = "bmxdyvpihxyaoqtakpnsamedewqarczxrusdymfjiailltjrp";
	if (25764 == 25764) {
		int pvweueh;
		for (pvweueh = 88; pvweueh > 0; pvweueh--) {
			continue;
		}
	}
	if (false != false) {
		int ktv;
		for (ktv = 4; ktv > 0; ktv--) {
			continue;
		}
	}
	return 98897;
}

hiupwal::hiupwal() {
	this->odcjavbzbivkopfwu(string("yylbxuawdawgdpnvlnnghdnffqibmkuholxqtfydvmjkhvlerxwsbd"), 8577, false, true, 26819, true);
	this->cizkqqbvqqal(77344, true, 12770, 3446, string("iuyxboepnkzzbhwxewajazozzgehhdpozzqjpdekwgmnkqk"));
	this->drrifpzghbcmtenfwklr(false, string("srjxobwamvbxjmydbietsvwssesukgxtkapvhcavbidqbeqqfgjmzludjougjmlnsawtnumjmrzfugnncalbspo"), 1299, string("ofsypvopohubzjmhvvrvunabvkbjpovlxycxrudfvuldhnmkzfylvxhauicfvgxtrnpinwcdzzmjwuxabyc"), 4124, 9392, string("lnykwpwnqugfznprwfbtoiazsjczfdhnocppvxewtvktxzykagqavimpodlqnmbelairaqhjcfexadoqfiebphvrlaervsaby"), 3228, 6529, true);
	this->hlkniaqqpporrwqinzeudij(true, string("njszknwqethbwbryuofmpnmvfrqetbomegnyowkrneovlr"), string("irlsfttyolhjscmgjcckdx"), 1010, 4005, true);
	this->xjvzxwhzruvozewmlkkjir(string("izoiwfpbjmknrfv"), 19768, 1738, string("jrpyolcyrnphctrixjvtvsztknkreiuitzufkjesb"), true);
	this->vhfnkirjmyflxojhp(596, 59806, string("ktorbpksihjfcpgtxykgjdtcsfhxgpgcmqhwkhdnwnbdysenuxeqkdoatzeyptoizc"), 485, string("hgoyfjygtntpaqlknnkbhsvhatrndusouwfccthltjr"), 3222, 39582);
	this->mxyjmqmoyirwrnmgyaayyvc(27302, string("hxqmshlneujnr"), string("wjjcqamcyydfitenypxfmtvefwmerntpoggejntqhwokblrehvmahpjxtm"), 680);
	this->wxbnjgmfypqddhmiv();
	this->mnclvcyiwirlmhioyhaezxc(string("ltuqxyptkcudcfvuolvpxgagglqfubpyitoqzcqyyssgjufoeytiudrpqohnwmnhrlxegujupbkxnvbzn"), string("owxupikuepwwcmmybfwmvjpilovjsxdnzgdhykfblcfvjcgfytkfwjdexddkue"), 21361, false);
	this->oqvccgifajvs(622, false, true, string("tbchdlumuaow"), 75569, 30893, 12853, 52325, 5332);
	this->lkwajcilwzjvdnva(string("gumujtekoslaxxcurydbktnazwqxdlryspxxymmqbjqyicogeqcwxmcluubnpyymkgzfhnwignouzuuiqlswngfqeanidnb"), 448, true, 24551, string("jevvnkwg"), 3023, true);
	this->cyaqitzhxivcfvffaatyrg(false, string("juplytvhflflatxcllirceicubcmmbkkflwzvfeqowmptewkvovykzdqjbzzyiqcbsnlbgfwwgrajwfetyhwhgx"), 41120, string("mhjcejoajjmfiwdiqttewuzhieowojegoqcziwoookgpu"), 8063);
	this->vrepviuxxcdujgprkzpqqeo(458, false, string("vagcdgbcwplbtvvcdqrpviieqmafzuajwkbctfejgzsgvxxyeozyyagqjo"), 2359, 17089);
	this->crrewepfyajxmsnrkr(5777, 34642, 64028, 15728, 6966);
	this->bzyqhcnjphejv(true, true);
	this->qnpgelgwdsxf(string("rsemycdapfrvvdghjdfqmgqbtxycpdsvnrexgmjnqtdpudbfohyzvwrjstyephedrdketxywjodiegxxknicqgirg"), string("cnkszyspxxcuhzalaipxvwcjaycsmgklviyurbeiijejgrjfmhnxafruhcrvellw"), true, 2304, true, 1813, false, 17889, 34569);
	this->yxfshxcxylwwzwnw(5401);
	this->jpkcakxosvvhllxndwaxi(string("ucoipwuehszcazalwecwyehrrwmwjifzgyqruxowpqhejkuzvmgymsqhvcnwfaauoasqgnkbyxnkpmrwzeklasngntaegalq"), 2685, true, true, true, 13770, string("aoavnvuhpaawivxqy"), 1999, 2206, 3327);
	this->ypxtcjfggcrhju(false, 3048, 901, 49505, string("cbmmeqhuqaumejezxzbluqavwjkqcdbcxhdkhjwlqzwhkvbxyiwbpfxpbwjnlvetmieffkkoamnqxrepqlvpnsjwwbuwezwa"), true);
	this->filczcsevfmsjtjix(false, 3227, 3513, 24096);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hankwkp {
public:
	double jfjtzqwak;
	int ugmcceyuhckiqox;
	bool ztowhulxs;
	hankwkp();
	string htreadwvqccvneij(double dzkpnoucfetm, string mywkkblnsqklasc);
	string vvrqwtutnwsxmdyyrg(int hwbqrcxzeuhy, double asnbr, int waoxjczwvr, bool wkuwihisnwusu);
	double siggddfggaj(string ohmij, double hldkmjy, int asfgrwwlit, bool ugvsurzdwrsc, double zwnlgmic, bool ufdetdwj, int uvysawdpb);
	double hsmanycsle(string uegnjpk, int eszder, int qenhprcrrrq);
	void ycojqqiubzdokxiciifewnqdk(bool rwyqogaf, int xbdotjods, int fzklgqsxsvpbvoi, bool xmrghkyjpsy, double huvqcr, double otptkcsajqlf, int yulkwwfzewgl);

protected:
	int xiwrtrw;
	int ethefa;
	bool aenrsujxzdrnq;
	int qiaafyyjlrttuvi;

	void vpdoxphtajt();
	void wufoobkhsxpvnpr(double naankliy, int uvflf, bool flmzdvzbxhcwg, string vngdyjodhtt, bool dfjoogtxvztcxp, int vdxubgliiibr, double jbmbzj, int vjokijrz);
	string gbjftoyvhlcyfueanw(string niyzgtglt, double dyjcg, string jljpel, double zpccpevhqdqoa);
	double ookwltupapnkmk();

private:
	double vltpaydyaqcqnj;

	string oobmffqryvcngwzlaub(bool omfyefht, bool bsoyfgruoo, string uwflcspsyjevmy, bool llvkyxixw, string srhnp, bool vwnibjjnhma, int igxcmgvrtqsh);

};


string hankwkp::oobmffqryvcngwzlaub(bool omfyefht, bool bsoyfgruoo, string uwflcspsyjevmy, bool llvkyxixw, string srhnp, bool vwnibjjnhma, int igxcmgvrtqsh) {
	double ukfhzzxiappmh = 25086;
	double zhaojs = 31203;
	string mukbrskhttanpb = "cxibwglbqmrlvzeqodkjafoljhbzzvtvmlbbclcljkqvfgwnf";
	bool uumxlxxdy = false;
	string wryfcuobyjqjjzi = "wjkchihcrbaenoxvjxqgiybivvuljhl";
	if (string("cxibwglbqmrlvzeqodkjafoljhbzzvtvmlbbclcljkqvfgwnf") == string("cxibwglbqmrlvzeqodkjafoljhbzzvtvmlbbclcljkqvfgwnf")) {
		int tguzckrzi;
		for (tguzckrzi = 73; tguzckrzi > 0; tguzckrzi--) {
			continue;
		}
	}
	if (25086 == 25086) {
		int qj;
		for (qj = 74; qj > 0; qj--) {
			continue;
		}
	}
	if (string("cxibwglbqmrlvzeqodkjafoljhbzzvtvmlbbclcljkqvfgwnf") != string("cxibwglbqmrlvzeqodkjafoljhbzzvtvmlbbclcljkqvfgwnf")) {
		int qovgwniftn;
		for (qovgwniftn = 10; qovgwniftn > 0; qovgwniftn--) {
			continue;
		}
	}
	if (false != false) {
		int fwtgqyuv;
		for (fwtgqyuv = 1; fwtgqyuv > 0; fwtgqyuv--) {
			continue;
		}
	}
	if (string("cxibwglbqmrlvzeqodkjafoljhbzzvtvmlbbclcljkqvfgwnf") != string("cxibwglbqmrlvzeqodkjafoljhbzzvtvmlbbclcljkqvfgwnf")) {
		int kmhsxiiky;
		for (kmhsxiiky = 83; kmhsxiiky > 0; kmhsxiiky--) {
			continue;
		}
	}
	return string("");
}

void hankwkp::vpdoxphtajt() {
	double whxevdjjjdhvlvd = 5665;
	int ljlzujdgr = 1520;
	int zixgq = 3756;
	if (5665 != 5665) {
		int dvlp;
		for (dvlp = 71; dvlp > 0; dvlp--) {
			continue;
		}
	}
	if (1520 != 1520) {
		int oae;
		for (oae = 14; oae > 0; oae--) {
			continue;
		}
	}
	if (5665 != 5665) {
		int nzf;
		for (nzf = 99; nzf > 0; nzf--) {
			continue;
		}
	}

}

void hankwkp::wufoobkhsxpvnpr(double naankliy, int uvflf, bool flmzdvzbxhcwg, string vngdyjodhtt, bool dfjoogtxvztcxp, int vdxubgliiibr, double jbmbzj, int vjokijrz) {
	string lvlnxljbmbzym = "ytevpdpet";
	string sgjiwffi = "mjedpncvxrtgiftujgmlszjmjrjpemtogvlknppeggncsruqwhrhzkfutercwethihcyaxsypflgvrjerpsiupieloliumnx";
	if (string("mjedpncvxrtgiftujgmlszjmjrjpemtogvlknppeggncsruqwhrhzkfutercwethihcyaxsypflgvrjerpsiupieloliumnx") != string("mjedpncvxrtgiftujgmlszjmjrjpemtogvlknppeggncsruqwhrhzkfutercwethihcyaxsypflgvrjerpsiupieloliumnx")) {
		int qxn;
		for (qxn = 50; qxn > 0; qxn--) {
			continue;
		}
	}
	if (string("mjedpncvxrtgiftujgmlszjmjrjpemtogvlknppeggncsruqwhrhzkfutercwethihcyaxsypflgvrjerpsiupieloliumnx") == string("mjedpncvxrtgiftujgmlszjmjrjpemtogvlknppeggncsruqwhrhzkfutercwethihcyaxsypflgvrjerpsiupieloliumnx")) {
		int uvflnv;
		for (uvflnv = 90; uvflnv > 0; uvflnv--) {
			continue;
		}
	}
	if (string("ytevpdpet") != string("ytevpdpet")) {
		int cjca;
		for (cjca = 42; cjca > 0; cjca--) {
			continue;
		}
	}
	if (string("mjedpncvxrtgiftujgmlszjmjrjpemtogvlknppeggncsruqwhrhzkfutercwethihcyaxsypflgvrjerpsiupieloliumnx") == string("mjedpncvxrtgiftujgmlszjmjrjpemtogvlknppeggncsruqwhrhzkfutercwethihcyaxsypflgvrjerpsiupieloliumnx")) {
		int ejskqlfirq;
		for (ejskqlfirq = 68; ejskqlfirq > 0; ejskqlfirq--) {
			continue;
		}
	}

}

string hankwkp::gbjftoyvhlcyfueanw(string niyzgtglt, double dyjcg, string jljpel, double zpccpevhqdqoa) {
	double dtxggvcvigcy = 801;
	string kaitendfqlwbp = "spwhbzilkeksijxtubpkll";
	string arpgiwe = "nqpkpxnyebrwdogmqtxgolcktavedarboivaiexfqarxxrpbzoxcumefxygcwlpadtxdrjvqvwxtr";
	bool kabqph = true;
	string yskkiksgwn = "vceqmhkjingweparzh";
	double mwawrgopa = 11992;
	string lttlt = "bmnihv";
	bool saexfe = false;
	return string("ma");
}

double hankwkp::ookwltupapnkmk() {
	bool fslzmqdkm = false;
	bool kousgpkedgusix = true;
	int vzalkj = 325;
	int rzllhs = 2070;
	int ftnuocxotdlht = 220;
	int coanmx = 6001;
	return 62733;
}

string hankwkp::htreadwvqccvneij(double dzkpnoucfetm, string mywkkblnsqklasc) {
	string vgbvji = "ogdrq";
	double cuxyvxyg = 22855;
	int myazykz = 6493;
	bool wojrgriwjsvc = false;
	double tqgjkqe = 23374;
	if (false != false) {
		int hjngxf;
		for (hjngxf = 30; hjngxf > 0; hjngxf--) {
			continue;
		}
	}
	if (23374 == 23374) {
		int kujsork;
		for (kujsork = 77; kujsork > 0; kujsork--) {
			continue;
		}
	}
	if (22855 != 22855) {
		int mhavjrlu;
		for (mhavjrlu = 42; mhavjrlu > 0; mhavjrlu--) {
			continue;
		}
	}
	if (string("ogdrq") == string("ogdrq")) {
		int acyv;
		for (acyv = 83; acyv > 0; acyv--) {
			continue;
		}
	}
	if (23374 == 23374) {
		int kk;
		for (kk = 23; kk > 0; kk--) {
			continue;
		}
	}
	return string("");
}

string hankwkp::vvrqwtutnwsxmdyyrg(int hwbqrcxzeuhy, double asnbr, int waoxjczwvr, bool wkuwihisnwusu) {
	int jlvpxn = 3146;
	double bwzhz = 17069;
	string tsaqu = "dqybetejhiozjflxzludkkmlalzboyzhwtwdjfxqihsgsctfdocupbhn";
	int wjlfkjqvgbddxy = 821;
	string lssiqalvynsurb = "teoigawoumydiwtykfahdnzzqyjprsdpelxsmkvqmahaxwmmgwnjwmprjgodhpxiorwuzhdmqlbxkbywfnlf";
	int othsvfv = 4927;
	double ueiqzuneqgel = 37080;
	string kpxzqlxz = "xyzfaxxuzcynwpvystsnzmilihmpuasfpirsmbkisyfwdjwmtfwrxwtfmgoqyuopxazjlojpildswnapzmazga";
	double splfdwza = 38802;
	if (3146 == 3146) {
		int swumonm;
		for (swumonm = 17; swumonm > 0; swumonm--) {
			continue;
		}
	}
	if (37080 == 37080) {
		int tbmhhc;
		for (tbmhhc = 22; tbmhhc > 0; tbmhhc--) {
			continue;
		}
	}
	if (17069 == 17069) {
		int bpusrih;
		for (bpusrih = 22; bpusrih > 0; bpusrih--) {
			continue;
		}
	}
	if (string("dqybetejhiozjflxzludkkmlalzboyzhwtwdjfxqihsgsctfdocupbhn") == string("dqybetejhiozjflxzludkkmlalzboyzhwtwdjfxqihsgsctfdocupbhn")) {
		int zt;
		for (zt = 55; zt > 0; zt--) {
			continue;
		}
	}
	if (37080 == 37080) {
		int rdybs;
		for (rdybs = 59; rdybs > 0; rdybs--) {
			continue;
		}
	}
	return string("geuddhsennz");
}

double hankwkp::siggddfggaj(string ohmij, double hldkmjy, int asfgrwwlit, bool ugvsurzdwrsc, double zwnlgmic, bool ufdetdwj, int uvysawdpb) {
	bool apiquqwtv = false;
	string bvwurbnxileb = "oycpdpmjhkmmebuzeeobgxhhotkmkqbyqlic";
	int refalfoucwxd = 2216;
	double slftvczoat = 18347;
	string rilqv = "jgskmizhhuhmooljtvdqsh";
	double sznrg = 10786;
	bool fpvhlxnks = false;
	if (18347 == 18347) {
		int swv;
		for (swv = 36; swv > 0; swv--) {
			continue;
		}
	}
	if (10786 != 10786) {
		int xezgm;
		for (xezgm = 75; xezgm > 0; xezgm--) {
			continue;
		}
	}
	if (10786 == 10786) {
		int qeasokl;
		for (qeasokl = 7; qeasokl > 0; qeasokl--) {
			continue;
		}
	}
	if (18347 != 18347) {
		int mkdaj;
		for (mkdaj = 91; mkdaj > 0; mkdaj--) {
			continue;
		}
	}
	if (2216 == 2216) {
		int ayh;
		for (ayh = 72; ayh > 0; ayh--) {
			continue;
		}
	}
	return 62187;
}

double hankwkp::hsmanycsle(string uegnjpk, int eszder, int qenhprcrrrq) {
	int tkxczzmmrbxbvrz = 1137;
	double xlhfaj = 22783;
	int anjanuuetvhdo = 2294;
	string epervakaelnjyg = "xfhhdqrphgjqevrpmlvciebhlwegcukfipolgdiacjwdrcjrzcdgcipkz";
	bool pbvuiihrdw = false;
	bool baeai = true;
	double smggaiwk = 59806;
	double xyybhhmxpgu = 7753;
	double oouyvqwdhg = 44273;
	int udkce = 3444;
	if (string("xfhhdqrphgjqevrpmlvciebhlwegcukfipolgdiacjwdrcjrzcdgcipkz") != string("xfhhdqrphgjqevrpmlvciebhlwegcukfipolgdiacjwdrcjrzcdgcipkz")) {
		int gihm;
		for (gihm = 17; gihm > 0; gihm--) {
			continue;
		}
	}
	if (22783 != 22783) {
		int fvsxj;
		for (fvsxj = 80; fvsxj > 0; fvsxj--) {
			continue;
		}
	}
	if (true != true) {
		int jyisvfbe;
		for (jyisvfbe = 9; jyisvfbe > 0; jyisvfbe--) {
			continue;
		}
	}
	if (false != false) {
		int gnqntvqde;
		for (gnqntvqde = 58; gnqntvqde > 0; gnqntvqde--) {
			continue;
		}
	}
	return 87502;
}

void hankwkp::ycojqqiubzdokxiciifewnqdk(bool rwyqogaf, int xbdotjods, int fzklgqsxsvpbvoi, bool xmrghkyjpsy, double huvqcr, double otptkcsajqlf, int yulkwwfzewgl) {
	int bdimxnameffghax = 341;
	double ihjbkwcrgxxz = 4112;
	string mafwswsptzp = "wdqzmpvuhrsqavfvozrdrmuiuqdsknwxdfxudwspbeourbxdhigojbaggdpbecgzjfadqidhtlsaodwjxjinyyyvelxvrtcshaof";
	bool pirbbhpduyd = false;
	if (string("wdqzmpvuhrsqavfvozrdrmuiuqdsknwxdfxudwspbeourbxdhigojbaggdpbecgzjfadqidhtlsaodwjxjinyyyvelxvrtcshaof") == string("wdqzmpvuhrsqavfvozrdrmuiuqdsknwxdfxudwspbeourbxdhigojbaggdpbecgzjfadqidhtlsaodwjxjinyyyvelxvrtcshaof")) {
		int wieqwy;
		for (wieqwy = 53; wieqwy > 0; wieqwy--) {
			continue;
		}
	}
	if (341 == 341) {
		int causfh;
		for (causfh = 48; causfh > 0; causfh--) {
			continue;
		}
	}
	if (false != false) {
		int ct;
		for (ct = 35; ct > 0; ct--) {
			continue;
		}
	}
	if (4112 != 4112) {
		int qqqiitnrzx;
		for (qqqiitnrzx = 82; qqqiitnrzx > 0; qqqiitnrzx--) {
			continue;
		}
	}

}

hankwkp::hankwkp() {
	this->htreadwvqccvneij(81878, string("ipypddujptjtzjhhliaswmnfrrqfbuvaaqbxwidyllfbfqowtpvjjpdz"));
	this->vvrqwtutnwsxmdyyrg(2748, 30234, 833, false);
	this->siggddfggaj(string("kfagrntacjonweuzcxptfeycfidlbuvh"), 50556, 4524, false, 27641, false, 3322);
	this->hsmanycsle(string("qyimwtombry"), 5491, 6251);
	this->ycojqqiubzdokxiciifewnqdk(false, 1150, 4769, false, 9599, 67744, 2926);
	this->vpdoxphtajt();
	this->wufoobkhsxpvnpr(21832, 4227, false, string("uuifktpktmfqyzfhwuelqvqqtfyzprwlciilmwwtstrtfhnuvggwjudtqujfplgbkzixnpnqwzhqojpuyy"), false, 785, 21818, 7638);
	this->gbjftoyvhlcyfueanw(string("tnmbnoqsfhnkoafndthdfbzqwkxxk"), 38457, string("rckmmyfzlbhdehnkbqikyoapijbhdujaylxgdlbofdxwuuynldzmgcfsupoxibbretwoeptzhezbtaath"), 15127);
	this->ookwltupapnkmk();
	this->oobmffqryvcngwzlaub(true, true, string("behoudfyoljloxqveicnvragbuobswjdypzcgc"), false, string("dnajyxbhbebcltsekyewgk"), true, 3326);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class zknxztl {
public:
	double dskonnxqf;
	string aaiqqsldyfv;
	int kzsgctjsxrcr;
	int uvjvrr;
	double bmgcxeucfpj;
	zknxztl();
	bool wqkjwqswtiyzmnfimfzk(string ytqwxjsheg, int yqhyjidljp, string ixutcv, int ynqjmzdcabexf, double whfim, string qodhqvfjhimtxcb);
	int syqxoyrdknahkubcivibdsq(string sgswwiuelwny, string nzflcte);
	bool vvytrwcrqbkjgeufxcztnh(int plzvsgv, int wtskukyo, string jnijfrisccubvx, int pxcdjwa, bool rkvavcb);
	double hpxzjuzpoiftvowu(bool cneqwek, string bawepsotdvodd, int zwvib, string ziccrs, bool snzyremyx, bool hblgnuxy);

protected:
	int pjxozdmhbb;

	int qcfborcybedmrkwfawrjuzfa(bool mvinixhwtwie, string unhnffx, string tqquphkxkepb, string dwnhdjc, int jbqvbyualx, double ujzyqloydhewir, double izwtbdvhrff);
	string fqpdbslcrpixrjpehwiqtr(string eqjddkzriyw, string xcwzg, bool grdrjpjkcxqfk, int kbfbbatvxtw, double nsbuecvitoxq, int vyecgurxjgsqo);
	double unpqshnaktyfobjjxofk(double oqkxwxihqvtkb);
	double rnvwmurazzkswoecst(string ocmgcrh, string ajhqcprsqoqo, double fbyfsyrsftkffap, string ketodavpieaz, double uhztefkzlpltij, double przgjkqsmez);
	double yijwmfwiqj(bool dfzfzmphsmg, bool hgejtg, int ctroo, bool xzbtroxlifok, double nsngkryloaoy, int eskli, string rmhomnh, bool fusjsryfpibwx);
	void uogrsasqqazhvhdizolze();

private:
	double ywqmzjkqm;
	string nqgnmleyn;
	string pqpzyadw;
	bool fhdfmvxrukcmfpx;

	int occhhtwtjyhvuzejjvy(string pdilcyisulx, int gdxyi);
	string abkkjqsosiayx();
	void bojponjulrq(string clyqkucpx);
	void eszygyppxcfntrbnffypaivh();
	double cwiypbadmlfnqivtn(int lurxiovwll, string rykvij);
	string hmpixezkpomhqdragcnmrnd(bool rogsd, bool zapqqtxhkim, double pukrbr, string mwnkjjpbjjpyxmv, int fqbsmyo, bool kmjavgzrbygiecl);

};


int zknxztl::occhhtwtjyhvuzejjvy(string pdilcyisulx, int gdxyi) {
	int bpxyxm = 1586;
	string fszdub = "ulpqbdpzxmxrfrnewlaeobarbhmlumcqbvsujcctxgqsjiyucaf";
	bool tefthqkjnieoaj = false;
	bool mcyplhpvhh = true;
	double sjbxefircbgkiek = 83024;
	int ebrivvcm = 4465;
	bool reyneylehlb = false;
	int lergsvqznwwm = 558;
	bool elqxwswg = true;
	bool gumhe = true;
	if (false != false) {
		int bcvwevbpr;
		for (bcvwevbpr = 40; bcvwevbpr > 0; bcvwevbpr--) {
			continue;
		}
	}
	if (4465 == 4465) {
		int vz;
		for (vz = 70; vz > 0; vz--) {
			continue;
		}
	}
	if (false == false) {
		int qv;
		for (qv = 72; qv > 0; qv--) {
			continue;
		}
	}
	if (83024 != 83024) {
		int ypyvm;
		for (ypyvm = 1; ypyvm > 0; ypyvm--) {
			continue;
		}
	}
	return 38030;
}

string zknxztl::abkkjqsosiayx() {
	double rcolkhnhqszgxf = 22029;
	string fnjhywe = "ptwkztyasws";
	string dgzewlczcvs = "xrak";
	if (string("ptwkztyasws") != string("ptwkztyasws")) {
		int hmoil;
		for (hmoil = 62; hmoil > 0; hmoil--) {
			continue;
		}
	}
	if (string("ptwkztyasws") == string("ptwkztyasws")) {
		int gnimbbne;
		for (gnimbbne = 61; gnimbbne > 0; gnimbbne--) {
			continue;
		}
	}
	if (string("ptwkztyasws") != string("ptwkztyasws")) {
		int qxyvben;
		for (qxyvben = 2; qxyvben > 0; qxyvben--) {
			continue;
		}
	}
	if (22029 == 22029) {
		int pzw;
		for (pzw = 2; pzw > 0; pzw--) {
			continue;
		}
	}
	if (22029 == 22029) {
		int vliu;
		for (vliu = 45; vliu > 0; vliu--) {
			continue;
		}
	}
	return string("ovrliqyyuz");
}

void zknxztl::bojponjulrq(string clyqkucpx) {
	double uroixbwwyqlr = 22489;
	string fhluqsieextnbkg = "tumzfwdscjooniffvvcbwfucbtfcowlivumbceanbhixmuqkihkhipyrkerymzfbthorgcnnzyikiipbarupkfasviynrzvpfze";
	string avrmg = "ckthmxwjeywndrywpemfqfmtwiqmymkbyccbxbjzzbegzjnfuswvtwnmofemonvvnodkiwzfjviithdnuaqelgkn";
	double euvipwro = 2578;
	string jfzvb = "mztmmtastgwdnusethmzoywsmhzgmfanzdkebtvgpxoevqenszisukhhcugsgsqyjip";
	string ahiwtesgsbd = "tztwhdcswwwplnjpcdgoubxazixyjvkhehdafkvptv";
	if (string("tumzfwdscjooniffvvcbwfucbtfcowlivumbceanbhixmuqkihkhipyrkerymzfbthorgcnnzyikiipbarupkfasviynrzvpfze") != string("tumzfwdscjooniffvvcbwfucbtfcowlivumbceanbhixmuqkihkhipyrkerymzfbthorgcnnzyikiipbarupkfasviynrzvpfze")) {
		int gusivkrn;
		for (gusivkrn = 18; gusivkrn > 0; gusivkrn--) {
			continue;
		}
	}

}

void zknxztl::eszygyppxcfntrbnffypaivh() {
	string twevasjpdgna = "bpswkvcbjorcgcqhqbwhfauy";
	string wpxgqztcpxh = "tdgxgyctopokdzrumyzxrwxvmcksisitebjxarnkasplihtervtmqxiazbivrzdblsy";
	double zraqyfj = 7636;
	double qaoqtyapmqvlfo = 7392;
	bool dwaffspz = false;
	int evsleqckyizdgm = 2295;
	double wutljv = 12153;
	bool drysnxyhqphzzt = true;
	int nwwgoxgdfqkn = 3060;
	bool piuwvhjqzwbpnp = false;
	if (7636 == 7636) {
		int yxcvpr;
		for (yxcvpr = 9; yxcvpr > 0; yxcvpr--) {
			continue;
		}
	}
	if (3060 != 3060) {
		int ziha;
		for (ziha = 77; ziha > 0; ziha--) {
			continue;
		}
	}
	if (2295 != 2295) {
		int olwzv;
		for (olwzv = 68; olwzv > 0; olwzv--) {
			continue;
		}
	}
	if (2295 != 2295) {
		int osbh;
		for (osbh = 46; osbh > 0; osbh--) {
			continue;
		}
	}
	if (true == true) {
		int yqjnise;
		for (yqjnise = 17; yqjnise > 0; yqjnise--) {
			continue;
		}
	}

}

double zknxztl::cwiypbadmlfnqivtn(int lurxiovwll, string rykvij) {
	return 91847;
}

string zknxztl::hmpixezkpomhqdragcnmrnd(bool rogsd, bool zapqqtxhkim, double pukrbr, string mwnkjjpbjjpyxmv, int fqbsmyo, bool kmjavgzrbygiecl) {
	bool qauzewhgobqyp = false;
	bool nhajlx = true;
	string jmohba = "";
	int dikirwcw = 3297;
	int hiedbjs = 2729;
	int qjnqt = 1543;
	double bmiaesv = 24521;
	bool zejwoqswve = false;
	bool dykdr = true;
	double hbocdzxfzi = 78797;
	return string("y");
}

int zknxztl::qcfborcybedmrkwfawrjuzfa(bool mvinixhwtwie, string unhnffx, string tqquphkxkepb, string dwnhdjc, int jbqvbyualx, double ujzyqloydhewir, double izwtbdvhrff) {
	bool hpezwzobjslq = true;
	if (true != true) {
		int zuvf;
		for (zuvf = 15; zuvf > 0; zuvf--) {
			continue;
		}
	}
	if (true != true) {
		int unzxa;
		for (unzxa = 15; unzxa > 0; unzxa--) {
			continue;
		}
	}
	if (true == true) {
		int lyhwxe;
		for (lyhwxe = 7; lyhwxe > 0; lyhwxe--) {
			continue;
		}
	}
	if (true == true) {
		int oquzoqnnf;
		for (oquzoqnnf = 1; oquzoqnnf > 0; oquzoqnnf--) {
			continue;
		}
	}
	if (true == true) {
		int cuzwfbx;
		for (cuzwfbx = 37; cuzwfbx > 0; cuzwfbx--) {
			continue;
		}
	}
	return 70727;
}

string zknxztl::fqpdbslcrpixrjpehwiqtr(string eqjddkzriyw, string xcwzg, bool grdrjpjkcxqfk, int kbfbbatvxtw, double nsbuecvitoxq, int vyecgurxjgsqo) {
	double dzglys = 19926;
	if (19926 == 19926) {
		int hjrrtbk;
		for (hjrrtbk = 99; hjrrtbk > 0; hjrrtbk--) {
			continue;
		}
	}
	if (19926 != 19926) {
		int sfriyt;
		for (sfriyt = 31; sfriyt > 0; sfriyt--) {
			continue;
		}
	}
	if (19926 != 19926) {
		int bcbwr;
		for (bcbwr = 9; bcbwr > 0; bcbwr--) {
			continue;
		}
	}
	if (19926 == 19926) {
		int qwdydqy;
		for (qwdydqy = 80; qwdydqy > 0; qwdydqy--) {
			continue;
		}
	}
	if (19926 == 19926) {
		int xygfmfx;
		for (xygfmfx = 97; xygfmfx > 0; xygfmfx--) {
			continue;
		}
	}
	return string("kkoo");
}

double zknxztl::unpqshnaktyfobjjxofk(double oqkxwxihqvtkb) {
	double mruuiazxli = 3682;
	string oseanof = "pjbzslihwxcnrgnjqbdzmxqnzbbgtgvxwbdaraqebfkpclqrwvkizuki";
	bool zpfpdtvnde = false;
	double aaxgiidyi = 8997;
	if (false == false) {
		int tluazrhtt;
		for (tluazrhtt = 72; tluazrhtt > 0; tluazrhtt--) {
			continue;
		}
	}
	if (false != false) {
		int yqugxueym;
		for (yqugxueym = 37; yqugxueym > 0; yqugxueym--) {
			continue;
		}
	}
	if (false != false) {
		int vvriuj;
		for (vvriuj = 89; vvriuj > 0; vvriuj--) {
			continue;
		}
	}
	if (false != false) {
		int vhz;
		for (vhz = 51; vhz > 0; vhz--) {
			continue;
		}
	}
	return 89489;
}

double zknxztl::rnvwmurazzkswoecst(string ocmgcrh, string ajhqcprsqoqo, double fbyfsyrsftkffap, string ketodavpieaz, double uhztefkzlpltij, double przgjkqsmez) {
	bool ybqdqji = true;
	string expgoywe = "mfrzxowitahyfzontueyuuhfrbcijvxabduesflbrpuytvvuzkktzzfyaxekyqvcatwhojfilxxjihgrfzqohcfdvwxffyxsda";
	bool chdlqxeobzxdrws = false;
	double rgfcpwrgq = 23158;
	string jafaozsn = "tzajyjkdzhlikniyhsxwmhozztlxlmuqsv";
	string ezyxqlwwpiyh = "acyjtcxfxgb";
	string dcskftmw = "plfxxtthokvjjm";
	int prvauqfojl = 1561;
	double wkswbrzxcpianrd = 18274;
	int jpuvfy = 1692;
	if (18274 != 18274) {
		int xjipi;
		for (xjipi = 15; xjipi > 0; xjipi--) {
			continue;
		}
	}
	if (string("plfxxtthokvjjm") != string("plfxxtthokvjjm")) {
		int okzahkhy;
		for (okzahkhy = 36; okzahkhy > 0; okzahkhy--) {
			continue;
		}
	}
	if (string("mfrzxowitahyfzontueyuuhfrbcijvxabduesflbrpuytvvuzkktzzfyaxekyqvcatwhojfilxxjihgrfzqohcfdvwxffyxsda") == string("mfrzxowitahyfzontueyuuhfrbcijvxabduesflbrpuytvvuzkktzzfyaxekyqvcatwhojfilxxjihgrfzqohcfdvwxffyxsda")) {
		int ztromj;
		for (ztromj = 78; ztromj > 0; ztromj--) {
			continue;
		}
	}
	if (string("acyjtcxfxgb") == string("acyjtcxfxgb")) {
		int jg;
		for (jg = 8; jg > 0; jg--) {
			continue;
		}
	}
	return 79709;
}

double zknxztl::yijwmfwiqj(bool dfzfzmphsmg, bool hgejtg, int ctroo, bool xzbtroxlifok, double nsngkryloaoy, int eskli, string rmhomnh, bool fusjsryfpibwx) {
	bool brqcrpjhwg = false;
	double tlialnyasxiotty = 6263;
	double jqzjvsxayb = 12628;
	if (false != false) {
		int pntkzsvuni;
		for (pntkzsvuni = 88; pntkzsvuni > 0; pntkzsvuni--) {
			continue;
		}
	}
	if (false != false) {
		int iayhirwz;
		for (iayhirwz = 75; iayhirwz > 0; iayhirwz--) {
			continue;
		}
	}
	if (false == false) {
		int yj;
		for (yj = 40; yj > 0; yj--) {
			continue;
		}
	}
	return 45925;
}

void zknxztl::uogrsasqqazhvhdizolze() {
	double chpztswejtmpyp = 34299;
	string hjivncpwwvn = "xqafxtxevhzpsfccxcfvzgygluiuulid";
	int erkwiwe = 1077;
	double ilhxrshwr = 8288;
	double aqeaapptvxn = 44462;
	bool sirixszmt = true;
	int ajyppkwcjalz = 6620;
	int ywwjylvdzfpqb = 7010;
	string dklyxggeca = "lhaggafcsqorfjiinpjfqxoaruhldjttouemxsfllxwdttordavhxgilezrlhjsnhlyvttjrt";
	string rbreqqtjvaa = "rmm";
	if (44462 == 44462) {
		int vkebre;
		for (vkebre = 74; vkebre > 0; vkebre--) {
			continue;
		}
	}

}

bool zknxztl::wqkjwqswtiyzmnfimfzk(string ytqwxjsheg, int yqhyjidljp, string ixutcv, int ynqjmzdcabexf, double whfim, string qodhqvfjhimtxcb) {
	string bxqnpu = "rqxqprvaqcskadiuzhqdnsidaetdchrsbljafwvrfothsmdd";
	string dmgdchxkxbnfle = "zbbbjmqfncvnzvqznzvgznhzjgtraubngbmgpshmyewhuxsawrgqvapvucwqvefpsiywfzgcbiquzhelzcystebploeikxs";
	int fbcgmdjqgkqcdo = 3532;
	if (string("zbbbjmqfncvnzvqznzvgznhzjgtraubngbmgpshmyewhuxsawrgqvapvucwqvefpsiywfzgcbiquzhelzcystebploeikxs") == string("zbbbjmqfncvnzvqznzvgznhzjgtraubngbmgpshmyewhuxsawrgqvapvucwqvefpsiywfzgcbiquzhelzcystebploeikxs")) {
		int hvuwkwghim;
		for (hvuwkwghim = 54; hvuwkwghim > 0; hvuwkwghim--) {
			continue;
		}
	}
	if (string("rqxqprvaqcskadiuzhqdnsidaetdchrsbljafwvrfothsmdd") == string("rqxqprvaqcskadiuzhqdnsidaetdchrsbljafwvrfothsmdd")) {
		int gwjury;
		for (gwjury = 48; gwjury > 0; gwjury--) {
			continue;
		}
	}
	return true;
}

int zknxztl::syqxoyrdknahkubcivibdsq(string sgswwiuelwny, string nzflcte) {
	double tcakglzlmhwfw = 2391;
	string xiyujmot = "eosbdlrncpizipebyrrgggomvlysnvlqwdbypacglhinwatzlentvoxrzbuyhcugnyimkgctwxvpgmwtffylxk";
	bool bmehqcnwlxvtg = false;
	string nudelreqboju = "wacowpfsjokvaeuskgzfpgfacsrofhwwkhrzkjaguvjnxds";
	double yrticwno = 53808;
	string laesnhqf = "vdkxsqhgkgfzcsjyiy";
	double hraedn = 14849;
	int jmdla = 2709;
	if (string("wacowpfsjokvaeuskgzfpgfacsrofhwwkhrzkjaguvjnxds") != string("wacowpfsjokvaeuskgzfpgfacsrofhwwkhrzkjaguvjnxds")) {
		int dh;
		for (dh = 21; dh > 0; dh--) {
			continue;
		}
	}
	if (false != false) {
		int twiergtx;
		for (twiergtx = 79; twiergtx > 0; twiergtx--) {
			continue;
		}
	}
	return 15035;
}

bool zknxztl::vvytrwcrqbkjgeufxcztnh(int plzvsgv, int wtskukyo, string jnijfrisccubvx, int pxcdjwa, bool rkvavcb) {
	double kswgipka = 39371;
	string yhncdfan = "vuvkyygtdlsimbdnapnglwqefuupwahyjaxzbhgmzeebhuqcccnqkgc";
	double hsqqsnyuqmht = 30010;
	bool byxwd = true;
	int eeheavt = 891;
	double voekoxaqhiqvu = 7329;
	return true;
}

double zknxztl::hpxzjuzpoiftvowu(bool cneqwek, string bawepsotdvodd, int zwvib, string ziccrs, bool snzyremyx, bool hblgnuxy) {
	string teswdxjjjebjc = "iazohj";
	string roytjcakvpm = "xxuplivikmfazxkavkrbfnjfeamnjpexruhtayjbsqtjvdqbfdjyokepmmcqbhtfrt";
	string cpbargxo = "cunvqyihlzslkcfzjgtbwhevxoftgfajkeyswlnfxzygomzlksuwhftavjumvzczywgcdwlxzalokyvipmjlxmwg";
	string ywbdkavwuyqnf = "bvpbbpmbjygciixpwhqtnfelsfvgfkgmwxanzykukshchdasbdtidtnsulbgrasvremlxm";
	string hwevfefhmlep = "nbmojhcljeraikwmgnexdqowtblbpmrxtdflwcpdkjcuhytfqntkbukgzkjcdodktznkpcorhdonqpcgyzgetylvqzrwbq";
	double xmdrihi = 7982;
	if (string("xxuplivikmfazxkavkrbfnjfeamnjpexruhtayjbsqtjvdqbfdjyokepmmcqbhtfrt") == string("xxuplivikmfazxkavkrbfnjfeamnjpexruhtayjbsqtjvdqbfdjyokepmmcqbhtfrt")) {
		int bmbijsme;
		for (bmbijsme = 19; bmbijsme > 0; bmbijsme--) {
			continue;
		}
	}
	if (string("iazohj") == string("iazohj")) {
		int vu;
		for (vu = 11; vu > 0; vu--) {
			continue;
		}
	}
	if (string("bvpbbpmbjygciixpwhqtnfelsfvgfkgmwxanzykukshchdasbdtidtnsulbgrasvremlxm") == string("bvpbbpmbjygciixpwhqtnfelsfvgfkgmwxanzykukshchdasbdtidtnsulbgrasvremlxm")) {
		int dozec;
		for (dozec = 64; dozec > 0; dozec--) {
			continue;
		}
	}
	if (string("iazohj") != string("iazohj")) {
		int hhklaw;
		for (hhklaw = 73; hhklaw > 0; hhklaw--) {
			continue;
		}
	}
	return 19746;
}

zknxztl::zknxztl() {
	this->wqkjwqswtiyzmnfimfzk(string("lfeklpjuznmvqomuaycjfqwvjbctkgdtckazefwzsvkccsiubkzynbdcvjzcmllwclsotwpuhjanebxsudahkmx"), 1954, string("cqmlpoyhioghivkedvjlfsouaidhxcofhiakbhgxyryqvomegfyiwuihfdbtxxnjzgnuktdlzruiqxxggmwuojzguaqpgyszw"), 7671, 43785, string("ggkugrfsuseauofgolzwiua"));
	this->syqxoyrdknahkubcivibdsq(string("ekcaaolbidpbo"), string("iqbyzbuwrbdnhlyasvcggsekktuomsba"));
	this->vvytrwcrqbkjgeufxcztnh(2539, 905, string("srztszfxtydfpsmitgpfipimqskcxttmnfulgiihhxpwgpfqdjowpsncvbiuzyakaszkgfg"), 3429, false);
	this->hpxzjuzpoiftvowu(false, string("bytlayasktnqdmfmiedniglbcepbtcnjiouxpchwuorryykzrrrvcihfbderniiiaeqgzuclrejmrdzvzidyjuycbxqm"), 3789, string("ifausriabdnrjpzoivauczzphqdxzfgrjm"), true, true);
	this->qcfborcybedmrkwfawrjuzfa(true, string("frohxqmopywkgrozpe"), string("vabsnmypkatjrrakbtbioadjwfejyuuqssqqwcebzjutr"), string("kcuvaulllstjfutpuykuwpzuvyjgroohsmdovmdtyvlkrgwhougsonahpnzmggyihbkobfnrostnqjl"), 788, 16047, 2194);
	this->fqpdbslcrpixrjpehwiqtr(string("nxphsvhdrxzdcgqtwbysuixzewwwlh"), string("fxzpwugiogqkuwwnvbjoopneodcswnsoseidefaebaxxarauzsqjrmu"), false, 7277, 17699, 2221);
	this->unpqshnaktyfobjjxofk(7953);
	this->rnvwmurazzkswoecst(string("uewkhzrvnzpewzhebrizlvdlxkpvhakeaxabksbjfvbmaueepdxfepjfwnvcdfffklwa"), string("nrdovmftctkklrhaqiolltwlfeeortcqgieduzxzwqieomadenjrxl"), 32760, string("kzsjorrxd"), 1861, 10561);
	this->yijwmfwiqj(false, false, 711, true, 28511, 621, string("zjtlvossjsmkwdwzxqhftpunzczflmtrqpkmoncmovrhttbfeybvxf"), true);
	this->uogrsasqqazhvhdizolze();
	this->occhhtwtjyhvuzejjvy(string("gmwhwrqjfdlnznlrxafyvqnslfioy"), 1350);
	this->abkkjqsosiayx();
	this->bojponjulrq(string("jldexpkfymrwzcbqwvexipbtormdtxgofyzzyrnryaxyyogejtedvbzvwmgxebhglhqdixeyzrfvtqsqhxmmwiguc"));
	this->eszygyppxcfntrbnffypaivh();
	this->cwiypbadmlfnqivtn(3614, string("zlfjvyripgfeookwazukkcmcsvou"));
	this->hmpixezkpomhqdragcnmrnd(false, false, 11057, string("ppbgmtemoczcrhxmiypxqwasajlzsuxwhjefjsemqmglggfikoihouzkeosogdkshyxufstipfnxckoqbtatgqueufceam"), 1363, true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class gmhimob {
public:
	bool jyjbecuoxaji;
	bool csrpjjib;
	string lirbufldfcby;
	int yhzdborlhjb;
	gmhimob();
	string stdpxvxuldusrinqpll(double brsinsnan, int pqijvbcnf, string ytzzrobpqm, bool yalqjx, double hfisfpgmvwxgu, double ksrcuazqrpvd, int xtehb);
	string vmumnfmakegi(double djwpxfymfmaimt, double yyfza, string qcsznzeayk, double wfpgk, double kqmdfuing, bool sqdjcmtjkllgdw);
	double zgdwvcicbnppbujwswoxaaxf();
	string jigkllbdzbgivskycw(int pyqswbqzp, string ifxnh, double ckpue, string ygthxkxidyww, double vrnjlosajupj, double piomtrbzlbwwey, string nlofh);
	string fvdixndojvgfgjgjcyjzvazgk(double hhxgffnmdgiwr, double mgapbybyrkvaipe, bool nhjmmixquh, bool eqoodbsm);
	string olbwuethtpg(int grgnyiqggn);
	void jtefqeooqg(bool kadqauhyxqlsx, int dnvfykpmcydoz, int ydmpinceft, string vrosys, double xdhqpx, double eargobstsrww);
	double qyesbwjjthz(double irqpgvyllobu, int fmqdkabizih, int pzdrlnswxfaezzw, double wgfkhsslyivj, int cjrupmewigchmva, string jjbrsxku, bool apulvavegxaquk, bool suxwgxteyrn);

protected:
	int goqxsclfwmsahvq;

	void suujkyhvamtcoklyftithql(double ozlmletvo, double uaqfsjmvxbpwds);
	bool rkjanudttjirfamekqmm(int iugdrve, int sejkifcbyc, int dmczdgckeb, int hlofpuigpmkchvl, bool umhrbrfoadmdiyu, bool qkulrijskwvf, int ohylujju, string yjwboziniaznfo, string fsipx, bool cwfvqf);
	bool acyridrykalzhkhemubmziadt(int mmyftqwmgyc, string wjqfgxz, int oqhhfuo, int whlanvkiokb, bool hcoescltpdmjj, double kljkiwtsl, int wlpafgkfims);
	void oyamhrlprvtp(double anvgeblff, string gsrpwc, string iypivecwi, double qxyccwzo, string gpkbmo, double tiurnzghjn, string dgvkdgllpil, int ranmxmzwhprhyj);

private:
	string bgfpd;
	double yipwqmufpkrljig;

	string vabvujxggnjjig(int vyqpvyddncui, bool mtbrsvlswr, double hhyspkojwv, int iutvs);
	string fnxymuzrunrnrhjbfdcu(int dgxiwxedzxxme, bool xgmbgqwcjiutxak);
	double dzgepytyraevfavnppw(int edivlccho, double vbitkkaggq, bool lbizenwy);

};


string gmhimob::vabvujxggnjjig(int vyqpvyddncui, bool mtbrsvlswr, double hhyspkojwv, int iutvs) {
	double xlelogofvbt = 22885;
	int ebqxgapdsyo = 5157;
	string hizmjc = "zldjmqmpmaqnidtfvrmmjzwxaeidybapygndvddhjjlsycmztqkuhpoqakxbjydspkxfhtkkcemexiwinjfedrteedkcphrpg";
	bool evfgyospn = true;
	bool psqbgd = true;
	bool lmokwideo = false;
	if (5157 != 5157) {
		int hxdiie;
		for (hxdiie = 24; hxdiie > 0; hxdiie--) {
			continue;
		}
	}
	return string("h");
}

string gmhimob::fnxymuzrunrnrhjbfdcu(int dgxiwxedzxxme, bool xgmbgqwcjiutxak) {
	double puyvurvvsl = 20065;
	string wxgzhlodmk = "yvavsdnhctlzdaquhduqce";
	bool wnsxaltwxcry = false;
	if (false == false) {
		int rfsiktbq;
		for (rfsiktbq = 22; rfsiktbq > 0; rfsiktbq--) {
			continue;
		}
	}
	if (false == false) {
		int avbnpi;
		for (avbnpi = 33; avbnpi > 0; avbnpi--) {
			continue;
		}
	}
	return string("tfzdtniqfgzlgbf");
}

double gmhimob::dzgepytyraevfavnppw(int edivlccho, double vbitkkaggq, bool lbizenwy) {
	int nkkqx = 6586;
	bool utbieugpsqj = false;
	int cfrrpemqtpw = 7328;
	string mfamqtdrlja = "uxqvovjdijfprnfsskuymhkbxyudkbkdrxalkigzaudsuxghigngezvffdeotuyyzdlttwgdagitbobdoskrnd";
	if (7328 == 7328) {
		int lyjvgda;
		for (lyjvgda = 52; lyjvgda > 0; lyjvgda--) {
			continue;
		}
	}
	if (false != false) {
		int cagmieqo;
		for (cagmieqo = 71; cagmieqo > 0; cagmieqo--) {
			continue;
		}
	}
	if (string("uxqvovjdijfprnfsskuymhkbxyudkbkdrxalkigzaudsuxghigngezvffdeotuyyzdlttwgdagitbobdoskrnd") == string("uxqvovjdijfprnfsskuymhkbxyudkbkdrxalkigzaudsuxghigngezvffdeotuyyzdlttwgdagitbobdoskrnd")) {
		int wiyn;
		for (wiyn = 83; wiyn > 0; wiyn--) {
			continue;
		}
	}
	if (6586 != 6586) {
		int yuqnxms;
		for (yuqnxms = 87; yuqnxms > 0; yuqnxms--) {
			continue;
		}
	}
	return 12576;
}

void gmhimob::suujkyhvamtcoklyftithql(double ozlmletvo, double uaqfsjmvxbpwds) {
	int gyybwt = 3809;
	bool zpbtqdjdlxaon = true;
	bool idwylrtccwzcz = false;
	double sgvvsqfdif = 24861;
	int hbjkotxcdvwarnj = 1369;
	string ujupfqbgvmffahf = "sxozxtieohuotfmaayrkxgfqwjpavwmkhcaixvhlusedlfpvkhuetlxekpgtbvjalk";
	double ijjgnltj = 23617;
	double giwqulavni = 1312;
	bool pebbjvqutp = true;
	double dadqe = 30953;
	if (3809 != 3809) {
		int gunnt;
		for (gunnt = 53; gunnt > 0; gunnt--) {
			continue;
		}
	}
	if (24861 == 24861) {
		int dbyefm;
		for (dbyefm = 76; dbyefm > 0; dbyefm--) {
			continue;
		}
	}
	if (24861 == 24861) {
		int ir;
		for (ir = 73; ir > 0; ir--) {
			continue;
		}
	}
	if (30953 == 30953) {
		int opdf;
		for (opdf = 66; opdf > 0; opdf--) {
			continue;
		}
	}
	if (23617 == 23617) {
		int pqozd;
		for (pqozd = 48; pqozd > 0; pqozd--) {
			continue;
		}
	}

}

bool gmhimob::rkjanudttjirfamekqmm(int iugdrve, int sejkifcbyc, int dmczdgckeb, int hlofpuigpmkchvl, bool umhrbrfoadmdiyu, bool qkulrijskwvf, int ohylujju, string yjwboziniaznfo, string fsipx, bool cwfvqf) {
	double nauovilnjd = 29366;
	double plmicgmdd = 21195;
	string rprjw = "kokoljhmjotmglhblakbgffcpnowfhsd";
	bool aohyvldrpgoiigq = false;
	string dqcxbahwnv = "stiiedqkxwqsoqnzlihdsgxnfbmcxdixeywnlpnmmgtdktvgfnpiwampao";
	bool zacvfobtlrf = true;
	string emcxgag = "wfgomielzbolwdpzosxyibsvrxas";
	double ykbxib = 2341;
	double utlucrjblehdu = 10179;
	if (string("wfgomielzbolwdpzosxyibsvrxas") != string("wfgomielzbolwdpzosxyibsvrxas")) {
		int duswogfjgv;
		for (duswogfjgv = 41; duswogfjgv > 0; duswogfjgv--) {
			continue;
		}
	}
	if (29366 != 29366) {
		int fzvbzidn;
		for (fzvbzidn = 69; fzvbzidn > 0; fzvbzidn--) {
			continue;
		}
	}
	if (21195 == 21195) {
		int zsoxbubap;
		for (zsoxbubap = 21; zsoxbubap > 0; zsoxbubap--) {
			continue;
		}
	}
	if (false == false) {
		int zvrb;
		for (zvrb = 56; zvrb > 0; zvrb--) {
			continue;
		}
	}
	if (2341 != 2341) {
		int uzixtqat;
		for (uzixtqat = 79; uzixtqat > 0; uzixtqat--) {
			continue;
		}
	}
	return true;
}

bool gmhimob::acyridrykalzhkhemubmziadt(int mmyftqwmgyc, string wjqfgxz, int oqhhfuo, int whlanvkiokb, bool hcoescltpdmjj, double kljkiwtsl, int wlpafgkfims) {
	bool akxeh = true;
	string dqhczosecyj = "iseigjklwwvlsqdlh";
	double yyrphmcxw = 6093;
	string gcsob = "onomjyakplzabepppmjgzsktsjijuqymzikzobvvhvliqqpxdloyimzxvmvvjwcimb";
	double xqggw = 32970;
	string qcflejnooa = "wcjicnypyisayzckiuolfqcxqkoksfnlbwdirhefubdlhkvifrxirlknmnfjnlvrvugmpiotoqcevrzccyyntnrghouowuvof";
	if (32970 == 32970) {
		int gmsezws;
		for (gmsezws = 29; gmsezws > 0; gmsezws--) {
			continue;
		}
	}
	return true;
}

void gmhimob::oyamhrlprvtp(double anvgeblff, string gsrpwc, string iypivecwi, double qxyccwzo, string gpkbmo, double tiurnzghjn, string dgvkdgllpil, int ranmxmzwhprhyj) {

}

string gmhimob::stdpxvxuldusrinqpll(double brsinsnan, int pqijvbcnf, string ytzzrobpqm, bool yalqjx, double hfisfpgmvwxgu, double ksrcuazqrpvd, int xtehb) {
	int fjkbwuoaqzsbt = 5624;
	int rzevdd = 11;
	int bfaffdcbghaptx = 7935;
	return string("jsnitiqicfmdrumfyoj");
}

string gmhimob::vmumnfmakegi(double djwpxfymfmaimt, double yyfza, string qcsznzeayk, double wfpgk, double kqmdfuing, bool sqdjcmtjkllgdw) {
	double ilbxavm = 7550;
	bool dtueifr = true;
	int iuuwbqdbos = 653;
	int algtmfplw = 5686;
	if (true == true) {
		int oenc;
		for (oenc = 10; oenc > 0; oenc--) {
			continue;
		}
	}
	return string("nxkkdsmvfgch");
}

double gmhimob::zgdwvcicbnppbujwswoxaaxf() {
	string zlzdqsjgwsdkb = "azbueyxkmerocsvmoqnbzvjyiwnmqvhpjtvxtbd";
	return 18390;
}

string gmhimob::jigkllbdzbgivskycw(int pyqswbqzp, string ifxnh, double ckpue, string ygthxkxidyww, double vrnjlosajupj, double piomtrbzlbwwey, string nlofh) {
	bool mfdspzdvcuvbc = true;
	int akhlpc = 552;
	string ucagfyxd = "tftgbvgveyexrannachkqmmuwfszgjiogjpcsaorrbzqczpzpiwovunmspltvrfannzgyvtnjbascwxllidlhwkqzoazoo";
	double omhzuz = 15709;
	double mskkibffnkow = 18726;
	return string("welayupxpyxmqosjaba");
}

string gmhimob::fvdixndojvgfgjgjcyjzvazgk(double hhxgffnmdgiwr, double mgapbybyrkvaipe, bool nhjmmixquh, bool eqoodbsm) {
	string llvibdeqrg = "itekqammzthjdiyzykyrqhzqjxjyeipldhjpjlzxmvtwnnwybfrcwwsgbomjz";
	return string("rlandrlrrlq");
}

string gmhimob::olbwuethtpg(int grgnyiqggn) {
	string odsvdecnujwob = "aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo";
	if (string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo") == string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo")) {
		int uiag;
		for (uiag = 55; uiag > 0; uiag--) {
			continue;
		}
	}
	if (string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo") != string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo")) {
		int qmhuxmgxoa;
		for (qmhuxmgxoa = 32; qmhuxmgxoa > 0; qmhuxmgxoa--) {
			continue;
		}
	}
	if (string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo") == string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo")) {
		int vhtmhxysbo;
		for (vhtmhxysbo = 11; vhtmhxysbo > 0; vhtmhxysbo--) {
			continue;
		}
	}
	if (string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo") == string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo")) {
		int pbvqgczxpw;
		for (pbvqgczxpw = 23; pbvqgczxpw > 0; pbvqgczxpw--) {
			continue;
		}
	}
	if (string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo") == string("aecbvwxaozpkinyrzkvnlmtstfzmqddxvyzzbtmcouhsniokjfmkbiwwo")) {
		int ds;
		for (ds = 80; ds > 0; ds--) {
			continue;
		}
	}
	return string("veswqcasdzjoyaq");
}

void gmhimob::jtefqeooqg(bool kadqauhyxqlsx, int dnvfykpmcydoz, int ydmpinceft, string vrosys, double xdhqpx, double eargobstsrww) {
	double ageaheugrgnkv = 16097;
	double tqvkmnbazlrbbf = 8579;
	bool isigyzgtet = false;
	if (16097 == 16097) {
		int cvqzehhtqv;
		for (cvqzehhtqv = 34; cvqzehhtqv > 0; cvqzehhtqv--) {
			continue;
		}
	}
	if (16097 == 16097) {
		int cs;
		for (cs = 45; cs > 0; cs--) {
			continue;
		}
	}

}

double gmhimob::qyesbwjjthz(double irqpgvyllobu, int fmqdkabizih, int pzdrlnswxfaezzw, double wgfkhsslyivj, int cjrupmewigchmva, string jjbrsxku, bool apulvavegxaquk, bool suxwgxteyrn) {
	bool ikzjmiagoecfx = false;
	int dqdsl = 7085;
	double vfkjgojnxdl = 20833;
	bool zbhmqhbuoq = true;
	string hnhubovlkuw = "ckvpwsdog";
	int mobjiz = 327;
	int wgiviodtzuen = 3114;
	int jqmhcf = 1720;
	int chputxr = 5424;
	int aodqbmvnlmzbek = 4703;
	return 24715;
}

gmhimob::gmhimob() {
	this->stdpxvxuldusrinqpll(803, 5991, string("hejpaxguazrhsnojyvkofutolllgrpufrfaokusemwd"), true, 30192, 59221, 960);
	this->vmumnfmakegi(33070, 12810, string("tuhtfpykqwtantsxplftnboikiwlfwgotywxkzudaqc"), 19368, 10241, false);
	this->zgdwvcicbnppbujwswoxaaxf();
	this->jigkllbdzbgivskycw(4061, string("vktvnxemkoegnhcaocpiklckndgaqdoypqhhdyulriwduymlquimgmjpdhltiigspxv"), 16232, string("tatteshktvspujlyroqufkdywwfmmraentzbscafvmkokdvrecmyjfepbclecyeidunifswrz"), 12750, 46254, string("zalnuviryqvzvcsddlpvfduysoztwnferkvjqecrkwpgvdvveinppoyncolseybinkgbegftcbfia"));
	this->fvdixndojvgfgjgjcyjzvazgk(6772, 28281, true, true);
	this->olbwuethtpg(5072);
	this->jtefqeooqg(true, 2004, 6629, string("izorlcjmiedmsxpzghmrbomaacrlgvokgegpiqimhzbceteacxbijteifkispoapkyuiznrjpljtflzk"), 6286, 42035);
	this->qyesbwjjthz(21340, 2141, 7728, 64794, 3757, string("ofhzcfkylceqkkeradxqmkruvdrljmemdmjijkqgflwoameqn"), false, false);
	this->suujkyhvamtcoklyftithql(15436, 5566);
	this->rkjanudttjirfamekqmm(6041, 3627, 2613, 610, true, false, 898, string("nsgqilcndlnfomoyjthlomvpphmghkbpujpyiczgzwdpndhkdokwsrotwk"), string("boeieyoeiagtqhyblqjrwxh"), false);
	this->acyridrykalzhkhemubmziadt(5649, string("wxjlyjkwb"), 2115, 1864, true, 29589, 887);
	this->oyamhrlprvtp(76602, string("aehceazsosgootwxhwgwyfqnipjuquzkhqkzjfgkdkxfasitipiitfkubjzfwsgilgqhtxmkpupkltqztngpyneskjbnfcdc"), string("pddfzkhhihjwdwrbvzdmadzsaxrtkmesbjjvjgwwqctlxnqhi"), 27465, string("rmfeaeazytjhfebyjvxqfsgdspsaxfxnpqkxxdypqw"), 23678, string("qknfarrudnmbsgpjbcgbooueiqjendgvkwrnbvflzshjdscsvocoizrmhq"), 781);
	this->vabvujxggnjjig(292, false, 853, 728);
	this->fnxymuzrunrnrhjbfdcu(2017, false);
	this->dzgepytyraevfavnppw(3076, 14716, true);
}
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class nkbwsej {
public:
	string zmdfb;
	double lmzfibd;
	int lvnyyyeawq;
	int vhuudjuzeyfpudj;
	double qxxkerug;
	nkbwsej();
	void vtxawksjwjnmlcvnokbgy(bool rhpuwiznufn, int ziumodqlxntuwgl, bool amqpo, int orfpibqfbela, double ruhtmpknjpmo, bool cdkxlkdbb);
	double konewckvnkmmad();
	int qbtkctaortoigbhtoq(int jkftlqracc, int szxjijmimuim, string ujohllezaaewq, int hqljoynyvxj, double ywiqfgvtyqy, bool upifd, double fezdmtjyuith, string mgsonv);
	string larzjozamkyikkskueaxlgfgs(int rjbpefyaeatdh, string ygurejazinp, int brxlzymt, double uynrddqox, int cbjqdxlmyzkt);
	int tdsdnbmzyhkgv(int pvmliood, string ojctv, bool lqortolwg, int lxdzjslhlgxw, string fipvnhhhmsjwbh, double zbbfblzgn, string ppyfsj, string gjjfsgbicceo, string xeuqwxflgmaar);
	string urrubiyfgrbii(double eirfsidjvaox, int twqriroknaaup, string iuimt);
	string jlbbenzwfj(int vhixjpvtsxnu, string mtkfi, string ffknjsv, string bkoxcpaq, bool wjvmgw, string uhgmbwzfcv, bool kyyuegsldsixc, string lrpigbbhplluy, string spdiaikdtdkvnrk);

protected:
	string zaxqzhchnjuff;
	int hmuyumabkyx;
	int oahixxetpi;
	int elsqflt;

	double hdbpazieoqzht(string htfbgdvofa, double ejdlykvzwdqeb, bool ynppyx, string vnunwzwqm, double xzlzafgw, bool xkptctftkifckxc);
	bool xfcveiiiiheumvp(int kbgqfy);
	bool dzstawtniweozrdfjchdwsyp(double bvyzj, int qzbkyhpbncms, int gvpxkvalywksgin, string ibcqyaisesn, string oxwmzhrwc, string otlgwrai);

private:
	double gbzkdiyf;
	bool nmfvq;
	bool vyiddjepw;

	bool hzcxarhsynugzggt(bool ypvwoepj);
	string qnmhzfqlyumg(int tpxyy, bool gkolvzfbpzvism, double nwejxcdiejko, bool ezufyz, bool zsnlftj, double ktchavlxghyf);
	bool tmvjicdtiylcazfqeor(bool bcqpozfimn, bool wccfblfec, double dzkuezvbpizxci, double pvcwecl, double ectzarmaqgbx, int fbjduzizfdzusax, string fspyhs, int rlieht);
	bool kyohjxswsx(bool lsdngh, double xttoeanfqv);

};


bool nkbwsej::hzcxarhsynugzggt(bool ypvwoepj) {
	int aeppntpmkyq = 7465;
	double qsslzafdgiiizao = 44928;
	bool cbspuzqjxts = false;
	int tzsdhyrxuqlscr = 6133;
	bool stzjqlm = false;
	if (false != false) {
		int kefrodok;
		for (kefrodok = 40; kefrodok > 0; kefrodok--) {
			continue;
		}
	}
	return false;
}

string nkbwsej::qnmhzfqlyumg(int tpxyy, bool gkolvzfbpzvism, double nwejxcdiejko, bool ezufyz, bool zsnlftj, double ktchavlxghyf) {
	string bujfvgango = "gianbcpsbkviraxoukdttaxwfhcgarwjwsgwezmwvocljvrvdwaiizikdbzfohndofpgejf";
	int hwmyjrrcls = 621;
	double jeorwhnm = 4590;
	double xmqrhsamuxo = 55604;
	if (4590 != 4590) {
		int vmw;
		for (vmw = 53; vmw > 0; vmw--) {
			continue;
		}
	}
	if (55604 == 55604) {
		int ouydcgfsoa;
		for (ouydcgfsoa = 22; ouydcgfsoa > 0; ouydcgfsoa--) {
			continue;
		}
	}
	if (621 != 621) {
		int hohpa;
		for (hohpa = 84; hohpa > 0; hohpa--) {
			continue;
		}
	}
	if (string("gianbcpsbkviraxoukdttaxwfhcgarwjwsgwezmwvocljvrvdwaiizikdbzfohndofpgejf") != string("gianbcpsbkviraxoukdttaxwfhcgarwjwsgwezmwvocljvrvdwaiizikdbzfohndofpgejf")) {
		int oqsytanuzh;
		for (oqsytanuzh = 55; oqsytanuzh > 0; oqsytanuzh--) {
			continue;
		}
	}
	if (4590 == 4590) {
		int ce;
		for (ce = 51; ce > 0; ce--) {
			continue;
		}
	}
	return string("j");
}

bool nkbwsej::tmvjicdtiylcazfqeor(bool bcqpozfimn, bool wccfblfec, double dzkuezvbpizxci, double pvcwecl, double ectzarmaqgbx, int fbjduzizfdzusax, string fspyhs, int rlieht) {
	int hcvkjdhwqjy = 637;
	double cuccoznbgjvgmp = 22744;
	bool fjomiigzkuo = true;
	string pynxhgdcjgy = "cuwvhlzftidkfaluvfrikucrkammquuofpswplcrxoqgypjlpsklvibdbxpwnybhmloumhojllw";
	bool tqnumgyfnt = true;
	if (string("cuwvhlzftidkfaluvfrikucrkammquuofpswplcrxoqgypjlpsklvibdbxpwnybhmloumhojllw") == string("cuwvhlzftidkfaluvfrikucrkammquuofpswplcrxoqgypjlpsklvibdbxpwnybhmloumhojllw")) {
		int kcohgrnj;
		for (kcohgrnj = 86; kcohgrnj > 0; kcohgrnj--) {
			continue;
		}
	}
	if (22744 != 22744) {
		int gjzojjeba;
		for (gjzojjeba = 78; gjzojjeba > 0; gjzojjeba--) {
			continue;
		}
	}
	return true;
}

bool nkbwsej::kyohjxswsx(bool lsdngh, double xttoeanfqv) {
	int nkrgsrp = 396;
	double bhtbgc = 63742;
	double aujcwwi = 7176;
	string dznaehvepomwxfy = "cesqaisadhzcbmixchbbo";
	string ccxznfbmszjijt = "xqcbnsyvqwtraqzetixgsyskkpyqerevmhxbsedbyskzcbospkwfsyzcrahju";
	int ocnjxpcnwoydw = 5968;
	string rwullxilll = "ypkmalbhhox";
	bool ayzbu = false;
	string yfhnjwlp = "cljebxcwedjvhzouzghxswwsmgtqvvmjbskcjg";
	if (string("cesqaisadhzcbmixchbbo") == string("cesqaisadhzcbmixchbbo")) {
		int paroc;
		for (paroc = 8; paroc > 0; paroc--) {
			continue;
		}
	}
	if (string("ypkmalbhhox") == string("ypkmalbhhox")) {
		int kshqyq;
		for (kshqyq = 18; kshqyq > 0; kshqyq--) {
			continue;
		}
	}
	if (63742 != 63742) {
		int hpsifjqzpa;
		for (hpsifjqzpa = 62; hpsifjqzpa > 0; hpsifjqzpa--) {
			continue;
		}
	}
	return true;
}

double nkbwsej::hdbpazieoqzht(string htfbgdvofa, double ejdlykvzwdqeb, bool ynppyx, string vnunwzwqm, double xzlzafgw, bool xkptctftkifckxc) {
	string oboxwihvcrxngak = "zsunr";
	double vsazfw = 35581;
	int ahxsrniej = 5161;
	bool mbide = false;
	string aewreqxaolqdii = "mmuttbsyvgzcvqldqvs";
	int mgapctjs = 1432;
	bool lnflscgugpkeoqi = true;
	double ohsmh = 18855;
	double opgflb = 28807;
	double wnyrztxwppw = 33470;
	if (string("mmuttbsyvgzcvqldqvs") == string("mmuttbsyvgzcvqldqvs")) {
		int oqmgnroqjk;
		for (oqmgnroqjk = 60; oqmgnroqjk > 0; oqmgnroqjk--) {
			continue;
		}
	}
	if (string("zsunr") != string("zsunr")) {
		int zwqqqiezh;
		for (zwqqqiezh = 100; zwqqqiezh > 0; zwqqqiezh--) {
			continue;
		}
	}
	return 6200;
}

bool nkbwsej::xfcveiiiiheumvp(int kbgqfy) {
	string vshbvpbnjihnco = "ivcktg";
	double zrqclatvc = 2541;
	bool yswzjqmbxlkts = false;
	bool nbtjjfjchc = false;
	if (false != false) {
		int rqzwp;
		for (rqzwp = 75; rqzwp > 0; rqzwp--) {
			continue;
		}
	}
	return false;
}

bool nkbwsej::dzstawtniweozrdfjchdwsyp(double bvyzj, int qzbkyhpbncms, int gvpxkvalywksgin, string ibcqyaisesn, string oxwmzhrwc, string otlgwrai) {
	string sncfcy = "phdbbntnldhkqkk";
	bool bbckjtgxask = false;
	string yjcvfdan = "qqyfcckejowltaibkrrpieyxhujoitvczrxpzusyjyfourqhljimwvfzxn";
	bool zhnlrxlcmsz = false;
	double ycttmufjwwdbrg = 41946;
	string rpqsufgwguajjx = "omtdnfjctcagcuejcewzewefefwvmtkaywtoycgcwqkdeiygnetmytxggqahcettsvd";
	double kmbhobhxbkjf = 69243;
	int qahuxqtvxdw = 7588;
	bool oqksefvt = true;
	if (string("qqyfcckejowltaibkrrpieyxhujoitvczrxpzusyjyfourqhljimwvfzxn") == string("qqyfcckejowltaibkrrpieyxhujoitvczrxpzusyjyfourqhljimwvfzxn")) {
		int lemmygl;
		for (lemmygl = 14; lemmygl > 0; lemmygl--) {
			continue;
		}
	}
	if (false == false) {
		int jb;
		for (jb = 79; jb > 0; jb--) {
			continue;
		}
	}
	if (7588 == 7588) {
		int alwb;
		for (alwb = 30; alwb > 0; alwb--) {
			continue;
		}
	}
	if (true != true) {
		int ttjvpct;
		for (ttjvpct = 72; ttjvpct > 0; ttjvpct--) {
			continue;
		}
	}
	if (false != false) {
		int nceomk;
		for (nceomk = 57; nceomk > 0; nceomk--) {
			continue;
		}
	}
	return true;
}

void nkbwsej::vtxawksjwjnmlcvnokbgy(bool rhpuwiznufn, int ziumodqlxntuwgl, bool amqpo, int orfpibqfbela, double ruhtmpknjpmo, bool cdkxlkdbb) {
	bool ikrjj = false;
	int pycchxunjiqnhqu = 2132;
	double xetcsto = 14970;
	int xuziv = 3861;
	if (false != false) {
		int afm;
		for (afm = 70; afm > 0; afm--) {
			continue;
		}
	}
	if (false != false) {
		int iqh;
		for (iqh = 31; iqh > 0; iqh--) {
			continue;
		}
	}
	if (3861 != 3861) {
		int oeovnv;
		for (oeovnv = 19; oeovnv > 0; oeovnv--) {
			continue;
		}
	}
	if (false == false) {
		int mitngrnmtl;
		for (mitngrnmtl = 33; mitngrnmtl > 0; mitngrnmtl--) {
			continue;
		}
	}

}

double nkbwsej::konewckvnkmmad() {
	int kcyvkio = 2000;
	bool isuelgowzcne = false;
	double qalxtnnhpdi = 43464;
	string qjvhksmndwev = "mvrkligwshwzsztgzpovhyamwxmmddrhusqccvebbxivvptpwgqdvg";
	double tnerqlayati = 14100;
	double ybczihlmfvmd = 2927;
	double dpdsxmv = 60354;
	bool wwacpcinxogg = false;
	if (string("mvrkligwshwzsztgzpovhyamwxmmddrhusqccvebbxivvptpwgqdvg") == string("mvrkligwshwzsztgzpovhyamwxmmddrhusqccvebbxivvptpwgqdvg")) {
		int ddbxkwrc;
		for (ddbxkwrc = 14; ddbxkwrc > 0; ddbxkwrc--) {
			continue;
		}
	}
	if (2000 == 2000) {
		int pkjtnu;
		for (pkjtnu = 47; pkjtnu > 0; pkjtnu--) {
			continue;
		}
	}
	return 74421;
}

int nkbwsej::qbtkctaortoigbhtoq(int jkftlqracc, int szxjijmimuim, string ujohllezaaewq, int hqljoynyvxj, double ywiqfgvtyqy, bool upifd, double fezdmtjyuith, string mgsonv) {
	bool vghrh = false;
	bool jxeqtkqydyrrmet = true;
	bool aucsyv = true;
	double cxfahqhw = 27737;
	string cscaprfeo = "mkqscijqvavzalx";
	bool hemebfld = true;
	if (false != false) {
		int qai;
		for (qai = 41; qai > 0; qai--) {
			continue;
		}
	}
	if (false != false) {
		int ikey;
		for (ikey = 13; ikey > 0; ikey--) {
			continue;
		}
	}
	if (true == true) {
		int loeek;
		for (loeek = 39; loeek > 0; loeek--) {
			continue;
		}
	}
	if (true != true) {
		int zek;
		for (zek = 72; zek > 0; zek--) {
			continue;
		}
	}
	return 20891;
}

string nkbwsej::larzjozamkyikkskueaxlgfgs(int rjbpefyaeatdh, string ygurejazinp, int brxlzymt, double uynrddqox, int cbjqdxlmyzkt) {
	bool skuukurlojlg = true;
	if (true == true) {
		int nhuenpvp;
		for (nhuenpvp = 88; nhuenpvp > 0; nhuenpvp--) {
			continue;
		}
	}
	if (true == true) {
		int lkkqkgvk;
		for (lkkqkgvk = 83; lkkqkgvk > 0; lkkqkgvk--) {
			continue;
		}
	}
	return string("n");
}

int nkbwsej::tdsdnbmzyhkgv(int pvmliood, string ojctv, bool lqortolwg, int lxdzjslhlgxw, string fipvnhhhmsjwbh, double zbbfblzgn, string ppyfsj, string gjjfsgbicceo, string xeuqwxflgmaar) {
	bool jqfvgjfkzwt = true;
	string cpivlnzvn = "idbsfgmuahuzgchrtkalkvpqktkxdlbfpwdltqqlmpzfwudbjblkueudzgjmgtxqqmatbecddnxuiiagxv";
	double kvchtn = 9127;
	double autvecexhx = 9816;
	string fdvyhfl = "fmemvhxguaftducosisupgxpdgumoguscmjaqocqw";
	string yflesvhfrpjpdr = "ccpmgwdeivjuntmugavucdicmwpkivgfyozylswrattafgvouzsonjexyl";
	return 76265;
}

string nkbwsej::urrubiyfgrbii(double eirfsidjvaox, int twqriroknaaup, string iuimt) {
	int seoyzhqiip = 1025;
	int qcmdisrsucppj = 1343;
	int rixek = 1625;
	bool ykxrifghq = false;
	if (1625 == 1625) {
		int tijbu;
		for (tijbu = 94; tijbu > 0; tijbu--) {
			continue;
		}
	}
	if (1025 != 1025) {
		int vnbeqzweab;
		for (vnbeqzweab = 79; vnbeqzweab > 0; vnbeqzweab--) {
			continue;
		}
	}
	if (1025 == 1025) {
		int wcjzizj;
		for (wcjzizj = 87; wcjzizj > 0; wcjzizj--) {
			continue;
		}
	}
	if (1025 == 1025) {
		int grylnaq;
		for (grylnaq = 22; grylnaq > 0; grylnaq--) {
			continue;
		}
	}
	return string("yjmoqpaprgobipfuuw");
}

string nkbwsej::jlbbenzwfj(int vhixjpvtsxnu, string mtkfi, string ffknjsv, string bkoxcpaq, bool wjvmgw, string uhgmbwzfcv, bool kyyuegsldsixc, string lrpigbbhplluy, string spdiaikdtdkvnrk) {
	string tvqfhqfoi = "wlmhyrwmfxwdukneqmfsbssiaqopdqncro";
	int ddjyvtgqyq = 3586;
	string pzuzmzufxfkzpw = "pweufhnzdunvyjutrgmnempnrulvoabncklbeamgxqipdus";
	int yexdrhsktmos = 7101;
	int nvurwqp = 634;
	string jqaxy = "";
	int lwdbu = 9416;
	int izxmrcrbpsgfq = 1229;
	string wjfebdgrpcfabl = "pljtxkmhrnd";
	return string("hfykybivyvxgindtnnyx");
}

nkbwsej::nkbwsej() {
	this->vtxawksjwjnmlcvnokbgy(true, 1187, true, 2357, 27599, false);
	this->konewckvnkmmad();
	this->qbtkctaortoigbhtoq(2319, 115, string("yrxotjprolfxzluwjpbyusloixwnieovypgabxmjbauqhdwbqbibqydwuhwpsbiqz"), 909, 13726, false, 86331, string("fbduovtkvpbzclhqkjspgoornjdnzkmqdffaexvvddopaszgswijtvzaycawqueyyjmo"));
	this->larzjozamkyikkskueaxlgfgs(107, string("nzvlhxfubmgzlizirzsifqdbedxuctnrlqwevyfopvqm"), 6334, 57641, 3686);
	this->tdsdnbmzyhkgv(2838, string("olavyrbmzcvlqvsadthphzjeshxgxvnjalwaskngymjx"), false, 6501, string("sxyhpbszafqztavpftypgehizunc"), 22917, string("xbttosnuajytmwcmbbdpvkxceegxaafckyuvmhfjjovkqyqwomkpnklxqsc"), string("swxzaisrptcaomhfkgny"), string("wybmydazchvwixigimsleftmzzajfoaasalwzaliv"));
	this->urrubiyfgrbii(13048, 3766, string("uncobunbqsyijpyjhhcdpponckoosifgihsimslmkegzbjlskv"));
	this->jlbbenzwfj(7451, string("qksmnuffbfkmsjbobarbraicgziqfivtcdzjwqwrfsnc"), string("hxhcpflzjhgszhhongkzohbhxdlbpjddpvpqyuhqpoverskrsot"), string("wxzhymxhamyvatspvruanvehlcz"), true, string("ipmqblxhcpte"), false, string("akzehkmsdiensgyqnfrtubjclxnjavnurzszgjpoqhdfktgejnzvdibwavkhrbvmdfuvynzcwfpx"), string("pmzmryfiivywqgxbqpfjnpddpxoqspurdwerwdagbgbeuvuhmikoogcmxhtigvjbldoiwubbpvwxzszctseib"));
	this->hdbpazieoqzht(string("hgsgzqkfqlojdrcpuphucmwcoj"), 1144, false, string("vtijsvfclcnsutmrwtmfiecsneaswwlexxlnkhwaqxpxfegwesvaeexkevksvnurcgcgpvhsynufiftbmyndarlgfaxns"), 9799, false);
	this->xfcveiiiiheumvp(2333);
	this->dzstawtniweozrdfjchdwsyp(17481, 530, 482, string("bzthqrgxmvuwepnompzioiqrfjjqplhujou"), string("hdnbmtcufswjnzxiywgujvsvtykijcmhtvrzcjdumipotgjthgrhmfvwflwzakjt"), string("oqygybzronfqaxrwhxicsubskothldavvy"));
	this->hzcxarhsynugzggt(false);
	this->qnmhzfqlyumg(4644, true, 13566, true, false, 3406);
	this->tmvjicdtiylcazfqeor(true, true, 23349, 81943, 2430, 5539, string("evcmzpmhdhvlmqnjijhmsonsywvdjnsvuizkhlmlkevirrbhkvhpvwhtbxpoe"), 1926);
	this->kyohjxswsx(true, 27970);
}
