#ifndef __CVNEMenuView_h__
#define __CVNEMenuView_h__

#include "CVNEApp.h"

class CVNEApp;

class CVNEMenuView
{
public:
	CVNEMenuView();
	~CVNEMenuView();

	void OnInit();
	void FlipAll();
	void LoadStartup();
	void DrawTextMenuPage();
	void DrawItemMenu(int iNumItem);
	void ShowUpOrDownIcon(int iType);
	void DrawMenuFocus(int iTypeMenu, int iDirection);
	void FocusMenuLv1(int iDirection);
	void FocusMenuLv2(int iDirection);
	void FocusMenuLv3(int iDirection);
	void ProcessKeyDown();

	IDirectFBWindow		*m_wMainWindow;
	IDirectFBSurface	*m_sfMainWindow;

	IDirectFBWindow		*m_wMenu;
	IDirectFBSurface	*m_sfMenu;

	IDirectFBWindow		*m_wMenuFocus;
	IDirectFBSurface	*m_sfMenuFocus;

	int					iPosMenu;
	int					iPosMenuPage;
	bool				bIsParentMenu;
	bool				bIsTurnOff;
};

#endif // !__CVNEMenuView_h__