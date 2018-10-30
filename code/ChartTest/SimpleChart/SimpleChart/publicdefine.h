#pragma once 

/////////////////////////////////////////////////////////////////////////////////////
//��������
/////////////////////////////////////////////////////////////////////////////////////
const double G_POSITIVEMAX					= 1E37f;				
const double G_NEGATIVEMAX					= -1E37f;
const double G_NOTAVAILABLE					= DBL_MIN;	
const float  G_NOTAVAILABLE_FLOAT			= FLT_MIN;		
const int    G_NOTAVAILABLE_INT				= INT_MIN;
const double G_PERMIT_MINVALUE				= 1.0E-07;
const double G_MIN_CANDLE_WIDTH				= 1.5f;
const double G_ADD_CANDLE_WIDTH_LEVELA		= 15.0f;
const double G_MAX_CANDLE_WIDTH				= 25.0f;
const double G_MAXYAXISSCALE				= 40.0f;

static const UINT	G_MAXGROUPDATA			= 12;		///< �ִ�׷��

const UINT	G_MARGIN_WIDTH			= 1;		//ҳ�߿� MarginWidth - 1
const UINT	G_MARGIN_HEIGHT			= 1;		//ҳ�߿� MarginHeight - 1

const int G_PAGE_MEMORY_SIZE = 1024;
const int G_PAGE_MARGIN_SIZE = 10;

const int MAXPAGESIZE    = 1024;
const int PAGEMARGINSIZE = 10; 

#define FLT_MIN         1.175494351e-38F        /* min positive value */
#define DBL_MIN         2.2250738585072014e-308 /* min positive value */


//�ڴ洦��
#define SAFEFREE(p) if(p) {delete p; p=NULL;}



///////////////////////////////////////////////////////////////////////////////////////
//����Ԥ����
//////////////////////////////////////////////////////////////////////////////////////
//�ǵ���״̬
enum EnRiseFallState
{	
	G_RISEFALL_STATE_DESCENT			= -1,	//��
	G_RISEFALL_STATE_STEADY				= 0,	//
	G_RISEFALL_STATE_ASCENT				= 1,	//��
};

//֤ȯ�г�
enum EnLanguage
{
		G_LANG_ZHCN = 0,
		G_LANG_ZHHK = 1,
		G_LANG_ZHTW = 2,
		G_LANG_ENUS = 3
};

//֤ȯ�г�
enum EnDataMarketType
{
		G_MARKET_TYPE_ALL					= 0,		// ȫ��
		G_MARKET_TYPE_STOCK				    = 1,		// ��Ʊ
		G_MARKET_TYPE_INDUSTRY				= 2,		// ָ��
		G_MARKET_TYPE_FUTURE				= 3,		// �ڻ�
		G_MARKET_TYPE_OPTION				= 4   		// ��Ȩ
};




//��������
enum EnChtDataType
{
		G_CHTDATA_DATE					= 0,		// ����
		G_CHTDATA_TIME					= 1,		// ʱ��
		G_CHTDATA_OPEN					= 2,		// ���̼�
		G_CHTDATA_HIGH					= 3,		// ��߼�
		G_CHTDATA_LOW					= 4,		// ��ͼ�
		G_CHTDATA_CLOSE					= 5,		// ���̼�
		G_CHTDATA_CHANGE				= 6,		// �ǵ�
		G_CHTDATA_CHANGERATE			= 7,		// �ǵ���
		G_CHTDATA_VOLUME				= 8,		// ������
		G_CHTDATA_AMOUNT				= 9,		// ���׶�
		G_CHTDATA_TURNOVER				= 10,		// ������
			

		G_CHTDATA_ITEMPOS				= 23,       // ��¼ÿ���������ݵ���Ļλ��
		G_CHTDATA_ITEMWIDTH				= 24	    // ��¼ÿ���������ݵĿ��
		
};

//��ʾͼ�����ͣ���ʱͼ��K��ͼ		
enum enViewType
{
	G_CHTTYPE_TREND = 0,
	G_CHTTYPE_KLINE = 1
};

enum enDrawType
{
	G_Draw45Line = 0,
	G_DrawLINE = 1
};

#define COLOR_GRAY RGB(192,192,192)
#define COLOR_WHITE RGB(255,255,255)
#define COLOR_RED   RGB(255,0,0)
#define COLOR_BG    RGB(0,0,0)
#define COLOR_YELLOW RGB(192,192,0)
#define COLOR_GREEN RGB(0,230,0)
#define FONT_HEIGHT 16

#define  WM_MSG_MOUSEAXIS (WM_USER+100)


#define     G_CLR_BLACK					RGB(  0,   0,   0)
#define     G_CLR_LIGHTBLACK			RGB(  45,   45,   45)
#define     G_CLR_WHITE					RGB(255, 255, 255)
#define     G_CLR_RED					RGB(255,   0,   0)
#define		G_CLR_DKRED					RGB(128, 0, 0)
#define		G_CLR_GREEN					RGB(0, 255, 0)
#define		G_CLR_GREEN2				RGB(  0, 106,   0)
#define		G_CLR_GREEN3				RGB(  5, 205,  30)
#define     G_CLR_LTGREEN				RGB(200,255,200)
#define		G_CLR_DKGREEN				RGB(0, 128, 0)
#define		G_CLR_PURPLE				RGB(56,0,56)
#define		G_CLR_SILVER				RGB(137,137,137)
#define     G_CLR_YELLOW				RGB(255, 255,   0)
#define		G_CLR_DKYELLOW				RGB(128, 128, 0)
#define     G_CLR_BLUE					RGB(  0,   0, 255)
#define		G_CLR_DKBLUE				RGB(0, 0, 128)
#define		G_CLR_CLOUDBLUE				RGB(128, 184, 223)
#define		G_CLR_MAGENTA				RGB(255, 0, 255)
#define		G_CLR_LTMAGENTA				RGB(255, 196, 255)
#define		G_CLR_DKMAGENTA				RGB(128, 0, 128)
#define		G_CLR_CYAN					RGB(0, 255, 255)
#define		G_CLR_DKCYAN				RGB(0, 128, 128)
#define     G_CLR_GRAY					RGB(220, 220, 220)
#define     G_CLR_BGRAY					RGB(152, 152, 152)
#define		G_CLR_DKGRAY				RGB(128, 128, 128)
#define		G_CLR_LTGRAY				RGB(230, 230, 255)
#define     G_CLR_KBJ					RGB(  0, 192, 192)
#define     G_CLR_MAROON				RGB(56,0,0)
#define     G_CLR_FUSCHIA				RGB(255,0,255)
#define     G_CLR_TEAL					RGB(0,56,56)
#define		G_CLR_OLIVE					RGB(56,56,0)
#define		G_CLR_NAVY					RGB(0,0,56)
#define		G_CLR_JUHANG				RGB(255, 128,   0)
#define		G_CLR_BORA					RGB(128,   0, 255)
#define		G_CLR_HWANG					RGB(128, 128,  64)
#define		G_CLR_PINGCU				RGB(255, 128, 192)
#define		G_CLR_CHANG					RGB( 64, 128, 128)
#define		G_CLR_GRAY_FORTY			RGB(102, 102, 102)

