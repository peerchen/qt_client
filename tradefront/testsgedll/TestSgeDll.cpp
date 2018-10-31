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
	//������ע�ύ�ף��������ṩ�Ľ��׶�ע���ϣ�����������Ҫע���
	m_nQuoSerail =0;

	m_nOrderNo=0;
	m_nDoneNo =0;
	m_bIsReadFile = false;
	
	//���۽��׽ӿ�
	AddFuncInfo("A130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"����Ա�����޸�");
	AddFuncInfo("A320",(SgeFuncPointer)&CTestSgeDll::SendMsg,"Ӧ�������޸�");
	AddFuncInfo("B320",(SgeFuncPointer)&CTestSgeDll::SendMsg,"���ӷ��ʲ�ѯ");
	AddFuncInfo("B340",(SgeFuncPointer)&CTestSgeDll::SendMsg,"������״̬��ѯ");
	AddFuncInfo("T430",(SgeFuncPointer)&CTestSgeDll::SendMsg,"ϯλ�ͻ���ѯ");
	AddFuncInfo("T440",(SgeFuncPointer)&CTestSgeDll::SendMsg,"ϯλ�ֲֲ�ѯ");
	AddFuncInfo("T450",(SgeFuncPointer)&CTestSgeDll::SendMsg,"ϯλ�ʽ��ѯ");
	AddFuncInfo("T460",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ͻ��ֲֲ�ѯ");
	AddFuncInfo("T470",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ͻ�����ѯ");
	AddFuncInfo("Q090",(SgeFuncPointer)&CTestSgeDll::SendMsg,"����ʵʱ�����ѯ");
	AddFuncInfo("Q100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"���׷��������ѯ");
	AddFuncInfo("Q200",(SgeFuncPointer)&CTestSgeDll::SendMsg,"����ʵʱ����");
	AddFuncInfo("Q900",(SgeFuncPointer)&CTestSgeDll::SendMsg,"���淢��");
	AddFuncInfo("Q910",(SgeFuncPointer)&CTestSgeDll::SendMsg,"���淢��");
	AddFuncInfo("Q900",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����������ѯ");
	AddFuncInfo("T200",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��������");
	AddFuncInfo("T210",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��������");
	AddFuncInfo("T230",(SgeFuncPointer)&CTestSgeDll::SendMsg,"������ѯ");
	AddFuncInfo("T090",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����걨");
	AddFuncInfo("T100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����걨����");
	AddFuncInfo("T120",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�������걨");
	AddFuncInfo("T130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�������걨����");
	AddFuncInfo("T400",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����걨������ѯ");
	AddFuncInfo("T410",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����걨�ɽ���ѯ");
	AddFuncInfo("T420",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�������걨������ѯ");
	//�ʽ�ִ��ӿ�
	AddFuncInfo("F010",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ʽ𻮲�");
	AddFuncInfo("F020",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����˲�ѯ");
	AddFuncInfo("F900",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����ʽ�����");
	AddFuncInfo("F910",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�޸��ʽ�����");
	AddFuncInfo("F920",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����ʽ�����");
	AddFuncInfo("S000",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����������");
	AddFuncInfo("S010",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����������");
	AddFuncInfo("S020",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��������ѯ");
	AddFuncInfo("S030",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����������");
	AddFuncInfo("S100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ��Ѻ�걨");
	AddFuncInfo("S110",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ��Ѻ�걨");
	AddFuncInfo("S120",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��Ѻ�걨��ѯ");
	AddFuncInfo("S130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ��Ѻע���걨");
	AddFuncInfo("S140",(SgeFuncPointer)&CTestSgeDll::SendMsg,"������Ѻע���걨");
	AddFuncInfo("S150",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��Ѻ�Ǽ�ע���걨");
	AddFuncInfo("S160",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��Ѻ�Ǽ�ע���걨");
	AddFuncInfo("S200",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ���Ǽ��걨");
	AddFuncInfo("S210",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�������Ǽ��걨");
	AddFuncInfo("S220",(SgeFuncPointer)&CTestSgeDll::SendMsg,"���Ǽ��걨��ѯ");
	AddFuncInfo("S230",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ��軹��Ǽ��걨");
	AddFuncInfo("S240",(SgeFuncPointer)&CTestSgeDll::SendMsg,"������軹��Ǽ��걨");
	AddFuncInfo("S250",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��軹���걨��ѯ");
	AddFuncInfo("S260",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ��������걨");
	AddFuncInfo("S270",(SgeFuncPointer)&CTestSgeDll::SendMsg,"������������걨");
	AddFuncInfo("S280",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��������걨��ѯ");
	AddFuncInfo("S290",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ���״̬����걨");
	AddFuncInfo("S300",(SgeFuncPointer)&CTestSgeDll::SendMsg,"���״̬����걨��ѯ");
	AddFuncInfo("S310",(SgeFuncPointer)&CTestSgeDll::SendMsg,"���Ǽǲ�ѯ");
	AddFuncInfo("S320",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��軹��Ǽǲ�ѯ");
	AddFuncInfo("S410",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��軹��Ǽǲ�ѯ");
	AddFuncInfo("S420",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��滮ת��ѯ");
	AddFuncInfo("S510",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ��滥���걨");
	AddFuncInfo("S520",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ύ��滥���걨");
	AddFuncInfo("S530",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��滥���걨��ѯ");
	AddFuncInfo("S540",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��滥���Ǽǲ�ѯ");
	AddFuncInfo("S810",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��ѯ�����ÿ��仯��ˮ");
	AddFuncInfo("S820",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��ѯ���仯��ˮ");
	AddFuncInfo("S840",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��ѯ���仯��ˮ");
	AddFuncInfo("S330",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��ѯÿ������׼���ʼ���ֵ");


	//�ƽ�ETF
	AddFuncInfo("E000",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�˻�����/�ͻ���");
	AddFuncInfo("E010",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�˻����");
	AddFuncInfo("E020",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�˻�����ҵ�񱾵ر�Ų�ѯ");
	AddFuncInfo("E030",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�Ϲ�����");
	AddFuncInfo("E050",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�깺����");
	AddFuncInfo("E070",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�������");
	AddFuncInfo("E090",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����˻��󶨽������");
	AddFuncInfo("E100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����Ϲ�ȷ��֪ͨ����");
	AddFuncInfo("E110",(SgeFuncPointer)&CTestSgeDll::SendMsg,"���������嵥ϵͳ���ư汾����");
	AddFuncInfo("E120",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����嵥��ѯ����");
	AddFuncInfo("E130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����꽻�ױ��ر�Ų�ѯ");

	//�˻���
	AddFuncInfo("R000",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��Ȼ�˿ͻ�����");
	AddFuncInfo("R010",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��Ȼ�˿ͻ���Ϣ���");
	AddFuncInfo("R020",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��Ȼ�˿ͻ�ָ������");
	AddFuncInfo("R030",(SgeFuncPointer)&CTestSgeDll::SendMsg,"��Ȼ�˿ͻ�ָ�����׳���");
	AddFuncInfo("R040",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ͻ���������");
	AddFuncInfo("R050",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�ͻ���Ϣ��ѯ����");
	AddFuncInfo("R100",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����ͻ�������������");
	AddFuncInfo("R110",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����ͻ���Ϣ�������");
	AddFuncInfo("R120",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����ͻ�ָ����������");
	AddFuncInfo("R130",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����ͻ�ָ�����׳�������");
	AddFuncInfo("R140",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����ͻ�������������");
	AddFuncInfo("R150",(SgeFuncPointer)&CTestSgeDll::SendMsg,"�����ͻ���Ϣ��ѯ����");


	//���Ϳͻ����仯��ˮ  S802
	//�����걨״̬�仯��ˮ  S832
	
	//�г���Ϣ�ر����ֻ�/����/���ڣ�     B002
	//�г�״̬�ı�ر����ֻ�/����/���ڣ� B062
	//��Լ��Ϣ�ر����ֻ�/����/���ڣ�     B102 
	//��Լ����״̬�ı�ر����ֻ�/����/���ڣ� B182
	//����Ʒ�ִ�����Ϣ�ر�                 B202
	//�����ֻ����ڽ��ղ�������֪ͨ         B302
	//����������״̬֪ͨ                   B332
	//����ʵʱ���飨�ֻ�/����/���ڣ�       Q012
	//����ʵʱ����                         Q202
	//���淢��������Ӧ�𼰻ر�             Q902
	//��������Ӧ�𼰻ر����ֻ�/����/���ڣ�T202
	//��������Ӧ�𼰻ر����ֻ�/����/���ڣ�T212
	//�ɽ��ر����ֻ�/����/���ڣ�            T222
	//�����걨����Ӧ�𼰻ر�              T092
	//�����걨��������Ӧ�𼰻ر�          T102
	//�����걨�ɽ��ر�                      T112
	//�������걨����Ӧ�𼰻ر�            T122
	//�������걨��������Ӧ�𼰻ر�        T132
	
	
	//�Ϲ�ȷ��֪ͨ                          E042
	//�깺����Ӧ�𼰻ر�                  E052
	//�깺ȷ��֪ͨ                          E062
	//���ȷ��֪ͨ                          E082
	
	
	//��Ȼ�˿ͻ�������Ϣ���֪ͨ            R062
	//�����ͻ�������������Ӧ�𡢸���֪ͨ  R102
	//�����ͻ���Ϣ�����������Ӧ�𡢸���֪ͨ  R112
	//�����ͻ�ָ��������������Ӧ�𡢸���֪ͨ  R122
	//�����ͻ�ָ�����׳�����������Ӧ�𡢸���֪ͨ  R132
	//�����ͻ�������������Ӧ�𡢸���֪ͨ R142
	//�����ͻ�������Ϣ���֪ͨ             R162
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
// ������: StartApi
// ���  : ������ 2016-3-11 16:31:55
// ����  : virtual bool 
// ����  : ��ʼAPI    �������ӣ�������־
bool CTestSgeDll::StartApi()
{
	//��ʼ��
	//��������
	m_nConnectTime = time(NULL);
	//����api�߳�

	//ģ�����ӳɹ�
	api_connection_state_t constatus;
	strcpy(constatus.ip,"127.0.0.1");
	constatus.port = 9011;
	constatus.state = IS_CONNECTED;
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ģ������SGEǰ��");
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


// ������: StopApi
// ���  : ������ 2016-3-11 16:32:06
// ����  : virtual bool 
// ����  : �Ͽ����ӣ�ֹͣapi��ֹͣ��־
bool CTestSgeDll::StopApi()
{
	m_pTimer.Stop();
	m_pTimer.Join();
	m_bIsRunning = false;
	Join();
	return true;
}

// ������: Init
// ���  : ������ 2016-3-11 11:29:23
// ����  : virtual bool 
// �����������  : S_SGE_GEMS2_API *api  apiָ�룬�����ص�������api��handle��ca��handle
// �������  : CIErrlog *log     ��־ָ�룬���̳�д��־
// �������  : CBF_Xml *xml      �������Ե�xml��
// �������  : const char *xmlnode  ����̬���Ӧ��xml���ýڵ㣬������˵��
// �������  : char *errmsg  ������Ϣ
// ����  : ��ʼ��
bool CTestSgeDll::Init(S_SGE_GEMS2_API *api,CIErrlog *log,CBF_Xml *xml,const char *xmlnode,char *errmsg)
{
	bool bRet = CIOfferingBase::Init(api,log,xml,xmlnode,errmsg);
	if (!bRet)
	{
		return bRet;
	}
	//�������������ĳ�ʼ��
	char nodename[100];
	sprintf(nodename,"%s/ģ�⵵��Ŀ¼",xmlnode);
	if (xml->GetNodeValueByPath(nodename,false,m_sTestDir,false) == NULL)
	{
		sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
		return false;
	}
	sprintf(nodename,"%s/ģ�⽻������",xmlnode);
	if (xml->GetNodeValueByPath(nodename,false,m_sTestTxDate,false) == NULL)
	{
		sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
		return false;
	}
	sprintf(nodename,"%s/����ѹ������",xmlnode);
	if (xml->GetNodeValueByPath(nodename,false,m_sOrderPmt,false) == NULL)
	{
		sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
		return false;
	}

	sprintf(nodename,"%s/ģ������",xmlnode);
	CXmlNode *testquonode = xml->GetNodeByPath(nodename);
	if (testquonode == NULL)
	{
		sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
		return false;
	}
	CXmlNode *quonode = (CXmlNode *)testquonode->GetFirstChild();
	CXmlAttribute *attr=NULL;
	S_TEST_QUO squo;
	while (quonode != NULL)
	{
		
		attr = quonode->GetAttribute("��ʱ���");
		if (attr == NULL)
		{
			m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"��[��ʱ���]����");
			quonode = (CXmlNode *)quonode->getNextSibling();
			continue;
		}
		squo.nTime = atoi(attr->GetAttrValue().c_str());
		attr = quonode->GetAttribute("�����ļ�");
		if (attr == NULL)
		{
			m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"��[�����ļ�]����");
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
	
	sprintf(nodename,"%s/���ļ�����",xmlnode);
	if (xml->GetNodeAttribute(nodename,false,"use",false,m_nIsFlowRun) == NULL)
	{
		sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
		m_nIsFlowRun = 0;
	}
	if (m_nIsFlowRun == 1)
	{
		std::string flowfilepath;
		if (xml->GetNodeAttribute(nodename,false,"���ļ�Ŀ¼",false,flowfilepath,false) == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������[���ļ�Ŀ¼]δ����",nodename);
			return false;
		}
		S_FLOWFILE_INFO info;
		CXmlNode *flownode = xml->GetNodeByPath(nodename,false);
		if (flownode == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]������",nodename);
			return false;
		}
		flownode = (CXmlNode *)flownode->GetFirstChild();
		if (flownode == NULL)
		{
			sprintf(errmsg,"XML�ڵ�[%s]���ӽڵ�Ϊ�գ������ļ�δ����",nodename);
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
				sprintf(errmsg,"XML�ڵ�[%s]���ӽڵ�Ϊ��ֵΪ�գ���λ�������ļ���",nodename);
				return false;
			}
			sprintf(info.flowflename,"%s/%s",flowfilepath.c_str(),flowfilename.c_str());
			m_pFlowList.push_back(info);
			flownode = (CXmlNode *)flownode->getNextSibling();
		}
	}
	

	

	return true;
}


// ������:  SendMsg
// ���  : ������ 2016-3-11 11:34:50
// ����  : virtual int 
// ����  : const char *gtpmsg  gtp��Ϣ������������
// ����  : unsigned short gtplen
// ����  : ����ҵ������
int  CTestSgeDll::SendMsg(CGtpData *senddata)
{
	CBF_PMutex  pp(&m_mutex);
	//���Է���
	t_btime = CBF_Date_Time::GetTickUS();
	std::string smsgtype ;
	int fieldtype;
	if (senddata->GetValueByName("X03",smsgtype,fieldtype)<0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"��X03�ֶ�");
		return -1;
	}
	char stxcode[10];
	strcpy(stxcode,smsgtype.c_str());
	stxcode[3] = '1';
	char tmpchar[200];
	
	//��Ӧ��
	
	UINT64_ msgserial = 0;

	

	
	if (m_sOrderPmt.compare("1") == 0 && smsgtype.compare("T200") ==0 ) //����ѹ������
	{
		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ģ�ⷢ�� ���뱨��ѹ������ǰ��ʱ[%d]΢��",t_etime-t_btime);
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
			if (!m_pOrderAns.FromFile(tmpchar)) //��ȡ�ļ�������ݷ���
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ļ�[%s]������",tmpchar);
				senddata->SetDataItem("X40","���̻�����ģ��Ӧ�𷵻أ����ļ����巵��");//��Ӧ��Ϣ
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
			if (!m_pOrderBack.FromFile(tmpchar)) //��ȡ�ļ�������ݷ���
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ļ�[%s]������",tmpchar);
				senddata->SetDataItem("X40","���̻�����ģ��Ӧ�𷵻أ����ļ����巵��");//��Ӧ��Ϣ
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
			if (!m_pOrderDone.FromFile(tmpchar)) //��ȡ�ļ�������ݷ���
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ļ�[%s]������",tmpchar);
				senddata->SetDataItem("X40","���̻�����ģ��Ӧ�𷵻أ����ļ����巵��");//��Ӧ��Ϣ
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
			m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ģ�ⷢ�� ����������ļ���ʱ[%d]΢��",t_etime-t_btime);

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

		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ��Ӧ�� [%s]",t_sgtpdata.c_str());

		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ģ�ⷢ�� Ӧ��api_recv_msg_ǰ��ʱ[%d]΢��",t_etime-t_btime);
	
		m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
		
		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ģ�ⷢ�� ����Ӧ����ʱ[%d]΢��",t_etime-t_btime);


		//��������Ӧ�𼰻ر����ֻ�/����/���ڣ�T202
		
		senddata->SetDataItem("X03","T202");
		senddata->SetDataItem("O00",cOrderNo);
		senddata->UpdateCurValue(&m_pOrderBack,false);
		
		senddata->SetDataItem("T11",m_sTestTxDate.c_str());
		senddata->SetDataItem("O61",m_sTestTxDate.c_str());
		
		t_sgtpdata ="";
		senddata->ToString(t_sgtpdata);
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ��ر� [%s]",t_sgtpdata.c_str());

		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ģ�ⷢ�� �ر�api_recv_msg_ǰ��ʱ[%d]΢��",t_etime-t_btime);

		m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
		
		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ģ�ⷢ�� ����ر����ʱ[%d]΢��",t_etime-t_btime);
		//�ɽ��ر����ֻ�/����/���ڣ�            T222
		

		senddata->SetDataItem("X03","T222");
		senddata->SetDataItem("O00",cOrderNo);
		
		m_nDoneNo++;
		sprintf(cDoneNo,INT64PFM,m_nDoneNo);
		//�ɽ����
		senddata->SetDataItem("O60",cDoneNo);

		//��������
		int ordernum=1;
		if (senddata->GetValueByName("O07",sDoneNo,fieldtype) >= 0)
		{
			ordernum = atoi(sDoneNo.c_str());
		}
		
		//�ɽ�����
		senddata->SetDataItem("O64",ordernum);
		senddata->UpdateCurValue(&m_pOrderDone,false);

		//�ɽ�״̬����ر������У�Ҫ����
		senddata->SetDataItem("O09",m_sDoneStatus);
		
		senddata->SetDataItem("T11",m_sTestTxDate.c_str());
		senddata->SetDataItem("O61",m_sTestTxDate.c_str());
		t_sgtpdata ="";
		senddata->ToString(t_sgtpdata);
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ��ɽ��ر� [%s]",t_sgtpdata.c_str());

		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ģ�ⷢ�� Ӧ��api_recv_msg_ǰ��ʱ[%d]΢��",t_etime-t_btime);
	
		m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
		
		t_etime = CBF_Date_Time::GetTickUS();
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"ģ�ⷢ�� ����ɽ��ر����ʱ[%d]΢��",t_etime-t_btime);

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

	if (!fdata.FromFile(tmpchar)) //��ȡ�ļ�������ݷ���
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ļ�[%s]������",tmpchar);
		senddata->SetDataItem("X40","���̻�����ģ��Ӧ�𷵻أ����ļ����巵��");//��Ӧ��Ϣ
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
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ��Ӧ�� [%s]",t_sgtpdata.c_str());
	m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
	
	//���ж��Ƿ���Ҫ�ر������ر�����ļ�������

	stxcode[3] = '2';

	if (m_sTestDir.length()>0)
	{
		sprintf(tmpchar,"%s/%s.txt",m_sTestDir.c_str(),stxcode);
	}
	else
	{
		sprintf(tmpchar,"%s.txt",stxcode);
	}
	
	//���Ϳͻ����仯��ˮ  S802
	//�����걨״̬�仯��ˮ  S832

	//�г���Ϣ�ر����ֻ�/����/���ڣ�     B002
	//�г�״̬�ı�ر����ֻ�/����/���ڣ� B062
	//��Լ��Ϣ�ر����ֻ�/����/���ڣ�     B102 
	//��Լ����״̬�ı�ر����ֻ�/����/���ڣ� B182
	//����Ʒ�ִ�����Ϣ�ر�                 B202
	//�����ֻ����ڽ��ղ�������֪ͨ         B302
	//����������״̬֪ͨ                   B332
	//����ʵʱ���飨�ֻ�/����/���ڣ�       Q012
	//����ʵʱ����                         Q202
	//���淢��������Ӧ�𼰻ر�             Q902
	//��������Ӧ�𼰻ر����ֻ�/����/���ڣ�T202
	//��������Ӧ�𼰻ر����ֻ�/����/���ڣ�T212
	//�ɽ��ر����ֻ�/����/���ڣ�            T222
	//�����걨����Ӧ�𼰻ر�              T092
	//�����걨��������Ӧ�𼰻ر�          T102
	//�����걨�ɽ��ر�                      T112
	//�������걨����Ӧ�𼰻ر�            T122
	//�������걨��������Ӧ�𼰻ر�        T132


	//�Ϲ�ȷ��֪ͨ                          E042
	//�깺����Ӧ�𼰻ر�                  E052
	//�깺ȷ��֪ͨ                          E062
	//���ȷ��֪ͨ                          E082


	//��Ȼ�˿ͻ�������Ϣ���֪ͨ            R062
	//�����ͻ�������������Ӧ�𡢸���֪ͨ  R102
	//�����ͻ���Ϣ�����������Ӧ�𡢸���֪ͨ  R112
	//�����ͻ�ָ��������������Ӧ�𡢸���֪ͨ  R122
	//�����ͻ�ָ�����׳�����������Ӧ�𡢸���֪ͨ  R132
	//�����ͻ�������������Ӧ�𡢸���֪ͨ R142
	//�����ͻ�������Ϣ���֪ͨ             R162
	if (!m_backIndex.Find(stxcode))
	{
		return 1;
	}
	if (!fdata.FromFile(tmpchar)) //��ȡ�ļ�������ݷ���
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ļ�[%s]������",tmpchar);
		senddata->SetDataItem("X40","���̻�����ģ��ر����أ����ļ����巵��");//��Ӧ��Ϣ
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
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ��ر� [%s]",t_sgtpdata.c_str());
	m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
	

	
	//���ж��Ƿ���Ҫ�ɽ��ر������ر�����ļ�������
	//��������Ӧ�𼰻ر����ֻ�/����/���ڣ�T202
	//��������Ӧ�𼰻ر����ֻ�/����/���ڣ�T212
	//�ɽ��ر����ֻ�/����/���ڣ�            T222
	//�����걨����Ӧ�𼰻ر�              T092
	//�����걨��������Ӧ�𼰻ر�          T102
	//�����걨�ɽ��ر�                      T112
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

	if (!fdata.FromFile(tmpchar)) //��ȡ�ļ�������ݷ���
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ļ�[%s]������",tmpchar);
		senddata->SetDataItem("X40","���̻�����ģ��ر����أ����ļ����巵��");//��Ӧ��Ϣ
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
		//�ɽ����
		senddata->SetDataItem("O60",cDoneNo);

		//��������
		int ordernum=1;
		if (senddata->GetValueByName("O07",sDoneNo,fieldtype) >= 0)
		{
			ordernum = atoi(sDoneNo.c_str());
		}
		
		//�ɽ�����
		senddata->SetDataItem("O64",ordernum);
		senddata->UpdateCurValue(&fdata,false);
	}
	senddata->SetDataItem("T11",m_sTestTxDate.c_str());
	senddata->SetDataItem("O61",m_sTestTxDate.c_str());
	
	t_sgtpdata="";
	senddata->ToString(t_sgtpdata);
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ��ɽ��ر� [%s]",t_sgtpdata.c_str());
	m_apiPoint->apistruct->cb_.api_recv_msg_(t_sgtpdata.c_str(),GTP_TYPE_STRING,t_sgtpdata.length(),m_apiPoint->apistruct);
	

	return 0;
}

// ������: CB_Connected
// ���  : ������ 2016-3-11 15:44:49
// ����  : virtual bool 
// ����  : api_connection_state_t * cs   ����״̬
// ����  : S_SGE_GEMS2_API_STRUCT *ctx   api����
// ����  : API�Ļص����������ӳɹ��ˣ�Ҫ�����淢��¼
bool CTestSgeDll::CB_Connected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
{
	bool bRet = CIOfferingBase::CB_Connected(cs,ctx);
	if (!bRet)
	{
		return bRet;
	}
	return true;
}

// ������: CB_Disconnected
// ���  : ������ 2016-3-11 15:44:43
// ����  : virtual bool 
// ����  : api_connection_state_t * cs
// ����  : S_SGE_GEMS2_API_STRUCT *ctx
// ����  : api�ص����� �Ͽ�������  Ҫ�ͷ�api�������Ա��ٴ�����
bool CTestSgeDll::CB_Disconnected(api_connection_state_t * cs,S_SGE_GEMS2_API_STRUCT *ctx)
{
	bool bRet = CIOfferingBase::CB_Disconnected(cs,ctx);
	if (!bRet)
	{
		return bRet;
	}
	//����¼���ر�
	
	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	gtpdata.SetDataItem("X02","0000");//����
	if (m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X03","A311");//��Ϣ����
	}
	else
	{
		gtpdata.SetDataItem("X03","A111");//��Ϣ����
	}
	
	gtpdata.SetDataItem("X04","1");//��������
	gtpdata.SetDataItem("X05","1");//��Ϣ���к�
	gtpdata.SetDataItem("X06","L");//��Ϣ��������־
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��
	
	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա����
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ��
	gtpdata.SetDataItem("X39","RSP000000");//��Ӧ��
	gtpdata.SetDataItem("X40","api�Ͽ�����");//��Ӧ��Ϣ
	std::string sLogGtp;
	if (gtpdata.ToString(sLogGtp))
	{
		m_apiPoint->apistruct->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),m_apiPoint->apistruct);
	}
	return true;
}

// ������: Uncrypt
// ���  : ������ 2016-3-11 16:29:31
// ����  : virtual bool 
// ����  : S_SGE_GEMS2_API_STRUCT *ctx  api����
// ����  : const char *cryptmsg         �����ܵ�����
// ����  : int msglen                   �����ܵ����ݳ���
// ����  : char *gtpmsg                 ���ܺ������
// ����  : int &gtpmsglen               ���ܺ�����ݳ���
// ����  : ����
bool CTestSgeDll::Uncrypt(S_SGE_GEMS2_API_STRUCT *ctx,const char *cryptmsg,int msglen,char *gtpmsg,int &gtpmsglen)
{
	return true;
}
void CTestSgeDll::TradeLogout()
{

}
// ������: TradeLogin
// ���  : ������ 2016-4-14 14:21:55
// ����  : virtual void 
// ����  : ����Ա��¼
void CTestSgeDll::TradeLogin()
{
	//ͨ���ϵ���GTP��¼����
	CGtpData gtpdata;

	m_nLoginNum++;

	gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	gtpdata.SetDataItem("X02",0);//����
	if (m_sNodeType.compare("12") == 0)  //etf
	{
		gtpdata.SetDataItem("X03","A300");//��Ϣ����
	}
	else
	{
		gtpdata.SetDataItem("X03","A100");//��Ϣ����
	}
	
	gtpdata.SetDataItem("X04","0");//��������
	gtpdata.SetDataItem("X05","0");//��Ϣ���к�
	gtpdata.SetDataItem("X06","L");//��Ϣ��������־
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08","send");//���ͷ���ʶ��
	gtpdata.SetDataItem("X09","recv");//���շ���ʶ��

	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա����
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ��

	gtpdata.SetDataItem("M62","xxxx");//��¼����
	gtpdata.SetDataItem("X50","127.0.0.1");//ip��ַ
	gtpdata.SetDataItem("X55","v1.0");//API�汾��Ϣ
 	gtpdata.SetDataItem("X20","1");//�ϵ���Ϣ
 	gtpdata.SetDataItem("X80","1");//��ȫ��Ϣ��
 	gtpdata.SetDataItem("X81","1");//��ȫ��Ϣ�򳤶�
	gtpdata.SetDataItem("T13",m_sTestTxDate.c_str());//��������
	//�ص���¼����Ӧ
	
	if (m_sNodeType.compare("12") == 0)  //etf
	{
		gtpdata.SetDataItem("X03","A301");//��Ϣ����
	}
	else
	{
		gtpdata.SetDataItem("X03","A101");//��Ϣ����
	}
	CBF_Date_Time pdata;
	
	
	gtpdata.SetDataItem("O14","1");//��󱾵ر�����
	gtpdata.SetDataItem("X39","RSP000000");//��Ӧ����
	gtpdata.SetDataItem("X40","���̻�����ģ�⽻��Ա��¼����");//��Ӧ��Ϣ

	//��Ϊ���ļ���ȡ���� 
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
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"%s�ļ�������",tmpchar);
		gtpdata.SetDataItem("X40","���̻�����ģ�⽻��Ա��¼���أ����ļ����巵��");//��Ӧ��Ϣ
	}
	else
	{
		gtpdata.UpdateCurValue(&fdata,false);
	}

	std::string sgtpdata;
	gtpdata.ToString(sgtpdata);
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ�⽻��Ա��¼ [%s]",sgtpdata.c_str());
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
	//��Ϊ���ļ���ȡ���� 
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
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ģ�����飬�ļ�[%s]��ʼ����",tmpchar);
			if (!m_vTestQuoGtp[id].quodata.FromFile(tmpchar))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ģ�����飬%s�ļ�������",tmpchar);
				return;
			}
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ģ�����飬�ļ�[%s]�������",tmpchar);
			m_vTestQuoGtp[id].m_bIsReadQuoFile = true;
			nRet = m_vTestQuoGtp[id].quodata.GetValueByName("X05",sdatastr,fieldtype);
			if (nRet <0)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X05 ��Ϣ���к��ֶλ����Ͳ���");
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
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������Q52�ֶΣ�����Q52����");
			sgtpdata = "";
			m_vTestQuoGtp[id].quodata.ToString(sgtpdata);
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ�ⷢ�ͷ����� [%s]",sgtpdata.c_str());
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
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ�ⷢ������ [%s]",sgtpdata.c_str());
		m_apiPoint->apistruct->cb_.api_recv_msg_(sgtpdata.c_str(),GTP_TYPE_STRING,sgtpdata.length(),m_apiPoint->apistruct);
		return;
	}


	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ģ�����飬�ļ�[%s]��ʼ����",tmpchar);
	if (!fdata.FromFile(tmpchar))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ģ�����飬%s�ļ�������",tmpchar);
		return;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ģ�����飬�ļ�[%s]�������",tmpchar);
	
	nRet = fdata.GetValueByName("X05",sdatastr,fieldtype);
	if (nRet <0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"GTP���ݰ���X05 ��Ϣ���к��ֶλ����Ͳ���");
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
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������Q52�ֶΣ�����Q52����");
		fdata.ToString(sgtpdata);
		m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ�ⷢ�ͷ����� [%s]",sgtpdata.c_str());
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
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"��ʼģ�ⷢ������ [%s]",sgtpdata.c_str());
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
				m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"��[%s]�ļ�",m_pFlowList[i].flowflename);
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
			nRet = fseek(m_pFlowList[i].pFlowFp,16,1);//�Ƶ����+���������
			if (nRet != 0) //��β��
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
					m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"����[%s]���� [%s]",m_pFlowList[i].flowflename,data.sBuffer);
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
	
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�Ͽ�api���� api_disconnect");
	//����¼���ر�
	
	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	gtpdata.SetDataItem("X02","0000");//����
	if (m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X03","A311");//��Ϣ����
	}
	else
	{
		gtpdata.SetDataItem("X03","A111");//��Ϣ����
	}
	
	gtpdata.SetDataItem("X04","1");//��������
	gtpdata.SetDataItem("X05","1");//��Ϣ���к�
	gtpdata.SetDataItem("X06","L");//��Ϣ��������־
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��
	
	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա����
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ��
	gtpdata.SetDataItem("X39","RSP000000");//��Ӧ��
	gtpdata.SetDataItem("X40","api�Ͽ�����");//��Ӧ��Ϣ
	std::string sLogGtp;
	if (gtpdata.ToString(sLogGtp))
	{
		m_apiPoint->apistruct->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),m_apiPoint->apistruct);
	}
}
