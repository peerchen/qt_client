#include "public.h"
#include "BF_SocketTcp.h"
#include "BF_SimpleLog.h"

#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "bf_kerneld.lib") 
#pragma message("Automatically linking with  bf_kerneld.lib")
#else
#pragma comment(lib, "bf_kerneld.lib")
#pragma message("Automatically linking with  bf_kernel.lib")
#endif
#endif

void DSP_2_HEX(const char *dsp,char *hex,int count)
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

void HEX_2_DSP(const char *hex,char *dsp,int count)
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

int main(int argc,char *argv[])
{
	if (argc <4)
	{
		printf("请输入报盘机IP及端口 日志级别\n");
		return -1;
	}
	CBF_SocketTcp socket;
	socket.Create(AF_INET,false);
	if (!socket.ConnectServer(argv[1],atoi(argv[2]),2000))
	{
		printf("连接报盘机失败\n");
		return -1;
	}
	socket.SetBlockFlag(true);

	unsigned int headlen = 8;
	CBF_SimpleLog log;
	log.SetLogPara(atoi(argv[3]),"","testsvr.log");
	//发送7000011报文
	char buffer[65534];
	bzero(buffer,sizeof(buffer));
	char bufferkv[65534];
	bzero(bufferkv,sizeof(bufferkv));
	strcpy(buffer,"X01=GTP1.0,X02=68,X03=ReqLogin,X04=1,X05=330,X06=L,X07=10110348,X08=ylink,X09=0000,X20=[{X05=0,X04=6},{X05=1,X04=3},{X05=204,X04=4},{X05=0,X04=2}]");
	strcpy(bufferkv,"00000000#TradeDate=20170331#NodeID=6011#NodeType=6#ApiName=ReqLogin#RootID=10110357#TXCODE=70000011#RspCode=000000#RspMsg=交易成功#GTPDATA=");
	int len = strlen(bufferkv);
	HEX_2_DSP(buffer,bufferkv+len,strlen(buffer));
	strcat(bufferkv,"#");
	len = strlen(bufferkv);
	sprintf(buffer,"%08d",len-8);
	memcpy(bufferkv,buffer,8);

	int nRet = socket.Receive(buffer,headlen,8000);
	if (nRet != 8)
	{
		printf("未收到70000010报文头\n");
		socket.Close();
		return -1;
	}
	buffer[8]=0;
	unsigned int wantlen = atoi(buffer);
	nRet = socket.Receive(buffer,wantlen,8000);
	if (nRet != wantlen)
	{
		printf("未收到70000010报文体或不全 %d\n",nRet);
		socket.Close();
		return -1;
	}
	buffer[nRet]=0;
	log.LogMp(LOG_PROMPT,__FILE__,__LINE__,"70000010报文[%s]",buffer);

	log.LogMp(LOG_PROMPT,__FILE__,__LINE__,"发送70000011报文[%s]",bufferkv);
	nRet = socket.Send(bufferkv,len);
	if (nRet != len )
	{
		printf("发送70000011败\n");
		socket.Close();
		return -1;
	}
	unsigned int rcvlen = sizeof(buffer)-1;
	while (true)
	{
		nRet = socket.Receive(buffer,headlen,8000);
		if (nRet != 8)
		{
			printf("未收到报文头\n");
			socket.Close();
			return -1;
		}
		buffer[8]=0;
		wantlen = atoi(buffer);
		nRet = socket.Receive(buffer,wantlen,8000);
		if (nRet != wantlen)
		{
			printf("未收到报文体或不全 %d\n",nRet);
			socket.Close();
			return -1;
		}
		buffer[nRet]=0;
		log.LogMp(LOG_PROMPT,__FILE__,__LINE__,"收到的报文[%s]",buffer);
		
	}
	strcpy(bufferkv,"00000000");
	nRet = socket.Send(bufferkv,8);

	socket.Close();
	printf("接收返回【%d】退出\n",nRet);
	//接收报文
	return 0;

}