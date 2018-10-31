
#include <stdio.h>
#include "FpApi.h"


void onFpConnectLostTrade( void *pParamter )
{
	printf( "onFpConnectLostTrade" );
}

void onFpConnectLostBroadcast( void *pParamter )
{
	printf( "onFpConnectLostBroadcast" );
}

void onFpConnectTrade( void *pParamter )
{
	printf( "onFpConnectTrade" );
}

void onFpConnectBroadcast( void *pParamter  )
{
	printf( "onFpConnectBroadcast" );
}

void onFpException( const char *exception_code, const char *exception_msg, void *pParamter )
{
	printf( "onFpException" );
}

void onFpRecvPacket( const char *packet, void *pParamter )
{
	printf( "onFpRecvPacket" );
}

int main(int argc, char **argv)
{
	//初始化回调函数
	API_CALLBACK api_callback;
	api_callback.on_fp_api_recv_msg               = &onFpRecvPacket;
	api_callback.on_fp_api_trade_connect          = &onFpConnectTrade;
	api_callback.on_fp_api_broadcast_connect      = &onFpConnectBroadcast;
	api_callback.on_fp_api_trade_connect_lost     = NULL;
	api_callback.on_fp_api_broadcast_connect_lost = NULL;
	api_callback.on_fp_api_exception              = NULL;

	//启动日志
	fp_api_log_start( "log" );

	//初始化api
	fp_api_init( "127.0.0.1",10000,"127.0.0.1",10001,&api_callback, "cert/UserCert.der", NULL );


	//发送报文
	//while( ture )
	//{
	//	fp_api_send_msg( "head", "body" );
	//}

	fp_api_wait();

	//程序退出时需要释放api空间
	fp_api_free();

	//关闭日志
	fp_api_log_end();

	return 0;
}