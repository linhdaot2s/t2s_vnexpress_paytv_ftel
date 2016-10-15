/*
 * parseHTML.h
 *
 *  Created on: Oct 15, 2016
 *      Author: SONY
 */

#ifndef PARSEHTML_H_
#define PARSEHTML_H_

#include "FBGlobal.h"
#include <cstring>
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <vector>

#define NUM_CHARACTER_HTML 40000
#define NUM_HEIGHT_MAX 15000000
using namespace std;
struct SElementHTML
{
	bool bTagI;
	bool bTagU;
	bool bTagB;
	bool bTagImg;
	bool bTagSub;
	bool bTagSup;
	int	 iTagH;
	int  iPosition;
	string sText;
	int iWidthImage;
	int iHeightImage;
};
class ParseHTML
{
private:
public:
	ParseHTML();
	virtual ~ParseHTML();
	IDirectFBSurface * m_fb_sfText;
	IDirectFBDisplayLayer * m_fb_dlGLayer;
	IDirectFB        *m_fb_dfbG;
	IDirectFBFont* m_fb_fText;
	bool m_running;
	/////////////////////////////
	virtual int parseTextHTML(string& SText,int iWidth,int iWidthImage, int iHeightImage);
	virtual bool initAllFont(int iSize);
	virtual void DeInitAllFont();
	virtual IDirectFBFont* returnFont(SElementHTML element);
	virtual bool drawTextHTML(IDirectFBSurface* fb_sfText, DFBColor fb_clText,int iX, int iY,int iW, int iH,int iWidthImage, int iHeightImage,IDirectFBSurface* fb_sfSubDrawHTML);
	string  getStringParseHTML();
	virtual void splitTagHTML(string &sText, int &iPosition);
	virtual bool isTagHTML(string sText, string sChar);
	virtual void getImageFromHTML(string sTagImg, string *sLinkImage, int *iWidth, int *iHeight);
	virtual void replaceAll(string& str, const string& from, const string& to);
	virtual void replaceText(string& str, const string& from, const string& to, int iPos);
	virtual IDirectFBSurface* processTextHTML(string sText, DFBColor fb_clText, int iSizeFont,int iWidth, const int& iWidthImage=-1, const int& iHeightImage=-1, IDirectFBSurface* (*fb_sfSubDrawHTML)=NULL);

protected:
	CFBGlobal				*m_pGlobal;
	vector<SElementHTML> vtListText;
	int m_iIndexText;
	bool m_bIsUText;
	bool m_bIsIText;
	bool m_bIsBText;
	bool m_bIsSub;
	bool m_bIsSup;
	bool m_bIsImg;
	string m_sLinkImg;
	bool m_bIsHeader;
	int m_iTagHeader;
	int m_iWidthImage;
	int m_iHeightImage;
	string m_sTextHTML;
	IDirectFBFont           *m_fb_fTextRegular;
	IDirectFBFont           *m_fb_fTextBold;
	IDirectFBFont           *m_fb_fTextItalic;
	IDirectFBFont           *m_fb_fTextBoldItalic;
	IDirectFBFont           *m_fb_fSmallRegular;
	IDirectFBFont           *m_fb_fSmallBold;
	IDirectFBFont           *m_fb_fSmallItalic;
	IDirectFBFont           *m_fb_fSmallBoldItalic;
	IDirectFBFont           *m_fb_fTextH1;
	IDirectFBFont           *m_fb_fTextH2;
	IDirectFBFont           *m_fb_fTextH3;
	IDirectFBFont           *m_fb_fTextH4;
	IDirectFBFont           *m_fb_fTextH5;
	IDirectFBFont           *m_fb_fTextH6;
};




#endif /* PARSEHTML_H_ */
