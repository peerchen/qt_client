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
	NVLIST m_nvList;//名称值列表
public:
	
	// 函数名: GetBuffer
	// 编程  : 王明松 2007-9-19 13:25:30
	// 返回  : int   >0 数据长度 -1失败 
	// 参数  : char *buf
	// 参数  : char mark 分隔符
	// 描述  : 根据设置的名称值生成数据包 如果返回码为空返回false
	int GetBuffer(char *buf,char mark);
	int GetBuffer(string &buf, char mark);

	// 函数名: SetValueName
	// 编程  : 王明松 2007-9-19 13:24:49
	// 返回  : int 
	// 参数  : string name
	// 参数  : string value
	// 描述  : 设置名称值，新增加返回大于0，否则返回0
	int SetValueName(string name,string value);
	int SetValueName(string name,int value);
	int SetValueName(string name,long value);
	int SetValueName(string name,double value);

	// 函数名: NewPackage
	// 编程  : 王明松 2007-9-19 13:24:37
	// 返回  : void 
	// 描述  : 生成一个新的包
	void NewPackage();

	// 函数名: GetValueByName
	// 编程  : 王明松 2007-9-19 13:24:15
	// 返回  : string 
	// 参数  : string name
	// 描述  : 根据名称取值，不存在返回""
	string GetValueByName(string name);

	// 函数名: GetValueByName
	// 编程  : 王明松 2007-9-19 13:24:01
	// 返回  : bool 
	// 参数  : string name
	// 参数  : string& value
	// 描述  : 根据名称取值
	bool GetValueByName(string name ,string &value);
	bool GetValueByName(string name ,int &value);
	bool GetValueByName(string name ,long &value);
	bool GetValueByName(string name ,double &value);

	// 函数名: GetValueByName
	// 编程  : 王明松 2007-9-19 13:23:49
	// 返回  : bool 
	// 参数  : const char *name
	// 参数  : char *value
	// 描述  : 根据名称取值
	bool GetValueByName(const char *name,char *value);


	// 函数名: FillString
	// 编程  : 王明松 2007-9-19 13:04:36
	// 返回  : bool 
	// 参数  : char *buf  以0结束
	// 参数  : int mark 分隔符asc
	// 描述  : 把分隔符装添到本类中，然后可以用getvaluebyname取值
	bool FillString(char *buf,int mark);
	bool FillString(char *buf,char mark);

protected:
	char m_dataBuf[MAXAPIBUFLEN];
	char m_itemData[MAXITEMDATALEN];
	char m_itemData2[MAXITEMDATALEN];

	
};

#endif // !defined(AFX_NAMEVALUE_H__7066D913_B567_4683_ABE4_EA64C5293829__INCLUDED_)
