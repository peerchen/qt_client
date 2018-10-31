#include "FpApiCpMgr.h"
#include "HandleRSA.h"
#include <stdio.h>
#include <iostream>
#include "SafeEngineClass.h"

CFpApiCpMgr::CFpApiCpMgr()
{ 
#ifdef _WIN32
	//#pragma comment(lib,"ws2_32.lib")
	WSADATA wsaData;
	int nnRtn = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (nnRtn != NO_ERROR)
	{
		CRLog(E_ERROR,"%s", "Error at WSAStartup()");
	}
#endif
	m_pConfig = new CConfigImpl();
	m_bIsInit = false;
	m_isPrintHello = 1;
	m_iMagicNumber = 123456;
	m_nTSend = 30;
	m_nTRecv = m_nTSend *4; 
}

CFpApiCpMgr::~CFpApiCpMgr()
{
	delete m_pConfig;
	m_pConfig = 0;
}

int CFpApiCpMgr::OnAccept(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort)
{
	return 0;
}

int CFpApiCpMgr::OnConnect(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort,int nFlag)
{
	if (ulKey == EnumKeyIfA2 && nFlag == 0)
	{
		if( nFlag == 0 )
		{
			m_pAPI->onConnect();
		}
		else
		{
			CProcessInterfaceA2C::SetLoginStatu( EnumLogout );
			m_pAPI->onConnectLost();
		}
	}
	return 0;
}

int CFpApiCpMgr::OnClose(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort)
{
	if (ulKey == EnumKeyIfA2)
	{
		m_pAPI->onConnectLost();
		CProcessInterfaceA2C::SetLoginStatu( EnumLogout );
	}
	return 0;
}

int CFpApiCpMgr::OnLogin(const unsigned long& ulKey,const string& sLocalIp, int nLocalPort, const string& sPeerIp, int nPeerPort,int nFlag)
{
	return 0;
}

int CFpApiCpMgr::SetTSend( long long nTSend)
{
	if( NULL == m_pCpInterfaceA2 )
	{
		m_nTSend = nTSend;
		return 0;
	}
	CRLog( E_ERROR, "不能在初始化之后设置发送超时" );
	return -1;
}

long long CFpApiCpMgr::GetTSend()
{
	return m_nTSend;
}

int CFpApiCpMgr::SetTRecv( long long nTRecv)
{
	if( NULL == m_pCpInterfaceA2 )
	{
		m_nTRecv = nTRecv;
		return 0;
	}
	CRLog( E_ERROR, "不能在初始化之后设置接收超时" );
	return -1;
}

long long CFpApiCpMgr::GetTRecv()
{
	return m_nTRecv;
}
int CFpApiCpMgr::Init( const char *sIP, const int iPort, API_CALLBACK *stApiCallback, const char *sPrivateCertPath, const char *sPublicCertPath, const char *sPrivateCertPassword, const char *sRootCertPath, void *pParamter )
{
	if (m_bIsInit == true)
	{
		//重复初始化
		return -10;
	}

	//初始化各应用模块
	if (0 != ModuleInit())
	{
		CRLog(E_ERROR,"%s", "ModuleInit fail");
		return -5;
	}

	if (0 != BasicCfgInit( sIP,iPort, sPrivateCertPath, sPublicCertPath, sPrivateCertPassword, sRootCertPath ) )
	{
		CRLog(E_ERROR,"%s", "BasicCfgInit fail");
		return -4;
	}
	//初始化各协议连接点
	IfCpsInit();


	CGessTimerMgrImp::Instance()->Init(2);
	CGessTimerMgrImp::Instance()->Start();

	m_pAPI->BindApi( stApiCallback, pParamter );
	m_pAPI->Start();
	m_pCpInterfaceA2->Start();

	m_bIsInit = true;
	return 0;	
}
void CFpApiCpMgr::Finish()
{
	CGessTimerMgrImp::Instance()->Stop();
	CGessTimerMgrImp::Instance()->Finish();


	//stop
	if (0 != m_pCpInterfaceA2)
	{		
		CRLog(E_NOTICE,"Stop connection point A2...");
		m_pCpInterfaceA2->Stop();
	}
	if (0 != m_pAPI)
		m_pAPI->Stop();


	//finish
	if (0 != m_pCpInterfaceA2)
	{
		CRLog(E_NOTICE,"Cleanup connection point A2");
		m_pCpInterfaceA2->Finish();
		delete m_pCpInterfaceA2;
		m_pCpInterfaceA2 = 0;
	}
	if (0 != m_pAPI)
	{
		CRLog(E_NOTICE,"Cleanup connection point API");
		m_pAPI->Finish();
		delete m_pAPI;
		m_pAPI = 0;
	}

	CRLog(E_NOTICE, "Cleanup log module");
	CLogger::Instance()->Finish();
	m_pConfig->Clear();

	m_bIsInit = false;
	
}
int CFpApiCpMgr::Forward(CPacket &GessPacket,const unsigned long& ulKey)
{
	try
	{
		if (EnumKeyUnknown <= ulKey)
		{
			CRLog(E_ERROR,"EnumKeyUnknown(%d) <= ulKey(%d)",EnumKeyUnknown, (int)ulKey );
			return -1;
		}

		CAPIThroughGtpPacket & pkt = dynamic_cast<CAPIThroughGtpPacket&>(GessPacket);
		CRLog(E_DEBUG,"Forward %s", pkt.Print().c_str() );

		if ( ulKey == EnumKeyIfA2 )
		{
			m_pAPI->EnqueRecv(pkt);
		}
		if ( ulKey == EnumKeyApi )
		{
			m_pCpInterfaceA2->SendPacket( GessPacket );
		}
		return 0;
	}
	catch(std::bad_cast)
	{
		CRLog(E_ERROR,"packet error!");
		return -1;
	}
	catch(std::exception e)
	{
		CRLog(E_CRITICAL,"exception:%s", e.what());
		return -1;
	}
	catch(...)
	{
		CRLog(E_CRITICAL,"Unknown exception");
		return -1;
	}
}


CApi * CFpApiCpMgr::GetApi()
{
	return m_pAPI;
}


int CFpApiCpMgr::StartLog(const char *sFilePath )
{
	m_pConfig->SetProperty("logger.type","common");
	m_pConfig->SetProperty("logger.common.device","file");
	m_pConfig->SetProperty("logger.common.path",sFilePath);
	m_pConfig->SetProperty("logger.common.level","E_CRITICAL, E_ERROR, E_WARNING, E_NOTICE, E_SYSINFO, E_PROINFO, E_APPINFO, E_DEBUG");
	m_pConfig->SetProperty("logger.common.prefix","FpApi");
	m_pConfig->SetProperty("logger.common.postfix","log");
	m_pConfig->SetProperty("logger.common.num","4");
	m_pConfig->SetProperty("logger.common.level1","E_CRITICAL");
	m_pConfig->SetProperty("logger.common.file1","LogErr");
	m_pConfig->SetProperty("logger.common.level2","E_ERROR");
	m_pConfig->SetProperty("logger.common.file2","LogErr");
	m_pConfig->SetProperty("logger.common.level3","E_WARNING");
	m_pConfig->SetProperty("logger.common.file3","LogErr");
	m_pConfig->SetProperty("logger.common.level4","E_PROINFO");
	m_pConfig->SetProperty("logger.common.file4","LogProInfo");
	// 初始化日志
	if (CLogger::Instance()->Initial(m_pConfig->GetProperties("logger")) != 0)
	{
		cout << "日志初始化失败!" << endl;
		return -1;
	}


	// 启动日志
	if (CLogger::Instance()->Start() != 0)
	{
		cout << "日志启动失败!" << endl;
		return -1;
	}
	CRLog( E_APPINFO, "日志启动成功");
	return 0;
}

void CFpApiCpMgr::StopLog()
{
	CLogger::Instance()->Finish();
}
int CFpApiCpMgr::BasicCfgInit( const char *sIP, const int iPort, const char *sPrivateCertPath, const char *sPublicCertPath, const char *sPrivateCertPassword, const char *sRootCertPath )
{
	string tempValue;

	tempValue  = sIP;
	tempValue += ":";
	tempValue += ToString(iPort);
	m_pConfig->SetProperty( "IFA2.ip_port",tempValue );

	if (m_isPrintHello == 1)
	{
		m_pConfig->SetProperty("IFA2.is_print_hello","1");
	}else
	{
		m_pConfig->SetProperty("IFA2.is_print_hello","0");
	}
	m_pConfig->SetProperty("IFA2.nTSend",ToString<int>(m_nTSend));
	m_pConfig->SetProperty("IFA2.nTRecv",ToString<int>(m_nTRecv));


	m_pConfig->SetProperty("IFA2.magic_number",ToString<int>(m_iMagicNumber));

	
	//验证证书路径
	string PrivatePath = sPrivateCertPath;
	string PublicPath  = sPublicCertPath;
	string RootPath = sRootCertPath;
	#ifdef _WIN32
		//初始化证书加密地址
		char szFileName[_MAX_PATH], szFilePath[_MAX_PATH];
		char * pcName;
		::GetModuleFileName(0,szFileName, _MAX_PATH);
		::GetFullPathName(szFileName, _MAX_PATH, szFilePath, &pcName);
		char szBuf[_MAX_PATH];
		strcpy(szBuf,pcName);
		*pcName = '\0';
		PrivatePath = string(szFilePath) + sPrivateCertPath;
		PublicPath  = string(szFilePath) + sPublicCertPath;
		RootPath    = string(szFilePath) + sRootCertPath;
	#endif

	FILE * ftest1;
	FILE * ftest2;
	FILE * ftest3;
	ftest1 = fopen( PrivatePath.c_str(),"r");
	ftest2 = fopen( PublicPath.c_str(),"r");
	ftest3 = fopen( RootPath.c_str(),"r");
	if (ftest1 != NULL && ftest2 != NULL && ftest3 != NULL)
	{
		CRLog(E_DEBUG,"私钥证书地址: %s",PrivatePath.c_str() );
		CRLog(E_DEBUG,"公钥证书地址: %s",PublicPath.c_str() );
		CRLog(E_DEBUG,"根证书地址: %s",RootPath.c_str() );
		m_pConfig->SetProperty("IFA2.private_cert_path",PrivatePath.c_str() );
		m_pConfig->SetProperty("IFA2.public_cert_path", PublicPath.c_str()  );
		m_pConfig->SetProperty("IFA2.private_cert_password",sPrivateCertPassword );
		m_pConfig->SetProperty("IFA2.root_cert",RootPath );

		fclose( ftest1 );
		fclose( ftest2 );
		fclose( ftest3 );
	}
	else
	{
		if( ftest1 != NULL )
		{
			fclose( ftest1 );
		}
		else
		{
			CRLog(E_NOTICE,"在%s目录下未找到私钥证书",PrivatePath.c_str());
		}
		
		if( ftest2 != NULL )
		{
			fclose( ftest2 );
		}
		else
		{
			CRLog(E_NOTICE,"在%s目录下未找到公钥证书",PublicPath.c_str());
		}	
		if( ftest3 != NULL )
		{
			fclose( ftest3 );
		}
		else
		{
			CRLog(E_NOTICE,"在%s目录下未找到根证书",RootPath.c_str());
		}

		

		return -1;
	}

	return 0;
}
int CFpApiCpMgr::ModuleInit()
{
	//初始化API模块
	CRLog(E_APPINFO,"%s","Init ApiModule");

	m_pAPI = new CApi();
	if (!m_pAPI)
	{
		CRLog(E_ERROR,"%s","Init ApiModule Fail");
		return -1;
	}
	m_pAPI->Bind(this,EnumKeyApi);
	m_pAPI->Init();

	return 0;
}
int CFpApiCpMgr::IfCpsInit()
{

	CConfig *pCfgA2;
	pCfgA2 = m_pConfig->GetProperties(gc_sCfgIfA2);

	CRLog(E_APPINFO,"Init Connect Point...");

	if (0 != pCfgA2 && !pCfgA2->IsEmpty())
	{
		CRLog(E_APPINFO,"Initialize connection point A2");
		m_pCpInterfaceA2 = new CProtocolCpCli<CProcessInterfaceA2C>();
		m_pCpInterfaceA2->Init(pCfgA2);
		m_pCpInterfaceA2->Bind(this,EnumKeyIfA2);
	}
	return 0;
}
