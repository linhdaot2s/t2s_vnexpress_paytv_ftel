#include "CVNEListView.h"

CVNEListView::CVNEListView()
{
	cout << "			CVNEListView::CVNEListView ==========================> Constructor !" << endl;
	m_wMainView = NULL;
	m_sfMainView = NULL;
	m_wMainFocus = NULL;
	m_sfMainFocus = NULL;
	pListItem = NULL;
	pLoadPic = NULL;
	pSize18 = NULL;
	pSize20 = NULL;
	pSize25 = NULL;
	iPosInfoPage = 0;
	iPosInfo = 0;
	bIsBreak = false;
	bIsListView = true;
	pCFBGlobal = CFBGlobal::FBSingletonGlobalInit();
	this->OnInit();
	cout << "			CVNEListView::CVNEListView ==========================> Constructor SUCCESSFULL !" << endl;
}


CVNEListView::~CVNEListView()
{
	cout << "			CVNEListView::~CVNEListView ==========================> Destructor !" << endl;
	if (m_wMainView != NULL) {
		cout << "			CVNEListView::~CVNEListView ---> Destroy m_wMainView !" << endl;
		pCFBGlobal->FBWindowDestroy(m_wMainView, m_sfMainView);
		m_wMainView = NULL; m_sfMainView = NULL;
		cout << "			CVNEListView::~CVNEListView ---> Destroy m_wMainView  SUCCESSFULL !" << endl;
	}
	if (m_wMainFocus != NULL) {
		cout << "			CVNEListView::~CVNEListView ---> Destroy m_wMainFocus !" << endl;
		pCFBGlobal->FBWindowDestroy(m_wMainFocus, m_sfMainFocus);
		m_wMainFocus = NULL; m_sfMainFocus = NULL;
		cout << "			CVNEListView::~CVNEListView ---> Destroy m_wMainFocus  SUCCESSFULL !" << endl;
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
	this->CancelThreadPicture();
	cout << "			CVNEListView::~CVNEListView ==========================> Destructor SUCCESSFULL !" << endl;
}

void CVNEListView::CancelThreadPicture()
{
	printf("				CVNEListView::CancelThreadPicture ==============================================>	Cancel Thread Load Picture \n");
	if (pLoadPic) {
		printf("				CVNEListView::CancelThreadPicture --->	pLoadpic is survival ! \n");
		pthread_cancel(pLoadPic);
		pthread_join(pLoadPic, NULL);
		pLoadPic = NULL;
		printf("				CVNEListView::CancelThreadPicture --->	pLoadpic has been canceled SUCCESSFULL ! \n");
	}
	printf("				CVNEListView::CancelThreadPicture ==============================================>	Cancel Thread Load Picture SUCCESSFULL ! \n");
}

void CVNEListView::FillRectPic(int iNumPic)
{
	cout << "			CVNEListView::FillRectPic ==========================> FillRectPic !" << endl;
	m_sfMainView->SetColor(m_sfMainView, 0x00, 0x00, 0x00, 0xff);
	for (int iIndex = 0; iIndex < iNumPic; iIndex++)
		m_sfMainView->DrawRectangle(m_sfMainView, Picdef[iIndex].x, Picdef[iIndex].y, Picdef[iIndex].w, Picdef[iIndex].h);

	m_sfMainView->Flip(m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
	cout << "			CVNEListView::FillRectPic ==========================> FillRectPic SUCCESSFULL !" << endl;
}

void CVNEListView::OnLoad(string strCateID)
{
	cout << "			CVNEListView::OnLoad ==========================> OnLoad !" << endl;
	pListItem = CVNEApp::GetInstance()->pCVNExpressModel->getListVNExpress(strCateID, "50", "0");
	if (pListItem != NULL) {
		iPosInfoPage = 1;
		this->LoadStartup();
	}
	cout << "			CVNEListView::OnLoad ==========================> OnLoad SUCCESSFULL !" << endl;
}

void CVNEListView::OnInit()
{
	cout << "			CVNEListView::OnInit ==========================> OnInit !" << endl;
	if (m_wMainView == NULL && m_sfMainView == NULL)
		pCFBGlobal->FBWindowCreateWithAlphaChannel(&m_wMainView, NULL, &m_sfMainView, list_x, list_y, list_width, list_height, 0xff);
	if (m_wMainFocus == NULL && m_sfMainFocus == NULL)
		pCFBGlobal->FBWindowCreateWithAlphaChannel(&m_wMainFocus, NULL, &m_sfMainFocus, list_x, media_y, 250, 250, 0x00);
	if (pSize18 == NULL)
		pCFBGlobal->FBFontCreate(&pSize18, "Roboto-Regular.ttf", 18);
	if (pSize20 == NULL)
		pCFBGlobal->FBFontCreate(&pSize20, "Roboto-Regular.ttf", 20);
	if (pSize25 == NULL)
		pCFBGlobal->FBFontCreate(&pSize25, "Roboto-Bold.ttf", 25);
	cout << "			CVNEListView::OnInit ==========================> OnInit SUCCESSFULL !" << endl;
}

void CVNEListView::FlipAll()
{
	cout << "			CVNEListView::FlipAll ==========================> FlipAll !" << endl;
	m_sfMainView->Flip(m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
	cout << "			CVNEListView::FlipAll ==========================> FlipAll SUCCESSFULL !" << endl;
}

void CVNEListView::LoadStartup()
{
	cout << "			CVNEListView::LoadStartup ==========================> LoadStartup !" << endl;
	iPosInfo = 0;
	this->CancelThreadPicture();
	pthread_create(&pLoadPic, NULL, CVNEListView::createPthreadShowItemsChangePage, (void*)this);
	this->DrawFocusInfo();
	this->FlipAll();
	cout << "			CVNEListView::LoadStartup ==========================> LoadStartup SUCCESSFULL !" << endl;
}

void CVNEListView::DrawFocusInfo()
{
	m_sfMainFocus->Clear(m_sfMainFocus, 0x00, 0x00, 0x00, 0x00);
	m_sfMainFocus->SetColor(m_sfMainFocus, 0x83, 0x00, 0x00, 0xff);
	m_sfMainFocus->FillRectangle(m_sfMainFocus, 0, 0, 230, 10);
	m_sfMainFocus->FillRectangle(m_sfMainFocus, 0, 0, 10, 250);
	m_sfMainFocus->FillRectangle(m_sfMainFocus, 230, 0, 10, 250);
	m_sfMainFocus->SetFont(m_sfMainFocus, pSize20);
	int iFontHeight = 0, iNumLine = 0;
	pSize20->GetHeight(pSize20, &iFontHeight);
	iNumLine = pCFBGlobal->CountNumLine(pSize20, pListItem[iPosInfo].title.c_str(), 240);
	if (iNumLine > 1) {
		m_sfMainFocus->FillRectangle(m_sfMainFocus, 0, (255 - iFontHeight - (iFontHeight * iNumLine)), 230, 10 + (iFontHeight * (iNumLine + 1)));
		pCFBGlobal->DrawTextMulti(m_sfMainFocus, pSize20,
			pListItem[iPosInfo].title.c_str(), 10, ((255 - iFontHeight - (iFontHeight * iNumLine)) + iFontHeight / 2), 240, VNE_WHITE, (DFBSurfaceTextFlags)DSTF_TOPLEFT, true, 2);
	}
	else {
		m_sfMainFocus->FillRectangle(m_sfMainFocus, 0, 180, 230, 75);
		pCFBGlobal->DrawTextMulti(m_sfMainFocus, pSize20,
			pListItem[iPosInfo].title.c_str(), 10, (180 + ((55 - iFontHeight) / 2)), 240, VNE_WHITE, (DFBSurfaceTextFlags)DSTF_TOPLEFT, true, 2);
	}
	m_wMainFocus->MoveTo(m_wMainFocus, Picdef[iPosInfo % 8].x + 240, Picdef[iPosInfo % 8].y + 77);
}

void CVNEListView::DrawTextInfoPage()
{
	cout << "			CVNEListView::DrawTextInfoPage ==========================> DrawTextInfoPage !" << endl;
	cout << "			CVNEListView::DrawTextInfoPage ==========================> DrawTextInfoPage SUCCESSFULL !" << endl;
}

void CVNEListView::ShowUpOrDownIcon(int iType)
{
	cout << "			CVNEListView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon !" << endl;
	switch (iType) {
	case 1: {
		pCFBGlobal->FBImageCreate(m_sfMainView, Icon_up, detail_up_icon_x, detail_up_icon_y);
		break;
	}
	case 2: {
		pCFBGlobal->FBImageCreate(m_sfMainView, Icon_down, detail_down_icon_x, detail_down_icon_y);
		break;
	}
	case 3: {
		pCFBGlobal->FBImageCreate(m_sfMainView, Icon_up, detail_up_icon_x, detail_up_icon_y);
		pCFBGlobal->FBImageCreate(m_sfMainView, Icon_down, detail_down_icon_x, detail_down_icon_y);
		break;
	}
	}
	cout << "			CVNEListView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon SUCCESSFULL !" << endl;
}

void* CVNEListView::createPthreadShowItemsChangePage(void *vshowItemsChangePage)
{
	CVNEListView *m_pVNExpressThis = (CVNEListView*)vshowItemsChangePage;
	m_pVNExpressThis->m_sfMainView->Clear(m_pVNExpressThis->m_sfMainView, 0, 0, 0, 0);
	m_pVNExpressThis->m_sfMainView->SetFont(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20);
	if (m_pVNExpressThis->pListItem->size < 9) {
		printf("				CVNEListView::createPthreadShowItemsChangePage ---> First page less :  \n");
		m_pVNExpressThis->FillRectPic(m_pVNExpressThis->pListItem->size);
		for (int i = 0; i < m_pVNExpressThis->pListItem->size; i++) {
			m_pVNExpressThis->pCFBGlobal->DrawTextMulti(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20,
				m_pVNExpressThis->pListItem[i].title.c_str(), TextDef[i % 8].x, TextDef[i % 8].y,
				240, VNE_BLACK, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 2);
		}
		m_pVNExpressThis->m_sfMainView->Flip(m_pVNExpressThis->m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
		for (int i = 0; i < m_pVNExpressThis->pListItem->size; i++) {
			string link = m_pVNExpressThis->pListItem[i].thumbnail_url;
			m_pVNExpressThis->pCFBGlobal->FBImageCreate(m_pVNExpressThis->m_sfMainView,
				link.c_str(), Picdef[i].x, Picdef[i].y, Picdef[i].w, Picdef[i].h);
			m_pVNExpressThis->m_sfMainView->Flip(m_pVNExpressThis->m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
		}
	}
	else {
		if (m_pVNExpressThis->iPosInfoPage == 1) {
			printf("				CVNEListView::createPthreadShowItemsChangePage ---> First page :  \n");
			m_pVNExpressThis->ShowUpOrDownIcon(2);
			m_pVNExpressThis->FillRectPic(8);
			for (int i = 0; i <= 7; i++) {
				m_pVNExpressThis->pCFBGlobal->DrawTextMulti(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20,
					m_pVNExpressThis->pListItem[i].title.c_str(), TextDef[i % 8].x, TextDef[i % 8].y,
					240, VNE_BLACK, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 2);
			}
			m_pVNExpressThis->m_sfMainView->Flip(m_pVNExpressThis->m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
			for (int i = 0; i <= 7; i++) {
				string link = m_pVNExpressThis->pListItem[i].thumbnail_url;
				m_pVNExpressThis->pCFBGlobal->FBImageCreate(m_pVNExpressThis->m_sfMainView,
					link.c_str(), Picdef[i].x, Picdef[i].y, Picdef[i].w, Picdef[i].h);
				m_pVNExpressThis->m_sfMainView->Flip(m_pVNExpressThis->m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
			}
		}
		else {
			if (m_pVNExpressThis->iPosInfoPage > 1 && m_pVNExpressThis->iPosInfoPage < m_pVNExpressThis->pListItem->sizepage) {
				printf("				CVNEListView::createPthreadShowItemsChangePage ---> Middle page :  \n");
				m_pVNExpressThis->ShowUpOrDownIcon(3);
				m_pVNExpressThis->FillRectPic(8);
				for (int i = (m_pVNExpressThis->iPosInfoPage - 1) * 8; i < m_pVNExpressThis->iPosInfoPage * 8; i++) {
					m_pVNExpressThis->pCFBGlobal->DrawTextMulti(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20,
						m_pVNExpressThis->pListItem[i].title.c_str(), TextDef[i % 8].x, TextDef[i % 8].y,
						240, VNE_BLACK, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 2);
				}
				m_pVNExpressThis->m_sfMainView->Flip(m_pVNExpressThis->m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
				for (int i = (m_pVNExpressThis->iPosInfoPage - 1) * 8; i < m_pVNExpressThis->iPosInfoPage * 8; i++) {
					string link = m_pVNExpressThis->pListItem[i].thumbnail_url;
					m_pVNExpressThis->pCFBGlobal->FBImageCreate(m_pVNExpressThis->m_sfMainView,
						link.c_str(), Picdef[i].x, Picdef[i].y, Picdef[i].w, Picdef[i].h);
					m_pVNExpressThis->m_sfMainView->Flip(m_pVNExpressThis->m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
				}
			}
			else {
				printf("				CVNEListView::createPthreadShowItemsChangePage ---> Last page :  \n");
				m_pVNExpressThis->ShowUpOrDownIcon(1);
				m_pVNExpressThis->FillRectPic(m_pVNExpressThis->pListItem->size - ((m_pVNExpressThis->pListItem->sizepage - 1) * 8));
				for (int i = (m_pVNExpressThis->pListItem->sizepage - 1) * 8; i < m_pVNExpressThis->pListItem->size; i++) {
					cout << endl << i << endl;
					m_pVNExpressThis->pCFBGlobal->DrawTextMulti(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20,
						m_pVNExpressThis->pListItem[i].title.c_str(), TextDef[i % 8].x, TextDef[i % 8].y,
						240, VNE_BLACK, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 2);
				}
				m_pVNExpressThis->m_sfMainView->Flip(m_pVNExpressThis->m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
				for (int i = (m_pVNExpressThis->pListItem->sizepage - 1) * 8; i < m_pVNExpressThis->pListItem->size; i++) {
					string link = m_pVNExpressThis->pListItem[i].thumbnail_url;
					m_pVNExpressThis->pCFBGlobal->FBImageCreate(m_pVNExpressThis->m_sfMainView,
						link.c_str(), Picdef[i].x, Picdef[i].y, Picdef[i].w, Picdef[i].h);
					m_pVNExpressThis->m_sfMainView->Flip(m_pVNExpressThis->m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
				}
			}
		}
	}
	pthread_exit(NULL);
}

bool CVNEListView::ProcessKeyDown()
{
	cout << "			CVNEListView::ProcessKeyDown ==========================> ProcessKeyDown !" << endl;
	bIsBreak = false;
	m_wMainFocus->SetOpacity(m_wMainFocus, 0xff);
	while (!bIsBreak) {
		DFBInputEvent event;
		if (CFBGlobal::events->GetEvent(CFBGlobal::events, DFB_EVENT(&event)) == DFB_OK) {
			if (event.type == DIET_KEYPRESS) {
				switch (event.key_symbol) {
				case DIKS_CURSOR_LEFT: {
					cout << "			CVNEListView::ProcessKeyDown ---> key LEFT !" << endl;
					if (iPosInfo % 4 == 0) {
						bIsBreak = true;
						m_wMainFocus->SetOpacity(m_wMainFocus, 0);
					}
					else {
						iPosInfo--;
						this->DrawFocusInfo();
					}
					break;
				}
				case DIKS_CURSOR_RIGHT: {
					cout << "			CVNEListView::ProcessKeyDown ---> key RIGHT !" << endl;
					if ((iPosInfo + 1) % 8 == 0) {
						iPosInfo++; iPosInfoPage++;
						this->DrawFocusInfo();
						this->CancelThreadPicture();
						pthread_create(&pLoadPic, NULL, CVNEListView::createPthreadShowItemsChangePage, (void*)this);
					}
					else {
						if (iPosInfo == pListItem->size - 1) {
							iPosInfo = pListItem->size - 1;
							iPosInfoPage = pListItem->sizepage;
						}
						else {
							iPosInfo++;
							this->DrawFocusInfo();
						}
					}
					break;
				}
				case DIKS_CURSOR_UP: {
					cout << "			CVNEListView::ProcessKeyDown ---> key UP !" << endl;
					if (iPosInfo - 4 >= 0) {
						if (iPosInfo % 8 > 3) {
							printf("				CVNExpressListView::OnKeyDown ---> move Up don't load page !\n");
							iPosInfo -= 4;
							this->DrawFocusInfo();
						}
						else {
							printf("				CVNExpressListView::OnKeyDown ---> move Up load page !\n");
							iPosInfo -= 4;
							iPosInfoPage--;
							this->DrawFocusInfo();
							this->CancelThreadPicture();
							pthread_create(&pLoadPic, NULL, CVNEListView::createPthreadShowItemsChangePage, (void*)this);
						}
					}
					break;
				}
				case DIKS_CURSOR_DOWN: {
					cout << "			CVNEListView::ProcessKeyDown ---> key DOWN !" << endl;
					if (iPosInfo + 4 <= pListItem->size - 1) {
						if (iPosInfo % 8 < 4) {
							printf("				CVNEListView::OnKeyDown ---> move Down don't load page !\n");
							iPosInfo += 4;
							this->DrawFocusInfo();
						}
						else {
							printf("				CVNEListView::OnKeyDown ---> move Down load page !\n");
							iPosInfo += 4;
							iPosInfoPage++;
							this->DrawFocusInfo();
							this->CancelThreadPicture();
							pthread_create(&pLoadPic, NULL, CVNEListView::createPthreadShowItemsChangePage, (void*)this);
						}
					}
					break;
				}
				case DIKS_RETURN: {
					cout << "			CVNEListView::ProcessKeyDown ---> key RETURN !" << endl;
					bool bCheckData = CVNEApp::GetInstance()->pCVNEDetailView->OnLoad(pListItem[iPosInfo].article_id);
					if (bCheckData) {
						m_wMainView->SetOpacity(m_wMainView, 0);
						m_wMainFocus->SetOpacity(m_wMainFocus, 0);
						CVNEApp::GetInstance()->pCVNEDetailView->ProcessHTMLDetail();
						CVNEApp::GetInstance()->pCVNEDetailView->DrawFocusText();
						bool bCheckShow = CVNEApp::GetInstance()->pCVNEDetailView->ProcessKeyDown();
						if (bCheckShow) {
							m_wMainView->SetOpacity(m_wMainView, 255);
							m_wMainFocus->SetOpacity(m_wMainFocus, 255);
						}
						else {
							bIsBreak = true;
							return false;
						}
					}
					break;
				}
				case DIKS_AUDIO: {
					cout << "			CVNEListView::ProcessKeyDown ---> key AUDIO !" << endl;
					CVNEApp::GetInstance()->saveListItem(pListItem[iPosInfo].article_id, pListItem[iPosInfo].title);
					break;
				}
				case DIKS_INFO: {
					CVNEApp::GetInstance()->pCVNEPlaybackView->OnLoad();
					CVNEApp::GetInstance()->pCVNEPlaybackView->ProcessKeyDown();
					break;
				}
				case DIKS_STOP: {
					CVNEApp::GetInstance()->gst->close();
					break;
				}
				}
			}
		}
	}
	cout << "			CVNEListView::ProcessKeyDown ==========================> ProcessKeyDown SUCCESSFULL !" << endl;
}
