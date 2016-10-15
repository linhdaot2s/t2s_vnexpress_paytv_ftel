#ifndef __CVNEPlaybackView_h__
#define __CVNEPlaybackView_h__

#include "CVNEApp.h"
class CVNEApp;

class CVNEPlaybackView
{
public:
	CVNEPlaybackView();
	~CVNEPlaybackView();

	void OnInit();
	void FlipAll();
	void LoadStartup();
	void ShowPlayBar(bool bIsShow);

	CFBGlobal *pCFBGlobal;

	IDirectFBWindow		*m_wMediaPlayer;
	IDirectFBSurface	*m_sfMediaPlayer;
};

#endif // !__CVNEPlaybackView_h__