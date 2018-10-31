#include "StdAfx.h"
#include "Share.h"

CShare g_Share;

CShare::CShare(void)
{
	m_bCrc = false;
}

CShare::~CShare(void)
{
}

void CShare::Initialize()
{
	SetSysPath();

	SetUpdateName();

	SetMainExeName();

	SetCrcFlag();
}

CString CShare::GetUpdate1Name( void ) const
{
	return m_csUpdate1Name;
}

CString CShare::GetUpdate2Name( void ) const
{
	return m_csUpdate2Name;
}

void CShare::SetUpdateName( void )
{
	// 由于主程序会调用到update1，所以将update1写到配置文件中。
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString( "Update", "Update1", "", buf, sizeof(buf), GetUpdateIniPath() );
	if( strcmp(buf, "") == 0 )
	{
		m_csUpdate1Name = _T("Update.exe");
	}
	else
	{
		m_csUpdate1Name = buf;

		// 去掉后面的启动参数
		int nPos = m_csUpdate1Name.Find(" ");
		if( nPos != -1 )
			m_csUpdate1Name = m_csUpdate1Name.Left(nPos);
	}

#ifdef _VERSION_GF
	m_csUpdate2Name =  _T("FlashTraderUpdate2.exe");
#else
	m_csUpdate2Name =  _T("CustomWindowUpdate2.exe");
#endif
}


CString CShare::GetTitle( void ) const
{
#ifdef _VERSION_GF
	return "快金升级程序";
#else
	return "升级程序";
#endif
}

void CShare::SetSysPath( void )
{
	TCHAR exeFullPath[MAX_PATH];
	memset(exeFullPath, 0, MAX_PATH);
	GetModuleFileName(AfxGetInstanceHandle(), exeFullPath, MAX_PATH);
	m_csSysPath    = (CString)exeFullPath;  //更新程序exe文件的完整目录，到时候exe文件放在系统的根目录
	int position    = m_csSysPath.ReverseFind('\\');
	m_csSysPath    = m_csSysPath.Left(position + 1);//exe文件所在目录，也就是系统根目录
}

CString CShare::GetSysPath( void ) const
{
	return m_csSysPath;
}

CString CShare::GetCallAppStrPath( void ) const
{
	// 读取配置文件，获取启动主程序的参数
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString("Update", "CallAppStr", "", buf, sizeof(buf), m_csSysPath + UPDATE_INI_NAME);

	// 如果为空，则默认和主程序名称一样
	if( strcmp(buf, "") == 0 )
	{
		return m_csSysPath + m_csMainExeName;
	}
	else
	{
		CString strTemp = buf;
		return m_csSysPath + strTemp;
	}
}

void CShare::SetMainExeName( void )
{
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString( "Update", "AppName", "", buf, sizeof(buf), GetUpdateIniPath() );
	m_csMainExeName = buf;
}

CString CShare::GetUpdateIniPath( void ) const
{
	return m_csSysPath + UPDATE_INI_NAME;
}

CString CShare::GetMainExeName( void ) const
{
	return m_csMainExeName;
}

CString CShare::GetTempPath( void ) const
{
	return m_csSysPath + TEM_FOLDER_NAME2 + "\\";
}

void CShare::SetCrcFlag( void )
{
	// 默认是采取crc加密的
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString( "Update", "CheckCrc", "", buf, sizeof(buf), GetUpdateIniPath() );

	if( strcmp(buf, "") == 0 ) // 仅仅该字段为“0”的时候才不采取Crc校验
		m_bCrc = false;
	else
		m_bCrc = true;
	
}

bool CShare::IsCheckCrc( void ) const
{
	return m_bCrc;
}
