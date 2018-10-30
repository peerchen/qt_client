/*******************************************************************************
* Copyright (c)2003, 雁联计算系统有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：YLink1.2
* 作    者：YLink王工
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/



#if !defined(_HSServerDataPath_h_)
#define _HSServerDataPath_h_

#include "stdafx.h"

#include "ylsmapwordtoptr.h"
#include "ylsmapstringtoptr.h"

#include "sharedmemory.h"
#include "serverstructex.h"

#include "../comm/userreportheader.h"


#define RT_ETF_TREND_CFG  0x1111

struct StockKey
{
	char		m_stkey[64];
	CodeInfo	m_ciInfo;

	StockKey()
	{
		memset(this,0,sizeof(StockKey));
	}
};

//	发送端-股票位置索引
struct CHSStockPosition_send
{
	//	索引值/地址ptr
	StockKey*		   m_lPosIndex;

	ShareRealTimeData  m_preData;
	
	Rpt_UserReportData m_sUserReportData;  // 人工报价系统使用

	//	构造函数
	CHSStockPosition_send()
	{
		m_lPosIndex = NULL;

		memset(&m_preData,0,sizeof(m_preData));

		memset(&m_sUserReportData,0,sizeof(m_sUserReportData));		
	}
	
	~CHSStockPosition_send()
	{
		if( m_lPosIndex != NULL )
		{
			delete m_lPosIndex;
			m_lPosIndex = NULL;
		}
	}

	int SaveData(ShareRealTimeData* pSendUDPDataItem,int nLen)
	{
		if( pSendUDPDataItem == NULL )
			return 0;

		memcpy(&m_preData,pSendUDPDataItem,min(sizeof(m_preData),nLen));

		return 1;
	}

	int CompareData(ShareRealTimeData* pSendUDPDataItem)
	{
		if( m_preData.m_nowData.m_lNewPrice == 0 )
			return 1;

		return memcmp(&m_preData,pSendUDPDataItem,sizeof(m_preData));
	}

	////	拷贝一个索引结构
	//BOOL Copy(CHSStockPosition_send* pRefPos)
	//{
	//	if( pRefPos == NULL )
	//		return FALSE;
	//	
	//	m_lPosIndex = pRefPos->m_lPosIndex;
	//	
	//	return TRUE;
	//}
};

//	服务器、接收端-股票位置索引
struct CHSStockPosition
{
	//	索引值/地址ptr
	long m_lPosIndex;
	
	//	构造函数
	CHSStockPosition()
	{
		m_lPosIndex = -1;
	}
	
	//	拷贝一个索引结构
	BOOL Copy(CHSStockPosition* pRefPos)
	{
		if( pRefPos == NULL )
			return FALSE;
		
		m_lPosIndex = pRefPos->m_lPosIndex;
		
		return TRUE;
	}
};

static int StrToInteger(LPCTSTR szKey)
{
	int number = 0;
	int nChar;
	while(*szKey)
	{
		if( *szKey >= '0' && *szKey <= '9' )
			nChar = *szKey;
		else
			nChar = (*szKey & ~(('a') - ('A'))) - ('A') + 10 + ('0');

		number = (number << 4);
		number += nChar - ('0');

		szKey++;
	}

	return number;
}

//	股票到指针的映射
//#define ARRAYSIZE 0xffffff
template<class STOCKPTR,int ARRAYSIZE = 0xffffff>	  //61.130.5.85
struct CYlsStockPos
{
public:		 // CArray
	CYlsStockPos()
	{
		m_mapPosition	 = NULL;
		m_nHashTableSize = 0;
	}

	virtual ~CYlsStockPos()
	{
		DeleteMap();
	}
	
protected:
	//	内建的映射
	long*			 m_mapPosition;
	//	Hash表的大小
	int				 m_nHashTableSize;
	
public:
	//	返回内建的映射
	long*  GetMapStock() 			    { return m_mapPosition; }
	//	返回映射的大小
	int    GetMapSize()								{ return m_nHashTableSize; }
		
	BOOL  InitMap(int nHashTableSize)
	{
		// empty
		DeleteMap();

		if( m_mapPosition == NULL && nHashTableSize != 0 )
		{
			m_nHashTableSize = ARRAYSIZE;//nHashTableSize;
			m_mapPosition = (long*)new char[sizeof(long)*m_nHashTableSize];
			memset(m_mapPosition,0,sizeof(long)*m_nHashTableSize);
		}

		return TRUE;
	}

	BOOL  AddToMap(StockUserInfo* pStock,STOCKPTR* pPosition)
	{
		if( pStock == NULL )
			return FALSE;
		return AddToMap( &pStock->m_ciStockCode,pPosition );
	}

	BOOL  AddToMap(CodeInfo* pStock,STOCKPTR* pPosition)
	{
		if( m_mapPosition == NULL || pStock == NULL )
			return FALSE;

		char strKey[9];		
		memset(strKey,0,sizeof(strKey));
		return AddToMap(YlsGetKey(strKey,pStock),pPosition);
	}

	BOOL  AddToMap(LPCTSTR strKey,STOCKPTR* pPosition)
	{
		if( m_mapPosition == NULL || strKey == NULL )
			return FALSE;

		int nCurPos = StrToInteger(strKey);

		if( nCurPos >= 0 && nCurPos < ARRAYSIZE )
		{
			m_mapPosition[nCurPos] = (long)pPosition;
			return TRUE;
		}

		return FALSE;
	}

	void  DeleteMap()
	{
		if( m_mapPosition == NULL )
		{
			return;
		}

		for(int i = 0; i < ARRAYSIZE; i++)
		{
			if( m_mapPosition[i] )
			{
				delete (STOCKPTR*)m_mapPosition[i];
				m_mapPosition[i] = NULL;
			}
		}
	}

	const STOCKPTR* GetStockByMap(StockUserInfo* pKey)
	{
		if( pKey == NULL )
			return NULL;

		char strKey[9];
		memset(strKey,0,sizeof(strKey));
		return GetStockByMap( YlsGetKey(strKey,&pKey->m_ciStockCode) );
	}

	const STOCKPTR* GetStockByMap(CodeInfo* pKey)
	{
		if( pKey == NULL )
			return NULL;

		char strKey[9];
		memset(strKey,0,sizeof(strKey));
		return GetStockByMap( YlsGetKey(strKey,pKey) );
	}

	const STOCKPTR* GetStockByMap(LPCTSTR key)
	{
		if( m_mapPosition == NULL || key == NULL ) 
			return NULL;

		
		int nCurPos = StrToInteger(key);

		if( nCurPos >= 0 && nCurPos < ARRAYSIZE )
		{
			return (STOCKPTR*)m_mapPosition[nCurPos];
		}

		return NULL;
	}
	
	BOOL IsValid() { return (m_mapPosition != NULL); }
};


//	股票到指针的映射
template<class POSITION_BASE>
struct CHSStockPosMap
{
public:
	CHSStockPosMap()
	{
		m_mapPosition	 = NULL;
		m_nHashTableSize = 0;
	}

	virtual ~CHSStockPosMap()
	{
		DeleteMap();
	}
	
protected:
	//	内建的映射
	CYlsMapStringToPtr* m_mapPosition;
	//	Hash表的大小
	int				 m_nHashTableSize;
	
public:
	//	返回内建的映射
	CYlsMapStringToPtr* GetMapStock() 			    { return m_mapPosition; }
	//	返回映射的大小
	int GetMapSize()								{ return m_nHashTableSize; }
		
	BOOL  InitMap(int nHashTableSize)
	{
		// empty
		DeleteMap();

		//
		if( m_mapPosition == NULL )
		{
			m_mapPosition = new CYlsMapStringToPtr;
		}
		m_nHashTableSize = nHashTableSize;
		m_mapPosition->InitHashTable(m_nHashTableSize);

		return TRUE;
	}

	BOOL  InitMap_Raw(int nHashTableSize)
	{
		if( m_mapPosition != NULL )
			return 1;

		// empty
		DeleteMap();

		//
		if( m_mapPosition == NULL )
		{
			m_mapPosition = new CYlsMapStringToPtr;
		}
		m_nHashTableSize = nHashTableSize;
		m_mapPosition->InitHashTable(m_nHashTableSize);

		return TRUE;
	}

	BOOL  AddToMap(StockUserInfo* pStock,POSITION_BASE* pPosition)
	{
		if( pStock == NULL )
			return FALSE;
		return AddToMap( &pStock->m_ciStockCode,pPosition );
	}

	BOOL  AddToMap(CodeInfo* pStock,POSITION_BASE* pPosition)
	{
		if( m_mapPosition == NULL || pStock == NULL )
			return FALSE;

		char strKey[9];
		memset(strKey,0,sizeof(strKey));
		return AddToMap(YlsGetKey(strKey,pStock),pPosition);
	}

	BOOL  AddToMap(LPCTSTR strKey,POSITION_BASE* pPosition)
	{
		if( m_mapPosition == NULL || strKey == NULL )
			return FALSE;

		void* pCurPosition;
		if( m_mapPosition->Lookup(strKey,pCurPosition) ) // 是否存在
		{
			//((POSITION_BASE*)pCurPosition)->m_lPosIndex = pPosition->m_lPosIndex;
			return FALSE;
		}
		m_mapPosition->SetAt( strKey,pPosition );

		return TRUE;
	}

	BOOL  DeleteFromMap(const char* lKey)
	{
		if( m_mapPosition == NULL )
			return FALSE;

		void* pCurPosition;
		if( m_mapPosition->Lookup(lKey,pCurPosition) ) // 是否存在
		{
			m_mapPosition->RemoveKey(lKey);
			delete (POSITION_BASE*)pCurPosition;
			return TRUE;
		}
		return FALSE;
	}

	void  DeleteMap()
	{
		if( m_mapPosition == NULL )
		{
			return;
		}

		POSITION pos = m_mapPosition->GetStartPosition();

		const char* lKey;
		void *pVal;
		while (pos != NULL)
		{
			m_mapPosition->GetNextAssoc (pos, lKey, pVal);
			if(pVal != NULL)
			{
				delete (POSITION_BASE*)pVal;
			}
		}

		m_mapPosition->RemoveAll();
		delete m_mapPosition;
		m_mapPosition = NULL;
	}

	const POSITION_BASE* GetStockByMap(StockUserInfo* pKey)
	{
		if( pKey == NULL )
			return NULL;

		char strKey[9];
		memset(strKey,0,sizeof(strKey));
		return GetStockByMap( YlsGetKey(strKey,&pKey->m_ciStockCode) );
	}

	const POSITION_BASE* GetStockByMap(CodeInfo* pKey)
	{
		if( pKey == NULL )
			return NULL;

		char strKey[9];
		memset(strKey,0,sizeof(strKey));
		return GetStockByMap( YlsGetKey(strKey,pKey) );
	}

	const POSITION_BASE* GetStockByMap(LPCTSTR key)
	{
		if( m_mapPosition == NULL || key == NULL ) 
			return NULL;

		void* pCurPostion;
		if( m_mapPosition->Lookup(key,pCurPostion) )
			return (POSITION_BASE*)pCurPostion;

		return NULL;
	}
	
	BOOL IsValid() { return (m_mapPosition != NULL); }
};

struct HsShareMemParam
{
	int  m_nStockCounts;					// 股票数
	int  m_nTickCounts;						// 分笔数
	int  m_nTrendCounts;					// 分时数

	HsShareMemParam()
	{
		memset(this,0,sizeof(HsShareMemParam));
	}
};


// 内存是否可用标志
#define HsShareStockCount_InitStart				0x00001	   // 共享内存初始化开始
#define HsShareStockCount_InitEnd				0x00002	   // 共享内存初始化完成


// 磁盘数据是否装入到内存标志
#define HsShareStockCount_Load					0x00004	   // 共享内存数据已经加载

// 内存是否启用标志
#define HsShareStockCount_Close					0x00020	   // 共享内存关闭

// 数据初始华标志
#define HsShareStockCount_DataInitStart			0x00008	   // 数据初始化开始
#define HsShareStockCount_DataInitEnd			0x00010	   // 数据初始化完成

// 补线时共享标志
#define HsShareStockCount_RefreshStart			0x00100	   // 正在更新数据加载-开始
#define HsShareStockCount_RefreshEnd			0x00200	   // 正在更新数据加载-结束

struct HsMarketShareParam
{
	unsigned int	m_nDate;	 // 更新日期
	int				m_nMarkInfo; // 标志信息,参见 HsShareStockCount_Start 等定义

	int				m_nSaveFlag;

	int				m_nResever[4];

	HsMarketShareParam()
	{
		memset(this,0,sizeof(HsMarketShareParam));
	}
};

struct HsShareStockCount
{
	int				m_nMarkInfo; // 标志信息,参见 HsShareStockCount_Start 等定义

	HsShareMemParam m_Memory_gp;
	HsShareMemParam m_Memory_qh;
	HsShareMemParam m_Memory_wh;
	HsShareMemParam m_Memory_wp;
	HsShareMemParam m_Memory_gg;
	HsShareMemParam m_Memory_hj;

	unsigned int    m_nDate;	 // 更新日期
	char*			m_pData;

	HsShareStockCount()
	{
		memset(this,0,sizeof(HsShareStockCount));
	}
};

// 股票总数共享name
#define HsShareMemManagerStockCounts "_StockCounts_"

// 行情变化标志
#define HQ_Change_Flag			0x01 // 行情变化
#define FB_Change_Flag			0x02 // 分笔变化
#define BQ_Change_Flag			0x04 // 经纪队列变化
#define BS_Change_Flag			0x08 // 买卖5~10档行情变化

#define Lelvel_Change_Flag		0x10 // level2逐笔变化
#define Lelvel_MM_Change_Flag	0x20 // level2买卖队列变化

// 独立变化标志
#define Lelvel_LJ_Change_Flag	0x1000 // level2累计变化
#define Lelvel_CD_Change_Flag	0x2000 // level2撤单变化

class HsShareMemManager
{
//protected:
	//char	m_cMemLoad;

public:
	HsShareMemManager()
	{
		memset(this,0,sizeof(HsShareMemManager));
	}

	~HsShareMemManager()
	{
		 FreeShare();
	}

	// 共享内存处理
public:
	
	//	证交所信息
	//	这其实是个short
	HSMarketDataType	m_cBourse; 

	CYlsMapStringToPtr* m_mapShareMemName;		// 共享内存文件对应

	HsShareMemParam		m_sParam;				// 参数

	char m_strNowBasePath[_MAX_PATH];		//	实时数据起始路径

	char m_name_StockCounts[_MAX_PATH];		// 参数share

	char m_name_param[_MAX_PATH];			// 本内存共享参数
	char m_name_mark[_MAX_PATH];			// 推送标志数据
	char m_name_real[_MAX_PATH];			// 实时数据
	char m_name_tick[_MAX_PATH];			// 分笔数据
	char m_name_bourseinfo[_MAX_PATH];		// 分类信息数据
	char m_name_trend[_MAX_PATH];			// 当日走势
	char m_name_stockinfo[_MAX_PATH];		// 代码信息
	char m_name_initinfo[_MAX_PATH];		// 初始化数据
	char m_name_other[_MAX_PATH];			// 其他数据

	CSharedMemory* m_Memory_stockCount;			// 参数share

	CSharedMemory* m_Memory_param;
	CSharedMemory* m_Memory_mark;			// 推送标志数据
	CSharedMemory* m_Memory_real;			// 实时数据
	CSharedMemory* m_Memory_tick;			// 分笔数据
	CSharedMemory* m_Memory_bourseinfo;		// 分类信息数据
	CSharedMemory* m_Memory_trend;			// 当日走势
	CSharedMemory* m_Memory_stockinfo;		// 代码信息
	CSharedMemory* m_Memory_initinfo;		// 初始化数据
	CSharedMemory* m_Memory_other;			// 其他数据

	HsShareStockCount* GetShareDataInfo()
	{
		if( m_Memory_stockCount != NULL )
			return (HsShareStockCount*)m_Memory_stockCount->GetData();

		return NULL;
	}

	int GetMark()
	{
		HsShareStockCount* pData = GetShareDataInfo();
		if( pData != NULL )
			return pData->m_nMarkInfo;

		return 0;
	}

	int SetMark(int nMarkInfo)
	{
		HsShareStockCount* pData = GetShareDataInfo();
		if( pData != NULL )
		{
			pData->m_nMarkInfo = nMarkInfo;
			return pData->m_nMarkInfo;
		}
		return 0;
	}

	int AddMark(int nMarkInfo)
	{
		HsShareStockCount* pData = GetShareDataInfo();
		if( pData != NULL )
		{
			pData->m_nMarkInfo |= nMarkInfo;
			return pData->m_nMarkInfo;
		}
		return 0;
	}

	int RemoveMark(int nMarkInfo)
	{
		HsShareStockCount* pData = GetShareDataInfo();
		if( pData != NULL )
		{
			pData->m_nMarkInfo &= (~nMarkInfo);
			return pData->m_nMarkInfo;
		}
		return 0;
	}

	int IsMark(int nMarkInfo)
	{
		HsShareStockCount* pData = GetShareDataInfo();
		if( pData != NULL )
			return (pData->m_nMarkInfo & nMarkInfo);

		return 0;
	}

	HsMarketShareParam* GetParam()
	{
		if( m_Memory_param )
			return (HsMarketShareParam*)m_Memory_param->GetData();

		return NULL;
	}

	unsigned int GetModifyDate()
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
			return pData->m_nDate;

		return 0;
	}

	unsigned int SetModifyDate(unsigned int lDate)
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
		{
			pData->m_nDate = lDate;
			return pData->m_nDate;
		}
		return 0;
	}

	int IsMemStyle(int nMarkInfo)
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
			return (pData->m_nMarkInfo & nMarkInfo);

		return 0;
	}

	int AddMemStyle(int nMarkInfo)
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
		{
			pData->m_nMarkInfo |= nMarkInfo;
			return pData->m_nMarkInfo;
		}

		return 0;
	}

	int RemoveMemStyle(int nMarkInfo)
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
		{
			pData->m_nMarkInfo &= (~nMarkInfo);
			return pData->m_nMarkInfo;
		}
		
		return 0;
	}

	int SetMemStyle(int nMarkInfo)
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
		{
			pData->m_nMarkInfo = nMarkInfo;
			return pData->m_nMarkInfo;
		}

		return 0;
	}

	int AddSaveFlag()
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
		{
			pData->m_nSaveFlag++;
			return pData->m_nSaveFlag;
		}

		return 0;
	}

	int SetSaveFlag(int nSaveFlag = 0)
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
		{
			pData->m_nSaveFlag = nSaveFlag;
			return pData->m_nSaveFlag;
		}

		return 0;
	}

	int IsSaveFlag()
	{
		HsMarketShareParam* pData = GetParam();
		if( pData )
		{
			return pData->m_nSaveFlag;
		}

		return 0;
	}

	void SetCount(HsShareStockCount* pHsShareStockCount)
	{
		if( pHsShareStockCount == NULL )
			return;

		if( MakeMarket(m_cBourse) == STOCK_MARKET )
			memcpy(&m_sParam,&pHsShareStockCount->m_Memory_gp,sizeof(m_sParam));
		else if( MakeMarket(m_cBourse) == HK_MARKET )
			memcpy(&m_sParam,&pHsShareStockCount->m_Memory_gg,sizeof(m_sParam));
		else if( MakeMarket(m_cBourse) == FUTURES_MARKET )
			memcpy(&m_sParam,&pHsShareStockCount->m_Memory_qh,sizeof(m_sParam));
		else if( MakeMarket(m_cBourse) == WP_MARKET )
			memcpy(&m_sParam,&pHsShareStockCount->m_Memory_wp,sizeof(m_sParam));
		else if( MakeMarket(m_cBourse) == FOREIGN_MARKET )
			memcpy(&m_sParam,&pHsShareStockCount->m_Memory_wh,sizeof(m_sParam));
		else if( MakeMarket(m_cBourse) == HJ_MARKET )
			memcpy(&m_sParam,&pHsShareStockCount->m_Memory_hj,sizeof(m_sParam));

		if( m_sParam.m_nStockCounts <= 0 )
			m_sParam.m_nStockCounts = 3000;			// 最大代码数据

		if( m_sParam.m_nTickCounts <= 0 )
			m_sParam.m_nTickCounts = 3;//300*1024*1024;	// 每个代码2千笔

		if( m_sParam.m_nTrendCounts <= 0 )
			m_sParam.m_nTrendCounts = 241;			// 分时周期241个点

	}

	static int Attatch(CSharedMemory* pMemory,const char* szName,int nSize,DWORD dw)
	{
		if( !pMemory->Init(szName,nSize,ERROR_ALREADY_EXISTS) )
		{		
			if( !pMemory->Init(szName,nSize,dw) )
			{
				return 0;
			}
		}

		return 1;
	}

	int DeleteShare(const char* strNowBasePath)
	{		
#ifdef HS_SUPPORT_UNIX
		//
		sprintf(m_name_StockCounts,"%s%s",strNowBasePath,HsShareMemManagerStockCounts);
		CSharedMemory::DeleteShare(m_name_StockCounts);

		// 本市场共享参数
		sprintf(m_name_param,"%s%s.%hx",strNowBasePath,"param",m_cBourse);
		CSharedMemory::DeleteShare(m_name_param);

		//
		sprintf(m_name_mark,"%s%s.%hx",strNowBasePath,"automark",m_cBourse);
		CSharedMemory::DeleteShare(m_name_mark);

		//
		sprintf(m_name_real,"%s%s.%hx",strNowBasePath,"real",m_cBourse);
		CSharedMemory::DeleteShare(m_name_real);

		sprintf(m_name_tick,"%s%s.%hx",strNowBasePath,"tick",m_cBourse);
		CSharedMemory::DeleteShare(m_name_tick);


		sprintf(m_name_bourseinfo,"%s%s.%hx",strNowBasePath,"bourseinfo",m_cBourse);
		CSharedMemory::DeleteShare(m_name_bourseinfo);

		sprintf(m_name_trend,"%s%s.%hx",strNowBasePath,"trend",m_cBourse);
		CSharedMemory::DeleteShare(m_name_trend);

		sprintf(m_name_stockinfo,"%s%s.%hx",strNowBasePath,"stockinfo",m_cBourse);
		CSharedMemory::DeleteShare(m_name_stockinfo);

		sprintf(m_name_initinfo,"%s%s.%hx",strNowBasePath,"initinfo",m_cBourse);
		CSharedMemory::DeleteShare(m_name_initinfo);

		sprintf(m_name_other,"%s%s.%hx",strNowBasePath,"other",m_cBourse);	
		CSharedMemory::DeleteShare(m_name_other);

		return 1;
#endif

		return 0;
	}

	int AllocShare(DWORD dw = ERROR_ALREADY_EXISTS)
	{		
		//
		sprintf(m_name_StockCounts,"%s%s",m_strNowBasePath,HsShareMemManagerStockCounts);
		m_Memory_stockCount = new CSharedMemory();			// 商品参数share
		if( !m_Memory_stockCount->Init(m_name_StockCounts,sizeof(HsShareStockCount),ERROR_ALREADY_EXISTS) )
		{
			delete m_Memory_stockCount;
			m_Memory_stockCount = NULL;
			FreeShare();
			return 0;
		}

		if( m_Memory_stockCount )
			SetCount((HsShareStockCount*)m_Memory_stockCount->GetData());

		// 本市场共享参数
		sprintf(m_name_param,"%s%s.%hx",m_strNowBasePath,"param",m_cBourse);
		m_Memory_param = new CSharedMemory();			
		if( !Attatch(m_Memory_param,m_name_param,sizeof(HsMarketShareParam),dw) )
		{			
			delete m_Memory_param;
			m_Memory_param = NULL;
			FreeShare();
			return 0;
		}

		//
		sprintf(m_name_mark,"%s%s.%hx",m_strNowBasePath,"automark",m_cBourse);
		m_Memory_mark = new CSharedMemory();			// 推送标志数据
		if( !Attatch(m_Memory_mark,m_name_mark,m_sParam.m_nStockCounts*sizeof(short),dw) )
		{			
			delete m_Memory_mark;
			m_Memory_mark = NULL;
			FreeShare();
			return 0;
		}

		//
		sprintf(m_name_real,"%s%s.%hx",m_strNowBasePath,"real",m_cBourse);
		m_Memory_real = new CSharedMemory();			// 实时数据
		if( !Attatch(m_Memory_real,m_name_real,m_sParam.m_nStockCounts*sizeof(ShareRealTimeData),dw) )
		{
			delete m_Memory_real;
			m_Memory_real = NULL;
			FreeShare();
			return 0;
		}

		sprintf(m_name_tick,"%s%s.%hx",m_strNowBasePath,"tick",m_cBourse);
		m_Memory_tick = new CSharedMemory();			// 分笔数据
		if( !Attatch(m_Memory_tick,m_name_tick,m_sParam.m_nStockCounts*sizeof(StockTrace)*m_sParam.m_nTickCounts,dw) )
		{
			delete m_Memory_tick;
			m_Memory_tick = NULL;
			FreeShare();
			return 0;
		}
		m_Memory_tick->SetTickType(1);


		sprintf(m_name_bourseinfo,"%s%s.%hx",m_strNowBasePath,"bourseinfo",m_cBourse);
		m_Memory_bourseinfo = new CSharedMemory();		// 分类信息数据
		if( !Attatch(m_Memory_bourseinfo,m_name_bourseinfo,sizeof(DiskBourseInfo),dw) )
		{
			delete m_Memory_bourseinfo; 
			m_Memory_bourseinfo = NULL;
			FreeShare();
			return 0;
		}

		sprintf(m_name_trend,"%s%s.%hx",m_strNowBasePath,"trend",m_cBourse);
		m_Memory_trend = new CSharedMemory();			// 当日走势
		if( !Attatch(m_Memory_trend,m_name_trend,m_sParam.m_nStockCounts*sizeof(StockHistoryData)*m_sParam.m_nTrendCounts,dw) )
		{
			delete m_Memory_trend;
			m_Memory_trend = NULL;
			FreeShare();
			return 0;
		}

		sprintf(m_name_stockinfo,"%s%s.%hx",m_strNowBasePath,"stockinfo",m_cBourse);
		m_Memory_stockinfo = new CSharedMemory();		// 代码信息
		if( !Attatch(m_Memory_stockinfo,m_name_stockinfo,m_sParam.m_nStockCounts*sizeof(StockInfoIn),dw) )
		{
			delete m_Memory_stockinfo;
			m_Memory_stockinfo = NULL;
			FreeShare();
			return 0;
		}

		sprintf(m_name_initinfo,"%s%s.%hx",m_strNowBasePath,"initinfo",m_cBourse);
		m_Memory_initinfo = new CSharedMemory();		// 初始化数据
		if( !Attatch(m_Memory_initinfo,m_name_initinfo,m_sParam.m_nStockCounts*sizeof(StockInfo),dw) )
		{
			delete m_Memory_initinfo;
			m_Memory_initinfo = NULL;
			FreeShare();
			return 0;
		}

		sprintf(m_name_other,"%s%s.%hx",m_strNowBasePath,"other",m_cBourse);	
		m_Memory_other = new CSharedMemory();			// 其他数据
		if( !Attatch(m_Memory_other,m_name_other,m_sParam.m_nStockCounts*sizeof(StockOtherData),dw) )
		{
			delete m_Memory_other;
			m_Memory_other = NULL;
			FreeShare();
			return 0;
		}

		return ( (m_Memory_param != NULL)		    &&
			(m_Memory_stockCount != NULL)			&&
			(m_Memory_mark != NULL)					&&
			(m_Memory_real != NULL)					&&		// 实时数据
			(m_Memory_tick != NULL)					&&		// 分笔数据
			(m_Memory_bourseinfo != NULL)			&&		// 分类信息数据
			(m_Memory_trend != NULL)				&&		// 当日走势
			(m_Memory_stockinfo != NULL)			&&		// 代码信息
			(m_Memory_initinfo != NULL)				&&		// 初始化数据
			(m_Memory_other != NULL) );						// 其他数据 );

		//return m_cMemLoad;
	}

	void FreeShare()
	{
		//m_cMemLoad = 0;

		_delObject(m_Memory_param);
		_delObject(m_Memory_stockCount);			
		_delObject(m_Memory_mark);			
		_delObject(m_Memory_real);			// 实时数据
		_delObject(m_Memory_tick);			// 分笔数据
		_delObject(m_Memory_bourseinfo);	// 分类信息数据
		_delObject(m_Memory_trend);			// 当日走势
		_delObject(m_Memory_stockinfo);		// 代码信息
		_delObject(m_Memory_initinfo);		// 初始化数据
		_delObject(m_Memory_other);			// 其他数据
	}

	virtual int IsHaveShareMemory()
	{
		return ( (m_Memory_param != NULL)		&&
			(m_Memory_stockCount != NULL)			&&
			(m_Memory_mark != NULL)					&&
			(m_Memory_real != NULL)					&&		// 实时数据
			(m_Memory_tick != NULL)					&&		// 分笔数据
			(m_Memory_bourseinfo != NULL)			&&		// 分类信息数据
			(m_Memory_trend != NULL)				&&		// 当日走势
			(m_Memory_stockinfo != NULL)			&&		// 代码信息
			(m_Memory_initinfo != NULL)				&&		// 初始化数据
			(m_Memory_other != NULL) );
		//return m_cMemLoad;
	}
};

// 共享内存数据保存
struct MemShareDataSave
{
	int m_nTicks;  // 分笔当前最大桶数
};


//
class HSServerDataPath : //public CHSStockPosMap<CHSStockPosition>, // CHSStockPosArray
						  public HsShareMemManager

{
public:
	//	构造函数
	HSServerDataPath(HSMarketDataType cBourse = 0);
	
	//	数据类型
	enum 
	{
		NowDataType,			//	实时数据类型
		DayDataType				//	日线等K线数据类型
	};			
	
	//	实时数据路径
	char m_SHFileNowName[_MAX_PATH];		//	now时时
	char m_SHFileTraName[_MAX_PATH];		//	分笔
	char m_SHFileHisName[_MAX_PATH];		//	分时走势
	char m_SHFileCodeInfo[_MAX_PATH];		//	代码数据
	char m_SHFileInfoName[_MAX_PATH];		//	browse info

	char m_SHFileMsgName[_MAX_PATH];		//	信息、个股资料？

	char m_strFileCodeList[_MAX_PATH];		// 代码表文件
	char m_strFileOtherData[_MAX_PATH];		// 其他数据文件 other
	
	//char m_SHFileCdpName[_MAX_PATH];		//	5日总手文件名

	char m_SHFilePYJCName[_MAX_PATH];		//	拼音简称文件名
	//char m_strNowBasePath[_MAX_PATH];		//	实时数据起始路径
	
	//	盘后数据路径
	char m_strFileTend [_MAX_PATH] ;		//	历史分钟线文件名

	char m_strFileMin[_MAX_PATH]   ;		//	5分钟K线文件名
	char m_strFileMin1[_MAX_PATH]   ;		//	1分钟线文件名
	char m_strFileMin15[_MAX_PATH]   ;		//	15分钟线文件名
	char m_strFileMin30[_MAX_PATH]   ;		//	30分钟线文件名
	char m_strFileMin60[_MAX_PATH]   ;		//	60分钟线文件名
	char m_strFileMin120[_MAX_PATH]   ;		//	120分钟线文件名

	char m_strFileDay[_MAX_PATH]   ;		//	日线文件名	
	char m_strFileWeek[_MAX_PATH]  ;		//	周线文件名
	char m_strFileMonth[_MAX_PATH] ;		//	月线文件名
	char m_strFileSeason[_MAX_PATH] ;		//	季线文件名
	char m_strFileYear[_MAX_PATH] ;			//	年线文件名

	char m_strFileCDP[_MAX_PATH]   ;		//	5日总手文件名
	
	char m_strHisFileTrace[_MAX_PATH]  ;	//	历史分笔数据
	char m_strHKQiQuan[_MAX_PATH]  ;	    //	港股期权数据
	
	char m_strETFFileDay[_MAX_PATH];        // etf路径
	char m_strBrokerFile[_MAX_PATH];        // 经纪队列路径

	char m_strOrderQueue[_MAX_PATH];        // level2 买卖队列路径
	char m_strConsolidated[_MAX_PATH];      // level2 累计
	char m_strCancellation[_MAX_PATH];      // level2 撤单
	char m_strLargeTick[_MAX_PATH];         // level2 tick


	char m_strLvl2OrderQueue[_MAX_PATH];        // level2 买卖队列
	char m_strLvl2Consolidated[_MAX_PATH];      // level2 累计-撤消买入/卖出委托累计数量最多的前10只股票
	char m_strLvl2Cancellation[_MAX_PATH];      // level2 撤单-单笔委托数量最大的10笔买/卖撤单

	char m_strInitFileCheck[_MAX_PATH]   ;	//	数据初始化检测文件
	char m_strInitFileCheckBegin[_MAX_PATH];//	数据初始化开始文件

	char m_strShareData[_MAX_PATH];			//	内存管理参数

	char m_strFillDataBegin[_MAX_PATH]   ;	//	补数据开始
	char m_strFillDataEnd[_MAX_PATH];		//	补数据结束

	char m_strPanHouFileTend[_MAX_PATH] ;	//	盘后历史分钟线文件名	
	char m_strPanHouFileMin[_MAX_PATH]  ;	//	盘后分钟线文件名
	char m_strPanHouFileDay[_MAX_PATH]  ;	//	盘后日线文件名
	
	char m_strDayBasePath[_MAX_PATH];		//	日线起始路径
	
	//
	char m_strInfoBasePath[_MAX_PATH];		//	资讯起始路径	

	//char m_strFileBroker[_MAX_PATH]   ;	//	经纪号对应股票
	
public:
	void	SetNowPath(const char* strBasePath,int nAllocType = ERROR_ALREADY_EXISTS);
	void	SetPanhouPath(const char* strBasePath,BOOL bOther = FALSE);
	void	SetZiXun(const char* strBasePath);

	
	// 内存共享----------
	int					AddShareMemName(int nAllocType = ERROR_ALREADY_EXISTS);
	CSharedMemory*	    GetMemShareName(const char* szFileName);
	void				SetMemToDiskFile();
	void				SaveFileData();


	//
	char* GetMarketName(char* strRet,int nLen);

	static void MakeValidPath(char* strBasePath);
	static void RemoveFile(const char* szFileName);
	static void CreateEmptyFile(const char* szFileName);

	BOOL GetPanHouPath(int nPeriod,char* strDayFile,char* strSuffix);  // added by Ben 20100926

	BOOL GetPanHouPath(int nPeriod,char* strDayFile,char* strSuffix,ReqDayData* pReqDayData);


// 内存共享数据读写
public:
	MemShareDataSave m_sMemShareDataSave;
	int  WriteShareData(MemShareDataSave& mem);
	int  ReadShareData(int nDefault);
	void RemoveShareData();

public:
	// 是否有补线数据过来
	int		IsHaveBeginFillData(int nMask = 0);
	int		IsHaveEndFillData(int nMask = 0);

};

struct HSServerDataPath_Send : public CHSStockPosMap<CHSStockPosition_send> // CHSStockPosArray
{
	HSMarketDataType m_cBourse;

	//	构造函数
	HSServerDataPath_Send(HSMarketDataType cBourse = 0)
	{
		m_cBourse = cBourse;
	}
};

class CHSFilePath
{
public:

	//enum FileType
	//{
	//	BlockUserStock,		// 板块、自选股
	//	Setting,			// 设置...
	//	FinancialData,
	//	ClientFileUpdate,	// 客户端文件升级
	//	UserManagerDBF,		// 用户管理
	//	UserConfig,			// 用户对应的配置文件
	//	sysInfoData,		// 系统运行状态文件
	//	AcceptFilePath,		// 收到上传的文件
	//};

	enum FileType
	{
		SaveInit = 20,		// 初始化数据(接收端)
		RunLog,				// 运行日志

		CodeFile,			// 代码文件(发送端)
		MarketFile,			// 市场对应配置文件(发送端)
		ZX_Setting,			// 资讯设置路径(发送端)
		ZX_Setting_File,	// 资讯配置文件(发送端)
		
		GG_CurDateData,     // 港股当日数据
		GG_StockUnion,      // 港股各股关联数据
		GG_StockList,		// 港股计算指数成份股目录
		GP_StockList,		// 股票计算指数成份股目录
		GP_IndexDataFile,	// 股票计算指数文件

		GG_CurDateAcceptData,     // 当日实时数据目录
		BackupData,				  // 备份数据目录
		Dfx_WGT_Path,		      // dfx除权路径
		RunLog_Temp,			  // 临时目录
		UserReportData,			  // 人工报价数据保存目录
		MappingPath,			  // 网络文件同步设置路径
		SendShare_Setting,		  // 发送共享行情库目录
		SrvTotalPath,			  // 临时统计目录
		DBF_Setting,			  // dbf设置
		LanguagePath,			  // 翻译文件对照表(服务器端)
		LogDataPath,			  // 日志文件路径
	};
	
	static char* GetPath(char* strPath,char cType,HSMarketDataType nMarket = 0,char* szFileName = NULL);
};


extern	const char* YlsGetCurrentExeBasePath();
extern	BOOL		CreatPath(const char* strBasePath,BOOL bList = TRUE);
extern	long		GetSizeByMask(long lMask);

extern int			YlsGetFileMarkInfo(TextMarkData* pMarkData,const char* strFileName);

#endif
