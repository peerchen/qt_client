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

	// 获取升级临时目录
	CString GetTempPath( void ) const;

	bool IsCheckCrc( void ) const;

	// 获取窗口标题文字
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

	CString m_csMainExeName; // 主进程的名称

	bool m_bCrc; // 升级文件是否采用了Crc加密
};

extern CShare g_Share;
