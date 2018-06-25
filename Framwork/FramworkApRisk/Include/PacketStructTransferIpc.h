#ifndef _PACKET_STRUCT_TRANSFER_IPC_H
#define _PACKET_STRUCT_TRANSFER_IPC_H

#include "IpcPacket.h"
#include "PacketBodyStructIpc.h"

namespace ipc
{
	class CPacketStructIpc
	{
	public:

		//----------------------------------------------���Ľӿ� [StateInfo] ���Ľṹ��ؽ���
		// ���Ľ��������� -> �ṹ    StateInfo
		static int Packet2Struct(StateInfo& stBody, CIpcPacket& pkt)
		{
			pkt.GetParameterVal("node_id"           , stBody.node_id);
			// 		pkt.GetParameterVal("node_peer_id"      , stBody.node_peer_id);
			pkt.GetParameterVal("ms_flag"           , stBody.ms_flag);
			// 		pkt.GetParameterVal("ind_login"         , stBody.ind_login);
			// 		pkt.GetParameterVal("login_state"       , stBody.login_state);
			pkt.GetParameterVal("token"             , stBody.token);
			pkt.GetParameterVal("tm_token"          , stBody.tm_token);
			pkt.GetParameterVal("magic_number"      , stBody.magic_number);
			// 		pkt.GetParameterVal("pkt_flag"			, stBody.pkt_flag);
			return 0;
		}


		// ���Ľ����� �ṹ -> ����    StateInfo
		static int Struct2Packet(StateInfo& stBody, CIpcPacket& pkt)
		{
			pkt.AddParameter("node_id"           , stBody.node_id);
			// 		pkt.AddParameter("node_peer_id"      , stBody.node_peer_id);
			pkt.AddParameter("ms_flag"           , stBody.ms_flag);
			// 		pkt.AddParameter("ind_login"         , stBody.ind_login);		
			// 		pkt.AddParameter("login_state"       , stBody.login_state);
			pkt.AddParameter("token"             , stBody.token);
			pkt.AddParameter("tm_token"          , stBody.tm_token);
			pkt.AddParameter("magic_number"      , stBody.magic_number);
			// 		pkt.AddParameter("pkt_flag"			, stBody.pkt_flag);
			return 0;
		}

	};
}
#endif
