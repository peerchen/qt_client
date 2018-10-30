/*******************************************************************************
* Copyright (c)2003, 雁联计算系统有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：YLink1.2
* 作    者：YLink王工
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/




#include "stdafx.h"

#include "globalfun.h"
//#include "ylsinifile.h"
#include "ylsini.h"
#include "tool.h"




//#include "hssortdata.h"


//#include <windowsx.h>
//#include "shlwapi.h"

//#include <share.h>
//#include <io.h>
//#include <direct.h>
//#include <dos.h>
//#include <sys\stat.h>


//#include "..\tools\tools.h"


//// 市场分类
//CQHServerMarketInfo g_QHServerMarketInfo; // 期货
//CSHServerMarketInfo g_SHServerMarketInfo; // 上海
//CSZServerMarketInfo g_SZServerMarketInfo; // 深证

// 时时资讯
//ZiXunRunTime_Ex* g_pZiXunRunTime = NULL;


//ShareMarketFile		 g_sShareMarketFile;


HS_EveryTimeData m_sEvery;

// 公告信息
CurInfoSend g_sNoticeSend;
// 跑马灯
CurInfoSend g_sScrollSend;

// 主站信息
ServerInfoData	g_yyySInfoData;
AnsServerInfo2  g_yyySInfoData2;
TestSrvLoad		g_yyyTestSrvLoad;

CHqDataBuffer   g_PublicPromptInfo;  // 全局提示信息

// error文件
char		    g_strErrorFileName[256];
// 当前配置名称
char			g_strCfgfileName[256];
// 进程号等保存
char			g_strCfgDynamic[256];
// 配置文件短名称
char			g_strCfgShortName[256];
// setting路径
char			g_strSettingPath[256];
// 用户信息文件
char			g_strUserfileName[256];
// 通讯状态
char		    g_strCommStatus[256];

// 期货没有处理的代码文件
char		    g_strQiHuoCodeProfile[256];
// 合约名称代码对照表
char		    g_strQiHuoCodeNameProfile[256];// = "合约名称代码对照表.ini";

// 通讯数据日志
char		    g_strCommDataFile[256];



// 最大不同数
int			    g_nMaxDiffCount = 0;
int				g_nDiffCount    = 0;
BOOL			g_bYlsSupportZip = 1;

// 重起服务程序
BOOL		    g_bReStartProgram = FALSE;

// 外汇总数,临时的
//int				g_nWhCount = 0; 

// 初始化所有
int				g_nInitAll = 0; 


// 得到web子路经
const char* GetWebPath(const char* szSubPath,CHqDataBuffer& path)
{
	path.Alloc(_MAX_PATH);

	char szMainPath[_MAX_PATH];
	sprintf(path.m_lpszBuffer,"%s%s%s",CHSFilePath::GetPath(szMainPath,Srv_Config),szSubPath,Yls_Path_Spl);

	return path.m_lpszBuffer;
}

const char* GetWebStyle1()
{
	static CHqDataBuffer path;
	if(path.IsEmpty())
	{
		GetWebPath("swebhq/Templates/Style1",path);
	}
	return path.m_lpszBuffer;
}

const char* GetWebStyle2()
{
	static CHqDataBuffer path;
	if(path.IsEmpty())
	{
		GetWebPath("swebhq/Templates/Style2",path);
	}
	return path.m_lpszBuffer;
}

const char* GetWebStyle3()
{
	static CHqDataBuffer path;
	if(path.IsEmpty())
	{
		GetWebPath("swebhq/Templates/Style3",path);
	}
	return path.m_lpszBuffer;
}

// 代码对应表
CYlsMapStringToPtr	g_mapCodeToCode;
BOOL GetMapCode(CodeInfo* pCurCode,CodeInfo*& pCode)
{	
	if( pCurCode == NULL ||
		MakeMarket(pCurCode->m_cCodeType) != STOCK_MARKET )
		return FALSE;

	char strKey[STOCK_CODE_SIZE + 1];
	memset(strKey,0,sizeof(strKey));
	strncpy(strKey,pCurCode->m_cCode,STOCK_CODE_SIZE);
	strKey[STOCK_CODE_SIZE] = '\0';

	YlsRTrim(strKey);

	if( g_mapCodeToCode.GetCount() <= 0 )
		return FALSE;

	if( g_mapCodeToCode.Lookup(strKey,(void*&)pCode) )
	{
		return TRUE;
	}

	return FALSE;
}

char			g_strPanHouPath[_MAX_PATH];
char			g_strDayPath[_MAX_PATH];
char			g_strInfoBasePath[_MAX_PATH];		//	资讯起始路径
char			g_strInfoDirs[_MAX_PATH];           //  资讯目录 added 20110824
char			g_strInfoFilterKeys[1024];      //  资讯过滤关键字 added 20110906
long			g_lInfoMaxCount;                //  资讯最大条数 added 20110906
char* GetZiXunBasePath(char* szPath)
{
	if( szPath )
	{
		strcpy(szPath,g_strInfoBasePath);
	}
	return szPath;
}


void SetCfgFileInfo(char* szCfgName,
					char* szErrorName,
					char* strUserConnect,
					char* szSettingPath,
					char* strCommStatus /*= NULL*/,
					char* strQiHuoCodeProfile /*= NULL*/,
					char* strQiHuoCodeNameProfile /*= NULL*/)
{
	char szPath[_MAX_PATH];

	// 配置文件存放路径
	if( szSettingPath )
		sprintf(g_strSettingPath,"%s",szSettingPath);
	else
		sprintf(g_strSettingPath,"%s%s","setting",Yls_Path_Spl);

	if( szCfgName )
		sprintf(g_strCfgDynamic,"%s.dyn",szCfgName);
	else
		sprintf(g_strCfgDynamic,"%s","DYNAMIC.INI");

	if( szCfgName )
		sprintf(g_strCfgShortName,"%s",szCfgName);
	else
		sprintf(g_strCfgShortName,"%s","PUBLIC");	

	// 配置文件名称
	if( szCfgName )
		sprintf(g_strCfgfileName,"%s",szCfgName);
	else
		sprintf(g_strCfgfileName,"%s","SETTING.INI");

	// 错误信息文件名称
	if( szErrorName )
		sprintf(g_strErrorFileName,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),szErrorName);
	else
		sprintf(g_strErrorFileName,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),"LOG.TXT");

	// 用户连接信息文件
	if( strUserConnect )
		sprintf(g_strUserfileName,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),strUserConnect);
	else
		sprintf(g_strUserfileName,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),"USERINFO.TXT");

	if( strCommStatus )
		sprintf(g_strCommStatus,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),strCommStatus);
	else
		sprintf(g_strCommStatus,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),"COMMSTATUS.TXT");

	if( strQiHuoCodeProfile )
		sprintf(g_strQiHuoCodeProfile,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),strQiHuoCodeProfile);
	else
		sprintf(g_strQiHuoCodeProfile,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),"期货没有处理的代码文件.TXT");

	if( strQiHuoCodeNameProfile )
		sprintf(g_strQiHuoCodeNameProfile,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),strQiHuoCodeNameProfile);
	else
		sprintf(g_strQiHuoCodeNameProfile,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),"合约名称代码对照表.INI");

	sprintf(g_strCommDataFile,"%s%s",CHSFilePath::GetPath(szPath,Srv_Setting),"通讯日志.TXT");	
}

//void Prompt(const char* szText)
//{
//	CWnd* pWnd = AfxGetMainWnd();
//	if( pWnd == NULL )
//		return;
//
//	pWnd->SendMessage(g_nUDPDataMessage,0,(LPARAM)szText);
//}

//
void Throw(const char* szfile,int nFileRow,const char* szError)
{
	/*static CHqDataBuffer buffer;

	if( szfile && szError )
	{
	CString str;
	str.Format("文件：%s,位置：%i,错误信息：%s",szfile,nFileRow,szError);

	if( buffer.Alloc(str.GetLength()) )
	{
	strncpy((char*)buffer.m_lpszBuffer,str,buffer.m_cbBuffer);
	}
	}

	throw &buffer;*/

	throw -1;
}


int GetMaskByMarket(HSMarketDataType nMarket)
{
	if(WhoMarket(nMarket,STOCK_MARKET))		return Market_STOCK_MARKET;
	else if(WhoMarket(nMarket,HK_MARKET))		return Market_HK_MARKET;
	else if(WhoMarket(nMarket,WP_MARKET))		return Market_WP_MARKET;
	else if(WhoMarket(nMarket,FUTURES_MARKET))   return Market_FUTURES_MARKET;  
	else if(WhoMarket(nMarket,FOREIGN_MARKET))   return Market_FOREIGN_MARKET;
	else if(WhoMarket(nMarket,HJ_MARKET))   return Market_HJ_MARKET;

	return 0;
}


#define SS_MINTIME				100000000	//最小时间
long LongToDate(long lDate)
{
	time_t tm = ::LongToTime(lDate);
	if(tm < SS_MINTIME)
	{
		tm = time(NULL);
	}
	return tm;
}

time_t LongToTime(long lDate)
{
	struct tm atm;
	memset(&atm, 0, sizeof(tm));
	char szTime[32];
	sprintf(szTime, "%ld", lDate);
	int nLen = strlen(szTime);
	if(nLen <= 8)
	{
		atm.tm_year = int(lDate/10000);
		if(atm.tm_year < 1900)
		{
			atm.tm_mon    = atm.tm_year/100 - 1;
			atm.tm_mday   = atm.tm_year%100;
			atm.tm_hour   = (int)((lDate%10000)/100);
			atm.tm_min    = (int)(lDate%100);
			time_t ct     = time(NULL);
			atm.tm_year   = localtime(&ct)->tm_year + 1900;
		}
		else
		{
			atm.tm_mon    = (int)((lDate%10000)/100) - 1;
			atm.tm_mday   = (int)(lDate%100);
			atm.tm_hour   = 0;
			atm.tm_min    = 0;
		}
	}
	else if(nLen > 8)
	{
		atm.tm_year = (int)(lDate/100000000 + 1990);
		int nTemp   = (int)(lDate%100000000)/10000;
		atm.tm_mon  = nTemp/100 - 1;
		atm.tm_mday = nTemp%100;
		atm.tm_hour = (int)((lDate%10000)/100);
		atm.tm_min  = (int)(lDate%100);
	}
	atm.tm_year -= 1900;
	if(atm.tm_mday < 1 || atm.tm_mday > 31 || 
		atm.tm_mon  < 0 || atm.tm_mon  > 11 ||
		atm.tm_hour < 0 || atm.tm_hour > 23 ||
		atm.tm_min  < 0 || atm.tm_min  > 59 ||
		atm.tm_sec  < 0 || atm.tm_sec  > 59)
	{
		return -1;
	}
	return mktime(&atm);
}

#ifdef HS_SUPPORT_UNIX
int SetFileProcess(const char* strFileName,const char* lpAppName,const char* lpKeyName,long dw)
{	
	char szT[64];
	sprintf(szT, "%d", dw);

	CYlsIni YlsIniFile;
	YlsIniFile.Open(strFileName);

	YlsIniFile.WriteString(lpAppName,lpKeyName,szT);
	return YlsIniFile.Write(NULL);
}

int GetFileProcess(const char* strFileName,const char* lpAppName,const char* lpKeyName,long dw)
{	
	CYlsIni YlsIniFile;
	YlsIniFile.Open(strFileName);

	return YlsIniFile.GetProfileInt(lpAppName,lpKeyName,dw);
}

int GetFileProcess_Child(const char* strFileName,const char* lpAppName,const char* lpKeyName,
						 CYlsArray<CHqDataBuffer*,CHqDataBuffer*>& ayRet)
{	
	// 关闭子进程
	CYlsIni YlsIniFile;
	YlsIniFile.Open(strFileName);

	char* sz = YlsIniFile.ReadString(lpAppName,lpKeyName);
	if( sz != NULL )
	{
		return AnalyzeStr(sz,",",ayRet);
	}

	return 0;
}

#endif

void LoadFile_Dfx(const char* szKey,const char* szPath)
{
	char strFileName[_MAX_PATH];
	sprintf(strFileName,"%s%s",szPath,szKey);


	CYlsFile fp;
	CFileException fileExcept; 		
	if( !fp.Open(strFileName,Yls_OnlyRead_Open,&fileExcept) )
		return;

	CHqDataBuffer* pFixFileBuffer = new CHqDataBuffer;
	if( !pFixFileBuffer->Alloc(fp.GetLength()) )
	{
		delete pFixFileBuffer;
		return;
	}

	fp.Read(pFixFileBuffer->m_lpszBuffer,pFixFileBuffer->m_cbBuffer);
	fp.Close();

	g_sysSysConfig.m_mapDfx_FixInfo.SetAt(szKey,pFixFileBuffer);

}

// 装入路径
BOOL MakeQianLongPath(BOOL bLoad /*= TRUE*/,int nPort /*= 0*/)
{
	// 配置文件使用
	char szPath[_MAX_PATH];	
	CHSFilePath::GetPath(szPath,Srv_Setting_File);
	//YlsPrompt("MakeQianLongPath-配置文件",szPath);

	CYlsIni YlsIniFile;//(1);
	YlsIniFile.Open(szPath);

	char * szRet;

	// 多少代码不同，则重新初始化
	g_nMaxDiffCount = YlsIniFile.ReadInteger("System", "MaxDiff", 1);

	// 是否支持压缩
	g_bYlsSupportZip = YlsIniFile.ReadInteger("System", "SupportZip", 1);

	// 盘后数据主路径
	memset(g_strPanHouPath,0,sizeof(g_strPanHouPath));

	szRet = YlsIniFile.ReadString(Rec_Srv_Internet,Rec_Srv_PanHouPath);
	sprintf(g_strPanHouPath,"%s",szRet);
	if( strlen(g_strPanHouPath) <= 0 )
	{		
		strcpy(g_strPanHouPath,YlsGetCurrentExeBasePath());
		strcat(g_strPanHouPath,"data");
		strcat(g_strPanHouPath,Yls_Path_Spl);
	}
	HSServerDataPath::MakeValidPath(g_strPanHouPath);

	YlsPrompt("盘后数据主路径:",g_strPanHouPath);

	// 资讯数据主路径
	memset(g_strInfoBasePath,0,sizeof(g_strInfoBasePath));
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_ZiXunPath);
	sprintf(g_strInfoBasePath,"%s",szRet);
	if( strlen(g_strInfoBasePath) <= 0 )
	{	 	
		strcpy(g_strInfoBasePath,YlsGetCurrentExeBasePath());
		strcat(g_strInfoBasePath,"ZiXun");
		strcat(g_strInfoBasePath,Yls_Path_Spl);
	}
	HSServerDataPath::MakeValidPath(g_strInfoBasePath);

	YlsPrompt("资讯数据主路径:",g_strInfoBasePath);

   // 资讯目录
	memset(g_strInfoDirs,0,sizeof(g_strInfoDirs));
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_ZiXunDir);
	sprintf(g_strInfoDirs,"%s",szRet);

	YlsPrompt("资讯目录:",g_strInfoDirs);

	// 资讯最大条数
	g_lInfoMaxCount = 50;
	g_lInfoMaxCount = YlsIniFile.ReadInteger(Rec_Srv_Internet, Rec_Srv_ZiXunMaxCount, 50);


	// 资讯过滤关键字
	memset(g_strInfoFilterKeys, 0, sizeof(g_strInfoFilterKeys));
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_ZiXunFilter);
	sprintf(g_strInfoFilterKeys,"%s",szRet);

	YlsPrompt("资讯过滤关键字:",g_strInfoFilterKeys);


	// 时时数据主路径
	memset(g_strDayPath,0,sizeof(g_strDayPath));
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_RealPath);
	sprintf(g_strDayPath,"%s",szRet);
	if( strlen(g_strDayPath) <= 0 )
	{
		strcpy(g_strDayPath,YlsGetCurrentExeBasePath());
		strcat(g_strDayPath,"dat");
		strcat(g_strDayPath,Yls_Path_Spl);
	}

	YlsPrompt("时时数据主路径1:",g_strDayPath);

	HSServerDataPath::MakeValidPath(g_strDayPath);

	YlsPrompt("时时数据主路径:",g_strDayPath);

	// 交换数据文件路径	  SRV_SETTING
	//g_sShareMarketFile.SetPathFile(g_strDayPath);

	if( nPort != 0 )
	{
		g_sysSysConfig.m_nPort = nPort;
	}
	else
	{
		szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_Port, "8001");
		g_sysSysConfig.m_nPort = atol(szRet);
	}

	// 
	g_sysSysConfig.nEntry_Support_GP	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_GP,0) ;//"Support_沪深"
	g_sysSysConfig.nEntry_Support_QH	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_QH,0) ;//"Support_期货"
	g_sysSysConfig.nEntry_Support_WH	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_WH,     0) ;//"Support_外汇"
	g_sysSysConfig.nEntry_Support_WP	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_WP,0) ;//"Support_外盘"
	g_sysSysConfig.nEntry_Support_GG	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_GG,0) ;//"Support_港股"
	g_sysSysConfig.nEntry_Support_HJ	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_HJ,0) ;//"Support_黄金" //added by Ben
	g_sysSysConfig.nEntry_Support_ZX	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_SRVZX,0) ;

	g_sysSysConfig.nEntry_Support_Delay	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Delay,0) ;
	g_sysSysConfig.nEntry_Support_ZixunPush	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_ZixunPush,1) ;
	g_sysSysConfig.nEntry_Support_Group_ZixunPush	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Group_ZixunPush,0) ;



	g_sysSysConfig.m_nDownLoadSpeed     = YlsIniFile.ReadInteger(Rec_Srv_SJXZ,Rec_Srv_Speed,100);// 数据下载速度
	if( g_sysSysConfig.m_nDownLoadSpeed < 0 )
		g_sysSysConfig.m_nDownLoadSpeed = 100;

	g_sysSysConfig.m_dDownLoadDataMax = YlsIniFile.ReadInteger(Rec_Srv_SJXZ,Rec_Srv_DowloadMax,2);// 数据下载速度
	if( g_sysSysConfig.m_dDownLoadDataMax < 0 )
		g_sysSysConfig.m_dDownLoadDataMax = 1;

	g_sysSysConfig.m_nHttpPort	= YlsIniFile.ReadInteger(Section_Internet,Entry_Http_Port,8007);//"Support_港股"

	//
	szRet = YlsIniFile.ReadString(Rec_Srv_SJXZ, Rec_Srv_SUPERSTK,"http://download.fxj.com.cn/base/SUPERSTK.FIN");
	sprintf(g_sysSysConfig.m_strSUPERSTK,"%s",szRet);

	szRet = YlsIniFile.ReadString(Rec_Srv_SJXZ, Rec_Srv_SPLIT,"http://download.fxj.com.cn/base/SPLIT.PWR");
	sprintf(g_sysSysConfig.m_strSPLIT,"%s",szRet);

	szRet = YlsIniFile.ReadString(Rec_Srv_SJXZ, Rec_Srv_BLOCK,"http://download.fxj.com.cn/base/block.zip");
	sprintf(g_sysSysConfig.m_strBlock,"%s",szRet);


	g_sysSysConfig.m_cSupportMultiMarketReq = YlsIniFile.ReadInteger(Rec_Srv_Internet,Rec_Srv_MultiMarket,0);

	g_sysSysConfig.m_nTimeOut = YlsIniFile.ReadInteger(Rec_Srv_Internet,Rec_Srv_NotAcceptData,600);

	//
#ifdef HS_SUPPORT_UNIX
	printf("gp:%i,qh:%i,wh:%i,wp:%i,gg:%i,hj:%i\r\n",g_sysSysConfig.nEntry_Support_GP,
		g_sysSysConfig.nEntry_Support_QH,
		g_sysSysConfig.nEntry_Support_WH,
		g_sysSysConfig.nEntry_Support_WP,
		g_sysSysConfig.nEntry_Support_GG,
		g_sysSysConfig.nEntry_Support_HJ);
#endif

	g_sysSysConfig.nEntry_Support_Auth	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Auth,0) ;//"Support_港股"	
	g_sysSysConfig.m_nFromFileCheckUser	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_FromFileCheck,0) ;

	g_sysSysConfig.m_nHLTCheckUser = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_HLTCheck,0);

	szRet = YlsIniFile.ReadString(Section_Internet,Entry_Support_FromFilePath);	
	sprintf(g_sysSysConfig.m_FileCheckPath,"%s",szRet);
	HSServerDataPath::MakeValidPath(g_sysSysConfig.m_FileCheckPath);

	szRet = YlsIniFile.ReadString(Section_Internet,Entry_Support_FileUpdatePath) ;	
	sprintf(g_sysSysConfig.m_FileUpdatePath,"%s",szRet);
	HSServerDataPath::MakeValidPath(g_sysSysConfig.m_FileUpdatePath);

	szRet = YlsIniFile.ReadString(Section_Internet,Entry_Support_FinancialDataPath) ;	
	sprintf(g_sysSysConfig.m_FinancialDataPath,"%s",szRet);
	HSServerDataPath::MakeValidPath(g_sysSysConfig.m_FinancialDataPath);	

	g_sysSysConfig.m_nDllDataNotify	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_DllDataNotify,0);

	g_sysSysConfig.nEntry_Support_Auto_QH	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Auto_QH,0) ;//"Support_港股"
	g_sysSysConfig.nEntry_Support_Auto_QH_Port	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Auto_QH_Port,0) ;//"Support_港股"
	g_sysSysConfig.nEntry_Support_Auto_QH_Forware	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Auto_QH_Forware,0) ;//"Support_港股"

	//szRet = YlsIniFile.ReadString(Section_Internet,Entry_Support_Auto_QH_Addr);
	//sprintf(g_sysSysConfig.strEntry_Support_Auto_QH_Addr,"%s",szRet);
	//YlsIniFile.WriteString(Section_Internet,Entry_Support_Auto_QH_Addr,g_sysSysConfig.strEntry_Support_Auto_QH_Addr);

	g_sysSysConfig.nEntry_Support_Auto_WH	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Auto_WH,0) ;//"Support_港股"
	g_sysSysConfig.nEntry_Support_Auto_WH_Port = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Auto_WH_Port,2910) ;//"Support_港股"
	g_sysSysConfig.nEntry_Support_Auto_WH_Forware = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Auto_WH_Forware,2911) ;//"Support_港股"

	//szRet = YlsIniFile.ReadString(Section_Internet,Entry_Support_Auto_WH_Addr);
	//sprintf(g_sysSysConfig.strEntry_Support_Auto_WH_Addr,"%s",szRet);
	//YlsIniFile.WriteString(Section_Internet,Entry_Support_Auto_WH_Addr,g_sysSysConfig.strEntry_Support_Auto_WH_Addr);

	g_sysSysConfig.m_nSupportDZGY = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_DZGY,0) ; // 支持大宗工业行情

	g_sysSysConfig.m_nSupportUDPSendLog = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_UDPSendLog,0) ;

	g_sysSysConfig.m_nSupportWINCERemoteZixun = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_WINCEZiXun,0) ;

	g_sysSysConfig.m_nSupportWINCELogin = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_WINCEZiXun_Login,1);

	g_sysSysConfig.m_nSupportDFX_Login = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_DFX_Login,1);

	g_sysSysConfig.nEntry_Support_GG_Market	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_GG_Market,0);//HK_MARKET | INDEX_BOURSE);

	g_sysSysConfig.m_nDelayTimeSrv = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_PushDelaytime,g_sysSysConfig.m_nDelayTimeSrv);
	if( g_sysSysConfig.m_nDelayTimeSrv <= 0 )
		g_sysSysConfig.m_nDelayTimeSrv = 800;

	g_sysSysConfig.m_nSocketTimeOutDelay = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_SOCKETTIMEOUT,g_sysSysConfig.m_nSocketTimeOutDelay);
	if( g_sysSysConfig.m_nSocketTimeOutDelay <= 0 )
		g_sysSysConfig.m_nSocketTimeOutDelay = 20;	

	g_sysSysConfig.m_nThreadDelayTimer = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_ThreadDelay,g_sysSysConfig.m_nThreadDelayTimer);
	if( g_sysSysConfig.m_nThreadDelayTimer <= 0 )
		g_sysSysConfig.m_nThreadDelayTimer = 20;	


	g_sysSysConfig.m_nSortTimeSrv = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_SortDelaytime,g_sysSysConfig.m_nSortTimeSrv);
	if( g_sysSysConfig.m_nSortTimeSrv < 0 )
		g_sysSysConfig.m_nSortTimeSrv = 1000;

	g_sysSysConfig.m_nSupportSort = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_Sort,g_sysSysConfig.m_nSupportSort);
	g_sysSysConfig.m_nSupportSortSingle = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_SortSingle,g_sysSysConfig.m_nSupportSortSingle);

	g_sysSysConfig.m_nSupportTotal = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_TotalStatus,g_sysSysConfig.m_nSupportTotal);

	g_sysSysConfig.m_nSupportTotal = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_TotalStatus,g_sysSysConfig.m_nSupportTotal);

	g_sysSysConfig.m_nSupportZip = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_DataZip,g_sysSysConfig.m_nSupportZip);

	g_sysSysConfig.m_nSupportGifName = YlsIniFile.ReadInteger(Section_Internet,Entry_Support_GIFNAME,g_sysSysConfig.m_nSupportGifName);

	//
	g_sysSysConfig.m_nWriteUserList	= YlsIniFile.ReadInteger(Section_Internet,Entry_Support_CreateUsrList,10);

	//
	g_sysSysConfig.m_lPassword = YlsIniFile.ReadInteger(Section_Internet,Entry_DeleteDataPwd,0);//(unsigned)time(NULL) );
	//g_sysSysConfig.m_lAndSendTime = YlsIniFile.ReadInteger( Section_Internet,Entry_AndSendTime,0 );


	szRet = YlsIniFile.ReadString(Srv_capability, Srv_capability_LoginTips,"");
	sprintf(g_sysSysConfig.m_strLoginTips, "%s", szRet);


	// 服务器性能设置
	g_sysSysConfig.m_nSrvMaxProcess = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_SrvMaxProcess,0);
	if( g_sysSysConfig.m_nSrvMaxProcess <= 1 )
		g_sysSysConfig.m_nSrvMaxProcess = 3;

	// 排名失效间隔时间
	g_sysSysConfig.m_nSortDelayTimer = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_SortDelayTimer,5);	

	// 数据处理线程
#ifdef HS_SUPPORT_UNIX
	g_sysSysConfig.m_nSrvMaxThread_TZT = 100;
#else
	g_sysSysConfig.m_nSrvMaxThread_TZT = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_SrvMaxThread_TZT,50);
	//if( g_sysSysConfig.m_nSrvMaxThread_TZT <= 0 )
	//	g_sysSysConfig.m_nSrvMaxThread_TZT = 100;
#endif

	g_sysSysConfig.m_nSrvMaxThread_DFX = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_SrvMaxThread_DFX,1);
	if( g_sysSysConfig.m_nSrvMaxThread_DFX <= 0 )
		g_sysSysConfig.m_nSrvMaxThread_DFX = 0;

	// 用户验证线程
	g_sysSysConfig.m_nSupporUserCheck = YlsIniFile.ReadInteger(Section_Internet, TCP_UsedCheck_WINCE, 0);
	if( g_sysSysConfig.m_nSupporUserCheck )
	{
		g_sysSysConfig.m_nCheckUserMaxThread = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_CheckUserMaxThread,10);
		if( g_sysSysConfig.m_nCheckUserMaxThread <= 0 )
			g_sysSysConfig.m_nCheckUserMaxThread = 2;
	}

	// 服务器不验证登陆数据包
	g_sysSysConfig.m_nSrvNotCheckLogin = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_NotCheckLogin,0);


	// 数据下载
	g_sysSysConfig.m_nDataDownloadMaxThread = YlsIniFile.ReadInteger(Rec_Srv_SJXZ,Rec_Srv_DowloadMaxThread,10);
	if( g_sysSysConfig.m_nDataDownloadMaxThread <= 0 )
		g_sysSysConfig.m_nDataDownloadMaxThread = 10;


	// socket处理线程
	g_sysSysConfig.m_nSocketCounts = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_SocketMaxThread,5);
	if( g_sysSysConfig.m_nSocketCounts <= 0 )
		g_sysSysConfig.m_nSocketCounts = 5;	

	// 从内存中检测用户
	g_sysSysConfig.m_nMemoryCheckUser = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_MemoryCheckUser,0);

	// 从内存中读取日线数据 
	g_sysSysConfig.m_nMemStockDayData = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_MemStockDayData,0);
	g_sysSysConfig.m_nMem1Min = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_Mem1Min,0);
	g_sysSysConfig.m_nMem5Min = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_Mem5Min,0);

	// 处理线程等待时间（毫秒） AnalyzeStr
	g_sysSysConfig.m_nDealDataDelayTime = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_DealDataDelayTime,0);

	g_sysSysConfig.m_nMaxUserConnects = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_MaxUserConnects,5300 /*ACE_CompletePort_maxSocket*/);

	g_sysSysConfig.m_nMaxConnectsFromOnePeer = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_MaxUserFromOnePeer,100);

	g_sysSysConfig.m_nProcessMaxConnects = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_ProcessMaxConnects,200);
	if( g_sysSysConfig.m_nProcessMaxConnects <= 0 )
		g_sysSysConfig.m_nProcessMaxConnects = 200;

	//
	g_sysSysConfig.m_nInMemoryDeal_gp = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_gp,0);
	g_sysSysConfig.m_nInMemoryDeal_qh = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_qh,0);
	g_sysSysConfig.m_nInMemoryDeal_wh = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_wh,0);
	g_sysSysConfig.m_nInMemoryDeal_wp = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_wp,0);
	g_sysSysConfig.m_nInMemoryDeal_gg = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_gg,0);
	g_sysSysConfig.m_nInMemoryDeal_hj = YlsIniFile.ReadInteger(Srv_capability_MemorySet,Srv_capability_InMemoryDeal_hj,0); // added by Ben

	g_sysSysConfig.m_nAcceptMsgWndCounts = YlsIniFile.ReadInteger(Srv_capability,Srv_capability_AcceptMsgWnd,10);
	if( g_sysSysConfig.m_nAcceptMsgWndCounts <= 0 )
		g_sysSysConfig.m_nAcceptMsgWndCounts = 10;

	g_sysSysConfig.m_nMemTickData = 0;

	printf("[服务器性能设置]\r\n");
	printf("当前进程数：%i\r\n",g_sysSysConfig.m_nSrvMaxProcess);
	printf("当前线程数：%i\r\n",g_sysSysConfig.m_nSrvMaxThread_TZT);
	//printf("当前线程数_大幅星：%i\r\n",g_sysSysConfig.m_nSrvMaxThread_DFX);


	// 服务器id,识别服务器的唯一标示
	g_yyySInfoData2.m_lResever[0] = YlsIniFile.ReadInteger(Rec_Srv_JHFZ, Rec_Srv_ID, 0);
	//pApp->WriteProfileInt(Rec_Srv_JHFZ, Rec_Srv_ID, g_yyySInfoData2.m_lResever[0]);

	g_sysSysConfig.m_nWriteLog = YlsIniFile.ReadInteger(Rec_Srv_DataTrace, Rec_Srv_DataTrace, 0);


	// 市场分时分笔时间设定
	g_sysSysConfig.m_gp.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_GP,1);
	g_sysSysConfig.m_gp.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_GP,0);

	g_sysSysConfig.m_qh.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_QH,1);
	g_sysSysConfig.m_qh.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_QH,0);

	g_sysSysConfig.m_wp.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_WP,1);
	g_sysSysConfig.m_wp.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_WP,0);

	g_sysSysConfig.m_wh.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_WH,1);
	g_sysSysConfig.m_wh.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_WH,0);

	g_sysSysConfig.m_gg.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_GG,1);
	g_sysSysConfig.m_gg.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_GG,0);

	g_sysSysConfig.m_hj.m_cUseLocalTime = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Local_HJ,1);
	g_sysSysConfig.m_hj.m_cTickAutoPush = YlsIniFile.ReadInteger(MarketUserTime_Section,MarketUserTime_Tick_HJ,0);

#ifdef HS_SUPPORT_GIF

	// gif
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_GifPath);
	sprintf(g_sysSysConfig.m_strGifMainPath,"%s",szRet);
	if( strlen(g_sysSysConfig.m_strGifMainPath) <= 0 )
	{
		strcpy(g_sysSysConfig.m_strGifMainPath,YlsGetCurrentExeBasePath());
		strcat(g_sysSysConfig.m_strGifMainPath,"GIF");
		strcat(g_sysSysConfig.m_strGifMainPath,Yls_Path_Spl);
	}
	HSServerDataPath::MakeValidPath(g_sysSysConfig.m_strGifMainPath);	
	printf(g_sysSysConfig.m_strGifMainPath);
	printf("\r\n");

	// gif字体路径
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_GifFontPath);
	sprintf(g_sysSysConfig.m_strGif_FontPath,"%s",szRet);
	if( strlen(g_sysSysConfig.m_strGif_FontPath) <= 0 )
	{
		strcpy(g_sysSysConfig.m_strGif_FontPath,CHSFilePath::GetPath(szPath,Srv_Setting));
	}
	HSServerDataPath::MakeValidPath(g_sysSysConfig.m_strGif_FontPath);
	printf(g_sysSysConfig.m_strGif_FontPath);
	printf("\r\n");

	// 图片字体	
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_GifFontName,"SIMSUN.TTF");
	sprintf(g_sysSysConfig.m_strGif_simsun_ttf,"%s%s",g_sysSysConfig.m_strGif_FontPath,szRet);	
	printf(g_sysSysConfig.m_strGif_simsun_ttf);
	printf("\r\n");

	//
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_GifFontName2,"SIMLI.TTF");
	sprintf(g_sysSysConfig.m_strGif_simli_ttf,"%s%s",g_sysSysConfig.m_strGif_FontPath,szRet);	
	printf(g_sysSysConfig.m_strGif_simli_ttf);
	printf("\r\n");


	// gif 名称对应,2007.03.14
	{
		CHqDataBufferArray strKeyArray;
		CYlsArray<CHqDataBuffer*,CHqDataBuffer*> pValueArray;

		int nItemCount = YlsIniFile.ReadConfigSectionString(Rec_Srv_gifName,
			strKeyArray.ay,&pValueArray);

		CHqDataBuffer* key;
		CHqDataBuffer* value;
		CHqDataBuffer* FindValue;

		for( int i = 0; i < nItemCount; i++ )
		{
			key = strKeyArray.ay.GetAt(i);
			if( key == NULL || key->IsEmpty() )
				continue;

			value = pValueArray.GetAt(i);

			key->MakeUpper();
			value->MakeUpper();

			if( !g_sysSysConfig.m_mapGif.Lookup(key->m_lpszBuffer,(void*&)FindValue) )
				g_sysSysConfig.m_mapGif.SetAt(key->m_lpszBuffer,value);
			else
				delete value;
		}
		pValueArray.RemoveAll();
	}

#endif

	// 公司名称
	szRet = YlsIniFile.ReadString(Rec_Srv_Internet, Rec_Srv_CompanyName,"雁联");
	sprintf(g_sysSysConfig.m_CompanyName,"%s",szRet);	
	printf(g_sysSysConfig.m_CompanyName);
	//printf("\r\n");

	memset(&g_yyySInfoData, 0, sizeof(ServerInfoData));

	strncpy(g_yyySInfoData.m_pName,g_sysSysConfig.m_CompanyName,sizeof(g_yyySInfoData.m_pName));

	//
	//YlsPrompt("MakeQianLongPath","完成");

	// 支持dfx
#ifdef Support_DFX

	// 读取大幅星资讯路径对应表

	CHqDataBufferArray strKeyArray;
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> pValueArray;

	int nItemCount = YlsIniFile.ReadConfigSectionString(Rec_Srv_DFX,strKeyArray.ay,&pValueArray);

	CHqDataBuffer* key;
	CHqDataBuffer* value;
	CHqDataBuffer* FindValue;

	for( int i = 0; i < nItemCount; i++ )
	{
		key = strKeyArray.ay.GetAt(i);
		if( key == NULL || key->IsEmpty() )
			continue;

		value = pValueArray.GetAt(i);

		key->MakeUpper();
		value->MakeUpper();

		if( !g_sysSysConfig.m_mapDfx.Lookup(key->m_lpszBuffer,(void*&)FindValue) )
			g_sysSysConfig.m_mapDfx.SetAt(key->m_lpszBuffer,value);
		else
			delete value;
	}
	pValueArray.RemoveAll();

	// 生成dfx目录
	CHSFilePath::GetPath(szPath,Srv_DFxPath);

	//	LoadFile_Dfx(SHORTMSG_Dfx,szPath);
	//	LoadFile_Dfx(START_Dfx,szPath);
	//	LoadFile_Dfx(INDIVIDUATION_Dfx,szPath);
	//	LoadFile_Dfx(HSINFO_Dfx,szPath);
	LoadFile_Dfx(FINANCE_Dfx,szPath);

	// 数据映射Map
	Dfx_DataItem::InitMap();

#endif


	// 如果没有密码，则写入
	if( g_sysSysConfig.m_lPassword == 0 )
	{
		g_sysSysConfig.m_lPassword = (unsigned)time(NULL);
		YlsIniFile.WriteProfileInt( Section_Internet,Entry_DeleteDataPwd,g_sysSysConfig.m_lPassword );
		YlsIniFile.Write();
	}

	//if( !bLoad )
	//	return TRUE;	

	//return LoadAll(FALSE,TRUE);

	return 1;
}

BOOL LoadAll(BOOL bInit /*= FALSE*/,
			 BOOL bDelete /*= FALSE*/,
			 BOOL bCheck /*= FALSE*/)
{



#ifdef HS_SUPPORT_UNIX

	YlsPrompt("LoadAll","begin");

	char strPath[_MAX_PATH];
	strncpy(strPath,g_strDayPath,sizeof(strPath));
	//strcat(strPath,"*bourseinfo.*");

	YlsPrompt("LoadAll",strPath);

	char	strFileName[_MAX_PATH];
	char	szFile[_MAX_PATH];
	HSMarketDataType  cBourse;

	int nPos;

	CStockServerMarketInfo* pCServerMarketInfo;

	// delete all
	if( bDelete )
	{
		CServerMarketInfo::FreeAllMarket();
	}

	int nLen;
	char* pExt;

	DIR * dir;
	struct dirent * ptr;
	dir = opendir(strPath);

	if( dir == NULL )
	{
		YlsPrompt("LoadAll","不能打开目录");
		return 0;
	}

	while( (ptr = readdir(dir)) != NULL )
	{
		sprintf(strFileName,"%s",ptr->d_name);

		//YlsPrompt("路径全名",strFileName);

		if( strchr(strFileName,'/') != NULL ||
			strFileName[0] == '.' ||
			(strFileName[0] == '.' && strFileName[1] == '.') )
			continue;

		if( strstr(strFileName,"-bourseinfo") == NULL )
			continue;
		//YlsPrompt("路径全名",strFileName);

		memset(szFile,0,sizeof(szFile));
		strcpy(szFile,basename(strFileName));

		//YlsPrompt("文件名称",szFile);

		nLen = strlen(szFile);
		if( nLen <= 5 )
			continue;

		nLen -= 4;
		pExt = &szFile[nLen];

		//YlsPrompt("扩展名",pExt);

		char *pchEnd;
		cBourse = strtol(pExt,&pchEnd,16);
		if( cBourse == 0 )
			continue;

		if( !g_sysSysConfig.IsSupport(cBourse) )
			continue;

		//YlsPrompt("装入市场",pExt);

		pCServerMarketInfo = new CStockServerMarketInfo(cBourse);
		pCServerMarketInfo->SetNowPath(g_strDayPath);

		if( !CServerMarketInfo::AddMarket(cBourse,pCServerMarketInfo) )
		{
			delete pCServerMarketInfo;

			YlsPrompt("装入市场不成功",szFile);
			continue;
		}

		pCServerMarketInfo->SetPanhouPath(g_strPanHouPath);

		//YlsPrompt("装入市场",pExt);

		if( bInit )
		{
#if 0
			if( bCheck )
			{
				if( pCServerMarketInfo->CheckNewData() ) // 检查是否有新的数据
					pCServerMarketInfo->InitData();
			}
			else
#endif
			{
				pCServerMarketInfo->CheckNewData(1);
				pCServerMarketInfo->InitData();

				/*if( pCServerMarketInfo->IsHaveShareMemory() )
				{
				MarketNameMan::GetMarketName(pCServerMarketInfo->m_cBourse,strName);
				g_PublicPromptInfo.AddStr(strName);
				g_PublicPromptInfo.AddStr("->支持内存共享");
				}*/
			}
		}
	}

	if( dir )
	{
		closedir(dir);
	}

	YlsPrompt("LoadAll","end");

	return TRUE;

#else

	char strPath[_MAX_PATH];
	strncpy(strPath,g_strDayPath,sizeof(strPath));
	strcat(strPath,"*bourseinfo.*");
	CFileFind find;

	char strFileName[_MAX_PATH];
	HSMarketDataType  cBourse;

	//int nPos;

	CStockServerMarketInfo* pCServerMarketInfo;

	// delete all
	if( bDelete )
	{
		CServerMarketInfo::FreeAllMarket();
	}

	// 由指定目录，装入市场分类信息
	BOOL bContinue = find.FindFile(strPath);
	while(bContinue)
	{
		bContinue   = find.FindNextFile();
		sprintf(strFileName ,"%s",find.GetFileName());

		if( find.IsDots() || find.IsDirectory() )
			continue;

		char ext[_MAX_EXT];
		_splitpath( strFileName, NULL, NULL, NULL, ext );

		char* pExt = &ext[1];
		char *pchEnd;
		cBourse = strtol(pExt,&pchEnd,16);
		if( cBourse == 0 )
			continue;

		if( !g_sysSysConfig.IsSupport(cBourse) )
			continue;

		pCServerMarketInfo = new CStockServerMarketInfo(cBourse);
		pCServerMarketInfo->SetNowPath(g_strDayPath);

		if( !CServerMarketInfo::AddMarket(cBourse,pCServerMarketInfo) )
		{
			delete pCServerMarketInfo;
			continue;
		}

		pCServerMarketInfo->SetPanhouPath(g_strPanHouPath);
		if( bInit )
		{
#if 0
			if( bCheck )
			{
				if( pCServerMarketInfo->CheckNewData(1) ) // 检查是否有新的数据
					pCServerMarketInfo->InitData();
			}
			else
#endif
			{
				pCServerMarketInfo->CheckNewData(1);
				pCServerMarketInfo->InitData();

				/*if( pCServerMarketInfo->IsHaveShareMemory() )
				{
				MarketNameMan::GetMarketName(pCServerMarketInfo->m_cBourse,strName);
				g_PublicPromptInfo.AddStr(strName);
				g_PublicPromptInfo.AddStr("->支持内存共享");
				}*/
			}
		}
	}

	find.Close();

	return TRUE;
#endif

}

short GetBourseTime(HSMarketDataType cCodeType, short nMinute)
{
	DiskBourseInfo* pInfo;

	CServerMarketInfo* pCServerMarketInfo = NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
		return 0;

	pInfo = pCServerMarketInfo->GetInfo();

	short nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= pInfo->m_cType))
		nIndex = 0;
	if(nMinute <= pInfo->m_stNewType[nIndex].m_union.m_nAheadOpenTime)
		return 0;
	else if(nMinute <= pInfo->m_stNewType[nIndex].m_union.m_nAheadCloseTime)
		return nMinute - pInfo->m_stNewType[nIndex].m_union.m_nAheadOpenTime;
	else if(nMinute <= pInfo->m_stNewType[nIndex].m_union.m_nAfterOpenTime)
		return pInfo->m_stNewType[nIndex].m_union.m_nAheadCloseTime -
		pInfo->m_stNewType[nIndex].m_union.m_nAheadOpenTime;
	else if(nMinute <= pInfo->m_stNewType[nIndex].m_union.m_nAfterCloseTime)
		return nMinute - pInfo->m_stNewType[nIndex].m_union.m_nAfterOpenTime + 
		pInfo->m_stNewType[nIndex].m_union.m_nAheadCloseTime - pInfo->m_stNewType[nIndex].m_union.m_nAheadOpenTime;
	else
		return pInfo->m_stNewType[nIndex].m_nTotalTime;
}

BOOL GetKDataPath(char* strDayFile, CodeInfo* pciInfo, short nPeriod,
				  const char* szExt /*= NULL*/,
				  ReqDayData* pReqDayData /*= NULL*/)
{
	CServerMarketInfo* pCServerMarketInfo = NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(pciInfo->m_cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
	{
		strDayFile[0] = '\0';
		printf("无效市场！");

		return FALSE;
	}

	char strSuffix[32];
	memset(strSuffix,0,sizeof(strSuffix));
	if( !pCServerMarketInfo->GetPanHouPath(nPeriod,strDayFile,strSuffix,pReqDayData) )
	{
		printf("无效路径！");
		return FALSE;
	}

	strncat(strDayFile, pciInfo->m_cCode, sizeof(pciInfo->m_cCode));
	if( szExt )
		strcat(strDayFile,szExt);
	else
		strcat(strDayFile,strSuffix);

	return TRUE;
}

short GetBourseTotalTime(HSMarketDataType cCodeType)
{
	DiskBourseInfo* pInfo;

	CServerMarketInfo* pCServerMarketInfo = NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
		return 0;

	pInfo = pCServerMarketInfo->GetInfo();

	short nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= pInfo->m_cType))
		nIndex = 0;

	return pInfo->m_stNewType[nIndex].m_nTotalTime;
}

long GetStockOffsetInHistory(long lOffset,HSMarketDataType cCodeType)
{
	CServerMarketInfo* pCServerMarketInfo = NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
		return 0;

	DiskBourseInfo* pbiInfo;
	pbiInfo = pCServerMarketInfo->GetInfo();

	int nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= pbiInfo->m_cType))
		nIndex = 0;

	long lTotal;
	long lTotalMinute;
	long lRet = 0; 

	int i = 0;

	for( ; i < nIndex; i++)
	{
		lTotal = (long)pbiInfo->m_stNewType[i].m_nTotal;
		lTotalMinute = (long)pbiInfo->m_stNewType[i].m_nTotalTime + 1;
		lRet += lTotal*lTotalMinute;
	}

	lOffset -= pbiInfo->m_stNewType[i].m_nOffset;
	lTotalMinute = (long)pbiInfo->m_stNewType[i].m_nTotalTime + 1;
	lRet += lOffset*lTotalMinute;

	return lRet;
}

int IsRunningTime(HSMarketDataType cCodeType)
{
	CServerMarketInfo* pCServerMarketInfo = NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
		return 0;

	DiskBourseInfo* pInfo = pCServerMarketInfo->GetInfo();

	short nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= pInfo->m_cType))
		nIndex = 0;

	short nAhead = pInfo->m_stNewType[nIndex].m_union.m_nAheadCloseTime - 
		pInfo->m_stNewType[nIndex].m_union.m_nAheadOpenTime;

	return (((pInfo->m_stNewType[nIndex].m_nCurTime >= 1) && 
		(pInfo->m_stNewType[nIndex].m_nCurTime <= nAhead)) ||
		((pInfo->m_stNewType[nIndex].m_nCurTime - nAhead >= 1) && 
		(pInfo->m_stNewType[nIndex].m_nCurTime - nAhead <= 
		(pInfo->m_stNewType[nIndex].m_union.m_nAfterCloseTime -
		pInfo->m_stNewType[nIndex].m_union.m_nAfterOpenTime))) );
}
#include "stdafxi.cpp"















int GetTime()
{
	return GetTime(SZ_Bourse);
}

int GetTime(HSMarketDataType cCodeType)
{
	CServerMarketInfo* pCServerMarketInfo = NULL;
	CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
		return 0;

	DiskBourseInfo* pInfo = pCServerMarketInfo->GetInfo();

	short nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= pInfo->m_cType))
		nIndex = 0;

	return pInfo->m_stNewType[nIndex].m_nCurTime;
}

StockType* GetStockType(HSMarketDataType cCodeType,CServerMarketInfo*& pCServerMarketInfo,int* pDate /*= NULL*/)
{
	pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
	if( pCServerMarketInfo == NULL )
		return NULL;

	DiskBourseInfo*	pBiInfo	= pCServerMarketInfo->GetInfo();

	if( pBiInfo == NULL )
		return NULL;

	if( pDate )
		*pDate = pBiInfo->m_lDate;

	int nIndex = MakeSubMarketPos(cCodeType);
	if((nIndex < 0) || (nIndex >= pBiInfo->m_cType))
		nIndex = 0;

	return &pBiInfo->m_stNewType[nIndex];
}

int IsSeasonDay(CYlsTime& cLast,CYlsTime& cNow)
{
	// 是否为季线周期...

	if( cLast.GetYear() != cNow.GetYear() )
		return 0;

	int nMonth = cNow.GetMonth();
	int nDay = cNow.GetDay();

	int nOldMonth = cLast.GetMonth();
	int nOldDay = cLast.GetDay();

	if( nMonth <= 3 && nDay <= 31 &&
		nOldMonth <= 3 && nOldDay <= 31 )
		return 1;

	if( nMonth > 3 && nMonth <= 6 && nDay <= 30 &&
		nOldMonth > 3 && nOldMonth <= 6 && nOldDay <= 30 )
		return 1;

	if( nMonth > 6 && nMonth <= 12 && nDay <= 31 &&
		nOldMonth > 6 && nOldMonth <= 12 && nOldDay <= 31 )
		return 1;

	return 0;
}

int MakeWeekFile(StockCompDayDataEx* pPreDay,StockDay* pDay)
{
	// 周线...

	CYlsTime cLast;
	CYlsTime cNow;
	CYlsTime cNLast;
	BOOL bExit;
	if(pPreDay != NULL)
	{
		cLast  = LongToDate(pPreDay->m_lDate);
		cNow   = LongToDate(pDay->m_lDate);
		if((cLast.GetMonth() == cNow.GetMonth()) && (cLast.GetDay() == cNow.GetDay()))
		{
			return 0;
		}
		cNLast = cNow - CYlsTimeSpan(7,0,0,0);
		bExit = TRUE;
	}
	else
	{
		bExit = FALSE;
	}

	if(bExit && (cNow.GetDayOfWeek() <= cLast.GetDayOfWeek()) && (cNLast < cLast))
	{
		if(pDay->m_lOpenPrice != 0)
			pPreDay->m_lOpenPrice = pDay->m_lOpenPrice;
		if(pPreDay->m_lClosePrice == 0)
			pPreDay->m_lClosePrice = pDay->m_lClosePrice;
		if(pPreDay->m_lMaxPrice < pDay->m_lMaxPrice)
			pPreDay->m_lMaxPrice = pDay->m_lMaxPrice;
		if(pPreDay->m_lMinPrice > pDay->m_lMinPrice)
			pPreDay->m_lMinPrice = pDay->m_lMinPrice;
		pPreDay->m_lTotal += pDay->m_lTotal;
		memcpy(pDay,pPreDay,sizeof(StockDay));
	}

	return 1;
}

int MakeMonthFile(StockCompDayDataEx* pPreDay,StockDay* pDay)
{
	// 月线...

	CYlsTime cLast;
	CYlsTime cNow;
	BOOL bExit;
	if(pPreDay != NULL)
	{
		cLast  = LongToDate(pPreDay->m_lDate);
		cNow   = LongToDate(pDay->m_lDate);
		bExit = TRUE;
	}
	else
	{
		bExit = FALSE;
	}
	if(bExit && (cNow.GetYear() == cLast.GetYear()) && (cNow.GetMonth() == cLast.GetMonth()))
	{

		if(pDay->m_lOpenPrice != 0)
			pPreDay->m_lOpenPrice = pDay->m_lOpenPrice;
		if(pPreDay->m_lClosePrice == 0)
			pPreDay->m_lClosePrice = pDay->m_lClosePrice;
		if(pPreDay->m_lMaxPrice < pDay->m_lMaxPrice)
			pPreDay->m_lMaxPrice = pDay->m_lMaxPrice;
		if(pPreDay->m_lMinPrice > pDay->m_lMinPrice)
			pPreDay->m_lMinPrice = pDay->m_lMinPrice;
		pPreDay->m_lTotal += pDay->m_lTotal;
		memcpy(pDay,pPreDay,sizeof(StockDay));

	}

	return 1;
} 

int MakeSeasonFile(StockCompDayDataEx* pPreDay,StockDay* pDay)
{
	// 季线...

	CYlsTime cLast;
	CYlsTime cNow;
	BOOL bExit;
	if(pPreDay != NULL)
	{
		cLast  = LongToDate(pPreDay->m_lDate);
		cNow   = LongToDate(pDay->m_lDate);
	}
	else
	{
		bExit = FALSE;
	}

	if(bExit && IsSeasonDay(cLast,cNow) )
	{
		if(pDay->m_lOpenPrice != 0)
			pPreDay->m_lOpenPrice = pDay->m_lOpenPrice;
		if(pPreDay->m_lClosePrice == 0)
			pPreDay->m_lClosePrice = pDay->m_lClosePrice;
		if(pPreDay->m_lMaxPrice < pDay->m_lMaxPrice)
			pPreDay->m_lMaxPrice = pDay->m_lMaxPrice;
		if(pPreDay->m_lMinPrice > pDay->m_lMinPrice)
			pPreDay->m_lMinPrice = pDay->m_lMinPrice;
		pPreDay->m_lTotal += pDay->m_lTotal;
		memcpy(pDay,pPreDay,sizeof(StockDay));
	}

	return 1;
}

int MakeYearFile(StockCompDayDataEx* pPreDay,StockDay* pDay)
{
	// 年线...

	CYlsTime cLast;
	CYlsTime cNow;
	BOOL bExit;
	if(pPreDay != NULL)
	{
		cLast  = LongToDate(pPreDay->m_lDate);
		cNow   = LongToDate(pDay->m_lDate);
		if(cLast.GetYear() == cNow.GetYear())
		{
			return 0;
		}
		bExit = TRUE;
	}
	else
	{
		bExit = FALSE;
	}
	if(bExit && (cNow.GetYear() == cLast.GetYear()) )
	{
		/*
		pPreDay->m_lDate = pDay->m_lDate;
		if(pPreDay->m_lOpenPrice == 0)
			pPreDay->m_lOpenPrice = pDay->m_lOpenPrice;
		if(pDay->m_lClosePrice != 0)
			pPreDay->m_lClosePrice = pDay->m_lClosePrice;
		if(pPreDay->m_lMaxPrice < pDay->m_lMaxPrice)
			pPreDay->m_lMaxPrice = pDay->m_lMaxPrice;
		if(pPreDay->m_lMinPrice > pDay->m_lMinPrice)
			pPreDay->m_lMinPrice = pDay->m_lMinPrice;
		pPreDay->m_lTotal += pDay->m_lTotal;

		memcpy(pPreDay,pDay,sizeof(StockDay));*/

		if(pDay->m_lOpenPrice != 0)
			pPreDay->m_lOpenPrice = pDay->m_lOpenPrice;
		if(pPreDay->m_lClosePrice == 0)
			pPreDay->m_lClosePrice = pDay->m_lClosePrice;
		if(pPreDay->m_lMaxPrice < pDay->m_lMaxPrice)
			pPreDay->m_lMaxPrice = pDay->m_lMaxPrice;
		if(pPreDay->m_lMinPrice > pDay->m_lMinPrice)
			pPreDay->m_lMinPrice = pDay->m_lMinPrice;
		pPreDay->m_lTotal += pDay->m_lTotal;
		memcpy(pDay,pPreDay,sizeof(StockDay));
	}

	return 1;
}

int MakeMinuteData(StockDay* pDay, int nDayCount, StockTraceData* ptrData, int nSize, 
				   int nPeriod, long lDate, 
				   CodeInfo* pCode,ShareRealTimeData* pNowData,
				   StockType* pStockType,int lCurDate)
{
	// 有分笔生成分钟数据...

	HSMarketDataType cCodeType = pCode->m_cCodeType;
	int n = 0;
	BOOL bOpen = FALSE;
	pDay[0].m_lDate = lDate;
	int nHand = 1;

	long  lCurrTotal = 0, lPreTotal = 0; 
	float fCurrTurnOver = 0, fPreTurnOver = 0; // 交易额
	long  lHolding = 0;  // 持仓量

#if 0
	static LogSystem pLogSystem(NULL,0,0,1,"timeError");

	int bWrite = 0;
	if( nPeriod == 5 ) // 只记5分钟日志
	{
		char szKey[STOCK_CODE_SIZE + 1];
		_strncpy(szKey,pNowData->m_stStockInfo.m_ciStockCode.m_cCode,STOCK_CODE_SIZE);

		if( MakeSubMarket(pNowData->m_stStockInfo.m_ciStockCode.m_cCodeType) == KIND_STOCKA )
		{
			int l = atol(szKey);
			if( l >= 600000 && l < 600100 )
				bWrite = 1;
			else if( l >= 1 && l < 100 )
				bWrite = 1;
		}

		if( bWrite )
		{			
			pLogSystem.WriteLog(szKey,"\r\n");
		}
	}
#endif

	//SortTick(ptrData,nSize);

	if( MakeMarket(cCodeType) == STOCK_MARKET )
	{
		if( !MakeIndexMarket(cCodeType) )
		{
			nHand = pNowData->m_stStockData.m_nHand;
		}
		if( nHand <= 0 )
			nHand = 100;
	}

	//int lCurDate = 0;
	//StockType* pStockType = GetStockType(cCodeType,lCurDate);

	long lClose = 0;//pNowData->m_stStockInfo.m_lPrevClose;
	int nTime;
	int i;

	int nPreTime = 0;


	for(i = 0; i < nSize; i++)
	{
		nTime = ptrData[i].m_sTick.m_nTime;

		// added 20110902 如果9.10没数据，则增加一笔
		if ((i == 0 && (nTime > 340)) || (i > 0 && (ptrData[i - 1].m_sTick.m_nTime < 340 && nTime > 340)) )
		{
			ptrData[i].m_sTick.m_nTime = 340;
			nTime = 340;
		}
		// end add
		if(nTime < 0)
			break;


		//#ifdef Support_JiaoHang_AutoEvery // 2007.08.14
		// 2006.12.29 add
		// 如果后面的时间小于前面的时间，则无效。
		//if( nTime >= nPreTime )
		//	nPreTime = nTime; 
		//else
		//	continue;
		//#endif

		if((ptrData[i].m_sTick.m_lCurrent <= 0) && (i > 0))
		{
			ptrData[i].m_sTick.m_lCurrent = ptrData[i-1].m_sTick.m_lCurrent;
		}

		n = (nTime - 1) / nPeriod;
		if(n < 0)
			n = 0;
		if( n >= nDayCount )
			n = nDayCount - 1;

		if(pDay[n].m_lDate == 0)
		{// 第一笔			
			if( MakeMarket(cCodeType) == FOREIGN_MARKET || // 外汇
				MakeMarket(cCodeType) == WP_MARKET )	
			{
				pDay[n].m_lOpenPrice  = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMaxPrice   = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMinPrice   = ptrData[i].m_sTick.m_lNewPrice;				
				bOpen = TRUE;
			}
			else if((ptrData[i].m_sTick.m_lCurrent != 0) && (ptrData[i].m_sTick.m_lNewPrice != 0))
			{
				pDay[n].m_lOpenPrice  = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMaxPrice   = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMinPrice   = ptrData[i].m_sTick.m_lNewPrice;				
				bOpen = TRUE;
			}			
			else
			{
				if(n == 0)
				{
					pDay[n].m_lOpenPrice  = lClose;
					pDay[n].m_lClosePrice = lClose;
					pDay[n].m_lMaxPrice   = lClose;
					pDay[n].m_lMinPrice   = lClose;
				}
				else
				{
					pDay[n].m_lOpenPrice  = pDay[n-1].m_lClosePrice;
					pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
					pDay[n].m_lMaxPrice   = pDay[n-1].m_lClosePrice;
					pDay[n].m_lMinPrice   = pDay[n-1].m_lClosePrice;
				}
				bOpen = FALSE;
			}

			lCurrTotal = (ptrData[i].m_sTick.m_lCurrent - lPreTotal)/nHand;
		}
		else
		{
			if(bOpen) 
			{
				if(ptrData[i].m_sTick.m_lNewPrice != 0)
				{
					if(pDay[n].m_lMaxPrice < ptrData[i].m_sTick.m_lNewPrice)
						pDay[n].m_lMaxPrice = ptrData[i].m_sTick.m_lNewPrice;
					if(pDay[n].m_lMinPrice > ptrData[i].m_sTick.m_lNewPrice)
						pDay[n].m_lMinPrice = ptrData[i].m_sTick.m_lNewPrice;
					pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				}
			}
			else if( MakeMarket(cCodeType) == FOREIGN_MARKET ||// 外汇
				     MakeMarket(cCodeType) == WP_MARKET )	
			{
				pDay[n].m_lOpenPrice  = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMaxPrice   = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMinPrice   = ptrData[i].m_sTick.m_lNewPrice;
				bOpen = TRUE;
			}
			else if((ptrData[i].m_sTick.m_lCurrent != 0) && (ptrData[i].m_sTick.m_lNewPrice != 0))
			{
				pDay[n].m_lOpenPrice  = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMaxPrice   = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMinPrice   = ptrData[i].m_sTick.m_lNewPrice;
				bOpen = TRUE;
			}

			if (ptrData[i].m_sTick.m_lCurrent > lPreTotal)
			{
				lCurrTotal += (ptrData[i].m_sTick.m_lCurrent - lPreTotal)/nHand;
				lPreTotal = ptrData[i].m_sTick.m_lCurrent;
			}
		}


		fPreTurnOver = ptrData[i].m_sStockMMP.m_fAvgPrice;
		if( MakeIndexMarket(cCodeType) )
		{
			fCurrTurnOver = (ptrData[i].m_sStockMMP.m_fAvgPrice - fPreTurnOver)/10;
		}
		if( MakeMarket(cCodeType) == HK_MARKET)
		{
			fCurrTurnOver = (ptrData[i].m_sStockMMP.m_fAvgPrice - fPreTurnOver)/1000;
		}
		else if( MakeMarket(cCodeType) == STOCK_MARKET)
		{
			fCurrTurnOver = (ptrData[i].m_sStockMMP.m_fAvgPrice - fPreTurnOver)/1000;
		}
		else if( MakeMarket(cCodeType) == FUTURES_MARKET) // modified by Ben
		{
			fCurrTurnOver = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
		}
		else if( MakeMarket(cCodeType) == HJ_MARKET && !IS_CURR_GOLD(pCode->m_cCode,cCodeType)) // modified by Ben
		{
			lHolding = (ptrData[i].m_sStockMMP.m_fAvgPrice - fPreTurnOver);
			fCurrTurnOver = ptrData[i].m_sTick.m_nChiCangLiang;
		}
		else if (MakeMarket(cCodeType) == FOREIGN_MARKET)
		{
			fCurrTurnOver = 0;
			lHolding = 0;
		}
		else
		{
			if (MakeMainMarket(cCodeType) == (WP_MARKET | WP_INDEX))
			{
				fCurrTurnOver = (ptrData[i].m_sStockMMP.m_fAvgPrice - fPreTurnOver);
			}
			else
			{
				lHolding = (ptrData[i].m_sStockMMP.m_fAvgPrice - fPreTurnOver);
				fCurrTurnOver = ptrData[i].m_sTick.m_nChiCangLiang;
			}
		}


		if (lCurrTotal > 0)
			pDay[n].m_lTotal = lCurrTotal;
		pDay[n].m_lMoney = fCurrTurnOver;
		pDay[n].m_lNationalDebtRatio = lHolding;

		if (MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_SH_CURR))
		{
			pDay[n].m_lDate = YlsGetLongTime2(lCurDate, nPeriod*(n+1), pStockType);
		}
		else
			pDay[n].m_lDate = YlsGetLongTime2_Ex(lCurDate, nPeriod*(n+1), pStockType);//GetLongTime(cCodeType, nPeriod*(n+1),0);//,(bWrite?&pLogSystem:0));//nTime);
	}

	//
	CYlsArray<StockDay*,StockDay*> ay;

	StockDay* pStockDay;

	int nPreDate = 0;

	for(i = 0; i <= n && i < nDayCount; i++)
	{
		if (i == 0)
		{
			if (pDay[i].m_lDate != 0 && pDay[i].m_lClosePrice != 0)
			{
				if (pDay[i].m_lOpenPrice == 0)
					pDay[i].m_lOpenPrice = pDay[i].m_lClosePrice;
				if (pDay[i].m_lMaxPrice == 0)
					pDay[i].m_lMaxPrice = pDay[i].m_lClosePrice;
				if (pDay[i].m_lMinPrice == 0)
					pDay[i].m_lMinPrice = pDay[i].m_lClosePrice;
			}
		}
		if( pDay[i].m_lDate		  != 0	&& 
			pDay[i].m_lOpenPrice  != 0	&&
			pDay[i].m_lMaxPrice   != 0	&&
			pDay[i].m_lMinPrice   != 0	&&
			pDay[i].m_lClosePrice != 0 )
		{
			pStockDay = new StockDay;
			memcpy(pStockDay,&pDay[i],sizeof(StockDay));
			ay.Add(pStockDay);
		}
	}

	n = ay.GetSize();

	for( i = 0; i < n && i < nDayCount; i++ )
	{		
		memcpy(&pDay[i],ay.GetAt(i),sizeof(StockDay));
	}
	_delArrayObj(ay);

	// 2007.08.24 add
	//SortDay(pDay,n);

	return n;
}

int MakeSecondData(StockDay* pDay, int nDayCount, StockTraceData* ptrData, int nSize, 
				   int nPeriod, long lDate, 
				   CodeInfo* pCode,ShareRealTimeData* pNowData,
				   StockType* pStockType,int lCurDate)
{
	// 有分笔生成分钟数据...

	HSMarketDataType cCodeType = pCode->m_cCodeType;
	int n = 0;
	BOOL bOpen = FALSE;
	pDay[0].m_lDate = lDate;
	int nHand = 1;

	if( MakeMarket(cCodeType) == STOCK_MARKET )
	{
		if( !MakeIndexMarket(cCodeType) )
		{
			nHand = pNowData->m_stStockData.m_nHand;
		}
		if( nHand <= 0 )
			nHand = 100;
	}

	long lClose = 0;
	int nTime;
	int i;

	int nPreTime = 0;
	CYlsTime tmPre = 0;
	CYlsTime tmCur;

	for(i = 0; i < nSize; i++)
	{
		nTime = ptrData[i].m_sTick.m_nTime;
		if(nTime < 0)
			break;

		if((ptrData[i].m_sTick.m_lCurrent <= 0) && (i > 0))
		{
			ptrData[i].m_sTick.m_lCurrent = ptrData[i-1].m_sTick.m_lCurrent;
		}

		if( YlsGetWholeTime(tmCur, lDate, nTime, &ptrData[i].m_sTick, pStockType) <= 0 )
			continue;

		CYlsTimeSpan span = tmCur - tmPre;
		if( tmPre == 0 )
		{
			tmPre = tmCur;
		}
		else if( span.GetTotalSeconds() >= nPeriod )
		{		
			if( pDay[n].m_lDate		  != 0	&& 
				pDay[n].m_lOpenPrice  != 0	&&
				pDay[n].m_lMaxPrice   != 0	&&
				pDay[n].m_lMinPrice   != 0	&&
				pDay[n].m_lClosePrice != 0 )
			{
				n++;
			}

			tmPre = tmCur;
		}

		if( n < 0 )
			n = 0;
		if( n >= nDayCount )
			n = nDayCount - 1;

		//
		if(pDay[n].m_lDate == 0)
		{
			if( MakeMarket(cCodeType) == FOREIGN_MARKET || // 外汇
				MakeMarket(cCodeType) == WP_MARKET )	
			{
				pDay[n].m_lOpenPrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMaxPrice  = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMinPrice  = ptrData[i].m_sTick.m_lNewPrice;				
				bOpen = TRUE;
			}
			else if((ptrData[i].m_sTick.m_lCurrent != 0) && (ptrData[i].m_sTick.m_lNewPrice != 0))
			{
				pDay[n].m_lOpenPrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMaxPrice  = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMinPrice  = ptrData[i].m_sTick.m_lNewPrice;				
				bOpen = TRUE;
			}
			else
			{
				if(n == 0)
				{
					pDay[n].m_lOpenPrice  = lClose;
					pDay[n].m_lClosePrice = lClose;
					pDay[n].m_lMaxPrice   = lClose;
					pDay[n].m_lMinPrice   = lClose;
				}
				else
				{
					pDay[n].m_lOpenPrice  = pDay[n-1].m_lClosePrice;
					pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
					pDay[n].m_lMaxPrice   = pDay[n-1].m_lClosePrice;
					pDay[n].m_lMinPrice   = pDay[n-1].m_lClosePrice;
				}
				bOpen = FALSE;
			}

			if(i > 0)
			{
				if( ptrData[i].m_sTick.m_lCurrent > ptrData[i-1].m_sTick.m_lCurrent )
					pDay[n].m_lTotal = (ptrData[i].m_sTick.m_lCurrent - ptrData[i-1].m_sTick.m_lCurrent)/nHand;

				if( MakeIndexMarket(cCodeType) )
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice)/10;//00;
#else
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_fAvgPrice - ptrData[i-1].m_sStockMMP.m_fAvgPrice)/10;
#endif
				}
				if( MakeMarket(cCodeType) == HK_MARKET)
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_stNow.m_hkData.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_stNow.m_hkData.m_fAvgPrice)/1000;
#else
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_fAvgPrice - ptrData[i-1].m_sStockMMP.m_fAvgPrice)/1000;
#endif

				}
				else if( MakeMarket(cCodeType) == STOCK_MARKET)
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice)/1000;
#else
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_fAvgPrice - ptrData[i-1].m_sStockMMP.m_fAvgPrice)/1000;
#endif
				}
				else if( MakeMarket(cCodeType) == FUTURES_MARKET) // modified by Ben
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_qhData.m_lChiCangLiang;
#else
					pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
#endif
				}
				else if( MakeMarket(cCodeType) == HJ_MARKET && !IS_CURR_GOLD(pCode->m_cCode,cCodeType)) // modified by Ben
				{					
					pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang;
				}
				else
				{

					if (MakeMainMarket(cCodeType) == (WP_MARKET | WP_INDEX))
					{
#ifdef _Support_LargeTick
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice;
#else
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice;
#endif
					}
					else
					{
#ifdef _Support_LargeTick
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_qhData.m_lChiCangLiang;
#else
						pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
#endif
					}
				}
			}
			else
			{
				if( ptrData[i].m_sTick.m_lCurrent > 0 )
					pDay[n].m_lTotal = ptrData[i].m_sTick.m_lCurrent/nHand;

				if( MakeIndexMarket(cCodeType) )
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice/10;//00;
#else
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice/10;
#endif
				}
				else if( MakeMarket(cCodeType) == HK_MARKET)
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_hkData.m_fAvgPrice/1000;
#else
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice/1000;
#endif
				}
				else if( MakeMarket(cCodeType) == STOCK_MARKET)
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice/1000;
#else
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice/1000;
#endif
				}
				else if( MakeMarket(cCodeType) == FUTURES_MARKET) // modified by Ben
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_qhData.m_lChiCangLiang;
#else
					pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
#endif
				}
				else if( MakeMarket(cCodeType) == HJ_MARKET && !IS_CURR_GOLD(pCode->m_cCode,cCodeType)) // modified by Ben
				{					
					pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang;
				}
				else
				{

					if (MakeMainMarket(cCodeType) == (WP_MARKET | WP_INDEX))
					{
#ifdef _Support_LargeTick
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice;
#else
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice;
#endif				
					}
					else
					{
#ifdef _Support_LargeTick
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_qhData.m_lChiCangLiang;
#else
						pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
#endif
					}
				}
			}
		}
		else
		{
			if( i > 0 )
			{
				if( ptrData[i].m_sTick.m_lCurrent > ptrData[i-1].m_sTick.m_lCurrent )
					pDay[n].m_lTotal += (ptrData[i].m_sTick.m_lCurrent - ptrData[i-1].m_sTick.m_lCurrent)/nHand;

				if( MakeIndexMarket(cCodeType) )
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice)/10;//00;
#else
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_fAvgPrice)/10;
#endif
				}
				else if( MakeMarket(cCodeType) == HK_MARKET)
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_stNow.m_hkData.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_stNow.m_hkData.m_fAvgPrice)/1000;
#else
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_fAvgPrice)/1000;
#endif
				}
				else if( MakeMarket(cCodeType) == STOCK_MARKET)
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice)/1000;
#else
					pDay[n].m_lMoney = (ptrData[i].m_sStockMMP.m_fAvgPrice - 
						ptrData[i-1].m_sStockMMP.m_fAvgPrice)/1000;
#endif
				}
				else if( MakeMarket(cCodeType) == FUTURES_MARKET) // modified by Ben
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_qhData.m_lChiCangLiang;
#else
					pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
#endif
				}
				else if( MakeMarket(cCodeType) == HJ_MARKET && !IS_CURR_GOLD(pCode->m_cCode,cCodeType)) // modified by Ben
				{					
					pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang;
				}
				else
				{
					if (MakeMainMarket(cCodeType) == (WP_MARKET | WP_INDEX))
					{
#ifdef _Support_LargeTick
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice;
#else
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice;
#endif					
					}
					else
					{
#ifdef _Support_LargeTick
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_qhData.m_lChiCangLiang;
#else
						pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
#endif
					}
				}
			}
			else
			{
				if( ptrData[i].m_sTick.m_lCurrent > 0 )
					pDay[n].m_lTotal = ptrData[i].m_sTick.m_lCurrent/nHand;

				if( MakeIndexMarket(cCodeType) )
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice/10;//00;
#else
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice/10;
#endif
				}
				else if( MakeMarket(cCodeType) == HK_MARKET)
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_hkData.m_fAvgPrice/1000;
#else
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice/1000;
#endif
				}
				else if( MakeMarket(cCodeType) == STOCK_MARKET)
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice/1000;
#else
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice/1000;
#endif
				}
				else if( MakeMarket(cCodeType) == FUTURES_MARKET) // modified by Ben
				{
#ifdef _Support_LargeTick
					pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_qhData.m_lChiCangLiang;
#else
					pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
#endif
				}
				else if( MakeMarket(cCodeType) == HJ_MARKET && !IS_CURR_GOLD(pCode->m_cCode,cCodeType)) // modified by Ben
				{					
					pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang;
				}
				else
				{
					if (MakeMainMarket(cCodeType) == (WP_MARKET | WP_INDEX))
					{
#ifdef _Support_LargeTick
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_stStockData.m_fAvgPrice;
#else
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_fAvgPrice;
#endif					
					}
					else
					{
#ifdef _Support_LargeTick
						pDay[n].m_lMoney = ptrData[i].m_sStockMMP.m_stNow.m_qhData.m_lChiCangLiang;
#else
						pDay[n].m_lMoney = ptrData[i].m_sTick.m_nChiCangLiang; //ptrData[i].m_sStockMMP.m_lChiCangLiang;
#endif
					}

				}
			}

			if(bOpen) 
			{
				if( ptrData[i].m_sTick.m_lNewPrice != 0 )
				{
					if(pDay[n].m_lMaxPrice < ptrData[i].m_sTick.m_lNewPrice)
						pDay[n].m_lMaxPrice = ptrData[i].m_sTick.m_lNewPrice;
					if(pDay[n].m_lMinPrice > ptrData[i].m_sTick.m_lNewPrice)
						pDay[n].m_lMinPrice = ptrData[i].m_sTick.m_lNewPrice;
					pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				}
			}
			else if( MakeMarket(cCodeType) == FOREIGN_MARKET || // 外汇
					 MakeMarket(cCodeType) == WP_MARKET )	
			{
				pDay[n].m_lOpenPrice  = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMaxPrice   = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMinPrice   = ptrData[i].m_sTick.m_lNewPrice;
				bOpen = TRUE;
			}
			else if( (ptrData[i].m_sTick.m_lCurrent != 0) && (ptrData[i].m_sTick.m_lNewPrice != 0) )
			{
				pDay[n].m_lOpenPrice  = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lClosePrice = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMaxPrice   = ptrData[i].m_sTick.m_lNewPrice;
				pDay[n].m_lMinPrice   = ptrData[i].m_sTick.m_lNewPrice;
				bOpen = TRUE;
			}
		}

		char strTime[64];
		sprintf(strTime,"%02d%02d%02d%02d%02d",
			tmCur.GetMonth(),tmCur.GetDay(),tmCur.GetHour(),tmCur.GetMinute(),tmCur.GetSecond());

		pDay[n].m_lDate = atol(strTime);
	}

#if 0

	//
	CYlsArray<StockDay*,StockDay*> ay;

	StockDay* pStockDay;

	int nPreDate = 0;

	for(i = 0; i <= n && i < nDayCount; i++)
	{
		if( pDay[i].m_lDate		  != 0	&& 
			pDay[i].m_lOpenPrice  != 0	&&
			pDay[i].m_lMaxPrice   != 0	&&
			pDay[i].m_lMinPrice   != 0	&&
			pDay[i].m_lClosePrice != 0 )
		{
			pStockDay = new StockDay;
			memcpy(pStockDay,&pDay[i],sizeof(StockDay));
			ay.Add(pStockDay);
		}
	}

	n = ay.GetSize();

	for( i = 0; i < n && i < nDayCount; i++ )
	{		
		memcpy(&pDay[i],ay.GetAt(i),sizeof(StockDay));
	}
	_delArrayObj(ay);

#endif

	return n;
}

int MakeMinuteDataByHis(StockDay* pDay,int nDayCount, StockCompHistoryData* pHisData, int nSize, 
						int nPeriod, long lDate, 
						HSMarketDataType cCodeType,ShareRealTimeData* pNowData,long lPrevClose,
						StockType* pStockType,int lCurDate)
{
	// 从历史1分钟数据生成分钟周期数据...

	int n = 0;
	BOOL bOpen = FALSE;
	pDay[0].m_lDate = lDate;
	int nHand = 1;
	if( MakeMarket(cCodeType) == STOCK_MARKET )
	{
		if( !MakeIndexMarket(cCodeType) )
		{
			nHand = pNowData->m_stStockData.m_nHand;
		}
		if( nHand <= 0 )
			nHand = 100;
	}

	long lClose = lPrevClose;
	int i;
	for(i = 0; i < nSize; i++)
	{
		if((pHisData[i].m_lTotal <= 0) && (i > 0))
		{
			pHisData[i].m_lTotal = pHisData[i-1].m_lTotal;
		}

		if((i == 0) || (( i != 1) && !((i-1)%nPeriod)))
		{
			if( pDay[n].m_lDate		  != 0	&& 
				pDay[n].m_lOpenPrice  != 0	&&
				pDay[n].m_lMaxPrice   != 0	&&
				pDay[n].m_lMinPrice   != 0	&&
				pDay[n].m_lClosePrice != 0 )
			{
				n++;
			}

			if( n >= nDayCount )
				n = nDayCount - 1;

			if(pHisData[i].m_lNewPrice != 0)
			{
				pDay[n].m_lOpenPrice  = pHisData[i].m_lNewPrice;
				pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lMaxPrice   = pHisData[i].m_lNewPrice;
				pDay[n].m_lMinPrice   = pHisData[i].m_lNewPrice;
				bOpen = TRUE;
			}
			else
			{
				if(n == 0)
				{
					pDay[n].m_lOpenPrice  = lClose;
					pDay[n].m_lClosePrice = lClose;
					pDay[n].m_lMaxPrice   = lClose;
					pDay[n].m_lMinPrice   = lClose;
				}
				else
				{
					pDay[n].m_lOpenPrice  = pDay[n-1].m_lClosePrice;
					pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
					pDay[n].m_lMaxPrice   = pDay[n-1].m_lClosePrice;
					pDay[n].m_lMinPrice   = pDay[n-1].m_lClosePrice;
				}

				bOpen = FALSE;
			}
			if(i > 0)
			{
				if( pHisData[i].m_lTotal > pHisData[i-1].m_lTotal )
					pDay[n].m_lTotal = (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal)/nHand;
			}
			else
			{
				if( pHisData[i].m_lTotal > 0 )
					pDay[n].m_lTotal = pHisData[i].m_lTotal/nHand;
			}
		}
		else
		{
			if( pHisData[i].m_lTotal > pHisData[i-1].m_lTotal )
				pDay[n].m_lTotal += (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal)/nHand;

			if(bOpen) 
			{
				if(pHisData[i].m_lNewPrice != 0)
				{
					if(pDay[n].m_lMaxPrice < pHisData[i].m_lNewPrice)
						pDay[n].m_lMaxPrice = pHisData[i].m_lNewPrice;
					if(pDay[n].m_lMinPrice > pHisData[i].m_lNewPrice)
						pDay[n].m_lMinPrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
				}
			}
			else if(pHisData[i].m_lNewPrice != 0)
			{
				pDay[n].m_lOpenPrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lMaxPrice  = pHisData[i].m_lNewPrice;
				pDay[n].m_lMinPrice  = pHisData[i].m_lNewPrice;
				bOpen = TRUE;
			}
		}

		if(nPeriod < 24*60)
			pDay[n].m_lDate = YlsGetLongTime2(lCurDate,nPeriod*(n+1),pStockType);//GetLongTime(cCodeType,nPeriod*(n+1));//i);
	}

	return n;	
}

int MakeMinuteData(StockDay* pDay,int nDayCount, StockHistoryData* pHisData, int nSize, 
				   int nPeriod, long lDate, 
				   CodeInfo* pCode,ShareRealTimeData* pNowData,long lPrevClose,
				   StockType* pStockType,int lCurDate)
{
	// 有分钟数据生成分钟周期数据...

	HSMarketDataType cCodeType = pCode->m_cCodeType;
	int n = 0;
	BOOL bOpen = FALSE;
	pDay[0].m_lDate = lDate;
	int nHand = 1;
	if( MakeMarket(cCodeType) == STOCK_MARKET )
	{
		if( !MakeIndexMarket(cCodeType) )
		{
			nHand = pNowData->m_stStockData.m_nHand;
		}
		if( nHand <= 0 )
			nHand = 100;
	}

	long lClose = lPrevClose;
	int i;
	for(i = 0; i < nSize; i++)
	{
		if((pHisData[i].m_lTotal <= 0) && (i > 0))
		{
			pHisData[i].m_lTotal = pHisData[i-1].m_lTotal;
		}

		if((i == 0) || (( i != 1) && !((i-1)%nPeriod)))
		{
			if( pDay[n].m_lDate		  != 0	&& 
				pDay[n].m_lOpenPrice  != 0	&&
				pDay[n].m_lMaxPrice   != 0	&&
				pDay[n].m_lMinPrice   != 0	&&
				pDay[n].m_lClosePrice != 0 )
			{
				n++;
			}

			if( n >= nDayCount )
				n = nDayCount - 1;

			if(pHisData[i].m_lNewPrice != 0)
			{
				pDay[n].m_lOpenPrice  = pHisData[i].m_lNewPrice;
				pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lMaxPrice   = pHisData[i].m_lNewPrice;
				pDay[n].m_lMinPrice   = pHisData[i].m_lNewPrice;
				bOpen = TRUE;
			}
			else
			{
				if(n == 0)
				{
					pDay[n].m_lOpenPrice  = lClose;
					pDay[n].m_lClosePrice = lClose;
					pDay[n].m_lMaxPrice   = lClose;
					pDay[n].m_lMinPrice   = lClose;
				}
				else
				{
					pDay[n].m_lOpenPrice  = pDay[n-1].m_lClosePrice;
					pDay[n].m_lClosePrice = pDay[n-1].m_lClosePrice;
					pDay[n].m_lMaxPrice   = pDay[n-1].m_lClosePrice;
					pDay[n].m_lMinPrice   = pDay[n-1].m_lClosePrice;
				}

				bOpen = FALSE;
			}
			if(i > 0)
			{
				if( pHisData[i].m_lTotal > pHisData[i-1].m_lTotal )
					pDay[n].m_lTotal = (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal)/nHand;
			}
			else
			{
				if( pHisData[i].m_lTotal > 0 )
					pDay[n].m_lTotal = pHisData[i].m_lTotal/nHand;
			}
		}
		else
		{
			if( pHisData[i].m_lTotal > pHisData[i-1].m_lTotal )
				pDay[n].m_lTotal += (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal)/nHand;

			if(bOpen) 
			{
				if(pHisData[i].m_lNewPrice != 0)
				{
					if(pDay[n].m_lMaxPrice < pHisData[i].m_lNewPrice)
						pDay[n].m_lMaxPrice = pHisData[i].m_lNewPrice;
					if(pDay[n].m_lMinPrice > pHisData[i].m_lNewPrice)
						pDay[n].m_lMinPrice = pHisData[i].m_lNewPrice;
					pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
				}
			}
			else if(pHisData[i].m_lNewPrice != 0)
			{
				pDay[n].m_lOpenPrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lClosePrice = pHisData[i].m_lNewPrice;
				pDay[n].m_lMaxPrice  = pHisData[i].m_lNewPrice;
				pDay[n].m_lMinPrice  = pHisData[i].m_lNewPrice;
				bOpen = TRUE;
			}
		}
		if(nPeriod < 24*60)
		{
			if (MakeMainMarket(cCodeType) == (HJ_MARKET | HJ_SH_CURR))
			{
				pDay[n].m_lDate = YlsGetLongTime2(lCurDate, nPeriod*(n+1), pStockType);
			}
			else
				pDay[n].m_lDate = YlsGetLongTime2_Ex(lCurDate, nPeriod*(n+1), pStockType);//GetLongTime(cCodeType, nPeriod*(n+1),0);//,(bWrite?&pLogSystem:0));//nTime);
				
		}
	}

#if 0
	//
	CYlsArray<StockDay*,StockDay*> ay;

	StockDay* pStockDay;

	int nPreDate = 0;

	for(i = 0; i < n && i < nDayCount; i++)
	{
		if( pDay[i].m_lDate		  != 0	&& 
			pDay[i].m_lOpenPrice  != 0	&&
			pDay[i].m_lMaxPrice   != 0	&&
			pDay[i].m_lMinPrice   != 0	&&
			pDay[i].m_lClosePrice != 0 )
		{
			pStockDay = new StockDay;
			memcpy(pStockDay,&pDay[i],sizeof(StockDay));
			ay.Add(pStockDay);
		}
	}

	n = ay.GetSize();

	for( i = 0; i < n; i++ )
	{		
		memcpy(&pDay[i],ay.GetAt(i),sizeof(StockDay));
	}

	_delArrayObj(ay);
#endif

	return n;	
}

int GetDateByMinute(int lDate,CYlsTime& tmPre,int nPeriod)
{
	int nYear = lDate / 100000000;
	nYear -= 10;
	nYear += 2000;

	int nMonth  = lDate % 100000000 / 1000000;
	int nDay    = lDate % 100000000 / 10000 % 100;
	int nHour   = lDate % 100000000 % 10000 / 100;
	int nMinute = lDate % 100000000 % 10000 % 100;

	CYlsTime tm = CYlsTime(nYear,nMonth,nDay,nHour,nMinute,0);

	if( tmPre.GetDay() != tm.GetDay() )
	{
		tmPre = tm;
		return 1;
	}

	CYlsTimeSpan span = tm - tmPre;
	if((span.GetTotalMinutes() - nPeriod) >= 0)
	{
		tmPre = tm;
		return 1;
	}

	return 0;
}

int MakeMinuteDataByPanhou(CYlsArray<StockDay*,StockDay*>& ay,
						   StockDay* pHisData, int nSize, 
						   int nPeriod)
{
	// 由1分钟数据生成n分钟周期数据...

	int n = 0;
	BOOL bOpen = FALSE;

	int i;
	StockDay* pStockDay = NULL;

	CYlsTime tmPre;
	for( i = 0; i < nSize; i++ )
	{
		if( pHisData[i].m_lOpenPrice <= 0 )
			continue;

		if((pHisData[i].m_lTotal <= 0) && (i > 0))
		{
			pHisData[i].m_lTotal = pHisData[i-1].m_lTotal;
		}

		if( GetDateByMinute(pHisData[i].m_lDate,tmPre,nPeriod) )
		{
			pStockDay = new StockDay;
			memset(pStockDay,0,sizeof(StockDay));
			ay.Add(pStockDay);

			pStockDay->m_lDate		 = pHisData[i].m_lDate;
			pStockDay->m_lOpenPrice  = pHisData[i].m_lOpenPrice;
			pStockDay->m_lClosePrice = pHisData[i].m_lClosePrice;
			pStockDay->m_lMaxPrice   = pHisData[i].m_lMaxPrice;
			pStockDay->m_lMinPrice   = pHisData[i].m_lMinPrice;
			bOpen = TRUE;
		}
		else if( pStockDay != NULL )
		{
			pStockDay->m_lDate = pHisData[i].m_lDate;

			if( pHisData[i].m_lTotal > pHisData[i-1].m_lTotal )
				pStockDay->m_lTotal += (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal);

			if( pHisData[i].m_lMoney > pHisData[i-1].m_lMoney )
				pStockDay->m_lMoney += (pHisData[i].m_lMoney - pHisData[i-1].m_lMoney);

			if( bOpen ) 
			{
				if(pStockDay->m_lMaxPrice < pHisData[i].m_lMaxPrice)
					pStockDay->m_lMaxPrice = pHisData[i].m_lMaxPrice;
				if(pStockDay->m_lMinPrice > pHisData[i].m_lMinPrice)
					pStockDay->m_lMinPrice = pHisData[i].m_lMinPrice;
				pStockDay->m_lClosePrice = pHisData[i].m_lClosePrice;
			}
			else
			{
				pStockDay->m_lOpenPrice  = pHisData[i].m_lOpenPrice;
				pStockDay->m_lClosePrice = pHisData[i].m_lClosePrice;
				pStockDay->m_lMaxPrice   = pHisData[i].m_lMaxPrice;
				pStockDay->m_lMinPrice   = pHisData[i].m_lMinPrice;
				bOpen = TRUE;
			}
		}
	}

	for( i = 0; i < ay.GetSize(); i++ )
	{
		memcpy(&pHisData[i],ay.GetAt(i),sizeof(StockDay));
	}

	return ay.GetSize();
}

int GetDateByDay(int lDate,CYlsTime& tmPre,int nPeriod)
{
	int nYear = lDate / 10000;
	int nMonth  = lDate % 10000 / 100;
	int nDay    = lDate % 10000 % 100;

	CYlsTime tm = CYlsTime(nYear,nMonth,nDay,0,0,0);

	CYlsTimeSpan span = tm - tmPre;
	if((span.GetDays() - nPeriod) >= 0)
	{
		tmPre = tm;
		return 1;
	}

	return 0;
}

int MakeDayDataByPanhou(CYlsArray<StockDay*,StockDay*>& ay,
						StockDay* pHisData, int nSize, 
						int nPeriod)
{
	// 由日线数据生成n周期数据...

	int n = 0;
	BOOL bOpen = FALSE;

	int i;
	StockDay* pStockDay = NULL;

	CYlsTime tmPre;
	for( i = 0; i < nSize; i++ )
	{
		if( pHisData[i].m_lOpenPrice <= 0 )
			continue;

		if((pHisData[i].m_lTotal <= 0) && (i > 0))
		{
			pHisData[i].m_lTotal = pHisData[i-1].m_lTotal;
		}

		if( GetDateByDay(pHisData[i].m_lDate,tmPre,nPeriod) )
		{
			pStockDay = new StockDay;
			memset(pStockDay,0,sizeof(StockDay));
			ay.Add(pStockDay);

			pStockDay->m_lDate		 = pHisData[i].m_lDate;
			pStockDay->m_lOpenPrice  = pHisData[i].m_lOpenPrice;
			pStockDay->m_lClosePrice = pHisData[i].m_lClosePrice;
			pStockDay->m_lMaxPrice   = pHisData[i].m_lMaxPrice;
			pStockDay->m_lMinPrice   = pHisData[i].m_lMinPrice;
			bOpen = TRUE;
		}
		else if( pStockDay != NULL )
		{
			pStockDay->m_lDate = pHisData[i].m_lDate;

			if( pHisData[i].m_lTotal > pHisData[i-1].m_lTotal )
				pStockDay->m_lTotal += (pHisData[i].m_lTotal - pHisData[i-1].m_lTotal);

			if( pHisData[i].m_lMoney > pHisData[i-1].m_lMoney )
				pStockDay->m_lMoney += (pHisData[i].m_lMoney - pHisData[i-1].m_lMoney);

			if( bOpen ) 
			{
				if(pStockDay->m_lMaxPrice < pHisData[i].m_lMaxPrice)
					pStockDay->m_lMaxPrice = pHisData[i].m_lMaxPrice;
				if(pStockDay->m_lMinPrice > pHisData[i].m_lMinPrice)
					pStockDay->m_lMinPrice = pHisData[i].m_lMinPrice;
				pStockDay->m_lClosePrice = pHisData[i].m_lClosePrice;
			}
			else
			{
				pStockDay->m_lOpenPrice  = pHisData[i].m_lOpenPrice;
				pStockDay->m_lClosePrice = pHisData[i].m_lClosePrice;
				pStockDay->m_lMaxPrice   = pHisData[i].m_lMaxPrice;
				pStockDay->m_lMinPrice   = pHisData[i].m_lMinPrice;
				bOpen = TRUE;
			}
		}
	}

	for( i = 0; i < ay.GetSize(); i++ )
	{
		memcpy(&pHisData[i],ay.GetAt(i),sizeof(StockDay));

		delete ay.GetAt(i);
	}

	return ay.GetSize();
}


#ifndef HS_SUPPORT_UNIX
extern CYlsMutex* g_pReadNowMutex;
#endif

BOOL InitData()
{

	CATCH_Begin;

#ifdef HS_SUPPORT_UNIX
	CYlsMutexLock lock(&g_pReadNowMutex);
#else
	CYlsMutexLock lock(g_pReadNowMutex);
#endif

	//YlsPrompt("InitData()","begin");

	g_nInitAll = 1;

	if( !LoadAll(FALSE,TRUE) )
	{
		g_nInitAll = 0;

		//YlsPrompt("InitData()","LoadAll(FALSE,TRUE)");

		return FALSE;
	}

	CServerMarketInfo::InitDataAll();

	//YlsPrompt("InitData()","end");

	g_nInitAll = 0;

	CYlsClassSort::SetSortStatus(1);

	CATCH_End("CServerMarketInfo::InitDataAll error!",TRUE);

	//YlsPrompt("CServerMarketInfo::InitDataAll","完成");

	return TRUE;
}

int ReadNow(int& nMarket,int& nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
			CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,CYlsMutex* pYlsMutex)
{
	if( g_nInitAll )
		return 0;

	return ReadNow(nMarket,nIsChange,ay,ayChangeCode,1,pYlsMutex);
}

int ReadNow(int& nMarket,int& nIsChange,CYlsArray<CServerMarketInfo*,CServerMarketInfo*>& ay,
			CYlsArray<StockInitInfo*,StockInitInfo*>& ayChangeCode,UINT nPosition,
			CYlsMutex* pYlsMutex)
{
	try
	{
		// notice
		g_sNoticeSend.g_bSendNoticeText = FALSE;
		if(g_sNoticeSend.g_nOldNoticeTextLen != g_sNoticeSend.g_nNewNoticeTextLen)
		{
			g_sNoticeSend.g_bSendNoticeText   = TRUE;
			g_sNoticeSend.g_nOldNoticeTextLen = g_sNoticeSend.g_nNewNoticeTextLen;
		}

		// 跑马灯
		g_sScrollSend.g_bSendNoticeText = FALSE;
		if(g_sScrollSend.g_nOldNoticeTextLen != g_sScrollSend.g_nNewNoticeTextLen)
		{
			g_sScrollSend.g_bSendNoticeText   = TRUE;
			g_sScrollSend.g_nOldNoticeTextLen = g_sScrollSend.g_nNewNoticeTextLen;
		}

		return CServerMarketInfo::ReadNowAll(nMarket,nIsChange,ay,ayChangeCode,pYlsMutex);
	}
	catch(...)
	{
		//char szText[128];
		//sprintf(szText, "ReadNow(UINT nPosition)!");
		//ExceptionHandler(szText, strlen(szText));
	}

	return 0;
}

void ComputerMinuteRise(short nFirst,short nTotal, 
						HSMarketDataType cCodeType,
						ShareRealTimeData* pfNowData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,
						long* plResult, int nMinute)
{

	if( pfNowData == NULL || pStockInitInfo == NULL || pStockOtherData == NULL )
		return;

	if( nMinute == 0 )
		nMinute = 5;

	int nTotalTime = 0;

	CServerMarketInfo* pCServerMarketInfo = NULL;
	int nTime = 0;
	StockType* pStockType;
	cCodeType = 0;

	long lClose;	
	StockHistoryData* stHis = NULL;

	pfNowData += nFirst;
	pStockInitInfo += nFirst;

	//StockInfoIn* pStockInfoIn;

	int nMinTotal = 0;
	unsigned int nMinMax;

	for(int i = 0; i < nTotal; i++)
	{
		if( cCodeType != pStockInitInfo->m_ciStockCode.m_cCodeType ||
			pCServerMarketInfo == NULL )
		{
			cCodeType = pStockInitInfo->m_ciStockCode.m_cCodeType;

			pCServerMarketInfo = CServerMarketInfo::GetMarketByID(MakeMainMarket(cCodeType),pCServerMarketInfo);
			if( pCServerMarketInfo == NULL )
				return;

			//pStockInfoIn = FindIndex(&pStockInitInfo->m_ciStockCode,pCServerMarketInfo);
			//if( pStockInfoIn == NULL )
			//	return;

			pStockType = GetStockType(cCodeType,pCServerMarketInfo);
			if( pStockType == NULL )
				return;

			nTotalTime = GetBourseTotalTime(cCodeType) + 1;/*GetStockOffsetInHistory(pStockInfoIn->GetFenShiPos(pCServerMarketInfo),cCodeType);*///
			nTime = GetTime(cCodeType) + 1 - nMinute;
			nTime -= 1;

			nMinTotal = nTime;

			// by yls 2006.10.31
			//pfNowData = pCServerMarketInfo->GetShareRealTimeData();
			//pStockInitInfo = pCServerMarketInfo->GetStockInitInfo();

			//pfNowData += pStockType->m_nOffset;
			//pStockInitInfo += pStockType->m_nOffset;

			stHis = pCServerMarketInfo->GetStockHistoryData(pStockType->m_nOffset * nTotalTime,&nMinMax);
			nMinMax /= sizeof(StockHistoryData);
		}

		if( stHis == NULL )
			return;
		if( (nMinTotal + nTotalTime) > nMinMax )
			return;

		/*if( i == 1034 )
		{
		AfxMessageBox("OK");
		}*/

		if( (nTime >= 0) && (stHis != NULL) )
		{
			lClose = stHis[nTime].m_lNewPrice;
			stHis += nTotalTime;

			nMinTotal += nTotalTime;
		}
		else
		{
			lClose = pStockInitInfo->m_lPrevClose;

			//stHis += nTotalTime;
		}	

		if((lClose > 0) && (pfNowData->m_nowData.m_lNewPrice > 0))
		{
			plResult[i] = 10000L*(pfNowData->m_nowData.m_lNewPrice - lClose)/lClose;
		}
		else
		{
			plResult[i] = 0x80000000;
		}

		pStockInitInfo++;
		pfNowData++;
	}
}


long DynFillData(long* pData,
				 ShareRealTimeData*  pfNowData,
				 StockOtherData*  pOthers,
				 StockInitInfo*	pStockInitInfo,
				 long lMask,long lMask1)
{
	if( pfNowData == NULL || pOthers == NULL || 
		(lMask == 0 && lMask1 == 0) )
	{
		return 0;
	}

	/*if( MakeMarket(pStockInitInfo->m_ciStockCode.m_cCodeType) != STOCK_MARKET )
	{
	return 0;
	}*/

	long lLen = 0;
	if( lMask & MASK_REALTIME_DATA_OPEN )   //00000001       //今开盘
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lOpen);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_MAXPRICE	) //00000002     //最高价
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lMaxPrice);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_MINPRICE	) //00000004     //最低价
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lMinPrice);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_NEWPRICE	) //00000008     //最新价
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lNewPrice);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_TOTAL		) //00000010     //成交量(单位:股)
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lTotal);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_MONEY	   ) //00000020	   //成交金额(单位:元)
	{
		*((float*)pData) = YlsFloatComputerToIntel(pfNowData->m_nowData.m_fAvgPrice);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_BUYPRICE1	) //00000040
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyPrice1);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_BUYCOUNT1	) //00000080
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyCount1);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_BUYPRICE2	) //00000100
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyPrice2);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_BUYCOUNT2	) //00000200
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyCount2);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_BUYPRICE3	) //00000400
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyPrice3);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_BUYCOUNT3	) //00000800
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyCount3);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_BUYPRICE4	) //00000400
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyPrice4);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_BUYCOUNT4	) //00000800
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyCount4);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_BUYPRICE5	) //00000400
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyPrice5);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_BUYCOUNT5	) //00000800
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lBuyCount5);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_SELLPRICE1	) //00001000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellPrice1);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_SELLCOUNT1	) //00002000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellCount1);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_SELLPRICE2	) //00004000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellPrice2);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_SELLCOUNT2	) //00008000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellCount2);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_SELLPRICE3	) //00010000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellPrice3);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_SELLCOUNT3	) //00020000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellCount3);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_SELLPRICE4	) //00010000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellPrice4);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_SELLCOUNT4	) //00020000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellCount4);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_SELLPRICE5	) //00010000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellPrice5);
		pData ++; lLen += sizeof(long);
	}
	if( lMask & MASK_REALTIME_DATA_SELLCOUNT5	) //00020000
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lSellCount5);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_PERHAND		) //00040000      //股/手 单位
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_nHand);
		pData ++; lLen += sizeof(long);
	}

	if( lMask & MASK_REALTIME_DATA_NATIONAL_DEBT_RATIO ) // //国债利率
	{
		*pData = YlsIntC(pfNowData->m_nowData.m_lNationalDebtRatio);
		pData ++; lLen += sizeof(long);
	}

	// 其他数据
	if( lMask1 & MASK_REALTIME_DATA_TIME		) //00080000		//距开盘分钟数
	{
		*pData = YlsIntC(pOthers->m_nTime);
		pData ++; lLen += sizeof(long);
	}

	if( lMask1 & MASK_REALTIME_DATA_CURRENT	) //00100000		//现手
	{
		*pData = YlsIntC(pOthers->m_lCurrent);
		pData ++; lLen += sizeof(long);
	}

	if( lMask1 & MASK_REALTIME_DATA_OUTSIDE	) //00200000		//外盘
	{
		*pData = YlsIntC(pOthers->m_lOutside);
		pData ++; lLen += sizeof(long);
	}
	if( lMask1 & MASK_REALTIME_DATA_INSIDE		) //00400000		//内盘
	{
		*pData = YlsIntC(pOthers->m_lInside);
		pData ++; lLen += sizeof(long);
	}
	if( lMask1 & MASK_REALTIME_DATA_OPEN_POSITION	) //00800000      //今开仓
	{
		*pData = YlsIntC(pOthers->m_lKaiCang);
		pData ++; lLen += sizeof(long);
	}
	if( lMask1 & MASK_REALTIME_DATA_CLEAR_POSITION	) //01000000      //今平仓
	{
		*pData = YlsIntC(pOthers->m_lPingCang);
		pData ++; lLen += sizeof(long);
	}

	return lLen;
}


SysConfig g_sysSysConfig;

GGExternMghlMgpx* SysConfig::GetZqlSyl(CodeInfo* pCode)
{
	if( pCode == NULL )
		return NULL;

	char strKey[9];
	memset(strKey,0,sizeof(strKey));
	YlsGetKey(strKey,pCode);

	YlsRTrim(strKey);

	GGExternMghlMgpx* pGGExternMghlMgpx;
	if( !m_mapZqlSyl.Lookup(strKey,(void*&)pGGExternMghlMgpx) )
		return NULL;

	return pGGExternMghlMgpx;
}

void SysConfig::InitZqlSyl(char* strPath)
{
	if( strPath == NULL || 
		m_mapZqlSyl.GetCount() > 0 )
		return;

	CYlsFile fp;
	if( !fp.Open(strPath,Yls_Read_Open) )
		return;

	int nLen = fp.GetLength();
	if( nLen <= 0 )
	{
		fp.Close();
		return;
	}

	char* pData = new char[nLen];
	if( fp.Read(pData,nLen) != nLen )
		return;

	if( (nLen % sizeof(GGExternMghlMgpx)) != 0 )
		return;

	int nCount = nLen / sizeof(GGExternMghlMgpx);

	GGExternMghlMgpx* pGGExternMghlMgpx = (GGExternMghlMgpx*)pData;

	char szCode[9];
	for( int i = 0; i < nCount; i++,pGGExternMghlMgpx++ )
	{
		memset(szCode,0,sizeof(szCode));
		strncpy(szCode,pGGExternMghlMgpx->m_szCode,sizeof(pGGExternMghlMgpx->m_szCode));

		m_mapZqlSyl.SetAt(szCode,pGGExternMghlMgpx);
	}
}

BOOL SysConfig::IsCheckMemory()
{
	return (m_nInMemoryDeal_gp ||
		m_nInMemoryDeal_gg ||
		m_nInMemoryDeal_qh ||
		m_nInMemoryDeal_wp ||
		m_nInMemoryDeal_wh ||
        m_nInMemoryDeal_hj // added by Ben
		);
}

BOOL SysConfig::IsMemory(HSMarketDataType cBourse)
{
	if( WhoMarket(cBourse,STOCK_MARKET) )   // gu
	{
		return m_nInMemoryDeal_gp;
	}
	else if( WhoMarket(cBourse,HK_MARKET) )  //港股 
	{
		return m_nInMemoryDeal_gg;
	}
	else if( WhoMarket(cBourse,FUTURES_MARKET) )
	{
		return m_nInMemoryDeal_qh;
	}
	else if( WhoMarket(cBourse,WP_MARKET) )
	{
		return m_nInMemoryDeal_wp;
	}
	else if( WhoMarket(cBourse,FOREIGN_MARKET) )
	{
		return m_nInMemoryDeal_wh;
	}
	else if( WhoMarket(cBourse,HJ_MARKET) )  // added by Ben
	{
		return m_nInMemoryDeal_hj;
	}
	return 0;
}

BOOL SysConfig::IsSupport(HSMarketDataType cBourse)
{
	if( WhoMarket(cBourse,STOCK_MARKET) )   // gu
	{
		return nEntry_Support_GP;
	}
	else if( WhoMarket(cBourse,HK_MARKET) )  //港股 
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
	else if( WhoMarket(cBourse,HJ_MARKET) )  // added by Ben
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
	}

	return 0;
}

const char* SysConfig::GetIndentFileName(char*& szRet,const char* szDir,const char* szExt)
{
	char szSplitFileName[_MAX_PATH];

#ifdef HS_SUPPORT_UNIX	
	CYlsTime tm = CYlsTime::GetCurrentTime();
	sprintf(szSplitFileName,"%i%s", 
		tm.GetTime(),
		szExt );
#else
	SYSTEMTIME timeDest;
	GetSystemTime( &timeDest );
	sprintf(szSplitFileName,"%04d%02d%02d%02d%02d%02d%02d%02d%s", 
		timeDest.wYear,
		timeDest.wMonth,
		timeDest.wDayOfWeek,
		timeDest.wDay,
		timeDest.wHour,
		timeDest.wMinute, 
		timeDest.wSecond, 
		timeDest.wMilliseconds,
		szExt );
#endif

	char szCur[_MAX_PATH];
	memset(szCur,0,sizeof(szCur));
	strncpy(szCur,szDir,sizeof(szCur));
	strcat(szCur,szSplitFileName);

	while(1)
	{
		if( (access( szCur, 0 )) != 0 )
		{
			strncpy(szRet,szSplitFileName,_MAX_PATH);
			return szRet;
			//return szSplitFileName;
		}
		else
		{
#ifdef	HS_SUPPORT_UNIX
			Usleep(1000);
#else
			Sleep(1000);
#endif			return GetIndentFileName(szRet,szDir,szExt);
		}
	}

	memset(szRet,0,sizeof(szRet));
	return szRet;
}

char* SysConfig::GetIndexFileName(char* szIndexFileName,const char* szMarketName,
								  const char* szPath,const char* szFileName,
								  const char* szExt /*= ".HK"*/)
{
	if( m_strZixunPath[0] == '\0' || 
		szPath == NULL			  || 	
		szFileName == NULL		  ||
		szMarketName == NULL	  ||
		szExt == NULL )
		return NULL;


	sprintf(szIndexFileName,"%s%s%s%s%s",m_strZixunPath,szMarketName,Yls_Path_Spl,szPath,Yls_Path_Spl);

	CreatPath(szIndexFileName,TRUE);

	YlsAllTrim(szFileName);
	sprintf(szIndexFileName,"%s%s%s%s%s%s%s",
		m_strZixunPath,szMarketName,Yls_Path_Spl,
		szPath,Yls_Path_Spl,
		szFileName,szExt);

	return szIndexFileName;
}

BOOL SysConfig::IsInit(int nDate)
{
	CYlsTime tmNow = CYlsTime::GetCurrentTime();

	char szDate[20];
	sprintf(szDate,"%04d%02d%02d",
		tmNow.GetYear(),tmNow.GetMonth(),tmNow.GetDay());

	nDate = atol(szDate);
	for( int i = 0;i < m_ayNotInitDate.GetSize(); i++ )
	{
		if(m_ayNotInitDate.GetAt(i) == nDate)
			return 0;
	}

	return (tmNow.GetDayOfWeek() >= 2 && tmNow.GetDayOfWeek() <= 6);
}

BOOL SysConfig::IsShouPan(int nDate)
{
	for( int i = 0;i < m_ayNotDoPanHou.GetSize(); i++ )
	{
		if(m_ayNotDoPanHou.GetAt(i) == nDate)
			return 1;
	}

	return 0;
}



////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
void YlsFree( void* pData, int nType /*= charType*/ )
{
	switch( nType )
	{
	case charType:
		{
			delete[] (char*)pData;
		}
		break;
	}
}

void* YlsAlloc( long nCurSize,int nType /*= charType */  )
{		
	switch( nType )
	{
	case charType:
		{
			if( nCurSize <= 0 )
			{
				return NULL;
			}
			char* pData = new char[nCurSize];
			memset( pData,0,nCurSize);
			return pData;
		}
		break;
	}

	return NULL;
}


BOOL UDPSend(const char *pszData,int cbData)
{
#ifndef HS_SUPPORT_UNIX

#ifndef Support_Manager_Start
	return 0;
#endif

	if( !g_sysSysConfig.m_nSupportUDPSendLog )
		return 0;

	static CString strAddr;
	static int nPort;
	static UDPApplay* pUDPApplay = NULL;
	if( pUDPApplay == NULL )
	{
		CWinApp *pApp = AfxGetApp();
		strAddr = pApp->GetProfileString(Section_Internet, UDP_TRACE_Addr, "211.155.231.101");//"www.hsmobile.cn");
		pApp->WriteProfileString(Section_Internet, UDP_TRACE_Addr, strAddr);
		nPort = pApp->GetProfileInt(Section_Internet, UDP_TRACE_PORT, 1394);
		pApp->WriteProfileInt(Section_Internet, UDP_TRACE_PORT, nPort);

		pUDPApplay = new UDPApplay();
	}

	int ret;

	CATCH_Begin;

	ret = pUDPApplay->UDPSendData(pszData,cbData,strAddr,nPort);

	CATCH_End0("pUDPApplay->UDPSendData");

	return ret;

#endif

}

BOOL YlsIsFullToday(StockType* pStockType)
{
	// 判断是否夸天
	int nPos = -1;
	int nCount = _countof(pStockType->m_nNewTimes);
	
	int nOpenTime = -1;

	for(int j = 0; j <= nCount; j++)
	{
		// 比较开盘
		if( nOpenTime == -1 )
		{
			nOpenTime = pStockType->m_nNewTimes[j].m_nOpenTime;
		}

		if( pStockType->m_nNewTimes[j].m_nOpenTime == -1 || pStockType->m_nNewTimes[j].m_nCloseTime == -1 )
		{
			if (nOpenTime != -1 && pStockType->m_nNewTimes[j -1].m_nOpenTime != -1)
			{
				if (nOpenTime == pStockType->m_nNewTimes[j -1].m_nCloseTime)
					return true;
			}
			break;
		}
	}

	return false;
}

long YlsIsOverToday(StockType* pStockType,int nCount)
{
	// 判断是否夸天
	int nPos = -1;
	for(int j = 0; j <= nCount; j++)
	{
		if( pStockType->m_nNewTimes[j].m_nOpenTime == -1 || pStockType->m_nNewTimes[j].m_nCloseTime == -1 )
			break;

		// 比较开盘
		if( nPos <= pStockType->m_nNewTimes[j].m_nOpenTime )
		{
			nPos = pStockType->m_nNewTimes[j].m_nOpenTime;
		}
		else
		{
			return 1;
		}

		// 比较收盘
		if( nPos <= pStockType->m_nNewTimes[j].m_nCloseTime )
		{
			nPos = pStockType->m_nNewTimes[j].m_nCloseTime;
		}
		else
		{
			return 1;
		}
	}

	return 0;
}

long YlsConvertToday(StockType* pStockType,long nTime,long lCurDate)
{
	/*if( YlsGetToday(pStockType,nTime) )
	{
		CYlsTime cDate = LongToDate(lCurDate);
		cDate += CYlsTimeSpan(1,0,0,0);

		char strTime[64];
		sprintf(strTime,"%04d%02d%02d",cDate.GetYear(),cDate.GetMonth(),cDate.GetDay());

		lCurDate = atol(strTime);
	}*/

	return lCurDate;
}

long YlsGetToday(StockType* pStockType,long nTime)
{
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;

	int nCount = _countof(pStockType->m_nNewTimes);
	int i;

	for(i = 0; i < nCount; i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		if( nTime >= pHSTypeTime->GetDist() )
		{
			nTime -= pHSTypeTime->GetDist();
		}
		else
		{
			// 判断是否夸天
			return YlsIsOverToday(pStockType,i);
		}
	}

	return YlsIsOverToday(pStockType,min((nCount-1),i));
}

long YlsGetLongTime(StockType* pStockType,int lDate,short nOffset,
					int nDays /*= 0*/,
					LogSystem* pLogSystem /*= NULL*/)
{
	if( pStockType == NULL )
		return -1;

	short nMinute = pStockType->m_union.m_nAheadOpenTime + nOffset;
	if(nMinute > pStockType->m_union.m_nAheadCloseTime)
	{
		nMinute -= pStockType->m_union.m_nAheadCloseTime;
		nMinute += pStockType->m_union.m_nAfterOpenTime;
		if(nMinute > pStockType->m_union.m_nAfterCloseTime)
		{
			nMinute = pStockType->m_union.m_nAfterCloseTime;
		}

#ifdef Support_JiaoHang_AutoEvery
		nDays = 1;
#endif
	}

	int lRetDate;
	if( nDays > 0 )
	{
		CYlsTime cDate = LongToDate(lDate);
		cDate += CYlsTimeSpan((long)nMinute*60L);
		if( nDays > 0 )
			cDate += CYlsTimeSpan(nDays,0,0,0);

		lRetDate = YlsGetTime(&cDate);
	}
	else
	{
		lRetDate = YlsGetTimeEx(lDate/10000,lDate/100%100,lDate%100,
			nMinute / 60,nMinute % 60);
	}

	if( pLogSystem )
	{
		char szDate[512];
		sprintf(szDate,"New:%i,Old:%i,%i,open1:%i,%i,open2:%i,%i\r\n",lRetDate,lDate,nMinute,
			pStockType->m_union.m_nAheadOpenTime,
			pStockType->m_union.m_nAheadCloseTime,
			pStockType->m_union.m_nAfterOpenTime,
			pStockType->m_union.m_nAfterCloseTime);
		pLogSystem->WriteLog(szDate);
	}

	return lRetDate;
}

int YlsGetWholeTime(CYlsTime& tm, int lDate,short nOffset,StockTick* pStockTick,StockType* pStockType)
{
	if( pStockType == NULL || lDate <= 0 )
		return 0;

	short nMinute = nOffset;

	HSTypeTime* pCur = NULL;
	HSTypeTime* pPre = NULL;
	HSTypeTime* pLast = NULL;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;

	int nCount = _countof(pStockType->m_nNewTimes);

	// 查找指定区间的时间
	for( int i = 0; i < nCount; i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		pCur = pPre;
		pPre = pHSTypeTime;

		if( nMinute >= pHSTypeTime->GetDist() )
		{
			nMinute -= pHSTypeTime->GetDist();
		}
		else
		{
			if( (i+1) < nCount )
			{
				pHSTypeTime++;
				pLast = pHSTypeTime;
			}
			break;
		}
	}

	// 没有找到,超过交易区间
	if( pLast == NULL && pPre != NULL ) 
	{
		nMinute = pPre->m_nCloseTime;
	}
	else if( pPre != NULL )
	{
		nMinute += pPre->m_nOpenTime;

		/*if( pCur != NULL )
			nMinute += pCur->m_nCloseTime;
		else
			nMinute += pPre->m_nOpenTime;*/
	}

	tm = LongToDate(lDate);
	tm += CYlsTimeSpan(0,nMinute/60,nMinute%60,pStockTick->m_sDetailTime.m_nSecond);

	//// 是否夸天
	//int nDays = YlsGetToday(pStockType,nOffset);

	//// 计算日期时间
	//if( nDays > 0 )
	//{
	//	tm = LongToDate(lDate);
	//	tm += CYlsTimeSpan(nDays,nMinute/60,nMinute%60,pStockTick->m_sDetailTime.m_nSecond);
	//}
	//else
	//{
	//	tm = CYlsTime(lDate/10000,lDate/100%100,lDate%100,
	//		nMinute / 60,nMinute % 60,pStockTick->m_sDetailTime.m_nSecond);
	//}

	return 1;
}

long YlsGetLongTime2(int lDate,short nOffset,StockType* pStockType)
{
	if( pStockType == NULL || lDate <= 0 )
		return 0;

	short nMinute = nOffset;

	HSTypeTime* pCur = NULL;
	HSTypeTime* pPre = NULL;
	HSTypeTime* pLast = NULL;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;

	int nCount = _countof(pStockType->m_nNewTimes);

	// 查找指定区间的时间
	for( int i = 0; i < nCount; i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		pCur = pPre;
		pPre = pHSTypeTime;

		if( nMinute >= pHSTypeTime->GetDist() )
		{
			nMinute -= pHSTypeTime->GetDist();
		}
		else
		{
			if( (i+1) < nCount )
			{
				pHSTypeTime++;
				pLast = pHSTypeTime;
			}
			break;
		}
	}

	// 没有找到,超过交易区间
	if( pLast == NULL && pPre != NULL ) 
	{
		nMinute = pPre->m_nCloseTime;
	}
	else if( pPre != NULL )
	{
		nMinute += pPre->m_nOpenTime;

		/*
		if( pCur != NULL )
			nMinute += pCur->m_nCloseTime;
		else
			nMinute += pPre->m_nOpenTime;
			*/
	}

	CYlsTime cDate = LongToDate(lDate);
	cDate += CYlsTimeSpan(0,nMinute/60,nMinute%60,0);
	return YlsGetTime(&cDate);



	//return lRetDate;
}


long YlsGetLongTime2_Ex(int lDate,short nOffset,StockType* pStockType)
{
	if( pStockType == NULL || lDate <= 0 )
		return 0;

	short nMinute = nOffset;

	HSTypeTime* pCur = NULL;
	HSTypeTime* pPre = NULL;
	HSTypeTime* pLast = NULL;
	HSTypeTime* pHSTypeTime = pStockType->m_nNewTimes;

	int nCount = _countof(pStockType->m_nNewTimes);

	// 查找指定区间的时间
	for( int i = 0; i < nCount; i++,pHSTypeTime++ )
	{
		if( pHSTypeTime->m_nOpenTime == -1 || pHSTypeTime->m_nCloseTime == -1 )
			break;

		pCur = pPre;
		pPre = pHSTypeTime;

		if( nMinute >= pHSTypeTime->GetDist() )
		{
			nMinute -= pHSTypeTime->GetDist();
		}
		else
		{
			if( (i+1) < nCount )
			{
				pHSTypeTime++;
				pLast = pHSTypeTime;
			}
			break;
		}
	}

	// 没有找到,超过交易区间
	if( pLast == NULL && pPre != NULL ) 
	{
		nMinute = pPre->m_nCloseTime;
	}
	else if( pPre != NULL )
	{
		nMinute += pPre->m_nOpenTime;

		/*
		if( pCur != NULL )
			nMinute += pCur->m_nCloseTime;
		else
			nMinute += pPre->m_nOpenTime;
			*/
	}

	// 是否夸天
	int nDays = YlsGetToday(pStockType,nOffset);
	// 计算日期时间
	int lRetDate;
	if( nDays > 0 )
	{
		CYlsTime cDate = LongToDate(lDate);
		cDate += CYlsTimeSpan(nDays,nMinute/60,nMinute%60,0);

		lRetDate = YlsGetTime(&cDate);
	}
	else
	{
		lRetDate = YlsGetTimeEx(lDate/10000,lDate/100%100,lDate%100,
			nMinute / 60,nMinute % 60);
	}

	CYlsTime cDate = LongToDate(lDate);
	cDate += CYlsTimeSpan(nDays,nMinute/60,nMinute%60,0);
	return YlsGetTime(&cDate);

}

void YlsLongToDate(long lDate,int& nHour,int& nMinute)
{
	nHour   = lDate%10000/100;
	nMinute = lDate%100;
}


short GetStockPriceDecimal(HSMarketDataType cStockType)
{
	if( MakeMarket(cStockType) == STOCK_MARKET/*SH_Bourse*/ )
	{
		if( MakeSubMarket(cStockType)  == KIND_STOCKB || 
			MakeSubMarket(cStockType)  == KIND_FUND   || 
			MakeSubMarket(cStockType)  == KIND_LOF	  ||
			MakeETF(cStockType) )
		{
			return 3;
		}
	}

	return 2;
}

short GetStockPriceDecimal(const CodeInfo* pInfo)
{
	if( pInfo == NULL )
		return 2;

	if( (pInfo->m_cCode[0] == '1' && pInfo->m_cCode[1] == '3') || // 13
		(pInfo->m_cCode[0] == '2' && pInfo->m_cCode[1] == '0') || // 20
		(pInfo->m_cCode[0] == '1' && pInfo->m_cCode[1] == '8') || // 18
		(pInfo->m_cCode[0] == '5' && pInfo->m_cCode[1] == '0' && pInfo->m_cCode[2] == '0') ||   // 500
		(pInfo->m_cCode[0] == '5' && pInfo->m_cCode[1] == '8') || // 58
		(pInfo->m_cCode[0] == '0' && pInfo->m_cCode[1] == '3')    // 03
		)
	{
		return 3;
	}

	return GetStockPriceDecimal(pInfo->m_cCodeType);
}


void WriteReportInfo()
{
	if( !g_sysSysConfig.m_nSupportTotal )
		return;

#ifdef HS_SUPPORT_UNIX

	static CYlsTime tmLast = CYlsTime::GetCurrentTime();

	CYlsTimeSpan span = CYlsTime::GetCurrentTime() - tmLast;
	if( span.GetTotalMinutes() < 1 ) // 一分钟写一次
		return;

	tmLast = CYlsTime::GetCurrentTime();

	static CYlsFile fp;	
	if( fp.m_hFile == INVALID_HANDLE_VALUE )
	{
		memset(&m_sEvery,0,sizeof(m_sEvery));

		char szPath[260];
		sprintf(szPath,"%s%i",CHSFilePath::GetPath(szPath,CHSFilePath::SrvTotalPath),getpid());

		if(!fp.Open(szPath,Yls_Create_NoTruncate_Open))
			return;
	}
	if(fp.m_hFile == INVALID_HANDLE_VALUE)
		return;

	fp.SeekToBegin();
	m_sEvery.m_lTime = tmLast.GetTime();
	fp.Write(&m_sEvery,sizeof(m_sEvery));

	//printf("pid:%i,receive:%i,send:%i,PacketCounts:%f,QuitCounts:%f,SendPacketCounts:%f\r\n",
	//	getpid(),m_sEvery.m_sFlux.m_nRecieve,m_sEvery.m_sFlux.m_nSend,
	//	m_sEvery.m_packet.m_dPacketCounts,m_sEvery.m_packet.m_dQuitCounts,m_sEvery.m_packet.m_dSendPacketCounts);

	//m_sEvery.m_sFlux.Empty();
	//m_sEvery.m_packet.Empty();

#endif
}

void WriteReportInfoTotal()
{
	if( !g_sysSysConfig.m_nSupportTotal )
		return;

#ifdef HS_SUPPORT_UNIX

	static CYlsTime tmLast = CYlsTime::GetCurrentTime();

	CYlsTimeSpan span = CYlsTime::GetCurrentTime() - tmLast;
	if( span.GetTotalMinutes() < 1 ) // 一分钟写一次
		return;

	tmLast = CYlsTime::GetCurrentTime();

	static const int File_Max_length = 1024*1024*5;
	static CYlsFile fp;
	static CHqDataBuffer szCurProgramName;
	if( fp.m_hFile == INVALID_HANDLE_VALUE )
	{
		memset(&m_sEvery,0,sizeof(m_sEvery));

		char szFile[260];
		char szPath[260];
		sprintf(szFile,"%sEveryReport",CHSFilePath::GetPath(szPath,Srv_Setting));

		if(!fp.Open(szFile,Yls_Create_NoTruncate_Open))
			return;

		szCurProgramName.AddStr(YlsExe_server_Name);
	}
	if(fp.m_hFile == INVALID_HANDLE_VALUE)
		return;

	// 连接数
	m_sEvery.m_srv.m_lCurConnect = CYlsBaseDoc::GetProcessConnectCount(szCurProgramName,
		YlsExe_server_Name,g_sysSysConfig.m_nPort);

	if( m_sEvery.m_srv.m_lCurConnect <= 0 )
		return;

	float fCPUTotal = 0;
	float fMEMTotal = 0;
	if( CYlsBaseDoc::GetProcessInfo_ps(szCurProgramName,YlsExe_server_Name,fCPUTotal,fMEMTotal)  )
	{
		m_sEvery.m_srv.m_lCpu = fCPUTotal;
		m_sEvery.m_srv.m_lMemTotal = fMEMTotal;
	}

	char szFileName[_MAX_PATH];	
	CHSFilePath::GetPath(szFileName,Srv_Dynamic_File);
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> ayRet;
	int nCount = GetFileProcess_Child(szFileName,Section_This,Entry_CurProcessID_Child,ayRet);
	if( nCount <= 0 )
		return;

	char szDataPath[260];
	CHqDataBuffer* pBuffer;
	HS_EveryTimeData sEvery;
	BOOL bWrite = FALSE;

	for(int i = 0; i < ayRet.GetSize(); i++ )
	{
		pBuffer = ayRet.GetAt(i);
		if( pBuffer == NULL || pBuffer->m_lpszBuffer == NULL )
			continue;

		char szPath[256];
		sprintf(szDataPath,"%s%i",CHSFilePath::GetPath(szPath,CHSFilePath::SrvTotalPath),atol(pBuffer->m_lpszBuffer));
		CYlsFile fp;
		if( fp.Open(szDataPath,Yls_OnlyRead_Open) )
		{
			if( fp.Read(&sEvery,sizeof(sEvery)) == sizeof(sEvery) )
			{
				CYlsTime tm = sEvery.m_lTime;
				CYlsTimeSpan span = tmLast - tm;
				if( span.GetTotalMinutes() >= (0 - 5) && span.GetTotalMinutes() <= 5 )
				{
					m_sEvery.m_sFlux.m_nRecieve += sEvery.m_sFlux.m_nRecieve;
					m_sEvery.m_sFlux.m_nSend	+= sEvery.m_sFlux.m_nSend;

					m_sEvery.m_packet.m_dPacketCounts		+= sEvery.m_packet.m_dPacketCounts;
					m_sEvery.m_packet.m_dQuitCounts			+= sEvery.m_packet.m_dQuitCounts;
					m_sEvery.m_packet.m_dSendPacketCounts	+= sEvery.m_packet.m_dSendPacketCounts;

					m_sEvery.m_packet.m_dFenshiPacket	+= sEvery.m_packet.m_dFenshiPacket	;		// 分时数据包
					m_sEvery.m_packet.m_dDayPacket		+= sEvery.m_packet.m_dDayPacket		;		// 日线数据包
					m_sEvery.m_packet.m_dSortPacket61	+= sEvery.m_packet.m_dSortPacket61	;		// 61~66排名数据包
					m_sEvery.m_packet.m_dSortPacket81	+= sEvery.m_packet.m_dSortPacket81	;		// 81~86排名数据包
					m_sEvery.m_packet.m_dInfoPacket		+= sEvery.m_packet.m_dInfoPacket	;		// 资料数据包
					m_sEvery.m_packet.m_dPricePacket	+= sEvery.m_packet.m_dPricePacket	;		// 报价数据包
					m_sEvery.m_packet.m_dEveryPacket	+= sEvery.m_packet.m_dEveryPacket	;		// 主推数据包

					bWrite = TRUE;
				}
				else
				{
					printf("不是统计区间:%i\r\n",span.GetTotalMinutes());
				}			
			}

			fp.Close();
		}
		else
		{
			printf("不能打开:%s\r\n",szDataPath);
			remove(szDataPath);
		}
	}

	if( !bWrite )
		return;

	m_sEvery.m_lTime = tmLast.GetTime();

	int nLen = fp.GetLength();
	if( nLen > File_Max_length )
	{
		fp.SetLength(0);
	}
	fp.SeekToEnd();

	m_sEvery.m_sFlux.m_nRecieve /= 1024;
	m_sEvery.m_sFlux.m_nSend    /= 1024;

	fp.Write(&m_sEvery,sizeof(m_sEvery));


	printf("total-pid:%i,connect:%i,receive:%i,send:%i,PacketCounts:%f,QuitCounts:%f,SendPacketCounts:%f\r\n",
		getpid(),
		m_sEvery.m_srv.m_lCurConnect,
		m_sEvery.m_sFlux.m_nRecieve,m_sEvery.m_sFlux.m_nSend,
		m_sEvery.m_packet.m_dPacketCounts,m_sEvery.m_packet.m_dQuitCounts,m_sEvery.m_packet.m_dSendPacketCounts);

	printf("total-pid:%i,fenshi:%f,day:%f,61:%f,81:%f,zx:%f,report:%f,auto:%f\r\n",
		getpid(),
		m_sEvery.m_packet.m_dFenshiPacket,		// 分时数据包
		m_sEvery.m_packet.m_dDayPacket	,		// 日线数据包
		m_sEvery.m_packet.m_dSortPacket61,		// 61~66排名数据包
		m_sEvery.m_packet.m_dSortPacket81,		// 81~86排名数据包
		m_sEvery.m_packet.m_dInfoPacket	,		// 资料数据包
		m_sEvery.m_packet.m_dPricePacket,		// 报价数据包
		m_sEvery.m_packet.m_dEveryPacket);		// 主推数据包	

	m_sEvery.m_sFlux.Empty();
	m_sEvery.m_packet.Empty();

#endif

}



bool g_IsValidDate(unsigned long lDate)
{
	int year,month,day;
	year = lDate /10000;
	month = (lDate / 100) % 100;
	day = lDate % 100;

	if (year < 1900 || year > 2100 || month <= 0 || month > 12 || day <= 0 || day > 31)
	{
		return false;
	}

	if (month <= 12 && day <= 31) 
	{ 
		if ( year % 1000 == 0 && year % 400 == 0 && month == 2 && day == 29) 
			return true; 
		else if ((month==1||month==3||month==5||month==7||month==8||month==10||month==12) && (day >= 30)) return true; 
		else if ((month==4||month==6||month==9||month==11) && day == 30 ) return true;
		else if (day < 30) return true;
		else 
			return false;
	} 
	else 
		return false; 

}

bool g_IsValidDateTime(unsigned long lTime)
{
	int year,month,day,nHou,nMin;
	year = lTime /100000000 + 1990;
	month = (lTime / 1000000) % 100;
	day = (lTime / 10000) % 100;

	int nDate = year * 10000 + month * 100 + day;
	if (g_IsValidDate(nDate))
	{
		nHou = (lTime / 100) % 100;
		nMin = lTime % 100;

		if (nHou >= 0 && nHou <= 24 && nMin >= 0 && nMin <= 60)
			return true;
	}
	return false;
}