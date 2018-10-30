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


#pragma once

#include "ylstypedptrmap.h"
#include "tool.h"


//���Զ��ͷ��ڴ����ݽṹ
struct AutoFreeIndexData
{
	char* m_pData;	//����ָ��
	long  m_lSize;	//���ݳ���

	AutoFreeIndexData()
	{
		m_pData = NULL;
		m_lSize = 0;
	}
	~AutoFreeIndexData()
	{
		Free();
	}
	//����
	void Alloc( int nCurSize  )
	{		
		if( nCurSize <= 0 )
		{
			Free();
			return;
		}		
		if( m_lSize != nCurSize )
		{
			Free();
			m_pData = new char[nCurSize];
			m_lSize = nCurSize;
		}
		memset( m_pData,0,m_lSize);
	}
	//�ͷ�
	void Free()
	{
		if ( m_pData != NULL )
		{
			delete[] m_pData;
			m_pData = NULL;
			m_lSize = 0;
		}
	}
	//�ж���Ч��
	BOOL IsValid() { return (m_pData != NULL && m_lSize > 0); }
};


// �����ļ���¼
struct InfoIndex
{
	char m_cType;    // Bit0�����ܱ�־ (0:������,1:����)
				  // Bit1-Bit6������
				  // Bit7����Ч��¼��־λ(0:��Ч��¼��1:��Ч��¼)
				  // 0x00	��ͨ��Ϣ����
				  // 0x01	������Ϣ����
	              // 0x80	��Ч��¼
	char m_cGroup;   // Bit0-Bit3Ϊ��һ���ࣨ��֧��16�����ͣ�
				  //����4BitΪ��Ѷ���̱������xx����Ϣ��
				  // Bit0-3ֵ	��Ϣ����
	              // 0x00	    ����������
				  // 0x01	    �ƾ�����
				  // 0x02	    ������ʷ��Ѷ (��˾���¼�)
				  // 0x03	    ����ʵʱ��Ѷ
				  // 0x04	    F10����
				  // 0x05-0x0e	����
				  // 0x0f	    ����	
	char m_cMarket;  // Bit0-Bit7Ϊ�г����ࣨ��֧��8���г�����
				  // �ͱ���Ϣ��ص��г�Bit��Ϊ1��
	              // ����Ϣ�������κ��г�ʱ��Bit0-Bit7ȫΪ0��
				  // 0	�Ϻ�
				  // 1	����
				  // 2	��ҵ
				  // 3	���
				  // 4	̨��
				  // 5	����
				  // 6	����
				  // 7	����
	long m_lDate;	    // ��*10000+��*100+��
	long m_lTime;      // ʱ*10000+��*100+��
	char m_cTitle[64]; // �ַ���������0x00��β
					// ������ʷ��Ѷ	��ظ�����ʷ��Ѷ���ݵı��⡣�������63���ֽڣ�������0x00��β��
					// ����ʵʱ��Ѷ	��ظ���ʵʱ��Ѷ���ݵı��⡣�������63���ֽڣ�������0x00��β��
					// ����F10����	��ΪF10����ҳ�ϵķ������ƣ����֧��4�����֡�
					// ��Ѷ���̵���ɫ��Ѷ	�����ɫ��Ѷ���ݵı��⡣�������63���ֽڣ�������0x00��β��

	union
	{
		char m_CYlsFilePath[80]; // Դ�ļ�·�� // 130
		char m_cFilePath[80];    // Դ�ļ�·�� // 130
	};

	long m_lOffset;		  // ƫ��λ��
	long m_lLength;	      // ��Ϣ����
	char m_cCode[4][9];   // ��ش���
						  // ���֧��4����ظ��ɴ��롣ÿ����ظ��ɴ���ռ9�ֽڣ����е�1�ֽ��Ǹø��������г�����(�����������)������8���ֽ�������д��ظ��ɴ��룬������0x00��

	//char m_cReserved[55]; // ���� // 5
	union
	{
		char FilePK[12];	  // ������ţ������������Ψһ������֤������(�׸��������)
		char m_cReserved[55]; // ���� // 5
	};

	char m_cSubType;	  // ��Ϣ�ӷ��� 0-8
	                      // 0 	��ʾ
						  // 1	˵��
						  // 2	��˾��̬
						  // 3	��������
						  // 4	�ֺ����
						  // 5	ҵ������
						  // 6 	�й�����
						  // 7	��˾��������

						  // 100 �ļ�
						  // 101 �ļ�����

	char m_cChksum;		  // У��

	//��ȡ����,���ļ���ȡ
	char*		     ReadData(AutoFreeIndexData* pRefData);
	//����·��
	void             GetPath(char* strFileName);


	CString GetFilePK()
	{
		CString str = CString(FilePK,sizeof(FilePK));
		str.Trim();
		return str;
	}

	BOOL IsEqualPK(InfoIndex* pIndex)
	{
		return ( (pIndex->m_lDate == m_lDate) && !GetFilePK().CompareNoCase(pIndex->GetFilePK()) );
	}

	CString GetTitle()
	{
		CString str = CString(m_cTitle,sizeof(m_cTitle));
		str.Trim();
		return str;
	}

	BOOL IsEqual(InfoIndex* pIndex)
	{
		return (pIndex && !GetTitle().CompareNoCase(pIndex->GetTitle()));
	}
};

struct AttachData
{
	unsigned long m_nSize;
	char		  m_cData[1];
};

class ZiXunRunTime
{
public:
	ZiXunRunTime();
	ZiXunRunTime(const char* szIndexFileName,const char* szIndexPath,const char* szDataPath);
	~ZiXunRunTime();

	char m_szDataPath[_MAX_PATH];	// ��������·��
	char m_szRelativelyDataPath[_MAX_PATH];	// �������·��

	char m_szIndexFileName[_MAX_PATH]; // �����ļ�

	char m_szFlag[16];

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> m_ay; // ��ǰ�仯��ʱʱ��Ѷ����

	int m_nPreDataPos;

	int  ReadIndex();
	BOOL MakeData(CHqDataBuffer* pBuffer,InfoIndex* pInfoIndex,const char* szIndexFileName,int nPosition);
	void Empty();

	int  Write(InfoIndex* pInfo,char* pGroup,int nGroupLen,char* pText,int nLen);
	int	 Write(ReqInfoSend* pReqInfoSend);

	static CYlsTypedPtrMap<CYlsMapStringToPtr,const char*,ZiXunRunTime*> m_mapInfo;

	static void Refresh(int nMask);
	static void EmptyAll(int nMask);

	static void Init(CString strList);

	static void InitFromRead();

	static void AddDataTo(CString strList,
						  InfoIndex* pInfo,char* pGroup,int nGroupLen,char* pText,int nLen);
	static void AddDataTo(ReqInfoSend* pReqInfoSend);

	int	WriteIndex(InfoUpdateIndex* pInfoUpdateIndex);
	static void UpdateIndex(InfoUpdateIndex* pInfoUpdateIndex);

	int WriteOneIndex(InfoUpdateOneIndex* pInfoUpdateOneIndex,AskData* pAsk);
	static int UpdateOneIndex(InfoUpdateOneIndex* pInfoUpdateOneIndex,AskData* pAsk);
	int PushOneIndex(InfoIndex* pInfoIndex,const char* szIndexFileName,int nPosition);

};

// added 2000825
// �����ļ���¼
struct InfoIndex_Ex
{
	char m_cType;    // Bit0�����ܱ�־ (0:������,1:����)
	// Bit1-Bit6������
	// Bit7����Ч��¼��־λ(0:��Ч��¼��1:��Ч��¼)
	// 0x00	��ͨ��Ϣ����
	// 0x01	������Ϣ����
	// 0x80	��Ч��¼
	char m_cGroup;   // Bit0-Bit3Ϊ��һ���ࣨ��֧��16�����ͣ�
	//����4BitΪ��Ѷ���̱������xx����Ϣ��
	// Bit0-3ֵ	��Ϣ����
	// 0x00	    ����������
	// 0x01	    �ƾ�����
	// 0x02	    ������ʷ��Ѷ (��˾���¼�)
	// 0x03	    ����ʵʱ��Ѷ
	// 0x04	    F10����
	// 0x05-0x0e	����
	// 0x0f	    ����	
	char m_cMarket;  // Bit0-Bit7Ϊ�г����ࣨ��֧��8���г�����
	// �ͱ���Ϣ��ص��г�Bit��Ϊ1��
	// ����Ϣ�������κ��г�ʱ��Bit0-Bit7ȫΪ0��
	// 0	�Ϻ�
	// 1	����
	// 2	��ҵ
	// 3	���
	// 4	̨��
	// 5	����
	// 6	����
	// 7	����
	long m_lDate;	    // ��*10000+��*100+��
	long m_lTime;      // ʱ*10000+��*100+��
	char m_cTitle[64]; // �ַ���������0x00��β
	// ������ʷ��Ѷ	��ظ�����ʷ��Ѷ���ݵı��⡣�������63���ֽڣ�������0x00��β��
	// ����ʵʱ��Ѷ	��ظ���ʵʱ��Ѷ���ݵı��⡣�������63���ֽڣ�������0x00��β��
	// ����F10����	��ΪF10����ҳ�ϵķ������ƣ����֧��4�����֡�
	// ��Ѷ���̵���ɫ��Ѷ	�����ɫ��Ѷ���ݵı��⡣�������63���ֽڣ�������0x00��β��

	union
	{
		char m_CYlsFilePath[80]; // Դ�ļ�·�� // 130
		char m_cFilePath[80];    // Դ�ļ�·�� // 130
	};

	long m_lOffset;		  // ƫ��λ��
	long m_lLength;	      // ��Ϣ����
	char m_cCode[4][9];   // ��ش���
	// ���֧��4����ظ��ɴ��롣ÿ����ظ��ɴ���ռ9�ֽڣ����е�1�ֽ��Ǹø��������г�����(�����������)������8���ֽ�������д��ظ��ɴ��룬������0x00��

	//char m_cReserved[55]; // ���� // 5
	union
	{
		char FilePK[12];	  // ������ţ������������Ψһ������֤������(�׸��������)
		char m_cReserved[55]; // ���� // 5
	};

	char m_cSubType;	  // ��Ϣ�ӷ��� 0-8
	// 0 	��ʾ
	// 1	˵��
	// 2	��˾��̬
	// 3	��������
	// 4	�ֺ����
	// 5	ҵ������
	// 6 	�й�����
	// 7	��˾��������

	// 100 �ļ�
	// 101 �ļ�����

	char m_cChksum;		  // У��

	//��ȡ����,���ļ���ȡ
	char*		     ReadData(AutoFreeIndexData* pRefData);

	//���ļ���ȡָ����¼������  add 20110824
	char*            ReadContent(CHqDataBuffer* pBuffer);
	//����·��
	void             GetPath(char* strFileName);


	CString GetFilePK()
	{
		CString str = CString(FilePK,sizeof(FilePK));
		str.Trim();
		return str;
	}

	BOOL IsEqualPK(InfoIndex_Ex* pIndex)
	{
		return ( (pIndex->m_lDate == m_lDate) && !GetFilePK().CompareNoCase(pIndex->GetFilePK()) );
	}

	CString GetTitle()
	{
		CString str = CString(m_cTitle,sizeof(m_cTitle));
		str.Trim();
		return str;
	}

	BOOL IsEqual(InfoIndex_Ex* pIndex)
	{
		return (pIndex && !GetTitle().CompareNoCase(pIndex->GetTitle()));
	}
};


class ZiXunRunTime_Ex
{
public:
	ZiXunRunTime_Ex();
	ZiXunRunTime_Ex(const char* szIndexFileName,const char* szIndexPath,const char* szDataPath);
	~ZiXunRunTime_Ex();

	char m_szDataPath[_MAX_PATH];	// ��������·��
	char m_szRelativelyDataPath[_MAX_PATH];	// �������·��

	char m_szIndexFileName[_MAX_PATH]; // �����ļ�

	char m_szFlag[16];

	CYlsArray<CHqDataBuffer*,CHqDataBuffer*> m_ay; // ��ǰ�仯��ʱʱ��Ѷ����

	CYlsArray<InfoIndex_Ex*, InfoIndex_Ex*> m_ayIdx; // ���浱ǰ��Ѷ����
	CYlsArray<CHqDataBuffer*, CHqDataBuffer*> m_ayContent; // ���浱ǰ��Ѷ����

	int m_nPreDataPos;

	int  ReadIndex();
	BOOL MakeData(CHqDataBuffer* pBuffer,InfoIndex_Ex* pInfoIndex);
	void Empty();

	int  Write(InfoIndex_Ex* pInfo,char* pGroup,int nGroupLen,char* pText,int nLen);
	InfoIndex_Ex*  FindIndex(char* pszTitle);

	static CYlsTypedPtrMap<CYlsMapStringToPtr,const char*,ZiXunRunTime_Ex*> m_mapInfoEx;

	static void Refresh(int nMask);
	static void EmptyAll(int nMask);

	static void Init(CString strList);
	static void AddDataTo(CString strList,
		InfoIndex_Ex* pInfo,char* pGroup,int nGroupLen,char* pText,int nLen);
	static void AddDataTo(ReqInfoSend* pReqInfoSend);
	static bool MakeIndexListData(char* pszType, CHqDataBuffer* pBuffer);
	static bool MakeContentData(char* pszType, char* pszTitle, CHqDataBuffer* pBuffer);
};
// end add

extern int AnalyzeStr(CString strResource,const char* strDelimit,CStringArray& ayRet);

