#ifndef __CVNEListView_h__
#define __CVNEListView_h__

#include "CVNEApp.h"

class CVNEListView
{
public:
	CVNEListView();
	~CVNEListView();

	void OnLoad(string strCateID);
	void OnInit();
	void FlipAll();
	void LoadStartup();
	void DrawFocusInfo();
	void DrawTextInfoPage();
	void CancelThreadPicture();
	void FillRectPic(int iNumPic);
	void ShowUpOrDownIcon(int iType);
	static void* createPthreadShowItemsChangePage(void *vshowItemsChangePage);

	void ProcessKeyDown();

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
	bool				bIsBreak;
};

#endif // !__CVNEListView_h__