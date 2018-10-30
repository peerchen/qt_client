/*************************************************************
*	Copyright (c)2002, YLink软件有限公司
*	All rights reserved.
*
*	文件名称：	Thread.h
*	作	  者：	YLink王工
*  当前版本：	4.0
*  创建日期：	2004年3月19日
*  完成日期：	
*  描    述：	线程控制的包装类
*
*	修改历史：	
*          日期：  
*          作者：  
*          改动：  
*
***************************************************************/

#pragma once

#include "afxmt.h"

// 线程的几种状态
#ifndef Share_Thread_status
#define Share_Thread_status
enum 
{ 
	AgentNone,
	AgentRun,        // 启动
	AgentIdle,       // 空闲
	AgentStop,       // 停止
	AgentRunning,    // 正在运行
	AgentSuspend,    // 崭停
	AgentFail = -1   // 错误
};
#endif

class YlsThread
{
public:
	YlsThread()
	{
		m_dwMainThreadID = 0;
		m_evtInitialized = NULL;
		m_hThread = NULL;
		m_nStopThread = AgentNone;		
		m_pnProgress = NULL;
	}

	~YlsThread()
	{
		YlsStop();
	}

protected:	
	DWORD   m_dwMainThreadID;
	CEvent* m_evtInitialized;
	HANDLE  m_hThread;
	int     m_nStopThread;
	int*    m_pnProgress;
public:
	void YlsStart(LPVOID lpParameter,LPTHREAD_START_ROUTINE lpStartAddress)
	{
		YlsStop();

		m_evtInitialized = new CEvent;

		m_dwMainThreadID = -1;
		m_nStopThread = AgentRun;
		m_pnProgress = NULL;
		m_hThread = CreateThread(NULL,0,lpStartAddress,lpParameter,0,&m_dwMainThreadID);
		if (m_hThread)
		{
			while (m_nStopThread == AgentRun)
			{
				Sleep(20);
			}
			if (m_nStopThread == AgentFail) // fail
			{
				CloseHandle(m_hThread);
				m_hThread = NULL;
				return;
			}
		}
		else // fail
		{
			return;
		}
	}
	
	virtual BOOL YlsStop()
	{
		if( m_hThread )
		{
			if(m_pnProgress)
			{	
				*m_pnProgress = 0;
				m_pnProgress = NULL;
			}

			if( m_evtInitialized )
				m_evtInitialized->SetEvent();

			m_nStopThread = AgentStop;
			WaitForSingleObject(m_hThread, INFINITE);
			CloseHandle(m_hThread);
			m_hThread = NULL;

			if( m_evtInitialized )
			{
				delete m_evtInitialized;
				m_evtInitialized = NULL;
			}
			return TRUE;
		}
		return FALSE;
	}

	BOOL YlsIsValid() { return (m_hThread != NULL); }

	void CloseThread() 
	{
		m_nStopThread = AgentStop;
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	BOOL IsThreadStatus(int nStatus)
	{
		return (nStatus == m_nStopThread);
	}

	BOOL IsThreadExit()
	{
		if( m_evtInitialized == NULL )
			return FALSE;

		DWORD dwEvent = WaitForSingleObject(m_evtInitialized->m_hObject, 20);
		return (dwEvent == WAIT_OBJECT_0);
	}

};
