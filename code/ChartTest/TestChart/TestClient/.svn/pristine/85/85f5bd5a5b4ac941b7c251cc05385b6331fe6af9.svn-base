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


#if !defined(_hssortdata_h_)
#define _hssortdata_h_

#include "stdafx.h"
#include "servermarketinfo.h"


//
extern StockInfoIn*   FindIndex(const CodeInfo * code,CServerMarketInfo*& pCServerMarketInfo);
extern StockInfoIn*   FindIndexByMarket(const CodeInfo * code,CServerMarketInfo* pCServerMarketInfo);
extern CodeInfo*	  FindIndexByCode(const char* pCode,HSMarketDataType cBourse,StockInitInfo** pStockInitInfo = NULL);
extern CodeInfo*	  FindIndexByCode(const char* pCode,CServerMarketInfo* pCServerMarketInfo,StockInitInfo** pStockInitInfo = NULL);
extern StockInfoIn*   FindIndex_Dfx(HSMarketDataType nMarket,const char* pCode,CServerMarketInfo*& pCServerMarketInfo);


// 查找匹配的代码

#define SI_CODE		1
#define SI_NAME		2
#define SI_PYJC		3

#define Find_Max	5

int FindMatchByCode(const char* pCode,CServerMarketInfo* pCServerMarketInfo,
					CYlsArray<StockInitInfo*,StockInitInfo*>& ay,
					int nType,int nMax);

//
extern StockCdp*	  GetCurCDP(const CodeInfo * code,CServerMarketInfo*& pCServerMarketInfo);

	//计算涨跌幅
extern BOOL ComputerRise(short nFirst,short nTotal, HSMarketDataType cCodeType, ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
	//成交价震幅排名
extern BOOL ComputerPrice(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
	//成交量变化(量比)排名
extern BOOL ComputerVolBi(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues,long lMask = 0);
	//成交量排名
extern BOOL ComputerVolume(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
	//资金流向排名
extern BOOL ComputerMoney(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
	//计算委比
extern BOOL ComputerComm(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);

// 涨跌
extern BOOL ComputerZhangDie(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
// 委差
extern BOOL ComputerCommSub(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);

// 换手率
extern BOOL ComputerHuanShou(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
// 市盈率
extern BOOL ComputerShiYing(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);

// 
extern BOOL ComputerVarField(int nMarket,int nPos,short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues,long lMask = 0);

extern void QuickSortDescend(short iLow,short iHigh, short* pIndex, long* pData );
extern void QuickSortAscend(short iLow, short iHigh, short* pIndex,long* pData);

#endif
