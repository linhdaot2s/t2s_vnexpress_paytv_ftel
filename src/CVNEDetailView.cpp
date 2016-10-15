#include "CVNEDetailView.h"

CVNEDetailView::CVNEDetailView()
{
	cout << "			CVNEDetailView::CVNEDetailView ==========================> Constructor !" << endl;
	m_wMainView = NULL;
	m_sfMainView = NULL;
	m_wMainFocus = NULL;
	m_sfMainFocus = NULL;
	this->OnInit();
	this->LoadStartup();
	cout << "			CVNEDetailView::CVNEDetailView ==========================> Constructor SUCCESSFULL !" << endl;
}


CVNEDetailView::~CVNEDetailView()
{
	cout << "			CVNEDetailView::~CVNEDetailView ==========================> Destructor !" << endl;
	if (m_wMainView != NULL) {
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainView !" << endl;
		CFBGlobal::m_pGlobal->FBWindowDestroy(m_wMainView, m_sfMainView);
		m_wMainView = NULL; m_sfMainView = NULL;
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainView  SUCCESSFULL !" << endl;
	}
	if (m_wMainFocus != NULL) {
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainFocus !" << endl;
		CFBGlobal::m_pGlobal->FBWindowDestroy(m_wMainFocus, m_sfMainFocus);
		m_wMainFocus = NULL; m_sfMainFocus = NULL;
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainFocus  SUCCESSFULL !" << endl;
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

void CVNEDetailView::OnInit()
{
	cout << "			CVNEDetailView::OnInit ==========================> OnInit !" << endl;
	if (m_wMainView == NULL && m_sfMainView == NULL)
		CFBGlobal::m_pGlobal->FBWindowCreateWithAlphaChannel(&m_wMainView, NULL, &m_sfMainView, list_x, list_y, list_width, list_height, 0xff);
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
	this->FillRectPic(8);
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
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMainView, Icon_up, detail_up_icon_x, detail_up_icon_y);
		break;
	}
	case 2: {
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMainView, Icon_down, detail_down_icon_x, detail_down_icon_y);
		break;
	}
	case 3: {
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMainView, Icon_up, detail_up_icon_x, detail_up_icon_y);
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMainView, Icon_down, detail_down_icon_x, detail_down_icon_y);
		break;
	}
	}
	cout << "			CVNEDetailView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon SUCCESSFULL !" << endl;
}
