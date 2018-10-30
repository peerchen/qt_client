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



#if !defined(_CServerMarketInfo_h_)
#define _CServerMarketInfo_h_

#include "stdafx.h"
#include "outsharefile.h"


#include "serverstructex.h"

#include "ylsfile.h"
#include "ylsini.h"



//#include "ylsdadan.h"

//#include "hsserverdatapath.h"
//#include <sys\stat.h>

//#ifndef HS_SUPPORT_UNIX
class CYlsReadHqData;
//#endif

struct FileParam
{
	CYlsFile* m_pFile;

	FileParam()
	{
		m_pFile = NULL;
	}
	~FileParam()
	{
		Free();
	}

	BOOL IsValid() 
	{ 
		if( this == NULL )
			return FALSE;

		return ( m_pFile && m_pFile->IsValid() );//(m_pFile && m_pFile->m_hFile != INVALID_HANDLE_VALUE); 
	}
	
	void Empty() 
	{
		m_pFile = NULL;		
	}

	void Free()
	{
		CYlsFile* fp = m_pFile;
		m_pFile = NULL;

		if( fp != NULL )
		{
			fp->Close();
			delete fp;
		}
	}
};

class CServerMarketInfo;
struct CMarketGroup
{
	CYlsArray<CServerMarketInfo*,CServerMarketInfo*> m_ay;

	void Empty()
	{
		m_ay.RemoveAll();
	}
};

// 内存分笔数据
#define MenTickData_default 100
struct MenTickData
{
	int		  m_nCount;
	StockTick m_sStick[MenTickData_default];   // 最近100条

	MenTickData()
	{
		m_nCount = 0;
	}
};

// 日线内存
struct DayDataBuffer
{
	CHqDataBuffer m_sBuffer;

	int			  m_nLength;  // 文件实际数据长度
	char		  m_strDayFile[256];

	DayDataBuffer()
	{
		memset(this,0,sizeof(DayDataBuffer));
	}
};

// 拼音简称
struct PYJCItem
{
	char m_szPYJC[5];
	PYJCItem()
	{
		memset(this,0,sizeof(PYJCItem));
	}
};

struct MemStockDay
{
	DayDataBuffer* m_sBuffer;
	DayDataBuffer* m_sMinBuffer;
	DayDataBuffer* m_s5MinBuffer;

	int GetLength(char* strDayFile,int nPeriod = PERIOD_TYPE_DAY);

	int Read(void* pData,int nCount,int nSeek,int nDays,int nPeriod = PERIOD_TYPE_DAY);

	MemStockDay()
	{
		memset(this,0,sizeof(MemStockDay));
	}
	~MemStockDay()
	{
		_delObject(m_sBuffer);
		_delObject(m_sMinBuffer);
		_delObject(m_s5MinBuffer);
	}
};

struct LanguageConvertInfo
{
	char	m_strCode[64];				 // 实际代码,必须和接收行情对应
	char	m_strName[16];				 // 显示名称
	char	m_strEnglishName[16];		 // 英文名称

	LanguageConvertInfo()
	{
		memset(this,0,sizeof(LanguageConvertInfo));
	}
};

//
class CServerMarketInfo : public HSServerDataPath,
						  public /*CYlsStockPos*/CHSStockPosMap<CHSStockPosition>
{
public:
	CServerMarketInfo(HSMarketDataType cBourse = 0);
	virtual ~CServerMarketInfo(void);

public:
	struct InitingData
	{
		CServerMarketInfo* m_pCServerMarketInfo;
		InitingData(CServerMarketInfo* pCServerMarketInfo = NULL)
		{
			m_pCServerMarketInfo = pCServerMarketInfo;
			Begin();
		}

		~InitingData()
		{
			if( m_pCServerMarketInfo == NULL )
				return;
			End();
		}

		void Begin()
		{
			if( m_pCServerMarketInfo != NULL )
				m_pCServerMarketInfo->m_bInitDataEnd = FALSE;
		}

		void End()
		{
			if( m_pCServerMarketInfo != NULL )
				m_pCServerMarketInfo->m_bInitDataEnd = TRUE;
		}
	};

public:
	int m_nSHCode;			// 当前市场代码总数	

	//int  m_nNowTime;		// 当前时间

	BOOL m_bInitDataEnd;    // 主机是否在初始化数据
	BOOL m_bStockInfoFlag;  // 是否重新向客户端发初始化数据

	BOOL m_bPartStockInfoFlag; // 是否重新向客户端发部分初始化数据

	BOOL m_bCodeValidate;	   // 代码读取是否有效

	//BOOL m_bInitLoadFailed;    // 初始化装入失败

public:
	//static CMap<long,long,CServerMarketInfo*,CServerMarketInfo*> g_mapMarket;
	static CYlsMapWordToPtr g_mapMarket;
	
//#ifdef Support_DFX
	
//#endif
public:

	//long CalculateCloseDate(long lDate); // added by Ben 20100622 计算跨日交易品种的收盘日期

public:
	static int FindIndexByCode(const char* pCode,CYlsArray<StockInitInfo*,StockInitInfo*>& ay,HSMarketDataType cCodeType = 0);	// 在全部里面查找

	static CServerMarketInfo* GetMarketByID(UINT nMarket,CServerMarketInfo*& pServerMarketInfo);
	static int  IsStockInfoFlag(CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay);
	static BOOL IsInitDataEnd();
	static BOOL IsInitDataEnd(int nBourse);
	static BOOL IsInitDataEnd(AskData* pAsk);

	static int  GetMarketCount(int cBourse,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay);

	static BOOL InitDataAll();

	static int  ReadNowAll(int& nMarket,
		int& nIsChange,
		CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
		CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
		CYlsMutex* pYlsMutex);	

	static int  ReadNowAll_Other(int& nMarket,
		CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
		CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,
		CYlsMutex* pYlsMutex);	

	static BOOL AddMarket(int nBourse,CServerMarketInfo* pCServerMarketInfo);

	static void FreeAllMarket();

	static int  GetMarketCount() { return g_mapMarket.GetCount(); }

public:
	void Default();
	void End();

	void FreeAll();

	int  GetCurTime(long lTime);
	int  GetTime();

public:
	static CYlsFile*  GetFile(const char* strFileName,UINT nOpenMode,CServerMarketInfo* pCServerMarketInfo = NULL);

	static BOOL		  MyReadFile( const char* szFileName,CHqDataBuffer& buffer,
		int nStructSize = -1,
		FileParam* pFile = NULL,
		int nNeedLength = 0,
		CServerMarketInfo* pCServerMarketInfo = NULL,
		int nPos = 0);

	static BOOL		  MyWriteFile( const char* szFileName,void* pData,int nLen);

public:
	virtual BOOL   ReadLonInfoFromFile(int& nNeedInit,BOOL bInit = FALSE,CServerMarketInfo* pCServerMarketInfo = NULL);
	virtual BOOL   InitData(CYlsMutex* pYlsMutex = NULL,int* pError = NULL);
	virtual int    ReadNow(int& nMarket,int& nIsChange,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex);
	virtual int	   ReadNow_Other(int& nMarket,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex);


public:
	void ReadTick(int nInit = 0);

public:
	// 添加到查找列表
	BOOL AddKeyToMap();

	void DispHQTest();

public:
	virtual void Init();

	int IsHaveShareMemory();

public:
	//CYlsDaDan m_ylsdadan;

	// 新的数据
protected:
	DiskBourseInfo  m_biSHInfo; // 市场信息位置信息

	//CHqDataBuffer m_TempBrowseBufferDate; // 比较数据，是否需要初始化

	CHqDataBuffer m_TempBrowseBuffer;
	FileParam	  m_pBrowseFile;

	// 时时数据 指向 ShareRealTimeData
	CHqDataBuffer m_NowBuffer;
	CHqDataBuffer m_OldNowBuffer;
	FileParam	  m_pNowFile;

	CHqDataBuffer m_TempNowBuffer;

	// 代码信息数据 指向 StockInfoIn
	CHqDataBuffer m_CodeBuffer;
	CHqDataBuffer m_OldCodeBuffer;
	FileParam	  m_pCodeFile;

	CHqDataBuffer m_TempCodeBuffer;

	// 其他时时数据 指向 StockOtherData
	CHqDataBuffer m_StockOtherDataBuffer;
	CHqDataBuffer m_OldStockOtherDataBuffer;
	FileParam	  m_pStockOtherDataFile;

	CHqDataBuffer m_TempStockOtherDataBuffer;

	// 数据是否修改标志 指向 short
	CHqDataBuffer m_pNowChangeFlagBuffer;
	long		  m_nSigleFlag;			// 变化标志

	// 代码表数据  指向 StockInitInfo
	CHqDataBuffer m_pCodeListBuffer;
	CHqDataBuffer m_pOldCodeListBuffer;
	FileParam	  m_pCodeListFile;

	CHqDataBuffer m_pEnglishCodeListBuffer;  // 英文版

	// 拼音简称 指向 PYJCItem
	CHqDataBuffer m_pPYJCBuffer;
	
	// 一分钟数据  指向 StockHistoryData
	CHqDataBuffer m_StockHistoryDataBuffer;
	FileParam	  m_pStockHistoryDataFile;
	CHqDataBuffer m_TempStockHistoryDataBuffer;

	// 最近分笔数据  指向 MenTickData
	CHqDataBuffer m_TickDataBuffer;
	FileParam	  m_pTickDataFile;

	// level2 累计  指向 LevelConsolidatedOrderCancellationRankingDisk
	CHqDataBuffer m_pLeiJiBuffer;
	CHqDataBuffer m_pOldLeiJiBuffer;
	FileParam	  m_pLeiJiFile;
	CHqDataBuffer m_TempLeiJiBuffer;

	// level2 撤单  指向 LevelSingleOrderCancellationRankingDisk
	CHqDataBuffer m_pCheDanBuffer;
	CHqDataBuffer m_pOldCheDanBuffer;
	FileParam	  m_pCheDanFile;
	CHqDataBuffer m_TempCheDanBuffer;

	// level2 买卖队列数据  指向 LevelOrderQueueDisk
	CHqDataBuffer m_pQueueBuffer;
	CHqDataBuffer m_pOldQueueBuffer;
	FileParam	  m_pQueueFile;
	CHqDataBuffer m_TempQueueBuffer;

	//
	unsigned long	  m_lChangeCRC;
	CYlsFile*		  m_pChangedFile;

public:
	DiskBourseInfo*    GetInfo(UINT* pLen = NULL);					// 市场信息位置信息
	ShareRealTimeData* GetShareRealTimeData(UINT* pLen = NULL);		// 实时数据
	StockOtherData*	   GetStockOtherData(UINT* pLen = NULL);		// 其他数据
	StockInitInfo*     GetStockInitInfo(UINT* pLen = NULL);			// 初始化数据
	StockInfoIn*	   GetStockInfoIn(UINT* pLen = NULL);			// 代码信息数据
	short*			   GetNowChangeFlagSH();						// 变化标志

	LevelConsolidatedOrderCancellationRankingDisk*	   GetLeiJiData(UINT* pLen = NULL);		// level2 累计
	LevelSingleOrderCancellationRankingDisk*		   GetCheDanData(UINT* pLen = NULL);	// level2 撤单

	LevelOrderQueueDisk* GetQueueData(UINT* pLen = NULL);	// level2 买卖队列数据

	StockHistoryData*  GetStockHistoryData(int nPos,UINT* pLen = NULL);

	int				   GetMenTickData(int nPos,StockTick* pNextTrace,int nCount);

	int				   CalcGetStockCount();

	PYJCItem*		   GetPYJC();

	unsigned long	   GetChangeCRC();

	int	IsSigleFlag(long nSigleFlag)  { return (m_nSigleFlag & nSigleFlag); }


	// 语言翻译...
protected:
	CYlsMapStringToPtr m_mapCodeLanguage;
	char			   m_szLanguagePath[260];

protected:
	void FreeLanguage(CYlsMapStringToPtr& mapCodeLanguage);

	int	 GetCFgFileData(const char* strFileName,CYlsMapStringToPtr& mapCodeFilter);
	void ConvertEnglish(StockInitInfo* pSrcStock,StockInitInfo* pDesStock,CYlsIni& YlsIni);


	//
public:
	int GetNowCount()	{ return m_NowBuffer.GetCount(sizeof(RealData)); }
	int GetStockCount()	{ return m_pCodeListBuffer.GetCount(sizeof(StockInitInfo)); }

	int GetCount_Dfx(int nPos);

public:
	CYlsMapStringToPtr m_mapMemStockDay;

	MemStockDay* GetMemStockDay(CodeInfo* pCode,ReqDayData* pReqDayData/*int nPeriod = PERIOD_TYPE_DAY*/);
	void		 FreeMemStockDay();

	void		 LoadPanHouData(char* pRefData,int nCodeCount);

	void		 LoadStockDay(const char* szPath,CodeInfo* pCode,MemStockDay*& pMemStockDay,int nPeriod = PERIOD_TYPE_DAY);

	struct LoadPanHouParam
	{
		CServerMarketInfo* m_pThis;
		int				   m_nStopThread;
	};

	static ThreadReturn LoadPanHou(ThreadParam pParameter);

public:
	// 得到当前市场数据
	BOOL GetInitData(CHqDataBuffer& buffer,AskData* pAsk,int nLen,CYlsReadHqData* pThis,long lMask = 0);

	BOOL GetInitDataChinese(CHqDataBuffer& buffer,AskData* pAsk,int nLen,long lMask = 0);
	BOOL GetInitDataEnglish(CHqDataBuffer& buffer,AskData* pAsk,int nLen,long lMask = 0);

	// 当前市场初始化是否改变
	BOOL IsChangeInitData(ServerCompare* pData);

#ifndef HS_SUPPORT_UNIX
	//friend CYlsReadHqData;
#endif

protected:
	CHqDataBuffer	   m_StockCdpDataBuffer;
	CYlsMapStringToPtr m_mapCDPData;

public:
	BOOL	  AddToCDP(CodeInfo* pCode,StockCdp* psCdp);
	StockCdp* GetCDP(LPCTSTR key);
	StockCdp* GetCDP(CodeInfo* pCode);

	void	  LoadCDP();

	// 添加五日总量数据
	void Add5DayVol(char* pRefData,int nCodeCount);

	BOOL IsOpenTime();


	BOOL TestData();

	BOOL CheckNewData(int nInitOK = 0);

	BOOL CheckBeginData();

protected:
	CYlsTime	  m_tmStatusLog;
	void		  WriteFailed(LogSystem& pLogStatus,const char* szData);

public:		
	static CYlsTime	  m_lOldTime;
	static CYlsTime	  m_curTime;

	// dfx1.5支持
public:
	static unsigned int m_uCodeListCRC;
	static CServerMarketInfo* m_sh;
	static CServerMarketInfo* m_sz;

	static CHqDataBuffer m_InitCodeList;	// 代码表 for 1.5

#ifdef Support_JiaoHang_AutoEvery
	static CServerMarketInfo* m_WH_BASE_RATE;
	static CServerMarketInfo* m_WH_ACROSS_RATE;
	static AskData* GetWhEveryData(CHqDataBuffer& buffer);
#endif

	

public:
	BOOL GetLonInfo_Dfx(CHqDataBuffer& buffer,int nComp = 1);

	static char* GetCodeList_Dfx(CHqDataBuffer& buffer,int nPack = 1);

	void CalcCRC(BOOL bForce = FALSE);

public:
	static CYlsMapWordToPtr m_mapGroup;

	static void			EmptyGroup();
	static void			AddGroup(int nBourse,CServerMarketInfo* pCServerMarketInfo);

	static StockInfoIn* FindIndexByGroup(const CodeInfo * code,CServerMarketInfo*& pCServerMarketInfo);

public:
	int	m_nForceRefreshData; // 强制刷新数据
	int m_nCheckTimes;       // 监测共享内存次数

protected:
	void LoadPYJC(StockInitInfo* pStockInitInfo,int nCodeCount);
};

// 
class CStockServerMarketInfo : public CServerMarketInfo
{
public:
	CStockServerMarketInfo(HSMarketDataType cBourse = 0);
	virtual ~CStockServerMarketInfo(void);

public:
	virtual BOOL InitData(CYlsMutex* pYlsMutex = NULL,int* pError = NULL);
	virtual int  ReadNow(int& nMarket,int& nIsChange,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex);
	virtual int	 ReadNow_Other(int& nMarket,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex);
	virtual BOOL ReadLonInfoFromFile(int& nNeedInit,BOOL bInit = FALSE,CServerMarketInfo* pCServerMarketInfo = NULL);

	int NeedInit(CYlsMutex* pYlsMutex,long lTime = 10000);

	int CheckLevel2(int& nMarket,int& nIsChange,CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex);
};

#endif
