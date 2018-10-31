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
//�����ļ�
int CFlowFile::OpenFlowFile(const char * fileName)
{
	if (m_fStream.is_open())
	{
		m_fStream.clear();
		m_fStream.close();
	}else
	{
		//�ж��ļ��Ƿ����
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
//�ر����ļ�
void CFlowFile::CloseFlowFile()
{
	m_fStream.clear();
	m_fStream.close();
}
//������ļ�
int CFlowFile::ClearFlowFile()
{
	string fileName = "data_";
	fileName += m_cSeriesNo;
	//�ر��ļ�
	if (m_fStream.is_open())
	{
		m_fStream.clear();
		m_fStream.close();
	}
	//ʹ�����´����ķ�ʽ���ļ�
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
//��֤���ļ�����������
int CFlowFile::LoadFlowFile(int nSeriesNo)
{
	try
	{
		m_cSeriesNo = nSeriesNo+'0';
		string fileName = "data_";
		fileName += m_cSeriesNo;
		//�ӻ�Աǰ���յ��Ľ������� 
		//string sTradeDate;//��ʱ��û���յ���������
		OpenFlowFile(fileName.c_str());
		if (m_fStream.fail())
		{
			CRLog(E_ERROR,"Stream file [%s]read failed��",fileName.c_str());
			return -1;
		}
		//��ʼ��
		m_sFileDate = "-";
		m_ullLastSeqNo = 0;
		m_ullStartSeqNo = 0;
		m_mapIndex.clear();

		char szTradeDate[9] = {0};
		m_fStream.read(szTradeDate,sizeof(szTradeDate)-1);
		szTradeDate[8] = '\0';
		if (m_fStream.gcount() == 0)
		{
			//��ȡ����Ϊ0����ʾ�ļ�Ϊ�գ�
			//OpenFlowFile(fileName);
			m_fStream.clear();
			m_fStream.seekg(0,ios_base::beg);
			m_sFileDate = "-";
			return 0;
		}else if (m_fStream.gcount() != 8)
		{
			//���ļ���ȡ���ڳ���
			CRLog(E_ERROR,"Stream file [%s]read the date wrong��",fileName.c_str());
			return -2;
		}
		m_sFileDate = szTradeDate;
		//�������ļ�����ռ�
		char szBuf[MAX_BUFFLEN] = {0};
		string sRecord;
		unsigned int numPacket = 0;
		fstream::pos_type pos = 0;
		while (1)
		{	

			pos = m_fStream.tellg();
			//�����һ����¼
			int nReadRtn = ReadRecordFromFilePos(sRecord,pos);
			if (m_fStream.eof())
			{
				//Load����
				m_fStream.clear();
				//����load�˶��ٱ���
				return numPacket;
			}
			if ( nReadRtn == -1)
			{
				//�����ļ��ж�ȡ��¼ʧ��
				return -3;
			}else if (nReadRtn == -2)
			{
				//CRC��鷢�ִ���
				return -4;
			}
			//��¼�������к�
			string sSqlNo = sRecord.substr(LENGTH_SIZE,SEQNO_SIZE);
			UINT64  ullSqlNo = FromString<UINT64>(sSqlNo);
			if (m_ullLastSeqNo +1 != ullSqlNo && m_ullLastSeqNo != 0)
			{
				//���к�û�е���
				return -5;
			}
			m_ullLastSeqNo = ullSqlNo;
			if (numPacket == 0)
			{
				//��¼��һ��������
				m_ullStartSeqNo = m_ullLastSeqNo;
			}
			//��������
			m_mapIndex[m_ullLastSeqNo] = pos;
			//��ȡһ����Ϣ�ɹ�
			numPacket++;
		}
		return 0;
	}
	catch (...)
	{
		
	}

	return 0;
}
//�Ѷ�Ӧ����д�����ļ�
int CFlowFile::WriteToFlowFile(const char * sPacket,int pktLen,UINT64 ullSqlNo)
{
	if (m_ullLastSeqNo +1 != ullSqlNo && m_ullLastSeqNo != 0)
	{
		return -1;
	}
	if (!m_fStream.is_open())
	{
		//�ļ�δ��
		return -2;
	}
	//дָ�붨λ���ļ���ĩ
	m_fStream.seekp(0,ios_base::end);
	std::string sRecord;
	unsigned int len = 0;
	//Ԥ������λ��
	sRecord.append(LENGTH_SIZE,0x00);
	len += LENGTH_SIZE;
	//������
	string sSqlNo = ToString<UINT64>(ullSqlNo);
	sSqlNo = StrAddZero(sSqlNo);
	sRecord.append(sSqlNo.c_str(),SEQNO_SIZE);
	len += SEQNO_SIZE;
	//д�뱨��
	sRecord.append(sPacket,pktLen);
	len += pktLen;
	//д����
	len += sizeof(unsigned int);
	char * pLen;
	pLen = (char *)&len;
	sRecord[0] = *pLen;
	pLen++;
	sRecord[1] = *pLen;
	//sRecord.replace(0,2,pLen);
	//����У��
	unsigned int uiCrc32 = CCRC32::crc32_loader((unsigned char *)sRecord.data(),sRecord.length());
	sRecord.append((char*)(&uiCrc32),sizeof(unsigned int));

	//д���ļ�
	m_fStream.write(sRecord.c_str(),len);
	m_fStream.flush();
	len = sRecord.length();
	m_ullLastSeqNo = ullSqlNo;
	return len;
}
//�����ƶ����кţ���ȡ���ļ��ж�Ӧ���Ĳ������
int CFlowFile::ReadFromFlowFile(UINT64 ullSqlNo,int enumType)
{
	map<UINT64 ,fstream::pos_type>::iterator itPos;
	itPos = m_mapIndex.find(ullSqlNo);
	if (itPos == m_mapIndex.end())
	{
		//û�л��������
		return -1;
	}
	if (!m_fStream.is_open())
	{
		//�ļ�δ��
		return -2;
	}
	string sRecord;
	while(itPos != m_mapIndex.end())
	{
		//����������ö�ָ��
		fstream::pos_type pRead = itPos->second;
		//���ö�ָ��
		//m_fStream.seekg(pRead,ios_base::beg);
		//�����һ����¼
		int nReadRtn = ReadRecordFromFilePos(sRecord,pRead);

		if ( nReadRtn == -1)
		{
			//�����ļ��ж�ȡ��¼ʧ��
			return -3;
		}else if (nReadRtn == -2)
		{
			//CRC��鷢�ִ���
			return -4;
		}
		//���ݶ�ȡ�ļ�¼��ñ���
		CGtpPacket pkt(sRecord.substr(LENGTH_SIZE+SEQNO_SIZE,sRecord.length()-LENGTH_SIZE-SEQNO_SIZE-sizeof(unsigned int)));
		//����������ʷ����
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
		//���ļ�Ϊ��
		m_sFileDate = date;
		//����������д�����ļ�
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
		//�ļ�δ��
		return -3;
	}
	int numPacket = 0;
	sRecord = "";
	unsigned short int  len = 0;
	unsigned int uiCrc32Len = sizeof(unsigned int);
	char szBuf[MAX_BUFFLEN] = {0};
	m_fStream.seekg(pos,ios_base::beg);
	//�� ����
	char sLen[2]={0,0};
	m_fStream.read(sLen,LENGTH_SIZE);
	char * p = (char *)& len;
	*p = sLen[0];
	p++;
	*p = sLen[1];
	if (len < sizeof(unsigned int)+LENGTH_SIZE+SEQNO_SIZE)
	{
		//��ȡ���ļ�����
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
			//��ȡ���ļ�����
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
			//��ȡ���ļ�����
			return -1;
		}
		sRecord.append(szBuf,readLen);
	}
	//CRC���
	unsigned int uiCrc32Val = *((unsigned int *)(sRecord.c_str()+len-uiCrc32Len));
	unsigned int uiCrc32Cal = CCRC32::crc32_loader((unsigned char*)sRecord.c_str(),len-uiCrc32Len);
	if (uiCrc32Val != uiCrc32Cal)
	{
		//CRC��鷢�ִ���
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
// 			//����ֵ��λ��ʼ�ҵ�һ����Ϊ0��ֵ
// 			break;
// 		}
// 	}
// 	if (i == size)
// 	{
// 		//�����ַ����ɡ�0�����
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
// 				//����Ҫ��λ���˳�ѭ��
// 				break;
// 			}
// 		}
// 		if (i == -1)
// 		{
// 			//˵�����λ����һ����λ��
// 			result = "1";
// 			result = result + s1;
// 		}else
// 		{
// 			result = s1;
// 		}
// 	}
// 	return result;
// }