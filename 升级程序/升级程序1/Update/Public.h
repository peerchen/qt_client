// Public.h: interface for the CPublic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBLIC_H__46EB9686_9686_4BA1_83CB_30DC63F345E0__INCLUDED_)
#define AFX_PUBLIC_H__46EB9686_9686_4BA1_83CB_30DC63F345E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

// added by Ben  系统版本信息
#define UPPER_VISTA 1
#define BELOW_VISTA 0
// end add

#define UPDATE_SYSTEM_VERSION  2 // 系统版本号

struct FileInfo
{
	CString strName; //文件路径
	bool isDownLoad; //是否已经下载成功
	//int iType;       //0添加，1删除，2修改 
};

class CPublic  
{
private:
	CPublic();
	virtual ~CPublic();
public:
	//////////////////////////////////////////////////////////////////////////
	//Singlon模式
	static void ExitInstance();
	static CPublic* Instance();

public://外界接口
	BOOL RunFileExe(CString fileName);
	CString GetTempPath();
	CString GetSysPath();                    // 功能：获取系统路径
	CString GetUpdateIniPath();
	BOOL DirectoryExist(CString Path);
	BOOL FileExist(CString FileName);
	BOOL DeleteDirectory(CString Path);
	BOOL MoveFiles(CString Sou, CString Des);

	DWORD FindAppProcessID(CString strsoft);
	bool CheckCrc(CString filepath);
	void Makefileexist(CString filepath);

private:
	void InitSysPath();
	CString m_strSysPath; 
	CString	m_szHostIP;
	static CPublic* _instance;

public:
	BOOL DeleteAllFiles(CString Foler1);
	bool MakeFolderExist( const CString &folderpath );
	bool MakeDirAllExist(CString strFolderPath);
	void SplitStrToVector( CString &Str, CString SplitWord , vector<CString> &Vec);//以splitword为分隔符，将字符串str中的字符串分割进vec;

	void WriteLog( const CString &sMsg);
};

#endif // !defined(AFX_PUBLIC_H__46EB9686_9686_4BA1_83CB_30DC63F345E0__INCLUDED_)
