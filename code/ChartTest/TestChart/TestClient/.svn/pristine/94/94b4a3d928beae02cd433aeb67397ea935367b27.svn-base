#include "StdAfx.h"
#include ".\doginfofile.h"

#include "SysInfo.h"
#include "winbase.h"

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <math.h>
#include <sys\stat.h>

static const int File_Max_length = 1024*1024*5;

char  CDogInfoFile::g_strInfoFileName[256];
char  CDogInfoFile::g_strInfoPath[256];

char  CDogInfoFile::g_strReportInfoFile[256];
CFile CDogInfoFile::g_fpReportInfo;
//HS_EveryTimeData m_sEvery;

extern HS_EveryTimeData m_sEvery;

CDogInfoFile::CDogInfoFile(void)
{
	// 项定义
	m_strAll = "<font size=5>%s</font><BR><font size=-1>%s</font><br>";
	m_strValue = "<font size=-1>%s</font><br>";
	m_strTitle = "<font size=5>%s</font><BR>";

	strcpy(g_strInfoPath,"C:\\sysInfoData\\");
	if (_access(g_strInfoPath, 0) != 0)
	{
		_mkdir(g_strInfoPath);
	}
}

void CDogInfoFile::GetRootFile()
{
	char strPath[_MAX_PATH];
	strncpy(strPath,g_strInfoPath,sizeof(strPath));
	strcat(strPath,"*.htm");

	CFileFind find;

	char strFileName[_MAX_PATH];
	strncpy(strFileName,g_strInfoPath,sizeof(strFileName));
	strcat(strFileName,"info.htm");

	CFile fp;
	if( !fp.Open(strFileName,CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeBinary) )
	{
		return;
	}

	static char* szItem = "<a href=\"/%s\"> %s <br>";

	// 由指定目录，装入市场分类信息
	BOOL bContinue = find.FindFile(strPath);
	while(bContinue)
	{
		bContinue   = find.FindNextFile();
		if( find.IsDots() || find.IsDirectory() )
			continue;

		sprintf(strFileName,szItem,find.GetFileName(),find.GetFileName());

		fp.Write(strFileName,strlen(strFileName));
	}

	fp.Close();
}

void CDogInfoFile::SetFileName(CString strPath,int nPort /*= 0*/)
{
	char strCurrentPath[_MAX_PATH];
	GetModuleFileName( AfxGetInstanceHandle(),
		strCurrentPath, _MAX_PATH );

	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath( strCurrentPath, NULL, NULL, fname, ext );

	sprintf(CDogInfoFile::g_strInfoFileName,"%s%s_%i.htm",
		g_strInfoPath, fname, nPort);

	if( !strPath.IsEmpty() )
	{
		sprintf(CDogInfoFile::g_strReportInfoFile,"%sEveryReport",strPath);

		memset(&m_sEvery,0,sizeof(m_sEvery));
	}
}

void CDogInfoFile::WriteReport()
{
	if( g_fpReportInfo.m_hFile == INVALID_HANDLE_VALUE )
	{
		if( g_fpReportInfo.m_hFile == INVALID_HANDLE_VALUE && 
			!g_fpReportInfo.Open(g_strReportInfoFile,CFile::modeReadWrite | CFile::shareDenyNone | 
								CFile::modeCreate | CFile::modeNoTruncate | CFile::typeBinary ) )
		{
			g_fpReportInfo.m_hFile = INVALID_HANDLE_VALUE;
			return;
		}
	}

	int nLen = g_fpReportInfo.GetLength();
	if( nLen > File_Max_length )
	{
		g_fpReportInfo.SetLength(0);
	}
	g_fpReportInfo.SeekToEnd();
	g_fpReportInfo.Write(&m_sEvery,sizeof(m_sEvery));
	m_sEvery.m_sFlux.Empty();
}

CDogInfoFile::~CDogInfoFile(void)
{
}

CString CDogInfoFile::AddItem(CString strTitle,CString strValue)
{
	CString strRet;
	if( strTitle.IsEmpty() )
		strRet.Format(m_strValue,strValue);
	else if( strValue.IsEmpty() )
		strRet.Format(m_strTitle,strTitle);
	else
		strRet.Format(m_strAll,strTitle, strValue);
	return strRet;
}

int CDogInfoFile::Write(CString strFileName,CString strData)
{
	if( strFileName.IsEmpty() || strData.IsEmpty() )
		return 0;

	if( m_fp.m_hFile == INVALID_HANDLE_VALUE && 
		!m_fp.Open(strFileName,CFile::modeReadWrite | CFile::shareDenyNone | 
				CFile::modeCreate | CFile::typeBinary ) )
	{
		return 0;
	}

	m_fp.SetLength(0);
	m_fp.Write((const char*)strData,strData.GetLength());	

	return 1;
}

void CDogInfoFile::Add(CString strTitle,CString strValue)
{
	m_strData += AddItem(strTitle,strValue);
}

void  CDogInfoFile::AddTableItem(CString strValue)
{
	m_strData += strValue;
}

int	CDogInfoFile::GetCurSysInfo(CString strData)
{
	CString strTemp;

	strData += AddItem("运行正常","");

	char szName[MAX_COMPUTERNAME_LENGTH + 1];
	memset(szName,0,MAX_COMPUTERNAME_LENGTH + 1);
	DWORD nLen = sizeof(szName);
	if( ::GetComputerName(szName,&nLen) )
		strData += AddItem("机器名称：",szName);

	CSysInfo si;
	si.SetShowLoopback(TRUE);
	si.Init(TRUE);

	strTemp.Format(_T(" = %dM"),si.GetTotalPhys()/1048576);
	strData += AddItem("Total size of physical memory：",strTemp);

	m_sEvery.m_srv.m_lMemTotal = si.GetTotalPhys()/1048576;

	strTemp.Format(_T(" = %dM"),si.GetAvailPhys()/1048576);
	strData += AddItem("Size of physical memory available：",strTemp);

	m_sEvery.m_srv.m_lMemVar = si.GetAvailPhys()/1048576;

	//
	strData += m_strData;
	m_strData.Empty();

	CTime tm = CTime::GetCurrentTime();	

	m_sEvery.m_lTime = tm.GetTime();

	strTemp.Format( "%04d年%02d月%02d日-%02d时%02d分%02d秒",tm.GetYear(),tm.GetMonth(),tm.GetDay(),
		tm.GetHour(),tm.GetMinute(),tm.GetSecond() );
	strData += AddItem("更新时间：",strTemp);

	return Write(g_strInfoFileName,strData);
}

CString CDogInfoFile::GetCurDiskFreeSpace(CString strFileName)
{
	// 磁盘空间
	CString strTemp;
	CString strRoot;
	//AfxGetRoot(strFileName, strRoot);
	int nIndex = strFileName.Find(":");
	if( nIndex == -1 )
		return strTemp; 

	strRoot = strFileName.Left(nIndex);
	strRoot += ":\\";

	DWORD dwSecPerClus, dwBytesPerSec, dwFreeClus, dwTotalClus;
	double long nBytes = 0;
	if (GetDiskFreeSpace(strRoot, &dwSecPerClus, &dwBytesPerSec, &dwFreeClus,
		&dwTotalClus))
	{
		nBytes = (double long)dwFreeClus*dwSecPerClus*dwBytesPerSec;
		strTemp.Format(_T(" = %.2fM"),nBytes/1048576);
	}

	return strTemp;
}

int CDogInfoFile::GetSysInfo(CString strFileName)
{
	if( strFileName.IsEmpty() )
		strFileName = g_strInfoFileName;
	if( strFileName.IsEmpty() )
		return 0;

	CSysInfo si;
	si.SetShowLoopback(TRUE);
	si.Init();

	int n,k,i;

	CString strTemp;

	CString strData;
	strData += AddItem("操作系统名称：",si.GetOSType());

	strTemp.Format(_T(" %d Speed = %d %s %s %s"),si.GetNumProcessors(),si.GetCPUSpeed(),
		si.GetCPUIdentifier(),si.GetCPUVendorIdentifier(),si.GetCPUNameString());
	strData += AddItem("CPUs：",strTemp);

	//long lCpu;
	//if( CpuUsage2000(&lCpu) )
	//{
	//	strTemp.Format("%i",lCpu);
	//	strData += AddItem("当前CPU利用率：",strTemp);
	//}

	strTemp.Format(_T(" = %dM"),si.GetTotalPhys()/1048576);
	strData += AddItem("Total size of physical memory：",strTemp);

	strTemp.Format(_T(" = %dM"),si.GetAvailPhys()/1048576);
	strData += AddItem("Size of physical memory available：",strTemp);

	strTemp.Format(_T(" %d.%d.%d.%d"),si.GetIEMajor(),si.GetIEMinor(),si.GetIEBuild(),si.GetIESomething());
	strData += AddItem("IE version：",strTemp);

	strTemp.Format(_T(" %d.%d.%d.%d"),si.GetADOMajor(),si.GetADOMinor(),
		si.GetADOBuild(),si.GetADOSomething());
	strData += AddItem("ADO version：",strTemp);

	strTemp.Format(_T("User = %s (Admin rights = %d)"),si.GetLoginUserName(),si.IsUserAdmin());
	strData += AddItem("User/Admin rights：",strTemp);

	DWORD dwSpeed, dwStatus;
	CString p,str;

	strTemp.Empty();
	for (i = 0;i < si.GetAPINumAdapters();i++)
	{
		p.Empty();
		for(k = 0;k < si.GetAPINumAddresses(i);k++)
		{
			p += si.GetAPIAdapterIPStr(i,k);
			p += _T("/");

			p += si.GetAPIAdapterMaskStr(i,k);
			p += _T(" ");
		}

		si.GetAPIAdapterSpeedStatus(i,&dwSpeed,&dwStatus);
		if (dwSpeed >= 1000000)
		{
			str.Format(_T("%d %s Speed = %dM Status = %d %s"),i,
				si.GetAPIAdapterDescr(i),
				dwSpeed/1000000,dwStatus,p);
		}
		else
		{
			str.Format(_T("%d %s Speed = %d Status = %d %s"),i,
				si.GetAPIAdapterDescr(i),
				dwSpeed,dwStatus,p);
		}

		if( !strTemp.IsEmpty() )
			strTemp += "<br>";
		strTemp += str;
	}
	strData += AddItem("NIC list of this computer obtained with Iphlpapi：",strTemp);

	BYTE a1,a2,a3,a4;
	strTemp.Empty();
	for (i = 0;i < si.GetMIBAddresses();i++)
	{
		DWORD dw = si.GetMIBIP(i);
		a1 = (BYTE)((dw>>24) & 0xFF);
		a2 = (BYTE)((dw>>16) & 0xFF);
		a3 = (BYTE)((dw>>8) & 0xFF);
		a4 = (BYTE)(dw & 0xFF);
		p.Format(_T("%d.%d.%d.%d "),a1,a2,a3,a4);
		if( !strTemp.IsEmpty() )
			strTemp += "<br>";
		strTemp += p;
	}
	strData += AddItem("IP addresses of this computer obtained with MIB：",strTemp);

	strTemp.Empty();
	TCHAR szIP[50],szMask[50];
	for(i = 0;i < si.GetMIBNumAdapters();i++)
	{
		si.GetMIBAdapterIPStr(i,szIP);
		si.GetMIBAdapterMaskStr(i,szMask);
		n = si.GetMIBAdapterSpeed(i);
		if (n >= 1000000)
		{
			p.Format(_T("%d %s Speed = %dM Status = %d Type = %d %s %s"),
				i,si.GetMIBAdapterDescr(i),
				si.GetMIBAdapterSpeed(i)/1000000,
				si.GetMIBAdapterOperStatus(i),
				si.GetMIBAdapterType(i),
				szIP,szMask);
		}
		else
		{
			p.Format(_T("%d %s Speed = %d Status = %d Type = %d %s %s"),
				i,si.GetMIBAdapterDescr(i),
				si.GetMIBAdapterSpeed(i),
				si.GetMIBAdapterOperStatus(i),
				si.GetMIBAdapterType(i),
				szIP,szMask);
		}

		if( !strTemp.IsEmpty() )
			strTemp += "<br>";
		strTemp += p;
	}
	strData += AddItem("NIC list of this computer obtained with MIB：",strTemp);

	return Write(strFileName,strData);

}

// ------------------------------------------------------------------------------------------------
// WindowsNT/2000下CPU使用率
#define SystemBasicInformation       0
#define SystemPerformanceInformation 2
#define SystemTimeInformation        3

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

typedef struct
{
    DWORD   dwUnknown1;
    ULONG   uKeMaximumIncrement;
    ULONG   uPageSize;
    ULONG   uMmNumberOfPhysicalPages;
    ULONG   uMmLowestPhysicalPage;
    ULONG   uMmHighestPhysicalPage;
    ULONG   uAllocationGranularity;
    PVOID   pLowestUserAddress;
    PVOID   pMmHighestUserAddress;
    ULONG   uKeActiveProcessors;
    BYTE    bKeNumberProcessors;
    BYTE    bUnknown2;
    WORD    wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
    LARGE_INTEGER   liIdleTime;
    DWORD           dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
    LARGE_INTEGER liKeBootTime;
    LARGE_INTEGER liKeSystemTime;
    LARGE_INTEGER liExpTimeZoneBias;
    ULONG         uCurrentTimeZoneId;
    DWORD         dwReserved;
} SYSTEM_TIME_INFORMATION;


typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

PROCNTQSI NtQuerySystemInformation;

BOOL CDogInfoFile::CpuUsage2000(long *plResult)
{
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
    SYSTEM_TIME_INFORMATION        SysTimeInfo;
    SYSTEM_BASIC_INFORMATION       SysBaseInfo;
    double                         dbIdleTime;
    double                         dbSystemTime;
    LONG                           status;
	static LARGE_INTEGER           liOldIdleTime = {0,0};
    static LARGE_INTEGER           liOldSystemTime = {0,0};

    NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(
                                          GetModuleHandle("ntdll"),
                                         "NtQuerySystemInformation"
                                         );

    if (!NtQuerySystemInformation)
        return S_FALSE;

    // 得到系统中处理器数
    status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL);
    if (status != NO_ERROR)
        return S_FALSE;
    
    // 得到新的系统时间
    status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);
    if (status!=NO_ERROR)
        return S_FALSE;

    // 得到新的CPU空闲时间
    status = NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
    if (status != NO_ERROR)
        return S_FALSE;

    // 如果第一次调用跳过
    if (liOldIdleTime.QuadPart != 0)
    {
        // 当前值 = 最新值 - 旧值
        dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime);
        dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime);

        // 当前CPU空闲时间 = 空闲时间 / 系统时间
        dbIdleTime = dbIdleTime / dbSystemTime;

        // 当前CPU利用率% = 100 - (当前CPU空闲时间 * 100) / 处理器数
        dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.bKeNumberProcessors + 0.5;

        *plResult = (UINT)dbIdleTime;
    }

    // 存储新的CPU空闲及系统时间
    liOldIdleTime = SysPerfInfo.liIdleTime;
    liOldSystemTime = SysTimeInfo.liKeSystemTime;

	return S_OK;
}
