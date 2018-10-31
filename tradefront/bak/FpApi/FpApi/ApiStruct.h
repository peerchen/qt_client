

#ifndef _API_STRUCT_H_
#define _API_STRUCT_H_
#include <string>
#include <string.h>
using namespace std;

//----------------------------------------------����ǰ�û���ַ�ӿ�[SetService]����
typedef struct tagIpPort
{
	char		sIp[16];		//IP		�ǿ�
	int			nPort;			//�˿ں�	�ǿ�
	tagIpPort()
	{
		memset(sIp,0x00,sizeof(sIp));
		nPort = -1;
	}
}TIpPort,*PIpPort;
//----------------------------------------------�����Ļ���
typedef struct tagReqMsg
{
	char		teller_id[11];	//����Ա��		�ǿ�
	char		branch_id[21];	//��������		�ǿ�
	char		member_id[7];	//��Ա��		�ǿ�
	char		unit_id[7];		//���뵥Ԫ��	�ǿ�
	char		root_id[19];	//����������Ӧ���ƥ�䣬Ӧ�𷵻���������ͬ��ֵ��	�ǿ�
	tagReqMsg()
	{
		memset(teller_id,0x00,sizeof(teller_id));
		memset(branch_id,0x00,sizeof(branch_id));
		memset(member_id,0x00,sizeof(member_id));
		memset(unit_id,0x00,sizeof(unit_id));
		memset(root_id,0x00,sizeof(root_id));
	}
}TReqMsg,*PReqMsg;
//----------------------------------------------��Ӧ���Ļ��� ����
// �ṹ����:��Ӧ�������
typedef struct tagRspMsg
{
	char		teller_id[11];	//����Ա��		
	char		branch_id[21];	//��������		
	char		member_id[7];	//��Ա��		
	char		unit_id[7];		//���뵥Ԫ��	
	char		root_id[19];	//����������Ӧ���ƥ�䣬Ӧ�𷵻���������ͬ��ֵ��	�ǿ�
	char       rsp_code[21];	//��Ӧ����		
	char       rsp_msg[41];    //��Ӧ��Ϣ		
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
//----------------------------------------------�쳣�ص��ӿ�[onException]����
//�ṹ���壺�쳣�ص��ӿ�
typedef struct tagExceptionMsg
{
	char       exception_code[10];		//�쳣����	�ǿ�
	char       exception_msg[200];		//�쳣��Ϣ	�ǿ�
	tagExceptionMsg()
	{
		memset(exception_code,0x00,sizeof(exception_code));
		memset(exception_msg,0x00,sizeof(exception_msg));
	}
}TExceptionMsg,*PExceptionMsg;
//----------------------------------------------Req���Ľӿ�[ReqLoginTrade/ReqLoginBroadcast]����
//�ṹ����:API��¼������
typedef struct tagReqLogin :public TReqMsg
{
	int      oper_flag;				//������־	�ǿ�	Ĭ���� 1                       
	char	 crt_pwd[50];			//֤������	��������""
	struct tagAlmBreakpoint			
	{
		char	sequence_seriesno[3];//��Ϣ�������� 
		char	sequence_no[11];	 //�ش���ʽ 0:�ش���RESTART�� �������:������RESUME��   -1:���գ�QUICK��
	} *		p_almbreakpoint;		 //�ϵ���Ϣ			�޶ϵ���Ϣ��NULL
	int		num_almbreakpoint;		//�ϵ���Ϣ����		�޶ϵ���Ϣ��0		û���ϴ��ϵ���ϢʱĬ�Ϸ�������������
	char	unit_password[61];		//���뵥Ԫ��¼����	�ǿ�
	tagReqLogin()
	{
		oper_flag = 1;
		memset(crt_pwd,0x00,sizeof(crt_pwd));
		p_almbreakpoint = NULL;
		num_almbreakpoint = 0;
		memset(unit_password,0x00,sizeof(unit_password));
	}
}TReqLogin,*PReqLogin;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspLoginTrade/onRecvRspLoginBroadcast] ����
// �ṹ����:API��¼��Ӧ����
typedef struct tagRspLogin :public TRspMsg
{
	int      oper_flag;				//������־ 
	char	 exch_date[9];			//��������  ��¼δ�ɹ���Ϊ��
	tagRspLogin()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
	}
}TRspLogin ,*PRspLogin;


//----------------------------------------------Req���Ľӿ� [ReqLogoutTrade/ReqLogoutBroadcast] ����
//�ṹ����:���뵥Ԫ�ǳ�������
typedef struct tagReqLogout :public TReqMsg
{
	int      oper_flag;				//������־	�ǿ�	Ĭ���� 1 
	tagReqLogout()
	{
		oper_flag =	0;
	}
}TReqLogout,*PReqLogout;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspLogoutTrade/onRecvRspLogoutBroadcast] ����
// �ṹ����:���뵥Ԫ�ǳ���Ӧ����
typedef struct tagRspLogout :public TRspMsg
{
	int     oper_flag;				//������־ 
	tagRspLogout()
	{
		oper_flag =	0;
	}
}TRspLogout,*PRspLogout;

//----------------------------------------------Req���Ľӿ� [ReqTellerLogin] ����
//�ṹ����:����Ա��¼������
typedef struct tagReqTellerLogin :public TReqMsg
{
	int      oper_flag;				//������־	�ǿ�	Ĭ���� 1  
	char     password[61];			//����Ա����	�ǿ�	��MD5���ܺ��ֵ   
	tagReqTellerLogin()
	{
		oper_flag =	0;
		memset(password,0x00,sizeof(password));
	}
}TReqTellerLogin,*PReqTellerLogin;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspTellerLogin] ����
// �ṹ����:����Ա��¼��Ӧ����
typedef struct tagRspTellerLogin :public TRspMsg
{
	int      oper_flag;				//������־
	char	 exch_date[9];			//��������  ��¼δ�ɹ���Ϊ��
	tagRspTellerLogin()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
	}
}TRspTellerLogin ,*PRspTellerLogin;

//----------------------------------------------Req���Ľӿ� [ReqTellerLogout] ����
//�ṹ����:����Ա�ǳ�������
typedef struct tagReqTellerLogout :public TReqMsg
{
	int      oper_flag;				//������־	�ǿ�	Ĭ���� 1        
	tagReqTellerLogout()
	{
		oper_flag =	0;
	}
}TReqTellerLogout,*PReqTellerLogout;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspTellerLogout] ����
// �ṹ����:����Ա�ǳ���Ӧ����
typedef struct tagRspTellerLogout :public TRspMsg
{
	int      oper_flag;				//������־
	tagRspTellerLogout()
	{
		oper_flag =	0;
	}
}TRspTellerLogout,*PRspTellerLogout;


//----------------------------------------------Req���Ľӿ� [ReqPreOpenAccountLegal] ����
// �ṹ����:����Ԥ������������
typedef struct tagReqPreOpenAccountLegal :public TReqMsg
{
	int				 oper_flag;				//������־	�ǿ�	Ĭ���� 1
	char			 gess_branch_id[21];	//ǩԼ����	�ǿ�	��Ĭ��ֵ������ʱ����
	char			 acct_type;				//�˻�����  �̶���'2'��������  ȡֵ��Χ��'1'-��Ӫ '2'-���� '3'-����
	char			 gess_grade_id[21];		//�ͻ�����	�ǿ�
	char			 settle_bank_no[5];		//�����к�	�ǿ�
	char			 account_no[31];		//�����˻�	�ǿ�
	char			 account_name[41];		//���л�������	�ǿ� 
	char			 open_account_date[9];	//�˻���������	�ǿ�
	char			 account_due_date[9];	//�˻���������	�ǿ�
	char			 corp_en_name[121];		//��˾Ӣ������	�ǿ�
	char			 corp_chn_name[81];		//��˾��������	�ǿ�
	char			 corp_en_abbr[21];		//��˾Ӣ�ļ��	�ǿ�
	char			 corp_chn_abbr[21];		//��˾���ļ��	�ǿ�
	char			 corp_prop_id;			//��˾����		�ǿ�	ȡֵ��Χ��'1'-���޹�˾,'2'-��Ȼ�˶���,'3'-���޺ϻ�,'4'-����
	char			 corp_code[33];			//��ҵ��֯�ṹ����	�ǿ�
	char			 cert_type;				//֤������	�ǿ�	ȡֵ��Χ��'1'-��ҵ���֤ commercial licence,'2'-��˾ע��֤ certificate of incorporation,'3'-��ҵ�Ǽ�֤ business registration certificate,'4'-��business number��֤��,'5'-����
	char			 cert_num[41];			//֤�����	�ǿ�
	char			 contacter[81];			//���˴���	
	char			 mobile_phone[31];		//�ֻ�����			
	char			 regist_addr[81];		//ע���	�ǿ�	
	double		     reg_capital;		    //ע���ʱ�	�ǿ�
	char			 org_type;				//��������	�ǿ�	ȡֵ��Χ��'2'-����˾,'3'-��Ա��λ,'4'-����˾�ͻ�Ա��λ
	char			 corp_zip[11];			//��˾�ʱ�	�ǿ�				
	char			 corp_tel[31];			//��˾�绰	�ǿ�	
	char			 corp_fax[31];			//��˾����	�ǿ�
	char			 corp_email[81];		//��˾��������	�ǿ�
	char			 pawnee_flag;			//��Ȩ�˱�־	�ǿ�	ȡֵ��Χ��'1'-�ǣ�'0'-��
	char			 corp_regist_addr[121]; //��˾ע���ַ	�ǿ�	
	char			 copr_authorizer;		//��˾��Ȩ��	�ǿ�	ȡֵ��Χ��'1'-��˾��Ȩ�ˣ�'2'-���ˣ�'3'-���£�'4'-������
	char			 auth_nationality[41];	//��Ȩ�˹���	�ǿ�	
	char			 auth_cert_type_id;	//��Ȩ��֤������	�ǿ�	ȡֵ��Χ��'s'-���֤��'h'-���ա�'j'-����֤��'y'-Ӫҵִ��	
	char			 auth_cert_no[21];		//��Ȩ��֤����	�ǿ�	
	char			 auth_addr[81];			//��Ȩ����ϵ��ַ	�ǿ�
	char			 auth_zip[11];			//��Ȩ���ʱ�	�ǿ�
	char			 auth_tel[31];			//��Ȩ�˵绰	�ǿ�
	char			 auth_fax[31];			//��Ȩ�˴���	�ǿ�
	char			 auth_email[81];		//��Ȩ�˵�������	�ǿ�
	char			 busi_license[21];		//Ӫҵִ��
	char			 tax_cert[21];			//˰��Ǽ�֤	
	char			 org_code_cert[21];		//��֯��������֤
	char			 regist_address[81];	//ע���ַ
	char			 sigex_post_code[11];	//��ó���ʱ�	
	char			 sigex_tel[31];			//��ó���绰
	char			 sigex_fax[31];			//��ó������
	char			 sigex_email[81];		//��ó����������
	char			 cust_id[13];			//�ƽ��ױ���	�ؿ�����
	char			 gess_broker_id[21];	//�ͻ������	�ǿ�  �̶�����
	char			 exec_name[41];			//���׾�����	�ǿ�
	char			 exec_tel[31];			//��������ϵ�绰	
	char			 exec_cert_type_id;		//������֤������	�ǿ�	
	char			 exec_cert_num[21];		//������֤������	�ǿ�
	char			 taxpayer_identifier[22];//��˰��ʶ���	
	char			 is_val_added_taxplayer;//�Ƿ�Ϊ��ֵ˰һ����˰��	
	char			 taxplayer_address[82]; //��˰�˵�ַ	
	char			 taxpayer_telephone[31];//��˰�˵绰	
	char			 taxpayer_bankcode[5];	//��˰�����д���		
	char			 taxpayer_bankinfo[82]; //��˰�˿�������Ϣ		
	char			 taxpayer_account_id[32];//��˰���˺�		
	char			 memo[255];				//��ע	
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


//----------------------------------------------Rsp���Ľӿ� [onRecvRspPreOpenAccountLegal] ����
// �ṹ����:����Ԥ��������Ӧ������
typedef struct tagRspPreOpenAccountLegal :public TRspMsg
{
	int      oper_flag;				//������־
	char	 cust_id[13];			//�ͻ���
	tagRspPreOpenAccountLegal()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
	}
}TRspPreOpenAccountLegal,*PRspPreOpenAccountLegal;
//----------------------------------------------Req���Ľӿ� [ReqOpenAccountPersonal] ����
// �ṹ����:���˿�����������
typedef struct tagReqOpenAccountPersonal  :public TReqMsg
{
	int        oper_flag;			//������־	�ǿ�	Ĭ���� 1
	char       cust_id[13];			//�ͻ�����	�ؿ�����
	char       account_no[33];		//�����˻�	�ǿ�
	char       account_name[41];	//���л�������	�ǿ�	
	char       open_account_date[9];//�˻���������	�ǿ�		
	char       account_due_date[9]; //�˻���������	�ǿ�
	char       cert_type_id;		//֤������	�ǿ�	
	char       cert_num[21];		//֤������	�ǿ�
	char       gess_branch_id[21];	//��֧����	�ǿ�	��Ĭ��ֵ������ʱ����
	char       gess_broker_id[21];	//�ͻ�����	�ǿ�	�̶�����
	char       gess_grade_id[21];	//�ͻ�����	�ǿ�	�̶�����
	char       mobile_phone[31];	//�ֻ�		�ǿ�
	char       tel[31];				//��ϵ�绰
	char       addr[81];			//��ϵ��ַ	�ǿ�
	char       zipcode[11];			//��������	�ǿ�
	char       email[81];			//��������	�ǿ�
	char       settle_bank_no[5];	//�����к�	�ǿ�
	char       nationality[41];		//����		�ǿ�
	char       birthday[9];		//��������	�ǿ�
	char       first_name[31];		//��		�ǿ�
	char       last_name[31];		//��		�ǿ�	
	char       middle_name[21];		//�м���	�ǿ�
	char       cert_open_date[9];	//֤��ǩ������	�ǿ�	����18900101����С�ڵ��ڵ�ǰ����
	char       cert_due_date[9];	//֤����Ч����	�ǿ�	����18900101����С�ڵ��ڵ�ǰ���� ֤����Ч�����������֤��ǩ������
	char       memo[255];			//��ע
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


//----------------------------------------------Rsp���Ľӿ� [onRecvRspOpenAccountPersonal] ����
// �ṹ����:���˿�������Ӧ������
typedef struct tagRspOpenAccountPersonal :public TRspMsg
{
	int      oper_flag;				//������־
	char	 cust_id[13];			//�ͻ�����
	tagRspOpenAccountPersonal()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
	}
}TRspOpenAccountPersonal,*PRspOpenAccountPersonal;

//----------------------------------------------Req���Ľӿ� [ReqModifyBankAcctBind] ����   
// �ṹ����:�ͻ������˻����޸ĵ���������                                        
typedef struct tagReqModifyBankAcctBind    :public TReqMsg                                         
{                                                                         
	int        oper_flag;			//������־	�ǿ�	Ĭ���� 0         
	char       cust_id[13];			//�ͻ�����	�ǿ�	                    
	char       acct_type;		//�˻�����	�ǿ�	���ַ��˿ͻ�����˿ͻ�	                    
	char       cert_type_id;		//֤������	�ǿ�	���˿ͻ���ָ����˾֤�����͡�                   
	char       cert_num[41];		//֤������	�ǿ�	���˿ͻ���ָ����˾֤���š�	                  
	char       new_account_no[31];	//�������˺�	�ǿ�    ���Ը�֮ǰ�����к�����ͬ����ʾ���°�
	char	   account_name[41];	//�����˻�����  �ǿ�
	char	   settle_bank_no[5];	//�����д���	�ǿ�
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspModifyBankAcctBind] ����   
// �ṹ����:�ͻ������˻����޸ĵ���Ӧ������                                        
typedef struct tagRspModifyBankAcctBind :public TRspMsg                             
{                                                                         
	int      oper_flag;				//������־                         
	tagRspModifyBankAcctBind()
	{
		oper_flag =	0;
	}
}TRspModifyBankAcctBind,*PRspModifyBankAcctBind;                                                       

//----------------------------------------------Req���Ľӿ� [ReqCancelAccount] ����
// �ṹ����:������������������
typedef struct tagReqCancelAccount  :public TReqMsg
{
	int      oper_flag;				//������־	�ǿ�	Ĭ���� 0 
	char     cust_id[13];			//�ͻ�����	�ǿ� 
	tagReqCancelAccount()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
	}
}TReqCancelAccount,*PReqCancelAccount;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspCancelAccount] ����
// �ṹ����:������������Ӧ������
typedef struct tagRspCancelAccount :public TRspMsg
{
	int      oper_flag;				//������־    
	char	 exch_date[9];			//��������	�ͻ������г���ʱ�Ż���ֵ
	char	 client_serial_no[41];	//�ͻ�����ˮ��	�ͻ������г���ʱ�Ż���ֵ
	tagRspCancelAccount()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
	}
}TRspCancelAccount,*PRspCancelAccount;

//----------------------------------------------Req���Ľӿ� [ReqModifyAcctInfoPersonal] ����
// �ṹ����:���˿ͻ���Ϣ�޸���������
typedef struct tagReqModifyAcctInfoPersonal  :public TReqMsg
{
	int        oper_flag;			//������־	�ǿ�	Ĭ���� 1 
	char       cust_id[13];			//�ͻ�����	�ǿ�		
	char       nationality[41];		//����	�ǿ�				
	char       birthday[9];			//��������	�ǿ�
	char       first_name[31];		//��	�ǿ�					
	char       last_name[31];		//��	�ǿ�				
	char       middle_name[21];		//�м���	�ǿ�			
	char       cert_open_date[9];	//֤��ǩ������	�ǿ�  ����18900101
	char       cert_due_date[9];	//֤����Ч����	�ǿ�  ����18900101��֤����Ч�����������֤��ǩ������
	char       mobile_phone[31];	//�ֻ�				
	char       tel[31];				//��ϵ�绰	�ǿ�	
	char       addr[81];			//��ϵ��ַ	�ǿ�
	char       zipcode[11];			//��������	�ǿ�		
	char       email[81];			//��������	�ǿ�	
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspModifyAcctInfoPersonal] ����
// �ṹ����:���˿ͻ���Ϣ�޸���Ӧ������
typedef struct tagRspModifyAcctInfoPersonal :public TRspMsg
{
	int      oper_flag;				//������־
	tagRspModifyAcctInfoPersonal()
	{
		oper_flag =	0;
	}
}TRspModifyAcctInfoPersonal,*PRspModifyAcctInfoPersonal;



//----------------------------------------------Req���Ľӿ� [ReqModifyAcctInfoLegal] ����
// �ṹ����:���˿ͻ���Ϣ�޸ĵ���������
typedef struct tagReqModifyAcctInfoLegal  :public TReqMsg
{
	int		 oper_flag;				//������־	�ǿ�	Ĭ���� 1              
	char	 cust_id[13];			//�ƽ��ױ���	�ǿ�          
	char	 corp_en_name[121];		//��˾Ӣ������	�ǿ�          
	char	 corp_chn_name[81];		//��˾��������	�ǿ�          
	char	 corp_en_abbr[21];		//��˾Ӣ�ļ��	�ǿ�          
	char	 corp_chn_abbr[21];		//��˾���ļ��	�ǿ�          
	char	 regist_addr[81];		//ע��� 	�ǿ�               
	char     cert_type;				//֤������	�ǿ�              
	char     cert_num[41];			//֤����	�ǿ�              
	char     corp_prop_id;			//��˾����	�ǿ�              
	char     corp_code[33];			//��ҵ��֯��������	�ǿ�      
	char     contacter[81];			//���˴���              
	char     mobile_phone[32];		//�ֻ�����              
	char     org_type[3];			//��������	�ǿ�              
	double   reg_capital;			//ע���ʱ�              
	char     pawnee_flag;			//��Ȩ�˱�־	�ǿ�            
	char     corp_regist_addr[121]; //��˾ע���ַ	�ǿ�          
	char     corp_zip[11];			//��˾�ʱ�	�ǿ�              
	char     corp_tel[31];			//��˾�绰	�ǿ�              
	char     corp_fax[31];			//��˾����	�ǿ�              
	char     corp_email[81];		//��˾��������	�ǿ�          
	char     copr_authorizer;		//��˾��Ȩ��	�ǿ�            
	char     auth_nationality[41];	//��Ȩ�˹���	�ǿ�            
	char     auth_cert_type_id;		//��Ȩ��֤������	�ǿ�    
	char     auth_cert_no[21];		//��Ȩ��֤����	�ǿ�        
	char     auth_addr[81];			//��Ȩ����ϵ��ַ	�ǿ�        
	char     auth_zip[11];			//��Ȩ���ʱ�	�ǿ�            
	char     auth_tel[31];			//��Ȩ�˵绰	�ǿ�            
	char     auth_fax[31];			//��Ȩ�˴���	�ǿ�            
	char     auth_email[81];		//��Ȩ�˵�������	�ǿ�        
	char     busi_license[21];		//Ӫҵִ��		�ǿ�              
	char     tax_cert[21];			//˰��Ǽ�֤	�ǿ�            
	char     org_code_cert[21];		//��֯��������֤	�ǿ�        
	char     regist_address[81];	//ע���ַ		�ǿ�              
	char     sigex_post_code[11];	//��ó���ʱ�	�ǿ�            
	char     sigex_tel[31];			//��ó���绰	�ǿ�            
	char     sigex_fax[31];			//��ó������	�ǿ�            
	char     sigex_email[81];		//��ó����������	�ǿ�        
	char     exec_name[41];			//���׾�����	�ǿ�            
	char     exec_tel[32];			//��������ϵ�绰        
	char     exec_cert_num[21];		//������֤������	�ǿ�        
	char     exec_cert_type_id;	//������֤������	�ǿ�	
	char     taxpayer_identifier[22];	//��˰��ʶ���          
	char     is_val_added_taxplayer;	//�Ƿ�Ϊ��ֵ˰һ����˰��
	char     taxplayer_address[82];		//��˰�˵�ַ            
	char     taxpayer_telephone[31];	//��˰�˵绰            
	char     taxpayer_bankcode[5];		//��˰�����д���        
	char     taxpayer_bankinfo[82];		//��˰�˿�������Ϣ      
	char     taxpayer_account_id[32];	//��˰���˺�            
	char     memo[255];				//��ע  
	char	 account_no[31];		//�����˺�
	char	 open_account_date[9];	//��������
	char	 account_due_date[9];	//�˻�������
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspModifyAcctInfoLegal] ����
// �ṹ����:���˿ͻ���Ϣ�޸ĵ���Ӧ������
typedef struct tagRspModifyAcctInfoLegal :public TRspMsg
{
	int      oper_flag;				//������־
	tagRspModifyAcctInfoLegal()
	{
		oper_flag =	0;
	}
}TRspModifyAcctInfoLegal,*PRspModifyAcctInfoLegal;

//----------------------------------------------Req���Ľӿ� [ReqMemberFareModelChange] ����
// �ṹ����:�ͻ���Ա����ģ������������
typedef struct tagReqMemberFareModelChange  :public TReqMsg
{
	int      oper_flag;				//������־	�ǿ�	Ĭ���� 0               
	char	 cust_id[13];			//�ͻ�����	�ǿ�          
	char	 gesas_fare_mode_id[21];//�»�Ա����ģ��	�ǿ�  
	tagReqMemberFareModelChange()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
		memset(gesas_fare_mode_id,0x00,sizeof(gesas_fare_mode_id));
	}
}TReqMemberFareModelChange,*PReqMemberFareModelChange;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspMemberFareModelChange] ����
// �ṹ����:�ͻ���Ա����ģ������Ӧ������
typedef struct tagRspMemberFareModelChange :public TRspMsg
{
	int      oper_flag;				//������־ 
	tagRspMemberFareModelChange()
	{
		oper_flag =	0;
	}
}TRspMemberFareModelChange,*PRspMemberFareModelChange;

//----------------------------------------------Req���Ľӿ� [ReqQueryAcctInfoPersonal] ����
// ���˿ͻ���Ϣ��ѯ��������
typedef struct tagReqQueryAcctInfoPersonal  :public TReqMsg
{
	int		oper_flag;			//������־	�ǿ�	Ĭ���� 1
	char	query_flag;			//��ѯ����	'1'-���������ʺŲ�ѯ�������˺ű���;'2'-����֤����ѯ��֤�����ͼ��������
	char	account_no[31];		//�����˺�	��query_flagΪ'1'ʱ���ǿ�
	char	cert_type_id;	//֤������	��query_flagΪ'2'ʱ���ǿ�
	char	cert_num[21];		//֤������	��query_flagΪ'2'ʱ���ǿ�  
	tagReqQueryAcctInfoPersonal()
	{
		oper_flag =	0;
		query_flag = 0;
		memset(account_no,0x00,sizeof(account_no));
		cert_type_id = 0;
		memset(cert_num,0x00,sizeof(cert_num));
	}
}TReqQueryAcctInfoPersonal,*PReqQueryAcctInfoPersonal;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspQueryAcctInfoPersonal] ����
// �ṹ����:���˿ͻ���Ϣ��ѯ��Ӧ������
typedef struct tagRspQueryAcctInfoPersonal :public TRspMsg
{
	int		oper_flag;				//������־        
	char    cust_id[13];			//�ͻ�����               	       
	char    settle_bank_no[5];		//�����к�	        
	char    account_no[31];			//�����˻�	        
	char    account_name[41];		//���л�������	    
	char    open_account_date[9];	//�˻���������    
	char    account_due_date[9];	//�˻���������	   
	char    cert_type_id;			//֤������		        
	char    cert_num[21];			//֤������ 	       
	char    gess_fare_mode_id[21];	//�������ķ���ģ��	
	char    gesas_fare_mode_id[21]; //��Ա����ģ��	    
	char    gess_broker_id[21];		//�ͻ�����	        
	char    grade_id[21];			//�ͻ�����	        
	char    mobile_phone[31];		//�ֻ� 		           
	char    tel[31];				//��ϵ�绰        
	char    addr[81];				//��ϵ��ַ	        
	char    zipcode[11];			//�������� 	       
	char    email[81];				//��������        
	char    nationality[41];		//����     	       
	char    birthday[9];			//��������        
	char    first_name[31];			//��      	        
	char    last_name[31];			//��    	          
	char    middle_name[21];		//�м���       
	char    cert_open_date[11];		//֤��ǩ������   
	char    cert_due_date[11];		//֤����Ч����    
	char    acct_stat[3];			//�ͻ�״̬        
	char    memo[255];				//��ע  
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

//----------------------------------------------Req���Ľӿ� [ReqQueryAcctInfoLegal] ����
// ���˿ͻ���Ϣ��ѯ��������
typedef struct tagReqQueryAcctInfoLegal  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1
	char      query_flag;		//��ѯ����	'1'-���������ʺŲ�ѯ�������˺ű���;'2'-����֤����ѯ��֤�����ͼ��������
	char      account_no[31];	//�����˺�	��query_flagΪ'1'ʱ���ǿ�
	char      cert_type_id;		//֤������	��query_flagΪ2ʱ���ǿ�
	char      cert_num[41];		//֤������	��query_flagΪ2ʱ���ǿ�
	tagReqQueryAcctInfoLegal()
	{
		oper_flag =	0;
		query_flag = 0;
		memset(account_no,0x00,sizeof(account_no));
		cert_type_id = 0;
		memset(cert_num,0x00,sizeof(cert_num));
	}
}TReqQueryAcctInfoLegal,*PReqQueryAcctInfoLegal;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspQueryAcctInfoLegal] ����
// �ṹ����:���˿ͻ���Ϣ��ѯ��Ӧ������
typedef struct tagRspQueryAcctInfoLegal :public TRspMsg
{
	int           oper_flag;			//������־		Ĭ���� 0                          
	char          corp_en_name[121];	//��˾Ӣ������                        
	char          corp_chn_name[81];	//��˾��������                        
	char          corp_en_abbr[21];		//��˾Ӣ�ļ��                        
	char          corp_chn_abbr[21];	//��˾���ļ��                        
	char          settle_bank_no[5];	//�����к�                            
	char          account_no[31];		//�����˻�                            
	char          account_name[41];		//����                                
	char          open_account_date[9];	//��������                            
	char          account_due_date[9];	//��������                            
	char          regist_addr[81];		//ע���                              
	char          cert_type;			//֤������                            
	char          cert_num[41];			//֤����                            
	char          corp_prop_id[9];		//��˾����                            
	char          corp_regist_addr[121];//��˾ע���ַ                        
	char          corp_zip[11];			//��˾�ʱ�                            
	char          corp_tel[31];			//��˾�绰                            
	char          corp_fax[31];			//��˾����                            
	char          corp_email[81];		//��˾��������                        
	char          copr_authorizer[3];	//��˾��Ȩ��\����\����\������         
	char          auth_nationality[41];	//��Ȩ�˹���                          
	char          auth_cert_type_id;	//��Ȩ��֤����	                
	char          auth_cert_no[21];		//��Ȩ��֤������                      
	char          auth_addr[81];		//��Ȩ����ϵ��ַ                      
	char          auth_zip[11];			//��Ȩ���ʱ�                          
	char          auth_tel[31];			//��Ȩ�˵绰                          
	char          auth_fax[31];			//��Ȩ�˴���                          
	char          auth_email[81];		//��Ȩ�˵�������                      
	char          busi_license[21];		//Ӫҵִ��                            
	char          tax_cert[21];			//˰��Ǽ�֤                          
	char          org_code_cert[21];	//��֯��������֤                      
	char          regist_address[81];	//ע���ַ                            
	char          sigex_post_code[11];	//��ó���ʱ�                          
	char          sigex_tel[31];		//��ó���绰                          
	char          sigex_fax[31];		//��ó������                          
	char          sigex_email[81];		//��ó����������                      
	char          cust_id[13];			//�ƽ��ױ���                        
	char          gess_broker_id[21];	//�ͻ������                          
	char          exec_name[31];		//���׾�����                          
	char          exec_cert_type_id;	//������֤������	              
	char          exec_cert_num[21];	//������֤������                      
	char          corp_code[33];		//��ҵ��֯��������                    
	char          contacter[81];		//���˴���                            
	char          org_type[3];			//��������                            
	double        reg_capital;			//ע���ʱ�                            
	char          corp_type[3];			//��ҵ���                            
	char          taxpayer_identifier[22];	//��˰��ʶ���                        
	char          is_val_added_taxplayer;	//�Ƿ�Ϊ��ֵ˰һ����˰��              
	char          taxplayer_address[82];	//��˰�˵�ַ                          
	char          taxpayer_telephone[31];	//��˰�˵绰                          
	char          taxpayer_bankcode[5];		//��˰�����д���                      
	char          taxpayer_bankinfo[81];	//��˰�˿�������Ϣ                    
	char          taxpayer_account_id[32];	//��˰���˺�                          
	char          grade_id[21];			//�ͻ�����                            
	char          acct_stat[3];			//�ͻ�״̬                            
	char          memo[255];			//��ע 
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

//----------------------------------------------Req���Ľӿ� [ReqTransferApply] ����
// �ṹ����:�ͻ������������������
typedef struct tagReqTransferApply  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 0
	char      f_busi_type;		//ҵ������	�ǿ�
	char      exch_date[9];		//��������	�ǿ�
	char      cust_no[13];		//�ͻ���	�ǿ�  
	char      access_way;		//��ȡ��־	�ǿ�
	char      currency_id;		//���� 		�ǿ�   
	double    exch_bal;			//�������	�ǿ�	С�������λ Ĭ��0.0
	char      remark[255];		//��ע    
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspTransferApply] ����
// �ṹ����:�ͻ������������Ӧ������
typedef struct tagRspTransferApply :public TRspMsg
{                              
	int       oper_flag;			//������־     
	char      gess_exch_date[9];	//��������   
	char	  client_serial_no[19];	//������ˮ��		�����ĵı�ʶ�ţ������ڳ������ˮ��ѯ
	char      gess_serial_no[33];	//����������ˮ��	���׳ɹ�������ˮ��
	char      bk_serial_no[41];		//��������ˮ��		���׳ɹ�������ˮ��
	tagRspTransferApply()
	{
		oper_flag =	0;
		memset(gess_exch_date,0x00,sizeof(gess_exch_date));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
		memset(gess_serial_no,0x00,sizeof(gess_serial_no));
		memset(bk_serial_no  ,0x00,sizeof(bk_serial_no  ));
	}
}TRspTransferApply,*PRspTransferApply;

//----------------------------------------------Req���Ľӿ� [ReqQueryAcctTransfer] ����
// �ṹ����:�ͻ��������ˮ��ѯ��������
typedef struct tagReqQueryAcctTransfer  :public TReqMsg
{
	int       oper_flag;			//������־	�ǿ�	Ĭ���� 0 
	char      gess_exch_date[9];	//��������	�ǿ�  
	char      client_serial_no[21];	//������ˮ��	�ǿ�	����������ˮ��
	tagReqQueryAcctTransfer()
	{
		oper_flag =	0;
		memset(gess_exch_date  ,0x00,sizeof(gess_exch_date  ));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
	}
}TReqQueryAcctTransfer,*PReqQueryAcctTransfer;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspQueryAcctTransfer] ����
// �ṹ����:�ͻ��������ˮ��ѯ��Ӧ������
typedef struct tagRspQueryAcctTransfer :public TRspMsg
{                              
	int       oper_flag;			//������־    Ĭ���� 0      
	char      exch_date[9];			//��������          
	char      serial_no[33];		//����������ˮ��    
	char      client_serial_no[21];	//������ˮ��        
	char      acct_no[13];			//�ͻ���            
	char      settle_bank_no[5];	//�����к�          
	char      f_busi_type;			//ҵ������          
	char      access_way;			//��ȡ����          
	char      out_account_no[31];	//���������˺�      
	char      in_account_no[31];	//��������˺�      
	double    exch_bal;				//�������          
	char      check_stat1;			//����״̬1         
	char      check_stat2;			//����״̬2         
	char      send_stat;			//����״̬          
	char      in_account_flag;		//�Ƿ�������        
	char      remark[255];			//��ע              
	char      bk_plat_date[9];		//��������          
	char      bk_seq_no[33];		//��������ˮ��      
	char      bk_rsp_code[21];		//��������Ӧ����    
	char      bk_rsp_msg[201];		//��������Ӧ��Ϣ    
	char      o_term_type[3];		//������Դ          
	char      o_teller_id[11];		//�����û���        
	char      o_date[21];			//��������          
	char      c_term_type1[3];		//����1��Դ         
	char      c_teller_id1[11];		//����1�û���       
	char      c_date1[21];			//����1����         
	char      c_term_type2[3];		//����2��Դ         
	char      c_teller_id2[11];		//����2�û���       
	char      c_date2[21];			//����2����  
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

//----------------------------------------------Req���Ľӿ� [ReqSigexMemTransferApply] ����
// �ṹ����:���Ļ�Ա�����������������
typedef struct tagReqSigexMemTransferApply  :public TReqMsg
{
	int      oper_flag;			//������־	�ǿ�	Ĭ���� 0 
	char     f_busi_type;		//ҵ������	�ǿ�
	char     exch_date[9];		//�������� 	�ǿ� 
	char     access_way;		//��ȡ��־	�ǿ�
	char     currency_id;		//����	�ǿ�    
	double   exch_bal;			//�������	�ǿ�	С�������λ Ĭ��0.0
	char     remark[255];		//��ע    
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspSigexMemTransferApply] ����
// �ṹ����:���Ļ�Ա�����������Ӧ������
typedef struct tagRspSigexMemTransferApply :public TRspMsg
{                              
	int       oper_flag;			//������־      
	char      gess_exch_date[9];	//��������  
	char	  client_serial_no[19];	//������ˮ��		�����ĵı�ʶ�ţ������ڳ������ˮ��ѯ
	char      gess_serial_no[33];	//����������ˮ��	���׳ɹ�������ˮ��
	char      bk_serial_no[41];		//��������ˮ��		���׳ɹ�������ˮ��  
	tagRspSigexMemTransferApply()
	{
		oper_flag =	0;
		memset(gess_exch_date  ,0x00,sizeof(gess_exch_date  ));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
		memset(gess_serial_no  ,0x00,sizeof(gess_serial_no  ));
		memset(bk_serial_no    ,0x00,sizeof(bk_serial_no    ));
	}
}TRspSigexMemTransferApply,*PRspSigexMemTransferApply;

//----------------------------------------------Req���Ľӿ� [ReqQuerySigexMemTransfer] ����
// �ṹ����:���Ļ�Ա�������ˮ��ѯ��������
typedef struct tagReqQuerySigexMemTransfer  :public TReqMsg
{
	int       oper_flag;			//������־	�ǿ�	Ĭ���� 1   
	char      gess_exch_date[9];	//��������	�ǿ�   
	char      client_serial_no[19];	//������ˮ��	�ǿ�	����������ˮ��
	tagReqQuerySigexMemTransfer()
	{
		oper_flag =	0;
		memset(gess_exch_date  ,0x00,sizeof(gess_exch_date  ));
		memset(client_serial_no,0x00,sizeof(client_serial_no));
	}
}TReqQuerySigexMemTransfer,*PReqQuerySigexMemTransfer;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspQuerySigexMemTransfer] ����
// �ṹ����:���Ļ�Ա�������ˮ��ѯ��Ӧ������
typedef struct tagRspQuerySigexMemTransfer :public TRspMsg
{                              
	int       oper_flag;			//������־        
	char      exch_date[9];			//��������      
	char      serial_no[33];		//����������ˮ��
	char      client_serial_no[19];	//������ˮ��                
	char      settle_bank_no[5];	//�����к�      
	char      f_busi_type;			//ҵ������      
	char      access_way;			//��ȡ����      
	char      out_account_no[31];	//���������˺�  
	char      in_account_no[31];	//��������˺�  
	double    exch_bal;				//�������      
	char      check_stat1;			//����״̬1     
	char      check_stat2;			//����״̬2     
	char      send_stat;			//����״̬      
	char      in_account_flag;		//�Ƿ�������    
	char      remark[255];			//��ע          
	char      bk_plat_date[9];		//��������      
	char      bk_seq_no[41];		//��������ˮ��  
	char      bk_rsp_code[21];		//��������Ӧ����
	char      bk_rsp_msg[201];		//��������Ӧ��Ϣ
	char      o_term_type[3];		//������Դ      
	char      o_teller_id[11];		//�����û���    
	char      o_date[21];			//��������      
	char      c_term_type1[3];		//����1��Դ     
	char      c_teller_id1[11];		//����1�û���   
	char      c_date1[21];			//����1����     
	char      c_term_type2[3];		//����2��Դ     
	char      c_teller_id2[11];		//����2�û���   
	char      c_date2[21];			//����2����     
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

//----------------------------------------------Req���Ľӿ� [ReqEntrOrder] ����
// �ṹ����:ί�б�����������
typedef struct tagReqEntrOrder  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1       
	char      cust_id[13];		//�ͻ�����	�ǿ�      
	char      prod_code[9];	//��Լ����	�ǿ�      
	char      req_exch_code[5];	//���״���	�ǿ�      
	double    price;			//ί�м۸�  �����걨���������걨���۸�ɲ������������д�۸�    
	int       volume;			//ί������	�ǿ�      
	char      is_force_order;	//�Ƿ���ǿƽ����	�ǿ�
	char	  gess_local_order_no[15];//���ر����� �ǿ� 
	char	  order_send_type;	//�������ͷ�ʽ �ǿ�
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspEntrOrder] ����
// �ṹ����:ί�б�����Ӧ������
typedef struct tagRspEntrOrder :public TRspMsg
{                              
	int       oper_flag;				//������־
	char	  client_serial_no[21];		//������ˮ��	�����ĵı�ʶ�ţ������ڱ�����ˮ��ѯ
	char      gess_local_order_no[15];	//���ر�����        
	char      gess_serial_no[33];		//�������ı�����ˮ��
	tagRspEntrOrder()
	{
		oper_flag =	0;
		memset(client_serial_no,0x00,sizeof(client_serial_no));
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(gess_serial_no	  ,0x00,sizeof(gess_serial_no	  ));
	}
}TRspEntrOrder,*PRspEntrOrder;

//----------------------------------------------Req���Ľӿ� [ReqEntrCancel] ����
// �ṹ����:ί�г�����������
typedef struct tagReqEntrCancel  :public TReqMsg
{
	int       oper_flag;				//������־	�ǿ�	Ĭ���� 1    
	char      gess_local_order_no[15];	//���ر�����	�ǿ�  
	char      order_no[17];				//������������	�ǿ�
	tagReqEntrCancel()
	{
		oper_flag =	0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(order_no			  ,0x00,sizeof(order_no			  ));
	}
}TReqEntrCancel,*PReqEntrCancel;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspEntrCancel] ����
// �ṹ����:ί�г�����Ӧ������
typedef struct tagRspEntrCancel :public TRspMsg
{                              
	int       oper_flag;				//������־ 
	char      gess_local_order_no[15];	//���ر�����
	tagRspEntrCancel()
	{
		oper_flag =	0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
	}
}TRspEntrCancel,*PRspEntrCancel;

//----------------------------------------------Req���Ľӿ� [ReqEndDayListConfirm] ����
// �ṹ����:�սᵥȷ����������
typedef struct tagReqEndDayListConfirm  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1     
	char      cust_id[13];		//�ƽ��ױ���	�ǿ�
	char      exch_date[9];		//ȷ�Ͻ�������	�ǿ�
	tagReqEndDayListConfirm()
	{
		oper_flag =	0;
		memset(cust_id  ,0x00,sizeof(cust_id  ));
		memset(exch_date,0x00,sizeof(exch_date));
	}
}TReqEndDayListConfirm,*PReqEndDayListConfirm;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspEndDayListConfirm] ����
// �ṹ����:�սᵥȷ����Ӧ������
typedef struct tagRspEndDayListConfirm :public TRspMsg
{                              
	int         oper_flag;		//������־  
	tagRspEndDayListConfirm()
	{
		oper_flag =	0;
	}
}TRspEndDayListConfirm,*PRspEndDayListConfirm;

//----------------------------------------------Req���Ľӿ� [ReqQueryEntrFlow] ����
// �ṹ����:ί����ˮ��ѯ��������
typedef struct tagReqQueryEntrFlow  :public TReqMsg
{
	int       oper_flag;				//������־	�ǿ�	Ĭ���� 1   
	char      client_serial_no[41];		//������ˮ��	�ǿ� 
	char      gess_local_order_no[15];	//���ر����� 	�ǿ�
	tagReqQueryEntrFlow()
	{
		oper_flag =	0;
		memset(client_serial_no	  ,0x00,sizeof(client_serial_no	  ));
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
	}
}TReqQueryEntrFlow,*PReqQueryEntrFlow;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspQueryEntrFlow] ����
// �ṹ����:ί����ˮ��ѯ��Ӧ������
typedef struct tagRspQueryEntrFlow :public TRspMsg
{                              
	int       oper_flag;				//������־             
	char      order_no[17];				//������������         
	char      client_serial_no[41];		//������ˮ��           
	char      gess_local_order_no[15];	//���ر�����           
	char      gess_serial_no[33];		//�������ı�����ˮ��   
	char      cust_id[13];				//�ͻ�����             
	char      req_exch_code[5];			//���״���             
	char      market_id[3];				//�����г�             
	char      prod_code[9];				//��Լ����             
	double    entr_price;				//ί�м۸�             
	int       entr_amount;				//ί������             
	int       remain_amount;			//ʣ������             
	char      offset_flag;				//��ƽ��־             
	char      deli_flag;				//���ձ�־             
	char      bs;						//��������             
	double    exch_bal;					//�������             
	double    froz_margin;				//��֤�𶳽���       
	double    exch_fare;				//���׷���             
	char      cov_type[3];				//ƽ�ַ�ʽ             
	char      src_match_no[17];			//ָ����λ��           
	char      origin_order_no[17];		//ԭ������             
	char      match_type[3];			//��������             
	char      order_send_type[3];		//�������ͷ�ʽ         
	char      entr_stat;				//ί��״̬             
	char      cancel_flag;				//������־             
	char      exch_date[9];				//��������             
	char      accept_time[9];			//Ӧ��ʱ��             
	char      e_term_type[3];			//ί����Դ             
	char      e_branch_id[21];			//ί�з�֧����         
	char      e_teller_id[11];			//ί�в���Ա           
	char      e_trader_id[11];			//ί�н���Ա           
	char      e_exch_time[9];			//ί��ʱ��             
	char      c_term_type[3];			//������Դ             
	char      c_teller_id[11];			//��������Ա           
	char      c_trader_id[11];			//��������Ա           
	char      c_exch_time[9];			//����ʱ��             
	char      rsp_msg[201];				//������Ӧ             
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

//----------------------------------------------Req���Ľӿ� [ReqRefPriceApply] ����
// �ṹ����:�����г��ο����걨��������
typedef struct tagReqRefPriceApply  :public TReqMsg
{
	int			oper_flag;			//������־	�ǿ� Ĭ���� 1
	char    	cust_id[13];		//�ͻ�����	�ǿ� ֻ������Ӫ�ͻ���
	char    	game_id[11];		//���α��	�ǿ�
	double		report_price;		//�ο��۸�	�ǿ�
	char		prod_code[9];		//��Լ����	�ǿ�
	char		exch_date[9];		//��������	�ǿ�
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspRefPriceApply] ����
// �ṹ����:�����г��ο����걨��Ӧ������
typedef struct tagRspRefPriceApply :public TRspMsg
{                              
	int        oper_flag;			//������־    
	tagRspRefPriceApply()
	{
		oper_flag =	0;
	}
}TRspRefPriceApply,*PRspRefPriceApply;

//----------------------------------------------Req���Ľӿ� [ReqFpEntrOrder] ����
// �ṹ����:�����г�ί���걨��������
typedef struct tagReqFpEntrOrder  :public TReqMsg
{
	int 		 oper_flag;				//������־	�ǿ� Ĭ���� 1
	char		 cust_id[13];			//�ͻ�����	�ǿ�
	char		 game_id[11];			//���α��	�ǿ�
	char		 bs;					//��������	�ǿ�
	char		 order_type[3];			//�걨��ʽ	�ǿ�
	int 		 volume;				//�걨����	�ǿ� 
	char		 prod_code[9];			//��Լ���� 	�ǿ�        
	int			 round_id;				//�ִα��	�ǿ�          
	char		 order_send_type[3];	//�������ͷ�ʽ	�ǿ�      
	double		 entr_price;			//ί�м۸�	�ǿ�          
	char		 gess_local_order_no[15];//����ϵͳ���ر�����	�ǿ�
	char		 gess_serial_no[33];	//����ϵͳ������ˮ 	�ǿ� 
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspFpEntrOrder] ����
// �ṹ����:�����г�ί���걨��Ӧ������
typedef struct tagRspFpEntrOrder :public TRspMsg
{                              
	int      oper_flag;					//������־        
	char     gess_local_order_no[15];	//���ر�����  
	char     gess_serial_no[33];		//�������ı�����ˮ��      
	tagRspFpEntrOrder()
	{
		oper_flag =	0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
		memset(gess_serial_no	  ,0x00,sizeof(gess_serial_no	  ));
	}
}TRspFpEntrOrder,*PRspFpEntrOrder;
//----------------------------------------------Req���Ľӿ� [ReqFpEntrCancel] ����
// �ṹ����:�����г�ί�г�����������
typedef struct tagReqFpEntrCancel  :public TReqMsg
{
	int 		    oper_flag;			//������־	�ǿ� Ĭ���� 1
	char			acct_no[13];		//�ͻ���	�ǿ�  
	char		 	prod_code[9];		//��Լ����	�ǿ�
	char		 	bs;					//��������	�ǿ�
	tagReqFpEntrCancel()
	{
		oper_flag =	0;
		memset(acct_no	,0x00,sizeof(acct_no  ));
		memset(prod_code,0x00,sizeof(prod_code));
		bs = 0;
	}
}TReqFpEntrCancel,*PReqFpEntrCancel;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspFpEntrCancel] ����
// �ṹ����:�����г�ί�г�����Ӧ������
typedef struct tagRspFpEntrCancel :public TRspMsg
{                              
	int        oper_flag;				//������־          
	tagRspFpEntrCancel()
	{
		oper_flag =	0;
	}
}TRspFpEntrCancel,*PRspFpEntrCancel;
//----------------------------------------------Req���Ľӿ� [ReqRefPriceQueryFlow] ����
// �ṹ����:�����г��ο��۱�����ˮ��ѯ��������
typedef struct tagReqRefPriceQueryFlow   :public TReqMsg
{
	int			oper_flag;				//������־	�ǿ�	Ĭ���� 1
	char    	game_id[11];			//���α��	�ǿ�
	char		prod_code[9];			//��Լ����	�ǿ�
	tagReqRefPriceQueryFlow()
	{
		oper_flag =	0;
		memset(game_id	,0x00,sizeof(game_id  ));
		memset(prod_code,0x00,sizeof(prod_code));
	}
}TReqRefPriceQueryFlow,*PReqRefePricQueryFlow;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspRefPriceQueryFlow] ����
// �ṹ����:�����г��ο��۱�����ˮ��ѯ��Ӧ������
typedef struct tagRspRefPriceQueryFlow :public TRspMsg
{                              
	int       oper_flag;			//������־          
	int		  num_ref_price;		//�ο��۱����б� ��¼����
	struct tagRefPrice
	{
		char	prod_code[9];		//��Լ����
		double	report_price;		//�ο��۸�
		char    exch_date[9];		//��������  
		char    game_id[11];		//���α�� 
		char    member_id[7];		//��Ա��� 
		char	serial[19];			//��ˮ��
		char	report_time[21];	//����ʱ��
	}		  * p_ref_price;		//�ο��۱����б� 
	tagRspRefPriceQueryFlow()
	{
		oper_flag =	0;
		num_ref_price =	0;
		p_ref_price = NULL;
	}
}TRspRefPriceQueryFlow,*PRspRefPriceQueryFlow;
//----------------------------------------------Req���Ľӿ� [ReqFpEntrOrderQueryFlow] ����
// �ṹ����:�����г�ί���걨��ˮ��ѯ��������
typedef struct tagReqFpEntrOrderQueryFlow  :public TReqMsg
{
	int 		  oper_flag;				//������־	�ǿ�	Ĭ���� 1
	char		  gess_local_order_no[15];	//���ر�����	�ǿ�
	tagReqFpEntrOrderQueryFlow()
	{
		oper_flag =	0;
		memset(gess_local_order_no,0x00,sizeof(gess_local_order_no));
	}
}TReqFpEntrOrderQueryFlow,*PReqFpEntrOrderQueryFlow;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspFpEntrOrderQueryFlow] ����
// �ṹ����:�����г�ί���걨��ˮ��ѯ��Ӧ������
typedef struct tagRspFpEntrOrderQueryFlow :public TRspMsg
{                              
	int		  oper_flag;		//������־  	
	char      exch_date[9];		//��������  	
	int       order_no;			//������    	
	char      gess_local_order_no[15];	//���ر�����	
	char      acct_no[13];		//�ͻ���    	
	char      market_id[3];		//�����г�  	
	char      prod_code[9];		//��Լ����  	
	char      game_id[11];		//���α��  	
	int       round_id;			//ί���ִ�  	
	char      entr_phase;		//�걨�׶�  	
	char      bs;				//��������  	
	double    entr_price;		//ί�м۸�  	
	int       entr_amount;		//ί������  	
	int       entr_weight;		//ί������  	
	double    froz_margin;		//���ᱣ֤��	
	double    froz_exch_fare;	//����������	
	char      entr_stat;		//ί��״̬  	
	char      cancel_flag;		//������־  	
	char      e_term_type[3];	//ί����Դ  	
	char      e_trader_id[11];	//ί�н���Ա	
	char      entr_time[21];	//ί��ʱ��  	
	char      c_term_type[3];	//������Դ  	
	char      c_trader_id[11];	//��������Ա	
	char      cancel_time[21];	//����ʱ��  	    
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
//----------------------------------------------Req���Ľӿ� [ReqTakeApply] ����
// �ṹ����:���������������
typedef struct tagReqTakeApply  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1      
	char      cust_id[13];		//�ͻ�����	�ǿ�      
	char      variety_id[4];	//����Ʒ�ִ���	�ǿ�  
	int       app_amount;		//�����׼����	�ǿ�  
	char      city_code[7];		//������� 	�ǿ�     
	char      stor_id[5];		//�ֿ����	�ǿ�      
	char      take_man[21];		//�����	�ǿ�        
	char      cert_type_id;		//�����֤������	�ǿ�	
	char      cert_num[21];		//�����֤������	�ǿ�
	char      app_pwd[255];		//�������	�ǿ�	����      
	char      app_record[11];	//����¼����    
	int       self_draw;		//��������	�ǿ�   
	int       trade_draw;		//�������� 	�ǿ�     
	char      gold_forword;		//ʵ������ 	�ǿ�     
	char      remark[255];		//��ע   	�ǿ�       
	char      take_date[9];		//������� 	�ǿ�     
	char      lend_check_no[11];//���ǼǱ�� 
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspTakeApply] ����
// �ṹ����:���������Ӧ������
typedef struct tagRspTakeApply :public TRspMsg
{                              
	int      oper_flag;					//������־        
	char     gess_local_sheet_no[17];	//������������  
	char     sheet_no[15];				//��������      
	char     cust_id[13];				//�ͻ�����        
	char     send_stat;					//����״̬        
	char     stat;						//���״̬        
	double   take_margin;				//�����֤��
	char	 is_other_take;				//�Ƿ���������
	char     app_start_date[9];			//���������ʼ����
	char     app_end_date[9];			//���������ֹ����
	char     variety_id[4];				//����Ʒ�ִ���    
	int      app_amount;				//�����׼����    
	char     draw_type;					//�������        
	int      self_draw;					//��������        
	int      trade_draw;				//��������        
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

//----------------------------------------------Req���Ľӿ� [ReqTakeApplyCancel] ����
// �ṹ����:������볷����������
typedef struct tagReqTakeApplyCancel :public TReqMsg 
{
	int       oper_flag;				//������־	�ǿ�	Ĭ���� 1       
	char      gess_local_sheet_no[17];	//������������	�ǿ�
	char      sheet_no[15];				//��������	�ǿ�    
	char      cust_id[13];				//�ͻ�����	�ǿ�      
	char      take_man[21];				//�����    �ǿ�
	char      take_pwd[255];				//�������	�ǿ�	����    
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspTakeApplyCancel] ����
// �ṹ����:������볷����Ӧ������
typedef struct tagRspTakeApplyCancel :public TRspMsg
{                              
	int       oper_flag;				//������־      
	char      gess_local_sheet_no[17];	//������������
	char      sheet_no[15];				//��������    
	char      cust_id[13];				//�ͻ�����      
	char      stat;						//���״̬      
	tagRspTakeApplyCancel()
	{
		oper_flag =	0;
		memset(gess_local_sheet_no,0x00,sizeof(gess_local_sheet_no));
		memset(sheet_no           ,0x00,sizeof(sheet_no           ));
		memset(cust_id            ,0x00,sizeof(cust_id            ));
		stat = 0;
	}
}TRspTakeApplyCancel,*PRspTakeApplyCancel;

//----------------------------------------------Req���Ľӿ� [ReqQueryTakeList] ����
// �ṹ����:�������ѯ��������
typedef struct tagReqQueryTakeList  :public TReqMsg
{
	int       oper_flag;				//������־	�ǿ�	Ĭ���� 1       
	char      gess_local_sheet_no[17];	//������������	�ǿ�
	char      sheet_no[15];				//��������	
	tagReqQueryTakeList()
	{
		oper_flag =	0;
		memset(gess_local_sheet_no,0x00,sizeof(gess_local_sheet_no));
		memset(sheet_no           ,0x00,sizeof(sheet_no           ));
	}
}TReqQueryTakeList,*PReqQueryTakeList;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspQueryTakeList] ����
// �ṹ����:�������ѯ��Ӧ������
typedef struct tagRspQueryTakeList :public TRspMsg
{					               
	int       oper_flag;				//������־        
	char      gess_local_sheet_no[17];	//������������  
	char      sheet_no[15];				//��������      
	char      cust_id[13];				//�ͻ�����        
	char      variety_id[4];			//����Ʒ�ִ���    
	int       app_amount;				//�����׼����    
	char      draw_type;				//�������        
	int       self_draw;				//��������        
	int       trade_draw;				//��������        
	char      city_code[7];				//�������        
	char      stor_id[5];				//�ֿ����        
	char      take_man[21];				//�����          
	char      cert_type_id;			//�����֤������	  
	char      cert_num[21];				//�����֤������  
	char      app_record[32];			//����¼����      
	char      app_date[9];				//������������    
	char      app_time[9];				//��������ʱ��    
	char      app_exch_date[9];			//���뽻������    
	char      app_start_date[9];		//���������ʼ����
	char      app_end_date[9];			//���������ֹ����
	char      due_take_date[9];			//Ԥ���������    
	char      stat;						//���״̬        
	char      cancel_date[9];			//������������    
	char      cancel_time[9];			//����ʱ��        
	char      cancel_exch_date[9];		//������������    
	char      cancel_record[21];		//����¼����      
	char      send_stat;				//����״̬        
	double    take_margin;				//�����֤��      
	char      is_other_take;			//�Ƿ�������    
	char      take_affirm;				//������ȷ��    
	char      take_rsp_code[21];		//�����Ӧ����        
	char      take_rsp_msg[201];		//�����Ӧ��Ϣ        
	char      gold_forword;				//ʵ������        
	char      remark[255];				//��ע            
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

//----------------------------------------------Req���Ľӿ� [ReqTransferDataDownload] ����
// �ṹ����:���г�����������������������
typedef struct tagReqTransferDataDownload  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1 
	char      exch_date[9];		//��������	�ǿ�
	char      branchID[21];		//��֧����	�ǿ�
	tagReqTransferDataDownload()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(branchID ,0x00,sizeof(branchID ));
	}
}TReqTransferDataDownload,*PReqTransferDataDownload;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspTransferDataDownload] ����
// �ṹ����:���г�����������������Ӧ������
typedef struct tagRspTransferDataDownload :public TRspMsg
{                              
	int         oper_flag;		//������־ 
	int			num_checksum;	//������ˮ��������
	struct tagAlmChecksum		 
	{
		int		sum_num;		//�ܱ���
		double	sum_bal;		//�ܽ��
		int		in_num;			//ת�����
		double	in_bal;			//ת����
		int		out_num;		//ת������
		double	out_bal;		//ת�����
		char	currency_id;	//����   
	}			* p_checksum;	//������ˮ����
	
	int			num_checkdetail;//������ˮ��ϸ������
	struct tagAlmCheckdetail	
	{
		char	exch_date[9];	//��������
		char	bank_seq[33];	//������ˮ��
		char	gess_serial_no[33];		//����������ˮ��
		char	client_serial_no[21];	//������ˮ��
		char	account_no[33]; //�����˺�	
		char    cust_no[13];	//�ͻ��� 
		char    f_busi_type;	//ҵ������
		char    access_way;		//��ȡ��־
		double	exch_bal;		//���׽��
		char	currency_id;	//����  
	}			* p_checkdetail;//������ˮ��ϸ 
	tagRspTransferDataDownload()
	{
		oper_flag =	0;
		num_checksum =	0;
		p_checksum = NULL;
		num_checkdetail =	0;
		p_checkdetail =	NULL;
	}
}TRspTransferDataDownload,*PRspTransferDataDownload;

//----------------------------------------------Req���Ľӿ� [ReqLiquDataDownload] ����
// �ṹ����:������������������������
typedef struct tagReqLiquDataDownload  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1
	char      exch_date[9];		//��������	�ǿ�
	char      branchID[21];		//��֧����	�ǿ�
	tagReqLiquDataDownload()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(branchID ,0x00,sizeof(branchID ));
	}
}TReqLiquDataDownload,*PReqLiquDataDownload;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspLiquDataDownload] ����
// �ṹ����:������������������Ӧ������
typedef struct tagRspLiquDataDownload :public TRspMsg
{                              
	int       oper_flag;				//������־      
	char      newxml_file_addr[1024];	//NewXML�ļ���ַ
	char	  sftp_user_name[21];		//����Ա����
	char	  sftp_pwd[61];				//��¼����
	tagRspLiquDataDownload()
	{
		oper_flag =	0;
		memset(newxml_file_addr,0x00,sizeof(newxml_file_addr));
		memset(sftp_user_name  ,0x00,sizeof(sftp_user_name  ));
		memset(sftp_pwd		   ,0x00,sizeof(sftp_pwd	    ));
	}
}TRspLiquDataDownload,*PRspLiquDataDownload;

//----------------------------------------------Req���Ľӿ� [ReqFundCheckDataDownload] ����
// �ṹ����:���ն��˻�������������������
typedef struct tagReqFundCheckDataDownload  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1
	char      exch_date[9];		//��������	�ǿ�
	char      branchID[21];		//��֧����	�ǿ�
	tagReqFundCheckDataDownload()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(branchID ,0x00,sizeof(branchID ));
	}
}TReqFundCheckDataDownload,*PReqFundCheckDataDownload;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspFundCheckDataDownload] ����
// �ṹ����:���ն��˻�������������Ӧ������
typedef struct tagRspFundCheckDataDownload :public TRspMsg
{                              
	int     oper_flag;				//������־  
	int		num_forward_member_posi;//�ֻ����ڻ�Ա�ֲ�������
	struct tagForwardMemberPosi
	{
		char	exch_date[9];	//����
		char	member_id[7];	//��Ա����
		char	instID[9];		//��Լ���� 
		char	due_date[9];	//������
		int		net_amt;		//���ֲ���
		int		curr_long_amt;	//��ͷ�ֲ���
		int		curr_short_amt;	//��ͷ�ֲ���
		double	long_posi_bal;	//��ͷ�ֲֽ��
		double	short_posi_bal;	//��ͷ�ֲֽ��
		int		open_long_amt;	//���ն�ͷ����
		int		open_short_amt;	//���տ�ͷ����
		int		cov_long_amt;	//���ն�ͷƽ��
		int		cov_short_amt;	//���տ�ͷƽ��
		double	float_surplus;	//����ӯ��
		double	cov_surplus;	//ƽ��ӯ��
		double	fee;			//������
		double	margin;			//��֤��
		double	settle_price;	//�����
	}		* p_forward_member_posi;//�ֻ����ڻ�Ա�ֲ�
	int		num_defer_member_posi;	//���ڻ�Ա�ֲ�������
	struct tagDeferMemberPosi
	{
		char	exch_date[9];	//����
		char	member_id[7];	//��Ա����
		char	instID[9];		//��Լ���� 
		int		curr_long_amt;	//��ͷ�ֲ���
		int		curr_short_amt;	//��ͷ�ֲ���
		int		open_long_amt;	//���ն�ͷ����
		int		open_short_amt;	//���տ�ͷ����
		int		cov_long_amt;	//���ն�ͷƽ��
		int		cov_short_amt;	//���տ�ͷƽ��
		double	exch_surplus;	//����ӯ��
		double	fee;			//������
		double	margin;			//��֤��
		double	settle_price;	//�����
		double	defer_fee;		//���ӷ�
	}		* p_defer_member_posi;	//���ڻ�Ա�ֲ�
	int		num_member_capital;		//��Ա�ʽ�������
	struct tagMemberCapital
	{
		char	exch_date[9];	//����
		char	member_id[7];	//��Ա����
		char	acct_type;	//�˻�����
		double	curr_can_get;	//���ֿ����ʽ�  
		double	last_balance;	//���ս���׼������� 	
		double	last_b_margin;	//����ռ�ñ�֤��
		double	last_base_margin;	//���ջ�����֤��
		double	last_reserve;	//���ղ��𶳽���
		double	last_long_froz;	//�����ֹ������ʽ�
		double	last_forward_froz;	//����Զ��ӯ�������ʽ�
		double	last_deli_prepare;	//���հ��������
		double	last_deli_margin;	//���ս��֤��ռ��
		double	deli_prepare;	//���������
		double	deli_margin;	//���֤��ռ��
		double	balance;		//���ս���׼�������
		double	real_b_margin;	//����ռ�ñ�֤��
		double	base_margin;	//���ջ�����֤��
		double	real_reserve;	//���ղ��𶳽���
		double	day_long_froz;	//�����ֹ������ʽ�
		double	day_forward_froz;	//����Զ��ӯ�������ʽ�
		double	profit;			//����ӯ��
		double	today_inbal;	//�������
		double	today_outbal;	//���ճ���
		double	real_sell;		//�յ��Ļ���
		double	real_buy;		//֧���Ļ���
		double	misc_fee;		//����
		double	interest;		//��Ϣ
		double	bail;			//׷�ӱ�֤��
	}		* p_member_capital;	//��Ա�ʽ�
	int		num_fee_summary;	//��Ա������úϼ�������  
	struct tagFeeSummary
	{
		char	exch_date[9];	//����
		char	member_id[7];	//��Ա����
		double	fee;			//������
		double	delivery_fee;	//����������  
		double	storage_fee;	//�ִ��� 	
		double	trans_fee;		//�˱���
		double	overdue_fee;	//���ڷ�
		double	impawn_fee;		//��Ѻ�ǼǷ�
		double	loadreg_fee;	//���ǼǷ�
		double	breach_fee;		//ΥԼ��
		double	defer_fee;		//���ӷ�
		double	profit;			//ӯ��
		double	amount;			//���úϼ�=����������������+�����+�ִ���+�˱���+���ڲ�����+��Ѻ�ǼǷ�+���ǼǷ�+ΥԼ��+���ӷ�+ӯ��
	}		* p_fee_summary;	//��Ա������úϼ�
	int		num_settle_summary;	//��Ա����������úϼ������� 
	struct tagSettleSummary
	{
		char	exch_date[9];	//����
		char	member_id[7];	//��Ա����
		double	diff;			//�������
		double	vari_agio;		//Ʒ������ˮ  
		double	item_agio;		//��������ˮ 	
		double	sum_agio;		//����ˮ�ϼ�
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

//----------------------------------------------Req���Ľӿ� [ReqInterestDataDownload] ����
// �ṹ����:���ռ�Ϣ����������������
typedef struct tagReqInterestDataDownload  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1
	char      exch_date[9];		//��������	�ǿ�
	char      branchID[21];		//��֧����	�ǿ�
	tagReqInterestDataDownload()
	{
		oper_flag =	0;
		memset(exch_date,0x00,sizeof(exch_date));
		memset(branchID ,0x00,sizeof(branchID ));
	}
}TReqInterestDataDownload,*PReqInterestDataDownload;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspInterestDataDownload] ����
// �ṹ����:���ռ�Ϣ����������Ӧ������
typedef struct tagRspInterestDataDownload :public TRspMsg
{                              
	int       oper_flag;			//������־    
	int       num_pre_interest;		//Ԥ����Ϣ����������   
	struct tagPreInterest
	{
		char		seq_no[19];		//��ˮ�� 
		char		member_id[7];	//��Ա���
		char		acct_no[16];	//�ͻ���
		char		cust_id[16];	//�ͻ�����
		char		inte_type[3];	//��Ϣ����
		double		inte_integral;	//��Ϣ����
		double		inte_rate;		//��Ϣ����
		double		inte_tax_rate;	//��Ϣ˰����
		double		incr_inte;		//������Ϣ
		double		incr_inte_tax;	//������Ϣ˰
		char		currency_id;	//����
		char		o_term_type[3];	//������Դ
	}		* p_pre_interest;		//Ԥ����Ϣ����
	int		num_interest;			//��Ϣ����������  
	struct tagInterest
	{
		char		seq_no[19];		//��ˮ�� 
		char		member_id[7];	//��Ա���
		char		acct_no[16];	//�ͻ���
		char		cust_id[16];	//�ͻ�����
		double		incr_inte;		//������Ϣ
		double		incr_inte_tax;	//������Ϣ˰
		char		currency_id;	//����
		char		o_term_type[3];	//������Դ
	}		* p_interest;	//��Ϣ����
	tagRspInterestDataDownload()
	{
		oper_flag =	0;
		num_pre_interest =	0;
		p_pre_interest = NULL;
		num_interest =	0;
		p_interest = NULL;
	}
}TRspInterestDataDownload,*PRspInterestDataDownload;

//----------------------------------------------Req���Ľӿ� [ReqQuerySigexNotice] ����
// �ṹ����:�������Ĺ�����Ϣ��ѯ��������
typedef struct tagReqQuerySigexNotice  :public TReqMsg
{
	int       oper_flag;		//������־	�ǿ�	Ĭ���� 1    
	char      seq_no[11];		//�������    
	char      title[41];		//�������   ��ģ��ƥ��
	char      s_exch_date[9];	//��ʼ��������	�ǿ�
	char      e_exch_date[9];	//������������	�ǿ�
	tagReqQuerySigexNotice()
	{
		oper_flag =	0;
		memset(seq_no,0x00,sizeof(seq_no));
		memset(title ,0x00,sizeof(title ));
		memset(s_exch_date,0x00,sizeof(s_exch_date));
		memset(e_exch_date ,0x00,sizeof(e_exch_date ));
	}
}TReqQuerySigexNotice,*PReqQuerySigexNotice;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspQuerySigexNotice] ����
// �ṹ����:�������Ĺ�����Ϣ��ѯ��Ӧ������
typedef struct tagRspQuerySigexNotice :public TRspMsg
{                              
	int       oper_flag;	//������־
	int		  num_result;	//��ѯ���������
	struct tagResult
	{
		char      seq_no[11];	//�������    
		char      title[41];	//������� 
		char	  content[256];//����
		char	  announcer[16];//������
		char	  exch_date[9];	//��������
		char	  exch_time[9];	//����ʱ��
	}		  * p_result;	//��ѯ���
	tagRspQuerySigexNotice()
	{
		oper_flag =	0;
		num_result =	0;
		p_result = NULL;
	}
}TRspQuerySigexNotice,*PRspQuerySigexNotice;

//----------------------------------------------Req���Ľӿ� [ReqSigexBasicDataDownload] ����
// �ṹ����:�������Ļ�������������������
typedef struct tagReqSigexBasicDataDownload  :public TReqMsg
{
	int       oper_flag;                   //������־	�ǿ�	Ĭ���� 1                           
	char      city_info;                   //���д�����Ϣ��    
	char      spec_date;                   //�ڼ������ñ�      
	char      prod_code_def;               //��Լ�����        
	char      variety;                     //����Ʒ�ֱ�        
	char      variety_substitue;           //�������Ʒ�ֱ�    
	char      fare_model_def;              //��Ա����ģ����Ϣ  
	char      wh_fare_model;               //�ִ�����ģ����Ϣ  
	char      defer_over_fee;              //���ڷ��ʱ�        
	char      defer_fee;                   //���ڵ��Ӳ����ѱ�  
	char      rmb_day_interest_data;       //��������ʱ�      
	char      take_margin_para;            //�����֤�������  
	char      branch_fare_interval;        //��֧�������������
	char      stor_info;                   //�ֿ���Ϣ��               
	char      branchID[21];                //��֧����	�ǿ�   
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspSigexBasicDataDownload] ����
// �ṹ����:�������Ļ�������������Ӧ������
typedef struct tagRspSigexBasicDataDownload :public TRspMsg
{                              
	int       oper_flag;					//������־              
	//���д�����Ϣ��  
	int		  num_city_info;				//���д�����Ϣ����
	struct tagCityInfo
	{
		char		city_code[7];			//���д���
		char		city_name[51];			//��������
	}		  * p_city_info;			    //���д�����Ϣ 
	//�ڼ������ñ� 
	int			num_spec_date;				//�ڼ������ü�¼����
	struct		tagSpecDate 
	{
		char		spec_date[9];			//��������
		char		date_type[3];			//��������
	}		  * p_spec_date;				//�ڼ�������
	//��Լ����� 
	int			num_prod_code_def;			//��Լ�����¼����
	struct		tagProdCodeDef 
	{
		char		prod_code[11];			//��Լ����
		char		prod_name[32];			//��Լ����
		char		bourse_id[3];			//���������
		char		currency_id;			//���� 
		char		market_id[3];			//�����г����� 
		char		variety_type[3];		//Ʒ����� 
		char		variety_id[7];			//����Ʒ�ִ���	
		double		tick;             		//��С�䶯��λ 
		char		t0_sign[3];				//�Ƿ�T+0   
		char		bail_sign[3];			//�Ƿ�֤��ģʽ
		double		bail_rate;        		//��֤�����  
		char		limit_sign[3];			//�Ƿ��ǵ�ͣ���� 
		double		upper_limit_value;		//��ͣ����  
		double		lower_limit_value;		//��ͣ���� 
		char		active_flag;       		//��Ծ��־ 
		char		inst_stat[3];			//��Լ����״̬
		double		ref_price;        		//�ο��� 
		double		recv_rate;        		//�����տ���� 
		char		busi_mode[3];			//����ģʽ 
		int			max_hand;        		//����걨����
		int			min_hand;         		//��С�걨���� 
		char		exch_unit[3];			//���׵�λ
		double		measure_unit;     		//������λ 
		char		entr_way_str[11];		//ί�з�ʽ 
		char		fare_sign;         		//�Ƿ������� 
		double		fare_value;       		//������ֵ
		char		fare_model_id[7];		//����ģ��
		char		due_date[9];			//������ 
		int			deli_days;        		//����������   
	}			* p_prod_code_def;			//��Լ������Ϣ
	//����Ʒ�ֱ� 
	int		    num_variety;                //����Ʒ�ֱ� ��¼����
	struct	tagVariety
	{
		char		variety_ID[4];			//����Ʒ�ִ���  
		char		name[41];				//����Ʒ��ȫ�� 
		char		abbr[21];				//��� 
		char		variety_type[3];		//Ʒ�����  
		double		min_pickup;  			//��С������� 
		double		pickup_base; 			//������� 
		char		weight_unit[3];			//������λ 
		char		destroy_flag[3];		//ע����־ 
	}			* p_variety;			//����Ʒ����Ϣ   
	//�������Ʒ�ֱ� 
	int			num_variety_substitue;		//�������Ʒ�� ��Ϣ����
	struct	tagVarietySubstitue
	{
		char		prod_code[11];			//��Լ����
		int			seq_no;    				//����˳��
		char		variety_id[4];			//����Ʒ�ִ���
		double		diff_amt;  				//���  
	}			* p_variety_substitue;	//�������Ʒ����Ϣ 
	//��Ա����ģ����Ϣ 
	int			num_fare_model_def;			//��Ա����ģ����Ϣ ����
	struct		tagFareModelDef
	{
		char		fare_model_id[7];		//���׷���ģ��ID 
		char		fare_model_name[101];	//���׷���ģ������  
		char		fare_model_type[3];		//ģ������      
		char		contain_bourse[3];		//�Ƿ�������������� 
		char		branch_id[21];			//�����������  
		//char		o_term_type[3];			//������Դ    
		//char		o_teller_id[11];		//��������Ա�� 
		//char		o_date[9];				//��������  
		char		m_term_type[3];			//�޸���Դ  
		char		m_teller_id[11];		//�޸Ĳ���Ա��
		//char		m_date[9];				//�޸�����
	}			* p_fare_model_def;		//��Ա����ģ����Ϣ
	//�ִ�����ģ����Ϣ   
	int			num_wh_fare_model;		    //�ִ�����ģ����Ϣ ����
	struct	tagWhFareModel
	{
		char		fare_model_id[7];		//����ģ��ID 
		char		stor_id[5];				//�ִ����� 
		char		variety_id[7];			//����Ʒ��  
		char		fare_type_id[4];		//��������ID 
		char		fare_mode[3];			//�շ�ģʽ
		double		fare_value;   			//����ֵ
	}			* p_wh_fare_model;//�ִ�����ģ����Ϣ
	//���ڷ��ʱ� 
	int         num_defer_over_fee;          //���ڷ��ʱ�  ��¼����
	struct  tagDeferOverFee
	{
		char		prod_code[11];			//��Լ����  
		int 		seq_no;       			//���
		char 		start_day[9];    		//��ʼ������ 
		char 		end_day[9];      		//����������
		double		fee_rate;     			//���� 
	}			* p_defer_over_fee;		//���ڷ��ʱ� ��¼
	//���ڵ��Ӳ����ѱ�  
	int         num_defer_fee;          //���ڵ��Ӳ����ѱ�  ��¼����
	struct  tagDeferFee
	{
		char		exch_date[9];			//�������� 
		char		prod_code[11];			//��Լ����        
		char		pay_direction[3];		//֧������    
		double		fee_rate;         		//���� 
	}			* p_defer_fee;			//���ڵ��Ӳ����ѱ� ��¼
	//��������ʱ�      
	int         num_rmb_day_interest_rate;//��������ʱ�  ��¼����
	struct  tagRmbDayInterestRate
	{
		char		acct_type;			//�˻�����  
		int			seq_no;              	//�������
		char		s_valid_exch_date[9];	//��ʼ��Ч����   
		char		e_valid_exch_date[9];	//������Ч����
		double		inte_rate;        		//��Ϣ���� 
		double		inte_tax_rate;    		//��Ϣ˰���� 
		double		puni_rate;        		//��Ϣ����
	}			* p_rmb_day_interest_rate;//��������ʱ� ��¼
	//�����֤�������   
	int         num_take_margin_para;          //�����֤�������  ��¼����
	struct  tagTakeMarginPara
	{
		char		variety_ID[4];			// ����Ʒ�ִ���
		double		price_offset_rate;    	// �۸�Ԥ�� 
		double		unit_max_diff;          // ÿǧ�������������ˣ�   
	}			* p_take_margin_para;	//�����֤������� ��¼
	//��֧�������������    
	int         num_branch_interval;    //��֧�������������  ��¼����
	struct  tagBranchInterval
	{
		char		branch_id[21];			// ������� 
		char		prod_code[11];			// ��Լ����  
		char		fare_type_id[4];		// ��������ID  
		char		fare_mode[3];			// �շ�ģʽ 
		double		min_value;       		// ��С����ֵ
		double		max_value;             	// ������ֵ 
	}			* p_branch_interval;	//��֧������������� ��¼
	//�ֿ���Ϣ��      
	int         num_stor_info;          //�ֿ���Ϣ��  ��¼����
	struct  tagStorInfo
	{
		char		stor_id[5];				// �ֿ����
		char		stor_name[61];			// �ֿ�����
		char		addr[201];				// �ֿ��ַ
		char		tel[32];				// ��ϵ�绰
		char		fax[32];				// ��ϵ����
		char		link_man[32];			// ��ϵ�� 
		char		zip_code[11];			// �ʱ� 
		char		use_variety_type[201];	// ֧��ʹ�õĽ���Ʒ��
		char		is_take[3];				// �Ƿ�������� 
		char		stor_name_e[101];		// �ֿ�����
	}			* p_stor_info;			//�ֿ���Ϣ�� ��¼
	//�ֿ�����ж�Ӧ��Ϣ���
	int         num_stor_city_info;     //�ֿ�����ж�Ӧ��Ϣ���  ��¼����
	struct  tagStorCityInfo
	{
		char		stor_id[5];				// �ֿ���� 
		char		city_code[5];			// ���д���
		char		is_default_stor[3];		// �Ƿ�Ĭ������ֿ� 
	}			* p_stor_city_info;		//�ֿ�����ж�Ӧ��Ϣ��� ��¼
	//����ģ����ϸ��   
	int         num_fare_model_detail;  //����ģ����ϸ��  ��¼����
	struct  tagFareModelDetail
	{
		char		fare_model_id[7];		// ����ģ��ID
		char		prod_code[11];			// ��Լ���� 
		char		fare_type_id[4];		// ��������ID 
		char		fare_mode[3];			// �շ�ģʽ
		double		fare_value;       		// ����ֵ 
	}			* p_fare_model_detail;	//����ģ����ϸ�� ��¼
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

//----------------------------------------------Req���Ľӿ� [ReqSigexMemFareSyn] ����
// �ṹ����:���Ļ�Ա����ͬ��ά����������
typedef struct tagReqSigexMemFareSyn  :public TReqMsg
{
	int         oper_flag;               //������־		�ǿ�   1�����ӣ�2���޸ģ�3��ɾ��       
	char        fare_model_id[21];       //���׷���ģ��ID	�ǿ�    
	char        fare_model_name[101];    //���׷���ģ������	�ǿ�  
	char        fare_model_type[3];      //ģ������			�ǿ�          
	char        contain_bourse;          //�Ƿ��������������	�ǿ�	�̶��'0'
	char        gess_branch_id[21];      //������֧���� 	�ǿ�     
	//���׷�����ϸ�б�   
	int         num_fare_info_list;      //���׷�����ϸ�б�	�ǿ�  ��¼���� 
	struct  tagFareInfoList
	{   
		char			prod_code[11];		// ��Լ���� 
		char			fare_type_id[4];	// ��������ID 
		char			fare_mode[3];		// �շ�ģʽ
		double			fare_value;       	// ����ֵ
	}			* p_fare_info_list;		//���׷�����ϸ�б� ��¼
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

//----------------------------------------------Rsp���Ľӿ� [onRecvRspSigexMemFareSyn] ����
// �ṹ����:���Ļ�Ա����ͬ��ά����Ӧ������
typedef struct tagRspSigexMemFareSyn :public TRspMsg
{                              
	int             oper_flag;               //������־	1�����ӣ�2���޸ģ�3��ɾ��
	tagRspSigexMemFareSyn()
	{
		oper_flag =	0;
	}
}TRspSigexMemFareSyn,*PRspSigexMemFareSyn;

//----------------------------------------------Req���Ľӿ� [ReqSpecialAcctFareSyn] ����
// �ṹ����:�ͻ���������޸�ͬ��ά����������
typedef struct tagReqSpecialAcctFareSyn  :public TReqMsg
{
	int           oper_flag;               //������־	�ǿ�   Ĭ���� 1     
	char          cust_id[13];             //�ͻ����� 	�ǿ�       
	//���˷�����ϸ�б�
	int         num_acct_fare_info;        //���˷�����ϸ�б�	�ǿ�  ��¼����
	struct  tagAcctFareInfo
	{   
		char			prod_code[11];			// ��Լ����            
		char			fare_type_id[4];		// ��������ID           
		char			fare_mode[3];			// �շ�ģʽ                       
		double			fare_value;       		// ����ֵ   
	}			* p_acct_fare_info;			//���˷�����ϸ�б� ��¼
	tagReqSpecialAcctFareSyn()
	{
		oper_flag =	0;
		memset(cust_id,0x00,sizeof(cust_id));
		num_acct_fare_info = 0;
		p_acct_fare_info = NULL;
	}
}TReqSpecialAcctFareSyn,*PReqSpecialAcctFareSyn;

//----------------------------------------------Rsp���Ľӿ� [onRecvRspSpecialAcctFareSyn] ����
// �ṹ����:�ͻ���������޸�ͬ��ά����Ӧ������
typedef struct tagRspSpecialAcctFareSyn  :public TRspMsg
{                              
	int             oper_flag;               //������־  
	tagRspSpecialAcctFareSyn()
	{
		oper_flag =	0;
	}
}TRspSpecialAcctFareSyn,*PRspSpecialAcctFareSyn;











//----------------------------------------------------------------------�㲥����----------------------------------------------------------------------------------------

//������
//----------------------------------------------���Ľӿ� [onRecvSpotQuotation] ����
// �ṹ����:
typedef struct tagSpotQuotation
{
	char      instID[9];    //��Լ����      
	char      name [13];     //��Լ����        
	double    lastClose;     //������   
	double    open;          //���̼�          
	double    high;          //��߼�          
	double    low;           //��ͼ�          
	double    last;          //���¼�          
	double    close;         //���̼�          
	double    bid1;          //���1           
	int		  bidLot1;       //����1           
	double    bid2;          //���2           
	int		  bidLot2;       //����2           
	double    bid3;          //���3           
	int		  bidLot3;       //����3           
	double    bid4;          //���4           
	int       bidLot4;       //����4           
	double    bid5;          //���5           
	int       bidLot5;       //����5           
	double    ask1;          //����1           
	int		  askLot1;       //����1           
	double    ask2;          //����2           
	int		  askLot2;       //����2           
	double    ask3;          //����3           
	int		  askLot3;       //����3           
	double    ask4;          //����4           
	int		  askLot4;       //����4           
	double    ask5;          //����5           
	int		  askLot5;       //����5           
	int       volume;        //�ɽ�����˫�ߣ�  
	int		  weight;        //�ɽ���˫�ߣ�����
	double    highLimit;     //��ͣ��          
	double    lowLimit;      //��ͣ��          
	double    upDown;        //�ǵ�            
	double    upDownRate;    //�ǵ�����        
	double    turnOver;      //�ɽ���          
	double    average;       //����            
	char      quoteDate[9];     //��������        
	char      quoteTime[9];     //����ʱ��        
	int       sequenceNo;    //�������     
	char	  sequence_seriesno; //��Ϣ��������
	char	  sequence_no[11];	 //��Ϣ���	  
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

//----------------------------------------------���Ľӿ� [onRecvForwardQuotation] ����
// �ṹ����:
typedef struct tagForwardQuotation
{
	char        instID[9];          //��Լ����        
	char        name[13];            //��Լ����        
	double      lastSettle;          //�����          
	double      lastClose;           //������          
	double      open;                //���̼�          
	double      high;                //��߼�          
	double      low;                 //��ͼ�          
	double      last;                //���¼�          
	double      close;               //���̼�          
	double      settle;              //�����          
	double      bid1;                //���1           
	int         bidLot1;             //����1           
	double      bid2;                //���2           
	int         bidLot2;             //����2           
	double      bid3;                //���3           
	int         bidLot3;             //����3           
	double      bid4;                //���4           
	int         bidLot4;             //����4           
	double      bid5;                //���5           
	int         bidLot5;             //����5           
	double      ask1;                //����1           
	int         askLot1;             //����1           
	double      ask2;                //����2           
	int         askLot2;             //����2           
	double      ask3;                //����>3          
	int         askLot3;             //����3           
	double      ask4;                //����4           
	int         askLot4;             //����4           
	double      ask5;                //����5           
	int         askLot5;             //����5           
	int         volume;              //�ɽ���          
	int         weight;              //�ɽ���˫�ߣ�����
	double      highLimit;           //��ͣ��          
	double      lowLimit;            //��ͣ��          
	int         Posi;                //�ֲ���          
	double      upDown;              //�ǵ�            
	double      upDownRate;          //�ǵ�����        
	double      turnOver;            //�ɽ���          
	double      average;             //����            
	char        quoteDate[9];       //��������        
	char        quoteTime[9];       //����ʱ��        
	int         sequenceNo;          //�������        
	char		sequence_seriesno;	 //��Ϣ��������
	char		sequence_no[11];	 //��Ϣ���	 
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

//----------------------------------------------���Ľӿ� [onRecvDeferQuotation] ����
// �ṹ����:
typedef struct tagDeferQuotation
{
	char        instID[9];          //��Լ����        
	char        name[13];            //��Լ����        
	double      lastSettle;          //�����          
	double      lastClose;           //������          
	double      open;                //���̼�          
	double      high;                //��߼�          
	double      low;                 //��ͼ�          
	double      last;                //���¼�          
	double      close;               //���̼�          
	double      settle;              //�����          
	double      bid1;                //���1           
	int         bidLot1;             //����1           
	double      bid2;                //���2           
	int         bidLot2;             //����2           
	double      bid3;                //���3           
	int         bidLot3;             //����3           
	double      bid4;                //���4           
	int         bidLot4;             //����4           
	double      bid5;                //���5           
	int         bidLot5;             //����5           
	double      ask1;                //����1           
	int         askLot1;             //����1           
	double      ask2;                //����2           
	int         askLot2;             //����2           
	double      ask3;                //����3          
	int         askLot3;             //����3           
	double      ask4;                //����4           
	int         askLot4;             //����4           
	double      ask5;                //����5           
	int         askLot5;             //����5           
	int         volume;              //�ɽ���          
	int         weight;              //�ɽ���˫�ߣ�����
	double      highLimit;           //��ͣ��          
	double      lowLimit;            //��ͣ��          
	int         Posi;                //�ֲ���          
	double      upDown;              //�ǵ�            
	double      upDownRate;          //�ǵ�����        
	double      turnOver;            //�ɽ���          
	double      average;             //����            
	char        quoteDate[9];       //��������        
	char        quoteTime[9];       //����ʱ��        
	int         sequenceNo;          //�������        
	char		sequence_seriesno;   //��Ϣ��������
	char		sequence_no[11];	 //��Ϣ���	 
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

//----------------------------------------------���Ľӿ� [onRecvDeferDeliveryQuotation] ����
// �ṹ����:
typedef struct tagDeferDeliveryQuotation
{
	char        instID[9];          //��Լ����                              
	int         bidLot;             //����  
	int         askLot;             //���� 
	int         midBidLot;          //����������                           
	int         midAskLot;          //����������           
	char		sequence_seriesno;   //��Ϣ��������
	char		sequence_no[11];	 //��Ϣ���	 
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

//----------------------------------------------���Ľӿ� [onRecvRtnFpRoundQuotation] ����
// �ṹ����:
typedef struct tagFpRoundQuotation
{
	char        prodCode[9];            //��Լ����        
	char        prodName[13];           //��Լ����        
	char		exchDate[9];       		//��������
	char		gameID[11];         	//���α��
	int			roundID;        		//�ִα��
	double		price;          		//�۸�    	 
	double		adjust;         		//�䶯    	 
	int			bidLot;         		//����    	 
	int			askLot;         		//����    	 
	double		lastSettlePrice;		//������	 
	char		quoteTime[9];      		//����ʱ��
	char		sequenceNo[11];     	//�������
	char		sequence_seriesno;		//��Ϣ��������
	char		sequence_no[11];		//��Ϣ���	
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
 
//----------------------------------------------���Ľӿ� [onRecvRtnFpQuotation] ����
// �ṹ����:
typedef struct tagFpQuotation
{
	char        prodCode[9];            //��Լ����        
	char        prodName[13];           //��Լ����        
	char		exchDate[9];       		//��������
	char		gameID[11];         	//���α��
	double		price;          		//�۸� 
	char		isSettlePrice[3];		//�Ƿ��ǽ����
	int 		matchVolume;  			//�ɽ���
	double		initPrice;    			//��ʼ��
	int   		rounds;       			//����  
	char	    sequence_seriesno;		//��Ϣ��������
	char	    sequence_no[11];		//��Ϣ���	
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

//�г�״̬�ı���

//----------------------------------------------���Ľӿ� [onRecvRtnSpotMarketStateUpdate] ����
// �ṹ����:
typedef struct tagSpotMarketState
{
	char    marketID[3];           //�г�����    
	char    marketState;			//�г�״̬  
	char	sequence_seriesno;		//��Ϣ��������
	char	sequence_no[11];		//��Ϣ���	 
	tagSpotMarketState()
	{
		memset(marketID       ,0x00,sizeof(marketID       ));
		marketState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSpotMarketState,*PSpotMarketState;


//----------------------------------------------���Ľӿ� [onRecvRtnDeferMarketStateUpdate] ����
// �ṹ����:
typedef struct tagDeferMarketState
{
	char    marketID[3];           //�г�����    
	char    marketState;			//�г�״̬  
	char	sequence_seriesno;		//��Ϣ��������
	char	sequence_no[11];		//��Ϣ���	  
	tagDeferMarketState()
	{
		memset(marketID       ,0x00,sizeof(marketID       ));
		marketState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferMarketState,*PDeferMarketState;

//----------------------------------------------���Ľӿ� [onRecvRtnForwardMarketStateUpdate] ����
// �ṹ����:
typedef struct tagForwardMarketState
{
	char    marketID[3];           //�г�����    
	char    marketState;			//�г�״̬  
	char	sequence_seriesno;		//��Ϣ��������
	char	sequence_no[11];		//��Ϣ���	 
	tagForwardMarketState()
	{
		memset(marketID       ,0x00,sizeof(marketID       ));
		marketState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TForwardMarketState,*PForwardMarketState;
//��Լ״̬�ı���

//----------------------------------------------���Ľӿ� [onRecvRtnSpotInstStateUpdate] ����
// �ṹ����:
typedef struct tagSpotInstState
{
	char    instID[9];             //��Լ����    
	char    tradeState;				//��Լ����״̬  
	char	sequence_seriesno;		//��Ϣ��������
	char	sequence_no[11];		//��Ϣ���	  
	tagSpotInstState()
	{
		memset(instID        ,0x00,sizeof(instID        ));
		tradeState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSpotInstState,*PSpotInstState;

//----------------------------------------------���Ľӿ� [onRecvRtnForwardInstStateUpdate] ����
// �ṹ����:
typedef struct tagForwardInstState
{
	char    instID[9];            //��Լ����    
	char    tradeState;            //��Լ����״̬  
	char	sequence_seriesno;	   //��Ϣ��������
	char	sequence_no[11];	   //��Ϣ���	  
	tagForwardInstState()
	{
		memset(instID        ,0x00,sizeof(instID        ));
		tradeState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TForwardInstState,*PForwardInstState;

//----------------------------------------------���Ľӿ� [onRecvRtnDeferInstStateUpdate] ����
// �ṹ����:
typedef struct tagDeferInstState
{
	char       instID[9];            //��Լ����    
	char       tradeState;            //��Լ����״̬  
	char	   sequence_seriesno;	  //��Ϣ��������
	char	   sequence_no[11];		  //��Ϣ���	  
	tagDeferInstState()
	{
		memset(instID        ,0x00,sizeof(instID        ));
		tradeState = 0;
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TDeferInstState,*PDeferInstState;

//----------------------------------------------���Ľӿ� [onRecvRtnFpInstStatUpdate] ����
// �ṹ����:
typedef struct tagFpInstStat
{
	char    ProdCode[9];            //��Լ����    
	char	ExchDate[9];      		//��������      
	char	PreState;      			//ǰ��Լ����״̬
	char	NowState;      			//�ֺ�Լ����״̬
	char    GameID[11];             //���α��      
	int     RoundID;				//�ִα��      
	char    StartTime[9];			//��ʼʱ��      
	char    ContinueTime[9];		//����ʱ��   
	char	sequence_seriesno;		//��Ϣ��������
	char	sequence_no[11];		//��Ϣ���	
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

//������
//----------------------------------------------���Ľӿ� [onRecvRtnSpotOrder/onRecvRtnSpotOrderCancel] ����
// �ṹ����:
typedef struct tagSpotOrder
{
	char      orderNo[17];         //������      
	char      instID[9];          //��Լ����    
	char      clientID[13];        //�ͻ�����    
	char      memberID[7];         //��Ա����    
	char      buyOrSell;           //��������    
	char      applyDate[9];        //�걨����    
	char      applyTime[9];        //�걨ʱ��    
	char      traderID[11];        //����Ա����  
	double    price;               //�۸�        
	int       amount;              //����        
	int       remainAmount;        //ʣ������    
	char      cancelTime[9];       //����ʱ��    
	char      cancelID[11];         //����Ա����  
	char      status;              //״̬        
	char      matchType;           //����        
	char      endorseInstID[9];   //ת�ú�Լ����
	char      localOrderNo[15];    //���ر���    
	char	  sequence_seriesno;   //��Ϣ��������
	char	  sequence_no[11];	   //��Ϣ���	  
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

//----------------------------------------------���Ľӿ� [onRecvRtnForwardOrder/onRecvRtnForwardOrderCancel] ����
// �ṹ����:
typedef struct tagForwardOrder
{
	char      orderNo[17];         //������    
	char      instID[9];          //��Լ����  
	char      clientID[13];        //�ͻ�����  
	char      memberID[7];         //��Ա����  
	char      buyOrSell;           //��������  
	char      applyDate[9];        //�걨����  
	char      applyTime[9];        //�걨ʱ��  
	char      traderID[11];        //����Ա����
	double    price;			   //�۸�      
	int       amount;			   //����      
	int       remainAmount;		   //ʣ������  
	char      cancelTime[9];       //����ʱ��  
	char      cancelID[11];        //����Ա����
	char      status;              //״̬      
	char      localOrderNo[15];    //���ر�����
	char      matchType;           //����      
	char	  sequence_seriesno;   //��Ϣ��������
	char	  sequence_no[11];	   //��Ϣ���	  
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

//----------------------------------------------���Ľӿ� [onRecvRtnDeferOrder/onRecvRtnDeferOrderCancel] ����
// �ṹ����:
typedef struct tagDeferOrder
{
	char      orderNo[17];          //������    
	char      clientID[13];         //�ͻ�����  
	char      instID[9];           //��Լ����  
	char      memberID[7];          //��Ա����  
	char      buyOrSell;			//��������  
	char      applyDate[9];         //�걨����  
	char      applyTime[9];         //�걨ʱ��  
	char      offSetFlag;			//��ƽ�ֱ�־
	double    price;				//�۸�      
	int       amount;				//����      
	int       remainAmount;			//ʣ������  
	char      cancelTime[9];        //����ʱ��  
	char      status;				//״̬      
	char      localOrderNo[15];     //���ر�����
	double    margin;				//��֤����  
	char      marginType;			//��֤������
	char      traderID[11];         //����Ա����
	char      cancelID[11];         //����Ա����
	char      matchType;			//����      
	char	  sequence_seriesno;	//��Ϣ��������
	char	  sequence_no[11];		//��Ϣ���	  
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

//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppOrder/onRecvRtnDeferDeliveryAppOrderCancel] ����
// �ṹ����:
typedef struct tagDeferDeliveryAppOrder
{
	char      orderNo[17];          //�������    
	char      clientID[13];         //�ͻ�����    
	char      instID[9];           //��Լ����    
	char      buyOrSell;            //��������    
	char      applyDate[9];         //��������    
	char      applyTime[9];         //����ʱ��    
	int       amount;               //����        
	char      cancelTime[9];        //����ʱ��    
	char      status;               //����״̬    
	char      localOrderID[15];     //���ر������
	char      memberID[7];          //��Ա����    
	char      traderID[11];         //����Ա����  
	char      cancelID[11];         //����Ա����  
	int       remainAmount;         //ʣ������    
	char	  sequence_seriesno;	//��Ϣ��������
	char	  sequence_no[11];		//��Ϣ���	  
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



//----------------------------------------------���Ľӿ� [onRecvRtnSpotMatch] ����
// �ṹ����:
typedef struct tagSpotMatch
{
	char      matchNo[17];         //�ɽ����    
	char      buyOrSell;           //��������    
	char      clientID[13];        //�ͻ�����  
	char	  clientType;		   //�ͻ�����
	char      memberID[7];         //��Ա����    
	char      instID[9];           //��Լ����    
	char      matchDate[9];        //�ɽ�����    
	char      matchTime[9];        //�ɽ�ʱ��    
	double    price;               //�۸�        
	int       volume;              //����        
	char      orderNo[17];         //ϵͳ������  
	char      localOrderNo[15];    //�������ر��
	char      matchType;           //����        
	char	  sequence_seriesno;   //��Ϣ��������
	char	  sequence_no[11];	   //��Ϣ���	 
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

//----------------------------------------------���Ľӿ� [onRecvRtnForwardMatch] ����
// �ṹ����:
typedef struct tagForwardMatch
{
	char      matchNo[17];         //�ɽ����       
	char      buyOrSell;           //��������       
	char      clientID[13];        //�ͻ�����
	char	  clientType;		   //�ͻ�����
	char      instID[9];          //��Լ����       
	char      memberID[7];         //��Ա����       
	char      matchDate[9];        //�ɽ�����       
	char      matchTime[9];        //�ɽ�ʱ��       
	double    price;               //�۸�           
	int       volume;              //����           
	double    marginRate;          //��֤����       
	char      rateType;            //��֤������     
	char      orderNo[17];         //ϵͳ������     
	char      localOrderNo[15];    //�������ر��   
	char	sequence_seriesno;	   //��Ϣ��������
	char	sequence_no[11];	   //��Ϣ���	  
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

//----------------------------------------------���Ľӿ� [onRecvRtnDeferMatch] ����
// �ṹ����:
typedef struct tagDeferMatch
{
	char      matchNo[17];         //�ɽ����    
	char      buyOrSell;           //��������    
	char      clientID[13];        //�ͻ�����
	char	  clientType;		   //�ͻ�����
	char      instID[9];          //��Լ����    
	char      memberID[7];         //��Ա����    
	char      matchDate[9];        //�ɽ�����    
	char      matchTime[9];        //�ɽ�ʱ��    
	double    price;               //�۸�        
	int       volume;              //����        
	char      offsetFlag;          //��ƽ��־    
	char      orderNo[17];         //ϵͳ������  
	char      localOrderNo[15];    //�������ر��
	char	  sequence_seriesno;   //��Ϣ��������
	char	  sequence_no[11];	   //��Ϣ���	  
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

//----------------------------------------------���Ľӿ� [onRecvRtnDeferDeliveryAppMatch] ����
// �ṹ����:
typedef struct tagDeferDeliveryAppMatch
{
	char      matchNo[17];	       //�ɽ����    
	char      clientID[13];        //�ͻ�����    
	char      instID[9];          //��Լ����    
	char      memberID[7];         //��Ա����    
	char      buyOrSell;           //��������    
	int       volume;              //����        
	char      matchDate[9];        //�ɽ�����    
	char      matchTime[9];        //�ɽ�ʱ��    
	char      orderNo[17];         //������      
	char      localOrderNo[15];    //�������ر��
	char      middleFlag;          //�Ƿ�Ϊ������
	char	  sequence_seriesno;	   //��Ϣ��������
	char	  sequence_no[11];	   //��Ϣ���	  
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
//----------------------------------------------���Ľӿ� [onRecvRspFpOrder] ����
// �ṹ����:
typedef struct tagFpOrder
{
	char		OrderNo[17];		 //������    		
	char      	LocalOrderNo[15];    //���ر�����   
	char      	MemberID[7];         //��Ա���      
	char      	AcctNo[13];          //�ͻ���       
	char      	ProdCode[9];         //��Լ         
	char      	Bs;					 //��������    'b'-��  's'-��
	char      	OrderType;			 //��������      
	int         Amount;              //ί������    
	char      	ApplyDate[9];        //ί������     
	char      	ApplyTime[9];        //ί��ʱ��     
	char      	EntrPhase;			 //�걨�׶�     
	char      	GameID[11];          //���α���     
	int         RoundID;             //�ִα��    
	double      EntrPrice;           //ί�м۸�    
	char      	Status;				 //״̬          	
	char		sequence_seriesno;	 //��Ϣ��������
	char	    sequence_no[11];	 //��Ϣ���	
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

//----------------------------------------------���Ľӿ� [onRecvRtnFpEntrStatistics] ����
// �ṹ����:
typedef struct tagFpEntrStatistics
{
	char		ExchDate[9];      	 //��������             
	char   		MemberID[7];         //��Ա��               
	char   		AcctNo[13];          //�ͻ���              
	char   		ProdCode[9];        //��Լ����            
	char   		GameID[11];			 //���α��             
	double   	Price;			     //���ּ۸�            
	int   		MrBuyAmount;         //�����г��걨����    
	int			MrSellAmount;        //�����г��걨����    
	int   		FrBuyAmount;         //���ֲ����걨����    
	int   		FrSellAmount;        //���ֲ����걨����    
	int   		LrMrBuyAmount;       //��һ���г��걨����  
	int   		LrMrSellAmount;      //��һ���г��걨����  
	int			LrFrBuyAmount;       //��һ�ֲ����걨����  
	int			LrFrSellAmount;     //��һ�ֲ����걨����  
	double   	LrPrice;             //��һ�ֵļ۸�        
	double		FrozBuyMargin;       //Ŀǰ�Ѷ������뱣֤��
	double		FrozSellMargin;      //Ŀǰ�Ѷ���������֤��
	double		FrozBuyExchFare;     //Ŀǰ�Ѷ�������������
	double		FrozSellExchFare;    //Ŀǰ�Ѷ�������������
	char		sequence_seriesno;	 //��Ϣ��������
	char		sequence_no[11];	 //��Ϣ���	
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
//----------------------------------------------���Ľӿ� [onRecvRtnFpMatch] ����
// �ṹ����:
typedef struct tagFpMatch
{
	char		MatchNo[17];		//�ɽ�����  	
	char		MatchDate[9];		//�ɽ�����  	 	
	char		DeliDate[9];		//��������  	 
	char		MatchGame[11];		//�ɽ�����  	 	
	int 		MatchRound;			//�ɽ��ִ�  	 	
	char		MemberID[7];		//��Ա���  	 
	char		AcctNo[13];			//�ͻ���    	
	char		ProdCode[9];		//��Լ      		
	char		Bs;					//��������  	 
	double  	MatchPrice;			//�ɽ��۸�  	  
	int     	MatchAmount;		//�ɽ�����  	  
	char    	EntrPhase;			//�걨�׶�  	 
	char    	IsAllocate;			//�Ƿ�Ϊ��̯	
	char		sequence_seriesno;	//��Ϣ��������
	char		sequence_no[11];	//��Ϣ���	
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

//----------------------------------------------���Ľӿ� [onRecvRspFpOrderCancel] ����
// �ṹ����:
typedef struct tagFpOrderCancel
{
	char		MemberID[7];	//��Ա���   
	char		AcctNo[13];		//�ͻ���     
	char		ProdCode[9];	//��Լ       
	char		EntrPhase;		//�걨�׶�   
	char		Bs;				//��������    
	int 		CancelAmount;	//��������  
	char		GameID[11];     //���α��   
	int 		RoundID;        //�ִα��  
	char		Status;			//״̬       
	char		sequence_seriesno;	 //��Ϣ��������
	char		sequence_no[11];	 //��Ϣ���	
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


//----------------------------------------------���Ľӿ� [onRecvRspFpOrderFullCancel] ����
// �ṹ����:
typedef struct tagFpOrderFullCancel
{
	char		GameID[11];    //���α��    
	int			RoundID;	   //�ִα��    
	char		ProdCode[9];  //��Լ          
	char		Bs;			   //��������    
	char		NeedCancel;	   //�Ƿ���Ҫȫ��    
	double		NewRoundPrice; //��һ�ּ۸� 
	char		sequence_seriesno;		//��Ϣ��������
	char		sequence_no[11];		//��Ϣ���	
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




//ϵͳ��
//----------------------------------------------���Ľӿ� [onSysInit] ����
// �ṹ����:
typedef struct tagSysInit
{
	char      old_exch_date[9];       //ԭ��������
	char      new_exch_date[9];       //�½�������
	char	  sequence_seriesno;	  //��Ϣ��������
	char	  sequence_no[11];		  //��Ϣ���
	tagSysInit()
	{
		memset(old_exch_date,0x00,sizeof(old_exch_date));
		memset(new_exch_date,0x00,sizeof(new_exch_date));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TSysInit,*PSysInit;

//----------------------------------------------���Ľӿ� [onSysStatChange] ����
// �ṹ����:
typedef struct tagSysStat
{
	char      sys_date[9];         //ϵͳ����          
	char      exch_date[9];        //��������          
	char      m_sys_stat;          //��������ϵͳ״̬  
	char      b_sys_stat;          //���彻����ϵͳ״̬
	char	  sequence_seriesno;   //��Ϣ��������
	char	  sequence_no[11];	   //��Ϣ���	 
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

//----------------------------------------------���Ľӿ� [onNewMemberBulletin] ����
// �ṹ����:
typedef struct tagNewMemberBulletin
{
	char      bulletin_id[11];      //�������
	char      title[41];           //�������
	char	  sequence_seriesno;	//��Ϣ��������
	char	  sequence_no[11];		//��Ϣ���	  
	tagNewMemberBulletin()
	{
		memset(bulletin_id,0x00,sizeof(bulletin_id));
		memset(title	  ,0x00,sizeof(title	  ));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}TNewMemberBulletin,*PNewMemberBulletin;


//�ͻ���
//----------------------------------------------���Ľӿ� [onCustOpenCheck] ����
// �ṹ����:
typedef struct tagCustOpenCheck
{
	char      member_id[7];            //��Ա����    
	char      cert_type_id;				//֤������    
	char      cert_num[41];            //֤������    
	char      cust_id[13];             //�ƽ��ױ���
	char	  sequence_seriesno;	   //��Ϣ��������
	char	  sequence_no[11];		   //��Ϣ���	
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

//�����
//----------------------------------------------���Ľӿ� [on0x00A00123] ����
// �ṹ����:
typedef struct tag0x00A00123
{
	char      memberID[7];     //��Ա����     
	char      effectDate[9];   //��������     
	char      seqNo[32];       //��ˮ���     
	char      sheetNo[11];     //���ݱ��     
	char      clientID[13];    //�ͻ�����     
	char      accountType;	   //�˻�����     
	char      transType[3];    //���仯���� 
	char      varietyID[5];    //����Ʒ�ִ��� 
	char      warehouseID[5];  //�ֿ����     
	double    stdStorage;	   //������׼���� 
	double    totalStore;      //����ʵ������ 
	double    sumStore;        //�������     
	char      transDate[9];    //ʵ�ʷ������� 
	char      transTime[9];    //ʵ�ʷ���ʱ�� 
	char	  sequence_seriesno;	   //��Ϣ��������
	char	  sequence_no[11];		   //��Ϣ���	
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

//----------------------------------------------���Ľӿ� [on0x00A00202] ����
// �ṹ����:
typedef struct tag0x00A00202
{
	char      pickupSheetNo[15];    //�������     
	char      applyDate[9];			//��������     
	char      applyTransDate[9];    //�������ʱ��������     
	char      memberID[7];			//��Ա����     
	char      localNo[17];			//�����������     
	char	  sequence_seriesno;	//��Ϣ��������
	char	  sequence_no[11];		//��Ϣ���	
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

//----------------------------------------------���Ľӿ� [on0x00A00212] ����
// �ṹ����:
typedef struct tag0x00A00212
{
	char      pickupSheetNo[15];    //�������        
	char      memberID[7];			//��Ա����         
	char	  sequence_seriesno;	//��Ϣ��������
	char	  sequence_no[11];		//��Ϣ���	
	tag0x00A00212()
	{
		memset(pickupSheetNo   ,0x00,sizeof(pickupSheetNo));
		memset(memberID    ,0x00,sizeof(memberID));
		sequence_seriesno = 0;		
		memset(sequence_no,0x00,sizeof(sequence_no));
	}
}T0x00A00212,*P0x00A00212;

//----------------------------------------------���Ľӿ� [on0x00A00222] ����
// �ṹ����:
typedef struct tag0x00A00222
{
	char      SheetNo[15];        //�������          
	char      localNo[17];        //�����������      
	char      memberID[7];        //��Ա����          
	char      clientID[13];       //�ͻ���            
	char      warehouseID[5];     //�ֿ����          
	char      pickupPerson[21];   //�����            
	char      cipher[255];        //�������          
	char      certificateType;    //֤������          
	char      certificateNo[21];  //֤������          
	char      applyDate[9];       //��������          
	char      beginDate[9];       //�����ʼ����      
	char      endDate[9];         //�����������      
	char      applyTransDate[9];  //�������ʱ��������
	char      traderID[11];       //����Ա����        
	double    stdDrawWeight;      //��׼�������      
	char      varietyID[4];       //�������          
	double    selfDrawWeight;     //��������          
	double    tradeDrawWeight;    //��������          
	char      drawType;			  //�������          
	char      leaseRegNo[9];      //���Ǽǵ����           
	char	  sequence_seriesno;	//��Ϣ��������
	char	  sequence_no[11];		//��Ϣ���	
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

//----------------------------------------------���Ľӿ� [on0x00A00223] ����
// �ṹ����:
typedef struct tag0x00A00223
{
	char      memberID[7];			//��Ա����      
	char      effectDate[9];		//��������      
	char      seqNo[11];			//��ˮ��        
	char      clientID[13];			//�ͻ���        
	char      SheetNo[15];			//�������      
	char      appSheetNo[17];		//���뵥�ݱ��  
	char      localNo[17];			//�����������  
	char      stgOptType[5];		//����          
	char      appState;				//�걨״̬        
	char	  sequence_seriesno;	//��Ϣ��������
	char	  sequence_no[11];		//��Ϣ���	
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
