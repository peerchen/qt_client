

#ifndef _API_STRUCT_H_
#define _API_STRUCT_H_
#include <string>
#include <string.h>
using namespace std;

//----------------------------------------------设置前置机地址接口[SetService]定义
typedef struct tagIpPort
{
	char		sIp[16];		//IP		非空
	int			nPort;			//端口号	非空
	tagIpPort()
	{
		memset(sIp,0x00,sizeof(sIp));
		nPort = -1;
	}
}TIpPort,*PIpPort;
//----------------------------------------------请求报文基类
typedef struct tagReqMsg
{
	char		teller_id[11];	//交易员号		非空
	char		branch_id[21];	//机构代码		非空
	char		member_id[7];	//会员号		非空
	char		unit_id[7];		//接入单元号	非空
	char		root_id[19];	//用于请求与应答的匹配，应答返回与请求相同的值。	非空
	tagReqMsg()
	{
		memset(teller_id,0x00,sizeof(teller_id));
		memset(branch_id,0x00,sizeof(branch_id));
		memset(member_id,0x00,sizeof(member_id));
		memset(unit_id,0x00,sizeof(unit_id));
		memset(root_id,0x00,sizeof(root_id));
	}
}TReqMsg,*PReqMsg;
//----------------------------------------------响应报文基类 定义
// 结构定义:响应结果报文
typedef struct tagRspMsg
{
	char		teller_id[11];	//交易员号		
	char		branch_id[21];	//机构代码		
	char		member_id[7];	//会员号		
	char		unit_id[7];		//接入单元号	
	char		root_id[19];	//用于请求与应答的匹配，应答返回与请求相同的值。	非空
	char       rsp_code[21];	//响应代码		
	char       rsp_msg[41];    //响应信息		
	tagRspMsg()
	{
		memset(teller_id,0x00,sizeof(teller_id));
		memset(branch_id,0x00,sizeof(branch_id));
		memset(member_id,0x00,sizeof(member_id));
		memset(unit_id,0x00,sizeof(unit_id));
		memset(root_id,0x00,sizeof(root_id));
		memset(rsp_code,0x00,sizeof(rsp_code));
		memset(rsp_msg,0x00,sizeof(rsp_msg));
	}
}TRspMsg,*PRspMsg;
//----------------------------------------------异常回调接口[onException]定义
//结构定义：异常回调接口
typedef struct tagExceptionMsg
{
	char       exception_code[10];		//异常代码	非空
	char       exception_msg[200];		//异常消息	非空
	tagExceptionMsg()
	{
		memset(exception_code,0x00,sizeof(exception_code));
		memset(exception_msg,0x00,sizeof(exception_msg));
	}
}TExceptionMsg,*PExceptionMsg;
//----------------------------------------------Req报文接口[ReqLoginTrade/ReqLoginBroadcast]定义
//结构定义:API登录请求报文
typedef struct tagReqLogin :public TReqMsg
{
	int      oper_flag;				//操作标志	非空	默认填 1                       
	char	 crt_pwd[50];			//证书密码	无密码填""
	struct tagAlmBreakpoint			
	{
		char	sequence_seriesno[3];//消息序列类别号 
		char	sequence_no[11];	 //重传方式 0:重传（RESTART） 具体序号:续传（RESUME）   -1:快照（QUICK）
	} *		p_almbreakpoint;		 //断点信息			无断点信息填NULL
	int		num_almbreakpoint;		//断电信息数量		无断点信息填0		没有上传断点信息时默认发送数据流快照
	char	unit_password[61];		//接入单元登录密码	非空
	tagReqLogin()
	{
		oper_flag = 1;
		memset(crt_pwd,0x00,sizeof(crt_pwd));
		p_almbreakpoint = NULL;
		num_almbreakpoint = 0;
		memset(unit_password,0x00,sizeof(unit_password));
	}
}TReqLogin,*PReqLogin;

//----------------------------------------------Rsp报文接口 [onRecvRspLoginTrade/onRecvRspLoginBroadcast] 定义
// 结构定义:API登录响应报文
typedef struct tagRspLogin :public TRspMsg
{
	int      oper_flag;				//操作标志 
	char	 exch_date[9];			//交易日期  登录未成功则为空
	tagRspLogin()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
	}
}TRspLogin ,*PRspLogin;


//----------------------------------------------Req报文接口 [ReqLogoutTrade/ReqLogoutBroadcast] 定义
//结构定义:接入单元登出请求报文
typedef struct tagReqLogout :public TReqMsg
{
	int      oper_flag;				//操作标志	非空	默认填 1 
	tagReqLogout()
	{
		oper_flag =	0;
	}
}TReqLogout,*PReqLogout;

//----------------------------------------------Rsp报文接口 [onRecvRspLogoutTrade/onRecvRspLogoutBroadcast] 定义
// 结构定义:接入单元登出响应报文
typedef struct tagRspLogout :public TRspMsg
{
	int     oper_flag;				//操作标志 
	tagRspLogout()
	{
		oper_flag =	0;
	}
}TRspLogout,*PRspLogout;

//----------------------------------------------Req报文接口 [ReqTellerLogin] 定义
//结构定义:交易员登录请求报文
typedef struct tagReqTellerLogin :public TReqMsg
{
	int      oper_flag;				//操作标志	非空	默认填 1  
	char     password[61];			//操作员密码	非空	填MD5加密后的值   
	tagReqTellerLogin()
	{
		oper_flag =	0;
		memset(password,0x00,sizeof(password));
	}
}TReqTellerLogin,*PReqTellerLogin;

//----------------------------------------------Rsp报文接口 [onRecvRspTellerLogin] 定义
// 结构定义:交易员登录响应报文
typedef struct tagRspTellerLogin :public TRspMsg
{
	int      oper_flag;				//操作标志
	char	 exch_date[9];			//交易日期  登录未成功则为空
	tagRspTellerLogin()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
	}
}TRspTellerLogin ,*PRspTellerLogin;

//----------------------------------------------Req报文接口 [ReqTellerLogout] 定义
//结构定义:交易员登出请求报文
typedef struct tagReqTellerLogout :public TReqMsg
{
	int      oper_flag;				//操作标志	非空	默认填 1        
	tagReqTellerLogout()
	{
		oper_flag =	0;
	}
}TReqTellerLogout,*PReqTellerLogout;

//----------------------------------------------Rsp报文接口 [onRecvRspTellerLogout] 定义
// 结构定义:交易员登出响应报文
typedef struct tagRspTellerLogout :public TRspMsg
{
	int      oper_flag;				//操作标志
	tagRspTellerLogout()
	{
		oper_flag =	0;
	}
}TRspTellerLogout,*PRspTellerLogout;


//----------------------------------------------Req报文接口 [ReqPreOpenAccountLegal] 定义
// 结构定义:法人预开户请求报文体
typedef struct tagReqPreOpenAccountLegal :public TReqMsg
{
	int				 oper_flag;				//操作标志	非空	默认填 1
	char			 gess_branch_id[21];	//签约机构	非空	填默认值，上线时分配
	char			 acct_type;				//账户类型  固定填'2'，代表法人  取值范围：'1'-自营 '2'-法人 '3'-个人
	char			 gess_grade_id[21];		//客户级别	非空
	char			 settle_bank_no[5];		//结算行号	非空
	char			 account_no[31];		//银行账户	非空
	char			 account_name[41];		//银行户名名称	非空 
	char			 open_account_date[9];	//账户开户日期	非空
	char			 account_due_date[9];	//账户到期日期	非空
	char			 corp_en_name[121];		//公司英文名称	非空
	char			 corp_chn_name[81];		//公司中文名称	非空
	char			 corp_en_abbr[21];		//公司英文简称	非空
	char			 corp_chn_abbr[21];		//公司中文简称	非空
	char			 corp_prop_id;			//公司类型		非空	取值范围：'1'-有限公司,'2'-自然人独资,'3'-有限合伙,'4'-其他
	char			 corp_code[33];			//企业组织结构代码	非空
	char			 cert_type;				//证书类型	非空	取值范围：'1'-商业许可证 commercial licence,'2'-公司注册证 certificate of incorporation,'3'-商业登记证 business registration certificate,'4'-有business number的证书,'5'-其他
	char			 cert_num[41];			//证书编码	非空
	char			 contacter[81];			//法人代表	
	char			 mobile_phone[31];		//手机号码			
	char			 regist_addr[81];		//注册地	非空	
	double		     reg_capital;		    //注册资本	非空
	char			 org_type;				//机构类型	非空	取值范围：'2'-基金公司,'3'-会员单位,'4'-基金公司和会员单位
	char			 corp_zip[11];			//公司邮编	非空				
	char			 corp_tel[31];			//公司电话	非空	
	char			 corp_fax[31];			//公司传真	非空
	char			 corp_email[81];		//公司电子邮箱	非空
	char			 pawnee_flag;			//质权人标志	非空	取值范围：'1'-是，'0'-否
	char			 corp_regist_addr[121]; //公司注册地址	非空	
	char			 copr_authorizer;		//公司授权人	非空	取值范围：'1'-公司授权人，'2'-法人，'3'-董事，'4'-负责人
	char			 auth_nationality[41];	//授权人国籍	非空	
	char			 auth_cert_type_id;	//授权人证件类型	非空	取值范围：'s'-身份证、'h'-护照、'j'-军官证、'y'-营业执照	
	char			 auth_cert_no[21];		//授权人证件号	非空	
	char			 auth_addr[81];			//授权人联系地址	非空
	char			 auth_zip[11];			//授权人邮编	非空
	char			 auth_tel[31];			//授权人电话	非空
	char			 auth_fax[31];			//授权人传真	非空
	char			 auth_email[81];		//授权人电子邮箱	非空
	char			 busi_license[21];		//营业执照
	char			 tax_cert[21];			//税务登记证	
	char			 org_code_cert[21];		//组织机构代码证
	char			 regist_address[81];	//注册地址
	char			 sigex_post_code[11];	//自贸区邮编	
	char			 sigex_tel[31];			//自贸区电话
	char			 sigex_fax[31];			//自贸区传真
	char			 sigex_email[81];		//自贸区电子邮箱
	char			 cust_id[13];			//黄金交易编码	重开户填
	char			 gess_broker_id[21];	//客户经理号	非空  固定配置
	char			 exec_name[41];			//交易经办人	非空
	char			 exec_tel[31];			//经办人联系电话	
	char			 exec_cert_type_id;		//经办人证件号码	非空	
	char			 exec_cert_num[21];		//经办人证件类型	非空
	char			 taxpayer_identifier[22];//纳税人识别号	
	char			 is_val_added_taxplayer;//是否为增值税一般纳税人	
	char			 taxplayer_address[82]; //纳税人地址	
	char			 taxpayer_telephone[31];//纳税人电话	
	char			 taxpayer_bankcode[5];	//纳税人银行代码		
	char			 taxpayer_bankinfo[82]; //纳税人开户行信息		
	char			 taxpayer_account_id[32];//纳税人账号		
	char			 memo[255];				//备注	
	tagReqPreOpenAccountLegal()
	{
		oper_flag =	0;
		memset(gess_branch_id     ,0x00,sizeof(gess_branch_id     ));
		acct_type = 0;
		memset(gess_grade_id      ,0x00,sizeof(gess_grade_id      ));
		memset(settle_bank_no     ,0x00,sizeof(settle_bank_no     ));
		memset(account_no         ,0x00,sizeof(account_no         ));
		memset(account_name       ,0x00,sizeof(account_name       ));
		memset(open_account_date  ,0x00,sizeof(open_account_date  ));
		memset(account_due_date   ,0x00,sizeof(account_due_date   ));
		memset(corp_en_name       ,0x00,sizeof(corp_en_name       ));
		memset(corp_chn_name      ,0x00,sizeof(corp_chn_name      ));
		memset(corp_en_abbr       ,0x00,sizeof(corp_en_abbr       ));
		memset(corp_chn_abbr      ,0x00,sizeof(corp_chn_abbr      ));
		corp_prop_id = 0;
		memset(corp_code          ,0x00,sizeof(corp_code          ));
		cert_type = 0;
		memset(cert_num           ,0x00,sizeof(cert_num           ));
		memset(contacter          ,0x00,sizeof(contacter          ));
		memset(mobile_phone       ,0x00,sizeof(mobile_phone       ));
		memset(regist_addr        ,0x00,sizeof(regist_addr        ));
		reg_capital = 0.0;
		org_type = 0;
		memset(corp_zip           ,0x00,sizeof(corp_zip           ));
		memset(corp_tel           ,0x00,sizeof(corp_tel           ));
		memset(corp_fax           ,0x00,sizeof(corp_fax           ));
		memset(corp_email         ,0x00,sizeof(corp_email         ));
		pawnee_flag = 0;
		memset(corp_regist_addr   ,0x00,sizeof(corp_regist_addr   ));
		copr_authorizer = 0;
		memset(auth_nationality   ,0x00,sizeof(auth_nationality   ));
		auth_cert_type_id = 0;
		memset(auth_cert_no       ,0x00,sizeof(auth_cert_no       ));
		memset(auth_addr          ,0x00,sizeof(auth_addr          ));
		memset(auth_zip           ,0x00,sizeof(auth_zip           ));
		memset(auth_tel           ,0x00,sizeof(auth_tel           ));
		memset(auth_fax           ,0x00,sizeof(auth_fax           ));
		memset(auth_email         ,0x00,sizeof(auth_email         ));
		memset(busi_license       ,0x00,sizeof(busi_license       ));
		memset(tax_cert           ,0x00,sizeof(tax_cert           ));
		memset(org_code_cert      ,0x00,sizeof(org_code_cert      ));
		memset(regist_address     ,0x00,sizeof(regist_address     ));
		memset(sigex_post_code    ,0x00,sizeof(sigex_post_code    ));
		memset(sigex_tel          ,0x00,sizeof(sigex_tel          ));
		memset(sigex_fax          ,0x00,sizeof(sigex_fax          ));
		memset(sigex_email        ,0x00,sizeof(sigex_email        ));
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		memset(gess_broker_id     ,0x00,sizeof(gess_broker_id     ));
		memset(exec_name          ,0x00,sizeof(exec_name          ));
		memset(exec_tel           ,0x00,sizeof(exec_tel           ));
		exec_cert_type_id = 0;
		memset(exec_cert_num      ,0x00,sizeof(exec_cert_num      ));
		memset(taxpayer_identifier,0x00,sizeof(taxpayer_identifier));
		is_val_added_taxplayer = 0;
		memset(taxplayer_address  ,0x00,sizeof(taxplayer_address  ));
		memset(taxpayer_telephone ,0x00,sizeof(taxpayer_telephone ));
		memset(taxpayer_bankcode  ,0x00,sizeof(taxpayer_bankcode  ));
		memset(taxpayer_bankinfo  ,0x00,sizeof(taxpayer_bankinfo  ));
		memset(taxpayer_account_id,0x00,sizeof(taxpayer_account_id));
		memset(memo               ,0x00,sizeof(memo               ));
	}
}TReqPreOpenAccountLegal,*PReqPreOpenAccountLegal;


//----------------------------------------------Rsp报文接口 [onRecvRspPreOpenAccountLegal] 定义
// 结构定义:法人预开户的响应报文体
typedef struct tagRspPreOpenAccountLegal :public TRspMsg
{
	int      oper_flag;				//操作标志
	char	 cust_id[13];			//客户号
	tagRspPreOpenAccountLegal()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
	}
}TRspPreOpenAccountLegal,*PRspPreOpenAccountLegal;
//----------------------------------------------Req报文接口 [ReqOpenAccountPersonal] 定义
// 结构定义:个人开户请求报文体
typedef struct tagReqOpenAccountPersonal  :public TReqMsg
{
	int        oper_flag;			//操作标志	非空	默认填 1
	char       cust_id[13];			//客户代码	重开户填
	char       account_no[33];		//银行账户	非空
	char       account_name[41];	//银行户名名称	非空	
	char       open_account_date[9];//账户开户日期	非空		
	char       account_due_date[9]; //账户到期日期	非空
	char       cert_type_id;		//证件类型	非空	
	char       cert_num[21];		//证件号码	非空
	char       gess_branch_id[21];	//分支机构	非空	填默认值，上线时分配
	char       gess_broker_id[21];	//客户经理	非空	固定配置
	char       gess_grade_id[21];	//客户级别	非空	固定配置
	char       mobile_phone[31];	//手机		非空
	char       tel[31];				//联系电话
	char       addr[81];			//联系地址	非空
	char       zipcode[11];			//邮政编码	非空
	char       email[81];			//电子邮箱	非空
	char       settle_bank_no[5];	//结算行号	非空
	char       nationality[41];		//国籍		非空
	char       birthday[9];		//出生日期	非空
	char       first_name[31];		//姓		非空
	char       last_name[31];		//名		非空	
	char       middle_name[21];		//中间名	非空
	char       cert_open_date[9];	//证件签发日期	非空	大于18900101，且小于等于当前日期
	char       cert_due_date[9];	//证件有效期至	非空	大于18900101，且小于等于当前日期 证件有效期至必须大于证件签发日期
	char       memo[255];			//备注
	tagReqOpenAccountPersonal()
	{
		oper_flag =	0;
		memset(cust_id          ,0x00,sizeof(cust_id          ));
		memset(account_no       ,0x00,sizeof(account_no       ));
		memset(account_name     ,0x00,sizeof(account_name     ));
		memset(open_account_date,0x00,sizeof(open_account_date));
		memset(account_due_date ,0x00,sizeof(account_due_date ));
		cert_type_id = 0;
		memset(cert_num         ,0x00,sizeof(cert_num         ));
		memset(gess_branch_id   ,0x00,sizeof(gess_branch_id   ));
		memset(gess_broker_id   ,0x00,sizeof(gess_broker_id   ));
		memset(gess_grade_id    ,0x00,sizeof(gess_grade_id    ));
		memset(mobile_phone     ,0x00,sizeof(mobile_phone     ));
		memset(tel              ,0x00,sizeof(tel              ));
		memset(addr             ,0x00,sizeof(addr             ));
		memset(zipcode          ,0x00,sizeof(zipcode          ));
		memset(email            ,0x00,sizeof(email            ));
		memset(settle_bank_no   ,0x00,sizeof(settle_bank_no   ));
		memset(nationality      ,0x00,sizeof(nationality      ));
		memset(birthday         ,0x00,sizeof(birthday         ));
		memset(first_name       ,0x00,sizeof(first_name       ));
		memset(last_name        ,0x00,sizeof(last_name        ));
		memset(middle_name      ,0x00,sizeof(middle_name      ));
		memset(cert_open_date   ,0x00,sizeof(cert_open_date   ));
		memset(cert_due_date    ,0x00,sizeof(cert_due_date    ));
		memset(memo             ,0x00,sizeof(memo             ));
	}
}TReqOpenAccountPersonal,*PReqOpenAccountPersonal;


//----------------------------------------------Rsp报文接口 [onRecvRspOpenAccountPersonal] 定义
// 结构定义:个人开户的响应报文体
typedef struct tagRspOpenAccountPersonal :public TRspMsg
{
	int      oper_flag;				//操作标志
	char	 cust_id[13];			//客户代码
	tagRspOpenAccountPersonal()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
	}
}TRspOpenAccountPersonal,*PRspOpenAccountPersonal;

//----------------------------------------------Req报文接口 [ReqModifyBankAcctBind] 定义   
// 结构定义:客户银行账户绑定修改的请求报文体                                        
typedef struct tagReqModifyBankAcctBind    :public TReqMsg                                         
{                                                                         
	int        oper_flag;			//操作标志	非空	默认填 0         
	char       cust_id[13];			//客户代码	非空	                    
	char       acct_type;		//账户类型	非空	区分法人客户或个人客户	                    
	char       cert_type_id;		//证件类型	非空	法人客户则指“公司证书类型”                   
	char       cert_num[41];		//证件号码	非空	法人客户则指“公司证书编号”	                  
	char       new_account_no[31];	//新银行账号	非空    可以跟之前的银行号码相同，表示重新绑定
	char	   account_name[41];	//银行账户名称  非空
	char	   settle_bank_no[5];	//结算行代码	非空
	tagReqModifyBankAcctBind()
	{
		oper_flag =	0;
		memset(cust_id       ,0x00,sizeof(cust_id       ));
		acct_type = 0;
		cert_type_id = 0;
		memset(cert_num      ,0x00,sizeof(cert_num      ));
		memset(account_name  ,0x00,sizeof(account_name  ));
		memset(new_account_no,0x00,sizeof(new_account_no));
	}
}TReqModifyBankAcctBind,*PReqModifyBankAcctBind;                                                       

//----------------------------------------------Rsp报文接口 [onRecvRspModifyBankAcctBind] 定义   
// 结构定义:客户银行账户绑定修改的响应报文体                                        
typedef struct tagRspModifyBankAcctBind :public TRspMsg                             
{                                                                         
	int      oper_flag;				//操作标志                         
	tagRspModifyBankAcctBind()
	{
		oper_flag =	0;
	}
}TRspModifyBankAcctBind,*PRspModifyBankAcctBind;                                                       

//----------------------------------------------Req报文接口 [ReqCancelAccount] 定义
// 结构定义:个人销户的请求报文体
typedef struct tagReqCancelAccount  :public TReqMsg
{
	int      oper_flag;				//操作标志	非空	默认填 0 
	char     cust_id[13];			//客户代码	非空 
	tagReqCancelAccount()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
	}
}TReqCancelAccount,*PReqCancelAccount;

//----------------------------------------------Rsp报文接口 [onRecvRspCancelAccount] 定义
// 结构定义:个人销户的响应报文体
typedef struct tagRspCancelAccount :public TRspMsg
{
	int      oper_flag;				//操作标志    
	char	 exch_date[9];			//交易日期	客户销户有出金时才会有值
	char	 client_serial_no[41];	//客户端流水号	客户销户有出金时才会有值
	tagRspCancelAccount()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
	}
}TRspCancelAccount,*PRspCancelAccount;

//----------------------------------------------Req报文接口 [ReqModifyAcctInfoPersonal] 定义
// 结构定义:个人客户信息修改请求报文体
typedef struct tagReqModifyAcctInfoPersonal  :public TReqMsg
{
	int        oper_flag;			//操作标志	非空	默认填 1 
	char       cust_id[13];			//客户代码	非空		
	char       nationality[41];		//国籍	非空				
	char       birthday[9];			//出生日期	非空
	char       first_name[31];		//姓	非空					
	char       last_name[31];		//名	非空				
	char       middle_name[21];		//中间名	非空			
	char       cert_open_date[9];	//证件签发日期	非空  大于18900101
	char       cert_due_date[9];	//证件有效期至	非空  大于18900101，证件有效期至必须大于证件签发日期
	char       mobile_phone[31];	//手机				
	char       tel[31];				//联系电话	非空	
	char       addr[81];			//联系地址	非空
	char       zipcode[11];			//邮政编码	非空		
	char       email[81];			//电子邮箱	非空	
	tagReqModifyAcctInfoPersonal()
	{
		oper_flag =	0;
		memset(cust_id       ,0x00,sizeof(cust_id       ));
		memset(nationality   ,0x00,sizeof(nationality   ));
		memset(birthday      ,0x00,sizeof(birthday      ));
		memset(first_name    ,0x00,sizeof(first_name    ));
		memset(last_name     ,0x00,sizeof(last_name     ));
		memset(middle_name   ,0x00,sizeof(middle_name   ));
		memset(cert_open_date,0x00,sizeof(cert_open_date));
		memset(cert_due_date ,0x00,sizeof(cert_due_date ));
		memset(mobile_phone  ,0x00,sizeof(mobile_phone  ));
		memset(tel           ,0x00,sizeof(tel           ));
		memset(addr          ,0x00,sizeof(addr          ));
		memset(zipcode       ,0x00,sizeof(zipcode       ));
		memset(email         ,0x00,sizeof(email         ));
	}
}TReqModifyAcctInfoPersonal,*PReqModifyAcctInfoPersonal;

//----------------------------------------------Rsp报文接口 [onRecvRspModifyAcctInfoPersonal] 定义
// 结构定义:个人客户信息修改响应报文体
typedef struct tagRspModifyAcctInfoPersonal :public TRspMsg
{
	int      oper_flag;				//操作标志
	tagRspModifyAcctInfoPersonal()
	{
		oper_flag =	0;
	}
}TRspModifyAcctInfoPersonal,*PRspModifyAcctInfoPersonal;



//----------------------------------------------Req报文接口 [ReqModifyAcctInfoLegal] 定义
// 结构定义:法人客户信息修改的请求报文体
typedef struct tagReqModifyAcctInfoLegal  :public TReqMsg
{
	int		 oper_flag;				//操作标志	非空	默认填 1              
	char	 cust_id[13];			//黄金交易编码	非空          
	char	 corp_en_name[121];		//公司英文名称	非空          
	char	 corp_chn_name[81];		//公司中文名称	非空          
	char	 corp_en_abbr[21];		//公司英文简称	非空          
	char	 corp_chn_abbr[21];		//公司中文简称	非空          
	char	 regist_addr[81];		//注册地 	非空               
	char     cert_type;				//证件类型	非空              
	char     cert_num[41];			//证书编号	非空              
	char     corp_prop_id;			//公司类型	非空              
	char     corp_code[33];			//企业组织机构代码	非空      
	char     contacter[81];			//法人代表              
	char     mobile_phone[32];		//手机号码              
	char     org_type[3];			//机构类型	非空              
	double   reg_capital;			//注册资本              
	char     pawnee_flag;			//质权人标志	非空            
	char     corp_regist_addr[121]; //公司注册地址	非空          
	char     corp_zip[11];			//公司邮编	非空              
	char     corp_tel[31];			//公司电话	非空              
	char     corp_fax[31];			//公司传真	非空              
	char     corp_email[81];		//公司电子邮箱	非空          
	char     copr_authorizer;		//公司授权人	非空            
	char     auth_nationality[41];	//授权人国籍	非空            
	char     auth_cert_type_id;		//授权人证件类型	非空    
	char     auth_cert_no[21];		//授权人证件号	非空        
	char     auth_addr[81];			//授权人联系地址	非空        
	char     auth_zip[11];			//授权人邮编	非空            
	char     auth_tel[31];			//授权人电话	非空            
	char     auth_fax[31];			//授权人传真	非空            
	char     auth_email[81];		//授权人电子邮箱	非空        
	char     busi_license[21];		//营业执照		非空              
	char     tax_cert[21];			//税务登记证	非空            
	char     org_code_cert[21];		//组织机构代码证	非空        
	char     regist_address[81];	//注册地址		非空              
	char     sigex_post_code[11];	//自贸区邮编	非空            
	char     sigex_tel[31];			//自贸区电话	非空            
	char     sigex_fax[31];			//自贸区传真	非空            
	char     sigex_email[81];		//自贸区电子邮箱	非空        
	char     exec_name[41];			//交易经办人	非空            
	char     exec_tel[32];			//经办人联系电话        
	char     exec_cert_num[21];		//经办人证件号码	非空        
	char     exec_cert_type_id;	//经办人证件类型	非空	
	char     taxpayer_identifier[22];	//纳税人识别号          
	char     is_val_added_taxplayer;	//是否为增值税一般纳税人
	char     taxplayer_address[82];		//纳税人地址            
	char     taxpayer_telephone[31];	//纳税人电话            
	char     taxpayer_bankcode[5];		//纳税人银行代码        
	char     taxpayer_bankinfo[82];		//纳税人开户行信息      
	char     taxpayer_account_id[32];	//纳税人账号            
	char     memo[255];				//备注  
	char	 account_no[31];		//银行账号
	char	 open_account_date[9];	//开户日期
	char	 account_due_date[9];	//账户到期日
	tagReqModifyAcctInfoLegal()
	{
		oper_flag =	0;
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		memset(corp_en_name       ,0x00,sizeof(corp_en_name       ));
		memset(corp_chn_name      ,0x00,sizeof(corp_chn_name      ));
		memset(corp_en_abbr       ,0x00,sizeof(corp_en_abbr       ));
		memset(corp_chn_abbr      ,0x00,sizeof(corp_chn_abbr      ));
		memset(regist_addr        ,0x00,sizeof(regist_addr        ));
		cert_type = 0;
		memset(cert_num           ,0x00,sizeof(cert_num           ));
		corp_prop_id = 0;
		memset(corp_code          ,0x00,sizeof(corp_code          ));
		memset(contacter          ,0x00,sizeof(contacter          ));
		memset(mobile_phone       ,0x00,sizeof(mobile_phone       ));
		memset(org_type           ,0x00,sizeof(org_type           ));
		reg_capital = 0.0;
		pawnee_flag = 0;
		memset(corp_regist_addr   ,0x00,sizeof(corp_regist_addr   ));
		memset(corp_zip           ,0x00,sizeof(corp_zip           ));
		memset(corp_tel           ,0x00,sizeof(corp_tel           ));
		memset(corp_fax           ,0x00,sizeof(corp_fax           ));
		memset(corp_email         ,0x00,sizeof(corp_email         ));
		copr_authorizer = 0;
		memset(auth_nationality   ,0x00,sizeof(auth_nationality   ));
		auth_cert_type_id = 0;
		memset(auth_cert_no       ,0x00,sizeof(auth_cert_no       ));
		memset(auth_addr          ,0x00,sizeof(auth_addr          ));
		memset(auth_zip           ,0x00,sizeof(auth_zip           ));
		memset(auth_tel           ,0x00,sizeof(auth_tel           ));
		memset(auth_fax           ,0x00,sizeof(auth_fax           ));
		memset(auth_email         ,0x00,sizeof(auth_email         ));
		memset(busi_license       ,0x00,sizeof(busi_license       ));
		memset(tax_cert           ,0x00,sizeof(tax_cert           ));
		memset(org_code_cert      ,0x00,sizeof(org_code_cert      ));
		memset(regist_address     ,0x00,sizeof(regist_address     ));
		memset(sigex_post_code    ,0x00,sizeof(sigex_post_code    ));
		memset(sigex_tel          ,0x00,sizeof(sigex_tel          ));
		memset(sigex_fax          ,0x00,sizeof(sigex_fax          ));
		memset(sigex_email        ,0x00,sizeof(sigex_email        ));
		memset(exec_name          ,0x00,sizeof(exec_name          ));
		memset(exec_tel           ,0x00,sizeof(exec_tel           ));
		exec_cert_type_id = 0;
		memset(exec_cert_num      ,0x00,sizeof(exec_cert_num      ));
		memset(taxpayer_identifier,0x00,sizeof(taxpayer_identifier));
		is_val_added_taxplayer = 0;
		memset(taxplayer_address  ,0x00,sizeof(taxplayer_address  ));
		memset(taxpayer_telephone ,0x00,sizeof(taxpayer_telephone ));
		memset(taxpayer_bankcode  ,0x00,sizeof(taxpayer_bankcode  ));
		memset(taxpayer_bankinfo  ,0x00,sizeof(taxpayer_bankinfo  ));
		memset(taxpayer_account_id,0x00,sizeof(taxpayer_account_id));
		memset(memo               ,0x00,sizeof(memo               ));
		memset(account_no         ,0x00,sizeof(account_no         ));
		memset(open_account_date  ,0x00,sizeof(open_account_date  ));
		memset(account_due_date   ,0x00,sizeof(account_due_date   ));
	}
}TReqModifyAcctInfoLegal,*PReqModifyAcctInfoLegal;

//----------------------------------------------Rsp报文接口 [onRecvRspModifyAcctInfoLegal] 定义
// 结构定义:法人客户信息修改的响应报文体
typedef struct tagRspModifyAcctInfoLegal :public TRspMsg
{
	int      oper_flag;				//操作标志
	tagRspModifyAcctInfoLegal()
	{
		oper_flag =	0;
	}
}TRspModifyAcctInfoLegal,*PRspModifyAcctInfoLegal;

//----------------------------------------------Req报文接口 [ReqMemberFareModelChange] 定义
// 结构定义:客户会员费率模板变更请求报文体
typedef struct tagReqMemberFareModelChange  :public TReqMsg
{
	int      oper_flag;				//操作标志	非空	默认填 0               
	char	 cust_id[13];			//客户代码	非空          
	char	 gesas_fare_mode_id[21];//新会员费率模板	非空  
	tagReqMemberFareModelChange()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
		memset(gesas_fare_mode_id,0x00,sizeof(gesas_fare_mode_id));
	}
}TReqMemberFareModelChange,*PReqMemberFareModelChange;

//----------------------------------------------Rsp报文接口 [onRecvRspMemberFareModelChange] 定义
// 结构定义:客户会员费率模板变更响应报文体
typedef struct tagRspMemberFareModelChange :public TRspMsg
{
	int      oper_flag;				//操作标志 
	tagRspMemberFareModelChange()
	{
		oper_flag =	0;
	}
}TRspMemberFareModelChange,*PRspMemberFareModelChange;

//----------------------------------------------Req报文接口 [ReqQueryAcctInfoPersonal] 定义
// 个人客户信息查询请求报文体
typedef struct tagReqQueryAcctInfoPersonal  :public TReqMsg
{
	int		oper_flag;			//操作标志	非空	默认填 1
	char	query_flag;			//查询条件	'1'-根据银行帐号查询，银行账号必填;'2'-根据证件查询，证件类型及号码必填
	char	account_no[31];		//银行账号	当query_flag为'1'时，非空
	char	cert_type_id;	//证件类型	当query_flag为'2'时，非空
	char	cert_num[21];		//证件号码	当query_flag为'2'时，非空  
	tagReqQueryAcctInfoPersonal()
	{
		oper_flag =	0;
		query_flag = 0;
		memset(account_no,0x00,sizeof(account_no));
		cert_type_id = 0;
		memset(cert_num,0x00,sizeof(cert_num));
	}
}TReqQueryAcctInfoPersonal,*PReqQueryAcctInfoPersonal;

//----------------------------------------------Rsp报文接口 [onRecvRspQueryAcctInfoPersonal] 定义
// 结构定义:个人客户信息查询响应报文体
typedef struct tagRspQueryAcctInfoPersonal :public TRspMsg
{
	int		oper_flag;				//操作标志        
	char    cust_id[13];			//客户代码               	       
	char    settle_bank_no[5];		//结算行号	        
	char    account_no[31];			//银行账户	        
	char    account_name[41];		//银行户名名称	    
	char    open_account_date[9];	//账户开户日期    
	char    account_due_date[9];	//账户到期日期	   
	char    cert_type_id;			//证件类型		        
	char    cert_num[21];			//证件号码 	       
	char    gess_fare_mode_id[21];	//国际中心费率模板	
	char    gesas_fare_mode_id[21]; //会员费率模板	    
	char    gess_broker_id[21];		//客户经理	        
	char    grade_id[21];			//客户级别	        
	char    mobile_phone[31];		//手机 		           
	char    tel[31];				//联系电话        
	char    addr[81];				//联系地址	        
	char    zipcode[11];			//邮政编码 	       
	char    email[81];				//电子邮箱        
	char    nationality[41];		//国籍     	       
	char    birthday[9];			//出生日期        
	char    first_name[31];			//姓      	        
	char    last_name[31];			//名    	          
	char    middle_name[21];		//中间名       
	char    cert_open_date[11];		//证件签发日期   
	char    cert_due_date[11];		//证件有效期至    
	char    acct_stat[3];			//客户状态        
	char    memo[255];				//备注  
	tagRspQueryAcctInfoPersonal()
	{
		oper_flag =	0;
		memset(cust_id           ,0x00,sizeof(cust_id           ));
		memset(settle_bank_no    ,0x00,sizeof(settle_bank_no    ));
		memset(account_no        ,0x00,sizeof(account_no        ));
		memset(account_name      ,0x00,sizeof(account_name      ));
		memset(open_account_date ,0x00,sizeof(open_account_date ));
		memset(account_due_date  ,0x00,sizeof(account_due_date  ));
		cert_type_id = 0 ;
		memset(cert_num          ,0x00,sizeof(cert_num          ));
		memset(gess_fare_mode_id ,0x00,sizeof(gess_fare_mode_id ));
		memset(gesas_fare_mode_id,0x00,sizeof(gesas_fare_mode_id));
		memset(gess_broker_id    ,0x00,sizeof(gess_broker_id    ));
		memset(grade_id          ,0x00,sizeof(grade_id          ));
		memset(mobile_phone      ,0x00,sizeof(mobile_phone      ));
		memset(tel               ,0x00,sizeof(tel               ));
		memset(addr              ,0x00,sizeof(addr              ));
		memset(zipcode           ,0x00,sizeof(zipcode           ));
		memset(email             ,0x00,sizeof(email             ));
		memset(nationality       ,0x00,sizeof(nationality       ));
		memset(birthday          ,0x00,sizeof(birthday          ));
		memset(first_name        ,0x00,sizeof(first_name        ));
		memset(last_name         ,0x00,sizeof(last_name         ));
		memset(middle_name       ,0x00,sizeof(middle_name       ));
		memset(cert_open_date    ,0x00,sizeof(cert_open_date    ));
		memset(cert_due_date     ,0x00,sizeof(cert_due_date     ));
		memset(acct_stat         ,0x00,sizeof(acct_stat         ));
		memset(memo              ,0x00,sizeof(memo              ));
	}
}TRspQueryAcctInfoPersonal,*PRspQueryAcctInfoPersonal;

//----------------------------------------------Req报文接口 [ReqQueryAcctInfoLegal] 定义
// 法人客户信息查询请求报文体
typedef struct tagReqQueryAcctInfoLegal  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1
	char      query_flag;		//查询条件	'1'-根据银行帐号查询，银行账号必填;'2'-根据证件查询，证件类型及号码必填
	char      account_no[31];	//银行账号	当query_flag为'1'时，非空
	char      cert_type_id;		//证件类型	当query_flag为2时，非空
	char      cert_num[41];		//证件号码	当query_flag为2时，非空
	tagReqQueryAcctInfoLegal()
	{
		oper_flag =	0;
		query_flag = 0;
		memset(account_no,0x00,sizeof(account_no));
		cert_type_id = 0;
		memset(cert_num,0x00,sizeof(cert_num));
	}
}TReqQueryAcctInfoLegal,*PReqQueryAcctInfoLegal;

//----------------------------------------------Rsp报文接口 [onRecvRspQueryAcctInfoLegal] 定义
// 结构定义:个人客户信息查询响应报文体
typedef struct tagRspQueryAcctInfoLegal :public TRspMsg
{
	int           oper_flag;			//操作标志		默认填 0                          
	char          corp_en_name[121];	//公司英文名称                        
	char          corp_chn_name[81];	//公司中文名称                        
	char          corp_en_abbr[21];		//公司英文简称                        
	char          corp_chn_abbr[21];	//公司中文简称                        
	char          settle_bank_no[5];	//结算行号                            
	char          account_no[31];		//银行账户                            
	char          account_name[41];		//户名                                
	char          open_account_date[9];	//开户日期                            
	char          account_due_date[9];	//到期日期                            
	char          regist_addr[81];		//注册地                              
	char          cert_type;			//证件类型                            
	char          cert_num[41];			//证书编号                            
	char          corp_prop_id[9];		//公司类型                            
	char          corp_regist_addr[121];//公司注册地址                        
	char          corp_zip[11];			//公司邮编                            
	char          corp_tel[31];			//公司电话                            
	char          corp_fax[31];			//公司传真                            
	char          corp_email[81];		//公司电子邮箱                        
	char          copr_authorizer[3];	//公司授权人\法人\董事\负责人         
	char          auth_nationality[41];	//授权人国籍                          
	char          auth_cert_type_id;	//授权人证件号	                
	char          auth_cert_no[21];		//授权人证件类型                      
	char          auth_addr[81];		//授权人联系地址                      
	char          auth_zip[11];			//授权人邮编                          
	char          auth_tel[31];			//授权人电话                          
	char          auth_fax[31];			//授权人传真                          
	char          auth_email[81];		//授权人电子邮箱                      
	char          busi_license[21];		//营业执照                            
	char          tax_cert[21];			//税务登记证                          
	char          org_code_cert[21];	//组织机构代码证                      
	char          regist_address[81];	//注册地址                            
	char          sigex_post_code[11];	//自贸区邮编                          
	char          sigex_tel[31];		//自贸区电话                          
	char          sigex_fax[31];		//自贸区传真                          
	char          sigex_email[81];		//自贸区电子邮箱                      
	char          cust_id[13];			//黄金交易编码                        
	char          gess_broker_id[21];	//客户经理号                          
	char          exec_name[31];		//交易经办人                          
	char          exec_cert_type_id;	//经办人证件类型	              
	char          exec_cert_num[21];	//经办人证件号码                      
	char          corp_code[33];		//企业组织机构代码                    
	char          contacter[81];		//法人代表                            
	char          org_type[3];			//机构类型                            
	double        reg_capital;			//注册资本                            
	char          corp_type[3];			//企业类别                            
	char          taxpayer_identifier[22];	//纳税人识别号                        
	char          is_val_added_taxplayer;	//是否为增值税一般纳税人              
	char          taxplayer_address[82];	//纳税人地址                          
	char          taxpayer_telephone[31];	//纳税人电话                          
	char          taxpayer_bankcode[5];		//纳税人银行代码                      
	char          taxpayer_bankinfo[81];	//纳税人开户行信息                    
	char          taxpayer_account_id[32];	//纳税人账号                          
	char          grade_id[21];			//客户级别                            
	char          acct_stat[3];			//客户状态                            
	char          memo[255];			//备注 
	tagRspQueryAcctInfoLegal()
	{
		oper_flag =	0;
		memset(corp_en_name       ,0x00,sizeof(corp_en_name       ));
		memset(corp_chn_name      ,0x00,sizeof(corp_chn_name      ));
		memset(corp_en_abbr       ,0x00,sizeof(corp_en_abbr       ));
		memset(corp_chn_abbr      ,0x00,sizeof(corp_chn_abbr      ));
		memset(settle_bank_no     ,0x00,sizeof(settle_bank_no     ));
		memset(account_no         ,0x00,sizeof(account_no         ));
		memset(account_name       ,0x00,sizeof(account_name       ));
		memset(open_account_date  ,0x00,sizeof(open_account_date  ));
		memset(account_due_date   ,0x00,sizeof(account_due_date   ));
		memset(regist_addr        ,0x00,sizeof(regist_addr        ));
		cert_type = 0;
		memset(cert_num           ,0x00,sizeof(cert_num           ));
		memset(corp_prop_id       ,0x00,sizeof(corp_prop_id       ));
		memset(corp_regist_addr   ,0x00,sizeof(corp_regist_addr   ));
		memset(corp_zip           ,0x00,sizeof(corp_zip           ));
		memset(corp_tel           ,0x00,sizeof(corp_tel           ));
		memset(corp_fax           ,0x00,sizeof(corp_fax           ));
		memset(corp_email         ,0x00,sizeof(corp_email         ));
		memset(copr_authorizer    ,0x00,sizeof(copr_authorizer    ));
		memset(auth_nationality   ,0x00,sizeof(auth_nationality   ));
		auth_cert_type_id = 0;
		memset(auth_cert_no       ,0x00,sizeof(auth_cert_no       ));
		memset(auth_addr          ,0x00,sizeof(auth_addr          ));
		memset(auth_zip           ,0x00,sizeof(auth_zip           ));
		memset(auth_tel           ,0x00,sizeof(auth_tel           ));
		memset(auth_fax           ,0x00,sizeof(auth_fax           ));
		memset(auth_email         ,0x00,sizeof(auth_email         ));
		memset(busi_license       ,0x00,sizeof(busi_license       ));
		memset(tax_cert           ,0x00,sizeof(tax_cert           ));
		memset(org_code_cert      ,0x00,sizeof(org_code_cert      ));
		memset(regist_address     ,0x00,sizeof(regist_address     ));
		memset(sigex_post_code    ,0x00,sizeof(sigex_post_code    ));
		memset(sigex_tel          ,0x00,sizeof(sigex_tel          ));
		memset(sigex_fax          ,0x00,sizeof(sigex_fax          ));
		memset(sigex_email        ,0x00,sizeof(sigex_email        ));
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		memset(gess_broker_id     ,0x00,sizeof(gess_broker_id     ));
		memset(exec_name          ,0x00,sizeof(exec_name          ));
		exec_cert_type_id = 0;
		memset(exec_cert_num      ,0x00,sizeof(exec_cert_num      ));
		memset(corp_code          ,0x00,sizeof(corp_code          ));
		memset(contacter          ,0x00,sizeof(contacter          ));
		memset(org_type           ,0x00,sizeof(org_type           ));
		reg_capital = 0.0;
		memset(corp_type          ,0x00,sizeof(corp_type          ));
		memset(taxpayer_identifier,0x00,sizeof(taxpayer_identifier));
		is_val_added_taxplayer = 0;
		memset(taxplayer_address  ,0x00,sizeof(taxplayer_address  ));
		memset(taxpayer_telephone ,0x00,sizeof(taxpayer_telephone ));
		memset(taxpayer_bankcode  ,0x00,sizeof(taxpayer_bankcode  ));
		memset(taxpayer_bankinfo  ,0x00,sizeof(taxpayer_bankinfo  ));
		memset(taxpayer_account_id,0x00,sizeof(taxpayer_account_id));
		memset(grade_id           ,0x00,sizeof(grade_id           ));
		memset(acct_stat          ,0x00,sizeof(acct_stat          ));
		memset(memo               ,0x00,sizeof(memo               ));
	}
}TRspQueryAcctInfoLegal,*PRspQueryAcctInfoLegal;

//----------------------------------------------Req报文接口 [ReqTransferApply] 定义
// 结构定义:客户出入金申请请求报文体
typedef struct tagReqTransferApply  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 0
	char      f_busi_type;		//业务类型	非空
	char      exch_date[9];		//交易日期	非空
	char      cust_no[13];		//客户号	非空  
	char      access_way;		//存取标志	非空
	char      currency_id;		//币种 		非空   
	double    exch_bal;			//发生金额	非空	小数点后两位 默认0.0
	char      remark[255];		//备注    
	tagReqTransferApply()
	{
		oper_flag =	0;
		f_busi_type = 0;
		memset(exch_date  ,0x00,sizeof(exch_date  ));
		memset(cust_no    ,0x00,sizeof(cust_no    ));
		access_way = 0;
		currency_id = 0;
		exch_bal = 0.0;
		memset(remark     ,0x00,sizeof(remark     ));
	}
}TReqTransferApply,*PReqTransferApply;

//----------------------------------------------Rsp报文接口 [onRecvRspTransferApply] 定义
// 结构定义:客户出入金申请响应报文体
typedef struct tagRspTransferApply :public TRspMsg
{                              
	int       oper_flag;			//操作标志     
	char      gess_exch_date[9];	//交易日期   
	char	  client_serial_no[19];	//请求流水号		请求报文的标识号，可用于出入金流水查询
	char      gess_serial_no[33];	//国际中心流水号	交易成功才有流水号
	char      bk_serial_no[41];		//结算行流水号		交易成功才有流水号
	tagRspTransferApply()
	{
		oper_flag =	0;
		memset(gess_exch_date,0x00,sizeof(gess_exch_date));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
		memset(gess_serial_no,0x00,sizeof(gess_serial_no));
		memset(bk_serial_no  ,0x00,sizeof(bk_serial_no  ));
	}
}TRspTransferApply,*PRspTransferApply;

//----------------------------------------------Req报文接口 [ReqQueryAcctTransfer] 定义
// 结构定义:客户出入金流水查询请求报文体
typedef struct tagReqQueryAcctTransfer  :public TReqMsg
{
	int       oper_flag;			//操作标志	非空	默认填 0 
	char      gess_exch_date[9];	//交易日期	非空  
	char      client_serial_no[21];	//请求流水号	非空	国际中心流水号
	tagReqQueryAcctTransfer()
	{
		oper_flag =	0;
		memset(gess_exch_date  ,0x00,sizeof(gess_exch_date  ));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
	}
}TReqQueryAcctTransfer,*PReqQueryAcctTransfer;

//----------------------------------------------Rsp报文接口 [onRecvRspQueryAcctTransfer] 定义
// 结构定义:客户出入金流水查询响应报文体
typedef struct tagRspQueryAcctTransfer :public TRspMsg
{                              
	int       oper_flag;			//操作标志    默认填 0      
	char      exch_date[9];			//交易日期          
	char      serial_no[33];		//国际中心流水号    
	char      client_serial_no[21];	//请求流水号        
	char      acct_no[13];			//客户号            
	char      settle_bank_no[5];	//结算行号          
	char      f_busi_type;			//业务类型          
	char      access_way;			//存取方向          
	char      out_account_no[31];	//出金银行账号      
	char      in_account_no[31];	//入金银行账号      
	double    exch_bal;				//发生金额          
	char      check_stat1;			//复核状态1         
	char      check_stat2;			//复核状态2         
	char      send_stat;			//发送状态          
	char      in_account_flag;		//是否已入账        
	char      remark[255];			//备注              
	char      bk_plat_date[9];		//银行日期          
	char      bk_seq_no[33];		//结算行流水号      
	char      bk_rsp_code[21];		//结算行响应代码    
	char      bk_rsp_msg[201];		//结算行响应消息    
	char      o_term_type[3];		//创建来源          
	char      o_teller_id[11];		//创建用户号        
	char      o_date[21];			//创建日期          
	char      c_term_type1[3];		//复核1来源         
	char      c_teller_id1[11];		//复核1用户号       
	char      c_date1[21];			//复核1日期         
	char      c_term_type2[3];		//复核2来源         
	char      c_teller_id2[11];		//复核2用户号       
	char      c_date2[21];			//复核2日期  
	tagRspQueryAcctTransfer()
	{
		oper_flag =	0;
		memset(exch_date       ,0x00,sizeof(exch_date       ));
		memset(serial_no       ,0x00,sizeof(serial_no       ));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
		memset(acct_no         ,0x00,sizeof(acct_no         ));
		memset(settle_bank_no  ,0x00,sizeof(settle_bank_no  ));
		f_busi_type = 0;
		access_way = 0;
		memset(out_account_no  ,0x00,sizeof(out_account_no  ));
		memset(in_account_no   ,0x00,sizeof(in_account_no   ));
		exch_bal = 0.0;
		check_stat1 = 0;
		check_stat2 = 0;
		send_stat = 0;
		in_account_flag = 0;
		memset(remark          ,0x00,sizeof(remark          ));
		memset(bk_plat_date    ,0x00,sizeof(bk_plat_date    ));
		memset(bk_seq_no       ,0x00,sizeof(bk_seq_no       ));
		memset(bk_rsp_code     ,0x00,sizeof(bk_rsp_code     ));
		memset(bk_rsp_msg      ,0x00,sizeof(bk_rsp_msg      ));
		memset(o_term_type     ,0x00,sizeof(o_term_type     ));
		memset(o_teller_id     ,0x00,sizeof(o_teller_id     ));
		memset(o_date          ,0x00,sizeof(o_date          ));
		memset(c_term_type1    ,0x00,sizeof(c_term_type1    ));
		memset(c_teller_id1    ,0x00,sizeof(c_teller_id1    ));
		memset(c_date1         ,0x00,sizeof(c_date1         ));
		memset(c_term_type2    ,0x00,sizeof(c_term_type2    ));
		memset(c_teller_id2    ,0x00,sizeof(c_teller_id2    ));
		memset(c_date2         ,0x00,sizeof(c_date2         ));
	}
}TRspQueryAcctTransfer,*PRspQueryAcctTransfer;

//----------------------------------------------Req报文接口 [ReqSigexMemTransferApply] 定义
// 结构定义:中心会员出入金申请请求报文体
typedef struct tagReqSigexMemTransferApply  :public TReqMsg
{
	int      oper_flag;			//操作标志	非空	默认填 0 
	char     f_busi_type;		//业务类型	非空
	char     exch_date[9];		//交易日期 	非空 
	char     access_way;		//存取标志	非空
	char     currency_id;		//币种	非空    
	double   exch_bal;			//发生金额	非空	小数点后两位 默认0.0
	char     remark[255];		//备注    
	tagReqSigexMemTransferApply()
	{
		oper_flag =	0;
		f_busi_type = 0;
		memset(exch_date  ,0x00,sizeof(exch_date  ));
		access_way = 0;
		currency_id = 0;
		exch_bal = 0.0;
		memset(remark     ,0x00,sizeof(remark     ));
	}
}TReqSigexMemTransferApply,*PReqSigexMemTransferApply;

//----------------------------------------------Rsp报文接口 [onRecvRspSigexMemTransferApply] 定义
// 结构定义:中心会员出入金申请响应报文体
typedef struct tagRspSigexMemTransferApply :public TRspMsg
{                              
	int       oper_flag;			//操作标志      
	char      gess_exch_date[9];	//交易日期  
	char	  client_serial_no[19];	//请求流水号		请求报文的标识号，可用于出入金流水查询
	char      gess_serial_no[33];	//国际中心流水号	交易成功才有流水号
	char      bk_serial_no[41];		//结算行流水号		交易成功才有流水号  
	tagRspSigexMemTransferApply()
	{
		oper_flag =	0;
		memset(gess_exch_date  ,0x00,sizeof(gess_exch_date  ));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
		memset(gess_serial_no  ,0x00,sizeof(gess_serial_no  ));
		memset(bk_serial_no    ,0x00,sizeof(bk_serial_no    ));
	}
}TRspSigexMemTransferApply,*PRspSigexMemTransferApply;

//----------------------------------------------Req报文接口 [ReqQuerySigexMemTransfer] 定义
// 结构定义:中心会员出入金流水查询请求报文体
typedef struct tagReqQuerySigexMemTransfer  :public TReqMsg
{
	int       oper_flag;			//操作标志	非空	默认填 1   
	char      gess_exch_date[9];	//交易日期	非空   
	char      client_serial_no[19];	//请求流水号	非空	国际中心流水号
	tagReqQuerySigexMemTransfer()
	{
		oper_flag =	0;
		memset(gess_exch_date  ,0x00,sizeof(gess_exch_date  ));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
	}
}TReqQuerySigexMemTransfer,*PReqQuerySigexMemTransfer;

//----------------------------------------------Rsp报文接口 [onRecvRspQuerySigexMemTransfer] 定义
// 结构定义:中心会员出入金流水查询响应报文体
typedef struct tagRspQuerySigexMemTransfer :public TRspMsg
{                              
	int       oper_flag;			//操作标志        
	char      exch_date[9];			//交易日期      
	char      serial_no[33];		//国际中心流水号
	char      client_serial_no[19];	//请求流水号                
	char      settle_bank_no[5];	//结算行号      
	char      f_busi_type;			//业务类型      
	char      access_way;			//存取方向      
	char      out_account_no[31];	//出金银行账号  
	char      in_account_no[31];	//入金银行账号  
	double    exch_bal;				//发生金额      
	char      check_stat1;			//复核状态1     
	char      check_stat2;			//复核状态2     
	char      send_stat;			//发送状态      
	char      in_account_flag;		//是否已入账    
	char      remark[255];			//备注          
	char      bk_plat_date[9];		//银行日期      
	char      bk_seq_no[41];		//结算行流水号  
	char      bk_rsp_code[21];		//结算行响应代码
	char      bk_rsp_msg[201];		//结算行响应消息
	char      o_term_type[3];		//创建来源      
	char      o_teller_id[11];		//创建用户号    
	char      o_date[21];			//创建日期      
	char      c_term_type1[3];		//复核1来源     
	char      c_teller_id1[11];		//复核1用户号   
	char      c_date1[21];			//复核1日期     
	char      c_term_type2[3];		//复核2来源     
	char      c_teller_id2[11];		//复核2用户号   
	char      c_date2[21];			//复核2日期     
	tagRspQuerySigexMemTransfer()
	{
		oper_flag =	0;
		memset(exch_date       ,0x00,sizeof(exch_date       ));
		memset(serial_no       ,0x00,sizeof(serial_no       ));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
		memset(settle_bank_no  ,0x00,sizeof(settle_bank_no  ));
		f_busi_type = 0;
		access_way =	0;
		memset(out_account_no  ,0x00,sizeof(out_account_no  ));
		memset(in_account_no   ,0x00,sizeof(in_account_no   ));
		exch_bal = 0.0;
		check_stat1 = 0;
		check_stat2 = 0;
		send_stat = 0;
		in_account_flag = 0;
		memset(remark          ,0x00,sizeof(remark          ));
		memset(bk_plat_date    ,0x00,sizeof(bk_plat_date    ));
		memset(bk_seq_no       ,0x00,sizeof(bk_seq_no       ));
		memset(bk_rsp_code     ,0x00,sizeof(bk_rsp_code     ));
		memset(bk_rsp_msg      ,0x00,sizeof(bk_rsp_msg      ));
		memset(o_term_type     ,0x00,sizeof(o_term_type     ));
		memset(o_teller_id     ,0x00,sizeof(o_teller_id     ));
		memset(o_date          ,0x00,sizeof(o_date          ));
		memset(c_term_type1    ,0x00,sizeof(c_term_type1    ));
		memset(c_teller_id1    ,0x00,sizeof(c_teller_id1    ));
		memset(c_date1         ,0x00,sizeof(c_date1         ));
		memset(c_term_type2    ,0x00,sizeof(c_term_type2    ));
		memset(c_teller_id2    ,0x00,sizeof(c_teller_id2    ));
		memset(c_date2         ,0x00,sizeof(c_date2         ));
	}
}TRspQuerySigexMemTransfer,*PRspQuerySigexMemTransfer;

//----------------------------------------------Req报文接口 [ReqEntrOrder] 定义
// 结构定义:委托报单请求报文体
typedef struct tagReqEntrOrder  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1       
	char      cust_id[13];		//客户代码	非空      
	char      prod_code[9];	//合约代码	非空      
	char      req_exch_code[5];	//交易代码	非空      
	double    price;			//委托价格  交割申报、中立仓申报，价格可不填，其他必须填写价格    
	int       volume;			//委托手数	非空      
	char      is_force_order;	//是否是强平报单	非空
	char	  gess_local_order_no[15];//本地报单号 非空 
	char	  order_send_type;	//报单发送方式 非空
	tagReqEntrOrder()
	{
		oper_flag =	0;
		memset(cust_id		,0x00,sizeof(cust_id	  ));
		memset(prod_code	,0x00,sizeof(prod_code	  ));
		memset(req_exch_code,0x00,sizeof(req_exch_code));
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		order_send_type = 0;
		price =	0.0;
		volume = 0;
		is_force_order = 0;
	}
}TReqEntrOrder,*PReqEntrOrder;

//----------------------------------------------Rsp报文接口 [onRecvRspEntrOrder] 定义
// 结构定义:委托报单响应报文体
typedef struct tagRspEntrOrder :public TRspMsg
{                              
	int       oper_flag;				//操作标志
	char	  client_serial_no[21];		//请求流水号	请求报文的标识号，可用于报单流水查询
	char      gess_local_order_no[15];	//本地报单号        
	char      gess_serial_no[33];		//国际中心报单流水号
	tagRspEntrOrder()
	{
		oper_flag =	0;
		memset(client_serial_no,0x00,sizeof(client_serial_no));
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(gess_serial_no	  ,0x00,sizeof(gess_serial_no	  ));
	}
}TRspEntrOrder,*PRspEntrOrder;

//----------------------------------------------Req报文接口 [ReqEntrCancel] 定义
// 结构定义:委托撤销请求报文体
typedef struct tagReqEntrCancel  :public TReqMsg
{
	int       oper_flag;				//操作标志	非空	默认填 1    
	char      gess_local_order_no[15];	//本地报单号	非空  
	char      order_no[17];				//交易所报单号	非空
	tagReqEntrCancel()
	{
		oper_flag =	0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(order_no			  ,0x00,sizeof(order_no			  ));
	}
}TReqEntrCancel,*PReqEntrCancel;

//----------------------------------------------Rsp报文接口 [onRecvRspEntrCancel] 定义
// 结构定义:委托撤销响应报文体
typedef struct tagRspEntrCancel :public TRspMsg
{                              
	int       oper_flag;				//操作标志 
	char      gess_local_order_no[15];	//本地报单号
	tagRspEntrCancel()
	{
		oper_flag =	0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
	}
}TRspEntrCancel,*PRspEntrCancel;

//----------------------------------------------Req报文接口 [ReqEndDayListConfirm] 定义
// 结构定义:日结单确认请求报文体
typedef struct tagReqEndDayListConfirm  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1     
	char      cust_id[13];		//黄金交易编码	非空
	char      exch_date[9];		//确认交易日期	非空
	tagReqEndDayListConfirm()
	{
		oper_flag =	0;
		memset(cust_id  ,0x00,sizeof(cust_id  ));
		memset(exch_date,0x00,sizeof(exch_date));
	}
}TReqEndDayListConfirm,*PReqEndDayListConfirm;

//----------------------------------------------Rsp报文接口 [onRecvRspEndDayListConfirm] 定义
// 结构定义:日结单确认响应报文体
typedef struct tagRspEndDayListConfirm :public TRspMsg
{                              
	int         oper_flag;		//操作标志  
	tagRspEndDayListConfirm()
	{
		oper_flag =	0;
	}
}TRspEndDayListConfirm,*PRspEndDayListConfirm;

//----------------------------------------------Req报文接口 [ReqQueryEntrFlow] 定义
// 结构定义:委托流水查询请求报文体
typedef struct tagReqQueryEntrFlow  :public TReqMsg
{
	int       oper_flag;				//操作标志	非空	默认填 1   
	char      client_serial_no[41];		//请求流水号	非空 
	char      gess_local_order_no[15];	//本地报单号 	非空
	tagReqQueryEntrFlow()
	{
		oper_flag =	0;
		memset(client_serial_no	  ,0x00,sizeof(client_serial_no	  ));
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
	}
}TReqQueryEntrFlow,*PReqQueryEntrFlow;

//----------------------------------------------Rsp报文接口 [onRecvRspQueryEntrFlow] 定义
// 结构定义:委托流水查询响应报文体
typedef struct tagRspQueryEntrFlow :public TRspMsg
{                              
	int       oper_flag;				//操作标志             
	char      order_no[17];				//交易所报单号         
	char      client_serial_no[41];		//请求流水号           
	char      gess_local_order_no[15];	//本地报单号           
	char      gess_serial_no[33];		//国际中心报单流水号   
	char      cust_id[13];				//客户代码             
	char      req_exch_code[5];			//交易代码             
	char      market_id[3];				//交易市场             
	char      prod_code[9];				//合约代码             
	double    entr_price;				//委托价格             
	int       entr_amount;				//委托数量             
	int       remain_amount;			//剩余数量             
	char      offset_flag;				//开平标志             
	char      deli_flag;				//交收标志             
	char      bs;						//买卖方向             
	double    exch_bal;					//发生金额             
	double    froz_margin;				//保证金冻结金额       
	double    exch_fare;				//交易费用             
	char      cov_type[3];				//平仓方式             
	char      src_match_no[17];			//指定仓位号           
	char      origin_order_no[17];		//原报单号             
	char      match_type[3];			//交易类型             
	char      order_send_type[3];		//报单发送方式         
	char      entr_stat;				//委托状态             
	char      cancel_flag;				//撤单标志             
	char      exch_date[9];				//交易日期             
	char      accept_time[9];			//应答时间             
	char      e_term_type[3];			//委托来源             
	char      e_branch_id[21];			//委托分支机构         
	char      e_teller_id[11];			//委托操作员           
	char      e_trader_id[11];			//委托交易员           
	char      e_exch_time[9];			//委托时间             
	char      c_term_type[3];			//撤消来源             
	char      c_teller_id[11];			//撤消操作员           
	char      c_trader_id[11];			//撤消交易员           
	char      c_exch_time[9];			//撤消时间             
	char      rsp_msg[201];				//报单响应             
	tagRspQueryEntrFlow()
	{
		oper_flag =	0;
		memset(order_no           ,0x00,sizeof(order_no           ));
		memset(client_serial_no   ,0x00,sizeof(client_serial_no   ));
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(gess_serial_no     ,0x00,sizeof(gess_serial_no     ));
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		memset(req_exch_code      ,0x00,sizeof(req_exch_code      ));
		memset(market_id          ,0x00,sizeof(market_id          ));
		memset(prod_code          ,0x00,sizeof(prod_code          ));
		entr_price = 0.0;
		entr_amount = 0;
		remain_amount = 0;
		offset_flag = 0;
		deli_flag = 0;
		bs = 0;
		exch_bal = 0.0;
		froz_margin = 0.0;
		exch_fare = 0.0;
		memset(cov_type           ,0x00,sizeof(cov_type           ));
		memset(src_match_no       ,0x00,sizeof(src_match_no       ));
		memset(origin_order_no    ,0x00,sizeof(origin_order_no    ));
		memset(match_type         ,0x00,sizeof(match_type         ));
		memset(order_send_type    ,0x00,sizeof(order_send_type    ));
		entr_stat = 0;
		cancel_flag = 0;
		memset(exch_date          ,0x00,sizeof(exch_date          ));
		memset(accept_time        ,0x00,sizeof(accept_time        ));
		memset(e_term_type        ,0x00,sizeof(e_term_type        ));
		memset(e_branch_id        ,0x00,sizeof(e_branch_id        ));
		memset(e_teller_id        ,0x00,sizeof(e_teller_id        ));
		memset(e_trader_id        ,0x00,sizeof(e_trader_id        ));
		memset(e_exch_time        ,0x00,sizeof(e_exch_time        ));
		memset(c_term_type        ,0x00,sizeof(c_term_type        ));
		memset(c_teller_id        ,0x00,sizeof(c_teller_id        ));
		memset(c_trader_id        ,0x00,sizeof(c_trader_id        ));
		memset(c_exch_time        ,0x00,sizeof(c_exch_time        ));
		memset(rsp_msg            ,0x00,sizeof(rsp_msg            ));
	}
}TRspQueryEntrFlow,*PRspQueryEntrFlow;

//----------------------------------------------Req报文接口 [ReqRefPriceApply] 定义
// 结构定义:定价市场参考价申报请求报文体
typedef struct tagReqRefPriceApply  :public TReqMsg
{
	int			oper_flag;			//操作标志	非空 默认填 1
	char    	cust_id[13];		//客户代码	非空 只能是自营客户号
	char    	game_id[11];		//场次编号	非空
	double		report_price;		//参考价格	非空
	char		prod_code[9];		//合约代码	非空
	char		exch_date[9];		//交易日期	非空
	tagReqRefPriceApply()
	{
		oper_flag =	0;
		memset(cust_id  ,0x00,sizeof(cust_id  ));
		memset(game_id  ,0x00,sizeof(game_id  ));
		report_price = 0.0;
		memset(prod_code,0x00,sizeof(prod_code));
		memset(exch_date,0x00,sizeof(exch_date));
	}
}TReqRefPriceApply,*PReqRefePricApply;

//----------------------------------------------Rsp报文接口 [onRecvRspRefPriceApply] 定义
// 结构定义:定价市场参考价申报响应报文体
typedef struct tagRspRefPriceApply :public TRspMsg
{                              
	int        oper_flag;			//操作标志    
	tagRspRefPriceApply()
	{
		oper_flag =	0;
	}
}TRspRefPriceApply,*PRspRefPriceApply;

//----------------------------------------------Req报文接口 [ReqFpEntrOrder] 定义
// 结构定义:定价市场委托申报请求报文体
typedef struct tagReqFpEntrOrder  :public TReqMsg
{
	int 		 oper_flag;				//操作标志	非空 默认填 1
	char		 cust_id[13];			//客户代码	非空
	char		 game_id[11];			//场次编号	非空
	char		 bs;					//买卖方向	非空
	char		 order_type[3];			//申报方式	非空
	int 		 volume;				//申报数量	非空 
	char		 prod_code[9];			//合约代码 	非空        
	int			 round_id;				//轮次编号	非空          
	char		 order_send_type[3];	//报单发送方式	非空      
	double		 entr_price;			//委托价格	非空          
	char		 gess_local_order_no[15];//二级系统本地报单号	非空
	char		 gess_serial_no[33];	//二级系统报单流水 	非空 
	tagReqFpEntrOrder()
	{
		oper_flag =	0;
		memset(cust_id			  ,0x00,sizeof(cust_id			  ));
		memset(game_id			  ,0x00,sizeof(game_id			  ));
		bs = 0;
		memset(order_type		  ,0x00,sizeof(order_type		  ));
		volume = 0;
		memset(prod_code		  ,0x00,sizeof(prod_code		  ));
		round_id = 0;
		memset(order_send_type	  ,0x00,sizeof(order_send_type	  ));
		entr_price = 0.0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(gess_serial_no	  ,0x00,sizeof(gess_serial_no	  ));
	}
}TReqFpEntrOrder,*PReqFpEntrOrder;

//----------------------------------------------Rsp报文接口 [onRecvRspFpEntrOrder] 定义
// 结构定义:定价市场委托申报响应报文体
typedef struct tagRspFpEntrOrder :public TRspMsg
{                              
	int      oper_flag;					//操作标志        
	char     gess_local_order_no[15];	//本地报单号  
	char     gess_serial_no[33];		//国际中心报单流水号      
	tagRspFpEntrOrder()
	{
		oper_flag =	0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(gess_serial_no	  ,0x00,sizeof(gess_serial_no	  ));
	}
}TRspFpEntrOrder,*PRspFpEntrOrder;
//----------------------------------------------Req报文接口 [ReqFpEntrCancel] 定义
// 结构定义:定价市场委托撤单请求报文体
typedef struct tagReqFpEntrCancel  :public TReqMsg
{
	int 		    oper_flag;			//操作标志	非空 默认填 1
	char			acct_no[13];		//客户号	非空  
	char		 	prod_code[9];		//合约代码	非空
	char		 	bs;					//买卖方向	非空
	tagReqFpEntrCancel()
	{
		oper_flag =	0;
		memset(acct_no	,0x00,sizeof(acct_no  ));
		memset(prod_code,0x00,sizeof(prod_code));
		bs = 0;
	}
}TReqFpEntrCancel,*PReqFpEntrCancel;

//----------------------------------------------Rsp报文接口 [onRecvRspFpEntrCancel] 定义
// 结构定义:定价市场委托撤单响应报文体
typedef struct tagRspFpEntrCancel :public TRspMsg
{                              
	int        oper_flag;				//操作标志          
	tagRspFpEntrCancel()
	{
		oper_flag =	0;
	}
}TRspFpEntrCancel,*PRspFpEntrCancel;
//----------------------------------------------Req报文接口 [ReqRefPriceQueryFlow] 定义
// 结构定义:定价市场参考价报入流水查询请求报文体
typedef struct tagReqRefPriceQueryFlow   :public TReqMsg
{
	int			oper_flag;				//操作标志	非空	默认填 1
	char    	game_id[11];			//场次编号	非空
	char		prod_code[9];			//合约代码	非空
	tagReqRefPriceQueryFlow()
	{
		oper_flag =	0;
		memset(game_id	,0x00,sizeof(game_id  ));
		memset(prod_code,0x00,sizeof(prod_code));
	}
}TReqRefPriceQueryFlow,*PReqRefePricQueryFlow;

//----------------------------------------------Rsp报文接口 [onRecvRspRefPriceQueryFlow] 定义
// 结构定义:定价市场参考价报入流水查询响应报文体
typedef struct tagRspRefPriceQueryFlow :public TRspMsg
{                              
	int       oper_flag;			//操作标志          
	int		  num_ref_price;		//参考价报入列表 记录数量
	struct tagRefPrice
	{
		char	prod_code[9];		//合约代码
		double	report_price;		//参考价格
		char    exch_date[9];		//交易日期  
		char    game_id[11];		//场次编号 
		char    member_id[7];		//会员编号 
		char	serial[19];			//流水号
		char	report_time[21];	//报入时间
	}		  * p_ref_price;		//参考价报入列表 
	tagRspRefPriceQueryFlow()
	{
		oper_flag =	0;
		num_ref_price =	0;
		p_ref_price = NULL;
	}
}TRspRefPriceQueryFlow,*PRspRefPriceQueryFlow;
//----------------------------------------------Req报文接口 [ReqFpEntrOrderQueryFlow] 定义
// 结构定义:定价市场委托申报流水查询请求报文体
typedef struct tagReqFpEntrOrderQueryFlow  :public TReqMsg
{
	int 		  oper_flag;				//操作标志	非空	默认填 1
	char		  gess_local_order_no[15];	//本地报单号	非空
	tagReqFpEntrOrderQueryFlow()
	{
		oper_flag =	0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
	}
}TReqFpEntrOrderQueryFlow,*PReqFpEntrOrderQueryFlow;

//----------------------------------------------Rsp报文接口 [onRecvRspFpEntrOrderQueryFlow] 定义
// 结构定义:定价市场委托申报流水查询响应报文体
typedef struct tagRspFpEntrOrderQueryFlow :public TRspMsg
{                              
	int		  oper_flag;		//操作标志  	
	char      exch_date[9];		//交易日期  	
	int       order_no;			//报单号    	
	char      gess_local_order_no[15];	//本地报单号	
	char      acct_no[13];		//客户号    	
	char      market_id[3];		//交易市场  	
	char      prod_code[9];		//合约代码  	
	char      game_id[11];		//场次编号  	
	int       round_id;			//委托轮次  	
	char      entr_phase;		//申报阶段  	
	char      bs;				//买卖方向  	
	double    entr_price;		//委托价格  	
	int       entr_amount;		//委托手数  	
	int       entr_weight;		//委托重量  	
	double    froz_margin;		//冻结保证金	
	double    froz_exch_fare;	//冻结手续费	
	char      entr_stat;		//委托状态  	
	char      cancel_flag;		//撤单标志  	
	char      e_term_type[3];	//委托来源  	
	char      e_trader_id[11];	//委托交易员	
	char      entr_time[21];	//委托时间  	
	char      c_term_type[3];	//撤销来源  	
	char      c_trader_id[11];	//撤销交易员	
	char      cancel_time[21];	//撤销时间  	    
	tagRspFpEntrOrderQueryFlow()
	{
		oper_flag =	0;
		memset(exch_date          ,0x00,sizeof(exch_date          ));
		order_no = 0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(member_id          ,0x00,sizeof(member_id          ));
		memset(acct_no            ,0x00,sizeof(acct_no            ));
		memset(market_id          ,0x00,sizeof(market_id          ));
		memset(prod_code          ,0x00,sizeof(prod_code          ));
		memset(game_id            ,0x00,sizeof(game_id            ));
		round_id = 0;
		entr_phase = 0;
		bs = 0;
		entr_price = 0.0;
		entr_amount = 0;
		entr_weight = 0;
		froz_margin = 0.0;
		froz_exch_fare = 0.0;
		entr_stat = 0;
		cancel_flag = 0;
		memset(e_term_type        ,0x00,sizeof(e_term_type        ));
		memset(e_trader_id        ,0x00,sizeof(e_trader_id        ));
		memset(entr_time          ,0x00,sizeof(entr_time          ));
		memset(c_term_type        ,0x00,sizeof(c_term_type        ));
		memset(c_trader_id        ,0x00,sizeof(c_trader_id        ));
		memset(cancel_time        ,0x00,sizeof(cancel_time        ));
	}
}TRspFpEntrOrderQueryFlow,*PRspFpEntrOrderQueryFlow;
//----------------------------------------------Req报文接口 [ReqTakeApply] 定义
// 结构定义:提货申请请求报文体
typedef struct tagReqTakeApply  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1      
	char      cust_id[13];		//客户代码	非空      
	char      variety_id[4];	//交割品种代码	非空  
	int       app_amount;		//提货标准重量	非空  
	char      city_code[7];		//提货城市 	非空     
	char      stor_id[5];		//仓库代码	非空      
	char      take_man[21];		//提货人	非空        
	char      cert_type_id;		//提货人证件类型	非空	
	char      cert_num[21];		//提货人证件号码	非空
	char      app_pwd[255];		//提货密码	非空	明文      
	char      app_record[11];	//申请录入人    
	int       self_draw;		//自提重量	非空   
	int       trade_draw;		//交提重量 	非空     
	char      gold_forword;		//实物流向 	非空     
	char      remark[255];		//备注   	非空       
	char      take_date[9];		//提货日期 	非空     
	char      lend_check_no[11];//租借登记编号 
	tagReqTakeApply()
	{
		oper_flag =	0;
		memset(cust_id         ,0x00,sizeof(cust_id         ));
		memset(variety_id      ,0x00,sizeof(variety_id      ));
		app_amount = 0; 
		memset(city_code       ,0x00,sizeof(city_code       ));
		memset(stor_id         ,0x00,sizeof(stor_id         ));
		memset(take_man        ,0x00,sizeof(take_man        ));
		cert_type_id = 0;
		memset(cert_num        ,0x00,sizeof(cert_num        ));
		memset(app_pwd         ,0x00,sizeof(app_pwd         ));
		memset(app_record      ,0x00,sizeof(app_record      ));
		self_draw = 0;
		trade_draw = 0;
		gold_forword = 0;
		memset(remark          ,0x00,sizeof(remark          ));
		memset(take_date       ,0x00,sizeof(take_date       ));
		memset(lend_check_no   ,0x00,sizeof(lend_check_no   ));
	}
}TReqTakeApply,*PReqTakeApply;

//----------------------------------------------Rsp报文接口 [onRecvRspTakeApply] 定义
// 结构定义:提货申请响应报文体
typedef struct tagRspTakeApply :public TRspMsg
{                              
	int      oper_flag;					//操作标志        
	char     gess_local_sheet_no[17];	//本地提货单编号  
	char     sheet_no[15];				//提货单编号      
	char     cust_id[13];				//客户代码        
	char     send_stat;					//发送状态        
	char     stat;						//提货状态        
	double   take_margin;				//提货保证金
	char	 is_other_take;				//是否是异地提货
	char     app_start_date[9];			//申请提货开始日期
	char     app_end_date[9];			//申请提货截止日期
	char     variety_id[4];				//交割品种代码    
	int      app_amount;				//提货标准重量    
	char     draw_type;					//提货类型        
	int      self_draw;					//自提重量        
	int      trade_draw;				//交提重量        
	tagRspTakeApply()
	{
		oper_flag =	0;
		memset(gess_local_sheet_no,0x00,sizeof(gess_local_sheet_no));
		memset(sheet_no           ,0x00,sizeof(sheet_no           ));
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		send_stat = 0;
		stat = 0;
		take_margin = 0.0;
		is_other_take = 0;
		memset(app_start_date     ,0x00,sizeof(app_start_date     ));
		memset(app_end_date       ,0x00,sizeof(app_end_date       ));
		memset(variety_id         ,0x00,sizeof(variety_id         ));
		app_amount = 0; 
		draw_type = 0;
		self_draw = 0;
		trade_draw = 0;
	}
}TRspTakeApply,*PRspTakeApply;

//----------------------------------------------Req报文接口 [ReqTakeApplyCancel] 定义
// 结构定义:提货申请撤销请求报文体
typedef struct tagReqTakeApplyCancel :public TReqMsg 
{
	int       oper_flag;				//操作标志	非空	默认填 1       
	char      gess_local_sheet_no[17];	//本地提货单编号	非空
	char      sheet_no[15];				//提货单编号	非空    
	char      cust_id[13];				//客户代码	非空      
	char      take_man[21];				//提货人    非空
	char      take_pwd[255];				//提货密码	非空	明文    
	tagReqTakeApplyCancel()
	{
		oper_flag =	0;
		memset(gess_local_sheet_no,0x00,sizeof(gess_local_sheet_no));
		memset(sheet_no           ,0x00,sizeof(sheet_no           ));
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		memset(take_man           ,0x00,sizeof(take_man           ));
		memset(take_pwd           ,0x00,sizeof(take_pwd           ));
	}
}TReqTakeApplyCancel,*PReqTakeApplyCancel;

//----------------------------------------------Rsp报文接口 [onRecvRspTakeApplyCancel] 定义
// 结构定义:提货申请撤销响应报文体
typedef struct tagRspTakeApplyCancel :public TRspMsg
{                              
	int       oper_flag;				//操作标志      
	char      gess_local_sheet_no[17];	//本地提货单编号
	char      sheet_no[15];				//提货单编号    
	char      cust_id[13];				//客户代码      
	char      stat;						//提货状态      
	tagRspTakeApplyCancel()
	{
		oper_flag =	0;
		memset(gess_local_sheet_no,0x00,sizeof(gess_local_sheet_no));
		memset(sheet_no           ,0x00,sizeof(sheet_no           ));
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		stat = 0;
	}
}TRspTakeApplyCancel,*PRspTakeApplyCancel;

//----------------------------------------------Req报文接口 [ReqQueryTakeList] 定义
// 结构定义:提货单查询请求报文体
typedef struct tagReqQueryTakeList  :public TReqMsg
{
	int       oper_flag;				//操作标志	非空	默认填 1       
	char      gess_local_sheet_no[17];	//本地提货单编号	非空
	char      sheet_no[15];				//提货单编号	
	tagReqQueryTakeList()
	{
		oper_flag =	0;
		memset(gess_local_sheet_no,0x00,sizeof(gess_local_sheet_no));
		memset(sheet_no           ,0x00,sizeof(sheet_no           ));
	}
}TReqQueryTakeList,*PReqQueryTakeList;

//----------------------------------------------Rsp报文接口 [onRecvRspQueryTakeList] 定义
// 结构定义:提货单查询响应报文体
typedef struct tagRspQueryTakeList :public TRspMsg
{					               
	int       oper_flag;				//操作标志        
	char      gess_local_sheet_no[17];	//本地提货单编号  
	char      sheet_no[15];				//提货单编号      
	char      cust_id[13];				//客户代码        
	char      variety_id[4];			//交割品种代码    
	int       app_amount;				//提货标准重量    
	char      draw_type;				//提货类型        
	int       self_draw;				//自提重量        
	int       trade_draw;				//交提重量        
	char      city_code[7];				//提货城市        
	char      stor_id[5];				//仓库代码        
	char      take_man[21];				//提货人          
	char      cert_type_id;			//提货人证件类型	  
	char      cert_num[21];				//提货人证件号码  
	char      app_record[32];			//申请录入人      
	char      app_date[9];				//申请物理日期    
	char      app_time[9];				//申请物理时间    
	char      app_exch_date[9];			//申请交易日期    
	char      app_start_date[9];		//申请提货开始日期
	char      app_end_date[9];			//申请提货截止日期
	char      due_take_date[9];			//预备提货日期    
	char      stat;						//提货状态        
	char      cancel_date[9];			//撤消物理日期    
	char      cancel_time[9];			//撤消时间        
	char      cancel_exch_date[9];		//撤消交易日期    
	char      cancel_record[21];		//撤消录入人      
	char      send_stat;				//发送状态        
	double    take_margin;				//提货保证金      
	char      is_other_take;			//是否异地提货    
	char      take_affirm;				//异地提货确认    
	char      take_rsp_code[21];		//提货响应代码        
	char      take_rsp_msg[201];		//提货响应信息        
	char      gold_forword;				//实物流向        
	char      remark[255];				//备注            
	tagRspQueryTakeList()
	{
		oper_flag =	0;
		memset(gess_local_sheet_no,0x00,sizeof(gess_local_sheet_no));
		memset(sheet_no           ,0x00,sizeof(sheet_no           ));
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		memset(variety_id         ,0x00,sizeof(variety_id         ));
		app_amount = 0;
		draw_type = 0;
		self_draw = 0;
		trade_draw = 0;
		memset(city_code          ,0x00,sizeof(city_code          ));
		memset(stor_id            ,0x00,sizeof(stor_id            ));
		memset(take_man           ,0x00,sizeof(take_man           ));
		cert_type_id = 0;
		memset(cert_num           ,0x00,sizeof(cert_num           ));
		memset(app_record         ,0x00,sizeof(app_record         ));
		memset(app_date           ,0x00,sizeof(app_date           ));
		memset(app_time           ,0x00,sizeof(app_time           ));
		memset(app_exch_date      ,0x00,sizeof(app_exch_date      ));
		memset(app_start_date     ,0x00,sizeof(app_start_date     ));
		memset(app_end_date       ,0x00,sizeof(app_end_date       ));
		memset(due_take_date      ,0x00,sizeof(due_take_date      ));
		stat = 0;
		memset(cancel_date        ,0x00,sizeof(cancel_date        ));
		memset(cancel_time        ,0x00,sizeof(cancel_time        ));
		memset(cancel_exch_date   ,0x00,sizeof(cancel_exch_date   ));
		memset(cancel_record      ,0x00,sizeof(cancel_record      ));
		send_stat = 0;
		take_margin = 0.0;
		is_other_take = 0;
		take_affirm = 0;
		memset(take_rsp_code      ,0x00,sizeof(take_rsp_code      ));
		memset(take_rsp_msg       ,0x00,sizeof(take_rsp_msg       ));
		gold_forword = 0;
		memset(remark             ,0x00,sizeof(remark             ));
	}
}TRspQueryTakeList,*PRspQueryTakeList;

//----------------------------------------------Req报文接口 [ReqTransferDataDownload] 定义
// 结构定义:银行出入金对账数据下载请求报文体
typedef struct tagReqTransferDataDownload  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1 
	char      exch_date[9];		//交易日期	非空
	char      branchID[21];		//分支机构	非空
	tagReqTransferDataDownload()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(branchID ,0x00,sizeof(branchID ));
	}
}TReqTransferDataDownload,*PReqTransferDataDownload;

//----------------------------------------------Rsp报文接口 [onRecvRspTransferDataDownload] 定义
// 结构定义:银行出入金对账数据下载响应报文体
typedef struct tagRspTransferDataDownload :public TRspMsg
{                              
	int         oper_flag;		//操作标志 
	int			num_checksum;	//对账流水汇总条数
	struct tagAlmChecksum		 
	{
		int		sum_num;		//总笔数
		double	sum_bal;		//总金额
		int		in_num;			//转入笔数
		double	in_bal;			//转入金额
		int		out_num;		//转出笔数
		double	out_bal;		//转出金额
		char	currency_id;	//币种   
	}			* p_checksum;	//对账流水汇总
	
	int			num_checkdetail;//对账流水明细总条数
	struct tagAlmCheckdetail	
	{
		char	exch_date[9];	//交易日期
		char	bank_seq[33];	//银行流水号
		char	gess_serial_no[33];		//国际中心流水号
		char	client_serial_no[21];	//请求流水号
		char	account_no[33]; //银行账号	
		char    cust_no[13];	//客户号 
		char    f_busi_type;	//业务类型
		char    access_way;		//存取标志
		double	exch_bal;		//交易金额
		char	currency_id;	//币种  
	}			* p_checkdetail;//对账流水明细 
	tagRspTransferDataDownload()
	{
		oper_flag =	0;
		num_checksum =	0;
		p_checksum = NULL;
		num_checkdetail =	0;
		p_checkdetail =	NULL;
	}
}TRspTransferDataDownload,*PRspTransferDataDownload;

//----------------------------------------------Req报文接口 [ReqLiquDataDownload] 定义
// 结构定义:日终清算数据下载请求报文体
typedef struct tagReqLiquDataDownload  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1
	char      exch_date[9];		//交易日期	非空
	char      branchID[21];		//分支机构	非空
	tagReqLiquDataDownload()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(branchID ,0x00,sizeof(branchID ));
	}
}TReqLiquDataDownload,*PReqLiquDataDownload;

//----------------------------------------------Rsp报文接口 [onRecvRspLiquDataDownload] 定义
// 结构定义:日终清算数据下载响应报文体
typedef struct tagRspLiquDataDownload :public TRspMsg
{                              
	int       oper_flag;				//操作标志      
	char      newxml_file_addr[1024];	//NewXML文件地址
	char	  sftp_user_name[21];		//操作员姓名
	char	  sftp_pwd[61];				//登录密码
	tagRspLiquDataDownload()
	{
		oper_flag =	0;
		memset(newxml_file_addr,0x00,sizeof(newxml_file_addr));
		memset(sftp_user_name  ,0x00,sizeof(sftp_user_name  ));
		memset(sftp_pwd		   ,0x00,sizeof(sftp_pwd	    ));
	}
}TRspLiquDataDownload,*PRspLiquDataDownload;

//----------------------------------------------Req报文接口 [ReqFundCheckDataDownload] 定义
// 结构定义:日终对账汇总数据下载请求报文体
typedef struct tagReqFundCheckDataDownload  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1
	char      exch_date[9];		//交易日期	非空
	char      branchID[21];		//分支机构	非空
	tagReqFundCheckDataDownload()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(branchID ,0x00,sizeof(branchID ));
	}
}TReqFundCheckDataDownload,*PReqFundCheckDataDownload;

//----------------------------------------------Rsp报文接口 [onRecvRspFundCheckDataDownload] 定义
// 结构定义:日终对账汇总数据下载响应报文体
typedef struct tagRspFundCheckDataDownload :public TRspMsg
{                              
	int     oper_flag;				//操作标志  
	int		num_forward_member_posi;//现货即期会员持仓总条数
	struct tagForwardMemberPosi
	{
		char	exch_date[9];	//日期
		char	member_id[7];	//会员代码
		char	instID[9];		//合约代码 
		char	due_date[9];	//到期日
		int		net_amt;		//净持仓量
		int		curr_long_amt;	//多头持仓量
		int		curr_short_amt;	//空头持仓量
		double	long_posi_bal;	//多头持仓金额
		double	short_posi_bal;	//空头持仓金额
		int		open_long_amt;	//今日多头开仓
		int		open_short_amt;	//今日空头开仓
		int		cov_long_amt;	//今日多头平仓
		int		cov_short_amt;	//今日空头平仓
		double	float_surplus;	//浮动盈亏
		double	cov_surplus;	//平仓盈亏
		double	fee;			//手续费
		double	margin;			//保证金
		double	settle_price;	//结算价
	}		* p_forward_member_posi;//现货即期会员持仓
	int		num_defer_member_posi;	//延期会员持仓总条数
	struct tagDeferMemberPosi
	{
		char	exch_date[9];	//日期
		char	member_id[7];	//会员代码
		char	instID[9];		//合约代码 
		int		curr_long_amt;	//多头持仓量
		int		curr_short_amt;	//空头持仓量
		int		open_long_amt;	//今日多头开仓
		int		open_short_amt;	//今日空头开仓
		int		cov_long_amt;	//今日多头平仓
		int		cov_short_amt;	//今日空头平仓
		double	exch_surplus;	//交易盈亏
		double	fee;			//手续费
		double	margin;			//保证金
		double	settle_price;	//结算价
		double	defer_fee;		//递延费
	}		* p_defer_member_posi;	//延期会员持仓
	int		num_member_capital;		//会员资金总条数
	struct tagMemberCapital
	{
		char	exch_date[9];	//日期
		char	member_id[7];	//会员代码
		char	acct_type;	//账户类型
		double	curr_can_get;	//币种可提资金  
		double	last_balance;	//上日结算准备金余额 	
		double	last_b_margin;	//上日占用保证金
		double	last_base_margin;	//上日基础保证金
		double	last_reserve;	//上日铂金冻结金额
		double	last_long_froz;	//上日手工冻结资金
		double	last_forward_froz;	//上日远期盈亏冻结资金
		double	last_deli_prepare;	//上日白银货款冻结
		double	last_deli_margin;	//上日交割保证金占用
		double	deli_prepare;	//白银货款冻结
		double	deli_margin;	//交割保证金占用
		double	balance;		//当日结算准备金余额
		double	real_b_margin;	//当日占用保证金
		double	base_margin;	//当日基础保证金
		double	real_reserve;	//当日铂金冻结金额
		double	day_long_froz;	//当日手工冻结资金
		double	day_forward_froz;	//当日远期盈亏冻结资金
		double	profit;			//当日盈亏
		double	today_inbal;	//当日入金
		double	today_outbal;	//当日出金
		double	real_sell;		//收到的货款
		double	real_buy;		//支付的货款
		double	misc_fee;		//费用
		double	interest;		//利息
		double	bail;			//追加保证金
	}		* p_member_capital;	//会员资金
	int		num_fee_summary;	//会员清算费用合计总条数  
	struct tagFeeSummary
	{
		char	exch_date[9];	//日期
		char	member_id[7];	//会员代码
		double	fee;			//手续费
		double	delivery_fee;	//交割手续费  
		double	storage_fee;	//仓储费 	
		double	trans_fee;		//运保费
		double	overdue_fee;	//超期费
		double	impawn_fee;		//质押登记费
		double	loadreg_fee;	//租借登记费
		double	breach_fee;		//违约金
		double	defer_fee;		//递延费
		double	profit;			//盈亏
		double	amount;			//费用合计=交易所交易手续费+交割费+仓储费+运保费+超期补偿费+质押登记费+租借登记费+违约金+递延费+盈亏
	}		* p_fee_summary;	//会员清算费用合计
	int		num_settle_summary;	//会员二次清算费用合计总条数 
	struct tagSettleSummary
	{
		char	exch_date[9];	//日期
		char	member_id[7];	//会员代码
		double	diff;			//重量溢短
		double	vari_agio;		//品种升贴水  
		double	item_agio;		//条块升贴水 	
		double	sum_agio;		//升贴水合计
	}		* p_settle_summary;
	tagRspFundCheckDataDownload()
	{
		oper_flag =	0;
		num_forward_member_posi =	0;
		p_forward_member_posi = NULL;
		num_defer_member_posi =	0;
		p_defer_member_posi = NULL;
		num_member_capital =	0;
		p_member_capital = NULL;
		num_fee_summary =	0;
		p_fee_summary = NULL;
		num_settle_summary =	0;
		p_settle_summary =	NULL;
	}
}TRspFundCheckDataDownload,*PRspFundCheckDataDownload;

//----------------------------------------------Req报文接口 [ReqInterestDataDownload] 定义
// 结构定义:日终计息数据下载请求报文体
typedef struct tagReqInterestDataDownload  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1
	char      exch_date[9];		//交易日期	非空
	char      branchID[21];		//分支机构	非空
	tagReqInterestDataDownload()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(branchID ,0x00,sizeof(branchID ));
	}
}TReqInterestDataDownload,*PReqInterestDataDownload;

//----------------------------------------------Rsp报文接口 [onRecvRspInterestDataDownload] 定义
// 结构定义:日终计息数据下载响应报文体
typedef struct tagRspInterestDataDownload :public TRspMsg
{                              
	int       oper_flag;			//操作标志    
	int       num_pre_interest;		//预计利息数据总条数   
	struct tagPreInterest
	{
		char		seq_no[19];		//流水号 
		char		member_id[7];	//会员编号
		char		acct_no[16];	//客户号
		char		cust_id[16];	//客户代码
		char		inte_type[3];	//利息类型
		double		inte_integral;	//利息积数
		double		inte_rate;		//利息利率
		double		inte_tax_rate;	//利息税利率
		double		incr_inte;		//入账利息
		double		incr_inte_tax;	//入账利息税
		char		currency_id;	//币种
		char		o_term_type[3];	//创建来源
	}		* p_pre_interest;		//预计利息数据
	int		num_interest;			//利息数据总条数  
	struct tagInterest
	{
		char		seq_no[19];		//流水号 
		char		member_id[7];	//会员编号
		char		acct_no[16];	//客户号
		char		cust_id[16];	//客户代码
		double		incr_inte;		//入账利息
		double		incr_inte_tax;	//入账利息税
		char		currency_id;	//币种
		char		o_term_type[3];	//创建来源
	}		* p_interest;	//利息数据
	tagRspInterestDataDownload()
	{
		oper_flag =	0;
		num_pre_interest =	0;
		p_pre_interest = NULL;
		num_interest =	0;
		p_interest = NULL;
	}
}TRspInterestDataDownload,*PRspInterestDataDownload;

//----------------------------------------------Req报文接口 [ReqQuerySigexNotice] 定义
// 结构定义:国际中心公告信息查询请求报文体
typedef struct tagReqQuerySigexNotice  :public TReqMsg
{
	int       oper_flag;		//操作标志	非空	默认填 1    
	char      seq_no[11];		//公告序号    
	char      title[41];		//公告标题   可模糊匹配
	char      s_exch_date[9];	//起始公告日期	非空
	char      e_exch_date[9];	//结束公告日期	非空
	tagReqQuerySigexNotice()
	{
		oper_flag =	0;
		memset(seq_no,0x00,sizeof(seq_no));
		memset(title ,0x00,sizeof(title ));
		memset(s_exch_date,0x00,sizeof(s_exch_date));
		memset(e_exch_date ,0x00,sizeof(e_exch_date ));
	}
}TReqQuerySigexNotice,*PReqQuerySigexNotice;

//----------------------------------------------Rsp报文接口 [onRecvRspQuerySigexNotice] 定义
// 结构定义:国际中心公告信息查询响应报文体
typedef struct tagRspQuerySigexNotice :public TRspMsg
{                              
	int       oper_flag;	//操作标志
	int		  num_result;	//查询结果总条数
	struct tagResult
	{
		char      seq_no[11];	//公告序号    
		char      title[41];	//公告标题 
		char	  content[256];//内容
		char	  announcer[16];//发布人
		char	  exch_date[9];	//公告日期
		char	  exch_time[9];	//公告时间
	}		  * p_result;	//查询结果
	tagRspQuerySigexNotice()
	{
		oper_flag =	0;
		num_result =	0;
		p_result = NULL;
	}
}TRspQuerySigexNotice,*PRspQuerySigexNotice;

//----------------------------------------------Req报文接口 [ReqSigexBasicDataDownload] 定义
// 结构定义:国际中心基础数据下载请求报文体
typedef struct tagReqSigexBasicDataDownload  :public TReqMsg
{
	int       oper_flag;                   //操作标志	非空	默认填 1                           
	char      city_info;                   //城市代码信息表    
	char      spec_date;                   //节假日配置表      
	char      prod_code_def;               //合约代码表        
	char      variety;                     //交割品种表        
	char      variety_substitue;           //替代交割品种表    
	char      fare_model_def;              //会员费率模板信息  
	char      wh_fare_model;               //仓储费用模板信息  
	char      defer_over_fee;              //超期费率表        
	char      defer_fee;                   //延期递延补偿费表  
	char      rmb_day_interest_data;       //人民币利率表      
	char      take_margin_para;            //提货保证金参数表  
	char      branch_fare_interval;        //分支机构费率区间表
	char      stor_info;                   //仓库信息表               
	char      branchID[21];                //分支机构	非空   
	tagReqSigexBasicDataDownload()
	{
		oper_flag =	'0';
		city_info =	'0';
		spec_date =	'0';
		prod_code_def =	'0';
		variety =	'0';
		variety_substitue =	'0';
		fare_model_def =	'0';
		wh_fare_model =	'0';
		defer_over_fee =	'0';
		defer_fee =	'0';
		rmb_day_interest_data =	'0';
		take_margin_para =	'0';
		branch_fare_interval =	'0';
		stor_info =	'0';
		memset(branchID,0x00,sizeof(branchID));
	}
}TReqSigexBasicDataDownload,*PReqSigexBasicDataDownload;

//----------------------------------------------Rsp报文接口 [onRecvRspSigexBasicDataDownload] 定义
// 结构定义:国际中心基础数据下载响应报文体
typedef struct tagRspSigexBasicDataDownload :public TRspMsg
{                              
	int       oper_flag;					//操作标志              
	//城市代码信息表  
	int		  num_city_info;				//城市代码信息条数
	struct tagCityInfo
	{
		char		city_code[7];			//城市代码
		char		city_name[51];			//城市名称
	}		  * p_city_info;			    //城市代码信息 
	//节假日配置表 
	int			num_spec_date;				//节假日配置记录数量
	struct		tagSpecDate 
	{
		char		spec_date[9];			//交易日期
		char		date_type[3];			//日期类型
	}		  * p_spec_date;				//节假日配置
	//合约代码表 
	int			num_prod_code_def;			//合约代码记录数量
	struct		tagProdCodeDef 
	{
		char		prod_code[11];			//合约代码
		char		prod_name[32];			//合约名称
		char		bourse_id[3];			//交易所编号
		char		currency_id;			//币种 
		char		market_id[3];			//交易市场类型 
		char		variety_type[3];		//品种类别 
		char		variety_id[7];			//交割品种代码	
		double		tick;             		//最小变动价位 
		char		t0_sign[3];				//是否T+0   
		char		bail_sign[3];			//是否保证金模式
		double		bail_rate;        		//保证金比例  
		char		limit_sign[3];			//是否涨跌停限制 
		double		upper_limit_value;		//涨停板率  
		double		lower_limit_value;		//跌停板率 
		char		active_flag;       		//活跃标志 
		char		inst_stat[3];			//合约交易状态
		double		ref_price;        		//参考价 
		double		recv_rate;        		//卖方收款比例 
		char		busi_mode[3];			//交收模式 
		int			max_hand;        		//最大申报数量
		int			min_hand;         		//最小申报数量 
		char		exch_unit[3];			//交易单位
		double		measure_unit;     		//计量单位 
		char		entr_way_str[11];		//委托方式 
		char		fare_sign;         		//是否手续费 
		double		fare_value;       		//手续费值
		char		fare_model_id[7];		//费用模板
		char		due_date[9];			//到期日 
		int			deli_days;        		//交割间隔天数   
	}			* p_prod_code_def;			//合约代码信息
	//交割品种表 
	int		    num_variety;                //交割品种表 记录数量
	struct	tagVariety
	{
		char		variety_ID[4];			//交割品种代码  
		char		name[41];				//交割品种全称 
		char		abbr[21];				//简称 
		char		variety_type[3];		//品种类别  
		double		min_pickup;  			//最小提货数量 
		double		pickup_base; 			//提货步长 
		char		weight_unit[3];			//重量单位 
		char		destroy_flag[3];		//注销标志 
	}			* p_variety;			//交割品种信息   
	//替代交割品种表 
	int			num_variety_substitue;		//替代交割品种 信息条数
	struct	tagVarietySubstitue
	{
		char		prod_code[11];			//合约代码
		int			seq_no;    				//交割顺序
		char		variety_id[4];			//交割品种代码
		double		diff_amt;  				//差价  
	}			* p_variety_substitue;	//替代交割品种信息 
	//会员费率模板信息 
	int			num_fare_model_def;			//会员费率模板信息 数量
	struct		tagFareModelDef
	{
		char		fare_model_id[7];		//交易费用模板ID 
		char		fare_model_name[101];	//交易费用模板名称  
		char		fare_model_type[3];		//模板类型      
		char		contain_bourse[3];		//是否包含交易所费用 
		char		branch_id[21];			//所属代理机构  
		//char		o_term_type[3];			//创建来源    
		//char		o_teller_id[11];		//创建操作员号 
		//char		o_date[9];				//创建日期  
		char		m_term_type[3];			//修改来源  
		char		m_teller_id[11];		//修改操作员号
		//char		m_date[9];				//修改日期
	}			* p_fare_model_def;		//会员费率模板信息
	//仓储费用模板信息   
	int			num_wh_fare_model;		    //仓储费用模板信息 数量
	struct	tagWhFareModel
	{
		char		fare_model_id[7];		//费用模板ID 
		char		stor_id[5];				//仓储代码 
		char		variety_id[7];			//交割品种  
		char		fare_type_id[4];		//费用类型ID 
		char		fare_mode[3];			//收费模式
		double		fare_value;   			//费率值
	}			* p_wh_fare_model;//仓储费用模板信息
	//超期费率表 
	int         num_defer_over_fee;          //超期费率表  记录数量
	struct  tagDeferOverFee
	{
		char		prod_code[11];			//合约代码  
		int 		seq_no;       			//序号
		char 		start_day[9];    		//起始交易日 
		char 		end_day[9];      		//结束交易日
		double		fee_rate;     			//费率 
	}			* p_defer_over_fee;		//超期费率表 记录
	//延期递延补偿费表  
	int         num_defer_fee;          //延期递延补偿费表  记录数量
	struct  tagDeferFee
	{
		char		exch_date[9];			//交易日期 
		char		prod_code[11];			//合约代码        
		char		pay_direction[3];		//支付方向    
		double		fee_rate;         		//费率 
	}			* p_defer_fee;			//延期递延补偿费表 记录
	//人民币利率表      
	int         num_rmb_day_interest_rate;//人民币利率表  记录数量
	struct  tagRmbDayInterestRate
	{
		char		acct_type;			//账户类型  
		int			seq_no;              	//利率序号
		char		s_valid_exch_date[9];	//起始生效日期   
		char		e_valid_exch_date[9];	//结束生效日期
		double		inte_rate;        		//利息利率 
		double		inte_tax_rate;    		//利息税利率 
		double		puni_rate;        		//罚息利率
	}			* p_rmb_day_interest_rate;//人民币利率表 记录
	//提货保证金参数表   
	int         num_take_margin_para;          //提货保证金参数表  记录数量
	struct  tagTakeMarginPara
	{
		char		variety_ID[4];			// 交割品种代码
		double		price_offset_rate;    	// 价格预期 
		double		unit_max_diff;          // 每千克最大溢短量（克）   
	}			* p_take_margin_para;	//提货保证金参数表 记录
	//分支机构费率区间表    
	int         num_branch_interval;    //分支机构费率区间表  记录数量
	struct  tagBranchInterval
	{
		char		branch_id[21];			// 代理机构 
		char		prod_code[11];			// 合约代码  
		char		fare_type_id[4];		// 费率类型ID  
		char		fare_mode[3];			// 收费模式 
		double		min_value;       		// 最小费率值
		double		max_value;             	// 最大费率值 
	}			* p_branch_interval;	//分支机构费率区间表 记录
	//仓库信息表      
	int         num_stor_info;          //仓库信息表  记录数量
	struct  tagStorInfo
	{
		char		stor_id[5];				// 仓库代码
		char		stor_name[61];			// 仓库名称
		char		addr[201];				// 仓库地址
		char		tel[32];				// 联系电话
		char		fax[32];				// 联系传真
		char		link_man[32];			// 联系人 
		char		zip_code[11];			// 邮编 
		char		use_variety_type[201];	// 支持使用的交割品种
		char		is_take[3];				// 是否允许提货 
		char		stor_name_e[101];		// 仓库名称
	}			* p_stor_info;			//仓库信息表 记录
	//仓库与城市对应信息表表
	int         num_stor_city_info;     //仓库与城市对应信息表表  记录数量
	struct  tagStorCityInfo
	{
		char		stor_id[5];				// 仓库代码 
		char		city_code[5];			// 城市代码
		char		is_default_stor[3];		// 是否默认提货仓库 
	}			* p_stor_city_info;		//仓库与城市对应信息表表 记录
	//费用模板明细表   
	int         num_fare_model_detail;  //费用模板明细表  记录数量
	struct  tagFareModelDetail
	{
		char		fare_model_id[7];		// 费用模板ID
		char		prod_code[11];			// 合约代码 
		char		fare_type_id[4];		// 费用类型ID 
		char		fare_mode[3];			// 收费模式
		double		fare_value;       		// 费率值 
	}			* p_fare_model_detail;	//费用模板明细表 记录
	tagRspSigexBasicDataDownload()
	{
		oper_flag =	0;
		num_city_info =	0;
		p_city_info = NULL;
		num_spec_date =	0;
		p_spec_date = NULL;
		num_prod_code_def =	0;
		p_prod_code_def = NULL;
		num_variety =	0;
		p_variety = NULL;
		num_variety_substitue =	0;
		p_variety_substitue = NULL;
		num_fare_model_def =	0;
		p_fare_model_def = NULL;
		num_wh_fare_model =	0;
		p_wh_fare_model = NULL;
		num_defer_over_fee =	0;
		p_defer_over_fee = NULL;
		num_defer_fee =	0;
		p_defer_fee = NULL;
		num_rmb_day_interest_rate =	0;
		p_rmb_day_interest_rate = NULL;
		num_take_margin_para =	0;
		p_take_margin_para = NULL;
		num_branch_interval =	0;
		p_branch_interval = NULL;
		num_stor_info =	0;
		p_stor_info = NULL;
		num_stor_city_info =	0;
		p_stor_city_info = NULL;
		num_fare_model_detail =	0;
		p_fare_model_detail = NULL;
	}
}TRspSigexBasicDataDownload,*PRspSigexBasicDataDownload;

//----------------------------------------------Req报文接口 [ReqSigexMemFareSyn] 定义
// 结构定义:中心会员费率同步维护请求报文体
typedef struct tagReqSigexMemFareSyn  :public TReqMsg
{
	int         oper_flag;               //操作标志		非空   1：增加，2：修改，3：删除       
	char        fare_model_id[21];       //交易费用模板ID	非空    
	char        fare_model_name[101];    //交易费用模板名称	非空  
	char        fare_model_type[3];      //模板类型			非空          
	char        contain_bourse;          //是否包含交易所费用	非空	固定填：'0'
	char        gess_branch_id[21];      //所属分支机构 	非空     
	//交易费用明细列表   
	int         num_fare_info_list;      //交易费用明细列表	非空  记录数量 
	struct  tagFareInfoList
	{   
		char			prod_code[11];		// 合约代码 
		char			fare_type_id[4];	// 费用类型ID 
		char			fare_mode[3];		// 收费模式
		double			fare_value;       	// 费率值
	}			* p_fare_info_list;		//交易费用明细列表 记录
	tagReqSigexMemFareSyn()
	{
		oper_flag =	0;
		memset(fare_model_id  ,0x00,sizeof(fare_model_id  ));
		memset(fare_model_name,0x00,sizeof(fare_model_name));
		memset(fare_model_type,0x00,sizeof(fare_model_type));
		contain_bourse = 0;
		memset(gess_branch_id ,0x00,sizeof(gess_branch_id ));
		num_fare_info_list = 0;
		p_fare_info_list = NULL;
	}
}TReqSigexMemFareSyn,*PReqSigexMemFareSyn;

//----------------------------------------------Rsp报文接口 [onRecvRspSigexMemFareSyn] 定义
// 结构定义:中心会员费率同步维护响应报文体
typedef struct tagRspSigexMemFareSyn :public TRspMsg
{                              
	int             oper_flag;               //操作标志	1：增加，2：修改，3：删除
	tagRspSigexMemFareSyn()
	{
		oper_flag =	0;
	}
}TRspSigexMemFareSyn,*PRspSigexMemFareSyn;

//----------------------------------------------Req报文接口 [ReqSpecialAcctFareSyn] 定义
// 结构定义:客户特殊费率修改同步维护请求报文体
typedef struct tagReqSpecialAcctFareSyn  :public TReqMsg
{
	int           oper_flag;               //操作标志	非空   默认填 1     
	char          cust_id[13];             //客户代码 	非空       
	//个人费用明细列表
	int         num_acct_fare_info;        //个人费用明细列表	非空  记录数量
	struct  tagAcctFareInfo
	{   
		char			prod_code[11];			// 合约代码            
		char			fare_type_id[4];		// 费用类型ID           
		char			fare_mode[3];			// 收费模式                       
		double			fare_value;       		// 费率值   
	}			* p_acct_fare_info;			//个人费用明细列表 记录
	tagReqSpecialAcctFareSyn()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
		num_acct_fare_info = 0;
		p_acct_fare_info = NULL;
	}
}TReqSpecialAcctFareSyn,*PReqSpecialAcctFareSyn;

//----------------------------------------------Rsp报文接口 [onRecvRspSpecialAcctFareSyn] 定义
// 结构定义:客户特殊费率修改同步维护响应报文体
typedef struct tagRspSpecialAcctFareSyn  :public TRspMsg
{                              
	int             oper_flag;               //操作标志  
	tagRspSpecialAcctFareSyn()
	{
		oper_flag =	0;
	}
}TRspSpecialAcctFareSyn,*PRspSpecialAcctFareSyn;











//----------------------------------------------------------------------广播报文----------------------------------------------------------------------------------------

//行情类
//----------------------------------------------报文接口 [onRecvSpotQuotation] 定义
// 结构定义:
typedef struct tagSpotQuotation
{
	char      instID[9];    //合约代码      
	char      name [13];     //合约名称        
	double    lastClose;     //昨收盘   
	double    open;          //开盘价          
	double    high;          //最高价          
	double    low;           //最低价          
	double    last;          //最新价          
	double    close;         //收盘价          
	double    bid1;          //买价1           
	int		  bidLot1;       //买量1           
	double    bid2;          //买价2           
	int		  bidLot2;       //买量2           
	double    bid3;          //买价3           
	int		  bidLot3;       //买量3           
	double    bid4;          //买价4           
	int       bidLot4;       //买量4           
	double    bid5;          //买价5           
	int       bidLot5;       //买量5           
	double    ask1;          //卖价1           
	int		  askLot1;       //卖量1           
	double    ask2;          //卖价2           
	int		  askLot2;       //卖量2           
	double    ask3;          //卖价3           
	int		  askLot3;       //卖量3           
	double    ask4;          //卖价4           
	int		  askLot4;       //卖量4           
	double    ask5;          //卖价5           
	int		  askLot5;       //卖量5           
	int       volume;        //成交量（双边）  
	int		  weight;        //成交（双边）重量
	double    highLimit;     //涨停板          
	double    lowLimit;      //跌停板          
	double    upDown;        //涨跌            
	double    upDownRate;    //涨跌幅度        
	double    turnOver;      //成交额          
	double    average;       //均价            
	char      quoteDate[9];     //行情日期        
	char      quoteTime[9];     //行情时间        
	int       sequenceNo;    //行情序号     
	char	  sequence_seriesno; //消息序列类别号
	char	  sequence_no[11];	 //消息序号	  
	tagSpotQuotation()
	{
		memset(instID,0x00,sizeof(instID));
		memset(name,0x00,sizeof(name));
		lastClose =	0.0;
		open      =	0.0;
		high      =	0.0;
		low       =	0.0;
		last      =	0.0;
		close     =	0.0;
		bid1      =	0.0;
		bidLot1   = 0;
		bid2      =	0.0;
		bidLot2   = 0;
		bid3      =	0.0;
		bidLot3   = 0;
		bid4      =	0.0;
		bidLot4   = 0;
		bid5      =	0.0;
		bidLot5   = 0;
		ask1      =	0.0;
		askLot1   = 0;
		ask2      =	0.0;
		askLot2   = 0;
		ask3      =	0.0;
		askLot3   = 0;
		ask4      =	0.0;
		askLot4   = 0;
		ask5      =	0.0;
		askLot5   = 0;
		volume    = 0;
		weight    =	0;
		highLimit =	0.0;
		lowLimit  =	0.0;
		upDown    =	0.0;
		upDownRate=	0.0;
		turnOver  =	0.0;
		average   =	0.0;
		memset(quoteDate,0x00,sizeof(quoteDate));    
		memset(quoteTime,0x00,sizeof(quoteTime));
		sequenceNo= 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSpotQuotation,*PSpotQuotation;

//----------------------------------------------报文接口 [onRecvForwardQuotation] 定义
// 结构定义:
typedef struct tagForwardQuotation
{
	char        instID[9];          //合约代码        
	char        name[13];            //合约名称        
	double      lastSettle;          //昨结算          
	double      lastClose;           //昨收盘          
	double      open;                //开盘价          
	double      high;                //最高价          
	double      low;                 //最低价          
	double      last;                //最新价          
	double      close;               //收盘价          
	double      settle;              //结算价          
	double      bid1;                //买价1           
	int         bidLot1;             //买量1           
	double      bid2;                //买价2           
	int         bidLot2;             //买量2           
	double      bid3;                //买价3           
	int         bidLot3;             //买量3           
	double      bid4;                //买价4           
	int         bidLot4;             //买量4           
	double      bid5;                //买价5           
	int         bidLot5;             //买量5           
	double      ask1;                //卖价1           
	int         askLot1;             //卖量1           
	double      ask2;                //卖价2           
	int         askLot2;             //卖量2           
	double      ask3;                //卖价>3          
	int         askLot3;             //卖量3           
	double      ask4;                //卖价4           
	int         askLot4;             //卖量4           
	double      ask5;                //卖价5           
	int         askLot5;             //卖量5           
	int         volume;              //成交量          
	int         weight;              //成交（双边）重量
	double      highLimit;           //涨停板          
	double      lowLimit;            //跌停板          
	int         Posi;                //持仓量          
	double      upDown;              //涨跌            
	double      upDownRate;          //涨跌幅度        
	double      turnOver;            //成交额          
	double      average;             //均价            
	char        quoteDate[9];       //行情日期        
	char        quoteTime[9];       //行情时间        
	int         sequenceNo;          //行情序号        
	char		sequence_seriesno;	 //消息序列类别号
	char		sequence_no[11];	 //消息序号	 
	tagForwardQuotation()
	{
		memset(instID,0x00,sizeof(instID));
		memset(name,0x00,sizeof(name));
		lastSettle= 0.0;
		lastClose =	0.0;
		open      =	0.0;
		high      =	0.0;
		low       =	0.0;
		last      =	0.0;
		close     =	0.0;    
		settle    =	0.0;
		bid1      =	0.0;
		bidLot1   = 0;
		bid2      =	0.0;
		bidLot2   = 0;
		bid3      =	0.0;
		bidLot3   = 0;
		bid4      =	0.0;
		bidLot4   = 0;
		bid5      =	0.0;
		bidLot5   = 0;
		ask1      =	0.0;
		askLot1   = 0;
		ask2      =	0.0;
		askLot2   = 0;
		ask3      =	0.0;
		askLot3   = 0;
		ask4      =	0.0;
		askLot4   = 0;
		ask5      =	0.0;
		askLot5   = 0;
		volume    = 0;
		weight    =	0;
		highLimit =	0.0;
		lowLimit  =	0.0;
		Posi	  = 0;
		upDown    =	0.0;
		upDownRate=	0.0;
		turnOver  =	0.0;
		average   =	0.0;
		memset(quoteDate,0x00,sizeof(quoteDate));    
		memset(quoteTime,0x00,sizeof(quoteTime));
		sequenceNo= 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TForwardQuotation,*PForwardQuotation;

//----------------------------------------------报文接口 [onRecvDeferQuotation] 定义
// 结构定义:
typedef struct tagDeferQuotation
{
	char        instID[9];          //合约代码        
	char        name[13];            //合约名称        
	double      lastSettle;          //昨结算          
	double      lastClose;           //昨收盘          
	double      open;                //开盘价          
	double      high;                //最高价          
	double      low;                 //最低价          
	double      last;                //最新价          
	double      close;               //收盘价          
	double      settle;              //结算价          
	double      bid1;                //买价1           
	int         bidLot1;             //买量1           
	double      bid2;                //买价2           
	int         bidLot2;             //买量2           
	double      bid3;                //买价3           
	int         bidLot3;             //买量3           
	double      bid4;                //买价4           
	int         bidLot4;             //买量4           
	double      bid5;                //买价5           
	int         bidLot5;             //买量5           
	double      ask1;                //卖价1           
	int         askLot1;             //卖量1           
	double      ask2;                //卖价2           
	int         askLot2;             //卖量2           
	double      ask3;                //卖价3          
	int         askLot3;             //卖量3           
	double      ask4;                //卖价4           
	int         askLot4;             //卖量4           
	double      ask5;                //卖价5           
	int         askLot5;             //卖量5           
	int         volume;              //成交量          
	int         weight;              //成交（双边）重量
	double      highLimit;           //涨停板          
	double      lowLimit;            //跌停板          
	int         Posi;                //持仓量          
	double      upDown;              //涨跌            
	double      upDownRate;          //涨跌幅度        
	double      turnOver;            //成交额          
	double      average;             //均价            
	char        quoteDate[9];       //行情日期        
	char        quoteTime[9];       //行情时间        
	int         sequenceNo;          //行情序号        
	char		sequence_seriesno;   //消息序列类别号
	char		sequence_no[11];	 //消息序号	 
	tagDeferQuotation()
	{
		memset(instID,0x00,sizeof(instID));
		memset(name,0x00,sizeof(name));
		lastSettle= 0.0;
		lastClose =	0.0;
		open      =	0.0;
		high      =	0.0;
		low       =	0.0;
		last      =	0.0;
		close     =	0.0;    
		settle    =	0.0;
		bid1      =	0.0;
		bidLot1   = 0;
		bid2      =	0.0;
		bidLot2   = 0;
		bid3      =	0.0;
		bidLot3   = 0;
		bid4      =	0.0;
		bidLot4   = 0;
		bid5      =	0.0;
		bidLot5   = 0;
		ask1      =	0.0;
		askLot1   = 0;
		ask2      =	0.0;
		askLot2   = 0;
		ask3      =	0.0;
		askLot3   = 0;
		ask4      =	0.0;
		askLot4   = 0;
		ask5      =	0.0;
		askLot5   = 0;
		volume    = 0;
		weight    =	0;
		highLimit =	0.0;
		lowLimit  =	0.0;
		Posi		  = 0;
		upDown    =	0.0;
		upDownRate=	0.0;
		turnOver  =	0.0;
		average   =	0.0;
		memset(quoteDate,0x00,sizeof(quoteDate));    
		memset(quoteTime,0x00,sizeof(quoteTime));
		sequenceNo= 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferQuotation,*PDeferQuotation;

//----------------------------------------------报文接口 [onRecvDeferDeliveryQuotation] 定义
// 结构定义:
typedef struct tagDeferDeliveryQuotation
{
	char        instID[9];          //合约代码                              
	int         bidLot;             //买量  
	int         askLot;             //卖量 
	int         midBidLot;          //中立仓买量                           
	int         midAskLot;          //中立仓卖量           
	char		sequence_seriesno;   //消息序列类别号
	char		sequence_no[11];	 //消息序号	 
	tagDeferDeliveryQuotation()
	{
		memset(instID,0x00,sizeof(instID));
		bidLot   = 0;
		askLot   = 0;
		midBidLot   = 0;
		midAskLot   = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferDeliveryQuotation,*PDeferDeliveryQuotation;

//----------------------------------------------报文接口 [onRecvRtnFpRoundQuotation] 定义
// 结构定义:
typedef struct tagFpRoundQuotation
{
	char        prodCode[9];            //合约代码        
	char        prodName[13];           //合约名称        
	char		exchDate[9];       		//交易日期
	char		gameID[11];         	//场次编号
	int			roundID;        		//轮次编号
	double		price;          		//价格    	 
	double		adjust;         		//变动    	 
	int			bidLot;         		//买量    	 
	int			askLot;         		//卖量    	 
	double		lastSettlePrice;		//昨结算价	 
	char		quoteTime[9];      		//行情时间
	char		sequenceNo[11];     	//行情序号
	char		sequence_seriesno;		//消息序列类别号
	char		sequence_no[11];		//消息序号	
	tagFpRoundQuotation()
	{
		memset(prodCode       ,0x00,sizeof(prodCode       ));
		memset(prodName       ,0x00,sizeof(prodName       ));
		memset(exchDate       ,0x00,sizeof(exchDate       ));
		memset(gameID         ,0x00,sizeof(gameID         ));
		roundID = 0;
		price = 0.0;
		adjust = 0.0;
		bidLot = 0;
		askLot = 0;
		lastSettlePrice = 0.0;
		memset(quoteTime      ,0x00,sizeof(quoteTime      ));
		memset(sequenceNo     ,0x00,sizeof(sequenceNo     ));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TFpRoundQuotation,*PFpRoundQuotation;
 
//----------------------------------------------报文接口 [onRecvRtnFpQuotation] 定义
// 结构定义:
typedef struct tagFpQuotation
{
	char        prodCode[9];            //合约代码        
	char        prodName[13];           //合约名称        
	char		exchDate[9];       		//交易日期
	char		gameID[11];         	//场次编号
	double		price;          		//价格 
	char		isSettlePrice[3];		//是否是结算价
	int 		matchVolume;  			//成交量
	double		initPrice;    			//初始价
	int   		rounds;       			//轮数  
	char	    sequence_seriesno;		//消息序列类别号
	char	    sequence_no[11];		//消息序号	
	tagFpQuotation()
	{
		memset(prodCode       ,0x00,sizeof(prodCode       ));
		memset(prodName       ,0x00,sizeof(prodName       ));
		memset(exchDate       ,0x00,sizeof(exchDate       ));
		memset(gameID         ,0x00,sizeof(gameID         ));
		price = 0.0;
		memset(isSettlePrice  ,0x00,sizeof(isSettlePrice  ));
		matchVolume = 0;
		initPrice = 0.0;
		rounds = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TFpQuotation,*PFpQuotation;

//市场状态改变类

//----------------------------------------------报文接口 [onRecvRtnSpotMarketStateUpdate] 定义
// 结构定义:
typedef struct tagSpotMarketState
{
	char    marketID[3];           //市场代码    
	char    marketState;			//市场状态  
	char	sequence_seriesno;		//消息序列类别号
	char	sequence_no[11];		//消息序号	 
	tagSpotMarketState()
	{
		memset(marketID       ,0x00,sizeof(marketID       ));
		marketState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSpotMarketState,*PSpotMarketState;


//----------------------------------------------报文接口 [onRecvRtnDeferMarketStateUpdate] 定义
// 结构定义:
typedef struct tagDeferMarketState
{
	char    marketID[3];           //市场代码    
	char    marketState;			//市场状态  
	char	sequence_seriesno;		//消息序列类别号
	char	sequence_no[11];		//消息序号	  
	tagDeferMarketState()
	{
		memset(marketID       ,0x00,sizeof(marketID       ));
		marketState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferMarketState,*PDeferMarketState;

//----------------------------------------------报文接口 [onRecvRtnForwardMarketStateUpdate] 定义
// 结构定义:
typedef struct tagForwardMarketState
{
	char    marketID[3];           //市场代码    
	char    marketState;			//市场状态  
	char	sequence_seriesno;		//消息序列类别号
	char	sequence_no[11];		//消息序号	 
	tagForwardMarketState()
	{
		memset(marketID       ,0x00,sizeof(marketID       ));
		marketState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TForwardMarketState,*PForwardMarketState;
//合约状态改变类

//----------------------------------------------报文接口 [onRecvRtnSpotInstStateUpdate] 定义
// 结构定义:
typedef struct tagSpotInstState
{
	char    instID[9];             //合约代码    
	char    tradeState;				//合约交易状态  
	char	sequence_seriesno;		//消息序列类别号
	char	sequence_no[11];		//消息序号	  
	tagSpotInstState()
	{
		memset(instID        ,0x00,sizeof(instID        ));
		tradeState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSpotInstState,*PSpotInstState;

//----------------------------------------------报文接口 [onRecvRtnForwardInstStateUpdate] 定义
// 结构定义:
typedef struct tagForwardInstState
{
	char    instID[9];            //合约代码    
	char    tradeState;            //合约交易状态  
	char	sequence_seriesno;	   //消息序列类别号
	char	sequence_no[11];	   //消息序号	  
	tagForwardInstState()
	{
		memset(instID        ,0x00,sizeof(instID        ));
		tradeState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TForwardInstState,*PForwardInstState;

//----------------------------------------------报文接口 [onRecvRtnDeferInstStateUpdate] 定义
// 结构定义:
typedef struct tagDeferInstState
{
	char       instID[9];            //合约代码    
	char       tradeState;            //合约交易状态  
	char	   sequence_seriesno;	  //消息序列类别号
	char	   sequence_no[11];		  //消息序号	  
	tagDeferInstState()
	{
		memset(instID        ,0x00,sizeof(instID        ));
		tradeState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferInstState,*PDeferInstState;

//----------------------------------------------报文接口 [onRecvRtnFpInstStatUpdate] 定义
// 结构定义:
typedef struct tagFpInstStat
{
	char    ProdCode[9];            //合约代码    
	char	ExchDate[9];      		//交易日期      
	char	PreState;      			//前合约交易状态
	char	NowState;      			//现合约交易状态
	char    GameID[11];             //场次编号      
	int     RoundID;				//轮次编号      
	char    StartTime[9];			//开始时间      
	char    ContinueTime[9];		//持续时间   
	char	sequence_seriesno;		//消息序列类别号
	char	sequence_no[11];		//消息序号	
	tagFpInstStat()
	{
		memset(ProdCode    ,0x00,sizeof(ProdCode    ));
		memset(ExchDate    ,0x00,sizeof(ExchDate    ));
		PreState = 0;
		NowState = 0;
		memset(GameID      ,0x00,sizeof(GameID      ));
		RoundID = 0;
		memset(StartTime   ,0x00,sizeof(StartTime   ));
		memset(ContinueTime,0x00,sizeof(ContinueTime));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TFpInstStat,*PFpInstStat;

//交易类
//----------------------------------------------报文接口 [onRecvRtnSpotOrder/onRecvRtnSpotOrderCancel] 定义
// 结构定义:
typedef struct tagSpotOrder
{
	char      orderNo[17];         //报单号      
	char      instID[9];          //合约代码    
	char      clientID[13];        //客户代码    
	char      memberID[7];         //会员代码    
	char      buyOrSell;           //买卖方向    
	char      applyDate[9];        //申报日期    
	char      applyTime[9];        //申报时间    
	char      traderID[11];        //交易员代码  
	double    price;               //价格        
	int       amount;              //数量        
	int       remainAmount;        //剩余数量    
	char      cancelTime[9];       //撤消时间    
	char      cancelID[11];         //撤消员代码  
	char      status;              //状态        
	char      matchType;           //类型        
	char      endorseInstID[9];   //转让合约代码
	char      localOrderNo[15];    //本地报单    
	char	  sequence_seriesno;   //消息序列类别号
	char	  sequence_no[11];	   //消息序号	  
	tagSpotOrder()
	{
		memset(orderNo      ,0x00,sizeof(orderNo      ));
		memset(instID       ,0x00,sizeof(instID       ));
		memset(clientID     ,0x00,sizeof(clientID     ));
		memset(memberID     ,0x00,sizeof(memberID     ));
		buyOrSell = 0;	
		memset(applyDate    ,0x00,sizeof(applyDate    ));
		memset(applyTime    ,0x00,sizeof(applyTime    ));
		memset(traderID     ,0x00,sizeof(traderID     ));
		price = 0.0;	
		amount = 0;	
		remainAmount = 0;	
		memset(cancelTime   ,0x00,sizeof(cancelTime   ));
		memset(cancelID     ,0x00,sizeof(cancelID     ));
		status = 0;	
		matchType = 0;	
		memset(endorseInstID,0x00,sizeof(endorseInstID)); 
		memset(localOrderNo ,0x00,sizeof(localOrderNo ));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSpotOrder,*PSpotOrder;

//----------------------------------------------报文接口 [onRecvRtnForwardOrder/onRecvRtnForwardOrderCancel] 定义
// 结构定义:
typedef struct tagForwardOrder
{
	char      orderNo[17];         //报单号    
	char      instID[9];          //合约代码  
	char      clientID[13];        //客户代码  
	char      memberID[7];         //会员代码  
	char      buyOrSell;           //买卖方向  
	char      applyDate[9];        //申报日期  
	char      applyTime[9];        //申报时间  
	char      traderID[11];        //交易员代码
	double    price;			   //价格      
	int       amount;			   //数量      
	int       remainAmount;		   //剩余数量  
	char      cancelTime[9];       //撤消时间  
	char      cancelID[11];        //撤消员代码
	char      status;              //状态      
	char      localOrderNo[15];    //本地报单号
	char      matchType;           //类型      
	char	  sequence_seriesno;   //消息序列类别号
	char	  sequence_no[11];	   //消息序号	  
	tagForwardOrder()
	{
		memset(orderNo      ,0x00,sizeof(orderNo      ));
		memset(instID       ,0x00,sizeof(instID       ));
		memset(clientID     ,0x00,sizeof(clientID     ));
		memset(memberID     ,0x00,sizeof(memberID     ));
		buyOrSell = 0;	
		memset(applyDate    ,0x00,sizeof(applyDate    ));
		memset(applyTime    ,0x00,sizeof(applyTime    ));
		memset(traderID     ,0x00,sizeof(traderID     ));
		price = 0.0;	
		amount = 0;	
		remainAmount = 0;	
		memset(cancelTime   ,0x00,sizeof(cancelTime   ));
		memset(cancelID     ,0x00,sizeof(cancelID     ));
		status = 0;	
		matchType = 0;	
		memset(localOrderNo ,0x00,sizeof(localOrderNo ));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TForwardOrder,*PForwardOrder;

//----------------------------------------------报文接口 [onRecvRtnDeferOrder/onRecvRtnDeferOrderCancel] 定义
// 结构定义:
typedef struct tagDeferOrder
{
	char      orderNo[17];          //报单号    
	char      clientID[13];         //客户代码  
	char      instID[9];           //合约代码  
	char      memberID[7];          //会员代码  
	char      buyOrSell;			//买卖方向  
	char      applyDate[9];         //申报日期  
	char      applyTime[9];         //申报时间  
	char      offSetFlag;			//开平仓标志
	double    price;				//价格      
	int       amount;				//数量      
	int       remainAmount;			//剩余数量  
	char      cancelTime[9];        //撤消时间  
	char      status;				//状态      
	char      localOrderNo[15];     //本地报单号
	double    margin;				//保证金率  
	char      marginType;			//保证金类型
	char      traderID[11];         //交易员代码
	char      cancelID[11];         //撤消员代码
	char      matchType;			//类型      
	char	  sequence_seriesno;	//消息序列类别号
	char	  sequence_no[11];		//消息序号	  
	tagDeferOrder()
	{
		memset(orderNo      ,0x00,sizeof(orderNo      ));
		memset(instID       ,0x00,sizeof(instID       ));
		memset(clientID     ,0x00,sizeof(clientID     ));
		memset(memberID     ,0x00,sizeof(memberID     ));
		buyOrSell = 0;	
		memset(applyDate    ,0x00,sizeof(applyDate    ));
		memset(applyTime    ,0x00,sizeof(applyTime    ));
		offSetFlag = 0;	
		memset(traderID     ,0x00,sizeof(traderID     ));
		price = 0.0;	
		amount = 0;	
		remainAmount = 0;	
		memset(cancelTime   ,0x00,sizeof(cancelTime   ));
		memset(cancelID     ,0x00,sizeof(cancelID     ));
		status = 0;	
		matchType = 0;	
		marginType = 0;
		margin = 0.0;
		memset(localOrderNo ,0x00,sizeof(localOrderNo ));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferOrder,*PDeferOrder;

//----------------------------------------------报文接口 [onRecvRtnDeferDeliveryAppOrder/onRecvRtnDeferDeliveryAppOrderCancel] 定义
// 结构定义:
typedef struct tagDeferDeliveryAppOrder
{
	char      orderNo[17];          //报单编号    
	char      clientID[13];         //客户代码    
	char      instID[9];           //合约代码    
	char      buyOrSell;            //买卖方向    
	char      applyDate[9];         //申请日期    
	char      applyTime[9];         //申请时间    
	int       amount;               //数量        
	char      cancelTime[9];        //撤消时间    
	char      status;               //报单状态    
	char      localOrderID[15];     //本地报单编号
	char      memberID[7];          //会员代码    
	char      traderID[11];         //交易员代码  
	char      cancelID[11];         //撤消员代码  
	int       remainAmount;         //剩余数量    
	char	  sequence_seriesno;	//消息序列类别号
	char	  sequence_no[11];		//消息序号	  
	tagDeferDeliveryAppOrder()
	{
		memset(orderNo      ,0x00,sizeof(orderNo      ));
		memset(instID       ,0x00,sizeof(instID       ));
		memset(clientID     ,0x00,sizeof(clientID     ));
		memset(memberID     ,0x00,sizeof(memberID     ));
		buyOrSell = 0;	
		memset(applyDate    ,0x00,sizeof(applyDate    ));
		memset(applyTime    ,0x00,sizeof(applyTime    ));
		memset(traderID     ,0x00,sizeof(traderID     ));
		amount = 0;	
		remainAmount = 0;	
		memset(cancelTime   ,0x00,sizeof(cancelTime   ));
		memset(cancelID     ,0x00,sizeof(cancelID     ));
		status = 0;	
		memset(localOrderID ,0x00,sizeof(localOrderID ));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferDeliveryAppOrder,*PDeferDeliveryAppOrder;



//----------------------------------------------报文接口 [onRecvRtnSpotMatch] 定义
// 结构定义:
typedef struct tagSpotMatch
{
	char      matchNo[17];         //成交编号    
	char      buyOrSell;           //买卖方向    
	char      clientID[13];        //客户代码  
	char	  clientType;		   //客户类型
	char      memberID[7];         //会员代码    
	char      instID[9];           //合约代码    
	char      matchDate[9];        //成交日期    
	char      matchTime[9];        //成交时间    
	double    price;               //价格        
	int       volume;              //数量        
	char      orderNo[17];         //系统报单号  
	char      localOrderNo[15];    //报单本地编号
	char      matchType;           //类型        
	char	  sequence_seriesno;   //消息序列类别号
	char	  sequence_no[11];	   //消息序号	 
	tagSpotMatch()
	{
		memset(matchNo     ,0x00,sizeof(matchNo     ));
		buyOrSell = 0;
		memset(clientID    ,0x00,sizeof(clientID    ));
		clientType = 0;
		memset(memberID    ,0x00,sizeof(memberID    ));
		memset(instID      ,0x00,sizeof(instID      ));
		memset(matchDate   ,0x00,sizeof(matchDate   ));
		memset(matchTime   ,0x00,sizeof(matchTime   ));
		price= 0.0;
		volume= 0;
		memset(orderNo     ,0x00,sizeof(orderNo     ));
		memset(localOrderNo,0x00,sizeof(localOrderNo));
		matchType = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSpotMatch,*PSpotMatch;

//----------------------------------------------报文接口 [onRecvRtnForwardMatch] 定义
// 结构定义:
typedef struct tagForwardMatch
{
	char      matchNo[17];         //成交编号       
	char      buyOrSell;           //买卖方向       
	char      clientID[13];        //客户代码
	char	  clientType;		   //客户类型
	char      instID[9];          //合约代码       
	char      memberID[7];         //会员代码       
	char      matchDate[9];        //成交日期       
	char      matchTime[9];        //成交时间       
	double    price;               //价格           
	int       volume;              //数量           
	double    marginRate;          //保证金率       
	char      rateType;            //保证金类型     
	char      orderNo[17];         //系统报单号     
	char      localOrderNo[15];    //报单本地编号   
	char	sequence_seriesno;	   //消息序列类别号
	char	sequence_no[11];	   //消息序号	  
	tagForwardMatch()
	{
		memset(matchNo     ,0x00,sizeof(matchNo     ));
		buyOrSell = 0;
		memset(clientID    ,0x00,sizeof(clientID    ));
		clientType = 0;
		memset(instID      ,0x00,sizeof(instID      ));
		memset(memberID    ,0x00,sizeof(memberID    ));
		memset(matchDate   ,0x00,sizeof(matchDate   ));
		memset(matchTime   ,0x00,sizeof(matchTime   ));
		price= 0.0;
		volume= 0;
		marginRate= 0.0;
		rateType = 0;
		memset(orderNo     ,0x00,sizeof(orderNo     ));
		memset(localOrderNo,0x00,sizeof(localOrderNo));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TForwardMatch,*PForwardMatch;

//----------------------------------------------报文接口 [onRecvRtnDeferMatch] 定义
// 结构定义:
typedef struct tagDeferMatch
{
	char      matchNo[17];         //成交编号    
	char      buyOrSell;           //买卖方向    
	char      clientID[13];        //客户代码
	char	  clientType;		   //客户类型
	char      instID[9];          //合约代码    
	char      memberID[7];         //会员代码    
	char      matchDate[9];        //成交日期    
	char      matchTime[9];        //成交时间    
	double    price;               //价格        
	int       volume;              //数量        
	char      offsetFlag;          //开平标志    
	char      orderNo[17];         //系统报单号  
	char      localOrderNo[15];    //报单本地编号
	char	  sequence_seriesno;   //消息序列类别号
	char	  sequence_no[11];	   //消息序号	  
	tagDeferMatch()
	{
		memset(matchNo     ,0x00,sizeof(matchNo     ));
		buyOrSell = 0;
		memset(clientID    ,0x00,sizeof(clientID    ));
		clientType = 0;
		memset(instID      ,0x00,sizeof(instID      ));
		memset(memberID    ,0x00,sizeof(memberID    ));
		memset(matchDate   ,0x00,sizeof(matchDate   ));
		memset(matchTime   ,0x00,sizeof(matchTime   ));
		price= 0.0;
		volume= 0;
		offsetFlag = 0;
		memset(orderNo     ,0x00,sizeof(orderNo     ));
		memset(localOrderNo,0x00,sizeof(localOrderNo));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferMatch,*PDeferMatch;

//----------------------------------------------报文接口 [onRecvRtnDeferDeliveryAppMatch] 定义
// 结构定义:
typedef struct tagDeferDeliveryAppMatch
{
	char      matchNo[17];	       //成交序号    
	char      clientID[13];        //客户代码    
	char      instID[9];          //合约代码    
	char      memberID[7];         //会员代码    
	char      buyOrSell;           //买卖方向    
	int       volume;              //数量        
	char      matchDate[9];        //成交日期    
	char      matchTime[9];        //成交时间    
	char      orderNo[17];         //报单号      
	char      localOrderNo[15];    //报单本地编号
	char      middleFlag;          //是否为中立仓
	char	  sequence_seriesno;	   //消息序列类别号
	char	  sequence_no[11];	   //消息序号	  
	tagDeferDeliveryAppMatch()
	{
		memset(matchNo	   ,0x00,sizeof(matchNo	    ));
		memset(clientID    ,0x00,sizeof(clientID    ));
		memset(instID      ,0x00,sizeof(instID      ));
		memset(memberID    ,0x00,sizeof(memberID    ));
		buyOrSell = 0;
		volume= 0;
		memset(matchDate   ,0x00,sizeof(matchDate   ));
		memset(matchTime   ,0x00,sizeof(matchTime   ));
		memset(orderNo     ,0x00,sizeof(orderNo     ));
		memset(localOrderNo,0x00,sizeof(localOrderNo));
		middleFlag= 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferDeliveryAppMatch,*PDeferDeliveryAppMatch;
//----------------------------------------------报文接口 [onRecvRspFpOrder] 定义
// 结构定义:
typedef struct tagFpOrder
{
	char		OrderNo[17];		 //报单号    		
	char      	LocalOrderNo[15];    //本地报单号   
	char      	MemberID[7];         //会员编号      
	char      	AcctNo[13];          //客户号       
	char      	ProdCode[9];         //合约         
	char      	Bs;					 //买卖方向    'b'-买  's'-卖
	char      	OrderType;			 //报单类型      
	int         Amount;              //委托手数    
	char      	ApplyDate[9];        //委托日期     
	char      	ApplyTime[9];        //委托时间     
	char      	EntrPhase;			 //申报阶段     
	char      	GameID[11];          //场次编码     
	int         RoundID;             //轮次编号    
	double      EntrPrice;           //委托价格    
	char      	Status;				 //状态          	
	char		sequence_seriesno;	 //消息序列类别号
	char	    sequence_no[11];	 //消息序号	
	tagFpOrder()
	{
		memset(OrderNo     ,0x00,sizeof(OrderNo     ));
		memset(LocalOrderNo,0x00,sizeof(LocalOrderNo));
		memset(MemberID    ,0x00,sizeof(MemberID    ));
		memset(AcctNo      ,0x00,sizeof(AcctNo      ));
		memset(ProdCode    ,0x00,sizeof(ProdCode    ));
		Bs = 0;
		OrderType = 0;
		Amount = 0;
		memset(ApplyDate   ,0x00,sizeof(ApplyDate   ));
		memset(ApplyTime   ,0x00,sizeof(ApplyTime   ));
		EntrPhase = 0;
		memset(GameID      ,0x00,sizeof(GameID      ));
		RoundID = 0;
		EntrPrice = 0.0;
		Status = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TFpOrder,*PFpOrder;

//----------------------------------------------报文接口 [onRecvRtnFpEntrStatistics] 定义
// 结构定义:
typedef struct tagFpEntrStatistics
{
	char		ExchDate[9];      	 //交易日期             
	char   		MemberID[7];         //会员号               
	char   		AcctNo[13];          //客户号              
	char   		ProdCode[9];        //合约代码            
	char   		GameID[11];			 //场次编号             
	double   	Price;			     //本轮价格            
	int   		MrBuyAmount;         //本轮市场申报买量    
	int			MrSellAmount;        //本轮市场申报卖量    
	int   		FrBuyAmount;         //本轮补充申报买量    
	int   		FrSellAmount;        //本轮补充申报卖量    
	int   		LrMrBuyAmount;       //上一轮市场申报买量  
	int   		LrMrSellAmount;      //上一轮市场申报卖量  
	int			LrFrBuyAmount;       //上一轮补充申报买量  
	int			LrFrSellAmount;     //上一轮补充申报卖量  
	double   	LrPrice;             //上一轮的价格        
	double		FrozBuyMargin;       //目前已冻结买入保证金
	double		FrozSellMargin;      //目前已冻结卖出保证金
	double		FrozBuyExchFare;     //目前已冻结买入手续费
	double		FrozSellExchFare;    //目前已冻结卖出手续费
	char		sequence_seriesno;	 //消息序列类别号
	char		sequence_no[11];	 //消息序号	
	tagFpEntrStatistics()
	{
		memset(ExchDate,0x00,sizeof(ExchDate));
		memset(MemberID,0x00,sizeof(MemberID));
		memset(AcctNo  ,0x00,sizeof(AcctNo  ));
		memset(ProdCode,0x00,sizeof(ProdCode));
		memset(GameID  ,0x00,sizeof(GameID  ));
		Price            = 0.0;	
		MrBuyAmount      = 0;	
		MrSellAmount     = 0;	
		FrBuyAmount      = 0;	
		FrSellAmount     = 0;	
		LrMrBuyAmount    = 0;	
		LrMrSellAmount   = 0;	
		LrFrBuyAmount    = 0;	
		LrFrSellAmount   = 0;	
		LrPrice          = 0.0;	
		FrozBuyMargin    = 0.0;	
		FrozSellMargin   = 0.0;	
		FrozBuyExchFare  = 0.0;
		FrozSellExchFare = 0.0;	
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TFpEntrStatistics,*PFpEntrStatistics;
//----------------------------------------------报文接口 [onRecvRtnFpMatch] 定义
// 结构定义:
typedef struct tagFpMatch
{
	char		MatchNo[17];		//成交单号  	
	char		MatchDate[9];		//成交日期  	 	
	char		DeliDate[9];		//交割日期  	 
	char		MatchGame[11];		//成交场次  	 	
	int 		MatchRound;			//成交轮次  	 	
	char		MemberID[7];		//会员编号  	 
	char		AcctNo[13];			//客户号    	
	char		ProdCode[9];		//合约      		
	char		Bs;					//买卖方向  	 
	double  	MatchPrice;			//成交价格  	  
	int     	MatchAmount;		//成交手数  	  
	char    	EntrPhase;			//申报阶段  	 
	char    	IsAllocate;			//是否为分摊	
	char		sequence_seriesno;	//消息序列类别号
	char		sequence_no[11];	//消息序号	
	tagFpMatch()
	{
		memset(MatchNo    ,0x00,sizeof(MatchNo    ));
		memset(MatchDate  ,0x00,sizeof(MatchDate  ));
		memset(DeliDate   ,0x00,sizeof(DeliDate   ));
		memset(MatchGame  ,0x00,sizeof(MatchGame  ));
		MatchRound = 0;
		memset(MemberID   ,0x00,sizeof(MemberID   ));
		memset(AcctNo     ,0x00,sizeof(AcctNo     ));
		memset(ProdCode   ,0x00,sizeof(ProdCode   ));
		Bs = 0;
		MatchPrice = 0.0;
		MatchAmount = 0;
		EntrPhase = 0;
		IsAllocate = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TFpMatch,*PFpMatch;

//----------------------------------------------报文接口 [onRecvRspFpOrderCancel] 定义
// 结构定义:
typedef struct tagFpOrderCancel
{
	char		MemberID[7];	//会员编号   
	char		AcctNo[13];		//客户号     
	char		ProdCode[9];	//合约       
	char		EntrPhase;		//申报阶段   
	char		Bs;				//买卖方向    
	int 		CancelAmount;	//撤销手数  
	char		GameID[11];     //场次编号   
	int 		RoundID;        //轮次编号  
	char		Status;			//状态       
	char		sequence_seriesno;	 //消息序列类别号
	char		sequence_no[11];	 //消息序号	
	tagFpOrderCancel()
	{
		memset(MemberID    ,0x00,sizeof(MemberID    ));
		memset(AcctNo      ,0x00,sizeof(AcctNo      ));
		memset(ProdCode    ,0x00,sizeof(ProdCode    ));
		EntrPhase = 0;
		Bs = 0;
		CancelAmount = 0;
		memset(GameID      ,0x00,sizeof(GameID      ));
		RoundID = 0;
		Status = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TFpOrderCancel,*PFpOrderCancel;


//----------------------------------------------报文接口 [onRecvRspFpOrderFullCancel] 定义
// 结构定义:
typedef struct tagFpOrderFullCancel
{
	char		GameID[11];    //场次编号    
	int			RoundID;	   //轮次编号    
	char		ProdCode[9];  //合约          
	char		Bs;			   //买卖方向    
	char		NeedCancel;	   //是否需要全撤    
	double		NewRoundPrice; //新一轮价格 
	char		sequence_seriesno;		//消息序列类别号
	char		sequence_no[11];		//消息序号	
	tagFpOrderFullCancel()
	{
		memset(GameID       ,0x00,sizeof(GameID       ));
		RoundID = 0;
		memset(ProdCode     ,0x00,sizeof(ProdCode     ));
		Bs = 0;
		NeedCancel = 0;
		NewRoundPrice = 0.0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TFpOrderFullCancel,*PFpOrderFullCancel;




//系统类
//----------------------------------------------报文接口 [onSysInit] 定义
// 结构定义:
typedef struct tagSysInit
{
	char      old_exch_date[9];       //原交易日期
	char      new_exch_date[9];       //新交易日期
	char	  sequence_seriesno;	  //消息序列类别号
	char	  sequence_no[11];		  //消息序号
	tagSysInit()
	{
		memset(old_exch_date,0x00,sizeof(old_exch_date));
		memset(new_exch_date,0x00,sizeof(new_exch_date));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSysInit,*PSysInit;

//----------------------------------------------报文接口 [onSysStatChange] 定义
// 结构定义:
typedef struct tagSysStat
{
	char      sys_date[9];         //系统日期          
	char      exch_date[9];        //交易日期          
	char      m_sys_stat;          //国际中心系统状态  
	char      b_sys_stat;          //主板交易所系统状态
	char	  sequence_seriesno;   //消息序列类别号
	char	  sequence_no[11];	   //消息序号	 
	tagSysStat()
	{
		memset(sys_date ,0x00,sizeof(sys_date ));
		memset(exch_date,0x00,sizeof(exch_date));
		m_sys_stat = 0;	
		b_sys_stat = 0;	
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSysStat,*PSysStat;

//----------------------------------------------报文接口 [onNewMemberBulletin] 定义
// 结构定义:
typedef struct tagNewMemberBulletin
{
	char      bulletin_id[11];      //公告序号
	char      title[41];           //公告标题
	char	  sequence_seriesno;	//消息序列类别号
	char	  sequence_no[11];		//消息序号	  
	tagNewMemberBulletin()
	{
		memset(bulletin_id,0x00,sizeof(bulletin_id));
		memset(title	  ,0x00,sizeof(title	  ));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TNewMemberBulletin,*PNewMemberBulletin;


//客户类
//----------------------------------------------报文接口 [onCustOpenCheck] 定义
// 结构定义:
typedef struct tagCustOpenCheck
{
	char      member_id[7];            //会员代码    
	char      cert_type_id;				//证件类型    
	char      cert_num[41];            //证件号码    
	char      cust_id[13];             //黄金交易编码
	char	  sequence_seriesno;	   //消息序列类别号
	char	  sequence_no[11];		   //消息序号	
	tagCustOpenCheck()
	{
		memset(member_id,0x00,sizeof(member_id));
		cert_type_id = 0;
		memset(cert_num ,0x00,sizeof(cert_num));	
		memset(cust_id  ,0x00,sizeof(cust_id));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TCustOpenCheck,*PCustOpenCheck;

//库存类
//----------------------------------------------报文接口 [on0x00A00123] 定义
// 结构定义:
typedef struct tag0x00A00123
{
	char      memberID[7];     //会员代码     
	char      effectDate[9];   //交易日期     
	char      seqNo[32];       //流水序号     
	char      sheetNo[11];     //单据编号     
	char      clientID[13];    //客户代码     
	char      accountType;	   //账户类型     
	char      transType[3];    //库存变化类型 
	char      varietyID[5];    //交割品种代码 
	char      warehouseID[5];  //仓库代码     
	double    stdStorage;	   //发生标准重量 
	double    totalStore;      //发生实际重量 
	double    sumStore;        //库存余量     
	char      transDate[9];    //实际发生日期 
	char      transTime[9];    //实际发生时间 
	char	  sequence_seriesno;	   //消息序列类别号
	char	  sequence_no[11];		   //消息序号	
	tag0x00A00123()
	{
		memset(memberID   ,0x00,sizeof(memberID));
		memset(effectDate ,0x00,sizeof(effectDate));
		memset(seqNo	  ,0x00,sizeof(seqNo));
		memset(sheetNo    ,0x00,sizeof(sheetNo));
		memset(clientID   ,0x00,sizeof(clientID));
		accountType = 0;
		memset(transType  ,0x00,sizeof(transType));
		memset(varietyID  ,0x00,sizeof(varietyID));
		memset(warehouseID,0x00,sizeof(warehouseID));
		stdStorage = 0.0;
		totalStore = 0.0;
		sumStore = 0.0;
		memset(transDate  ,0x00,sizeof(transDate));
		memset(transTime  ,0x00,sizeof(transTime));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}T0x00A00123,*P0x00A00123;

//----------------------------------------------报文接口 [on0x00A00202] 定义
// 结构定义:
typedef struct tag0x00A00202
{
	char      pickupSheetNo[15];    //提货单号     
	char      applyDate[9];			//申请日期     
	char      applyTransDate[9];    //申请提货时交易日期     
	char      memberID[7];			//会员代码     
	char      localNo[17];			//本地提货单号     
	char	  sequence_seriesno;	//消息序列类别号
	char	  sequence_no[11];		//消息序号	
	tag0x00A00202()
	{
		memset(pickupSheetNo   ,0x00,sizeof(pickupSheetNo));
		memset(applyDate ,0x00,sizeof(applyDate));
		memset(applyTransDate	  ,0x00,sizeof(applyTransDate));
		memset(memberID    ,0x00,sizeof(memberID));
		memset(localNo   ,0x00,sizeof(localNo));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}T0x00A00202,*P0x00A00202;

//----------------------------------------------报文接口 [on0x00A00212] 定义
// 结构定义:
typedef struct tag0x00A00212
{
	char      pickupSheetNo[15];    //提货单号        
	char      memberID[7];			//会员代码         
	char	  sequence_seriesno;	//消息序列类别号
	char	  sequence_no[11];		//消息序号	
	tag0x00A00212()
	{
		memset(pickupSheetNo   ,0x00,sizeof(pickupSheetNo));
		memset(memberID    ,0x00,sizeof(memberID));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}T0x00A00212,*P0x00A00212;

//----------------------------------------------报文接口 [on0x00A00222] 定义
// 结构定义:
typedef struct tag0x00A00222
{
	char      SheetNo[15];        //提货单号          
	char      localNo[17];        //本地提货单号      
	char      memberID[7];        //会员代码          
	char      clientID[13];       //客户号            
	char      warehouseID[5];     //仓库代码          
	char      pickupPerson[21];   //提货人            
	char      cipher[255];        //提货密码          
	char      certificateType;    //证件类型          
	char      certificateNo[21];  //证件号码          
	char      applyDate[9];       //申请日期          
	char      beginDate[9];       //提货开始日期      
	char      endDate[9];         //提货结束日期      
	char      applyTransDate[9];  //提货申请时交易日期
	char      traderID[11];       //交易员代码        
	double    stdDrawWeight;      //标准提货总重      
	char      varietyID[4];       //交割代码          
	double    selfDrawWeight;     //自提重量          
	double    tradeDrawWeight;    //交提重量          
	char      drawType;			  //提货类型          
	char      leaseRegNo[9];      //租借登记单编号           
	char	  sequence_seriesno;	//消息序列类别号
	char	  sequence_no[11];		//消息序号	
	tag0x00A00222()
	{
		memset(SheetNo        ,0x00,sizeof(SheetNo        ));
		memset(localNo        ,0x00,sizeof(localNo        ));
		memset(memberID       ,0x00,sizeof(memberID       ));
		memset(clientID       ,0x00,sizeof(clientID       ));
		memset(warehouseID    ,0x00,sizeof(warehouseID    ));
		memset(pickupPerson   ,0x00,sizeof(pickupPerson   ));
		memset(cipher         ,0x00,sizeof(cipher         ));
		certificateType = 0;
		memset(certificateNo  ,0x00,sizeof(certificateNo  ));
		memset(applyDate      ,0x00,sizeof(applyDate      ));
		memset(beginDate      ,0x00,sizeof(beginDate      ));
		memset(endDate        ,0x00,sizeof(endDate        ));
		memset(applyTransDate ,0x00,sizeof(applyTransDate ));
		memset(traderID       ,0x00,sizeof(traderID       ));
		stdDrawWeight = 0.0;
		memset(varietyID      ,0x00,sizeof(varietyID      ));
		selfDrawWeight = 0.0;
		tradeDrawWeight = 0.0;
		drawType = 0;
		memset(leaseRegNo     ,0x00,sizeof(leaseRegNo     ));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}T0x00A00222,*P0x00A00222;

//----------------------------------------------报文接口 [on0x00A00223] 定义
// 结构定义:
typedef struct tag0x00A00223
{
	char      memberID[7];			//会员代码      
	char      effectDate[9];		//交易日期      
	char      seqNo[11];			//流水号        
	char      clientID[13];			//客户号        
	char      SheetNo[15];			//提货单号      
	char      appSheetNo[17];		//申请单据编号  
	char      localNo[17];			//本地提货单号  
	char      stgOptType[5];		//类型          
	char      appState;				//申报状态        
	char	  sequence_seriesno;	//消息序列类别号
	char	  sequence_no[11];		//消息序号	
	tag0x00A00223()
	{
		memset(memberID  ,0x00,sizeof(memberID  ));   
		memset(effectDate,0x00,sizeof(effectDate));   
		memset(seqNo     ,0x00,sizeof(seqNo     ));   
		memset(clientID  ,0x00,sizeof(clientID  ));   
		memset(SheetNo   ,0x00,sizeof(SheetNo   ));   
		memset(appSheetNo,0x00,sizeof(appSheetNo));   
		memset(localNo   ,0x00,sizeof(localNo   ));   
		memset(stgOptType,0x00,sizeof(stgOptType));
		appState = 0;	
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}T0x00A00223,*P0x00A00223;
#endif
