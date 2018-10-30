
#ifndef _marketinfomanager_send_h
#define _marketinfomanager_send_h

#include "ylsini.h"
#include "marketinfomanager.h"
#include "ylsmapptrtoptr.h"


// �����
#define LastError_Inited					1 	// �Ѿ���ʼ��
#define LastError_NotInitFileName			2 	// û�г�ʼ���ļ�����
#define LastError_InitOverTimes				3 	// ��ʼ����������� 
#define LastError_InitFailed				4 	// ��ʼ��ʧ��
#define LastError_ReadCodeEmpty				5 	// ��ȡ�����Ϊ��
#define LastError_CfgFormatError			6 	// ������ʽ����
#define LastError_initErrorReceived			7 	// ��ʼ����û�з���
#define LastError_initErrorReceived2		8 	// ��ʼ����û�з���2
#define LastError_NotInitTime				9 	// ���ǳ�ʼ��ʱ��
#define LastError_ForceInit					10	// ǿ�Ƴ�ʼ��

class  CMainFrameSend;
struct MarketInfo_send;


typedef DWORD (WINAPI* YlsUpdateDataProc) (LPVOID pParameter);

typedef BOOL (*YlsInitDataProc)(CZMRequest*,BOOL,MarketInfo_send*,CMainFrameSend*);

#define MarketInfo_Date "�г���ʼ������"
#define MarketInfo_Date_detail "�г���ʼ����ϸʱ��"

struct StockTypeInfo
{
	StockType			m_stType;

	CHqDataBuffer		m_strCodeScope;
	CHqDataBuffer		m_strNotCode;  // �������Ĵ���

	CHqDataBuffer		m_strName;	

	BOOL				m_bInit;  // ��ǰ�����Ƿ��ʼ��

	short				m_lSendUnit;

	short				m_lClientDecimal; // �ͻ���С��λ

	short				m_nUnionClass; // �������

	StockTypeInfo()
	{
		m_bInit = 0;
		m_lSendUnit = 1;
		m_lClientDecimal = 0;
		m_nUnionClass = 0;
	}
};

class CMainFrame;

struct UpdateDataProcParam
{
	int					m_nID;
	YlsUpdateDataProc   m_pYlsUpdateDataProc;

	UpdateDataProcParam()
	{
		memset(this,0,sizeof(UpdateDataProcParam));
	}
};

struct ThreadStartParam
{
	CMainFrame*			 m_pMainWin;
	UpdateDataProcParam* m_pParam;
	int					 m_nStopFlag;

	ThreadStartParam()
	{
		memset(this,0,sizeof(ThreadStartParam));
	}

	int  IsExit() { return (m_nStopFlag == 1); }
};


#ifndef HS_SUPPORT_UNIX

struct LevelValue_map
{
	CStringArray m_ay;
};

// �ֽ�
class CLevelTwoAnalysis_Map
{
protected:
	CMapWordToOb m_map;

public:
	CLevelTwoAnalysis_Map()
	{
	}

	~CLevelTwoAnalysis_Map()
	{
		Free();
	}

	void Free()
	{
		WORD key;
		LevelValue_map* value;
		POSITION  pos;
		for( pos = m_map.GetStartPosition(); pos != NULL; )
		{
			m_map.GetNextAssoc( pos, key, (CObject*&)value );
			if( value )
			{
				delete value;
			}
		}

		m_map.RemoveAll();
	}

	static int IsGroup(int nKey)
	{
		return ( (nKey == 454) ||
			(nKey == 10068) ||
			(nKey == 10069) ||
			(nKey == 10045) ||
			(nKey == 10051) ||
			(nKey == 10063) ||
			(nKey == 73) );
	}

	int AnalyzeStr(const char* strResource,const char* strDelimit,CStringArray& ayRet)
	{
		ayRet.RemoveAll();

		CString strCur;
		strCur.Format("%s",strResource);
		CString tmp;
		char* token = strtok( (char*)LPCSTR(strCur), strDelimit);
		while(token != NULL)
		{
			tmp.Format("%s",token);
			ayRet.Add(tmp);
			token = strtok( NULL, strDelimit);
		}
		return ayRet.GetSize();
	}

	int AddToMap(const char* strCur)
	{		
		CStringArray ay;
		AnalyzeStr(strCur,"=",ay);

		if( ay.GetSize() < 2 )
			return 0;

		LevelValue_map* pValue;
		WORD nKey = atol(ay.GetAt(0));

		if( !m_map.Lookup(nKey,(CObject*&)pValue) )
		{
			pValue = new LevelValue_map;
			m_map.SetAt(nKey,(CObject*)pValue);
		}

		pValue->m_ay.Add(ay.GetAt(1));

		return 0;
	}

	int Analysis(const char* pData,int nLen)
	{
		if( pData == NULL || 
			nLen <= 0 )
			return 0;

		CStringArray ay;
		int nRet = AnalyzeStr(CString(pData,nLen),
			Level2_Delimit,ay);
		for( int i = 0; i < nRet; i++ )
		{
			AddToMap(ay.GetAt(i));
		}

		return m_map.GetSize();
	}

	CString GetCode(int nPos = 0)
	{
		CString str = GetValue(48,nPos);		
		str.MakeUpper();
		return str;
	}

	CString GetValue(WORD nKey,int nPos = 0)
	{
		LevelValue_map* value;
		if( m_map.Lookup(nKey,(CObject*&)value) )
		{
			if( nPos >= 0 && nPos < value->m_ay.GetSize() )
			{
				CString str = value->m_ay.GetAt(nPos);
				str.Trim();
				return str;
			}
		}

		return "";
	}

	float GetValueFloat(WORD nKey,int nPos = 0)
	{
		CString str = GetValue(nKey,nPos);
		return atof(str);
	}

	long GetValueTime(WORD nKey,int nPos = 0)
	{
		CString str = GetValue(nKey,nPos);

		if( str.GetLength() <= 0 )
			return 0;

		int	hour = 0;
		int	minute = 0;
		int	second = 0;
		//char str[21];

		//str[20] = 0;
		//strncpy(str, str, 20);
		int nRet = sscanf(str, "%d:%d:%d", &hour, &minute, &second);
		if( nRet < 3 )
			return 0;

		return (hour * 10000 + minute * 100 + second);
	}

	unsigned long GetValueInt(WORD nKey,
		int nPriceUnit = 1000,
		int nPos = 0)
	{
		CString str = GetValue(nKey,nPos);

		if( nPriceUnit > 0 )
		{
			return GetLongValue((const char*)str,str.GetLength(),nPriceUnit);
		}

		return atol(str);
	}

	long GetValueDate(WORD nKey,int nPos = 0)
	{
		CString str = GetValue(nKey,nPos);
		return atol(str);
	}

	char GetValueChar(WORD nKey,int nPos = 0)
	{
		CString str = GetValue(nKey,nPos);
		if( str.GetLength() > 0 )
			return str[0];

		return 0;
	}
};

#endif


struct MarketInfo_send : public HSServerDataPath_Send//CYlsStockPosMap
{
	char				m_strName[_MAX_PATH];

	char				m_strDbfName[_MAX_PATH];       // .dbf��.code
	char				m_strStaticFile[_MAX_PATH];    // ��̬�����ļ�

	char				m_strUserDbf[_MAX_PATH];       // etf �����ļ�·��
	char				m_strSanBanDbfName[_MAX_PATH]; // ����dbf
	char				m_strSjsxxnName[_MAX_PATH];	   // �����Ϣdbf
	char				m_strCodetoDisp[_MAX_PATH];    // ʵ�ʴ��뵽��ʾ����

	int					m_nID;
	YlsUpdateDataProc   m_pYlsUpdateDataProc;
	YlsUpdateDataProc   m_pYlsUpdateDataProcWH;
	YlsUpdateDataProc   m_pYlsUpdateDataProcQH;

	YlsInitDataProc		m_pYlsInitDataProc; // ���ݳ�ʼ��

	StockTypeInfo*		m_stiStock;			// ���ͷ���

	short				m_nStockTotal;      // ��Ʊ����

	short				m_nTypeTotal;		// ��������

	BOOL				m_bInit;			// �Ƿ��ʼ��
	BOOL				m_bReceived;        // �Ƿ񷵻�
	int					m_nMaxTime;			// �Ƿ��ʼ��������ʾ����
	int					m_nWaitTime;        // ��ʼ�����ݷ�������Ҫ�ȴ���ʱ��

	BOOL				m_bReInit;        // �Ƿ񷵻�


	BOOL				m_bNext;

	int					m_nCount;
	int					m_nDelay;

	// YLink�ڻ�
	BOOL				m_bUsedUDP;  // �Ƿ�ʹ��udp
	int					m_nUDPPort;

	char				m_cAdd;		 // �Ƿ�װ��

public:
	// �Ƿ���UDP��ʼ����������ݳ�ʼ��
	YlsInitDataProc		m_pUDPInitDataProc;    // ���ݳ�ʼ��

	CYlsIni				m_sYlsIni;

	CYlsIni				m_sCurYlsIni; // ��ǰ���������ļ�

	CYlsMapStringToPtr  m_mapCodetoDisp;    // ������ձ�,ʵ�ʴ���=��ʾ����

public:
	BOOL InitData(CZMRequest* pRequest,BOOL bSend,CMainFrameSend* pMain);

	// ��ȡ
	void  ReadCodetoDisp();

	// ʵ�ʴ���=��ʾ����,ȱʡ����
	void  WriteDefaultCodetoDisp();


	long  CalculateCloseDate(long lDate, long lTime); // added by Ben 20100624
protected:
	CYlsArray<ThreadStartParam*,ThreadStartParam*> m_ayThreadParam;
public:
	void StopAllThreadParam();
	void RemoveAllThreadParam();
	void AddThreadParam(ThreadStartParam* pParam);

public:
	CYlsMapStringToPtr  m_mapStatic;  // ��̬�ļ�����map
	int m_nWriteToBufferCount;		  // ��ǰд������

	void WriteStatic();
	void ReadStatic();

public:
	ZMInitialData* m_pZMInitialData; // ��ǰ��ʼ������ptr
	FileNowData*   m_pFileNowData;
	int			   m_nCurCount;

public:
	//CMapStringToString m_mapCode; // �ڻ�����ӳ��
	CYlsMapStringToPtr m_mapCode;   // �ڻ�����ӳ��
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> m_ay;      // �����ִ�����

public:
	//CYlsMutex		   m_pUserReportMutex; //
	CYlsMapStringToPtr m_mapUserReportData; // �˹���������

	void FreeUserReportData();
	
public:
	//
	BOOL InitToMap(int nCount);
	BOOL AddKey(StockKey* pKey);
	BOOL IsInclude(const char* strCode);

public:
	static CYlsMapWordToPtr g_mapMarketSend;

public:
	static MarketInfo_send* GetMarketByID(UINT nMarket);

public:
	void BulidStockInfo(CMainFrameSend* pMain);
	void ChangeCFGFile();

	// �õ��������ƶ�Ӧ�Ķ�
	const char* GetCodeToNameSection()
	{
		if( MakeMarket(m_cBourse) == FUTURES_MARKET )
			return "�ڻ�";
		else if( MakeMarket(m_cBourse) == FOREIGN_MARKET )
			return "���";

		return "����";
	}

	const char* GetName();

protected:
	CYlsArray<UpdateDataProcParam*,UpdateDataProcParam*> m_ayThread;

public:
	MarketInfo_send(int nTypeTotal = SC_MAX)
	{
		m_nTypeTotal = nTypeTotal;
		m_stiStock = new StockTypeInfo[m_nTypeTotal];

		m_nStockTotal = 0;           // ��Ʊ����

		m_bInit = FALSE;			 // �Ƿ��ʼ��
		m_bReceived = FALSE;         // �Ƿ񷵻�
		m_nMaxTime = 0;
		m_nWaitTime = 0;

		m_bReInit = FALSE;

		m_bNext = FALSE;

		m_nCount = 0;
		m_nDelay = 1000;

		m_pZMInitialData = NULL;
		m_pFileNowData   = NULL;
		m_nCurCount		 = 0;

		m_bUsedUDP = 0;
		m_nUDPPort = 0;

		m_pUDPInitDataProc = 0;

		m_nWriteToBufferCount = 0;

		memset(m_nSaveCurNow,0,sizeof(m_nSaveCurNow));

		memset(m_strName,0,sizeof(m_strName));

		memset(m_strDbfName,0,sizeof(m_strDbfName)); // .dbf,.code
		memset(m_strStaticFile,0,sizeof(m_strStaticFile)); 
		
		memset(m_strUserDbf,0,sizeof(m_strUserDbf));
		memset(m_strSanBanDbfName,0,sizeof(m_strSanBanDbfName));
		memset(m_strSjsxxnName,0,sizeof(m_strSjsxxnName));
		
		m_cAdd = 1;
	}

	~MarketInfo_send()
	{		
		if( m_stiStock )
		{
			delete[] m_stiStock;
			m_stiStock = NULL;
		}
	}

	void Empty()
	{
		for(int i = 0; i < m_nTypeTotal; i++)
		{
			m_stiStock[i].m_stType.m_nTotal = 0;
			m_stiStock[i].m_stType.m_nOffset = 0;
		}
	}

	int IsAdd(HSMarketDataType cBourse,CYlsIni* pYlsIniFile);

	void Set(CYlsIni* pYlsIniFile,
		const char* strName,HSMarketDataType cBourse,int nID,
		YlsUpdateDataProc pYlsUpdateDataProc,
		YlsInitDataProc	  pYlsInitDataProc,
		int nSubCount = SC_MAX,
		int nPos = -1,
		YlsUpdateDataProc pYlsUpdateDataProcWH = NULL,
		YlsUpdateDataProc pYlsUpdateDataProcQH = NULL);

	int GetInitDataTime(int x,int nAdd = 0);

	void ReSetInit(int nTimer,CMainFrameSend* pMain,long& lLastError);
	//BOOL IsReInit(int nTimer,StockType* pStockType);

	void SetCodeFile(const char* szPath);

	MarketInfo_send* GetMarket(const char* strCode,CHSStockPosition_send*& pPosition);

public:
	long IsRunTime(int nDist,CMainFrameSend* pMain);
	long IsOpenTime(int nDist = 0);
	long IsOpenRunning(int nPreDist,int nLastDist);

	// �����ʼ������
	void SaveUpdateDate(int lDate);  

	BOOL IsInit() { return (m_bInit && m_bReceived); }

#ifndef HS_SUPPORT_UNIX
	void StartOtherThread(ThreadStartParam* pThreadStartParam);
	void StopOtherThread(CMainFrame* pCMainFrame);

	void AddOtherThread(int nID,YlsUpdateDataProc pYlsUpdateDataProc);
#endif


#ifndef	HS_SUPPORT_UNIX
	CYlsMutex	m_pMutex; // 
#endif


	// ��������
	CYlsMutex	m_pCodeMutex; 

	char		m_nSaveCurNow[16]; // ������������

public:
	char* GetMarketInfo(CHqDataBuffer& buffer);

};



class MarketInfoManager
{
public:
	MarketInfoManager(void);
	virtual ~MarketInfoManager(void);

public://protected:
	CYlsArray<MarketInfo_send*,MarketInfo_send*>	m_ay;
	CYlsMapWordToPtr								m_map;
	CYlsMapStringToPtr								m_mapNotFindCode;
	//CMap<int,int,MarketInfo_send*,MarketInfo_send*> m_map;
	//CMapStringToString				m_mapNotFindCode;

public:	
	BOOL		     IsNotCode(const char* strCode,int nLen,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay);
	BOOL			 IsClassifyStock(MarketInfo_send* pMarketInfo,const char* strCode);

	void		     Add(MarketInfo_send* pMarketInfo,const char* str = "" /*������*/);

	char*			 GetMarketInfo(CHqDataBuffer& buffer);

	MarketInfo_send* GetMarketByInclude(const char* strCode);

	MarketInfo_send* GetMarket( const char* strCode,CHSStockPosition_send*& pPosition,MarketInfo_send* pBaseMarketInfo = NULL );

	MarketInfo_send* GetMarketPtr_JiaoTong(const char* strCode,
		CHSStockPosition_send*& pPosition,
		CMainFrameSend* pMain = NULL,
		BOOL bInit = FALSE,BOOL bNotAdd = TRUE);

	MarketInfo_send* GetMarketPtr( const char* strCode,
		CHSStockPosition_send*& pPosition,
		CMainFrameSend* pMain = NULL,
		const char* strDispCode = "",
		const char* strDispName = "",
		MarketInfo_send* pCurMarketInfo = NULL,
		const char* szExchangeCode = "",
		MarketInfo_send* pUserMarketInfo = NULL /*�ڵ�ǰ�ڲ���*/ 
		);

	MarketInfo_send* GetMarketByCode(const char* strCode);

	MarketInfo_send* GetMarketPtr_SZFZ(const char* strCode,CHSStockPosition_send*& pPosition,CMainFrameSend* pMain = NULL);

	MarketInfo_send* GetMarketPtr_YF(YF_stRecordFXStock* pstRecordFXStock,CHSStockPosition_send*& pPosition,CMainFrameSend* pMain = NULL);
	MarketInfo_send* GetMarketPtr_GG(YF_stRecordHKStock* pstRecordFXStock,CHSStockPosition_send*& pPosition,CMainFrameSend* pMain = NULL);

	MarketInfo_send* GetMarketPtr_YT(SendUDPDataItem* pSendUDPDataItem,
		CHSStockPosition_send*& pPosition,
		CMainFrameSend* pMain = NULL,
		BOOL bNextMarket = TRUE,
		BOOL bNotCheckReceived = FALSE,
		BOOL bAutoWriteFile = TRUE,
		MarketInfo_send* pDefaultMarketInfo = NULL);

	MarketInfo_send* GetMarketPtr_YT(QUOTATION* pQuotation,
		CHSStockPosition_send*& pPosition,
		CMainFrameSend* pMain = NULL,
		BOOL bNextMarket = TRUE,
		BOOL bNotCheckReceived = FALSE,
		BOOL bAutoWriteFile = TRUE,
		MarketInfo_send* pDefaultMarketInfo = NULL);

	void Write_GG(YF_stRecordHKStock* pstRecordFXStock,CMainFrameSend* pMain);
	int  GetDispCode(int& nDelete,CHqDataBuffer*& pCodeInfo,CHqDataBuffer*& pOldName,
		CHqDataBuffer*& pType,
		CHqDataBufferArray& ayRet,char* pStr);

#ifndef HS_SUPPORT_UNIX
	MarketInfo_send* GetMarketPtr_GP( CLevelTwoAnalysis_Map* pLevelTwoAnalysis_Map,CHSStockPosition_send*& pPosition,CMainFrameSend* pMain = NULL,MarketInfo_send* pRefMarketInfo = NULL,BOOL bNotWrite = TRUE);
#endif

	void AllAutoInitData(CMainFrameSend* pMain,CYlsTime& tmNow,int nSend = 1,int nForce = 0);

	void SetCodeFile(const char* szPath);

	void WriteCodeTo(MarketInfo_send* pMarketInfo,const char* strCode,const char* strValue,CMainFrameSend* pMain,
		const char* szName,
		const char* szDispCode,
		int*		pGGType = NULL,
		int*		pPreClose = NULL,
		const char* szExchangeCode = "");

	char* GetMarketCode_GG( YF_stRecordHKStock* pstRecordFXStock,const char* strDispCode,char* szRet);


	MarketInfo_send* GetMarketPtr_Syyh( SyyhItemData* pSyyhItemData,
		CHSStockPosition_send*& pPosition,
		CMainFrameSend* pMain = NULL);



public:
	MarketInfo_send* GetMarketPtr_YF_Convert( const char* strCode,
		CHSStockPosition_send*& pPosition,
		CMainFrameSend* pMain = NULL);

public:
	BOOL IsRequest();

};

#endif
