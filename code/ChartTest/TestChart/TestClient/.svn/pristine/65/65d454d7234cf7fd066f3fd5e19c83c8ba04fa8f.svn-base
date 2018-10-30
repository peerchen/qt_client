/*******************************************************************************
 * Copyright (c)2003, 讯捷软件有限公司
 * All rights reserved.
 *
 * 文件名称：commapi.h
 * 文件标识：通讯模块结构接口定义
 * 摘    要：通讯模块结构接口定义
 *
 * 当前版本：2.0
 * 作    者：讯捷软件有限公司
 * 完成日期：
 *
 * 取代版本：
 * 原 作 者：讯捷软件有限公司
 * 完成日期：
 * 备	 注：
 *******************************************************************************/
#ifndef INC_COMMAPI_H
#define INC_COMMAPI_H

#pragma pack(1)

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////////////////
//Notify Message : DLL ==> User

// OnThisMessage(WPARAM wParam, LPARAM lParam)
// wParam : not used
// lParam : pointer to struct CNI_General or derived struct
// DLL uses SendMessage(not PostMessage) to send the message.

#define Comm_Setting_Section	   "通讯设置-市场分类开关"

// 公共常量
#define CEV_Connect_HQ		       HS_LANGUAGE("行情") // 行情
#define CEV_Connect_QH		       HS_LANGUAGE("期货") // 期货
#define CEV_Connect_ZX		       HS_LANGUAGE("资讯") // 资讯
#define CEV_Connect_WH			   HS_LANGUAGE("外汇") // 外汇
#define CEV_Connect_GG			   HS_LANGUAGE("港股") // 港股
#define CEV_Connect_WP			   HS_LANGUAGE("外盘") // 外盘8
#define CEV_Connect_HJ			   HS_LANGUAGE("黄金") // 黄金 added by Ben
#define CEV_Connect_JY			   HS_LANGUAGE("交易") // 交易

#define CEV_Connect_HQ_		       1 // 行情
#define CEV_Connect_QH_		       2 // 期货
#define CEV_Connect_ZX_		       3 // 资讯
#define CEV_Connect_WH_			   4 // 外汇
#define CEV_Connect_GG_			   5 // 港股
#define CEV_Connect_WP_			   6 // 外盘
#define CEV_Connect_JY_			   7 // 交易
#define CEV_Connect_HJ_			   8 // 黄金 added by Ben
#define CEV_Connect_Any			   20 // 任意

#define CEV_Connect_AllInfo		     "站点公共信息"
#define CEV_Connect_ProxyInfo        HS_LANGUAGE("代理")        //yangdl 2008.02.01 交易代理
#define CEV_Connect_InfoFile_version HS_LANGUAGE("当前版本号")
#define CEV_Connect_Force_version    HS_LANGUAGE("强制使用服务器配置")
#define CEV_Connect_Old_version		 HS_LANGUAGE("是否为旧的版本")
#define CEV_Connect_InternetGroup	 HS_LANGUAGE("站点分组信息")


#define CEV_Connect_StartAuto	   HS_LANGUAGE("启动时自动登录")
#define CEV_Connect_LoginPass	   HS_LANGUAGE("使用统一用户认证")

#define CEV_Connect_AutoSelect	   HS_LANGUAGE("自动选择站点") // 和每组地址对应

#define CEV_Connect_LoopNext	   HS_LANGUAGE("自动选择下一站点")
#define CEV_Connect_DisAutoConn    HS_LANGUAGE("断线自动重连")

#define CEV_Connect_UseIE		   HS_LANGUAGE("使用浏览器的网络设置")
#define CEV_Connect_UseDial		   HS_LANGUAGE("使用拨号网络")
#define CEV_Connect_DialEntry	   HS_LANGUAGE("拨号名称")

#define CEV_Connect_UseProxy	   HS_LANGUAGE("使用代理服务器")
#define CEV_Connect_UseProxy_Addr  HS_LANGUAGE("代理服务器地址")
#define CEV_Connect_UseProxy_Port  HS_LANGUAGE("代理服务器端口")
#define CEV_Connect_UseProxy_User  HS_LANGUAGE("代理服务器用户名")
#define CEV_Connect_UseProxy_Pass  HS_LANGUAGE("代理服务器密码")
#define CEV_Connect_UseProxy_Type  HS_LANGUAGE("代理服务器类型")


#define PI_SOCKS		0					//	使用SOCKS5代理协议
#define PI_HTTP			1					//	使用HTTP代理协议
#define PI_SOCKS5		2					//	使用SOCKS5代理协议
#define PI_HTTPGET		3					//	使用HTTP<Get>代理协议<binary>
#define PI_HTTPGETText	4					//	使用HTTP<Get>代理协议<text>
#define PI_SOCKS4A      5                   //  使用SOCKS4A代理协议

//	代理服务器信息
struct ProxyInfo
{
	CString	m_strUser;					//	用户名
	CString	m_strPwd;					//	用户密码
	CString	m_strProxyIP;				//	代理服务器地址
	int		m_nPort;					//	代理服务器端口
	int		m_nOptions;					//	代理协议

	CString m_base64str;

	ProxyInfo()
	{
		m_nPort = 0;
		m_nOptions = PI_SOCKS;
	}
};

struct ProxyInfoEx
{
	char	m_strUser[64];					//	用户名
	char	m_strPwd[64];					//	用户密码
	char	m_strProxyIP[128];				//	代理服务器地址
	int		m_nPort;						//	代理服务器端口
	int		m_nOptions;						//	代理协议

	ProxyInfoEx()
	{
		memset(this,0,sizeof(ProxyInfoEx));
		m_nOptions = PI_SOCKS;
	}
};

struct ProxyInfoExOld
{
	char	m_strUser[64];					//	用户名
	char	m_strPwd[64];					//	用户密码
	char	m_strProxyIP[17];				//	代理服务器地址
	int		m_nPort;					//	代理服务器端口
	int		m_nOptions;					//	代理协议

	ProxyInfoExOld()
	{
		memset(this,0,sizeof(ProxyInfoExOld));
		m_nOptions = PI_SOCKS;
	}
};

//	用户信息结构
struct UserInfo				
{
	CString	m_strUser;					//	用户名
	CString	m_strPwd;					//	用户密码
	BOOL	m_bSavePwd;					//	是否需要记住密码
};

struct UserInfoEx				
{
	char	m_strUser[64];					//	用户名
	char	m_strPwd[64];					//	用户密码
	char	m_bSavePwd;					//	是否需要记住密码
};

// gbq add
#define		CCI_REGISTERUSER			0x00000001		// 注册用户

#define		ClxCommonalityInfo_Version  1

// 站点公共信息
struct ClxCommonalityInfo
{
	char	  m_strHQ[128];  // 行情缺省站点
	char	  m_strQH[128];  // 期货缺省站点
	char	  m_strZX[128];  // 资讯缺省站点
	char	  m_strWH[128];  // 外汇缺省站点
	char	  m_strGG[128];  // 港股缺省站点
	char	  m_strWP[128];	 // 外盘缺省站点
	char	  m_strHJ[128];	 // 黄金缺省站点  added by Ben

	char      m_cStartByTrader; // 交易端启动标志 added by Ben 20100818
	char	  m_cStartAuto;     //	   "启动时自动登录"
	char	  m_cLoginPass;     //	   "所以站点使用统一的用户验证"

	char      m_cHQAutoSelect;  // 是否自动选择站点
	char      m_cQHAutoSelect; 
	char      m_cZXAutoSelect; 
	char      m_cWHAutoSelect; 
	char      m_cGGAutoSelect; 
	char	  m_cWPAutoSelect;
	char	  m_cHJAutoSelect; // added by Ben

	char      m_cHQAutoAddLogin;  // 自动添加到登录页面
	char      m_cQHAutoAddLogin; 
	char      m_cZXAutoAddLogin; 
	char      m_cWHAutoAddLogin; 
	char      m_cGGAutoAddLogin; 
	char	  m_cWPAutoAddLogin;
	char	  m_cHJAutoAddLogin;

	char	  m_cLoopNext;		// 自动选择下一站点
	char	  m_cDisAutoConn;	// 断线自动重连

	char	  m_cUseIE;				 // 使用浏览器的网络设置

	char	  m_cUseDial;			 // 是否使用拨号
	char      m_strDialEntry[128];   // 当前拨号名称

	char		m_cProxy;		  // 是否使用代理
	ProxyInfoExOld m_sProxyInfoOld;     // 代理信息

	UserInfoEx  m_sUserInfoEx;

	char		m_cUsedSimplify; // 是否使用精简登录方式
	char		m_cSaveAccount;  // 保存账号
	
	// gbq modify 20060615, 增加标识功能
	/* old
	char		m_szReserve[11]; // 保留
	*/
	char		m_cServerType;	 // 宽带服务商, 如电信、网通等
	char		m_cStartSelect;	 // 启动选择
	short		m_cFlags;		 // 标识
	char	    m_cJYAutoSelect;
	char	    m_cJYAutoAddLogin;
	char        m_cstrJY;        //yangdl 2008.01.23 交易默认选择项
	HWND        hwndNotify;      //yangdl 2008.02.01 交易窗口句柄
	//char		m_szReserve[4];  // 保留
	int			m_nVersion;
	ProxyInfoEx m_sProxyInfo;     // 代理信息
	//

	char	     m_strJY[128];

	BOOL GetFlags(short nMask)
	{
		return m_cFlags & nMask;
	}

	void SetFlags(short nMask, BOOL b = TRUE)
	{
		if( b )
			m_cFlags |= nMask;
		else
			m_cFlags &= ~nMask;
	}

	BOOL IsAutoSelect(char cType)
	{
		switch(cType)
		{
		case CEV_Connect_HQ_: return m_cHQAutoSelect;  // 行情缺省站点
		case CEV_Connect_QH_: return m_cQHAutoSelect;  // 期货缺省站点
		case CEV_Connect_ZX_: return m_cZXAutoSelect;  // 资讯缺省站点
		case CEV_Connect_WH_: return m_cWHAutoSelect;  // 外汇缺省站点
		case CEV_Connect_GG_: return m_cGGAutoSelect;  // 港股缺省站点
		case CEV_Connect_WP_: return m_cWPAutoSelect;  // 外盘缺省站点
		case CEV_Connect_HJ_: return m_cHJAutoSelect;  // 黄金缺省站点
		case CEV_Connect_JY_: return m_cJYAutoSelect;  // 交易缺省站点
		}
		return 0;
	}

	CString GetDefaultSrv(char cType)
	{
		switch(cType)
		{
		case CEV_Connect_HQ_: return m_strHQ;  // 行情缺省站点
		case CEV_Connect_QH_: return m_strQH;  // 期货缺省站点
		case CEV_Connect_ZX_: return m_strZX;  // 资讯缺省站点
		case CEV_Connect_WH_: return m_strWH;  // 外汇缺省站点
		case CEV_Connect_GG_: return m_strGG;  // 港股缺省站点
		case CEV_Connect_WP_: return m_strWP;  // 外盘缺省站点
		case CEV_Connect_HJ_: return m_strHJ;  // 黄金缺省站点
		case CEV_Connect_JY_: return m_strJY;  // 交易缺省站点
		}
		return "";
	}

	char GetAutoAddLogin()
	{
		return (m_cHQAutoAddLogin + m_cQHAutoAddLogin +
			    m_cZXAutoAddLogin + m_cWHAutoAddLogin +
				m_cGGAutoAddLogin + m_cWPAutoAddLogin + m_cHJAutoAddLogin);
	}

	void EmptyAutoAddLogin(char* pCur,char cValue)
	{
		if( pCur == NULL )
			return;

		if( pCur != &m_cHQAutoAddLogin )
			m_cHQAutoAddLogin = 0;  // 自动添加到登录页面
		if( pCur != &m_cQHAutoAddLogin )
			m_cQHAutoAddLogin = 0; 
		if( pCur != &m_cZXAutoAddLogin )
			m_cZXAutoAddLogin = 0; 
		if( pCur != &m_cWHAutoAddLogin )
			m_cWHAutoAddLogin = 0; 
		if( pCur != &m_cGGAutoAddLogin )
			m_cGGAutoAddLogin = 0; 
		if( pCur != &m_cWPAutoAddLogin )
			m_cWPAutoAddLogin = 0;
		if( pCur != &m_cJYAutoAddLogin )
			m_cJYAutoAddLogin = 0;
		if( pCur != &m_cHJAutoAddLogin )
			m_cHJAutoAddLogin = 0;
		*pCur = cValue;
	}
};

//
#define CEV_START_CONNECT	0x0001
#define CEV_CONNECT_PROMPT	0x0100
#define CEV_CONNECT_FAIL	0x0002
#define CEV_CONNECT_SUCC	0x0004
#define CEV_DISCONNECTED	0x0008
#define CEV_ALLCLOSED		0x0010
#define CEV_RECEIVE_DATA	0x0020
#define CEV_SEND_DATA		0x0040
#define CEV_IDLE			0x0200
#define CEV_ASK_DATA		0x0400		//DLL ask User for some data.

#define CEV_HTTP_SUCCINFO	0x1000		//http 下载使用,成功信息
#define CEV_HTTP_FAILINFO	0x2000	    //http 下载使用,失败信息

//yangdl 2008.01.29 交易消息
#define CEV_HQJY_COMMSET	0x4000		//设置交易
#define CEV_HQJY_COMMRETURN	0x8000	    //设置成功返回
//客户端数据包报头
struct CNI_General
{
	int	 m_nSize;	// 数据包长度
	long m_lCommID;	// 通讯属主
	int	 m_nEvent;	// 事件, CEV_...

	long m_nLoginSrvType;	// 参见RT_LOGIN定义
};
//客户端数据包连接后提示
struct CNI_ConnectPrompt
{
	struct CNI_General m_hd;	//客户端数据包报头
	const TCHAR *m_pszPrompt;	//提示
};
//连接失败
struct CNI_ConnectFail
{
	struct CNI_General m_hd;		//客户端数据包报头
	BOOL m_bServerContacted;		//是否已经与服务器建立了连接
	const TCHAR FAR *m_pszErrorText;//错误信息
};
//连接成功
struct CNI_ConnectSucc
{
	struct CNI_General m_hd;	//客户端数据包报头
	int	   m_nMaxConnectTime;	//连接分钟数
	const char* m_pszData;		//成功信息
};
//断开连接
struct CNI_Disconnected
{
	struct CNI_General m_hd;	//客户端数据包报头
	int m_nLocalOrRemote;		//本地断开还是服务器断开 local : 0; remote : 1
};

// http 下载使用
struct CNI_HttpInfo
{
	struct CNI_General m_hd;		 //客户端数据包报头
	long   m_lFileSize;				 // 文件大小
	long   m_lFileDownloadedSize;    // 已下载大小
	const TCHAR FAR *m_pszText;		 // 要下载的实际文件名
};

#define CLX_TS_START	0x0001
#define CLX_TS_MIDDLE   0x0002
#define CLX_TS_END      0x0004
#define CLX_TS_ERROR    0x0008
#define CLX_TS_CANCEL	0x0010

// http
#define CLX_HTTP_TS_START	0x0100
#define CLX_HTTP_TS_MIDDLE  0x0200
#define CLX_HTTP_TS_END     0x0400
#define CLX_HTTP_TS_ERROR   0x0800
#define CLX_HTTP_TS_CANCEL	0x1000
//客户端接受数据通用包
struct CNI_ReceiveData
{
	struct CNI_General m_hd;	//数据报头
	int m_nStatus;				// 状态CLX_TS_...
	BOOL m_bFile;				//是否为文件
	long m_lDataTotal;			//数据长度
	long m_lDataTransmited;		//已经传送的数据长度
	const char* m_pszData;		// if m_bFile is TRUE, m_pszData points to file name
};

#define CNI_SendData CNI_ReceiveData
//请求属主信息
#define CLX_AD_INIT		0x0001		//ask for init data.
struct CNI_AskData
{
	struct CNI_General	m_hd;
	short				m_nType;	//CLX_AD_...
};

///////////////////////////////////////////////////////////////////////////////////////////
// API : User ==> DLL

#define YLS_HXTRANSTYPE_			0x0001//11
#define YLS_haowangjiaoTRANSTYPE_		0x0002//254
#define YLS_haowangjiaoSOURCETRANS_	0x0004//255
#define YLS_CURTYPE					0x0008//10

#define YLS_NotSendPacketTest		0x0100//不发送数据包，测试通讯
#define YLS_DFXComm					0x0200//1.5xfd通讯
#define YLS_TestConnect				0x0400//测试connect
#define YLS_User_Pwd				0x0800//使用通讯内部用户名和密码

#define YLS_NotUser					0x1000//不检测用户
#define YLS_NotZip					0x2000//不发送时不做压缩处理
#define YLS_RawRecSend				0x4000//原始接收发送
#define YLS_HttpRecSend				0x8000//HTTP发送接收

#define YLS_RecRaw					0x0010//接收数据原始发送
#define YLS_RecDataWriteFile		0x0020//接收数据写入到文件
#define YLS_SendLoginData			0x0040//发送登陆数据
#define YLS_SendSrvLoad				0x0080//需要服务器返回负载信息


//当前的主站设置
#define YLS_OPEN_LOGIN		0x0001		// 登录
#define YLS_OPEN_SET		0x0002		// 行情设置
#define YLS_OPEN_REFRESH	0x0004		// 刷新配置文件
#define YLS_OPEN_AddTest	0x0008		// 地址测试
#define YLS_OPEN_SetProxy   0x0010      // xxhhss代理设置 yangdl 2008.09.04     

//连接信息
struct YlsConnectUsrInfo
{
	char	m_cUsed;			// 是否使用

	char    m_strServerName[64];//服务器名称
	char	m_strServerIP[128];	//IP
	unsigned short	m_nPort;			//port

	char	m_strID[64];		//用户ID
	char	m_strPwd[64];		//密码
	char	m_bSavePwd;			//是否保存密码
};

//连接参数
struct ClxConnectParam
{
	char	m_strServerID[128];		//服务器名称
	char	m_strCommProtocol[64];	//协议,新的没有用

	char    m_bSavePwd;
	char	m_strID[64];			//登录ID
	char	m_strPwd[64];			//密码

	char	       m_strServerIP_old[17];	//17    IP
	unsigned short m_nPort;					//short port	
	
	short	m_nTransType;			// 传输类型

	HWND	m_hwndNotify;			// 消息句柄
	long*	m_plCommID;				// 属主

	char	m_cServerType;			// 服务器类型, 用于标识电信、网通等运营商
	char	m_cReserved;			// 启动时提示选择
	short	m_lGotoSrv;				// 是否跳转

	long	m_nSrvType;			    //服务器请求类型

	char	m_strServerIP[128];		// 2006.09.14 添加
	short	m_nSrvID;				// 服务器标示id 2007.09.03 add 
	short   m_nModify;              // yangdl 2008.01.23 交易是否可修改 

	short	    m_nCookieLen;			// 2008.04.22 by yls cookie 串长度 
	const char*	m_pCookiePtr;			// 2008.04.22 by yls cookie 串ptr 

	short	m_lReserved2[5];	    // 2006.09.14 添加 8
	
	YlsConnectUsrInfo m_sZiXunSrv;	//关联到资讯,新的没有用

	ClxConnectParam()
	{
		memset(this,0,sizeof(ClxConnectParam));
	}

	// 复制和连接有关的信息
	BOOL Copy(ClxConnectParam* pData,ClxCommonalityInfo* pCommonalityInfo = NULL)
	{
		if( pData == NULL )
			return FALSE;

		// 段名
		strncpy(m_strServerID,pData->m_strServerID,sizeof(m_strServerID));

		// 地址、端口 
		strncpy(m_strServerIP,pData->m_strServerIP,sizeof(m_strServerIP));
		m_nPort = pData->m_nPort;

		// 用户名、密码
		if( pCommonalityInfo && pCommonalityInfo->m_cLoginPass ) // 
		{			
			strncpy(m_strID,pCommonalityInfo->m_sUserInfoEx.m_strUser,sizeof(m_strID));
			strncpy(m_strPwd,pCommonalityInfo->m_sUserInfoEx.m_strPwd,sizeof(m_strPwd));
			m_bSavePwd = pCommonalityInfo->m_sUserInfoEx.m_bSavePwd;
		}
		else
		{
			strncpy(m_strID,pData->m_strID,sizeof(m_strID));
			strncpy(m_strPwd,pData->m_strPwd,sizeof(m_strPwd));
			m_bSavePwd = pData->m_bSavePwd;
		}

		return TRUE;
	}
};

#define	CO_ONETON		0x0001		//可建立一对多连接
#define	CO_NINONE		0x0002		//可有多条连接
#define	CO_LOCAL		0x0004		//本地通讯
#define	CO_INTERNAL		0x0008		//内部使用
//未使用
typedef struct tagClxCaps
{
	const TCHAR*	m_pszClass;
	const TCHAR*	m_pszID;
	const TCHAR*	m_pszName;
	long		m_lOptions;	
	long		m_lReserved;
} ClxCaps;

//当前的主站设置
#define CC_SERVERNAME		0x0001		//主站名称
#define CC_USERID			0x0002		//用户ID(可有多个,用 ; 分开)
#define CC_USERPWD			0x0003		//用户密码(可有多个,用 ; 分开)
#define CC_WRITE_USERID		0x0004		//设置用户ID(可有多个,用 ; 分开)

typedef void (WINAPI *SessionCloseHook)(long lCommID);

#ifdef _USE_COMMDLL
//用户端使用的函数
BOOL WINAPI ClxCommInit(const TCHAR* pszProfile);
int  WINAPI ClxEnumCommProtocol(TCHAR* pszBuf, int nLen);
BOOL WINAPI ClxConnect(ClxConnectParam *pConnectParam);
BOOL WINAPI ClxIsConnect(long lCommID);
BOOL WINAPI ClxDisconnect(long lCommID);
BOOL WINAPI ClxSendData(long lCommID, const char* pszBuffer, int cbBuffer);
BOOL WINAPI ClxSendFile(long lCommID, const TCHAR* pszFileName);
BOOL WINAPI ClxGetLastError(TCHAR* szBuf, int nLen);

void WINAPI ClxCloseAll(HWND hWnd);

BOOL WINAPI ClxSetCommOptions(const TCHAR* pszParam, const TCHAR* pszCommProtocol, HWND hwndParent);
BOOL WINAPI ClxSetSystemOptions(const TCHAR* pszParam, const TCHAR* pszCommProtocol, HWND hwndParent);
int  WINAPI ClxOperator(const TCHAR* pszCommProtocol, const TCHAR* pszOperator, void* pData, int nLen);
BOOL WINAPI ClxGetCaps(const TCHAR* pszCommProtocol, ClxCaps* pCaps);
int  WINAPI ClxGetCurSetting(const TCHAR* pszCommProtocol, long lOperator, const TCHAR* pszParam, TCHAR* pBuf, int nLen);

#endif

//动态调用的函数(各通讯动态库的输出函数)
typedef BOOL (WINAPI *Clx_CommInit)(const TCHAR* pszProfile, SessionCloseHook pHook);
typedef BOOL (WINAPI *Clx_Connect)(ClxConnectParam* pConnectParam);
typedef BOOL (WINAPI *Clx_IsConnect)(long lCommID);
typedef BOOL (WINAPI *Clx_Disconnect)(long lCommID);
typedef BOOL (WINAPI *Clx_SendData)(long lCommID, const char* pszBuffer, int cbBuffer);
typedef BOOL (WINAPI *Clx_SendFile)(long lCommID, const TCHAR* pszFileName);
typedef BOOL (WINAPI *Clx_GetLastError)(TCHAR* szBuf, int nLen);

typedef void (WINAPI *Clx_CloseAll)();

typedef BOOL (WINAPI *Clx_SetCommOptions)(const TCHAR* pszProfile, const TCHAR* pszParam, HWND hwndParent);
typedef BOOL (WINAPI *Clx_SetSystemOptions)(const TCHAR* pszProfile, const TCHAR* pszParam, HWND hwndParent);
typedef int  (WINAPI *Clx_Operator)(const TCHAR* pszProfile, const TCHAR* pszOperator, void* pData, int nLen);
typedef int  (WINAPI *Clx_GetCurSetting)(const TCHAR* pszProfile, long lOperator, const TCHAR* pszParam, TCHAR* pBuf, int nLen);
typedef void (WINAPI *Clx_GetCaps)(const TCHAR* pszProfile, ClxCaps *pCaps);

#ifdef __cplusplus
}
#endif

#pragma pack()
#endif


