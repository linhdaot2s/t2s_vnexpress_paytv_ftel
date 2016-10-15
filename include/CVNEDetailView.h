#ifndef __CVNEDetailView_h__
#define __CVNEDetailView_h__

#include "CVNEApp.h"

class CVNEDetailView
{
public:
	CVNEDetailView();
	~CVNEDetailView();

	void OnLoad(string iCateID);
	void OnInit();
	void FlipAll();
	void LoadStartup();
	void DrawTextInfoPage();
	void FillRectPic(int iNumPic);
	void ShowUpOrDownIcon(int iType);
	static void* createPthreadShowItemsChangePage(void *vshowItemsChangePage);

	pthread_t pLoadPic;
	IDirectFBFont		*pSize18;
	IDirectFBFont		*pSize20;
	IDirectFBFont		*pSize25;

	ListItem *pListItem;
	CFBGlobal *pCFBGlobal;

	IDirectFBWindow		*m_wMainView;
	IDirectFBSurface	*m_sfMainView;
	IDirectFBWindow		*m_wMainFocus;
	IDirectFBSurface	*m_sfMainFocus;

	int					iPosInfo;
	int					iPosInfoPage;
};

#endif // !__CVNEDetailView_h__