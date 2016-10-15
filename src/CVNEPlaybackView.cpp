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
	cout << "			CVNEPlaybackView::CVNEPlaybackView ==========================> Constructor SUCCESSFULL !" << endl;
}

CVNEPlaybackView::~CVNEPlaybackView()
{
	cout << "			CVNEPlaybackView::~CVNEPlaybackView ==========================> Destructor !" << endl;
	if (m_wMediaPlayer != NULL) {
		cout << "			CVNEPlaybackView::~CVNEPlaybackView ---> Destroy m_wMediaPlayer !" << endl;
		pGlobal->FBWindowDestroy(m_wMediaPlayer, m_sfMediaPlayer);
		m_wMediaPlayer = NULL; m_sfMediaPlayer = NULL;
		cout << "			CVNEPlaybackView::~CVNEPlaybackView ---> Destroy m_wMediaPlayer  SUCCESSFULL !" << endl;
	}
	cout << "			CVNEPlaybackView::~CVNEPlaybackView ==========================> Destructor SUCCESSFULL !" << endl;
}

void CVNEPlaybackView::OnLoad()
{
	cout << "			CVNEPlaybackView::OnLoad =====";
	pGlobal->FBFontCreate(&m_fText18, "Roboto-Regular.ttf", 18);
	pGlobal->FBFontCreate(&m_fText20, "Roboto-Bold.ttf", 20);
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
void CVNEPlaybackView::ShowPlayBar(bool bIsShow)
{
	cout << "			CVNEPlaybackView::ShowPlayBar ===============1===========> ShowPlayBar !" << endl;
	sleep(2);
	list<ListSave> listItems = CVNEApp::GetInstance()->listSave;
	cout << "			CVNEPlaybackView::ShowPlayBar ===============2===========> ShowPlayBar !" << endl;
	sleep(2);
	DFBColor fb_clText = {0xff,0,0,0};
	cout << "			CVNEPlaybackView::ShowPlayBar ===============3===========> ShowPlayBar !" << endl;

	if (bIsShow) {
		cout << "			CVNEPlaybackView::ShowPlayBar ---> Show playbar !" << endl;

	}
	else {
		cout << "			CVNEPlaybackView::ShowPlayBar ---> Hide playbar !" << endl;
		pGlobal->FBImageCreate(m_sfMediaPlayer, "images/playback/bg_t2s_03.png", 0, 0, 285, 510);
		cout << "			CVNEPlaybackView::ShowPlayBar ==========================> ShowPlayBar !" << endl;
		int index = 0;
		this->drawText(m_sfMediaPlayerData, "Danh sách đã lưu", fb_clText, m_fText20, 32, 130+(index*37), DSTF_TOPLEFT);
		for (list<ListSave>::iterator it=listItems.begin(); it!=listItems.end(); ++it)
		{
			index++;
			//this->drawText(m_sfMediaPlayerData, (*it).sTitleItem.c_str(), fb_clText, m_fText18, 33, 130+(index*35), DSTF_TOPLEFT);
			this->drawTextItems((*it).sTitleItem.c_str(), 230, 33, 130+(index*35), m_sfMediaPlayerData, m_fText18, fb_clText, 1);
		}


		m_sfMediaPlayer->Flip(m_sfMediaPlayer, NULL, DSFLIP_WAITFORSYNC);
	}
	cout << "			CVNEPlaybackView::ShowPlayBar ==========================> ShowPlayBar SUCCESSFULL !" << endl;

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
				case DIKS_CURSOR_LEFT: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key LEFT !" << endl;

					break;
				}
				case DIKS_CURSOR_RIGHT: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key RIGHT !" << endl;

					break;
				}
				case DIKS_CURSOR_UP: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key UP !" << endl;

					break;
				}
				case DIKS_CURSOR_DOWN: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key DOWN !" << endl;

					break;
				}
				case DIKS_RETURN: {
					cout << "			CVNEMenuView::ProcessKeyDown ---> key OK !" << endl;

					break;
				}
				}
			}
		}
	}
	cout << "			CVNEMenuView::ProcessKeyDown ==========================> ProcessKeyDown SUCCESSFULL !" << endl;
}
