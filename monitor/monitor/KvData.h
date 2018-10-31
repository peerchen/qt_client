// KvData.h: interface for the CKvData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KVDATA_H__3A8993D3_2C8A_40EC_8B0C_27D1396CF119__INCLUDED_)
#define AFX_KVDATA_H__3A8993D3_2C8A_40EC_8B0C_27D1396CF119__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "public.h"
#include "MoniHead.h"
#include "KVNode.h"




#ifdef WIN32
#ifdef _DEBUG
#pragma comment(lib, "bf_kerneld.lib") 
#pragma message("Automatically linking with  bf_kerneld.lib ")
#else
#pragma comment(lib, "bf_kernel.lib") 
#pragma message("Automatically linking with  bf_kernel.lib ")
#endif
#endif





class CKvData  
{
public:
	// ������: SetNodeNameValue
	// ���  : ������ 2013-12-26 16:39:23
	// ����  : bool 
	// ����  : std::string name =�ָ�������
	// ����  : std::string svalue =�����ֵ
	// ����  : ���ýڵ����ƺ�ֵ
	bool SetNodeNameValue(std::string name,int value);

	// ������: SetNodeNameValue
	// ���  : ������ 2013-12-26 16:39:23
	// ����  : bool 
	// ����  : std::string name =�ָ�������
	// ����  : std::string svalue =�����ֵ
	// ����  : ���ýڵ����ƺ�ֵ
	bool SetNodeNameValue(std::string name,double value);

	// ������: SetNodeNameValue
	// ���  : ������ 2013-12-26 16:39:23
	// ����  : bool 
	// ����  : std::string name =�ָ�������
	// ����  : std::string svalue =�����ֵ
	// ����  : ���ýڵ����ƺ�ֵ
	bool SetNodeNameValue(std::string name,std::string svalue);

	// ������: SetNodeByName
	// ���  : ������ 2013-12-11 17:57:36
	// ����  : CKVNode *  2��Ľڵ�
	// ����  : std::string name   =�ָ�������
	// ����  : int nodetype       =�����ֵ�����ͣ��й�ϣ�����б���
	// ����  : ���ýڵ������ڵ����ͣ������ɸ��ݷ��صĽڵ��������ֵ�Ȳ���
	CKVNode * SetNodeByName(std::string name,int nodetype);

	// ������: GetValueByNameOne
	// ���  : ������ 2013-12-11 15:14:28
	// ����  : bool 
	// ����  : std::string name  
	// ����  : std::string &svalue
	// ����  : int &col   ��
	// ����  : int &line  ��
	// ����  : ��������ȡֵ��ͳһ��|�ָ�
	bool GetValueByNameOne(std::string name,std::string &svalue,int &col, int &line);


	// ������: GetValueByName
	// ���  : ������ 2013-12-11 14:24:00
	// ����  : CKVNode* 2��Ľڵ� NULLû�ҵ�
	// ����  : std::string name =�ָ�������
	// ����  : std::string &svalue    =�ָ���ֵ
	// ����  : ��������ȡֵ =�ָ���ֵ
	CKVNode* GetValueByName(std::string name,std::string &svalue);


	// ������: GetNodeByName
	// ���  : ������ 2013-12-13 9:02:43
	// ����  : CKVNode*   2��Ľڵ� NULLû�ҵ�
	// ����  : std::string name  =�ָ�������
	// ����  : �������ƻ�ȡ�ڵ�
	CKVNode* GetNodeByName(std::string name);


	// ������: ToString
	// ���  : ������ 2013-12-11 13:56:43
	// ����  : bool 
	// ����  : std::string &data
	// ����  : ��kv�����ַ������������̶�ͷ
	bool ToString(std::string &data);


	// ������: ParseNode
	// ���  : ������ 2013-12-11 11:24:31
	// ����  : bool 
	// ����  : std::string data
	// ����  : �����ڵ㣬��ȥ�̶�����ͷ�Ľ���
	bool ParseNode(std::string data);

	// ������: ParseHead
	// ���  : ������ 2013-12-10 20:53:19
	// ����  : bool 
	// ����  : std::string data
	// ����  : ��������ͷ
	bool ParseHead(std::string data);

	// ������: FromBuffer
	// ���  : ������ 2013-12-10 20:32:07
	// ����  : bool 
	// ����  : string data
	// ����  : ����ֵ
	bool FromBuffer(std::string data);


	//��װ

	// ������: fromBuffer
	// ���  : ������ 2013-12-13 9:12:52
	// ����  : bool 
	// ����  : char *buf
	// ����  : ��kv��������ת����kv���Ķ���
	bool fromBuffer(char *buf); 
	
	// ������: toBuffer
	// ���  : ������ 2013-12-13 9:13:10
	// ����  : bool 
	// ����  : char *buf
	// ����  : unsigned int size  buf�Ĵ�С
	// ����  : ��kv���Ķ���ת����kv��������
	bool toBuffer(char *buf, unsigned int size);
	
	/* ����kv���Ķ���ı���ͷ��ֵ*/
	int setHead(std::string key, std::string svalue);
	
	// ������: setPack
	// ���  : ������ 2013-12-13 9:13:31
	// ����  : int 
	// ����  : std::string key
	// ����  : std::string value   ��ͨ��ֵ���޷ָ�
	// ����  : bool flag= true
	// ����  : ����kv���Ķ��������ֵ,flagΪtrueʱ���»�����key Ϊflaseʱֱ������key
	int setPack(std::string key, std::string svalue, bool flag= true);
	
	// ������: setPackX
	// ���  : ������ 2013-12-12 20:39:13
	// ����  : int 
	// ����  : std::string key    ����
	// ����  : std::string value  "��"�߷ָ��ĵ�ֵ
	// ����  : int row= 0         ��  value���¼�ж����� (���ǹ�ϣ����������һ�У���ȥ����ͷ)
	// ����  : int col= 0         ��  ÿ����¼�������
	// ����  : bool flag= true
	// ����  : ����kv���Ķ��������ֵ
	int setPackX(std::string key, std::string svalue, int line= 0, int col= 0, bool flag= true);
	
	// ������: getHead
	// ���  : ������ 2013-12-13 9:14:49
	// ����  : bool 
	// ����  : std::string key   ��������ͷ�������  serial_no��
	// ����  : std::string &value  ֵ
	// ����  : ��ȡ��������ͷ������ƶ�Ӧ��ֵ
	bool getHead(std::string key, std::string &svalue);
	

	// ������: getPack
	// ���  : ������ 2013-12-13 9:16:19
	// ����  : bool 
	// ����  : std::string key   =�ָ�������
	// ����  : std::string &value  ֵ
	// ����  : int row= 0    ��Ӧ����
	// ����  : int col= 0    ��Ӧ����
	// ����  : ��ȡָ���к��е�ֵ�����������ڵĲ���kvtype_datalist��Ϊ�˲��ֵ����Ϊ��ϣ�����б�ʱȡ��Ӧ�����ݼ�¼���к��е�ֵ 
	bool getPack(std::string key, std::string &svalue, int row= 0, int col= 0);
	
	// ������: getPackH
	// ���  : ������ 2013-12-13 9:19:11
	// ����  : bool 
	// ����  : std::string key  =�ָ�������
	// ����  : std::string &value  ֵ
	// ����  : int row= 0    ��Ӧ����
	// ����  : int col= 0    ��Ӧ����
	// ����  : ��ȡָ���к��е�ֵ�����������ڵĲ���kvtype_datalist��Ϊ�˲��ֵ����Ϊ��ϣ��ʱȡ������ͷ��Ӧ�к��е�ֵ����Ϊ�б�ʱΪ���ݼ�¼���к��е�ֵ 
	bool getPackH(std::string key, std::string &svalue, int row= 0, int col= 0);
	
	// ������: getPackX
	// ���  : ������ 2013-12-13 9:22:27
	// ����  : bool 
	// ����  : std::string key   =�ָ�������
	// ����  : std::string &value  ��ͨ����"��"�ָ�,��ϣ�����б�ʱֵ��"��"�ָ�
	// ����  : int &row       ���ص���
	// ����  : int &col       ���ص���
	// ����  : ȡָ�����Ƶ�ֵ
	bool getPackX(std::string key, std::string &svalue, int &row, int &col);
				
	
	// ������: clear
	// ���  : ������ 2013-12-13 9:24:45
	// ����  : void 
	// ����  : ��ն��ұ���ͷ�ṹ����ɾ�����нڵ�
	void clear();

	CKvData();
	virtual ~CKvData();
	
	char    m_sErrMsg[256];

	CKVNode     m_pDataNode;
protected:
	
	bool        m_bIsRequestPack; //�Ƿ��������ݰ�
	S_KV_HEAD   m_kvHead;

private:
	CBF_SimpleLog  m_pLog;
	// ������: stringConvertX2K
	// ���  : ������ 2013-12-13 9:25:20
	// ����  : int 
	// ����  : CKVNode *namenode    =�ָ��Ĳ�  2��
	// ����  : std::string &value   "��"�ָ��ı�������
	// ����  : int line              ���������ж�����(��ϣ��ʱ��������ͷ����)
	// ����  : int col              ���������ж�����
	// ����  : ��"��"�ָ��ı�������һ�������ӵ�namenode(=�ָ��Ĳ�)��������
	int stringConvertX2K(CKVNode *namenode,std::string &svalue, int line, int col);

};

#endif // !defined(AFX_KVDATA_H__3A8993D3_2C8A_40EC_8B0C_27D1396CF119__INCLUDED_)