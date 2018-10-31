// CWebUpdate.cpp : implementation file
//

#include "stdafx.h"
#include "CWebUpdate.h"
#include <sys/stat.h>
#include "Public.h"
#include ".\cwebupdate.h"
#include "Update.h"

CString remoteFile;
CString localFile;
HRESULT dloadResult;


CWebUpdate::CWebUpdate()
: m_strSerVersion(_T(""))
{
	m_pFile = NULL;

	m_bProxy = false;
	m_bLogon = false;

	memset(&m_cUserName, 0, sizeof(m_cUserName));
	memset(&m_cPsw,      0, sizeof(m_cPsw));

	m_dwHttpRequestFlags= INTERNET_FLAG_RELOAD	| INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_DONT_CACHE;
}
CWebUpdate::~CWebUpdate()
{
	if(m_pHttp != 0)
	{
		m_pHttp->Close();
	}
		
	//m_cis.Close();	
}

// 根据本地升级配置文件，初始化网络连接信息
void CWebUpdate::InitUpdate()
{
	// 读取本地升级配置的路径
	char buf[MAX_PATH] = {0};
	CString strPath = CPublic::Instance()->GetUpdateIniPath();

	// 获取客户端版本号
	::GetPrivateProfileString("Update", "VERSION", "0", buf, sizeof(buf), strPath);
	m_fVersion = (float)atof(buf); 

	// 获取升级目标地址ip
	::GetPrivateProfileString("Update", "IP","http:", buf,sizeof(buf), strPath);
	CString strIP = buf;

	DWORD dwType;
	AfxParseURL(strIP + CLI_UPDATE_INI_PATH, dwType, m_strServerByDomain, m_ServerPath, m_dwPort);	

	m_strServer = m_strServerByDomain;

	if(dwType != AFX_INET_SERVICE_HTTP)
	{
		strIP = "http://211.154.141.236/";
#ifdef _VERSION_XM
		strIP +="XM/";
#else
#ifdef _VERSION_WLMQ
		strIP +="WLMQ/";
#else
#ifdef _VERSION_YC
		strIP +="YC/";
#else
#ifdef  _VERSION_GF
		strIP +="GF/";
#else
		strIP +="gcn/";
#endif
#endif
#endif
#endif
		AfxParseURL(strIP + CLI_UPDATE_INI_PATH, dwType, m_strServerByDomain, m_ServerPath, m_dwPort);
		m_strServer = m_strServerByDomain;
		if (dwType != AFX_INET_SERVICE_HTTP)
		{
			AfxMessageBox(_T("update.ini文件内容出错"),MB_ICONSTOP);
			exit(0);
		}
	}

	m_dwType = dwType;
	m_cis.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 30000);      // 5秒的连接超时 
	m_pHttp = m_cis.GetHttpConnection(m_strServer,m_dwPort);
	CString strIniName = CLI_UPDATE_INI_PATH;
	m_ServerPath = m_ServerPath.Left(m_ServerPath.GetLength()-strIniName.GetLength());

	// 根据配置文件获取代理类型
	char cProxyType[2] = {0};
	strPath = CPublic::Instance()->GetSysPath() + "iconfig.ini";
	::GetPrivateProfileString("ICONFIG", "PROXYTYPE", "0", cProxyType, sizeof(cProxyType), strPath);

	// modified by Jerry Lee, 2011-3-24
	// begin
	int iProxy = atoi(cProxyType);
	if (iProxy > 0)  // 需要代理
	{
		// 需要代理
		m_bProxy = true;

		// 获取代理类型的名称
		char cProxyName[50] = {0};
		if(!strcmp(cProxyType, "1"))      // socks4
		{
			strcpy(cProxyName,"SOCKS=");   
		}
		else if(!strcmp(cProxyType, "2")) // socks4A
		{
			strcpy(cProxyName,"SOCKS=");   
		}
		else if(!strcmp(cProxyType, "3")) // socks5
		{
			strcpy(cProxyName,"SOCKS5=");   
		}
		else // http  if(!strcmp(cProxyType, "4"))
		{
			strcpy(cProxyName, "");   
		}

		char cProxyIp[MAX_PATH] = {0};
		char cProxyPort[10]  = {0}; 
		::GetPrivateProfileString("ICONFIG", "PROXYIP",   "", cProxyIp,   sizeof(cProxyIp),   strPath);
		::GetPrivateProfileString("ICONFIG", "PROXYPORT", "", cProxyPort, sizeof(cProxyPort), strPath);

		char strProxyInfo[MAX_PATH] = {0};
		sprintf(strProxyInfo, "%s%s:%s ", cProxyName, cProxyIp, cProxyPort);

		INTERNET_PROXY_INFO   proxyinfo; 
		proxyinfo.dwAccessType    =   INTERNET_OPEN_TYPE_PROXY; 
		proxyinfo.lpszProxy       =   strProxyInfo; 
		proxyinfo.lpszProxyBypass =   NULL; 
		m_cis.SetOption(INTERNET_OPTION_PROXY,   (LPVOID)&proxyinfo,   sizeof(INTERNET_PROXY_INFO)); 
	}
	else
	{
		// modified 20110922 以下操作导致死机
		//INTERNET_PROXY_INFO   proxyinfo; 
		//proxyinfo.dwAccessType    =   INTERNET_OPEN_TYPE_PRECONFIG; 
		////proxyinfo.lpszProxy       =   NULL; 
		//proxyinfo.lpszProxyBypass =   NULL; 
		//m_cis.SetOption(INTERNET_OPEN_TYPE_PRECONFIG, (LPVOID)&proxyinfo,   sizeof(INTERNET_PROXY_INFO));
		return;
	}
	// end

	// 如果需要使用代理
	if(m_bProxy) 
	{
		// 读取用户名和密码
		char cLogon[2]= {0};
		::GetPrivateProfileString("ICONFIG", "PROXYLOGON", "0", cLogon,  sizeof(cLogon),  strPath);
		if (!strcmp(cLogon, "1")) 
		{
			m_bLogon = true;
			::GetPrivateProfileString("ICONFIG", "PROXYUSER", "", m_cUserName,  sizeof(m_cUserName),  strPath);
			::GetPrivateProfileString("ICONFIG", "PROXYPASS", "", m_cPsw,       sizeof(m_cPsw),       strPath);
		}
	}
}

// 连接并下载服务器的一个文件到缓冲区，判断是否连接成功
BOOL CWebUpdate::ConnectServerFile(CString UpdateFile,CHttpConnection*pHttp)
{
	// modified by Jerry Lee, 2011-3-24
	// begin
	BOOL bResult = FALSE;

	if(pHttp == NULL)
	{
		pHttp = m_pHttp;
	}
    
	m_pFile = pHttp->OpenRequest(CHttpConnection::HTTP_VERB_GET, 
		m_ServerPath + UpdateFile, NULL, 1, NULL, NULL, m_dwHttpRequestFlags); 

	if(m_bProxy) // 如果需要使用代理
	{
		if(m_bLogon)
		{
			m_pFile-> SetOption(INTERNET_OPTION_PROXY_USERNAME,   m_cUserName,  strlen(m_cUserName) + 1); 
			m_pFile-> SetOption(INTERNET_OPTION_PROXY_PASSWORD,   m_cPsw,       strlen(m_cPsw) + 1); 
		}
	}

	try
	{
		bResult = m_pFile->SendRequest();
	}
	catch(CInternetException* ex)
	{
		m_pFile->Close();
		ex->Delete();
	}
	// end

	DWORD dwStatusCode;
	if(bResult)
	{
		m_pFile->QueryInfoStatusCode(dwStatusCode);
		if(!((dwStatusCode >= 200)&&(dwStatusCode <= 299)))
		{
			bResult = FALSE;
		}
	}

	if(!bResult)
	{
		if(m_strServerByDomain != m_strServer)
		{
			m_strServer = m_strServerByDomain;
			m_pHttp->Close();
			m_pHttp = m_cis.GetHttpConnection(m_strServer, m_dwPort);
			return ConnectServerFile(UpdateFile, m_pHttp); // 重新连接
		}
	}

	return bResult;
}

/*
检测是否需要更新
返回1则为升级配置文件下载出错
返回2则为UpdateFiles.ini下载出错
返回3则为无需更新
返回4则为需要更新
*/
int CWebUpdate::CheckUpdate()
{
	// 将缓冲区的的Update.ini文件写入到临时目录
	WriteBufferToTemp(SER_UPDATE_INI_PATH);
	
	// 对update临时目录下的update.ini进行crc校验和解crc处理
	if(!CPublic::Instance()->CheckCrc(SER_UPDATE_INI_PATH)) // 如果update的crc校验出错
	{
		return CHECK_UPDATE_DOWNLOAD_ERROR;
	}
	
	// 读取临时目录下的升级配置文件（即服务器的），与本地比较系统版本号
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString("Update", "VERSION","1.0", buf, sizeof(buf), CPublic::Instance()->GetTempPath() + SER_UPDATE_INI_PATH);
	m_strSerVersion   = buf;
	int dVersion = 1000* (m_fVersion+0.0005); // 客户端版本
	int dbuf = (atof(buf)+0.0005)*1000;       // 服务端版本
	
	// 如果现有版本大于或等于服务器版本，则无需更新
	if(dVersion >= dbuf) 
	{
		return CHECK_UPDATE_NO_NEED_UPDATE;  // 无需更新
	}

	// 如果发现新的版本，则开始寻找对比文件名。
	// 从服务器上读取UpdateFiles.ini文件，与本地的UpdateFiles.ini文件相比较。
	if(!CheckUpdateFile())
	{
		return CHECK_UPDATE_DOWNLOAD_ERROR; // UpdateFiles.ini下载出错
	}

	return CHECK_UPDATE_NEED_UPDATE;     // 有文件需要更新
}


// 对比客户端和服务端的UpdateFiles.xml文件，获取要更新的文件
BOOL CWebUpdate::CheckUpdateFile()
{
	// 下载UpdateFiles.xml到临时目录
	if(!HttpDownloadFiles(UPDATE_FILES_XML_NAME))
	{
		return false;
	}

	// 如果XML文件的crc校验出错，则返回false
	if(!CPublic::Instance()->CheckCrc(UPDATE_FILES_XML_NAME)) 
	{
		return false;
	}
	 
	CXmlDocument m_pXMLDoc;
	vector<UpdateFileStru> vecFileClient;
	vector<UpdateFileStru> vecFileServer;
	UpdateFileStru stru;

	// 载入本地的xml的文件信息到vecFileClient
	LoadXMLToVec(vecFileClient,  CPublic::Instance()->GetSysPath() + UPDATE_FILES_XML_NAME);
	// 载入服务器的xml的文件信息到vecFileServer
	LoadXMLToVec(vecFileServer,  CPublic::Instance()->GetTempPath() + UPDATE_FILES_XML_NAME);
    
	// 对比客户端和服务端文件信息，加载下载文件列表
	GetDownLoadFile(vecFileClient, vecFileServer);

	// 删除客户区多余文件，要实现不？
	
	// 如果要下载的文件不为空，则需要更新
	if(m_vecDLFiles.size() != 0)
	{
		// 需要更新
		return TRUE;
	}
	else 
	{
		// 不需要更新
		return FALSE;
	}
}

// 获取字符串形式的客户端版本号，虽然m_fVersion保存版本号，但是格式化转换后可能有误，所以重新获取了
CString CWebUpdate::GetClientVersion(void)
{
	char buf[MAX_PATH];   
	::GetPrivateProfileString("Update", "VERSION", "0", buf, sizeof(buf), CPublic::Instance()->GetUpdateIniPath());

	return (CString)buf;
}

// 将升级xml的信息加载到Vector
void CWebUpdate::LoadXMLToVec( vector<UpdateFileStru> &vecFile, CString &strFilePath )
{
	CXmlDocument m_pXMLDoc;
	UpdateFileStru stru;

	m_pXMLDoc.Load(strFilePath);

	CXmlElement      *pRootXmlEle = NULL;
	CXmlElement   *pCataBigXmlEle = NULL;
	CXmlElement *pCataSmallXmlEle = NULL;
	CXmlElement      *pItemXmlEle = NULL;

	pRootXmlEle    = m_pXMLDoc.GetRootElement();
	pCataBigXmlEle = m_pXMLDoc.FindElement(pRootXmlEle, _T("catalogs"));
	if(pCataBigXmlEle) 
	{	
		pCataSmallXmlEle = m_pXMLDoc.FindElement(pCataBigXmlEle, _T("catalog"));

		// 遍历catalogs下面的所有catalog
		while(pCataSmallXmlEle)
		{	
			CString strDate = "";

			// 获取catalog下面的name
			CString strFileName = pCataSmallXmlEle->GetValue(_T("name"));
			
			if(UPDATE_SYSTEM_VERSION == 2) // 如果是采用原来的版本
			{
				// 获取catalog下面的item节点
				pItemXmlEle          = m_pXMLDoc.FindElement(pCataSmallXmlEle, _T("item"));

				// 获取catalog的type字段的值
				CString strType = pCataSmallXmlEle->GetValue(_T("type"));
				// 如果还有子目录
				if(strType == "2")
				{
					CString strFileName2 = pItemXmlEle->GetValue(_T("name"));
					// 合并文件名称
					strFileName         += strFileName2;
				}
                
				// 记录日期
				strDate = pItemXmlEle->GetValue(_T("updatedate"));
			}
			else // 如果xml结构是新的版本，暂时没有弄
			{
				// 获取catalog下item的updatedate
				strDate = pCataSmallXmlEle->GetValue(_T("updatedate"));
			}

			stru.strFileName = strFileName;
			stru.strDate     = strDate;

			vecFile.push_back(stru);

			pCataSmallXmlEle = m_pXMLDoc.FindNextElement(pCataBigXmlEle);
		}
	}
	m_pXMLDoc.Store(strFilePath);
}
// 通过比较客户端和服务端的xml文件，加载要下载的文件的信息
void CWebUpdate::GetDownLoadFile( const vector<UpdateFileStru> &vecClient, const vector<UpdateFileStru> &vecServer )
{
	// 遍历服务器文件列表
	for( int i = 0; i< vecServer.size(); i++)
	{
		UpdateFileStru stru;
		bool bFind = false;
		bool bAdd  = false;
        
		stru = vecServer.at(i);
		// 判断文件名是否在客户端文件列表中存在
		for(int i = 0; i < vecClient.size(); i++)
		{
			if(vecClient.at(i).strFileName == stru.strFileName)
			{
				bFind = true;
				
				// 如果日期不一致，则添加到下载列表
				if(stru.strDate != vecClient.at(i).strDate)
				{
					bAdd = true;
				}

				break;
			}
		}
        
		// 如果不存在或者日期不一致，则添加
		if(!bFind || bAdd)
		{
			DLFileInfo struDL;
			struDL.strName    = stru.strFileName;
			struDL.isDownLoad = false;

			m_vecDLFiles.push_back(struDL);	
		}
	}
}

// 利用http下载一个文件到临时目录
bool CWebUpdate::HttpDownloadFiles( CString strFileName )
{
	// 下载一个文件到缓冲区
	if(!ConnectServerFile(strFileName))
	{
		// 下载失败
		return false;
	}
    
	// 从缓冲区写入文件到临时目录
	WriteBufferToTemp(strFileName);

	return true;
}
// 从缓冲区写入到临时目录
void CWebUpdate::WriteBufferToTemp( const CString &strFileName )
{
	// 从缓冲区写入文件到临时目录
	if(m_pFile)
	{
		CFile csf; 

		// 构建文件在临时目录的完整路径
		CString strFilePath = CPublic::Instance()->GetTempPath() + strFileName; 
		int index = strFilePath.ReverseFind('/');
		if(index == -1)
		{
			index = strFilePath.ReverseFind('\\');
		}
		CString strPath = strFilePath.Left(index);     // 获取最后的文件夹

		// 确保该文件夹的存在，用于文件名包含目录的清空
		CPublic::Instance()->MakeDirAllExist(strPath); 

		if(!csf.Open(CPublic::Instance()->GetTempPath() + strFileName, CFile::modeCreate|CFile::modeWrite))
		{
			if (((CUpdateApp*)AfxGetApp())->g_SysVersion == UPPER_VISTA)
			{
				AfxMessageBox("创建目录失败，请使用管理员身份运行本程序！");			
			}
			else
			{
				AfxMessageBox("创建目录失败，请确认用户有足够的权限！");
			}
			exit(0);
		}

		// 从缓冲区写入文件到临时目录
		char buf[1024];
		int n;

		while(1)
		{
			// modified by Jerry Lee, 2011-3-24
			// begin
			try
			{
				n = m_pFile->Read(buf, MAX_PATH);
			}
			catch(CInternetException* ex)
			{
				break;
			}
			// end

			if(n <= 0)
			{
				break;
			}
			csf.Write(buf, n);
		}

		csf.Close();
		m_pFile->Close();
	}
}
