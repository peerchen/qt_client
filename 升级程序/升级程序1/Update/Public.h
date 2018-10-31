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

// added by Ben  ϵͳ�汾��Ϣ
#define UPPER_VISTA 1
#define BELOW_VISTA 0
// end add

#define UPDATE_SYSTEM_VERSION  2 // ϵͳ�汾��

struct FileInfo
{
	CString strName; //�ļ�·��
	bool isDownLoad; //�Ƿ��Ѿ����سɹ�
	//int iType;       //0��ӣ�1ɾ����2�޸� 
};

class CPublic  
{
private:
	CPublic();
	virtual ~CPublic();
public:
	//////////////////////////////////////////////////////////////////////////
	//Singlonģʽ
	static void ExitInstance();
	static CPublic* Instance();

public://���ӿ�
	BOOL RunFileExe(CString fileName);
	CString GetTempPath();
	CString GetSysPath();                    // ���ܣ���ȡϵͳ·��
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
	void SplitStrToVector( CString &Str, CString SplitWord , vector<CString> &Vec);//��splitwordΪ�ָ��������ַ���str�е��ַ����ָ��vec;

	void WriteLog( const CString &sMsg);
};

#endif // !defined(AFX_PUBLIC_H__46EB9686_9686_4BA1_83CB_30DC63F345E0__INCLUDED_)
