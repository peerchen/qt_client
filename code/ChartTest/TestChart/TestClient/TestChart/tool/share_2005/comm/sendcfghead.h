
#ifndef _SendCFGHead_H
#define _SendCFGHead_H

#ifndef HS_SUPPORT_UNIX
#include "shlobj.h"
#endif

#include "houtaiheader.h"

//sendcfghead.h

struct SysConfig_send
{
#ifndef HS_SUPPORT_UNIX
	CString m_strIP; // 接收端地址
#else
	char m_strIP[_MAX_PATH];
#endif
	int		m_nPort; // 接收端端口

	int		nEntry_TCP			 ;//"TCP_接收外汇外盘港股行情"
#ifndef HS_SUPPORT_UNIX
	CString strEntry_TCP_Addr	 ;//"TCP_地址"
#else
	char strEntry_TCP_Addr[_MAX_PATH]	 ;
#endif
	int		nEntry_TCP_Port		 ;//"TCP_端口"

	//
	int		nEntry_TCP_wh		 ;//"TCP_wh接收外汇外盘港股行情"
#ifndef HS_SUPPORT_UNIX
	CString strEntry_TCP_Addr_wh;
#else
	char strEntry_TCP_Addr_wh[_MAX_PATH] ;//"TCP_wh地址"
#endif
	int		nEntry_TCP_Port_wh	 ;//"TCP_wh端口"
	//

	int		m_nAutoSrcConnect;	// 当和接收断开时，自动断开TCP连接

	int		nEntry_Support_GP	 ;//"Support_沪深"
	int		nEntry_Support_QH	 ;//"Support_期货"
	
	int		nEntry_Support_WH	 ;//"Support_外汇"
	int		m_WH_BASE_RATE		 ; // 基本汇率
	int		m_WH_ACROSS_RATE	 ; // 交叉汇率
	int		m_WH_FUTURES_RATE	 ; // 期汇

	int		nEntry_Support_WP	 ;//"Support_外盘"
	int		nEntry_Support_GG	 ;//"Support_港股"
	int		nEntry_Support_HJ	 ;//"Support_黄金"

	int		nEntry_Support_ZX    ;//支持文件传送

	int		nEntry_Support_MAXPacket;
	int		nEntry_Support_PacketMaxLIvingTime;

	int		nEntry_Support_Name  ; // 商品名称不自动从接口源里获取

	int		nEntry_Support_DataTransmit;			//	支持数据转发
	int     nEntry_TransmitPort;					//	数据转发端口
	int		nEntry_Support_timelapse;				//	支持延时转发
	int		nEntry_Support_timelapse_Delay;			//	延时转发分钟数
	int		nEntry_Support_WriteLogFile;			//	转发数据写入日志文件

	int		nEntry_Support_QHDataAccept;			//  支持行情端口数据接收

	int		nEntry_Support_SettingReportData;		// 人工报价

	int		nEntry_Support_LEVEL2;					// 启用LEVEL2连接

	int		nEntry_Support_LEVEL2RebuildConnection; // 启用LEVEL2Rebuild连接

	int     nEntry_Support_TZTHuangJinQiHuo;		// 启用投资堂黄金期货数据生成

	int     nEntry_Support_JinKaiXun;				// 金凯讯的数据

	int     nEntry_Support_XinJiaPo;				// 新加坡的数据

	int		nEntry_Support_UDPTransmit;				// 启用UDP转发

	int		nEntry_Support_UDPTransmit_Log;			// 是否写UDP转发日志

	int		nEntry_Support_PortToPort;				// 端口数据转发

	int		nEntry_Support_JJT;						// 启用经济通连接

	int		nEntry_Support_CAIHUAGANGGU;			// 财华港股接口
	unsigned int	m_nGGStartPos;					// 港股包请求起始位置

	int		nEntry_Support_TongXin;			// 启用同鑫数据源（新华社专用）

	int		nEntry_Support_LME;				// LME数据源

	int		nEntry_Support_SHGold;			// 上海黄金数据源

	int		nEntry_Support_LILV;			// 利率数据源

	int		nEntry_Support_ZYWL;			// 为中游数据源

	int		nEntry_Support_XHS;				// 新华社内部接口
	char	m_strXHSChech[1024];			// 新华社认证串

	int		nEntry_Support_GuangXiTW;		// 支持广西糖网

	int		nEntry_Support_Oil_XHS;			// 石油期货
	int		nEntry_Support_CurrentOil_XHS;	// 石油即期	

	int		nEntry_Support_DBF;				// 使用dbf同步

	int		nEntry_Support_JSD;				// 支持金士达期货行情
	int		nEntry_Support_JSD_PORT;		// 支持金士达期货行情端口

	int		nEntry_Support_BLOCKINDEX;		// 支持板块指数生成
	char	m_strBlockIndexPath[_MAX_PATH];	// 板块指数文件

	int		nEntry_Support_SunLinux;		// 支持SUNLinux数据发送

	int		nAllSelectItemForceSend;		// 所有选中项强制发送一次
	DWORD   m_dwMaxTransRate;				// 最大每秒发送字节字节数,=0则不限制

	int		m_nSupportDZGY;					// 支持大宗工业行情

	int		nEntry_Support_YiTian;			// 支持倚天数据源

	int     m_nTcpOverTime;					// tcp间隔连接时间

	int		m_dealGGDelayTime;				// 处理港股数据等待时间

	int		m_Entry_AUTOUSERZIP;

	int		nEntry_Auto_Start    ;			// 当我登录windows时自动启动
#ifndef HS_SUPPORT_UNIX
	CString	m_strYFNewsPath;
#else
	char	m_strYFNewsPath[_MAX_PATH];  // 
#endif

	int		m_nHSUDP			;// "UDP外汇外盘港股行情"
	int	    m_nHSUDP_Port		;// "UDP外汇外盘港股行情-端口"

	// 期货
#ifndef HS_SUPPORT_UNIX
	CString m_strQHFile;
#else
	char m_strQHFile[_MAX_PATH]; // 期货文件配置
#endif
	BOOL	m_bUDP;			// 期货使用udp
	int		m_nUDPPort;		// 期货使用udp时端口
	int		m_nUDPWriteLog; // 期货记录日志

	// 外盘
#ifndef HS_SUPPORT_UNIX
	CString m_strWPFile;
#else
	char m_strWPFile[_MAX_PATH];		// 外盘dbf文件
#endif
	int		m_bSupportWenHua;		    // 外盘支持文华dbf

	int		m_bCodeListSort;		    // 代码表自动排序

	int		m_nZXSendSleep;			    // 资讯传送文件和文件之间等待时间
	int		m_nZXDataLen;			    // 传送文件大小限制在（M）
	int		m_nZXSendDirSleep;			// 资讯传送文件，目录之间的等待时间
	int		m_nZXSendFileSleep;			// 资讯传送文件，文件之间的等待时间

	int		m_nJiaoTongPort;			// 接收交通银行外汇数据

	int		m_nTransmitData;			// 发送是否传输数据状态

	// 连接交行地址和端口
	char	 m_strIPJH[_MAX_PATH];
	int		 m_nPortJH;		// 接收端端口
	int		 m_nJiaoHangInitReq; // 从交行请求初始化数据

	int		 m_nGGDealThreadCount;//"港股数据处理线程数"

	int		 m_nJHMaxError;// 交行外汇->收到数据处理最大错误数

	// 初始化时间
	int		m_nInitTime_GP	 ;//"Support_沪深"
	int		m_nInitTime_QH	 ;//"Support_期货"
	int		m_nInitTime_WH	 ;//"Support_外汇"
	int		m_nInitTime_WP	 ;//"Support_外盘"
	int		m_nInitTime_GG	 ;//"Support_港股"
	int		m_nInitTime_HJ	 ;//"Support_黄金"   // added by Ben
			
	int		m_nOpenMapping_Synchronization;	// 是否同步运行
	int		m_nOpenMapping_Independence;	// 独立运行

	int		m_nUsedMappingFile;	// 使用映像读取DBF文件

	// option
	int		m_Send_Option_ReadClose;

	int		m_nLogEveryDate;      // 日志每天一个文件

	int		m_nWriteNowStick;     // 是否记录实时数据和分笔

	int		m_nUsedEnglishName;   // 港股使用英文作为名称

	char	m_dbfGZLX[_MAX_PATH];		// 国债利息库
	char	m_dbfQuanZheng[_MAX_PATH];	// 上证权证信息库

	int		IsTransmit() { return m_nTransmitData; }

	void Print()
	{
#ifdef HS_SUPPORT_UNIX
		printf("接收端地址:%s,接收端端口:%i\r\n 支持数据转发:%i,数据转发端口:%i\r\n gp:%i,qh:%i,wh:%i,wp:%i,gg:%i,hj:%i,zx:%i\r\n",
			m_strIP,m_nPort,
			nEntry_Support_DataTransmit,nEntry_TransmitPort,
			nEntry_Support_GP,
			nEntry_Support_QH,
			nEntry_Support_WH,
			nEntry_Support_WP,
			nEntry_Support_GG,
			nEntry_Support_HJ,
			nEntry_Support_ZX
			); // modified by Ben
#endif
	}

	SysConfig_send()
	{
		Empty();
	}

	void EmptyEx()
	{
		nEntry_Support_GP	 = 0;
		nEntry_Support_QH	 = 0;

		nEntry_Support_WH	 = 0;
		m_WH_BASE_RATE		 = 0; // 基本汇率
		m_WH_ACROSS_RATE	 = 0; // 交叉汇率
		m_WH_FUTURES_RATE	 = 0;

		nEntry_Support_WH    = 1; // 黄金 added by Ben

		nEntry_Support_WP	 = 0;
		nEntry_Support_GG	 = 0;
		nEntry_Support_ZX	 = 0;
		nEntry_Support_DataTransmit    = 0;
		nEntry_Support_Name = 1;
		nEntry_Support_DBF = 1;

		nEntry_Support_timelapse = 0;
		nEntry_Support_timelapse_Delay = 30;
		nEntry_Support_YiTian = 0;
		m_nTcpOverTime = 0;

		nEntry_Support_QHDataAccept = 0;
		nEntry_Support_SettingReportData = 0;
		nEntry_Support_PortToPort = 0;

		nEntry_Support_JJT   = 0;
		nEntry_Support_TongXin = 0;
		nEntry_Support_LME = 0;
		nEntry_Support_SHGold = 0;
		nEntry_Support_LILV = 0;
		nEntry_Support_ZYWL = 0;
		nEntry_Support_XHS = 0;
		nEntry_Support_GuangXiTW = 0;
		nEntry_Support_Oil_XHS = 0;
		nEntry_Support_CurrentOil_XHS = 0;
		nEntry_Support_CAIHUAGANGGU = 0;
		nEntry_Support_TZTHuangJinQiHuo = 0;
		nEntry_Support_JinKaiXun = 0;
		nEntry_Support_XinJiaPo = 0;

		m_nGGStartPos = 0;
		memset(m_strXHSChech,0,sizeof(m_strXHSChech));

		nEntry_Support_LEVEL2 = 0;
		nEntry_Support_LEVEL2RebuildConnection = 0;

		nEntry_Support_UDPTransmit = 0;
		nEntry_Support_UDPTransmit_Log = 0;

		nEntry_TransmitPort  = 0;
		nEntry_Support_WriteLogFile = 0;

		m_nTransmitData = 1;

		m_nOpenMapping_Synchronization = 0;
		m_nOpenMapping_Independence = 0;
		m_nUsedMappingFile = 0;
		m_Send_Option_ReadClose = 0;

		m_nJHMaxError = 0;
		m_nLogEveryDate = 0;
		m_nWriteNowStick = 0;
		m_nUsedEnglishName = 0;
		m_dealGGDelayTime = 0;
		m_Entry_AUTOUSERZIP = 0;	
		
	}

	void Empty()
	{
#ifdef HS_SUPPORT_UNIX
		
		memset(this,0,sizeof(SysConfig_send));
		m_nTransmitData = 1;

		m_dealGGDelayTime = 0;
#else
		memset(m_strXHSChech,0,sizeof(m_strXHSChech));

		m_nTransmitData = 1;		
		m_Entry_AUTOUSERZIP = 0;

		m_strIP = "";
		m_nPort = 0;

		nEntry_TCP			 = 0;
		strEntry_TCP_Addr	 = "";
		nEntry_TCP_Port		 = 0;

		nEntry_TCP_wh		 = 0; //"TCP_wh接收外汇外盘港股行情"
		strEntry_TCP_Addr_wh = "";//"TCP_wh地址"
		nEntry_TCP_Port_wh	 = 0; //"TCP_wh端口"

		m_nAutoSrcConnect    = 0;

		nEntry_Support_GP	 = 0;
		nEntry_Support_QH	 = 0;

		nEntry_Support_WH	 = 0;
		m_WH_BASE_RATE		 = 0; // 基本汇率
		m_WH_ACROSS_RATE	 = 0; // 交叉汇率
		m_WH_FUTURES_RATE	 = 0;

		nEntry_Support_WP	 = 0;
		nEntry_Support_GG	 = 0;
		nEntry_Support_ZX	 = 0;
		nEntry_Support_DataTransmit    = 0;
		nEntry_Support_timelapse = 0;
		nEntry_Support_timelapse_Delay = 30;
		nEntry_Support_YiTian = 0;
		m_nTcpOverTime = 0;
		nEntry_Support_JJT   = 0;
		nEntry_Support_LEVEL2 = 0;
		nEntry_Support_LEVEL2RebuildConnection = 0;
		nEntry_TransmitPort  = 0;
		nEntry_Support_WriteLogFile = 0;
		nEntry_Support_DBF = 1;
		nEntry_Support_XHS = 0;
		nEntry_Support_GuangXiTW = 0;

		nEntry_Support_Oil_XHS = 0;
		nEntry_Support_CurrentOil_XHS = 0;
		nEntry_Support_CAIHUAGANGGU = 0;
		m_nGGStartPos = 0;

		nEntry_Support_QHDataAccept = 0;
		nEntry_Support_SettingReportData = 0;
		nEntry_Support_PortToPort = 0;

		m_nSupportDZGY       = 0;		 //支持大宗工业行情

		nEntry_Auto_Start	 = 0;

		m_nHSUDP = 0;
		m_nHSUDP_Port = 0;

		m_bUDP = 0;				// 期货使用udp
		m_nUDPPort = 0;

		m_bSupportWenHua = 0;   // 外盘支持文华dbf
		nEntry_Support_Name = 1;

		//
		nAllSelectItemForceSend = 0;
		m_dwMaxTransRate = 0;

		m_bCodeListSort = 1;

		m_nZXSendSleep = 0;
		m_nZXDataLen = 0;

		m_nInitTime_GP = 30;//"Support_沪深"
		m_nInitTime_QH = 30;//"Support_期货"
		m_nInitTime_WH = 1;//"Support_外汇"
		m_nInitTime_WP = 1;//"Support_外盘"
		m_nInitTime_GG = 50;//"Support_港股"

		m_Send_Option_ReadClose = 0;

		m_nJHMaxError = 0;
		m_nLogEveryDate = 0;
		m_nWriteNowStick = 0;
		m_nUsedEnglishName = 0;

		memset(m_dbfGZLX,0,sizeof(m_dbfGZLX));

		memset(m_dbfQuanZheng,0,sizeof(m_dbfQuanZheng));
		
		m_dealGGDelayTime = 0;

		nEntry_Support_MAXPacket = 50000;

		m_nUDPWriteLog = 0;

#endif
	}

	BOOL IsSupportZX()
	{
		return nEntry_Support_ZX;
	}

	BOOL IsSupport(HSMarketDataType cBourse)
	{	
		if( WhoMarket(cBourse,STOCK_MARKET) )
		{
			return nEntry_Support_GP;
		}
		else if( WhoMarket(cBourse,HK_MARKET) )
		{
			return nEntry_Support_GG;
		}
		else if( WhoMarket(cBourse,FUTURES_MARKET) )
		{
			return nEntry_Support_QH;
		}
		else if( WhoMarket(cBourse,WP_MARKET) )
		{
			return nEntry_Support_WP;
		}
		else if( WhoMarket(cBourse,HJ_MARKET) )
		{
			return nEntry_Support_HJ;
		}
		else if( WhoMarket(cBourse,FOREIGN_MARKET) )
		{
			// 基本汇率
			if( MakeMainMarket(cBourse) == (FOREIGN_MARKET | WH_BASE_RATE) ) 
			{
				if( m_WH_BASE_RATE != 0 )
					return m_WH_BASE_RATE;
			}
			// 交叉汇率
			else if( MakeMainMarket(cBourse) == (FOREIGN_MARKET | WH_ACROSS_RATE) ) 
			{
				if( m_WH_ACROSS_RATE != 0 )	
					return m_WH_ACROSS_RATE;
			}
			// 期汇
			else if( MakeMainMarket(cBourse) == (FOREIGN_MARKET | WH_FUTURES_RATE) ) 
			{
				if( m_WH_FUTURES_RATE != 0)	
					return m_WH_FUTURES_RATE;
			}

			return ( nEntry_Support_WH && (m_WH_BASE_RATE == 0 && m_WH_ACROSS_RATE == 0 && m_WH_FUTURES_RATE == 0) );
			//return nEntry_Support_WH;
		}
		return 0;
	}
};

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else//#ifndef HS_SUPPORT_UNIX
static CString GetBrowsePath(CString strTitle = _T("请选择目录。"),int ulFlags = BIF_EDITBOX)
{
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = AfxGetMainWnd()->m_hWnd;
	bi.ulFlags = BIF_EDITBOX;//BIF_EDITBOX;// | BIF_RETURNONLYFSDIRS;// | BIF_STATUSTEXT;// | BIF_NEWDIALOGSTYLE;

	CString strPath;

	bi.lpszTitle = strTitle;
	LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
	if ( pidl != 0 )
	{
		// get the name of the folder
		TCHAR path[MAX_PATH];
		if ( SHGetPathFromIDList ( pidl, path ) )
		{
			strPath  = path;
			strPath += "\\";
		}

		// free memory used
		IMalloc* imalloc = 0;
		if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
		{
			imalloc->Free ( pidl );
			imalloc->Release ( );
		}
	}

	return strPath;
}

static void MakeValidPath(CString strBasePath)
{
	int lLen = strBasePath.GetLength();
	if( lLen > 1 && strBasePath[lLen-1] != '\\' )
		strBasePath += "\\";
}
#endif

extern SysConfig_send g_sysSysConfigSend;

//extern ShareMarketFile   g_sShareMarketFile;
#endif
