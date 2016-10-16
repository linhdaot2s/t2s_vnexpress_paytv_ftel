#ifndef __CVNEPlaybackView_h__
#define __CVNEPlaybackView_h__

#include <FBGlobal.h>
#include "CVNEApp.h"
#include "ParseHTML.h"
class CVNEApp;

#define SIZE_LIST 10

class CVNEPlaybackView
{
private:
	IDirectFBWindow		*m_wMediaPlayer;
	IDirectFBSurface	*m_sfMediaPlayer;
	IDirectFBWindow		*m_wMediaPlayerData;
	IDirectFBSurface	*m_sfMediaPlayerData;
	IDirectFBFont *m_fText20;
	IDirectFBFont *m_fText18;
	DFBColor m_fb_clText;
	DFBColor m_fb_clTextFocus;
	DetailItem *m_detailItem;
	ParseHTML *m_pParseHTML;
	int m_iFocus;
	int m_iOldFocus;
	bool bIsTurnOff;
	string LinkPlay;
	pthread_t m_PthreadPlay;
public:
	CVNEPlaybackView();
	~CVNEPlaybackView();
	CFBGlobal *pGlobal;
	void OnInit();
	void FlipAll();
	void LoadStartup();
	void showFocus(int iIndex, int iOldIndex);
	void ShowPlayBar(bool bIsShow);
	void OnLoad();
	void ProcessKeyDown();
	void executePressEnter();
	void drawImageWithSurface(IDirectFBSurface *fb_sfPlayback,const char* cImage, int iX, int iY, int iW, int iH);
	void drawText(IDirectFBSurface *fb_sfPlayback, const char* cText, DFBColor fb_clText, IDirectFBFont* fb_fText, int iX, int iY, DFBSurfaceTextFlags fb_sfTFlag);
	void drawTextItems(const char *pText, int iSize, int iX, int iY, IDirectFBSurface* fb_sfText, IDirectFBFont* fb_fText, DFBColor fb_clText, int iRow);
	void 					*createPthreadPlay();
	static void 			*callCreatePthreadPlay(void* play);
	void stopPthreadAndPlay();
};

#endif // !__CVNEPlaybackView_h__
