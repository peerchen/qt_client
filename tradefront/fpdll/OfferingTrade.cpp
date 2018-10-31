// OfferingTrade.cpp: implementation of the COfferingTrade class.
//
//////////////////////////////////////////////////////////////////////
// 
#include <string.h>

#include "OfferingTrade.h"
#include "BF_Date_Time.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COfferingTrade * getInstance() 
{ 
    return new COfferingTrade(); 
}

COfferingTrade::COfferingTrade()
{
	m_nConnTime = 0;
	bzero(&m_pPoint,sizeof(FP_API_OFFERING));
	m_pDllApiHandle = NULL;
	m_pDllCaApiHandle = NULL;
	m_sSgeSafeInfo = NULL;
	m_nSgeSafeInfoLen = 0;

	m_bIsInit = false;
	m_state = 0;

	AddFuncInfo("A000",(SgeFuncPointer)&COfferingTrade::SendMsg,"接入单元登录");
	AddFuncInfo("A010",(SgeFuncPointer)&COfferingTrade::SendMsg,"接入单元登出");
	AddFuncInfo("A100",(SgeFuncPointer)&COfferingTrade::SendMsg,"交易员登录");
	AddFuncInfo("A110",(SgeFuncPointer)&COfferingTrade::SendMsg,"交易员登出");
	AddFuncInfo("Q380",(SgeFuncPointer)&COfferingTrade::SendMsg,"库存互换意向发布");
	AddFuncInfo("T520",(SgeFuncPointer)&COfferingTrade::SendMsg,"参考价录入");
	AddFuncInfo("T530",(SgeFuncPointer)&COfferingTrade::SendMsg,"定价委托报单");
	AddFuncInfo("T540",(SgeFuncPointer)&COfferingTrade::SendMsg,"定价委托撤单");
	AddFuncInfo("T650",(SgeFuncPointer)&COfferingTrade::SendMsg,"参考价报入流水查询");
	AddFuncInfo("T660",(SgeFuncPointer)&COfferingTrade::SendMsg,"定价委托申报流水查询");
	AddFuncInfo("M650",(SgeFuncPointer)&COfferingTrade::SendMsg,"服务器时间同步");


	printf("API创建");
}

COfferingTrade::~COfferingTrade()
{
	if (m_pDllApiHandle != NULL)
	{
		FREEDLL(m_pDllApiHandle);
		m_pDllApiHandle = NULL;
	}
	if (m_pDllCaApiHandle != NULL)
	{
		FREEDLL(m_pDllCaApiHandle);
		m_pDllCaApiHandle = NULL;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API回收");
	
}

bool COfferingTrade::Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg)
{

 	bool bRet = CIOfferingBase::Init(api,log,xml,xmlnode,errmsg);

	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API初始化开始");
	if (!bRet)
	{
		return bRet;
	}
 	//打开动态库
 	std::string dllname;
#ifdef _WINDOWS
 	dllname = "FpApi.dll";
 #else
	dllname = "libfpapi.so";
#endif	

	m_pDllApiHandle = LOADDLL(dllname.c_str());
// 	if (ISNOTOPEN(m_pDllApiHandle))
// 	{
// 		sprintf(errmsg,"打开动态库%s失败 出错码%d",dllname.c_str(),GET_LAST_SOCK_ERROR());
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
// 		return false;
// 	}
#ifdef _WINDOWS
	if (ISNOTOPEN(m_pDllApiHandle))
	{
		sprintf(errmsg,"打开动态库%s失败 出错码%d",dllname.c_str(),GetLastError());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#else
	char *err = dlerror();
	if (err != NULL)
	{
		sprintf(errmsg,"打开动态库%s失败 出错[%s]",dllname.c_str(),err);
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#endif
	m_pPoint.fp_api_init             = (_fp_api_init)GETINSTANCE(m_pDllApiHandle, "fp_api_init");
	m_pPoint.fp_api_wait             = (_fp_api_wait)GETINSTANCE(m_pDllApiHandle, "fp_api_wait");
	m_pPoint.fp_api_send_msg         = (_fp_api_send_msg)GETINSTANCE(m_pDllApiHandle, "fp_api_send_msg");
	m_pPoint.fp_api_get_version      = (_fp_api_get_version)GETINSTANCE(m_pDllApiHandle, "fp_api_get_version");
	m_pPoint.fp_api_free             = (_fp_api_free)GETINSTANCE(m_pDllApiHandle, "fp_api_free");
	m_pPoint.fp_api_set_recv_timeout = (_fp_api_set_recv_timeout)GETINSTANCE(m_pDllApiHandle, "fp_api_set_recv_timeout");
	m_pPoint.fp_api_get_recv_timeout = (_fp_api_get_recv_timeout)GETINSTANCE(m_pDllApiHandle, "fp_api_get_recv_timeout");
	m_pPoint.fp_api_set_send_timeout = (_fp_api_set_send_timeout)GETINSTANCE(m_pDllApiHandle, "fp_api_set_send_timeout");
	m_pPoint.fp_api_get_send_timeout = (_fp_api_get_send_timeout)GETINSTANCE(m_pDllApiHandle, "fp_api_get_send_timeout");
	m_pPoint.fp_api_log_start        = (_fp_api_log_start)GETINSTANCE(m_pDllApiHandle, "fp_api_log_start");
	m_pPoint.fp_api_log_end          = (_fp_api_log_end)GETINSTANCE(m_pDllApiHandle, "fp_api_log_end");

     if (NULL == m_pPoint.fp_api_init
		 ||NULL == m_pPoint.fp_api_wait
		 ||NULL == m_pPoint.fp_api_send_msg
		 ||NULL == m_pPoint.fp_api_get_version 
		 ||NULL == m_pPoint.fp_api_free 
		 ||NULL == m_pPoint.fp_api_set_recv_timeout 
		 ||NULL == m_pPoint.fp_api_get_recv_timeout 
		 ||NULL == m_pPoint.fp_api_set_send_timeout
		 ||NULL == m_pPoint.fp_api_get_send_timeout 
		 ||NULL == m_pPoint.fp_api_log_start 
		 ||NULL == m_pPoint.fp_api_log_end )
     {
         sprintf(errmsg,"取动态库[%s]里的函数地址失败",dllname.c_str());
 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
         return false;
     }

	 if (m_sNodeType.compare("20") ==0) //定价报盘机
	 {
		 char xmlnodepath[100];
		 sprintf(xmlnodepath,"%s/会员代码",xmlnode);
		 if (xml->GetNodeValueByPath(xmlnodepath,false,m_sMemberId,false) == NULL)
		 {
			 sprintf(errmsg,"配置文件[%s]不存在",xmlnodepath);
			 m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			 return false;
		 }
		 sprintf(xmlnodepath,"%s/交易日期",xmlnode);
		 if (xml->GetNodeValueByPath(xmlnodepath,false,m_sTradeDate,false) == NULL)
		 {
			 sprintf(errmsg,"配置文件[%s]不存在",xmlnodepath);
			 m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			 return false;
		 }

	 }
	 m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API初始化成功");

	return true;
}
int  COfferingTrade::SendMsg(CGtpData *senddata)
{
	//判断连接是否正常
	if (m_nApiStatus != 1 || m_nApiLoginStatus != 1)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易所状态为未连接或未登录");
		return -1;
	}
	CBF_PMutex pp(&m_mutex);
	//发送数据
	std::string gtpstring;
	if (!senddata->ToString(gtpstring))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ToString出错");
		return -1;
	}
	
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"要发送的GTP数据 [%s]",gtpstring.c_str());

	int head = gtpstring.find("X09");
	int index = gtpstring.find(",",head);
	int ret = m_pPoint.fp_api_send_msg( gtpstring.substr(0,index).c_str(), gtpstring.substr(index+1).c_str() );

	if (ret <0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"fp_api_send_msg 发送出错 %d",ret);
		return -1;
	}
	m_nSendReqTime=time(NULL);
	return 0;
}


bool COfferingTrade::Uncrypt(S_SGE_GEMS2_API_STRUCT *ctx,const char *cryptmsg,int msglen,char *gtpmsg,int &gtpmsglen)
{
	gtpmsglen = msglen;
	memcpy( gtpmsg, cryptmsg, msglen+1 );
	return true;
}

bool COfferingTrade::StartApi()
{

	m_bIsInit = true;

	CBF_PMutex pp(&m_mutex);
	if (!GetFrontIpPort(m_sIp,m_nPort))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"无交易所前置IP及端口");
        return false;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"本次连接的交易所前置端口[%s %d]",m_sIp,m_nPort);
	//初始化api    
	m_pPoint.fp_api_log_start("fp");

	m_apiPoint->apistruct->api_ = NULL;

	API_CALLBACK api_callback;

	api_callback.on_fp_api_connect = &OnFpApiConnect;
	api_callback.on_fp_api_connect_lost = &OnFpApiConnectLost;
	api_callback.on_fp_api_exception = &OnFpApiException;
	api_callback.on_fp_api_recv_msg = &OnFpApiRecvMsg;


	if( 0 > m_pPoint.fp_api_init(
		m_sIp,
		m_nPort,
		&api_callback,
		m_sPath_key.c_str(),
		m_sPath_user.c_str(),
		m_sPath_svr.c_str(),
		m_sCertPwd.c_str(),
		m_sPath_root.c_str(),
		(void*)this ) )
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易所api_init出错");
        return false;
	}


	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API启动");
	m_nSendReqTime = time(NULL);
	m_nRcvBackTime = time(NULL);
	m_nRcvAnsTime = time(NULL);

	return true;
}
bool COfferingTrade::StopApi()
{
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API停止（%d）", m_bIsInit);

	if( !m_bIsInit) 
		return true;
	
	CBF_PMutex pp(&m_mutex);
	//发送交易员录出指令
	//TradeLogout();

	//释放api
	m_pPoint.fp_api_free();

	
	SLEEP_SECONDS(5);

	//等待线程终止
	//m_pPoint.fp_api_wait();
	//停止日志线程
	//m_pPoint.fp_api_log_end();

	m_bIsInit = false;

	CBF_Date_Time pdate;
	pdate.Update();
	m_nLogoutTime = atoi(pdate.ToStringD8().c_str())*10000+pdate.GetHour()*100+pdate.GetMinute(); 
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API停止（%d）完成", m_bIsInit);
	return true;
}

void COfferingTrade::TradeLogout()
{
	if( !m_bIsInit) 
		return ;
	if( m_state == 2 )
	{
		CBF_PMutex pp(&m_mutex);
		string A110packet;
		MakeA110Packet(A110packet);
		int nRet = m_pPoint.fp_api_send_msg( A110packet.c_str(), "");
		if (nRet <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送交易员登出失败 %d",nRet);
			return;
		}
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API发送交易员登出请求");
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送交易员登出请求 [%s]",A110packet.c_str());
	}
	CBF_Date_Time pdate;
	pdate.Update();
	m_nLogoutTime = atoi(pdate.ToStringD8().c_str())*10000+pdate.GetHour()*100+pdate.GetMinute(); 
	return;	
}
void COfferingTrade::TradeLogin()
{
	m_nLoginNum++;
	if( m_state == 0 )
	{
		CBF_PMutex pp(&m_mutex);
		string A000packet;
		MakeA000Packet(A000packet);

		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送接入单元登录请求 [%s]",A000packet.c_str());
		int nRet = m_pPoint.fp_api_send_msg( A000packet.c_str(), "" );
		if (nRet <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送接入单元登录失败 %d",nRet);
			return;
		}
	}
	else if( m_state == 1 )
	{
		CBF_PMutex pp(&m_mutex);
		string A100packet;
		MakeA100Packet(A100packet);

		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送交易员登录请求 [%s]",A100packet.c_str());
		int nRet = m_pPoint.fp_api_send_msg( A100packet.c_str(), "" );
		if (nRet <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送交易员登录失败 %d",nRet);
			return;
		}
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API登陆状态%d",m_state);
	return;
}

bool COfferingTrade::GetFrontIpPort(char *ip, int &port)
{
	int nIpList = m_pListIp.size();
	if (nIpList <1 )
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"未配置交易所IP");
		return false;
	}
	else if (nIpList == 1)
	{
		strcpy(ip,m_pListIp[0].sIp);
		port = m_pListIp[0].nPort;
		return true;
	}
	//在列表中随机选一个IP
	srand(CBF_Date_Time::GetTickCount());
	int id = rand() % nIpList;
	strcpy(ip,m_pListIp[id].sIp);
	port = m_pListIp[id].nPort;


	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"交易所IP%s(%d)", ip, port);
	return true;
}

void COfferingTrade::OnFpApiConnect(void *paramter)
{
	COfferingTrade* offeringTrade = (COfferingTrade*)paramter;
	if( offeringTrade->m_apiPoint->apistruct->cb_.api_cb_connected_ != NULL )
	{
		api_connection_state_t st;
		memcpy( st.ip, offeringTrade->m_sIp, strlen(offeringTrade->m_sIp) );
		st.port = offeringTrade->m_nPort;
		st.state = IS_CONNECTED; 
		offeringTrade->m_apiPoint->apistruct->cb_.api_cb_connected_( &st,offeringTrade->m_apiPoint->apistruct );
	}
	offeringTrade->m_state = 0;
	offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API连接成功");
}

void COfferingTrade::OnFpApiConnectLost(void *paramter)
{
	COfferingTrade* offeringTrade = (COfferingTrade*)paramter;
	if( offeringTrade->m_apiPoint->apistruct->cb_.api_cb_disconnected_ != NULL )
	{
		api_connection_state_t st;
		memcpy( st.ip, offeringTrade->m_sIp, strlen(offeringTrade->m_sIp) );
		st.port = offeringTrade->m_nPort;
		st.state = IS_ERROR_DISCONNECTED; 
		offeringTrade->m_apiPoint->apistruct->cb_.api_cb_disconnected_( &st,offeringTrade->m_apiPoint->apistruct );
	}
	offeringTrade->m_state = 0;
	offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API连接断开");
}

void COfferingTrade::OnFpApiException(const char *exception_code, const char *exception_msg, void *paramter)
{
	COfferingTrade* offeringTrade = (COfferingTrade*)paramter;
	offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"定价api出现错误(%s):%s", exception_code, exception_msg );
}

void COfferingTrade::OnFpApiRecvMsg(const char *packet, void *paramter)
{
	COfferingTrade* offeringTrade = (COfferingTrade*)paramter;
	string gtp_packet = packet;

	if( gtp_packet.find("X03=A001") != string::npos )//接入单元登陆
	{
		if( gtp_packet.find("HJ0000") != string::npos )//接入单元登陆成功，发送交易员登陆
		{

			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"接入单元登录成功：%s", gtp_packet.c_str());
			offeringTrade->m_state = 1;
			string A100packet;
			offeringTrade->MakeA100Packet(A100packet);
			offeringTrade->m_pPoint.fp_api_send_msg( A100packet.c_str(),"" );
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送交易员登录请求：%s", A100packet.c_str() );
		}
		else//接入单元登陆失败，重复登陆
		{
			offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"接入单元登录失败：%s", gtp_packet.c_str() );
			SLEEP_SECONDS( 5 );
			string A000packet;
			offeringTrade->MakeA000Packet( A000packet );
			offeringTrade->m_pPoint.fp_api_send_msg( A000packet.c_str(), "" );
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送接入单元登录请求：%s", A000packet.c_str() );
		}

		return;
	}
	else if( gtp_packet.find("X03=A011") != string::npos )//接入单元登出
	{
		offeringTrade->m_state = 0;
		if( gtp_packet.find("HJ0000") == string::npos )//接入单元失败,重复登出
		{
			offeringTrade->m_state = 1;
			offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"接入单元失败重复登出：%s", gtp_packet.c_str() );
			SLEEP_SECONDS( 5 );
			string A010packet;
			offeringTrade->MakeA010Packet( A010packet );
			offeringTrade->m_pPoint.fp_api_send_msg( A010packet.c_str(), "" );
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送接入单元登出请求：%s", A010packet.c_str() );
		}
	}
	else if( gtp_packet.find("X03=A111") != string::npos )//交易员登出
	{
		offeringTrade->m_state = 2;
		if( offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_!= NULL )
			offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_( gtp_packet.c_str(),GTP_TYPE_STRING,gtp_packet.length(),offeringTrade->m_apiPoint->apistruct );
		if( gtp_packet.find("HJ0000") != string::npos )//交易员登出，发送接入单元登出请求
		{
			offeringTrade->m_state = 1;
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"交易员登出成功：%s", gtp_packet.c_str() );
			string A010packet;
			offeringTrade->MakeA010Packet( A010packet );
			offeringTrade->m_pPoint.fp_api_send_msg( A010packet.c_str(), "" );
			offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送接入单元登出请求：%s", A010packet.c_str() );
		}
		else
		{
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"交易员登出失败重复登出：%s", gtp_packet.c_str() );
			SLEEP_SECONDS(5);
			string A110packet;
			offeringTrade->MakeA110Packet( A110packet );
			offeringTrade->m_pPoint.fp_api_send_msg( A110packet.c_str(), "" );
			offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送交易员登出请求：%s", A110packet.c_str() );
		}
	}
	else if( offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_!= NULL )//交易员登陆及其他报文
	{
		if( gtp_packet.find("X03=A101") != string::npos )
		{
			//兼容主程序的判定
			string::size_type off = gtp_packet.find("HJ0000");
			if ( off != string::npos)
				gtp_packet.replace(off,6,"RSP000000");

			offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_( gtp_packet.c_str(),GTP_TYPE_STRING,gtp_packet.length(),offeringTrade->m_apiPoint->apistruct );
			if( off != string::npos )
			{
				offeringTrade->m_state = 2;
				for( vector<string>::iterator it = offeringTrade->m_packet_buffer.begin();
					it != offeringTrade->m_packet_buffer.end(); 
					++it )
				{
					offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_( 
						(*it).c_str(),
						GTP_TYPE_STRING,
						it->length(),
						offeringTrade->m_apiPoint->apistruct );
				}
				offeringTrade->m_packet_buffer.clear();
			}
		}
		else
		{
			if( offeringTrade->m_state == 2 )
				offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_( gtp_packet.c_str(),GTP_TYPE_STRING,gtp_packet.length(),offeringTrade->m_apiPoint->apistruct );
			else
				offeringTrade->m_packet_buffer.push_back(gtp_packet.c_str());
		}
	}
}
void COfferingTrade::MakeA000Packet(string &packet)
{
	//CGtpData  gtpdata;
	//gtpdata.SetDataItem("X01","GTP1.0");//GTP版本
	//gtpdata.SetDataItem("X02",214);//长度
	//gtpdata.SetDataItem("X03","A000");//消息类型
	//gtpdata.SetDataItem("X04","0");//序列类别号
	//gtpdata.SetDataItem("X05","0");//消息序列号
	//gtpdata.SetDataItem("X06","S");//消息的连续标志
	//gtpdata.SetDataItem("X07","0");//RootID
	//gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
	//gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符

	//gtpdata.SetDataItem("X63","1");//操作标志
	//if (m_sTradeDate.length()<2)
	//{
	//	CBF_Date_Time pdate;
	//	pdate.Update();
	//	gtpdata.SetDataItem("T13",pdate.ToStringD8().c_str());//交易日期
	//}
	//else
	//{
	//	gtpdata.SetDataItem("T13",m_sTradeDate.c_str());//交易日期
	//}
	//gtpdata.SetDataItem("X79","ABCDEFGHIJKL");//随机密钥
	//gtpdata.SetDataItem("X77","ABCDEFGH");//3DES加密向量
	//CGtpData *arrynode = gtpdata.AddDataItem("X20",GTP_DATATYPE_ARRAY);//消息断点信息
	//CGtpData *hashnode = NULL;
	//char tmpchar[100];
	//for (int i=0; i<MAXFLOWNO; i++ )
	//{
	//	sprintf(tmpchar,"%d",i);
	//	hashnode = arrynode->AddDataItem(tmpchar,GTP_DATATYPE_HASH);
	//	hashnode->SetDataItem("X04",m_FlowInfo[i]->nFlowNo);
	//	hashnode->SetDataItem("X05",m_FlowInfo[i]->nMaxSerial);
	//}

	//gtpdata.SetDataItem("X22",m_sAccessUnitId.c_str());//接入单元代码
	//gtpdata.SetDataItem("M00",m_sMemberId.c_str());//会员代码
	//gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位代码
	//gtpdata.SetDataItem("M62",m_sAccessPwd.c_str());//接入单元密码

	//gtpdata.ToString( packet );




	CGtpData  gtphead;
	gtphead.SetDataItem("X01","GTP1.0");//GTP版本
	gtphead.SetDataItem("X02",0);//长度
	gtphead.SetDataItem("X03","A000");//消息类型
	gtphead.SetDataItem("X04","0");//序列类别号
	gtphead.SetDataItem("X05","0");//消息序列号
	gtphead.SetDataItem("X06","S");//消息的连续标志
	gtphead.SetDataItem("X07","0");//RootID
	gtphead.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
	gtphead.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符


	CGtpData  gtpdata;
	gtpdata.SetDataItem("X63","1");//操作标志
	if (m_sTradeDate.length()<2)
	{
		CBF_Date_Time pdate;
		pdate.Update();
		gtpdata.SetDataItem("T13",pdate.ToStringD8().c_str());//交易日期
	}
	else
	{
		gtpdata.SetDataItem("T13",m_sTradeDate.c_str());//交易日期
	}
	gtpdata.SetDataItem("X79","ABCDEFGHIJKL");//随机密钥
	gtpdata.SetDataItem("X77","ABCDEFGH");//3DES加密向量
	CGtpData *arrynode = gtpdata.AddDataItem("X20",GTP_DATATYPE_ARRAY);//消息断点信息
	CGtpData *hashnode = NULL;
	char tmpchar[100];
	for (int i=0; i<MAXFLOWNO; i++ )
	{
		sprintf(tmpchar,"%d",i);
		hashnode = arrynode->AddDataItem(tmpchar,GTP_DATATYPE_HASH);
		hashnode->SetDataItem("X04",m_FlowInfo[i]->nFlowNo);
		hashnode->SetDataItem("X05",m_FlowInfo[i]->nMaxSerial);
	}

	gtpdata.SetDataItem("X22",m_sAccessUnitId.c_str());//接入单元代码
	gtpdata.SetDataItem("M00",m_sMemberId.c_str());//会员代码
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位代码
	gtpdata.SetDataItem("M62",m_sAccessPwd.c_str());//接入单元密码


	std::string gtpdatastring = "";
	gtpdata.ToString(gtpdatastring);
	gtphead.SetDataItem("X02", gtpdatastring.length() + 1);

	std::string gtpheadstring = "";
	gtphead.ToString(gtpheadstring);

	packet = gtpheadstring + "," + gtpdatastring;


}

void COfferingTrade::MakeA010Packet(string &packet)
{
	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP版本
	gtpdata.SetDataItem("X02",40);//长度
	gtpdata.SetDataItem("X03","A010");//消息类型
	gtpdata.SetDataItem("X04","0");//序列类别号
	gtpdata.SetDataItem("X05","0");//消息序列号
	gtpdata.SetDataItem("X06","S");//消息的连续标志
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符

	gtpdata.SetDataItem("X63","1");//操作标志
	gtpdata.SetDataItem("X22",m_sAccessUnitId.c_str());//交易员
	gtpdata.SetDataItem("M00",m_sMemberId.c_str());//会员
	gtpdata.SetDataItem("M20",m_sSeatNo);//席位代码

	gtpdata.ToString( packet );
}

void COfferingTrade::MakeA100Packet(string &packet)
{
	CGtpData  gtphead;
	gtphead.SetDataItem("X01","GTP1.0");//GTP版本
	gtphead.SetDataItem("X02",0);//长度
	gtphead.SetDataItem("X03","A100");//消息类型
	gtphead.SetDataItem("X04","0");//序列类别号
	gtphead.SetDataItem("X05","0");//消息序列号
	gtphead.SetDataItem("X06","S");//消息的连续标志
	gtphead.SetDataItem("X07","1");//RootID
	gtphead.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
	gtphead.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符


	CGtpData  gtpdata;
	gtpdata.SetDataItem("X63","1");//操作标志
	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//交易员
	gtpdata.SetDataItem("M00",m_sMemberId.c_str());//会员
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位代码
	gtpdata.SetDataItem("M62",m_sTradePwd.c_str());//交易员密码
	if (m_sTradeDate.length()<2)
	{
		CBF_Date_Time pdate;
		pdate.Update();
		gtpdata.SetDataItem("T13",pdate.ToStringD8().c_str());//交易日期
	}
	else
	{
		gtpdata.SetDataItem("T13",m_sTradeDate.c_str());//交易日期
	}
	std::string gtpdatastring = "";
	gtpdata.ToString(gtpdatastring);
	gtphead.SetDataItem("X02", gtpdatastring.length() +1);

	std::string gtpheadstring = "";
	gtphead.ToString(gtpheadstring);

	packet = gtpheadstring + "," + gtpdatastring;

}

void COfferingTrade::MakeA110Packet(string &packet)
{
	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP版本
	gtpdata.SetDataItem("X02",39);//长度
	gtpdata.SetDataItem("X03","A110");//消息类型
	gtpdata.SetDataItem("X04","0");//序列类别号
	gtpdata.SetDataItem("X05","0");//消息序列号
	gtpdata.SetDataItem("X06","S");//消息的连续标志
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符



	gtpdata.SetDataItem("X63","1");//操作标志
	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//交易员
	gtpdata.SetDataItem("M00",m_sMemberId.c_str());//会员
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位代码

	gtpdata.ToString(packet);
}

bool COfferingTrade::CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
{
	if (ctx == m_apiPoint->apistruct)
	{
		m_nApiStatus = cs->state;
		m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"CB_Disconnected 和交易所前置断开[%s %d] 状态%d",\
			cs->ip,cs->port,cs->state);
		--(ctx->connected_count_);
		//连接断开 重设前置IP
		if (!GetFrontIpPort(m_sIp,m_nPort))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"无交易所前置IP及端口");
			return false;
		}
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"断开连接，下次连接的交易所前置端口[%s %d]",m_sIp,m_nPort);
		//发送录出回报
		
		CGtpData  gtpdata;
		gtpdata.SetDataItem("X01","GTP1.0");//GTP版本
		gtpdata.SetDataItem("X02","0000");//长度
		if (m_sNodeType.compare("12") == 0)
		{
			gtpdata.SetDataItem("X03","A311");//消息类型
		}
		else
		{
			gtpdata.SetDataItem("X03","A111");//消息类型
		}
		
		gtpdata.SetDataItem("X04","1");//序列类别号
		gtpdata.SetDataItem("X05","1");//消息序列号
		gtpdata.SetDataItem("X06","L");//消息的连续标志
		gtpdata.SetDataItem("X07","0");//RootID
		gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
		gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符
		
		gtpdata.SetDataItem("M60",m_sTradeId.c_str());//交易员代码
		gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位号
		gtpdata.SetDataItem("X39","RSP000000");//响应码
		gtpdata.SetDataItem("X40","api断开连接");//响应信息
		std::string sLogGtp;
		if (gtpdata.ToString(sLogGtp))
		{
			ctx->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),ctx);
		}
	}
	else
	{
		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"CB_Disconnected 返回不是本API的");
	}
	return true;
}


void COfferingTrade::Disconnect()
{
	CIOfferingBase::Disconnect();
	
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"断开api连接 api_disconnect");
	//发送录出回报
	m_nConnectTime = time(NULL);
	
	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP版本
	gtpdata.SetDataItem("X02","0000");//长度
	if (m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X03","A311");//消息类型
	}
	else
	{
		gtpdata.SetDataItem("X03","A111");//消息类型
	}
	
	gtpdata.SetDataItem("X04","1");//序列类别号
	gtpdata.SetDataItem("X05","1");//消息序列号
	gtpdata.SetDataItem("X06","L");//消息的连续标志
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符
	
	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//交易员代码
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位号
	gtpdata.SetDataItem("X39","RSP000000");//响应码
	gtpdata.SetDataItem("X40","api断开连接");//响应信息
	std::string sLogGtp;
	if (gtpdata.ToString(sLogGtp))
	{
		m_apiPoint->apistruct->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),m_apiPoint->apistruct);
	}
}
