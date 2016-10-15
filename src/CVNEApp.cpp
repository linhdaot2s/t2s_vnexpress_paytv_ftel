#include "CVNEApp.h"

CVNEApp *CVNEApp::pApp = NULL;

CVNEApp *CVNEApp::GetInstance()
{
	if (pApp == NULL) 
	{
		cout << "			CVNEApp::CVNEApp 1231242434 Constructor !" << endl;
		pApp = new CVNEApp();
	}
	return pApp;
}

CVNEApp::CVNEApp()
{
	cout << "			CVNEApp::CVNEApp ==========================> Constructor !" << endl;
	pCVNEMenuView = NULL;
	pCVNEDetailView = NULL;
	pCVNExpressModel = NULL;
	pCVNEPlaybackView = NULL;

	pCVNExpressModel	= new CVNExpressModel();
	pCVNEMenuView		= new CVNEMenuView();
	pCVNEDetailView		= new CVNEDetailView();
	pCVNEPlaybackView	= new CVNEPlaybackView();
	cout << "			CVNEApp::CVNEApp ==========================> Constructor SUCCESSFULL !" << endl;
}


CVNEApp::~CVNEApp()
{
	cout << "			CVNEApp::~CVNEApp ==========================> Destructor !" << endl;
	
	cout << "			CVNEApp::~CVNEApp ==========================> Destructor SUCCESSFULL !" << endl;
}

void CVNEApp::Onload()
{
	cout << "			CVNEApp::Onload ==========================> Onload 23232 !" << endl;
	pCVNEMenuView->OnLoad();
	pCVNEDetailView->OnLoad();

	pCVNEMenuView->FlipAll();
	pCVNEDetailView->FlipAll();
	pCVNEPlaybackView->FlipAll();
	pCVNEMenuView->ProcessKeyDown();
	cout << "			CVNEApp::Onload ==========================> Onload SUCCESSFULL !" << endl;
}
