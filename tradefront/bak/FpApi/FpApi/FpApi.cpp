// #define DLL_EXPORT

#include "FpApi.h"
#include "FpApiCpMgr.h"

CFpApiCpMgr theMgr;

int fp_api_init(  const char   *ip,
				  const int     port,
				  API_CALLBACK *api_callback,
				  const char   *private_cert_path,
				  const char   *public_cert_path,
				  const char   *private_cert_password,
				  const char   *root_cert_path,
				  void         *paramter )
{
	if( 0 != theMgr.Init( ip, port, api_callback, private_cert_path, public_cert_path, private_cert_password,root_cert_path, paramter ) )
	{
		string code;
		string msg;

		if( ip == NULL || private_cert_path == NULL || public_cert_path == NULL )
		{
			code = "-1";
			msg  = "参数为NULL";
		}
		else
		{
			code = "1";
			msg  = "系统初始化失败";
		}

		if( api_callback != NULL && api_callback->on_fp_api_exception != NULL )
		{
			api_callback->on_fp_api_exception( code.c_str(), msg.c_str(), paramter );
		}
		return -1;
	}
	return 0;
}

void fp_api_wait()
{
	theMgr.GetApi()->Wait();
}


int fp_api_send_msg( const char * head, const char * body)
{
	return theMgr.GetApi()->SendPacket( head, body );
}

const char * fp_api_get_version()
{
	return theMgr.GetApi()->GetVersion();
}

void fp_api_free()
{
	theMgr.Finish();
}

int fp_api_set_recv_timeout( long long rt)
{
	return theMgr.SetTRecv( rt );
}

long long fp_api_get_recv_timeout()
{
	return theMgr.GetTRecv();
}

int fp_api_set_send_timeout( long long wt)
{
	return theMgr.SetTSend( wt );
}

long long fp_api_get_send_timeout()
{
	return theMgr.GetTSend();
}

int fp_api_log_start( const char * tname )
{
	return theMgr.StartLog( tname );
}

void fp_api_log_end(void)
{
	theMgr.StopLog();
}
