// FlowData.cpp: implementation of the CFlowData class.
//
//////////////////////////////////////////////////////////////////////

#include "FlowData.h"


#define  FLOWBUFSIZE  4096

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFlowData::CFlowData()
{
	m_pDrebApi = NULL;
	m_pSockMgr = NULL;
	m_pLog = NULL;
	bzero(m_sTxDate,sizeof(m_sTxDate));
	m_pRes = NULL;
	m_bIsrun = false;
	ResetFlowInfo();
}

CFlowData::~CFlowData()
{
	WriteBreakPoint();
}

void CFlowData::DSP_2_HEX(const char *dsp,char *hex,int count)
{
    int i;
	int hexcount=count/2;
    for(i = 0; i < hexcount; i++)
    {
		hex[i]=((dsp[i*2]<=0x39)?dsp[i*2]-0x30:dsp[i*2]-0x41+10);
        hex[i]=hex[i]<<4;
		hex[i]+=((dsp[i*2+1]<=0x39)?dsp[i*2+1]-0x30:dsp[i*2+1]-0x41+10);
    }
} 

void CFlowData::HEX_2_DSP(const char *hex,char *dsp,int count)
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
} 
bool CFlowData::Init()
{
	char pathfilename[300];
	
	if (m_pRes->m_sFlowFilePath.length()<1)
	{
#ifdef _WINDOWS
		sprintf(pathfilename,"%s\\breakpoint.dat",m_pRes->g_sCurPath);
#else
		sprintf(pathfilename,"breakpoint.dat");
#endif
	}
	else
	{
#ifdef _WINDOWS
		sprintf(pathfilename,"%s\\breakpoint.dat",m_pRes->m_sFlowFilePath.c_str());
#else
		sprintf(pathfilename,"%s/breakpoint.dat",m_pRes->m_sFlowFilePath.c_str());
#endif
	}

	FILE *fp = fopen(pathfilename,"rb");
	if (fp == NULL)
	{
		m_pLog->LogMp(LOG_ERROR_GENERAL,__FILE__,__LINE__,"���ļ�[%s]����",pathfilename);
		return true;
	}
	//����������
	int ret = fread(m_sTxDate,1,8,fp);
	if (ret != 8)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ļ�breakpoint.dat���޽�����������");
		fclose(fp);
		return false;
	}
	//��ȡ�ϵ���Ϣ
	ret = fread(&m_FlowInfo,1,sizeof(m_FlowInfo),fp);
	if (ret != sizeof(m_FlowInfo))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�ļ�breakpoint.dat���޽�����������");
		fclose(fp);
		ResetFlowInfo();
		ReadFlowInfo(m_sTxDate);
		return false;
	}
	fclose(fp);

	ReadFlowInfo(m_sTxDate);
// 	std::vector<S_FLOW_INFO> BPLIST;
// 	S_FLOW_INFO aa;
// 	aa.nFlowNo=4;
// 	aa.nMaxSerial=0;
// 	BPLIST.push_back(aa);
// 	BPCCOMMSTRU data;
// 	data.sBpcHead.nBpuIndex =1;
// 	GetFlowData(BPLIST,data);
	return true;
}

void CFlowData::ResetFlowInfo()
{
	bzero(&m_FlowInfo,sizeof(m_FlowInfo));
	
	for (int i=0; i<MAXFLOWNO ; i++)
	{
		m_FlowInfo[i].nFlowNo = i+1;
		m_FlowInfo[i].nMaxSerial = 0;
	}
	//Ӧ������Ҫ�󣬲���ʱ������Ϊ-1
//	m_FlowInfo[5].nMaxSerial = -1;
}

void CFlowData::ReadFlowInfo(const char *datepath)
{
	//�ļ���Ϊflow+��Ϣ����.dat���
	//���ļ��ù̶�����8+4kһ�����ݣ�ǰ���8Ϊ��Ϣ��ˮ��
	int ret;
	int len;
	char tmpchar[300];
	struct_stat fstat;
	char serialno[9];
	for (int i=0 ; i< MAXFLOWNO; i++)
	{
		if (m_pRes->m_sFlowFilePath.length()<1)
		{
#ifdef _WINDOWS
			sprintf(tmpchar,"%s\\%s\\flow%d.dat",m_pRes->g_sCurPath,datepath,m_FlowInfo[i].nFlowNo);
#else
			sprintf(tmpchar,"%s/flow%d.dat",datepath,m_FlowInfo[i].nFlowNo);
#endif
		}
		else
		{
#ifdef _WINDOWS
			sprintf(tmpchar,"%s\\%s\\flow%d.dat",m_pRes->m_sFlowFilePath.c_str(),datepath,m_FlowInfo[i].nFlowNo);
#else
			sprintf(tmpchar,"%s/%s/flow%d.dat",m_pRes->m_sFlowFilePath.c_str(),datepath,m_FlowInfo[i].nFlowNo);
#endif
		}
		fstat.st_size=0;
		FSTAT(tmpchar,&fstat);
		if (fstat.st_size <1)
		{
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���ļ�[%s]�����ڻ�������",tmpchar);
			m_FlowInfo[i].nMaxSerial = 0;
			continue;
		}
		if (fstat.st_size>0)
		{
			ret = fstat.st_size %(FLOWBUFSIZE+16);
			if (ret !=0)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ļ�[%s]��С[%d]����%d+16�ı���",tmpchar,fstat.st_size,FLOWBUFSIZE);
				ret = fstat.st_size - FLOWBUFSIZE - 16 - ret;
			}
			else
			{
				ret = fstat.st_size - FLOWBUFSIZE - 16;
			}
		}
		
		
		FILE *fp = fopen(tmpchar,"rb");
		if (fp == NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ļ�[%s]�����ڻ�������",tmpchar);
			m_FlowInfo[i].nMaxSerial = 0;
			continue;
		}
		fseek(fp,ret,1);
		bzero(serialno,sizeof(serialno));
		len = fread(serialno,1,8,fp);
		if (len!=8)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�����ļ�[%s] λ��[%d]����",tmpchar,ret);
//			m_FlowInfo[i].nMaxSerial = 0;
			fclose(fp);
			continue;
		}
		fclose(fp);
		fp = NULL;
		if (atoi(serialno)>m_FlowInfo[i].nMaxSerial)
		{
			m_FlowInfo[i].nMaxSerial = atoi(serialno);
		}
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�����ļ��ж��������� ������[%d] ������[%d]",m_FlowInfo[i].nFlowNo,m_FlowInfo[i].nMaxSerial);
		
	}
	
}

bool CFlowData::WriteFlow(int type,unsigned int serial,unsigned int txcode,BPCCOMMSTRU data)
{
	if (type <1 || type > MAXFLOWNO)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������[%d]����",type);
		return false;
	}
	if (type != 1 && type != 5) //�������Ͳ�ѯ�������ͬ��Ϊ0���������ж�
	{
		if (m_FlowInfo[type-1].nMaxSerial >= serial)
		{
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"������[%d %d] ���[%d]�������£�����д��",type,m_FlowInfo[type-1].nMaxSerial,serial);
			return true;
		}
		m_FlowInfo[type-1].nMaxSerial = serial;
	}
	int ret;
	char flowfilename[300];
	char tmpchar[200];
	if (m_pRes->m_sFlowFilePath.length()<1)
	{
#ifdef _WINDOWS
		sprintf(flowfilename,"%s\\%s\\flow%d.dat",m_pRes->g_sCurPath,m_sTxDate,type);
#else
		sprintf(flowfilename,"%s/flow%d.dat",m_sTxDate,type);
#endif
	}
	else
	{
#ifdef _WINDOWS
		sprintf(flowfilename,"%s\\%s\\flow%d.dat",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate,type);
#else
		sprintf(flowfilename,"%s/%s/flow%d.dat",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate,type);
#endif
	}

	struct_stat fstat;
	FILE *fp = fopen(flowfilename,"ab");
	if (fp == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ļ�[%s]����",flowfilename);
		return false;
	}
	//��д��ʱ�������С����4096+8�ı��������㱶������д����������
	fstat.st_size=0;
	FSTAT(flowfilename,&fstat);
	if (fstat.st_size >0)
	{
		int wret = fstat.st_size %(FLOWBUFSIZE+16);
		if (wret !=0)
		{
			
			char wbuf[FLOWBUFSIZE+16];
			bzero(wbuf,sizeof(wbuf));
			if (wret >1)
			{
				wbuf[wret-2]=0; 
			}
			wbuf[wret-1]=9; //ʹ���ַ�9��Ϊ������Ϣ�ı�־
			ret = fwrite(wbuf,1,wret,fp);
			if (ret != wret)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д�ļ�[%s]���� [%d] Ҫд[%d]",flowfilename,ret,wret);
				fclose(fp);
				return false;
			}
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ļ�[%s]��С[%d]����%d+16�ı���  ���������� %d",\
				flowfilename,fstat.st_size,FLOWBUFSIZE,ret);
		}
	}
	

	sprintf(tmpchar,"%08d",serial);
	ret = fwrite(tmpchar,1,8,fp);
	if (ret != 8)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д�ļ�[%s]���� [%d]",flowfilename,ret);
		fclose(fp);
		return false;
	}
	sprintf(tmpchar,"%08d",txcode);
	ret = fwrite(tmpchar,1,8,fp);
	if (ret != 8)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д�ļ�[%s]���� [%d]",flowfilename,ret);
		fclose(fp);
		return false;
	}
	memset(data.sBuffer+data.sDBHead.nLen,0,BPUDATASIZE-data.sDBHead.nLen-1);
	//gtp�������ֻ��4k
	ret = fwrite(data.sBuffer,1,FLOWBUFSIZE,fp);
	if (ret != FLOWBUFSIZE)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д�ļ�[%s]���� [%d]",flowfilename,ret);
		fclose(fp);
		return false;
	}
	fclose(fp);
	return true;
}

bool CFlowData::GetFlowData(std::vector<S_FLOW_INFO> &bplist, BPCCOMMSTRU &data,CKvData *kvdata)
{
	FILE *fp= NULL;
	char flowfilename[300];
	char tmpchar[200];
	int nRet=0;
	int curserial=0;

	if (data.sDBHead.n_Ninfo.n_nNextNo != atoi(m_sTxDate))
	{
		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�ϵ㽻�����ڲ�����ֱ�ӷ���");
		return true;
	}
 	UINT64_ btime =CBF_Date_Time::GetTickUS();
	int  bpnum=0;
// 	UINT64_ etime;
// 	UINT64_ eetime;
	for (int i=0; i< bplist.size(); i++)
	{
		if (bplist[i].nMaxSerial <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������[%d]��ȡ�ϵ�[%d]",bplist[i].nFlowNo,bplist[i].nMaxSerial);
			continue;
		}
		if (bplist[i].nFlowNo <1 || bplist[i].nFlowNo > MAXFLOWNO)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"������[%d]����",bplist[i].nFlowNo);
			continue;
		}
		//���浱ǰ������ţ��Ժ������Ѿ��ŵ���������
		unsigned int endserial= m_FlowInfo[bplist[i].nFlowNo-1].nMaxSerial;
		

//		etime =CBF_Date_Time::GetTickUS();

		if (m_pRes->m_sFlowFilePath.length()<1)
		{
#ifdef _WINDOWS
		sprintf(flowfilename,"%s\\%s\\flow%d.dat",m_pRes->g_sCurPath,m_sTxDate,bplist[i].nFlowNo);
#else
		sprintf(flowfilename,"%s/flow%d.dat",m_sTxDate,bplist[i].nFlowNo);
#endif
		}
		else
		{
#ifdef _WINDOWS
			sprintf(flowfilename,"%s\\%s\\flow%d.dat",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate,bplist[i].nFlowNo);
#else
			sprintf(flowfilename,"%s/%s/flow%d.dat",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate,bplist[i].nFlowNo);
#endif
		}
		fp = fopen(flowfilename,"rb");
		if (fp == NULL)
		{
			m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"���ļ�[%s]������",flowfilename);
			continue;
		}
//		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"�����ļ���ɺ�ʱ[%d]΢��",CBF_Date_Time::GetTickUS()-etime);
		
		curserial=0;
		while (fp != NULL)
		{
//			eetime =CBF_Date_Time::GetTickUS();
			bzero(tmpchar,sizeof(tmpchar));
			nRet = fread(tmpchar,1,8,fp);
			if (nRet != 8)
			{
				m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"�����ļ�[%s]��������Ż��ѵ��ļ�β",flowfilename);
				fclose(fp);
				fp= NULL;
				break;
			}
			if (!CBF_Tools::IsNumber(tmpchar))
			{
				m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"�����ļ�[%s]���������[%s]����",flowfilename,tmpchar);
				fclose(fp);
				fp= NULL;
				break;
			}
			curserial = atoi(tmpchar);
			if (data.sBpcHead.nBpuIndex == 1) //����������
			{
				//ʹ���������ֶα��������ͺ������
				data.sDBHead.s_Sinfo.s_nHook = bplist[i].nFlowNo;
				data.sDBHead.s_Sinfo.s_nSerial = curserial;
				
			}
			
			if (bplist[i].nMaxSerial >= curserial)
			{
				//���÷�
				nRet = fseek(fp,FLOWBUFSIZE+8,1);//�Ƶ�����
				continue;
			}
			if (endserial >0)
			{
				if (curserial > endserial)
				{
					m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"�����ļ�[%s]�ѵ����ϵ� %d",flowfilename,endserial);
					fclose(fp);
					fp= NULL;
					break;
				}
			}
			
			//��������
			nRet = fread(tmpchar,1,8,fp);
			if (nRet != 8)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�����ļ�[%s]���ĳ������Ȳ���[%d]",flowfilename,nRet);
				fclose(fp);
				fp= NULL;
				break;
			}
			data.sDBHead.d_Dinfo.d_nServiceNo = atoi(tmpchar);
			//�����ݵ�data
			nRet = fread(data.sBuffer,1,FLOWBUFSIZE,fp);
			if (nRet != FLOWBUFSIZE)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�����ļ�[%s]���ĳ������Ȳ���[%d]",flowfilename,nRet);
				fclose(fp);
				fp= NULL;
				break;
			}
			data.sBuffer[FLOWBUFSIZE]=0;
			//�ж����һ���ַ��Ƿ�����
			if (data.sBuffer[FLOWBUFSIZE-1] == 9)
			{
				m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"�����ļ�[%s]����һ�ʴ������Ϣ���Թ�",flowfilename);
				continue;
			}

			data.sDBHead.nLen = strlen(data.sBuffer);
			m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"���������[%d %d]  �ϵ�[%d - %d]",\
					data.sDBHead.s_Sinfo.s_nHook,data.sDBHead.s_Sinfo.s_nSerial,bplist[i].nMaxSerial,endserial);
//			m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"����[%d]һ����¼��ɺ�ʱ[%d]΢��",bplist[i].nFlowNo,CBF_Date_Time::GetTickUS()-eetime);
			//���ͳ�ȥ
			nRet = SendBack(data,kvdata);
//			m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"������[%d]һ����¼��ɺ�ʱ[%d]΢��",bplist[i].nFlowNo,CBF_Date_Time::GetTickUS()-eetime);
			if (nRet <0)
			{
				m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���������[%d %d]  �ϵ�[%d - %d] ���ͳ���",\
					data.sDBHead.s_Sinfo.s_nHook,data.sDBHead.s_Sinfo.s_nSerial,bplist[i].nMaxSerial,endserial);
				fclose(fp);
				fp= NULL;
				return false;
			}
			bpnum++;

		}
		
//		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"������[%d]��ɺ�ʱ[%d]΢��",bplist[i].nFlowNo,CBF_Date_Time::GetTickUS()-etime);
	}
	m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"��ɶϵ� ��ʱ[%d]΢�� �ܹ�[%d]����¼",CBF_Date_Time::GetTickUS()-btime,bpnum);
	return true;
}

int CFlowData::Login(const char *txdate)
{
	CBF_PMutex pp(&m_pWmutex);
	char oldbpfile[300];
	char newbpfile[300];
	char flowpath[300];
	int nRet = 0;
	if (strlen(txdate) != 8)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ա��¼��������[%s]���Ȳ���",txdate);
		return nRet;
	}
	if (strlen(m_sTxDate) !=8 )
	{
		if (m_pRes->m_sFlowFilePath.length()<1)
		{
#ifdef _WINDOWS
			sprintf(oldbpfile,"%s\\breakpoint.%s",m_pRes->g_sCurPath,m_sTxDate);
#else
			sprintf(oldbpfile,"breakpoint.%s",m_sTxDate);
#endif
		}
		else
		{
#ifdef _WINDOWS
			sprintf(oldbpfile,"%s\\breakpoint.%s",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate);
#else
			sprintf(oldbpfile,"%s/breakpoint.%s",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate);
#endif
		}
		strcpy(m_sTxDate,txdate);
	}
	else if (atoi(txdate) > atoi(m_sTxDate)) //���ڸ�����
	{
		if (m_pRes->m_sFlowFilePath.length()<1)
		{
#ifdef _WINDOWS
		sprintf(oldbpfile,"%s\\breakpoint.%s",m_pRes->g_sCurPath,m_sTxDate);
#else
		sprintf(oldbpfile,"breakpoint.%s",m_sTxDate);
#endif
		}
		else
		{
#ifdef _WINDOWS
		sprintf(oldbpfile,"%s\\breakpoint.%s",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate);
#else
		sprintf(oldbpfile,"%s/breakpoint.%s",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate);
#endif
		}
		strcpy(m_sTxDate,txdate);
		nRet = 1;
	}
	else //����������ͬ��С�ڣ�ֱ�ӷ��أ����ô���
	{
		m_pLog->LogMp(LOG_WARNNING,__FILE__,__LINE__,"��¼���ؽ�������[%s]��ԭ������[%s]��ͬ��С��",txdate,m_sTxDate);

		if (m_pRes->m_sFlowFilePath.length()<1)
		{
#ifdef _WINDOWS
			sprintf(flowpath,"%s\\%s",m_pRes->g_sCurPath,m_sTxDate);
#else
			strcpy(flowpath,m_sTxDate);
#endif
		}
		else
		{
#ifdef _WINDOWS
			sprintf(flowpath,"%s\\%s",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate);
#else
			sprintf(flowpath,"%s/%s",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate);
#endif
		}
		if (!CBF_Tools::MakeDir(flowpath))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ŀ¼[%s]ʧ��",flowpath);
			return nRet;
		}
		//���¶�ȡ���ļ��������
		ReadFlowInfo(m_sTxDate);
		return nRet;
	}
	
	if (m_pRes->m_sFlowFilePath.length()<1)
	{
#ifdef _WINDOWS
		sprintf(newbpfile,"%s\\breakpoint.dat",m_pRes->g_sCurPath);
#else
		strcpy(newbpfile,"breakpoint.dat");
#endif
	}
	else
	{
#ifdef _WINDOWS
		sprintf(newbpfile,"%s\\breakpoint.dat",m_pRes->m_sFlowFilePath.c_str());
#else
		sprintf(newbpfile,"%s/breakpoint.dat",m_pRes->m_sFlowFilePath.c_str());
#endif
	}
	rename(newbpfile,oldbpfile);
	//���½�������
	ResetFlowInfo();
	

	if (m_pRes->m_sFlowFilePath.length()<1)
	{
#ifdef _WINDOWS
		sprintf(flowpath,"%s\\%s",m_pRes->g_sCurPath,m_sTxDate);
#else
		strcpy(flowpath,m_sTxDate);
#endif
	}
	else
	{
#ifdef _WINDOWS
		sprintf(flowpath,"%s\\%s",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate);
#else
		sprintf(flowpath,"%s/%s",m_pRes->m_sFlowFilePath.c_str(),m_sTxDate);
#endif
	}
	if (!CBF_Tools::MakeDir(flowpath))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"����Ŀ¼[%s]ʧ��",flowpath);
		return nRet;
	}
	FILE *fp = fopen(newbpfile,"wb");
	if (fp == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д���ļ�[%s]ʧ��",newbpfile);
		return nRet;
	}
	int ret = fwrite(m_sTxDate,1,8,fp);
	if (ret != 8)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д�ļ�[%s]��������ʧ��",newbpfile);
		fclose(fp);
		return nRet;
	}

	ret = fwrite(&m_FlowInfo,1,sizeof(m_FlowInfo),fp);
	if (ret != sizeof(m_FlowInfo))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д�ļ�[%s]�ϵ�����ʧ��",newbpfile);
		fclose(fp);
		return nRet;
	}
	fclose(fp);
	ReadFlowInfo(m_sTxDate);
	return nRet;
}

void CFlowData::SetPara(CIErrlog *log, CSocketMgr *smgr, CBF_DrebServer *api,CTradeResource *res)
{
	m_pLog = log;
	m_pSockMgr = smgr;
	m_pDrebApi = api;
	m_pRes = res;
	m_sCurPath = m_pRes->g_sCurPath;
	m_sFlowFilePath = m_pRes->m_sFlowFilePath;
	m_bIsrun = true;
}

int CFlowData::SendBack(BPCCOMMSTRU &data,CKvData *kvdata)
{
	
	if (data.sBpcHead.nBpuIndex == 1) //����������
	{
		S_OFFERING_DATA senddata;
		if (!m_pSockMgr->at(data.sBpcHead.nIndex)->ResetData(senddata))
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ݷ���ռ����");
			return -1;
		}
		memset(senddata.pData,0,MAX_OFFERINGDATA_LEN+20);
		char tmpchar[11];
		sprintf(tmpchar,"%d%d",m_pRes->g_nSvrMainId,m_pRes->g_nSvrPrivateId);
		
		sprintf(senddata.pData,"ApiName=onRcvGtpMsg#TXCODE=%d#NodeID=%s#NodeType=%s#SequenceSeriesNo=%d#SequenceNo=%d#TradeDate=%s#GTPDATA=",\
			data.sDBHead.d_Dinfo.d_nServiceNo,tmpchar,m_pRes->g_sNodeType.c_str(),\
			data.sDBHead.s_Sinfo.s_nHook,data.sDBHead.s_Sinfo.s_nSerial,m_sTxDate);
		unsigned int t_tmpdatalen = strlen(senddata.pData);
		//m_pLog->LogMp(LOG_DEBUG,__FILE__,__LINE__,"kv����ͷ����[%d %s]",t_tmpdatalen,senddata.pData);

		HEX_2_DSP(data.sBuffer,senddata.pData+t_tmpdatalen,data.sDBHead.nLen);
		strcat(senddata.pData,"#");
		senddata.nWantlen = strlen(senddata.pData);
		
		m_pLog->LogBin(LOG_DEBUG+1,__FILE__,__LINE__,"�ϵ㷢��KV����",senddata.pData,senddata.nWantlen);
//		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"��ʼ����ǰ��ʱ [%d]΢��",CBF_Date_Time::GetTickUS()-btime);
		//Ӧ���ȥ
		int ret = m_pSockMgr->at(data.sBpcHead.nIndex)->SendMsg(senddata,0);
//		m_pLog->LogMp(LOG_INFO,__FILE__,__LINE__,"������ɺ�ʱ [%d]΢��",CBF_Date_Time::GetTickUS()-btime);
		if (ret <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͳ��� %d",ret);
			return ret;
		}
		
	}
	else //���߹�����
	{
		m_pLog->LogBin(LOG_DEBUG,__FILE__,__LINE__,"�ϵ㷢��GTP����",data.sBuffer,data.sDBHead.nLen);

		S_BPC_RSMSG drebdata;
		drebdata.sMsgBuf = (PBPCCOMMSTRU)m_pDrebApi->PoolMalloc();
		if (drebdata.sMsgBuf== NULL)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"�������ݷ���ռ����");
			return -1;
		}
		//���㲥��ʽ����
		data.sDBHead.cRaflag = 0;
		data.sDBHead.cZip = 0;
		data.sDBHead.cCmd = CMD_DPABC;
		data.sDBHead.d_Dinfo.d_nServiceNo = TRADEFRONT_BAEAKPOINT;
		memcpy(&(drebdata.sMsgBuf->sDBHead),&(data.sDBHead),sizeof(DREB_HEAD));
		
		if (data.sDBHead.nLen>0)
		{
			memcpy(drebdata.sMsgBuf->sBuffer,data.sBuffer,data.sDBHead.nLen);
		}
		//�������ã�����ָ�������ߣ��ر���
		drebdata.sMsgBuf->sDBHead.d_Dinfo.d_nNodeId = m_pRes->g_nSendDrebNode;
		
		int ret = m_pDrebApi->SendMsg(drebdata);
		if (ret <0)
		{
			m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"���ͳ��� %d",ret);
			return ret;
		}

	}
	return 0;
}

void CFlowData::WriteBreakPoint()
{
	if (!m_bIsrun)
	{
		return;
	}
	CBF_PMutex pp(&m_pWmutex);
	char newbpfile[300];
	
	if (m_sFlowFilePath.length()<1)
	{
#ifdef _WINDOWS
		sprintf(newbpfile,"%s\\breakpoint.dat",m_sCurPath.c_str());
#else
		strcpy(newbpfile,"breakpoint.dat");
#endif
	}
	else
	{
#ifdef _WINDOWS
		sprintf(newbpfile,"%s\\breakpoint.dat",m_sFlowFilePath.c_str());
#else
		sprintf(newbpfile,"%s/breakpoint.dat",m_sFlowFilePath.c_str());
#endif
	}
	FILE *fp = fopen(newbpfile,"wb");
	if (fp == NULL)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д���ļ�[%s]ʧ��",newbpfile);
		return ;
	}
	int ret = fwrite(m_sTxDate,1,8,fp);
	if (ret != 8)
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д�ļ�[%s]��������ʧ��",newbpfile);
		fclose(fp);
		return ;
	}
	
	ret = fwrite(&m_FlowInfo,1,sizeof(m_FlowInfo),fp);
	if (ret != sizeof(m_FlowInfo))
	{
		m_pLog->LogMp(LOG_ERROR,__FILE__,__LINE__,"д�ļ�[%s]�ϵ�����ʧ��",newbpfile);
		fclose(fp);
		return ;
	}
	fclose(fp);
	fp=NULL;
	return ;
}
