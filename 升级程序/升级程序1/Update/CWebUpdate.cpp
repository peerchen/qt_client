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

// ���ݱ������������ļ�����ʼ������������Ϣ
void CWebUpdate::InitUpdate()
{
	// ��ȡ�����������õ�·��
	char buf[MAX_PATH] = {0};
	CString strPath = CPublic::Instance()->GetUpdateIniPath();

	// ��ȡ�ͻ��˰汾��
	::GetPrivateProfileString("Update", "VERSION", "0", buf, sizeof(buf), strPath);
	m_fVersion = (float)atof(buf); 

	// ��ȡ����Ŀ���ַip
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
			AfxMessageBox(_T("update.ini�ļ����ݳ���"),MB_ICONSTOP);
			exit(0);
		}
	}

	m_dwType = dwType;
	m_cis.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 30000);      // 5������ӳ�ʱ 
	m_pHttp = m_cis.GetHttpConnection(m_strServer,m_dwPort);
	CString strIniName = CLI_UPDATE_INI_PATH;
	m_ServerPath = m_ServerPath.Left(m_ServerPath.GetLength()-strIniName.GetLength());

	// ���������ļ���ȡ��������
	char cProxyType[2] = {0};
	strPath = CPublic::Instance()->GetSysPath() + "iconfig.ini";
	::GetPrivateProfileString("ICONFIG", "PROXYTYPE", "0", cProxyType, sizeof(cProxyType), strPath);

	// modified by Jerry Lee, 2011-3-24
	// begin
	int iProxy = atoi(cProxyType);
	if (iProxy > 0)  // ��Ҫ����
	{
		// ��Ҫ����
		m_bProxy = true;

		// ��ȡ�������͵�����
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
		// modified 20110922 ���²�����������
		//INTERNET_PROXY_INFO   proxyinfo; 
		//proxyinfo.dwAccessType    =   INTERNET_OPEN_TYPE_PRECONFIG; 
		////proxyinfo.lpszProxy       =   NULL; 
		//proxyinfo.lpszProxyBypass =   NULL; 
		//m_cis.SetOption(INTERNET_OPEN_TYPE_PRECONFIG, (LPVOID)&proxyinfo,   sizeof(INTERNET_PROXY_INFO));
		return;
	}
	// end

	// �����Ҫʹ�ô���
	if(m_bProxy) 
	{
		// ��ȡ�û���������
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

// ���Ӳ����ط�������һ���ļ������������ж��Ƿ����ӳɹ�
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

	if(m_bProxy) // �����Ҫʹ�ô���
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
			return ConnectServerFile(UpdateFile, m_pHttp); // ��������
		}
	}

	return bResult;
}

/*
����Ƿ���Ҫ����
����1��Ϊ���������ļ����س���
����2��ΪUpdateFiles.ini���س���
����3��Ϊ�������
����4��Ϊ��Ҫ����
*/
int CWebUpdate::CheckUpdate()
{
	// ���������ĵ�Update.ini�ļ�д�뵽��ʱĿ¼
	WriteBufferToTemp(SER_UPDATE_INI_PATH);
	
	// ��update��ʱĿ¼�µ�update.ini����crcУ��ͽ�crc����
	if(!CPublic::Instance()->CheckCrc(SER_UPDATE_INI_PATH)) // ���update��crcУ�����
	{
		return CHECK_UPDATE_DOWNLOAD_ERROR;
	}
	
	// ��ȡ��ʱĿ¼�µ����������ļ������������ģ����뱾�رȽ�ϵͳ�汾��
	char buf[MAX_PATH] = {0};
	::GetPrivateProfileString("Update", "VERSION","1.0", buf, sizeof(buf), CPublic::Instance()->GetTempPath() + SER_UPDATE_INI_PATH);
	m_strSerVersion   = buf;
	int dVersion = 1000* (m_fVersion+0.0005); // �ͻ��˰汾
	int dbuf = (atof(buf)+0.0005)*1000;       // ����˰汾
	
	// ������а汾���ڻ���ڷ������汾�����������
	if(dVersion >= dbuf) 
	{
		return CHECK_UPDATE_NO_NEED_UPDATE;  // �������
	}

	// ��������µİ汾����ʼѰ�ҶԱ��ļ�����
	// �ӷ������϶�ȡUpdateFiles.ini�ļ����뱾�ص�UpdateFiles.ini�ļ���Ƚϡ�
	if(!CheckUpdateFile())
	{
		return CHECK_UPDATE_DOWNLOAD_ERROR; // UpdateFiles.ini���س���
	}

	return CHECK_UPDATE_NEED_UPDATE;     // ���ļ���Ҫ����
}


// �Աȿͻ��˺ͷ���˵�UpdateFiles.xml�ļ�����ȡҪ���µ��ļ�
BOOL CWebUpdate::CheckUpdateFile()
{
	// ����UpdateFiles.xml����ʱĿ¼
	if(!HttpDownloadFiles(UPDATE_FILES_XML_NAME))
	{
		return false;
	}

	// ���XML�ļ���crcУ������򷵻�false
	if(!CPublic::Instance()->CheckCrc(UPDATE_FILES_XML_NAME)) 
	{
		return false;
	}
	 
	CXmlDocument m_pXMLDoc;
	vector<UpdateFileStru> vecFileClient;
	vector<UpdateFileStru> vecFileServer;
	UpdateFileStru stru;

	// ���뱾�ص�xml���ļ���Ϣ��vecFileClient
	LoadXMLToVec(vecFileClient,  CPublic::Instance()->GetSysPath() + UPDATE_FILES_XML_NAME);
	// �����������xml���ļ���Ϣ��vecFileServer
	LoadXMLToVec(vecFileServer,  CPublic::Instance()->GetTempPath() + UPDATE_FILES_XML_NAME);
    
	// �Աȿͻ��˺ͷ�����ļ���Ϣ�����������ļ��б�
	GetDownLoadFile(vecFileClient, vecFileServer);

	// ɾ���ͻ��������ļ���Ҫʵ�ֲ���
	
	// ���Ҫ���ص��ļ���Ϊ�գ�����Ҫ����
	if(m_vecDLFiles.size() != 0)
	{
		// ��Ҫ����
		return TRUE;
	}
	else 
	{
		// ����Ҫ����
		return FALSE;
	}
}

// ��ȡ�ַ�����ʽ�Ŀͻ��˰汾�ţ���Ȼm_fVersion����汾�ţ����Ǹ�ʽ��ת������������������»�ȡ��
CString CWebUpdate::GetClientVersion(void)
{
	char buf[MAX_PATH];   
	::GetPrivateProfileString("Update", "VERSION", "0", buf, sizeof(buf), CPublic::Instance()->GetUpdateIniPath());

	return (CString)buf;
}

// ������xml����Ϣ���ص�Vector
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

		// ����catalogs���������catalog
		while(pCataSmallXmlEle)
		{	
			CString strDate = "";

			// ��ȡcatalog�����name
			CString strFileName = pCataSmallXmlEle->GetValue(_T("name"));
			
			if(UPDATE_SYSTEM_VERSION == 2) // ����ǲ���ԭ���İ汾
			{
				// ��ȡcatalog�����item�ڵ�
				pItemXmlEle          = m_pXMLDoc.FindElement(pCataSmallXmlEle, _T("item"));

				// ��ȡcatalog��type�ֶε�ֵ
				CString strType = pCataSmallXmlEle->GetValue(_T("type"));
				// ���������Ŀ¼
				if(strType == "2")
				{
					CString strFileName2 = pItemXmlEle->GetValue(_T("name"));
					// �ϲ��ļ�����
					strFileName         += strFileName2;
				}
                
				// ��¼����
				strDate = pItemXmlEle->GetValue(_T("updatedate"));
			}
			else // ���xml�ṹ���µİ汾����ʱû��Ū
			{
				// ��ȡcatalog��item��updatedate
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
// ͨ���ȽϿͻ��˺ͷ���˵�xml�ļ�������Ҫ���ص��ļ�����Ϣ
void CWebUpdate::GetDownLoadFile( const vector<UpdateFileStru> &vecClient, const vector<UpdateFileStru> &vecServer )
{
	// �����������ļ��б�
	for( int i = 0; i< vecServer.size(); i++)
	{
		UpdateFileStru stru;
		bool bFind = false;
		bool bAdd  = false;
        
		stru = vecServer.at(i);
		// �ж��ļ����Ƿ��ڿͻ����ļ��б��д���
		for(int i = 0; i < vecClient.size(); i++)
		{
			if(vecClient.at(i).strFileName == stru.strFileName)
			{
				bFind = true;
				
				// ������ڲ�һ�£�����ӵ������б�
				if(stru.strDate != vecClient.at(i).strDate)
				{
					bAdd = true;
				}

				break;
			}
		}
        
		// ��������ڻ������ڲ�һ�£������
		if(!bFind || bAdd)
		{
			DLFileInfo struDL;
			struDL.strName    = stru.strFileName;
			struDL.isDownLoad = false;

			m_vecDLFiles.push_back(struDL);	
		}
	}
}

// ����http����һ���ļ�����ʱĿ¼
bool CWebUpdate::HttpDownloadFiles( CString strFileName )
{
	// ����һ���ļ���������
	if(!ConnectServerFile(strFileName))
	{
		// ����ʧ��
		return false;
	}
    
	// �ӻ�����д���ļ�����ʱĿ¼
	WriteBufferToTemp(strFileName);

	return true;
}
// �ӻ�����д�뵽��ʱĿ¼
void CWebUpdate::WriteBufferToTemp( const CString &strFileName )
{
	// �ӻ�����д���ļ�����ʱĿ¼
	if(m_pFile)
	{
		CFile csf; 

		// �����ļ�����ʱĿ¼������·��
		CString strFilePath = CPublic::Instance()->GetTempPath() + strFileName; 
		int index = strFilePath.ReverseFind('/');
		if(index == -1)
		{
			index = strFilePath.ReverseFind('\\');
		}
		CString strPath = strFilePath.Left(index);     // ��ȡ�����ļ���

		// ȷ�����ļ��еĴ��ڣ������ļ�������Ŀ¼�����
		CPublic::Instance()->MakeDirAllExist(strPath); 

		if(!csf.Open(CPublic::Instance()->GetTempPath() + strFileName, CFile::modeCreate|CFile::modeWrite))
		{
			if (((CUpdateApp*)AfxGetApp())->g_SysVersion == UPPER_VISTA)
			{
				AfxMessageBox("����Ŀ¼ʧ�ܣ���ʹ�ù���Ա������б�����");			
			}
			else
			{
				AfxMessageBox("����Ŀ¼ʧ�ܣ���ȷ���û����㹻��Ȩ�ޣ�");
			}
			exit(0);
		}

		// �ӻ�����д���ļ�����ʱĿ¼
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
