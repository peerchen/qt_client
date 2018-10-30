
#ifndef _CYlsIni_H
#define _CYlsIni_H

#include "stdafx.h"

#include "ylsmapstringtoptr.h"
#include "ylstypedptrmap.h"
#include "tool.h"

#define Not_used

class SectionKey
{
public:
	SectionKey();
	~SectionKey();
public:
	CHqDataBuffer			m_szSection;
	CYlsMapStringToPtr		m_map;

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*>  m_ay;

	void AddKey(const char* szKey,void* pValue);
};

class CYlsIni
{
public:
	CYlsIni(char nWriteDefault = 0);
	virtual ~CYlsIni(void);

protected:	
	char m_szFileName[_MAX_PATH];
	CYlsArray<SectionKey*,SectionKey*> m_ay;
	CHqDataBuffer m_pResult;

	CHqDataBuffer* GetKey(const char *pSection, const char *pName,SectionKey*& pSectionKey);
	SectionKey*    GetSectionKey(const char *pSection);
	SectionKey*	   SetSectionKey(const char *pSection,BOOL bAdd = TRUE);


	char	m_nWriteDefault; // 写入缺省
	char    m_nIsOpenSucc;

	int		m_nWriteBufferCount; // 写入buffer个数

#ifndef	Not_used
	CYlsMutex	m_pMutex; // 
#endif

public:
	CYlsArray<SectionKey*,SectionKey*>* GetKeyArray() { return &m_ay; }

public:
	int		Open(const char* szFileName);
	int		Write(char* szFileName = NULL);
	int		AutoWrite();
	void	Free();	

	int     IsOpen();
public:		
	char*	ReadString(const char *pSection, const char *pName, const char *pDefaultValue = "");
	int		WriteString(const char *pSection, const char *pName, const char *pValue); 
	int		ReadInteger(const char *pSection, const char *pName, const int nDefaultValue);
	int		WriteInteger(const char *pSection, const char *pName, int nValue);

	char* GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,LPCTSTR lpszDefault = "")
	{
		return	ReadString(lpszSection,lpszEntry,lpszDefault);
	}

	BOOL WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,LPCTSTR lpszValue)
	{
		return WriteString(lpszSection,lpszEntry,lpszValue);
	}

	int GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault)
	{
		return ReadInteger(lpszSection,lpszEntry,nDefault);
	}

	BOOL WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue)
	{
		return WriteInteger(lpszSection,lpszEntry,nValue);
	}

	int ReadConfigSectionString(const char* strSection,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& strKeyArray,CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* pValueArray = NULL);

public:
	int GetBuffer(CHqDataBuffer* buffer);

};

#endif
