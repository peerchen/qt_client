// Resource.h: interface for the CResource class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCE_H__FF782DDA_47F8_4B57_961C_BF9F48B676FC__INCLUDED_)
#define AFX_RESOURCE_H__FF782DDA_47F8_4B57_961C_BF9F48B676FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BF_Xml.h"
#include "BF_SimpleLog.h"
#include "BF_Date_Time.h"
#include "BF_Tools.h"
#include "MdbBase.h"
#include "MoniHead.h"
#include "BF_ProcessMgr.h"
#include "XmlPack.h"


class CResource  
{
public:
	CResource();
	virtual ~CResource();

	bool g_bIsExit;

	std::string m_sHostId;//����ID
	std::string m_sNodeId;//�ڵ�ID
	std::string m_sHostName;//��������

	int   g_nUseMonitor;       //�Ƿ���
	int   g_nMonitorHost;      //�Ƿ񱨸�������Դ
	int   g_nMonitorDrebId;            //�����ڵ��
	int   g_nMonitorDrebPrivateId;     //˽�нڵ��
	int   g_nMonitorSvrId;            //��������ڵ��
	int   g_nMonitorSvrPrivateId;     //˽�з���ڵ��
	int   g_nMonitorTxCode;           //��ؽ�����
	
	char              g_sCurPath[300]; //��ǰ����Ŀ¼
	char              g_sModulePath[300];//��������Ŀ¼
	char              g_sModuleName[300];//������

	char              m_sStartDate[20];//��������
	
	int g_nLoglevel;           //��־���� Ĭ��Ϊ5
	std::string g_sLogFileName;//��־�ļ���
	std::string g_sLogFilePath;//��־�ļ�Ŀ¼
	int g_nHeartRun;           //����ʱ��,���������ӳ�����ʱ��δ��ʱ��������������
	int g_nDisconnectTime;//δʹ�öϿ�ʱ�䣬���һ�������ڴ�ʱ����һֱû��ʹ�ã��򽫴����ӶϿ�����λ��Ĭ��600�뼴10����
	int g_nGwDisTime;  //ת������δʹ�öϿ�ʱ��

	int g_nPort;   //�����˿�

	int g_nNoHeartRestarTime;
	int g_nHeartPoolSize;

	CBF_Xml  g_pXml; //xml������

	CXmlPack m_xmlWarnError;//cpu�����ڴ澯���������
	CXmlPack m_xmlItem;    //����������

	CBF_SimpleLog  g_pLog;
	CBF_Date_Time  m_pDate;

	CBF_Xml  g_pRunXml; //�������������Ϣ����PID��xml�ļ�
	char     m_sErrMsg[256]; //������Ϣ

	vector<S_DREBLINK_INFO> g_vDrebLinkInfo;//dreb�����б�
	vector<S_PROCESS_NODE>  g_vProcessInfo; //����Ľ�����Ϣ
	
public:

	// ������: GetProcessIndexById
	// ���  : ������ 2013-12-26 19:47:30
	// ����  : int 
	// ����  : std::string nodeid  
	// ����  : ȡ�ý��̵�����
	int GetProcessIndexById(std::string nodeid);

	bool UpdateLastTimeById(std::string nodeid);

	// ������: Init
	// ���  : ������ 2013-12-10 9:46:25
	// ����  : bool 
	// ����  : const char *confile
	// ����  : �������ļ�
	bool Init(const char *confile);


protected:
	
};

#endif // !defined(AFX_RESOURCE_H__FF782DDA_47F8_4B57_961C_BF9F48B676FC__INCLUDED_)
