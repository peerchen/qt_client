/*******************************************************************************
* Copyright (c)2003, 讯捷软件有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：
* 作    者：
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/


//#pragma once
#if !defined(_CYlsTimeSpan_h_)
#define _CYlsTimeSpan_h_

#include "stdafx.h"


#ifndef HS_SUPPORT_UNIX
#define CYlsTimeSpan CTimeSpan
#define CYlsTime	 CTime
#	include	<time.h>
#else
//#	include	<sys/time.h>
typedef time_t __time64_t;

class CYlsTimeSpan
{
public:
	CYlsTimeSpan() /*throw()*/;
	CYlsTimeSpan( __time64_t time ) /*throw()*/;
	CYlsTimeSpan( LONG lDays, int nHours, int nMins, int nSecs ) /*throw()*/;

	LONGLONG GetDays() const /*throw()*/;
	LONGLONG GetTotalHours() const /*throw()*/;
	LONG GetHours() const /*throw()*/;
	LONGLONG GetTotalMinutes() const /*throw()*/;
	LONG GetMinutes() const /*throw()*/;
	LONGLONG GetTotalSeconds() const /*throw()*/;
	LONG GetSeconds() const /*throw()*/;

	__time64_t GetTimeSpan() const /*throw()*/;

	CYlsTimeSpan operator+( CYlsTimeSpan span ) const /*throw()*/;
	CYlsTimeSpan operator-( CYlsTimeSpan span ) const /*throw()*/;
	CYlsTimeSpan& operator+=( CYlsTimeSpan span ) /*throw()*/;
	CYlsTimeSpan& operator-=( CYlsTimeSpan span ) /*throw()*/;
	bool operator==( CYlsTimeSpan span ) const /*throw()*/;
	bool operator!=( CYlsTimeSpan span ) const /*throw()*/;
	bool operator<( CYlsTimeSpan span ) const /*throw()*/;
	bool operator>( CYlsTimeSpan span ) const /*throw()*/;
	bool operator<=( CYlsTimeSpan span ) const /*throw()*/;
	bool operator>=( CYlsTimeSpan span ) const /*throw()*/;

private:
	__time64_t m_timeSpan;
};


class CYlsTime
{
public:
	static CYlsTime GetCurrentTime() /*throw()*/;

	CYlsTime() /*throw()*/;
	CYlsTime( __time64_t time ) /*throw()*/;
	CYlsTime( SYSTEMTIME& st );
	CYlsTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
		int nDST = -1 ) /*throw()*/;
	CYlsTime( WORD wDosDate, WORD wDosTime, int nDST = -1 ) /*throw()*/;

	CYlsTime& operator=( __time64_t time ) /*throw()*/;

	CYlsTimeSpan operator-( CYlsTime time ) const /*throw()*/;
	CYlsTime& operator+=( CYlsTimeSpan span ) /*throw()*/;
	CYlsTime& operator-=( CYlsTimeSpan span ) /*throw()*/;

	CYlsTime operator-( CYlsTimeSpan span ) const /*throw()*/;
	CYlsTime operator+( CYlsTimeSpan span ) const /*throw()*/;

	bool operator==( CYlsTime time ) const /*throw()*/;
	bool operator!=( CYlsTime time ) const /*throw()*/;
	bool operator<( CYlsTime time ) const /*throw()*/;
	bool operator>( CYlsTime time ) const /*throw()*/;
	bool operator<=( CYlsTime time ) const /*throw()*/;
	bool operator>=( CYlsTime time ) const /*throw()*/;

	__time64_t GetTime() const /*throw()*/;
	struct tm* GetLocalTm( struct tm* ptm = NULL ) const /*throw()*/;

	int GetYear() const /*throw()*/;
	int GetMonth() const /*throw()*/;
	int GetDay() const /*throw()*/;
	int GetHour() const /*throw()*/;
	int GetMinute() const /*throw()*/;
	int GetSecond() const /*throw()*/;
	int GetDayOfWeek() const /*throw()*/;

private:
	__time64_t m_time;
};

#endif
#endif // HS_SUPPORT_UNIX

