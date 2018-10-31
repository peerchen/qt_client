// OfferingTrade.cpp: implementation of the COfferingTrade class.
//
//////////////////////////////////////////////////////////////////////

#include "OfferingTrade.h"
#include "TradeResource.h"
#include "BF_Date_Time.h"
#include "BF_3Des.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COfferingTrade * getInstance() 
{ 
    return new COfferingTrade(); 
}


void COfferingTrade::DSP_2_HEX(const char *dsp,char *hex,int count)
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

void COfferingTrade::HEX_2_DSP(const char *hex,char *dsp,int count)
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
COfferingTrade::COfferingTrade()
{
	m_nIpIndex =0;
	m_nConnTime = 0;
	bzero(m_cCurDir,sizeof(m_cCurDir));
	WORKPATH(m_cCurDir);
	bzero(&m_pPoint,sizeof(SGE_API_OFFERING_POINTS));
	m_pDllApiHandle = NULL;
	m_pDllCaApiHandle = NULL;
	m_sSgeSafeInfo = NULL;
	m_pApiEasy = NULL;
	m_pApiShca = NULL;
	m_nSgeSafeInfoLen = 0;
	m_bIsInit = false;
	m_bIsStop = true;
	m_nEncryptFlag =1;
	m_nQuotaBreak = 0;
	//竞价交易接口
	AddFuncInfo("A130",(SgeFuncPointer)&COfferingTrade::SendMsg,"交易员密码修改");
	AddFuncInfo("A320",(SgeFuncPointer)&COfferingTrade::SendMsg,"应急密码修改");
	AddFuncInfo("B320",(SgeFuncPointer)&COfferingTrade::SendMsg,"递延费率查询");
	AddFuncInfo("B340",(SgeFuncPointer)&COfferingTrade::SendMsg,"交易所状态查询");
	AddFuncInfo("T430",(SgeFuncPointer)&COfferingTrade::SendMsg,"席位客户查询");
	AddFuncInfo("T440",(SgeFuncPointer)&COfferingTrade::SendMsg,"席位持仓查询");
	AddFuncInfo("T450",(SgeFuncPointer)&COfferingTrade::SendMsg,"席位资金查询");
	AddFuncInfo("T460",(SgeFuncPointer)&COfferingTrade::SendMsg,"客户持仓查询");
	AddFuncInfo("T470",(SgeFuncPointer)&COfferingTrade::SendMsg,"客户库存查询");
	AddFuncInfo("Q090",(SgeFuncPointer)&COfferingTrade::SendMsg,"交易实时行情查询");
	AddFuncInfo("Q100",(SgeFuncPointer)&COfferingTrade::SendMsg,"交易分钟行情查询");
	AddFuncInfo("Q200",(SgeFuncPointer)&COfferingTrade::SendMsg,"交割实时行情");
	AddFuncInfo("Q900",(SgeFuncPointer)&COfferingTrade::SendMsg,"公告发布");
	AddFuncInfo("Q910",(SgeFuncPointer)&COfferingTrade::SendMsg,"公告发布");
	AddFuncInfo("Q900",(SgeFuncPointer)&COfferingTrade::SendMsg,"交易所公告查询");
	AddFuncInfo("T200",(SgeFuncPointer)&COfferingTrade::SendMsg,"报单请求");
	AddFuncInfo("T210",(SgeFuncPointer)&COfferingTrade::SendMsg,"撤单请求");
	AddFuncInfo("T230",(SgeFuncPointer)&COfferingTrade::SendMsg,"报单查询");
	AddFuncInfo("T240",(SgeFuncPointer)&COfferingTrade::SendMsg,"本地报单查询");
	AddFuncInfo("T250",(SgeFuncPointer)&COfferingTrade::SendMsg,"成交单查询");
	AddFuncInfo("T090",(SgeFuncPointer)&COfferingTrade::SendMsg,"交割申报");
	AddFuncInfo("T100",(SgeFuncPointer)&COfferingTrade::SendMsg,"交割申报撤销");
	AddFuncInfo("T120",(SgeFuncPointer)&COfferingTrade::SendMsg,"中立仓申报");
	AddFuncInfo("T130",(SgeFuncPointer)&COfferingTrade::SendMsg,"中立仓申报撤销");
	AddFuncInfo("T400",(SgeFuncPointer)&COfferingTrade::SendMsg,"交割申报报单查询");
	AddFuncInfo("T410",(SgeFuncPointer)&COfferingTrade::SendMsg,"交割申报成交查询");
	AddFuncInfo("T420",(SgeFuncPointer)&COfferingTrade::SendMsg,"中立仓申报报单查询");
	
	//资金仓储接口
	AddFuncInfo("F010",(SgeFuncPointer)&COfferingTrade::SendMsg,"资金划拨");
	AddFuncInfo("F020",(SgeFuncPointer)&COfferingTrade::SendMsg,"往来账查询");
	AddFuncInfo("F900",(SgeFuncPointer)&COfferingTrade::SendMsg,"增加资金密码");
	AddFuncInfo("F910",(SgeFuncPointer)&COfferingTrade::SendMsg,"修改资金密码");
	AddFuncInfo("F920",(SgeFuncPointer)&COfferingTrade::SendMsg,"重置资金密码");
	AddFuncInfo("S000",(SgeFuncPointer)&COfferingTrade::SendMsg,"增加提货申请");
	AddFuncInfo("S010",(SgeFuncPointer)&COfferingTrade::SendMsg,"撤销提货申请");
	AddFuncInfo("S020",(SgeFuncPointer)&COfferingTrade::SendMsg,"提货申请查询");
	AddFuncInfo("S030",(SgeFuncPointer)&COfferingTrade::SendMsg,"提货密码重置");
	AddFuncInfo("S100",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交质押申报");
	AddFuncInfo("S110",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交质押申报");
	AddFuncInfo("S120",(SgeFuncPointer)&COfferingTrade::SendMsg,"质押申报查询");
	AddFuncInfo("S130",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交质押注销申报");
	AddFuncInfo("S140",(SgeFuncPointer)&COfferingTrade::SendMsg,"撤销质押注销申报");
	AddFuncInfo("S150",(SgeFuncPointer)&COfferingTrade::SendMsg,"质押登记注销申报");
	AddFuncInfo("S160",(SgeFuncPointer)&COfferingTrade::SendMsg,"质押登记注销申报");
	AddFuncInfo("S200",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交租借登记申报");
	AddFuncInfo("S210",(SgeFuncPointer)&COfferingTrade::SendMsg,"撤销租借登记申报");
	AddFuncInfo("S220",(SgeFuncPointer)&COfferingTrade::SendMsg,"租借登记申报查询");
	AddFuncInfo("S230",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交租借还金登记申报");
	AddFuncInfo("S240",(SgeFuncPointer)&COfferingTrade::SendMsg,"撤销租借还金登记申报");
	AddFuncInfo("S250",(SgeFuncPointer)&COfferingTrade::SendMsg,"租借还金申报查询");
	AddFuncInfo("S260",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交租借续租申报");
	AddFuncInfo("S270",(SgeFuncPointer)&COfferingTrade::SendMsg,"撤销租借续租申报");
	AddFuncInfo("S280",(SgeFuncPointer)&COfferingTrade::SendMsg,"租借续租申报查询");
	AddFuncInfo("S290",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交租借状态变更申报");
	AddFuncInfo("S300",(SgeFuncPointer)&COfferingTrade::SendMsg,"租借状态变更申报查询");
	AddFuncInfo("S310",(SgeFuncPointer)&COfferingTrade::SendMsg,"租借登记查询");
	AddFuncInfo("S320",(SgeFuncPointer)&COfferingTrade::SendMsg,"租借还金登记查询");
	AddFuncInfo("S410",(SgeFuncPointer)&COfferingTrade::SendMsg,"租借还金登记查询");
	AddFuncInfo("S420",(SgeFuncPointer)&COfferingTrade::SendMsg,"库存划转查询");
	AddFuncInfo("S510",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交库存互换申报");
	AddFuncInfo("S520",(SgeFuncPointer)&COfferingTrade::SendMsg,"提交库存互换申报");
	AddFuncInfo("S530",(SgeFuncPointer)&COfferingTrade::SendMsg,"库存互换申报查询");
	AddFuncInfo("S540",(SgeFuncPointer)&COfferingTrade::SendMsg,"库存互换登记查询");
	AddFuncInfo("S810",(SgeFuncPointer)&COfferingTrade::SendMsg,"查询清算用库存变化流水");
	AddFuncInfo("S820",(SgeFuncPointer)&COfferingTrade::SendMsg,"查询库存变化流水");
	AddFuncInfo("S840",(SgeFuncPointer)&COfferingTrade::SendMsg,"查询库存变化流水");
	AddFuncInfo("S330",(SgeFuncPointer)&COfferingTrade::SendMsg,"查询每日租借基准利率及均值");
	
	
	//黄金ETF
	AddFuncInfo("E000",(SgeFuncPointer)&COfferingTrade::SendMsg,"账户备案/客户绑定");
	AddFuncInfo("E010",(SgeFuncPointer)&COfferingTrade::SendMsg,"账户解绑定");
	AddFuncInfo("E020",(SgeFuncPointer)&COfferingTrade::SendMsg,"账户备案业务本地编号查询");
	AddFuncInfo("E030",(SgeFuncPointer)&COfferingTrade::SendMsg,"认购请求");
	AddFuncInfo("E050",(SgeFuncPointer)&COfferingTrade::SendMsg,"申购请求");
	AddFuncInfo("E070",(SgeFuncPointer)&COfferingTrade::SendMsg,"赎回请求");
	AddFuncInfo("E090",(SgeFuncPointer)&COfferingTrade::SendMsg,"发送账户绑定结果请求");
	AddFuncInfo("E100",(SgeFuncPointer)&COfferingTrade::SendMsg,"发送认购确认通知请求");
	AddFuncInfo("E110",(SgeFuncPointer)&COfferingTrade::SendMsg,"发送申赎清单系统控制版本请求");
	AddFuncInfo("E120",(SgeFuncPointer)&COfferingTrade::SendMsg,"申赎清单查询请求");
	AddFuncInfo("E130",(SgeFuncPointer)&COfferingTrade::SendMsg,"认申赎交易本地编号查询");
	
	//账户卡
	AddFuncInfo("R000",(SgeFuncPointer)&COfferingTrade::SendMsg,"自然人客户开户");
	AddFuncInfo("R010",(SgeFuncPointer)&COfferingTrade::SendMsg,"自然人客户信息变更");
	AddFuncInfo("R020",(SgeFuncPointer)&COfferingTrade::SendMsg,"自然人客户指定交易");
	AddFuncInfo("R030",(SgeFuncPointer)&COfferingTrade::SendMsg,"自然人客户指定交易撤销");
	AddFuncInfo("R040",(SgeFuncPointer)&COfferingTrade::SendMsg,"客户销户请求");
	AddFuncInfo("R050",(SgeFuncPointer)&COfferingTrade::SendMsg,"客户信息查询请求");
	AddFuncInfo("R100",(SgeFuncPointer)&COfferingTrade::SendMsg,"机构客户开户申请请求");
	AddFuncInfo("R110",(SgeFuncPointer)&COfferingTrade::SendMsg,"机构客户信息变更申请");
	AddFuncInfo("R120",(SgeFuncPointer)&COfferingTrade::SendMsg,"机构客户指定交易申请");
	AddFuncInfo("R130",(SgeFuncPointer)&COfferingTrade::SendMsg,"机构客户指定交易撤销申请");
	AddFuncInfo("R140",(SgeFuncPointer)&COfferingTrade::SendMsg,"机构客户销户申请请求");
	AddFuncInfo("R150",(SgeFuncPointer)&COfferingTrade::SendMsg,"机构客户信息查询请求");

}

COfferingTrade::~COfferingTrade()
{
	if (m_apiPoint->apistruct->safe_handle_!= NULL)
	{
		//释放ca
		m_pPoint.ca_api_safe_deinit(m_apiPoint->apistruct->safe_handle_);
		m_apiPoint->apistruct->safe_handle_ = NULL;
	}
	if (m_sSgeSafeInfo != NULL)
	{
		free(m_sSgeSafeInfo);
		m_sSgeSafeInfo = NULL;
	}
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
// #ifdef _WINDOWS
// #else
// 	//20170328 增加当退出时，备份api日志
// 	int status;  
// 	char cmd[1000];
// 	CBF_Date_Time pDate;
// 	pDate.Update();
// 	std::string logstr=pDate.ToStringD8()+pDate.ToStringT6();
// 	std::string sdate= pDate.ToStringD8();
// 	
// 	
// #ifdef _WINDOWS
// 	
// 	chdir(m_cCurDir);
// 	sprintf(cmd,"clearapilog.bat %s %s %s",sdate.c_str(),logstr.c_str(),m_cCurDir);
// #else
// 	sprintf(cmd,"./clearapilog.sh %s %s ",sdate.c_str(),logstr.c_str());
// #endif
//     status = System(cmd);  
// 	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"清除api日志 system返回[0x%x]",status);
// 	SLEEP_SECONDS(2);
//     if (-1 == status)  
//     {  
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"调用system出错 %s",cmd);
// 		return ;
//     }  
//     else  
//     {  
// #ifdef  LINUX	
//         if (WIFEXITED(status))  
//         {  
//             if (0 == WEXITSTATUS(status))  
//             {  
//                 m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"清除api日志成功");
//             }  
//             else  
//             {  
// 				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"清除api日志调用shell脚本失败 %d",WEXITSTATUS(status));
// 				return ;
//             }  
//         }  
//         else  
//         {  
// 			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"清除api日志 返回[%d]",WEXITSTATUS(status));
// 			return ;
//         }  
// #else
// 		
// #endif
//     }  
// #endif
}

bool COfferingTrade::Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg)
{
	bool bRet = CIOfferingBase::Init(api,log,xml,xmlnode,errmsg);
	if (!bRet)
	{
		return bRet;
	}
	//针对密码字段解密成明文
	if (m_nPwdFlag == 1)
	{
		char  xmlnodepath2[200];
		sprintf(xmlnodepath2,"%s/密码加密模式",xmlnode);
		int encryptflag=0;
		if (xml->GetNodeValueByPath(xmlnodepath2,false,encryptflag) == NULL)
		{
			sprintf(errmsg,"配置文件[%s]不存在,默认为0",xmlnodepath2);
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,errmsg);
			encryptflag =0;
		}
		
		
		//交易员密码
		char tmpchar[300];
		bzero(tmpchar,sizeof(tmpchar));
		if (encryptflag != 0)  //3DES方式
		{
			CBF_3Des pDes;
			strcpy(tmpchar,m_sTradePwd.c_str());
			int buflen = strlen(tmpchar);
			if (!pDes.UnDes3Buffer(tmpchar,buflen,DBPWD3DESKEY,errmsg))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易员密码解密出错 %s",errmsg);
				return false;
			}
			tmpchar[buflen]=0;
			m_sTradePwd = tmpchar;	
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sTradePwd=%s",m_sTradePwd.c_str());
			
			
			//证书密码
			bzero(tmpchar,sizeof(tmpchar));
			strcpy(tmpchar,m_sCertPwd.c_str());
			buflen = strlen(tmpchar);
			if (!pDes.UnDes3Buffer(tmpchar,buflen,DBPWD3DESKEY,errmsg))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"证书密码解密出错 %s",errmsg);
				return false;
			}
			tmpchar[buflen]=0;
			
			m_sCertPwd = tmpchar;	
			
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sCertPwd=%s",m_sCertPwd.c_str());
			
			if (m_sSeatPwd.length()>0)
			{
				//席位密码
				bzero(tmpchar,sizeof(tmpchar));
				strcpy(tmpchar,m_sSeatPwd.c_str());
				buflen = strlen(tmpchar);
				if (!pDes.UnDes3Buffer(tmpchar,buflen,DBPWD3DESKEY,errmsg))
				{
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"席位密码解密出错 %s",errmsg);
					return false;
				}
				tmpchar[buflen]=0;
				m_sSeatPwd = tmpchar;	
				m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sSeatPwd=%s",m_sSeatPwd.c_str());
			}
		}
		else  //des方式
		{
			CBF_Des       pDes;
			strcpy(tmpchar,m_sTradePwd.c_str());
			int buflen = strlen(tmpchar);
			if (pDes.Uncryptchar(tmpchar,buflen,DBPWDKEY)<=0)
			{
				sprintf(errmsg,"交易员密码解密出错");
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
				return false;
			}
			tmpchar[buflen]=0;
			m_sTradePwd = tmpchar;	
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sTradePwd=%s",m_sTradePwd.c_str());
			
			
			//证书密码
			bzero(tmpchar,sizeof(tmpchar));
			strcpy(tmpchar,m_sCertPwd.c_str());
			buflen = strlen(tmpchar);
			if (pDes.Uncryptchar(tmpchar,buflen,DBPWDKEY)<=0)
			{
				sprintf(errmsg,"证书密码解密出错");
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
				return false;
			}
			tmpchar[buflen]=0;
			
			m_sCertPwd = tmpchar;	
			
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sCertPwd=%s",m_sCertPwd.c_str());
			
			if (m_sSeatPwd.length()>0)
			{
				//席位密码
				bzero(tmpchar,sizeof(tmpchar));
				strcpy(tmpchar,m_sSeatPwd.c_str());
				buflen = strlen(tmpchar);
				if (pDes.Uncryptchar(tmpchar,buflen,DBPWDKEY)<=0)
				{
					sprintf(errmsg,"席位密码解密出错");
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
					return false;
				}
				tmpchar[buflen]=0;
				m_sSeatPwd = tmpchar;	
				m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sSeatPwd=%s",m_sSeatPwd.c_str());
			}
		}
		
		
	}
	if (m_sNodeType.compare("12") ==0) //ETF报盘机
	{
		char xmlnodepath[100];
		sprintf(xmlnodepath,"%s/会员代码",xmlnode);
		if (xml->GetNodeValueByPath(xmlnodepath,false,m_sMemberId,false) == NULL)
		{
			sprintf(errmsg,"配置文件[%s]不存在",xmlnodepath);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		sprintf(xmlnodepath,"%s/机构类型",xmlnode);
		if (xml->GetNodeValueByPath(xmlnodepath,false,m_sOrganType,false) == NULL)
		{
			sprintf(errmsg,"配置文件[%s]不存在",xmlnodepath);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		sprintf(xmlnodepath,"%s/ETF交易日期",xmlnode);
		if (xml->GetNodeValueByPath(xmlnodepath,false,m_sTradeDate,false) == NULL)
		{
			sprintf(errmsg,"配置文件[%s]不存在",xmlnodepath);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		
	}
	char xmlnodeencryptflag[100];
	sprintf(xmlnodeencryptflag,"%s/发送交易所加密",xmlnode);
	if (xml->GetNodeValueByPath(xmlnodeencryptflag,false,m_nEncryptFlag) == NULL)
	{
		sprintf(errmsg,"配置文件[%s]不存在",xmlnodeencryptflag);
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
	sprintf(xmlnodeencryptflag,"%s/行情断点",xmlnode);
	if (xml->GetNodeValueByPath(xmlnodeencryptflag,false,m_nQuotaBreak) == NULL)
	{
		sprintf(errmsg,"配置文件[%s]不存在",xmlnodeencryptflag);
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		m_nQuotaBreak =0;
	}
	
	//打开动态库
	std::string dllname;
	std::string dllcaname;
	std::string dlleasy;
	std::string dllshca;
#ifdef _WINDOWS
	dllname = "libapi.dll";
	dllcaname = "libapi_safe.dll";
	dlleasy = "libEasy.dll";
	dllshca = "SafeEngine.dll";
#else
	dllname = "libapi.so";
	dllcaname = "libapi_safe.so";
	dlleasy = "libeasy.so";
	dllshca = "libsafeengine.so";
#endif	
	m_pApiEasy = LOADDLL(dlleasy.c_str());
	if (ISNOTOPEN(m_pApiEasy))
	{
		sprintf(errmsg,"打开动态库%s失败",dlleasy.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
	m_pDllApiHandle = LOADDLL(dllname.c_str());
#ifdef _WINDOWS
	if (ISNOTOPEN(m_pDllApiHandle))
	{
		sprintf(errmsg,"打开动态库%s失败 出错码%d",dllname.c_str(),GetLastError());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#else
	char *err = dlerror();
	if (err != NULL)
	{
		sprintf(errmsg,"打开动态库%s失败 出错[%s]",dllname.c_str(),err);
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#endif
	
	m_pPoint.api_set_new_endpoint = (_api_set_new_endpoint)GETINSTANCE(m_pDllApiHandle, "api_set_new_endpoint"); 
	m_pPoint.api_disconnect = (_api_disconnect)GETINSTANCE(m_pDllApiHandle, "api_disconnect"); 
	m_pPoint.api_free = (_api_free)GETINSTANCE(m_pDllApiHandle, "api_free"); 
	m_pPoint.api_get_version = (_api_get_version)GETINSTANCE(m_pDllApiHandle, "api_get_version"); 
	m_pPoint.api_init = (_api_init)GETINSTANCE(m_pDllApiHandle, "api_init"); 
	m_pPoint.api_send_msg = (_api_send_msg)GETINSTANCE(m_pDllApiHandle, "api_send_msg"); 
	m_pPoint.api_send_msg_no_enc = (_api_send_msg_no_enc)GETINSTANCE(m_pDllApiHandle, "api_send_msg_no_enc"); 
	m_pPoint.api_thread_begin = (_api_thread_begin)GETINSTANCE(m_pDllApiHandle, "api_thread_begin"); 
	m_pPoint.api_thread_end = (_api_thread_end)GETINSTANCE(m_pDllApiHandle, "api_thread_end"); 
	m_pPoint.api_wait = (_api_wait)GETINSTANCE(m_pDllApiHandle, "api_wait"); 
	m_pPoint.api_stop = (_api_stop)GETINSTANCE(m_pDllApiHandle, "api_stop"); 
	
    if (NULL == m_pPoint.api_set_new_endpoint || \
		NULL == m_pPoint.api_disconnect || \
		NULL == m_pPoint.api_free || \
		NULL == m_pPoint.api_get_version || \
		NULL == m_pPoint.api_init || \
		NULL == m_pPoint.api_send_msg || \
		NULL == m_pPoint.api_send_msg_no_enc || \
		NULL == m_pPoint.api_thread_begin || \
		NULL == m_pPoint.api_thread_end || \
		NULL == m_pPoint.api_wait || \
		NULL == m_pPoint.api_stop
		)
    {
        sprintf(errmsg,"取动态库[%s]里的函数地址失败",dllname.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
        return false;
    }
	m_pApiShca = LOADDLL(dllshca.c_str());
	if (ISNOTOPEN(m_pApiShca))
	{
		sprintf(errmsg,"打开动态库%s失败",dllshca.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
	m_pDllCaApiHandle = LOADDLL(dllcaname.c_str());
#ifdef _WINDOWS
	if (ISNOTOPEN(m_pDllCaApiHandle))
	{
		sprintf(errmsg,"打开动态库%s失败 出错码%d",dllcaname.c_str(),GET_LAST_SOCK_ERROR());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#else
	err = dlerror();
	if (err != NULL)
	{
		sprintf(errmsg,"打开动态库%s失败 出错[%s]",dllcaname.c_str(),err);
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#endif
// 	if (ISNOTOPEN(m_pDllCaApiHandle))
// 	{
// 		sprintf(errmsg,"打开动态库[%s]失败",dllcaname.c_str());
// 		return false;
// 	}
	m_pPoint.ca_api_safe_check_server_info = (_api_safe_check_server_info)GETINSTANCE(m_pDllCaApiHandle, "api_safe_check_server_info"); 
	m_pPoint.ca_api_safe_create_client_info = (_api_safe_create_client_info)GETINSTANCE(m_pDllCaApiHandle, "api_safe_create_client_info"); 
	m_pPoint.ca_api_safe_decrypt = (_api_safe_decrypt)GETINSTANCE(m_pDllCaApiHandle, "api_safe_decrypt"); 
	m_pPoint.ca_api_safe_deinit = (_api_safe_deinit)GETINSTANCE(m_pDllCaApiHandle, "api_safe_deinit"); 
	m_pPoint.ca_api_safe_encrypt = (_api_safe_encrypt)GETINSTANCE(m_pDllCaApiHandle, "api_safe_encrypt"); 
	m_pPoint.ca_api_safe_get_version = (_api_safe_get_version)GETINSTANCE(m_pDllCaApiHandle, "api_safe_get_version"); 
	m_pPoint.ca_api_safe_init = (_api_safe_init)GETINSTANCE(m_pDllCaApiHandle, "api_safe_init"); 
	
	
    if (NULL == m_pPoint.ca_api_safe_check_server_info || \
		NULL == m_pPoint.ca_api_safe_create_client_info || \
		NULL == m_pPoint.ca_api_safe_decrypt || \
		NULL == m_pPoint.ca_api_safe_deinit || \
		NULL == m_pPoint.ca_api_safe_encrypt || \
		NULL == m_pPoint.ca_api_safe_get_version || \
		NULL == m_pPoint.ca_api_safe_init 	
		)
    {
        sprintf(errmsg,"取动态库[%s]里的函数地址失败",dllcaname.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
        return false;
    }

// 	}
// 	std::string   m_sPath_key;//UserKey.key文件路径 即私钥
// 	std::string   m_sPath_user;//UserCert.der文件路径
// 	std::string   m_sPath_root;//RootCert.der文件路径
// 	std::string   m_sPath_svr;//server.der文件路径
// 	std::string   m_sCertPwd;//证书密码

// 	    key_path：		UserKey.key文件路径
// 		rootcert_path：	RootCert.der文件路径
// 		svr_cert_path：	server.der文件路径
// 		cli_cert_path：	UserCert.der文件路径
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"key_path[%s] rootcert_path：[%s] svr_cert_path：[%s] cli_cert_path：[%s]",\
		m_sPath_key.c_str(),m_sPath_root.c_str(),m_sPath_svr.c_str(),m_sPath_user.c_str());
    m_apiPoint->apistruct->safe_handle_ =	m_pPoint.ca_api_safe_init(m_sPath_key.c_str(),m_sPath_root.c_str(),m_sPath_svr.c_str(),m_sPath_user.c_str(),m_sCertPwd.c_str());
	if(m_apiPoint->apistruct->safe_handle_ == NULL)
	{
		sprintf(errmsg,"ca_api_safe_init[%s]初始化失败 key_path[%s] rootcert_path：[%s] svr_cert_path：[%s] cli_cert_path：[%s]",\
			m_sPath_key.c_str(),m_sPath_root.c_str(),m_sPath_svr.c_str(),m_sPath_user.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
	//生成安全信息
	m_sSgeSafeInfo = (char *)calloc(8192, 1); 
	if (m_sSgeSafeInfo == NULL)
	{
		sprintf(errmsg,"分配CA安全信息空间失败");
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}

	m_bIsInit = true;
	return true;
}
int  COfferingTrade::SendMsg(CGtpData *senddata)
{
	//判断连接是否正常
	if (m_nApiStatus != 1 || m_nApiLoginStatus != 1)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易所状态为未连接或未登录");
		return -1;
	}
	CBF_PMutex pp(&m_mutex);
	senddata->SetDataItem("X08",m_sSendFlag.c_str());
	senddata->SetDataItem("X09",m_sRcvFlag.c_str());
	//发送数据
	char sendBuffer[8192];
	size_t  sendlen=8192;
	std::string gtpstring;
	if (!senddata->ToString(gtpstring))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ToString出错");
		return -1;
	}
	
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"要发送的GTP数据 [%s]",gtpstring.c_str());
	int ret;
	if (m_nEncryptFlag == 1)
	{
		try
		{
			
			ret = m_pPoint.ca_api_safe_encrypt(m_apiPoint->apistruct->safe_handle_, (const unsigned char *)gtpstring.c_str(), gtpstring.length(), (unsigned char *)sendBuffer, &sendlen);
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"调用ca_api_safe_encrypt 异常出错 %d",ret);
			return -1;	
		}
		
		if (ret < 0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ca_api_safe_encrypt 加密出错 %d",ret);
			return -1;
		}
		try
		{
			ret = m_pPoint.api_send_msg(m_apiPoint->apistruct->api_, sendBuffer, sendlen);
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"调用api_send_msg 异常出错 %d",ret);
			return -1;	
		}
		
		if (ret <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"api_send_msg 发送出错 %d",ret);
			return -1;
		}
	}
	else
	{
		try
		{
			ret = m_pPoint.api_send_msg_no_enc(m_apiPoint->apistruct->api_, gtpstring.c_str(), gtpstring.length());
			
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"调用api_send_msg 异常出错 %d",ret);
			return -1;	
		}
		
		if (ret <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"api_send_msg 发送出错 %d",ret);
			return -1;
		}
	}
	m_nSendReqTime=time(NULL);
	return 0;
}


bool COfferingTrade::Uncrypt(S_SGE_GEMS2_API_STRUCT *ctx,const char *cryptmsg,int msglen,char *gtpmsg,int &gtpmsglen)
{
	if (ctx == m_apiPoint->apistruct)
	{
		size_t dstmsglen = gtpmsglen;
		//解密数据
		//(api_safe_handle_t handle, const unsigned char *src, const size_t len, unsigned char *dst, size_t *cap);
		int ret =  m_pPoint.ca_api_safe_decrypt(m_apiPoint->apistruct->safe_handle_,(const unsigned char *)cryptmsg,msglen,(unsigned char *)gtpmsg,&dstmsglen);
		if (ret <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"解密出错 %d",ret);
			return false;
		}
		gtpmsglen = dstmsglen;
		return true;
	}
	else
	{
		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"Uncrypt 返回不是本API的");
		return false;
	}
}

bool COfferingTrade::StartApi()
{
	char sIp[40];
	int  nPort;
	if (!GetFrontIpPort(sIp,nPort))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"无交易所前置IP及端口");
        return false;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"本次连接的交易所前置端口[%s %d]",sIp,nPort);

	CBF_PMutex pp(&m_mutex);
    //初始化api    
	m_apiPoint->apistruct->api_ = m_pPoint.api_init(sIp, nPort, &(m_apiPoint->apistruct->cb_), m_apiPoint->apistruct);
	if(m_apiPoint->apistruct->api_ == NULL) 
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"交易所api_init出错");
        return false;
	}
	m_nSgeSafeInfoLen = 8192;
	int ret = m_pPoint.ca_api_safe_create_client_info(m_apiPoint->apistruct->safe_handle_ , m_sSgeSafeInfo, m_nSgeSafeInfoLen);
	if (ret <= 0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ca_api_safe_create_client_info 生成安全信息失败 [%d]",ret);
		return false;
	}
	m_nSgeSafeInfoLen = ret;
	
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"证书安全信息 [%s] 长度[%d]",m_sSgeSafeInfo,m_nSgeSafeInfoLen);


	//启动api线程
	m_pPoint.api_thread_begin(m_apiPoint->apistruct->api_,"gtpapi.inf");
	m_bIsStop = false;

	m_nSendReqTime = time(NULL);
	m_nRcvBackTime = time(NULL);
	m_nRcvAnsTime = time(NULL);
	return true;
}
bool COfferingTrade::StopApi()
{
	if (!m_bIsInit)
	{
		return true;
	}
	CBF_PMutex pp(&m_mutex);
	if (m_bIsStop)
	{
		return true;
	}
	
	//发送交易员录出指令
	if (m_nApiLoginStatus == 1)
	{
		TradeLogout();
		Disconnect();
	}
	if (m_apiPoint == NULL ||  m_apiPoint->apistruct == NULL)
	{
		return true;
	}
	if (m_apiPoint->apistruct->api_ != NULL)
	{
		//停止api线程
		m_pPoint.api_thread_end(m_apiPoint->apistruct->api_);
		//等待线程终止
		printf("开始api_stop\n");
		m_pPoint.api_stop(m_apiPoint->apistruct->api_);
		m_pPoint.api_wait(m_apiPoint->apistruct->api_);
		printf("结束api_stop\n");
		m_bIsStop = true;
		
	}

	if (m_apiPoint->apistruct->api_ != NULL)
	{
		//释放api
		m_pPoint.api_free(m_apiPoint->apistruct->api_);
		m_apiPoint->apistruct->api_ = NULL;
	}
	return true;
}

void COfferingTrade::TradeLogout()
{
	//置最后连接时间
	if (!m_bIsInit)
	{
		return ;
	}
	//组gtp报文
	CBF_PMutex pp(&m_mutex);

	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP版本
	gtpdata.SetDataItem("X02","0000");//长度
	if (m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X03","A310");//消息类型
	}
	else
	{
		gtpdata.SetDataItem("X03","A110");//消息类型
	}
	
	gtpdata.SetDataItem("X04","1");//序列类别号
	gtpdata.SetDataItem("X05","1");//消息序列号
	gtpdata.SetDataItem("X06","L");//消息的连续标志
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符

	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//交易员代码
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位号


	if(m_sNodeType.compare("6") == 0)
	{
		gtpdata.SetDataItem("X25","TRA");//接入方系统标识
	}else if(m_sNodeType.compare("5") == 0)
	{
		gtpdata.SetDataItem("X25","WM");//接入方系统标识
	}else if(m_sNodeType.compare("4") == 0)
	{
		gtpdata.SetDataItem("X25","ACCT");//接入方系统标识
	}else if(m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X25","ETF");//接入方系统标识
	}  
	
	gtpdata.SetDataItem("X02",m_sTradeId.length()+m_sSeatNo.length()+9);//长度

	std::string gtpstring ;
	if (!gtpdata.ToString(gtpstring))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"设置断点信息节点错,ToString");
		return;
	}
	
	if (m_pPoint.api_send_msg_no_enc == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"未初始化动态库");
		return;
	}
	int nRet ;
	try
	{
		if (m_apiPoint->apistruct == NULL || m_apiPoint->apistruct->api_== NULL)
		{
			return;
		}
		nRet = m_pPoint.api_send_msg_no_enc(m_apiPoint->apistruct->api_,gtpstring.c_str(),gtpstring.length());
	}
	catch (...)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送交易员录出调用api_send_msg_no_enc异常失败");
		return;	
	}
	
	if (nRet <0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送交易员录出失败 %d",nRet);
		return;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送交易员录出完成 [%s]",gtpstring.c_str());
	CBF_Date_Time pdate;
	pdate.Update();
	m_nLogoutTime = atoi(pdate.ToStringD8().c_str())*10000+pdate.GetHour()*100+pdate.GetMinute(); 
	
	return;	
}
void COfferingTrade::TradeLogin()
{
	CBF_PMutex pp(&m_mutex);
	//交易员或席位登录
	
	//组gtp报文
	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP版本
	gtpdata.SetDataItem("X02","0000");//长度
	if (m_sNodeType.compare("12") == 0)
	{
		CBF_Date_Time pdate;
		pdate.Update();
		gtpdata.SetDataItem("X03","A300");//消息类型
		gtpdata.SetDataItem("X04","1");//序列类别号
		gtpdata.SetDataItem("X05","1");//消息序列号
		gtpdata.SetDataItem("X06","L");//消息的连续标志
		gtpdata.SetDataItem("X07","0");//RootID
		gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
		gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符
		if (m_sTradeDate.length()<2)
		{
			gtpdata.SetDataItem("T13",pdate.ToStringD8().c_str());//交易日期
		}
		else
		{
			gtpdata.SetDataItem("T13",m_sTradeDate.c_str());//使用交易服务的交易日期
		}
		gtpdata.SetDataItem("M00",m_sMemberId.c_str());//会员代码
		gtpdata.SetDataItem("R09",m_sOrganType);//机构类型
	}
	else
	{
		gtpdata.SetDataItem("X04","1");//序列类别号
		gtpdata.SetDataItem("X05","1");//消息序列号
		gtpdata.SetDataItem("X06","L");//消息的连续标志
		gtpdata.SetDataItem("X07","0");//RootID
		gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//发送方标识符
		gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//接收方标识符
		gtpdata.SetDataItem("X03","A100");//消息类型
		gtpdata.SetDataItem("M60",m_sTradeId.c_str());//交易员代码
	}

	
	
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//席位号
	gtpdata.SetDataItem("M62",m_sTradePwd);//登录密码
	gtpdata.SetDataItem("X50","127.0.0.1");//ip地址
	gtpdata.SetDataItem("X55",m_pPoint.api_get_version(m_apiPoint->apistruct->api_));//API版本信息
	
	if(m_sNodeType.compare("6") == 0)
	{
		gtpdata.SetDataItem("X25","TRA");//接入方系统标识
	}else if(m_sNodeType.compare("5") == 0)
	{
		gtpdata.SetDataItem("X25","WM");//接入方系统标识
	}else if(m_sNodeType.compare("4") == 0)
	{
		gtpdata.SetDataItem("X25","ACCT");//接入方系统标识
	}else if(m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X25","ETF");//接入方系统标识
	}   
	  
	gtpdata.SetDataItem("X80",m_sSgeSafeInfo);//安全信息域
	gtpdata.SetDataItem("X81",m_nSgeSafeInfoLen);//安全信息域长度

	

	CGtpData *arrynode = gtpdata.AddDataItem("X20",GTP_DATATYPE_ARRAY);
	if (arrynode == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"设置断点信息节点错 GTP_DATATYPE_ARRAY");
		return ;
	}
	CGtpData *hashnode = NULL;
	char tmpchar[100];
	for (int i=0; i<MAXFLOWNO; i++ )
	{
		sprintf(tmpchar,"%d",i);
		hashnode = arrynode->AddDataItem(tmpchar,GTP_DATATYPE_HASH);
		if (hashnode == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"设置断点信息节点错,GTP_DATATYPE_HASH");
			return;
		}
		hashnode->SetDataItem("X04",m_FlowInfo[i]->nFlowNo);
		if (m_FlowInfo[i]->nFlowNo == 6 && m_nQuotaBreak != 1)
		{
			hashnode->SetDataItem("X05",-1); //不取行情断点
		}
		else
		{
			hashnode->SetDataItem("X05",m_FlowInfo[i]->nMaxSerial);
		}
	}
	std::string gtpstring ;

	arrynode->ToString(gtpstring);

	gtpdata.SetDataItem("X02",m_sTradePwd.length()+m_sTradeId.length()+m_sSeatNo.length()+9+5+m_nSgeSafeInfoLen+4+40+gtpstring.length());//长度

	gtpstring = "";
	if (!gtpdata.ToString(gtpstring))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"设置断点信息节点错,ToString");
		return;
	}
	int nRet;

	try
	{
		nRet = m_pPoint.api_send_msg_no_enc(m_apiPoint->apistruct->api_,gtpstring.c_str(),gtpstring.length());
	}
	catch (...)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送交易员登录调用api_send_msg_no_enc异常失败");
		return;	
	}
	
	if (nRet <0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"发送交易员登录失败 %d",nRet);
		return;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"发送交易员登录完成 [%s]",gtpstring.c_str());
	m_nLoginNum++;
	return;
}

bool COfferingTrade::GetFrontIpPort(char *ip, int &port)
{
	int nIpList = m_pListIp.size();
	if (nIpList <1 )
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"未配置交易所IP");
		return false;
	}
	else if (nIpList == 1)
	{
		strcpy(ip,m_pListIp[0].sIp);
		port = m_pListIp[0].nPort;
		return true;
	}
// 	//在列表中随机选一个IP
// 	srand(CBF_Date_Time::GetTickCount());
// 	int id = rand() % nIpList;

	strcpy(ip,m_pListIp[m_nIpIndex].sIp);
	port = m_pListIp[m_nIpIndex].nPort;
	m_nPort = port;
	strcpy(m_sIp,ip);
	m_nIpIndex++;
	if (m_nIpIndex >= nIpList)
	{
		m_nIpIndex=0;
	}
	return true;
}
bool COfferingTrade::CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
{
	m_nDisconnectTime = time(NULL);

	if (ctx == m_apiPoint->apistruct)
	{
		m_nApiStatus = cs->state;
		m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"CB_Disconnected 和交易所前置断开[%s %d] 状态%d",\
			cs->ip,cs->port,cs->state);
		--(ctx->connected_count_);
		m_nApiLoginStatus =0;
		//连接断开 重设前置IP
// 		char sIp[40];
// 		int  nPort;
// 		if (!GetFrontIpPort(sIp,nPort))
// 		{
// 			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"无交易所前置IP及端口");
// 			return false;
// 		}
// 		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"断开连接，下次连接的交易所前置端口[%s %d]",sIp,nPort);
// 		m_pPoint.api_set_new_endpoint(m_apiPoint->apistruct->api_,sIp,nPort);
		
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
			ctx->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),ctx);
		}


	}
	else
	{
		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"CB_Disconnected 返回不是本API的");
	}
	return true;
}
void COfferingTrade::LoginRsp(int loginstatus,const char *gtp)
{
	//m_nApiLoginStatus = loginstatus;
// 	if (!loggindata->ToString(m_sLogGtp))
// 	{
// 		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"保存登录和录出报文出错");
// 	}
	m_sLogGtp = gtp;
	if (loginstatus == 1)
	{
		//登录成功后置为1
		m_nLoginNum = 1;
		if (m_nEncryptFlag == 1)
		{
			int ret;
			//校验
			try
			{
				//typedef int (*_api_safe_check_server_info)(api_safe_handle_t handle, const char *input, const size_t real_en_len);
				int ret=0;
				char x80[16384];
				char x81[16384];
				
				if (!GetGtpValue(gtp,"X80",x80))
//				if (loggindata->GetValueByName("X80",x80,fieldtype)<0)
				{
					m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"登录返回无x80字段");
					m_nApiLoginStatus =0;
					return;
				}
				std::string sx80 = x80;
				GtpGetTransSign(sx80);
				if (!GetGtpValue(gtp,"X81",x81))
//				if (loggindata->GetValueByName("X81",x81,fieldtype)<0)
				{
					m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"登录返回无x81字段");
					m_nApiLoginStatus =0;
					return;
				}
				int fieldtype = atoi(x81);
				m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"服务端安全信息 [%s] 长度[%s]",sx80.c_str(),x81);
				ret = m_pPoint.ca_api_safe_check_server_info(m_apiPoint->apistruct->safe_handle_,sx80.c_str(),fieldtype);
				if (ret != 0)
				{
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"服务端安全信息 [%s] 长度[%d]",sx80.c_str(),fieldtype);
					m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"ca_api_safe_check_server_info验证失败 %d",ret);
					m_nApiLoginStatus =0;
					return;
				}
				m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ca_api_safe_check_server_info OK");
				m_nApiLoginStatus = loginstatus;
			}
			catch (...)
			{
				m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"ca_api_safe_check_server_info验证异常出错");
				m_nApiLoginStatus =0;
			}
		
		}
		
	}
	else
	{
		//在Login里增加
		//m_nLoginNum++;
		m_nApiLoginStatus = loginstatus;
	}
	
}

void COfferingTrade::Disconnect()
{
	CIOfferingBase::Disconnect();
	m_pPoint.api_disconnect(m_apiPoint->apistruct->api_);
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"断开api连接 api_disconnect");

	//连接断开 重设前置IP
	char sIp[40];
	int  nPort;
	if (!GetFrontIpPort(sIp,nPort))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"无交易所前置IP及端口");
		return ;
	}
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"断开连接，下次连接的交易所前置端口[%s %d]",sIp,nPort);
	m_pPoint.api_set_new_endpoint(m_apiPoint->apistruct->api_,sIp,nPort);
	
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

int COfferingTrade::System(const char *cmd)
{
	int nRet =0;
#ifdef LINUX
	sighandler_t old_handler;
	old_handler = signal(SIGCHLD, SIG_DFL);
#endif
	nRet = system(cmd);
#ifdef LINUX
	signal(SIGCHLD, old_handler);
#endif
	
	return nRet;
}
int COfferingTrade::GtpGetTransSign(std::string &value)
{
	int nLength;
	char *tmpchar = (char *)malloc(value.length()+1);
	memset(tmpchar,0,value.length()+1);
	nLength = value.length();
	char *p = tmpchar;
	for (int i=0;i<nLength;)
	{
		if (value.c_str()[i] == '\\' && 
			( value.c_str()[i+1] == ',' || \
			value.c_str()[i+1] == '{' || \
			value.c_str()[i+1] == '}' || \
			value.c_str()[i+1] == '[' || \
			value.c_str()[i+1] == ']' ||  \
			value.c_str()[i+1] == '=') ) 
		{
			//是转义
			i++;
			continue;
		}
		*p = value.c_str()[i];
		p++;
		i++;
	}
	value = tmpchar;
	p=NULL;
	free(tmpchar);
	return 0;
}
//转义符
//\, ,
//\{ {
//\} }
//\[ [
//\] ]
//\= =
int COfferingTrade::GtpPutTransSign(std::string &value)
{
	if (value.length()<1)
	{
		return 0;
	}
	char *tmpchar = (char *)malloc(value.length()+100);
	memset(tmpchar,0,value.length()+100);
	
	char *p = tmpchar;
	for (int i=0;i<(int)value.length();i++)
	{
		if (value.c_str()[i] == ',' )
		{
			strcpy(p,"\\,");
			p+=2;
		}
		else if (value.c_str()[i] == '{' )
		{
			strcpy(p,"\\{");
			p+=2;
		}
		else if (value.c_str()[i] == '}' )
		{
			strcpy(p,"\\}");
			p+=2;
		}
		else if (value.c_str()[i] == '[' )
		{
			strcpy(p,"\\[");
			p+=2;
		}
		else if (value.c_str()[i] == ']' )
		{
			strcpy(p,"\\]");
			p+=2;
		}
		else if (value.c_str()[i] == '=' )
		{
			strcpy(p,"\\=");
			p+=2;
		}
		else
		{
			*p = value.c_str()[i];
			p++;
		}
	}
	*(p+1)= 0;
	value = tmpchar;
	p = NULL;
	free(tmpchar);
	return 0;
}
