/*******************************************************************************
* Copyright (c)2003, 讯捷软件有限公司
* All rights reserved.
*
* 文件名称：HSCommunication.h
* 文件标识：dfx2003通讯协议
* 摘    要：dfx2003通讯协议
*
* 当前版本：dfx2003
* 作    者：讯捷王工
* 完成日期：2003-07
* 备	注：
*
* 修改记录：
* 日	期：2003-08-05
* 作	者：讯捷王工
* 修改内容：加入周期类型
*
* 日	期：2003-08-11
* 作	者：讯捷王工
* 修改内容：增加AnsFileTransferData，ReqFileTransferData结构
*
* 日	期：2003-08-20
* 作	者：
* 修改内容：修改动态数据请求掩码与结构一一对应
*
* 日	期：2003-08-25
* 作	者：
* 修改内容：修改动态行情，大单请求相关的请求、返回包结构
*
* 日	期：2003-09-01
* 作	者：
* 修改内容：增加RT_VALUE、RT_REQAUTOPUSH、RT_FILEDOWNLOAD,调整资讯相关请求
*
* 日	期：2003-09-08
* 作	者：
* 修改内容：调整所有结构的对齐字段在被对齐字段后
*
* 日	期：2003-09-24
* 作	者：
* 修改内容：增加除权数据增量请求
*
* 日	期：2004年2月26日
* 作	者：
* 修改内容：修改StockCompDayData结构，加入一数据项m_lNationalDebtRatio,
*			对于国债为利率，对于基金为净值，对于其它则无意义
*			无意义时，约定服务器必须将其设为0
*
* 日	期：2004年3月3日
* 作	者：
* 修改内容：加入新的请求类型RT_GENERALSORT_COMP,返回的是综合排名的组合包（后去除...）
*
* 日	期：2004-03-09
* 作	者：
* 修改内容：增加资讯相关的请求
*
* 日	期：2004年4月1日
* 作	者：
* 修改内容：加入新的请求类型RT_SERVERTIME,返回的是当前服务器的时间
*
* 日	期：2004年6月23日
* 作	者：
* 修改内容：加入实时解盘相关协议
*******************************************************************************/
#ifndef _HS_COMMUNICATION_H
#define _HS_COMMUNICATION_H

//#ifndef HS_SUPPORT_UNIX
#pragma	pack(1)
//#else
//#endif

/* 新版数据结构:客户端,服务端必须一致 */

#include "hsstruct.h"		

#include "levelhq.h"

/* 请求/返回类型 DEFINE BEGIN*/

#define RT_BEGIN			    		0x0100
#define RT_END				    		0x8FFF


#define RT_COMPASKDATA					0x8FFE  /* 组合请求类型						*/
#define RT_ZIPDATA						0x8001  /* 压缩返回包类型					*/


#define RT_JAVA_MARK					0x0010	/* JAVA登录 | RT_LOGIN_*			*/
#define RT_WINCE_MARK					0x0020	/* WINCE登录 | RT_LOGIN_*			*/
#define RT_NOTZIP						0x0040	/* 不使用压缩数据传输				*/


#define RT_INITIALINFO          		0x0101  /* 客户端数据所有初始化				*/
#define RT_LOGIN						0x0102  /* 客户端登录行情服务器				*/
#define RT_SERVERINFO					0x0103  /* 主站信息							*/
#define RT_BULLETIN						0x0104	/* 紧急公告(主推)					*/
#define RT_PARTINITIALINFO				0x0105	/* 客户端数据部分初始化				*/
#define RT_ETF_INIT		          		0x0106  /* 52只股票数据(ETF)				*/
#define RT_LOGIN_HK						0x0107	/* 客户端登录港股服务器				*/
#define RT_LOGIN_FUTURES				0x0108	/* 客户端登录期货服务器				*/
#define RT_LOGIN_FOREIGN				0x0109	/* 客户端登录外汇服务器				*/
#define RT_LOGIN_WP						0x010A	/* 客户端登录外盘服务器				*/
#define RT_LOGIN_INFO					0x010B	/* 客户端登录资讯服务器				*/
#define RT_CHANGE_PWD					0x010C	/* 修改密码							*/
#define RT_SERVERINFO2					0x010E  /* 主站信息2						*/
#define RT_VERIFYINFO					0x010F  /* 用户认证信息返回					*/
#define RT_LOGIN_HJ   					0x0111  /* 客户端登录黄金服务器   			*/

#define RT_REALTIME						0x0201  /* 行情报价表:1-6乾隆操作键			*/
#define RT_DYNREPORT					0x0202  /* 强弱分析;指标排序;热门板块分析;区间分析;跑马灯股票列表数据;预警	*/
#define RT_REPORTSORT					0x0203  /* 排名报价表:61-66、点击列排序		*/
#define RT_GENERALSORT					0x0204  /* 综合排名报表:81-86				*/
#define RT_GENERALSORT_EX				0x0205  /* 综合排名报表:81-86加入自定义分钟排名	*/
#define RT_SEVER_EMPTY					0x0206  /* 服务器无数据返回空包	*/
#define RT_SEVER_CALCULATE				0x0207  /* 服务器计算数据包,包括涨停、跌停	*/
#define RT_ANS_BYTYPE					0x0208  /* 根据类型返回数据包	*/
#define RT_QHMM_REALTIME				0x0209  /* 期货买卖盘	*/
#define RT_LEVEL_REALTIME				0x020A  /* level	*/
#define RT_CLASS_REALTIME				0x020B  /* 根据分类类别获取行情报价*/
#define RT_DAY_CURPOS					0x020C  /* 日线当前实际位置	*/


#define RT_TREND						0x0301  /* 分时走势							*/
#define RT_ADDTREND						0x0302  /* 走势图叠加、多股同列				*/
#define RT_BUYSELLPOWER					0x0303  /* 买卖力道							*/
#define RT_HISTREND						0x0304  /* 历史回忆;多日分时;右小图下分时走势*/
#define RT_TICK							0x0305  /* TICK图							*/
#define RT_ETF_TREND					0x0306  /* ETF分时走势						*/
#define RT_ETF_NOWDATA					0x0307  /* ETF时时数据						*/
#define RT_ETF_TREND_TECH				0x0308  /* ETFtech分时走势						*/
#define RT_HISTREND_INDEX				0x0309  /* 对于大盘领先-历史回忆;多日分时;右小图下分时走势*/


#define RT_TECHDATA						0x0400  /* 盘后分析							*/
#define RT_FILEDOWNLOAD					0x0401	/* 文件请求（盘后数据下载）			*/
#define RT_TECHDATA_EX					0x0402	/* 盘后分析扩展 -- 支持基金净值*/
#define RT_DATA_WEIHU					0x0403	/* 数据维护处理 */
#define RT_FILEDOWNLOAD2				0x0404	/* 下载服务器指定目录文件			*/
#define RT_FILED_CFG					0x0405	/* 配置文件升级/更新			    */
#define RT_FILL_DATA					0x0406	/* 补线处理 */
#define RT_TECHDATA_BYPERIOD			0x0407	/* 盘后分析扩展 -- 支持不同周期转换*/
#define RT_ONE_BLOCKDATA				0x0408	/* 一个板块数据请求 */
#define RT_TECHDATA_INCREMENT			0x0409	/* 盘后分析扩展 -- 增量数据请求    */
#define RT_TECHDATA_SrvBuildData		0x040A	/* 盘后分析	-- 支持服务器生成周期数据  */


#define RT_TEXTDATAWITHINDEX_PLUS		0x0501	/* 正序资讯索引数据					*/
#define RT_TEXTDATAWITHINDEX_NEGATIVE	0x0502	/* 倒序资讯索引数据					*/
#define RT_BYINDEXRETDATA				0x0503  /* 资讯内容数据						*/
#define RT_USERTEXTDATA		    		0x0504  /* 自定义资讯请求（如菜单等）		*/
#define RT_FILEREQUEST					0x0505  /* 配置文件文件						*/
#define RT_FILESimplify					0x0506  /* 精简文件请求						*/
#define RT_ATTATCHDATA					0x0507  /* 附件数据							*/
#define RT_PROMPT_INFO					0x0508	/* 服务器设置的提示信息				*/

#define RT_STOCKTICK					0x0601  /* 个股分笔、个股详细的分笔数据		*/
#define RT_BUYSELLORDER 				0x0602  /* 个股买卖盘						*/
#define RT_LIMITTICK            		0x0603  /* 指定长度的分笔请求				*/
#define RT_HISTORYTICK					0x0604  /* 历史的分笔请求					*/
#define RT_MAJORINDEXTICK				0x0605  /* 大盘明细							*/
#define RT_VALUE						0x0606	/* 右小图“值”						*/
#define RT_BUYSELLORDER_HK 				0x0607  /* 个股买卖盘(港股）				*/		
#define RT_BUYSELLORDER_FUTURES			0x0608  /* 个股买卖盘(期货）				*/		
#define RT_VALUE_HK						0x0609	/* 右小图“值”(港股),右小图也发此请求*/		
#define RT_VALUE_FUTURES				0x060A	/* 右小图“值”(期货),左下小图也发此请求*/		
#define RT_TOTAL						0x060B	/* 总持请求包 */
#define RT_LIMITTICK_Offset        		0x060C  /* 指定长度的分笔请求,可以通过偏移量*/

#define RT_LEAD							0x0702  /* 大盘领先指标						*/
#define RT_MAJORINDEXTREND				0x0703  /* 大盘走势							*/
#define RT_MAJORINDEXADL				0x0704  /* 大盘走势－ADL					*/
#define RT_MAJORINDEXDBBI	    		0x0705  /* 大盘走势－多空指标				*/
#define RT_MAJORINDEXBUYSELL    		0x0706  /* 大盘走势－买卖力道				*/
#define RT_SERVERFILEINFO    			0x0707  /* 服务器自动推送要更新的文件信息				*/
#define RT_DOWNSERVERFILEINFO    		0x0708  /* 下载-服务器自动推送要更新的文件信息				*/


#define RT_CURRENTFINANCEDATA			0x0801  /* 最新的财务数据					*/
#define RT_HISFINANCEDATA				0x0802  /* 历史财务数据						*/
#define RT_EXRIGHT_DATA					0x0803	/* 除权数据							*/
#define RT_HK_RECORDOPTION				0x0804	/* 港股期权							*/
#define RT_BROKER_HK					0x0805	/* 港股经纪席位下委托情况			*/				// 看我们的服务器是否生成此数据
#define RT_BLOCK_DATA					0x0806	/* 板块数据							*/
#define RT_STATIC_HK					0x0807	/* 港股静态数据						*/


#define RT_MASSDATA             		0x0901  /* 大单								*/
#define RT_SERVERTIME					0x0902  /* 服务器当前时间					*/
#define RT_KEEPACTIVE					0x0903  /* 保活通信包						*/
#define RT_TEST							0x0904	/* 测试通信包						*/
#define RT_TESTSRV						0x0905	/* 测试客户端到服务器是否通畅		*/
#define RT_PUSHINFODATA					0x0906	/* 资讯实时主推						*/
#define RT_TESTSRVLOAD					0x0907	/* 请求服务器当前负载情况			*/

#define RT_AUTOPUSH             		0x0A01	/* 常用主推							*/		// 改RealTimeData 为 CommRealTimeData
#define RT_AUTOPUSHSIMP         		0x0A02	/* 精简主推				*/					// 改为请求主推
#define RT_REQAUTOPUSH					0x0A03  /* 请求主推,应用于：预警、跑马灯	*/		// 改RealTimeData 为 CommRealTimeData
#define RT_ETF_AUTOPUSH					0x0A04  /* ETF主推	*/
#define RT_AUTOBROKER_HK				0x0A05	/* 经纪主推							*/
#define RT_AUTOTICK_HK					0x0A06	/* 港股分笔主推						*/
#define RT_AUTOPUSH_QH					0x0A07	/* 期货最小主推						*/
#define RT_PUSHREALTIMEINFO				0x0A08	/* 实时解盘主推						*/
#define RT_RAW_AUTOPUSH					0x0A09  /* 数据源原始数据主推	*/

#define RT_QHMM_AUTOPUSH				0x0A0A  /* 期货买卖盘主推	*/
#define RT_LEVEL_AUTOPUSH				0x0A0B  /* level主推	*/


#define RT_UPDATEDFINANCIALDATA			0x0B01	/* 增量的财务报表数据 */
#define RT_SYNCHRONIZATIONDATA			0x0B02	/* 数据同步处理 */

#define RT_Level_OrderQueue				0x0B03	// 买卖队列 - level2 买卖队列数据
#define RT_Level_Cancellation			0x0B04	// 撤单 - 单笔委托数量最大的10笔买/卖撤单
#define RT_Level_Consolidated			0x0B05	// 累计 - 撤消买入/卖出委托累计数量最多的前10只股票
#define RT_Level_LargeTick				0x0B06	// 成交逐笔

// 
#define RT_Send_Notice				    0x0C01 // 发表公告
#define RT_Send_ScrollText				0x0C02 // 发表滚动信息
#define RT_Change_program				0x0C03 // 更改服务器程序
#define RT_Send_File_Data				0x0C04 // 发送文件到服务器
#define RT_RequestDBF					0x0C05 // 请求DBF文件

#define RT_InfoSend						0x0C06  // 发布信息
#define RT_InfoUpdateIndex				0x0C07  // 更新信息索引
#define RT_InfoUpdateOneIndex			0x0C08  // 更新一条信息索引
#define RT_NoteMsgData					0x0C09	/* 定制短信数据传送 */
#define RT_InfoDataTransmit				0x0C0A  // 验证转发
#define RT_InfoCheckPurview				0x0C0B  // 返回注册详细分类信息
#define RT_InfoClickTime				0x0C0C  // 点击次数

#define RT_REPORTSORT_Simple			0x0D01  /* 排名报价表:61-66、点击列排序（精简）	*/
#define RT_PARTINITIALINFO_Simple		0x0D02  /* 代码返回	*/
#define RT_RETURN_EMPTY					0x0D03  /* 返回空的数据包	*/
#define RT_InfoDataRailing				0x0D04  // 请求栏目

// wince 相关
#define RT_WINCE_FIND					0x0E01 // 查找代码
#define RT_WINCE_UPDATE					0x0E02 // CE版本升级
#define RT_WINCE_ZIXUN					0x0E03 // CE资讯请求

#define RT_Srv_SrvStatus				0x0F01 // 后台程序运行状态

// wince 客户端使用的协议
#define Session_Socket					0x0001 // socket
#define Session_Http					0x0002 // http

#define WINCEZixun_StockInfo		    0x1000 // 个股资讯


// AskData 中 m_nOption 指向的类型

// 公告信息配置
#define Notice_Option_WinCE				0x0001 // 公告信息只对WinCE用户//
#define Notice_Option_SaveSrv			0x0002 // 公告信息在服务器自动保存。
#define Notice_Option_DayToSrv			0x0004 // 发送修改的数据到服务器

// 登陆...
#define Login_Option_Password			0x0004 // 登陆时使用新的加密方式。
#define Login_Option_NotCheck			0x0008 // 不检测用户。
#define Login_Option_SrvLoad			0x0010 // 需要服务器返回负载信息

// 日线除权是否放到后台
#define Login_Option_DayChuQuan_left	0x0020 // 左边除权
#define Login_Option_DayChuQuan_Back	0x0040 // 向后除权





// AskData 中 m_nOption 指向的类型,为子类型
#define ByType_LevelStatic				0x1000  // 数据类型 LevelStatic  
#define ByType_LevelRealTime			0x2000  // 数据类型 LevelRealTime  



// 市场到俺码转换
#define Market_STOCK_MARKET				0x0001	 // 股票
#define	Market_HK_MARKET				0x0002   // 港股
#define Market_WP_MARKET				0x0004   // 外盘
#define Market_FUTURES_MARKET			0x0008   // 期货
#define Market_FOREIGN_MARKET			0x0010   // 外汇
#define Market_HJ_MARKET			    0x0020   // 黄金   // added by Ben

#define Market_Address_Changed			0x0040   // 当前服务器需要地址切换
#define Market_Client_ForceUpdate		0x0080   // 当前客户端必须升级才能够使用
#define Market_DelayUser				0x0100   // 当前用户为延时用户，在港股连接时使用
#define Market_TestSrvData				0x0200   // 是否支持测试
#define Market_UserCheck				0x0400   // 返回数据中包含用户资讯权限信息,参见结构：SrvCheckInfo
#define Market_LOGIN_INFO				0x0800   // 资讯
#define Market_SrvLoad					0x1000   // 需要服务器返回负载信息,参见结构：TestSrvLoadData
#define Market_SrvCheckError			0x2000   // 登陆验证服务器失败
#define Market_SrvUsePeriodData			0x4000   // 服务器支持不同周期的K线数据，无需本地生成


// 当前客户端的语言编号

/*
各位含义表示如下：
23		  7				   0
|	  	  |				   |
|语言分类 |客户端内部版本号|
*/

#define Language_China					0x000000	// 当前为中文版
#define Language_English				0x000100	// 当前为英文版


//#define Market_STOCK_MARKET_CH		0x0100	 // 股票改变
//#define	Market_HK_MARKET_CH			0x0200   // 港股改变
//#define Market_WP_MARKET_CH			0x0400   // 外盘改变
//#define Market_FUTURES_MARKET_CH		0x0800   // 期货改变
//#define Market_FOREIGN_MARKET_CH		0x1000   // 外汇改变


// 服务器
//
#define RT_Srv_Sub_Restart		0x0001 // 重新启动程序
#define RT_Srv_Sub_Replace		0x0002 // 替换程序

#define RT_Srv_Sub_DownCFG		0x0003 // 下载配置文件
#define RT_Srv_Sub_UpCFG		0x0004 // 上传配置文件

#define RT_Srv_Sub_DownUserDB	0x0005 // 下载用户管理文件文件
#define RT_Srv_Sub_UpUserDB		0x0006 // 上传用户管理文件文件

#define RT_Srv_Sub_DownReport	0x0007 // 下载后台程序报告文件
#define RT_Srv_Sub_LimitPrompt	0x0008 // 权限错误提示


#define RT_Srv_Sub_UserAdd				0x0009 // 用户添加
#define RT_Srv_Sub_UserDelete			0x000A // 用户删除
#define RT_Srv_Sub_UserUpdate			0x000B // 用户修改
#define RT_Srv_Sub_UserKickOut			0x000C // 用户从服务器踢出
#define RT_Srv_Sub_UserCancelKickOut	0x000D // 取消踢出
#define RT_Srv_Sub_UserSendInfo			0x000E // 向用户发送信息
#define RT_Srv_Sub_UserGetList			0x000F // 获得用户列表
 


#define RT_Srv_Sub_Succ			0x1000 // 操作成功提示


/* 请求/返回 DEFINE END*/

/* 实时数据俺码　DEFINE BEGIN*/
#define MASK_REALTIME_DATA_OPEN					0X00000001      //今开盘
#define MASK_REALTIME_DATA_MAXPRICE				0X00000002      //最高价
#define MASK_REALTIME_DATA_MINPRICE				0X00000004      //最低价
#define MASK_REALTIME_DATA_NEWPRICE				0X00000008      //最新价

#define MASK_REALTIME_DATA_TOTAL				0X00000010      //成交量(单位:股)
#define MASK_REALTIME_DATA_MONEY				0X00000020	    //成交金额(单位:元)

#define MASK_REALTIME_DATA_BUYPRICE1			0x00000040	    // 买１价
#define MASK_REALTIME_DATA_BUYCOUNT1			0x00000080		// 买１量
#define MASK_REALTIME_DATA_BUYPRICE2			0x00000100	    // 买２价
#define MASK_REALTIME_DATA_BUYCOUNT2			0x00000200		// 买２量
#define	MASK_REALTIME_DATA_BUYPRICE3			0x00000400	    // 买３价
#define MASK_REALTIME_DATA_BUYCOUNT3			0x00000800		// 买３量
#define MASK_REALTIME_DATA_BUYPRICE4			0x00001000	    // 买４价
#define MASK_REALTIME_DATA_BUYCOUNT4			0x00002000		// 买４量
#define MASK_REALTIME_DATA_BUYPRICE5			0x00004000	    // 买５价
#define MASK_REALTIME_DATA_BUYCOUNT5			0x00008000		// 买５量

#define MASK_REALTIME_DATA_SELLPRICE1			0x00010000		// 卖１价
#define MASK_REALTIME_DATA_SELLCOUNT1			0x00020000		// 卖１量
#define MASK_REALTIME_DATA_SELLPRICE2			0x00040000		// 卖２价
#define MASK_REALTIME_DATA_SELLCOUNT2			0x00080000		// 卖２量
#define MASK_REALTIME_DATA_SELLPRICE3			0x00100000		// 卖３价
#define MASK_REALTIME_DATA_SELLCOUNT3			0x00200000		// 卖３量
#define MASK_REALTIME_DATA_SELLPRICE4			0x00400000		// 卖４价
#define MASK_REALTIME_DATA_SELLCOUNT4			0x00800000		// 卖４量
#define MASK_REALTIME_DATA_SELLPRICE5			0x01000000		// 卖５价
#define MASK_REALTIME_DATA_SELLCOUNT5			0x02000000		// 卖５量

#define MASK_REALTIME_DATA_PERHAND				0x04000000      //股/手 单位
#define MASK_REALTIME_DATA_NATIONAL_DEBT_RATIO  0x08000000      //国债利率
//以下为高32位  m_lReqMask1 对应StockOtherData结构
#define MASK_REALTIME_DATA_TIME					0x00000001      //距开盘分钟数
#define MASK_REALTIME_DATA_CURRENT				0x00000002	    //现手
#define MASK_REALTIME_DATA_OUTSIDE				0x00000004		//外盘
#define MASK_REALTIME_DATA_INSIDE				0x00000008		//内盘
#define MASK_REALTIME_DATA_OPEN_POSITION		0x00000010      //今开仓
#define MASK_REALTIME_DATA_CLEAR_POSITION		0x00000020      //今平仓
#define MASK_REALTIME_DATA_CODEINFO				0x00000040		//代码

// 增加列定义说明
#define MASK_REALTIME_DATA_BUYORDER1			0x00000080		// 买1盘数
#define MASK_REALTIME_DATA_BUYORDER2			0x00000100	    // 买2盘数
#define MASK_REALTIME_DATA_BUYORDER3			0x00000200		// 买3盘数
#define	MASK_REALTIME_DATA_BUYORDER4			0x00000400	    // 买4盘数
#define MASK_REALTIME_DATA_BUYORDER5			0x00000800		// 买5盘数

#define MASK_REALTIME_DATA_SELLORDER1			0x00001000	    // 卖1盘数
#define MASK_REALTIME_DATA_SELLORDER2			0x00002000		// 卖2盘数
#define MASK_REALTIME_DATA_SELLORDER3			0x00004000	    // 卖3盘数
#define MASK_REALTIME_DATA_SELLORDER4			0x00008000		// 卖4盘数
#define MASK_REALTIME_DATA_SELLORDER5			0x00010000		// 卖5盘数

#define MASK_REALTIME_DATA_SELLCOUNT1			0x00020000		// 卖１量
#define MASK_REALTIME_DATA_SELLPRICE2			0x00040000		// 卖２价
#define MASK_REALTIME_DATA_SELLCOUNT2			0x00080000		// 卖２量
#define MASK_REALTIME_DATA_SELLPRICE3			0x00100000		// 卖３价
#define MASK_REALTIME_DATA_SELLCOUNT3			0x00200000		// 卖３量
#define MASK_REALTIME_DATA_SELLPRICE4			0x00400000		// 卖４价
#define MASK_REALTIME_DATA_SELLCOUNT4			0x00800000		// 卖４量
#define MASK_REALTIME_DATA_SELLPRICE5			0x01000000		// 卖５价
#define MASK_REALTIME_DATA_SELLCOUNT5			0x02000000		// 卖５量

/* 实时数据俺码　DEFINE END*/

/* 综合排名排序类型掩码 DEFINE BEGIN*/
#define	RT_RISE					0x0001		//涨幅排名
#define	RT_FALL					0x0002		//跌幅排名
#define	RT_5_RISE				0x0004		//5分钟涨幅排名
#define	RT_5_FALL				0x0008		//5分钟跌幅排名
#define RT_AHEAD_COMM			0x0010		//买卖量差(委比)正序排名
#define RT_AFTER_COMM			0x0020		//买卖量差(委比)倒序排名
#define	RT_AHEAD_PRICE			0x0040		//成交价震幅正序排名
#define	RT_AHEAD_VOLBI			0x0080		//成交量变化(量比)正序排名
#define	RT_AHEAD_MONEY			0x0100		//资金流向正序排名
/* 综合排名排序类型掩码 DEFINE END*/

/* K线请求的周期类型 BEGIN*/
#define PERIOD_TYPE_DAY			0x0010		//分析周期：日
#define PERIOD_TYPE_SECOND1		0x00E0		//分析周期：1秒钟
#define PERIOD_TYPE_MINUTE1		0x00C0		//分析周期：1分钟
#define PERIOD_TYPE_MINUTE5		0x0030		//分析周期：5分钟
/* K线请求的周期类型 END*/


//验证数据
struct HSPrivateKey
{
	CodeInfo m_pCode;	// 商品代码

#ifndef HS_SUPPORT_UNIX

	HSPrivateKey()
	{
		memset(this,0,sizeof(HSPrivateKey));
	}

	// 操作符 复制数据
	const HSPrivateKey& operator=(const HSPrivateKey& data)
	{
		memcpy(&m_pCode,&data.m_pCode,sizeof(m_pCode));
		return *this;
	}
	// 操作符 复制数据
	const HSPrivateKey& operator=(const StockUserInfo& pStockCode)
	{
		memcpy(&m_pCode,&pStockCode.m_ciStockCode,sizeof(m_pCode));
		return *this;
	}
	// 操作符 复制数据
	const HSPrivateKey& operator=(const CodeInfo& pCode)
	{
		memcpy(&m_pCode,&pCode,sizeof(m_pCode));
		return *this;
	}
	// 操作符 复制数据
	const HSPrivateKey& operator=(const long& pStockCode);
	// 复制数据
	void Copy(const HSPrivateKey& data)
	{
		memcpy(&m_pCode,&data.m_pCode,sizeof(m_pCode));
	}
	// 复制数据
	void Copy(const CodeInfo& pCode)
	{
		memcpy(&m_pCode,&pCode,sizeof(m_pCode));
	}
	// 比较代码 返回TRUE or FALSE
	BOOL Compare(const CodeInfo& pCode);
	BOOL Compare(const CodeInfo* pCode);
	// 比较代码 返回TRUE or FALSE
	BOOL Compare(const StockUserInfo& pCode);
	BOOL Compare(const StockUserInfo* pCode);
	// 返回对应的StockUserInfo结构地址
	const StockUserInfo* GetStock();

#endif
};

/*
通讯包格式说明:

单包请求包结构
说明：
1、	m_nIndex、m_cOperor、m_lKey、m_nPrivateKey为客户端专用的一些信息，
服务器端处理时直接拷贝返回,下同。
2、	宏定义：HS_SUPPORT_UNIX_ALIGN为使用于UNIX服务器4字节对齐使用，下同。
3、	所有请求都发送此包，根据m_nType类型具体情况来确定m_nSize和m_pCode[1]
内容来实现各种各样的请求。
4、	常用请求：指的是m_nSize取值为n个，m_pCode[1]内容只有n个CodeInfo，
即只请求n个股票数据，根据m_nType来识别请求类型。
*/
struct AskData
{
	unsigned short 		m_nType;	     // 请求类型
	char				m_nIndex;     	 // 请求索引，与请求数据包一致

	union
	{
		struct
		{
			char			m_cNotEmptyPacket:2;    // 客户端使用，服务器：=1时，当前请求包不能清，=0时，清除
			char			m_cOperator:6;	        // 客户端使用，当前所属的服务器类别，指向CEV_Connect_HQ_等的定义。
		};
		char			m_cSrv;						// 服务器使用
	};

	long				m_lKey;		 	 // 一级标识，通常为窗口句柄
	HSPrivateKey	    m_nPrivateKey;	 // 二级标识

	short     			m_nSize;         // 请求证券总数，小于零时，

	// 其绝对值代表后面的字节数
	unsigned short		m_nOption;       // 为了4字节对齐而添加的字段

	CodeInfo			m_pCode[1];      // 证券信息

	AskData()
	{
		Emtpy();
	}

	void Emtpy()
	{
		m_nType     = 0;
		m_cSrv      = 0;
		m_nSize     = 0;
		m_lKey      = 0;
		m_nOption   = 0;
	}

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			//YlsShortIntelToComputer(m_nType);
			m_lKey = YlsIntIntelToComputer(m_lKey);
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nOption = YlsShortIntelToComputer(m_nOption);			
		}
		else
		{
			m_nType = YlsShortComputerToIntel(m_nType);
			m_lKey = YlsIntComputerToIntel(m_lKey);
			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nOption = YlsShortComputerToIntel(m_nOption);
		}
		m_nPrivateKey.m_pCode.To(cIntelToComputer);
#endif
	}

};

//组合包请求格式
struct CompAskData               
{
	unsigned short	m_nType;	      // 请求类型 = COMPASKDATA

	char			m_nIndex;		  // 请求索引，与请求数据包一致

	union
	{
		struct
		{
			char			m_cNotEmptyPacket:2;   // 客户端使用，服务器：=1时，当前请求包不能清，=0时，清除
			char			m_cOperator:6;   // 客户端使用，当前所属的服务器类别，指向CEV_Connect_HQ_等的定义。
		};
		char			m_cSrv;          // 服务器使用
	};

	long			m_lKey;			  // 一级标识，通常为窗口句柄
	HSPrivateKey	m_nPrivateKey;    // 二级标识

	short			m_nAsk;		      // 请求数据包的个数
	short			m_nLength[1];     // 每个请求数据包的长度，有 m_nAsk	个

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		int i;

		if( cIntelToComputer )
		{
			//YlsShortIntelToComputer(m_nType);
			m_lKey = YlsIntIntelToComputer(m_lKey);
			m_nAsk = YlsShortIntelToComputer(m_nAsk);

			for(i = 0; i < m_nAsk; i++ )
			{
				m_nLength[i] = YlsShortIntelToComputer(m_nLength[i]);
			}
		}
		else
		{
			m_nType = YlsShortComputerToIntel(m_nType);
			m_lKey = YlsIntComputerToIntel(m_lKey);
			m_nAsk = YlsShortComputerToIntel(m_nAsk);

			for(i = 0; i < m_nAsk; i++ )
			{
				m_nLength[i] = YlsShortComputerToIntel(m_nLength[i]);
			}
		}
		m_nPrivateKey.m_pCode.To(cIntelToComputer);
#endif
	}

};

//压缩返回包格式
struct TransZipData
{
	unsigned short	m_nType;		// 请求类型,恒为RT_ZIPDATA

	short 			m_nAlignment;	// 为了4字节对齐而添加的字段

	long			m_lZipLen;		// 压缩后的长度
	long			m_lOrigLen;		// 压缩前的长度
	char		    m_cData[1];		// 压缩后的数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			//YlsShortIntelToComputer(m_nType);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
			m_lZipLen = YlsIntIntelToComputer(m_lZipLen);
			m_lOrigLen = YlsIntIntelToComputer(m_lOrigLen);			
		}
		else
		{
			m_nType = YlsShortComputerToIntel(m_nType);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
			m_lZipLen = YlsIntComputerToIntel(m_lZipLen);
			m_lOrigLen = YlsIntComputerToIntel(m_lOrigLen);
		}
#endif
	}

};

//返回包头结构
struct DataHead
{
	unsigned short		m_nType;         // 请求类型，与请求数据包一致
	char				m_nIndex;     	 // 请求索引，与请求数据包一致

	union
	{
		struct
		{
			char			m_cNotEmptyPacket:2;   // 客户端使用，服务器：=1时，当前请求包不能清，=0时，清除
			char			m_cOperator:6;   // 客户端使用，当前所属的服务器类别，指向CEV_Connect_HQ_等的定义。
		};
		char			m_cSrv;          // 服务器使用
	};

	//union
	//{
	//struct
	//{
	long				m_lKey;		 	 // 一级标识，通常为窗口句柄
	HSPrivateKey		m_nPrivateKey;	 // 二级标识
	//};

	//long					m_nPushType;	 // 对于精简主推市场类型
	//};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			//YlsShortIntelToComputer(m_nType);
			m_lKey = YlsIntIntelToComputer(m_lKey);
		}
		else
		{
			m_nType = YlsShortComputerToIntel(m_nType);
			m_lKey = YlsIntComputerToIntel(m_lKey);
		}
		m_nPrivateKey.m_pCode.To(cIntelToComputer);
#endif
	}
};


/*
以下为请求应答包结构详细说明
*/

// RT_NoteMsgData

// 请求
struct NoteMsgDataReq
{
	int  m_nType;		// 数据类型
	int  m_nSize;		// 数据长度
	char m_cData[1];    // 具体数据根据需要定义,服务器不做任何处理
};

// 应答
struct NoteMsgDataAns
{
	DataHead m_dhHead;	// 数据报头

	int  m_nType;		// 数据类型
	int  m_nSize;		// 数据长度
	char m_cData[1];	// 具体数据根据需要定义,服务器不做任何处理
};


/*
请求类型: RT_LOGIN、RT_LOGIN_INFO、RT_LOGIN_HK、RT_LOGIN_FUTURES、RT_LOGIN_FOREIGN
功能说明: 客户端登录请求
备	  注: 
*/
/* 请求结构 */
struct ReqLogin
{
	char			m_szUser[64];	// 用户名
	char			m_szPWD[64];	// 密码(加密密文），详细参加协议
};

/* 请求结构 */
struct ReqChangePassword
{
	char			m_szUser[64];	// 用户名
	char			m_szOldPWD[64];	// 密码(加密密文），详细参加协议
	char			m_szNewPWD[64];	// 密码(加密密文），详细参加协议
};

#define AnsLogin_Normal 0x0001   // 一般用户
#define AnsLogin_Midlle 0x0002   // 中级用户
#define AnsLogin_Hight  0x0004   // 高级用户

/* 返回结构 */
struct AnsLogin0
{
	DataHead		m_dhHead;	//数据报头

	long			m_nError:2;	// 错误号 见RT_LOGIN说明1
	long			m_nSize:30;	// 长度

	char			m_szRet[1];	// 配置文件数据或者返回错误信息字符串 见RT_LOGIN说明1
};

struct AnsLogin
{
	DataHead		m_dhHead;	//数据报头

	//long			m_nError:2;	// 错误号 见RT_LOGIN说明1
	//long			m_nSize:30;	// 长度

	short			m_nError;
	short 			m_nAlignment;	// 为了4字节对齐而添加的字段
	long			m_nSize;
	char			m_szRet[1];	// 配置文件数据或者返回错误信息字符串 见RT_LOGIN说明1
};
/*
RT_LOGIN说明1:
１、m_nError 等于0，则m_szRet为配置文件数据。
２、m_nError 小于0，则m_szRet为服务器返回错误信息字符串。
３、m_nError 等于ERROR_*(错误ID)，则m_szRet为空。
*/


/*
请求类型: RT_INITIALINFO
功能说明: 代码表的验证和初始化
备	  注: 
*/

/*
请求结构：
代码表的验证和初始化请求
*/
struct ReqInitSrv
{
	short            m_nSrvCompareSize;		// 服务器比较个数
	short 			 m_nAlignment;    		// 为了4字节对齐而添加的字段
	ServerCompare    m_sServerCompare[1];   // 服务器比较信息

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSrvCompareSize = YlsShortIntelToComputer(m_nSrvCompareSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
			for( int i = 0; i < m_nSrvCompareSize; i++ )
			{
				m_sServerCompare[i].To(cIntelToComputer);
			}
		}
#endif
	}
};

/*
返回结构：
代码表的验证和初始化应答
股票初始化信息
*/
/* 单个股票信息 */
struct StockInitInfo
{
	char		m_cStockName[STOCK_NAME_SIZE];	// 股票名称
	CodeInfo	m_ciStockCode;		// 股票代码结构
	long		m_lPrevClose;		// 昨收
	long		m_l5DayVol;			// 5日量(是否可在此加入成交单位？？？？）

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN

		m_ciStockCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lPrevClose = YlsIntIntelToComputer(m_lPrevClose);
			m_l5DayVol = YlsIntIntelToComputer(m_l5DayVol);
		}
		else
		{
			m_lPrevClose = YlsIntComputerToIntel(m_lPrevClose);
			m_l5DayVol = YlsIntComputerToIntel(m_l5DayVol);
		}		
#endif
	}
};

struct StockInitInfoSimple
{	
	CodeInfo	m_ciStockCode;		// 股票代码结构
	long		m_lPrevClose;		// 昨收
	long		m_l5DayVol;			// 5日量(是否可在此加入成交单位？？？？）
	short		m_nSize;			// 名称长度
	char		m_cStockName[STOCK_NAME_SIZE];	// 股票名称

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN

		m_ciStockCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lPrevClose = YlsIntIntelToComputer(m_lPrevClose);
			m_l5DayVol = YlsIntIntelToComputer(m_l5DayVol);
		}
		else
		{
			m_lPrevClose = YlsIntComputerToIntel(m_lPrevClose);
			m_l5DayVol = YlsIntComputerToIntel(m_l5DayVol);
		}		
#endif
	}
};

/* 单个市场包含的信息 */
struct OneMarketData
{
	CommBourseInfo  m_biInfo;		 // 市场信息

	short           m_nSize;        // 股票个数据
	short 		    m_nAlignment;    // 为了4字节对齐而添加的字段
	StockInitInfo   m_pstInfo[1];    // (m_biInfo）里指定分类的代码数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{			
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_pstInfo[i].To(cIntelToComputer);
			}			
		}		
#endif
	}
};

#define AnsInitialData_All 0x0002  // 当前市场所有分类数据

/* 返回结构 */
struct  AnsInitialData  
{
	DataHead		m_dhHead;		// 数据报头

	short		    m_nSize;		// 市场个数
	union
	{
		short 			m_nAlignment;   // 是否为主推初始化包(0：请求初始化包，非0：主推初始化包)
		short			m_nOpertion;    // 返回选项,参见:AnsInitialData_All 定义
	};
	OneMarketData   m_sOneMarketData [1]; // 市场数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}		
#endif
	}
};
/*
代码表初始化说明：
代码表初始化校验方式：校验每个分类的CRC（分类即最低级的品种）。
代码表初始化数据包被服务器推送的情况有以下两种：
1.客户端边上初始化，此类情况分：
a.某个市场所有品种校验相同，则不返回代码表。
b.某个市场中某些品种校验不同，则只返回不同品种的品种信息及品种代码表。
c.某个市场所有品种校验不同，则返回所有市场信息
2.服务器代码表变动时（如清盘），主推代码表，则中给客户端推送变
动品种的品种信息及品种代码表。并且，所有品种按市场归类，同类的品种
组成一个OneMarketData返回。

注：说明中提到的“品种信息”指StockType，
“品种代码表”指CommBourseInfo指定品种包含的所有代码,存放于OneMarketData::m_pstInfo
*/

/*
请求类型: RT_PARTINITIALINFO
功能说明: 代码表的部分初始化主推
备	  注: 
*/
/* 请求结构：无 */
/* 返回结构 */
struct  AnsPartInitialData  
{
	DataHead		m_dhHead;		// 数据报头

	short		    m_nSize;		// 市场个数
	short 			m_nAlignment;   // 是否为主推初始化包(0：请求初始化包，非0：主推初始化包)
	StockInitInfo   m_sStockInfo[1]; // 市场数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_sStockInfo[i].To(cIntelToComputer);
			}

			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};

struct  AnsPartInitialDataSimple  
{
	DataHead			  m_dhHead;		   // 数据报头

	short				  m_nSize;		   // 市场个数
	short 				  m_nAlignment;    // 是否为主推初始化包(0：请求初始化包，非0：主推初始化包)
	StockInitInfoSimple   m_sStockInfo[1]; // 市场数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_sStockInfo[i].To(cIntelToComputer);
			}

			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};

/*
请求类型: RT_SERVERINFO
功能说明: 主站信息
备	  注: 
*/
/* 请求结构 : 常用请求*/
/* 
返回结构 :
主站返回信息结构
*/

#define AnsServerInfo_SupportMarket  0x0001 // 支持分类代码请求

struct AnsServerInfo
{
	DataHead	m_dhHead;			// 数据报头
	char		m_pName[32];		// 服务器名
	char		m_pSerialNo[12];    // 序列号，验证正版性
	long		m_lTotalCount;		// 已连接过的总数

	long		m_lToDayCount;		// 当日连接总数
	long		m_lNowCount;		// 当前连接数

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lTotalCount = YlsIntIntelToComputer(m_lTotalCount);
			m_lToDayCount = YlsIntIntelToComputer(m_lToDayCount);
			m_lNowCount = YlsIntIntelToComputer(m_lNowCount);
		}
		else
		{
			m_lTotalCount = YlsIntComputerToIntel(m_lTotalCount);
			m_lToDayCount = YlsIntComputerToIntel(m_lToDayCount);
			m_lNowCount = YlsIntComputerToIntel(m_lNowCount);
		}
#endif
	}

};


struct AnsServerInfo2
{
	DataHead	m_dhHead;			// 数据报头

	long		m_lTotalCount;		// 已连接过的总数

	char		m_strAddr[20];      // ip  127.123.123.123
	short		m_nPort;			// 下个连接端口

	short		m_nMaxCount;

	long		m_lResever[2];		//

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lTotalCount = YlsIntIntelToComputer(m_lTotalCount);
			m_nPort = YlsShortIntelToComputer(m_nPort);
			m_nMaxCount = YlsShortIntelToComputer(m_nMaxCount);
			for( int i = 0; i < 2; i++ )
				m_lResever[i] = YlsIntIntelToComputer(m_lResever[i]);
		}
		else
		{
			m_lTotalCount = YlsIntComputerToIntel(m_lTotalCount);
			m_nPort = YlsShortComputerToIntel(m_nPort);
			m_nMaxCount = YlsShortComputerToIntel(m_nMaxCount);
			for( int i = 0; i < 2; i++ )
				m_lResever[i] = YlsIntComputerToIntel(m_lResever[i]);
		}
#endif
	}
};

/*
请求类型: RT_BULLETIN 
功能说明: 主推紧急公告
备	  注: 
*/
/* 请求结构 : 无请求*/
/* 返回结构 */
struct AnsBulletin
{
	DataHead		m_dhHead;		//数据报头

	long			m_nSize;		//公告内容长度	
	char			m_cData[1];		//公告内容

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};



//==========================================================================================
//==================================================改动处==================================
//==========================================================================================
/*
请求类型: RT_REALTIME 
功能说明: 行情报价表--1-6乾隆操作键
备	  注: 
*/
/* 请求结构 : 常用请求*/
/* 行情报价表数据项 */

//#ifdef HS_SUPPORT_UNIX // {{{
//#define CommRealTime_Macro	RealTimeData
#define CommRealTime_Macro	CommRealTimeData

#define RealTimeData CommRealTimeData

#ifndef RealTimeData
struct RealTimeData // 保有原有的，先期调试用
{
	CodeInfo		m_ciStockCode;		// 股票代码
	StockOtherData	m_othData;			// 实时其它数据
	union
	{
		HSStockRealTime	 m_nowData;		// 个股实时基本数据
		HSIndexRealTime  m_indData;		// 指数实时基本数据
	};	
};
#endif


// #define RT_CLASS_REALTIME				0x020B  /* 根据分类类别获取行情报价*/
struct ClassRealtime
{
	short			    m_nType;		// 0、不操作;1、自动主推数据;
	short				m_nSize;
	HSMarketDataType	m_cCodeType[1];	// 证券类型
};


// 空值,完全为参照使用,注意不要作为其他用途
struct CommRealTimeDataEmpty
{
	CodeInfo		  m_ciStockCode;		// 股票代码
	StockOtherData	  m_othData;			// 实时其它数据

	ShareRealTimeData m_sEmpty;
};
//#else
//#define CommRealTime_Macro	RealTimeData
////#define CommRealTime_Macro	CommRealTimeData
//struct RealTimeData // 保有原有的，先期调试用
//{
//	CodeInfo		m_ciStockCode;		// 股票代码
//	StockOtherData	m_othData;			// 实时其它数据
//	union
//	{
//		HSStockRealTime	 m_nowData;		// 个股实时基本数据
//		HSIndexRealTime  m_indData;		// 指数实时基本数据
//	};	
//};
//#endif	// }}}

static void YlsConvertNowTo( char cIntelToComputer,CodeInfo* pCode,void* pData )
{
#ifdef WORDS_BIGENDIAN

	if( pCode == NULL || pData == NULL )
		return;

	switch(MakeMarket(pCode->m_cCodeType))
	{
	case (HSMarketDataType)STOCK_MARKET:		         // 股票
		if( MakeIndexMarket(pCode->m_cCodeType) ) // 指数实时基本数据
		{
			HSIndexRealTime* pNow = (HSIndexRealTime*)pData;
			pNow->To(cIntelToComputer);
		}
#ifdef Support_MakeETF
		else if( MakeETF(pCode->m_cCodeType) )
		{
			ETFStockNowData* pNow = (ETFStockNowData*)pData;
			pNow->To(cIntelToComputer);
		}
#endif
		else
		{
			HSStockRealTime* pNow = (HSStockRealTime*)pData;
			pNow->To(cIntelToComputer);
		}
		break;			
	case (HSMarketDataType)HK_MARKET:				 // 港股
		{
			HSHKStockRealTime* pNow = (HSHKStockRealTime*)pData;
			pNow->To(cIntelToComputer);
		}
		break;
	case (HSMarketDataType)FUTURES_MARKET:			 // 期货
	case (HSMarketDataType)WP_MARKET:
		{
			HSQHRealTime* pNow = (HSQHRealTime*)pData;
			pNow->To(cIntelToComputer);
		}
		break;
	case (HSMarketDataType)FOREIGN_MARKET:			 // 外汇
		{
			HSWHRealTime* pNow = (HSWHRealTime*)pData;
			pNow->To(cIntelToComputer);
		}
		break;
	default:
		break;
	}
#endif
}

#ifdef WORDS_BIGENDIAN
	#define	YlsNowTo(cFlag,pCode,pData)	 YlsConvertNowTo(cFlag,pCode,pData)
#else
	#define	YlsNowTo(cFlag,pCode,pData)
#endif

// 
struct CommRealTimeData
{	
	CodeInfo		m_ciStockCode;		// 股票代码

	//union
	//{
	//struct
	//{
	StockOtherData	m_othData;			// 实时其它数据
	char			m_cNowData[1];		// 指向ShareRealTimeData的任意一个
	//};
	//char	m_cData[1]; // 只对精简推送数据
	//};

	//#ifndef HS_SUPPORT_UNIX
	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
		}
		else
		{
			switch(MakeMarket(m_ciStockCode.m_cCodeType))
			{
			case (HSMarketDataType)STOCK_MARKET:		         // 股票
				if( MakeIndexMarket(m_ciStockCode.m_cCodeType) ) // 指数实时基本数据
				{
					HSIndexRealTime* pNow = (HSIndexRealTime*)m_cNowData;
					pNow->To(cIntelToComputer);
				}
#ifdef Support_MakeETF
				else if( MakeETF(m_ciStockCode.m_cCodeType) )
				{
					ETFStockNowData* pNow = (ETFStockNowData*)m_cNowData;
					pNow->To(cIntelToComputer);
				}
#endif
				else
				{
					HSStockRealTime* pNow = (HSStockRealTime*)m_cNowData;
					pNow->To(cIntelToComputer);
				}
				break;			
			case (HSMarketDataType)HK_MARKET:				 // 港股
				{
					HSHKStockRealTime* pNow = (HSHKStockRealTime*)m_cNowData;
					pNow->To(cIntelToComputer);
				}
				break;
			case (HSMarketDataType)FUTURES_MARKET:			 // 期货
			case (HSMarketDataType)WP_MARKET:
				{
					HSQHRealTime* pNow = (HSQHRealTime*)m_cNowData;
					pNow->To(cIntelToComputer);
				}
				break;
			case (HSMarketDataType)FOREIGN_MARKET:			 // 外汇
				{
					HSWHRealTime* pNow = (HSWHRealTime*)m_cNowData;
					pNow->To(cIntelToComputer);
				}
				break;
			default:
				break;
			}

			m_ciStockCode.To(cIntelToComputer);
			m_othData.To(cIntelToComputer);
		}
#endif
	}

	// 根据代码得到下一个位置ptr
	CommRealTimeData* GetNext(CodeInfo* pCode,int& nNowSize,int* pTotal = NULL,int nFixSize = 0)
	{
		if( pCode == NULL )
			return this;

		if( nFixSize != 0 )
			nNowSize = nFixSize;
		else
		{
			nNowSize = GetStructSize( pCode );
			if( nNowSize == 0 )
				return this;
		}

		short nSize = nNowSize + GetAddSize();
		if( pTotal )
			*pTotal += nSize;

		char* pp = (char*)this;
		pp += nSize;

		return (CommRealTimeData*)pp;
	}

	ShareRealTimeData* GetShareData()
	{
		return (ShareRealTimeData*)m_cNowData;
	}

	static int GetAddSize()
	{
		return (sizeof(CommRealTimeData) - sizeof(char));//(sizeof(CodeInfo) + sizeof(StockOtherData));
	}

	// 结构大小(目前只支持相同结构处理，否则错误)
	static int GetStructSize(CodeInfo* pCode,int nAdd = 0)
	{
		if( pCode == NULL )
			return 0;

		switch(MakeMarket(pCode->m_cCodeType))
		{
		case (HSMarketDataType)STOCK_MARKET:		     // 股票
			if( MakeIndexMarket(pCode->m_cCodeType) )
				return (sizeof(HSIndexRealTime) + nAdd); // 指数实时基本数据
#ifdef Support_MakeETF
			else if( MakeETF(pCode->m_cCodeType) )
				return (sizeof(ETFStockNowData) + nAdd);
#endif
			return (sizeof(HSStockRealTime) + nAdd);
		case (HSMarketDataType)HK_MARKET:				 // 港股
			return (sizeof(HSHKStockRealTime) + nAdd);
		case (HSMarketDataType)FUTURES_MARKET:			 // 期货
		case (HSMarketDataType)WP_MARKET:
		case (HSMarketDataType)HJ_MARKET:			     // 黄金 // modified by Ben 20100506
			{
				if (IS_CURR_GOLD(pCode->m_cCode, pCode->m_cCodeType) ||
					MakeMainMarket(pCode->m_cCodeType) == (WP_MARKET | WP_INDEX))
					return (sizeof(HSStockRealTime) + nAdd);
				else
				    return (sizeof(HSQHRealTime) + nAdd);
			}
			break;			
		case (HSMarketDataType)FOREIGN_MARKET:			 // 外汇
			return (sizeof(HSWHRealTime) + nAdd);
		default:
			break;
		}

		return 0;
	}

	//#endif
};


/* 返回结构 */
struct AnsRealTime 
{
	DataHead				m_dhHead;		 // 数据报头
	short					m_nSize;		 // 报价表数据个数
	short 					m_nAlignment;    // 为了4字节对齐而添加的字段
	CommRealTimeData	  	m_pnowData[1];	 // 报价表数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);			
		}
		else
		{
			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
}; 
/*
说明：
CommRealTimeData将为一个不定长结构，具体分解及组合方法如下：
if( m_ciStockCode.是港股或港指() )
{
HSHKStockRealTime* pHKRealTime = (HSHKStockRealTime*)m_cNowData;
}
else if( m_ciStockCode.是期货() )
{
HSQHRealTime* pQHRealTime = (HSQHRealTime*)m_cNowData;
}
else if( m_ciStockCode.是国内股票() )
{
HSStockRealTime* pStockRealTime = (HSStockRealTime*)m_cNowData;
}
else if( m_ciStockCode.是国内指数() )
{
HSIndexRealTime* pIndexRealTime = (HSIndexRealTime*)m_cNowData;
}
else if( m_ciStockCode.是外汇() )
{
HSWHRealTime* pWHRealTime = (HSWHRealTime*)m_cNowData;
}
*/


/*
请求类型: RT_DYNREPORT 
功能说明: 
1.	强弱分析
2.	指标排序
3.	热门板块分析
4.	区间分析
5.	跑马灯股票列表数据
6.	预警
7.	星空图
备	  注: 
*/
/* 请求结构 */
struct ReqDynReportData
{
	long                m_lReqMask0;	// 掩码 0-31位
	long                m_lReqMask1;	// 掩码 32-63位 

	HSMarketDataType	m_cCodeType;	// 类别，见下面说明
	short				m_nSize;		// 后续代码长度对齐

	CodeInfo			m_pCode[1];		// 股票列表

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lReqMask0 = YlsIntIntelToComputer(m_lReqMask0);
			m_lReqMask1 = YlsIntIntelToComputer(m_lReqMask1);

			m_cCodeType = YlsShortIntelToComputer(m_cCodeType);
			m_nSize = YlsShortIntelToComputer(m_nSize);

			for( int i = 0; i < m_nSize; i++ )
			{		
				m_pCode[i].To(cIntelToComputer);
			}
		}
		else
		{
			for( int i = 0; i < m_nSize; i++ )
			{		
				m_pCode[i].To(cIntelToComputer);
			}

			m_lReqMask0 = YlsIntComputerToIntel(m_lReqMask0);
			m_lReqMask1 = YlsIntComputerToIntel(m_lReqMask1);

			m_cCodeType = YlsShortIntelToComputer(m_cCodeType);
			m_nSize = YlsShortIntelToComputer(m_nSize);
		}
#endif
	}
};
/* 返回结构 ：
说明:
1、	m_cCodeType 可参考RT_REPORTSORT说明
2、	m_lReqMask0为0-31bit，m_lReqMask1为32-63bit
3、	每一块数据以代码CodeInfo起始，后接数据；
数据单位为4字节长度，不足4字节则作补零处理;
返回数据按照低位至高位的顺序排列数据
4、	代码为固定返回数据内容

*/
struct AnsDynamicData
{
	DataHead			m_dhHead;		//数据报头
	long				m_lReqMask0; 	//当前要返回的结构俺码
	long				m_lReqMask1; 	//当前要返回的结构俺码

	unsigned long		m_nSize;		//数据长度
	char				m_cData[1];		//数据地址

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lReqMask0 = YlsIntIntelToComputer(m_lReqMask0);
			m_lReqMask1 = YlsIntIntelToComputer(m_lReqMask1);

			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_lReqMask0 = YlsIntComputerToIntel(m_lReqMask0);
			m_lReqMask1 = YlsIntComputerToIntel(m_lReqMask1);

			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};


/*
请求类型: RT_REPORTSORT 
功能说明: 
1、排名报价表（61-66乾隆操作键，下同）
2、点击列排序
备	  注: 
*/
/*（排名报价表--61-66、点击列排序）
请求结构
说明：
m_cCodeType有以下几种分类：
1、	标准分类：上A、深A
m_nSize = 0，m_sAnyReportData不指向任何东西
2、	系统板块：SYSBK_BOURSE
m_sAnyReportData指向ReqOneBlock
注：目前版本不进行板块CRC校验，直接发送报价数据。
3、	自选股和自定义板块（USERDEF_Bourse） 
m_sAnyReportData指向AnyReportData
4、	“所有A股”等
HSMarketDataType为二级分类取或运算，例如“所有A股”可以表示为：
STOCK_MARKET| SH_BOURSE| SZ_BOURSE| KIND_STOCKA
*/
/* 请求结构 */
struct AnyReportData
{
	CodeInfo		m_ciStockCode;	//股票代码

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_ciStockCode.To(cIntelToComputer);
#endif
	}
};

struct ReqAnyReport
{
	HSMarketDataType	m_cCodeType; 		// 类别，见RT_REPORTSORT说明1
	short				m_nBegin;			// 显示开始
	short				m_nCount; 			// 显示个数
	char				m_bAscending;		// 升序/降序
	char 				m_cAlignment;		//为了4字节对齐而添加的字段
	int					m_nColID;			// 排名列id 

	short				m_nSize;			// 个数
	short				m_nAlignment;		//为了4字节对齐而添加的字段
	AnyReportData		m_sAnyReportData[1];/*客户端给参考数据给服务器端
											见RT_REPORTSORT说明1*/

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_cCodeType = YlsShortIntelToComputer(m_cCodeType);
			m_nBegin = YlsShortIntelToComputer(m_nBegin);
			m_nCount = YlsShortIntelToComputer(m_nCount);
			m_nColID = YlsIntComputerToIntel(m_nColID);

			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);

			for(int i = 0; i < m_nSize; i++ )
			{
				m_sAnyReportData[i].To(cIntelToComputer);
			}
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_sAnyReportData[i].To(cIntelToComputer);
			}

			m_cCodeType = YlsShortComputerToIntel(m_cCodeType);
			m_nBegin = YlsShortComputerToIntel(m_nBegin);
			m_nCount = YlsShortComputerToIntel(m_nCount);
			m_nColID = YlsIntComputerToIntel(m_nColID);

			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};

// RT_REPORTSORT_Simple

struct CommRealTimeData_Simple
{	
	CodeInfo m_ciStockCode;		// 股票代码
	
	long	 m_lPrevClose;		// 昨收
	char	 m_szValue[12];

	short	 m_nSize;			// 大小
	char	 m_szName[8];		// 名称	
};
		
struct AnsReportData_Simple 
{
	DataHead					m_dhHead;			// 数据头

	short						m_nSize;			// 数据个数
	CommRealTimeData_Simple 	m_prptData[1];		// 数据
};


/*
RT_REPORTSORT说明1:
m_cCodeType有以下几种分类：
1、	标准分类：上A、深A
m_nSize = 0，m_sAnyReportData不指向任何东西
2、	系统板块：SysBK_Bourse -- 当前版本暂时不支持验证板块。
m_sAnyReportData指向ReqOneBlock
板块文件采用配置文件＋单个文件方式，客户端请求时将板块CRC校验码发送给服务器，服务器	将服务器板块CRC与客户端板块CRC进行检查，如果两者不匹配，则发送系统板块压缩数据包；然后发送报价数据，否则直接发送报价数据。
3、	自选股和自定义板块：UserDefBk_Bourse  
m_sAnyReportData指向AnyReportData
*/

#define BLOCK_NAME_LENGTH		32			// 板块名称长度
/* 请求结构 单个板块请求*/
struct ReqOneBlock
{
	long   m_lCRC;            // 板块CRC
	char   m_szBlockName[BLOCK_NAME_LENGTH];  // 板块名
};

/* 返回结构 */
struct AnsReportData 
{
	DataHead		m_dhHead;			// 数据头

	short			m_nSize;			// 数据个数
	short 			m_nAlignment;		// 为了4字节对齐而添加的字段
	CommRealTimeData 	m_prptData[1];		// 数据	

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};


/*
请求类型: RT_GENERALSORT
功能说明: 综合排名报表
备	  注: 
*/
/* 请求结构 */
struct ReqGeneralSort
{
	HSMarketDataType m_cCodeType;   // 市场类别
	short            m_nRetCount;   // 返回总数
	short            m_nSortType;   // 排序类型 见RT_GENERALSORT说明1
	short 			 m_nAlignment;  // 为了4字节对齐而添加的字段
	// 目前(2004年3月11日)用于新增功能的使用
	// 用于综合排名中快速排名窗口的几份钟排名设置。
};
/*
RT_GENERALSORT说明1:
m_nSortType掩码如下：（可取多值）
1、RT_RISE			涨幅排名
2、RT_FALL			跌幅排名
3、RT_5_RISE		5分钟涨幅排名
4、RT_5_FALL		5分钟跌幅排名
5、RT_AHEAD_COMM	买卖量差（委比）正序排名
6、RT_AFTER_COMM	买卖量差（委比）倒序排名
7、RT_AHEAD_PRICE	成交价震幅正序排名
8、RT_AHEAD_VOLBI	成交量变化（量比）正序排名
9、RT_AHEAD_MONEY	资金流向正序排名
*/

/* 综合排名报表数据项 */
struct GeneralSortData
{
	CodeInfo		m_ciStockCode;		// 股票代码
	long			m_lNewPrice;		// 最新价
	long			m_lValue;			// 计算值

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_ciStockCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lValue = YlsIntIntelToComputer(m_lValue);
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lValue = YlsIntComputerToIntel(m_lValue);
		}
#endif
	}
};

/*返回结构*/
struct AnsGeneralSort
{
	DataHead			m_dhHead;		// 数据报头
	short				m_nSortType;    // 排序类型
	short				m_nSize;		// 单个子包所含数据GeneralSortData个数
	// 当m_ nSortType为单值时（只有一位为1）,
	// 表示m_prptData数组的个数为m_nSize个。
	// 当m_ nSortType为多值相或时（如N位为1），表示此返回包针对N个子包，
	// 每个子包所含GeneralSortData个数为m_nSize，数组m_prptData的长度为N*m_nSize。
	GeneralSortData		m_prptData[1];	// 数据		
};

/* 
RT_SEVER_CALCULATE
返回计算数据数据包，使用常用请求包
*/

struct AnsSeverCalculate
{
	DataHead m_dhHead;

	int		 m_nSize;
	char     m_cData[1];

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

/*
RT_ANS_BYTYPE
返回指定类型的数据,由数据内部决定什么类型
请求包,注意:AskData 中 m_nOption 指向的类型
*/

struct AnsDataByType
{
	DataHead m_dhHead;

	short	 m_nSubType;   // 数据类型，根据此类类型确定 m_cData 里的数据,参见ByType_*定义
	short	 m_nResever;

	int		 m_nSize;
	char     m_cData[1];

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSubType = YlsShortIntelToComputer(m_nSubType);
			m_nResever = YlsShortIntelToComputer(m_nResever);
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nSubType = YlsShortComputerToIntel(m_nSubType);
			m_nResever = YlsShortComputerToIntel(m_nResever);
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

//#define RT_DAY_CURPOS					0x020C  // 日线当前实际位置	
struct AnsSeverDayCurpos
{
	DataHead			m_dhHead;		// 数据报头
	int					m_nCurPos;

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nCurPos = YlsIntIntelToComputer(m_nCurPos);
		}
		else
		{
			m_nCurPos = YlsIntComputerToIntel(m_nCurPos);
		}
#endif
	}
};

/* 
RT_SEVER_EMPTY
服务器没有数据时返回空包情况，一般日线无数据时
*/
struct AnsSeverEmpty
{
	DataHead			m_dhHead;		// 数据报头
	unsigned short		m_nOldType;     // 数据请求类型
	unsigned short		m_nAlignment;   // 
	int					m_nSize;
	char				m_cData[1];

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nOldType = YlsShortIntelToComputer(m_nOldType);
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nOldType = YlsShortComputerToIntel(m_nOldType);
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

/*
请求类型: RT_GENERALSORT_EX
功能说明: 综合排名报表(加入了几分钟排名设置)
备	  注: 
*/
/* 请求结构 */
struct ReqGeneralSortEx
{
	HSMarketDataType m_cCodeType;   // 市场类别
	short            m_nRetCount;   // 返回总数
	short            m_nSortType;   // 排序类型 见RT_GENERALSORT说明1
	short 			 m_nMinuteCount;// 用于综合排名中快速排名窗口的几份钟排名设置。
	// 0 使用服务器默认分钟数
	// 1 ... 15为合法取值(一般可能的取值为1,2,3,4,5,10,15)

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_cCodeType = YlsShortIntelToComputer(m_cCodeType);
			m_nRetCount = YlsShortIntelToComputer(m_nRetCount);
			m_nSortType = YlsShortIntelToComputer(m_nSortType);
			m_nMinuteCount = YlsShortIntelToComputer(m_nMinuteCount);
		}
		else
		{
			m_cCodeType = YlsShortComputerToIntel(m_cCodeType);
			m_nRetCount = YlsShortComputerToIntel(m_nRetCount);
			m_nSortType = YlsShortComputerToIntel(m_nSortType);
			m_nMinuteCount = YlsShortComputerToIntel(m_nMinuteCount);
		}
#endif
	}
};

/*返回结构*/
struct AnsGeneralSortEx
{
	DataHead			m_dhHead;		// 数据报头
	short				m_nSortType;    // 排序类型
	short				m_nSize;		// 单个子包所含数据GeneralSortData个数
	// 当m_ nSortType为单值时（只有一位为1）,
	// 表示m_prptData数组的个数为m_nSize个。
	// 当m_ nSortType为多值相或时（如N位为1），表示此返回包针对N个子包，
	// 每个子包所含GeneralSortData个数为m_nSize，数组m_prptData的长度为N*m_nSize。
	short				m_nAlignment;   // 字节对齐
	short				m_nMinuteCount;	// 用于综合排名中快速排名窗口的几份钟排名设置。
	// 0 使用服务器默认分钟数
	// 1 ... 15为合法取值(一般可能的取值为1,2,3,4,5,10,15)
	GeneralSortData		m_prptData[1];	// 数据		

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSortType = YlsShortIntelToComputer(m_nSortType);
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
			m_nMinuteCount = YlsShortIntelToComputer(m_nMinuteCount);
		}
		else
		{
			/*for(int i = 0; i < m_nSize; i++)
			{
				m_prptData[i].To(cIntelToComputer);
			}*/

			m_nSortType = YlsShortComputerToIntel(m_nSortType);
			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
			m_nMinuteCount = YlsShortComputerToIntel(m_nMinuteCount);
		}
#endif
	}
};


//#define RT_ETF_TREND	0x0306  /* ETF分时走势						*/

struct ETFReq
{
	CodeInfo m_pCode;  // 代码

	short m_nSize;   
	short m_lLine[1];  // 哪条线,参见ETFDataGroup_Buy1等的定义

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_pCode.To(cIntelToComputer);
		if( cIntelToComputer )
		{
			m_nSize = YlsShortIntelToComputer(m_nSize);
			for(int i = 0; i < m_nSize; i++ )
			{
				m_lLine[i] = YlsShortIntelToComputer(m_lLine[i]);
			}
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_lLine[i] = YlsShortComputerToIntel(m_lLine[i]);
			}

			m_nSize = YlsShortComputerToIntel(m_nSize);
		}
#endif
	}
};

//==========================================================================================
//==================================================改动处==================================
//==========================================================================================
// PriceVolItem::m_lTotal 在外汇时，意义不同
/*
请求类型: RT_TREND
功能说明: 分时走势
备	  注: 
*/
/*请求结构：常用请求AskData */
/* 价量数据项 */
struct PriceVolItem
{
	long			    m_lNewPrice;	// 最新价
	unsigned long		m_lTotal;		// 成交量(在外汇时，是跳动量)

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
		}
#endif
	}
};
/*返回结构*/
struct AnsTrendData
{
	DataHead		    m_dhHead;		// 数据报头
	short				m_nHisLen;		// 分时数据个数
	short 			    m_nAlignment;	// 为了4字节对齐而添加的字段
	StockOtherData		m_othData;		// 实时其它数据
	//HSStockRealTime		m_nowData;		// 实时基本数据
	union
	{
		HSStockRealTime			m_nowData;		// 个股实时基本数据
		HSIndexRealTime			m_indData;		// 指数实时基本数据
		HSHKStockRealTime		m_hkData;		// 港股实时基本数据
		HSQHRealTime			m_qhData;		// 期货实时基本数据
		HSWHRealTime			m_whData;		// 外汇实时基本数据
	};
	PriceVolItem		m_pHisData[1];	// 历史分时数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_othData.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_nHisLen = YlsShortIntelToComputer(m_nHisLen);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			for(int i = 0; i < m_nHisLen; i++)
			{
				m_pHisData[i].To(cIntelToComputer);
			}

			m_nHisLen = YlsShortComputerToIntel(m_nHisLen);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};

// ETF 数据项
struct ETFPriceVolItem
{
	union
	{
		unsigned long		m_lNewPrice;	// 最新价
		unsigned long		m_lTotal;		// 成交量
	};
};

// ETF 走势返回
struct AnsETFData
{
	DataHead		    m_dhHead;		// 数据报头

	long				m_lMaxPrice;
	long				m_lMinPrice;

	short 			    m_nLine;		// 当前线类型,参见 ETFDataGroup_Buy1 等的定义
	short				m_nHisLen;		// 分时数据个数

	ETFPriceVolItem		m_pHisData[1];	// 历史分时数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lMaxPrice = YlsIntIntelToComputer(m_lMaxPrice);
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);

			m_nLine = YlsShortIntelToComputer(m_nLine);
			m_nHisLen = YlsShortIntelToComputer(m_nHisLen);
		}
		else
		{
			m_lMaxPrice = YlsIntComputerToIntel(m_lMaxPrice);
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);

			m_nLine = YlsShortComputerToIntel(m_nLine);
			m_nHisLen = YlsShortComputerToIntel(m_nHisLen);
		}
#endif
	}
};

// ETF指标数据项
struct ETFTechPrice
{
	unsigned long		m_lNewPrice;	// 最新价
	unsigned long		m_lTotal;		// 成交量
};

// ETF tech走势返回
struct AnsETFTechData
{
	DataHead		    m_dhHead;		// 数据报头

	long				m_lMaxPrice;
	long				m_lMinPrice;

	short 			    m_nLine;		// 当前线类型,参见 ETFDataGroup_Buy1 等的定义
	short				m_nHisLen;		// 分时数据个数

	ETFTechPrice		m_pHisData[1];	// tech数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lMaxPrice = YlsIntIntelToComputer(m_lMaxPrice);
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);

			m_nLine = YlsShortIntelToComputer(m_nLine);
			m_nHisLen = YlsShortIntelToComputer(m_nHisLen);
		}
		else
		{
			m_lMaxPrice = YlsIntComputerToIntel(m_lMaxPrice);
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);

			m_nLine = YlsShortComputerToIntel(m_nLine);
			m_nHisLen = YlsShortComputerToIntel(m_nHisLen);
		}
#endif
	}
};

// ETF 时时返回
struct AnsETFNowData
{
	DataHead		    m_dhHead;		// 数据报头
	//ETFStockNowData     m_etf;

	StockOtherData		m_othData;		// 实时其它数据
	union
	{
		HSStockRealTime			m_nowData;		// 个股实时基本数据
		HSIndexRealTime			m_indData;		// 指数实时基本数据
		HSHKStockRealTime		m_hkData;		// 港股实时基本数据
		HSQHRealTime			m_qhData;		// 期货实时基本数据
		HSWHRealTime			m_whData;		// 外汇实时基本数据
	};

	ETFAllStockNow   m_etf;
};

/*
请求类型: RT_BUYSELLPOWER
功能说明: 买卖力道
备	  注: 
*/
/*请求结构：常用请求AskData */

/*返回结构 */
/* 买卖力道数据项 */
struct BuySellPowerData
{
	long		m_lBuyCount;		// 买量
	long		m_lSellCount;		// 卖量
};

struct AnsBuySellPower
{
	DataHead		    m_dhHead;			// 数据报头
	short				m_nHisLen;			// 买卖数据个数
	short 		    	m_nAlignment;       // 为了4字节对齐而添加的字段
	BuySellPowerData  	m_pHisData[1];		// 买卖数据
};


/*
请求类型: RT_HISTREND
功能说明: 历史回忆、多日分时、右小图下分时走势
备	  注: 
*/
/*请求结构*/
struct ReqHisTrend
{
	CodeInfo	 m_ciStockCode;	// 股票代码
	long         m_lDate; 		// 日期 见RT_HISTREND说明1

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_ciStockCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lDate = YlsIntIntelToComputer(m_lDate);
		}
		else
		{
			m_lDate = YlsIntComputerToIntel(m_lDate);
		}
#endif
	}
};
/*
RT_HISTREND说明1:
m_lDate：
如为正数则指具体日期,格式如20030701
如为负数则倒推m_lDate天数的当天分时走势（如-10则返回倒数第10天的）
如等于0,为当天
*/

struct HisTrendData
{
	StockHistoryTrendHead	m_shHead;		// 历史分时走势数据(2004年6月23日 改动处 结构不同）
	StockCompHistoryData	m_shData[1];	// 分钟历史数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_shHead.To(cIntelToComputer);
		}
		else
		{
			for(int i = 0; i < m_shHead.m_nSize; i++ )
			{
				m_shData[i].To(cIntelToComputer);
			}

			m_shHead.To(cIntelToComputer);
		}
#endif
	}
}; 
/*返回结构*/
struct AnsHisTrend
{
	DataHead			m_dhHead;	// 数据报头
	HisTrendData		m_shTend;	// 分时数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_shTend.To(cIntelToComputer);
#endif
	}
};



/*
请求类型: RT_ADDTREND
功能说明: 走势图叠加、多股同列
请求结构: 常用请求 AskData
返回结构: AnsTrendData 
*/

/*
请求类型: RT_TICK
功能说明: TICK图
*/
/* 请求结构：常用请求AskData */
/* 返回结构 */
struct AnsTick
{
	DataHead			m_dhHead;		// 数据报头
	StockOtherData		m_othData;		// 实时其它数据
	//HSStockRealTime		m_nowData;		// 实时基本数据
	union
	{
		HSStockRealTime			m_nowData;		// 个股实时基本数据
		HSIndexRealTime			m_indData;		// 指数实时基本数据
		HSHKStockRealTime		m_hkData;		// 港股实时基本数据
		HSQHRealTime			m_qhData;		// 期货实时基本数据
		HSWHRealTime			m_whData;		// 外汇实时基本数据
	};

	long				m_nSize;		// 分笔成交数据
	//short 		    	m_nAlignment;   // 为了4字节对齐而添加的字段
	StockTick			m_traData[1];	// 分笔成交数据 个数

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_othData.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_traData[i].To(cIntelToComputer);
			}

			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

// #define RT_TECHDATA_INCREMENT 0x0408	/* 盘后分析扩展 -- 增量数据请求 */
struct IncrementItem
{
	unsigned long m_lBeginDate;
	unsigned long m_lEndDate;

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lBeginDate = YlsIntIntelToComputer(m_lBeginDate);
			m_lEndDate = YlsIntIntelToComputer(m_lEndDate);
		}
		else
		{
			m_lBeginDate = YlsIntComputerToIntel(m_lBeginDate);
			m_lEndDate = YlsIntComputerToIntel(m_lEndDate);
		}
#endif
	}
};

struct ReqIncrementDayData
{	
	short				m_nPeriodNum;		// 周期长度,服务器不用,本地使用
	unsigned short		m_nSize;			// 需要请求的实际日期范围
	long				m_lBeginPosition;	// 起始个数，-1 表示当前位置。 （服务器端已经返回的个数）
	unsigned short		m_nDay;				// 申请的个数
	unsigned short		m_cPeriod;			// 周期类型
	CodeInfo			m_ciCode;			// 申请的股票代码

	IncrementItem		m_sItem[1];

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nPeriodNum = YlsShortIntelToComputer(m_nPeriodNum);
			m_lBeginPosition = YlsIntIntelToComputer(m_lBeginPosition);
			m_nDay = YlsShortIntelToComputer(m_nDay);
			m_cPeriod = YlsShortIntelToComputer(m_cPeriod);
			m_nSize = YlsShortIntelToComputer(m_nSize);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_sItem[i].To(cIntelToComputer);
			}

			m_nPeriodNum = YlsShortComputerToIntel(m_nPeriodNum);
			m_lBeginPosition = YlsIntComputerToIntel(m_lBeginPosition);
			m_nDay = YlsShortComputerToIntel(m_nDay);
			m_cPeriod = YlsShortComputerToIntel(m_cPeriod);
			m_nSize = YlsShortComputerToIntel(m_nSize);
		}
		m_ciCode.To(cIntelToComputer);
#endif
	}	
};

/*
请求类型: RT_TECHDATA / RT_TECHDATA_EX
功能说明: 盘后分析
*/

/*请求结构*/
struct ReqDayData 	
{
	short				m_nPeriodNum;		// 周期长度,服务器不用
	unsigned short		m_nSize;			// 本地数据当前已经读取数据起始个数,服务器不用
	long				m_lBeginPosition;	// 起始个数，-1 表示当前位置。 （服务器端已经返回的个数）
	unsigned short		m_nDay;				// 申请的个数
	short				m_cPeriod;			// 周期类型
	CodeInfo			m_ciCode;			// 申请的股票代码

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nPeriodNum = YlsShortIntelToComputer(m_nPeriodNum);
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_lBeginPosition = YlsIntIntelToComputer(m_lBeginPosition);
			m_nDay = YlsShortIntelToComputer(m_nDay);
			m_cPeriod = YlsShortIntelToComputer(m_cPeriod);
		}
		else
		{
			m_nPeriodNum = YlsShortComputerToIntel(m_nPeriodNum);
			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_lBeginPosition = YlsIntComputerToIntel(m_lBeginPosition);
			m_nDay = YlsShortComputerToIntel(m_nDay);
			m_cPeriod = YlsShortComputerToIntel(m_cPeriod);
		}
		m_ciCode.To(cIntelToComputer);
#endif
	}
};

/* 返回结构 */
// 针对RT_TECHDATA请求返回
struct StockCompDayData
{
	long	m_lDate;		// 日期
	long	m_lOpenPrice;	// 开
	long	m_lMaxPrice;	// 高
	long	m_lMinPrice;	// 低
	long	m_lClosePrice;	// 收
	long	m_lMoney;		// 成交金额
	unsigned long	m_lTotal;		// 成交量

};
struct AnsDayData
{
	DataHead			m_dhHead;			//数据头

	long				m_nSize;			//日线数据个数	
	//short 			    m_nAlignment;  	 	//为了4字节对齐而添加的字段
	StockCompDayData	m_sdData[1];		//日线数据
};

// 针对RT_TECHDATA_EX请求返回
struct StockCompDayDataEx
{
	long	m_lDate;		// 日期
	long	m_lOpenPrice;	// 开
	long	m_lMaxPrice;	// 高
	long	m_lMinPrice;	// 低
	long	m_lClosePrice;	// 收
	long	m_lMoney;		// 成交金额
	unsigned long	m_lTotal;		// 成交量
	long	m_lNationalDebtRatio; // 国债利率(单位为0.1分),基金净值(单位为0.1分), 无意义时，须将其设为0 2004年2月26日加入

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lDate = YlsIntIntelToComputer(m_lDate);
			m_lOpenPrice = YlsIntIntelToComputer(m_lOpenPrice);
			m_lMaxPrice = YlsIntIntelToComputer(m_lMaxPrice);
			m_lMinPrice = YlsIntIntelToComputer(m_lMinPrice);
			m_lClosePrice = YlsIntIntelToComputer(m_lClosePrice);
			m_lMoney = YlsIntIntelToComputer(m_lMoney);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_lNationalDebtRatio = YlsIntIntelToComputer(m_lNationalDebtRatio);
		}
		else
		{
			m_lDate = YlsIntComputerToIntel(m_lDate);
			m_lOpenPrice = YlsIntComputerToIntel(m_lOpenPrice);
			m_lMaxPrice = YlsIntComputerToIntel(m_lMaxPrice);
			m_lMinPrice = YlsIntComputerToIntel(m_lMinPrice);
			m_lClosePrice = YlsIntComputerToIntel(m_lClosePrice);
			m_lMoney = YlsIntComputerToIntel(m_lMoney);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_lNationalDebtRatio = YlsIntComputerToIntel(m_lNationalDebtRatio);
		}
#endif
	}
};

struct AnsDayDataEx 
{
	DataHead			m_dhHead;			//数据头

	long				m_nSize;			//日线数据个数	
	//short 			    m_nAlignment;  	 	//为了4字节对齐而添加的字段
	StockCompDayDataEx	m_sdData[1];		//日线数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_sdData[i].To(cIntelToComputer);
			}

			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

struct AnsDayDataIncrement 
{
	DataHead			m_dhHead;			// 数据头
	
	long				m_nSize;			// 日线数据个数	
	long				m_lBeginPosition;	// 当前服务器位置

	StockCompDayDataEx	m_sdData[1];		// 日线数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lBeginPosition = YlsIntIntelToComputer(m_lBeginPosition);
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_sdData[i].To(cIntelToComputer);
			}
			m_lBeginPosition = YlsIntIntelToComputer(m_lBeginPosition);
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

/*
#define RT_FILL_DATA					补线处理 
*/
struct ReqFillData
{
	char		m_cReserve[8];// 保留

	long		m_lSize;
	char		m_cData[1];	   // 指向 AnsData_Weihu 结构数据
};


/*
#define RT_DATA_WEIHU					数据维护处理 
*/

#define ReqData_Weihu_Mask_1 0x01  // 不要当天数据
#define ReqData_Weihu_Mask_2 0x02  // 不要当天分笔数据

/*请求结构*/
struct ReqData_Weihu
{
	short		m_nType;	   // 类别,参见：Data_Weihu_Down 等定义
	int			m_nPeriod;     // 周期,1分钟、5分钟、日线、历史回忆数据,参见：PERIOD_TYPE_MINUTE1 等定义

	long		m_lBeginDate;  // 开始时间
	long		m_lEndDate;    // 终止时间

	int			m_lPassword;   // 密码

	char		m_cNotToday;   // 不要当天数据
	char		m_lVersion;	   // 版本
	char		m_lreserve[2]; // 保留

	long		m_nSize;
	CodeInfo	m_pCode[1];
};

struct AnsData_Weihu
{
	DataHead				m_dhHead;		// 数据包头

	short					m_nType;		// 类别,参见：Data_Weihu_Down 等定义
	int						m_nPeriod;      // 周期,1分钟、5分钟、日线、历史回忆数据,参见：PERIOD_TYPE_MINUTE1 等定义

	unsigned long			m_nSize;  		// 数据长度
	char					m_cData[1];		// 数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nType		= YlsShortIntelToComputer(m_nType);
			m_nPeriod	= YlsIntIntelToComputer(m_nPeriod);
			m_nSize		= YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nType		= YlsShortComputerToIntel(m_nType);
			m_nPeriod	= YlsIntComputerToIntel(m_nPeriod);
			m_nSize		= YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

// 数据上传结构
struct UpData_Weihu
{
	HSMarketDataType	m_cCodeType;	   // 证券类型
	union
	{
		char			m_cCode[STOCK_CODE_SIZE];		   // 证券代码,当m_cCodeType != 0 时有效
		char			m_szFileName[256]; // 文件
	};
	long m_lSize;
	char m_cData[1];
};

/*
请求类型: RT_FILEDOWNLOAD

功能说明: 
用于文件的请求与应答，目前主要用于数据下载
*/
/*请求结构*/
struct ReqFileTransferData			//正序索引和文件请求
{
	long		m_lCRC;	      		// ＣＲＣ值，校验全部文件内容
	long		m_lOffsetPos;     	// 文件的偏移（字节）
	long		m_lCheckCRC;		// 是否进行校验ＣＲＣ　非０进行校验，０则不校验，   

	char		m_cFilePath[256];	// 文件名/路径
	// 路径中具有"$ml30"字串时，服务器以钱龙数据的绝对路径替换

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lCRC = YlsIntIntelToComputer(m_lCRC);
			m_lOffsetPos = YlsIntIntelToComputer(m_lOffsetPos);
			m_lCheckCRC = YlsIntIntelToComputer(m_lCheckCRC);
		}
		else
		{
			m_lCRC = YlsIntComputerToIntel(m_lCRC);
			m_lOffsetPos = YlsIntComputerToIntel(m_lOffsetPos);
			m_lCheckCRC = YlsIntComputerToIntel(m_lCheckCRC);
		}
#endif
	}
};

// #define RT_SERVERFILEINFO    		0x0707  /* 服务器自动推送要更新的文件信息				*/
struct ServerFileInfo
{
	unsigned long	m_lCRC;			   // CRC
	char			m_szFileName[128]; // 文件名称
};

// 服务器自动推送要更新的文件信息
struct AnsServerFileInfo
{
	DataHead		   m_dhHead;			// 数据报头
	
	short				m_nSize;			//
	ServerFileInfo      m_sServerFileInfo[1];
};

// #define RT_DOWNSERVERFILEINFO    		0x0708  /* 下载-服务器自动推送要更新的文件信息				*/
/*返回结构*/
struct AnsFileTransferDataByType		// 根据类型返回服务器数据
{
	DataHead				m_dhHead;		// 数据包头

	long				    m_nType;		// 类别,参见SrvFileType定义

	long  					m_lCRC;	      	// ＣＲＣ值

	char					m_cFilePath[256];

	unsigned long			m_nSize;  		// 数据长度
	char					m_cData[1];		// 数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nType = YlsIntIntelToComputer(m_lCRC);
			m_lCRC = YlsIntIntelToComputer(m_lCRC);
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nType = YlsIntComputerToIntel(m_lCRC);
			m_lCRC = YlsIntComputerToIntel(m_lCRC);
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}

};


enum SrvFileType // 服务器路径类型
{
	Srv_BlockUserStock,		// 板块、自选股
	Srv_Setting,			// 设置...
	Srv_Setting_File,		// 配置文件
	Srv_FinancialData,
	Srv_ClientFileUpdate,	// 客户端文件升级
	Srv_UserManagerDBF,		// 用户管理
	Srv_UserConfig,			// 用户对应的配置文件
	Srv_sysInfoData,		// 系统运行状态文件
	Srv_AcceptFilePath,		// 收到上传的文件
	Srv_DFxPath,			// dfx1.5服务器配置文件目录
	Srv_Gif,				// gif文件目录
	Srv_Config,				// gif文件设置目录
	Srv_Dynamic_File,		// 进程保存
	Srv_ExterDll			// dll路径
};

struct ReqFileTransferData2			//
{
	short		m_nType;			// 类别,参见SrvFileType定义
	short       m_nReserve;
	long		m_lCRC;	      		// ＣＲＣ值，校验全部文件内容
	long		m_lOffsetPos;     	// 文件的偏移（字节）
	long		m_lCheckCRC;		// 是否进行校验ＣＲＣ　非０进行校验，０则不校验，   

	char		m_cFilePath[256];	// 文件名/路径
	// 路径中具有"$ml30"字串时，服务器以钱龙数据的绝对路径替换

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nType = YlsShortIntelToComputer(m_nType);
			m_nReserve = YlsShortIntelToComputer(m_nReserve);

			m_lCRC = YlsIntIntelToComputer(m_lCRC);
			m_lOffsetPos = YlsIntIntelToComputer(m_lOffsetPos);
			m_lCheckCRC = YlsIntIntelToComputer(m_lCheckCRC);
		}
		else
		{
			m_nType = YlsShortComputerToIntel(m_nType);
			m_nReserve = YlsShortComputerToIntel(m_nReserve);

			m_lCRC = YlsIntComputerToIntel(m_lCRC);
			m_lOffsetPos = YlsIntComputerToIntel(m_lOffsetPos);
			m_lCheckCRC = YlsIntComputerToIntel(m_lCheckCRC);
		}
#endif
	}
};

struct AnsFileTransferData0		//正序索引和文件请求
{
	DataHead				m_dhHead;		// 数据包头
	
	long  					m_lCRC;	      	// ＣＲＣ值
	
	unsigned long			m_nSize;  		// 数据长度
	char					m_cData[1];		// 数据
};

/*返回结构*/
struct AnsFileTransferData		//正序索引和文件请求
{
	DataHead				m_dhHead;		// 数据包头

	long  					m_lCRC;	      	// ＣＲＣ值

	char					m_cFilePath[256];

	unsigned long			m_nSize;  		// 数据长度
	char					m_cData[1];		// 数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lCRC = YlsIntIntelToComputer(m_lCRC);
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_lCRC = YlsIntComputerToIntel(m_lCRC);
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}

};



//#define RT_PROMPT_INFO					0x0508	/* 服务器设置的提示信息				*/
struct AnsPromptInfoData
{
	DataHead				m_dhHead;		// 数据包头

	unsigned long			m_nSize;  		// 数据长度
	char					m_cData[1];		// 数据
};

//#define RT_FILESimplify					0x0506  /* 精简文件请求						*/
struct ReqSimplifyFile
{
	long					m_lCRC;	      	// ＣＲＣ值
	unsigned long			m_nSize;  		// 数据长度
	char					m_cData[1];		// 数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lCRC = YlsIntIntelToComputer(m_lCRC);
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_lCRC = YlsIntComputerToIntel(m_lCRC);
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

/*
请求类型: 
类型ID							含义
RT_TEXTDATAWITHINDEX_NEGATIVE	倒序资讯索引数据
RT_BYINDEXRETDATA				资讯内容数据
RT_TEXTDATAWITHINDEX_PLUS		正序资讯索引数据
RT_USERTEXTDATA					自定义资讯请求（如菜单等）
RT_FILEREQUEST					纯粹文件请求（例如配置文件等）
功能说明: 
1、	倒序资讯索引数据：例如信息地雷的请求与应答
2、	资讯内容数据请求与应答
3、	正序资讯索引数据：目前一般为F10资料索引请求与应答
4、	自定义资讯请求（如菜单等）：目前为券商自定义菜单请求与应答
5、	纯粹文件请求：包括主要配置以及数据文件的下载请求与应答

*/
/* 倒序资讯索引和资讯内容数据项 */
struct TextMarkData
{
	long	m_lCRC;	      		//ＣＲＣ值
	long	m_lBeginPos;     	// 开始位置，直接针对索引文件或内容文件的偏移（字节）
	long	m_lEndPos;			// 终止位置,同上,参见说明

	long	m_lCheckCRC;		//是否进行校验ＣＲＣ　非０进行校验，０则不校验， 

	/*指向字串,客户端使用,字串格式为: aa;bb;cc;dd
	其中aa为:
	#define INFO_PATH_KEY_F10			 "F10-%i"
	#define INFO_PATH_KEY_TREND			 "TREND-%i"
	#define INFO_PATH_KEY_TECH			 "TECH-%i"
	#define INFO_PATH_KEY_REPORT			 "REPORT-%i"
	其中bb为: 配置的段名 
	其中cc为: 配置的取值名
	其中dd为: 配置文件名*/
	char	m_szInfoCfg[128];	//包含配置文件名称等信息的字符串，客户端使用
	char	m_cTitle[64];		// 标题,客户端本地使用
	char	m_cFilePath[192];	// 文件名/路径

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lCRC = YlsIntIntelToComputer(m_lCRC);
			m_lBeginPos = YlsIntIntelToComputer(m_lBeginPos);
			m_lEndPos = YlsIntIntelToComputer(m_lEndPos);
			m_lCheckCRC = YlsIntIntelToComputer(m_lCheckCRC);
		}
		else
		{
			m_lCRC = YlsIntComputerToIntel(m_lCRC);
			m_lBeginPos = YlsIntComputerToIntel(m_lBeginPos);
			m_lEndPos = YlsIntComputerToIntel(m_lEndPos);
			m_lCheckCRC = YlsIntComputerToIntel(m_lCheckCRC);
		}
#endif
	}
};
/*请求结构*/
struct ReqTextData	  //索引和内容请求包
{
	TextMarkData    m_sMarkData;		//校验数据项
};
/*返回结构*/
struct AnsTextData		// 详细文本信息返回
{
	DataHead			m_dhHead;	// 数据报头
	TextMarkData        m_sMarkData;// 索引和内容
	unsigned long		m_nSize;	// 数据长度
	char				m_cData[1]; // 数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_sMarkData.To(cIntelToComputer);
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}

};


// 资讯类别
enum InfoClassType
{
	InfoClassType_D1    = 1,	// 金阳光资讯
	InfoClassType_D2    = 2,	// 金阳光策略
	InfoClassType_D3    = 3,	// 金股池
	InfoClassType_D4    = 4,	// 稳健型投资组合
	InfoClassType_D5    = 5,	// 晨会纪要
	InfoClassType_D6    = 6,	// 信息简报
	InfoClassType_D7    = 7,	// 分析师快报
	InfoClassType_E1    = 8,	// 晨会报告
	InfoClassType_E2    = 9,	// 宏观策略
	InfoClassType_E3    = 10,	// 行业研究
	InfoClassType_E4    = 11,	// 公司研究
	InfoClassType_E5    = 12,	// 权证研究
	InfoClassType_E6    = 13,	// 基金研究
	InfoClassType_E7    = 14,	// 债券研究
    InfoClassType_N1    = 15,	// 新增资讯
    InfoClassType_N2    = 16,	// 新增资讯
    InfoClassType_N3    = 17,	// 新增资讯
    InfoClassType_N4    = 18,	// 新增资讯
    InfoClassType_N5    = 19,	// 新增资讯
    InfoClassType_N6    = 20,	// 新增资讯
    InfoClassType_N7    = 21,	// 新增资讯
    InfoClassType_N8    = 22,	// 新增资讯
    InfoClassType_N9    = 23,	// 新增资讯
    InfoClassType_NA    = 24,	// 新增资讯
    InfoClassType_NB    = 25,	// 新增资讯
    InfoClassType_NC    = 26,	// 新增资讯
    InfoClassType_ND    = 27,	// 新增资讯
    InfoClassType_NE    = 28,	// 新增资讯
};

// 操作状态
enum InfoOperator
{
    InfoOperator_ChuShi  = 0x0000, // 初始状态
    InfoOperator_ShenHe  = 0x0001, // 已审核
    InfoOperator_ShanChu = 0x0002, // 已删除
	InfoOperator_ZuoFei	 = 0x0004, // 已作废
	InfoOperator_TuiHui	 = 0x0008, // 已退回

	InfoOperator_DianJiLv = 0x1000, // 更新点击率

	InfoOperator_FengKongShenHe = 0x40000000,   // 风险控制审核
	InfoOperator_FengKong = 0x80000000, // 风险控制属性

    //InfoOperator_TianJia = 0x0004, // 添加
};

// 用户属性
enum UserAttribute
{
    // 注意:1~n类用户可以对应以下名称,根据实际需要而定
    //“试用”、“黄金”、“铂金”、“钻石”
    // 最大支持28个用户类型
    UserAttribute_0     = 0x00000000, // 所有用户都可以看
    UserAttribute_1     = 0x00000001, //  1类用户
    UserAttribute_2     = 0x00000002, //  2类用户
    UserAttribute_3     = 0x00000004, //  3类用户
    UserAttribute_4     = 0x00000008, //  4类用户
    UserAttribute_5     = 0x00000010, //  5类用户
    UserAttribute_6     = 0x00000020, //  6类用户
    UserAttribute_7     = 0x00000040, //  7类用户
    UserAttribute_8     = 0x00000080, //  8类用户
    UserAttribute_9     = 0x00000100, //  9类用户
    UserAttribute_10    = 0x00000200, // 10类用户
    UserAttribute_11    = 0x00000400, // 11类用户
    UserAttribute_12    = 0x00000800, // 12类用户
    UserAttribute_13    = 0x00001000, // 13类用户
    UserAttribute_14    = 0x00002000, // 14类用户
    UserAttribute_15    = 0x00004000, // 15类用户
    UserAttribute_16    = 0x00008000, // 16类用户
    UserAttribute_17    = 0x00010000, // 17类用户
    UserAttribute_18    = 0x00020000, // 18类用户
    UserAttribute_19    = 0x00040000, // 19类用户
    UserAttribute_20    = 0x00080000, // 20类用户
    UserAttribute_21    = 0x00100000, // 21类用户
    UserAttribute_22    = 0x00200000, // 22类用户
    UserAttribute_23    = 0x00400000, // 23类用户
    UserAttribute_24    = 0x00800000, // 24类用户
    UserAttribute_25    = 0x01000000, // 25类用户
    UserAttribute_26    = 0x02000000, // 26类用户
    UserAttribute_27    = 0x04000000, // 27类用户
    UserAttribute_28    = 0x08000000, // 28类用户

    UserAttribute_29    = 0x10000000, // 超级用户
    UserAttribute_30    = 0x20000000, // 审核用户
    UserAttribute_31    = 0x40000000, // 发布用户
    UserAttribute_32    = 0x80000000, // 删除用户
};

// 信息状态
struct InfoCheckStatus
{
    unsigned int	m_InfoClassType;	    // 信息类别,参见 InfoClassType 定义
    unsigned int	m_InfoOperator;		    // 资讯状态,参见 InfoOperator  定义,可以多个并集
    unsigned int	m_UserAttribute;	    // 用户属性,参见 UserAttribute 定义,可以多个并集
    unsigned int	m_Atattch[5];		    // 附件名称,用CTime保存
    unsigned int    m_nSalesDepartmentNum;  // 营业部号  参见 SalesDepartmentNum 定义
	unsigned int	m_nSenderNum;			// 发布号(用户ID)（可以指向：发布人、发布单位、发布商）,参见SenderNum定义
	unsigned int	m_nAreaNum;			    // 点击次数
	unsigned int	m_nAuditNum;			// 审核
};

// 服务器返回的用户信息
struct SrvCheckInfo
{
	unsigned int	m_InfoClassType;	    // 信息类别,参见 InfoClassType 定义
    unsigned int    m_InfoOperator;		    // 操作状态,参见 InfoOperator  定义,可以多个并集
    unsigned int    m_UserAttribute;	    // 用户属性,参见 UserAttribute 定义,可以多个并集
    unsigned int    m_nSalesDepartmentNum;  // 营业部号,参见 SalesDepartmentNum 定义
    unsigned int	m_nSenderNum;			// 发布号(用户ID)（可以指向：发布人、发布单位、发布商）,参见SenderNum定义
	unsigned int	m_nAreaNum;			    // 点击次数	

	char			m_szUserName[20];		// 用户名称

	unsigned int	m_nClassNum;			// 等级提示编号
	char			m_cResever[30];
};

#define InfoIndexDataEx_mark (0x7F) // 发布索引标志

// 索引文件记录,兼容InfoIndex结构
struct InfoIndexDataEx
{
	char m_cType; // Bit0：     加密标志 (0:不加密,1:加密)
				  // Bit1-Bit6：保留
				  // Bit7： 无效记录标志位(0:有效记录，1:无效记录)
				  // 0x00	普通信息索引
				  // 0x01	加密信息索引
	              // 0x80	无效记录
				  // 0x7F	发布的资讯(注意使用)

	char m_cGroup;   // Bit0-Bit3为第一大类（共支持16种类型）
				  //（此4Bit为资讯厂商必须告诉xx的信息）
				  // Bit0-3值	信息类型
	              // 0x00	    交易所公告
				  // 0x01	    财经新闻
				  // 0x02	    个股历史资讯 (公司大事记)
				  // 0x03	    个股实时资讯
				  // 0x04	    F10资料
				  // 0x05-0x0e	保留
				  // 0x0f	    其它	

	char m_cMarket;  // Bit0-Bit7为市场分类（共支持8个市场），
				  // 和本信息相关的市场Bit置为1，
	              // 当信息不属于任何市场时，Bit0-Bit7全为0。
				  // 0	上海
				  // 1	深圳
				  // 2	创业
				  // 3	香港
				  // 4	台湾
				  // 5	美国
				  // 6	保留
				  // 7	其它

	long m_lDate;	   // 年*10000+月*100+日
	long m_lTime;      // 时*10000+分*100+秒
	char m_cTitle[64]; // 字符串必须用0x00结尾
					// 个股历史资讯	相关个股历史资讯内容的标题。内容最多63个字节，必须用0x00结尾。
					// 个股实时资讯	相关个股实时资讯内容的标题。内容最多63个字节，必须用0x00结尾。
					// 个股F10资料	即为F10资料页上的分类名称，最多支持4个汉字。
					// 资讯厂商的特色资讯	相关特色资讯内容的标题。内容最多63个字节，必须用0x00结尾。

	union
	{
		char m_CYlsFilePath[80]; // 源文件路径 // 130
		char m_cFilePath[80];    // 源文件路径 // 130
	};

	long m_lOffset;		  // 偏移位置
	long m_lLength;	      // 信息长度
	char m_cCode[4][9];   // 相关代码
						  // 最多支持4个相关个股代码。每个相关个股代码占9字节，其中第1字节是该个股所在市场种类(编码见附表三)，其它8个字节用于填写相关个股代码，不足填0x00。

	//char m_cReserved[55]; // 保留 // 5
	union
	{
		char FilePK[12];	  // 新闻序号（当天新闻序号唯一，不保证连续）(易富新闻序号)
		char m_cReserved[55]; // 保留 // 5

		InfoCheckStatus m_sInfoCheckStatus; // 对于索引特定处理,只针对发布的资讯
	};

	char m_cSubType;	  // 信息子分类 0-8
	                      // 0 	提示
						  // 1	说明
						  // 2	公司动态
						  // 3	分析点评
						  // 4	分红配股
						  // 5	业绩报告
						  // 6 	招股上市
						  // 7	公司其它公告

						  // 100 文件
						  // 101 文件索引

	char m_cChksum;		  // 校验
};

// #define RT_InfoSend						0x0C06 // 发布信息
// 请求
struct ReqInfoSend
{
	int				m_nPassword;   // 密码

	InfoIndexDataEx m_sIndex;

	int				m_nSize;	   // 内容数据长度
	int				m_nAttach[5];  // 附件数据长度,一次最多5个附件
	char			m_cData[1];	   // 数据，按照："内容数据+附件数据"的顺序存放
};


// #define RT_InfoUpdateIndex				0x0C07 // 更新信息索引
// 请求
struct InfoUpdateIndex
{
	int				m_nPassword;   // 密码

	InfoCheckStatus m_sInfoCheckStatus; // 对于索引特定处理,只针对发布的资讯

	int  m_nSize;     // 更新长度
	char m_cData[1];  // 数据,应该为 InfoIndexDataEx 结构的倍数
};

//#define RT_InfoUpdateOneIndex			0x0C08 // 更新一条信息索引
struct InfoUpdateOneIndex
{
	int				m_nPassword;   // 密码

	int				m_nPosition;   // 当前所在的位置
	InfoIndexDataEx m_sIndex;	   // 对于索引特定处理,只针对发布的资讯	
};

// RT_InfoClickTime
struct InfoClickTime
{
	char		    m_szUserID[32];  // 用户ID
	
	int				m_nPosition;     // 当前索引所在的位置
	unsigned int	m_InfoClassType; // 所属类别

	int				m_nClickTime;    // 点击次数
	int				m_nPingJi;		 // 评级类别
};

//#define RT_InfoDataTransmit				0x0C09 // 验证转发
struct InfoDataTransmit
{
	int  m_nSize;     // 更新长度
	char m_cData[1];  // 数据	
};

// 返回
struct AnsInfoDataTransmit
{
	DataHead m_dhHead;		// 数据报头

	int		 m_nSize;       // 更新长度
	char	 m_cData[1];    // 数据	
};

/*
请求类型: RT_STOCKTICK
功能说明: 个股分笔、个股详细的分笔数据
*/
//请求结构：常用请求 AskData
//返回结构：个股分笔返回包
struct AnsStockTick
{
	DataHead	m_dhHead;		// 数据报头

	long		m_nSize;		// 数据个数
	//short 		m_nAlignment;   // 为了4字节对齐而添加的字段
	StockTick	m_traData[1];	// 分笔数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			for( int i = 0; i < m_nSize; i++ )
			{
				m_traData[i].To(cIntelToComputer);
			}

			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

/*
请求类型: RT_BUYSELLORDER
功能说明: 个股买卖盘
*/

//请求结构：
struct ReqBuySellOrder			// 个股买卖盘请求包
{
	CodeInfo 	m_pCode;		// 代码
	short	 	m_nOffsetSize;  // m_nOffsetSize = -1全部返回; m_nOffsetSize >= 0倒叙的起始位置
	short 		m_nCount;		// 需要返回的长度
	long	 	m_lDate;		// 日期,格式:19990101, <= 0 为当天

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_pCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_nOffsetSize = YlsShortIntelToComputer(m_nOffsetSize);
			m_nCount = YlsShortIntelToComputer(m_nCount);
			m_lDate = YlsIntIntelToComputer(m_lDate);
		}
		else
		{
			m_nOffsetSize = YlsShortComputerToIntel(m_nOffsetSize);
			m_nCount = YlsShortComputerToIntel(m_nCount);
			m_lDate = YlsIntComputerToIntel(m_lDate);
		}
#endif
	}
};

//返回结构：
struct BuySellOrderData
{
	short 	m_nTime;		 		//现在时间
	short	m_nHand;				//股/手	

	unsigned long m_lCurrent;    	//现在总手
	long	m_lNewPrice;     		//最新价

	long	m_lPrevClose;			//昨收盘
	long	m_lBuyPrice1;			//买一价
	long	m_lBuyCount1;			//买一量
	long	m_lBuyPrice2;			//买二价
	long	m_lBuyCount2;			//买二量
	long	m_lBuyPrice3;			//买三价
	long	m_lBuyCount3;			//买三量
	long	m_lBuyPrice4;			//买四价
	long	m_lBuyCount4;			//买四量
	long	m_lBuyPrice5;			//买五价
	long	m_lBuyCount5;			//买五量

	long	m_lSellPrice1;			//卖一价
	long	m_lSellCount1;			//卖一量
	long	m_lSellPrice2;			//卖二价
	long	m_lSellCount2;			//卖二量
	long	m_lSellPrice3;			//卖三价
	long	m_lSellCount3;			//卖三量
	long	m_lSellPrice4;			//卖四价
	long	m_lSellCount4;			//卖四量
	long	m_lSellPrice5;			//卖五价
	long	m_lSellCount5;			//卖五量

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nTime = YlsShortIntelToComputer(m_nTime);
			m_nHand = YlsShortIntelToComputer(m_nHand);
			
			m_lCurrent = YlsIntIntelToComputer(m_lCurrent);
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);

			m_lPrevClose = YlsIntIntelToComputer(m_lPrevClose);
			m_lBuyPrice1 = YlsIntIntelToComputer(m_lBuyPrice1);
			m_lBuyCount1 = YlsIntIntelToComputer(m_lBuyCount1);
			m_lBuyPrice2 = YlsIntIntelToComputer(m_lBuyPrice2);
			m_lBuyCount2 = YlsIntIntelToComputer(m_lBuyCount2);
			m_lBuyPrice3 = YlsIntIntelToComputer(m_lBuyPrice3);
			m_lBuyCount3 = YlsIntIntelToComputer(m_lBuyCount3);
			m_lBuyPrice4 = YlsIntIntelToComputer(m_lBuyPrice4);
			m_lBuyCount4 = YlsIntIntelToComputer(m_lBuyCount4);
			m_lBuyPrice5 = YlsIntIntelToComputer(m_lBuyPrice5);
			m_lBuyCount5 = YlsIntIntelToComputer(m_lBuyCount5);

			m_lSellPrice1 = YlsIntIntelToComputer(m_lSellPrice1);
			m_lSellCount1 = YlsIntIntelToComputer(m_lSellCount1);
			m_lSellPrice2 = YlsIntIntelToComputer(m_lSellPrice2);
			m_lSellCount2 = YlsIntIntelToComputer(m_lSellCount2);
			m_lSellPrice3 = YlsIntIntelToComputer(m_lSellPrice3);
			m_lSellCount3 = YlsIntIntelToComputer(m_lSellCount3);
			m_lSellPrice4 = YlsIntIntelToComputer(m_lSellPrice4);
			m_lSellCount4 = YlsIntIntelToComputer(m_lSellCount4);
			m_lSellPrice5 = YlsIntIntelToComputer(m_lSellPrice5);
			m_lSellCount5 = YlsIntIntelToComputer(m_lSellCount5);
		}									   
		else
		{
			m_nTime = YlsShortComputerToIntel(m_nTime);
			m_nHand = YlsShortComputerToIntel(m_nHand);
			
			m_lCurrent = YlsIntComputerToIntel(m_lCurrent);
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);

			m_lPrevClose = YlsIntComputerToIntel(m_lPrevClose);
			m_lBuyPrice1 = YlsIntComputerToIntel(m_lBuyPrice1);
			m_lBuyCount1 = YlsIntComputerToIntel(m_lBuyCount1);
			m_lBuyPrice2 = YlsIntComputerToIntel(m_lBuyPrice2);
			m_lBuyCount2 = YlsIntComputerToIntel(m_lBuyCount2);
			m_lBuyPrice3 = YlsIntComputerToIntel(m_lBuyPrice3);
			m_lBuyCount3 = YlsIntComputerToIntel(m_lBuyCount3);
			m_lBuyPrice4 = YlsIntComputerToIntel(m_lBuyPrice4);
			m_lBuyCount4 = YlsIntComputerToIntel(m_lBuyCount4);
			m_lBuyPrice5 = YlsIntComputerToIntel(m_lBuyPrice5);
			m_lBuyCount5 = YlsIntComputerToIntel(m_lBuyCount5);

			m_lSellPrice1 = YlsIntComputerToIntel(m_lSellPrice1);
			m_lSellCount1 = YlsIntComputerToIntel(m_lSellCount1);
			m_lSellPrice2 = YlsIntComputerToIntel(m_lSellPrice2);
			m_lSellCount2 = YlsIntComputerToIntel(m_lSellCount2);
			m_lSellPrice3 = YlsIntComputerToIntel(m_lSellPrice3);
			m_lSellCount3 = YlsIntComputerToIntel(m_lSellCount3);
			m_lSellPrice4 = YlsIntComputerToIntel(m_lSellPrice4);
			m_lSellCount4 = YlsIntComputerToIntel(m_lSellCount4);
			m_lSellPrice5 = YlsIntComputerToIntel(m_lSellPrice5);
			m_lSellCount5 = YlsIntComputerToIntel(m_lSellCount5);
		}
#endif
	}

};

struct AnsBuySellOrder	
{
	DataHead		 m_dhHead;					// 数据报头

	short	 		 m_nOffsetSize;  // 对应请求包
	short 			 m_nCount;		// 对应请求包
	long	 		 m_lDate;		// 日期,格式:19990101

	long			 m_nSize;					// 数据个数
	//short 			 m_nAlignment;				// 为了4字节对齐而添加的字段
	BuySellOrderData m_sBuySellOrderData[1];	// 买卖盘数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nOffsetSize = YlsShortIntelToComputer(m_nOffsetSize);
			m_nCount = YlsShortIntelToComputer(m_nCount);
			m_lDate = YlsIntIntelToComputer(m_lDate);

			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_sBuySellOrderData[i].To(cIntelToComputer);
			}

			m_nOffsetSize = YlsShortComputerToIntel(m_nOffsetSize);
			m_nCount = YlsShortComputerToIntel(m_nCount);
			m_lDate = YlsIntComputerToIntel(m_lDate);

			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

/*
请求类型: RT_BUYSELLORDER_HK
功能说明: 港股买卖盘
*/

//请求结构： 同RT_BUYSELLORDER请求

//返回结构：
struct HKBuySellOrderData
{
	short 	m_nTime;		 		//现在时间
	short	m_nHand;				//股/手	
	unsigned long  	m_lCurrent;    			//现在总手
	long	m_lNewPrice;     		//最新价
	long	m_lPrevClose;			//昨收盘

	long		m_lBuyPrice;			// 买价
	long		m_lSellPrice;			// 卖价

	long		m_lBuyCount1;			// 买一量
	long		m_lBuyCount2;			// 买二量
	long		m_lBuyCount3;			// 买三量
	long		m_lBuyCount4;			// 买四量
	long		m_lBuyCount5;			// 买五量

	long		m_lSellCount1;			// 卖一量
	long		m_lSellCount2;			// 卖二量
	long		m_lSellCount3;			// 卖三量
	long		m_lSellCount4;			// 卖四量
	long		m_lSellCount5;			// 卖五量

	unsigned short		m_lSellOrder1;	// 卖一盘数
	unsigned short		m_lSellOrder2;	// 卖二盘数
	unsigned short		m_lSellOrder3;	// 卖三盘数
	unsigned short		m_lSellOrder4;	// 卖四盘数
	unsigned short		m_lSellOrder5;	// 卖五盘数

	unsigned short		m_lBuyOrder1;	// 买一盘数
	unsigned short		m_lBuyOrder2;	// 买二盘数
	unsigned short		m_lBuyOrder3;	// 买三盘数
	unsigned short		m_lBuyOrder4;	// 买四盘数
	unsigned short		m_lBuyOrder5;	// 买五盘数

};

struct AnsHKBuySellOrder	
{
	DataHead		 m_dhHead;					// 数据报头

	short	 		m_nOffsetSize;  // 对应请求包
	short 			m_nCount;		// 对应请求包
	long	 		m_lDate;		// 日期,格式:19990101

	short			 m_nSize;					// 数据个数
	short 			 m_nAlignment;				// 为了4字节对齐而添加的字段
	HKBuySellOrderData m_sBuySellOrderData[1];	// 买卖盘数据
};

/*
请求类型: RT_BUYSELLORDER_FUTURES
功能说明: 个股买卖盘
*/

//请求结构：同RT_BUYSELLORDER请求

//返回结构：
struct FuturesBuySellOrderData
{
	short 	m_nTime;		 		//现在时间
	unsigned long  	m_lCurrent;    			//现在总手
	long	m_lNewPrice;     		//最新价
	long	m_lPrevClose;			//昨收盘

	unsigned long		m_lTotal;		   	// 成交量(单位:合约单位)
	long		m_lChiCangLiang;    // 持仓量(单位:合约单位)

	long		m_lBuyPrice1;		// 买一价
	long		m_lBuyCount1;		// 买一量
	long		m_lSellPrice1;		// 卖一价
	long		m_lSellCount1;		// 卖一量

	long 		m_lOpenChiCang;			// 开盘持仓量
	long 		m_lLongPositionOpen;	// 多头开
	long 		m_lLongPositionFlat;	// 多头平
	long 		m_lNominalOpen;			// 空头开	
	long 		m_lNominalFlat;			// 空头平

};

struct AnsFuturesBuySellOrder	
{
	DataHead		 m_dhHead;					// 数据报头

	short	 		m_nOffsetSize;  // 对应请求包
	short 			m_nCount;		// 对应请求包
	long	 		m_lDate;		// 日期,格式:19990101

	short			 m_nSize;					// 数据个数
	short 			 m_nAlignment;				// 为了4字节对齐而添加的字段
	FuturesBuySellOrderData m_sBuySellOrderData[1];	// 买卖盘数据
};


/*
请求类型: RT_LIMITTICK
功能说明: 指定长度的分笔请求
*/
//请求结构：
struct ReqLimitTick
{
	CodeInfo			 m_pCode;		// 代码
	short				 m_nCount;		// 需要返回的长度
	union
	{
		unsigned short 	 m_nAlignment;  // 为了4字节对齐而添加的字段
		unsigned short 	 m_nOffset;     // 偏移位置
	};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_pCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_nCount = YlsShortIntelToComputer(m_nCount);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			m_nCount = YlsShortComputerToIntel(m_nCount);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};

//返回结构：同分笔结构



/*
请求类型: RT_HISTORYTICK
功能说明: 历史的分笔请求
*/
//请求结构：
struct ReqHistoryTick
{
	CodeInfo		m_pCode;		// 代码
	unsigned short	m_nOffsetSize;  // m_nOffsetSize = -1全部返回; m_nOffsetSize >= 0倒叙的起始位置
	short 			m_nCount;		// 需要返回的长度
	long	 		m_lDate;		// 日期,格式:19990101, <= 0 为当天
};

//返回结构：同分笔结构

/*
请求类型: RT_MAJORINDEXTICK
功能说明: 大盘明细
请求结构：常用请求 AskData
*/
//返回结构：
struct MajorIndexItem
{
	long			m_lNewPrice;		// 最新价（指数）
	unsigned long	m_lTotal;			// 成交量
	float			m_fAvgPrice;		// 成交额

	short	m_nRiseCount;		// 上涨家数
	short	m_nFallCount;		// 下跌家数

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_nRiseCount = YlsShortIntelToComputer(m_nRiseCount);
			m_nFallCount = YlsShortIntelToComputer(m_nFallCount);
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_nRiseCount = YlsShortComputerToIntel(m_nRiseCount);
			m_nFallCount = YlsShortComputerToIntel(m_nFallCount);
		}
#endif
	}
};

struct AnsMajorIndexTick	
{
	DataHead			m_dhHead;			// 数据报头

	short				m_nSize;			// 数据个数
	short 	  		   	m_nAlignment;		// 为了4字节对齐而添加的字段
	MajorIndexItem	    m_ntrData[1];		// 大盘一分钟成交明细

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			for( int i = 0; i < m_nSize; i++ )
			{
				m_ntrData[i].To(cIntelToComputer);
			}

			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};


/*
请求类型: RT_LEAD
功能说明: 大盘领先指标
请求结构: 常用请求AskData
*/
//返回结构：
struct StockLeadData
{
	long			m_lNewPrice;	// 最新价(指数)
	unsigned long	m_lTotal;		// 成交量

	short	m_nLead;		// 领先指标
	short	m_nRiseTrend;	// 上涨趋势
	short	m_nFallTrend;	// 下跌趋势
	short 	m_nAlignment;   // 为了4字节对齐而添加的字段

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);

			m_nLead = YlsShortIntelToComputer(m_nLead);
			m_nRiseTrend = YlsShortIntelToComputer(m_nRiseTrend);
			m_nFallTrend = YlsShortIntelToComputer(m_nFallTrend);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);

			m_nLead = YlsShortComputerToIntel(m_nLead);
			m_nRiseTrend = YlsShortComputerToIntel(m_nRiseTrend);
			m_nFallTrend = YlsShortComputerToIntel(m_nFallTrend);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};
struct AnsLeadData  
{
	DataHead		m_dhHead;		// 数据头
	HSIndexRealTime	m_indData;		// 指数实时数据

	short			m_nHisLen;		// 领先数据个数
	short 			m_nAlignment;   // 为了4字节对齐而添加的字段
	StockLeadData	m_pHisData[1];	// 领先数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_indData.To(cIntelToComputer);
		if( cIntelToComputer )
		{
			m_nHisLen = YlsShortIntelToComputer(m_nHisLen);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			for(int i = 0; i < m_nHisLen; i++ )
			{
				m_pHisData[i].To(cIntelToComputer);
			}

			m_nHisLen = YlsShortComputerToIntel(m_nHisLen);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};

/*
请求类型: RT_MAJORINDEXTREND
功能说明: 大盘走势
请求结构: 常用请求AskData
*/
/*返回结构*/
struct AnsMajorIndexTrend	
{
	DataHead			m_dhHead;		// 数据头
	HSIndexRealTime		m_indData;		// 上证30或深证指数NOW数据

	short				m_nHisLen;		// 分时数据个数	
	short 			    m_nAlignment;   // 为了4字节对齐而添加的字段
	PriceVolItem		m_pHisData[1];	// 分时数据 见说明

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_indData.To(cIntelToComputer);
		if( cIntelToComputer )
		{
			m_nHisLen = YlsShortIntelToComputer(m_nHisLen);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			m_nHisLen = YlsShortComputerToIntel(m_nHisLen);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};
/*
说明:
以下请求类型: 
RT_MAJORINDEXADL、RT_MAJORINDEXTREND、RT_MAJORINDEXBBI、RT_MAJORINDEXBUYSELL
各分类返回数据以实际结构数据代替AnsMajorIndexTrend结构中的m_pHisData[1]
数据返回包为AnsMajorIndexTrend，使用此结构代替AnsMajorIndexTrend结构
m_pHisData[1]一项
*/


/*
请求类型: RT_MAJORINDEXADL
功能说明: 大盘ADL
请求结构: 常用请求AskData
*/
/*返回结构：
说明:
返回包为AnsMajorIndexTrend，使用此结构代替AnsMajorIndexTrend结构
m_pHisData[1];一项
*/
struct ADLItem
{
	long				m_lNewPrice;	// 指数
	unsigned long		m_lTotal;		// 成交量
	long				m_lADL;			// ADL值（算法:ADL = （上涨家数 - 下跌家数）累计值）

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_lADL = YlsIntIntelToComputer(m_lADL);
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_lADL = YlsIntComputerToIntel(m_lADL);
		}
#endif
	}
};

/*
请求类型: RT_MAJORINDEXBBI
功能说明: 大盘多空指标BBI
请求结构: 常用请求AskData
*/
/*返回结构：
说明:
返回包为AnsMajorIndexTrend，使用此结构代替AnsMajorIndexTrend结构m_pHisData[1];一项
*/
struct LeadItem
{
	long			m_lNewPrice;	// 最新价（指数）
	unsigned long	m_lTotal;		// 成交量

	short	m_nLead;		// 领先指标
	short	m_nRiseTrend;	// 上涨趋势
	short	m_nFallTrend;	// 下跌趋势
	short   m_nAlignment;   // 为了4字节对齐而添加的字段

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);

			m_nLead = YlsShortIntelToComputer(m_nLead);
			m_nRiseTrend = YlsShortIntelToComputer(m_nRiseTrend);
			m_nFallTrend = YlsShortIntelToComputer(m_nFallTrend);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);

			m_nLead = YlsShortComputerToIntel(m_nLead);
			m_nRiseTrend = YlsShortComputerToIntel(m_nRiseTrend);
			m_nFallTrend = YlsShortComputerToIntel(m_nFallTrend);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};


/*
请求类型: RT_MAJORINDEXBUYSELL
功能说明: 大盘买卖力道
请求结构: 常用请求AskData
*/
/*返回结构：
返回包为AnsMajorIndexTrend，使用此结构代替AnsMajorIndexTrend结构
m_pHisData[1];一项
*/
struct MajorIndexBuySellPowerItem
{
	long			m_lNewPrice;	// 最新价	
	unsigned long	m_lTotal;		// 成交量
	long	m_lBuyCount;	// 买量
	long	m_lSellCount;	// 卖量

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);

			m_lBuyCount = YlsShortIntelToComputer(m_lBuyCount);
			m_lSellCount = YlsShortIntelToComputer(m_lSellCount);			
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);

			m_lBuyCount = YlsShortComputerToIntel(m_lBuyCount);
			m_lSellCount = YlsShortComputerToIntel(m_lSellCount);
		}
#endif
	}
};



/*
请求类型: RT_MASSDATA
功能说明: 主力大单，现用于监控大笔现手在区间内的变化,此区间有股票区间、时间区间
*/
#define MASSDATA_FILE_COUNT	64
//请求结构：
struct ReqMassData
{
	short    	       m_nClassBegin; // 大单级别 左区间（手）
	short    		   m_nClassEnd;	// 大单级别 右区间（手） 

	short              m_nPositions[MASSDATA_FILE_COUNT]; // 文件位置


	long    		   m_nSize;		// 文件标识结构个数	
	//short 	          m_nAlignment;	 //为了4字节对齐而添加的字段

	HSMarketDataType   m_nMarket[1];    //市场类别，为标准分类
};
/*返回结构：
说明：
1、	m_nPositions[]表示当前客户端已经接收的数据在服务器对应文件中
的文件位置，服务器根据请求提供的数值，将[该位置，文件末尾]区间的
数据返回，并修改相应的m_nPositions[]。
2、	目前版本客户端进行时钟请求代替主推请求；
*/

struct FixedMassData
{
	long 			m_lTime;        	// 距开盘的分钟数
	CodeInfo		m_ciStockCode;		// 股票代码
	long			m_lNewPrice;		// 最新价
	long			m_lCurTotal;		// 现手
	//	杨朝惠添加，20040319
	long			m_lTrxCount;		//	成交的次数（笔数）
	//	意味着本次大单记录是有这么多次的实际
	//	交易而产生。
	//	杨朝惠添加结束
};

struct AnsMassData
{
	DataHead		m_dhHead;		//数据报头

	short           m_nPositions[MASSDATA_FILE_COUNT]; // 文件位置


	long    		m_nSize;		// 文件标识结构个数	
	//short 	        m_nAlignment;	 //为了4字节对齐而添加的字段
	FixedMassData	m_pData[1];		// 数据地址
};




/*
请求类型: RT_CURRENTFINANCEDATA
功能说明: 最新的财务数据
*/
/* 请求结构 */
struct ReqCurrentFinanceData
{
	long 	m_lLastDate;	//最新日期

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lLastDate = YlsIntIntelToComputer(m_lLastDate);
		}
		else
		{
			m_lLastDate = YlsIntComputerToIntel(m_lLastDate);
		}
#endif
	}
};
/* 返回结构 */
struct CurrentFinanceData
{
	CodeInfo		m_ciStockCode;	 	// 股票代码	
	int	   			m_nDate;		 	// 日期
	float   		m_fFinanceData[39]; // 数据项
};

struct AnsCurrentFinance
{
	DataHead				m_dhHead;			//数据报头

	short            		m_nSize;			//后续数据个数
	short 	        		m_nAlignment;		//为了4字节对齐而添加的字段
	CurrentFinanceData      m_sFinanceData[1]; // 财务数据
};



/*
请求类型: RT_HISFINANCEDATA
功能说明: 历史财务数据
请求结构: 常用请求:AskData
*/
/*返回结构*/
struct HisFinanceData
{
	int		m_nDate;		  // 日期
	float   m_fFinanceData[39];  // 数据项
};

struct AnsHisFinance
{
	DataHead		m_dhHead;		//数据报头

	short           m_nSize;			//后续数据个数
	short 	        m_nAlignment;	//为了4字节对齐而添加的字段
	HisFinanceData  m_sFinanceData[1]; // 财务数据
};

/*请求类型: 	RT_VALUE
功能:请求与应答显示于客户端右小图“值”的数据(股票)
*/
// 请求结构：常用请求
// 返回结构：
struct AnsValueData
{
	DataHead		m_dhHead;			// 数据报头

	long			m_nTime;			// 时间，距离开盘分钟数
	unsigned long	m_lTotal;			// 总手
	float			m_fAvgPrice;		// 总金额
	long			m_lNewPrice;		// 最新价
	//long			m_lPreMaxPrice;		// 昨日最高价
	//long			m_lPreMinPrice;		// 昨日最低价
	long			m_lTickCount;		// 成交笔数	

	union
	{
		struct
		{
			long 			m_lMa10;			// 10天，20天，50天收盘均价
			long 			m_lMa20;
			long 			m_lMa50;
			long 			m_lMonthMax;		// 月最高最低
			long 			m_lMonthMin;		
			long 			m_lYearMax;			// 年最高最低
			long 			m_lYearMin;
			long			m_lHisAmplitude;	// 历史波幅(使用时除1000为百分比数）
		};
		CalcData_Share m_Share;
	};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nTime = YlsIntIntelToComputer(m_nTime);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTickCount = YlsIntIntelToComputer(m_lTickCount);
		}
		else
		{
			m_nTime = YlsIntComputerToIntel(m_nTime);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTickCount = YlsIntComputerToIntel(m_lTickCount);
		}
		m_Share.To(cIntelToComputer);
#endif
	}
};


/*请求类型: 	RT_VALUE_HK
功能:请求与应答显示于客户端右小图“值”的数据(港股)
*/
// 请求结构：常用请求
// 返回结构：
struct AnsHKValueData
{
	DataHead		m_dhHead;			// 数据报头

	long			m_nTime;			// 时间，距离开盘分钟数
	unsigned long			m_lTotal;			// 总手
	float			m_fAvgPrice;		// 总金额
	long			m_lNewPrice;		// 最新价
	//long			m_lPreMaxPrice;		// 昨日最高价
	//long			m_lPreMinPrice;		// 昨日最低价
	long			m_lTickCount;		// 成交笔数	

	//long 			m_lAPAvgPrice;		// 加权平均价

	union
	{
		long 		m_lPEratio;			// 预期市盈率 股票相关
		long		m_fOverFlowPrice;	// 溢价 认股证相关
	};

	union
	{
		long 		m_lWeekratio;		// 预期周息率 股票相关
		long		m_FCSRatio;			// 控股比例 认股证相关
	};

	union
	{
		long 		m_lCutPriceRatio;	// 拆让率 股票相关
		long		m_fValidCSRatio;	// 有效控股比例 认股证相关
	};

	union
	{
		struct
		{
			long 			m_lMa10;			// 10天，20天，50天收盘均价
			long 			m_lMa20;
			long 			m_lMa50;
			long 			m_lMonthMax;		// 月最高最低
			long 			m_lMonthMin;		
			long 			m_lYearMax;			// 年最高最低
			long 			m_lYearMin;
			long			m_lHisAmplitude;	// 历史波幅(使用时除1000为百分比数）
		};
		CalcData_Share m_Share;
	};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nTime = YlsIntIntelToComputer(m_nTime);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTickCount = YlsIntIntelToComputer(m_lTickCount);

			m_lPEratio = YlsIntIntelToComputer(m_lPEratio);
			m_lWeekratio = YlsIntIntelToComputer(m_lWeekratio);
			m_lCutPriceRatio = YlsIntIntelToComputer(m_lCutPriceRatio);
		}
		else
		{
			m_nTime = YlsIntComputerToIntel(m_nTime);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTickCount = YlsIntComputerToIntel(m_lTickCount);

			m_lPEratio = YlsIntComputerToIntel(m_lPEratio);
			m_lWeekratio = YlsIntComputerToIntel(m_lWeekratio);
			m_lCutPriceRatio = YlsIntComputerToIntel(m_lCutPriceRatio);
		}
		m_Share.To(cIntelToComputer);
#endif
	}

};


/*请求类型: 	RT_VALUE_FUTURES
功能:请求与应答显示于客户端右小图“值”的数据(期货)
*/
// 请求结构：常用请求
// 返回结构：
struct AnsFtValueData
{
	DataHead		m_dhHead;			// 数据报头

	long			m_nTime;			// 时间，距离开盘分钟数
	unsigned long	m_lTotal;			// 总手
	float			m_fAvgPrice;		// 总金额
	long			m_lNewPrice;		// 最新价
	//long			m_lPreMaxPrice;		// 昨日最高价
	//long			m_lPreMinPrice;		// 昨日最低价
	long			m_lTickCount;		// 成交笔数

	// 合约信息
	long 			m_lLotUnit;			// 每手单位(相当于实时数据里的nHand,建议是否可将其放入代码表里？）
	long 			m_lDiffUnit;		// 变动单位(1/1000元)
	long 			m_lMaxDeal;			// 最大申报量(单位：合约单位)
	long			m_lMarginRatio;		// 保证金比例(1/100 = ?%)

	union
	{
		struct
		{
			long 			m_lMa10;			// 10天，20天，50天收盘均价
			long 			m_lMa20;
			long 			m_lMa50;
			long 			m_lMonthMax;		// 月最高最低
			long 			m_lMonthMin;		
			long 			m_lYearMax;			// 年最高最低
			long 			m_lYearMin;
			long			m_lHisAmplitude;	// 历史波幅(使用时除1000为百分比数）
		};
		CalcData_Share m_Share;
	};

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nTime = YlsIntIntelToComputer(m_nTime);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTickCount = YlsIntIntelToComputer(m_lTickCount);

			m_lLotUnit = YlsIntIntelToComputer(m_lLotUnit);
			m_lDiffUnit = YlsIntIntelToComputer(m_lDiffUnit);
			m_lMaxDeal = YlsIntIntelToComputer(m_lMaxDeal);
			m_lMarginRatio = YlsIntIntelToComputer(m_lMarginRatio);
		}
		else
		{
			m_nTime = YlsIntComputerToIntel(m_nTime);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTickCount = YlsIntComputerToIntel(m_lTickCount);

			m_lLotUnit = YlsIntComputerToIntel(m_lLotUnit);
			m_lDiffUnit = YlsIntComputerToIntel(m_lDiffUnit);
			m_lMaxDeal = YlsIntComputerToIntel(m_lMaxDeal);
			m_lMarginRatio = YlsIntComputerToIntel(m_lMarginRatio);
		}
		m_Share.To(cIntelToComputer);
#endif
	}
};


/*请求类型:RT_HK_RECORDOPTION
功能:港股期权数据
*/
// 返回结构：
struct AnsOptionData
{
	DataHead		m_dhHead;		//数据报头
	long           	m_nSize;		//后续数据流长度
	char        	m_cData[1]; 	//期权数据流，指向　HSQQStockRealTime 结构
};

/*请求类型:RT_EXRIGHT_DATA
功能:除权数据增量传输
*/
// 请求结构：
struct ReqExRightData
{
	long 	m_lLastDate;	//最新日期
};

// 返回结构：
struct AnsExRightData
{
	DataHead		m_dhHead;		//数据报头
	long           	m_nSize;		//后续数据流长度
	char        	m_cData[1]; 	//除权数据流，格式同文件，参见：除权文件结构
};



/*请求类型:RT_STATIC_HK
功能:港股静态数据的请求
*/
// 请求结构：常用请求结构

// 返回结构：
struct AnsHKStaticData
{
	DataHead		m_dhHead;		//数据报头
	HSHKStaticData	m_sData;		//静态数据
};


// #define RT_ONE_BLOCKDATA				0x0408	/* 一个板块数据请求 */
struct ReqOneBlockData
{
	unsigned int m_lLastDate;			// 最新修改日期 
	char		 m_szBlockName[32];		// 板块名称
};

struct AnsOneBlockData
{
	DataHead		m_dhHead;				// 数据报头
	
	char			m_szBlockName[32];		// 板块名称

	int				m_nSize;				// 板块数据长度
	char			m_cData[1];				// 数据
};

/*请求类型:RT_BROKER_HK
功能:港股经纪席位详细信息
*/
// 请求结构：
struct ReqHKBrokerData
{
	unsigned short 		m_nType;	     // 请求类型
	char				m_nIndex;     	 // 请求索引，与请求数据包一致
	char				m_cOperator;   	 // 操作(目前不使用)
	long				m_lKey;		 	 // 一级标识，通常为窗口句柄
	HSPrivateKey	    m_nPrivateKey;	 // 二级标识

	short   			m_nSize;         // 请求证券总数，小于零时，
	// 其绝对值代表后面的字节数
	short 				m_nAlignment;    // 为了4字节对齐而添加的字段

	HSHKBrokerCode		m_sCode[1];	      // 经纪席位号信息
};
// 返回结构：
struct AnsHKBrokerData
{
	DataHead		m_dhHead;		// 数据报头
	long			m_lSIze;		// 席位数
	HSHKBrokerDeal  m_sData[1];		// 席位下委托状况

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lSIze = YlsIntIntelToComputer(m_lSIze);
		}
		else
		{
			m_lSIze = YlsIntComputerToIntel(m_lSIze);
		}
#endif
	}
};


/*
主推：
功能：
完成服务器端向客户端推送数据，
有请求主推（即有请求才主推）和固定主推（即服务器自动发送的，如指数）。

规则：
1、所有请求主推都返回，当请求主推的股票个数为0时，则服务器删除此次主推。
2、主机实时发送的数据，只适用于指数。
*/

/*
说明: 常用主推  （在客户端适用于所有页面）
类型: RT_AUTOPUSH

说明: 请求主推，目前用于预警
类型: RT_REQAUTOPUSH 
*/
/*返回结构*/
struct AnsHSAutoPushData
{
	DataHead	 m_dhHead;				// 数据报头

	long		 m_nSize;				// 数据个数
	CommRealTimeData m_pstData[1];	// 主机实时发送的数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

// 期货买卖盘数据
struct QHMaiMaiRealTime 
{
	long				m_lBuyPrice1;			// 买一价
	unsigned long		m_lBuyCount1;			// 买一量
	long				m_lBuyPrice2;			// 买二价
	unsigned long		m_lBuyCount2;			// 买二量
	long				m_lBuyPrice3;			// 买三价
	unsigned long		m_lBuyCount3;			// 买三量
	long				m_lBuyPrice4;			// 买四价
	unsigned long		m_lBuyCount4;			// 买四量
	long				m_lBuyPrice5;			// 买五价
	unsigned long		m_lBuyCount5;			// 买五量

	long				m_lSellPrice1;			// 卖一价
	unsigned long		m_lSellCount1;			// 卖一量
	long				m_lSellPrice2;			// 卖二价
	unsigned long		m_lSellCount2;			// 卖二量
	long				m_lSellPrice3;			// 卖三价
	unsigned long		m_lSellCount3;			// 卖三量
	long				m_lSellPrice4;			// 卖四价
	unsigned long		m_lSellCount4;			// 卖四量
	long				m_lSellPrice5;			// 卖五价
	unsigned long		m_lSellCount5;			// 卖五量

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{		
			m_lBuyPrice1 = YlsIntIntelToComputer(m_lBuyPrice1);			// 买一价
			m_lBuyCount1 = YlsIntIntelToComputer(m_lBuyCount1);			// 买一量
			m_lBuyPrice2 = YlsIntIntelToComputer(m_lBuyPrice2);			// 买二价
			m_lBuyCount2 = YlsIntIntelToComputer(m_lBuyCount2);			// 买二量
			m_lBuyPrice3 = YlsIntIntelToComputer(m_lBuyPrice3);			// 买三价
			m_lBuyCount3 = YlsIntIntelToComputer(m_lBuyCount3);			// 买三量
			m_lBuyPrice4 = YlsIntIntelToComputer(m_lBuyPrice4);			// 买四价
			m_lBuyCount4 = YlsIntIntelToComputer(m_lBuyCount4);			// 买四量
			m_lBuyPrice5 = YlsIntIntelToComputer(m_lBuyPrice5);			// 买五价
			m_lBuyCount5 = YlsIntIntelToComputer(m_lBuyCount5);			// 买五量

			m_lSellPrice1 = YlsIntIntelToComputer(m_lSellPrice1);			// 卖一价
			m_lSellCount1 = YlsIntIntelToComputer(m_lSellCount1);			// 卖一量
			m_lSellPrice2 = YlsIntIntelToComputer(m_lSellPrice2);			// 卖二价
			m_lSellCount2 = YlsIntIntelToComputer(m_lSellCount2);			// 卖二量
			m_lSellPrice3 = YlsIntIntelToComputer(m_lSellPrice3);			// 卖三价
			m_lSellCount3 = YlsIntIntelToComputer(m_lSellCount3);			// 卖三量
			m_lSellPrice4 = YlsIntIntelToComputer(m_lSellPrice4);			// 卖四价
			m_lSellCount4 = YlsIntIntelToComputer(m_lSellCount4);			// 卖四量
			m_lSellPrice5 = YlsIntIntelToComputer(m_lSellPrice5);			// 卖五价
			m_lSellCount5 = YlsIntIntelToComputer(m_lSellCount5);			// 卖五量
		}
		else
		{
			m_lBuyPrice1 = YlsIntComputerToIntel(m_lBuyPrice1);			// 买一价
			m_lBuyCount1 = YlsIntComputerToIntel(m_lBuyCount1);			// 买一量
			m_lBuyPrice2 = YlsIntComputerToIntel(m_lBuyPrice2);			// 买二价
			m_lBuyCount2 = YlsIntComputerToIntel(m_lBuyCount2);			// 买二量
			m_lBuyPrice3 = YlsIntComputerToIntel(m_lBuyPrice3);			// 买三价
			m_lBuyCount3 = YlsIntComputerToIntel(m_lBuyCount3);			// 买三量
			m_lBuyPrice4 = YlsIntComputerToIntel(m_lBuyPrice4);			// 买四价
			m_lBuyCount4 = YlsIntComputerToIntel(m_lBuyCount4);			// 买四量
			m_lBuyPrice5 = YlsIntComputerToIntel(m_lBuyPrice5);			// 买五价
			m_lBuyCount5 = YlsIntComputerToIntel(m_lBuyCount5);			// 买五量

			m_lSellPrice1 = YlsIntComputerToIntel(m_lSellPrice1);			// 卖一价
			m_lSellCount1 = YlsIntComputerToIntel(m_lSellCount1);			// 卖一量
			m_lSellPrice2 = YlsIntComputerToIntel(m_lSellPrice2);			// 卖二价
			m_lSellCount2 = YlsIntComputerToIntel(m_lSellCount2);			// 卖二量
			m_lSellPrice3 = YlsIntComputerToIntel(m_lSellPrice3);			// 卖三价
			m_lSellCount3 = YlsIntComputerToIntel(m_lSellCount3);			// 卖三量
			m_lSellPrice4 = YlsIntComputerToIntel(m_lSellPrice4);			// 卖四价
			m_lSellCount4 = YlsIntComputerToIntel(m_lSellCount4);			// 卖四量
			m_lSellPrice5 = YlsIntComputerToIntel(m_lSellPrice5);			// 卖五价
			m_lSellCount5 = YlsIntComputerToIntel(m_lSellCount5);			// 卖五量
		}		
#endif
	}
};

struct RealTimeDataQHMaiMai
{	
	CodeInfo			m_ciStockCode;			// 代码
	QHMaiMaiRealTime	m_sQHMaiMaiRealTime;	// 

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
		}
		else
		{
			m_sQHMaiMaiRealTime.To(cIntelToComputer);
			m_ciStockCode.To(cIntelToComputer);
		}
#endif
	}
};

// 期货买卖盘主推
struct AnsHSAutoPushQHMaiMai
{
	DataHead			 m_dhHead;			// 数据报头

	long				 m_nSize;			// 数据个数
	RealTimeDataQHMaiMai m_pstData[1];		// 主机实时发送的数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

struct RealTimeDataLevel
{	
	CodeInfo			m_ciStockCode;		// 代码
	LevelRealTime		m_sLevelRealTime;	// 

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
		}
		else
		{			
			m_ciStockCode.To(cIntelToComputer);
			m_sLevelRealTime.To(cIntelToComputer);
		}
#endif
	}
};

// level主推
struct AnsHSAutoPushLevel
{
	DataHead			 m_dhHead;			// 数据报头

	long				 m_nSize;			// 数据个数
	RealTimeDataLevel	 m_pstData[1];		// 主机实时发送的数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

// RT_RAW_AUTOPUSH
struct HSQHSourceRAWData
{
	long m_lTime;			// 指向CTime
	char m_cData[150];		// 数据
};

struct AnsHSRAWPushData
{
	DataHead	 m_dhHead;			// 数据报头

	long		 m_nSize;			// 数据大小
	char		 m_pstData[1];		// 指向 SourceRAWData 
};


//#define RT_Level_OrderQueue			0x0B03	// 买卖队列 - level2 买卖队列数据
//#define RT_Level_Cancellation			0x0B04	// 撤单 - 单笔委托数量最大的10笔买/卖撤单
//#define RT_Level_Consolidated			0x0B05	// 累计 - 撤消买入/卖出委托累计数量最多的前10只股票
struct AnsLevel2TotalData
{
	DataHead	 m_dhHead;			// 数据报头

	long		 m_nSize;			// 数据大小
	char		 m_cData[1];		// 指向实际使用的结构
};

/*
说明: 经纪龙虎榜主推  （港股）
类型: RT_AUTOBROKER_HK
*/
/*请求结构*/
// 常用请求

/*返回结构*/
struct AnsHKBrokerAutoPushData
{
	DataHead	    m_dhHead;			// 数据报头

	long			m_nSize;		// 数据个数
	//short 			m_nAlignment;   // 为了4字节对齐而添加的字段
	HSHKBuyAndSell	m_sData[1];		// 主机实时发送的数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++ )
			{
				m_sData[i].To(cIntelToComputer);
			}

			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};



/*
说明 : 精简主推（当前适用于指数）
类型 : RT_AUTOPUSHSIMP
*/
/*请求结构*/
// 常用请求包

/*返回结构*/
struct SimplifyIndexNowData		//指标类精简主推
{
	long			 m_lNewPrice;		// 最新价
	unsigned long    m_lTotal;  		// 成交量
	float		  	 m_fAvgPrice;	    // 成交金额

	short	m_nRiseCount;		// 上涨家数
	short	m_nFallCount;		// 下跌家数
	short	m_nLead;			// 领先指标
	short	m_nRiseTrend;		// 上涨趋势
	short	m_nFallTrend;		// 下跌趋势
	short	m_nTotalStock2;		// 对于综合指数：A股 + B股

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_lNewPrice = YlsIntIntelToComputer(m_lNewPrice);
			m_lTotal = YlsIntIntelToComputer(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_nRiseCount = YlsShortIntelToComputer(m_nRiseCount);
			m_nFallCount = YlsShortIntelToComputer(m_nFallCount);
			m_nLead = YlsShortIntelToComputer(m_nLead);
			m_nRiseTrend = YlsShortIntelToComputer(m_nRiseTrend);
			m_nFallTrend = YlsShortIntelToComputer(m_nFallTrend);
			m_nTotalStock2 = YlsShortIntelToComputer(m_nTotalStock2);
		}
		else
		{
			m_lNewPrice = YlsIntComputerToIntel(m_lNewPrice);
			m_lTotal = YlsIntComputerToIntel(m_lTotal);
			m_fAvgPrice = YlsFloatComputerToIntel(m_fAvgPrice);

			m_nRiseCount = YlsShortComputerToIntel(m_nRiseCount);
			m_nFallCount = YlsShortComputerToIntel(m_nFallCount);
			m_nLead = YlsShortComputerToIntel(m_nLead);
			m_nRiseTrend = YlsShortComputerToIntel(m_nRiseTrend);
			m_nFallTrend = YlsShortComputerToIntel(m_nFallTrend);
			m_nTotalStock2 = YlsShortComputerToIntel(m_nTotalStock2);
		}
#endif
	}
};  

struct SimplifyStockItem
{
	CodeInfo		     m_ciStockCode;				// 股票代码
	SimplifyIndexNowData m_sSimplifyIndexNowData;	// 数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_ciStockCode.To(cIntelToComputer);
		m_sSimplifyIndexNowData.To(cIntelToComputer);
#endif
	}
};

struct AnsSimplifyAutoPushData
{
	DataHead			m_dhHead;			// 数据报头
	short				m_nSize;			// 数据个数
	short 				m_nAlignment;    	// 为了4字节对齐而添加的字段	
	SimplifyStockItem	m_pstData[1];		// 主机实时发送的数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsShortIntelToComputer(m_nSize);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			m_nSize = YlsShortComputerToIntel(m_nSize);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};

/*
特别：
1、排名主推，请求的代码服务器端产生代码列表（客户端无法确定）做为主推代码
包括：61-66,表格点击排名,初始化主推.
2、81-86当前定为本地主动请求方式。
*/

// RT_SERVERTIME说明 BEGIN
// 说明：请求服务器时间
// 类型：RT_SERVERTIME
// 请求结构: 常用请求:AskData
// 返回结构
struct AnsServerTime
{
	DataHead				m_dhHead;		// 数据报头
	int						m_nDateTime;	// 当前时间(time_t,从1970/1/1 0:0:0开始的秒计数)
};
// RT_SERVERTIME说明 END

// RT_KEEPACTIVE说明 BEGIN
// 说明：保活通信
// 类型：RT_KEEPACTIVE
// 请求结构:
struct ReqKeepActive
{
	unsigned short m_nType;			 // 请求类型，与请求数据包一致

	char			m_nIndex;     	 // 请求索引，与请求数据包一致
	char			m_cOperator;   	 // 操作（0：清空 1:不清空)
};
// 返回结构
struct AnsKeepActive
{
	unsigned short  m_nType;			// 请求类型，与请求数据包一致
	char			m_nIndex;     	 // 请求索引，与请求数据包一致
	char			m_cOperator;   	 // 操作（0：清空 1:不清空)
	int			    m_nDateTime;		// 当前时间(time_t,从1970/1/1 0:0:0开始的秒计数)
};
/*
说明:
1。服务器收到RT_KEEPACTIVE请求时，如果应答缓冲区中有返回数据，则可不处理此包，不用返回。
2。服务器收到此包时，不可按通用请求的方式处理，即收到此请求时不清应答或请求缓冲区。
*/
// RT_KEEPACTIVE说明 END

struct TestSrvLoadData
{
	long		m_lTotalCount;		// 已连接过的总数
	long		m_nMaxCount;		// 允许的最大连接数
	long		m_nCheckDelay;		// 认证登陆使用时间
	long		m_nCheckErrors;		// 认证登陆失败错误次数
	long		m_nCpu;				// cpu情况
	long		m_nMemory;			// 内存使用情况

	TestSrvLoadData()
	{
		memset(this,0,sizeof(TestSrvLoadData));
	}
};

//#define RT_TESTSRVLOAD					0x0907	/* 请求服务器当前负载情况			*/
struct TestSrvLoad
{
	DataHead		m_dhHead;			// 数据报头
	TestSrvLoadData m_sSrvLoadData;

	TestSrvLoad()
	{			
		m_dhHead.m_nType = RT_TESTSRVLOAD;
	}
};

//RT_TESTSRV	0x0905	/* 测试客户端到服务器是否通畅 */

struct TestSrvData
{
	unsigned short m_nType;				// 请求类型，与请求数据包一致
	char		   m_nIndex;     		// 请求索引，与请求数据包一致
	char		   m_cOperator;   		// 操作（0：清空 1:不清空)

	TestSrvData()
	{
		m_nType = RT_TESTSRV;
	}
};


// RT_TEST说明 BEGIN
// 说明：测试通信包
// 类型：RT_TEST
// 请求结构:
struct ReqTest
{
	unsigned short m_nType;				// 请求类型，与请求数据包一致
	char		   m_nIndex;     		// 请求索引，与请求数据包一致
	char		   m_cOperator;   		// 操作（0：清空 1:不清空)
	long		   m_nSize;				// 数据长度
	long 		   m_nCSendTick;		// 客户端请求开始发送时间
	long		   m_nCReceiveTick;		// 客户端接收完返回包时间
	char		   m_szData[1];			// 请求数据包
};
// 返回结构:
struct AnsTest
{
	unsigned short m_nType;				// 请求类型，与请求数据包一致
	char		   m_nIndex;     		// 请求索引，与请求数据包一致
	char		   m_cOperator;   		// 操作（0：清空 1:不清空)
	long		   m_nSize;				// 数据长度
	long 		   m_nCSendTick;		// 客户端请求开始发送时间
	long		   m_nCReceiveTick;		// 客户端接收完返回包时间

	long		   m_nSReceiveTick;		// 服务器端收完请求时间
	long		   m_nSBeginCalcTick;	// 服务器端开始计算时间
	long		   m_nSEndCalcTick;		// 服务器端计算完成时间
	long		   m_nSSendTick;		// 服务器端开始发包时间

	char		   m_szData[1];			// 返回数据包
};
/*
说明:
1。所有时间均以毫秒为单位
2。m_szData可能指向所有类型的请求/应答（主推除处）数据包
*/
// RT_TEST说明 END


/* 资讯服务器相关的通讯结构 BEGIN */
/*	RT_UPDATEDFINANCIALDATA（增量的财务报表数据）
功能: 用于财务报表分析（Financial Statement Analysis），
请求与应答增量部分的财务报表数据。
*/
/* 请求结构：*/
struct ReqCurrentFinanceData;

/* 返回结构：*/
//#define FINANCIAL_DATA_LENGTH	113 /* 对应版本 20040401-1 */
#define FINANCIAL_DATA_LENGTH	118 /* 对应版本 20040401-2 */
/* 财务数据 */
struct UpdatedFinancialData
{
	char		m_strCode[STOCK_CODE_SIZE];	 	/* 股票代码	 */
	long		m_lBiuldDate;		/* 发生日期  */
	long		m_lModifyDate;		/* 修改日期	 */
	float		m_fData[FINANCIAL_DATA_LENGTH]; /* 财务数据项 */
};

struct AnsUpdatedFinanceData
{
	DataHead				m_dhHead;		//数据报头
	short            		m_nSize;			//后续数据个数
	short 	        		m_nAlignment;	//为了4字节对齐而添加的字段    
	UpdatedFinancialData	m_pUpdatedFinancialData[1]; // 财务数据
};
/* 资讯服务器相关的通讯结构 END */


//RT_SYNCHRONIZATIONDATA			0x0B02	/* 数据同步处理 */
struct SynchronizationDataExchange
{
	DataHead m_dhHead;		

	int		 m_nSize;
	char	 m_cData[1];
};

// RT_PUSHINFODATA // 资讯实时主推
struct AnsPushInfoData
{
	DataHead				m_dhHead;			// 数据报头

	int						m_nIndexPos;		//

	char					m_szPath[64];		// 所在索引文件名称
	InfoIndexDataEx			m_sInfoIndex;		// 资讯索引
};

// RT_PUSHREALTIMEINFO （实时解盘主推）
// 请求结构：常用请求
// 返回结构：
struct PushRealtimeInfoItem
{
	long 			m_lDate;	            // 年*10000+月*100+日
	long 			m_lTime;      	        // 时*10000+分*100+秒
	char 			m_cTitle[64]; 		    // 字符串必须用0x00结尾，可以为空字串

	unsigned short		m_nDataType;		// 内容类型，0为内容， 1 为文件， 2为URL
	unsigned short		m_nDataSize;		// 内容长度
	char				m_cData[1];			// 内容数据
};

struct AnsPushRealtimeInfo
{
	DataHead				m_dhHead;			// 数据报头

	unsigned  short			m_nMyTypeID;		// 所属分类ID
	short					m_nSize;			// 数据个数

	PushRealtimeInfoItem	m_pData[1];			// 实时解盘条
};

// RT_AUTOTICK_HK （港股分笔主推）
// 请求结构：常用请求
// 返回结构：
struct AutoTickItem
{
	CodeInfo	m_sCode;
	long		m_lSize;
	StockTick	m_traData[1];	// 分笔成交数据 个数

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		m_sCode.To(cIntelToComputer);

		if( cIntelToComputer )
		{
			m_lSize = YlsIntIntelToComputer(m_lSize);
		}
		else
		{
			for(int i = 0; i < m_lSize; i++ )
			{
				m_traData[i].To(cIntelToComputer);
			}

			m_lSize = YlsIntComputerToIntel(m_lSize);
		}
#endif
	}
};

struct AnsAutoTick
{
	DataHead			m_dhHead;		// 数据报头
	long				m_nSize;		// 分笔成交数据
	AutoTickItem		m_ayData[1];	// 应答股票支数 个数

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nSize = YlsIntIntelToComputer(m_nSize);
		}
		else
		{
			for(int i = 0; i < m_nSize; i++)
			{
				m_ayData[i].To(cIntelToComputer);
			}

			m_nSize = YlsIntComputerToIntel(m_nSize);
		}
#endif
	}
};

/*
请求类型: RT_TOTAL
功能说明: 总持
备	  注: 
*/
/*请求结构：常用请求AskData */
/* 总持数据项 */
struct TotalItem
{
	unsigned long		m_nTotal;		// 总持

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nTotal = YlsIntIntelToComputer(m_nTotal);
		}
		else
		{
			m_nTotal = YlsIntComputerToIntel(m_nTotal);
		}
#endif
	}
};
/*返回结构*/
struct AnsTotalData
{
	DataHead		    m_dhHead;		// 数据报头
	short				m_nHisLen;		// 分时数据个数
	short 			    m_nAlignment;	// 为了4字节对齐而添加的字段
	TotalItem			m_pHisData[1];	// 总持数据

	void To(char cIntelToComputer )
	{
#ifdef WORDS_BIGENDIAN
		if( cIntelToComputer )
		{
			m_nHisLen = YlsShortIntelToComputer(m_nHisLen);
			m_nAlignment = YlsShortIntelToComputer(m_nAlignment);
		}
		else
		{
			for(int i = 0; i < m_nHisLen; i++ )
			{
				m_pHisData[i].To(cIntelToComputer);
			}

			m_nHisLen = YlsShortComputerToIntel(m_nHisLen);
			m_nAlignment = YlsShortComputerToIntel(m_nAlignment);
		}
#endif
	}
};


//#ifndef HS_SUPPORT_UNIX
#pragma	pack()
//#endif


#endif
