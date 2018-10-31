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
			printf("SIGHUP信号%d\n",signo);
			break;
		case SIGINT:  //2 当键盘按下CTRL+C从shell中发出信号，信号被传递给shell中前台运行的进程，对应该信号的默认操作是中断 (INTERRUPT) 该进程。
			printf("SIGINT信号%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGQUIT: //3  当键盘按下CTRL+\从shell中发出信号，信号被传递给shell中前台运行的进程，对应该信号的默认操作是退出 (QUIT) 该进程。
			printf("SIGQUIT信号%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGILL: //4  Illegal Instruction
			printf("SIGILL信号%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGABRT: //6  Abort signal from abort(3)
			printf("SIGABRT信号%d\n",signo);
			break;
		case SIGFPE://8 Floating point exception
			printf("SIGFPE信号%d\n",signo);
			break;
		case SIGKILL: //9  kill进程   Kill signal
			printf("SIGKILL信号%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGSEGV: // 11 Invalid memory reference
			printf("SIGSEGV信号%d\n",signo);
			break;
		case SIGPIPE:// 13 Broken pipe: write to pipe with no readers
			printf("SIGPIPE信号%d\n",signo);
			break;
		case SIGALRM:// 14 起到定时器的作用，通常是程序在一定的时间之后才生成该信号。
			printf("SIGALRM信号%d\n",signo);
			break;
		case SIGTERM:// 15 Termination signal
			printf("SIGTERM信号%d\n",signo);
			g_pRunFlag = 0;
			break;
		case SIGUSR1: // 30,10,16 User-defined signal 1
			printf("SIGUSR1信号%d\n",signo);
			break;
		case SIGUSR2:// 31,12,17 User-defined signal 2
			printf("SIGUSR2信号%d\n",signo);
			break;
		case SIGCHLD: // 20,17,18  Child stopped or terminated
			printf("SIGCHLD信号%d\n",signo);
			break;
		case SIGSTOP:// 17,19,23  Stop process
			printf("SIGSTOP信号%d\n",signo);
			break;
		case SIGBUS:// 10,7,10  Bus error (bad memory access)
			printf("SIGBUS信号%d\n",signo);
			break;
// 		case SIGCLD:  // -,-,18   A synonym for SIGCHLD
// 			printf("SIGCLD信号%d",signo);
// 			break;
		default:
			printf("信号%d",signo);
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
	//登录应答
	int nRet = gtp->GetValueByName("X39",srspcode,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X39响应代码字段或类型不符");
		return;
	}
	nRet = gtp->GetValueByName("X40",srspmsg,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X40响应信息字段或类型不符");
		return;
	}
	if (data.sDBHead.d_Dinfo.d_nServiceNo == 76549481 || data.sDBHead.d_Dinfo.d_nServiceNo == 76551481)  //A101 登录应答  A301 ETF登录应答
	{
		//登录不管成不成功，只要有交易日期，流文件类要处理
		std::string stradedate;
		nRet = gtp->GetValueByName("T13",stradedate,fieldtype);
		if (nRet <0)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无T13交易日期字段或类型不符");
		}
		else
		{
			g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"交易员登录返回 交易日期[%s]",stradedate.c_str());


			if (g_sgedll->m_sNodeType.compare("12") == 0)
			{

			}
			else  //不是ETF报盘机
			{
				//使用返回的日期
				g_sgedll->m_sTradeDate = stradedate;
			}
			
		}
		
		//RSP000000为成功
		if (srspcode.compare("RSP000000") != 0)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员登录返回不成功[%s -%s]",srspcode.c_str(),srspmsg.c_str());
			try
			{
				g_sgedll->LoginRsp(0,gtp);
			}
			catch (...)
			{
				g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员登录返回不成功 调用LoginRsp异常");
				return;
			}
			return;
		}
		//找到对应实例，调用logrsp   sBpcHead.cMsgType保存的是对应的实例容器下标
		try
		{
			g_sgedll->LoginRsp(1,gtp);
		}
		catch (...)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员登录返回成功 调用LoginRsp异常");
			return;
		}
		
		return;
	}
	else if (data.sDBHead.d_Dinfo.d_nServiceNo == 76549491 || data.sDBHead.d_Dinfo.d_nServiceNo == 76551491)  //A111 录出应答  A311 etf录出应答
	{
		if (srspcode.compare("RSP000000") != 0)
		{
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员录出返回不成功[%s -%s]",srspcode.c_str(),srspmsg.c_str());
			try
			{
				g_sgedll->LoginRsp(0,gtp);
			}
			catch (...)
			{
				g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员录出返回不成功 调用LoginRsp异常");
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
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员录出返回成功 调用LoginRsp异常");
			return;
		}
		return;
	}
	return;
}
void ProcRequest(CGtpData *gtp, BPCCOMMSTRU &data)
{
	g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"GTP请求报文",(char *)data.sBuffer,data.sDBHead.nLen);
	return ;
}
void ProcAns(CGtpData *gtp, BPCCOMMSTRU &data)
{
	//交易所过来的应答
	//首先取得rootid
	std::string srootid;
	int fieldtype=0;
	int nRet = gtp->GetValueByName("X07",srootid,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X07 ROOTID字段或类型不符");
		return ;
	}
	int gtpdatalen = data.sDBHead.nLen;
	unsigned int txcode = data.sDBHead.d_Dinfo.d_nServiceNo;
	int  dllofset = data.sBpcHead.cMsgType;//动态库的实例下标

	//若是交易员登录或录出，则发给所有连接的交易服务器
	g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"GTP应答报文",(char *)data.sBuffer,data.sDBHead.nLen);

	
	return;
}

void ProcBack(CGtpData *gtp, BPCCOMMSTRU &data)
{
	//交易所过来的回报
	//首先记流
	int msgtype=0;
	unsigned int msgserial=0;
	std::string sdatastr;
	int fieldtype=0;
	int nRet = gtp->GetValueByName("X04",sdatastr,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X04 序列类别号字段或类型不符");
		return ;
	}
	msgtype = atoi(sdatastr.c_str());
	nRet = gtp->GetValueByName("X05",sdatastr,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X04 消息序列号字段或类型不符");
		return ;
	}
	msgserial = atol(sdatastr.c_str());
	
	g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"GTP回报报文",(char *)data.sBuffer,data.sDBHead.nLen);


	return ;

}

void ProcLoginBack(CGtpData *gtp, BPCCOMMSTRU &data)
{
	
	
	g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送GTP登录应答报文",(char *)data.sBuffer,data.sDBHead.nLen);
	
	return ;
}

void ProcData(BPCCOMMSTRU &data)
{
	g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"收到的GTP数据包[%s] 长度[%d]",data.sBuffer,data.sDBHead.nLen);
	if (!g_pGtpData.FromBuffer(data.sBuffer))
	{
		g_pLog.LogBin(LOG_ERROR,__FILE__,__LINE__,"数据包非GTP",data.sBuffer,data.sDBHead.nLen);
		return;
	}
	//得到交易码
	std::string stxcode;
	int fieldtype=0;
	int nRet = g_pGtpData.GetValueByName("X03",stxcode,fieldtype);
	if (nRet <0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X03字段或类型不符");
		return;
	}
	//转换交易码
	if (stxcode.length() != 4)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"消息类型[%s]不符",stxcode.c_str());
		return;
	}
	char tmpchar[100];
	bzero(tmpchar,sizeof(tmpchar));
	tmpchar[0]=stxcode.c_str()[3];
	data.sDBHead.d_Dinfo.d_nServiceNo = 7*10000000+stxcode.c_str()[0]*100000+stxcode.c_str()[1]*1000+stxcode.c_str()[2]*10+atoi(tmpchar);
	g_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"消息类型[%s]转为交易码[%d]",stxcode.c_str(),data.sDBHead.d_Dinfo.d_nServiceNo);
	//登录和退出指令
	
	if (stxcode.compare("A101") == 0 || stxcode.compare("A111") == 0 || \
		stxcode.compare("A301") == 0 || stxcode.compare("A311") == 0 )  //etf登录
	{
		ProcLogin(&g_pGtpData,data);
		//将应答发给交易服务器
		ProcLoginBack(&g_pGtpData,data);
		return;
	}
	switch (atoi(tmpchar))
	{
		case 0: //请求
			ProcRequest(&g_pGtpData,data);
			break;
		case 1: //应答
			ProcAns(&g_pGtpData,data);
			break;
		case 2: //回报
			ProcBack(&g_pGtpData,data);
			break;
		default:
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"报文标识[%s]不符 0请求，1应答 2回报",tmpchar);
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
		//明文
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

		g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"收到的SGE数据",(char *)msg,con_len);
		if (!g_sgedll->Uncrypt(pctx,msg,con_len,data.sBuffer,len))
		{
			g_pLog.LogBin(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据",(char *)msg,con_len);
			g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"实例解密出错");
			return;
		}
		data.sDBHead.nLen = len;
		g_pLog.LogBin(LOG_DEBUG,__FILE__,__LINE__,"解密后的SGE数据",data.sBuffer,data.sDBHead.nLen);
	}
	else
	{
		//printf("this message is no handled,msg: %s", msg);
		g_pLog.LogBin(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据类型不符",(char *)msg,con_len);
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
	printf("连接[%s %d]成功\n",cs->ip,cs->port);
	g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"连接[%s %d]成功",cs->ip,cs->port);


	if (!g_sgedll->CB_Connected(cs,(S_SGE_GEMS2_API_STRUCT *)ctx))
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"实例CB_Connected出错");
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
	printf("连接[%s %d]断开\n",cs->ip,cs->port);
	g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"连接[%s %d]断开",cs->ip,cs->port);
	
	if (!g_sgedll->CB_Disconnected(cs,(S_SGE_GEMS2_API_STRUCT *)ctx))
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"实例CB_Disconnected出错");
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
			sprintf(errmsg,"打开动态库[%s]失败",dllpathname);
			return false;
		}
		sprintf(dllpathname,"%s",dllname);
		CBF_Tools::LRtrim(dllpathname);
		*pDll = LOADDLL(dllpathname);
		if (ISNOTOPEN(*pDll))
		{
			sprintf(errmsg,"打开动态库[%s]失败",dllpathname);
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
			sprintf(errmsg,"打开动态库[%s]失败",dllpathname);
			return false;
		}
		sprintf(dllpathname,"%s",dllname);
		CBF_Tools::LRtrim(dllpathname);
		*pDll = LOADDLL(dllpathname);
		pdllerror = dlerror();
		if (pdllerror!=NULL)
		{
			sprintf(errmsg,"打开动态库[%s]失败[%s]",dllpathname,pdllerror);
			
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
		printf("配置文件[%s]不存在或非法\n","tradefront.xml");
		return -1;
	}
	std::string m_sSeatNo;
	if (xml.GetNodeValueByPath("/package/head/公共配置/席位代码",false,m_sSeatNo,false) == NULL)
	{
		printf("[/package/head/公共配置/席位代码]未配置\n");
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
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"打开动态库[%s]失败",dllname.c_str());
		printf("打开动态库[%s]失败\n",dllname.c_str());
		return false;
	}
	NEWOFFERINGNSTANCE baseinstance = (NEWOFFERINGNSTANCE)GETINSTANCE(apihandle,"getInstance");
	if (NULL == baseinstance)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]实例化失败",dllname.c_str());
		printf("动态库[%s]实例化失败\n",dllname.c_str());
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
	
	g_api.offernodepath = "/package/head/报盘机配置/交易报盘机";
	g_api.apistructpvalue = (UINT64_)(g_api.apistruct);

	
	bRet = g_sgedll->Init(&g_api,&g_pLog,&xml,g_api.offernodepath.c_str(),errmsg);
	if (!bRet)
	{
		printf("初始化失败 [%s]\n",errmsg);
		return -1;
	}
	//要置席位代码
	g_sgedll->m_sSeatNo = m_sSeatNo;

	S_FLOW_INFO m_FlowInfo[MAXFLOWNO];//保存各消息最大序号的结构数据
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
	//启动api
	g_sgedll->StartApi();
	int ret;
	while (g_pRunFlag == 1)
	{
		ret = g_sgedll->IsConnect();
		switch (ret)
		{
			case 0:
				//如果登录次数超过10次，则退出，切换至备机
				if (g_sgedll->m_nLoginNum >10)
				{
					//置程序退出标志
					g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"[%s %d] 已连接但登录超过10次未成功，退出程序切换备机",\
						g_sgedll->m_sIp,\
						g_sgedll->m_nPort);
					g_pRunFlag  = 0;
					break;
				}
				g_pLog.LogMp(LOG_DEBUG,__FILE__,__LINE__,"[%s %d] 已连接但未登录返回",\
					g_sgedll->m_sIp,\
					g_sgedll->m_nPort);
				//去登录，只有当登录出错，反复尝试去登录
				g_sgedll->TradeLogin();
				break;
			case 1:
				g_pLog.LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"[%s %d] 已连接已登录",\
					g_sgedll->m_sIp,\
					g_sgedll->m_nPort);
				//查看是否需要录出
				break;
			default:
				g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"[%s %d] 未连接",\
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