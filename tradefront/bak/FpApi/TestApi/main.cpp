
#include <stdio.h>
#include "FpApi.h"

void onFpConnect( void *pParamter )
{
	printf( "onFpConnect" );
}

void onFpConnectLost( void *pParamter )
{
	printf( "onFpConnectLost" );
}

void onFpException( const char *exception_code, const char *exception_msg, void *pParamter )
{
	printf( "onFpException" );
}

void onFpRecvPacket( const char *packet, void *pParamter )
{
	//printf( "onFpRecvPacket:%s\n", packet );
}

int main(int argc, char **argv)
{
	
	//初始化回调函数
	API_CALLBACK api_callback;
	api_callback.on_fp_api_recv_msg     = &onFpRecvPacket;
	api_callback.on_fp_api_connect      = &onFpConnect;
	api_callback.on_fp_api_connect_lost = &onFpConnectLost;
	api_callback.on_fp_api_exception    = &onFpException;

	//启动日志
	fp_api_log_start( "log" );

	//初始化api
	fp_api_init( "180.2.31.170",
		14001,
		&api_callback, 
		"gjy2901\\UserKey.key", 
		"gjy2901\\UserCert.der", 
		"123412", 
		"gjy2901\\RootCert.der",
		NULL );

	while( 1 )
	{
		char buffer[10000];
		scanf( "%s", buffer );
		fp_api_send_msg(buffer,"U98=00");
		//fp_api_send_msg( "X01=GTP1.0,X02=149,X03=A000,X04=1,X05=1,X06=S,X07=0,X08=0,X09=0,", "X63=1,T13=20151214,X79=123456785678,X20=[{X04=1,X05=1},{X04=1,X05=1}],X22=1,M00=0001,M62=123456,X73=10,X74=10,X75=10,X76=10,X77=11231123" );
	}


	fp_api_wait();

	//程序退出时需要释放api空间
	fp_api_free();

	//关闭日志u
	fp_api_log_end();

	return 0;
}