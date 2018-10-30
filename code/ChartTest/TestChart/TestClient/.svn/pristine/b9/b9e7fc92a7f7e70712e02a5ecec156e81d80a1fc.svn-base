
#ifndef	__CYlsIniFile_H
#define	__CYlsIniFile_H

#include "stdafx.h"

class CYlsIniFile
{
private:
	FILE	*fp;
	char	m_szFileName[_MAX_PATH];
public:
	CYlsIniFile();
	CYlsIniFile(char *pszName);

	//virtual ~CYlsIniFile();
	~CYlsIniFile() { };
	int		ReadString(const char *pSection, const char *pName, const char *pDefaultValue, char *pResult, int nLimit = 256);
	float	ReadFloat(const char *pSection, const char *pName, const float fDefaultValue, float *fResult);
	int		ReadInteger(const char *pSection, const char *pName, const int nDefaultValue, int *nResult);
	int		WriteString(const char *pSection, const char *pName, char *pValue); 

//	int	Gets(char *szContent, char *szBuf, int lineno);
//	int	Puts(char *szContent, char *szBuf, int lineno);
};

#endif
