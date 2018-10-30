/*******************************************************************************
* Copyright (c)2003, Ѷ��������޹�˾
* All rights reserved.
*
* �ļ����ƣ�HsStruct.h
* �ļ���ʶ��ͨѶ�����ṹ
* ժ    Ҫ��ͨѶ�����ṹ
*
* ��ǰ�汾��xfd2003
* ��    �ߣ�Ѷ��������޹�˾
* ������ڣ�2003-07
*
* ��    ע��
*
* �޸ļ�¼��
*
*	��	  �ڣ�2004��2��26��
*	��	  �ߣ�Ѷ��������޹�˾
*	�޸����ݣ��������µĹ�Ʊ����KIND_PLACE���µ��г�����STOCK_WHILOM_NAME_MARKET
*
*	��	  �ڣ�2004��2��27��
*	��	  �ߣ�Ѷ��������޹�˾
*	�޸����ݣ���StockTick�ṹ˵�������е�ԭ�ڻ���m_nChiCangLiang�ֶο�������������Ʊ�ĵ��ʳɽ�������
*			  ��StockOtherData�ṹ˵��������ԭ�ڻ���m_lKaiCang�ֶο�������������Ʊ�ĵ��ʳɽ�������
*******************************************************************************/
#ifndef HS_STRUCT_H
#define HS_STRUCT_H

#include "time.h"
#include "computer_intel_convert.h"

/* 
ע�⣺HS_SUPPORT_UNIX ��ǰͷ�ļ��Ƿ�ʹ���ڷ�������
*/
//#define HS_SUPPORT_UNIX
#pragma pack(1)
#ifndef HS_SUPPORT_UNIX
#pragma	pack(1)
#else
#endif
/*
�г�����壺
��λ�����ʾ���£�
15		   12		8					0
|			|	  	  |					|
| ���ڷ���	|�г����� |	����Ʒ�ַ���	|
*/
typedef short HSMarketDataType;			  // �г�������������
/*���ڴ���*/
#define STOCK_MARKET			 0X1000   // ��Ʊ
#	define SH_BOURSE			 0x0100   // �Ϻ�
#	define SZ_BOURSE			 0x0200   // ����
#	define SYSBK_BOURSE			 0x0400   // ϵͳ���
#	define USERDEF_BOURSE		 0x0800   // �Զ��壨��ѡ�ɻ����Զ����飩
#			define KIND_INDEX		 0x0000   // ָ�� 
#			define KIND_STOCKA		 0x0001   // A�� 
#			define KIND_STOCKB		 0x0002   // B�� 
#			define KIND_BOND		 0x0003   // ծȯ
#			define KIND_FUND		 0x0004   // ����
#			define KIND_THREEBOAD	 0x0005   // ����
#			define KIND_SMALLSTOCK	 0x0006   // ��С�̹�
#			define KIND_PLACE		 0x0007	  // ����
#			define KIND_LOF			 0x0008	  // LOF
#			define KIND_ETF			 0x0009   // ETF
#			define KIND_QuanZhen	 0x000A   // Ȩ֤

#			define KIND_OtherIndex	 0x000E   // ������������࣬��:����ָ��

#			define SC_Others		 0x000F   // ���� 0x09
#			define KIND_USERDEFINE	 0x0010   // �Զ���ָ��

// �۹��г�
#define HK_MARKET				 0x2000 // �۹ɷ���
#	define HK_BOURSE			 0x0100 // �����г�
#	define	GE_BOURSE			 0x0200 // ��ҵ���г�(Growth Enterprise Market)
#	define	INDEX_BOURSE		 0x0300	// ָ���г�	
#		define HK_KIND_INDEX			 0x0000   // ��ָ
#		define HK_KIND_FUTURES_INDEX	 0x0001   // ��ָ
//#		define	KIND_Option				 0x0002	  // �۹���Ȩ

#	define SYSBK_BOURSE			 0x0400 // �۹ɰ��(H��ָ���ɷݹɣ���ɫK��ָ���ɷݹɣ���
#	define USERDEF_BOURSE		 0x0800 // �Զ��壨��ѡ�ɻ����Զ����飩
#			define HK_KIND_BOND		 0x0000   // ծȯ
#			define HK_KIND_MulFund	 0x0001   // һ�����Ϲ�֤
#			define HK_KIND_FUND		 0x0002   // ����
#			define KIND_WARRANTS	 0x0003   // �Ϲ�֤
#			define KIND_JR			 0x0004   // ����
#			define KIND_ZH			 0x0005   // �ۺ�
#			define KIND_DC			 0x0006   // �ز�
#			define KIND_LY			 0x0007   // ����
#			define KIND_GY			 0x0008   // ��ҵ
#			define KIND_GG			 0x0009   // ����
#			define KIND_QT			 0x000A   // ����

/*�ڻ�����*/
#define FUTURES_MARKET			 0x4000 // �ڻ�
#		define DALIAN_BOURSE		 0x0100	// ����
#				define KIND_BEAN		 0x0001	// ����
#				define KIND_YUMI		 0x0002	// ��������
#				define KIND_SHIT		 0x0003	// ����ʳ��
#				define KIND_DZGY		 0x0004	// ���ڹ�ҵ1
#				define KIND_DZGY2		 0x0005	// ���ڹ�ҵ2
#				define KIND_DOUYOU		 0x0006	// ������
#				define KIND_JYX			 0x0007	// ����ϩ
#				define KIND_ZTY			 0x0008	// �����

#		define SHANGHAI_BOURSE	  0x0200	// �Ϻ�
#				define KIND_METAL		 0x0001	// �Ϻ�����
#				define KIND_RUBBER		 0x0002	// �Ϻ���
#				define KIND_FUEL		 0x0003	// �Ϻ�ȼ��
//#				define KIND_GUZHI		 0x0004	// ��ָ�ڻ�
#				define KIND_QHGOLD		 0x0005	// �Ϻ��ƽ�

#		define ZHENGZHOU_BOURSE	  0x0300	// ֣��
#				define KIND_XIAOM		 0x0001	// ֣��С��
#				define KIND_MIANH		 0x0002	// ֣���޻�
#				define KIND_BAITANG		 0x0003	// ֣�ݰ���
#				define KIND_PTA			 0x0004	// ֣��PTA
#				define KIND_CZY			 0x0005	// ������

#		define HUANGJIN_BOURSE	  0x0400		// �ƽ�����
#				define KIND_GOLD		 0x0001	// �Ϻ��ƽ�

#		define GUZHI_BOURSE		  0x0500		// ��ָ�ڻ�
#				define KIND_GUZHI		 0x0001	// ��ָ�ڻ�

#		define SELF_BOURSE		  0x0600	// �Զ�������

#		define DZGT_BOURSE		  0x0610	// ���ڸ�������

/*���̴���*/
#define WP_MARKET				 ((HSMarketDataType)0x5000) // ����
#		define WP_INDEX				0x0100	// ����ָ�� // ������
#		define WP_INDEX_RJ	 		0x0001 //"�վ�";
#		define WP_INDEX_HZ	 		0x0002 //"��ָ";
#		define WP_INDEX_NH	 		0x0003 //"�Ϻ��ۺ�";
#		define WP_INDEX_TG	 		0x0004 //"̨�ɼ�Ȩ";
#		define WP_INDEX_XG	 		0x0005 //"�ǹɺ�Ͽ";
#		define WP_INDEX_MG	 		0x0006 //"����ۺ�";
#		define WP_INDEX_TGZH 		0x0007 //"̩���ۺ�";
#		define WP_INDEX_YN 		    0x0008 //"ӡ���ۺ�";
#		define WP_INDEX_AZ 		    0x0009 //"�����ۺ�";
#		define WP_INDEX_NXL  		0x000a //"Ŧ����";
#		define WP_INDEX_SGX         0x000b //"SGXĦ̨";
#		define WP_INDEX_SENSEX      0x000c //"ӡSENSEX";
#		define WP_INDEX_KOSPI       0x000d //"KOSPI200";
#		define WP_INDEX_DQGY        0x000e //"����ҵ";
#		define WP_INDEX_DQYS        0x000f //"��������";
#		define WP_INDEX_DQGG        0x0010 //"������";
#		define WP_INDEX_NSDK        0x0011 //"��˹���"
#		define WP_INDEX_BZPE        0x0012 //"��׼�ն�"
#		define WP_INDEX_CRBYX       0x0013 //"CRB����"
#		define WP_INDEX_CRBZS       0x0014 //"CRBָ��"
#		define WP_INDEX_JND         0x0015 //"���ô�"
#		define WP_INDEX_FS100       0x0016 //"��ʱ100"
#		define WP_INDEX_FACAC       0x0017 //"��CAC40"
#		define WP_INDEX_DEDAX       0x0018 //"��DAX"
#		define WP_INDEX_HEAEX       0x0019 //"����AEX"
#		define WP_INDEX_DMKFX       0x001a //"����KFX"
#		define WP_INDEX_BLS         0x001b //"����ʱ"
#		define WP_INDEX_RSSSMI      0x001c //"��ʿSSMI"
#		define WP_INDEX_BXBVSP      0x001d //"����BVSP"
#		define WP_INDEX_BDI         0x001e //"BDIָ��"
#		define WP_INDEX_BP100       0x001f //"����100"
#		define WP_INDEX_ERTS        0x0020 //"��RTS"
#		define WP_INDEX_YFTMIB      0x0021 //"��FTMIB"
#		define WP_LME				0x0200	// LME		// ������
#			define WP_LME_CLT			0x0210 //"����ͭ";
#			define WP_LME_CLL			0x0220 //"������";
#			define WP_LME_CLM			0x0230 //"������";
#			define WP_LME_CLQ			0x0240 //"����Ǧ";
#			define WP_LME_CLX			0x0250 //"����п";
#			define WP_LME_CWT			0x0260 //"������";
#			define WP_LME_CW			0x0270 //"����";
#			define WP_LME_SUB			0x0000

#			define WP_CBOT				0x0300	// CBOT			
#			define WP_NYMEX	 			0x0400	// NYMEX	 	
#			define WP_NYMEX_YY			0x0000	//"ԭ��";
#			define WP_NYMEX_RY			0x0001	//"ȼ��";
#			define WP_NYMEX_QY			0x0002	//"����";

#			define WP_COMEX	 			0x0500	// COMEX	 	
#			define WP_TOCOM	 			0x0600	// TOCOM	 	
#			define WP_IPE				0x0700	// IPE			
#			define WP_NYBOT				0x0800	// NYBOT		
#			define WP_NOBLE_METAL		0x0900	// �����	
#			  define WP_NOBLE_METAL_XH	0x0000  //"�ֻ�";
#			  define WP_NOBLE_METAL_HJ	0x0001  //"�ƽ�";
#			  define WP_NOBLE_METAL_BY	0x0002  //"����";

#			define WP_FUTURES_INDEX		0x0a00	// ��ָ
#			define WP_SICOM				0x0b00	// SICOM		
#			define WP_LIBOR				0x0c00	// LIBOR		
#			define WP_NYSE				0x0d00	// NYSE
#			define WP_CEC				0x0e00	// CEC


#			define WP_Other_TZTHuanjin	0x0F10	// �ƽ��ڻ���������,����������
#			define WP_Other_JinKaiXun	0x0F20	// ��Ѷ������
#			define WP_JKX               WP_Other_JinKaiXun
#			define WP_XJP               0x0F30	// �¼�������



/*������*/
#define FOREIGN_MARKET			 ((HSMarketDataType)0x8000) // ���
#	define WH_BASE_RATE			0x0100	// ��������
#	define WH_ACROSS_RATE		0x0200	// �������
#		define FX_TYPE_AU 			0x0000 // AU	��Ԫ
#		define FX_TYPE_CA 			0x0001 // CA	��Ԫ
#		define FX_TYPE_CN 			0x0002 // CN	�����
#		define FX_TYPE_DM 			0x0003 // DM	���
#		define FX_TYPE_ER 			0x0004 // ER	ŷԪ	 
#		define FX_TYPE_HK 			0x0005 // HK	�۱�
#		define FX_TYPE_SF 			0x0006 // SF	��ʿ 
#		define FX_TYPE_UK 			0x0007 // UK	Ӣ��
#		define FX_TYPE_YN 			0x0008 // YN	��Ԫ

#	define WH_FUTURES_RATE			0x0300  // �ڻ�


/*������*/
#define HJ_MARKET			 ((HSMarketDataType)0x6000) // �ƽ�
#	define HJ_SH_CURR			0x0100	// �Ϻ�����
#	define HJ_SH_QH		        0x0200	// �Ϻ��ڻ�
#	define HJ_WORLD	        0x0300	// �����г�
#	define HJ_OTHER	        0x0400	// �����г�

// �ڲ����࣬����Ʊ��������
#define STOCK_WHILOM_NAME_MARKET ((HSMarketDataType)0xF000)


//#define	MakeMarket(x)			((HSMarketDataType)((x) & 0xF000))
//#define MakeMainMarket(x)		((HSMarketDataType)((x) & 0xFFF0))
//#define	MakeMidMarket(x)		((HSMarketDataType)((x) & 0x0F00)) // ����ڶ�λ

static int	MakeMarket(HSMarketDataType x)
{
	return ((HSMarketDataType)((x) & 0xF000));
}
static int  MakeMainMarket(HSMarketDataType x)
{
	return ((HSMarketDataType)((x) & 0xFF00));
}
static int	MakeMidMarket(HSMarketDataType x)
{
	return ((HSMarketDataType)((x) & 0x0F00)); // ����ڶ�λ
}


//#define MakeSubMarket(x)		((HSMarketDataType)((x) & 0x000F))
static int MakeSubMarket(HSMarketDataType x)
{
	if (MakeMainMarket(x) == (WP_MARKET | WP_INDEX))
		return ((HSMarketDataType)((x) & 0x00FF));
	else
		return ((HSMarketDataType)((x) & 0x000F));
}

//#define MakeHexSubMarket(x)		( (HSMarketDataType)((x) & 0x000F) )
//#define MakeSubMarketPos(x)		( ((MakeHexSubMarket(x) / 16) * 10) + (MakeHexSubMarket(x) % 16) )

static int MakeHexSubMarket(HSMarketDataType x)
{
	return ( (HSMarketDataType)((x) & 0x000F) );
}

static int MakeSubMarketPos(HSMarketDataType x)
{
	if (MakeMainMarket(x) == (WP_MARKET | WP_INDEX))
		return MakeSubMarket(x);
	return ( ((MakeHexSubMarket(x) / 16) * 10) + (MakeHexSubMarket(x) % 16) );
}

// �Ƿ�Ϊ���ڹ�Ʊָ��
//#define MakeIndexMarket(x)		( (MakeMarket(x) == STOCK_MARKET) && (MakeSubMarket(x) == KIND_INDEX))
static int MakeIndexMarket(HSMarketDataType x)
{
	return ( (MakeMarket(x) == STOCK_MARKET) &&
			 (MakeMidMarket(x) != 0) &&
		     ((MakeSubMarket(x) == KIND_INDEX) ||
			 (MakeSubMarket(x) == KIND_OtherIndex)));
}

static int MakeIndexSelf(HSMarketDataType x)
{
	return ( (MakeMarket(x) == STOCK_MARKET) &&
			 (MakeMidMarket(x) != 0) &&
		     ((MakeSubMarket(x) == KIND_OtherIndex)));
}

// �Ƿ�Ϊ����
static int MakeFundMarket(HSMarketDataType x)
{
	return ( (MakeMarket(x) == STOCK_MARKET) &&
			 (MakeMidMarket(x) != 0) &&
		     (MakeSubMarket(x) == KIND_FUND) );
}

// �Ƿ�Ϊ�۹�ָ��
//#define MakeHKIndex(x)          ( MakeMainMarket(x) == (HK_MARKET | INDEX_BOURSE) )
static int MakeHKIndex(HSMarketDataType x)
{
	return ( MakeMainMarket(x) == (HK_MARKET | INDEX_BOURSE) );
}

// �Ƿ�Ϊ��ָ�ڻ�
static int MakeGZIndex(HSMarketDataType x)
{
	return ( (MakeMainMarket(x) == (FUTURES_MARKET | GUZHI_BOURSE)) &&
		     (MakeSubMarket(x) == KIND_GUZHI) );
}

// �Ƿ�Ϊ�ƽ��ڻ�
/*static int MakeGoldIndex(HSMarketDataType x)
{
	if (MakeMainMarket(x) = (HJ_MARKET | HJ_SH_CURR) ||  MakeMainMarket(x) = (HJ_MARKET | HJ_SH_QH))
	{
		return 1;
	}

	return ( (MakeMainMarket(x) == (FUTURES_MARKET | HUANGJIN_BOURSE)) && (MakeSubMarket(x) == KIND_GOLD) );
}
*/
// �Ƿ�Ϊ�ƽ��ڻ�
static int MakeGoldIndex(HSMarketDataType x, char * pszCode)
{
	if ( MakeMainMarket(x) == (HJ_MARKET | HJ_SH_QH))
	{
		return 1;
	}

	if (MakeMainMarket(x) == (HJ_MARKET | HJ_SH_CURR) && pszCode != NULL)
	{
		if (strcmp("AGTD", pszCode) == 0 || strcmp( "AUTD", pszCode) == 0)
		{
			return 1;
		}
	}

	return 0;
}


//yangdl 2008.03.06 ���⴦��۸�
// �Ƿ�Ϊ��Ҫ���⴦��۸�ķ���
static int MakeNegativeIndex(HSMarketDataType x)
{
	return ( (MakeMainMarket(x) == (FOREIGN_MARKET | WH_FUTURES_RATE)) &&
		     ( (MakeSubMarket(x) == FX_TYPE_AU)  || (MakeSubMarket(x) == FX_TYPE_YN)));
}

//#define MakeWPIndex(x)          ( (MakeMainMarket(x) >= (WP_MARKET | WP_INDEX_AZ)) && (MakeMainMarket(x) <= (WP_MARKET | WP_INDEX_MLX)) )
//#define MakeWP_LME(x)           ( (MakeMainMarket(x) >= (WP_MARKET | WP_LME_CLT))  && (MakeMainMarket(x) <= (WP_MARKET | WP_LME_CW)) )
static int MakeWPIndex(HSMarketDataType x)
{
	return ( ((x) >= (WP_MARKET | WP_INDEX)) && ((x) <= (WP_MARKET | WP_INDEX | WP_INDEX_YFTMIB)) );
}

static int MakeWP_LME(HSMarketDataType x)
{
	return ( (MakeMainMarket(x) >= (WP_MARKET | WP_LME_CLT))  && (MakeMainMarket(x) <= (WP_MARKET | WP_LME_CW)) );
}

//#define	WhoMarket(x,y)			( MakeMarket(x) == MakeMarket(y) )
static int	WhoMarket(HSMarketDataType x,HSMarketDataType y)
{
	return ( MakeMarket(x) == MakeMarket(y) );
}

// �Ƿ�Ϊ���ڹ�ƱETF
//#define MakeETF(x)				( (MakeMarket(x) == STOCK_MARKET) && (MakeSubMarket(x) == KIND_ETF))
static int MakeETF(HSMarketDataType x)
{
	return ( (MakeMarket(x) == STOCK_MARKET) && (MakeSubMarket(x) == KIND_ETF));
}


#define SH_Bourse	((HSMarketDataType)(STOCK_MARKET|SH_BOURSE))
#define SZ_Bourse	((HSMarketDataType)(STOCK_MARKET|SZ_BOURSE))

#define ToDataType(x) ((HSMarketDataType)(x))

#ifndef HS_SUPPORT_UNIX
extern UINT HashKey(LPCTSTR key,int nKeyCount,const int nHashTableSize); // ref #include "stockmanager.h"
#endif /*HS_SUPPORT_UNIX*/

#ifdef Support_XHX_Dll 
   #define Negative(x,y)  ( y ? x&0x0FFFFFFF : x )
   #define NegativeFlag(x,y) ( y ? ( ( x&0xF0000000 ) ? 1 : 0 ) : 0  ) 
#else
   #define Negative(x,y)   x
   #define NegativeFlag(x,y) 0
#endif

struct NegativeValue
{
	DWORD m_lValue:28;
	DWORD m_lFlag:4;
};

struct NegativeData
{
	union
	{
		DWORD		  m_keyValue;		
		NegativeValue m_Value;
	};
};
// use
// NegativeData data;
// data.m_Value.m_lValue = 123; // ʵ����ֵ
// data.m_Value.m_lFlag  = 1;   // ���� 0�����ţ�1������

#define PYJC_MAX_LENGTH		16			// ƴ������
#define STOCK_NAME_SIZE		16			// ��Ʊ���Ƴ���
#define STOCK_CODE_SIZE		6			// ��Ʊ���Ƴ���
// ��Ʊ����ṹ
struct CodeInfo
{
	HSMarketDataType	m_cCodeType;	// ֤ȯ����
	char				m_cCode[STOCK_CODE_SIZE];		// ֤ȯ����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_cCodeType = YlsShortIntelToComputer(m_cCodeType);
		}
		else
		{
			m_cCodeType = YlsShortComputerToIntel(m_cCodeType);
		}
#endif
	}

#ifndef HS_SUPPORT_UNIX

#ifndef _WIN32_WCE
	CodeInfo()
	{
		memset(this,0,sizeof(CodeInfo));
	}

	CodeInfo(HSMarketDataType cCodeType,CString cCode)
	{
		m_cCodeType = cCodeType;
		strncpy(m_cCode,cCode,sizeof(m_cCode));
	}

	// ������ϣ��, ���ع�ϣ����
	long GetLongKey(int nHashTableSize = 999999)
	{
		return HashKey(m_cCode,STOCK_CODE_SIZE,nHashTableSize);
	}

	// �Ƚ�����	����TRUE or FALSE
	BOOL IsType(HSMarketDataType cType)
	{
		return (MakeSubMarket(m_cCodeType) == cType);
	}

	// ���ع�Ʊ����
	LPCTSTR GetKey(char* strKey) // strKey > 9
	{
		strncpy(strKey,m_cCode,STOCK_CODE_SIZE);
		strKey[STOCK_CODE_SIZE] = '\0';

		return strKey;
	}
	// ���ع�Ʊ����
	LPCTSTR GetKey()
	{
		static char strKey[STOCK_CODE_SIZE+1];
		strncpy(strKey,m_cCode,STOCK_CODE_SIZE);
		strKey[STOCK_CODE_SIZE] = '\0';

		return strKey;
	}

	// ������ ��������
	void operator=(CodeInfo* pInfo)
	{
		if(pInfo != NULL)
		{
			memcpy(this,pInfo,sizeof(CodeInfo));
		}
	}
	// ������ ��������
	void operator=(CodeInfo pInfo)
	{
		memcpy(this,&pInfo,sizeof(CodeInfo));		
	}

#endif

	// ���ش���
	CString GetCode()
	{
		return CString(m_cCode).Left(STOCK_CODE_SIZE);
	}

	// ȡ�ô���, �����4λ, Ҳ��������λ����
	CString GetFindCode()
	{
		switch(MakeMainMarket(m_cCodeType))
		{
		case SH_Bourse:
			return CString(m_cCode).Left(STOCK_CODE_SIZE);
		case SZ_Bourse:
			return CString(m_cCode).Mid(2,4);
		default:
			break;
		}
		return CString(m_cCode).Left(STOCK_CODE_SIZE);
	}		
#endif

};

//��Ʊ��ϸ��Ϣ
struct StockUserInfo
{
	CodeInfo	m_ciStockCode;		//��Ʊ����ṹ
	char		m_cStockName[STOCK_NAME_SIZE];	//��Ʊ����
	char		m_cStockPYJC[PYJC_MAX_LENGTH];	//ƴ�����
	long		m_lPrevClose;		 //����
	long		m_lPrevSettle;		 //���
	unsigned long		m_l5DayVol;			//������
#ifndef HS_SUPPORT_UNIX
	//ȡ�ù�Ʊ����
	CString			GetKey();
	virtual CString	GetName()
	{
		// Modified by Ben 20101126 for satisfing the requirement by XiaMeng Bank

		static char s_strName[STOCK_NAME_SIZE+1];
		s_strName[STOCK_NAME_SIZE] = '\0';
	
		if (m_ciStockCode.GetCode() == "5120")
		{
			strcpy(s_strName, "�ֻ��ƽ�");			
		}
		else if(m_ciStockCode.GetCode() == "5121")
		{
			strcpy(s_strName, "�ֻ�����");
		}
		else if(m_ciStockCode.GetCode() == "5122")
		{
			strcpy(s_strName, "�ֻ�����");
		}
		else if(m_ciStockCode.GetCode() == "5123")
		{
			strcpy(s_strName, "�ֻ��ٽ�");
		}
		else
		{
			memcpy(s_strName, m_cStockName, STOCK_NAME_SIZE);
		}
		// end mod
		return s_strName;
	}
	//ȡ��ƴ�����
	//CString		GetPyjc();

#ifndef _WIN32_WCE
	CString		GetPyjc();
#else
	CString		GetPyjc()
	{
		return CString(m_cStockPYJC).Left(sizeof(m_cStockPYJC));
	}
#endif

	CString		GetCode() { return m_ciStockCode.GetCode(); }

	// ���ҹ�Ʊ����������ƻ���ƴ�����
	int  IsFind(const char* strKey,int& nUnique,int& nStart,int& nEnd);
	int  IsFind(CString& strKey,int& nUnique,int& nStart,int& nEnd);

	// ���αȽϹ�Ʊ����,����,ƴ�����
	int  Compare(const unsigned char* pData, const unsigned char* strKey,
		int& nStart,int& nEnd);
	int  Compare(CString& strKey,int& nStart,int& nEnd);

	virtual void Copy(StockUserInfo* pStock)
	{
		if( pStock )
		{
			m_ciStockCode = pStock->m_ciStockCode;		//��Ʊ����ṹ
			strncpy(m_cStockName,pStock->m_cStockName,sizeof(m_cStockName)) ;	    //��Ʊ����
			strncpy(m_cStockPYJC,pStock->m_cStockPYJC,sizeof(m_cStockPYJC)) ;	    //ƴ�����
			//m_cStockPYJC  = pStock->m_cStockPYJC;
			m_lPrevClose  = pStock->m_lPrevClose ;		//����
			m_l5DayVol    = pStock->m_l5DayVol   ;		//������
		}
	}

	//���л�
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);
#else
	virtual void Serialize(CArchive& ar)
	{
		if( ar.IsStoring() )
		{
			ar << m_ciStockCode.m_cCodeType;			// ֤ȯ����
			ar << m_ciStockCode.GetCode();
			ar << GetName();
			ar << GetPyjc();
			ar << m_lPrevClose;
			ar << m_l5DayVol;
		}
		else
		{
			ar >> m_ciStockCode.m_cCodeType;			// ֤ȯ����
			CString str;
			ar >> str;
			WideCharToMultiByte(CP_ACP, 0, str, -1, m_ciStockCode.m_cCode, sizeof(m_ciStockCode.m_cCode), NULL, NULL);
			//strncpy(m_ciStockCode.m_cCode,str,sizeof(m_ciStockCode.m_cCode));
			ar >> str;
			WideCharToMultiByte(CP_ACP, 0, str, -1, m_cStockName, sizeof(m_cStockName), NULL, NULL);
			//strncpy(m_cStockName,str,sizeof(m_cStockName));

			//ar >> m_cStockPYJC;
			ar >> str;
			WideCharToMultiByte(CP_ACP, 0, str, -1, m_cStockPYJC, sizeof(m_cStockPYJC), NULL, NULL);
			//strncpy(m_cStockPYJC,str,sizeof(m_cStockPYJC));
			ar >> m_lPrevClose;
			ar >> m_l5DayVol;
		}
	}
#endif

#endif /*HS_SUPPORT_UNIX*/
};

static bool IsValidDate(unsigned long lDate)
{
	int year,month,day;
	year = lDate /10000;
	month = (lDate / 100) % 100;
	day = lDate % 100;

	if (year < 1900 || year > 2100 || month <= 0 || month > 12 || day <= 0 || day > 31)
	{
		return false;
	}

	if (month <= 12 && day <= 31) 
	{ 
		if ( year % 1000 == 0 && year % 400 == 0 && month == 2 && day == 29) 
			return true; 
		else if ((month==1||month==3||month==5||month==7||month==8||month==10||month==12) && (day >= 30)) return true; 
		else if ((month==4||month==6||month==9||month==11) && day == 30 ) return true;
		else if (day < 30) return true;
		else 
			return false;
	} 
	else 
		return false; 

}

static bool IsValidDateTime(unsigned long lTime)
{
	int year,month,day,nHou,nMin;
	year = lTime /100000000 + 1990;
	month = (lTime / 1000000) % 100;
	day = (lTime / 10000) % 100;

	int nDate = year * 10000 + month * 100 + day;
	if (IsValidDate(nDate))
	{
		nHou = (lTime / 100) % 100;
		nMin = lTime % 100;

		if (nHou >= 0 && nHou <= 24 && nMin >= 0 && nMin <= 60)
			return true;
	}
	return false;
}

static int IsValidMarket(CodeInfo * pstCode)
{
	if ((MakeMarket(pstCode->m_cCodeType) == STOCK_MARKET) || 
		(MakeMarket(pstCode->m_cCodeType) == FUTURES_MARKET)|| 
		(MakeMarket(pstCode->m_cCodeType) == WP_MARKET)|| 
		(MakeMarket(pstCode->m_cCodeType) == FOREIGN_MARKET) || 
		(MakeMarket(pstCode->m_cCodeType) == HJ_MARKET) )
	{
		for (int i = 0; i < STOCK_CODE_SIZE; i ++)
		{
			char c = pstCode->m_cCode[i];
			if ((c  >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || 
				(c >= 'A' && c <= 'Z') || (i > 2 && c == 0))
			{
				continue;;
			}
			else
			{
				return 0;
			}
		}
		return 1;
	}

	return 0;
}

//yangdl 2007.09.24 �����µ�
struct StockKsXdInfo
{
	BYTE m_nXd;
    StockUserInfo m_StockUser;
	float m_nPrice;
	DWORD m_nAmount;
};

//֤ȯ��Ϣ
struct HSTypeTime
{
	short	m_nOpenTime;	// ǰ����ʱ��
	short	m_nCloseTime;	// ǰ����ʱ��

	short   GetDist() { return (m_nCloseTime - m_nOpenTime); }

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nOpenTime = YlsShortIntelToComputer(m_nOpenTime);
			m_nCloseTime = YlsShortIntelToComputer(m_nCloseTime);
		}
		else
		{
			m_nOpenTime = YlsShortComputerToIntel(m_nOpenTime);
			m_nCloseTime = YlsShortComputerToIntel(m_nCloseTime);
		}
#endif
	}
};

struct  HSTypeTime_Unoin
{
	short	m_nAheadOpenTime;	// ǰ����ʱ��
	short	m_nAheadCloseTime;	// ǰ����ʱ��
	short	m_nAfterOpenTime;	// ����ʱ��
	short	m_nAfterCloseTime;	// �����ʱ��

	HSTypeTime	m_nTimes[9];	// �¼������α߽�,���߽�Ϊ-1ʱ��Ϊ��Ч����

	HSTypeTime	m_nPriceDecimal;   // С��λ, < 0

	// ��һ����Ч���κ���������ȫΪ��Ч��
};

// ��Ʊ��������
struct StockTypeName 
{
	char m_szName[20];	// ��Ʊ��������
};

struct StockType
{
	StockTypeName m_stTypeName;	// ��Ӧ���������

	short   m_nStockType;		// ֤ȯ����
	short   m_nTotal;			// ֤ȯ����
	short   m_nOffset;			// ƫ����
	short   m_nPriceUnit;		// �۸�λ
	short   m_nTotalTime;		// �ܿ���ʱ�䣨���ӣ�
	short   m_nCurTime;			// ����ʱ�䣨���ӣ�

	union
	{
		HSTypeTime		 m_nNewTimes[11];
		HSTypeTime_Unoin m_union;
	};

#ifndef HS_SUPPORT_UNIX
	StockType()
	{
		memset(this,0,sizeof(StockType));
	}
#endif

	BOOL IsInitTime(int nTimer,int nDist = 10)
	{
		return ( nTimer >= (m_nNewTimes->m_nOpenTime - nDist) && nTimer < m_nNewTimes->m_nOpenTime );
	}

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nStockType = YlsShortIntelToComputer(m_nStockType);
			m_nTotal = YlsShortIntelToComputer(m_nTotal);
			m_nOffset = YlsShortIntelToComputer(m_nOffset);
			m_nPriceUnit = YlsShortIntelToComputer(m_nPriceUnit);
			m_nTotalTime = YlsShortIntelToComputer(m_nTotalTime);
			m_nCurTime = YlsShortIntelToComputer(m_nCurTime);
		}
		else
		{
			m_nStockType = YlsShortComputerToIntel(m_nStockType);
			m_nTotal = YlsShortComputerToIntel(m_nTotal);
			m_nOffset = YlsShortComputerToIntel(m_nOffset);
			m_nPriceUnit = YlsShortComputerToIntel(m_nPriceUnit);
			m_nTotalTime = YlsShortComputerToIntel(m_nTotalTime);
			m_nCurTime = YlsShortComputerToIntel(m_nCurTime);
		}

		for( int i = 0; i < 12; i++ )
		{
			m_nNewTimes[i].To(cIntelToComputer);
		}
#endif
	}
};

#define STOCKTYPE_COUNT 60
// �г���Ϣ�ṹ(�ͻ��˱���ʹ��)
struct BourseInfo
{
	StockTypeName	m_stGroupName;	// �г�����(��Ӧ�г����)
	short			m_nMarketType;	// �г����(�����λ)

	unsigned int	m_dwCRC;		// CRCУ���루�г���

	long			m_lDate;		// �������ڣ�19971230��

	//char  m_cVersion;			    /* �汾�ţ�= 'A' ��ʾ���汾������	Ϊ�ϰ汾*/	
	//short m_nSize;				// ���ṹ�ĳ���

	short  m_cType;				// ��Ч��֤ȯ���͸���

	StockType		 m_stNewType[STOCKTYPE_COUNT];	// ֤ȯ��Ϣ
	StockTypeName	 m_stTypeName[STOCKTYPE_COUNT]; // ��Ӧ������
	int				 m_nMenuID[STOCKTYPE_COUNT];    // ��Ӧ�Ĳ˵�id

#ifndef HS_SUPPORT_UNIX
	BourseInfo()
	{
		memset(this, 0, sizeof(BourseInfo));
		//m_cVersion = 'A';
		//m_nSize    = sizeof(BourseInfo);
	}
#endif
};






// �г���Ϣ�ṹ
struct CommBourseInfo
{
	StockTypeName	m_stTypeName;	// �г�����(��Ӧ�г����)
	short			m_nMarketType;	// �г����(�����λ)

	short			m_cCount;		// ��Ч��֤ȯ���͸���

	long			m_lDate;		// �������ڣ�19971230��
	unsigned int	m_dwCRC;		// CRCУ���루���ࣩ

	StockType		m_stNewType[1];	// ֤ȯ��Ϣ	

#ifndef HS_SUPPORT_UNIX
	CommBourseInfo()
	{
		memset(this, 0, sizeof(CommBourseInfo));
	}
#endif

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nMarketType = YlsShortIntelToComputer(m_nMarketType);
			m_cCount = YlsShortIntelToComputer(m_cCount);
			m_lDate = YlsIntIntelToComputer(m_lDate);
			m_dwCRC = YlsIntIntelToComputer(m_dwCRC);

			for(int i = 0; i < m_cCount; i++ )
			{
				m_stNewType[i].To(cIntelToComputer);
			}
		}
		else
		{
			for(int i = 0; i < m_cCount; i++ )
			{
				m_stNewType[i].To(cIntelToComputer);
			}

			m_nMarketType = YlsShortComputerToIntel(m_nMarketType);
			m_cCount = YlsShortComputerToIntel(m_cCount);
			m_lDate = YlsIntComputerToIntel(m_lDate);
			m_dwCRC = YlsIntComputerToIntel(m_dwCRC);
		}		
#endif
	}
};

// ������֤ȯ�����Ϣ
struct ServerCompare	
{
	HSMarketDataType	m_cBourse;			// ֤ȯ��������
	short				m_nAlignment;    	// Ϊ��4�ֽڶ������ӵ��ֶ�
	unsigned int		m_dwCRC;			// CRCУ����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_cBourse = YlsShortIntelToComputer(m_cBourse);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
			m_dwCRC = YlsIntIntelToComputer(m_dwCRC);
		}
		else
		{
			m_cBourse = YlsShortComputerToIntel(m_cBourse);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
			m_dwCRC = YlsIntComputerToIntel(m_dwCRC);
		}
#endif
	}
};

// ��������
struct SeverCalculateData
{
	//CodeInfo m_sCodeInfo;
	HSMarketDataType	m_cCodeType;	// ֤ȯ����
	char				m_cCode[STOCK_CODE_SIZE];		// ֤ȯ����

	float				m_fUpPrice;     // ��ͣ���
	float				m_fDownPrice;   // ��ͣ���

	void To( char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_cCodeType = YlsShortComputerToIntel(m_cCodeType);

			m_fUpPrice = YlsFloatComputerToIntel(m_fUpPrice);
			m_fDownPrice = YlsFloatComputerToIntel(m_fDownPrice);
		}
		else
		{
			m_cCodeType = YlsShortIntelToComputer(m_cCodeType);

			m_fUpPrice = YlsFloatComputerToIntel(m_fUpPrice);
			m_fDownPrice = YlsFloatComputerToIntel(m_fDownPrice);
		}
#endif
	}
};


// Level 2 ��չ�ľ�̬����
struct LevelStatic
{
	SeverCalculateData m_calc;			// ���������

	float m_fPrice;						// ���Ѓr

	float m_fShareFaceValue;			// ÿ����ֵ

	float m_fOutstandingShares;			// �ܷ�����
	float m_fPublicFloatShareQuantity;	// ��ͨ����

	long  MaturityDate;					// ����/������
	long  CouponPaymentDate;			// ��Ϣ��
	long  LastInterestPaymentDate;		// ��һ�����۸�Ϣ��
	long  NextInterestPaymentDate;		// ��һ�����۸�Ϣ��

	float ConversionPrice;				// ��Ȩ/ת�ɼ۸�
	float m_fCVRatio;					// ��Ȩ����
	long  ConversionPeriod;				// ��Ȩʱ��

	float InterestRate;					// ��������
	float m_fCouponRate;				// Ʊ������
	float ContractMultiplier;			// ծȯ�ۺϳɻع���׼ȯ�ı���
	long  InterestAccrualDate;			// ��Ϣ��
	long  Residualmaturity;			    // ʣ��ʱ��
	float AccruedInterestAmt;			// Ӧ����Ϣ
	
	float RoundLot;						// ���׵�λ

	int	  NoSecurityAltID;				// ��ѡ֤ȯ�������

	char  SecurityAltID[16];			// ��ѡ֤ȯ����
	char  SecurityAltIDSource[16];		// ��ѡ֤ȯ����Դ
	char  SecurityIDSource[16];			// ֤ȯ����Դ
	char  SecurityDesc[16];				// ֤ȯ����

	char  CFICode[4];					// ֤ȯ���
	char  SecurityExchange[4];			// ����������
	char  SecuritySubType[4];			// ֤ȯ�����

	char  m_szIndustryClassification[4];// ��ҵ����
	char  Currency[4];					// ����

	char  SecurityTradingStatus[4];		// ����״̬
	char  m_szCorporateAction[4];		// ��Ȩ��Ϣ��־

	char  CouponRate[4];

	char  BondType[4];					// ծȯ����
	char  American_European;			// ��ʽ/ŷʽ
	char  CallOrPut;					// Call/Put ��־
	char  Underlying[12];				// ����֤ȯ,Ϊ����֤ȯ����
	char  Issuer[16];					// ���л���

	char  m_szResever[10];				// ����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN

		m_calc.To(cIntelToComputer);

		if( cIntelToComputer )
		{					
			m_fPrice = YlsFloatComputerToIntel(m_fPrice);			

			m_fShareFaceValue = YlsFloatComputerToIntel(m_fShareFaceValue);			
			m_fOutstandingShares = YlsFloatComputerToIntel(m_fOutstandingShares);
			m_fPublicFloatShareQuantity = YlsFloatComputerToIntel(m_fPublicFloatShareQuantity);
			ConversionPrice = YlsFloatComputerToIntel(ConversionPrice);
			m_fCVRatio = YlsFloatComputerToIntel(m_fCVRatio);
			InterestRate = YlsFloatComputerToIntel(InterestRate);
			m_fCouponRate = YlsFloatComputerToIntel(m_fCouponRate);
			ContractMultiplier = YlsFloatComputerToIntel(ContractMultiplier);
			AccruedInterestAmt = YlsFloatComputerToIntel(AccruedInterestAmt);
			RoundLot = YlsFloatComputerToIntel(RoundLot);

			MaturityDate = YlsIntComputerToIntel(MaturityDate);
			CouponPaymentDate = YlsIntComputerToIntel(CouponPaymentDate);

			LastInterestPaymentDate = YlsIntComputerToIntel(LastInterestPaymentDate);
			NextInterestPaymentDate = YlsIntComputerToIntel(NextInterestPaymentDate);
			ConversionPeriod = YlsIntComputerToIntel(ConversionPeriod);

			InterestAccrualDate = YlsIntComputerToIntel(InterestAccrualDate);
			Residualmaturity = YlsIntComputerToIntel(Residualmaturity);
			NoSecurityAltID = YlsIntComputerToIntel(NoSecurityAltID);
		}
		else
		{	
			m_fPrice = YlsFloatComputerToIntel(m_fPrice);			

			m_fShareFaceValue = YlsFloatComputerToIntel(m_fShareFaceValue);			
			m_fOutstandingShares = YlsFloatComputerToIntel(m_fOutstandingShares);
			m_fPublicFloatShareQuantity = YlsFloatComputerToIntel(m_fPublicFloatShareQuantity);
			ConversionPrice = YlsFloatComputerToIntel(ConversionPrice);
			m_fCVRatio = YlsFloatComputerToIntel(m_fCVRatio);
			InterestRate = YlsFloatComputerToIntel(InterestRate);
			m_fCouponRate = YlsFloatComputerToIntel(m_fCouponRate);
			ContractMultiplier = YlsFloatComputerToIntel(ContractMultiplier);
			AccruedInterestAmt = YlsFloatComputerToIntel(AccruedInterestAmt);
			RoundLot = YlsFloatComputerToIntel(RoundLot);

			MaturityDate = YlsIntIntelToComputer(MaturityDate);
			CouponPaymentDate = YlsIntIntelToComputer(CouponPaymentDate);

			LastInterestPaymentDate = YlsIntIntelToComputer(LastInterestPaymentDate);
			NextInterestPaymentDate = YlsIntIntelToComputer(NextInterestPaymentDate);
			ConversionPeriod = YlsIntIntelToComputer(ConversionPeriod);

			InterestAccrualDate = YlsIntIntelToComputer(InterestAccrualDate);
			Residualmaturity = YlsIntIntelToComputer(Residualmaturity);
			NoSecurityAltID = YlsIntIntelToComputer(NoSecurityAltID);
		}		
#endif
	}
};

// Level 2 ��չ����������
struct LevelRealTime 
{
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

	float				m_fBuyTotal;			// ί����������
	float				WeightedAvgBidPx;			// ��Ȩƽ��ί��۸�
	float				AltWeightedAvgBidPx;

	float				m_fSellTotal;			// ί����������
	float				WeightedAvgOfferPx;			// ��Ȩƽ��ί���۸�
	float				AltWeightedAvgOfferPx;

	unsigned long       m_lTickCount;			// �ɽ�����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{		
			m_lBuyPrice1 = YlsIntIntelToComputer(m_lBuyPrice1);			// ��һ��
			m_lBuyCount1 = YlsIntIntelToComputer(m_lBuyCount1);			// ��һ��
			m_lBuyPrice2 = YlsIntIntelToComputer(m_lBuyPrice2);			// �����
			m_lBuyCount2 = YlsIntIntelToComputer(m_lBuyCount2);			// �����
			m_lBuyPrice3 = YlsIntIntelToComputer(m_lBuyPrice3);			// ������
			m_lBuyCount3 = YlsIntIntelToComputer(m_lBuyCount3);			// ������
			m_lBuyPrice4 = YlsIntIntelToComputer(m_lBuyPrice4);			// ���ļ�
			m_lBuyCount4 = YlsIntIntelToComputer(m_lBuyCount4);			// ������
			m_lBuyPrice5 = YlsIntIntelToComputer(m_lBuyPrice5);			// �����
			m_lBuyCount5 = YlsIntIntelToComputer(m_lBuyCount5);			// ������

			m_lSellPrice1 = YlsIntIntelToComputer(m_lSellPrice1);			// ��һ��
			m_lSellCount1 = YlsIntIntelToComputer(m_lSellCount1);			// ��һ��
			m_lSellPrice2 = YlsIntIntelToComputer(m_lSellPrice2);			// ������
			m_lSellCount2 = YlsIntIntelToComputer(m_lSellCount2);			// ������
			m_lSellPrice3 = YlsIntIntelToComputer(m_lSellPrice3);			// ������
			m_lSellCount3 = YlsIntIntelToComputer(m_lSellCount3);			// ������
			m_lSellPrice4 = YlsIntIntelToComputer(m_lSellPrice4);			// ���ļ�
			m_lSellCount4 = YlsIntIntelToComputer(m_lSellCount4);			// ������
			m_lSellPrice5 = YlsIntIntelToComputer(m_lSellPrice5);			// �����
			m_lSellCount5 = YlsIntIntelToComputer(m_lSellCount5);			// ������

			m_fBuyTotal = YlsFloatComputerToIntel(m_fBuyTotal);			//	ί����������
			WeightedAvgBidPx = YlsFloatComputerToIntel(WeightedAvgBidPx);
			AltWeightedAvgBidPx = YlsFloatComputerToIntel(AltWeightedAvgBidPx);
			m_fSellTotal = YlsFloatComputerToIntel(m_fSellTotal);
			WeightedAvgOfferPx = YlsFloatComputerToIntel(WeightedAvgOfferPx);
			AltWeightedAvgOfferPx = YlsFloatComputerToIntel(AltWeightedAvgOfferPx);

			m_lTickCount = YlsIntIntelToComputer(m_lTickCount);			
		}
		else
		{
			m_lBuyPrice1 = YlsIntComputerToIntel(m_lBuyPrice1);			// ��һ��
			m_lBuyCount1 = YlsIntComputerToIntel(m_lBuyCount1);			// ��һ��
			m_lBuyPrice2 = YlsIntComputerToIntel(m_lBuyPrice2);			// �����
			m_lBuyCount2 = YlsIntComputerToIntel(m_lBuyCount2);			// �����
			m_lBuyPrice3 = YlsIntComputerToIntel(m_lBuyPrice3);			// ������
			m_lBuyCount3 = YlsIntComputerToIntel(m_lBuyCount3);			// ������
			m_lBuyPrice4 = YlsIntComputerToIntel(m_lBuyPrice4);			// ���ļ�
			m_lBuyCount4 = YlsIntComputerToIntel(m_lBuyCount4);			// ������
			m_lBuyPrice5 = YlsIntComputerToIntel(m_lBuyPrice5);			// �����
			m_lBuyCount5 = YlsIntComputerToIntel(m_lBuyCount5);			// ������

			m_lSellPrice1 = YlsIntComputerToIntel(m_lSellPrice1);			// ��һ��
			m_lSellCount1 = YlsIntComputerToIntel(m_lSellCount1);			// ��һ��
			m_lSellPrice2 = YlsIntComputerToIntel(m_lSellPrice2);			// ������
			m_lSellCount2 = YlsIntComputerToIntel(m_lSellCount2);			// ������
			m_lSellPrice3 = YlsIntComputerToIntel(m_lSellPrice3);			// ������
			m_lSellCount3 = YlsIntComputerToIntel(m_lSellCount3);			// ������
			m_lSellPrice4 = YlsIntComputerToIntel(m_lSellPrice4);			// ���ļ�
			m_lSellCount4 = YlsIntComputerToIntel(m_lSellCount4);			// ������
			m_lSellPrice5 = YlsIntComputerToIntel(m_lSellPrice5);			// �����
			m_lSellCount5 = YlsIntComputerToIntel(m_lSellCount5);			// ������

			m_fBuyTotal = YlsFloatComputerToIntel(m_fBuyTotal);			//	ί����������
			WeightedAvgBidPx = YlsFloatComputerToIntel(WeightedAvgBidPx);
			AltWeightedAvgBidPx = YlsFloatComputerToIntel(AltWeightedAvgBidPx);
			m_fSellTotal = YlsFloatComputerToIntel(m_fSellTotal);
			WeightedAvgOfferPx = YlsFloatComputerToIntel(WeightedAvgOfferPx);
			AltWeightedAvgOfferPx = YlsFloatComputerToIntel(AltWeightedAvgOfferPx);

			m_lTickCount = YlsIntIntelToComputer(m_lTickCount);			
		}		
#endif
	}
};

// ʵʱ����
struct HSStockRealTime 
{
	long				m_lOpen;         		// ����
	long				m_lMaxPrice;     		// ��߼�
	long				m_lMinPrice;     		// ��ͼ�
	long				m_lNewPrice;     		// ���¼�
	unsigned long		m_lTotal;				// �ɽ���(��λ:��)
	float				m_fAvgPrice;			// �ɽ����

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

	long				m_nHand;				// ÿ�ֹ���	(�Ƿ�ɷ��������У���������
	long				m_lNationalDebtRatio;	// ��ծ����,����ֵ

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{		
			m_lOpen = YlsIntIntelToComputer(m_lOpen);         		// ����
			m_lMaxPrice = YlsIntIntelToComputer(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);     		// ���¼�
			m_lTotal = YlsIntIntelToComputer(m_lTotal);				// �ɽ���(��λ:��)
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);			// �ɽ����

			m_lBuyPrice1 = YlsIntIntelToComputer(m_lBuyPrice1);			// ��һ��
			m_lBuyCount1 = YlsIntIntelToComputer(m_lBuyCount1);			// ��һ��
			m_lBuyPrice2 = YlsIntIntelToComputer(m_lBuyPrice2);			// �����
			m_lBuyCount2 = YlsIntIntelToComputer(m_lBuyCount2);			// �����
			m_lBuyPrice3 = YlsIntIntelToComputer(m_lBuyPrice3);			// ������
			m_lBuyCount3 = YlsIntIntelToComputer(m_lBuyCount3);			// ������
			m_lBuyPrice4 = YlsIntIntelToComputer(m_lBuyPrice4);			// ���ļ�
			m_lBuyCount4 = YlsIntIntelToComputer(m_lBuyCount4);			// ������
			m_lBuyPrice5 = YlsIntIntelToComputer(m_lBuyPrice5);			// �����
			m_lBuyCount5 = YlsIntIntelToComputer(m_lBuyCount5);			// ������

			m_lSellPrice1 = YlsIntIntelToComputer(m_lSellPrice1);			// ��һ��
			m_lSellCount1 = YlsIntIntelToComputer(m_lSellCount1);			// ��һ��
			m_lSellPrice2 = YlsIntIntelToComputer(m_lSellPrice2);			// ������
			m_lSellCount2 = YlsIntIntelToComputer(m_lSellCount2);			// ������
			m_lSellPrice3 = YlsIntIntelToComputer(m_lSellPrice3);			// ������
			m_lSellCount3 = YlsIntIntelToComputer(m_lSellCount3);			// ������
			m_lSellPrice4 = YlsIntIntelToComputer(m_lSellPrice4);			// ���ļ�
			m_lSellCount4 = YlsIntIntelToComputer(m_lSellCount4);			// ������
			m_lSellPrice5 = YlsIntIntelToComputer(m_lSellPrice5);			// �����
			m_lSellCount5 = YlsIntIntelToComputer(m_lSellCount5);			// ������

			m_nHand = YlsIntIntelToComputer(m_nHand);					// ÿ�ֹ���	(�Ƿ�ɷ��������У���������
			m_lNationalDebtRatio = YlsIntIntelToComputer(m_lNationalDebtRatio);	// ��ծ����,����ֵ
		}
		else
		{
			m_lOpen = YlsIntComputerToIntel(m_lOpen);         		// ����
			m_lMaxPrice = YlsIntComputerToIntel(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);     		// ���¼�
			m_lTotal = YlsIntComputerToIntel(m_lTotal);				// �ɽ���(��λ:��)
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);			// �ɽ����

			m_lBuyPrice1 = YlsIntComputerToIntel(m_lBuyPrice1);			// ��һ��
			m_lBuyCount1 = YlsIntComputerToIntel(m_lBuyCount1);			// ��һ��
			m_lBuyPrice2 = YlsIntComputerToIntel(m_lBuyPrice2);			// �����
			m_lBuyCount2 = YlsIntComputerToIntel(m_lBuyCount2);			// �����
			m_lBuyPrice3 = YlsIntComputerToIntel(m_lBuyPrice3);			// ������
			m_lBuyCount3 = YlsIntComputerToIntel(m_lBuyCount3);			// ������
			m_lBuyPrice4 = YlsIntComputerToIntel(m_lBuyPrice4);			// ���ļ�
			m_lBuyCount4 = YlsIntComputerToIntel(m_lBuyCount4);			// ������
			m_lBuyPrice5 = YlsIntComputerToIntel(m_lBuyPrice5);			// �����
			m_lBuyCount5 = YlsIntComputerToIntel(m_lBuyCount5);			// ������

			m_lSellPrice1 = YlsIntComputerToIntel(m_lSellPrice1);			// ��һ��
			m_lSellCount1 = YlsIntComputerToIntel(m_lSellCount1);			// ��һ��
			m_lSellPrice2 = YlsIntComputerToIntel(m_lSellPrice2);			// ������
			m_lSellCount2 = YlsIntComputerToIntel(m_lSellCount2);			// ������
			m_lSellPrice3 = YlsIntComputerToIntel(m_lSellPrice3);			// ������
			m_lSellCount3 = YlsIntComputerToIntel(m_lSellCount3);			// ������
			m_lSellPrice4 = YlsIntComputerToIntel(m_lSellPrice4);			// ���ļ�
			m_lSellCount4 = YlsIntComputerToIntel(m_lSellCount4);			// ������
			m_lSellPrice5 = YlsIntComputerToIntel(m_lSellPrice5);			// �����
			m_lSellCount5 = YlsIntComputerToIntel(m_lSellCount5);			// ������

			m_nHand = YlsIntComputerToIntel(m_nHand);					// ÿ�ֹ���	(�Ƿ�ɷ��������У���������
			m_lNationalDebtRatio = YlsIntComputerToIntel(m_lNationalDebtRatio);	// ��ծ����,����ֵ
		}		
#endif
	}
};  
// ԭ28*4 = 112

// ָ����ʵʱ����
struct HSIndexRealTime  
{
	long		m_lOpen;				// ����
	long		m_lMaxPrice;			// ��߼�
	long		m_lMinPrice;			// ��ͼ�
	long		m_lNewPrice;			// ���¼�
	unsigned long		m_lTotal;				// �ɽ���
	float		m_fAvgPrice;			// �ɽ����

	short		m_nRiseCount;			// ���Ǽ���
	short		m_nFallCount;			// �µ�����
	long		m_nTotalStock1;			/* �����ۺ�ָ�������й�Ʊ - ָ��
										���ڷ���ָ���������Ʊ���� */
	unsigned long		m_lBuyCount;			// ί����
	unsigned long		m_lSellCount;			// ί����
	short		m_nType;				// ָ�����ࣺ0-�ۺ�ָ�� 1-A�� 2-B��
	short		m_nLead;            	// ����ָ��
	short		m_nRiseTrend;       	// ��������
	short		m_nFallTrend;       	// �µ�����
	short		m_nNo2[5];				// ����
	short		m_nTotalStock2;			/* �����ۺ�ָ����A�� + B�� 
										���ڷ���ָ����0 */
	long		m_lADL;					// ADL ָ��
	long		m_lNo3[3];				// ����
	long		m_nHand;				// ÿ�ֹ���	

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		int i;

		if( cIntelToComputer )
		{
			m_lOpen = YlsIntIntelToComputer(m_lOpen);         		// ����
			m_lMaxPrice = YlsIntIntelToComputer(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);     		// ���¼�
			m_lTotal = YlsIntIntelToComputer(m_lTotal);				// �ɽ���(��λ:��)
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);			// �ɽ����

			m_nRiseCount = YlsShortIntelToComputer(m_nRiseCount);			// ���Ǽ���
			m_nFallCount = YlsShortIntelToComputer(m_nFallCount);			// �µ�����
			m_nTotalStock1 = YlsIntIntelToComputer(m_nTotalStock1);			/* �����ۺ�ָ�������й�Ʊ - ָ��
																			���ڷ���ָ���������Ʊ���� */
			m_lBuyCount = YlsIntIntelToComputer(m_lBuyCount);			    // ί����
			m_lSellCount = YlsIntIntelToComputer(m_lSellCount);			// ί����
			m_nType = YlsShortIntelToComputer(m_nType);				// ָ�����ࣺ0-�ۺ�ָ�� 1-A�� 2-B��
			m_nLead = YlsShortIntelToComputer(m_nLead);            	// ����ָ��
			m_nRiseTrend = YlsShortIntelToComputer(m_nRiseTrend);       	// ��������
			m_nFallTrend = YlsShortIntelToComputer(m_nFallTrend);       	// �µ�����
			for( i = 0; i < 5; i++ )
				m_nNo2[5] = YlsShortIntelToComputer(m_nNo2[5]);			// ����
			m_nTotalStock2 = YlsShortIntelToComputer(m_nTotalStock2);		/* �����ۺ�ָ����A�� + B�� 
																			���ڷ���ָ����0 */
			m_lADL = YlsIntIntelToComputer(m_lADL);					// ADL ָ��
			for( i = 0; i < 3; i++ )
				m_lNo3[i] = YlsIntIntelToComputer(m_lNo3[i]);			// ����
			m_nHand = YlsIntIntelToComputer(m_nHand);					// ÿ�ֹ���
		}
		else
		{
			m_lOpen = YlsIntComputerToIntel(m_lOpen);         		// ����
			m_lMaxPrice = YlsIntComputerToIntel(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);     		// ���¼�
			m_lTotal = YlsIntComputerToIntel(m_lTotal);				// �ɽ���(��λ:��)
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);			// �ɽ����

			m_nRiseCount = YlsShortComputerToIntel(m_nRiseCount);			// ���Ǽ���
			m_nFallCount = YlsShortComputerToIntel(m_nFallCount);			// �µ�����
			m_nTotalStock1 = YlsIntComputerToIntel(m_nTotalStock1);			/* �����ۺ�ָ�������й�Ʊ - ָ��
																			���ڷ���ָ���������Ʊ���� */
			m_lBuyCount = YlsIntComputerToIntel(m_lBuyCount);			    // ί����
			m_lSellCount = YlsIntComputerToIntel(m_lSellCount);			// ί����
			m_nType = YlsShortComputerToIntel(m_nType);				// ָ�����ࣺ0-�ۺ�ָ�� 1-A�� 2-B��
			m_nLead = YlsShortComputerToIntel(m_nLead);            	// ����ָ��
			m_nRiseTrend = YlsShortComputerToIntel(m_nRiseTrend);       	// ��������
			m_nFallTrend = YlsShortComputerToIntel(m_nFallTrend);       	// �µ�����
			for( i = 0; i < 5; i++ )
				m_nNo2[5] = YlsShortComputerToIntel(m_nNo2[5]);			// ����
			m_nTotalStock2 = YlsShortComputerToIntel(m_nTotalStock2);		/* �����ۺ�ָ����A�� + B�� 
																			���ڷ���ָ����0 */
			m_lADL = YlsIntComputerToIntel(m_lADL);					// ADL ָ��
			for( i = 0; i < 3; i++ )
				m_lNo3[i] = YlsIntComputerToIntel(m_lNo3[i]);			// ����
			m_nHand = YlsIntComputerToIntel(m_nHand);					// ÿ�ֹ���
		}		
#endif
	}
};  

// �۹�ʵʱ 29*4 = 116 ��  26*4 = 104���۱��short)
struct HSHKStockRealTime 
{
	long		m_lOpen;         		// ����
	long		m_lMaxPrice;     		// ��߼�
	long		m_lMinPrice;     		// ��ͼ�
	long		m_lNewPrice;     		// ���¼�

	unsigned long		m_lTotal;				// �ɽ������ɣ�	
	float		m_fAvgPrice;			// �ɽ����(Ԫ)

	long		m_lBuyPrice;			// ���
	long		m_lSellPrice;			// ����
	union
	{
		long		m_lYield;		// ��Ϣ�� ��Ʊ���
		long		m_lOverFlowPrice;	// ���% �Ϲ�֤���
		// �Ϲ�֤����ۣ����Ϲ�֤�ּۡ��һ����ʣ���ʹ�ۣ�����ʲ��ּۣ�/����ʲ��ּۡ�100
		// �Ϲ�֤����ۣ����Ϲ�֤�ּۡ��һ����ʣ���ʹ�ۣ�����ʲ��ּۣ�/����ʲ��ּۡ�100

	};

	long		m_lBuyCount1;			// ��һ��
	long		m_lBuyCount2;			// �����
	long		m_lBuyCount3;			// ������
	long		m_lBuyCount4;			// ������
	long		m_lBuyCount5;			// ������

	long		m_lSellCount1;			// ��һ��
	long		m_lSellCount2;			// ������
	long		m_lSellCount3;			// ������
	long		m_lSellCount4;			// ������
	long		m_lSellCount5;			// ������

	unsigned short		m_lSellOrder1;	// ��һ����
	unsigned short		m_lSellOrder2;	// ��������
	unsigned short		m_lSellOrder3;	// ��������
	unsigned short		m_lSellOrder4;	// ��������
	unsigned short		m_lSellOrder5;	// ��������

	unsigned short		m_lBuyOrder1;	// ��һ����
	unsigned short		m_lBuyOrder2;	// �������
	unsigned short		m_lBuyOrder3;	// ��������
	unsigned short		m_lBuyOrder4;	// ��������
	unsigned short		m_lBuyOrder5;	// ��������

	long		m_lIEP;					// �ο�ƽ���
	long		m_lIEV;					// �ο�ƽ����

	// ���Ʒֱʵ�ǰ�ɽ��������ͣ�������
	long		m_lMatchType;			// ���̷���

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lOpen = YlsIntIntelToComputer(m_lOpen);         		// ����
			m_lMaxPrice = YlsIntIntelToComputer(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);     		// ���¼�
			m_lTotal = YlsIntIntelToComputer(m_lTotal);				// �ɽ���(��λ:��)
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);			// �ɽ����

			m_lBuyPrice = YlsIntIntelToComputer(m_lBuyPrice);			// ���
			m_lSellPrice = YlsIntIntelToComputer(m_lSellPrice);			// ����
			m_lYield = YlsIntIntelToComputer(m_lYield);		// ��Ϣ�� ��Ʊ���

			m_lBuyCount1 = YlsIntIntelToComputer(m_lBuyCount1);			// ��һ��
			m_lBuyCount2 = YlsIntIntelToComputer(m_lBuyCount2);			// �����
			m_lBuyCount3 = YlsIntIntelToComputer(m_lBuyCount3);			// ������
			m_lBuyCount4 = YlsIntIntelToComputer(m_lBuyCount4);			// ������
			m_lBuyCount5 = YlsIntIntelToComputer(m_lBuyCount5);			// ������

			m_lSellCount1 = YlsIntIntelToComputer(m_lSellCount1);			// ��һ��
			m_lSellCount2 = YlsIntIntelToComputer(m_lSellCount2);			// ������
			m_lSellCount3 = YlsIntIntelToComputer(m_lSellCount3);			// ������
			m_lSellCount4 = YlsIntIntelToComputer(m_lSellCount4);			// ������
			m_lSellCount5 = YlsIntIntelToComputer(m_lSellCount5);			// ������

			m_lSellOrder1 = YlsShortIntelToComputer(m_lSellOrder1);	// ��һ����
			m_lSellOrder2 = YlsShortIntelToComputer(m_lSellOrder2);	// ��������
			m_lSellOrder3 = YlsShortIntelToComputer(m_lSellOrder3);	// ��������
			m_lSellOrder4 = YlsShortIntelToComputer(m_lSellOrder4);	// ��������
			m_lSellOrder5 = YlsShortIntelToComputer(m_lSellOrder5);	// ��������

			m_lBuyOrder1 = YlsShortIntelToComputer(m_lBuyOrder1);	// ��һ����
			m_lBuyOrder2 = YlsShortIntelToComputer(m_lBuyOrder2);	// �������
			m_lBuyOrder3 = YlsShortIntelToComputer(m_lBuyOrder3);	// ��������
			m_lBuyOrder4 = YlsShortIntelToComputer(m_lBuyOrder4);	// ��������
			m_lBuyOrder5 = YlsShortIntelToComputer(m_lBuyOrder5);	// ��������

			m_lIEP = YlsIntIntelToComputer(m_lIEP);					// �ο�ƽ���
			m_lIEV = YlsIntIntelToComputer(m_lIEV);					// �ο�ƽ����

			// ���Ʒֱʵ�ǰ�ɽ��������ͣ�������
			m_lMatchType = YlsIntIntelToComputer(m_lMatchType);			// ���̷���
		}
		else
		{
			m_lOpen = YlsIntComputerToIntel(m_lOpen);         		// ����
			m_lMaxPrice = YlsIntComputerToIntel(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);     		// ���¼�
			m_lTotal = YlsIntComputerToIntel(m_lTotal);				// �ɽ���(��λ:��)
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);			// �ɽ����

			m_lBuyPrice = YlsIntComputerToIntel(m_lBuyPrice);			// ���
			m_lSellPrice = YlsIntComputerToIntel(m_lSellPrice);			// ����
			m_lYield = YlsIntComputerToIntel(m_lYield);		// ��Ϣ�� ��Ʊ���

			m_lBuyCount1 = YlsIntComputerToIntel(m_lBuyCount1);			// ��һ��
			m_lBuyCount2 = YlsIntComputerToIntel(m_lBuyCount2);			// �����
			m_lBuyCount3 = YlsIntComputerToIntel(m_lBuyCount3);			// ������
			m_lBuyCount4 = YlsIntComputerToIntel(m_lBuyCount4);			// ������
			m_lBuyCount5 = YlsIntComputerToIntel(m_lBuyCount5);			// ������

			m_lSellCount1 = YlsIntComputerToIntel(m_lSellCount1);			// ��һ��
			m_lSellCount2 = YlsIntComputerToIntel(m_lSellCount2);			// ������
			m_lSellCount3 = YlsIntComputerToIntel(m_lSellCount3);			// ������
			m_lSellCount4 = YlsIntComputerToIntel(m_lSellCount4);			// ������
			m_lSellCount5 = YlsIntComputerToIntel(m_lSellCount5);			// ������

			m_lSellOrder1 = YlsShortComputerToIntel(m_lSellOrder1);	// ��һ����
			m_lSellOrder2 = YlsShortComputerToIntel(m_lSellOrder2);	// ��������
			m_lSellOrder3 = YlsShortComputerToIntel(m_lSellOrder3);	// ��������
			m_lSellOrder4 = YlsShortComputerToIntel(m_lSellOrder4);	// ��������
			m_lSellOrder5 = YlsShortComputerToIntel(m_lSellOrder5);	// ��������

			m_lBuyOrder1 = YlsShortComputerToIntel(m_lBuyOrder1);	// ��һ����
			m_lBuyOrder2 = YlsShortComputerToIntel(m_lBuyOrder2);	// �������
			m_lBuyOrder3 = YlsShortComputerToIntel(m_lBuyOrder3);	// ��������
			m_lBuyOrder4 = YlsShortComputerToIntel(m_lBuyOrder4);	// ��������
			m_lBuyOrder5 = YlsShortComputerToIntel(m_lBuyOrder5);	// ��������

			m_lIEP = YlsIntComputerToIntel(m_lIEP);					// �ο�ƽ���
			m_lIEV = YlsIntComputerToIntel(m_lIEV);					// �ο�ƽ����

			// ���Ʒֱʵ�ǰ�ɽ��������ͣ�������
			m_lMatchType = YlsIntComputerToIntel(m_lMatchType);			// ���̷���
		}		
#endif
	}
}; 

// �۹���Ȩ
struct HSQQStockRealTime 
{
	long				m_Month;				// ������,19990101

	char				m_Symbol[10];			// ���
	char				m_OptionType;			// ��Ȩ���ࣺ��P��(����)����C�������룩

	float				m_StrikePrice;		    // ��ʹ��

	float				m_lOpen;         		// ����
	float				m_lMaxPrice;     		// ��߼�
	float				m_lMinPrice;     		// ��ͼ�
	float				m_lNewPrice;     		// ���¼�

	float				m_lTotal;				// �ɽ������ɣ�	
	float				m_fAvgPrice;			// �ɽ����(Ԫ)

	float				m_lBuyPrice;			// ���
	float				m_lSellPrice;			// ����

	float				m_BidVol;				// ������
	float				m_AskVol;				// ������

	float				m_YClose;				// ǰ�����̼�

	char				m_cReserve[20];			// ����
};

/*
// �ڻ�ʵʱ����
struct HSQHRealTime 
{
long		m_lOpen;         	// ����
long		m_lMaxPrice;     	// ��߼�
long		m_lMinPrice;     	// ��ͼ�
long		m_lNewPrice;     	// ���¼�

unsigned long		m_lTotal;		   	// �ɽ���(��λ:��Լ��λ)
long				m_lChiCangLiang;    // �ֲ���(��λ:��Լ��λ)

long		m_lBuyPrice1;		// ��һ��
long		m_lBuyCount1;		// ��һ��
long		m_lSellPrice1;		// ��һ��
long		m_lSellCount1;		// ��һ��

long		m_lPreJieSuanPrice; // ������

union
{
struct
{
long				m_lBuyPrice2;			// �����
unsigned short		m_lBuyCount2;			// �����
long				m_lBuyPrice3;			// ������
unsigned short		m_lBuyCount3;			// ������
long				m_lBuyPrice4;			// ���ļ�
unsigned short		m_lBuyCount4;			// ������
long				m_lBuyPrice5;			// �����
unsigned short		m_lBuyCount5;			// ������

long				m_lSellPrice2;			// ������
unsigned short		m_lSellCount2;			// ������
long				m_lSellPrice3;			// ������
unsigned short		m_lSellCount3;			// ������
long				m_lSellPrice4;			// ���ļ�
unsigned short		m_lSellCount4;			// ������
long				m_lSellPrice5;			// �����
unsigned short		m_lSellCount5;			// ������
};

struct
{
long		m_lJieSuanPrice;    // �ֽ����
long		m_lCurrentCLOSE;	// ������
long		m_lHIS_HIGH;		// ʷ���
long		m_lHIS_LOW;	 		// ʷ���
long		m_lUPPER_LIM;		// ��ͣ��
long		m_lLOWER_LIM;		// ��ͣ��

long 		m_lLongPositionOpen;	// ��ͷ��(��λ:��Լ��λ)
long 		m_lLongPositionFlat;	// ��ͷƽ(��λ:��Լ��λ)
long 		m_lNominalOpen;			// ��ͷ��(��λ:��Լ��λ)	
long 		m_lNominalFlat;			// ��ͷƽ(��λ:��Լ��λ)

long		m_lPreClose;			// ǰ������????
};
};

long		m_nHand;				// ÿ�ֹ���
long 		m_lPreCloseChiCang;		// ��ֲ���(��λ:��Լ��λ)
};
*/

// �ڻ�������ʵʱ����
struct HSQHRealTime 
{
	long		m_lOpen;         	// ����
	long		m_lMaxPrice;     	// ��߼�
	long		m_lMinPrice;     	// ��ͼ�
	long		m_lNewPrice;     	// ���¼�

	unsigned long		m_lTotal;		   	// �ɽ���(��λ:��Լ��λ)
	long				m_lChiCangLiang;    // �ֲ���(��λ:��Լ��λ)

	long		m_lPreJieSuanPrice; // ������

	//long		m_nHand;				// ÿ�ֹ���
	//long 		m_lPreCloseChiCang;		// ��ֲ���(��λ:��Լ��λ)


	long		m_lJieSuanPrice;    // �ֽ����
	long		m_lCurrentCLOSE;	// ������
	long		m_lHIS_HIGH;		// ʷ���
	long		m_lHIS_LOW;	 		// ʷ���
	long		m_lUPPER_LIM;		// ��ͣ��
	long		m_lLOWER_LIM;		// ��ͣ��

	long		m_nHand;				// ÿ�ֹ���
	long 		m_lPreCloseChiCang;		// ��ֲ���(��λ:��Լ��λ)

	long 		m_lLongPositionOpen;	// ��ͷ��(��λ:��Լ��λ)
	long 		m_lLongPositionFlat;	// ��ͷƽ(��λ:��Լ��λ)
	long 		m_lNominalOpen;			// ��ͷ��(��λ:��Լ��λ)	
	long 		m_lNominalFlat;			// ��ͷƽ(��λ:��Լ��λ)

	long		m_lPreClose;			// ǰ������????
	long        m_lAvgPrice;            // �ɽ����  added by Ben 20100506

	// modified by Ben 20100506
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


	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lOpen = YlsIntIntelToComputer(m_lOpen);         		// ����
			m_lMaxPrice = YlsIntIntelToComputer(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);     		// ���¼�
			m_lTotal = YlsIntIntelToComputer(m_lTotal);				// �ɽ���(��λ:��)
			m_lChiCangLiang = YlsIntComputerToIntel(m_lChiCangLiang);			// �ɽ����

			m_lPreJieSuanPrice = YlsIntComputerToIntel(m_lPreJieSuanPrice); // ������

			//long		m_nHand;				// ÿ�ֹ���
			//long 		m_lPreCloseChiCang;		// ��ֲ���(��λ:��Լ��λ)

			m_lJieSuanPrice = YlsIntComputerToIntel(m_lJieSuanPrice);    // �ֽ����
			m_lCurrentCLOSE = YlsIntComputerToIntel(m_lCurrentCLOSE);	// ������
			m_lHIS_HIGH = YlsIntComputerToIntel(m_lHIS_HIGH);		// ʷ���
			m_lHIS_LOW = YlsIntComputerToIntel(m_lHIS_LOW);	 		// ʷ���
			m_lUPPER_LIM = YlsIntComputerToIntel(m_lUPPER_LIM);		// ��ͣ��
			m_lLOWER_LIM = YlsIntComputerToIntel(m_lLOWER_LIM);		// ��ͣ��

			m_nHand = YlsIntComputerToIntel(m_nHand);				// ÿ�ֹ���
			m_lPreCloseChiCang = YlsIntIntelToComputer(m_lPreCloseChiCang);		// ��ֲ���(��λ:��Լ��λ)

			m_lLongPositionOpen = YlsIntIntelToComputer(m_lLongPositionOpen);	// ��ͷ��(��λ:��Լ��λ)
			m_lLongPositionFlat = YlsIntIntelToComputer(m_lLongPositionFlat);	// ��ͷƽ(��λ:��Լ��λ)
			m_lNominalOpen = YlsIntIntelToComputer(m_lNominalOpen);			// ��ͷ��(��λ:��Լ��λ)	
			m_lNominalFlat = YlsIntIntelToComputer(m_lNominalFlat);			// ��ͷƽ(��λ:��Լ��λ)

			m_lPreClose = YlsIntIntelToComputer(m_lPreClose);			// ǰ������????
			m_lAvgPrice = YlsIntIntelToComputer(m_lAvgPrice);



			m_lBuyPrice1 = YlsIntIntelToComputer(m_lBuyPrice1);			// ��һ��
			m_lBuyCount1 = YlsIntIntelToComputer(m_lBuyCount1);			// ��һ��
			m_lBuyPrice2 = YlsIntIntelToComputer(m_lBuyPrice2);			// �����
			m_lBuyCount2 = YlsIntIntelToComputer(m_lBuyCount2);			// �����
			m_lBuyPrice3 = YlsIntIntelToComputer(m_lBuyPrice3);			// ������
			m_lBuyCount3 = YlsIntIntelToComputer(m_lBuyCount3);			// ������
			m_lBuyPrice4 = YlsIntIntelToComputer(m_lBuyPrice4);			// ���ļ�
			m_lBuyCount4 = YlsIntIntelToComputer(m_lBuyCount4);			// ������
			m_lBuyPrice5 = YlsIntIntelToComputer(m_lBuyPrice5);			// �����
			m_lBuyCount5 = YlsIntIntelToComputer(m_lBuyCount5);			// ������

			m_lSellPrice1 = YlsIntIntelToComputer(m_lSellPrice1);			// ��һ��
			m_lSellCount1 = YlsIntIntelToComputer(m_lSellCount1);			// ��һ��
			m_lSellPrice2 = YlsIntIntelToComputer(m_lSellPrice2);			// ������
			m_lSellCount2 = YlsIntIntelToComputer(m_lSellCount2);			// ������
			m_lSellPrice3 = YlsIntIntelToComputer(m_lSellPrice3);			// ������
			m_lSellCount3 = YlsIntIntelToComputer(m_lSellCount3);			// ������
			m_lSellPrice4 = YlsIntIntelToComputer(m_lSellPrice4);			// ���ļ�
			m_lSellCount4 = YlsIntIntelToComputer(m_lSellCount4);			// ������
			m_lSellPrice5 = YlsIntIntelToComputer(m_lSellPrice5);			// �����
			m_lSellCount5 = YlsIntIntelToComputer(m_lSellCount5);			// ������

		}
		else
		{
			m_lOpen = YlsIntComputerToIntel(m_lOpen);         		// ����
			m_lMaxPrice = YlsIntComputerToIntel(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);     		// ���¼�
			m_lTotal = YlsIntComputerToIntel(m_lTotal);				// �ɽ���(��λ:��)
			m_lChiCangLiang = YlsIntComputerToIntel(m_lChiCangLiang);			// �ɽ����

			m_lPreJieSuanPrice = YlsIntComputerToIntel(m_lPreJieSuanPrice); // ������

			//long		m_nHand;				// ÿ�ֹ���
			//long 		m_lPreCloseChiCang;		// ��ֲ���(��λ:��Լ��λ)

			m_lJieSuanPrice = YlsIntComputerToIntel(m_lJieSuanPrice);    // �ֽ����
			m_lCurrentCLOSE = YlsIntComputerToIntel(m_lCurrentCLOSE);	// ������
			m_lHIS_HIGH = YlsIntComputerToIntel(m_lHIS_HIGH);		// ʷ���
			m_lHIS_LOW = YlsIntComputerToIntel(m_lHIS_LOW);	 		// ʷ���
			m_lUPPER_LIM = YlsIntComputerToIntel(m_lUPPER_LIM);		// ��ͣ��
			m_lLOWER_LIM = YlsIntComputerToIntel(m_lLOWER_LIM);		// ��ͣ��

			m_nHand = YlsIntComputerToIntel(m_nHand);				// ÿ�ֹ���
			m_lPreCloseChiCang = YlsIntComputerToIntel(m_lPreCloseChiCang);		// ��ֲ���(��λ:��Լ��λ)

			m_lLongPositionOpen = YlsIntComputerToIntel(m_lLongPositionOpen);	// ��ͷ��(��λ:��Լ��λ)
			m_lLongPositionFlat = YlsIntComputerToIntel(m_lLongPositionFlat);	// ��ͷƽ(��λ:��Լ��λ)
			m_lNominalOpen = YlsIntComputerToIntel(m_lNominalOpen);			// ��ͷ��(��λ:��Լ��λ)	
			m_lNominalFlat = YlsIntComputerToIntel(m_lNominalFlat);			// ��ͷƽ(��λ:��Լ��λ)

			m_lPreClose = YlsIntComputerToIntel(m_lPreClose);			// ǰ������????
			m_lAvgPrice = YlsIntComputerToIntel(m_lAvgPrice);			// ǰ������????


			m_lBuyPrice1 = YlsIntComputerToIntel(m_lBuyPrice1);			// ��һ��
			m_lBuyCount1 = YlsIntComputerToIntel(m_lBuyCount1);			// ��һ��
			m_lBuyPrice2 = YlsIntComputerToIntel(m_lBuyPrice2);			// �����
			m_lBuyCount2 = YlsIntComputerToIntel(m_lBuyCount2);			// �����
			m_lBuyPrice3 = YlsIntComputerToIntel(m_lBuyPrice3);			// ������
			m_lBuyCount3 = YlsIntComputerToIntel(m_lBuyCount3);			// ������
			m_lBuyPrice4 = YlsIntComputerToIntel(m_lBuyPrice4);			// ���ļ�
			m_lBuyCount4 = YlsIntComputerToIntel(m_lBuyCount4);			// ������
			m_lBuyPrice5 = YlsIntComputerToIntel(m_lBuyPrice5);			// �����
			m_lBuyCount5 = YlsIntComputerToIntel(m_lBuyCount5);			// ������

			m_lSellPrice1 = YlsIntComputerToIntel(m_lSellPrice1);			// ��һ��
			m_lSellCount1 = YlsIntComputerToIntel(m_lSellCount1);			// ��һ��
			m_lSellPrice2 = YlsIntComputerToIntel(m_lSellPrice2);			// ������
			m_lSellCount2 = YlsIntComputerToIntel(m_lSellCount2);			// ������
			m_lSellPrice3 = YlsIntComputerToIntel(m_lSellPrice3);			// ������
			m_lSellCount3 = YlsIntComputerToIntel(m_lSellCount3);			// ������
			m_lSellPrice4 = YlsIntComputerToIntel(m_lSellPrice4);			// ���ļ�
			m_lSellCount4 = YlsIntComputerToIntel(m_lSellCount4);			// ������
			m_lSellPrice5 = YlsIntComputerToIntel(m_lSellPrice5);			// �����
			m_lSellCount5 = YlsIntComputerToIntel(m_lSellCount5);			// ������

		}		
#endif
	}
};


// �������ծȯ
struct HSWHCenterRealTime
{	
	long		m_lOpen;         			// ���̼�	->���̼�
	long		m_lMaxPrice;     			// ��߼�	->��߼�
	long		m_lMinPrice;     			// ��ͼ�	->��ͼ�
	long		m_lNewPrice;     			// ���¼�	->���¼�
	unsigned long		m_lTotal;		   	// �ɽ���(��λ:��Լ��λ)	->�ɽ���

	long		m_lChiCangLiang;			// �ֲ���(��λ:��Լ��λ)	->���̼�

	long		m_lBuyPrice1;				// ��һ��	->����1
	long		m_lBuyCount1;				// ��һ��	->���������
	long		m_lSellPrice1;				// ��һ��	->����1
	long		m_lSellCount1;				// ��һ��	->���������

	long		m_lPreJieSuanPrice;			// ������ ->����������
	long		m_lJieSuanPrice;			// �����	->ǰ���̼�
	long		m_lCurrentCLOSE;			// ������	->����������
	long		m_lHIS_HIGH;				// ʷ���	->��Ȩ��
	long		m_lHIS_LOW;	 				// ʷ���	->��Ȩ������
	long		m_lUPPER_LIM;				// ��ͣ��	->ǰ����������
	long		m_lLOWER_LIM;				// ��ͣ��	->ǰ��Ȩ������
	
	long		m_nHand;					// ÿ�ֹ���

	long 		m_lPreCloseChiCang;			// ��ֲ���(��λ:��Լ��λ) ->����������
	long 		m_lLongPositionOpen;		// ��ͷ��(��λ:��Լ��λ)   ->ʱ��
	long 		m_lLongPositionFlat;		// ��ͷƽ(��λ:��Լ��λ)   ->���۷����
	long 		m_lNominalOpen;				// ��ͷ��(��λ:��Լ��λ)	
	long 		m_lNominalFlat;				// ƽ����				   ->ǰ��Ȩ��
	long		m_lPreClose;				// ǰ������????
};

// �ڻ�����������ʵʱ����(����)
struct HSQHRealTime_Min
{
	long		m_lOpen;         	// ����
	long		m_lMaxPrice;     	// ��߼�
	long		m_lMinPrice;     	// ��ͼ�
	long		m_lNewPrice;     	// ���¼�

	unsigned long		m_lTotal;		   	// �ɽ���(��λ:��Լ��λ)
	long				m_lChiCangLiang;    // �ֲ���(��λ:��Լ��λ)

	long		m_lBuyPrice1;		// ��һ��
	long		m_lBuyCount1;		// ��һ��
	long		m_lSellPrice1;		// ��һ��
	long		m_lSellCount1;		// ��һ��

	long		m_lPreJieSuanPrice; // ������
};

// ���ʵʱ����
struct HSWHRealTime 
{
	long		m_lOpen;         	// ����(1/10000Ԫ)
	long		m_lMaxPrice;     	// ��߼�(1/10000Ԫ)
	long		m_lMinPrice;     	// ��ͼ�(1/10000Ԫ)
	long		m_lNewPrice;     	// ���¼�(1/10000Ԫ)

	long		m_lBuyPrice;		// ���(1/10000Ԫ)
	long		m_lSellPrice;		// ����(1/10000Ԫ)

	//long		m_lPrevClose;	    // ��������
	//long		m_lPriceTimes;	    // ��������һ���Ӽ۸�仯����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{			
			m_lOpen = YlsIntIntelToComputer(m_lOpen);         		// ����
			m_lMaxPrice	= YlsIntIntelToComputer(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice	= YlsIntIntelToComputer(m_lNewPrice);     		// ���¼�
			m_lBuyPrice	= YlsIntIntelToComputer(m_lBuyPrice);				// �ɽ���(��λ:��)
			m_lSellPrice = YlsIntIntelToComputer(m_lSellPrice);			// �ɽ����
		}
		else
		{
			m_lOpen = YlsIntComputerToIntel(m_lOpen);         		// ����
			m_lMaxPrice	= YlsIntComputerToIntel(m_lMaxPrice);     		// ��߼�
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);     		// ��ͼ�
			m_lNewPrice	= YlsIntComputerToIntel(m_lNewPrice);     		// ���¼�
			m_lBuyPrice	= YlsIntComputerToIntel(m_lBuyPrice);				// �ɽ���(��λ:��)
			m_lSellPrice = YlsIntComputerToIntel(m_lSellPrice);			// �ɽ����
		}		
#endif
	}

};

// ָ����NOW����
struct IndexRealTime : public HSIndexRealTime
{
	unsigned long  m_lOutside;    // ���̳ɽ���
};


// �۹ɶ��̷��ඨ��
#define HSHK_OrderType_A			'A' // �Զ����̷����߿ͽ���
#define HSHK_OrderType_M			'M' // ��"�Զ����̻��ر�������λ"�ķ����߿ͽ���
#define HSHK_OrderType_X			'X' // ��"�Զ����̻��ر�������λ"�����߿ͽ���
#define HSHK_OrderType_Y			'Y' // �Զ��������߿ͽ���
#define HSHK_OrderType_D			'D' // ��ɳɽ�
#define HSHK_OrderType_P			'P' // ����ǰ�ɽ�
#define HSHK_OrderType_U			'U' // ����ǰ�����̳ɽ�
#define HSHK_OrderType_N			'*' // ��ȡ���ĳɽ�

struct StockTickDetailTime
{
	char m_nBuyOrSell;
	char m_nSecond;
};

// �ֱʼ�¼
struct StockTick
{
	short		   m_nTime;			   // ��ǰʱ�䣨�࿪�̷�������

	union
	{

		short			    m_nBuyOrSellOld;	 // �ɵģ�����
		char			    m_nBuyOrSell;	     // �ǰ��۳ɽ����ǰ����۳ɽ�(1 ����� 0 ������)
		StockTickDetailTime m_sDetailTime;       // ����������
	};

	long		   m_lNewPrice;        // �ɽ���
	unsigned long  m_lCurrent;		   // �ɽ���

	long		   m_lBuyPrice;        // ί���
	long		   m_lSellPrice;       // ί����

	//
	unsigned long  m_nChiCangLiang;	   // �ֲ���,�����Ʊ���ʳɽ���,�۹ɳɽ��̷���(Y,M,X�ȣ���������Դ��ȷ����

	//long  m_lOutside;         // ����
	//long  m_lInside;          // ����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nTime = YlsShortIntelToComputer(m_nTime);
			//m_nBuyOrSell = YlsShortIntelToComputer(m_nBuyOrSell);

			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lCurrent = YlsIntIntelToComputer(m_lCurrent);

			m_lBuyPrice = YlsIntIntelToComputer(m_lBuyPrice);
			m_lSellPrice = YlsIntIntelToComputer(m_lSellPrice);

			m_nChiCangLiang = YlsIntIntelToComputer(m_nChiCangLiang);
		}
		else
		{
			m_nTime = YlsShortComputerToIntel(m_nTime);
			//m_nBuyOrSell = YlsShortComputerToIntel(m_nBuyOrSell);

			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lCurrent = YlsIntComputerToIntel(m_lCurrent);

			m_lBuyPrice = YlsIntComputerToIntel(m_lBuyPrice);
			m_lSellPrice = YlsIntComputerToIntel(m_lSellPrice);

			m_nChiCangLiang = YlsIntComputerToIntel(m_nChiCangLiang);
		}
#endif
	}
};

//��ʷ��ʱ1��������
struct StockCompHistoryData
{
	long	m_lNewPrice;		// ���¼�
	unsigned long	m_lTotal;			/* �ɽ��� //���ڹ�Ʊ(��λ:��)
										����ָ��(��λ:�ٹ�) */
	float	m_fAvgPrice;		/*�ɽ���� */
	long	m_lBuyCount;        // ί����
	long	m_lSellCount;       // ί����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);
			m_lBuyCount = YlsIntIntelToComputer(m_lBuyCount);
			m_lSellCount = YlsIntIntelToComputer(m_lSellCount);
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);
			m_lBuyCount = YlsIntComputerToIntel(m_lBuyCount);
			m_lSellCount = YlsIntComputerToIntel(m_lSellCount);
		}
#endif
	}

};

// ��ʷ��ʱ��������
struct StockHistoryTrendHead 
{
	long				m_lDate;		// ����
	long				m_lPrevClose;	// ����

	union
	{
		HSStockRealTime			m_stStockData;		// ����ʵʱ��������
		HSIndexRealTime			m_stIndexData;		// ָ��ʵʱ��������
		HSHKStockRealTime		m_hkData;		// �۹�ʵʱ��������
		HSQHRealTime			m_qhData;		// �ڻ�ʵʱ��������
		HSWHRealTime			m_whData;		// ���ʵʱ��������
	};

	short			    m_nSize;		//  ÿ�������ܸ���
	short				m_nAlignment;   //  ������

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lDate = YlsIntIntelToComputer(m_lDate);
			m_lPrevClose = YlsIntIntelToComputer(m_lPrevClose);

			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			m_lDate = YlsIntComputerToIntel(m_lDate);
			m_lPrevClose = YlsIntComputerToIntel(m_lPrevClose);

			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};

//��ʱ���ư���������
struct StockHistoryTrend 
{
	StockHistoryTrendHead	m_shHead;		// ��ʷ��ʱ��������
	StockCompHistoryData	m_shData[1];	// ��ʷ��ʱ1��������
};

struct StockOtherDataDetailTime
{
	unsigned short m_nTime;
	unsigned short m_nSecond;
};

//struct JYSStatusInfo
//{
//	unsigned char m_nStatus1;
//	unsigned char m_nStatus2;
//	unsigned char m_nStatus3;
//	unsigned char m_nStatus4;
//};

// ����Ʊ��������
struct StockOtherData
{
	union
	{
		unsigned long					 m_nTimeOld;	  // ����ʱ��	
		unsigned short					 m_nTime;		  // ����ʱ��	
		StockOtherDataDetailTime		 m_sDetailTime;
	};

	unsigned long  m_lCurrent;    // ��������

	unsigned long  m_lOutside;    // ����
	unsigned long  m_lInside;     // ����

	union
	{
		unsigned long  m_lKaiCang;    // �񿪲�,�����Ʊ���ʳɽ���,�۹ɽ�������

		unsigned long  m_lPreClose;   // �������ʱ������������		
	};

	union
	{
		unsigned long  m_rate_status; // �������ʱ������״̬
									  // ���ڹ�Ʊ����Ϣ״̬��־,
									  // MAKELONG(MAKEWORD(nStatus1,nStatus2),MAKEWORD(nStatus3,nStatus4))

		unsigned long  m_lPingCang;   // ��ƽ��

		long		   m_lSortValue;  // ����ʱ��Ϊ������ֵ
	};

	void GetStatus(BYTE& bStatus1,BYTE& bStatus2,BYTE& bStatus3,BYTE& bStatus4)
	{

#ifndef HS_SUPPORT_UNIX
		WORD lo = LOWORD(m_rate_status);
		WORD hi = HIWORD(m_rate_status);
		
		bStatus1 = LOBYTE(lo);
		bStatus2 = HIBYTE(lo);
		bStatus3 = LOBYTE(hi);
		bStatus4 = HIBYTE(hi);
#endif
	}

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{			
		}
		else
		{
			m_sDetailTime.m_nTime = YlsShortIntelToComputer(m_sDetailTime.m_nTime);
			m_sDetailTime.m_nSecond = YlsShortIntelToComputer(m_sDetailTime.m_nSecond);
			m_lCurrent = YlsIntComputerToIntel(m_lCurrent);

			m_lOutside = YlsIntComputerToIntel(m_lOutside);
			m_lInside = YlsIntComputerToIntel(m_lInside);

			m_lKaiCang = YlsIntComputerToIntel(m_lKaiCang);
			m_rate_status =YlsIntComputerToIntel(m_rate_status);
		}
#endif
	}
};

//K������
struct StockDay
{
	unsigned long	m_lDate;  			/*year-month-day ,example: 19960616
								�������ݵı�ʾ�������£�yymmddhhnn(������ʱ��)
								yyָ����year - 1990������ݱ�ﷶΧ��1990 - 2011
								��0905131045��ָ���ǣ�1999��5��13��10��45�֡�*/
	long	m_lOpenPrice;		//��
	long	m_lMaxPrice;		//��
	long	m_lMinPrice;		//��
	long	m_lClosePrice;		//��
	long	m_lMoney;			//�ɽ����
	unsigned long	m_lTotal;			//�ɽ���   ��λ���ٹɣ��֣�

	//#ifdef SUPPORT_NETVALUE
	long	m_lNationalDebtRatio; // ��ծ����(��λΪ0.1��),����ֵ
	//#endif

	union
	{
		long	m_lPrevClose;
		struct
		{
			short	m_nMessageMask;	//������Ϣ����
			short	m_nOpenVolumn;  //���̳ɽ���
		};
	};
	//#ifndef SUPPORT_NETVALUE
	//	unsigned  m_lOutside : 28;		//���̳ɽ���
	//	unsigned  m_nVersion : 4;		//�汾�ţ�0���ɰ汾��1���°汾
	//#endif

	union
	{
		struct
		{
			short  m_nVolAmount;   //�ɽ�����
			short  m_nZeroVol;	   //�Ե��ɽ�����
		};
		long* m_pDataEx;		   // ����ǳ�Ȩ���� ChuQuanData �ṹ����ָ��
	};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lDate = YlsIntIntelToComputer(m_lDate);
			m_lOpenPrice = YlsIntIntelToComputer(m_lOpenPrice);
			m_lMaxPrice = YlsIntIntelToComputer(m_lMaxPrice);
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);
			m_lClosePrice = YlsIntIntelToComputer(m_lClosePrice);
			m_lMoney = YlsIntIntelToComputer(m_lMoney);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_lNationalDebtRatio = YlsIntIntelToComputer(m_lNationalDebtRatio);
		}
		else
		{
			m_lDate = YlsIntComputerToIntel(m_lDate);
			m_lOpenPrice = YlsIntComputerToIntel(m_lOpenPrice);
			m_lMaxPrice = YlsIntComputerToIntel(m_lMaxPrice);
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);
			m_lClosePrice = YlsIntComputerToIntel(m_lClosePrice);
			m_lMoney = YlsIntComputerToIntel(m_lMoney);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_lNationalDebtRatio = YlsIntComputerToIntel(m_lNationalDebtRatio);
		}
#endif
	}
};

// ��Ȩ�����ļ�������Ϣ
struct HSExRight 
{
	CodeInfo	m_CodeInfo;
	long 		m_lLastDate;	//��������
	long	    m_lCount;		//�ο�ʹ��
};
// ��Ȩ���ݽṹ
struct HSExRightItem
{
	int   	m_nTime;			// ʱ��
	float 	m_fGivingStock;		// �͹�
	float 	m_fPlacingStock;	// ���
	float 	m_fGivingPrice;		// �͹ɼ�
	float 	m_fBonus;			// �ֺ�
};

//ͨ���ļ�ͷ�ṹ
struct HSCommonFileHead
{
	long 	m_lFlag;   // �ļ����ͱ�ʶ
	time_t 	m_lDate;   // �ļ���������(����:32bit)
	long 	m_lVersion; // �ļ��ṹ�汾��ʶ
	long 	m_lCount;  // �����ܸ���	 
};

// �¼���ṹ ============================================================
// ������Ϣ����
#define BROKER_LENGTH		4		// ���ͺų���
#define NAME_LENGTH			36		// ���Ƴ���
// ϯλ��
struct HSHKBrokerCode
{
	char	m_sCode[BROKER_LENGTH];// �������ڴ�����У����ԣ�������0001-9999֮����κδ��롣	

#ifndef HS_SUPPORT_UNIX
	CString GetCode()
	{
		CString strRet(m_sCode, sizeof(m_sCode));
		return strRet;
	}
#endif
};
// ������Ϣ����
struct HSHKBroker
{
	char		 m_szEnglishName[NAME_LENGTH];	// ����(֤ȯ��)Ӣ����
	char		 m_szChineseDesc[NAME_LENGTH];	// ����(֤ȯ��)������
	char		 m_szTel[16];					// �绰����
	long		 m_lCount;						// ϯλ��
	HSHKBrokerCode m_ayCode[1];					// ����ϯλ��
};


// ����������Ϣ
struct HSHKBuyAndSellItem
{
	HSHKBrokerCode m_sCode;		// ����ϯλ����
	short		   m_nIsBuy;	// �������� 1: �� 0: ��
	short		   m_nNum;		// �ڼ���

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		//m_sCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_nIsBuy = YlsShortIntelToComputer(m_nIsBuy);
			m_nNum = YlsShortIntelToComputer(m_nNum);			
		}
		else
		{
			m_nIsBuy = YlsShortComputerToIntel(m_nIsBuy);
			m_nNum = YlsShortComputerToIntel(m_nNum);
		}
#endif
	}
};

// �����̾�����ϸ��Ϣ(��Ҫ����������)
struct HSHKBuyAndSell
{
	CodeInfo m_sCode;
	long	m_lBuyPrice;				// ���
	long	m_lSellPrice;				// ����
	long	m_lCount;					// ����
	HSHKBuyAndSellItem m_ayItem[1];		// ������
	// ע�⣬���ʱ����һ,�����������
	//       ����һ��������������˳����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_sCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lBuyPrice = YlsIntIntelToComputer(m_lBuyPrice);
			m_lSellPrice = YlsIntIntelToComputer(m_lSellPrice);
			m_lCount = YlsIntIntelToComputer(m_lCount);
		}
		else
		{
			for(int i = 0; i < m_lCount; i++ )
			{
				m_ayItem[i].To(cIntelToComputer);
			}

			m_lBuyPrice = YlsIntComputerToIntel(m_lBuyPrice);
			m_lSellPrice = YlsIntComputerToIntel(m_lSellPrice);
			m_lCount = YlsIntComputerToIntel(m_lCount);
		}
#endif
	}

};


// �˹��ܿ���Ҫ��������Դ�����Ƿ�ʹ�ã���Ϊ���ֻ�Ǹ��������̼��㣬���Ƿǳ����صĲ��裩��
// ĳ֧��Ʊ��ί�����
struct HSHKBrokerDealItem
{
	CodeInfo	m_sCode;
	char		m_cIsBuy;		// �������� 1: �� 0: ��
	char		m_cNum;			// �ڼ���
	char		m_cCount;		// ���ڵ��ĸ���
	char		m_cAlignment;	// Ϊ�˸��ṹ����
};
// ����ϯλ��ί�����
struct HSHKBrokerDeal
{
	HSHKBrokerCode	m_sCode;	// ϯλ��

	long	m_lCount;				// ����
	HSHKBrokerDealItem m_ayCode[1]; // ����ί�����
};


// ���ֶ���
#define		RMB		0			// �����
#define		HKD		1			// �۱�	
#define		USA		2			// ��Ԫ
// ��Ʊ���Ϲ�֤��־����
#define FinFlag_H	0x0001		// �ɽ������յ�ָ��֤ȯ������H�� ��־
#define FinFlag_3	0x0002		// # ������������㼰����ϵͳ��#�� ��־
#define FinFlag_O	0x0004		// �������Ʊ��Ȩ��O�� ��־
#define FinFlag_F	0x0008		// �������Ʊ�ڻ���F�� ��־
#define FinFlag_S	0x0010		// ��ʾ�����ù�Ʊ��Ҫӡ��˰��S�� ��־
#define FinFlag_P	0x0020		// �Ϲ�֤��P�� ��־
#define FinFlag_C	0x0040		// �Ϲ�֤��C�� ��־
#define FinFlag_X	0x0080		// �����Ϲ�֤��X�� ��־
#define FinFlag_E	0x0100		// ŷʽ���֤��E�� ��־
#define FinFlag_2	0x0200		// �ֽ���㡯@����־
#define FinFlag_8	0x0400		// ʵ���Ʊ���ա�*����־
// ��ع�Ʊ�ṹ
struct HSHKLineStockAndWarrants
{
	short m_nLineStock;		// ��ع�Ʊ��
	short m_nBuyCount;		// ����Ϲ�֤��
	short m_nSellCount;		// ����Ϲ�֤��
	short m_nAlignment;		// Ϊ�˸��ṹ����
	CodeInfo m_ayCode[1];   // �洢��ʽ����ع�Ʊ+�Ϲ�֤+�Ϲ�֤
};
// ������Ϣ��������Ϲ�֤����ع�Ʊ�����׵�λ�����ױ��֣�
struct HSHKStaticData
{
	CodeInfo	m_sCode;						// ����
	char		m_szEnglishName[NAME_LENGTH];	// Ӣ��
	char		m_szChineseName[NAME_LENGTH];	// ����
	char		m_szFinanceText[40];			// �����־�ı�

	short		m_cMoney;						// ���Ҵ���
	short 		m_cFinFlag;						// �����־
	long		m_lLotUnit;						// ���׵�λ(�Ƿ�ɷ�������????��

	// �����ֶ��Ϲ�֤ר��
	float		m_fPrice;						// �Ϲɼ�
	float		m_fExplicateAmplitude;			// ���겨��
	long		m_lExerDate;					// ������
	HSHKBrokerCode		m_sLineBroker;			// ��ؾ���

	HSHKLineStockAndWarrants m_sLineStock;		// ��ع�Ʊ���Ϲ�֤
};

struct HSHKSource
{
	char szFlags[4]; // EXHK
	char szCode[10]; // CODE
	char szMsg[40];  // MSG
	char szEnd[2];
};

// etf ʱʱ����
struct ETFAllStockNow
{
	// һ���Ʊ
	long			m_lETFBuyPrice1;
	unsigned long	m_lETFBuyCount1;
	long			m_lETFBuyPrice2;
	unsigned long	m_lETFBuyCount2;
	long			m_lETFBuyPrice3;
	unsigned long	m_lETFBuyCount3;	
	long			m_lETFBuyPrice4;
	unsigned long	m_lETFBuyCount4;
	long			m_lETFBuyPrice5;
	unsigned long	m_lETFBuyCount5;

	long			m_lETFSellPrice1;
	unsigned long	m_lETFSellCount1;
	long			m_lETFSellPrice2;
	unsigned long	m_lETFSellCount2;
	long			m_lETFSellPrice3;
	unsigned long	m_lETFSellCount3;
	long			m_lETFSellPrice4;
	unsigned long	m_lETFSellCount4;
	long			m_lETFSellPrice5;
	unsigned long	m_lETFSellCount5;

	// �Զ�
	long			m_lBuyAutoPrice;		// �Զ�
	unsigned long	m_lBuyAutoCount;		// �Զ�
	long			m_lSellAutoPrice;		// �Զ�
	unsigned long	m_lSellAutoCount;		// �Զ�

	long			m_lETFBuyAutoPrice;		// �Զ�
	unsigned long	m_lETFBuyAutoCount;		// �Զ�	
	long			m_lETFSellAutoPrice;	// �Զ�
	unsigned long	m_lETFSellAutoCount;	// �Զ�	

	long    m_lIPVE;

	//
	unsigned long    m_lReserv[9]; // ����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
		}
		else
		{
			m_lETFBuyPrice1	=   YlsIntComputerToIntel(m_lETFBuyPrice1);
			m_lETFBuyCount1	=	YlsIntComputerToIntel(m_lETFBuyCount1);
			m_lETFBuyPrice2	=	YlsIntComputerToIntel(m_lETFBuyPrice2);
			m_lETFBuyCount2	=	YlsIntComputerToIntel(m_lETFBuyCount2);
			m_lETFBuyPrice3	=	YlsIntComputerToIntel(m_lETFBuyPrice3);
			m_lETFBuyCount3	=	YlsIntComputerToIntel(m_lETFBuyCount3);	
			m_lETFBuyPrice4	=	YlsIntComputerToIntel(m_lETFBuyPrice4);
			m_lETFBuyCount4	=	YlsIntComputerToIntel(m_lETFBuyCount4);
			m_lETFBuyPrice5	=	YlsIntComputerToIntel(m_lETFBuyPrice5);
			m_lETFBuyCount5	=	YlsIntComputerToIntel(m_lETFBuyCount5);

			m_lETFSellPrice1	=   YlsIntComputerToIntel(m_lETFSellPrice1);
			m_lETFSellCount1	=	YlsIntComputerToIntel(m_lETFSellCount1);
			m_lETFSellPrice2	=	YlsIntComputerToIntel(m_lETFSellPrice2);
			m_lETFSellCount2	=	YlsIntComputerToIntel(m_lETFSellCount2);
			m_lETFSellPrice3	=	YlsIntComputerToIntel(m_lETFSellPrice3);
			m_lETFSellCount3	=	YlsIntComputerToIntel(m_lETFSellCount3);
			m_lETFSellPrice4	=	YlsIntComputerToIntel(m_lETFSellPrice4);
			m_lETFSellCount4	=	YlsIntComputerToIntel(m_lETFSellCount4);
			m_lETFSellPrice5	=	YlsIntComputerToIntel(m_lETFSellPrice5);
			m_lETFSellCount5	=	YlsIntComputerToIntel(m_lETFSellCount5);

			// �Զ�
			m_lBuyAutoPrice = YlsIntComputerToIntel(m_lBuyAutoPrice);		// �Զ�
			m_lBuyAutoCount = YlsIntComputerToIntel(m_lBuyAutoCount);		// �Զ�
			m_lSellAutoPrice = YlsIntComputerToIntel(m_lSellAutoPrice);		// �Զ�
			m_lSellAutoCount = YlsIntComputerToIntel(m_lSellAutoCount);		// �Զ�

			m_lETFBuyAutoPrice = YlsIntComputerToIntel(m_lETFBuyAutoPrice);		// �Զ�
			m_lETFBuyAutoCount = YlsIntComputerToIntel(m_lETFBuyAutoCount);		// �Զ�	
			m_lETFSellAutoPrice = YlsIntComputerToIntel(m_lETFSellAutoPrice);	// �Զ�
			m_lETFSellAutoCount = YlsIntComputerToIntel(m_lETFSellAutoCount);	// �Զ�	

			m_lIPVE = YlsIntComputerToIntel(m_lIPVE);

			//
			for(int i = 0; i < 9; i++ )
				m_lReserv[i] = YlsIntComputerToIntel(m_lReserv[i]); // ����			
		}
#endif
	}
};

struct ETFStockNowData
{
	HSStockRealTime  m_stStockData;
	ETFAllStockNow   m_etf;

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_stStockData.To(cIntelToComputer);
		m_etf.To(cIntelToComputer);
#endif
	}
};

// ʱʱ���ݷ���
union ShareRealTimeData
{
	HSStockRealTime			m_nowData;		// ����ʵʱ��������
	HSStockRealTime			m_stStockData;

	HSIndexRealTime			m_indData;		// ָ��ʵʱ��������
	HSHKStockRealTime		m_hkData;		// �۹�ʵʱ��������
	HSQHRealTime			m_qhData;		// �ڻ�ʵʱ��������
	HSWHRealTime			m_whData;		// ���ʵʱ��������	

	HSQHRealTime_Min		m_qhMin;	
};

union ShareRealTimeData_ETF
{
	HSStockRealTime			m_nowData;		// ����ʵʱ��������
	HSIndexRealTime			m_indData;		// ָ��ʵʱ��������
	HSHKStockRealTime		m_hkData;		// �۹�ʵʱ��������
	HSQHRealTime			m_qhData;		// �ڻ�ʵʱ��������
	HSWHRealTime			m_whData;		// ���ʵʱ��������

	ETFStockNowData			m_etfData;

	HSQHRealTime_Min		m_qhMin;
};

struct CalcData_Share // ��Ʊ����
{
	long 			m_lMa10;			// 10�죬20�죬50�����̾���
	long 			m_lMa20;
	long 			m_lMa50;

	long 			m_lMonthMax;		// ��������
	long 			m_lMonthMin;		

	long 			m_lYearMax;			// ��������
	long 			m_lYearMin;

	long			m_lHisAmplitude;	// ��ʷ����(ʹ��ʱ��1000Ϊ�ٷֱ�����

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lMa10 = YlsIntIntelToComputer(m_lMa10);
			m_lMa20 = YlsIntIntelToComputer(m_lMa20);
			m_lMa50 = YlsIntIntelToComputer(m_lMa50);

			m_lMonthMax = YlsIntIntelToComputer(m_lMonthMax);
			m_lMonthMin = YlsIntIntelToComputer(m_lMonthMin);

			m_lYearMax = YlsIntIntelToComputer(m_lYearMax);
			m_lYearMin = YlsIntIntelToComputer(m_lYearMin);

			m_lHisAmplitude = YlsIntIntelToComputer(m_lHisAmplitude);
		}
		else
		{
			m_lMa10 = YlsIntComputerToIntel(m_lMa10);
			m_lMa20 = YlsIntComputerToIntel(m_lMa20);
			m_lMa50 = YlsIntComputerToIntel(m_lMa50);

			m_lMonthMax = YlsIntComputerToIntel(m_lMonthMax);
			m_lMonthMin = YlsIntComputerToIntel(m_lMonthMin);

			m_lYearMax = YlsIntComputerToIntel(m_lYearMax);
			m_lYearMin = YlsIntComputerToIntel(m_lYearMin);

			m_lHisAmplitude = YlsIntComputerToIntel(m_lHisAmplitude);
		}
#endif
	}
};

struct CalcData_GP
{
};

struct CalcData_GG // �۹ɼ���
{
	union
	{
		long 		m_lPEratio;			// Ԥ����ӯ�� ��Ʊ���
		long		m_fOverFlowPrice;	// ��� �Ϲ�֤���
	};

	union
	{
		long 		m_lWeekratio;		// Ԥ����Ϣ�� ��Ʊ���
		long		m_FCSRatio;			// �عɱ��� �Ϲ�֤���
	};

	union
	{
		long 		m_lCutPriceRatio;	// ������ ��Ʊ���
		long		m_fValidCSRatio;	// ��Ч�عɱ��� �Ϲ�֤���
	};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lPEratio = YlsIntIntelToComputer(m_lPEratio);
			m_lWeekratio = YlsIntIntelToComputer(m_lWeekratio);
			m_lCutPriceRatio = YlsIntIntelToComputer(m_lCutPriceRatio);
		}
		else
		{
			m_lPEratio = YlsIntComputerToIntel(m_lPEratio);
			m_lWeekratio = YlsIntComputerToIntel(m_lWeekratio);
			m_lCutPriceRatio = YlsIntComputerToIntel(m_lCutPriceRatio);
		}
#endif
	}
};

struct CalcData_QH // �ڻ�����
{
	long 			m_lLotUnit;			// ÿ�ֵ�λ(�൱��ʵʱ�������nHand,�����Ƿ�ɽ�������������
	long 			m_lDiffUnit;		// �䶯��λ(1/1000Ԫ)
	long 			m_lMaxDeal;			// ����걨��(��λ����Լ��λ)
	long			m_lMarginRatio;		// ��֤�����(1/100 = ?%)

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lLotUnit = YlsIntIntelToComputer(m_lLotUnit);
			m_lDiffUnit = YlsIntIntelToComputer(m_lDiffUnit);
			m_lMaxDeal = YlsIntIntelToComputer(m_lMaxDeal);
			m_lMarginRatio = YlsIntIntelToComputer(m_lMarginRatio);
		}
		else
		{
			m_lLotUnit = YlsIntComputerToIntel(m_lLotUnit);
			m_lDiffUnit = YlsIntComputerToIntel(m_lDiffUnit);
			m_lMaxDeal = YlsIntComputerToIntel(m_lMaxDeal);
			m_lMarginRatio = YlsIntComputerToIntel(m_lMarginRatio);
		}
#endif
	}
};

// data struct in file loncdp.*
struct StockCdp
{
	CodeInfo		m_CodeInfo;
	long			m_lNoUse[5];		//����
	unsigned long	m_l5DayVol;			//����ƽ������

	union
	{
		CalcData_GP m_GP;
		CalcData_GG m_GG;
		CalcData_QH m_QH;
	};

	CalcData_Share  m_Share;
};

// added by Ben 20100505
#define IS_CURR_GOLD(CODE,CODETYPE)( (!strcmp(CODE, "AG999") || !strncmp(CODE, "AG9999",6) ||!strncmp(CODE, "AU100",5) || !strncmp(CODE, "AU50",4) ||!strncmp(CODE, "AU9995",6) || !strncmp(CODE, "AU9999",6) || !strncmp(CODE, "PT9995",6) || (MakeMainMarket(CODETYPE) == (HJ_MARKET | HJ_WORLD)) ))
#define GETBUYCOUNT(X)  (X->m_lBuyCount1 + X->m_lBuyCount2 + X->m_lBuyCount3 + X->m_lBuyCount4 + X->m_lBuyCount5)
#define GETSELLCOUNT(X) (X->m_lSellCount1 + X->m_lSellCount2 + X->m_lSellCount3 + X->m_lSellCount4 + X->m_lSellCount5)
// end add

#pragma pack()
#ifndef HS_SUPPORT_UNIX
#pragma pack()
#else
#endif
#endif