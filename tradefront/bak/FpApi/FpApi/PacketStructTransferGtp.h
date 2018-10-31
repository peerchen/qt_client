#ifndef _PACKET_STRUCT_TRANSFER_GTP_H
#define _PACKET_STRUCT_TRANSFER_GTP_H
#include "ApiStruct.h"
#include "GtpPacket.h"
#include "GtpMsgArray.h"
class CPacketStructGtp
{
public:
	//消息报文头
	//请求报文编码: 结构 -> 报文  
	//----------------------------------------------请求报文结构编解码
	// 结构 -> 报文 
	static int Struct2PacketReq( TReqMsg& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("X11"          ,stBody.root_id      );  
		pkt.AddParameter("G20"          ,stBody.teller_id    ); 
		pkt.AddParameter("U11"        ,stBody.branch_id    );
		pkt.AddParameter("M00"        ,stBody.member_id    );
		pkt.AddParameter("X22"			,stBody.unit_id      );
		return 0;
	}
	//报文 -> 结构 
	static int Packet2StructReq( TReqMsg& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("X11"         ,stBody.root_id   ,sizeof(stBody.root_id)  );  
		pkt.GetParameterVal("G20"         ,stBody.teller_id   ,sizeof(stBody.teller_id) ); 
		pkt.GetParameterVal("U11"        ,stBody.branch_id    ,sizeof(stBody.branch_id));
		pkt.GetParameterVal("M00"        ,stBody.member_id    ,sizeof(stBody.member_id));
		pkt.GetParameterVal("X22"			,stBody.unit_id     ,sizeof(stBody.unit_id) );
		//pkt.GetParameterVal("MsgType"			,stBody.msg_type      );
		return 0;
	}
	//----------------------------------------------响应码报文结构编解码
	// 结构 -> 报文 
	static int Struct2PacketRsp( TRspMsg& stBody, CGtpPacket& pkt)
	{
		//rootID放置在消息报文头里面
		pkt.AddParameter("X11"          ,stBody.root_id      );  
		pkt.AddParameter("G20"         ,stBody.teller_id    ); 
		pkt.AddParameter("U11"        ,stBody.branch_id    );
		pkt.AddParameter("M00"        ,stBody.member_id    );
		pkt.AddParameter("X22"			,stBody.unit_id      );
		pkt.AddParameter("X40"         ,stBody.rsp_msg     );  
		pkt.AddParameter("X39"        ,stBody.rsp_code    );
		return 0;
	}
	//报文 -> 结构 
	static int Packet2StructRsp( TRspMsg* stBody, CGtpPacket& pkt)
	{
		if (!stBody)
		{
			return -1;
		}
		pkt.GetParameterVal("X11"         ,stBody->root_id     ,sizeof(stBody->root_id));  
		pkt.GetParameterVal("G20"         ,stBody->teller_id    ,sizeof(stBody->teller_id) ); //user_id
		pkt.GetParameterVal("U11"        ,stBody->branch_id     ,sizeof(stBody->branch_id));
		pkt.GetParameterVal("M00"        ,stBody->member_id     ,sizeof(stBody->member_id));
		pkt.GetParameterVal("X22"			,stBody->unit_id      ,sizeof(stBody->unit_id) );
		//pkt.GetParameterVal("MsgType"			,stBody->msg_type      );
		pkt.GetParameterVal("X40"         ,stBody->rsp_msg      ,sizeof(stBody->rsp_msg));  
		pkt.GetParameterVal("X39"        ,stBody->rsp_code    ,sizeof(stBody->rsp_code) ); 
		return 0;
	}
	//报文 -> 结构 
	static int Packet2StructRsp( TRspMsg& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("X11"         ,stBody.root_id   ,sizeof(stBody.root_id)  );  
		pkt.GetParameterVal("G20"         ,stBody.teller_id   ,sizeof(stBody.teller_id)  ); //user_id
		pkt.GetParameterVal("U11"        ,stBody.branch_id    ,sizeof(stBody.branch_id) );
		pkt.GetParameterVal("M00"        ,stBody.member_id    ,sizeof(stBody.member_id) );
		pkt.GetParameterVal("X22"			,stBody.unit_id      ,sizeof(stBody.unit_id) );
		//pkt.GetParameterVal("MsgType"			,stBody.msg_type      );
		pkt.GetParameterVal("X40"         ,stBody.rsp_msg      ,sizeof(stBody.rsp_msg));  
		pkt.GetParameterVal("X39"        ,stBody.rsp_code    ,sizeof(stBody.rsp_code) ); 
		return 0;
	}
	//----------------------------------------------报文接口 [6101] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqLogin& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("M62"              ,stBody.unit_password  );    
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspLogin& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("T13"          ,stBody.exch_date ,sizeof(stBody.exch_date));
		return 0;
	}


	//----------------------------------------------报文接口 [6102] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqLogout& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspLogout& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		return 0;
	}

	//----------------------------------------------报文接口 [6105] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTellerLogin& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("M62"         ,stBody.password     );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTellerLogin& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("T13"          ,stBody.exch_date ,sizeof(stBody.exch_date));
		return 0;
	}
	//----------------------------------------------报文接口 [6106] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTellerLogout& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTellerLogout& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		return 0;
	}
	//----------------------------------------------报文接口 [6202] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqPreOpenAccountLegal& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		pkt.AddParameter("X62"                ,stBody.gess_branch_id              );
		pkt.AddParameter("A03"                     ,stBody.acct_type                   );
		pkt.AddParameter("M37"                 ,stBody.gess_grade_id               );
		pkt.AddParameter("W40"                ,stBody.settle_bank_no              );
		pkt.AddParameter("A10"                    ,stBody.account_no                  );
		pkt.AddParameter("A11"                  ,stBody.account_name                );
		pkt.AddParameter("A12"             ,stBody.open_account_date           );
		pkt.AddParameter("A13"              ,stBody.account_due_date            );
		pkt.AddParameter("M34"                  ,stBody.corp_en_name                );
		pkt.AddParameter("M32"                 ,stBody.corp_chn_name               );
		pkt.AddParameter("M35"                  ,stBody.corp_en_abbr                );
		pkt.AddParameter("M33"                 ,stBody.corp_chn_abbr               );
		pkt.AddParameter("B24"                  ,stBody.corp_prop_id                );
		pkt.AddParameter("B45"                     ,stBody.corp_code                   );
		pkt.AddParameter("B22"                     ,stBody.cert_type                   );
		pkt.AddParameter("B23"                      ,stBody.cert_num                    );
		pkt.AddParameter("B30"                     ,stBody.contacter                   );
		pkt.AddParameter("B15"                  ,stBody.mobile_phone                );
		pkt.AddParameter("B81"                   ,stBody.regist_addr                 );
		pkt.AddParameter("B34"                   ,stBody.reg_capital                 );
		pkt.AddParameter("R09"                      ,stBody.org_type                    );
		pkt.AddParameter("B29"                      ,stBody.corp_zip                    );
		pkt.AddParameter("B26"                      ,stBody.corp_tel                    );
		pkt.AddParameter("B27"                      ,stBody.corp_fax                    );
		pkt.AddParameter("B28"                    ,stBody.corp_email                  );
		pkt.AddParameter("K49"                   ,stBody.pawnee_flag                 );
		pkt.AddParameter("B25"              ,stBody.corp_regist_addr            );
		pkt.AddParameter("B35"               ,stBody.copr_authorizer             );
		pkt.AddParameter("B08"              ,stBody.auth_nationality            );
		pkt.AddParameter("B01"             ,stBody.auth_cert_type_id           );
		pkt.AddParameter("B02"                  ,stBody.auth_cert_no                );
		pkt.AddParameter("B03"                     ,stBody.auth_addr                   );
		pkt.AddParameter("B07"                      ,stBody.auth_zip                    );
		pkt.AddParameter("B04"                      ,stBody.auth_tel                    );
		pkt.AddParameter("B05"                      ,stBody.auth_fax                    );
		pkt.AddParameter("B06"                    ,stBody.auth_email                  );
		pkt.AddParameter("B20"                  ,stBody.busi_license                );
		pkt.AddParameter("B32"                      ,stBody.tax_cert                    );
		pkt.AddParameter("B21"                 ,stBody.org_code_cert               );
		pkt.AddParameter("B80"                ,stBody.regist_address              );
		pkt.AddParameter("B41"               ,stBody.sigex_post_code             );
		pkt.AddParameter("B42"                     ,stBody.sigex_tel                   );
		pkt.AddParameter("B43"                     ,stBody.sigex_fax                   );
		pkt.AddParameter("B44"                   ,stBody.sigex_email                 );
		pkt.AddParameter("M30"                       ,stBody.cust_id                     );
		pkt.AddParameter("M38"                ,stBody.gess_broker_id              );
		pkt.AddParameter("M39"                     ,stBody.exec_name                   );
		pkt.AddParameter("M40"                      ,stBody.exec_tel                    );
		pkt.AddParameter("M41"             ,stBody.exec_cert_type_id           );
		pkt.AddParameter("M42"                 ,stBody.exec_cert_num               );
		pkt.AddParameter("B48"           ,stBody.taxpayer_identifier         );
		pkt.AddParameter("B33"        ,stBody.is_val_added_taxplayer      );
		pkt.AddParameter("B36"             ,stBody.taxplayer_address           );
		pkt.AddParameter("B37"            ,stBody.taxpayer_telephone          );
		pkt.AddParameter("B38"             ,stBody.taxpayer_bankcode           );
		pkt.AddParameter("B39"             ,stBody.taxpayer_bankinfo           );
		pkt.AddParameter("B40"           ,stBody.taxpayer_account_id         );
		pkt.AddParameter("B89"                          ,stBody.memo                        );
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspPreOpenAccountLegal& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
		pkt.GetParameterVal("M30"		   ,stBody.cust_id ,sizeof(stBody.cust_id));
		return 0;
	}


	//----------------------------------------------报文接口 [6203] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqOpenAccountPersonal& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		pkt.AddParameter("M30"               ,stBody.cust_id             );
		pkt.AddParameter("A10"            ,stBody.account_no          );
		pkt.AddParameter("A11"          ,stBody.account_name        );
		pkt.AddParameter("A12"     ,stBody.open_account_date   );
		pkt.AddParameter("A13"      ,stBody.account_due_date    );
		pkt.AddParameter("B01"          ,stBody.cert_type_id        );
		pkt.AddParameter("B02"              ,stBody.cert_num            );
		pkt.AddParameter("X62"        ,stBody.gess_branch_id      );
		pkt.AddParameter("M38"        ,stBody.gess_broker_id      );
		pkt.AddParameter("M37"         ,stBody.gess_grade_id       );
		pkt.AddParameter("B15"          ,stBody.mobile_phone        );
		pkt.AddParameter("B04"                   ,stBody.tel                 );
		pkt.AddParameter("B03"                  ,stBody.addr                );
		pkt.AddParameter("B07"               ,stBody.zipcode             );/////////应为B07，目前前置跟API一致
		pkt.AddParameter("B06"                 ,stBody.email               );////////应为B06
		pkt.AddParameter("W40"        ,stBody.settle_bank_no      );
		pkt.AddParameter("B08"           ,stBody.nationality         );
		pkt.AddParameter("B12"              ,stBody.birthday            );
		pkt.AddParameter("B09"            ,stBody.first_name          );
		pkt.AddParameter("B10"             ,stBody.last_name           );
		pkt.AddParameter("B11"           ,stBody.middle_name         );
		pkt.AddParameter("B13"        ,stBody.cert_open_date      );
		pkt.AddParameter("B14"         ,stBody.cert_due_date       );
		pkt.AddParameter("B89"                  ,stBody.memo                );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspOpenAccountPersonal& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("M30"               ,stBody.cust_id        ,sizeof(stBody.cust_id)     );

		return 0;
	}


	//----------------------------------------------报文接口 [6205] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqModifyBankAcctBind& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		pkt.AddParameter("M30"           ,stBody.cust_id         );
		pkt.AddParameter("A01"         ,stBody.acct_type       );
		pkt.AddParameter("B01"      ,stBody.cert_type_id    );
		pkt.AddParameter("B02"          ,stBody.cert_num        );
		pkt.AddParameter("A10"    ,stBody.new_account_no  );
		pkt.AddParameter("A11"    ,stBody.account_name  );
		pkt.AddParameter("W40"    ,stBody.settle_bank_no  );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspModifyBankAcctBind& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
		return 0;
	}

	//----------------------------------------------报文接口 [6207] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqCancelAccount& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		pkt.AddParameter("M30"               ,stBody.cust_id             );
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspCancelAccount& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
		pkt.GetParameterVal("T13"          ,stBody.exch_date,sizeof(stBody.exch_date));  
		pkt.GetParameterVal("T85"          ,stBody.client_serial_no,sizeof(stBody.client_serial_no));  
		return 0;
	}

	//----------------------------------------------报文接口 [6208] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqModifyAcctInfoPersonal& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("M30"          ,stBody.cust_id           );
		pkt.AddParameter("B08"      ,stBody.nationality       );
		pkt.AddParameter("B12"         ,stBody.birthday          );
		pkt.AddParameter("B09"       ,stBody.first_name        );
		pkt.AddParameter("B10"        ,stBody.last_name         );
		pkt.AddParameter("B11"      ,stBody.middle_name       );
		pkt.AddParameter("B13"   ,stBody.cert_open_date    );
		pkt.AddParameter("B14"    ,stBody.cert_due_date     );
		pkt.AddParameter("B15"     ,stBody.mobile_phone      );
		pkt.AddParameter("B04"              ,stBody.tel               );
		pkt.AddParameter("B03"             ,stBody.addr              );
		pkt.AddParameter("B07"          ,stBody.zipcode           );
		pkt.AddParameter("B06"            ,stBody.email             );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspModifyAcctInfoPersonal& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag); 
		return 0;
	}

	//----------------------------------------------报文接口 [6209] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqModifyAcctInfoLegal& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );        
		pkt.AddParameter("M30"                   ,stBody.cust_id                  );
		pkt.AddParameter("M34"              ,stBody.corp_en_name             );
		pkt.AddParameter("M32"             ,stBody.corp_chn_name            );
		pkt.AddParameter("M35"              ,stBody.corp_en_abbr             );
		pkt.AddParameter("M33"             ,stBody.corp_chn_abbr            );
		pkt.AddParameter("B81"               ,stBody.regist_addr              );
		pkt.AddParameter("B22"                 ,stBody.cert_type                );
		pkt.AddParameter("B23"                  ,stBody.cert_num                 );
		pkt.AddParameter("B24"              ,stBody.corp_prop_id             );
		pkt.AddParameter("B45"                 ,stBody.corp_code                );
		pkt.AddParameter("B30"                 ,stBody.contacter                );
		pkt.AddParameter("B15"              ,stBody.mobile_phone             );
		pkt.AddParameter("B46"                  ,stBody.org_type                 );
		pkt.AddParameter("B34"               ,stBody.reg_capital              );
		pkt.AddParameter("K49"               ,stBody.pawnee_flag              );
		pkt.AddParameter("B25"          ,stBody.corp_regist_addr         );
		pkt.AddParameter("B29"                  ,stBody.corp_zip                 );
		pkt.AddParameter("B26"                  ,stBody.corp_tel                 );
		pkt.AddParameter("B27"                  ,stBody.corp_fax                 );
		pkt.AddParameter("B28"                ,stBody.corp_email               );
		pkt.AddParameter("B35"           ,stBody.copr_authorizer          );
		pkt.AddParameter("B08"          ,stBody.auth_nationality         );
		pkt.AddParameter("B01"         ,stBody.auth_cert_type_id        );
		pkt.AddParameter("B02"              ,stBody.auth_cert_no             );
		pkt.AddParameter("B03"                 ,stBody.auth_addr                );
		pkt.AddParameter("B07"                  ,stBody.auth_zip                 );
		pkt.AddParameter("B04"                  ,stBody.auth_tel                 );
		pkt.AddParameter("B05"                  ,stBody.auth_fax                 );
		pkt.AddParameter("B06"                ,stBody.auth_email               );
		pkt.AddParameter("B20"              ,stBody.busi_license             );
		pkt.AddParameter("B32"                  ,stBody.tax_cert                 );
		pkt.AddParameter("B21"             ,stBody.org_code_cert            );
		pkt.AddParameter("B80"            ,stBody.regist_address           );
		pkt.AddParameter("B41"           ,stBody.sigex_post_code          );
		pkt.AddParameter("B42"                 ,stBody.sigex_tel                );
		pkt.AddParameter("B43"                 ,stBody.sigex_fax                );
		pkt.AddParameter("B44"               ,stBody.sigex_email              );
		pkt.AddParameter("M39"                 ,stBody.exec_name                );
		pkt.AddParameter("M40"                  ,stBody.exec_tel                 );
		pkt.AddParameter("M41"              ,stBody.exec_cert_type_id             );
		pkt.AddParameter("M42"         ,stBody.exec_cert_num        );
		pkt.AddParameter("B48"       ,stBody.taxpayer_identifier      );
		pkt.AddParameter("B33"    ,stBody.is_val_added_taxplayer   );
		pkt.AddParameter("B36"         ,stBody.taxplayer_address        );
		pkt.AddParameter("B37"        ,stBody.taxpayer_telephone       );
		pkt.AddParameter("B38"         ,stBody.taxpayer_bankcode        );
		pkt.AddParameter("B39"         ,stBody.taxpayer_bankinfo        );
		pkt.AddParameter("B40"       ,stBody.taxpayer_account_id      );
		pkt.AddParameter("B89"                      ,stBody.memo                     );
		pkt.AddParameter("A10"        ,stBody.account_no       );
		pkt.AddParameter("A12"         ,stBody.open_account_date        );
		pkt.AddParameter("A13"         ,stBody.account_due_date        );
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspModifyAcctInfoLegal& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag); 
		return 0;
	}

	//----------------------------------------------报文接口 [6210] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqMemberFareModelChange& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		pkt.AddParameter("M30"               ,stBody.cust_id             );
		pkt.AddParameter("M43"    ,stBody.gesas_fare_mode_id  );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspMemberFareModelChange& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag); 
		return 0;
	}

	//----------------------------------------------报文接口 [6211] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryAcctInfoPersonal& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("J10"        ,stBody.query_flag      );  
		pkt.AddParameter("A10"        ,stBody.account_no      );  
		pkt.AddParameter("B01"      ,stBody.cert_type_id    );  
		pkt.AddParameter("B02"          ,stBody.cert_num        );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryAcctInfoPersonal& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("M30"               ,stBody.cust_id      ,sizeof(stBody.cust_id)       );
		pkt.GetParameterVal("W40"        ,stBody.settle_bank_no    ,sizeof(stBody.settle_bank_no)  );
		pkt.GetParameterVal("A10"            ,stBody.account_no     ,sizeof(stBody.account_no)     );
		pkt.GetParameterVal("A11"          ,stBody.account_name     ,sizeof(stBody.account_name)   );
		pkt.GetParameterVal("A12"     ,stBody.open_account_date   ,sizeof(stBody.open_account_date));
		pkt.GetParameterVal("A13"      ,stBody.account_due_date   ,sizeof(stBody.account_due_date) );
		pkt.GetParameterVal("B01"          ,stBody.cert_type_id  );
		pkt.GetParameterVal("B02"              ,stBody.cert_num      ,sizeof(stBody.cert_num)      );
		pkt.GetParameterVal("M44"     ,stBody.gess_fare_mode_id  ,sizeof(stBody.gess_fare_mode_id) );
		pkt.GetParameterVal("M43"    ,stBody.gesas_fare_mode_id  ,sizeof(stBody.gesas_fare_mode_id));
		pkt.GetParameterVal("M38"        ,stBody.gess_broker_id      ,sizeof(stBody.gess_broker_id));
		pkt.GetParameterVal("M37"              ,stBody.grade_id          ,sizeof(stBody.grade_id)  );
		pkt.GetParameterVal("B15"          ,stBody.mobile_phone      ,sizeof(stBody.mobile_phone)  );
		pkt.GetParameterVal("B04"                   ,stBody.tel         ,sizeof(stBody.tel)        );
		pkt.GetParameterVal("B03"                  ,stBody.addr        ,sizeof(stBody.addr)        );
		pkt.GetParameterVal("B07"               ,stBody.zipcode          ,sizeof(stBody.zipcode)   );
		pkt.GetParameterVal("B06"                 ,stBody.email           ,sizeof(stBody.email)    );
		pkt.GetParameterVal("B08"           ,stBody.nationality        ,sizeof(stBody.nationality) );
		pkt.GetParameterVal("B12"              ,stBody.birthday        ,sizeof(stBody.birthday)    );
		pkt.GetParameterVal("B09"            ,stBody.first_name       ,sizeof(stBody.first_name)   );
		pkt.GetParameterVal("B10"             ,stBody.last_name      ,sizeof(stBody.last_name)     );
		pkt.GetParameterVal("B11"           ,stBody.middle_name      ,sizeof(stBody.middle_name)   );
		pkt.GetParameterVal("B13"        ,stBody.cert_open_date    ,sizeof(stBody.cert_open_date)  );
		pkt.GetParameterVal("B14"         ,stBody.cert_due_date     ,sizeof(stBody.cert_due_date)  );
		pkt.GetParameterVal("M36"             ,stBody.acct_stat        ,sizeof(stBody.acct_stat)   );
		pkt.GetParameterVal("B89"                  ,stBody.memo        ,sizeof(stBody.memo)        );
		return 0;
	}

	//----------------------------------------------报文接口 [6212] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryAcctInfoLegal& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("J10"        ,stBody.query_flag      );  
		pkt.AddParameter("A10"        ,stBody.account_no      );  
		pkt.AddParameter("B22"      ,stBody.cert_type_id    );  
		pkt.AddParameter("B23"          ,stBody.cert_num        ); 
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryAcctInfoLegal& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
		pkt.GetParameterVal("M34"           ,stBody.corp_en_name,sizeof(stBody.corp_en_name         )  );
		pkt.GetParameterVal("M32"          ,stBody.corp_chn_name,sizeof(stBody.corp_chn_name        )  );
		pkt.GetParameterVal("M35"           ,stBody.corp_en_abbr,sizeof(stBody.corp_en_abbr         )  );
		pkt.GetParameterVal("M33"          ,stBody.corp_chn_abbr,sizeof(stBody.corp_chn_abbr        )  );
		pkt.GetParameterVal("W40"         ,stBody.settle_bank_no,sizeof(stBody.settle_bank_no        )  );
		pkt.GetParameterVal("A10"             ,stBody.account_no,sizeof(stBody.account_no            )  );
		pkt.GetParameterVal("A11"           ,stBody.account_name,sizeof(stBody.account_name          )  );
		pkt.GetParameterVal("A12"      ,stBody.open_account_date,sizeof(stBody.open_account_date     )  );
		pkt.GetParameterVal("A13"       ,stBody.account_due_date,sizeof(stBody.account_due_date      )  );
		pkt.GetParameterVal("B81"            ,stBody.regist_addr,sizeof(stBody.regist_addr           )  );
		pkt.GetParameterVal("B22"              ,stBody.cert_type );
		pkt.GetParameterVal("B23"               ,stBody.cert_num,sizeof(stBody.cert_num              )  );
		pkt.GetParameterVal("B24"           ,stBody.corp_prop_id,sizeof(stBody.corp_prop_id          )  );
		pkt.GetParameterVal("B25"       ,stBody.corp_regist_addr,sizeof(stBody.corp_regist_addr     )  );
		pkt.GetParameterVal("B29"               ,stBody.corp_zip,sizeof(stBody.corp_zip              )  );
		pkt.GetParameterVal("B26"               ,stBody.corp_tel,sizeof(stBody.corp_tel              )  );
		pkt.GetParameterVal("B27"               ,stBody.corp_fax,sizeof(stBody.corp_fax              )  );
		pkt.GetParameterVal("B28"             ,stBody.corp_email,sizeof(stBody.corp_email            )  );
		pkt.GetParameterVal("B35"        ,stBody.copr_authorizer,sizeof(stBody.copr_authorizer       )  );
		pkt.GetParameterVal("B08"       ,stBody.auth_nationality,sizeof(stBody.auth_nationality      )  );
		pkt.GetParameterVal("B01"      ,stBody.auth_cert_type_id );
		pkt.GetParameterVal("B02"           ,stBody.auth_cert_no,sizeof(stBody.auth_cert_no          )  );
		pkt.GetParameterVal("B03"              ,stBody.auth_addr,sizeof(stBody.auth_addr             )  );
		pkt.GetParameterVal("B07"               ,stBody.auth_zip,sizeof(stBody.auth_zip              )  );
		pkt.GetParameterVal("B04"               ,stBody.auth_tel,sizeof(stBody.auth_tel              )  );
		pkt.GetParameterVal("B05"               ,stBody.auth_fax,sizeof(stBody.auth_fax              )  );
		pkt.GetParameterVal("B06"             ,stBody.auth_email,sizeof(stBody.auth_email            )  );
		pkt.GetParameterVal("B20"           ,stBody.busi_license,sizeof(stBody.busi_license          )  );
		pkt.GetParameterVal("B32"               ,stBody.tax_cert,sizeof(stBody.tax_cert              )  );
		pkt.GetParameterVal("B21"          ,stBody.org_code_cert,sizeof(stBody.org_code_cert         )  );
		pkt.GetParameterVal("B80"         ,stBody.regist_address,sizeof(stBody.regist_address        )  );
		pkt.GetParameterVal("B41"        ,stBody.sigex_post_code,sizeof(stBody.sigex_post_code       )  );
		pkt.GetParameterVal("B42"              ,stBody.sigex_tel,sizeof(stBody.sigex_tel             )  );
		pkt.GetParameterVal("B43"              ,stBody.sigex_fax,sizeof(stBody.sigex_fax             )  );
		pkt.GetParameterVal("B44"            ,stBody.sigex_email,sizeof(stBody.sigex_email           )  );
		pkt.GetParameterVal("M30"                ,stBody.cust_id,sizeof(stBody.cust_id               )  );
		pkt.GetParameterVal("M38"         ,stBody.gess_broker_id,sizeof(stBody.gess_broker_id        )  );
		pkt.GetParameterVal("M39"              ,stBody.exec_name,sizeof(stBody.exec_name             )  );
		pkt.GetParameterVal("M41"      ,stBody.exec_cert_type_id );
		pkt.GetParameterVal("M42"          ,stBody.exec_cert_num,sizeof(stBody.exec_cert_num         )  );
		pkt.GetParameterVal("B45"              ,stBody.corp_code,sizeof(stBody.corp_code             )  );
		pkt.GetParameterVal("B30"              ,stBody.contacter,sizeof(stBody.contacter             )  );
		pkt.GetParameterVal("R09"               ,stBody.org_type,sizeof(stBody.org_type              )  );
		pkt.GetParameterVal("B34"            ,stBody.reg_capital );
		pkt.GetParameterVal("B46"              ,stBody.corp_type,sizeof(stBody.corp_type             )  );
		pkt.GetParameterVal("B48"    ,stBody.taxpayer_identifier,sizeof(stBody.taxpayer_identifier   )  );
		pkt.GetParameterVal("B33" ,stBody.is_val_added_taxplayer);
		pkt.GetParameterVal("B36"      ,stBody.taxplayer_address,sizeof(stBody.taxplayer_address     )  );
		pkt.GetParameterVal("B37"     ,stBody.taxpayer_telephone,sizeof(stBody.taxpayer_telephone    )  );
		pkt.GetParameterVal("B38"      ,stBody.taxpayer_bankcode,sizeof(stBody.taxpayer_bankcode     )  );
		pkt.GetParameterVal("B39"      ,stBody.taxpayer_bankinfo,sizeof(stBody.taxpayer_bankinfo     )  );
		pkt.GetParameterVal("B40"    ,stBody.taxpayer_account_id,sizeof(stBody.taxpayer_account_id   )  );
		pkt.GetParameterVal("M37"               ,stBody.grade_id,sizeof(stBody.grade_id              )  );
		pkt.GetParameterVal("M36"              ,stBody.acct_stat,sizeof(stBody.acct_stat             )  );
		pkt.GetParameterVal("B89"                   ,stBody.memo,sizeof(stBody.memo                  )  );
		return 0;
	}

	//----------------------------------------------报文接口 [6301] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTransferApply& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("J01"     ,stBody.f_busi_type     ); 
		pkt.AddParameter("T13"        ,stBody.exch_date       ); 
		pkt.AddParameter("M30"          ,stBody.cust_no         ); 
		pkt.AddParameter("J09"       ,stBody.access_way      ); 
		pkt.AddParameter("A02"      ,stBody.currency_id     ); 
		pkt.AddParameter("T55"         ,stBody.exch_bal        ); 
		pkt.AddParameter("B89"           ,stBody.remark          ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTransferApply& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);    
		pkt.GetParameterVal("T13"    ,stBody.gess_exch_date ,sizeof(stBody.gess_exch_date) );    
		pkt.GetParameterVal("X61"    ,stBody.gess_serial_no ,sizeof(stBody.gess_serial_no) );    
		pkt.GetParameterVal("T85"      ,stBody.bk_serial_no  ,sizeof(stBody.bk_serial_no)  );    
		pkt.GetParameterVal("X11"      ,stBody.client_serial_no   ,sizeof(stBody.client_serial_no) ); //从二级系统报文头中获得   
		return 0;
	}


	//----------------------------------------------报文接口 [6304] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryAcctTransfer& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("T13"       ,stBody.gess_exch_date   ); 
		pkt.AddParameter("X12"     ,stBody.client_serial_no ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryAcctTransfer& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag); 
		pkt.GetParameterVal("T13"         ,stBody.exch_date ,sizeof(stBody.exch_date       ) );
		pkt.GetParameterVal("X61"         ,stBody.serial_no ,sizeof(stBody.serial_no       )  );
		pkt.GetParameterVal("X12"  ,stBody.client_serial_no ,sizeof(stBody.client_serial_no) );
		pkt.GetParameterVal("M30"           ,stBody.acct_no ,sizeof(stBody.acct_no         )  );
		pkt.GetParameterVal("W40"    ,stBody.settle_bank_no ,sizeof(stBody.settle_bank_no  ) );
		pkt.GetParameterVal("J01"      ,stBody.f_busi_type  );
		pkt.GetParameterVal("J09"        ,stBody.access_way);
		pkt.GetParameterVal("J11"    ,stBody.out_account_no ,sizeof(stBody.out_account_no  ) );
		pkt.GetParameterVal("J12"     ,stBody.in_account_no ,sizeof(stBody.in_account_no   ) );
		pkt.GetParameterVal("T55"          ,stBody.exch_bal );
		pkt.GetParameterVal("T71"       ,stBody.check_stat1  );
		pkt.GetParameterVal("T73"       ,stBody.check_stat2 );
		pkt.GetParameterVal("T72"         ,stBody.send_stat  );
		pkt.GetParameterVal("J07"   ,stBody.in_account_flag  );
		pkt.GetParameterVal("B89"            ,stBody.remark ,sizeof(stBody.remark          )); 
		pkt.GetParameterVal("T26"      ,stBody.bk_plat_date ,sizeof(stBody.bk_plat_date    ) );
		pkt.GetParameterVal("T85"         ,stBody.bk_seq_no ,sizeof(stBody.bk_seq_no       ) );
		pkt.GetParameterVal("X41"       ,stBody.bk_rsp_code ,sizeof(stBody.bk_rsp_code     ) );
		pkt.GetParameterVal("X42"        ,stBody.bk_rsp_msg ,sizeof(stBody.bk_rsp_msg      ) );
		pkt.GetParameterVal("T86"       ,stBody.o_term_type ,sizeof(stBody.o_term_type     ) );
		pkt.GetParameterVal("T01"       ,stBody.o_teller_id ,sizeof(stBody.o_teller_id     ) );
		pkt.GetParameterVal("T28"            ,stBody.o_date ,sizeof(stBody.o_date          ) );
		pkt.GetParameterVal("T87"      ,stBody.c_term_type1 ,sizeof(stBody.c_term_type1    ) );
		pkt.GetParameterVal("T03"      ,stBody.c_teller_id1 ,sizeof(stBody.c_teller_id1    ) );
		pkt.GetParameterVal("T29"           ,stBody.c_date1 ,sizeof(stBody.c_date1         ) );
		pkt.GetParameterVal("T88"     ,stBody.c_term_type2  ,sizeof(stBody.c_term_type2    ) );
		pkt.GetParameterVal("T06"      ,stBody.c_teller_id2 ,sizeof(stBody.c_teller_id2    ) );
		pkt.GetParameterVal("T30"           ,stBody.c_date2 ,sizeof(stBody.c_date2         ) );

		return 0;
	}


	//----------------------------------------------报文接口 [6305] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqSigexMemTransferApply& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("J01"     ,stBody.f_busi_type     );  
		pkt.AddParameter("T13"        ,stBody.exch_date       );  
		pkt.AddParameter("J09"       ,stBody.access_way      );  
		pkt.AddParameter("A02"      ,stBody.currency_id     );  
		pkt.AddParameter("T55"         ,stBody.exch_bal        );  
		pkt.AddParameter("B89"           ,stBody.remark          );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspSigexMemTransferApply& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
		pkt.GetParameterVal("T13"    ,stBody.gess_exch_date ,sizeof(stBody.gess_exch_date) );  
		pkt.GetParameterVal("X61"    ,stBody.gess_serial_no ,sizeof(stBody.gess_serial_no) );  
		pkt.GetParameterVal("T85"      ,stBody.bk_serial_no  ,sizeof(stBody.bk_serial_no)  );  
		pkt.GetParameterVal("X11"      ,stBody.client_serial_no  ,sizeof(stBody.client_serial_no)  ); //从二级系统报文头中获得 

		return 0;
	}


	//----------------------------------------------报文接口 [6306] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQuerySigexMemTransfer& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("T13"       ,stBody.gess_exch_date   ); 
		pkt.AddParameter("X12"     ,stBody.client_serial_no ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQuerySigexMemTransfer& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"         ,stBody.oper_flag ); 
		pkt.GetParameterVal("T13"         ,stBody.exch_date         ,sizeof(stBody.exch_date       ) );   
		pkt.GetParameterVal("X61"         ,stBody.serial_no         ,sizeof(stBody.serial_no       ) );   
		pkt.GetParameterVal("X12"  				,stBody.client_serial_no  ,sizeof(stBody.client_serial_no) );   
		pkt.GetParameterVal("W40"   			,stBody.settle_bank_no    ,sizeof(stBody.settle_bank_no  ) );   
		pkt.GetParameterVal("J01"      		,stBody.f_busi_type  );   
		pkt.GetParameterVal("J09"         ,stBody.access_way    );   
		pkt.GetParameterVal("J11"    		  ,stBody.out_account_no    ,sizeof(stBody.out_account_no  ) );   
		pkt.GetParameterVal("J12"     		,stBody.in_account_no     ,sizeof(stBody.in_account_no   ) );   
		pkt.GetParameterVal("T55"         ,stBody.exch_bal          );   
		pkt.GetParameterVal("T71"       	,stBody.check_stat1   );   
		pkt.GetParameterVal("T73"       	,stBody.check_stat2   );   
		pkt.GetParameterVal("T72"         ,stBody.send_stat  );   
		pkt.GetParameterVal("J07"   			,stBody.in_account_flag  );   
		pkt.GetParameterVal("B89"         ,stBody.remark            ,sizeof(stBody.remark          ) );   
		pkt.GetParameterVal("T26"      		,stBody.bk_plat_date      ,sizeof(stBody.bk_plat_date    ) );   
		pkt.GetParameterVal("T85"         ,stBody.bk_seq_no         ,sizeof(stBody.bk_seq_no       ) );   
		pkt.GetParameterVal("X41"       	,stBody.bk_rsp_code       ,sizeof(stBody.bk_rsp_code     ) );   
		pkt.GetParameterVal("X42"        	,stBody.bk_rsp_msg        ,sizeof(stBody.bk_rsp_msg      ) );   
		pkt.GetParameterVal("T86"       	,stBody.o_term_type       ,sizeof(stBody.o_term_type     ) );   
		pkt.GetParameterVal("T01"       	,stBody.o_teller_id       ,sizeof(stBody.o_teller_id     ) );   
		pkt.GetParameterVal("T28"         ,stBody.o_date            ,sizeof(stBody.o_date          ) );   
		pkt.GetParameterVal("T87"      		,stBody.c_term_type1      ,sizeof(stBody.c_term_type1    ) );   
		pkt.GetParameterVal("T03"      		,stBody.c_teller_id1      ,sizeof(stBody.c_teller_id1    ) );   
		pkt.GetParameterVal("T29"         ,stBody.c_date1           ,sizeof(stBody.c_date1         ) );   
		pkt.GetParameterVal("T88"    		 	,stBody.c_term_type2      ,sizeof(stBody.c_term_type2    ) );   
		pkt.GetParameterVal("T06"      		,stBody.c_teller_id2      ,sizeof(stBody.c_teller_id2    ) );   
		pkt.GetParameterVal("T30"         ,stBody.c_date2           ,sizeof(stBody.c_date2         ) );   


		return 0;
	}


	//----------------------------------------------报文接口 [6401] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqEntrOrder& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );      
		pkt.AddParameter("M30"              ,stBody.cust_id         );
		pkt.AddParameter("I10"            ,stBody.prod_code       );
		pkt.AddParameter("U03"            ,stBody.req_exch_code       );
		pkt.AddParameter("O06"                ,stBody.price           );
		pkt.AddParameter("O07"               ,stBody.volume          );
		pkt.AddParameter("O18"       ,stBody.is_force_order  );
//		pkt.AddParameter("O01"       ,stBody.gess_local_order_no    );  
//		pkt.AddParameter("X61"       ,stBody.gess_serial_no   );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspEntrOrder& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
		pkt.GetParameterVal("O01"  ,stBody.gess_local_order_no ,sizeof(stBody.gess_local_order_no));  
		pkt.GetParameterVal("X61"       ,stBody.gess_serial_no    ,sizeof(stBody.gess_serial_no)  );  
		pkt.GetParameterVal("X11"       ,stBody.client_serial_no   ,sizeof(stBody.client_serial_no)   );  //从二级系统报文头中获得 
		return 0;
	}


	//----------------------------------------------报文接口 [6402] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqEntrCancel& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("O01"  ,stBody.gess_local_order_no ); 
		pkt.AddParameter("O00"             ,stBody.order_no            ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspEntrCancel& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
		pkt.GetParameterVal("O01"  ,stBody.gess_local_order_no,sizeof(stBody.gess_local_order_no) );  

		return 0;
	}


	//----------------------------------------------报文接口 [6403] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqEndDayListConfirm& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		pkt.AddParameter("M30"          ,stBody.cust_id    );
		pkt.AddParameter("T13"        ,stBody.exch_date  );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspEndDayListConfirm& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);

		return 0;
	}


	//----------------------------------------------报文接口 [6404] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryEntrFlow& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("O01"  ,stBody.gess_local_order_no );  
		pkt.AddParameter("T85"     ,stBody.client_serial_no    );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryEntrFlow& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("O00"  ,stBody.order_no            ,sizeof(stBody.order_no      ));       
		pkt.GetParameterVal("T85" ,stBody.client_serial_no    ,sizeof(stBody.client_serial_no   ));   
		pkt.GetParameterVal("O01" ,stBody.gess_local_order_no ,sizeof(stBody.gess_local_order_no));   
		pkt.GetParameterVal("X61" 	,stBody.gess_serial_no      ,sizeof(stBody.gess_serial_no     )); 
		pkt.GetParameterVal("M30"  ,stBody.cust_id             ,sizeof(stBody.cust_id         ));     
		pkt.GetParameterVal("U03" ,stBody.req_exch_code       ,sizeof(stBody.req_exch_code       ));      
		pkt.GetParameterVal("I00"  ,stBody.market_id           ,sizeof(stBody.market_id       ));     
		pkt.GetParameterVal("I10"  ,stBody.prod_code           ,sizeof(stBody.prod_code       ));     
		pkt.GetParameterVal("O06"  ,stBody.entr_price );     
		pkt.GetParameterVal("O07"  ,stBody.entr_amount );     
		pkt.GetParameterVal("O08" ,stBody.remain_amount   );      
		pkt.GetParameterVal("O03"  ,stBody.offset_flag  );     
		pkt.GetParameterVal("O21"  ,stBody.deli_flag   );     
		pkt.GetParameterVal("O02"  ,stBody.bs  );     
		pkt.GetParameterVal("T55"  ,stBody.exch_bal         );     
		pkt.GetParameterVal("T56"  ,stBody.froz_margin      );     
		pkt.GetParameterVal("T57"  ,stBody.exch_fare        );     
		pkt.GetParameterVal("O19"  ,stBody.cov_type            ,sizeof(stBody.cov_type        ));     
		pkt.GetParameterVal("O67" 	,stBody.src_match_no        ,sizeof(stBody.src_match_no    ));    
		pkt.GetParameterVal("O20" ,stBody.origin_order_no     ,sizeof(stBody.origin_order_no ));      
		pkt.GetParameterVal("O66"  ,stBody.match_type          ,sizeof(stBody.match_type      ));     
		pkt.GetParameterVal("O16" ,stBody.order_send_type     ,sizeof(stBody.order_send_type ));      
		pkt.GetParameterVal("O09"  ,stBody.entr_stat   );     
		pkt.GetParameterVal("O17"  ,stBody.cancel_flag );     
		pkt.GetParameterVal("T13"  ,stBody.exch_date           ,sizeof(stBody.exch_date       ));     
		pkt.GetParameterVal("T17"  ,stBody.accept_time         ,sizeof(stBody.accept_time     ));     
		pkt.GetParameterVal("T86"  ,stBody.e_term_type         ,sizeof(stBody.e_term_type     ));     
		pkt.GetParameterVal("X62"  ,stBody.e_branch_id         ,sizeof(stBody.e_branch_id     ));     
		pkt.GetParameterVal("T01"  ,stBody.e_teller_id         ,sizeof(stBody.e_teller_id     ));     
		pkt.GetParameterVal("M60"  ,stBody.e_trader_id         ,sizeof(stBody.e_trader_id     ));     
		pkt.GetParameterVal("T12"  ,stBody.e_exch_time         ,sizeof(stBody.e_exch_time     ));     
		pkt.GetParameterVal("T87"  ,stBody.c_term_type         ,sizeof(stBody.c_term_type     ));     
		pkt.GetParameterVal("T02"  ,stBody.c_teller_id         ,sizeof(stBody.c_teller_id     ));     
		pkt.GetParameterVal("T07"  ,stBody.c_trader_id         ,sizeof(stBody.c_trader_id     ));     
		pkt.GetParameterVal("T22"  ,stBody.c_exch_time         ,sizeof(stBody.c_exch_time     ));     
		pkt.GetParameterVal("X42"  ,stBody.rsp_msg             ,sizeof(stBody.rsp_msg         ));     

		return 0;
	}

	//----------------------------------------------报文接口 [6405] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqRefPriceApply& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("M30"     ,stBody.cust_id    );  
		pkt.AddParameter("Q34"		,stBody.game_id );  
		pkt.AddParameter("I20"     ,stBody.report_price);  
		pkt.AddParameter("I10"     ,stBody.prod_code    );  
		pkt.AddParameter("T13"     ,stBody.exch_date    );  
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspRefPriceApply& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		return 0;
	}

	//----------------------------------------------报文接口 [6406] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqFpEntrOrder& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("M30"     ,stBody.cust_id    );  
		pkt.AddParameter("Q34"  ,stBody.game_id );  
		pkt.AddParameter("O02"     ,stBody.bs    );  
		pkt.AddParameter("015"     ,stBody.order_type    );/////////应为015  
		pkt.AddParameter("O07"     ,stBody.volume    );  
		pkt.AddParameter("I10"     ,stBody.prod_code    );  
		pkt.AddParameter("Q41"     ,stBody.round_id    );  
		pkt.AddParameter("O16"     ,stBody.order_send_type    );  
		pkt.AddParameter("O06"     ,stBody.entr_price    );  
		pkt.AddParameter("O01"     ,stBody.gess_local_order_no    );  
		pkt.AddParameter("X61"     ,stBody.gess_serial_no    );  
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspFpEntrOrder& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("O01"     ,stBody.gess_local_order_no,sizeof(stBody.gess_local_order_no)    );  
		pkt.GetParameterVal("X61"     ,stBody.gess_serial_no ,sizeof(stBody.gess_serial_no)   );  		
		return 0;
	}
	//----------------------------------------------报文接口 [6407] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqFpEntrCancel& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("M30"  ,stBody.acct_no );  
		pkt.AddParameter("I10"     ,stBody.prod_code    );  
		pkt.AddParameter("O02"  ,stBody.bs );  
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspFpEntrCancel& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		return 0;
	}
	//----------------------------------------------报文接口 [6408] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqRefPriceQueryFlow& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("Q34"     ,stBody.game_id    );  
		pkt.AddParameter("I10"  ,stBody.prod_code );  
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspRefPriceQueryFlow& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		return 0;
	}
	//----------------------------------------------报文接口 [6409] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqFpEntrOrderQueryFlow& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("O01"  ,stBody.gess_local_order_no );  
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspFpEntrOrderQueryFlow& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("T13"   ,stBody.exch_date			,sizeof(stBody.exch_date  ));                                    
		pkt.GetParameterVal("O00"   ,stBody.order_no			);                                               
		pkt.GetParameterVal("O01"   ,stBody.gess_local_order_no	,sizeof(stBody.gess_local_order_no));                                                
		pkt.GetParameterVal("M30"   ,stBody.acct_no				,sizeof(stBody.acct_no       ));                                                
		pkt.GetParameterVal("I00"   ,stBody.market_id			,sizeof(stBody.market_id     ));                                          
		pkt.GetParameterVal("I10"   ,stBody.prod_code			,sizeof(stBody.prod_code     ));                                             
		pkt.GetParameterVal("Q34"   ,stBody.game_id				,sizeof(stBody.game_id       ));                                          
		pkt.GetParameterVal("Q41"   ,stBody.round_id);                                             
		pkt.GetParameterVal("Q47"   ,stBody.entr_phase);                                           
		pkt.GetParameterVal("O02"   ,stBody.bs		);                                               
		pkt.GetParameterVal("O06"   ,stBody.entr_price		);                                           
		pkt.GetParameterVal("O07"   ,stBody.entr_amount		);                                         
		pkt.GetParameterVal("T52"   ,stBody.entr_weight		);                                     
		pkt.GetParameterVal("T56"   ,stBody.froz_margin		);                                    
		pkt.GetParameterVal("T57"   ,stBody.froz_exch_fare);                               
		pkt.GetParameterVal("O09"   ,stBody.entr_stat		);                                            
		pkt.GetParameterVal("O17"   ,stBody.cancel_flag		);                                     
		pkt.GetParameterVal("T86"   ,stBody.e_term_type		,sizeof(stBody.e_term_type   ));                                      
		pkt.GetParameterVal("M60"   ,stBody.e_trader_id		,sizeof(stBody.e_trader_id   ));                                          
		pkt.GetParameterVal("T12"   ,stBody.entr_time			,sizeof(stBody.entr_time     ));                                              
		pkt.GetParameterVal("T87"   ,stBody.c_term_type		,sizeof(stBody.c_term_type   ));                                        
		pkt.GetParameterVal("T07"   ,stBody.c_trader_id		,sizeof(stBody.c_trader_id   ));                                        
		pkt.GetParameterVal("T22"   ,stBody.cancel_time		,sizeof(stBody.cancel_time   ));   
		return 0;
	}
	//----------------------------------------------报文接口 [6501] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTakeApply& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );    
		pkt.AddParameter("M30"          ,stBody.cust_id         );
		pkt.AddParameter("V00"       ,stBody.variety_id      );
		pkt.AddParameter("T53"       ,stBody.app_amount      );
		pkt.AddParameter("B50"        ,stBody.city_code       );
		pkt.AddParameter("W00"          ,stBody.stor_id         );
		pkt.AddParameter("K22"         ,stBody.take_man        );
		pkt.AddParameter("B01"     ,stBody.cert_type_id    );
		pkt.AddParameter("B02"         ,stBody.cert_num        );
		pkt.AddParameter("K23"          ,stBody.app_pwd         );
		pkt.AddParameter("T01"       ,stBody.app_record      );
		pkt.AddParameter("K24"        ,stBody.self_draw       );
		pkt.AddParameter("K25"       ,stBody.trade_draw      );
		pkt.AddParameter("K28"     ,stBody.gold_forword    );
		pkt.AddParameter("K06"           ,stBody.remark          );
		pkt.AddParameter("T11"        ,stBody.take_date       );
		pkt.AddParameter("K61"    ,stBody.lend_check_no   );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTakeApply& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("K00"   ,stBody.gess_local_sheet_no,sizeof(stBody.gess_local_sheet_no)); 
		pkt.GetParameterVal("K20"              ,stBody.sheet_no,sizeof(stBody.sheet_no)           ); 
		pkt.GetParameterVal("M30"               ,stBody.cust_id,sizeof(stBody.cust_id)            ); 
		pkt.GetParameterVal("T72"             ,stBody.send_stat ); 
		pkt.GetParameterVal("K27"                  ,stBody.stat ); 
		pkt.GetParameterVal("T56"           ,stBody.take_margin        ); 
		pkt.GetParameterVal("K29"           ,stBody.is_other_take       ); 
		pkt.GetParameterVal("T18"        ,stBody.app_start_date,sizeof(stBody.app_start_date)     ); 
		pkt.GetParameterVal("T19"          ,stBody.app_end_date,sizeof(stBody.app_end_date)       ); 
		pkt.GetParameterVal("V00"            ,stBody.variety_id,sizeof(stBody.variety_id)         ); 
		pkt.GetParameterVal("T53"            ,stBody.app_amount        ); 
		pkt.GetParameterVal("K21"             ,stBody.draw_type); 
		pkt.GetParameterVal("K24"             ,stBody.self_draw          ); 
		pkt.GetParameterVal("K25"            ,stBody.trade_draw         ); 

		return 0;
	}

	//----------------------------------------------报文接口 [6502] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTakeApplyCancel& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );    
		pkt.AddParameter("K00"  ,stBody.gess_local_sheet_no );   
		pkt.AddParameter("K20"             ,stBody.sheet_no            );   
		pkt.AddParameter("M30"              ,stBody.cust_id             );   
		pkt.AddParameter("K22"             ,stBody.take_man            );   
		pkt.AddParameter("K23"             ,stBody.take_pwd            );   

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTakeApplyCancel& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag); 
		pkt.GetParameterVal("K00"   ,stBody.gess_local_sheet_no,sizeof(stBody.gess_local_sheet_no) ); 
		pkt.GetParameterVal("K20"   ,stBody.sheet_no ,sizeof(stBody.sheet_no)           ); 
		pkt.GetParameterVal("M30"   ,stBody.cust_id ,sizeof(stBody.cust_id)            ); 
		pkt.GetParameterVal("K27"   ,stBody.stat    ); 

		return 0;
	}

	//----------------------------------------------报文接口 [6503] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryTakeList& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("K00"  ,stBody.gess_local_sheet_no ); 
		pkt.AddParameter("K20"             ,stBody.sheet_no            ); 
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryTakeList& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("K00"   ,stBody.gess_local_sheet_no ,sizeof(stBody.gess_local_sheet_no));
		pkt.GetParameterVal("K20"              ,stBody.sheet_no ,sizeof(stBody.sheet_no        ));
		pkt.GetParameterVal("M30"               ,stBody.cust_id ,sizeof(stBody.cust_id         ));
		pkt.GetParameterVal("V00"            ,stBody.variety_id ,sizeof(stBody.variety_id      ));
		pkt.GetParameterVal("T53"            ,stBody.app_amount);
		pkt.GetParameterVal("K21"             ,stBody.draw_type );
		pkt.GetParameterVal("K24"             ,stBody.self_draw );
		pkt.GetParameterVal("K25"            ,stBody.trade_draw );
		pkt.GetParameterVal("B50"             ,stBody.city_code ,sizeof(stBody.city_code       ));
		pkt.GetParameterVal("W00"               ,stBody.stor_id ,sizeof(stBody.stor_id         ));
		pkt.GetParameterVal("K22"              ,stBody.take_man ,sizeof(stBody.take_man        ));
		pkt.GetParameterVal("B01"          ,stBody.cert_type_id );
		pkt.GetParameterVal("B02"              ,stBody.cert_num ,sizeof(stBody.cert_num        ));
		pkt.GetParameterVal("T01"            ,stBody.app_record ,sizeof(stBody.app_record      ));
		pkt.GetParameterVal("T11"              ,stBody.app_date ,sizeof(stBody.app_date        ));
		pkt.GetParameterVal("T12"              ,stBody.app_time ,sizeof(stBody.app_time        ));
		pkt.GetParameterVal("T15"         ,stBody.app_exch_date ,sizeof(stBody.app_exch_date   ));
		pkt.GetParameterVal("T18"        ,stBody.app_start_date ,sizeof(stBody.app_start_date  ));
		pkt.GetParameterVal("T19"          ,stBody.app_end_date ,sizeof(stBody.app_end_date    ));
		pkt.GetParameterVal("T13"         ,stBody.due_take_date ,sizeof(stBody.due_take_date   ));
		pkt.GetParameterVal("K27"                  ,stBody.stat );
		pkt.GetParameterVal("T23"           ,stBody.cancel_date ,sizeof(stBody.cancel_date     ));
		pkt.GetParameterVal("T22"           ,stBody.cancel_time ,sizeof(stBody.cancel_time     ));
		pkt.GetParameterVal("T29"      ,stBody.cancel_exch_date ,sizeof(stBody.cancel_exch_date));
		pkt.GetParameterVal("T02"         ,stBody.cancel_record ,sizeof(stBody.cancel_record   ));
		pkt.GetParameterVal("T72"             ,stBody.send_stat );
		pkt.GetParameterVal("T56"           ,stBody.take_margin);
		pkt.GetParameterVal("K29"         ,stBody.is_other_take );
		pkt.GetParameterVal("K30"           ,stBody.take_affirm );
		pkt.GetParameterVal("X41"         ,stBody.take_rsp_code ,sizeof(stBody.rsp_code        ));
		pkt.GetParameterVal("X42"          ,stBody.take_rsp_msg ,sizeof(stBody.rsp_msg         ));
		pkt.GetParameterVal("K28"          ,stBody.gold_forword );
		pkt.GetParameterVal("K06"                ,stBody.remark ,sizeof(stBody.remark          ));  
		return 0;
	}


	//----------------------------------------------报文接口 [6701] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTransferDataDownload& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("T13"			   ,stBody.exch_date ); 
		pkt.AddParameter("X62"                ,stBody.branchID  ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTransferDataDownload& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		//pkt.GetParameterVal("alm_check_sum"         ,stBody.alm_check_sum       );
		//pkt.GetParameterVal("alm_check_detail"      ,stBody.alm_check_detail    );

		return 0;
	}


	//----------------------------------------------报文接口 [6702] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqLiquDataDownload& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("T13"			   ,stBody.exch_date ); 
		pkt.AddParameter("X62"               ,stBody.branchID ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspLiquDataDownload& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		pkt.GetParameterVal("X24"   ,stBody.newxml_file_addr ,sizeof(stBody.newxml_file_addr));
		pkt.GetParameterVal("G21"   ,stBody.sftp_user_name ,sizeof(stBody.sftp_user_name));
		pkt.GetParameterVal("M62"   ,stBody.sftp_pwd ,sizeof(stBody.sftp_pwd));
		return 0;
	}


	//----------------------------------------------报文接口 [6704] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqFundCheckDataDownload& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("T13"			   ,stBody.exch_date ); 
		pkt.AddParameter("X62"               ,stBody.branchID ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspFundCheckDataDownload& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
//		pkt.GetParameterVal("alm_forward_member_posi"   ,stBody.alm_forward_member_posi );  
//		pkt.GetParameterVal("alm_defer_member_posi"     ,stBody.alm_defer_member_posi   );  
//		pkt.GetParameterVal("alm_member_capital"        ,stBody.alm_member_capital      );  
//		pkt.GetParameterVal("alm_fee_summary"           ,stBody.alm_fee_summary         );  
//		pkt.GetParameterVal("alm_settle_summary"        ,stBody.alm_settle_summary      );  

		return 0;
	}


	//----------------------------------------------报文接口 [6705] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqInterestDataDownload& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
		pkt.AddParameter("T13"			   ,stBody.exch_date ); 
		pkt.AddParameter("X62"               ,stBody.branchID ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspInterestDataDownload& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
//		pkt.GetParameterVal("alm_pre_interest"      ,stBody.alm_pre_interest    );
//		pkt.GetParameterVal("alm_interest"          ,stBody.alm_interest        );

		return 0;
	}


	//----------------------------------------------报文接口 [6801] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQuerySigexNotice& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    ); 
		pkt.AddParameter("T80"           ,stBody.seq_no       );  
		pkt.AddParameter("Q84"            ,stBody.title        );  
		pkt.AddParameter("T18"      ,stBody.s_exch_date  );  
		pkt.AddParameter("T19"      ,stBody.e_exch_date  );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQuerySigexNotice& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
//		pkt.GetParameterVal("alm_result"            ,stBody.alm_result);
		return 0;
	}


	//----------------------------------------------报文接口 [6901] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqSigexBasicDataDownload& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );  
// 		pkt.AddParameter("city_info"                ,stBody.city_info               ); 
// 		pkt.AddParameter("spec_date"                ,stBody.spec_date               ); 
// 		pkt.AddParameter("prod_code_def"            ,stBody.prod_code_def           ); 
// 		pkt.AddParameter("variety"                  ,stBody.variety                 ); 
// 		pkt.AddParameter("variety_substitue"        ,stBody.variety_substitue       ); 
// 		pkt.AddParameter("fare_model_def"           ,stBody.fare_model_def          ); 
// 		pkt.AddParameter("wh_fare_model"            ,stBody.wh_fare_model           ); 
// 		pkt.AddParameter("defer_over_fee"           ,stBody.defer_over_fee          ); 
// 		pkt.AddParameter("defer_fee"                ,stBody.defer_fee               ); 
// 		pkt.AddParameter("rmb_day_interest_data"    ,stBody.rmb_day_interest_data   ); 
// 		pkt.AddParameter("take_margin_para"         ,stBody.take_margin_para        ); 
// 		pkt.AddParameter("branch_fare_interval"     ,stBody.branch_fare_interval    ); 
// 		pkt.AddParameter("stor_info"                ,stBody.stor_info               ); 
		pkt.AddParameter("X62"                ,stBody.branchID               ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspSigexBasicDataDownload& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);  
// 		pkt.GetParameterVal("alm_city_info"                 ,stBody.alm_city_info            );  
// 		pkt.GetParameterVal("alm_spec_date"                 ,stBody.alm_spec_date            );  
// 		pkt.GetParameterVal("alm_prod_code_def"             ,stBody.alm_prod_code_def        );  
// 		pkt.GetParameterVal("alm_variety"                   ,stBody.alm_variety              );  
// 		pkt.GetParameterVal("alm_variety_substitue"         ,stBody.alm_variety_substitue    );  
// 		pkt.GetParameterVal("alm_fare_model_def"            ,stBody.alm_fare_model_def       );  
// 		pkt.GetParameterVal("alm_wh_fare_model"             ,stBody.alm_wh_fare_model        );  
// 		pkt.GetParameterVal("alm_defer_over_fee"            ,stBody.alm_defer_over_fee       );  
// 		pkt.GetParameterVal("alm_defer_fee"                 ,stBody.alm_defer_fee            );  
// 		pkt.GetParameterVal("alm_rmb_day_interest_rata"     ,stBody.alm_rmb_day_interest_rata);  
// 		pkt.GetParameterVal("alm_take_margin_para"          ,stBody.alm_take_margin_para     );  
// 		pkt.GetParameterVal("alm_branch_interval"           ,stBody.alm_branch_interval      );  
// 		pkt.GetParameterVal("alm_stor_info"                 ,stBody.alm_stor_info            );  
// 		pkt.GetParameterVal("alm_stor_city_info"            ,stBody.alm_stor_city_info       );  
// 		pkt.GetParameterVal("alm_fare_model_detail"         ,stBody.alm_fare_model_detail    );  

		return 0;
	}


	//----------------------------------------------报文接口 [6902] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqSigexMemFareSyn& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("B52"        ,stBody.fare_model_id       );  
		pkt.AddParameter("B53"      ,stBody.fare_model_name     );  
		pkt.AddParameter("B54"      ,stBody.fare_model_type     );  
		pkt.AddParameter("B55"       ,stBody.contain_bourse      );  
		pkt.AddParameter("X62"       ,stBody.gess_branch_id      );  
//		pkt.AddParameter("alm_fare_info_list"   ,stBody.alm_fare_info_list  );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspSigexMemFareSyn& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		return 0;
	}



	//----------------------------------------------报文接口 [6904] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqSpecialAcctFareSyn& stBody, CGtpPacket& pkt)
	{
		Struct2PacketReq(stBody,pkt);
		pkt.AddParameter("X63"        ,stBody.oper_flag    );   
		pkt.AddParameter("M30"			    ,stBody.cust_id				);  
//		pkt.AddParameter("alm_acct_fare_info"   ,stBody.alm_acct_fare_info  );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspSpecialAcctFareSyn& stBody, CGtpPacket& pkt)
	{
		Packet2StructRsp((TRspMsg *)&stBody,pkt);
		pkt.GetParameterVal("X63"          ,stBody.oper_flag);
		return 0;
	}


	//----------------------------------------------报文接口 [onRecvSpotQuotation] 报文结构编解码
	//解码：GtpMsgArray -> 结构
	static int Array2Struct(TSpotQuotation& stBody, CGtpPacket& pkt)
	{
		string Q53;
		pkt.GetParameterVal("Q53",Q53);
		CGtpMsgArray array(Q53);
		array.GetParameterVal("I10"            ,stBody.instID ,sizeof(stBody.instID)     );  
		array.GetParameterVal("I11"              ,stBody.name    ,sizeof(stBody.name)    );  
		array.GetParameterVal("Q14"         ,stBody.lastClose   );  
		array.GetParameterVal("Q15"              ,stBody.open        );  
		array.GetParameterVal("Q16"              ,stBody.high        );  
		array.GetParameterVal("Q17"               ,stBody.low         );  
		array.GetParameterVal("Q18"              ,stBody.last        );  
		array.GetParameterVal("Q19"             ,stBody.close       );  
		string Q00 = array.GetValueByKeyIndex("Q00",0);
		CGtpMsgArray subArray(Q00);
		for (int i = 0; i<5 ; i++)
		{
			//获得行情档数
			int n = FromString<int>(subArray.GetValueByKeyIndex("Q02",i));
			switch (n)
			{
			case 1:
				subArray.GetParameterVal("Q21"              ,stBody.bid1    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot1   ,i  );
				subArray.GetParameterVal("Q23"              ,stBody.ask1    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot1   ,i  );
				break;
			case 2:
				subArray.GetParameterVal("Q21"              ,stBody.bid2     ,i   );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot2    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask2    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot2    ,i ); 
				break;
			case 3:
				subArray.GetParameterVal("Q21"              ,stBody.bid3    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot3    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask3    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot3    ,i );
				break;
			case 4:
				subArray.GetParameterVal("Q21"              ,stBody.bid4    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot4    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask4   ,i     );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot4    ,i ); 
				break;
			case 5:
				subArray.GetParameterVal("Q21"              ,stBody.bid5    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot5   ,i  );  
				subArray.GetParameterVal("Q23"              ,stBody.ask5    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot5   ,i  ); 
				break;
			default:
				break;
			}
		}

// 		array.GetParameterVal("H01"              ,stBody.bid1        );  
// 		array.GetParameterVal("H02"           ,stBody.bidLot1     );  
// 		array.GetParameterVal("H03"              ,stBody.bid2        );  
// 		array.GetParameterVal("H04"           ,stBody.bidLot2     );  
// 		array.GetParameterVal("H05"              ,stBody.bid3        );  
// 		array.GetParameterVal("H06"           ,stBody.bidLot3     );  
// 		array.GetParameterVal("H07"              ,stBody.bid4        );  
// 		array.GetParameterVal("H08"           ,stBody.bidLot4     );  
// 		array.GetParameterVal("H09"              ,stBody.bid5        );  
// 		array.GetParameterVal("H10"           ,stBody.bidLot5     );  
// 		array.GetParameterVal("H11"              ,stBody.ask1        );  
// 		array.GetParameterVal("H12"           ,stBody.askLot1     );  
// 		array.GetParameterVal("H13"              ,stBody.ask2        );  
// 		array.GetParameterVal("H14"           ,stBody.askLot2     );  
// 		array.GetParameterVal("H15"              ,stBody.ask3        );  
// 		array.GetParameterVal("H16"           ,stBody.askLot3     );  
// 		array.GetParameterVal("H17"              ,stBody.ask4        );  
// 		array.GetParameterVal("H18"           ,stBody.askLot4     );  
// 		array.GetParameterVal("H19"              ,stBody.ask5        );  
// 		array.GetParameterVal("H20"           ,stBody.askLot5     );  
		array.GetParameterVal("O64"            ,stBody.volume      );  
		array.GetParameterVal("Q25"            ,stBody.weight      );  
		array.GetParameterVal("Q26"         ,stBody.highLimit   );  
		array.GetParameterVal("Q36"          ,stBody.lowLimit    ); 
		array.GetParameterVal("Q28"            ,stBody.upDown      );  
		array.GetParameterVal("Q29"        ,stBody.upDownRate  );  
		array.GetParameterVal("Q30"          ,stBody.turnOver    );  
		array.GetParameterVal("Q31"           ,stBody.average     );  
		array.GetParameterVal("Q11"         ,stBody.quoteDate   ,sizeof(stBody.quoteDate));  
		array.GetParameterVal("Q12"         ,stBody.quoteTime   ,sizeof(stBody.quoteTime));  
		array.GetParameterVal("X05"        ,stBody.sequenceNo  );  ///////////行情序号////////////////////////
		pkt.GetParameterVal("X05"		,stBody.sequence_no     ,sizeof(stBody.sequence_no));//从报文中取得
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);//从报文中取得

		return 0;
	}
	//请求报文解码: 报文 -> 结构  
/*	static int Packet2Struct(TSpotQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I10"            ,stBody.instID      );  
		pkt.GetParameterVal("I11"              ,stBody.name        );  
		pkt.GetParameterVal("Q14"         ,stBody.lastClose   );  
		pkt.GetParameterVal("Q15"              ,stBody.open        );  
		pkt.GetParameterVal("Q16"              ,stBody.high        );  
		pkt.GetParameterVal("Q17"               ,stBody.low         );  
		pkt.GetParameterVal("Q18"              ,stBody.last        );  
		pkt.GetParameterVal("Q19"             ,stBody.close       );  
		pkt.GetParameterVal("H01"              ,stBody.bid1        );  
		pkt.GetParameterVal("H02"           ,stBody.bidLot1     );  
		pkt.GetParameterVal("H03"              ,stBody.bid2        );  
		pkt.GetParameterVal("H04"           ,stBody.bidLot2     );  
		pkt.GetParameterVal("H05"              ,stBody.bid3        );  
		pkt.GetParameterVal("H06"           ,stBody.bidLot3     );  
		pkt.GetParameterVal("H07"              ,stBody.bid4        );  
		pkt.GetParameterVal("H08"           ,stBody.bidLot4     );  
		pkt.GetParameterVal("H09"              ,stBody.bid5        );  
		pkt.GetParameterVal("H10"           ,stBody.bidLot5     );  
		pkt.GetParameterVal("H11"              ,stBody.ask1        );  
		pkt.GetParameterVal("H12"           ,stBody.askLot1     );  
		pkt.GetParameterVal("H13"              ,stBody.ask2        );  
		pkt.GetParameterVal("H14"           ,stBody.askLot2     );  
		pkt.GetParameterVal("H15"              ,stBody.ask3        );  
		pkt.GetParameterVal("H16"           ,stBody.askLot3     );  
		pkt.GetParameterVal("H17"              ,stBody.ask4        );  
		pkt.GetParameterVal("H18"           ,stBody.askLot4     );  
		pkt.GetParameterVal("H19"              ,stBody.ask5        );  
		pkt.GetParameterVal("H20"           ,stBody.askLot5     );  
		pkt.GetParameterVal("O64"            ,stBody.volume      );  
		pkt.GetParameterVal("Q25"            ,stBody.weight      );  
		pkt.GetParameterVal("Q26"         ,stBody.highLimit   );  
		pkt.GetParameterVal("Q36"          ,stBody.lowLimit    ); ////////////////////////////////// 
		pkt.GetParameterVal("Q28"            ,stBody.upDown      );  
		pkt.GetParameterVal("Q29"        ,stBody.upDownRate  );  
		pkt.GetParameterVal("Q30"          ,stBody.turnOver    );  
		pkt.GetParameterVal("Q31"           ,stBody.average     );  
		pkt.GetParameterVal("Q11"         ,stBody.quoteDate   );  
		pkt.GetParameterVal("Q12"         ,stBody.quoteTime   );  
		pkt.GetParameterVal("X05"        ,stBody.sequenceNo  );  ///////////行情序号////////////////////////
		pkt.GetParameterVal("X05"		,stBody.sequence_no     );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet(TSpotQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.instID      ); 
		pkt.AddParameter("I11"              ,stBody.name        ); 
		pkt.AddParameter("Q14"         ,stBody.lastClose   ); 
		pkt.AddParameter("Q15"              ,stBody.open        ); 
		pkt.AddParameter("Q16"              ,stBody.high        ); 
		pkt.AddParameter("Q17"               ,stBody.low         ); 
		pkt.AddParameter("Q18"              ,stBody.last        ); 
		pkt.AddParameter("Q19"             ,stBody.close       ); 
		pkt.AddParameter("H01"              ,stBody.bid1        ); 
		pkt.AddParameter("H02"           ,stBody.bidLot1     ); 
		pkt.AddParameter("H03"              ,stBody.bid2        ); 
		pkt.AddParameter("H04"           ,stBody.bidLot2     ); 
		pkt.AddParameter("H05"              ,stBody.bid3        ); 
		pkt.AddParameter("H06"           ,stBody.bidLot3     ); 
		pkt.AddParameter("H07"              ,stBody.bid4        ); 
		pkt.AddParameter("H08"           ,stBody.bidLot4     ); 
		pkt.AddParameter("H09"              ,stBody.bid5        ); 
		pkt.AddParameter("H10"           ,stBody.bidLot5     ); 
		pkt.AddParameter("H11"              ,stBody.ask1        ); 
		pkt.AddParameter("H12"           ,stBody.askLot1     ); 
		pkt.AddParameter("H13"              ,stBody.ask2        ); 
		pkt.AddParameter("H14"           ,stBody.askLot2     ); 
		pkt.AddParameter("H15"              ,stBody.ask3        ); 
		pkt.AddParameter("H16"           ,stBody.askLot3     ); 
		pkt.AddParameter("H17"              ,stBody.ask4        ); 
		pkt.AddParameter("H18"           ,stBody.askLot4     ); 
		pkt.AddParameter("H19"              ,stBody.ask5        ); 
		pkt.AddParameter("H20"           ,stBody.askLot5     ); 
		pkt.AddParameter("O07"            ,stBody.volume      ); 
		pkt.AddParameter("Q25"            ,stBody.weight      ); 
		pkt.AddParameter("Q26"         ,stBody.highLimit   ); 
		pkt.AddParameter("Q36"          ,stBody.lowLimit    ); 
		pkt.AddParameter("Q28"            ,stBody.upDown      ); 
		pkt.AddParameter("Q29"        ,stBody.upDownRate  ); 
		pkt.AddParameter("Q30"          ,stBody.turnOver    ); 
		pkt.AddParameter("Q31"           ,stBody.average     ); 
		pkt.AddParameter("Q11"         ,stBody.quoteDate   ); 
		pkt.AddParameter("Q12"         ,stBody.quoteTime   ); 
		pkt.AddParameter("X05"        ,stBody.sequenceNo  ); 
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}

*/
	//----------------------------------------------报文接口 [onRecvForwardQuotation] 报文结构编解码

	//请求报文解码: GtpArray -> 结构  
	static int Array2Struct(TForwardQuotation& stBody, CGtpPacket& pkt)
	{
		string Q57;
		pkt.GetParameterVal("Q57",Q57);
		CGtpMsgArray array(Q57);
		array.GetParameterVal("I10"            ,stBody.instID   ,sizeof(stBody.instID)   );
		array.GetParameterVal("I11"              ,stBody.name   ,sizeof(stBody.name)     );
		array.GetParameterVal("Q13"        ,stBody.lastSettle  );
		array.GetParameterVal("Q14"         ,stBody.lastClose   );
		array.GetParameterVal("Q15"              ,stBody.open        );
		array.GetParameterVal("Q16"              ,stBody.high        );
		array.GetParameterVal("Q17"               ,stBody.low         );
		array.GetParameterVal("Q18"              ,stBody.last        );
		array.GetParameterVal("Q19"             ,stBody.close       );
		array.GetParameterVal("Q20"            ,stBody.settle      );
		string Q00 = array.GetValueByKeyIndex("Q00",0);
		CGtpMsgArray subArray(Q00);
		for (int i = 0; i<5 ; i++)
		{
			//获得行情档数
			int n = FromString<int>(subArray.GetValueByKeyIndex("Q02",i));
			switch (n)
			{
			case 1:
				subArray.GetParameterVal("Q21"              ,stBody.bid1    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot1   ,i  );
				subArray.GetParameterVal("Q23"              ,stBody.ask1    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot1   ,i  );
				break;
			case 2:
				subArray.GetParameterVal("Q21"              ,stBody.bid2     ,i   );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot2    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask2    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot2    ,i ); 
				break;
			case 3:
				subArray.GetParameterVal("Q21"              ,stBody.bid3    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot3    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask3    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot3    ,i );
				break;
			case 4:
				subArray.GetParameterVal("Q21"              ,stBody.bid4    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot4    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask4   ,i     );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot4    ,i ); 
				break;
			case 5:
				subArray.GetParameterVal("Q21"              ,stBody.bid5    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot5   ,i  );  
				subArray.GetParameterVal("Q23"              ,stBody.ask5    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot5   ,i  ); 
				break;
			default:
				break;
			}
		}

// 		pkt.GetParameterVal("H01"              ,stBody.bid1        );
// 		pkt.GetParameterVal("H02"           ,stBody.bidLot1     );
// 		pkt.GetParameterVal("H03"              ,stBody.bid2        );
// 		pkt.GetParameterVal("H04"           ,stBody.bidLot2     );
// 		pkt.GetParameterVal("H05"              ,stBody.bid3        );
// 		pkt.GetParameterVal("H06"           ,stBody.bidLot3     );
// 		pkt.GetParameterVal("H07"              ,stBody.bid4        );
// 		pkt.GetParameterVal("H08"           ,stBody.bidLot4     );
// 		pkt.GetParameterVal("H09"              ,stBody.bid5        );
// 		pkt.GetParameterVal("H10"           ,stBody.bidLot5     );
// 		pkt.GetParameterVal("H11"              ,stBody.ask1        );
// 		pkt.GetParameterVal("H12"           ,stBody.askLot1     );
// 		pkt.GetParameterVal("H13"              ,stBody.ask2        );
// 		pkt.GetParameterVal("H14"           ,stBody.askLot2     );
// 		pkt.GetParameterVal("H15"              ,stBody.ask3        );
// 		pkt.GetParameterVal("H16"           ,stBody.askLot3     );
// 		pkt.GetParameterVal("H17"              ,stBody.ask4        );
// 		pkt.GetParameterVal("H18"           ,stBody.askLot4     );
// 		pkt.GetParameterVal("H19"              ,stBody.ask5        );
// 		pkt.GetParameterVal("H20"           ,stBody.askLot5     );
		array.GetParameterVal("O64"            ,stBody.volume      );///////////////////应该使用O64 前置及文档都使用O64，代表成交数量
		array.GetParameterVal("Q25"            ,stBody.weight      );
		array.GetParameterVal("Q26"         ,stBody.highLimit   );
		array.GetParameterVal("Q36"          ,stBody.lowLimit    );
		array.GetParameterVal("Q27"             ,stBody.Posi        );
		array.GetParameterVal("Q28"            ,stBody.upDown      );
		array.GetParameterVal("Q29"        ,stBody.upDownRate  );
		array.GetParameterVal("Q30"          ,stBody.turnOver    );
		array.GetParameterVal("Q31"           ,stBody.average     );
		array.GetParameterVal("Q11"         ,stBody.quoteDate ,sizeof(stBody.quoteDate)  );
		array.GetParameterVal("Q12"         ,stBody.quoteTime ,sizeof(stBody.quoteTime)  );
		array.GetParameterVal("X05"        ,stBody.sequenceNo  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

/*
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct(TForwardQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I10"            ,stBody.instID      );
		pkt.GetParameterVal("I11"              ,stBody.name        );
		pkt.GetParameterVal("Q13"        ,stBody.lastSettle  );
		pkt.GetParameterVal("Q14"         ,stBody.lastClose   );
		pkt.GetParameterVal("Q15"              ,stBody.open        );
		pkt.GetParameterVal("Q16"              ,stBody.high        );
		pkt.GetParameterVal("Q17"               ,stBody.low         );
		pkt.GetParameterVal("Q18"              ,stBody.last        );
		pkt.GetParameterVal("Q19"             ,stBody.close       );
		pkt.GetParameterVal("Q20"            ,stBody.settle      );
		pkt.GetParameterVal("H01"              ,stBody.bid1        );
		pkt.GetParameterVal("H02"           ,stBody.bidLot1     );
		pkt.GetParameterVal("H03"              ,stBody.bid2        );
		pkt.GetParameterVal("H04"           ,stBody.bidLot2     );
		pkt.GetParameterVal("H05"              ,stBody.bid3        );
		pkt.GetParameterVal("H06"           ,stBody.bidLot3     );
		pkt.GetParameterVal("H07"              ,stBody.bid4        );
		pkt.GetParameterVal("H08"           ,stBody.bidLot4     );
		pkt.GetParameterVal("H09"              ,stBody.bid5        );
		pkt.GetParameterVal("H10"           ,stBody.bidLot5     );
		pkt.GetParameterVal("H11"              ,stBody.ask1        );
		pkt.GetParameterVal("H12"           ,stBody.askLot1     );
		pkt.GetParameterVal("H13"              ,stBody.ask2        );
		pkt.GetParameterVal("H14"           ,stBody.askLot2     );
		pkt.GetParameterVal("H15"              ,stBody.ask3        );
		pkt.GetParameterVal("H16"           ,stBody.askLot3     );
		pkt.GetParameterVal("H17"              ,stBody.ask4        );
		pkt.GetParameterVal("H18"           ,stBody.askLot4     );
		pkt.GetParameterVal("H19"              ,stBody.ask5        );
		pkt.GetParameterVal("H20"           ,stBody.askLot5     );
		pkt.GetParameterVal("O07"            ,stBody.volume      );
		pkt.GetParameterVal("Q25"            ,stBody.weight      );
		pkt.GetParameterVal("Q26"         ,stBody.highLimit   );
		pkt.GetParameterVal("Q36"          ,stBody.lowLimit    );
		pkt.GetParameterVal("Q27"             ,stBody.Posi        );
		pkt.GetParameterVal("Q28"            ,stBody.upDown      );
		pkt.GetParameterVal("Q29"        ,stBody.upDownRate  );
		pkt.GetParameterVal("Q30"          ,stBody.turnOver    );
		pkt.GetParameterVal("Q31"           ,stBody.average     );
		pkt.GetParameterVal("Q11"         ,stBody.quoteDate   );
		pkt.GetParameterVal("Q12"         ,stBody.quoteTime   );
		pkt.GetParameterVal("X05"        ,stBody.sequenceNo  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no     );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet(TForwardQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.instID      );
		pkt.AddParameter("I11"              ,stBody.name        );
		pkt.AddParameter("Q13"        ,stBody.lastSettle  );
		pkt.AddParameter("Q14"         ,stBody.lastClose   );
		pkt.AddParameter("Q15"              ,stBody.open        );
		pkt.AddParameter("Q16"              ,stBody.high        );
		pkt.AddParameter("Q17"               ,stBody.low         );
		pkt.AddParameter("Q18"              ,stBody.last        );
		pkt.AddParameter("Q19"             ,stBody.close       );
		pkt.AddParameter("Q20"            ,stBody.settle      );
		pkt.AddParameter("H01"              ,stBody.bid1        );
		pkt.AddParameter("H02"           ,stBody.bidLot1     );
		pkt.AddParameter("H03"              ,stBody.bid2        );
		pkt.AddParameter("H04"           ,stBody.bidLot2     );
		pkt.AddParameter("H05"              ,stBody.bid3        );
		pkt.AddParameter("H06"           ,stBody.bidLot3     );
		pkt.AddParameter("H07"              ,stBody.bid4        );
		pkt.AddParameter("H08"           ,stBody.bidLot4     );
		pkt.AddParameter("H09"              ,stBody.bid5        );
		pkt.AddParameter("H10"           ,stBody.bidLot5     );
		pkt.AddParameter("H11"              ,stBody.ask1        );
		pkt.AddParameter("H12"           ,stBody.askLot1     );
		pkt.AddParameter("H13"              ,stBody.ask2        );
		pkt.AddParameter("H14"           ,stBody.askLot2     );
		pkt.AddParameter("H15"              ,stBody.ask3        );
		pkt.AddParameter("H16"           ,stBody.askLot3     );
		pkt.AddParameter("H17"              ,stBody.ask4        );
		pkt.AddParameter("H18"           ,stBody.askLot4     );
		pkt.AddParameter("H19"              ,stBody.ask5        );
		pkt.AddParameter("H20"           ,stBody.askLot5     );
		pkt.AddParameter("O07"            ,stBody.volume      );
		pkt.AddParameter("Q25"            ,stBody.weight      );
		pkt.AddParameter("Q26"         ,stBody.highLimit   );
		pkt.AddParameter("Q36"          ,stBody.lowLimit    );
		pkt.AddParameter("Q27"             ,stBody.Posi        );
		pkt.AddParameter("Q28"            ,stBody.upDown      );
		pkt.AddParameter("Q29"        ,stBody.upDownRate  );
		pkt.AddParameter("Q30"          ,stBody.turnOver    );
		pkt.AddParameter("Q31"           ,stBody.average     );
		pkt.AddParameter("Q11"         ,stBody.quoteDate   );
		pkt.AddParameter("Q12"         ,stBody.quoteTime   );
		pkt.AddParameter("X05"        ,stBody.sequenceNo  );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}

*/
	//----------------------------------------------报文接口 [onRecvDeferQuotation] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Array2Struct(TDeferQuotation& stBody, CGtpPacket& pkt)
	{
		string Q55;
		pkt.GetParameterVal("Q55",Q55);
		CGtpMsgArray array(Q55);
		array.GetParameterVal("I10"            ,stBody.instID    ,sizeof(stBody.instID)   );  
		array.GetParameterVal("I11"              ,stBody.name     ,sizeof(stBody.name)    );
		array.GetParameterVal("Q13"        ,stBody.lastSettle   );
		array.GetParameterVal("Q14"         ,stBody.lastClose    );
		array.GetParameterVal("Q15"              ,stBody.open         );
		array.GetParameterVal("Q16"              ,stBody.high         );
		array.GetParameterVal("Q17"               ,stBody.low          );
		array.GetParameterVal("Q18"              ,stBody.last         );
		array.GetParameterVal("Q19"             ,stBody.close        );
		array.GetParameterVal("Q20"            ,stBody.settle       );
		string Q00 = array.GetValueByKeyIndex("Q00",0);
		CGtpMsgArray subArray(Q00);
		for (int i = 0; i<5 ; i++)
		{
			//获得行情档数
			int n = FromString<int>(subArray.GetValueByKeyIndex("Q02",i));
			switch (n)
			{
			case 1:
				subArray.GetParameterVal("Q21"              ,stBody.bid1    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot1   ,i  );
				subArray.GetParameterVal("Q23"              ,stBody.ask1    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot1   ,i  );
				break;
			case 2:
				subArray.GetParameterVal("Q21"              ,stBody.bid2     ,i   );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot2    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask2    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot2    ,i ); 
				break;
			case 3:
				subArray.GetParameterVal("Q21"              ,stBody.bid3    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot3    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask3    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot3    ,i );
				break;
			case 4:
				subArray.GetParameterVal("Q21"              ,stBody.bid4    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot4    ,i ); 
				subArray.GetParameterVal("Q23"              ,stBody.ask4   ,i     );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot4    ,i ); 
				break;
			case 5:
				subArray.GetParameterVal("Q21"              ,stBody.bid5    ,i    );  
				subArray.GetParameterVal("Q22"           ,stBody.bidLot5   ,i  );  
				subArray.GetParameterVal("Q23"              ,stBody.ask5    ,i    );  
				subArray.GetParameterVal("Q24"           ,stBody.askLot5   ,i  ); 
				break;
			default:
				break;
			}
		}
// 		array.GetParameterVal("H01"              ,stBody.bid1         );
// 		array.GetParameterVal("H02"           ,stBody.bidLot1      );
// 		array.GetParameterVal("H03"              ,stBody.bid2         );
// 		array.GetParameterVal("H04"           ,stBody.bidLot2      );
// 		array.GetParameterVal("H05"              ,stBody.bid3         );
// 		array.GetParameterVal("H06"           ,stBody.bidLot3      );
// 		array.GetParameterVal("H07"              ,stBody.bid4         );
// 		array.GetParameterVal("H08"           ,stBody.bidLot4      );
// 		array.GetParameterVal("H09"              ,stBody.bid5         );
// 		array.GetParameterVal("H10"           ,stBody.bidLot5      );
// 		array.GetParameterVal("H11"              ,stBody.ask1         );
// 		array.GetParameterVal("H12"           ,stBody.askLot1      );
// 		array.GetParameterVal("H13"              ,stBody.ask2         );
// 		array.GetParameterVal("H14"           ,stBody.askLot2      );
// 		array.GetParameterVal("H15"              ,stBody.ask3         );
// 		array.GetParameterVal("H16"           ,stBody.askLot3      );
// 		array.GetParameterVal("H17"              ,stBody.ask4         );
// 		array.GetParameterVal("H18"           ,stBody.askLot4      );
// 		array.GetParameterVal("H19"              ,stBody.ask5         );
// 		array.GetParameterVal("H20"           ,stBody.askLot5      );
		array.GetParameterVal("O64"            ,stBody.volume       );/////////////应该使用O64
		array.GetParameterVal("Q25"            ,stBody.weight       );
		array.GetParameterVal("Q26"         ,stBody.highLimit    );
		array.GetParameterVal("Q36"          ,stBody.lowLimit     );
		array.GetParameterVal("Q27"             ,stBody.Posi         );
		array.GetParameterVal("Q28"            ,stBody.upDown       );
		array.GetParameterVal("Q29"        ,stBody.upDownRate   );
		array.GetParameterVal("Q30"          ,stBody.turnOver     );
		array.GetParameterVal("Q31"           ,stBody.average      );
		array.GetParameterVal("Q11"         ,stBody.quoteDate  ,sizeof(stBody.quoteDate)  );
		array.GetParameterVal("Q12"         ,stBody.quoteTime ,sizeof(stBody.quoteTime)   );
		array.GetParameterVal("X05"        ,stBody.sequenceNo   );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}
/*
	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet(TDeferQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.instID       );  
		pkt.AddParameter("I11"              ,stBody.name         );
		pkt.AddParameter("Q13"        ,stBody.lastSettle   );
		pkt.AddParameter("Q14"         ,stBody.lastClose    );
		pkt.AddParameter("Q15"              ,stBody.open         );
		pkt.AddParameter("Q16"              ,stBody.high         );
		pkt.AddParameter("Q17"               ,stBody.low          );
		pkt.AddParameter("Q18"              ,stBody.last         );
		pkt.AddParameter("Q19"             ,stBody.close        );
		pkt.AddParameter("Q20"            ,stBody.settle       );
		pkt.AddParameter("H01"              ,stBody.bid1         );
		pkt.AddParameter("H02"           ,stBody.bidLot1      );
		pkt.AddParameter("H03"              ,stBody.bid2         );
		pkt.AddParameter("H04"           ,stBody.bidLot2      );
		pkt.AddParameter("H05"              ,stBody.bid3         );
		pkt.AddParameter("H06"           ,stBody.bidLot3      );
		pkt.AddParameter("H07"              ,stBody.bid4         );
		pkt.AddParameter("H08"           ,stBody.bidLot4      );
		pkt.AddParameter("H09"              ,stBody.bid5         );
		pkt.AddParameter("H10"           ,stBody.bidLot5      );
		pkt.AddParameter("H11"              ,stBody.ask1         );
		pkt.AddParameter("H12"           ,stBody.askLot1      );
		pkt.AddParameter("H13"              ,stBody.ask2         );
		pkt.AddParameter("H14"           ,stBody.askLot2      );
		pkt.AddParameter("H15"              ,stBody.ask3         );
		pkt.AddParameter("H16"           ,stBody.askLot3      );
		pkt.AddParameter("H17"              ,stBody.ask4         );
		pkt.AddParameter("H18"           ,stBody.askLot4      );
		pkt.AddParameter("H19"              ,stBody.ask5         );
		pkt.AddParameter("H20"           ,stBody.askLot5      );
		pkt.AddParameter("O07"            ,stBody.volume       );
		pkt.AddParameter("Q25"            ,stBody.weight       );
		pkt.AddParameter("Q26"         ,stBody.highLimit    );
		pkt.AddParameter("Q36"          ,stBody.lowLimit     );
		pkt.AddParameter("Q27"             ,stBody.Posi         );
		pkt.AddParameter("Q28"            ,stBody.upDown       );
		pkt.AddParameter("Q29"        ,stBody.upDownRate   );
		pkt.AddParameter("Q30"          ,stBody.turnOver     );
		pkt.AddParameter("Q31"           ,stBody.average      );
		pkt.AddParameter("Q11"         ,stBody.quoteDate    );
		pkt.AddParameter("Q12"         ,stBody.quoteTime    );
		pkt.AddParameter("X05"        ,stBody.sequenceNo   );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}
*/

	//----------------------------------------------报文接口 [onRecvDeferDeliveryQuotation] 报文结构编解码
	static int Array2Struct(TDeferDeliveryQuotation& stBody,CGtpPacket &pkt)
	{
		string Q69;
		pkt.GetParameterVal("Q69",Q69);
		CGtpMsgArray array(Q69);
		array.GetParameterVal("I10"            ,stBody.instID    ,sizeof(stBody.instID)   );  
		array.GetParameterVal("Q22"		,stBody.bidLot);
		array.GetParameterVal("Q24"		,stBody.askLot);
		array.GetParameterVal("Q33"		,stBody.midBidLot);
		array.GetParameterVal("Q32"		,stBody.midAskLot);
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);
		return 0;
	}
	//----------------------------------------------报文接口 [onRecvRtnFpRoundQuotation] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct(TFpRoundQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I10"            ,stBody.prodCode    ,sizeof(stBody.prodCode)   );  
		pkt.GetParameterVal("I11"              ,stBody.prodName   ,sizeof(stBody.prodName)      );
		pkt.GetParameterVal("T13"        ,stBody.exchDate ,sizeof(stBody.exchDate)  );
		pkt.GetParameterVal("Q34"         ,stBody.gameID   ,sizeof(stBody.gameID) );
		pkt.GetParameterVal("Q41"              ,stBody.roundID   );
		pkt.GetParameterVal("O06"              ,stBody.price         );
		pkt.GetParameterVal("I13"               ,stBody.adjust          );
		pkt.GetParameterVal("Q22"              ,stBody.bidLot         );
		pkt.GetParameterVal("Q24"             ,stBody.askLot        );
		pkt.GetParameterVal("Q13"            ,stBody.lastSettlePrice       );
		pkt.GetParameterVal("Q12"              ,stBody.quoteTime      ,sizeof(stBody.quoteTime)   );
		pkt.GetParameterVal("T80"           ,stBody.sequenceNo    ,sizeof(stBody.sequenceNo)  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet(TFpRoundQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.prodCode       );  
		pkt.AddParameter("I11"              ,stBody.prodName         );
		pkt.AddParameter("T13"        ,stBody.exchDate   );
		pkt.AddParameter("Q34"         ,stBody.gameID    );
		pkt.AddParameter("Q41"              ,stBody.roundID         );
		pkt.AddParameter("O06"              ,stBody.price         );
		pkt.AddParameter("I13"               ,stBody.adjust          );
		pkt.AddParameter("Q22"              ,stBody.bidLot         );
		pkt.AddParameter("Q24"             ,stBody.askLot        );
		pkt.AddParameter("Q13"            ,stBody.lastSettlePrice       );
		pkt.AddParameter("Q12"              ,stBody.quoteTime         );
		pkt.AddParameter("T80"           ,stBody.sequenceNo      );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);
		return 0;
	}
	//----------------------------------------------报文接口 [onRecvRtnFpQuotation] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct(TFpQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I10"            ,stBody.prodCode     ,sizeof(stBody.prodCode)  );  
		pkt.GetParameterVal("I11"              ,stBody.prodName    ,sizeof(stBody.prodName)     );
		pkt.GetParameterVal("T13"        ,stBody.exchDate ,sizeof(stBody.exchDate)  );
		pkt.GetParameterVal("Q34"         ,stBody.gameID  ,sizeof(stBody.gameID)  );
		pkt.GetParameterVal("O06"              ,stBody.price         );
		pkt.GetParameterVal("Q40"               ,stBody.isSettlePrice     ,sizeof(stBody.isSettlePrice)     );
		pkt.GetParameterVal("Q25"              ,stBody.matchVolume         );
		pkt.GetParameterVal("Q45"             ,stBody.initPrice        );
		pkt.GetParameterVal("Q46"            ,stBody.rounds       );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet(TFpQuotation& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.prodCode       );  
		pkt.AddParameter("I11"              ,stBody.prodName         );
		pkt.AddParameter("T13"        ,stBody.exchDate   );
		pkt.AddParameter("Q34"         ,stBody.gameID    );
		pkt.AddParameter("O06"              ,stBody.price         );
		pkt.AddParameter("Q40"               ,stBody.isSettlePrice          );
		pkt.AddParameter("Q25"              ,stBody.matchVolume         );
		pkt.AddParameter("Q45"             ,stBody.initPrice        );
		pkt.AddParameter("Q46"            ,stBody.rounds       );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRtnSpotMarketStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSpotMarketState& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I00"            ,stBody.marketID  ,sizeof(stBody.marketID)    );
		pkt.GetParameterVal("I04"        ,stBody.marketState  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRtnDeferMarketStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferMarketState& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I00"            ,stBody.marketID ,sizeof(stBody.marketID)     );
		pkt.GetParameterVal("I04"        ,stBody.marketState  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no    ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}
	//----------------------------------------------报文接口 [onRecvRtnForwardMarketStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TForwardMarketState& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I00"            ,stBody.marketID  ,sizeof(stBody.marketID)    );
		pkt.GetParameterVal("I04"        ,stBody.marketState  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no    ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}
	//----------------------------------------------报文接口 [onRecvRtnSpotInstStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSpotInstState& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I10"            ,stBody.instID     ,sizeof(stBody.instID) );
		pkt.GetParameterVal("I19"        ,stBody.tradeState  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no    ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSpotInstState& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.instID      );
		pkt.AddParameter("I19"        ,stBody.tradeState  );
		pkt.AddParameter("X05"		 ,stBody.sequence_no       );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnForwardInstStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TForwardInstState& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I10"            ,stBody.instID    ,sizeof(stBody.instID)  );
		pkt.GetParameterVal("I19"        ,stBody.tradeState  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)     );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TForwardInstState& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.instID      );
		pkt.AddParameter("I19"        ,stBody.tradeState  );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferInstStateUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferInstState& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I10"            ,stBody.instID   ,sizeof(stBody.instID)   );
		pkt.GetParameterVal("I19"        ,stBody.tradeState  );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)    );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferInstState& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.instID      );
		pkt.AddParameter("I19"        ,stBody.tradeState  );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnFpInstStatUpdate] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TFpInstStat& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("I10"            ,stBody.ProdCode   ,sizeof(stBody.ProdCode)   );
		pkt.GetParameterVal("T13"        ,stBody.ExchDate,sizeof(stBody.ExchDate)  );
		pkt.GetParameterVal("I34"		,stBody.PreState  );
		pkt.GetParameterVal("I35" ,stBody.NowState);
		pkt.GetParameterVal("Q34"            ,stBody.GameID  ,sizeof(stBody.GameID)    );
		pkt.GetParameterVal("Q41"        ,stBody.RoundID  );
		pkt.GetParameterVal("T21"		,stBody.StartTime ,sizeof(stBody.StartTime)    );
		pkt.GetParameterVal("T24" ,stBody.ContinueTime,sizeof(stBody.ContinueTime));
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TFpInstStat& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("I10"            ,stBody.ProdCode      );
		pkt.AddParameter("T13"        ,stBody.ExchDate  );
		pkt.AddParameter("I34"		 ,stBody.PreState     );
		pkt.AddParameter("I35" ,stBody.NowState);
		pkt.AddParameter("Q34"            ,stBody.GameID      );
		pkt.AddParameter("Q41"        ,stBody.RoundID  );
		pkt.AddParameter("T21"		 ,stBody.StartTime     );
		pkt.AddParameter("T24" ,stBody.ContinueTime);
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRtnSpotOrder/onRecvRtnSpotOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSpotOrder& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O00"           ,stBody.orderNo,sizeof(stBody.orderNo      )      ); 
		pkt.GetParameterVal("I10"            ,stBody.instID,sizeof(stBody.instID       )       ); 
		pkt.GetParameterVal("M30"          ,stBody.clientID,sizeof(stBody.clientID     )     ); 
		pkt.GetParameterVal("M00"          ,stBody.memberID,sizeof(stBody.memberID     )     ); 
		pkt.GetParameterVal("O02"         ,stBody.buyOrSell   ); 
		pkt.GetParameterVal("T11"         ,stBody.applyDate,sizeof(stBody.applyDate    )    ); 
		pkt.GetParameterVal("T12"         ,stBody.applyTime,sizeof(stBody.applyTime    )    ); 
		pkt.GetParameterVal("M60"          ,stBody.traderID,sizeof(stBody.traderID     )     ); 
		pkt.GetParameterVal("O06"             ,stBody.price    ); 
		pkt.GetParameterVal("O07"            ,stBody.amount    ); 
		pkt.GetParameterVal("O08"      ,stBody.remainAmount ); 
		pkt.GetParameterVal("T22"        ,stBody.cancelTime,sizeof(stBody.cancelTime   ) 	  ); 
		pkt.GetParameterVal("T02"          ,stBody.cancelID,sizeof(stBody.cancelID     )     ); 
		pkt.GetParameterVal("O09"            ,stBody.status  ); 
		pkt.GetParameterVal("O66"         ,stBody.matchType  ); 
		pkt.GetParameterVal("I27"     ,stBody.endorseInstID,sizeof(stBody.endorseInstID) ); 
		pkt.GetParameterVal("O01"      ,stBody.localOrderNo,sizeof(stBody.localOrderNo )	 );                                    
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSpotOrder& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O00"           ,stBody.orderNo         );
		pkt.AddParameter("I10"            ,stBody.instID          );
		pkt.AddParameter("M30"          ,stBody.clientID        );
		pkt.AddParameter("M00"          ,stBody.memberID        );
		pkt.AddParameter("O02"         ,stBody.buyOrSell       );
		pkt.AddParameter("T11"         ,stBody.applyDate       );
		pkt.AddParameter("T12"         ,stBody.applyTime       );
		pkt.AddParameter("M60"          ,stBody.traderID        );
		pkt.AddParameter("O06"             ,stBody.price           );
		pkt.AddParameter("O07"            ,stBody.amount          );
		pkt.AddParameter("O08"      ,stBody.remainAmount    );
		pkt.AddParameter("T22"        ,stBody.cancelTime      );
		pkt.AddParameter("T02"          ,stBody.cancelID        );
		pkt.AddParameter("O09"            ,stBody.status          );
		pkt.AddParameter("O66"         ,stBody.matchType       );
		pkt.AddParameter("I27"     ,stBody.endorseInstID   );
		pkt.AddParameter("O01"      ,stBody.localOrderNo    );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnForwardOrder/onRecvRtnForwardOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TForwardOrder& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O00"           ,stBody.orderNo,sizeof(stBody.orderNo     )     ); 
		pkt.GetParameterVal("I10"            ,stBody.instID,sizeof(stBody.instID      )      );
		pkt.GetParameterVal("M30"          ,stBody.clientID,sizeof(stBody.clientID    )    );  
		pkt.GetParameterVal("M00"          ,stBody.memberID,sizeof(stBody.memberID    )    );  
		pkt.GetParameterVal("O02"         ,stBody.buyOrSell );   
		pkt.GetParameterVal("T11"         ,stBody.applyDate,sizeof(stBody.applyDate   )   );   
		pkt.GetParameterVal("T12"         ,stBody.applyTime,sizeof(stBody.applyTime   )   );   
		pkt.GetParameterVal("M60"          ,stBody.traderID,sizeof(stBody.traderID    )    );  
		pkt.GetParameterVal("O06"             ,stBody.price  );
		pkt.GetParameterVal("O07"            ,stBody.amount  );
		pkt.GetParameterVal("O08"      ,stBody.remainAmount);      
		pkt.GetParameterVal("T22"        ,stBody.cancelTime,sizeof(stBody.cancelTime  )  );    
		pkt.GetParameterVal("T02"          ,stBody.cancelID,sizeof(stBody.cancelID    )    );  
		pkt.GetParameterVal("O09"            ,stBody.status  );
		pkt.GetParameterVal("O01"      ,stBody.localOrderNo,sizeof(stBody.localOrderNo));      
		pkt.GetParameterVal("O65"         ,stBody.matchType );   
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TForwardOrder& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O00"           ,stBody.orderNo         );
		pkt.AddParameter("I10"            ,stBody.instID          );
		pkt.AddParameter("M30"          ,stBody.clientID        );
		pkt.AddParameter("M00"          ,stBody.memberID        );
		pkt.AddParameter("O02"         ,stBody.buyOrSell       );
		pkt.AddParameter("T11"         ,stBody.applyDate       );
		pkt.AddParameter("T12"         ,stBody.applyTime       );
		pkt.AddParameter("M60"          ,stBody.traderID        );
		pkt.AddParameter("O06"             ,stBody.price           );
		pkt.AddParameter("O07"            ,stBody.amount          );
		pkt.AddParameter("O08"      ,stBody.remainAmount    );
		pkt.AddParameter("T22"        ,stBody.cancelTime      );
		pkt.AddParameter("T02"          ,stBody.cancelID        );
		pkt.AddParameter("O09"            ,stBody.status          );
		pkt.AddParameter("O01"      ,stBody.localOrderNo    );
		pkt.AddParameter("O65"         ,stBody.matchType       );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferOrder/onRecvRtnDeferOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferOrder& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O00"           ,stBody.orderNo,sizeof(stBody.orderNo     )     );  
		pkt.GetParameterVal("M30"          ,stBody.clientID,sizeof(stBody.clientID    )    );  
		pkt.GetParameterVal("I10"            ,stBody.instID,sizeof(stBody.instID      )      );  
		pkt.GetParameterVal("M00"          ,stBody.memberID,sizeof(stBody.memberID    )    );  
		pkt.GetParameterVal("O02"         ,stBody.buyOrSell  );  
		pkt.GetParameterVal("T11"         ,stBody.applyDate,sizeof(stBody.applyDate   )   );  
		pkt.GetParameterVal("T12"         ,stBody.applyTime,sizeof(stBody.applyTime   )   );  
		pkt.GetParameterVal("O03"        ,stBody.offSetFlag );  
		pkt.GetParameterVal("O06"             ,stBody.price   );  
		pkt.GetParameterVal("O07"            ,stBody.amount   );  
		pkt.GetParameterVal("O08"      ,stBody.remainAmount);  
		pkt.GetParameterVal("T22"        ,stBody.cancelTime,sizeof(stBody.cancelTime  )  );  
		pkt.GetParameterVal("O09"            ,stBody.status    );  
		pkt.GetParameterVal("O01"      ,stBody.localOrderNo,sizeof(stBody.localOrderNo));  
		pkt.GetParameterVal("I24"            ,stBody.margin  );  
		pkt.GetParameterVal("I80"        ,stBody.marginType );  
		pkt.GetParameterVal("M60"          ,stBody.traderID,sizeof(stBody.traderID    )    );  
		pkt.GetParameterVal("T02"          ,stBody.cancelID,sizeof(stBody.cancelID    )    );  
		pkt.GetParameterVal("O65"         ,stBody.matchType );   
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferOrder& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O00"           ,stBody.orderNo         );
		pkt.AddParameter("M30"          ,stBody.clientID        );
		pkt.AddParameter("I10"            ,stBody.instID          );
		pkt.AddParameter("M00"          ,stBody.memberID        );
		pkt.AddParameter("O02"         ,stBody.buyOrSell       );
		pkt.AddParameter("T11"         ,stBody.applyDate       );
		pkt.AddParameter("T12"         ,stBody.applyTime       );
		pkt.AddParameter("O03"        ,stBody.offSetFlag      );
		pkt.AddParameter("O06"             ,stBody.price           );
		pkt.AddParameter("O07"            ,stBody.amount          );
		pkt.AddParameter("O08"      ,stBody.remainAmount    );
		pkt.AddParameter("T22"        ,stBody.cancelTime      );
		pkt.AddParameter("O09"            ,stBody.status          );
		pkt.AddParameter("O01"      ,stBody.localOrderNo    );
		pkt.AddParameter("I24"            ,stBody.margin          );
		pkt.AddParameter("I80"        ,stBody.marginType      );
		pkt.AddParameter("M60"          ,stBody.traderID        );
		pkt.AddParameter("T02"          ,stBody.cancelID        );
		pkt.AddParameter("O65"         ,stBody.matchType       );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferDeliveryAppOrder/onRecvRtnDeferDeliveryAppOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferDeliveryAppOrder& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O00"           ,stBody.orderNo,sizeof(stBody.orderNo     )     ); 
		pkt.GetParameterVal("M30"          ,stBody.clientID,sizeof(stBody.clientID    )    );  
		pkt.GetParameterVal("I10"            ,stBody.instID,sizeof(stBody.instID      )      );
		pkt.GetParameterVal("O02"         ,stBody.buyOrSell  );   
		pkt.GetParameterVal("T11"         ,stBody.applyDate,sizeof(stBody.applyDate   )   );   
		pkt.GetParameterVal("T12"         ,stBody.applyTime,sizeof(stBody.applyTime   )   );   
		pkt.GetParameterVal("O07"            ,stBody.amount );
		pkt.GetParameterVal("T22"        ,stBody.cancelTime,sizeof(stBody.cancelTime  )  );    
		pkt.GetParameterVal("O09"            ,stBody.status    );
		pkt.GetParameterVal("O01"      ,stBody.localOrderID,sizeof(stBody.localOrderID));      
		pkt.GetParameterVal("M00"          ,stBody.memberID,sizeof(stBody.memberID    )    );  
		pkt.GetParameterVal("M60"          ,stBody.traderID,sizeof(stBody.traderID    )    );  
		pkt.GetParameterVal("T02"          ,stBody.cancelID,sizeof(stBody.cancelID    )    );  
		pkt.GetParameterVal("O08"      ,stBody.remainAmount    ); 
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferDeliveryAppOrder& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O00"           ,stBody.orderNo         ); 
		pkt.AddParameter("M30"          ,stBody.clientID        );
		pkt.AddParameter("I10"            ,stBody.instID          );
		pkt.AddParameter("O02"         ,stBody.buyOrSell       );
		pkt.AddParameter("T11"         ,stBody.applyDate       );
		pkt.AddParameter("T12"         ,stBody.applyTime       );
		pkt.AddParameter("O07"            ,stBody.amount          );
		pkt.AddParameter("T22"        ,stBody.cancelTime      );
		pkt.AddParameter("O09"            ,stBody.status          );
		pkt.AddParameter("O01"      ,stBody.localOrderID    );
		pkt.AddParameter("M00"          ,stBody.memberID        );
		pkt.AddParameter("M60"          ,stBody.traderID        );
		pkt.AddParameter("T02"          ,stBody.cancelID        );
		pkt.AddParameter("O08"      ,stBody.remainAmount    );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnSpotMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSpotMatch& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O60"           ,stBody.matchNo,sizeof(stBody.matchNo     )     );  
		pkt.GetParameterVal("O02"         ,stBody.buyOrSell  );    
		pkt.GetParameterVal("M30"          ,stBody.clientID,sizeof(stBody.clientID    )    );  
		pkt.GetParameterVal("M31"          ,stBody.clientType );  
		pkt.GetParameterVal("M00"          ,stBody.memberID,sizeof(stBody.memberID    )    );   
		pkt.GetParameterVal("I10"            ,stBody.instID,sizeof(stBody.instID      )      ); 
		pkt.GetParameterVal("O61"         ,stBody.matchDate,sizeof(stBody.matchDate   )   );    
		pkt.GetParameterVal("O62"         ,stBody.matchTime,sizeof(stBody.matchTime   )   );     
		pkt.GetParameterVal("O63"             ,stBody.price);
		pkt.GetParameterVal("O64"            ,stBody.volume);  
		pkt.GetParameterVal("O00"           ,stBody.orderNo,sizeof(stBody.orderNo     )     );  
		pkt.GetParameterVal("O01"      ,stBody.localOrderNo,sizeof(stBody.localOrderNo)); 
		pkt.GetParameterVal("O66"         ,stBody.matchType);
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSpotMatch& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O60"           ,stBody.matchNo         );
		pkt.AddParameter("O02"         ,stBody.buyOrSell       );
		pkt.AddParameter("M30"          ,stBody.clientID        );
		pkt.AddParameter("M31"          ,stBody.clientType        );
		pkt.AddParameter("M00"          ,stBody.memberID        );
		pkt.AddParameter("I10"            ,stBody.instID          );
		pkt.AddParameter("O61"         ,stBody.matchDate       );
		pkt.AddParameter("O62"         ,stBody.matchTime       );
		pkt.AddParameter("O63"             ,stBody.price           );
		pkt.AddParameter("O64"            ,stBody.volume          );
		pkt.AddParameter("O00"           ,stBody.orderNo         );
		pkt.AddParameter("O01"      ,stBody.localOrderNo    );
		pkt.AddParameter("O66"         ,stBody.matchType       );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnForwardMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TForwardMatch& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O60"           ,stBody.matchNo,sizeof(stBody.matchNo     )     );  
		pkt.GetParameterVal("O02"         ,stBody.buyOrSell );  
		pkt.GetParameterVal("M30"          ,stBody.clientID,sizeof(stBody.clientID    )    );  
		pkt.GetParameterVal("M31"          ,stBody.clientType );  
		pkt.GetParameterVal("I10"            ,stBody.instID,sizeof(stBody.instID      )      );  
		pkt.GetParameterVal("M00"          ,stBody.memberID,sizeof(stBody.memberID    )    );  
		pkt.GetParameterVal("O61"         ,stBody.matchDate,sizeof(stBody.matchDate   )   );  
		pkt.GetParameterVal("O62"         ,stBody.matchTime,sizeof(stBody.matchTime   )   );  
		pkt.GetParameterVal("O63"             ,stBody.price     );  
		pkt.GetParameterVal("O64"            ,stBody.volume    );  
		pkt.GetParameterVal("I24"        ,stBody.marginRate );  
		pkt.GetParameterVal("I80"          ,stBody.rateType  );  
		pkt.GetParameterVal("O00"           ,stBody.orderNo,sizeof(stBody.orderNo     )     );  
		pkt.GetParameterVal("O01"      ,stBody.localOrderNo,sizeof(stBody.localOrderNo));     
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TForwardMatch& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O60"           ,stBody.matchNo         );  
		pkt.AddParameter("O02"         ,stBody.buyOrSell       );  
		pkt.AddParameter("M30"          ,stBody.clientID        );  
		pkt.AddParameter("M31"          ,stBody.clientType        );
		pkt.AddParameter("I10"            ,stBody.instID          );  
		pkt.AddParameter("M00"          ,stBody.memberID        );  
		pkt.AddParameter("O61"         ,stBody.matchDate       );  
		pkt.AddParameter("O62"         ,stBody.matchTime       );  
		pkt.AddParameter("O63"             ,stBody.price           );  
		pkt.AddParameter("O64"            ,stBody.volume          );  
		pkt.AddParameter("I24"        ,stBody.marginRate      );  
		pkt.AddParameter("I80"          ,stBody.rateType        );  
		pkt.AddParameter("O00"           ,stBody.orderNo         );  
		pkt.AddParameter("O01"      ,stBody.localOrderNo    );  
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferMatch& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O60"           ,stBody.matchNo,sizeof(stBody.matchNo     )     );
		pkt.GetParameterVal("O02"         ,stBody.buyOrSell );
		pkt.GetParameterVal("M30"          ,stBody.clientID,sizeof(stBody.clientID    )    );
		pkt.GetParameterVal("M31"          ,stBody.clientType );  
		pkt.GetParameterVal("I10"            ,stBody.instID,sizeof(stBody.instID      )      );
		pkt.GetParameterVal("M00"          ,stBody.memberID,sizeof(stBody.memberID    )    );
		pkt.GetParameterVal("O61"         ,stBody.matchDate,sizeof(stBody.matchDate   )   );
		pkt.GetParameterVal("O62"         ,stBody.matchTime,sizeof(stBody.matchTime   )   );
		pkt.GetParameterVal("O63"             ,stBody.price  );
		pkt.GetParameterVal("O64"            ,stBody.volume );
		pkt.GetParameterVal("O03"        ,stBody.offsetFlag );
		pkt.GetParameterVal("O00"           ,stBody.orderNo,sizeof(stBody.orderNo     )     );
		pkt.GetParameterVal("O01"      ,stBody.localOrderNo,sizeof(stBody.localOrderNo));   
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferMatch& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O60"           ,stBody.matchNo         );
		pkt.AddParameter("O02"         ,stBody.buyOrSell       );
		pkt.AddParameter("M30"          ,stBody.clientID        );
		pkt.AddParameter("M31"          ,stBody.clientType        );
		pkt.AddParameter("I10"            ,stBody.instID          );
		pkt.AddParameter("M00"          ,stBody.memberID        );
		pkt.AddParameter("O61"         ,stBody.matchDate       );
		pkt.AddParameter("O62"         ,stBody.matchTime       );
		pkt.AddParameter("O63"             ,stBody.price           );
		pkt.AddParameter("O64"            ,stBody.volume          );
		pkt.AddParameter("O03"        ,stBody.offsetFlag      );
		pkt.AddParameter("O00"           ,stBody.orderNo         );
		pkt.AddParameter("O01"      ,stBody.localOrderNo    );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onRecvRtnDeferDeliveryAppMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TDeferDeliveryAppMatch& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O60"           ,stBody.matchNo,sizeof(stBody.matchNo	    )     ); 
		pkt.GetParameterVal("M30"          ,stBody.clientID,sizeof(stBody.clientID    )    );
		pkt.GetParameterVal("I10"            ,stBody.instID,sizeof(stBody.instID      )      );
		pkt.GetParameterVal("M00"          ,stBody.memberID,sizeof(stBody.memberID    )    );
		pkt.GetParameterVal("O02"         ,stBody.buyOrSell );
		pkt.GetParameterVal("O64"            ,stBody.volume);
		pkt.GetParameterVal("O61"         ,stBody.matchDate,sizeof(stBody.matchDate   )   );
		pkt.GetParameterVal("O62"         ,stBody.matchTime,sizeof(stBody.matchTime   )   );
		pkt.GetParameterVal("O00"           ,stBody.orderNo,sizeof(stBody.orderNo     )     );
		pkt.GetParameterVal("O01"      ,stBody.localOrderNo,sizeof(stBody.localOrderNo));
		pkt.GetParameterVal("O05"        ,stBody.middleFlag      );
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TDeferDeliveryAppMatch& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O60"           ,stBody.matchNo	     ); 
		pkt.AddParameter("M30"          ,stBody.clientID        );
		pkt.AddParameter("I10"            ,stBody.instID          );
		pkt.AddParameter("M00"          ,stBody.memberID        );
		pkt.AddParameter("O02"         ,stBody.buyOrSell       );
		pkt.AddParameter("O64"            ,stBody.volume          );
		pkt.AddParameter("O61"         ,stBody.matchDate       );
		pkt.AddParameter("O62"         ,stBody.matchTime       );
		pkt.AddParameter("O00"           ,stBody.orderNo         );
		pkt.AddParameter("O01"      ,stBody.localOrderNo    );
		pkt.AddParameter("O05"        ,stBody.middleFlag      );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRspFpOrder] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TFpOrder& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O00"           ,stBody.OrderNo     	,sizeof(stBody.OrderNo     )); 
		pkt.GetParameterVal("O01"           ,stBody.LocalOrderNo	,sizeof(stBody.LocalOrderNo)); 
		pkt.GetParameterVal("M00"           ,stBody.MemberID    	,sizeof(stBody.MemberID    )); 
		pkt.GetParameterVal("M30"           ,stBody.AcctNo      	,sizeof(stBody.AcctNo      )); 
		pkt.GetParameterVal("I10"           ,stBody.ProdCode    	,sizeof(stBody.ProdCode    )); 
		pkt.GetParameterVal("O02"           ,stBody.Bs   ); 
		pkt.GetParameterVal("O15"           ,stBody.OrderType   	); 
		pkt.GetParameterVal("O07"           ,stBody.Amount); 
		pkt.GetParameterVal("T11"           ,stBody.ApplyDate   	,sizeof(stBody.ApplyDate   )); 
		pkt.GetParameterVal("T12"           ,stBody.ApplyTime   	,sizeof(stBody.ApplyTime   )); 
		pkt.GetParameterVal("Q47"           ,stBody.EntrPhase  ); 
		pkt.GetParameterVal("Q34"           ,stBody.GameID      	,sizeof(stBody.GameID      )); 
		pkt.GetParameterVal("Q41"           ,stBody.RoundID); 
		pkt.GetParameterVal("O06"           ,stBody.EntrPrice); 
		pkt.GetParameterVal("O09"           ,stBody.Status      ); 
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TFpOrder& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O00"           ,stBody.OrderNo     	        );  
		pkt.AddParameter("O01"           ,stBody.LocalOrderNo	        );  
		pkt.AddParameter("M00"           ,stBody.MemberID    	        );  
		pkt.AddParameter("M30"           ,stBody.AcctNo      	        ); 
		pkt.AddParameter("I10"           ,stBody.ProdCode    	        ); 
		pkt.AddParameter("O02"           ,stBody.Bs          	        ); 
		pkt.AddParameter("O15"           ,stBody.OrderType   	        ); 
		pkt.AddParameter("O07"           ,stBody.Amount      	        ); 
		pkt.AddParameter("T11"           ,stBody.ApplyDate   	        );    
		pkt.AddParameter("T12"           ,stBody.ApplyTime   	        ); 
		pkt.AddParameter("Q47"           ,stBody.EntrPhase   	        );  
		pkt.AddParameter("Q34"           ,stBody.GameID      	        );  
		pkt.AddParameter("Q41"           ,stBody.RoundID     	        );  
		pkt.AddParameter("O06"           ,stBody.EntrPrice   	        ); 
		pkt.AddParameter("O09"           ,stBody.Status      	        ); 
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRtnFpEntrStatistics] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TFpEntrStatistics& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("T13"           ,stBody.ExchDate  ,sizeof(stBody.ExchDate)  );  
		pkt.GetParameterVal("M00"           ,stBody.MemberID ,sizeof(stBody.MemberID) );  
		pkt.GetParameterVal("M30"           ,stBody.AcctNo    ,sizeof(stBody.AcctNo) );  
		pkt.GetParameterVal("I10"           ,stBody.ProdCode  ,sizeof(stBody.ProdCode)  ); 
		pkt.GetParameterVal("Q34"           ,stBody.GameID    ,sizeof(stBody.GameID)); 
		pkt.GetParameterVal("O06"           ,stBody.Price           	        ); 
		pkt.GetParameterVal("H02"           ,stBody.MrBuyAmount     	        ); 
		pkt.GetParameterVal("H12"           ,stBody.MrSellAmount    	        ); 
		pkt.GetParameterVal("H04"           ,stBody.FrBuyAmount     	        );    
		pkt.GetParameterVal("H14"           ,stBody.FrSellAmount    	        ); 
		pkt.GetParameterVal("H06"           ,stBody.LrMrBuyAmount   	        );  
		pkt.GetParameterVal("H16"           ,stBody.LrMrSellAmount  	        );  
		pkt.GetParameterVal("H08"           ,stBody.LrFrBuyAmount   	        );  
		pkt.GetParameterVal("H18"           ,stBody.LrFrSellAmount  	        ); 
		pkt.GetParameterVal("Q18"           ,stBody.LrPrice         	        ); 
		pkt.GetParameterVal("F15"           ,stBody.FrozBuyMargin   	        ); 
		pkt.GetParameterVal("F16"           ,stBody.FrozSellMargin  	        ); 
		pkt.GetParameterVal("F17"           ,stBody.FrozBuyExchFare 	        ); 
		pkt.GetParameterVal("F18"           ,stBody.FrozSellExchFare	        ); 
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TFpEntrStatistics& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("T13"           ,stBody.ExchDate        	        );  
		pkt.AddParameter("M00"           ,stBody.MemberID        	        );  
		pkt.AddParameter("M30"           ,stBody.AcctNo          	        );  
		pkt.AddParameter("I10"           ,stBody.ProdCode        	        ); 
		pkt.AddParameter("Q34"           ,stBody.GameID          	        ); 
		pkt.AddParameter("O06"           ,stBody.Price           	        ); 
		pkt.AddParameter("H02"           ,stBody.MrBuyAmount     	        ); 
		pkt.AddParameter("H12"           ,stBody.MrSellAmount    	        ); 
		pkt.AddParameter("H04"           ,stBody.FrBuyAmount     	        );    
		pkt.AddParameter("H14"           ,stBody.FrSellAmount    	        ); 
		pkt.AddParameter("H06"           ,stBody.LrMrBuyAmount   	        );  
		pkt.AddParameter("H16"           ,stBody.LrMrSellAmount  	        );  
		pkt.AddParameter("H08"           ,stBody.LrFrBuyAmount   	        );  
		pkt.AddParameter("H18"           ,stBody.LrFrSellAmount  	        ); 
		pkt.AddParameter("Q18"           ,stBody.LrPrice         	        ); 
		pkt.AddParameter("F15"           ,stBody.FrozBuyMargin   	        ); 
		pkt.AddParameter("F16"           ,stBody.FrozSellMargin  	        ); 
		pkt.AddParameter("F17"           ,stBody.FrozBuyExchFare 	        ); 
		pkt.AddParameter("F18"           ,stBody.FrozSellExchFare	        ); 
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRtnFpMatch] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TFpMatch& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("O60"           ,stBody.MatchNo    ,sizeof(stBody.MatchNo    ));  
		pkt.GetParameterVal("O61"           ,stBody.MatchDate  ,sizeof(stBody.MatchDate  ));  
		pkt.GetParameterVal("I23"           ,stBody.DeliDate   ,sizeof(stBody.DeliDate   ));  
		pkt.GetParameterVal("Q34"           ,stBody.MatchGame  ,sizeof(stBody.MatchGame  ));  
		pkt.GetParameterVal("Q41"           ,stBody.MatchRound);  
		pkt.GetParameterVal("M00"           ,stBody.MemberID   ,sizeof(stBody.MemberID   ));  
		pkt.GetParameterVal("M30"           ,stBody.AcctNo     ,sizeof(stBody.AcctNo     ));  
		pkt.GetParameterVal("I10"           ,stBody.ProdCode   ,sizeof(stBody.ProdCode   ));  
		pkt.GetParameterVal("O02"           ,stBody.Bs         );  
		pkt.GetParameterVal("O63"           ,stBody.MatchPrice );  
		pkt.GetParameterVal("O64"           ,stBody.MatchAmount);  
		pkt.GetParameterVal("Q47"           ,stBody.EntrPhase );  
		pkt.GetParameterVal("O22"           ,stBody.IsAllocate );  
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TFpMatch& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("O60"           ,stBody.MatchNo    	        ); 
		pkt.AddParameter("O61"           ,stBody.MatchDate  	        ); 
		pkt.AddParameter("I23"           ,stBody.DeliDate   	        ); 
		pkt.AddParameter("Q34"           ,stBody.MatchGame  	        ); 
		pkt.AddParameter("Q41"           ,stBody.MatchRound 	        ); 
		pkt.AddParameter("M00"           ,stBody.MemberID   	        ); 
		pkt.AddParameter("M30"           ,stBody.AcctNo     	        ); 
		pkt.AddParameter("I10"           ,stBody.ProdCode   	        ); 
		pkt.AddParameter("O02"           ,stBody.Bs         	        ); 
		pkt.AddParameter("O63"           ,stBody.MatchPrice 	        ); 
		pkt.AddParameter("O64"           ,stBody.MatchAmount	        ); 
		pkt.AddParameter("Q47"           ,stBody.EntrPhase  	        ); 
		pkt.AddParameter("O22"           ,stBody.IsAllocate 	        ); 
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRspFpOrderCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TFpOrderCancel& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("M00"           ,stBody.MemberID    ,sizeof(stBody.MemberID)	        ); 
		pkt.GetParameterVal("M30"           ,stBody.AcctNo      ,sizeof(stBody.AcctNo)	        ); 
		pkt.GetParameterVal("I10"           ,stBody.ProdCode    ,sizeof(stBody.ProdCode)	        ); 
		pkt.GetParameterVal("Q47"           ,stBody.EntrPhase         ); 
		pkt.GetParameterVal("O02"           ,stBody.Bs          ); 
		pkt.GetParameterVal("O07"           ,stBody.CancelAmount ); 
		pkt.GetParameterVal("Q34"           ,stBody.GameID      ,sizeof(stBody.GameID)	        ); 
		pkt.GetParameterVal("Q41"           ,stBody.RoundID     	        ); 
		pkt.GetParameterVal("O09"           ,stBody.Status           ); 
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	} 

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TFpOrderCancel& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("M00"           ,stBody.MemberID    	        ); 
		pkt.AddParameter("M30"           ,stBody.AcctNo      	        ); 
		pkt.AddParameter("I10"           ,stBody.ProdCode    	        ); 
		pkt.AddParameter("Q47"           ,stBody.EntrPhase   	        ); 
		pkt.AddParameter("O02"           ,stBody.Bs          	        ); 
		pkt.AddParameter("O07"           ,stBody.CancelAmount	        ); 
		pkt.AddParameter("Q34"           ,stBody.GameID      	        ); 
		pkt.AddParameter("Q41"           ,stBody.RoundID     	        ); 
		pkt.AddParameter("O09"           ,stBody.Status      	        ); 
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);
		return 0;
	}

	//----------------------------------------------报文接口 [onRecvRspFpOrderFullCancel] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TFpOrderFullCancel& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("Q34"           ,stBody.GameID       ,sizeof(stBody.GameID)	        );
		pkt.GetParameterVal("Q41"           ,stBody.RoundID        );
		pkt.GetParameterVal("I10"           ,stBody.ProdCode     ,sizeof(stBody.ProdCode)	        );
		pkt.GetParameterVal("O02"           ,stBody.Bs                 );
		pkt.GetParameterVal("O23"           ,stBody.NeedCancel     );
		pkt.GetParameterVal("O06"           ,stBody.NewRoundPrice	        );
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TFpOrderFullCancel& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("Q34"           ,stBody.GameID       	        );
		pkt.AddParameter("Q41"           ,stBody.RoundID      	        );
		pkt.AddParameter("I10"           ,stBody.ProdCode     	        );
		pkt.AddParameter("O02"           ,stBody.Bs           	        );
		pkt.AddParameter("O23"           ,stBody.NeedCancel   	        );
		pkt.AddParameter("O06"           ,stBody.NewRoundPrice	        );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);
		return 0;
	}


	//----------------------------------------------报文接口 [onSysInit] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSysInit& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("T25",         stBody.old_exch_date    ,sizeof(stBody.old_exch_date) );
		pkt.GetParameterVal("T26",        stBody.new_exch_date    ,sizeof(stBody.new_exch_date) );
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSysInit& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("T25",        stBody.old_exch_date     );
		pkt.AddParameter("T26",        stBody.new_exch_date     );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onSysStatChange] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TSysStat& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("T16",         stBody.sys_date  ,sizeof(stBody.sys_date)   ); 
		pkt.GetParameterVal("T13",        stBody.exch_date   ,sizeof(stBody.exch_date) ); 
		pkt.GetParameterVal("G02",       stBody.m_sys_stat   ); 
		pkt.GetParameterVal("G01",       stBody.b_sys_stat   ); 
		pkt.GetParameterVal("X05"		,stBody.sequence_no  ,sizeof(stBody.sequence_no)   );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TSysStat& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("T16",         stBody.sys_date     );
		pkt.AddParameter("T13",        stBody.exch_date    );
		pkt.AddParameter("G02",       stBody.m_sys_stat   );
		pkt.AddParameter("G01",       stBody.b_sys_stat   );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onNewMemberBulletin] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TNewMemberBulletin& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("T80",        stBody.bulletin_id    ,sizeof(stBody.bulletin_id) );
		pkt.GetParameterVal("Q84",              stBody.title      ,sizeof(stBody.title)     );
		pkt.GetParameterVal("X05"		,stBody.sequence_no ,sizeof(stBody.sequence_no)    );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TNewMemberBulletin& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("T80",        stBody.bulletin_id     );
		pkt.AddParameter("Q84",              stBody.title           );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [onCustOpenCheck] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( TCustOpenCheck& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("M00"         ,stBody.member_id   ,sizeof(stBody.member_id)    );
		pkt.GetParameterVal("B22"      ,stBody.cert_type_id   );
		pkt.GetParameterVal("B23"          ,stBody.cert_num    ,sizeof(stBody.cert_num)    );
		pkt.GetParameterVal("M30"           ,stBody.cust_id     ,sizeof(stBody.cust_id)    );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//应答报文编码: 结构 -> 报文  
	static int Struct2Packet( TCustOpenCheck& stBody, CGtpPacket& pkt)
	{
		pkt.AddParameter("M00"         ,stBody.member_id       );
		pkt.AddParameter("B01"      ,stBody.cert_type_id    );
		pkt.AddParameter("B02"          ,stBody.cert_num        );
		pkt.AddParameter("M30"           ,stBody.cust_id         );
		pkt.AddParameter("X05"		 ,stBody.sequence_no     );
		pkt.AddParameter("X04" ,stBody.sequence_seriesno);

		return 0;
	}


	//----------------------------------------------报文接口 [on0x00A00123] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( T0x00A00123& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("M00"         ,stBody.memberID      ,sizeof(stBody.memberID   )    );
		pkt.GetParameterVal("T13"         ,stBody.effectDate    ,sizeof(stBody.effectDate )    );
		pkt.GetParameterVal("T81"         ,stBody.seqNo         ,sizeof(stBody.seqNo      )    );
		pkt.GetParameterVal("K04"         ,stBody.sheetNo       ,sizeof(stBody.sheetNo    )    );
		pkt.GetParameterVal("M30"         ,stBody.clientID      ,sizeof(stBody.clientID   )    );
		pkt.GetParameterVal("A01"         ,stBody.accountType   );
		pkt.GetParameterVal("K01"         ,stBody.transType     ,sizeof(stBody.transType  )    );
		pkt.GetParameterVal("V00"         ,stBody.varietyID     ,sizeof(stBody.varietyID  )    );
		pkt.GetParameterVal("W00"         ,stBody.warehouseID   ,sizeof(stBody.warehouseID)    );
		pkt.GetParameterVal("T52"         ,stBody.stdStorage );
		pkt.GetParameterVal("T50"         ,stBody.totalStore   );
		pkt.GetParameterVal("S16"         ,stBody.sumStore     );
		pkt.GetParameterVal("T16"         ,stBody.transDate     ,sizeof(stBody.transDate  )    );
		pkt.GetParameterVal("T17"         ,stBody.transTime     ,sizeof(stBody.transTime  )    );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//----------------------------------------------报文接口 [on0x00A00202] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( T0x00A00202& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("K20"         ,stBody.pickupSheetNo    ,sizeof(stBody.pickupSheetNo )    );
		pkt.GetParameterVal("T13"         ,stBody.applyDate        ,sizeof(stBody.applyDate     )    );
		pkt.GetParameterVal("T15"         ,stBody.applyTransDate   ,sizeof(stBody.applyTransDate)    );
		pkt.GetParameterVal("M00"         ,stBody.memberID         ,sizeof(stBody.memberID      )    );
		pkt.GetParameterVal("K00"         ,stBody.localNo          ,sizeof(stBody.localNo       )    );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//----------------------------------------------报文接口 [on0x00A00212] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( T0x00A00212& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("K20"          ,stBody.pickupSheetNo    ,sizeof(stBody.pickupSheetNo)    );
		pkt.GetParameterVal("M00"           ,stBody.memberID     ,sizeof(stBody.memberID)    );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//----------------------------------------------报文接口 [on0x00A00222] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( T0x00A00222& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("K20"         ,stBody.SheetNo           ,sizeof(stBody.SheetNo        )    );
		pkt.GetParameterVal("K00"         ,stBody.localNo           ,sizeof(stBody.localNo        )    );
		pkt.GetParameterVal("M00"         ,stBody.memberID          ,sizeof(stBody.memberID       )    );
		pkt.GetParameterVal("M30"         ,stBody.clientID          ,sizeof(stBody.clientID       )    );
		pkt.GetParameterVal("W00"         ,stBody.warehouseID       ,sizeof(stBody.warehouseID    )    );
		pkt.GetParameterVal("K22"         ,stBody.pickupPerson      ,sizeof(stBody.pickupPerson   )    );
		pkt.GetParameterVal("K23"         ,stBody.cipher            ,sizeof(stBody.cipher         )    );
		pkt.GetParameterVal("B01"         ,stBody.certificateType  );
		pkt.GetParameterVal("B02"         ,stBody.certificateNo     ,sizeof(stBody.certificateNo  )    );
		pkt.GetParameterVal("T13"         ,stBody.applyDate         ,sizeof(stBody.applyDate      )    );
		pkt.GetParameterVal("T18"         ,stBody.beginDate         ,sizeof(stBody.beginDate      )    );
		pkt.GetParameterVal("T19"         ,stBody.endDate           ,sizeof(stBody.endDate        )    );
		pkt.GetParameterVal("T15"         ,stBody.applyTransDate    ,sizeof(stBody.applyTransDate )    );
		pkt.GetParameterVal("M60"         ,stBody.traderID          ,sizeof(stBody.traderID       )    );
		pkt.GetParameterVal("T51"         ,stBody.stdDrawWeight     );
		pkt.GetParameterVal("V00"         ,stBody.varietyID         ,sizeof(stBody.varietyID      )    );
		pkt.GetParameterVal("K24"         ,stBody.selfDrawWeight      );
		pkt.GetParameterVal("K25"         ,stBody.tradeDrawWeight    );
		pkt.GetParameterVal("K21"         ,stBody.drawType          );
		pkt.GetParameterVal("K60"         ,stBody.leaseRegNo        ,sizeof(stBody.leaseRegNo     )    );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

	//----------------------------------------------报文接口 [on0x00A00223] 报文结构编解码
	//请求报文解码: 报文 -> 结构  
	static int Packet2Struct( T0x00A00223& stBody, CGtpPacket& pkt)
	{
		pkt.GetParameterVal("M00"       ,stBody.memberID     ,sizeof(stBody.memberID  )    );
		pkt.GetParameterVal("T13"       ,stBody.effectDate   ,sizeof(stBody.effectDate)    );
		pkt.GetParameterVal("T80"       ,stBody.seqNo        ,sizeof(stBody.seqNo     )    );
		pkt.GetParameterVal("M30"       ,stBody.clientID     ,sizeof(stBody.clientID  )    );
		pkt.GetParameterVal("K20"       ,stBody.SheetNo      ,sizeof(stBody.SheetNo   )    );
		pkt.GetParameterVal("K03"       ,stBody.appSheetNo   ,sizeof(stBody.appSheetNo)    );
		pkt.GetParameterVal("K00"       ,stBody.localNo      ,sizeof(stBody.localNo   )    );
		pkt.GetParameterVal("K02"       ,stBody.stgOptType   ,sizeof(stBody.stgOptType)    );
		pkt.GetParameterVal("K04"       ,stBody.appState     );
		pkt.GetParameterVal("X05"		,stBody.sequence_no   ,sizeof(stBody.sequence_no)  );
		pkt.GetParameterVal("X04" ,stBody.sequence_seriesno);

		return 0;
	}

};
#endif
