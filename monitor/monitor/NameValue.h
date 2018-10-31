// NameValue.h: interface for the CNameValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NAMEVALUE_H__7066D913_B567_4683_ABE4_EA64C5293829__INCLUDED_)
#define AFX_NAMEVALUE_H__7066D913_B567_4683_ABE4_EA64C5293829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "public.h"


#define  MAXAPIBUFLEN  64*1024
#define  MAXITEMDATALEN  8*1024

typedef struct _NAMEVALUE
{
	string name;
	string value;
};
typedef std::vector<_NAMEVALUE> NVLIST;
class DLL_EXPORT CNameValue  
{
public:
	CNameValue();
	virtual ~CNameValue();
	NVLIST m_nvList;//����ֵ�б�
public:
	
	// ������: GetBuffer
	// ���  : ������ 2007-9-19 13:25:30
	// ����  : int   >0 ���ݳ��� -1ʧ�� 
	// ����  : char *buf
	// ����  : char mark �ָ���
	// ����  : �������õ�����ֵ�������ݰ� ���������Ϊ�շ���false
	int GetBuffer(char *buf,char mark);
	int GetBuffer(string &buf, char mark);

	// ������: SetValueName
	// ���  : ������ 2007-9-19 13:24:49
	// ����  : int 
	// ����  : string name
	// ����  : string value
	// ����  : ��������ֵ�������ӷ��ش���0�����򷵻�0
	int SetValueName(string name,string value);
	int SetValueName(string name,int value);
	int SetValueName(string name,long value);
	int SetValueName(string name,double value);

	// ������: NewPackage
	// ���  : ������ 2007-9-19 13:24:37
	// ����  : void 
	// ����  : ����һ���µİ�
	void NewPackage();

	// ������: GetValueByName
	// ���  : ������ 2007-9-19 13:24:15
	// ����  : string 
	// ����  : string name
	// ����  : ��������ȡֵ�������ڷ���""
	string GetValueByName(string name);

	// ������: GetValueByName
	// ���  : ������ 2007-9-19 13:24:01
	// ����  : bool 
	// ����  : string name
	// ����  : string& value
	// ����  : ��������ȡֵ
	bool GetValueByName(string name ,string &value);
	bool GetValueByName(string name ,int &value);
	bool GetValueByName(string name ,long &value);
	bool GetValueByName(string name ,double &value);

	// ������: GetValueByName
	// ���  : ������ 2007-9-19 13:23:49
	// ����  : bool 
	// ����  : const char *name
	// ����  : char *value
	// ����  : ��������ȡֵ
	bool GetValueByName(const char *name,char *value);


	// ������: FillString
	// ���  : ������ 2007-9-19 13:04:36
	// ����  : bool 
	// ����  : char *buf  ��0����
	// ����  : int mark �ָ���asc
	// ����  : �ѷָ���װ�������У�Ȼ�������getvaluebynameȡֵ
	bool FillString(char *buf,int mark);
	bool FillString(char *buf,char mark);

protected:
	char m_dataBuf[MAXAPIBUFLEN];
	char m_itemData[MAXITEMDATALEN];
	char m_itemData2[MAXITEMDATALEN];

	
};

#endif // !defined(AFX_NAMEVALUE_H__7066D913_B567_4683_ABE4_EA64C5293829__INCLUDED_)
