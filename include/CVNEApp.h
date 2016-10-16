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
#include "CVNEListView.h"
#include "CVNEDetailView.h"
#include "CVNEPlaybackView.h"
#include "directfb.h"
#include <pthread.h>

class CFBGlobal;
class CVNEMenuView;
class CVNEListView;
class CVNExpressModel;
class CVNEDetailView;
class CVNEPlaybackView;

using namespace std;

class CVNEApp
{
	static CVNEApp  *pApp;
public:
	CVNEApp();
	~CVNEApp();
	void Onload();
	static CVNEApp   *GetInstance();
	CVNEMenuView	 *pCVNEMenuView;
	CVNEListView	 *pCVNEListView;
	CVNExpressModel	 *pCVNExpressModel;
	CVNEDetailView	 *pCVNEDetailView;
	CVNEPlaybackView *pCVNEPlaybackView;
};

#endif // !__CVNEApp_h__