#ifndef NDK_SOCKET_DEFINE_DLL_H
#define NDK_SOCKET_DEFINE_DLL_H

#include <iostream>
using namespace std;

// ����ͻ�����ṹ
typedef struct tagNDK_Socket
{
    unsigned int    sSocket;            // �׽���
    unsigned long   ulIp;               // IP��ַ,�����ͱ�ʾ(������Ϊ��������,�����޶�һ��IPָ�ܵ�¼һ���ͻ���)
    unsigned long   ulPort;             // �˿�
    unsigned long   ulLoginTime;        // ���ӵ���������ʱ��
    unsigned long   ulOperator;         // ��������(1Ϊ��¼;2Ϊ�˳�;3Ϊ�������ݰ�,����������)
    unsigned char   ucIp[32];           // ʮ���Ƶ�α�ʾIP��ַ
}NDK_SOCKET, *LPNDK_SOCKET;

// �ص��������ݺ���ԭ��
typedef int __stdcall ProcRecvData(char * pData,
                                   unsigned long DataLength,
                                   long* lpParent,
                                   NDK_SOCKET* pClient);

// �׽�������ö��
typedef enum tagNDK_Socket_Type
{
    SOCKET_TYPE_IO_OVERLAP_SERVER   = 1,    // ��ɶ˿ڷ����
    SOCKET_TYPE_IO_SELECT_CLIENT    = 2,    // IOѡ��ģʽ�ͻ���
    SOCKET_TYPE_IO_SELECT_SERVER    = 3     // IOѡ��ģʽ�����
}NDK_SOCKET_TYPE;

// �����¼�����
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