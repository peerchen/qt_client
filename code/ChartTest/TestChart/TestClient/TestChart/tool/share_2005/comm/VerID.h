/*******************************************************************************
* Copyright (c)2003, Ѷ��������޹�˾
* All rights reserved.
*
* �ļ����ƣ�HS_DISK_H.h
* �ļ���ʶ��ͨѶ�����ṹ
* ժ    Ҫ��ͨѶ�����ṹ
*
* ��ǰ�汾��xunjie
* ��    �ߣ�Ѷ������
* ������ڣ�2005-06
*
* ��    ע��
*
* �޸ļ�¼��
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