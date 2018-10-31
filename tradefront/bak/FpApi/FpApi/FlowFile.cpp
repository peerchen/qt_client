#include "FlowFile.h"
#include "CRC32.h"
#include "Api.h"
#define MAX_BUFFLEN 4096
#define LENGTH_SIZE 2
#define SEQNO_SIZE 10
CFlowFile::CFlowFile()
{
	m_ullStartSeqNo = 0;
	m_ullLastSeqNo = 0;
	m_sFileDate = "";
}
CFlowFile::~CFlowFile()
{
	if (m_fStream.is_open())
	{
		m_fStream.clear();
		m_fStream.close();
	}
	m_mapIndex.clear();
}
//打开流文件
int CFlowFile::OpenFlowFile(const char * fileName)
{
	if (m_fStream.is_open())
	{
		m_fStream.clear();
		m_fStream.close();
	}else
	{
		//判断文件是否存在
		m_fStream.open(fileName,fstream::in);
		if (m_fStream == 0)
		{
			m_fStream.open(fileName,fstream::in | fstream::out | fstream::binary| fstream::trunc);
		}
		m_fStream.clear();
		m_fStream.close();
	}
	m_fStream.open(fileName,fstream::in | fstream::out | fstream::binary);
	if (m_fStream.fail())
	{
		m_fStream.clear();
		m_fStream.close();
		m_fStream.open(fileName,fstream::in | fstream::out | fstream::binary| fstream::trunc);
	}
	m_fStream.seekg(0,ios_base::beg);
	return 0;
}
//关闭流文件
void CFlowFile::CloseFlowFile()
{
	m_fStream.clear();
	m_fStream.close();
}
//清空流文件
int CFlowFile::ClearFlowFile()
{
	string fileName = "data_";
	fileName += m_cSeriesNo;
	//关闭文件
	if (m_fStream.is_open())
	{
		m_fStream.clear();
		m_fStream.close();
	}
	//使用重新创建的方式打开文件
	m_fStream.open(fileName.c_str(),fstream::in | fstream::out | fstream::binary| fstream::trunc);
	if (m_fStream.fail())
	{
		m_fStream.clear();
		m_fStream.close();
		m_fStream.open(fileName.c_str(),fstream::in | fstream::out | fstream::binary| fstream::trunc);
	}
	m_fStream.clear();
	m_fStream.close();
	m_sFileDate = "-";
	m_ullLastSeqNo = 0;
	m_ullStartSeqNo = 0;
	m_mapIndex.clear();
	m_cSeriesNo = 0;
	return 0;
}
//验证流文件，加载索引
int CFlowFile::LoadFlowFile(int nSeriesNo)
{
	try
	{
		m_cSeriesNo = nSeriesNo+'0';
		string fileName = "data_";
		fileName += m_cSeriesNo;
		//从会员前置收到的交易日期 
		//string sTradeDate;//此时还没有收到交易日期
		OpenFlowFile(fileName.c_str());
		if (m_fStream.fail())
		{
			CRLog(E_ERROR,"Stream file [%s]read failed！",fileName.c_str());
			return -1;
		}
		//初始化
		m_sFileDate = "-";
		m_ullLastSeqNo = 0;
		m_ullStartSeqNo = 0;
		m_mapIndex.clear();

		char szTradeDate[9] = {0};
		m_fStream.read(szTradeDate,sizeof(szTradeDate)-1);
		szTradeDate[8] = '\0';
		if (m_fStream.gcount() == 0)
		{
			//读取长度为0，表示文件为空，
			//OpenFlowFile(fileName);
			m_fStream.clear();
			m_fStream.seekg(0,ios_base::beg);
			m_sFileDate = "-";
			return 0;
		}else if (m_fStream.gcount() != 8)
		{
			//流文件读取日期出错
			CRLog(E_ERROR,"Stream file [%s]read the date wrong！",fileName.c_str());
			return -2;
		}
		m_sFileDate = szTradeDate;
		//操作流文件缓存空间
		char szBuf[MAX_BUFFLEN] = {0};
		string sRecord;
		unsigned int numPacket = 0;
		fstream::pos_type pos = 0;
		while (1)
		{	

			pos = m_fStream.tellg();
			//获得下一条记录
			int nReadRtn = ReadRecordFromFilePos(sRecord,pos);
			if (m_fStream.eof())
			{
				//Load结束
				m_fStream.clear();
				//返回load了多少报文
				return numPacket;
			}
			if ( nReadRtn == -1)
			{
				//从流文件中读取记录失败
				return -3;
			}else if (nReadRtn == -2)
			{
				//CRC检查发现错误
				return -4;
			}
			//记录最新序列号
			string sSqlNo = sRecord.substr(LENGTH_SIZE,SEQNO_SIZE);
			UINT64  ullSqlNo = FromString<UINT64>(sSqlNo);
			if (m_ullLastSeqNo +1 != ullSqlNo && m_ullLastSeqNo != 0)
			{
				//序列号没有递增
				return -5;
			}
			m_ullLastSeqNo = ullSqlNo;
			if (numPacket == 0)
			{
				//记录第一条索引号
				m_ullStartSeqNo = m_ullLastSeqNo;
			}
			//插入索引
			m_mapIndex[m_ullLastSeqNo] = pos;
			//读取一条信息成功
			numPacket++;
		}
		return 0;
	}
	catch (...)
	{
		
	}

	return 0;
}
//把对应报文写入流文件
int CFlowFile::WriteToFlowFile(const char * sPacket,int pktLen,UINT64 ullSqlNo)
{
	if (m_ullLastSeqNo +1 != ullSqlNo && m_ullLastSeqNo != 0)
	{
		return -1;
	}
	if (!m_fStream.is_open())
	{
		//文件未打开
		return -2;
	}
	//写指针定位到文件最末
	m_fStream.seekp(0,ios_base::end);
	std::string sRecord;
	unsigned int len = 0;
	//预留长度位置
	sRecord.append(LENGTH_SIZE,0x00);
	len += LENGTH_SIZE;
	//获得序号
	string sSqlNo = ToString<UINT64>(ullSqlNo);
	sSqlNo = StrAddZero(sSqlNo);
	sRecord.append(sSqlNo.c_str(),SEQNO_SIZE);
	len += SEQNO_SIZE;
	//写入报文
	sRecord.append(sPacket,pktLen);
	len += pktLen;
	//写长度
	len += sizeof(unsigned int);
	char * pLen;
	pLen = (char *)&len;
	sRecord[0] = *pLen;
	pLen++;
	sRecord[1] = *pLen;
	//sRecord.replace(0,2,pLen);
	//计算校验
	unsigned int uiCrc32 = CCRC32::crc32_loader((unsigned char *)sRecord.data(),sRecord.length());
	sRecord.append((char*)(&uiCrc32),sizeof(unsigned int));

	//写入文件
	m_fStream.write(sRecord.c_str(),len);
	m_fStream.flush();
	len = sRecord.length();
	m_ullLastSeqNo = ullSqlNo;
	return len;
}
//根据制定序列号，读取流文件中对应报文并入队列
int CFlowFile::ReadFromFlowFile(UINT64 ullSqlNo,int enumType)
{
	map<UINT64 ,fstream::pos_type>::iterator itPos;
	itPos = m_mapIndex.find(ullSqlNo);
	if (itPos == m_mapIndex.end())
	{
		//没有缓存该索引
		return -1;
	}
	if (!m_fStream.is_open())
	{
		//文件未打开
		return -2;
	}
	string sRecord;
	while(itPos != m_mapIndex.end())
	{
		//根据索引获得读指针
		fstream::pos_type pRead = itPos->second;
		//设置读指针
		//m_fStream.seekg(pRead,ios_base::beg);
		//获得下一条记录
		int nReadRtn = ReadRecordFromFilePos(sRecord,pRead);

		if ( nReadRtn == -1)
		{
			//从流文件中读取记录失败
			return -3;
		}else if (nReadRtn == -2)
		{
			//CRC检查发现错误
			return -4;
		}
		//根据读取的记录获得报文
		CGtpPacket pkt(sRecord.substr(LENGTH_SIZE+SEQNO_SIZE,sRecord.length()-LENGTH_SIZE-SEQNO_SIZE-sizeof(unsigned int)));
		//将报文入历史队列
		if (enumType == 0)
		{
			m_api->EnqueBroadcastRecv(pkt);
		}else
		{
			m_api->EnqueTradeRecv(pkt);
		}
		
		++ ullSqlNo;
		itPos = m_mapIndex.find(ullSqlNo);
	}
	return 0;
}
int CFlowFile::EqualDate(string date)
{
	if (m_sFileDate == "-")
	{
		//流文件为空
		m_sFileDate = date;
		//将交易日期写入流文件
		m_fStream.seekp(0,ios_base::end);
		m_fStream.write(m_sFileDate.c_str(),m_sFileDate.length());
		m_fStream.flush();
		return 1;
	}else if (m_sFileDate == date)
	{
		return 0;
	}
	return -1;
}
int CFlowFile::ReadRecordFromFilePos(string &sRecord,fstream::pos_type pos)
{
	if (!m_fStream.is_open())
	{
		//文件未打开
		return -3;
	}
	int numPacket = 0;
	sRecord = "";
	unsigned short int  len = 0;
	unsigned int uiCrc32Len = sizeof(unsigned int);
	char szBuf[MAX_BUFFLEN] = {0};
	m_fStream.seekg(pos,ios_base::beg);
	//读 长度
	char sLen[2]={0,0};
	m_fStream.read(sLen,LENGTH_SIZE);
	char * p = (char *)& len;
	*p = sLen[0];
	p++;
	*p = sLen[1];
	if (len < sizeof(unsigned int)+LENGTH_SIZE+SEQNO_SIZE)
	{
		//读取流文件出错
		return -1;
	}
	sRecord.append(sLen,LENGTH_SIZE);
	memset(szBuf,0x00,sizeof(szBuf));
	unsigned short int readLen = len-LENGTH_SIZE;
	
	while (readLen > MAX_BUFFLEN)
	{
		m_fStream.read(szBuf,MAX_BUFFLEN);
		if (m_fStream.gcount() != MAX_BUFFLEN)
		{
			//读取流文件出错
			return -1;
		}
		sRecord.append(szBuf,MAX_BUFFLEN);
		readLen -= MAX_BUFFLEN;
	}
	if (readLen > 0)
	{
		m_fStream.read(szBuf,readLen);
		if (m_fStream.gcount() != readLen)
		{
			//读取流文件出错
			return -1;
		}
		sRecord.append(szBuf,readLen);
	}
	//CRC检查
	unsigned int uiCrc32Val = *((unsigned int *)(sRecord.c_str()+len-uiCrc32Len));
	unsigned int uiCrc32Cal = CCRC32::crc32_loader((unsigned char*)sRecord.c_str(),len-uiCrc32Len);
	if (uiCrc32Val != uiCrc32Cal)
	{
		//CRC检查发现错误
		return -2;
	}
	return sRecord.length();
}
int CFlowFile::bind(CApi * api)
{
	if (api == NULL)
	{
		return -1;
	}
	m_api = api;
	return 0;
}
// string CFlowFile::StrDelZero(string s1)
// {
// 	string result;
// 	int size = s1.size();
// 	int i = 0;
// 	for(i;i<size;i++)
// 	{
// 		if (s1[i] != '0')
// 		{
// 			//从数值高位开始找第一个不为0的值
// 			break;
// 		}
// 	}
// 	if (i == size)
// 	{
// 		//整个字符串由‘0’组成
// 		result = "0";
// 	}else
// 	{
// 		result = s1.substr(i);
// 	}
// 	return result;
// }
string CFlowFile::StrAddZero(string s1)
{
	string result;
	int size = s1.size();
	result.append(10-size,'0');
	result = result + s1;
	return result;
}
// string CFlowFile::StrAddOne(string s1)
// {
// 	string result;
// 	s1 = StrDelZero(s1);
// 	if (s1 == "9999999999")
// 	{
// 		result = "0";
// 	}else
// 	{
// 		int size = s1.size();
// 		int i ;
// 		for (i = size-1; i > -1;i--)
// 		{
// 			if (s1[i] == '9')
// 			{
// 				s1[i] = '0';
// 			}else
// 			{
// 				s1[i] += 1;
// 				//不需要进位，退出循环
// 				break;
// 			}
// 		}
// 		if (i == -1)
// 		{
// 			//说明最高位还有一个进位。
// 			result = "1";
// 			result = result + s1;
// 		}else
// 		{
// 			result = s1;
// 		}
// 	}
// 	return result;
// }