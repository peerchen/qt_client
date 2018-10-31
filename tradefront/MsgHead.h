// MsgHead.h: interface for the CMsgHead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGHEAD_H__C023DB8B_F5EB_4200_A616_E4D4FD0B95FC__INCLUDED_)
#define AFX_MSGHEAD_H__C023DB8B_F5EB_4200_A616_E4D4FD0B95FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "public.h"
#include "BpcHead.h"
#include "BF_Mutex.h"
#include "MdbBase.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	//�ֽڶ���
#ifdef _WINDOWS
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
	//#pragma pack(push,1)
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif


#define  ROOTID_LENGTH     10    //ROOTID�ĳ���

//������ҪӦ�����Ϣͷ��Ϣ��SGEӦ���������ݴ�ͷӦ�������
typedef struct 
{
	char          sRootId[ROOTID_LENGTH+1];//��̨������Ψһ��ţ����ݴ���Ų���
	unsigned  int nTimeStamp;//����ʱ��
	S_BPC_HEAD    sBpcHead;        //  nBpuIndex���������߹�����������������0���� 1����  nIndex��ʾ�������������� nConnectTimeΪʱ���
	DREB_HEAD     sDBHead;         //drebͷ
}__PACKED__ S_MSG_HEAD_STRU; 

//ȡ���ֽڶ���
#ifdef _WINDOWS
#pragma pack(pop)
#else
#ifdef __GNUC__
//#pragma pack(pop)
#else
#pragma options align=reset
#endif
#endif
#undef __PACKED__

#ifdef __cplusplus
}
#endif



class CMsgHead  
{
public:

	// ������: Update
	// ���  : ������ 2016-3-24 15:43:21
	// ����  : void 
	// ����  : ���£�ɾ�����ڵı���ͷ����ֹ����Խ��Խ��
	void Update();

	// ������: GetHead
	// ���  : ������ 2016-3-24 15:40:49
	// ����  : bool 
	// ����  : const char *rootid   ����ͷ��ʶ
	// ����  : BPCCOMMSTRU &data    ����ͷ
	// ����  : bool isdel=true      �Ƿ�ɾ���˱���ͷ   ���к���Ӧ��ʱ����ɾ��
	// ����  : ȡ��ԭ����ͷ
	bool GetHead(const char *rootid,BPCCOMMSTRU &data,bool isdel=true);

	// ������: Insert
	// ���  : ������ 2016-3-24 15:40:02
	// ����  : bool 
	// ����  : const char *rootid
	// ����  : BPCCOMMSTRU data
	// ����  : ������ͷ���뻺�����Ӧ��ʱʹ��
	bool Insert(const char *rootid,BPCCOMMSTRU data);
	CMsgHead();
	virtual ~CMsgHead();


protected:
	CBF_Mutex  m_mutex;

	CMemTable <S_MSG_HEAD_STRU> m_table;        //�ڴ��
	CPkeyCharF<ROOTID_LENGTH,1>             m_key;          //rootid����

};

#endif // !defined(AFX_MSGHEAD_H__C023DB8B_F5EB_4200_A616_E4D4FD0B95FC__INCLUDED_)
