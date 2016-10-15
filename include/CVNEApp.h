#ifndef __CVNEApp_h__
#define __CVNEApp_h__

#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include "CVNEDef.h"
#include "FBGlobal.h"
#include "VNExpressModel.h"
#include "CVNEMenuView.h"
#include "CVNEDetailView.h"
#include "CVNEPlaybackView.h"
#include <list>

class CFBGlobal;
class CVNEMenuView;
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
	list<ListSave> listSave;
	CFBGlobal		 *m_pGlobal;
	static CVNEApp   *GetInstance();
	CVNEMenuView	 *pCVNEMenuView;
	CVNExpressModel	 *pCVNExpressModel;
	CVNEDetailView	 *pCVNEDetailView;
	CVNEPlaybackView *pCVNEPlaybackView;

};

#endif // !__CVNEApp_h__
