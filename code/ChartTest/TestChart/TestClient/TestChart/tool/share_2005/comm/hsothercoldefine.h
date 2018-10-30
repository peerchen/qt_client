/*******************************************************************************
 * Copyright (c)2003, 讯捷软件有限公司
 * All rights reserved.
 *
 * 文件名称：HSOtherColDefine.h
 * 文件标识：字段宏定义
 * 摘    要：用于客户端的字段宏定义，与hscoldefine.h配合使用
 *
 * 当前版本：dfx2003
 * 作    者：讯捷王工
 * 完成日期：2003-8-19
 *
 * 取代版本：dfx2.0
 * 原 作 者：
 * 完成日期：2003-04-01
 * 备	 注：
 *
 * 修改记录：
 * 作    者：
 * 修改日期：
 * 修改内容：
 *******************************************************************************/
#ifndef _HS_OTHER_COL_DEFINE_HEADER_FILE_
#define _HS_OTHER_COL_DEFINE_HEADER_FILE_

#include "hscoldefine.h"

/* 字段分类名称*定义 BEGIN*/
#define	YLS_HQ_BASE_NAME			 _T("股票行情字段")
#define	YLS_HQ_EX_NAME				 _T("股票扩展行情")
#define	YLS_HQ_DETAIL_NAME			 _T("明细表")
#define	YLS_GB_GUBEN_NAME			 _T("股本数据")
#define	YLS_Cj_GUBEN_NAME			 _T("财务数据")
#define	LLX_LOCK_NAME				 _T("联动分析")
#define	YLS_USR_DEF_NAME			 _T("自定义")
#define ORIGINAL_USE_COLUMN_NAME	 _T("内部使用")
#define YLS_Block_Anysis_Name		 _T("报表分析")
#define YLS_ZiXun_Browse_Name		 _T("资讯/EMAIL字段")
#define YLS_Qihuo_HangQing_Name		 _T("期货行情")
#define FINANCIAL_STATEMENT_NAME	 _T("财务分析")
/* 字段分类名称*定义 END*/

/* 补充定义hscoldefine.h BEGIN*/
#define COLUMN_HQ_BASE_NUMBER				(COLUMN_HQ_BASE_BEGIN + 73) // 序号
#define COLUMN_HQ_BASE_TECH_SORT			(COLUMN_HQ_BASE_BEGIN + 74) // 技术指标排序数据
#define COLUMN_HQ_BASE_INFO_MARK			(COLUMN_HQ_BASE_BEGIN + 75) // 信息地雷标记
#define COLUMN_HQ_BASE_ARROW				(COLUMN_HQ_BASE_BEGIN + 76) // 上下箭头
#define COLUMN_HQ_BASE_INVERSE_PRICE		(COLUMN_HQ_BASE_BEGIN + 77) // 反汇率
/* 补充定义hscoldefine.h END*/


#ifdef COLUMN_END
	#define COLUMN_OTHER_BEGIN				(COLUMN_END + 1)	
#else
	#define COLUMN_OTHER_BEGIN				11000
#endif
#define COLUMN_OTHER_END					(COLUMN_OTHER_BEGIN + 2999)

/* 明细表 COLUMN_HQ_DETAIL_ DEFINE BEGIN*/
#define	COLUMN_HQ_DETAIL_BEGIN				(COLUMN_OTHER_BEGIN)
#define	COLUMN_HQ_DETAIL_END				(COLUMN_HQ_DETAIL_BEGIN + 150)

// 分时明细表
#define COLUMN_HQ_DETAIL_TREND_Time        	(COLUMN_HQ_DETAIL_BEGIN + 0)	//时间
#define COLUMN_HQ_DETAIL_TREND_NEW_PRICE   	(COLUMN_HQ_DETAIL_BEGIN + 1)	//成交价
#define COLUMN_HQ_DETAIL_TREND_RISE_VALUE  	(COLUMN_HQ_DETAIL_BEGIN + 2)	//涨跌值
#define COLUMN_HQ_DETAIL_TREND_BUY_PRICE    (COLUMN_HQ_DETAIL_BEGIN + 3)	//买入价
#define COLUMN_HQ_DETAIL_TREND_SELL_PRICE   (COLUMN_HQ_DETAIL_BEGIN + 4)	//卖出价
#define COLUMN_HQ_DETAIL_TREND_HAND     	(COLUMN_HQ_DETAIL_BEGIN + 5)	//现手
//	杨朝惠添加，20040315
#define	COLUMN_HQ_DETAIL_TREND_REALHANDS	(COLUMN_HQ_DETAIL_BEGIN + 6)	//	实际分笔数
//	杨朝惠添加结束
#define COLUMN_HQ_DETAIL_TREND_POSITION		(COLUMN_HQ_DETAIL_BEGIN+7)		// 总持
#define COLUMN_HQ_DETAIL_TREND_KPC			(COLUMN_HQ_DETAIL_BEGIN+8)		// 开平仓

// 盘后明细
#define COLUMN_HQ_DETAIL_TECH_TIME        	(COLUMN_HQ_DETAIL_BEGIN + 20)	//时间
#define COLUMN_HQ_DETAIL_TECH__RISE_VALUE   (COLUMN_HQ_DETAIL_BEGIN + 21)	//涨跌
#define COLUMN_HQ_DETAIL_TECH_OPEN_PRICE   	(COLUMN_HQ_DETAIL_BEGIN + 22)	//开盘
#define COLUMN_HQ_DETAIL_TECH_MAX_PRICE    	(COLUMN_HQ_DETAIL_BEGIN + 23)	//最高
#define COLUMN_HQ_DETAIL_TECH_MIN_PRICE    	(COLUMN_HQ_DETAIL_BEGIN + 24)	 //最低
#define COLUMN_HQ_DETAIL_TECH_CLOSE_PRICE  	(COLUMN_HQ_DETAIL_BEGIN + 25)	 //收盘
#define COLUMN_HQ_DETAIL_TECH_VOLUME      	(COLUMN_HQ_DETAIL_BEGIN + 26)	 //成交量
#define COLUMN_HQ_DETAIL_TECH_5DAY_AVGPRICE (COLUMN_HQ_DETAIL_BEGIN + 27)	 //5日均价
#define COLUMN_HQ_DETAIL_TECH_5DAY_TOTALVOL (COLUMN_HQ_DETAIL_BEGIN + 28)	 //5日总量
// 大盘明细
#define COLUMN_HQ_DETAIL_INDEX_TIME		  	(COLUMN_HQ_DETAIL_BEGIN + 40)	 //时间
#define COLUMN_HQ_DETAIL_INDEX_INDEX	  	(COLUMN_HQ_DETAIL_BEGIN + 41)	 //指数
#define COLUMN_HQ_DETAIL_INDEX_RISE_VALUE 	(COLUMN_HQ_DETAIL_BEGIN + 42)	 //涨跌值
#define COLUMN_HQ_DETAIL_INDEX_RISE_RATIO 	(COLUMN_HQ_DETAIL_BEGIN + 43)	 //涨跌幅
#define COLUMN_HQ_DETAIL_INDEX_RISE_COUNT 	(COLUMN_HQ_DETAIL_BEGIN + 44)	 //上涨家数
#define COLUMN_HQ_DETAIL_INDEX_FALL_COUNT 	(COLUMN_HQ_DETAIL_BEGIN + 45)	 //下跌家数
#define COLUMN_HQ_DETAIL_INDEX_EQUAL_COUNT	(COLUMN_HQ_DETAIL_BEGIN + 46)    //平盘家数	
#define COLUMN_HQ_DETAIL_INDEX_SUM_PRICE	(COLUMN_HQ_DETAIL_BEGIN + 47)	 //累计成交值
#define COLUMN_HQ_DETAIL_INDEX_PRICE		(COLUMN_HQ_DETAIL_BEGIN + 48)	 //成交值
#define COLUMN_HQ_DETAIL_INDEX_SUM_VOLUME	(COLUMN_HQ_DETAIL_BEGIN + 49)	 //累计成交量
#define COLUMN_HQ_DETAIL_INDEX_VOLUME		(COLUMN_HQ_DETAIL_BEGIN + 50)	 //成交量
// 买卖盘
#define COLUMN_HQ_DETAIL_BSORDER_DIRECTION	(COLUMN_HQ_DETAIL_BEGIN + 60)	 //买卖方向
#define COLUMN_HQ_DETAIL_BSORDER_PRICE		(COLUMN_HQ_DETAIL_BEGIN + 61)	 //成交价
#define COLUMN_HQ_DETAIL_BSORDER_VOLUME     (COLUMN_HQ_DETAIL_BEGIN + 62)	 //成交量
// 分价表
#define COLUMN_HQ_DETAIL_SPREAD_PRICE		(COLUMN_HQ_DETAIL_BEGIN + 66)	 //成交价
#define COLUMN_HQ_DETAIL_SPREAD_VOLUME		(COLUMN_HQ_DETAIL_BEGIN + 67)	 //分手
#define COLUMN_HQ_DETAIL_SPREAD_GRAPHIC		(COLUMN_HQ_DETAIL_BEGIN + 68)	 //分价表绘图
#define	COLUMN_HQ_DETAIL_SPREAD_VOLUMERATIO	(COLUMN_HQ_DETAIL_BEGIN + 69)	 //分价量比
#define	COLUMN_HQ_DETAIL_SPREAD_SELLVOLUME	(COLUMN_HQ_DETAIL_BEGIN + 70)	 //外盘绘图

// 财务报表
#define COLHEAD_FINANCE_NAME				(COLUMN_HQ_DETAIL_BEGIN + 80)	 //名称
#define COLHEAD_FINANCE_VALUE				(COLUMN_HQ_DETAIL_BEGIN + 81)	 //数据

// 买卖盘明细
#define COLUMN_BSORDER_ORDER				(COLUMN_HQ_DETAIL_BEGIN	+ 82)	 //成交
#define COLUMN_BSORDER_BS1					(COLUMN_HQ_DETAIL_BEGIN + 83)	 //卖买一
#define COLUMN_BSORDER_BS2					(COLUMN_HQ_DETAIL_BEGIN + 84)	 //卖买二
#define COLUMN_BSORDER_BS3					(COLUMN_HQ_DETAIL_BEGIN + 85)	 //卖买三
#define COLUMN_BSORDER_BS4					(COLUMN_HQ_DETAIL_BEGIN + 86)	 //卖买四
#define COLUMN_BSORDER_BS5					(COLUMN_HQ_DETAIL_BEGIN + 87)	 //卖买五

// 配股除权
#define COLUMN_HQ_DETAIL_EXRIGHT_DATE		(COLUMN_HQ_DETAIL_BEGIN	+ 90)	 //除权日期
#define COLUMN_HQ_DETAIL_EXRIGHT_GIVE		(COLUMN_HQ_DETAIL_BEGIN + 91)	 //送股
#define COLUMN_HQ_DETAIL_EXRIGHT_PLACING	(COLUMN_HQ_DETAIL_BEGIN + 92)	 //配股
#define COLUMN_HQ_DETAIL_EXRIGHT_GIVE_PRICE	(COLUMN_HQ_DETAIL_BEGIN + 93)	 //送股价
#define COLUMN_HQ_DETAIL_EXRIGHT_BONUS		(COLUMN_HQ_DETAIL_BEGIN + 94)	 //分红
/* 明细表 COLUMN_HQ_DETAIL_ DEFINE END*/

/* 股本数据 COLUMN_CAPITALIZATION_ DEFINE BEGIN*/
#define	COLUMN_CAPITALIZATION_BEGIN			(COLUMN_HQ_DETAIL_END + 1)
#define	COLUMN_CAPITALIZATION_END			(COLUMN_CAPITALIZATION_BEGIN + 20)

#define	COLUMN_CAPITALIZATION_TOTAL			COLUMN_CAPITALIZATION_BEGIN		  //1 总股本（万股）
#define	COLUMN_CAPITALIZATION_NATIONAL		(COLUMN_CAPITALIZATION_BEGIN + 1) //2 国家股
#define	COLUMN_CAPITALIZATION_INITIATOR		(COLUMN_CAPITALIZATION_BEGIN + 2) //3 发起人法人股
#define	COLUMN_CAPITALIZATION_CORPORATION	(COLUMN_CAPITALIZATION_BEGIN + 3) //4 法人股 
#define	COLUMN_CAPITALIZATION_B				(COLUMN_CAPITALIZATION_BEGIN + 4) //5 B股
#define	COLUMN_CAPITALIZATION_H				(COLUMN_CAPITALIZATION_BEGIN + 5) //6 H股
#define	COLUMN_CAPITALIZATION_PASS_A		(COLUMN_CAPITALIZATION_BEGIN + 6) //7 流通A股 
#define	COLUMN_CAPITALIZATION_EMPLOYEE		(COLUMN_CAPITALIZATION_BEGIN + 7) //8 职工股
#define	COLUMN_CAPITALIZATION_A2_GIVE		(COLUMN_CAPITALIZATION_BEGIN + 8) //9 A2转配股
/* 股本数据 COLUMN_CAPITALIZATION_ DEFINE END*/

/* 
财务数据 COLUMN_FINANCE_ DEFINE BEGIN 
ACCFUND = accumulation fund
*/
#define	COLUMN_FINANCE_BEGIN				(COLUMN_CAPITALIZATION_END + 1)
#define	COLUMN_FINANCE_END					(COLUMN_FINANCE_BEGIN + 50)

#define	COLUMN_FINANCE_TOTAL_ASSETS			COLUMN_FINANCE_BEGIN        //10 总资产 
#define	COLUMN_FINANCE_CURRENT_ASSETS		(COLUMN_FINANCE_BEGIN+1 )   //11 流动资产  
#define	COLUMN_FINANCE_CAPITAL_ASSETS		(COLUMN_FINANCE_BEGIN+2 )   //12 固定资产  
#define	COLUMN_FINANCE_UNBODIED_ASSETS		(COLUMN_FINANCE_BEGIN+3 )   //13 无形资产  
#define	COLUMN_FINANCE_LONG_INVESTMENT		(COLUMN_FINANCE_BEGIN+4 )   //14 长期投资  
#define	COLUMN_FINANCE_CURRENT_LIABILITIES  (COLUMN_FINANCE_BEGIN+5 )   //15 流动负债  
#define	COLUMN_FINANCE_LONG_LIABILITIES		(COLUMN_FINANCE_BEGIN+6 )   //16 长期负债  
#define	COLUMN_FINANCE_CAPITAL_ACCFUND		(COLUMN_FINANCE_BEGIN+7 )   //17 资本公积金
#define	COLUMN_FINANCE_PERSTOCK_ACCFUND	    (COLUMN_FINANCE_BEGIN+8 )   //18 每股公积金
#define	COLUMN_FINANCE_PARTNER_RIGHT	    (COLUMN_FINANCE_BEGIN+9 )   //19 股东权益  
#define	COLUMN_FINANCE_MAIN_INCOME			(COLUMN_FINANCE_BEGIN+10 )  //20 主营收入
#define	COLUMN_FINANCE_MAIN_PROFIT			(COLUMN_FINANCE_BEGIN+11 )  //21 主营利润 
#define	COLUMN_FINANCE_OTHER_PROFIT		    (COLUMN_FINANCE_BEGIN+12 )  //22 其他利润 
#define	COLUMN_FINANCE_TAKING_PROFIT		(COLUMN_FINANCE_BEGIN+13 )  //23 营业利润  
#define	COLUMN_FINANCE_YIELD				(COLUMN_FINANCE_BEGIN+14 )  //24 投资收益  
#define	COLUMN_FINANCE_SUBSIDY				(COLUMN_FINANCE_BEGIN+15 )  //25 补贴收入
#define	COLUMN_FINANCE_OTHER_INCOME		    (COLUMN_FINANCE_BEGIN+16 )  //26 营业外收支
#define	COLUMN_FINANCE_LAST_PROFIT_LOSS		(COLUMN_FINANCE_BEGIN+17 )  //27 上年损益调整
#define	COLUMN_FINANCE_TOTAL_PROFIT			(COLUMN_FINANCE_BEGIN+18 )  //28 利润总额
#define	COLUMN_FINANCE_SCOT_PROFIT			(COLUMN_FINANCE_BEGIN+19 )	//29 税后利润
#define	COLUMN_FINANCE_RETAINED_PROFITS		(COLUMN_FINANCE_BEGIN+20 )  //30 净利润
#define	COLUMN_FINANCE_UNPAID_PROFIT		(COLUMN_FINANCE_BEGIN+21 )  //31 未分配利润
#define	COLUMN_FINANCE_PER_UNPAID			(COLUMN_FINANCE_BEGIN+22 )  //32 每股未分配
#define	COLUMN_FINANCE_PER_INCOME			(COLUMN_FINANCE_BEGIN+23 )  //33 每股收益
#define	COLUMN_FINANCE_PER_ASSETS		    (COLUMN_FINANCE_BEGIN+24 )	//34 每股净资产
#define	COLUMN_FINANCE_ADJUST_PER_ASSETS	(COLUMN_FINANCE_BEGIN+25 )  //35 调整每股净资产
#define	COLUMN_FINANCE_PARTNER_RIGHT_RATIO  (COLUMN_FINANCE_BEGIN+26 )  //36 股东权益比
#define	COLUMN_FINANCE_ASSETS_YIELD			(COLUMN_FINANCE_BEGIN+27 )  //37 净资收益率
/* 财务数据 COLUMN_FINANCE_ DEFINE END */

/* 联动板块分析 COLUMN_LINKAGE_ DEFINE BEGIN*/
#define	COLUMN_LINKAGE_BEGIN				(COLUMN_FINANCE_END + 1)
#define	COLUMN_LINKAGE_END					(COLUMN_LINKAGE_BEGIN + 100)
#define	LLX_AU_CODE_ID						(COLUMN_LINKAGE_BEGIN +0  )		// "A股代码"
#define	LLX_AU_NAME_ID						(COLUMN_LINKAGE_BEGIN +1  )		 // A股名称	
#define	LLX_AU_LATEST_ID					(COLUMN_LINKAGE_BEGIN +2	 )		//"A股最新价"
#define	LLX_AU_CJL_ID						(COLUMN_LINKAGE_BEGIN +3	 )		//"A股成交量"
#define	LLX_AU_LTP_ID						(COLUMN_LINKAGE_BEGIN +4	 )		//"A股流通盘
#define	LLX_AU_LTPBL_ID						(COLUMN_LINKAGE_BEGIN +5	 )		//"A股流通盘比例"
#define	LLX_AU_ZF_ID						(COLUMN_LINKAGE_BEGIN +6	 )		//"A股涨幅"
#define	LLX_AU_5ZF_ID						(COLUMN_LINKAGE_BEGIN +7	 )		//A股5日涨幅"
#define	LLX_AU_10ZF_ID						(COLUMN_LINKAGE_BEGIN +8	 )		//"A股10涨幅"
#define	LLX_AU_20ZF_ID						(COLUMN_LINKAGE_BEGIN +9	 )		//"A股20涨幅"
#define	LLX_AU_60ZF_ID						(COLUMN_LINKAGE_BEGIN +10 )		//"A股60涨幅"
#define	LLX_AU_YL_ID						(COLUMN_LINKAGE_BEGIN +11 )		//"A股市盈率"
#define	LLX_AU_HSL_ID						(COLUMN_LINKAGE_BEGIN +12 )		//"A股换手率"
#define	LLX_AU_LTPSZ_ID						(COLUMN_LINKAGE_BEGIN +13 )		//"A股流通盘市值"

#define	LLX_BU_CODE_ID						(COLUMN_LINKAGE_BEGIN +14 ) 		//"B股代码"
#define	LLX_BU_NAME_ID						(COLUMN_LINKAGE_BEGIN +15 ) 		//"B股名称"
#define	LLX_BU_LATEST_ID					(COLUMN_LINKAGE_BEGIN +16 )		//"B股最新价"
#define	LLX_BU_CJL_ID						(COLUMN_LINKAGE_BEGIN +17 )		//"B股成交量"
#define	LLX_BU_LTP_ID						(COLUMN_LINKAGE_BEGIN +18 )		//"B股流通盘"
#define	LLX_BU_LTPBL_ID						(COLUMN_LINKAGE_BEGIN +19 )		//"B股流通盘比例"
#define	LLX_BU_ZF_ID						(COLUMN_LINKAGE_BEGIN +20 )		//"B股涨幅"
#define	LLX_BU_5ZF_ID						(COLUMN_LINKAGE_BEGIN +21 )		//"B股5日涨幅"
#define	LLX_BU_10ZF_ID						(COLUMN_LINKAGE_BEGIN +22 )		//"B股10涨幅"
#define	LLX_BU_20ZF_ID						(COLUMN_LINKAGE_BEGIN +23 )		//"B股20涨幅"
#define	LLX_BU_60ZF_ID						(COLUMN_LINKAGE_BEGIN +24 )		//"B股60涨幅"
#define	LLX_BU_YL_ID						(COLUMN_LINKAGE_BEGIN +25 )		//"B股市盈率"
#define	LLX_BU_HSL_ID						(COLUMN_LINKAGE_BEGIN +26 )		//"B股换手率"
#define	LLX_BU_LTPSZ_ID						(COLUMN_LINKAGE_BEGIN +27 )		//"B股流通盘市值"

#define	LLX_HU_CODE_ID						(COLUMN_LINKAGE_BEGIN +28 )		//"H股代码"
#define	LLX_HU_NAME_ID						(COLUMN_LINKAGE_BEGIN +29 )		//"H股名称"
#define	LLX_HU_LATEST_ID					(COLUMN_LINKAGE_BEGIN +30 )		//"H股最新价"
#define	LLX_HU_CJL_ID						(COLUMN_LINKAGE_BEGIN +31 )		//"H股成交量"
#define	LLX_HU_LTP_ID						(COLUMN_LINKAGE_BEGIN +32 )		//"H股流通盘"
#define	LLX_HU_LTPBL_ID						(COLUMN_LINKAGE_BEGIN +33 )		//"H股流通盘比例"
#define	LLX_HU_ZF_ID						(COLUMN_LINKAGE_BEGIN +34 )		//"H股涨幅"
#define	LLX_HU_5ZF_ID						(COLUMN_LINKAGE_BEGIN +35 )		//"H股5日涨幅"
#define	LLX_HU_10ZF_ID						(COLUMN_LINKAGE_BEGIN +36 )		//"H股10涨幅"
#define	LLX_HU_20ZF_ID						(COLUMN_LINKAGE_BEGIN +37 )		//"H股20涨幅"
#define	LLX_HU_60ZF_ID						(COLUMN_LINKAGE_BEGIN +38 )		//"H股60涨幅"
#define	LLX_HU_YL_ID						(COLUMN_LINKAGE_BEGIN +39 )		//"H股市盈率"
#define	LLX_HU_HSL_ID						(COLUMN_LINKAGE_BEGIN +40 )		//"H股换手率"
#define	LLX_HU_LTPSZ_ID						(COLUMN_LINKAGE_BEGIN +41 )		//"H股流通盘市值"

#define	LLX_ABU_PRICE_ID					(COLUMN_LINKAGE_BEGIN +42 )		//"A股价格/B股价格"
#define	LLX_AHU_PRICE_ID					(COLUMN_LINKAGE_BEGIN +43 )		//"A股价格/H股价格"
#define	LLX_ALL_GB_ID						(COLUMN_LINKAGE_BEGIN +44 )		//"总股本"
#define	LLX_EVERY_BEHALF_ID					(COLUMN_LINKAGE_BEGIN +45 )		//"每股收益"
#define	LLX_EVERY_CAPITAL_ID				 ( COLUMN_LINKAGE_BEGIN +46 )		//"每股净资产"
#define	LLX_EVERY_CB_ID						(COLUMN_LINKAGE_BEGIN +47 )		//"净资产收益率"	
#define	LLX_DELETE_ID						(COLUMN_LINKAGE_BEGIN +48 )		//"净资产收益率"

/* 联动板块分析 COLUMN_LINKAGE_ DEFINE END*/

/* 板块分析 COLUMN_BLOCK_ DEFINE BEGIN*/
#define COLUMN_BLOCK_BEGIN					(COLUMN_LINKAGE_END + 1)
#define COLUMN_BLOCK_END					(COLUMN_BLOCK_BEGIN + 40)

#define Llx_Block_To_Stock_Name				(COLUMN_BLOCK_BEGIN + 0)
#define Llx_Block_To_Stock_1 				(COLUMN_BLOCK_BEGIN + 1)
#define Llx_Block_To_Stock_2 				(COLUMN_BLOCK_BEGIN + 2)
#define Llx_Block_To_Stock_3 				(COLUMN_BLOCK_BEGIN + 3)
#define Llx_Block_To_Stock_4 				(COLUMN_BLOCK_BEGIN + 4)
#define Llx_Block_To_Stock_5 				(COLUMN_BLOCK_BEGIN + 5)
#define Llx_Block_To_Stock_6 				(COLUMN_BLOCK_BEGIN + 6)
#define Llx_Block_To_Stock_7 				(COLUMN_BLOCK_BEGIN + 7)
#define Llx_Block_To_Stock_8 				(COLUMN_BLOCK_BEGIN + 8)
/* 板块分析 COLUMN_BLOCK_ DEFINE END*/



// 自定义数据项									 
#define	YLS_USR_DEF_BEGIN        (COLUMN_LINKAGE_END + 1)
#define	YLS_USR_DEF_END		     (YLS_USR_DEF_BEGIN + 200)									
// 内部使用字段
#define ORIGINAL_USE_COLUMN_BEGIN	(YLS_USR_DEF_END + 1)
#define ORIGINAL_USE_COLUMN_END		(ORIGINAL_USE_COLUMN_BEGIN + 200)

// 资讯相关
#define YLS_ZiXun_Browse_Begin			(ORIGINAL_USE_COLUMN_END + 1)
#define YLS_ZiXun_Browse_End			(YLS_ZiXun_Browse_Begin + 30)

#define Yls_ZiXun_ReadMark			   (YLS_ZiXun_Browse_Begin + 0)    // 读写标记
#define Yls_ZiXun_NewsProtected		   (YLS_ZiXun_Browse_Begin + 1)    // 新闻保护
#define Yls_ZiXun_Block				   (YLS_ZiXun_Browse_Begin + 2)    // 新闻板块/栏目
#define Yls_ZiXun_Title				   (YLS_ZiXun_Browse_Begin + 3)    // 新闻标题
#define Yls_ZiXun_AcceptTime		   (YLS_ZiXun_Browse_Begin + 4)    // 接收时间
#define Yls_ZiXun_ZuoZhe			   (YLS_ZiXun_Browse_Begin + 5)    // 作者
#define Yls_ZiXun_FuJian			   (YLS_ZiXun_Browse_Begin + 6)    // 附件
#define Yls_ZiXun_InfoSource           (YLS_ZiXun_Browse_Begin + 7)    // 信息提供者

#define Yls_ZiXun_CreateTime           (YLS_ZiXun_Browse_Begin + 8)     // 创建时间
#define Yls_ZiXun_ZhongYaoXing         (YLS_ZiXun_Browse_Begin + 9)     // 重要性
#define Yls_ZiXun_SendTime             (YLS_ZiXun_Browse_Begin + 10)    // 发送时间
#define Yls_ZiXun_DownloadStatus       (YLS_ZiXun_Browse_Begin + 11)    // 下载状态
#define Yls_ZiXun_ReadOver		       (YLS_ZiXun_Browse_Begin + 12)    // 已读
#define Yls_ZiXun_AcceptMan		       (YLS_ZiXun_Browse_Begin + 13)    // 收件人
#define Yls_ZiXun_MaxMin		       (YLS_ZiXun_Browse_Begin + 14)    // 大小
#define Yls_ZiXun_OverTime		       (YLS_ZiXun_Browse_Begin + 15)    // 到期时间
#define Yls_ZiXun_MinGanDu		       (YLS_ZiXun_Browse_Begin + 16)    // 敏感度
#define Yls_ZiXun_ChaoSong		       (YLS_ZiXun_Browse_Begin + 17)    // 抄送
#define Yls_ZiXun_ConnectMan		   (YLS_ZiXun_Browse_Begin + 18)    // 联系人字段
#define Yls_ZiXun_Type				   (YLS_ZiXun_Browse_Begin + 19)    // 类别
#define Yls_ZiXun_XuYaoHuiZhi		   (YLS_ZiXun_Browse_Begin + 20)    // 需要回执
#define Yls_ZiXun_MailInterVer		   (YLS_ZiXun_Browse_Begin + 21)    // Mail内部版本
#define Yls_ZiXun_SendMan			   (YLS_ZiXun_Browse_Begin + 22)    // 发件人

#endif /*_HS_OTHER_COL_DEFINE_HEADER_FILE_*/
