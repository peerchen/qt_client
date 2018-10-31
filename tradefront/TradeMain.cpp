// ArbMain.cpp: implementation of the CArbMain class.
//
//////////////////////////////////////////////////////////////////////

#include "TradeMain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CTradeMain g_pOfferingMain;
extern int   g_pRunFlag;

typedef CTradeMain *(*NEWOFFERINGNSTANCE)();


void __recv_msg(const char * msg, int type, unsigned int con_len, void * ctx) 
{
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT*)ctx;    
	++(pctx->recv_count_);
	S_SGE_DATA data;
	data.type = type;
	data.pctx = pctx;
	bzero(&data.data,sizeof(BPCCOMMSTRU));
	g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"收到的SGE数据",(char *)msg,con_len);
	if (con_len>0 && con_len<BPUDATASIZE)
	{
		memcpy(data.data.sBuffer,msg,con_len);
		data.data.sDBHead.nLen = con_len;
		data.data.sBuffer[data.data.sDBHead.nLen]=0;
		g_pOfferingMain.PushRcvData(data);
	}
	else
	{
		g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据大小[%d]不符",con_len);
		return;
	}

	//songfree 20161024 因解密需要验服务端信息才能解密，所以解密放到处理线程里面做
	
// 	if(type == GTP_TYPE_STRING)
// 	{ 
// 		// is the no_enc msg
// 		//明文
// 		bzero(&data,sizeof(BPCCOMMSTRU));
// 		if (con_len>0 && con_len<BPUDATASIZE)
// 		{
// 			memcpy(data.sBuffer,msg,con_len);
// 		}
// 		else
// 		{
// 			g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据大小[%d]不符",con_len);
// 			return;
// 		}
// 		
// 		data.sDBHead.nLen = con_len;
// 		for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
// 		{
// 			if (g_pOfferingMain.m_vApiDllClass[i].apistruct == pctx)
// 			{
// 				//保存动态库的索引，接收处理线程可根据此字段判定是哪个动态库接收到的
// 				data.sBpcHead.cMsgType = i;
// 				data.sBpcHead.nBpcLen = atoi(g_pOfferingMain.m_vApiDllClass[i].apiPoint->m_sNodeType.c_str());
// 				break;
// 			}
// 		}
// 		g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"收到的SGE数据",(char *)msg,con_len);
// 		
// 		g_pOfferingMain.PushRcvData(data);
// 
// 	}
// 	else if(type == GTP_TYPE_ENCRYPT)
// 	{
// 		bzero(&data,sizeof(BPCCOMMSTRU));
// 		int len = BPUDATASIZE;
// 		if (con_len>0 && con_len<BPUDATASIZE)
// 		{
// 			
// 		}
// 		else
// 		{
// 			g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据大小[%d]不符",con_len);
// 			return;
// 		}
// 		//解密
// 		//根据pctx找到对应api实例类，然后调用api实例类方法解密
// 		for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
// 		{
// 			if (g_pOfferingMain.m_vApiDllClass[i].apistruct == pctx)
// 			{
// 				g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"收到的SGE数据",(char *)msg,con_len);
// 				if (!g_pOfferingMain.m_vApiDllClass[i].apiPoint->Uncrypt(pctx,msg,con_len,data.sBuffer,len))
// 				{
// 					g_pOfferingMain.m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据",(char *)msg,con_len);
// 					g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]实例解密出错",g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str());
// 					return;
// 				}
// 				data.sDBHead.nLen = len;
// 				g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"解密后的SGE数据",data.sBuffer,data.sDBHead.nLen);
// 				//保存动态库的索引，接收处理线程可根据此字段判定是哪个动态库接收到的
// 				data.sBpcHead.cMsgType = i;
// 				g_pOfferingMain.PushRcvData(data);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		//printf("this message is no handled,msg: %s", msg);
// 		g_pOfferingMain.m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据类型不符",(char *)msg,con_len);
// 	}
}

void __cb_connected(api_connection_state_t * cs, void * ctx) 
{
//	printf("begin connected\n");
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT *)ctx;    
	if(cs->state == IS_CONNECTED)
	{
		++(pctx->connected_count_);
	}
	printf("连接[%s %d]成功\n",cs->ip,cs->port);
	g_pOfferingMain.m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"连接[%s %d]成功",cs->ip,cs->port);
	for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
	{
		if (g_pOfferingMain.m_vApiDllClass[i].apistruct == pctx)
		{
			g_pOfferingMain.m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"动态库[%s]连接[%s %d]成功",\
				g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str(),cs->ip,cs->port);
			if (!g_pOfferingMain.m_vApiDllClass[i].apiPoint->CB_Connected(cs,(S_SGE_GEMS2_API_STRUCT *)ctx))
			{
				g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]实例CB_Connected出错",g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str());
				return;
			}
			return;
		}
	}
	g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"找不到对应的指针");

//	printf("connected to acsvr. ip: %s, port: %d, state: %d\n", cs->ip, cs->port, cs->state);
}

void __cb_disconnect(api_connection_state_t * cs, void * ctx) 
{
//	printf("begin disconnect\n");
	S_SGE_GEMS2_API_STRUCT * pctx = (S_SGE_GEMS2_API_STRUCT *)ctx;    
	if(cs->state == IS_ERROR_DISCONNECTED || cs->state == IS_ACTIVE_DISCONNECTED )
	{
		--(pctx->connected_count_);
	}
//	printf("连接[%s %d]断开",cs->ip,cs->port);
	g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"连接[%s %d]断开 状态[%d]",cs->ip,cs->port,cs->state);
	for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
	{
		if (g_pOfferingMain.m_vApiDllClass[i].apistruct == pctx)
		{
			g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]连接[%s %d]断开",\
				g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str(),cs->ip,cs->port);
			if (!g_pOfferingMain.m_vApiDllClass[i].apiPoint->CB_Disconnected(cs,(S_SGE_GEMS2_API_STRUCT *)ctx))
			{
				g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]实例CB_Disconnected出错",g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str());
				return;
			}
			return;
		}
	}
	g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"找不到对应的指针");
//	printf("disconnect with acsvr. ip: %s, port: %d, state: %d\n", cs->ip, cs->port, cs->state);
}



CTradeMain::CTradeMain()
{
	m_pLog = NULL;
	m_bIsInit = false;
}

CTradeMain::~CTradeMain()
{
	for (int i=0 ; i<m_vApiDllClass.size(); i++)
	{
		if (m_vApiDllClass[i].apiPoint != NULL)
		{
			delete m_vApiDllClass[i].apiPoint;
			m_vApiDllClass[i].apiPoint = NULL;
		}
		if (m_vApiDllClass[i].apistruct != NULL)
		{
			delete m_vApiDllClass[i].apistruct;
			m_vApiDllClass[i].apistruct = NULL;
		}
	}
//	printf("析构退出!\n");
	
}

bool CTradeMain::Init(const char *confile)
{
	m_bIsInit = false;

	//配置初始
	if (!m_pRes.Init(confile))
	{
		printf("初始化出错  %s\n",m_pRes.m_errMsg.c_str());
		return false;
	}
	//api初始化
	if (!m_pDrebApi.Init(&m_pRes))
	{
		printf("数据总线初始化出错! \n");
		return false;
	}
	m_pLog = m_pDrebApi.GetLogPoint();
	m_pRes.m_log = m_pLog;
	//初始线程
	m_pDrebMsgThread.m_pSgeMgr = &m_pSgeMgr;
	m_pDrebMsgThread.m_pRcvQueue = &m_pSendQueue;
	m_pDrebMsgThread.m_pFlowData = &m_pFlowData;

	if (!m_pDrebMsgThread.Init(&m_pDrebApi,&m_pRes))
	{
		printf("消息处理线程初始化出错! \n");
		return false;
	}
	//初始化动态库

	CXmlNode *offernode =  m_pRes.m_pXml.GetNodeByPath("/package/head/报盘机配置",false);
	if (offernode == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML配置无[/package/head/报盘机配置]节点");
		printf("XML配置无[/package/head/报盘机配置]节点! \n");
		return false;
	}
	offernode = (CXmlNode *)offernode->GetFirstChild();
	if (offernode == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML配置[/package/head/报盘机配置]节点无子节点");
		printf("XML配置[/package/head/报盘机配置]节点无子节点! \n");
		return false;
	}	
	//从配置中打开动态库，读取动态库里的交易码，初始化动态库
	S_SGE_GEMS2_API  api;
	CXmlNode *dllnode = NULL;
	char tmpchar[100];
	std::string nodetype;
	while (offernode != NULL)
	{
		
		sprintf(tmpchar,"/package/head/报盘机配置/%s/DLLNAME",offernode->GetNodeName(false).c_str());
		dllnode = (CXmlNode *)m_pRes.m_pXml.GetNodeByPath(tmpchar,false);
		if (dllnode == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML配置[/package/head/报盘机配置/%s]节点无DLLNAME子节点或有多个",offernode->GetNodeName(false).c_str());
			printf("XML配置[/package/head/报盘机配置/%s]节点无DLLNAME子节点或有多个\n",offernode->GetNodeName(false).c_str());
			return false;
		}
		api.apidllhandle =NULL;
		api.apidllname= dllnode->GetNodeValue(false);
		if (m_pRes.m_pXml.GetNodeAttribute(tmpchar,false,"method",false,api.apiInstance,false) == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML配置[/package/head/报盘机配置/%s/DLLNAME]节点无method属性",offernode->GetNodeName(false).c_str());
			printf("XML配置[/package/head/报盘机配置/%s/DLLNAME]节点无method属性\n",offernode->GetNodeName(false).c_str());
			return false;
		}
		if (m_pRes.m_pXml.GetNodeAttribute(tmpchar,false,"dllpath",false,api.apidllpath,false) == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML配置[/package/head/报盘机配置/%s/DLLNAME]节点无dllpath属性",offernode->GetNodeName(false).c_str());
			printf("XML配置[/package/head/报盘机配置/%s/DLLNAME]节点无dllpath属性\n",offernode->GetNodeName(false).c_str());
			return false;
		}
		sprintf(tmpchar,"/package/head/报盘机配置/%s/节点类型",offernode->GetNodeName(false).c_str());
		if (m_pRes.m_pXml.GetNodeValueByPath(tmpchar,false,nodetype,false) == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"XML配置[/package/head/报盘机配置/%s]节点无节点类型子节点或有多个",offernode->GetNodeName(false).c_str());
			printf("XML配置[/package/head/报盘机配置/%s]节点无节点类型子节点或有多个\n",offernode->GetNodeName(false).c_str());
			return false;
		}
		if (m_pRes.g_sNodeType.length()<1)
		{
			m_pRes.g_sNodeType = nodetype;
		}
		else 
		{
			//有多个节点类型用,分隔
			m_pRes.g_sNodeType = m_pRes.g_sNodeType+","+nodetype;
		}

		api.apiPoint = NULL;
		api.apistruct = new S_SGE_GEMS2_API_STRUCT();
		if (api.apistruct == NULL)
		{
			return false;
		}
		memset(api.apistruct, 0, sizeof(S_SGE_GEMS2_API_STRUCT));
		api.apistruct->cb_.api_recv_msg_ = __recv_msg; 
		api.apistruct->cb_.api_cb_connected_ = __cb_connected;
		api.apistruct->cb_.api_cb_disconnected_ = __cb_disconnect;

//		printf("inti api_cb_connected_[%x] api_cb_disconnected_[%x] \n",api.apistruct->cb_.api_cb_connected_,api.apistruct->cb_.api_cb_disconnected_);

		sprintf(tmpchar,"/package/head/报盘机配置/%s",offernode->GetNodeName(false).c_str());
		api.offernodepath = tmpchar;
		api.apistructpvalue = (UINT64_)(api.apistruct);
		m_vApiDllClass.push_back(api);
		offernode = (CXmlNode *)offernode->getNextSibling();
	}


	m_pFlowData.SetPara(m_pLog,&(m_pListenThread.m_pSockMgr),&m_pDrebApi,&m_pRes);
	//20170330，在启动时不初始化去读流文件，当为主机时再去初始化
//	m_pFlowData.Init();

	char errmsg[300];
	bzero(errmsg,sizeof(errmsg));
	S_SGE_TBL_FUNC func;
	bool bRet;
	int i=0;
	//打开动态库，初始化
	for (i=0; i< m_vApiDllClass.size() ; i++)
	{
		if (!OpenDll(&(m_vApiDllClass[i].apidllhandle),m_vApiDllClass[i].apidllname.c_str(),m_vApiDllClass[i].apidllpath.c_str()))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"打开动态库[%s]失败",m_vApiDllClass[i].apidllname.c_str());
			printf("打开动态库[%s]失败\n",m_vApiDllClass[i].apidllname.c_str());
			return false;
		}
		NEWOFFERINGNSTANCE baseinstance = (NEWOFFERINGNSTANCE)GETINSTANCE(m_vApiDllClass[i].apidllhandle,m_vApiDllClass[i].apiInstance.c_str());
		if (NULL == baseinstance)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]实例化失败",m_vApiDllClass[i].apidllname.c_str());
			printf("动态库[%s]实例化失败\n",m_vApiDllClass[i].apidllname.c_str());
			return false;
		}
		m_vApiDllClass[i].apiPoint =(CIOfferingBase *)baseinstance(); 
		if (NULL == m_vApiDllClass[i].apiPoint)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]实例化失败",m_vApiDllClass[i].apidllname.c_str());
			printf("动态库[%s]实例化失败\n",m_vApiDllClass[i].apidllname.c_str());
			return false;
		}
		try
		{
// 			m_pRes.m_pXml.ToFile("t2.xml");
// 			printf("m_pRes.m_pXml[%x]\n",&m_pRes.m_pXml);
			//初始化
			//if (!m_vApiDllClass[i].apiPoint->Init(&(m_vApiDllClass[i]),m_pLog,confile,m_vApiDllClass[i].offernodepath.c_str(),errmsg))
			if (!m_vApiDllClass[i].apiPoint->Init(&(m_vApiDllClass[i]),m_pLog,&(m_pRes.m_pXml),m_vApiDllClass[i].offernodepath.c_str(),errmsg))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]Init失败[%s]",m_vApiDllClass[i].apidllname.c_str(),errmsg);
				printf("动态库[%s]Init失败[%s]\n",m_vApiDllClass[i].apidllname.c_str(),errmsg);
				return false;
			}
			m_vApiDllClass[i].apiPoint->m_sSeatNo = m_pRes.m_sSeatNo;
			bzero(&func,sizeof(S_SGE_TBL_FUNC));
			//得到动态库里的交易码
			bRet = m_vApiDllClass[i].apiPoint->FirstFunc(func);
			if (!bRet)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]无交易",m_vApiDllClass[i].apidllname.c_str());
				printf("动态库[%s]无交易\n",m_vApiDllClass[i].apidllname.c_str());
				return false;
			}
			while (bRet)
			{
				func.nCallNum = 0;
				func.pBuInstance = m_vApiDllClass[i].apiPoint;
				CBF_Tools::StringCopy(func.sDllName,200,  m_vApiDllClass[i].apidllname.c_str());
				
				if (!m_pFuncList.Insert(func))
				{
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]交易[%d]重复",m_vApiDllClass[i].apidllname.c_str(),func.nFuncNo);
					printf("动态库[%s]交易[%d]重复\n",m_vApiDllClass[i].apidllname.c_str(),func.nFuncNo);
				}
				//将交易放到注册列表中，当总线连接上后注册上去
				if (m_pRes.m_nUseSeatNoPrefix == 1)
				{
					//报盘机交易码只能小于8位数字
					m_pRes.g_lSvrTxList.push_back(m_pRes.m_nSeatNoPrefix*100000000+func.nFuncNo);
				}
				else
				{
					m_pRes.g_lSvrTxList.push_back(func.nFuncNo);
				}
				

				bRet = m_vApiDllClass[i].apiPoint->NextFunc(func);
			}
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"调用业务动态库%s初始化异常出错",m_vApiDllClass[i].apidllname.c_str());
			printf("调用业务动态库[%s]初始化异常出错\n",m_vApiDllClass[i].apidllname.c_str());
			return false;
		}
		for (int k=0; k< MAXFLOWNO; k++)
		{
			m_vApiDllClass[i].apiPoint->m_FlowInfo[k] =  &(m_pFlowData.m_FlowInfo[k]);
		}
		
	}
	//将断点续传交易注册到总线
	if (m_pRes.m_nUseSeatNoPrefix == 1)
	{
		//报盘机交易码只能小于8位数字
		m_pRes.g_lSvrTxList.push_back(m_pRes.m_nSeatNoPrefix*100000000+TRADEFRONT_BAEAKPOINT);
	}
	else
	{
		m_pRes.g_lSvrTxList.push_back(TRADEFRONT_BAEAKPOINT);
	}
	

	m_pSgeMgr.InitDll(&m_pRes,m_pLog,&m_pFuncList,&m_vApiDllClass,&m_pFlowData);
	
	if (!m_pListenThread.InitFront(&m_pRes,&m_pSendQueue,&m_pSgeMgr,m_pLog))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"初始化侦听线程出错");
		printf("初始化侦听线程出错\n");
		return false;
	}
	
	m_pSendQueue.m_pRes = &m_pRes;
	m_pSgeRcvQueue.m_pRes = &m_pRes;
	m_pSgeBackQueue.m_pRes = &m_pRes;
	m_pSgeProcQueue.m_pRes = &m_pRes;
	
	for (i=0 ;i < 3 ; i++)
	{
		m_pSgeMsgProcThread[i].SetPara(&m_pRes,&m_pSgeRcvQueue,&m_pMsgHead,&m_pDrebApi,&m_pFlowData,&(m_pListenThread.m_pSockMgr));
		m_pSgeMsgProcThread[i].m_vApiDllClass = &m_vApiDllClass;
		m_pSgeMsgProcThread[i].m_nIndex =i;
		m_pSgeMsgProcThread[i].m_pSgeProcQueue = &(m_pSgeProcQueue);
		m_pSgeMsgProcThread[i].m_pSgeBackQueue = &(m_pSgeBackQueue);
	}
	for (i=0 ;i < 3 ; i++)
	{
		m_pYlMsgProcThread[i].m_nIndex =i;
		m_pYlMsgProcThread[i].m_pSgeMgr = &m_pSgeMgr;
		m_pYlMsgProcThread[i].SetPara(&m_pRes,&m_pSendQueue,&m_pMsgHead,&m_pFuncList,&m_pDrebApi,&m_pFlowData,&(m_pListenThread.m_pSockMgr));
	}

	m_bIsInit = true;

	
	return true;
}

bool CTradeMain::Start()
{
	if (!m_bIsInit)
	{
		printf("未初始化 \n");
		return false;
	}
	//启动api线程
	if (!m_pDrebApi.Start())
	{
		printf("启动总线线程失败 \n");
		return false;
	}
	//启动消息处理线程
	if (!m_pDrebMsgThread.Start())
	{
		printf("启动总线消息处理线程失败 \n");
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"启动总线消息处理线程失败!");
		m_pDrebApi.Stop();
		return false;
	}

	if (!m_pListenThread.StartFront())
	{
		printf("启动侦听线程失败 \n");
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"启动侦听线程失败!");
		m_pDrebApi.Stop();
		m_pDrebMsgThread.Stop();
		return false;
	}
	int i=0;
	int j=0;
	for (i=0 ;i < 3 ; i++)
	{
		if (!m_pSgeMsgProcThread[i].Start())
		{
			printf("启动SGE消息处理线程失败 %d\n",i);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"启动SGE消息处理线程[%d]失败!",i);
			m_pDrebApi.Stop();
			m_pDrebMsgThread.Stop();
			m_pListenThread.StopFront();
			return false;
		}
	}
	for (i=0 ;i < 3 ; i++)
	{
		if (!m_pYlMsgProcThread[i].Start())
		{
			printf("启动发送处理线程失败 \n");
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"启动发送处理线程失败!");
			m_pDrebApi.Stop();
			m_pDrebMsgThread.Stop();
			m_pListenThread.StopFront();
			for (j=0 ;j < 3 ; j++)
			{
				m_pSgeMsgProcThread[j].Stop();
			}
			return false;
		}
	}
	if (m_pRes.m_nArbMode != 1)
	{
		if (!m_pSgeMgr.Start())
		{
			printf("启动SGE API 管理线程 失败 \n");
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"启动SGE API 管理线程 失败!");
			m_pDrebApi.Stop();
			m_pDrebMsgThread.Stop();
			m_pListenThread.StopFront();
			for (i=0 ;i < 3 ; i++)
			{
				m_pSgeMsgProcThread[i].Stop();
				m_pYlMsgProcThread[i].Stop();
			}
			
			return false;
		}
	}

	
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"启动报盘机完成!");
	return true;
}

void CTradeMain::Stop()
{
	
//	printf("退出！");
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"开始退出API管理线程!");
	m_pSgeMgr.Stop();
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"退出API管理线程!");

	m_pDrebMsgThread.Stop();
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"退出总线消息处理线程!");
	m_pListenThread.StopFront();
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"退出侦听线程!");

	

	int i=0;
	for (i=0 ;i < 3 ; i++)
	{
		m_pSgeMsgProcThread[i].Stop();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"退出SGE消息处理线程[%d]!",i);
		m_pYlMsgProcThread[i].Stop();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"退出发送处理线程[%d]!",i);
	}
	
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"退出报盘处理线程!");
	m_pDrebApi.Stop();
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"退出总线API线程!");
	SLEEP_SECONDS(5);
	for (i=0 ;i < 3 ; i++)
	{
		m_pSgeMsgProcThread[i].Join();
		m_pYlMsgProcThread[i].Join();
	}
	m_pListenThread.Join();
	m_pDrebMsgThread.Join();
	m_pSgeMgr.Join();

}

void CTradeMain::Monitor()
{
	if (g_pRunFlag == 0)
	{
		return;
	}
 	m_pDrebApi.MonitorThread();
	if (m_pDrebMsgThread.IsStoped())
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"重启总线消息处理线程!");
		m_pDrebMsgThread.Start();
	}
	if (g_pRunFlag == 0)
	{
		return;
	}
	if (m_pListenThread.IsStoped())
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"重启侦听线程!");
		m_pListenThread.StartFront();
	}
	int i=0;
	for (i=0 ;i < 3 ; i++)
	{
		if (m_pSgeMsgProcThread[i].IsStoped())
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"重启SGE消息处理线程[%d]!",i);
			m_pSgeMsgProcThread[i].Start();
		}
		if (m_pYlMsgProcThread[i].IsStoped())
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"重启发送处理线程[%d]!",i);
			m_pYlMsgProcThread[i].Start();
		}
	}
	switch (m_pRes.m_nSvrHostStatus)
	{
		case ARBSTATUS_UNKNOW:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"节点[%d %d]当前服务状态为 [未知]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		case ARBSTATUS_MASTER:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"节点[%d %d]当前服务状态为 [主机]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		case ARBSTATUS_MASTER_AYN:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"节点[%d %d]当前服务状态为 [主机同步]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		case ARBSTATUS_BACKUP:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"节点[%d %d]当前服务状态为 [备机]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		case ARBSTATUS_BACKUP_AYN:
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"节点[%d %d]当前服务状态为 [备机同步]\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId);
			break;
		default: 
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"节点[%d %d]当前服务状态为错误状态 %d\n",m_pRes.g_nSvrMainId,m_pRes.g_nSvrPrivateId,m_pRes.m_nSvrHostStatus);
			break;
		
	}
	if (m_pRes.m_nSvrHostStatus == ARBSTATUS_MASTER) //只有主机才去检查api管理线程是否停止
	{
		if (g_pRunFlag == 0)
		{
			return;
		}
		if (m_pSgeMgr.IsStoped())
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"重启SGE API 管理线程!");
			m_pSgeMgr.Start();
		}
		
	}
 	//更新消息头，将过期的删除
 	m_pMsgHead.Update();

	//打印队列数目
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"待发送交易所队列数目[%d] 接收交易所队列数目[%d] 交易所请求应答队列[%d] 交易所回报队列[%d]",\
		m_pSendQueue.GetSize(),m_pSgeRcvQueue.GetSize(),m_pSgeProcQueue.GetSize(),m_pSgeBackQueue.GetSize());
	
	int total;
	int unused;
	int bufsize;
	m_pDrebApi.GetBufferPoolInfo(total,unused,bufsize);
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"总线内存情况  总数[%d] 未使用[%d]  缓冲大小[%d]",total,unused,bufsize);

	m_pListenThread.m_pMemPool.PoolInfo(total,unused);
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"select线程内存情况 总数[%d] 未使用[%d]  缓冲大小[%d]",total,unused,MAX_OFFERINGDATA_LEN+20);

	

}
bool CTradeMain::OpenDll(DLLHANDLE *pDll, const char *dllname, const char *dllpath)
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
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		sprintf(dllpathname,"%s",dllname);
		CBF_Tools::LRtrim(dllpathname);
		*pDll = LOADDLL(dllpathname);
		if (ISNOTOPEN(*pDll))
		{
			sprintf(errmsg,"打开动态库[%s]失败",dllpathname);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
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
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		sprintf(dllpathname,"%s",dllname);
		CBF_Tools::LRtrim(dllpathname);
		*pDll = LOADDLL(dllpathname);
		pdllerror = dlerror();
		if (pdllerror!=NULL)
		{
			sprintf(errmsg,"打开动态库[%s]失败[%s]",dllpathname,pdllerror);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		
	}
#endif	
	return true;
}

void CTradeMain::PushRcvData(S_SGE_DATA &data)
{
	m_pSgeRcvQueue.PushData(data);
	return;
}
