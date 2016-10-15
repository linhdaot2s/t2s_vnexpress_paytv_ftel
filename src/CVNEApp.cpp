#include "CVNEApp.h"

CVNEApp::CVNEApp()
{
	cout << "			CVNEApp::CVNEApp ==========================> Constructor !" << endl;
	m_pGlobal							= CFBGlobal::FBSingletonGlobalInit();
	pCVNEMenuView = NULL;
	pCVNEDetailView = NULL;
	pCVNEPlaybackView = NULL;

	pCVNEMenuView		= new CVNEMenuView();
	pCVNEDetailView	= new CVNEDetailView();
	pCVNEPlaybackView = new CVNEPlaybackView();

	pCVNEMenuView->FlipAll();
	pCVNEDetailView->FlipAll();
	pCVNEPlaybackView->FlipAll();
	cout << "			CVNEApp::CVNEApp ==========================> Constructor SUCCESSFULL !" << endl;
}


CVNEApp::~CVNEApp()
{
}

void CVNEApp::Onload()
{
	cout << "			CVNEApp::Onload ==========================> Onload !" << endl;
	pCVNEMenuView->ProcessKeyDown();
	cout << "			CVNEApp::Onload ==========================> Onload SUCCESSFULL !" << endl;
}
