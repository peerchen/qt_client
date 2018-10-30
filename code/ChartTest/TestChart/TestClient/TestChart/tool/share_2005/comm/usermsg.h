
#pragma once

#ifdef HS_SUPPORT_UNIX
#	define WM_USER 0x0400 
#endif

#define WM_RECEIVEDDATA		 (WM_USER + 111)
#define WM_ACCEPTSESSION	 (WM_USER + 112)
#define WM_SESSIONEND		 (WM_USER + 113)
#define WM_DATAREADY		 (WM_USER + 114)
#define WM_MONITOR			 (WM_USER + 115)
#define WM_SESSIONSTART		 (WM_USER + 116)

#define WM_SEND_SESSION_DATA (WM_USER + 117)


#define ID_COMMU		1
#define ID_SH_INDEX		2
#define ID_SZ_INDEX		3
#define ID_MESSAGE		4
#define ID_SENDDATA		5

#define ID_DELTHREAD				6
#define ID_DELMinuteDataItem		7
#define ID_MESSAGE_STRING			8

#define ID_PROMPT		9

#define ID_UDP_HS		10 // %6666666666%udp状态
#define ID_UDP_DZST		11 // 广西大宗食糖交易中心有限公司udp状态
#define ID_UDP_WBJR		12 // 外部udp状态

#define ID_MAINCONNECT	13 // 为主连接行情