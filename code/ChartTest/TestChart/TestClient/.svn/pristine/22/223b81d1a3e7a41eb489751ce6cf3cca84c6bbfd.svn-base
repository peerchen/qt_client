/*******************************************************************************
* Copyright (c)2003, 讯捷软件有限公司
* All rights reserved.
*
* 文件名称：HS_DISK_H.h
* 文件标识：通讯基本结构
* 摘    要：通讯基本结构
*
* 当前版本：xunjie
* 作    者：讯捷王工
* 完成日期：2005-06
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/

#ifndef HS_VERID_H_
#define HS_VERID_H_

#include "hsstruct.h"
#include "hscommunication.h"

#define HS_VERID_1	(0x1000)

static long YlsGetDataStructLength()
{
	return (sizeof(BourseInfo) + sizeof(StockType) + sizeof(CodeInfo) + 
		    sizeof(FileNowData) + 
			sizeof(StockHistoryData) + 
			sizeof(StockDay) +
			sizeof(RealTimeData) + 
			sizeof(ANSDAYDATA) + HS_VERID_1);
}

#endif // HS_VERID_H_