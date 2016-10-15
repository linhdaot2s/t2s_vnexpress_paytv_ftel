/*
 * ParseHTML.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: SONY
 */

#include "ParseHTML.h"

ParseHTML::ParseHTML()
{
	m_pGlobal = CFBGlobal::FBSingletonGlobalInit();
	m_sTextHTML = "";
}

ParseHTML::~ParseHTML()
{

}
void ParseHTML::replaceAll(string& str, const string& from, const string& to)
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
void ParseHTML::replaceText(string& str, const string& from, const string& to, int iPos)
{
    if(from.empty())
        return;
    size_t start_pos = iPos;
    if((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
    }
}
bool ParseHTML::isTagHTML(string sText, string sChar)
{
	for(int Index=0;Index<sChar.length();Index++)
	{
		size_t found = sText.find(sChar[Index]);
		if (found!=std::string::npos)
			sText.erase(found,1);
	}
	for(int iIdx = 0;iIdx<sText.length();iIdx++)
	{
		if(sText[iIdx]!=' '&&sText[iIdx]!='<'&&sText[iIdx]!='>'&&sText[iIdx]!='/')
		{
			return false;
		}
	}
	return true;
}
void ParseHTML::getImageFromHTML(string sTagImg, string *sLinkImage, int *iWidth, int *iHeight)
{
	string sURL="",sWImg="",sHImg="";
	int iWImg=0, iHImg=0;
	//parse link image
	size_t found = sTagImg.find("http://");
	if (found!=std::string::npos)
	{
		size_t found1=sTagImg.find_first_of("\"",found+1);
		if (found1!=std::string::npos)
		{
			sURL = sTagImg.substr(found,found1-found);
		}
	}
	//parse width image
	size_t found_W = sTagImg.find("width=\"");
	if (found_W!=std::string::npos)
	{
		size_t found_W1 = sTagImg.find_first_of("\"",found_W+7);
		if (found_W1!=std::string::npos)
		{
			sWImg = sTagImg.substr(found_W+7,found_W1-(found_W+7));
		}
	}
	//parse height image
	size_t found_H = sTagImg.find("height=\"");
	if (found_W!=std::string::npos)
	{
		size_t found_H1 = sTagImg.find_first_of("\"",found_H+8);
		if (found_H1!=std::string::npos)
		{
			sHImg = sTagImg.substr(found_H+8,found_H1-(found_H+8));
		}
	}
	if(sWImg != "" && isdigit(sWImg[0]))
	{
		(*iWidth) = atoi(sWImg.c_str());
	}
	if(sHImg != "" && isdigit(sHImg[0]))
	{
		(*iHeight) = atoi(sHImg.c_str());
	}
	(*sLinkImage) = sURL;
}
void ParseHTML::splitTagHTML(string &sText, int &iPosFirst)
{
	string sStrcmp3, sStrcmp4,sStrcmp5,sStrcmp6;
	int iPosSecond = iPosFirst;
	string splitText;
	size_t found;
	m_bIsImg = false;
	while(sText[iPosSecond]!='>' && iPosSecond<sText.length())
	{
		iPosSecond++;
	}
	splitText = sText.substr(iPosFirst,iPosSecond-iPosFirst+1);
	sStrcmp3 = "";
	sStrcmp4 = "";
	sStrcmp5 = "";
	sStrcmp6 = "";

	sStrcmp3.push_back(sText[iPosFirst+1]);

	sStrcmp4.push_back(sText[iPosFirst+1]);
	sStrcmp4.push_back(sText[iPosFirst+2]);

	sStrcmp5.push_back(sText[iPosFirst+1]);
	sStrcmp5.push_back(sText[iPosFirst+2]);
	sStrcmp5.push_back(sText[iPosFirst+3]);

	sStrcmp6.push_back(sText[iPosFirst+1]);
	sStrcmp6.push_back(sText[iPosFirst+2]);
	sStrcmp6.push_back(sText[iPosFirst+3]);
	sStrcmp6.push_back(sText[iPosFirst+4]);

	if(sStrcmp3=="b")
	{
		if(sStrcmp4!="br")
		{
			m_bIsBText = true;
		}
		else
		{
			this->replaceText(sText,splitText,"\n",iPosFirst);
			iPosSecond = iPosFirst-1;
		}
	}
	else if(sStrcmp5=="img")
	{
		m_bIsImg = true;
		m_iWidthImage = 0;
		m_iHeightImage = 0;
		this->getImageFromHTML(splitText,&m_sLinkImg,&m_iWidthImage,&m_iHeightImage);
	}
	else if(sStrcmp5=="sub")
	{
		m_bIsSub = true;
	}
	else if(sStrcmp5=="sup")
	{
		m_bIsSup = true;
	}
	else if(sStrcmp3=="i")
	{
		if(sStrcmp5!="img")
			m_bIsIText = true;
	}
	else if(sStrcmp3=="u")
	{
		m_bIsUText = true;
	}
	else if(sStrcmp3=="p")
	{
		this->replaceText(sText,splitText,"\n",iPosFirst);
		iPosSecond = iPosFirst-1;
	}
	else if(sStrcmp5=="div")
	{
		if(sText[iPosFirst-1]!='\n')
		{
			this->replaceText(sText,splitText,"\n",iPosFirst);
			iPosSecond = iPosFirst-1;
		}
	}
	else if(sStrcmp4=="h1")
	{
		m_iTagHeader = 1;
		m_bIsHeader = true;
	}
	else if(sStrcmp4=="h2")
	{
		m_iTagHeader = 2;
		m_bIsHeader = true;
	}
	else if(sStrcmp4=="h3")
	{
		m_iTagHeader = 3;
		m_bIsHeader = true;
	}
	else if(sStrcmp4=="h4")
	{
		m_iTagHeader = 4;
		m_bIsHeader = true;
	}
	else if(sStrcmp4=="h5")
	{
		m_iTagHeader = 5;
		m_bIsHeader = true;
	}
	else if(sStrcmp4=="h6")
	{
		m_iTagHeader = 6;
		m_bIsHeader = true;
	}
	else if(sStrcmp5=="/h1"||sStrcmp5=="/h2"||sStrcmp5=="/h3"||sStrcmp5=="/h4"||sStrcmp5=="/h5"||sStrcmp5=="/h6")
	{
		m_iTagHeader = -1;
		m_bIsHeader = true;
	}
	else if((sStrcmp3 == "/" && (found=splitText.find("b"))!=string::npos)&&isTagHTML(splitText,"/b")==true)
	{
		m_bIsBText = false;
	}
	else if(sStrcmp3 == "/"&&(found=splitText.find("br"))!=string::npos)
	{
		this->replaceText(sText, splitText,"\n",iPosFirst);
		iPosSecond = iPosFirst-1;
	}
	else if(sStrcmp3 == "br"&&(found=splitText.find("/"))!=string::npos)
	{
		if(sStrcmp4=="br")
		{
			this->replaceText(sText, splitText,"\n",iPosFirst);
			iPosSecond = iPosFirst-1;
		}
	}
	else if((sStrcmp3 == "/" &&(found=splitText.find("i"))!=string::npos)&&isTagHTML(splitText,"/i")==true)
	{
		if((found=splitText.find("img"))==string::npos)
			m_bIsIText = false;
	}
	else if((sStrcmp3 == "/" &&(found=splitText.find("u"))!=string::npos)&&isTagHTML(splitText,"/u")==true)
	{
		m_bIsUText = false;
	}
	else if((sStrcmp3 == "/" &&(found=splitText.find("sub"))!=string::npos)&&isTagHTML(splitText,"/sub")==true)
	{
		m_bIsSub = false;
	}
	else if((sStrcmp3 == "/" &&(found=splitText.find("sup"))!=string::npos)&&isTagHTML(splitText,"/sup")==true)
	{
		m_bIsSup = false;
	}
	else if((sStrcmp3 == "/"&&(found=splitText.find("p"))!=string::npos)&&isTagHTML(splitText,"/p")==true)
	{
		this->replaceText(sText, splitText,"\n",iPosFirst);
		iPosSecond = iPosFirst-1;
	}
	else if((sStrcmp3 == "p"&&(found=splitText.find("/"))!=string::npos)&&isTagHTML(splitText,"p/")==true)
	{
		this->replaceText(sText, splitText,"\n",iPosFirst);
		iPosSecond = iPosFirst-1;
	}
	else if((sStrcmp3 == "/"&&(found=splitText.find("div"))!=string::npos)&&isTagHTML(splitText,"/div")==true)
	{
		this->replaceText(sText, splitText,"\n",iPosFirst);
		iPosSecond = iPosFirst-1;
	}
	else if((sStrcmp5 == "div"&&(found=splitText.find("/"))!=string::npos)&&isTagHTML(splitText,"div/")==true)
	{
		this->replaceText(sText, splitText,"\n",iPosFirst);
		iPosSecond = iPosFirst-1;
	}
	iPosFirst = iPosSecond;
}
int ParseHTML::parseTextHTML(string& SText,int iWidth,int iWidthImage, int iHeightImage)
{
	m_sTextHTML = "";
	IDirectFBImageProvider* fb_iProvider = NULL;
	DFBRectangle fb_rec;
	DFBSurfaceDescription fb_sfdsc;
	int iStringWidth = 0, iWidthText=0;
	int iHeightFont=0;
	int iHeightText = 0;
	m_iIndexText = 0;
	m_sLinkImg = "";
	m_fb_fTextRegular->GetHeight(m_fb_fTextRegular,&iHeightFont);
	this->replaceAll(SText, "\t","     ");
	this->replaceAll(SText, "\n","");
	this->replaceAll(SText, "\r","");
	this->replaceAll(SText, "<strong>","<b>");
	this->replaceAll(SText, "</strong>","</b>");
	this->replaceAll(SText, "&nbsp;"," ");
	for(int iIdx = 0;iIdx<SText.length()&&SText[iIdx]!='\0';iIdx++)
	{
		if(m_iIndexText<NUM_CHARACTER_HTML-1)
		{
			if(SText[iIdx]=='<')
			{
				int iTmp = iIdx;
				this->splitTagHTML(SText,iIdx);
				if(m_bIsImg == true)
				{
					iHeightText+=iHeightFont;
					SElementHTML stListTemp={m_bIsIText,m_bIsUText,m_bIsBText,m_bIsImg,m_bIsSub,m_bIsSup,m_iTagHeader,iTmp,m_sLinkImg,m_iWidthImage,m_iHeightImage};
					vtListText.push_back(stListTemp);
					DFBResult result = m_pGlobal->pDfb->CreateImageProvider( m_pGlobal->pDfb,(char*)m_sLinkImg.c_str(),&fb_iProvider);
					m_sLinkImg = "";
					if (fb_iProvider != NULL || result == DFB_OK)
					{
						fb_iProvider->GetSurfaceDescription(fb_iProvider, &fb_sfdsc);
						if(m_iWidthImage != 0 && m_iHeightImage != 0)
						{
							iHeightText += m_iHeightImage;
						}
						else if(iWidthImage ==-1 && iHeightImage == -1)
						{
							iHeightText+=fb_sfdsc.height;
						}
						else
						{
							iHeightText+= ((float)fb_sfdsc.height)*((float)iWidthImage/(float)fb_sfdsc.width);
						}
						fb_iProvider->Release(fb_iProvider);
						fb_iProvider = NULL;
					}
					iHeightText+=iHeightFont;
					iWidthText = 0;
					m_iIndexText++;
					m_bIsImg = false;
				}
			}
			else
			{
				if(m_bIsHeader == true)
				{
					m_bIsHeader = false;
					string sTextTemp="";
					sTextTemp.push_back('\n');
					SElementHTML stListTemp={m_bIsIText,m_bIsUText,m_bIsBText,m_bIsImg,m_bIsSub,m_bIsSup,m_iTagHeader,iIdx-1,sTextTemp,0,0};
					vtListText.push_back(stListTemp);
					iHeightText+=iHeightFont;
					iWidthText = 0;
					m_iIndexText++;
				}
				if(SText[iIdx]!='\n'&&SText[iIdx]!='\r')
				{
					string sCharTemp = "";
					while(SText[iIdx] != ' ' && SText[iIdx] != '<' &&SText[iIdx] != '\n' &&SText[iIdx] != '\r'&&SText[iIdx] != '\0')
					{
						sCharTemp.push_back(SText[iIdx]);
						iIdx++;
					}
					if(SText[iIdx] == ' ' || SText[iIdx] == '\0')
						sCharTemp.push_back(SText[iIdx]);
					m_sTextHTML.append(sCharTemp);
					SElementHTML stListTemp={m_bIsIText,m_bIsUText,m_bIsBText,m_bIsImg,m_bIsSub,m_bIsSup,m_iTagHeader,iIdx,sCharTemp,0,0};
					vtListText.push_back(stListTemp);
					if(SText[iIdx] == '<'||SText[iIdx] == '\n'||SText[iIdx] == '\r')
							iIdx--;
					if(m_bIsImg == false)
					{
						returnFont(stListTemp)->GetStringWidth(returnFont(stListTemp),(char*)stListTemp.sText.c_str(),-1,&iStringWidth);
						if((iWidthText+iStringWidth)>iWidth)
						{
							returnFont(stListTemp)->GetHeight(returnFont(stListTemp),&iHeightFont);
							iHeightText+=iHeightFont;
							iWidthText=iStringWidth;
						}
						else
						{
							returnFont(stListTemp)->GetHeight(returnFont(stListTemp),&iHeightFont);
							iWidthText+=iStringWidth;
						}
					}
					m_iIndexText++;
				}
				else
				{
					string sTemp="";
					sTemp.push_back(SText[iIdx]);
					SElementHTML stListTemp={m_bIsIText,m_bIsUText,m_bIsBText,m_bIsImg,m_bIsSub,m_bIsSup,m_iTagHeader,iIdx,sTemp,0,0};
					vtListText.push_back(stListTemp);
					iHeightText+=iHeightFont;
					iWidthText = 0;
					m_iIndexText++;
				}
			}
		}
	}
	string sTempChar="";
	sTempChar.push_back(' ');
	SElementHTML stListTemp={m_bIsIText,m_bIsUText,m_bIsBText,m_bIsImg,m_bIsSub,m_bIsSup,m_iTagHeader,SText.length(),sTempChar,0,0};
	vtListText.push_back(stListTemp);
	iHeightText+=iHeightFont;
	return iHeightText;
}
string ParseHTML::getStringParseHTML()
{
	return m_sTextHTML;
}
bool ParseHTML::initAllFont(int iSize)
{
	//CLOG_INFO(CORE_UI_CTEXT, "[kiennt28][FILE %s]--[FUNCTION %s]--[LINE %d] \n",__FILE__, __FUNCTION__,__LINE__);
	bool result;
	m_fb_fTextRegular = NULL;
	m_fb_fTextBold = NULL;
	m_fb_fTextItalic = NULL;
	m_fb_fTextBoldItalic = NULL;
	m_fb_fSmallRegular = NULL;
	m_fb_fSmallBold = NULL;
	m_fb_fSmallItalic = NULL;
	m_fb_fSmallBoldItalic = NULL;
	m_fb_fTextH1 = NULL;
	m_fb_fTextH2 = NULL;
	m_fb_fTextH3 = NULL;
	m_fb_fTextH4 = NULL;
	m_fb_fTextH5 = NULL;
	m_fb_fTextH6 = NULL;
	iSize = iSize*m_pGlobal->m_fScaleHeight;
	int iSizeSmall = (iSize*m_pGlobal->m_fScaleHeight)*0.83;
	result = m_pGlobal->FBFontCreate(&m_fb_fTextRegular,"Roboto-Regular.ttf",iSize);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextBold,"Roboto-Bold.ttf",iSize);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextItalic,"Roboto-Italic.ttf",iSize);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextBoldItalic,"Roboto-BoldItalic.ttf",iSize);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fSmallRegular,"Roboto-Regular.ttf",iSizeSmall);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fSmallBold,"Roboto-Bold.ttf",iSizeSmall);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fSmallItalic,"Roboto-Italic.ttf",iSizeSmall);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fSmallBoldItalic,"Roboto-BoldItalic.ttf",iSizeSmall);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextH1,"Roboto-Bold.ttf",iSize*2);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextH2,"Roboto-Bold.ttf",iSize*1.5);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextH3,"Roboto-Bold.ttf",iSize*1.17);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextH4,"Roboto-Bold.ttf",iSize);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextH5,"Roboto-Bold.ttf",iSize*0.83);
	if(result!=true)
	{
			return false;
	}
	result = m_pGlobal->FBFontCreate(&m_fb_fTextH6,"Roboto-Bold.ttf",iSize*0.67);
	if(result!=true)
	{
			return false;
	}
	return true;
}
void ParseHTML::DeInitAllFont()
{
	m_pGlobal->FBFontDestroy(m_fb_fTextRegular);
	m_pGlobal->FBFontDestroy(m_fb_fTextBold);
	m_pGlobal->FBFontDestroy(m_fb_fTextItalic);
	m_pGlobal->FBFontDestroy(m_fb_fTextBoldItalic);
	m_pGlobal->FBFontDestroy(m_fb_fSmallRegular);
	m_pGlobal->FBFontDestroy(m_fb_fSmallBold);
	m_pGlobal->FBFontDestroy(m_fb_fSmallItalic);
	m_pGlobal->FBFontDestroy(m_fb_fSmallBoldItalic);
	m_pGlobal->FBFontDestroy(m_fb_fTextH1);
	m_pGlobal->FBFontDestroy(m_fb_fTextH2);
	m_pGlobal->FBFontDestroy(m_fb_fTextH3);
	m_pGlobal->FBFontDestroy(m_fb_fTextH4);
	m_pGlobal->FBFontDestroy(m_fb_fTextH5);
	m_pGlobal->FBFontDestroy(m_fb_fTextH6);
	m_fb_fTextRegular = NULL;
	m_fb_fTextBold = NULL;
	m_fb_fTextItalic = NULL;
	m_fb_fTextBoldItalic = NULL;
	m_fb_fSmallRegular = NULL;
	m_fb_fSmallBold = NULL;
	m_fb_fSmallItalic = NULL;
	m_fb_fSmallBoldItalic = NULL;
	m_fb_fTextH1 = NULL;
	m_fb_fTextH3 = NULL;
	m_fb_fTextH4 = NULL;
	m_fb_fTextH5 = NULL;
	m_fb_fTextH6 = NULL;
}
/**
 * FUNCTION
 *      returnFont(SElementHTML element)
 * DESCRIPTION
 *      return font with tag
 * @PARAM
 *		SElementHTML element
 *
 * @RETURN none
 *
 * AUTHOR: kiennt28
 */
IDirectFBFont* ParseHTML::returnFont(SElementHTML element)
{
	if(element.iTagH == -1)
	{
		if(element.bTagB==true)
		{
			if(element.bTagI==true)
			{
				if(element.bTagSub==true||element.bTagSup==true)
					return m_fb_fSmallBoldItalic;
				else
					return m_fb_fTextBoldItalic;
			}
			else
			{
				if(element.bTagSub==true||element.bTagSup==true)
					return m_fb_fSmallBold;
				else
					return m_fb_fTextBold;
			}
		}
		else if(element.bTagI==true)
		{
			if(element.bTagSub==true||element.bTagSup==true)
				return m_fb_fSmallItalic;
			else
				return m_fb_fTextItalic;
		}
		else
		{
			if(element.bTagSub==true||element.bTagSup==true)
				return m_fb_fSmallRegular;
			else
				return m_fb_fTextRegular;
		}
	}
	else
	{
		if(element.iTagH==1)
		{
			return m_fb_fTextH1;
		}
		else if(element.iTagH==2)
		{
			return m_fb_fTextH2;
		}
		else if(element.iTagH==3)
		{
			return m_fb_fTextH3;
		}
		else if(element.iTagH==4)
		{
			return m_fb_fTextH4;
		}
		else if(element.iTagH==5)
		{
			return m_fb_fTextH5;
		}
		else if(element.iTagH==6)
		{
			return m_fb_fTextH6;
		}
		else
			return m_fb_fTextRegular;
	}
}
bool ParseHTML::drawTextHTML(IDirectFBSurface* fb_sfText, DFBColor fb_clText,int iX, int iY,int iW, int iH,int iWidthImage, int iHeightImage,IDirectFBSurface* fb_sfSubDrawHTML)
{
	IDirectFBImageProvider* fb_iProvider = NULL;
	DFBRectangle fb_rec={0,0,0,0};
	DFBSurfaceDescription fb_sfdsc;
	int iStringWidth = 0, iHeightText = 0, iXpos = iX, iYpos = iY, iWidthText=0, iHeightSurface=0;
	int iHeight = 0;
	IDirectFBSurface* fb_sfTempDraw=fb_sfText;
	m_fb_fTextRegular->GetHeight(m_fb_fTextRegular,&iHeightText);
	for (std::vector<SElementHTML>::iterator it = vtListText.begin() ; it != vtListText.end(); ++it)
	{
		if((*it).sText=="\n"||(*it).sText=="\r")
		{
			iXpos=iX;
			iYpos+=iHeightText;
			iHeightSurface+=iHeightText;
			iHeight+=iHeightText;
			iWidthText = 0;
			if((iHeightSurface*iW) > NUM_HEIGHT_MAX)
			{
				iXpos=iX;
				iYpos=iY;
				iHeightSurface = 0;
				iHeight = 0;
				iWidthText = 0;
				fb_sfTempDraw = fb_sfSubDrawHTML;
			}
		}
		else
		{
			if((*it).bTagImg == false)
			{
				fb_sfTempDraw->SetFont(fb_sfTempDraw, returnFont(*it));
				returnFont((*it))->GetStringWidth(returnFont(*it),(char*)(*it).sText.c_str(),-1,&iStringWidth);
				if((iWidthText+iStringWidth)<=iW)
				{
					returnFont(*it)->GetHeight(returnFont(*it),&iHeightText);
					fb_sfTempDraw->SetColor(fb_sfTempDraw, fb_clText.r, fb_clText.g, fb_clText.b, fb_clText.a);
					if((*it).bTagSub==true)
					{
						fb_sfTempDraw->DrawString(fb_sfTempDraw, (char*)(*it).sText.c_str(), -1, iXpos,iYpos+(iHeightText/2), (DFBSurfaceTextFlags)(DSTF_TOPLEFT));
					}
					else
					{
						fb_sfTempDraw->DrawString(fb_sfTempDraw, (char*)(*it).sText.c_str(), -1, iXpos,iYpos, (DFBSurfaceTextFlags)(DSTF_TOPLEFT));
					}
					if((*it).bTagU==true)
					{
						fb_sfTempDraw->DrawLine(fb_sfTempDraw,iXpos,iYpos,iXpos+iStringWidth,iYpos);
					}
					iXpos+=iStringWidth;
					iWidthText+=iStringWidth;
				}
				else
				{
					--it;
					iXpos=iX;
					iYpos+=iHeightText;
					iHeightSurface+=iHeightText;
					iHeight+=iHeightText;
					iWidthText = 0;
					if((iHeightSurface*iW) > NUM_HEIGHT_MAX)
					{
						iXpos=iX;
						iYpos=iY;
						iHeightSurface = 0;
						iHeight = 0;
						iWidthText = 0;
						fb_sfTempDraw = fb_sfSubDrawHTML;
					}
				}
			}
			else
			{
				iXpos=iX;
				iYpos+=iHeightText;
				iHeightSurface+=iHeightText;
				if((iHeightSurface*iW) > NUM_HEIGHT_MAX)
				{
					iXpos=iX;
					iYpos=iY;
					iHeightSurface = 0;
					iHeight = 0;
					iWidthText = 0;
					fb_sfTempDraw = fb_sfSubDrawHTML;
				}
				DFBResult result = m_pGlobal->pDfb->CreateImageProvider( m_pGlobal->pDfb,(char*)(*it).sText.c_str(),&fb_iProvider);
				if (fb_iProvider != NULL || result == DFB_OK)
				{
					fb_iProvider->GetSurfaceDescription(fb_iProvider, &fb_sfdsc);
					if((*it).iWidthImage != 0 && (*it).iHeightImage != 0)
					{
						fb_rec.w = (*it).iWidthImage;
						fb_rec.h = (*it).iHeightImage;
						fb_rec.x = iXpos+((iW - fb_sfdsc.width)/2);
						fb_rec.y = iYpos;
					}
					else if(iWidthImage ==-1 && iHeightImage == -1)
					{
						fb_rec.w = fb_sfdsc.width;
						fb_rec.h = fb_sfdsc.height;
						fb_rec.x = iXpos+((iW - fb_sfdsc.width)/2);
						fb_rec.y = iYpos;
					}
					else
					{
						fb_rec.w = iWidthImage;
						fb_rec.h = ((float)fb_sfdsc.height)*((float)iWidthImage/(float)fb_sfdsc.width);
						fb_rec.x = iXpos+((iW - iWidthImage)/2);
						fb_rec.y = iYpos;
					}
					fb_iProvider->RenderTo(fb_iProvider, fb_sfTempDraw, &fb_rec);
					fb_iProvider->Release(fb_iProvider);
					fb_iProvider = NULL;
				}
				iYpos+=fb_rec.h;
				iHeightSurface+=fb_rec.h;
				iYpos+=iHeightText;
				iHeightSurface+=iHeightText;
				iHeight+=fb_sfdsc.height;
				iWidthText = 0;
				if((iHeightSurface*iW) > NUM_HEIGHT_MAX)
				{
					iXpos=iX;
					iYpos=iY;
					iHeightSurface = 0;
					iHeight = 0;
					iWidthText = 0;
					fb_sfTempDraw = fb_sfSubDrawHTML;
				}
			}

		}
	}
	return true;
}
IDirectFBSurface* ParseHTML::processTextHTML(string sText, DFBColor fb_clText, int iSizeFont,int iWidth, const int& iWidthImage, const int& iHeightImage,IDirectFBSurface** fb_sfSubDrawHTML)
{
	IDirectFBSurface *fb_sfDrawHTML = NULL;
	DFBColor fb_clTxt = {0xff,0x00,0x00,0x05};
	int iHeightString=0, iTempStringHeight=0, iSubTempHeight=0;
	vtListText.clear();
	m_iIndexText = 0;
	m_bIsImg = false;
	m_bIsBText = false;
	m_bIsUText = false;
	m_bIsIText = false;
	m_bIsHeader = false;
	m_bIsSub = false;
	m_bIsSup = false;
	m_iTagHeader = -1;
	if(fb_clText.r == 0x00 && fb_clText.g==0x00 && fb_clText.b==0x00)
		fb_clText = fb_clTxt;
	bool bResult  = this->initAllFont(iSizeFont);
	if(bResult == true)
	{
		iHeightString = this->parseTextHTML(sText,iWidth,iWidthImage,iHeightImage);
		if((iHeightString*iWidth) > NUM_HEIGHT_MAX)
		{
			iTempStringHeight = NUM_HEIGHT_MAX/iWidth;
			bool result1 = m_pGlobal->FBSurfaceCreate(&fb_sfDrawHTML,iWidth,iTempStringHeight,(DFBSurfaceDescriptionFlags)(DSDESC_CAPS|DSDESC_WIDTH | DSDESC_HEIGHT|DSDESC_PIXELFORMAT));
			if(result1!=true)
				return NULL;
			if((iHeightString-iTempStringHeight) > NUM_HEIGHT_MAX)
				iSubTempHeight = NUM_HEIGHT_MAX;
			else
				iSubTempHeight = iHeightString-iTempStringHeight;
			bool result2 = m_pGlobal->FBSurfaceCreate(fb_sfSubDrawHTML,iWidth,iSubTempHeight,(DFBSurfaceDescriptionFlags)(DSDESC_CAPS|DSDESC_WIDTH | DSDESC_HEIGHT|DSDESC_PIXELFORMAT));
		}
		else
		{
			bool result = m_pGlobal->FBSurfaceCreate(&fb_sfDrawHTML,iWidth,iHeightString,(DFBSurfaceDescriptionFlags)(DSDESC_CAPS|DSDESC_WIDTH | DSDESC_HEIGHT|DSDESC_PIXELFORMAT));
			if(result!=true)
			{
				return NULL;
			}
		}
		if(fb_sfSubDrawHTML==NULL)
		{
			this->drawTextHTML(fb_sfDrawHTML,fb_clText,0,0,iWidth,iHeightString,iWidthImage,iHeightImage,NULL);
		}
		else
		{
			this->drawTextHTML(fb_sfDrawHTML,fb_clText,0,0,iWidth,iHeightString,iWidthImage,iHeightImage,(*fb_sfSubDrawHTML));
		}
	}
	this->DeInitAllFont();
	return fb_sfDrawHTML;
}




