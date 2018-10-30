#ifndef _CompileOption_H
#define _CompileOption_H

#define Send_Version	"版本: 4.00.02.08"
#define Receive_Version "版本: 4.00.02.08"
#define Server_Version  "版本: 4.00.02.08"

#define Support_Manager_Start   		      // 是否使用管理程序启动

//#define Support_RawSend

// 发送端、接收端
//#define Support_DHJR						  // 是否为东航专用
 
//#define Support_XHS							  // 是否为新华社专用

//#define Support_JiaoHang_AutoEvery		  // 支持交行(外汇)服务器自动添加主推数据列表

// 
#ifdef Support_XHS
#	define Support_GGTime					  // 使用港股接口时间
#	define Support_GGIndex		              // 是否支持港股文本指数接口
#endif

//
#ifdef Support_DHJR

#	define Support_WHTime	    	      // 使用外汇接口时间

#	define Support_WPTime	    	      // 使用外盘接口时间

#	define Support_GGTime		          // 使用港股接口时间
#	define Support_GGIndex		          // 是否支持港股文本指数接口
#	define Support_GGExternData           // 港股支持外部配置数据，如：市盈率、周息率、买卖价差

#else

// 发送端、接收端
#	define Support_WHStandardCode        // 外汇使用标准分类码，如:USD

// 使用虚拟分类,只对外盘使用,指针对于文化
#	define Support_UsedVirtualClass    

// 外盘使用机器时间
#	define Support_WP_UsedLocalTime

#endif


// 外盘行情显示时间使用固定区间,参见：g_szWPDefaultTime 定义,在发送断使用
//#define Support_WP_UsedFiedTime		

// 发送端、接收端
//#define SUPPORT_UDP_STOCK			  // 国内股票是否为UDP行情

// 服务器、发送端、接收端
//#define Support_Test			      // 是否为临时测试使用

// 发送端、、服务器
#define Support_YTJK				  // 是否支持倚天接口

// 接收端
//#define Support_YTJK_Accept		  // 是否支持倚天接口


#if defined(Support_DHJR) || defined(Support_JiaoHang_AutoEvery)

#define _Support_LargeTick			  // 使用大的分笔数据

#endif



#ifndef _Support_LargeTick
//#define Support_MaiMai			  // 最小分笔时保存买卖盘明细
#endif


#define Support_DFX					  // 支持dfx行情客户端请求

#ifdef WIN32
#define HS_SUPPORT_GIF				  // 支持gif图片请求
#endif

//#define WORDS_BIGENDIAN			  // 支持linux(sun)字节序转换

#ifndef WORDS_BIGENDIAN				  // 是否支持字节转换

#	define Support_Used_Old_HistoryTendHead // 是否使用旧的历史回忆数据结构

#endif







#ifndef HS_SUPPORT_UNIX

#ifdef Support_MaiMai
#pragma message("支持买卖盘明细")
#endif

#ifdef Support_Test
#pragma message("当前为测试方式")
#endif

#ifdef SUPPORT_UDP_STOCK
#pragma message("国内股票为UDP方式接收行情")
#endif

#endif	 // HS_SUPPORT_UNIX

#endif
