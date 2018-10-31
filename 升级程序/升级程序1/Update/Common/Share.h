#pragma once

#define UPDATE_INI_NAME _T("Update.ini")
#define TEM_FOLDER_NAME2 "update"

class CShare
{
public:
	CShare(void);
public:
	~CShare(void);

	void Initialize();

	CString GetUpdate1Name( void ) const;

	CString GetUpdate2Name( void ) const;

	CString GetSysPath( void ) const;

	CString GetCallAppStrPath( void ) const;

	CString GetMainExeName( void ) const;

	// ��ȡ������ʱĿ¼
	CString GetTempPath( void ) const;

	bool IsCheckCrc( void ) const;

	// ��ȡ���ڱ�������
	CString GetTitle( void ) const;

private:
	void SetUpdateName( void );

	void SetSysPath( void );

	void SetMainExeName( void );

	CString GetUpdateIniPath( void ) const;

	void SetCrcFlag( void );

private:
	CString m_csSysPath;

	CString m_csUpdate1Name;

	CString m_csUpdate2Name;

	CString m_csMainExeName; // �����̵�����

	bool m_bCrc; // �����ļ��Ƿ������Crc����
};

extern CShare g_Share;
