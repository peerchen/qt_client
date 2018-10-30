

#include "stdafx.h"

#include "marketinfomanager_send.h"

#include "mainframesend.h"
#include "globalfun.h"

SysConfig_send	g_sysSysConfigSend;

#ifndef	HS_SUPPORT_UNIX
int YlsIsalpha(int c)
{
	if( (unsigned)(c + 1) <= 256 )
		return isalpha(c);
	return 0;
}
#endif

CYlsMapWordToPtr MarketInfo_send::g_mapMarketSend;
MarketInfo_send* MarketInfo_send::GetMarketByID(UINT nMarket)
{
	nMarket = MakeMainMarket(nMarket);

	MarketInfo_send* pMarketInfo;
	if( g_mapMarketSend.Lookup(nMarket,(void*&)pMarketInfo) ) // 是否存在
	{
		return pMarketInfo;
	}
	return NULL;
}

BOOL MarketInfo_send::InitToMap(int nCount)
{
	if( nCount <= 0 )
		return FALSE;

	m_nStockTotal = nCount;
	InitMap(m_nStockTotal);

	return TRUE;
}

BOOL MarketInfo_send::AddKey(StockKey* pKey)
{
	if( pKey == NULL )
		return FALSE;

	CHSStockPosition_send* pPosition = new CHSStockPosition_send;
	pPosition->m_lPosIndex = pKey;

	/*printf(pKey->m_stkey);
	printf("\r\n");*/

	if( !this->AddToMap(pKey->m_stkey,pPosition) )
	{
		const CHSStockPosition_send* pOldPosition = GetStockByMap(pKey->m_stkey);
		if( pOldPosition->m_lPosIndex )
		{
			memcpy(pOldPosition->m_lPosIndex,pPosition->m_lPosIndex,sizeof(StockKey));
		}

		delete pPosition;
	}

	return 1;
}

void MarketInfo_send::ChangeCFGFile()
{
	m_sYlsIni.Free();

	char strCFGFile[_MAX_PATH];
	memset(strCFGFile,0,sizeof(strCFGFile));
	strcpy(strCFGFile,GetName());
	strcat(strCFGFile,".cfg");
	
	char szPath[_MAX_PATH];
	CHSFilePath::GetPath(szPath,CHSFilePath::MarketFile);

	char strCurrentPath[_MAX_PATH];
	memset(strCurrentPath,0,sizeof(strCurrentPath));
	strcpy(strCurrentPath,szPath);
	strcat(strCurrentPath,strCFGFile);
	m_sYlsIni.Open(strCurrentPath);
}

void MarketInfo_send::WriteStatic()
{
	if( m_nWriteToBufferCount <= 0 )
		return;

	CYlsFile fp;
	if( !fp.Open(m_strStaticFile,Yls_Create_Open) )
		return;

	const char* key;
	LevelStatic* value;
	POSITION  pos;
	for( pos = m_mapStatic.GetStartPosition(); pos != NULL; )
	{
		m_mapStatic.GetNextAssoc( pos, key, (void*&)value );
		if( value == NULL )
			continue;

		fp.Write(value,sizeof(*value));
	}

	fp.Close();

	m_nWriteToBufferCount = 0;
	
}

void MarketInfo_send::ReadStatic()
{
	CYlsFile fp;
	if( !fp.Open(m_strStaticFile,Yls_OnlyRead_Open) )
		return;

	LevelStatic value;
	LevelStatic* pLevelStatic;
	LevelStatic* pp;

	CHqDataBuffer buffer;
	while(1)
	{
		if( fp.Read(&value,sizeof(value)) != sizeof(value) )
			break;

		pLevelStatic = new LevelStatic;
		memcpy(pLevelStatic,&value,sizeof(value));

		buffer.CopyStr(pLevelStatic->m_calc.m_cCode,sizeof(pLevelStatic->m_calc.m_cCode));

		if( !m_mapStatic.Lookup(buffer.m_lpszBuffer,(void*&)pp) )
		{
			m_mapStatic.SetAt(buffer.m_lpszBuffer,pLevelStatic);
		}
		else
		{
			delete pLevelStatic;
		}
	}

	fp.Close();
}

void MarketInfo_send::WriteDefaultCodetoDisp()
{
	if( MakeMainMarket(this->m_cBourse) == SH_Bourse )
	{
		CYlsIni YlsIni(1);
		YlsIni.Open(m_strCodetoDisp);

		YlsIni.GetProfileString(Section_CodeToDispCode, "000001", "1A0001");  //,"上证指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000002", "1A0002");  //,"Ａ股指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000003", "1A0003");  //,"Ｂ股指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000004", "1B0001");  //,"工业指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000005", "1B0002");  //,"商业指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000006", "1B0004");  //,"地产指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000007", "1B0005");  //,"公用指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000008", "1B0006");  //,"综合指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000010", "1B0007");  //,"上证180",
		YlsIni.GetProfileString(Section_CodeToDispCode, "000011", "1B0008");  //,"基金指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000012", "1B0009");  //,"国债指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000013", "1B0010");  //,"企债指数"
		YlsIni.GetProfileString(Section_CodeToDispCode, "000016", "1B0011");  //,"上证５０"

		//YlsIni.Write();
	}
	else if( MakeMainMarket(this->m_cBourse) == SZ_Bourse )
	{
		CYlsIni YlsIni(1);
		YlsIni.Open(m_strCodetoDisp);

		YlsIni.GetProfileString(Section_CodeToDispCode, "399001", "2A01");  //深证成指
		YlsIni.GetProfileString(Section_CodeToDispCode, "399002", "2A02");  //成份Ａ指
		YlsIni.GetProfileString(Section_CodeToDispCode, "399003", "2A03");  //成份Ｂ指
		YlsIni.GetProfileString(Section_CodeToDispCode, "399006", "2C01");  //深证综指
		YlsIni.GetProfileString(Section_CodeToDispCode, "399007", "2C02");  //深证Ａ指
		YlsIni.GetProfileString(Section_CodeToDispCode, "399008", "2C03");  //深证Ｂ指

		//YlsIni.Write();
	}
}

void MarketInfo_send::ReadCodetoDisp()
{
	CYlsIni YlsIni;
	YlsIni.Open(m_strCodetoDisp);

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> strKeyArray;
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> pValueArray;

	// 实际代码=显示代码
	int nCount = YlsIni.ReadConfigSectionString(Section_CodeToDispCode,strKeyArray,&pValueArray);

	CHqDataBuffer* pKey;
	CHqDataBuffer* pValue;
	for(int i = 0; i < nCount; i++ )
	{
		pKey = strKeyArray.GetAt(i);
		if( pKey == NULL || pKey->IsEmpty() )
			continue;

		pValue = pValueArray.GetAt(i);
		if( pValue == NULL )
			continue;
		if( pValue->IsEmpty() )
		{
			delete pValue;
			continue;
		}

		pKey->MakeUpper();
		m_mapCodetoDisp.SetAt(pKey->m_lpszBuffer,pValue);
	}

	_delArrayObj(strKeyArray);
	pValueArray.RemoveAll();
}

void MarketInfo_send::BulidStockInfo(CMainFrameSend* pMain)
{
	if( pMain == NULL )
		return;

	ChangeCFGFile();

	// 子类
	char nSaveCurNow = 0;
	HSMarketDataType cType;
	for( int i = 0; i < m_nTypeTotal; i++ )
	{
		cType = m_cBourse | (HSMarketDataType)i;
		pMain->BulidStockInfo(m_stiStock[i], cType, nSaveCurNow);

		// 保留当日数据
		if( i < 16 )
			m_nSaveCurNow[i] = nSaveCurNow;
	}

	this->m_sYlsIni.Write();
}

int MarketInfo_send::IsAdd(HSMarketDataType cBourse,CYlsIni* pYlsIniFile)
{
	char szEntry[64];
	sprintf(szEntry,"%hx",cBourse);
	int nRet = pYlsIniFile->ReadInteger(Section_MarketList,szEntry,-1);
	if(nRet == -1)
	{
		pYlsIniFile->WriteInteger(Section_MarketList,szEntry,1);
		return 1;
	}

	return nRet;
}

void MarketInfo_send::Set(CYlsIni* pYlsIniFile,
						  const char* strName,
						  HSMarketDataType cBourse,int nID,
						  YlsUpdateDataProc pYlsUpdateDataProc,
						  YlsInitDataProc   pYlsInitDataProc,
						  int nSubCount /*= SC_MAX*/,
						  int nPos /*= -1*/,
						  YlsUpdateDataProc pYlsUpdateDataProcWH /*= NULL*/,
						  YlsUpdateDataProc pYlsUpdateDataProcQH /*= NULL*/)
{
	if( strName )
		strncpy(m_strName,strName,sizeof(m_strName));

	m_cBourse = cBourse;

	if( strlen(m_strName) <= 0 )
		sprintf(m_strName,"%hx",this->m_cBourse);

	m_nID = nID;

	m_pYlsInitDataProc     = pYlsInitDataProc;

	m_pYlsUpdateDataProc   = pYlsUpdateDataProc;
	m_pYlsUpdateDataProcWH = pYlsUpdateDataProcWH;
	m_pYlsUpdateDataProcQH = pYlsUpdateDataProcQH;
	
	if( IsAdd(cBourse,pYlsIniFile) )
	{
		m_cAdd = 1;
		g_mapMarketSend.SetAt(cBourse,this);
	}
	else
	{
		m_cAdd = 0;
	}

//#ifndef HS_SUPPORT_UNIX
//	if( nPos != -1 )
//	{
//		extern CTypedPtrMap<CMapWordToPtr,WORD,MarketInfo_send*> m_mapTestMarket;
//
//		m_mapTestMarket.SetAt(nPos,this);
//	}
//#endif

}

BOOL MarketInfo_send::InitData(CZMRequest* pRequest,BOOL bSend,CMainFrameSend* pMain)
{
	if( m_pYlsInitDataProc )
	{
		m_bInit = (*m_pYlsInitDataProc)(pRequest,bSend,this,pMain);
	}

	return m_bInit;
}

const char* MarketInfo_send::GetName()
{ 
	return m_strName;
}

void MarketInfo_send::SetCodeFile(const char* szPath)
{
//	m_strDbfName = pApp->GetProfileString(strSection,m_strName, "");
//	if( m_strDbfName.IsEmpty() )
//	{
		sprintf(m_strStaticFile,"%s%s.static",szPath,m_strName);

		sprintf(m_strCodetoDisp,"%s%s.disp",szPath,m_strName);
		/*if (access(m_strCodetoDisp, 0) != 0)
		{
			CYlsFile fpTemp;
			if(fpTemp.Open(m_strCodetoDisp, Yls_Create_Open))
			{
				fpTemp.Close();
			}
		}*/

		sprintf(m_strDbfName,"%s%s.code",szPath,m_strName);
		if (access(m_strDbfName, 0) != 0)
		{
			CYlsFile fpTemp;
			if(fpTemp.Open(m_strDbfName, Yls_Create_Open))
			{
				fpTemp.Close();
			}
		}

		// 缺省代码
		WriteDefaultCodetoDisp();

		// 代码对照表
		ReadCodetoDisp();

		// 读取静态数据
		ReadStatic();
//	}
}

long MarketInfo_send::IsOpenTime(int nDist/* = 0*/)
{
	CYlsIni YlsIni;
	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);
	YlsIni.Open(szPath);

	int lDate = YlsIni.GetProfileInt(MarketInfo_Date, m_strName, 0);

	StockTypeInfo* pStockTypeInfo = m_stiStock;
	HSTypeTime* pHSTypeTime = pStockTypeInfo->m_stType.m_nNewTimes;
	
	return IsExceedCloseTime(lDate,pHSTypeTime->m_nOpenTime,nDist);
}

long MarketInfo_send::IsOpenRunning(int nPreDist,int nLastDist)
{
	// 判断当前时间是否为开盘时间
	StockTypeInfo* pStockTypeInfo = m_stiStock;
	HSTypeTime* pHSTypeTime = pStockTypeInfo->m_stType.m_nNewTimes;	
	
	CYlsTime tmCur = CYlsTime::GetCurrentTime();

	int nStart = pHSTypeTime->m_nOpenTime;
	nStart -= nLastDist;

	CYlsTime tmBegin = CYlsTime(tmCur.GetYear(),
		tmCur.GetMonth(),
		tmCur.GetDay(),
		nStart/60,nStart%60,0);

	int lEnd  = pHSTypeTime->m_nOpenTime;
	lEnd -= nPreDist;

	CYlsTime tmEnd = CYlsTime(tmCur.GetYear(),
		tmCur.GetMonth(),
		tmCur.GetDay(),
		lEnd/60,lEnd%60,0);

	return (tmCur >= tmBegin && tmCur <= tmEnd);
}

void MarketInfo_send::SaveUpdateDate(int lDate)
{
	CYlsIni YlsIni;
	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);
	YlsIni.Open(szPath);

	// 保存日期
	CYlsTime curTime = CYlsTime::GetCurrentTime();
	/*char strTime[32];
	sprintf(strTime,"%04d%02d%02d",curTime.GetYear(),curTime.GetMonth(),curTime.GetDay());
	int lDate = atol(strTime);*/

	char strTimeDetail[32];
	sprintf(strTimeDetail,"%04d/%02d/%02d-%02d:%02d:%02d",
		curTime.GetYear(),curTime.GetMonth(),curTime.GetDay(),
		curTime.GetHour(),curTime.GetMinute(),curTime.GetSecond());
	short sNowMins = curTime.GetHour() * 60 + curTime.GetMinute();

	//
	YlsIni.WriteProfileInt(MarketInfo_Date, m_strName, CalculateCloseDate(lDate,sNowMins));
	YlsIni.WriteProfileString(MarketInfo_Date_detail, m_strName, strTimeDetail);
	
	YlsIni.Write(NULL);

	//
	static LogSystem lonInit("初始化日志数据.dat",10);
	char strLog[256];
	sprintf(strLog,"[%s] %s %s \r\n",g_strCfgfileName,m_strName,strTimeDetail);
	lonInit.WriteLog(strLog);

}
// 计算收盘日期
long MarketInfo_send::CalculateCloseDate(long lDate, long lTime)
{
	if (lDate == 0)
		return 0;

	StockTypeInfo* pStockTypeInfo = m_stiStock;
	StockType* pStockType = &pStockTypeInfo->m_stType;
	
	HSTypeTime* pHSTypeTime = pStockTypeInfo->m_stType.m_nNewTimes;


	// 取最后一个日期和时间点
	int lEnd = -1;
	int lBegin = 0;
	for( int i = 0; i < _countof(pStockType->m_nNewTimes); i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( lBegin != -1 && (lBegin < pHSTypeTime->m_nCloseTime ) )
		{
			lBegin = pHSTypeTime->m_nCloseTime;
		}
		else
		{
			lBegin = -1; // 跨天
		}

		lEnd = pHSTypeTime->m_nCloseTime; // 得到最后时刻
	}

	// 跨天
	if( (lBegin == -1) && (lTime > lEnd) && (lEnd > 720))
	{
		CYlsTime tm = CYlsTime(lDate/10000,
			lDate%10000/100,
			lDate%10000%100,
			0,0,0);
		tm += CYlsTimeSpan(1,0,0,0); // 添加
		lDate = tm.GetYear() * 10000 + tm.GetMonth() * 100 + tm.GetDay();
	}

	return lDate;
}

// modified by Ben 20100624

long MarketInfo_send::IsRunTime(int nDist,CMainFrameSend* pMain)
{
	StockTypeInfo* pStockTypeInfo = m_stiStock;
	HSTypeTime* pHSTypeTime = pStockTypeInfo->m_stType.m_nNewTimes;



	CYlsTime curTime = CYlsTime::GetCurrentTime();

	short nowTime = curTime.GetHour()*60 + curTime.GetMinute();
	char strDate[9];
	sprintf(strDate,"%04d%02d%02d",curTime.GetYear(),
		curTime.GetMonth(),curTime.GetDay());
	long lCurrDate = CalculateCloseDate(atol(strDate), nowTime);





	//
	CYlsIni YlsIni;
	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Dynamic_File);//Srv_Setting_File);
	YlsIni.Open(szPath);

	int lDate = YlsIni.GetProfileInt(MarketInfo_Date, m_strName, 0);

	int nInit = IsExceedRunTime(lDate,pHSTypeTime->m_nOpenTime,lCurrDate, nowTime, nDist);

	if( lDate <= 0 || nInit )
	{
		if( nInit && MakeMarket(m_cBourse) == STOCK_MARKET && !IsOpenRunning(2,40) )
		{
			char str[256];
			sprintf(str,"[%s] 已经错过初始化时间（9:00~9:28），请确认行情是否正常，不正常，则需要手工初始化,然后补线！",this->GetName());
			pMain->Prompt(str);
			return 0;
		}

		m_nWaitTime = 2;		
		return 1;
	}

	return 0;
}

int MarketInfo_send::GetInitDataTime(int x,int nAdd /*= 0*/)
{
	int nCur = 30;

	if( MakeMarket(x) == MakeMarket(STOCK_MARKET) )
		nCur = g_sysSysConfigSend.m_nInitTime_GP;
	else if( MakeMarket(x) == MakeMarket(FUTURES_MARKET) ) 
		nCur = g_sysSysConfigSend.m_nInitTime_QH;
	else if( MakeMarket(x) == MakeMarket(FOREIGN_MARKET) ) 
		nCur = g_sysSysConfigSend.m_nInitTime_WH;
	else if( MakeMarket(x) == MakeMarket(WP_MARKET) ) 
		nCur = g_sysSysConfigSend.m_nInitTime_WP;
	else if( MakeMarket(x) == MakeMarket(HK_MARKET) ) 
		nCur = g_sysSysConfigSend.m_nInitTime_GG;
	else if( MakeMarket(x) == MakeMarket(HJ_MARKET) ) 
		nCur = g_sysSysConfigSend.m_nInitTime_HJ;

	return (nCur + nAdd); 
}

void MarketInfo_send::ReSetInit(int nTimer,CMainFrameSend* pMain,long& lLastError)
{

	// 保存代码表文件
	int nCount = m_sCurYlsIni.AutoWrite();
	if( nCount > 0 && pMain )
	{
		char szData[1024];
		sprintf(szData,"[%s],自动写入初始化代码数：%i",this->GetName(),nCount);
		pMain->Prompt(szData);
	}

	// 写入静态数据
	WriteStatic();

	// 
	if( m_bInit && (!m_bReceived) && m_nWaitTime > 0 )
	{
		lLastError = LastError_initErrorReceived;
		m_nWaitTime--;
		return;
	}

	// 
	if( m_bInit && (!m_bReceived) )
	{
		lLastError = LastError_initErrorReceived2;
		m_bInit = FALSE;
	}

	// 通过时间,判断什么时候重新初始化
	if( m_bInit && m_bReceived && m_stiStock )
	{
		//StockTypeInfo* pStockTypeInfo = m_stiStock; // 提前初始化

		int nDist = GetInitDataTime(m_cBourse);
		//if( MakeMarket(m_cBourse) == HK_MARKET )
		//	nDist += 20;
		//else if( MakeMarket(m_cBourse) == STOCK_MARKET )
		//	nDist -= 1;

		if( MakeMarket(m_cBourse) == WP_MARKET ||
			MakeMarket(m_cBourse) == FOREIGN_MARKET||
			MakeMarket(m_cBourse) == HJ_MARKET )
			nDist += 20;

		// 
		if( IsRunTime(nDist,pMain) )
		{
			if( pMain )
			{
				char str[128];
				sprintf(str,"[%s] 自动初始化！",this->GetName());
				pMain->Prompt(str);
			}

			//if( !m_bReInit && m_bInit && m_bReceived )
			{
				m_bInit		= FALSE;
				m_bReceived = FALSE;

				// 
				if( pMain )
				{
					pMain->StartInitData(m_cBourse,1);
				}
			}
			//m_bReInit = TRUE;
		}
		else
		{
			lLastError = LastError_NotInitTime;
			m_bReInit = FALSE;
		}
	}
	// 2007.04.26 add
	else if( !m_bInit )
	{
		if( pMain )
		{
			lLastError = LastError_ForceInit;
			pMain->StartInitData(m_cBourse,1);
		}
#if 0
		if( pMain )
		{
			lLastError = LastError_ForceInit;
			pMain->StartInitData(m_cBourse,0);
		}
#endif
	}
}

BOOL MarketInfo_send::IsInclude(const char* strCode)
{
	if( strCode == NULL || strlen(strCode) <= 0 )
		return FALSE;

	CHqDataBuffer buffer;
	char* pData = YlsMakeLower(strCode,buffer);
	if( pData == NULL )
		return FALSE;

	CHqDataBuffer* str;
	for(int i = 0; i < m_ay.GetSize(); i++ )
	{
		str = m_ay.GetAt(i);
		if( str == NULL ||
			str->IsEmpty() )
			continue;

		if( buffer.Find(str->m_lpszBuffer) != -1 )
			return TRUE;

		//if( memcmp(strCode,str,min(strlen(str),strlen(strCode))) == 0 )
		//	return TRUE;
	}

	return FALSE;
}

void MarketInfo_send::FreeUserReportData()
{

}

void MarketInfo_send::RemoveAllThreadParam()
{
	ThreadStartParam* pParam;
	int i;

	for( i = m_ayThreadParam.GetSize() - 1; i >= 0; i-- )
	{
		pParam = m_ayThreadParam.GetAt(i);
		if( pParam == NULL )
		{
			m_ayThreadParam.RemoveAt(i);
			//i--;
			continue;
		}
	}
}

void MarketInfo_send::StopAllThreadParam()
{
	CYlsArray<ThreadStartParam*,ThreadStartParam*> ay;
	ThreadStartParam* pParam;
	int i;

	for( i = 0; i < m_ayThreadParam.GetSize(); i++ )
	{
		pParam = m_ayThreadParam.GetAt(i);
		if( pParam == NULL )
			continue;

		if( pParam->m_nStopFlag == 2 )
		{
			ay.Add(pParam);
			m_ayThreadParam.SetAt(i,NULL);
		}
		else if( pParam->m_nStopFlag == 3 )
		{
			pParam->m_nStopFlag = 1;
		}
	}

	for( i = 0; i < ay.GetSize(); i++ )
	{
		delete ay.GetAt(i);
	}
}

void MarketInfo_send::AddThreadParam(ThreadStartParam* pParam)
{
	m_ayThreadParam.Add(pParam);
}

char* MarketInfo_send::GetMarketInfo(CHqDataBuffer& buffer)
{
	buffer.Free();

	buffer.AddStr("初始化(m_bInit):");
	buffer.AddLong(this->m_bInit);

	buffer.AddStr("接收返回状态(m_bReceived):");
	buffer.AddLong(this->m_bReceived);

	buffer.AddStr("初始化代码数(m_mapCode):");
	buffer.AddLong(this->m_mapCode.GetSize());
	buffer.AddStr("\r\n");

	buffer.AddStr("代码列表:");
	const char* key = NULL;
	CHqDataBuffer* value = NULL;
	POSITION  pos;
	for( pos = m_mapCode.GetStartPosition(); pos != NULL; )
	{
		m_mapCode.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			buffer.AddStr(value->m_lpszBuffer,value->m_cbBuffer);
			buffer.AddStr(",");
		}
	}
	
	if( buffer.IsValid() )
		return buffer.m_lpszBuffer;

	return "";
}

MarketInfo_send* MarketInfo_send::GetMarket(const char* strCode,CHSStockPosition_send*& pPosition)
{
	CHqDataBuffer* strDispCode;
	MarketInfo_send* pMarketInfo = this;

	/*char sz[256];
	sprintf(sz,"个数：%i\r\n",m_ay.GetSize());
	printf(sz);*/

	CHqDataBuffer strCurCode;
	strCurCode.CopyStr(strCode);

	if( !strCurCode.IsValid() )
		return NULL;

	if( pMarketInfo->m_mapCode.Lookup(strCurCode.m_lpszBuffer,(void*&)strDispCode) )
	{
		StockKey* psKey = new StockKey;
		strncpy(psKey->m_stkey,strDispCode->m_lpszBuffer,sizeof(psKey->m_stkey));

		pPosition = (CHSStockPosition_send*)pMarketInfo->GetStockByMap(psKey->m_stkey);

		delete psKey;

		if( pPosition == NULL )
			return NULL;

		return pMarketInfo;
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
MarketInfoManager::MarketInfoManager(void)
{
}

MarketInfoManager::~MarketInfoManager(void)
{
}

BOOL MarketInfoManager::IsRequest()
{
	MarketInfo_send* pMarketInfo;
	for( int i = 0; i < m_ay.GetSize(); i++ )
	{
		pMarketInfo = m_ay.GetAt(i);
		if( pMarketInfo == NULL )
			continue;

		if( !pMarketInfo->m_bInit || !pMarketInfo->m_bReceived )
			return 0;
	}

	return 1;
}

void MarketInfoManager::Add(MarketInfo_send* pMarketInfo,const char* str) 
{ 
	if( pMarketInfo == NULL )
		return;

	if( !pMarketInfo->m_cAdd )
		return;

	if( strlen(str) > 0 )
	{
		CHqDataBuffer buffer;
		char* pData = YlsMakeLower(str,buffer);
		if( pData != NULL )
		{
			AnalyzeStr(buffer.m_lpszBuffer,",",pMarketInfo->m_ay);
		}
	}

	//printf("MarketInfoManager::Add\r\n");

	m_ay.Add(pMarketInfo);
	::YlsMapAdd(m_map,pMarketInfo->m_cBourse,(void*)pMarketInfo);
}

char* MarketInfoManager::GetMarketInfo(CHqDataBuffer& buffer)
{
	MarketInfo_send* pMarketInfo;
	for( int i = 0; i < m_ay.GetSize(); i++ )
	{
		pMarketInfo = m_ay.GetAt(i);
		if( pMarketInfo == NULL )
			continue;

		CHqDataBuffer curBuffer;
		pMarketInfo->GetMarketInfo(curBuffer);
		if( curBuffer.IsValid() )
		{
			buffer.AddStr(curBuffer.m_lpszBuffer,curBuffer.m_cbBuffer);
			buffer.AddStr("\r\n\r\n");
		}		
	}
	
	if( buffer.IsValid() )
		return buffer.m_lpszBuffer;

	return "";
}

MarketInfo_send* MarketInfoManager::GetMarket(const char* strCode,CHSStockPosition_send*& pPosition,
											  MarketInfo_send* pBaseMarketInfo /*= NULL*/ )
{
	if( pBaseMarketInfo != NULL )
		return pBaseMarketInfo->GetMarket(strCode,pPosition);

	CHqDataBuffer* strDispCode;
	MarketInfo_send* pMarketInfo;

	/*char sz[256];
	sprintf(sz,"个数：%i\r\n",m_ay.GetSize());
	printf(sz);*/

	CHqDataBuffer strCurCode;
	strCurCode.CopyStr(strCode);

	if( !strCurCode.IsValid() )
		return NULL;
	
	for( int i = 0; i < m_ay.GetSize(); i++ )
	{
		pMarketInfo = m_ay.GetAt(i);
		if( pMarketInfo == NULL )
			continue;
		

		if( pMarketInfo->m_mapCode.Lookup(strCurCode.m_lpszBuffer,(void*&)strDispCode) )
		{
			StockKey* psKey = new StockKey;
			strncpy(psKey->m_stkey,strDispCode->m_lpszBuffer,sizeof(psKey->m_stkey));

			pPosition = (CHSStockPosition_send*)pMarketInfo->GetStockByMap(psKey->m_stkey);

			delete psKey;

			if( pPosition == NULL )
				continue;

			return pMarketInfo;
		}	
	}

	return NULL;
}

BOOL MarketInfoManager::IsNotCode(const char* strCode,int nLen,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ay)
{
	if( strCode == NULL || ay.GetSize() <= 0 )
		return FALSE;

	CHqDataBuffer* pStart;
	for( int i = 0; i < ay.GetSize(); i++ )
	{
		pStart = ay.GetAt(i);
		if( pStart == NULL || !pStart->IsValid() )
			continue;

		if( memcmp(strCode,pStart->m_lpszBuffer,strlen(pStart->m_lpszBuffer)) == 0 )
			return TRUE;
	}

	return FALSE;
}

BOOL MarketInfoManager::IsClassifyStock(MarketInfo_send* pMarketInfo,const char* strCode)
{
	if( pMarketInfo == NULL || strCode == NULL )
		return FALSE;

	StockTypeInfo* pStock = pMarketInfo->m_stiStock;
	short nTotal = pMarketInfo->m_nTypeTotal;

	char* pStart;
	char* pEnd;

	YlsMakeUpper((char*)strCode);
	//printf(strCode);
	//printf("\r\n");

	int nLen = strlen(strCode);

	CHqDataBuffer strFind;
	strFind.CopyStr(strCode);

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;

	for( int i = 0; i < nTotal; i++ )
	{
		AnalyzeStr(pStock[i].m_strNotCode.m_lpszBuffer,",",ay);

		if( IsNotCode(strCode,nLen,ay) )
			continue;

		CHqDataBuffer strScope;
		strScope.CopyStr(pStock[i].m_strCodeScope.m_lpszBuffer);
		if( !strScope.IsValid() )
			continue;

		YlsMakeUpper(strScope.m_lpszBuffer);

		//printf(strScope.m_lpszBuffer);
		//printf("\r\n");

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
					return TRUE;
				}
			}
			// 完全匹配
			else if( !strncasecmp(strCode,pStart,strlen(strCode)) )
			{
				return TRUE;
			}
			// 前面匹配
			else if( memcmp(strCode,pStart,min(strlen(strCode),strlen(pStart))) == 0 )
			{
				return TRUE;
			}
			// 部分包含
			else if( strFind.Find(pStart) != -1 ) 
			{
				return TRUE;
			}
			
			pStart = strtok(NULL,",");
		}
	}

	return FALSE;
}

MarketInfo_send* MarketInfoManager::GetMarketByCode(const char* strCode)
{
	if( strCode == NULL ||
		strlen(strCode) <= 0 )
		return NULL;

	MarketInfo_send* pMarketInfo;

	for( int i = 0; i < m_ay.GetSize(); i++ )
	{
		pMarketInfo = m_ay.GetAt(i);
		if( pMarketInfo == NULL )
			continue;

		if( pMarketInfo->IsInclude(strCode) )
			return pMarketInfo;
	}

	return NULL;
}

MarketInfo_send* MarketInfoManager::GetMarketByInclude(const char* strCode)
{
	MarketInfo_send* pMarketInfo;

	for( int i = 0; i < m_ay.GetSize(); i++ )
	{
		pMarketInfo = m_ay.GetAt(i);
		if( pMarketInfo == NULL )
			continue;

		if( IsClassifyStock(pMarketInfo,strCode) )
			return pMarketInfo;
	}

	return NULL;
}

int MarketInfoManager::GetDispCode(int& nDelete,
								   CHqDataBuffer*& pCodeInfo,
								   CHqDataBuffer*& pOldName,
								   CHqDataBuffer*& pType,
								   CHqDataBufferArray& ayRet,char* pStr)
{
	if( pStr == NULL || strlen(pStr) <= 0 )
		return 0;

	int nCount = AnalyzeStr(pStr,",",ayRet.ay);

	if( nCount >= 4 )
	{			
		// 显示名称
		pOldName = ayRet.ay.GetAt(1);
		if( pOldName )
			pOldName->Trim();

		// 显示代码
		pCodeInfo = ayRet.ay.GetAt(3);
		if( pCodeInfo )
			pCodeInfo->Trim();

		// 是否删除
		CHqDataBuffer* pDel = ayRet.ay.GetAt(2);
		if( pDel && pDel->IsValid() )
		{
			pDel->Trim();
			nDelete = atol(pDel->m_lpszBuffer);
		}

		if( nCount > 4 )
		{
			pType = ayRet.ay.GetAt(4);
			if( pType )
				pType->Trim();
		}

		return (pCodeInfo != NULL);
	}

	return 0;
}

void MarketInfoManager::WriteCodeTo(MarketInfo_send* pMarketInfo,
									const char* strCode,
									const char* strValue,
									CMainFrameSend* pMain,
									const char* szName,
									const char* szDispCode,
									int*		pGGType /*= NULL*/,
									int*		pPreClose /*= NULL*/,
									const char* szExchangeCode /*= ""*/)
{
	if( pMarketInfo == NULL || strCode == NULL || strlen(strCode) <= 0 || strlen(strCode) > 20 )
		return;
	
#ifndef	HS_SUPPORT_UNIX
	CYlsMutex* pMutex = NULL;
	if( pMarketInfo )
		pMutex = &pMarketInfo->m_pMutex;

	CYlsMutexLock lock(pMutex);
#endif

	if( pMarketInfo )
	{
		const char* szNewName = szName;

		//
		if( !pMarketInfo->m_sCurYlsIni.IsOpen() )
			pMarketInfo->m_sCurYlsIni.Open(pMarketInfo->m_strDbfName);

		char* pStr = pMarketInfo->m_sCurYlsIni.GetProfileString("code",strCode,"");

		int nDelete = 0;
		CHqDataBuffer* pCodeInfo = NULL;
		CHqDataBuffer* pOldName = NULL;
		CHqDataBuffer* pTypeValue = NULL;
		CHqDataBufferArray ayRet;

		// 得到原有项
		GetDispCode(nDelete,pCodeInfo,pOldName,pTypeValue,ayRet,pStr);

		// 找到对应代码
		CHqDataBuffer* pCodeToDisp;
		if( pMarketInfo->m_mapCodetoDisp.Lookup(strCode,(void*&)pCodeToDisp) )
		{
			szDispCode = pCodeToDisp->m_lpszBuffer;
		}
		else if( pCodeInfo != NULL )
		{
			szDispCode = pCodeInfo->m_lpszBuffer;
		}

		// 取旧的名称
		if( pOldName != NULL && (szName == NULL || strlen(szName) <= 0) )
		{
			szName = pOldName->m_lpszBuffer;
		}

		// 取旧的类型分类
		int nType;
		if( pTypeValue != NULL )
		{
			nType = atol(pTypeValue->m_lpszBuffer);
			pGGType = &nType;
		}

		//
		char strOldValue[256];
		sprintf(strOldValue," %s, %s, %i, %s, %i, %i,",
			strCode,							 // 代码 
			szName?szName:"",					 // 名称
			nDelete,							 // 删除标志
			szDispCode?szDispCode:"",			 // 实际显示代码
			pGGType?*pGGType:0,					 // 港股类型
			pPreClose?*pPreClose:0);			 // 昨收盘

		pMarketInfo->m_sCurYlsIni.WriteProfileString("code",strCode,strOldValue);

		// 港股必须有名称
		if( MakeMarket(pMarketInfo->m_cBourse) == HK_MARKET )
		{
			if( szNewName != NULL )
				m_mapNotFindCode.SetAt(strCode,(void*)strCode);
		}
		else
		{
			m_mapNotFindCode.SetAt(strCode,(void*)strCode);
		}
	}
	else
	{
		CYlsIni	sYlsIni;
		sYlsIni.Open(g_strQiHuoCodeProfile);

		char strOldValue[512];
		sprintf(strOldValue," %s, %s, %i, %s, %s, %i,",
			strCode,			// 代码 
			"",					// 名称
			0,					// 删除标志
			"",					// 实际显示代码
			szExchangeCode,		// 类型
			0);					// 昨收盘
		sYlsIni.WriteProfileString("code",strCode,strOldValue);
		sYlsIni.Write();

		char str[256];
		sprintf(str,"收到新代码： %s,必须手工添加才有效,具体察看文件%s。",
			strCode,g_strQiHuoCodeProfile);

		if( pMain )
			pMain->Prompt(str);

		m_mapNotFindCode.SetAt(strCode,(void*)strCode);
	}
}

#ifndef HS_SUPPORT_UNIX
MarketInfo_send* MarketInfoManager::GetMarketPtr_GP(CLevelTwoAnalysis_Map* pLevelTwoAnalysis_Map,
													CHSStockPosition_send*& pPosition,
													CMainFrameSend* pMain /*= NULL*/,
													MarketInfo_send* pRefMarketInfo /*= NULL*/,
													BOOL bWrite /*= TRUE*/)
{
	CString strCode = pLevelTwoAnalysis_Map->GetCode();   // 证券代码 Instrument ID

	//CString strExchange = pLevelTwoAnalysis_Map->GetValue(207);

	MarketInfo_send* pMarketInfo = GetMarket(strCode,pPosition);
	if( pMarketInfo == NULL )
		pMarketInfo = pRefMarketInfo;

	//if( pMarketInfo == NULL && pPosition == NULL )
	if( bWrite )
	{
		//void* str;
		//if( !m_mapNotFindCode.Lookup(strCode,str) )
		{
			CString strDispName = pLevelTwoAnalysis_Map->GetValue(55);
 			CString strDispCode = strCode;

			//char mbstr[256];
			wchar_t wcstr[256];

			//memset(mbstr,0,sizeof(mbstr));
			memset(wcstr,0,sizeof(wcstr));

			MultiByteToWideChar( CP_UTF8, 0, (char*)(const char*)strDispName, 
				strlen(strDispName), wcstr, 255 );

			//WideCharToMultiByte( CP_ACP, 0, wcstr, -1,mbstr, 128, NULL, NULL );

			strDispName = wcstr;

			strDispName.Trim();
			strDispCode.Trim();

			//
			CString strValue;

			int nPre = pLevelTwoAnalysis_Map->GetValueInt(140,1000); // 昨收盘价

			/*strValue.Format(" %s, %s, 0, %s, %i",
				strCode,
				strDispName,
				strDispCode,
				nPre);*/

			// 写入到文件
			if( pMarketInfo == NULL )
				pMarketInfo = GetMarketByInclude(strDispCode);

			WriteCodeTo(pMarketInfo,strCode,strValue,pMain,
				strDispName,strDispCode,NULL,&nPre);				
		}
	}

	return pMarketInfo;
}

#endif

MarketInfo_send* MarketInfoManager::GetMarketPtr(const char* strCode,CHSStockPosition_send*& pPosition,
											CMainFrameSend* pMain /*= NULL*/,
											const char* strDispCode /*= ""*/,
											const char* strDispName /*= ""*/,
											MarketInfo_send* pCurMarketInfo /*= NULL*/,
											const char* szExchangeCode /*= ""*/,
											MarketInfo_send* pUserMarketInfo /*= NULL*/)
{
	pPosition = NULL;
	MarketInfo_send* pMarketInfo = GetMarket(strCode,pPosition,pUserMarketInfo);

	// 没有找到的新代码写到配置文件,注意：新代码只有下次初始化才起作用。
	if( pMarketInfo == NULL || !pMarketInfo->m_bReceived )
	{
		if( pPosition == NULL )
		{
			void* str;
			if( !m_mapNotFindCode.Lookup(strCode,str) )
			{
				YlsAllTrim(strDispName);
				YlsAllTrim(strDispCode);

				// 写入到文件
				if( pCurMarketInfo && pMarketInfo == NULL )
				{
					pMarketInfo = pCurMarketInfo;
				}

				if( pMarketInfo == NULL )
				{
					pMarketInfo = GetMarketByCode(strCode);
					if( pMarketInfo == NULL )
						pMarketInfo = GetMarketByInclude(strCode);				
				}

				WriteCodeTo(pMarketInfo,strCode,"",pMain,strDispName,strDispCode,0,0,szExchangeCode);		
			}
		}

		return 0;
	}

	return pMarketInfo;
}

MarketInfo_send* MarketInfoManager::GetMarketPtr_JiaoTong(const char* strCode,
														  CHSStockPosition_send*& pPosition,
														  CMainFrameSend* pMain /*= NULL*/,
														  BOOL bInit /*= FALSE*/,
														  BOOL bNotAdd /*= TRUE*/)
{
	pPosition = NULL;
	MarketInfo_send* pMarketInfo = GetMarket(strCode,pPosition);

	// 没有找到的新代码写到配置文件,注意：新代码只有下次初始化才起作用。
	if( pMarketInfo == NULL || !pMarketInfo->m_bReceived )
	{
		/*if( pMarketInfo )
		{
			char sz[128];
			sprintf(sz,"pMarketInfo:%hx,连接接收状态：%i",(long)pMarketInfo,pMarketInfo->m_bReceived);
			printf(sz);
		}*/

		if( pPosition == NULL )
		{
			if( !bNotAdd )
				return NULL;

			if( strCode && strlen(strCode) >= STOCK_CODE_SIZE )
				return NULL;

			void* str;
			if( bInit || !m_mapNotFindCode.Lookup(strCode,str) )
			{
				char strValue[256];
				memset(strValue,0,sizeof(strValue));
				sprintf(strValue," %s, %s, 0, %s, ",strCode,"","");

				// 写入到文件
				pMarketInfo = GetMarketByCode(strCode);
				if( pMarketInfo == NULL )
				{
					//printf("MarketInfoManager::GetMarketPtr_JiaoTong-begin2\r\n");

					pMarketInfo = GetMarketByInclude(strCode);
					if( pMarketInfo == NULL )  // 缺省为交叉汇率
					{
						pMarketInfo = MarketInfo_send::GetMarketByID(FOREIGN_MARKET | WH_ACROSS_RATE);
					}
				}

				//printf("MarketInfoManager::GetMarketPtr_JiaoTong-begin3\r\n");

				WriteCodeTo(pMarketInfo,strCode,strValue,pMain,"","");

				// 0755-25879131 
				//printf("MarketInfoManager::GetMarketPtr_JiaoTong-end\r\n");
			}
		}

		return 0;
	}

	return pMarketInfo;
}

MarketInfo_send* MarketInfoManager::GetMarketPtr_Syyh( SyyhItemData* pSyyhItemData,
											      CHSStockPosition_send*& pPosition,
												  CMainFrameSend* pMain /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
	return NULL;
#else	
	pPosition = NULL;
	if( pSyyhItemData == NULL )
		return NULL;

	CString strCode = pSyyhItemData->GetCode();
	MarketInfo_send* pMarketInfo = GetMarket(strCode,pPosition);

	// 没有找到的新代码写到配置文件,注意：新代码只有下次初始化才起作用。
	if( pMarketInfo == NULL || !pMarketInfo->m_bReceived )
	{
		if( pPosition == NULL )
		{
			void* str;
			if( !m_mapNotFindCode.Lookup(strCode,str) )
			{
				// 写入到文件
				pMarketInfo = GetMarketByInclude(strCode);
				WriteCodeTo(pMarketInfo,strCode,"",pMain,"","");

				return 0;
			}
		}

		return 0;
	}

	return pMarketInfo;
#endif

}

MarketInfo_send* MarketInfoManager::GetMarketPtr_YF_Convert( const char* strCode,
											    CHSStockPosition_send*& pPosition,
												CMainFrameSend* pMain /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
	return NULL;
#else
	pPosition = NULL;
	if( strCode == NULL ||
		strlen(strCode) <= 0 )
		return NULL;

	MarketInfo_send* pMarketInfo = GetMarket(strCode,pPosition);

	// 没有找到的新代码写到配置文件,注意：新代码只有下次初始化才起作用。
	if( pMarketInfo == NULL || !pMarketInfo->m_bReceived )
	{
		if( pPosition == NULL )
		{
			void* str;
			if( !m_mapNotFindCode.Lookup(strCode,str) )
			{
				CString strDispName;
				CString strDispCode = strCode;
				if( strDispCode.GetLength() >= 5 )
					strDispCode = strDispCode.Mid(1);

				strDispName.Trim();
				strDispCode.Trim();

				CString strValue;
				strValue.Format(" %s, %s, 0, %s, ",strCode,
					strDispName,strDispCode);

				// 写入到文件
				pMarketInfo = GetMarketByInclude(strCode);
				WriteCodeTo(pMarketInfo,strCode,strValue,pMain,
					strDispName,strDispCode);

				return 0;
			}
		}
		return 0;
	}

	return pMarketInfo;
#endif

}

MarketInfo_send* MarketInfoManager::GetMarketPtr_YT(QUOTATION * pQuotation,
													CHSStockPosition_send*& pPosition,
													CMainFrameSend* pMain /*= NULL*/,
													BOOL bNextMarket /*= TRUE*/,
													BOOL bNotCheckReceived /*= FALSE*/,
													BOOL bAutoWriteFile /*= TRUE*/,
													MarketInfo_send* pDefaultMarketInfo /*= NULL*/)
{
	pPosition = NULL;

	char strCode[9];
	memset(strCode, 0 , 9);
	strncpy(strCode,pQuotation->m_CodeInfo.m_acCode,STOCK_CODE_SIZE);
	MarketInfo_send* pMarketInfo = NULL;


	// modified by Ben 20100611 沪深两市有些代码重复
	if (MakeMarket(pQuotation->m_CodeInfo.m_usMarketType) == STOCK_MARKET)
	{
		pMarketInfo = MarketInfo_send::GetMarketByID(pQuotation->m_CodeInfo.m_usMarketType);

		pMarketInfo = pMarketInfo->GetMarket(strCode,pPosition);
	}
	else
		pMarketInfo = GetMarket(strCode,pPosition);


	if( bNextMarket && pMarketInfo == NULL )
		pMarketInfo = MarketInfo_send::GetMarketByID(pQuotation->m_CodeInfo.m_usMarketType);	

	if( !bAutoWriteFile )
		return pMarketInfo;

	// 没有找到的新代码写到配置文件,注意：新代码只有下次初始化才起作用。
	if( pPosition == NULL || pMarketInfo == NULL || 
		(!bNotCheckReceived && !pMarketInfo->m_bReceived) )
	{
		if( pPosition == NULL )
		{
			void* str;
			if( !m_mapNotFindCode.Lookup(strCode,str) )
			{
				CHqDataBuffer strDispName;
				strDispName.CopyStr(pQuotation->m_CodeInfo.m_acName,sizeof(pQuotation->m_CodeInfo.m_acName));
				CHqDataBuffer strDispCode;
				strDispCode.CopyStr(pQuotation->m_CodeInfo.m_acCode,sizeof(pQuotation->m_CodeInfo.m_acCode));
				//CString strDispName = pSendUDPDataItem->m_cStockName;
				//CString strDispCode = pSendUDPDataItem->m_ciStockCode.GetCode();

				strDispName.Trim();
				strDispCode.Trim();

				CHqDataBuffer strValue;
				strValue.Alloc(256);
				sprintf(strValue.m_lpszBuffer," %s, %s, 0, %s, ",strCode,
					strDispName.m_lpszBuffer,strDispCode.m_lpszBuffer);

				int nType = 5;

				// 港股...
				if( (HK_MARKET) == MakeMarket(pQuotation->m_CodeInfo.m_usMarketType) )
				{	
				}
				else
				{
					nType = 0;
				}

				// 缺省...
				if(pMarketInfo == NULL && bNextMarket && pDefaultMarketInfo != NULL )
					pMarketInfo = pDefaultMarketInfo;

				//
				WriteCodeTo(pMarketInfo,strCode,strValue.m_lpszBuffer,pMain,
					strDispName.m_lpszBuffer,strDispCode.m_lpszBuffer,&nType);

				return 0;
			}
		}

		return 0;
	}

	return pMarketInfo;
}

MarketInfo_send* MarketInfoManager::GetMarketPtr_YT( SendUDPDataItem* pSendUDPDataItem,
											    CHSStockPosition_send*& pPosition,
												CMainFrameSend* pMain /*= NULL*/,
												BOOL bNextMarket /*= TRUE*/,
												BOOL bNotCheckReceived /*= FALSE*/,
												BOOL bAutoWriteFile /*= TRUE*/,
												MarketInfo_send* pDefaultMarketInfo /*= NULL*/)
{
	pPosition = NULL;
	if( pSendUDPDataItem == NULL )
		return NULL;

	char strCode[9];
	YlsGetKey(strCode,&pSendUDPDataItem->m_ciStockCode);
	YlsAllTrim(strCode);
	MarketInfo_send* pMarketInfo = NULL;


	// modified by Ben 20100611 沪深两市有些代码重复
	if (MakeMarket(pSendUDPDataItem->m_ciStockCode.m_cCodeType) == STOCK_MARKET)
	{
		pMarketInfo = MarketInfo_send::GetMarketByID(pSendUDPDataItem->m_ciStockCode.m_cCodeType);
		
		pMarketInfo = pMarketInfo->GetMarket(strCode,pPosition);
	}
	else
		pMarketInfo = GetMarket(strCode,pPosition);



	if( bNextMarket && pMarketInfo == NULL )
		pMarketInfo = MarketInfo_send::GetMarketByID(pSendUDPDataItem->m_ciStockCode.m_cCodeType);	

	if( !bAutoWriteFile )
		return pMarketInfo;

	// 没有找到的新代码写到配置文件,注意：新代码只有下次初始化才起作用。
	if( pPosition == NULL || pMarketInfo == NULL || 
		(!bNotCheckReceived && !pMarketInfo->m_bReceived) )
	{
		if( pPosition == NULL )
		{
			void* str;
			if( !m_mapNotFindCode.Lookup(strCode,str) )
			{
				CHqDataBuffer strDispName;
				strDispName.CopyStr(pSendUDPDataItem->m_cStockName,sizeof(pSendUDPDataItem->m_cStockName));
				CHqDataBuffer strDispCode;
				strDispCode.CopyStr(pSendUDPDataItem->m_ciStockCode.m_cCode,sizeof(pSendUDPDataItem->m_ciStockCode.m_cCode));
				//CString strDispName = pSendUDPDataItem->m_cStockName;
				//CString strDispCode = pSendUDPDataItem->m_ciStockCode.GetCode();
				
				strDispName.Trim();
				strDispCode.Trim();

				CHqDataBuffer strValue;
				strValue.Alloc(256);
				sprintf(strValue.m_lpszBuffer," %s, %s, 0, %s, ",strCode,
					strDispName.m_lpszBuffer,strDispCode.m_lpszBuffer);


				int nType = 5;

				// 港股...
				if( (HK_MARKET) == MakeMarket(pSendUDPDataItem->m_ciStockCode.m_cCodeType) )
				{
					// 主板分类...
				}
				else
				{
					nType = 0;
				}

				// 缺省...
				if(pMarketInfo == NULL && bNextMarket && pDefaultMarketInfo != NULL )
					pMarketInfo = pDefaultMarketInfo;

				//
				WriteCodeTo(pMarketInfo,strCode,strValue.m_lpszBuffer,pMain,
					strDispName.m_lpszBuffer,strDispCode.m_lpszBuffer,&nType);

				return 0;
			}
		}

		return 0;
	}

	return pMarketInfo;
}

MarketInfo_send* MarketInfoManager::GetMarketPtr_SZFZ( const char* strCode,
													  CHSStockPosition_send*& pPosition,
													  CMainFrameSend* pMain /*= NULL*/ )
{
#ifdef HS_SUPPORT_UNIX
	return NULL;
#else

	pPosition = NULL;

	if( strCode == NULL )
		return NULL;

	MarketInfo_send* pMarketInfo = GetMarket(strCode,pPosition);

	// 没有找到的新代码写到配置文件,注意：新代码只有下次初始化才起作用。
	if( pMarketInfo == NULL || !pMarketInfo->m_bReceived )
	{
		if( pPosition == NULL )
		{
			void* str;
			if( !m_mapNotFindCode.Lookup(strCode,str) )
			{
				CString strDispName;
				CString strDispCode = strCode;

				strDispName.Trim();
				strDispCode.Trim();

				CString strValue;
				strValue.Format(" %s, %s, 0, %s, ",strCode,
					strDispName,strDispCode);

				// 写入到文件
				pMarketInfo = GetMarketByInclude(strCode);
				WriteCodeTo(pMarketInfo,strCode,strValue,pMain,
					strDispName,strDispCode);

				return 0;
			}
		}
		return 0;
	}

	return pMarketInfo;
#endif
}


MarketInfo_send* MarketInfoManager::GetMarketPtr_YF( YF_stRecordFXStock* pstRecordFXStock,
											    CHSStockPosition_send*& pPosition,
												CMainFrameSend* pMain /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
	return NULL;
#else
	pPosition = NULL;
	if( pstRecordFXStock == NULL )
		return NULL;

	CString strCode = pstRecordFXStock->GetCode();
	MarketInfo_send* pMarketInfo = GetMarket(strCode,pPosition);

	// 没有找到的新代码写到配置文件,注意：新代码只有下次初始化才起作用。
	if( pMarketInfo == NULL || !pMarketInfo->m_bReceived )
	{
		if( pPosition == NULL )
		{
			void* str;
			if( !m_mapNotFindCode.Lookup(strCode,str) )
			{
				CString strDispName = pstRecordFXStock->GetName();
				CString strDispCode = pstRecordFXStock->GetCode();
				if( strDispCode.GetLength() >= 5 )
					strDispCode = strDispCode.Mid(1);

				strDispName.Trim();
				strDispCode.Trim();

				CString strValue;
				strValue.Format(" %s, %s, 0, %s, ",strCode,
					strDispName,strDispCode);

				// 写入到文件
				pMarketInfo = GetMarketByInclude(strCode);
				WriteCodeTo(pMarketInfo,strCode,strValue,pMain,
					strDispName,strDispCode);

				return 0;
			}
		}
		return 0;
	}

	return pMarketInfo;
#endif
}


char* MarketInfoManager::GetMarketCode_GG( YF_stRecordHKStock* pstRecordFXStock,const char* strDispCode,char* szRet)
{
#ifdef HS_SUPPORT_UNIX
	return "";
#else

	int InstrumentType = pstRecordFXStock->GetInstrumentType();

	if( InstrumentType == 13 ||
		InstrumentType == 14 )
	{
		sprintf(szRet,"%s",strDispCode);
	}
	else
	{
#ifdef Support_HKStockUseFive
		sprintf(szRet,"H%05s",strDispCode);	  //港股代码 
#else
		sprintf(szRet,"%s%04s","HK",strDispCode); //港股代码 
#endif
	}
	return szRet;
#endif
}

void MarketInfoManager::Write_GG(YF_stRecordHKStock* pstRecordFXStock,CMainFrameSend* pMain)
{
#ifdef HS_SUPPORT_UNIX
#else

	/*
	繁体---->简体

	char Dest[256] = "";
	CString strIn = "東億";
	LCMapString(0x0804,LCMAP_SIMPLIFIED_CHINESE,  strIn,   -1,   Dest,   strIn.GetLength() * 2);
	CString   rt;
	rt.Format("%s",Dest);
	*/

	CString strDispName;
	if( g_sysSysConfigSend.nEntry_Support_Name )
	{
		strDispName = pstRecordFXStock->GetAutoName();
		if( strlen(strDispName) <= 0 || strDispName.IsEmpty() )
			return;
	}

	CString strCode = pstRecordFXStock->GetCode();

	void* str;
	if( m_mapNotFindCode.Lookup(strCode,str) )
		return;

	if( strCode.Find(".") != -1 ) // 代码包含小数点
		return;
	else if( strCode.GetLength() > 0 && YlsIsalpha(strCode.GetAt(0)) )
	{
	}
	else
	{
		int nCode = atol(strCode);
		if( nCode > 100000 )
			return;
		if( nCode <= 0 )
			return;
	}

	CString strDispCode = pstRecordFXStock->GetCode();

	if( !(g_sysSysConfigSend.nEntry_Support_JJT || g_sysSysConfigSend.nEntry_Support_CAIHUAGANGGU ) &&
		strlen(strDispCode) >= 5 )
		strDispCode = strDispCode.Mid(1);

	strDispName.Trim();
	strDispCode.Trim();

	char szRet[256];
	memset(szRet,0,sizeof(szRet));

	char strValue[256];
	memset(strValue,0,sizeof(strValue));

	char szGG[256];
	memset(szGG,0,sizeof(szGG));

	sprintf(strValue," %s, %s, 0, %s, %i",
		strCode,
		strDispName,
		GetMarketCode_GG(pstRecordFXStock,strDispCode,szGG),
		pstRecordFXStock->GetInstrumentType()/*,szRet*/);

	//
	int nType = pstRecordFXStock->GetInstrumentType();
	if( strCode[0] == '8' && strlen(strCode) >= 4 )
	{
		nType = 12;
		pstRecordFXStock->InstrumentType[0] = '1';
		pstRecordFXStock->InstrumentType[1] = '2';
	}
	else if( nType <= 0 )
	{
		nType = 5;
		pstRecordFXStock->InstrumentType[0] = '0';
		pstRecordFXStock->InstrumentType[1] = '5';
	}
	strDispCode.Format("%02i",nType);

	// 写入到文件
	MarketInfo_send* pMarketInfo = GetMarketByInclude(strDispCode);
	WriteCodeTo(pMarketInfo,strCode,strValue,pMain,
		strDispName,szGG,&nType);				
#endif

}

MarketInfo_send* MarketInfoManager::GetMarketPtr_GG( YF_stRecordHKStock* pstRecordFXStock,
													CHSStockPosition_send*& pPosition,
												CMainFrameSend* pMain /*= NULL*/)
{
#ifdef HS_SUPPORT_UNIX
	return NULL;
#else

	pPosition = NULL;
	if( pstRecordFXStock == NULL )
		return NULL;

	CString strCode = pstRecordFXStock->GetCode();
	MarketInfo_send* pMarketInfo = GetMarket(strCode,pPosition);

	Write_GG(pstRecordFXStock,pMain);

	return pMarketInfo;
#endif
}


void MarketInfoManager::AllAutoInitData(CMainFrameSend* pMain,CYlsTime& tmNow,
										int nSend /*= 1*/,
										int nForce /*= 0*/)
{
	if( pMain == NULL )
		return;

	MarketInfo_send* pMarketInfo;

	for( int i = 0; i < m_ay.GetSize(); i++ )
	{
		pMarketInfo = m_ay.GetAt(i);
		if( pMarketInfo == NULL )
			continue;

		pMain->AutoInitData(pMarketInfo,tmNow,nSend,nForce);
	}
}

void MarketInfoManager::SetCodeFile(const char* szPath)
{	
	MarketInfo_send* pMarketInfo;

	for( int i = 0; i < m_ay.GetSize(); i++ )
	{
		pMarketInfo = m_ay.GetAt(i);
		if( pMarketInfo == NULL )
			continue;

		pMarketInfo->SetCodeFile(szPath);
	}
}
