
/*******************************************************************************
 * Copyright (c)2003, 讯捷软件有限公司
 * All rights reserved.
 *
 * 文件名称：BaseDefine.h
 * 文件标识：常用宏定义
 * 摘    要：常用宏定义
 *
 * 当前版本：dfx2003
 * 作    者：讯捷王工
 * 完成日期：2003-08-26
 *
 * 取代版本：2.0
 * 原 作 者：讯捷王工
 * 完成日期：2003-04-01
 * 备	 注：
 *******************************************************************************/

#ifndef YLS_BASEDEFINE_H
#define YLS_BASEDEFINE_H
#pragma	pack(1)


// 不同进程内存交换
enum YlsAllocType {charType,InfoIndexType,InfoIndexSubType,YlsDrawOtherDataType,HSDoubleType,HSCString,HSCStringCopy};
typedef void* ( *YlsExternAlloc )( long nCurSize,int nType /*= 0*/ );
typedef void  ( *YlsExternFree )( void* pData, int nType /*= 0*/ );

#define _delObject(p)    { if(p) {delete p;   p = NULL; } }
#define _delArray(p)	 { if(p) {delete[] p; p = NULL; } }
#define _delArrayObj(p)  { for(int i = p.GetSize() - 1; i >= 0; i--) { delete p.GetAt(i); } p.RemoveAll(); }

#define YlsInvalidateMinValues 0x80000000
#define YlsInvalidateMaxValues 0x7fffffff

#ifndef PERIOD_TYPE_DAY
#define PERIOD_TYPE_DAY			0x0010		//分析周期：日
#define PERIOD_TYPE_MINUTE1		0x00C0		//分析周期：1分钟
#define PERIOD_TYPE_MINUTE5		0x0030		//分析周期：5分钟
#define PERIOD_TYPE_SECOND1		0x00E0		//分析周期：1秒钟
#endif	/*PERIOD_TYPE_DAY*/

#define PERIOD_TYPE_MINUTE15	0x0040		//分析周期：15分钟
#define HISDAY					0x0020		//分析周期：日
#define MINUTE30				0x0050		//分析周期：30分钟
#define MINUTE60				0x0060		//分析周期：60分钟
#define PERIOD_TYPE_MINUTE120	0x0070		//分析周期：120分钟
#define WEEK					0x0080		//分析周期：周
#define MONTH					0x0090		//分析周期：月

#define PERIOD_TYPE_DAY_ANY		0x00A0		//日线任意周期
#define MINUTE_ANY				0x00B0		//分钟任意周期
#define SECOND_ANY				0x00D0		//秒任意周期

//空值
#ifndef SS_MINTIME
#define SS_MINTIME		100000000		//最小时间
#endif

#define SI_VERSION			0xFF
#define SD_VERSION			1

#define PH_REPLY			0x8000		//应答
#define PH_ASK				0x4000		//请求
#define PH_ZIP				0x2000		//压缩数据
#define PH_HTML				0x1000		//超文本

//传输数据时，不压缩传输的最大长度，超过此长度后，尽量压缩。
#define TS_MAXUNZIPSIZE		(1024 * 5)

#define TEXTDATA				0x0B00		//文本信息
#define SHATEXTDATA				0x0B01		//上海证交所信息
#define SZNTEXTDATA				0x0B02		//深圳证交所信息
#define QLTEXTDATA				0x0B03		//乾隆信息
#define QSTEXTDATA				0x0B04		//券商信息
#define ZLTEXTDATA				0x0B05		//个股资料
#define QTTEXTDATA				0x0B06		//其他资料

#define DISKDATA				0x0C10		//用户端传给DISK的数据结构
#define WRITEDATA				0x0C11		//用户端接收到主站数据后，传给DISK的数据结构
#define ASKDATA					0x0C12		//用户端向DISK请求数据
#define PREASKDATA				0x0C13		//在有主站连接的情况下, 用户端向DISK请求数据

#define ST_BUCKETSIZE	    1000 // 明细缺省大小
#define HBS_BUCKETSIZE		100  // 买卖盘数据大小
#define MAX_TRACE			10   // 历史成交明细数据结构

#pragma	pack()
#endif // YLS_BASEDEFINE_H
