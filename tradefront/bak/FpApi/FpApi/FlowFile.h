#ifndef FLOW_FILE_H
#define FLOW_FILE_H
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "Comm.h"
#include "strutils.h"
#ifndef _WIN32
typedef unsigned long long    UINT64, *PUINT64;
#endif
using namespace std;
using namespace strutils;
struct CApi;
class CFlowFile
{
public:
	CFlowFile();
	~CFlowFile();

	//清空流文件
	int ClearFlowFile();
	//验证流文件，加载索引
	int LoadFlowFile(int nSeriesNo);
	//关闭流文件
	void CloseFlowFile();
	//把对应报文写入流文件,返回-1，表示seqNo比流文件中最新序号大，为异常现象；返回0，表示seqNo比流文件中最新序号小，为历史报文，不写流文件；
	//返回>0的数字，表示写入流文件的长度
	//输入seqNo为序列号(最多10位)
	int WriteToFlowFile(const char * sPacket,int pktLen,UINT64 seqNo);
	//根据指定序列号取得流文件索引，读取流文件中对应报文并入队列
	int ReadFromFlowFile(UINT64 seqNo,int enumType);
	//判断流文件交易日期是否正确，在写入流文件前需要先判断该项。
	int EqualDate(string date);
	//绑定api节点
	int bind(CApi * api);
	UINT64 GetLastSequenceNo(void){return m_ullLastSeqNo;}
	UINT64 GetStartSequenceNo(void){return m_ullStartSeqNo;}
private:
	//从制定位置读取一条记录
	int ReadRecordFromFilePos(string &sRecord,fstream::pos_type pos);
	//打开流文件
	int OpenFlowFile(const char * fileName);
// 	//返回s1数值+1的结果
// 	string StrAddOne(string s1);
// 	//去除str前面的‘0’
// 	string StrDelZero(string s1);
 	//在str前面填充‘0’ 至10位
 	string StrAddZero(string s1);
private:
	//流文件指针
	fstream m_fStream;
	//文件地址索引
	std::map < UINT64,fstream::pos_type > m_mapIndex;
	//流文件内记录的交易日期
	string m_sFileDate;
	//起始序列号
	UINT64 m_ullStartSeqNo;
	//最新序列号
	UINT64 m_ullLastSeqNo;

	CApi * m_api;
	char m_cSeriesNo;
};
#endif