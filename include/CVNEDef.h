#ifndef __CVNEDef_h__
#define __CVNEDef_h__

#include "directfb.h"

#define Max_width   1280
#define Max_height  720

typedef struct SPosition {
	int x;
	int y;
	int w;
	int h;
} SMenuPos;

//============Define window===========
#define menu_x  0
#define menu_y  85
#define menu_width  250
#define menu_height  635

#define list_x  250
#define list_y  85
#define list_width  1030
#define list_height  635

#define detail_x  250
#define detail_y  85
#define detail_width  780
#define detail_height  635

#define media_x  1250
#define media_y  147
#define media_width  30
#define media_height 450
//=====================================

//--------------Menu position----------
static SPosition MenuLevel1def[] =
{
	//draw menu header
	/*0*/{ 0, 58, 250, 58 },
	/*1*/{ 0, 2 * 58, 250, 58 },
	/*2*/{ 0, 3 * 58, 250, 58 },
	/*3*/{ 0, 4 * 58, 250, 58 },
	/*4*/{ 0, 5 * 58, 250, 58 },
	/*5*/{ 0, 6 * 58, 250, 58 },
	/*6*/{ 0, 7 * 58, 250, 58 },
	/*7*/{ 0, 8 * 58, 250, 58 },
	/*8*/{ 0, 9 * 58, 250, 58 }
};
//------------------------------------

//--------------Menu 2 position----------
static SPosition MenuLevel2def[] =
{
	//draw menu header
	/*0*/{ 0, 60, 250, 44 },
	/*1*/{ 0, 1 * 44 + 60, 250, 44 },
	/*2*/{ 0, 2 * 44 + 60, 250, 44 },
	/*3*/{ 0, 3 * 44 + 60, 250, 44 },
	/*4*/{ 0, 4 * 44 + 60, 250, 44 },
	/*5*/{ 0, 5 * 44 + 60, 250, 44 },
	/*6*/{ 0, 6 * 44 + 60, 250, 44 },
	/*7*/{ 0, 7 * 44 + 60, 250, 44 },
	/*8*/{ 0, 8 * 44 + 60, 250, 44 }
};
//------------------------------------

//--------------Pic position----------
static SPosition Picdef[] =
{
	//draw menu header
	/*0*/{ 10, 62, 230, 180 },
	/*1*/{ 260, 62, 230, 180 },
	/*2*/{ 510, 62, 230, 180 },
	/*3*/{ 760, 62, 230, 180 },
	/*4*/{ 10, 332, 230, 180 },
	/*5*/{ 260, 332, 230, 180 },
	/*6*/{ 510, 332, 230, 180 },
	/*7*/{ 760, 332, 230, 180 }
};
//------------------------------------

//--------------Pic position----------
static SPosition TextDef[] =
{
	//draw menu header
	/*0*/{ 125, 247 },
	/*1*/{ 375, 247 },
	/*2*/{ 625, 247 },
	/*3*/{ 875, 247 },
	/*4*/{ 125, 515 },
	/*5*/{ 375, 515 },
	/*6*/{ 625, 515 },
	/*7*/{ 875, 515 }
};
//------------------------------------

//============Define icon==============
//-------Item menu------------
#define menu_item_first_x  0
#define menu_item_first_y  62

#define menu_focus_y 85

#define menu_item_width  250
#define menu_item_height  58
//----------------------------

//-------Item icon------------
#define menu_down_icon_x  94
#define menu_down_icon_y  578

#define detail_down_icon_x  469
#define detail_down_icon_y  578

#define menu_up_icon_x  94
#define menu_up_icon_y  -2

#define detail_up_icon_x  469
#define detail_up_icon_y  -2

#define down_icon_width  62
#define down_icon_height  62
//----------------------------
//=====================================

//=============Define color=============
const DFBColor VNE_WHITE = { 255, 255, 255, 255 };
const DFBColor VNE_BLACK = { 255, 0, 0, 5 };
//=====================================

//------ define logo ---------------
#define Images_startup "./images/logo/Startup.jpg"
#define Images_background "./images/logo/background.png"
//--------------------------------------

//------ define playback ---------------
#define Icon_next "./images/playback/icon-next.png"
#define Icon_disnext "./images/playback/icon-next-disable.png"
#define Icon_prev "./images/playback/icon-PREV.png"
#define Icon_disprev "./images/playback/icon-PREV-disable.png"
#define Icon_disPlay "./images/playback/icon-pause-disable.png"
#define Icon_Play "./images/playback/icon-next-disable.png"
#define Icon_Pause "./images/playback/icon-next-disable.png"
#define Icon_hide "./images/playback/hide_playbar.png"
//--------------------------------------

//------ define button ---------------
#define Icon_up "./images/button/up focus.png" 
#define Icon_down "./images/button/down focus.png" 
#define Icon_menu "./images/button/button menu.png" 
#define Icon_menufocus "./images/button/button menu focus.png"
//--------------------------------------

const int MOVE_UP = 1;
const int MOVE_DOWN = 2;
const int MOVE_NOTHING = 3;

const int MENU_LEVEL_1 = 1;
const int MENU_LEVEL_2 = 2;
const int MENU_LEVEL_3 = 3;
const int MENU_FIRST = 4;


#endif // !__CVNEDef_h__