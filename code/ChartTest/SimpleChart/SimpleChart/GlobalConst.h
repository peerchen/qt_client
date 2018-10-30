#ifndef __GLOBALCONST_H__
#define __GLOBALCONST_H__

#pragma once

//-----------------------------------------------------------------------------
//	Pre-Include Defines 
//-----------------------------------------------------------------------------
#include <afxmt.h>
#include <afxtempl.h>


//-----------------------------------------------------------------------------

#define USE_NEW_FILEDB							///< �� FileDB ���(Hong~ �߰�)

//����Ÿ��												//					2����	:	16����	: 10����:CodeType
#define	S_MARKETTYPE_ALL					0x0000		//						 0	:	   0	:	    0	:	0	��ü

#define	S_MARKETTYPE_STOCK					0x0001		//				         1	:	   1	:	    1	:	1	�ֽ�
#define	S_MARKETTYPE_INDUSTRY				0x0002		//					    10	:	   2	:	    2	:	2	����
#define	S_MARKETTYPE_FUTURE					0x0004		//					   100	:	   4	:	    4	:	3	����
#define	S_MARKETTYPE_OPTION					0x0008		//					  1000	:	   8	:	    8	:	4	�ɼ�

#define	S_MARKETTYPE_MEMBER					0x0010		//				    1 0000	:	  10	:	   16	:	5	ȸ����
#define	S_MARKETTYPE_BOND					0x0020		//				   10 0000	:	  20	:	   32	:	6	ä��
#define	S_MARKETTYPE_EXCHANGE				0x0040		//				  100 0000	:	  40	:	   64	:	7	��ȯ/ȯ��
#define	S_MARKETTYPE_RATE					0x0080		//				 1000 0000	:	  80	:	  128	:	8	�ݸ�

#define	S_MARKETTYPE_PRODUCT				0x0100		//			   1 0000 0000	:	 100	:	  256	:	9	��ǰ
#define	S_MARKETTYPE_NEWS					0x0200		//			  10 0000 0000	:	 200	:	  512	:	10	Kofex����
#define	S_MARKETTYPE_SECURITY_OPTION		0x0400		//			 100 0000 0000	:	 400	:	 1024	:	11	�ֽĿɼ�
#define	S_MARKETTYPE_INTEREST_SWAP			0x0800		//			1000 0000 0000	:	 800	:	 2048	:	12	�ݸ�����

#define	S_MARKETTYPE_THEME					0x1000		//		   1 0000 0000 0000 :	1000	:	 4096	:	13	�׸�
#define	S_MARKETTYPE_MPDATA					0x2000		//		  10 0000 0000 0000	:	2000	:	 8192	:	14	User

#define	S_MARKETTYPE_MPDATA1				0x4000		//		 100 0000 0000 0000	:	4000	:	16384	:	15
#define	S_MARKETTYPE_MPDATA2				0x8000		//		1000 0000 0000 0000	:	8000	:	32768	:	16

#define	S_MARKETTYPE_MPDATA3				0xFFFF		//		1111 1111 1111 1111	:			:	65535	:	

// ȸ�籸��
#define	S_COMPANY_GTA						0			// GTA ��Ʈ
#define	S_COMPANY_FXPLATFORM				1			// FX(�Ϻ�)
#define	S_COMPANY_EUGENEFUTURES				2			// ��������
#define	S_COMPANY_ROYCEASSET				3			// ���̽������ڹ�


#define G_INVALID_INDEX		-1		///< Invalid Index
#define G_INVALID_SIZE		-1		///< Invalid Size
//////////////////////////////////////////////////////////////////
//	Define Const Values
#ifdef _DEBUG
//	#define G_CHART_SYSTEM_MANAGER							// [HONG...]IB���� ���� �ý��� DB�� �����Ҷ� Ǯ�� ���
#endif
//////////////////////////////////////////////////////////////////
// �̴���Ʈ ���� Definition
#define G_SCRCHT_SAVE_DELIMITER				_T('#')			// ȭ�� ��Ʈ ���� ������
#define FS									(BYTE)0x1E		// ���� ����� �ʵ带 �и��ϴ� ����(Field Separator)
#define US									(BYTE)0x1F		// ������ ��Ҹ� �и��ϴ� ����(Unit Separator)

// ȭ�� ��Ʈ ���� ����
//											MAKELONG(0, 0)	// ó�� ���� ó���� ���������� �⺻ ����
#define	G_SCRCHT_SAVE_VERSION				MAKELONG(1, 1)	// G_LAST_SLMODE_PROPERTY���� MaxMinDisplay, TitleShow�� ����, 
															// ��� G_LAST_SLMODE_ALLINDEX�� MaxMinDisplay, TitleShow, FloatingPoint�� �߰�

// ȭ�� �׷��� ���� ����
//											MAKELONG(0, 1)	// �׷��� �⺻ ����
#define	G_SCRGRP_SAVE_VERSION				MAKELONG(0, 2)	// Head, Foot, Legend Bar�� show/hide �߰�

//const double G_POSITIVEMAX					= 1E37f;				
//const double G_NEGATIVEMAX					= -1E37f;
//const float G_NOTAVAILABLE_FLOAT			= FLT_MIN;		
//const int G_NOTAVAILABLE_INT				= INT_MIN;

const int G_MAXDATASIZE						= 100000;	//�ִ� DataSize���� - �ǹ̰� ����
const int G_MINDATASIZE						= 3;		//�ּ� DataSize���� - Ȯ�븦 ��� ������ �ּҴ���
const int G_INC1MONTH						= 20;		//�Ѵ� ����(Day�ϰ��,�ƴϸ� Count����)
const int G_INC2MONTH						= 40;		//�δ� ����(Day�ϰ��,�ƴϸ� Count����)
const int G_INC3MONTH						= 60;		//���� ����(Day�ϰ��,�ƴϸ� Count����)

const UINT	G_YAXIS_POS_LEFT				= 0;		//Current YAxis Pos
const UINT	G_YAXIS_POS_RIGHT				= 1;		//Current YAxis Pos

const int	G_FORMULA_MAX_VARSIZE			= 10;
const UINT	G_MIN_CHT_HEIGHT				= 12;//20;		//Min Chart Height
const UINT	G_MIN_CHT_WIDTH					= 60;		//Min Chart Width

//const double G_PERMIT_MINVALUE				= 1.0E-07;	//�ִ����ġ �ּҰ�

const UINT	G_INIT_CHT_WIDTH				= 720;		//���� ��Ʈ ����
const UINT	G_INIT_CHT_HEIGHT				= 480;		//���� ��Ʈ ����
const UINT	G_TIMER_CHTID_INQUIRY			= 2001;

const int	G_MAX_ANS_LIST_COUNT			= 15;		//�߼���Wizard���� �ִ� �߼��� ���� ����
//const double G_MIN_CANDLE_WIDTH				= 1.5f;		//�����ν� �������ټ� �ִ� �ִ� Width��

////////////////////////////////////////////////
// File DB�� ����ϴ� �̸��� ������ 30�ڷ� �����ؾ��Ѵ� �ȱ׷�
// ������ Struct���� Hard Cording�� 30�� �Ѿ��(2006.11.28 Hong~)
const int	G_DEF_DB_NAME_MAX_SIZE			= 255;		///< �⺻ File DB�� �ִ� ����
//const int	G_INDICATOR_DB_NAME_MAX_SIZE	= 50;		///< Indicator File DB�� �ִ� ����
////////////////////////////////////////////////

const int	G_FUNCTION_DB_NAME_MAX_SIZE		= 100;		///< Function File DB�� �ִ� ����
const int	G_FORMULA_MAX_SIZE				= 4096;		///< Formula �ִ� ���� 

//��� ���� Event�� ���ϱ� ���ؼ� DelayTime(�� �ǹ� ����)
const int	G_EVENT_DELAY_TIME_LONG			= 1000;		//1��
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
const TCHAR *const G_LASTSCREEN_INFOFILE	= _T("LastScreenInfo.inf");		//������ ���� ����/�ε�
const TCHAR *const G_ENVIRONMENT_INFOFILE	= _T("EnvironmentInfo.inf");	//��Ʈȯ�漳������
const TCHAR *const G_OPTSETTING_INFOFILE	= _T("OptSettingInfo.inf");		//����ȭ��������
const TCHAR *const G_OPTRESULT_INFOFILE		= _T("OptResultInfo.inf");		//����ȭ��������
const TCHAR *const G_OPTLOGIC_INFOFILE		= _T("Logic.inf");				//����ȭLogic��������
const TCHAR *const G_OPTRESULT_HISTORYS		= _T("ResultHistory.jrh");		//����ȭ���History����
const TCHAR *const G_OPTRESULT_SUMMARYS		= _T("ResultSummary.jrs");		//����ȭ���Summary����
const TCHAR *const G_OPTRESULT_SUMMARY_REPORT = _T("ResultSummary.html");	//����ȭ���Summary - Html����
const TCHAR *const G_MENULIST_FILE			= _T("MenuList.inf");			//�޴����������ϵ��� ���̵��� �޴������ ��Ƴ��� ȭ��
const TCHAR *const G_MENULIST_FILE_JP		= _T("MenuList_JP.inf");		//

const TCHAR *const G_PRICETYPE_ORG_INFOFILE		= _T("PriceTypeOrgInfo.inf");		//PriceType OrgInfo(�Ϻ�,�ѱ�,�̱�)
const TCHAR *const G_PRICETYPE_ORG_INFOFILE_CH	= _T("PriceTypeOrgInfo_CH.inf");	//PriceType OrgInfo(�߱�)

const TCHAR *const G_OPTIMIZE_ALL_FILE		= _T("ALL_Logic.inf");			//����ȭ����� ��ü ��ϵ� ȭ�� ����

const TCHAR *const G_OPTSETTING_INFOFILE_JP	= _T("OptSettingInfoJP.inf");	//����ȭ��������

const TCHAR *const G_LASTENVIRONMENT_INFOFILE	= _T("LastEnvironment.inf");		//������ ���� ����/�ε�

const TCHAR *const G_DISPLAYMSG_INFOFILE	= _T("MsgDspEnvironmentInfo.inf");		//�޽������ڶ����/�ȶ��������������

const TCHAR *const G_CHARTCONFIG_INIFILE	= _T("ChartConfig.ini");		//ȯ�漳��(����,ȯ�漳����)

const TCHAR *const G_CHART_LIMIT_INF		= _T("ChartLimit.inf");			// ��Ʈ���Ѽ���(���̽���Ʈ���� ����...)

const TCHAR *const	G_MOVINGNETLIST_NAME	= _T("MovingAvgNet(MAN)");		//����׹���ǥ
const TCHAR *const	G_ZIGZAGIDX_NAME		= _T("ZigZag");					//ZigZag��ǥ
const TCHAR *const	G_DEMARKIDX_NAME		= _T("Demark");					//Demark��ǥ
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

static const UINT	G_MAXMULTI_CHART_COUNT	= 16;		// �ִ� ����,���ߺ���Ʈ����		
static const UINT	G_SELECT_MINSIZE		= 4;		// Select MinSize
static const UINT	G_SELECT_MAXSIZE		= 8;		// Select MaxSize

static const int	G_HEAD_GROUP_COL_SIZE	= 3;		
static const int	G_GRPHEADBAR_SIZE		= 14;
static const BOOL	G_CHTPROPERTY_LOADING	= TRUE;
static const int	G_XAXISHEIGHT			= 20;		//��Ʈ X�� ����
static const int	G_YAXISWIDTH			= 60;		//��Ʈ Y�� ����

static const int	G_HEADBAR_SIZE			= 26;		//��Ʈ ����� HeadBar
static const int	G_FOOTBAR_SIZE			= 18;		//��Ʈ �ϴ��� FootBar
static const int	G_GRIDBAR_SIZE			= 100;		//��Ʈ GridBar Size
static const int	G_SIDETOOLBAR_SIZE		= 26;		//��Ʈ �м�ToolBar Size
static const int	G_SIDEBAR_SIZE			= 165;		//��Ʈ �޴��� Size
static const int	G_SIDEBAR_POS			= 1;		//��Ʈ �޴��� Pos(����/������)
static const int	G_SIDETOOLBAR_POS		= 1;		//��Ʈ �м������޴��� Pos(����/������)
static const int	G_LEGENDBAR_SIZE		= 110;		//�׷��� ���ʹ� Size

static const int	G_MAX_ZONE_PER_CHART	= 20;		//�ִ� ��ƮZone����
static const int	G_MAX_VOLBAND_PER_CHART	= 20;		
static const int	G_MAX_IDX_PER_CHART		= 10;		//�ѿ����� �ִ� ��ǥ����

static const int	G_KIND_SYSTEM			= 0;		///< �ý��� ����(�Ǵ� �ý���)
static const int	G_KIND_USER				= 1;		///< ����� ����(�Ǵ� �����)
static const int	G_KIND_SYSCHG			= 2;		///< FileDB���� ��� �ý��� DB�� �Ӽ��� ������ ��� �ý��ۺ��� Ÿ������ ����

//static const UINT	G_MARGIN_WIDTH			= 1;		//�⺻��Ʈ MarginWidth - 1
//static const UINT	G_MARGIN_HEIGHT			= 1;		//�⺻��Ʈ MarginHeight - 1
static const UINT   G_LONGFITCH_LENGTH		= 5;		//��ƮMain������ ���� 
static const UINT   G_SHORTFITCH_LENGTH		= 3;		//��ƮSub������ ���� 

static const UINT	G_MAXCHTREGION			= 20;
static const UINT	G_MAXIDXCOUNT			= 20;		//Max Index COUNT

static const UINT	G_MATH_MAXGROUPDATA		= 42;		//Math�׷��� �ִ� �׷��
static const UINT	G_MAXEXPRESSION			= 10;		//����ǥ�� �ִ� ���ļ�
static const UINT	G_MAXIBVARIABLE			= 10;		//IB�����⿡�� �ִ� ���� ����
static const UINT	G_MAXIBBASELINE			= 10;		//IB�����⿡�� �ִ� ���ؼ�
static const UINT   G_POINT_TOLERANCE		= 4;		//��ǥ Select Margin
static const UINT   G_MAXSIGNAL_COUNT		= 5000;		//�ִ� Signal����

static const UINT   G_COMPARE_ALIGN_VER		= 0;		///< ����Ʈ ���Ĺ��(����)
static const UINT   G_COMPARE_ALIGN_HOR		= 1;		///< ����Ʈ ���Ĺ��(����)

static const UINT   G_MAX_CHART_MARGIN_SIZE	= 15;
//////////////////////////////////////////////////////////////////////////
static const UINT   G_SIGNAL_EXTEND_LENGTH	= 120;		// ָ���ļ���չ���Գ��� [kangyb 2010-08-04]

typedef CMap<int,int,CString,CString> G_GLOBALMAP;
///////////////////////////////////////////////////////////////////////////////////////////////
//			Main���� ��ġ�� ���ؼ� 

//����ȭ ����� �⺻������
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

static const UINT   G_FRMTYPE_MULTI_MAX	= 8;	//Multi Frame�� ��Ʈ Count
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

//��Ʈ ���ο��� ���Field����
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
	long	lMsg;			// Msg ����.
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
		_T("Chart Types"),				//	�Ϲ���Ʈ ����	:	10800
		_T("Main Indicators"),			//	��ͼ����ָ��		:	91580 [Vincent Chen, 10-01-26]
		_T("Sub Indicators"),			//	����ָ�����	:	10801
		_T("Strategies"),				//	����ȭ �м�		:	10802
		_T("Trading Signals"),			//	�Ÿ� �ñ׳�		:	10803
		_T("Pattern(1)"),				//	����(1)			:	11233
		//_T("Pattern(2)"),				//	����(2)			:	11234	>>>> No more "Pattern(2)" [Vincent Chen, 10-01-26]
		_T("Bull & Bear Ranges"),		//	�����༼ ����	:	10804
		_T("Templates"),				//	���ø� �м�		:	10806
		_T("Featured Tools"),			//	��ɫ������		:	91581 [Vincent Chen, 10-01-26]
		_T(""),
};

#define	IBMENU_TAB_CNT	6

const CString G_IBMENU_NAMELIST_ENG[50] = {	
		_T("Indicators"),				//	������ǥ �м�	:	10801
		_T("Strategies"),				//	����ȭ �м�		:	10802
		_T("Trading Signals"),			//	�Ÿ� �ñ׳�		:	10803
		_T("Pattern(1)"),				//	����(1)			:	11233
		_T("Bull & Bear Ranges"),		//	�����༼ ����	:	10804
		_T("Function"),					//	�Լ�(�����)		:	11078
		_T(""),
};

const CString G_PRCTYPE_NAMELIST_ENG[50] = {	
	/*General Chart*/
	_T("Market Chart"),					// [��Ȳ��Ʈ]		:	10352
		_T("Candlestick"),				// ����Ʈ			:	10227
		_T("Bar"),						// ����Ʈ			:	10202
		_T("Line"),						// ����Ʈ			:	10275
		_T("Mountain"),					// Mountain��Ʈ		:	10758
		_T("Stair Chart"),				// �����Ʈ			:	10073
		_T("Trend"),					// �߼���Ʈ			:	10642
		_T("Rise & Fall Mountain"),		// �������Ʈ		:	10165
		_T("Flow"),						// Flow��Ʈ			:	10749
		_T("Price by Volume"),			// �Ź���Ʈ			:	10192
		_T("Equivolume"),				// Equivolume��Ʈ	:	10748
		_T("Candlevolume"),				// Candlevolume��Ʈ	:	10738
		_T("Spread"),					// ������Ʈ			:	10387
		_T("Compression"),				// ������Ʈ			:	10370
		_T("Sync. Overlap"),			// SyncOverlap��Ʈ	:	10769
	/*Special Chart*/											
	_T("Special Chart"),				// [����ͼ��]		:	10232
		_T("Three Line Break"),			// ����ת��ͼ��		:	10251
		_T("Point & Figure"),			// PnFͼ��			:	10763
		_T("Renko"),					// ש��ͼ    		:	10764
		_T("Kagi"),						// ����ͼ��			:	10754
		_T("Swing"),					// ת��ͼ   		:	10768
		_T("Broken Line"),				// ����ͼ�� 		:	10126
		_T("Counterclockwise Curve"),	// ��ʱ����ͼ�� 	:	10384
		_T("Multi-Market Chart"),		// ���г��ڻ�ͼ��	:	10142
		_T("Cycle"),					// ����ͼ��			:	10551
		_T("3D Comparison Chart"),		// ��ά�Ƚ�ͼ		:	10033
		_T(""),
};

const CString G_SUBINDICATOR_ORG_NAMELIST_ENG[50] = {
	_T("General"),				// ��������ǥ		:	10537
	_T("Industry"),				// ����������ǥ		:	10376
	_T("Volume Indicators"),	// �ŷ���������ǥ	:	10062
	_T("Overlay"),				// �ְ�������ǥ		:	10548
	_T("Market Activities"),	// �ü�������ǥ		:	10335
	_T("Derivatives"),			// �Ļ�������ǥ		:	10675
	_T("Market Statistics"),	// ���庸����ǥ		:	10349
	_T("Investors"),			// ������ü��ǥ		:	10667
	_T("Fundamental"),			// �繫������ǥ		:	10456
	_T(""),
};

#define	IBMENU_INDICATOR_CNT	6
const CString G_SUBINDICATOR_IB_NAMELIST_ENG[50] = {
	_T("General"),				// ��������ǥ		:	10537
	_T("Industry"),				// ����������ǥ		:	10376
	_T("Volume Indicators"),	// �ŷ���������ǥ	:	10062
	_T("Overlay"),				// �ְ�������ǥ		:	10548
	_T(""),
};

//////////////////////////////////////////////////////////////////////////
/// ��ɫ��������ض��� [Vincent Chen, 10-01-27]
//////////////////////////////////////////////////////////////////////////
#define FEATURED_TOOLS_TYPE_CNT		10
const CString G_FEATURED_TOOLS_TYPELIST_ENG[50] = {
	_T("Editors"),				// ͼ��༭��		:	91582 (TODO: Wordbook)
	_T("Optimizers"),			// �Ż�����			:	91583 (TODO: Wordbook)
	_T(""),
};

#define FEATURED_TOOLS_ITEM_CNT		20
const CString G_FEATURED_TOOLS_ITEMLIST_ENG[50] = {
	_T("IndicatorBuilder"),				// ����ָ��༭��		:	10752
	_T("CandlePatternEditor"),			// ����ͼ�༭��			:	10740
	_T("IBOptExecutor"),				// ����ָ������Ż�����	:	10624
	_T(""),
};
//////////////////////////////////////////////////////////////////////////

// �Ϻ�FX (����) ĵ���Լ� �߿��� ���ܽ�ų �׸� 
const CString G_EXCEPTION_CANDLE_JP[41] = { _T("BEAR"),		   _T("BEARBTL"),	_T("BEARBTS"),	  _T("BEARSTAR"),		 _T("BEARUTL"),		
											_T("BEARUTS"), 	   _T("BULL"),	    _T("BULLBTL"),	  _T("BULLBTS"),		 _T("BULLSTAR"),
											_T("BULLUTL"),	   _T("BULLUTS"),   _T("DARKCLOUD"),  _T("DNCOUNTERATTACK"), _T("DNENGULF"),
											_T("DNHARAMI"),	   _T("DNONNECK"),  _T("UPONNECK"),	  _T("DNPIERCE"), 		 _T("DNPIERCE"),
											_T("DNSTAR"),	   _T("DNTHRUST"),  _T("DOJI"),		  _T("DSD"),			 _T("DSS"),
											_T("EVENINGSTAR"), _T("HAMMER"),	_T("HANGINGMAN"), _T("MORNINGSTAR"), 	 _T("SHOOTINGSTAR"),
											_T("THREEBEAR"),   _T("THREEBULL"),	_T("TWOCROWS"),   _T("UPCOUNTERATTACK"), _T("UPENGULF"),
											_T("UPHARAMI"),	   _T("UPONNECK"),	_T("UPPIERCE"),   _T("UPSTAR"),			 _T("UPTHRUST"),		 
											_T("WHITECLOUD")   };

// ����Ÿ���� �߿��� ���ܽ�ų �׸� 
const CString G_EXCEPTION_DATAVAR_NAME_JP[2] = {_T("V,VOLUME,�ŷ���"), _T("VM,VOLUMEMONEY,�ŷ����") };
//// �⺻������ �߿��� ���ܽ�ų �׸� 
//const CString G_EXCEPTION_BASICOP_NAME_JP[0] = {	_T("") };
// ���п����Լ� �߿��� ���ܽ�ų �׸� 
const CString G_EXCEPTION_MATHOP_NAME_JP[1] = {	_T("AVER") };
// �Լ�ȣ���Լ� �߿��� ���ܽ�ų �׸� 
const CString G_EXCEPTION_FUNCALL_NAME_JP[12] = { _T("STD"),	_T("TMA,TAVG"), _T("MAX"),	_T("MIN"),	  _T("PMAX"),
												 _T("PMIN"),	_T("STRONG"),	_T("WEAK"),	_T("REGION"), _T("PERCENTAGE"),
												 _T("HAFTER"),	_T("LAFTER") };
// ��ü�⺻�Լ�
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


// �Ϻ�FX (��ȯ) CandlePatern �߿��� �̸��� �ٲ� �׸� 
const CString G_EXCEPTION_CP_RENAME_JP[2] = { _T("BullishGapSideBySide"), _T("BearishGapSidebySide") };

// �Ϻ�FX (��ȯ) CandlePatern �߿��� ���̸� �׸� 
const CString G_EXCEPTION_CP_NEWNAME_JP[2] = { _T("Side by Side White Lines"), _T("Side by Side Black Lines") };

//////////////////////////////////////////////////////////////////////////

const CString G_VOLTYPE_NAMELIST_ENG[6] = 
{
	_T("Volume Bar Chart"),					// �ŷ�Bar��Ʈ
	_T("Volume Line Chart"),				// �ŷ�Line��Ʈ
	_T("Volume Mountain Chart"),			// �ŷ�Mountain��Ʈ
	_T("Volume White & Black Bar Chart"),	// �ŷ�����Bar��Ʈ
	_T("Price White & Black Bar Chart"),	// �ְ�����Bar��Ʈ
	_T("Execution Bar Chart")				// ü��Bar��Ʈ
};

const CString G_VOLTYPE_NAMELIST[6] = 
{
	_T("�ŷ�Bar��Ʈ"), _T("�ŷ�Line��Ʈ"), _T("�ŷ�Mountain��Ʈ"), _T("�ŷ�����Bar��Ʈ"), _T("�ְ�����Bar��Ʈ"), _T("ü��Bar��Ʈ")
};

const int G_VOLTYPE_NAMEIDLIST[6] = 
{
	           10067,   		   10068,			   	   10069,				   10066,		  	    10549,		   10601
};

const CString G_ITEMNIND_DBNAME[7] = { _T("Open"), _T("High"), _T("Low"), _T("Close"), _T("(H + L) / 2"), _T("(H + L + C) / 3"), _T("(H + L + C * 2) / 4")};

//////////////////////////////////////////////////////////////////////////////

const int	G_MAXSYMBOLLIST	= 100;
static TCHAR* G_CPSYMBOLLIST[G_MAXSYMBOLLIST]	= { _T("��(�ż�)"), _T("��(�ŵ�)"),		_T("��(ȯ�ż�)"),	_T("��(���ŵ�)"),	_T("��(����)"), 
_T("��(����)"), _T("��(��)"),		_T("��(����)"),		_T("��(����)"),		_T("��(��)"), 
_T("��(����)"), _T("��(�������)"), _T("��(�϶�����)"),	_T("��(�ٴ�)"),		_T("��(õ��)"),
_T("?(��Ȯ��)"),_T("+(����)"),      _T("-(����)"),
_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T("��"),_T(""),};

static int G_CPSYMBOLIDLIST[G_MAXSYMBOLLIST]	= { 10013, 10015, 10024, 10023, 10014, 
10016, 10012, 10017, 10005, 10006, 
10019, 10018, 10020, 10022, 10021, 
10004, 10007, 10002, 0, };

//�ż�,�ŵ�,ȯ�ż�,���ŵ�,����,����,��,����,����,��,����,�������,�϶�����,�ٴ�,õ��,��Ȯ��,����,����,....���ڵ�

static TCHAR* G_CPSIGNALLIST[G_MAXSYMBOLLIST]= { _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), 
_T("��"), _T("��"), _T("��"), _T("��"), _T("?"),  _T("+"),  _T("-"),  _T("��"), 
_T("��"), _T("��"), _T("��"), _T("��"),  _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
_T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("")};

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
static TCHAR* G_TICK_DATATYPE_LIST[G_TICK_DATATYPE_MAXCOUNT]= {_T("1ƽ"),_T("2ƽ"),_T("3ƽ"),_T("4ƽ"),_T("5ƽ"),_T("")};
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

// �ϸ���� ������
//const CString G_ICHIMOKU_NAME[8] = { _T("���ؼ�"), _T("��ȯ��"), _T("���ེ��"), _T("���ེ��1"), _T("���ེ��2"), _T("������1"), _T("������2"), _T("������3") };
const CString G_ICHIMOKU_NAME[8] = { _T("��׼��"), _T("ת����"), _T("���м��"), _T("ǰ�м��1"), _T("ǰ�м��2"), _T("Ԥ�����1"), _T("Ԥ�����2"), _T("Ԥ�����3") };

const int G_ICHIMOKU_ID[8] = { 11128, 11129, 11130, 11131, 11132, 11133, 11134, 11135 };

//////////////////////////////////////////////////////////////////////////////

// FileDB Section String
const TCHAR *const	G_FD_SECTION_IND_ITEM			= _T("INDICATES@ITEM_SUPPORT");			// ��������ǥ
const TCHAR *const	G_FD_SECTION_IND_UPJONG			= _T("INDICATES@UPJONG_SUPPORT");		// ����������ǥ
const TCHAR *const	G_FD_SECTION_IND_VOLUME			= _T("INDICATES@VOLUME_SUPPORT");		// �ŷ���������ǥ
const TCHAR *const	G_FD_SECTION_IND_PRICE			= _T("INDICATES@PRICE_SUPPORT");		// �ְ�������ǥ
const TCHAR *const	G_FD_SECTION_IND_STOCK			= _T("INDICATES@STOCK_SUPPORT");		// �ü�������ǥ
const TCHAR *const	G_FD_SECTION_IND_DERIVE			= _T("INDICATES@DERIVATION_SUPPORT");	// �Ļ�������ǥ
const TCHAR *const	G_FD_SECTION_IND_MARKET			= _T("INDICATES@MARKET_SUPPORT");		// ���庸����ǥ
const TCHAR *const	G_FD_SECTION_IND_INVESTOR		= _T("INDICATES@INVESTOR_SUPPORT");		// ������ü��ǥ
const TCHAR *const	G_FD_SECTION_IND_FINANCIAL		= _T("INDICATES@FINANCIAL_SUPPORT");	// �繫������ǥ
const TCHAR *const	G_FD_SECTION_IND_OVERLAB		= _T("INDICATES@OVERLAB_SUPPORT");		// �߰�����ǥ
const TCHAR *const	G_FD_SECTION_OPT				= _T("OPTIMIZES");						// ����ȭ
const TCHAR *const	G_FD_SECTION_SIG				= _T("SIGNALS");						// �ñ׳�
const TCHAR *const	G_FD_SECTION_SHOW				= _T("SHOWATS");						// ����
const TCHAR *const	G_FD_SECTION_FUN				= _T("FUNCTIONS");						// �Լ�
const TCHAR *const	G_FD_SECTION_CP_REVERSE_BULL	= _T("REVERSE@BULLISH");				// ��¹���
const TCHAR *const	G_FD_SECTION_CP_CONTINUE_BULL	= _T("CONTINUE@BULLISH");				// �������
const TCHAR *const	G_FD_SECTION_CP_REVERSE_BEAR	= _T("REVERSE@BEARISH");				// �϶�����
const TCHAR *const	G_FD_SECTION_CP_CONTINUE_BEAR	= _T("CONTINUE@BEARISH");				// �϶�����

// FileDB Section Name
const TCHAR *const	G_FD_SECTIONNAME_IND_ITEM			= _T("��������ǥ");				// ��������ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_UPJONG			= _T("����������ǥ");				// ����������ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_VOLUME			= _T("�ŷ���������ǥ");				// �ŷ���������ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_PRICE			= _T("�ְ�������ǥ");				// �ְ�������ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_STOCK			= _T("�ü�������ǥ");				// �ü�������ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_DERIVE			= _T("�Ļ�������ǥ");				// �Ļ�������ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_MARKET			= _T("���庸����ǥ");				// ���庸����ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_INVESTOR		= _T("������ü��ǥ");				// ������ü��ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_FINANCIAL		= _T("�繫������ǥ");				// �繫������ǥ
const TCHAR *const	G_FD_SECTIONNAME_IND_OVERLAB		= _T("�߰�����ǥ");				// �߰�����ǥ
const TCHAR *const	G_FD_SECTIONNAME_OPT				= _T("����ȭ");						// ����ȭ
const TCHAR *const	G_FD_SECTIONNAME_SIG				= _T("�ñ׳�");						// �ñ׳�
const TCHAR *const	G_FD_SECTIONNAME_SHOW				= _T("����");						// ����
const TCHAR *const	G_FD_SECTIONNAME_FUN				= _T("�Լ�");						// �Լ�
const TCHAR *const	G_FD_SECTIONNAME_CP_REVERSE_BULL	= _T("��¹���");					// ��¹���
const TCHAR *const	G_FD_SECTIONNAME_CP_CONTINUE_BULL	= _T("�������");					// �������
const TCHAR *const	G_FD_SECTIONNAME_CP_REVERSE_BEAR	= _T("�϶�����");					// �϶�����
const TCHAR *const	G_FD_SECTIONNAME_CP_CONTINUE_BEAR	= _T("�϶�����");					// �϶�����

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
	G_ANSTYPE_PARALLEL					= 2,            //ƽ����
	G_ANSTYPE_EQUIVALENCE				= 3,			//�ȼ���
	G_ANSTYPE_AUTOTREND					= 4,			//�Զ���������
	G_ANSTYPE_TURNINGLINE				= 5,            //��������
	G_ANSTYPE_TIMECYCLE					= 6,            //ʱ�������ߣ������м�Ӻܶ�Բ��
	/////////////////////////////////////////////////////
	G_ANSTYPE_TARGETLINE				= 7,            //Ŀ���ߣ�������ƽ�еĺ��ߣ�
	G_ANSTYPE_STOPLOSSLINE				= 8,            //ֹ���ߣ�������ƽ�еĺ��ߣ�
	G_ANSTYPE_GOLDENRULE				= 9,            //�ƽ�ָ��ߣ����˵�ƽ���ߣ�
	G_ANSTYPE_SILVERRULE				= 10,           //ǿ��֧��(���������㣬�����ƽ�к�����Ϊ֧����)
	G_ANSTYPE_DOUBLERULE				= 11,           //˫֧��(���������㣬�����ƽ�к�����Ϊ֧����)
	G_ANSTYPE_TURNINGFAN				= 12,           //��תɡ����ɢ��ɡ���ߣ�
	/////////////////////////////////////////////////////
	G_ANSTYPE_ELLIOTWAVELINE			= 13,           //�����ز�����
	G_ANSTYPE_ELLIOTWAVEARCUP			= 14,           //����������������
	G_ANSTYPE_ELLIOTWAVEARCDOWN			= 15,           //����������������
	/////////////////////////////////////////////////////
	G_ANSTYPE_FREELINE					= 16,           //���ɻ�����
	G_ANSTYPE_TRENDLINE					= 17,			//�����ߣ��Լ�����ֱ�ߣ�
	G_ANSTYPE_HORIZONTAL				= 18,			//��ˮƽ��
	G_ANSTYPE_VERTICAL					= 19,			//����ֱ��
	G_ANSTYPE_CROSS						= 20,			//��ʮ�ֽ�����
	/////////////////////////////////////////////////////
	G_ANSTYPE_FIBARC					= 21,           //쳲����� ����
	G_ANSTYPE_FIBFAN					= 22,			//쳲����� ɡ����
	G_ANSTYPE_FIBRETRACEMENT			= 23,			//쳲����� ˮƽ�ع���
	G_ANSTYPE_FIBVERTICALRET			= 24,			//쳲����� ��ֱ�ع���
	G_ANSTYPE_FIBTIMEGOALDAY			= 25,			//쳲����� ʱ��Ŀ������
	G_ANSTYPE_FIBTIMEZONES				= 26,			//쳲����� ʱ�䴰��
	/////////////////////////////////////////////////////
	G_ANSTYPE_GANNLINE					= 27,           //�����Ƕ���
	G_ANSTYPE_GANNFAN					= 28,			//������
	G_ANSTYPE_GANNRETRACEMENT			= 29,			//�����ع�
	G_ANSTYPE_GANNGRID					= 30,			//��������
	/////////////////////////����////////////////////////
	G_ANSTYPE_QUADRANTLINE				= 31,
	G_ANSTYPE_TIRONELEVELS				= 32,
	G_ANSTYPE_SPEEDRESISTANCEARC		= 33,
	G_ANSTYPE_SPEEDRESISTANCEFAN		= 34,
	G_ANSTYPE_ANDREWPITCHFORK			= 35,
	//////////////////////////ͼ��/////////////////////////
	G_ANSTYPE_ANGLE						= 36,           //�Ƕ�
	G_ANSTYPE_DIFFER					= 37,           //������
	G_ANSTYPE_ELLIPSE					= 38,           //��Բ
	G_ANSTYPE_RECTANGLE					= 39,           //����
	G_ANSTYPE_TRIANGLE					= 40,			//������
	G_ANSTYPE_DIAMOND					= 41,	        //����
	/////////////////////////////////////////////////////
	G_ANSTYPE_SYMBOL					= 42,			//��ʶ����
	G_ANSTYPE_TEXT						= 43,			//�ı�
	//////////////////////////��Ĭ��///////////////////////////	
	G_ANSTYPE_OBVIOUSEQUALVALUE			= 44,	        //��ֵ
	G_ANSTYPE_OBVIOUSEQUALTIME			= 45,	        //ʱ��
	G_ANSTYPE_TIMEINTERVAL				= 46,			//ʱ������
	G_ANSTYPE_VALUEINTERVAL				= 47,			//��ֵ����
	/////////////////////////////////////////////////////
	G_ANSTYPE_LINEARREGRESSION			= 48,			//���Իع�
	G_ANSTYPE_RAFFREGRESSION			= 49,			//�ع�ͨ��
	G_ANSTYPE_STANDARDDEVIATION			= 50,			//��׼ƫ��
	G_ANSTYPE_STANDARDERROR				= 51,			//��׼���
	//////////////////////////////////////////////////////	
	G_ANSTYPE_REMOVEAT					= 55,	
	G_ANSTYPE_REMOVEALL					= 56,	
	G_ANSTYPE_CONTINUE_FLAG				= 57,	
};

enum EnANSCursorID
{		
	G_ANSCURSOR_ARROW					= 0,		//�߼���Ŀ��-ȭ��ǥ
	G_ANSCURSOR_PEN						= 1,		//�߼���Ŀ��-Pen
	G_ANSCURSOR_SYMBOL					= 2,		//�߼���Ŀ��-�ɺ�
	G_ANSCURSOR_TEXT					= 3,		//�߼���Ŀ��-�ؽ�Ʈ
	G_ANSCURSOR_AUTO					= 4,		//�߼���Ŀ��-Auto
	G_ANSCURSOR_DISABLE					= 5,		//�߼���Ŀ��-Disable
};

enum EnANSLineDrawStyle
{
	G_ANSDRAW_LINE						= 0,		//�߼���-����
	G_ANSDRAW_RECTANGLE					= 1,		//�߼���-�簢��
	G_ANSDRAW_ELLIPSE					= 2,		//�߼���-Ÿ��
	G_ANSDRAW_CIRCLE					= 3,		//�߼���-��
	G_ANSDRAW_HALFCIRCLE				= 4,		//�߼���-�ݿ�
	G_ANSDRAW_ARC						= 5,		//�߼���-ȣ
	G_ANSDRAW_POINT						= 6,		//�߼���-��
};

enum EnANSLineExtStyle
{
	G_ANSEXT_LINE						= 0,		//�߼���-����
	G_ANSEXT_START						= 1,		//�߼���-���ν���Ȯ��
	G_ANSEXT_END						= 2,		//�߼���-���γ�Ȯ��
	G_ANSEXT_BOTH						= 3,		//�߼���-��üȮ��
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
	G_ANSSELED_LINE_OTHERS				= 9,		//FibLines,...ElliotWave...���� ���μ��� 3�� �Ѵ� �߼��� Select
};

enum EnIBTypeMode
{
	G_IBTYPE_MODE_NONE					= -1,		//����
	G_IBTYPE_MODE_IND					= 0,		//��ǥ
	G_IBTYPE_MODE_OPT					= 1,		//����ȭ
	G_IBTYPE_MODE_SIG					= 2,		//�ñ׳�
	G_IBTYPE_MODE_SHOWAT				= 3,		//��������
	G_IBTYPE_MODE_BASIC					= 4,		//�⺻�Լ�
};

enum EnIBWorkModeType
{
	G_IBWORK_MODE_NEW					= 0,		//�߰�
	G_IBWORK_MODE_COPY					= 1,		//����
	G_IBWORK_MODE_MODIFY				= 2,		//����
	G_IBWORK_MODE_DELETE				= 3,		//����
	G_IBWORK_MODE_RENAME				= 4,		//���̷�
	G_IBWORK_MODE_DISABLED				= 5,		//�ʱ������
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
	G_REQUEST_ITEM_MAIN		= 0,		//Main��Ʈ��ȸ
	G_REQUEST_ITEM_MARIND	= 1,		//���庸����ǥ��ȸ
	G_REQUEST_ITEM_OVERLAP	= 2,		//SyncOverlap��ȸ
	G_REQUEST_ITEM_CALC		= 3,		//������Ʈ��ȸ
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
	G_REQUEST_TYPE_MAIN_DB	= 0,		// MainDB��ȸ
	G_REQUEST_TYPE_MAIN_FIELD= 1,		// MainField��ȸ
	G_REQUEST_TYPE_SUB_DB	= 2,		// SubDB��ȸ
	G_REQUEST_TYPE_SUB_FIELD= 3,		// SubField��ȸ
	G_REQUEST_TYPE_BOND_DB	= 4,		// Bond��ȸ
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
//#define		G_USERMSG_CHTPROPERTY			WM_USER + 107	// ���� ��� ����.(2006.09.01 Hong~)
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
#define		G_USERMSG_ANSTOOL_SELECT		WM_USER + 126		// �߼������� Message
#define		G_USERMSG_ANSTEXT_END			WM_USER + 127		// �߼����߿��� Text Edit�� Message exchange
#define		G_USERMSG_HORIZONTAL_INFO		WM_USER + 128		// ���� ��ġ��ȸ 
#define		G_USERMSG_VERTICAL_INFO			WM_USER + 129		// ���� ��ġ��ȸ 
#define		G_USERMSG_CROSS_INFO			WM_USER + 130		// ���� ��ġ��ȸ 
#define		G_USERMSG_ANSINFO_CHANGE		WM_USER + 131		// �߼��� ���� 
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

//��ǥ��ȸ
#define		G_USERMSG_INDEXITEM_REQUEST		WM_USER + 191	

//����ȭ ����
#define		G_USERMSG_OPTRESULT_PROGRESS	WM_USER + 192	
#define		G_USERMSG_OPTRESULT_SIGEVENT	WM_USER + 193	
#define		G_USERMSG_OPTRESULT_EVENT		WM_USER + 194	

//Chart Data Request Msg
#define		G_USERMSG_PERIOD_TICK			WM_USER + 195		// Tick Data ��û	
#define		G_USERMSG_PERIOD_INTRA			WM_USER + 196		// Intra Data ��û	
#define		G_USERMSG_PERIOD_DAY			WM_USER + 197		// Day Data ��û	
#define		G_USERMSG_PERIOD_WEEK			WM_USER + 198		// Week Data ��û
#define		G_USERMSG_PERIOD_MONTH			WM_USER + 199		// Month Data ��û
#define		G_USERMSG_PERIOD_QUARTER		WM_USER + 200		// Quarter Data ��û
#define		G_USERMSG_PERIOD_YEAR			WM_USER + 201		// Year Data ��û
// TradingTrend ��뿩�� �Ǵ�
#define		G_USERMSG_GETAVAILABLETRADINGTREND	WM_USER + 202

//////////////////////////////////////////////////////////////////////////////

#define		G_USERMSG_SLIDERZOOM			WM_USER + 203	// Slider Message

#define		G_USERMSG_CHARTINIT				WM_USER + 204	// ��Ʈ �ʱ�ȭ��ư

#define		G_USERMSG_ANSTOOL_UNSELECT		WM_USER + 205	// �߼��� �̼��� Message

#define		G_USERMSG_PERIOD_SUBBTN_MSG		WM_USER + 206	// Period Sub Button Message

#define		G_USERMSG_SIDEBARINFO			WM_USER + 207	// Bar ������ �������ش�.

#define		G_USERMSG_OPTEXE_OVERLAPCHECK	WM_USER + 208	// ȭ���ߺ��� üũ�Ѵ�.
#define		G_USERMSG_OPTEXE_TREEAPPEND		WM_USER + 209	// TREE�� ����ȭ�� �߰��Ѵ�.

#define		G_USERMSG_INDICATORBUILDER		WM_USER + 300	// IndicatorBuilder ȣ��

#define		G_USERMSG_MODIFY				WM_USER + 301	// Modify

#define		G_USERMSG_INDICATORPROPERTYDLG	WM_USER + 302	// IndicatorProperty ȣ��

#define		G_USERMSG_PROPERTY_CONFIG		WM_USER + 303	// Config (����Ͼ��, �޷�, SkinStyle, SkinColor)

#define		G_USERMSG_ANALYSISBAR_APPLY		WM_USER + 304	// �߼��� ����

#define		G_USERMSG_ANALYSIS_SCREENAREA_SETTING	WM_USER + 305	// '������ ��������'�߼������� ȭ������� ������� �޽���

#define		G_USERMSG_ANALYSIS_CANCEL		WM_USER + 306	// '������ ��������'�߼��� ������� �޽���

#define		G_USERMSG_KEY_CROSSMOVE			WM_USER + 307	// Ű���忡 ���� ���ڼ� �̵�
#define		G_USERMSG_KEY_ZOOM				WM_USER + 308	// Ű���忡 Ȯ��/���

#define		G_USERMSG_MPERIOD_SIDETOOLBAR	WM_USER + 309	

#define		G_USERMSG_LAST_PROPERTY			WM_USER + 310

#define		G_USERMSG_MAXDATA_SETTING		WM_USER + 311	// �м���Ʈ�϶� SliderBar �纸��


#define		G_USERMSG_PERIOD_ROTATE			WM_USER + 312	// ��ȸ Ÿ�� ��ȯ

//////////////////////////////////////////////////////////////////////////////
#define		G_USERMSG_PERIOD_GETPROPERTY	WM_USER + 500

//////////////////////////////////////////////////////////////////////////////
/// ����Ϊ��ɫ��������ʹ�õ���Ϣ [Last Modified: Vincent Chen, 10-01-27]
//////////////////////////////////////////////////////////////////////////////
#define		G_USERMSG_TOOLS_EXECUTE				WM_USER + 600	// ִ�й���
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// ��ɫ����ö�ٱ�ʶ [Last Modified: Vincent Chen, 10-01-27]
//////////////////////////////////////////////////////////////////////////////
enum EnFeaturedTools
{
	IndicatorBuilder = 100,	// ����ָ��༭��
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
	TCHAR	chChtStCode[30];			//���� Standard�ڵ�
	TCHAR	chChtName[30];				//���� ��
	TCHAR	chItemName[30];				//�ð�,����...
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
	int		nMarketCode;				//0:�ֽ�,1:�ڽ�Ź,2:����,3:�ɼ�.....
	TCHAR	chItemStCode[20];			//���� Standard�ڵ�
	TCHAR	chItemCode[20];				//���� �ڵ�
	TCHAR	chItemName[30];				//���� ��

	UINT	nDataPeriod;				//Tick,Intra,Day,Week,Month,Year....
	UINT	nDataCycle;					//1Tick,2Tick,.....
	UINT	nDateDayInfo;				//1��,2��

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
	BOOL	bItemSaved;					//TRUE:�Ʒ� ���� �״�� Save & Load
										//FALSE:�Ʒ� ���� ������� Chart ������	

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

	//���� ©������ ������� - ��� ǥ���Ҽ��� ����
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

		//���� ©������ ������� - ��� ǥ���Ҽ��� ����
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

//���ڰ� ������ �ִ� PriceType��
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
	int		nCalcType;			//0:TurningRatio,1:ȣ��,2����
	double  dChartValue1;		//������,��ȣ��,����,3��<->4����ȯ��
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
	int		 nPrcType;				///< Price(Main)��Ʈ Ÿ�� (G_PRCCHT_CANDLE,...)

	COLORREF crPrcUpLine;			///< ��� ���λ�
	BOOL	 bPrcUpFill;			///< ��� ����ü���� ä������ ����
	COLORREF crPrcUpBody;			///< ��� ����ü��
	COLORREF crPrcDownLine;			///< �϶� ���λ�
	BOOL	 bPrcDownFill;			///< �϶� ����ü���� ä������ ����
	COLORREF crPrcDownBody;			///< �϶� ����ü��

	COLORREF crPrcFlat;				///< ���� ����/��ü��
	BOOL	 bPrcFlat;				///< ���� ����/��ü���� �ڵ������� ���ο��� ���Ѵ�� ������ ����

	COLORREF crPrcOffLine;			///< �Ź��� ���λ�
	BOOL	 bPrcOffFill;			///< �Ź��� ����ü���� ä������ ����
	COLORREF crPrcOffBody;			///< �Ź��� ����ü��

	int		nDataType;				///< ���� ������(��,��,��,��, �ð�����,...)
	COLORREF crLineColor;			///< ���λ�
	int		nLineStyle;				///< ���ν�Ÿ��
	int		nLineWeight;			///< ���α���

	int		nDefineBase;			///< �������(��������>���Ͻð�, ��������>��������, ��������>���ذ�)
									///< ���߸޹���Ʈ���� �Ź��ð����� ���
	double	dBaseValue;				///< ������ذ�(��������>���ذ��� ���ذ�)

	BOOL	bLastPrevLine;			///< ���������� ǥ�� ����
	COLORREF crLastPrevLine;		///< ������������
	int		nPrevLineStyle;			///< ���������� ��Ÿ��
	int		nPrevLineWeight;		///< ���������� ����

	BOOL	bMaxMinDisplay;			///< �ִ�/�ּҰ� ǥ��
	BOOL	bLogScale;				///< �α���Ʈ
	BOOL	bInvertScale;			///< ������Ʈ
	BOOL	bTitleShow;				///< Ÿ��Ʋ����
	BOOL	bGradationShow;			///< Gradationȿ��

	BOOL	bAutoOffering;			///< �ڵ� �Ź��� ����
	int		nOfferingCount;			///< �Ź����� ����
	double  dIndexValue1;			///< Price(Main)��Ʈ�� �ʿ䰪(��:������Ʈ�� �������, SyncOverlap��Ʈ�� �����)
	double  dIndexValue2;			///< Price(Main)��Ʈ�� �ʿ䰪2(��:SyncOverlap��Ʈ�� �׸�����)

	//2005/03/07 - ���� ��Ʈ������ ���� �߰��� �κ�
	int		nCalcInfo;
	TCHAR	chCalcInfo[30];
	TCHAR	chMainStCode[30];
	TCHAR	chSub1StCode[30];
	TCHAR	chSub2StCode[30];
	int     nTwoCandleStyle;        //[kenny]  2010-1-12  Ĭ���ǡ���ɫ������

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
	int		nVolumeType;			///< �ŷ�������(�ŷ�Bar, �ŷ�Line, �ŷ�Mountain, �ŷ�����Bar, �ְ�����Bar)

	COLORREF crVolLine;				///< �����λ�
	BOOL	 bVolFill;				///< ����ü���� ä������ ����
	COLORREF crVolBody;				///< ����ü��
	int		nLineStyle;				///< �ŷ�Line�϶� Line Style
	int		nLineWeight;			///< �ŷ�Line�϶� Line Weight

	COLORREF crVolUpLine;			///< �ŷ�/�ְ� ������� ��� ���λ�
	BOOL	 bVolUpFill;			///< �ŷ�/�ְ� ������� ��� ����ü���� ä������ ����
	COLORREF crVolUpBody;			///< �ŷ�/�ְ� ������� ��� ����ü��

	COLORREF crVolDownLine;			///< �ŷ�/�ְ� ������� �϶� ���λ�
	BOOL	 bVolDownFill;			///< �ŷ�/�ְ� ������� �϶� ����ü���� ä������ ����
	COLORREF crVolDownBody;			///< �ŷ�/�ְ� ������� �϶� ����ü��

	BOOL	bMaxMinDisplay;			///< �ִ��ּҰ�ǥ��
	BOOL	bLogScale;				///< LogScale
	BOOL	bTitleShow;				///< Title����
	BOOL	bGradationShow;			///< Gradationȿ��

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
	int		nXAxisTimeType;			///< ƽ/�� ��Ʈ�� �ð� ǥ�� ���
	int		nXAxisDayType;			///< ���ֿ� ��Ʈ�� ��¥ ǥ�� ���
	
	int		nXAxisSpace;			///< X�� ���� ����(+ ������, - ���� �������)
	
	BOOL	bShowFirstData;			///< ù������ǥ��
	int		nFirstDataType;			///< ù������ ǥ�� ���
	COLORREF crFirstText;			///< ù������ ���ڻ�

	BOOL	bShowLastData;			///< ������������ǥ��
	int		nLastDataType;			///< ������������ ǥ�� ���
	COLORREF crLastText;			///< ������������ ���ڻ�

	BOOL	bShowXAxis;				///< X�� ���̱�
	BOOL	bShowWeekMark;			///< �ִ��� ��ũ ���̱�
	COLORREF crBackGround;			///< X�� ������
	COLORREF crForeGround;			///< X�� ���ڻ�

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
	int		nQueryPeriod;		///< ��ȸ Period(G_CHTPERIOD_TICK,..) ///<
	int		nQueryType;			///< ??? ///<

	int		nSection;			///< ����(0:������(1ƽor��)1��2��.., 1:��¥����, 2:��������)

	int		nTickMinVal;		///< 1ƽ,2ƽ,3ƽ... or 1��,2��,3��(�ʷα��)...
	int		nDateVal;			///< 1��,2��,3��,4��,5��...
	int		nOptionVal;			///< ����(nTickMinVal = -1 < Intra �϶� ���� ������ ������(�ֱ���Ʈ ����)...�и� ����������.>)

	double	dStartDateTime;		///< �����Ͻ�(20070527091200)
	double	dEndDateTime;		///< ��  �Ͻ�(20070528102000)

	BOOL	bQueryFull;			///< ��ü�����Ϳ䱸	///<
	int		nQueryCount;		///< ��ȸ���� ///<
	int		nViewCount;			///< ȭ�鿡 ������ ���� ///<

	BOOL	bFixedEndDateTime;	///< �̶��Ľ������ڣ����������ݲ�ʵʱ���¡�[Vincent Chen, 10-01-07]

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
		bFixedEndDateTime = FALSE;	/// Ĭ�ϲ��̶��̶��������ڡ�[Vincent Chen, 10-01-07]
	}
	~tagST_QUERY_TYPE_INFO()
	{
	}
}ST_QUERY_TYPE_INFO,*LPST_QUERY_TYPE_INFO;
#define ST_QUERY_TYPE_INFO_SIZE sizeof(tagST_QUERY_TYPE_INFO)

typedef struct tagST_CYCLE_QUERY_TYPE_INFO
{
	int		nQueryPeriod;		///< ��ȸ Period(G_CHTPERIOD_TICK,..) ///<

	int		nSection;			///< ����(0:������(1ƽor��)1��2��.., 1:��¥����, 2:��������)

	int		nMinVal;			///< 10��,20��,30��,1��,2��,3��(�ʷα��)...
	int		nDateVal;			///< 2��,3��,4��,5��,6��,7�� / 2��,3��,4��,5��,6��,7��

	double	dStartDateTime;		///< �����Ͻ�(20070527091200)
	double	dEndDateTime;		///< ��  �Ͻ�(20070528102000)


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
	BOOL	bHeadBarShow;			///< HeadBar���̱�
	BOOL	bFootBarShow;			///< FootBar���̱�
	BOOL	bSideBarShow;			///< Sidebar���̱�
	BOOL	bSideToolBarShow;		///< SideToolBar���̱�
	BOOL	bDataGridBarShow;		///< DataGridBar���̱�

	ST_QUERY_TYPE_INFO stQueryTypeInfo[10];	///< ��ȸ������ ����(Day�� ��ü�����Ϳ䱸 �Ǵ� ��������, View Count������..)
	//--  2004/09/15

	int		nScreenBKType;			///< ȭ���漳��(0:Color BK Screen,1:WallPaper - Image BK Screen)
	COLORREF crBKColor;				///< ȭ�����
	TCHAR	szWallPaperPath[300];	///< WallPaper ���� ���

	BOOL	bScreenHorizon;			///< ���򴫱��� ��뿩��
	int		nScreenHLineType;		///< ���򴫱��� Ÿ��(solid, dot...)
	int		nScreenHLineWeight;		///< ���򴫱��� ����
	COLORREF crScreenHLineColor;	///< ���򴫱��� ��
	BOOL	bScreenHBackward;		///< ���򴫱��� ȭ�� �ڿ� ǥ�������� ����

	COLORREF crScreenHLineFillColor;	///< ���򴫱��� Fill ��

	BOOL	bScreenVertical;		///< ���������� ��뿩��
	int		nScreenVLineType;		///< ���������� Ÿ��(solid, dot...)
	int		nScreenVLineWeight;		///< ���������� ����
	COLORREF crScreenVLineColor;	///< ���������� ��
	BOOL	bScreenVBackward;		///< ���������� ȭ�� �ڿ� ǥ�������� ����	

	BOOL	bDataGapCorrect;		///< DataGap����	
	BOOL	bDataOff;				///< �����ְ�����
	BOOL	bDataLimit;				///< ��/���Ѱ�ǥ��
	BOOL	bDataOption;			///< �ɼ���簡ǥ��	

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
	int		nQueryPeriod;		///< ��ȸ Period(G_CHTPERIOD_TICK,..) ///<
	int		nQueryType;			///< ??? ///<
	BOOL	bQueryFull;			///< ��ü�����Ϳ䱸	///<
	int		nQueryCount;		///< ��ȸ���� ///<
	int		nViewCount;			///< ȭ�鿡 ������ ���� ///<

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
	USHORT	nFontType;				///< ��Ʈ Ÿ��
	USHORT	nFontSize;				///< ��Ʈ������
	USHORT	nBoldType;				///< ��Ʈ��Ÿ��(0:����,1:����,2:�����,3:���Ա����)
	
	COLORREF crFontColor;			///< ��Ʈ�÷�
	BOOL	bFontFixStyle;			///< ����/���� ����
	BOOL	bMaxMinRatio;			///< �ְ�/��������� ǥ��
	BOOL	bShowComparison;		//��� ǥ�� - ���� �ŷ�����ǥ�� ����
	BOOL	b3DEffect;				///< 3Dȿ��
	BOOL	bAnsContinue;			///< ��Ʈ�м��� ���ӱ׸���
	BOOL	bShowToolTip;			///< ���� ���������� ����
	BOOL	bRegionSelected;		///< ��Ʈ���� ����ǥ��

	int		nTitleDisplayDirect;	///< ����/���� Ÿ��Ʋ ǥ��
	int		nTitleDisplayType;		///< Title ��ġ��ȭ(0:���콺�̵��� �ڵ�,1:���콺 Ŭ���� ��ġ��ȸ,2:������ ������)
	int		nBongInterval;			///< ������
	int		nChtMarginSize;			///< ��Ʈ���鿵��

	BOOL	bChtZoneMoving;			///< ��Ʈ ������� �̵� ��ũ��
	BOOL	bReturnRegionExpand;	///< ����Ȯ��� �ǵ������

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
	BOOL	bHeadBarShow;			///< HeadBar���̱�
	BOOL	bFootBarShow;			///< FootBar���̱�
	BOOL	bSideBarShow;			///< Sidebar���̱�
	BOOL	bSideToolBarShow;		///< SideToolBar���̱�
	BOOL	bDataGridBarShow;		///< DataGridBar���̱�

	ST_QUERY_TYPE_INFO_TEMP stQueryTypeInfo[10];	///< ��ȸ������ ����(Day�� ��ü�����Ϳ䱸 �Ǵ� ��������, View Count������..)
	//--  2004/09/15

	int		nScreenBKType;			///< ȭ���漳��(0:Color BK Screen,1:WallPaper - Image BK Screen)
	COLORREF crBKColor;				///< ȭ�����
	TCHAR	szWallPaperPath[300];	///< WallPaper ���� ���

	BOOL	bScreenHorizon;			///< ���򴫱��� ��뿩��
	int		nScreenHLineType;		///< ���򴫱��� Ÿ��(solid, dot...)
	int		nScreenHLineWeight;		///< ���򴫱��� ����
	COLORREF crScreenHLineColor;	///< ���򴫱��� ��
	BOOL	bScreenHBackward;		///< ���򴫱��� ȭ�� �ڿ� ǥ�������� ����

	COLORREF crScreenHLineFillColor;	///< ���򴫱��� Fill ��

	BOOL	bScreenVertical;		///< ���������� ��뿩��
	int		nScreenVLineType;		///< ���������� Ÿ��(solid, dot...)
	int		nScreenVLineWeight;		///< ���������� ����
	COLORREF crScreenVLineColor;	///< ���������� ��
	BOOL	bScreenVBackward;		///< ���������� ȭ�� �ڿ� ǥ�������� ����	
	BOOL	bDataGapCorrect;		///< DataGap����	
	BOOL	bDataOff;				///< �����ְ�����
	BOOL	bDataLimit;				///< ��/���Ѱ�ǥ��
	BOOL	bDataOption;			///< �ɼ���簡ǥ��	

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
	TCHAR	szFontName[30];			///< ��Ʈ�̸�
	int		nFontStyle;				///< ��Ʈ��Ÿ��(0:����,1:����,2:�����,3:���Ա����)
	int		nFontSize;				///< ��Ʈ������
	COLORREF crFontColor;			///< ��Ʈ�÷�
	BOOL	bFontFixStyle;			///< ����/���� ����
	BOOL	bMaxMinRatio;			///< �ְ�/��������� ǥ��
	BOOL	bShowComparison;		//��� ǥ�� - ���� �ŷ�����ǥ�� ����
	BOOL	b3DEffect;				///< 3Dȿ��
	BOOL	bAnsContinue;			///< ��Ʈ�м��� ���ӱ׸���
	BOOL	bShowToolTip;			///< ���� ���������� ����
	BOOL	bRegionSelected;		///< ��Ʈ���� ����ǥ��

	int		nTitleDisplayDirect;	///< ����/���� Ÿ��Ʋ ǥ��
	int		nTitleDisplayType;		///< Title ��ġ��ȭ(0:���콺�̵��� �ڵ�,1:���콺 Ŭ���� ��ġ��ȸ,2:������ ������)
	int		nBongInterval;			///< ������
	int		nChtMarginSize;			///< ��Ʈ���鿵��

	BOOL	bChtZoneMoving;			///< ��Ʈ ������� �̵� ��ũ��
	BOOL	bReturnRegionExpand;	///< ����Ȯ��� �ǵ������

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
	int		 nPrcType;				///< Price(Main)��Ʈ Ÿ�� (G_PRCCHT_CANDLE,...)

	COLORREF crPrcUpLine;			///< ��� ���λ�
	BOOL	 bPrcUpFill;			///< ��� ����ü���� ä������ ����
	COLORREF crPrcUpBody;			///< ��� ����ü��
	COLORREF crPrcDownLine;			///< �϶� ���λ�
	BOOL	 bPrcDownFill;			///< �϶� ����ü���� ä������ ����
	COLORREF crPrcDownBody;			///< �϶� ����ü��

	COLORREF crPrcOffLine;			///< �Ź��� ���λ�
	BOOL	 bPrcOffFill;			///< �Ź��� ����ü���� ä������ ����
	COLORREF crPrcOffBody;			///< �Ź��� ����ü��

	int		nDataType;				///< ���� ������(��,��,��,��, �ð�����,...)
	COLORREF crLineColor;			///< ���λ�
	int		nLineStyle;				///< ���ν�Ÿ��
	int		nLineWeight;			///< ���α���

	int		nDefineBase;			///< �������(��������>���Ͻð�, ��������>��������, ��������>���ذ�)
									///< ���߸޹���Ʈ���� �Ź��ð����� ���
	double	dBaseValue;				///< ������ذ�(��������>���ذ��� ���ذ�)

	BOOL	bLastPrevLine;			///< ���������� ǥ�� ����
	COLORREF crLastPrevLine;		///< ������������
	int		nPrevLineStyle;			///< ���������� ��Ÿ��
	int		nPrevLineWeight;		///< ���������� ����

	BOOL	bMaxMinDisplay;			///< �ִ�/�ּҰ� ǥ��
	BOOL	bLogScale;				///< �α���Ʈ
	BOOL	bInvertScale;			///< ������Ʈ
	BOOL	bTitleShow;				///< Ÿ��Ʋ����
	BOOL	bGradationShow;			///< Gradationȿ��

	BOOL	bAutoOffering;			///< �ڵ� �Ź��� ����
	int		nOfferingCount;			///< �Ź����� ����
	double  dIndexValue1;			///< Price(Main)��Ʈ�� �ʿ䰪(��:������Ʈ�� �������, SyncOverlap��Ʈ�� �����)
	double  dIndexValue2;			///< Price(Main)��Ʈ�� �ʿ䰪2(��:SyncOverlap��Ʈ�� �׸�����)

	//2005/03/07 - ���� ��Ʈ������ ���� �߰��� �κ�
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

	// ���
	COLORREF crPrcUpLine;
	BOOL	 bPrcUpFill;
	COLORREF crPrcUpBody;	
	// �϶�
	COLORREF crPrcDownLine;
	BOOL	 bPrcDownFill;
	COLORREF crPrcDownBody;
	// ����
	COLORREF crPrcFlat;
	BOOL	 bPrcFlat;
	// �ŷ���
	COLORREF crPrcOffLine;
	BOOL	 bPrcOffFill;
	COLORREF crPrcOffBody;
	// ����
	COLORREF crLineColor;	// ����
	int		nLineStyle;		// ���
	int		nLineWeight;	// ����

	BOOL	bMaxMinDisplay;	// MinMax
	BOOL	bTitleShow;		// Title

	// ȭ�鼳��
	COLORREF crBKColor;
	COLORREF crFontColor;
	BOOL	bScreenHorizon;			// ����GridLine
	BOOL	bScreenVertical;		// ����GridLine
	BOOL	bToolTipShow;			// ToolTip

	// X�༳��
	BOOL	bShowFirstData;			//X�� ó�� ������ ����
	BOOL	bShowLastData;			//X�� ������ ������ ����
	int		nXAxisSpace;			//X�� ��������

	// Y�༳��
	TCHAR   szIndexNameList[G_MAX_IDX_PER_CHART][30];	// ���� Zone�� IndexList - ������� 	
	int		nDecimalDepress[G_MAX_IDX_PER_CHART];		// 10������ ���
	int		nFloatingPoint[G_MAX_IDX_PER_CHART];		// �Ҽ��� ���� ǥ��	
	int		nYScaleShowType[G_MAX_IDX_PER_CHART];		// Y�� Label
	BOOL	bThousandComma[G_MAX_IDX_PER_CHART];		// õ������ǥ

	float	fYScaleRatioUpper;		// ���ʳ��� ����
	float	fYScaleRatioLower;		// �Ʒ��ʳ��� ����
	int		nYAxisShowType;			// Y����̺���(0:Both,1:Left,2:Right,3:None)

	//	Gen������ ���	
	BOOL	bRequestAllData[8];		//��üData�䱸
	int		nRequestCount[8];		//��ȸDataCount
	int		nChtViewCount[8];		//ChartViewCount
	BOOL	bModifiedData;			//�����ְ�
	BOOL	bYZoneOverlap;			//Y��Overlap

	BOOL	bYDaebiRatio;			//Y������ show/hide

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
	int		 nChtDrawType;			//Price�� ��� - PrcType,�ŷ����ϰ�� - Bar,Line...�׿� ��ǥ-DB Reading�� Setting	
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
	tag3DPRICLINEINFO st3DPrcInfoList[10];		//Max10��

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
		//st3DPrcInfoList[10];		//Max10��
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
const int	G_ANSSELECTFUZZ = 4;		//�߼�������ũ��
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
	// �׷��� ���� �Ӽ�-->
	BOOL	bTitleShow;			///< Title ����	
	BOOL	bMaxMinDisplay;		///< �ִ�/�ּҰ� ����
	BOOL	bDrawGradient;		///< Gradation
	BOOL	bShowCircle;		///< Line,Period���� Circleǥ��

	COLORREF crBKColor;			///< �׷��� ����
	COLORREF crFontColor;		///< �׷��� �۲û�
	COLORREF crGridColor;		///< �׷��� ���ݻ�

	BOOL	bScreenHorizon;		///< ���򴫱� ���̱�
	BOOL	bScreenVertical;	///< �������� ���̱�

	int		nDecimalDepress;	///< �������
	int		nFloatingPoint;		///< �Ҽ���

	float	fYScaleRatio;		///< Y���̺���
	int		nYAxisShowType;		///< ��ü Y�� ���� Ÿ��(����,����,������,����)
	// �׷��� ���� �Ӽ�<--

	// Index �Ӽ�-->
	BOOL	 bPrcUpFill;		///< ��� ����� ��뿩��
	COLORREF crPrcUpLine;		///< ��� ���λ�
	COLORREF crPrcUpBody;		///< ��� �����

	BOOL	 bPrcDownFill;		///< �϶� ����� ��뿩��
	COLORREF crPrcDownLine;		///< �϶� ���λ�
	COLORREF crPrcDownBody;		///< �϶� �����

	COLORREF crLineColor;		///< �Ϲ� ���λ�
	int		nLineStyle;			///< �Ϲ� ���� ��Ÿ��
	int		nLineWeight;		///< �Ϲ� ���� ����
	// Index �Ӽ�<--

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
	// �׷��� ���� �Ӽ�-->
	BOOL	bTitleShow;								///< Title ����	
	BOOL	bMaxMinDisplay;							///< �ִ�/�ּҰ� ����
	BOOL	bDrawGradient;							///< Gradation

	COLORREF crBKColor;								///< �׷��� ����
	COLORREF crFontColor;							///< �׷��� �۲û�
	COLORREF crGridColor;							///< �׷��� ���ݻ�

	BOOL	bScreenHorizon;							///< ���򴫱� ���̱�
	BOOL	bScreenVertical;						///< �������� ���̱�

	int		nDecimalDepress;						///< �������
	int		nFloatingPoint;							///< �Ҽ���

	float	fYScaleRatio;							///< Y���̺���
	int		nYAxisShowType;							///< ��ü Y�� ���� Ÿ��(����,����,������,����)
	// �׷��� ���� �Ӽ�<--

	// �׷� �Ӽ�-->
	int		 nGroupDataCount;						///< �׷� ����
	TCHAR    szGroupNameList[G_MAXGROUPDATA][30];	///< �׷��
	COLORREF crGroupLineList[G_MAXGROUPDATA];		///< �׷� ���λ�
	COLORREF crGroupBodyList[G_MAXGROUPDATA];		///< �׷� �����
	BOOL	 bGroupFillList[G_MAXGROUPDATA];		///< �׷� ����� ä�� ����
	// �׷� �Ӽ�<--

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
	// �׷��� ���� �Ӽ�-->
	BOOL	bTitleShow;				///< ����ȸ�ͼ� Title ����
	BOOL	bMaxMinDisplay;			///< �ִ�/�ּҰ� ����
	BOOL	bNameShow;				///< Scatter �̸� ����

	COLORREF crBKColor;				///< �׷��� ����
	COLORREF crFontColor;			///< �׷��� �۲û�
	COLORREF crGridColor;			///< �׷��� ���ݻ�

	BOOL	bScreenHorizon;			///< ���򴫱� ���̱�
	BOOL	bScreenVertical;		///< �������� ���̱�

	int		nDecimalDepress;		///< �������
	int		nFloatingPoint;			///< �Ҽ���

	float	fYScaleRatio;			///< Y���̺���
	int		nYAxisShowType;			///< ��ü Y�� ���� Ÿ��(����,����,������,����)

	BOOL	bShowLinearLine;		///< ����ȸ�ͼ� ���̱�
	
	//		Base����,����
	BOOL	bShowHorizonLine;		///< ���� ���̱�
	double  dBaseHorizon;			///< ���� ��
	COLORREF crBaseHorizon;			///< ���� ����
	int		nHorizonStyle;			///< ���� ��Ÿ��
	int		nHorizonWeight;			///< ���� ����

	BOOL	bShowVerticalLine;		///< ������ ���̱�
	double  dBaseVertical;			///< ������ ��
	COLORREF crBaseVertical;		///< ������ ����
	int		nVerticalStyle;			///< ������ ��Ÿ��
	int		nVerticalWeight;		///< ������ ����
	// �׷��� ���� �Ӽ�<--

	// Index �Ӽ�-->
	COLORREF crScatterColor;		///< Scatter ����
	int		nScatterType;			///< Scatter ǥ�����

	COLORREF crLinearReg;			///< ����ȸ�ͼ� ����
	int		nLinearRegStyle;		///< ����ȸ�ͼ� ��Ÿ��(PS_SOLID,...)
	int		nLinearRegWeight;		///< ����ȸ�ͼ� ����
	// Index �Ӽ�<--

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
	// �׷��� ���� �Ӽ�-->
	BOOL	bTitleShow;								///< Title ����	
	BOOL	bTextLabelShow;							///< Text Label ���̱�

	COLORREF crBKColor;								///< �׷��� ����
	COLORREF crFontColor;							///< �׷��� �۲û�
	COLORREF crGridColor;							///< �׷��� ���ݻ�

	int		nDecimalDepress;						///< �������
	int		nFloatingPoint;							///< �Ҽ���

	BOOL	bRadarGradient;							///< ���̴� Gradation
	COLORREF crRadarBack;							///< ���̴� ����
	BOOL	bRadarYScaleLineShow;					///< ���̴� Y�� ���� ���̱�

	// �׷��� ���� �Ӽ�<--

	// �׷� �Ӽ�-->
	int		nGroupDataCount;						///< �׷� ����
	TCHAR    szGroupNameList[G_MAXGROUPDATA][30];	///< �׷��
	COLORREF crGroupLineList[G_MAXGROUPDATA];		///< �׷� ���λ�
	int		 nGroupLineStyle[G_MAXGROUPDATA];		///< �׷� ���� ��Ÿ��
	int		 nGroupLineWeight[G_MAXGROUPDATA];		///< �׷� ���� ����
	// �׷� �Ӽ�<--

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
	// �׷��� ���� �Ӽ�-->
	BOOL	bTitleShow;								///< Title ����	
	BOOL	bTextLabelShow;							///< Text Label ���̱�

	COLORREF crBKColor;								///< �׷��� ����
	COLORREF crFontColor;							///< �׷��� �۲û�

	int		nDecimalDepress;						///< �������
	int		nFloatingPoint;							///< �Ҽ���

	BOOL	bShowDonutPie;							///< ������ ��� ���� ����
	double  dDonutRatio;							///< ������ ����

	BOOL	bSlicePie;								///< Slice Pie(���� ���� �ȵ�)
	// �׷��� ���� �Ӽ�<--

	// �׷� �Ӽ�-->
	int		nGroupDataCount;						///< �׷� ����
	TCHAR    szGroupNameList[G_MAXGROUPDATA][30];	///< �׷��
	COLORREF crGroupLineList[G_MAXGROUPDATA];		///< �׷� ���λ�
	// �׷� �Ӽ�<--

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
	// �׷��� ���� �Ӽ�-->
	BOOL	bTitleShow;				///< Title ����	
	BOOL	bShowLinearLine;		///< ���� ȸ�ͼ� ���� (���� ������ 2006.11.20 Hong~)

	COLORREF crBKColor;				///< �׷��� ����
	COLORREF crFontColor;			///< �׷��� �۲û�
	COLORREF crGridColor;			///< �׷��� ���ݻ�

	BOOL	bScreenHorizon;			///< ���򴫱� ���̱�
	BOOL	bScreenVertical;		///< �������� ���̱�

	int		nDecimalDepress;		///< �������
	int		nFloatingPoint;			///< �Ҽ���

	float	fYScaleRatio;			///< Y���̺���
	int		nYAxisShowType;			///< ��ü Y�� ���� Ÿ��(����,����,������,����)
	// �׷��� ���� �Ӽ�<--

	//		Base����,����
	BOOL	bShowHorizonLine;		///< ���� ���̱�
	double  dBaseHorizon;			///< ���� ��
	COLORREF crBaseHorizon;			///< ���� ����
	int		nHorizonStyle;			///< ���� ��Ÿ��
	int		nHorizonWeight;			///< ���� ����

	BOOL	bShowVerticalLine;		///< ������ ���̱�
	double  dBaseVertical;			///< ������ ��
	COLORREF crBaseVertical;		///< ������ ����
	int		nVerticalStyle;			///< ������ ��Ÿ��
	int		nVerticalWeight;		///< ������ ����

	// �׷� �Ӽ�-->
	int		 nGroupDataCount;							///< �׷� ����
	TCHAR    szGroupNameList[G_MATH_MAXGROUPDATA][30];	///< �׷��
	COLORREF crGroupLineList[G_MATH_MAXGROUPDATA];		///< �׷� ���λ�
	int		 nGroupLineStyle[G_MATH_MAXGROUPDATA];		///< �׷� ���� ��Ÿ��
	int		 nGroupLineWeight[G_MATH_MAXGROUPDATA];		///< �׷� ���� ����
	// �׷� �Ӽ�<--

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
	int		nLeftExt;			// ����Ȯ��
	int		nRightExt;			// ������Ȯ��
	int		nFullExt;			// ��üȮ��
	int		nFillRegion;		// ����ä��
	int		nLeftRatio;			// ��������
	int		nRightValue;		// ��������
	int		nFullMoving;		// ��ü�̵�
	int		nAnsDirect;			// DiagonalLine�� ��� ����(45��,-45��)...
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
	int		nIndexNo;						//�ѿ����� ���� Text��������� ����
	CString strText;					//char�� ǥ���ϱ�� �����
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
/*2004/01/10 - ��ü���� ��� ���� Struct						   */
typedef struct tagST_ANSDATA_INFO
{
	int				nANSDrawingType;			//Class Define Const
	int				nANSChtPos;					//��ġ - Save Load �ÿ��� ��Ʈ ��ġ���� ��Ȯ�ϰ� �¾ƾ��Ѵ�		
	double			dCalcRatio[12];				//Fibonacci,Gann,Speed�� Calc Ratio
	double			dSwingRatio;				//Swing Point Ratio	
	int				nANSDirect;					//Diagonal,Golden,ElliotArc	...
	int				nSnapInfo;					//Select Pos,Close Pos,High Pos,Low Pos	
	int				nSnapPos;
	//////////////////////////////////////////
	int				nPointsCount;
	LPST_ANSPOINT_PROPERTY pStAnsPointsInfo;
	int					 nLinesCount;
	LPST_ANSLINE_PROPERTY  pStAnsLinesInfo;
	//int					 nTurnPosCount;		//TurningInfo�� ������ �����ϱ� ��ƴ�	
	//LPST_ANSTURN_POSINFO pStAnsTurnPosInfo;	//���� ���� �� ���� ���� ���� ����
	ST_ANSTOOL_PROPERTY	 cStAnsToolPropertyInfo;	
	//ST_ANSTEXT_INFO		 cStAnsTextInfo;	//Text�� �ʿ䰡 ����
	ST_ANSTEXT_FONTINFO  cStAnsTextFontInfo;	//FontInfo�� FontDialog���� �ذ�	
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
/// ��ǥ ����
typedef struct tagST_FILEDB_IBODY_VARIABLE
{
	TCHAR chVariable[255];			///< ������
	/*2004/03/30 - float���� VarPrice�� ǥ���Ҽ� ����*/
	TCHAR chValue[20];				///< ������
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

/// ��ǥ ���ؼ�����
typedef struct tagST_FILEDB_IBODY_BASE
{
	int		 nBaseType;					///< ���ؼ� Ÿ��(0:Line,1:Upper,2:Lower	)
	double	 dBaseValue;				///< ���ؼ� ���ذ�
	int		 nBaseValueType;			///< ���ؼ� ��Ÿ��(0:Value,1:Percent)
	COLORREF crBaseColor;				///< ���ؼ� ����
	int		 nBaseStyle;				///< ���ؼ� ��Ÿ��
	int		 nBaseWeight;				///< ���ؼ� ����

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

/// ��ǥ ����
typedef struct tagST_FILEDB_IBODY_LINE
{
	int nLineShow;					///< Line�� ���������� ����
	int nFormulaSize;				///< Line Formula size
	TCHAR chLineName[30];			///< Line �̸�
	COLORREF crLineColor;			///< Line ����
	int nLineStyle;					///< Line ��Ÿ��
	int nLineWeight;				///< Line ����
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

/// ��ǥ Signal Line
typedef struct tagST_FILEDB_IBODY_SIGNAL
{
	UINT uSignalLine;			///< Signal Line �������
	int nSignalPeriod;			///< �Ⱓ
	int nSignalType;			///< ���(Simple, Exponential, Smooth,...)
	COLORREF crLineColor;		///< ����
	int nSignalStyle;			///< ����(Solid, Dash, dot,..)
	int nSignalWeight;			///< ����
	int nSignalDrawType;		///< 0:Line,1:OSC,2:Line+OSC
	
	int nChartLineBasic;		//�������������ߡ��Ƚ���
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
	BOOL bTitleShow;		//2004/03/23  - �߰�
	BOOL bMinMaxShow;		//2004/03/23  - �߰�

	int	 nFloatingPoint;	//2005/04/20  - �߰�
	tagST_FILEDB_IBODY_SIGNAL stSignalLine;		//2004/03/23  - �߰� //[kangyb 2010-08-04]
	int nLineCnt;
	tagST_FILEDB_IBODY_LINE_SAVE pStLineLists[5];
	int nVariableCnt;
	tagST_FILEDB_IBODY_VARIABLE_SAVE pStBodyVariables[G_MAXIBVARIABLE];

	//++2004/08/03 - �߰�
	int	nDisplayType;				//0:�⺻,1:Range(0~100),2:��ǥ�̺�(0~100)
	int nDisplayValues[2];			//++2004/08/05

	BOOL bIndPractical[3];			//0:���ؼ� �Ÿ�,1:��ȣ���Ÿ�,2:���ż�/���ŵ��� ���� �Ÿ�
	int nIndPractical;				//���� Selected�� Ȱ����	:  -1 �̸� X
	//--2004/08/03 - �߰�

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
	int nTradingType;					//0:�ż�����,1:�ż�û��,2:�ŵ�����,3:�ŵ�û��
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
	int nFormulaSize;					///< Formula ���ڿ� ����
	int nTradingType;					///< 0:�ż�����,1:�ż�û��,2:�ŵ�����,3:�ŵ�û��
	int nSignalIndex;					///< Signal ����(Signal,��,��...) 
	int nSignalSize;					///< Signal ũ��
	COLORREF crSignalColor;				///< Signal ����
	TCHAR *pChFormula;					///< Formula ���ڿ�

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
	G_OPT_TRADEFEE_FIXVALUE				= 0,		//���׹�
	G_OPT_TRADEFEE_FIXRATIO				= 1,		//������
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
	G_OPT_TRADE_POSTYPE_NEXTOPEN		= 0,	// �����ð�
	G_OPT_TRADE_POSTYPE_NEXTCLOSE		= 1,	// ��������
	G_OPT_TRADE_POSTYPE_THISCLOSE		= 2,	// �̹�����
};

enum EnOptInvestRuleType
{
	G_OPT_INVESTTYPE_FULLVALUE			= 0,	//����-õ����+�߰�����/�սǱ�
	G_OPT_INVESTTYPE_FIXVALUE			= 1,	//����-õ����
	G_OPT_INVESTTYPE_STOCKCOUNT			= 2,	//�ֽļ�
};

// ����
enum EnOptTradeStopRuleType
{
	G_OPT_TRADESTOP_NONE				= 0,	// �����ſ�Ģ �������
	G_OPT_TRADESTOP_FIXVALUE			= 1,	// ���׹� ���� : ���԰��� ���� ���/�϶�
	G_OPT_TRADESTOP_VARVALUE			= 2,	// ������ ����
};

// 
enum EnOptTradeStopExitType
{
	G_STOP_TRADE_DIFFPRICE				= 0,	// �����ſ�Ģ ���׹�(�ŸŰ��� _%�����/�϶���)
	G_STOP_TRADE_LOSSCUT				= 1,	// �����ſ�Ģ ������(�ŸŰ��� _%�϶���(StopLoss))
	G_STOP_TRADE_TARGETPROFIT			= 2,	// �����ſ�Ģ ������(�ŸŰ��� _%��½�(TargetProfit))
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
	G_OPT_HISTORY_BSTYPE				= 0,	//�Ÿ�����(�ż�:0, �ŵ�:1)
	G_OPT_HISTORY_ENTDATE				= 1,	//��������
	G_OPT_HISTORY_ENTVALUE				= 2,	//���Աݾ�
	G_OPT_HISTORY_ENTRESULT				= 3,	//������ ���� ���Աݾ�
	G_OPT_HISTORY_EXITDATE				= 4,	//û������
	G_OPT_HISTORY_EXITVALUE				= 5,	//û��ݾ�
	G_OPT_HISTORY_EXITRESULT			= 6,	//������ ���� û��ݾ�
	G_OPT_HISTORY_ENTINDEX				= 7,	//���Խ���Index
	G_OPT_HISTORY_EXITINDEX				= 8,	//û�����Index
	G_OPT_HISTORY_CONTRACT				= 9,	//����
	G_OPT_HISTORY_BALANCE_PRICE			= 10,	//�ܾ�
	G_OPT_HISTORY_PROFIT_AMOUNT			= 11,	//����(�ս�)�ݾ�
	G_OPT_HISTORY_PROFIT_RATIO			= 12,	//����(�ս�)��	
	G_OPT_HISTORY_ACCUM_PROFIT_RATIO	= 13,	//��������(�ս�)��
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

// ��Ʈ �ε��� ã�� ����
enum enChtIndexFindFlag
{	
	G_CIFF_KINDTYPE	= 0x01,			///< Chart Ÿ�� �˻�
	G_CIFF_POS		= 0x02,			///< Postion �˻�
	G_CIFF_NAME		= 0x04,			///< �̸� �˻�
};

/// ���/�϶�/���� ����


enum en_CPBongType
{
	G_CPBT_1BONG = 0,				// 1��
	G_CPBT_2BONG,					// 2��
	G_CPBT_3BONG,					// 3��
	G_CPBT_4BONG,					// 4��
	G_CPBT_5BONG,					// 5��
	G_CPBT_6BONG,					// 6��
	G_CPBT_COUNT					// ���� ī��Ʈ
};

typedef struct tagST_OPT_ENV_CONFIG
{
	//RuleTab
	BOOL bRuleSignalSound;
	UINT uRuleDisplayType;		//0:ApplyScreen,1:PopupDlg
	UINT uRuleEntryPos;			//���Խ���
	UINT uRuleExitPos;			//û�����
	UINT uRuleInvestType;		//0:���ڱݾ�(����),���ڱݾ�(����),�ֽļ�(�����ɼǰ����)
	long lRuleInvestValue[3];	//�ݾ�
	UINT uRuleTradeFee;			//0:���׹�,1:������
	float fRuleFixEntryFee;		//���׹����Լ�����
	float fRuleFixExitFee;		//���׹�û�������
	float fRuleVarEntryFee;		//���������Լ�����
	float fRuleVarExitFee;		//������û�������
	float fRuleSlippage;		//Slippage
	//LossCutTab
	UINT uStopLossCutType;		//����û���Ģ
	float fStopFixLossCut;		//���׹� - �����,���϶�
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
	int nTotDataCount;		//��ü DataCount
	int btDatePeriod;		//�к�,�Ϻ�??	
	int btDateCycle;		//10��,20��30��,1��,2��,3��,5��,10��,15��,20��,30��,60��,180��
	int	nDateCycle;			//�����(..��)
	int btDateCount;		//1��,2��??
	double dBaseDate;		//�к����� �����Ϸκ��� N��
	double dStartDate;		//�����Ͻ�
	double dEndDate;		//�����Ͻ�		

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

//�������� Summary ������ �ϳ��� ����
typedef struct tagST_RESULT_BODY_SUMMARY
{
	TCHAR   chVarName[30];	
	UINT	nTradeNum;			//������ TradeHistory�� SummaryHistory���� ���� ����
	UINT	nTotalTrdCnt;		//�Ѱŷ�Ƚ��	
	int		nCurTradeType;		//�������
	int		nProfitTrdCnt;		//���Ͱŷ�Ƚ��
	float   fAccumProfitPrice;	//�������ͱ�
	float   fAvgProfitRatio;	//��ռ��ͷ�
	UINT	nTotTrdHoldCount;		//�Ѱŷ����������ͼ�
	UINT	nAvgProfitHoldCount;//���Ͱŷ���պ��������ͼ�
	UINT	nAvgLossHoldCount;	//�սǰŷ���պ��������ͼ�	
	int		nLossTrdCnt;		//�սǰŷ�Ƚ��	
	float   fAccumLossPrice;	//�����սǱ�
	float   fAvgLossRatio;		//��ռսǷ�	
	float   fPurePLPrice;		//�����ͱ�
	float   fPurePLRatio;		//�����ͷ�

	float   fTradeWinRatio;		//�·� - ���Ͱŷ�/�սǰŷ�

	UINT	nMaxProfitDataCount;//�ִ������ϼ�		
	float	fMaxProfitRatio;	//�ִ���;�	
	float	fMaxProfitPrice;	//�ִ���ͷ�
	double	dMaxProfitEntryDate;//�ִ���ͳ�¥/�ð�-û�����
	double	dMaxLossExitDate;	//�ִ�սǳ�¥/�ð�-û�����
	UINT	nMaxLossDataCount;  //�ִ�ս��ϼ�		
	float	fMaxLossPrice;		//�ִ�սǾ�
	float	fMaxLossRatio;		//�ִ�սǷ�	
	double	dMaxLossEntryDate;	//�ִ�սǳ�¥/�ð�-û�����
	double	dMaxProfitExitDate;	//�ִ���ͳ�¥/�ð�-û�����		

	double  dFirstEntryClose;	//�������԰��� - ����
	double  dLastExitClose;		//������û�갡�� - ����

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
	UINT	nTradeType;			//�ż�/�ż�û��,�ŵ�/�ŵ�û��
	double  dEntryDate;			//���Գ�¥
	double  dEntryPrice;		//���԰���
	double  dExitDate;			//û�곯¥
	double  dExitPrice;			//û�갡��
	double	dBalancePrice;		//�ܱ�
	int		nContracts;			//�ŷ�����	
	float	fTradePLPrice;		//���Ͱ���
	float	fTradePLRatio;		//���ͷ�
	float   fAccumPLRatio;		//�������ͷ�	

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

//�������� �ż�/�ŵ��� ��� ���� �� ������ �־����
typedef struct tagST_RESULT_BODY_HISTORY
{
	TCHAR   chVarName[30];	
	UINT	nTotalTrdCnt;		//�Ѱŷ�Ƚ�� - File���� VarPos�� ã�ư��� Key�� �ȴ�	
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
	int nSignalPos;			//2004/09/01 - ���� �߰�
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
	int nCandlePos;			//2004/09/01 - ���� �߰�
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
	int		nYAxisZoneIdx;			//���� Zone Index Number
	TCHAR	szZoneName[50];	
	/*2004/04/08*/
	//����:�켱�� �ѿ����� ��ǥ�� 15���̻� �ö󰥼� ���ٰ� �����Ѵ�
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
	double		dMaxScale;				///< ���������(G_YSCALE_DSPUSER) Scale�� Y�� �ִ밪
	double		dMinScale;				///< ���������(G_YSCALE_DSPUSER) Scale�� Y�� �ּҰ�

	int			nYScaleLabel;			//0:����,1:����,2:������,3:����
	BOOL		bThousandComma;	
	BOOL		bShortFitch;			//���� ���� ���̱�

	int			nDecimalDepress;		//10������ ���
	int			nFloatingPoint;			//�Ҽ��� ���� ǥ��

	//Y�� ��ü ����
	BOOL		bScreenYOverlab;
	float		fRegionFromRatio;
	float		fRegionToRatio;

	int			nYAxisShowType;			///< 0:����,1:����,2:������,3:����,4:Auto
	//float		fYScaleRatio;			///< Y�� ����
	float		fYScaleRatioUpper;		///< ���� Y�� ����
	float		fYScaleRatioLower;		///< �Ʒ��� Y�� ����
	COLORREF	crBackGround;			///< Y�� ����
	COLORREF	crForeGround;			///< Y�� ���ڻ�

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
	int		nOrderNum;		// ��Ʈ���� ����

	int		nRegion;		// ����
	int		nIdxNum;		// �����ȿ��� Index
	CString	strChtIdxName;	// Index ��

	int		nLineStyle;		// ������ ����(�ŷ������)����?
	int		nDataType;		// -1:�Ϲ�����,G_CHTDATA_DATE, G_CHTDATA_OPEN, G_CHTDATA_HIGH, G_CHTDATA_LOW, G_CHTDATA_CLOSE

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
		_T("���� ���Ŀ��� Parameter�� ����� �ʿ��մϴ�"), 
		_T("���� ���Ŀ��� Parameter�� ������ �ʿ��մϴ�"),
		_T("�߸��� ���� �Դϴ�"),
		_T("��� �Ҽ� ���� �����Դϴ�"),		
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
//���ͷ� Class
class CProfitRateData:public CObject
{
public:
	UINT	nFlag;						//0:�ż�,1:�ŵ�,2:������,3:���ͽ���
	double	dDate;						//Ex:2002/08/23-10:23:13 �����Ͻ�
	double	cDate;						//Ex:2002/08/23-10:23:13 û���Ͻ�
	long	lEntrancePrc;				//���Աݾ�
	long	lExitPrc;					//û��ݾ�
	long	lCount;						//����
		//float	fEarningRate;			//���ͷ�
	//float	fEarningAccmRate;		//�������ͷ�
	float	fEarningRate;				//���ͷ�
	float	fEarningAccmRate;			//�������ͷ�
	long	lEarningPrc;				//���ͱݾ�
	long	lEarningAccmPrc;			//�������ͱݾ�
	//		��ǥ,Bar	
	CPoint  ptAccmRate; 				//�������ͷ�-��ǥ
	CRect   rcRate;						//���ͷ� Bong Rect

	virtual ~CProfitRateData(){};
	CProfitRateData()
	{		
		nFlag=-1;						//0:�ż�,1:�ŵ�,2:������,3:���ͽ���
		dDate=-1.0f;					//Ex:2002/08/23-10:23:13 �����Ͻ�
		cDate=-1.0f;					//Ex:2002/08/23-10:23:13 û���Ͻ�
		lEntrancePrc=0;					//���Աݾ�
		lEntrancePrc=0;					//û��ݾ�
		lCount=0;						//����
		fEarningRate=0.0f;				//���ͷ�
		fEarningAccmRate=0.0f;			//�������ͷ�
		lEarningPrc=0;					//���ͱݾ�
		lEarningAccmPrc=0;				//�������ͱݾ�

		ptAccmRate=CPoint(0,0); 		//�������ͷ�-��ǥ
		rcRate.SetRect(0,0,0,0);		//���ͷ� Bong Rect
	}
};
typedef CTypedPtrArray<CObArray,CProfitRateData*> CProfitRateArray;

//////////////////////////////////////////////////////////////////////////////
//						Global Macro Defines 

#define IsHangul(c)	((c) & 0x8000)			//�ѱ����� �������� ����
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

// ��Ȩ���ݽṹ 
#define   MAX_CODE    30

typedef struct drdata_t
{
	//DWORD	m_dwMarket;			// ֤ȯ�г�����
	//char	m_szCode[MAX_CODE];	// ֤ȯ����,��'\0'��β

	double	m_date;				//����	Format is XXMMDDHHMM for 5min, Format is YYYYMMDD for day
	time_t	m_time;				//ʱ�䡡��m_dateһ�£��������ĳ�գ���Сʱ�����Ϊ0

	double	m_fGive;			// ÿ���ͣ����
	double  m_fPei;				// ÿ����
	double	m_fPeiPrice;		// ��ɼ�,���� m_fPei!=0.0f ʱ��Ч
	double	m_fProfit;			// ÿ�ɺ�������Ϣ(ҪôΪ��ͨ��Ϣ��ҪôΪ�ر���Ϣ,����ͬʱ����ʱΪͬһ��)
	//double	m_fSpeProfit;	// ÿ���ر���Ϣ ,2010-2-4 �����ٶ��壬��������
	double  m_fSplit;           // ��ֹɷ�
	double  m_fCombine;         // �ϲ��ɷ�

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
