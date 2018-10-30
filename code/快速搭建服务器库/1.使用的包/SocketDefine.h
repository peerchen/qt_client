#ifndef NDK_SOCKET_DEFINE_DLL_H
#define NDK_SOCKET_DEFINE_DLL_H

#include <iostream>
using namespace std;

// 定义客户对象结构
typedef struct tagNDK_Socket
{
    unsigned int    sSocket;            // 套接字
    unsigned long   ulIp;               // IP地址,整数型表示(用于做为限制条件,比如限定一个IP指能登录一个客户端)
    unsigned long   ulPort;             // 端口
    unsigned long   ulLoginTime;        // 连接到服务器的时间
    unsigned long   ulOperator;         // 操作类型(1为登录;2为退出;3为发送数据包,服务器接收)
    unsigned char   ucIp[32];           // 十进制点段表示IP地址
}NDK_SOCKET, *LPNDK_SOCKET;

// 回调处理数据函数原型
typedef int __stdcall ProcRecvData(char * pData,
                                   unsigned long DataLength,
                                   long* lpParent,
                                   NDK_SOCKET* pClient);

// 套接字类型枚举
typedef enum tagNDK_Socket_Type
{
    SOCKET_TYPE_IO_OVERLAP_SERVER   = 1,    // 完成端口服务端
    SOCKET_TYPE_IO_SELECT_CLIENT    = 2,    // IO选择模式客户端
    SOCKET_TYPE_IO_SELECT_SERVER    = 3     // IO选择模式服务端
}NDK_SOCKET_TYPE;

// 网络事件操作
typedef enum tagNDK_Operator_Type
{
	SOCKET_OPERATOR_CONNECT			= 1,
	SOCKET_OPERATOR_CLOSE			= 2,
	SOCKET_OPERATOR_RECEIVE			= 3
}NDK_OPERTATOR_TYPE;

typedef enum tagNDK_Return_Value
{
    NDK_SUCC                        =   0,
    NDK_PARAM_INVALID               =   -1,
    NDK_INIT_FAILED                 =   -2,
    NDK_SOCKET_NONENTITY            =   -3,
    NDK_SOCKET_ERROR                =   -4,
    NDK_DISCONNECT_FAILED           =   -5,
    NDK_INIT_BIND_FAILED            =   -6,
    NDK_INIT_LISTEN_FAILED          =   -7,
	NDK_LOGIN_FAILED				=	-8
} NDK_RETURN_VALUE;

#endif // NDK_SOCKET_DEFINE_DLL_H