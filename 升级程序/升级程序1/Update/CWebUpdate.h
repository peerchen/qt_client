// CWebUpdate.h : header file
//

#ifndef _CWEBUPDATE_H
#define _CWEBUPDATE_H

#include "XmlDocument.h"
#define WM_MAILNEWS WM_USER + 500 
#include "winsock2.h"
#include <afxinet.h>

#include <vector>
using namespace std;

struct UpdateFileStru
{
	CString strFileName; // 文件名（不是根目录的话包括路径）
	CString strDate;     // 更新日期
};


class CWebUpdate
{
public:
	CWebUpdate();
	~CWebUpdate();
    
	// 根据本地升级配置文件，获取连接服务器的相关信息和本地版本号以及代理信息
	void InitUpdate(); 
    // 首先通过Ini文件对比版本号，如果需要更新，则调用CheckUpdateFile函数来获取要下载的文件信息
	int CheckUpdate();
	// 通过对比xml文件，如果需要更新则将需要下载的文件信息添加到类变量（把xml的下载放到这里去了，有点乱，有时间纠正）
	BOOL CheckUpdateFile();
	// 根据一个文件名称将一个文件下载到缓冲区并将缓冲区的文件写入到临时目录
	bool HttpDownloadFiles(CString strFileName);
	// 将一个文件下载到缓冲区，由HttpDownloadFiles函数调用
	BOOL ConnectServerFile(CString UpdateFile,CHttpConnection *pHttp = NULL);
	// 从缓冲区写入到临时目录
	void  WriteBufferToTemp(const CString &strFileName);
	// 将升级xml的信息加载到Vector
	void LoadXMLToVec(vector<UpdateFileStru> &vecFile, CString &strFilePath);
	// 通过比较客户端和服务端的xml文件，加载要下载的文件的信息
	void GetDownLoadFile(const vector<UpdateFileStru> &vecClient, const vector<UpdateFileStru> &vecServer);
	// 通过读取本地的ini文件，获取本地版本号
	CString GetClientVersion(void);

private:
	// 下载和服务器连接信息的声明
	DWORD m_dwType;
	CHttpFile* m_pFile;         // 下载文件
	DWORD m_dwHttpRequestFlags; // http请求类型
	INTERNET_PORT m_dwPort;     // 端口号
	CString m_strServer;        // 服务器
	CString m_ServerPath;       // 服务器文件路径
	
	CInternetSession m_cis;
	CHttpConnection *m_pHttp;
	CString m_strServerByDomain;
	CString m_strStatus;

private:
	float m_fVersion;         // 本地的版本号

	// 代理信息
	bool  m_bProxy;        // 是否需要代理
	char  m_cUserName[64]; // 代理登陆的用户名
	char  m_cPsw[64];      // 代理登陆的密码     
	bool  m_bLogon;        // 登陆代理时是否需要用户名和密码
public:
	CString m_strSerVersion;  // 服务器版本号
	vector<DLFileInfo> m_vecDLFiles; // 要下载的文件的清单

   
	
};

#endif
