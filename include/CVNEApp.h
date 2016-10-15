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

class CFBGlobal;
class CVNEMenuView;
class CVNEDetailView;
class CVNExpressModel;
class CVNEPlaybackView;

using namespace std;

class CVNEApp
{

	static CVNEApp  *pApp;
public:
	CVNEApp();
	~CVNEApp();
	void Onload();
	CFBGlobal		 *m_pGlobal;
	static CVNEApp   *GetInstance();
	CVNEMenuView	 *pCVNEMenuView;
	CVNExpressModel	 *pCVNExpressModel;
	CVNEDetailView	 *pCVNEDetailView;
	CVNEPlaybackView *pCVNEPlaybackView;
};

#endif // !__CVNEApp_h__