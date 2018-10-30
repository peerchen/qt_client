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



#ifndef Share_TOOLS_H
#define Share_TOOLS_H

#include "stdafx.h"

#include "ylsmapptrtoptr.h"

#include "ylsmapstringtoptr.h"
#include "ylstypedptrmap.h"
#include "ylstime.h"

class CYlsFile;
class CSharedMemory;

#define GetRValue_Linux(rgb)      ((BYTE)(rgb))
#define GetGValue_Linux(rgb)      ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue_Linux(rgb)      ((BYTE)((rgb)>>16))

#define RGB_Linux(r,g,b)  ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))


#define	QS_INT			-1
#define	QS_UNINT		-2
#define	QS_LONG			-3
#define	QS_UNLONG		-4
#define	QS_SHORT		-5
#define	QS_WORD		    -6
#define	QS_UNSHORT		-6
#define	QS_FLOAT		-7
#define	QS_DOUBLE		-8

struct KQuickSort
{
	void*	m_pData;
	short	m_nDataLen;
	short	m_nKeyOffset;
	short	m_nKeyLen;
	long	m_nLow;
	long	m_nHigh;
};

// LongToTime
//functions for quick sort and search
int  smartcmp(const void* pBuff1,const void* pBuff2,short count);
int	 BinarySearch(struct KQuickSort* pQSData,void* pKeySearchFor);
void QuickSortAscend(struct KQuickSort* pQSData);
void QuickSortDescend(struct KQuickSort* pQSData);
void QuickSortAscend2(struct KQuickSort* pQSData);
void QuickSortDescend2(struct KQuickSort* pQSData);



extern int   Usleep( unsigned int iUsTimeout );
extern char* YlsMakeUpper(char* szSrc);
extern char* YlsMakeLower2(char* szSrc);

extern void  YlsMakeUpperCode(CodeInfo* pCode);


extern int   StartShareMemoryProcess();
extern void* IsHaveShareMemoryProcess(CSharedMemory* pMemory_stockCount);


extern const char* YlsRTrim(const char* strSrc);
extern const char* YlsLTrim(const char* strSrc);
extern const char* YlsAllTrim(const char* strSrc);

extern LPCTSTR YlsGetKey(char* strKey,CodeInfo* pCode);
extern void	   ConvertStock(StockUserInfo* pStock,StockInitInfo* pStockInfo);

//extern LPCTSTR YlsGetKey(CodeInfo* pCode);

extern int	   Yls_mkdir(const char* szPath);

extern long    GetFileNameLength(const char* strFileName);
extern long    GetFileNameStat(struct stat& stBuff,const char* strFileName);
extern long	   GetFileNameCRC(const char* strFileName);
extern unsigned long	   GetFileNameCreateTime(const char* strFileName);


extern long	   YlsGetFileAttributes(const char* strFileName);
extern long    YlsGetFullPathName(char* lpFileName,unsigned long nBufferLength,char* lpBuffer,char** lpFilePart);


extern void    YlsPrompt(const char* strName,const char* strText);

extern char*  _strncpy(char* string1, const char* string2, int nCount);
extern double _atof(const char* str,int nLen = -1);
extern long   _atol(const char* str,int nLen = -1);
extern int    _strlen(const char* str, int nLen = -1);
extern char*  strcpyn(char* strDest, int nDest, const char* strSource, int nSource = -1, BOOL bTrim = FALSE);

extern unsigned long _atofNew(const char* str,int nUnit = 1,int nLen = -1);
extern unsigned long ConvertStrToLong(const char* str,int nUnit = 1,int nLen = -1);

extern char*  UnionFileName(char* strFile,int nLen,const char* szPath,const char* szCode,const char* szExt);

extern void  YlsSplitFileName( const char *szFileName,char *fname, char *ext );
extern void  YlsSplitpath( const char *path, char *drive, char *dir, char *fname, char *ext );

extern void  YlsSleep(DWORD lTime);
extern void  YlsReplace( char* szData, char chOld, char chNew );


extern char* UnionPath(char* strPath,const char* szFile);


#define WriteError_Flag_Empty 0x0001

extern void	WriteError(void *pRequest, int nLen,char* pFileName);
extern void	WriteCommData(void *pRequest, int nLen);

extern void WriteDataByFile(const char* pData,int nLen,CYlsFile* fp,const char* strDelimit = ",",int nMask = 1);

#ifndef HS_SUPPORT_UNIX

extern BOOL ReadConfigSectionString(const char* strSection, 
							 CStringArray& strArray,const char* strFileName,
							 CStringArray* pArray = NULL);

// ��ȡ���ձ�
extern BOOL ReadCodeToCode(const char* strFileName,CYlsMapStringToPtr& mapCodeToCode);

#else

extern int	   Yls_pthread_mutex_lock(pthread_mutex_t *mutex);

#endif


class LogSystem
{
public:
	LogSystem(int nSize = 1,char cNeedTimer = 0,long lDate = -1);

	LogSystem(char* strFileName,int nSize = 1,char cNeedTimer = 0,long lDate = -1,char* szName = NULL);

	~LogSystem();

	void SetName(char* strFileName);

protected:
	char		m_strFileName[260];
	int			m_nSize;
	char		m_cNeedTimer;
	CYlsFile*	m_fp;

	long		m_lDate; // �Զ�������Ϊ�ļ�����
	char		m_szName[32]; // �����ڹ���������

public:
	long WriteLog(const char* pData,const char* szEnd = NULL);
	long WriteLog(void* pData,int nLen,const char* szEnd = NULL);
};


struct CHqDataBuffer
{
	char* m_lpszBuffer;
	long  m_cbBuffer;
	long  m_nCount;    // ��Ӧ�ṹ����

	CHqDataBuffer()
	{
		m_lpszBuffer = NULL;
		m_cbBuffer = 0;
		m_nCount = 0;
	}

	~CHqDataBuffer()
	{
		Free();
	}

	CHqDataBuffer(const char* sz)
	{
		m_lpszBuffer = NULL;
		m_cbBuffer = 0;
		m_nCount = 0;

		CopyStr(sz);
	}

	void SetCount(int nCount)
	{
		if( nCount > 0 )
			m_nCount = nCount;
	}

	char* Add(long cbBuffer)
	{
		if( cbBuffer <= 0 )
			return NULL;

		cbBuffer += m_cbBuffer;

		char* lpszBuffer = new char[cbBuffer+1];
		if ( lpszBuffer != NULL )
		{
			memset(lpszBuffer,0,cbBuffer+1);

			// ���ƾɵ�
			if( m_cbBuffer > 0 && m_lpszBuffer != NULL )
			{				
				memcpy(lpszBuffer,m_lpszBuffer,m_cbBuffer);
			}
	
			char* pRet = lpszBuffer + m_cbBuffer;
			Free();

			m_lpszBuffer = lpszBuffer;
			m_cbBuffer   = cbBuffer;

			return pRet;
		}

		return NULL;
	}

	int Alloc(long cbBuffer,int nStructSize = -1)
	{
		if( cbBuffer <= 0 )
		{
			Free();
			return 0;
		}

		// ͬ����С,���ٷ���
		if( (cbBuffer == m_cbBuffer) && 
			m_lpszBuffer != NULL )
			return 2;

		Free(); // �ͷžɵ�

		m_lpszBuffer = new char[cbBuffer+1];
		if ( m_lpszBuffer )
		{			
			memset(m_lpszBuffer,0,cbBuffer+1);
			m_cbBuffer = cbBuffer;

			// ��Ӧ�ṹʱ����
			if( nStructSize != -1 && (m_cbBuffer % nStructSize) == 0 )
				m_nCount = m_cbBuffer / nStructSize;
		}

		return IsValid();
	}

	int IsValid() { return (m_cbBuffer > 0 && m_lpszBuffer != NULL); }

	char* Alloc_IncludeSize_DFx(long cbBuffer,int nStructSize = -1)
	{
		 if( !Alloc(cbBuffer + 4,nStructSize) )
			 return 0;

		 char* pData = m_lpszBuffer;

		 *(int*)pData =	YlsIntC(cbBuffer);
		 pData += 4;

		 return pData;
	}

	char* Alloc_DFx(long cbBuffer,int nStructSize = -1)
	{
		 if( !Alloc(cbBuffer,nStructSize) )
			 return NULL;

		 return m_lpszBuffer;
	}

	int IsEmpty()
	{
		if( IsValid() )
			return (strlen(m_lpszBuffer) <= 0 );

		return 1;
	}

	char GetAt(int nIndex)
	{
		if( !IsValid() )
			return 0;

		if( nIndex < m_cbBuffer )
			return m_lpszBuffer[nIndex];

		return 0;
	}

	void Trim()
	{
		if( !IsValid() )
			return;

		YlsAllTrim(m_lpszBuffer);
	}

	void TrimLeft()
	{
		if( !IsValid() )
			return;

		YlsLTrim(m_lpszBuffer);
	}

	void TrimRight()
	{
		if( !IsValid() )
			return;

		YlsRTrim(m_lpszBuffer);
	}

	void Empty()
	{
		this->Free();
	}

	CHqDataBuffer& MakeUpper()
	{
		if( !IsValid() )
			return (*this);

		YlsMakeUpper(m_lpszBuffer);

		return (*this);
	}

	CHqDataBuffer& MakeLower()
	{
		if( !IsValid() )
			return (*this);

		YlsMakeLower2(m_lpszBuffer);

		return (*this);
	}

	int Find(const char* str)
	{
		if( !IsValid() )
			return -1;

		char* pdest = strstr(m_lpszBuffer,str);
		if( pdest )
			return (pdest - m_lpszBuffer);

		return -1;
	}

	int ReverseFind(char ch )
	{
		if( !IsValid() )
			return -1;

		for( int i = strlen(m_lpszBuffer) - 1; i >= 0; i-- )
		{
			if( m_lpszBuffer[i] == ch )
				return i;
		}

		return -1;
	}

	void Free()
	{
		if( m_lpszBuffer == NULL )
			return;

		if( m_cbBuffer <= 0 )
			return;

		m_nCount = 0;
		m_cbBuffer = 0;
		char* pp = m_lpszBuffer;
		m_lpszBuffer = NULL;
		delete [] pp;
	}

	void CopyStr(const char* lpsz)
	{
		if( lpsz == NULL )
			return;

		int nLen = strlen(lpsz);
		this->Alloc(nLen);
		if( m_lpszBuffer )
		{
			strncpy(m_lpszBuffer,lpsz,nLen);
		}
	}

	void CopyMem(const char* lpsz)
	{
		if( lpsz == NULL )
			return;

		int nLen = strlen(lpsz);
		this->Alloc(nLen);
		if( m_lpszBuffer )
		{
			memcpy(m_lpszBuffer,lpsz,nLen);
		}
	}

	void CopyStr(const char* lpsz,int nLen)
	{
		if( lpsz == NULL || nLen <= 0 )
			return;

		this->Alloc(nLen);
		if( m_lpszBuffer )
		{
			strncpy(m_lpszBuffer,lpsz,nLen);
		}
	}

	void CopyMem(const char* lpsz,int nLen)
	{
		if( lpsz == NULL || nLen <= 0 )
			return;

		this->Alloc(nLen);
		if( m_lpszBuffer )
		{
			memcpy(m_lpszBuffer,lpsz,nLen);
		}
	}

	void CopyData(void* lpsz,int nLen)
	{
		if( lpsz == NULL || nLen <= 0 )
			return;

		this->Alloc(nLen);
		if( m_lpszBuffer )
		{
			memcpy(m_lpszBuffer,lpsz,nLen);
		}
	}

	void AddStr(const char* lpsz,int nLen = 0)
	{
		if( lpsz == NULL )
			return;

		CHqDataBuffer buffer;
		if( nLen == 0 )
		{
			buffer.cat(this->m_lpszBuffer,this->m_cbBuffer,lpsz,nLen);
		}
		else
		{
			CHqDataBuffer bufferAdd;
			bufferAdd.CopyStr(lpsz,nLen);
			buffer.cat(this->m_lpszBuffer,this->m_cbBuffer,bufferAdd.m_lpszBuffer,bufferAdd.m_cbBuffer);
		}

		this->Copy(&buffer);
	}

	void AddMem(const char* lpsz,int nLen = 0)
	{
		if( lpsz == NULL )
			return;

		CHqDataBuffer buffer;
		if( nLen == 0 )
		{
			buffer.catMem(this->m_lpszBuffer,this->m_cbBuffer,lpsz,nLen);
		}
		else
		{
			CHqDataBuffer bufferAdd;
			bufferAdd.CopyMem(lpsz,nLen);
			buffer.catMem(this->m_lpszBuffer,this->m_cbBuffer,bufferAdd.m_lpszBuffer,bufferAdd.m_cbBuffer);
		}

		this->Copy(&buffer);
	}

	void AddChar(char lpsz)
	{
		CHqDataBuffer buffer;
		char szChar[2];
		memset(szChar,0,sizeof(szChar));
		szChar[0] = lpsz;
		buffer.cat(this->m_lpszBuffer,this->m_cbBuffer,szChar,0);
		this->Copy(&buffer);
	}
	
	void AddLong(long lpsz)
	{
		CHqDataBuffer buffer;
		char szChar[128];
		sprintf(szChar,"%i",lpsz);
		buffer.cat(this->m_lpszBuffer,this->m_cbBuffer,szChar,0);
		this->Copy(&buffer);
	}

	char* Left(int ndx,CHqDataBuffer& buffer)
	{
		if( !IsValid() )
			return "";

		if( ndx < m_cbBuffer )
		{
			buffer.CopyStr(m_lpszBuffer,ndx);
			return buffer.m_lpszBuffer;
		}

		return "";
	}

	char* LeftMem(int ndx,CHqDataBuffer& buffer)
	{
		if( !IsValid() )
			return "";

		if( ndx < m_cbBuffer )
		{
			buffer.CopyMem(m_lpszBuffer,ndx);
			return buffer.m_lpszBuffer;
		}

		return "";
	}

	char* Mid(int ndx,CHqDataBuffer& buffer,int nLen = 0)
	{
		if( !IsValid() )
			return "";

		if( ndx < m_cbBuffer && (m_cbBuffer - ndx) > 0 )
		{
			buffer.CopyStr(&m_lpszBuffer[ndx],m_cbBuffer - ndx);
			if( nLen > 0 )
			{
				if( buffer.m_cbBuffer > nLen )
				{
					buffer.m_cbBuffer -= nLen;
					memset(&buffer.m_lpszBuffer[nLen],0,buffer.m_cbBuffer);
				}
			}

			return buffer.m_lpszBuffer;
		}

		return "";
	}

	char* MidMem(int ndx,CHqDataBuffer& buffer,int nLen = 0)
	{
		if( !IsValid() )
			return "";

		if( ndx < m_cbBuffer && (m_cbBuffer - ndx) > 0 )
		{
			buffer.CopyMem(&m_lpszBuffer[ndx],m_cbBuffer - ndx);
			if( nLen > 0 )
			{
				if( buffer.m_cbBuffer > nLen )
				{
					buffer.m_cbBuffer -= nLen;
					memset(&buffer.m_lpszBuffer[nLen],0,buffer.m_cbBuffer);
				}
			}

			return buffer.m_lpszBuffer;
		}

		return "";
	}

	void cat(const char* lpsz,int nLen,const char* lpsz1,int nLen1)
	{
		if( (lpsz == NULL) && (lpsz1 == NULL) )
			return;

		if( lpsz )
			nLen = strlen(lpsz);
		if( lpsz1 )
			nLen1 = strlen(lpsz1);

		this->Alloc(nLen + nLen1);
		if( m_lpszBuffer )
		{
			if( lpsz )
				strncpy(m_lpszBuffer,lpsz,nLen);
			if( lpsz1 )
				strncpy(&m_lpszBuffer[nLen],lpsz1,nLen1);
		}
	}

	void catMem(const char* lpsz,int nLen,const char* lpsz1,int nLen1)
	{
		if( (lpsz == NULL) && (lpsz1 == NULL) )
			return;

		if( nLen <= 0 && lpsz )
			nLen = strlen(lpsz);
		if( nLen1 <= 0 && lpsz1 )
			nLen1 = strlen(lpsz1);

		this->Alloc(nLen + nLen1);
		if( m_lpszBuffer )
		{
			if( lpsz )
				memcpy(m_lpszBuffer,lpsz,nLen);
			if( lpsz1 )
				memcpy(&m_lpszBuffer[nLen],lpsz1,nLen1);
		}
	}

	int CompareNoCase(const char* lpsz)
	{
		if( !IsValid() || (lpsz == NULL) )
			return -1;

		if( strlen(m_lpszBuffer) != strlen(lpsz) )
			return -1;

		return strncasecmp(m_lpszBuffer,lpsz,strlen(m_lpszBuffer));
	}

	int Compare(const char* lpsz)
	{
		if( !IsValid() || (lpsz == NULL) )
			return -1;

		if( strlen(m_lpszBuffer) != strlen(lpsz) )
			return -1;

		return strncmp(m_lpszBuffer,lpsz,strlen(m_lpszBuffer));
	}

	CHqDataBuffer& operator=(const char* lpsz)
	{
		CopyStr(lpsz);
		return *this;
	}

	CHqDataBuffer& operator=(char* lpsz)
	{
		CopyStr(lpsz);
		return *this;
	}

	/*CHqDataBuffer& operator=(CHqDataBuffer& data)
	{
		Copy(&data);
		return *this;
	}*/

	BOOL CompareMem(CHqDataBuffer* pData)
	{
		if( pData == NULL || !pData->IsValid() )
			return FALSE;

		if( pData->m_cbBuffer != this->m_cbBuffer )
			return FALSE;

		return (memcmp(this->m_lpszBuffer,pData->m_lpszBuffer,this->m_cbBuffer) == 0);
	}

	BOOL CompareMem(void* pData,int lLen)
	{
		if( pData == NULL || lLen <= 0 )
			return FALSE;

		if( lLen != this->m_cbBuffer )
			return FALSE;

		return (memcmp(this->m_lpszBuffer,pData,this->m_cbBuffer) == 0);
	}

	BOOL Copy(CHqDataBuffer* pData)
	{
		if( pData == NULL || !pData->IsValid() )
			return FALSE;

		if( !this->Alloc(pData->m_cbBuffer) )
			return FALSE;

		memcpy(this->m_lpszBuffer,pData->m_lpszBuffer,this->m_cbBuffer);
		m_nCount = pData->m_nCount;

		return TRUE;
	}

	int GetCount(int nStructSize)
	{
		if( /*m_lpszBuffer != NULL &&*/ nStructSize != 0 && (m_cbBuffer % nStructSize) == 0)
			return (m_cbBuffer / nStructSize);

		return 0;
	}	

	int GetLength()
	{
		if( !IsValid() )
			return 0;

		return strlen(m_lpszBuffer);
	}

	int GetLengthMem()
	{
		if( !IsValid() )
			return 0;

		return m_cbBuffer;
	}

	char* FormatWebItem(const char* szFormat,unsigned long nColor,const char* sz,int nLen)
	{
		int l = strlen(szFormat);
		l += 64;
		l += nLen;

		if( !this->Alloc(l) )
			return "";

		CHqDataBuffer buffer;
		buffer.CopyStr(sz,nLen);

		sprintf(this->m_lpszBuffer,szFormat,
			GetRValue_Linux(nColor),GetGValue_Linux(nColor),GetBValue_Linux(nColor),
			buffer.m_lpszBuffer);

		return m_lpszBuffer;
	}

	void AddError(int nNumber,char* szError,int bUtf8 = 1);

};

struct CShareHqDataBuffer : public CHqDataBuffer
{
	CYlsTime m_oldTime;

	int IsChange(CYlsTime& tm,int nDist = 6)
	{
		CYlsTimeSpan span = tm - m_oldTime;
		if( span.GetTotalSeconds() > nDist ) 
		{
			m_oldTime = tm;
			return 1;
		}

		return 0;
	}

	CShareHqDataBuffer()
		:CHqDataBuffer()
	{
		m_oldTime = 0;
	}
};

extern char* YlsReplaceStr( CHqDataBuffer& oldBuffer,const char* szFind,const char* szData,int nLen);



#define MAX_TABLE_LEN 		65536	 	/* �����ļ���ĳ���*/
#define MAX_FILE_LEN        (4096*1024)

class CYlsConvert
{
protected:
	static int gb2u_table[MAX_TABLE_LEN];
	static int m_isInit;

public:
	static int g2u_get_file(const char* filename,char** buf,int* buf_len);

	static int g2u_init(const char* filename);

	static int g2u_convert_unicode(char* gbchar,int gb_len,char* unichar,int uni_len);

	static int g2u_convert_utf8(char* gbchar,int gb_len,char* utfchar,int utf_len,int* new_len);
};

extern char* g2u(const char* str,CHqDataBuffer& bufferNew);




struct CHqDataBufferArray_NotFree
{
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;
};

struct CHqDataBufferArray
{
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;

	CHqDataBufferArray()
	{
	}

	~CHqDataBufferArray()
	{
		_delArrayObj(ay);
	}	
};

struct RGBData
{
	int r;
	int g;
	int b;

	RGBData()
	{
		r = -1;
		g = -1;
		b = -1;
	}

	int IsValid()
	{
		return (r != -1 && g != -1 && b != -1);
	}
};

static char* Get_Dfx_DataItem(CHqDataBuffer* pBuffer) 
{ 
	if( pBuffer && pBuffer->IsValid() )
		return pBuffer->m_lpszBuffer;

	return NULL;
}

struct Dfx_DataItem
{
	int				m_SRV;
	int				m_MARKET;
	int				m_CODE;
	int				m_STEP;
	int				m_OFS;
	int				m_BS45;

	int				m_FLAG;
	int				m_TRANNUM;
	int				m_OFSNUM;
	int				m_DAYTYPE;
	int				m_GZLX;
	int				m_DATE;	
	int				m_CRC;
	
	int				m_POS;
	int				m_LEN;
	int				m_KINDS;
	int				m_BALL;
	int				m_LastDATE;

	CHqDataBuffer*	m_PCODE;
	CHqDataBuffer*	m_COMP;
	CHqDataBuffer*	m_PACK;
	CHqDataBuffer*	m_CODES;
	CHqDataBuffer*	m_CHANGED;
	CHqDataBuffer*	m_MAP;
	CHqDataBuffer*	m_GETNUM;
	CHqDataBuffer*	m_HEADER;
	CHqDataBuffer*	m_ABS;
	CHqDataBuffer*	m_FILE;
	CHqDataBuffer*	m_ZLIB;

	static CYlsMapPtrToPtr m_map;
	static void InitMap();
	static UINT HashKey(const char* key);

	Dfx_DataItem();
	~Dfx_DataItem();
};

struct CHqDataBufferArray_Dfx
{
	CYlsMapStringToPtr  m_map;

	Dfx_DataItem		m_sDfx_DataItem;

	CHqDataBuffer		m_pBuffer;   // ���ص�buffer
	CHqDataBuffer		m_pSrcBuffer;   // src buffer

	int					m_nIsSend;

	CHqDataBufferArray_Dfx();

	~CHqDataBufferArray_Dfx();

	void    FreeMap();

	int     BuildMapByFile(const char* strFileName,const char* strDelimit);
	int     BuildMap(CHqDataBuffer* strResource,const char* strDelimit);

	int		SetItemValue_Dfx(CHqDataBuffer* pKey,CHqDataBuffer*& pValue);
	int     BuildMap_DFX(CHqDataBuffer* strResource,const char* strDelimit);

	int	    GetContenttype(CHqDataBuffer& buffer);

	char*   GetValue(const char* szKey);
	int     GetNumValue(const char* szKey,int nDefault = 0);
	int     GetMarketValue();
	int		GetSrvValue();

	int     GetGifWidth();			  // ���
	int     GetGifHeight();			  // �߶�
	int     GetGifLeftPrice();		  // ��ʱ�Ƿ���ʾ��߼�
	int     GetGifRightRate();		  // ��ʱ�Ƿ���ʾ�ұ߱�����

	char*   GetGifStkCode();		  // ����
	char*	GetGifStkName();		  // ����

	int	    GetGifClock();			  // �Ƿ���Ҫ��ʾͼƬ�²����ӵ㡰09��30����
	int	    GetGifStyle();			  //
	int	    GetGifIszs();			  // ����һ��ͼ�β��ַ��
	int	    GetGifWanthead();		  // ��Ҫ����̧ͷ
	int		GetGifNotWantCode();	  // ����Ҫ�����д���

	int	    GetGifLinetype();		  // k������
	int	    GetGifWantana();		  // �Ƿ�Ҫ��������
	int	    GetGifVolume();			  // �Ƿ�Ҫ�ɽ���
	int	    GetGifRightPrice();		  // �Ƿ�Ҫ�ұ�Сͼ
	char*   GetGifZbkind();			  // ָ������
	int	    GetGifDAY();			  // һ����ʾ������
	int	    GetGifWid();			  // ͼ��Ŀ��

	int	    GetGifWithnow();			  // ��ʵʱ����

	int	    GetGifFontSize();			  // �����С
	char*   GetGifFontName();			  // ��������

	int	    GetGifJpep();

	int		GetReportMarket();
	int		GetReportBegin();		// ���ۿ�ʼλ��
	int		GetReportTotal();		// ���۸���
	int		GetRefreshMode();		// ����ˢ�·�ʽ
	int     GetRefreshtime();		// ����ˢ��ʱ��
	int     GetReportSort();		// �Ƿ�Ϊ��������
	int     GetReportField();		// �����ֶ�
	int     GetReportAscending();	// ����������/����
	char*	GetReportBlockName();

	unsigned long GetGifRGBByWord(const char* szKey);

	int		GetReportCode();		// ������ɫ
	int		GetReportName();		// ������ɫ
	int		GetReportEqual();		// ƽ����ɫ
	int		GetReportRaise();		// ������ɫ
	int		GetReportDown();		// �µ���ɫ
	int		GetReportVolum();		// �ɽ�����ɫ
	int		GetReportMoney();		// �ɽ�����ɫ

	int		GetXMLOut();			// �Ƿ���xml���
	int		GetTextOut();			// �Ƿ����ı����
	int		GetTextCfgNum();		// �����ļ����




	RGBData	   GetGifRGB(const char* szKey);

	// ��ɫ
	RGBData	   GetGifCoordinateColor();// = YlsRGB(128,0,0);		// ��������
	RGBData	   GetGifTechText();// = YlsRGB(128,0,0);				// ����ͼ���ı�

	RGBData	   GetGifFixTextColor();// = YlsRGB(244,244,244);		// �̶��ı�

	RGBData	   GetGifUpColor();//	   = YlsRGB(255,0,0);			// ����
	RGBData	   GetGifDownColor();//	   = YlsRGB(0,255,0);			// �µ�	

	RGBData	   GetGifTitleColor();//   = YlsRGB(255,255,0);			// ����
	RGBData	   GetGifCompanyColor();	// ��˾

	RGBData	   GetGifGridColor();//	   = YlsRGB(128,0,0);			// �����

	RGBData	   GetGifBackColor();//    = YlsRGB(0,0,0);				// ����
	RGBData	   GetGifLianBiAxis();//   = YlsRGB(192,192,192);		// ����ָ�ꡢָ��ADL�����ָ�� ������ɫ
	RGBData	   GetGifLianBi();//	   = YlsRGB(255,0,255);			// ����ָ�ꡢָ��ADL�����ָ��
	RGBData	   GetGifclWhite();//	   = YlsRGB(255,255,255);		// ƽ��

	RGBData	   GetGifclBuy();//		   = YlsRGB(255,255,255);		// ��������
	RGBData	   GetGifclSell();//	   = YlsRGB(255,255,0);			// ��������

	RGBData	   GetGifclFenshiPrice();// = YlsRGB(255,255,255);      // ��ʱ�۸���
	RGBData	   GetGifclAvgPrice();//    = YlsRGB(255,255,0);        // ����ͼ����
	RGBData	   GetGifclFenshiMid();//	= YlsRGB(255,255,255);	    // ��ʱ�м�������,�����̼�
	RGBData	   GetGifclFenshiBottomHor();//	= YlsRGB(255,255,255);	// ��ʱ�ײ������ߣ���:9:30
	RGBData	   GetGifVolumeAxis();									// �ɽ�������

	RGBData	   GetGifclMacdHor();//	   = YlsRGB(244,233,222);		// macd�м����

	RGBData	   GetGifclAvg1();//	   = YlsRGB(255,255,255);		// ָ�����1
	RGBData	   GetGifclAvg2();//	   = YlsRGB(255,255,0);			// ָ�����2
	RGBData	   GetGifclAvg3();//	   = YlsRGB(255,0,255);			// ָ�����3
	RGBData	   GetGifclAvg4();//	   = YlsRGB(0,255,128);			// ָ�����4
	RGBData	   GetGifclAvg5();//	   = YlsRGB(0,128,255);			// ָ�����5

	RGBData GetGifInSideBack();	  // �ڲ�����
	RGBData GetGifInSideGrid();	  // �ڲ��߿�

	RGBData GetGifSolidPKline();  // k�������ɫ
	RGBData GetGifParamBack();	  // ����������K���£�
	RGBData GetGifParamBarBack(); // ������������K���£�
	RGBData GetGifParamValue();   // ����ֵ


	RGBData GetGifJinE();	 // ���
	RGBData GetGifXianShou();// ����

	char* GetValue_Dfx(const char* szKey,CHqDataBuffer& buffer);
	int	  GetNumValue_Dfx(const char* szKey,CHqDataBuffer& buffer,int nDefault = 0);
	int	  GetMarketValue_Dfx(CHqDataBuffer& buffer);

};



struct CHqDataBufferArray_Level
{
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ay;

	CHqDataBufferArray_Level()
	{
	}

	~CHqDataBufferArray_Level()
	{
		_delArrayObj(ay);
	}
};

extern char* YlsMakeLower(const char* szSrc,CHqDataBuffer& buffer);

extern int   AnalyzeStr(const char* strResource,const char* strDelimit,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayRet);

//
extern int	 URLToSelected(char *URL,int stkcount,CYlsArray<int,int>& ay,CYlsMapPtrToPtr& map);

extern char* SelectedToURL(CHqDataBuffer& pBuffer,int stkcount,CYlsMapPtrToPtr& map);

extern char* PackRecords(CHqDataBuffer& unpack, char *map, int recordsize,CHqDataBuffer& packed);

extern char* PackData(CHqDataBuffer& data, int reclen,CHqDataBuffer& s1);


/*
2�� ����������

�������������ڴ�������ʱ��ָ������LinuxThreadsʵ���н���һ�����������ԣ���ͬ������������ͼ��һ���Ѿ��������Ļ���������ʱ���ֲ�ͬ����ǰ��glibc2.2.3,linuxthreads0.9�����ĸ�ֵ�ɹ�ѡ��

PTHREAD_MUTEX_TIMED_NP������ȱʡֵ��Ҳ������ͨ������һ���̼߳����Ժ��������������߳̽��γ�һ���ȴ����У����ڽ��������ȼ�����������������Ա�֤����Դ����Ĺ�ƽ�ԡ� 
PTHREAD_MUTEX_RECURSIVE_NP��Ƕ����������ͬһ���̶߳�ͬһ�����ɹ���ö�Σ���ͨ�����unlock����������ǲ�ͬ�߳��������ڼ����߳̽���ʱ���¾����� 
PTHREAD_MUTEX_ERRORCHECK_NP������������ͬһ���߳�����ͬһ�������򷵻�EDEADLK��������PTHREAD_MUTEX_TIMED_NP���Ͷ�����ͬ�������ͱ�֤���������μ���ʱ��������������µ������� 
PTHREAD_MUTEX_ADAPTIVE_NP����Ӧ����������򵥵������ͣ����ȴ����������¾����� 
*/

//
class CYlsMutexLock;

class CYlsMutex
{
public:
#ifdef HS_SUPPORT_UNIX
	pthread_mutex_t	m_pMutex;
#else
	CMutex* m_pMutex;
#endif

public:
	CYlsMutex()
	{
#ifdef HS_SUPPORT_UNIX
	pthread_mutex_init(&m_pMutex, NULL);
#else
	m_pMutex = new CMutex;
#endif
	}

	~CYlsMutex()
	{
#ifdef HS_SUPPORT_UNIX
	pthread_mutex_destroy(&m_pMutex);
#else
	if (m_pMutex)
	{
		delete m_pMutex;
		m_pMutex = NULL;
	}
#endif
	}

	int Lock()
	{
#ifdef HS_SUPPORT_UNIX
		return Yls_pthread_mutex_lock(&m_pMutex);
#else
		m_pMutex->Lock();
#endif
	    return 0;
	}

	int UnLock()
	{
#ifdef HS_SUPPORT_UNIX
		return pthread_mutex_unlock(&m_pMutex);
#else
		m_pMutex->Unlock();
#endif
		return 0;
	}

	//friend CYlsMutexLock;
};

// lock/unlock
class CYlsMutexLock
{
protected:
	CYlsMutex* m_pMutex;

#ifndef HS_SUPPORT_UNIX
	CSingleLock* m_pLock;
#endif

public:
	CYlsMutexLock(CYlsMutex *pMutex)
	{
		if( pMutex == NULL )
		{
			m_pMutex = NULL;
			return;
		}

		m_pMutex = pMutex;

#ifdef HS_SUPPORT_UNIX
		Yls_pthread_mutex_lock(&m_pMutex->m_pMutex);
#else
		m_pLock = new CSingleLock(m_pMutex->m_pMutex);
		m_pLock->Lock();
#endif
	}

	~CYlsMutexLock()
	{
		if( m_pMutex == NULL )
			return;

#ifdef HS_SUPPORT_UNIX
		pthread_mutex_unlock(&m_pMutex->m_pMutex);
#else
		m_pLock->Unlock();
		delete m_pLock;
#endif
	}
};

struct DFX_ParamArray
{
	CYlsArray<CHqDataBufferArray_Dfx*,CHqDataBufferArray_Dfx*> ay;

	DFX_ParamArray()
	{
	}

	~DFX_ParamArray()
	{
		_delArrayObj(ay);
	}	

};

// �������
typedef CYlsArray<CHqDataBufferArray_Dfx*,CHqDataBufferArray_Dfx*> DFX_Param;

class CSaveParam_Dfx
{
protected:
	static CYlsMapStringToPtr m_map;
	static CYlsMutex		  m_pSessionMutex;

public:
	CSaveParam_Dfx();
	~CSaveParam_Dfx();

	static int		  Add(CHqDataBuffer* buffer,DFX_Param* pParam);
	static DFX_Param* Get(CHqDataBuffer* buffer);


	static int		  GetCount() { return m_map.GetCount(); }
};

#ifndef HS_SUPPORT_UNIX
class CYlsCriticalSection
{
protected:
	CCriticalSection* m_pSect;
public:
	CYlsCriticalSection(CCriticalSection* pSect)
	{
		m_pSect = pSect;
		m_pSect->Lock();
	}
	~CYlsCriticalSection()
	{
		if( m_pSect == NULL )
			return;
		m_pSect->Unlock();
	}
};
#endif


// ������Ϣ
struct UnixProcessStatus
{
	int UID;
	int PID;
	int	PPID;
	int C;
	int STIME;
	int TTY;
	int TIME;
	int CMD;

	UnixProcessStatus()
	{
		memset(this,-1,sizeof(UnixProcessStatus));
	}
};

struct UnixProcessData
{
	CHqDataBuffer UID;
	CHqDataBuffer PID;
	CHqDataBuffer PPID;
	CHqDataBuffer C;
	CHqDataBuffer STIME;
	CHqDataBuffer TTY;
	CHqDataBuffer TIME;
	CHqDataBuffer CMD;
};
				  
// �˿���Ϣ
struct UnixListenPortStatus
{
	int Proto;
	int Recv_Q;
	int Send_Q;
	int LocalAddress;
	int ForeignAddress;
	int State;
	int PID_Programname;

	UnixListenPortStatus()
	{
		memset(this,-1,sizeof(UnixListenPortStatus));
	}
};

struct UnixListenPortData
{
	CHqDataBuffer Proto;
	CHqDataBuffer Recv_Q;
	CHqDataBuffer Send_Q;
	CHqDataBuffer LocalAddress;
	CHqDataBuffer ForeignAddress;
	CHqDataBuffer State;
	CHqDataBuffer PID_Programname;
};

struct FileUserInfo
{
	CHqDataBuffer	   m_szSrc;
	CHqDataBuffer	   m_szPath;
	CHqDataBuffer	   m_szDate;
	CHqDataBuffer	   m_szName;
	CHqDataBufferArray m_ayItem;
};


// map���� --- ɾ��map��������
template<class YLS_MAP_NAME, class YLS_KEY, class YLS_VALUE>
void YlsMapDelAll( YLS_MAP_NAME& map,YLS_KEY key,YLS_VALUE value )
{
	POSITION  pos;
	for( pos = map.GetStartPosition(); pos != NULL; )
	{
		map.GetNextAssoc( pos, key, value );
		if( value )
		{
			delete value;
		}
	}
	map.RemoveAll();
}

// map���� --- map add
template<class YLS_MAP_NAME, class YLS_KEY, class YLS_VALUE>
void* YlsMapAdd( YLS_MAP_NAME& map,YLS_KEY key,YLS_VALUE value )
{
	YLS_VALUE oldValue;
	if( map.Lookup(key,oldValue) )
	{
		return oldValue;
	}
	map.SetAt(key,value);

	return value;
}

// map���� --- map add
template<class YLS_MAP_NAME, class YLS_KEY, class YLS_VALUE>
void* YlsMapAdd( YLS_MAP_NAME& map,YLS_KEY key,YLS_VALUE value,BOOL bAutoDelete )
{
	YLS_VALUE oldValue;
	if( map.Lookup(key,oldValue) )
	{
		if( bAutoDelete )
		{
			delete value;
		}
		return oldValue;
	}
	map.SetAt(key,value);

	return value;
}

// map���� --- map del
template<class YLS_MAP_NAME, class YLS_KEY, class YLS_VALUE>
int YlsMapDel( YLS_MAP_NAME& map,YLS_KEY key )
{
	YLS_VALUE oldValue;
	if( map.Lookup(key,oldValue) )
	{
		map.RemoveKey(key);
		delete oldValue;
		return 1;
	}

	return 0;
}

#endif
