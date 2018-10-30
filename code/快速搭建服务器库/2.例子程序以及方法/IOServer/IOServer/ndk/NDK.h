#ifndef NDK_DLL_H
#define NDK_DLL_H

#ifdef NDK_EXPORTS
#define NDK_API __declspec(dllexport)
#else
#define NDK_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
// SOCKETͨѶ
#include "SocketDefine.h"

// This class is exported from the NDK.dll
extern "C" class NDK_API CNDKSocket 
{
public:
    CNDKSocket(void){};
    virtual ~CNDKSocket(){};
    
    // ��ʼ��,����uiType�����׽���(��������ͻ�)
    virtual int Initial(
        ProcRecvData* pRecvData, 
        long* lpParent,
        unsigned long ulPort,
        const char* pucIp = NULL) = 0;
    
    // �ر�
    virtual void Release() = 0;
    
    // ���ر���Ip��ַ������ֵΪ���ʮ���Ƶ��ַ���
    virtual const char* GetLocalIpAddr() = 0;
    // ���ط���ʹ�õ������˿ںŻ�ͻ��׽����Զ�ʹ�õĶ˿�
    virtual unsigned short GetLocalPort() = 0;
    
    // ��������(���ڿͻ����׽���)
    virtual int Send(unsigned long ulLength, char* pucData) = 0;
    
    // �жϿͻ����Ƿ�����
    virtual bool IsConnected(unsigned int sSocket = 0) = 0;
    
    //////////////////////////////////////////////////////////////////////////
    // ���·����������׽�������Ϊ������(SOCKET_TYPE_IO_OVERLAP_SERVER��SOCKET_TYPE_IO_SELECT_SERVER)
    // ��ָ����SOCKET��������
    virtual int Send(unsigned int sSocket, unsigned long ulLength, char* pucData) = 0;
    // ��ָ����IP��������,ʮ���Ƶ����
    virtual int Send(const char* pucIp, unsigned long ulLength, char* pucData) = 0;
    
    // ���������߿ͻ��˷�������
    virtual int SendMsgToAll(char* pData, unsigned long ulLen) = 0;
    
    // ������Ϣ�����������û�����ָ���ͻ�����
    virtual int SendMsgToOther(const char* strExceptIp, char* pData,unsigned long ulLen) = 0;
    virtual int SendMsgToOther(unsigned int sExcept, char * pData, unsigned long ulLen) = 0;
    
    // �ж�ָ���ͻ��˵�����
    virtual int DisConnectClient(const char* strClientIp) = 0;
    virtual int DisConnectClient(unsigned int sClient) = 0;
    // �ж����пͻ��˵����ӡ�
    virtual void DisConnectAll() = 0;
    //////////////////////////////////////////////////////////////////////////
    
    // �ͷ��ڴ�,���ڷ��ص�ָ�����(ֻ����new��������)
    virtual void FreeMemory(char* pPtr) = 0;
};

// ��ȡ�׽�����ָ��
extern "C" NDK_API CNDKSocket* GetNDKSocketPtr(NDK_SOCKET_TYPE uiType = SOCKET_TYPE_IO_SELECT_CLIENT);
// ɾ���׽���
extern "C" NDK_API void  DeleteNDKSocket(CNDKSocket* pSocket);


#endif // NDK_DLL_H