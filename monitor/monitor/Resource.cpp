// Resource.cpp: implementation of the CResource class.
//
//////////////////////////////////////////////////////////////////////

#include "Resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResource::CResource()
{
	g_bIsExit = false;
	bzero(g_sCurPath,sizeof(g_sCurPath));
	bzero(g_sModuleName,sizeof(g_sCurPath));
	bzero(g_sModulePath,sizeof(g_sModulePath));
	bzero(m_sStartDate,sizeof(m_sStartDate));

	g_nGwDisTime = 6000;
	g_nHeartRun = 5;
	g_nDisconnectTime = 60;
	g_nNoHeartRestarTime = 15;
	g_nHeartPoolSize = 200;

}

CResource::~CResource()
{

}
bool CResource::Init(const char *confile)
{
	char tmpchar[300];
	sprintf(tmpchar,"%s/monirun.xml",g_sCurPath);
	g_pRunXml.FromFile(tmpchar);

	if (!g_pXml.FromFile(confile))
	{
		sprintf(m_sErrMsg,"配置文件[%s]不存在或非xml",confile);
		return false;
	}

	

	m_pDate.Update();
	
	CBF_Tools::StringCopy(m_sStartDate,17,m_pDate.ToStringDT17().c_str());
	
	int ret=0;
	std::string stmp;
	
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/日志级别",false,g_nLoglevel) == NULL)
	{
		sprintf(m_sErrMsg,"配置文件错,无[package/head/公共配置/日志级别]节点");
		return false;
	}
	if (g_nLoglevel <0 )
	{
		g_nLoglevel = LOG_DEBUG;//配置错则为5
	}
	
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/日志文件",false,g_sLogFileName) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件错,无[package/head/公共配置/日志文件]节点");
		return false;
	}
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/日志目录",false,g_sLogFilePath) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件错,无[package/head/公共配置/日志目录]节点");
		g_sLogFilePath="";
	}
	g_pLog.SetLogPara(g_nLoglevel,g_sLogFilePath.c_str(),g_sLogFileName.c_str());
	
	
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/主机ID",false,m_sHostId) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件错,无[package/head/公共配置/主机ID]节点");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/主机名称",false,m_sHostName) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件错,无[package/head/公共配置/主机名称]节点");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/节点ID",false,m_sNodeId) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件错,无[package/head/公共配置/节点ID]节点");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}
	
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/心跳时间",false,g_nHeartRun) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件,无[package/head/公共配置/心跳时间]节点");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nHeartRun = 5;
	}
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/监控服务连接过期时间",false,g_nDisconnectTime) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件,无[package/head/公共配置/监控服务连接过期时间]节点");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nDisconnectTime = 60;
	}
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/连接过期时间",false,g_nGwDisTime) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件,无[package/head/公共配置/连接过期时间]节点");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nGwDisTime = 6000;
	}
	if (g_pXml.GetNodeValueByPath("package/head/公共配置/心跳侦听端口",false,g_nPort) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件,无[package/head/公共配置/心跳侦听端口]节点");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}

	if (g_pXml.GetNodeValueByPath("package/head/公共配置/无心跳重启时间",false,g_nNoHeartRestarTime) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件,无[package/head/公共配置/无心跳重启时间]节点，默认15秒");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nNoHeartRestarTime =15;
	}
	if (g_nNoHeartRestarTime <15)
	{
		g_nNoHeartRestarTime = 15;
	}

	if (g_pXml.GetNodeValueByPath("package/head/公共配置/心跳连接池大小",false,g_nHeartPoolSize) == NULL)
	{
		sprintf(m_sErrMsg, "配置文件,无[package/head/公共配置/心跳连接池大小]节点，默认200");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nHeartPoolSize = 200;
	}
	if (g_nHeartPoolSize <20)
	{
		g_nHeartPoolSize = 20;
	}

	
	
	g_nUseMonitor=1;
	
	CXmlNode *tmpnode = NULL;
	CXmlNode *drebnode = g_pXml.GetNodeByPath("package/head/监控服务端口配置",false);
	if (drebnode != NULL)
	{
		tmpnode = (CXmlNode *)drebnode->GetFirstChild();
		S_DREBLINK_INFO dreblinkinfo;
		while (tmpnode != NULL)
		{
			if (tmpnode->GetAttribute("ip",false,dreblinkinfo.sIp) == NULL)
			{
				g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"%s 无ip属性",tmpnode->GetNodeName().c_str());
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			if (tmpnode->GetAttribute("port",false,stmp) == NULL)
			{
				g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"%s 无port属性",tmpnode->GetNodeName().c_str());
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			dreblinkinfo.nPort = atoi(stmp.c_str());
			g_vDrebLinkInfo.push_back(dreblinkinfo);
			tmpnode = (CXmlNode *)tmpnode->getNextSibling();
		}
		if (g_vDrebLinkInfo.size() < 2 )
		{
			sprintf(m_sErrMsg, "节点[package/head/监控服务端口配置]配置数目不符");
			g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
			return false;
		}
	}
	else
	{
		sprintf(m_sErrMsg, "节点[package/head/监控服务端口配置]没有配置");
		g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}
	
	S_PROCESS_NODE pnode;
	CXmlNode *mgrnode = g_pXml.GetNodeByPath("package/head/进程守护",false);
	if (mgrnode != NULL)
	{
		
		tmpnode = (CXmlNode *)mgrnode->GetFirstChild();
		if (tmpnode == NULL)
		{
			sprintf(m_sErrMsg, "节点[package/head/进程守护]没有配置进程信息");
			g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
			return true;
		}
		while (tmpnode != NULL)
		{
			pnode.nodeid = tmpnode->GetNodeName();//进程ID
			sprintf(tmpchar,"package/head/进程守护/%s/进程名称",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.processname) == NULL)
			{
				sprintf(m_sErrMsg, "节点[%s]没有配置",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/进程守护/%s/程序名",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.prgname) == NULL)
			{
				sprintf(m_sErrMsg, "节点[%s]没有配置",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/进程守护/%s/程序路径",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.prgpath) == NULL)
			{
				sprintf(m_sErrMsg, "节点[%s]没有配置",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/进程守护/%s/运行目录",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.runpath) == NULL)
			{
				sprintf(m_sErrMsg, "节点[%s]没有配置",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/进程守护/%s/启动参数",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.prgpara) == NULL)
			{
				sprintf(m_sErrMsg, "节点[%s]没有配置",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/进程守护/%s/停止脚本",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.stopscript) == NULL)
			{
				sprintf(m_sErrMsg, "节点[%s]没有配置",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/进程守护/%s/无心跳是否重启",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.heartstart) == NULL)
			{
				sprintf(m_sErrMsg, "节点[%s]没有配置",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/进程守护/%s/是否接受控制",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.acceptcontrol) == NULL)
			{
				sprintf(m_sErrMsg, "节点[%s]没有配置",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			pnode.pid = -1;
			pnode.status = "1"; //0为正常 1为停止 2为无心跳
			pnode.controltype = "0";//0为由主机资源控制启动  1为由客户端远程控制启动，只是客户端停止时置为1
			//取得进程信息
			sprintf(tmpchar,"进程守护/%s/进程ID",pnode.nodeid.c_str());
			g_pRunXml.GetNodeValueByPath(tmpchar,false,pnode.pid);
			pnode.lastUseTIme = time(NULL)+300;//设最后使用时间为300秒后，防止进程启动时间较长不停的重启
			g_vProcessInfo.push_back(pnode);
			tmpnode = (CXmlNode *)tmpnode->getNextSibling();
		}
		
	}
	else
	{
		sprintf(m_sErrMsg, "节点[package/head/DREB配置]没有配置");
		g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
	}
	if (m_xmlWarnError.fromFile("check.xml")<0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"check.xml文件不存在或格式错");
		printf("check.xml文件不存在或格式错!\n");
		return false;
	}
	if (m_xmlItem.fromFile("item.xml")<0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"item.xml文件不存在或格式错");
		printf("item.xml文件不存在或格式错!\n");
		return false;
	}
	return true;
}

bool CResource::UpdateLastTimeById(std::string nodeid)
{
	for (int i=0 ; i< g_vProcessInfo.size(); i++)
	{
		if (g_vProcessInfo[i].nodeid.compare(nodeid) == 0)
		{
			g_vProcessInfo[i].lastUseTIme = time(NULL);
			return true;
		}
	}
	return false;
}
int CResource::GetProcessIndexById(std::string nodeid)
{
	for (int i=0 ; i< g_vProcessInfo.size(); i++)
	{
		if (g_vProcessInfo[i].nodeid.compare(nodeid) == 0)
		{
			return i;
		}
	}
	return -1;
}