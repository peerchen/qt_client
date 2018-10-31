// MsgHead.h: interface for the CMsgHead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGHEAD_H__C023DB8B_F5EB_4200_A616_E4D4FD0B95FC__INCLUDED_)
#define AFX_MSGHEAD_H__C023DB8B_F5EB_4200_A616_E4D4FD0B95FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "public.h"
#include "BpcHead.h"
#include "BF_Mutex.h"
#include "MdbBase.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	//字节对齐
#ifdef _WINDOWS
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
	//#pragma pack(push,1)
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif


#define  ROOTID_LENGTH     10    //ROOTID的长度

//保存需要应答的消息头信息，SGE应答回来后根据此头应答给请求方
typedef struct 
{
	char          sRootId[ROOTID_LENGTH+1];//后台送来的唯一序号，根据此序号查找
	unsigned  int nTimeStamp;//放入时间
	S_BPC_HEAD    sBpcHead;        //  nBpuIndex保存是总线过来还是侦听过来，0总线 1侦听  nIndex表示过来的连接索引 nConnectTime为时间戳
	DREB_HEAD     sDBHead;         //dreb头
}__PACKED__ S_MSG_HEAD_STRU; 

//取消字节对齐
#ifdef _WINDOWS
#pragma pack(pop)
#else
#ifdef __GNUC__
//#pragma pack(pop)
#else
#pragma options align=reset
#endif
#endif
#undef __PACKED__

#ifdef __cplusplus
}
#endif



class CMsgHead  
{
public:

	// 函数名: Update
	// 编程  : 王明松 2016-3-24 15:43:21
	// 返回  : void 
	// 描述  : 更新，删除过期的报文头，防止报文越来越多
	void Update();

	// 函数名: GetHead
	// 编程  : 王明松 2016-3-24 15:40:49
	// 返回  : bool 
	// 参数  : const char *rootid   报文头标识
	// 参数  : BPCCOMMSTRU &data    报文头
	// 参数  : bool isdel=true      是否删除此报文头   当有后续应答时不用删除
	// 描述  : 取得原报文头
	bool GetHead(const char *rootid,BPCCOMMSTRU &data,bool isdel=true);

	// 函数名: Insert
	// 编程  : 王明松 2016-3-24 15:40:02
	// 返回  : bool 
	// 参数  : const char *rootid
	// 参数  : BPCCOMMSTRU data
	// 描述  : 将报文头放入缓存表，供应答时使用
	bool Insert(const char *rootid,BPCCOMMSTRU data);
	CMsgHead();
	virtual ~CMsgHead();


protected:
	CBF_Mutex  m_mutex;

	CMemTable <S_MSG_HEAD_STRU> m_table;        //内存表
	CPkeyCharF<ROOTID_LENGTH,1>             m_key;          //rootid主键

};

#endif // !defined(AFX_MSGHEAD_H__C023DB8B_F5EB_4200_A616_E4D4FD0B95FC__INCLUDED_)
