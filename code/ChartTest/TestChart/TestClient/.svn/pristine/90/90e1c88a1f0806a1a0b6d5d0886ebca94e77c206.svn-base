/*******************************************************************************
* Copyright (c)2003, 南阳油田讯捷软件有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：
* 作    者：
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/




#include "stdafx.h"
#include "info.h"
#include "globalfun.h"
//#include "hssortdata.h"



CYlsTypedPtrMap<CYlsMapStringToPtr,const char*,ZiXunRunTime_Ex*> ZiXunRunTime_Ex::m_mapInfoEx;

ZiXunRunTime_Ex::ZiXunRunTime_Ex()
{

}

ZiXunRunTime_Ex::ZiXunRunTime_Ex(const char* szIndexFileName,const char* szIndexPath,const char* szDataPath)
{
	GetZiXunBasePath(m_szIndexFileName);

	strncpy(m_szDataPath,m_szIndexFileName,sizeof(m_szDataPath));
	//strcat(m_szDataPath,szDataPath);
	//strcat(m_szDataPath,"\\");
	CreatPath(m_szDataPath);

	memset(m_szRelativelyDataPath,0,sizeof(m_szRelativelyDataPath));
	strcpy(m_szRelativelyDataPath,szDataPath);

	strcat(m_szIndexFileName,szIndexPath);
	strcat(m_szIndexFileName,"\\");

	CreatPath(m_szIndexFileName);

	strncat(m_szIndexFileName,szIndexFileName,sizeof(m_szIndexFileName));

	m_nPreDataPos = 0;

	//
	memset(m_szFlag,0,sizeof(m_szFlag));
	strcpy(m_szFlag,"NewsSend");
}

ZiXunRunTime_Ex::~ZiXunRunTime_Ex()
{
	Empty();
	_delArrayObj(m_ayIdx);
	_delArrayObj(m_ayContent);
}

void ZiXunRunTime_Ex::Init(CString strList)
{
	CString str;
	CStringArray ayRet;
	int nCount = AnalyzeStr(strList,";",ayRet);
	for( int i = 0; i < nCount; i++ )
	{
		str = ayRet.GetAt(i);
		if(str.IsEmpty() )
			continue;

		ZiXunRunTime_Ex* pZiXunRunTime;
		if( !ZiXunRunTime_Ex::m_mapInfoEx.Lookup(str,pZiXunRunTime) )
		{
			pZiXunRunTime = new ZiXunRunTime_Ex(str + ".idx",str,str);
			ZiXunRunTime_Ex::m_mapInfoEx.SetAt(str,pZiXunRunTime);
		}
	}
}

void ZiXunRunTime_Ex::Refresh(int nMask)
{
	char* key;
	ZiXunRunTime_Ex* value;
	POSITION  pos;
	for( pos = ZiXunRunTime_Ex::m_mapInfoEx.GetStartPosition(); pos != NULL; )
	{
		ZiXunRunTime_Ex::m_mapInfoEx.GetNextAssoc( pos, (const char* &)key, value );
		if( value )
		{
			value->ReadIndex();
		}
	}
}

bool ZiXunRunTime_Ex::MakeIndexListData(char* pszType, CHqDataBuffer* pBuffer)
{

	ZiXunRunTime_Ex* pZiXunRunTime;
	if (ZiXunRunTime_Ex::m_mapInfoEx.Lookup(pszType,pZiXunRunTime) )
	{
		if (pBuffer->Alloc(pZiXunRunTime->m_ayIdx.GetSize() * sizeof(InfoIndex_Ex)))
		{
			for (int i = 0; i < pZiXunRunTime->m_ayIdx.GetSize(); i ++)
			{
				memcpy(pBuffer->m_lpszBuffer + (i * sizeof(InfoIndex_Ex)), pZiXunRunTime->m_ayIdx[i], sizeof(InfoIndex_Ex));			
			}
			return true;
		}
	}
	return false;
}

bool ZiXunRunTime_Ex::MakeContentData(char* pszType, char* pszTitle, CHqDataBuffer* pBuffer)
{
	ZiXunRunTime_Ex* pZiXunRunTime;
	if (ZiXunRunTime_Ex::m_mapInfoEx.Lookup(pszType,pZiXunRunTime) )
	{
		if (pBuffer->Alloc(pZiXunRunTime->m_ayIdx.GetSize() * sizeof(InfoIndex_Ex)))
		{
			InfoIndex_Ex* pInfoIndex;
			for (int i = 0; i < pZiXunRunTime->m_ayIdx.GetSize(); i ++)
			{
				pInfoIndex = (InfoIndex_Ex*) pZiXunRunTime->m_ayIdx[i];
				if (!strncmp(pszTitle, pInfoIndex->GetTitle(), strlen(pszTitle)))
				{
					if (pBuffer->Alloc(pZiXunRunTime->m_ayContent[i]->m_cbBuffer))
					{
						pBuffer->Copy(pZiXunRunTime->m_ayContent[i]);
						return true;
					}					
				}		
			}
		}
	}
	return false;
}

InfoIndex_Ex* ZiXunRunTime_Ex::FindIndex(char* pszTitle)
{
	InfoIndex_Ex* pInfoIndex = NULL;
	for (int i = 0; i < m_ayIdx.GetSize(); i ++)
	{
		pInfoIndex = (InfoIndex_Ex*) m_ayIdx[i];
		if (!strcmp(pInfoIndex->GetTitle(), pszTitle))
		{
			return pInfoIndex;
		}		
	}
	return NULL;
}

void ZiXunRunTime_Ex::EmptyAll(int nMask)
{
	char* key;
	ZiXunRunTime_Ex* value;
	POSITION  pos;
	for( pos = ZiXunRunTime_Ex::m_mapInfoEx.GetStartPosition(); pos != NULL; )
	{
		ZiXunRunTime_Ex::m_mapInfoEx.GetNextAssoc( pos, (const char* &)key, value );
		if( value )
		{
			value->Empty();
		}
	}
}

// 待实现
void ZiXunRunTime_Ex::AddDataTo(ReqInfoSend* pReqInfoSend)
{

}

void ZiXunRunTime_Ex::AddDataTo(CString strList,
							 InfoIndex_Ex* pInfo,char* pGroup,int nGroupLen,char* pText,int nLen)
{
	CString str;
	CStringArray ayRet;
	int nCount = AnalyzeStr(strList,"\r\n",ayRet);
	for( int i = 0; i < nCount; i++ )
	{
		str = ayRet.GetAt(i);
		if(str.IsEmpty() )
			continue;

		ZiXunRunTime_Ex* pZiXunRunTime;
		if( !ZiXunRunTime_Ex::m_mapInfoEx.Lookup(str,pZiXunRunTime) )
		{
			pZiXunRunTime = new ZiXunRunTime_Ex(str,str,str);
			ZiXunRunTime_Ex::m_mapInfoEx.SetAt(str,pZiXunRunTime);
		}
		pZiXunRunTime->Write(pInfo,pGroup,nGroupLen,pText,nLen);
	}
}

void ZiXunRunTime_Ex::Empty()
{
	_delArrayObj(m_ay)
}

int ZiXunRunTime_Ex::ReadIndex()
{
	Empty();

	CFile szFile;
	if( !szFile.Open( m_szIndexFileName, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone) )
	{
		m_nPreDataPos = 0;
		return 0;
	}

	long lSize = szFile.GetLength();
	if( lSize <= 0 )
	{
		m_nPreDataPos = 0;
		szFile.Close();
		return 0;
	}

	if ( m_nPreDataPos == lSize )
	{
		szFile.Close();
		return 0;
	}// added 20110915
	else if(m_nPreDataPos > lSize)
	{
		m_nPreDataPos = 0;
		Empty();
		_delArrayObj(m_ayIdx);
		_delArrayObj(m_ayContent);
	}
	// end add

	int nLen = lSize - m_nPreDataPos;
	if( m_nPreDataPos <= 0 )
	{
	//	nLen -= 16; // head
	//	m_nPreDataPos = 16;
	}
	if( nLen <= 0 )
	{
		szFile.Close();
		return 0;
	}

	int nRecord = nLen / sizeof(InfoIndex_Ex);

	if( nRecord <= 0 || (nLen % sizeof(InfoIndex_Ex)) != 0 )
	{
		szFile.Close();
		return 0;
	}

	char* pData = new char[nLen];

	szFile.Seek( m_nPreDataPos, CFile::begin );
	szFile.Read( pData, nLen );	
	szFile.Close();

	m_nPreDataPos = lSize;
	//m_nPreDataPos += 16;

	// modified 20110824
//	char szDate[16];
//	CYlsTime tm = CYlsTime::GetCurrentTime();
//	sprintf(szDate,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());
//	long lDate = atol(szDate);
	// end mod

	//
	InfoIndex_Ex* pInfoIndex = (InfoIndex_Ex*)(pData);//(pData + ((m_nPreDataPos <= 0)?16:0));
	InfoIndex_Ex* pInfo = NULL;
	CHqDataBuffer* pBuffer;
	for( int i = 0; i < nRecord; i++, pInfoIndex ++ )
	{
		// modified 20110824
		//if( lDate != pInfoIndex->m_lDate )	 // 不是当天的，不做处理！
		//	continue;
		// end mod

		/*pBuffer = new CHqDataBuffer;
		if( MakeData(pBuffer,pInfoIndex) )
		{
			m_ay.Add(pBuffer);
		}
		else
		{
			delete pBuffer;
		}*/

		// 过滤重复资讯
		if (NULL != FindIndex(pInfoIndex->m_cTitle))
			continue;
		
		if (g_sScrollSend.g_szNoticeText)
			delete g_sScrollSend.g_szNoticeText;
		g_sScrollSend.g_szNoticeText = NULL;
		g_sScrollSend.g_nOldNoticeTextLen = g_sScrollSend.g_nNewNoticeTextLen;
		g_sScrollSend.g_nNewNoticeTextLen = 0;

		
		g_sScrollSend.g_szNoticeText = new unsigned char[strlen(pInfoIndex->m_cTitle) + 1];
		if (g_sScrollSend.g_szNoticeText != NULL)
		{			
			g_sScrollSend.g_nNewNoticeTextLen = strlen(pInfoIndex->m_cTitle);
			memset(g_sScrollSend.g_szNoticeText,0, g_sScrollSend.g_nNewNoticeTextLen);
			g_sScrollSend.g_bSendNoticeText = TRUE;
			strcpy((char*)g_sScrollSend.g_szNoticeText, pInfoIndex->m_cTitle);
		}

		pInfo = new InfoIndex_Ex;
		pBuffer = new CHqDataBuffer;
		if (NULL != pInfo && NULL != pInfoIndex->ReadContent(pBuffer))
		{
			memcpy(pInfo, pInfoIndex, sizeof(InfoIndex_Ex));
			m_ayIdx.Add(pInfo);
			m_ayContent.Add(pBuffer);

			// 保存不超过最大条数
			if (m_ayIdx.GetCount() > g_lInfoMaxCount)
			{
				InfoIndex_Ex* pIndex = (InfoIndex_Ex*)m_ayIdx[0];
				delete pIndex;
				m_ayIdx.RemoveAt(0);
			}
			if (m_ayContent.GetCount() > g_lInfoMaxCount)
			{
				CHqDataBuffer* phqBuf = (CHqDataBuffer*)m_ayContent[0];
				phqBuf->Free();
				delete phqBuf;
				m_ayContent.RemoveAt(0);
			}
		}
		else
		{
			delete pBuffer;
		}
		pInfo = pInfoIndex;
	}	

	pBuffer = new CHqDataBuffer;
	if (pBuffer->Alloc(nLen))
	{
		pBuffer->CopyData(pData, nLen);

		m_ay.Add(pBuffer);  // 将最新资讯存入数组用于推送
	}
	else
		delete pBuffer;


	delete [] pData;

	return m_ay.GetSize();
}

BOOL ZiXunRunTime_Ex::MakeData(CHqDataBuffer* pBuffer,InfoIndex_Ex* pInfoIndex)
{
	if( pBuffer == NULL || pInfoIndex == NULL )
		return FALSE;

	long lLen = sizeof(AnsPushRealtimeInfo);	

	AutoFreeIndexData data;
	//pInfoIndex->m_cType = 0; // 设置为内容方式
	if( pInfoIndex->m_cType == 0 )
	{
		if( pInfoIndex->ReadData(&data) == NULL )
			return 0;
	}
	else
	{
		data.Alloc(sizeof(pInfoIndex->m_cFilePath));

		strncpy(data.m_pData,pInfoIndex->m_cFilePath,data.m_lSize);
	}

	int lHis = data.m_lSize;

	if( !pBuffer->Alloc(lLen+lHis) )
		return FALSE;

	AnsPushRealtimeInfo* pAnsPushRealtimeInfo = (AnsPushRealtimeInfo*)pBuffer->m_lpszBuffer;
	pAnsPushRealtimeInfo->m_dhHead.m_nType = RT_PUSHREALTIMEINFO;
	pAnsPushRealtimeInfo->m_nSize = 1;
	pAnsPushRealtimeInfo->m_nMyTypeID = pInfoIndex->m_cGroup;

	PushRealtimeInfoItem* pPushRealtimeInfoItem = pAnsPushRealtimeInfo->m_pData;
	strncpy(pPushRealtimeInfoItem->m_cTitle,pInfoIndex->m_cTitle,sizeof(pPushRealtimeInfoItem->m_cTitle));
	pPushRealtimeInfoItem->m_lDate = pInfoIndex->m_lDate;
	pPushRealtimeInfoItem->m_lTime = pInfoIndex->m_lTime;
	pPushRealtimeInfoItem->m_nDataType = pInfoIndex->m_cType;
	pPushRealtimeInfoItem->m_nDataSize = lHis;
	memcpy(pPushRealtimeInfoItem->m_cData,data.m_pData,pPushRealtimeInfoItem->m_nDataSize);

	return TRUE;
}

int ZiXunRunTime_Ex::Write(InfoIndex_Ex* pInfo,char* pGroup,int nGroupLen,char* pText,int nLen)
{
	CFile szFile;
	if( !szFile.Open( m_szIndexFileName, CFile::modeWrite | CFile::typeBinary | CFile::shareDenyNone) )
	{
		if( !szFile.Open( m_szIndexFileName, 
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::shareDenyNone) )
		{
			return 0;
		}
	}

	int nFileLen = szFile.GetLength();
	if( nFileLen <= 0 )
	{
		szFile.Write(m_szFlag,sizeof(m_szFlag));
	}
	szFile.SeekToEnd();

	CYlsTime tm = CYlsTime::GetCurrentTime();
	pInfo->m_cType = 1;
	sprintf(pInfo->m_cFilePath,"%s\\%04d%02d%02d-%02d%02d%02d.run",
		m_szRelativelyDataPath,
		tm.GetYear(),tm.GetMonth(),
		tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());

	char szData[100];
	sprintf(szData,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());
	pInfo->m_lDate = atol(szData);
	sprintf(szData,"%04d%02d%02d",tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	pInfo->m_lTime = atol(szData);

	szFile.Write(pInfo,sizeof(*pInfo));
	szFile.Close();

	if( nLen <= 0 || pText == NULL )
		return 1;

	char szFileName[_MAX_PATH];
	strncpy(szFileName,m_szDataPath,sizeof(szFileName));
	//GetZiXunBasePath(szFileName);	
	strncat(szFileName,pInfo->m_cFilePath,sizeof(szFileName));

	if( !szFile.Open( szFileName, 
		CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::shareDenyNone) )
		return 0;
	szFile.Write(pText,nLen);
	szFile.Close();

	return 1;
}

char* InfoIndex_Ex::ReadData(AutoFreeIndexData* pCurData)
{
	if( pCurData == NULL )
		return NULL;

	char strFileName[_MAX_PATH];
	strFileName[0] = '\0';

	GetPath(strFileName);
	
	CFile szFile;
	if( !szFile.Open( m_cFilePath/*strFileName*/, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone) )
		return NULL;

	long lSize = szFile.GetLength();
	if( lSize <= 0 )
		return NULL;
	
	if( m_lLength <= 0 )
	{
		pCurData->Alloc(lSize + 1);
		if( !pCurData->IsValid() )
		{
			szFile.Close();
			return NULL;
		}

		szFile.Read( pCurData->m_pData, lSize );
		szFile.Close();
		pCurData->m_pData[lSize] = '\0';

		return pCurData->m_pData;
	}

	if( lSize < (m_lOffset + m_lLength) )
	{
		szFile.Close();
		return NULL;
	}

	pCurData->Alloc(m_lLength + 1);
	if( !pCurData->IsValid() )
	{
		szFile.Close();
		return NULL;
	}

	szFile.Seek( m_lOffset, CFile::begin );
	szFile.Read( pCurData->m_pData, m_lLength );	
	szFile.Close();

	pCurData->m_pData[m_lLength] = '\0';

	return pCurData->m_pData;
}

char* InfoIndex_Ex::ReadContent(CHqDataBuffer* pBuffer)
{
	if( pBuffer == NULL )
		return NULL;

	char strFileName[_MAX_PATH];
	strFileName[0] = '\0';

	GetPath(strFileName);
	CFile szFile;
	if (szFile.Open( m_cFilePath, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone) )
	{
		try
		{	

			long lSize = szFile.GetLength();
			if ((lSize - m_lOffset)  >= m_lLength)
			{
				pBuffer->Alloc(m_lLength + 1);
				if (pBuffer->IsValid() )
				{
					szFile.Seek(m_lOffset, SEEK_CUR);
					szFile.Read(pBuffer->m_lpszBuffer, m_lLength);
					szFile.Close();
					pBuffer->m_lpszBuffer[m_lLength] = '\0';
					return pBuffer->m_lpszBuffer;
				}
			}

		}
		catch (...)
		{
			szFile.Close();
			return NULL;
		}
	}
	szFile.Close();
	return NULL;
}

void InfoIndex_Ex::GetPath(char* strFileName)
{
	GetZiXunBasePath(strFileName);
	strcat(strFileName,m_cFilePath);
}
