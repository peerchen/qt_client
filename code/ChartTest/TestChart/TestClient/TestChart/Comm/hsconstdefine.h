/*******************************************************************************
* Copyright (c)2003, 讯捷软件有限公司
* All rights reserved.
*
* 文件名称：HSConstDefine.h
* 文件标识：常量定义
* 摘    要：常量定义
*
* 当前版本：xfd2003
* 作    者：讯捷软件有限公司
* 完成日期：2003-07
* 备	注：
*
* 日	期：2004-03-09
* 作	者：讯捷软件有限公司
* 修改内容：增加资讯相关的宏定义
*
* 日	期：2004年7月7日
* 作	者：讯捷软件有限公司
* 修改内容：增加多金融相关的宏定义
*******************************************************************************/
#ifndef _HS_CONST_HEADER_FILE_
#define _HS_CONST_HEADER_FILE_

/* 文件名称定义 DEFINE BEGIN */
#define CLIENT_VERSION_INI_FILE	"clientversion.ini"		/* 客户端版本号文件		*/
#define DYN_NEWS_INI_FILE		"dynnews.ini"			/* 滚动新闻文件	*/
#define WELCOME_HTM_FILE		"welcome.htm"			/* 欢迎信息文件	*/
#define USERDEF_INFO_INI_FILE	"userdefinfo.ini"		/* 自定义配置资讯文件	*/
#define INFO_PATH_INI_FILE		"infopath.ini"			/* 资讯路径配置文件*/
#define SYS_BLOCK_FILE			"sysblock"				/* 系统板块数据名称，配置文件扩展名：INI，数据文件扩展名：DAT*/
#define EX_RIGHT_FILE			"exright.dat"			/* 除权数据文件 */
#define CURRENT_FINANCE_FILE	"curfinance.fin"		/* 最新财务数据 */
#define INFO_TREE_INI_FILE		"InfoTree.ini"			/* 资讯树配置文件 */
#define NEW_INFO_TREE_INI_FILE	"InfoTreeConfig.ini"	/* 资讯树配置文件  added 20110915 避免删除*/

#define HIS_FINANCE_DAT_FILE	"hisfinance.dat"		/* 历史财务报表数据文件 */
#define SECRET_TREE_INI_FILE	"secrettree.ini"		/* 秘籍树 */
#define BASE_INFO_TREE_INI_FILE	"baseinfotree.ini"		/* 基本资料树 */

#define SERVER_SETTING_INI_FILE	"serversetting.ini"		// 服务器配置信息文件 

#define SJSXXN_tishi_duizhaobiao	"sjsxxn.ini"		// 交易所提示信息对照表
#define SRV_condition				"condition.ini"		// 服务器选股配置文件

//yangdl 2008.01.15 外汇中心债券对照表.ini
//yangdl 2008.03.06 更改配置文件名
#define SRV_Foreign_Code            "ForeignCurrencyBond_List.ini" //外汇中心债券对照表
#define SRV_PriceOffer_Code         "PriceOffer_Code.ini"          //报价方代码对照表

// 2004年6月28日 为多金融加入的资讯配置定义 讯捷软件有限公司
#define S_INFO_Stock			"infoconfig.ini"		// 行情资讯配置（服务器端）
#define S_INFO_Futures			"ft_infoconfig.ini"		// 期货资讯配置（服务器端）
#define S_INFO_Foreign			"fr_infoconfig.ini"		// 外汇资讯配置（服务器端）
#define S_INFO_Finance			"zx_infoconfig.ini"		// 财务分析资讯配置（服务器端）
#define S_INFO_HK				"hk_infoconfig.ini"		// 港股资讯配置（服务器端）

#define C_INFO_Stock_Tree		INFO_TREE_INI_FILE		/* 股票资讯树配置文件 */
#define C_INFO_Stock_Path		INFO_PATH_INI_FILE		/* 股票资讯路径配置文件*/

#define C_INFO_Futures_Tree		"ft_infotree.ini"		/* 期货资讯树配置文件 */
#define C_INFO_Futures_Path		"ft_infopath.ini"		/* 期货资讯路径配置文件*/

#define C_INFO_Foreign_Tree		"fr_infotree.ini"		/* 外汇资讯树配置文件 */
#define C_INFO_Foreign_Path		"fr_infopath.ini"		/* 外汇资讯路径配置文件*/

#define C_INFO_HK_Tree			"hk_infotree.ini"		/* 港股资讯树配置文件 */
#define C_INFO_HK_Path			"hk_infopath.ini"		/* 港股资讯路径配置文件*/

#define C_INFO_Finance_Tree		SECRET_TREE_INI_FILE		/* 基本资料树 */
#define C_INFO_Finance_Path		BASE_INFO_TREE_INI_FILE		/* 秘籍树*/

#define S_HK_SYS_BLOCK_FILE		"hksysblock"			/* 系统板块数据名称，配置文件扩展名：INI，数据文件扩展名：DAT*/
#define SC_HK_STATIC_FILE		"hkstatic.dat"			/* 港股静态信息数据文件*/
#define SC_FT_STATIC_FILE		"qhstatic.dat"			// 期货静态信息数据文件：合约信息
#define SC_HK_FINANCE_FILE		"hkfinance.dat"			// 港股财务数据文件

// gbq add 20060208, 焦作特色服务需求, 增加配置文件
#define SERVICE_TREE_INI_FILE	"ServiceTree.ini"		//焦作特色菜单配置文件
// gbq add end;
/* 文件名称定义 DEFINE END */


#define INFO_PATH_KEY_F10				 "%sF10资讯路径"   // F10资讯
#define INFO_PATH_KEY_TREND				 "%s分时资讯路径"  // 分时资讯
#define INFO_PATH_KEY_TECH				 "%s盘后资讯路径"  // 盘后资讯
#define INFO_PATH_KEY_REPORT			 "%s报表资讯路径"  // 报表资讯
#define INFO_PATH_KEY_SPEC				 "%s特色资讯路径"  // 特色资讯

#endif /* _HS_CONST_HEADER_FILE_ */





#if 0 //old
/*******************************************************************************
* Copyright (c)2003, 讯捷软件有限公司
* All rights reserved.
*
* 文件名称：HSConstDefine.h
* 文件标识：常量定义
* 摘    要：常量定义
*
* 当前版本：xfd2003
* 作    者：讯捷软件有限公司
* 完成日期：2003-07
* 备	注：
*
* 日	期：2004-03-09
* 作	者：讯捷软件有限公司
* 修改内容：增加资讯相关的宏定义
*
* 日	期：2004年7月7日
* 作	者：讯捷软件有限公司
* 修改内容：增加多金融相关的宏定义
*******************************************************************************/
#ifndef _HS_CONST_HEADER_FILE_
#define _HS_CONST_HEADER_FILE_

/* 文件名称定义 DEFINE BEGIN */
#define CLIENT_VERSION_INI_FILE	"clientversion.ini"		/* 客户端版本号文件		*/
#define DYN_NEWS_INI_FILE		"dynnews.ini"			/* 滚动新闻文件	*/
#define WELCOME_HTM_FILE		"welcome.htm"			/* 欢迎信息文件	*/
#define USERDEF_INFO_INI_FILE	"userdefinfo.ini"		/* 自定义配置资讯文件	*/
#define INFO_PATH_INI_FILE		"infopath.ini"			/* 资讯路径配置文件*/
#define SYS_BLOCK_FILE			"sysblock"				/* 系统板块数据名称，配置文件扩展名：INI，数据文件扩展名：DAT*/
#define EX_RIGHT_FILE			"exright.dat"			/* 除权数据文件 */
#define CURRENT_FINANCE_FILE	"curfinance.fin"		/* 最新财务数据 */
#define INFO_TREE_INI_FILE		"InfoTree.ini"			/* 资讯树配置文件 */
#define NEW_INFO_TREE_INI_FILE	"InfoTreeConfig.ini"	/* 资讯树配置文件  added 20110915 避免删除*/


#define HIS_FINANCE_DAT_FILE	"hisfinance.dat"		/* 历史财务报表数据文件 */
#define SECRET_TREE_INI_FILE	"secrettree.ini"		/* 秘籍树 */
#define BASE_INFO_TREE_INI_FILE	"baseinfotree.ini"		/* 基本资料树 */

#define SERVER_SETTING_INI_FILE	"serversetting.ini"		// 服务器配置信息文件 

// 2004年6月28日 为多金融加入的资讯配置定义 讯捷软件有限公司
#define S_INFO_Stock			"infoconfig.ini"		// 行情资讯配置（服务器端）
#define S_INFO_Futures			"ft_infoconfig.ini"		// 期货资讯配置（服务器端）
#define S_INFO_Foreign			"fr_infoconfig.ini"		// 外汇资讯配置（服务器端）
#define S_INFO_Finance			"zx_infoconfig.ini"		// 财务分析资讯配置（服务器端）
#define S_INFO_HK				"hk_infoconfig.ini"		// 港股资讯配置（服务器端）

#define C_INFO_Stock_Tree		INFO_TREE_INI_FILE		/* 股票资讯树配置文件 */
#define C_INFO_Stock_Path		INFO_PATH_INI_FILE		/* 股票资讯路径配置文件*/

#define C_INFO_Futures_Tree		"ft_infotree.ini"		/* 期货资讯树配置文件 */
#define C_INFO_Futures_Path		"ft_infopath.ini"		/* 期货资讯路径配置文件*/

#define C_INFO_Foreign_Tree		"fr_infotree.ini"		/* 外汇资讯树配置文件 */
#define C_INFO_Foreign_Path		"fr_infopath.ini"		/* 外汇资讯路径配置文件*/

#define C_INFO_HK_Tree			"hk_infotree.ini"		/* 港股资讯树配置文件 */
#define C_INFO_HK_Path			"hk_infopath.ini"		/* 港股资讯路径配置文件*/

#define C_INFO_Finance_Tree		SECRET_TREE_INI_FILE		/* 基本资料树 */
#define C_INFO_Finance_Path		BASE_INFO_TREE_INI_FILE		/* 秘籍树*/

#define S_HK_SYS_BLOCK_FILE		"hksysblock"			/* 系统板块数据名称，配置文件扩展名：INI，数据文件扩展名：DAT*/
#define SC_HK_STATIC_FILE		"hkstatic.dat"			/* 港股静态信息数据文件*/
#define SC_FT_STATIC_FILE		"qhstatic.dat"			// 期货静态信息数据文件：合约信息
#define SC_HK_FINANCE_FILE		"hkfinance.dat"			// 港股财务数据文件

/* 文件名称定义 DEFINE END */


#define INFO_PATH_KEY_F10				 "%sF10资讯路径"   // F10资讯
#define INFO_PATH_KEY_TREND				 "%s分时资讯路径"  // 分时资讯
#define INFO_PATH_KEY_TECH				 "%s盘后资讯路径"  // 盘后资讯
#define INFO_PATH_KEY_REPORT			 "%s报表资讯路径"  // 报表资讯
#define INFO_PATH_KEY_SPEC				 "%s特色资讯路径"  // 特色资讯

#endif /* _HS_CONST_HEADER_FILE_ */
#endif