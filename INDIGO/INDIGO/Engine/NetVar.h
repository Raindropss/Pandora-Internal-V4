#pragma once

#include "Engine.h"

struct netvar_info_s
{
#ifdef DUMP_NETVARS_TO_FILE
	char szTableName[128];
	char szPropName[128];
#endif
	DWORD_PTR dwCRC32;
	DWORD_PTR dwOffset;
};

namespace Engine
{
	class NetVarManager
	{
	public:
		DWORD_PTR GetNetVar(DWORD_PTR dwCRC32);
		//[swap_lines]
		bool Init( ClientClass* pClientClass );

		DWORD GetOffset( const char* tableName , const char* propName );
		bool HookProp( const char* tableName , const char* propName , RecvVarProxyFn function );
//[/swap_lines]
	private:
//[swap_lines]
		DWORD dwGetProp( const char* tableName , const char* propName , RecvProp** prop = 0 );
		DWORD dwGetProp( RecvTable* recvTable , const char* propName , RecvProp** prop = 0 );
//[/swap_lines]
		RecvTable* GetTable( const char* tableName );
		vector<RecvTable*> m_tables;
	private:
		std::vector<netvar_info_s>vars;
	};

	extern NetVarManager g_NetVar;
}