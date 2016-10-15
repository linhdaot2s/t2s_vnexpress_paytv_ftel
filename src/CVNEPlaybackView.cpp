#include "CVNEPlaybackView.h"

CVNEPlaybackView::CVNEPlaybackView()
{
	cout << "			CVNEPlaybackView::CVNEPlaybackView ==========================> Constructor !" << endl;
	m_wMediaPlayer = NULL;
	m_sfMediaPlayer = NULL;
	this->OnInit();
	this->LoadStartup();
	cout << "			CVNEPlaybackView::CVNEPlaybackView ==========================> Constructor SUCCESSFULL !" << endl;
}

CVNEPlaybackView::~CVNEPlaybackView()
{
	cout << "			CVNEPlaybackView::~CVNEPlaybackView ==========================> Destructor !" << endl;
	if (m_wMediaPlayer != NULL) {
		cout << "			CVNEPlaybackView::~CVNEPlaybackView ---> Destroy m_wMediaPlayer !" << endl;
		CFBGlobal::m_pGlobal->m_pGlobal->FBWindowDestroy(m_wMediaPlayer, m_sfMediaPlayer);
		m_wMediaPlayer = NULL; m_sfMediaPlayer = NULL;
		cout << "			CVNEPlaybackView::~CVNEPlaybackView ---> Destroy m_wMediaPlayer  SUCCESSFULL !" << endl;
	}
	cout << "			CVNEPlaybackView::~CVNEPlaybackView ==========================> Destructor SUCCESSFULL !" << endl;
}

void CVNEPlaybackView::OnInit()
{
	cout << "			CVNEPlaybackView::OnInit ==========================> OnInit !" << endl;
	if (m_wMediaPlayer == NULL && m_sfMediaPlayer == NULL)
		CFBGlobal::m_pGlobal->m_pGlobal->FBWindowCreateWithAlphaChannel(&m_wMediaPlayer, NULL, &m_sfMediaPlayer, media_x, media_y, media_width, media_height, 0xff);
	cout << "			CVNEPlaybackView::OnInit ==========================> OnInit SUCCESSFULL !" << endl;
}

void CVNEPlaybackView::FlipAll()
{
	cout << "			CVNEPlaybackView::FlipAll ==========================> FlipAll !" << endl;
	m_sfMediaPlayer->Flip(m_sfMediaPlayer, NULL, DSFLIP_WAITFORSYNC);
	cout << "			CVNEPlaybackView::FlipAll ==========================> FlipAll SUCCESSFULL !" << endl;
}

void CVNEPlaybackView::LoadStartup()
{
	cout << "			CVNEPlaybackView::LoadStartup ==========================> LoadStartup !" << endl;
	this->ShowPlayBar(false);
	cout << "			CVNEPlaybackView::LoadStartup ==========================> LoadStartup SUCCESSFULL !" << endl;
}

void CVNEPlaybackView::ShowPlayBar(bool bIsShow)
{
	cout << "			CVNEPlaybackView::ShowPlayBar ==========================> ShowPlayBar !" << endl;
	if (bIsShow) {
		cout << "			CVNEPlaybackView::ShowPlayBar ---> Show playbar !" << endl;

	}
	else {
		cout << "			CVNEPlaybackView::ShowPlayBar ---> Hide playbar !" << endl;
		CFBGlobal::m_pGlobal->FBImageCreate(m_sfMediaPlayer, Icon_hide, 0, 0, media_width, media_height);
		m_sfMediaPlayer->Flip(m_sfMediaPlayer, NULL, DSFLIP_WAITFORSYNC);
	}
	cout << "			CVNEPlaybackView::ShowPlayBar ==========================> ShowPlayBar SUCCESSFULL !" << endl;

}
