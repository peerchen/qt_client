
/*******************************************************************************
* Copyright (c)2003, 讯捷软件有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：xunjie2008
* 作    者：
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/


#ifndef SrvManager_h
#define SrvManager_h

#include "hscommunication.h"


struct ProgramProperty
{
	char	 m_szName[256];		// 程序完整路径名称
	int		 m_nProccessID;		// 当前进程ID

	int		 m_nOperator;		// 操作,参见: RT_Srv_Sub_Restart 等的定义
};

struct AnsBackSrvStatusInfo
{
	DataHead m_dhHead;			// 数据报头

	ProgramProperty m_sProg;    // 程序属性

	int				m_nSize;    // 当前状态数据
	char			m_cData[1];
};

struct ProgramAsk
{	
	ProgramProperty m_sProg;

	int				m_nSize;
	char			m_cData[1];
};

//
struct UserDataInfo
{
	char  userid[32];
	char  username[32];
	char  password[32];
	char  groupname[32];
	char  area[32];

	int   notlogin; // =0验证用户密码
				    // =1超级用户
				    // =2用户不能够修改密码
				    // =3延时港股行情用户
				    // =4实时港股行情用户

 	unsigned int  validdate;

	int  viewnews;

	int  viewgp;
	int  viewqh;
	int  viewwp;
	int  viewwh;
	int  viewgg;

	int  userlevel;

	int  viewgp_max;
	int  viewqh_max;
	int  viewwp_max;
	int  viewwh_max;
	int  viewgg_max;

	char  memo[256];
	char  usercfg[1024];

	int  begintime;
	int  endtime;
	int  usedtotaltime;

	unsigned int m_nSession;

	UserDataInfo()
	{
		memset(this,0,sizeof(UserDataInfo));
	}
};

struct SendToUser
{
	char		 m_userid[32];
	unsigned int m_nSession;
	
	SendToUser()
	{
		memset(this,0,sizeof(SendToUser));
	}
};

struct SendToUserItem
{
	SendToUser m_sSendToUser;
	char	   m_szGroupName[64];

	SendToUserItem()
	{
		memset(this,0,sizeof(SendToUserItem));
	}
};

struct SendInfoToUser
{
	int m_nDataSize;
	int m_nUserSize;

	SendToUser m_sSendToUser[1];
};

#endif

