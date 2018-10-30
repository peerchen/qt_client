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



#if !defined(UserManager_h)
#define UserManager_h


#pragma once

//#include "dbdaoint.h"
//#include "hsserverdatapath.h"
#include "HSDes.h"
#include "ylssession.h"


#include <comdef.h>			// COM support
#include <atlbase.h>		// CComBSTR support
#include <afxadv.h>			// CSharedFile
#include <oledb.h>

//#import "msxml4.dll" named_guids
#import "D:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF", "adoEOF")

// 远程用户信息（内存中的）
struct MemUserInfo
{
	CYlsArray<CHqDataBuffer*,CHqDataBuffer*>* m_ayGroup;		// 分组
	CHqDataBuffer					   		  m_strUnionGroup;  // 合并的分组串
	CHqDataBuffer					   		  m_strType;		// 类型
	CHqDataBuffer							  m_strPassword;	// 成功后的密码

	MemUserInfo()
	{
		m_ayGroup = NULL;
	}

	~MemUserInfo()
	{
	}

	int IsValid() { return (m_ayGroup != NULL); }
};

class CYlsMapStringToPtr;
struct User_Info
{
	CStringBuffer  userid;
	CStringBuffer  username;
	CStringBuffer  password;
	CStringBuffer  groupname;
	CStringBuffer  area;
	CStringBuffer  kaihutime;

	int  notlogin; // =0 验证用户密码
				   // =1 超级用户
				   // =2 用户不能够修改密码
				   // =3 延时港股行情用户
				   // =4 实时港股行情用户
				   // =5 用户不检查密码
	               // =6 用可以发送群组公告

 	CStringBuffer  validdate;

	int  viewnews;

	int  viewgp;
	int  viewqh;
	int  viewwp;
	int  viewwh;
	int  viewgg;
	int  viewhj;   //added by Ben 20100823

	int  userlevel;

	int  viewgp_max;
	int  viewqh_max;
	int  viewwp_max;
	int  viewwh_max;
	int  viewgg_max;
	int  viewhj_max; // added by Ben 20100823

	CStringBuffer  memo;
	CStringBuffer  usercfg;

	int  begintime;
	int  endtime;
	int  usedtotaltime;

	MemUserInfo m_sMemUserInfo;

	CYlsArray<CYlsSession*,CYlsSession*> m_aySession; // 当前用户关联的session

	int m_nKickOut;   // 当前用户已经被剔出
	int m_nNeedWrite; // 是否写入

	User_Info()
	{
		notlogin = 0;
		viewnews = 0;

		viewgp = 0;
		viewqh = 0;
		viewwp = 0;
		viewwh = 0;
		viewgg = 0;
		viewhj = 0;

		userlevel = 0;

		viewgp_max = 0;
		viewqh_max = 0;
		viewwp_max = 0;
		viewwh_max = 0;
		viewgg_max = 0;
		viewhj_max = 0;

		begintime = 0;
		endtime = 0;
		usedtotaltime = 0;

		m_nKickOut = 0;
		m_nNeedWrite = 0;

		//memset(this,0,sizeof(User_Info));		
	}

	BOOL IsPWD(int nOption,const char* szPwd);
	BOOL IsMaxLogin(AskData *pAsk,CSessionInfo* pSessionInfo);
	BOOL ExitLogin(CSessionInfo* pSessionInfo);

	int	 IsExpire();

	BOOL IsNotLogin()		 { return (notlogin == 1); }	

	BOOL IsNotChangePwd()	 { return (notlogin == 2); }

	BOOL IsDelayUser()		 { return (notlogin == 3); }

	BOOL IsRealTimeUser()	 { return (notlogin == 4); }

	BOOL IsNotCheckPwd()	 { return (notlogin == 5); }	

	BOOL IsSendGroupNotice() { return (notlogin == 6); }	

	BOOL GetCFGPath(CSessionInfo* pSessionInfo);

	static User_Info* GetUserInfo(const char* pUserKey);
	static int		  InitUserInfoList();

	static int		  LoadCheckUserFile(CYlsMapStringToPtr* mapbdzpass,CYlsMapStringToPtr* mapbdzaddr);
	static int		  Loadbdzpass(char* szsbdzpass,CYlsMapStringToPtr* mapbdzpass,CYlsMapStringToPtr* mapbdzaddr);
	static int		  Loadbdzaddr(char* szsbdzaddr,CYlsMapStringToPtr* mapbdzaddr);

	static char*	  Getbdzaddr(const char* szKey,CHqDataBuffer& buffer,CYlsMapStringToPtr* mapbdzaddr);
	static char*	  Getbdzpass(const char* szKey,CHqDataBuffer& buffer,CHqDataBuffer& PathBuffer);

	static void		  Writebdzpass(CHqDataBuffer& buffer,const char* szIP);

	static void	      Free(CYlsMapStringToPtr& mapbdzpass,CYlsMapStringToPtr& mapbdzaddr);

	void Copy(User_Info* pInfo);

	// 宏力通认证
	static int CheckHltpass(const char* szKey,CHqDataBuffer& buffer,CHqDataBuffer& PathBuffer);

};

enum
{
	beginTime,
	endTime,
};

class OpenDBase
{
public:
	static _ConnectionPtr m_pCnn;

public:
	OpenDBase();

	~OpenDBase()
	{
		Close();
	}
	
	void Close();

	BOOL Open() { return (GetCnn() != NULL); }

public:
	static _ConnectionPtr GetCnn();

	static CString GetComError( _com_error& e );

	BOOL GetFieldValue(FieldsPtr fields, long nIndex, CStringBuffer& buffer);
	BOOL GetFieldValue(FieldsPtr fields, long nIndex, int& buffer);

	int GetUserInfo(User_Info*& pUser_Info,const char* userid);

	int GetUserInfo(User_Info& Info,const char* userid);
	int GetUserCount(User_Info& Info,const char* userid);

	int AddUserInfo(const char* userid,int nMax,User_Info* pInfo = NULL);

	int  WriteUserInfo(User_Info& Info,const char* userid,int nMask);
	BOOL ExecuteSQL(_ConnectionPtr &pCnn, const char* strSQL);

	void InitMaxValue();
	BOOL UpdatePwd(ReqChangePassword* pReqChangePassword);

	int GetAllUserInfo(CYlsMapStringToPtr& mapUserList);

	int AddUser(UserDataInfo* pUserDataInfo);
	int DelUser(const char* userid);
	int UpdateUser(UserDataInfo* pUserDataInfo,int nMask);
	int KickOutUser(const char* userid,unsigned int nSession);

public:
	static BOOL IsChange();

	void StartWriteDB();

protected:
	static struct stat m_stPre;
	static char	  m_strCnnFile[256];

	char m_nStopFlag;
	static ThreadReturn WriteDBThread(ThreadParam pParameter);
};

#endif
