#include <iostream>
#include <string.h>
//#include "FpApi.h"

#include "OfferingTrade.h"

using namespace std;

void __recv_msg(const char * msg, int type, unsigned int con_len, void * ctx)
{
	cout << msg << endl;
}

void __cb_connected(api_connection_state_t * cs, void * ctx) 
{
	cout << "connected" << endl;
}


void __cb_disconnect(api_connection_state_t * cs, void * ctx) 
{
	cout << "disconnect" << endl;
}


int main(int argc, char **argv)
{
		S_SGE_GEMS2_API api;
		CBF_SimpleLog log;
		CBF_Xml xml;
		char errmsg[1024];
		
		api.apistruct = new S_SGE_GEMS2_API_STRUCT();
		memset(api.apistruct, 0, sizeof(S_SGE_GEMS2_API_STRUCT));
		api.apistruct->cb_.api_recv_msg_ = __recv_msg; 
		api.apistruct->cb_.api_cb_connected_ = __cb_connected;
		api.apistruct->cb_.api_cb_disconnected_ = __cb_disconnect;
		
		api.apistructpvalue = (UINT64_)(api.apistruct);
		api.apidllhandle = dlopen("libfptrade.so",RTLD_NOW);
		api.apiPoint = (CIOfferingBase *)(((CIOfferingBase*(*)())dlsym(api.apidllhandle,"getInstance"))());
		api.apidllname = "libfptrade.so";
		api.apiInstance = "getInstance";
		api.offernodepath = "/package/head/报盘机配置/交易报盘机";
	
		cout << "xml.FromFile" << endl;
		if( !xml.FromFile("tradefront.xml"))
		{
			cout << "tradefront.xml not find" << endl;
			return 0;
		}
		
		cout << "api.apiPoint->Init" << endl;
		if( !api.apiPoint->Init(&api, &log, &xml, "/package/head/报盘机配置/交易报盘机", errmsg ) )
		{
			cout << "Init false" << endl;
		}
		
		sleep(10);
		
		
		return 0;
}
