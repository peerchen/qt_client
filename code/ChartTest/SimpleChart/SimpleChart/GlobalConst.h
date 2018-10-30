#ifndef __GLOBALCONST_H__
#define __GLOBALCONST_H__

#pragma once

//-----------------------------------------------------------------------------
//	Pre-Include Defines 
//-----------------------------------------------------------------------------
#include <afxmt.h>
#include <afxtempl.h>


//-----------------------------------------------------------------------------

#define USE_NEW_FILEDB							///< »õ FileDB »ç¿ë(Hong~ Ãß°¡)

//½ÃÀåÅ¸ÀÔ												//					2Áø¼ö	:	16Áø¼ö	: 10Áø¼ö:CodeType
#define	S_MARKETTYPE_ALL					0x0000		//						 0	:	   0	:	    0	:	0	ÀüÃ¼

#define	S_MARKETTYPE_STOCK					0x0001		//				         1	:	   1	:	    1	:	1	ÁÖ½Ä
#define	S_MARKETTYPE_INDUSTRY				0x0002		//					    10	:	   2	:	    2	:	2	¾÷Á¾
#define	S_MARKETTYPE_FUTURE					0x0004		//					   100	:	   4	:	    4	:	3	¼±¹°
#define	S_MARKETTYPE_OPTION					0x0008		//					  1000	:	   8	:	    8	:	4	¿É¼Ç

#define	S_MARKETTYPE_MEMBER					0x0010		//				    1 0000	:	  10	:	   16	:	5	È¸¿ø»ç
#define	S_MARKETTYPE_BOND					0x0020		//				   10 0000	:	  20	:	   32	:	6	Ã¤±Ç
#define	S_MARKETTYPE_EXCHANGE				0x0040		//				  100 0000	:	  40	:	   64	:	7	¿ÜÈ¯/È¯À²
#define	S_MARKETTYPE_RATE					0x0080		//				 1000 0000	:	  80	:	  128	:	8	±Ý¸®

#define	S_MARKETTYPE_PRODUCT				0x0100		//			   1 0000 0000	:	 100	:	  256	:	9	»óÇ°
#define	S_MARKETTYPE_NEWS					0x0200		//			  10 0000 0000	:	 200	:	  512	:	10	Kofex¼±¹°
#define	S_MARKETTYPE_SECURITY_OPTION		0x0400		//			 100 0000 0000	:	 400	:	 1024	:	11	ÁÖ½Ä¿É¼Ç
#define	S_MARKETTYPE_INTEREST_SWAP			0x0800		//			1000 0000 0000	:	 800	:	 2048	:	12	±Ý¸®½º¿Ò

#define	S_MARKETTYPE_THEME					0x1000		//		   1 0000 0000 0000 :	1000	:	 4096	:	13	Å×¸¶
#define	S_MARKETTYPE_MPDATA					0x2000		//		  10 0000 0000 0000	:	2000	:	 8192	:	14	User

#define	S_MARKETTYPE_MPDATA1				0x4000		//		 100 0000 0000 0000	:	4000	:	16384	:	15
#define	S_MARKETTYPE_MPDATA2				0x8000		//		1000 0000 0000 0000	:	8000	:	32768	:	16

#define	S_MARKETTYPE_MPDATA3				0xFFFF		//		1111 1111 1111 1111	:			:	65535	:	

// È¸»ç±¸ºÐ
#define	S_COMPANY_GTA						0			// GTA Â÷Æ®
#define	S_COMPANY_FXPLATFORM				1			// FX(ÀÏº»)
#define	S_COMPANY_EUGENEFUTURES				2			// À¯Áø¼±¹°
#define	S_COMPANY_ROYCEASSET				3			// ·ÎÀÌ½ºÅõÀÚÀÚ¹®


#define G_INVALID_INDEX		-1		///< Invalid Index
#define G_INVALID_SIZE		-1		///< Invalid Size
//////////////////////////////////////////////////////////////////
//	Define Const Values
#ifdef _DEBUG
//	#define G_CHART_SYSTEM_MANAGER							// [HONG...]IB¿¡¼­ Á÷Á¢ ½Ã½ºÅÛ DB¸¦ º¯°æÇÒ¶§ Ç®°í¼­ »ç¿ë
#endif
//////////////////////////////////////////////////////////////////
// ¹Ì´ÏÂ÷Æ® ÀúÀå Definition
#define G_SCRCHT_SAVE_DELIMITER				_T('#')			// È­¸é Â÷Æ® ¹öÁ¯ ±¸ºÐÀÚ
#define FS									(BYTE)0x1E		// °³º° ¿ä¼ÒÀÇ ÇÊµå¸¦ ºÐ¸®ÇÏ´Â ´ÜÀ§(Field Separator)
#define US									(BYTE)0x1F		// °³º°ÀÇ ¿ä¼Ò¸¦ ºÐ¸®ÇÏ´Â ´ÜÀ§(Unit Separator)

// È­¸é Â÷Æ® ÀúÀå ¹öÁ¯
//											MAKELONG(0, 0)	// Ã³À½ ¹öÁ¯ Ã³¸®°¡ ¾ø¾úÀ»¶§ÀÇ ±âº» ¹öÁ¯
#define	G_SCRCHT_SAVE_VERSION				MAKELONG(1, 1)	// G_LAST_SLMODE_PROPERTY¿¡¼­ MaxMinDisplay, TitleShow¸¦ Á¦°Å, 
															// ´ë½Å G_LAST_SLMODE_ALLINDEX¿¡ MaxMinDisplay, TitleShow, FloatingPoint¸¦ Ãß°¡

// È­¸é ±×·¡ÇÁ ÀúÀå ¹öÁ¯
//											MAKELONG(0, 1)	// ±×·¡ÇÁ ±âº» ¹öÁ¯
#define	G_SCRGRP_SAVE_VERSION				MAKELONG(0, 2)	// Head, Foot, Legend BarÀÇ show/hide Ãß°¡

//const double G_POSITIVEMAX					= 1E37f;				
//const double G_NEGATIVEMAX					= -1E37f;
//const float G_NOTAVAILABLE_FLOAT			= FLT_MIN;		
//const int G_NOTAVAILABLE_INT				= INT_MIN;

const int G_MAXDATASIZE						= 100000;	//ÃÖ´ë DataSize°¹¼ö - ÀÇ¹Ì°¡ ¾øÀ½
const int G_MINDATASIZE						= 3;		//ÃÖ¼Ò DataSize°¹¼ö - È®´ë¸¦ °è¼Ó ÇßÀ»¶§ ÃÖ¼Ò´ÜÀ§
const int G_INC1MONTH						= 20;		//ÇÑ´Þ Áõ°¡(DayÀÏ°æ¿ì,¾Æ´Ï¸é Count°³³ä)
const int G_INC2MONTH						= 40;		//µÎ´Þ Áõ°¡(DayÀÏ°æ¿ì,¾Æ´Ï¸é Count°³³ä)
const int G_INC3MONTH						= 60;		//¼¼´Þ Áõ°¡(DayÀÏ°æ¿ì,¾Æ´Ï¸é Count°³³ä)

const UINT	G_YAXIS_POS_LEFT				= 0;		//Current YAxis Pos
const UINT	G_YAXIS_POS_RIGHT				= 1;		//Current YAxis Pos

const int	G_FORMULA_MAX_VARSIZE			= 10;
const UINT	G_MIN_CHT_HEIGHT				= 12;//20;		//Min Chart Height
const UINT	G_MIN_CHT_WIDTH					= 60;		//Min Chart Width

//const double G_PERMIT_MINVALUE				= 1.0E-07;	//ÃÖ´ëÇã¿ëÄ¡ ÃÖ¼Ò°ª

const UINT	G_INIT_CHT_WIDTH				= 720;		//ÃÖÃÊ Â÷Æ® ³ÐÀÌ
const UINT	G_INIT_CHT_HEIGHT				= 480;		//ÃÖÃÊ Â÷Æ® ³ôÀÌ
const UINT	G_TIMER_CHTID_INQUIRY			= 2001;

const int	G_MAX_ANS_LIST_COUNT			= 15;		//Ãß¼¼¼­Wizard¿¡¼­ ÃÖ´ë Ãß¼¼¼± ¼³Á¤ °¹¼ö
//const double G_MIN_CANDLE_WIDTH				= 1.5f;		//ºÀÀ¸·Î½á ÀÎÁ¤ÇØÁÙ¼ö ÀÖ´Â ÃÖ´ë Width°ª

////////////////////////////////////////////////
// File DB¿¡ »ç¿ëÇÏ´Â ÀÌ¸§Àº ¹«Á¶°Ç 30ÀÚ·Î °íÁ¤ÇØ¾ßÇÑ´Ù ¾È±×·³
// ±âÁ¸ÀÇ Struct¿¡¼­ Hard CordingµÈ 30À» ³Ñ¾î¼±´Ù(2006.11.28 Hong~)
const int	G_DEF_DB_NAME_MAX_SIZE			= 255;		///< ±âº» File DB¸í ÃÖ´ë °¹¼ö
//const int	G_INDICATOR_DB_NAME_MAX_SIZE	= 50;		///< Indicator File DB¸í ÃÖ´ë °¹¼ö
////////////////////////////////////////////////

const int	G_FUNCTION_DB_NAME_MAX_SIZE		= 100;		///< Function File DB¸í ÃÖ´ë °¹¼ö
const int	G_FORMULA_MAX_SIZE				= 4096;		///< Formula ÃÖ´ë ¼ö½Ä 

//°è¼Ó ÀûÀÎ Event¸¦ ÇÇÇÏ±â À§ÇØ¼­ DelayTime(º° ÀÇ¹Ì ¾øÀ½)
const int	G_EVENT_DELAY_TIME_LONG			= 1000;		//1ÃÊ
const int	G_EVENT_DELAY_TIME_MID			= 500;
const int	G_EVENT_DELAY_TIME_SHORT		= 250;

const TCHAR *const G_CHART_PASSWORD			= _T("1234");
const TCHAR *const G_CHART_VERSION			= _T("1.0.0.0");

const TCHAR *const G_IBOBSERVOR_FILE		= _T("IBObserveList.inf");
const TCHAR *const G_LOGFILENAME			= _T("LogEvent.log");			//Log File Path
const TCHAR *const G_CHTPROPERTY_FILE		= _T("ChtPropertyAll.cpa");		//Chart Property File Path
const TCHAR *const G_ANSPROPERTY_FILE		= _T("AnsPropertySet.aps");		//Analysis Property File Path
const TCHAR *const G_BASICFUNCTION_FILE		= _T("BasicFunc.inf");			//Basic Function File Path
const TCHAR *const G_PRICETYPE_INFOFILE		= _T("PriceTypeInfo.inf");		//PriceType Info
const TCHAR *const G_LASTSCREEN_INFOFILE	= _T("LastScreenInfo.inf");		//¸¶Áö¸· »óÅÂ ÀúÀå/·Îµù
const TCHAR *const G_ENVIRONMENT_INFOFILE	= _T("EnvironmentInfo.inf");	//Â÷Æ®È¯°æ¼³Á¤ÆÄÀÏ
const TCHAR *const G_OPTSETTING_INFOFILE	= _T("OptSettingInfo.inf");		//ÃÖÀûÈ­¼³Á¤ÆÄÀÏ
const TCHAR *const G_OPTRESULT_INFOFILE		= _T("OptResultInfo.inf");		//ÃÖÀûÈ­¼³Á¤ÆÄÀÏ
const TCHAR *const G_OPTLOGIC_INFOFILE		= _T("Logic.inf");				//ÃÖÀûÈ­Logic¼³Á¤ÆÄÀÏ
const TCHAR *const G_OPTRESULT_HISTORYS		= _T("ResultHistory.jrh");		//ÃÖÀûÈ­°á°úHistoryÆÄÀÏ
const TCHAR *const G_OPTRESULT_SUMMARYS		= _T("ResultSummary.jrs");		//ÃÖÀûÈ­°á°úSummaryÆÄÀÏ
const TCHAR *const G_OPTRESULT_SUMMARY_REPORT = _T("ResultSummary.html");	//ÃÖÀûÈ­°á°úSummary - HtmlÆÄÀÏ
const TCHAR *const G_MENULIST_FILE			= _T("MenuList.inf");			//¸Þ´ºÆíÁý°¡´ÉÇÏµµ·Ï »çÀÌµåÀÇ ¸Þ´º¸ñ·ÏÀ» ¸ð¾Æ³õÀº È­ÀÏ
const TCHAR *const G_MENULIST_FILE_JP		= _T("MenuList_JP.inf");		//

const TCHAR *const G_PRICETYPE_ORG_INFOFILE		= _T("PriceTypeOrgInfo.inf");		//PriceType OrgInfo(ÀÏº»,ÇÑ±¹,¹Ì±¹)
const TCHAR *const G_PRICETYPE_ORG_INFOFILE_CH	= _T("PriceTypeOrgInfo_CH.inf");	//PriceType OrgInfo(Áß±¹)

const TCHAR *const G_OPTIMIZE_ALL_FILE		= _T("ALL_Logic.inf");			//ÃÖÀûÈ­¸ñ·ÏÀÌ ÀüÃ¼ µî·ÏµÈ È­ÀÏ »ý¼º

const TCHAR *const G_OPTSETTING_INFOFILE_JP	= _T("OptSettingInfoJP.inf");	//ÃÖÀûÈ­¼³Á¤ÆÄÀÏ

const TCHAR *const G_LASTENVIRONMENT_INFOFILE	= _T("LastEnvironment.inf");		//¸¶Áö¸· »óÅÂ ÀúÀå/·Îµù

const TCHAR *const G_DISPLAYMSG_INFOFILE	= _T("MsgDspEnvironmentInfo.inf");		//¸Þ½ÃÁö»óÀÚ¶ç¿ïÁö/¾È¶ç¿ïÁö¿¡´ëÇÑÁ¤º¸

const TCHAR *const G_CHARTCONFIG_INIFILE	= _T("ChartConfig.ini");		//È¯°æ¼³Á¤(³ª¶ó,È¯°æ¼³Á¤ÅÇ)

const TCHAR *const G_CHART_LIMIT_INF		= _T("ChartLimit.inf");			// Â÷Æ®±âÇÑ¼³Á¤(·ÎÀÌ½ºÂ÷Æ®¿¡¸¸ Àû¿ë...)

const TCHAR *const	G_MOVINGNETLIST_NAME	= _T("MovingAvgNet(MAN)");		//ÀÌÆò±×¹°ÁöÇ¥
const TCHAR *const	G_ZIGZAGIDX_NAME		= _T("ZigZag");					//ZigZagÁöÇ¥
const TCHAR *const	G_DEMARKIDX_NAME		= _T("Demark");					//DemarkÁöÇ¥
const TCHAR *const	G_PIVOTIDX_NAME			= _T("Pivot");
const TCHAR *const	G_ILMOKOBVIOUS_NAME		= _T("Ichimoku");
const TCHAR *const	G_PRICE_MA_NAME			= _T("Price MA");
const TCHAR *const	G_UNDERLYING_ASSET_NAME	= _T("Underlying Asset");
const TCHAR *const	G_MARKET_BASIS_NAME		= _T("Market Basis");
const TCHAR *const	G_THEORY_BASIS_NAME		= _T("Theory Basis");
const TCHAR *const	G_SPREAD_NAME			= _T("Spread");
const TCHAR *const	G_OPEN_INTEREST_NAME	= _T("Open Interest");

const TCHAR *const	G_CLOSE_NAME			= _T("Close");

//Chart
//const TCHAR *const	G_PATH_SYS_CHARTDIR		= _T("\\")_PATH_CHART_SYSTEM_(_T("Chart"));
//const TCHAR *const	G_PATH_USER_CHARTDIR	= _T("\\")_PATH_CHART_USER_(_T("Chart"));
// System
const TCHAR *const	G_PATH_SUBNAME_SYSTEM	= _T("\\SysTempl\\");
const TCHAR *const	G_PATH_SUBNAME_DATA		= _T("\\Data\\");
// User
const TCHAR *const	G_PATH_SUBNAME_OPTIMIZE	= _T("\\Optimize\\");
const TCHAR *const	G_PATH_SUBNAME_TEMPL	= _T("\\Templ\\");
const TCHAR *const	G_PATH_SUBNAME_IMAGE	= _T("\\Image\\");
const TCHAR *const	G_PATH_SUBNAME_REPORT	= _T("\\Report\\");
// User In Old System
const TCHAR *const	G_PATH_SUBNAME_USER		= _T("User\\");

const TCHAR *const	G_PATH_CONFIG_INI		= _T("\\Ini\\");


const TCHAR *const	G_CHART_PRICE_NAME		= _T("PriceChart");
const TCHAR *const	G_CHART_VOLUME_NAME		= _T("VolumeChart");

static const UINT	G_MAXMULTI_CHART_COUNT	= 16;		// ÃÖ´ë ´ÙÁß,´ÙÁßºñ±³Â÷Æ®°¹¼ö		
static const UINT	G_SELECT_MINSIZE		= 4;		// Select MinSize
static const UINT	G_SELECT_MAXSIZE		= 8;		// Select MaxSize

static const int	G_HEAD_GROUP_COL_SIZE	= 3;		
static const int	G_GRPHEADBAR_SIZE		= 14;
static const BOOL	G_CHTPROPERTY_LOADING	= TRUE;
static const int	G_XAXISHEIGHT			= 20;		//Â÷Æ® XÃà ³ôÀÌ
static const int	G_YAXISWIDTH			= 60;		//Â÷Æ® YÃà ³ÐÀÌ

static const int	G_HEADBAR_SIZE			= 26;		//Â÷Æ® »ó´ÜÀÇ HeadBar
static const int	G_FOOTBAR_SIZE			= 18;		//Â÷Æ® ÇÏ´ÜÀÇ FootBar
static const int	G_GRIDBAR_SIZE			= 100;		//Â÷Æ® GridBar Size
static const int	G_SIDETOOLBAR_SIZE		= 26;		//Â÷Æ® ºÐ¼®ToolBar Size
static const int	G_SIDEBAR_SIZE			= 165;		//Â÷Æ® ¸Þ´º¹Ù Size
static const int	G_SIDEBAR_POS			= 1;		//Â÷Æ® ¸Þ´º¹Ù Pos(¿ÞÂÊ/¿À¸¥ÂÊ)
static const int	G_SIDETOOLBAR_POS		= 1;		//Â÷Æ® ºÐ¼®µµ±¸¸Þ´º¹Ù Pos(¿ÞÂÊ/¿À¸¥ÂÊ)
static const int	G_LEGENDBAR_SIZE		= 110;		//±×·¡ÇÁ ¹ü·Ê¹Ù Size

static const int	G_MAX_ZONE_PER_CHART	= 20;		//ÃÖ´ë Â÷Æ®Zone°¹¼ö
static const int	G_MAX_VOLBAND_PER_CHART	= 20;		
static const int	G_MAX_IDX_PER_CHART		= 10;		//ÇÑ¿µ¿ª´ç ÃÖ´ë ÁöÇ¥°¹¼ö

static const int	G_KIND_SYSTEM			= 0;		///< ½Ã½ºÅÛ ÆÄÀÏ(¶Ç´Â ½Ã½ºÅÛ)
static const int	G_KIND_USER				= 1;		///< »ç¿ëÀÚ ÆÄÀÏ(¶Ç´Â »ç¿ëÀÚ)
static const int	G_KIND_SYSCHG			= 2;		///< FileDB¿¡¼­ »ç¿ë ½Ã½ºÅÛ DBÀÇ ¼Ó¼ºÀ» º¯°æÇÑ °æ¿ì ½Ã½ºÅÛº¯°æ Å¸ÀÔÀ¸·Î ÀúÀå

//static const UINT	G_MARGIN_WIDTH			= 1;		//±âº»Â÷Æ® MarginWidth - 1
//static const UINT	G_MARGIN_HEIGHT			= 1;		//±âº»Â÷Æ® MarginHeight - 1
static const UINT   G_LONGFITCH_LENGTH		= 5;		//Â÷Æ®Mainº¸Á¶¼± ±æÀÌ 
static const UINT   G_SHORTFITCH_LENGTH		= 3;		//Â÷Æ®Subº¸Á¶¼± ±æÀÌ 

static const UINT	G_MAXCHTREGION			= 20;
static const UINT	G_MAXIDXCOUNT			= 20;		//Max Index COUNT

static const UINT	G_MATH_MAXGROUPDATA		= 42;		//Math±×·¡ÇÁ ÃÖ´ë ±×·ì¼ö
static const UINT	G_MAXEXPRESSION			= 10;		//ÇÑÁöÇ¥´ç ÃÖ´ë ¼ö½Ä¼ö
static const UINT	G_MAXIBVARIABLE			= 10;		//IBÆíÁý±â¿¡¼­ ÃÖ´ë º¯¼ö ¼³Á¤
static const UINT	G_MAXIBBASELINE			= 10;		//IBÆíÁý±â¿¡¼­ ÃÖ´ë ±âÁØ¼±
static const UINT   G_POINT_TOLERANCE		= 4;		//ÁöÇ¥ Select Margin
static const UINT   G_MAXSIGNAL_COUNT		= 5000;		//ÃÖ´ë Signal°¹¼ö

static const UINT   G_COMPARE_ALIGN_VER		= 0;		///< ºñ±³Â÷Æ® Á¤·Ä¹æ½Ä(¼öÁ÷)
static const UINT   G_COMPARE_ALIGN_HOR		= 1;		///< ºñ±³Â÷Æ® Á¤·Ä¹æ½Ä(¼öÆò)

static const UINT   G_MAX_CHART_MARGIN_SIZE	= 15;
//////////////////////////////////////////////////////////////////////////
static const UINT   G_SIGNAL_EXTEND_LENGTH	= 120;		// Ö¸±êÎÄ¼þÀ©Õ¹ÊôÐÔ³¤¶È [kangyb 2010-08-04]

typedef CMap<int,int,CString,CString> G_GLOBALMAP;
///////////////////////////////////////////////////////////////////////////////////////////////
//			Main°úÀÇ ÀÏÄ¡¸¦ À§ÇØ¼­ 

//ÃÖÀûÈ­ ¼öÇà½Ã ±âº»Á¤º¸µé
typedef struct tagOPTIMIZETHREADINFO
{
	CWinThread* pThread;
	CWnd*       pParentWnd;
	CCriticalSection* pSection;
	int		    iStatus;
	CStringList	strResultList;
	DWORD		dwData;			// ResultRecordNum
	LPVOID		pSimCalc;		// CSimulationCalc
	LPVOID		pIndexList;		// CStringList
	LPVOID		pSymbolList;	// CStringList

	tagOPTIMIZETHREADINFO()
	{
		pThread		= NULL;
		pParentWnd	= NULL;
		pSection	= NULL;
		iStatus		= 0;
		dwData		= 0;
		pSimCalc	= NULL;
		pIndexList	= NULL;
		pSymbolList	= NULL;
	}
	~tagOPTIMIZETHREADINFO()
	{
	}

} ST_OPTIMIZE_THREAD_INFO,*LPST_OPTIMIZE_THREAD_INFO;

static const UINT   G_FRMTYPE_MULTI_MAX	= 8;	//Multi FrameÀÇ Â÷Æ® Count
const CString MULTIFRM_RATIO[8][8] = 
{	{_T("1.0:1.0")},
{_T("0.5:1.0"),_T("0.5:1.0")},
{_T("0.5:1.0"),_T("0.5:0.5"),_T("0.5:0.5")},
{_T("0.5:0.5"),_T("0.5:0.5"),_T("0.5:0.5"),_T("0.5:0.5")},
{_T("0.5:0.5"),_T("0.5:0.5"),_T("0.5:0.34"),_T("0.5:0.33"),_T("0.5:0.33")},
{_T("0.5:0.34"),_T("0.5:0.33"),_T("0.5:0.33"),_T("0.5:0.34"),_T("0.5:0.33"),_T("0.5:0.33")},
{_T("0.5:0.34"),_T("0.5:0.33"),_T("0.5:0.33"),_T("0.5:0.25"),_T("0.5:0.25"),_T("0.5:0.25"),_T("0.5:0.25")},
{_T("0.5:0.25"),_T("0.5:0.25"),_T("0.5:0.25"),_T("0.5:0.25"),_T("0.5:0.25"),_T("0.5:0.25"),_T("0.5:0.25"),_T("0.5:0.25")}	};
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//Â÷Æ® ³»ºÎ¿¡¼­ Åë½ÅFieldÁ¤ÀÇ
const CString G_REALTIME_CATEGORY		=	_T("KSE Stock Contract");
const CString G_FIELDNAME_OPENPRICE		=	_T("OpenPrice");
const CString G_FIELDNAME_HIGHPRICE		=	_T("HighPrice");
const CString G_FIELDNAME_LOWPRICE		=	_T("LowPrice");
const CString G_FIELDNAME_CLOSEPRICE	=	_T("ClosePrice");
const CString G_FIELDNAME_CONTRACTVOLUME=	_T("ContractVolume");
const CString G_FIELDNAME_TOTALVOLUME	=	_T("TotalVolume");
const CString G_FIELDNAME_TRADINGTREND	=	_T("TradingTrend");
const CString G_FIELDNAME_TRADINGTIME	=	_T("TradingTime");
const CString G_FIELDNAME_TRADINGDATE	=	_T("TradingDate");
const CString G_FIELDNAME_PREVCPRICE	=	_T("PrevClosePrice");
const CString G_FIELDNAME_REFERENCECPRICE=	_T("ReferencePrice"); 

const CString G_FIELDNAME_ADVANCEISSUES	=	_T("AdvanceIssues");
const CString G_FIELDNAME_DECLINEISSUES	=	_T("DeclineIssues");
const CString G_FIELDNAME_NEWHIGHISSUES	=	_T("NewHighIssues");
const CString G_FIELDNAME_NEWLOWISSUES	=	_T("NewLowIssues");

const CString G_FIELDNAME_ADVANCEVOLUME	=	_T("AdvanceVolume");
const CString G_FIELDNAME_DECLINEVOLUME	=	_T("DeclineVolume");
const CString G_FIELDNAME_ADVANCEAMOUNT	=	_T("AdvanceAmount");
const CString G_FIELDNAME_DECLINEAMOUNT	=	_T("DeclineAmount");

const CString G_FIELDNAME_VALUEINDEX	=	_T("ValueIndex");

//////////////////////////////////////////////////////////////////////////////
//ChartScreen Event Values

typedef struct tagSTChartEventMsg
{
	long	lMsg;			// Msg Á¾·ù.
	WPARAM	wParam;			// Param 1
	LPARAM	lParam;			// Param 2	

	tagSTChartEventMsg()
	{
		lMsg	= 0;
		wParam	= 0;
		lParam	= 0;
	}
	~tagSTChartEventMsg()
	{
	}

}ST_CHART_EVENT_MSG,*LPST_CHART_EVENT_MSG;

#define	MAINMENU_TAB_CNT	9	// 8 -> 9 [Vincent Chen, 10-01-26]

const CString G_MAINMENU_NAMELIST_ENG[50] = {	
		_T("Chart Types"),				//	ÀÏ¹ÝÂ÷Æ® ¼±ÅÃ	:	10800
		_T("Main Indicators"),			//	Ö÷Í¼µþ¼ÓÖ¸±ê		:	91580 [Vincent Chen, 10-01-26]
		_T("Sub Indicators"),			//	¸¨ÖúÖ¸±ê·ÖÎö	:	10801
		_T("Strategies"),				//	ÃÖÀûÈ­ ºÐ¼®		:	10802
		_T("Trading Signals"),			//	¸Å¸Å ½Ã±×³Î		:	10803
		_T("Pattern(1)"),				//	ÆÐÅÏ(1)			:	11233
		//_T("Pattern(2)"),				//	ÆÐÅÏ(2)			:	11234	>>>> No more "Pattern(2)" [Vincent Chen, 10-01-26]
		_T("Bull & Bear Ranges"),		//	°­¼¼¾à¼¼ ±¸°£	:	10804
		_T("Templates"),				//	ÅÛÇÃ¸´ ºÐ¼®		:	10806
		_T("Featured Tools"),			//	ÌØÉ«¹¤¾ßÀ¸		:	91581 [Vincent Chen, 10-01-26]
		_T(""),
};

#define	IBMENU_TAB_CNT	6

const CString G_IBMENU_NAMELIST_ENG[50] = {	
		_T("Indicators"),				//	º¸Á¶ÁöÇ¥ ºÐ¼®	:	10801
		_T("Strategies"),				//	ÃÖÀûÈ­ ºÐ¼®		:	10802
		_T("Trading Signals"),			//	¸Å¸Å ½Ã±×³Î		:	10803
		_T("Pattern(1)"),				//	ÆÐÅÏ(1)			:	11233
		_T("Bull & Bear Ranges"),		//	°­¼¼¾à¼¼ ±¸°£	:	10804
		_T("Function"),					//	ÇÔ¼ö(¿¹¾à¾î)		:	11078
		_T(""),
};

const CString G_PRCTYPE_NAMELIST_ENG[50] = {	
	/*General Chart*/
	_T("Market Chart"),					// [½ÃÈ²Â÷Æ®]		:	10352
		_T("Candlestick"),				// ºÀÂ÷Æ®			:	10227
		_T("Bar"),						// ¹ÙÂ÷Æ®			:	10202
		_T("Line"),						// ¼±Â÷Æ®			:	10275
		_T("Mountain"),					// MountainÂ÷Æ®		:	10758
		_T("Stair Chart"),				// °è´ÜÂ÷Æ®			:	10073
		_T("Trend"),					// Ãß¼¼Â÷Æ®			:	10642
		_T("Rise & Fall Mountain"),		// µî¶ô¼±Â÷Æ®		:	10165
		_T("Flow"),						// FlowÂ÷Æ®			:	10749
		_T("Price by Volume"),			// ¸Å¹°Â÷Æ®			:	10192
		_T("Equivolume"),				// EquivolumeÂ÷Æ®	:	10748
		_T("Candlevolume"),				// CandlevolumeÂ÷Æ®	:	10738
		_T("Spread"),					// ¿¬»êÂ÷Æ®			:	10387
		_T("Compression"),				// ¾ÐÃàÂ÷Æ®			:	10370
		_T("Sync. Overlap"),			// SyncOverlapÂ÷Æ®	:	10769
	/*Special Chart*/											
	_T("Special Chart"),				// [·ÖÎöÍ¼±í]		:	10232
		_T("Three Line Break"),			// ÈýÏß×ª»»Í¼±í		:	10251
		_T("Point & Figure"),			// PnFÍ¼±í			:	10763
		_T("Renko"),					// ×©ÐÎÍ¼    		:	10764
		_T("Kagi"),						// °´¼üÍ¼±í			:	10754
		_T("Swing"),					// ×ªÏòÍ¼   		:	10768
		_T("Broken Line"),				// ÕÛÏßÍ¼±í 		:	10126
		_T("Counterclockwise Curve"),	// ÄæÊ±ÇúÏßÍ¼±í 	:	10384
		_T("Multi-Market Chart"),		// ¶àÊÐ³¡ÆÚ»õÍ¼±í	:	10142
		_T("Cycle"),					// ÖÜÆÚÍ¼±í			:	10551
		_T("3D Comparison Chart"),		// ÈýÎ¬±È½ÏÍ¼		:	10033
		_T(""),
};

const CString G_SUBINDICATOR_ORG_NAMELIST_ENG[50] = {
	_T("General"),				// Á¾¸ñº¸Á¶ÁöÇ¥		:	10537
	_T("Industry"),				// ¾÷Á¾º¸Á¶ÁöÇ¥		:	10376
	_T("Volume Indicators"),	// °Å·¡·®º¸Á¶ÁöÇ¥	:	10062
	_T("Overlay"),				// ÁÖ°¡º¸Á¶ÁöÇ¥		:	10548
	_T("Market Activities"),	// ½Ã¼¼º¸Á¶ÁöÇ¥		:	10335
	_T("Derivatives"),			// ÆÄ»ýº¸Á¶ÁöÇ¥		:	10675
	_T("Market Statistics"),	// ½ÃÀåº¸Á¶ÁöÇ¥		:	10349
	_T("Investors"),			// ÅõÀÚÁÖÃ¼ÁöÇ¥		:	10667
	_T("Fundamental"),			// Àç¹«º¸Á¶ÁöÇ¥		:	10456
	_T(""),
};

#define	IBMENU_INDICATOR_CNT	6
const CString G_SUBINDICATOR_IB_NAMELIST_ENG[50] = {
	_T("General"),				// Á¾¸ñº¸Á¶ÁöÇ¥		:	10537
	_T("Industry"),				// ¾÷Á¾º¸Á¶ÁöÇ¥		:	10376
	_T("Volume Indicators"),	// °Å·¡·®º¸Á¶ÁöÇ¥	:	10062
	_T("Overlay"),				// ÁÖ°¡º¸Á¶ÁöÇ¥		:	10548
	_T(""),
};

//////////////////////////////////////////////////////////////////////////
/// ÌØÉ«¹¤¾ßÀ¸Ïà¹Ø¶¨Òå [Vincent Chen, 10-01-27]
//////////////////////////////////////////////////////////////////////////
#define FEATURED_TOOLS_TYPE_CNT		10
const CString G_FEATURED_TOOLS_TYPELIST_ENG[50] = {
	_T("Editors"),				// Í¼±í±à¼­Æ÷		:	91582 (TODO: Wordbook)
	_T("Optimizers"),			// ÓÅ»¯¹¤¾ß			:	91583 (TODO: Wordbook)
	_T(""),
};

#define FEATURED_TOOLS_ITEM_CNT		20
const CString G_FEATURED_TOOLS_ITEMLIST_ENG[50] = {
	_T("IndicatorBuilder"),				// ¼¼ÊõÖ¸±ê±à¼­Æ÷		:	10752
	_T("CandlePatternEditor"),			// À¯ÖòÍ¼±à¼­Æ÷			:	10740
	_T("IBOptExecutor"),				// ¼¼ÊõÖ¸±ê²ßÂÔÓÅ»¯¹¤¾ß	:	10624
	_T(""),
};
//////////////////////////////////////////////////////////////////////////

// ÀÏº»FX (¿ÜÇÑ) ÄµµéÇÔ¼ö Áß¿¡¼­ Á¦¿Ü½ÃÅ³ Ç×¸ñ 
const CString G_EXCEPTION_CANDLE_JP[41] = { _T("BEAR"),		   _T("BEARBTL"),	_T("BEARBTS"),	  _T("BEARSTAR"),		 _T("BEARUTL"),		
											_T("BEARUTS"), 	   _T("BULL"),	    _T("BULLBTL"),	  _T("BULLBTS"),		 _T("BULLSTAR"),
											_T("BULLUTL"),	   _T("BULLUTS"),   _T("DARKCLOUD"),  _T("DNCOUNTERATTACK"), _T("DNENGULF"),
											_T("DNHARAMI"),	   _T("DNONNECK"),  _T("UPONNECK"),	  _T("DNPIERCE"), 		 _T("DNPIERCE"),
											_T("DNSTAR"),	   _T("DNTHRUST"),  _T("DOJI"),		  _T("DSD"),			 _T("DSS"),
											_T("EVENINGSTAR"), _T("HAMMER"),	_T("HANGINGMAN"), _T("MORNINGSTAR"), 	 _T("SHOOTINGSTAR"),
											_T("THREEBEAR"),   _T("THREEBULL"),	_T("TWOCROWS"),   _T("UPCOUNTERATTACK"), _T("UPENGULF"),
											_T("UPHARAMI"),	   _T("UPONNECK"),	_T("UPPIERCE"),   _T("UPSTAR"),			 _T("UPTHRUST"),		 
											_T("WHITECLOUD")   };

// µ¥ÀÌÅ¸º¯¼ö Áß¿¡¼­ Á¦¿Ü½ÃÅ³ Ç×¸ñ 
const CString G_EXCEPTION_DATAVAR_NAME_JP[2] = {_T("V,VOLUME,°Å·¡·®"), _T("VM,VOLUMEMONEY,°Å·¡´ë±Ý") };
//// ±âº»¿¬»êÀÚ Áß¿¡¼­ Á¦¿Ü½ÃÅ³ Ç×¸ñ 
//const CString G_EXCEPTION_BASICOP_NAME_JP[0] = {	_T("") };
// ¼öÇÐ¿¬»êÇÔ¼ö Áß¿¡¼­ Á¦¿Ü½ÃÅ³ Ç×¸ñ 
const CString G_EXCEPTION_MATHOP_NAME_JP[1] = {	_T("AVER") };
// ÇÔ¼öÈ£ÃâÇÔ¼ö Áß¿¡¼­ Á¦¿Ü½ÃÅ³ Ç×¸ñ 
const CString G_EXCEPTION_FUNCALL_NAME_JP[12] = { _T("STD"),	_T("TMA,TAVG"), _T("MAX"),	_T("MIN"),	  _T("PMAX"),
												 _T("PMIN"),	_T("STRONG"),	_T("WEAK"),	_T("REGION"), _T("PERCENTAGE"),
												 _T("HAFTER"),	_T("LAFTER") };
// ÀüÃ¼±âº»ÇÔ¼ö
const CString G_EXCEPTION_FUNCTION_NAME_JP[48] = {	_T("AR(Period)"),
													_T("AROONDN(Period)"),
													_T("AROONDN(VarPrice,Period)"),
													_T("AROONUP(Period)"),
													_T("AROONUP(VarPrice,Period)"),
													_T("A_DRatio()"),
													_T("AdvanceNumber(Period)"),
													_T("BOP(Period)"),
													_T("BR(Period)"),
													_T("CMF(Period)"),
													_T("CO(Period1,Period2)"),
													_T("CV(MAPeriod,ROCPeriod)"),
													_T("DPO(Period)"),
													_T("DPO(VarPrice,Period)"),
													_T("DeclineNumber(Period)"),
													_T("DnWidthRatio(Period)"),
													_T("DnWidthRatio(VarPrice,Period)"),
													_T("EMV(Period)"),
													_T("EOM(Period)"),
													_T("ERayBear(Period)"),
													_T("ERayBear(VarPrice,Period)"),
													_T("ERayBull(Period)"),
													_T("ERayBull(VarPrice,Period)"),
													_T("ForceIndex(Period)"),
													_T("ForceIndex(VarPrice,Period)"),
													_T("MFI(Period)"),
													_T("MI(Period1,Period2)"),
													_T("McO(Period1,Period2)"),
													_T("NPL(Period)"),
													_T("NPL(VarPrice,Period)"),
													_T("RT(Period)"),
													_T("RVI(Period)"),
													_T("SONA(Period1,Period2)"),
													_T("SONA(VarPrice,Period1,Period2)"),
													_T("StdDev(Period)"),
													_T("StdDev(VarPrice,Period)"),
													//_T("TC(Period)"),
													_T("TII(Period1,Period2)"),
													_T("TII(VarPrice,Period1,Period2)"),
													_T("TR()"),
													_T("TRIS(Period1,Period2,Period3)"),
													_T("TRIS(VarPrice,Period1,Period2,Period3)"),
													_T("TSI(Period1,Period2)"),
													_T("TSI(VarPrice,Period1,Period2)"),
													_T("UpWidthRatio(Period)"),
													_T("UpWidthRatio(VarPrice,Period)"),
													_T("VHF(Period)"),
													_T("VHF(VarPrice,Period)"),
													_T("VOSC(Period1,Period2)")
													 };


// ÀÏº»FX (¿ÜÈ¯) CandlePatern Áß¿¡¼­ ÀÌ¸§ÀÌ ¹Ù²ð Ç×¸ñ 
const CString G_EXCEPTION_CP_RENAME_JP[2] = { _T("BullishGapSideBySide"), _T("BearishGapSidebySide") };

// ÀÏº»FX (¿ÜÈ¯) CandlePatern Áß¿¡¼­ »õÀÌ¸§ Ç×¸ñ 
const CString G_EXCEPTION_CP_NEWNAME_JP[2] = { _T("Side by Side White Lines"), _T("Side by Side Black Lines") };

//////////////////////////////////////////////////////////////////////////

const CString G_VOLTYPE_NAMELIST_ENG[6] = 
{
	_T("Volume Bar Chart"),					// °Å·¡BarÂ÷Æ®
	_T("Volume Line Chart"),				// °Å·¡LineÂ÷Æ®
	_T("Volume Mountain Chart"),			// °Å·¡MountainÂ÷Æ®
	_T("Volume White & Black Bar Chart"),	// °Å·¡À½¾çBarÂ÷Æ®
	_T("Price White & Black Bar Chart"),	// ÁÖ°¡À½¾çBarÂ÷Æ®
	_T("Execution Bar Chart")				// Ã¼°áBarÂ÷Æ®
};

const CString G_VOLTYPE_NAMELIST[6] = 
{
	_T("°Å·¡BarÂ÷Æ®"), _T("°Å·¡LineÂ÷Æ®"), _T("°Å·¡MountainÂ÷Æ®"), _T("°Å·¡À½¾çBarÂ÷Æ®"), _T("ÁÖ°¡À½¾çBarÂ÷Æ®"), _T("Ã¼°áBarÂ÷Æ®")
};

const int G_VOLTYPE_NAMEIDLIST[6] = 
{
	           10067,   		   10068,			   	   10069,				   10066,		  	    10549,		   10601
};

const CString G_ITEMNIND_DBNAME[7] = { _T("Open"), _T("High"), _T("Low"), _T("Close"), _T("(H + L) / 2"), _T("(H + L + C) / 3"), _T("(H + L + C * 2) / 4")};

//////////////////////////////////////////////////////////////////////////////

const int	G_MAXSYMBOLLIST	= 100;
static TCHAR* G_CPSYMBOLLIST[G_MAXSYMBOLLIST]	= { _T("¡ø(¸Å¼ö)"), _T("¨‹(¸Åµµ)"),		_T("¡Î(È¯¸Å¼ö)"),	_T("¡Ï(Àü¸Åµµ)"),	_T("¢º(ÁøÇà)"), 
_T("¢¸(ÈÄÇà)"), _T("¡«(½°)"),		_T("¡Ü(¸ØÃã)"),		_T("¡¼(½ÃÀÛ)"),		_T("¡½(³¡)"), 
_T("¢Ñ(ÂüÁ¶)"), _T("¢Ö(»ó½ÂÃßÀÌ)"), _T("¢Ù(ÇÏ¶ôÃßÀÌ)"),	_T("¦µ(¹Ù´Ú)"),		_T("¦³(ÃµÀå)"),
_T("?(ºÒÈ®½Ç)"),_T("+(Áõ°¡)"),      _T("-(°¨¼Ò)"),
_T("¨ç"),_T("¨è"),_T("¨é"),_T("¨ê"),_T("¨ë"),_T("¨ì"),_T("¨í"),_T("¨î"),_T("¨ï"),_T("¨ð"),_T(""),};

static int G_CPSYMBOLIDLIST[G_MAXSYMBOLLIST]	= { 10013, 10015, 10024, 10023, 10014, 
10016, 10012, 10017, 10005, 10006, 
10019, 10018, 10020, 10022, 10021, 
10004, 10007, 10002, 0, };

//¸Å¼ö,¸Åµµ,È¯¸Å¼ö,Àü¸Åµµ,ÁøÇà,ÈÄÇà,½°,¸ØÃã,½ÃÀÛ,³¡,ÂüÁ¶,»ó½ÂÃßÀÌ,ÇÏ¶ôÃßÀÌ,¹Ù´Ú,ÃµÁ¤,ºÒÈ®½Ç,Áõ°¡,°¨¼Ò,....¼ýÀÚµé

static TCHAR* G_CPSIGNALLIST[G_MAXSYMBOLLIST]= { _T("¡â"), _T("¡ø"), _T("¡ä"), _T("¨‹"), _T("¡Î"), _T("¡Ï"), _T("¢¹"), _T("¢º"), _T("¢·"), _T("¢¸"), 
_T("¡Û"), _T("¡Ü"), _T("¡¼"), _T("¡½"), _T("¢Ñ"), _T("¢Ð"), _T("¢Ö"), _T("¢Ù"), _T("¦µ"), _T("¦³"), 
_T("¢Á"), _T("¢Ã"), _T("¢Â"), _T("¡Þ"), _T("¡ß"), _T("¡Ý"), _T("¡à"), _T("¡á"), _T("¢Ä"), _T("¢Å"),
_T("¢»"), _T("¢¼"), _T("¢½"), _T("¢¾"), _T("¢¿"), _T("¢À"), _T("¢Í"), _T("¢Î"), _T("¢Ï"), _T("¡Ù"), _T("¡Ú"),
_T("¢Ì"), _T("¢Æ"), _T("¢Ç"), _T("¢È"), _T("¢É"), _T("¢Ê"), _T("¢Ë"), 
_T("¡ü"), _T("¡ý"), _T("¡ê"), _T("¡ë"), _T("?"),  _T("+"),  _T("-"),  _T("¡«"), 
_T("¡Ø"), _T("££"), _T("£À"), _T("¡×"),  _T("£Ü"), _T("£¤"), _T("¡Í"), _T("¡Ì"), _T("¥õ"), _T("¥È"),
_T("¨ç"), _T("¨è"), _T("¨é"), _T("¨ê"), _T("¨ë"), _T("¨ì"), _T("¨í"), _T("¨î"), _T("¨ï"), _T("¨ð"), _T("")};

static const int G_MAXRATIOCOUNT = 12;
const int	 G_OBVIOUSEQUALTIMES[30] = {0,9,17,26,33,42,52,65,76,129,172,226,-1};
const int	 G_FIBVALUELIST[30] = {1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10945,17710,28655,46365,75020,-1};

/////////////////////////////////////////////////////////////////////////
static const UINT G_INTRA_DATATYPE_MAXCOUNT = 25;
static TCHAR* G_INTRA_DATATYPE_LIST[G_INTRA_DATATYPE_MAXCOUNT]= {
	_T("10"),_T("20"),_T("30"),_T("1"),_T("2"),_T("3"),
	_T("5"),_T("10"),_T("15"),_T("20"),_T("30"),_T("60"),_T("180"),_T("")};
static int G_INTRA_DATATYPE_VALUE_LIST[G_INTRA_DATATYPE_MAXCOUNT]= {10,20,30,60,120,180,300,600,900,1200,1800,3600,10800,-1,};

static const UINT G_MAIN_INTRA_DATATYPE_MAXCOUNT = 50;
static TCHAR* G_MAIN_INTRA_DATATYPE_LIST[G_MAIN_INTRA_DATATYPE_MAXCOUNT]= {
	_T("10"),_T("20"),_T("30"),_T("1"),_T("2"),_T("3"),
	_T("4"),_T("5"),_T("6"),_T("7"),_T("8"),_T("9"),_T("10"),
	_T("15"),_T("20"),_T("30"),_T("40"),_T("50"),_T("60"),
	_T("100"),_T("120"),_T("150"),_T("180"),_T("240"),_T("480"),_T("")};

static int G_MAIN_INTRA_DATATYPE_VALUE_LIST[G_MAIN_INTRA_DATATYPE_MAXCOUNT]= {
	10,20,30,60,120,180,240,300,360,420,480,540,600,
	900,1200,1800,2400,3000,3600,6000,7200,9000,10800,14400,28800,-1,};


static const UINT G_TICK_DATATYPE_MAXCOUNT = 10;
static TCHAR* G_TICK_DATATYPE_LIST[G_TICK_DATATYPE_MAXCOUNT]= {_T("1Æ½"),_T("2Æ½"),_T("3Æ½"),_T("4Æ½"),_T("5Æ½"),_T("")};
static int G_TICK_DATATYPE_VALUE_LIST[G_TICK_DATATYPE_MAXCOUNT]= {1,2,3,4,5,-1,};

static TCHAR* G_CALC_TYPE_LIST[30] = {  _T("A")
									  , _T("AB,B")
									  , _T("ABC,B,C")
									  , _T("AB,(A+B)")
									  , _T("AB,(A-B)")
									  , _T("AB,(A+2xB)")
									  , _T("AB,(2xA+B)")
									  , _T("AB,(A+B)/2")
									  , _T("AC,(A+C)/2")
									  , _T("ABC,(B+C)/2")
									  , _T("AB,(A+B),(A-B)")
									  , _T("ABC,(A+B+C)/3")
									  , _T("User")
									  , _T("UserSetting"), _T("")};

static const int G_CALC_TYPE_LIST_COUNT = 25;

// ÀÏ¸ñ±ÕÇü ±¸¼º¸í
//const CString G_ICHIMOKU_NAME[8] = { _T("±âÁØ¼±"), _T("ÀüÈ¯¼±"), _T("ÈÄÇà½ºÆÒ"), _T("¼±Çà½ºÆÒ1"), _T("¼±Çà½ºÆÒ2"), _T("¿¹ºñ½ºÆÒ1"), _T("¿¹ºñ½ºÆÒ2"), _T("¿¹ºñ½ºÆÒ3") };
const CString G_ICHIMOKU_NAME[8] = { _T("»ù×¼Ïß"), _T("×ª»¯Ïß"), _T("ºóÐÐ¼ä¾à"), _T("Ç°ÐÐ¼ä¾à1"), _T("Ç°ÐÐ¼ä¾à2"), _T("Ô¤±¸¼ä¾à1"), _T("Ô¤±¸¼ä¾à2"), _T("Ô¤±¸¼ä¾à3") };

const int G_ICHIMOKU_ID[8] = { 11128, 11129, 11130, 11131, 11132, 11133, 11134, 11135 };

//////////////////////////////////////////////////////////////////////////////

// FileDB Section String
const TCHAR *const	G_FD_SECTION_IND_ITEM			= _T("INDICATES@ITEM_SUPPORT");			// Á¾¸ñº¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_UPJONG			= _T("INDICATES@UPJONG_SUPPORT");		// ¾÷Á¾º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_VOLUME			= _T("INDICATES@VOLUME_SUPPORT");		// °Å·¡·®º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_PRICE			= _T("INDICATES@PRICE_SUPPORT");		// ÁÖ°¡º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_STOCK			= _T("INDICATES@STOCK_SUPPORT");		// ½Ã¼¼º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_DERIVE			= _T("INDICATES@DERIVATION_SUPPORT");	// ÆÄ»ýº¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_MARKET			= _T("INDICATES@MARKET_SUPPORT");		// ½ÃÀåº¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_INVESTOR		= _T("INDICATES@INVESTOR_SUPPORT");		// ÅõÀÚÁÖÃ¼ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_FINANCIAL		= _T("INDICATES@FINANCIAL_SUPPORT");	// Àç¹«º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTION_IND_OVERLAB		= _T("INDICATES@OVERLAB_SUPPORT");		// Ãß°¡ºñ±³ÁöÇ¥
const TCHAR *const	G_FD_SECTION_OPT				= _T("OPTIMIZES");						// ÃÖÀûÈ­
const TCHAR *const	G_FD_SECTION_SIG				= _T("SIGNALS");						// ½Ã±×³Î
const TCHAR *const	G_FD_SECTION_SHOW				= _T("SHOWATS");						// ±¸°£
const TCHAR *const	G_FD_SECTION_FUN				= _T("FUNCTIONS");						// ÇÔ¼ö
const TCHAR *const	G_FD_SECTION_CP_REVERSE_BULL	= _T("REVERSE@BULLISH");				// »ó½Â¹ÝÀü
const TCHAR *const	G_FD_SECTION_CP_CONTINUE_BULL	= _T("CONTINUE@BULLISH");				// »ó½ÂÁö¼Ó
const TCHAR *const	G_FD_SECTION_CP_REVERSE_BEAR	= _T("REVERSE@BEARISH");				// ÇÏ¶ô¹ÝÀü
const TCHAR *const	G_FD_SECTION_CP_CONTINUE_BEAR	= _T("CONTINUE@BEARISH");				// ÇÏ¶ôÁö¼Ó

// FileDB Section Name
const TCHAR *const	G_FD_SECTIONNAME_IND_ITEM			= _T("Á¾¸ñº¸Á¶ÁöÇ¥");				// Á¾¸ñº¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_UPJONG			= _T("¾÷Á¾º¸Á¶ÁöÇ¥");				// ¾÷Á¾º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_VOLUME			= _T("°Å·¡·®º¸Á¶ÁöÇ¥");				// °Å·¡·®º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_PRICE			= _T("ÁÖ°¡º¸Á¶ÁöÇ¥");				// ÁÖ°¡º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_STOCK			= _T("½Ã¼¼º¸Á¶ÁöÇ¥");				// ½Ã¼¼º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_DERIVE			= _T("ÆÄ»ýº¸Á¶ÁöÇ¥");				// ÆÄ»ýº¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_MARKET			= _T("½ÃÀåº¸Á¶ÁöÇ¥");				// ½ÃÀåº¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_INVESTOR		= _T("ÅõÀÚÁÖÃ¼ÁöÇ¥");				// ÅõÀÚÁÖÃ¼ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_FINANCIAL		= _T("Àç¹«º¸Á¶ÁöÇ¥");				// Àç¹«º¸Á¶ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_IND_OVERLAB		= _T("Ãß°¡ºñ±³ÁöÇ¥");				// Ãß°¡ºñ±³ÁöÇ¥
const TCHAR *const	G_FD_SECTIONNAME_OPT				= _T("ÃÖÀûÈ­");						// ÃÖÀûÈ­
const TCHAR *const	G_FD_SECTIONNAME_SIG				= _T("½Ã±×³Î");						// ½Ã±×³Î
const TCHAR *const	G_FD_SECTIONNAME_SHOW				= _T("±¸°£");						// ±¸°£
const TCHAR *const	G_FD_SECTIONNAME_FUN				= _T("ÇÔ¼ö");						// ÇÔ¼ö
const TCHAR *const	G_FD_SECTIONNAME_CP_REVERSE_BULL	= _T("»ó½Â¹ÝÀü");					// »ó½Â¹ÝÀü
const TCHAR *const	G_FD_SECTIONNAME_CP_CONTINUE_BULL	= _T("»ó½ÂÁö¼Ó");					// »ó½ÂÁö¼Ó
const TCHAR *const	G_FD_SECTIONNAME_CP_REVERSE_BEAR	= _T("ÇÏ¶ô¹ÝÀü");					// ÇÏ¶ô¹ÝÀü
const TCHAR *const	G_FD_SECTIONNAME_CP_CONTINUE_BEAR	= _T("ÇÏ¶ôÁö¼Ó");					// ÇÏ¶ôÁö¼Ó

typedef struct tagST_CALC_REQUEST_INFO
{
	int		nCalcInfo;
	TCHAR	chCalcInfo[30];
	TCHAR	chMainStCode[30];
	TCHAR	chSub1StCode[30];
	TCHAR	chSub2StCode[30];

	TCHAR	chMainStCodeName[30];
	TCHAR	chSub1StCodeName[30];
	TCHAR	chSub2StCodeName[30];

	tagST_CALC_REQUEST_INFO()
	{
		nCalcInfo		= 0;
		*chCalcInfo		= 0x00;
		*chMainStCode	= 0x00;
		*chSub1StCode	= 0x00;
		*chSub2StCode	= 0x00;

		*chMainStCodeName	= 0x00;
		*chSub1StCodeName	= 0x00;
		*chSub2StCodeName	= 0x00;
	}
	~tagST_CALC_REQUEST_INFO()
	{
	}

} ST_CALC_REQUEST_INFO,*LPST_CALC_REQUEST_INFO;
//////////////////////////////////////////////////////////////////////////////
//Drawing Tool - Trend Type
static const UINT G_ANSTOOL_COUNT = 60;
static const UINT G_ANSTOOL_MAXCOUNT = 40;
static TCHAR* G_CPANSTOOLLIST[G_ANSTOOL_COUNT]= { 
	//Line 
	_T("[Line]Diagonal"),_T("[Line]Parallel"),_T("[Line]Equivalence"),_T("[Line]Auto"),_T("[Line]Turning"),_T("[Line]TimeCycle"), 
	//Target
	_T("[Target]Target"),_T("[Target]StopLoss"),_T("[Target]GoldLine"),_T("[Target]SilverLine"),_T("[Target]DoubleRule"),_T("[Target]TurningFan"),
	//Elliot
	_T("[Elliot]Line"),_T("[Elliot]UpArc"),_T("[Elliot]DownArc"), 
	//Draw
	_T("[Draw]Free"),_T("[Draw]Trend"),_T("[Draw]Horizontal"),_T("[Draw]Vertical"),_T("[Draw]Cross"), 
	//Fibonacci
	_T("[Fibonacci]Arc"), _T("[Fibonacci]Fan"),_T("[Fibonacci]H-Retrace"),_T("[Fibonacci]V-Retrace"),_T("[Fibonacci]TimeGoalDay"),_T("[Fibonacci]TimeZone"),
	//Gann
	_T("[Gann]Line"), _T("[Gann]Fan"),_T("[Gann]Retrace"),_T("[Gann]Grid"),
	//Analysis
	_T("[Analysis]Quardrant"), _T("[Analysis]TironeLevel"),_T("[Analysis]SpeedArc"), _T("[Analysis]SpeedFan"),_T("[Analysis]AndrewPitchFork"),
	//Diagram
	_T("[Diagram]Angle"),_T("[Diagram]Difference"),_T("[Diagram]Ellipse"),_T("[Diagram]Rectangle"),_T("[Diagram]Triangle"),_T("[Diagram]Diamond"),
	//Object
	_T("[Object]Symbol"),_T("[Object]Text"),			
	//Ilmok
	_T("[ilmok]Value"),_T("[ilmok]Time"),_T("[ilmok]TimeInterval"),_T("[ilmok]ValueInterval"),
	//Regression
	_T("[Regression]LinearRegressLine"),_T("[Regression]LinearRegressChannel"),_T("[Regression]StandardDeviation"),_T("[Regression]StandardError"),
	_T(""),
};

static TCHAR* G_CPANSTOOLLIST_LOCAL[G_ANSTOOL_COUNT]= { 
	//Line 
	_T("11156.91601"),_T("11156.91602"),_T("11156.91603"),_T("11156.91604"),_T("11156.91605"),_T("11156.91606"), 
	//Target
	_T("11159.91607"),_T("11159.91608"),_T("11159.91609"),_T("11159.91610"),_T("11159.91611"),_T("11159.91612"),
	//Elliot
	_T("11152.91613"),_T("11152.91614"),_T("11152.91615"), 
	//Draw
	_T("11151.91616"),_T("11151.91617"),_T("11151.91618"),_T("11151.91619"),_T("11151.91620"), 
	//Fibonacci
	_T("11153.91621"), _T("11153.91622"),_T("11153.91623"),_T("11153.91624"),_T("11153.91625"),_T("11153.91626"),
	//Gann
	_T("11154.91627"), _T("11154.91628"),_T("11154.91629"),_T("11154.91630"),
	//Analysis
	_T("11149.91631"), _T("11149.91632"),_T("11149.91633"), _T("11149.91634"),_T("11149.91635"),
	//Diagram
	_T("11150.91637"),_T("11150.91638"),_T("11150.91639"),_T("11150.91640"),_T("11150.91641"),_T("11150.91642"),
	//Object
	_T("11157.91643"),_T("11157.91644"),			
	//Ilmok
	_T("11155.91645"),_T("11157.91646"),_T("11157.91647"),_T("11157.91648"),
	//Regression
	_T("11158.91649"),_T("11158.91650"),_T("11158.91651"),_T("11158.91652"),
	_T(""),
};

static TCHAR* G_CPANSTOOLLIST_JP[G_ANSTOOL_COUNT]= { 
	//Line 
	_T("[Line]Diagonal"),_T("[Line]Parallel"),_T("[Line]Equivalence"),_T("[Line]Auto"),_T("[Line]Turning"),_T("[Line]TimeCycle"), 
		//Target
		_T("[Target]Target"),_T("[Target]StopLoss"),_T("[Target]GoldLine"),_T("[Target]SilverLine"),_T("[Target]DoubleRule"),_T("[Target]TurningFan"),
		//Elliot
		_T("[Elliot]Line"),_T("[Elliot]UpArc"),_T("[Elliot]DownArc"), 
		//Draw
		_T("[Draw]Free"),_T("[Draw]Trend"),_T("[Draw]Horizontal"),_T("[Draw]Vertical"),_T("[Draw]Cross"), 
		//Fibonacci
		_T("[Fibonacci]Arc"), _T("[Fibonacci]Fan"),_T("[Fibonacci]H-Retrace"),_T("[Fibonacci]V-Retrace"),_T("[Fibonacci]TimeGoalDay"),_T("[Fibonacci]TimeZone"),
		//Gann
		_T("[Gann]Line"), _T("[Gann]Fan"),_T("[Gann]Retrace"),_T("[Gann]Grid"),
		//Analysis
		_T("[Analysis]Quardrant"), _T("[Analysis]TironeLevel"),_T("[Analysis]SpeedArc"), _T("[Analysis]SpeedFan"),_T("[Analysis]AndrewPitchFork"),
		//Diagram
		_T("[Diagram]Angle"),_T("[Diagram]Difference"),_T("[Diagram]Ellipse"),_T("[Diagram]Rectangle"),_T("[Diagram]Triangle"),_T("[Diagram]Diamond"),
		//Object
		_T("[Object]Symbol"),_T("[Object]Text"),			
		//Ilmok
		_T("[Ichimoku]Value"),_T("[Ichimoku]Time"),_T("[Ichimoku]TimeInterval"),_T("[Ichimoku]ValueInterval"),
		//Regression
		_T("[Regression]LinearRegressLine"),_T("[Regression]LinearRegressChannel"),_T("[Regression]StandardDeviation"),_T("[Regression]StandardError"),
		_T(""),
};

enum EnANSToolType										// Ans Tool Type
{
	G_ANSTYPE_ARROW						= 0,			// Not Selected Ans

	/////////////////////////////////////////////////////
	G_ANSTYPE_DIAGONAL					= 1,		
	G_ANSTYPE_PARALLEL					= 2,            //Æ½ÐÐÏß
	G_ANSTYPE_EQUIVALENCE				= 3,			//µÈ¼ÛÏß
	G_ANSTYPE_AUTOTREND					= 4,			//×Ô¶¯»­Ç÷ÊÆÏß
	G_ANSTYPE_TURNINGLINE				= 5,            //Á¬ÐøÕÛÏß
	G_ANSTYPE_TIMECYCLE					= 6,            //Ê±¼äÖÜÆÚÏß£¨ÊúÏßÖÐ¼ä¼ÓºÜ¶àÔ²£©
	/////////////////////////////////////////////////////
	G_ANSTYPE_TARGETLINE				= 7,            //Ä¿±êÏß£¨»­¼¸¸ùÆ½ÐÐµÄºáÏß£©
	G_ANSTYPE_STOPLOSSLINE				= 8,            //Ö¹ËðÏß£¨»­¼¸¸ùÆ½ÐÐµÄºáÏß£©
	G_ANSTYPE_GOLDENRULE				= 9,            //»Æ½ð·Ö¸îÏß£¨´øÀËµÄÆ½ÐÐÏß£©
	G_ANSTYPE_SILVERRULE				= 10,           //Ç¿Á¦Ö§³Å(Êó±êµãÈý¸öµã£¬»­¶à¸ùÆ½ÐÐºáÏß×÷ÎªÖ§³ÅÏß)
	G_ANSTYPE_DOUBLERULE				= 11,           //Ë«Ö§³Å(Êó±êµãÈý¸öµã£¬»­¶à¸ùÆ½ÐÐºáÏß×÷ÎªÖ§³ÅÏß)
	G_ANSTYPE_TURNINGFAN				= 12,           //·­×ªÉ¡£¨À©É¢µÄÉ¡ÐÎÏß£©
	/////////////////////////////////////////////////////
	G_ANSTYPE_ELLIOTWAVELINE			= 13,           //°¬ÂÔÌØ²¨ÀËÏß
	G_ANSTYPE_ELLIOTWAVEARCUP			= 14,           //°¬ÂÔÌØÏòÉÏÇ÷ÊÆÏß
	G_ANSTYPE_ELLIOTWAVEARCDOWN			= 15,           //°¬ÂÔÌØÏòÏÂÇ÷ÊÆÏß
	/////////////////////////////////////////////////////
	G_ANSTYPE_FREELINE					= 16,           //×ÔÓÉ»æÖÆÏß
	G_ANSTYPE_TRENDLINE					= 17,			//Ç÷ÊÆÏß£¨×Ô¼º»æÖÆÖ±Ïß£©
	G_ANSTYPE_HORIZONTAL				= 18,			//»­Ë®Æ½Ïß
	G_ANSTYPE_VERTICAL					= 19,			//»­´¹Ö±Ïß
	G_ANSTYPE_CROSS						= 20,			//»­Ê®×Ö½»²æÏß
	/////////////////////////////////////////////////////
	G_ANSTYPE_FIBARC					= 21,           //ì³²¨À­Æõ »¡Ïß
	G_ANSTYPE_FIBFAN					= 22,			//ì³²¨À­Æõ É¡ÐÎÏß
	G_ANSTYPE_FIBRETRACEMENT			= 23,			//ì³²¨À­Æõ Ë®Æ½»Ø¹éÏß
	G_ANSTYPE_FIBVERTICALRET			= 24,			//ì³²¨À­Æõ ´¹Ö±»Ø¹éÏß
	G_ANSTYPE_FIBTIMEGOALDAY			= 25,			//ì³²¨À­Æõ Ê±¼äÄ¿±êÈÕÏß
	G_ANSTYPE_FIBTIMEZONES				= 26,			//ì³²¨À­Æõ Ê±¼ä´°Ïß
	/////////////////////////////////////////////////////
	G_ANSTYPE_GANNLINE					= 27,           //½­¶÷½Ç¶ÈÏß
	G_ANSTYPE_GANNFAN					= 28,			//½­¶÷Ïß
	G_ANSTYPE_GANNRETRACEMENT			= 29,			//½­¶÷»Ø¹é
	G_ANSTYPE_GANNGRID					= 30,			//½­¶÷ÍøÂç
	/////////////////////////·ÖÎö////////////////////////
	G_ANSTYPE_QUADRANTLINE				= 31,
	G_ANSTYPE_TIRONELEVELS				= 32,
	G_ANSTYPE_SPEEDRESISTANCEARC		= 33,
	G_ANSTYPE_SPEEDRESISTANCEFAN		= 34,
	G_ANSTYPE_ANDREWPITCHFORK			= 35,
	//////////////////////////Í¼±í/////////////////////////
	G_ANSTYPE_ANGLE						= 36,           //½Ç¶È
	G_ANSTYPE_DIFFER					= 37,           //Èý½ÇÐÎ
	G_ANSTYPE_ELLIPSE					= 38,           //ÍÖÔ²
	G_ANSTYPE_RECTANGLE					= 39,           //¾ØÐÎ
	G_ANSTYPE_TRIANGLE					= 40,			//Èý½ÇÐÎ
	G_ANSTYPE_DIAMOND					= 41,	        //ÁâÐÎ
	/////////////////////////////////////////////////////
	G_ANSTYPE_SYMBOL					= 42,			//±êÊ¶¶ÔÏó
	G_ANSTYPE_TEXT						= 43,			//ÎÄ±¾
	//////////////////////////°¬Ä¬¿Ë///////////////////////////	
	G_ANSTYPE_OBVIOUSEQUALVALUE			= 44,	        //¼ÛÖµ
	G_ANSTYPE_OBVIOUSEQUALTIME			= 45,	        //Ê±¼ä
	G_ANSTYPE_TIMEINTERVAL				= 46,			//Ê±¼äÇø¼ä
	G_ANSTYPE_VALUEINTERVAL				= 47,			//¼ÛÖµÇø¼ä
	/////////////////////////////////////////////////////
	G_ANSTYPE_LINEARREGRESSION			= 48,			//ÏßÐÔ»Ø¹é
	G_ANSTYPE_RAFFREGRESSION			= 49,			//»Ø¹éÍ¨µÀ
	G_ANSTYPE_STANDARDDEVIATION			= 50,			//±ê×¼Æ«²î
	G_ANSTYPE_STANDARDERROR				= 51,			//±ê×¼Îó²î
	//////////////////////////////////////////////////////	
	G_ANSTYPE_REMOVEAT					= 55,	
	G_ANSTYPE_REMOVEALL					= 56,	
	G_ANSTYPE_CONTINUE_FLAG				= 57,	
};

enum EnANSCursorID
{		
	G_ANSCURSOR_ARROW					= 0,		//Ãß¼¼¼±Ä¿¼­-È­»ìÇ¥
	G_ANSCURSOR_PEN						= 1,		//Ãß¼¼¼±Ä¿¼­-Pen
	G_ANSCURSOR_SYMBOL					= 2,		//Ãß¼¼¼±Ä¿¼­-½Éº¼
	G_ANSCURSOR_TEXT					= 3,		//Ãß¼¼¼±Ä¿¼­-ÅØ½ºÆ®
	G_ANSCURSOR_AUTO					= 4,		//Ãß¼¼¼±Ä¿¼­-Auto
	G_ANSCURSOR_DISABLE					= 5,		//Ãß¼¼¼±Ä¿¼­-Disable
};

enum EnANSLineDrawStyle
{
	G_ANSDRAW_LINE						= 0,		//Ãß¼¼¼±-¸®ÀÎ
	G_ANSDRAW_RECTANGLE					= 1,		//Ãß¼¼¼±-»ç°¢Çü
	G_ANSDRAW_ELLIPSE					= 2,		//Ãß¼¼¼±-Å¸¿ø
	G_ANSDRAW_CIRCLE					= 3,		//Ãß¼¼¼±-¿ø
	G_ANSDRAW_HALFCIRCLE				= 4,		//Ãß¼¼¼±-¹Ý¿ø
	G_ANSDRAW_ARC						= 5,		//Ãß¼¼¼±-È£
	G_ANSDRAW_POINT						= 6,		//Ãß¼¼¼±-Á¡
};

enum EnANSLineExtStyle
{
	G_ANSEXT_LINE						= 0,		//Ãß¼¼¼±-¶óÀÎ
	G_ANSEXT_START						= 1,		//Ãß¼¼¼±-¶óÀÎ½ÃÀÛÈ®Àå
	G_ANSEXT_END						= 2,		//Ãß¼¼¼±-¶óÀÎ³¡È®Àå
	G_ANSEXT_BOTH						= 3,		//Ãß¼¼¼±-ÀüÃ¼È®Àå
};

enum EnANSSelectedPos
{
	G_ANSSELED_NONE						= -1,
	G_ANSSELED_POINT_START				= 0,
	G_ANSSELED_POINT_END				= 1,
	G_ANSSELED_POINT_THIRD				= 2,
	G_ANSSELED_LINE_SE					= 3,		//Start,End
	G_ANSSELED_LINE_ST					= 4,		//Start,Third
	G_ANSSELED_LINE_ET					= 5,		//End,Third
	G_ANSSELED_REGION					= 6,		//Symbol,Text,CircleInside....
	G_ANSSELED_LINE_FREE				= 7,		//Free Line
	G_ANSSELED_LINE_ARC					= 8,		//Arc,Circle,HalfCircle,Ellipse...
	G_ANSSELED_LINE_OTHERS				= 9,		//FibLines,...ElliotWave...µîÀÇ ¶óÀÎ¼ö°¡ 3ÀÌ ³Ñ´Â Ãß¼¼¼± Select
};

enum EnIBTypeMode
{
	G_IBTYPE_MODE_NONE					= -1,		//¾øÀ½
	G_IBTYPE_MODE_IND					= 0,		//ÁöÇ¥
	G_IBTYPE_MODE_OPT					= 1,		//ÃÖÀûÈ­
	G_IBTYPE_MODE_SIG					= 2,		//½Ã±×³Î
	G_IBTYPE_MODE_SHOWAT				= 3,		//±¸°£¼³Á¤
	G_IBTYPE_MODE_BASIC					= 4,		//±âº»ÇÔ¼ö
};

enum EnIBWorkModeType
{
	G_IBWORK_MODE_NEW					= 0,		//Ãß°¡
	G_IBWORK_MODE_COPY					= 1,		//º¹»ç
	G_IBWORK_MODE_MODIFY				= 2,		//¼öÁ¤
	G_IBWORK_MODE_DELETE				= 3,		//»èÁ¦
	G_IBWORK_MODE_RENAME				= 4,		//»õÀÌ·ë
	G_IBWORK_MODE_DISABLED				= 5,		//ÃÊ±â»ç¿ë¾ÈÇÔ
};

enum EnIBMadeType
{
	G_IB_MADE_SYSTEM					= 0,		//System
	G_IB_MADE_USER						= 1,		//User
	G_IB_MADE_NONE						= 2,		//ETC
};

const int G_KEYTABLESIZE				= 50;
enum EnTokenValue 
{
	G_TOKEN_ERROR	=-1,
	G_TOKEN_NAME	=0,
	G_TOKEN_NUMBER	=1,
	G_TOKEN_END		=2,
	G_TOKEN_PLUS	='+',
	G_TOKEN_MINUS	='-',
	G_TOKEN_MUL		='*',
	G_TOKEN_DIV		='/',
	G_TOKEN_MOD		='%',
	G_TOKEN_POW		='^',
	G_TOKEN_PRINT	=';',
	G_TOKEN_ASSIGN	='=',
	G_TOKEN_LP		='(',
	G_TOKEN_RP		=')',
	G_TOKEN_AND		='&',	              // &&, AND (logical AND)
	G_TOKEN_OR		='|',		          // ||, OR (logical OR)
	G_TOKEN_LT			,                 // <
	G_TOKEN_LE			,                 // <=
	G_TOKEN_GT			,                 // >
	G_TOKEN_GE			,                 // >=
	G_TOKEN_EQ			,                 // ==
	G_TOKEN_NEQ			,                 // != , <>
	G_TOKEN_NOT			,			      // ! , NOT (Not)
};

enum EnRequestItemType
{
	G_REQUEST_ITEM_MAIN		= 0,		//MainÂ÷Æ®Á¶È¸
	G_REQUEST_ITEM_MARIND	= 1,		//½ÃÀåº¸Á¶ÁöÇ¥Á¶È¸
	G_REQUEST_ITEM_OVERLAP	= 2,		//SyncOverlapÁ¶È¸
	G_REQUEST_ITEM_CALC		= 3,		//¿¬»êÂ÷Æ®Á¶È¸
};

enum EnChtFontStyle
{
	G_FONT_STYLE_NORMAL		= 0,		// NormalFont
	G_FONT_STYLE_BOLD		= 1,		// BoldFont
	G_FONT_STYLE_ITALIC		= 2,		// ItaliclFont
	G_FONT_STYLE_BOLDITALIC	= 3,		// BoldItalicFont
};

enum EnRequestQueryType
{
	G_REQUEST_TYPE_MAIN_DB	= 0,		// MainDBÁ¶È¸
	G_REQUEST_TYPE_MAIN_FIELD= 1,		// MainFieldÁ¶È¸
	G_REQUEST_TYPE_SUB_DB	= 2,		// SubDBÁ¶È¸
	G_REQUEST_TYPE_SUB_FIELD= 3,		// SubFieldÁ¶È¸
	G_REQUEST_TYPE_BOND_DB	= 4,		// BondÁ¶È¸
};

enum EnMPeriodANSEvent
{
	G_MPERIOD_EVENT_NONE				= -1,	
	G_MPERIOD_EVENT_ANSADD				= 0,
	G_MPERIOD_EVENT_ANSDELETE			= 1,		
	G_MPERIOD_EVENT_IDXADD				= 2,
	G_MPERIOD_EVENT_IDXDELETE			= 3,
};

//////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------------------------------------
Glabal Chart User Message Define Part
Chart User Message WM_User +100 ~ 200
----------------------------------------------------------------------------*/

#define		G_USERMSG_RESIZE				WM_USER + 100	
#define		G_USERMSG_HSCROLL				WM_USER + 101	
#define		G_USERMSG_ZOOMIN				WM_USER + 102	
#define		G_USERMSG_ZOOMOUT				WM_USER + 103	
#define		G_USERMSG_SHOWALL				WM_USER + 104	
#define		G_USERMSG_AREAEXPAND			WM_USER + 105	
#define		G_USERMSG_DATASEARCH			WM_USER + 106	
//#define		G_USERMSG_CHTPROPERTY			WM_USER + 107	// ÇöÀç »ç¿ë ¾ÈÇÔ.(2006.09.01 Hong~)
#define		G_USERMSG_CHART_ADD				WM_USER + 108	
#define		G_USERMSG_VIEWSIZE_CHANGE		WM_USER + 109	
#define		G_USERMSG_HEADBAR				WM_USER + 110
#define		G_USERMSG_FOOTBAR				WM_USER + 111
#define		G_USERMSG_SIDEBAR				WM_USER + 112
#define		G_USERMSG_SIDETOOLBAR			WM_USER + 113	
#define		G_USERMSG_VOLUMECHART			WM_USER + 114	
#define		G_USERMSG_SIDETOOLDLG			WM_USER + 115	
#define		G_USERMSG_CHTTYPE_CHANGE		WM_USER + 116

#define		G_USERMSG_PROPERTY_PRC			WM_USER + 117
#define		G_USERMSG_PROPERTY_VOL			WM_USER + 118
#define		G_USERMSG_PROPERTY_XAXIS		WM_USER + 119
#define		G_USERMSG_PROPERTY_YAXIS		WM_USER + 120
#define		G_USERMSG_PROPERTY_SCR			WM_USER + 121
#define		G_USERMSG_PROPERTY_GLOBAL		WM_USER + 122
#define		G_USERMSG_PROPERTY_INDEX		WM_USER + 123
#define		G_USERMSG_PROPERTY_MINI			WM_USER + 124
#define		G_USERMSG_CHART_DRAGDROP		WM_USER + 125
#define		G_USERMSG_ANSTOOL_SELECT		WM_USER + 126		// Ãß¼¼¼±¼±ÅÃ Message
#define		G_USERMSG_ANSTEXT_END			WM_USER + 127		// Ãß¼¼¼±Áß¿¡¼­ Text EditÀÇ Message exchange
#define		G_USERMSG_HORIZONTAL_INFO		WM_USER + 128		// ¼öÆò ¼öÄ¡Á¶È¸ 
#define		G_USERMSG_VERTICAL_INFO			WM_USER + 129		// ¼öÁ÷ ¼öÄ¡Á¶È¸ 
#define		G_USERMSG_CROSS_INFO			WM_USER + 130		// ½ÊÀÚ ¼öÄ¡Á¶È¸ 
#define		G_USERMSG_ANSINFO_CHANGE		WM_USER + 131		// Ãß¼¼¼± Àû¿ë 
#define		G_USERMSG_IBFUNCTION_FIND		WM_USER + 133
#define		G_USERMSG_IBCOMBO_EVENT			WM_USER + 134		// IBCombo Event
#define		G_USERMSG_BASEBTN_EVENT			WM_USER + 135
#define		G_USERMSG_IBPROPERTY_CHANGE		WM_USER + 136
#define		G_USERMSG_IBMESH_CHANGE			WM_USER + 137		// Mesh IB Change
#define		G_USERMSG_CODECOMBO_CHANGED		WM_USER + 138		// CodeCombo Changing Message
#define		G_USERMSG_DATASIZE_CHANGE		WM_USER + 139
#define		G_USERMSG_VARIABLE_FOCUS		WM_USER + 140
#define		G_USERMSG_CHTTEMPL_CHANGE		WM_USER + 141
#define		G_USERMSG_DBINFO_REFRESH		WM_USER + 142
#define		G_USERMSG_DATAGRIDBAR			WM_USER + 143
#define		G_USERMSG_DATAGRID_EVENT		WM_USER + 144	
#define		G_USERMSG_DATAGRID_ADD			WM_USER + 145	
#define		G_USERMSG_ITEMCOMBO_CHANGED		WM_USER + 146	
#define		G_USERMSG_PRCIND_DELETED		WM_USER + 147	
#define		G_USERMSG_REQUEST_CANCEL		WM_USER + 148
#define		G_USERMSG_3DCHART_EVENT			WM_USER + 149

//2004/07/01 - New Add
#define		G_USERMSG_CHART_CATCH			WM_USER + 150
#define		G_USERMSG_CHART_REVERSE			WM_USER + 151
#define		G_USERMSG_CHART_LOG				WM_USER + 152
#define		G_USERMSG_CHART_3D				WM_USER + 153
#define		G_USERMSG_CHART_OFF				WM_USER + 154
#define		G_USERMSG_CHART_MINMAX			WM_USER + 155
#define		G_USERMSG_CHART_YOVERLAB		WM_USER + 156
#define		G_USERMSG_CHART_TOOLTIP			WM_USER + 157
#define		G_USERMSG_CHART_TEMPLEXIT		WM_USER + 158
#define		G_USERMSG_CHART_TEMPLSAVE		WM_USER + 159
#define		G_USERMSG_CHART_TEMPLAPPLY		WM_USER + 160
#define		G_USERMSG_CHART_TEMPLDELETE		WM_USER + 161
#define		G_USERMSG_COMPARE_DATA_MOVE		WM_USER + 162
#define		G_USERMSG_DATA_WIZARD_APPLY		WM_USER + 163
#define		G_USERMSG_CHART_QUEUEADD		WM_USER + 164

//////////////////////////////////////////////////////////////////////////
/// MULTI
#define		G_USERMSG_MULTI_SIZE_CHANGE		WM_USER + 165
#define		G_USERMSG_MULTI_FOCUS_CHANGE	WM_USER + 166
#define		G_USERMSG_MULTI_SYNC_MODE		WM_USER + 167
#define		G_USERMSG_MULTI_CATE_CHANGE		WM_USER + 168
#define		G_USERMSG_MULTI_PROP_CHANGE		WM_USER + 169	

#define		G_USERMSG_MPERIOD_TYPECHANGE	WM_USER + 170
#define		G_USERMSG_MPERIOD_CHTEVENT		WM_USER + 171
#define		G_USERMSG_IBILMOK_CHANGE		WM_USER + 172

#define		G_USERMSG_GET_FUNC_FORMULA		WM_USER + 173
#define		G_USERMSG_CALC_REQUEST_CHANGE	WM_USER + 174
#define		G_USERMSG_CALC_SUB_DELETE		WM_USER + 175
#define		G_USERMSG_CALC_SUB_CHANGE		WM_USER + 176
#define		G_USERMSG_CHTFRAME_RESIZE		WM_USER + 177
#define		G_USERMSG_CYCLE_TYPE_CHANGE		WM_USER + 178
#define		G_USERMSG_CHART_TEMPLRENAME		WM_USER + 179
#define		G_USERMSG_SCREEN_CHT_EVENT		WM_USER + 180
#define		G_USERMSG_MINI_CHT_EVENT		WM_USER + 181
#define		G_USERMSG_CHART_SAVE_IMAGE		WM_USER + 182

// CColourPopup messages
#define		G_USERMSG_CPN_SELCHANGE			WM_USER + 183        // Colour Picker Selection change
#define		G_USERMSG_CPN_DROPDOWN			WM_USER + 184        // Colour Picker drop down
#define		G_USERMSG_CPN_CLOSEUP			WM_USER + 185        // Colour Picker close up
#define		G_USERMSG_CPN_SELENDOK			WM_USER + 186        // Colour Picker end OK
#define		G_USERMSG_CPN_SELENDCANCEL		WM_USER + 187        // Colour Picker end (cancelled)

// gxListCtrl messages
#define		G_USERMSG_GXLIST_EDITCHANGE		WM_USER + 188 
#define		G_USERMSG_PROPERTY_GRAPH		WM_USER + 189 

#define		G_USERMSG_VSCROLL				WM_USER + 190

//ÁöÇ¥Á¶È¸
#define		G_USERMSG_INDEXITEM_REQUEST		WM_USER + 191	

//ÃÖÀûÈ­ °ü·Ã
#define		G_USERMSG_OPTRESULT_PROGRESS	WM_USER + 192	
#define		G_USERMSG_OPTRESULT_SIGEVENT	WM_USER + 193	
#define		G_USERMSG_OPTRESULT_EVENT		WM_USER + 194	

//Chart Data Request Msg
#define		G_USERMSG_PERIOD_TICK			WM_USER + 195		// Tick Data ¿äÃ»	
#define		G_USERMSG_PERIOD_INTRA			WM_USER + 196		// Intra Data ¿äÃ»	
#define		G_USERMSG_PERIOD_DAY			WM_USER + 197		// Day Data ¿äÃ»	
#define		G_USERMSG_PERIOD_WEEK			WM_USER + 198		// Week Data ¿äÃ»
#define		G_USERMSG_PERIOD_MONTH			WM_USER + 199		// Month Data ¿äÃ»
#define		G_USERMSG_PERIOD_QUARTER		WM_USER + 200		// Quarter Data ¿äÃ»
#define		G_USERMSG_PERIOD_YEAR			WM_USER + 201		// Year Data ¿äÃ»
// TradingTrend »ç¿ë¿©ºÎ ÆÇ´Ü
#define		G_USERMSG_GETAVAILABLETRADINGTREND	WM_USER + 202

//////////////////////////////////////////////////////////////////////////////

#define		G_USERMSG_SLIDERZOOM			WM_USER + 203	// Slider Message

#define		G_USERMSG_CHARTINIT				WM_USER + 204	// Â÷Æ® ÃÊ±âÈ­¹öÆ°

#define		G_USERMSG_ANSTOOL_UNSELECT		WM_USER + 205	// Ãß¼¼¼± ¹Ì¼±ÅÃ Message

#define		G_USERMSG_PERIOD_SUBBTN_MSG		WM_USER + 206	// Period Sub Button Message

#define		G_USERMSG_SIDEBARINFO			WM_USER + 207	// Bar Á¤º¸¸¦ ¼¼ÆÃÇØÁØ´Ù.

#define		G_USERMSG_OPTEXE_OVERLAPCHECK	WM_USER + 208	// È­ÀÏÁßº¹À» Ã¼Å©ÇÑ´Ù.
#define		G_USERMSG_OPTEXE_TREEAPPEND		WM_USER + 209	// TREE¿¡ ÃÖÀûÈ­¸¦ Ãß°¡ÇÑ´Ù.

#define		G_USERMSG_INDICATORBUILDER		WM_USER + 300	// IndicatorBuilder È£Ãâ

#define		G_USERMSG_MODIFY				WM_USER + 301	// Modify

#define		G_USERMSG_INDICATORPROPERTYDLG	WM_USER + 302	// IndicatorProperty È£Ãâ

#define		G_USERMSG_PROPERTY_CONFIG		WM_USER + 303	// Config (¿öµåºÏ¾ð¾î, ´Þ·Â, SkinStyle, SkinColor)

#define		G_USERMSG_ANALYSISBAR_APPLY		WM_USER + 304	// Ãß¼¼¹Ù Àû¿ë

#define		G_USERMSG_ANALYSIS_SCREENAREA_SETTING	WM_USER + 305	// '¼¼Á¡À» ÂïÀ¸¼¼¿ä'Ãß¼¼¼±¿¡¼­ È­¸é»çÀÌÁî ¾ò±âÀ§ÇÑ ¸Þ½ÃÁö

#define		G_USERMSG_ANALYSIS_CANCEL		WM_USER + 306	// '¼¼Á¡À» ÂïÀ¸¼¼¿ä'Ãß¼¼¼± Ãë¼ÒÀ§ÇÑ ¸Þ½ÃÁö

#define		G_USERMSG_KEY_CROSSMOVE			WM_USER + 307	// Å°º¸µå¿¡ ÀÇÇÑ ½ÊÀÚ¼± ÀÌµ¿
#define		G_USERMSG_KEY_ZOOM				WM_USER + 308	// Å°º¸µå¿¡ È®´ë/Ãà¼Ò

#define		G_USERMSG_MPERIOD_SIDETOOLBAR	WM_USER + 309	

#define		G_USERMSG_LAST_PROPERTY			WM_USER + 310

#define		G_USERMSG_MAXDATA_SETTING		WM_USER + 311	// ºÐ¼®Â÷Æ®ÀÏ¶§ SliderBar Àçº¸Á¤


#define		G_USERMSG_PERIOD_ROTATE			WM_USER + 312	// Á¶È¸ Å¸ÀÔ ¼øÈ¯

//////////////////////////////////////////////////////////////////////////////
#define		G_USERMSG_PERIOD_GETPROPERTY	WM_USER + 500

//////////////////////////////////////////////////////////////////////////////
/// ÏÂÃæÎªÌØÉ«¹¤¾ßÀ¸ËùÊ¹ÓÃµÄÏûÏ¢ [Last Modified: Vincent Chen, 10-01-27]
//////////////////////////////////////////////////////////////////////////////
#define		G_USERMSG_TOOLS_EXECUTE				WM_USER + 600	// Ö´ÐÐ¹¤¾ß
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// ÌØÉ«¹¤¾ßÃ¶¾Ù±êÊ¶ [Last Modified: Vincent Chen, 10-01-27]
//////////////////////////////////////////////////////////////////////////////
enum EnFeaturedTools
{
	IndicatorBuilder = 100,	// ¼¼ÊõÖ¸±ê±à¼­Æ÷
	CandlePatternEditor,
	IBOptimizeExecutor,
};

const int G_MARKETTIME_VALUSECOUNT = 5;
static int G_MARKETTIMEVALUES[6] = {30,60,90,120,180,};
//////////////////////////////////////////////////////////////////////////////
//						Struct Defines

typedef struct tagST_CHART_COMMON_UNIT
{
	int		nChtKindType;				//
	TCHAR	chChtStCode[30];			//Á¾¸ñ StandardÄÚµå
	TCHAR	chChtName[30];				//Á¾¸ñ ¸í
	TCHAR	chItemName[30];				//½Ã°¡,Á¾°¡...
	int		nChtYScaleType;

	tagST_CHART_COMMON_UNIT()
	{
		nChtKindType	= 0;
		*chChtStCode	= 0x00;
		*chChtName		= 0x00;
		*chItemName		= 0x00;
		nChtYScaleType	= 0;
	}
	~tagST_CHART_COMMON_UNIT()
	{
	}

} ST_CHART_COMMON_UNIT,*LPST_CHART_COMMON_UNIT;

typedef struct tagST_PROPERTY_CHART
{
	int		nMarketCode;				//0:ÁÖ½Ä,1:ÄÚ½ºÅ¹,2:¼±¹°,3:¿É¼Ç.....
	TCHAR	chItemStCode[20];			//Á¾¸ñ StandardÄÚµå
	TCHAR	chItemCode[20];				//Á¾¸ñ ÄÚµå
	TCHAR	chItemName[30];				//Á¾¸ñ ¸í

	UINT	nDataPeriod;				//Tick,Intra,Day,Week,Month,Year....
	UINT	nDataCycle;					//1Tick,2Tick,.....
	UINT	nDateDayInfo;				//1ÀÏ,2ÀÏ

	TCHAR	chPassWord[10];				
	TCHAR	chVersion[10];				//Version - 1.0.0.0		
	TCHAR	chDummy[2];	

	tagST_PROPERTY_CHART()
	{
		nMarketCode		= 0;
		*chItemStCode	= 0x00;
		*chItemCode		= 0x00;
		*chItemName		= 0x00;

		nDataPeriod		= 0;
		nDataCycle		= 0;
		nDateDayInfo	= 0;

		*chPassWord		= 0x00;
		*chVersion		= 0x00;
		*chDummy		= 0x00;
	}
	~tagST_PROPERTY_CHART()
	{
	}

} ST_PROPERTY_CHART,*LPST_PROPERTY_CHART;
#define ST_PROPERTY_CHART_SIZE sizeof(tagST_PROPERTY_CHART)

typedef struct tagST_PROPERTY_TEMPLATE
{
	BOOL	bItemSaved;					//TRUE:¾Æ·¡ Á¤º¸ ±×´ë·Î Save & Load
										//FALSE:¾Æ·¡ Á¤º¸ »ó°ü¾øÀÌ Chart ¼³Á¤¸¸	

	TCHAR	chPassWord[10];				
	TCHAR	chVersion[10];				//Version - 1.0.0.0		
	TCHAR	chComment[100];	
	TCHAR	chDummy[2];	

	tagST_PROPERTY_TEMPLATE()
	{
		bItemSaved	= FALSE;
		*chPassWord	= 0x00;
		*chVersion	= 0x00;
		*chComment	= 0x00;
		*chDummy	= 0x00;
	}
	~tagST_PROPERTY_TEMPLATE()
	{
	}
} ST_PROPERTY_TEMPLATE,*LPST_PROPERTY_TEMPLATE;
#define ST_PROPERTY_TEMPLATE_SIZE sizeof(tagST_PROPERTY_TEMPLATE)

//ANS Struct - 
struct tagST_ANALYSIS_LINE_INFO
{
	BOOL bLineShow;
	int nLineStyle;
	int nLineWeight;
	COLORREF crLineColor;

	tagST_ANALYSIS_LINE_INFO()
	{
		bLineShow	= FALSE;
		nLineStyle	= 0;
		nLineWeight	= 0;
		crLineColor	= 0;
	}
	~tagST_ANALYSIS_LINE_INFO()
	{
	}
};
#define ST_ANALYSIS_LINE_INFO_SIZE sizeof(tagST_ANALYSIS_LINE_INFO)

typedef struct tagST_ANALYSIS_INFO
{
	int nDrawType;
	int nStartXPos;
	int nEndXPos;
	int nThirdXPos;
	int nFourthXPos;

	double dStartYValue;
	double dEndYValue;
	double dThirdYValue;
	double dFourthYValue;

	CPoint ptStart;
	CPoint ptEnd;
	CPoint ptThird;
	CPoint ptFourth;

	int nLeftExt;
	int nRightExt;
	int nFullExt;
	int nFillRegion;
	int nLeftRatio;
	int nRightValue;
	int	nFullMoving;
	int	nAnsDirect;
	int	nBLineShow;

	int nShiftXIndex;
	double dShiftYVAlue;

	double dSwingRatio;
	int nSapPos;
	int nChtRegionIndex;

	TCHAR chText[200];
	double dCalcRatio[10];
	CPoint ptPosLists[10];
	double dYValueLists[10];
	tagST_ANALYSIS_LINE_INFO pANSLineInfos[10];
	CRect rcANSREct;
	COLORREF crSymbolColor;
	int nSymbolIndex;
	int nSymbolSize;

	BOOL bRatioBaseLine;
	double dBandHeight;

	//¸¸ÀÏ Â©¸®´õ¶óµµ »ó°ü¾ø´Ù - °è¼Ó Ç¥ÇöÇÒ¼ö´Â ¾ø´Ù
	int nFreeLineCount;
	CPoint ptFreeLines[200];
	int nTurningDirect[200];
	int nFreeXIndex[200];
	double dFreeYValue[200];


	tagST_ANALYSIS_INFO()
	{
		nDrawType		= 0;
		nStartXPos		= 0;
		nEndXPos		= 0;
		nThirdXPos		= 0;
		nFourthXPos		= 0;

		dStartYValue	= 0.0;
		dEndYValue		= 0.0;
		dThirdYValue	= 0.0;
		dFourthYValue	= 0.0;

		//ptStart;
		//ptEnd;
		//ptThird;
		//ptFourth;

		nLeftExt		= 0;
		nRightExt		= 0;
		nFullExt		= 0;
		nFillRegion		= 0;
		nLeftRatio		= 0;
		nRightValue		= 0;
		nFullMoving		= 0;
		nAnsDirect		= 0;
		nBLineShow		= 0;

		nShiftXIndex	= 0;
		dShiftYVAlue	= 0.0;

		dSwingRatio		= 0.0;
		nSapPos			= 0;
		nChtRegionIndex	= 0;

		*chText			= 0x00;
		memset(dCalcRatio, 0, sizeof(double)*10);
		//ptPosLists[10];
		memset(dYValueLists, 0, sizeof(double)*10);
		//pANSLineInfos[10];
		//rcANSREct;
		crSymbolColor	= 0;
		nSymbolIndex	= 0;
		nSymbolSize		= 0;

		bRatioBaseLine	= FALSE;
		dBandHeight		= 0.0;

		//¸¸ÀÏ Â©¸®´õ¶óµµ »ó°ü¾ø´Ù - °è¼Ó Ç¥ÇöÇÒ¼ö´Â ¾ø´Ù
		nFreeLineCount	= 0;
		//ptFreeLines[200];
		memset(nTurningDirect, 0, sizeof(int)*200);
		memset(nFreeXIndex, 0, sizeof(int)*200);
		memset(dFreeYValue, 0, sizeof(double)*200);
	}
	~tagST_ANALYSIS_INFO()
	{
	}

} ST_ANALYSIS_INFO,*LPST_ANALYSIS_INFO;
#define ST_ANALYSIS_INFO_SIZE sizeof(tagST_ANALYSIS_INFO)

typedef struct tagST_MPERIOD_ANSINFO
{
	int nDrawType;
	double dStartXDate;
	double dEndXDate;
	double dNextStartXDate;
	double dNextEndXDate;

	double dStartYValue;
	double dEndYValue;	

	double dSwingRatio;

	tagST_MPERIOD_ANSINFO()
	{
		nDrawType		= 0;
		dStartXDate		= 0.0;
		dEndXDate		= 0.0;
		dNextStartXDate	= 0.0;
		dNextEndXDate	= 0.0;
		dStartYValue	= 0.0;
		dEndYValue		= 0.0;
		dSwingRatio		= 0.0;
	}
	~tagST_MPERIOD_ANSINFO()
	{
	}

} ST_MPERIOD_ANSINFO,*LPST_MPERIOD_ANSINFO;
#define ST_MPERIOD_ANSINFO_SIZE sizeof(tagST_MPERIOD_ANSINFO)

//°¢ÀÚ°¡ °¡Áö°í ÀÖ´Â PriceTypeµé
typedef struct tagST_PRICETYPE_INFO
{
	COLORREF crPrcUpLine;
	BOOL	 bPrcUpFill;
	COLORREF crPrcUpBody;	
	COLORREF crPrcDownLine;
	BOOL	 bPrcDownFill;
	COLORREF crPrcDownBody;
	COLORREF crPrcOffLine;
	BOOL	 bPrcOffFill;
	COLORREF crPrcOffBody;

	int		nDataType;
	COLORREF crLineColor;
	int		nLineStyle;
	int		nLineWeight;

	int		nDefineBase;
	double	dBaseValue;

	//2005/08/01++
	BOOL	bLastPrevLine;
	COLORREF crLastPrevLine;
	int		nPrevLineStyle;
	int		nPrevLineWeight;
	//2005/08/01--

	BOOL	bMaxMinDisplay;
	BOOL	bLogScale;
	BOOL	bInvertScale;
	BOOL	bTitleShow;
	BOOL	bGradationShow;

	BOOL	bAutoOffering;
	int		nOfferingCount;
	//////////////////////////////
	int		nCalcType;			//0:TurningRatio,1:È£°¡,2°¡°Ý
	double  dChartValue1;		//ºñÀ²°ª,¸îÈ£°¡,°¡°Ý,3¼±<->4¼±ÀüÈ¯µî
	double	dChartValue2;		


	tagST_PRICETYPE_INFO()
	{
		crPrcUpLine			= 0;
		bPrcUpFill			= FALSE;
		crPrcUpBody			= 0;
		crPrcDownLine		= 0;
		bPrcDownFill		= FALSE;
		crPrcDownBody		= 0;
		crPrcOffLine		= 0;
		bPrcOffFill			= FALSE;
		crPrcOffBody		= 0;

		nDataType			= 0;
		crLineColor			= 0;
		nLineStyle			= 0;
		nLineWeight			= 0;

		nDefineBase			= 0;
		dBaseValue			= 0.0;

		//2005/08/01++
		bLastPrevLine		= FALSE;
		crLastPrevLine		= 0;
		nPrevLineStyle		= 0;
		nPrevLineWeight		= 0;
		//2005/08/01--

		bMaxMinDisplay		= FALSE;
		bLogScale			= FALSE;
		bInvertScale		= FALSE;
		bTitleShow			= FALSE;
		bGradationShow		= FALSE;

		bAutoOffering		= FALSE;
		nOfferingCount		= 0;
		
		nCalcType			= 0;
		dChartValue1		= 0.0;
		dChartValue2		= 0.0;
	}
	~tagST_PRICETYPE_INFO()
	{
	}

} ST_PRICETYPE_INFO,*LPST_PRICETYPE_INFO;
#define ST_PRICETYPE_INFO_SIZE sizeof(tagST_PRICETYPE_INFO)

//Price Struct
typedef struct tagST_PROPERTY_PRICE
{
	int		 nPrcType;				///< Price(Main)Â÷Æ® Å¸ÀÔ (G_PRCCHT_CANDLE,...)

	COLORREF crPrcUpLine;			///< »ó½Â ¶óÀÎ»ö
	BOOL	 bPrcUpFill;			///< »ó½Â ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crPrcUpBody;			///< »ó½Â ºÀ¸öÃ¼»ö
	COLORREF crPrcDownLine;			///< ÇÏ¶ô ¶óÀÎ»ö
	BOOL	 bPrcDownFill;			///< ÇÏ¶ô ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crPrcDownBody;			///< ÇÏ¶ô ºÀ¸öÃ¼»ö

	COLORREF crPrcFlat;				///< º¸ÇÕ ¶óÀÎ/¸öÃ¼»ö
	BOOL	 bPrcFlat;				///< º¸ÇÕ ¶óÀÎ/¸öÃ¼»öÀ» ÀÚµ¿ÀûÀ¸·Î ³»ºÎ¿¡¼­ Á¤ÇÑ´ë·Î ÇÒÁöÀÇ ¿©ºÎ

	COLORREF crPrcOffLine;			///< ¸Å¹°´ë ¶óÀÎ»ö
	BOOL	 bPrcOffFill;			///< ¸Å¹°´ë ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crPrcOffBody;			///< ¸Å¹°´ë ºÀ¸öÃ¼»ö

	int		nDataType;				///< °¡°Ý µ¥ÀÌÅÍ(½Ã,°í,Àú,Á¾, ½Ã°íÀúÁ¾,...)
	COLORREF crLineColor;			///< ¶óÀÎ»ö
	int		nLineStyle;				///< ¶óÀÎ½ºÅ¸ÀÏ
	int		nLineWeight;			///< ¶óÀÎ±¼±â

	int		nDefineBase;			///< ¾çºÀ±âÁØ(´çÀÏÁ¾°¡>´çÀÏ½Ã°¡, ´çÀÏÁ¾°¡>ÀüÀÏÁ¾°¡, ´çÀÏÁ¾°¡>±âÁØ°¡)
									///< ´ÙÁß¸Þ¹°Â÷Æ®¿¡¼± ¸Å¹°½Ã°£À¸·Î »ç¿ë
	double	dBaseValue;				///< ¾çºÀ±âÁØ°¡(´çÀÏÁ¾°¡>±âÁØ°¡ÀÇ ±âÁØ°¡)

	BOOL	bLastPrevLine;			///< ÀüÀÏÁ¾°¡¼± Ç¥½Ã ¿©ºÎ
	COLORREF crLastPrevLine;		///< ÀüÀÏÁ¾°¡¼±»ö
	int		nPrevLineStyle;			///< ÀüÀÏÁ¾°¡¼± ½ºÅ¸ÀÏ
	int		nPrevLineWeight;		///< ÀüÀÏÁ¾°¡¼± ±½±â

	BOOL	bMaxMinDisplay;			///< ÃÖ´ë/ÃÖ¼Ò°ª Ç¥½Ã
	BOOL	bLogScale;				///< ·Î±×Â÷Æ®
	BOOL	bInvertScale;			///< ¿ª»óÂ÷Æ®
	BOOL	bTitleShow;				///< Å¸ÀÌÆ²º¸±â
	BOOL	bGradationShow;			///< GradationÈ¿°ú

	BOOL	bAutoOffering;			///< ÀÚµ¿ ¸Å¹°´ë ¿©ºÎ
	int		nOfferingCount;			///< ¸Å¹°ÁöÁ¤ °¹¼ö
	double  dIndexValue1;			///< Price(Main)Â÷Æ®º° ÇÊ¿ä°ª(¿¹:¾ÐÃàÂ÷Æ®ÀÇ ¾ÐÃàºñÀ², SyncOverlapÂ÷Æ®ÀÇ °è»ê¹æ½Ä)
	double  dIndexValue2;			///< Price(Main)Â÷Æ®º° ÇÊ¿ä°ª2(¿¹:SyncOverlapÂ÷Æ®ÀÇ ±×¸®±â¹æ½Ä)

	//2005/03/07 - ¿¬»ê Â÷Æ®¶§¹®¿¡ »õ·Î Ãß°¡µÈ ºÎºÐ
	int		nCalcInfo;
	TCHAR	chCalcInfo[30];
	TCHAR	chMainStCode[30];
	TCHAR	chSub1StCode[30];
	TCHAR	chSub2StCode[30];
	int     nTwoCandleStyle;        //[kenny]  2010-1-12  Ä¬ÈÏÊÇ¡°¶þÉ«ÒõÑôÖò¡±

	tagST_PROPERTY_PRICE()
	{
		nPrcType			= 0;
		crPrcUpLine			= G_CLR_RED;
		bPrcUpFill			= TRUE;
		crPrcUpBody			= G_CLR_RED;
		crPrcDownLine		= G_CLR_BLUE;
		bPrcDownFill		= TRUE;
		crPrcDownBody		= G_CLR_BLUE;
		crPrcFlat			= G_CLR_GRAY_FORTY;
		bPrcFlat			= FALSE;
		crPrcOffLine		= G_CLR_GREEN;
		bPrcOffFill			= TRUE;
		crPrcOffBody		= G_CLR_GREEN;
		nDataType			= 0;
		crLineColor			= G_CLR_GRAY_FORTY;
		nLineStyle			= 0;
		nLineWeight			= 0;
		nDefineBase			= 0;
		dBaseValue			= 0.0;
		bLastPrevLine		= FALSE;
		crLastPrevLine		= 0;
		nPrevLineStyle		= 0;
		nPrevLineWeight		= 0;
		bMaxMinDisplay		= FALSE;
		bLogScale			= FALSE;
		bInvertScale		= FALSE;
		bTitleShow			= FALSE;
		bGradationShow		= FALSE;
		bAutoOffering		= FALSE;
		nOfferingCount		= 0;
		dIndexValue1		= 0.0;
		dIndexValue2		= 0.0;
		nCalcInfo			= 0;
		*chCalcInfo			= 0x00;
		*chMainStCode		= 0x00;
		*chSub1StCode		= 0x00;
		*chSub2StCode		= 0x00;

		nTwoCandleStyle     =0;
	}
	~tagST_PROPERTY_PRICE()
	{
	}

} ST_PROPERTY_PRICE,*LPST_PROPERTY_PRICE;
#define ST_PROPERTY_PRICE_SIZE sizeof(tagST_PROPERTY_PRICE)

//Volume Struct
typedef struct tagST_PROPERTY_VOLUME
{
	int		nVolumeType;			///< °Å·¡·®Á¾·ù(°Å·¡Bar, °Å·¡Line, °Å·¡Mountain, °Å·¡À½¾çBar, ÁÖ°¡À½¾çBar)

	COLORREF crVolLine;				///< ºÀ¶óÀÎ»ö
	BOOL	 bVolFill;				///< ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crVolBody;				///< ºÀ¸öÃ¼»ö
	int		nLineStyle;				///< °Å·¡LineÀÏ¶§ Line Style
	int		nLineWeight;			///< °Å·¡LineÀÏ¶§ Line Weight

	COLORREF crVolUpLine;			///< °Å·¡/ÁÖ°¡ À½¾ç¹ÙÀÇ »ó½Â ¶óÀÎ»ö
	BOOL	 bVolUpFill;			///< °Å·¡/ÁÖ°¡ À½¾ç¹ÙÀÇ »ó½Â ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crVolUpBody;			///< °Å·¡/ÁÖ°¡ À½¾ç¹ÙÀÇ »ó½Â ºÀ¸öÃ¼»ö

	COLORREF crVolDownLine;			///< °Å·¡/ÁÖ°¡ À½¾ç¹ÙÀÇ ÇÏ¶ô ¶óÀÎ»ö
	BOOL	 bVolDownFill;			///< °Å·¡/ÁÖ°¡ À½¾ç¹ÙÀÇ ÇÏ¶ô ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crVolDownBody;			///< °Å·¡/ÁÖ°¡ À½¾ç¹ÙÀÇ ÇÏ¶ô ºÀ¸öÃ¼»ö

	BOOL	bMaxMinDisplay;			///< ÃÖ´ëÃÖ¼Ò°ªÇ¥½Ã
	BOOL	bLogScale;				///< LogScale
	BOOL	bTitleShow;				///< Titleº¸±â
	BOOL	bGradationShow;			///< GradationÈ¿°ú

	tagST_PROPERTY_VOLUME()
	{
		nVolumeType		= 0;
		crVolLine		= 0;
		bVolFill		= FALSE;
		crVolBody		= 0;
		nLineStyle		= 0;
		nLineWeight		= 0;
		crVolUpLine		= 0;
		bVolUpFill		= FALSE;
		crVolUpBody		= 0;
		crVolDownLine	= 0;
		bVolDownFill	= FALSE;
		crVolDownBody	= 0;
		bMaxMinDisplay	= FALSE;
		bLogScale		= FALSE;
		bTitleShow		= FALSE;
		bGradationShow	= FALSE;
	}
	~tagST_PROPERTY_VOLUME()
	{
	}
} ST_PROPERTY_VOLUME,*LPST_PROPERTY_VOLUME;
#define ST_PROPERTY_VOLUME_SIZE sizeof(tagST_PROPERTY_VOLUME)

//XAxis Struct
typedef struct tagST_PROPERTY_XAXIS
{
	int		nXAxisTimeType;			///< Æ½/ºÐ Â÷Æ®ÀÇ ½Ã°£ Ç¥Çö ¹æ½Ä
	int		nXAxisDayType;			///< ÀÏÁÖ¿ù Â÷Æ®ÀÇ ³¯Â¥ Ç¥Çö ¹æ½Ä
	
	int		nXAxisSpace;			///< XÃà °ø°£ ºñ¿ì±â(+ ¿À¸¥ÂÊ, - ¿ÞÂÊ °ø°£ºñ¿ò)
	
	BOOL	bShowFirstData;			///< Ã¹µ¥ÀÌÅÍÇ¥½Ã
	int		nFirstDataType;			///< Ã¹µ¥ÀÌÅÍ Ç¥Çö ¹æ½Ä
	COLORREF crFirstText;			///< Ã¹µ¥ÀÌÅÍ ±ÛÀÚ»ö

	BOOL	bShowLastData;			///< ¸¶Áö¸·µ¥ÀÌÅÍÇ¥½Ã
	int		nLastDataType;			///< ¸¶Áö¸·µ¥ÀÌÅÍ Ç¥Çö ¹æ½Ä
	COLORREF crLastText;			///< ¸¶Áö¸·µ¥ÀÌÅÍ ±ÛÀÚ»ö

	BOOL	bShowXAxis;				///< XÃà º¸ÀÌ±â
	BOOL	bShowWeekMark;			///< ÁÖ´ÜÀ§ ¸¶Å© º¸ÀÌ±â
	COLORREF crBackGround;			///< XÃà ¹ÙÅÁ»ö
	COLORREF crForeGround;			///< XÃà ±ÛÀÚ»ö

	tagST_PROPERTY_XAXIS()
	{
		nXAxisTimeType		= 0;
		nXAxisDayType		= 0;
		nXAxisSpace			= 0;
		bShowFirstData		= FALSE;
		nFirstDataType		= 0;
		crFirstText			= 0;
		bShowLastData		= FALSE;
		nLastDataType		= 0;
		crLastText			= 0;
		bShowXAxis			= FALSE;
		bShowWeekMark		= FALSE;
		crBackGround		= 0;
		crForeGround		= 0;
	}
	~tagST_PROPERTY_XAXIS()
	{
	}
} ST_PROPERTY_XAXIS,*LPST_PROPERTY_XAXIS;
#define ST_PROPERTY_XAXIS_SIZE sizeof(tagST_PROPERTY_XAXIS)

typedef struct tagST_QUERY_TYPE_INFO
{
	int		nQueryPeriod;		///< Á¶È¸ Period(G_CHTPERIOD_TICK,..) ///<
	int		nQueryType;			///< ??? ///<

	int		nSection;			///< ±¸ºÐ(0:³¯ÁöÁ¤(1Æ½orºÐ)1ÀÏ2ÀÏ.., 1:³¯Â¥ÁöÁ¤, 2:°¹¼öÁöÁ¤)

	int		nTickMinVal;		///< 1Æ½,2Æ½,3Æ½... or 1ºÐ,2ºÐ,3ºÐ(ÃÊ·Î±â¾ï)...
	int		nDateVal;			///< 1ÀÏ,2ÀÏ,3ÀÏ,4ÀÏ,5ÀÏ...
	int		nOptionVal;			///< ÀÓÀÇ(nTickMinVal = -1 < Intra ÀÏ¶§ ÀÓÀÇ ÁöÁ¤ÇÒ ¼öÀÖÀ½(ÁÖ±âÂ÷Æ® »©°í)...ºÐ¸¸ ³ÖÀ»¼öÀÖÀ½.>)

	double	dStartDateTime;		///< ½ÃÀÛÀÏ½Ã(20070527091200)
	double	dEndDateTime;		///< ³¡  ÀÏ½Ã(20070528102000)

	BOOL	bQueryFull;			///< ÀüÃ¼µ¥ÀÌÅÍ¿ä±¸	///<
	int		nQueryCount;		///< Á¶È¸°¹¼ö ///<
	int		nViewCount;			///< È­¸é¿¡ º¸¿©ÁÙ °¹¼ö ///<

	BOOL	bFixedEndDateTime;	///< ¹Ì¶¨µÄ½áÊøÈÕÆÚ£¬¼´À´ÐÂÊý¾Ý²»ÊµÊ±¸üÐÂ¡£[Vincent Chen, 10-01-07]

	tagST_QUERY_TYPE_INFO()
	{
		nQueryPeriod	= 2;
		nQueryType		= 0;

		nSection		= 2;

		nTickMinVal		= 1;	
		nDateVal		= 1;
		nOptionVal		= 0;	

		dStartDateTime	= 0.0;	
		dEndDateTime	= 0.0;	

		bQueryFull		= FALSE;
		nQueryCount		= 0;
		nViewCount		= 0;
		bFixedEndDateTime = FALSE;	/// Ä¬ÈÏ²»¹Ì¶¨¹Ì¶¨½áÊøÈÕÆÚ¡£[Vincent Chen, 10-01-07]
	}
	~tagST_QUERY_TYPE_INFO()
	{
	}
}ST_QUERY_TYPE_INFO,*LPST_QUERY_TYPE_INFO;
#define ST_QUERY_TYPE_INFO_SIZE sizeof(tagST_QUERY_TYPE_INFO)

typedef struct tagST_CYCLE_QUERY_TYPE_INFO
{
	int		nQueryPeriod;		///< Á¶È¸ Period(G_CHTPERIOD_TICK,..) ///<

	int		nSection;			///< ±¸ºÐ(0:³¯ÁöÁ¤(1Æ½orºÐ)1ÀÏ2ÀÏ.., 1:³¯Â¥ÁöÁ¤, 2:°¹¼öÁöÁ¤)

	int		nMinVal;			///< 10ÃÊ,20ÃÊ,30ÃÊ,1ºÐ,2ºÐ,3ºÐ(ÃÊ·Î±â¾ï)...
	int		nDateVal;			///< 2ÀÏ,3ÀÏ,4ÀÏ,5ÀÏ,6ÀÏ,7ÀÏ / 2³â,3³â,4³â,5³â,6³â,7³â

	double	dStartDateTime;		///< ½ÃÀÛÀÏ½Ã(20070527091200)
	double	dEndDateTime;		///< ³¡  ÀÏ½Ã(20070528102000)


	tagST_CYCLE_QUERY_TYPE_INFO()
	{
		nQueryPeriod	= 2;

		nSection		= 0;

		nMinVal			= 10;
		nDateVal		= 0;

		dStartDateTime	= 0.0;	
		dEndDateTime	= 0.0;	
	}
	~tagST_CYCLE_QUERY_TYPE_INFO()
	{
	}
}ST_CYCLE_QUERY_TYPE_INFO,*LPST_CYCLE_QUERY_TYPE_INFO;
#define ST_CYCLE_QUERY_TYPE_INFO_SIZE sizeof(tagST_CYCLE_QUERY_TYPE_INFO)

//Screen Struct
typedef struct tagST_PROPERTY_SCREEN
{
	BOOL	bHeadBarShow;			///< HeadBarº¸ÀÌ±â
	BOOL	bFootBarShow;			///< FootBarº¸ÀÌ±â
	BOOL	bSideBarShow;			///< Sidebarº¸ÀÌ±â
	BOOL	bSideToolBarShow;		///< SideToolBarº¸ÀÌ±â
	BOOL	bDataGridBarShow;		///< DataGridBarº¸ÀÌ±â

	ST_QUERY_TYPE_INFO stQueryTypeInfo[10];	///< Á¶È¸µ¥ÀÌÅÍ Á¤º¸(DayÀÇ ÀüÃ¼µ¥ÀÌÅÍ¿ä±¸ ¶Ç´Â °¹¼öÁöÁ¤, View CountÁöÁ¤µî..)
	//--  2004/09/15

	int		nScreenBKType;			///< È­¸é¹è°æ¼³Á¤(0:Color BK Screen,1:WallPaper - Image BK Screen)
	COLORREF crBKColor;				///< È­¸é¹è°æ»ö
	TCHAR	szWallPaperPath[300];	///< WallPaper ÆÄÀÏ °æ·Î

	BOOL	bScreenHorizon;			///< ¼öÆò´«±ÝÀÚ »ç¿ë¿©ºÎ
	int		nScreenHLineType;		///< ¼öÆò´«±ÝÀÚ Å¸ÀÔ(solid, dot...)
	int		nScreenHLineWeight;		///< ¼öÆò´«±ÝÀÚ ±½±â
	COLORREF crScreenHLineColor;	///< ¼öÆò´«±ÝÀÚ »ö
	BOOL	bScreenHBackward;		///< ¼öÆò´«±ÝÀÚ È­¸é µÚ¿¡ Ç¥½ÃÇÒÁöÀÇ ¿©ºÎ

	COLORREF crScreenHLineFillColor;	///< ¼öÆò´«±ÝÀÚ Fill »ö

	BOOL	bScreenVertical;		///< ¼öÁ÷´«±ÝÀÚ »ç¿ë¿©ºÎ
	int		nScreenVLineType;		///< ¼öÁ÷´«±ÝÀÚ Å¸ÀÔ(solid, dot...)
	int		nScreenVLineWeight;		///< ¼öÁ÷´«±ÝÀÚ ±½±â
	COLORREF crScreenVLineColor;	///< ¼öÁ÷´«±ÝÀÚ »ö
	BOOL	bScreenVBackward;		///< ¼öÁ÷´«±ÝÀÚ È­¸é µÚ¿¡ Ç¥½ÃÇÒÁöÀÇ ¿©ºÎ	

	BOOL	bDataGapCorrect;		///< DataGapº¸Á¤	
	BOOL	bDataOff;				///< ¼öÁ¤ÁÖ°¡º¸Á¤
	BOOL	bDataLimit;				///< »ó/ÇÏÇÑ°¡Ç¥½Ã
	BOOL	bDataOption;			///< ¿É¼ÇÇà»ç°¡Ç¥½Ã	

	tagST_PROPERTY_SCREEN()
	{
		bHeadBarShow		= FALSE;
		bFootBarShow		= FALSE;
		bSideBarShow		= FALSE;
		bSideToolBarShow	= FALSE;
		bDataGridBarShow	= FALSE;
		//stQueryTypeInfo[10];
		nScreenBKType		= 0;
		crBKColor			= 0;
		//*szWallPaperPath	= 0x00;	
		memset(szWallPaperPath,0x00,sizeof(TCHAR)*300);//[kangyb 2010-08-04]
		bScreenHorizon		= FALSE;
		nScreenHLineType	= 0;
		nScreenHLineWeight	= 0;
		crScreenHLineColor	= 0;
		bScreenHBackward	= FALSE;

		crScreenHLineFillColor = 0;
		
		bScreenVertical		= FALSE;
		nScreenVLineType	= 0;
		nScreenVLineWeight	= 0;
		crScreenVLineColor	= 0;
		bScreenVBackward	= FALSE;
		bDataGapCorrect		= FALSE;
		bDataOff			= FALSE;
		bDataLimit			= FALSE;
		bDataOption			= FALSE;
	}
	~tagST_PROPERTY_SCREEN()
	{
	}

} ST_PROPERTY_SCREEN,*LPST_PROPERTY_SCREEN;
#define ST_PROPERTY_SCREEN_SIZE sizeof(tagST_PROPERTY_SCREEN)

typedef struct tagST_QUERY_TYPE_INFO_TEMP
{
	int		nQueryPeriod;		///< Á¶È¸ Period(G_CHTPERIOD_TICK,..) ///<
	int		nQueryType;			///< ??? ///<
	BOOL	bQueryFull;			///< ÀüÃ¼µ¥ÀÌÅÍ¿ä±¸	///<
	int		nQueryCount;		///< Á¶È¸°¹¼ö ///<
	int		nViewCount;			///< È­¸é¿¡ º¸¿©ÁÙ °¹¼ö ///<

	tagST_QUERY_TYPE_INFO_TEMP()
	{
		nQueryPeriod	= 0;
		nQueryType		= 0;
		bQueryFull		= FALSE;
		nQueryCount		= 0;
		nViewCount		= 0;
	}
	~tagST_QUERY_TYPE_INFO_TEMP()
	{
	}
}ST_QUERY_TYPE_INFO_TEMP,*LPST_QUERY_TYPE_INFO_TEMP;
#define ST_QUERY_TYPE_INFO_TEMP_SIZE sizeof(tagST_QUERY_TYPE_INFO_TEMP)

//Global Struct
typedef struct tagST_PROPERTY_GLOBAL
{
	USHORT	nFontType;				///< ÆùÆ® Å¸ÀÔ
	USHORT	nFontSize;				///< ÆùÆ®»çÀÌÁî
	USHORT	nBoldType;				///< ÆùÆ®½ºÅ¸ÀÏ(0:º¸Åë,1:±½°Ô,2:±â¿ïÀÓ,3:±½°Ô±â¿ïÀÓ)
	
	COLORREF crFontColor;			///< ÆùÆ®ÄÃ·¯
	BOOL	bFontFixStyle;			///< °íÁ¤/°¡º¯ ¿©ºÎ
	BOOL	bMaxMinRatio;			///< ÃÖ°í/ÃÖÀú°¡´ëºñ Ç¥½Ã
	BOOL	bShowComparison;		//´ëºñ Ç¥½Ã - ÇöÀç °Å·¡·®ÁöÇ¥´Â Á¦¿Ü
	BOOL	b3DEffect;				///< 3DÈ¿°ú
	BOOL	bAnsContinue;			///< Â÷Æ®ºÐ¼®Åø ¿¬¼Ó±×¸®±â
	BOOL	bShowToolTip;			///< ÅøÆÁ º¸¿©ÁÙÁöÀÇ ¿©ºÎ
	BOOL	bRegionSelected;		///< Â÷Æ®¿µ¿ª ¼±ÅÃÇ¥½Ã

	int		nTitleDisplayDirect;	///< ¼öÆò/¼öÁ÷ Å¸ÀÌÆ² Ç¥½Ã
	int		nTitleDisplayType;		///< Title ¼öÄ¡Á¶È­(0:¸¶¿ì½ºÀÌµ¿½Ã ÀÚµ¿,1:¸¶¿ì½º Å¬¸®½Ã ¼öÄ¡Á¶È¸,2:¸¶Áö¸· Á¾°¡¸¸)
	int		nBongInterval;			///< ºÀ°£°Ý
	int		nChtMarginSize;			///< Â÷Æ®¿©¹é¿µ¿ª

	BOOL	bChtZoneMoving;			///< Â÷Æ® ¿µ¿ªÀâ°í ÀÌµ¿ ½ºÅ©·Ñ
	BOOL	bReturnRegionExpand;	///< ±¸°£È®´ë½Ã µÇµ¹¸²±â´É

	tagST_PROPERTY_GLOBAL()
	{
		nFontType			= 0;
		nFontSize			= 0;
		nBoldType			= 0;
		crFontColor			= 0;
		bFontFixStyle		= FALSE;
		bMaxMinRatio		= FALSE;
		bShowComparison		= FALSE;
		b3DEffect			= FALSE;
		bAnsContinue		= FALSE;
		bShowToolTip		= FALSE;
		bRegionSelected		= FALSE;
		nTitleDisplayDirect	= 0;
		nTitleDisplayType	= 0;
		nBongInterval		= 0;
		nChtMarginSize		= 0;
		bChtZoneMoving		= FALSE;
		bReturnRegionExpand	= FALSE;
	}
	~tagST_PROPERTY_GLOBAL()
	{
	}

} ST_PROPERTY_GLOBAL,*LPST_PROPERTY_GLOBAL;
#define ST_PROPERTY_GLOBAL_SIZE sizeof(tagST_PROPERTY_GLOBAL)

//ScreenTemp Struct
typedef struct tagST_PROPERTY_SCREEN_TEMP
{
	BOOL	bHeadBarShow;			///< HeadBarº¸ÀÌ±â
	BOOL	bFootBarShow;			///< FootBarº¸ÀÌ±â
	BOOL	bSideBarShow;			///< Sidebarº¸ÀÌ±â
	BOOL	bSideToolBarShow;		///< SideToolBarº¸ÀÌ±â
	BOOL	bDataGridBarShow;		///< DataGridBarº¸ÀÌ±â

	ST_QUERY_TYPE_INFO_TEMP stQueryTypeInfo[10];	///< Á¶È¸µ¥ÀÌÅÍ Á¤º¸(DayÀÇ ÀüÃ¼µ¥ÀÌÅÍ¿ä±¸ ¶Ç´Â °¹¼öÁöÁ¤, View CountÁöÁ¤µî..)
	//--  2004/09/15

	int		nScreenBKType;			///< È­¸é¹è°æ¼³Á¤(0:Color BK Screen,1:WallPaper - Image BK Screen)
	COLORREF crBKColor;				///< È­¸é¹è°æ»ö
	TCHAR	szWallPaperPath[300];	///< WallPaper ÆÄÀÏ °æ·Î

	BOOL	bScreenHorizon;			///< ¼öÆò´«±ÝÀÚ »ç¿ë¿©ºÎ
	int		nScreenHLineType;		///< ¼öÆò´«±ÝÀÚ Å¸ÀÔ(solid, dot...)
	int		nScreenHLineWeight;		///< ¼öÆò´«±ÝÀÚ ±½±â
	COLORREF crScreenHLineColor;	///< ¼öÆò´«±ÝÀÚ »ö
	BOOL	bScreenHBackward;		///< ¼öÆò´«±ÝÀÚ È­¸é µÚ¿¡ Ç¥½ÃÇÒÁöÀÇ ¿©ºÎ

	COLORREF crScreenHLineFillColor;	///< ¼öÆò´«±ÝÀÚ Fill »ö

	BOOL	bScreenVertical;		///< ¼öÁ÷´«±ÝÀÚ »ç¿ë¿©ºÎ
	int		nScreenVLineType;		///< ¼öÁ÷´«±ÝÀÚ Å¸ÀÔ(solid, dot...)
	int		nScreenVLineWeight;		///< ¼öÁ÷´«±ÝÀÚ ±½±â
	COLORREF crScreenVLineColor;	///< ¼öÁ÷´«±ÝÀÚ »ö
	BOOL	bScreenVBackward;		///< ¼öÁ÷´«±ÝÀÚ È­¸é µÚ¿¡ Ç¥½ÃÇÒÁöÀÇ ¿©ºÎ	
	BOOL	bDataGapCorrect;		///< DataGapº¸Á¤	
	BOOL	bDataOff;				///< ¼öÁ¤ÁÖ°¡º¸Á¤
	BOOL	bDataLimit;				///< »ó/ÇÏÇÑ°¡Ç¥½Ã
	BOOL	bDataOption;			///< ¿É¼ÇÇà»ç°¡Ç¥½Ã	

	tagST_PROPERTY_SCREEN_TEMP()
	{
		bHeadBarShow		= FALSE;
		bFootBarShow		= FALSE;
		bSideBarShow		= FALSE;
		bSideToolBarShow	= FALSE;
		bDataGridBarShow	= FALSE;
		//stQueryTypeInfo[10];
		nScreenBKType		= 0;
		crBKColor			= 0;
		*szWallPaperPath	= 0x00;	
		bScreenHorizon		= FALSE;
		nScreenHLineType	= 0;
		nScreenHLineWeight	= 0;
		crScreenHLineColor	= 0;
		bScreenHBackward	= FALSE;

		crScreenHLineFillColor = 0;

		bScreenVertical		= FALSE;
		nScreenVLineType	= 0;
		nScreenVLineWeight	= 0;
		crScreenVLineColor	= 0;
		bScreenVBackward	= FALSE;
		bDataGapCorrect		= FALSE;
		bDataOff			= FALSE;
		bDataLimit			= FALSE;
		bDataOption			= FALSE;
	}
	~tagST_PROPERTY_SCREEN_TEMP()
	{
	}

} ST_PROPERTY_SCREEN_TEMP,*LPST_PROPERTY_SCREEN_TEMP;
#define ST_PROPERTY_SCREEN_TEMP_SIZE sizeof(tagST_PROPERTY_SCREEN_TEMP)

//GlobalTemp Struct
typedef struct tagST_PROPERTY_GLOBAL_TEMP
{
	TCHAR	szFontName[30];			///< ÆùÆ®ÀÌ¸§
	int		nFontStyle;				///< ÆùÆ®½ºÅ¸ÀÏ(0:º¸Åë,1:±½°Ô,2:±â¿ïÀÓ,3:±½°Ô±â¿ïÀÓ)
	int		nFontSize;				///< ÆùÆ®»çÀÌÁî
	COLORREF crFontColor;			///< ÆùÆ®ÄÃ·¯
	BOOL	bFontFixStyle;			///< °íÁ¤/°¡º¯ ¿©ºÎ
	BOOL	bMaxMinRatio;			///< ÃÖ°í/ÃÖÀú°¡´ëºñ Ç¥½Ã
	BOOL	bShowComparison;		//´ëºñ Ç¥½Ã - ÇöÀç °Å·¡·®ÁöÇ¥´Â Á¦¿Ü
	BOOL	b3DEffect;				///< 3DÈ¿°ú
	BOOL	bAnsContinue;			///< Â÷Æ®ºÐ¼®Åø ¿¬¼Ó±×¸®±â
	BOOL	bShowToolTip;			///< ÅøÆÁ º¸¿©ÁÙÁöÀÇ ¿©ºÎ
	BOOL	bRegionSelected;		///< Â÷Æ®¿µ¿ª ¼±ÅÃÇ¥½Ã

	int		nTitleDisplayDirect;	///< ¼öÆò/¼öÁ÷ Å¸ÀÌÆ² Ç¥½Ã
	int		nTitleDisplayType;		///< Title ¼öÄ¡Á¶È­(0:¸¶¿ì½ºÀÌµ¿½Ã ÀÚµ¿,1:¸¶¿ì½º Å¬¸®½Ã ¼öÄ¡Á¶È¸,2:¸¶Áö¸· Á¾°¡¸¸)
	int		nBongInterval;			///< ºÀ°£°Ý
	int		nChtMarginSize;			///< Â÷Æ®¿©¹é¿µ¿ª

	BOOL	bChtZoneMoving;			///< Â÷Æ® ¿µ¿ªÀâ°í ÀÌµ¿ ½ºÅ©·Ñ
	BOOL	bReturnRegionExpand;	///< ±¸°£È®´ë½Ã µÇµ¹¸²±â´É

	tagST_PROPERTY_GLOBAL_TEMP()
	{
		*szFontName			= 0x00;
		nFontStyle			= 0;
		nFontSize			= 0;
		crFontColor			= 0;
		bFontFixStyle		= FALSE;
		bMaxMinRatio		= FALSE;
		bShowComparison		= FALSE;
		b3DEffect			= FALSE;
		bAnsContinue		= FALSE;
		bShowToolTip		= FALSE;
		bRegionSelected		= FALSE;
		nTitleDisplayDirect	= 0;
		nTitleDisplayType	= 0;
		nBongInterval		= 0;
		nChtMarginSize		= 0;
		bChtZoneMoving		= FALSE;
		bReturnRegionExpand	= FALSE;
	}
	~tagST_PROPERTY_GLOBAL_TEMP()
	{
	}

} ST_PROPERTY_GLOBAL_TEMP,*LPST_PROPERTY_GLOBAL_TEMP;
#define ST_PROPERTY_GLOBAL_TEMP_SIZE sizeof(tagST_PROPERTY_GLOBAL_TEMP)

// PriceTemp Struct
typedef struct tagST_PROPERTY_PRICE_TEMP
{
	int		 nPrcType;				///< Price(Main)Â÷Æ® Å¸ÀÔ (G_PRCCHT_CANDLE,...)

	COLORREF crPrcUpLine;			///< »ó½Â ¶óÀÎ»ö
	BOOL	 bPrcUpFill;			///< »ó½Â ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crPrcUpBody;			///< »ó½Â ºÀ¸öÃ¼»ö
	COLORREF crPrcDownLine;			///< ÇÏ¶ô ¶óÀÎ»ö
	BOOL	 bPrcDownFill;			///< ÇÏ¶ô ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crPrcDownBody;			///< ÇÏ¶ô ºÀ¸öÃ¼»ö

	COLORREF crPrcOffLine;			///< ¸Å¹°´ë ¶óÀÎ»ö
	BOOL	 bPrcOffFill;			///< ¸Å¹°´ë ºÀ¸öÃ¼»öÀ» Ã¤¿ïÁöÀÇ ¿©ºÎ
	COLORREF crPrcOffBody;			///< ¸Å¹°´ë ºÀ¸öÃ¼»ö

	int		nDataType;				///< °¡°Ý µ¥ÀÌÅÍ(½Ã,°í,Àú,Á¾, ½Ã°íÀúÁ¾,...)
	COLORREF crLineColor;			///< ¶óÀÎ»ö
	int		nLineStyle;				///< ¶óÀÎ½ºÅ¸ÀÏ
	int		nLineWeight;			///< ¶óÀÎ±¼±â

	int		nDefineBase;			///< ¾çºÀ±âÁØ(´çÀÏÁ¾°¡>´çÀÏ½Ã°¡, ´çÀÏÁ¾°¡>ÀüÀÏÁ¾°¡, ´çÀÏÁ¾°¡>±âÁØ°¡)
									///< ´ÙÁß¸Þ¹°Â÷Æ®¿¡¼± ¸Å¹°½Ã°£À¸·Î »ç¿ë
	double	dBaseValue;				///< ¾çºÀ±âÁØ°¡(´çÀÏÁ¾°¡>±âÁØ°¡ÀÇ ±âÁØ°¡)

	BOOL	bLastPrevLine;			///< ÀüÀÏÁ¾°¡¼± Ç¥½Ã ¿©ºÎ
	COLORREF crLastPrevLine;		///< ÀüÀÏÁ¾°¡¼±»ö
	int		nPrevLineStyle;			///< ÀüÀÏÁ¾°¡¼± ½ºÅ¸ÀÏ
	int		nPrevLineWeight;		///< ÀüÀÏÁ¾°¡¼± ±½±â

	BOOL	bMaxMinDisplay;			///< ÃÖ´ë/ÃÖ¼Ò°ª Ç¥½Ã
	BOOL	bLogScale;				///< ·Î±×Â÷Æ®
	BOOL	bInvertScale;			///< ¿ª»óÂ÷Æ®
	BOOL	bTitleShow;				///< Å¸ÀÌÆ²º¸±â
	BOOL	bGradationShow;			///< GradationÈ¿°ú

	BOOL	bAutoOffering;			///< ÀÚµ¿ ¸Å¹°´ë ¿©ºÎ
	int		nOfferingCount;			///< ¸Å¹°ÁöÁ¤ °¹¼ö
	double  dIndexValue1;			///< Price(Main)Â÷Æ®º° ÇÊ¿ä°ª(¿¹:¾ÐÃàÂ÷Æ®ÀÇ ¾ÐÃàºñÀ², SyncOverlapÂ÷Æ®ÀÇ °è»ê¹æ½Ä)
	double  dIndexValue2;			///< Price(Main)Â÷Æ®º° ÇÊ¿ä°ª2(¿¹:SyncOverlapÂ÷Æ®ÀÇ ±×¸®±â¹æ½Ä)

	//2005/03/07 - ¿¬»ê Â÷Æ®¶§¹®¿¡ »õ·Î Ãß°¡µÈ ºÎºÐ
	int		nCalcInfo;
	TCHAR	chCalcInfo[30];
	TCHAR	chMainStCode[30];
	TCHAR	chSub1StCode[30];
	TCHAR	chSub2StCode[30];

	tagST_PROPERTY_PRICE_TEMP()
	{
		nPrcType			= 0;
		crPrcUpLine			= 0;
		bPrcUpFill			= FALSE;
		crPrcUpBody			= 0;
		crPrcDownLine		= 0;
		bPrcDownFill		= FALSE;
		crPrcDownBody		= 0;
		crPrcOffLine		= 0;
		bPrcOffFill			= FALSE;
		crPrcOffBody		= 0;
		nDataType			= 0;
		crLineColor			= 0;
		nLineStyle			= 0;
		nLineWeight			= 0;
		nDefineBase			= 0;
		dBaseValue			= 0.0;
		bLastPrevLine		= FALSE;
		crLastPrevLine		= 0;
		nPrevLineStyle		= 0;
		nPrevLineWeight		= 0;
		bMaxMinDisplay		= FALSE;
		bLogScale			= FALSE;
		bInvertScale		= FALSE;
		bTitleShow			= FALSE;
		bGradationShow		= FALSE;
		bAutoOffering		= FALSE;
		nOfferingCount		= 0;
		dIndexValue1		= 0.0;
		dIndexValue2		= 0.0;
		nCalcInfo			= 0;
		*chCalcInfo			= 0x00;
		*chMainStCode		= 0x00;
		*chSub1StCode		= 0x00;
		*chSub2StCode		= 0x00;
	}
	~tagST_PROPERTY_PRICE_TEMP()
	{
	}

} ST_PROPERTY_PRICE_TEMP,*LPST_PROPERTY_PRICE_TEMP;
#define ST_PROPERTY_PRICE_TEMP_SIZE sizeof(tagST_PROPERTY_PRICE_TEMP)

//MiniChart Property Struct
typedef struct tagST_PROPERTY_MINI
{	
	int		 nPrcChtType;

	// »ó½Â
	COLORREF crPrcUpLine;
	BOOL	 bPrcUpFill;
	COLORREF crPrcUpBody;	
	// ÇÏ¶ô
	COLORREF crPrcDownLine;
	BOOL	 bPrcDownFill;
	COLORREF crPrcDownBody;
	// º¸ÇÕ
	COLORREF crPrcFlat;
	BOOL	 bPrcFlat;
	// °Å·¡·®
	COLORREF crPrcOffLine;
	BOOL	 bPrcOffFill;
	COLORREF crPrcOffBody;
	// ¶óÀÎ
	COLORREF crLineColor;	// »ö»ó
	int		nLineStyle;		// ¸ð¾ç
	int		nLineWeight;	// ±½±â

	BOOL	bMaxMinDisplay;	// MinMax
	BOOL	bTitleShow;		// Title

	// È­¸é¼³Á¤
	COLORREF crBKColor;
	COLORREF crFontColor;
	BOOL	bScreenHorizon;			// ¼öÆòGridLine
	BOOL	bScreenVertical;		// ¼öÁ÷GridLine
	BOOL	bToolTipShow;			// ToolTip

	// XÃà¼³Á¤
	BOOL	bShowFirstData;			//XÃà Ã³À½ µ¥ÀÌÅÍ º¸±â
	BOOL	bShowLastData;			//XÃà ¸¶Áö¸· µ¥ÀÌÅÍ º¸±â
	int		nXAxisSpace;			//XÃà °ø°£ºñ¿ì±â

	// YÃà¼³Á¤
	TCHAR   szIndexNameList[G_MAX_IDX_PER_CHART][30];	// ÇöÀç Zone¿¡ IndexList - ¼ø¼­´ë·Î 	
	int		nDecimalDepress[G_MAX_IDX_PER_CHART];		// 10Áø´ÜÀ§ Ãà¾à
	int		nFloatingPoint[G_MAX_IDX_PER_CHART];		// ¼Ò¼ýÁ¡ ´ÜÀ§ Ç¥½Ã	
	int		nYScaleShowType[G_MAX_IDX_PER_CHART];		// YÃà Label
	BOOL	bThousandComma[G_MAX_IDX_PER_CHART];		// Ãµ´ÜÀ§½°Ç¥

	float	fYScaleRatioUpper;		// À­ÂÊ³ôÀÌ ºñÀ²
	float	fYScaleRatioLower;		// ¾Æ·§ÂÊ³ôÀÌ ºñÀ²
	int		nYAxisShowType;			// YÃà³ôÀÌºñÀ²(0:Both,1:Left,2:Right,3:None)

	//	Gen¿¡¼­¸¸ »ç¿ë	
	BOOL	bRequestAllData[8];		//ÀüÃ¼Data¿ä±¸
	int		nRequestCount[8];		//Á¶È¸DataCount
	int		nChtViewCount[8];		//ChartViewCount
	BOOL	bModifiedData;			//¼öÁ¤ÁÖ°¡
	BOOL	bYZoneOverlap;			//YÃàOverlap

	BOOL	bYDaebiRatio;			//YÃà´ëºñÀ² show/hide

	tagST_PROPERTY_MINI()
	{
		nPrcChtType			= 0;
		
		crPrcUpLine			= 0;
		bPrcUpFill			= FALSE;
		crPrcUpBody			= 0;

		crPrcDownLine		= 0;
		bPrcDownFill		= FALSE;
		crPrcDownBody		= 0;

		crPrcFlat			= 0;
		bPrcFlat			= FALSE;

		crPrcOffLine		= 0;
		bPrcOffFill			= FALSE;
		crPrcOffBody		= 0;

		crLineColor			= 0;
		nLineStyle			= 0;
		nLineWeight			= 0;

		bMaxMinDisplay		= FALSE;
		bTitleShow			= FALSE;

		crBKColor			= 0;
		crFontColor			= 0;
		bScreenHorizon		= FALSE;
		bScreenVertical		= FALSE;
		bToolTipShow		= FALSE;

		bShowFirstData		= FALSE;
		bShowLastData		= FALSE;
		nXAxisSpace			= 0;

		memset(szIndexNameList, 0x00, sizeof(TCHAR)*G_MAX_IDX_PER_CHART*30);
		memset(nDecimalDepress, 0, sizeof(int)*G_MAX_IDX_PER_CHART);
		memset(nFloatingPoint, 0, sizeof(int)*G_MAX_IDX_PER_CHART);
		memset(nYScaleShowType, 0, sizeof(int)*G_MAX_IDX_PER_CHART);
		memset(bThousandComma, 0, sizeof(BOOL)*G_MAX_IDX_PER_CHART);

		/*szIndexNameList = new TCHAR[G_MAX_IDX_PER_CHART][30];
		nDecimalDepress = new int[G_MAX_IDX_PER_CHART];
		nFloatingPoint = new int[G_MAX_IDX_PER_CHART];
		nYScaleShowType = new int[G_MAX_IDX_PER_CHART];
		bThousandComma = new int[G_MAX_IDX_PER_CHART];*/
		
		fYScaleRatioUpper	= 0.40f;	// 0.45f;
		fYScaleRatioLower	= 0.40f;	// 0.48f;
		nYAxisShowType		= 0;
		
		memset(bRequestAllData, 0, sizeof(BOOL)*8);
		memset(nRequestCount, 0, sizeof(int)*8);
		memset(nChtViewCount, 0, sizeof(int)*8);
		bModifiedData		= FALSE;
		bYZoneOverlap		= FALSE;

		bYDaebiRatio		= TRUE;
	}
	~tagST_PROPERTY_MINI()
	{
	}

} ST_PROPERTY_MINI,*LPST_PROPERTY_MINI;
#define ST_PROPERTY_MINI_SIZE sizeof(tagST_PROPERTY_MINI)

//MiniChart Script Property Struct
typedef struct tagST_PROPERTY_MINISCRIPT
{	
	int		 nRegionNumber;
	int		 nChtKindType;

	TCHAR 	 chChtStCode[30];
	TCHAR 	 chChtCodeName[30];
	TCHAR 	 chChtItemName[30];
	int		 nChtDrawType;			//PriceÀÏ °æ¿ì - PrcType,°Å·¡·®ÀÏ°æ¿ì - Bar,Line...±×¿Ü ÁöÇ¥-DB ReadingÈÄ Setting	
	int		 nFloatingPoint;

	tagST_PROPERTY_MINISCRIPT()
	{
		nRegionNumber	= 0;
		nChtKindType	= 0;
		*chChtStCode	= 0x00;
		*chChtCodeName	= 0x00;
		*chChtItemName	= 0x00;
		nChtDrawType	= 0;
		nFloatingPoint	= 0;
	}
	~tagST_PROPERTY_MINISCRIPT()
	{
	}
} ST_PROPERTY_MINISCRIPT,*LPST_PROPERTY_MINISCRIPT;

#define ST_PROPERTY_MINISCRIPT_SIZE sizeof(tagST_PROPERTY_MINISCRIPT)

typedef struct tagST_PROPERTY_MINISCRIPT_EX
{	
	int		 nRegionIndex;	
	float	 fRegionFromRatio;		//0.0
	float	 fRegionToRatio;		//30.5

	tagST_PROPERTY_MINISCRIPT_EX()
	{
		nRegionIndex		= 0;
		fRegionFromRatio	= 0.0f;
		fRegionToRatio		= 0.0f;
	}
	~tagST_PROPERTY_MINISCRIPT_EX()
	{
	}
} ST_PROPERTY_MINISCRIPT_EX,*LPST_PROPERTY_MINISCRIPT_EX;

#define ST_PROPERTY_MINISCRIPT_EX_SIZE sizeof(tagST_PROPERTY_MINISCRIPT_EX)

struct tag3DPRICLINEINFO
{
	TCHAR   chStCode[30];
	TCHAR	chStName[30];
	COLORREF crLineColor;
	BOOL	bTitleShow;
	int		nLineStyle;
	int		nLineWeight;

	tag3DPRICLINEINFO()
	{
		*chStCode	= 0x00;
		*chStName	= 0x00;
		crLineColor	= 0;
		bTitleShow	= FALSE;
		nLineStyle	= 0;;
		nLineWeight	= 0;
	}
	~tag3DPRICLINEINFO()
	{
	}
};

typedef struct tag3DPRCCHTINFO
{
	int nXZDepthRatio;
	int nYZDepthRatio;
	COLORREF crBgColor;
	COLORREF crBackColor;
	COLORREF crLeftColor;
	COLORREF crBottomColor;
	COLORREF crBoundaryColor;
	COLORREF crGridLineColor;
	COLORREF crFontColor;
	BOOL	bShowXGrid;
	BOOL	bShowYGrid;
	BOOL	bXAxisDisplay;
	BOOL	bYAxisComma;
	BOOL	bEmptyDisplay;
	BOOL	bZoneBoundary;
	BOOL	bOnly3DAxisLine;
	BOOL	bAxisExtend;
	int		n3DPrcLineCount;
	tag3DPRICLINEINFO st3DPrcInfoList[10];		//Max10°³

	tag3DPRCCHTINFO()
	{
		nXZDepthRatio		= 0;
		nYZDepthRatio		= 0;
		crBgColor			= 0;
		crBackColor			= 0;
		crLeftColor			= 0;
		crBottomColor		= 0;
		crBoundaryColor		= 0;
		crGridLineColor		= 0;
		crFontColor			= 0;
		bShowXGrid			= FALSE;
		bShowYGrid			= FALSE;
		bXAxisDisplay		= FALSE;
		bYAxisComma			= FALSE;
		bEmptyDisplay		= FALSE;
		bZoneBoundary		= FALSE;
		bOnly3DAxisLine		= FALSE;
		bAxisExtend			= FALSE;
		n3DPrcLineCount		= 0;
		//st3DPrcInfoList[10];		//Max10°³
	}
	~tag3DPRCCHTINFO()
	{
	}
}ST_3DPRC_INFO,*LPST_3DPRC_INFO;
#define ST_3DPRC_INFO_SIZE sizeof(tag3DPRCCHTINFO)

//	ImageStatic		
typedef struct tagCHTData
{
	double	dDate;
	double	dOpen;
	double	dHigh;
	double	dLow;
	double	dCls;
	double	dTrdngVlm;
	CRect   rcBong;	

	tagCHTData()
	{
		dDate		= 0.0;
		dOpen		= 0.0;
		dHigh		= 0.0;
		dLow		= 0.0;
		dCls		= 0.0;
		dTrdngVlm	= 0.0;
		//rcBong;	
	}
	~tagCHTData()
	{
	}
}CHTData,*LPCHTData;
const int	G_BMPIMAGE = 1000;
const int	G_BMPCANDLE = 1001;

//ANSDrawing Tool Struct++
const int	G_ANSSELECTFUZZ = 4;		//Ãß¼¼¼±¼±ÅÃÅ©±â
const int	G_ANSSQUAREHAFSIZE = 4;		
#define		GC_PI 3.1415926535897932384626433832795
#define		GC_RADIANTODEGREE 57.2957795130823

/*==================================================================================*/
/*						GRAPH PROPERTY INFO STRUCT									*/
/*----------------------------------------------------------------------------------*/
/*														Create:2005/09/01			*/		
/*														LastUpdate:2005/09/01		*/	
/*	Comment:Base Graphs - G_PRCGRP_CANDLE,G_PRCGRP_BAR,	G_PRCGRP_UPDNBAR,	 	    */
/*						G_PRCGRP_GROUPUPDNBAR,G_PRCGRP_LINE,G_PRCGRP_STAIRS,		*/
/*						G_PRCGRP_PERIOD,G_PRCGRP_MOUNTAIN,G_PRCGRP_RISEFALL,		*/
/*						G_PRCGRP_VERTICALBAR										*/
/*==================================================================================*/
//
typedef struct tagST_PROPERTY_GRAPH_BASE
{	
	// ±×·¡ÇÁ °øÅë ¼Ó¼º-->
	BOOL	bTitleShow;			///< Title º¸±â	
	BOOL	bMaxMinDisplay;		///< ÃÖ´ë/ÃÖ¼Ò°ª º¸±â
	BOOL	bDrawGradient;		///< Gradation
	BOOL	bShowCircle;		///< Line,Period¿¡¼­ CircleÇ¥½Ã

	COLORREF crBKColor;			///< ±×·¡ÇÁ ¹è°æ»ö
	COLORREF crFontColor;		///< ±×·¡ÇÁ ±Û²Ã»ö
	COLORREF crGridColor;		///< ±×·¡ÇÁ ´«±Ý»ö

	BOOL	bScreenHorizon;		///< ¼öÆò´«±Ý º¸ÀÌ±â
	BOOL	bScreenVertical;	///< ¼öÁ÷´«±Ý º¸ÀÌ±â

	int		nDecimalDepress;	///< ´ÜÀ§Ãà¾à
	int		nFloatingPoint;		///< ¼Ò¼öÁ¡

	float	fYScaleRatio;		///< Y³ôÀÌºñÀ²
	int		nYAxisShowType;		///< ÀüÃ¼ YÃà º¸±â Å¸ÀÔ(¾øÀ½,¿ÞÂÊ,¿À¸¥ÂÊ,¾çÂÊ)
	// ±×·¡ÇÁ °øÅë ¼Ó¼º<--

	// Index ¼Ó¼º-->
	BOOL	 bPrcUpFill;		///< »ó½Â ¸öÅë»ö »ç¿ë¿©ºÎ
	COLORREF crPrcUpLine;		///< »ó½Â ¶óÀÎ»ö
	COLORREF crPrcUpBody;		///< »ó½Â ¸öÅë»ö

	BOOL	 bPrcDownFill;		///< ÇÏ¶ô ¸öÅë»ö »ç¿ë¿©ºÎ
	COLORREF crPrcDownLine;		///< ÇÏ¶ô ¶óÀÎ»ö
	COLORREF crPrcDownBody;		///< ÇÏ¶ô ¸öÅë»ö

	COLORREF crLineColor;		///< ÀÏ¹Ý ¶óÀÎ»ö
	int		nLineStyle;			///< ÀÏ¹Ý ¶óÀÎ ½ºÅ¸ÀÏ
	int		nLineWeight;		///< ÀÏ¹Ý ¶óÀÎ ±½±â
	// Index ¼Ó¼º<--

	tagST_PROPERTY_GRAPH_BASE()
	{
		crPrcUpLine			= 0;
		bPrcUpFill			= FALSE;
		crPrcUpBody			= 0;
		crPrcDownLine		= 0;
		bPrcDownFill		= FALSE;
		crPrcDownBody		= 0;
		crLineColor			= 0;
		nLineStyle			= 0;
		nLineWeight			= 0;
		bDrawGradient		= FALSE;
		bShowCircle			= FALSE;
		bMaxMinDisplay		= FALSE;
		bTitleShow			= FALSE;
		nDecimalDepress		= 0;
		nFloatingPoint		= 0;
		fYScaleRatio		= 0.0f;
		nYAxisShowType		= 0;
		crBKColor			= 0;
		crFontColor			= 0;
		crGridColor			= 0;
		bScreenHorizon		= FALSE;
		bScreenVertical		= FALSE;
	}
	~tagST_PROPERTY_GRAPH_BASE()
	{
	}
} ST_PROPERTY_GRAPH_BASE,*LPST_PROPERTY_GRAPH_BASE;
#define ST_PROPERTY_GRAPH_BASE_SIZE sizeof(tagST_PROPERTY_GRAPH_BASE)
/*----------------------------------------------------------------------------------*/
/*														Create:2005/09/01			*/		
/*														LastUpdate:2005/09/01		*/	
/*	Comment:Group Graphs -  G_PRCGRP_STACKBAR,G_PRCGRP_BAR,		 					*/
/*							G_PRCGRP_GROUPBAR,G_PRCGRP_GROUPVERTBAR					*/
/*==================================================================================*/
//
typedef struct tagST_PROPERTY_GRAPH_GROUP
{	
	// ±×·¡ÇÁ °øÅë ¼Ó¼º-->
	BOOL	bTitleShow;								///< Title º¸±â	
	BOOL	bMaxMinDisplay;							///< ÃÖ´ë/ÃÖ¼Ò°ª º¸±â
	BOOL	bDrawGradient;							///< Gradation

	COLORREF crBKColor;								///< ±×·¡ÇÁ ¹è°æ»ö
	COLORREF crFontColor;							///< ±×·¡ÇÁ ±Û²Ã»ö
	COLORREF crGridColor;							///< ±×·¡ÇÁ ´«±Ý»ö

	BOOL	bScreenHorizon;							///< ¼öÆò´«±Ý º¸ÀÌ±â
	BOOL	bScreenVertical;						///< ¼öÁ÷´«±Ý º¸ÀÌ±â

	int		nDecimalDepress;						///< ´ÜÀ§Ãà¾à
	int		nFloatingPoint;							///< ¼Ò¼öÁ¡

	float	fYScaleRatio;							///< Y³ôÀÌºñÀ²
	int		nYAxisShowType;							///< ÀüÃ¼ YÃà º¸±â Å¸ÀÔ(¾øÀ½,¿ÞÂÊ,¿À¸¥ÂÊ,¾çÂÊ)
	// ±×·¡ÇÁ °øÅë ¼Ó¼º<--

	// ±×·ì ¼Ó¼º-->
	int		 nGroupDataCount;						///< ±×·ì °¹¼ö
	TCHAR    szGroupNameList[G_MAXGROUPDATA][30];	///< ±×·ì¸í
	COLORREF crGroupLineList[G_MAXGROUPDATA];		///< ±×·ì ¶óÀÎ»ö
	COLORREF crGroupBodyList[G_MAXGROUPDATA];		///< ±×·ì ¸öÅë»ö
	BOOL	 bGroupFillList[G_MAXGROUPDATA];		///< ±×·ì ¸öÅë»ö Ã¤¿ò ¿©ºÎ
	// ±×·ì ¼Ó¼º<--

	tagST_PROPERTY_GRAPH_GROUP()
	{
		nGroupDataCount		= 0;
		memset(szGroupNameList, 0x00, sizeof(TCHAR)*G_MAXGROUPDATA*30);
		memset(crGroupLineList, 0, sizeof(COLORREF)*G_MAXGROUPDATA);
		memset(crGroupBodyList, 0, sizeof(COLORREF)*G_MAXGROUPDATA);
		memset(bGroupFillList, 0, sizeof(BOOL)*G_MAXGROUPDATA);
		bMaxMinDisplay		= FALSE;
		bTitleShow			= FALSE;
		nDecimalDepress		= 0;
		nFloatingPoint		= 0;
		bDrawGradient		= FALSE;
		fYScaleRatio		= 0.0f;
		nYAxisShowType		= 0;
		crBKColor			= 0;
		crFontColor			= 0;
		crGridColor			= 0;
		bScreenHorizon		= FALSE;
		bScreenVertical		= FALSE;
	}
	~tagST_PROPERTY_GRAPH_GROUP()
	{
	}
} ST_PROPERTY_GRAPH_GROUP,*LPST_PROPERTY_GRAPH_GROUP;
#define ST_PROPERTY_GRAPH_GROUP_SIZE sizeof(tagST_PROPERTY_GRAPH_GROUP)

/*----------------------------------------------------------------------------------*/
/*														Create:2005/09/01			*/		
/*														LastUpdate:2005/09/01		*/	
/*	Comment:Scatter Graphs -  G_PRCGRP_SCATTER,G_PRCGRP_BUBBLE	 					*/
/*==================================================================================*/
//
typedef struct tagST_PROPERTY_GRAPH_SCATTER
{	
	// ±×·¡ÇÁ °øÅë ¼Ó¼º-->
	BOOL	bTitleShow;				///< ¼±ÇüÈ¸±Í¼± Title º¸±â
	BOOL	bMaxMinDisplay;			///< ÃÖ´ë/ÃÖ¼Ò°ª º¸±â
	BOOL	bNameShow;				///< Scatter ÀÌ¸§ º¸±â

	COLORREF crBKColor;				///< ±×·¡ÇÁ ¹è°æ»ö
	COLORREF crFontColor;			///< ±×·¡ÇÁ ±Û²Ã»ö
	COLORREF crGridColor;			///< ±×·¡ÇÁ ´«±Ý»ö

	BOOL	bScreenHorizon;			///< ¼öÆò´«±Ý º¸ÀÌ±â
	BOOL	bScreenVertical;		///< ¼öÁ÷´«±Ý º¸ÀÌ±â

	int		nDecimalDepress;		///< ´ÜÀ§Ãà¾à
	int		nFloatingPoint;			///< ¼Ò¼öÁ¡

	float	fYScaleRatio;			///< Y³ôÀÌºñÀ²
	int		nYAxisShowType;			///< ÀüÃ¼ YÃà º¸±â Å¸ÀÔ(¾øÀ½,¿ÞÂÊ,¿À¸¥ÂÊ,¾çÂÊ)

	BOOL	bShowLinearLine;		///< ¼±ÇüÈ¸±Í¼± º¸ÀÌ±â
	
	//		Base¼öÁ÷,¼öÆò¼±
	BOOL	bShowHorizonLine;		///< ¼öÆò¼± º¸ÀÌ±â
	double  dBaseHorizon;			///< ¼öÆò¼± °ª
	COLORREF crBaseHorizon;			///< ¼öÆò¼± »ö»ó
	int		nHorizonStyle;			///< ¼öÆò¼± ½ºÅ¸ÀÏ
	int		nHorizonWeight;			///< ¼öÆò¼± ±½±â

	BOOL	bShowVerticalLine;		///< ¼öÁ÷¼± º¸ÀÌ±â
	double  dBaseVertical;			///< ¼öÁ÷¼± °ª
	COLORREF crBaseVertical;		///< ¼öÁ÷¼± »ö»ó
	int		nVerticalStyle;			///< ¼öÁ÷¼± ½ºÅ¸ÀÏ
	int		nVerticalWeight;		///< ¼öÁ÷¼± ±½±â
	// ±×·¡ÇÁ °øÅë ¼Ó¼º<--

	// Index ¼Ó¼º-->
	COLORREF crScatterColor;		///< Scatter »ö»ó
	int		nScatterType;			///< Scatter Ç¥Çö¹æ½Ä

	COLORREF crLinearReg;			///< ¼±ÇüÈ¸±Í¼± »ö»ó
	int		nLinearRegStyle;		///< ¼±ÇüÈ¸±Í¼± ½ºÅ¸ÀÏ(PS_SOLID,...)
	int		nLinearRegWeight;		///< ¼±ÇüÈ¸±Í¼± ±½±â
	// Index ¼Ó¼º<--

	tagST_PROPERTY_GRAPH_SCATTER()
	{
		bTitleShow			= FALSE;	
		bMaxMinDisplay		= FALSE;
		bNameShow			= FALSE;
		crScatterColor		= 0;
		nScatterType		= 0;
		crLinearReg			= 0;
		nLinearRegStyle		= 0;
		nLinearRegWeight	= 0;
		nDecimalDepress		= 0;
		nFloatingPoint		= 0;
		fYScaleRatio		= 0.0f;
		nYAxisShowType		= 0;
		bShowLinearLine		= FALSE;
		crBKColor			= 0;
		crFontColor			= 0;
		crGridColor			= 0;
		bShowHorizonLine	= FALSE;
		bShowVerticalLine	= FALSE;
		dBaseHorizon		= 0.0;
		dBaseVertical		= 0.0;
		crBaseHorizon		= 0;
		nHorizonStyle		= 0;
		nHorizonWeight		= 0;
		crBaseVertical		= 0;
		nVerticalStyle		= 0;
		nVerticalWeight		= 0;
		bScreenHorizon		= FALSE;
		bScreenVertical		= FALSE;
	}
	~tagST_PROPERTY_GRAPH_SCATTER()
	{
	}
} ST_PROPERTY_GRAPH_SCATTER,*LPST_PROPERTY_GRAPH_SCATTER;
#define ST_PROPERTY_GRAPH_SCATTER_SIZE sizeof(tagST_PROPERTY_GRAPH_SCATTER)

/*----------------------------------------------------------------------------------*/
/*														Create:2005/09/01			*/		
/*														LastUpdate:2005/09/01		*/	
/*	Comment:Radar Graphs -  G_PRCGRP_RADAR,G_PRCGRP_SPIDER							*/
/*==================================================================================*/
//
typedef struct tagST_PROPERTY_GRAPH_RADAR
{	
	// ±×·¡ÇÁ °øÅë ¼Ó¼º-->
	BOOL	bTitleShow;								///< Title º¸±â	
	BOOL	bTextLabelShow;							///< Text Label º¸ÀÌ±â

	COLORREF crBKColor;								///< ±×·¡ÇÁ ¹è°æ»ö
	COLORREF crFontColor;							///< ±×·¡ÇÁ ±Û²Ã»ö
	COLORREF crGridColor;							///< ±×·¡ÇÁ ´«±Ý»ö

	int		nDecimalDepress;						///< ´ÜÀ§Ãà¾à
	int		nFloatingPoint;							///< ¼Ò¼öÁ¡

	BOOL	bRadarGradient;							///< ·¹ÀÌ´õ Gradation
	COLORREF crRadarBack;							///< ·¹ÀÌ´õ ¹è°æ»ö
	BOOL	bRadarYScaleLineShow;					///< ·¹ÀÌ´õ YÃà ¶óÀÎ º¸ÀÌ±â

	// ±×·¡ÇÁ °øÅë ¼Ó¼º<--

	// ±×·ì ¼Ó¼º-->
	int		nGroupDataCount;						///< ±×·ì °¹¼ö
	TCHAR    szGroupNameList[G_MAXGROUPDATA][30];	///< ±×·ì¸í
	COLORREF crGroupLineList[G_MAXGROUPDATA];		///< ±×·ì ¶óÀÎ»ö
	int		 nGroupLineStyle[G_MAXGROUPDATA];		///< ±×·ì ¶óÀÎ ½ºÅ¸ÀÏ
	int		 nGroupLineWeight[G_MAXGROUPDATA];		///< ±×·ì ¶óÀÎ ±½±â
	// ±×·ì ¼Ó¼º<--

	tagST_PROPERTY_GRAPH_RADAR()
	{
		bTitleShow		= FALSE;
		bTextLabelShow	= FALSE;
		nGroupDataCount	= 0;
		memset(szGroupNameList, 0x00, sizeof(TCHAR)*G_MAXGROUPDATA*30);
		memset(crGroupLineList, 0, sizeof(COLORREF)*G_MAXGROUPDATA);
		memset(nGroupLineStyle, 0, sizeof(int)*G_MAXGROUPDATA);
		memset(nGroupLineWeight, 0, sizeof(int)*G_MAXGROUPDATA);
		nDecimalDepress	= 0;
		nFloatingPoint	= 0;
		crRadarBack	= 0;
		bRadarGradient	= FALSE;
		bRadarYScaleLineShow	= FALSE;
		crBKColor		= 0;
		crFontColor		= 0;
		crGridColor		= 0;
	}
	~tagST_PROPERTY_GRAPH_RADAR()
	{
	}
} ST_PROPERTY_GRAPH_RADAR,*LPST_PROPERTY_GRAPH_RADAR;
#define ST_PROPERTY_GRAPH_RADAR_SIZE sizeof(tagST_PROPERTY_GRAPH_RADAR)

/*----------------------------------------------------------------------------------*/
/*														Create:2005/09/01			*/		
/*														LastUpdate:2005/09/01		*/	
/*	Comment:Pie Graphs -  G_PRCGRP_PIE,G_PRCGRP_CIRCLE								*/
/*==================================================================================*/
//
typedef struct tagST_PROPERTY_GRAPH_PIE
{	
	// ±×·¡ÇÁ °øÅë ¼Ó¼º-->
	BOOL	bTitleShow;								///< Title º¸±â	
	BOOL	bTextLabelShow;							///< Text Label º¸ÀÌ±â

	COLORREF crBKColor;								///< ±×·¡ÇÁ ¹è°æ»ö
	COLORREF crFontColor;							///< ±×·¡ÇÁ ±Û²Ã»ö

	int		nDecimalDepress;						///< ´ÜÀ§Ãà¾à
	int		nFloatingPoint;							///< ¼Ò¼öÁ¡

	BOOL	bShowDonutPie;							///< µµ³ÊÃ÷ ¸ð¾ç º¸ÀÓ ¿©ºÎ
	double  dDonutRatio;							///< µµ³ÊÃ÷ ºñÀ²

	BOOL	bSlicePie;								///< Slice Pie(¾ÆÁ÷ ±¸Çö ¾ÈµÊ)
	// ±×·¡ÇÁ °øÅë ¼Ó¼º<--

	// ±×·ì ¼Ó¼º-->
	int		nGroupDataCount;						///< ±×·ì °¹¼ö
	TCHAR    szGroupNameList[G_MAXGROUPDATA][30];	///< ±×·ì¸í
	COLORREF crGroupLineList[G_MAXGROUPDATA];		///< ±×·ì ¶óÀÎ»ö
	// ±×·ì ¼Ó¼º<--

	tagST_PROPERTY_GRAPH_PIE()
	{
		bTitleShow		= FALSE;
		bTextLabelShow	= FALSE;
		nGroupDataCount	= 0;
		memset(szGroupNameList, 0x00, sizeof(TCHAR)*G_MAXGROUPDATA*30);
		memset(crGroupLineList, 0, sizeof(COLORREF)*G_MAXGROUPDATA);
		nDecimalDepress	= 0;
		nFloatingPoint	= 0;
		bSlicePie		= FALSE;
		bShowDonutPie	= FALSE;
		dDonutRatio		= 0.0;
		crBKColor		= 0;
		crFontColor		= 0;
	}
	~tagST_PROPERTY_GRAPH_PIE()
	{
	}
} ST_PROPERTY_GRAPH_PIE,*LPST_PROPERTY_GRAPH_PIE;
#define ST_PROPERTY_GRAPH_PIE_SIZE sizeof(tagST_PROPERTY_GRAPH_PIE)

/*----------------------------------------------------------------------------------*/
/*														Create:2005/09/05			*/		
/*														LastUpdate:2005/09/05		*/	
/*	Comment:Math Graphs -  G_PRCGRP_PL,G_PRCGRP_SENS,G_PRCGRP_STRATEGY				*/
/*==================================================================================*/
//
typedef struct tagST_PROPERTY_GRAPH_MATH
{
	// ±×·¡ÇÁ °øÅë ¼Ó¼º-->
	BOOL	bTitleShow;				///< Title º¸±â	
	BOOL	bShowLinearLine;		///< ¼±Çü È¸±Í¼± º¸±â (ÇöÀç »ç¿ë¾ÈÇÔ 2006.11.20 Hong~)

	COLORREF crBKColor;				///< ±×·¡ÇÁ ¹è°æ»ö
	COLORREF crFontColor;			///< ±×·¡ÇÁ ±Û²Ã»ö
	COLORREF crGridColor;			///< ±×·¡ÇÁ ´«±Ý»ö

	BOOL	bScreenHorizon;			///< ¼öÆò´«±Ý º¸ÀÌ±â
	BOOL	bScreenVertical;		///< ¼öÁ÷´«±Ý º¸ÀÌ±â

	int		nDecimalDepress;		///< ´ÜÀ§Ãà¾à
	int		nFloatingPoint;			///< ¼Ò¼öÁ¡

	float	fYScaleRatio;			///< Y³ôÀÌºñÀ²
	int		nYAxisShowType;			///< ÀüÃ¼ YÃà º¸±â Å¸ÀÔ(¾øÀ½,¿ÞÂÊ,¿À¸¥ÂÊ,¾çÂÊ)
	// ±×·¡ÇÁ °øÅë ¼Ó¼º<--

	//		Base¼öÁ÷,¼öÆò¼±
	BOOL	bShowHorizonLine;		///< ¼öÆò¼± º¸ÀÌ±â
	double  dBaseHorizon;			///< ¼öÆò¼± °ª
	COLORREF crBaseHorizon;			///< ¼öÆò¼± »ö»ó
	int		nHorizonStyle;			///< ¼öÆò¼± ½ºÅ¸ÀÏ
	int		nHorizonWeight;			///< ¼öÆò¼± ±½±â

	BOOL	bShowVerticalLine;		///< ¼öÁ÷¼± º¸ÀÌ±â
	double  dBaseVertical;			///< ¼öÁ÷¼± °ª
	COLORREF crBaseVertical;		///< ¼öÁ÷¼± »ö»ó
	int		nVerticalStyle;			///< ¼öÁ÷¼± ½ºÅ¸ÀÏ
	int		nVerticalWeight;		///< ¼öÁ÷¼± ±½±â

	// ±×·ì ¼Ó¼º-->
	int		 nGroupDataCount;							///< ±×·ì °¹¼ö
	TCHAR    szGroupNameList[G_MATH_MAXGROUPDATA][30];	///< ±×·ì¸í
	COLORREF crGroupLineList[G_MATH_MAXGROUPDATA];		///< ±×·ì ¶óÀÎ»ö
	int		 nGroupLineStyle[G_MATH_MAXGROUPDATA];		///< ±×·ì ¶óÀÎ ½ºÅ¸ÀÏ
	int		 nGroupLineWeight[G_MATH_MAXGROUPDATA];		///< ±×·ì ¶óÀÎ ±½±â
	// ±×·ì ¼Ó¼º<--

	tagST_PROPERTY_GRAPH_MATH()
	{
		nGroupDataCount		= 0;
		memset(szGroupNameList, 0x00, sizeof(TCHAR)*G_MATH_MAXGROUPDATA*30);
		memset(crGroupLineList, 0, sizeof(COLORREF)*G_MATH_MAXGROUPDATA);
		memset(nGroupLineStyle, 0, sizeof(int)*G_MATH_MAXGROUPDATA);
		memset(nGroupLineWeight, 0, sizeof(int)*G_MATH_MAXGROUPDATA);
		bTitleShow			= FALSE;
		nDecimalDepress		= 0;
		nFloatingPoint		= 0;
		bShowLinearLine		= FALSE;
		crBKColor			= 0;
		crFontColor			= 0;
		crGridColor			= 0;
		bShowHorizonLine	= FALSE;
		bShowVerticalLine	= FALSE;
		dBaseHorizon		= 0.0;
		dBaseVertical		= 0.0;
		crBaseHorizon		= 0;
		nHorizonStyle		= 0;
		nHorizonWeight		= 0;
		fYScaleRatio		= 0.0f;
		nYAxisShowType		= 0;
		crBaseVertical		= 0;
		nVerticalStyle		= 0;
		nVerticalWeight		= 0;
		bScreenHorizon		= FALSE;
		bScreenVertical		= FALSE;
	}
	~tagST_PROPERTY_GRAPH_MATH()
	{
	}
} ST_PROPERTY_GRAPH_MATH,*LPST_PROPERTY_GRAPH_MATH;
#define ST_PROPERTY_GRAPH_MATH_SIZE sizeof(tagST_PROPERTY_GRAPH_MATH)
/*=================================================================*/
/*						ANS DRAWING INFO STRUCT					   */
/*=================================================================*/
//ANSDrawing Tool Struct++
typedef struct tagST_ANSPOINT_PROPERTY
{		
	int		nXPos;
	double   dYValue;
	double	dXValue;				//20040107.000000

	tagST_ANSPOINT_PROPERTY()
	{
		nXPos	= 0;
		dYValue	= 0.0;
		dXValue	= 0.0;
	}
	~tagST_ANSPOINT_PROPERTY()
	{
	}
} ST_ANSPOINT_PROPERTY,*LPST_ANSPOINT_PROPERTY;
#define ST_ANSPOINT_PROPERTY_SIZE sizeof(tagST_ANSPOINT_PROPERTY)

typedef struct tagST_ANSLINE_PROPERTY
{	
	BOOL	bLineShow;
	int		nLineStyle;
	int		nLineWeight;
	COLORREF crLineColor;

	tagST_ANSLINE_PROPERTY()
	{
		bLineShow	= FALSE;
		nLineStyle	= 0;
		nLineWeight	= 0;
		crLineColor	= 0;
	}
	~tagST_ANSLINE_PROPERTY()
	{
	}
} ST_ANSLINE_PROPERTY,*LPST_ANSLINE_PROPERTY;
#define ST_ANSLINE_PROPERTY_SIZE sizeof(tagST_ANSLINE_PROPERTY)

typedef struct tagST_ANSTOOL_PROPERTY
{		
	int		nLeftExt;			// ¿ÞÂÊÈ®Àå
	int		nRightExt;			// ¿À¸¥ÂÊÈ®Àå
	int		nFullExt;			// ÀüÃ¼È®Àå
	int		nFillRegion;		// ¿µ¿ªÃ¤¿ò
	int		nLeftRatio;			// ÁÂÃøºñÀ²
	int		nRightValue;		// ¿ìÃø°¡°Ý
	int		nFullMoving;		// ÀüÃ¼ÀÌµ¿
	int		nAnsDirect;			// DiagonalLineÀÇ °æ¿ì °¢µµ(45µµ,-45µµ)...
	int		nBLineShow;			// BaseLine - Quadrant,Tirone,Linear,...,AutoLine,...

	tagST_ANSTOOL_PROPERTY()
	{
		nLeftExt	= 0;
		nRightExt	= 0;
		nFullExt	= 0;
		nFillRegion	= 0;
		nLeftRatio	= 0;
		nRightValue	= 0;
		nFullMoving	= 0;
		nAnsDirect	= 0;
		nBLineShow	= 0;
	}
	~tagST_ANSTOOL_PROPERTY()
	{
	}
} ST_ANSTOOL_PROPERTY,*LPST_ANSTOOL_PROPERTY;
#define ST_ANSTOOL_PROPERTY_SIZE sizeof(tagST_ANSTOOL_PROPERTY)

typedef struct tagST_ANSTEXT_INFO
{
	int		nChartNo;
	int		nIndexNo;						//ÇÑ¿µ¿ª¿¡ ¿©·¯ Text°¡ÀÖÀ»°æ¿ì ±¸ºÐ
	CString strText;					//char·Î Ç¥ÇöÇÏ±â´Â Èûµé´Ù
	CRect	rcText;

	tagST_ANSTEXT_INFO()
	{
		nChartNo	= 0;
		nIndexNo	= 0;
		//strText;
		//rcText;
	}
	~tagST_ANSTEXT_INFO()
	{
	}
} ST_ANSTEXT_INFO,*LPST_ANSTEXT_INFO;
#define ST_ANSTEXT_INFO_SIZE sizeof(tagST_ANSTEXT_INFO)

typedef struct tagST_ANSSYMBOL_INFO
{
	CString			strANSText;	
	CRect			rcANSRect;			//	
	COLORREF		crSymbolColor;
	int				nSymbolIndex;
	int				nSymbolSize;

	tagST_ANSSYMBOL_INFO()
	{
		//strANSText;	
		//rcANSRect;
		crSymbolColor	= 0;
		nSymbolIndex	= 0;
		nSymbolSize		= 0;
	}
	~tagST_ANSSYMBOL_INFO()
	{
	}
} ST_ANSSYMBOL_INFO,*LPST_ANSSYMBOL_INFO;
#define ST_ANSSYMBOL_INFO_SIZE sizeof(tagST_ANSSYMBOL_INFO)	

typedef struct tagST_ANSTEXT_FONTINFO
{
	int nFontHeight;
	int nFontWeight;
	int nFontCharSet;
	COLORREF crFontColor;
	CString strFontName;

	tagST_ANSTEXT_FONTINFO()
	{
		nFontHeight		= 0;
		nFontWeight		= 0;
		nFontCharSet	= 0;
		crFontColor		= 0;
		//strFontName;
	}
	~tagST_ANSTEXT_FONTINFO()
	{
	}
} ST_ANSTEXT_FONTINFO,*LPST_ANSTEXT_FONTINFO;
#define ST_ANSTEXT_FONTINFO_SIZE sizeof(tagST_ANSTEXT_FONTINFO)

typedef struct tagST_ANSTURN_POSINFO
{
	CPoint ptPoint;
	int    nTurnDirect;
	int	   nTurnXIndex;
	double dTurnYValue;

	tagST_ANSTURN_POSINFO()
	{
		//ptPoint;
		nTurnDirect	= 0;
		nTurnXIndex	= 0;
		dTurnYValue	= 0.0;
	}
	~tagST_ANSTURN_POSINFO()
	{
	}
} ST_ANSTURN_POSINFO,*LPST_ANSTURN_POSINFO;
#define ST_ANSTURN_POSINFO_SIZE sizeof(tagST_ANSTURN_POSINFO)

/*=================================================================*/
/*						ANS DATA INFO STRUCT					   */
/*=================================================================*/
/*2004/01/10 - ±¸Ã¼ÀûÀÎ ¸ðµç Á¤º¸ Struct						   */
typedef struct tagST_ANSDATA_INFO
{
	int				nANSDrawingType;			//Class Define Const
	int				nANSChtPos;					//À§Ä¡ - Save Load ½Ã¿¡´Â Â÷Æ® À§Ä¡±îÁö Á¤È®ÇÏ°Ô ¸Â¾Æ¾ßÇÑ´Ù		
	double			dCalcRatio[12];				//Fibonacci,Gann,SpeedÀÇ Calc Ratio
	double			dSwingRatio;				//Swing Point Ratio	
	int				nANSDirect;					//Diagonal,Golden,ElliotArc	...
	int				nSnapInfo;					//Select Pos,Close Pos,High Pos,Low Pos	
	int				nSnapPos;
	//////////////////////////////////////////
	int				nPointsCount;
	LPST_ANSPOINT_PROPERTY pStAnsPointsInfo;
	int					 nLinesCount;
	LPST_ANSLINE_PROPERTY  pStAnsLinesInfo;
	//int					 nTurnPosCount;		//TurningInfo´Â Á¤º¸¸¦ º¯°æÇÏ±â ¾î·Æ´Ù	
	//LPST_ANSTURN_POSINFO pStAnsTurnPosInfo;	//¶óÀÎ Á¤º¸ ¹× ½ÃÀÛ Á¾·á Á¡¸¸ º¯°æ
	ST_ANSTOOL_PROPERTY	 cStAnsToolPropertyInfo;	
	//ST_ANSTEXT_INFO		 cStAnsTextInfo;	//Textµµ ÇÊ¿ä°¡ ¾ø´Ù
	ST_ANSTEXT_FONTINFO  cStAnsTextFontInfo;	//FontInfoµµ FontDialog¿¡¼­ ÇØ°á	
	ST_ANSSYMBOL_INFO    cStAsnSymbolInfo;		

	tagST_ANSDATA_INFO()
	{
		nANSDrawingType		= 0;
		nANSChtPos			= 0;
		memset(dCalcRatio, 0, sizeof(double)*10);
		dSwingRatio			= 0.0;
		nANSDirect			= 0;
		nSnapInfo			= 0;
		nSnapPos			= 0;
		nPointsCount		= 0;
		pStAnsPointsInfo	= NULL;
		nLinesCount			= 0;
		pStAnsLinesInfo		= NULL;
		//cStAnsToolPropertyInfo;	
		//cStAnsTextFontInfo;
		//cStAsnSymbolInfo;		
	}
	~tagST_ANSDATA_INFO()
	{
		if(pStAnsPointsInfo)
		{
			ASSERT(FALSE);
		}
		if(pStAnsLinesInfo)
		{
			ASSERT(FALSE);
		}
	}

	void Clear()
	{
		if(pStAnsPointsInfo)
		{
			delete[] pStAnsPointsInfo;
			pStAnsPointsInfo = NULL;
		}
		if(pStAnsLinesInfo)
		{
			delete[] pStAnsLinesInfo;
			pStAnsLinesInfo = NULL;
		}
	}

} ST_ANSDATA_INFO,*LPST_ANSDATA_INFO;
#define ST_ANSDATA_INFO_SIZE sizeof(tagST_ANSDATA_INFO)
//ANSDrawing Tool Struct--

/*=================================================================*/
/*						FILE HEAD INFO STRUCT					   */
/*=================================================================*/
/*IHEAD - Indicator Head										   */	
typedef struct tagST_FILEDB_HEADINFO
{	
	int nVersion;					//Ex>1000,1001
	int nDate;						//20040129
	int nFileDBCount;				//FileDB Count	
	TCHAR chDummy[8];				/* Dummy */

	tagST_FILEDB_HEADINFO()
	{
		nVersion	= 0;
		nDate		= 0;
		nFileDBCount= 0;
		*chDummy	= 0x00;
	}
	~tagST_FILEDB_HEADINFO()
	{
	}
} ST_FILEDB_HEADINFO,*LPST_FILEDB_HEADINFO;
#define ST_FILEDB_HEADINFO_SIZE sizeof(tagST_FILEDB_HEADINFO)

/*=================================================================*/
/*						INDICATE FUNCTIONS						   */
/*=================================================================*/
/// ÁöÇ¥ º¯¼ö
typedef struct tagST_FILEDB_IBODY_VARIABLE
{
	TCHAR chVariable[255];			///< º¯¼ö¸í
	/*2004/03/30 - floatÇüÀº VarPrice¸¦ Ç¥ÇöÇÒ¼ö ¾ø´Ù*/
	TCHAR chValue[20];				///< º¯¼ö°ª
	//double dValue;

	tagST_FILEDB_IBODY_VARIABLE()
	{
		*chVariable = 0x00;
		*chValue	= 0x00;
	}
	~tagST_FILEDB_IBODY_VARIABLE()
	{
	}
}ST_FILEDB_IBODY_VARIABLE;

struct tagST_FILEDB_IBODY_VARIABLE_SAVE
{
	TCHAR chValue[20];

	tagST_FILEDB_IBODY_VARIABLE_SAVE()
	{
		*chValue = 0x00;
	}
	~tagST_FILEDB_IBODY_VARIABLE_SAVE()
	{
	}
};

/// ÁöÇ¥ ±âÁØ¼±ÆíÁý
typedef struct tagST_FILEDB_IBODY_BASE
{
	int		 nBaseType;					///< ±âÁØ¼± Å¸ÀÔ(0:Line,1:Upper,2:Lower	)
	double	 dBaseValue;				///< ±âÁØ¼± ±âÁØ°ª
	int		 nBaseValueType;			///< ±âÁØ¼± ºñ±³Å¸ÀÔ(0:Value,1:Percent)
	COLORREF crBaseColor;				///< ±âÁØ¼± »ö»ó
	int		 nBaseStyle;				///< ±âÁØ¼± ½ºÅ¸ÀÏ
	int		 nBaseWeight;				///< ±âÁØ¼± ±½±â

	tagST_FILEDB_IBODY_BASE()
	{
		nBaseType		= 0;
		dBaseValue		= 0.0;
		nBaseValueType	= 0;
		crBaseColor		= 0;
		nBaseStyle		= 0;
		nBaseWeight		= 0;
	}
	~tagST_FILEDB_IBODY_BASE()
	{
	}
}ST_FILEDB_IBODY_BASE;

/// ÁöÇ¥ ¶óÀÎ
typedef struct tagST_FILEDB_IBODY_LINE
{
	int nLineShow;					///< LineÀ» º¸¿©ÁÙÁöÀÇ ¿©ºÎ
	int nFormulaSize;				///< Line Formula size
	TCHAR chLineName[30];			///< Line ÀÌ¸§
	COLORREF crLineColor;			///< Line »ö»ó
	int nLineStyle;					///< Line ½ºÅ¸ÀÏ
	int nLineWeight;				///< Line ±½±â
	int nLineDrawType;				///< Line DrawType( 0:Line,1:Dot,2:OscBar,3:Bar,4:Mountain,..)
	TCHAR *pChFormula;				///< Line Formula size

	tagST_FILEDB_IBODY_LINE()
	{
		nLineShow		= 0;
		nFormulaSize	= 0;
		*chLineName		= 0x00;
		crLineColor		= 0;
		nLineStyle		= 0;
		nLineWeight		= 0;
		nLineDrawType	= 0;
		pChFormula		= NULL;
	}
	~tagST_FILEDB_IBODY_LINE()
	{
		if(pChFormula)
		{
			ASSERT(FALSE);
		}
	}

	void Clear()
	{
		if(pChFormula)
		{
			delete[] pChFormula;
			pChFormula = NULL;
		}
	}
}ST_FILEDB_IBODY_LINE;

struct tagST_FILEDB_IBODY_LINE_SAVE
{
	int nLineShow;
	COLORREF crLineColor;
	int nLineStyle;
	int nLineWeight;
	int nLineDrawType;				//0:Line,1:Dot,2:OscBar,3:Bar,4:Mountain

	tagST_FILEDB_IBODY_LINE_SAVE()
	{
		nLineShow		= 0;
		crLineColor		= 0;
		nLineStyle		= 0;
		nLineWeight		= 0;
		nLineDrawType	= 0;
	}
	~tagST_FILEDB_IBODY_LINE_SAVE()
	{
	}
};

typedef struct tagST_FILEDB_ILMOK_LINE
{
	int nLineShow;

	TCHAR chLineName[30];
	COLORREF crLineColor;
	int nLineStyle;
	int nLineWeight;
	int nLineDrawType;

	int nCalcPeriod;
	int nCalcType;

	int nShiftPeriod;

	tagST_FILEDB_ILMOK_LINE()
	{
		nLineShow		= 0;
		memset(chLineName, 0x00, sizeof(TCHAR)*30);
		crLineColor		= 0;
		nLineStyle		= 0;
		nLineWeight		= 0;
		nLineDrawType	= 0;
		nCalcPeriod		= 0;
		nCalcType		= 0;
		nShiftPeriod	= 0;
	}
	~tagST_FILEDB_ILMOK_LINE()
	{
	}
}ST_FILEDB_ILMOK_LINE,*LPST_FILEDB_ILMOK_LINE;

/// ÁöÇ¥ Signal Line
typedef struct tagST_FILEDB_IBODY_SIGNAL
{
	UINT uSignalLine;			///< Signal Line »ç¿ëÀ¯¹«
	int nSignalPeriod;			///< ±â°£
	int nSignalType;			///< ¹æ½Ä(Simple, Exponential, Smooth,...)
	COLORREF crLineColor;		///< »ö»ó
	int nSignalStyle;			///< À¯Çü(Solid, Dash, dot,..)
	int nSignalWeight;			///< ±½±â
	int nSignalDrawType;		///< 0:Line,1:OSC,2:Line+OSC
	
	int nChartLineBasic;		//ÐÂÔö²ÎÊý£º»ùÏß¡¢±È½ÏÏß
	int nChartLineCompare; 	

	tagST_FILEDB_IBODY_SIGNAL()
	{
		uSignalLine		= 0;
		nSignalPeriod	= 0;
		nSignalType		= 0;
		crLineColor		= 0;
		nSignalStyle	= 0;
		nSignalWeight	= 0;
		nSignalDrawType	= 0;
		nChartLineBasic = 0;
		nChartLineCompare = 0;  
	}
	~tagST_FILEDB_IBODY_SIGNAL()
	{
	}
}ST_FILEDB_IBODY_SIGNAL;

typedef struct tagST_FILEDB_IBODY_SAVE
{
	BOOL bTitleShow;		//2004/03/23  - Ãß°¡
	BOOL bMinMaxShow;		//2004/03/23  - Ãß°¡

	int	 nFloatingPoint;	//2005/04/20  - Ãß°¡
	tagST_FILEDB_IBODY_SIGNAL stSignalLine;		//2004/03/23  - Ãß°¡ //[kangyb 2010-08-04]
	int nLineCnt;
	tagST_FILEDB_IBODY_LINE_SAVE pStLineLists[5];
	int nVariableCnt;
	tagST_FILEDB_IBODY_VARIABLE_SAVE pStBodyVariables[G_MAXIBVARIABLE];

	//++2004/08/03 - Ãß°¡
	int	nDisplayType;				//0:±âº»,1:Range(0~100),2:ÁöÇ¥¹ÌºÐ(0~100)
	int nDisplayValues[2];			//++2004/08/05

	BOOL bIndPractical[3];			//0:±âÁØ¼± ¸Å¸Å,1:½ÅÈ£¼±¸Å¸Å,2:°ú¸Å¼ö/°ú¸Åµµ¿¡ ÀÇÇÑ ¸Å¸Å
	int nIndPractical;				//ÇöÀç SelectedµÈ È°¿ë¹æ¾È	:  -1 ÀÌ¸é X
	//--2004/08/03 - Ãß°¡

	int nBaseCnt;
	tagST_FILEDB_IBODY_BASE pStBodyBases[G_MAXIBBASELINE];	

	tagST_FILEDB_IBODY_SAVE()
	{
		bTitleShow		= FALSE;
		bMinMaxShow		= FALSE;
		nFloatingPoint	= 0;
		//stSignalLine;
		nLineCnt		= 0;
		//pStLineLists[5];
		nVariableCnt	= 0;
		//pStBodyVariables[G_MAXIBVARIABLE];
		nDisplayType	= 0;
		memset(nDisplayValues, 0, sizeof(int)*2);
		memset(bIndPractical, 0, sizeof(BOOL)*3);
		nIndPractical	= 0;
		nBaseCnt		= 0;
		//pStBodyBases[10];	
	}
	~tagST_FILEDB_IBODY_SAVE()
	{
	}
} ST_FILEDB_IBODY_SAVE,*LPST_FILEDB_IBODY_SAVE;
#define ST_FILEDB_IBODY_SAVE_SIZE sizeof(tagST_FILEDB_IBODY_SAVE)

/*=================================================================*/
/*							OPTIMIZE							   */
/*=================================================================*/	
/*	Optimize Variable Structs									   */
typedef struct tagST_FILEDB_OBODY_VARIABLE
{
	TCHAR chVariable[255];
	float fCurValue;
	float fInitValue;
	float fEndValue;
	float fStepValue;

	tagST_FILEDB_OBODY_VARIABLE()
	{
		memset(chVariable, 0x00, sizeof(TCHAR)*255);
		fCurValue	= 0.0f;
		fInitValue	= 0.0f;
		fEndValue	= 0.0f;
		fStepValue	= 0.0f;
	}
	~tagST_FILEDB_OBODY_VARIABLE()
	{
	}
}ST_FILEDB_OBODY_VARIABLE;

struct tagST_FILEDB_OBODY_VARIABLE_SAVE
{
	float fCurValue;
	float fInitValue;
	float fEndValue;
	float fStepValue;

	tagST_FILEDB_OBODY_VARIABLE_SAVE()
	{
		fCurValue	= 0.0f;
		fInitValue	= 0.0f;
		fEndValue	= 0.0f;
		fStepValue	= 0.0f;
	}
	~tagST_FILEDB_OBODY_VARIABLE_SAVE()
	{
	}
};

struct tagST_FILEDB_OBODY_FORMULA_SAVE
{
	int nTradingType;					//0:¸Å¼öÁøÀÔ,1:¸Å¼öÃ»»ê,2:¸ÅµµÁøÀÔ,3:¸ÅµµÃ»»ê
	int nSignalIndex;			
	int nSignalSize;
	COLORREF crSignalColor;

	tagST_FILEDB_OBODY_FORMULA_SAVE()
	{
		nTradingType	= 0;
		nSignalIndex	= 0;
		nSignalSize		= 0;
		crSignalColor	= 0;
	}
	~tagST_FILEDB_OBODY_FORMULA_SAVE()
	{
	}
};

typedef struct tagST_FILEDB_OBODY_FORMULA
{
	int nFormulaSize;					///< Formula ¹®ÀÚ¿­ °¹¼ö
	int nTradingType;					///< 0:¸Å¼öÁøÀÔ,1:¸Å¼öÃ»»ê,2:¸ÅµµÁøÀÔ,3:¸ÅµµÃ»»ê
	int nSignalIndex;					///< Signal À¯Çü(Signal,¡â,¡ø...) 
	int nSignalSize;					///< Signal Å©±â
	COLORREF crSignalColor;				///< Signal »ö»ó
	TCHAR *pChFormula;					///< Formula ¹®ÀÚ¿­

	tagST_FILEDB_OBODY_FORMULA()
	{
		nFormulaSize	= 0;
		nTradingType	= 0;
		nSignalIndex	= 0;
		nSignalSize		= 0;
		crSignalColor	= 0;
		pChFormula		= NULL;
	}
	~tagST_FILEDB_OBODY_FORMULA()
	{
		if(pChFormula)
		{
			ASSERT(FALSE);
		}
	}

	void Clear()
	{
		if(pChFormula)
		{
			delete[] pChFormula;
			pChFormula = NULL;
		}
	}
}ST_FILEDB_OBODY_FORMULA;

typedef struct tagST_FILEDB_OPTBODY_SAVE
{	 
	tagST_FILEDB_OBODY_FORMULA_SAVE pOPTFormula[4];

	int nVariableCnt;
	tagST_FILEDB_OBODY_VARIABLE_SAVE pStOptVariables[10];

	tagST_FILEDB_OPTBODY_SAVE()
	{
		//pOPTFormula[4];
		nVariableCnt	= 0;
		//pStOptVariables[10];
	}
	~tagST_FILEDB_OPTBODY_SAVE()
	{
	}
} ST_FILEDB_OPTBODY_SAVE,*LPST_FILEDB_OPTBODY_SAVE;
#define ST_FILEDB_OPTBODY_SAVE_SIZE sizeof(tagST_FILEDB_OPTBODY_SAVE)

////////////////////////////////////////////////////////////////////
//				2006/01/13 - Optimize Exe & Config
const int G_MAX_HISTORY_TYPE_SIZE		= 14;
const int G_MAX_SUMMARY_SIZE			= 200;
const TCHAR *const G_OPT_RESULT_VAREXT_SUMMARY	= _T(".ovs");
const TCHAR *const G_OPT_RESULT_VAREXT_TRADE	= _T(".ovt");

const TCHAR *const G_OPT_RESULT_LOGEXT_SUMMARY	= _T(".ols");
const TCHAR *const G_OPT_RESULT_LOGEXT_TRADE	= _T(".olt");

enum EnOptTradeFeeType
{
	G_OPT_TRADEFEE_FIXVALUE				= 0,		//Á¤¾×¹ý
	G_OPT_TRADEFEE_FIXRATIO				= 1,		//Á¤·ü¹ý
};

enum EnOptCurrentTradeType
{
	G_OPT_CURRENT_TRADETYPE_NONE		= -1,
	G_OPT_CURRENT_TRADETYPE_BUY			= 0,
	G_OPT_CURRENT_TRADETYPE_SELL		= 1,
};

enum EnOptTradeType
{
	G_OPT_TRADETYPE_NONE				= -1,
	G_OPT_TRADETYPE_BUY					= 0,
	G_OPT_TRADETYPE_SELL				= 1,
	G_OPT_TRADETYPE_BOTH				= 2,
};

enum EnOptTradePosType
{
	G_OPT_TRADE_POSTYPE_NEXTOPEN		= 0,	// ´ÙÀ½½Ã°¡
	G_OPT_TRADE_POSTYPE_NEXTCLOSE		= 1,	// ´ÙÀ½Á¾°¡
	G_OPT_TRADE_POSTYPE_THISCLOSE		= 2,	// ÀÌ¹øÁ¾°¡
};

enum EnOptInvestRuleType
{
	G_OPT_INVESTTYPE_FULLVALUE			= 0,	//Àü¾×-Ãµ¸¸¿ø+Ãß°¡¼öÀÍ/¼Õ½Ç±Ý
	G_OPT_INVESTTYPE_FIXVALUE			= 1,	//Á¤¾×-Ãµ¸¸¿ø
	G_OPT_INVESTTYPE_STOCKCOUNT			= 2,	//ÁÖ½Ä¼ö
};

// ¶óµð¿À
enum EnOptTradeStopRuleType
{
	G_OPT_TRADESTOP_NONE				= 0,	// ¼ÕÀý¸Å¿øÄ¢ Àû¿ë¾ÈÇÔ
	G_OPT_TRADESTOP_FIXVALUE			= 1,	// Á¤¾×¹ý Àû¿ë : ¸ÅÀÔ°¡°Ý Á¤¾× »ó½Â/ÇÏ¶ô
	G_OPT_TRADESTOP_VARVALUE			= 2,	// Á¤·ü¹ý Àû¿ë
};

// 
enum EnOptTradeStopExitType
{
	G_STOP_TRADE_DIFFPRICE				= 0,	// ¼ÕÀý¸Å¿øÄ¢ Á¤¾×¹ý(¸Å¸Å°¡ÀÇ _%¿ø»ó½Â/ÇÏ¶ô½Ã)
	G_STOP_TRADE_LOSSCUT				= 1,	// ¼ÕÀý¸Å¿øÄ¢ Á¤·ü¹ý(¸Å¸Å°¡ÀÇ _%ÇÏ¶ô½Ã(StopLoss))
	G_STOP_TRADE_TARGETPROFIT			= 2,	// ¼ÕÀý¸Å¿øÄ¢ Á¤·ü¹ý(¸Å¸Å°¡ÀÇ _%»ó½Â½Ã(TargetProfit))
};

enum EnOptVarTrdStopType
{
	G_OPT_TRADESTOP_VARVALUE_LOSS		= 0,	//	
	G_OPT_TRADESTOP_VARVALUE_PROFIT		= 1,	//	
	G_OPT_TRADESTOP_VARVALUE_TRAIL1		= 2,	//	
	G_OPT_TRADESTOP_VARVALUE_TRAIL2		= 3,	//	
};

enum EnOptHistoryType
{
	G_OPT_HISTORY_BSTYPE				= 0,	//¸Å¸ÅÀ¯Çü(¸Å¼ö:0, ¸Åµµ:1)
	G_OPT_HISTORY_ENTDATE				= 1,	//ÁøÀÔÀÏÀÚ
	G_OPT_HISTORY_ENTVALUE				= 2,	//ÁøÀÔ±Ý¾×
	G_OPT_HISTORY_ENTRESULT				= 3,	//¼ö¼ö·á Æ÷ÇÔ ÁøÀÔ±Ý¾×
	G_OPT_HISTORY_EXITDATE				= 4,	//Ã»»êÀÏÀÚ
	G_OPT_HISTORY_EXITVALUE				= 5,	//Ã»»ê±Ý¾×
	G_OPT_HISTORY_EXITRESULT			= 6,	//¼ö¼ö·á Æ÷ÇÔ Ã»»ê±Ý¾×
	G_OPT_HISTORY_ENTINDEX				= 7,	//ÁøÀÔ½ÃÁ¡Index
	G_OPT_HISTORY_EXITINDEX				= 8,	//Ã»»ê½ÃÁ¡Index
	G_OPT_HISTORY_CONTRACT				= 9,	//¼ö·®
	G_OPT_HISTORY_BALANCE_PRICE			= 10,	//ÀÜ¾×
	G_OPT_HISTORY_PROFIT_AMOUNT			= 11,	//¼öÀÍ(¼Õ½Ç)±Ý¾×
	G_OPT_HISTORY_PROFIT_RATIO			= 12,	//¼öÀÍ(¼Õ½Ç)·ü	
	G_OPT_HISTORY_ACCUM_PROFIT_RATIO	= 13,	//´©Àû¼öÀÍ(¼Õ½Ç)·ü
};

enum EnOptResultEvent
{
	G_OPTRESULT_EVENT_NONE				= -1,
	G_OPTRESULT_EVENT_SIGNAL			= 0,
	G_OPTRESULT_CHART_SIGNAL			= 1,
	G_OPTRESULT_EVENT_PLINDEX_LINE		= 2,
	G_OPTRESULT_EVENT_PLINDEX_OSC		= 3,
	G_OPTRESULT_EVENT_SCREEN_CLEAR		= 4,
};

// Â÷Æ® ÀÎµ¦½º Ã£±â Á¶°Ç
enum enChtIndexFindFlag
{	
	G_CIFF_KINDTYPE	= 0x01,			///< Chart Å¸ÀÔ °Ë»ö
	G_CIFF_POS		= 0x02,			///< Postion °Ë»ö
	G_CIFF_NAME		= 0x04,			///< ÀÌ¸§ °Ë»ö
};

/// »ó½Â/ÇÏ¶ô/º¸ÇÕ ±¸ºÐ


enum en_CPBongType
{
	G_CPBT_1BONG = 0,				// 1ºÀ
	G_CPBT_2BONG,					// 2ºÀ
	G_CPBT_3BONG,					// 3ºÀ
	G_CPBT_4BONG,					// 4ºÀ
	G_CPBT_5BONG,					// 5ºÀ
	G_CPBT_6BONG,					// 6ºÀ
	G_CPBT_COUNT					// ´ÜÁö Ä«¿îÆ®
};

typedef struct tagST_OPT_ENV_CONFIG
{
	//RuleTab
	BOOL bRuleSignalSound;
	UINT uRuleDisplayType;		//0:ApplyScreen,1:PopupDlg
	UINT uRuleEntryPos;			//ÁøÀÔ½ÃÁ¡
	UINT uRuleExitPos;			//Ã»»ê½ÃÁ¡
	UINT uRuleInvestType;		//0:ÅõÀÚ±Ý¾×(Àü¾×),ÅõÀÚ±Ý¾×(Á¤¾×),ÁÖ½Ä¼ö(¼±¹°¿É¼Ç°è¾àÁÖ)
	long lRuleInvestValue[3];	//±Ý¾×
	UINT uRuleTradeFee;			//0:Á¤¾×¹ý,1:Á¤·ü¹ý
	float fRuleFixEntryFee;		//Á¤¾×¹ýÁøÀÔ¼ö¼ö·á
	float fRuleFixExitFee;		//Á¤¾×¹ýÃ»»ê¼ö¼ö·á
	float fRuleVarEntryFee;		//Á¤·ü¹ýÁøÀÔ¼ö¼ö·á
	float fRuleVarExitFee;		//Á¤·ü¹ýÃ»»ê¼ö¼ö·á
	float fRuleSlippage;		//Slippage
	//LossCutTab
	UINT uStopLossCutType;		//°­Á¦Ã»»ê±ÔÄ¢
	float fStopFixLossCut;		//Á¤¾×¹ý - ¿ø»ó½Â,¿øÇÏ¶ô
	BOOL bStopLossCut;
	float fStopLossCut;
	BOOL bStopProfitCut;
	float fStopProfitCut;
	BOOL bStopTrailStop1; 
	float fStopTrailStop11;
	float fStopTrailStop12;
	BOOL bStopTrailStop2;
	float fStopTrailStop21;
	float fStopTrailStop22;
	TCHAR chDummy[8];

	tagST_OPT_ENV_CONFIG()
	{
		bRuleSignalSound	= FALSE;
		uRuleDisplayType	= 0;
		uRuleEntryPos		= 0;
		uRuleExitPos		= 0;
		uRuleInvestType		= 0;
		memset(lRuleInvestValue, 0, sizeof(long)*3);
		uRuleTradeFee		= 0;
		fRuleFixEntryFee	= 0.0f;
		fRuleFixExitFee		= 0.0f;
		fRuleVarEntryFee	= 0.0f;
		fRuleVarExitFee		= 0.0f;
		fRuleSlippage		= 0.0f;
		uStopLossCutType	= 0;
		fStopFixLossCut		= 0.0f;
		bStopLossCut		= FALSE;
		fStopLossCut		= 0.0f;
		bStopProfitCut		= FALSE;
		fStopProfitCut		= 0.0f;
		bStopTrailStop1		= FALSE;
		fStopTrailStop11	= 0.0f;
		fStopTrailStop12	= 0.0f;
		bStopTrailStop2		= FALSE;
		fStopTrailStop21	= 0.0f;
		fStopTrailStop22	= 0.0f;
		memset(chDummy, 0x00, sizeof(TCHAR)*8);
	}
	~tagST_OPT_ENV_CONFIG()
	{
	}
} ST_OPT_ENV_CONFIG,*LPST_OPT_ENV_CONFIG;
#define ST_OPT_ENV_CONFIG_SIZE sizeof(tagST_OPT_ENV_CONFIG)

typedef struct tagST_OPT_RESULT_HEAD
{
	int nVersionIndex;		//1.0.0.1
	TCHAR chOptCode[30];
	TCHAR chIndexName[30];
	int nTotDataCount;		//ÀüÃ¼ DataCount
	int btDatePeriod;		//ºÐºÀ,ÀÏºÀ??	
	int btDateCycle;		//10ÃÊ,20ÃÊ30ÃÊ,1ºÐ,2ºÐ,3ºÐ,5ºÐ,10ºÐ,15ºÐ,20ºÐ,30ºÐ,60ºÐ,180ºÐ
	int	nDateCycle;			//»ç¿ëÀÚ(..ºÐ)
	int btDateCount;		//1ÀÏ,2ÀÏ??
	double dBaseDate;		//ºÐºÀ¿¡¼­ ±âÁØÀÏ·ÎºÎÅÍ NÀÏ
	double dStartDate;		//½ÃÀÛÀÏ½Ã
	double dEndDate;		//Á¾·áÀÏ½Ã		

	tagST_OPT_RESULT_HEAD()
	{
		nVersionIndex	= 0;
		memset(chOptCode, 0x00, sizeof(TCHAR)*30);
		memset(chIndexName, 0x00, sizeof(TCHAR)*30);
		nTotDataCount	= 0;
		btDatePeriod	= 0;
		btDateCycle		= 0;
		btDateCount		= 0;
		nDateCycle		= 0;
		dBaseDate		= 0.0;
		dStartDate		= 0.0;
		dEndDate		= 0.0;
	}
	~tagST_OPT_RESULT_HEAD()
	{
	}
}ST_OPT_RESULT_HEAD,*LPST_OPT_RESULT_HEAD;
#define ST_RESULT_HEAD_SIZE sizeof(tagST_OPT_RESULT_HEAD)

//º¯¼ö¸¶´Ù Summary Á¤º¸´Â ÇÏ³ª¸¸ Á¸Àç
typedef struct tagST_RESULT_BODY_SUMMARY
{
	TCHAR   chVarName[30];	
	UINT	nTradeNum;			//ÇÏÀ§ÀÇ TradeHistory³ª SummaryHistory¿ÍÀÇ ¿¬°á Á¤º¸
	UINT	nTotalTrdCnt;		//ÃÑ°Å·¡È½¼ö	
	int		nCurTradeType;		//ÇöÀç»óÅÂ
	int		nProfitTrdCnt;		//¼öÀÍ°Å·¡È½¼ö
	float   fAccumProfitPrice;	//´©Àû¼öÀÍ±Ý
	float   fAvgProfitRatio;	//Æò±Õ¼öÀÍ·ü
	UINT	nTotTrdHoldCount;		//ÃÑ°Å·¡º¸À¯µ¥ÀÌÅÍ¼ö
	UINT	nAvgProfitHoldCount;//¼öÀÍ°Å·¡Æò±Õº¸À¯µ¥ÀÌÅÍ¼ö
	UINT	nAvgLossHoldCount;	//¼Õ½Ç°Å·¡Æò±Õº¸À¯µ¥ÀÌÅÍ¼ö	
	int		nLossTrdCnt;		//¼Õ½Ç°Å·¡È½¼ö	
	float   fAccumLossPrice;	//´©Àû¼Õ½Ç±Ý
	float   fAvgLossRatio;		//Æò±Õ¼Õ½Ç·ü	
	float   fPurePLPrice;		//¼ø¼ÕÀÍ±Ý
	float   fPurePLRatio;		//¼ø¼ÕÀÍ·ü

	float   fTradeWinRatio;		//½Â·ü - ¼öÀÍ°Å·¡/¼Õ½Ç°Å·¡

	UINT	nMaxProfitDataCount;//ÃÖ´ëÀÌÀÍÀÏ¼ö		
	float	fMaxProfitRatio;	//ÃÖ´ë¼öÀÍ¾×	
	float	fMaxProfitPrice;	//ÃÖ´ë¼öÀÍ·ü
	double	dMaxProfitEntryDate;//ÃÖ´ë¼öÀÍ³¯Â¥/½Ã°£-Ã»»ê±âÁØ
	double	dMaxLossExitDate;	//ÃÖ´ë¼Õ½Ç³¯Â¥/½Ã°£-Ã»»ê±âÁØ
	UINT	nMaxLossDataCount;  //ÃÖ´ë¼Õ½ÇÀÏ¼ö		
	float	fMaxLossPrice;		//ÃÖ´ë¼Õ½Ç¾×
	float	fMaxLossRatio;		//ÃÖ´ë¼Õ½Ç·ü	
	double	dMaxLossEntryDate;	//ÃÖ´ë¼Õ½Ç³¯Â¥/½Ã°£-Ã»»ê±âÁØ
	double	dMaxProfitExitDate;	//ÃÖ´ë¼öÀÍ³¯Â¥/½Ã°£-Ã»»ê±âÁØ		

	double  dFirstEntryClose;	//ÃÖÃÊÁøÀÔ°¡°Ý - Á¾°¡
	double  dLastExitClose;		//¸¶Áö¸·Ã»»ê°¡°Ý - Á¾°¡

	int		nMaxProfitCnt;
	int		nMaxLossCnt;

	tagST_RESULT_BODY_SUMMARY()
	{
		memset(chVarName, 0x00, sizeof(TCHAR)*30);
		nTradeNum			= 0;
		nTotalTrdCnt		= 0;
		nCurTradeType		= 0;
		nProfitTrdCnt		= 0;
		fAccumProfitPrice	= 0.0f;
		fAvgProfitRatio		= 0.0f;
		nTotTrdHoldCount	= 0;
		nAvgProfitHoldCount	= 0;
		nAvgLossHoldCount	= 0;
		nLossTrdCnt			= 0;
		fAccumLossPrice		= 0.0f;
		fAvgLossRatio		= 0.0f;
		fPurePLPrice		= 0.0f;
		fPurePLRatio		= 0.0f;
		fTradeWinRatio		= 0.0f;
		nMaxProfitDataCount	= 0;
		fMaxProfitRatio		= 0.0f;
		fMaxProfitPrice		= 0.0f;
		dMaxProfitEntryDate	= 0.0;
		dMaxLossExitDate	= 0.0;
		nMaxLossDataCount	= 0;
		fMaxLossPrice		= 0.0f;
		fMaxLossRatio		= 0.0f;
		dMaxLossEntryDate	= 0.0;
		dMaxProfitExitDate	= 0.0;
		dFirstEntryClose	= 0.0;
		dLastExitClose		= 0.0;

		nMaxProfitCnt		= 0;
		nMaxLossCnt			= 0;
	}
	~tagST_RESULT_BODY_SUMMARY()
	{
	}
}ST_RESULT_BODY_SUMMARY,*LPST_RESULT_BODY_SUMMARY;
#define ST_RESULT_BODY_SUMMARY_SIZE sizeof(tagST_RESULT_BODY_SUMMARY)

struct tagST_RESULT_BODY_HISTORY_ITEM
{
	int		nEntryTradeIdx;	
	int		nExitTradeIdx;	
	UINT	nTradeType;			//¸Å¼ö/¸Å¼öÃ»»ê,¸Åµµ/¸ÅµµÃ»»ê
	double  dEntryDate;			//ÁøÀÔ³¯Â¥
	double  dEntryPrice;		//ÁøÀÔ°¡°Ý
	double  dExitDate;			//Ã»»ê³¯Â¥
	double  dExitPrice;			//Ã»»ê°¡°Ý
	double	dBalancePrice;		//ÀÜ±Ý
	int		nContracts;			//°Å·¡¼ö·®	
	float	fTradePLPrice;		//¼ÕÀÍ°¡°Ý
	float	fTradePLRatio;		//¼öÀÍ·ü
	float   fAccumPLRatio;		//´©Àû¼öÀÍ·ü	

	tagST_RESULT_BODY_HISTORY_ITEM()
	{
		nEntryTradeIdx	= 0;
		nExitTradeIdx	= 0;
		nTradeType		= 0;
		dEntryDate		= 0.0;
		dEntryPrice		= 0.0;
		dExitDate		= 0.0;
		dExitPrice		= 0.0;
		dBalancePrice	= 0.0;
		nContracts		= 0;
		fTradePLPrice	= 0.0f;
		fTradePLRatio	= 0.0f;
		fAccumPLRatio	= 0.0f;
	}
	~tagST_RESULT_BODY_HISTORY_ITEM()
	{
	}
};

//º¯¼ö¸¶´Ù ¸Å¼ö/¸ÅµµÀÇ ¸ðµç °ªÀ» ´Ù °¡Áö°í ÀÖ¾î¾ßÇÔ
typedef struct tagST_RESULT_BODY_HISTORY
{
	TCHAR   chVarName[30];	
	UINT	nTotalTrdCnt;		//ÃÑ°Å·¡È½¼ö - File¿¡¼­ VarPos¸¦ Ã£¾Æ°¡´Â Key°¡ µÈ´Ù	
	tagST_RESULT_BODY_HISTORY_ITEM *pStResultHistoryItems;	

	tagST_RESULT_BODY_HISTORY()
	{
		memset(chVarName, 0x00, sizeof(TCHAR)*30);
		nTotalTrdCnt			= 0;
		pStResultHistoryItems	= NULL;	
	}
	~tagST_RESULT_BODY_HISTORY()
	{
		if(pStResultHistoryItems)
		{
			ASSERT(FALSE);
		}
	}

	void Clear()
	{
		if(pStResultHistoryItems)
		{
			delete[] pStResultHistoryItems;
			pStResultHistoryItems = NULL;
		}
	}

}ST_RESULT_BODY_HISTORY,*LPST_RESULT_BODY_HISTORY;
#define ST_RESULT_BODY_HISTORY_SIZE sizeof(tagST_RESULT_BODY_HISTORY)

/*=================================================================*/
/*							SIGNAL								   */
/*=================================================================*/	

typedef struct tagST_FILEDB_SIGNALBODY_SAVE
{	
	int nSignalIndex;
	int nSignalPos;			//2004/09/01 - »õ·Î Ãß°¡
	int nSignalSize;
	COLORREF crSignalColor;

	int nVariableCnt;
	tagST_FILEDB_IBODY_VARIABLE_SAVE pStSigVariables[10];

	tagST_FILEDB_SIGNALBODY_SAVE()
	{
		nSignalIndex	= 0;
		nSignalPos		= 0;
		nSignalSize		= 0;
		crSignalColor	= 0;
		nVariableCnt	= 0;
		//pStSigVariables[10];
	}
	~tagST_FILEDB_SIGNALBODY_SAVE()
	{
	}
} ST_FILEDB_SIGNALBODY_SAVE,*LPST_FILEDB_SIGNALBODY_SAVE;
#define ST_FILEDB_SIGNALBODY_SAVE_SIZE sizeof(tagST_FILEDB_SIGNALBODY_SAVE)

/*=================================================================*/
/*							SHOWAT								   */
/*=================================================================*/	

typedef struct tagST_FILEDB_SHOWATBODY_SAVE
{	
	int nShowatIndex;	
	int nShowatType;
	COLORREF crShowatColor;

	int nVariableCnt;
	tagST_FILEDB_IBODY_VARIABLE_SAVE pStShowVariables[10];

	tagST_FILEDB_SHOWATBODY_SAVE()
	{
		nShowatIndex	= 0;
		nShowatType		= 0;
		crShowatColor	= 0;
		nVariableCnt	= 0;
		//pStShowVariables[10];
	}
	~tagST_FILEDB_SHOWATBODY_SAVE()
	{
	}
} ST_FILEDB_SHOWATBODY_SAVE,*LPST_FILEDB_SHOWATBODY_SAVE;
#define ST_FILEDB_SHOWATBODY_SAVE_SIZE sizeof(tagST_FILEDB_SHOWATBODY_SAVE)


/*=================================================================*/
/*					CandlePattern1								   */
/*=================================================================*/	

typedef struct tagST_FILEDB_CANDLEBODY_SAVE
{	
	int nCandleIndex;
	int nCandlePos;			//2004/09/01 - »õ·Î Ãß°¡
	int nCandleSize;
	COLORREF crCandleColor;

	int nVariableCnt;
	tagST_FILEDB_IBODY_VARIABLE_SAVE pStCandleVariables[10];

	tagST_FILEDB_CANDLEBODY_SAVE()
	{
		nCandleIndex	= 0;
		nCandlePos		= 0;
		nCandleSize		= 0;
		crCandleColor	= 0;
		nVariableCnt	= 0;
		//pStCandleVariables[10];
	}
	~tagST_FILEDB_CANDLEBODY_SAVE()
	{
	}
} ST_FILEDB_CANDLEBODY_SAVE,*LPST_FILEDB_CANDLEBODY_SAVE;
#define ST_FILEDB_CANDLEBODY_SAVE_SIZE sizeof(tagST_FILEDB_CANDLEBODY_SAVE)

/*=================================================================*/
/*					CandlePattern2 - 2005/04/05~					   */
/*=================================================================*/	

typedef struct tagST_PREVBONG_DATA_INFO
{
	int		nBongType;			//EnCandlePatternTypes

	double	dOpen;
	double	dHigh;
	double	dLow;
	double	dClose;

	tagST_PREVBONG_DATA_INFO()
	{
		nBongType	= 0;
		dOpen		= 0.0;
		dHigh		= 0.0;
		dLow		= 0.0;
		dClose		= 0.0;
	}
	~tagST_PREVBONG_DATA_INFO()
	{
	}
}ST_PREVBONG_DATA_INFO,*LPST_PREVBONG_DATA_INFO;

typedef struct tagST_BONG_DATA_INFO
{
	int		nBongType;			//EnCandlePatternTypes

	int		nOpen;
	int		nHigh;
	int		nLow;
	int		nClose;

	tagST_BONG_DATA_INFO()
	{
		nBongType	= 0;
		nOpen		= 0;
		nHigh		= 0;
		nLow		= 0;
		nClose		= 0;
	}
	~tagST_BONG_DATA_INFO()
	{
	}
}ST_BONG_DATA_INFO,*LPST_BONG_DATA_INFO;

typedef struct tagST_FILEDB_CPATTERNBODY_SAVE
{
	TCHAR chDBName[G_FUNCTION_DB_NAME_MAX_SIZE];

	int nCPIndex;
	int nCPPos;
	int nCPSize;
	COLORREF crCPColor;

	int nVariableCnt;
	tagST_FILEDB_IBODY_VARIABLE_SAVE pStCPVariables[10];

	tagST_FILEDB_CPATTERNBODY_SAVE()
	{
		//TCHAR chDBName[G_FUNCTION_DB_NAME_MAX_SIZE];
		memset(chDBName, 0x00, sizeof(TCHAR)*G_FUNCTION_DB_NAME_MAX_SIZE);
		nCPIndex	= 0;
		nCPPos		= 0;
		nCPSize		= 0;
		crCPColor	= 0;
		nVariableCnt= 0;
		//pStCPVariables[10];
	}
	~tagST_FILEDB_CPATTERNBODY_SAVE()
	{
	}
} ST_FILEDB_CPATTERNBODY_SAVE,*LPST_FILEDB_CPATTERNBODY_SAVE;

#define ST_FILEDB_CPATTERNBODY_SAVE_SIZE sizeof(tagST_FILEDB_CPATTERNBODY_SAVE)



//YAxis Struct
typedef struct tagST_PROPERTY_YAXIS
{
	int		nYAxisZoneIdx;			//ÇöÀç Zone Index Number
	TCHAR	szZoneName[50];	
	/*2004/04/08*/
	//ÁÖÀÇ:¿ì¼±Àº ÇÑ¿µ¿ª¿¡ ÁöÇ¥°¡ 15°³ÀÌ»ó ¿Ã¶ó°¥¼ö ¾ø´Ù°í °¡Á¤ÇÑ´Ù
	int		nIdxListNum;
	int		nIdxChtKind[G_MAX_IDX_PER_CHART];
	TCHAR   szIndexNameList[G_MAX_IDX_PER_CHART][30];

	/*++2004/12/03*/
	TCHAR   szChtStCodeList[G_MAX_IDX_PER_CHART][30];
	TCHAR   szItemNameList[G_MAX_IDX_PER_CHART][30];
	int		nIdxYScaleList[G_MAX_IDX_PER_CHART];
	/*--2004/12/03*/

	int		nIdxSubTypeList[G_MAX_IDX_PER_CHART];

	ST_FILEDB_IBODY_SAVE		stIdxDBList[G_MAX_IDX_PER_CHART];
	ST_FILEDB_OPTBODY_SAVE		stOptDBList[G_MAX_IDX_PER_CHART];
	ST_FILEDB_SIGNALBODY_SAVE	stSigDBList[G_MAX_IDX_PER_CHART];
	ST_FILEDB_SHOWATBODY_SAVE	stShowDBList[G_MAX_IDX_PER_CHART];
	ST_FILEDB_CPATTERNBODY_SAVE	stCPDBList[G_MAX_IDX_PER_CHART];
	ST_FILEDB_CANDLEBODY_SAVE	stCandleDBList[G_MAX_IDX_PER_CHART];

	int			nYScaleDspType;			///< 0:Current Scale,1:Total Scale,2:Paper Scale,3:User Scale, (G_YSCALE_DSPUSER,...)
	double		dMaxScale;				///< »ç¿ëÀÚÁ¤ÀÇ(G_YSCALE_DSPUSER) ScaleÀÇ YÃà ÃÖ´ë°ª
	double		dMinScale;				///< »ç¿ëÀÚÁ¤ÀÇ(G_YSCALE_DSPUSER) ScaleÀÇ YÃà ÃÖ¼Ò°ª

	int			nYScaleLabel;			//0:¾çÂÊ,1:¿ÞÂÊ,2:¿À¸¥ÂÊ,3:¾øÀ½
	BOOL		bThousandComma;	
	BOOL		bShortFitch;			//º¸Á¶ ´ÜÀ§ º¸ÀÌ±â

	int			nDecimalDepress;		//10Áø´ÜÀ§ Ãà¾à
	int			nFloatingPoint;			//¼Ò¼ýÁ¡ ´ÜÀ§ Ç¥½Ã

	//YÃà ÀüÃ¼ Àû¿ë
	BOOL		bScreenYOverlab;
	float		fRegionFromRatio;
	float		fRegionToRatio;

	int			nYAxisShowType;			///< 0:¾çÂÊ,1:¿ÞÂÊ,2:¿À¸¥ÂÊ,3:¾øÀ½,4:Auto
	//float		fYScaleRatio;			///< YÃà ºñÀ²
	float		fYScaleRatioUpper;		///< À§ÂÊ YÃà ºñÀ²
	float		fYScaleRatioLower;		///< ¾Æ·§ÂÊ YÃà ºñÀ²
	COLORREF	crBackGround;			///< YÃà ¹è°æ»ö
	COLORREF	crForeGround;			///< YÃà ±ÛÀÚ»ö

	tagST_PROPERTY_YAXIS()
	{
		nYAxisZoneIdx		= 0;
		memset(szZoneName, 0x00, sizeof(TCHAR)*50);
		nIdxListNum			= 0;
		memset(nIdxChtKind, 0, sizeof(int)*G_MAX_IDX_PER_CHART);
		memset(szIndexNameList, 0x00, sizeof(TCHAR)*G_MAX_IDX_PER_CHART*30);
		memset(szChtStCodeList, 0x00, sizeof(TCHAR)*G_MAX_IDX_PER_CHART*30);
		memset(szItemNameList, 0x00, sizeof(TCHAR)*G_MAX_IDX_PER_CHART*30);
		memset(nIdxYScaleList, 0, sizeof(int)*G_MAX_IDX_PER_CHART);
		memset(nIdxSubTypeList, 0, sizeof(int)*G_MAX_IDX_PER_CHART);

		/*nIdxChtKind = new int[G_MAX_IDX_PER_CHART];
		szIndexNameList = new TCHAR[G_MAX_IDX_PER_CHART][30];
		szChtStCodeList = new TCHAR[G_MAX_IDX_PER_CHART][30];
		szItemNameList = new TCHAR[G_MAX_IDX_PER_CHART][30];
		nIdxYScaleList = new int[G_MAX_IDX_PER_CHART];
		nIdxSubTypeList = new int[G_MAX_IDX_PER_CHART];*/

		//stIdxDBList[G_MAX_IDX_PER_CHART];
		//stOptDBList[G_MAX_IDX_PER_CHART];
		//stSigDBList[G_MAX_IDX_PER_CHART];
		//stShowDBList[G_MAX_IDX_PER_CHART];
		//stCPDBList[G_MAX_IDX_PER_CHART];
		nYScaleDspType		= 0;
		dMaxScale			= 0.0;
		dMinScale			= 0.0;
		nYScaleLabel		= 0;
		bThousandComma		= FALSE;
		bShortFitch			= FALSE;
		nDecimalDepress		= 0;
		nFloatingPoint		= -1;
		bScreenYOverlab		= FALSE;
		fRegionFromRatio	= 0.0f;
		fRegionToRatio		= 0.0f;
		nYAxisShowType		= 0;
		//fYScaleRatio		= 0.0f;
		fYScaleRatioUpper	= 0.40f;	// 0.45f;
		fYScaleRatioLower	= 0.40f;	// 0.48f;
		crBackGround		= 0;
		crForeGround		= 0;
	}
	~tagST_PROPERTY_YAXIS()
	{
	}
} ST_PROPERTY_YAXIS,*LPST_PROPERTY_YAXIS;
#define ST_PROPERTY_YAXIS_SIZE sizeof(tagST_PROPERTY_YAXIS)

///////////////////////////////////////////////////////////////////////////////
typedef struct tagST_SCROLL_INFO
{
	int nCurPos;
	int nMaxPos;
	int nMinPos;

	tagST_SCROLL_INFO()
	{
		nCurPos = 0;
		nMaxPos	= 0;
		nMinPos	= 0;
	}
	~tagST_SCROLL_INFO()
	{
	}
}ST_SCROLL_INFO,*LPST_SCROLL_INFO;
#define ST_SCROLL_INFO_SIZE sizeof(tagST_SCROLL_INFO)
///////////////////////////////////////////////////////////////////////////////
//MarketIndicatorInfo
typedef struct tagST_MARKETINDICATOR_INFO
{
	CString		pstrMarketType;
	CString		pstrPeriodType;
	int			pnQueryType;
	int			pnQueryWParam;
	CString		pstrQueryLParam;
	CString		pstrQueryBaseCode;
	CString		pstrQueryCalcType;
	CString		pstrQueryCategory;
	CString		pstrFieldTickType;
	CString		pstrFieldIntraType;
	CString		pstrFieldETCType;
	int			pnRealtimeType;
	CString		pstrRealCategory;

	tagST_MARKETINDICATOR_INFO()
	{
		pstrMarketType		= _T("");
		pstrPeriodType		= _T("");
		pnQueryType			= -1;
		pnQueryWParam		= -1;
		pstrQueryLParam		= _T("");
		pstrQueryBaseCode	= _T("");
		pstrQueryCalcType	= _T("");
		pstrQueryCategory	= _T("");
		pstrFieldTickType	= _T("");
		pstrFieldIntraType	= _T("");
		pstrFieldETCType	= _T("");
		pnRealtimeType		= -1;
		pstrRealCategory	= _T("");
	}
	~tagST_MARKETINDICATOR_INFO()
	{
	}
}ST_MARKETINDICATOR_INFO,*LPST_MARKETINDICATOR_INFOO;
#define ST_MARKETINDICATOR_INFO_SIZE sizeof(tagST_MARKETINDICATOR_INFO)

typedef struct tagST_CHARTIDX_INFO
{
	int		nKeyID;			// map Key
	int		nOrderNum;		// Â÷Æ®»ý¼º ¼ø¼­

	int		nRegion;		// ¿µ¿ª
	int		nIdxNum;		// ¿µ¿ª¾È¿¡¼­ Index
	CString	strChtIdxName;	// Index ¸í

	int		nLineStyle;		// ¼±ÀÎÁö ¸·´ë(°Å·¡·®¸ð¾ç)ÀÎÁö?
	int		nDataType;		// -1:ÀÏ¹ÝÁ¾°¡,G_CHTDATA_DATE, G_CHTDATA_OPEN, G_CHTDATA_HIGH, G_CHTDATA_LOW, G_CHTDATA_CLOSE

	tagST_CHARTIDX_INFO()
	{
		nKeyID		  = -1;
		nOrderNum	  = -1;

		nRegion		  = -1;
		nIdxNum		  = -1;
		strChtIdxName = _T("");

		nLineStyle	  = 0;
		nDataType	  = -1;
	}
	~tagST_CHARTIDX_INFO()
	{
	}
}ST_CHARTIDX_INFO,*LPST_CHARTIDX_INFO;
#define ST_CHARTIDX_INFO_SIZE sizeof(tagST_CHARTIDX_INFO)

///////////////////////////////////////////////////////////////////////////////
enum EnParingErrorIndex
{
	G_PARSING_ERROR_NONE			= -1,
	G_PARSING_ERROR_NEED_CONST		= 0,
	G_PARSING_ERROR_NEED_VARIABLE	= 1,
	G_PARSING_ERROR_INCORRECT_EXP	= 2,	
	G_PARSING_ERROR_CANNOT_CALC		= 3,	
};

static LPTSTR G_PARSING_ERROR_COMMENT[] =
{
		_T("ÇöÀç ¼ö½Ä¿¡¼­ Parameter·Î »ó¼ö°¡ ÇÊ¿äÇÕ´Ï´Ù"), 
		_T("ÇöÀç ¼ö½Ä¿¡¼­ Parameter·Î º¯¼ö°¡ ÇÊ¿äÇÕ´Ï´Ù"),
		_T("Àß¸øµÈ ¼ö½Ä ÀÔ´Ï´Ù"),
		_T("°è»ê ÇÒ¼ö ¾ø´Â ¼ö½ÄÀÔ´Ï´Ù"),		
		NULL
};

static LPTSTR s_apszERRORKeywordList[] =
{
		_T("ADX"),
		_T("IF"),
		_T("SUM"),
		_T("AVG"),
		_T("MA"),
		_T("EAVG"),
		_T("EMA"),
		_T("WAVG"),
		_T("WMA"),
		//_T("SAVG"),
		//_T("SMA"),
		_T("TAVG"),
		_T("TMA"),
		_T("STDEV"),
		_T("DIMINUS"), 
		_T("DIPLUS"), 
		_T("DISPERSION"),
		_T("DX"), 
		_T("STDERR"),
		_T("HIGHEST"),
		_T("LOWEST"),
		_T("MIN"),
		_T("MAX"),
		_T("PMIN"),
		_T("PMAX"),
		_T("SHIFT"),
		_T("VSHIFT"),
		_T("EQUAL"),
		_T("PACCUM"),
		_T("ACCUM"),
		_T("STRONG"),
		_T("WEAK"),
		_T("CONTINUEUP"),
		_T("CONTINUEDN"),
		_T("REGION"),
		_T("PERCENTAGE"),
		_T("HAFTER"),
		_T("LAFTER"),
		_T("HHV"),
		_T("LLV"),
		_T("CROSSDN"),
		_T("CROSSUP"),
		_T("DNTURN"),
		_T("UPTURN"),
		_T("MOBV"),
		_T("OBV"),
		_T("NVI"),
		_T("PVI"),
		_T("PSAR"),
		_T("PIVOT"),
		_T("GETV"),
		NULL
};
//////////////////////////////////////////////////////////////////////////////
//						Earning Ratio Graph Class Defines
//////////////////////////////////////////////////////////////////////////////
#include <afxtempl.h>
//#include "MPChartLib.h"
//#include "MVChartLibExt.h"
//¼öÀÍ·ü Class
class CProfitRateData:public CObject
{
public:
	UINT	nFlag;						//0:¸Å¼ö,1:¸Åµµ,2:¼ÕÀý¸Å,3:ÀÌÀÍ½ÇÇö
	double	dDate;						//Ex:2002/08/23-10:23:13 ÁøÀÔÀÏ½Ã
	double	cDate;						//Ex:2002/08/23-10:23:13 Ã»»êÀÏ½Ã
	long	lEntrancePrc;				//ÁøÀÔ±Ý¾×
	long	lExitPrc;					//Ã»»ê±Ý¾×
	long	lCount;						//¼ö·®
		//float	fEarningRate;			//¼öÀÍ·ü
	//float	fEarningAccmRate;		//´©Àû¼öÀÍ·ü
	float	fEarningRate;				//¼öÀÍ·ü
	float	fEarningAccmRate;			//´©Àû¼öÀÍ·ü
	long	lEarningPrc;				//¼öÀÍ±Ý¾×
	long	lEarningAccmPrc;			//´©Àû¼öÀÍ±Ý¾×
	//		ÁöÇ¥,Bar	
	CPoint  ptAccmRate; 				//´©Àû¼öÀÍ·ü-ÁÂÇ¥
	CRect   rcRate;						//¼öÀÍ·ü Bong Rect

	virtual ~CProfitRateData(){};
	CProfitRateData()
	{		
		nFlag=-1;						//0:¸Å¼ö,1:¸Åµµ,2:¼ÕÀý¸Å,3:ÀÌÀÍ½ÇÇö
		dDate=-1.0f;					//Ex:2002/08/23-10:23:13 ÁøÀÔÀÏ½Ã
		cDate=-1.0f;					//Ex:2002/08/23-10:23:13 Ã»»êÀÏ½Ã
		lEntrancePrc=0;					//ÁøÀÔ±Ý¾×
		lEntrancePrc=0;					//Ã»»ê±Ý¾×
		lCount=0;						//¼ö·®
		fEarningRate=0.0f;				//¼öÀÍ·ü
		fEarningAccmRate=0.0f;			//´©Àû¼öÀÍ·ü
		lEarningPrc=0;					//¼öÀÍ±Ý¾×
		lEarningAccmPrc=0;				//´©Àû¼öÀÍ±Ý¾×

		ptAccmRate=CPoint(0,0); 		//´©Àû¼öÀÍ·ü-ÁÂÇ¥
		rcRate.SetRect(0,0,0,0);		//¼öÀÍ·ü Bong Rect
	}
};
typedef CTypedPtrArray<CObArray,CProfitRateData*> CProfitRateArray;

//////////////////////////////////////////////////////////////////////////////
//						Global Macro Defines 

#define IsHangul(c)	((c) & 0x8000)			//ÇÑ±ÛÀÎÁö ÇÑÀÚÀÎÁö ±¸ºÐ
#define IsHanja(c)	(((c) & 0x4000)==0x4000)
#define IsJapan(c)	(((c) > 0x1f00 && (c) < 0x1fb7))

#define	SWAP2BYTE(x)	(((x&0xFF00) >> 8) | ((x&0x00FF) << 8))
#define	SWAP4BYTE(x)	((((x&0x00FF0000L) >> 8) | ((x&0x0000FF00L) << 8)) | (((x&0xFF000000L) >> 24) | ((x& 0x000000FFL) << 24)))
#endif


//MultiChart Property Struct
typedef struct tagST_PROPERTY_MULTI
{	
	int		 nPrcChtType;

	COLORREF crPrcUpLine;
	BOOL	 bPrcUpFill;
	COLORREF crPrcUpBody;	
	COLORREF crPrcDownLine;
	BOOL	 bPrcDownFill;
	COLORREF crPrcDownBody;
	/*COLORREF crPrcOffLine;
	BOOL	 bPrcOffFill;
	COLORREF crPrcOffBody;*/

	COLORREF crLineColor;
	int		nLineStyle;
	int		nLineWeight;

	tagST_PROPERTY_MULTI()
	{
		nPrcChtType		= 0;
		crPrcUpLine		= 0;
		bPrcUpFill		= FALSE;
		crPrcUpBody		= 0;
		crPrcDownLine	= 0;
		bPrcDownFill	= FALSE;
		crPrcDownBody	= 0;
		crLineColor		= 0;
		nLineStyle		= 0;
		nLineWeight		= 0;
	}
	~tagST_PROPERTY_MULTI()
	{
	}
} ST_PROPERTY_MULTI,*LPST_PROPERTY_MULTI;
#define ST_PROPERTY_MULTI_SIZE sizeof(tagST_PROPERTY_MULTI)

// ³ýÈ¨Êý¾Ý½á¹¹ 
#define   MAX_CODE    30

typedef struct drdata_t
{
	//DWORD	m_dwMarket;			// Ö¤È¯ÊÐ³¡ÀàÐÍ
	//char	m_szCode[MAX_CODE];	// Ö¤È¯´úÂë,ÒÔ'\0'½áÎ²

	double	m_date;				//ÈÕÆÚ	Format is XXMMDDHHMM for 5min, Format is YYYYMMDD for day
	time_t	m_time;				//Ê±¼ä¡¡Óëm_dateÒ»ÖÂ£®Èç¹ûÊÇÊÇÄ³ÈÕ£¬ÔòÐ¡Ê±·ÖÃë¾ùÎª0

	double	m_fGive;			// Ã¿¹ÉËÍ£¬ºì¹É
	double  m_fPei;				// Ã¿¹ÉÅä
	double	m_fPeiPrice;		// Åä¹É¼Û,½öµ± m_fPei!=0.0f Ê±ÓÐÐ§
	double	m_fProfit;			// Ã¿¹ÉºìÀû£¬ÅÉÏ¢(ÒªÃ´ÎªÆÕÍ¨ÅÉÏ¢£¬ÒªÃ´ÎªÌØ±ðÅÉÏ¢,¿ÉÒÔÍ¬Ê±´æÔÚÊ±ÎªÍ¬Ò»Ìì)
	//double	m_fSpeProfit;	// Ã¿¹ÉÌØ±ðÅÉÏ¢ ,2010-2-4 ²»ÐèÔÙ¶¨Òå£¬¼ÓÔÚÉÏÃæ
	double  m_fSplit;           // ²ð·Ö¹É·Ý
	double  m_fCombine;         // ºÏ²¢¹É·Ý

	DWORD	m_dwReserved;
	drdata_t()
	{
		Reset();
	
	}


	~drdata_t()
	{

	}

	void Reset()
	{
		memset(this,0,sizeof(drdata_t));
		//memset(m_szCode,0,sizeof(m_szCode));
	}

} DRDATA, * PDRDATA;
