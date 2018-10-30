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
#include "usermanager.h"
#include "globalfun.h"
#include "hsserverdatapath.h"

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <math.h>
#include <sys\stat.h>

BOOL User_Info::IsPWD(int nOption,const char* szPwd)
{
	if( password.m_lpszBuffer == NULL )
		return FALSE;

	char szRet[64];
	memset(szRet,0,sizeof(szRet));
	return (MakeSerial(nOption,szRet,password.m_lpszBuffer) &&
			!strncmp(szRet,szPwd,64));

//	CHSDes HSDes;
//	CString strPwd = HSDes.MakeSerial(password.m_lpszBuffer);

	//return !strPwd.Compare(szPwd);
}

int User_Info::IsExpire()
{
	if( !validdate.IsValid() )
		return (0 - 999999);

	CTime tm = CTime::GetCurrentTime();
	long lDate = atol(validdate.m_lpszBuffer);

	CTime tm1 = CTime(lDate/10000,lDate%10000/100,lDate%10000%100,0,0,0);

	CTimeSpan span = tm1 - tm;

	return ( span.GetDays() );

	/*CTime tm = CTime::GetCurrentTime();
	char szTime[128];
	sprintf(szTime,"%04d%02d%02d",tm.GetYear(),tm.GetMonth(),tm.GetDay());

	return (atol(validdate.m_lpszBuffer) < atol(szTime));*/
}

BOOL User_Info::IsMaxLogin(AskData *pAsk,CSessionInfo* pSessionInfo)
{
	if( pAsk->m_nType & RT_JAVA_MARK )
		return FALSE;

	pSessionInfo->m_nMarketType = pAsk->m_nType;

	switch( (pSessionInfo->m_nMarketType & (~RT_JAVA_MARK)) )
	{
	case RT_LOGIN							:		
		if( viewgp == 0 )
			return 0;

		viewgp_max++;
		if( viewgp_max > viewgp )
		{
			viewgp_max = viewgp+1;
			return 1;
		}

		return ( viewgp_max > viewgp );
	case RT_LOGIN_HK						:	/* 客户端登录港股服务器				*/
		if( viewgg == 0 )
			return 0;

		viewgg_max++;
		if( viewgg_max > viewgg )
		{
			viewgg_max = viewgg+1;
			return 1;
		}

		return ( viewgg_max > viewgg );
	case RT_LOGIN_FUTURES					:	/* 客户端登录期货服务器				*/
		if( viewqh == 0 )
			return 0;

		viewqh_max++;
		if( viewqh_max > viewqh )
		{
			viewqh_max = viewqh+1;
			return 1;
		}

		return ( viewqh_max > viewqh );
	case RT_LOGIN_FOREIGN					:	/* 客户端登录外汇服务器				*/
		if( viewwh == 0 )
			return 0;

		viewwh_max++;
		if( viewwh_max > viewwh )
		{
			viewwh_max = viewwh+1;
			return 1;
		}

		return ( viewwh_max > viewwh );
	case RT_LOGIN_WP						:	/* 客户端登录外盘服务器				*/
		if( viewwp == 0 )
			return 0;

		viewwp_max++;
		if( viewwp_max > viewwp )
		{
			viewwp_max = viewwp+1;
			return 1;
		}

		return ( viewwp_max > viewwp );
	case RT_LOGIN_HJ						:	/* 客户端登录黄金服务器				*/
		if( viewhj == 0 )
			return 0;

		viewhj_max++;
		if( viewhj_max > viewhj )
		{
			viewhj_max = viewhj+1;
			return 1;
		}

		return ( viewhj_max > viewhj );
	}

	return FALSE;
}

BOOL User_Info::ExitLogin(CSessionInfo* pSessionInfo)
{
	if( pSessionInfo->m_nMarketType & RT_JAVA_MARK )
		return FALSE;

	switch( (pSessionInfo->m_nMarketType & (~RT_JAVA_MARK)) )
	{
	case RT_LOGIN							:		
		viewgp_max--;
		if( viewgp_max < 0 )
			viewgp_max = 0;
		break;
	case RT_LOGIN_HK						:	/* 客户端登录港股服务器				*/
		viewgg_max--;
		if( viewgg_max < 0 )
			viewgg_max = 0;		
		break;
	case RT_LOGIN_FUTURES					:	/* 客户端登录期货服务器				*/
		viewqh_max--;
		if( viewqh_max < 0 )
			viewqh_max = 0;		
		break;
	case RT_LOGIN_FOREIGN					:	/* 客户端登录外汇服务器				*/
		viewwh_max--;
		if( viewwh_max < 0 )
			viewwh_max = 0;		
		break;
	case RT_LOGIN_WP						:	/* 客户端登录外盘服务器				*/
		viewwp_max--;
		if( viewwp_max < 0 )
			viewwp_max = 0;		
		break;
	case RT_LOGIN_HJ						:	/* 客户端登录黄金服务器				*/
		viewhj_max--;
		if( viewhj_max < 0 )
			viewhj_max = 0;		
		break;
	}

	return 1;
}

BOOL User_Info::GetCFGPath(CSessionInfo* pSessionInfo)
{
	if( pSessionInfo == NULL )
		return FALSE;

	pSessionInfo->m_strUserCfg[0] = '\0';

	if( !usercfg.IsValid() )
		return FALSE;

	strncpy(pSessionInfo->m_strUserCfg,usercfg.m_lpszBuffer,sizeof(pSessionInfo->m_strUserCfg));

	/*char strPath[256];
	CHSFilePath::GetPath(strPath,CHSFilePath::UserConfig);
	sprintf(pSessionInfo->m_strUserCfg,"%s%s",strPath,usercfg.m_lpszBuffer);
	if( access(pSessionInfo->m_strUserCfg,0) != 0 )
	{
		pSessionInfo->m_strUserCfg[0] = '\0';
		return FALSE;
	}*/

	return TRUE;
}

void User_Info::Copy(User_Info* pInfo)
{
	userid.Copy(&pInfo->userid);
	username.Copy(&pInfo->username);
	password.Copy(&pInfo->password);
	groupname.Copy(&pInfo->groupname);
	area.Copy(&pInfo->area);

	notlogin = pInfo->notlogin; // =0验证用户密码；=1超级用户；=2用户不能够修改密码

 	validdate.Copy(&pInfo->validdate);

	viewnews = pInfo->viewnews;

	viewgp = pInfo->viewgp;
	viewqh = pInfo->viewqh;
	viewwp = pInfo->viewwp;
	viewwh = pInfo->viewwh;
	viewgg = pInfo->viewgg;
	viewhj = pInfo->viewhj;

	userlevel = pInfo->userlevel;

	viewgp_max = pInfo->viewgp_max;
	viewqh_max = pInfo->viewqh_max;
	viewwp_max = pInfo->viewwp_max;
	viewwh_max = pInfo->viewwh_max;
	viewgg_max = pInfo->viewgg_max;
	viewhj_max = pInfo->viewhj_max;

	memo.Copy(&pInfo->memo);
	usercfg.Copy(&pInfo->usercfg);

	begintime = pInfo->begintime;
	endtime = pInfo->endtime;
	usedtotaltime = pInfo->usedtotaltime;
}

// 用户管理列表
CYlsMapStringToPtr g_mapUserList;
User_Info* User_Info::GetUserInfo(const char* pUserKey)
{
	char* pUser = _strlwr(_strdup(pUserKey));

	YlsAllTrim(pUser);

	User_Info* pUser_Info = NULL;
	if( g_mapUserList.Lookup(pUser,(void*&)pUser_Info) )
	{
		free(pUser);
		return pUser_Info;
	}

	free(pUser);
	return NULL;
}

int User_Info::InitUserInfoList()
{
	if( g_db == NULL )
		return 0;

	const char* key = NULL;
	User_Info* value = NULL;
	::YlsMapDelAll(g_mapUserList,key,(void*&)value);
	int nRet = g_db->GetAllUserInfo(g_mapUserList);

	g_db->Close();


	//
	//User_Info::LoadCheckUserFile();

	return nRet;
}

int User_Info::LoadCheckUserFile(CYlsMapStringToPtr* mapbdzpass,CYlsMapStringToPtr* mapbdzaddr)
{

	return 0;
}

int User_Info::Loadbdzpass(char* szsbdzpass,
						   CYlsMapStringToPtr* mapbdzpass,
						   CYlsMapStringToPtr* mapbdzaddr)
{
	return 0;
}

void User_Info::Free(CYlsMapStringToPtr& mapbdzpass,CYlsMapStringToPtr& mapbdzaddr)
{
	const char* pkey = NULL;
	FileUserInfo* value = NULL;
	POSITION  pos;
	for( pos = mapbdzpass.GetStartPosition(); pos != NULL; )
	{
		mapbdzpass.GetNextAssoc( pos, pkey, (void*&)value );
		if( value )
		{
			delete value;
		}
	}
	mapbdzpass.RemoveAll();

	CHqDataBuffer* value2;
	for( pos = mapbdzaddr.GetStartPosition(); pos != NULL; )
	{
		mapbdzaddr.GetNextAssoc( pos, pkey, (void*&)value2 );
		if( value )
		{
			delete value2;
		}
	}
	mapbdzaddr.RemoveAll();
}

char* User_Info::Getbdzpass(const char* szKey,CHqDataBuffer& buffer,CHqDataBuffer& PathBuffer)
{
	
	return 0;
}

int User_Info::Loadbdzaddr(char* szsbdzaddr,CYlsMapStringToPtr* mapbdzaddr)
{
	
	return 0;
}

char* User_Info::Getbdzaddr(const char* szKey,
							CHqDataBuffer& buffer,
							CYlsMapStringToPtr* mapbdzaddr)
{
	return NULL;
}

void User_Info::Writebdzpass(CHqDataBuffer& buffer,const char* szIP)
{
}

int	User_Info::CheckHltpass(const char* szKey,CHqDataBuffer& NameBuffer,CHqDataBuffer& DateBuffer)
{
	return 0;
}


_ConnectionPtr OpenDBase::m_pCnn = NULL;
struct stat    OpenDBase::m_stPre;
char	       OpenDBase::m_strCnnFile[256];


OpenDBase::OpenDBase()
{
	char strPath[256];
	CHSFilePath::GetPath(strPath,Srv_UserManagerDBF);
	sprintf(m_strCnnFile,"%sAgileReader.mdb",strPath);

	GetFileNameStat(m_stPre,m_strCnnFile);
}

void OpenDBase::Close()
{
	if( m_pCnn != NULL )
	{
		try
		{
			m_pCnn->Close();
			m_pCnn.Release();
		}
		catch( _com_error& e )
		{
			ErrorOutput0("OpenDBase::Close");
		}
	}
}

_ConnectionPtr OpenDBase::GetCnn()
{
	if( m_pCnn != NULL )
		return m_pCnn;

	//::CoInitialize(NULL);

	if(FAILED(::CoInitialize(NULL)))
	{
		AfxMessageBox(_T("初始化COM失败！"));
		return m_pCnn;
	}


	//char strPath[256];
	//CHSFilePath::GetPath(strPath,Srv_UserManagerDBF);
	//sprintf(strCnn,"%sAgileReader.mdb",strPath);
	if( access(m_strCnnFile,0) != 0 )
		return NULL;

	m_pCnn.CreateInstance( __uuidof( Connection ) );
	if ( m_pCnn == NULL )
	{
		//AfxMessageBox( _T("Can not create connection object, please install MDAC!") );
		return NULL;
	}

	try
	{		
		char strCnn[256];
		sprintf(strCnn, _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Jet OLEDB:Database Password=philips;"),
			m_strCnnFile );
		m_pCnn->Open( _bstr_t(strCnn), "", "", adConnectUnspecified);//adAsyncConnect);// | adConnectUnspecified);//adAsyncConnect);
		//m_pCnn->Close();

	}
	catch( _com_error& e )
	{
		//AfxMessageBox( _T("Can not open connection:\n") + GetComError( e ) );

		CString str	= _T("Can not open connection:\n") + GetComError( e );
		ErrorOutput((void*)(const char*)str,str.GetLength());

		m_pCnn.Release();
		return NULL;
	}

	return m_pCnn;
}

BOOL OpenDBase::IsChange()
{
	struct stat stCur;
	if( GetFileNameStat(stCur,m_strCnnFile) )
	{
		if(m_stPre.st_size != stCur.st_size)
		{
			memcpy(&m_stPre,&stCur,sizeof(stCur));
			return TRUE;
		}
	}

	return FALSE;
}

BOOL OpenDBase::GetFieldValue(FieldsPtr fields, long nIndex,CStringBuffer& buffer)
{
	_variant_t vt = fields->GetItem( nIndex )->Value;
	if ( vt.vt == VT_NULL || vt.vt == VT_EMPTY )
	{
		//throw 0;
		//char szError[255];
		//sprintf(szError,"0:GetFieldValue(FieldsPtr fields, long nIndex,CStringBuffer& buffer) %i",nIndex);
		//ErrorOutput(szError,strlen(szError));
		return 0;
	}

	buffer = (const char*)_bstr_t( vt );

	return 1;
}

BOOL OpenDBase::GetFieldValue(FieldsPtr fields, long nIndex,int& buffer)
{
	buffer = 0;

	_variant_t vt = fields->GetItem( nIndex )->Value;
	if ( vt.vt == VT_NULL || vt.vt == VT_EMPTY )
	{
		//char szError[255];
		//sprintf(szError,"1:GetFieldValue(FieldsPtr fields, long nIndex,int& buffer) %i",nIndex);
		//ErrorOutput(szError,strlen(szError));//"意外:GetFieldValue(FieldsPtr fields, long nIndex,int& buffer)");
		return 0;
	}

	buffer = atol((const char*)_bstr_t( vt ));

	return 1;
}

BOOL OpenDBase::ExecuteSQL(_ConnectionPtr &pCnn, const char* strSQL)
{
	if( pCnn == NULL )
		return FALSE;

	try
	{
		pCnn->Execute( _bstr_t( strSQL ), NULL, adCmdText );
	}
	catch( _com_error& e )
	{
		//strMsg = GetComError( e );
		//e.~_com_error();
		return FALSE;
	}

	return TRUE;
}

void OpenDBase::InitMaxValue()
{
	_ConnectionPtr pCnn = GetCnn();
	if( pCnn == NULL )
		return;

	char strSQL[512];
	sprintf(strSQL, _T("update UserInfo set viewgp_max = %i,viewqh_max = %i,viewwp_max = %i,viewwh_max = %i,viewgg_max = %i,viewhj_max = %i"), 
			0,
			0,
			0,
			0,
			0,
			0);

	ExecuteSQL( pCnn, strSQL );
}

BOOL OpenDBase::UpdatePwd(ReqChangePassword* pReqChangePassword)
{
	_ConnectionPtr pCnn = GetCnn();
	if( pCnn == NULL )
		return FALSE;

	User_Info info;
	int nRet = GetUserInfo(info,pReqChangePassword->m_szUser);
	if( nRet < 0 )
		return FALSE;  // 不验证用户

	//if( info.notlogin == 2 )
	if( info.IsNotChangePwd() )
		return -3;

	CHSDes HSDes;
	CHqDataBuffer ret;
	CString strPwd = HSDes.DecodeString(ret,pReqChangePassword->m_szOldPWD);

	if( info.password.m_lpszBuffer != NULL &&
		strPwd.Compare(info.password.m_lpszBuffer) )
		return -2;

	CHqDataBuffer ret1;
	strPwd = HSDes.DecodeString(ret1,pReqChangePassword->m_szNewPWD);

	char strSQL[512];
	sprintf(strSQL, _T("update UserInfo set pwd = '%s' where userid = '%s'"), 
			strPwd,
			pReqChangePassword->m_szUser);

	int nReturn = ExecuteSQL( pCnn, strSQL );

	User_Info* pUser_Info = User_Info::GetUserInfo(pReqChangePassword->m_szUser);
	if( nReturn && pUser_Info )
	{
		pUser_Info->password.Copy(strPwd);
	}

	//
	Close();

	return nReturn;
}

int OpenDBase::WriteUserInfo(User_Info& Info,const char* userid,int nMask)
{
	CTime tm = CTime::GetCurrentTime();
	if( nMask == beginTime )
		Info.begintime = tm.GetTime();
	else if( nMask == endTime )
	{
		Info.endtime = tm.GetTime();
		CTime begin = Info.begintime;
		CTimeSpan span = tm - begin;
		Info.usedtotaltime += span.GetTotalMinutes();
	}

	User_Info* pUser_Info = User_Info::GetUserInfo(userid);
	if( pUser_Info )
	{
		pUser_Info->Copy(&Info);
		pUser_Info->m_nNeedWrite = 1;
	}

	return 1;

#if 0
	//
	_ConnectionPtr pCnn = GetCnn();
	if( pCnn == NULL )
		return -1;

	char strSQL[512];
	sprintf(strSQL, _T("update UserInfo set viewgp_max = %i,viewqh_max = %i,viewwp_max = %i,viewwh_max = %i,viewgg_max = %i,viewhj_max = %i,begintime = %i,endtime = %i,usedtotaltime = %i where userid = '%s' "), 
			Info.viewgp_max,
			Info.viewqh_max,
			Info.viewwp_max,
			Info.viewwh_max,
			Info.viewgg_max,
			Info.viewhj_max,
			Info.begintime,
			Info.endtime,
			Info.usedtotaltime,
			userid);

	return ExecuteSQL( pCnn, strSQL );
#endif

}

CString OpenDBase::GetComError( _com_error& e )
{
	CString		strMsg;

    _bstr_t bstrSource(e.Source());
    _bstr_t bstrDescription(e.Description());
    
    strMsg.Format( _T("Code = %08lx\nCode meaning = %s\nSource = %s\nDescription = %s"),
		e.Error(),
		e.ErrorMessage(),
		(LPCSTR) bstrSource,
		(LPCSTR) bstrDescription );

	return strMsg;
}

int OpenDBase::AddUserInfo(const char* userid,int nMax,User_Info* pInfo /*= NULL*/)
{
	if( userid == NULL )
		return -1;

	char* pUser = _strlwr(_strdup(userid));
	if( pUser == NULL )
		return -1;

	YlsAllTrim(pUser);
	
	User_Info* pUser_Info = NULL;
	if( g_mapUserList.Lookup(pUser,(void*&)pUser_Info) )
	{
		free(pUser);
		return 1;
	}

	pUser_Info = new User_Info();
	pUser_Info->userid.Copy(pUser);
	pUser_Info->viewgp_max = nMax;
	::YlsMapAdd(g_mapUserList,pUser,(void*)pUser_Info);
	free(pUser);

#if 0

	CATCH_Begin;	

	_ConnectionPtr pCnn = GetCnn();
	if( pCnn == NULL )
		return 0;

	char strSQL[512];

	sprintf(strSQL, _T("insert into UserInfo(userid,viewgp_max) values('%s','%i')"), userid,nMax);
	if( !ExecuteSQL( pCnn, strSQL ) )
	{
		sprintf(strSQL, _T("update UserInfo set viewgp_max = '%i' where userid = '%s'"), nMax,userid);
		if( ExecuteSQL( pCnn, strSQL ) )
			return 1;
	}

	CATCH_End0("OpenDBase::AddUserInfo");
#endif

	return 0;
}

int OpenDBase::GetUserInfo(User_Info& Info,const char* userid)
{
	if( userid == NULL )
		return -1;
	
	User_Info* pUser_Info = User_Info::GetUserInfo(userid);
	if( pUser_Info )
	{
		Info.Copy(pUser_Info);		
		return 1;
	}

	return -1;
}

int OpenDBase::GetUserInfo(User_Info*& pUser_Info,const char* userid)
{
	pUser_Info = NULL;

	if( userid == NULL )
		return -1;
	
	pUser_Info = User_Info::GetUserInfo(userid);
	if( pUser_Info )
	{
		//Info.Copy(pUser_Info);		
		return 1;
	}

	return -1;
}

int OpenDBase::GetUserCount(User_Info& Info,const char* userid)
{
	memset(&Info,0,sizeof(Info));
	if( userid == NULL )
		return -1;

	return GetUserInfo(Info,userid);
}

int OpenDBase::GetAllUserInfo(CYlsMapStringToPtr& mapUserList)
{
	_ConnectionPtr pCnn = GetCnn();
	if( pCnn == NULL )
		return 0;

	//
	char				strSQL[512];
	_RecordsetPtr		rs = NULL;

	sprintf(strSQL, _T("select * from UserInfo"));

	int bRet = 0;

	try
	{
		rs = pCnn->Execute( _bstr_t( strSQL ), NULL, adCmdText );
		while( rs != NULL && rs->adoEOF != TRUE )
		{
			if ( rs->adoEOF )
			{
				break;
			}

			bRet++;

			User_Info* Info = new User_Info;

			GetFieldValue( rs->Fields,0,Info->userid );
			if( Info->userid.IsValid() )
			{
				//ErrorOutput(Info->userid.m_lpszBuffer,Info->userid.m_cbBuffer);

				//
				GetFieldValue( rs->Fields,1,Info->username );
				GetFieldValue( rs->Fields,2,Info->password );
				GetFieldValue( rs->Fields,3,Info->groupname );
				GetFieldValue( rs->Fields,4,Info->area );
				GetFieldValue( rs->Fields,5,Info->notlogin );
				GetFieldValue( rs->Fields,6,Info->validdate );
				GetFieldValue( rs->Fields,7,Info->viewnews );
				GetFieldValue( rs->Fields,8,Info->viewgp );
				GetFieldValue( rs->Fields,9,Info->viewqh );
				GetFieldValue( rs->Fields,10,Info->viewwp );
				GetFieldValue( rs->Fields,11,Info->viewwh );
				GetFieldValue( rs->Fields,12,Info->viewgg );
				GetFieldValue( rs->Fields,13,Info->viewhj );
				GetFieldValue( rs->Fields,14,Info->userlevel );
				GetFieldValue( rs->Fields,15,Info->memo );

				GetFieldValue( rs->Fields,16,Info->viewgp_max );
				GetFieldValue( rs->Fields,17,Info->viewqh_max );
				GetFieldValue( rs->Fields,18,Info->viewwp_max );
				GetFieldValue( rs->Fields,19,Info->viewwh_max );
				GetFieldValue( rs->Fields,20,Info->viewgg_max );
				GetFieldValue( rs->Fields,21,Info->viewhj_max );

				GetFieldValue( rs->Fields,22,Info->usercfg );
				GetFieldValue( rs->Fields,23,Info->begintime );
				GetFieldValue( rs->Fields,24,Info->endtime );
				GetFieldValue( rs->Fields,25,Info->usedtotaltime );
				GetFieldValue( rs->Fields,26,Info->kaihutime );

				void* p = Info;
				char* pUser = _strlwr(_strdup(Info->userid.m_lpszBuffer));
				YlsAllTrim(pUser);
				::YlsMapAdd(mapUserList,pUser,p);
				free(pUser);
			}
			else
			{
				ErrorOutput0("无效用户ID");

				delete Info;
			}

			rs->MoveNext();
		}
	}
	catch(_com_error& e )
	{
		bRet = -2;
		//AfxMessageBox( GetComError( e ) );

		CString str = _T("从数据库读取纪录失败:\n") + GetComError( e );

		ErrorOutput((void*)(const char*)str,str.GetLength());
	}
	catch(...)//_com_error& e )
	{
		bRet = -2;
		
		//AfxMessageBox( GetComError( e ) );
		//e.~_com_error();
	}

	if( rs != NULL )
	{
		rs.Release();
		rs = NULL;
	}

	return bRet;
}

int OpenDBase::AddUser(UserDataInfo* pUserDataInfo)
{
	if( pUserDataInfo == NULL )
		return 0;

	CATCH_Begin;	

	_ConnectionPtr pCnn = GetCnn();
	if( pCnn == NULL )
		return 0;

	char strSQL[2048];

	sprintf(strSQL,_T("INSERT INTO UserInfo(userid, username, pwd, groupname, notlogin, validdate, viewgp, usercfg) values('%s','%s','%s','%s','%i','%s','%i','%s')"),
		pUserDataInfo->userid,pUserDataInfo->username,pUserDataInfo->password,pUserDataInfo->groupname,
		pUserDataInfo->notlogin,pUserDataInfo->validdate,pUserDataInfo->viewgp,pUserDataInfo->usercfg);

	if( !ExecuteSQL( pCnn, strSQL ) )
	{
		return 0;
	}

	return 1;

	CATCH_End0("OpenDBase::AddUserInfo");

	return 0;
}

int OpenDBase::DelUser(const char* userid)
{
	CATCH_Begin;	

	_ConnectionPtr pCnn = GetCnn();
	if( pCnn == NULL )
		return 0;

	char strSQL[2048];

	sprintf(strSQL,_T("delete from UserInfo where userid = '%s'"),userid);

	if( !ExecuteSQL( pCnn, strSQL ) )
	{
		return 0;
	}

	return 1;

	CATCH_End0("OpenDBase::DelUser");

	return 0;
}

int OpenDBase::UpdateUser(UserDataInfo* pUserDataInfo,int nMask)
{
	if( pUserDataInfo == NULL )
		return 0;

	CATCH_Begin;	

	_ConnectionPtr pCnn = GetCnn();
	if( pCnn == NULL )
		return 0;

	char strSQL[2048];

	sprintf(strSQL,_T("update UserInfo set username = '%s', pwd = '%s', groupname = '%s', notlogin = '%i', validdate = '%s', viewgp = '%i', usercfg = '%s' where userid = '%s'"),
		pUserDataInfo->username,pUserDataInfo->password,pUserDataInfo->groupname,
		pUserDataInfo->notlogin,pUserDataInfo->validdate,pUserDataInfo->viewgp,pUserDataInfo->usercfg);

	if( !ExecuteSQL( pCnn, strSQL ) )
	{
		return 0;
	}

	return 1;

	CATCH_End0("OpenDBase::UpdateUser");

	return 0;	
}

int OpenDBase::KickOutUser(const char* userid,unsigned int nSession)
{
	return 0;
}

ThreadReturn OpenDBase::WriteDBThread(ThreadParam pParameter)
{
	OpenDBase* pSortParam = (OpenDBase*)pParameter;

	pSortParam->m_nStopFlag = 1;

	while(1)
	{
		Sleep(1000*60);

		_ConnectionPtr pCnn = GetCnn();
		if( pCnn == NULL )
			continue;

		const char* key = NULL;
		User_Info* Info = NULL;

		POSITION  pos;
		for( pos = g_mapUserList.GetStartPosition(); pos != NULL; )
		{
			g_mapUserList.GetNextAssoc( pos, key, (void*&)Info );
			if( Info == NULL )
				continue;

			if( !Info->m_nNeedWrite )
				continue;

			Info->m_nNeedWrite = 0;

			char strSQL[512];
			sprintf(strSQL, _T("update UserInfo set begintime = %i,endtime = %i,usedtotaltime = %i where userid = '%s' "), 
				Info->begintime,
				Info->endtime,
				Info->usedtotaltime,
				Info->userid);

			pSortParam->ExecuteSQL( pCnn, strSQL );

		}
	}
}

void OpenDBase::StartWriteDB()
{
	//
	m_nStopFlag = 0;
	DWORD dwMainThreadID = -1;
	HANDLE hThread = CreateThread(NULL,0,WriteDBThread,this,0,&dwMainThreadID);
	if (hThread)
	{				  
		while (m_nStopFlag == 0)
		{
			Sleep(20);
		}

		::CloseHandle(hThread);
	}
}

