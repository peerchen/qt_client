/*******************************************************************************
 * Copyright (c)2003, Ѷ��������޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ�dayfile.h
 * �ļ���ʶ���̺����ݴ���
 * ժ    Ҫ���̺����ݴ���
 *
 * ��ǰ�汾��2.0
 * ��    �ߣ�
 * ������ڣ�
 *
 * ȡ���汾��
 * ԭ �� �ߣ�
 * ������ڣ�
 * ��	 ע��
 *******************************************************************************/

#ifndef INC_DAYFILE_H
#define INC_DAYFILE_H

//#include "..\comm\struct3.h"
#include "fileobj.h"


/////////////////////////////////////////////////////////////////////////////
//�����ļ������
class CDataFile : public CSupperFileObj
{
public:
	CDataFile();
	CDataFile(LPCTSTR lpszFileName, UINT nOpenFlags);
	//���ļ�
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags, short nPeriod = 0);
public:
	//���麯��
	virtual short HandleData(void* pData, long& lSize, CTime& cBegin, CTime& cEnd) = 0;
							//lSize < 0 : Delete Data
							//lSize = 0 : Exam   Data
							//lSize > 0 : Read	 Data
	//���麯��
	virtual long  TimeToLong(CTime ctm) = 0;
	//�����г���Ϣ
	void SetStockCodeInfo(HSMarketDataType cCodeType, CBourseInfo* pBourse);
	//ת��ʱ��	
	static CTime  LongToTime(long lDate);
protected:
	/*��ʽ�����ڵ�:�ļ�����|���� 
	�ļ����ͣ�SDF_DAYFILE�� SDF_VOLUMEFILE,SDF_VOLUMEFILE
	����:SDF_MINUTE,...SDF_YEAR
	*/
	short			  m_nPeriod;
	//����
	HSMarketDataType  m_cCodeType;
	//�г���Ϣָ��
	CBourseInfo* m_pBourse;
};
/////////////////////////////////////////////////////////////////////////////
//5���ӡ�15���ӡ�30���ӡ�60���ӡ�120���ӡ����ߡ����ߡ����ߡ����������ļ�
//���ߡ����ߡ����ߡ����߳ɽ�����ϸ�����ļ�
//���ߡ����ߡ����ߡ�������ʷ�ɽ���ϸ�����ļ�
#define SDF_DAYFILE		0x0000		//K �������ļ�
#define SDF_TRACEFILE	0x1000		//�ɽ�����ϸ�����ļ�
#define SDF_VOLUMEFILE	0x2000		//��ʷ�ɽ���ϸ�����ļ�

#define SDF_MINUTE		0x0100		//�����ߣ��Ͱ�λ���������������������ı�����
#define SDF_PERIOD_TYPE_DAY			0x0200		//����
#define SDF_WEEK		0x0300		//����
#define SDF_MONTH		0x0400		//����
#define SDF_YEAR		0x0500		//����

#define SDF_IGNORE		0		//���ԣ�������
#define SDF_OVERLAY		1		//����
#define SDF_UPDATE		2		//���£��ۼӳɽ���
#define SDF_INSERT		3		//������K��

class CBourseInfo;
class CStockDayFile : public CDataFile
{
public:
	CStockDayFile();
	//�������ڣ����û��๹��
	CStockDayFile(LPCTSTR lpszFileName, UINT nOpenFlags, short nPeriod);

	virtual short HandleData(void* pData, long& lSize, CTime& cBegin, CTime& cEnd);
	/********************************************************************************
	 * �������� : ��������,����long��ʱ��	
	 * �������� : CTime ctm - ʱ��	
	 *  ����ֵ  : long, �������ΪSDF_MINUTE, ����(YYYY - 1990)MMDDHHmm, ����13041809
	 *					���򷵻�YYYYMMDD,����20030418
	 * �������� :	
	 * ��    �� :
	 * ������� :
	 * �޸ļ�¼ :
	 *******************************************************************************/
	virtual long  TimeToLong(CTime ctm);
	/********************************************************************************
	 * �������� : �����ļ������ݵĸ���(��¼����)	
	 * �������� : void	
	 *  ����ֵ  : ��¼���� ʧ�ܷ���0	
	 * �������� :	
	 * ��    �� :
	 * ������� :
	 * �޸ļ�¼ :
	 *******************************************************************************/
	long  GetDaySize();
	/********************************************************************************
	* �������� : �����ļ�����ȡ�����ݵ�λ�Ľṹ���ȣ�һ����¼�ĳ��ȣ�
	* �������� : void	
	*  ����ֵ  : long һ����¼�ĳ��� 
	* �������� : �˺���ǰ���Ǳ����ļ������Ѿ�ָ��	Ĭ�ϴ���Ϊ�����ļ�
	* ��    �� :
	* ������� :
	* �޸ļ�¼ :
	*******************************************************************************/
	long  GetRecordSize();
	/********************************************************************************
	 * �������� : ��ȡ���ݼ�¼	
	 * �������� : void* pData - ��¼����ָ�� �ⲿ�ڴ���������㹻��,����������
	 *			  long lSize - ����ȡ��¼��Ŀ
	 *			  long lFrom - FILE_CURRENT����ʱ��,
					���ΪFILE_CURRENT,�����ļ���ǰλ�ö�
					���Ϊʱ��,�����ٲ��Ҹ�ʱ������ݼ�¼λ��
	 *  ����ֵ  : �ɹ���ȡ�ļ�¼����	ʧ�ܷ���0
	 * �������� :	
	 * ��    �� :
	 * ������� :
	 * �޸ļ�¼ :
	 *******************************************************************************/
	long  ReadData(void* pData, long lSize, long lFrom = FILE_CURRENT);
	//�����ļ�����
	short GetDayFileType() { return (m_nPeriod & 0xF000); }
	/********************************************************************************
	 * �������� :	�����ļ�����,����д���� ���Ƚ�ʱ��,����:����,����,���²���
	 * �������� :	void* pData - ��д����ָ��
	 *				long lSize -  ���ݼ�¼����
	 *				short nPeriod - ָ������, ��ط����ļ�����֧�ֵ�����,����ʧ��
	 *
	 *				FileNowData* pNowData - �ļ���ʵʱ����
	 *				short nMessageMask -	������Ϣ����
	 *				short nVolAmount -	�ɽ�����
	 *				long lOpenVolumn -	���̳ɽ���
	 *				long lZeroVol -�Ե��ɽ���
	 *
	 *				StockHistoryData* pHisData -  ��������
	 *				short nSize - ���ݸ��� 
	 *				long nHand - ����
	 *				StockTick* pTraceData - �ֱ�����
	 *  ����ֵ  :	�ɹ�����TRUE ʧ�ܷ���FALSE
	 * �������� :	
	 * ��    �� :
	 * ������� :
	 * �޸ļ�¼ :
	 *******************************************************************************/
	BOOL  WriteData(void* pData, long lSize, short nPeriod);
	BOOL  WriteData(FileNowData* pNowData, short nMessageMask = 0, short nVolAmount = 0, long lOpenVolumn = 0, long lZeroVol = 0);
	BOOL  WriteData(StockHistoryData* pHisData, short nSize, long nHand = 100);
	BOOL  WriteData(StockTick* pTraceData, short nSize, long nHand = 100);
	//�����ļ����ݼ�¼ �Է������ļ���Ч
	void  Upgrade();
	//�����ļ����ݼ�¼ �Է������ļ���Ч	StockDay* pData - ���� long lSize -��¼����
	void  Upgrade(StockDay* pData, long lSize);
	//�Ƿ���Ҫ���� ����ʱ���ʽ�Ƿ�Ϸ�
	BOOL  IsNeedUpgrade();

protected:
	//ʵʱ��������, �����ļ����Ͳ�ͬ
	void  UpdateData(void* pOld, void* pNew);
	//�����ļ���ʱ���¼
	long  FindDate(long lDate);
	//�����ڴ���ʱ���¼ ���ز���,����,���²�������,
	short FindDate(char* pData, long lSize, long lDate, short nPeriod, long& lIndex);
	//�Ƚ�ʱ�� �������� ����ֵ��0--��Ȼ�ͬһK��    >0����>��   <0����<�� lDate1:ԭ����	lDate2:������
	int   CompDate(long lDate1, short nPeriod1, long lDate2, short nPeriod2, short& nResult);
	//���ݲ�ͬ�ļ�����, д��ͬ�ļ�����	
	BOOL  WriteDayData(StockTick* pTraceData, short nSize, long nHand = 100);
	BOOL  WriteVolumeData(StockTick* pTraceData, short nSize, long nHand = 100);
	BOOL  WriteTraceData(StockTick* pTraceData, short nSize, long nHand = 100);

public:
	//����ָ������, ����֧�ִ����ڵ��ļ�����; nPeriod - ��Чֵ:&0xFF00
	short CommPeriodToData(short nPeriod);

};

/////////////////////////////////////////////////////////////////////////////
//��ʷ��ʱ�����ļ�	δʹ��
class CStockTrendFile : public CDataFile
{
public:
	CStockTrendFile();
	CStockTrendFile(LPCTSTR lpszFileName, UINT nOpenFlags);
	
	virtual short HandleData(void* pData, long& lSize, CTime& cBegin, CTime& cEnd);
	virtual long  TimeToLong(CTime ctm);

	BOOL  WriteData(StockHistoryTrend* pData);
	BOOL  WriteData(StockHistoryData* pHisData, StockHistoryTrendHead* pHead);

protected:
	short FindDate(long& lDate, long& lPos, short& nSize);
};

/////////////////////////////////////////////////////////////////////////////
//Ӳ�̻��������ļ�
#define DC_LASTTIME			0x0001
#define DC_FILENAME			0x0002
#define DC_CODEINFO			0x0004
#define DC_DATATYPE			0x0008
#define DC_BEGINTIME		0x0010
#define DC_ENDTIME			0x0020

#define DC_NOT_CREATE_ZIP		0x0001
#define DC_NOT_CREATE_UNZIP		0x0002
//δʹ��
class CDiskCacheIndexFile;
class CDiskCacheIndex
{
public:
	CDiskCacheIndex();
	CDiskCacheIndex(unsigned short nDataType, long lBegin, long lEnd, CodeInfo* pciInfo);
	CDiskCacheIndex(const CDiskCacheIndex& value);

	int Compare(const CDiskCacheIndex&  dataSrc) const;       
	const CDiskCacheIndex& operator=(const CDiskCacheIndex& dataSrc);
	
	CString GetFileName(BOOL &bZip);
	void    SetFileName(const char* pszName, int nMode = 0);
	void    SetLastTime(long lLastTime = -1);
protected:
	unsigned short	m_nDataType;
	long			m_lBeginTime;	//CTime
	long			m_lEndTime;		//CTime
	CodeInfo		m_ciInfo;
	long			m_lLastTime;	//CTime
	char			m_szFileName[16];		//only file name;

	friend class CDiskCacheIndexFile;
};
//δʹ��
// Compare helpers
//operator '=='
inline BOOL AFXAPI operator==(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) == 0; }
//operator '!='
inline BOOL AFXAPI operator!=(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) != 0; }
//operator '<'
inline BOOL AFXAPI operator<(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) < 0; }
//operator '>'
inline BOOL AFXAPI operator>(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) > 0; }
//operator '<='
inline BOOL AFXAPI operator<=(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) <= 0; }
//operator '>='
inline BOOL AFXAPI operator>=(const CDiskCacheIndex& data1, const CDiskCacheIndex& data2)
       {  return data1.Compare(data2) >= 0; }
//δʹ��
/////////////////////////////////////////////////////////////////////////////
class CDiskCacheIndexFile : public CSupperFileObj
{
public:
	CDiskCacheIndexFile();
	CDiskCacheIndexFile(LPCTSTR lpszFileName, UINT nOpenFlags);
	
	BOOL FindCacheIndex(CDiskCacheIndex* pkey, long& lIndex, CString& strFileName, BOOL& bZip);

	BOOL InsertCacheIndex(CDiskCacheIndex* pInsert, long lIndex);
	BOOL UpdateCacheIndex(CDiskCacheIndex* pUpdate, long lIndex, short nMode = (short)0x0FFFF);
	int  DeleteCacheIndex(const char* pszPath, const char* pszCacheName, int nHoldDay = 30);
};

#endif