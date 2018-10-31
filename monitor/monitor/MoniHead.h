// MoniHead.h: interface for the CMoniHead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONIHEAD_H__1A490998_AE1D_4016_859A_2C1896E2D51B__INCLUDED_)
#define AFX_MONIHEAD_H__1A490998_AE1D_4016_859A_2C1896E2D51B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#ifdef __cplusplus
extern "C" {
#endif
	
	//�ֽڶ���
#ifdef _WINDOWS
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
	//#pragma pack(push,1)
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif
	
#define MONI_SOCK_UNKNOW   10      //δ֪
#define MONI_SOCK_H1       21      //�ͼ�ط�������H1����
#define MONI_SOCK_H2       22      //�ͼ�ط�������H2����
#define MONI_SOCK_LISTEN   23      //�����˿�


typedef struct
{
	std::string sIp;       //IP
	int         nPort;     //�˿�
	int         nBandwidth;//����
}S_DREBLINK_INFO;


typedef struct _S_KV_HEAD
{
	char m_seq_no[8+1];  //��ˮ��
	char m_msg_type[1+1];  //��������     
	char m_exch_code[4+1];  //���״��� 
	char m_msg_flag[1+1];   //���ı�ʶ    '1' ����  '2' Ӧ��
	char m_term_type[2+1];    //�ն���Դ
	char m_user_type[2+1];   //�û�����
	char m_user_id[10+1];    //�û�ID
	char m_area_code[4+1];    //��������
	char m_branch_id[12+1];  //�������
	char m_c_teller_id1[10+1]; //һ�����˲���Ա
	char m_c_teller_id2[10+1]; //�������˲���Ա
	char m_rsp_code[8+1];     //������
}__PACKED__ S_KV_HEAD;

typedef struct
{
	char serial[8+1];  // ��ˮ��
	char msgtype[1+1]; //�������� 
	char txcode[4+1];  //���״���
	char msgflag[1+1];  //���ı�ʶ
	char termtype[2+1];  //�ն���Դ
	char usertype[2+1];  //�û�����
	char userid[10+1];    //�û�ID
	char areacode[4+1];      //��������
	char depart[12+1];        //�������
	char oper1[10+1];       //һ�����˲���Ա
	char oper2[10+1];          //�������˲���Ա
} __PACKED__ MSGHEAD;
typedef struct
{
	char serial[8+1];  // ��ˮ��
	char msgtype[1+1]; //�������� 
	char txcode[4+1];  //���״���
	char msgflag[1+1];  //���ı�ʶ
	char termtype[2+1];  //�ն���Դ
	char usertype[2+1];  //�û�����
	char userid[10+1];    //�û�ID
	char areacode[4+1];      //��������
	char depart[12+1];        //�������
	char retcode[8+1];       //��Ӧ����
} __PACKED__ MSGANSHEAD;

#define  MAXCOMMBUFLEN   64*1024   //��󻺳峤��
#define  HEARTHEAD    8   //����������ͨѶͷ����
#define  MSGHEADLEN      (sizeof(MSGHEAD)-11)       //����ͨѶͷ����
#define  MSGANSHEADLEN   (sizeof(MSGANSHEAD)-10)     //Ӧ��ͨѶͷ����

const int gc_nQuolityGood				= 0;				//��������Good
const int gc_nQuolityBad				= 1;				//��������Bad
const int gc_nQuolityUncertain			= 2;				//��������Uncertain

const string gc_nItemTypeDigital		= "0";				//�����ͼ����(ֵ��ʱ����ɢ�仯)
const string gc_nItemTypeAnalog			= "1";				//ģ���ͼ����(ֵ��ʱ�������仯)
const string gc_nItemTypeConfig			= "2";				//������(ֵ����ʱ��仯)


const string gc_CtrQuit		            = "0";				//�˳���������
const string gc_CtrRestar		        = "1";				//������������
const string gc_CtrStar			        = "2";				//������������

const int gc_nValueTypeInt				= 0;				//int��ֵ����
const int gc_nValueTypeDbl				= 1;				//double��ֵ����
const int gc_nValueTypeStr				= 2;				//string��ֵ����

const int gc_nEvtSimple					= 0;				//���¼�
const int gc_nEvtTrack					= 1;				//track�¼�

const int gc_nAlmGrade0					= 0;				//����
const int gc_nAlmGrade1					= 1;				//һ��澯
const int gc_nAlmGrade2					= 2;				//��Ҫת��

const int gc_nAlmNtfNew					= 0;				//�����澯
const int gc_nAlmNtfEnd					= 1;				//�澯����
const int gc_nAlmNtfChg					= 2;				//�澯ת��

const int gc_nThreadRun					= 0;				//����
const int gc_nThreadBlock				= 1;				//����
const int gc_nThreadQuit				= 2;				//�˳�

const int gc_nTcpInit					= 0;				//��ʼ��
const int gc_nTcpConneted				= 1;				//��������
const int gc_nTcpDisConneted			= 2;				//�����ж�

const int gc_ProceRun				    = 0;				//����    ��������״̬
const int gc_ProceStop					= 1;				//δ����
const int gc_ProceNoHeart				= 2;				//������

//MIB
const std::string mibCpuRadio			= "1.1.1.1.1";		//cpuʹ����
const std::string mibEmsTotal			= "1.1.1.2.1.1";		//�ڴ�����
const std::string mibEmsUse				= "1.1.1.2.1.2";		//�ڴ�ʹ����
const std::string mibEmsRadio			= "1.1.1.2.1.3";		//�ڴ�ʹ����
const std::string mibDiskNum			= "1.1.1.3.1";		//Ӳ�̷�����

const std::string mibPartIndex		    = "1.1.1.3.2.1.1";	//Ӳ�̷�������
const std::string mibDiskPhyTotal		= "1.1.1.3.2.1.2";	//Ӳ�̵�����������С
const std::string mibDisk_Used			= "1.1.1.3.2.1.3";	//Ӳ���Ѿ�ʹ�õĴ�С
const std::string mibDisk_Used_Ratio    = "1.1.1.3.2.1.4";	//Ӳ��ʹ����

const std::string gc_sThreadNum			= "1.1.2.1";		//�߳�����
const std::string gc_sThreadIdx			= "1.1.2.2.1.1";	//�߳�����
const std::string gc_sThreadState		= "1.1.2.2.1.2";	//�߳�״̬

const std::string gc_sTcpLocalIp		= "1.1.3.2.1.2";	//����IP
const std::string gc_sTcpLocalPort		= "1.1.3.2.1.3";	//���ض˿�
const std::string gc_sTcpRemoteIp		= "1.1.3.2.1.4";	//�Զ�IP
const std::string gc_sTcpRemotePort		= "1.1.3.2.1.5";	//�Զ˶˿�
const std::string gc_sTcpState			= "1.1.3.2.1.6";	//����״̬
const std::string gc_sTcpInBytesAve		= "1.1.3.2.1.7";	//ƽ�����ֽ���
const std::string gc_sTcpOutBytesAve	= "1.1.3.2.1.8";	//ƽ�����ֽ���


const std::string mib_NodeId		    = "1.2.6.1.1.1";	//���ID     ���¼
const std::string mib_NodeSta    	    = "1.2.6.1.1.2";	//���״̬
const std::string mib_NodeCtr			= "1.2.6.1.1.3";	//������  0 1 2 ������ֹͣ����ʼ
const std::string mibQueNum 		    = "1.1.4.1.1.2";	//�����б�������


	//ȡ���ֽڶ���
#ifdef _WINDOWS
#pragma pack(pop)
#else
#ifdef __GNUC__
	//#pragma pack(pop)
#else
#pragma options align=reset
#endif
#endif
#undef __PACKED__
	
#ifdef __cplusplus
}
#endif

#endif // !defined(AFX_GATEHEAD_H__1A490998_AE1D_4016_859A_2C1896E2D51B__INCLUDED_)
