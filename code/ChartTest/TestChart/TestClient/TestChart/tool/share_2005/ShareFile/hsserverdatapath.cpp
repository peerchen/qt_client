/*******************************************************************************
* Copyright (c)2003, ��������ϵͳ���޹�˾
* All rights reserved.
*
* �ļ����ƣ�*.h
* �ļ���ʶ��
* ժ    Ҫ��
*
* ��ǰ�汾��YLink1.2
* ��    �ߣ�YLink����
* ������ڣ�2005
*
* ��    ע��
*
* �޸ļ�¼��
*
*******************************************************************************/



#include "stdafx.h"
#include "hsserverdatapath.h"

#include "hs_disk_h.h"
#include "tool.h"

#include "globalfun.h"

//#ifndef Srv_Setting_str
//#define Srv_Setting_str		"Srv_Setting/"      // ������
//#endif

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////


static char g_szSupper[] = "FLHQSUPPERFLHQ";//


HSServerDataPath::HSServerDataPath(HSMarketDataType cBourse /*= 0*/)
:HsShareMemManager()
{
	memset(this,0,sizeof(HSServerDataPath));
	//m_cMemLoad = 0;
	m_cBourse = cBourse;
}

void HSServerDataPath::MakeValidPath(char* strBasePath)
{
	int lLen = strlen(strBasePath);
	if( lLen > 1 && strBasePath[lLen-1] != Yls_Path_Spl_Char )
		strcat(strBasePath,Yls_Path_Spl);
}

char* HSServerDataPath::GetMarketName(char* strRet,int nLen)
{
	return MarketNameMan::GetMarketName(m_cBourse,strRet,nLen);
}

void HSServerDataPath::SetNowPath(const char* strBasePath,
								  int nAllocType /*= ERROR_ALREADY_EXISTS*/)
{
	char strName[128];
	MarketNameMan::GetMarketName(m_cBourse,strName,sizeof(strName));

	strncpy(m_strNowBasePath,strBasePath,sizeof(m_strNowBasePath));
	MakeValidPath(m_strNowBasePath);
	CreatPath(m_strNowBasePath);

	sprintf(m_SHFileNowName,"%s%s-%s.%hx",m_strNowBasePath,strName,"real",m_cBourse);
	sprintf(m_SHFileTraName,"%s%s-%s.%hx",m_strNowBasePath,strName,"tick",m_cBourse);
	sprintf(m_SHFileInfoName,"%s%s-%s.%hx",m_strNowBasePath,strName,"bourseinfo",m_cBourse);
	sprintf(m_SHFileHisName,"%s%s-%s.%hx",m_strNowBasePath,strName,"trend",m_cBourse);
	sprintf(m_SHFileCodeInfo,"%s%s-%s.%hx",m_strNowBasePath,strName,"stockinfo",m_cBourse);
	sprintf(m_strFileCodeList,"%s%s-%s.%hx",m_strNowBasePath,strName,"initinfo",m_cBourse);
	sprintf(m_strFileOtherData,"%s%s-%s.%hx",m_strNowBasePath,strName,"other",m_cBourse);	

	sprintf(m_SHFileMsgName,"%s%s-%s.%hx",m_strNowBasePath,strName,"News.txt",m_cBourse);

	sprintf(m_strFileCDP,"%s%s-%s.%hx",m_strNowBasePath,strName,"cdp",m_cBourse);

	sprintf(m_strBrokerFile,"%s%s-%s.%hx",m_strNowBasePath,strName,"broker",m_cBourse);

	// for level2
	sprintf(m_strLvl2OrderQueue,"%s%s-%s.%hx",m_strNowBasePath,strName,"OrderQueue",m_cBourse);
	sprintf(m_strLvl2Consolidated,"%s%s-%s.%hx",m_strNowBasePath,strName,"Consolidated",m_cBourse);
	sprintf(m_strLvl2Cancellation,"%s%s-%s.%hx",m_strNowBasePath,strName,"Cancellation",m_cBourse);
	
	// ��ʼ������ļ�
	sprintf(m_strInitFileCheck,"%s%s-%s.%hx",m_strNowBasePath,strName,"Check",m_cBourse);
	sprintf(m_strInitFileCheckBegin,"%s%s-%s.%hx",m_strNowBasePath,strName,"Begin",m_cBourse);

	// ���߼���ļ�
	sprintf(m_strFillDataBegin,"%s%s-%s.%hx",m_strNowBasePath,strName,"FillBegin",m_cBourse);
	sprintf(m_strFillDataEnd,"%s%s-%s.%hx",m_strNowBasePath,strName,"FillEnd",m_cBourse);

	// �ڴ�������
	sprintf(m_strShareData,"%s%s-%s.%hx",m_strNowBasePath,strName,"Param",m_cBourse);


	// ��ӹ����ڴ�
	if( (nAllocType == ERROR_SUCCESS) || // ��һ�δ���
		g_sysSysConfig.IsMemory(m_cBourse) )
	{
		AddShareMemName(nAllocType);
	}

	//YlsPrompt("����ʵʱ�ļ�",m_strInitFileCheckBegin);
}

void HSServerDataPath::SetMemToDiskFile()
{
	if( !IsHaveShareMemory() )
		return;

	m_Memory_real->SetFileName(m_SHFileNowName);					// ʵʱ����
	m_Memory_tick->SetFileName(m_SHFileTraName);					// �ֱ�����
	m_Memory_bourseinfo->SetFileName(m_SHFileInfoName);				// ������Ϣ����
	m_Memory_trend->SetFileName(m_SHFileHisName);					// ��������
	m_Memory_stockinfo->SetFileName(m_SHFileCodeInfo);				// ������Ϣ
	m_Memory_initinfo->SetFileName(m_strFileCodeList);				// ��ʼ������
	m_Memory_other->SetFileName(m_strFileOtherData);				// ��������
}

void HSServerDataPath::SaveFileData()
{
	if( !IsHaveShareMemory() )
		return;

	m_Memory_real->SaveMemToFile();					// ʵʱ����
	m_Memory_tick->SaveMemToFile();					// �ֱ�����
	m_Memory_bourseinfo->SaveMemToFile();			// ������Ϣ����
	m_Memory_trend->SaveMemToFile();				// ��������
	m_Memory_stockinfo->SaveMemToFile();			// ������Ϣ
	m_Memory_initinfo->SaveMemToFile();				// ��ʼ������
	m_Memory_other->SaveMemToFile();				// ��������
}

int HSServerDataPath::AddShareMemName(int nAllocType /*= ERROR_ALREADY_EXISTS*/)
{
	if( IsHaveShareMemory() )
		return 1;

	printf("��ӹ����ڴ濪ʼ\r\n");

	AllocShare(nAllocType);

	if( !IsHaveShareMemory() )
		return 0;

	_delObject(m_mapShareMemName);

	m_mapShareMemName = new CYlsMapStringToPtr;

	m_mapShareMemName->SetAt(m_SHFileNowName,	m_Memory_real		);		// ʵʱ����
	m_mapShareMemName->SetAt(m_SHFileTraName,	m_Memory_tick		);		// �ֱ�����
	m_mapShareMemName->SetAt(m_SHFileInfoName,	m_Memory_bourseinfo	);		// ������Ϣ����
	m_mapShareMemName->SetAt(m_SHFileHisName,	m_Memory_trend		);		// ��������
	m_mapShareMemName->SetAt(m_SHFileCodeInfo,	m_Memory_stockinfo	);		// ������Ϣ
	m_mapShareMemName->SetAt(m_strFileCodeList,	m_Memory_initinfo	);		// ��ʼ������
	m_mapShareMemName->SetAt(m_strFileOtherData, m_Memory_other		);		// ��������

	m_mapShareMemName->SetAt(m_name_StockCounts,	m_Memory_stockCount	);		// ����share

	m_mapShareMemName->SetAt(m_name_param,	    m_Memory_param		);
	m_mapShareMemName->SetAt(m_name_mark,		m_Memory_mark		);		// ���ͱ�־����
	m_mapShareMemName->SetAt(m_name_real,		m_Memory_real		);		// ʵʱ����
	m_mapShareMemName->SetAt(m_name_tick,		m_Memory_tick		);		// �ֱ�����
	m_mapShareMemName->SetAt(m_name_bourseinfo,	m_Memory_bourseinfo	);		// ������Ϣ����
	m_mapShareMemName->SetAt(m_name_trend,		m_Memory_trend		);		// ��������
	m_mapShareMemName->SetAt(m_name_stockinfo,	m_Memory_stockinfo	);		// ������Ϣ
	m_mapShareMemName->SetAt(m_name_initinfo,	m_Memory_initinfo	);		// ��ʼ������
	m_mapShareMemName->SetAt(m_name_other,		m_Memory_other		);		// ��������

	// ���ñ����ļ���Ϣ
	SetMemToDiskFile();

	printf("��ӹ����ڴ����\r\n");

	return 1;
}

void HSServerDataPath::CreateEmptyFile(const char* szFileName)
{
	int ll = 123;
	CYlsFile* pFile = ssfsopen(szFileName,Yls_Create_Open,1);
	if( pFile )
	{
		pFile->Write(&ll,sizeof(int));
		pFile->SetLength(0);
		CLOSE_FILE(pFile);
	}
	else
	{
		pFile = ssfsopen(szFileName,Yls_Read_Open,1);
		if( pFile )
		{
			pFile->Write(&ll,sizeof(int));
			pFile->SetLength(0);
			CLOSE_FILE(pFile);
		}
	}
}

void HSServerDataPath::RemoveFile(const char* szFileName)
{
	int nCount = 10;
	while(nCount--)
	{
		if( access(szFileName,0) == 0 )
		{
			remove(szFileName);
			YlsSleep(100);
		}
		else
		{
			break;
		}
	}
}

CSharedMemory* HSServerDataPath::GetMemShareName(const char* szFileName)
{
	if( m_mapShareMemName == NULL || szFileName == NULL )
		return NULL;

	CSharedMemory* pShareName;
	if( m_mapShareMemName->Lookup(szFileName,(void*&)pShareName) )
		return pShareName;

	return NULL;
}

void HSServerDataPath::SetZiXun(const char* strBasePath)
{
	strncpy(m_strInfoBasePath ,strBasePath,sizeof(m_strInfoBasePath));
	MakeValidPath(m_strInfoBasePath);
}

void HSServerDataPath::SetPanhouPath(const char* strBasePath,BOOL bOther /*= FALSE*/)
{
	strncpy(m_strDayBasePath ,strBasePath,sizeof(m_strDayBasePath));
	MakeValidPath(m_strDayBasePath);

	char szRet[_MAX_PATH];
	sprintf(m_strFileTend,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"tend",Yls_Path_Spl);
	CreatPath(m_strFileTend);

	//YlsPrompt("SetPanhouPath",m_strFileTend);

	// ���������
	sprintf(m_strFileMin1,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"min1",Yls_Path_Spl);
	CreatPath(m_strFileMin1);

	sprintf(m_strFileMin,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"min",Yls_Path_Spl);
	CreatPath(m_strFileMin);

	sprintf(m_strFileMin15,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"min15",Yls_Path_Spl);
	CreatPath(m_strFileMin15);

	sprintf(m_strFileMin30,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"min30",Yls_Path_Spl);
	CreatPath(m_strFileMin30);

	sprintf(m_strFileMin60,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"min60",Yls_Path_Spl);
	CreatPath(m_strFileMin60);

	sprintf(m_strFileMin120,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"min120",Yls_Path_Spl);
	CreatPath(m_strFileMin120);


	// ���������й�
	sprintf(m_strFileDay,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"day",Yls_Path_Spl);
	CreatPath(m_strFileDay);

	sprintf(m_strFileWeek,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"week",Yls_Path_Spl);
	CreatPath(m_strFileWeek);

	sprintf(m_strFileMonth,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"month",Yls_Path_Spl);
	CreatPath(m_strFileMonth);

	sprintf(m_strFileSeason,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"season",Yls_Path_Spl);
	CreatPath(m_strFileSeason);

	sprintf(m_strFileYear,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"year",Yls_Path_Spl);
	CreatPath(m_strFileYear);


	//
	sprintf(m_strHisFileTrace,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"Trace",Yls_Path_Spl);
	CreatPath(m_strHisFileTrace);
	
	sprintf(m_strHKQiQuan,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"QiQuan",Yls_Path_Spl);
	CreatPath(m_strHKQiQuan);
	
	sprintf(m_strETFFileDay,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"ETF",Yls_Path_Spl);
	CreatPath(m_strETFFileDay);

	sprintf(m_strOrderQueue,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"OrderQueue",Yls_Path_Spl);
	CreatPath(m_strOrderQueue);

	sprintf(m_strLargeTick,"%s%s%s%s%s",m_strDayBasePath,GetMarketName(szRet,sizeof(szRet)),Yls_Path_Spl,"LargeTick",Yls_Path_Spl);
	CreatPath(m_strLargeTick);

}

BOOL HSServerDataPath::GetPanHouPath(int nPeriod,char* strDayFile,char* strSuffix)
{
	switch(nPeriod)
	{
	case PERIOD_TYPE_MINUTE1:
		strcpy(strDayFile,m_strFileMin1);
		strcpy(strSuffix, ".nmn");
		break;
	case PERIOD_TYPE_MINUTE5:
	case PERIOD_TYPE_MINUTE15:
	case MINUTE30:
	case MINUTE60:
	case PERIOD_TYPE_MINUTE120:
			strcpy(strDayFile,m_strFileMin);
			strcpy(strSuffix, ".nmn");
		break;
	case PERIOD_TYPE_DAY:
	case HISDAY:
	case WEEK:
	case MONTH:
	case PERIOD_TYPE_DAY_ANY:
			strcpy(strDayFile,m_strFileDay);
			strcpy(strSuffix, ".day");
		break;
		//case WEEK:
		//	strcpy(strDayFile,m_strFileWeek);
		//	strcpy(strSuffix, ".wek");
		//	break;
		//case MONTH:
		//	strcpy(strDayFile,m_strFileDay);
		//	strcpy(strSuffix, ".mnt");
		//	break;
	case RT_HISTREND_INDEX:
	case RT_HISTREND:
		strcpy(strDayFile,m_strFileTend);
		strcpy(strSuffix, ".ten");
		break;
	case RT_MAJORINDEXTICK:
		strcpy(strDayFile,m_strHisFileTrace);
		strcpy(strSuffix, ".tri");
		break;
	case RT_HK_RECORDOPTION:
		strcpy(strDayFile,m_strHKQiQuan);
		strcpy(strSuffix, ".qiq");
		break;
	case RT_HISTORYTICK:
		strcpy(strDayFile,m_strHisFileTrace);
		strcpy(strSuffix, ".tra");
		break;
	case RT_ETF_TREND:
		strcpy(strDayFile,m_strETFFileDay);
		strcpy(strSuffix, ".etf");
		break;
	case RT_ETF_TREND_CFG:
		strcpy(strDayFile,m_strETFFileDay);
		strcpy(strSuffix, ".cfg");
		break;

	case RT_Level_OrderQueue:
		strcpy(strDayFile,m_strOrderQueue);
		strcpy(strSuffix, ".OrQ");
		break;
	case RT_Level_LargeTick:
		strcpy(strDayFile,m_strLargeTick);
		strcpy(strSuffix, ".Ltk");
		break;

	default:
		strDayFile[0] = '\0';
		return FALSE;
	}

	return TRUE;
}

BOOL HSServerDataPath::GetPanHouPath(int nPeriod,char* strDayFile,char* strSuffix,ReqDayData* pReqDayData)
{
	switch(nPeriod)
	{
	case PERIOD_TYPE_MINUTE1:
		strcpy(strDayFile,m_strFileMin1);
		strcpy(strSuffix, ".nmn");
		break;
	case PERIOD_TYPE_MINUTE5:
	case PERIOD_TYPE_MINUTE15:
	case MINUTE30:
	case MINUTE60:
	case PERIOD_TYPE_MINUTE120:
		if( pReqDayData )
		{
			switch(pReqDayData->m_nPeriodNum)
			{
			case 3  :  strcpy(strDayFile,m_strFileMin15);   strcpy(strSuffix, ".15"); strSuffix  = ".15";   break; // 15����
			case 6  :  strcpy(strDayFile,m_strFileMin30);   strcpy(strSuffix, ".30"); strSuffix  = ".30";   break; // 30����
			case 12 :  strcpy(strDayFile,m_strFileMin60);   strcpy(strSuffix, ".60"); strSuffix  = ".60";   break; // 60����
			case 24 :  strcpy(strDayFile,m_strFileMin120);  strcpy(strSuffix, ".120"); strSuffix = ".120"; break; // 120����
			default:   strcpy(strDayFile,m_strFileMin);     strcpy(strSuffix, ".nmn"); strSuffix = ".nmn"; break; // 5����
			}
		}
		else
		{
			strcpy(strDayFile,m_strFileMin);
			strcpy(strSuffix, ".nmn");
		}
		break;
	case PERIOD_TYPE_DAY:
	case HISDAY:
	case WEEK:
	case MONTH:
	case PERIOD_TYPE_DAY_ANY:
		if( pReqDayData )
		{
			switch(pReqDayData->m_nPeriodNum)
			{				
			case 7  :  strcpy(strDayFile,m_strFileWeek);   strcpy(strSuffix, ".wek");   break; // ����
			case 30 :  strcpy(strDayFile,m_strFileMonth);  strcpy(strSuffix, ".mnt");  break; // ����
			case 90 :  strcpy(strDayFile,m_strFileSeason); strcpy(strSuffix, ".season"); break; // ����
			case 360 : strcpy(strDayFile,m_strFileYear);   strcpy(strSuffix, ".year");   break; // ����
			default:   strcpy(strDayFile,m_strFileDay);    strcpy(strSuffix, ".day");    break; // ����
			}			
		}
		else
		{
			strcpy(strDayFile,m_strFileDay);
			strcpy(strSuffix, ".day");
		}
		break;
	//case WEEK:
	//	strcpy(strDayFile,m_strFileWeek);
	//	strcpy(strSuffix, ".wek");
	//	break;
	//case MONTH:
	//	strcpy(strDayFile,m_strFileDay);
	//	strcpy(strSuffix, ".mnt");
	//	break;
	case RT_HISTREND_INDEX:
	case RT_HISTREND:
		strcpy(strDayFile,m_strFileTend);
		strcpy(strSuffix, ".ten");
		break;
	case RT_MAJORINDEXTICK:
		strcpy(strDayFile,m_strHisFileTrace);
		strcpy(strSuffix, ".tri");
		break;
	case RT_HK_RECORDOPTION:
		strcpy(strDayFile,m_strHKQiQuan);
		strcpy(strSuffix, ".qiq");
		break;
	case RT_HISTORYTICK:
		strcpy(strDayFile,m_strHisFileTrace);
		strcpy(strSuffix, ".tra");
		break;
	case RT_ETF_TREND:
		strcpy(strDayFile,m_strETFFileDay);
		strcpy(strSuffix, ".etf");
		break;
	case RT_ETF_TREND_CFG:
		strcpy(strDayFile,m_strETFFileDay);
		strcpy(strSuffix, ".cfg");
		break;

	case RT_Level_OrderQueue:
		strcpy(strDayFile,m_strOrderQueue);
		strcpy(strSuffix, ".OrQ");
		break;
	case RT_Level_LargeTick:
		strcpy(strDayFile,m_strLargeTick);
		strcpy(strSuffix, ".Ltk");
		break;
	
	default:
		strDayFile[0] = '\0';
		return FALSE;
	}

	return TRUE;
}

int HSServerDataPath::WriteShareData(MemShareDataSave& mem)
{
#ifdef HS_SUPPORT_UNIX
#else
	CYlsFile* pFile = ssfsopen(m_strShareData,Yls_Create_NoTruncate_Open,1);
	if( pFile )
	{
		memcpy(&m_sMemShareDataSave,&mem,sizeof(mem));
		pFile->Write(&m_sMemShareDataSave,sizeof(m_sMemShareDataSave));
		CLOSE_FILE(pFile);
		return TRUE;
	}
#endif
	return 0;
}

int HSServerDataPath::ReadShareData(int nDefault)
{
#ifdef HS_SUPPORT_UNIX
#else
	CYlsFile* pFile = ssfsopen(m_strShareData,Yls_OnlyRead_Open,1);
	if( pFile )
	{
		pFile->SeekToBegin();
		if( pFile->Read(&m_sMemShareDataSave,sizeof(m_sMemShareDataSave)) != sizeof(m_sMemShareDataSave) )
		{
			m_sMemShareDataSave.m_nTicks = nDefault;
		}

		CLOSE_FILE(pFile);
		return TRUE;
	}

	m_sMemShareDataSave.m_nTicks = nDefault;
#endif
	return 0;
}

void HSServerDataPath::RemoveShareData()
{
#ifdef HS_SUPPORT_UNIX
#else
	CYlsFile* pFile = ssfsopen(m_strShareData,Yls_Read_Open,1);
	if( pFile )
	{
		pFile->SetLength(0);
		CLOSE_FILE(pFile);
	}
#endif
}

int	HSServerDataPath::IsHaveBeginFillData(int nMask /*= 0*/)
{
	return ( access(m_strFillDataBegin,0) == 0 );
}

int	HSServerDataPath::IsHaveEndFillData(int nMask /*= 0*/)
{
	return ( access(m_strFillDataEnd,0) == 0 );
}

const char* YlsGetCurrentExeBasePath()
{
	static CHqDataBuffer strCurrentPath;

	if( !strCurrentPath.IsValid() )
	{
		strCurrentPath.Alloc(_MAX_PATH);

#ifdef HS_SUPPORT_UNIX

		char* pp = (char*)strCurrentPath.m_lpszBuffer;
		getcwd(pp, _MAX_PATH);
		strcat(pp,"/");

		YlsPrompt("��ǰ·��",pp);
#else
		GetModuleFileName( AfxGetInstanceHandle(),
			(char*)strCurrentPath.m_lpszBuffer, _MAX_PATH );

		//char path_buffer[_MAX_PATH];
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];

		_splitpath( strCurrentPath.m_lpszBuffer, drive, dir, NULL, NULL );
		char* pp = (char*)strCurrentPath.m_lpszBuffer;

		sprintf(pp,"%s%s",drive,dir);
#endif

	}

	return (char*)strCurrentPath.m_lpszBuffer;
}


char* GetPathByMarkType(char* szName,HSMarketDataType nMarket)
{
	memset(szName,0,sizeof(szName));
	switch(MakeMarket(nMarket))
	{
	case STOCK_MARKET			 : // ��Ʊ
		strcpy(szName,"HQ");
		break;
	case HK_MARKET				 : // �۹ɷ���
		strcpy(szName,"GG");
		break;
	case FUTURES_MARKET			 : // �ڻ�
		strcpy(szName,"QH");
		break;
	case FOREIGN_MARKET			 : // ���
		strcpy(szName,"WH");
		break;
	}

	return szName;
}




char* CHSFilePath::GetPath(char* strPath,
						   char cType,
						   HSMarketDataType nMarket /*= 0*/,
						   char* szFileName /*= NULL*/)
{
	memset(strPath,0,sizeof(strPath));

	//char szName[100];

	switch(cType)
	{
	case Srv_BlockUserStock:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"BLOCK",Yls_Path_Spl);
		break;
	case Srv_Setting:
		sprintf(strPath,"%s%s",YlsGetCurrentExeBasePath(),g_strSettingPath);//GetSettingPath());
		break;	
	case Srv_Setting_File:		   // LPTSTR 
		{
			sprintf(strPath,"%s%s",YlsGetCurrentExeBasePath(),g_strSettingPath);//GetSettingPath());//Srv_Setting_str);
			if (access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}
			if( szFileName )
				strcat(strPath,szFileName);
			else
				strcat(strPath,g_strCfgfileName);//"hqserver.ini");

			return strPath;
		}
		break;
	case Srv_Dynamic_File:
		{
			sprintf(strPath,"%s%s",YlsGetCurrentExeBasePath(),g_strSettingPath);
			if (access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}
			if( szFileName )
				strcat(strPath,szFileName);
			else
				strcat(strPath,g_strCfgDynamic);

			return strPath;
		}
		break;
	case SrvTotalPath:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"SrvTotalPath",Yls_Path_Spl);
		}
		break;
	case SendShare_Setting:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"SendShare_Setting",Yls_Path_Spl);
		}
		break;
	case Srv_Config:			// web��Ŀ¼
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"webbase",Yls_Path_Spl);
		}
		break;
	case Srv_Gif:				// gif�ļ�Ŀ¼
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"GIF",Yls_Path_Spl);
		}
		break;
	case Srv_DFxPath:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"DFXPATH",Yls_Path_Spl);
		}
		break;
	case Srv_AcceptFilePath:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"ACCEPTFILEPATH",Yls_Path_Spl);
		break;
	case GG_CurDateAcceptData:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"TODAY",Yls_Path_Spl);
		break;
	case Srv_FinancialData:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(), "FINANCIALDATA",Yls_Path_Spl);
		break;
	case Srv_ClientFileUpdate:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(), "FILEUPDATE",Yls_Path_Spl); // �ͻ��˳���
		break;
	case Srv_UserManagerDBF:
/*#ifndef HS_SUPPORT_UNIX
		sprintf(strPath,"%s%s%s","C:\\", "USERMANAGERDBF",Yls_Path_Spl);
#else*/
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(), "USERMANAGERDBF",Yls_Path_Spl);
//#endif
		break;
	case Srv_UserConfig:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(), "USERMANAGERDBF",Yls_Path_Spl);
			if (access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}
			sprintf(strPath,"%s%s%s%s%s",YlsGetCurrentExeBasePath(), "USERMANAGERDBF",Yls_Path_Spl,"USERCONFIG",Yls_Path_Spl);
		}
		break;
	case Srv_sysInfoData:
		{
#ifndef HS_SUPPORT_UNIX
			char strCurrentPath[_MAX_PATH];
			GetModuleFileName( AfxGetInstanceHandle(),
				strCurrentPath, _MAX_PATH );

			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];

			_splitpath( strCurrentPath, NULL, NULL, fname, ext );
			
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(), "SYSINFODATA",Yls_Path_Spl);
			if (_access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}

			sprintf(strPath,"%s%s%s%s.dat",YlsGetCurrentExeBasePath(), "SYSINFODATA",Yls_Path_Spl,fname);

			return strPath;
#endif
		}
		break;

		// for reciev
	case SaveInit:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(), "SAVEINIT",Yls_Path_Spl);
		break;
	case RunLog:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(), "RUNLOG",Yls_Path_Spl);
		break;
	case RunLog_Temp:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(), "RunLog_Temp",Yls_Path_Spl);
		break;

	case DBF_Setting:
		sprintf(strPath,"%s%s",YlsGetCurrentExeBasePath(),receive_Setting_str);//GetSettingPath());
		break;

		// for send
	case UserReportData:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"�˹���������",Yls_Path_Spl);
			if (access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}
			sprintf(strPath,"%s%s%s%s",YlsGetCurrentExeBasePath(), "�˹���������",Yls_Path_Spl,"�˹���������.cfg");

			return strPath;		
		}
		break;
	case MappingPath:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"MappingPath",Yls_Path_Spl);
			if (access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}
			sprintf(strPath,"%s%s%s%s",YlsGetCurrentExeBasePath(), "MappingPath",Yls_Path_Spl,"Mapping.dat");

			return strPath;		
		}
		break;
	case CodeFile:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"CODEFILE",Yls_Path_Spl);
		break;
	case LanguagePath:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"LanguagePath",Yls_Path_Spl);
		break;
	case MarketFile:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"MARKETFILE",Yls_Path_Spl);

#ifdef Support_JiaoHang_AutoEvery
#else
			if (access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}
			strcat(strPath,g_strCfgShortName);
			strcat(strPath,Yls_Path_Spl);
			if (access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}
#endif
			return strPath;
		}
		break;
	case ZX_Setting:
		sprintf(strPath,"%s%s%s%s",YlsGetCurrentExeBasePath(),ZX_Setting_str,g_strCfgfileName,Yls_Path_Spl);
		break;
	case ZX_Setting_File:
		{
			sprintf(strPath,"%s%s%s%s",YlsGetCurrentExeBasePath(),ZX_Setting_str,g_strCfgfileName,Yls_Path_Spl);
			CreatPath(strPath);

			strcat(strPath,ZX_Setting_FileName);

			return strPath;
		}
		break;
	case GG_CurDateData:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"GG_CurDateData",Yls_Path_Spl);
		break;
	case GG_StockUnion:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"GG_StockUnion",Yls_Path_Spl);
		break;
	case GG_StockList:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"GG_StockIndexList",Yls_Path_Spl);
		break;
	case GP_StockList:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"StockIndexList",Yls_Path_Spl);
		break;
	case GP_IndexDataFile:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"IndexDataFile",Yls_Path_Spl);
			if (access(strPath, 0) != 0)
			{
				Yls_mkdir(strPath);
			}
			sprintf(strPath,"%s%s%s%s",YlsGetCurrentExeBasePath(), "IndexDataFile",Yls_Path_Spl,"IndexDataFile.dat");

			return strPath;
		}
		break;
	case BackupData:
		{
			CYlsTime tm = CYlsTime::GetCurrentTime();

			sprintf(strPath,"%s%s%s%02d%s",YlsGetCurrentExeBasePath(),"BACKUPDATA",Yls_Path_Spl,
				tm.GetDayOfWeek(),Yls_Path_Spl);

			CreatPath(strPath);

			return strPath;
		}
		break;
	case Dfx_WGT_Path:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"DFX_WEIGHT",Yls_Path_Spl);
		}
		break;
	case Srv_ExterDll:
		{
			sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"externDll",Yls_Path_Spl);
		}
		break;
	default:
		sprintf(strPath,"%s%s%s",YlsGetCurrentExeBasePath(),"DEFAULT",Yls_Path_Spl);
		break;
	}

	if (access(strPath, 0) != 0)
	{
		Yls_mkdir(strPath);
	}

	return strPath;
}

BOOL CreatPath(const char* strBasePath,BOOL bList /*= TRUE*/)
{
	if( access(strBasePath,0) == 0 )
		return TRUE;

	if( bList )
	{
		const char* strDelimit = Yls_Path_Spl;//"\\";
		char strCur[_MAX_PATH];
		memset(strCur,0,sizeof(strCur));
		sprintf(strCur,"%s",strBasePath);

		//YlsPrompt("CreatPath",strCur);

		int nRet;

		char tmp[_MAX_PATH];
		char tmp1[_MAX_PATH];
		memset(tmp1,0,sizeof(tmp1));

#ifdef HS_SUPPORT_UNIX
		strcat(tmp1,Yls_Path_Spl);
#endif

		char* token = strtok( strCur, strDelimit );
		while(token != NULL)
		{
			sprintf(tmp,"%s",token);
			token = strtok( NULL, strDelimit);

			//
			strcat(tmp1,tmp);

			//YlsPrompt("tmp1:",tmp1);

			if( access(tmp1,0) == -1 )
			{
			   nRet = Yls_mkdir( tmp1 );
			   if( nRet < 0 )
			   {
				   return FALSE;
			   }
			}
			strcat(tmp1,Yls_Path_Spl);//"\\");
		}
	}
	else
	{
		Yls_mkdir( strBasePath );
	}

	return TRUE;
}

long GetSizeByMask(long lMask)
{
	long lLen = 0;
	long lCurMask;
	for( int i = 0; i < 32; i++ )
	{
		lCurMask = ( 1 << i );

		// ����
		if( lMask & MASK_REALTIME_DATA_CODEINFO )
		{
			lLen += sizeof(CodeInfo);
		}
		else if( lMask & lCurMask )
		{
			lLen += sizeof(long);
		}
	}

	return lLen;
}

int YlsGetFileMarkInfo(TextMarkData* pMarkData,const char* strFileName)
{
	if( pMarkData == NULL )
		return 0;

	if( access(strFileName,0) != 0 )
		return 0;

	struct stat stBuff;
	if( stat(strFileName, &stBuff) != 0 )
	{
		return 0;
	}

	/*CFileStatus rStatus;
	if( !CFile::GetStatus( strFileName, rStatus ) )
		return 0;*/

	pMarkData->m_lCRC = stBuff.st_mtime;//rStatus.m_mtime.GetTime();
	pMarkData->m_lBeginPos = 0;
	pMarkData->m_lEndPos   = stBuff.st_size;//rStatus.m_size;

	return 1;
}
