#ifndef NDK_DLL_H
#define NDK_DLL_H

#ifdef NDK_EXPORTS
#define NDK_API __declspec(dllexport)
#else
#define NDK_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
// SOCKET通讯
#include "SocketDefine.h"

// This class is exported from the NDK.dll
extern "C" class NDK_API CNDKSocket 
{
public:
    CNDKSocket(void){};
    virtual ~CNDKSocket(){};
    
    // 初始化,根据uiType创建套接字(服务器或客户)
    virtual int Initial(
        ProcRecvData* pRecvData, 
        long* lpParent,
        unsigned long ulPort,
        const char* pucIp = NULL) = 0;
    
    // 关闭
    virtual void Release() = 0;
    
    // 返回本地Ip地址，返回值为点分十进制的字符串
    virtual const char* GetLocalIpAddr() = 0;
    // 返回服务使用的侦听端口号或客户套接字自动使用的端口
    virtual unsigned short GetLocalPort() = 0;
    
    // 发送数据(用于客户端套接字)
    virtual int Send(unsigned long ulLength, char* pucData) = 0;
    
    // 判断客户端是否连接
    virtual bool IsConnected(unsigned int sSocket = 0) = 0;
    
    //////////////////////////////////////////////////////////////////////////
    // 以下方法仅用于套接字类型为服务器(SOCKET_TYPE_IO_OVERLAP_SERVER和SOCKET_TYPE_IO_SELECT_SERVER)
    // 向指定的SOCKET发送数据
    virtual int Send(unsigned int sSocket, unsigned long ulLength, char* pucData) = 0;
    // 向指定的IP发送数据,十进制点段型
    virtual int Send(const char* pucIp, unsigned long ulLength, char* pucData) = 0;
    
    // 向所有连线客户端发送数据
    virtual int SendMsgToAll(char* pData, unsigned long ulLen) = 0;
    
    // 发送消息给所有在线用户，除指定客户端外
    virtual int SendMsgToOther(const char* strExceptIp, char* pData,unsigned long ulLen) = 0;
    virtual int SendMsgToOther(unsigned int sExcept, char * pData, unsigned long ulLen) = 0;
    
    // 切断指定客户端的连接
    virtual int DisConnectClient(const char* strClientIp) = 0;
    virtual int DisConnectClient(unsigned int sClient) = 0;
    // 切断所有客户端的连接。
    virtual void DisConnectAll() = 0;
    //////////////////////////////////////////////////////////////////////////
    
    // 释放内存,用于返回的指针对象(只能是new出的数组)
    virtual void FreeMemory(char* pPtr) = 0;
};

// 获取套接字类指针
extern "C" NDK_API CNDKSocket* GetNDKSocketPtr(NDK_SOCKET_TYPE uiType = SOCKET_TYPE_IO_SELECT_CLIENT);
// 删除套接字
extern "C" NDK_API void  DeleteNDKSocket(CNDKSocket* pSocket);


#endif // NDK_DLL_H