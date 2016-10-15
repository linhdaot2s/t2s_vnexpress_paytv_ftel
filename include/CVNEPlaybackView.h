#ifndef __CVNEPlaybackView_h__
#define __CVNEPlaybackView_h__

#include <FBGlobal.h>
#include "CVNEApp.h"
class CVNEApp;

class CVNEPlaybackView
{
public:
	CVNEPlaybackView();
	~CVNEPlaybackView();
	CFBGlobal *pGlobal;
	void OnInit();
	void FlipAll();
	void LoadStartup();
	void ShowPlayBar(bool bIsShow);
	void OnLoad();
	void ProcessKeyDown();
	void drawImageWithSurface(IDirectFBSurface *fb_sfPlayback,const char* cImage, int iX, int iY, int iW, int iH);
	void drawText(IDirectFBSurface *fb_sfPlayback, const char* cText, DFBColor fb_clText, IDirectFBFont* fb_fText, int iX, int iY, DFBSurfaceTextFlags fb_sfTFlag);
	void drawTextItems(const char *pText, int iSize, int iX, int iY, IDirectFBSurface* fb_sfText, IDirectFBFont* fb_fText, DFBColor fb_clText, int iRow);
	bool bIsTurnOff;

	CFBGlobal *pCFBGlobal;

	IDirectFBWindow		*m_wMediaPlayer;
	IDirectFBSurface	*m_sfMediaPlayer;
	IDirectFBWindow		*m_wMediaPlayerData;
	IDirectFBSurface	*m_sfMediaPlayerData;
	IDirectFBFont *m_fText20;
	IDirectFBFont *m_fText18;
};

#endif // !__CVNEPlaybackView_h__
