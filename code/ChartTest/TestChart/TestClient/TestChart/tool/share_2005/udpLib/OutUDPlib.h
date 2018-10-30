
#if !defined(OutUDPlib_h_)
#define OutUDPlib_h_


#ifdef _DEBUG
	#pragma comment(lib,"..\\..\\Share_2005\\lib\\debug\\udpLib.lib") 
	//#pragma message("Automatically linking with ..\\lib\\debug\\udpLib.lib")  
#else
	#pragma comment(lib,"..\\..\\Share_2005\\lib\\Release\\udpLib.lib") 
	//#pragma message("Automatically linking with ..\\lib\\Release\\udpLib.lib")  
#endif


#include "UdpLink.h"
#include "udpsessionnotify.h"


#endif // OutUDPlib_h_
