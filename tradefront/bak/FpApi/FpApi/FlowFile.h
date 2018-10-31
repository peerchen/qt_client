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

	//������ļ�
	int ClearFlowFile();
	//��֤���ļ�����������
	int LoadFlowFile(int nSeriesNo);
	//�ر����ļ�
	void CloseFlowFile();
	//�Ѷ�Ӧ����д�����ļ�,����-1����ʾseqNo�����ļ���������Ŵ�Ϊ�쳣���󣻷���0����ʾseqNo�����ļ����������С��Ϊ��ʷ���ģ���д���ļ���
	//����>0�����֣���ʾд�����ļ��ĳ���
	//����seqNoΪ���к�(���10λ)
	int WriteToFlowFile(const char * sPacket,int pktLen,UINT64 seqNo);
	//����ָ�����к�ȡ�����ļ���������ȡ���ļ��ж�Ӧ���Ĳ������
	int ReadFromFlowFile(UINT64 seqNo,int enumType);
	//�ж����ļ����������Ƿ���ȷ����д�����ļ�ǰ��Ҫ���жϸ��
	int EqualDate(string date);
	//��api�ڵ�
	int bind(CApi * api);
	UINT64 GetLastSequenceNo(void){return m_ullLastSeqNo;}
	UINT64 GetStartSequenceNo(void){return m_ullStartSeqNo;}
private:
	//���ƶ�λ�ö�ȡһ����¼
	int ReadRecordFromFilePos(string &sRecord,fstream::pos_type pos);
	//�����ļ�
	int OpenFlowFile(const char * fileName);
// 	//����s1��ֵ+1�Ľ��
// 	string StrAddOne(string s1);
// 	//ȥ��strǰ��ġ�0��
// 	string StrDelZero(string s1);
 	//��strǰ����䡮0�� ��10λ
 	string StrAddZero(string s1);
private:
	//���ļ�ָ��
	fstream m_fStream;
	//�ļ���ַ����
	std::map < UINT64,fstream::pos_type > m_mapIndex;
	//���ļ��ڼ�¼�Ľ�������
	string m_sFileDate;
	//��ʼ���к�
	UINT64 m_ullStartSeqNo;
	//�������к�
	UINT64 m_ullLastSeqNo;

	CApi * m_api;
	char m_cSeriesNo;
};
#endif