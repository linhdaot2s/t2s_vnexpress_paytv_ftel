#ifndef __CVNEApp_h__
#define __CVNEApp_h__

#include <string>
#include <iostream>
#include "CVNEDef.h"
#include "FBGlobal.h"
#include "CVNEMenuView.h"
#include "CVNEDetailView.h"
#include "CVNEPlaybackView.h"

class CVNEMenuView;
class CVNEDetailView;
class CVNEPlaybackView;

using namespace std;

class CVNEApp
{
public:
	CFBGlobal *m_pGlobal;
	CVNEApp();
	~CVNEApp();
	void Onload();
	
	CVNEMenuView	 *pCVNEMenuView;
	CVNEDetailView	 *pCVNEDetailView;
	CVNEPlaybackView *pCVNEPlaybackView;
};

#endif // !__CVNEApp_h__