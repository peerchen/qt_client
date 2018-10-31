#include "GTPArray.h"
CGtpArray::CGtpArray()
:m_sChecksum("")
,m_sCheckdetail("")
,m_sForwardMemberPosi("")
,m_sDeferMemberPosi("")
,m_sMemberCapital("")
,m_sFeeSummary("")
,m_sSettleSummary("")
,m_sPreInterest("")
,m_sInterest("")
,m_sCityInfo("")
,m_sSpecDate("")
,m_sProdCodeDef("")
,m_sVariety("")
,m_sVarietySubstitue("")
,m_sFareModelDef("")
,m_sWhFareModel("")
,m_sDeferOverFee("")
,m_sDeferFee("")
,m_sRmbDayInterestRate("")
,m_sTakeMarginPara("")
,m_sBranchInterval("")
,m_sStorInfo("")
,m_sStorCityInfo("")
,m_sFareModelDetail("")
{

}
CGtpArray::CGtpArray(string srcStr)
:m_sChecksum("")
,m_sCheckdetail("")
,m_sForwardMemberPosi("")
,m_sDeferMemberPosi("")
,m_sMemberCapital("")
,m_sFeeSummary("")
,m_sSettleSummary("")
,m_sPreInterest("")
,m_sInterest("")
,m_sCityInfo("")
,m_sSpecDate("")
,m_sProdCodeDef("")
,m_sVariety("")
,m_sVarietySubstitue("")
,m_sFareModelDef("")
,m_sWhFareModel("")
,m_sDeferOverFee("")
,m_sDeferFee("")
,m_sRmbDayInterestRate("")
,m_sTakeMarginPara("")
,m_sBranchInterval("")
,m_sStorInfo("")
,m_sStorCityInfo("")
,m_sFareModelDetail("")
{
	SetArraySrcStr(srcStr);
}
CGtpArray::~CGtpArray()
{
	
}
//解析如下GTP数组结构"[[a1,b1,c1,d1],[a2,b2,c2,d2],[a3,b3,c3,d3]]"
//输入参数sString为要解析的字段，numOfInside为内部字段数量（如上例为4），slResult放置结果字段
//输出表示共有多少组数据结构项（如上例为3），输出-1表示解析出错，输出的字段已转义
int CGtpArray::explodeGTPArray(string sString,int numOfInside,std::vector<std::string> &slResult)
{
	//去除最外层括号
	int nRtn = strutils::stripBracket(sString);
	if (nRtn == -1)
	{
		return nRtn;
	}
	//解析
	if (sString == "" ||sString.size() == 0)
	{
		return 0;
	}
	vector<string> temp = strutils::explodeGTP(',',sString);
	int size = temp.size();
	//预设结果集大小
	slResult.reserve(numOfInside* size);

	for (int i = 0; i<size;i++)
	{
		//对解析出的每个内层结构进行解析(如解析"[a1,b1,c1,d1]")
		nRtn = strutils::stripBracket(temp[i]);
		if (nRtn == -1)
		{
			return nRtn;
		}
		vector<string> tempVal = strutils::explodeGTP(',',temp[i]);
		if (tempVal.size() != numOfInside)
		{
			//判断数量是否正确
			return -1;
		}
		//遍历解析出来的数据，进行转义
		for (int j = 0;j <tempVal.size();j++)
		{
			//转义
			tempVal[j] = strutils::delTransStr(tempVal[j]);
			//放入结果集
			slResult.insert(slResult.end(),tempVal[j]);
		}
	}
	return size;
}
//数组类型，srcStr形如 [k1=[[a1,b1,c1],[a2,b2,c2],[a3,b3,c3]],k2=[[d1],[d2]],k3=[[x1,y1],[x2,y2],[x3,y3]]]
void CGtpArray::SetArraySrcStr(string srcStr)
{
	//去掉最外层的中括号。
	int nRtn = strutils::stripBracket(srcStr);
	if (nRtn == -1)
	{
		return ;
	}
	std::vector<string> vBody;
	//k1=[[a1,b1,c1],[a2,b2,c2],[a3,b3,c3]],k2=[[d1],[d2]],k3=[[x1,y1],[x2,y2],[x3,y3]]
	//用','截取字段
	vBody = strutils::explodeGTP(',',srcStr);
	int nSize = vBody.size();
	for (int i = 0;i<nSize;i++)
	{
		//k1=[[a1,b1,c1],[a2,b2,c2],[a3,b3,c3]]
		//k2=[[d1],[d2]]
		//k3=[[x1,y1],[x2,y2],[x3,y3]]
		std::string  sParameter = vBody[i];
		string sKey("");
		string::size_type iPos;
		iPos = strutils::findFirstOf('=',sParameter);
		if (iPos != string::npos)
		{
			sKey = sParameter.substr(0,iPos);
			//{bulletinBoardInfo}	公告信息
			if (sKey == "alm_check_sum")
			{
				//形如[[a1,b1,c1],[a2,b2,c2],[a3,b3,c3]]
				m_sChecksum = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_check_detail")
			{
				m_sCheckdetail = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_forward_member_posi")
			{
				m_sForwardMemberPosi = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_defer_member_posi")
			{
				m_sDeferMemberPosi = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_member_capital")
			{
				m_sMemberCapital = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_fee_summary")
			{
				m_sFeeSummary = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_settle_summary")
			{
				m_sSettleSummary = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_pre_interest")
			{
				m_sPreInterest = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_interest")
			{
				m_sInterest = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_city_info")
			{
				m_sCityInfo = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_spec_date")
			{
				m_sSpecDate = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_prod_code_def")
			{
				m_sProdCodeDef = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_variety")
			{
				m_sVariety = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_variety_substitue")
			{
				m_sVarietySubstitue = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_fare_model_def")
			{
				m_sFareModelDef = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_wh_fare_model")
			{
				m_sWhFareModel = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_defer_over_fee")
			{
				m_sDeferOverFee = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_defer_fee")
			{
				m_sDeferFee = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_rmb_day_interest_rata")
			{
				m_sRmbDayInterestRate = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_take_margin_para")
			{
				m_sTakeMarginPara = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_branch_interval")
			{
				m_sBranchInterval = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_stor_info")
			{
				m_sStorInfo = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_stor_city_info")
			{
				m_sStorCityInfo = sParameter.substr(iPos + 1);
			}else if (sKey == "alm_fare_model_detail")
			{
				m_sFareModelDetail = sParameter.substr(iPos + 1);
			}
		}
	}
}
void CGtpArray::GetChecksumFromArrayStr(TRspTransferDataDownload *p)
{
	p->p_checksum = NULL;
	p->num_checksum = 0;
	if (m_sChecksum =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 7;
	int nSize = explodeGTPArray(m_sChecksum,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_checksum = new TRspTransferDataDownload::tagAlmChecksum[nSize];
	p->num_checksum = nSize;
	TRspTransferDataDownload::tagAlmChecksum * pNX = p->p_checksum;
	for (int i = 0;i<nSize;i++)
	{
		pNX->sum_num = FromString<int>(vec_result[0+num*i]);
		pNX->sum_bal = FromString<double>(vec_result[1+num*i]);
		pNX->in_num = FromString<int>(vec_result[2+num*i]);
		pNX->in_bal = FromString<double>(vec_result[3+num*i]);
		pNX->out_num = FromString<int>(vec_result[4+num*i]);
		pNX->out_bal = FromString<double>(vec_result[5+num*i]);
		pNX->currency_id = vec_result[6+num*i].c_str()[0];
	}
	vec_result.clear();
}
void CGtpArray::GetCheckdetailFromArrayStr(TRspTransferDataDownload *p)
{
	p->num_checkdetail = 0;
	p->p_checkdetail = NULL;
	if (m_sCheckdetail == "")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 10;
	int nSize = explodeGTPArray(m_sCheckdetail,10,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_checkdetail = new TRspTransferDataDownload::tagAlmCheckdetail[nSize];
	p->num_checkdetail = nSize;
	TRspTransferDataDownload::tagAlmCheckdetail *pNX;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_checkdetail+i;
		StrCopyToChar(pNX->exch_date,vec_result[0+num*i],sizeof(pNX->exch_date));
		StrCopyToChar(pNX->bank_seq,vec_result[1+num*i],sizeof(pNX->bank_seq));
		StrCopyToChar(pNX->gess_serial_no,vec_result[2+num*i],sizeof(pNX->gess_serial_no));
		StrCopyToChar(pNX->client_serial_no,vec_result[3+num*i],sizeof(pNX->client_serial_no));
		StrCopyToChar(pNX->account_no,vec_result[4+num*i],sizeof(pNX->account_no));
		StrCopyToChar(pNX->cust_no,vec_result[5+num*i],sizeof(pNX->cust_no));
		pNX->f_busi_type = vec_result[6+num*i].c_str()[0];
		pNX->access_way = vec_result[7+num*i].c_str()[0];
		pNX->exch_bal = FromString<double>(vec_result[8+num*i]);
		pNX->currency_id = vec_result[9+num*i].c_str()[0];
	}
	vec_result.clear();
}
void CGtpArray::GetForwardMemberPosiFromArrayStr(TRspFundCheckDataDownload *p)
{
	p->p_forward_member_posi = NULL;
	p->num_forward_member_posi = 0;
	if (m_sForwardMemberPosi =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 18;
	int nSize = explodeGTPArray(m_sForwardMemberPosi,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_forward_member_posi = new TRspFundCheckDataDownload::tagForwardMemberPosi[nSize];
	p->num_forward_member_posi = nSize;
	TRspFundCheckDataDownload::tagForwardMemberPosi * pNX ;//= p->p_forward_member_posi;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_forward_member_posi + i;
		StrCopyToChar(pNX->exch_date,vec_result[0+num*i],sizeof(pNX->exch_date));
		StrCopyToChar(pNX->member_id,vec_result[1+num*i],sizeof(pNX->member_id));
		StrCopyToChar(pNX->instID,vec_result[2+num*i],sizeof(pNX->instID));
		StrCopyToChar(pNX->due_date,vec_result[3+num*i],sizeof(pNX->due_date));
		pNX->net_amt = FromString<int>(vec_result[4+num*i]);
		pNX->curr_long_amt = FromString<int>(vec_result[5+num*i]);
		pNX->curr_short_amt = FromString<int>(vec_result[6+num*i]);
		pNX->long_posi_bal = FromString<double>(vec_result[7+num*i]);
		pNX->short_posi_bal = FromString<double>(vec_result[8+num*i]);
		pNX->open_long_amt = FromString<int>(vec_result[9+num*i]);
		pNX->open_short_amt = FromString<int>(vec_result[10+num*i]);
		pNX->cov_long_amt = FromString<int>(vec_result[11+num*i]);
		pNX->cov_short_amt = FromString<int>(vec_result[12+num*i]);
		pNX->float_surplus = FromString<double>(vec_result[13+num*i]);
		pNX->cov_surplus = FromString<double>(vec_result[14+num*i]);
		pNX->fee = FromString<double>(vec_result[15+num*i]);
		pNX->margin = FromString<double>(vec_result[16+num*i]);
		pNX->settle_price = FromString<double>(vec_result[17+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetDeferMemberPosiFromArrayStr(TRspFundCheckDataDownload *p)
{
	p->p_defer_member_posi = NULL;
	p->num_defer_member_posi = 0;
	if (m_sDeferMemberPosi =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 14;
	int nSize = explodeGTPArray(m_sDeferMemberPosi,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_defer_member_posi = new TRspFundCheckDataDownload::tagDeferMemberPosi[nSize];
	p->num_defer_member_posi = nSize;
	TRspFundCheckDataDownload::tagDeferMemberPosi * pNX;// = p->p_defer_member_posi;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_defer_member_posi + i;
		StrCopyToChar(pNX->exch_date,vec_result[0+num*i],sizeof(pNX->exch_date));
		StrCopyToChar(pNX->member_id,vec_result[1+num*i],sizeof(pNX->member_id));
		StrCopyToChar(pNX->instID,vec_result[2+num*i],sizeof(pNX->instID));
		pNX->curr_long_amt = FromString<int>(vec_result[3+num*i]);
		pNX->curr_short_amt = FromString<int>(vec_result[4+num*i]);
		pNX->open_long_amt = FromString<int>(vec_result[5+num*i]);
		pNX->open_short_amt = FromString<int>(vec_result[6+num*i]);
		pNX->cov_long_amt = FromString<int>(vec_result[7+num*i]);
		pNX->cov_short_amt = FromString<int>(vec_result[8+num*i]);
		pNX->exch_surplus = FromString<double>(vec_result[9+num*i]);
		pNX->fee = FromString<double>(vec_result[10+num*i]);
		pNX->margin = FromString<double>(vec_result[11+num*i]);
		pNX->settle_price = FromString<double>(vec_result[12+num*i]);
		pNX->defer_fee = FromString<double>(vec_result[13+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetMemberCapitalFromArrayStr(TRspFundCheckDataDownload *p)
{
	p->p_member_capital = NULL;
	p->num_member_capital = 0;
	if (m_sMemberCapital =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 28;
	int nSize = explodeGTPArray(m_sMemberCapital,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_member_capital = new TRspFundCheckDataDownload::tagMemberCapital[nSize];
	p->num_member_capital = nSize;
	TRspFundCheckDataDownload::tagMemberCapital * pNX ;//= p->p_member_capital;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_member_capital + i ;
		StrCopyToChar(pNX->exch_date,vec_result[0+num*i],sizeof(pNX->exch_date));
		StrCopyToChar(pNX->member_id,vec_result[1+num*i],sizeof(pNX->member_id));
		//StrCopyToChar(pNX->acct_type,vec_result[2+num*i],sizeof(pNX->member_id));
		pNX->acct_type = vec_result[2+num*i].c_str()[0];
		pNX->curr_can_get = FromString<double>(vec_result[3+num*i]);
		pNX->last_balance = FromString<double>(vec_result[4+num*i]);
		pNX->last_b_margin = FromString<double>(vec_result[5+num*i]);
		pNX->last_base_margin = FromString<double>(vec_result[6+num*i]);
		pNX->last_reserve = FromString<double>(vec_result[7+num*i]);
		pNX->last_long_froz = FromString<double>(vec_result[8+num*i]);
		pNX->last_forward_froz = FromString<double>(vec_result[9+num*i]);
		pNX->last_deli_prepare = FromString<double>(vec_result[10+num*i]);
		pNX->last_deli_margin = FromString<double>(vec_result[11+num*i]);
		pNX->deli_prepare = FromString<double>(vec_result[12+num*i]);
		pNX->deli_margin = FromString<double>(vec_result[13+num*i]);
		pNX->balance = FromString<double>(vec_result[14+num*i]);
		pNX->real_b_margin = FromString<double>(vec_result[15+num*i]);
		pNX->base_margin = FromString<double>(vec_result[16+num*i]);
		pNX->real_reserve = FromString<double>(vec_result[17+num*i]);
		pNX->day_long_froz = FromString<double>(vec_result[18+num*i]);
		pNX->day_forward_froz = FromString<double>(vec_result[19+num*i]);
		pNX->profit = FromString<double>(vec_result[20+num*i]);
		pNX->today_inbal = FromString<double>(vec_result[21+num*i]);
		pNX->today_outbal = FromString<double>(vec_result[22+num*i]);
		pNX->real_sell = FromString<double>(vec_result[23+num*i]);
		pNX->real_buy = FromString<double>(vec_result[24+num*i]);
		pNX->misc_fee = FromString<double>(vec_result[25+num*i]);
		pNX->interest = FromString<double>(vec_result[26+num*i]);
		pNX->bail = FromString<double>(vec_result[27+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetFeeSummaryFromArrayStr(TRspFundCheckDataDownload *p)
{
	p->p_fee_summary = NULL;
	p->num_fee_summary = 0;
	if (m_sFeeSummary =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 13;
	int nSize = explodeGTPArray(m_sFeeSummary,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_fee_summary = new TRspFundCheckDataDownload::tagFeeSummary[nSize];
	p->num_fee_summary = nSize;
	TRspFundCheckDataDownload::tagFeeSummary * pNX ;//;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_fee_summary + i;
		StrCopyToChar(pNX->exch_date,vec_result[0+num*i],sizeof(pNX->exch_date));
		StrCopyToChar(pNX->member_id,vec_result[1+num*i],sizeof(pNX->member_id));
		pNX->fee = FromString<double>(vec_result[2+num*i]);
		pNX->delivery_fee = FromString<double>(vec_result[3+num*i]);
		pNX->storage_fee = FromString<double>(vec_result[4+num*i]);
		pNX->trans_fee = FromString<double>(vec_result[5+num*i]);
		pNX->overdue_fee = FromString<double>(vec_result[6+num*i]);
		pNX->impawn_fee = FromString<double>(vec_result[7+num*i]);
		pNX->loadreg_fee = FromString<double>(vec_result[8+num*i]);
		pNX->breach_fee = FromString<double>(vec_result[9+num*i]);
		pNX->defer_fee = FromString<double>(vec_result[10+num*i]);
		pNX->profit = FromString<double>(vec_result[11+num*i]);
		pNX->amount = FromString<double>(vec_result[12+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetSettleSummaryFromArrayStr(TRspFundCheckDataDownload *p)
{
	p->p_settle_summary = NULL;
	p->num_settle_summary = 0;
	if (m_sSettleSummary =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 6;
	int nSize = explodeGTPArray(m_sSettleSummary,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_settle_summary = new TRspFundCheckDataDownload::tagSettleSummary[nSize];
	p->num_settle_summary = nSize;
	TRspFundCheckDataDownload::tagSettleSummary * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_settle_summary + i;
		StrCopyToChar(pNX->exch_date,vec_result[0+num*i],sizeof(pNX->exch_date));
		StrCopyToChar(pNX->member_id,vec_result[1+num*i],sizeof(pNX->member_id));
		pNX->diff = FromString<double>(vec_result[2+num*i]);
		pNX->vari_agio = FromString<double>(vec_result[3+num*i]);
		pNX->item_agio = FromString<double>(vec_result[4+num*i]);
		pNX->sum_agio = FromString<double>(vec_result[5+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetPreInterestFromArrayStr(TRspInterestDataDownload *p)
{
	p->p_pre_interest = NULL;
	p->num_pre_interest = 0;
	if (m_sPreInterest =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 12;
	int nSize = explodeGTPArray(m_sPreInterest,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_pre_interest = new TRspInterestDataDownload::tagPreInterest[nSize];
	p->num_pre_interest = nSize;
	TRspInterestDataDownload::tagPreInterest * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_pre_interest + i;
		StrCopyToChar(pNX->seq_no,vec_result[0+num*i],sizeof(pNX->seq_no));
		StrCopyToChar(pNX->member_id,vec_result[1+num*i],sizeof(pNX->member_id));
		StrCopyToChar(pNX->acct_no,vec_result[2+num*i],sizeof(pNX->acct_no));
		StrCopyToChar(pNX->cust_id,vec_result[3+num*i],sizeof(pNX->cust_id));
		StrCopyToChar(pNX->inte_type,vec_result[4+num*i],sizeof(pNX->inte_type));
		pNX->inte_integral = FromString<double>(vec_result[5+num*i]);
		pNX->inte_rate = FromString<double>(vec_result[6+num*i]);
		pNX->inte_tax_rate = FromString<double>(vec_result[7+num*i]);
		pNX->incr_inte = FromString<double>(vec_result[8+num*i]);
		pNX->incr_inte_tax = FromString<double>(vec_result[9+num*i]);
		pNX->currency_id = vec_result[10+num*i].c_str()[0];
		StrCopyToChar(pNX->o_term_type,vec_result[11+num*i],sizeof(pNX->o_term_type));
	}
	vec_result.clear();
}
void CGtpArray::GetInterestFromArrayStr(TRspInterestDataDownload *p)
{
	p->p_interest = NULL;
	p->num_interest = 0;
	if (m_sInterest =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 8;
	int nSize = explodeGTPArray(m_sInterest,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_interest = new TRspInterestDataDownload::tagInterest[nSize];
	p->num_interest = nSize;
	TRspInterestDataDownload::tagInterest * pNX;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_interest + i;
		StrCopyToChar(pNX->seq_no,vec_result[0+num*i],sizeof(pNX->seq_no));
		StrCopyToChar(pNX->member_id,vec_result[1+num*i],sizeof(pNX->member_id));
		StrCopyToChar(pNX->acct_no,vec_result[2+num*i],sizeof(pNX->acct_no));
		StrCopyToChar(pNX->cust_id,vec_result[3+num*i],sizeof(pNX->cust_id));
		pNX->incr_inte = FromString<double>(vec_result[4+num*i]);
		pNX->incr_inte_tax = FromString<double>(vec_result[5+num*i]);
		pNX->currency_id = vec_result[10+num*i].c_str()[0];
		StrCopyToChar(pNX->o_term_type,vec_result[11+num*i],sizeof(pNX->o_term_type));
	}
	vec_result.clear();
}
void CGtpArray::GetCityInfoFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_city_info = NULL;
	p->num_city_info = 0;
	if (m_sCityInfo =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 2;
	int nSize = explodeGTPArray(m_sCityInfo,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_city_info = new TRspSigexBasicDataDownload::tagCityInfo[nSize];
	p->num_city_info = nSize;
	TRspSigexBasicDataDownload::tagCityInfo * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_city_info + i;
		StrCopyToChar(pNX->city_code,vec_result[0+num*i],sizeof(pNX->city_code));
		StrCopyToChar(pNX->city_name,vec_result[1+num*i],sizeof(pNX->city_name));
	}
	vec_result.clear();
}
void CGtpArray::GetSpecDateFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_spec_date = NULL;
	p->num_spec_date = 0;
	if (m_sSpecDate =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 2;
	int nSize = explodeGTPArray(m_sSpecDate,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_spec_date = new TRspSigexBasicDataDownload::tagSpecDate[nSize];
	p->num_spec_date = nSize;
	TRspSigexBasicDataDownload::tagSpecDate * pNX;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_spec_date + i;
		StrCopyToChar(pNX->spec_date,vec_result[0+num*i],sizeof(pNX->spec_date));
		StrCopyToChar(pNX->date_type,vec_result[1+num*i],sizeof(pNX->date_type));
	}
	vec_result.clear();
}
void CGtpArray::GetProdCodeDefFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_prod_code_def = NULL;
	p->num_prod_code_def = 0;
	if (m_sProdCodeDef =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 29;
	int nSize = explodeGTPArray(m_sProdCodeDef,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_prod_code_def = new TRspSigexBasicDataDownload::tagProdCodeDef[nSize];
	p->num_prod_code_def = nSize;
	TRspSigexBasicDataDownload::tagProdCodeDef * pNX;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_prod_code_def + i ;
		StrCopyToChar(pNX->prod_code,vec_result[0+num*i],sizeof(pNX->prod_code));
		StrCopyToChar(pNX->prod_name,vec_result[1+num*i],sizeof(pNX->prod_name));
		StrCopyToChar(pNX->bourse_id,vec_result[2+num*i],sizeof(pNX->bourse_id));
		pNX->currency_id = vec_result[3+num*i].c_str()[0];
		StrCopyToChar(pNX->market_id,vec_result[4+num*i],sizeof(pNX->market_id));
		StrCopyToChar(pNX->variety_type,vec_result[5+num*i],sizeof(pNX->variety_type));
		StrCopyToChar(pNX->variety_id,vec_result[6+num*i],sizeof(pNX->variety_id));
		pNX->tick = FromString<double>(vec_result[7+num*i]);
		StrCopyToChar(pNX->t0_sign,vec_result[8+num*i],sizeof(pNX->t0_sign));
		StrCopyToChar(pNX->bail_sign,vec_result[9+num*i],sizeof(pNX->bail_sign));
		pNX->bail_rate = FromString<double>(vec_result[10+num*i]);
		StrCopyToChar(pNX->limit_sign,vec_result[11+num*i],sizeof(pNX->limit_sign));
		pNX->upper_limit_value = FromString<double>(vec_result[12+num*i]);
		pNX->lower_limit_value = FromString<double>(vec_result[13+num*i]);
		pNX->active_flag = vec_result[14+num*i].c_str()[0];
		StrCopyToChar(pNX->inst_stat,vec_result[15+num*i],sizeof(pNX->inst_stat));
		pNX->ref_price = FromString<double>(vec_result[16+num*i]);
		pNX->recv_rate = FromString<double>(vec_result[17+num*i]);
		StrCopyToChar(pNX->busi_mode,vec_result[18+num*i],sizeof(pNX->busi_mode));
		pNX->max_hand = FromString<int>(vec_result[19+num*i]);
		pNX->min_hand = FromString<int>(vec_result[20+num*i]);
		StrCopyToChar(pNX->exch_unit,vec_result[21+num*i],sizeof(pNX->exch_unit));
		pNX->measure_unit = FromString<double>(vec_result[22+num*i]);
		StrCopyToChar(pNX->entr_way_str,vec_result[23+num*i],sizeof(pNX->entr_way_str));
		pNX->fare_sign = vec_result[24+num*i].c_str()[0];
		pNX->fare_value = FromString<double>(vec_result[25+num*i]);
		StrCopyToChar(pNX->fare_model_id,vec_result[26+num*i],sizeof(pNX->fare_model_id));
		StrCopyToChar(pNX->due_date,vec_result[27+num*i],sizeof(pNX->due_date));
		pNX->deli_days = FromString<int>(vec_result[28+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetVarietyFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_variety = NULL;
	p->num_variety = 0;
	if (m_sVariety =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 8;
	int nSize = explodeGTPArray(m_sVariety,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_variety = new TRspSigexBasicDataDownload::tagVariety[nSize];
	p->num_variety = nSize;
	TRspSigexBasicDataDownload::tagVariety * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_variety + i ;
		StrCopyToChar(pNX->variety_ID,vec_result[0+num*i],sizeof(pNX->variety_ID));
		StrCopyToChar(pNX->name,vec_result[1+num*i],sizeof(pNX->name));
		StrCopyToChar(pNX->abbr,vec_result[2+num*i],sizeof(pNX->abbr));
		StrCopyToChar(pNX->variety_type,vec_result[3+num*i],sizeof(pNX->variety_type));
		pNX->min_pickup = FromString<double>(vec_result[4+num*i]);
		pNX->pickup_base = FromString<double>(vec_result[5+num*i]);
		StrCopyToChar(pNX->weight_unit,vec_result[6+num*i],sizeof(pNX->weight_unit));
		StrCopyToChar(pNX->destroy_flag,vec_result[7+num*i],sizeof(pNX->destroy_flag));
	}
	vec_result.clear();
}
void CGtpArray::GetVarietySubstitueFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_variety_substitue = NULL;
	p->num_variety_substitue = 0;
	if (m_sVarietySubstitue =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 4;
	int nSize = explodeGTPArray(m_sVarietySubstitue,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_variety_substitue = new TRspSigexBasicDataDownload::tagVarietySubstitue[nSize];
	p->num_variety_substitue = nSize;
	TRspSigexBasicDataDownload::tagVarietySubstitue * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_variety_substitue + i;
		StrCopyToChar(pNX->prod_code,vec_result[0+num*i],sizeof(pNX->prod_code));
		pNX->seq_no = FromString<int>(vec_result[1+num*i]);
		StrCopyToChar(pNX->variety_id,vec_result[2+num*i],sizeof(pNX->variety_id));
		pNX->diff_amt = FromString<double>(vec_result[3+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetFareModelDefFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_fare_model_def = NULL;
	p->num_fare_model_def = 0;
	if (m_sFareModelDef =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 7;
	int nSize = explodeGTPArray(m_sFareModelDef,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_fare_model_def = new TRspSigexBasicDataDownload::tagFareModelDef[nSize];
	p->num_fare_model_def = nSize;
	TRspSigexBasicDataDownload::tagFareModelDef * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_fare_model_def + i;
		StrCopyToChar(pNX->fare_model_id,vec_result[0+num*i],sizeof(pNX->fare_model_id));
		StrCopyToChar(pNX->fare_model_name,vec_result[1+num*i],sizeof(pNX->fare_model_name));
		StrCopyToChar(pNX->fare_model_type,vec_result[2+num*i],sizeof(pNX->fare_model_type));
		StrCopyToChar(pNX->contain_bourse,vec_result[3+num*i],sizeof(pNX->contain_bourse));
		StrCopyToChar(pNX->branch_id,vec_result[4+num*i],sizeof(pNX->branch_id));
		StrCopyToChar(pNX->m_term_type,vec_result[5+num*i],sizeof(pNX->m_term_type));
		StrCopyToChar(pNX->m_teller_id,vec_result[6+num*i],sizeof(pNX->m_teller_id));
	}
	vec_result.clear();
}
void CGtpArray::GetWhFareModelFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_wh_fare_model = NULL;
	p->num_wh_fare_model = 0;
	if (m_sWhFareModel =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 6;
	int nSize = explodeGTPArray(m_sWhFareModel,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_wh_fare_model = new TRspSigexBasicDataDownload::tagWhFareModel[nSize];
	p->num_wh_fare_model = nSize;
	TRspSigexBasicDataDownload::tagWhFareModel * pNX;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_wh_fare_model + i;
		StrCopyToChar(pNX->fare_model_id,vec_result[0+num*i],sizeof(pNX->fare_model_id));
		StrCopyToChar(pNX->stor_id,vec_result[1+num*i],sizeof(pNX->stor_id));
		StrCopyToChar(pNX->variety_id,vec_result[2+num*i],sizeof(pNX->variety_id));
		StrCopyToChar(pNX->fare_type_id,vec_result[3+num*i],sizeof(pNX->fare_type_id));
		StrCopyToChar(pNX->fare_mode,vec_result[4+num*i],sizeof(pNX->fare_mode));
		pNX->fare_value = FromString<double>(vec_result[5+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetDeferOverFeeFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_defer_over_fee = NULL;
	p->num_defer_over_fee = 0;
	if (m_sDeferOverFee =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 5;
	int nSize = explodeGTPArray(m_sDeferOverFee,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_defer_over_fee = new TRspSigexBasicDataDownload::tagDeferOverFee[nSize];
	p->num_defer_over_fee = nSize;
	TRspSigexBasicDataDownload::tagDeferOverFee * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_defer_over_fee + i;
		StrCopyToChar(pNX->prod_code,vec_result[0+num*i],sizeof(pNX->prod_code));
		pNX->seq_no = FromString<int>(vec_result[1+num*i]);
		StrCopyToChar(pNX->start_day,vec_result[2+num*i],sizeof(pNX->start_day));
		StrCopyToChar(pNX->end_day,vec_result[3+num*i],sizeof(pNX->end_day));
		pNX->fee_rate = FromString<double>(vec_result[4+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetDeferFeeFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_defer_fee = NULL;
	p->num_defer_fee = 0;
	if (m_sDeferFee =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 4;
	int nSize = explodeGTPArray(m_sDeferFee,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_defer_fee = new TRspSigexBasicDataDownload::tagDeferFee[nSize];
	p->num_defer_fee = nSize;
	TRspSigexBasicDataDownload::tagDeferFee * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_defer_fee + i;
		StrCopyToChar(pNX->exch_date,vec_result[0+num*i],sizeof(pNX->exch_date));
		StrCopyToChar(pNX->prod_code,vec_result[1+num*i],sizeof(pNX->prod_code));
		StrCopyToChar(pNX->pay_direction,vec_result[2+num*i],sizeof(pNX->pay_direction));
		pNX->fee_rate = FromString<double>(vec_result[3+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetRmbDayInterestRateFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_rmb_day_interest_rate = NULL;
	p->num_rmb_day_interest_rate = 0;
	if (m_sRmbDayInterestRate =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 7;
	int nSize = explodeGTPArray(m_sRmbDayInterestRate,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_rmb_day_interest_rate = new TRspSigexBasicDataDownload::tagRmbDayInterestRate[nSize];
	p->num_rmb_day_interest_rate = nSize;
	TRspSigexBasicDataDownload::tagRmbDayInterestRate * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_rmb_day_interest_rate + i;
		//StrCopyToChar(pNX->acct_type,vec_result[0+num*i],sizeof(pNX->member_id));
		pNX->acct_type = vec_result[0+num*i].c_str()[0];
		pNX->seq_no = FromString<int>(vec_result[1+num*i]);
		StrCopyToChar(pNX->s_valid_exch_date,vec_result[2+num*i],sizeof(pNX->s_valid_exch_date));
		StrCopyToChar(pNX->e_valid_exch_date,vec_result[3+num*i],sizeof(pNX->e_valid_exch_date));
		pNX->inte_rate = FromString<double>(vec_result[4+num*i]);
		pNX->inte_tax_rate = FromString<double>(vec_result[5+num*i]);
		pNX->puni_rate = FromString<double>(vec_result[6+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetTakeMarginParaFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_take_margin_para = NULL;
	p->num_take_margin_para = 0;
	if (m_sTakeMarginPara =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 3;
	int nSize = explodeGTPArray(m_sTakeMarginPara,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_take_margin_para = new TRspSigexBasicDataDownload::tagTakeMarginPara[nSize];
	p->num_take_margin_para = nSize;
	TRspSigexBasicDataDownload::tagTakeMarginPara * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_take_margin_para + i ;
		StrCopyToChar(pNX->variety_ID,vec_result[0+num*i],sizeof(pNX->variety_ID));
		pNX->price_offset_rate = FromString<double>(vec_result[1+num*i]);
		pNX->unit_max_diff = FromString<double>(vec_result[2+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetBranchIntervalFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_branch_interval = NULL;
	p->num_branch_interval = 0;
	if (m_sBranchInterval =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 6;
	int nSize = explodeGTPArray(m_sBranchInterval,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_branch_interval = new TRspSigexBasicDataDownload::tagBranchInterval[nSize];
	p->num_branch_interval = nSize;
	TRspSigexBasicDataDownload::tagBranchInterval * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_branch_interval + i;
		StrCopyToChar(pNX->branch_id,vec_result[0+num*i],sizeof(pNX->branch_id));
		StrCopyToChar(pNX->prod_code,vec_result[1+num*i],sizeof(pNX->prod_code));
		StrCopyToChar(pNX->fare_type_id,vec_result[2+num*i],sizeof(pNX->fare_type_id));
		StrCopyToChar(pNX->fare_mode,vec_result[3+num*i],sizeof(pNX->fare_mode));
		pNX->min_value = FromString<double>(vec_result[4+num*i]);
		pNX->max_value = FromString<double>(vec_result[5+num*i]);

	}
	vec_result.clear();
}
void CGtpArray::GetStorInfoFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_stor_info = NULL;
	p->num_stor_info = 0;
	if (m_sStorInfo =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 10;
	int nSize = explodeGTPArray(m_sStorInfo,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_stor_info = new TRspSigexBasicDataDownload::tagStorInfo[nSize];
	p->num_stor_info = nSize;
	TRspSigexBasicDataDownload::tagStorInfo * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_stor_info + i;
		StrCopyToChar(pNX->stor_id,vec_result[0+num*i],sizeof(pNX->stor_id));
		StrCopyToChar(pNX->stor_name,vec_result[1+num*i],sizeof(pNX->stor_name));
		StrCopyToChar(pNX->addr,vec_result[2+num*i],sizeof(pNX->addr));
		StrCopyToChar(pNX->tel,vec_result[3+num*i],sizeof(pNX->tel));
		StrCopyToChar(pNX->fax,vec_result[4+num*i],sizeof(pNX->fax));
		StrCopyToChar(pNX->link_man,vec_result[5+num*i],sizeof(pNX->link_man));
		StrCopyToChar(pNX->zip_code,vec_result[6+num*i],sizeof(pNX->zip_code));
		StrCopyToChar(pNX->use_variety_type,vec_result[7+num*i],sizeof(pNX->use_variety_type));
		StrCopyToChar(pNX->is_take,vec_result[8+num*i],sizeof(pNX->is_take));
		StrCopyToChar(pNX->stor_name_e,vec_result[9+num*i],sizeof(pNX->stor_name_e));
	}
	vec_result.clear();
}
void CGtpArray::GetStorCityInfoFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_stor_city_info = NULL;
	p->num_stor_city_info = 0;
	if (m_sStorCityInfo =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 3;
	int nSize = explodeGTPArray(m_sStorCityInfo,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_stor_city_info = new TRspSigexBasicDataDownload::tagStorCityInfo[nSize];
	p->num_stor_city_info = nSize;
	TRspSigexBasicDataDownload::tagStorCityInfo * pNX;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_stor_city_info + i ;
		StrCopyToChar(pNX->stor_id,vec_result[0+num*i],sizeof(pNX->stor_id));
		StrCopyToChar(pNX->city_code,vec_result[1+num*i],sizeof(pNX->city_code));
		StrCopyToChar(pNX->is_default_stor,vec_result[2+num*i],sizeof(pNX->is_default_stor));
	}
	vec_result.clear();
}
void CGtpArray::GetFareModelDetailFromArrayStr(TRspSigexBasicDataDownload *p)
{
	p->p_fare_model_detail = NULL;
	p->num_fare_model_detail = 0;
	if (m_sFareModelDetail =="")
	{
		return ;
	}
	vector<string> vec_result;
	int num = 5;
	int nSize = explodeGTPArray(m_sFareModelDetail,num,vec_result);
	if (nSize <1)
	{
		return ;
	}
	p->p_fare_model_detail = new TRspSigexBasicDataDownload::tagFareModelDetail[nSize];
	p->num_fare_model_detail = nSize;
	TRspSigexBasicDataDownload::tagFareModelDetail * pNX ;
	for (int i = 0;i<nSize;i++)
	{
		pNX = p->p_fare_model_detail + i ;
		StrCopyToChar(pNX->fare_model_id,vec_result[0+num*i],sizeof(pNX->fare_model_id));
		StrCopyToChar(pNX->prod_code,vec_result[1+num*i],sizeof(pNX->prod_code));
		StrCopyToChar(pNX->fare_type_id,vec_result[2+num*i],sizeof(pNX->fare_type_id));
		StrCopyToChar(pNX->fare_mode,vec_result[3+num*i],sizeof(pNX->fare_mode));
		pNX->fare_value = FromString<double>(vec_result[4+num*i]);
	}
	vec_result.clear();
}
void CGtpArray::GetRefPriceQueryFlow(TRspRefPriceQueryFlow * p,string srcStr)
{
	//消息组件格式
	//k={ka1=va1,kb1=vb1,kc1=vc1},k={ka2=va2,kb2=vb2,kc2=vc2},k={ka3=va3,kb3=vb3,kc3=vc3}
	p->p_ref_price = NULL;
	p->num_ref_price = 0;
	CGtpMsgArray msgArray(srcStr);
	p->num_ref_price = msgArray.GetArraySize();
	if (p->num_ref_price < 1)
	{
		return ;
	}
	p->p_ref_price = new TRspRefPriceQueryFlow::tagRefPrice[p->num_ref_price];
	TRspRefPriceQueryFlow::tagRefPrice *pNX;
	for (int i = 0;i<p->num_ref_price;i++)
	{
		pNX = p->p_ref_price + i;
		StrCopyToChar(pNX->prod_code,msgArray.GetValueByKeyIndex("I10",i),sizeof(pNX->prod_code));
		StrCopyToChar(pNX->exch_date,msgArray.GetValueByKeyIndex("T13",i),sizeof(pNX->exch_date));
		StrCopyToChar(pNX->game_id,msgArray.GetValueByKeyIndex("Q34",i),sizeof(pNX->game_id));
		StrCopyToChar(pNX->member_id,msgArray.GetValueByKeyIndex("M00",i),sizeof(pNX->member_id));
		StrCopyToChar(pNX->serial,msgArray.GetValueByKeyIndex("X61",i),sizeof(pNX->serial));
		StrCopyToChar(pNX->report_time,msgArray.GetValueByKeyIndex("T12",i),sizeof(pNX->report_time));
		pNX->report_price = FromString<double>(msgArray.GetValueByKeyIndex("I20",i));
	}
}
void CGtpArray::StrCopyToChar(char *destStr,string  srcStr,size_t copyNum)
{
	strncpy(destStr,srcStr.c_str(),copyNum);
	destStr[copyNum-1]='\0';
}
void CGtpArray::GetResultFromArrayStr(TRspQuerySigexNotice * p,string srcStr)
{
	//消息组件格式
	//k={ka1=va1,kb1=vb1,kc1=vc1},k={ka2=va2,kb2=vb2,kc2=vc2},k={ka3=va3,kb3=vb3,kc3=vc3}
	p->p_result = NULL;
	p->num_result = 0;
	CGtpMsgArray msgArray(srcStr);
	p->num_result = msgArray.GetArraySize();
	if (p->num_result < 1)
	{
		return ;
	}
	p->p_result = new TRspQuerySigexNotice::tagResult[p->num_result];
	TRspQuerySigexNotice::tagResult *pNX ;
	for (int i = 0;i<p->num_result;i++)
	{
		pNX = p->p_result + i;
		StrCopyToChar(pNX->announcer,msgArray.GetValueByKeyIndex("G20",i),sizeof(pNX->announcer));
		StrCopyToChar(pNX->content,msgArray.GetValueByKeyIndex("Q85",i),sizeof(pNX->content));
		StrCopyToChar(pNX->title,msgArray.GetValueByKeyIndex("Q84",i),sizeof(pNX->title));
		StrCopyToChar(pNX->exch_date,msgArray.GetValueByKeyIndex("Q82",i),sizeof(pNX->exch_date));
		StrCopyToChar(pNX->exch_time,msgArray.GetValueByKeyIndex("Q83",i),sizeof(pNX->exch_time));
		StrCopyToChar(pNX->seq_no,msgArray.GetValueByKeyIndex("T80",i),sizeof(pNX->seq_no));
	}
}
//取结构体中值拼凑为数组格式的字符串
//消息组件类型，srcStr形如[k={ka1=va1,kb1=vb1,kc1=vc1},k={ka2=va2,kb2=vb2,kc2=vc2},k={ka3=va3,kb3=vb3,kc3=vc3}]
//消息组件格式
string CGtpArray::PutBreakpointToArrayStr(TReqLogin &almBreakPoint)
{
	if (almBreakPoint.num_almbreakpoint == 0 || almBreakPoint.p_almbreakpoint == NULL)
	{
		return "[]";
	}
	vector<string> vArray;
	
	int n = almBreakPoint.num_almbreakpoint;
	for (int i = 0;i<n;i++)
	{
		vArray.push_back("X21");
		vArray.push_back("X04");
		vArray.push_back(almBreakPoint.p_almbreakpoint[i].sequence_seriesno);
		vArray.push_back("X05");
		vArray.push_back(almBreakPoint.p_almbreakpoint[i].sequence_no);
	}
	string result = CGtpMsgArray::PrintArrayStr(vArray);
	return result;
}
//普通数组格式
//输入：sArrayStr数组名(k1)	  vValue值数组(a1,b1,c1,a2,b2,c2)  nLineSize 每一行长度(3)
//输出： k1=[[a1,b1,c1],[a2,b2,c2]]
void CGtpArray::PutValueToArrayStr(string &sArrayStr,vector<string> &vValue,int nLineSize)
{
	if (sArrayStr == "")
	{
		return ;
	}
	sArrayStr += "=[[";
	sArrayStr += strutils::addTransStr(vValue[0]);
	for (int i = 1;i<vValue.size();i++)
	{
		if (i % nLineSize == 0)
		{
			//整除
			sArrayStr += "],[";
		}else
			sArrayStr += ",";
		sArrayStr += strutils::addTransStr(vValue[i]);
	}
	sArrayStr += "]]";
}
//数组类型，srcStr形如 [k1=[[a1,b1,c1],[a2,b2,c2],[a3,b3,c3]],k2=[[d1],[d2]],k3=[[x1,y1],[x2,y2],[x3,y3]]]
string CGtpArray::PutFareInfoListToArrayStr(TReqSigexMemFareSyn &almFareInfoList)
{
	string result ="alm_fare_info_list";
	if (almFareInfoList.num_fare_info_list == 0 || almFareInfoList.p_fare_info_list == NULL)
	{
		result = "[" +result;
		result += "=[]]";
		return result;
	}
	vector<string> vList ;
	for (int i = 0;i<almFareInfoList.num_fare_info_list;i++)
	{
		vList.insert(vList.end(),almFareInfoList.p_fare_info_list[i].prod_code);
		vList.insert(vList.end(),almFareInfoList.p_fare_info_list[i].fare_type_id);
		vList.insert(vList.end(),almFareInfoList.p_fare_info_list[i].fare_mode);
		vList.insert(vList.end(),ToString<double>(almFareInfoList.p_fare_info_list[i].fare_value));
	}
	PutValueToArrayStr(result,vList,4);
	result = "[" +result;
	result += "]";
	return result;
}
string CGtpArray::PutAcctFareInfoToArrayStr(TReqSpecialAcctFareSyn &almAcctFareInfo)
{
	string result = "alm_acct_fare_info";
	if (almAcctFareInfo.num_acct_fare_info == 0 || almAcctFareInfo.p_acct_fare_info == NULL)
	{
		result = "[" +result;
		result += "=[]]";
		return result;
	}
	vector<string> vList ;
	for (int i = 0;i<almAcctFareInfo.num_acct_fare_info;i++)
	{
		vList.insert(vList.end(),almAcctFareInfo.p_acct_fare_info[i].prod_code);
		vList.insert(vList.end(),almAcctFareInfo.p_acct_fare_info[i].fare_type_id);
		vList.insert(vList.end(),almAcctFareInfo.p_acct_fare_info[i].fare_mode);
		vList.insert(vList.end(),ToString<double>(almAcctFareInfo.p_acct_fare_info[i].fare_value));
	}
	PutValueToArrayStr(result,vList,4);
	result = "[" +result;
	result += "]";
	return result;
}
//自由包的buff解析
void CGtpArray::Get0x00A00123(T0x00A00123 *p ,std::string buff)
{
	vector<std::string> result;
	result = strutils::explodeGTP('|',buff);
	int i = 0;
	StrCopyToChar(p->memberID   ,result[i++],sizeof(p->memberID   ));
	StrCopyToChar(p->effectDate ,result[i++],sizeof(p->effectDate ));
	StrCopyToChar(p->seqNo      ,result[i++],sizeof(p->seqNo      ));
	StrCopyToChar(p->sheetNo    ,result[i++],sizeof(p->sheetNo    ));
	StrCopyToChar(p->clientID   ,result[i++],sizeof(p->clientID   ));
	p->accountType = (result[i++].c_str())[0];
	StrCopyToChar(p->transType  ,result[i++],sizeof(p->transType  ));
	StrCopyToChar(p->varietyID  ,result[i++],sizeof(p->varietyID  ));
	StrCopyToChar(p->warehouseID,result[i++],sizeof(p->warehouseID));
	p->stdStorage = FromString<double>(result[i++]);
	p->totalStore = FromString<double>(result[i++]);
	p->sumStore = FromString<double>(result[i++]);
	StrCopyToChar(p->transDate  ,result[i++],sizeof(p->transDate  ));
	StrCopyToChar(p->transTime  ,result[i++],sizeof(p->transTime  ));

}
void CGtpArray::Get0x00A00202(T0x00A00202 *p ,std::string buff)
{
	vector<std::string> result;
	result = strutils::explodeGTP('|',buff);
	int i = 0;
	StrCopyToChar(p->pickupSheetNo ,result[i++],sizeof(p->pickupSheetNo ));
	StrCopyToChar(p->applyDate     ,result[i++],sizeof(p->applyDate     ));
	StrCopyToChar(p->applyTransDate,result[i++],sizeof(p->applyTransDate));
	StrCopyToChar(p->memberID      ,result[i++],sizeof(p->memberID      ));
	StrCopyToChar(p->localNo       ,result[i++],sizeof(p->localNo       ));

}
void CGtpArray::Get0x00A00212(T0x00A00212 *p ,std::string buff)
{
	vector<std::string> result;
	result = strutils::explodeGTP('|',buff);
	int i = 0;
	StrCopyToChar(p->pickupSheetNo,result[i++],sizeof(p->pickupSheetNo));
	StrCopyToChar(p->memberID     ,result[i++],sizeof(p->memberID     ));

}
void CGtpArray::Get0x00A00222(T0x00A00222 *p ,std::string buff)
{
	vector<std::string> result;
	result = strutils::explodeGTP('|',buff);
	int i = 0;
	StrCopyToChar(p->SheetNo        ,result[i++],sizeof(p->SheetNo        ));
	StrCopyToChar(p->localNo        ,result[i++],sizeof(p->localNo        ));
	StrCopyToChar(p->memberID       ,result[i++],sizeof(p->memberID       ));
	StrCopyToChar(p->clientID       ,result[i++],sizeof(p->clientID       ));
	StrCopyToChar(p->warehouseID    ,result[i++],sizeof(p->warehouseID    ));
	StrCopyToChar(p->pickupPerson   ,result[i++],sizeof(p->pickupPerson   ));
	StrCopyToChar(p->cipher         ,result[i++],sizeof(p->cipher         ));
	p->certificateType = result[i++].c_str()[0];
	StrCopyToChar(p->certificateNo  ,result[i++],sizeof(p->certificateNo  ));
	StrCopyToChar(p->applyDate      ,result[i++],sizeof(p->applyDate      ));
	StrCopyToChar(p->beginDate      ,result[i++],sizeof(p->beginDate      ));
	StrCopyToChar(p->endDate        ,result[i++],sizeof(p->endDate        ));
	StrCopyToChar(p->applyTransDate ,result[i++],sizeof(p->applyTransDate ));
	StrCopyToChar(p->traderID       ,result[i++],sizeof(p->traderID       ));
	p->stdDrawWeight = FromString<double>(result[i++]);
	StrCopyToChar(p->varietyID      ,result[i++],sizeof(p->varietyID      ));
	p->selfDrawWeight = FromString<double>(result[i++]);
	p->tradeDrawWeight = FromString<double>(result[i++]);
	p->drawType = result[i++].c_str()[0];
	StrCopyToChar(p->leaseRegNo     ,result[i++],sizeof(p->leaseRegNo     ));

}
void CGtpArray::Get0x00A00223(T0x00A00223 *p ,std::string buff)
{
	vector<std::string> result;
	result = strutils::explodeGTP('|',buff);
	int i = 0;
	StrCopyToChar(p->memberID  ,result[i++],sizeof(p->memberID  ));
	StrCopyToChar(p->effectDate,result[i++],sizeof(p->effectDate));
	StrCopyToChar(p->seqNo     ,result[i++],sizeof(p->seqNo     ));
	StrCopyToChar(p->clientID  ,result[i++],sizeof(p->clientID  ));
	StrCopyToChar(p->SheetNo   ,result[i++],sizeof(p->SheetNo   ));
	StrCopyToChar(p->appSheetNo,result[i++],sizeof(p->appSheetNo));
	StrCopyToChar(p->localNo   ,result[i++],sizeof(p->localNo   ));
	StrCopyToChar(p->stgOptType,result[i++],sizeof(p->stgOptType));
	p->appState = result[i].c_str()[0];
}