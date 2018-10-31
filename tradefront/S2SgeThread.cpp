// S2SgeThread.cpp: implementation of the CS2SgeThread class.
//
//////////////////////////////////////////////////////////////////////

#include "S2SgeThread.h"
#include "KvData.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CS2SgeThread::CS2SgeThread()
{
	m_pRes = NULL;
	m_pRcvQueue= NULL;
	m_pMsgHead= NULL;
	m_pFuncList = NULL;
	m_bIsRunning = false;
	m_bIsSetPara = false;
	m_pDrebApi = NULL;
	m_pSockMgr = NULL;
	m_pLog = NULL;
	m_pSgeMgr = NULL;
	m_pFlowData = NULL;
	m_nIndex=0;
	m_pBpkvdata.setPack("ApiName","onRcvGtpMsg");
}

CS2SgeThread::~CS2SgeThread()
{
	m_pRes = NULL;
	m_pRcvQueue= NULL;
	m_pMsgHead= NULL;
	m_pFuncList = NULL;
	m_bIsRunning = false;
	m_bIsSetPara = false;
	m_pDrebApi = NULL;
	m_pSockMgr = NULL;
	m_pLog = NULL;
	m_pSgeMgr = NULL;
	m_pFlowData = NULL;
}
int CS2SgeThread::Run()
{
	BPCCOMMSTRU  data;
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"启动报盘处理线程");
	while (m_bIsRunning)
	{
		
		if (m_pRcvQueue->GetData(data))
		{
			ProcData(data);
		}
		else
		{
			SLEEP(1);
		}
	}
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"停止报盘处理线程");
	return 0;
}

bool CS2SgeThread::InitThreadInstance()
{
	return true;
}


void CS2SgeThread::ExitThreadInstance()
{
	return ;
}
void CS2SgeThread::SetPara(CTradeResource *res, CPoolDataMsg *que, CMsgHead *msghead,CSgeFuncTbl *funclist,CBF_DrebServer *api,CFlowData *fd,CSocketMgr *sockmgr)
{
	m_pRes = res;
	m_pRcvQueue = que;
	m_pMsgHead = msghead;
	m_pFuncList = funclist;
	m_bIsSetPara = true;
	m_pDrebApi = api;
	m_pFlowData = fd;
	m_pSockMgr = sockmgr;
	m_pLog = m_pDrebApi->GetLogPoint();
}

bool CS2SgeThread::Start()
{
	if (!m_bIsSetPara)
	{
		return false;
	}
	m_bIsRunning = true;
	CreateThread();
	return true;
}

void CS2SgeThread::Stop()
{
	m_bIsRunning = false;
//	printf("开始退出CS2SgeThread\n");
//	Join();
//	printf("结束退出CS2SgeThread\n");
}

void CS2SgeThread::ProcData(BPCCOMMSTRU &data)
{
//	t_butime = CBF_Date_Time::GetTickUS();

	if (!m_pGtpData.FromBuffer(data.sBuffer))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"线程序号[%d] 数据非GTP[%s]",m_nIndex,data.sBuffer);
		return;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"交易服务器请求  交易码[%d] GTP[%s] ",data.sDBHead.d_Dinfo.d_nServiceNo,data.sBuffer);
	if (data.sDBHead.d_Dinfo.d_nServiceNo == 70000030 || data.sDBHead.d_Dinfo.d_nServiceNo == 70000011)
	{
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"线程序号[%d] 取断点信息GTP[%s]",m_nIndex,data.sBuffer);
		//取断点信息
		GetBreakPoingInfo(data,&m_pGtpData);
		//可以发送回报等数据了
		return;
	}
	
	t_fieldtype=0;
	int ret = m_pGtpData.GetValueByName("X07",t_sRootId,t_fieldtype);
	if (ret<0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据无X07:ROOTID字段 线程序号[%d]",m_nIndex);
		return;
	}
	
	//查看是否有席位号，若无则增加
	ret = m_pGtpData.GetValueByName("M20",t_sseatid,t_fieldtype);
	if (ret<0)
	{
		m_pGtpData.SetDataItem("M20",m_pRes->m_sSeatNo.c_str());
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"GTP报文未设置席位代码m20,设为默认配置[%s]",m_pRes->m_sSeatNo.c_str());
	}
	//找到报盘机注册的交易码对应函数指针，调用
	
	if (!m_pFuncList->Select(data.sDBHead.d_Dinfo.d_nServiceNo,t_func))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易[%d]在报盘机中未注册 线程序号[%d]",data.sDBHead.d_Dinfo.d_nServiceNo,m_nIndex);
		return;
	}
	//将节点类型保存在此字段中
	data.sBpcHead.nBpcLen = atoi(t_func.pBuInstance->m_sNodeType.c_str());
	//保存报文头，供应答使用
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ROOTID[%s] index[%d] 线程序号[%d]",t_sRootId.c_str(),data.sBpcHead.nIndex,m_nIndex);
	if (!m_pMsgHead->Insert(t_sRootId.c_str(),data))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"保存报文头失败 【%s】 线程序号[%d]",data.sBuffer,m_nIndex);
		return;
	}

//	t_eutime = CBF_Date_Time::GetTickUS();
//	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"调动态库的发送前 耗时[%d]微秒",t_eutime-t_butime);

	try
	{
		ret = (t_func.pBuInstance->*(t_func.pFunc))(&m_pGtpData);
	}
	catch (...)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"调用动态库方法出错 [%s %s %d] 线程序号[%d]",t_func.sDllName,t_func.sFuncName,t_func.nFuncNo,m_nIndex);	
		return ;
	}
	if (ret <0)
	{
		//得到交易码
		char txcode[100];
		bzero(txcode,sizeof(txcode));
		int fieldtype=0;
		int nRet = m_pGtpData.GetValueByName("X03",txcode,fieldtype);
		if (nRet <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X03字段或类型不符 线程序号[%d]",m_nIndex);
			return;
		}
		txcode[3]='1';
		m_pGtpData.SetDataItem("X03",txcode);
		//发送失败  应答回去
		m_pGtpData.SetDataItem("X39",999999);
		m_pGtpData.SetDataItem("X40","发送给交易所失败，可能未连接未登录等系统错误");
		std::string gtpdata;
		m_pGtpData.ToString(gtpdata);
		strcpy(data.sBuffer,gtpdata.c_str());
		data.sDBHead.nLen= gtpdata.length();
		SendBack(data,999999,"发送给交易所出错");

		return;
	}
//	t_eutime = CBF_Date_Time::GetTickUS();
//	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"交易耗时[%d]微秒",t_eutime-t_butime);
	return ;
// 	//若是多个报盘机在一起，则根据交易码发至不同的动态库进行处理
// 	if (m_pSgeMgr->m_vApiDllClass->size() == 1)
// 	{
// 		m_pSgeMgr->m_vApiDllClass->at(0).apiPoint->SendMsg(&m_pGtpData);
// 	}
// 	else
// 	{
// 		
// 	}
}

void CS2SgeThread::DSP_2_HEX(const char *dsp,char *hex,int count)
{
    int i;
	int hexcount=count/2;
    for(i = 0; i < hexcount; i++)
    {
		hex[i]=((dsp[i*2]<=0x39)?dsp[i*2]-0x30:dsp[i*2]-0x41+10);
        hex[i]=hex[i]<<4;
		hex[i]+=((dsp[i*2+1]<=0x39)?dsp[i*2+1]-0x30:dsp[i*2+1]-0x41+10);
    }
	return;
} 

void CS2SgeThread::HEX_2_DSP(const char *hex,char *dsp,int count)
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
	return;
} 

void CS2SgeThread::GetBreakPoingInfo(BPCCOMMSTRU &data,CGtpData *gtpdata)
{
	//置断点标志
	m_pSockMgr->at(data.sBpcHead.nIndex)->m_nBpFlag = 1;

	std::vector<S_FLOW_INFO> bplist;
	//取断点数据发送
	int arrayrowid;
	int fieldtype=0;
	int nRet;
	//判断X20节点是否存在，这里要验证一下只解析一层时字段类型是否也解析了
	arrayrowid = gtpdata->GetRowId("X20",fieldtype);
	if (arrayrowid < 0 )
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据无X20断点信息 线程序号[%d]",m_nIndex);
		return;
	}
	if (fieldtype != GTP_DATATYPE_ARRAY)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据无X20不是数组类型 线程序号[%d]",m_nIndex);
		return;
	}
	//得到断点数组的类指针
	CGtpData *arraypoint = gtpdata->GetDataPoint("X20");
	if (arraypoint == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"数组节点为NULL， %d  线程序号[%d]",arrayrowid,m_nIndex);
		return;
	}
	//得到数组下面的hash表个数
	int fieldcount = arraypoint->FieldCount();
	std::string svalue;
	CGtpData *hashbp=NULL;
	S_FLOW_INFO  bpinfo;
	//循环取每个hash表的数据
	for (int i=0; i< fieldcount; i++)
	{
		bzero(&bpinfo,sizeof(S_FLOW_INFO));
		hashbp = arraypoint->GetDataPoint(i);
		nRet = hashbp->GetValueByName("X04",svalue,fieldtype);
		if (nRet <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP断点哈希表无X04字段或类型不符 %d",nRet);
			return;
		}
		bpinfo.nFlowNo = atoi(svalue.c_str());
		nRet = hashbp->GetValueByName("X05",svalue,fieldtype);
		if (nRet <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP断点哈希表无X05字段或类型不符 %d",nRet);
			return;
		}
		bpinfo.nMaxSerial = atol(svalue.c_str());
		//增加，当断点值小于0时不用取断点
		if (bpinfo.nMaxSerial >= 0)
		{
			//将一类消息放入断点列表
			bplist.push_back(bpinfo);
		}
	
	}
	//交给流文件类去取流信息发送
	m_pFlowData->GetFlowData(bplist,data,&m_pBpkvdata);
	if (data.sBpcHead.nBpuIndex == 1) //侦听过来的
	{
		m_pSockMgr->at(data.sBpcHead.nIndex)->m_nBpFlag = 0;
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"index[%d]断点完成 线程序号[%d]",data.sBpcHead.nIndex,m_nIndex);
	}
	return;
}

void CS2SgeThread::SendBack(BPCCOMMSTRU &data,int retcode,char *retmsg)
{
	
	if (data.sBpcHead.nBpuIndex == 1) //侦听过来的
	{
		S_OFFERING_DATA senddata;
		if (!m_pSockMgr->at(data.sBpcHead.nIndex)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送数据分配空间出错 线程序号[%d]",m_nIndex);
			return;
		}
		//组KV报文
// 		CKvData kvdata;
// 		kvdata.setPack("ApiName","onRcvGtpMsg");
// 		kvdata.setPack("TXCODE",data.sDBHead.d_Dinfo.d_nServiceNo);
// 
// 		kvdata.setPack("RspCode",retcode);
// 		kvdata.setPack("RspMsg",retmsg);
// //		kvdata.setPack("RspMsg",data.sBpcHead.nBpcLen);
// 		char tmpchar[11];
// 		sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
// 		kvdata.setPack("NodeID",tmpchar);
// 		kvdata.setPack("NodeType",data.sBpcHead.nBpcLen);
// 
// 		m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送返回 应答GTP报文",data.sBuffer,data.sDBHead.nLen);
// 		
// 		bzero(senddata.pData,data.sDBHead.nLen*2+1);
// 		HEX_2_DSP(data.sBuffer,senddata.pData,data.sDBHead.nLen);
// 		kvdata.setPack("GTPDATA",senddata.pData);
// 		std::string logins;
// 		if (!kvdata.ToString(logins))
// 		{
// 			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"应答发送 ToString出错 线程序号[%d]",m_nIndex);
// 			m_pSockMgr->at(data.sBpcHead.nIndex)->PoolFree(senddata.pData);
// 			return ;
// 		}
// 		
// 		strcpy(senddata.pData,logins.c_str());
// 		senddata.nWantlen = logins.length();


		memset(senddata.pData,0,MAX_OFFERINGDATA_LEN+20);
		char tmpchar[11];
		sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
		
		sprintf(senddata.pData,"ApiName=onRcvGtpMsg#TXCODE=%d#NodeID=%s#NodeType=%d#RspCode=%d#RspMsg=%s#GTPDATA=",\
			data.sDBHead.d_Dinfo.d_nServiceNo,tmpchar,data.sBpcHead.nBpcLen,\
			retcode,retmsg);
		unsigned int t_tmpdatalen = strlen(senddata.pData);
		
		HEX_2_DSP(data.sBuffer,senddata.pData+t_tmpdatalen,data.sDBHead.nLen);
		strcat(senddata.pData,"#");
		senddata.nWantlen = strlen(senddata.pData);

		//应答回去
		m_pSockMgr->at(data.sBpcHead.nIndex)->SendMsg(senddata,0);
	}
	else //总线过来的
	{
		m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"发送出错 应答GTP报文",data.sBuffer,data.sDBHead.nLen);
		
		S_BPC_RSMSG drebdata;
		drebdata.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
		if (drebdata.sMsgBuf== NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送数据分配空间出错");
			return;
		}
		//应答回去
		data.sDBHead.cRaflag = 1;
		data.sDBHead.cZip = 0;
		data.sDBHead.cCmd  = CMD_DPCALL;
		data.sDBHead.a_Ainfo.a_nRetCode = retcode;
		memcpy(&(drebdata.sMsgBuf->sDBHead),&(data.sDBHead),sizeof(DREB_HEAD));
		if (data.sDBHead.nLen>0)
		{
			memcpy(drebdata.sMsgBuf->sBuffer,data.sBuffer,data.sDBHead.nLen);
		}
		
		m_pDrebApi->SendMsg(drebdata);
	}
	
}

