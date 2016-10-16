#ifndef __CLOADING_H__
#define __CLOADING_H__


#include "FBGlobal.h"
#include <cstring>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <unistd.h>

class CLoading
{
private:
	IDirectFBWindow	 		*m_fb_wLoading;
	IDirectFBSurface		*m_fb_sfLoading;
	CFBGlobal 				*m_pLoadingGlobal;
	pthread_t				m_PthreadLoading;
	int 					break_show_loading;
	static CLoading    		*m_pCLoading;
public:
							CLoading();
	virtual 				~CLoading();
	void 					showLoading();
	void 					hideLoading();
	static CLoading* 		getCLoading();
	static void* 			deleteLoading();
	void 					*createPthreadLoading();
	static void 			*createPthreadLoadingMain(void* vshowLoading);
};

#endif // __CLOADING_H__
