// SgeMsgProcThread.cpp: implementation of the CSgeMsgProcThread class.
//
//////////////////////////////////////////////////////////////////////

#include "SgeMsgProcThread.h"
#include "TradeMain.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CTradeMain g_pOfferingMain;
extern int   g_pRunFlag;

CSgeMsgProcThread::CSgeMsgProcThread()
{
	m_pRes = NULL;
	m_pRcvQueue= NULL;
	m_pMsgHead= NULL;
	m_pDrebApi = NULL;
	m_pFlowData = NULL;
	m_bIsRunning = false;
	m_pSockMgr = NULL;
	m_vApiDllClass = NULL;
	m_pLog = NULL;
	m_pRspXml = NULL;
	m_nIndex = 0;
	m_pSgeBackQueue = NULL;
	m_pSgeProcQueue = NULL;
	t_tmpdatalen =0;
}

CSgeMsgProcThread::~CSgeMsgProcThread()
{
	m_pRes = NULL;
	m_pRcvQueue= NULL;
	m_pMsgHead= NULL;
	m_pDrebApi = NULL;
	m_pFlowData = NULL;
	m_bIsRunning = false;
	m_pSockMgr = NULL;
	m_vApiDllClass = NULL;
	m_pLog = NULL;
	m_pRspXml = NULL;
	m_pSgeBackQueue = NULL;
	m_pSgeProcQueue = NULL;
}
int CSgeMsgProcThread::Run()
{
	S_SGE_DATA data;
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"启动SGE消息处理线程[%d]",m_nIndex);
	while (m_bIsRunning)
	{
		if (m_nIndex == 0) //处理加解密
		{
			if (m_pRcvQueue->GetData(data))
			{
				if(data.type == GTP_TYPE_STRING)
				{ 
					//				g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"收到的SGE数据",(char *)data.data.sBuffer,data.data.sDBHead.nLen);
					// is the no_enc msg
					//明文
					for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
					{
						if (g_pOfferingMain.m_vApiDllClass[i].apistruct == data.pctx)
						{
							//保存动态库的索引，接收处理线程可根据此字段判定是哪个动态库接收到的
							data.data.sBpcHead.cMsgType = i;
							data.data.sBpcHead.nBpcLen = atoi(g_pOfferingMain.m_vApiDllClass[i].apiPoint->m_sNodeType.c_str());
							break;
						}
					}
					//				m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始处理SGE数据");
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"动态库[%s] 收到的GTP数据包长度[%d]",m_vApiDllClass->at(data.data.sBpcHead.cMsgType).apidllname.c_str(),data.data.sDBHead.nLen);
					m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"收到的GTP数据包",data.data.sBuffer,data.data.sDBHead.nLen);
				}
				else if(data.type == GTP_TYPE_ENCRYPT)
				{
					
					BPCCOMMSTRU rdata;
					bzero(&rdata,sizeof(BPCCOMMSTRU));
					memcpy(&rdata,&(data.data),sizeof(BPCCOMMSTRU));
					int msglen = BPUDATASIZE;
					//解密
					g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"收到的SGE加密数据",(char *)data.data.sBuffer,data.data.sDBHead.nLen);
					//根据pctx找到对应api实例类，然后调用api实例类方法解密
					for (int i=0; i<g_pOfferingMain.m_vApiDllClass.size(); i++)
					{
						if (g_pOfferingMain.m_vApiDllClass[i].apistruct == data.pctx)
						{
							//g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"收到的SGE数据",(char *)rdata.sBuffer,rdata.sDBHead.nLen);
							if (!g_pOfferingMain.m_vApiDllClass[i].apiPoint->Uncrypt(data.pctx,rdata.sBuffer,rdata.sDBHead.nLen,data.data.sBuffer,msglen))
							{
								g_pOfferingMain.m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据",(char *)rdata.sBuffer,rdata.sDBHead.nLen);
								g_pOfferingMain.m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"动态库[%s]实例解密出错",g_pOfferingMain.m_vApiDllClass[i].apidllname.c_str());
								break;
							}
							data.data.sDBHead.nLen = msglen;
							g_pOfferingMain.m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"解密后的SGE数据",data.data.sBuffer,data.data.sDBHead.nLen);
							//保存动态库的索引，接收处理线程可根据此字段判定是哪个动态库接收到的
							data.data.sBpcHead.cMsgType = i;
							data.data.sBpcHead.nBpcLen = atoi(g_pOfferingMain.m_vApiDllClass[i].apiPoint->m_sNodeType.c_str());
							//有数据过来就置连接时间为当前时间
							g_pOfferingMain.m_vApiDllClass[i].apiPoint->m_nConnectTime = time(NULL);
							m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"动态库[%s] 收到的GTP数据包长度[%d]",m_vApiDllClass->at(data.data.sBpcHead.cMsgType).apidllname.c_str(),data.data.sDBHead.nLen);
							m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"收到的GTP数据包",data.data.sBuffer,data.data.sDBHead.nLen);

						}
					}
				}
				else
				{
					//printf("this message is no handled,msg: %s", msg);
					g_pOfferingMain.m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"收到的SGE数据类型不符",(char *)data.data.sBuffer,data.data.sDBHead.nLen);
					continue;
				}
				//预处理，解析得到交易码，放到不同的队列,如果是登录返回直接处理
				PreProcData(data);
			}
			else
			{
				SLEEP(1);
			}
			continue;
		}
		if (m_nIndex == 2)
		{
			//printf("处理回报\n");
			if (m_pSgeBackQueue->GetData(data))
			{
				ProcData(data.data);
			}
			else
			{
				SLEEP(1);
			}
			continue;
		}
		if (m_nIndex == 1)
		{ //应答请求
		
			//printf("应答请求\n");
			if (m_pSgeProcQueue->GetData(data))
			{
				ProcData(data.data);
			}
			else
			{
				SLEEP(1);
			}
		}
	}
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"停止SGE消息处理线程[%d]",m_nIndex);
	return 0;
}

bool CSgeMsgProcThread::InitThreadInstance()
{
	return true;
}


void CSgeMsgProcThread::ExitThreadInstance()
{
	return ;
}

void CSgeMsgProcThread::SetPara(CTradeResource *res, CPoolDataMsgSge *que, CMsgHead *msghead,CBF_DrebServer *api,CFlowData *fd,CSocketMgr *sockmgr)
{
	m_pRes = res;
	m_pRcvQueue = que;
	m_pMsgHead = msghead;
	m_pDrebApi = api;
	m_pFlowData = fd;
	m_pSockMgr  = sockmgr;
	m_pLog = m_pDrebApi->GetLogPoint();
	m_pRspXml = &(m_pRes->m_pRspXml);
}

bool CSgeMsgProcThread::Start()
{
	m_bIsRunning = true;
	CreateThread();
	return true;
}

void CSgeMsgProcThread::Stop()
{
	m_bIsRunning = false;
//	printf("开始退出CSgeMsgProcThread\n");
//	Join();
//	printf("结束退出CSgeMsgProcThread\n");
}

void CSgeMsgProcThread::ProcData(BPCCOMMSTRU &data)
{

	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d]开始处理ProcData",m_nIndex);
	t_butime = CBF_Date_Time::GetTickUS();

	switch (data.sBpcHead.nMsgFlag)
	{
		case 0: //请求
			ProcRequest(data);
			t_eutime = CBF_Date_Time::GetTickUS();
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 处理交易所过来请求数据时间[%d]微秒",m_nIndex,t_eutime-t_butime);
			break;
		case 1: //应答
			ProcAns(data);
			t_eutime = CBF_Date_Time::GetTickUS();
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 处理交易所过来应答数据时间[%d]微秒",m_nIndex,t_eutime-t_butime);
			break;
		case 2: //回报
			ProcBack(data);
			t_eutime = CBF_Date_Time::GetTickUS();
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 处理交易所过来回报数据时间[%d]微秒",m_nIndex,t_eutime-t_butime);
			break;
		default:
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"报文标识[%d]不符 0请求，1应答 2回报",data.sBpcHead.nMsgFlag);
			break;
	}
	
	
	return;

}

void CSgeMsgProcThread::DSP_2_HEX(const char *dsp,char *hex,int count)
{
    int i;
	int hexcount=count/2;
    for(i = 0; i < hexcount; i++)
    {
		hex[i]=((dsp[i*2]<=0x39)?dsp[i*2]-0x30:dsp[i*2]-0x41+10);
        hex[i]=hex[i]<<4;
		hex[i]+=((dsp[i*2+1]<=0x39)?dsp[i*2+1]-0x30:dsp[i*2+1]-0x41+10);
    }
} 

void CSgeMsgProcThread::HEX_2_DSP(const char *hex,char *dsp,int count)
{
    int i;
    char ch;
    for(i = 0; i < count; i++)
    {
        ch=(hex[i]&0xf0)>>4;
        dsp[i*2]=(ch>9)?ch+0x41-10:ch+0x30;
        ch=hex[i]&0xf;
        dsp[i*2+1]=(ch>9)?ch+0x41-10:ch+0x30;
    }
} 

void CSgeMsgProcThread::ProcLogin(BPCCOMMSTRU &data)
{
	std::string srspcode;
	std::string srspmsg;
	t_fieldtype=0;
	int nChgData=0;
	char tmpchar[1000];

	
	//登录应答
	
//	int nRet = gtp->GetValueByName("X39",srspcode,t_fieldtype);
//	if (nRet <0)
	if (!GetGtpValue(data.sBuffer,"X39",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X39响应代码字段或类型不符");
		return;
	}
	srspcode = tmpchar;
//	nRet = gtp->GetValueByName("X40",srspmsg,t_fieldtype);
//	if (nRet <0)
	if (!GetGtpValue(data.sBuffer,"X40",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X40响应信息字段或类型不符");
		return;
	}
	srspmsg = tmpchar;
	if (data.sDBHead.d_Dinfo.d_nServiceNo == 76549481 || data.sDBHead.d_Dinfo.d_nServiceNo == 76551481)  //A101 登录应答  A301 ETF登录应答
	{
		//登录不管成不成功，只要有交易日期，流文件类要处理
		std::string stradedate;
//		nRet = gtp->GetValueByName("T13",stradedate,t_fieldtype);
//		if (nRet <0)
		if (!GetGtpValue(data.sBuffer,"T13",tmpchar))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无T13交易日期字段或类型不符");
		}
		else
		{
			stradedate = tmpchar;
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"交易员登录返回 交易日期[%s]",stradedate.c_str());

			//流切换日期
			nChgData = m_pFlowData->Login(stradedate.c_str());
			m_pRes->g_sTradeDate = stradedate;
			if (m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->m_sNodeType.compare("12") == 0 || \
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->m_sNodeType.compare("20") == 0 )
			{

			}
			else  //不是ETF报盘机
			{
				//使用返回的日期
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->m_sTradeDate = stradedate;
			}
			
		}
		
		//RSP000000为成功
		if (srspcode.compare("RSP000000") != 0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员登录返回不成功[%s -%s]",srspcode.c_str(),srspmsg.c_str());
			try
			{
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->LoginRsp(0,data.sBuffer);
			}
			catch (...)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员登录返回不成功 调用LoginRsp异常");
				return;
			}
			//20161020 songfree add 如果是已登录，直接发送录出指令
			if (srspcode.compare("RSP013005") == 0)
			{
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->TradeLogout();
			}
			return;
		}
		//找到对应实例，调用logrsp   sBpcHead.cMsgType保存的是对应的实例容器下标
		try
		{
			m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->LoginRsp(1,data.sBuffer);
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员登录返回成功 调用LoginRsp异常");
			return;
		}
		if (nChgData == 1) //日切，要重登录
		{
			try
			{
				m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"日切先交易员录出再重新登录");
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->TradeLogout();
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->Disconnect();
			}
			catch (...)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"日切换用交易员录出异常");
				return;
			}
		}
		return;
	}
	else if (data.sDBHead.d_Dinfo.d_nServiceNo == 76549491 || data.sDBHead.d_Dinfo.d_nServiceNo == 76551491)  //A111 录出应答  A311 etf录出应答
	{
		if (srspcode.compare("RSP000000") != 0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员录出返回不成功[%s -%s]",srspcode.c_str(),srspmsg.c_str());
			try
			{
				m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->LoginRsp(0,data.sBuffer);
			}
			catch (...)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员录出返回不成功 调用LoginRsp异常");
				return;
			}
			return;
		}
		try
		{
			m_vApiDllClass->at(data.sBpcHead.cMsgType).apiPoint->LoginRsp(0,data.sBuffer);
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员录出返回成功 调用LoginRsp异常");
			return;
		}
		return;
	}
	return;
}
void CSgeMsgProcThread::ProcRequest(BPCCOMMSTRU &data)
{
	//交易所过来的请求

	if (m_pRes->g_nSendDrebBack == 1)
	{
		S_BPC_RSMSG drebmsg;
		drebmsg.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
		if (NULL == drebmsg.sMsgBuf)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"分配总线内存空间出划");
			return ;
		}
		//复制报文头
		memcpy(&(drebmsg.sMsgBuf->sBpcHead),&(data.sBpcHead),BPCHEADLEN);
		memcpy(&(drebmsg.sMsgBuf->sDBHead),&(data.sDBHead),DREBHEADLEN);
		if (data.sDBHead.nLen>0)
		{
			memcpy(drebmsg.sMsgBuf->sBuffer,data.sBuffer,data.sDBHead.nLen);
		}
		//置标志
		drebmsg.sMsgBuf->sBpcHead.nIndex=100;
		drebmsg.sMsgBuf->sDBHead.cCmd = CMD_DPABC;//广播
		drebmsg.sMsgBuf->sDBHead.cZip = 0;
		drebmsg.sMsgBuf->sDBHead.cRaflag = 0;
		drebmsg.sMsgBuf->sDBHead.cNextFlag = 0;
		//全局广播
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nNodeId = m_pRes->g_nSendDrebNode;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cNodePrivateId =0;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nSvrMainId =0;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cSvrPrivateId =0;
		
		m_pDrebApi->SendMsg(drebmsg);
	}
	
	

	//通过连接发给交易服务器
	S_OFFERING_DATA senddata;
	//组KV报文
	m_pKvData.clear();
	m_pKvData.setPack("ApiName","onRcvGtpMsg");
	m_pKvData.setPack("TXCODE",data.sDBHead.d_Dinfo.d_nServiceNo);
	
	m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送GTP请求报文",(char *)data.sBuffer,data.sDBHead.nLen);
	
	bzero(t_tmpdata,sizeof(t_tmpdata));
	HEX_2_DSP(data.sBuffer,t_tmpdata,data.sDBHead.nLen);
	m_pKvData.setPack("GTPDATA",t_tmpdata);
	t_skvdatas="";
	if (!m_pKvData.ToString(t_skvdatas))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送回报 kv ToString出错");
		return ;
	}
	
	for (int i=0; i<m_pSockMgr->m_socketList.size(); i++)
	{
		if (m_pSockMgr->at(i)->m_sock == INVALID_SOCKET  )
		{
			continue;
		}
		if (!m_pSockMgr->at(i)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送数据分配空间出错");
			return;
		}
		strcpy(senddata.pData,t_skvdatas.c_str());
		senddata.nWantlen = t_skvdatas.length();
		//发送
		m_pSockMgr->at(i)->SendMsg(senddata,1);
		
	}
	return ;

}
void CSgeMsgProcThread::ProcAns(BPCCOMMSTRU &data)
{
	//交易所过来的应答
	//首先取得rootid
	
	memcpy(t_tmpdata,&(data.sDBHead.n_Ninfo),sizeof(data.sDBHead.n_Ninfo)+sizeof(data.sDBHead.b_Cinfo));
	t_srootid = t_tmpdata;

	int gtpdatalen = data.sDBHead.nLen;
	unsigned int txcode = data.sDBHead.d_Dinfo.d_nServiceNo;
	int  dllofset = data.sBpcHead.cMsgType;//动态库的实例下标

	int msgtype=0;
	unsigned int msgserial=0;
	msgtype = data.sBpcHead.nConnectTime; //流类型
	msgserial = data.sBpcHead.nRtime; //流序号
	if (!m_pMsgHead->GetHead(t_srootid.c_str(),data))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ROOTID[%s]对应的报文头不存在或过期",t_srootid.c_str());
		return ;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ROOTID[%s] index[%d]",t_srootid.c_str(),data.sBpcHead.nIndex);

	
	
	if (1 == data.sBpcHead.nBpuIndex)//表示侦听过来的
	{
		S_OFFERING_DATA senddata;
		if (!m_pSockMgr->at(data.sBpcHead.nIndex)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送数据分配空间出错");
			return;
		}

		//组KV报文
// 		m_pKvData.clear();
// 		std::string sgtpstring;
// 		m_pKvData.setPack("ApiName","onRcvGtpMsg");
// 		m_pKvData.setPack("TXCODE",txcode);
// 
// 		//kvdata.setPack("NodeID",m_pRes->g_nSvrMainId);
// 		char tmpchar[11];
// 		sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
// 		m_pKvData.setPack("NodeID",tmpchar);
// 
// 		m_pKvData.setPack("NodeType",data.sBpcHead.nBpcLen);
// 		
// 		m_pKvData.setPack("SequenceSeriesNo",data.sBpcHead.nConnectTime);
// 		
// 		m_pKvData.setPack("SequenceNo",data.sBpcHead.nRtime);
// 
// 		if (m_pLog->isWrite(LOG_DEBUG+1))
// 		{
// 			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送GTP应答报文 index[%d]",data.sBpcHead.nIndex);
// 			m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送GTP应答报文",(char *)data.sBuffer,data.sDBHead.nLen);
// 		}
// 		
// 		bzero(senddata.pData,gtpdatalen*2+1);
// 		HEX_2_DSP(data.sBuffer,senddata.pData,gtpdatalen);
// 		m_pKvData.setPack("GTPDATA",senddata.pData);
// 		t_skvdatas = "";
// 		if (!m_pKvData.ToString(t_skvdatas))
// 		{
// 			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送应答 kv ToString出错");
// 			m_pSockMgr->at(data.sBpcHead.nIndex)->PoolFree(senddata.pData);
// 			senddata.pData = NULL;
// 			return ;
// 		}
// 		strcpy(senddata.pData,t_skvdatas.c_str());
// 		senddata.nWantlen = t_skvdatas.length();

		bzero(senddata.pData,MAX_OFFERINGDATA_LEN+20);
		
		char tmpchar[11];
		sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
		
		sprintf(senddata.pData,"ApiName=onRcvGtpMsg#TXCODE=%d#NodeID=%s#NodeType=%d#SequenceSeriesNo=%d#SequenceNo=%d#TradeDate=%s#GTPDATA=",\
			data.sDBHead.d_Dinfo.d_nServiceNo,tmpchar,data.sBpcHead.nBpcLen,\
			msgtype,msgserial,m_pRes->g_sTradeDate.c_str());
		t_tmpdatalen = strlen(senddata.pData);
		
		HEX_2_DSP(data.sBuffer,senddata.pData+t_tmpdatalen,data.sDBHead.nLen);
		strcat(senddata.pData,"#");
		senddata.nWantlen = strlen(senddata.pData);
		if (m_pLog->isWrite(LOG_DEBUG+1))
		{
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送KV应答报文 index[%d]",data.sBpcHead.nIndex);
			m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送KV应答报文",(char *)senddata.pData,senddata.nWantlen);
		}
		//应答回去
		m_pSockMgr->at(data.sBpcHead.nIndex)->SendMsg(senddata,0);
	}
	else  //总线过来的
	{
		S_BPC_RSMSG drebmsg;
		drebmsg.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
		if (NULL == drebmsg.sMsgBuf)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"分配总线内存空间出划");
			return ;
		}
		//复制报文头
		memcpy(&(drebmsg.sMsgBuf->sBpcHead),&(data.sBpcHead),BPCHEADLEN);
		memcpy(&(drebmsg.sMsgBuf->sDBHead),&(data.sDBHead),DREBHEADLEN);
		if (gtpdatalen>0)
		{
			memcpy(drebmsg.sMsgBuf->sBuffer,data.sBuffer,gtpdatalen);
		}
		//交易日期
		drebmsg.sMsgBuf->sDBHead.n_Ninfo.n_nNextNo = atoi(m_pRes->g_sTradeDate.c_str());

		drebmsg.sMsgBuf->sDBHead.cRaflag = 1;
		drebmsg.sMsgBuf->sDBHead.nLen = gtpdatalen;
		m_pDrebApi->SendMsg(drebmsg);
	}
	return;
}

void CSgeMsgProcThread::ProcBack(BPCCOMMSTRU &data)
{
	//交易所过来的回报
	//首先记流
	UINT64_ etime=CBF_Date_Time::GetTickUS();
	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] ProcBack前耗时[%d]微秒",m_nIndex,etime-t_butime);

	int msgtype=0;
	unsigned int msgserial=0;
	msgtype = data.sBpcHead.nConnectTime;
	msgserial = data.sBpcHead.nRtime;

//	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"index[%d]  流[%d %d] 交易[%d] %s",\
//		m_nIndex,msgtype,msgserial,data.sDBHead.d_Dinfo.d_nServiceNo,data.sBuffer);


 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 写流文件前耗时[%d]微秒",m_nIndex,etime-t_butime);

	if (!m_pFlowData->WriteFlow(msgtype,msgserial,data.sDBHead.d_Dinfo.d_nServiceNo,data))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"index[%d]  记流[%d %d] 交易[%d] 失败",m_nIndex,msgtype,msgserial,data.sDBHead.d_Dinfo.d_nServiceNo);
		m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"GTP报文",data.sBuffer,data.sDBHead.nLen);
	}

 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 写流文件后耗时[%d]微秒 回报发送总线标志[%d]",m_nIndex,etime-t_butime,m_pRes->g_nSendDrebBack);

	if (m_pRes->g_nSendDrebBack == 1)
	{
		if (msgtype == 6)//行情的流类型为6
		{
			if (m_pRes->g_nSendDrebQuotation != 1) //不发行情
			{
				goto aa;
			}
		}
		
		//通过广播发给总线
		S_BPC_RSMSG drebmsg;
		drebmsg.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
		if (NULL == drebmsg.sMsgBuf)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"分配总线内存空间出划");
			return ;
		}
		//复制报文头
		memcpy(&(drebmsg.sMsgBuf->sBpcHead),&(data.sBpcHead),BPCHEADLEN);
		memcpy(&(drebmsg.sMsgBuf->sDBHead),&(data.sDBHead),DREBHEADLEN);
		if (data.sDBHead.nLen>0)
		{
			memcpy(drebmsg.sMsgBuf->sBuffer,data.sBuffer,data.sDBHead.nLen);
		}
		//置标志
		drebmsg.sMsgBuf->sBpcHead.nIndex=100;
		drebmsg.sMsgBuf->sDBHead.cCmd = CMD_DPABC;//广播
		drebmsg.sMsgBuf->sDBHead.cZip = 0;
		drebmsg.sMsgBuf->sDBHead.cRaflag = 0;
		drebmsg.sMsgBuf->sDBHead.cNextFlag = 0;

		//交易日期
		drebmsg.sMsgBuf->sDBHead.n_Ninfo.n_nNextNo = atoi(m_pRes->g_sTradeDate.c_str());
		//全局广播
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nNodeId =m_pRes->g_nSendDrebNode;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cNodePrivateId =0;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nSvrMainId =0;
		drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cSvrPrivateId =0;
		
		m_pDrebApi->SendMsg(drebmsg);
	}
	
aa:
	if (msgtype == 6 && m_pRes->g_nSendQuotation == 0)  //行情为6则配置为不通过socket发给交易服务器
	{
		return ;
	}

// 	etime=CBF_Date_Time::GetTickUS();
// 	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"发给交易服务器前耗时[%d]微秒",etime-t_butime);

	//通过连接发给交易服务器
	S_OFFERING_DATA senddata;
	//组KV报文
	
 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d]  组KV报文前耗时[%d]微秒",m_nIndex,etime-t_butime);

	
	bzero(t_tmpdata,sizeof(t_tmpdata));
	char tmpchar[11];
 	sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);

	sprintf(t_tmpdata,"ApiName=onRcvGtpMsg#TXCODE=%d#NodeID=%s#NodeType=%d#SequenceSeriesNo=%d#SequenceNo=%d#TradeDate=%s#GTPDATA=",\
		data.sDBHead.d_Dinfo.d_nServiceNo,tmpchar,data.sBpcHead.nBpcLen,msgtype,msgserial,m_pRes->g_sTradeDate.c_str());
	t_tmpdatalen = strlen(t_tmpdata);
 	
	HEX_2_DSP(data.sBuffer,t_tmpdata+t_tmpdatalen,data.sDBHead.nLen);
	strcat(t_tmpdata,"#");
	t_tmpdatalen = strlen(t_tmpdata);

	if (m_pLog->isWrite(LOG_DEBUG+1))
	{
		m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送KV回报报文",(char *)t_tmpdata,t_tmpdatalen);
	}

 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 组KV报文完成，准备发往交易服务器前耗时[%d]微秒",m_nIndex,etime-t_butime);
	

	for (int i=1; i<m_pRes->g_nMaxConnectNum; i++)
	{
		if (m_pSockMgr->at(i)->m_sock == INVALID_SOCKET  )
		{
			continue;
		}
		m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] type[%d]",i,m_pSockMgr->at(i)->m_nType);
		if (m_pSockMgr->at(i)->m_nType == SOCK_LISTEN)
		{
			continue;
		}
		if (!m_pSockMgr->at(i)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送数据分配空间出错");
			return;
		}
		strcpy(senddata.pData,t_tmpdata);
		senddata.nWantlen = t_tmpdatalen;
		//发送
		if (t_tmpdatalen <4096)
		{
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"发送index[%d] type[%d]回报报文[%s]",m_pSockMgr->at(i)->m_index,m_pSockMgr->at(i)->m_nType,senddata.pData);
		}
		m_pSockMgr->at(i)->SendMsg(senddata,1);
		
	}
 	etime=CBF_Date_Time::GetTickUS();
 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 发完交易服务器耗时[%d]微秒",m_nIndex,etime-t_butime);
	return ;

}

void CSgeMsgProcThread::ProcLoginBack(BPCCOMMSTRU &data)
{
	int msgtype=0;
	unsigned int msgserial=0;
	std::string sdatastr;
	t_fieldtype=0;
	
	//通过广播发给总线
	S_BPC_RSMSG drebmsg;
	drebmsg.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
	if (NULL == drebmsg.sMsgBuf)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"分配总线内存空间出划");
		return ;
	}
	//复制报文头
	memcpy(&(drebmsg.sMsgBuf->sBpcHead),&(data.sBpcHead),BPCHEADLEN);
	memcpy(&(drebmsg.sMsgBuf->sDBHead),&(data.sDBHead),DREBHEADLEN);
	if (data.sDBHead.nLen>0)
	{
		memcpy(drebmsg.sMsgBuf->sBuffer,data.sBuffer,data.sDBHead.nLen);
	}
	//置标志
	drebmsg.sMsgBuf->sBpcHead.nIndex=100;
	drebmsg.sMsgBuf->sDBHead.cCmd = CMD_DPABC;//广播
	drebmsg.sMsgBuf->sDBHead.cZip = 0;
	drebmsg.sMsgBuf->sDBHead.cRaflag = 0;
	drebmsg.sMsgBuf->sDBHead.cNextFlag = 0;
	//全局广播
	drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nNodeId =m_pRes->g_nSendDrebNode;
	drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cNodePrivateId =0;
	drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_nSvrMainId =0;
	drebmsg.sMsgBuf->sDBHead.d_Dinfo.d_cSvrPrivateId =0;

	//交易日期
	drebmsg.sMsgBuf->sDBHead.n_Ninfo.n_nNextNo = atoi(m_pRes->g_sTradeDate.c_str());
	
	m_pDrebApi->SendMsg(drebmsg);
	
	//通过连接发给交易服务器
	S_OFFERING_DATA senddata;
	//组KV报文
// 	
// 	std::string sgtpstring;
// 	gtp->GetValueByName("X04",sgtpstring,t_fieldtype);
// 	msgtype = atoi(sgtpstring.c_str());
// 	gtp->GetValueByName("X05",sgtpstring,t_fieldtype);
// 	msgserial = atoi(sgtpstring.c_str());

	msgtype = data.sBpcHead.nConnectTime;
	msgserial = data.sBpcHead.nRtime;

// 	m_pKvData.clear();
// 	m_pKvData.setPack("ApiName","onRcvGtpMsg");
// 	m_pKvData.setPack("TXCODE",data.sDBHead.d_Dinfo.d_nServiceNo);
// 	
// 	char tmpchar[11];
// 	sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
// 	m_pKvData.setPack("NodeID",tmpchar);
// 
// 	//kvdata.setPack("NodeID",m_pRes->g_nSvrMainId);
// 	m_pKvData.setPack("NodeType",data.sBpcHead.nBpcLen);
// 	gtp->GetValueByName("X04",sgtpstring,t_fieldtype);
// 	
// 	m_pKvData.setPack("SequenceSeriesNo",sgtpstring.c_str());
// 	gtp->GetValueByName("X05",sgtpstring,t_fieldtype);
// 	m_pKvData.setPack("SequenceNo",sgtpstring.c_str());
// 	m_pKvData.setPack("TradeDate",m_pRes->g_sTradeDate.c_str());//交易日期
// 	
// 	m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送GTP登录应答报文",(char *)data.sBuffer,data.sDBHead.nLen);
// 	char tmpdata[16384];
// 	bzero(tmpdata,sizeof(tmpdata));
// 	HEX_2_DSP(data.sBuffer,tmpdata,data.sDBHead.nLen);
// 	m_pKvData.setPack("GTPDATA",tmpdata);
// 	t_skvdatas ="";
// 	if (!m_pKvData.ToString(t_skvdatas))
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送回报 kv ToString出错");
// 		return ;
// 	}
	m_pLog->LogBin(LOG_PROMPT,__FILE__,__LINE__,"发送GTP登录应答报文",(char *)data.sBuffer,data.sDBHead.nLen);
	bzero(t_tmpdata,sizeof(t_tmpdata));
	char tmpchar[11];
	sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
	
	sprintf(t_tmpdata,"ApiName=onRcvGtpMsg#TXCODE=%d#NodeID=%s#NodeType=%d#SequenceSeriesNo=%d#SequenceNo=%d#TradeDate=%s#GTPDATA=",\
		data.sDBHead.d_Dinfo.d_nServiceNo,tmpchar,data.sBpcHead.nBpcLen,\
		msgtype,msgserial,m_pRes->g_sTradeDate.c_str());
	t_tmpdatalen = strlen(t_tmpdata);
	
	HEX_2_DSP(data.sBuffer,t_tmpdata+t_tmpdatalen,data.sDBHead.nLen);
	strcat(t_tmpdata,"#");
	t_tmpdatalen = strlen(t_tmpdata);
	
	m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"发送登录应答KV报文",(char *)t_tmpdata,t_tmpdatalen);
	for (int i=1; i<m_pSockMgr->m_socketList.size(); i++)
	{
		if (m_pSockMgr->at(i)->m_sock == INVALID_SOCKET  )
		{
			continue;
		}
		if (!m_pSockMgr->at(i)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送数据分配空间出错");
			return;
		}
		strcpy(senddata.pData,t_tmpdata);
		senddata.nWantlen = t_tmpdatalen;
		//发送
		m_pSockMgr->at(i)->SendMsg(senddata,0);
		
	}
	return ;
}

void CSgeMsgProcThread::PreProcData(S_SGE_DATA &data)
{
	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 开始处理PreProcData",m_nIndex);
	
	t_butime = CBF_Date_Time::GetTickUS();
	//得到交易码
	char tmpchar[100];
	bzero(tmpchar,sizeof(tmpchar));
	data.data.sBuffer[data.data.sDBHead.nLen] =0;

	if (!GetGtpValue(data.data.sBuffer,"X03",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X03字段或类型不符");
		return;
	}
	t_stxcode = tmpchar;
	data.data.sDBHead.d_Dinfo.d_nServiceNo = 7*10000000+t_stxcode.c_str()[0]*100000+t_stxcode.c_str()[1]*1000+t_stxcode.c_str()[2]*10+tmpchar[3]-48;
	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"消息类型[%s]转为交易码[%d]",t_stxcode.c_str(),data.data.sDBHead.d_Dinfo.d_nServiceNo);
	
	//使用BPC头的nMsgFlag保存 交易码最后一位，表示请求0，1应答 2回报 
	data.data.sBpcHead.nMsgFlag = tmpchar[3]-48;

	if (!GetGtpValue(data.data.sBuffer,"X04",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X04 序列类别号字段或类型不符");
		return ;
	}
	//使用BPC头的nConnectTime保存X04 流类型 
	data.data.sBpcHead.nConnectTime = atoi(tmpchar);

	if (!GetGtpValue(data.data.sBuffer,"X05",tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X05 消息序列号字段或类型不符");
		return ;
	}

	
	//使用BPC头的nRtime保存X05 流序号 
	data.data.sBpcHead.nRtime = atoi(tmpchar);

	if (data.data.sBpcHead.nConnectTime == 6)
	{
		m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 流[%d %d] 交易[%d]",\
			m_nIndex,data.data.sBpcHead.nConnectTime,data.data.sBpcHead.nRtime,\
			data.data.sDBHead.d_Dinfo.d_nServiceNo);
		m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"GTP报文",data.data.sBuffer,data.data.sDBHead.nLen);
	}
	else
	{
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"index[%d] 流[%d %d] 交易[%d]",\
			m_nIndex,data.data.sBpcHead.nConnectTime,data.data.sBpcHead.nRtime,\
			data.data.sDBHead.d_Dinfo.d_nServiceNo);
		m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"GTP报文",data.data.sBuffer,data.data.sDBHead.nLen);
	}
	

	//登录和退出指令

	
	if (t_stxcode.compare("A101") == 0 || t_stxcode.compare("A111") == 0 || \
		t_stxcode.compare("A301") == 0 || t_stxcode.compare("A311") == 0 )  //etf登录
	{
		ProcLogin(data.data);
		//将应答发给交易服务器
		ProcLoginBack(data.data);
		t_eutime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"index[%d] 处理交易所过来登录录出响应PreProcData数据时间[%d]微秒",m_nIndex,t_eutime-t_butime);
		return;
	}
	if (data.data.sBpcHead.nMsgFlag  == 2) //回报
	{
		//20170330 增加交易员判断，当不是本交易员发出的，根据配置是否发给交易服务器
		if (m_pRes->g_nSendBackLocalTrade == 1)
		{
			if (!GetGtpValue(data.data.sBuffer,"M60",tmpchar))
			{
				
			}
			else
			{
				if (g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_sTradeId.compare(tmpchar) == 0)
				{
					//为本交易员的回报，发回
				}
				else
				{
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"非本交易员的回报，不发给交易服务器,报文交易员[%s] 本交易员[%s]",\
						tmpchar,g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_sTradeId.c_str());
					return;
				}
			}
		}
		g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_nRcvBackTime=time(NULL);//回报时间
		m_pSgeBackQueue->PushData(data);
	}
	else
	{
		g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_nRcvAnsTime=time(NULL);//应答时间
		if (data.data.sBpcHead.nMsgFlag  == 1) //应答
		{
			if (!GetGtpValue(data.data.sBuffer,"X07",tmpchar))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X07 ROOTID字段或类型不符");
				return ;
			}
			//使用n_Ninfo+b_Cinfo这里的四个字段来保存rootid
			memset(&(data.data.sDBHead.n_Ninfo),0,sizeof(data.data.sDBHead.n_Ninfo)+sizeof(data.data.sDBHead.b_Cinfo));
			memcpy(&(data.data.sDBHead.n_Ninfo),tmpchar,strlen(tmpchar));

		}
		m_pSgeProcQueue->PushData(data);
	}
	t_eutime = CBF_Date_Time::GetTickUS();
	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 预处理PreProcData请求应答回报数据时间[%d]微秒",m_nIndex,t_eutime-t_butime);
	return;
}
// 
// void CSgeMsgProcThread::PreProcData(S_SGE_DATA &data)
// {
// 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 开始处理PreProcData",m_nIndex);
// 	t_butime = CBF_Date_Time::GetTickUS();
// 	if (!m_pGtpData.FromBuffer(data.data.sBuffer))
// 	{
// 		m_pLog->LogBin(LOG_ERROR,__FILE__,__LINE__,"数据包非GTP",data.data.sBuffer,data.data.sDBHead.nLen);
// 		return;
// 	}
// 	//得到交易码
// 	
// 	t_fieldtype=0;
// 	int nRet = m_pGtpData.GetValueByName("X03",t_stxcode,t_fieldtype);
// 	if (nRet <0)
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X03字段或类型不符");
// 		return;
// 	}
// 	//转换交易码
// 	if (t_stxcode.length() != 4)
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"消息类型[%s]不符",t_stxcode.c_str());
// 		return;
// 	}
// 	char tmpchar[100];
// 	bzero(tmpchar,sizeof(tmpchar));
// 	tmpchar[0]=t_stxcode.c_str()[3];
// 
// 	data.data.sDBHead.d_Dinfo.d_nServiceNo = 7*10000000+t_stxcode.c_str()[0]*100000+t_stxcode.c_str()[1]*1000+t_stxcode.c_str()[2]*10+atoi(tmpchar);
// 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"消息类型[%s]转为交易码[%d]",t_stxcode.c_str(),data.data.sDBHead.d_Dinfo.d_nServiceNo);
// 	
// 	//使用BPC头的nMsgFlag保存 交易码最后一位，表示请求0，1应答 2回报 
// 	data.data.sBpcHead.nMsgFlag = atoi(tmpchar);
// 
// 	std::string sdatastr;
// 	nRet = m_pGtpData.GetValueByName("X04",sdatastr,t_fieldtype);
// 	if (nRet <0)
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X04 序列类别号字段或类型不符");
// 		return ;
// 	}
// 	//使用BPC头的nConnectTime保存X04 流类型 
// 	data.data.sBpcHead.nConnectTime = atoi(sdatastr.c_str());
// 	nRet = m_pGtpData.GetValueByName("X05",sdatastr,t_fieldtype);
// 	if (nRet <0)
// 	{
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X05 消息序列号字段或类型不符");
// 		return ;
// 	}
// 	//使用BPC头的nRtime保存X05 流序号 
// 	data.data.sBpcHead.nRtime = atoi(sdatastr.c_str());
// 	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"index[%d] 流[%d %d] 交易[%d] %s",\
// 		m_nIndex,data.data.sBpcHead.nConnectTime,data.data.sBpcHead.nRtime,\
// 		data.data.sDBHead.d_Dinfo.d_nServiceNo,data.data.sBuffer);
// 
// 	//登录和退出指令
// 
// 	
// 	if (t_stxcode.compare("A101") == 0 || t_stxcode.compare("A111") == 0 || \
// 		t_stxcode.compare("A301") == 0 || t_stxcode.compare("A311") == 0 )  //etf登录
// 	{
// 		ProcLogin(&m_pGtpData,data.data);
// 		//将应答发给交易服务器
// 		ProcLoginBack(&m_pGtpData,data.data);
// 		t_eutime = CBF_Date_Time::GetTickUS();
// 		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"index[%d] 处理交易所过来登录录出响应PreProcData数据时间[%d]微秒",m_nIndex,t_eutime-t_butime);
// 		return;
// 	}
// 	if (data.data.sBpcHead.nMsgFlag  == 2) //回报
// 	{
// 		//20170330 增加交易员判断，当不是本交易员发出的，根据配置是否发给交易服务器
// 		if (m_pRes->g_nSendBackLocalTrade == 1)
// 		{
// 			nRet = m_pGtpData.GetValueByName("M60",sdatastr,t_fieldtype);
// 			if (nRet <0) //无交易员
// 			{
// 				
// 			}
// 			else
// 			{
// 				if (g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_sTradeId.compare(sdatastr) == 0)
// 				{
// 					//为本交易员的回报，发回
// 				}
// 				else
// 				{
// 					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"非本交易员的回报，不发给交易服务器,报文交易员[%s] 本交易员[%s]",\
// 						sdatastr.c_str(),g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_sTradeId.c_str());
// 					return;
// 				}
// 			}
// 		}
// 		g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_nRcvBackTime=time(NULL);//回报时间
// 		m_pSgeBackQueue->PushData(data);
// 	}
// 	else
// 	{
// 		g_pOfferingMain.m_vApiDllClass[data.data.sBpcHead.cMsgType].apiPoint->m_nRcvAnsTime=time(NULL);//应答时间
// 		if (data.data.sBpcHead.nMsgFlag  == 1) //应答
// 		{
// 			nRet = m_pGtpData.GetValueByName("X07",t_srootid,t_fieldtype);
// 			if (nRet <0)
// 			{
// 				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X07 ROOTID字段或类型不符");
// 				return ;
// 			}
// 			//使用n_Ninfo+b_Cinfo这里的四个字段来保存rootid
// 			memset(&(data.data.sDBHead.n_Ninfo),0,sizeof(data.data.sDBHead.n_Ninfo)+sizeof(data.data.sDBHead.b_Cinfo));
// 			memcpy(&(data.data.sDBHead.n_Ninfo),t_srootid.c_str(),t_srootid.length());
// 
// 		}
// 		m_pSgeProcQueue->PushData(data);
// 	}
// 	t_eutime = CBF_Date_Time::GetTickUS();
// 	m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"index[%d] 预处理PreProcData请求应答回报数据时间[%d]微秒",m_nIndex,t_eutime-t_butime);
// 	return;
// }
bool CSgeMsgProcThread::GetGtpValue(const char *gtpbuffer,const char *key,char *cvalue)
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
		if (!isfind) //查找第一个字符
		{
			if (gtpbuffer[i] == key[keyoffset])
			{
				isfind = true;
				keyoffset++;
				keybegin = i;
				if (keyoffset == kelen) //找到key了，这里只有一个字符的KEY
				{
					if (gtpbuffer[i+1] != '=') //后面的不是=，不是key
					{
						isfind = false;
						keyoffset =0;
					}
					else
					{
						isfindkey = true;
						valuebegin = i+2; //值从这里开始
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
		else  //查找后续
		{
			if (gtpbuffer[i] == key[keyoffset])
			{
				isfind = true;
				keyoffset++;
				if (keyoffset == kelen) //找到key了
				{
					if (gtpbuffer[i+1] != '=') //后面的不是=，不是key
					{
						isfind = false;
						keyoffset =0;
					}
					else
					{
						isfindkey = true;
						valuebegin = i+2; //值从这里开始
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
	if (!isfind || !isfindkey) //没有找到
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
	if (!isend)  //没找到','，说明是最后一个
	{
		valueend = ngtplen;
	}
	memcpy(cvalue,gtpbuffer+valuebegin,valueend -valuebegin);
	cvalue[valueend -valuebegin]=0;
	return true;
}