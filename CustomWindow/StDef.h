#ifndef _STDEF_H
#define _STDEF_H


#include <QString>
#include <list>
using namespace std;

struct VarietyInfo
{
	QString       variety_id           ; // ����Ʒ�ִ���    
	QString       name                 ; // ����Ʒ��ȫ��            
	QString       abbr                 ; // ���                    
	QString       variety_type         ; // Ʒ�����    
	double       min_pickup           ; // ��С�������        
	double       pickup_base          ; // �������        
	QString       weight_unit          ; // ������λ        
	QString       destroy_flag         ; // ע����־ 
};

struct MyCodeInfo
{
	QString       code_type            ; //�������    
	QString       code_id              ; //������    
	QString       code_desc            ; //��������  

	MyCodeInfo(){}

	MyCodeInfo( const QString &sCode_type, const QString &sCode_id,  const QString &sCode_desc) : code_type(sCode_type),code_id(sCode_id),code_desc(sCode_desc){}
};

//
struct ProdCodeInfo
{
	QString       prod_code            ; //��Լ����    
	QString       prod_name            ; //��Լ����    
	QString       variety_type         ; //Ʒ�����    
	QString       variety_id           ; //Ʒ�ִ���    
	double       tick                 ; //��С�䶯��λ    
	double       upper_limit_value    ; //��ͣ����    
	double       lower_limit_value    ; //��ͣ����    
	QString       active_flag          ; //��Ծ��־    
	QString       exch_unit            ; //���׵�λ    
	double       measure_unit         ; //������λ    
	QString       market_id            ; //�����г�   
};

struct StoreInfo
{
	int iAllAmt;
	int iUseFulAmt;
	int iCanGetAmt;
	int iTodayIn;
	int iTodayOut;
	int iExchFreeze;
	int iTihuoFreeze;
	int iUnitCost;

	StoreInfo()
	{
		iAllAmt = 0;
		iUseFulAmt = 0;
		iCanGetAmt = 0;
		iTodayIn = 0;
		iTodayOut = 0;
		iExchFreeze = 0;
		iTihuoFreeze = 0;
		iUnitCost = 0;
	}
};

struct DeferMatchSimple
{
	QString sLocalOrderNo;
	double dPosiMoney;
	double dPrice;
	int iHand; // ʣ�������
	int iTotalHand; // �ܵ����������ɽ�������

	DeferMatchSimple()
	{
		dPosiMoney = 0.00;
		iTotalHand = 1;
	}
};

typedef list<DeferMatchSimple> LISTDeferMatch;

struct DeferPosiInfo
{
	int iCurrAllAmt;     // �ֲܳ�
	int iYesAmt;         // ���
	int iTodayAmt;       // ���
	int iUsefulAmt;      // ���ò�

	double fYesAvgPosPrice; // ���ճֲ־���

	double dAvgPosPrice;     // �ܵĳֲ־���
	double dAvgOpenPosPrice; // �ܵĿ��־���
	double dPosi_PL;         // �ֲ�ӯ��
	double dTotalFare;       // �ֱֲ�֤��

    double dSvrAvgPosPrice;  // ����˳ֲ־���
    double dSvrAvgOpenPosPrice; // ����˿��־���

	LISTDeferMatch listMatch; // �ɽ��б�

	double dYesPosiMoney;
	int iYesOrgAmt;
	double dYesAvgOpenPosPrice; // ���տ��־���

	DeferPosiInfo()
	{
		iCurrAllAmt = 0;
		iYesAmt = 0;
		iTodayAmt = 0;
		iUsefulAmt = 0;

		fYesAvgPosPrice = 0.00;
		dAvgOpenPosPrice = 0.00;
		dAvgPosPrice = 0.00;
		dPosi_PL = 0.00;
		dTotalFare = 0.00;

		iYesOrgAmt = 0;
		dYesPosiMoney = 0.00;
	}
};

struct DeferPosi
{
	QString sProdCode;
	unsigned int uiLastPrice; // ��һ����������ӯ���ļ۸�
	double dUnite; // 

	DeferPosiInfo infoLong;//��
	DeferPosiInfo infoShort;//��

	DeferPosi()
	{	
		uiLastPrice = 0;
		dUnite = 0.00;
	}
};

// ����ƽ���������
struct PCSSPara 
{
	QString csProdCode;
	QString sBS;
	QString csPrice;
	QString csHand;
};

namespace AutoMode
{

}

#endif