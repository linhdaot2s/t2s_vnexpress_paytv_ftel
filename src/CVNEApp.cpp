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
	m_pLoading = CLoading::getCLoading();
	gst = new GStreamerPlayer();
	pCVNExpressModel	= new CVNExpressModel();
	pCVNEMenuView		= new CVNEMenuView();
	pCVNEListView		= new CVNEListView();
	pCVNEDetailView		= new CVNEDetailView();
	pCVNEPlaybackView	= new CVNEPlaybackView();
	cout << "			CVNEApp::CVNEApp ==========================> Constructor SUCCESSFULL !" << endl;
}
void CVNEApp::saveListItem(string sID, string sTitle)
{
	if(listSave.size() > 9)
	{
		cout << "			CVNEApp::saveListItem ==11111111111111========= "<<listSave.size() <<"   "<<sTitle <<endl;
		listSave.pop_back();
		cout << "			CVNEApp::saveListItem ==111111111111114444444444444========= "<<listSave.size();
	}
	cout << "			CVNEApp::saveListItem ==2222222222222222========="<<listSave.size() <<"   "<<sTitle <<endl;
	ListSave listsave;
	listsave.sIDItem = sID;
	listsave.sTitleItem = sTitle;
	listSave.insert(listSave.begin(),listsave);
	cout << "			CVNEApp::saveListItem ==111111111111113333333333333========= "<<listSave.size();
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
	pCVNEMenuView->ProcessKeyDown();
	cout << "			CVNEApp::Onload ==========================> Onload SUCCESSFULL !" << endl;
	
}
