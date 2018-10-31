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
		sprintf(m_sErrMsg,"�����ļ�[%s]�����ڻ��xml",confile);
		return false;
	}

	

	m_pDate.Update();
	
	CBF_Tools::StringCopy(m_sStartDate,17,m_pDate.ToStringDT17().c_str());
	
	int ret=0;
	std::string stmp;
	
	if (g_pXml.GetNodeValueByPath("package/head/��������/��־����",false,g_nLoglevel) == NULL)
	{
		sprintf(m_sErrMsg,"�����ļ���,��[package/head/��������/��־����]�ڵ�");
		return false;
	}
	if (g_nLoglevel <0 )
	{
		g_nLoglevel = LOG_DEBUG;//���ô���Ϊ5
	}
	
	if (g_pXml.GetNodeValueByPath("package/head/��������/��־�ļ�",false,g_sLogFileName) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ���,��[package/head/��������/��־�ļ�]�ڵ�");
		return false;
	}
	if (g_pXml.GetNodeValueByPath("package/head/��������/��־Ŀ¼",false,g_sLogFilePath) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ���,��[package/head/��������/��־Ŀ¼]�ڵ�");
		g_sLogFilePath="";
	}
	g_pLog.SetLogPara(g_nLoglevel,g_sLogFilePath.c_str(),g_sLogFileName.c_str());
	
	
	if (g_pXml.GetNodeValueByPath("package/head/��������/����ID",false,m_sHostId) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ���,��[package/head/��������/����ID]�ڵ�");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}
	if (g_pXml.GetNodeValueByPath("package/head/��������/��������",false,m_sHostName) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ���,��[package/head/��������/��������]�ڵ�");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}
	if (g_pXml.GetNodeValueByPath("package/head/��������/�ڵ�ID",false,m_sNodeId) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ���,��[package/head/��������/�ڵ�ID]�ڵ�");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}
	
	if (g_pXml.GetNodeValueByPath("package/head/��������/����ʱ��",false,g_nHeartRun) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ�,��[package/head/��������/����ʱ��]�ڵ�");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nHeartRun = 5;
	}
	if (g_pXml.GetNodeValueByPath("package/head/��������/��ط������ӹ���ʱ��",false,g_nDisconnectTime) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ�,��[package/head/��������/��ط������ӹ���ʱ��]�ڵ�");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nDisconnectTime = 60;
	}
	if (g_pXml.GetNodeValueByPath("package/head/��������/���ӹ���ʱ��",false,g_nGwDisTime) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ�,��[package/head/��������/���ӹ���ʱ��]�ڵ�");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nGwDisTime = 6000;
	}
	if (g_pXml.GetNodeValueByPath("package/head/��������/���������˿�",false,g_nPort) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ�,��[package/head/��������/���������˿�]�ڵ�");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}

	if (g_pXml.GetNodeValueByPath("package/head/��������/����������ʱ��",false,g_nNoHeartRestarTime) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ�,��[package/head/��������/����������ʱ��]�ڵ㣬Ĭ��15��");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nNoHeartRestarTime =15;
	}
	if (g_nNoHeartRestarTime <15)
	{
		g_nNoHeartRestarTime = 15;
	}

	if (g_pXml.GetNodeValueByPath("package/head/��������/�������ӳش�С",false,g_nHeartPoolSize) == NULL)
	{
		sprintf(m_sErrMsg, "�����ļ�,��[package/head/��������/�������ӳش�С]�ڵ㣬Ĭ��200");
		g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,m_sErrMsg);
		g_nHeartPoolSize = 200;
	}
	if (g_nHeartPoolSize <20)
	{
		g_nHeartPoolSize = 20;
	}

	
	
	g_nUseMonitor=1;
	
	CXmlNode *tmpnode = NULL;
	CXmlNode *drebnode = g_pXml.GetNodeByPath("package/head/��ط���˿�����",false);
	if (drebnode != NULL)
	{
		tmpnode = (CXmlNode *)drebnode->GetFirstChild();
		S_DREBLINK_INFO dreblinkinfo;
		while (tmpnode != NULL)
		{
			if (tmpnode->GetAttribute("ip",false,dreblinkinfo.sIp) == NULL)
			{
				g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"%s ��ip����",tmpnode->GetNodeName().c_str());
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			if (tmpnode->GetAttribute("port",false,stmp) == NULL)
			{
				g_pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"%s ��port����",tmpnode->GetNodeName().c_str());
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			dreblinkinfo.nPort = atoi(stmp.c_str());
			g_vDrebLinkInfo.push_back(dreblinkinfo);
			tmpnode = (CXmlNode *)tmpnode->getNextSibling();
		}
		if (g_vDrebLinkInfo.size() < 2 )
		{
			sprintf(m_sErrMsg, "�ڵ�[package/head/��ط���˿�����]������Ŀ����");
			g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
			return false;
		}
	}
	else
	{
		sprintf(m_sErrMsg, "�ڵ�[package/head/��ط���˿�����]û������");
		g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
		return false;
	}
	
	S_PROCESS_NODE pnode;
	CXmlNode *mgrnode = g_pXml.GetNodeByPath("package/head/�����ػ�",false);
	if (mgrnode != NULL)
	{
		
		tmpnode = (CXmlNode *)mgrnode->GetFirstChild();
		if (tmpnode == NULL)
		{
			sprintf(m_sErrMsg, "�ڵ�[package/head/�����ػ�]û�����ý�����Ϣ");
			g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
			return true;
		}
		while (tmpnode != NULL)
		{
			pnode.nodeid = tmpnode->GetNodeName();//����ID
			sprintf(tmpchar,"package/head/�����ػ�/%s/��������",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.processname) == NULL)
			{
				sprintf(m_sErrMsg, "�ڵ�[%s]û������",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/�����ػ�/%s/������",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.prgname) == NULL)
			{
				sprintf(m_sErrMsg, "�ڵ�[%s]û������",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/�����ػ�/%s/����·��",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.prgpath) == NULL)
			{
				sprintf(m_sErrMsg, "�ڵ�[%s]û������",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/�����ػ�/%s/����Ŀ¼",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.runpath) == NULL)
			{
				sprintf(m_sErrMsg, "�ڵ�[%s]û������",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/�����ػ�/%s/��������",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.prgpara) == NULL)
			{
				sprintf(m_sErrMsg, "�ڵ�[%s]û������",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/�����ػ�/%s/ֹͣ�ű�",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.stopscript) == NULL)
			{
				sprintf(m_sErrMsg, "�ڵ�[%s]û������",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/�����ػ�/%s/�������Ƿ�����",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.heartstart) == NULL)
			{
				sprintf(m_sErrMsg, "�ڵ�[%s]û������",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			sprintf(tmpchar,"package/head/�����ػ�/%s/�Ƿ���ܿ���",pnode.nodeid.c_str());
			if (g_pXml.GetNodeValueByPath(tmpchar,false,pnode.acceptcontrol) == NULL)
			{
				sprintf(m_sErrMsg, "�ڵ�[%s]û������",tmpchar);
				g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
				tmpnode = (CXmlNode *)tmpnode->getNextSibling();
				continue;
			}
			pnode.pid = -1;
			pnode.status = "1"; //0Ϊ���� 1Ϊֹͣ 2Ϊ������
			pnode.controltype = "0";//0Ϊ��������Դ��������  1Ϊ�ɿͻ���Զ�̿���������ֻ�ǿͻ���ֹͣʱ��Ϊ1
			//ȡ�ý�����Ϣ
			sprintf(tmpchar,"�����ػ�/%s/����ID",pnode.nodeid.c_str());
			g_pRunXml.GetNodeValueByPath(tmpchar,false,pnode.pid);
			pnode.lastUseTIme = time(NULL)+300;//�����ʹ��ʱ��Ϊ300��󣬷�ֹ��������ʱ��ϳ���ͣ������
			g_vProcessInfo.push_back(pnode);
			tmpnode = (CXmlNode *)tmpnode->getNextSibling();
		}
		
	}
	else
	{
		sprintf(m_sErrMsg, "�ڵ�[package/head/DREB����]û������");
		g_pLog.LogMp(LOG_PROMPT,__FILE__,__LINE__,m_sErrMsg);
	}
	if (m_xmlWarnError.fromFile("check.xml")<0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"check.xml�ļ������ڻ��ʽ��");
		printf("check.xml�ļ������ڻ��ʽ��!\n");
		return false;
	}
	if (m_xmlItem.fromFile("item.xml")<0)
	{
		g_pLog.LogMp(LOG_ERROR,__FILE__,__LINE__,"item.xml�ļ������ڻ��ʽ��");
		printf("item.xml�ļ������ڻ��ʽ��!\n");
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