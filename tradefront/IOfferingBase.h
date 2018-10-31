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


//报盘机接口基类
//各个报盘机继承此基类实现
// </资金仓储报盘机>
// 	<DLLNAME method="getInstance" >trade.so</DLLNAME>
// 	<魔数 remark="GTP报文头的魔数" >1123</魔数>
// 	<安全认证 remark="上海CA的配置">
// 		<key_path remark="UserKey.key文件路径" >/home/appgess/ylink/tfront/shca</key_path>
// 		<rootcrt_path remark="RootCert.der文件路径" >/home/appgess/ylink/tfront/shca</rootcrt_path>
// 		<svr_cert_path remark="server.der文件路径" >/home/appgess/ylink/tfront/shca</svr_cert_path>
// 		<cli_cert_path remark="UserCert.der文件路径" >/home/appgess/ylink/tfront/shca</cli_cert_path>
// 		<证书密码 remark="证书密码,默认123412" >123412</证书密码>
// 	</安全认证>
// 	<交易员 remark="登录交易所的交易员" >jy</交易员>
// 	<交易员密码 remark="" >1123</交易员密码>
// 	<接入单元 remark="连接交易所的接入单元" >jy</接入单元>
// 	<接入单元密码 remark="连接交易所的接入单元密码" >888888</接入单元密码>
// 	<前置配置 remark="配置交易所的前置，连不上可尝试下一个">
// 		<front ip="127.0.0.1" port="9011" remark="配置要连接前置的参数" />
// 		<front ip="127.0.0.1" port="9012" remark="配置要连接前置的参数" />
// 	</前置配置>
// </资金仓储报盘机>



// 数据流	消息序列类别号
// 交易流	1
// 回报流	2
// 私有流	3
// 公共流	4
// 查询流	5
// 行情流	6

typedef struct 
{
	int           nFlowNo;//消息类别号
	int  nMaxSerial;//最大流水号
}S_FLOW_INFO;
#define  MAXFLOWNO     6

typedef struct 
{
	api_t * api_;
	api_cb_t cb_;
	api_safe_handle_t safe_handle_;
	volatile unsigned int recv_count_;
	volatile unsigned int connected_count_;
}S_SGE_GEMS2_API_STRUCT;  //对应ctx_t

typedef struct
{
	S_SGE_GEMS2_API_STRUCT *apistruct;//保存api调用、handle、回调等的结构
	CIOfferingBase         *apiPoint;//调用api的dll库类指针
	UINT64_                apistructpvalue; //存放apistruct指针的值
	DLLHANDLE              apidllhandle;//动态库句柄
	std::string            apidllname;//动态库名称
	std::string            apiInstance;//实例的函数名
	std::string            apidllpath;//动态库路径，绝对
	std::string            offernodepath;//配置所在的节点路径
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
		//释放环境
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
	virtual bool Init(S_SGE_GEMS2_API *api,CIErrlog *log,const char *xmlfile,const char *xmlnode,char *errmsg)
	{
		CBF_Xml xml;
		if (!xml.FromFile(xmlfile))
		{
			sprintf(errmsg,"XML文件[%s]不存在或非法xml",xmlfile);
			return false;
		}
		return Init(api,log,&xml,xmlnode,errmsg);
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
	virtual bool Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg)
	{
		m_apiPoint = api;
		m_pLog = log;
		char nodename[512];
		
		CXmlNode *offeringnode = xml->GetNodeByPath(xmlnode,false);
		if (offeringnode == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",xmlnode);
			return false;
		}
		m_sOfferingName = offeringnode->GetNodeName(false);
		
		sprintf(nodename,"%s/魔数",xmlnode);
		std::string ss;
		if (xml->GetNodeValueByPath(nodename,false,ss,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}

		sprintf(nodename,"%s/节点类型",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sNodeType,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}

		
		m_magicNum = atol(ss.c_str());
		sprintf(nodename,"%s/交易员",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sTradeId,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/交易员密码",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sTradePwd,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/证件号码",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sCertNo,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/发送方标识",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sSendFlag,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/接收方标识",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sRcvFlag,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/密码加密标志",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_nPwdFlag) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
//		printf("%s=%d\n",nodename,m_nPwdFlag);

		sprintf(nodename,"%s/接入单元",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sAccessUnitId,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/接入单元密码",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sAccessPwd,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/安全认证/key_path",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sPath_key,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/安全认证/rootcrt_path",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sPath_root,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/安全认证/svr_cert_path",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sPath_svr,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/安全认证/cli_cert_path",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sPath_user,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/安全认证/证书密码",xmlnode);
		if (xml->GetNodeValueByPath(nodename,false,m_sCertPwd,false) == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		sprintf(nodename,"%s/前置配置",xmlnode);
		CXmlNode *fnode = xml->GetNodeByPath(nodename,false);
		if (fnode == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
			return false;
		}
		fnode = (CXmlNode *)fnode->GetFirstChild();
		if (fnode  == NULL)
		{
			sprintf(errmsg,"XML节点[%s]无子节点",nodename);
			return false;
		}
		S_FRONT_IPPORT fconf;
		while (fnode != NULL)
		{
			bzero(&fconf,sizeof(S_FRONT_IPPORT));
			if (fnode->GetAttribute("ip",false,ss,false) == NULL)
			{
				sprintf(errmsg,"XML节点[%s/%s]无ip属性",nodename,fnode->GetNodeName(false).c_str());
				return false;
			}
			CBF_Tools::StringCopy(fconf.sIp,32,ss.c_str());
			if (fnode->GetAttribute("port",false,ss,false) == NULL)
			{
				sprintf(errmsg,"XML节点[%s/%s]无port属性",nodename,fnode->GetNodeName(false).c_str());
				return false;
			}
			fconf.nPort= atoi(ss.c_str());
			m_pListIp.push_back(fconf);
			fnode = (CXmlNode *)fnode->getNextSibling();
		}
		//读取交易配置
		sprintf(nodename,"%s/交易注册",xmlnode);
		fnode = xml->GetNodeByPath(nodename,false);
		if (fnode == NULL)
		{
			sprintf(errmsg,"XML节点[%s]不存在",nodename);
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
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"使用配置文件里的交易注册");
			fnode = (CXmlNode *)fnode->GetFirstChild();
			if (fnode  == NULL)
			{
				sprintf(errmsg,"XML节点[%s]无子节点",nodename);
				return false;
			}
			//清空析构里注册的交易
			m_pTblFunc.Clear();

			while (fnode != NULL)
			{
				//将配置中的交易加到列表
				AddFuncInfo(fnode->GetNodeName(false).c_str(),&CIOfferingBase::SendMsg,fnode->GetNodeValue(false).c_str());
				fnode = (CXmlNode *)fnode->getNextSibling();
			}
		}
		
//		printf("IOfferingBase init api_cb_connected_[%x] api_cb_disconnected_[%x] \n",m_apiPoint->apistruct->cb_.api_cb_connected_,m_apiPoint->apistruct->cb_.api_cb_disconnected_);

		//开始初始化交易所的api和CA环境等
		
		m_bInit = true;
		return true;
	}


	// 函数名:  SendMsg
	// 编程  : 王明松 2016-3-11 11:34:50
	// 返回  : virtual int 
	// 参数  : const char *gtpmsg  gtp消息不含定长数据
	// 参数  : unsigned short gtplen
	// 描述  : 发送业务数据
	virtual int  SendMsg(CGtpData *senddata)=0;

	// 函数名: CB_Connected
	// 编程  : 王明松 2016-3-11 15:44:49
	// 返回  : virtual bool 
	// 参数  : api_connection_state_t * cs   连接状态
	// 参数  : S_SGE_GEMS2_API_STRUCT *ctx   api参数
	// 描述  : API的回调方法，连接成功了，要在里面发登录
	virtual bool CB_Connected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
	{
		if (ctx == m_apiPoint->apistruct)
		{
			m_nConnectTime = time(NULL);
			m_nApiStatus = cs->state;
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,"CB_Connected 和交易所前置连接上[%s %d] 状态%d",\
				cs->ip,cs->port,cs->state);
			++(ctx->connected_count_);
			//要发送登录请求
			m_nApiLoginStatus = 0;
			m_nSendReqTime = time(NULL);
			m_nRcvBackTime = time(NULL);
			m_nRcvAnsTime = time(NULL);
			TradeLogin();

		}
		else
		{
			m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"CB_Connected 返回不是本API的");
		}
		return true;
	}


	// 函数名: CB_Disconnected
	// 编程  : 王明松 2016-3-11 15:44:43
	// 返回  : virtual bool 
	// 参数  : api_connection_state_t * cs
	// 参数  : S_SGE_GEMS2_API_STRUCT *ctx
	// 描述  : api回调方法 断开连接了  要释放api环境，以备再次连接
	virtual bool CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
	{
		if (ctx == m_apiPoint->apistruct)
		{
			m_nDisconnectTime = time(NULL);
			m_nApiStatus = cs->state;
			m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"CB_Disconnected 和交易所前置断开[%s %d] 状态%d",\
				cs->ip,cs->port,cs->state);
			--(ctx->connected_count_);
			//释放环境
			
			//重连
		}
		else
		{
			m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"CB_Disconnected 返回不是本API的");
		}
		return true;
	}

	// 函数名: TradeLogin
	// 编程  : 王明松 2016-4-14 14:21:55
	// 返回  : virtual void 
	// 描述  : 交易员登录，记得要发断点信息    要对登录次数增加
	virtual void TradeLogin()=0;

	// 函数名: TradeLogout
	// 编程  : 王明松 2016-4-14 14:21:55
	// 返回  : virtual void 
	// 描述  : 交易员录出
	virtual void TradeLogout()=0;

	// 函数名: Uncrypt
	// 编程  : 王明松 2016-3-11 16:29:31
	// 返回  : virtual bool 
	// 参数  : S_SGE_GEMS2_API_STRUCT *ctx  api参数
	// 参数  : const char *cryptmsg         待解密的数据
	// 参数  : int msglen                   待解密的数据长度
	// 参数  : char *gtpmsg                 解密后的数据
	// 参数  : int &gtpmsglen               解密后的数据长度
	// 描述  : 解密
	virtual bool Uncrypt(S_SGE_GEMS2_API_STRUCT *ctx,const char *cryptmsg,int msglen,char *gtpmsg,int &gtpmsglen)=0;

	
	// 函数名: IsConnect
	// 编程  : 王明松 2016-3-11 16:30:37
	// 返回  : virtual int  -1未连接  0连接未登录 1已连接已登录
	// 描述  : 是否连接并登录上
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

	// 函数名: LoginRsp
	// 编程  : 王明松 2016-3-25 14:16:58
	// 返回  : virtual void 
	// 参数  : int loginstatus  0未登录  1已登录
	// 参数  : CGtpData *loggindata  登录响应或录出报文
	// 描述  : 登录响应，表明是否登录成功
	virtual void LoginRsp(int loginstatus,const char *gtp)
	{
		m_nApiLoginStatus = loginstatus;
		if (m_nApiLoginStatus == 1)
		{
			//登录成功后置为1
			m_nLoginNum = 1;
		}
		else
		{
			//在Login里增加
			//m_nLoginNum++;
		}
		m_sLogGtp =gtp;
// 		if (!loggindata->ToString(m_sLogGtp))
// 		{
// 			m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"保存登录和录出报文出错");
// 		}
	}
	std::string GetLoginRsp(int &loginstatus)
	{
		loginstatus = m_nApiLoginStatus;
		if (loginstatus != 1 && m_sLogGtp.length() <1) //未登录且录出报文为空，模拟一个报文出来
		{
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
			gtpdata.SetDataItem("X40","录出成功");//响应信息
			gtpdata.ToString(m_sLogGtp);
		}
		return m_sLogGtp;
	}
	// 函数名: StartApi
	// 编程  : 王明松 2016-3-11 16:31:55
	// 返回  : virtual bool 
	// 描述  : 开始API    建立连接，启动日志   要置m_nConnectTime为当前时间
	virtual bool StartApi()=0;
	

	// 函数名: StopApi
	// 编程  : 王明松 2016-3-11 16:32:06
	// 返回  : virtual bool 
	// 描述  : 断开连接，停止api，停止日志
	virtual bool StopApi()=0;

	// 函数名: Disconnect
	// 编程  : 王明松 2017-2-6 16:32:06
	// 返回  : virtual void 
	// 描述  : 断开连接
	virtual void Disconnect()
	{
		m_nDisconnectTime =time(NULL); 
		m_nApiStatus = 0;
	}


	// 函数名: NextFunc
	// 编程  : 王明松 2016-3-11 16:32:27
	// 返回  : virtual bool 
	// 参数  : S_SGE_TBL_FUNC &funcinfo
	// 描述  : 下一条交易信息
	virtual bool NextFunc(S_SGE_TBL_FUNC &funcinfo)
	{
		return m_pTblFunc.Next(funcinfo);
	}
	

	// 函数名: FirstFunc
	// 编程  : 王明松 2016-3-11 16:32:41
	// 返回  : virtual bool 
	// 参数  : S_SGE_TBL_FUNC &funcinfo
	// 描述  : 第一条交易信息
	virtual bool FirstFunc(S_SGE_TBL_FUNC &funcinfo)
	{
		return m_pTblFunc.First(funcinfo);
	}

	// 函数名: AddFuncInfo
	// 编程  : 王明松 2016-3-11 16:34:00
	// 返回  : void 
	// 参数  : int funcNo
	// 参数  : SgeFuncPointer pfunc
	// 参数  : const char *funcName
	// 描述  : 增加交易信息  
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
	// 函数名: AddFuncInfo
	// 编程  : 王明松 2016-3-11 16:34:00
	// 返回  : void 
	// 参数  : const char * funcNo
	// 参数  : SgeFuncPointer pfunc
	// 参数  : const char *funcName
	// 描述  : 增加交易信息  
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

public:
	char          m_sIp[33];//当前连接的前置IP
	int           m_nPort;  //当前连接的前置端口
	std::string   m_sNodeType;//节点类型，当前报盘机的类型 :4-账户卡报盘机 5-仓储资金报盘机 6-交易报盘机 7-银行资金前置机 12-ETF报盘机

	std::string   m_sTradeDate;//ETF报盘机交易日期

	S_FLOW_INFO   *m_FlowInfo[MAXFLOWNO];//保存各消息最大序号的结构数据

	std::string   m_sOfferingName;//报盘机名称

	unsigned  int   m_nLoginNum;//登录次数      在Login
	unsigned  int   m_nConnectTime;//连接时间   在startapi里设置
	unsigned  int   m_nDisconnectTime;


	std::string     m_sSeatNo;//席位代码
	std::string     m_sTradeId;//交易员

	UINT64_       m_nLogoutTime;//交易员录出时间  yyyymmddhhmm

	unsigned int  m_nRcvBackTime;   //最后接收回报时间   收到回报时时赋值
	unsigned int  m_nRcvAnsTime;   //最后接收应答时间   收到应答时时赋值
	unsigned int  m_nSendReqTime;  //最后发送请求时间   SendMsg时赋值

protected:
	
	

	S_SGE_GEMS2_API *m_apiPoint;
	CIErrlog      *m_pLog;

	bool          m_bInit;//是否INIT
	bool          m_bIsRunning;//线程运行标志

	unsigned int  m_magicNum;//GTP报文体魔数
	std::string   m_sPath_key;//UserKey.key文件路径 即私钥
	std::string   m_sPath_user;//UserCert.der文件路径
	std::string   m_sPath_root;//RootCert.der文件路径
	std::string   m_sPath_svr;//server.der文件路径
	std::string   m_sCertPwd;//证书密码

	
	std::string   m_sTradePwd;//交易员密码
	std::string   m_sCertNo;//证件号码
	int           m_nPwdFlag;//密码加密标志 0明文 1加密
	std::string   m_sSeatPwd;//席位密码

	std::string   m_sSendFlag;//发送方标识
	std::string   m_sRcvFlag;//接收方标识

	

	std::string   m_sAccessUnitId;//接入单元
	std::string   m_sAccessPwd;//接入单元密码

	std::vector<S_FRONT_IPPORT> m_pListIp;//前置IP端口列表
	
	


	CSgeFuncTbl   m_pTblFunc;//功能表

	volatile int  m_nApiStatus;//状态  经常的  0未连接 1已连接

	volatile int  m_nApiLoginStatus;//登录状态  经常变  1登录成功0未登录

	std::string   m_sLogGtp;//保存登录或录出的gtp报文

	


};

#endif // !defined(AFX_IOFFERINGBASE_H__40779290_A4D2_4574_BBCC_7885BED1E661__INCLUDED_)
