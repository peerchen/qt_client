/*******************************************************************************
* Copyright (c)2003, ��������ϵͳ���޹�˾
* All rights reserved.
*
* �ļ����ƣ�*.h
* �ļ���ʶ��
* ժ    Ҫ��
*
* ��ǰ�汾��YLink1.2
* ��    �ߣ�YLink����
* ������ڣ�2005
*
* ��    ע��
*
* �޸ļ�¼��
*
*******************************************************************************/




#ifndef _ServerStructEx
#define _ServerStructEx

#include "stdafx.h"

#include "hs_disk_h.h"
#include "ylstypedptrmap.h"

#pragma	pack(1)

class CServerMarketInfo;

#if 0

//������
struct YlsDaDanData
{
	CodeInfo			m_pCode;
	StockNowDataOld		m_nowData;	
	StockOtherData		m_othData;
};

struct YlsDaDanReqData
{
	short    m_nClassBegin; // �󵥼���
	short    m_nClassEnd;

	long     m_nDateBegin;  // ����
	long     m_nDateEnd;

	long     m_lReqMask;    // ��ǰҪ���ص��ֶΰ���
	long     m_lReqCount;   // ��ǰҪ���صĸ���  0Ϊ����

	short    m_nSize;       // �������볤��
	CodeInfo m_pCode[1];
};

#endif


#define RealData ShareRealTimeData

class CServerMarketInfo;

// �ڲ���������
struct StockInfoIn : public StockInfoPosition	
{
	StockInfoIn()
	{
		memset(this,0,sizeof(StockInfoIn));
	}

	int GetTablePos(CServerMarketInfo* pCServerMarketInfo = NULL);
	int GetTrendPos(CServerMarketInfo* pCServerMarketInfo = NULL);
	int GetTickPos(CServerMarketInfo* pCServerMarketInfo = NULL);
	int GetFenShiPos(CServerMarketInfo* pCServerMarketInfo = NULL);

	void Set(int nPos,CodeInfo* pCode,LevelStatic* pEveryCalculateData = NULL)
	{
		Type = pCode->m_cCodeType;						// ��0x1101
		strncpy(Code,pCode->m_cCode,sizeof(Code));		// ����

		PosInKind   = nPos;		// �����е�ƫ��
		PosInBourse = nPos;	    // �г��е�ƫ��
		PosInTable  = nPos;		// ������е�ƫ��
		PosInTrend  = nPos;		// ��ʱ�е�ƫ��
		PosInTick   = nPos;		// �ֱ��е�ƫ��
		TrendOffset = nPos;	    // ��ʱƫ����

		// ���������
		if( pEveryCalculateData )
		{
			memcpy(&m_StockExtend.m_sStatic,pEveryCalculateData,sizeof(m_StockExtend.m_sStatic));
		}
	}
};


// ��ʱ��������
struct StockDetailedMinuteDataEx
{
	long	m_nTotalHold;	   //�ڻ��ܳ�
	short	m_nReserved[2];    //����
	long	m_lOutside;        //���̳ɽ���
};

//���̷�ʱ����
struct IndexDetailedMinuteDataEx
{
	short	m_nRiseCount;       //���Ǽ���
	short	m_nFallCount;       //�µ�����
	short	m_nLead;            //����ָ��
	short	m_nRiseTrend;       //��������
	short	m_nFallTrend;       //�µ�����
	short	m_lADL;             //ADLָ��
};

//���ɷ�ʱ
struct StockHistoryDataEx
{
	long	m_lNewPrice;		//���¼�
	long	m_lTotal;           /*�ɽ��� ���ڹ�Ʊ(��λ:��)
								  ����ָ��(��λ:�ٹ�)*/
	float	m_fAvgPrice;	    /*�ɽ����  ���ڹ�Ʊ(��λ:Ԫ) ,�ڻ�Ϊ�ֲ���
								����ָ��(��λ:��Ԫ)*/
	long	m_lBuyCount;        //ί����
	long	m_lSellCount;       //ί����
	union
	{
		StockDetailedMinuteDataEx	m_dmStock;	//��������
		IndexDetailedMinuteDataEx	m_dmIndex;	//��������
	};
};

#ifdef Support_Used_Old_HistoryTendHead

// ��ʷ��ʱͷ����
struct DiskStockHistoryTendHead 
{
	long				m_lDate;		// ����
	long				m_lPrevClose;	// ����

	ShareRealTimeData   m_stStockData;

	short			    m_nSize;		//  ÿ�������ܸ���
	//short				m_nAlignment;   //  ������
};

#else

#define DiskStockHistoryTendHead StockHistoryTrendHead

#endif

struct AnyReportDataEx : public AnyReportData
{
	float m_fValue;	//��������
};

//#define DiskStockTraceData StockTraceData 
//#define DiskStockTrace	   StockTrace 



//#define _Support_LargeTick

#ifdef _Support_LargeTick

#define LargeTickCounts (1000)

// ����������
struct StockMMP
{
	ShareRealTimeData m_stNow;
};

struct StockTraceData
{
	StockTick   m_sTick;

	union
	{
		StockMMP  m_sMMP;
		StockMMP  m_sStockMMP;     // ����������
	};
};

struct StockTrace
{
	long	m_nTotal;        //ʵ������
	long	m_lNextPoint;    //-1:no next else:next block file point
	StockTraceData	m_stData[1000];
};

#else

#define LargeTickCounts (500)

struct StockMMP
{
	union
	{
		float m_fAvgPrice;
		float m_lChiCangLiang;
	};

#ifdef Support_MaiMai

	long				m_lBuyPrice1;			// ��һ��
	unsigned long		m_lBuyCount1;			// ��һ��
	long				m_lBuyPrice2;			// �����
	unsigned long		m_lBuyCount2;			// �����
	long				m_lBuyPrice3;			// ������
	unsigned long		m_lBuyCount3;			// ������
	long				m_lBuyPrice4;			// ���ļ�
	unsigned long		m_lBuyCount4;			// ������
	long				m_lBuyPrice5;			// �����
	unsigned long		m_lBuyCount5;			// ������

	long				m_lSellPrice1;			// ��һ��
	unsigned long		m_lSellCount1;			// ��һ��
	long				m_lSellPrice2;			// ������
	unsigned long		m_lSellCount2;			// ������
	long				m_lSellPrice3;			// ������
	unsigned long		m_lSellCount3;			// ������
	long				m_lSellPrice4;			// ���ļ�
	unsigned long		m_lSellCount4;			// ������
	long				m_lSellPrice5;			// �����
	unsigned long		m_lSellCount5;			// ������	
#endif

};

struct StockTraceData
{
	StockTick   m_sTick;

	union
	{
		StockMMP  m_sMMP;
		StockMMP  m_sStockMMP;     // ����������
	};
};

struct StockTrace
{
	long	m_nTotal;        //ʵ������
	long	m_lNextPoint;    //-1:no next else:next block file point
	StockTraceData	m_stData[LargeTickCounts];//00];
};

#endif

#define DiskStockTraceData	StockTraceData
#define DiskStockTrace StockTrace

//// ����������
//struct StockMMP
//{
//	ShareRealTimeData m_stNow;
//};
//
//struct DiskStockTraceData
//{
//	StockTick m_sTick;
//	StockMMP  m_sMMP;
//};
//
////���ɷֱ�
//struct DiskStockTrace
//{
//	long	m_nTotal;					 //ʵ������
//	long	m_lNextPoint;				//-1:no next else:next block file point
//	DiskStockTraceData	m_stData[1000];		//���ɷֱ�
//};


// gifͼƬ����
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#define GIF_Fun_Begin 0

#define GIF_Fenshi				(GIF_Fun_Begin + 401)	//��ʱ����
#define GIF_Day					(GIF_Fun_Begin + 402)	//����
#define GIF_Lead				(GIF_Fun_Begin + 405)	//��������
#define GIF_Report				(GIF_Fun_Begin + 407)	//���۷���
#define GIF_CurPrice			(GIF_Fun_Begin + 408)	//��ǰ��������

// 1.5 dfx����
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

#define DFX_Fun_Begin 0

#define DFX_File				(DFX_Fun_Begin + 1)	//�����ļ�
#define DFX_CodeList			(DFX_Fun_Begin + 2)	//��������
#define DFX_Lonhis_Stock		(DFX_Fun_Begin + 3)	//����Lonhis��ͨ����
#define DFX_Lonhis_Index		(DFX_Fun_Begin + 4)	//����Lonhisָ������
#define DFX_LonInfo				(DFX_Fun_Begin + 5)	//����LonInfo
#define DFX_LonInfo_Simple		(DFX_Fun_Begin + 6)	//����LonInfo ����
#define DFX_LonNow_Single		(DFX_Fun_Begin + 7)	//����LonNow (1ֻ)
#define DFX_LonNow_Multi		(DFX_Fun_Begin + 8)	//����LonNow (��ֻ)      
#define DFX_LonTran				(DFX_Fun_Begin + 9)	//����LonTran  
#define DFX_LonTran_Param		(DFX_Fun_Begin + 10) //	����LonTran (�����Ȳ���)
#define DFX_LonDay				(DFX_Fun_Begin + 11) //	����LonDay
#define DFX_LonNow_5Day			(DFX_Fun_Begin + 12) // ����LonNow (��ֻ,��5�վ���)    
#define DFX_Stop_Down			(DFX_Fun_Begin + 22) //	ֹͣ��������
#define DFX_LonHis_Zip			(DFX_Fun_Begin + 23) //	�����������ѹ����ʽ��LonHis   
#define DFX_Sort				(DFX_Fun_Begin + 24) //	����������ۺ�����      
#define DFX_Downdata			(DFX_Fun_Begin + 200)//	������������
#define DFX_Login				(DFX_Fun_Begin + 1001)//	�����¼ login
#define DFX_Logout				(DFX_Fun_Begin + 1010)//	�������� logout(δ��)
#define DFX_AutoPush			(DFX_Fun_Begin + 9999)//	��������
#define DFX_CheckStock			(DFX_Fun_Begin + 55)  //	
#define DFX_FinanceDate			(DFX_Fun_Begin + 41)  // ������������DealFinanceDate
#define DFX_zslonnow			(DFX_Fun_Begin + 47)  // ָ��lonnow
#define DFX_real_loninfo		(DFX_Fun_Begin + 45)  // ʵʱloninfo


#define	USEFLOAT	1
#define		SHA		0x10
#define		SZN		0x20

#define		SHORTMSG_Dfx		"SHORTMSG.TXT"
#define		START_Dfx			"START.TXT"
#define		INDIVIDUATION_Dfx	"INDIVIDUATION.INI"
#define		FINANCE_Dfx			"FINANCE.DAT"
#define		HSINFO_Dfx			"HSINFO.INI"

#define		shmsg2_txt_Dfx		"SHMSG2.TXT" //1=�Ϻ�֤������Ϣ|(ml30)\lond\dat\shmsg2.txt|71|��֤��Ϣ
#define		szmsg1_txt_Dfx		"SZMSG1.TXT" //2=����֤������Ϣ|(ml30)\lond\dat\szmsg1.txt|72|��֤��Ϣ
#define		czmsg_txt_Dfx		"CZMSG.TXT"  //3=��ҵ֤ȯ��Ϣ|(ml30)\lond\dat\czmsg.txt|73|��֤��Ϣ
#define		qsxx_txt_Dfx		"QSXX.TXT"   //4=ȯ����Ϣ|(ml30)\lond\dat\qsxx.txt|74|ȯ����Ϣ
											 //5=�Ϻ�֤��������|(ml30)\lond\dat\shmsg2.txt|75|��֤����
											 //6=����֤��������|(ml30)\lond\dat\szmsg1.txt|76|��֤����
#define		zhxx_txt_Dfx		"ZHXX.TXT"   //7=�ۺ���Ϣ|(ml30)\lond\dat\zhxx.txt|77|�ۺ���Ϣ
#define		notice_txt_Dfx		"NOTICE.TXT" //8=����֤ȯ������|(ml30)\lond\dat\notice.txt|78|���Ź���


static int IsFixedFile(char* szFile)
{
	return (!strncasecmp(szFile,SHORTMSG_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,START_Dfx,strlen(szFile))		  ||
			!strncasecmp(szFile,INDIVIDUATION_Dfx,strlen(szFile)) ||
			!strncasecmp(szFile,HSINFO_Dfx,strlen(szFile))		  ||
			!strncasecmp(szFile,FINANCE_Dfx,strlen(szFile)));
}

static int IsFixedFile_JYS(char* szFile)
{
	return (!strncasecmp(szFile,shmsg2_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,szmsg1_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,czmsg_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,qsxx_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,zhxx_txt_Dfx,strlen(szFile))	  ||
			!strncasecmp(szFile,notice_txt_Dfx,strlen(szFile)) );
}


static char MakeMarket_Dfx(HSMarketDataType x,char* szCode)
{
	char cMarket = ( (MakeMidMarket(x) >> 4) | MakeSubMarket(x));
	if( MakeMainMarket(x) == SH_Bourse && cMarket > 19 ) // ��֤
	{
		cMarket = 19;
	}
	else if( MakeMainMarket(x) == SZ_Bourse )	   // ��֤
	{
		if( MakeSubMarket(x) == KIND_SMALLSTOCK ) // ��С�̹�
			cMarket = 33; // 36
		else if( cMarket > 36 )
			cMarket = 33; // 35
	}

	//
	if( szCode )
	{
		if( MakeMainMarket(x) == SH_Bourse )
		{
			if( szCode[0] == '5' && szCode[1] == '1' && szCode[2] == '9' )
			{
				cMarket = 18;
			}
		}
		else if( MakeMainMarket(x) == SZ_Bourse )
		{
			if( (szCode[0] == '1' && szCode[1] == '6') ||
				(szCode[0] == '1' && szCode[1] == '5' && szCode[1] == '9') )
			{
				cMarket = 33; // 33
			}
		}
	}

	return cMarket;
}

static HSMarketDataType MakeMarket_Tzt(HSMarketDataType x,char* szCode)
{
	if( szCode )
	{
		if( MakeMainMarket(x) == SH_Bourse )
		{
			if( szCode[0] == '5' && szCode[1] == '1' && szCode[2] == '9' )
			{
				return 18;
			}
		}
		else if( MakeMainMarket(x) == SZ_Bourse )
		{
			if( szCode[0] == '1' && szCode[1] == '6' )
			{
				return 34;
			}
		}
	}

	return (STOCK_MARKET | ((x & 0xF0) << 4) | (x & 0x0F) );
}

static int	table[256] =  
{0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D};/*,
0x74726F50, 0x736E6F69, 0x706F4320, 0x67697279,0x28207468, 0x31202963, 0x20393939, 0x48207962,
0x6E656761, 0x64655220, 0x6E616D64, 0x6FBBA36E}; */
  
static void calc_crc32 (unsigned char *p, unsigned int nbyte, unsigned int *crcvalue)
{
	unsigned int i;

	for (i = 0; i < nbyte; i++)
		*crcvalue = (*crcvalue >> 8) ^ table[p[i] ^ (*crcvalue & 0x000000ff)];
}

typedef struct
{
	char	*cap;
	int		filet;
	int		interval;
	int		m_nPKLineType;
} TZBDATATYPE;

static TZBDATATYPE   zbdatatype[8] =
{
	{"��  ��",  	2, 	PERIOD_TYPE_DAY,4},
	{"�����",  	1, 	PERIOD_TYPE_MINUTE5,0},
	{"ʮ�����",	1, 	PERIOD_TYPE_MINUTE15,1},
	{"��ʮ����",	1,	MINUTE30,2},
	{"��ʮ����",	1,	MINUTE60,3},
	{"����", 		3,	WEEK,5},
	{"����", 		4,	MONTH,6},
	{"һ����",		5,  PERIOD_TYPE_MINUTE1,7}
};

#define SMALLORDERNUM	6
struct  TSMALLORDER
{
	int	order;
	float	v;
	TSMALLORDER()
	{
		order = -1;
		v = 0;
	}
};

static int GetDayType_Dfx(int daytype,int& nMulti,int& nConvert)
{
	if( daytype >= 0 && daytype < 8 )
	{
		if( zbdatatype[daytype].interval == WEEK )
		{
			nConvert = WEEK;
			nMulti = 7;
			return PERIOD_TYPE_DAY;
		}
		else if( zbdatatype[daytype].interval == MONTH )
		{
			nConvert = MONTH;
			nMulti = 30;
			return PERIOD_TYPE_DAY;
		}		
		else if( zbdatatype[daytype].interval == PERIOD_TYPE_MINUTE15 )
		{
			nConvert = PERIOD_TYPE_MINUTE15;
			nMulti = 3;
			return PERIOD_TYPE_MINUTE5;
		}
		else if( zbdatatype[daytype].interval == MINUTE30 )
		{
			nConvert = MINUTE30;
			nMulti = 6;
			return PERIOD_TYPE_MINUTE5;
		}
		else if( zbdatatype[daytype].interval == MINUTE60 )
		{
			nConvert = MINUTE60;
			nMulti = 12;
			return PERIOD_TYPE_MINUTE5;
		}

		return zbdatatype[daytype].interval;
	}

	return -1;
}

/* login success */
typedef struct
{
	unsigned int	ip;			/* client ip address */
	unsigned int	w;
	int		ww;
} TID;

typedef struct
{
	char		ip[4];			/* client ip address */
	char		w[4];
	char		ww[4];
} PTID;

/* login reply */
typedef struct
{
	int	errcode;			/* error code, 0 is OK */
	union
	{
		TID	tid;
		char	errinfo[256];
	} info;
} TANSWER;

#define		TRANNUM1000	1000
#define		MAXCODES	8000 //4000
#define		MAXLONHIS	241
#define		MAXLONDAY	4000
#define		MAXLONTRAN	4000
#define		BLOCKNUM	5
#define		STKNAME_LEN	8
#define		STKCODE_LEN	6
#define		DT_DAY		0
#define		DT_M300		1
#define		DT_M900		2
#define		DT_M1800	3
#define		DT_M3600	4
#define		DT_MWEEK	5
#define		DT_MMONTH	6
#define		DT_MIN		7
#define		PREVLONNOWCOUNT	5

/* ���������� Loninfo �ļ�����
 * һ�� Loninfo �ļ�����һ�� TLONINFO �ṹ,
 * һ�� TLONINFO �ṹ��2���ֶ� ��4�� RTLONINFO
 * 4��ֱ����ý������� ָ��,A��,B��,ծȯ���
 */

typedef struct
{
	unsigned short	kind;		/* ��� $0010:ָ��;$0011:��A.. */
	unsigned short	num;		/* ֧�� ��ָ:9;��A:411... */
	unsigned short	index;		/* ������ Lonnow �е���ʼλ�� */
	unsigned short	pricescale;	/* 1000 */
	unsigned short	minall;		/* 240,�ܽ���ʱ��(����) */
	unsigned short	minnow;		/* ��ǰ����ʱ��(���� 0~240) */
	unsigned short	opentime1;	/* ���翪��ʱ��(��0�㵽���ڷ�����,��ͬ) */
	unsigned short	closetime1;	/* ���������ʱ�� */
	unsigned short	opentime2;	/* ���翪��ʱ�� */
	unsigned short	closetime2;	/* ���������ʱ�� */
} RTLONINFO;

typedef struct
{
	char	kind[2];		/* ��� $0010:ָ��;$0011:��A.. */
	char	num[2];			/* ֧�� ��ָ:9;��A:411... */
	char	index[2];		/* ������ Lonnow �е���ʼλ�� */
	char	pricescale[2];		/* 1000 */
	char	minall[2];		/* 240,�ܽ���ʱ��(����) */
	char	minnow[2];		/* ��ǰ����ʱ��(���� 0~240) */
	char	opentime1[2];		/* ���翪��ʱ��(��0�㵽���ڷ�����,��ͬ) */
	char	closetime1[2];		/* ���������ʱ�� */
	char	opentime2[2];		/* ���翪��ʱ�� */
	char	closetime2[2];		/* ���������ʱ�� */
} PRTLONINFO;

typedef struct
{
           int date;			/* ��������,��ʽ�磺19980101 */
           char null[128];		/* δ�� */
           RTLONINFO kindinfo[BLOCKNUM];/* ����(ָ��,A��,B��,ծȯ) ���� */
} TLONINFO;

typedef struct
{
           char date[4];			/* ��������,��ʽ�磺19980101 */
           char null[128];			/* δ�� */
           PRTLONINFO kindinfo[BLOCKNUM];	/* ����(ָ��,A��,B��,ծȯ) ���� */
} PTLONINFO;


//struct Yls_PRTLONINFO
//{
//	short	kind;		/* ��� $0010:ָ��;$0011:��A.. */
//	short	num;			/* ֧�� ��ָ:9;��A:411... */
//	short	index;		/* ������ Lonnow �е���ʼλ�� */
//	short	pricescale;		/* 1000 */
//	short	minall;		/* 240,�ܽ���ʱ��(����) */
//	short	minnow;		/* ��ǰ����ʱ��(���� 0~240) */
//	short	opentime1;		/* ���翪��ʱ��(��0�㵽���ڷ�����,��ͬ) */
//	short	closetime1;		/* ���������ʱ�� */
//	short	opentime2;		/* ���翪��ʱ�� */
//	short	closetime2;		/* ���������ʱ�� */
//
//	void To(char cIntelToComputer )
//	{
//#ifdef WORDS_BIGENDIAN
//		if( cIntelToComputer )
//		{
//		}
//		else
//		{
//			kind = YlsShortComputerToIntel(kind);
//			num = YlsShortComputerToIntel(num);
//			index = YlsShortComputerToIntel(index);
//			pricescale = YlsShortComputerToIntel(pricescale);
//			minall = YlsShortComputerToIntel(minall);
//			minnow = YlsShortComputerToIntel(minnow);
//			opentime1 = YlsShortComputerToIntel(opentime1);
//			closetime1 = YlsShortComputerToIntel(closetime1);
//			opentime2 = YlsShortComputerToIntel(opentime2);
//			closetime2 = YlsShortComputerToIntel(closetime2);
//		}
//#endif
//	}
//};
//
//struct  Yls_TLONINFO
//{
//	int date;			/* ��������,��ʽ�磺19980101 */
//	char null[128];		/* δ�� */
//	Yls_PRTLONINFO kindinfo[BLOCKNUM];/* ����(ָ��,A��,B��,ծȯ) ���� */
//
//	void To(char cIntelToComputer )
//	{
//#ifdef WORDS_BIGENDIAN
//		if( cIntelToComputer )
//		{
//		}
//		else
//		{
//			date = YlsIntComputerToIntel(date);
//
//			for( int i = 0; i < BLOCKNUM; i++ )
//			{
//				kindinfo[i].To(cIntelToComputer);
//			}
//		}
//#endif
//	}
//};

/* ��ǰ���� Lonnow �ļ�����
 * һ�� Lonnow �ļ�����һ������,ÿһ����¼����TLonnow���͵�һ֧��Ʊ����
 * һ�� Lonnow �й�Ʊ���е�˳��������: ָ��(��12/��9),A��(Լ500),B��(Լ50),ծȯ��(Լ50)
 * �⼸������Ĺ�Ʊ��������Lonnow�е���ʼλ���� Loninfo �ļ���ָ��
 */

typedef struct
{
	char	xflag;			/* ͣ�̱�־;' '-ͣ,'0'-�� */
	char	name[STKNAME_LEN];	/* ��Ʊ���� */
	char	kind;			/*����:��ָ16,��A17,��B18,��ծ19;��ָ32,��A33,��B34,��ծ35 */
	char	code[STKCODE_LEN];	/* ��Ʊ���� */
	int	close_p;		/* �����̼� */
	int	open_p;			/* ���̼� */
	int	high_p;			/* ��߼� */
	int	low_p;			/* ��ͼ� */
	int	last_p;			/* ���¼� */
	unsigned int	total_h;	/* �ܳɽ��� */
	float	total_m;		/* �ܳɽ���� */
	int	p1;			/* ��һ�� */
	int	q1;			/* ��һ�� */
	int	p2;			/* ����� */
	int	q2;			/* ����� */
	int	p3;			/* ������ */
	int	q3;			/* ������ */
	int	p4;			/* ��һ�� */
	int	q4;			/* ��һ�� */
	int	p5;			/* ������ */
	int	q5;			/* ������ */
	int	p6;			/* ������ */
	int	q6;			/* ������ */
	int	p7;			/* ���ļ� */
	int	q7;			/* ������ */
	int	p8;			/* ����� */
	int	q8;			/* ������ */
	int	p9;			/* ���ļ� */
	int	q9;			/* ������ */
	int	p10;		/* ����� */
	int	q10;		/* ������ */
	short	newkind;	/* ����� */
	unsigned short	per_h;		/* ÿ�ֹ��� */
	int	last_h;			/* ���� */
} TLONNOW;

typedef struct
{
	char	xflag;			/* ͣ�̱�־;' '-ͣ,'0'-�� */
	char	name[STKNAME_LEN];	/* ��Ʊ���� */
	char	kind;			/*����:��ָ16,��A17,��B18,��ծ19;��ָ32,��A33,��B34,��ծ35 */
	char	code[STKCODE_LEN];	/* ��Ʊ���� */
	char	close_p[4];		/* �����̼� */
	char	open_p[4];		/* ���̼� */
	char	high_p[4];		/* ��߼� */
	char	low_p[4];		/* ��ͼ� */
	char	last_p[4];		/* ���¼� */
	char	total_h[4];		/* �ܳɽ��� */
	char	total_m[4];		/* �ܳɽ���� */
	char	p1[4];			/* ��һ�� */
	char	q1[4];			/* ��һ�� */
	char	p2[4];			/* ����� */
	char	q2[4];			/* ����� */
	char	p3[4];			/* ������ */
	char	q3[4];			/* ������ */
	char	p4[4];			/* ��һ�� */
	char	q4[4];			/* ��һ�� */
	char	p5[4];			/* ������ */
	char	q5[4];			/* ������ */
	char	p6[4];			/* ������ */
	char	q6[4];			/* ������ */
	char	p7[4];			/* ���ļ� */
	char	q7[4];			/* ������ */
	char	p8[4];			/* ����� */
	char	q8[4];			/* ������ */
	char	p9[4];			/* ���ļ� */
	char	q9[4];			/* ������ */
	char	p10[4];			/* ����� */
	char	q10[4];			/* ������ */
	char	newkind[2];		/* ����� */
	char	per_h[2];		/* ÿ�ֹ��� */
	char	last_h[4];		/* ���� */
} PTLONNOW;

typedef struct
{
	char	xflag;			/* ͣ�̱�־;' '-ͣ,��0���� */
	char	name[STKNAME_LEN];	/* ��Ʊ���� */
	char	kind;			/* ����  ��ָ16,��A17,��B18,��ծ19;��ָ32,��A33,��B34,��ծ35 */
	char	code[STKCODE_LEN];	/* ��Ʊ���� */
	int	close_p;		/* �����̼� */
	int	open_p;			/* ���̼� */
	int	high_p;			/* ��߼� */
	int	low_p;			/* ��ͼ� */
	int	last_p;			/* ���¼� */
	unsigned int	total_h;	/* �ܳɽ��� */
	float	total_m;		/* �ܳɽ���� */

	unsigned short	ups;		/* ���ǹ�Ʊ�� */
	unsigned short	downs;		/* �µ���Ʊ�� */
	unsigned short	x0;
	int	buy_h;			/* �������� */
	int	sale_h;			/* �������� */
	short	lnahead;			/* ����ָ�� */
	short	lndkzb;			/* ���ָ�� */
	short	lnqrd;			/* ǿ���� */
	short	buygasmain;		/* ������ */
	int	buygastop;		/* ���� */
	short	salegasmain;		/* ������ */
	short	salegastop;		/* ���� */

	unsigned short	totals;		/* �ܹ�Ʊ�� */
	int	lnadl;			/* ADLָ�� */

	int	pq[9];		/* m4m5 */
	int	p6;			/* δ�� */
	int	q6;			/* δ�� */
	int	x2;			/* δ�� */
	int	x3;			/* δ�� */
} TLONNOWZS;

typedef struct
{
	char	xflag;			/* ͣ�̱�־;' '-ͣ,��0���� */
	char	name[STKNAME_LEN];	/* ��Ʊ���� */
	char	kind;			/* ����  ��ָ16,��A17,��B18,��ծ19;��ָ32,��A33,��B34,��ծ35 */
	char	code[STKCODE_LEN];	/* ��Ʊ���� */
	char	close_p[4];		/* �����̼� */
	char	open_p[4];		/* ���̼� */
	char	high_p[4];		/* ��߼� */
	char	low_p[4];		/* ��ͼ� */
	char	last_p[4];		/* ���¼� */
	char	total_h[4];		/* �ܳɽ��� */
	char	total_m[4];		/* �ܳɽ���� */
	char	ups[2];			/* ���ǹ�Ʊ�� */
	char	downs[2];		/* �µ���Ʊ�� */
	char	x0[2];
	char	buy_h[4];		/* �������� */
	char	sale_h[4];		/* �������� */
	char	lnahead[2];		/* ����ָ�� */
	char	lndkzb[2];		/* ���ָ�� */
	char	lnqrd[2];		/* ǿ���� */
	char	buygasmain[2];		/* ������ */
	char	buygastop[4];		/* ���� */
	char	salegasmain[2];		/* ������ */
	char	salegastop[2];		/* ���� */
	char	totals[2];		/* �ܹ�Ʊ�� */
	char	lnadl[4];		/* ADLָ�� */

	char 	pq[36];

	char	p6[4];			/* δ�� */
	char	q6[4];			/* δ�� */
	char	x2[4];			/* δ�� */
	char	x3[4];			/* δ�� */
} PTLONNOWZS;

/* ��ʱ�ɽ� LonHis �ļ�����
 * LonHis�ļ���¼��ÿ֧��Ʊ��ÿ���ӵļ�λ����,���ԱȽϴ�
 * LonHis �Ĵ�С= (Sizeof(TLonHis) * 241) * ��Ʊ��
 * ��Ʊ����˳���� Lonnow ��һ��
 * ÿһ֧��Ʊ�����ݾ��� 241 �� TLonHis.
 */
typedef struct
{
	int	last_p;			/* ���¼� */	
	unsigned int	total_h;	/* ���� */
	float	total_m;		/* �ܳɽ���� */
	int	buy_qty; 		/* ������ */
	int	sale_qty;		/* ������ */
	unsigned short	ups;		/* ���Ǽ��� */
	unsigned short	downs;		/* �µ����� */
	short	ahead;			/* ����ָ�� */
	short	dkzb;			/* ���ָ�� */
	short	qrd;			/* ָ��ǿ�� */
	int	adl;			/* ADLָ�� */
} TLONHIS;

typedef struct
{
	char	last_p[4];		/* ���¼� */	
	char	total_h[4];		/* ���� */
	char	total_m[4];		/* �ܳɽ���� */
	char	buy_qty[4];		/* ������ */
	char	sale_qty[4];		/* ������ */
	char	ups[2];			/* ���Ǽ��� */
	char	downs[2];		/* �µ����� */
	char	ahead[2];		/* ����ָ�� */
	char	dkzb[2];		/* ���ָ�� */
	char	qrd[2];			/* ָ��ǿ�� */
	char	adl[4];			/* ADLָ�� */
} PTLONHIS;



/* �ֱʳɽ� LonTra �ļ�����
 * LonTra�ļ���¼��ÿ֧��Ʊ�ķֱʳɽ�,����Ҳ�Ƚϴ�
 * LonTra �Ĵ�С= Sizeof(TLONTRANBLOCK) * ��Ʊ��(ע�ⲻ��ָ��)
 * ��Ʊ����˳���� Lonnow ��һ��, ������ָ����
 * ÿһ֧��Ʊ�����ݾ���һ�� TLONTRANBLOCK
 * ÿһ�� TLONTRANBLOCK ��һ�� TLONTRANHEAD ͷ�� 1000 ��TLONTRAN ���.
 * ���ĳ��Ʊ�ֱʳɽ������� 1000 ��,�����ļ����ٷ���һ��1000����TLONTRANBLOCK
 * ���ѱ����е� TLONTRANHEAD.Addres ָ����һ����ʼ�ֽ�λ��,����2000������.
 */
typedef struct
{
	unsigned short tran_num;	/* ��¼���� */
	int	addres;			/* �� Tran_num>1000ʱ, 		*/
					/* Ϊ��1000����¼���ļ�ָ��;����Ϊ-1 */
} TLONTRANHEAD;

typedef struct
{
	char 	tran_num[2];		/* ��¼���� */
	char 	addres[4];		/* �� Tran_num>1000ʱ, 		*/
					/* Ϊ��1000����¼���ļ�ָ��;����Ϊ-1 */
} PTLONTRANHEAD;

typedef struct
{
	unsigned short	time;		/* �ñʳɽ���ʱ��:0-DayCount */
	int	price;			/* �ɽ��� */
	int	hands;			/* �ɽ��� */
	int	buy_price;		/* ������ */
	int	sale_price;		/* ������� */
} TLONTRAN;

typedef struct
{
	char	time[2];		/* �ñʳɽ���ʱ��:0-DayCount */
	char	price[4];		/* �ɽ��� */
	char	hands[4];		/* �ɽ��� */
	char	buy_price[4];		/* ������ */
	char	sale_price[4];		/* ������� */
} PTLONTRAN;

typedef struct
{
	TLONTRANHEAD	head;
	TLONTRAN 	data[TRANNUM1000];
}TLONTRANBLOCK;

typedef struct
{
	PTLONTRANHEAD	head;
	PTLONTRAN 	data[TRANNUM1000];
} PTLONTRANBLOCK;

/* ��ʷ K ���ļ����� .Day .wek .nmn .mnt 
 * ÿһ����ʷ�ļ�ֻ��һ֧��Ʊ������, �ù�Ʊ��������ļ����ơ��� 600600.Day
 * ����ʷ�����ļ���ʱ���Ⱥ�˳������������ TLONDAY ��¼.
 */
typedef struct
{
	int	time;		/* ʱ��,��ʽ�磺19980101,��05051300(5�����ļ�.nmn �����) */
	int	openprice;	/* ���̼� */
	int	highprice;	/* ��߼� */
	int	lowprice;	/* ��ͼ� */
	int	closeprice;	/* ���̼� */
	int	total_m;	/* �ܽ�� ��10 */
	int	total_h;	/* �ܳɽ��� */
	int	s2;		/* δ�� */
	int	s3;		/* δ�� */
	int	s4;		/* δ�� */
} TLONDAY;

typedef struct
{
	char	time[4];	/* ʱ��,��ʽ�磺19980101,��05051300(5�����ļ�.nmn �����) */
	char	openprice[4];	/* ���̼� */
	char	highprice[4];	/* ��߼� */
	char	lowprice[4];	/* ��ͼ� */
	char	closeprice[4];	/* ���̼� */
	char	total_m[4];	/* �ܽ�� ��10 */
	char	total_h[4];	/* �ܳɽ��� */
	char	s2[4];		/* δ�� */
	char	s3[4];		/* δ�� */
	char	s4[4];		/* δ�� */
} PTLONDAY;

/* LonCDP �ļ����� �� \data\shase\ \data\sznse\ ��
 * LonCDP �ļ���С= sizeof(TLONCDP) * ��Ʊ֧��,
 * LonCDP ����5��ƽ��������
 */
typedef struct
{
	char code[STKCODE_LEN];	/* ��Ʊ���� */
	int	ah;		/* δ�� */
	int	nh;		/* δ�� */
	int	cdp;		/* δ�� */
	int	nl;		/* δ�� */
	int	al;		/* δ�� */
	int	total5;		/* 5��ƽ�������� */
} TLONCDP;

typedef struct
{
	char code[STKCODE_LEN];	/* ��Ʊ���� */
	char	ah[4];		/* δ�� */
	char	nh[4];		/* δ�� */
	char	cdp[4];		/* δ�� */
	char	nl[4];		/* δ�� */
	char	al[4];		/* δ�� */
	char	total5[4];	/* 5��ƽ�������� */
} PTLONCDP;


/* Ʊ�������(���ڳ�ʼ��)
 */
typedef struct
{
	char	xflag;			/* ͣ�̱�־;' '-ͣ,��0���� */
	char	name[STKNAME_LEN];	/* ��Ʊ���� */
	char	kind;			/* ����  ��ָ16,��A17,��B18,��ծ19;��ָ32,��A33,��B34,��ծ35 */
	char	code[STKCODE_LEN];	/* ��Ʊ���� */
	int	close_p;		/* �����̼� */
	unsigned short per_h;		/* ÿ�ֹ��� */
	int	total5;			/* 5��ƽ�������� */
} TSTOCKCODE;

typedef struct
{
	char	xflag;			/* ͣ�̱�־;' '-ͣ,��0���� */
	char	name[STKNAME_LEN];	/* ��Ʊ���� */
	char	kind;			/* ����  ��ָ16,��A17,��B18,��ծ19;��ָ32,��A33,��B34,��ծ35 */
	char	code[STKCODE_LEN];	/* ��Ʊ���� */
	char	close_p[4];		/* �����̼� */
	char	per_h[2];		/* ÿ�ֹ��� */
	char	total5[4];		/* 5��ƽ�������� */
} PTSTOCKCODE;

//typedef struct
//{
//	char	*cap;
//	int	filet;
//	int	interval;
//} TZBDATATYPE;

typedef struct
{
	char	code[STKCODE_LEN];	/* ��Ʊ���� */
	char	name[STKNAME_LEN];	/* ��Ʊ���� */
	int	lastdate;		/* �������ʱ�� */
	float	data[34];		/* �������� */
} TFINANCE;

typedef struct
{
	char	code[STKCODE_LEN];	/* ��Ʊ���� */
	char	name[STKNAME_LEN];	/* ��Ʊ���� */
	char	lastdate[4];		/* �������ʱ�� */
	char	data[34][4];		/* �������� */
} PTFINANCE;

/* һ�����Ϻ�֤ȯ����������Ľṹ */
/* ��ʷ�ֱ����� */
typedef struct
{
	int 	date;		// ���� yyyymmdd
	int 	offset;		// �����ļ��е�ƫ����
	int		len;		// ���շֱ����ݳ���
	int		blocknumber;	// ���շֱ���Ŀ
} TTRAINDEX;
typedef struct
{
	char	date[4];
	char	offset[4];
	char	len[4];
	char	blocknumber[4];
}PTTRAINDEX;
/* ��ʷ�ֱ����� */
typedef struct
{
	unsigned short 	time;	/* �ɽ�ʱ�� */
	int				price;	/* �ɽ��۸� */			
	unsigned int	hands;	/* �ɽ����� */
	int				buy_price;	/* ��һ�� */
	int				sale_price; /* ��һ�� */
}THISTRA;
typedef struct
{
	char	time[2];
	char	price[4];
	char	hands[4];
	char	buy_price[4];
	char	sale_price[4];
}PTHISTRA;

/* ��ʷ���������� */
typedef struct
{
	int 	date;
	int		offset;
	int		len;
	int		blocknumber;
}TLONORDINDEX;

/*  ��ʷ���������� */
typedef struct
{
	int	time;		/*ʱ��,�Թ�Ʊ��0-240*/
	int price;		/*���³ɽ���*/
	int	hands;		/*���³ɽ�����*/
	int buy_p1;		/*��һ�۸�*/
	int buy_h1;		/*��һ����*/
	int buy_p2;		/*����۸�*/
	int buy_h2;		/*�������*/
	int buy_p3;		/*�����۸�*/
	int buy_h3;		/*��������*/
	int buy_p4;		/*���ļ۸�*/
	int buy_h4;		/*��������*/
	int buy_p5;		/*����۸�*/
	int buy_h5;		/*��������*/
	int sale_p1;		/*��һ�۸�*/
	int sale_h1;		/*��һ����*/
	int sale_p2;		/*�����۸�*/
	int sale_h2;		/*��������*/
	int sale_p3;		/*�����۸�*/
	int sale_h3;		/*��������*/	
	int sale_p4;		/*���ļ۸�*/
	int sale_h4;		/*��������*/
	int sale_p5;		/*����۸�*/
	int sale_h5;		/*��������*/	
}THISMMP;
typedef struct
{
	char	time[4];		/*ʱ��,�Թ�Ʊ��0-240*/
	char 	price[4];		/*���³ɽ���*/
	char	hands[4];		/*���³ɽ�����*/
	char 	buy_p1[4];		/*��һ�۸�*/
	char 	buy_h1[4];		/*��һ����*/
	char 	buy_p2[4];		/*����۸�*/
	char 	buy_h2[4];		/*�������*/
	char 	buy_p3[4];		/*�����۸�*/
	char 	buy_h3[4];		/*��������*/
	char	buy_p4[4];		/*���ļ۸�*/
	char	buy_h4[4];		/*��������*/
	char	buy_p5[4];		/*����۸�*/
	char	buy_h5[4];		/*��������*/
	char 	sale_p1[4];		/*��һ�۸�*/
	char 	sale_h1[4];		/*��һ����*/
	char 	sale_p2[4];		/*�����۸�*/
	char 	sale_h2[4];		/*��������*/
	char 	sale_p3[4];		/*�����۸�*/
	char 	sale_h3[4];		/*��������*/	
	char	sale_p4[4];		/*���ļ۸�*/
	char	sale_h4[4];		/*��������*/
	char	sale_p5[4];		/*����۸�*/
	char	sale_h5[4];		/*��������*/	
} PTHISMMP;


#define AHEADERSIG	0xff20

/* ͨѶ�е�Ǯ�����ݰ� */ 
typedef struct
{
	int	open_p;
	int	high_p;
	int	low_p;
	int	last_p;
	unsigned int	total_h;
	float	total_m;
	int	p1;
	int	q1;
	int	p2;
	int	q2;
	int	p3;
	int	q3;
	int	p4;
	int	q4;
	int	p5;
	int	q5;
	int	p6;
	int	q6;
	int	p7;			/* ���ļ� */
	int	q7;			/* ������ */
	int	p8;			/* ����� */
	int	q8;			/* ������ */
	int	p9;			/* ���ļ� */
	int	q9;			/* ������ */
	int	p10;		/* ����� */
	int	q10;		/* ������ */
	int	last_h;
} TTCPLONNOW;

typedef struct
{
	char	open_p[4];
	char	high_p[4];
	char	low_p[4];
	char	last_p[4];
	char	total_h[4];
	char	total_m[4];
	char	p1[4];
	char	q1[4];
	char	p2[4];
	char	q2[4];
	char	p3[4];
	char	q3[4];
	char	p4[4];
	char	q4[4];
	char	p5[4];
	char	q5[4];
	char	p6[4];
	char	q6[4];
	char	p7[4];			/* ���ļ� */
	char	q7[4];			/* ������ */
	char	p8[4];			/* ����� */
	char	q8[4];			/* ������ */
	char	p9[4];			/* ���ļ� */
	char	q9[4];			/* ������ */
	char	p10[4];			/* ����� */
	char	q10[4];			/* ������ */
	char	last_h[4];
} PTTCPLONNOW;

typedef struct
{
	int	open_p;
	int	high_p;
	int	low_p;
	int	last_p;
	unsigned int	total_h;
	float	total_m;
	int	p1;
	int	q1;
	int	p2;
	int	q2;
	int	p3;
	int	q3;
	int	p4;
	int	q4;
	int	p5;
	int	q5;
	int	p6;
	int	q6;
	int	last_h;
} TOLDTCPLONNOW;

typedef struct
{
	char	open_p[4];
	char	high_p[4];
	char	low_p[4];
	char	last_p[4];
	char	total_h[4];
	char	total_m[4];
	char	p1[4];
	char	q1[4];
	char	p2[4];
	char	q2[4];
	char	p3[4];
	char	q3[4];
	char	p4[4];
	char	q4[4];
	char	p5[4];
	char	q5[4];
	char	p6[4];
	char	q6[4];
	char	last_h[4];
} PTOLDTCPLONNOW;

/* �˳�ʱ���ļ�Ҫʵʱ���� */
typedef struct
{
	int	open_p;
	int	high_p;
	int	low_p;
	int	last_p;
	unsigned int	total_h;
	float	total_m;
	int	p1;
	int	q1;
	int	p4;
	int	q4;
	int	last_h;
} TTCPLONNOWLAST;

typedef struct
{
	char	open_p[4];
	char	high_p[4];
	char	low_p[4];
	char	last_p[4];
	char	total_h[4];
	char	total_m[4];
	char	p1[4];
	char	q1[4];
	char	p4[4];
	char	q4[4];
	char	last_h[4];
} PTTCPLONNOWLAST;

/* �˳�ʱ���ļ�Ҫʵʱ���� */
typedef struct
{
	TTCPLONNOWLAST	nowdata;
	int		last_p5;
} TTCPLONNOWLAST5;

typedef struct
{
	PTTCPLONNOWLAST	nowdata;
	char		last_p5[4];
} PTTCPLONNOWLAST5;

/* ��ͨ��Ʊ��lonhis */
typedef struct
{
	int	last_p;
	unsigned int	total_h;
	float	total_m;
	int	buy_qty;
	int	sale_qty;
} TTCPLONHISNORMAL;

typedef struct
{
	char	last_p[4];
	char	total_h[4];
	char	total_m[4];
	char	buy_qty[4];
	char	sale_qty[4];
} PTTCPLONHISNORMAL;

/* ��ͨ��Ʊ��lonhis���� */
typedef struct
{
	unsigned short	last_p;
	unsigned short	aver_p;
	unsigned int	total_h;
} TTCPLONHISNORMALCOMP;

typedef struct
{
	char	last_p[2];
	char	aver_p[2];
	char	total_h[4];
} PTTCPLONHISNORMALCOMP;

typedef struct
{
	unsigned short	headsig;
	unsigned short	minnow;
	unsigned short	len;
	unsigned short	step;
	int		icode;
	short		pscale;
} THISHEADER;

typedef struct
{
	char	headsig[2];
	char	minnow[2];
	char	len[2];
	char	step[2];
	char	icode[4];
	char	pscale[2];
} PTHISHEADER;

/* ָ����lonhis */
typedef struct
{
	unsigned short	ups; 	/* ���Ǽ��� */
	unsigned short	downs; 	/* �µ����� */
	short		ahead;	/* ����ָ�� */
	short		dkzb; 	/* ���ָ�� */
	short		qrd; 	/* ָ��ǿ�� */
	int		adl; 	/* ADLָ�� */
} TTCPLONHISZHISHU;

typedef struct
{
	char	ups[2]; 	/* ���Ǽ��� */
	char	downs[2]; 	/* �µ����� */
	char	ahead[2];	/* ����ָ�� */
	char	dkzb[2]; 	/* ���ָ�� */
	char	qrd[2]; 	/* ָ��ǿ�� */
	char	adl[4]; 	/* ADLָ�� */
} PTTCPLONHISZHISHU;

/****�ֱʳɽ������ݽṹ TcpLonTran ****************/
typedef struct
{
	unsigned short	tran_num; /* ��¼���� */
	int		addres; /* �� Tan_num>1000ʱ,Ϊ��1000����¼���ļ�ָ��;����Ϊ-1 */
	unsigned short	time; /* �ñʳɽ���ʱ��:0-240 */
	int		price; /* �� */
	int		hands; /* �� */
	int		buy_price; /* ��� */
	int		sale_price; /* ���� */
} TTCPLONTRAN;

typedef struct
{
	int	time;
	int	openprice;
	int	highprice;
	int	lowprice;
	int	closeprice;
	int	total_h;
	int	total_m;
} TTCPLONDAY;

typedef struct
{
	char	time[4];
	char	openprice[4];
	char	highprice[4];
	char	lowprice[4];
	char	closeprice[4];
	char	total_h[4];
	char	total_m[4];
} PTTCPLONDAY;

typedef struct
{
	int		time;
	unsigned short	openprice;
	unsigned short	highprice;
	unsigned short	lowprice;
	unsigned short	closeprice;
	int		total_h;
} TTCPLONDAYCOMP;

typedef struct
{
	char	time[4];
	char	openprice[2];
	char	highprice[2];
	char	lowprice[2];
	char	closeprice[2];
	char	total_h[4];
} PTTCPLONDAYCOMP;

typedef struct
{
	TTCPLONDAY 		tcplonday;
	int		gzlx;
}TTCPLONDAYGZ;

typedef struct
{
	PTTCPLONDAY		pttcplonday;
	char	gzlx[4];
}PTTCPLONDAYGZ;

typedef struct
{
	TTCPLONDAYCOMP	tcplondaycomp;
	int		gzlx;
}TTCPLONDAYCOMPGZ;

typedef struct
{
	PTTCPLONDAYCOMP pttcplondaycomp;
	char	gzlx[4];
}PTTCPLONDAYCOMPGZ;

typedef struct
{
	unsigned short	headsig;
	int		icode;
	unsigned short	len;
	short		pscale;
} TDAYHEADER;

typedef struct
{
	char	headsig[2];
	char	icode[4];
	char	len[2];
	char	pscale[2];
} PTDAYHEADER;


struct TSMALLRINFO
{
	unsigned short	kind;
	unsigned short	num;
	unsigned short	index;
};

typedef struct
{
	char	kind[2];
	char	num[2];
	char	index[2];
} PTSMALLRINFO;

struct TTCPLONINFO
{
	unsigned short	headsig;
	int				date;
	unsigned short	pricescale;
	unsigned short	minall;
	unsigned short	minnow;
	unsigned short	opentime1;
	unsigned short	closetime1;
	unsigned short	opentime2;
	unsigned short	closetime2;
	TSMALLRINFO		rinfo[9];
};	

typedef struct
{
	char		headsig[2];
	char		date[4];
	char		pricescale[2];
	char		minall[2];
	char		minnow[2];
	char		opentime1[2];
	char		closetime1[2];
	char		opentime2[2];
	char		closetime2[2];
	PTSMALLRINFO	rinfo[9];
} PTTCPLONINFO;	

typedef struct
{
	unsigned short  kind;
	unsigned short  minnow;
} TREALLONINFO;

typedef struct
{
	char    kind[2];
	char    minnow[2];
} PTREALLONINFO;

typedef struct
{
	int     last_p;
	int     total_h;
	float   total_m;
	unsigned short  ups;
	unsigned short  downs;
	short   dkzb;
	short   qrd;
} TTCPLONNOWZS;

typedef struct
{   
	char    last_p[4];
	char    total_h[4];
	char    total_m[4];
	char    ups[2];
	char    downs[2];
	char    dkzb[2];
	char    qrd[2];
} PTTCPLONNOWZS;


static void PackTTcpLonInfo(TTCPLONINFO *unpack, PTTCPLONINFO *pack)
{
	int	i;

	short2byte(unpack->headsig, pack->headsig);
	int2byte(unpack->date, pack->date);
	short2byte(unpack->pricescale, pack->pricescale);
	short2byte(unpack->minall, pack->minall);
	short2byte(unpack->minnow, pack->minnow);
	short2byte(unpack->opentime1, pack->opentime1);
	short2byte(unpack->closetime1, pack->closetime1);
	short2byte(unpack->opentime2, pack->opentime2);
	short2byte(unpack->closetime2, pack->closetime2);
	for(i = 0; i < BLOCKNUM * 2 - 1; i++)
	{
		short2byte(unpack->rinfo[i].kind, pack->rinfo[i].kind);
		short2byte(unpack->rinfo[i].num, pack->rinfo[i].num);
		short2byte(unpack->rinfo[i].index, pack->rinfo[i].index);
	}
}

static void PackStockCode(TSTOCKCODE *unpack, PTSTOCKCODE *pack)
{
	pack->xflag = unpack->xflag;
	memcpy(pack->name, unpack->name, STKNAME_LEN);
	pack->kind = unpack->kind;
	memcpy(pack->code, unpack->code, STKCODE_LEN);
	int2byte(unpack->close_p, pack->close_p);
	short2byte(unpack->per_h, pack->per_h);
	int2byte(unpack->total5, pack->total5);
}

static void iGenerizeTTCPLONNOWLAST5(TTCPLONNOWLAST5 *result, TLONNOW *lonnow)
{
	result->nowdata.open_p = lonnow->open_p;
	result->nowdata.high_p = lonnow->high_p;
	result->nowdata.low_p = lonnow->low_p;
	result->nowdata.last_p = lonnow->last_p;
	result->nowdata.total_h = lonnow->total_h;
	result->nowdata.total_m = lonnow->total_m;
	result->nowdata.p1 = lonnow->p1;
	result->nowdata.q1 = lonnow->q1 + lonnow->q2 + lonnow->q3 + lonnow->q7 + lonnow->q8;
	result->nowdata.p4 = lonnow->p4;
	result->nowdata.q4 = lonnow->q4 + lonnow->q5 + lonnow->q6 + lonnow->q9 + lonnow->q10;
	result->nowdata.last_h = lonnow->last_h;
	//result->last_p5 = prevlonnow[prevlonnowcur][i].last_p;
}

static void PackTTcpLonNowLast(TTCPLONNOWLAST *unpack, PTTCPLONNOWLAST *pack)
{
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->p1, pack->p1);
	int2byte(unpack->q1, pack->q1);
	int2byte(unpack->p4, pack->p4);
	int2byte(unpack->q4, pack->q4);
	int2byte(unpack->last_h, pack->last_h);
}

static void PackTTcpLonNowLast5(TTCPLONNOWLAST5 *unpack, PTTCPLONNOWLAST5 *pack)
{
	PackTTcpLonNowLast(&unpack->nowdata, &pack->nowdata);
	int2byte(unpack->last_p5, pack->last_p5);
}

static void ConvertLonNowToDfx(StockInitInfo* pStockInitInfo,ShareRealTimeData* pShareRealTimeData,StockOtherData* pStockOtherData,TLONNOW* pTLONNOW)
{
	TLONNOWZS zs;

	if( MakeIndexMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) )
	{
		memset(&zs,0,sizeof(zs));

		zs.xflag = '0';			/* ͣ�̱�־;' '-ͣ,��0���� */
		strncpy(zs.name,pStockInitInfo->m_cStockName,STKNAME_LEN);	/* ��Ʊ���� */
		zs.kind = MakeMarket_Dfx(pStockInitInfo->m_ciStockCode.m_cCodeType,
			pStockInitInfo->m_ciStockCode.m_cCode);			/* ����  ��ָ16,��A17,��B18,��ծ19;��ָ32,��A33,��B34,��ծ35 */
		strncpy(zs.code,pStockInitInfo->m_ciStockCode.m_cCode,STKCODE_LEN);	/* ��Ʊ���� */
		zs.close_p = pStockInitInfo->m_lPrevClose;		/* �����̼� */
		zs.open_p = pShareRealTimeData->m_indData.m_lOpen;			/* ���̼� */
		zs.high_p = pShareRealTimeData->m_indData.m_lMaxPrice;			/* ��߼� */
		zs.low_p = pShareRealTimeData->m_indData.m_lMinPrice;			/* ��ͼ� */
		zs.last_p = pShareRealTimeData->m_indData.m_lNewPrice;			/* ���¼� */
		zs.total_h = pShareRealTimeData->m_indData.m_lTotal;	/* �ܳɽ��� */
		zs.total_m = pShareRealTimeData->m_indData.m_fAvgPrice;		/* �ܳɽ���� */

		zs.ups = pShareRealTimeData->m_indData.m_nRiseCount;		/* ���ǹ�Ʊ�� */
		zs.downs = pShareRealTimeData->m_indData.m_nFallCount;		/* �µ���Ʊ�� */
		zs.x0 = 0;
		zs.buy_h = pShareRealTimeData->m_indData.m_lBuyCount;			/* �������� */
		zs.sale_h = pShareRealTimeData->m_indData.m_lSellCount;			/* �������� */
		zs.lnahead = pShareRealTimeData->m_indData.m_nLead;			/* ����ָ�� */
		zs.lndkzb = pShareRealTimeData->m_indData.m_nRiseTrend;			/* ���ָ�� */
		zs.lnqrd = pShareRealTimeData->m_indData.m_nFallTrend;			/* ǿ���� */
		zs.buygasmain;		/* ������ */
		zs.buygastop;		/* ���� */
		zs.salegasmain;		/* ������ */
		zs.salegastop;		/* ���� */

		zs.totals = pShareRealTimeData->m_indData.m_nTotalStock2;		/* �ܹ�Ʊ�� */
		zs.lnadl = pShareRealTimeData->m_indData.m_lADL;			/* ADLָ�� */

		memset(pTLONNOW,0,sizeof(TLONNOW));
		memcpy(pTLONNOW,&zs,sizeof(zs));

	}
	else
	{
		pTLONNOW->xflag = '0';			/* ͣ�̱�־;' '-ͣ,'0'-�� */
		strncpy(pTLONNOW->name,pStockInitInfo->m_cStockName,STKNAME_LEN);	/* ��Ʊ���� */
		pTLONNOW->kind = MakeMarket_Dfx(pStockInitInfo->m_ciStockCode.m_cCodeType,pStockInitInfo->m_ciStockCode.m_cCode);			/*����:��ָ16,��A17,��B18,��ծ19;��ָ32,��A33,��B34,��ծ35 */
		strncpy(pTLONNOW->code,pStockInitInfo->m_ciStockCode.m_cCode,STKCODE_LEN);	/* ��Ʊ���� */
		pTLONNOW->close_p = pStockInitInfo->m_lPrevClose;		/* �����̼� */
		pTLONNOW->open_p = pShareRealTimeData->m_nowData.m_lOpen;			/* ���̼� */
		pTLONNOW->high_p = pShareRealTimeData->m_nowData.m_lMaxPrice;			/* ��߼� */
		pTLONNOW->low_p = pShareRealTimeData->m_nowData.m_lMinPrice;			/* ��ͼ� */
		pTLONNOW->last_p = pShareRealTimeData->m_nowData.m_lNewPrice;			/* ���¼� */

		// ��ծ
		if( MakeSubMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) == KIND_BOND )
			pTLONNOW->total_h = pShareRealTimeData->m_nowData.m_lTotal*100;	/* �ܳɽ��� */
		else
			pTLONNOW->total_h = pShareRealTimeData->m_nowData.m_lTotal;	/* �ܳɽ��� */

		pTLONNOW->total_m = pShareRealTimeData->m_nowData.m_fAvgPrice;		/* �ܳɽ���� */
		pTLONNOW->p1 = pShareRealTimeData->m_nowData.m_lBuyPrice1;			/* ��һ�� */
		pTLONNOW->q1 = pShareRealTimeData->m_nowData.m_lBuyCount1;			/* ��һ�� */
		pTLONNOW->p2 = pShareRealTimeData->m_nowData.m_lBuyPrice2;			/* ����� */
		pTLONNOW->q2 = pShareRealTimeData->m_nowData.m_lBuyCount2;			/* ����� */
		pTLONNOW->p3 = pShareRealTimeData->m_nowData.m_lBuyPrice3;			/* ������ */
		pTLONNOW->q3 = pShareRealTimeData->m_nowData.m_lBuyCount3;			/* ������ */
		pTLONNOW->p4 = pShareRealTimeData->m_nowData.m_lSellPrice1;			/* ��һ�� */
		pTLONNOW->q4 = pShareRealTimeData->m_nowData.m_lSellCount1;			/* ��һ�� */
		pTLONNOW->p5 = pShareRealTimeData->m_nowData.m_lSellPrice2;			/* ������ */
		pTLONNOW->q5 = pShareRealTimeData->m_nowData.m_lSellCount2;			/* ������ */
		pTLONNOW->p6 = pShareRealTimeData->m_nowData.m_lSellPrice3;			/* ������ */
		pTLONNOW->q6 = pShareRealTimeData->m_nowData.m_lSellCount3;			/* ������ */
		pTLONNOW->p7 = pShareRealTimeData->m_nowData.m_lBuyPrice4;			/* ���ļ� */
		pTLONNOW->q7 = pShareRealTimeData->m_nowData.m_lBuyCount4;			/* ������ */
		pTLONNOW->p8 = pShareRealTimeData->m_nowData.m_lBuyPrice5;			/* ����� */
		pTLONNOW->q8 = pShareRealTimeData->m_nowData.m_lBuyCount5;			/* ������ */
		pTLONNOW->p9 = pShareRealTimeData->m_nowData.m_lSellPrice4;			/* ���ļ� */
		pTLONNOW->q9 = pShareRealTimeData->m_nowData.m_lSellCount4;			/* ������ */
		pTLONNOW->p10 = pShareRealTimeData->m_nowData.m_lSellPrice5;		/* ����� */
		pTLONNOW->q10 = pShareRealTimeData->m_nowData.m_lSellCount5;		/* ������ */
		pTLONNOW->newkind = 0;	/* ����� */
		
		pTLONNOW->per_h = pShareRealTimeData->m_nowData.m_nHand;		/* ÿ�ֹ��� */

		pTLONNOW->last_h = pStockOtherData->m_lCurrent;			/* ���� */
	}
}

static void iGenerizeTTCPLONNOW(TTCPLONNOW *result,TLONNOW *lonnow)
{
	result->open_p = lonnow->open_p;
	result->high_p = lonnow->high_p; 
	result->low_p = lonnow->low_p;
	result->last_p = lonnow->last_p;
	result->total_h = lonnow->total_h;
	result->total_m = lonnow->total_m;
	result->p1 = lonnow->p1;
	result->q1 = lonnow->q1;
	result->p2 = lonnow->p2;
	result->q2 = lonnow->q2;
	result->p3 = lonnow->p3;
	result->q3 = lonnow->q3;
	result->p4 = lonnow->p4;
	result->q4 = lonnow->q4;
	result->p5 = lonnow->p5;
	result->q5 = lonnow->q5;
	result->p6 = lonnow->p6;
	result->q6 = lonnow->q6;
	result->p7 = lonnow->p7;
	result->q7 = lonnow->q7;
	result->p8 = lonnow->p8;
	result->q8 = lonnow->q8;
	result->p9 = lonnow->p9;
	result->q9 = lonnow->q9;
	result->p10 = lonnow->p10;
	result->q10 = lonnow->q10;
	result->last_h = lonnow->last_h;
}

static void PackTTcpLonNow(TTCPLONNOW *unpack, PTTCPLONNOW *pack)
{
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->p1, pack->p1);
	int2byte(unpack->q1, pack->q1);
	int2byte(unpack->p2, pack->p2);
	int2byte(unpack->q2, pack->q2);
	int2byte(unpack->p3, pack->p3);
	int2byte(unpack->q3, pack->q3);
	int2byte(unpack->p4, pack->p4);
	int2byte(unpack->q4, pack->q4);
	int2byte(unpack->p5, pack->p5);
	int2byte(unpack->q5, pack->q5);
	int2byte(unpack->p6, pack->p6);
	int2byte(unpack->q6, pack->q6);
	int2byte(unpack->p7, pack->p7);
	int2byte(unpack->q7, pack->q7);
	int2byte(unpack->p8, pack->p8);
	int2byte(unpack->q8, pack->q8);
	int2byte(unpack->p9, pack->p9);
	int2byte(unpack->q9, pack->q9);
	int2byte(unpack->p10, pack->p10);
	int2byte(unpack->q10, pack->q10);
	int2byte(unpack->last_h, pack->last_h);
}

static void PackTOldTcpLonNow_Index(TLONNOWZS* unpack, PTLONNOWZS *pack)
{
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	short2byte(unpack->ups, pack->ups);
	short2byte(unpack->downs, pack->downs);
	short2byte(unpack->x0, pack->x0);
	int2byte(unpack->buy_h, pack->buy_h);
	int2byte(unpack->sale_h, pack->sale_h);
	short2byte(unpack->lnahead, pack->lnahead);
	short2byte(unpack->lndkzb, pack->lndkzb);
	short2byte(unpack->lnqrd, pack->lnqrd);
	short2byte(unpack->buygasmain, pack->buygasmain);
	short2byte(unpack->buygastop, pack->buygastop);
	short2byte(unpack->salegasmain, pack->salegasmain);
	short2byte(unpack->salegastop, pack->salegastop);
	short2byte(unpack->totals, pack->totals);
	int2byte(unpack->lnadl, pack->lnadl);
}

static void PackTOldTcpLonNow(TOLDTCPLONNOW *unpack, PTOLDTCPLONNOW *pack)
{
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->p1, pack->p1);
	int2byte(unpack->q1, pack->q1);
	int2byte(unpack->p2, pack->p2);
	int2byte(unpack->q2, pack->q2);
	int2byte(unpack->p3, pack->p3);
	int2byte(unpack->q3, pack->q3);
	int2byte(unpack->p4, pack->p4);
	int2byte(unpack->q4, pack->q4);
	int2byte(unpack->p5, pack->p5);
	int2byte(unpack->q5, pack->q5);
	int2byte(unpack->p6, pack->p6);
	int2byte(unpack->q6, pack->q6);
	int2byte(unpack->last_h, pack->last_h);
}

static void iGenerizeTOLDTCPLONNOW(TOLDTCPLONNOW *result, TLONNOW *lonnow)
{
	result->open_p = lonnow->open_p;
	result->high_p = lonnow->high_p; 
	result->low_p = lonnow->low_p;
	result->last_p = lonnow->last_p;
	result->total_h = lonnow->total_h;
	result->total_m = lonnow->total_m;
	result->p1 = lonnow->p1;
	result->q1 = lonnow->q1;
	result->p2 = lonnow->p2;
	result->q2 = lonnow->q2;
	result->p3 = lonnow->p3;
	result->q3 = lonnow->q3;
	result->p4 = lonnow->p4;
	result->q4 = lonnow->q4;
	result->p5 = lonnow->p5;
	result->q5 = lonnow->q5;
	result->p6 = lonnow->p6;
	result->q6 = lonnow->q6;
	result->last_h = lonnow->last_h;
}

static void iGenerizeTTCPLONHISNORMAL(TTCPLONHISNORMAL *result, StockHistoryData* pHisData)
{
	result->last_p = pHisData->m_lNewPrice;
	result->total_h = pHisData->m_lTotal;
	result->total_m = pHisData->m_fAvgPrice;
	result->buy_qty = pHisData->m_lBuyCount;
	result->sale_qty = pHisData->m_lSellCount;
}

static void PackTTcpLonHisNormal(TTCPLONHISNORMAL *unpack, PTTCPLONHISNORMAL *pack)
{
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->buy_qty, pack->buy_qty);
	int2byte(unpack->sale_qty, pack->sale_qty);
}

static short getpricescale(int close_p)
{
	short	pscale = 0;

	if		(close_p < 0x1f)		pscale = (short)-7;
	else if (close_p < 0x3f)		pscale = (short)-6;
	else if (close_p < 0x7f)		pscale = (short)-5;
	else if (close_p < 0xff)		pscale = (short)-4;
	else if (close_p < 0x1ff)		pscale = (short)-3;
	else if (close_p < 0x3ff)		pscale = (short)-2;
	else if (close_p < 0x7ff)		pscale = (short)-1;
	else if (close_p < 0xfff)		pscale = (short)0;
	else if (close_p < 0x1fff)		pscale = (short)1;
	else if (close_p < 0x3fff)		pscale = (short)2;
	else if (close_p < 0x7fff)		pscale = (short)3;
	else if (close_p < 0xffff)		pscale = (short)4;
	else if (close_p < 0x1ffff)		pscale = (short)5;
	else if (close_p < 0x3ffff)		pscale = (short)6;
	else if (close_p < 0x7ffff)		pscale = (short)7;
	else if (close_p < 0xfffff)		pscale = (short)8;
	else if (close_p < 0x1fffff)	pscale = (short)9;
	else if (close_p < 0x3fffff)	pscale = (short)10;
	else if (close_p < 0x7fffff)	pscale = (short)11;
	else if (close_p < 0xffffff)	pscale = (short)12;
	else if (close_p < 0x1ffffff)	pscale = (short)13;
	else if (close_p < 0x3ffffff)	pscale = (short)14;
	else if (close_p < 0x7ffffff)	pscale = (short)15;
	else if (close_p < 0xfffffff)	pscale = (short)16;
	else if (close_p < 0x1fffffff)	pscale = (short)16;
	else if (close_p < 0x3fffffff)	pscale = (short)16;
	else if (close_p < 0x7fffffff)	pscale = (short)16;

	return pscale;
}

static void iGenerizeTTCPLONHISNORMALCOMP(TTCPLONHISNORMALCOMP *result, StockHistoryData* pHisData, int pscale)
{
	if (pscale < 0)
	{
		result->last_p = (unsigned short)(pHisData->m_lNewPrice << (-pscale));
#ifdef HS_SUPPORT_UNIX
		result->aver_p = (unsigned short)(rint((double)((pHisData->m_fAvgPrice + 1) * (1 << (-pscale))) / (double)(pHisData->m_lTotal + 1) * 1000));
#else
		result->aver_p = (unsigned short)((int)((double)((pHisData->m_fAvgPrice + 1) * (1 << (-pscale))) / (double)(pHisData->m_lTotal + 1) * 1000));
#endif
	}
	else
	{
		result->last_p = (unsigned short)(pHisData->m_lNewPrice >> pscale);
#ifdef HS_SUPPORT_UNIX
		result->aver_p = (unsigned short)(rint((double)((pHisData->m_fAvgPrice + 1) / (1 << pscale)) / (double)(pHisData->m_lTotal + 1) * 1000));
#else
		result->aver_p = (unsigned short)((int)((double)((pHisData->m_fAvgPrice + 1) / (1 << pscale)) / (double)(pHisData->m_lTotal + 1) * 1000));
#endif
	}
	result->total_h = pHisData->m_lTotal;
}

static void PackTTcpLonHisNormalCOMP(TTCPLONHISNORMALCOMP *unpack, PTTCPLONHISNORMALCOMP *pack)
{
	short2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	short2byte(unpack->aver_p, pack->aver_p);
}

static void PackTHISHEADER(THISHEADER *unpack, PTHISHEADER *pack)
{
	short2byte(unpack->headsig, pack->headsig);
	int2byte(unpack->icode, pack->icode);
	short2byte(unpack->minnow, pack->minnow);
	short2byte(unpack->len, pack->len);
	short2byte(unpack->step, pack->step);
	short2byte(unpack->pscale, pack->pscale);
}

static void PackLonTran(TLONTRAN *unpack, PTLONTRAN *pack)
{
	short2byte(unpack->time, pack->time);
	int2byte(unpack->price, pack->price);
	int2byte(unpack->hands, pack->hands);
	int2byte(unpack->buy_price, pack->buy_price);
	int2byte(unpack->sale_price, pack->sale_price);
}

static void ConvertLonTran_Dfx(StockTick* pNextTrace, TLONTRAN* ln)
{
	ln->time = pNextTrace->m_nTime;		/* �ñʳɽ���ʱ��:0-DayCount */
	ln->price = pNextTrace->m_lNewPrice;			/* �ɽ��� */
	ln->hands = pNextTrace->m_lCurrent;			/* �ɽ��� */
	ln->buy_price = pNextTrace->m_lBuyPrice;		/* ������ */
	ln->sale_price = pNextTrace->m_lSellPrice;		/* ������� */
}

static void iGenerizeTTCPLONHISZHISHU(TTCPLONHISZHISHU *result, StockHistoryData* pHisData)
{
	result->ups = pHisData->m_dmIndex.m_nRiseCount;
	result->downs = pHisData->m_dmIndex.m_nFallCount;
	result->ahead = pHisData->m_dmIndex.m_nLead;
	result->dkzb = pHisData->m_dmIndex.m_nRiseTrend;
	result->qrd = pHisData->m_dmIndex.m_nFallTrend;
	result->adl = pHisData->m_dmIndex.m_lADL;
}

static void PackTTcpLonHisZHISHU(TTCPLONHISZHISHU *unpack, PTTCPLONHISZHISHU *pack)
{
	short2byte(unpack->ups, pack->ups);
	short2byte(unpack->downs, pack->downs);
	short2byte(unpack->ahead, pack->ahead);
	short2byte(unpack->dkzb, pack->dkzb);
	short2byte(unpack->qrd, pack->qrd);
	int2byte(unpack->adl, pack->adl);
}

static void PackLonInfo(TLONINFO *unpack, PTLONINFO *pack)
{
	int	i;

	int2byte(unpack->date, pack->date);
	memcpy(pack->null, unpack->null, 128);
	for(i = 0; i < BLOCKNUM; i++) {
		short2byte(unpack->kindinfo[i].kind, pack->kindinfo[i].kind);
		short2byte(unpack->kindinfo[i].num, pack->kindinfo[i].num);
		short2byte(unpack->kindinfo[i].index, pack->kindinfo[i].index);
		short2byte(unpack->kindinfo[i].pricescale, pack->kindinfo[i].pricescale);
		short2byte(unpack->kindinfo[i].minall, pack->kindinfo[i].minall);
		short2byte(unpack->kindinfo[i].minnow, pack->kindinfo[i].minnow);
		short2byte(unpack->kindinfo[i].opentime1, pack->kindinfo[i].opentime1);
		short2byte(unpack->kindinfo[i].closetime1, pack->kindinfo[i].closetime1);
		short2byte(unpack->kindinfo[i].opentime2, pack->kindinfo[i].opentime2);
		short2byte(unpack->kindinfo[i].closetime2, pack->kindinfo[i].closetime2);
	}
}

static void PackLonnow(TLONNOW *unpack, PTLONNOW *pack)
{
	memcpy(pack->code, unpack->code, STKCODE_LEN);
	memcpy(pack->name, unpack->name, STKNAME_LEN);
	pack->kind = unpack->kind;
	pack->xflag = unpack->xflag;
	int2byte(unpack->close_p, pack->close_p);
	int2byte(unpack->open_p, pack->open_p);
	int2byte(unpack->high_p, pack->high_p);
	int2byte(unpack->low_p, pack->low_p);
	int2byte(unpack->last_p, pack->last_p);
	int2byte(unpack->total_h, pack->total_h);
	float2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->last_h, pack->last_h);
	short2byte(unpack->per_h, pack->per_h);
	int2byte(unpack->p1, pack->p1);
	int2byte(unpack->q1, pack->q1);
	int2byte(unpack->p2, pack->p2);
	int2byte(unpack->q2, pack->q2);
	int2byte(unpack->p3, pack->p3);
	int2byte(unpack->q3, pack->q3);
	int2byte(unpack->p4, pack->p4);
	int2byte(unpack->q4, pack->q4);
	int2byte(unpack->p5, pack->p5);
	int2byte(unpack->q5, pack->q5);
	int2byte(unpack->p6, pack->p6);
	int2byte(unpack->q6, pack->q6);
}

static void PackRealLoninfo(TREALLONINFO *unpack, PTREALLONINFO *pack)
{       
	short2byte(unpack->kind, pack->kind);
	short2byte(unpack->minnow, pack->minnow);
}

static void iGenerizeTTCPLONDAY(TTCPLONDAY *result, StockDay* londay)
{
	result->time = londay->m_lDate;
	result->openprice = londay->m_lOpenPrice;
	result->highprice = londay->m_lMaxPrice;
	result->lowprice = londay->m_lMinPrice;
	result->closeprice = londay->m_lClosePrice;
	result->total_m = londay->m_lMoney;
	result->total_h = londay->m_lTotal;
}

static void PackTTCPLonDay(TTCPLONDAY *unpack, PTTCPLONDAY *pack)
{
	int2byte(unpack->openprice, pack->openprice);
	int2byte(unpack->total_h, pack->total_h);
	int2byte(unpack->total_m, pack->total_m);
	int2byte(unpack->highprice, pack->highprice);
	int2byte(unpack->lowprice, pack->lowprice);
	int2byte(unpack->closeprice, pack->closeprice);
	int2byte(unpack->time, pack->time);
}

static void iGenerizeTTCPLONDAYGZ(TTCPLONDAYGZ *result, StockDay* londay)
{
	iGenerizeTTCPLONDAY(&result->tcplonday, londay);
	result->gzlx = londay->m_lNationalDebtRatio;
}

static void PackTTCPLonDayGZ(TTCPLONDAYGZ *unpack, PTTCPLONDAYGZ *pack)
{
	PackTTCPLonDay(&unpack->tcplonday, &pack->pttcplonday);
	int2byte(unpack->gzlx, pack->gzlx);
}

static void iGenerizeTTCPLONDAYCOMP(TTCPLONDAYCOMP *result, StockDay* londay, int pscale)
{
	if (pscale < 0)
	{
		result->openprice = (unsigned short)(londay->m_lOpenPrice << -pscale);
		result->highprice = (unsigned short)(londay->m_lMaxPrice << -pscale);
		result->lowprice = (unsigned short)(londay->m_lMinPrice << -pscale);
		result->closeprice = (unsigned short)(londay->m_lClosePrice << -pscale);
	}
	else
	{
		result->openprice = (unsigned short)(londay->m_lOpenPrice >> pscale);
		result->highprice = (unsigned short)(londay->m_lMaxPrice >> pscale);
		result->lowprice = (unsigned short)(londay->m_lMinPrice >> pscale);
		result->closeprice = (unsigned short)(londay->m_lClosePrice >> pscale);
	}
	result->time = londay->m_lDate;
	result->total_h = londay->m_lTotal;
}

static void PackTTCPLonDayCOMP(TTCPLONDAYCOMP *unpack, PTTCPLONDAYCOMP *pack)
{
	short2byte(unpack->openprice, pack->openprice);
	int2byte(unpack->total_h, pack->total_h);
	short2byte(unpack->highprice, pack->highprice);
	short2byte(unpack->lowprice, pack->lowprice);
	short2byte(unpack->closeprice, pack->closeprice);
	int2byte(unpack->time, pack->time);
}

static void iGenerizeTTCPLONDAYCOMPGZ(TTCPLONDAYCOMPGZ *result, StockDay* londay, int pscale)
{
	iGenerizeTTCPLONDAYCOMP(&result->tcplondaycomp, londay, pscale);
	result->gzlx = londay->m_lNationalDebtRatio;
}

static void PackTTCPLonDayCOMPGZ(TTCPLONDAYCOMPGZ *unpack, PTTCPLONDAYCOMPGZ *pack)
{
	PackTTCPLonDayCOMP(&unpack->tcplondaycomp, &pack->pttcplondaycomp);
	int2byte(unpack->gzlx, pack->gzlx);
}

static void PackTDAYHEADER(TDAYHEADER *unpack, PTDAYHEADER *pack)
{
	short2byte(unpack->headsig, pack->headsig);
	int2byte(unpack->icode, pack->icode);
	short2byte(unpack->len, pack->len);
	short2byte(unpack->pscale, pack->pscale);
}


#pragma	pack()

#endif
