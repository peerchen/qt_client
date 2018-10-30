#pragma once


#include "../comm/programstatus.h"


class CDogInfoFile
{
public:
	CDogInfoFile(void);
	virtual ~CDogInfoFile(void);

protected:
	CString m_strAll;
	CString m_strValue;
	CString m_strTitle;

	CFile	m_fp;
	CString m_strData;

public:

	static void SetFileName(CString strPath,int nPort = 0);
	static char g_strInfoFileName[256];
	static char g_strInfoPath[256];

	/*static HS_EveryTimeData m_sEvery;*/
	static char  g_strReportInfoFile[256];
	static CFile g_fpReportInfo;
	static void  WriteReport();

	static CString GetCurDiskFreeSpace(CString strFileName);

	static void    GetRootFile();


	int     GetSysInfo(CString strFileName);

	virtual int	GetCurSysInfo(CString strData);

	CString AddItem(CString strTitle,CString strValue);
	void	Add(CString strTitle,CString strValue);
	void    AddTableItem(CString strValue);


	int		Write(CString strFileName,CString strData);

	BOOL    CpuUsage2000(long *plResult);

};
