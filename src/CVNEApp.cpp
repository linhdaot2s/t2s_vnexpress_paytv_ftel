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
	m_pGlobal							= CFBGlobal::FBSingletonGlobalInit();
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
void CVNEApp::saveListItem(string sID, string sTitle)
{
	if(listSave.size() > 9)
	{
		cout << "			CVNEApp::saveListItem ===========";
		listSave.pop_back();
	}
	else
	{
		cout << "			CVNEApp::saveListItem ===========";
		ListSave listsave;
		listsave.sIDItem = sID;
		listsave.sTitleItem = sTitle;
		listSave.push_front(listsave);
	}
}
CVNEApp::~CVNEApp()
{
	cout << "			CVNEApp::~CVNEApp ==========================> Destructor !" << endl;
	cout << "			CVNEApp::~CVNEApp ==========================> Destructor SUCCESSFULL !" << endl;
}

void CVNEApp::Onload()
{
	cout << "			CVNEApp::Onload ==========================> Onload 23232 !" << endl;
	this->saveListItem("3465014","1Bộ xương cá voi lưng gù cá voi lưng gù  ");
	this->saveListItem("3465014","2Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","3Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","4Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","5Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","6Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","7Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","8Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","9Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","10Bộ xương cá voi lưng gù cá voi lưng gù ");
	this->saveListItem("3465014","11Bộ xương cá voi lưng gù cá voi lưng gù ");


	pCVNEPlaybackView->OnLoad();
//	pCVNEDetailView->OnLoad();
//
//	pCVNEMenuView->FlipAll();
//	pCVNEDetailView->FlipAll();
//	pCVNEPlaybackView->FlipAll();
	pCVNEPlaybackView->ProcessKeyDown();
	cout << "			CVNEApp::Onload ==========================> Onload SUCCESSFULL !" << endl;
}
