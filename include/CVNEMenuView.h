#ifndef __CVNEMenuView_h__
#define __CVNEMenuView_h__

#include "CVNEApp.h"

class CVNEMenuView
{
public:
	CVNEMenuView();
	~CVNEMenuView();

	void OnLoad();
	void OnInit();
	void FlipAll();
	void LoadStartup();
	void DrawTextMenuPage();
	void ProcessKeyDown();
	void LoadPageItemMenuLv1();
	void DrawItemMenu(int iNumItem);
	void ShowUpOrDownIcon(int iType);
	void FocusMenuLv1(int iDirection);
	void FocusMenuLv2(int iDirection);
	void FocusMenuLv3(int iDirection);
	void DrawMenuFocus(int iTypeMenu, int iDirection);

	ListMenu *pListMenu;
	CFBGlobal *pCFBGlobal;

	IDirectFBWindow		*m_wMainWindow;
	IDirectFBSurface	*m_sfMainWindow;

	IDirectFBWindow		*m_wMenu;
	IDirectFBSurface	*m_sfMenu;

	IDirectFBWindow		*m_wMenuFocus;
	IDirectFBSurface	*m_sfMenuFocus;

	IDirectFBFont		*pSize18;
	IDirectFBFont		*pSize20;
	IDirectFBFont		*pSize25;

	int					iPosMenu;
	int					iPosMenuPage;
	int					iPosMenuLevel;
	bool				bIsTurnOff;
	bool				bIsListView;
};

#endif // !__CVNEMenuView_h__