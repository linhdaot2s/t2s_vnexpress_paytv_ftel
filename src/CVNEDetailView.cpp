#include "CVNEDetailView.h"

CVNEDetailView::CVNEDetailView()
{
	cout << "			CVNEDetailView::CVNEDetailView ==========================> Constructor !" << endl;
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
	pCFBGlobal = CFBGlobal::FBSingletonGlobalInit();
	cout << "			CVNEDetailView::CVNEDetailView ==========================> Constructor SUCCESSFULL !" << endl;
}


CVNEDetailView::~CVNEDetailView()
{
	cout << "			CVNEDetailView::~CVNEDetailView ==========================> Destructor !" << endl;
	if (m_wMainView != NULL) {
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainView !" << endl;
		pCFBGlobal->FBWindowDestroy(m_wMainView, m_sfMainView);
		m_wMainView = NULL; m_sfMainView = NULL;
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainView  SUCCESSFULL !" << endl;
	}
	if (m_wMainFocus != NULL) {
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainFocus !" << endl;
		pCFBGlobal->FBWindowDestroy(m_wMainFocus, m_sfMainFocus);
		m_wMainFocus = NULL; m_sfMainFocus = NULL;
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainFocus  SUCCESSFULL !" << endl;
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
	cout << "			CVNEDetailView::~CVNEDetailView ==========================> Destructor SUCCESSFULL !" << endl;
}

void CVNEDetailView::FillRectPic(int iNumPic)
{
	cout << "			CVNEDetailView::FillRectPic ==========================> FillRectPic !" << endl;
	m_sfMainView->SetColor(m_sfMainView, 0x00, 0x00, 0x00, 0xff);
	for (int iIndex = 0; iIndex < iNumPic; iIndex++)
		m_sfMainView->DrawRectangle(m_sfMainView, Picdef[iIndex].x, Picdef[iIndex].y, Picdef[iIndex].w, Picdef[iIndex].h);

	m_sfMainView->Flip(m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
	cout << "			CVNEDetailView::FillRectPic ==========================> FillRectPic SUCCESSFULL !" << endl;
}

void CVNEDetailView::OnLoad(string strCateID)
{
	cout << "			CVNEDetailView::OnLoad ==========================> OnLoad !" << endl;
	pListItem =  CVNEApp::GetInstance()->pCVNExpressModel->getListVNExpress(strCateID, "50", "0");
	if (pListItem != NULL) {
		iPosInfoPage = 1;
		pCFBGlobal->FBFontCreate(&pSize18, "Roboto-Regular.ttf", 18);
		pCFBGlobal->FBFontCreate(&pSize20, "Roboto-Regular.ttf", 20);
		pCFBGlobal->FBFontCreate(&pSize25, "Roboto-Bold.ttf", 25);
		this->OnInit();
		this->LoadStartup();
	}
	cout << "			CVNEDetailView::OnLoad ==========================> OnLoad SUCCESSFULL !" << endl;
}

void CVNEDetailView::OnInit()
{
	cout << "			CVNEDetailView::OnInit ==========================> OnInit !" << endl;
	if (m_wMainView == NULL && m_sfMainView == NULL)
		pCFBGlobal->FBWindowCreateWithAlphaChannel(&m_wMainView, NULL, &m_sfMainView, list_x, list_y, list_width, list_height, 0xff);
	cout << "			CVNEDetailView::OnInit ==========================> OnInit SUCCESSFULL !" << endl;
}

void CVNEDetailView::FlipAll()
{
	cout << "			CVNEDetailView::FlipAll ==========================> FlipAll !" << endl;
	m_sfMainView->Flip(m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
	cout << "			CVNEDetailView::FlipAll ==========================> FlipAll SUCCESSFULL !" << endl;
}

void CVNEDetailView::LoadStartup()
{
	cout << "			CVNEDetailView::LoadStartup ==========================> LoadStartup !" << endl;
	pthread_create(&pLoadPic, NULL, CVNEDetailView::createPthreadShowItemsChangePage, (void*)this);
	this->FlipAll();
	cout << "			CVNEDetailView::LoadStartup ==========================> LoadStartup SUCCESSFULL !" << endl;
}

void CVNEDetailView::DrawTextInfoPage()
{
	cout << "			CVNEDetailView::DrawTextInfoPage ==========================> DrawTextInfoPage !" << endl;
	cout << "			CVNEDetailView::DrawTextInfoPage ==========================> DrawTextInfoPage SUCCESSFULL !" << endl;
}

void CVNEDetailView::ShowUpOrDownIcon(int iType)
{
	cout << "			CVNEDetailView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon !" << endl;
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
	cout << "			CVNEDetailView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon SUCCESSFULL !" << endl;
}

void* CVNEDetailView::createPthreadShowItemsChangePage(void *vshowItemsChangePage)
{
	CVNEDetailView *m_pVNExpressThis = (CVNEDetailView*)vshowItemsChangePage;
	m_pVNExpressThis->m_sfMainView->SetFont(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20);
	if (m_pVNExpressThis->pListItem->size < 9) {
		printf("				CVNEDetailView::createPthreadShowItemsChangePage ---> First page less :  \n");
		m_pVNExpressThis->FillRectPic(m_pVNExpressThis->pListItem->size);
		for (int i = 0; i < m_pVNExpressThis->pListItem->size; i++) {
			m_pVNExpressThis->pCFBGlobal->DrawTextMulti(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20,
				m_pVNExpressThis->pListItem[m_pVNExpressThis->iPosInfo].title.c_str(), TextDef[i%8].x, TextDef[i % 8].y,
				250, VNE_BLACK, (DFBSurfaceTextFlags) DSTF_TOPCENTER, false, 2);
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
			printf("				CVNEDetailView::createPthreadShowItemsChangePage ---> First page :  \n");
			m_pVNExpressThis->ShowUpOrDownIcon(2);
			m_pVNExpressThis->FillRectPic(8);
			for (int i = 0; i <= 7; i++) {
				m_pVNExpressThis->pCFBGlobal->DrawTextMulti(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20,
					m_pVNExpressThis->pListItem[m_pVNExpressThis->iPosInfo].title.c_str(), TextDef[i % 8].x, TextDef[i % 8].y,
					250, VNE_BLACK, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 2);
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
				printf("				CVNExpressListView::createPthreadShowItemsChangePage ---> Middle page :  \n");
				m_pVNExpressThis->ShowUpOrDownIcon(3);
				m_pVNExpressThis->FillRectPic(8);
				for (int i = (m_pVNExpressThis->iPosInfoPage - 1) * 8; i < m_pVNExpressThis->iPosInfoPage * 8; i++) {
					m_pVNExpressThis->pCFBGlobal->DrawTextMulti(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20,
						m_pVNExpressThis->pListItem[m_pVNExpressThis->iPosInfo].title.c_str(), TextDef[i % 8].x, TextDef[i % 8].y,
						250, VNE_BLACK, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 2);
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
				printf("				CVNExpressListView::createPthreadShowItemsChangePage ---> Last page :  \n");
				m_pVNExpressThis->ShowUpOrDownIcon(1);
				m_pVNExpressThis->FillRectPic(m_pVNExpressThis->pListItem->size - ((m_pVNExpressThis->pListItem->sizepage - 1) * 8));
				for (int i = (m_pVNExpressThis->pListItem->sizepage - 1) * 8; i < m_pVNExpressThis->pListItem->size; i++) {
					m_pVNExpressThis->pCFBGlobal->DrawTextMulti(m_pVNExpressThis->m_sfMainView, m_pVNExpressThis->pSize20,
						m_pVNExpressThis->pListItem[m_pVNExpressThis->iPosInfo].title.c_str(), TextDef[i % 8].x, TextDef[i % 8].y,
						250, VNE_BLACK, (DFBSurfaceTextFlags)DSTF_TOPCENTER, false, 2);
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
