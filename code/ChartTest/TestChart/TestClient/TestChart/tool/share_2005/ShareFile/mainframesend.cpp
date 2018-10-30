

#include "stdafx.h"
#include "mainframesend.h"

#include "outsharefile.h"

#define JH_Used_MIDPrice

#ifndef HS_SUPPORT_UNIX
IMPLEMENT_DYNCREATE(CMainFrameSend, CMainSendBase)
#endif


//
static char  g_szStockDefaultTime[][10] = {"09:30","11:30","13:00","15:00"};

static char  g_szQHDefaultTime[][10]    = {"09:00","11:30","13:30","15:00"};

static char  g_szGGDefaultTime[][10]    = {"10:00","12:30","14:30","16:00"};

static char  g_szWPDefaultTime[][10]    = {"07:00","24:00","00:00","07:00"};

static char  g_szWHDefaultTime[][10]    = {"06:00","24:00","00:00","06:00"};   // modified by Ben 20100909

static char  g_szHJDefaultTime[][10]    = {"09:00","11:30","13:30","15:30","21:00","24:00","00:00","2:30"};   // modified by Ben 20110317

// ͬ������Դ
static char  g_szWHDefaultTime_TongXin[][10]    = {"06:00","24:00","00:00","05:00"};

#define MakeSecMarket(x) ((HSMarketDataType)((x) & (0x0F00)))


char sz_MLPath_SH[128];
char sz_MLPath_SZ[128];

int  yyyCount = 0;
int  yyyDelay = 1000;
int  g_nSigleDelay = 5;
int  yyyQlInitTime = 560;

struct FileNowData_Static
{
	FileNowData* pFileNowData;
	LevelStatic* pLevelStatic;
	FileNowData_Static()
	{
		memset(this,0,sizeof(FileNowData_Static));
	}

	~FileNowData_Static()
	{
		if(pFileNowData)
		{
			delete pFileNowData;
			pFileNowData = NULL;
		}
		if( pLevelStatic )
		{
			delete pLevelStatic;
			pLevelStatic = NULL;
		}
	}
};

typedef CYlsArray<FileNowData_Static*,FileNowData_Static*> typeFileNowData;


MarketInfo_send	CMainFrameSend::m_QHMarketInfo(QH_GuoLeiTotal + QH_GuoWaiMax*2);

MarketInfo_send	CMainFrameSend::m_SHMarketInfo; // �Ϻ�
MarketInfo_send	CMainFrameSend::m_SZMarketInfo;	// ����

//�ƽ�
MarketInfo_send		CMainFrameSend::m_HJMarketInfo1;		// �Ϻ��ֻ�
MarketInfo_send		CMainFrameSend::m_HJMarketInfo2;	    // �Ϻ��ڻ�
MarketInfo_send		CMainFrameSend::m_HJMarketInfo3;		// ���ʻƽ�
MarketInfo_send		CMainFrameSend::m_HJMarketInfo4;		// �����г�

MarketInfo_send	CMainFrameSend::m_WPMarketInfo1(35);  // ����ָ��
MarketInfo_send	CMainFrameSend::m_WPMarketInfo2;  // LME


MarketInfo_send	CMainFrameSend::m_WPMarketInfo3;  // CBOT
MarketInfo_send	CMainFrameSend::m_WPMarketInfo4;  // NYMEX
MarketInfo_send	CMainFrameSend::m_WPMarketInfo5;  // COMEX
MarketInfo_send	CMainFrameSend::m_WPMarketInfo6;  // TOCOM
MarketInfo_send	CMainFrameSend::m_WPMarketInfo7;  // IPE	
MarketInfo_send	CMainFrameSend::m_WPMarketInfo8;  // NYBOT
MarketInfo_send	CMainFrameSend::m_WPMarketInfo10; // ��ָ 



MarketInfo_send	CMainFrameSend::m_WHMarketInfo1; // ���
MarketInfo_send	CMainFrameSend::m_WHMarketInfo2; // ���
//MarketInfo_send	CMainFrameSend::m_WHMarketInfo3; // ���

MarketInfo_send	CMainFrameSend::m_GGMarketInfo1; // �۹�
MarketInfo_send	CMainFrameSend::m_GGMarketInfo2; // �۹�
MarketInfo_send	CMainFrameSend::m_GGMarketInfo3; // �۹�

MarketInfo_send	CMainFrameSend::m_QHMarketInfo1; // 
MarketInfo_send	CMainFrameSend::m_QHMarketInfo2; // 
MarketInfo_send	CMainFrameSend::m_QHMarketInfo3; // 

MarketInfo_send	CMainFrameSend::m_QHMarketInfo_DL;
MarketInfo_send	CMainFrameSend::m_QHMarketInfo_SH;
MarketInfo_send	CMainFrameSend::m_QHMarketInfo_ZZ;
MarketInfo_send	CMainFrameSend::m_QHMarketInfo_GZ;		// ��ָ
MarketInfo_send	CMainFrameSend::m_QHMarketInfo_Self;	// �Զ���



//
MarketInfo_send	CMainFrameSend::m_TestMarketInfo;


// ���׸�����õ���������
static HSMarketDataType YF_GetClassify(int InstrumentType)
{
	static HSMarketDataType type[20] = 
	{
		0,
			HK_KIND_BOND	 ,   // ծȯ
			HK_KIND_MulFund	 ,   // һ�����Ϲ�֤
			HK_KIND_FUND	 ,   // ����
			KIND_WARRANTS	 ,   // �Ϲ�֤
			KIND_JR			 ,   // ����
			KIND_ZH			 ,   // �ۺ�
			KIND_DC			 ,   // �ز�
			KIND_LY			 ,   // ����
			KIND_GY			 ,   // ��ҵ
			KIND_GG			 ,   //  ����
			KIND_QT			 ,   //  ����
			0				 ,	 // ��ҵ��			
			HK_KIND_INDEX			 ,   // ��ָ
			HK_KIND_FUTURES_INDEX	 ,   // ��ָ
	};

	if( InstrumentType >= 1 && InstrumentType < 15 )
		return type[InstrumentType];

	return KIND_QT;
}


// ���������ļ��ֶ�
struct QH_Code_Cfg
{
	char	m_strCode[64];		 // ʵ�ʴ���,����ͽ��������Ӧ
	char	m_strDispCode[STOCK_CODE_SIZE];    // ��ʾ����,���ж���
	char	m_strName[16];		 // ��ʾ����
	float	m_lPreClose;		 // ������
	int		m_InstrumentType;    // �׸��۹ɹ�Ʊ����

	HSMarketDataType ClassifyStock(CMainFrameSend* pMain,
		HSMarketDataType cBourse,const char* strCode,int nCodeLen)
	{
		if( MakeMarket(cBourse) == HK_MARKET )
		{
			return ( cBourse | YF_GetClassify(m_InstrumentType) );
		}

		return pMain->ClassifyStock(cBourse,strCode,nCodeLen);
	}
};


CMainFrameSend::CMainFrameSend(CYlsBaseDoc* pYlsBaseDoc /*= NULL*/)
{
	m_pYlsBaseDoc = pYlsBaseDoc;
	m_nInitTime = 0;
	m_nCheckInitData = 0;

	memset(m_strIP,0,sizeof(m_strIP));
	m_nPort = 0;
	m_pConnectSession = NULL;

	m_pMainSend = NULL;

	m_nForceInit = 1;

	m_nCheckByTime = 0;

	m_lLastError = 0;
}

CMainFrameSend::~CMainFrameSend(void)
{
}

int CMainFrameSend::GetClass_QH_MARKET_Timer(HSMarketDataType cStockType,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay)
{
	switch( MakeSecMarket(cStockType) )
	{
	case ZHENGZHOU_BOURSE:
	case DALIAN_BOURSE: // ����
		{

			ay.Add(new CHqDataBuffer("09:00"));
			ay.Add(new CHqDataBuffer("10:15"));
			ay.Add(new CHqDataBuffer("10:30"));
			ay.Add(new CHqDataBuffer("11:30"));
			ay.Add(new CHqDataBuffer("13:30"));
			ay.Add(new CHqDataBuffer("15:00"));
			return ay.GetSize();

			/*
			switch(MakeSubMarket(cStockType))
			{
			case KIND_BEAN:
				break;
			case KIND_YUMI:
				break;
			case KIND_SHIT: // ����ʳ��
				ay.Add(new CHqDataBuffer("09:00"));
				ay.Add(new CHqDataBuffer("11:00"));
				return ay.GetSize();
			case KIND_DZGY:
				ay.Add(new CHqDataBuffer("09:30"));
				ay.Add(new CHqDataBuffer("11:00"));
				return ay.GetSize();
			case KIND_DZGY2:
				ay.Add(new CHqDataBuffer("14:00"));
				ay.Add(new CHqDataBuffer("15:00"));
				return ay.GetSize();
			}*/
		}
		break;
	case SHANGHAI_BOURSE: // �Ϻ�
		{
			ay.Add(new CHqDataBuffer("09:00"));
			ay.Add(new CHqDataBuffer("10:15"));
			ay.Add(new CHqDataBuffer("10:30"));
			ay.Add(new CHqDataBuffer("11:30"));
			ay.Add(new CHqDataBuffer("13:30"));
			ay.Add(new CHqDataBuffer("14:10"));
			ay.Add(new CHqDataBuffer("14:20"));
			ay.Add(new CHqDataBuffer("15:00"));
			return ay.GetSize();

			//switch(MakeSubMarket(cStockType))
			//{
			//case 0:		    // ��������
			//	ay.Add(new CHqDataBuffer("09:00"));
			//	ay.Add(new CHqDataBuffer("11:30"));
			//	ay.Add(new CHqDataBuffer("13:00"));
			//	ay.Add(new CHqDataBuffer("15:15"));
			//	return ay.GetSize();
			//case KIND_GUZHI: // ��ָ�ڻ�
			//	ay.Add(new CHqDataBuffer("09:15"));
			//	ay.Add(new CHqDataBuffer("11:30"));
			//	ay.Add(new CHqDataBuffer("13:00"));
			//	ay.Add(new CHqDataBuffer("15:15"));
			//	return ay.GetSize();			
			//}
		}
		break;
	case HUANGJIN_BOURSE: // �ƽ�����
		{
			switch(MakeSubMarket(cStockType))
			{
			case 0:		    // ��������
				ay.Add(new CHqDataBuffer("20:55"));
				ay.Add(new CHqDataBuffer("23:30"));
				ay.Add(new CHqDataBuffer("09:00"));
				ay.Add(new CHqDataBuffer("11:30"));
				ay.Add(new CHqDataBuffer("13:00"));
				ay.Add(new CHqDataBuffer("15:30"));
				return ay.GetSize();
			case KIND_GOLD:		    // �Ϻ��ƽ�
				ay.Add(new CHqDataBuffer("20:55"));
				ay.Add(new CHqDataBuffer("23:30"));
				ay.Add(new CHqDataBuffer("09:00"));
				ay.Add(new CHqDataBuffer("11:30"));
				ay.Add(new CHqDataBuffer("13:00"));
				ay.Add(new CHqDataBuffer("15:30"));
				return ay.GetSize();
			}
		}
		break;
	case GUZHI_BOURSE: // ��ָ�ڻ�
		{
			switch(MakeSubMarket(cStockType))
			{
			case 0:		    // ��������
				ay.Add(new CHqDataBuffer("09:00"));
				ay.Add(new CHqDataBuffer("11:30"));
				ay.Add(new CHqDataBuffer("13:00"));
				ay.Add(new CHqDataBuffer("15:00"));
				return ay.GetSize();
			case KIND_GUZHI: // ��ָ�ڻ�
				ay.Add(new CHqDataBuffer("09:15"));
				ay.Add(new CHqDataBuffer("11:30"));
				ay.Add(new CHqDataBuffer("13:00"));
				ay.Add(new CHqDataBuffer("15:00"));
				return ay.GetSize();
			}
		}
		break;
	default:
		break;
	}

	ay.Add(new CHqDataBuffer("09:00"));
	ay.Add(new CHqDataBuffer("11:30"));
	ay.Add(new CHqDataBuffer("13:30"));
	ay.Add(new CHqDataBuffer("15:00"));
	return ay.GetSize();
}

void SplitString(CString source, CString divKey, CStringArray& dest) // ����ַ���
{
	dest.RemoveAll();   
	CString szTemp;   
	char* skey = divKey.GetBuffer(0);
	int i=0;
	while(AfxExtractSubString(szTemp, source, i++, *skey))   
	{   
		dest.Add(szTemp);   
	} 
}


int CMainFrameSend::GetClass_TradePhases(HSMarketDataType cStockType,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay)
{

	char acMarketType[32];
	sprintf(acMarketType, "%x", MakeMainMarket(cStockType));

	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Setting_File);
	YlsPrompt("MakeSystemSetup-�����ļ�",szPath);

	CYlsIni YlsIniFile;//(1);
	YlsIniFile.Open(szPath);


	char * pszTradePhases;

	// ȡ�����г���Ӧ�Ľ���ʱ��
	pszTradePhases = YlsIniFile.ReadString(Section_TradePhases, acMarketType, "") ;
	if (CString(pszTradePhases) == "")
	{
		// ȡ�ø��г���Ӧ�Ľ���ʱ��
		sprintf(acMarketType, "%x", MakeMarket(cStockType));
		pszTradePhases = YlsIniFile.ReadString(Section_TradePhases, acMarketType, "");
	}

	CStringArray arrPhases;
	CString szTradePhases(pszTradePhases);
	if (szTradePhases != "")
	{
		SplitString(szTradePhases, ",", arrPhases);
		int i;
		for (i = 0; i < arrPhases.GetSize(); i ++)
		{
			ay.Add(new CHqDataBuffer(arrPhases[i]));
		}
	}
	return ay.GetSize();
}


// added by Ben
int CMainFrameSend::GetClass_HJ_MARKET_Timer(HSMarketDataType cStockType,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay)
{


	switch( MakeSecMarket(cStockType) )
	{
	case HJ_SH_CURR:
		{		
			ay.Add(new CHqDataBuffer("21:00"));
			ay.Add(new CHqDataBuffer("24:00"));
			ay.Add(new CHqDataBuffer("00:00"));
			ay.Add(new CHqDataBuffer("03:30"));
			ay.Add(new CHqDataBuffer("09:00"));
			ay.Add(new CHqDataBuffer("11:30"));
			ay.Add(new CHqDataBuffer("13:30"));
			ay.Add(new CHqDataBuffer("15:30"));

/*
			ay.Add(new CHqDataBuffer("20:55"));
			ay.Add(new CHqDataBuffer("23:30"));
			ay.Add(new CHqDataBuffer("09:00"));
			ay.Add(new CHqDataBuffer("11:30"));
			ay.Add(new CHqDataBuffer("13:00"));
			ay.Add(new CHqDataBuffer("15:30"));*/
			
			return ay.GetSize();
		}
		break;
	case HJ_SH_QH:
		{
			ay.Add(new CHqDataBuffer("09:00"));
			ay.Add(new CHqDataBuffer("10:15"));
			ay.Add(new CHqDataBuffer("10:30"));
			ay.Add(new CHqDataBuffer("11:30"));
			ay.Add(new CHqDataBuffer("13:30"));
			ay.Add(new CHqDataBuffer("14:10"));
			ay.Add(new CHqDataBuffer("14:20"));
			ay.Add(new CHqDataBuffer("15:00"));
			return ay.GetSize();
		}
		break;
	case HJ_WORLD:
	case HJ_OTHER:
		{
			ay.Add(new CHqDataBuffer("06:00"));
			ay.Add(new CHqDataBuffer("24:00"));
			ay.Add(new CHqDataBuffer("00:00"));	
			ay.Add(new CHqDataBuffer("06:00"));
			return ay.GetSize();
		}
		break;
	}

	ay.Add(new CHqDataBuffer("06:00"));
	ay.Add(new CHqDataBuffer("24:00"));
	ay.Add(new CHqDataBuffer("00:00"));	
	ay.Add(new CHqDataBuffer("06:00"));
	return ay.GetSize();
}
// end add


int CMainFrameSend::GetClass_WP_MARKET_Timer(HSMarketDataType cStockType,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay)
{
/*	if( g_sysSysConfigSend.m_bSupportWenHua  || // �Ļ�
		g_sysSysConfigSend.nEntry_Support_YiTian )	
	{
		ay.Add(new CHqDataBuffer("07:00"));
		ay.Add(new CHqDataBuffer("24:00"));
		ay.Add(new CHqDataBuffer("00:00"));
		ay.Add(new CHqDataBuffer("07:00"));
		return ay.GetSize();
	}
*/
	//
	int nSecMarket = MakeSecMarket(cStockType);
	switch( nSecMarket )
	{
	case WP_INDEX:
		{
			int nSubMarket = MakeSubMarket(cStockType);
			switch(nSubMarket)
			{
			case WP_INDEX_RJ: 
				{													  
					ay.Add(new CHqDataBuffer("08:00"));
					ay.Add(new CHqDataBuffer("10:00"));
					ay.Add(new CHqDataBuffer("11:30"));
					ay.Add(new CHqDataBuffer("14:00"));
				}
				return ay.GetSize();
			case WP_INDEX_HZ: 
				{													  
					ay.Add(new CHqDataBuffer("09:30"));
					ay.Add(new CHqDataBuffer("11:30"));
					ay.Add(new CHqDataBuffer("14:00"));
					ay.Add(new CHqDataBuffer("16:00"));
				}
				return ay.GetSize();
			case WP_INDEX_NH: 
				{													  
					ay.Add(new CHqDataBuffer("08:00"));
					ay.Add(new CHqDataBuffer("14:00"));
				}
				return ay.GetSize();
			case WP_INDEX_TG: 
				{													  
					ay.Add(new CHqDataBuffer("09:00"));
					ay.Add(new CHqDataBuffer("13:30"));
				}
				return ay.GetSize();
			case WP_INDEX_XG: 
				{													  
					ay.Add(new CHqDataBuffer("09:00"));
					ay.Add(new CHqDataBuffer("12:30"));
					ay.Add(new CHqDataBuffer("14:00"));
					ay.Add(new CHqDataBuffer("17:00"));
				}
				return ay.GetSize();
			case WP_INDEX_MG: 
				{
					ay.Add(new CHqDataBuffer("09:00"));
					ay.Add(new CHqDataBuffer("12:30"));
					ay.Add(new CHqDataBuffer("14:30"));
					ay.Add(new CHqDataBuffer("17:00"));
				}
				return ay.GetSize();
			case WP_INDEX_TGZH: 
				{
					ay.Add(new CHqDataBuffer("11:00"));
					ay.Add(new CHqDataBuffer("13:30"));
					ay.Add(new CHqDataBuffer("15:30"));
					ay.Add(new CHqDataBuffer("17:30"));
				}
				return ay.GetSize();
			case WP_INDEX_YN: 
			case WP_INDEX_SENSEX:
				{
					ay.Add(new CHqDataBuffer("10:30"));
					ay.Add(new CHqDataBuffer("13:00"));
					ay.Add(new CHqDataBuffer("14:30"));
					ay.Add(new CHqDataBuffer("17:00"));
				}
				return ay.GetSize();
			case WP_INDEX_AZ: // ����
				{													  
					ay.Add(new CHqDataBuffer("07:00"));
					ay.Add(new CHqDataBuffer("14:00"));
				}
				return ay.GetSize();


			case WP_INDEX_DQGY:
			case WP_INDEX_DQYS:
			case WP_INDEX_DQGG:
			case WP_INDEX_NSDK:
			case WP_INDEX_BZPE:
			case WP_INDEX_CRBYX:
			case WP_INDEX_CRBZS:
			case WP_INDEX_JND:
			case WP_INDEX_FS100:
			case WP_INDEX_BP100:
				{													  
					ay.Add(new CHqDataBuffer("21:30"));
					ay.Add(new CHqDataBuffer("24:00"));
					ay.Add(new CHqDataBuffer("00:00"));
					ay.Add(new CHqDataBuffer("04:00"));
				}
				return ay.GetSize();

			case WP_INDEX_DEDAX:
			case WP_INDEX_FACAC:
			case WP_INDEX_HEAEX:
			case WP_INDEX_DMKFX:
			case WP_INDEX_BLS:
			case WP_INDEX_RSSSMI:
			case WP_INDEX_BDI:
			case WP_INDEX_ERTS:
			case WP_INDEX_YFTMIB:
				{													  
					ay.Add(new CHqDataBuffer("15:00"));
					ay.Add(new CHqDataBuffer("24:00"));
				}
				return ay.GetSize();
			case WP_INDEX_BXBVSP:
				ay.Add(new CHqDataBuffer("21:30"));
				ay.Add(new CHqDataBuffer("24:00"));
				ay.Add(new CHqDataBuffer("00:00"));
				ay.Add(new CHqDataBuffer("05:00"));
				return ay.GetSize();
			default:
				ay.Add(new CHqDataBuffer("06:00"));
				ay.Add(new CHqDataBuffer("24:00"));
				ay.Add(new CHqDataBuffer("00:00"));
				ay.Add(new CHqDataBuffer("06:00"));
				return ay.GetSize();
			}
		}
	case WP_LME:
		ay.Add(new CHqDataBuffer("08:00"));
		ay.Add(new CHqDataBuffer("24:00"));
		ay.Add(new CHqDataBuffer("00:00"));
		ay.Add(new CHqDataBuffer("02:00"));
		return ay.GetSize();
		break;
	case WP_CBOT:	//				0x0300	// CBOT			
		{
			ay.Add(new CHqDataBuffer("06:00"));
			ay.Add(new CHqDataBuffer("24:00"));
			ay.Add(new CHqDataBuffer("00:00"));
			ay.Add(new CHqDataBuffer("06:00"));
			/*
			ay.Add(new CHqDataBuffer("20:30"));
			ay.Add(new CHqDataBuffer("24:00"));
			ay.Add(new CHqDataBuffer("00:00"));
			ay.Add(new CHqDataBuffer("03:15"));
			ay.Add(new CHqDataBuffer("09:30"));
			ay.Add(new CHqDataBuffer("20:00"));*/
		}
		return ay.GetSize();
	case WP_NYMEX:	 //			0x0400	// NYMEX	 	
		//strSection = "NYMEX";
		ay.Add(new CHqDataBuffer("06:00"));
		ay.Add(new CHqDataBuffer("24:00"));
		ay.Add(new CHqDataBuffer("00:00"));
		ay.Add(new CHqDataBuffer("06:00"));
		return ay.GetSize();		
		break;
	case WP_COMEX:	 //			0x0500	// COMEX	 	
		//strSection = "COMEX";
		{
			ay.Add(new CHqDataBuffer("06:00"));
			ay.Add(new CHqDataBuffer("24:00"));
			ay.Add(new CHqDataBuffer("00:00"));
			ay.Add(new CHqDataBuffer("06:00"));
		}
		return ay.GetSize();
	case WP_TOCOM:	 //			0x0600	// TOCOM	 	
		//strSection = "TOCOM";
		if( g_sysSysConfigSend.nEntry_Support_TongXin )	// ͬ��
		{
		}
		else
		{
			ay.Add(new CHqDataBuffer("08:00"));
			ay.Add(new CHqDataBuffer("10:00"));
			ay.Add(new CHqDataBuffer("11:00"));
			ay.Add(new CHqDataBuffer("14:30"));
		}
		return ay.GetSize();
	case WP_IPE:	//				0x0700	// IPE			
		//strSection = "IPE";

		ay.Add(new CHqDataBuffer("06:00"));
		ay.Add(new CHqDataBuffer("24:00"));
		ay.Add(new CHqDataBuffer("00:00"));
		ay.Add(new CHqDataBuffer("06:00"));

		return ay.GetSize();
	case WP_NYBOT:	//			0x0800	// NYBOT		
		//strSection = "NYBOT";
		ay.Add(new CHqDataBuffer("06:00"));
		ay.Add(new CHqDataBuffer("24:00"));
		ay.Add(new CHqDataBuffer("00:00"));
		ay.Add(new CHqDataBuffer("06:00"));
		/*
		ay.Add(new CHqDataBuffer("01:30"));
		ay.Add(new CHqDataBuffer("14:15"));*/
		return ay.GetSize();
	case WP_NOBLE_METAL:	//		0x0900	// �Ϻ��ƽ�	
		ay.Add(new CHqDataBuffer("06:00"));
		ay.Add(new CHqDataBuffer("24:00"));
		ay.Add(new CHqDataBuffer("00:00"));
		ay.Add(new CHqDataBuffer("06:00"));
			return ay.GetSize();
		break;

	case WP_FUTURES_INDEX:	//	0x0a00	// ��ָ
		//strSection = "��ָ";
		if( g_sysSysConfigSend.nEntry_Support_TongXin )	// ͬ��
		{
			switch(MakeSubMarket(cStockType))
			{
			case 0: // �յ�����				
				ay.Add(new CHqDataBuffer("00:00"));
				ay.Add(new CHqDataBuffer("24:00"));				
				break;
			case 1:	 // ��ָ501,HK
				ay.Add(new CHqDataBuffer("09:45"));
				ay.Add(new CHqDataBuffer("12:30"));
				ay.Add(new CHqDataBuffer("14:30"));
				ay.Add(new CHqDataBuffer("16:15"));
				break;
			case 2:	 // �վ�503,CM
				ay.Add(new CHqDataBuffer("08:00"));
				ay.Add(new CHqDataBuffer("14:30"));
				break;
			case 3:	 // �ն�503,CM
				ay.Add(new CHqDataBuffer("23:30"));
				ay.Add(new CHqDataBuffer("24:00"));
				ay.Add(new CHqDataBuffer("00:00"));
				ay.Add(new CHqDataBuffer("03:30"));
				break;
			}
		}
		else
		{
			ay.Add(new CHqDataBuffer("09:45"));
			ay.Add(new CHqDataBuffer("12:30"));
			ay.Add(new CHqDataBuffer("14:30"));
			ay.Add(new CHqDataBuffer("16:15"));
		}
		return ay.GetSize();
	case WP_SICOM:			//	0x0b00	// SICOM		
		//strSection = "SICOM";

		// modified by Ben
		ay.Add(new CHqDataBuffer("06:00"));
		ay.Add(new CHqDataBuffer("24:00"));
		ay.Add(new CHqDataBuffer("00:00"));
		ay.Add(new CHqDataBuffer("06:00"));

		//ay.Add(new CHqDataBuffer("10:00"));
		//ay.Add(new CHqDataBuffer("17:00"));
		return ay.GetSize();
	case WP_LIBOR:			//	0x0c00	// LIBOR		
		//strSection = "LIBOR";
		ay.Add(new CHqDataBuffer("07:00"));
		ay.Add(new CHqDataBuffer("24:00"));
		ay.Add(new CHqDataBuffer("00:00"));
		ay.Add(new CHqDataBuffer("06:00"));
		return ay.GetSize();
	case WP_NYSE:			//		0x0d00	// NYSE
		//strSection = "NYSE";
		return 0;
	case WP_CEC:			//		0x0e00	// CEC
		//strSection = "CEC";
		return 0;

	default:
		{
			ay.Add(new CHqDataBuffer(g_szWPDefaultTime[0]));
			ay.Add(new CHqDataBuffer(g_szWPDefaultTime[1]));
			ay.Add(new CHqDataBuffer(g_szWPDefaultTime[2]));
			ay.Add(new CHqDataBuffer(g_szWPDefaultTime[3]));
			return ay.GetSize();
		}
	}

	return 0;
}


short CMainFrameSend::ReadTaskTime(HSMarketDataType cStockType,HSMarketDataType cTime,int nPos,BOOL bWrite)
{
	CHqDataBuffer strSection;
	strSection.Alloc(256);
	CHqDataBuffer strEntry;
	strEntry.Alloc(256);

	//	int nDefault;

	MarketInfo_send* pMarketInfo = MarketInfo_send::GetMarketByID(cStockType);
	if( pMarketInfo == NULL )
		return -1;

	//strSection  = pMarketInfo->GetName();
	//strSection += "-��ͣ��ʱ��";

	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);

	switch(cTime & 0x0F)
	{
	case ZT_Start:
		sprintf(strEntry.m_lpszBuffer, "%hx-����%i",cStockType,nPos );
		//nDefault = 2*nDefault;
		break;
	case ZT_Stop:
		sprintf(strEntry.m_lpszBuffer, "%hx-ͣ��%i",cStockType,nPos );
		//nDefault = 2*nDefault + 1;
		break;
	default:
		return -1;
	}

	//CWinApp* pApp = AfxGetApp();
	CHqDataBuffer strTemp;
	strTemp.CopyStr(pMarketInfo->m_sYlsIni.GetProfileString(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,""));
	if(strTemp.IsEmpty())
	{
		if( MakeMarket(cStockType) == FUTURES_MARKET ) // �����ڻ�
		{
			CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;
			int nCount = GetClass_TradePhases(cStockType,ay);
			if (nCount == 0)
				nCount = GetClass_QH_MARKET_Timer(cStockType,ay);
			if ( nPos < nCount )
			{
				strTemp.Copy(ay.GetAt(nPos));
				_delArrayObj(ay);
			}
			else
			{
				_delArrayObj(ay);
				return -1;
			}			

			//if( nPos > 3 )
			//	return -1;
			//strTemp = g_szQHDefaultTime[nPos];
		}
		else if( MakeMarket(cStockType) == HK_MARKET ) // �۹�
		{
			if( nPos > 3 )
				return -1;
			strTemp = g_szGGDefaultTime[nPos];
		}
		else if( MakeMarket(cStockType) == WP_MARKET ) // ����
		{
#if defined(Support_Test) || defined(Support_WP_UsedFiedTime)
			if( nPos > 3 )
				return -1;
			strTemp = g_szWPDefaultTime[nPos];
#else
			CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;
			int nCount = GetClass_TradePhases(cStockType,ay);
			if (nCount == 0)
				nCount = GetClass_WP_MARKET_Timer(cStockType,ay);
			if ( nPos < nCount )
			{
				strTemp.Copy(ay.GetAt(nPos));
				_delArrayObj(ay);
			}
			else
			{
				_delArrayObj(ay);
				return -1;
			}	
#endif

		}
		else if( MakeMarket(cStockType) == HJ_MARKET ) // �ƽ�
		{
			CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;
			int nCount = GetClass_TradePhases(cStockType,ay);
			if (nCount == 0)
			    nCount = GetClass_HJ_MARKET_Timer(cStockType,ay);
			if ( nPos < nCount )
			{
				strTemp.Copy(ay.GetAt(nPos));
				_delArrayObj(ay);
			}
			else
			{
				_delArrayObj(ay);
				return -1;
			}
		}
		else if( MakeMarket(cStockType) == FOREIGN_MARKET ) // ���
		{
			if( nPos > 3 )
				return -1;

			CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;
			int nCount = GetClass_TradePhases(cStockType,ay);
			if (nCount != 0)
			{
				if ( nPos < nCount )
				{
					strTemp.Copy(ay.GetAt(nPos));
					_delArrayObj(ay);
				}
				else
				{
					_delArrayObj(ay);
					return -1;
				}
			}
			else
			{
				if( g_sysSysConfigSend.nEntry_Support_TongXin )
					strTemp = g_szWHDefaultTime_TongXin[nPos];
				else
					strTemp = g_szWHDefaultTime[nPos];
			}
		}
		else	// ��Ʊ
		{
			if( nPos > 3 )
				return -1;
			CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;
			int nCount = GetClass_TradePhases(cStockType,ay);
			if (nCount != 0)
			{
				if ( nPos < nCount )
				{
					strTemp.Copy(ay.GetAt(nPos));
					_delArrayObj(ay);
				}
				else
				{
					_delArrayObj(ay);
					return -1;
				}
			}
			else
			{
				strTemp = g_szStockDefaultTime[nPos];
			}
		}

		if( bWrite )
		{
			pMarketInfo->m_sYlsIni.WriteProfileString(strSection.m_lpszBuffer, 
				strEntry.m_lpszBuffer,strTemp.m_lpszBuffer);
		}
	}

	nPos = strTemp.Find(":");
	int nHour,nMinute = 0;
	nHour = atoi(strTemp.m_lpszBuffer);

	if(nPos != -1)
		nMinute = atoi(&strTemp.m_lpszBuffer[nPos+1]);

	return (short)(nHour*60 + nMinute);
}

void CMainFrameSend::GetClass_STOCK_MARKET(HSMarketDataType cStockType,
										   CHqDataBuffer& strSection,
										   CHqDataBuffer& strEntry,
										   CHqDataBuffer& strDefault,
										   CHqDataBuffer& strNot,
										   CHqDataBuffer& strName)
{
	switch( MakeSecMarket(cStockType) )
	{
	case SH_BOURSE: // �Ϻ�
		{
			//strSection = "��֤֤ȯ����";
			switch(MakeSubMarket(cStockType))
			{
			case KIND_INDEX:
				strName = "��ָ֤��";
				strDefault = "000000~000030,000300,0009";
				break;
			case KIND_STOCKA:
				strName = "��֤����";
				strDefault = "600,601";				
				//strNot = "600000,600001";
				break;
			case KIND_STOCKB:
				strName = "��֤�¹�";
				strDefault = "9";
				break;
			case KIND_BOND:		    // ծȯ
				strName = "��֤ծȯ";
				strDefault = "00,01,10,11,12,181,190,191,201,202,704036,799";
				break;
			case KIND_FUND:			// ����
				strName = "��֤����";
				strDefault = "500,519";
				break;
				//case KIND_THREEBOAD:    // ����
				//	strName = "����";
				//	strDefault = "4";
				//	break;
				//case KIND_SMALLSTOCK:   // ��С�̹�
				//	strName = "��С�̹�";
				//	strDefault = "002";
				//	break;
			case KIND_PLACE:		// ����
				strName = "�������";
				strDefault = "609";
				break;
				//case KIND_LOF:			// LOF
				//	break;
				//case KIND_USERDEFINE:   // �Զ���ָ��
				//	break;
			case KIND_ETF:
				strName = "��֤ETF";
				strDefault = "510,510050,510051";
				break;
			case KIND_QuanZhen: // Ȩ֤
				strName = "��֤Ȩ֤";
				strDefault = "58";
				break;
			case SC_Others:
				strName = "��֤����";
				break;			
			}
		}
		break;
	case SZ_BOURSE: // ����
		{
			//strSection = "��֤֤ȯ����";
			switch(MakeSubMarket(cStockType))
			{
			case KIND_INDEX:
				strName = "��ָ֤��";
				strDefault = "39";
				break;
			case KIND_STOCKA:
				strName = "��֤����";
				strDefault = "000,001";
				//strNot = "000001,000002";
				break;
			case KIND_STOCKB:
				strName = "��֤�¹�";
				strDefault = "2";
				break;
			case KIND_BOND:		    // ծȯ
				strName = "��֤ծȯ";
				strDefault = "080,10,11,12,13";
				break;
			case KIND_FUND:			// ����
				strName = "��֤����";
				strDefault = "16,184";
				break;
			case KIND_THREEBOAD:    // ����
				strName = "����";
				strDefault = "4";
				break;
			case KIND_SMALLSTOCK:   // ��С�̹�
				strName = "��С�̹�";
				strDefault = "002";
				break;
			case KIND_PLACE:		// ����
				strName = "��������";
				strDefault = "003";
				break;
				//case KIND_LOF:			// LOF
				//	break;
				//case KIND_USERDEFINE:   // �Զ���ָ��
				//	break;
			case KIND_ETF:
				strName = "��֤ETF";
				strDefault = "519";//"51,510050,510051";
				break;
			case KIND_QuanZhen: // Ȩ֤
				strName = "��֤Ȩ֤";
				strDefault = "03";
				break;
			case KIND_OtherIndex:
				strName = "���ָ��";
				strDefault = "8";
				break;
			case SC_Others:
				strName = "��֤����";
				break;
				//case SC_StockS:
				//	strName = "��ҵ��";
				//	strDefault = "6";
				//	break;
				//case SC_Others:
			}
		}
		break;
	}

	strSection.Alloc(256);
	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);

	strEntry.Alloc(256);
	sprintf(strEntry.m_lpszBuffer,"%hx",cStockType);
}

void CMainFrameSend::GetClass_HK_MARKET(HSMarketDataType cStockType,
										CHqDataBuffer& strSection,
										CHqDataBuffer& strEntry,
										CHqDataBuffer& strDefault,
										CHqDataBuffer& strNot,
										CHqDataBuffer& strName)
{
	switch( MakeSecMarket(cStockType) )
	{
	case HK_BOURSE: // �����г�
		{
			//strSection = "�۹������г�����";
			switch(MakeSubMarket(cStockType))
			{
			case HK_KIND_BOND	:   // ծȯ
				strName = "ծȯ";
				strDefault = "01";
				break;
			case HK_KIND_MulFund:   // һ�����Ϲ�֤
				strName = "һ�����Ϲ�֤";
				strDefault = "02";
				break;
			case HK_KIND_FUND	:   // ����
				strName = "����";
				strDefault = "03";
				break;
			case KIND_WARRANTS	:   // �Ϲ�֤
				strName = "�Ϲ�֤";
				strDefault = "04";
				break;
			case KIND_JR		:   // ����
				strName = "����";
				strDefault = "05";
				break;
			case KIND_ZH		:   // �ۺ�
				strName = "�ۺ�";
				strDefault = "06";
				break;
			case KIND_DC		:   // �ز�
				strName = "�ز�";
				strDefault = "07";
				break;
			case KIND_LY		:   // ����
				strName = "����";
				strDefault = "08";
				break;
			case KIND_GY		:   // ��ҵ
				strName = "��ҵ";
				strDefault = "09";
				break;
			case KIND_GG		:   //  ����
				strName = "����";
				strDefault = "10";
				break;
			case KIND_QT		:   //  ����
				strName = "����";
				strDefault = "11";
				break;
			}
		}
		break;
	case GE_BOURSE://		 ��ҵ���г�(Growth Enterprise Market)
		{
			//strSection = "�۹ɴ�ҵ�����";
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "��ҵ��";
				strDefault = "12";
				break;
			}
		}
		break;
	case INDEX_BOURSE://	 ָ���г�
		{
			//strSection = "�۹�ָ������";
			switch(MakeSubMarket(cStockType))
			{
			case HK_KIND_INDEX			 :   // ��ָ
				strName = "�۹�ָ��";
				strDefault = "13";
				break;
			case HK_KIND_FUTURES_INDEX	 :   // ��ָ
				strName = "�۹���ָ";
				strDefault = "14";
				break;
			}
		}
		break;
	}

	strSection.Alloc(256);
	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);

	strEntry.Alloc(256);
	sprintf(strEntry.m_lpszBuffer,"%hx",cStockType);
}


void CMainFrameSend::GetClass_WP_MARKET(HSMarketDataType cStockType,
										CHqDataBuffer& strSection,
										CHqDataBuffer& strEntry,
										CHqDataBuffer& strDefault,
										CHqDataBuffer& strNot,
										CHqDataBuffer& strName)
{
	switch( MakeSecMarket(cStockType) )
	{
	case WP_INDEX:	 //			0x0500	// COMEX	 	
		{
			switch(MakeSubMarket(cStockType))
			{
			case 1: //"�վ�"
				strName = "�վ�ָ��";
				strDefault = "7120";
				break;
			case 2: //"����ָ��"
				strName = "����ָ��";
				strDefault = "7121";
				break;
			case 3: //"�Ϻ��ۺ�"
				strName = "�Ϻ��ۺ�";
				strDefault = "7122";
				break;
			case 4: //"̨�ɼ�Ȩ"
				strName = "̨�ɼ�Ȩ";
				strDefault = "7123";
				break;
			case 5: //"�ǹɺ�Ͽ"
				strName = "�ǹɺ�Ͽ";
				strDefault = "7124";
				break;
			case 6: //"����ۺ�"
				strName = "����ۺ�";
				strDefault = "7125";
				break;
			case 7: //"̩���ۺ�"
				strName = "̩���ۺ�";
				strDefault = "7126";
				break;
			case 8: //"ӡ���ۺ�"
				strName = "ӡ���ۺ�";
				strDefault = "7127";
				break;
			case 9: //"�����ۺ�"
				strName = "�����ۺ�";
				strDefault = "7128";
				break;
			case 0x0a: //"Ŧ����"
				strName = "Ŧ����";
				strDefault = "7129";
				break;

			case 0x0b: //"SGXĦ̨"
				strName = "SGXĦ̨";
				strDefault = "7130";
				break;
			case 0x0c: //"ӡSENSEX"
				strName = "ӡSENSEX";
				strDefault = "7164";
				break;
			case 0x0d:
				strName = "KOSPI200";
				strDefault = "7185";
				break;
			case 0x0e:
				strName = "����ҵ";
				strDefault = "7301";
				break;
			case 0x0f:
				strName = "��������";
				strDefault = "7302";
				break;
			case 0x10: 
				strName = "������";
				strDefault = "7303";
				break;
			case 0x11: 
				strName = "��˹���";
				strDefault = "7304";
				break;


			case 0x12: 
				strName = "��׼�ն�";
				strDefault = "7305";
				break;
			case 0x13: 
				strName = "CRB����";
				strDefault = "7306";
				break;
			case 0x14: 
				strName = "CRBָ��";
				strDefault = "7307";
				break;
			case 0x15: 
				strName = "���ô�";
				strDefault = "7308";
				break;
			case 0x16: 
				strName = "��ʱ100";
				strDefault = "7309";
				break;
			case 0x17: 
				strName = "��CAC40";
				strDefault = "7310";
				break;
			case 0x18: 
				strName = "��DAX";
				strDefault = "7312";
				break;
			case 0x19: 
				strName = "����AEX";
				strDefault = "7313";
				break;
			case 0x1a: 
				strName = "����KFX";
				strDefault = "7314";
				break;
			case 0x1b: 
				strName = "����ʱ";
				strDefault = "7315";
				break;

			case 0x1c: 
				strName = "��ʿSSMI";
				strDefault = "7316";
				break;
			case 0x1d: 
				strName = "����BVSP";
				strDefault = "7117";
				break;
			case 0x1e: 
				strName = "BDIָ��";
				strDefault = "7321";
				break;
			case 0x1f: 
				strName = "����100";
				strDefault = "7322";
				break;
			case 0x20: 
				strName = "��RTS";
				strDefault = "7123";
				break;
			case 0x21: 
				strName = "��FTMIB";
				strDefault = "7124";
				break;
			default:
				strName = "����ָ��";
				strDefault = "";
				break;
			}
		}
		break;
	case WP_LME:
		{
			switch(MakeSubMarket(cStockType))
			{
			case WP_LME_SUB:
				strName = "�׶ؽ���"; // ����ͭ
				strDefault = "7071700~7071749";
				break;
			}
		}
		break;

	case WP_CBOT:	//				0x0300	// CBOT		
		{
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "֥�Ӹ���Ʒ";
				strDefault = "7010000~7010999,7012000~7019999";
				break;
			}
		}
		break;
	case WP_NYMEX:	 //			0x0400	// NYMEX	 	
		//strSection = "NYMEX";
		strName = "ŦԼԭ��";
		switch(MakeSubMarket(cStockType))
		{
		case WP_NYMEX_YY:		
			strName = "ԭ��";
			strDefault = "7060700~7060799";
			break;
		case WP_NYMEX_RY:		
			strName = "ȼ��";
			strDefault = "7060800~7060899";
			break;
		case WP_NYMEX_QY:		
			strName = "����";
			strDefault = "7060900~7060999";
			break;
		}
		break;
	case WP_COMEX:	 //			0x0500	// COMEX	 	
		{
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "ŦԼ��Ʒ";
				strDefault = "7040000~7049999";
				break;
			}
		}
		break;
	case WP_TOCOM:	 //			0x0600	// TOCOM	 	
		{
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "������ҵƷ";
				strDefault = "7100000~7109999";
				break;
			}
		}
		break;
	case WP_IPE:	//				0x0700	// IPE			
		//strSection = "IPE";
		switch(MakeSubMarket(cStockType))
		{
		case 0:
			strName = "�׶ع���ʯ��";
			strDefault = "7110000~7119999";
			break;
		}
		break;
	case WP_NYBOT:	//			0x0800	// NYBOT		
		//strSection = "NYBOT";
		switch(MakeSubMarket(cStockType))
		{
		case 0:
			strName = "ŦԼ�ڻ�";
			strDefault = "7030000~7039999";
			break;
		}
		break;
	case WP_NOBLE_METAL:	//		0x0900	// �����	// �Ϻ��ƽ�
		{
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "�ֻ�";
				strDefault = "3000000~3999999";
				break;
			case 1:
				strName = "�ƽ�";
				strDefault = "7011500~7011599";
				break;
			case 2:
				strName = "����";
				strDefault = "7011600~7011699";
				break;
			}
		}
		break;

	case WP_FUTURES_INDEX:	//	0x0a00	// ��ָ
		{
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "��ָ";
				strDefault = "5000000~5999999";
				break;
			}
		}
		break;
	case WP_SICOM:			//	0x0b00	// SICOM		
		//strSection = "SICOM";
		switch(MakeSubMarket(cStockType))
		{
		case 0:
			strName = "SICOM";
			strDefault = "7090000~7099999";
			break;
		}
		break;
	case WP_LIBOR:			//	0x0c00	// LIBOR		
		//strSection = "LIBOR";
		switch(MakeSubMarket(cStockType))
		{
		case 0:
			strName = "LIBOR";
			strDefault = "6000000~6999999";
			break;
		}
		break;
	case WP_NYSE:			//		0x0d00	// NYSE
		//strSection = "NYSE";
		switch(MakeSubMarket(cStockType))
		{
		case 0:
			strName = "NYSE";
			break;
		}
		break;
	case WP_CEC:			//		0x0e00	// CEC
		//strSection = "CEC";
		switch(MakeSubMarket(cStockType))
		{
		case 0:
			strName = "CEC";
			break;
		}
		break;
	}

	strSection.Alloc(256);
	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);

	strEntry.Alloc(256);
	sprintf(strEntry.m_lpszBuffer,"%hx",cStockType);
}


// added by Ben
void CMainFrameSend::GetClass_HJ_MARKET(HSMarketDataType cStockType,
										CHqDataBuffer& strSection,
										CHqDataBuffer& strEntry,
										CHqDataBuffer& strDefault,
										CHqDataBuffer& strNot,
										CHqDataBuffer& strName)
{
	switch( MakeSecMarket(cStockType) )
	{
	case HJ_SH_CURR:
		{
			strName = "�Ϻ��ƽ�";
			strDefault = "AU9999,AU9995,PT9995,AUT5,AU50,AUTD,AG999,AGTD,AU100,AUTN1,AUTN2,AG9999";
			/*
			switch(MakeSubMarket(cStockType))
			{
				case 0:
				strName = "�Ϻ��ƽ�";
				strDefault = "5101~5111";
				break;
			}*/
		}
		break;
	case HJ_SH_QH:
		{
			strName = "�Ϻ��ڻ�";
			strDefault = "010501~010524";
		}
		break;
	case HJ_WORLD:
		{
			strName = "���ʻƽ�";
			strDefault = "5120~5128";
		}
		break;
	case HJ_OTHER:
		{
			strName = "�����г�";
			strDefault = "5180~5192";
			/*
			switch(MakeSubMarket(cStockType))
			{
				strName = "�����г�";
				strDefault = "5180~5192";
				break;
			}*/
	
		}
		break;
	}

	strSection.Alloc(256);
	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);

	strEntry.Alloc(256);
	sprintf(strEntry.m_lpszBuffer,"%hx",cStockType);
}
// end add


void CMainFrameSend::GetClass_FOREIGN_MARKET(HSMarketDataType cStockType,
											 CHqDataBuffer& strSection,
											 CHqDataBuffer& strEntry,
											 CHqDataBuffer& strDefault,
											 CHqDataBuffer& strNot,
											 CHqDataBuffer& strName)
{
	switch( MakeSecMarket(cStockType) )
	{
	case WH_BASE_RATE: // ��������
		{
			//strSection = "���������г�����";
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "��������";

#ifdef Support_WHStandardCode
				strDefault = "USD";
#else
				strDefault = "1020000~1020099";
#endif
				break;
			}
		}
		break;
	case WH_ACROSS_RATE://		 �������
		{
			//strSection = "������ʷ���";
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "�������";

#ifdef Support_WHStandardCode
				strDefault = "AUDCAD,AUDCHF,AUDHKD,AUDJPY,CADHKD,CADJPY,CHFCAD,CHFHKD,CHFJPY,EURAUD,EURCAD,EURCHF,EURHKD,EURJPY,GBPAUD,GBPCAD,GBPCHF,GBPEUR,GBPHKD,GBPJPY,HKDJPY";
#else
				strDefault = "1020100~1029999";
#endif
				break;
			}
		}
		break;
	case WH_FUTURES_RATE://	 �ڻ�
		{
			//strSection = "�ڻ����";			
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				strName = "�ڻ�";
				strDefault = "4000000~4999999";
				break;
			}
		}
		break;
	}

	strSection.Alloc(256);
	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);

	strEntry.Alloc(256);
	sprintf(strEntry.m_lpszBuffer,"%hx",cStockType);
}

void CMainFrameSend::GetClass_FUTURES_MARKET(HSMarketDataType cStockType,
											 CHqDataBuffer& strSection,
											 CHqDataBuffer& strEntry,
											 CHqDataBuffer& strDefault,
											 CHqDataBuffer& strNot,
											 CHqDataBuffer& strName)
{
	switch( MakeSecMarket(cStockType) )
	{
	case DALIAN_BOURSE: // ����
		{
			//strSection = "�����ڻ�����";
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				//strName = "��������";
				//break;
			//case 0xf:               // modified by Ben
				strName = "�����г�";
				break;
			case KIND_BEAN:
				strName = "��������";
				strDefault = "A,B,M,GN";
				break;
			case KIND_YUMI:
				strName = "��������";
				strDefault = "C";
				break;
			case KIND_SHIT:
				strName = "����ʳ��";
				strDefault = "DT";
				break;
			case KIND_DZGY:
				strName = "���ڹ�ҵ1";
				strDefault = "GJ";
				break;
			case KIND_DZGY2:
				strName = "���ڹ�ҵ2";
				strDefault = "SS";
				break;
			case KIND_DOUYOU: 
				strName = "��������";
				strDefault = "Y";
				break;
			case KIND_JYX:
				strName = "����ϩ";
				strDefault = "L";
				break;
			case KIND_ZTY:
				strName = "�����";
				strDefault = "P";
				break;
			}
		}
		break;
	case SHANGHAI_BOURSE://		 0x0200	// �Ϻ�
		{
			//strSection = "�Ϻ��ڻ�����";
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				//strName = "�Ϻ�����";
				//break;
			//case 0xf:
				strName = "�Ϻ��г�";
				break;
			case KIND_METAL:
				strName = "�Ϻ�����";
				strDefault = "CU,AL,ZN";
				break;
			case KIND_RUBBER:
				strName = "�Ϻ���";
				strDefault = "RU";
				break;
			case KIND_FUEL:
				strName = "�Ϻ���Դ";
				strDefault = "FU";
				break;
			//case KIND_GUZHI:// ��ָ�ڻ�
			//	strName = "��ָ�ڻ�";
			//	strDefault = "IF";
			//	break;
			case KIND_QHGOLD:	// �Ϻ��ƽ�
				strName = "�ƽ��ڻ�";
				strDefault = "AU";
				break;
			}
		}
		break;
	case HUANGJIN_BOURSE://		 0x0200	// �ƽ�
		{
			//strSection = "�Ϻ��ڻ�����";
			switch(MakeSubMarket(cStockType))
			{			
			case KIND_GOLD:	// �Ϻ��ƽ�
				strName = "�Ϻ��ƽ�";
				strDefault = "AGT+D,AG999,AUT+5,AUT+D,AU100G,AU50G,AU9995,AU9999,PT9995";
				break;
			}
		}
		break;
	case GUZHI_BOURSE:	// ��ָ�ڻ�
		{
			//strSection = "�Ϻ��ڻ�����";
			switch(MakeSubMarket(cStockType))
			{			
			case KIND_GUZHI:	// ��ָ�ڻ�
				strName = "��ָ�ڻ�";
				strDefault = "IF,04";   // modified by Ben,it need to be complete.
				break;
			}
		}
		break;
	case ZHENGZHOU_BOURSE://	 0x0300	// ֣��
		{
			//strSection = "֣���ڻ�����";
			switch(MakeSubMarket(cStockType))
			{
			case 0:
				//strName = "֣������";
				//break;
			//case 0xf:
				strName = "֣���г�";
				break;
			case KIND_XIAOM:
				strName = "֣��С��";
				strDefault = "WT,WS";
				break;
			case KIND_MIANH:
				strName = "֣���޻�";
				strDefault = "CF";
				break;
			case KIND_BAITANG:
				strName = "֣�ݰ���";
				strDefault = "SR";
				break;
			case KIND_PTA: // pta
				strName = "PTA";
				strDefault = "TA";
				break;
			case KIND_CZY:
				strName = "������";
				strDefault = "RO";
				break;
			}		
		}
		break;
	}

	strSection.Alloc(256);
	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);

	strEntry.Alloc(256);
	sprintf(strEntry.m_lpszBuffer,"%hx",cStockType);
}

//��ʼ������
char* CMainFrameSend::ReadCodeScope(HSMarketDataType cStockType,StockTypeInfo& stiStock,CHqDataBuffer& strTemp,BOOL bWrite)
{
	CHqDataBuffer strSection;
	CHqDataBuffer strEntry;
	CHqDataBuffer strDefault;
	CHqDataBuffer strNot;
	CHqDataBuffer strName;

	switch( MakeMarket(cStockType) )
	{
	case STOCK_MARKET: // ��Ʊ
		GetClass_STOCK_MARKET(cStockType,strSection,strEntry,strDefault,strNot,strName);
		break;
	case FUTURES_MARKET: // �����ڻ�
		GetClass_FUTURES_MARKET(cStockType,strSection,strEntry,strDefault,strNot,strName);
		break;
	case HK_MARKET: // �۹ɷ���
		GetClass_HK_MARKET(cStockType,strSection,strEntry,strDefault,strNot,strName);
		break;
	case WP_MARKET: // ����
		GetClass_WP_MARKET(cStockType,strSection,strEntry,strDefault,strNot,strName);
		break;
	case FOREIGN_MARKET: // ���
		GetClass_FOREIGN_MARKET(cStockType,strSection,strEntry,strDefault,strNot,strName);
		break;
	case HJ_MARKET: // �ƽ�
		GetClass_HJ_MARKET(cStockType,strSection,strEntry,strDefault,strNot,strName); // added by Ben
		break;
	default:
		return ("");
	}

	MarketInfo_send* pMarketInfo = MarketInfo_send::GetMarketByID(cStockType);
	if( pMarketInfo == NULL )
		return "";

	//CWinApp* pApp = AfxGetApp();

	// ������
	CHqDataBuffer strNotCode;
	CHqDataBuffer strTempEntry;
	strTempEntry.cat(strEntry.m_lpszBuffer,0,"-����������",0);

	strNotCode = pMarketInfo->m_sYlsIni.GetProfileString(strSection.m_lpszBuffer,strTempEntry.m_lpszBuffer,"");
	strNotCode.MakeUpper();
	if( strNotCode.IsEmpty() )
	{
		strNotCode.Copy(&strNot);
		strNotCode.MakeUpper();
		if( bWrite )
		{
			pMarketInfo->m_sYlsIni.WriteProfileString(strSection.m_lpszBuffer, 
				strTempEntry.m_lpszBuffer,strNotCode.m_lpszBuffer);
		}
	}
	stiStock.m_strNotCode.Copy(&strNotCode);	

	// ��������
	strTempEntry.cat(strEntry.m_lpszBuffer,0,"-��������",0);
	stiStock.m_strName = pMarketInfo->m_sYlsIni.GetProfileString(strSection.m_lpszBuffer,strTempEntry.m_lpszBuffer,"");
	if( stiStock.m_strName.IsEmpty() )
	{
		stiStock.m_strName.Copy(&strName);
		if( bWrite )
		{
			pMarketInfo->m_sYlsIni.WriteProfileString(strSection.m_lpszBuffer, 
				strTempEntry.m_lpszBuffer,strName.m_lpszBuffer);
		}
	}

	// ����	
	strTempEntry.cat(strEntry.m_lpszBuffer,0,"-��������",0);
	strTemp = pMarketInfo->m_sYlsIni.GetProfileString(strSection.m_lpszBuffer,strTempEntry.m_lpszBuffer,"");
	strTemp.MakeUpper();
	if(strTemp.IsEmpty())
	{
		strTemp.Copy(&strDefault);
		strTemp.MakeUpper();
		if( bWrite )
		{
			pMarketInfo->m_sYlsIni.WriteProfileString(strSection.m_lpszBuffer, 
				strTempEntry.m_lpszBuffer,strTemp.m_lpszBuffer);
		}
	}

	return strTemp.m_lpszBuffer;
}

BOOL CMainFrameSend::BulidStockInfo(StockTypeInfo& stiStock,HSMarketDataType cStockType,char& nSaveCurNow)
{
	// 
	stiStock.m_stType.m_nStockType = cStockType;

	MarketInfo_send* pMarketInfo = MarketInfo_send::GetMarketByID(cStockType);
	if( pMarketInfo == NULL )
		return 0;

	// �ͻ���ʹ�õ�λ
	//CWinApp* pApp = AfxGetApp();
	CHqDataBuffer strSection;
	strSection.Alloc(256);
	CHqDataBuffer strEntry;
	strEntry.Alloc(256);
	//CString strSection = pMarketInfo->GetName();
	//strSection += "�ͻ���ʹ�õ�λ";

	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);
	sprintf(strEntry.m_lpszBuffer,"%hx-��һ������",cStockType );
	int nUseDefalut = pMarketInfo->m_sYlsIni.GetProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,-1);
	if( nUseDefalut == -1 )
	{
		nUseDefalut = 0;
		pMarketInfo->m_sYlsIni.WriteProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,nUseDefalut);
		nUseDefalut = 1;
	}

	//
	sprintf(strSection.m_lpszBuffer,"%hx",cStockType);
	sprintf(strEntry.m_lpszBuffer,"%hx-�ͻ���ʹ�õ�λ",cStockType );
	int nPriceUnit = pMarketInfo->m_sYlsIni.GetProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,0);
	if( nPriceUnit == 0 )
	{
		if( MakeMarket(cStockType) == FOREIGN_MARKET )
			stiStock.m_stType.m_nPriceUnit = 10000;
		else
			stiStock.m_stType.m_nPriceUnit = 1000;

		if( nUseDefalut )
			pMarketInfo->m_sYlsIni.WriteProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,stiStock.m_stType.m_nPriceUnit);
	}
	else
	{
		stiStock.m_stType.m_nPriceUnit = nPriceUnit;
	}

	// ����ʹ�õ�λ
	//strSection = pMarketInfo->GetName();
	//strSection += "���Ͷ�ʹ�õ�λ";
	sprintf( strEntry.m_lpszBuffer,"%hx-���Ͷ�ʹ�õ�λ",cStockType );
	nPriceUnit = pMarketInfo->m_sYlsIni.GetProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,0);
	if( nPriceUnit == 0 )
	{
		stiStock.m_lSendUnit = stiStock.m_stType.m_nPriceUnit;
		if( nUseDefalut )
			pMarketInfo->m_sYlsIni.WriteProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,stiStock.m_lSendUnit);
	}
	else
	{
		stiStock.m_lSendUnit = nPriceUnit;
	}

	// 
	stiStock.m_stType.m_nTotal	   = 0;
	stiStock.m_stType.m_nOffset    = 0;

	// ʱ�������
	memset(stiStock.m_stType.m_nNewTimes,-1,sizeof(stiStock.m_stType.m_nNewTimes));

	stiStock.m_stType.m_nTotalTime = 0;

	HSTypeTime* pHSTypeTime = stiStock.m_stType.m_nNewTimes;
	int nPos = 0;
	for( int i = 0; i < _countof(stiStock.m_stType.m_nNewTimes); i++,pHSTypeTime++ )
	{
		pHSTypeTime->m_nOpenTime  = ReadTaskTime(cStockType,ZT_Start,nPos++,nUseDefalut);
		pHSTypeTime->m_nCloseTime = ReadTaskTime(cStockType,ZT_Stop,nPos++,nUseDefalut);
		if( pHSTypeTime->m_nOpenTime == -1 )
			break;

		// ʱ������	
		stiStock.m_stType.m_nTotalTime += pHSTypeTime->GetDist();
	}

	// �ͻ���С��λ
	stiStock.m_stType.m_union.m_nPriceDecimal.m_nOpenTime  = -1;
	stiStock.m_stType.m_union.m_nPriceDecimal.m_nCloseTime = -1;

	sprintf(strEntry.m_lpszBuffer,"%hx-�ͻ���С��λ",cStockType );
	int nClientDecimal = pMarketInfo->m_sYlsIni.GetProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,-99);
	if( nClientDecimal == (0 - 99) )
	{
		if( MakeGZIndex(cStockType) /*== (FUTURES_MARKET | SHANGHAI_BOURSE | KIND_GUZHI)*/ ) // ��ָ�ڻ�
		{
			nClientDecimal = 1;//
		}
		else
		{
			nClientDecimal = -1;//
		}

		if( nUseDefalut )
		{
			pMarketInfo->m_sYlsIni.WriteProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,
				nClientDecimal);
		}
	}
	stiStock.m_lClientDecimal = nClientDecimal;
	stiStock.m_stType.m_union.m_nPriceDecimal.m_nCloseTime = nClientDecimal;

	// ������������
	sprintf(strEntry.m_lpszBuffer,"%hx-������������",cStockType);
	nSaveCurNow = pMarketInfo->m_sYlsIni.GetProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,0);
	if( nUseDefalut )
		pMarketInfo->m_sYlsIni.WriteProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,nSaveCurNow);

	// �������	
	sprintf(strEntry.m_lpszBuffer,"%hx-�������",cStockType);
	short nUnionClass = pMarketInfo->m_sYlsIni.GetProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,0);
	stiStock.m_nUnionClass = nUnionClass;
	if( nUseDefalut )
		pMarketInfo->m_sYlsIni.WriteProfileInt(strSection.m_lpszBuffer,strEntry.m_lpszBuffer,nUnionClass);

	// ��ǰʱ��
	stiStock.m_stType.m_nCurTime = 0;

	// �ֽ��������
	CHqDataBuffer strTemp;
	stiStock.m_strCodeScope = ReadCodeScope(cStockType,stiStock,strTemp,nUseDefalut);

	return TRUE;
}

void CMainFrameSend::Prompt(const char* str)
{
	if( str == NULL )
		return;

	char szPrompt[256];
	memset(szPrompt,0,sizeof(szPrompt));
	strncpy(szPrompt,str,sizeof(szPrompt));
	SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)szPrompt);
}

LRESULT CMainFrameSend::OnMonitor(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case ID_COMMU:
		{
			const CSessionInfo_Rec * pInfo = (const CSessionInfo_Rec *)lParam;
			char szBuf[512];

			sprintf(szBuf, "����ͨѶ״̬ TransTotalBytes:%lu,TransRate:%lu,TransTimes:%lu,MaxMinuteTimes:%lu,LastMinuteTimes:%lu", 
				pInfo->m_nTransTotalBytes, 
				pInfo->m_nTransRate, 
				pInfo->m_nTransTimes, 
				pInfo->m_nMaxMinuteTimes, 
				pInfo->m_nLastMinuteTimes);

			WriteError(szBuf,strlen(szBuf),g_strCommStatus);

			//
			break;
		}
	case ID_SH_INDEX:
		{
			break;
		}
	case ID_PROMPT:
		{

#if 0
			CListBox* pList = (CListBox*)pView->GetDlgItem(IDC_MESSAGE);
			if(pList == NULL)
				return 0;
			if(pList->GetCount() > 30000)
			{
				pView->Save(g_strLogfile);
				pList->ResetContent();
			}

			CString strMessage;
			CTime curTime = CTime::GetCurrentTime();
			strMessage.Format("%d/%02d/%02d %02d:%02d:%02d : %s",
				curTime.GetYear(), curTime.GetMonth(), curTime.GetDay(), 
				curTime.GetHour(), curTime.GetMinute(), curTime.GetSecond(),
				*(CString*)lParam);

			pList->AddString(strMessage);
#endif
		}
		break;

	case ID_UDP_HS:
		{
#if 0
			CWnd* pWnd = (CListBox*)pView->GetDlgItem(IDC_EDITCHANGE);
			if(pWnd == NULL)
				return 0;

			CString strMessage;
			strMessage.Format( "%s", *(CString*)lParam);

			pWnd->SetWindowText(strMessage);
#endif

		}
		break;
	case ID_UDP_DZST:
		{
#if 0
			CWnd* pWnd = (CListBox*)pView->GetDlgItem(IDC_EDITCHANGE2);
			if(pWnd == NULL)
				return 0;

			CString strMessage;
			strMessage.Format( "%s", *(CString*)lParam);

			pWnd->SetWindowText(strMessage);
#endif
		}
		break;
	case ID_UDP_WBJR:
		{
#if 0
			CWnd* pWnd = (CListBox*)pView->GetDlgItem(IDC_EDITCHANGE3);
			if(pWnd == NULL)
				return 0;

			CString strMessage;
			strMessage.Format( "%s", *(CString*)lParam);

			pWnd->SetWindowText(strMessage);
#endif
		}
		break;
	case ID_MESSAGE:
		{
			if( lParam == NULL )
				return 0;

			LPCTSTR pData = (LPCTSTR)lParam;
			int nLen = strlen(pData);

			printf(pData);
			WriteError((void*)pData,nLen,NULL);

			break;
		}
	}
	return 0;
}

LRESULT CMainFrameSend::SendMessage(UINT message, WPARAM wParam, LPARAM lParam)
{ 
#ifdef HS_SUPPORT_UNIX
	if( message == (UINT)WM_MONITOR )
		OnMonitor(wParam, lParam);

	return 0;
#else
	return ::SendMessage(m_hWnd, message, wParam, lParam); // m_pWnd->OnMonitor(wParam, lParam);
#endif
}

BOOL CMainFrameSend::StartInitData(int nMarket,int nSend /*= 1*/)
{
	CYlsTime tmNow = CYlsTime::GetCurrentTime();

	// ��Ʊ
	if( MakeMarket(nMarket) == STOCK_MARKET &&
		g_sysSysConfigSend.nEntry_Support_GP )
	{
		m_GP.AllAutoInitData(this,tmNow,nSend);
	}

	// �ڻ�
	if( MakeMarket(nMarket) == FUTURES_MARKET &&
		g_sysSysConfigSend.nEntry_Support_QH )
	{
		m_QH.AllAutoInitData(this,tmNow,nSend);
	}

	// ���
	if( MakeMarket(nMarket) == FOREIGN_MARKET &&
		g_sysSysConfigSend.nEntry_Support_WH )
	{
		m_WH.AllAutoInitData(this,tmNow,nSend);
	}

	// ����
	if( MakeMarket(nMarket) == WP_MARKET &&
		g_sysSysConfigSend.nEntry_Support_WP )
	{
		m_WP.AllAutoInitData(this,tmNow,nSend);
	}

	// �۹�
	if( MakeMarket(nMarket) == HK_MARKET &&
		g_sysSysConfigSend.nEntry_Support_GG )
	{
		m_GG.AllAutoInitData(this,tmNow,nSend);
	}


	// �ƽ�
	if( MakeMarket(nMarket) == HJ_MARKET &&
		g_sysSysConfigSend.nEntry_Support_HJ )
	{
		m_HJ.AllAutoInitData(this,tmNow,nSend);
	}

	return TRUE;
}

void CMainFrameSend::AutoInitData(MarketInfo_send* pMarketInfo,CYlsTime& tmNow,
								  int nSend /*= 1*/,
								  int nForce /*= 0*/)
{
	if( nForce )
	{
		pMarketInfo->m_bInit = 0;
		pMarketInfo->m_bReceived = 0;
		pMarketInfo->m_nMaxTime = 0;
	}

	if(pMarketInfo->m_bInit)
	{
		m_lLastError = LastError_Inited;
		return;
	}

	if( strlen(pMarketInfo->m_strDbfName) <= 0 )
	{
		m_lLastError = LastError_NotInitFileName;
		return;
	}

	// ����3��������ʾ
	if( pMarketInfo->m_nMaxTime > 30 )
	{
		m_lLastError = LastError_InitOverTimes;
		return;
	}

	m_zmRequest.m_nType    = ZM_INITDATA;
	m_zmRequest.m_cSetCode = pMarketInfo->m_cBourse;
	//m_zmRequest.m_cSubType = pMarketInfo->m_cSubType; // ��������,���������ʼ��

	int nRet = pMarketInfo->InitData(&m_zmRequest,nSend/*TRUE*/,this);
	if( nRet == -1 ) // ��������Ϊ��
	{
		m_lLastError = LastError_InitFailed; // ��ʼ��ʧ��
		pMarketInfo->m_nMaxTime++;
		return;
	}

	if( !pMarketInfo->m_bInit )
	{
		pMarketInfo->m_nMaxTime++;

		char strText[1024];
		sprintf(strText,"[%s] ��ʼ��ʧ��,[CMainFrame::AutoInitData]",pMarketInfo->GetName());
		SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);
	}
}

// ʹ��UDP��ʽ���ڹ�Ʊ����
BOOL CMainFrameSend::Init_GP(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain /*= NULL*/)
{
	if( pMarketInfo == NULL )
		return 0;

	if( strlen(pMarketInfo->m_strDbfName) <= 0 )
		return -2;

	return Init_UDP(pMarketInfo,pRequest,bSend);
}

// �ڻ�
BOOL CMainFrameSend::Init_QH(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain /*= NULL*/)
{
	if( pMarketInfo == NULL )
		return 0;

	//	if( !( m_pHsQH->IsValid() || m_pDZSTQH->IsValid() ) )
	//		return 0;

	if( strlen(pMarketInfo->m_strDbfName) <= 0 )
		return -2;

	return Init_UDP(pMarketInfo,pRequest,bSend);
}

// ���
BOOL CMainFrameSend::Init_WH(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain /*= NULL*/)
{
	if( pMarketInfo == NULL )
		return 0;

	//	if( !( m_pWBJRQH->IsValid() || m_pWBJRQH->IsValid() || m_pYF->IsValid() ) )
	//		return 0;

	if( strlen(pMarketInfo->m_strDbfName) <= 0 )
		return -2;

	return Init_UDP(pMarketInfo,pRequest,bSend);
}

// ����
BOOL  CMainFrameSend::Init_WP(CZMRequest* pRequest,BOOL bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain /*= NULL*/) // ����ָ��
{
	if( pMarketInfo == NULL/* || !m_pYF->IsValid()*/ )
		return 0;

	if( strlen(pMarketInfo->m_strDbfName) <= 0 )
		return -2;

	return Init_UDP(pMarketInfo,pRequest,bSend);
}

// �۹�
BOOL  CMainFrameSend::Init_GG(CZMRequest* pRequest,BOOL  bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain /*= NULL*/) // �����г�
{
	if( pMarketInfo == NULL/* || !m_pYF->IsValid()*/ )
		return 0;

	if( strlen(pMarketInfo->m_strDbfName) <= 0 )
		return -2;

	return Init_UDP(pMarketInfo,pRequest,bSend);
}

// �ƽ�
BOOL  CMainFrameSend::Init_HJ(CZMRequest* pRequest,BOOL  bSend,MarketInfo_send* pMarketInfo,CMainFrameSend* pMain /*= NULL*/)
{
	if( pMarketInfo == NULL/* || !m_pYF->IsValid()*/ )
		return 0;

	if( strlen(pMarketInfo->m_strDbfName) <= 0 )
		return -2;

	return Init_UDP(pMarketInfo,pRequest,bSend);
}

BOOL CMainFrameSend::Init_UDP(MarketInfo_send* pMarketInfo,CZMRequest* pRequest,BOOL bSend)
{
	char strPrompt[256];
	CHqDataBuffer buffer;
	int RecordSum = GetQHCFgFileData(pMarketInfo,
		pMarketInfo->GetCodeToNameSection(),pMarketInfo->m_strDbfName,buffer);
	if( RecordSum <= 0 )
	{
		m_lLastError = LastError_ReadCodeEmpty;

		sprintf(strPrompt,"[%s] �ļ�[%s]������:%i\r\n",pMarketInfo->GetName(),pMarketInfo->m_strDbfName,RecordSum);
		Prompt(strPrompt);
		return -1;
	}
	sprintf(strPrompt,"[%s] �ļ�[%s]������:%i\r\n",pMarketInfo->GetName(),pMarketInfo->m_strDbfName,RecordSum);
	Prompt(strPrompt);

	QH_Code_Cfg* pSHData = (QH_Code_Cfg*)buffer.m_lpszBuffer;

	CYlsTime curTime = CYlsTime::GetCurrentTime();
	pMarketInfo->/*InitMap*/InitMap_Raw(RecordSum + RecordSum * 0.2);
	pMarketInfo->Empty();

	// 
	//	HANDLE hInitData;
	ZMInitialData* pInitData;

	CHqDataBuffer bufferInit;

	//
	int nDataSize = sizeof(FileNowData)*RecordSum;
	if( pMarketInfo->m_mapStatic.GetCount() >= 0 )
		nDataSize += sizeof(LevelStatic)*RecordSum;

	long lSize = sizeof(ZMInitialData) + nDataSize;
	if( !bufferInit.Alloc(lSize) )
	{		
		sprintf(strPrompt,"[CMainFrameSend::Init_UDP] �ڴ����ʧ��:%i\r\n",lSize);
		Prompt(strPrompt);
		return -1;
	}

	//hInitData = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,lSize);
	//pInitData = (ZMInitialData*)GlobalLock(hInitData);

	pInitData = (ZMInitialData*)bufferInit.m_lpszBuffer;

	memcpy(&pInitData->m_dhHead,pRequest,sizeof(CZMReplyHead));
	pInitData->m_dhHead.m_nType |= ZM_REPLY;
	pInitData->m_lNowTime = curTime.GetTime();

	// ������������
	memcpy(pInitData->m_nSaveCurNow,pMarketInfo->m_nSaveCurNow,sizeof(pInitData->m_nSaveCurNow));

	//
	DiskBourseInfo*	pbiInfo = &pInitData->m_biInfo;
	FileNowData*    pstInfo = pInitData->m_pstInfo;	

	LevelStatic* pEveryCalculateData = NULL;
	LevelStatic* pCurCalculate = NULL;
	if( pMarketInfo->m_mapStatic.GetCount() > 0 )
	{
		pInitData->m_nCalcDataPos = RecordSum;
		pCurCalculate = pInitData->GetEveryCalculateData();
		pEveryCalculateData = pCurCalculate;
	}


	char strTime[64];

	//CodeInfo* pETFCode = pInitData->m_sCode;

	sprintf(strTime,"%04d%02d%02d",curTime.GetYear(),curTime.GetMonth(),curTime.GetDay());
	pbiInfo->m_lDate  = atol(strTime);
	pbiInfo->m_cType  = pMarketInfo->m_nTypeTotal;
	pbiInfo->m_nBourseType = pMarketInfo->m_cBourse;
	pbiInfo->m_dwCRC = (int)pInitData;


	//
	StockKey* psKey = NULL;
	HSMarketDataType cClassify;
	int nIndex;
	int nUnit;

	/* 2007.09.03 remove
	// delall
	const char* key = NULL;
	CHqDataBuffer* value = NULL;
	POSITION  pos;
	for( pos = pMarketInfo->m_mapCode.GetStartPosition(); pos != NULL; )
	{
		pMarketInfo->m_mapCode.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			delete value;
		}
	}
	pMarketInfo->m_mapCode.RemoveAll();
	*/

	int i;



#define Support_AutoSort

#ifdef Support_AutoSort
	typeFileNowData*  pAy = new typeFileNowData[pMarketInfo->m_nTypeTotal];
#endif

	//
	int nCurCount = 0;
	for( i = 0; i < RecordSum; i++,pSHData++ )
	{
		//
		CHqDataBuffer* strOldDisp;

		CHqDataBuffer strCode;
		strCode.CopyStr(pSHData->m_strCode);

		CHqDataBuffer* strDispCode = new CHqDataBuffer;
		strDispCode->CopyStr(pSHData->m_strDispCode,STOCK_CODE_SIZE);

		//if( !strCode.CompareNoCase("LWLX") )
		//{
		//	int i = 100;
		//	i += 1;
		//	//AfxMessageBox("OK");
		//}

		// ����Դʵ�ʴ���(�ɱ�) = ����ʵ����ʾ����(���6λ)
		if( pMarketInfo->m_mapCode.Lookup(strCode.m_lpszBuffer,(void*&)strOldDisp) ) // ȥ���ظ�����
		{
			// 2007.09.03 replace
			//delete strDispCode;
			//continue;

			strOldDisp->Copy(strDispCode);

			CHqDataBuffer* pDel = strDispCode;
			strDispCode = strOldDisp;
			delete pDel;
		}
		else
		{
			pMarketInfo->m_mapCode.SetAt(strCode.m_lpszBuffer,(void*&)strDispCode);
		}

		//
		psKey = new StockKey;
		strncpy(psKey->m_stkey,strDispCode->m_lpszBuffer,sizeof(psKey->m_stkey));

		cClassify = pSHData->ClassifyStock(this,pMarketInfo->m_cBourse,
			strCode.m_lpszBuffer,strCode.GetLength());

		/*if (MakeMainMarket(cClassify) == (WP_MARKET | WP_INDEX))
			nIndex = 0;
		else
			*/nIndex = MakeSubMarketPos(cClassify);

		pMarketInfo->m_stiStock[nIndex].m_stType.m_nTotal++;
		nUnit = pMarketInfo->m_stiStock[nIndex].m_stType.m_nPriceUnit;

		pstInfo->m_stStockInfo.m_ciStockCode.m_cCodeType = cClassify;
		strncpy(pstInfo->m_stStockInfo.m_ciStockCode.m_cCode,pSHData->m_strDispCode,STOCK_CODE_SIZE);
		strncpy(pstInfo->m_stStockInfo.m_cStockName,pSHData->m_strName,
			sizeof(pstInfo->m_stStockInfo.m_cStockName));

		pstInfo->m_stStockInfo.m_lPrevClose = pSHData->m_lPreClose;//(unsigned long)(pSHData->m_lPreClose*nUnit);
		pstInfo->m_stStockData.m_nHand = GetStockHand(cClassify);

		memcpy(&psKey->m_ciInfo,&pstInfo->m_stStockInfo.m_ciStockCode,sizeof(CodeInfo));

		//
		if( pCurCalculate )
		{
			LevelStatic* pCur;
			if( pMarketInfo->m_mapStatic.Lookup(psKey->m_stkey,(void*&)pCur) )
			{
				memcpy(pCurCalculate,pCur,sizeof(LevelStatic));
			}

			memcpy(&pCurCalculate->m_calc.m_cCodeType,
				&pstInfo->m_stStockInfo.m_ciStockCode,sizeof(CodeInfo));

			CalcData(&pCurCalculate->m_calc,pstInfo);
		}

		pMarketInfo->AddKey(psKey);

#ifdef Support_AutoSort
		FileNowData_Static* pFileNowData = new FileNowData_Static;
		pFileNowData->pFileNowData = new FileNowData;
		memcpy(pFileNowData->pFileNowData,pstInfo,sizeof(FileNowData));

		if( pCurCalculate )
		{
			pFileNowData->pLevelStatic = new LevelStatic;
			memcpy(pFileNowData->pLevelStatic,pCurCalculate,sizeof(LevelStatic));
		}

		pAy[nIndex].Add(pFileNowData);
#endif

		pstInfo++;
		if( pCurCalculate )
			pCurCalculate++;
		nCurCount++;
	}

#ifdef Support_AutoSort
	// ������ദ��
	pstInfo = pInitData->m_pstInfo;
	pCurCalculate = pEveryCalculateData;

	int nCur = 0;
	int j;
	for( i = 0; i < pMarketInfo->m_nTypeTotal; i++ )
	{
		for( j = 0; j < pAy[i].GetSize(); j++ )
		{
			memcpy(pstInfo,pAy[i].GetAt(j)->pFileNowData,sizeof(FileNowData));

			if( pCurCalculate )
			{
				memcpy(pCurCalculate,pAy[i].GetAt(j)->pLevelStatic,sizeof(LevelStatic));
			}

			delete pAy[i].GetAt(j);
			pstInfo++;
			nCur++;

			if( pCurCalculate )
				pCurCalculate++;

		}
	}
	delete[] pAy;

#endif


	// �������
	int nCount = 0;

	short nOffset =  0;
	short nowTime = curTime.GetHour()*60 + curTime.GetMinute();

	for( i = 0; i < pMarketInfo->m_nTypeTotal; i++)
	{
		pMarketInfo->m_stiStock[i].m_stType.m_nCurTime = 0;

		pMarketInfo->m_stiStock[i].m_stType.m_nOffset = nOffset;
		nOffset += pMarketInfo->m_stiStock[i].m_stType.m_nTotal;

		memcpy(&pbiInfo->m_stNewType[i],&pMarketInfo->m_stiStock[i].m_stType,sizeof(StockType));

		//if( pMarketInfo->m_stiStock[i].m_stType.m_nTotal > 0 &&
		//	!pMarketInfo->m_stiStock[i].m_strName.IsEmpty() )
		if( !pMarketInfo->m_stiStock[i].m_strName.IsEmpty() )
		{
			strncpy(pbiInfo->m_stNewType[i].m_stTypeName.m_szName,
				pMarketInfo->m_stiStock[i].m_strName.m_lpszBuffer,
				sizeof(pbiInfo->m_stNewType[i].m_stTypeName.m_szName));			
		}
		if( pMarketInfo->m_stiStock[i].m_stType.m_nTotal > 0 )
			nCount = i;
	}
	pbiInfo->m_cType = nCount + 1;


#ifndef Support_Test
	AddVirtualClass(pMarketInfo,pbiInfo);
#endif


	if ( g_sysSysConfigSend.m_bCodeListSort ) // �Ƿ�����
	{
		KQuickSort qsData;

		// ��������
		qsData.m_pData      = pInitData->m_pstInfo;
		qsData.m_nDataLen   = sizeof(FileNowData);
		qsData.m_nKeyOffset = sizeof(pInitData->m_pstInfo->m_stStockInfo.m_cStockName);
		if( WhoMarket(pMarketInfo->m_cBourse,FUTURES_MARKET) || 
			WhoMarket(pMarketInfo->m_cBourse,STOCK_MARKET) )
		{
			qsData.m_nKeyLen = sizeof(CodeInfo);
		}
		else
		{
			qsData.m_nKeyLen = QS_UNSHORT;
		}
		if( qsData.m_nKeyLen != QS_UNSHORT )  // ��������
		{
			qsData.m_nLow  = 0;
			qsData.m_nHigh = (RecordSum - 1);	
			QuickSortAscend2(&qsData);
		}

		//
		// ��̬��������
		if( pEveryCalculateData != NULL )
		{
			qsData.m_pData      = pEveryCalculateData;
			qsData.m_nDataLen   = sizeof(LevelStatic);
			qsData.m_nKeyOffset = 0;
			if( WhoMarket(pMarketInfo->m_cBourse,FUTURES_MARKET) || 
				WhoMarket(pMarketInfo->m_cBourse,STOCK_MARKET) )
			{
				qsData.m_nKeyLen = sizeof(CodeInfo);
			}
			else
			{
				qsData.m_nKeyLen = QS_UNSHORT;
			}
			if( qsData.m_nKeyLen != QS_UNSHORT )  // ��������
			{
				qsData.m_nLow       = 0;
				qsData.m_nHigh      = (RecordSum-1);	
				QuickSortAscend2(&qsData);
			}
		}
	}

	pMarketInfo->m_bInit = TRUE;

	pInitData->m_dhHead.m_cSetCode = pMarketInfo->m_cBourse;

	//long lSize = sizeof(ZMInitialData) + (long)sizeof(FileNowData)*(RecordSum);
	pInitData->m_lLen  = lSize;
	pInitData->m_nSize = RecordSum;
	Send(pInitData,lSize);

	//// ��������
	//CWinApp* pApp = AfxGetApp();
	//pApp->WriteProfileInt(MarketInfo_Date, pMarketInfo->m_strName, pbiInfo->m_lDate);

	pMarketInfo->m_bReceived = FALSE;

	//
	sprintf(strPrompt,"[%s] �����ļ�[%s]���,������:%i,ʵ����:%i\r\n",
		pMarketInfo->GetName(),pMarketInfo->m_strDbfName,RecordSum,nCurCount);
	Prompt(strPrompt);


	//	if( pMarketInfo->m_pUDPInitDataProc != NULL )
	//	{
	//		(*pMarketInfo->m_pUDPInitDataProc)(pRequest,bSend,pMarketInfo,this);
	//	}

	return 1;
}
long CMainFrameSend::GetGoldWeight(const CodeInfo* pCode)
{
	if( pCode == NULL )
		return 1;

	if( MakeMainMarket(pCode->m_cCodeType) == (HJ_MARKET | HJ_SH_CURR))
	{

		if (CString(pCode->m_cCode,6) == "Au100g" || CString(pCode->m_cCode,7) == "Au99.99")
		{
			return 100;
		}
		else if(CString(pCode->m_cCode,5) == "Au50g")
		{
			return 50;
		}
		else if (CString(pCode->m_cCode,7) == "Ag99.99")
			return 15;
		else if (CString(pCode->m_cCode,7) == "Ag(T+D)")
			return 1000;
		else if (CString(pCode->m_cCode,7) == "Au99.95" || CString(pCode->m_cCode,7) == "Au(T+D)" ||
			CString(pCode->m_cCode,8) == "Au(T+N1)" || CString(pCode->m_cCode,8) == "Au(T+N2)"  || 
			CString(pCode->m_cCode,7) == "Pt99.95" || CString(pCode->m_cCode,7) == "Au(T+5)" || CString(pCode->m_cCode,6) == "Ag99.9")
		{
			return 1000;
		}


		return 1;
		/*		
		if ( CString(pCode->m_cCode,6) == "AU9999")
			return 10;
		else if (CString(pCode->m_cCode,6) == "AU9995")
			return 1;
		else if (CString(pCode->m_cCode,6) == "PT9995")
			return 1;
		else if (CString(pCode->m_cCode,5) == "AU100")
		{
			return 100;
		}
		else if (CString(pCode->m_cCode,4) == "AUTD" ||
			CString(pCode->m_cCode,5) == "AUTN1" || CString(pCode->m_cCode,5) == "AUTN2"  || 
			CString(pCode->m_cCode,4) == "AUT5")
		{
			return 1000;
		}
		else if (CString(pCode->m_cCode,6) == "AG9999")
			return 15;
		else if (CString(pCode->m_cCode,4) == "AGTD")
			return 1;

		return 1;
		*/
	}

	return 1;
}
long CMainFrameSend::GetStockHand(const CodeInfo* pCode,short nHand /*= 0*/)
{

	if (IS_CURR_GOLD(pCode->m_cCode, pCode->m_cCodeType))
		return GetGoldWeight(pCode);

	if( pCode == NULL )
	{
		// 2005.11.10 �ɽ���Խ��
		//return 100;
		return 1;
	}

	if( MakeMarket(pCode->m_cCodeType) == HK_MARKET )
	{
		return 1;
		//return GetHKHand(pCode);
	}
	else
	{
		return GetStockHand(pCode->m_cCodeType, nHand);
	}

	// 2005.11.10 �ɽ���Խ��
	return 100;
	//return 1;
}

long CMainFrameSend::GetStockHand(HSMarketDataType cStockType,short nHand /*= 0*/)
{
	if( nHand > 0 )
	{
		return 1;
		//return nHand;
	}

	// �ڻ�
	if( MakeMarket(cStockType) == QH_Bourse 
		|| MakeMarket(cStockType) == WP_MARKET
		|| MakeMarket(cStockType) == (HSMarketDataType)FOREIGN_MARKET 
		||  MakeMarket(cStockType) == HJ_MARKET)  // modified by Ben
	{
		return 1;
	}

	// ծȯ
	else if( (MakeMarket(cStockType) == STOCK_MARKET) && 
		(MakeSubMarket(cStockType) == KIND_BOND) )
	{
		return 1;
	}
	else if( MakeMarket(cStockType) == HK_MARKET )
	{
		return 1;
	}

	// ��Ʊ
	return 100;
	//return 1;
}

void CMainFrameSend::AddVirtualClass(MarketInfo_send* pMarketInfo,DiskBourseInfo* pbiInfo)
{
	int nSub;
	StockType* pStockType = pbiInfo->m_stNewType;

	int i;

	// ��Ϸ��ദ��...
	StockTypeInfo* pStockTypeInfo = pMarketInfo->m_stiStock;
	for( i = 0; i < pMarketInfo->m_nTypeTotal; i++,pStockTypeInfo++ )
	{
		if( pStockTypeInfo->m_nUnionClass )
		{
			pStockType[i].m_nOffset = 0;
			pStockType[i].m_nTotal  = pStockType[pbiInfo->m_cType-1].m_nOffset + 
				pStockType[pbiInfo->m_cType-1].m_nTotal;

			if( i > pbiInfo->m_cType )
				pbiInfo->m_cType = i + 1;
		}		
	}

	if( WhoMarket(pMarketInfo->m_cBourse,FUTURES_MARKET) )
	{
		/*if( (pMarketInfo->m_cBourse) == (FUTURES_MARKET | DALIAN_BOURSE) )
		{
			if( pStockType[KIND_DZGY].m_nTotal > 0 || pStockType[KIND_DZGY2].m_nTotal > 0 )
			{
				memset(pStockType[KIND_DZGY].m_stTypeName.m_szName,0,
					sizeof(pStockType[KIND_DZGY].m_stTypeName.m_szName));

				memset(pStockType[KIND_DZGY2].m_stTypeName.m_szName,0,
					sizeof(pStockType[KIND_DZGY2].m_stTypeName.m_szName));

				nSub = KIND_DZGY2;
				nSub++;
				pStockType[nSub].m_nOffset = pStockType[KIND_DZGY].m_nOffset;
				pStockType[nSub].m_nTotal  = pStockType[KIND_DZGY2].m_nOffset +
					pStockType[KIND_DZGY2].m_nTotal - 
					pStockType[KIND_DZGY].m_nOffset;
				strncpy(pStockType[nSub].m_stTypeName.m_szName,"���ڹ�ҵ",sizeof(pStockType[nSub].m_stTypeName));

				pbiInfo->m_cType++;
			}
		}*/

		// ���һ��������Ϊȫ������
		if( ((pMarketInfo->m_cBourse) == (FUTURES_MARKET | DALIAN_BOURSE)    ||
			 (pMarketInfo->m_cBourse) == (FUTURES_MARKET | SHANGHAI_BOURSE)  || 
			 (pMarketInfo->m_cBourse) == (FUTURES_MARKET | ZHENGZHOU_BOURSE) ||
			 (pMarketInfo->m_cBourse) == (FUTURES_MARKET | SELF_BOURSE)) )
		{
			nSub = 0xf;
			if( strlen(pStockType[nSub].m_stTypeName.m_szName) > 0 )
			{
				pStockType[nSub].m_nOffset = 0;
				pStockType[nSub].m_nTotal  = pStockType[pbiInfo->m_cType-1].m_nOffset +
					pStockType[pbiInfo->m_cType-1].m_nTotal;

				pbiInfo->m_cType = 16;
			}
		}
		
	}
	// ����
	else if( WhoMarket(pMarketInfo->m_cBourse,WP_MARKET) )
	{	
		// ��һ��Ϊ�ͻ�����ʾ����
		{
			
			if( MakeWPIndex(pMarketInfo->m_cBourse) ) // ����ָ������ʾ�������
			{			
				if( (pMarketInfo->m_cBourse) == (WP_INDEX_AZ | WP_MARKET) ) // ��Ϊ�ܵ���ʾ
				{
				}
				else
				{
					for( i = 1; i < pbiInfo->m_cType; i++ ) // ����ʾ
					{
						memset(pStockType[i].m_stTypeName.m_szName,0,
							sizeof(pStockType[i].m_stTypeName.m_szName));
					}
				}
				pbiInfo->m_cType = (WP_INDEX_YFTMIB - WP_INDEX_RJ);
			}
			else if( MakeWP_LME(pMarketInfo->m_cBourse) ) // LME����ʾ�������
			{	
				// modified by Ben
				if( (pMarketInfo->m_cBourse) == (WP_LME | WP_MARKET) ) // ��Ϊ�ܵ���ʾ
				{
				}
				else
				{
					for( i = 0; i < pbiInfo->m_cType; i++ ) // ����ʾ
					{
						memset(pStockType[i].m_stTypeName.m_szName,0,
							sizeof(pStockType[i].m_stTypeName.m_szName));
					}
				}
			}
			else if( MakeMainMarket(pMarketInfo->m_cBourse) == (WP_MARKET | WP_NOBLE_METAL) ) // �����
			{
				for( i = 0; i < pbiInfo->m_cType; i++ )
				{
					memset(pStockType[i].m_stTypeName.m_szName,0,
						sizeof(pStockType[i].m_stTypeName.m_szName));
				}

				nSub = WP_NOBLE_METAL_BY;
				nSub++;
				pStockType[nSub].m_nOffset = 0;
				pStockType[nSub].m_nTotal  = pStockType[WP_NOBLE_METAL_BY].m_nOffset +
					pStockType[WP_NOBLE_METAL_BY].m_nTotal;
				strncpy(pStockType[nSub].m_stTypeName.m_szName,Language("�����"),sizeof(pStockType[nSub].m_stTypeName));

#ifdef Support_UsedVirtualClass//Support_ACCEPT_RUNTIME_DATA
				pbiInfo->m_cType = nSub + 1;
#else
				pbiInfo->m_cType++;
#endif
			}
			else if( MakeMainMarket(pMarketInfo->m_cBourse) == (WP_MARKET | WP_NYMEX) )
			{
				for( i = 0; i < pbiInfo->m_cType; i++ )
				{
					memset(pStockType[i].m_stTypeName.m_szName,0,
						sizeof(pStockType[i].m_stTypeName.m_szName));
				}

				nSub = WP_NYMEX_QY;
				nSub++;
				pStockType[nSub].m_nOffset = 0;
				pStockType[nSub].m_nTotal  = pStockType[WP_NYMEX_QY].m_nOffset +
					pStockType[WP_NYMEX_QY].m_nTotal;
				strncpy(pStockType[nSub].m_stTypeName.m_szName,"ŦԼԭ��",sizeof(pStockType[nSub].m_stTypeName));

#ifdef Support_UsedVirtualClass//Support_ACCEPT_RUNTIME_DATA
				pbiInfo->m_cType = nSub + 1;
#else
				pbiInfo->m_cType++;
#endif
			}

		}
	}
	// �۹�
	else if( WhoMarket(pMarketInfo->m_cBourse,HK_MARKET) )
	{
		if( MakeMainMarket(pMarketInfo->m_cBourse) == (HK_MARKET | HK_BOURSE) )
		{
			nSub = KIND_QT;
			nSub++;
			pStockType[nSub].m_nOffset = 0;
			pStockType[nSub].m_nTotal  = pStockType[KIND_QT].m_nOffset +
				pStockType[KIND_QT].m_nTotal;
			strncpy(pStockType[nSub].m_stTypeName.m_szName,Language("�۹�����"),sizeof(pStockType[nSub].m_stTypeName));

			pbiInfo->m_cType++;

			nSub++;
			pStockType[nSub].m_nOffset = pStockType[KIND_JR].m_nOffset;
			pStockType[nSub].m_nTotal  = pStockType[KIND_QT].m_nOffset +
				pStockType[KIND_QT].m_nTotal - 
				pStockType[KIND_JR].m_nOffset;
			strncpy(pStockType[nSub].m_stTypeName.m_szName,Language("��Ʊ"),sizeof(pStockType[nSub].m_stTypeName));

			pbiInfo->m_cType++;
			if( pbiInfo->m_cType < (KIND_QT + 1) )
				pbiInfo->m_cType = (KIND_QT + 2);
		}
		else if( MakeMainMarket(pMarketInfo->m_cBourse) == (HK_MARKET | INDEX_BOURSE) )
		{
			nSub = HK_KIND_FUTURES_INDEX;
			nSub++;
			pStockType[nSub].m_nOffset = 0;
			pStockType[nSub].m_nTotal  = pStockType[HK_KIND_FUTURES_INDEX].m_nOffset +
				pStockType[HK_KIND_FUTURES_INDEX].m_nTotal;
			strncpy(pStockType[nSub].m_stTypeName.m_szName,Language("����ָ��"),sizeof(pStockType[nSub].m_stTypeName));
			pbiInfo->m_cType++;
		}
	}
	// �ƽ� added by Ben
	else if( WhoMarket(pMarketInfo->m_cBourse,HJ_MARKET) )
	{
		int test = 0;
	}
}

BOOL CMainFrameSend::IsNotCode(const char* strCode,int nLen,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay)
{
	if( strCode == NULL || ay.GetSize() <= 0 )
		return FALSE;

	CHqDataBuffer* pStart;
	for( int i = 0; i < ay.GetSize(); i++ )
	{
		pStart = ay.GetAt(i);
		if( pStart == NULL || pStart->IsEmpty() )
			continue;

		if( memcmp(strCode,pStart->m_lpszBuffer,strlen(pStart->m_lpszBuffer)) == 0 )
			return TRUE;
	}

	return FALSE;
}

HSMarketDataType CMainFrameSend::ClassifyStock(HSMarketDataType cBourse,const char* strCode,int nCodeLen,
											   int* pRet /*= NULL*/)
{
	if( pRet )
		*pRet = 0;

	StockTypeInfo* pStock;
	short nTotal = 4;

	MarketInfo_send* pMarketInfo = MarketInfo_send::GetMarketByID(cBourse);
	if( pMarketInfo == NULL )			
		return 0;	

	pStock = pMarketInfo->m_stiStock;
	nTotal = pMarketInfo->m_nTypeTotal;

	BOOL bStock = ( cBourse == SH_Bourse || cBourse == SZ_Bourse );
	if( bStock )
	{
		for(int i = 0; i < nCodeLen; i++)
		{
			if(isalpha(strCode[i]))
				return (cBourse | KIND_INDEX);
		}
	}

	char* pStart;
	char* pEnd;

	int nLen = strlen(strCode);

	CHqDataBufferArray ay;

	for( int i = 0; i < nTotal; i++ )
	{
		AnalyzeStr(pStock[i].m_strNotCode.m_lpszBuffer,",",ay.ay);

		if( IsNotCode(strCode,nLen,ay.ay) )
			continue;

		CHqDataBuffer strScope;
		strScope.Copy(&pStock[i].m_strCodeScope);
		if( strScope.IsEmpty() )
			continue;

		pStart = (char*)(const char*)strScope.m_lpszBuffer;
		pStart = strtok(pStart,",");
		while( pStart != NULL )
		{
			pEnd = strchr(pStart,'~');
			if(pEnd != NULL)
			{
				*pEnd = '\0';
				pEnd++;
				if( (nLen == strlen(pEnd)) &&
					(nLen == strlen(pStart)) && 
					(memcmp(strCode,pStart,nLen) >= 0) &&
					(memcmp(strCode,pEnd,nLen) <= 0) )
				{
					if( pRet )
						*pRet = 1;
					return (HSMarketDataType)pStock[i].m_stType.m_nStockType;
				}
			}
			else if( !strncasecmp(strCode,pStart,strlen(strCode)) )
			{
				if( pRet )
					*pRet = 1;
				return (HSMarketDataType)pStock[i].m_stType.m_nStockType;
			}
			else if( memcmp(strCode,pStart,min(strlen(strCode),strlen(pStart))) == 0)
			{
				if( pRet )
					*pRet = 1;
				return (HSMarketDataType)pStock[i].m_stType.m_nStockType;
			}

			pStart = strtok(NULL,",");
		}
	}

	if( !bStock )
	{
		return cBourse;
	}

	return cBourse | SC_Others;
}

int CMainFrameSend::LoadCodeNameData(const char* strSection,CYlsMapStringToPtr& mapCodeName,const char* strQiHuoCodeNameProfile)
{
	if( mapCodeName.GetCount() > 0 )
		return mapCodeName.GetCount();

	CHqDataBufferArray strArray;
	CHqDataBufferArray pCodeArray;
	CYlsIni YlsIni;
	YlsIni.Open(strQiHuoCodeNameProfile);
	if( !YlsIni.ReadConfigSectionString(strSection,pCodeArray.ay,&strArray.ay) )
		return 0;

	CHqDataBuffer* str;
	int nItem = min(strArray.ay.GetSize(),pCodeArray.ay.GetSize());
	for( int i = 0; i < nItem; i++ )
	{
		str = pCodeArray.ay.GetAt(i);
		if( str == NULL || str->IsEmpty() )
			continue;

		str->MakeUpper();
		mapCodeName.SetAt(str->m_lpszBuffer,strArray.ay.GetAt(i));
	}

	strArray.ay.RemoveAll();

	return mapCodeName.GetCount();
}

char* CMainFrameSend::Language(const char* szSource,int nMask /*= 0*/)
{
	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Setting_File);

	CYlsIni YlsIni;
	YlsIni.Open(szPath);

	char* strTemp;
	strTemp = YlsIni.GetProfileString("���Զ��ձ�", szSource, szSource);
	if( strTemp == NULL )
		return (char*)szSource;

	static CHqDataBuffer buffer;
	buffer.CopyStr(strTemp);

	return buffer.m_lpszBuffer;
}

char* CMainFrameSend::GetCodeToNameFileName(CHqDataBuffer& buffer)
{
	// ˽���ļ�����...

	buffer.Alloc(512);

	char szPath[_MAX_PATH];
	CHSFilePath::GetPath(szPath,CHSFilePath::MarketFile);

	sprintf(buffer.m_lpszBuffer,"%s%s.name",szPath,g_strCfgShortName);

	if( access(buffer.m_lpszBuffer,0) != 0 )
		buffer.CopyStr(g_strQiHuoCodeNameProfile);

	return buffer.m_lpszBuffer;
}

int CMainFrameSend::ReplaceName(CYlsMapStringToPtr& mapCodeName,QH_Code_Cfg* pSHData,int nLen)
{
	if( nLen > 6 )
		return 0;

	CHqDataBuffer str1;
	str1.CopyStr(pSHData->m_strDispCode,nLen);
	str1.MakeUpper();
	CHqDataBuffer* strName;

	if( mapCodeName.Lookup(str1.m_lpszBuffer,(void*&)strName) ) // 2
	{
		CHqDataBuffer cur;
		cur.CopyStr(&pSHData->m_strDispCode[nLen],STOCK_CODE_SIZE-nLen);
		CHqDataBuffer curName;
		curName.Copy(strName);
		curName.AddStr(cur.m_lpszBuffer);
		if( !curName.IsEmpty() )
		{
			strncpy(pSHData->m_strName,curName.m_lpszBuffer,sizeof(pSHData->m_strName));
			return 1;
		}
	}

	return 0;
}

int CMainFrameSend::GetQHCFgFileData(MarketInfo_send* pMarketInfo,const char* strCodeToName,
									 const char* strFileName,CHqDataBuffer& buffer)
{
	CYlsIni YlsIni;
	YlsIni.Open(strFileName);

	CHqDataBufferArray strArray1;
	CHqDataBufferArray strArray;
	if( !YlsIni.ReadConfigSectionString("code",strArray1.ay,&strArray.ay) )
	{
		m_lLastError = LastError_CfgFormatError;

		char strPrompt[256];
		sprintf(strPrompt,"[%s] �����ļ�[%s]û�ж�[code],��ȷ�ϸ�ʽ�Ƿ���ȷ\r\n",
			pMarketInfo->GetName(),pMarketInfo->m_strDbfName);
		Prompt(strPrompt);

		return 0;
	}

	int nItem = strArray.ay.GetSize();

	// 2007.11.15 replace
	if( !buffer.Alloc(sizeof(QH_Code_Cfg) * (nItem + 1)) )
		return 0;

	QH_Code_Cfg* pSHData = (QH_Code_Cfg*)buffer.m_lpszBuffer;

	// ��������
	CYlsMapStringToPtr mapCodeName;
	CHqDataBuffer bufferCodeToNameFile;
	LoadCodeNameData(strCodeToName,mapCodeName,GetCodeToNameFileName(bufferCodeToNameFile));

	CYlsMapStringToPtr mapCodeFilter;

	// ��ʽ��1=��ǰ�������,����,ɾ�����,��ʾ����,����,�����̼�
	CHqDataBuffer* str;
	CHqDataBuffer* str1;
	CHqDataBufferArray ayRet;
	CHqDataBuffer* pTemp;
	int n;
	int nCurCount = 0;

	for( int i = 0; i < nItem; i++ )
	{
		str = strArray.ay.GetAt(i);
		if( str == NULL || str->IsEmpty() )
			continue;

		n = AnalyzeStr(str->m_lpszBuffer,",",ayRet.ay);
		if( n < 1 )
			continue;

		// �Ƿ�ʹ�øô���,��ʹ������ʾ
		if( n >= 3 )
		{
			pTemp = ayRet.ay.GetAt(2);
			if( pTemp == NULL )
				continue;

			pTemp->Trim();
			if( atol(pTemp->m_lpszBuffer) )	// = 1
				continue;
		}

		// ����
		if( n >= 1 )
		{
			str = ayRet.ay.GetAt(0);
			str->Trim();
			str->MakeUpper();
			strncpy(pSHData->m_strCode,str->m_lpszBuffer,sizeof(pSHData->m_strCode));

			if( n < 4 ) // �õ�ǰ���������ʾ����
			{				
				strncpy(pSHData->m_strDispCode,str->m_lpszBuffer,sizeof(pSHData->m_strDispCode));
			}			
		}

		// ����
		if( n >= 2 )
		{
			str = ayRet.ay.GetAt(1);
			str->Trim();
			strncpy(pSHData->m_strName,str->m_lpszBuffer,sizeof(pSHData->m_strName));
		}
		else
			memset(pSHData->m_strName,0,sizeof(pSHData->m_strName));

		// ������
		if( n >= 6 )
		{
			str = ayRet.ay.GetAt(5);
			str->Trim();
			pSHData->m_lPreClose = atol(str->m_lpszBuffer);
		}

		// ʵ����ʾ����
		if( n >= 4 )
		{
			str = ayRet.ay.GetAt(3);
			str->Trim();
			str->MakeUpper();
			if( str->IsEmpty() )
			{
				strncpy(pSHData->m_strDispCode,pSHData->m_strCode,sizeof(pSHData->m_strDispCode));
			}
			else
			{
				strncpy(pSHData->m_strDispCode,str->m_lpszBuffer,sizeof(pSHData->m_strDispCode));
			}

			//if( !str->CompareNoCase("LWLX") )
			//{
			//	int i = 100;
			//	i += 1;
			//	//AfxMessageBox("OK");
			//}
		}

		// ����ָ������
		if( n >= 5 )
		{
			str = ayRet.ay.GetAt(4);
			str->Trim();
			str->MakeUpper();

			if( str->IsEmpty() )
				pSHData->m_InstrumentType = 0;
			else
				pSHData->m_InstrumentType = atol(str->m_lpszBuffer);
		}

		// �Զ��������
		if( strlen(pSHData->m_strName) <= 0 )
		{
			if( MakeMarket(pMarketInfo->m_cBourse) == FOREIGN_MARKET ) // ���
			{
				CHqDataBuffer strName;
				CHqDataBuffer str1; 
				str1.CopyStr(pSHData->m_strDispCode,3);
				CHqDataBuffer* strName1;
				if( mapCodeName.Lookup(str1.m_lpszBuffer,(void*&)strName1) ) // 3
					strName.AddStr(strName1->m_lpszBuffer);
				str1.CopyStr(&pSHData->m_strDispCode[3],3);
				CHqDataBuffer* strName2;
				if( mapCodeName.Lookup(str1.m_lpszBuffer,(void*&)strName2) ) // 3
					strName.AddStr(strName2->m_lpszBuffer);

				if( !strName.IsEmpty() )
					strncpy(pSHData->m_strName,strName.m_lpszBuffer,sizeof(pSHData->m_strName));
			}
			else if( MakeMarket(pMarketInfo->m_cBourse) == FUTURES_MARKET ) // �ڻ�
			{
				for(int nCount = 6; nCount > 0; nCount-- )
				{
					if( ReplaceName(mapCodeName,pSHData,nCount) )
						break;
				}

				/*
				CHqDataBuffer str1;
				str1.CopyStr(pSHData->m_strDispCode,2);
				str1.MakeUpper();
				CHqDataBuffer* strName;

				if( mapCodeName.Lookup(str1.m_lpszBuffer,(void*&)strName) ) // 2
				{
					CHqDataBuffer cur;
					cur.CopyStr(&pSHData->m_strDispCode[2],4);
					CHqDataBuffer curName;
					curName.Copy(strName);
					curName.AddStr(cur.m_lpszBuffer);
					if( !curName.IsEmpty() )
						strncpy(pSHData->m_strName,curName.m_lpszBuffer,sizeof(pSHData->m_strName));
				}
				else 
				{
					//CHqDataBuffer str1;
					str1.CopyStr(pSHData->m_strDispCode,1);
					str1.MakeUpper();

					if( mapCodeName.Lookup(str1.m_lpszBuffer,(void*&)strName) ) // 1
					{
						CHqDataBuffer cur;
						cur.CopyStr(&pSHData->m_strDispCode[1],5);
						CHqDataBuffer curName;
						curName.Copy(strName);
						curName.AddStr(cur.m_lpszBuffer);
						if( !curName.IsEmpty() )
							strncpy(pSHData->m_strName,curName.m_lpszBuffer,sizeof(pSHData->m_strName));
					}
				}
				*/

			}
		}

		// ������ʾ�ظ�����
		CHqDataBuffer curStr;
		curStr.CopyStr(pSHData->m_strDispCode,STOCK_CODE_SIZE);
		if( mapCodeFilter.Lookup(curStr.m_lpszBuffer,(void*&)str1) )
			continue;
		else
			mapCodeFilter.SetAt(curStr.m_lpszBuffer,str1);

		//
		pSHData++;
		nCurCount++;
	}


	// delall
	const char* key = NULL;
	CHqDataBuffer* value = NULL;
	POSITION  pos;
	for( pos = mapCodeName.GetStartPosition(); pos != NULL; )
	{
		mapCodeName.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			delete value;
		}
	}
	mapCodeName.RemoveAll();

	//char* key = NULL;
	//void* value = NULL;
	//CHqDataBuffer* pType = NULL;
	//YlsMapDelAll2(mapCodeName,key,value,pType);

	return nCurCount;
}

int	CMainFrameSend::IsConnectSrv()
{
	return ( m_pConnectSession != NULL && m_pConnectSession->IsConnect() );
}

BOOL CMainFrameSend::Send(void* pData, long lLen,BOOL bZip /*= 1*/)
{
	/*if( !g_sysSysConfigSend.IsTransmit() )
		 return 1;*/

	if( !IsConnectSrv()/*m_pConnectSession == NULL || !m_pConnectSession->IsConnect()*/ )
	{
#ifdef HS_SUPPORT_UNIX
		if( m_pYlsBaseDoc )
		{
			m_pYlsBaseDoc->AutoConnectRecv();
		}

		//YlsPrompt("CYlsBaseDoc::SendData","û������");
#endif
		return 0;
	}

	static char* szBuf = "��������";	
	WriteError(szBuf,strlen(szBuf),g_strCommStatus);

	if( bZip && 
		lLen > 512 // 2007.09.06 add ����һ���ֽ���ѹ��
		)
	{
		CZipDataBuffer pDataBuffer;
		YlsZipData(pDataBuffer,(char*&)pData,lLen);
		return m_pConnectSession->Send(pData,lLen,CYlsSession::Send_NotDelPrePackage);
	}

	// CYlsSession::Send_NotDelPrePackage [2006.12.06 add]
	return m_pConnectSession->Send(pData,lLen,CYlsSession::Send_NotDelPrePackage);

	//	if( m_pYlsBaseDoc == NULL )
	//		return 0;
	//				  
	//#ifdef HS_SUPPORT_UNIX
	//	return m_pYlsBaseDoc->SendData(pData,lLen);
	//#endif

	//return 0;

	/*if (m_pSession)
	{
	CCommLinkStatusInfo info;
	m_pSession->GetLinkStatus(&info);
	if (info.m_nStatus == SS_CONNECTED)
	{
	CZipDataBuffer pDataBuffer;
	YlsZipData(pDataBuffer,(char*&)pData,lLen);
	return m_pSession->Send((const char *)pData,lLen);
	}
	}*/

	//return FALSE;
}

LRESULT CMainFrameSend::OnReceivedData_JH(WPARAM wParam, LPARAM lParam)
{
	if( m_pMainSend == NULL )
	{
		printf("m_pMainSend == NULL");
		return 0;
	}

	if( (wParam - 8) < sizeof(XLI_SysParamReturn) || lParam == NULL )
	{
		printf("��ȡ��ʼ�����ݴ���");
		return 0;
	}

	char* pData = (char*)lParam;
	pData = &pData[8];
	XLI_SysParamReturn* pXLI_SysParamReturn = (XLI_SysParamReturn*)pData;

	char szPrompt[256];
	memset(szPrompt,0,sizeof(szPrompt));
	strncpy(szPrompt,pXLI_SysParamReturn->available_product.v,200);
	printf("���г�ʼ�����ݷ��أ�\r\n");
	printf(szPrompt);
	printf("\r\n");

	CHqDataBufferArray ay;
	CHqDataBuffer* pBuffer;

	CHSStockPosition_send* pPosition = NULL;
	MarketInfo_send* pMarketInfo;

	// audcad,audchf,audhkd,audjpy,cadhkd,cadjpy,chfcad,chfhkd,chfjpy,euraud,eurcad,eurchf,eurhkd,eurjpy,gbpaud,gbpcad,gbpchf,gbpeur,gbphkd,gbpjpy,hkdjpy

	//char c[256];
	//sprintf(c,"MarketInfoManager::GetMarketByInclude:%i\r\n",m_WH.m_ay.GetSize());
	//printf(c);

	//CString szPrompt = "audcad,audchf,audhkd,audjpy,cadhkd,cadjpy,chfcad,chfhkd,chfjpy,euraud,eurcad,eurchf,eurhkd,eurjpy,gbpaud,gbpcad,gbpchf,gbpeur,gbphkd,gbpjpy,hkdjpy";

	YlsAllTrim(szPrompt);

	int nCount = AnalyzeStr(szPrompt,"|",ay.ay);
	for( int i = 0; i < nCount; i++ )
	{
		pBuffer = ay.ay.GetAt(i);
		if( pBuffer == NULL || pBuffer->IsEmpty() )
			continue;

		CHqDataBufferArray ayItem;
		AnalyzeStr(pBuffer->m_lpszBuffer,"#",ayItem.ay);
		if( ayItem.ay.GetSize() < 2 )
		{
			printf(pBuffer->m_lpszBuffer);
			printf("\r\n");
			continue;
		}

		pBuffer = ayItem.ay.GetAt(0);
		if( pBuffer == NULL || pBuffer->IsEmpty() )
			continue;

		pMarketInfo = m_pMainSend->m_WH.GetMarketPtr_JiaoTong(pBuffer->m_lpszBuffer,pPosition,this,1);
		if( pMarketInfo == NULL )
			continue;
	}

	return 1;
}

LRESULT CMainFrameSend::OnReceivedData(WPARAM wParam, LPARAM lParam)
{
	if( wParam < sizeof(CZMRequest) )
		return 0;

	CZMRequest* pRequest = (CZMRequest*)lParam;
	if(pRequest->m_nFlag != ZMCOMM_FLAG)
		return 0;

	if(pRequest->m_nType & ZM_REPLY)
		OnReceivedData((CZMReplyHead*)lParam);
	else
		OnReceivedData(pRequest);

	return 0;
}

void CMainFrameSend::OnReceivedData(CZMReplyHead* pReply)
{
	if(pReply->m_nFlag != ZMCOMM_FLAG)
		return;
	if(!(pReply->m_nType & ZM_REPLY))
		return;

	unsigned short nType = pReply->m_nType & ~ZM_REPLY;

	switch(nType)
	{	
	case ZM_KeepConnect			:		// ��ʼ��������
		{
			g_sysSysConfigSend.m_nTransmitData = 1;
			m_nCheckInitData = 0xffff;

			StartAll();		
		}
		break;
	case ZM_StopTransmitted		:		// ֹͣ��������
		{
			g_sysSysConfigSend.m_nTransmitData = 0;
			StopAll();

			char strText[128];
			sprintf(strText,"[��������] �����ɹ�.");
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);
		}
		break;
	case ZM_START				:		// ����ת��
		{
			HSMarketDataType cBourse = pReply->m_cSetCode;

			MarketInfo_send* pMarketInfo = MarketInfo_send::GetMarketByID(cBourse);
			if( pMarketInfo == NULL )
				return;

			pMarketInfo->m_bReceived = TRUE;

			char strText[128];
			sprintf(strText,"[%s] �յ�������������.",pMarketInfo->GetName());
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);
			StartZMThread(cBourse);

			//// by yls add 2007.02.27
			//pMarketInfo->SaveUpdateDate();

			// ��������ʼ������(ĿǰӦ���ڽ���)
			if( m_WH.IsRequest() )
			{
				printf("��������ʼ����������\r\n");
				g_sysSysConfigSend.m_nJiaoHangInitReq = 1;
			}

			break;
		}
	case ZM_ReceiveInitFinish:
		{
			HSMarketDataType cBourse = pReply->m_cSetCode;

			MarketInfo_send* pMarketInfo = MarketInfo_send::GetMarketByID(cBourse);
			if( pMarketInfo == NULL )
				return;

			// by yls add 2007.02.27
			pMarketInfo->SaveUpdateDate(pReply->m_nId);
		}
		break;
	case ZM_TestToReceive:
		{
			// �ͽ��ս���ʱ��
			m_tmTestBegin = CYlsTime::GetCurrentTime();
			m_nCheckByTime = 1;

			// ��������
			SendTestData(pReply);
		}
		break;
	}
}

void CMainFrameSend::OnReceivedData(CZMRequest* pRequest)
{
	if(pRequest->m_nFlag != ZMCOMM_FLAG)
		return;
	if(pRequest->m_nType & ZM_REPLY)
		return;

	unsigned short nType = pRequest->m_nType;

	//�ļ�����
	if( nType == ZM_FILESEND )
	{
		SendFileData(pRequest);
		return;
	}
	//��Ѷ�ļ�����
	else if( nType == ZM_ZX_FILESEND )
	{
		ZX_FILESEND(pRequest);
		return;
	}

	//	
	HSMarketDataType cBourse = pRequest->m_cSetCode;

	MarketInfo_send* pMarketInfo = MarketInfo_send::GetMarketByID(cBourse);
	if( nType != ZM_PROMPT && pMarketInfo == NULL )
		return;

	switch(nType)
	{
	case ZM_INITDATA:
		{
			char strText[128];

			if( !g_sysSysConfigSend.IsSupport(pMarketInfo->m_cBourse) )
			{
				sprintf(strText,"��֧��[ %s ]��ʼ������!",pMarketInfo->GetName());
				SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);
				return;
			}

			pMarketInfo->m_bInit = 0;
			pMarketInfo->m_bReceived = 0;

			sprintf(strText,"�յ�[ %s ]��ʼ������!",pMarketInfo->GetName());
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);

			// ����֧���Ļ�dbf
			if( pMarketInfo->m_cBourse == (WP_MARKET | WP_LME) && 
				g_sysSysConfigSend.m_bSupportWenHua )
			{
				Init_WenHua(pRequest,1,pMarketInfo,this);
			}

			// by yls 2007.02.27 replace
			pMarketInfo->InitData(pRequest,TRUE,this);
			// old reserve
			//pMarketInfo->InitData(pRequest,TRUE,this);

			if( !pMarketInfo->m_bInit )
			{
				sprintf(strText,"[ %s ]��ʼ��ʧ�� [CMainFrame::OnReceivedData]",pMarketInfo->GetName());
				SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);
			}
			break;
		}
	case ZM_START:
		{
			char strText[128];
			if(MakeMainMarket(cBourse) == SH_Bourse)
				strcpy(strText,"�յ������Ϻ�����ת������!");
			else if(MakeMainMarket(cBourse) == QH_Bourse)
				strcpy(strText,"�յ������ڻ�����ת������!");
			else if(MakeMainMarket(cBourse) == SZ_Bourse)
				strcpy(strText,"�յ�������������ת������!");
			else if(MakeMainMarket(cBourse) == TEST_MARKET)
				strcpy(strText,"�յ�������������ת������!");
			else
				break;

			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);
			StartZMThread(cBourse);
			break;
		}
	case ZM_STOP:
		{
			char strText[128];
			if(MakeMainMarket(cBourse) == SH_Bourse)
				strcpy(strText,"�յ���ֹ�Ϻ�����ת������!");
			else if(MakeMainMarket(cBourse) == QH_Bourse)
				strcpy(strText,"�յ���ֹ�ڻ�����ת������!");
			else if(MakeMainMarket(cBourse) == SZ_Bourse)
				strcpy(strText,"�յ���ֹ��������ת������!");
			else if(MakeMainMarket(cBourse) == TEST_MARKET)
				strcpy(strText,"�յ���ֹ��������ת������!");
			else
				break;

			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)strText);
			StopZMThread(cBourse);
			break;
		}
	case ZM_PROMPT:
		{
			ZMNewsData* pNews = (ZMNewsData*)pRequest;
			SendMessage(WM_MONITOR,ID_MESSAGE,(LPARAM)pNews->m_cText);
			break;
		}
	case ZM_FILESEND:
		{
			SendFileData(pRequest);
			break;
		}

	}
}

LRESULT CMainFrameSend::OnSessionStart(WPARAM wParam, LPARAM lParam)
{
	char strPrompt[128];
	sprintf(strPrompt,"����: %s:%i �ɹ���\r\n",m_strIP,m_nPort);
	Prompt(strPrompt);

	// 2007.09.06 add �ر�ǰһ����
	CYlsSession* pSendSession = m_pConnectSession;
	m_pConnectSession = NULL;

	if( pSendSession != NULL )
	{
		pSendSession->SetClose(1);
		pSendSession->CloseSocket();
	}

	m_pConnectSession = (CSendSession*)lParam;

	//int nIndex = m_wndStatusBar.CommandToIndex(ID_SESSION_STATUS);
	//m_wndStatusBar.SetPaneText(nIndex, "������·������");

	return 0;
}

void CMainFrameSend::FreeSession(CYlsSession* pSession)
{
	// 2007.09.06 add �����Ѿ����ӵı����
	// ԭ�ȵ�Ϊ m_pConnectSession = NULL;
	if(m_pConnectSession != NULL && pSession == m_pConnectSession )
		m_pConnectSession = NULL;

	//
	if( pSession )
	{
		pSession->SetClose(1);
		pSession->CloseSocket();
	}
}

LRESULT CMainFrameSend::OnSessionEnd(WPARAM, LPARAM lParam)
{
	return 0;
}

void CMainFrameSend::Init(CYlsIni* pYlsIniFile)
{	
	// ���
	if( g_sysSysConfigSend.IsSupport(FOREIGN_MARKET | WH_BASE_RATE) )
		m_WHMarketInfo1.Set(pYlsIniFile,"���-��������",FOREIGN_MARKET | WH_BASE_RATE,0,0,&CFunctionList_Send::Init_WH);    // ��������
	if( g_sysSysConfigSend.IsSupport(FOREIGN_MARKET | WH_ACROSS_RATE) )
		m_WHMarketInfo2.Set(pYlsIniFile,"���-�������",FOREIGN_MARKET | WH_ACROSS_RATE,0,0,&CFunctionList_Send::Init_WH);  // �������

#ifndef HS_SUPPORT_UNIX
	if( !g_sysSysConfigSend.nEntry_Support_TongXin )
	{
		//if( g_sysSysConfigSend.IsSupport(FOREIGN_MARKET | WH_FUTURES_RATE) )
			//m_WHMarketInfo3.Set(pYlsIniFile,"���-�ڻ�",FOREIGN_MARKET | WH_FUTURES_RATE,0,0,&CFunctionList_Send::Init_WH); // �ڻ�
	}	
#endif

	if( g_sysSysConfigSend.IsSupport(FOREIGN_MARKET | WH_BASE_RATE) )
		m_WH.Add(&m_WHMarketInfo1);
	if( g_sysSysConfigSend.IsSupport(FOREIGN_MARKET | WH_ACROSS_RATE) )
		m_WH.Add(&m_WHMarketInfo2);

#ifndef HS_SUPPORT_UNIX
	if( !g_sysSysConfigSend.nEntry_Support_TongXin )
	{
		//if( g_sysSysConfigSend.IsSupport(FOREIGN_MARKET | WH_FUTURES_RATE) )
		//	m_WH.Add(&m_WHMarketInfo3);
	}	
#endif	

}


BOOL CMainFrameSend::MakeSystemSetup()
{
	char* strTemp;
	//CWinApp* pApp = AfxGetApp();

	// �����ļ�ʹ��
	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Setting_File);
	YlsPrompt("MakeSystemSetup-�����ļ�",szPath);

	CYlsIni YlsIniFile;//(1);
	YlsIniFile.Open(szPath);

	//System
	yyyCount = YlsIniFile.GetProfileInt("System", "CompCount", 0);
	yyyDelay = YlsIniFile.GetProfileInt("System", Entry_RecordToRecord, 50);
	g_nSigleDelay = YlsIniFile.GetProfileInt("System", Entry_EveryRecord, 0);

#ifndef HS_SUPPORT_UNIX
	g_sysSysConfigSend.m_strIP = YlsIniFile.GetProfileString(Section_Internet, Entry_Communiction, "127.0.0.1");
#else
	strcpy(g_sysSysConfigSend.m_strIP,YlsIniFile.GetProfileString(Section_Internet, Entry_Communiction, "127.0.0.1"));
#endif
	g_sysSysConfigSend.m_nPort = YlsIniFile.GetProfileInt(Section_Internet, Entry_Port, 8000);

	// 
	g_sysSysConfigSend.nEntry_TCP			= YlsIniFile.GetProfileInt(Section_Internet,Entry_TCP,0);//"TCP_����������̸۹�����"
#ifndef HS_SUPPORT_UNIX
	g_sysSysConfigSend.strEntry_TCP_Addr	= YlsIniFile.GetProfileString(Section_Internet, Entry_TCP_Addr, "");//"TCP_��ַ"
#else
	strcpy(g_sysSysConfigSend.strEntry_TCP_Addr,YlsIniFile.GetProfileString(Section_Internet, Entry_TCP_Addr, ""));
#endif
	g_sysSysConfigSend.nEntry_TCP_Port		= YlsIniFile.GetProfileInt(Section_Internet,Entry_TCP_Port,0);//"TCP_�˿�"

	g_sysSysConfigSend.nEntry_TCP_wh		= YlsIniFile.GetProfileInt(Section_Internet,Entry_TCP_wh,0);//"TCP_����������̸۹�����"
#ifndef HS_SUPPORT_UNIX
	g_sysSysConfigSend.strEntry_TCP_Addr_wh	= YlsIniFile.GetProfileString(Section_Internet, Entry_TCP_Addr_wh, "");//"TCP_��ַ"
#else
	strcpy(g_sysSysConfigSend.strEntry_TCP_Addr_wh,YlsIniFile.GetProfileString(Section_Internet, Entry_TCP_Addr_wh, ""));
#endif
	g_sysSysConfigSend.nEntry_TCP_Port_wh	= YlsIniFile.GetProfileInt(Section_Internet,Entry_TCP_Port_wh,0);//"TCP_�˿�"


	// ͬʱ�г�֧��
	g_sysSysConfigSend.nEntry_Support_GP	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_GP,0);//"Support_����"
	g_sysSysConfigSend.nEntry_Support_QH	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_QH,0);//"Support_�ڻ�"
	
	g_sysSysConfigSend.nEntry_Support_WH	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_WH,0);//"Support_���"
	g_sysSysConfigSend.m_WH_BASE_RATE		= YlsIniFile.ReadInteger(Section_Internet,Entry_WH_BASE_RATE,   0);
	g_sysSysConfigSend.m_WH_ACROSS_RATE		= YlsIniFile.ReadInteger(Section_Internet,Entry_WH_ACROSS_RATE, 0);
	g_sysSysConfigSend.m_WH_FUTURES_RATE	= YlsIniFile.ReadInteger(Section_Internet,Entry_WH_FUTURES_RATE,0);


	g_sysSysConfigSend.nEntry_Support_HJ	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_HJ,0);//"Support_�ƽ�" added by Ben

	g_sysSysConfigSend.nEntry_Support_WP	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_WP,0);//"Support_����"
	g_sysSysConfigSend.nEntry_Support_GG	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_GG,0);//"Support_�۹�"
	g_sysSysConfigSend.nEntry_Support_ZX	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_ZX,0);//"Support_�۹�"

	g_sysSysConfigSend.nEntry_Support_MAXPacket = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_MAXPacket,50000);
	g_sysSysConfigSend.nEntry_Support_PacketMaxLIvingTime = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_PacketMaxLIvingTime,0);

	g_sysSysConfigSend.m_nTcpOverTime			 = YlsIniFile.GetProfileInt(Section_Internet,Entry_TCP_CONNECT,0);	
	g_sysSysConfigSend.m_dealGGDelayTime		 = YlsIniFile.GetProfileInt(Section_Internet,Entry_DealGGDelayTime,10);	
	g_sysSysConfigSend.m_Entry_AUTOUSERZIP		 = YlsIniFile.GetProfileInt(Section_Internet,Entry_AUTOUSERZIP,1);	
		
	g_sysSysConfigSend.nEntry_Support_BLOCKINDEX = YlsIniFile.GetProfileInt(Section_STOCK,Entry_Support_BLOCKINDEX,0);

	g_sysSysConfigSend.nEntry_Support_SunLinux = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_SunLinux,0);

	g_sysSysConfigSend.nEntry_Support_DataTransmit    = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_YF,0);
	g_sysSysConfigSend.nEntry_TransmitPort  = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_Transmit,6666);

	g_sysSysConfigSend.nEntry_Support_timelapse			 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_timelapse,0);
	g_sysSysConfigSend.nEntry_Support_timelapse_Delay    = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_timelapse_Delay,30);
	g_sysSysConfigSend.nEntry_Support_QHDataAccept		 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_QHDataAccept,0);
	g_sysSysConfigSend.nEntry_Support_SettingReportData	 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_SettingReportData,0);
	

	g_sysSysConfigSend.nEntry_Support_LEVEL2	   = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_LEVEL2,0);

	g_sysSysConfigSend.nEntry_Support_LEVEL2RebuildConnection = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_LEVEL2RebuildConnection,0);

	g_sysSysConfigSend.nEntry_Support_TZTHuangJinQiHuo = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_TZTHuangJinQiHuo,0);
	g_sysSysConfigSend.nEntry_Support_JinKaiXun = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_JinKaiXun,0);

	g_sysSysConfigSend.nEntry_Support_UDPTransmit     = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_UDPTransmit,0);
	g_sysSysConfigSend.nEntry_Support_UDPTransmit_Log = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_UDPTransmit_Log,0);

	//
	g_sysSysConfigSend.m_nLogEveryDate	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_Log,0);
	g_sysSysConfigSend.m_nWriteNowStick = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_NowStickLog,0);

	g_sysSysConfigSend.nEntry_Support_WriteLogFile = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_WriteToLogFile,0);

	g_sysSysConfigSend.m_nUsedEnglishName  = YlsIniFile.GetProfileInt(Section_Internet,Entry_UsedEnglishName,0); 

	g_sysSysConfigSend.nEntry_Support_Name = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_Name,1);
	
	// TCP����Դ
	g_sysSysConfigSend.nEntry_Support_PortToPort = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_PortToPort,0);
	g_sysSysConfigSend.nEntry_Support_JJT		 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_JJT,0);
	g_sysSysConfigSend.nEntry_Support_CAIHUAGANGGU = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_CAIHUAGANGGU,0);
	g_sysSysConfigSend.m_nGGStartPos = YlsIniFile.GetProfileInt(Section_Internet,Entry_GGStartPos,0);
	g_sysSysConfigSend.nEntry_Support_TongXin    = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_TongXin,0);
	g_sysSysConfigSend.nEntry_Support_LME		 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_LME,0);
	g_sysSysConfigSend.nEntry_Support_SHGold	 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_SHGold,0);
	g_sysSysConfigSend.nEntry_Support_LILV		 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_LILV,0);		
	g_sysSysConfigSend.nEntry_Support_ZYWL		 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_ZYWL,0);
	g_sysSysConfigSend.nEntry_Support_XHS		 = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_XHS,0);
	strTemp = YlsIniFile.GetProfileString(Section_Internet, Entry_Support_XHS_STR, "");
	if( strlen(strTemp) > 0 )
	{
		strncpy(g_sysSysConfigSend.m_strXHSChech,strTemp,sizeof(g_sysSysConfigSend.m_strXHSChech));
	}
	g_sysSysConfigSend.nEntry_Support_GuangXiTW	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_GuangXiTW,0);	

	g_sysSysConfigSend.nEntry_Support_Oil_XHS	     = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_Oil_XHS,0);
	g_sysSysConfigSend.nEntry_Support_CurrentOil_XHS = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_CurrentOil_XHS,0);

	g_sysSysConfigSend.nEntry_Support_YiTian = 1;// modified by Ben 20100517 YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_YiTian,0);

	//
	g_sysSysConfigSend.nEntry_Support_DBF	= YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_DBF,1);

	g_sysSysConfigSend.nEntry_Support_JSD	   = YlsIniFile.GetProfileInt(Section_QH,Entry_JSD_UDP,0);
	g_sysSysConfigSend.nEntry_Support_JSD_PORT = YlsIniFile.GetProfileInt(Section_QH,Entry_JSD_UDP_PORT,32021);

	//	g_sysSysConfigSend.nEntry_Support_Push_QH	= pApp->GetProfileInt(Section_Internet,Entry_Support_Push_QH,0) ;//"Support_����"
	//	g_sysSysConfigSend.nEntry_Support_Push_WH	= pApp->GetProfileInt(Section_Internet,Entry_Support_Push_WH,0) ;//"Support_�۹�"

	// ֧�ִ��ڹ�ҵ����
	g_sysSysConfigSend.m_nSupportDZGY	    = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_DZGY,0); 

	g_sysSysConfigSend.m_bCodeListSort      = YlsIniFile.GetProfileInt(Section_Internet,Entry_Support_AutoSort,1); 

	// �׸����Ÿ�·���ļ�
#ifndef HS_SUPPORT_UNIX
	g_sysSysConfigSend.m_strYFNewsPath      = YlsIniFile.GetProfileString(Section_Internet,Entry_YF_NewPaths,""); 
#else
	strcpy(g_sysSysConfigSend.m_strYFNewsPath,YlsIniFile.GetProfileString(Section_Internet,Entry_YF_NewPaths,""));
#endif
	// ʹ��UDP�����ڻ�����
	g_sysSysConfigSend.m_nHSUDP				= YlsIniFile.GetProfileInt(Section_HSUDP,Entry_QH_UDP,0);
	g_sysSysConfigSend.m_nHSUDP_Port		= YlsIniFile.GetProfileInt(Section_HSUDP,Entry_QH_UDP_PORT,2920);

	// ����DBF�ļ�
#ifndef HS_SUPPORT_UNIX
	g_sysSysConfigSend.m_strWPFile			= YlsIniFile.GetProfileString(Section_WP,Section_WP_DBF,"");
#else
	strcpy(g_sysSysConfigSend.m_strWPFile,YlsIniFile.GetProfileString(Section_WP,Section_WP_DBF,""));
#endif
	g_sysSysConfigSend.m_bSupportWenHua		= YlsIniFile.GetProfileInt(Section_WP,Section_WP_WenHuaDBF,0);

	//	g_sysSysConfigSend.m_strExchangePath    = pApp->GetProfileString(Section_Internet,Entry_Auto_ExchangePath,"") ; // ֧�ִ��ڹ�ҵ����

	//	g_sShareMarketFile.SetPathFile(g_sysSysConfigSend.m_strExchangePath);

	g_sysSysConfigSend.m_nZXSendSleep	  = YlsIniFile.GetProfileInt(Rec_Srv_ZXSend,Rec_Srv_ZXSend_Sleep,150);
	g_sysSysConfigSend.m_nZXSendDirSleep  = YlsIniFile.GetProfileInt(Rec_Srv_ZXSend,Rec_Srv_ZXSend_DirSleep,1000*60*5);
	g_sysSysConfigSend.m_nZXSendFileSleep = YlsIniFile.GetProfileInt(Rec_Srv_ZXSend,Rec_Srv_ZXSend_FileSleep,100);
	g_sysSysConfigSend.m_nZXDataLen		  = YlsIniFile.GetProfileInt(Rec_Srv_ZXSend,Rec_Srv_ZXSend_Size,2);

	if( g_sysSysConfigSend.m_nZXDataLen <= 0 )
		g_sysSysConfigSend.m_nZXDataLen = 2;
	g_sysSysConfigSend.m_nZXDataLen *= 1024;
	g_sysSysConfigSend.m_nZXDataLen *= 1024;

	g_sysSysConfigSend.m_nJiaoTongPort = YlsIniFile.GetProfileInt(Rec_Srv_ZXSend,Rec_Srv_JTYH_Port,9000); 

	g_sysSysConfigSend.Print();


	g_sysSysConfigSend.m_nInitTime_GP = YlsIniFile.GetProfileInt(Send_Rec_DataInit,InitTime_GP,30); 
	g_sysSysConfigSend.m_nInitTime_QH = YlsIniFile.GetProfileInt(Send_Rec_DataInit,InitTime_QH,30); 
	g_sysSysConfigSend.m_nInitTime_WH = YlsIniFile.GetProfileInt(Send_Rec_DataInit,InitTime_WH,1); 
	g_sysSysConfigSend.m_nInitTime_WP = YlsIniFile.GetProfileInt(Send_Rec_DataInit,InitTime_WP,1); 
	g_sysSysConfigSend.m_nInitTime_GG = YlsIniFile.GetProfileInt(Send_Rec_DataInit,InitTime_GG,50); 
	g_sysSysConfigSend.m_nInitTime_HJ = YlsIniFile.GetProfileInt(Send_Rec_DataInit,InitTime_HJ,30);  // added by Ben
	

	//
	g_sysSysConfigSend.m_nGGDealThreadCount = YlsIniFile.GetProfileInt(Section_GG,Send_GGDealThreadCount,1);

	g_sysSysConfigSend.m_nJHMaxError = YlsIniFile.GetProfileInt(Section_WH,Section_WH_MaxErrors,60);

	

	//
	int nPos;
	int nMinute = 0;
	int nHour = 0;

	// Ǭ¡���ݳ�ʼ��ʱ��
	/*strTemp = YlsIniFile.GetProfileString("System","Ǭ¡���ݳ�ʼ��ʱ��", "9:20");
	if( !(strlen(strTemp) <= 0) )
	{
		YlsIniFile.WriteProfileString("System","Ǭ¡���ݳ�ʼ��ʱ��", "9:20");
		YlsIniFile.Write();

		nHour = atoi(strTemp);

		CHqDataBuffer temp;
		temp.CopyStr(strTemp);
		nPos = temp.Find(":");
		if(nPos != -1)
		{
			nMinute = atoi(&temp.m_lpszBuffer[nPos+1]);
		}
		else
		{
			nMinute = 0;
		}
		yyyQlInitTime = nHour*60 + nMinute;
	}*/

	//
	Init(&YlsIniFile);


	// �Ϻ�֤ȯ������ļ�
	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_SH_DBF, "");
	strcpy(m_SHMarketInfo.m_strDbfName,strTemp);	

	// ��ծ��Ϣ��
	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_SH_GZLX_DBF, "");
	strcpy(g_sysSysConfigSend.m_dbfGZLX,strTemp);
	HSServerDataPath::MakeValidPath(g_sysSysConfigSend.m_dbfGZLX);

	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_SH_QuanZheng, "");
	strcpy(g_sysSysConfigSend.m_dbfQuanZheng,strTemp);
	HSServerDataPath::MakeValidPath(g_sysSysConfigSend.m_dbfQuanZheng);
	

	// ����֤ȯ������ļ�
	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_SZ_DBF, "");
	strcpy(m_SZMarketInfo.m_strDbfName,strTemp);

	// ��������������ļ�
	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_SZ_SANBAN_DBF, "");
	strcpy(m_SZMarketInfo.m_strSanBanDbfName,strTemp);			

	// �����Ϣdbf
	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_SZ_Sjsxxn_DBF, "");
	strcpy(m_SZMarketInfo.m_strSjsxxnName,strTemp);			

	// ���ָ���ļ�
	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_BLOCKINDEX_FILE, "");
	sprintf(g_sysSysConfigSend.m_strBlockIndexPath,"%s",strTemp);	

	// Ǭ¡·��
	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_QH_PATH_SH, "");
	strcpy(sz_MLPath_SH, strTemp);

	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_QH_PATH_SZ, "");
	strcpy(sz_MLPath_SZ, strTemp);

	// ETF�����ļ�·��
	strTemp = YlsIniFile.GetProfileString(Section_STOCK, Entry_ETF_FILE, "");
	strcpy(m_SZMarketInfo.m_strUserDbf,strTemp);	

	// �ڻ����ļ�
	strTemp = YlsIniFile.GetProfileString(Section_QH, Entry_QH_File, "");
	sprintf(m_QHMarketInfo.m_strDbfName,"%s",strTemp);

	// "�ڻ�UDP"
	m_QHMarketInfo.m_bUsedUDP = YlsIniFile.GetProfileInt(Section_QH,	Entry_QH_UDP, 0);	
	m_QHMarketInfo.m_nUDPPort = YlsIniFile.GetProfileInt(Section_QH,	Entry_QH_UDP_PORT, 2900);
	g_sysSysConfigSend.m_nUDPWriteLog = YlsIniFile.GetProfileInt(Section_QH, Entry_UDPWriteLog, 0);	

	// ���ӽ��е�ַ�Ͷ˿�
	strcpy(g_sysSysConfigSend.m_strIPJH,YlsIniFile.GetProfileString(Section_Internet, Entry_Communiction_JH, "182.247.70.43"));
	g_sysSysConfigSend.m_nPortJH = YlsIniFile.GetProfileInt(Section_Internet, Entry_Port_JH, 15000);

	g_sysSysConfigSend.m_nOpenMapping_Synchronization = YlsIniFile.GetProfileInt(Section_STOCK, OpenMapping_Synchronization, 0);
	g_sysSysConfigSend.m_nOpenMapping_Independence = YlsIniFile.GetProfileInt(Section_STOCK, OpenMapping_Independence, 0);
	g_sysSysConfigSend.m_nUsedMappingFile = YlsIniFile.GetProfileInt(Section_STOCK, UsedMappingFile, 1);

	// option
	g_sysSysConfigSend.m_Send_Option_ReadClose = YlsIniFile.GetProfileInt(Send_Option, Send_Option_ReadClose, 0);

	//char szPath[_MAX_PATH];
	CHSFilePath::GetPath(szPath,CHSFilePath::CodeFile);

	// ֧�������Ʊ����
	if( g_sysSysConfigSend.nEntry_Support_YiTian )
	{
		m_GP.SetCodeFile(szPath);
	}

	//#ifdef SUPPORT_UDP_STOCK
	m_GPUDP.SetCodeFile(szPath);
	//#endif

	// �ڻ�
	m_QH.SetCodeFile(szPath);

	// ���UDP/TCP
	m_WH.SetCodeFile(szPath);

	// ����
	m_WP.SetCodeFile(szPath);

	// �۹�
	m_GG.SetCodeFile(szPath);

	// �ƽ� added by Ben
	m_HJ.SetCodeFile(szPath);
	//										   
	strTemp = YlsIniFile.GetProfileString("System", "�»����������·��", "");
	if (strlen(strTemp) <= 0)
	{
		//return FALSE;
	}
	sprintf(m_TestMarketInfo.m_strDbfName,"%s",strTemp);


	// ������Ϣ��ʼ��
	WORD key = 0;
	MarketInfo_send* value = NULL;
	POSITION  pos;
	for( pos = MarketInfo_send::g_mapMarketSend.GetStartPosition(); pos != NULL; )
	{
		MarketInfo_send::g_mapMarketSend.GetNextAssoc( pos, key, (void*&)value );
		if( value == NULL )
			continue;

		if( !g_sysSysConfigSend.IsSupport(value->m_cBourse) )
			continue;

		value->BulidStockInfo(this);
	}

	// ��ʼ����������
	InitRemain();

	return TRUE;
}

int CMainFrameSend::SendTestData(CZMReplyHead* pReply)
{
	CZMRequest head;
	memset(&head,0,sizeof(head));
	head.m_nFlag = ZMCOMM_FLAG;
	head.m_nType = ZM_TestToReceive | ZM_REPLY;

	this->Send(&head,sizeof(head));

	CZMRequest* pQuest = (CZMRequest*)pReply;

	CYlsTime tm = CYlsTime(pQuest->m_nId);

	//
	char szPrompt[256];
	sprintf(szPrompt,"���һ���յ����ն�����ʱ�� -> %04d/%02d/%02d - %02d:%02d:%02d",
		tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	SendMessage(WM_MONITOR,ID_MAINCONNECT,(LPARAM)szPrompt);

	return 1;
}

void CMainFrameSend::Check(CYlsTime& tmNow,short nTime,int nForce /*= 0*/)
{
	// ����������
	if( !g_sysSysConfigSend.IsTransmit() )
	{
		printf("��������.\r\n");
		return;
	}

	//printf("Check: %i,%i\r\n",m_nCheckInitData,nForce);

	// �Զ�����Ƿ�Ҫ���³�ʼ��
	m_nCheckInitData++;
	if( m_nCheckInitData > 60 )
	{
		m_nCheckInitData = 0;

		WORD key = 0;
		MarketInfo_send* value = NULL;
		POSITION  pos;
		for( pos = MarketInfo_send::g_mapMarketSend.GetStartPosition(); pos != NULL; )
		{
			MarketInfo_send::g_mapMarketSend.GetNextAssoc( pos, key, (void*&)value );
			if( value )
			{
				if( !g_sysSysConfigSend.IsSupport(value->m_cBourse) )
					continue;

				value->ReSetInit(nTime,this,this->m_lLastError);
			}
		}
	}

	// ǿ������
	if( nForce )
	{
		printf("ǿ������-begin\r\n");

		if( g_sysSysConfigSend.nEntry_Support_GP )
		{
			m_GP.AllAutoInitData(this,tmNow,0,nForce);
		}

		// �ڻ�
		if( g_sysSysConfigSend.nEntry_Support_QH )
		{
			m_QH.AllAutoInitData(this,tmNow,0,nForce);
		}

		// ���
		if( g_sysSysConfigSend.nEntry_Support_WH )
		{
			m_WH.AllAutoInitData(this,tmNow,0,nForce);
		}

		// ����
		if( g_sysSysConfigSend.nEntry_Support_WP )
		{
			m_WP.AllAutoInitData(this,tmNow,0,nForce);
		}

		// �۹�
		if( g_sysSysConfigSend.nEntry_Support_GG )
		{
			m_GG.AllAutoInitData(this,tmNow,0,nForce);
		}

		// �ƽ� added by Ben
		if( g_sysSysConfigSend.nEntry_Support_HJ )
		{
			m_HJ.AllAutoInitData(this,tmNow,0,nForce);
		}

		printf("ǿ������-end\r\n");

		return;
	}

	// �Զ���ʼ��
	// ��Ʊ
	if( m_nInitTime == 2 && g_sysSysConfigSend.nEntry_Support_GP )
	{
		m_GP.AllAutoInitData(this,tmNow,0);
	}

	// �ڻ�
	if( m_nInitTime == 4 && g_sysSysConfigSend.nEntry_Support_QH )
	{
		m_QH.AllAutoInitData(this,tmNow,0);
	}

	// ���
	if( m_nInitTime == 6 &&  g_sysSysConfigSend.nEntry_Support_WH )
	{
		m_WH.AllAutoInitData(this,tmNow,0);
	}

	// ����
	if( m_nInitTime == 8 && g_sysSysConfigSend.nEntry_Support_WP )
	{
		m_WP.AllAutoInitData(this,tmNow,0);
	}

	// �۹�
	if( m_nInitTime == 10 && g_sysSysConfigSend.nEntry_Support_GG )
	{
		m_GG.AllAutoInitData(this,tmNow,0);
	}

	// �ƽ� added by Ben
	if( m_nInitTime == 12 && g_sysSysConfigSend.nEntry_Support_HJ )
	{
		m_HJ.AllAutoInitData(this,tmNow,0);
	}

	m_nInitTime++;
	if( m_nInitTime > 12 )
		m_nInitTime = 0;

}

LRESULT CMainFrameSend::OnReceivedData_JiaoTong(WPARAM wParam, LPARAM lParam)
{
	if( !g_sysSysConfigSend.nEntry_Support_WH )
		return 0;

	if( lParam == NULL || wParam <= 0 )
		return 0;

	if( wParam <= sizeof(JiaoTong_HQData) )
	{
		printf("wParam <= sizeof(JiaoTong_HQData):%s,%i\r\n",(char*)lParam,wParam);
		YlsPrompt("��Ч����,���� < sizeof(JiaoTong_HQData)",NULL);
		return 0;
	}

	//printf("CMainFrameSend::OnReceivedData_JiaoTong:\r\n%s,%i\r\n",(char*)lParam,wParam);

	JiaoTong_HQData* pJiaoTong_HQData = (JiaoTong_HQData*)lParam;
	if( !pJiaoTong_HQData->IsHQ() )
	{
		printf("!pJiaoTong_HQData->IsHQ():%s,%i\r\n",pJiaoTong_HQData->query_type,wParam);

		// 2007.09.03 remove
		//YlsPrompt("��Ч����,!pJiaoTong_HQData->IsHQ()",NULL);
		return 0;
	}

	//�������ݼ��ԡ�#���ָ���������ڸ�Ԫ�ؼ��ԡ�|���ָ������Ϊ��@@@@��
	//2#USDJPY|102.7600|102.9600|1|200501080245200#USDCAD|1.2306|1.2336|1|20050108 0245200#@@@@

	wParam -= (sizeof(JiaoTong_HQData) - sizeof(char));
	CHqDataBuffer curBuffer;
	curBuffer.CopyStr(pJiaoTong_HQData->m_cData,wParam);
	if( !curBuffer.IsValid() )
	{
		YlsPrompt("��Ч����,curBuffer.IsValid()",NULL);
		return 0;
	}

	//printf("�յ�ʵʱ����:\r\n���ݣ�%s\r\n,���ȣ�%i\r\n",
	//	curBuffer.m_lpszBuffer,wParam);

	CHqDataBufferArray ay;
	CHqDataBuffer* pBuffer;
	int nItem;
	int nCount = AnalyzeStr(curBuffer.m_lpszBuffer,"#",ay.ay);

	/*
	sprintf(szPrompt,"%i\r\n",nCount);
	printf(szPrompt);*/

	int nRet = 0;
	//char szPrompt[256];

	for( int i = 0; i < nCount; i++ )
	{
		CHqDataBuffer szPrompt;

		pBuffer = ay.ay.GetAt(i);
		if( pBuffer == NULL || pBuffer->IsEmpty() )
			continue;

		//
		CHqDataBufferArray item;
		nItem = AnalyzeStr(pBuffer->m_lpszBuffer,"|",item.ay);

#ifdef JH_Used_MIDPrice
		if( nItem < 4 )
		{
			/*szPrompt.AddStr("��Ч������");
			szPrompt.AddStr(pBuffer->m_lpszBuffer);
			szPrompt.AddStr("\r\n");
			printf(szPrompt.m_lpszBuffer);

			YlsPrompt(szPrompt.m_lpszBuffer,NULL);*/
			continue;
		}
#else
		if( nItem < 5 )
			continue;	
#endif

		if( Update_JiaoTong(item) )
		{
			nRet++;
		}
		else
		{
			/*szPrompt.AddStr("��Ч(���ܴ���)��");
			szPrompt.AddStr(pBuffer->m_lpszBuffer);
			szPrompt.AddStr("\r\n");
			printf(szPrompt.m_lpszBuffer);

			YlsPrompt(szPrompt.m_lpszBuffer,NULL);*/
		}
	}

	return nRet;
}

short CMainFrameSend::GetPriceUnit(HSMarketDataType cStockType)
{
	StockTypeInfo* pstiStock;
	int nTotal = 4;

	MarketInfo_send* pMarketInfo = MarketInfo_send::GetMarketByID(cStockType);
	if( pMarketInfo == NULL )
		return 1000;

	pstiStock =	pMarketInfo->m_stiStock;
	nTotal    = pMarketInfo->m_nTypeTotal;

	int nIndex = MakeSubMarketPos(cStockType);
	if((nIndex < 0) || (nIndex >= nTotal))
		nIndex = 0;

	return pstiStock[nIndex].m_lSendUnit;
	//return pstiStock[nIndex].m_stType.m_nPriceUnit;
}

LRESULT CMainFrameSend::Update_JiaoTong(CHqDataBufferArray& item)
{
	CHSStockPosition_send* pPosition = NULL;

	CHqDataBuffer* pBuffer_name = item.ay.GetAt(0);   // ����
	if( pBuffer_name == NULL || !pBuffer_name->IsValid() )
	{
		//printf("��Ч���ƣ�\r\n");
		YlsPrompt("��Ч���ƣ�",NULL);
		return 0;
	}

	MarketInfo_send* pMarketInfo;
	if( m_pMainSend )  // ��ʼ������
	{
		pMarketInfo = 
			m_pMainSend->m_WH.GetMarketPtr_JiaoTong(pBuffer_name->m_lpszBuffer,pPosition,this,FALSE,FALSE);
	}
	else
	{
		pMarketInfo = m_WH.GetMarketPtr_JiaoTong(pBuffer_name->m_lpszBuffer,pPosition,this,FALSE,FALSE);
	}


	if( pMarketInfo == NULL )
	{
		static int nErrorBeginTime = 0;  // ����������
		nErrorBeginTime++;

		if( nErrorBeginTime > g_sysSysConfigSend.m_nJHMaxError )
		{
			char szError[1024];
			sprintf(szError,"[%s,%i,%i] û���ҵ��г�,���������ָ�.",
				pBuffer_name->m_lpszBuffer,m_lLastError,m_WH.m_ay.GetSize());
			YlsPrompt(szError,NULL);	

			// ȫ����Ϣ״̬
			CHqDataBuffer buffer;
			m_WH.GetMarketInfo(buffer);
			if( buffer.IsValid() )
			{
				WriteError(buffer.m_lpszBuffer,buffer.m_cbBuffer,NULL);
			}

			exit(0);
			//system(YlsExe_send); // ������������
		}

		//
		char szError[1024];
		sprintf(szError,"[%s,%i,%i] û���ҵ��г�.\r\n",pBuffer_name->m_lpszBuffer,m_lLastError,m_WH.m_ay.GetSize());
		YlsPrompt(szError,NULL);	

		// ȫ����Ϣ״̬
		CHqDataBuffer buffer;
		m_WH.GetMarketInfo(buffer);
		if( buffer.IsValid() )
		{
			WriteError(buffer.m_lpszBuffer,buffer.m_cbBuffer,NULL);
		}

		return 0;
	}

	if( !pMarketInfo->IsInit() )
	{
		static int nErrorBeginTime = 0;  // ����������
		nErrorBeginTime++;

		if( nErrorBeginTime > g_sysSysConfigSend.m_nJHMaxError )
		{
			char szError[1024];
			sprintf(szError,"[%s,%i,%i] û�г�ʼ��,���������ָ�.",
				pBuffer_name->m_lpszBuffer,m_lLastError,m_WH.m_ay.GetSize());
			YlsPrompt(szError,NULL);

			// ȫ����Ϣ״̬
			CHqDataBuffer buffer;
			m_WH.GetMarketInfo(buffer);
			if( buffer.IsValid() )
			{
				WriteError(buffer.m_lpszBuffer,buffer.m_cbBuffer,NULL);
			}

			exit(0);
			//system(YlsExe_send); // ������������
		}

		// 2007.08.22 add
		pMarketInfo->m_nMaxTime = 0;
		m_nForceInit = 1;

		//
		char szError[1024];
		sprintf(szError,"[%s,%i,%i] û�г�ʼ��.\r\n",pBuffer_name->m_lpszBuffer,m_lLastError,m_WH.m_ay.GetSize());
		YlsPrompt(szError,NULL);

		// ȫ����Ϣ״̬
		CHqDataBuffer buffer;
		m_WH.GetMarketInfo(buffer);
		if( buffer.IsValid() )
		{
			WriteError(buffer.m_lpszBuffer,buffer.m_cbBuffer,NULL);
		}

		return 0;
	}

	int lHeadLen = sizeof(ZMCompressedNowData);
	int lDataLen = sizeof(ZMStockNowData);

	CHqDataBuffer buffer;
	if( !buffer.Alloc(lHeadLen + lDataLen) )
	{
		return 0;
	}

	ZMCompressedNowData* pNowData = (ZMCompressedNowData*)buffer.m_lpszBuffer;

	pNowData->m_dhHead.m_nFlag    = (unsigned short)0xefff;
	pNowData->m_dhHead.m_nType    = ZM_REPLY | ZM_PRICES;
	pNowData->m_dhHead.m_nId      = 0;
	pNowData->m_dhHead.m_cSetCode = pMarketInfo->m_cBourse;

	float* lValue = pNowData->m_lData;
	short nUnit;
	int	  nIndex;

	if( pPosition != NULL && pPosition->m_lPosIndex != NULL )
	{
		memcpy(&pNowData->m_ciStockCode,&pPosition->m_lPosIndex->m_ciInfo,
			sizeof(CodeInfo));

		nUnit = GetPriceUnit(pNowData->m_ciStockCode.m_cCodeType);
	}
	else
	{
		//printf("CMainFrameSend::Update_JiaoTong:û���ҵ����룡\r\n");
		YlsPrompt("CMainFrameSend::Update_JiaoTong:û���ҵ����룡",NULL);
		return 0;
	}

	/*char szPrompt[256];
	printf(pBuffer_name->m_lpszBuffer);
	sprintf(szPrompt,"��λ��%i\r\n",nUnit);
	printf(szPrompt);*/

	// λ��
	nIndex = 0;
	pNowData->m_lChangedData  = 0;
	pNowData->m_lChangedData2 = 0;

	CHqDataBuffer* pBuffer_buy  = item.ay.GetAt(1);		 // �����

#ifdef JH_Used_MIDPrice

	CHqDataBuffer* pBuffer_mark = item.ay.GetAt(2);		 // ��Ч��� 0 - ��Ч 1-��Ч
														 // ���Ƽ۵���Ч��־(status)Ϊ��Ч"0"��
														 // ��ʾ���Ƽ۲����� ,�������Ƽۿͻ�����ʾ
														 // (��"--"������ǲ�����)
	CHqDataBuffer* pBuffer_time = item.ay.GetAt(3);		 // ����Դʱ�� yyyymmddhhmmss 

	if( pBuffer_buy  == NULL || !pBuffer_buy->IsValid()  ||
		pBuffer_mark == NULL || !pBuffer_mark->IsValid() ||
		pBuffer_time == NULL || !pBuffer_time->IsValid() )
	{
		YlsPrompt("�ӿ�������Ŀ��Ч��",NULL);
		return 0;
	}

	float fNewsPrice = (atof(pBuffer_buy->m_lpszBuffer) + 0.00001) * nUnit;
		//GetLongValue(pBuffer_buy->m_lpszBuffer,pBuffer_buy->m_cbBuffer,nUnit);
	float fSellPrice = 0;
	float fBuyPrice  = 0;

	/*if( !pBuffer_name->CompareNoCase("EURUSD") )
	{
		printf("%s,%f,%s\r\n",pBuffer_name->m_lpszBuffer,fNewsPrice,pBuffer_buy->m_lpszBuffer);
	}*/

#else

	CHqDataBuffer* pBuffer_sell = item.ay.GetAt(2);		 // ������
	CHqDataBuffer* pBuffer_mark = item.ay.GetAt(3);		 // ��Ч��� 0 - ��Ч 1-��Ч
	// ���Ƽ۵���Ч��־(status)Ϊ��Ч"0"��
	// ��ʾ���Ƽ۲����� ,�������Ƽۿͻ�����ʾ
	// (��"--"������ǲ�����)
	CHqDataBuffer* pBuffer_time = item.ay.GetAt(4);		 // ����Դʱ�� yyyymmddhhmmss 

	if( pBuffer_buy  == NULL || !pBuffer_buy->IsValid()  ||
		pBuffer_sell == NULL || !pBuffer_sell->IsValid() ||
		pBuffer_mark == NULL || !pBuffer_mark->IsValid() ||
		pBuffer_time == NULL || !pBuffer_time->IsValid() )
	{
		YlsPrompt("��Ч���ݻ�ȡ��",NULL);
		return 0;
	}

	float fBuyPrice  = GetLongValue(pBuffer_buy->m_lpszBuffer,pBuffer_buy->m_cbBuffer,nUnit);
	float fSellPrice = GetLongValue(pBuffer_sell->m_lpszBuffer,pBuffer_sell->m_cbBuffer,nUnit);
	float fNewsPrice = (fBuyPrice + fSellPrice)/2;

#endif

	// ���¼�
	if(fNewsPrice != 0)
	{
		lValue[nIndex] = (fNewsPrice/**nUnit*/);
		nIndex++;
		pNowData->m_lChangedData |= ZD_NewPrice;
	}

	// ����1
	if(fBuyPrice != 0)
	{
		lValue[nIndex] = (fBuyPrice/**nUnit*/);
		nIndex++;
		pNowData->m_lChangedData |= ZD_BuyPrice1;
	}

	// ����1
	if(fSellPrice != 0)
	{
		lValue[nIndex] = (fSellPrice/**nUnit*/);
		nIndex++;
		pNowData->m_lChangedData |= ZD_SellPrice1;
	}

	// ����״̬
	pBuffer_mark->Trim();
	if( pBuffer_mark->IsValid() )
	{
		/*printf(pBuffer_mark->m_lpszBuffer);
		printf("\r\n");*/

		lValue[nIndex] = atol(pBuffer_mark->m_lpszBuffer);
		/*if( lValue[nIndex] == 0 )
		{
		YlsPrompt("��Ʒ������Ч��",NULL);
		return 0;
		}*/

		nIndex++; // SRV_SETTING
		pNowData->m_lChangedData |= ZD_SellPrice2;
	}
	else // ��Ч���
	{
		YlsPrompt("��Ч���,����Ϊ�գ�",NULL);
	}

	// 
	pNowData->m_dhHead.m_cSetCode = pMarketInfo->m_cBourse;

	pNowData->m_nSize = nIndex;

	if( nIndex > 0 ) 
	{
		if( m_pMainSend )
			m_pMainSend->Send(pNowData,lHeadLen + sizeof(long)*(nIndex-1));
		else
			Send(pNowData,lHeadLen + sizeof(long)*(nIndex-1));		
	}

	return (nIndex > 0);
}

void CMainFrameSend::StopAll()
{
	WORD key = 0;
	MarketInfo_send* value = NULL;
	POSITION  pos;
	for( pos = MarketInfo_send::g_mapMarketSend.GetStartPosition(); pos != NULL; )
	{
		MarketInfo_send::g_mapMarketSend.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			StopZMThread(value->m_cBourse);
		}
	}
}

void CMainFrameSend::StartAll()
{
	WORD key = 0;
	MarketInfo_send* value = NULL;
	POSITION  pos;
	for( pos = MarketInfo_send::g_mapMarketSend.GetStartPosition(); pos != NULL; )
	{
		MarketInfo_send::g_mapMarketSend.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			value->m_bInit = 0;
			value->m_bReceived = 0;
		}
	}
}

