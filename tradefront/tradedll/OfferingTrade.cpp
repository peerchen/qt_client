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
	//���۽��׽ӿ�
	AddFuncInfo("A130",(SgeFuncPointer)&COfferingTrade::SendMsg,"����Ա�����޸�");
	AddFuncInfo("A320",(SgeFuncPointer)&COfferingTrade::SendMsg,"Ӧ�������޸�");
	AddFuncInfo("B320",(SgeFuncPointer)&COfferingTrade::SendMsg,"���ӷ��ʲ�ѯ");
	AddFuncInfo("B340",(SgeFuncPointer)&COfferingTrade::SendMsg,"������״̬��ѯ");
	AddFuncInfo("T430",(SgeFuncPointer)&COfferingTrade::SendMsg,"ϯλ�ͻ���ѯ");
	AddFuncInfo("T440",(SgeFuncPointer)&COfferingTrade::SendMsg,"ϯλ�ֲֲ�ѯ");
	AddFuncInfo("T450",(SgeFuncPointer)&COfferingTrade::SendMsg,"ϯλ�ʽ��ѯ");
	AddFuncInfo("T460",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ͻ��ֲֲ�ѯ");
	AddFuncInfo("T470",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ͻ�����ѯ");
	AddFuncInfo("Q090",(SgeFuncPointer)&COfferingTrade::SendMsg,"����ʵʱ�����ѯ");
	AddFuncInfo("Q100",(SgeFuncPointer)&COfferingTrade::SendMsg,"���׷��������ѯ");
	AddFuncInfo("Q200",(SgeFuncPointer)&COfferingTrade::SendMsg,"����ʵʱ����");
	AddFuncInfo("Q900",(SgeFuncPointer)&COfferingTrade::SendMsg,"���淢��");
	AddFuncInfo("Q910",(SgeFuncPointer)&COfferingTrade::SendMsg,"���淢��");
	AddFuncInfo("Q900",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����������ѯ");
	AddFuncInfo("T200",(SgeFuncPointer)&COfferingTrade::SendMsg,"��������");
	AddFuncInfo("T210",(SgeFuncPointer)&COfferingTrade::SendMsg,"��������");
	AddFuncInfo("T230",(SgeFuncPointer)&COfferingTrade::SendMsg,"������ѯ");
	AddFuncInfo("T240",(SgeFuncPointer)&COfferingTrade::SendMsg,"���ر�����ѯ");
	AddFuncInfo("T250",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ɽ�����ѯ");
	AddFuncInfo("T090",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����걨");
	AddFuncInfo("T100",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����걨����");
	AddFuncInfo("T120",(SgeFuncPointer)&COfferingTrade::SendMsg,"�������걨");
	AddFuncInfo("T130",(SgeFuncPointer)&COfferingTrade::SendMsg,"�������걨����");
	AddFuncInfo("T400",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����걨������ѯ");
	AddFuncInfo("T410",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����걨�ɽ���ѯ");
	AddFuncInfo("T420",(SgeFuncPointer)&COfferingTrade::SendMsg,"�������걨������ѯ");
	
	//�ʽ�ִ��ӿ�
	AddFuncInfo("F010",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ʽ𻮲�");
	AddFuncInfo("F020",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����˲�ѯ");
	AddFuncInfo("F900",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����ʽ�����");
	AddFuncInfo("F910",(SgeFuncPointer)&COfferingTrade::SendMsg,"�޸��ʽ�����");
	AddFuncInfo("F920",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����ʽ�����");
	AddFuncInfo("S000",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����������");
	AddFuncInfo("S010",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����������");
	AddFuncInfo("S020",(SgeFuncPointer)&COfferingTrade::SendMsg,"��������ѯ");
	AddFuncInfo("S030",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����������");
	AddFuncInfo("S100",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ��Ѻ�걨");
	AddFuncInfo("S110",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ��Ѻ�걨");
	AddFuncInfo("S120",(SgeFuncPointer)&COfferingTrade::SendMsg,"��Ѻ�걨��ѯ");
	AddFuncInfo("S130",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ��Ѻע���걨");
	AddFuncInfo("S140",(SgeFuncPointer)&COfferingTrade::SendMsg,"������Ѻע���걨");
	AddFuncInfo("S150",(SgeFuncPointer)&COfferingTrade::SendMsg,"��Ѻ�Ǽ�ע���걨");
	AddFuncInfo("S160",(SgeFuncPointer)&COfferingTrade::SendMsg,"��Ѻ�Ǽ�ע���걨");
	AddFuncInfo("S200",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ���Ǽ��걨");
	AddFuncInfo("S210",(SgeFuncPointer)&COfferingTrade::SendMsg,"�������Ǽ��걨");
	AddFuncInfo("S220",(SgeFuncPointer)&COfferingTrade::SendMsg,"���Ǽ��걨��ѯ");
	AddFuncInfo("S230",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ��軹��Ǽ��걨");
	AddFuncInfo("S240",(SgeFuncPointer)&COfferingTrade::SendMsg,"������軹��Ǽ��걨");
	AddFuncInfo("S250",(SgeFuncPointer)&COfferingTrade::SendMsg,"��軹���걨��ѯ");
	AddFuncInfo("S260",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ��������걨");
	AddFuncInfo("S270",(SgeFuncPointer)&COfferingTrade::SendMsg,"������������걨");
	AddFuncInfo("S280",(SgeFuncPointer)&COfferingTrade::SendMsg,"��������걨��ѯ");
	AddFuncInfo("S290",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ���״̬����걨");
	AddFuncInfo("S300",(SgeFuncPointer)&COfferingTrade::SendMsg,"���״̬����걨��ѯ");
	AddFuncInfo("S310",(SgeFuncPointer)&COfferingTrade::SendMsg,"���Ǽǲ�ѯ");
	AddFuncInfo("S320",(SgeFuncPointer)&COfferingTrade::SendMsg,"��軹��Ǽǲ�ѯ");
	AddFuncInfo("S410",(SgeFuncPointer)&COfferingTrade::SendMsg,"��軹��Ǽǲ�ѯ");
	AddFuncInfo("S420",(SgeFuncPointer)&COfferingTrade::SendMsg,"��滮ת��ѯ");
	AddFuncInfo("S510",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ��滥���걨");
	AddFuncInfo("S520",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ύ��滥���걨");
	AddFuncInfo("S530",(SgeFuncPointer)&COfferingTrade::SendMsg,"��滥���걨��ѯ");
	AddFuncInfo("S540",(SgeFuncPointer)&COfferingTrade::SendMsg,"��滥���Ǽǲ�ѯ");
	AddFuncInfo("S810",(SgeFuncPointer)&COfferingTrade::SendMsg,"��ѯ�����ÿ��仯��ˮ");
	AddFuncInfo("S820",(SgeFuncPointer)&COfferingTrade::SendMsg,"��ѯ���仯��ˮ");
	AddFuncInfo("S840",(SgeFuncPointer)&COfferingTrade::SendMsg,"��ѯ���仯��ˮ");
	AddFuncInfo("S330",(SgeFuncPointer)&COfferingTrade::SendMsg,"��ѯÿ������׼���ʼ���ֵ");
	
	
	//�ƽ�ETF
	AddFuncInfo("E000",(SgeFuncPointer)&COfferingTrade::SendMsg,"�˻�����/�ͻ���");
	AddFuncInfo("E010",(SgeFuncPointer)&COfferingTrade::SendMsg,"�˻����");
	AddFuncInfo("E020",(SgeFuncPointer)&COfferingTrade::SendMsg,"�˻�����ҵ�񱾵ر�Ų�ѯ");
	AddFuncInfo("E030",(SgeFuncPointer)&COfferingTrade::SendMsg,"�Ϲ�����");
	AddFuncInfo("E050",(SgeFuncPointer)&COfferingTrade::SendMsg,"�깺����");
	AddFuncInfo("E070",(SgeFuncPointer)&COfferingTrade::SendMsg,"�������");
	AddFuncInfo("E090",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����˻��󶨽������");
	AddFuncInfo("E100",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����Ϲ�ȷ��֪ͨ����");
	AddFuncInfo("E110",(SgeFuncPointer)&COfferingTrade::SendMsg,"���������嵥ϵͳ���ư汾����");
	AddFuncInfo("E120",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����嵥��ѯ����");
	AddFuncInfo("E130",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����꽻�ױ��ر�Ų�ѯ");
	
	//�˻���
	AddFuncInfo("R000",(SgeFuncPointer)&COfferingTrade::SendMsg,"��Ȼ�˿ͻ�����");
	AddFuncInfo("R010",(SgeFuncPointer)&COfferingTrade::SendMsg,"��Ȼ�˿ͻ���Ϣ���");
	AddFuncInfo("R020",(SgeFuncPointer)&COfferingTrade::SendMsg,"��Ȼ�˿ͻ�ָ������");
	AddFuncInfo("R030",(SgeFuncPointer)&COfferingTrade::SendMsg,"��Ȼ�˿ͻ�ָ�����׳���");
	AddFuncInfo("R040",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ͻ���������");
	AddFuncInfo("R050",(SgeFuncPointer)&COfferingTrade::SendMsg,"�ͻ���Ϣ��ѯ����");
	AddFuncInfo("R100",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����ͻ�������������");
	AddFuncInfo("R110",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����ͻ���Ϣ�������");
	AddFuncInfo("R120",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����ͻ�ָ����������");
	AddFuncInfo("R130",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����ͻ�ָ�����׳�������");
	AddFuncInfo("R140",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����ͻ�������������");
	AddFuncInfo("R150",(SgeFuncPointer)&COfferingTrade::SendMsg,"�����ͻ���Ϣ��ѯ����");

}

COfferingTrade::~COfferingTrade()
{
	if (m_apiPoint->apistruct->safe_handle_!= NULL)
	{
		//�ͷ�ca
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
// 	//20170328 ���ӵ��˳�ʱ������api��־
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
// 	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���api��־ system����[0x%x]",status);
// 	SLEEP_SECONDS(2);
//     if (-1 == status)  
//     {  
// 		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����system���� %s",cmd);
// 		return ;
//     }  
//     else  
//     {  
// #ifdef  LINUX	
//         if (WIFEXITED(status))  
//         {  
//             if (0 == WEXITSTATUS(status))  
//             {  
//                 m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���api��־�ɹ�");
//             }  
//             else  
//             {  
// 				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���api��־����shell�ű�ʧ�� %d",WEXITSTATUS(status));
// 				return ;
//             }  
//         }  
//         else  
//         {  
// 			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���api��־ ����[%d]",WEXITSTATUS(status));
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
	//��������ֶν��ܳ�����
	if (m_nPwdFlag == 1)
	{
		char  xmlnodepath2[200];
		sprintf(xmlnodepath2,"%s/�������ģʽ",xmlnode);
		int encryptflag=0;
		if (xml->GetNodeValueByPath(xmlnodepath2,false,encryptflag) == NULL)
		{
			sprintf(errmsg,"�����ļ�[%s]������,Ĭ��Ϊ0",xmlnodepath2);
			m_pLog->LogMp(LOG_PROMPT,__FILE__,__LINE__,errmsg);
			encryptflag =0;
		}
		
		
		//����Ա����
		char tmpchar[300];
		bzero(tmpchar,sizeof(tmpchar));
		if (encryptflag != 0)  //3DES��ʽ
		{
			CBF_3Des pDes;
			strcpy(tmpchar,m_sTradePwd.c_str());
			int buflen = strlen(tmpchar);
			if (!pDes.UnDes3Buffer(tmpchar,buflen,DBPWD3DESKEY,errmsg))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա������ܳ��� %s",errmsg);
				return false;
			}
			tmpchar[buflen]=0;
			m_sTradePwd = tmpchar;	
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sTradePwd=%s",m_sTradePwd.c_str());
			
			
			//֤������
			bzero(tmpchar,sizeof(tmpchar));
			strcpy(tmpchar,m_sCertPwd.c_str());
			buflen = strlen(tmpchar);
			if (!pDes.UnDes3Buffer(tmpchar,buflen,DBPWD3DESKEY,errmsg))
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"֤��������ܳ��� %s",errmsg);
				return false;
			}
			tmpchar[buflen]=0;
			
			m_sCertPwd = tmpchar;	
			
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sCertPwd=%s",m_sCertPwd.c_str());
			
			if (m_sSeatPwd.length()>0)
			{
				//ϯλ����
				bzero(tmpchar,sizeof(tmpchar));
				strcpy(tmpchar,m_sSeatPwd.c_str());
				buflen = strlen(tmpchar);
				if (!pDes.UnDes3Buffer(tmpchar,buflen,DBPWD3DESKEY,errmsg))
				{
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ϯλ������ܳ��� %s",errmsg);
					return false;
				}
				tmpchar[buflen]=0;
				m_sSeatPwd = tmpchar;	
				m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sSeatPwd=%s",m_sSeatPwd.c_str());
			}
		}
		else  //des��ʽ
		{
			CBF_Des       pDes;
			strcpy(tmpchar,m_sTradePwd.c_str());
			int buflen = strlen(tmpchar);
			if (pDes.Uncryptchar(tmpchar,buflen,DBPWDKEY)<=0)
			{
				sprintf(errmsg,"����Ա������ܳ���");
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
				return false;
			}
			tmpchar[buflen]=0;
			m_sTradePwd = tmpchar;	
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sTradePwd=%s",m_sTradePwd.c_str());
			
			
			//֤������
			bzero(tmpchar,sizeof(tmpchar));
			strcpy(tmpchar,m_sCertPwd.c_str());
			buflen = strlen(tmpchar);
			if (pDes.Uncryptchar(tmpchar,buflen,DBPWDKEY)<=0)
			{
				sprintf(errmsg,"֤��������ܳ���");
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
				return false;
			}
			tmpchar[buflen]=0;
			
			m_sCertPwd = tmpchar;	
			
			m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sCertPwd=%s",m_sCertPwd.c_str());
			
			if (m_sSeatPwd.length()>0)
			{
				//ϯλ����
				bzero(tmpchar,sizeof(tmpchar));
				strcpy(tmpchar,m_sSeatPwd.c_str());
				buflen = strlen(tmpchar);
				if (pDes.Uncryptchar(tmpchar,buflen,DBPWDKEY)<=0)
				{
					sprintf(errmsg,"ϯλ������ܳ���");
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
					return false;
				}
				tmpchar[buflen]=0;
				m_sSeatPwd = tmpchar;	
				m_pLog->LogMp(LOG_DEBUG+1,__FILE__,__LINE__,"m_sSeatPwd=%s",m_sSeatPwd.c_str());
			}
		}
		
		
	}
	if (m_sNodeType.compare("12") ==0) //ETF���̻�
	{
		char xmlnodepath[100];
		sprintf(xmlnodepath,"%s/��Ա����",xmlnode);
		if (xml->GetNodeValueByPath(xmlnodepath,false,m_sMemberId,false) == NULL)
		{
			sprintf(errmsg,"�����ļ�[%s]������",xmlnodepath);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		sprintf(xmlnodepath,"%s/��������",xmlnode);
		if (xml->GetNodeValueByPath(xmlnodepath,false,m_sOrganType,false) == NULL)
		{
			sprintf(errmsg,"�����ļ�[%s]������",xmlnodepath);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		sprintf(xmlnodepath,"%s/ETF��������",xmlnode);
		if (xml->GetNodeValueByPath(xmlnodepath,false,m_sTradeDate,false) == NULL)
		{
			sprintf(errmsg,"�����ļ�[%s]������",xmlnodepath);
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
			return false;
		}
		
	}
	char xmlnodeencryptflag[100];
	sprintf(xmlnodeencryptflag,"%s/���ͽ���������",xmlnode);
	if (xml->GetNodeValueByPath(xmlnodeencryptflag,false,m_nEncryptFlag) == NULL)
	{
		sprintf(errmsg,"�����ļ�[%s]������",xmlnodeencryptflag);
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
	sprintf(xmlnodeencryptflag,"%s/����ϵ�",xmlnode);
	if (xml->GetNodeValueByPath(xmlnodeencryptflag,false,m_nQuotaBreak) == NULL)
	{
		sprintf(errmsg,"�����ļ�[%s]������",xmlnodeencryptflag);
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		m_nQuotaBreak =0;
	}
	
	//�򿪶�̬��
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
		sprintf(errmsg,"�򿪶�̬��%sʧ��",dlleasy.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
	m_pDllApiHandle = LOADDLL(dllname.c_str());
#ifdef _WINDOWS
	if (ISNOTOPEN(m_pDllApiHandle))
	{
		sprintf(errmsg,"�򿪶�̬��%sʧ�� ������%d",dllname.c_str(),GetLastError());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#else
	char *err = dlerror();
	if (err != NULL)
	{
		sprintf(errmsg,"�򿪶�̬��%sʧ�� ����[%s]",dllname.c_str(),err);
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
        sprintf(errmsg,"ȡ��̬��[%s]��ĺ�����ַʧ��",dllname.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
        return false;
    }
	m_pApiShca = LOADDLL(dllshca.c_str());
	if (ISNOTOPEN(m_pApiShca))
	{
		sprintf(errmsg,"�򿪶�̬��%sʧ��",dllshca.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
	m_pDllCaApiHandle = LOADDLL(dllcaname.c_str());
#ifdef _WINDOWS
	if (ISNOTOPEN(m_pDllCaApiHandle))
	{
		sprintf(errmsg,"�򿪶�̬��%sʧ�� ������%d",dllcaname.c_str(),GET_LAST_SOCK_ERROR());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#else
	err = dlerror();
	if (err != NULL)
	{
		sprintf(errmsg,"�򿪶�̬��%sʧ�� ����[%s]",dllcaname.c_str(),err);
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
#endif
// 	if (ISNOTOPEN(m_pDllCaApiHandle))
// 	{
// 		sprintf(errmsg,"�򿪶�̬��[%s]ʧ��",dllcaname.c_str());
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
        sprintf(errmsg,"ȡ��̬��[%s]��ĺ�����ַʧ��",dllcaname.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
        return false;
    }

// 	}
// 	std::string   m_sPath_key;//UserKey.key�ļ�·�� ��˽Կ
// 	std::string   m_sPath_user;//UserCert.der�ļ�·��
// 	std::string   m_sPath_root;//RootCert.der�ļ�·��
// 	std::string   m_sPath_svr;//server.der�ļ�·��
// 	std::string   m_sCertPwd;//֤������

// 	    key_path��		UserKey.key�ļ�·��
// 		rootcert_path��	RootCert.der�ļ�·��
// 		svr_cert_path��	server.der�ļ�·��
// 		cli_cert_path��	UserCert.der�ļ�·��
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"key_path[%s] rootcert_path��[%s] svr_cert_path��[%s] cli_cert_path��[%s]",\
		m_sPath_key.c_str(),m_sPath_root.c_str(),m_sPath_svr.c_str(),m_sPath_user.c_str());
    m_apiPoint->apistruct->safe_handle_ =	m_pPoint.ca_api_safe_init(m_sPath_key.c_str(),m_sPath_root.c_str(),m_sPath_svr.c_str(),m_sPath_user.c_str(),m_sCertPwd.c_str());
	if(m_apiPoint->apistruct->safe_handle_ == NULL)
	{
		sprintf(errmsg,"ca_api_safe_init[%s]��ʼ��ʧ�� key_path[%s] rootcert_path��[%s] svr_cert_path��[%s] cli_cert_path��[%s]",\
			m_sPath_key.c_str(),m_sPath_root.c_str(),m_sPath_svr.c_str(),m_sPath_user.c_str());
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}
	//���ɰ�ȫ��Ϣ
	m_sSgeSafeInfo = (char *)calloc(8192, 1); 
	if (m_sSgeSafeInfo == NULL)
	{
		sprintf(errmsg,"����CA��ȫ��Ϣ�ռ�ʧ��");
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,errmsg);
		return false;
	}

	m_bIsInit = true;
	return true;
}
int  COfferingTrade::SendMsg(CGtpData *senddata)
{
	//�ж������Ƿ�����
	if (m_nApiStatus != 1 || m_nApiLoginStatus != 1)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������״̬Ϊδ���ӻ�δ��¼");
		return -1;
	}
	CBF_PMutex pp(&m_mutex);
	senddata->SetDataItem("X08",m_sSendFlag.c_str());
	senddata->SetDataItem("X09",m_sRcvFlag.c_str());
	//��������
	char sendBuffer[8192];
	size_t  sendlen=8192;
	std::string gtpstring;
	if (!senddata->ToString(gtpstring))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ToString����");
		return -1;
	}
	
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"Ҫ���͵�GTP���� [%s]",gtpstring.c_str());
	int ret;
	if (m_nEncryptFlag == 1)
	{
		try
		{
			
			ret = m_pPoint.ca_api_safe_encrypt(m_apiPoint->apistruct->safe_handle_, (const unsigned char *)gtpstring.c_str(), gtpstring.length(), (unsigned char *)sendBuffer, &sendlen);
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����ca_api_safe_encrypt �쳣���� %d",ret);
			return -1;	
		}
		
		if (ret < 0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ca_api_safe_encrypt ���ܳ��� %d",ret);
			return -1;
		}
		try
		{
			ret = m_pPoint.api_send_msg(m_apiPoint->apistruct->api_, sendBuffer, sendlen);
		}
		catch (...)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����api_send_msg �쳣���� %d",ret);
			return -1;	
		}
		
		if (ret <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"api_send_msg ���ͳ��� %d",ret);
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
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����api_send_msg �쳣���� %d",ret);
			return -1;	
		}
		
		if (ret <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"api_send_msg ���ͳ��� %d",ret);
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
		//��������
		//(api_safe_handle_t handle, const unsigned char *src, const size_t len, unsigned char *dst, size_t *cap);
		int ret =  m_pPoint.ca_api_safe_decrypt(m_apiPoint->apistruct->safe_handle_,(const unsigned char *)cryptmsg,msglen,(unsigned char *)gtpmsg,&dstmsglen);
		if (ret <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ܳ��� %d",ret);
			return false;
		}
		gtpmsglen = dstmsglen;
		return true;
	}
	else
	{
		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"Uncrypt ���ز��Ǳ�API��");
		return false;
	}
}

bool COfferingTrade::StartApi()
{
	char sIp[40];
	int  nPort;
	if (!GetFrontIpPort(sIp,nPort))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�޽�����ǰ��IP���˿�");
        return false;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"�������ӵĽ�����ǰ�ö˿�[%s %d]",sIp,nPort);

	CBF_PMutex pp(&m_mutex);
    //��ʼ��api    
	m_apiPoint->apistruct->api_ = m_pPoint.api_init(sIp, nPort, &(m_apiPoint->apistruct->cb_), m_apiPoint->apistruct);
	if(m_apiPoint->apistruct->api_ == NULL) 
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������api_init����");
        return false;
	}
	m_nSgeSafeInfoLen = 8192;
	int ret = m_pPoint.ca_api_safe_create_client_info(m_apiPoint->apistruct->safe_handle_ , m_sSgeSafeInfo, m_nSgeSafeInfoLen);
	if (ret <= 0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"ca_api_safe_create_client_info ���ɰ�ȫ��Ϣʧ�� [%d]",ret);
		return false;
	}
	m_nSgeSafeInfoLen = ret;
	
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"֤�鰲ȫ��Ϣ [%s] ����[%d]",m_sSgeSafeInfo,m_nSgeSafeInfoLen);


	//����api�߳�
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
	
	//���ͽ���Ա¼��ָ��
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
		//ֹͣapi�߳�
		m_pPoint.api_thread_end(m_apiPoint->apistruct->api_);
		//�ȴ��߳���ֹ
		printf("��ʼapi_stop\n");
		m_pPoint.api_stop(m_apiPoint->apistruct->api_);
		m_pPoint.api_wait(m_apiPoint->apistruct->api_);
		printf("����api_stop\n");
		m_bIsStop = true;
		
	}

	if (m_apiPoint->apistruct->api_ != NULL)
	{
		//�ͷ�api
		m_pPoint.api_free(m_apiPoint->apistruct->api_);
		m_apiPoint->apistruct->api_ = NULL;
	}
	return true;
}

void COfferingTrade::TradeLogout()
{
	//���������ʱ��
	if (!m_bIsInit)
	{
		return ;
	}
	//��gtp����
	CBF_PMutex pp(&m_mutex);

	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	gtpdata.SetDataItem("X02","0000");//����
	if (m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X03","A310");//��Ϣ����
	}
	else
	{
		gtpdata.SetDataItem("X03","A110");//��Ϣ����
	}
	
	gtpdata.SetDataItem("X04","1");//��������
	gtpdata.SetDataItem("X05","1");//��Ϣ���к�
	gtpdata.SetDataItem("X06","L");//��Ϣ��������־
	gtpdata.SetDataItem("X07","0");//RootID
	gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
	gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��

	gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա����
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ��


	if(m_sNodeType.compare("6") == 0)
	{
		gtpdata.SetDataItem("X25","TRA");//���뷽ϵͳ��ʶ
	}else if(m_sNodeType.compare("5") == 0)
	{
		gtpdata.SetDataItem("X25","WM");//���뷽ϵͳ��ʶ
	}else if(m_sNodeType.compare("4") == 0)
	{
		gtpdata.SetDataItem("X25","ACCT");//���뷽ϵͳ��ʶ
	}else if(m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X25","ETF");//���뷽ϵͳ��ʶ
	}  
	
	gtpdata.SetDataItem("X02",m_sTradeId.length()+m_sSeatNo.length()+9);//����

	std::string gtpstring ;
	if (!gtpdata.ToString(gtpstring))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���öϵ���Ϣ�ڵ��,ToString");
		return;
	}
	
	if (m_pPoint.api_send_msg_no_enc == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"δ��ʼ����̬��");
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
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ���Ա¼������api_send_msg_no_enc�쳣ʧ��");
		return;	
	}
	
	if (nRet <0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ���Ա¼��ʧ�� %d",nRet);
		return;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ͽ���Ա¼����� [%s]",gtpstring.c_str());
	CBF_Date_Time pdate;
	pdate.Update();
	m_nLogoutTime = atoi(pdate.ToStringD8().c_str())*10000+pdate.GetHour()*100+pdate.GetMinute(); 
	
	return;	
}
void COfferingTrade::TradeLogin()
{
	CBF_PMutex pp(&m_mutex);
	//����Ա��ϯλ��¼
	
	//��gtp����
	CGtpData  gtpdata;
	gtpdata.SetDataItem("X01","GTP1.0");//GTP�汾
	gtpdata.SetDataItem("X02","0000");//����
	if (m_sNodeType.compare("12") == 0)
	{
		CBF_Date_Time pdate;
		pdate.Update();
		gtpdata.SetDataItem("X03","A300");//��Ϣ����
		gtpdata.SetDataItem("X04","1");//��������
		gtpdata.SetDataItem("X05","1");//��Ϣ���к�
		gtpdata.SetDataItem("X06","L");//��Ϣ��������־
		gtpdata.SetDataItem("X07","0");//RootID
		gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
		gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��
		if (m_sTradeDate.length()<2)
		{
			gtpdata.SetDataItem("T13",pdate.ToStringD8().c_str());//��������
		}
		else
		{
			gtpdata.SetDataItem("T13",m_sTradeDate.c_str());//ʹ�ý��׷���Ľ�������
		}
		gtpdata.SetDataItem("M00",m_sMemberId.c_str());//��Ա����
		gtpdata.SetDataItem("R09",m_sOrganType);//��������
	}
	else
	{
		gtpdata.SetDataItem("X04","1");//��������
		gtpdata.SetDataItem("X05","1");//��Ϣ���к�
		gtpdata.SetDataItem("X06","L");//��Ϣ��������־
		gtpdata.SetDataItem("X07","0");//RootID
		gtpdata.SetDataItem("X08",m_sSendFlag.c_str());//���ͷ���ʶ��
		gtpdata.SetDataItem("X09",m_sRcvFlag.c_str());//���շ���ʶ��
		gtpdata.SetDataItem("X03","A100");//��Ϣ����
		gtpdata.SetDataItem("M60",m_sTradeId.c_str());//����Ա����
	}

	
	
	gtpdata.SetDataItem("M20",m_sSeatNo.c_str());//ϯλ��
	gtpdata.SetDataItem("M62",m_sTradePwd);//��¼����
	gtpdata.SetDataItem("X50","127.0.0.1");//ip��ַ
	gtpdata.SetDataItem("X55",m_pPoint.api_get_version(m_apiPoint->apistruct->api_));//API�汾��Ϣ
	
	if(m_sNodeType.compare("6") == 0)
	{
		gtpdata.SetDataItem("X25","TRA");//���뷽ϵͳ��ʶ
	}else if(m_sNodeType.compare("5") == 0)
	{
		gtpdata.SetDataItem("X25","WM");//���뷽ϵͳ��ʶ
	}else if(m_sNodeType.compare("4") == 0)
	{
		gtpdata.SetDataItem("X25","ACCT");//���뷽ϵͳ��ʶ
	}else if(m_sNodeType.compare("12") == 0)
	{
		gtpdata.SetDataItem("X25","ETF");//���뷽ϵͳ��ʶ
	}   
	  
	gtpdata.SetDataItem("X80",m_sSgeSafeInfo);//��ȫ��Ϣ��
	gtpdata.SetDataItem("X81",m_nSgeSafeInfoLen);//��ȫ��Ϣ�򳤶�

	

	CGtpData *arrynode = gtpdata.AddDataItem("X20",GTP_DATATYPE_ARRAY);
	if (arrynode == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���öϵ���Ϣ�ڵ�� GTP_DATATYPE_ARRAY");
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
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���öϵ���Ϣ�ڵ��,GTP_DATATYPE_HASH");
			return;
		}
		hashnode->SetDataItem("X04",m_FlowInfo[i]->nFlowNo);
		if (m_FlowInfo[i]->nFlowNo == 6 && m_nQuotaBreak != 1)
		{
			hashnode->SetDataItem("X05",-1); //��ȡ����ϵ�
		}
		else
		{
			hashnode->SetDataItem("X05",m_FlowInfo[i]->nMaxSerial);
		}
	}
	std::string gtpstring ;

	arrynode->ToString(gtpstring);

	gtpdata.SetDataItem("X02",m_sTradePwd.length()+m_sTradeId.length()+m_sSeatNo.length()+9+5+m_nSgeSafeInfoLen+4+40+gtpstring.length());//����

	gtpstring = "";
	if (!gtpdata.ToString(gtpstring))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���öϵ���Ϣ�ڵ��,ToString");
		return;
	}
	int nRet;

	try
	{
		nRet = m_pPoint.api_send_msg_no_enc(m_apiPoint->apistruct->api_,gtpstring.c_str(),gtpstring.length());
	}
	catch (...)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ���Ա��¼����api_send_msg_no_enc�쳣ʧ��");
		return;	
	}
	
	if (nRet <0)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͽ���Ա��¼ʧ�� %d",nRet);
		return;
	}
	m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ͽ���Ա��¼��� [%s]",gtpstring.c_str());
	m_nLoginNum++;
	return;
}

bool COfferingTrade::GetFrontIpPort(char *ip, int &port)
{
	int nIpList = m_pListIp.size();
	if (nIpList <1 )
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"δ���ý�����IP");
		return false;
	}
	else if (nIpList == 1)
	{
		strcpy(ip,m_pListIp[0].sIp);
		port = m_pListIp[0].nPort;
		return true;
	}
// 	//���б������ѡһ��IP
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
		m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"CB_Disconnected �ͽ�����ǰ�öϿ�[%s %d] ״̬%d",\
			cs->ip,cs->port,cs->state);
		--(ctx->connected_count_);
		m_nApiLoginStatus =0;
		//���ӶϿ� ����ǰ��IP
// 		char sIp[40];
// 		int  nPort;
// 		if (!GetFrontIpPort(sIp,nPort))
// 		{
// 			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�޽�����ǰ��IP���˿�");
// 			return false;
// 		}
// 		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�Ͽ����ӣ��´����ӵĽ�����ǰ�ö˿�[%s %d]",sIp,nPort);
// 		m_pPoint.api_set_new_endpoint(m_apiPoint->apistruct->api_,sIp,nPort);
		
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
			ctx->cb_.api_recv_msg_(sLogGtp.c_str(),GTP_TYPE_STRING,sLogGtp.length(),ctx);
		}


	}
	else
	{
		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"CB_Disconnected ���ز��Ǳ�API��");
	}
	return true;
}
void COfferingTrade::LoginRsp(int loginstatus,const char *gtp)
{
	//m_nApiLoginStatus = loginstatus;
// 	if (!loggindata->ToString(m_sLogGtp))
// 	{
// 		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"�����¼��¼�����ĳ���");
// 	}
	m_sLogGtp = gtp;
	if (loginstatus == 1)
	{
		//��¼�ɹ�����Ϊ1
		m_nLoginNum = 1;
		if (m_nEncryptFlag == 1)
		{
			int ret;
			//У��
			try
			{
				//typedef int (*_api_safe_check_server_info)(api_safe_handle_t handle, const char *input, const size_t real_en_len);
				int ret=0;
				char x80[16384];
				char x81[16384];
				
				if (!GetGtpValue(gtp,"X80",x80))
//				if (loggindata->GetValueByName("X80",x80,fieldtype)<0)
				{
					m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"��¼������x80�ֶ�");
					m_nApiLoginStatus =0;
					return;
				}
				std::string sx80 = x80;
				GtpGetTransSign(sx80);
				if (!GetGtpValue(gtp,"X81",x81))
//				if (loggindata->GetValueByName("X81",x81,fieldtype)<0)
				{
					m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"��¼������x81�ֶ�");
					m_nApiLoginStatus =0;
					return;
				}
				int fieldtype = atoi(x81);
				m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"����˰�ȫ��Ϣ [%s] ����[%s]",sx80.c_str(),x81);
				ret = m_pPoint.ca_api_safe_check_server_info(m_apiPoint->apistruct->safe_handle_,sx80.c_str(),fieldtype);
				if (ret != 0)
				{
					m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����˰�ȫ��Ϣ [%s] ����[%d]",sx80.c_str(),fieldtype);
					m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"ca_api_safe_check_server_info��֤ʧ�� %d",ret);
					m_nApiLoginStatus =0;
					return;
				}
				m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"ca_api_safe_check_server_info OK");
				m_nApiLoginStatus = loginstatus;
			}
			catch (...)
			{
				m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"ca_api_safe_check_server_info��֤�쳣����");
				m_nApiLoginStatus =0;
			}
		
		}
		
	}
	else
	{
		//��Login������
		//m_nLoginNum++;
		m_nApiLoginStatus = loginstatus;
	}
	
}

void COfferingTrade::Disconnect()
{
	CIOfferingBase::Disconnect();
	m_pPoint.api_disconnect(m_apiPoint->apistruct->api_);
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�Ͽ�api���� api_disconnect");

	//���ӶϿ� ����ǰ��IP
	char sIp[40];
	int  nPort;
	if (!GetFrontIpPort(sIp,nPort))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�޽�����ǰ��IP���˿�");
		return ;
	}
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�Ͽ����ӣ��´����ӵĽ�����ǰ�ö˿�[%s %d]",sIp,nPort);
	m_pPoint.api_set_new_endpoint(m_apiPoint->apistruct->api_,sIp,nPort);
	
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
			//��ת��
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
//ת���
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
