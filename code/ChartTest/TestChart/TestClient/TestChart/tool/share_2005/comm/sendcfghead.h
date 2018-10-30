
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
	CString m_strIP; // ���ն˵�ַ
#else
	char m_strIP[_MAX_PATH];
#endif
	int		m_nPort; // ���ն˶˿�

	int		nEntry_TCP			 ;//"TCP_����������̸۹�����"
#ifndef HS_SUPPORT_UNIX
	CString strEntry_TCP_Addr	 ;//"TCP_��ַ"
#else
	char strEntry_TCP_Addr[_MAX_PATH]	 ;
#endif
	int		nEntry_TCP_Port		 ;//"TCP_�˿�"

	//
	int		nEntry_TCP_wh		 ;//"TCP_wh����������̸۹�����"
#ifndef HS_SUPPORT_UNIX
	CString strEntry_TCP_Addr_wh;
#else
	char strEntry_TCP_Addr_wh[_MAX_PATH] ;//"TCP_wh��ַ"
#endif
	int		nEntry_TCP_Port_wh	 ;//"TCP_wh�˿�"
	//

	int		m_nAutoSrcConnect;	// ���ͽ��նϿ�ʱ���Զ��Ͽ�TCP����

	int		nEntry_Support_GP	 ;//"Support_����"
	int		nEntry_Support_QH	 ;//"Support_�ڻ�"
	
	int		nEntry_Support_WH	 ;//"Support_���"
	int		m_WH_BASE_RATE		 ; // ��������
	int		m_WH_ACROSS_RATE	 ; // �������
	int		m_WH_FUTURES_RATE	 ; // �ڻ�

	int		nEntry_Support_WP	 ;//"Support_����"
	int		nEntry_Support_GG	 ;//"Support_�۹�"
	int		nEntry_Support_HJ	 ;//"Support_�ƽ�"

	int		nEntry_Support_ZX    ;//֧���ļ�����

	int		nEntry_Support_MAXPacket;
	int		nEntry_Support_PacketMaxLIvingTime;

	int		nEntry_Support_Name  ; // ��Ʒ���Ʋ��Զ��ӽӿ�Դ���ȡ

	int		nEntry_Support_DataTransmit;			//	֧������ת��
	int     nEntry_TransmitPort;					//	����ת���˿�
	int		nEntry_Support_timelapse;				//	֧����ʱת��
	int		nEntry_Support_timelapse_Delay;			//	��ʱת��������
	int		nEntry_Support_WriteLogFile;			//	ת������д����־�ļ�

	int		nEntry_Support_QHDataAccept;			//  ֧������˿����ݽ���

	int		nEntry_Support_SettingReportData;		// �˹�����

	int		nEntry_Support_LEVEL2;					// ����LEVEL2����

	int		nEntry_Support_LEVEL2RebuildConnection; // ����LEVEL2Rebuild����

	int     nEntry_Support_TZTHuangJinQiHuo;		// ����Ͷ���ûƽ��ڻ���������

	int     nEntry_Support_JinKaiXun;				// ��Ѷ������

	int     nEntry_Support_XinJiaPo;				// �¼��µ�����

	int		nEntry_Support_UDPTransmit;				// ����UDPת��

	int		nEntry_Support_UDPTransmit_Log;			// �Ƿ�дUDPת����־

	int		nEntry_Support_PortToPort;				// �˿�����ת��

	int		nEntry_Support_JJT;						// ���þ���ͨ����

	int		nEntry_Support_CAIHUAGANGGU;			// �ƻ��۹ɽӿ�
	unsigned int	m_nGGStartPos;					// �۹ɰ�������ʼλ��

	int		nEntry_Support_TongXin;			// ����ͬ������Դ���»���ר�ã�

	int		nEntry_Support_LME;				// LME����Դ

	int		nEntry_Support_SHGold;			// �Ϻ��ƽ�����Դ

	int		nEntry_Support_LILV;			// ��������Դ

	int		nEntry_Support_ZYWL;			// Ϊ��������Դ

	int		nEntry_Support_XHS;				// �»����ڲ��ӿ�
	char	m_strXHSChech[1024];			// �»�����֤��

	int		nEntry_Support_GuangXiTW;		// ֧�ֹ�������

	int		nEntry_Support_Oil_XHS;			// ʯ���ڻ�
	int		nEntry_Support_CurrentOil_XHS;	// ʯ�ͼ���	

	int		nEntry_Support_DBF;				// ʹ��dbfͬ��

	int		nEntry_Support_JSD;				// ֧�ֽ�ʿ���ڻ�����
	int		nEntry_Support_JSD_PORT;		// ֧�ֽ�ʿ���ڻ�����˿�

	int		nEntry_Support_BLOCKINDEX;		// ֧�ְ��ָ������
	char	m_strBlockIndexPath[_MAX_PATH];	// ���ָ���ļ�

	int		nEntry_Support_SunLinux;		// ֧��SUNLinux���ݷ���

	int		nAllSelectItemForceSend;		// ����ѡ����ǿ�Ʒ���һ��
	DWORD   m_dwMaxTransRate;				// ���ÿ�뷢���ֽ��ֽ���,=0������

	int		m_nSupportDZGY;					// ֧�ִ��ڹ�ҵ����

	int		nEntry_Support_YiTian;			// ֧����������Դ

	int     m_nTcpOverTime;					// tcp�������ʱ��

	int		m_dealGGDelayTime;				// ����۹����ݵȴ�ʱ��

	int		m_Entry_AUTOUSERZIP;

	int		nEntry_Auto_Start    ;			// ���ҵ�¼windowsʱ�Զ�����
#ifndef HS_SUPPORT_UNIX
	CString	m_strYFNewsPath;
#else
	char	m_strYFNewsPath[_MAX_PATH];  // 
#endif

	int		m_nHSUDP			;// "UDP������̸۹�����"
	int	    m_nHSUDP_Port		;// "UDP������̸۹�����-�˿�"

	// �ڻ�
#ifndef HS_SUPPORT_UNIX
	CString m_strQHFile;
#else
	char m_strQHFile[_MAX_PATH]; // �ڻ��ļ�����
#endif
	BOOL	m_bUDP;			// �ڻ�ʹ��udp
	int		m_nUDPPort;		// �ڻ�ʹ��udpʱ�˿�
	int		m_nUDPWriteLog; // �ڻ���¼��־

	// ����
#ifndef HS_SUPPORT_UNIX
	CString m_strWPFile;
#else
	char m_strWPFile[_MAX_PATH];		// ����dbf�ļ�
#endif
	int		m_bSupportWenHua;		    // ����֧���Ļ�dbf

	int		m_bCodeListSort;		    // ������Զ�����

	int		m_nZXSendSleep;			    // ��Ѷ�����ļ����ļ�֮��ȴ�ʱ��
	int		m_nZXDataLen;			    // �����ļ���С�����ڣ�M��
	int		m_nZXSendDirSleep;			// ��Ѷ�����ļ���Ŀ¼֮��ĵȴ�ʱ��
	int		m_nZXSendFileSleep;			// ��Ѷ�����ļ����ļ�֮��ĵȴ�ʱ��

	int		m_nJiaoTongPort;			// ���ս�ͨ�����������

	int		m_nTransmitData;			// �����Ƿ�������״̬

	// ���ӽ��е�ַ�Ͷ˿�
	char	 m_strIPJH[_MAX_PATH];
	int		 m_nPortJH;		// ���ն˶˿�
	int		 m_nJiaoHangInitReq; // �ӽ��������ʼ������

	int		 m_nGGDealThreadCount;//"�۹����ݴ����߳���"

	int		 m_nJHMaxError;// �������->�յ����ݴ�����������

	// ��ʼ��ʱ��
	int		m_nInitTime_GP	 ;//"Support_����"
	int		m_nInitTime_QH	 ;//"Support_�ڻ�"
	int		m_nInitTime_WH	 ;//"Support_���"
	int		m_nInitTime_WP	 ;//"Support_����"
	int		m_nInitTime_GG	 ;//"Support_�۹�"
	int		m_nInitTime_HJ	 ;//"Support_�ƽ�"   // added by Ben
			
	int		m_nOpenMapping_Synchronization;	// �Ƿ�ͬ������
	int		m_nOpenMapping_Independence;	// ��������

	int		m_nUsedMappingFile;	// ʹ��ӳ���ȡDBF�ļ�

	// option
	int		m_Send_Option_ReadClose;

	int		m_nLogEveryDate;      // ��־ÿ��һ���ļ�

	int		m_nWriteNowStick;     // �Ƿ��¼ʵʱ���ݺͷֱ�

	int		m_nUsedEnglishName;   // �۹�ʹ��Ӣ����Ϊ����

	char	m_dbfGZLX[_MAX_PATH];		// ��ծ��Ϣ��
	char	m_dbfQuanZheng[_MAX_PATH];	// ��֤Ȩ֤��Ϣ��

	int		IsTransmit() { return m_nTransmitData; }

	void Print()
	{
#ifdef HS_SUPPORT_UNIX
		printf("���ն˵�ַ:%s,���ն˶˿�:%i\r\n ֧������ת��:%i,����ת���˿�:%i\r\n gp:%i,qh:%i,wh:%i,wp:%i,gg:%i,hj:%i,zx:%i\r\n",
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
		m_WH_BASE_RATE		 = 0; // ��������
		m_WH_ACROSS_RATE	 = 0; // �������
		m_WH_FUTURES_RATE	 = 0;

		nEntry_Support_WH    = 1; // �ƽ� added by Ben

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

		nEntry_TCP_wh		 = 0; //"TCP_wh����������̸۹�����"
		strEntry_TCP_Addr_wh = "";//"TCP_wh��ַ"
		nEntry_TCP_Port_wh	 = 0; //"TCP_wh�˿�"

		m_nAutoSrcConnect    = 0;

		nEntry_Support_GP	 = 0;
		nEntry_Support_QH	 = 0;

		nEntry_Support_WH	 = 0;
		m_WH_BASE_RATE		 = 0; // ��������
		m_WH_ACROSS_RATE	 = 0; // �������
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

		m_nSupportDZGY       = 0;		 //֧�ִ��ڹ�ҵ����

		nEntry_Auto_Start	 = 0;

		m_nHSUDP = 0;
		m_nHSUDP_Port = 0;

		m_bUDP = 0;				// �ڻ�ʹ��udp
		m_nUDPPort = 0;

		m_bSupportWenHua = 0;   // ����֧���Ļ�dbf
		nEntry_Support_Name = 1;

		//
		nAllSelectItemForceSend = 0;
		m_dwMaxTransRate = 0;

		m_bCodeListSort = 1;

		m_nZXSendSleep = 0;
		m_nZXDataLen = 0;

		m_nInitTime_GP = 30;//"Support_����"
		m_nInitTime_QH = 30;//"Support_�ڻ�"
		m_nInitTime_WH = 1;//"Support_���"
		m_nInitTime_WP = 1;//"Support_����"
		m_nInitTime_GG = 50;//"Support_�۹�"

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
			// ��������
			if( MakeMainMarket(cBourse) == (FOREIGN_MARKET | WH_BASE_RATE) ) 
			{
				if( m_WH_BASE_RATE != 0 )
					return m_WH_BASE_RATE;
			}
			// �������
			else if( MakeMainMarket(cBourse) == (FOREIGN_MARKET | WH_ACROSS_RATE) ) 
			{
				if( m_WH_ACROSS_RATE != 0 )	
					return m_WH_ACROSS_RATE;
			}
			// �ڻ�
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
static CString GetBrowsePath(CString strTitle = _T("��ѡ��Ŀ¼��"),int ulFlags = BIF_EDITBOX)
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
