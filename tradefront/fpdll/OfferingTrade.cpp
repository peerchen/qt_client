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

	AddFuncInfo("A000",(SgeFuncPointer)&COfferingTrade::SendMsg,"���뵥Ԫ��¼");
	AddFuncInfo("A010",(SgeFuncPointer)&COfferingTrade::SendMsg,"���뵥Ԫ�ǳ�");
	AddFuncInfo("A100",(SgeFuncPointer)&COfferingTrade::SendMsg,"����Ա��¼");
	AddFuncInfo("A110",(SgeFuncPointer)&COfferingTrade::SendMsg,"����Ա�ǳ�");
	AddFuncInfo("Q380",(SgeFuncPointer)&COfferingTrade::SendMsg,"��滥�����򷢲�");
	AddFuncInfo("T520",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ο���¼��");
	AddFuncInfo("T530",(SgeFuncPointer)&COfferingTrade::SendMsg,"����ί�б���");
	AddFuncInfo("T540",(SgeFuncPointer)&COfferingTrade::SendMsg,"����ί�г���");
	AddFuncInfo("T650",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ο��۱�����ˮ��ѯ");
	AddFuncInfo("T660",(SgeFuncPointer)&COfferingTrade::SendMsg,"����ί���걨��ˮ��ѯ");
	AddFuncInfo("M650",(SgeFuncPointer)&COfferingTrade::SendMsg,"������ʱ��ͬ��");


	printf("API����");
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
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API����");
	
}

bool COfferingTrade::Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg)
{

 	bool bRet = CIOfferingBase::Init(api,log,xml,xmlnode,errmsg);

	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API��ʼ����ʼ");
	if (!bRet)
	{
		return bRet;
	}
 	//�򿪶�̬��
 	std::string dllname;
#ifdef _WINDOWS
 	dllname = "FpApi.dll";
 #else
	dllname = "libfpapi.so";
#endif	

	m_pDllApiHandle = LOADDLL(dllname.c_str());
// 	if (ISNOTOPEN(m_pDllApiHandle))
// 	{
// 		sprintf(errmsg,"�򿪶�̬��%sʧ�� ������%d",dllname.c_str(),GET_LAST_SOCK_ERROR());
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
// 		return false;
// 	}
#ifdef _WINDOWS
	if (ISNOTOPEN(m_pDllApiHandle))
	{
		sprintf(errmsg,"�򿪶�̬��%sʧ�� ������%d",dllname.c_str(),GetLastError());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#else
	char *err = dlerror();
	if (err != NULL)
	{
		sprintf(errmsg,"�򿪶�̬��%sʧ�� ����[%s]",dllname.c_str(),err);
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
         sprintf(errmsg,"ȡ��̬��[%s]��ĺ�����ַʧ��",dllname.c_str());
 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
         return false;
     }

	 if (m_sNodeType.compare("20") ==0) //���۱��̻�
	 {
		 char xmlnodepath[100];
		 sprintf(xmlnodepath,"%s/��Ա����",xmlnode);
		 if (xml->GetNodeValueByPath(xmlnodepath,false,m_sMemberId,false) == NULL)
		 {
			 sprintf(errmsg,"�����ļ�[%s]������",xmlnodepath);
			 m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			 return false;
		 }
		 sprintf(xmlnodepath,"%s/��������",xmlnode);
		 if (xml->GetNodeValueByPath(xmlnodepath,false,m_sTradeDate,false) == NULL)
		 {
			 sprintf(errmsg,"�����ļ�[%s]������",xmlnodepath);
			 m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			 return false;
		 }

	 }
	 m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API��ʼ���ɹ�");

	return true;
}
int  COfferingTrade::SendMsg(CGtpData *senddata)
{
	//�ж������Ƿ�����
	if (m_nApiStatus != 1 || m_nApiLoginStatus != 1)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������״̬Ϊδ���ӻ�δ��¼");
		return -1;
	}
	CBF_PMutex pp(&m_mutex);
	//��������
	std::string gtpstring;
	if (!senddata->ToString(gtpstring))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ToString����");
		return -1;
	}
	
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"Ҫ���͵�GTP���� [%s]",gtpstring.c_str());

	int head = gtpstring.find("X09");
	int index = gtpstring.find(",",head);
	int ret = m_pPoint.fp_api_send_msg( gtpstring.substr(0,index).c_str(), gtpstring.substr(index+1).c_str() );

	if (ret <0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"fp_api_send_msg ���ͳ��� %d",ret);
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
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�޽�����ǰ��IP���˿�");
        return false;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"�������ӵĽ�����ǰ�ö˿�[%s %d]",m_sIp,m_nPort);
	//��ʼ��api    
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
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������api_init����");
        return false;
	}


	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API����");
	m_nSendReqTime = time(NULL);
	m_nRcvBackTime = time(NULL);
	m_nRcvAnsTime = time(NULL);

	return true;
}
bool COfferingTrade::StopApi()
{
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"APIֹͣ��%d��", m_bIsInit);

	if( !m_bIsInit) 
		return true;
	
	CBF_PMutex pp(&m_mutex);
	//���ͽ���Ա¼��ָ��
	//TradeLogout();

	//�ͷ�api
	m_pPoint.fp_api_free();

	
	SLEEP_SECONDS(5);

	//�ȴ��߳���ֹ
	//m_pPoint.fp_api_wait();
	//ֹͣ��־�߳�
	//m_pPoint.fp_api_log_end();

	m_bIsInit = false;

	CBF_Date_Time pdate;
	pdate.Update();
	m_nLogoutTime = atoi(pdate.ToStringD8().c_str())*10000+pdate.GetHour()*100+pdate.GetMinute(); 
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"APIֹͣ��%d�����", m_bIsInit);
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
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ���Ա�ǳ�ʧ�� %d",nRet);
			return;
		}
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API���ͽ���Ա�ǳ�����");
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ͽ���Ա�ǳ����� [%s]",A110packet.c_str());
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

		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ͽ��뵥Ԫ��¼���� [%s]",A000packet.c_str());
		int nRet = m_pPoint.fp_api_send_msg( A000packet.c_str(), "" );
		if (nRet <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ��뵥Ԫ��¼ʧ�� %d",nRet);
			return;
		}
	}
	else if( m_state == 1 )
	{
		CBF_PMutex pp(&m_mutex);
		string A100packet;
		MakeA100Packet(A100packet);

		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ͽ���Ա��¼���� [%s]",A100packet.c_str());
		int nRet = m_pPoint.fp_api_send_msg( A100packet.c_str(), "" );
		if (nRet <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ���Ա��¼ʧ�� %d",nRet);
			return;
		}
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API��½״̬%d",m_state);
	return;
}

bool COfferingTrade::GetFrontIpPort(char *ip, int &port)
{
	int nIpList = m_pListIp.size();
	if (nIpList <1 )
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"δ���ý�����IP");
		return false;
	}
	else if (nIpList == 1)
	{
		strcpy(ip,m_pListIp[0].sIp);
		port = m_pListIp[0].nPort;
		return true;
	}
	//���б������ѡһ��IP
	srand(CBF_Date_Time::GetTickCount());
	int id = rand() % nIpList;
	strcpy(ip,m_pListIp[id].sIp);
	port = m_pListIp[id].nPort;


	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"������IP%s(%d)", ip, port);
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
	offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API���ӳɹ�");
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
	offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"API���ӶϿ�");
}

void COfferingTrade::OnFpApiException(const char *exception_code, const char *exception_msg, void *paramter)
{
	COfferingTrade* offeringTrade = (COfferingTrade*)paramter;
	offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����api���ִ���(%s):%s", exception_code, exception_msg );
}

void COfferingTrade::OnFpApiRecvMsg(const char *packet, void *paramter)
{
	COfferingTrade* offeringTrade = (COfferingTrade*)paramter;
	string gtp_packet = packet;

	if( gtp_packet.find("X03=A001") != string::npos )//���뵥Ԫ��½
	{
		if( gtp_packet.find("HJ0000") != string::npos )//���뵥Ԫ��½�ɹ������ͽ���Ա��½
		{

			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���뵥Ԫ��¼�ɹ���%s", gtp_packet.c_str());
			offeringTrade->m_state = 1;
			string A100packet;
			offeringTrade->MakeA100Packet(A100packet);
			offeringTrade->m_pPoint.fp_api_send_msg( A100packet.c_str(),"" );
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ͽ���Ա��¼����%s", A100packet.c_str() );
		}
		else//���뵥Ԫ��½ʧ�ܣ��ظ���½
		{
			offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���뵥Ԫ��¼ʧ�ܣ�%s", gtp_packet.c_str() );
			SLEEP_SECONDS( 5 );
			string A000packet;
			offeringTrade->MakeA000Packet( A000packet );
			offeringTrade->m_pPoint.fp_api_send_msg( A000packet.c_str(), "" );
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ͽ��뵥Ԫ��¼����%s", A000packet.c_str() );
		}

		return;
	}
	else if( gtp_packet.find("X03=A011") != string::npos )//���뵥Ԫ�ǳ�
	{
		offeringTrade->m_state = 0;
		if( gtp_packet.find("HJ0000") == string::npos )//���뵥Ԫʧ��,�ظ��ǳ�
		{
			offeringTrade->m_state = 1;
			offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���뵥Ԫʧ���ظ��ǳ���%s", gtp_packet.c_str() );
			SLEEP_SECONDS( 5 );
			string A010packet;
			offeringTrade->MakeA010Packet( A010packet );
			offeringTrade->m_pPoint.fp_api_send_msg( A010packet.c_str(), "" );
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ͽ��뵥Ԫ�ǳ�����%s", A010packet.c_str() );
		}
	}
	else if( gtp_packet.find("X03=A111") != string::npos )//����Ա�ǳ�
	{
		offeringTrade->m_state = 2;
		if( offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_!= NULL )
			offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_( gtp_packet.c_str(),GTP_TYPE_STRING,gtp_packet.length(),offeringTrade->m_apiPoint->apistruct );
		if( gtp_packet.find("HJ0000") != string::npos )//����Ա�ǳ������ͽ��뵥Ԫ�ǳ�����
		{
			offeringTrade->m_state = 1;
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"����Ա�ǳ��ɹ���%s", gtp_packet.c_str() );
			string A010packet;
			offeringTrade->MakeA010Packet( A010packet );
			offeringTrade->m_pPoint.fp_api_send_msg( A010packet.c_str(), "" );
			offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ��뵥Ԫ�ǳ�����%s", A010packet.c_str() );
		}
		else
		{
			offeringTrade->m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"����Ա�ǳ�ʧ���ظ��ǳ���%s", gtp_packet.c_str() );
			SLEEP_SECONDS(5);
			string A110packet;
			offeringTrade->MakeA110Packet( A110packet );
			offeringTrade->m_pPoint.fp_api_send_msg( A110packet.c_str(), "" );
			offeringTrade->m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ���Ա�ǳ�����%s", A110packet.c_str() );
		}
	}
	else if( offeringTrade->m_apiPoint->apistruct->cb_.api_recv_msg_!= NULL )//����Ա��½����������
	{
		if( gtp_packet.find("X03=A101") != string::npos )
		{
			//������������ж�
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
	//gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	//gtpdata.SetDataItem("X02",214);//����
	//gtpdata.SetDataItem("X03","A000");//��Ϣ����
	//gtpdata.SetDataItem("X04","0");//��������
	//gtpdata.SetDataItem("X05","0");//��Ϣ���к�
	//gtpdata.SetDataItem("X06","S");//��Ϣ��������־
	//gtpdata.SetDataItem("X07","0");//RootID
	//gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	//gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��

	//gtpdata.SetDataItem("X63","1");//������־
	//if (m_sTradeDate.length()<2)
	//{
	//	CBF_Date_Time pdate;
	//	pdate.Update();
	//	gtpdata.SetDataItem("T13",pdate.ToStringD8().c_str());//��������
	//}
	//else
	//{
	//	gtpdata.SetDataItem("T13",m_sTradeDate.c_str());//��������
	//}
	//gtpdata.SetDataItem("X79","ABCDEFGHIJKL");//�����Կ
	//gtpdata.SetDataItem("X77","ABCDEFGH");//3DES��������
	//CGtpData *arrynode = gtpdata.AddDataItem("X20",GTP_DATATYPE_ARRAY);//��Ϣ�ϵ���Ϣ
	//CGtpData *hashnode = NULL;
	//char tmpchar[100];
	//for (int i=0; i<MAXFLOWNO; i++ )
	//{
	//	sprintf(tmpchar,"%d",i);
	//	hashnode = arrynode->AddDataItem(tmpchar,GTP_DATATYPE_HASH);
	//	hashnode->SetDataItem("X04",m_FlowInfo[i]->nFlowNo);
	//	hashnode->SetDataItem("X05",m_FlowInfo[i]->nMaxSerial);
	//}

	//gtpdata.SetDataItem("X22",m_sAccessUnitId.c_str());//���뵥Ԫ����
	//gtpdata.SetDataItem("M00",m_sMemberId.c_str());//��Ա����
	//gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ����
	//gtpdata.SetDataItem("M62",m_sAccessPwd.c_str());//���뵥Ԫ����

	//gtpdata.ToString( packet );




	CGtpData  gtphead;
	gtphead.SetDataItem("X01","GTP1.0");//GTP�汾
	gtphead.SetDataItem("X02",0);//����
	gtphead.SetDataItem("X03","A000");//��Ϣ����
	gtphead.SetDataItem("X04","0");//��������
	gtphead.SetDataItem("X05","0");//��Ϣ���к�
	gtphead.SetDataItem("X06","S");//��Ϣ��������־
	gtphead.SetDataItem("X07","0");//RootID
	gtphead.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	gtphead.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��


	CGtpData  gtpdata;
	gtpdata.SetDataItem("X63","1");//������־
	if (m_sTradeDate.length()<2)
	{
		CBF_Date_Time pdate;
		pdate.Update();
		gtpdata.SetDataItem("T13",pdate.ToStringD8().c_str());//��������
	}
	else
	{
		gtpdata.SetDataItem("T13",m_sTradeDate.c_str());//��������
	}
	gtpdata.SetDataItem("X79","ABCDEFGHIJKL");//�����Կ
	gtpdata.SetDataItem("X77","ABCDEFGH");//3DES��������
	CGtpData *arrynode = gtpdata.AddDataItem("X20",GTP_DATATYPE_ARRAY);//��Ϣ�ϵ���Ϣ
	CGtpData *hashnode = NULL;
	char tmpchar[100];
	for (int i=0; i<MAXFLOWNO; i++ )
	{
		sprintf(tmpchar,"%d",i);
		hashnode = arrynode->AddDataItem(tmpchar,GTP_DATATYPE_HASH);
		hashnode->SetDataItem("X04",m_FlowInfo[i]->nFlowNo);
		hashnode->SetDataItem("X05",m_FlowInfo[i]->nMaxSerial);
	}

	gtpdata.SetDataItem("X22",m_sAccessUnitId.c_str());//���뵥Ԫ����
	gtpdata.SetDataItem("M00",m_sMemberId.c_str());//��Ա����
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ����
	gtpdata.SetDataItem("M62",m_sAccessPwd.c_str());//���뵥Ԫ����


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
	gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	gtpdata.SetDataItem("X02",40);//����
	gtpdata.SetDataItem("X03","A010");//��Ϣ����
	gtpdata.SetDataItem("X04","0");//��������
	gtpdata.SetDataItem("X05","0");//��Ϣ���к�
	gtpdata.SetDataItem("X06","S");//��Ϣ��������־
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��

	gtpdata.SetDataItem("X63","1");//������־
	gtpdata.SetDataItem("X22",m_sAccessUnitId.c_str());//����Ա
	gtpdata.SetDataItem("M00",m_sMemberId.c_str());//��Ա
	gtpdata.SetDataItem("M20",m_sSeatNo);//ϯλ����

	gtpdata.ToString( packet );
}

void COfferingTrade::MakeA100Packet(string &packet)
{
	CGtpData  gtphead;
	gtphead.SetDataItem("X01","GTP1.0");//GTP�汾
	gtphead.SetDataItem("X02",0);//����
	gtphead.SetDataItem("X03","A100");//��Ϣ����
	gtphead.SetDataItem("X04","0");//��������
	gtphead.SetDataItem("X05","0");//��Ϣ���к�
	gtphead.SetDataItem("X06","S");//��Ϣ��������־
	gtphead.SetDataItem("X07","1");//RootID
	gtphead.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	gtphead.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��


	CGtpData  gtpdata;
	gtpdata.SetDataItem("X63","1");//������־
	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա
	gtpdata.SetDataItem("M00",m_sMemberId.c_str());//��Ա
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ����
	gtpdata.SetDataItem("M62",m_sTradePwd.c_str());//����Ա����
	if (m_sTradeDate.length()<2)
	{
		CBF_Date_Time pdate;
		pdate.Update();
		gtpdata.SetDataItem("T13",pdate.ToStringD8().c_str());//��������
	}
	else
	{
		gtpdata.SetDataItem("T13",m_sTradeDate.c_str());//��������
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
	gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	gtpdata.SetDataItem("X02",39);//����
	gtpdata.SetDataItem("X03","A110");//��Ϣ����
	gtpdata.SetDataItem("X04","0");//��������
	gtpdata.SetDataItem("X05","0");//��Ϣ���к�
	gtpdata.SetDataItem("X06","S");//��Ϣ��������־
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��



	gtpdata.SetDataItem("X63","1");//������־
	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա
	gtpdata.SetDataItem("M00",m_sMemberId.c_str());//��Ա
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ����

	gtpdata.ToString(packet);
}

bool COfferingTrade::CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
{
	if (ctx == m_apiPoint->apistruct)
	{
		m_nApiStatus = cs->state;
		m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"CB_Disconnected �ͽ�����ǰ�öϿ�[%s %d] ״̬%d",\
			cs->ip,cs->port,cs->state);
		--(ctx->connected_count_);
		//���ӶϿ� ����ǰ��IP
		if (!GetFrontIpPort(m_sIp,m_nPort))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�޽�����ǰ��IP���˿�");
			return false;
		}
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�Ͽ����ӣ��´����ӵĽ�����ǰ�ö˿�[%s %d]",m_sIp,m_nPort);
		//����¼���ر�
		
		CGtpData  gtpdata;
		gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
		gtpdata.SetDataItem("X02","0000");//����
		if (m_sNodeType.compare("12") == 0)
		{
			gtpdata.SetDataItem("X03","A311");//��Ϣ����
		}
		else
		{
			gtpdata.SetDataItem("X03","A111");//��Ϣ����
		}
		
		gtpdata.SetDataItem("X04","1");//��������
		gtpdata.SetDataItem("X05","1");//��Ϣ���к�
		gtpdata.SetDataItem("X06","L");//��Ϣ��������־
		gtpdata.SetDataItem("X07","0");//RootID
		gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
		gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��
		
		gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա����
		gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ��
		gtpdata.SetDataItem("X39","RSP000000");//��Ӧ��
		gtpdata.SetDataItem("X40","api�Ͽ�����");//��Ӧ��Ϣ
		std::string sLogGtp;
		if (gtpdata.ToString(sLogGtp))
		{
			ctx->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),ctx);
		}
	}
	else
	{
		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"CB_Disconnected ���ز��Ǳ�API��");
	}
	return true;
}


void COfferingTrade::Disconnect()
{
	CIOfferingBase::Disconnect();
	
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�Ͽ�api���� api_disconnect");
	//����¼���ر�
	m_nConnectTime = time(NULL);
	
	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	gtpdata.SetDataItem("X02","0000");//����
	if (m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X03","A311");//��Ϣ����
	}
	else
	{
		gtpdata.SetDataItem("X03","A111");//��Ϣ����
	}
	
	gtpdata.SetDataItem("X04","1");//��������
	gtpdata.SetDataItem("X05","1");//��Ϣ���к�
	gtpdata.SetDataItem("X06","L");//��Ϣ��������־
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��
	
	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա����
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ��
	gtpdata.SetDataItem("X39","RSP000000");//��Ӧ��
	gtpdata.SetDataItem("X40","api�Ͽ�����");//��Ӧ��Ϣ
	std::string sLogGtp;
	if (gtpdata.ToString(sLogGtp))
	{
		m_apiPoint->apistruct->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),m_apiPoint->apistruct);
	}
}
