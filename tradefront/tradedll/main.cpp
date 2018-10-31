#include "public.h"
#include "IOfferingBase.h"
#include "OfferingTrade.h"



#ifdef _WINDOWS
#ifdef _DEBUG
#pragma comment(lib, "bf_kerneld.lib") 
#pragma comment(lib, "bf_xdpd.lib") 
#pragma comment(lib, "bf_drebapid.lib") 
#pragma comment(lib, "bf_kvdatad.lib") 
#pragma comment(lib, "bf_gtpd.lib") 
#pragma message("Automatically linking with   bf_kerneld.lib bf_xdpd.lib bf_drebapid.lib bf_kvdatad.lib bf_gtpd.lib")
#else
#pragma comment(lib, "bf_kernel.lib") 
#pragma comment(lib, "bf_xdp.lib") 
#pragma comment(lib, "bf_drebapi.lib") 
#pragma comment(lib, "bf_kvdata.lib") 
#pragma comment(lib, "bf_gtp.lib") 
#pragma message("Automatically linking with   bf_kernel.lib bf_xdp.lib bf_drebapi.lib bf_kvdata.lib bf_gtp.lib")
#endif

#endif

S_SGE_GEMS2_API  g_api;
CIOfferingBase   *g_sgedll;
CBF_SimpleLog    g_pLog;
CGtpData         g_pGtpData;


int   g_pRunFlag =  1;

#ifndef _WINDOWS

typedef void Sigfunc(int);
Sigfunc * Signal_proc(int signo, Sigfunc *func);
Sigfunc* Signal_proc(int signo, Sigfunc* func)
{
	struct sigaction act, oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	
	if(signo == SIGALRM) 
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;   /* SunOS 4.x */
#endif
	} 
	else 
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;   /* SVR4, 4.4BSD */
#endif
	}
	
	if(sigaction(signo, &act, &oact) <0)
	{
		return(SIG_ERR);
	}
	return(oact.sa_handler);
}

void sig_int(int signo)
{
	switch(signo)
	{
		case SIGHUP:  //1  Hangup detected on controlling terminal or death of controlling process
			printf("SIGHUP�ź�%d\n",signo);
			break;
		case SIGINT:  //2 �����̰���CTRL+C��shell�з����źţ��źű����ݸ�shell��ǰ̨���еĽ��̣���Ӧ���źŵ�Ĭ�ϲ������ж� (INTERRUPT) �ý��̡�
			printf("SIGINT�ź�%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGQUIT: //3  �����̰���CTRL+\��shell�з����źţ��źű����ݸ�shell��ǰ̨���еĽ��̣���Ӧ���źŵ�Ĭ�ϲ������˳� (QUIT) �ý��̡�
			printf("SIGQUIT�ź�%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGILL: //4  Illegal Instruction
			printf("SIGILL�ź�%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGABRT: //6  Abort signal from abort(3)
			printf("SIGABRT�ź�%d\n",signo);
			break;
		case SIGFPE://8 Floating point exception
			printf("SIGFPE�ź�%d\n",signo);
			break;
		case SIGKILL: //9  kill����   Kill signal
			printf("SIGKILL�ź�%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGSEGV: // 11 Invalid memory reference
			printf("SIGSEGV�ź�%d\n",signo);
			break;
		case SIGPIPE:// 13 Broken pipe: write to pipe with no readers
			printf("SIGPIPE�ź�%d\n",signo);
			break;
		case SIGALRM:// 14 �𵽶�ʱ�������ã�ͨ���ǳ�����һ����ʱ��֮������ɸ��źš�
			printf("SIGALRM�ź�%d\n",signo);
			break;
		case SIGTERM:// 15 Termination signal
			printf("SIGTERM�ź�%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGUSR1: // 30,10,16 User-defined signal 1
			printf("SIGUSR1�ź�%d\n",signo);
			break;
		case SIGUSR2:// 31,12,17 User-defined signal 2
			printf("SIGUSR2�ź�%d\n",signo);
			break;
		case SIGCHLD: // 20,17,18  Child stopped or terminated
			printf("SIGCHLD�ź�%d\n",signo);
			break;
		case SIGSTOP:// 17,19,23  Stop process
			printf("SIGSTOP�ź�%d\n",signo);
			break;
		case SIGBUS:// 10,7,10  Bus error (bad memory access)
			printf("SIGBUS�ź�%d\n",signo);
			break;
// 		case SIGCLD:  // -,-,18   A synonym for SIGCHLD
// 			printf("SIGCLD�ź�%d",signo);
// 			break;
		default:
			printf("�ź�%d",signo);
			break;
	}
// 	if ((signo == 2) || (signo == 4) || (signo == 15)  ) 
// 	{
// 		g_pRunFlag = 0;
// 	}
}
void sig_usr1(int signo)
{
}

void sig_hup(int signo)
{
}
#endif

void ProcLogin(CGtpData *gtp, BPCCOMMSTRU &data)
{
	std::string srspcode;
	std::string srspmsg;
	int fieldtype=0;
	//��¼Ӧ��
	int nRet = gtp->GetValueByName("X39",srspcode,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X39��Ӧ�����ֶλ����Ͳ���");
		return;
	}
	nRet = gtp->GetValueByName("X40",srspmsg,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X40��Ӧ��Ϣ�ֶλ����Ͳ���");
		return;
	}
	if (data.sDBHead.d_Dinfo.d_nServiceNo == 76549481 || data.sDBHead.d_Dinfo.d_nServiceNo == 76551481)  //A101 ��¼Ӧ��  A301 ETF��¼Ӧ��
	{
		//��¼���ܳɲ��ɹ���ֻҪ�н������ڣ����ļ���Ҫ����
		std::string stradedate;
		nRet = gtp->GetValueByName("T13",stradedate,fieldtype);
		if (nRet <0)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���T13���������ֶλ����Ͳ���");
		}
		else
		{
			g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"����Ա��¼���� ��������[%s]",stradedate.c_str());


			if (g_sgedll->m_sNodeType.compare("12") == 0)
			{

			}
			else  //����ETF���̻�
			{
				//ʹ�÷��ص�����
				g_sgedll->m_sTradeDate = stradedate;
			}
			
		}
		
		//RSP000000Ϊ�ɹ�
		if (srspcode.compare("RSP000000") != 0)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա��¼���ز��ɹ�[%s -%s]",srspcode.c_str(),srspmsg.c_str());
			try
			{
				g_sgedll->LoginRsp(0,gtp);
			}
			catch (...)
			{
				g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա��¼���ز��ɹ� ����LoginRsp�쳣");
				return;
			}
			return;
		}
		//�ҵ���Ӧʵ��������logrsp   sBpcHead.cMsgType������Ƕ�Ӧ��ʵ�������±�
		try
		{
			g_sgedll->LoginRsp(1,gtp);
		}
		catch (...)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա��¼���سɹ� ����LoginRsp�쳣");
			return;
		}
		
		return;
	}
	else if (data.sDBHead.d_Dinfo.d_nServiceNo == 76549491 || data.sDBHead.d_Dinfo.d_nServiceNo == 76551491)  //A111 ¼��Ӧ��  A311 etf¼��Ӧ��
	{
		if (srspcode.compare("RSP000000") != 0)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա¼�����ز��ɹ�[%s -%s]",srspcode.c_str(),srspmsg.c_str());
			try
			{
				g_sgedll->LoginRsp(0,gtp);
			}
			catch (...)
			{
				g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա¼�����ز��ɹ� ����LoginRsp�쳣");
				return;
			}
			return;
		}
		try
		{
			g_sgedll->LoginRsp(0,gtp);
		}
		catch (...)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա¼�����سɹ� ����LoginRsp�쳣");
			return;
		}
		return;
	}
	return;
}
void ProcRequest(CGtpData *gtp, BPCCOMMSTRU &data)
{
	g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"GTP������",(char *)data.sBuffer,data.sDBHead.nLen);
	return ;
}
void ProcAns(CGtpData *gtp, BPCCOMMSTRU &data)
{
	//������������Ӧ��
	//����ȡ��rootid
	std::string srootid;
	int fieldtype=0;
	int nRet = gtp->GetValueByName("X07",srootid,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X07 ROOTID�ֶλ����Ͳ���");
		return ;
	}
	int gtpdatalen = data.sDBHead.nLen;
	unsigned int txcode = data.sDBHead.d_Dinfo.d_nServiceNo;
	int  dllofset = data.sBpcHead.cMsgType;//��̬���ʵ���±�

	//���ǽ���Ա��¼��¼�����򷢸��������ӵĽ��׷�����
	g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"GTPӦ����",(char *)data.sBuffer,data.sDBHead.nLen);

	
	return;
}

void ProcBack(CGtpData *gtp, BPCCOMMSTRU &data)
{
	//�����������Ļر�
	//���ȼ���
	int msgtype=0;
	unsigned int msgserial=0;
	std::string sdatastr;
	int fieldtype=0;
	int nRet = gtp->GetValueByName("X04",sdatastr,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X04 ���������ֶλ����Ͳ���");
		return ;
	}
	msgtype = atoi(sdatastr.c_str());
	nRet = gtp->GetValueByName("X05",sdatastr,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X04 ��Ϣ���к��ֶλ����Ͳ���");
		return ;
	}
	msgserial = atol(sdatastr.c_str());
	
	g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"GTP�ر�����",(char *)data.sBuffer,data.sDBHead.nLen);


	return ;

}

void ProcLoginBack(CGtpData *gtp, BPCCOMMSTRU &data)
{
	
	
	g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"����GTP��¼Ӧ����",(char *)data.sBuffer,data.sDBHead.nLen);
	
	return ;
}

void ProcData(BPCCOMMSTRU &data)
{
	g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"�յ���GTP���ݰ�[%s] ����[%d]",data.sBuffer,data.sDBHead.nLen);
	if (!g_pGtpData.FromBuffer(data.sBuffer))
	{
		g_pLog.LogBin(LOG_ERROR,__FILE__,__LINE__,"���ݰ���GTP",data.sBuffer,data.sDBHead.nLen);
		return;
	}
	//�õ�������
	std::string stxcode;
	int fieldtype=0;
	int nRet = g_pGtpData.GetValueByName("X03",stxcode,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X03�ֶλ����Ͳ���");
		return;
	}
	//ת��������
	if (stxcode.length() != 4)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"��Ϣ����[%s]����",stxcode.c_str());
		return;
	}
	char tmpchar[100];
	bzero(tmpchar,sizeof(tmpchar));
	tmpchar[0]=stxcode.c_str()[3];
	data.sDBHead.d_Dinfo.d_nServiceNo = 7*10000000+stxcode.c_str()[0]*100000+stxcode.c_str()[1]*1000+stxcode.c_str()[2]*10+atoi(tmpchar);
	g_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"��Ϣ����[%s]תΪ������[%d]",stxcode.c_str(),data.sDBHead.d_Dinfo.d_nServiceNo);
	//��¼���˳�ָ��
	
	if (stxcode.compare("A101") == 0 || stxcode.compare("A111") == 0 || \
		stxcode.compare("A301") == 0 || stxcode.compare("A311") == 0 )  //etf��¼
	{
		ProcLogin(&g_pGtpData,data);
		//��Ӧ�𷢸����׷�����
		ProcLoginBack(&g_pGtpData,data);
		return;
	}
	switch (atoi(tmpchar))
	{
		case 0: //����
			ProcRequest(&g_pGtpData,data);
			break;
		case 1: //Ӧ��
			ProcAns(&g_pGtpData,data);
			break;
		case 2: //�ر�
			ProcBack(&g_pGtpData,data);
			break;
		default:
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"���ı�ʶ[%s]���� 0����1Ӧ�� 2�ر�",tmpchar);
			break;
	}
	return;

}



void __recv_msg(const char * msg, int type, unsigned int con_len, void * ctx) 
{
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT*)ctx;    
	++(pctx->recv_count_);
	BPCCOMMSTRU data;
	
	if(type == GTP_TYPE_STRING)
	{ 
		// is the no_enc msg
		//����
		bzero(&data,sizeof(BPCCOMMSTRU));
		if (con_len>0)
		{
			memcpy(data.sBuffer,msg,con_len);
		}
		data.sDBHead.nLen = con_len;
		

	}
	else if(type == GTP_TYPE_ENCRYPT)
	{
		bzero(&data,sizeof(BPCCOMMSTRU));
		int len = BPUDATASIZE;

		g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"�յ���SGE����",(char *)msg,con_len);
		if (!g_sgedll->Uncrypt(pctx,msg,con_len,data.sBuffer,len))
		{
			g_pLog.LogBin(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE����",(char *)msg,con_len);
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"ʵ�����ܳ���");
			return;
		}
		data.sDBHead.nLen = len;
		g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"���ܺ��SGE����",data.sBuffer,data.sDBHead.nLen);
	}
	else
	{
		//printf("this message is no handled,msg: %s", msg);
		g_pLog.LogBin(LOG_ERROR,__FILE__,__LINE__,"�յ���SGE�������Ͳ���",(char *)msg,con_len);
		return ;
	}
	ProcData(data);
}

void __cb_connected(api_connection_state_t * cs, void * ctx) 
{
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT *)ctx;    
	if(cs->state == IS_ERROR_DISCONNECTED)
	{
		++(pctx->connected_count_);
	}
	printf("����[%s %d]�ɹ�\n",cs->ip,cs->port);
	g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"����[%s %d]�ɹ�",cs->ip,cs->port);


	if (!g_sgedll->CB_Connected(cs,(S_SGE_GEMS2_API_STRUCT *)ctx))
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"ʵ��CB_Connected����");
		return;
	}

	

//	printf("connected to acsvr. ip: %s, port: %d, state: %d\n", cs->ip, cs->port, cs->state);
}

void __cb_disconnect(api_connection_state_t * cs, void * ctx) 
{
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT *)ctx;    
	if(cs->state == IS_ERROR_DISCONNECTED)
	{
		--(pctx->connected_count_);
	}
	printf("����[%s %d]�Ͽ�\n",cs->ip,cs->port);
	g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"����[%s %d]�Ͽ�",cs->ip,cs->port);
	
	if (!g_sgedll->CB_Disconnected(cs,(S_SGE_GEMS2_API_STRUCT *)ctx))
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"ʵ��CB_Disconnected����");
		return;
	}
			
}


typedef CIOfferingBase *(*NEWOFFERINGNSTANCE)();

bool OpenDll(DLLHANDLE *pDll, const char *dllname, const char *dllpath)
{
	char errmsg[300];
	bool bIsNotPath=false;
	char dllpathname[401];
	memset(dllpathname,0,sizeof(dllpathname));
	if (strlen(dllpath) <1)
	{
		bIsNotPath=true;
	}
	else
	{
		bIsNotPath=false;
	}
	if (bIsNotPath)
	{
		sprintf(dllpathname,"%s",dllname);
	}
	else
	{
#ifdef _WINDOWS
		sprintf(dllpathname,"%s\\%s",dllpath,dllname);
#else
		sprintf(dllpathname,"%s/%s",dllpath,dllname);
#endif
	}
	
	CBF_Tools::LRtrim(dllpathname);
	
	*pDll = LOADDLL(dllpathname);
#ifdef WIN32
	if (ISNOTOPEN(*pDll))
	{
		if (bIsNotPath)
		{
			sprintf(errmsg,"�򿪶�̬��[%s]ʧ��",dllpathname);
			return false;
		}
		sprintf(dllpathname,"%s",dllname);
		CBF_Tools::LRtrim(dllpathname);
		*pDll = LOADDLL(dllpathname);
		if (ISNOTOPEN(*pDll))
		{
			sprintf(errmsg,"�򿪶�̬��[%s]ʧ��",dllpathname);
			return false;
		}
	}
#else
	char *pdllerror;
	pdllerror = dlerror();
	if (pdllerror!=NULL)
	{	
		if (bIsNotPath)
		{
			sprintf(errmsg,"�򿪶�̬��[%s]ʧ��",dllpathname);
			return false;
		}
		sprintf(dllpathname,"%s",dllname);
		CBF_Tools::LRtrim(dllpathname);
		*pDll = LOADDLL(dllpathname);
		pdllerror = dlerror();
		if (pdllerror!=NULL)
		{
			sprintf(errmsg,"�򿪶�̬��[%s]ʧ��[%s]",dllpathname,pdllerror);
			
			return false;
		}
		
	}
#endif	
	return true;
}


int main(int argc,char *argv[])
{



	CBF_Xml         xml;
	bool bRet;
	g_pLog.SetLogPara(LOG_DEBUG,"","testsgeapi.log");

	bRet = xml.FromFile("tradefront.xml");
	if (!bRet)
	{
		printf("�����ļ�[%s]�����ڻ�Ƿ�\n","tradefront.xml");
		return -1;
	}
	std::string m_sSeatNo;
	if (xml.GetNodeValueByPath("/package/head/��������/ϯλ����",false,m_sSeatNo,false) == NULL)
	{
		printf("[/package/head/��������/ϯλ����]δ����\n");
		return -1;
	}
	char errmsg[512];
	DLLHANDLE apihandle;

	std::string dllname;
#ifdef _WINDOWS
	dllname = "tradedlld.dll";
#else
	dllname = "libsgetrade.so";

#endif
	if (!OpenDll(&apihandle,dllname.c_str(),""))
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"�򿪶�̬��[%s]ʧ��",dllname.c_str());
		printf("�򿪶�̬��[%s]ʧ��\n",dllname.c_str());
		return false;
	}
	NEWOFFERINGNSTANCE baseinstance = (NEWOFFERINGNSTANCE)GETINSTANCE(apihandle,"getInstance");
	if (NULL == baseinstance)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"��̬��[%s]ʵ����ʧ��",dllname.c_str());
		printf("��̬��[%s]ʵ����ʧ��\n",dllname.c_str());
		return false;
	}
    g_sgedll =(CIOfferingBase *)baseinstance(); 

//	g_sgedll = new COfferingTrade();
	g_api.apidllhandle =NULL;
	g_api.apidllname=  "tradesge";
	g_api.apiPoint =   g_sgedll;
	g_api.apistruct = new S_SGE_GEMS2_API_STRUCT();
	if (g_api.apistruct == NULL)
	{
		return -1;
	}
	memset(g_api.apistruct, 0, sizeof(S_SGE_GEMS2_API_STRUCT));
	g_api.apistruct->cb_.api_recv_msg_ = __recv_msg; 
	g_api.apistruct->cb_.api_cb_connected_ = __cb_connected;
	g_api.apistruct->cb_.api_cb_disconnected_ = __cb_disconnect;
	
	g_api.offernodepath = "/package/head/���̻�����/���ױ��̻�";
	g_api.apistructpvalue = (UINT64_)(g_api.apistruct);

	
	bRet = g_sgedll->Init(&g_api,&g_pLog,&xml,g_api.offernodepath.c_str(),errmsg);
	if (!bRet)
	{
		printf("��ʼ��ʧ�� [%s]\n",errmsg);
		return -1;
	}
	//Ҫ��ϯλ����
	g_sgedll->m_sSeatNo = m_sSeatNo;

	S_FLOW_INFO m_FlowInfo[MAXFLOWNO];//�������Ϣ�����ŵĽṹ����
	bzero(&m_FlowInfo,sizeof(m_FlowInfo));
	
	for (int i=0; i<MAXFLOWNO ; i++)
	{
		m_FlowInfo[i].nFlowNo = i+1;
		m_FlowInfo[i].nMaxSerial = 0;
	}
	for (int k=0; k< MAXFLOWNO; k++)
	{
		g_sgedll->m_FlowInfo[k] =  &(m_FlowInfo[k]);
	}
	//����api
	g_sgedll->StartApi();
	int ret;
	while (g_pRunFlag == 1)
	{
		ret = g_sgedll->IsConnect();
		switch (ret)
		{
			case 0:
				//�����¼��������10�Σ����˳����л�������
				if (g_sgedll->m_nLoginNum >10)
				{
					//�ó����˳���־
					g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"[%s %d] �����ӵ���¼����10��δ�ɹ����˳������л�����",\
						g_sgedll->m_sIp,\
						g_sgedll->m_nPort);
					g_pRunFlag  = 0;
					break;
				}
				g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"[%s %d] �����ӵ�δ��¼����",\
					g_sgedll->m_sIp,\
					g_sgedll->m_nPort);
				//ȥ��¼��ֻ�е���¼������������ȥ��¼
				g_sgedll->TradeLogin();
				break;
			case 1:
				g_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"[%s %d] �������ѵ�¼",\
					g_sgedll->m_sIp,\
					g_sgedll->m_nPort);
				//�鿴�Ƿ���Ҫ¼��
				break;
			default:
				g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"[%s %d] δ����",\
					g_sgedll->m_sIp,\
					g_sgedll->m_nPort);
				break;
		}
		
		SLEEP_SECONDS(4);
	}
	g_sgedll->TradeLogout();
	g_sgedll->StopApi();

	SLEEP_SECONDS(4);
	
	return 0;
}