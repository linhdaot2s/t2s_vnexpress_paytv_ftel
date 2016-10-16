#include "CVNEDetailView.h"

CVNEDetailView::CVNEDetailView()
{
	iWidthPageCurrent = 62;
	iWidthPageTotal = 1;

	m_sfEditedText = NULL;
	m_sfSubEditedText = NULL;
	pParseHTML = NULL;

	m_wMainView = NULL;
	m_sfMainView = NULL;

	pSize18 = NULL;
	pSize20 = NULL;
	pSize25 = NULL;
	bIsBreak = false;
	bListView = true;
	pCFBGlobal = CFBGlobal::FBSingletonGlobalInit();
	this->OnInit();
}

CVNEDetailView::~CVNEDetailView()
{
	if (m_wMainView != NULL) {
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainView !" << endl;
		pCFBGlobal->FBWindowDestroy(m_wMainView, m_sfMainView);
		m_wMainView = NULL; m_sfMainView = NULL;
		cout << "			CVNEDetailView::~CVNEDetailView ---> Destroy m_wMainView  SUCCESSFULL !" << endl;
	}
	if (pSize18 != NULL) {
		pCFBGlobal->FBFontDestroy(pSize18);
		pSize18 = NULL;
	}
	if (pSize20 != NULL) {
		pCFBGlobal->FBFontDestroy(pSize20);
		pSize20 = NULL;
	}
	if (pSize25 != NULL) {
		pCFBGlobal->FBFontDestroy(pSize25);
		pSize25 = NULL;
	}
}

bool CVNEDetailView::OnLoad(string strArticleID)
{
	printf("				CVNEDetailView::OnLoad ==============================================> OnLoad ! \n");
	pDetailItem = CVNEApp::GetInstance()->pCVNExpressModel->getDetailVNExpress(strArticleID);
	if (pDetailItem != NULL) {
		iWidthPageCurrent = 62;
		iWidthPageTotal = 1;
		return true;
	}
	else
		return false;
	printf("				CVNEDetailView::OnLoad ==============================================> OnLoad SUCCESSFULL !\n");
}

void CVNEDetailView::OnInit()
{
	printf("				CVNEDetailView::OnInit ==============================================> OnInit ! \n");
	if (m_wMainView == NULL && m_sfMainView == NULL) {
		printf("				CVNEDetailView::OnInit ---> Create WINDOW ! \n");
		pCFBGlobal->FBWindowCreateWithAlphaChannel(&m_wMainView, NULL, &m_sfMainView, list_x, list_y, list_width - 30, list_height, 0xff);
	}
		if (pSize18 == NULL)
		pCFBGlobal->FBFontCreate(&pSize18, "Roboto-Regular.ttf", 18);
	if (pSize20 == NULL)
		pCFBGlobal->FBFontCreate(&pSize20, "Roboto-Regular.ttf", 20);
	if (pSize25 == NULL)
		pCFBGlobal->FBFontCreate(&pSize25, "Roboto-Bold.ttf", 25);
	if (pParseHTML == NULL)
		pParseHTML = new ParseHTML();
	printf("				CVNEDetailView::OnInit ==============================================> OnInit SUCCESSFULL ! \n");
}

void CVNEDetailView::LoadStartup()
{
}

void CVNEDetailView::DrawFocusText()
{
	printf("				CVNEDetailView::DrawFocusText ==============================================> Draw focus text \n");
	m_sfMainView->Clear(m_sfMainView, 0x00, 0x00, 0x00, 0x00);
	if (iWidthPageTotal > 517) {
		printf("				CVNEDetailView::DrawFocusText ---> Multi text !\n");
		m_sfMainView->SetFont(m_sfMainView, pSize20);
		DFBRectangle rect = { 0, (iWidthPageCurrent - 62), 999, 510 };
		m_sfMainView->SetBlittingFlags(m_sfMainView, DSBLIT_DST_PREMULTIPLY);
		m_sfMainView->Blit(m_sfMainView, m_sfEditedText, &rect, 5, 62);

		stringstream page;
		int ipage = 0;
		if (iWidthPageTotal % 510 == 0)
			ipage = iWidthPageTotal / 510;
		else
			ipage = (iWidthPageTotal / 510) + 1;
		if (iWidthPageCurrent == 62) {
			page << "Trang 1/" << ipage;
			this->ShowUpOrDownIcon(2);
		}
		else {
			if (iWidthPageCurrent > 62 && iWidthPageCurrent < iWidthPageTotal - (iWidthPageTotal % 510)) {
				page << "Trang " << ((510 + iWidthPageCurrent) / 510) + 1 << "/" << ipage;
				this->ShowUpOrDownIcon(3);
			}
			else {
				page << "Trang " << ipage << "/" << ipage;
				this->ShowUpOrDownIcon(1);
			}
		}
		string strpage = page.str();
		pCFBGlobal->DrawText(m_sfMainView, pSize20, strpage.c_str(), VNE_BLACK, (DFBPoint) { 1000, 580 }, DSTF_TOPRIGHT);
		m_sfMainView->Flip(m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
		printf("				CVNEDetailView::DrawFocusText ---> Multi text SUCCESSFULL !\n");
	}
	else {
		printf("				CVNEDetailView::DrawFocusText ---> Only one page !\n");
		m_sfMainView->SetFont(m_sfMainView, pSize20);
		pCFBGlobal->DrawText(m_sfMainView, pSize20, "Trang 1/1", VNE_BLACK, (DFBPoint) { 1000, 580 }, DSTF_TOPRIGHT);

		DFBRectangle rect = { 0, 0, 999, 510 };
		m_sfMainView->SetBlittingFlags(m_sfMainView, DSBLIT_DST_PREMULTIPLY);
		m_sfMainView->Blit(m_sfMainView, m_sfEditedText, &rect, 5, 62);
		m_sfMainView->Flip(m_sfMainView, NULL, DSFLIP_WAITFORSYNC);
	}
	printf("				CVNEDetailView::DrawFocusText ==============================================> Draw focus text SUCCESSFULL !\n");
}

bool CVNEDetailView::ProcessKeyDown()
{
	cout << "			CVNEDetailView::ProcessKeyDown ==========================> ProcessKeyDown !" << endl;
	bIsBreak = false;
	m_wMainView->SetOpacity(m_wMainView, 255);
	while (!bIsBreak) {
		DFBInputEvent event;
		if (CFBGlobal::events->GetEvent(CFBGlobal::events, DFB_EVENT(&event)) == DFB_OK) {
			if (event.type == DIET_KEYPRESS) {
				switch (event.key_symbol) {
				case DIKS_CURSOR_LEFT: {
					cout << "			CVNEDetailView::ProcessKeyDown ---> key LEFT !" << endl;
					return false;
					break;
				}
				case DIKS_CURSOR_RIGHT: {
					cout << "			CVNEDetailView::ProcessKeyDown ---> key RIGHT !" << endl;
					CVNEApp::GetInstance()->pCVNEPlaybackView->OnLoad();
					CVNEApp::GetInstance()->pCVNEPlaybackView->ProcessKeyDown();
					break;
				}
				case DIKS_CURSOR_UP: {
					cout << "			CVNEDetailView::ProcessKeyDown ---> key UP !" << endl;
					iWidthPageCurrent -= 27;
					if (iWidthPageCurrent <= 62)
						iWidthPageCurrent = 62;
					if (iWidthPageTotal <= 510)
						iWidthPageCurrent = 62;
					this->DrawFocusText();
					break;
				}
				case DIKS_CURSOR_DOWN: {
					cout << "			CVNEDetailView::ProcessKeyDown ---> key DOWN !" << endl;
					iWidthPageCurrent += 27;
					if (iWidthPageCurrent >= (iWidthPageTotal - (iWidthPageTotal % 510)))
						iWidthPageCurrent = (iWidthPageTotal - (iWidthPageTotal % 510));
					if (iWidthPageTotal <= 510)
						iWidthPageCurrent = 62;
					this->DrawFocusText();
					break;
				}
				case DIKS_BACKSPACE: {
					cout << "			CVNEDetailView::ProcessKeyDown ---> key OK !" << endl;
					if (m_sfEditedText != NULL) {
						pCFBGlobal->FBSurfaceDestroy(m_sfEditedText);
						m_sfEditedText = NULL;
						printf("				CVNEDetailView::ProcessHTMLDetail ---> Destroy m_sfEditedText SUCCESSFULL !\n");
					}
					if (m_sfSubEditedText != NULL) {
						pCFBGlobal->FBSurfaceDestroy(m_sfSubEditedText);
						m_sfSubEditedText = NULL;
						printf("				CVNEDetailView::ProcessHTMLDetail ---> Destroy m_sfSubEditedText SUCCESSFULL !\n");
					}
					m_wMainView->SetOpacity(m_wMainView, 0);
					bIsBreak = true;
					return true;
					break;
				}
				case DIKS_AUDIO: {
					bool bCheckState = CVNEApp::GetInstance()->gst->checkState(1);
					if (bCheckState)
						CVNEApp::GetInstance()->gst->close();

					CVNEApp::GetInstance()->gst->openLinks(CVNEApp::GetInstance()->pCVNExpressModel->postGetLinkPlay(pParseHTML->getStringParseHTML(), "0").c_str());
					CVNEApp::GetInstance()->saveListItem(pDetailItem->article_id, pDetailItem->title);
					break;
				}
				case DIKS_STOP: {
					CVNEApp::GetInstance()->gst->close();
					break;
				}
				}
			}
		}
	}
	cout << "			CVNEListView::ProcessKeyDown ==========================> ProcessKeyDown SUCCESSFULL !" << endl;
}

void CVNEDetailView::ProcessHTMLDetail()
{
	printf("				CVNEDetailView::ProcessHTMLDetail ==============================================> Process detail text !\n");
	string TotalContent;
	TotalContent = "<h1>" + pDetailItem->title + "</h1> </p> <br> <i>" + pDetailItem->lead + "</i> </p>" + pDetailItem->content + "<br>";
	cout << endl<<pDetailItem->content << endl;
	if (m_sfEditedText != NULL) {
		pCFBGlobal->FBSurfaceDestroy(m_sfEditedText);
		m_sfEditedText = NULL;
		printf("				CVNEDetailView::ProcessHTMLDetail ---> Destroy m_sfEditedText SUCCESSFULL !\n");
	}
	if (m_sfSubEditedText != NULL) {
		pCFBGlobal->FBSurfaceDestroy(m_sfSubEditedText);
		m_sfSubEditedText = NULL;
		printf("				CVNEDetailView::ProcessHTMLDetail ---> Destroy m_sfSubEditedText SUCCESSFULL !\n");
	}
	m_sfEditedText = pParseHTML->processTextHTML(TotalContent, (DFBColor) { 0xff, 0x00, 0x00, 0x6 }, 20, 999, 490, 294);
	cout << endl << "TotalContent  : " << TotalContent << endl << endl;
	m_sfEditedText->GetSize(m_sfEditedText, NULL, &iWidthPageTotal);
	printf("				CVNEDetailView::ProcessHTMLDetail ==============================================> Process detail text SUCCESSFULL !\n");
}

void CVNEDetailView::ShowUpOrDownIcon(int iType)
{
	cout << "			CVNEDetailView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon !" << endl;
	switch (iType) {
	case 1: {
		pCFBGlobal->FBImageCreate(m_sfMainView, Icon_up, detail_up_icon_x, detail_up_icon_y);
		break;
	}
	case 2: {
		pCFBGlobal->FBImageCreate(m_sfMainView, Icon_down, detail_down_icon_x, detail_down_icon_y);
		break;
	}
	case 3: {
		pCFBGlobal->FBImageCreate(m_sfMainView, Icon_up, detail_up_icon_x, detail_up_icon_y);
		pCFBGlobal->FBImageCreate(m_sfMainView, Icon_down, detail_down_icon_x, detail_down_icon_y);
		break;
	}
	}
	cout << "			CVNEDetailView::ShowUpOrDownIcon ==========================> ShowUpOrDownIcon SUCCESSFULL !" << endl;
}