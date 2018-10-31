/*******************************************************************************
 * Copyright (c)2003, 讯捷软件有限公司
 * All rights reserved.
 *
 * 文件名称：dayfile.h
 * 文件标识：盘后数据处理
 * 摘    要：盘后数据处理
 *
 * 当前版本：2.0
 * 作    者：
 * 完成日期：
 *
 * 取代版本：
 * 原 作 者：
 * 完成日期：
 * 备	 注：
 *******************************************************************************/

#ifndef INC_DAYFILE_H
#define INC_DAYFILE_H

//#include "..\comm\struct3.h"
#include "fileobj.h"


/////////////////////////////////////////////////////////////////////////////
//数据文件虚基类
class CDataFile : public CSupperFileObj
{
public:
	CDataFile();
	CDataFile(LPCTSTR lpszFileName, UINT nOpenFlags);
	//打开文件
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags, short nPeriod = 0);
public:
	//纯虚函数
	virtual short HandleData(void* pData, long& lSize, CTime& cBegin, CTime& cEnd) = 0;
							//lSize < 0 : Delete Data
							//lSize = 0 : Exam   Data
							//lSize > 0 : Read	 Data
	//纯虚函数
	virtual long  TimeToLong(CTime ctm) = 0;
	//设置市场信息
	void SetStockCodeInfo(HSMarketDataType cCodeType, CBourseInfo* pBourse);
	//转换时间	
	static CTime  LongToTime(long lDate);
protected:
	/*样式与周期等:文件类型|周期 
	文件类型：SDF_DAYFILE， SDF_VOLUMEFILE,SDF_VOLUMEFILE
	周期:SDF_MINUTE,...SDF_YEAR
	*/
	short			  m_nPeriod;
	//类型
	HSMarketDataType  m_cCodeType;
	//市场信息指针
	CBourseInfo* m_pBourse;
};
/////////////////////////////////////////////////////////////////////////////
//5分钟、15分钟、30分钟、60分钟、120分钟、日线、周线、月线、年线数据文件
//日线、周线、月线、年线成交量详细数据文件
//日线、周线、月线、年线历史成交明细数据文件
#define SDF_DAYFILE		0x0000		//K 线数据文件
#define SDF_TRACEFILE	0x1000		//成交量明细数据文件
#define SDF_VOLUMEFILE	0x2000		//历史成交明细数据文件

#define SDF_MINUTE		0x0100		//分钟线，低八位代表分钟数，但必须是五的倍数。
#define SDF_PERIOD_TYPE_DAY			0x0200		//日线
#define SDF_WEEK		0x0300		//周线
#define SDF_MONTH		0x0400		//月线
#define SDF_YEAR		0x0500		//年线

#define SDF_IGNORE		0		//忽略，不处理
#define SDF_OVERLAY		1		//覆盖
#define SDF_UPDATE		2		//更新，累加成交量
#define SDF_INSERT		3		//插入新K线

class CBourseInfo;
class CStockDayFile : public CDataFile
{
public:
	CStockDayFile();
	//保存周期，调用基类构造
	CStockDayFile(LPCTSTR lpszFileName, UINT nOpenFlags, short nPeriod);

	virtual short HandleData(void* pData, long& lSize, CTime& cBegin, CTime& cEnd);
	/********************************************************************************
	 * 函数功能 : 根据周期,返回long型时间	
	 * 函数参数 : CTime ctm - 时间	
	 *  返回值  : long, 如果周期为SDF_MINUTE, 返回(YYYY - 1990)MMDDHHmm, 例如13041809
	 *					否则返回YYYYMMDD,例如20030418
	 * 调用依赖 :	
	 * 作    者 :
	 * 完成日期 :
	 * 修改记录 :
	 *******************************************************************************/
	virtual long  TimeToLong(CTime ctm);
	/********************************************************************************
	 * 函数功能 : 返回文件中数据的个数(记录个数)	
	 * 函数参数 : void	
	 *  返回值  : 记录个数 失败返回0	
	 * 调用依赖 :	
	 * 作    者 :
	 * 完成日期 :
	 * 修改记录 :
	 *******************************************************************************/
	long  GetDaySize();
	/********************************************************************************
	* 函数功能 : 根据文件类型取得数据单位的结构长度（一个记录的长度）
	* 函数参数 : void	
	*  返回值  : long 一个记录的长度 
	* 调用依赖 : 此函数前提是必须文件类型已经指定	默认处理为日线文件
	* 作    者 :
	* 完成日期 :
	* 修改记录 :
	*******************************************************************************/
	long  GetRecordSize();
	/********************************************************************************
	 * 函数功能 : 读取数据记录	
	 * 函数参数 : void* pData - 记录保存指针 外部内存区域必须足够大,否则造成溢出
	 *			  long lSize - 待读取记录数目
	 *			  long lFrom - FILE_CURRENT或者时间,
					如果为FILE_CURRENT,将从文件当前位置读
					如果为时间,将快速查找该时间的数据记录位置
	 *  返回值  : 成功读取的记录个数	失败返回0
	 * 调用依赖 :	
	 * 作    者 :
	 * 完成日期 :
	 * 修改记录 :
	 *******************************************************************************/
	long  ReadData(void* pData, long lSize, long lFrom = FILE_CURRENT);
	//返回文件类型
	short GetDayFileType() { return (m_nPeriod & 0xF000); }
	/********************************************************************************
	 * 函数功能 :	按照文件类型,周期写数据 将比较时间,决定:插入,覆盖,更新操作
	 * 函数参数 :	void* pData - 待写数据指针
	 *				long lSize -  数据记录个数
	 *				short nPeriod - 指定周期, 务必符合文件类型支持的周期,否则失败
	 *
	 *				FileNowData* pNowData - 文件中实时数据
	 *				short nMessageMask -	资料信息掩码
	 *				short nVolAmount -	成交次数
	 *				long lOpenVolumn -	开盘成交量
	 *				long lZeroVol -对倒成交量
	 *
	 *				StockHistoryData* pHisData -  分钟数据
	 *				short nSize - 数据个数 
	 *				long nHand - 现手
	 *				StockTick* pTraceData - 分笔数据
	 *  返回值  :	成功返回TRUE 失败返回FALSE
	 * 调用依赖 :	
	 * 作    者 :
	 * 完成日期 :
	 * 修改记录 :
	 *******************************************************************************/
	BOOL  WriteData(void* pData, long lSize, short nPeriod);
	BOOL  WriteData(FileNowData* pNowData, short nMessageMask = 0, short nVolAmount = 0, long lOpenVolumn = 0, long lZeroVol = 0);
	BOOL  WriteData(StockHistoryData* pHisData, short nSize, long nHand = 100);
	BOOL  WriteData(StockTick* pTraceData, short nSize, long nHand = 100);
	//更新文件数据记录 对分钟线文件有效
	void  Upgrade();
	//更新文件数据记录 对分钟线文件有效	StockDay* pData - 数据 long lSize -记录个数
	void  Upgrade(StockDay* pData, long lSize);
	//是否需要更新 根据时间格式是否合法
	BOOL  IsNeedUpgrade();

protected:
	//实时更新数据, 按照文件类型不同
	void  UpdateData(void* pOld, void* pNew);
	//查找文件中时间记录
	long  FindDate(long lDate);
	//查找内存中时间记录 返回插入,覆盖,更新操作类型,
	short FindDate(char* pData, long lSize, long lDate, short nPeriod, long& lIndex);
	//比较时间 决定操作 返回值：0--相等或同一K线    >0：新>旧   <0：新<旧 lDate1:原日期	lDate2:新日期
	int   CompDate(long lDate1, short nPeriod1, long lDate2, short nPeriod2, short& nResult);
	//根据不同文件类型, 写不同文件数据	
	BOOL  WriteDayData(StockTick* pTraceData, short nSize, long nHand = 100);
	BOOL  WriteVolumeData(StockTick* pTraceData, short nSize, long nHand = 100);
	BOOL  WriteTraceData(StockTick* pTraceData, short nSize, long nHand = 100);

public:
	//根据指定周期, 返回支持此周期的文件类型; nPeriod - 有效值:&0xFF00
	short CommPeriodToData(short nPeriod);

};

/////////////////////////////////////////////////////////////////////////////
//历史分时数据文件	未使用
class CStockTrendFile : public CDataFile
{
public:
	CStockTrendFile();
	CStockTrendFile(LPCTSTR lpszFileName, UINT nOpenFlags);
	
	virtual short HandleData(void* pData, long& lSize, CTime& cBegin, CTime& cEnd);
	virtual long  TimeToLong(CTime ctm);

	BOOL  WriteData(StockHistoryTrend* pData);
	BOOL  WriteData(StockHistoryData* pHisData, StockHistoryTrendHead* pHead);

protected:
	short FindDate(long& lDate, long& lPos, short& nSize);
};

/////////////////////////////////////////////////////////////////////////////
//硬盘缓冲索引文件
#define DC_LASTTIME			0x0001
#define DC_FILENAME			0x0002
#define DC_CODEINFO			0x0004
#define DC_DATATYPE			0x0008
#define DC_BEGINTIME		0x0010
#define DC_ENDTIME			0x0020

#define DC_NOT_CREATE_ZIP		0x0001
#define DC_NOT_CREATE_UNZIP		0x0002
//未使用
class CDiskCacheIndexFile;
class CDiskCacheIndex
{
public:
	CDiskCacheIndex();
	CDiskCacheIndex(unsigned short nDataType, long lBegin, long lEnd, CodeInfo* pciInfo);
	CDiskCacheIndex(const CDiskCacheIndex& value);

	int Compare(const CDiskCacheIndex&  dataSrc) const;       
	const CDiskCacheIndex& operator=(const CDiskCacheIndex& dataSrc);
	
	CString GetFileName(BOOL &bZip);
	void    SetFileName(const char* pszName, int nMode = 0);
	void    SetLastTime(long lLastTime = -1);
protected:
	unsigned short	m_nDataType;
	long			m_lBeginTime;	//CTime
	long			m_lEndTime;		//CTime
	CodeInfo		m_ciInfo;
	long			m_lLastTime;	//CTime
	char			m_szFileName[16];		//only file name;

	friend class CDiskCacheIndexFile;
};
//未使用
// Compare helpers
//operator '=='
inline BOOL AFXAPI operator==(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) == 0; }
//operator '!='
inline BOOL AFXAPI operator!=(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) != 0; }
//operator '<'
inline BOOL AFXAPI operator<(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) < 0; }
//operator '>'
inline BOOL AFXAPI operator>(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) > 0; }
//operator '<='
inline BOOL AFXAPI operator<=(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) <= 0; }
//operator '>='
inline BOOL AFXAPI operator>=(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) >= 0; }
//未使用
/////////////////////////////////////////////////////////////////////////////
class CDiskCacheIndexFile : public CSupperFileObj
{
public:
	CDiskCacheIndexFile();
	CDiskCacheIndexFile(LPCTSTR lpszFileName, UINT nOpenFlags);
	
	BOOL FindCacheIndex(CDiskCacheIndex* pkey, long& lIndex, CString& strFileName, BOOL& bZip);

	BOOL InsertCacheIndex(CDiskCacheIndex* pInsert, long lIndex);
	BOOL UpdateCacheIndex(CDiskCacheIndex* pUpdate, long lIndex, short nMode = (short)0x0FFFF);
	int  DeleteCacheIndex(const char* pszPath, const char* pszCacheName, int nHoldDay = 30);
};

#endif