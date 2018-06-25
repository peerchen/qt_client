#ifndef _PACKET_BODY_STRUCT_IPC_H
#define _PACKET_BODY_STRUCT_IPC_H

#include <string>
#include "ArrayListMsg.h"
#include "HashtableMsg.h"

namespace ipc
{
	//----------------------------------------------���Ľӿ� [StateInfo] ����

	// �ṹ����:StateInfo
	typedef struct tagStateInfo
	{
		string       node_id              ; //Դ�ڵ��
// 		string       node_peer_id         ; //�Զ˽ڵ�� �����Ϊ��
		string		 ms_flag			  ; //���ӱ�־
		// 	string       ind_login            ; //��¼ָʾ
		// 	string       login_state          ; //��¼״̬
		string       token				  ; //��¼����
		string       tm_token			  ; //������Ƶ�ʱ���
		string		 magic_number		  ; //�����
// 		string		 pkt_flag			  ; //��������/Ӧ���־
	}StateInfo,*PStateInfo;

}

#endif
