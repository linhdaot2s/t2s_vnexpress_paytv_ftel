#include "CVNEMenuView.h"

CVNEMenuView::CVNEMenuView()
{
	cout << "			CVNEMenuView::CVNEMenuView ==========================> Constructor !" << endl;
	m_wMainWindow = NULL;
	m_sfMainWindow = NULL;
	m_wMenu = NULL;
	m_sfMenu = NULL;
	m_wMenuFocus = NULL;
	m_sfMenuFocus = NULL;
	iPosMenu = 0;
	iPosMenuPage = 0;
	bIsParentMenu = true;
	bIsTurnOff = false;
	this->OnInit();
	this->LoadStartup();
	cout << "			CVNEMenuView::CVNEMenuView ==========================> Constructor SUCCESSFULL !" << endl;
}


CVNEMenuView::~CVNEMenuView()
{
	cout << "			CVNEMenuView::~CVNEMenuView ==========================> Destructor !" << endl;
	if (m_wMainWindow != NULL) {
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMainWindow !" << endl;
		
		CFBGlobal::m_pGlobal->FBWindowDestroy(m_wMainWindow, m_sfMainWindow);
		m_wMainWindow = NULL; m_sfMainWindow = NULL;
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMainWindow  SUCCESSFULL !" << endl;
	}
	if (m_wMenu != NULL) {
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMenu !" << endl;
		CFBGlobal::m_pGlobal->FBWindowDestroy(m_wMenu, m_sfMenu);
		m_wMenu = NULL; m_sfMenu = NULL;
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMenu  SUCCESSFULL !" << endl;
	}
	if (m_wMenuFocus != NULL) {
		cout << "			CVNEList::~CVNEList ---> Destroy m_wMenuFocus !" << endl;
		CFBGlobal::m_pGlobal->FBWindowDestroy(m_wMenuFocus, m_sfMenuFocus);
		m_wMenuFocus = NULL; m_sfMenuFocus = NULL;
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMenuFocus  SUCCESSFULL !" << endl;
	}
	cout << "			CVNEMenuView::~CVNEMenuView ==========================> Destructor SUCCESSFULL !" << endl;
}

void CVNEMenuView::OnInit()
{
	cout << "			CVNEMenuView::OnInit ==========================> OnInit !" << endl;
	if (m_wMainWindow == NULL && m_sfMainWindow == NULL)
		CFBGlobal::m_pGlobal->FBWindowCreateWithAlphaChannel(&m_wMainWindow, NULL, &m_sfMainWindow, 0, 0, Max_width, Max_height, 0xff);
	if (m_wMenu == NULL && m_sfMenu == NULL)
		CFBGlobal::m_pGlobal->FBWindowCreateWithAlphaChannel(&m_wMenu, NULL, &m_sfMenu, menu_x, menu_y, menu_width, menu_height, 0xff);
	if (m_wMenuFocus == NULL && m_sfMenuFocus == NULL)
		CFBGlobal::m_pGlobal->FBWindowCreateWithAlphaChannel(&m_wMenuFocus, NULL, &m_sfMenuFocus, MenuLevel1def[0].x, MenuLevel1def[0].y, MenuLevel1def[0].w, MenuLevel1def[0].h, 0xff);
	cout << "			CVNEMenuView::OnInit ==========================> OnInit SUCCESSFULL !" << endl;
}

void CVNEMenuView::FlipAll()
{
	cout << "			CVNEMenuView::FlipAll ==========================> FlipAll !" << endl;
	m_sfMainWindow->Flip(m_sfMainWindow, NULL, DSFLIP_WAITFORSYNC);
	m_sfMenu->Flip(m_sfMenu, NULL, DSFLIP_WAITFORSYNC);
	m_sfMenuFocus->Flip(m_sfMenuFocus, NULL, DSFLIP_WAITFORSYNC);
	cout << "			CVNEMenuView::FlipAll ==========================> FlipAll SUCCESSFULL !" << endl;
}

void CVNEMenuView::DrawTextMenuPage()
{
	cout << "			CVNEMenuView::DrawTextMenuPage ==========================> DrawTextMenuPage !" << endl;

	cout << "			CVNEMenuView::DrawTextMenuPage ==========================> DrawTextMenuPage SUCCESSFULL !" << endl;
}

void CVNEMenuView::ShowUpOrDownIcon(int iType)
{
	cout << "			CVNEMenuView::DrawItemMenu ==========================> DrawItemMenu !" << endl;
	switch (iType) {
	case 1: {
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMenu, Icon_up, menu_up_icon_x, menu_up_icon_y);
		break;
	}
	case 2: {
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMenu, Icon_down, menu_down_icon_x, menu_down_icon_y);
		break;
	}
	case 3: {
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMenu, Icon_up, menu_up_icon_x, menu_up_icon_y);
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMenu, Icon_down, menu_down_icon_x, menu_down_icon_y);
		break;
	}
	}
	cout << "			CVNEMenuView::DrawItemMenu ==========================> DrawItemMenu SUCCESSFULL !" << endl;
}

void CVNEMenuView::DrawItemMenu(int iNumItem)
{
	cout << "			CVNEMenuView::DrawItemMenu ==========================> DrawItemMenu !" << endl;
	for (int iIndex = 0; iIndex < iNumItem; iIndex++)
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMenu, Icon_menu, MenuLevel1def[iIndex].x, MenuLevel1def[iIndex].y, MenuLevel1def[iIndex].w, MenuLevel1def[iIndex].h);
	m_sfMenu->Flip(m_sfMenu, NULL, DSFLIP_WAITFORSYNC);
	cout << "			CVNEMenuView::DrawItemMenu ==========================> DrawItemMenu SUCCESSFULL !" << endl;
}

void CVNEMenuView::DrawMenuFocus(int iTypeMenu, int iDirection)
{
	cout << "			CVNEMenuView::DrawMenuFocus ==========================> DrawMenuFocus !" << endl;
	switch (iTypeMenu) {
	case MENU_LEVEL_1:
		this->FocusMenuLv1(iDirection);
		break;
	case MENU_LEVEL_2:
		this->FocusMenuLv2(iDirection);
		break;
	case MENU_LEVEL_3:
		this->FocusMenuLv3(iDirection);
		break;
	}
	cout << "			CVNEMenuView::DrawMenuFocus ==========================> DrawMenuFocus SUCCESSFULL !" << endl;
}

void CVNEMenuView::FocusMenuLv1(int iDirection)
{
	cout << "			CVNEMenuView::FocusMenuLv1 ==========================> FocusMenuLv1 !" << endl;
	switch (iDirection) {
	case MOVE_UP: {
		m_sfMenuFocus->Clear(m_sfMenuFocus, 0, 0, 0, 0);
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMenuFocus, Icon_menufocus, 0, 0);
		m_wMenuFocus->MoveTo(m_wMenuFocus, MenuLevel1def[iPosMenu % 9].x, MenuLevel1def[iPosMenu % 9].y);
		break;
	}
	case MOVE_DOWN: {
		m_sfMenuFocus->Clear(m_sfMenuFocus, 0, 0, 0, 0);
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMenuFocus, Icon_menufocus, 0, 0);
		m_wMenuFocus->MoveTo(m_wMenuFocus, MenuLevel1def[iPosMenu % 9].x, MenuLevel1def[iPosMenu % 9].y);
		break;
	}
	case MOVE_NOTHING: {
		m_sfMenuFocus->Clear(m_sfMenuFocus, 0, 0, 0, 0);
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMenuFocus, Icon_menufocus, 0, 0);
		m_wMenuFocus->MoveTo(m_wMenuFocus, MenuLevel1def[iPosMenu % 9].x, MenuLevel1def[iPosMenu % 9].y);
		break;
	}
	}
	cout << "			CVNEMenuView::FocusMenuLv1 ==========================> FocusMenuLv1 SUCCESSFULL !" << endl;
}

void CVNEMenuView::FocusMenuLv2(int iDirection)
{
	cout << "			CVNEMenuView::FocusMenuLv2 ==========================> FocusMenuLv2 !" << endl;
	cout << "			CVNEMenuView::FocusMenuLv2 ==========================> FocusMenuLv2 SUCCESSFULL !" << endl;
}

void CVNEMenuView::FocusMenuLv3(int iDirection)
{
	cout << "			CVNEMenuView::FocusMenuLv3 ==========================> FocusMenuLv3 !" << endl;
	cout << "			CVNEMenuView::FocusMenuLv3 ==========================> FocusMenuLv3 SUCCESSFULL !" << endl;
}

void CVNEMenuView::LoadStartup()
{
	cout << "			CVNEMenuView::LoadStartup ==========================> LoadStartup !" << endl;
	CFBGlobal::m_pGlobal->FBImageCreate(m_sfMainWindow, Images_startup, 0, 0);
	m_sfMainWindow->Flip(m_sfMainWindow, NULL, DSFLIP_WAITFORSYNC);
	m_sfMainWindow->Clear(m_sfMainWindow, 0x00, 0x00, 0x00, 0x00);
	CFBGlobal::m_pGlobal->FBImageCreate(m_sfMainWindow, Images_background, 0, 0);
	this->ShowUpOrDownIcon(3);
	this->DrawItemMenu(9);
	this->DrawTextMenuPage();
	this->DrawMenuFocus(MENU_LEVEL_1, MOVE_NOTHING);
	cout << "			CVNEMenuView::LoadStartup ==========================> LoadStartup SUCCESSFULL !" << endl;
}

void CVNEMenuView::ProcessKeyDown()
{
	cout << "			CVNEMenuView::ProcessKeyDown ==========================> ProcessKeyDown !" << endl;
	while (!bIsTurnOff) {
		DFBInputEvent event;
		if (CFBGlobal::events->GetEvent(CFBGlobal::events, DFB_EVENT(&event)) == DFB_OK) {
			if (event.type == DIET_KEYPRESS) {
				switch (event.key_symbol) {
				case DIKS_CURSOR_LEFT: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key LEFT !" << endl;

					break;
				}
				case DIKS_CURSOR_RIGHT: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key RIGHT !" << endl;

					break;
				}
				case DIKS_CURSOR_UP: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key UP !" << endl;
					iPosMenu--;
					this->DrawMenuFocus(MENU_LEVEL_1, MOVE_UP);

					break;
				}
				case DIKS_CURSOR_DOWN: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key DOWN !" << endl;
					iPosMenu++;
					this->DrawMenuFocus(MENU_LEVEL_1, MOVE_DOWN);
					break;
				}
				case DIKS_RETURN: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key OK !" << endl;

					break;
				}
				}
			}
		}
	}
	cout << "			CVNEMenuView::ProcessKeyDown ==========================> ProcessKeyDown SUCCESSFULL !" << endl;
}