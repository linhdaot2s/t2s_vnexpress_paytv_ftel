#ifndef __CVNEApp_h__
#define __CVNEApp_h__

#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include "CVNEDef.h"
#include "FBGlobal.h"
#include "Loading.h"
#include "VNExpressModel.h"
#include "CVNEMenuView.h"
#include "CVNEListView.h"
#include "CVNEDetailView.h"
#include "CVNEPlaybackView.h"
#include <gstplayer.h>

#include <list>

class CFBGlobal;
class CVNEMenuView;
class CVNEListView;
class CVNEDetailView;
class CVNExpressModel;
class CVNEPlaybackView;

using namespace std;


struct ListSave
{
	int size;
	string sIDItem;
	string sTitleItem;
	ListSave()
	{
		size = 0;
		sIDItem = "";
		sTitleItem = "";
	}
	~ListSave()
	{
	}
};
class CVNEApp
{

	static CVNEApp  *pApp;
public:
	CVNEApp();
	~CVNEApp();
	void Onload();
	void saveListItem(string sID, string sTitle);
	vector<ListSave> listSave;
	CFBGlobal		 *m_pGlobal;
	GStreamerPlayer *gst;
	CLoading *m_pLoading;
	static CVNEApp   *GetInstance();
	CVNEMenuView	 *pCVNEMenuView;
	CVNEListView	 *pCVNEListView;	CVNExpressModel	 *pCVNExpressModel;
	CVNEDetailView	 *pCVNEDetailView;
	CVNEPlaybackView *pCVNEPlaybackView;

};

#endif // !__CVNEApp_h__
