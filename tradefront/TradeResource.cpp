// TradeResource.cpp: implementation of the CTradeResource class.
//
//////////////////////////////////////////////////////////////////////

#include "TradeResource.h"
#include "BF_Slist.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTradeResource::CTradeResource()
{
	g_bToExit = false;
	m_nSvrHostStatus = ARBSTATUS_UNKNOW;
	m_nTradeReportTime = 1; //定时上报为1秒
	m_log = NULL;
	g_nMaxConnectNum = 10;
	g_nListenOld = false;
	g_nListenPort = 9001;
	g_nHeartRun = 5;
	m_nArbMode = 0;
	g_nSendDrebBack = 0;
	g_nSendDrebQuotation = 0;
	g_nSendDrebNode  = 0;
	g_nSendBackLocalTrade =0;
	
}

CTradeResource::~CTradeResource()
{
	m_log = NULL;
}

bool CTradeResource::Init(const char *confile)
{
	bool bRet = CBF_DrebResource::Init(confile);
	if (!bRet)
	{
		return false;
	}
// 	g_lSvrTxList.push_back(ARB_SEND_CONTROL);//仲裁指定主机
// 	g_lSvrTxList.push_back(ARB_SEND_QUERY);//仲裁查询
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/XDP定义文件",false,m_sXdpDefineXml,false) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/XDP定义文件]未配置";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/上报仲裁时间",false,m_nTradeReportTime) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/上报仲裁时间]未配置";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/席位代码",false,m_sSeatNo,false) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/席位代码]未配置";
		return false;
	}
	
	if (m_pXml.GetNodeAttribute("/package/head/公共配置/席位代码",false,"usehead",false,m_nUseSeatNoPrefix) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/席位代码]未配置usehead属性，指明是否注册总线加前缀";
		return false;
	}
	if (m_nUseSeatNoPrefix == 1)
	{
		if (m_pXml.GetNodeAttribute("/package/head/公共配置/席位代码",false,"seatNoPrefix",false,m_nSeatNoPrefix) == NULL)
		{
			m_errMsg = "[/package/head/公共配置/席位代码]未配置seatNoPrefix属性";
			return false;
		}
	}
	


	std::string logouttime;
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/定时录出时间",false,logouttime) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/定时录出时间]未配置";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/流文件目录",false,m_sFlowFilePath) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/流文件目录]未配置";
	}
	
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/是否推送非本登录交易员的回报",false,g_nSendBackLocalTrade) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/是否推送非本登录交易员的回报]未配置";
		g_nSendBackLocalTrade=0;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/是否根据接收回报应答时间和发送请求时间断开连接",false,g_nIsDisconnectByTime) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/是否根据接收回报应答时间和发送请求时间断开连接]未配置";
		g_nIsDisconnectByTime=0;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/无数据断开时间",false,g_nSgeDisconnectTime) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/无数据断开时间]未配置";
		g_nSgeDisconnectTime=300;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/应答延迟时间",false,g_nAnsDelayTime) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/应答延迟时间]未配置";
		g_nAnsDelayTime = 20;
	}
	

	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/回报发送总线",false,g_nSendDrebBack) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/回报发送总线]未配置";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/行情发送总线",false,g_nSendDrebQuotation) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/行情发送总线]未配置";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/发送总线节点",false,g_nSendDrebNode) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/发送总线节点]未配置";
		return false;
	}
	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/行情发送",false,g_nSendQuotation) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/行情发送]未配置";
		return false;
	}


	CBF_Slist  slist;
	int ret = slist.FillSepString(logouttime);
	if (ret <1)
	{
		m_errMsg = "[/package/head/公共配置/定时录出时间]配置不符";
		return false;
	}
	int nlogouttime;
	std::string stmp;
	for (int i=0; i< ret ; i++)
	{
		stmp =  slist.GetAt(i);
		if (stmp.length() != 4)
		{
			continue;
		}
		nlogouttime = atoi(stmp.c_str());
		if (nlogouttime <1)
		{
			continue;
		}
		g_lLogoutTime.push_back(nlogouttime);
	}


// 	std::string rspfile;
// 	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/响应码文件",false,rspfile,false) == NULL)
// 	{
// 		m_errMsg = "[/package/head/公共配置/响应码文件]未配置";
// 		return false;
// 	}
// 	if (!m_pRspXml.FromFile(rspfile.c_str()))
// 	{
// 		m_errMsg = "[/package/head/公共配置/响应码文件]非xml文件";
// 		return false;
// 	}

	if (m_pXml.GetNodeValueByPath("/package/head/公共配置/主备仲裁",false,m_nArbMode) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/主备仲裁]未配置";
		return false;
	}
	if (m_nArbMode == 1)
	{
		g_lSvrTxList.push_back(ARB_SEND_CONTROL);//仲裁指定主机
		g_lSvrTxList.push_back(ARB_SEND_QUERY);//仲裁查询
	}
	
	if (m_pXml.GetNodeAttribute("/package/head/公共配置/兼容原侦听",false,"use",false,g_nListenOld) == NULL)
	{
		m_errMsg = "[/package/head/公共配置/兼容原侦听]未配置";
		return false;
	}
	if (1 == g_nListenOld)
	{
		if (m_pXml.GetNodeValueByPath("/package/head/公共配置/兼容原侦听/侦听端口",false,g_nListenPort) == NULL)
		{
			m_errMsg = "[/package/head/公共配置/兼容原侦听/侦听端口]未配置";
			return false;
		}
		if (g_nListenPort <1024 || g_nListenPort > 65534)
		{
			m_errMsg = "[/package/head/公共配置/兼容原侦听/侦听端口]配置非法";
			return false;
		}
		if (m_pXml.GetNodeValueByPath("/package/head/公共配置/兼容原侦听/最大连接数",false,g_nMaxConnectNum) == NULL)
		{
			m_errMsg = "[/package/head/公共配置/兼容原侦听/最大连接数]未配置";
			return false;
		}
#ifdef _WINDOWS
		if (g_nMaxConnectNum >60)
		{
			g_nMaxConnectNum = 60;
		}
#endif	
		if (g_nMaxConnectNum <10)
		{
			g_nMaxConnectNum = 10;
		}

		
		if (m_pXml.GetNodeValueByPath("/package/head/公共配置/兼容原侦听/通讯报文头长度",false,g_nHeadNum) == NULL)
		{
			m_errMsg = "[/package/head/公共配置/兼容原侦听/通讯报文头长度]未配置";
			return false;
		}
		

	}

	return true;
}
