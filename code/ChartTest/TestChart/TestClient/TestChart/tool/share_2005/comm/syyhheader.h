
#if !defined(_syyhheader_h_)
#define _syyhheader_h_

// ��ҵ���нӿ�
struct SYYHWhUDPData
{
	int   m_nSize;
	char  m_szFlag[4];

	//
	int  total_count;		//��¼����	
	char Market_no;			//�����г�	
	char Market_name[10];	//�г�����	
	char money_name1[3];	//��Ʒ����	
	char money_name2[3];	//���ۻ���	
	char buy_rate[9];		//�������	
	char sale_rate[9];		//��������	
	char rate_date[10];		//��������	
	char rate_time[8];		//����ʱ��	
	char rate_status;		//����״̬	
	char show_order[5];		//�������	

	SYYHWhUDPData()
	{
		memset(this,0,sizeof(SYYHWhUDPData));
	}
};

#define SYYHReqestFirstData_Section				"��ҵ������������ӿ�"
#define SYYHReqestFirstData_trans_code 			"������"
#define SYYHReqestFirstData_req_serial 			"������ˮ��"
#define SYYHReqestFirstData_trans_branch 		"�������"
#define SYYHReqestFirstData_trans_terminal 		"�ն˱��"
#define SYYHReqestFirstData_trans_user 			"���׹�Ա"
#define SYYHReqestFirstData_grant_user 			"��Ȩ��Ա"
#define SYYHReqestFirstData_entrust_way 		"��������"

#define SYYHReqestFirstData_market_no			"�����г�"
#define SYYHReqestFirstData_money_name1			"��Ʒ����"
#define SYYHReqestFirstData_money_name2			"���ۻ���"

// ��ҵ���нӿ�
struct SYYHReqestFirstData
{
	char trans_code[6];					//1	������		
	char req_serial[12];				//2	������ˮ��	
	char trans_branch[10];				//3	�������	
	char trans_terminal[10];			//4	�ն˱��	
	char trans_user[10];				//5	���׹�Ա	
	char grant_user[10];				//6	��Ȩ��Ա	
	char entrust_way;					//7	��������	

	char market_no;						//8 �����г�
	char money_name1[3];				//9 ��Ʒ����
	char money_name2[3];				//10 ���ۻ���

	SYYHReqestFirstData()
	{
		Empty();
	}

	void Empty()
	{
		memset(this,' ',sizeof(SYYHReqestFirstData));
	}

	void FormatSpace()
	{
		char* pData = (char*)this;
		for( int i = 0; i < sizeof(SYYHReqestFirstData); i++,pData++)
		{
			if( *pData == '\0' )
				*pData = ' ';
		}
	}
};

struct SyyhItemData
{
	char Market_no;		//		�����г�	Market_no	Y	              C1
	char Market_name[10];//		�г�����	Market_name	Y	CHAR(10)
	char money_name1[3];//		��Ʒ����	money_name1	Y	C3
	char money_name2[3];//		���ۻ���	money_name2	Y	C3
	char buy_rate[9];	//		�������	buy_rate	Y	N9.4
	char sale_rate[9];//		��������	sale_rate	Y	N9.4
	char rate_date[10];//		��������	rate_date	Y	ˢ������C10
	char rate_time[8];//		����ʱ��	rate_time	Y	ˢ��ʱ��C8
	char rate_status;	//		����״̬	rate_status	Y	C1
	char show_order[5];//		�������	show_order	Y	C5

	SyyhItemData()
	{
		memset(this,0,sizeof(SyyhItemData));
	}

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	CString GetCode()
	{
		/*if( szRet == NULL )
		return "";

		strncpy(szRet,money_name1,sizeof(money_name1));
		YlsAllTrim(szRet);

		int nLen = strlen(szRet);
		strncpy(&szRet[nLen],money_name2,sizeof(money_name2)));
		YlsAllTrim(szRet);

		YlsMakeUpper(szRet);

		return szRet;*/

		CString str = CString(money_name1,sizeof(money_name1));
		str.Trim();
		str += CString(money_name2,sizeof(money_name2));
		str.Trim();
		str.MakeUpper();
		return str;
	}

	CString GetName()
	{
		//if( szRet == NULL )
		//	return "";

		//strncpy(szRet,Market_name,sizeof(Market_name));
		//YlsAllTrim(szRet);

		CString str = CString(Market_name,sizeof(Market_name));
		str.Trim();
		return str;
		//return szRet;
	}

	float Get_buy_rate()		
	{ 
		return atof(CString(buy_rate		,sizeof(buy_rate			)));
	}

	float Get_sale_rate()		
	{ 
		return atof(CString(sale_rate		,sizeof(sale_rate			))); 
	}	
#endif
};

struct SyyhDataHeader
{
	char head;				// ��־'\x0'
	char total_Length[5];  // ���ݳ���
	char total_count[8];	//��¼����	total_count	Y	���濪ʼѭ��  n8

	SyyhItemData m_item[1];

	SyyhDataHeader()
	{
		memset(this,0,sizeof(SyyhDataHeader));
	}

#if defined(HS_SUPPORT_UNIX) || defined(_WIN32_WCE)
#else
//#ifndef HS_SUPPORT_UNIX
	int GetLength()
	{
		return atol(CString(total_Length,sizeof(total_Length)));
	}

	int GetCount()
	{
		return atol(CString(total_count,sizeof(total_count)));
	}

	BOOL IsValid()
	{
		return ((GetCount()*sizeof(SyyhItemData) + sizeof(total_count)) == GetLength());
	}
#endif

};

struct SendUDPDataItem
{
	char				 m_szFlag[4];					// ��־
	CodeInfo			 m_ciStockCode;					// ����
	char				 m_cStockName[STOCK_NAME_SIZE]; // ����

	int					 m_lDataLen;

	long				 m_lPreClose; // ������
	long                 m_lTime;     // ����ʱ��

	union
	{
		struct
		{
			ShareRealTimeData	 m_sData;						// ָ�� ShareRealTimeData ������һ��
			ETFStockNowData      m_sETF;
		};

		char				 m_cData[1];
	};

	SendUDPDataItem(int lDataLen = 0)
	{
		memset(this,0,sizeof(SendUDPDataItem));
		m_lDataLen = lDataLen;
		SetFlag();
	}

	void Empty()
	{
		m_lPreClose = 0;

#ifndef HS_SUPPORT_UNIX
		memset(&m_sData,0,sizeof(m_sData));
#endif
	}

	void SetFlag(const char* strFlag = "HSHS")
	{
		strncpy(m_szFlag,strFlag,sizeof(m_szFlag));
	}

	BOOL IsValid(int nLen)
	{
		if( nLen < 32 )
			return 0;

		return ( m_szFlag[0] == 'H' &&
			m_szFlag[1] == 'S' &&
			m_szFlag[2] == 'H' &&
			m_szFlag[3] == 'S' );
	}

	char* GetName(char* szRet)
	{
		strncpy(szRet,m_cStockName,sizeof(m_cStockName));
		//YlsAllTrim(szRet);
		return szRet;
	}
};

// ��ͨ���нӿ�

#define PLACEHOLDER  ' '
#define PLACEHOLDER2 '0'
#define XLI_SYSPARAMREQUEST "417419"

template <class T, int L>
class YlsChar
{
public:
	YlsChar () { memset (this, PLACEHOLDER, sizeof(v)); }

	void set(const char* szValue)
	{
		if( szValue == NULL )
			return;

		strncpy(v,szValue,sizeof(v));
	}

public:
	T v[L];
};

template <class T, int L>
class YlsNumber
{
public:
	YlsNumber () { memset (this, PLACEHOLDER2, sizeof(v)); }

	void set(const char* szValue)
	{
		if( szValue == NULL )
			return;

		int nLen = strlen(szValue);
		int nCurLen = sizeof(v);
		int nPos = nCurLen - nLen;
		if( nPos < 0 )
			nPos = 0;
		if( nLen > nCurLen)
			nLen = nCurLen;
		strncpy(&v[nPos],szValue,nLen);
	}

public:
	T v[L];
};

#define CHART(EXP)	 YlsChar<char, EXP>
#define NUMBERT(EXP) YlsNumber<char, EXP>

//��㱣֤��->�����ն�
struct XLI_OBlockHead
{
	CHART(3)	toa_filler;				//������
	CHART(1)	toa_msg_type;			// N-���� A-Ҫ����Ȩ E-����
	CHART(2)	toa_msg_ap_mmo;			// Ӧ�ô��룬Ϊ�ַ��ͣ��ɹ�SC ����PX
	NUMBERT(4)	toa_msg_code;		//�ɹ�-000 ʧ��-������
	NUMBERT(4)	toa_curs_pos;		//���������У������ֶ�
	//��ÿ�����������ֶ��У���һ���ֶ�Ϊ1��
	CHART(7)	toa_tm_no;
	NUMBERT(6)	toa_tm_seq_no;
	NUMBERT(4)	toa_subs_tr_code;	//��ǰ���ṩ�����룬��㱣֤����д
	NUMBERT(2)	toa_subs_ap_code;	//��ǰ���ṩ�����룬��㱣֤����д

	CHART(3)	toa_tr_mmo;	 //������
	NUMBERT(8)	toa_tr_date;		 //������ǰϵͳ����
	NUMBERT(6) 	toa_tr_time;		//������ǰϵͳʱ��
	NUMBERT(8)	toa_ac_date;		//������ǰ�������
	NUMBERT(9)    toa_jrn_no;			//����������ˮ��
	NUMBERT(11)	toa_vch_no;			//�����ˮ��

	NUMBERT(1)	toa_page_no;
	NUMBERT(1)	toa_comp_ind;
	NUMBERT(1)	toa_encr_ind;

	NUMBERT(6)	toa_tr_br;	 //����ȷ���Ľ��׻�����
	CHART(1)	toa_auth_log;
	CHART(1)	toa_fin_flag;	 //F-���ڽ��� N-�ǽ��ڽ�Ӵ

	NUMBERT(2)	toa_auth;  
	CHART(7)	toa_sup1_id;
	CHART(7) 	toa_sup2_id;
	CHART(5)	toa_filler2;

	NUMBERT(4)	toa_meg_len;	//�����ʵ�����ݳ���
	XLI_OBlockHead()
	{
	}
};

// ��ͷ �����ն�->��㱣֤��
struct XLI_IBlockHead
{
	CHART(4)		tia_filler;			// CICS ������				
	NUMBERT(2)	tia_ap_code;	//�ַ��ͣ������ֶ������λ�Ľ����룬��41

	NUMBERT(4)	tia_tr_code;	//����������
	NUMBERT(6)	tia_fe_code;    //ǰ�ý����룬����˫�����룬����㱣֤������
	CHART(7)		tia_tm_seq_no;	    //�ն˺�			

	CHART(5)		tia_tx_type;		
	//0������ҵ��
	//1���绰����
	//2������
	//3��ATM/CDM/CRS
	//4��POS
	//5-��ý�� 
	//6���ֻ�����
	NUMBERT(15)	tia_tx_seq;		//������ˮ��:			
	CHART(7)		tia_tl_id;
	CHART(1)		tia_req_type;		//��T/A/P/B/C��

	NUMBERT(2) 	tia_auth;
	CHART(7)		tia_sup1_id;
	CHART(7)		tia_sup2_id;
	CHART(6)		tia_sup1_psw;
	CHART(6)		tia_sup2_psw;
	CHART(1)		tia_sup1_dev;
	CHART(1)		tia_sup2_dev;
	NUMBERT(1)	tia_auth_resn_tbl;	//��һ�ֶ�Ϊ����Ԫ�أ����10����Ȩԭ��
	CHART(6)		tia_auth_resn[10];
	NUMBERT(9)	tia_jrn_no;
	NUMBERT(1)	tia_comp_ind;	    //��0/1��
	NUMBERT(1)	tia_encr_ind;		//��0/1��	
	NUMBERT(6)	tia_tr_br;
	NUMBERT(1)	tia_tl_lvl;
	NUMBERT(8)	tia_ver_no;
	CHART(1)		tia_outer_tlp;
	CHART(2)		tia_filler2;

	XLI_IBlockHead()
	{
	}
};

//��㱣֤�𹫹��ӿ� ������:�����ն�->����ƽ̨
struct XLI_CommonRequest
{
	CHART(5)	business_type;	//ҵ������
	CHART(1)	tx_type;		//���� 
	// 0 - ����
	// 1 - �绰����
	// 2 - ����
	// 3 - ATM/CDM/CRS
	// 4 - POS
	// 5 - ��ý��
	// 6 - �ֻ�
	CHART(1)	pwd_mark;		// 0 - ��У��
	// 1 - ���齻������
	// 2 - �����ѯ����

	NUMBERT(20)	password;  	//��������

	XLI_CommonRequest()
	{
	}

};

//3. ���ܺ� 0x1212 ϵͳ������ѯ
struct XLI_SysParamRequest
{
	NUMBERT(8)   m_cLength;

	struct XLI_IBlockHead 		  head;
	struct XLI_CommonRequest      comreq;

	XLI_SysParamRequest()
	{
		head.tia_fe_code.set( XLI_SYSPARAMREQUEST );
		head.tia_tr_br.set("cccccc");
		comreq.pwd_mark.set("0");
		comreq.tx_type.set("0");
	}
};

#define XLI_HQREQUEST "7419"
struct XLI_HqRequest
{
	NUMBERT(8)   m_cLength;

	struct XLI_IBlockHead head;
	struct XLI_CommonRequest comreq;

	XLI_HqRequest()
	{
		memset (this, PLACEHOLDER, sizeof(XLI_HqRequest));
	}	
};

// ���������¼
struct hq_record
{
	CHART(6)		product_name;	//USDJPY, EURUSD

	NUMBERT(13)	buy_price;		//�����
	NUMBERT(13)   sell_price;		//������

	CHART(1)	mark;				//��Ч��� 0 - ��Ч 1-��Ч
	//���Ƽ۵���Ч��־(status)Ϊ��Ч"0"��
	//��ʾ���Ƽ۲����� ,�������Ƽۿͻ�����ʾ
	//(��"--"������ǲ�����)

	NUMBERT(14)	time;			//����Դʱ�� yyyymmddhhmmss

};

struct XLI_HqReturn
{
	struct XLI_OBlockHead head;

	CHART(3)	query_type;	//QUO - ����
	//SYS - ϵͳ����

	NUMBERT(2)	rd_num;	//��¼����

	//char 		data[4096 - 5];	//�������ݼ���"#"�ָ���������ڸ�Ԫ�ؼ���"|"�ָ������Ϊ"@@@@" 2#USDJPY|102.7600|102.9600|1|200501080245200#USDCAD|
	//1.2306|1.2336|1|20050108 0245200#@@@@ 

};

struct XLI_SysParamReturn
{
	struct XLI_OBlockHead head;
	//CHART(3)	        query_type;
	CHART(9)		slot;
	CHART(30)		available_power;		// ���ñ��� 1,2,5,8,10
	NUMBERT(2)		max_online_days;		// ����������������
	CHART(200)		available_product;		//���ò�Ʒ
	NUMBERT(2)		max_position_distance;	        //�ͻ�����ĵ�ֵ�����ֵ
	NUMBERT(3)		positon_down_stop;		//���̼۸�͵�ǰ���ʵ�ƫ������
	NUMBERT(3)		postion_up_stop;		//���̼۸񣦵�ǰ���ʵƫ������?  NUMBERT(2)		buy_percentage;			//���ְٷֱ� 70 ��ʾ 70%
	NUMBERT(2)		warn_percentage;		//����ٷֱ�
	NUMBERT(2)		force_percentage;		//ǿ��ƽ�ְٷֱ�
	CHART(1)			acount_mark;		// 0 - ����
	// 1 - �Ѹ���
	// �ͻ��յ��ñ�־�Ժ󣬷�����ؽ��ײ�ѯ�ͻ���?
	//char 			liquidationI[3929];		// ���ż���#Ϊ�ָ���,���ݿ�ʼ����һ���ָ���ֱ��Ϊ
	// ǿ��ƽ���Ŀ��Ÿ��� �磺
	//50#0123456789#0123456789#... 
	XLI_SysParamReturn()
	{
		memset (this, 0, sizeof(XLI_SysParamReturn));
	}
};

/*
3.3.3	�����
���������	����/����	ע��

��������	X��03��	QUO �C ����
SYS �C ϵͳ����
��ͬ�������������ò�ͬ�����ݣ��������ݸ�ʽ�����ġ�
��������ΪQUOʱ�����������ݣ���������ΪSYSʱ����ϵͳ��������
��������

���������	����/����	ע��
��¼����	9��02��	

������ݣ������ǵ�������

��Ʒ����	X(06)	�磺USDJPY��EURUSD
�����	9��9��V9��04��	
������	9��9��V9��04��	
��Ч��־	X(01)	0 - ��Ч��1-��Ч
���Ƽ۵���Ч��־��status��Ϊ����Ч������0����ʱ����ʾ���Ƽ۲����á��������Ƽۿͻ�����ʾ���ԡ�--��������߲����£�
ʱ��	9��14��	����Դ��ʱ�䣬yyyymmddhhmmsss

˵����
�������ݼ��ԡ�#���ָ���������ڸ�Ԫ�ؼ��ԡ�|���ָ������Ϊ��@@@@��
2#USDJPY|102.7600|102.9600|1|200501080245200#USDCAD|1.2306|1.2336|1|20050108 0245200#@@@@
*/

struct JiaoTong_HQData
{
	char	query_type[3];	// QUO - ����
	// SYS - ϵͳ����

	char	rd_num[2];		// ��¼����

	char	m_cData[1];		// ����

	int IsHQ()
	{
		return (query_type[0] == 'Q' && query_type[1] == 'U' && query_type[2] == 'O');
	}
};

#endif
