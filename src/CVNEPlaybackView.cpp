#include "CVNEPlaybackView.h"

CVNEPlaybackView::CVNEPlaybackView()
{
	cout << "			CVNEPlaybackView::CVNEPlaybackView ==========================> Constructor !" << endl;
	m_wMediaPlayer = NULL;
	m_sfMediaPlayer = NULL;
	pGlobal = CFBGlobal::FBSingletonGlobalInit();
	bIsTurnOff = false;
	m_fText18 = NULL;
	m_fText20 = NULL;
	m_detailItem = NULL;
	LinkPlay = "";
	m_PthreadPlay = 0;
	cout << "			CVNEPlaybackView::CVNEPlaybackView ==========================> Constructor SUCCESSFULL !" << endl;
}

CVNEPlaybackView::~CVNEPlaybackView()
{
	cout << "			CVNEPlaybackView::~CVNEPlaybackView ==========================> Destructor !" << endl;
	if (m_wMediaPlayer != NULL)
	{
		pGlobal->FBWindowDestroy(m_wMediaPlayer, m_sfMediaPlayer);
		m_wMediaPlayer = NULL; m_sfMediaPlayer = NULL;
	}
}

void CVNEPlaybackView::OnLoad()
{
	cout << "			CVNEPlaybackView::OnLoad =====";
	pGlobal->FBFontCreate(&m_fText18, "Roboto-Regular.ttf", 18);
	pGlobal->FBFontCreate(&m_fText20, "Roboto-Bold.ttf", 20);
	m_iFocus = 0;
	m_iOldFocus = -1;
	m_fb_clText.a = 0xff;
	m_fb_clText.r = 0x00;
	m_fb_clText.g = 0x00;
	m_fb_clText.b = 0x00;
	m_fb_clTextFocus.a = 0xff;
	m_fb_clTextFocus.r = 0x62;
	m_fb_clTextFocus.g = 0x01;
	m_fb_clTextFocus.b = 0x01;
	m_pParseHTML = new ParseHTML();
	this->OnInit();
	this->LoadStartup();
}
void CVNEPlaybackView::OnInit()
{
	cout << "			CVNEPlaybackView::OnInit ==========================> OnInit !" << endl;
	if (m_wMediaPlayer == NULL && m_sfMediaPlayer == NULL)
		pGlobal->FBWindowCreateWithAlphaChannel(&m_wMediaPlayer, NULL, &m_sfMediaPlayer, 995, 105, 285, 510, 0xff);
	if (m_wMediaPlayerData == NULL && m_sfMediaPlayerData == NULL)
		pGlobal->FBWindowCreateWithAlphaChannel(&m_wMediaPlayerData, NULL, &m_sfMediaPlayerData, 995, 105, 285, 510, 0xff);
	cout << "			CVNEPlaybackView::OnInit ==========================> OnInit SUCCESSFULL !" << endl;
}

void CVNEPlaybackView::FlipAll()
{
	cout << "			CVNEPlaybackView::FlipAll ==========================> FlipAll !" << endl;
	m_sfMediaPlayer->Flip(m_sfMediaPlayer, NULL, DSFLIP_WAITFORSYNC);
	cout << "			CVNEPlaybackView::FlipAll ==========================> FlipAll SUCCESSFULL !" << endl;
}

void CVNEPlaybackView::LoadStartup()
{
	cout << "			CVNEPlaybackView::LoadStartup ==========================> LoadStartup !" << endl;
	this->ShowPlayBar(false);
	cout << "			CVNEPlaybackView::LoadStartup ==========================> LoadStartup SUCCESSFULL !" << endl;
}
void CVNEPlaybackView::drawImageWithSurface(IDirectFBSurface *fb_sfPlayback,const char* cImage, int iX, int iY, int iW, int iH)
{
        IDirectFBSurface *fb_sfDraw = NULL;
        fb_sfDraw = pGlobal->FBImageSurfaceCreate(fb_sfDraw,cImage,iW,iH);
        DFBRectangle rec = {0,0,iW,iH};
        fb_sfPlayback->SetBlittingFlags(fb_sfPlayback, DSBLIT_BLEND_ALPHACHANNEL);
        fb_sfPlayback->Blit(fb_sfPlayback,fb_sfDraw,&rec,iX,iY);
        pGlobal->FBSurfaceDestroy(fb_sfDraw);
}
void CVNEPlaybackView::drawText(IDirectFBSurface *fb_sfPlayback, const char* cText, DFBColor fb_clText, IDirectFBFont* fb_fText, int iX, int iY, DFBSurfaceTextFlags fb_sfTFlag)
{
        fb_sfPlayback->SetFont(fb_sfPlayback, fb_fText);
        fb_sfPlayback->SetColor(fb_sfPlayback, fb_clText.r, fb_clText.g, fb_clText.b, fb_clText.a);
        fb_sfPlayback->DrawString(fb_sfPlayback, cText, -1, iX, iY, fb_sfTFlag);
}
void CVNEPlaybackView::stopPthreadAndPlay()
{
	if(CVNEApp::GetInstance()->gst->getTimePosition() > 0)
	{
		CVNEApp::GetInstance()->gst->close();
	}
}
void CVNEPlaybackView::drawTextItems(const char *pText, int iSize, int iX, int iY, IDirectFBSurface* fb_sfText, IDirectFBFont* fb_fText, DFBColor fb_clText, int iRow)
{
        int i, iRetWidth, iRetStrLength, iHeightFont, iWsfText, iHsfText, iXPosition,iYPosition;
        iRetWidth = 0;iRetStrLength = 0;iHeightFont = 0;iWsfText = 0;iHsfText = 0;iXPosition = 0;iYPosition = 0;
        const char* chRetNextLine = NULL;
        fb_sfText->GetSize(fb_sfText, &iWsfText, &iHsfText);
        fb_fText->GetHeight(fb_fText, &iHeightFont);
        for(i = 0;i<iRow && pText!=NULL;i++)
        {
                fb_fText->GetStringBreak(fb_fText, pText, -1, iSize, &iRetWidth, &iRetStrLength, &chRetNextLine);
                if (chRetNextLine == pText) chRetNextLine += iRetStrLength;
                else if (pText == NULL) iRetStrLength = -1;
                else iRetStrLength = chRetNextLine - pText;
                fb_sfText->SetFont(fb_sfText, fb_fText);
                fb_sfText->SetColor(fb_sfText, fb_clText.r, fb_clText.g, fb_clText.b, fb_clText.a);
                fb_sfText->DrawString(fb_sfText, pText, iRetStrLength, iX, iY, (DFBSurfaceTextFlags)(DSTF_TOPLEFT));
                iY += iHeightFont;
                pText = chRetNextLine;
        }

}
void CVNEPlaybackView::showFocus(int iIndex, int iOldIndex)
{
	cout<<"kienen====================="<< iIndex << "    "<< CVNEApp::GetInstance()->listSave.at(iIndex).sTitleItem << endl;
	//cout<<"kienen====================="<< iIndex << "    "<< CVNEApp::GetInstance()->listSave.at(iOldIndex).sTitleItem<< endl;
	if(iIndex != -1)
	{
		m_sfMediaPlayerData->SetColor(m_sfMediaPlayerData, 0, 0, 0, 0);
		m_sfMediaPlayerData->FillRectangle(m_sfMediaPlayerData,33, 165+(iIndex*35),235,25);
		this->drawTextItems(CVNEApp::GetInstance()->listSave.at(iIndex).sTitleItem.c_str(), 230, 33, 165+(iIndex*35), m_sfMediaPlayerData, m_fText18, m_fb_clTextFocus, 1);
	}
	if(iOldIndex != -1)
	{
		m_sfMediaPlayerData->SetColor(m_sfMediaPlayerData, 0, 0, 0, 0);
		m_sfMediaPlayerData->FillRectangle(m_sfMediaPlayerData,33, 165+(iOldIndex*35),235,25);
		this->drawTextItems(CVNEApp::GetInstance()->listSave.at(iOldIndex).sTitleItem.c_str(), 230, 33, 165+(iOldIndex*35), m_sfMediaPlayerData, m_fText18, m_fb_clText, 1);
	}
	m_sfMediaPlayerData->Flip(m_sfMediaPlayerData, NULL, DSFLIP_WAITFORSYNC);
}
void CVNEPlaybackView::ShowPlayBar(bool bIsShow)
{
	cout << "			CVNEPlaybackView::ShowPlayBar ===============1===========> ShowPlayBar !" << endl;
	if (bIsShow) {
		cout << "			CVNEPlaybackView::ShowPlayBar ---> Show playbar !" << endl;
	}
	else {
		cout << "			CVNEPlaybackView::ShowPlayBar ---> Hide playbar !" << endl;
		pGlobal->FBImageCreate(m_sfMediaPlayer, "images/playback/bg_t2s_03.png", 0, 0, 285, 510);
		this->drawText(m_sfMediaPlayerData, "Danh sách đã lưu", m_fb_clText, m_fText20, 32, 130, DSTF_TOPLEFT);
		int index = 0;
		for (vector<ListSave>::iterator it=CVNEApp::GetInstance()->listSave.begin(); it!=CVNEApp::GetInstance()->listSave.end(); ++it)
		{
			this->drawTextItems((*it).sTitleItem.c_str(), 230, 33, 165+(index*35), m_sfMediaPlayerData, m_fText18, m_fb_clText, 1);
			index++;
		}
		this->showFocus(m_iFocus, m_iOldFocus);
		m_sfMediaPlayer->Flip(m_sfMediaPlayer, NULL, DSFLIP_WAITFORSYNC);
	}
	cout << "			CVNEPlaybackView::ShowPlayBar ==========================> ShowPlayBar SUCCESSFULL !" << endl;

}
void CVNEPlaybackView::executePressEnter()
{
	fprintf(stderr," LINE==================== %d \n",__LINE__);
	CVNEApp::GetInstance()->m_pLoading->showLoading();
	if(m_detailItem)
	{
		delete[] m_detailItem;
		m_detailItem = NULL;
	}
	if(m_detailItem == NULL)
	{
		m_detailItem = CVNEApp::GetInstance()->pCVNExpressModel->getDetailVNExpress(CVNEApp::GetInstance()->listSave.at(m_iFocus).sIDItem);
	}
	m_pParseHTML->initAllFont(20);
	m_pParseHTML->parseTextHTML(m_detailItem->content,900,-1, -1);
	string sText = m_pParseHTML->getStringParseHTML();
	LinkPlay = CVNEApp::GetInstance()->pCVNExpressModel->postGetLinkPlay(sText,"0");
	if(LinkPlay != "")
	{
		CVNEApp::GetInstance()->gst->openLinks(LinkPlay.c_str());
		if(!m_PthreadPlay)
		{
			pthread_create(&m_PthreadPlay, NULL, &CVNEPlaybackView::callCreatePthreadPlay, (void*)this);
		}
	}
	CVNEApp::GetInstance()->m_pLoading->hideLoading();
}
void *CVNEPlaybackView::createPthreadPlay()
{
	if(LinkPlay != "")
		CVNEApp::GetInstance()->gst->openLinks(LinkPlay.c_str());
	return 0;
}

void *CVNEPlaybackView::callCreatePthreadPlay(void* vPlay)
{
	return ((CVNEPlaybackView*)vPlay)->createPthreadPlay();
}
void CVNEPlaybackView::ProcessKeyDown()
{
	cout << "			CVNEMenuView::ProcessKeyDown ==========================> ProcessKeyDown !" << endl;
	DFBInputEvent event;
	while (!bIsTurnOff) {
		while (CFBGlobal::events->GetEvent(CFBGlobal::events, DFB_EVENT(&event)) == DFB_OK) {
			cout << "			CVNEMenuView::ProcessKeyDown =====";
			if (event.type == DIET_KEYPRESS) {
				switch (event.key_symbol) {
				case DIKS_CURSOR_LEFT:
					cout << "			CVNEMenuView::ProcessKeyDown ---> key LEFT !" << endl;
					break;
				case DIKS_CURSOR_RIGHT:
					cout << "			CVNEMenuView::ProcessKeyDown ---> key RIGHT !" << endl;

					break;
				case DIKS_CURSOR_UP:
					cout << "			CVNEMenuView::ProcessKeyDown ---> key UP !" << endl;
					if(m_iFocus > 0)
					{
						m_iOldFocus = m_iFocus;
						m_iFocus--;
						this->showFocus(m_iFocus,m_iOldFocus);
					}
					else
					{
						m_iOldFocus = m_iFocus;
						m_iFocus = CVNEApp::GetInstance()->listSave.size() - 1;
						this->showFocus(m_iFocus,m_iOldFocus);
					}
					break;
				case DIKS_CURSOR_DOWN:
					cout << "			CVNEMenuView::ProcessKeyDown ---> key DOWN !" << m_iFocus<<"         " <<CVNEApp::GetInstance()->listSave.size() <<endl;
					if(m_iFocus < CVNEApp::GetInstance()->listSave.size()-1)
					{
						m_iOldFocus = m_iFocus;
						m_iFocus++;
						this->showFocus(m_iFocus,m_iOldFocus);
					}
					else
					{
						m_iOldFocus = m_iFocus;
						m_iFocus = 0;
						this->showFocus(m_iFocus,m_iOldFocus);
					}
					break;
				case DIKS_BACKSPACE:
					cout << "			CVNEMenuView::BACK ---> key OK !" << endl;
					break;
				case DIKS_RETURN:
					cout << "			CVNEMenuView::DIKS_RETURN ---> key OK !" << endl;
					this->executePressEnter();
					break;
				}
			}
		}
	}
	cout << "			CVNEMenuView::ProcessKeyDown ==========================> ProcessKeyDown SUCCESSFULL !" << endl;
}

