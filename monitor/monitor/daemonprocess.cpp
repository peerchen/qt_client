
#include "public.h"
#include "BF_Tools.h"
#include "BF_SocketTcp.h"
#include "BF_Xml.h"
#include "KvData.h"

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "bf_kerneld.lib") 
#pragma message("Automatically linking with  bf_kerneld.lib")
#else
#pragma comment(lib, "bf_kernel.lib") 
#pragma message("Automatically linking with  bf_kernel.lib")
#endif
#endif


int main(int argc, char* argv[])
{
// 	CBF_Xml xml ;
// 
// 	if (!xml.FromFile("testdaemon.xml"))
// 	{
// 		printf("�����ļ�testdaemon.xml�����ڻ��xml\n");
// 		return -1;
// 	}

	if (argc<2)
	{
		printf("�������ļ���\n");
		return -1;
	}
	struct_stat ss;
	FSTAT(argv[1],&ss);
	if (ss.st_size<0)
	{
		printf("�ļ�[%s]�����ڻ��СΪ0\n",argv[1]);
		return -1;
	}
	if (ss.st_size < 4*1024*1024)
	{
		printf("�ļ�С��4M�����÷ָ�\n");
		return -1;
	}
	char *buf = (char *)malloc(4*1024*1024+1);
	if (buf == NULL)
	{
		printf("����ռ�ʧ��\n");
		return -1;
	}
	bzero(buf,4*1024*1024+1);
	FILE *fp = fopen(argv[1],"rb");
	if (fp == NULL)
	{
		printf("���ļ�[%s]ʧ��\n",argv[1]);
		free(buf);
		buf = NULL;
		return -1;
	}

	
	fseek(fp,ss.st_size-4*1024*1024,1);
	
	
	int nret = fread(buf,1,4*1024*1024,fp);
	fclose(fp);
	fp = fopen("tmp.txt","wb");
	if (fp == NULL)
	{
		printf("���ļ�[%s]ʧ��\n","tmp.txt");
		free(buf);
		buf = NULL;
		return -1;
	}
	fwrite(buf,1,nret,fp);
	fclose(fp);
	free(buf);
	buf = NULL;

	return 0;


	std::string sIp;
	int  nPort;
	std::string node_id;
	CBF_SocketTcp pSocket;
	CKvData data;
	std::string  sendbuffer;
	int ret;
	CBF_SimpleLog pLog;

// 	if (xml.GetNodeValueByPath("daemon/�����ػ�IP",false,sIp)== NULL)
// 	{
// 		printf("daemon��IPδ����\n");
// 		return -1;
// 	}
// 
// 	if (xml.GetNodeValueByPath("daemon/�����ػ��˿�",false,nPort) == NULL)
// 	{
// 		printf("daemon�Ķ˿�δ����\n");
// 		return -1;
// 	}
// 
// 	if (xml.GetNodeValueByPath("daemon/�ڵ��ʶ",false,node_id)== NULL)
// 	{
// 		printf("�ڵ��ʶδ����\n");
// 		return -1;
// 	}
	sIp = "127.0.0.1";
	nPort = 29000;
	node_id = argv[1];

	char logname[300];
	sprintf(logname,"testm%s.log",node_id.c_str());
	
	pLog.SetLogPara(LOG_DEBUG,"",logname);
	CKVNode *tmpnode = data.SetNodeByName("node_id",22);
	if (tmpnode == NULL)
	{
		printf("���ýڵ��ʶ����\n");
		return -1;
	}
	tmpnode->m_sKvValue = node_id;
	data.ToString(sendbuffer);
	char sendData[8192];
	int  sendLen = sendbuffer.length()+8;
	sprintf(sendData,"%08d#%s",sendbuffer.length(),sendbuffer.c_str());
	int nsl=0;
	while (true)
	{
		if (!pSocket.GetConnectStatus())
		{
			pSocket.Close();
			pSocket.Create(AF_INET,false);
			if (!pSocket.ConnectServer(sIp.c_str(),nPort,5))
			{
				printf("����daemon�����˿�ʧ��\n");
				SLEEP_SECONDS(2);
				continue;
			}
			pSocket.SetBlockFlag(false);
			pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"����������Դ�ɹ�");
		}
		
		while (nsl<sendLen)
		{
			ret = pSocket.Send(sendData+nsl,sendLen-nsl);
			if (ret < 0)
			{
				pSocket.Close();
				pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"���ͳ����ر�����");
				break;;
			}
			if (ret == sendLen-nsl)
			{
				break;
			}
			nsl +=ret;
			if (pSocket.CheckWriteEvent(5) == 1)
			{
				continue;
			}
			else
			{
				pSocket.Close();
				pLog.LogMp(LOG_WARNNING,__FILE__,__LINE__,"���Ӳ���д���˳��ر�����");
				break;;
			}
			break;
		}
		
		SLEEP_SECONDS(5);
	}

	return 0;
}

