#pragma once

#include "../../Engine/Engine.h"
#include "../../SDK/Spoofed.h"

class CMisc
{
public:
//[swap_lines]
	void OnRender();
	void Junkcode();
	void OnCreateMove( CUserCmd* pCmd );
	void Junkcode2();
	void FrameStageNotify(ClientFrameStage_t Stage);
#define POSTPROCESS_VALUE
	void OnDrawModelExecute();
	void Junkcode3();
	void OnPlaySound( const char* pszSoundName );

	void OnOverrideView( CViewSetup* pSetup );
	void OnGetViewModelFOV( float& fov );

	void Junkcode4();

	vector<int> GetObservervators( int playerId );
	void Junkcode5();
	void OnRenderSpectatorList();
//[/swap_lines]
};