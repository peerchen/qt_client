
#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include <libgen.h>

#include	<unistd.h>
#include	<sys/socket.h>
#include    <sys/time.h>
#include	<sys/ipc.h>
#include	<sys/shm.h>
#include	<sys/sem.h>
#include	<sys/msg.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<syslog.h>
#include	<zlib.h>
#include	<pwd.h>
#include    <ctype.h>
#include    <dirent.h>
#include	<zlib.h>
#include	<pthread.h>
#include	<errno.h>
#include	<signal.h>
#include	<syslog.h>

#include	<sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include	<errno.h>


#include <iconv.h>

#define OUTLEN 255

//代码转换:从一种编码转为另一种编码
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;
	memset(outbuf,0,outlen);
	if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1;
	iconv_close(cd);
	return 0;
}

//UNICODE码转为GB2312码
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}

//GB2312码转为UNICODE码
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}

int main()
{
	char *in_utf8 = "姝ｅ?ㄥ??瑁?";
	char *in_gb2312 = "正在安装";
	char out[OUTLEN];

	//unicode码转为gb2312码
	int rc = u2g(in_utf8,strlen(in_utf8),out,OUTLEN);
	printf("unicode-->gb2312 out=%sn",out);
	//gb2312码转为unicode码
	rc = g2u(in_gb2312,strlen(in_gb2312),out,OUTLEN);
	printf("gb2312-->unicode out=%sn",out);

	return 0;
}

