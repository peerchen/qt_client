/*******************************************************************************
* Copyright (c)2003, ��������ϵͳ���޹�˾
* All rights reserved.
*
* �ļ����ƣ�*.h
* �ļ���ʶ��
* ժ    Ҫ��
*
* ��ǰ�汾��YLink1.2
* ��    �ߣ�YLink����
* ������ڣ�2005
*
* ��    ע��
*
* �޸ļ�¼��
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
// http ���ݹ���
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


// ����
#include "mainframebase.h"
#include "recievesession.h"
#include "marketinfomanager.h"
#include "zixundata.h"


// ����
#include "marketinfomanager_send.h"
#include "sendsession.h"
#include "mainframesend.h"


#endif // OutShareFile_h_
