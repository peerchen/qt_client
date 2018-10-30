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

#include "stdafx.h"
#include "tool.h"
#include "ylsfile.h"
#include "hsserverdatapath.h"
#include "ylstime.h"

#include "globalfun.h"

#include "sharedmemory.h"


#ifndef HS_SUPPORT_UNIX

#include <stdio.h>
#include <io.h>
#include <sys/stat.h>
#include "dos.h"

#include "..\..\Share_2005\DogManager\OutProcessManager.h"


#endif

#define User_MapFind	 // 匹配在map中进行，只对于dfx

int StartShareMemoryProcess()
{
#ifndef HS_SUPPORT_UNIX
	CString strCmd = YlsGetCurrentExeBasePath();
	strCmd += "HsMemory.exe";

	char strCfgfileName[256];
	sprintf(strCfgfileName,"/%s",g_strCfgfileName);

	CString strDir;
	CProcessMgr mgr;

	int nRet = -1;//mgr.Execute(strCmd, strCfgfileName, strDir, FALSE);
	
	int hHinstance = 0;
	if( nRet == -1 )
		hHinstance = (int)ShellExecute(NULL, NULL,strCmd, strCfgfileName, NULL, SW_HIDE);
	if( nRet != -1 || hHinstance > 32 )
	{
		//Sleep(1000);

		CSharedMemory* pMemory_stockCount = new CSharedMemory(); // 共享参数
		HsShareStockCount* pData = NULL;

		int nCount = 60*10;
		while(nCount--)
		{
			if( pData == NULL )
			{
				pMemory_stockCount->Init(HsShareMemManagerStockCounts,
					sizeof(HsShareStockCount),ERROR_ALREADY_EXISTS);
				pData = (HsShareStockCount*)pMemory_stockCount->GetData();
			}

			if( pData != NULL )
			{
				if( (pData->m_nMarkInfo | HsShareStockCount_InitEnd)  )
				{
					delete pMemory_stockCount;
					return 1;
				}
			}

			Sleep(1000);			
		}

		delete pMemory_stockCount;

	}
	else
	{
		AfxMessageBox("共享进程不存在或启动不了!");
	}
#else

#endif
	//Sleep(1000);

	return 0;
}

void* IsHaveShareMemoryProcess(CSharedMemory* pMemory_stockCount)
{
	if( pMemory_stockCount == NULL )
		return 0;

	//pMemory_stockCount = new CSharedMemory(); // 共享参数
	HsShareStockCount* pData = NULL;

	pMemory_stockCount->Init(HsShareMemManagerStockCounts,sizeof(HsShareStockCount),ERROR_ALREADY_EXISTS);
	pData = (HsShareStockCount*)pMemory_stockCount->GetData();

	if( pData != NULL )
	{
		if( (pData->m_nMarkInfo | HsShareStockCount_InitEnd)  )
		{
			return pData;			
		}
	}

	return NULL;
}

// 返回股票代码
LPCTSTR YlsGetKey(char* strKey,CodeInfo* pCode) // strKey > 9
{
	strncpy(strKey,pCode->m_cCode,STOCK_CODE_SIZE);
	strKey[STOCK_CODE_SIZE] = '\0';

	return strKey;
}

void ConvertStock(StockUserInfo* pStock,StockInitInfo* pStockInfo)
{
	memcpy(&pStock->m_ciStockCode,&pStockInfo->m_ciStockCode,sizeof(pStock->m_ciStockCode));		//股票代码结构
	strncpy(pStock->m_cStockName,pStockInfo->m_cStockName,sizeof(pStock->m_cStockName));	//股票名称
	pStock->m_lPrevClose = pStockInfo->m_lPrevClose;		//昨收
	pStock->m_l5DayVol = pStockInfo->m_l5DayVol;			//五日量
}

int Usleep( unsigned int iUsTimeout )
{
	struct timeval tv;

	tv.tv_sec       = iUsTimeout / 1000000;
	tv.tv_usec      = iUsTimeout % 1000000;

	return select( 0,NULL,NULL,NULL,&tv );
}


//// 返回股票代码
//LPCTSTR YlsGetKey(CodeInfo* pCode)
//{
//	if( pCode == NULL )
//		return NULL;
//
//	static char strKey[7];
//	strncpy(strKey,pCode->m_cCode,6);
//	strKey[6] = '\0';
//
//	return strKey;
//}

char* UnionFileName(char* strFile,int nLen,const char* szPath,const char* szCode,const char* szExt)
{
	memset(strFile,0,nLen);
			
	snprintf(strFile, nLen - 1, "%s%s%s", szPath, szCode, szExt);

	//strncpy(strFile,szPath,nLen);
	//strcat(strFile,szCode);
	//strcat(strFile,szExt);

	return strFile;
}

int Yls_mkdir(const char* szPath)
{
#ifndef HS_SUPPORT_UNIX
	return mkdir(szPath);
#else
	return mkdir(szPath,0755);
#endif
}

long GetFileNameCRC(const char* strFileName)
{
	struct stat stBuff;
	if( stat(strFileName, &stBuff) == 0 )
		return stBuff.st_mtime;

	return 0;
}

unsigned long GetFileNameCreateTime(const char* strFileName)
{
	struct stat stBuff;
	if( stat(strFileName, &stBuff) == 0 )
	{
		return stBuff.st_mtime;//stBuff.st_ctime;
	}

	return 0;
}

long GetFileNameStat(struct stat& stBuff,const char* strFileName)
{
	if( stat(strFileName, &stBuff) == 0 )
	{
		return stBuff.st_size;
	}

	return 0;
}

long YlsGetFileAttributes(const char* strFileName)
{
	if( strFileName == NULL )
		return 0;

#ifndef HS_SUPPORT_UNIX
	return GetFileAttributes(strFileName);
#else
	struct stat stBuff;
	if( GetFileNameStat(stBuff,strFileName) )
	{
		return stBuff.st_mode;
	}
#endif

	return 0;
}

long YlsGetFullPathName(char* lpFileName,unsigned long nBufferLength,char* lpBuffer,char** lpFilePart)
{
#ifndef HS_SUPPORT_UNIX
	return GetFullPathName(lpFileName,nBufferLength,lpBuffer,lpFilePart);
#else
	char path[_MAX_PATH];
	YlsSplitpath(lpFileName,NULL,path,NULL,NULL);
	strncpy(lpBuffer,path,_MAX_PATH);
	return 1;
#endif
	return 0;
}

long GetFileNameLength(const char* strFileName)
{
	if( access(strFileName,0) != 0 )
		return 0;

	struct stat stBuff;
	if( stat(strFileName, &stBuff) == 0 )
	{
		return stBuff.st_size;
	}
	return 0;
}

void YlsSplitFileName( const char *szFileName,char *fname, char *ext )
{
	if( fname )
		memset(fname,0,_MAX_FNAME);
	if( ext )
		memset(ext,0,_MAX_EXT);

	int nCount = strlen(szFileName);
	for(int i = nCount-1; i >= 0; i--)
	{
		if( szFileName[i] == '.' )
		{
			if( ext && i < nCount )
			{
				strncpy(ext,&szFileName[i],nCount - i);
			}
			if( fname )
			{
				strncpy(fname,szFileName,i);
			}
			return;
		}
	}

	if( fname )
	{
		strncpy(fname,szFileName,_MAX_FNAME);
	}
}

void YlsSleep(DWORD lTime)
{
#ifdef HS_SUPPORT_UNIX
	Usleep(lTime*1000);
#else
	Sleep(lTime);
#endif
}

void YlsReplace( char* szData, char chOld, char chNew  )
{
	if( szData == NULL )
		return;

	int nLen = strlen(szData);
	for(int i = 0; i < nLen; i++,szData++ )
	{
		if( *szData == chOld )
			*szData = chNew;
	}
}

char* YlsReplaceStr( CHqDataBuffer& oldBuffer,const char* szFind,const char* szData,int nLen)
{
	if( szFind == NULL || szData == NULL || nLen <= 0 )
		return NULL;

	CHqDataBuffer saveBuffer;
	saveBuffer.Copy(&oldBuffer);

	CHqDataBuffer findBuffer;
	findBuffer.CopyStr(szFind);

	findBuffer.MakeLower();
	oldBuffer.MakeLower();

	int nIndex = oldBuffer.Find(findBuffer.m_lpszBuffer);
	if( nIndex != -1 )	 // 找到
	{
		CHqDataBuffer left,right;
		saveBuffer.Left(nIndex,left);
		saveBuffer.Mid(nIndex + strlen(findBuffer.m_lpszBuffer),right);

		oldBuffer.Free();
		oldBuffer.AddStr(left.m_lpszBuffer);
		oldBuffer.AddStr(szData,nLen);
		oldBuffer.AddStr(right.m_lpszBuffer);
	}
	else  // 没有找到
	{
		oldBuffer.Copy(&saveBuffer);
	}

	return oldBuffer.m_lpszBuffer;
}

char* UnionPath(char* strPath,const char* szFile)
{
	if( strlen(szFile) > 0 && szFile[0] == Yls_Path_Spl_Char )
	{
		int nLen = strlen(strPath);
		if( nLen > 0 && strPath[nLen - 1] == Yls_Path_Spl_Char )
		{
			strPath[nLen - 1] = '\0';
		}
	}
	strcat(strPath,szFile);

	return strPath;
}

void YlsSplitpath( const char *path, char *drive, char *dir, char *fname, char *ext )
{
#ifndef HS_SUPPORT_UNIX
	_splitpath(path, drive, dir, fname, ext);
#else

	// 替换
	YlsReplace((char*)path,'\\','/');

	// 分解文件和扩展名称
	char szFileName[_MAX_PATH];
	sprintf(szFileName,"%s",basename((char*)path));
	YlsSplitFileName(szFileName,fname,ext);	

	if( dir )  // 目录
	{
		char szCur[_MAX_PATH];
		memset(szCur,0,sizeof(szCur));

		int nLen = strlen(path);
		if( nLen > 2 && path[1] == ':' )  // 去除驱动器
		{
			strncpy(szCur,&path[2],sizeof(szCur));			
		}
		else
		{
			strncpy(szCur,path,sizeof(szCur));
		}
		sprintf(dir,"%s",dirname((char*)szCur));
	}

#endif
}

void  YlsPrompt(const char* strName,const char* strText)
{	
//#ifdef HS_SUPPORT_UNIX

	if( strName )
	{
		printf(strName);
	}
	if( strText )
	{
		printf(":");
		printf(strText);
		printf("\r\n");
	}

	CHqDataBuffer buffer;
	if( strName )
		buffer.AddStr(strName,strlen(strName));
	if( strText )
	{
		buffer.AddStr("\t");
		buffer.AddStr(strText,strlen(strText));
	}

	if( buffer.IsValid() )
		WriteError(buffer.m_lpszBuffer,buffer.m_cbBuffer,NULL);
//#endif

}

void WriteDataByFile(const char* pData,int nLen,CYlsFile* fp,
					 const char* strDelimit /*= ","*/,
					 int nMask /*= 1*/)
{
	if( fp == NULL || fp->m_hFile == INVALID_HANDLE_VALUE )
		return;

	if( strDelimit )
		fp->Write(strDelimit,strlen(strDelimit));
	if( pData != NULL && nLen > 0 )
	{
		if( nMask == 1 )
			fp->Write(&nLen,sizeof(nLen));

		fp->Write(pData,nLen);
	}
}

void WriteCommData(void *pRequest, int nLen)
{
	WriteError(pRequest, nLen, g_strCommDataFile);
}

#ifdef HS_SUPPORT_UNIX
void WriteError(void *pRequest, int nLen,char* pFileName)
{
	if( pFileName == NULL )
		pFileName = g_strErrorFileName;
	
	CYlsTime tm = CYlsTime::GetCurrentTime();
	char strFilePath[_MAX_PATH];
	//sprintf(strFilePath,"%s.%02d",pFileName,tm.GetDayOfWeek());
	sprintf(strFilePath,"%s",pFileName);

	CYlsFile fp;
	if( pRequest == NULL || nLen <= 0 )	 // empty
	{
		if( fp.Open( strFilePath,Yls_Create_Empty_Open ) )
			fp.Close();
		return;
	}

	if( fp.Open( strFilePath,Yls_Create_Open ) )
	{
		static int nSize = 1024*1024*150; // 150m
		if( fp.GetLength() > nSize )
		{
			fp.Close();
			if( !fp.Open( strFilePath,Yls_Create_Empty_Open ) )
				return;
		}

		fp.SeekToEnd();

		char strTime[_MAX_PATH];
		memset(strTime,0,sizeof(strTime));
		sprintf(strTime,"[%04d-%02d-%02d %02d:%02d:%02d] ",
			tm.GetYear(),tm.GetMonth(),tm.GetDay(),
			tm.GetHour(), tm.GetMinute(), tm.GetSecond());

		CHqDataBuffer buffer;
		buffer.AddStr(strTime,strlen(strTime));
		buffer.AddStr((char*)pRequest,nLen);

		// 是否有回车换行
		if( nLen > 2 )
		{
			char* pp = (char*)pRequest;
			if( pp[nLen-2] != '\r' && pp[nLen-1] != '\n' )
			{
				buffer.AddStr("\r\n");
			}
		}

		fp.Write(buffer.m_lpszBuffer,buffer.m_cbBuffer);

		fp.Close();
	}

}
#else
void WriteError(void *pRequest, int nLen,char* szFileName)
{
	if( pRequest == NULL || nLen <= 0 )
		return;

	char szPath[_MAX_PATH];
	char strFileName[_MAX_PATH];
	sprintf(strFileName,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),"log.dat");	

	CFile fp;
	if( fp.Open(strFileName,Yls_Create_NoTruncate_Open ))
	{
		static int nSize = 1024*1024*30; // 10m
		if( fp.GetLength() > nSize )
		{
			fp.SetLength(0);
		}

		fp.SeekToEnd();

		char strTime[_MAX_PATH];
		memset(strTime,0,sizeof(strTime));
		CYlsTime tm = CYlsTime::GetCurrentTime();
		sprintf(strTime,"[%04d-%02d-%02d %02d:%02d:%02d] \r\n",
			tm.GetYear(),tm.GetMonth(),tm.GetDay(),
			tm.GetHour(), tm.GetMinute(), tm.GetSecond());

		CHqDataBuffer buffer;
		buffer.AddStr((char*)pRequest,nLen);
		buffer.AddStr("\t");
		buffer.AddStr(strTime,strlen(strTime));
		
		fp.Write(buffer.m_lpszBuffer,buffer.m_cbBuffer);

		fp.Close();
	}
}
#endif

char* YlsMakeLower(const char* szSrc,CHqDataBuffer& buffer)
{
	char* pUser = strdup(szSrc);
	if( pUser )
	{		
		int nLen = strlen(pUser);
		for( int i = 0; i < nLen; i++ )
		{
			pUser[i] = tolower((int)pUser[i]);
		}

		if( buffer.Alloc(nLen) )
		{
			strncpy(buffer.m_lpszBuffer,pUser,buffer.m_cbBuffer);
		}
	}
	free(pUser);

	return buffer.m_lpszBuffer;
}

char* YlsMakeLower2(char* szSrc)
{
	CHqDataBuffer buffer;
	buffer.CopyStr(szSrc);

	if( buffer.IsValid() )
	{
		int nOld = strlen(szSrc);
		int nLen = buffer.GetLength();
		for( int i = 0; i < nLen && i < nOld; i++ )
		{
			szSrc[i] = tolower((int)buffer.m_lpszBuffer[i]);
		}
	}

	/*
	char* pUser = strdup(szSrc);
	if( pUser )
	{		
		int nLen = strlen(pUser);
		for( int i = 0; i < nLen; i++ )
		{
			szSrc[i] = tolower((int)pUser[i]);
		}
	}
	free(pUser);
	*/

	return szSrc;
}

char* YlsMakeUpper(char* szSrc)
{
	CHqDataBuffer buffer;
	buffer.CopyStr(szSrc);

	if( buffer.IsValid() )
	{
		int nOld = strlen(szSrc);
		int nLen = buffer.GetLength();
		for( int i = 0; i < nLen && i < nOld; i++ )
		{
			szSrc[i] = toupper((int)buffer.m_lpszBuffer[i]);
		}
	}

	/* 2007.09.03 replace
	char* pUser = strdup(szSrc);
	if( pUser )
	{		
		int nOld = strlen(szSrc);
		int nLen = strlen(pUser);
		for( int i = 0; i < nLen && i < nOld; i++ )
		{
			szSrc[i] = toupper((int)pUser[i]);
		}
	}
	free(pUser);
	*/

	return szSrc;
}

void YlsMakeUpperCode(CodeInfo* pCode)
{
	if( pCode == NULL )
		return;

	char strKey[STOCK_CODE_SIZE + 1];
	memset(strKey,0,sizeof(strKey));
	strncpy(strKey,pCode->m_cCode,STOCK_CODE_SIZE);

	YlsMakeUpper(strKey);

	strncpy(pCode->m_cCode,strKey,sizeof(pCode->m_cCode));
}

const char* YlsRTrim(const char* strSrc)
{
	int sLen = strlen(strSrc);
	if (sLen !=0 )
	{
		char* pstr = (char*)strSrc + sLen - 1;
		while(*pstr == ' ')  *pstr-- = '\0';
	}
	return strSrc;    
}

const char* YlsLTrim(const char* strSrc)
{
	if( *strSrc == '\0' )
	{
		return strSrc;
	}
	char* pHead = (char*)strSrc;
	char* pstr = (char*)strSrc;
	while(*(pstr++) == ' ');
	pstr--;
	if(strSrc != pstr)
	{
		int i = 0;
		for( ; *pstr != '\0'; i++,pstr++)
		{
			pHead[i] = *pstr;
		}
		pHead[i] = *pstr; 
	}
	return strSrc;
}


const char* YlsAllTrim(const char* strSrc)
{
	if( strSrc == NULL )
		return "";

	return YlsRTrim(YlsLTrim(strSrc));
}

char* _strncpy(char* string1, const char* string2, int nCount)
{
	int i = 0;
	for(i = nCount - 1; i >= 0; i--)
	{
		if(string2[i] != 0x20)
		{
			break;
		}
	}
	strncpy(string1, string2, i+1);
	string1[i+1] = '\0';
	return string1;
}

char* strcpyn(char* strDest, int nDest, const char* strSource, int nSource/* = -1*/, BOOL bTrim/* = FALSE*/)
{
	if(nSource < 0)
	{
		nSource = strlen(strSource);
	}
	int i = 0;
	for(i = nSource - 1; i >= 0; i--)
	{
		if(!isspace(strSource[i]) || (strSource[i] & 0x80) || !bTrim)
		{
			break;
		}
	}
	int nLen = min(i + 1, nDest);
	if(nLen > 0)
	{
		memcpy(strDest, strSource, nLen);
	}
	if(nLen < nDest)
	{
		strDest[nLen] = '\0';
	}
	return strDest;
}

double _atof(const char* str,int nLen/* = -1*/)
{
	char* pEnd;
	if(nLen <= -1)
	{
		nLen = strlen(str);
	}
	char Buff[32];
	memset(Buff, 0, sizeof(Buff));
	strcpyn(Buff, sizeof(Buff) - 1, str, nLen);
	YlsLTrim(Buff);
	return strtod(Buff, &pEnd);
}

unsigned long _atofNew(const char* str,int nUnit /*= 1*/,int nLen /*= -1*/)
{
	return (unsigned long)(_atof(str,nLen) * nUnit);
}

unsigned long ConvertStrToLong(const char* str,int nUnit /*= 1*/,int nLen /*= -1*/)
{
	CHqDataBuffer buffer;
	if( nLen <= -1 )
		nLen = strlen(str);

	buffer.CopyStr(str,nLen);

	if( !buffer.IsValid() )
		return 0;
 
	unsigned long nRet = 0;
	char* pdest = strstr(buffer.m_lpszBuffer,".");
	if( pdest && strlen(pdest) > 1 )
	{
		nRet = atol(&pdest[1]);
		pdest[0] = 0;
		nRet += atol(buffer.m_lpszBuffer) * nUnit;
	}
	else
	{
		nRet = atol(buffer.m_lpszBuffer) * nUnit;
	}

	return nRet;
}

long _atol(const char* str,int nLen/* = -1*/)
{
	char Buff[32];
	char* pEnd;
	if(nLen == -1)
	{
		nLen = strlen(str);
	}
	memset(Buff, 0, sizeof(Buff));
	strcpyn(Buff, sizeof(Buff) - 1, str, nLen);
	YlsLTrim(Buff);
	return strtol(Buff, &pEnd, 10);
}

int AnalyzeStr(const char* strResource,const char* strDelimit,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayRet)
{
	_delArrayObj(ayRet);

	if( strResource == NULL )
		return 0;

	CHqDataBuffer strSrc;
	strSrc.CopyStr(strResource);

	int nLen;
	CHqDataBuffer* tmp;
	char* token = strtok( (char*)strSrc.m_lpszBuffer, (char*)strDelimit);
	while(token != NULL)
	{
		nLen = strlen(token);
		if( nLen > 0 )
		{
			//nLen++; // 2007.08.23
			tmp = new CHqDataBuffer;
			if( tmp->Alloc(nLen) )
			{
				strncpy(tmp->m_lpszBuffer,token,nLen);//-1);
				ayRet.Add(tmp);
			}
		}
		token = strtok( NULL, (char*)strDelimit);
	}

	return ayRet.GetSize();
}

CHqDataBufferArray_Dfx::CHqDataBufferArray_Dfx()
{	
	m_nIsSend = 0;
}

CHqDataBufferArray_Dfx::~CHqDataBufferArray_Dfx()
{
	// 是共享内存，无需删除
	m_pSrcBuffer.m_lpszBuffer = NULL;
	m_pSrcBuffer.m_cbBuffer = 0;

	FreeMap();	
}

void CHqDataBufferArray_Dfx::FreeMap()
{
	CHqDataBuffer* value;
	const char* key;
	POSITION  pos;

	for( pos = m_map.GetStartPosition(); pos != NULL; )
	{
		m_map.GetNextAssoc( pos, key, (void*&)value );
		if( value )
		{
			delete value;
		}
	}

	m_map.RemoveAll();
}

int CHqDataBufferArray_Dfx::BuildMapByFile(const char* strFileName,const char* strDelimit)
{
	CHqDataBuffer buffer;
	if( !CServerMarketInfo::MyReadFile(strFileName,buffer) )
		return 0;

	return BuildMap(&buffer,strDelimit);
}

int CHqDataBufferArray_Dfx::SetItemValue_Dfx(CHqDataBuffer* pKey,CHqDataBuffer*& pValue)
{
#ifdef User_MapFind
	int* pCurValue = (int*)&m_sDfx_DataItem;

	int nPos;
	if( Dfx_DataItem::m_map.Lookup((void*)Dfx_DataItem::HashKey(pKey->m_lpszBuffer),(void*&)nPos) )
	{
		if( nPos >= 0 && nPos <= 17 )
		{
			if( pValue->IsValid() )
				pCurValue[nPos] = atol(pValue->m_lpszBuffer);
		}
		else
		{
			pCurValue[nPos] = (int)pValue;
			pValue = NULL;
		}
		return 1;
	}

	return 0;
#else
	if( !strncasecmp(pKey->m_lpszBuffer,"SRV",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_SRV = atol(pValue->m_lpszBuffer);

		return 1;
	}
	if( !strncasecmp(pKey->m_lpszBuffer,"MARKET",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
		{
			m_sDfx_DataItem.m_MARKET = atol(pValue->m_lpszBuffer);
			m_sDfx_DataItem.m_MARKET <<= 4;
		}

		return 1;
	}
	
	else if( !strncasecmp(pKey->m_lpszBuffer,"PCODE",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_PCODE = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"STEP",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_STEP = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"OFS",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_STEP = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"COMP",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_COMP = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"PACK",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_PACK = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"BS45",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_BS45 = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"CODE",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_CODE = atol(pValue->m_lpszBuffer);

		return 1;
	}

	else if( !strncasecmp(pKey->m_lpszBuffer,"CODES",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_CODES = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"FLAG",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_FLAG = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"CHANGED",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_CHANGED = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"MAP",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_MAP = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"TRANNUM",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_TRANNUM = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"GETNUM",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_GETNUM = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"OFSNUM",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_OFSNUM = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"DAYTYPE",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_DAYTYPE = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"GZLX",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_GZLX = atol(pValue->m_lpszBuffer);

		return 1;
	}	
	else if( !strncasecmp(pKey->m_lpszBuffer,"lastdate",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_DATE = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"DATE",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_DATE = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"CRC",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_CRC = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"POS",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_POS = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"LEN",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_LEN = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"KINDS",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_KINDS = atol(pValue->m_lpszBuffer);

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"BALL",pKey->m_cbBuffer) )
	{
		if( pValue->IsValid() )
			m_sDfx_DataItem.m_BALL = atol(pValue->m_lpszBuffer);

		return 1;
	}	
	
	else if( !strncasecmp(pKey->m_lpszBuffer,"HEADER",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_HEADER = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"ABS",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_ABS = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"FILE",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_FILE = pValue;
		pValue = NULL;

		return 1;
	}
	else if( !strncasecmp(pKey->m_lpszBuffer,"ZLIB",pKey->m_cbBuffer) )
	{
		m_sDfx_DataItem.m_ZLIB = pValue;
		pValue = NULL;

		return 1;
	}

	return 0;
#endif

}

char * Curl_strtok_r(char *ptr, const char *sep, char **end)
{
	if (!ptr)
		/* we got NULL input so then we get our last position instead */
		ptr = *end;

	/* pass all letters that are including in the separator string */
	while (*ptr && strchr(sep, *ptr))
		++ptr;

	if (*ptr)
	{
		/* so this is where the next piece of string starts */
		char *start = ptr;

		/* set the end pointer to the first byte after the start */
		*end = start + 1;

		/* scan through the string to find where it ends, it ends on a
		null byte or a character that exists in the separator string */
		while (**end && !strchr(sep, **end))
			++*end;

		if (**end) 
		{
			/* the end is not a null byte */
			**end = '\0';  /* zero terminate it! */
			++*end;        /* advance the last pointer to beyond the null byte */
		}

		return start; /* return the position where the string starts */
	}

	/* we ended up on a null byte, there are no more strings to find! */
	return NULL;
}


int AnalyzeStr_Dfx(CHqDataBuffer* buffer,
				   const char* strDelimit,
				   CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayRet)
{
	if( buffer == NULL || !buffer->IsValid() )
		return 0;

	char* strResource = buffer->m_lpszBuffer;

#if 0
	char* pEnd;
	CHqDataBuffer* tmp;

	char* token = Curl_strtok_r(strResource,strDelimit,&pEnd);
	while(token != NULL)
	{
		tmp = new CHqDataBuffer;
		tmp->CopyStr(token);
		ayRet.Add(tmp);

		token = Curl_strtok_r(pEnd,strDelimit,&pEnd);
	}
#endif

#if 1

	CHqDataBuffer* tmp;
	int nPos = 0;
	char* pPre = strResource;
	for(; nPos < buffer->m_cbBuffer; nPos++)
	{
		if( *strResource == *strDelimit )
		{
			*strResource = '\0';

			tmp = new CHqDataBuffer;
			tmp->CopyStr(pPre);
			//tmp->m_lpszBuffer = pPre;
			//tmp->m_lpszBuffer = strlen(pPre);
			ayRet.Add(tmp);

			strResource++;
			pPre = strResource;
		}
		else
		{
			strResource++;
		}
	}

	if( pPre )
	{
		tmp = new CHqDataBuffer;
		tmp->CopyStr(pPre);
		//tmp->m_lpszBuffer = pPre;
		//tmp->m_lpszBuffer = strlen(pPre);
		ayRet.Add(tmp);
	}
#endif


	//
	return ayRet.GetSize();
}

int CHqDataBufferArray_Dfx::BuildMap_DFX(CHqDataBuffer* strResource,const char* strDelimit)
{
	if( strResource == NULL || !strResource->IsValid() )
		return 0;

#ifdef User_MapFind
	strResource->MakeUpper();
#endif

	CHqDataBufferArray ayRet;
	int nCount = //AnalyzeStr(strResource->m_lpszBuffer,strDelimit,ayRet.ay);
		AnalyzeStr_Dfx(strResource,strDelimit,ayRet.ay);
	if( nCount <= 0 )
		return 0;

	int nItem;
	CHqDataBuffer* pBuffer;

	CHqDataBuffer* pKey;
	CHqDataBuffer* pValue;
	CHqDataBuffer* pTemp;

	for( int i = 0; i < nCount; i++ )
	{
		pBuffer = ayRet.ay.GetAt(i);
		if( pBuffer == NULL || pBuffer->IsEmpty() )
			continue;

		CHqDataBufferArray ayValue;
		nItem = //AnalyzeStr(pBuffer->m_lpszBuffer,"=",ayValue.ay);;
			AnalyzeStr_Dfx(pBuffer,"=",ayValue.ay);
		if( nItem < 2 )
			continue;

		pKey = ayValue.ay.GetAt(0);
		pValue = ayValue.ay.GetAt(1);

		if( pKey == NULL   || pKey->IsEmpty() ||
			pValue == NULL || pValue->IsEmpty() )
			continue;

		//pKey->Trim();
		if( !SetItemValue_Dfx(pKey,pValue) )
		{
#ifndef HS_SUPPORT_UNIX
			//AfxMessageBox("Failed!");
#endif
		}

		if( pValue == NULL )
		{
			ayValue.ay.RemoveAt(1);
		}

		//pKey->MakeUpper();		
		//pValue->MakeUpper();

		//if( !m_map.Lookup(pKey->m_lpszBuffer,(void*&)pTemp) )
		//{
		//	m_map.SetAt(pKey->m_lpszBuffer,pValue);
		//	ayValue.ay.RemoveAt(1);
		//}
	}

	return 1;//m_map.GetCount();
}

int CHqDataBufferArray_Dfx::BuildMap(CHqDataBuffer* strResource,const char* strDelimit)
{
	if( strResource == NULL || !strResource->IsValid() )
		return 0;

	strResource->MakeUpper();

	CHqDataBufferArray ayRet;
	int nCount = AnalyzeStr(strResource->m_lpszBuffer,strDelimit,ayRet.ay);
	if( nCount <= 0 )
		return 0;

	int nItem;
	CHqDataBuffer* pBuffer;

	CHqDataBuffer* pKey;
	CHqDataBuffer* pValue;
	CHqDataBuffer* pTemp;

	for( int i = 0; i < nCount; i++ )
	{
		pBuffer = ayRet.ay.GetAt(i);
		if( pBuffer == NULL || pBuffer->IsEmpty() )
			continue;

		CHqDataBufferArray ayValue;
		nItem = AnalyzeStr(pBuffer->m_lpszBuffer,"=",ayValue.ay);
		if( nItem < 2 )
			continue;

		pKey = ayValue.ay.GetAt(0);
		pValue = ayValue.ay.GetAt(1);

		if( pKey == NULL   || pKey->IsEmpty() ||
			pValue == NULL || pValue->IsEmpty() )
			continue;

		pKey->Trim();
		//pKey->MakeUpper();		
		//pValue->MakeUpper();

		if( !m_map.Lookup(pKey->m_lpszBuffer,(void*&)pTemp) )
		{
			m_map.SetAt(pKey->m_lpszBuffer,pValue);
			ayValue.ay.RemoveAt(1);
		}
	}

	return m_map.GetCount();
}

char* CHqDataBufferArray_Dfx::GetValue(const char* szKey)
{
	if( szKey == NULL )
		return NULL;

	//CHqDataBuffer buffer;
	//buffer.CopyStr(szKey);
	//buffer.MakeUpper();

	CHqDataBuffer* CurBuffer;
	if( m_map.Lookup(szKey,(void*&)CurBuffer) )
		return CurBuffer->m_lpszBuffer;

	return NULL;
}

char* CHqDataBufferArray_Dfx::GetValue_Dfx(const char* szKey,CHqDataBuffer& buffer)
{
	return GetValue(szKey);

#if 0
	if( szKey == NULL )
		return NULL;

	if( m_pSrcBuffer.IsEmpty() )
		return NULL;

	char* pValue = strstr(m_pSrcBuffer.m_lpszBuffer,szKey);
	if( pValue == NULL )
		return NULL;

	pValue += strlen(szKey);

	while( (*pValue == ' ') || (*pValue == '=') ) 
	{
		if(*pValue == '=')
		{
			pValue++;
			break;
		}
		pValue++;
	}

	char* pValueEnd = pValue;
	while( (*pValueEnd != '&') && (*pValueEnd != 0) ) 
	{
		pValueEnd++;
	}

	//pValue = strstr(pValue,"=");
	//if( pValue == NULL )
	//	return NULL;

	//char* pValueEnd = strstr(pValue,"&");
	//if( pValueEnd == NULL )
	//{

	//pValue++;
	if( *pValueEnd != 0 && pValueEnd > pValue )
	{
		buffer.Alloc(pValueEnd - pValue);
		memcpy(buffer.m_lpszBuffer,pValue,buffer.m_cbBuffer);
	}
	else
	{
		buffer.Alloc(strlen(pValue));
		memcpy(buffer.m_lpszBuffer,pValue,buffer.m_cbBuffer);
	}

	return buffer.m_lpszBuffer;
#endif

}

int CHqDataBufferArray_Dfx::GetMarketValue_Dfx(CHqDataBuffer& retbuffer)
{
	return GetMarketValue();

#if 0
	int nMarket = GetNumValue_Dfx("MARKET",retbuffer);
	nMarket <<= 4;
	return nMarket;
#endif
}

int CHqDataBufferArray_Dfx::GetNumValue_Dfx(const char* szKey,CHqDataBuffer& buffer,int nDefault /*= 0*/)
{
	return GetNumValue(szKey,nDefault);

#if 0
	if( szKey == NULL )
		return nDefault;

	if( m_pSrcBuffer.IsEmpty() )
		return nDefault;

	char* pValue = strstr(m_pSrcBuffer.m_lpszBuffer,szKey);
	if( pValue == NULL )
		return nDefault;

	pValue += strlen(szKey);

	while( ((*pValue == ' ') || (*pValue == '=')) && (*pValue != 0) ) 
	{
		if( *pValue == '=' )
		{
			pValue++;
			return atol(pValue);
		}
		pValue++;
	}

	//pValue = strstr(pValue,"=");
	//if( pValue == NULL )
	//	return nDefault;

	//char* pValueEnd = strstr(pValue,"&");
	//if( pValueEnd == NULL )
	//{

	//pValue++;
	//return atol(pValue);

	return nDefault;
#endif

}

int CHqDataBufferArray_Dfx::GetNumValue(const char* szKey,int nDefault /*= 0*/)
{
	char* szValue = GetValue(szKey);
	if( szValue )
		return atol(szValue);

	return nDefault;
}

int	CHqDataBufferArray_Dfx::GetSrvValue()
{
	return GetNumValue("SRV");
}

int	CHqDataBufferArray_Dfx::GetContenttype(CHqDataBuffer& buffer)
{
	int nSrv = GetSrvValue();
	nSrv += GIF_Fun_Begin;
	if( nSrv == GIF_Fenshi || 
		nSrv == GIF_Lead   ||
		nSrv == GIF_Day	)
	{
		if( GetGifJpep() == 1 )
			buffer.CopyStr("image/gif");
		else if( GetGifJpep() == 2 )
			buffer.CopyStr("image/jpeg");
		else
			buffer.CopyStr("image/png");
	}
	else
	{
		buffer.CopyStr("text/plain");
	}

	return 0;
}

int CHqDataBufferArray_Dfx::GetMarketValue()
{
	int nMarket = GetNumValue("MARKET");
	nMarket <<= 4;
	return nMarket;
}

int CHqDataBufferArray_Dfx::GetReportMarket()
{
	int nMarket = GetNumValue("REPORTMARKET");
	return nMarket;
}

int	CHqDataBufferArray_Dfx::GetReportBegin()
{
	return GetNumValue("REPORTBEGIN");
}

int	CHqDataBufferArray_Dfx::GetReportTotal()
{
	return GetNumValue("REPORTTOTAL");
}

int	CHqDataBufferArray_Dfx::GetXMLOut()
{
	return GetNumValue("XMLOUT");
}

int	CHqDataBufferArray_Dfx::GetTextOut()
{
	return GetNumValue("TEXTOUT");
}

int	CHqDataBufferArray_Dfx::GetTextCfgNum()
{
	return GetNumValue("CFGNUM");
}

int CHqDataBufferArray_Dfx::GetRefreshMode()
{
	return GetNumValue("REFRESHMODE");
}

int CHqDataBufferArray_Dfx::GetRefreshtime()
{
	int nRet = GetNumValue("REFRESHTIME");

	if( nRet <= 0 )
		nRet = 10000;

	return nRet;
}

int CHqDataBufferArray_Dfx::GetReportSort()
{
	return GetNumValue("REPORTSORT");
}

int CHqDataBufferArray_Dfx::GetReportField()
{
	return GetNumValue("REPORTFIELD");
}

int CHqDataBufferArray_Dfx::GetReportAscending()
{
	return GetNumValue("ASCENDING");
}

char* CHqDataBufferArray_Dfx::GetReportBlockName()
{
	return GetValue("BLOCKNAME");
}

unsigned long CHqDataBufferArray_Dfx::GetGifRGBByWord(const char* szKey)
{
	RGBData	rgb = GetGifRGB(szKey);
	if( rgb.IsValid() )
	{
		return RGB_Linux(rgb.r,rgb.g,rgb.b);
	}

	return -1;
}

int	CHqDataBufferArray_Dfx::GetReportCode()
{
	int nRet = GetGifRGBByWord("REPORTCODE");
	if( nRet < 0 )
		return RGB_Linux(244,244,244);
	return nRet;
}

int	CHqDataBufferArray_Dfx::GetReportName()
{
	int nRet = GetGifRGBByWord("REPORTNAME");
	if( nRet < 0 )
		return RGB_Linux(255,255,0);
	return nRet;
}

int	CHqDataBufferArray_Dfx::GetReportEqual()
{
	int nRet = GetGifRGBByWord("REPORTEQUAL");
	if( nRet < 0 )
		return RGB_Linux(255,255,255);
	return nRet;
}

int	CHqDataBufferArray_Dfx::GetReportRaise()
{
	int nRet = GetGifRGBByWord("REPORTRAISE");
	if( nRet < 0 )
		return RGB_Linux(255,0,0);
	return nRet;
}

int	CHqDataBufferArray_Dfx::GetReportDown()
{
	int nRet = GetGifRGBByWord("REPORTDOWN");
	if( nRet < 0 )
		return RGB_Linux(0,255,0);
	return nRet;
}

int	CHqDataBufferArray_Dfx::GetReportVolum()
{
	int nRet = GetGifRGBByWord("REPORTVOLUM");
	if( nRet < 0 )
		return RGB_Linux(244,244,244);
	return nRet;
}

int	CHqDataBufferArray_Dfx::GetReportMoney()
{
	int nRet = GetGifRGBByWord("REPORTMONEY");
	if( nRet < 0 )
		return RGB_Linux(255,0,0);
	return nRet;
}

int CHqDataBufferArray_Dfx::GetGifWidth()
{
	int nWid  = GetNumValue("W");
	int nWid2 = GetGifWid();

	if( nWid <= 0 && nWid2 <= 0 )
		return 400;
	
	return max((nWid + nWid2),1);
}

int CHqDataBufferArray_Dfx::GetGifHeight()
{
	int nHeight = GetNumValue("H");

	if( nHeight <= 0 )
        return 230;
	return nHeight;
}

int CHqDataBufferArray_Dfx::GetGifLeftPrice()
{
	return GetNumValue("PRICE",1);
}

int CHqDataBufferArray_Dfx::GetGifRightRate()
{
	return GetNumValue("RATE",1);
}

char* CHqDataBufferArray_Dfx::GetGifStkCode()
{
	return GetValue("STKCODE");	
}

char* CHqDataBufferArray_Dfx::GetGifStkName()
{
	return GetValue("STKNAME");	
}

int	CHqDataBufferArray_Dfx::GetGifClock()
{
	return GetNumValue("CLOCK",1);
}

int	CHqDataBufferArray_Dfx::GetGifStyle()
{
	return GetNumValue("STYLE");
}

int CHqDataBufferArray_Dfx::GetGifIszs()
{
	return GetNumValue("ISZS");
}

int	CHqDataBufferArray_Dfx::GetGifWanthead()
{
	return GetNumValue("WANTHEAD");
}

int	CHqDataBufferArray_Dfx::GetGifNotWantCode()
{
	return GetNumValue("NOTWANTCODE");
}

int	CHqDataBufferArray_Dfx::GetGifLinetype()
{
	int nRet = GetNumValue("LINETYPE");

	static short type[8] = {0,0,5,6,1,2,3,4};
	if( nRet > 0 && nRet < 8 )
		return type[nRet];

	return 0;

	//1   日线
	//2   周线
	//3   月线
	//4   5分钟线
	//5   15分钟线
	//6   30分钟线
	//7   60分钟线
}

int	CHqDataBufferArray_Dfx::GetGifWantana()
{
	return GetNumValue("WANTANA",1);
}

int CHqDataBufferArray_Dfx::GetGifVolume()
{
	return GetNumValue("VOLUME",1);
}

int	CHqDataBufferArray_Dfx::GetGifRightPrice()		  
{
	// 是否要右边小图
	return GetNumValue("RIGHTPRICE",0);
}

char* CHqDataBufferArray_Dfx::GetGifZbkind()
{
	char* pRet = GetValue("ZBKIND");
	if( pRet == NULL )
	{
		static char* pSz = "MACD";
		return pSz;
	}
	return pRet;
}

int	CHqDataBufferArray_Dfx::GetGifDAY()
{
	int nRet = GetNumValue("DAY");
	if( nRet <= 0 )
		return 240;

	return nRet;
}

int	CHqDataBufferArray_Dfx::GetGifWid()
{
	return GetNumValue("WID");
}

int	CHqDataBufferArray_Dfx::GetGifWithnow()
{
	return GetNumValue("WITHNOW");
}

int	CHqDataBufferArray_Dfx::GetGifFontSize()
{
	int nSize = GetNumValue("FONTSIZE");
	if( nSize == 0 )
		return 10;

	return nSize;
}

char* CHqDataBufferArray_Dfx::GetGifFontName()
{
	char* pName = GetValue("FONTNAME");
	if( pName == NULL )
	{
		static char* sz = "TIMES.TTF";
		return sz;
	}

	return pName;
}

int	CHqDataBufferArray_Dfx::GetGifJpep()
{
	return GetNumValue("JPEP");
}

RGBData	CHqDataBufferArray_Dfx::GetGifRGB(const char* szKey)
{
	RGBData rgb;
	char* pRgb = GetValue(szKey);
	if( pRgb == NULL )
		return rgb;

	CHqDataBufferArray ayRet;
	int nCount = AnalyzeStr(pRgb,",",ayRet.ay);
	if( nCount <= 0 )
		return rgb;

	if( ayRet.ay.GetSize() >= 1 )
	{
		rgb.r = atol(ayRet.ay.GetAt(0)->m_lpszBuffer);
		rgb.g = 0;
		rgb.b = 0;
	}

	if( ayRet.ay.GetSize() >= 2 )
	{
		rgb.g = atol(ayRet.ay.GetAt(1)->m_lpszBuffer);
		rgb.b = 0;
	}

	if( ayRet.ay.GetSize() >= 3 )
	{
		rgb.b = atol(ayRet.ay.GetAt(2)->m_lpszBuffer);
	}

	return rgb;
}

RGBData CHqDataBufferArray_Dfx::GetGifCoordinateColor()
{
	return GetGifRGB("COORDINATECOLOR");
}

RGBData CHqDataBufferArray_Dfx::GetGifTechText()
{
	return GetGifRGB("TECHTEXT");
}

RGBData CHqDataBufferArray_Dfx::GetGifFixTextColor()
{
	return GetGifRGB("FIXTEXTCOLOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifUpColor()
{
	return GetGifRGB("UPCOLOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifDownColor()
{
	return GetGifRGB("DOWNCOLOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifTitleColor()
{
	return GetGifRGB("TITLECOLOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifCompanyColor()
{
	return GetGifRGB("COMPANYCOLOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifGridColor()
{
	return GetGifRGB("GRIDCOLOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifBackColor()
{
	return GetGifRGB("BACKCOLOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifLianBiAxis()
{
	return GetGifRGB("LIANBIAXIS");
}
RGBData CHqDataBufferArray_Dfx::GetGifLianBi()
{
	return GetGifRGB("LIANBI");
}
RGBData CHqDataBufferArray_Dfx::GetGifclWhite()
{
	return GetGifRGB("WHITE");
}
RGBData CHqDataBufferArray_Dfx::GetGifclBuy()
{
	return GetGifRGB("BUY");
}
RGBData CHqDataBufferArray_Dfx::GetGifclSell()
{
	return GetGifRGB("SELL");
}
RGBData CHqDataBufferArray_Dfx::GetGifclFenshiPrice()
{
	return GetGifRGB("FENSHIPRICE");
}
RGBData CHqDataBufferArray_Dfx::GetGifclAvgPrice()
{
	return GetGifRGB("AVGPRICE");
}
RGBData CHqDataBufferArray_Dfx::GetGifclFenshiMid()
{
	return GetGifRGB("FENSHIMID");
}
RGBData CHqDataBufferArray_Dfx::GetGifclFenshiBottomHor()
{
	return GetGifRGB("FENSHIBOTTOMHOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifVolumeAxis()
{
	return GetGifRGB("VOLUMEAXIS");
}
RGBData CHqDataBufferArray_Dfx::GetGifclMacdHor()
{
	return GetGifRGB("MACDHOR");
}
RGBData CHqDataBufferArray_Dfx::GetGifclAvg1()
{
	return GetGifRGB("AVG1");
}
RGBData CHqDataBufferArray_Dfx::GetGifclAvg2()
{
	return GetGifRGB("AVG2");
}
RGBData CHqDataBufferArray_Dfx::GetGifclAvg3()
{
	return GetGifRGB("AVG3");
}
RGBData CHqDataBufferArray_Dfx::GetGifclAvg4()
{
	return GetGifRGB("AVG4");
}
RGBData CHqDataBufferArray_Dfx::GetGifclAvg5()
{
	return GetGifRGB("AVG5");
}

RGBData CHqDataBufferArray_Dfx::GetGifInSideBack()
{
	return GetGifRGB("INSIDEBACK");
}

RGBData CHqDataBufferArray_Dfx::GetGifInSideGrid()
{
	return GetGifRGB("INSIDEGRID");
}

RGBData CHqDataBufferArray_Dfx::GetGifSolidPKline()
{
	return GetGifRGB("SOLIDPKLINE");
}

RGBData CHqDataBufferArray_Dfx::GetGifParamBack()
{
	return GetGifRGB("PARAMBACK");
}

RGBData CHqDataBufferArray_Dfx::GetGifParamBarBack()
{
	return GetGifRGB("PARAMBARBACK");
}

RGBData CHqDataBufferArray_Dfx::GetGifParamValue()
{
	return GetGifRGB("PARAMVALUE");
}

RGBData CHqDataBufferArray_Dfx::GetGifJinE()	 // 金额
{
	return GetGifRGB("JINE");
}

RGBData CHqDataBufferArray_Dfx::GetGifXianShou() // 现手
{
	return GetGifRGB("XIANSHOU");
}


CYlsMapPtrToPtr Dfx_DataItem::m_map;
Dfx_DataItem::Dfx_DataItem()
{
	memset(this,0,sizeof(Dfx_DataItem));

	m_STEP = 1;
	m_OFS = 1;
	m_KINDS = 1;
	m_BALL = 5;
}

Dfx_DataItem::~Dfx_DataItem()
{
	_delObject(m_PCODE);

	_delObject(m_COMP);
	_delObject(m_PACK);

	_delObject(m_CODES);

	_delObject(m_CHANGED);
	_delObject(m_MAP);

	_delObject(m_GETNUM);

	_delObject(m_HEADER);
	_delObject(m_ABS);
	_delObject(m_FILE);
	_delObject(m_ZLIB);
}

UINT Dfx_DataItem::HashKey(const char* key)
{
	UINT nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}

void Dfx_DataItem::InitMap()
{
#ifdef User_MapFind

	if( m_map.GetSize() > 0 )
		return;

	Dfx_DataItem::m_map.InitHashTable(28+18);

	// 关键字和值得对应位置表
	// srv -> srv的值得位置

	m_map.SetAt((void*)HashKey("SRV"),		(void*)0);
	m_map.SetAt((void*)HashKey("MARKET"),	(void*)1);
	m_map.SetAt((void*)HashKey("CODE"),		(void*)2);
	m_map.SetAt((void*)HashKey("STEP"),		(void*)3);
	m_map.SetAt((void*)HashKey("OFS"),		(void*)4);
	m_map.SetAt((void*)HashKey("BS45"),		(void*)5);

	m_map.SetAt((void*)HashKey("FLAG"),		(void*)6);
	m_map.SetAt((void*)HashKey("TRANNUM"),	(void*)7);
	m_map.SetAt((void*)HashKey("OFSNUM"),	(void*)8);
	m_map.SetAt((void*)HashKey("DAYTYPE"),	(void*)9);
	m_map.SetAt((void*)HashKey("GZLX"),		(void*)10);
	m_map.SetAt((void*)HashKey("DATE"),		(void*)11);
	m_map.SetAt((void*)HashKey("CRC"),		(void*)12);

	m_map.SetAt((void*)HashKey("POS"),		(void*)13);
	m_map.SetAt((void*)HashKey("LEN"),		(void*)14);
	m_map.SetAt((void*)HashKey("KINDS"),	(void*)15);
	m_map.SetAt((void*)HashKey("BALL"),		(void*)16);
	m_map.SetAt((void*)HashKey("LASTDATE"),	(void*)17);

	m_map.SetAt((void*)HashKey("PCODE"),	(void*)18);
	m_map.SetAt((void*)HashKey("COMP"),		(void*)19);
	m_map.SetAt((void*)HashKey("PACK"),		(void*)20);
	m_map.SetAt((void*)HashKey("CODES"),	(void*)21);
	m_map.SetAt((void*)HashKey("CHANGED"),	(void*)22);
	m_map.SetAt((void*)HashKey("MAP"),		(void*)23);
	m_map.SetAt((void*)HashKey("GETNUM"),	(void*)24);
	m_map.SetAt((void*)HashKey("HEADER"),	(void*)25);
	m_map.SetAt((void*)HashKey("ABS"),		(void*)26);
	m_map.SetAt((void*)HashKey("FILE"),		(void*)27);
	m_map.SetAt((void*)HashKey("ZLIB"),		(void*)28);

	//m_map.SetAt((void*)HashKey("ZLIB"),		(void*)27);
#endif

}

CYlsMapStringToPtr CSaveParam_Dfx::m_map;
CYlsMutex		   CSaveParam_Dfx::m_pSessionMutex;
CSaveParam_Dfx::CSaveParam_Dfx()
{
}

CSaveParam_Dfx::~CSaveParam_Dfx()
{
}

int CSaveParam_Dfx::Add(CHqDataBuffer* buffer,DFX_Param* pParam)
{
	//return 0;

	//buffer->Trim();
	//buffer->MakeLower();

	CYlsMutexLock lock(&m_pSessionMutex);

	m_map.SetAt(buffer->m_lpszBuffer,pParam);

	return 0;
}

DFX_Param* CSaveParam_Dfx::Get(CHqDataBuffer* buffer)
{
	//return NULL;

	//buffer->MakeLower();

	CYlsMutexLock lock(&m_pSessionMutex);
	
	DFX_Param* pParam;
	if( m_map.Lookup(buffer->m_lpszBuffer,(void*&)pParam) )
		return pParam;

	return NULL;
}


struct Qentry
{
	int left;
	int right;
};
//
int smartcmp(const void* pBuff1,const void* pBuff2,short count)
{
	int nRet = 0;
	switch(count)
	{
		case QS_INT:
			nRet = (*(int*)pBuff1 == *(int*)pBuff2) ? 0 :
				   (*(int*)pBuff1 >  *(int*)pBuff2) ? 1 : -1;
			break;		
		case QS_UNINT:
			nRet = (*(unsigned int*)pBuff1 == *(unsigned int*)pBuff2) ? 0 :
				   (*(unsigned int*)pBuff1 >  *(unsigned int*)pBuff2) ? 1 : -1;
			break;		
		case QS_LONG:
			nRet = (*(long*)pBuff1 == *(long*)pBuff2) ? 0 :
				   (*(long*)pBuff1 >  *(long*)pBuff2) ? 1 : -1;
			break;		
		case QS_UNLONG:
			nRet = (*(unsigned long*)pBuff1 == *(unsigned long*)pBuff2) ? 0 :
				   (*(unsigned long*)pBuff1 >  *(unsigned long*)pBuff2) ? 1 : -1;
			break;		
		case QS_SHORT:
			nRet = (*(short*)pBuff1 == *(short*)pBuff2) ? 0 :
				   (*(short*)pBuff1 >  *(short*)pBuff2) ? 1 : -1;
			break;		
		case QS_UNSHORT:
			       
			nRet = (*(unsigned short*)pBuff1 == *(unsigned short*)pBuff2) ? 0 :
				   (*(unsigned short*)pBuff1 >  *(unsigned short*)pBuff2) ? 1 : -1;
			break;		
		case QS_FLOAT:
			nRet = (*(float*)pBuff1 == *(float*)pBuff2) ? 0 :
				   (*(float*)pBuff1 >  *(float*)pBuff2) ? 1 : -1;
			break;		
		case QS_DOUBLE:
			nRet = (*(double*)pBuff1 == *(double*)pBuff2) ? 0 :
				   (*(double*)pBuff1 >  *(double*)pBuff2) ? 1 : -1;
			break;		
		default:
			if(count > 0)
			{
 				void* p;
 				short sLen,sMin = count;
				if((p = (void*)memchr(pBuff1,'\0',count)) != NULL)
				{
					sLen = (char*)p - (char*)pBuff1;
					if((sLen > 0) && (sLen < sMin))
					{
						sMin = sLen;
					}	
				}
				if((p = (void*)memchr(pBuff2,'\0',count)) != NULL)
				{
					sLen = (char*)p - (char*)pBuff2;
					if((sLen > 0) && (sLen < sMin))
					{
						sMin = sLen;
					}	
				}
				nRet = memcmp(pBuff1,pBuff2,sMin);
			}
			break;					
      }
	return nRet;
}

int	BinarySearch(struct KQuickSort* pQSData,void* pKeySearchFor)
{
   long mid,iLow,iHigh;
   int nRet;
   if((pQSData == NULL) || (pKeySearchFor == NULL))
   {
   		return -1;
   }
   iLow = pQSData->m_nLow;
   iHigh = pQSData->m_nHigh;		
   if(iHigh < iLow)
       return -1;
   char* pKey = (char*)pQSData->m_pData + pQSData->m_nKeyOffset;
   char* pKeyCur;
   
   do
   {
      mid = (iLow + iHigh) / 2;
      pKeyCur = pKey + mid*pQSData->m_nDataLen;
      nRet = smartcmp(pKeyCur,pKeySearchFor,pQSData->m_nKeyLen);
      if(nRet == 0)
          return mid;
      if(nRet > 0)
         iHigh = mid - 1;
       else
         iLow  = mid + 1;
    }while (iLow <= iHigh);
   return -1;
}

void QuickSortAscend(struct KQuickSort* pQSData)
{
	long iUp, iDown;
	long iLow,iHigh;
 	if(pQSData == NULL)
   		return;
	iLow = pQSData->m_nLow;
	iHigh = pQSData->m_nHigh;		

	short  nDataLen = pQSData->m_nDataLen;
	short  nKeyLen  = pQSData->m_nKeyLen;

    if(iLow >= iHigh)	
    	return;
    if(nDataLen <= 0)
    	return;
    char* pTemp = new char[nDataLen];
	char* pKey = (char*)pQSData->m_pData + pQSData->m_nKeyOffset;
	char* pData = (char*)pQSData->m_pData;

    char* pKeyLow;
    char* pKeyHigh;
	if( (iHigh - iLow) == 1 )
	{
		pKeyLow  = pKey + iLow*nDataLen;
		pKeyHigh = pKey + iHigh*nDataLen;
        if(smartcmp(pKeyLow,pKeyHigh,nKeyLen) > 0)
        {
        	memcpy(pTemp,pData+iHigh*nDataLen,nDataLen);
            memcpy(pData+iHigh*nDataLen,pData+iLow*nDataLen,nDataLen);
            memcpy(pData+iLow*nDataLen,pTemp,nDataLen);
        }
    }
    else
    {
    	do
        {
                // Move in from both sides towards the pivot element.
         	iUp = iLow;
        	iDown = iHigh;
            while(iUp < iDown)
            {
            	if(smartcmp(pKey+iUp*nDataLen,pKey+iHigh*nDataLen,
                             nKeyLen) > 0)
                	break;
                iUp++;
            }  
            while(iDown > iUp)
            {
            	if(smartcmp(pKey+iDown*nDataLen,pKey+iHigh*nDataLen,
                             nKeyLen) < 0)
                	break;
				iDown--;
            }
                // If we haven't reached the pivot, it means that two
                // elements on either side are out of order, so swap them.
                //
            if( iUp < iDown )
            {
        		memcpy(pTemp,pData+iDown*nDataLen,nDataLen);
            	memcpy(pData+iDown*nDataLen,pData+iUp*nDataLen,nDataLen);
            	memcpy(pData+iUp*nDataLen,pTemp,nDataLen);
            }
     	} while ( iUp < iDown );

            // Move pivot element back to its proper place in the array.
        memcpy(pTemp,pData+iHigh*nDataLen,nDataLen);
        memcpy(pData+iHigh*nDataLen,pData+iUp*nDataLen,nDataLen);
        memcpy(pData+iUp*nDataLen,pTemp,nDataLen);
        if( (iUp - iLow) < (iHigh - iUp) )
        {
         	pQSData->m_nLow = iLow;
         	pQSData->m_nHigh = iUp - 1;		
         	QuickSortAscend(pQSData);
         	pQSData->m_nLow = iUp + 1;
         	pQSData->m_nHigh = iHigh;		
            QuickSortAscend(pQSData);
        }
        else
        {
         	pQSData->m_nLow = iUp + 1;
         	pQSData->m_nHigh = iHigh;		
        	QuickSortAscend(pQSData);
         	pQSData->m_nLow = iLow;
         	pQSData->m_nHigh = iUp - 1;		
            QuickSortAscend(pQSData);
        }
    }
    delete[] pTemp;
}
void QuickSortAscend2(struct KQuickSort* pQSData)
{
	long i = 0,j = 0,l = 0,r = 0,top = 0,PivotIndex = 0;
	
	if(pQSData == NULL) 
		return;

	i = pQSData->m_nLow;
	j = pQSData->m_nHigh;
	int iSize = j - i + 1;
	
	short  nDataLen = pQSData->m_nDataLen;
	short  nKeyLen  = pQSData->m_nKeyLen;
	
	if(nDataLen <= 0 || iSize <= 1)
		return;
	
	char* pivot = NULL;
	char* pKey	= (char*)pQSData->m_pData + pQSData->m_nKeyOffset;
	char* pData = (char*)pQSData->m_pData;
	
	char* pTemp = new char[nDataLen];
	
	if(iSize == 2)
	{
		if(smartcmp(pKey + i * nDataLen,pKey + j * nDataLen,nKeyLen) > 0)
		{
			memcpy(pTemp,pData + j * nDataLen,nDataLen);
			memcpy(pData + j * nDataLen,pData + i * nDataLen,nDataLen);
			memcpy(pData + i * nDataLen,pTemp,nDataLen);
		}
		delete[] pTemp;
		return;
	}

	Qentry* pStack = new Qentry[1000]; // 100
	memset(pStack,0,sizeof(Qentry)*1000);

	pStack->left  = i;
	pStack->right = j;

	while( top >= 0 )
	{
		//Pop Stack
		i = (pStack + top)->left;
		j = (pStack + top--)->right;
		
		//Find Pivot
		PivotIndex = (i + j) >> 1;
		
		pivot = pKey + PivotIndex * nDataLen;
		
		//Stick pivot at end
		memcpy(pTemp,pData + PivotIndex * nDataLen,nDataLen);
		memcpy(pData + PivotIndex * nDataLen,pData + j * nDataLen,nDataLen);
		memcpy(pData + j * nDataLen,pTemp,nDataLen);
		
		//Partition
		l = i - 1;
		r = j;
		do
		{
			while(smartcmp((char*)(pKey + (++l) * nDataLen),pivot,nKeyLen) < 0);
			while(r && smartcmp((char*)(pKey + (--r) * nDataLen),pivot,nKeyLen) > 0);
			memcpy(pTemp,pData + l * nDataLen,nDataLen);
			memcpy(pData + l * nDataLen,pData + r * nDataLen,nDataLen);
			memcpy(pData + r * nDataLen,pTemp,nDataLen);
		} while ( l < r );

		//==============================
		//Undo final swap
		memcpy(pTemp,pData + l * nDataLen,nDataLen);
		memcpy(pData + l * nDataLen,pData + r * nDataLen,nDataLen);
		memcpy(pData + r * nDataLen,pTemp,nDataLen);

		//==============================
		//Put pivot value in place
		memcpy(pTemp,pData + l * nDataLen,nDataLen);
		memcpy(pData + l * nDataLen,pData + j * nDataLen,nDataLen);
		memcpy(pData + j * nDataLen,pTemp,nDataLen);

		//==============================		
		if(l - i > 9)
		{
			top++;
			(pStack + top)->left = i;
			(pStack + top)->right = l - 1;
		}

		if(j - l > 9)
		{
			top++;
			(pStack + top)->left = l + 1;
			(pStack + top)->right = j;
		}
	}

	delete[] pStack;

	//Insertion Sort
	for(i = pQSData->m_nLow;i < pQSData->m_nHigh + 1;i ++)
		for(j = i;(j > pQSData->m_nLow) && (smartcmp((char*)(pKey + j * nDataLen),(char*)(pKey + (j - 1) * nDataLen),nKeyLen) < 0);j --)
		{
			memcpy(pTemp,pData + j * nDataLen,nDataLen);
			memcpy(pData + j * nDataLen,pData + (j - 1) * nDataLen,nDataLen);
			memcpy(pData + (j  - 1) * nDataLen,pTemp,nDataLen);
		}

   delete[] pTemp;		
}

void QuickSortDescend(struct KQuickSort* pQSData)
{
	long iUp, iDown;
	long iLow,iHigh;
 	if(pQSData == NULL)
   		return;
	iLow = pQSData->m_nLow;
	iHigh = pQSData->m_nHigh;		

	short  nDataLen = pQSData->m_nDataLen;
	short  nKeyLen  = pQSData->m_nKeyLen;

    if(iLow >= iHigh)
    	return;
    if(nDataLen <= 0)
    	return;
    char* pTemp = new char[nDataLen];
	char* pKey = (char*)pQSData->m_pData + pQSData->m_nKeyOffset;
	char* pData = (char*)pQSData->m_pData;

    char* pKeyLow;
    char* pKeyHigh;
    if( (iHigh - iLow) == 1 )
    {
		pKeyLow  = pKey + iLow*nDataLen;
		pKeyHigh = pKey + iHigh*nDataLen;
        if(smartcmp(pKeyLow,pKeyHigh,nKeyLen) < 0)
        {
        	memcpy(pTemp,pData+iHigh*nDataLen,nDataLen);
            memcpy(pData+iHigh*nDataLen,pData+iLow*nDataLen,nDataLen);
            memcpy(pData+iLow*nDataLen,pTemp,nDataLen);
        }
            
    }
    else
    {
    	do
    	{
                // Move in from both sides towards the pivot element.
         	iUp = iLow;
            iDown = iHigh;
            while(iUp < iDown)
            {
            	if(smartcmp(pKey+iUp*nDataLen,pKey+iHigh*nDataLen,
                             nKeyLen) < 0)
                	break;
 				iUp++;
            }  
            while(iDown > iUp)
            {
            	if(smartcmp(pKey+iDown*nDataLen,pKey+iHigh*nDataLen,
                             nKeyLen) > 0)
                	break;
				iDown--;
             }
                // If we haven't reached the pivot, it means that two
                // elements on either side are out of order, so swap them.
                //
             if( iUp < iDown )
             {
         		memcpy(pTemp,pData+iDown*nDataLen,nDataLen);
            	memcpy(pData+iDown*nDataLen,pData+iUp*nDataLen,nDataLen);
            	memcpy(pData+iUp*nDataLen,pTemp,nDataLen);
             }
        } while ( iUp < iDown );

        // Move pivot element back to its proper place in the array.
        memcpy(pTemp,pData+iHigh*nDataLen,nDataLen);
        memcpy(pData+iHigh*nDataLen,pData+iUp*nDataLen,nDataLen);
        memcpy(pData+iUp*nDataLen,pTemp,nDataLen);
             // Recursively call the QuickSort procedure (pass the smaller
            // subdivision first to use less stack space).
            //
       if( (iUp - iLow) < (iHigh - iUp) )
       {
         	pQSData->m_nLow = iLow;
         	pQSData->m_nHigh = iUp - 1;		
       		QuickSortDescend(pQSData);
         	pQSData->m_nLow = iUp + 1;
         	pQSData->m_nHigh = iHigh;		
       		QuickSortDescend(pQSData);
       }
       else
       {
         	pQSData->m_nLow = iUp + 1;
         	pQSData->m_nHigh = iHigh;		
       		QuickSortDescend(pQSData);
         	pQSData->m_nLow = iLow;
         	pQSData->m_nHigh = iUp - 1;		
       		QuickSortDescend(pQSData);
       }
   }
   delete[] pTemp;
}
void QuickSortDescend2(struct KQuickSort* pQSData)
{
	long i,j,l,r,top = 0,PivotIndex = 0;
	
	if(pQSData == NULL) return;
	i = pQSData->m_nLow;
	j = pQSData->m_nHigh;
	int iSize = j - i + 1;
	
	short  nDataLen = pQSData->m_nDataLen;
	short  nKeyLen  = pQSData->m_nKeyLen;
	
	if(nDataLen <= 0 || iSize <= 1) return;
	
	char* pivot = NULL;
	char* pKey	= (char*)pQSData->m_pData + pQSData->m_nKeyOffset;
	char* pData = (char*)pQSData->m_pData;
	
	char* pTemp = new char[nDataLen];
	char* pKeyLow;
	char* pKeyHigh;
	
	if(iSize == 2)
	{
		pKeyLow  = pKey + i * nDataLen;
		pKeyHigh = pKey + j * nDataLen;
		if(smartcmp(pKeyLow,pKeyHigh,nKeyLen) < 0)
		{
			memcpy(pTemp,pData + j * nDataLen,nDataLen);
			memcpy(pData + j * nDataLen,pData + i * nDataLen,nDataLen);
			memcpy(pData + i * nDataLen,pTemp,nDataLen);
		}
		delete[] pTemp;
		return;
	}
	Qentry* pStack = new Qentry[100];
	pStack->left  = i;
	pStack->right = j;
	while(top >= 0)
	{
		//Pop Stack
		i = (pStack + top)->left;
		j = (pStack + top--)->right;
		
		//Find Pivot
		PivotIndex = (i + j) >> 1;
		
		pivot = pKey + PivotIndex * nDataLen;
		
		//Stick pivot at end
		memcpy(pTemp,pData + PivotIndex * nDataLen,nDataLen);
		memcpy(pData + PivotIndex * nDataLen,pData + j * nDataLen,nDataLen);
		memcpy(pData + j * nDataLen,pTemp,nDataLen);
		
		//Partition
		l = i - 1;
		r = j;
		do
		{
			while(smartcmp(pKey + (++l) * nDataLen,pivot,nKeyLen) > 0);
			while(r && smartcmp((char*)(pKey + (--r) * nDataLen),pivot,nKeyLen) < 0);
			memcpy(pTemp,pData + l * nDataLen,nDataLen);
			memcpy(pData + l * nDataLen,pData + r * nDataLen,nDataLen);
			memcpy(pData + r * nDataLen,pTemp,nDataLen);
		} while ( l < r );
		//==============================
		//Undo final swap
		memcpy(pTemp,pData + l * nDataLen,nDataLen);
		memcpy(pData + l * nDataLen,pData + r * nDataLen,nDataLen);
		memcpy(pData + r * nDataLen,pTemp,nDataLen);
		//==============================
		//Put pivot value in place
		memcpy(pTemp,pData + l * nDataLen,nDataLen);
		memcpy(pData + l * nDataLen,pData + j * nDataLen,nDataLen);
		memcpy(pData + j * nDataLen,pTemp,nDataLen);
		//==============================		
		if(l - i > 9)
		{
			top++;
			(pStack + top)->left = i;
			(pStack + top)->right = l - 1;
		}
		if(j - l > 9)
		{
			top++;
			(pStack + top)->left = l + 1;
			(pStack + top)->right = j;
		}
	}
	delete[] pStack;
	//Insertion Sort
	for(i = pQSData->m_nLow;i < pQSData->m_nHigh + 1;i ++)
		for(j = i;(j > pQSData->m_nLow) && (smartcmp(pKey + j * nDataLen,pKey + (j - 1) * nDataLen,nKeyLen) > 0);j --)
		{
			memcpy(pTemp,pData + j * nDataLen,nDataLen);
			memcpy(pData + j * nDataLen,pData + (j - 1) * nDataLen,nDataLen);
			memcpy(pData + (j  - 1) * nDataLen,pTemp,nDataLen);
		}
   delete[] pTemp;		
}

#ifdef HS_SUPPORT_UNIX

int	 Yls_pthread_mutex_lock(pthread_mutex_t *mutex)
{
	return pthread_mutex_lock(mutex); // pthread_mutex_trylock(mutex);
}

#else

CString YlsGetProfileText(LPCTSTR lpAppName,        // section name
						  LPCTSTR lpKeyName,        // key name
						  LPCTSTR lpDefault,        // default string
						  LPCTSTR lpFileName)       // initialization file name
{
	CString str;
	int nLen = 128;
	int nRes;
	do
	{
		nLen *= 2;
		str.GetBufferSetLength(nLen);
		::GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,str.GetBuffer(),nLen,lpFileName);
		nRes = lstrlen(str);
	} while (nRes == nLen-1);
	str.ReleaseBuffer();

	return str;
}

BOOL ReadConfigSectionString(const char* strSection, 
							 CStringArray& strArray,const char* strFileName,
							 CStringArray* pArray /*= NULL*/)
{
	strArray.RemoveAll();

	if(strFileName == NULL)
		return NULL;;
	if(_access(strFileName, 0) != 0)
	{
		return FALSE;
	}
	struct _stat buf;
	memset(&buf, 0, sizeof(buf));
	_stat(strFileName, &buf);
	int nSize = (int)buf.st_size;
	if(nSize <= 0)
	{
		return FALSE;
	}
	char* strBuf = new char[nSize+1];
	memset(strBuf,0,nSize+1);

	::GetPrivateProfileString(strSection,NULL,"",strBuf,nSize,strFileName);
	char* p = strBuf;

	int nLen;
	int nTotal = 0;

	//char strItem1[128];
	CString strItem;
	while(*p != '\0')
	{
		//::GetPrivateProfileString(strSection,p,"",strItem1,127,strFileName);
		strItem = YlsGetProfileText(strSection,p,"",strFileName);

		if( pArray )
			pArray->Add(p);

		strArray.Add(strItem);
		nLen = strlen(p) + 1;

		nTotal += nLen;
		if( nTotal >= nSize )
			break;

		p += nLen;
	}  
	delete[] strBuf;

	return TRUE;
}

BOOL ReadCodeToCode(const char* strFileName,CYlsMapStringToPtr& mapCodeToCode)
{	
	mapCodeToCode.RemoveAll();

	// 上证
	char strKey[STOCK_CODE_SIZE + 1];
	char strKey1[20];
	CodeInfo* pCode;
	void* p;

	mapCodeToCode.InitHashTable(2050 - 2001 + 600999 - 600004 + 10);

	int nCode;
	int nCurCode = 2001;
	for( nCode = 609001; nCode < 609090; nCode++,nCurCode++ )
	{
		pCode = new CodeInfo;
		pCode->m_cCodeType = STOCK_MARKET | SZ_BOURSE | KIND_SMALLSTOCK;

		sprintf(strKey1,"%06i",nCurCode);
		strncpy(pCode->m_cCode,strKey1,STOCK_CODE_SIZE);

		sprintf(strKey1,"%06i",nCode);
		strncpy(strKey,strKey1,STOCK_CODE_SIZE);
		strKey[STOCK_CODE_SIZE] = '\0';

		//AfxMessageBox(strKey);

		if( !mapCodeToCode.Lookup(strKey,p) )
			mapCodeToCode.SetAt(strKey,pCode);
	}
	
	// 深证
	nCurCode = 600004;
	for( nCode = 3004; nCode < 3999; nCode++,nCurCode++ )
	{
		pCode = new CodeInfo;
		pCode->m_cCodeType = STOCK_MARKET | SH_BOURSE | KIND_STOCKA;

		sprintf(strKey1,"%06i",nCurCode);
		strncpy(pCode->m_cCode,strKey1,STOCK_CODE_SIZE);

		sprintf(strKey1,"%06i",nCode);
		strncpy(strKey,strKey1,STOCK_CODE_SIZE);
		strKey[STOCK_CODE_SIZE] = '\0';

		//AfxMessageBox(strKey);

		if( !mapCodeToCode.Lookup(strKey,p) )
			mapCodeToCode.SetAt(strKey,pCode);
	}

	return mapCodeToCode.GetCount();
}

#endif


int URLToSelected(char *URL,int stkcount,CYlsArray<int,int>& ay,CYlsMapPtrToPtr& map)//, int stkcount, int *selectedstockmark)
{
	if( URL == NULL )
		return 0;

	int     i, len;
	int		byte;
	char	cc[8];

	len = strlen(URL);
	byte = 0;

	/*for(i = 0; i < len; i++ ) 
	{
		if( URL[i] != '0' )
			break;
	}*/

	int nPos = 0;
	for(i = 0; i < stkcount && (i / 4) < len; i++,nPos++) 
	{
		if( (i % 4) == 0 ) 
		{
			cc[0] = URL[i / 4]; 
			cc[1] = 0;
			sscanf(cc, "%x", &byte);
		}
		if( (byte & (1 << (i % 4))) != 0 )
		{
			map.SetAt((void*)i,(void*)i);

			//ay.SetAt((void*)nPos,(void*)nPos);
			ay.Add(nPos);
			//selectedstockmark[i] = TRUE;
		}
		else
		{
			//ay.SetAt((void*)nPos,(void*)nPos);
			//ay.Add(FALSE);
			//selectedstockmark[i] = FALSE;
		}
	}

	return ay.GetSize();//ay.GetSize();
}

char* SelectedToURL(CHqDataBuffer& pBuffer,int stkcount,CYlsMapPtrToPtr& map)
{
	//int stkcount = ay.GetSize();
	if( stkcount <= 0 )
		return NULL;

	int	byte;
	int	i;

	byte = 0;
	if( !pBuffer.Alloc((stkcount + 3) / 4) )
		 return NULL;

	char* pData = pBuffer.m_lpszBuffer;

	void* value;
	for(i = 0; i < stkcount; i++) 
	{
		if( (i % 4) == 0 )
			byte = 0;

		if( map.Lookup((void*)i,value) )//== TRUE ) 
		{
			byte |= (1 << (i % 4));
		}

		if( (i % 4) == 3 || (i == stkcount - 1))
		{
			sprintf(pData + (i / 4), "%X", byte & 0xf);
		}
	}

	return pData;
}

char* PackRecords(CHqDataBuffer& unpack, char *map, int recordsize,CHqDataBuffer& packed)
{
	if( !unpack.IsValid() )
		return NULL;

	int	count, i, j, k, perrec = 0;
	char	cc[2];
	int	abyte, *isused;

	count = unpack.m_cbBuffer / recordsize;

#if 1
	CYlsArray<int,int> ay;

	int nMap = min(strlen(map)*4,recordsize);

	for (i = 0; i < nMap; i++)
	{
		//isused[i] = 1;
		if (i % 4 == 0)
		{
			if (i > strlen(map) * 4)
				cc[0] = 'f';
			cc[0] = map[i / 4];
			cc[1] = 0;
			sscanf(cc, "%x", &abyte);
		}
		if ((abyte & (1 << (i % 4))) == 0)
		{
			//isused[i] = 0;
		}
		else
		{
			ay.Add(i);
			perrec++;
		}
	}
#else

	CHqDataBuffer isusedBuffer;
	if( !isusedBuffer.Alloc(sizeof(int) * recordsize) )
		return NULL;

	isused = (int*)isusedBuffer.m_lpszBuffer;

	for (i = 0; i < recordsize; i++)
	{
		isused[i] = 1;
		if (i % 4 == 0)
		{
			if (i > strlen(map) * 4)
				cc[0] = 'f';
			cc[0] = map[i / 4];
			cc[1] = 0;
			sscanf(cc, "%x", &abyte);
		}
		if ((abyte & (1 << (i % 4))) == 0)
			isused[i] = 0;
		else
			perrec++;
	}
#endif

	int length = count * perrec * sizeof(char);
	int nCur = length;
	 
	// 2007.11.19 remove
	//if (length == 0)
	//	nCur = 1;

	if( !packed.Alloc(nCur) )
		return NULL;

	packed.m_cbBuffer = length;

#if 0
	for (i = 0; i < count; i++)
	{
		k = 0;
		for (j = 0; j < recordsize; j++)
		{
			if ( isused[j] )
			{
				packed.m_lpszBuffer[perrec * i + k] = unpack.m_lpszBuffer[i * recordsize + j];
				k++;
			}
		}
	}

#else

	nMap = ay.GetSize();
	if( recordsize > 0 )
	{
		for (i = 0; i < count; i++)
		{
			k = 0;
			for (j = 0; j < nMap; j++)
			{
				packed.m_lpszBuffer[perrec * i + k] = unpack.m_lpszBuffer[i * recordsize + ay.GetAt(j)];
				k++;
			}
		}
	}
#endif
	
	return packed.m_lpszBuffer;
}


#define pklabel "PKLWS"

#if 0
char* PackData(CHqDataBuffer& data, int reclen,CHqDataBuffer& s1)
{
    char* PiiPos;
    char* DataPos;
	char* DataLen;
    char* DataReclen;
    char* PPos;
    char  bit;
    int Len;
	int i;
	int pos;
	int iipos;
	int Flaglen;

	if( (reclen < 1) || data.m_cbBuffer <= 0 ) 
		return NULL;

    Flaglen = (reclen + 7) / 8;
	Len = data.m_cbBuffer;

    //result := pklabel + ilength(len) + ilength(reclen);
	s1.m_cbBuffer = 5 + 4 + 4;// + Len + reclen;
	iipos = s1.m_cbBuffer;

	if( !s1.Alloc(iipos + Len * 2) )
		return NULL;

	strncpy(s1.m_lpszBuffer,pklabel,5);

	char intstr[8];
	int2byte(data.m_cbBuffer, intstr);
	memcpy(s1.m_lpszBuffer + 5, (char *)intstr, sizeof(int));

	int2byte(reclen, intstr);
	memcpy(s1.m_lpszBuffer + 9, (char *)intstr, sizeof(int));

    //iipos = length(result);
    //setlength(result, iiPos + Len * 2);
    //inc(iiPos);
    //fillchar(result[iiPos], Len * 2, 0);
    //pos = 1;
	pos = 0;

	//int nPosTest = 0;

	PiiPos   = &s1.m_lpszBuffer[iipos];
	DataPos  = &data.m_lpszBuffer[pos];
    DataLen  = &data.m_lpszBuffer[Len - 1];
    DataReclen = &data.m_lpszBuffer[reclen - 1];
    while ( DataPos <= DataLen )
	{
        PPos = PiiPos;
        PiiPos += Flaglen;

        bit = 1;
        for( i = 0; i < reclen; i++ )
		{
            if( (DataPos <= DataReclen ) ||
               ((DataPos <= DataLen )  &&
                (*DataPos != *(DataPos - reclen - 1)) ) )
			{
                *PPos = ((*PPos) | bit);
                *PiiPos = *DataPos;
                PiiPos++;
			}
            _asm rol bit, 1;// end;
            if( bit == 1 )
				PPos++;

            DataPos++;

			//nPosTest++;
		}
	}

	s1.m_cbBuffer = PiiPos - (&s1.m_lpszBuffer[0]);// + 1;
    //setlength(result, integer(PiiPos) - integer(@result[1]) + 1);

	return s1.m_lpszBuffer;
}

#else

#if 0
char* PackData(CHqDataBuffer& data, int reclen,CHqDataBuffer& s1)
{
	int	pos, i, Flaglen;

	/*int	head_index, data_index;*/

	int	s3_len, s2_start, s3_start;
	char	intstr[8];

	if( (reclen < 1) || data.m_cbBuffer <= 0 )
		return NULL;
	
	Flaglen = (reclen + 7) / 8;
	s1.m_cbBuffer = data.m_cbBuffer + data.m_cbBuffer / 8 + 32;

	if( !s1.Alloc(s1.m_cbBuffer) )
		return NULL;

	s1.m_cbBuffer = strlen(pklabel);
	memcpy(s1.m_lpszBuffer, pklabel, s1.m_cbBuffer);

	int2byte(data.m_cbBuffer, intstr);
	memcpy(s1.m_lpszBuffer + s1.m_cbBuffer, (char *)intstr, sizeof(int));
	s1.m_cbBuffer += sizeof(int);

	int2byte(reclen, intstr);
	memcpy(s1.m_lpszBuffer + s1.m_cbBuffer, (char *)intstr, sizeof(int));
	s1.m_cbBuffer += sizeof(int);

	s2_start = s1.m_cbBuffer;
	s3_start = s2_start + Flaglen;

	pos = 0;
	s3_len = 0;

	while( pos < data.m_cbBuffer ) 
	{
		memset(s1.m_lpszBuffer + s2_start, 0, Flaglen);
		for (i = 0; i < reclen; i++) 
		{
			if( (i + pos < reclen) || ((i + pos < data.m_cbBuffer) && 
				(data.m_lpszBuffer[i + pos] != data.m_lpszBuffer[i + pos - reclen])))
			{
				s1.m_lpszBuffer[s2_start + i / 8] |= (1 << (i % 8));
				s1.m_lpszBuffer[s3_start + s3_len] = data.m_lpszBuffer[i + pos];
				s3_len++;
			 }
		}
		pos += reclen;
		s1.m_cbBuffer += (Flaglen + s3_len); 
		s2_start = s3_start + s3_len;
		s3_start = s2_start + Flaglen;
		s3_len = 0;
	}

	s1.m_lpszBuffer[s1.m_cbBuffer++] = 0;

	return s1.m_lpszBuffer;
}
#endif

#if 1
char* PackData(CHqDataBuffer& data, int reclen,CHqDataBuffer& s1)
{
	//String	s1;
	int	pos, i, Flaglen;

	/*int	head_index, data_index;*/

	int	s3_len, s2_start, s3_start;
	char intstr[8];

	if( (reclen < 1) || data.m_cbBuffer <= 0 ) 
		return NULL;

	Flaglen = (reclen + 7) / 8;
	
	s1.m_cbBuffer = data.m_cbBuffer + data.m_cbBuffer / 8 + 32;

	if( !s1.Alloc(s1.m_cbBuffer) )
		return NULL;

	s1.m_cbBuffer = strlen(pklabel);
	memcpy(s1.m_lpszBuffer, pklabel, s1.m_cbBuffer);

	int2byte(data.m_cbBuffer, intstr);
	memcpy(s1.m_lpszBuffer + s1.m_cbBuffer, (char *)intstr, sizeof(int));
	s1.m_cbBuffer += sizeof(int);

	int2byte(reclen, intstr);
	memcpy(s1.m_lpszBuffer + s1.m_cbBuffer, (char *)intstr, sizeof(int));
	s1.m_cbBuffer += sizeof(int);

	s2_start = s1.m_cbBuffer;
	s3_start = s2_start + Flaglen;

	pos = 0;

	s3_len = 0;

	//int nPosTest = 0;

	while( pos < data.m_cbBuffer )
	{
		//memset(s1.m_lpszBuffer + s2_start, 0, Flaglen);

		for (i = 0; i < reclen; i++)
		{
			if( //((i + pos < reclen) && (i + pos < data.m_cbBuffer)) || 
				(i + pos < reclen) ||
				((i + pos < data.m_cbBuffer) &&
				//(i + pos - reclen < data.m_cbBuffer) &&
				(data.m_lpszBuffer[i + pos] != data.m_lpszBuffer[i + pos - reclen])) ) 
			{
				s1.m_lpszBuffer[s2_start + i / 8] |= (1 << (i % 8));
				s1.m_lpszBuffer[s3_start + s3_len] = data.m_lpszBuffer[i + pos];
				s3_len++;
			 }

			//nPosTest++;
		}
		pos += reclen;
		s1.m_cbBuffer += (Flaglen + s3_len); 
		s2_start = s3_start + s3_len;
		s3_start = s2_start + Flaglen;
		s3_len = 0;
	}
	s1.m_lpszBuffer[s1.m_cbBuffer++] = 0;

	return s1.m_lpszBuffer;
}
#endif

#endif


void CHqDataBuffer::AddError(int nNumber,char* szError,int bUtf8)
{
	char szNum[64];
	sprintf(szNum,"%i",nNumber);
	this->AddStr(szNum);

	if( szError != NULL )
	{
		this->AddStr(",");
		this->AddStr(szError);
	}

	if( bUtf8 )
	{
		CHqDataBuffer bufferNew;
		g2u(this->m_lpszBuffer,bufferNew);
		this->Copy(&bufferNew);
	}
}

int CYlsConvert::gb2u_table[MAX_TABLE_LEN] = {0};
int CYlsConvert::m_isInit = 0;

int CYlsConvert::g2u_get_file(const char* filename,char** buf,int* buf_len)
{
	FILE *f;
	int  file_len = 0,file_head_len = 0,file_end_len = 0;

	*buf_len = 0;
	*buf = NULL;
	f = fopen(filename,"r");
	if (f == NULL)
	{
		//runlog.log("fopen failed can't open file:%s.! Do the file exist?",filename);
		YlsPrompt("fopen failed can't open file:%s.! Do the file exist?",filename);
		return -1;
	}

	fseek(f,0,SEEK_END);
	file_end_len = ftell(f);
	fseek(f,0,SEEK_SET);
	file_head_len = ftell(f);
	file_len = file_end_len - file_head_len;

	if (file_len > MAX_FILE_LEN)
	{
		fclose(f);
		//runlog.log("file gbTounicode exceeded max length.");
		YlsPrompt("file gbTounicode exceeded max length.",NULL);
		return -2;
	}

	*buf = (char*)malloc(file_len + 1);
	if (*buf == NULL)
	{
		fclose(f);
		//runlog.log("malloc error.");
		YlsPrompt("malloc error.",NULL);
		return -3;
	}

	fread(*buf,sizeof(char),file_len,f);
	fclose(f);
	*buf_len = file_len;
	(*buf)[file_len] = 0;

	return 0;
}

int CYlsConvert::g2u_init(const char* filename)
{
	if( m_isInit )
		return 0;

	char szPath[_MAX_PATH];
	CHqDataBuffer buffer;
	buffer.Alloc(260);
	if( filename != NULL )
	{
		sprintf(buffer.m_lpszBuffer,"%s%s",filename,"GbToUnicode");
	}
	else
	{
		sprintf(buffer.m_lpszBuffer,"%s%s",
			CHSFilePath::GetPath(szPath,Srv_Setting),
			"GbToUnicode");
	}
	filename = buffer.m_lpszBuffer;

	char *buf,*cur_pos,*nxt_pos = NULL;
	char is_continue = 1;
	int  buf_len = 0;
	int  gb,uni,ret;

	//runlog.log(__FILE__, __LINE__, " Begin to Init the GB->UTF-8 Table\n");

	if ((ret = g2u_get_file(filename,&buf,&buf_len)) < 0)
	{
		return ret;
	} 

	cur_pos = buf;
	while (is_continue)
	{
		nxt_pos = strchr(cur_pos,'\n');
		if (nxt_pos == NULL)
		{
			is_continue = 0;
		}

		if (sscanf(cur_pos + 2," %X %X",&gb,&uni) == 2)//;
		{
			if (gb < MAX_TABLE_LEN)
				gb2u_table[gb] = uni;	
		}
		cur_pos = nxt_pos + 1;		
	}

	free(buf);

	m_isInit = 1;

	return 0;
}

int CYlsConvert::g2u_convert_unicode(char* gbchar,int gb_len,char* unichar,int uni_len)
{
	if( !m_isInit )
		return 0;

	int num = 0;
	int gb_pos = 0,uni_pos = 0;
	int ret = 0;

	if ((gbchar == NULL) || (unichar == NULL) || (gb_len <= 0) || (uni_len <= 0))
		return 0;

	while ((gbchar[gb_pos] != 0) && (gb_pos < gb_len) && (uni_pos < uni_len))
	{		

		if (((unsigned char)gbchar[gb_pos] >= 0xA0) && ((unsigned char)gbchar[gb_pos + 1] >= 0xA0)
			&& (gb_pos + 1 < gb_len) && (uni_pos + 1 < uni_len))
		{
			num = ((unsigned char)gbchar[gb_pos])*256 + ((unsigned char)gbchar[gb_pos + 1]);		
			if (num == 0)
			{
				unichar[uni_pos++] = gbchar[gb_pos++];
				unichar[uni_pos++] = gbchar[gb_pos++];
			}
			else
			{
				unichar[uni_pos++] = gb2u_table[num] / 256;
				unichar[uni_pos++] = gb2u_table[num] % 256;
				gb_pos += 2;					
				ret ++;
			}
		}
		else
		{
			unichar[uni_pos++] = gbchar[gb_pos++];
		}

	}
	return ret;
}

int CYlsConvert::g2u_convert_utf8(char* gbchar,int gb_len,char* utfchar,int utf_len,int* new_len)
{
	if( !m_isInit )
		return -1;

	int num = 0;
	int gb_pos = 0,utf_pos = 0;
	unsigned char uni_code[2];
	int ret = 0;

	if ((gbchar == NULL) || (utfchar == NULL) || (gb_len <= 0) || (utf_len <= 0))
	{
		*new_len = gb_len;
		return -1;
	}

	while ((gbchar[gb_pos] != 0) && (gb_pos < gb_len) && (utf_pos < utf_len))
	{		

		if (((unsigned char)gbchar[gb_pos] >= 0xA0) && ((unsigned char)gbchar[gb_pos + 1] >= 0xA0)
			&& (gb_pos + 1 < gb_len) && (utf_pos + 1 < utf_len))
		{
			num = ((unsigned char)gbchar[gb_pos])*256 + ((unsigned char)gbchar[gb_pos + 1]);		
			if (num == 0)
			{
				utfchar[utf_pos++] = gbchar[gb_pos++];
				utfchar[utf_pos++] = gbchar[gb_pos++];
			}
			else
			{
				uni_code[0] = (gb2u_table[num] / 256);
				uni_code[1] = (gb2u_table[num] % 256);
				utfchar[utf_pos++] = ( uni_code[0] >> 4) | 0xE0;
				utfchar[utf_pos++] = ((( uni_code[0] & 0x0f) * 4) + (uni_code[1] >> 6) + 0x80) & 0xBF;
				utfchar[utf_pos++] = (uni_code[1] | 0x80) & 0xBF;
				gb_pos += 2;					
				ret ++;
			}
		}
		else
		{
			utfchar[utf_pos++] = gbchar[gb_pos++];
		}

	}
	*new_len = utf_pos;

	return ret;
}

char* g2u(const char* str,CHqDataBuffer& bufferNew)
{
	if( str == NULL )
		return NULL;

	CHqDataBuffer bufferOld;
	bufferOld.CopyStr(str);

	bufferNew.Alloc(strlen(str)*3);

	int new_len;
	if( CYlsConvert::g2u_convert_utf8(bufferOld.m_lpszBuffer,bufferOld.m_cbBuffer,
		bufferNew.m_lpszBuffer,bufferNew.m_cbBuffer,&new_len) < 0 )
	{
		bufferNew.Copy(&bufferOld);
	}

	return bufferNew.m_lpszBuffer;
}

#ifdef HS_SUPPORT_UNIX

char* GetHQPath()
{
	static CHqDataBuffer path;
	if( path.IsEmpty() )
	{
		path.Alloc(_MAX_PATH);
		CHSFilePath::GetPath(path.m_lpszBuffer,Srv_Config);
	}
	return path.m_lpszBuffer;
}

#endif





LogSystem::LogSystem(int nSize /*= 1*/,
					 char cNeedTimer /*= 0*/,
					 long lDate /*= -1*/)
{
	m_nSize = nSize * (1024*1024);
	m_cNeedTimer = cNeedTimer;
	m_fp = new CYlsFile();

	m_lDate = lDate;
}

LogSystem::LogSystem(char* strFileName,			// 文件名
					 int nSize /*= 1*/,			// 大小限制，0不限制
					 char cNeedTimer /*= 0*/,   // 是否加入时间标志
					 long lDate /*= -1*/,       // 自动使用日期作为文件名，即每天一个
					 char* szName /*= NULL*/
					 )
{
	m_nSize = nSize * (1024*1024);
	m_fp = new CYlsFile();
	m_cNeedTimer = cNeedTimer;

	m_lDate = lDate;
	memset(m_szName,0,sizeof(m_szName));
	if( szName )
		strncpy(m_szName,szName,sizeof(m_szName));

	SetName(strFileName);
}

LogSystem::~LogSystem()
{
	if( m_fp )
	{
		m_fp->Close();
		delete m_fp;
		m_fp = NULL;
	}
}

void LogSystem::SetName(char* strFileName)
{
	// 以时间为文件名称
	if( m_lDate != -1 )
	{
		CYlsTime tm = CYlsTime::GetCurrentTime();
		char szDate[64];
		sprintf(szDate,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());

		long lDate = atol(szDate);

		if( lDate == m_lDate )
			return;

		m_lDate = lDate;

		char szPath[_MAX_PATH];
		CHSFilePath::GetPath(szPath,CHSFilePath::RunLog_Temp);
		if( strlen(g_sysSysConfig.m_FileCheckPath) > 0 )
			strncpy(szPath,g_sysSysConfig.m_FileCheckPath,sizeof(szPath));

		if( strlen(m_szName) > 0 )
			sprintf(m_strFileName,"%s%s_%04d%02d%02d.log",szPath,m_szName,tm.GetYear(),tm.GetMonth(),tm.GetDay());
		else
			sprintf(m_strFileName,"%s%04d%02d%02d.log",szPath,tm.GetYear(),tm.GetMonth(),tm.GetDay());

		if( m_fp->m_hFile != INVALID_HANDLE_VALUE )
			m_fp->Close();

		if( !m_fp->Open(m_strFileName,Yls_Create_NoTruncate_Open) )
		{
			m_fp->m_hFile = INVALID_HANDLE_VALUE;
		}
	}
	else
	{
		char szPath[_MAX_PATH];
		CHSFilePath::GetPath(szPath,CHSFilePath::RunLog_Temp);
		if( strlen(g_sysSysConfig.m_FileCheckPath) > 0 )
			strncpy(szPath,g_sysSysConfig.m_FileCheckPath,sizeof(szPath));

		sprintf(m_strFileName,"%s%s%s",szPath,m_szName,strFileName);

		if( m_fp->m_hFile != INVALID_HANDLE_VALUE )
			m_fp->Close();

		if( !m_fp->Open(m_strFileName,Yls_Create_NoTruncate_Open) )
		{
			m_fp->m_hFile = INVALID_HANDLE_VALUE;
		}
	}
}

long LogSystem::WriteLog(const char* pData,const char* szEnd /*= NULL*/)
{
	if( pData == NULL || strlen(pData) <= 0 )
		return 0;

	return WriteLog((void*)pData,strlen(pData),szEnd);
}

long LogSystem::WriteLog(void* pData,int nLen,const char* szEnd /*= NULL*/)
{
	if( pData == NULL || nLen <= 0 )
		return 0;

	if( m_lDate != -1 )
	{
		SetName(NULL);
	}

	if( m_fp == NULL || 
		m_fp->m_hFile == INVALID_HANDLE_VALUE )
		return 0;

	if( m_nSize == 0 || (m_fp->GetLength() < m_nSize) )
	{
		m_fp->SeekToEnd();

		if( m_cNeedTimer )
		{
			char szTime[64];
			CYlsTime tm = CYlsTime::GetCurrentTime();
			sprintf(szTime,"%04d-%02d-%02d-%02d:%02d:%02d ",
				tm.GetYear(),tm.GetMonth(),tm.GetDay(),
				tm.GetHour(),tm.GetMinute(),tm.GetSecond());

			m_fp->Write(szTime,strlen(szTime));
		}

		m_fp->Write(pData,nLen);

		//
		if( szEnd != NULL )
		{
			m_fp->Write(szEnd,strlen(szEnd));
		}
	}
	else
	{
		m_fp->SetLength(0);
	}

	return 0;
}
