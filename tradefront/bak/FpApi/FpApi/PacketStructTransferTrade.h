#ifndef _PACKET_STRUCT_TRANSFER_TRADE_H                 
#define _PACKET_STRUCT_TRANSFER_TRADE_H  

#include "ApiStruct.h"
#include "TradePacket.h"

class CPacketStructTrade
{
public:
	//----------------------------------------------响应码报文结构编解码
	// 结构 -> 报文 
	static int Packet2Struct( TRspMsg& stBody, CTradePacket& pkt)
	{
		//pkt.GetParameterVal("rsp_msg"         stBody.rsp_msg     );  
		//pkt.GetParameterVal("rsp_code"        stBody.rsp_code    );  
		HEADER_RSP tHead;
		pkt.GetHeader(tHead);
		stBody.rsp_msg = tHead.rsp_msg;
		stBody.rsp_code = tHead.rsp_code;
		stBody.rsp_code = trim(stBody.rsp_code);
		stBody.rsp_msg = trim(stBody.rsp_msg);
		return 0;
	}


	//----------------------------------------------报文接口 [6101] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTradeLogin& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        ,stBody.oper_flag    );  
		pkt.AddParameter("teller_id"        ,stBody.teller_id    );  
		pkt.AddParameter("member_id"        ,stBody.member_id    );  
		pkt.AddParameter("password"         ,stBody.password     );  
		pkt.AddParameter("key"              ,stBody.key          );  
		pkt.AddParameter("iv"               ,stBody.iv           );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTradeLogin& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          ,stBody.oper_flag);
		pkt.GetParameterVal("exch_date"          ,stBody.exch_date);
		return 0;
	}


	//----------------------------------------------报文接口 [6102] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTradeLogout& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        ,stBody.oper_flag    );  
		pkt.AddParameter("teller_id"        ,stBody.teller_id    );  
		pkt.AddParameter("member_id"        ,stBody.member_id    );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTradeLogout& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          ,stBody.oper_flag);
		return 0;
	}


	//----------------------------------------------报文接口 [6103] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqHello& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"          ,stBody.oper_flag);
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TReqHello& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"          ,stBody.oper_flag);
		return 0;
	}
	//----------------------------------------------报文接口 [6202] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqPreOpenAccountLegal& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"                     ,stBody.oper_flag                   );  
		pkt.AddParameter("member_id"                     ,stBody.member_id                   );
		pkt.AddParameter("gess_branch_id"                ,stBody.gess_branch_id              );
		pkt.AddParameter("acct_type"                     ,stBody.acct_type                   );
		pkt.AddParameter("gess_grade_id"                 ,stBody.gess_grade_id               );
		pkt.AddParameter("settle_bank_no"                ,stBody.settle_bank_no              );
		pkt.AddParameter("account_no"                    ,stBody.account_no                  );
		pkt.AddParameter("account_name"                  ,stBody.account_name                );
		pkt.AddParameter("open_account_date"             ,stBody.open_account_date           );
		pkt.AddParameter("account_due_date"              ,stBody.account_due_date            );
		pkt.AddParameter("corp_en_name"                  ,stBody.corp_en_name                );
		pkt.AddParameter("corp_chn_name"                 ,stBody.corp_chn_name               );
		pkt.AddParameter("corp_en_abbr"                  ,stBody.corp_en_abbr                );
		pkt.AddParameter("corp_chn_abbr"                 ,stBody.corp_chn_abbr               );
		pkt.AddParameter("corp_prop_id"                  ,stBody.corp_prop_id                );
		pkt.AddParameter("corp_code"                     ,stBody.corp_code                   );
		pkt.AddParameter("cert_type"                     ,stBody.cert_type                   );
		pkt.AddParameter("cert_num"                      ,stBody.cert_num                    );
		pkt.AddParameter("contacter"                     ,stBody.contacter                   );
		pkt.AddParameter("mobile_phone"                  ,stBody.mobile_phone                );
		pkt.AddParameter("regist_addr"                   ,stBody.regist_addr                 );
		pkt.AddParameter("reg_capital"                   ,stBody.reg_capital                 );
		pkt.AddParameter("org_type"                      ,stBody.org_type                    );
		pkt.AddParameter("corp_zip"                      ,stBody.corp_zip                    );
		pkt.AddParameter("corp_tel"                      ,stBody.corp_tel                    );
		pkt.AddParameter("corp_fax"                      ,stBody.corp_fax                    );
		pkt.AddParameter("corp_email"                    ,stBody.corp_email                  );
		pkt.AddParameter("pawnee_flag"                   ,stBody.pawnee_flag                 );
		pkt.AddParameter("corp_regist_addr"              ,stBody.corp_regist_addr            );
		pkt.AddParameter("copr_authorizer"               ,stBody.copr_authorizer             );
		pkt.AddParameter("auth_nationality"              ,stBody.auth_nationality            );
		pkt.AddParameter("auth_cert_type_id"             ,stBody.auth_cert_type_id           );
		pkt.AddParameter("auth_cert_no"                  ,stBody.auth_cert_no                );
		pkt.AddParameter("auth_addr"                     ,stBody.auth_addr                   );
		pkt.AddParameter("auth_zip"                      ,stBody.auth_zip                    );
		pkt.AddParameter("auth_tel"                      ,stBody.auth_tel                    );
		pkt.AddParameter("auth_fax"                      ,stBody.auth_fax                    );
		pkt.AddParameter("auth_email"                    ,stBody.auth_email                  );
		pkt.AddParameter("busi_license"                  ,stBody.busi_license                );
		pkt.AddParameter("tax_cert"                      ,stBody.tax_cert                    );
		pkt.AddParameter("org_code_cert"                 ,stBody.org_code_cert               );
		pkt.AddParameter("regist_address"                ,stBody.regist_address              );
		pkt.AddParameter("sigex_post_code"               ,stBody.sigex_post_code             );
		pkt.AddParameter("sigex_tel"                     ,stBody.sigex_tel                   );
		pkt.AddParameter("sigex_fax"                     ,stBody.sigex_fax                   );
		pkt.AddParameter("sigex_email"                   ,stBody.sigex_email                 );
		pkt.AddParameter("cust_id"                       ,stBody.cust_id                     );
		pkt.AddParameter("gess_broker_id"                ,stBody.gess_broker_id              );
		pkt.AddParameter("exec_name"                     ,stBody.exec_name                   );
		pkt.AddParameter("exec_tel"                      ,stBody.exec_tel                    );
		pkt.AddParameter("exec_cert_type_id"             ,stBody.exec_cert_type_id           );
		pkt.AddParameter("exec_cert_num"                 ,stBody.exec_cert_num               );
		pkt.AddParameter("taxpayer_identifier"           ,stBody.taxpayer_identifier         );
		pkt.AddParameter("is_val_added_taxplayer"        ,stBody.is_val_added_taxplayer      );
		pkt.AddParameter("taxplayer_address"             ,stBody.taxplayer_address           );
		pkt.AddParameter("taxpayer_telephone"            ,stBody.taxpayer_telephone          );
		pkt.AddParameter("taxpayer_bankcode"             ,stBody.taxpayer_bankcode           );
		pkt.AddParameter("taxpayer_bankinfo"             ,stBody.taxpayer_bankinfo           );
		pkt.AddParameter("taxpayer_account_id"           ,stBody.taxpayer_account_id         );
		pkt.AddParameter("memo"                          ,stBody.memo                        );
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspPreOpenAccountLegal& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"                     ,stBody.oper_flag                   );  
		return 0;
	}


	//----------------------------------------------报文接口 [6203] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqOpenAccountPersonal& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"             ,stBody.oper_flag           );
		pkt.AddParameter("cust_id"               ,stBody.cust_id             );
		pkt.AddParameter("member_id"             ,stBody.member_id           );
		pkt.AddParameter("account_no"            ,stBody.account_no          );
		pkt.AddParameter("account_name"          ,stBody.account_name        );
		pkt.AddParameter("open_account_date"     ,stBody.open_account_date   );
		pkt.AddParameter("account_due_date"      ,stBody.account_due_date    );
		pkt.AddParameter("cert_type_id"          ,stBody.cert_type_id        );
		pkt.AddParameter("cert_num"              ,stBody.cert_num            );
		pkt.AddParameter("gess_branch_id"        ,stBody.gess_branch_id      );
		pkt.AddParameter("gess_broker_id"        ,stBody.gess_broker_id      );
		pkt.AddParameter("gess_grade_id"         ,stBody.gess_grade_id       );
		pkt.AddParameter("mobile_phone"          ,stBody.mobile_phone        );
		pkt.AddParameter("tel"                   ,stBody.tel                 );
		pkt.AddParameter("addr"                  ,stBody.addr                );
		pkt.AddParameter("zipcode"               ,stBody.zipcode             );
		pkt.AddParameter("email"                 ,stBody.email               );
		pkt.AddParameter("settle_bank_no"        ,stBody.settle_bank_no      );
		pkt.AddParameter("nationality"           ,stBody.nationality         );
		pkt.AddParameter("birthday"              ,stBody.birthday            );
		pkt.AddParameter("first_name"            ,stBody.first_name          );
		pkt.AddParameter("last_name"             ,stBody.last_name           );
		pkt.AddParameter("middle_name"           ,stBody.middle_name         );
		pkt.AddParameter("cert_open_date"        ,stBody.cert_open_date      );
		pkt.AddParameter("cert_due_date"         ,stBody.cert_due_date       );
		pkt.AddParameter("memo"                  ,stBody.memo                );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspOpenAccountPersonal& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag           );
		pkt.GetParameterVal("cust_id"               ,stBody.cust_id             );

		return 0;
	}


	//----------------------------------------------报文接口 [6205] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqModifyBankAcctBind& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         ,stBody.oper_flag       );
		pkt.AddParameter("cust_id"           ,stBody.cust_id         );
		pkt.AddParameter("acct_type"         ,stBody.acct_type       );
		pkt.AddParameter("cert_type_id"      ,stBody.cert_type_id    );
		pkt.AddParameter("cert_num"          ,stBody.cert_num        );
		pkt.AddParameter("new_account_no"    ,stBody.new_account_no  );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspModifyBankAcctBind& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"            ,stBody.oper_flag   );  
		return 0;
	}

	//----------------------------------------------报文接口 [6207] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqCancelAccount& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"             ,stBody.oper_flag           );
		pkt.AddParameter("cust_id"               ,stBody.cust_id             );
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspCancelAccount& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"            ,stBody.oper_flag   );  
		return 0;
	}

	//----------------------------------------------报文接口 [6208] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqModifyAcctInfoPersonal& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        ,stBody.oper_flag         ); 
		pkt.AddParameter("cust_id"          ,stBody.cust_id           );
		pkt.AddParameter("nationality"      ,stBody.nationality       );
		pkt.AddParameter("birthday"         ,stBody.birthday          );
		pkt.AddParameter("first_name"       ,stBody.first_name        );
		pkt.AddParameter("last_name"        ,stBody.last_name         );
		pkt.AddParameter("middle_name"      ,stBody.middle_name       );
		pkt.AddParameter("cert_open_date"   ,stBody.cert_open_date    );
		pkt.AddParameter("cert_due_date"    ,stBody.cert_due_date     );
		pkt.AddParameter("mobile_phone"     ,stBody.mobile_phone      );
		pkt.AddParameter("tel"              ,stBody.tel               );
		pkt.AddParameter("addr"             ,stBody.addr              );
		pkt.AddParameter("zipcode"          ,stBody.zipcode           );
		pkt.AddParameter("email"            ,stBody.email             );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspModifyAcctInfoPersonal& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"            ,stBody.oper_flag   ); 
		return 0;
	}

	//----------------------------------------------报文接口 [6209] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqModifyAcctInfoLegal& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"                 ,stBody.oper_flag                );       
		pkt.AddParameter("cust_id"                   ,stBody.cust_id                  );
		pkt.AddParameter("corp_en_name"              ,stBody.corp_en_name             );
		pkt.AddParameter("corp_chn_name"             ,stBody.corp_chn_name            );
		pkt.AddParameter("corp_en_abbr"              ,stBody.corp_en_abbr             );
		pkt.AddParameter("corp_chn_abbr"             ,stBody.corp_chn_abbr            );
		pkt.AddParameter("regist_addr"               ,stBody.regist_addr              );
		pkt.AddParameter("cert_type"                 ,stBody.cert_type                );
		pkt.AddParameter("cert_num"                  ,stBody.cert_num                 );
		pkt.AddParameter("corp_prop_id"              ,stBody.corp_prop_id             );
		pkt.AddParameter("corp_code"                 ,stBody.corp_code                );
		pkt.AddParameter("contacter"                 ,stBody.contacter                );
		pkt.AddParameter("mobile_phone"              ,stBody.mobile_phone             );
		pkt.AddParameter("org_type"                  ,stBody.org_type                 );
		pkt.AddParameter("reg_capital"               ,stBody.reg_capital              );
		pkt.AddParameter("pawnee_flag"               ,stBody.pawnee_flag              );
		pkt.AddParameter("corp_regist_addr"          ,stBody.corp_regist_addr         );
		pkt.AddParameter("corp_zip"                  ,stBody.corp_zip                 );
		pkt.AddParameter("corp_tel"                  ,stBody.corp_tel                 );
		pkt.AddParameter("corp_fax"                  ,stBody.corp_fax                 );
		pkt.AddParameter("corp_email"                ,stBody.corp_email               );
		pkt.AddParameter("copr_authorizer"           ,stBody.copr_authorizer          );
		pkt.AddParameter("auth_nationality"          ,stBody.auth_nationality         );
		pkt.AddParameter("auth_cert_type_id"         ,stBody.auth_cert_type_id        );
		pkt.AddParameter("auth_cert_no"              ,stBody.auth_cert_no             );
		pkt.AddParameter("auth_addr"                 ,stBody.auth_addr                );
		pkt.AddParameter("auth_zip"                  ,stBody.auth_zip                 );
		pkt.AddParameter("auth_tel"                  ,stBody.auth_tel                 );
		pkt.AddParameter("auth_fax"                  ,stBody.auth_fax                 );
		pkt.AddParameter("auth_email"                ,stBody.auth_email               );
		pkt.AddParameter("busi_license"              ,stBody.busi_license             );
		pkt.AddParameter("tax_cert"                  ,stBody.tax_cert                 );
		pkt.AddParameter("org_code_cert"             ,stBody.org_code_cert            );
		pkt.AddParameter("regist_address"            ,stBody.regist_address           );
		pkt.AddParameter("sigex_post_code"           ,stBody.sigex_post_code          );
		pkt.AddParameter("sigex_tel"                 ,stBody.sigex_tel                );
		pkt.AddParameter("sigex_fax"                 ,stBody.sigex_fax                );
		pkt.AddParameter("sigex_email"               ,stBody.sigex_email              );
		pkt.AddParameter("exec_name"                 ,stBody.exec_name                );
		pkt.AddParameter("exec_tel"                  ,stBody.exec_tel                 );
		pkt.AddParameter("exec_cert_no"              ,stBody.exec_cert_no             );
		pkt.AddParameter("exec_cert_type_id"         ,stBody.exec_cert_type_id        );
		pkt.AddParameter("taxpayer_identifier"       ,stBody.taxpayer_identifier      );
		pkt.AddParameter("is_val_added_taxplayer"    ,stBody.is_val_added_taxplayer   );
		pkt.AddParameter("taxplayer_address"         ,stBody.taxplayer_address        );
		pkt.AddParameter("taxpayer_telephone"        ,stBody.taxpayer_telephone       );
		pkt.AddParameter("taxpayer_bankcode"         ,stBody.taxpayer_bankcode        );
		pkt.AddParameter("taxpayer_bankinfo"         ,stBody.taxpayer_bankinfo        );
		pkt.AddParameter("taxpayer_account_id"       ,stBody.taxpayer_account_id      );
		pkt.AddParameter("memo"                      ,stBody.memo                     );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspModifyAcctInfoLegal& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"            ,stBody.oper_flag   ); 
		return 0;
	}

	//----------------------------------------------报文接口 [6210] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqMemberFareModelChange& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"             ,stBody.oper_flag           );
		pkt.AddParameter("cust_id"               ,stBody.cust_id             );
		pkt.AddParameter("gesas_fare_mode_id"    ,stBody.gesas_fare_mode_id  );
		
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspMemberFareModelChange& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"            ,stBody.oper_flag   ); 
		return 0;
	}

	//----------------------------------------------报文接口 [6211] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryAcctInfoPersonal& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         ,stBody.oper_flag       );  
		pkt.AddParameter("query_flag"        ,stBody.query_flag      );  
		pkt.AddParameter("account_no"        ,stBody.account_no      );  
		pkt.AddParameter("member_id"         ,stBody.member_id       );  
		pkt.AddParameter("cert_type_id"      ,stBody.cert_type_id    );  
		pkt.AddParameter("cert_num"          ,stBody.cert_num        );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryAcctInfoPersonal& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag           );
		pkt.GetParameterVal("cust_id"               ,stBody.cust_id             );
		pkt.GetParameterVal("member_id"             ,stBody.member_id           );
		pkt.GetParameterVal("settle_bank_no"        ,stBody.settle_bank_no      );
		pkt.GetParameterVal("account_no"            ,stBody.account_no          );
		pkt.GetParameterVal("account_name"          ,stBody.account_name        );
		pkt.GetParameterVal("open_account_date"     ,stBody.open_account_date   );
		pkt.GetParameterVal("account_due_date"      ,stBody.account_due_date    );
		pkt.GetParameterVal("cert_type_id"          ,stBody.cert_type_id        );
		pkt.GetParameterVal("cert_num"              ,stBody.cert_num            );
		pkt.GetParameterVal("gess_fare_mode_id"     ,stBody.gess_fare_mode_id   );
		pkt.GetParameterVal("gesas_fare_mode_id"    ,stBody.gesas_fare_mode_id  );
		pkt.GetParameterVal("gess_broker_id"        ,stBody.gess_broker_id      );
		pkt.GetParameterVal("grade_id"              ,stBody.grade_id            );
		pkt.GetParameterVal("mobile_phone"          ,stBody.mobile_phone        );
		pkt.GetParameterVal("tel"                   ,stBody.tel                 );
		pkt.GetParameterVal("addr"                  ,stBody.addr                );
		pkt.GetParameterVal("zipcode"               ,stBody.zipcode             );
		pkt.GetParameterVal("email"                 ,stBody.email               );
		pkt.GetParameterVal("nationality"           ,stBody.nationality         );
		pkt.GetParameterVal("birthday"              ,stBody.birthday            );
		pkt.GetParameterVal("first_name"            ,stBody.first_name          );
		pkt.GetParameterVal("last_name"             ,stBody.last_name           );
		pkt.GetParameterVal("middle_name"           ,stBody.middle_name         );
		pkt.GetParameterVal("cert_open_date"        ,stBody.cert_open_date      );
		pkt.GetParameterVal("cert_due_date"         ,stBody.cert_due_date       );
		pkt.GetParameterVal("acct_stat"             ,stBody.acct_stat           );
		pkt.GetParameterVal("memo"                  ,stBody.memo                );
		return 0;
	}

	//----------------------------------------------报文接口 [6212] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryAcctInfoLegal& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"         ,stBody.oper_flag       );  
		pkt.AddParameter("query_flag"        ,stBody.query_flag      );  
		pkt.AddParameter("account_no"        ,stBody.account_no      );  
		pkt.AddParameter("member_id"         ,stBody.member_id       );  
		pkt.AddParameter("cert_type_id"      ,stBody.cert_type_id    );  
		pkt.AddParameter("cert_num"          ,stBody.cert_num        ); 
		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryAcctInfoLegal& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"              ,stBody.oper_flag               );  
		pkt.GetParameterVal("corp_en_name"           ,stBody.corp_en_name           );
		pkt.GetParameterVal("corp_chn_name"          ,stBody.corp_chn_name          );
		pkt.GetParameterVal("corp_en_abbr"           ,stBody.corp_en_abbr           );
		pkt.GetParameterVal("corp_chn_abbr"          ,stBody.corp_chn_abbr          );
		pkt.GetParameterVal("settle_bank_no"         ,stBody.settle_bank_no          );
		pkt.GetParameterVal("account_no"             ,stBody.account_no              );
		pkt.GetParameterVal("account_name"           ,stBody.account_name            );
		pkt.GetParameterVal("open_account_date"      ,stBody.open_account_date       );
		pkt.GetParameterVal("account_due_date"       ,stBody.account_due_date        );
		pkt.GetParameterVal("regist_addr"            ,stBody.regist_addr             );
		pkt.GetParameterVal("cert_type"              ,stBody.cert_type               );
		pkt.GetParameterVal("cert_num"               ,stBody.cert_num                );
		pkt.GetParameterVal("corp_prop_id"           ,stBody.corp_prop_id            );
		pkt.GetParameterVal("corp_regist_addr"       ,stBody.corp_regist_addr       );
		pkt.GetParameterVal("corp_zip"               ,stBody.corp_zip                );
		pkt.GetParameterVal("corp_tel"               ,stBody.corp_tel                );
		pkt.GetParameterVal("corp_fax"               ,stBody.corp_fax                );
		pkt.GetParameterVal("corp_email"             ,stBody.corp_email              );
		pkt.GetParameterVal("copr_authorizer"        ,stBody.copr_authorizer         );
		pkt.GetParameterVal("auth_nationality"       ,stBody.auth_nationality        );
		pkt.GetParameterVal("auth_cert_type_id"      ,stBody.auth_cert_type_id       );
		pkt.GetParameterVal("auth_cert_no"           ,stBody.auth_cert_no            );
		pkt.GetParameterVal("auth_addr"              ,stBody.auth_addr               );
		pkt.GetParameterVal("auth_zip"               ,stBody.auth_zip                );
		pkt.GetParameterVal("auth_tel"               ,stBody.auth_tel                );
		pkt.GetParameterVal("auth_fax"               ,stBody.auth_fax                );
		pkt.GetParameterVal("auth_email"             ,stBody.auth_email              );
		pkt.GetParameterVal("busi_license"           ,stBody.busi_license            );
		pkt.GetParameterVal("tax_cert"               ,stBody.tax_cert                );
		pkt.GetParameterVal("org_code_cert"          ,stBody.org_code_cert           );
		pkt.GetParameterVal("regist_address"         ,stBody.regist_address          );
		pkt.GetParameterVal("sigex_post_code"        ,stBody.sigex_post_code         );
		pkt.GetParameterVal("sigex_tel"              ,stBody.sigex_tel               );
		pkt.GetParameterVal("sigex_fax"              ,stBody.sigex_fax               );
		pkt.GetParameterVal("sigex_email"            ,stBody.sigex_email             );
		pkt.GetParameterVal("cust_id"                ,stBody.cust_id                 );
		pkt.GetParameterVal("gess_broker_id"         ,stBody.gess_broker_id          );
		pkt.GetParameterVal("exec_name"              ,stBody.exec_name               );
		pkt.GetParameterVal("exec_cert_type_id"      ,stBody.exec_cert_type_id       );
		pkt.GetParameterVal("exec_cert_num"          ,stBody.exec_cert_num           );
		pkt.GetParameterVal("corp_code"              ,stBody.corp_code               );
		pkt.GetParameterVal("contacter"              ,stBody.contacter               );
		pkt.GetParameterVal("org_type"               ,stBody.org_type                );
		pkt.GetParameterVal("reg_capital"            ,stBody.reg_capital             );
		pkt.GetParameterVal("corp_type"              ,stBody.corp_type               );
		pkt.GetParameterVal("taxpayer_identifier"    ,stBody.taxpayer_identifier     );
		pkt.GetParameterVal("is_val_added_taxplayer" ,stBody.is_val_added_taxplayer  );
		pkt.GetParameterVal("taxplayer_address"      ,stBody.taxplayer_address       );
		pkt.GetParameterVal("taxpayer_telephone"     ,stBody.taxpayer_telephone      );
		pkt.GetParameterVal("taxpayer_bankcode"      ,stBody.taxpayer_bankcode       );
		pkt.GetParameterVal("taxpayer_bankinfo"      ,stBody.taxpayer_bankinfo       );
		pkt.GetParameterVal("taxpayer_account_id"    ,stBody.taxpayer_account_id     );
		pkt.GetParameterVal("grade_id"               ,stBody.grade_id                );
		pkt.GetParameterVal("acct_stat"              ,stBody.acct_stat               );
		pkt.GetParameterVal("memo"                   ,stBody.memo                    );
		return 0;
	}

	//----------------------------------------------报文接口 [6301] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTransferApply& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        ,stBody.oper_flag       ); 
		pkt.AddParameter("f_busi_type"      ,stBody.f_busi_type     ); 
		pkt.AddParameter("exch_date"        ,stBody.exch_date       ); 
		pkt.AddParameter("cust_no"          ,stBody.cust_no         ); 
		pkt.AddParameter("access_way"       ,stBody.access_way      ); 
		pkt.AddParameter("currency_id"      ,stBody.currency_id     ); 
		pkt.AddParameter("exch_bal"         ,stBody.exch_bal        ); 
		pkt.AddParameter("remark"           ,stBody.remark          ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTransferApply& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         ,stBody.oper_flag       );    
		pkt.GetParameterVal("gess_exch_date"    ,stBody.gess_exch_date  );    
		pkt.GetParameterVal("gess_serial_no"    ,stBody.gess_serial_no  );    
		pkt.GetParameterVal("bk_serial_no"      ,stBody.bk_serial_no    );    

		return 0;
	}


	//----------------------------------------------报文接口 [6304] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryAcctTransfer& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag        ); 
		pkt.AddParameter("gess_exch_date"       ,stBody.gess_exch_date   ); 
		pkt.AddParameter("client_serial_no"     ,stBody.client_serial_no ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryAcctTransfer& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         ,stBody.oper_flag        ); 
		pkt.GetParameterVal("exch_date"         ,stBody.exch_date        );
		pkt.GetParameterVal("serial_no"         ,stBody.serial_no        );
		pkt.GetParameterVal("client_serial_no"  ,stBody.client_serial_no );
		pkt.GetParameterVal("acct_no"           ,stBody.acct_no          );
		pkt.GetParameterVal("settle_bank_no"    ,stBody.settle_bank_no   );
		pkt.GetParameterVal("f_busi_type"       ,stBody.f_busi_type      );
		pkt.GetParameterVal("access_way"        ,stBody.access_way       );
		pkt.GetParameterVal("out_account_no"    ,stBody.out_account_no   );
		pkt.GetParameterVal("in_account_no"     ,stBody.in_account_no    );
		pkt.GetParameterVal("exch_bal"          ,stBody.exch_bal         );
		pkt.GetParameterVal("check_stat1"       ,stBody.check_stat1      );
		pkt.GetParameterVal("check_stat2"       ,stBody.check_stat2      );
		pkt.GetParameterVal("send_stat"         ,stBody.send_stat        );
		pkt.GetParameterVal("in_account_flag"   ,stBody.in_account_flag  );
		pkt.GetParameterVal("remark"            ,stBody.remark           );
		pkt.GetParameterVal("bk_plat_date"      ,stBody.bk_plat_date     );
		pkt.GetParameterVal("bk_seq_no"         ,stBody.bk_seq_no        );
		pkt.GetParameterVal("bk_rsp_code"       ,stBody.bk_rsp_code      );
		pkt.GetParameterVal("bk_rsp_msg"        ,stBody.bk_rsp_msg       );
		pkt.GetParameterVal("o_term_type"       ,stBody.o_term_type      );
		pkt.GetParameterVal("o_teller_id"       ,stBody.o_teller_id      );
		pkt.GetParameterVal("o_date"            ,stBody.o_date           );
		pkt.GetParameterVal("c_term_type1"      ,stBody.c_term_type1     );
		pkt.GetParameterVal("c_teller_id1"      ,stBody.c_teller_id1     );
		pkt.GetParameterVal("c_date1"           ,stBody.c_date1          );
		pkt.GetParameterVal("c_term_type2"      ,stBody.c_term_type2     );
		pkt.GetParameterVal("c_teller_id2"      ,stBody.c_teller_id2     );
		pkt.GetParameterVal("c_date2"           ,stBody.c_date2          );
		return 0;
	}


	//----------------------------------------------报文接口 [6305] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqSigexMemTransferApply& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        ,stBody.oper_flag       );  
		pkt.AddParameter("f_busi_type"      ,stBody.f_busi_type     );  
		pkt.AddParameter("exch_date"        ,stBody.exch_date       );  
		pkt.AddParameter("member_id"        ,stBody.member_id       );  
		pkt.AddParameter("access_way"       ,stBody.access_way      );  
		pkt.AddParameter("currency_id"      ,stBody.currency_id     );  
		pkt.AddParameter("exch_bal"         ,stBody.exch_bal        );  
		pkt.AddParameter("remark"           ,stBody.remark          );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspSigexMemTransferApply& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         ,stBody.oper_flag       );  
		pkt.GetParameterVal("gess_exch_date"    ,stBody.gess_exch_date  );  
		pkt.GetParameterVal("gess_serial_no"    ,stBody.gess_serial_no  );  
		pkt.GetParameterVal("bk_serial_no"      ,stBody.bk_serial_no    );  

		return 0;
	}


	//----------------------------------------------报文接口 [6306] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQuerySigexMemTransfer& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag        ); 
		pkt.AddParameter("gess_exch_date"       ,stBody.gess_exch_date   ); 
		pkt.AddParameter("client_serial_no"     ,stBody.client_serial_no ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQuerySigexMemTransfer& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"         ,stBody.oper_flag         );  
		pkt.GetParameterVal("exch_date"         ,stBody.exch_date         );  
		pkt.GetParameterVal("serial_no"         ,stBody.serial_no         );  
		pkt.GetParameterVal("client_serial_no"  ,stBody.client_serial_no  );  
		pkt.GetParameterVal("member_id"         ,stBody.member_id         );  
		pkt.GetParameterVal("settle_bank_no"    ,stBody.settle_bank_no    );  
		pkt.GetParameterVal("f_busi_type"       ,stBody.f_busi_type       );  
		pkt.GetParameterVal("access_way"        ,stBody.access_way        );  
		pkt.GetParameterVal("out_account_no"    ,stBody.out_account_no    );  
		pkt.GetParameterVal("in_account_no"     ,stBody.in_account_no     );  
		pkt.GetParameterVal("exch_bal"          ,stBody.exch_bal          );  
		pkt.GetParameterVal("check_stat1"       ,stBody.check_stat1       );  
		pkt.GetParameterVal("check_stat2"       ,stBody.check_stat2       );  
		pkt.GetParameterVal("send_stat"         ,stBody.send_stat         );  
		pkt.GetParameterVal("in_account_flag"   ,stBody.in_account_flag   );  
		pkt.GetParameterVal("remark"            ,stBody.remark            );  
		pkt.GetParameterVal("bk_plat_date"      ,stBody.bk_plat_date      );  
		pkt.GetParameterVal("bk_seq_no"         ,stBody.bk_seq_no         );  
		pkt.GetParameterVal("bk_rsp_code"       ,stBody.bk_rsp_code       );  
		pkt.GetParameterVal("bk_rsp_msg"        ,stBody.bk_rsp_msg        );  
		pkt.GetParameterVal("o_term_type"       ,stBody.o_term_type       );  
		pkt.GetParameterVal("o_teller_id"       ,stBody.o_teller_id       );  
		pkt.GetParameterVal("o_date"            ,stBody.o_date            );  
		pkt.GetParameterVal("c_term_type1"      ,stBody.c_term_type1      );  
		pkt.GetParameterVal("c_teller_id1"      ,stBody.c_teller_id1      );  
		pkt.GetParameterVal("c_date1"           ,stBody.c_date1           );  
		pkt.GetParameterVal("c_term_type2"      ,stBody.c_term_type2      );  
		pkt.GetParameterVal("c_teller_id2"      ,stBody.c_teller_id2      );  
		pkt.GetParameterVal("c_date2"           ,stBody.c_date2           );  

		return 0;
	}


	//----------------------------------------------报文接口 [6401] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqEntrOrder& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag       );     
		pkt.AddParameter("cust_id"              ,stBody.cust_id         );
		pkt.AddParameter("prod_code"            ,stBody.prod_code       );
		pkt.AddParameter("exch_code"            ,stBody.exch_code       );
		pkt.AddParameter("price"                ,stBody.price           );
		pkt.AddParameter("volume"               ,stBody.volume          );
		pkt.AddParameter("is_force_order"       ,stBody.is_force_order  );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspEntrOrder& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"            ,stBody.oper_flag           );  
		pkt.GetParameterVal("gess_local_order_no"  ,stBody.gess_local_order_no );  
		pkt.GetParameterVal("gess_serial_no"       ,stBody.gess_serial_no      );  

		return 0;
	}


	//----------------------------------------------报文接口 [6402] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqEntrCancel& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag           ); 
		pkt.AddParameter("gess_local_order_no"  ,stBody.gess_local_order_no ); 
		pkt.AddParameter("order_no"             ,stBody.order_no            ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspEntrCancel& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"            ,stBody.oper_flag           );  
		pkt.GetParameterVal("gess_local_order_no"  ,stBody.gess_local_order_no );  

		return 0;
	}


	//----------------------------------------------报文接口 [6403] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqEndDayListConfirm& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        ,stBody.oper_flag  );
		pkt.AddParameter("cust_id"          ,stBody.cust_id    );
		pkt.AddParameter("exch_date"        ,stBody.exch_date  );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspEndDayListConfirm& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"        ,stBody.oper_flag  );

		return 0;
	}


	//----------------------------------------------报文接口 [6404] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryEntrFlow& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag           );  
		pkt.AddParameter("gess_local_order_no"  ,stBody.gess_local_order_no );  
		pkt.AddParameter("client_serial_no"     ,stBody.client_serial_no    );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryEntrFlow& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag            );
		pkt.GetParameterVal("order_no"              ,stBody.order_no             );
		pkt.GetParameterVal("client_serial_no"      ,stBody.client_serial_no     );
		pkt.GetParameterVal("gess_local_order_no"   ,stBody.gess_local_order_no  );
		pkt.GetParameterVal("gess_serial_no"        ,stBody.gess_serial_no       );
		pkt.GetParameterVal("cust_id"               ,stBody.cust_id              );
		pkt.GetParameterVal("exch_code"             ,stBody.exch_code            );
		pkt.GetParameterVal("market_id"             ,stBody.market_id            );
		pkt.GetParameterVal("prod_code"             ,stBody.prod_code            );
		pkt.GetParameterVal("entr_price"            ,stBody.entr_price           );
		pkt.GetParameterVal("entr_amount"           ,stBody.entr_amount          );
		pkt.GetParameterVal("remain_amount"         ,stBody.remain_amount        );
		pkt.GetParameterVal("offset_flag"           ,stBody.offset_flag          );
		pkt.GetParameterVal("deli_flag"             ,stBody.deli_flag            );
		pkt.GetParameterVal("bs"                    ,stBody.bs                   );
		pkt.GetParameterVal("exch_bal"              ,stBody.exch_bal             );
		pkt.GetParameterVal("froz_margin"           ,stBody.froz_margin          );
		pkt.GetParameterVal("exch_fare"             ,stBody.exch_fare            );
		pkt.GetParameterVal("cov_type"              ,stBody.cov_type             );
		pkt.GetParameterVal("src_match_no"          ,stBody.src_match_no         );
		pkt.GetParameterVal("origin_order_no"       ,stBody.origin_order_no      );
		pkt.GetParameterVal("match_type"            ,stBody.match_type           );
		pkt.GetParameterVal("order_send_type"       ,stBody.order_send_type      );
		pkt.GetParameterVal("entr_stat"             ,stBody.entr_stat            );
		pkt.GetParameterVal("cancel_flag"           ,stBody.cancel_flag          );
		pkt.GetParameterVal("exch_date"             ,stBody.exch_date            );
		pkt.GetParameterVal("accept_time"           ,stBody.accept_time          );
		pkt.GetParameterVal("e_term_type"           ,stBody.e_term_type          );
		pkt.GetParameterVal("e_branch_id"           ,stBody.e_branch_id          );
		pkt.GetParameterVal("e_teller_id"           ,stBody.e_teller_id          );
		pkt.GetParameterVal("e_trader_id"           ,stBody.e_trader_id          );
		pkt.GetParameterVal("e_exch_time"           ,stBody.e_exch_time          );
		pkt.GetParameterVal("c_term_type"           ,stBody.c_term_type          );
		pkt.GetParameterVal("c_teller_id"           ,stBody.c_teller_id          );
		pkt.GetParameterVal("c_trader_id"           ,stBody.c_trader_id          );
		pkt.GetParameterVal("c_exch_time"           ,stBody.c_exch_time          );
		pkt.GetParameterVal("rsp_msg"               ,stBody.rsp_msg              );
		return 0;
	}


	//----------------------------------------------报文接口 [6501] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTakeApply& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        ,stBody.oper_flag       );   
		pkt.AddParameter("cust_id"          ,stBody.cust_id         );
		pkt.AddParameter("variety_id"       ,stBody.variety_id      );
		pkt.AddParameter("app_amount"       ,stBody.app_amount      );
		pkt.AddParameter("city_code"        ,stBody.city_code       );
		pkt.AddParameter("stor_id"          ,stBody.stor_id         );
		pkt.AddParameter("take_man"         ,stBody.take_man        );
		pkt.AddParameter("cert_type_id"     ,stBody.cert_type_id    );
		pkt.AddParameter("cert_num"         ,stBody.cert_num        );
		pkt.AddParameter("app_pwd"          ,stBody.app_pwd         );
		pkt.AddParameter("app_record"       ,stBody.app_record      );
		pkt.AddParameter("self_draw"        ,stBody.self_draw       );
		pkt.AddParameter("trade_draw"       ,stBody.trade_draw      );
		pkt.AddParameter("gold_forword"     ,stBody.gold_forword    );
		pkt.AddParameter("remark"           ,stBody.remark          );
		pkt.AddParameter("take_date"        ,stBody.take_date       );
		pkt.AddParameter("lend_check_no"    ,stBody.lend_check_no   );

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTakeApply& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag          ); 
		pkt.GetParameterVal("gess_local_sheet_no"   ,stBody.gess_local_sheet_no); 
		pkt.GetParameterVal("sheet_no"              ,stBody.sheet_no           ); 
		pkt.GetParameterVal("cust_id"               ,stBody.cust_id            ); 
		pkt.GetParameterVal("send_stat"             ,stBody.send_stat          ); 
		pkt.GetParameterVal("stat"                  ,stBody.stat               ); 
		pkt.GetParameterVal("take_margin"           ,stBody.take_margin        ); 
		pkt.GetParameterVal("app_start_date"        ,stBody.app_start_date     ); 
		pkt.GetParameterVal("app_end_date"          ,stBody.app_end_date       ); 
		pkt.GetParameterVal("variety_id"            ,stBody.variety_id         ); 
		pkt.GetParameterVal("app_amount"            ,stBody.app_amount         ); 
		pkt.GetParameterVal("draw_type"             ,stBody.draw_type          ); 
		pkt.GetParameterVal("self_draw"             ,stBody.self_draw          ); 
		pkt.GetParameterVal("trade_draw"            ,stBody.trade_draw         ); 

		return 0;
	}

	//----------------------------------------------报文接口 [6502] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTakeApplyCancel& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag           );   
		pkt.AddParameter("gess_local_sheet_no"  ,stBody.gess_local_sheet_no );   
		pkt.AddParameter("sheet_no"             ,stBody.sheet_no            );   
		pkt.AddParameter("cust_id"              ,stBody.cust_id             );   
		pkt.AddParameter("take_man"             ,stBody.take_man            );   
		pkt.AddParameter("take_pwd"             ,stBody.take_pwd            );   

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTakeApplyCancel& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag           ); 
		pkt.GetParameterVal("gess_local_sheet_no"   ,stBody.gess_local_sheet_no ); 
		pkt.GetParameterVal("sheet_no"              ,stBody.sheet_no            ); 
		pkt.GetParameterVal("cust_id"               ,stBody.cust_id             ); 
		pkt.GetParameterVal("stat"                  ,stBody.stat                ); 

		return 0;
	}

	//----------------------------------------------报文接口 [6503] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQueryTakeList& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag           ); 
		pkt.AddParameter("gess_local_sheet_no"  ,stBody.gess_local_sheet_no ); 
		pkt.AddParameter("sheet_no"             ,stBody.sheet_no            ); 
		pkt.AddParameter("client_serial_no"     ,stBody.client_serial_no    ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQueryTakeList& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag           );
		pkt.GetParameterVal("gess_local_sheet_no"   ,stBody.gess_local_sheet_no );
		pkt.GetParameterVal("sheet_no"              ,stBody.sheet_no            );
		pkt.GetParameterVal("cust_id"               ,stBody.cust_id             );
		pkt.GetParameterVal("variety_id"            ,stBody.variety_id          );
		pkt.GetParameterVal("app_amount"            ,stBody.app_amount          );
		pkt.GetParameterVal("draw_type"             ,stBody.draw_type           );
		pkt.GetParameterVal("self_draw"             ,stBody.self_draw           );
		pkt.GetParameterVal("trade_draw"            ,stBody.trade_draw          );
		pkt.GetParameterVal("city_code"             ,stBody.city_code           );
		pkt.GetParameterVal("stor_id"               ,stBody.stor_id             );
		pkt.GetParameterVal("take_man"              ,stBody.take_man            );
		pkt.GetParameterVal("cert_type_id"          ,stBody.cert_type_id        );
		pkt.GetParameterVal("cert_num"              ,stBody.cert_num            );
		pkt.GetParameterVal("app_record"            ,stBody.app_record          );
		pkt.GetParameterVal("app_date"              ,stBody.app_date            );
		pkt.GetParameterVal("app_time"              ,stBody.app_time            );
		pkt.GetParameterVal("app_exch_date"         ,stBody.app_exch_date       );
		pkt.GetParameterVal("app_start_date"        ,stBody.app_start_date      );
		pkt.GetParameterVal("app_end_date"          ,stBody.app_end_date        );
		pkt.GetParameterVal("due_take_date"         ,stBody.due_take_date       );
		pkt.GetParameterVal("stat"                  ,stBody.stat                );
		pkt.GetParameterVal("cancel_date"           ,stBody.cancel_date         );
		pkt.GetParameterVal("cancel_time"           ,stBody.cancel_time         );
		pkt.GetParameterVal("cancel_exch_date"      ,stBody.cancel_exch_date    );
		pkt.GetParameterVal("cancel_record"         ,stBody.cancel_record       );
		pkt.GetParameterVal("send_stat"             ,stBody.send_stat           );
		pkt.GetParameterVal("take_margin"           ,stBody.take_margin         );
		pkt.GetParameterVal("is_other_take"         ,stBody.is_other_take       );
		pkt.GetParameterVal("take_affirm"           ,stBody.take_affirm         );
		pkt.GetParameterVal("rsp_code"              ,stBody.rsp_code            );
		pkt.GetParameterVal("rsp_msg"               ,stBody.rsp_msg             );
		pkt.GetParameterVal("gold_forword"          ,stBody.gold_forword        );
		pkt.GetParameterVal("remark"                ,stBody.remark              );

		return 0;
	}


	//----------------------------------------------报文接口 [6701] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqTransferDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"               ,stBody.oper_flag ); 
		pkt.AddParameter("exch_date"			   ,stBody.exch_date ); 
		pkt.AddParameter("member_id"               ,stBody.member_id ); 
		pkt.AddParameter("branch_id"               ,stBody.branch_id ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspTransferDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag           );
		pkt.GetParameterVal("alm_check_sum"         ,stBody.alm_check_sum       );
		pkt.GetParameterVal("alm_check_detail"      ,stBody.alm_check_detail    );

		return 0;
	}


	//----------------------------------------------报文接口 [6702] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqLiquDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"               ,stBody.oper_flag ); 
		pkt.AddParameter("exch_date"			   ,stBody.exch_date ); 
		pkt.AddParameter("member_id"               ,stBody.member_id ); 
		pkt.AddParameter("branch_id"               ,stBody.branch_id ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspLiquDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag           );
		pkt.GetParameterVal("newxml_file_content"   ,stBody.newxml_file_content );

		return 0;
	}


	//----------------------------------------------报文接口 [6704] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqFundCheckDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"               ,stBody.oper_flag ); 
		pkt.AddParameter("exch_date"			   ,stBody.exch_date ); 
		pkt.AddParameter("member_id"               ,stBody.member_id ); 
		pkt.AddParameter("branch_id"               ,stBody.branch_id ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspFundCheckDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"                 ,stBody.oper_flag               );  
		pkt.GetParameterVal("alm_forward_member_posi"   ,stBody.alm_forward_member_posi );  
		pkt.GetParameterVal("alm_defer_member_posi"     ,stBody.alm_defer_member_posi   );  
		pkt.GetParameterVal("alm_member_capital"        ,stBody.alm_member_capital      );  
		pkt.GetParameterVal("alm_fee_summary"           ,stBody.alm_fee_summary         );  
		pkt.GetParameterVal("alm_settle_summary"        ,stBody.alm_settle_summary      );  

		return 0;
	}


	//----------------------------------------------报文接口 [6705] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqInterestDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"               ,stBody.oper_flag ); 
		pkt.AddParameter("exch_date"			   ,stBody.exch_date ); 
		pkt.AddParameter("member_id"               ,stBody.member_id ); 
		pkt.AddParameter("branch_id"               ,stBody.branch_id ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspInterestDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag           );
		pkt.GetParameterVal("alm_pre_interest"      ,stBody.alm_pre_interest    );
		pkt.GetParameterVal("alm_interest"          ,stBody.alm_interest        );

		return 0;
	}


	//----------------------------------------------报文接口 [6801] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqQuerySigexNotice& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"        ,stBody.oper_flag    );  
		pkt.AddParameter("seq_no"           ,stBody.seq_no       );  
		pkt.AddParameter("title"            ,stBody.title        );  
		pkt.AddParameter("s_exch_date"      ,stBody.s_exch_date  );  
		pkt.AddParameter("e_exch_date"      ,stBody.e_exch_date  );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspQuerySigexNotice& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag );
		pkt.GetParameterVal("alm_result"            ,stBody.alm_result);
		return 0;
	}


	//----------------------------------------------报文接口 [6901] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqSigexBasicDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"                ,stBody.oper_flag               ); 
		pkt.AddParameter("member_id"                ,stBody.member_id               ); 
		pkt.AddParameter("city_info"                ,stBody.city_info               ); 
		pkt.AddParameter("spec_date"                ,stBody.spec_date               ); 
		pkt.AddParameter("prod_code_def"            ,stBody.prod_code_def           ); 
		pkt.AddParameter("variety"                  ,stBody.variety                 ); 
		pkt.AddParameter("variety_substitue"        ,stBody.variety_substitue       ); 
		pkt.AddParameter("fare_model_def"           ,stBody.fare_model_def          ); 
		pkt.AddParameter("wh_fare_model"            ,stBody.wh_fare_model           ); 
		pkt.AddParameter("defer_over_fee"           ,stBody.defer_over_fee          ); 
		pkt.AddParameter("defer_fee"                ,stBody.defer_fee               ); 
		pkt.AddParameter("rmb_day_interest_data"    ,stBody.rmb_day_interest_data   ); 
		pkt.AddParameter("take_margin_para"         ,stBody.take_margin_para        ); 
		pkt.AddParameter("branch_fare_interval"     ,stBody.branch_fare_interval    ); 
		pkt.AddParameter("stor_info"                ,stBody.stor_info               ); 
		pkt.AddParameter("branch_id"                ,stBody.branch_id               ); 

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspSigexBasicDataDownload& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"                     ,stBody.oper_flag                );  
		pkt.GetParameterVal("alm_city_info"                 ,stBody.alm_city_info            );  
		pkt.GetParameterVal("alm_spec_date"                 ,stBody.alm_spec_date            );  
		pkt.GetParameterVal("alm_prod_code_def"             ,stBody.alm_prod_code_def        );  
		pkt.GetParameterVal("alm_variety"                   ,stBody.alm_variety              );  
		pkt.GetParameterVal("alm_variety_substitue"         ,stBody.alm_variety_substitue    );  
		pkt.GetParameterVal("alm_fare_model_def"            ,stBody.alm_fare_model_def       );  
		pkt.GetParameterVal("alm_wh_fare_model"             ,stBody.alm_wh_fare_model        );  
		pkt.GetParameterVal("alm_defer_over_fee"            ,stBody.alm_defer_over_fee       );  
		pkt.GetParameterVal("alm_defer_fee"                 ,stBody.alm_defer_fee            );  
		pkt.GetParameterVal("alm_rmb_day_interest_rata"     ,stBody.alm_rmb_day_interest_rata);  
		pkt.GetParameterVal("alm_take_margin_para"          ,stBody.alm_take_margin_para     );  
		pkt.GetParameterVal("alm_branch_interval"           ,stBody.alm_branch_interval      );  
		pkt.GetParameterVal("alm_stor_info"                 ,stBody.alm_stor_info            );  
		pkt.GetParameterVal("alm_stor_city_info"            ,stBody.alm_stor_city_info       );  
		pkt.GetParameterVal("alm_fare_model_detail"         ,stBody.alm_fare_model_detail    );  

		return 0;
	}


	//----------------------------------------------报文接口 [6902] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqSigexMemFareSyn& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag           );  
		pkt.AddParameter("fare_model_id"        ,stBody.fare_model_id       );  
		pkt.AddParameter("fare_model_name"      ,stBody.fare_model_name     );  
		pkt.AddParameter("fare_model_type"      ,stBody.fare_model_type     );  
		pkt.AddParameter("contain_bourse"       ,stBody.contain_bourse      );  
		pkt.AddParameter("gess_branch_id"       ,stBody.gess_branch_id      );  
		pkt.AddParameter("alm_fare_info_list"   ,stBody.alm_fare_info_list  );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspSigexMemFareSyn& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag );
		return 0;
	}



	//----------------------------------------------报文接口 [6904] 报文结构编解码
	//请求报文编码: 结构 -> 报文  
	static int Struct2Packet( TReqSpecialAcctFareSyn& stBody, CTradePacket& pkt)
	{
		pkt.AddParameter("oper_flag"            ,stBody.oper_flag           );  
		pkt.AddParameter("cust_id"			    ,stBody.cust_id				);  
		pkt.AddParameter("alm_acct_fare_info"   ,stBody.alm_acct_fare_info  );  

		return 0;
	}

	//应答报文解码: 报文 -> 结构  
	static int Packet2Struct( TRspSpecialAcctFareSyn& stBody, CTradePacket& pkt)
	{
		pkt.GetParameterVal("oper_flag"             ,stBody.oper_flag );
		return 0;
	}


};

#endif