#ifndef __CVNEDetailView_h__
#define __CVNEDetailView_h__

#include "CVNEApp.h"
#include "ParseHTML.h"

class CVNEDetailView
{
public:
	CVNEDetailView();
	~CVNEDetailView();

	void OnInit();
	void LoadStartup();
	void DrawFocusText();
	bool ProcessKeyDown();
	void ProcessHTMLDetail();
	bool OnLoad(string strArticleID);
	void ShowUpOrDownIcon(int iType);

	IDirectFBFont		*pSize18;
	IDirectFBFont		*pSize20;
	IDirectFBFont		*pSize25;

	ParseHTML *pParseHTML;
	DetailItem *pDetailItem;
	CFBGlobal *pCFBGlobal;

	IDirectFBWindow		*m_wMainView;
	IDirectFBSurface	*m_sfMainView;

//	IDirectFBWindow		*wSpeakIcon;
//	IDirectFBSurface	*sfSpeakIcon;

	IDirectFBSurface	*m_sfEditedText;
	IDirectFBSurface	*m_sfSubEditedText;

	int iWidthPageCurrent;
	int iWidthPageTotal;
	bool bIsBreak;
	bool bListView;
};

#endif // !__CVNEDetailView_h__
