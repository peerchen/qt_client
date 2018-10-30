#pragma once

//计算涨跌幅
extern BOOL ComputerRise_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType, ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
//成交价震幅排名
extern BOOL ComputerPrice_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
//成交量变化(量比)排名
extern BOOL ComputerVolBi_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
//成交量排名
extern BOOL ComputerVolume_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
//资金流向排名
extern BOOL ComputerMoney_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
//计算委比
extern BOOL ComputerComm_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);

// 涨跌
extern BOOL ComputerZhangDie_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
// 委差
extern BOOL ComputerCommSub_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);

// 换手率
extern BOOL ComputerHuanShou_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);
// 市盈率
extern BOOL ComputerShiYing_Ex(short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);

extern BOOL ComputerVarField_Ex(int nMarket,int nPos,short nFirst,short nTotal, HSMarketDataType cCodeType,ShareRealTimeData* pSrcData,StockInitInfo* pStockInitInfo,StockOtherData* pStockOtherData,long* plResult,void* pData = NULL,long lErrorValue = YlsInvalidateMinValues);

extern void QuickSortDescend_Ex(short iLow,short iHigh, short* pIndex, long* pData );
extern void QuickSortAscend_Ex(short iLow, short iHigh, short* pIndex,long* pData);