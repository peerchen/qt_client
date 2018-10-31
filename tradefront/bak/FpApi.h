#ifndef	SIGEX_API_H
#define	SIGEX_API_H

#include "ApiConstant.h"
#ifdef __cplusplus
	extern "C"
	{
#endif

		typedef struct API_CALLBACK_
		{

			//----------------------------------------------------------------
			//函数功能：socket连接成功时通知
			//输入参数：无 
			//返 回	值：无
			void ( *on_fp_api_connect )( void *paramter );

			//----------------------------------------------------------------
			//函数功能：socket连接异常断开时通知
			//输入参数：无 
			//返 回	值：无
			void ( *on_fp_api_connect_lost )( void *paramter );

			//----------------------------------------------------------------
			//函数功能：广播socket连接成功时通知
			//输入参数：无 
			//返 回	值：无
			void ( *on_fp_api_exception )( const char *exception_code, const char *exception_msg, void *paramter );

			//----------------------------------------------------------------
			//函数功能：收到报文
			//输入参数：Gtp格式报文
			//返 回	值：无
			void ( *on_fp_api_recv_msg )( const char *packet, void *paramter );

		}API_CALLBACK;

		int FP_API fp_api_init( const char   *ip,           //前置地址
								const int    port,          //前置端口
								API_CALLBACK *api_callback, //回调函数
								const char   *private_cert_path,    //私钥证书路径
								const char   *public_cert_path,     //公钥证书路径
								const char   *public_server_cert_path,//服务器公钥证书路径
								const char   *private_cert_password,//私钥证书密码
								const char   *cert_cert_path,       //根证书密码
								void         *paramter );

		void FP_API fp_api_wait();

		int FP_API fp_api_send_msg( const char *head, const char *body );

		const char FP_API*fp_api_get_version( );

		void FP_API fp_api_free();

		int FP_API fp_api_set_recv_timeout( long long rt);

		long long FP_API fp_api_get_recv_timeout();

		int FP_API fp_api_set_send_timeout( long long wt);

		long long FP_API fp_api_get_send_timeout();

		int FP_API fp_api_log_start( const char * tname );

		void FP_API fp_api_log_end(void);
#ifdef __cplusplus
	}
#endif
#endif
