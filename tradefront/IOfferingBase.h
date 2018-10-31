// IOfferingBase.h: interface for the CIOfferingBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOFFERINGBASE_H__40779290_A4D2_4574_BBCC_7885BED1E661__INCLUDED_)
#define AFX_IOFFERINGBASE_H__40779290_A4D2_4574_BBCC_7885BED1E661__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "BF_Queue.h"
#include "GtpProtocol.h"
#include "BF_Xml.h"
#include "BF_Tools.h"
#include "SgeFuncTbl.h"
#include "BF_Thread.h"
#include "api.h"
#include "sge_api_safe_interface.h"


//���̻��ӿڻ���
//�������̻��̳д˻���ʵ��
// </�ʽ�ִ����̻�>
// 	<DLLNAME method="getInstance" >trade.so</DLLNAME>
// 	<ħ�� remark="GTP����ͷ��ħ��" >1123</ħ��>
// 	<��ȫ��֤ remark="�Ϻ�CA������">
// 		<key_path remark="UserKey.key�ļ�·��" >/home/appgess/ylink/tfront/shca</key_path>
// 		<rootcrt_path remark="RootCert.der�ļ�·��" >/home/appgess/ylink/tfront/shca</rootcrt_path>
// 		<svr_cert_path remark="server.der�ļ�·��" >/home/appgess/ylink/tfront/shca</svr_cert_path>
// 		<cli_cert_path remark="UserCert.der�ļ�·��" >/home/appgess/ylink/tfront/shca</cli_cert_path>
// 		<֤������ remark="֤������,Ĭ��123412" >123412</֤������>
// 	</��ȫ��֤>
// 	<����Ա remark="��¼�������Ľ���Ա" >jy</����Ա>
// 	<����Ա���� remark="" >1123</����Ա����>
// 	<���뵥Ԫ remark="���ӽ������Ľ��뵥Ԫ" >jy</���뵥Ԫ>
// 	<���뵥Ԫ���� remark="���ӽ������Ľ��뵥Ԫ����" >888888</���뵥Ԫ����>
// 	<ǰ������ remark="���ý�������ǰ�ã������Ͽɳ�����һ��">
// 		<front ip="127.0.0.1" port="9011" remark="����Ҫ����ǰ�õĲ���" />
// 		<front ip="127.0.0.1" port="9012" remark="����Ҫ����ǰ�õĲ���" />
// 	</ǰ������>
// </�ʽ�ִ����̻�>



// ������	��Ϣ��������
// ������	1
// �ر���	2
// ˽����	3
// ������	4
// ��ѯ��	5
// ������	6

typedef struct 
{
	int           nFlowNo;//��Ϣ����
	int  nMaxSerial;//�����ˮ��
}S_FLOW_INFO;
#define  MAXFLOWNO     6

typedef struct 
{
	api_t * api_;
	api_cb_t cb_;
	api_safe_handle_t safe_handle_;
	volatile unsigned int recv_count_;
	volatile unsigned int connected_count_;
}S_SGE_GEMS2_API_STRUCT;  //��Ӧctx_t

typedef struct
{
	S_SGE_GEMS2_API_STRUCT *apistruct;//����api���á�handle���ص��ȵĽṹ
	CIOfferingBase         *apiPoint;//����api��dll����ָ��
	UINT64_                apistructpvalue; //���apistructָ���ֵ
	DLLHANDLE              apidllhandle;//��̬����
	std::string            apidllname;//��̬������
	std::string            apiInstance;//ʵ���ĺ�����
	std::string            apidllpath;//��̬��·��������
	std::string            offernodepath;//�������ڵĽڵ�·��
}S_SGE_GEMS2_API;


typedef struct 
{
	char  sIp[33];
	unsigned short  nPort;
}S_FRONT_IPPORT;

typedef CBF_Stack<S_GTP_MSG> GTPMSG_QUEUE;


class CIOfferingBase  
{
public:
	CIOfferingBase()
	{
		m_apiPoint = NULL;
		m_pLog  = NULL;
		m_bInit = false;
		m_bIsRunning = false;
		m_nApiStatus = 0;
		m_nApiLoginStatus = 0;
		bzero(m_sIp,sizeof(m_sIp));
		m_nPort = 0;
		m_nPwdFlag = 0;
		m_nLoginNum = 0;
		m_nConnectTime = time(NULL);
		m_nDisconnectTime = time(NULL);
		m_nLogoutTime = 0;

	}
	virtual ~CIOfferingBase()
	{
		//�ͷŻ���
	}
	// ������: Init
	// ���  : ������ 2016-3-11 11:29:23
	// ����  : virtual bool 
	// �����������  : S_SGE_GEMS2_API *api  apiָ�룬�����ص�������api��handle��ca��handle
	// �������  : CIErrlog *log     ��־ָ�룬���̳�д��־
	// �������  : CBF_Xml *xml      �������Ե�xml��
	// �������  : const char *xmlnode  ����̬���Ӧ��xml���ýڵ㣬������˵��
	// �������  : char *errmsg  ������Ϣ
	// ����  : ��ʼ��
	virtual bool Init(S_SGE_GEMS2_API *api,CIErrlog *log,const char *xmlfile,const char *xmlnode,char *errmsg)
	{
		CBF_Xml xml;
		if (!xml.FromFile(xmlfile))
		{
			sprintf(errmsg,"XML�ļ�[%s]�����ڻ�Ƿ�xml",xmlfile);
			return false;
		}
		return Init(api,log,&xml,xmlnode,errmsg);
	}

	// ������: Init
	// ���  : ������ 2016-3-11 11:29:23
	// ����  : virtual bool 
	// �����������  : S_SGE_GEMS2_API *api  apiָ�룬�����ص�������api��handle��ca��handle
	// �������  : CIErrlog *log     ��־ָ�룬���̳�д��־
	// �������  : CBF_Xml *xml      �������Ե�xml��
	// �������  : const char *xmlnode  ����̬���Ӧ��xml���ýڵ㣬������˵��
	// �������  : char *errmsg  ������Ϣ
	// ����  : ��ʼ��
	virtual bool Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg)
	{
		m_apiPoint = api;
		m_pLog = log;
		char nodename[512];
		
		CXmlNode *offeringnode = xml->GetNodeByPath(xmlnode,false);
		if (offeringnode == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",xmlnode);
			return false;
		}
		m_sOfferingName = offeringnode->GetNodeName(false);
		
		sprintf(nodename,"%s/ħ��",xmlnode);
		std::string ss;
		if (xml->GetNodeValueByPath(nodename,false,ss,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}

		sprintf(nodename,"%s/�ڵ�����",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sNodeType,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}

		
		m_magicNum = atol(ss.c_str());
		sprintf(nodename,"%s/����Ա",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sTradeId,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/����Ա����",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sTradePwd,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/֤������",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sCertNo,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/���ͷ���ʶ",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sSendFlag,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/���շ���ʶ",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sRcvFlag,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/������ܱ�־",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_nPwdFlag) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
//		printf("%s=%d\n",nodename,m_nPwdFlag);

		sprintf(nodename,"%s/���뵥Ԫ",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sAccessUnitId,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/���뵥Ԫ����",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sAccessPwd,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/��ȫ��֤/key_path",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sPath_key,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/��ȫ��֤/rootcrt_path",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sPath_root,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/��ȫ��֤/svr_cert_path",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sPath_svr,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/��ȫ��֤/cli_cert_path",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sPath_user,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/��ȫ��֤/֤������",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sCertPwd,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		sprintf(nodename,"%s/ǰ������",xmlnode);
		CXmlNode *fnode = xml->GetNodeByPath(nodename,false);
		if (fnode == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		fnode = (CXmlNode *)fnode->GetFirstChild();
		if (fnode  == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]���ӽڵ�",nodename);
			return false;
		}
		S_FRONT_IPPORT fconf;
		while (fnode != NULL)
		{
			bzero(&fconf,sizeof(S_FRONT_IPPORT));
			if (fnode->GetAttribute("ip",false,ss,false) == NULL)
			{
				sprintf(errmsg,"XML�ڵ�[%s/%s]��ip����",nodename,fnode->GetNodeName(false).c_str());
				return false;
			}
			CBF_Tools::StringCopy(fconf.sIp,32,ss.c_str());
			if (fnode->GetAttribute("port",false,ss,false) == NULL)
			{
				sprintf(errmsg,"XML�ڵ�[%s/%s]��port����",nodename,fnode->GetNodeName(false).c_str());
				return false;
			}
			fconf.nPort= atoi(ss.c_str());
			m_pListIp.push_back(fconf);
			fnode = (CXmlNode *)fnode->getNextSibling();
		}
		//��ȡ��������
		sprintf(nodename,"%s/����ע��",xmlnode);
		fnode = xml->GetNodeByPath(nodename,false);
		if (fnode == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		bool bIsRegUse=false;
		CXmlAttribute *attr =  fnode->GetAttribute("use",false);
		if (attr == NULL)
		{
			bIsRegUse=false;
		}
		else
		{
			if (atoi(attr->GetAttrValue(false).c_str()) == 1)
			{
				bIsRegUse=true;
			}
		}
		if (bIsRegUse)
		{
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"ʹ�������ļ���Ľ���ע��");
			fnode = (CXmlNode *)fnode->GetFirstChild();
			if (fnode  == NULL)
			{
				sprintf(errmsg,"XML�ڵ�[%s]���ӽڵ�",nodename);
				return false;
			}
			//���������ע��Ľ���
			m_pTblFunc.Clear();

			while (fnode != NULL)
			{
				//�������еĽ��׼ӵ��б�
				AddFuncInfo(fnode->GetNodeName(false).c_str(),&CIOfferingBase::SendMsg,fnode->GetNodeValue(false).c_str());
				fnode = (CXmlNode *)fnode->getNextSibling();
			}
		}
		
//		printf("IOfferingBase init api_cb_connected_[%x] api_cb_disconnected_[%x] \n",m_apiPoint->apistruct->cb_.api_cb_connected_,m_apiPoint->apistruct->cb_.api_cb_disconnected_);

		//��ʼ��ʼ����������api��CA������
		
		m_bInit = true;
		return true;
	}


	// ������:  SendMsg
	// ���  : ������ 2016-3-11 11:34:50
	// ����  : virtual int 
	// ����  : const char *gtpmsg  gtp��Ϣ������������
	// ����  : unsigned short gtplen
	// ����  : ����ҵ������
	virtual int  SendMsg(CGtpData *senddata)=0;

	// ������: CB_Connected
	// ���  : ������ 2016-3-11 15:44:49
	// ����  : virtual bool 
	// ����  : api_connection_state_t * cs   ����״̬
	// ����  : S_SGE_GEMS2_API_STRUCT *ctx   api����
	// ����  : API�Ļص����������ӳɹ��ˣ�Ҫ�����淢��¼
	virtual bool CB_Connected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
	{
		if (ctx == m_apiPoint->apistruct)
		{
			m_nConnectTime = time(NULL);
			m_nApiStatus = cs->state;
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"CB_Connected �ͽ�����ǰ��������[%s %d] ״̬%d",\
				cs->ip,cs->port,cs->state);
			++(ctx->connected_count_);
			//Ҫ���͵�¼����
			m_nApiLoginStatus = 0;
			m_nSendReqTime = time(NULL);
			m_nRcvBackTime = time(NULL);
			m_nRcvAnsTime = time(NULL);
			TradeLogin();

		}
		else
		{
			m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"CB_Connected ���ز��Ǳ�API��");
		}
		return true;
	}


	// ������: CB_Disconnected
	// ���  : ������ 2016-3-11 15:44:43
	// ����  : virtual bool 
	// ����  : api_connection_state_t * cs
	// ����  : S_SGE_GEMS2_API_STRUCT *ctx
	// ����  : api�ص����� �Ͽ�������  Ҫ�ͷ�api�������Ա��ٴ�����
	virtual bool CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
	{
		if (ctx == m_apiPoint->apistruct)
		{
			m_nDisconnectTime = time(NULL);
			m_nApiStatus = cs->state;
			m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"CB_Disconnected �ͽ�����ǰ�öϿ�[%s %d] ״̬%d",\
				cs->ip,cs->port,cs->state);
			--(ctx->connected_count_);
			//�ͷŻ���
			
			//����
		}
		else
		{
			m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"CB_Disconnected ���ز��Ǳ�API��");
		}
		return true;
	}

	// ������: TradeLogin
	// ���  : ������ 2016-4-14 14:21:55
	// ����  : virtual void 
	// ����  : ����Ա��¼���ǵ�Ҫ���ϵ���Ϣ    Ҫ�Ե�¼��������
	virtual void TradeLogin()=0;

	// ������: TradeLogout
	// ���  : ������ 2016-4-14 14:21:55
	// ����  : virtual void 
	// ����  : ����Ա¼��
	virtual void TradeLogout()=0;

	// ������: Uncrypt
	// ���  : ������ 2016-3-11 16:29:31
	// ����  : virtual bool 
	// ����  : S_SGE_GEMS2_API_STRUCT *ctx  api����
	// ����  : const char *cryptmsg         �����ܵ�����
	// ����  : int msglen                   �����ܵ����ݳ���
	// ����  : char *gtpmsg                 ���ܺ������
	// ����  : int &gtpmsglen               ���ܺ�����ݳ���
	// ����  : ����
	virtual bool Uncrypt(S_SGE_GEMS2_API_STRUCT *ctx,const char *cryptmsg,int msglen,char *gtpmsg,int &gtpmsglen)=0;

	
	// ������: IsConnect
	// ���  : ������ 2016-3-11 16:30:37
	// ����  : virtual int  -1δ����  0����δ��¼ 1�������ѵ�¼
	// ����  : �Ƿ����Ӳ���¼��
	virtual int IsConnect()
	{
		if (m_nApiStatus == IS_CONNECTED)
		{
			if (m_nApiLoginStatus == 1)
			{
				return 1;
			}
			return 0;
		}
		else
		{
			return -1;
		}
	}

	// ������: LoginRsp
	// ���  : ������ 2016-3-25 14:16:58
	// ����  : virtual void 
	// ����  : int loginstatus  0δ��¼  1�ѵ�¼
	// ����  : CGtpData *loggindata  ��¼��Ӧ��¼������
	// ����  : ��¼��Ӧ�������Ƿ��¼�ɹ�
	virtual void LoginRsp(int loginstatus,const char *gtp)
	{
		m_nApiLoginStatus = loginstatus;
		if (m_nApiLoginStatus == 1)
		{
			//��¼�ɹ�����Ϊ1
			m_nLoginNum = 1;
		}
		else
		{
			//��Login������
			//m_nLoginNum++;
		}
		m_sLogGtp =gtp;
// 		if (!loggindata->ToString(m_sLogGtp))
// 		{
// 			m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"�����¼��¼�����ĳ���");
// 		}
	}
	std::string GetLoginRsp(int &loginstatus)
	{
		loginstatus = m_nApiLoginStatus;
		if (loginstatus != 1 && m_sLogGtp.length() <1) //δ��¼��¼������Ϊ�գ�ģ��һ�����ĳ���
		{
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
			gtpdata.SetDataItem("X40","¼���ɹ�");//��Ӧ��Ϣ
			gtpdata.ToString(m_sLogGtp);
		}
		return m_sLogGtp;
	}
	// ������: StartApi
	// ���  : ������ 2016-3-11 16:31:55
	// ����  : virtual bool 
	// ����  : ��ʼAPI    �������ӣ�������־   Ҫ��m_nConnectTimeΪ��ǰʱ��
	virtual bool StartApi()=0;
	

	// ������: StopApi
	// ���  : ������ 2016-3-11 16:32:06
	// ����  : virtual bool 
	// ����  : �Ͽ����ӣ�ֹͣapi��ֹͣ��־
	virtual bool StopApi()=0;

	// ������: Disconnect
	// ���  : ������ 2017-2-6 16:32:06
	// ����  : virtual void 
	// ����  : �Ͽ�����
	virtual void Disconnect()
	{
		m_nDisconnectTime =time(NULL); 
		m_nApiStatus = 0;
	}


	// ������: NextFunc
	// ���  : ������ 2016-3-11 16:32:27
	// ����  : virtual bool 
	// ����  : S_SGE_TBL_FUNC &funcinfo
	// ����  : ��һ��������Ϣ
	virtual bool NextFunc(S_SGE_TBL_FUNC &funcinfo)
	{
		return m_pTblFunc.Next(funcinfo);
	}
	

	// ������: FirstFunc
	// ���  : ������ 2016-3-11 16:32:41
	// ����  : virtual bool 
	// ����  : S_SGE_TBL_FUNC &funcinfo
	// ����  : ��һ��������Ϣ
	virtual bool FirstFunc(S_SGE_TBL_FUNC &funcinfo)
	{
		return m_pTblFunc.First(funcinfo);
	}

	// ������: AddFuncInfo
	// ���  : ������ 2016-3-11 16:34:00
	// ����  : void 
	// ����  : int funcNo
	// ����  : SgeFuncPointer pfunc
	// ����  : const char *funcName
	// ����  : ���ӽ�����Ϣ  
	void AddFuncInfo(int funcNo, SgeFuncPointer pfunc, const char *funcName)
	{
		S_SGE_TBL_FUNC pFunc;
		bzero(&pFunc,sizeof(S_SGE_TBL_FUNC));
		pFunc.nFuncNo = funcNo;
		pFunc.pFunc = pfunc;
		CBF_Tools::StringCopy(pFunc.sFuncName,80,funcName);
		pFunc.pBuInstance = NULL;
		strcpy(pFunc.sDllName,"");
		m_pTblFunc.Insert(pFunc);
	}
	// ������: AddFuncInfo
	// ���  : ������ 2016-3-11 16:34:00
	// ����  : void 
	// ����  : const char * funcNo
	// ����  : SgeFuncPointer pfunc
	// ����  : const char *funcName
	// ����  : ���ӽ�����Ϣ  
	void AddFuncInfo(const char *funcno, SgeFuncPointer pfunc, const char *funcName)
	{
		S_SGE_TBL_FUNC pFunc;
		bzero(&pFunc,sizeof(S_SGE_TBL_FUNC));
		if (strlen(funcno) != 4)
		{
			return;
		}
		pFunc.nFuncNo = 7*10000000+funcno[0]*100000+funcno[1]*1000+funcno[2]*10+atoi(funcno+3);
		
		pFunc.pFunc = pfunc;
		CBF_Tools::StringCopy(pFunc.sFuncName,80,funcName);
		pFunc.pBuInstance = NULL;
		strcpy(pFunc.sDllName,"");
		m_pTblFunc.Insert(pFunc);
	}

	bool GetGtpValue(const char *gtpbuffer,const char *key,char *cvalue)
	{
		int ngtplen = strlen(gtpbuffer);
		int kelen = strlen(key);
		bool isfind=false;
		bool isfindkey=false;
		int  valuebegin=0;
		
		int keybegin=0;
		int keyend=0;
		int keyoffset=0;
		for (int i=0 ; i< ngtplen; i++)
		{
			if (!isfind) //���ҵ�һ���ַ�
			{
				if (gtpbuffer[i] == key[keyoffset])
				{
					isfind = true;
					keyoffset++;
					keybegin = i;
					if (keyoffset == kelen) //�ҵ�key�ˣ�����ֻ��һ���ַ���KEY
					{
						if (gtpbuffer[i+1] != '=') //����Ĳ���=������key
						{
							isfind = false;
							keyoffset =0;
						}
						else
						{
							isfindkey = true;
							valuebegin = i+2; //ֵ�����￪ʼ
							break;
						}
						
					}
				}
				else
				{
					isfind = false;
					keyoffset =0;
				}
			}
			else  //���Һ���
			{
				if (gtpbuffer[i] == key[keyoffset])
				{
					isfind = true;
					keyoffset++;
					if (keyoffset == kelen) //�ҵ�key��
					{
						if (gtpbuffer[i+1] != '=') //����Ĳ���=������key
						{
							isfind = false;
							keyoffset =0;
						}
						else
						{
							isfindkey = true;
							valuebegin = i+2; //ֵ�����￪ʼ
							break;
						}
						
					}
				}
				else
				{
					isfind = false;
					keyoffset =0;
				}
			}
		}
		if (!isfind || !isfindkey) //û���ҵ�
		{
			return false;
		}
		int valueend=valuebegin;
		bool isend=false;
		for (int j=valuebegin; j<ngtplen ; j++)
		{
			if (gtpbuffer[j] == ',')
			{
				valueend = j;
				isend = true;
				break;
			}
		}
		if (!isend)  //û�ҵ�','��˵�������һ��
		{
			valueend = ngtplen;
		}
		memcpy(cvalue,gtpbuffer+valuebegin,valueend -valuebegin);
		cvalue[valueend -valuebegin]=0;
		return true;
	}

public:
	char          m_sIp[33];//��ǰ���ӵ�ǰ��IP
	int           m_nPort;  //��ǰ���ӵ�ǰ�ö˿�
	std::string   m_sNodeType;//�ڵ����ͣ���ǰ���̻������� :4-�˻������̻� 5-�ִ��ʽ��̻� 6-���ױ��̻� 7-�����ʽ�ǰ�û� 12-ETF���̻�

	std::string   m_sTradeDate;//ETF���̻���������

	S_FLOW_INFO   *m_FlowInfo[MAXFLOWNO];//�������Ϣ�����ŵĽṹ����

	std::string   m_sOfferingName;//���̻�����

	unsigned  int   m_nLoginNum;//��¼����      ��Login
	unsigned  int   m_nConnectTime;//����ʱ��   ��startapi������
	unsigned  int   m_nDisconnectTime;


	std::string     m_sSeatNo;//ϯλ����
	std::string     m_sTradeId;//����Ա

	UINT64_       m_nLogoutTime;//����Ա¼��ʱ��  yyyymmddhhmm

	unsigned int  m_nRcvBackTime;   //�����ջر�ʱ��   �յ��ر�ʱʱ��ֵ
	unsigned int  m_nRcvAnsTime;   //������Ӧ��ʱ��   �յ�Ӧ��ʱʱ��ֵ
	unsigned int  m_nSendReqTime;  //���������ʱ��   SendMsgʱ��ֵ

protected:
	
	

	S_SGE_GEMS2_API *m_apiPoint;
	CIErrlog      *m_pLog;

	bool          m_bInit;//�Ƿ�INIT
	bool          m_bIsRunning;//�߳����б�־

	unsigned int  m_magicNum;//GTP������ħ��
	std::string   m_sPath_key;//UserKey.key�ļ�·�� ��˽Կ
	std::string   m_sPath_user;//UserCert.der�ļ�·��
	std::string   m_sPath_root;//RootCert.der�ļ�·��
	std::string   m_sPath_svr;//server.der�ļ�·��
	std::string   m_sCertPwd;//֤������

	
	std::string   m_sTradePwd;//����Ա����
	std::string   m_sCertNo;//֤������
	int           m_nPwdFlag;//������ܱ�־ 0���� 1����
	std::string   m_sSeatPwd;//ϯλ����

	std::string   m_sSendFlag;//���ͷ���ʶ
	std::string   m_sRcvFlag;//���շ���ʶ

	

	std::string   m_sAccessUnitId;//���뵥Ԫ
	std::string   m_sAccessPwd;//���뵥Ԫ����

	std::vector<S_FRONT_IPPORT> m_pListIp;//ǰ��IP�˿��б�
	
	


	CSgeFuncTbl   m_pTblFunc;//���ܱ�

	volatile int  m_nApiStatus;//״̬  ������  0δ���� 1������

	volatile int  m_nApiLoginStatus;//��¼״̬  ������  1��¼�ɹ�0δ��¼

	std::string   m_sLogGtp;//�����¼��¼����gtp����

	


};

#endif // !defined(AFX_IOFFERINGBASE_H__40779290_A4D2_4574_BBCC_7885BED1E661__INCLUDED_)
