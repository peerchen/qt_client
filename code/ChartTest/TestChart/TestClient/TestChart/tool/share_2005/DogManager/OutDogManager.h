
/*******************************************************************************
* Copyright (c)2003, 
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：1.2
* 作    者：
* 完成日期：2001
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/



#if !defined(OutDogManager_h_)
#define OutDogManager_h_


#ifdef _DEBUG
	#pragma comment(lib,"..\\..\\Share_2005\\lib\\debug\\DogManager.lib") 
	#pragma message("Automatically linking with ..\\..\\Share_2005\\lib\\debug\\DogManager.lib")  
#else
	#pragma comment(lib,"..\\..\\Share_2005\\lib\\Release\\DogManager.lib") 
	#pragma message("Automatically linking with ..\\..\\Share_2005\\lib\\Release\\DogManager.lib")  
#endif

#include "SysInfo.h"
#include "doginfofile.h"
#include "../comm/programstatus.h"

//#include "ProcessMgr.h"
//#include "Processes.h"

#endif // OutDogManager_h_

