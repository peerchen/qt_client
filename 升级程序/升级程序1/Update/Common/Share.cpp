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
	// �������������õ�update1�����Խ�update1д�������ļ��С�
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString( "Update", "Update1", "", buf, sizeof(buf), GetUpdateIniPath() );
	if( strcmp(buf, "") == 0 )
	{
		m_csUpdate1Name = _T("Update.exe");
	}
	else
	{
		m_csUpdate1Name = buf;

		// ȥ���������������
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
	return "�����������";
#else
	return "��������";
#endif
}

void CShare::SetSysPath( void )
{
	TCHAR exeFullPath[MAX_PATH];
	memset(exeFullPath, 0, MAX_PATH);
	GetModuleFileName(AfxGetInstanceHandle(), exeFullPath, MAX_PATH);
	m_csSysPath    = (CString)exeFullPath;  //���³���exe�ļ�������Ŀ¼����ʱ��exe�ļ�����ϵͳ�ĸ�Ŀ¼
	int position    = m_csSysPath.ReverseFind('\\');
	m_csSysPath    = m_csSysPath.Left(position + 1);//exe�ļ�����Ŀ¼��Ҳ����ϵͳ��Ŀ¼
}

CString CShare::GetSysPath( void ) const
{
	return m_csSysPath;
}

CString CShare::GetCallAppStrPath( void ) const
{
	// ��ȡ�����ļ�����ȡ����������Ĳ���
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString("Update", "CallAppStr", "", buf, sizeof(buf), m_csSysPath + UPDATE_INI_NAME);

	// ���Ϊ�գ���Ĭ�Ϻ�����������һ��
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
	// Ĭ���ǲ�ȡcrc���ܵ�
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString( "Update", "CheckCrc", "", buf, sizeof(buf), GetUpdateIniPath() );

	if( strcmp(buf, "") == 0 ) // �������ֶ�Ϊ��0����ʱ��Ų���ȡCrcУ��
		m_bCrc = false;
	else
		m_bCrc = true;
	
}

bool CShare::IsCheckCrc( void ) const
{
	return m_bCrc;
}
