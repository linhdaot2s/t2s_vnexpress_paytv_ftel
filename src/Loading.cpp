#include "Loading.h"
#include <unistd.h>

CLoading 		*CLoading::m_pCLoading = NULL;

CLoading::CLoading(){
	m_pLoadingGlobal = CFBGlobal::FBSingletonGlobalInit();
	m_PthreadLoading = NULL;
	int x_Loading, y_Loading, w_Loading, h_Loading;
	break_show_loading = 0;
	x_Loading = 640.0*m_pLoadingGlobal->m_fScaleWidth;
	y_Loading = 360.0*m_pLoadingGlobal->m_fScaleWidth;
	w_Loading = 50.0*m_pLoadingGlobal->m_fScaleWidth;
	h_Loading = 50.0*m_pLoadingGlobal->m_fScaleWidth;
	m_pLoadingGlobal->FBWindowCreateWithAlphaChannel(&m_fb_wLoading, NULL, &m_fb_sfLoading, x_Loading, y_Loading, w_Loading, h_Loading, 0xff);
	m_fb_wLoading->RaiseToTop(m_fb_wLoading);
	m_fb_sfLoading->Clear(m_fb_sfLoading, 0x00,0x00,0x00,0x00);
}
CLoading::~CLoading()
{
	m_pLoadingGlobal->FBWindowDestroy(m_fb_wLoading, m_fb_sfLoading);
	m_pLoadingGlobal = NULL;
	m_fb_wLoading = NULL;
	m_fb_sfLoading = NULL;
	m_pCLoading = NULL;
}
CLoading *CLoading::getCLoading()
{
	if(m_pCLoading == NULL){
		m_pCLoading = new CLoading();
	}
	return m_pCLoading;
}
void* CLoading::deleteLoading()
{
	if(m_pCLoading){
		delete m_pCLoading;
		m_pCLoading = NULL;
	}
	return 0;
}

void *CLoading::createPthreadLoading()
{
	char path[50];
	int i = 0;
	int x_Loading = 50.0*m_pLoadingGlobal->m_fScaleWidth;
	int y_Loading = 50.0*m_pLoadingGlobal->m_fScaleHeight;
	m_fb_wLoading->SetOpacity(m_fb_wLoading, 0xff);
	m_fb_wLoading->RaiseToTop(m_fb_wLoading);
	while(break_show_loading == 0){
		for(i = 0; i< 54 ; i++)
		{
			m_fb_wLoading->RaiseToTop(m_fb_wLoading);
			if(i < 10) sprintf(path, "images/loading/FPTLoading_0000%d.png", i);
			else if(i < 100)  sprintf(path, "images/loading/FPTLoading_000%d.png", i);
			m_pLoadingGlobal->FBImageCreate(m_fb_sfLoading,path, 0,0,x_Loading,y_Loading);
			m_fb_sfLoading->Flip( m_fb_sfLoading, NULL, DSFLIP_WAITFORSYNC);
			usleep(100000);
			if(break_show_loading != 0){break;}
		}
		usleep(100);
	}
	m_fb_sfLoading->Clear(m_fb_sfLoading, 0x00,0x00,0x00,0x00);
	m_fb_sfLoading->Flip( m_fb_sfLoading, NULL, DSFLIP_WAITFORSYNC);
	return 0;
}

void *CLoading::createPthreadLoadingMain(void* vshowLoading)
{
	return ((CLoading*)vshowLoading)->createPthreadLoading();
}

void CLoading::hideLoading()
{
    break_show_loading = 1;
    if(m_PthreadLoading)
    {
    	pthread_join(m_PthreadLoading, NULL);
    	m_PthreadLoading = NULL;
    	m_fb_wLoading->SetOpacity(m_fb_wLoading, 0x00);
    }
}
void CLoading::showLoading()
{
	if(!m_PthreadLoading)
	{
		CLoading* ninitCLoading = CLoading::getCLoading();
		break_show_loading = 0;
		pthread_create(&m_PthreadLoading, NULL, &CLoading::createPthreadLoadingMain, (void*)ninitCLoading);
	}
}
