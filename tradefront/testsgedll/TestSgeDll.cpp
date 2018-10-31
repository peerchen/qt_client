// TestSgeDll.cpp: implementation of the CTestSgeDll class.
//
//////////////////////////////////////////////////////////////////////

#include "TestSgeDll.h"
#ifdef _WINDOWS
#define   INT64PFM  "%I64d"
#else
#define   INT64PFM  "%lld"
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestSgeDll * getInstance() 
{ 
    return new CTestSgeDll(); 
}


CTestSgeDll::CTestSgeDll()
{
	m_nIsFlowRun =0;
	//在这里注册交易，将所有提供的交易都注册上，连接总线需要注册的
	m_nQuoSerail =0;

	m_nOrderNo=0;
	m_nDoneNo =0;
	m_bIsReadFile = false;
	
	//竞价交易接口
	AddFuncInfo("A130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交易员密码修改");
	AddFuncInfo("A320",(SgeFuncPointer)&CTestSgeDll::SendMsg,"应急密码修改");
	AddFuncInfo("B320",(SgeFuncPointer)&CTestSgeDll::SendMsg,"递延费率查询");
	AddFuncInfo("B340",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交易所状态查询");
	AddFuncInfo("T430",(SgeFuncPointer)&CTestSgeDll::SendMsg,"席位客户查询");
	AddFuncInfo("T440",(SgeFuncPointer)&CTestSgeDll::SendMsg,"席位持仓查询");
	AddFuncInfo("T450",(SgeFuncPointer)&CTestSgeDll::SendMsg,"席位资金查询");
	AddFuncInfo("T460",(SgeFuncPointer)&CTestSgeDll::SendMsg,"客户持仓查询");
	AddFuncInfo("T470",(SgeFuncPointer)&CTestSgeDll::SendMsg,"客户库存查询");
	AddFuncInfo("Q090",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交易实时行情查询");
	AddFuncInfo("Q100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交易分钟行情查询");
	AddFuncInfo("Q200",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交割实时行情");
	AddFuncInfo("Q900",(SgeFuncPointer)&CTestSgeDll::SendMsg,"公告发布");
	AddFuncInfo("Q910",(SgeFuncPointer)&CTestSgeDll::SendMsg,"公告发布");
	AddFuncInfo("Q900",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交易所公告查询");
	AddFuncInfo("T200",(SgeFuncPointer)&CTestSgeDll::SendMsg,"报单请求");
	AddFuncInfo("T210",(SgeFuncPointer)&CTestSgeDll::SendMsg,"撤单请求");
	AddFuncInfo("T230",(SgeFuncPointer)&CTestSgeDll::SendMsg,"报单查询");
	AddFuncInfo("T090",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交割申报");
	AddFuncInfo("T100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交割申报撤销");
	AddFuncInfo("T120",(SgeFuncPointer)&CTestSgeDll::SendMsg,"中立仓申报");
	AddFuncInfo("T130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"中立仓申报撤销");
	AddFuncInfo("T400",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交割申报报单查询");
	AddFuncInfo("T410",(SgeFuncPointer)&CTestSgeDll::SendMsg,"交割申报成交查询");
	AddFuncInfo("T420",(SgeFuncPointer)&CTestSgeDll::SendMsg,"中立仓申报报单查询");
	//资金仓储接口
	AddFuncInfo("F010",(SgeFuncPointer)&CTestSgeDll::SendMsg,"资金划拨");
	AddFuncInfo("F020",(SgeFuncPointer)&CTestSgeDll::SendMsg,"往来账查询");
	AddFuncInfo("F900",(SgeFuncPointer)&CTestSgeDll::SendMsg,"增加资金密码");
	AddFuncInfo("F910",(SgeFuncPointer)&CTestSgeDll::SendMsg,"修改资金密码");
	AddFuncInfo("F920",(SgeFuncPointer)&CTestSgeDll::SendMsg,"重置资金密码");
	AddFuncInfo("S000",(SgeFuncPointer)&CTestSgeDll::SendMsg,"增加提货申请");
	AddFuncInfo("S010",(SgeFuncPointer)&CTestSgeDll::SendMsg,"撤销提货申请");
	AddFuncInfo("S020",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提货申请查询");
	AddFuncInfo("S030",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提货密码重置");
	AddFuncInfo("S100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交质押申报");
	AddFuncInfo("S110",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交质押申报");
	AddFuncInfo("S120",(SgeFuncPointer)&CTestSgeDll::SendMsg,"质押申报查询");
	AddFuncInfo("S130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交质押注销申报");
	AddFuncInfo("S140",(SgeFuncPointer)&CTestSgeDll::SendMsg,"撤销质押注销申报");
	AddFuncInfo("S150",(SgeFuncPointer)&CTestSgeDll::SendMsg,"质押登记注销申报");
	AddFuncInfo("S160",(SgeFuncPointer)&CTestSgeDll::SendMsg,"质押登记注销申报");
	AddFuncInfo("S200",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交租借登记申报");
	AddFuncInfo("S210",(SgeFuncPointer)&CTestSgeDll::SendMsg,"撤销租借登记申报");
	AddFuncInfo("S220",(SgeFuncPointer)&CTestSgeDll::SendMsg,"租借登记申报查询");
	AddFuncInfo("S230",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交租借还金登记申报");
	AddFuncInfo("S240",(SgeFuncPointer)&CTestSgeDll::SendMsg,"撤销租借还金登记申报");
	AddFuncInfo("S250",(SgeFuncPointer)&CTestSgeDll::SendMsg,"租借还金申报查询");
	AddFuncInfo("S260",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交租借续租申报");
	AddFuncInfo("S270",(SgeFuncPointer)&CTestSgeDll::SendMsg,"撤销租借续租申报");
	AddFuncInfo("S280",(SgeFuncPointer)&CTestSgeDll::SendMsg,"租借续租申报查询");
	AddFuncInfo("S290",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交租借状态变更申报");
	AddFuncInfo("S300",(SgeFuncPointer)&CTestSgeDll::SendMsg,"租借状态变更申报查询");
	AddFuncInfo("S310",(SgeFuncPointer)&CTestSgeDll::SendMsg,"租借登记查询");
	AddFuncInfo("S320",(SgeFuncPointer)&CTestSgeDll::SendMsg,"租借还金登记查询");
	AddFuncInfo("S410",(SgeFuncPointer)&CTestSgeDll::SendMsg,"租借还金登记查询");
	AddFuncInfo("S420",(SgeFuncPointer)&CTestSgeDll::SendMsg,"库存划转查询");
	AddFuncInfo("S510",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交库存互换申报");
	AddFuncInfo("S520",(SgeFuncPointer)&CTestSgeDll::SendMsg,"提交库存互换申报");
	AddFuncInfo("S530",(SgeFuncPointer)&CTestSgeDll::SendMsg,"库存互换申报查询");
	AddFuncInfo("S540",(SgeFuncPointer)&CTestSgeDll::SendMsg,"库存互换登记查询");
	AddFuncInfo("S810",(SgeFuncPointer)&CTestSgeDll::SendMsg,"查询清算用库存变化流水");
	AddFuncInfo("S820",(SgeFuncPointer)&CTestSgeDll::SendMsg,"查询库存变化流水");
	AddFuncInfo("S840",(SgeFuncPointer)&CTestSgeDll::SendMsg,"查询库存变化流水");
	AddFuncInfo("S330",(SgeFuncPointer)&CTestSgeDll::SendMsg,"查询每日租借基准利率及均值");


	//黄金ETF
	AddFuncInfo("E000",(SgeFuncPointer)&CTestSgeDll::SendMsg,"账户备案/客户绑定");
	AddFuncInfo("E010",(SgeFuncPointer)&CTestSgeDll::SendMsg,"账户解绑定");
	AddFuncInfo("E020",(SgeFuncPointer)&CTestSgeDll::SendMsg,"账户备案业务本地编号查询");
	AddFuncInfo("E030",(SgeFuncPointer)&CTestSgeDll::SendMsg,"认购请求");
	AddFuncInfo("E050",(SgeFuncPointer)&CTestSgeDll::SendMsg,"申购请求");
	AddFuncInfo("E070",(SgeFuncPointer)&CTestSgeDll::SendMsg,"赎回请求");
	AddFuncInfo("E090",(SgeFuncPointer)&CTestSgeDll::SendMsg,"发送账户绑定结果请求");
	AddFuncInfo("E100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"发送认购确认通知请求");
	AddFuncInfo("E110",(SgeFuncPointer)&CTestSgeDll::SendMsg,"发送申赎清单系统控制版本请求");
	AddFuncInfo("E120",(SgeFuncPointer)&CTestSgeDll::SendMsg,"申赎清单查询请求");
	AddFuncInfo("E130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"认申赎交易本地编号查询");

	//账户卡
	AddFuncInfo("R000",(SgeFuncPointer)&CTestSgeDll::SendMsg,"自然人客户开户");
	AddFuncInfo("R010",(SgeFuncPointer)&CTestSgeDll::SendMsg,"自然人客户信息变更");
	AddFuncInfo("R020",(SgeFuncPointer)&CTestSgeDll::SendMsg,"自然人客户指定交易");
	AddFuncInfo("R030",(SgeFuncPointer)&CTestSgeDll::SendMsg,"自然人客户指定交易撤销");
	AddFuncInfo("R040",(SgeFuncPointer)&CTestSgeDll::SendMsg,"客户销户请求");
	AddFuncInfo("R050",(SgeFuncPointer)&CTestSgeDll::SendMsg,"客户信息查询请求");
	AddFuncInfo("R100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"机构客户开户申请请求");
	AddFuncInfo("R110",(SgeFuncPointer)&CTestSgeDll::SendMsg,"机构客户信息变更申请");
	AddFuncInfo("R120",(SgeFuncPointer)&CTestSgeDll::SendMsg,"机构客户指定交易申请");
	AddFuncInfo("R130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"机构客户指定交易撤销申请");
	AddFuncInfo("R140",(SgeFuncPointer)&CTestSgeDll::SendMsg,"机构客户销户申请请求");
	AddFuncInfo("R150",(SgeFuncPointer)&CTestSgeDll::SendMsg,"机构客户信息查询请求");


	//推送客户库存变化流水  S802
	//推送申报状态变化流水  S832
	
	//市场信息回报（现货/延期/即期）     B002
	//市场状态改变回报（现货/延期/即期） B062
	//合约信息回报（现货/延期/即期）     B102 
	//合约交易状态改变回报（现货/延期/即期） B182
	//交割品种代码信息回报                 B202
	//发布现货延期交收补偿费率通知         B302
	//发布交易所状态通知                   B332
	//交易实时行情（现货/延期/即期）       Q012
	//交割实时行情                         Q202
	//公告发布请求与应答及回报             Q902
	//报单请求及应答及回报（现货/延期/即期）T202
	//撤单请求及应答及回报（现货/延期/即期）T212
	//成交回报（现货/延期/即期）            T222
	//交割申报请求及应答及回报              T092
	//交割申报撤销请求及应答及回报          T102
	//交割申报成交回报                      T112
	//中立仓申报请求及应答及回报            T122
	//中立仓申报撤销请求及应答及回报        T132
	
	
	//认购确认通知                          E042
	//申购请求及应答及回报                  E052
	//申购确认通知                          E062
	//赎回确认通知                          E082
	
	
	//自然人客户基础信息变更通知            R062
	//机构客户开户申请请求及应答、复核通知  R102
	//机构客户信息变更申请请求及应答、复核通知  R112
	//机构客户指定交易申请请求及应答、复核通知  R122
	//机构客户指定交易撤销申请请求及应答、复核通知  R132
	//机构客户销户申请请求及应答、复核通知 R142
	//机构客户基础信息变更通知             R162
	m_backIndex.Add(0,"S802");
	m_backIndex.Add(0,"S832");
	m_backIndex.Add(0,"B002");
	m_backIndex.Add(0,"B062");
	m_backIndex.Add(0,"B102");
	m_backIndex.Add(0,"B182");
	m_backIndex.Add(0,"B202");
	m_backIndex.Add(0,"B302");
	m_backIndex.Add(0,"B332");
	m_backIndex.Add(0,"Q012");
	m_backIndex.Add(0,"Q202");
	m_backIndex.Add(0,"Q902");
	m_backIndex.Add(0,"T202");
	m_backIndex.Add(0,"T212");
	m_backIndex.Add(0,"T222");
	m_backIndex.Add(0,"T092");
	m_backIndex.Add(0,"T102");
	m_backIndex.Add(0,"T112");
	m_backIndex.Add(0,"T122");
	m_backIndex.Add(0,"T132");
	m_backIndex.Add(0,"E042");
	m_backIndex.Add(0,"E052");
	m_backIndex.Add(0,"E062");
	m_backIndex.Add(0,"E082");
	m_backIndex.Add(0,"R062");
	m_backIndex.Add(0,"R102");
	m_backIndex.Add(0,"R112");
	m_backIndex.Add(0,"R122");
	m_backIndex.Add(0,"R132");
	m_backIndex.Add(0,"R142");
	m_backIndex.Add(0,"R162");

}

CTestSgeDll::~CTestSgeDll()
{
	
}
// 函数名: StartApi
// 编程  : 王明松 2016-3-11 16:31:55
// 返回  : virtual bool 
// 描述  : 开始API    建立连接，启动日志
bool CTestSgeDll::StartApi()
{
	//初始化
	//建立连接
	m_nConnectTime = time(NULL);
	//启动api线程

	//模拟连接成功
	api_connection_state_t constatus;
	strcpy(constatus.ip,"127.0.0.1");
	constatus.port = 9011;
	constatus.state = IS_CONNECTED;
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"模拟连接SGE前置");
	m_apiPoint->apistruct->cb_.api_cb_connected_(&constatus,m_apiPoint->apistruct);

	m_pTimer.Start();
	if (m_nIsFlowRun == 1)
	{
		m_bIsRunning = true;
		CreateThread();
	}
	m_nSendReqTime = time(NULL);
	m_nRcvBackTime = time(NULL);
	m_nRcvAnsTime = time(NULL);
	return true;
}


// 函数名: StopApi
// 编程  : 王明松 2016-3-11 16:32:06
// 返回  : virtual bool 
// 描述  : 断开连接，停止api，停止日志
bool CTestSgeDll::StopApi()
{
	m_pTimer.Stop();
	m_pTimer.Join();
	m_bIsRunning = false;
	Join();
	return true;
}

// 函数名: Init
// 编程  : 王明松 2016-3-11 11:29:23
// 返回  : virtual bool 
// 输入输出参数  : S_SGE_GEMS2_API *api  api指针，包含回调方法、api的handle和ca的handle
// 输入参数  : CIErrlog *log     日志指针，给继承写日志
// 输入参数  : CBF_Xml *xml      配置语言的xml类
// 输入参数  : const char *xmlnode  本动态库对应的xml配置节点，见上面说明
// 输出参数  : char *errmsg  出错信息
// 描述  : 初始化
bool CTestSgeDll::Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg)
{
	bool bRet = CIOfferingBase::Init(api,log,xml,xmlnode,errmsg);
	if (!bRet)
	{
		return bRet;
	}
	//在这里做其它的初始化
	char nodename[100];
	sprintf(nodename,"%s/模拟档板目录",xmlnode);
	if (xml->GetNodeValueByPath(nodename,false,m_sTestDir,false) == NULL)
	{
		sprintf(errmsg,"XML节点[%s]不存在",nodename);
		return false;
	}
	sprintf(nodename,"%s/模拟交易日期",xmlnode);
	if (xml->GetNodeValueByPath(nodename,false,m_sTestTxDate,false) == NULL)
	{
		sprintf(errmsg,"XML节点[%s]不存在",nodename);
		return false;
	}
	sprintf(nodename,"%s/报单压力测试",xmlnode);
	if (xml->GetNodeValueByPath(nodename,false,m_sOrderPmt,false) == NULL)
	{
		sprintf(errmsg,"XML节点[%s]不存在",nodename);
		return false;
	}

	sprintf(nodename,"%s/模拟行情",xmlnode);
	CXmlNode *testquonode = xml->GetNodeByPath(nodename);
	if (testquonode == NULL)
	{
		sprintf(errmsg,"XML节点[%s]不存在",nodename);
		return false;
	}
	CXmlNode *quonode = (CXmlNode *)testquonode->GetFirstChild();
	CXmlAttribute *attr=NULL;
	S_TEST_QUO squo;
	while (quonode != NULL)
	{
		
		attr = quonode->GetAttribute("定时间隔");
		if (attr == NULL)
		{
			m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"无[定时间隔]属性");
			quonode = (CXmlNode *)quonode->getNextSibling();
			continue;
		}
		squo.nTime = atoi(attr->GetAttrValue().c_str());
		attr = quonode->GetAttribute("行情文件");
		if (attr == NULL)
		{
			m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"无[行情文件]属性");
			quonode = (CXmlNode *)quonode->getNextSibling();
			continue;
		}
		squo.sQuoFile = attr->GetAttrValue();
		m_vTestQuo.push_back(squo);
		S_QUOSTRUCT aa;
		aa.m_bIsReadQuoFile = false;
		m_vTestQuoGtp.push_back(aa);

		quonode = (CXmlNode *)quonode->getNextSibling();
	}
	m_pTimer.Init(1000);
	for (int i=0;i<m_vTestQuo.size();i++)
	{
		m_pTimer.SetTimer(i,m_vTestQuo[i].nTime*1000,&CTestSgeDll::OnTimer,this);
	}
	
	sprintf(nodename,"%s/流文件重演",xmlnode);
	if (xml->GetNodeAttribute(nodename,false,"use",false,m_nIsFlowRun) == NULL)
	{
		sprintf(errmsg,"XML节点[%s]不存在",nodename);
		m_nIsFlowRun = 0;
	}
	if (m_nIsFlowRun == 1)
	{
		std::string flowfilepath;
		if (xml->GetNodeAttribute(nodename,false,"流文件目录",false,flowfilepath,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]的属性[流文件目录]未配置",nodename);
			return false;
		}
		S_FLOWFILE_INFO info;
		CXmlNode *flownode = xml->GetNodeByPath(nodename,false);
		if (flownode == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		flownode = (CXmlNode *)flownode->GetFirstChild();
		if (flownode == NULL)
		{
			sprintf(errmsg,"XML节点[%s]的子节点为空，即流文件未配置",nodename);
			return false;
		}
		std::string flowfilename;
		while (flownode != NULL)
		{
			info.pFlowFp = NULL;
			bzero(info.flowflename,sizeof(info.flowflename));
			flowfilename = flownode->GetNodeValue(false);
			if (flowfilename.length()<1)
			{
				sprintf(errmsg,"XML节点[%s]的子节点为的值为空，即位配置流文件名",nodename);
				return false;
			}
			sprintf(info.flowflename,"%s/%s",flowfilepath.c_str(),flowfilename.c_str());
			m_pFlowList.push_back(info);
			flownode = (CXmlNode *)flownode->getNextSibling();
		}
	}
	

	

	return true;
}


// 函数名:  SendMsg
// 编程  : 王明松 2016-3-11 11:34:50
// 返回  : virtual int 
// 参数  : const char *gtpmsg  gtp消息不含定长数据
// 参数  : unsigned short gtplen
// 描述  : 发送业务数据
int  CTestSgeDll::SendMsg(CGtpData *senddata)
{
	CBF_PMutex  pp(&m_mutex);
	//测试返回
	t_btime = CBF_Date_Time::GetTickUS();
	std::string smsgtype ;
	int fieldtype;
	if (senddata->GetValueByName("X03",smsgtype,fieldtype)<0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"无X03字段");
		return -1;
	}
	char stxcode[10];
	strcpy(stxcode,smsgtype.c_str());
	stxcode[3] = '1';
	char tmpchar[200];
	
	//先应答
	
	UINT64_ msgserial = 0;

	

	
	if (m_sOrderPmt.compare("1") == 0 && smsgtype.compare("T200") ==0 ) //报单压力测试
	{
		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"模拟发送 进入报单压力测试前耗时[%d]微秒",t_etime-t_btime);
		std::string sorderNo;
		char  cOrderNo[100];
		char  cDoneNo[100];
		std::string sDoneNo;
		UINT64_ doneserial = 0;
		if (!m_bIsReadFile)
		{
			if (m_sTestDir.length()>0)
			{
				sprintf(tmpchar,"%s/%s.txt",m_sTestDir.c_str(),"T201");
			}
			else
			{
				sprintf(tmpchar,"%s.txt","T201");
			}
			if (!m_pOrderAns.FromFile(tmpchar)) //读取文件里的内容返回
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"文件[%s]不存在",tmpchar);
				senddata->SetDataItem("X40","报盘机档板模拟应答返回，非文件档板返回");//响应信息
				return -1;
			}
			if (m_pOrderAns.GetValueByName("O00",sorderNo,fieldtype) >= 0)
			{
				msgserial = ATOI64(sorderNo.c_str());
			}
			
			if (m_nOrderNo< msgserial)
			{
				m_nOrderNo = msgserial;
			}

			if (m_sTestDir.length()>0)
			{
				sprintf(tmpchar,"%s/%s.txt",m_sTestDir.c_str(),"T202");
			}
			else
			{
				sprintf(tmpchar,"%s.txt","T202");
			}
			if (!m_pOrderBack.FromFile(tmpchar)) //读取文件里的内容返回
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"文件[%s]不存在",tmpchar);
				senddata->SetDataItem("X40","报盘机档板模拟应答返回，非文件档板返回");//响应信息
				return -1;
			}
			if (m_sTestDir.length()>0)
			{
				sprintf(tmpchar,"%s/%s.txt",m_sTestDir.c_str(),"T222");
			}
			else
			{
				sprintf(tmpchar,"%s.txt","T222");
			}
			if (!m_pOrderDone.FromFile(tmpchar)) //读取文件里的内容返回
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"文件[%s]不存在",tmpchar);
				senddata->SetDataItem("X40","报盘机档板模拟应答返回，非文件档板返回");//响应信息
				return -1;
			}
			if (m_pOrderDone.GetValueByName("O60",sDoneNo,fieldtype) >= 0)
			{
				doneserial = ATOI64(sDoneNo.c_str());
			}
			
			if (m_pOrderDone.GetValueByName("O09",m_sDoneStatus,fieldtype) >= 0)
			{
				m_sDoneStatus = "c";
			}
			
			if (m_nDoneNo< doneserial)
			{
				m_nDoneNo = doneserial;
			}
			m_bIsReadFile = true;
			t_etime = CBF_Date_Time::GetTickUS();
			m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"模拟发送 进入读配置文件耗时[%d]微秒",t_etime-t_btime);

		}

		senddata->SetDataItem("X03","T201");
		m_nOrderNo++;
		sprintf(cOrderNo,INT64PFM,m_nOrderNo);
		senddata->SetDataItem("O00",cOrderNo);
		senddata->UpdateCurValue(&m_pOrderAns,false);
		senddata->SetDataItem("T11",m_sTestTxDate.c_str());
		senddata->SetDataItem("O61",m_sTestTxDate.c_str());

	
		
		t_sgtpdata ="";
		senddata->ToString(t_sgtpdata);

		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟应答 [%s]",t_sgtpdata.c_str());

		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"模拟发送 应答api_recv_msg_前耗时[%d]微秒",t_etime-t_btime);
	
		m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
		
		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"模拟发送 处理应答后耗时[%d]微秒",t_etime-t_btime);


		//报单请求及应答及回报（现货/延期/即期）T202
		
		senddata->SetDataItem("X03","T202");
		senddata->SetDataItem("O00",cOrderNo);
		senddata->UpdateCurValue(&m_pOrderBack,false);
		
		senddata->SetDataItem("T11",m_sTestTxDate.c_str());
		senddata->SetDataItem("O61",m_sTestTxDate.c_str());
		
		t_sgtpdata ="";
		senddata->ToString(t_sgtpdata);
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟回报 [%s]",t_sgtpdata.c_str());

		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"模拟发送 回报api_recv_msg_前耗时[%d]微秒",t_etime-t_btime);

		m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
		
		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"模拟发送 处理回报后耗时[%d]微秒",t_etime-t_btime);
		//成交回报（现货/延期/即期）            T222
		

		senddata->SetDataItem("X03","T222");
		senddata->SetDataItem("O00",cOrderNo);
		
		m_nDoneNo++;
		sprintf(cDoneNo,INT64PFM,m_nDoneNo);
		//成交编号
		senddata->SetDataItem("O60",cDoneNo);

		//报单数量
		int ordernum=1;
		if (senddata->GetValueByName("O07",sDoneNo,fieldtype) >= 0)
		{
			ordernum = atoi(sDoneNo.c_str());
		}
		
		//成交数量
		senddata->SetDataItem("O64",ordernum);
		senddata->UpdateCurValue(&m_pOrderDone,false);

		//成交状态，因回报中已有，要重置
		senddata->SetDataItem("O09",m_sDoneStatus);
		
		senddata->SetDataItem("T11",m_sTestTxDate.c_str());
		senddata->SetDataItem("O61",m_sTestTxDate.c_str());
		t_sgtpdata ="";
		senddata->ToString(t_sgtpdata);
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟成交回报 [%s]",t_sgtpdata.c_str());

		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"模拟发送 应答api_recv_msg_前耗时[%d]微秒",t_etime-t_btime);
	
		m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
		
		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"模拟发送 处理成交回报后耗时[%d]微秒",t_etime-t_btime);

		return 0;
	}
	CGtpData fdata;
	std::string sorderNo;
	char  cOrderNo[100];


	if (m_sTestDir.length()>0)
	{
		sprintf(tmpchar,"%s/%s.txt",m_sTestDir.c_str(),stxcode);
	}
	else
	{
		sprintf(tmpchar,"%s.txt",stxcode);
	}

	if (!fdata.FromFile(tmpchar)) //读取文件里的内容返回
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"文件[%s]不存在",tmpchar);
		senddata->SetDataItem("X40","报盘机档板模拟应答返回，非文件档板返回");//响应信息
	}
	else
	{
		senddata->SetDataItem("X03",stxcode);
		
		if (fdata.GetValueByName("O00",sorderNo,fieldtype) >= 0)
		{
			msgserial = ATOI64(sorderNo.c_str());
		}
		
		if (m_nOrderNo< msgserial)
		{
			m_nOrderNo = msgserial;
		}
		m_nOrderNo++;
		sprintf(cOrderNo,INT64PFM,m_nOrderNo);
		senddata->SetDataItem("O00",cOrderNo);
		senddata->UpdateCurValue(&fdata,false);
	}
	senddata->SetDataItem("T11",m_sTestTxDate.c_str());
	senddata->SetDataItem("O61",m_sTestTxDate.c_str());


	
	
	t_sgtpdata="";
	senddata->ToString(t_sgtpdata);
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟应答 [%s]",t_sgtpdata.c_str());
	m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
	
	//再判断是否需要回报，若回报则从文件读返回

	stxcode[3] = '2';

	if (m_sTestDir.length()>0)
	{
		sprintf(tmpchar,"%s/%s.txt",m_sTestDir.c_str(),stxcode);
	}
	else
	{
		sprintf(tmpchar,"%s.txt",stxcode);
	}
	
	//推送客户库存变化流水  S802
	//推送申报状态变化流水  S832

	//市场信息回报（现货/延期/即期）     B002
	//市场状态改变回报（现货/延期/即期） B062
	//合约信息回报（现货/延期/即期）     B102 
	//合约交易状态改变回报（现货/延期/即期） B182
	//交割品种代码信息回报                 B202
	//发布现货延期交收补偿费率通知         B302
	//发布交易所状态通知                   B332
	//交易实时行情（现货/延期/即期）       Q012
	//交割实时行情                         Q202
	//公告发布请求与应答及回报             Q902
	//报单请求及应答及回报（现货/延期/即期）T202
	//撤单请求及应答及回报（现货/延期/即期）T212
	//成交回报（现货/延期/即期）            T222
	//交割申报请求及应答及回报              T092
	//交割申报撤销请求及应答及回报          T102
	//交割申报成交回报                      T112
	//中立仓申报请求及应答及回报            T122
	//中立仓申报撤销请求及应答及回报        T132


	//认购确认通知                          E042
	//申购请求及应答及回报                  E052
	//申购确认通知                          E062
	//赎回确认通知                          E082


	//自然人客户基础信息变更通知            R062
	//机构客户开户申请请求及应答、复核通知  R102
	//机构客户信息变更申请请求及应答、复核通知  R112
	//机构客户指定交易申请请求及应答、复核通知  R122
	//机构客户指定交易撤销申请请求及应答、复核通知  R132
	//机构客户销户申请请求及应答、复核通知 R142
	//机构客户基础信息变更通知             R162
	if (!m_backIndex.Find(stxcode))
	{
		return 1;
	}
	if (!fdata.FromFile(tmpchar)) //读取文件里的内容返回
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"文件[%s]不存在",tmpchar);
		senddata->SetDataItem("X40","报盘机档板模拟回报返回，非文件档板返回");//响应信息
	}
	else
	{
		senddata->SetDataItem("X03",stxcode);
		senddata->SetDataItem("O00",cOrderNo);
		senddata->UpdateCurValue(&fdata,false);
	}
	senddata->SetDataItem("T11",m_sTestTxDate.c_str());
	senddata->SetDataItem("O61",m_sTestTxDate.c_str());
	
	t_sgtpdata="";
	senddata->ToString(t_sgtpdata);
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟回报 [%s]",t_sgtpdata.c_str());
	m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
	

	
	//再判断是否需要成交回报，若回报则从文件读返回
	//报单请求及应答及回报（现货/延期/即期）T202
	//撤单请求及应答及回报（现货/延期/即期）T212
	//成交回报（现货/延期/即期）            T222
	//交割申报请求及应答及回报              T092
	//交割申报撤销请求及应答及回报          T102
	//交割申报成交回报                      T112
	if (smsgtype.compare("T200") == 0)
	{
		strcpy(stxcode,"T222");
	}
	else  if (smsgtype.compare("T090") == 0)
	{
		strcpy(stxcode,"T112");
	}
	else 
	{
		return 0;
	}
	if (m_sTestDir.length()>0)
	{
		sprintf(tmpchar,"%s/%s.txt",m_sTestDir.c_str(),stxcode);
	}
	else
	{
		sprintf(tmpchar,"%s.txt",stxcode);
	}

	char  cDoneNo[100];
	std::string sDoneNo;
	UINT64_ doneserial = 0;

	if (!fdata.FromFile(tmpchar)) //读取文件里的内容返回
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"文件[%s]不存在",tmpchar);
		senddata->SetDataItem("X40","报盘机档板模拟回报返回，非文件档板返回");//响应信息
		return 0;
	}
	else
	{
		senddata->SetDataItem("X03",stxcode);
		senddata->SetDataItem("O00",cOrderNo);
		if (fdata.GetValueByName("O60",sDoneNo,fieldtype) >= 0)
		{
			doneserial = ATOI64(sDoneNo.c_str());
		}
		
		if (m_nDoneNo< doneserial)
		{
			m_nDoneNo = doneserial;
		}
		m_nDoneNo++;
		sprintf(cDoneNo,INT64PFM,m_nDoneNo);
		//成交编号
		senddata->SetDataItem("O60",cDoneNo);

		//报单数量
		int ordernum=1;
		if (senddata->GetValueByName("O07",sDoneNo,fieldtype) >= 0)
		{
			ordernum = atoi(sDoneNo.c_str());
		}
		
		//成交数量
		senddata->SetDataItem("O64",ordernum);
		senddata->UpdateCurValue(&fdata,false);
	}
	senddata->SetDataItem("T11",m_sTestTxDate.c_str());
	senddata->SetDataItem("O61",m_sTestTxDate.c_str());
	
	t_sgtpdata="";
	senddata->ToString(t_sgtpdata);
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟成交回报 [%s]",t_sgtpdata.c_str());
	m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
	

	return 0;
}

// 函数名: CB_Connected
// 编程  : 王明松 2016-3-11 15:44:49
// 返回  : virtual bool 
// 参数  : api_connection_state_t * cs   连接状态
// 参数  : S_SGE_GEMS2_API_STRUCT *ctx   api参数
// 描述  : API的回调方法，连接成功了，要在里面发登录
bool CTestSgeDll::CB_Connected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
{
	bool bRet = CIOfferingBase::CB_Connected(cs,ctx);
	if (!bRet)
	{
		return bRet;
	}
	return true;
}

// 函数名: CB_Disconnected
// 编程  : 王明松 2016-3-11 15:44:43
// 返回  : virtual bool 
// 参数  : api_connection_state_t * cs
// 参数  : S_SGE_GEMS2_API_STRUCT *ctx
// 描述  : api回调方法 断开连接了  要释放api环境，以备再次连接
bool CTestSgeDll::CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
{
	bool bRet = CIOfferingBase::CB_Disconnected(cs,ctx);
	if (!bRet)
	{
		return bRet;
	}
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
		m_apiPoint->apistruct->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),m_apiPoint->apistruct);
	}
	return true;
}

// 函数名: Uncrypt
// 编程  : 王明松 2016-3-11 16:29:31
// 返回  : virtual bool 
// 参数  : S_SGE_GEMS2_API_STRUCT *ctx  api参数
// 参数  : const char *cryptmsg         待解密的数据
// 参数  : int msglen                   待解密的数据长度
// 参数  : char *gtpmsg                 解密后的数据
// 参数  : int &gtpmsglen               解密后的数据长度
// 描述  : 解密
bool CTestSgeDll::Uncrypt(S_SGE_GEMS2_API_STRUCT *ctx,const char *cryptmsg,int msglen,char *gtpmsg,int &gtpmsglen)
{
	return true;
}
void CTestSgeDll::TradeLogout()
{

}
// 函数名: TradeLogin
// 编程  : 王明松 2016-4-14 14:21:55
// 返回  : virtual void 
// 描述  : 交易员登录
void CTestSgeDll::TradeLogin()
{
	//通过断点组GTP登录报文
	CGtpData gtpdata;

	m_nLoginNum++;

	gtpdata.SetDataItem("X01","GTP1.0");//GTP版本
	gtpdata.SetDataItem("X02",0);//长度
	if (m_sNodeType.compare("12") == 0)  //etf
	{
		gtpdata.SetDataItem("X03","A300");//消息类型
	}
	else
	{
		gtpdata.SetDataItem("X03","A100");//消息类型
	}
	
	gtpdata.SetDataItem("X04","0");//序列类别号
	gtpdata.SetDataItem("X05","0");//消息序列号
	gtpdata.SetDataItem("X06","L");//消息的连续标志
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08","send");//发送方标识符
	gtpdata.SetDataItem("X09","recv");//接收方标识符

	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//交易员代码
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位号

	gtpdata.SetDataItem("M62","xxxx");//登录密码
	gtpdata.SetDataItem("X50","127.0.0.1");//ip地址
	gtpdata.SetDataItem("X55","v1.0");//API版本信息
 	gtpdata.SetDataItem("X20","1");//断点信息
 	gtpdata.SetDataItem("X80","1");//安全信息域
 	gtpdata.SetDataItem("X81","1");//安全信息域长度
	gtpdata.SetDataItem("T13",m_sTestTxDate.c_str());//交易日期
	//回调登录的响应
	
	if (m_sNodeType.compare("12") == 0)  //etf
	{
		gtpdata.SetDataItem("X03","A301");//消息类型
	}
	else
	{
		gtpdata.SetDataItem("X03","A101");//消息类型
	}
	CBF_Date_Time pdata;
	
	
	gtpdata.SetDataItem("O14","1");//最大本地报单号
	gtpdata.SetDataItem("X39","RSP000000");//响应代码
	gtpdata.SetDataItem("X40","报盘机档板模拟交易员登录返回");//响应信息

	//改为从文件读取返回 
	CGtpData fdata;
	char tmpchar[200];


	if (m_sTestDir.length()>0)
	{
		if (m_sNodeType.compare("12") == 0)  //etf
		{
			sprintf(tmpchar,"%s/%s",m_sTestDir.c_str(),"A301.txt");
		}
		else
		{
			sprintf(tmpchar,"%s/%s",m_sTestDir.c_str(),"A101.txt");
		}
	}
	else
	{
		if (m_sNodeType.compare("12") == 0)  //etf
		{
			sprintf(tmpchar,"%s","A301.txt");
		}
		else
		{
			sprintf(tmpchar,"%s","A101.txt");
		}
	}

	if (!fdata.FromFile(tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"%s文件不存在",tmpchar);
		gtpdata.SetDataItem("X40","报盘机档板模拟交易员登录返回，非文件档板返回");//响应信息
	}
	else
	{
		gtpdata.UpdateCurValue(&fdata,false);
	}

	std::string sgtpdata;
	gtpdata.ToString(sgtpdata);
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟交易员登录 [%s]",sgtpdata.c_str());
	m_apiPoint->apistruct->cb_.api_recv_msg_(sgtpdata.c_str(),GTP_TYPE_STRING,sgtpdata.length(),m_apiPoint->apistruct);
	m_nApiLoginStatus =1;
	
	return;
}
	

int CTestSgeDll::OnTimer(unsigned int eventid,void *p)
{
	CTestSgeDll *pp = (CTestSgeDll *)p;
	pp->SendQuotation(eventid);
	return 0;
}

void CTestSgeDll::SendQuotation(unsigned int id)
{
	CBF_PMutex pp(&m_mutex);
	//改为从文件读取返回 
	CGtpData fdata;
	char tmpchar[200];
	int fieldtype;
	std::string sdatastr;
	int nRet=0;
	int msgserial=0;
	std::string sgtpdata;
	int quonum=0;
	if (m_sTestDir.length()>0)
	{
		sprintf(tmpchar,"%s/%s",m_sTestDir.c_str(),m_vTestQuo[id].sQuoFile.c_str());
	}
	else
	{
		sprintf(tmpchar,"%s",m_vTestQuo[id].sQuoFile.c_str());
	}
	if (m_sOrderPmt.compare("1") == 0)
	{
		if (!m_vTestQuoGtp[id].m_bIsReadQuoFile)
		{
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"模拟行情，文件[%s]开始解析",tmpchar);
			if (!m_vTestQuoGtp[id].quodata.FromFile(tmpchar))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"模拟行情，%s文件不存在",tmpchar);
				return;
			}
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"模拟行情，文件[%s]解析完成",tmpchar);
			m_vTestQuoGtp[id].m_bIsReadQuoFile = true;
			nRet = m_vTestQuoGtp[id].quodata.GetValueByName("X05",sdatastr,fieldtype);
			if (nRet <0)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X05 消息序列号字段或类型不符");
				return ;
			}
			msgserial = atol(sdatastr.c_str());
			if (m_nQuoSerail< msgserial)
			{
				m_nQuoSerail = msgserial;
			}
		}
		
		m_nQuoSerail++;
		m_vTestQuoGtp[id].quodata.SetDataItem("X05",m_nQuoSerail);
		
		CGtpData *quogtp = m_vTestQuoGtp[id].quodata.GetDataPoint("Q52");
		if (quogtp == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"行情无Q52字段，即无Q52数组");
			sgtpdata = "";
			m_vTestQuoGtp[id].quodata.ToString(sgtpdata);
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟发送非行情 [%s]",sgtpdata.c_str());
			m_apiPoint->apistruct->cb_.api_recv_msg_(sgtpdata.c_str(),GTP_TYPE_STRING,sgtpdata.length(),m_apiPoint->apistruct);
			return ;
		}
		quonum = quogtp->FieldCount();
		CGtpData *quo=NULL;
		for (int kk=0; kk<quonum; kk++)
		{
			quo = quogtp->GetDataPoint(kk);
			quo->SetDataItem("T80",m_nQuoSerail);
			m_nQuoSerail++;
		}
		
		sgtpdata="";
		m_vTestQuoGtp[id].quodata.ToString(sgtpdata);
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟发送行情 [%s]",sgtpdata.c_str());
		m_apiPoint->apistruct->cb_.api_recv_msg_(sgtpdata.c_str(),GTP_TYPE_STRING,sgtpdata.length(),m_apiPoint->apistruct);
		return;
	}


	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"模拟行情，文件[%s]开始解析",tmpchar);
	if (!fdata.FromFile(tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"模拟行情，%s文件不存在",tmpchar);
		return;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"模拟行情，文件[%s]解析完成",tmpchar);
	
	nRet = fdata.GetValueByName("X05",sdatastr,fieldtype);
	if (nRet <0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP数据包无X05 消息序列号字段或类型不符");
		return ;
	}
	msgserial = atol(sdatastr.c_str());
	if (m_nQuoSerail< msgserial)
	{
		m_nQuoSerail = msgserial;
	}
	m_nQuoSerail++;
	fdata.SetDataItem("X05",m_nQuoSerail);
//	std::string sgtpdata;
	CGtpData *quogtp = fdata.GetDataPoint("Q52");
	if (quogtp == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"行情无Q52字段，即无Q52数组");
		fdata.ToString(sgtpdata);
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟发送非行情 [%s]",sgtpdata.c_str());
		m_apiPoint->apistruct->cb_.api_recv_msg_(sgtpdata.c_str(),GTP_TYPE_STRING,sgtpdata.length(),m_apiPoint->apistruct);
		return ;
	}
	quonum = quogtp->FieldCount();
	CGtpData *quo=NULL;
	for (int kk=0; kk<quonum; kk++)
	{
		quo = quogtp->GetDataPoint(kk);
		quo->SetDataItem("T80",m_nQuoSerail);
		m_nQuoSerail++;
	}
	
	
	fdata.ToString(sgtpdata);
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"开始模拟发送行情 [%s]",sgtpdata.c_str());
	m_apiPoint->apistruct->cb_.api_recv_msg_(sgtpdata.c_str(),GTP_TYPE_STRING,sgtpdata.length(),m_apiPoint->apistruct);
	return;
}
int CTestSgeDll::Run()
{
	SLEEP_SECONDS(1);
	int nRet=0;
	int datalen =0;
	BPCCOMMSTRU data;
	int i=0;
	for (i=0; i< m_pFlowList.size() ; i++)
	{
		if (m_pFlowList[i].pFlowFp == NULL)
		{
			m_pFlowList[i].pFlowFp = fopen(m_pFlowList[i].flowflename,"rb");
			if (m_pFlowList[i].pFlowFp == NULL)
			{
				m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"无[%s]文件",m_pFlowList[i].flowflename);
			}
		}
	}
	while (m_bIsRunning)
	{
		for (i=0; i< m_pFlowList.size() ; i++)
		{
			if (m_pFlowList[i].pFlowFp == NULL)
			{
				continue;
			}
			nRet = fseek(m_pFlowList[i].pFlowFp,16,1);//移到序号+交易码后面
			if (nRet != 0) //到尾了
			{
				fclose(m_pFlowList[i].pFlowFp);
				m_pFlowList[i].pFlowFp = NULL;
			}
			else
			{
				bzero(&data,sizeof(BPCCOMMSTRU));
				nRet = fread(data.sBuffer,1,4096,m_pFlowList[i].pFlowFp);
				if (nRet != 4096)
				{
					fclose(m_pFlowList[i].pFlowFp);
					m_pFlowList[i].pFlowFp = NULL;
				}
				else
				{
					datalen = strlen(data.sBuffer);
					data.sDBHead.nLen = datalen;
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"处理[%s]重演 [%s]",m_pFlowList[i].flowflename,data.sBuffer);
					m_apiPoint->apistruct->cb_.api_recv_msg_(data.sBuffer,GTP_TYPE_STRING,datalen,m_apiPoint->apistruct);
				}
			}

		}

		
		SLEEP(1);
	}
	return 0;
}
bool CTestSgeDll::InitThreadInstance()
{
	return true;
}

void CTestSgeDll::ExitThreadInstance()
{

}

void CTestSgeDll::Disconnect()
{
	CIOfferingBase::Disconnect();
	
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"断开api连接 api_disconnect");
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
		m_apiPoint->apistruct->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),m_apiPoint->apistruct);
	}
}
