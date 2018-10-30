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

#if !defined(OutShareFile_h_)
#define OutShareFile_h_

#ifndef HS_SUPPORT_UNIX

#ifdef _DEBUG
	#pragma comment(lib,"..\\..\\Share_2005\\lib\\debug\\ShareFile.lib") 
	//#pragma message("Automatically linking with ..\\..\\Share\\lib\\debug\\ShareFile.lib")  
#else
	#pragma comment(lib,"..\\..\\Share_2005\\lib\\Release\\ShareFile.lib") 
	//#pragma message("Automatically linking with ..\\..\\Share\\lib\\Release\\ShareFile.lib")  
#endif

#endif

#include "stdafx.h"

#include "tool.h"

#include "ylsstring.h"
#include "ylsmapwordtoptr.h"
#include "ylstypedptrmap.h"
#include "ylsptrlist.h"
#include "ylstime.h"
#include "ylsmapstringtoptr.h"
#include "ylsmapptrtoptr.h"
#include "ylsarrayobj.h"

#include "ylsfile.h"

#include "hsserverdatapath.h"
#include "servermarketinfo.h"
#include "serverstructex.h"
#include "hssortdata.h"
#include "hs_disk_h.h"
#include "globalfun.h"

//#include "ylsinifile.h"
#include "ylsini.h"

#include "ylsmemfile.h"
#include "sharedmemory.h"


#include "ylsbasedoc.h"
#include "ylssession.h"

#if defined(HS_SUPPORT_HTTP) || defined(WIN32)//#ifdef HS_SUPPORT_HTTP
// http 数据管理
#include "httpreqsock.h"
#endif

#ifdef Suppor_CompletionPortModel
#include "CompletionPortModel.h"
#endif

#include "ylsclog.h"
#include "hqses.h"

#include "datasock.h"

#include "ylssocket.h"

#include "readhq.h"

#include "quoteres.h"

#include "hsdes.h"

#ifndef HS_SUPPORT_UNIX
#include "usermanager.h"
#include "info.h"
#endif


// 接收
#include "mainframebase.h"
#include "recievesession.h"
#include "marketinfomanager.h"
#include "zixundata.h"


// 发送
#include "marketinfomanager_send.h"
#include "sendsession.h"
#include "mainframesend.h"


#endif // OutShareFile_h_
