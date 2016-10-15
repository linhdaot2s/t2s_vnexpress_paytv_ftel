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
	pListMenu = NULL;
	pSize18 = NULL;
	pSize20 = NULL;
	pSize25 = NULL;
	iPosMenu = 0;
	iPosMenuPage = 0;
	iPosMenuLevel = 1;
	bIsTurnOff = false;
	pCFBGlobal = CFBGlobal::FBSingletonGlobalInit();
	cout << "			CVNEMenuView::CVNEMenuView ==========================> Constructor SUCCESSFULL !" << endl;
}

CVNEMenuView::~CVNEMenuView()
{
	cout << "			CVNEMenuView::~CVNEMenuView ==========================> Destructor !" << endl;
	if (m_wMainWindow != NULL) {
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMainWindow !" << endl;
		pCFBGlobal->FBWindowDestroy(m_wMainWindow, m_sfMainWindow);
		m_wMainWindow = NULL; m_sfMainWindow = NULL;
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMainWindow  SUCCESSFULL !" << endl;
	}
	if (m_wMenu != NULL) {
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMenu !" << endl;
		pCFBGlobal->FBWindowDestroy(m_wMenu, m_sfMenu);
		m_wMenu = NULL; m_sfMenu = NULL;
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMenu  SUCCESSFULL !" << endl;
	}
	if (m_wMenuFocus != NULL) {
		cout << "			CVNEList::~CVNEList ---> Destroy m_wMenuFocus !" << endl;
		pCFBGlobal->FBWindowDestroy(m_wMenuFocus, m_sfMenuFocus);
		m_wMenuFocus = NULL; m_sfMenuFocus = NULL;
		cout << "			CVNEMenuView::~CVNEMenuView ---> Destroy m_wMenuFocus  SUCCESSFULL !" << endl;
	}
	if (pSize18 != NULL) {
		pCFBGlobal->FBFontDestroy(pSize18);
		pSize18 = NULL;
	}
	if (pSize20 != NULL) {
		pCFBGlobal->FBFontDestroy(pSize20);
		pSize20 = NULL;
	}
	if (pSize25 != NULL) {
		pCFBGlobal->FBFontDestroy(pSize25);
		pSize25 = NULL;
	}
	cout << "			CVNEMenuView::~CVNEMenuView ==========================> Destructor SUCCESSFULL !" << endl;
}

void CVNEMenuView::OnInit()
{
	cout << "			CVNEMenuView::OnInit ==========================> OnInit !" << endl;
	if (m_wMainWindow == NULL && m_sfMainWindow == NULL)
		pCFBGlobal->FBWindowCreateWithAlphaChannel(&m_wMainWindow, NULL, &m_sfMainWindow, 0, 0, Max_width, Max_height, 0xff);
	if (m_wMenu == NULL && m_sfMenu == NULL)
		pCFBGlobal->FBWindowCreateWithAlphaChannel(&m_wMenu, NULL, &m_sfMenu, menu_x, menu_y, menu_width, menu_height, 0xff);
	if (m_wMenuFocus == NULL && m_sfMenuFocus == NULL)
		pCFBGlobal->FBWindowCreateWithAlphaChannel(&m_wMenuFocus, NULL, &m_sfMenuFocus, 0, menu_focus_y, MenuLevel1def[0].w, MenuLevel1def[0].h, 0xff);
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
	cout << "			CVNEMenuView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon !" << endl;
	switch (iType) {
	case 1: {
		pCFBGlobal->FBImageCreate(m_sfMenu, Icon_up, menu_up_icon_x, menu_up_icon_y);
		break;
	}
	case 2: {
		pCFBGlobal->FBImageCreate(m_sfMenu, Icon_down, menu_down_icon_x, menu_down_icon_y);
		break;
	}
	case 3: {
		pCFBGlobal->FBImageCreate(m_sfMenu, Icon_up, menu_up_icon_x, menu_up_icon_y);
		pCFBGlobal->FBImageCreate(m_sfMenu, Icon_down, menu_down_icon_x, menu_down_icon_y);
		break;
	}
	}
	cout << "			CVNEMenuView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon SUCCESSFULL !" << endl;
}

void CVNEMenuView::DrawItemMenu(int iNumItem)
{
	cout << "			CVNEMenuView::DrawItemMenu ==========================> DrawItemMenu !" << endl;
	for (int iIndex = 0; iIndex < iNumItem; iIndex++)
		pCFBGlobal->FBImageCreate(m_sfMenu, Icon_menu, MenuLevel1def[iIndex].x, MenuLevel1def[iIndex].y, MenuLevel1def[iIndex].w, MenuLevel1def[iIndex].h);
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

void CVNEMenuView::OnLoad()
{
	cout << "			CVNEMenuView::OnLoad ==========================> OnLoad !" << endl;
	pListMenu = CVNEApp::GetInstance()->pCVNExpressModel->getMenuVNExpress();
	cout << "			CVNEMenuView::OnLoad ==========================> OnLoad  !    "<< pListMenu->size<<"  "<< pListMenu->sizepage << endl;
	if (pListMenu->size >= 1)
		iPosMenuPage = 1;
	if (pListMenu != NULL) {
		pCFBGlobal->FBFontCreate(&pSize18, "Roboto-Regular.ttf", 18);
		pCFBGlobal->FBFontCreate(&pSize20, "Roboto-Regular.ttf", 20);
		pCFBGlobal->FBFontCreate(&pSize25, "Roboto-Bold.ttf", 25);
		this->OnInit();
		this->LoadStartup();
		this->LoadPageItemMenuLv1();
	}
	cout << "			CVNEMenuView::OnLoad ==========================> OnLoad SUCCESSFULL !" << endl;
}

void CVNEMenuView::FocusMenuLv1(int iDirection)
{
	cout << "			CVNEMenuView::FocusMenuLv1 ==========================> FocusMenuLv1 !" << endl;
	m_sfMenuFocus->Clear(m_sfMenuFocus, 0, 0, 0, 0);
	m_sfMenuFocus->SetFont(m_sfMenuFocus, pSize25);
	switch (iDirection) {
	case MOVE_UP: {
		pCFBGlobal->FBImageCreate(m_sfMenuFocus, Icon_menufocus, 0, 0, menu_item_width, menu_item_height);
		pCFBGlobal->DrawTextMulti(m_sfMenuFocus, pSize25, pListMenu[iPosMenu].catename.c_str(), 125, 11,
			250, VNE_WHITE, (DFBSurfaceTextFlags) DSTF_TOPCENTER, false, 1);
		m_wMenuFocus->MoveTo(m_wMenuFocus, 0, MenuLevel1def[iPosMenu % 9].y + menu_focus_y);
		break;
	}
	case MOVE_DOWN: {
		pCFBGlobal->FBImageCreate(m_sfMenuFocus, Icon_menufocus, 0, 0, menu_item_width, menu_item_height);
		pCFBGlobal->DrawTextMulti(m_sfMenuFocus, pSize25, pListMenu[iPosMenu].catename.c_str(), 125, 11,
			250, VNE_WHITE, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 1);
		m_wMenuFocus->MoveTo(m_wMenuFocus, 0, MenuLevel1def[iPosMenu % 9].y + menu_focus_y);
		break;
	}
	case MOVE_NOTHING: {
		pCFBGlobal->FBImageCreate(m_sfMenuFocus, Icon_menufocus, 0, 0, menu_item_width, menu_item_height);
		pCFBGlobal->DrawTextMulti(m_sfMenuFocus, pSize25, pListMenu[iPosMenu].catename.c_str(), 125, 11,
			250, VNE_WHITE, (DFBSurfaceTextFlags) DSTF_TOPCENTER, false, 1);
		m_wMenuFocus->MoveTo(m_wMenuFocus, 0, MenuLevel1def[iPosMenu % 9].y + menu_focus_y);
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
	pCFBGlobal->FBImageCreate(m_sfMainWindow, Images_startup, 0, 0);
	m_sfMainWindow->Flip(m_sfMainWindow, NULL, DSFLIP_WAITFORSYNC);
	m_sfMainWindow->Clear(m_sfMainWindow, 0x00, 0x00, 0x00, 0x00);
	pCFBGlobal->FBImageCreate(m_sfMainWindow, Images_background, 0, 0);
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
					switch (iPosMenuLevel) {
					case MENU_LEVEL_1: {
						if (iPosMenu == 0) {
							iPosMenu = pListMenu->size - 1;
							iPosMenuPage = pListMenu->sizepage;
							this->LoadPageItemMenuLv1();
						}
						else {
							if ((iPosMenu) % 9 == 0) {
								iPosMenu -= 1;
								iPosMenuPage--;
								this->LoadPageItemMenuLv1();
							}
							else
								iPosMenu -= 1;
						}
						m_sfMenu->Flip(m_sfMenu, NULL, DSFLIP_WAITFORSYNC);
						this->DrawMenuFocus(MENU_LEVEL_1, MOVE_UP);
						break;
					}
					}
					break;
				}
				case DIKS_CURSOR_DOWN: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key DOWN !" << endl;
					switch (iPosMenuLevel) {
					case MENU_LEVEL_1: {
						if (iPosMenu == pListMenu->size - 1) {
							iPosMenu = 0;
							iPosMenuPage = 1;
							this->LoadPageItemMenuLv1();
						}
						else {
							if ((iPosMenu + 1) % 9 == 0) {
								iPosMenu += 1;
								iPosMenuPage++;
								this->LoadPageItemMenuLv1();
							}
							else
								iPosMenu += 1;
						}
						m_sfMenu->Flip(m_sfMenu, NULL, DSFLIP_WAITFORSYNC);
						this->DrawMenuFocus(MENU_LEVEL_1, MOVE_DOWN);
						break;
					}
					}
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

void CVNEMenuView::LoadPageItemMenuLv1()
{
	cout << "			CVNEMenuView::LoadItemMenuPage ==========================> LoadItemMenuPage !" << endl;
	int iHeight = 58;
	m_sfMenu->Clear(m_sfMenu, 0, 0, 0, 0);
	m_sfMenu->SetFont(m_sfMenu, pSize25);
	if (iPosMenuPage == 1) {
		if (pListMenu->size < 10) {
			cout << "			CVNEMenuView::LoadItemMenuPage ---> less than 10 item !" << endl;
			this->DrawItemMenu(pListMenu->size);
			for (int iIndex = 0; iIndex < pListMenu->size; iIndex++) 
				pCFBGlobal->DrawTextMulti(m_sfMenu, pSize25, pListMenu[iIndex].catename.c_str(),
					125, 73 + iHeight * iIndex, 250, VNE_BLACK, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 1);
		}
		else {
			cout << "			CVNEMenuView::LoadItemMenuPage ---> bigger than 10 item !" << endl;
			this->ShowUpOrDownIcon(2);
			this->DrawItemMenu(9);
			for (int iIndex = 0; iIndex < 9; iIndex++)
				pCFBGlobal->DrawTextMulti(m_sfMenu, pSize25, pListMenu[iIndex].catename.c_str(),
					125, 73 + iHeight * iIndex, 250, VNE_BLACK, (DFBSurfaceTextFlags) DSTF_TOPCENTER, false, 1);
		}
		m_sfMenu->Flip(m_sfMenu, NULL, DSFLIP_WAITFORSYNC);
	}
	else if (iPosMenuPage > 1 && iPosMenuPage < pListMenu->sizepage) {
		this->ShowUpOrDownIcon(3);
		this->DrawItemMenu(9);
		for (int iIndex = (iPosMenuPage - 1) * 9; iIndex < iPosMenuPage * 9; iIndex++)
			pCFBGlobal->DrawTextMulti(m_sfMenu, pSize25, pListMenu[iIndex].catename.c_str(), 125, 73 + iHeight * (iIndex % 9), 250,
				VNE_BLACK, (DFBSurfaceTextFlags) DSTF_TOPCENTER, false, 1);
	}
	else if (iPosMenuPage == pListMenu->sizepage) {
		this->ShowUpOrDownIcon(1);
		this->DrawItemMenu(pListMenu->size - ((pListMenu->sizepage - 1) * 9));
		for (int iIndex = (pListMenu->sizepage - 1) * 9; iIndex < pListMenu->size; iIndex++)
			pCFBGlobal->DrawTextMulti(m_sfMenu, pSize25, pListMenu[iIndex].catename.c_str(), 125, 73 + iHeight * (iIndex % 9), 250,
				VNE_BLACK, (DFBSurfaceTextFlags) DSTF_TOPCENTER, false, 1);
	}
	cout << "			CVNEMenuView::LoadItemMenuPage ==========================> LoadItemMenuPage SUCCESSFULL !" << endl;
}
