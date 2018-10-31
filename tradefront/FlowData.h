// FlowData.h: interface for the CFlowData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOWDATA_H__54F4047A_7C42_435C_8E6D_62987DB9898D__INCLUDED_)
#define AFX_FLOWDATA_H__54F4047A_7C42_435C_8E6D_62987DB9898D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "public.h"
#include "BF_Date_Time.h"
#include "IErrLog.h"
#include "PoolData.h"
#include "BF_DrebServer.h"
#include "SocketMgr.h"
#include "IOfferingBase.h"
#include "KvData.h"
//SGE的流文件类，将回报、通知等按类型写入文件

//目录结构为  交易日期目录+  流文件  (序号+交易码+内容)
//            断点文件   交易日期+每个流文件最大序号
// 数据流	消息序列类别号
// 交易流	1
// 回报流	2
// 私有流	3
// 公共流	4
// 查询流	5
// 行情流	6

// typedef struct 
// {
// 	int           nFlowNo;//消息类别号
// 	unsigned int  nMaxSerial;//最大流水号
// }S_FLOW_INFO;
// #define  MAXFLOWNO     6

class CFlowData  
{
public:
	void WriteBreakPoint();
	
	void SetPara(CIErrlog *log ,CSocketMgr *smgr,CBF_DrebServer *api,CTradeResource *res);

	// 函数名: Login
	// 编程  : 王明松 2016-4-11 9:36:07
	// 返回  : void 0不用日切  1日切
	// 参数  : const char *txdate
	// 描述  : 交易员登录，返回交易日期，判断是否重新记流
	int Login(const char *txdate);

	// 函数名: GetFlowData
	// 编程  : 王明松 2016-4-8 17:04:41
	// 返回  : bool true有，还得继
	// 输入参数  : std::vector<S_FLOW_INFO> &bplist   断点列表 
	// 输入参数  : BPCCOMMSTRU &data
	// 输入参数  : CKvData *kvdata  类
	// 描述  : 取流数据，发送
	bool GetFlowData(std::vector<S_FLOW_INFO> &bplist,BPCCOMMSTRU &data,CKvData *kvdata);

	// 函数名: WriteFlow
	// 编程  : 王明松 2016-4-8 16:29:01
	// 返回  : bool 
	// 输入参数  : int type  流类型
	// 输入参数  : unsigned int serial 流序号   若流序号小于等于当前的则不写入，否则写入
	// 输入参数  : unsigned int txcode 7位交易码
	// 输入参数  : BPCCOMMSTRU data
	// 描述  : 写流文件
	bool WriteFlow(int type,unsigned int serial,unsigned int txcode,BPCCOMMSTRU data);
	

	// 函数名: Init
	// 编程  : 王明松 2016-4-8 10:57:44
	// 返回  : bool 
	// 描述  : 初始化，读取本地的断点文件，若有则去读取，否则以当前日期生成本地断点文件。
	bool Init();
	CFlowData();
	virtual ~CFlowData();

	S_FLOW_INFO m_FlowInfo[MAXFLOWNO];//保存各消息最大序号的结构数据

	bool  m_bIsrun;

protected:

	int SendBack(BPCCOMMSTRU &data,CKvData *kvdata);

	// 函数名: HEX_2_DSP
	// 编程  : 王明松 2012-4-11 13:31:26
	// 返回  : void 
	// 输入参数  : const char *hex  数据
	// 输出参数  : char *dsp  可显示的内容  1-9,A-F
	// 输入参数  : int count hex的长度
	// 描述  : 将数据转换为16进制显示，转换后的数据长度为count*2
	void HEX_2_DSP(const char *hex,char *dsp,int count);
	
	// 函数名: DSP_2_HEX
	// 编程  : 王明松 2012-4-11 13:33:10
	// 返回  : void 
	// 输入参数  : const char *dsp  可显示的内容  1-9,A-F
	// 输出参数  : char *hex  实际数据
	// 输入参数  : int count  dsp长度
	// 描述  : 将16进制显示的数据转换为实际数据,转换后的数据长度为count/2
	void DSP_2_HEX(const char *dsp,char *hex,int count);
	
	// 函数名: ReadFlowInfo
	// 编程  : 王明松 2016-4-8 15:27:01
	// 返回  : void 
	// 参数  : const char *datepath
	// 描述  : 从交易日期对应的目录读取断点信息
	void ReadFlowInfo(const char *datepath);

	// 函数名: ResetFlowInfo
	// 编程  : 王明松 2016-4-8 15:26:45
	// 返回  : void 
	// 描述  : 重置断点信息
	void ResetFlowInfo();

	char m_sTxDate[9]; //交易日期
	

	CBF_Date_Time  m_pDate;
	CIErrlog      *m_pLog;
	CSocketMgr    *m_pSockMgr;
	CBF_DrebServer *m_pDrebApi;//api
	
	CTradeResource  *m_pRes;

	CBF_Mutex    m_pWmutex;
	std::string  m_sCurPath;
	std::string  m_sFlowFilePath;
	
};

#endif // !defined(AFX_FLOWDATA_H__54F4047A_7C42_435C_8E6D_62987DB9898D__INCLUDED_)
