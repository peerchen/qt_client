/*******************************************************************************
 * Copyright (c)2003, %111111111%�������޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ�HSCommunicationClient.h
 * �ļ���ʶ���ͻ���ʹ�õ�ͨѶ���ͷ�ļ�
 * ժ    Ҫ�����ڿͻ��������������ͨѶ�ӿ�ͷ�ļ����
 *
 * ��ǰ�汾��dfx2003
 * ��    �ߣ�Ѷ������
 * ������ڣ�2003-8-26
 *
 * ȡ���汾��
 * ԭ �� �ߣ�
 * ������ڣ�
 * ��	 ע��
 *
 * �޸ļ�¼��
 * ��    �ߣ�
 * �޸����ڣ�2004��2��26��
 * �޸����ݣ��޸�StockDay�ṹ,����m_lNationalDebtRatio���ծ����,����ֵ
 *******************************************************************************/
#ifndef _HSCOMMUNICATIONCLIENT_HEADER_FILE_
#define _HSCOMMUNICATIONCLIENT_HEADER_FILE_

#include "hscommunication.h"

#ifndef HS_SUPPORT_UNIX
#include "commapi.h"
#include "afxtempl.h"
#endif

// �ṹ������ �������
#define FinanceData HisFinanceData
#define StockDataOld	RealTimeData

#define QH_Bourse	FUTURES_MARKET
#define BK_Bourse	(STOCK_MARKET|SYSBK_BOURSE)
#define OT_Bourse	STOCK_WHILOM_NAME_MARKET // (�����г���Ŀǰ��Ҫ�����ڲ����࣬����Ʊ��������)

//#define SC_Others			0x11 // ���� 0x09
#define SC_Union			0x40 // ���

// k�߰���
#define SD_NEWS				0x0001	//��Ҫ����
#define SD_BULLETIN			0x0002	//������Ϣ
#define SD_SPECIFICATION	0x0004	//����֪ͨ
#define SD_MIDREPORT		0x0008	//�б�ժҪ
#define SD_ANNALS			0x0010	//�걨ժҪ
#define SD_SPSCHEME			0x0020	//���䷽��
#define SD_REVIEW			0x0040	//������˵
#define SD_CHUQUAN			0x0080	//��Ȩ����
#define SD_SelectStockMark	0x0100	//ѡ����ʾ
#define SD_FENSHITRACEDATA	0x0200	//ʱ������
#define SD_MEMOINFO			0x0400	//����¼
#define SD_FROMSRV			0x0800	//���������Է�����
#define SD_UserDataPtr		0x2000	//ʹ������ָ��

#define Big_NowData_Count  11
#define GeGu_NowData_Count 18


// ͨѶ���ඨ�忪ʼ --------------------------------------------------
#define RT_INITIALINFO_          		0x0100 // ��ʼ��

#define RT_REALTIME_					0x0200 // ����

#define RT_TREND_						0x0300 // ��ʱ����

#define RT_TECHDATA_					0x0400 // �̺����

#define RT_TEXTDATAWITHINDEX_NEGATIVE_	0x0500 // ��Ѷ

#define RT_STOCKTICK_					0x0600 // �ֱ�

#define RT_LEAD_						0x0700 // ����

#define RT_CURRENTFINANCEDATA_			0x0800 // ����

#define RT_MASSDATA_             		0x0900 // ��								

#define RT_AUTOPUSH_             		0x0A00 // ����
#define RT_AUTOPUSH_MASS           		0x0AAA // ������
// ͨѶ���ඨ����ֹ -------------------------------------------------


#ifdef SUPPORT_NETVALUE
#define TECH_KLINE_COMM_DATA StockCompDayDataEx
#define ANSDAYDATA		 AnsDayDataEx
#else 
#define TECH_KLINE_COMM_DATA StockCompDayData
#define ANSDAYDATA		 AnsDayData
#endif

#ifdef SUPPORT_NEW_GENERALSORT
#define RT_GENERALSORT_MACRO RT_GENERALSORT_EX
#define ReqGeneralSort_MACRO ReqGeneralSortEx
#define AnsGeneralSort_MACRO AnsGeneralSortEx
#else
#define RT_GENERALSORT_MACRO RT_GENERALSORT
#define ReqGeneralSort_MACRO ReqGeneralSort
#define AnsGeneralSort_MACRO AnsGeneralSort
#endif

/* ʹ���� ���� �ֶ� */
#define SRV_TYPE_HQ		CEV_Connect_HQ_//0x01	/* ���� */
#define SRV_TYPE_ZX		CEV_Connect_ZX_//0x02	/* ��Ѷ */
#define SRV_TYPE_WH		CEV_Connect_WH_//0x04	/* ��� */
#define SRV_TYPE_QH		CEV_Connect_QH_//0x08	/* �ڻ� */
#define SRV_TYPE_GG		CEV_Connect_GG_//0x09	/* �۹� */

////K������
//struct StockDay
//{
//	long	m_lDate;  			/*year-month-day ,example: 19960616
//								�������ݵı�ʾ�������£�yymmddhhnn(������ʱ��)
//								yyָ����year - 1990������ݱ�ﷶΧ��1990 - 2011
//								��0905131045��ָ���ǣ�1999��5��13��10��45�֡�*/
//	long	m_lOpenPrice;		//��
//	long	m_lMaxPrice;		//��
//	long	m_lMinPrice;		//��
//	long	m_lClosePrice;		//��
//	long	m_lMoney;			//�ɽ����
//	long	m_lTotal;			//�ɽ���   ��λ���ٹɣ��֣�
//
//#ifdef SUPPORT_NETVALUE
//	long	m_lNationalDebtRatio; // ��ծ����(��λΪ0.1��),����ֵ
//#endif
//
//	union
//	{
//		long	m_lPrevClose;
//		struct
//		{
//			short	m_nMessageMask;	//������Ϣ����
//			short	m_nOpenVolumn;  //���̳ɽ���
//		};
//	};
//#ifndef SUPPORT_NETVALUE
//	unsigned  m_lOutside : 28;		//���̳ɽ���
//	unsigned  m_nVersion : 4;		//�汾�ţ�0���ɰ汾��1���°汾
//#endif
//
//	union
//	{
//		struct
//		{
//			short  m_nVolAmount;   //�ɽ�����
//			short  m_nZeroVol;	   //�Ե��ɽ�����
//		};
//		long* m_pDataEx;		   // ����ǳ�Ȩ���� ChuQuanData �ṹ����ָ��
//	};
//};

struct DiskStockDay
{
	long	m_lDate;			/*year-month-day ,example: 19960616
								�������ݵı�ʾ�������£�yymmddhhnn(������ʱ��)
								yyָ����year - 1990������ݱ�ﷶΧ��1990 - 2011
								��0905131045��ָ���ǣ�1999��5��13��10��45�֡�*/
	float	m_lOpenPrice;		//��
	float	m_lMaxPrice;		//��
	float	m_lMinPrice;		//��
	float	m_lClosePrice;		//��
	float	m_lMoney;			/*�ɽ����
									���̵�λ����Ԫ    ���ɵ�λ��Ԫ*/
	float	m_lTotal;			//�ɽ���   ��λ���ٹɣ��֣�

	short	m_nMessageMask;		//������Ϣ����
};

struct RealTimeDataSource
{
	StockUserInfo	  m_stStockInfo;
	StockOtherData    m_sOthData;
	union
	{
		HSIndexRealTime  m_stIndexData;
		HSStockRealTime  m_stStockData;
		HSQHRealTime	 m_qhNowData;
	};
};

struct StockInfo//Old
{
	char		m_cStockName[STOCK_NAME_SIZE];	// ��Ʊ����
	CodeInfo	m_ciStockCode;		// ��Ʊ����ṹ
	long		m_lPrevClose;		// ����
	long		m_l5DayVol;			// 5����(�Ƿ���ڴ˼���ɽ���λ����������

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN

		m_ciStockCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lPrevClose = YlsIntIntelToComputer(m_lPrevClose);
			m_l5DayVol = YlsIntIntelToComputer(m_l5DayVol);			
		}
		else
		{
			m_lPrevClose = YlsIntComputerToIntel(m_lPrevClose);
			m_l5DayVol = YlsIntComputerToIntel(m_l5DayVol);
		}
#endif
	}
};

struct FileNowData//Old
{
	StockInfo		 m_stStockInfo;
	union
	{
		ShareRealTimeData	 m_sAll;

		HSIndexRealTime		 m_stIndexData;
		HSStockRealTime      m_stStockData;
		HSQHRealTime		 m_qhNowData;
	};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_stStockInfo.To(cIntelToComputer);

		switch(MakeMarket(m_stStockInfo.m_ciStockCode.m_cCodeType))
		{
		case (HSMarketDataType)STOCK_MARKET:		     // ��Ʊ
			if( MakeIndexMarket(m_stStockInfo.m_ciStockCode.m_cCodeType) )
				m_sAll.m_indData.To(cIntelToComputer);   //return (sizeof(HSIndexRealTime) + nAdd); // ָ��ʵʱ��������
#ifdef Support_MakeETF
			else if( MakeETF(m_stStockInfo.m_ciStockCode.m_cCodeType) )
				;	
#endif
			//m_sAll.//return (sizeof(ETFStockNowData) + nAdd);
			else
				m_sAll.m_nowData.To(cIntelToComputer);		//return (sizeof(HSStockRealTime) + nAdd);
			break;
		case (HSMarketDataType)HK_MARKET:				 // �۹�
			m_sAll.m_hkData.To(cIntelToComputer);		 //return (sizeof(HSHKStockRealTime) + nAdd);
			break;
		case (HSMarketDataType)FUTURES_MARKET:			 // �ڻ�
		case (HSMarketDataType)WP_MARKET:
			m_sAll.m_qhData.To(cIntelToComputer);		 //return (sizeof(HSQHRealTime) + nAdd);
			break;
		case (HSMarketDataType)FOREIGN_MARKET:			 // ���
			m_sAll.m_whData.To(cIntelToComputer);		 //return (sizeof(HSWHRealTime) + nAdd);
			break;
		default:
			break;
		}
#endif
	}
};

#if 0
//��Ʊ��ϸ��Ϣ �ɰ汾
struct StockInfo
{
	char      m_cVersion;		//���� �汾�ţ�0XFF�����汾���������ɰ汾��
	char      m_cStockName[8];	//֤ȯ����
	CodeInfo  m_ciStockCode;	//֤ȯ��Ϣ
	long      m_lPrevClose;		//ǰ����
};

//�ļ�ʵʱ����
struct FileNowData
{
	StockInfo		 m_stStockInfo;	//��Ʊ��Ϣ
	union
	{
		HSIndexRealTime   m_stIndexData;	//ָ��
		HSStockRealTime   m_stStockData;	//����
		HSQHRealTime	  m_qhNowData;	//�ڻ�	

		ShareRealTimeData m_otNowData;	//����ʱʱ����
	};	
};
#endif

#define FileNowDataOld FileNowData

//��Ȩ��۸� = ��Ȩǰ�۸� * m_fMulit + m_fAdd
struct ChuQuanData
{
	enum { NotCalc,Calc/* ����*/ };

	char	m_cMask;		//ѡ��

	long	m_lDate;		//��Ȩ��
	float	m_fMulit;		//��˵�����
	float	m_fAdd;			//��ӵ�����
	float	m_fSGBL;		//�͹ɱ���
	float	m_fPGBL;		//��ɱ���
	float	m_fPGJ;			//��ɼ�
	float	m_fXJHL;		//�ֽ����
};

struct SuccResult  // ѡ�ɳɹ���Ϣ
{
	long	m_lDate;  // ʱ��
	long	m_nPos;   // ��ǰk��λ��

#ifndef HS_SUPPORT_UNIX
	static CString m_strTip; // ѡ�ɳɹ���Ϣ��ʾ

	SuccResult(long lDate,long nPos)
	{
		m_lDate = lDate; // ʱ��
		m_nPos  = nPos;
	}
#endif

};

#ifndef HS_SUPPORT_UNIX

template <class TYlsMapBaseType>
class CMapStringToPtrEx : public CMapStringToPtr
{
public:
	// add a new (key, value) pair
	void SetAt(LPCTSTR key, void* newValue)
	{
		void* pData;
		if( this->Lookup(key,pData) ) // �Ƿ����
		{
			return;
		}
		CMapStringToPtr::SetAt(key, newValue);	
	}

	BOOL SetAt(LPCTSTR key, TYlsMapBaseType newValue)
	{
		void* pData;
		if( this->Lookup(key,pData) ) // �Ƿ����
		{
			return FALSE;
		}
		CMapStringToPtr::SetAt(key, (void*)newValue);
		return TRUE;
	}

	BOOL SetAt(CodeInfo* pCode, TYlsMapBaseType newValue)
	{
		if( pCode == NULL )
			return FALSE;
		CString key;
		key.Format("%s",pCode->GetKey());
		void* pData;
		if( this->Lookup(key,pData) ) // �Ƿ����
		{
			return FALSE;
		}
		CMapStringToPtr::SetAt(key, (void*)newValue);
		return TRUE;
	}

	// Lookup
	BOOL Lookup(LPCTSTR key, void*& rValue) const
		{ return CMapStringToPtr::Lookup(key, rValue); }

	BOOL Lookup(CodeInfo* pCode, char* strKey,TYlsMapBaseType& rValue) const
	{ 		
		return CMapStringToPtr::Lookup( pCode->GetKey(strKey), (void*&)rValue ); 
	}

	void Free()
	{
		POSITION pos = this->GetStartPosition();
		CString	sName;
		void *pVal;
		while (pos != NULL)
		{
			this->GetNextAssoc (pos, sName, pVal);
			if(pVal != NULL)
			{
				delete (TYlsMapBaseType)pVal;
			}
		}
		this->RemoveAll();
	}
};
#endif

// data struct in file lonhis.*
struct StockDetailedMinuteData
{
	unsigned long	m_nTotalHold;	   //�ڻ��ܳ�	
	unsigned long	m_lOutside;        //���̳ɽ���
	short			m_nReserved[4];    //����
};
//���̷�ʱ����
struct IndexDetailedMinuteData
{
	short	m_nRiseCount;       //���Ǽ���
	short	m_nFallCount;       //�µ�����
	short	m_nLead;            //����ָ��
	short	m_nRiseTrend;       //��������
	short	m_nFallTrend;       //�µ�����
	short   m_nReserved;        //4�ӽڶ��룬����
	long	m_lADL;             //ADLָ��
};

//���ɷ�ʱ
struct StockHistoryData
{
	long	m_lNewPrice;		//���¼�
	unsigned long	m_lTotal;           /*�ɽ��� ���ڹ�Ʊ(��λ:��)
								  ����ָ��(��λ:�ٹ�)*/
	float	m_fAvgPrice;	    /*�ɽ����  ���ڹ�Ʊ(��λ:Ԫ) ,�ڻ�Ϊ�ֲ���
								����ָ��(��λ:��Ԫ)*/
	unsigned long	m_lBuyCount;        //ί����
	unsigned long	m_lSellCount;       //ί����
	union
	{
		StockDetailedMinuteData	m_dmStock;	//��������
		IndexDetailedMinuteData	m_dmIndex;	//��������
	};
};

struct YlsBigTrace
{
	CodeInfo		m_ciStockCode;
	HSIndexRealTime m_indData;
};
struct StockNowData : public HSStockRealTime
{
	unsigned long  m_lOutside;    //���̳ɽ���
};

/*
//��Ʊ��ϸ��Ϣ
struct StockInfo : public StockInfoOld
{
	char 		m_cPYJC[4];		  //֤ȯ���Ƶ�ƴ�����
};
//�ļ�ʵʱ����	��
struct FileNowData
{
	StockInfo     m_stStockInfo;		//��Ʊ��Ϣ
	union
	{
		IndexRealTime  m_stIndexData;	//ָ��
		StockNowData  m_stStockData;	//����
	};	
};
*/

//ʵʱ��������
struct StockExTraceData : public StockTick
{
	union
	{
		struct			//�ɽ���ϸ
		{
			long	m_lBuyCount;        //ί����
			long	m_lSellCount;       //ί����
		};
		struct			//��ʷί��������
		{
			long	m_lPrice;		//ί��������
			unsigned long	m_lVolume;		//ί��������
		};
	};
};
struct DetailedVolume
{
	short		m_nVolMount;		//�ɽ�����
	unsigned	m_lVolume   : 28;  //�ɽ���
	unsigned	m_nVolClass : 4;	//�ɽ������ࣺ����3������2������1���Ե�������1������2������3��
};

struct StockStatVolumeData
{
	long			m_lDate;		//���ڣ�ͬ��������
	DetailedVolume	m_dvVol[7];		//7 �ֳɽ�����������
};

#define MAX_TRACE			10   // ��ʷ�ɽ���ϸ���ݽṹ
struct StockHistoryTraceData
{
	long			m_lDate;				//���ڣ�ͬ��������
	StockTick	m_stTrace[MAX_TRACE];	//ÿ�ʳɽ����ǰʮ��
};

#if 0
//���ɷֱ�
struct StockTrace
{
	short	m_nTotal;					 //ʵ������
	long	m_lNextPoint;				//-1:no next else:next block file point
	StockTick	m_stData[1000];		//���ɷֱ�
};
#endif

//��ʷ����
struct StockHisBuySell
{
	short				m_nTotal;		//ʵ������
	long				m_lNextPoint;	//-1:no next else:next block file point
	BuySellOrderData	m_sbData[100];	//��ʷ����

#ifndef HS_SUPPORT_UNIX
	StockHisBuySell()
	{
		memset(this, 0, sizeof(StockHisBuySell));
		m_lNextPoint = -1;
	}
#endif

};

////���̳ɽ���ϸ
//struct BigTraceData
//{
//	DataHead			m_dhHead;
//	short				m_nSize;
//	MajorIndexItem	m_ntrData[1];
//};
//struct BuySellData
//{
//	DataHead			m_dhHead;
//	short				m_nHisLen;
//	BuySellPowerData	m_pHisData[1];
//};
#define BuySellData AnsBuySellPower
// ֻҪ��ʱ����
//�ر𱨵�
struct SendReportDataOld
{
	CodeInfo		m_ciStockCode;
	//long			m_lCurrent;
	HSStockRealTime	m_nowData;
	StockOtherData	m_othData;
};

//�û��˴���DISK�����ݽṹ(�������յ�����վ����) WRITEDATA
struct LocalAskData
{
	short	m_nType;		//=WRITEDATA ASKDATA PREASKDATA
	long	m_lDate;		//����
	long	m_lSize;		//�յ���վ���ݵĳ���
	void*	m_pBuffer;		//���ݻ�����ָ��
	long	m_lTrans;		//�Ѵ�������ݳ���
};
struct StockData
{
	CodeInfo	m_ciStockCode;
	short		m_nTime;
	union
	{
		StockNowData	m_nowData;
		IndexRealTime 	m_indData;
	};	
};

//struct StockCdp
//{
//	char	m_cCode[6];		//֤ȯ����
//	long	m_lNoUse[5];	//����
//	long	m_l5DayVol;		//����ƽ������
//};

struct IndHisDayData
{
	DataHead		m_dhHead;
	long			m_lANewPrice;	//A���ּ�
	long			m_lBNewPrice;	//B���ּ�
	IndexRealTime	m_indData;		//��֤30����ָ֤��NOW����
	short			m_nDayLen;
	union
	{
		StockDay				m_sdData[1];
		StockStatVolumeData		m_svData[1];
		StockHistoryTraceData	m_stData[1];
	};
};
struct OnlyDayData
{
	DataHead	m_dhHead;
	short		m_nSize;
	union
	{
		StockDay				m_sdData[1];
		StockStatVolumeData		m_svData[1];
		StockHistoryTraceData	m_stData[1];
	};
};
struct MultiStockHisData
{
	DataHead			m_dhHead;
	CodeInfo	 		m_ciStockCode;
	short				m_nHisLen;
	StockNowData		m_nowData;	
	PriceVolItem		m_pHisData[1];
};

// ��鰴�չ�Ʊ����ʱ
struct StockUserBlock : public StockUserInfo
{
	char m_cStockName[BLOCK_NAME_LENGTH];	//�������

#ifndef HS_SUPPORT_UNIX
	StockUserBlock()
	{
		memset(m_cStockName,0,sizeof(m_cStockName));
	}

	CString	GetName()
	{
		return CString(m_cStockName).Left(BLOCK_NAME_LENGTH);
	}

	void Copy(StockUserInfo* pStock);
	//{	
	//	StockUserInfo::Copy(pStock);

	//	if( pStock )
	//	{
	//		strncpy(m_cStockName,pStock->GetName(),sizeof(m_cStockName)); //�������
	//	}
	//}

	void Serialize(CArchive& ar);
	//{
	//	StockUserInfo::Serialize(ar);
	//	if( ar.IsStoring() )
	//	{
	//		ar << GetName();			// ֤ȯ����
	//	}
	//	else
	//	{
	//		CString str;
	//		ar >> str;
	//		strncpy(m_cStockName,str,sizeof(m_cStockName));
	//	}
	//}
#endif

};

// ����������(ֻ��nt��֧��)
struct AutoMassData
{	
	CodeInfo		m_ciStockCode;		// ��Ʊ����

	short			m_nMask;		    // �����,��ǰֻ֧������
	short 			m_nTime;        	// �࿪�̵ķ�����
	long			m_lNewPrice;		// ���¼�
	unsigned long			m_lCurrent;			// ����
};

struct AnsHSAutoPushDataMass
{
	DataHead	 m_dhHead;			//���ݱ�ͷ
	
	short		 m_nSize;			//���ݸ���
	AutoMassData m_pstData[1];		//����ʵʱ���͵�����
};

//  ������ж� ��������������ͨ����Ϳ��Ż���(LOF) 2004-09-10
#define IsFund(Type) (MakeMarket(Type) == STOCK_MARKET && (MakeSubMarket(Type) == KIND_FUND || MakeSubMarket(Type) == KIND_LOF))

//  �ɽ���Ϊ0���г�����(û�о��ߵ�)
#define IsZeroVolType(Type) ( (MakeMarket(Type) == WP_MARKET) || (MakeMarket(Type) == FOREIGN_MARKET) /*|| Type == (HK_KIND_FUTURES_INDEX|INDEX_BOURSE|HK_MARKET)*/)


// �����г���Ϣ�ṹ(�ͻ��˱���ʹ��)
struct DiskBourseInfo
{
	StockTypeName	m_stGroupName;	// �г�����(��Ӧ�г����)

	int				m_lDate;		// ����
	int				m_nBourseType;
	int				m_nStockCount;	
	int			    m_cType;

	unsigned int	m_dwCRC;		/* CRCУ���� */

	StockType		m_stNewType[60];		// ֤ȯ��Ϣ
	char			m_cPanHouFlag[60];		// �Ƿ��������̱�־

#ifndef HS_SUPPORT_UNIX
	DiskBourseInfo()
	{
		memset(this, 0, sizeof(DiskBourseInfo));
	}
#endif

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lDate = YlsIntIntelToComputer(m_lDate);
			m_nBourseType = YlsIntIntelToComputer(m_nBourseType);
			m_nStockCount = YlsIntIntelToComputer(m_nStockCount);
			m_cType = YlsIntIntelToComputer(m_cType);
			m_dwCRC = YlsIntIntelToComputer(m_dwCRC);

			for( int i = 0; i < m_cType; i++ )
			{
				m_stNewType[i].To(cIntelToComputer);
			}
		}
		else
		{
			for( int i = 0; i < m_cType; i++ )
			{
				m_stNewType[i].To(cIntelToComputer);
			}

			m_lDate = YlsIntComputerToIntel(m_lDate);
			m_nBourseType = YlsIntComputerToIntel(m_nBourseType);
			m_nStockCount = YlsIntComputerToIntel(m_nStockCount);
			m_cType = YlsIntComputerToIntel(m_cType);
			m_dwCRC = YlsIntComputerToIntel(m_dwCRC);
		}
#endif
	}
};

template<class TYPE = DWORD>
struct CStyleSetting
{
protected:
	TYPE m_dwStyle;

public:
	CStyleSetting(TYPE dwStyle = 0)   { m_dwStyle = dwStyle; }

	void    AddStyle(TYPE dwStyle)	   { m_dwStyle |= dwStyle;  }
	void    RemoveStyle(TYPE dwStyle) { m_dwStyle &= ~dwStyle; }
	TYPE    IsStyle(TYPE dwStyle)     { return (m_dwStyle & dwStyle); }
	void    SetStyle(TYPE dwStyle)	   { m_dwStyle = dwStyle; }
	TYPE    GetStyle()				   { return m_dwStyle; }
};


#endif /*_HSCOMMUNICATIONCLIENT_HEADER_FILE_*/
