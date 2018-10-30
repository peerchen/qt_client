
#ifndef	__YlsLOG_H
#define	__YlsLOG_H

class CYlsLog
{
public:
	CYlsLog();
	CYlsLog(const char *pszName, int nLogMode = 0/*UDBG_FIFO*/, int nPort = 0, int nFileMode = 0666);
	~CYlsLog();

	int 	Log(const char *pszFormat, ...);
	int 	Log(const char *pszFileName, int nLineNo, const char *pszFormat, ...);
};

#endif
