#pragma once


#pragma	pack(1)


//////////////////////////////////////////////////ʵʱ���ݶ���/////////////////////////////////////////////////
// ʵʱ����
struct HSStockRealTime
{
	long				m_lOpen;         		// ����
	long				m_lMaxPrice;     		// ��߼�
	long				m_lMinPrice;     		// ��ͼ�
	long				m_lNewPrice;     		// ���¼�
	unsigned long		m_lTotal;				// �ɽ���(��λ:��)
	float				m_fAvgPrice;			// �ɽ����

	long				m_lBuyPrice1;			// ��һ��
	unsigned long		m_lBuyCount1;			// ��һ��
	long				m_lBuyPrice2;			// �����
	unsigned long		m_lBuyCount2;			// �����
	long				m_lBuyPrice3;			// ������
	unsigned long		m_lBuyCount3;			// ������
	long				m_lBuyPrice4;			// ���ļ�
	unsigned long		m_lBuyCount4;			// ������
	long				m_lBuyPrice5;			// �����
	unsigned long		m_lBuyCount5;			// ������

	long				m_lSellPrice1;			// ��һ��
	unsigned long		m_lSellCount1;			// ��һ��
	long				m_lSellPrice2;			// ������
	unsigned long		m_lSellCount2;			// ������
	long				m_lSellPrice3;			// ������
	unsigned long		m_lSellCount3;			// ������
	long				m_lSellPrice4;			// ���ļ�
	unsigned long		m_lSellCount4;			// ������
	long				m_lSellPrice5;			// �����
	unsigned long		m_lSellCount5;			// ������

	long				m_nHand;				// ÿ�ֹ���	(�Ƿ�ɷ��������У���������
	long				m_lNationalDebtRatio;	// ��ծ����,����ֵ
};
// ԭ28*4 = 112

// ָ����ʵʱ����
struct HSIndexRealTime
{
	long		m_lOpen;				// ����
	long		m_lMaxPrice;			// ��߼�
	long		m_lMinPrice;			// ��ͼ�
	long		m_lNewPrice;			// ���¼�
	unsigned long		m_lTotal;				// �ɽ���
	float		m_fAvgPrice;			// �ɽ����

	short		m_nRiseCount;			// ���Ǽ���
	short		m_nFallCount;			// �µ�����
	long		m_nTotalStock1;			/* �����ۺ�ָ�������й�Ʊ - ָ��
										���ڷ���ָ���������Ʊ���� */
	unsigned long		m_lBuyCount;			// ί����
	unsigned long		m_lSellCount;			// ί����
	short		m_nType;				// ָ�����ࣺ0-�ۺ�ָ�� 1-A�� 2-B��
	short		m_nLead;            	// ����ָ��
	short		m_nRiseTrend;       	// ��������
	short		m_nFallTrend;       	// �µ�����
	short		m_nNo2[5];				// ����
	short		m_nTotalStock2;			/* �����ۺ�ָ����A�� + B��
										���ڷ���ָ����0 */
	long		m_lADL;					// ADL ָ��
	long		m_lNo3[3];				// ����
	long		m_nHand;				// ÿ�ֹ���	
};

// �۹�ʵʱ 29*4 = 116 ��  26*4 = 104���۱��short)
struct HSHKStockRealTime
{
	long		m_lOpen;         		// ����
	long		m_lMaxPrice;     		// ��߼�
	long		m_lMinPrice;     		// ��ͼ�
	long		m_lNewPrice;     		// ���¼�

	unsigned long		m_lTotal;				// �ɽ������ɣ�	
	float		m_fAvgPrice;			// �ɽ����(Ԫ)

	long		m_lBuyPrice;			// ���
	long		m_lSellPrice;			// ����
	union
	{
		long		m_lYield;		// ��Ϣ�� ��Ʊ���
		long		m_lOverFlowPrice;	// ���% �Ϲ�֤���
										// �Ϲ�֤����ۣ����Ϲ�֤�ּۡ��һ����ʣ���ʹ�ۣ�����ʲ��ּۣ�/����ʲ��ּۡ�100
										// �Ϲ�֤����ۣ����Ϲ�֤�ּۡ��һ����ʣ���ʹ�ۣ�����ʲ��ּۣ�/����ʲ��ּۡ�100

	};

	long		m_lBuyCount1;			// ��һ��
	long		m_lBuyCount2;			// �����
	long		m_lBuyCount3;			// ������
	long		m_lBuyCount4;			// ������
	long		m_lBuyCount5;			// ������

	long		m_lSellCount1;			// ��һ��
	long		m_lSellCount2;			// ������
	long		m_lSellCount3;			// ������
	long		m_lSellCount4;			// ������
	long		m_lSellCount5;			// ������

	unsigned short		m_lSellOrder1;	// ��һ����
	unsigned short		m_lSellOrder2;	// ��������
	unsigned short		m_lSellOrder3;	// ��������
	unsigned short		m_lSellOrder4;	// ��������
	unsigned short		m_lSellOrder5;	// ��������

	unsigned short		m_lBuyOrder1;	// ��һ����
	unsigned short		m_lBuyOrder2;	// �������
	unsigned short		m_lBuyOrder3;	// ��������
	unsigned short		m_lBuyOrder4;	// ��������
	unsigned short		m_lBuyOrder5;	// ��������

	long		m_lIEP;					// �ο�ƽ���
	long		m_lIEV;					// �ο�ƽ����

										// ���Ʒֱʵ�ǰ�ɽ��������ͣ�������
	long		m_lMatchType;			// ���̷���

};

// �۹���Ȩ
struct HSQQStockRealTime
{
	long				m_Month;				// ������,19990101

	char				m_Symbol[10];			// ���
	char				m_OptionType;			// ��Ȩ���ࣺ��P��(����)����C�������룩

	float				m_StrikePrice;		    // ��ʹ��

	float				m_lOpen;         		// ����
	float				m_lMaxPrice;     		// ��߼�
	float				m_lMinPrice;     		// ��ͼ�
	float				m_lNewPrice;     		// ���¼�

	float				m_lTotal;				// �ɽ������ɣ�	
	float				m_fAvgPrice;			// �ɽ����(Ԫ)

	float				m_lBuyPrice;			// ���
	float				m_lSellPrice;			// ����

	float				m_BidVol;				// ������
	float				m_AskVol;				// ������

	float				m_YClose;				// ǰ�����̼�

	char				m_cReserve[20];			// ����
};



// �ڻ�������ʵʱ����
struct HSQHRealTime
{
	long		m_lOpen;         	// ����
	long		m_lMaxPrice;     	// ��߼�
	long		m_lMinPrice;     	// ��ͼ�
	long		m_lNewPrice;     	// ���¼�

	unsigned long		m_lTotal;		   	// �ɽ���(��λ:��Լ��λ)
	long				m_lChiCangLiang;    // �ֲ���(��λ:��Լ��λ)

	long		m_lPreJieSuanPrice; // ������

									//long		m_nHand;				// ÿ�ֹ���
									//long 		m_lPreCloseChiCang;		// ��ֲ���(��λ:��Լ��λ)


	long		m_lJieSuanPrice;    // �ֽ����
	long		m_lCurrentCLOSE;	// ������
	long		m_lHIS_HIGH;		// ʷ���
	long		m_lHIS_LOW;	 		// ʷ���
	long		m_lUPPER_LIM;		// ��ͣ��
	long		m_lLOWER_LIM;		// ��ͣ��

	long		m_nHand;				// ÿ�ֹ���
	long 		m_lPreCloseChiCang;		// ��ֲ���(��λ:��Լ��λ)

	long 		m_lLongPositionOpen;	// ��ͷ��(��λ:��Լ��λ)
	long 		m_lLongPositionFlat;	// ��ͷƽ(��λ:��Լ��λ)
	long 		m_lNominalOpen;			// ��ͷ��(��λ:��Լ��λ)	
	long 		m_lNominalFlat;			// ��ͷƽ(��λ:��Լ��λ)

	long		m_lPreClose;			// ǰ������????
	long        m_lAvgPrice;            // �ɽ����  added by Ben 20100506

										// modified by Ben 20100506
	long				m_lBuyPrice1;			// ��һ��
	unsigned long		m_lBuyCount1;			// ��һ��
	long				m_lBuyPrice2;			// �����
	unsigned long		m_lBuyCount2;			// �����
	long				m_lBuyPrice3;			// ������
	unsigned long		m_lBuyCount3;			// ������
	long				m_lBuyPrice4;			// ���ļ�
	unsigned long		m_lBuyCount4;			// ������
	long				m_lBuyPrice5;			// �����
	unsigned long		m_lBuyCount5;			// ������

	long				m_lSellPrice1;			// ��һ��
	unsigned long		m_lSellCount1;			// ��һ��
	long				m_lSellPrice2;			// ������
	unsigned long		m_lSellCount2;			// ������
	long				m_lSellPrice3;			// ������
	unsigned long		m_lSellCount3;			// ������
	long				m_lSellPrice4;			// ���ļ�
	unsigned long		m_lSellCount4;			// ������
	long				m_lSellPrice5;			// �����
	unsigned long		m_lSellCount5;			// ������

};



// ���ʵʱ����
struct HSWHRealTime
{
	long		m_lOpen;         	// ����(1/10000Ԫ)
	long		m_lMaxPrice;     	// ��߼�(1/10000Ԫ)
	long		m_lMinPrice;     	// ��ͼ�(1/10000Ԫ)
	long		m_lNewPrice;     	// ���¼�(1/10000Ԫ)

	long		m_lBuyPrice;		// ���(1/10000Ԫ)
	long		m_lSellPrice;		// ����(1/10000Ԫ)

									//long		m_lPrevClose;	    // ��������
									//long		m_lPriceTimes;	    // ��������һ���Ӽ۸�仯����
};

//////////////////////////////////////////////////ʵʱ���ݶ���/////////////////////////////////////////////////






////////////////////////////////////////��ʷ��ʱ///////////////////////////////////////////////////

// ��ʷ��ʱ��������
struct StockHistoryTrendHead
{
	long				m_lDate;		// ����
	long				m_lPrevClose;	// ����

	union
	{
		HSStockRealTime			m_stStockData;		// ����ʵʱ��������
		HSIndexRealTime			m_stIndexData;		// ָ��ʵʱ��������
		HSHKStockRealTime		m_hkData;		// �۹�ʵʱ��������
		HSQHRealTime			m_qhData;		// �ڻ�ʵʱ��������
		HSWHRealTime			m_whData;		// ���ʵʱ��������
	};

	short			    m_nSize;		//  ÿ�������ܸ���
	short				m_nAlignment;   //  ������
};
//��ʷ��ʱ1��������
struct StockCompHistoryData
{
	long	        m_lNewPrice;		// ���¼�
	unsigned long	m_lTotal;			/* �ɽ��� //���ڹ�Ʊ(��λ:��)
										����ָ��(��λ:�ٹ�) */
	float	        m_fAvgPrice;		/*�ɽ���� */
	long	        m_lBuyCount;        // ί����
	long	        m_lSellCount;       // ί����

};





////////////////////////////////////////��ʷ��ʱ///////////////////////////////////////////////////





// �ڻ�����������ʵʱ����(����)
struct HSQHRealTime_Min
{
	long		m_lOpen;         	// ����
	long		m_lMaxPrice;     	// ��߼�
	long		m_lMinPrice;     	// ��ͼ�
	long		m_lNewPrice;     	// ���¼�

	unsigned long		m_lTotal;		   	// �ɽ���(��λ:��Լ��λ)
	long				m_lChiCangLiang;    // �ֲ���(��λ:��Լ��λ)

	long		m_lBuyPrice1;		// ��һ��
	long		m_lBuyCount1;		// ��һ��
	long		m_lSellPrice1;		// ��һ��
	long		m_lSellCount1;		// ��һ��

	long		m_lPreJieSuanPrice; // ������
};
// ʱʱ���ݷ���
union ShareRealTimeData
{
	HSStockRealTime			m_nowData;		// ����ʵʱ��������
	HSStockRealTime			m_stStockData;

	HSIndexRealTime			m_indData;		// ָ��ʵʱ��������
	HSHKStockRealTime		m_hkData;		// �۹�ʵʱ��������
	HSQHRealTime			m_qhData;		// �ڻ�ʵʱ��������
	HSWHRealTime			m_whData;		// ���ʵʱ��������	

	HSQHRealTime_Min		m_qhMin;
};

// ��ʷ��ʱͷ����
struct DiskStockHistoryTendHead
{
	long				m_lDate;		// ����
	long				m_lPrevClose;	// ����

	ShareRealTimeData   m_stStockData;

	short			    m_nSize;		//  ÿ�������ܸ���
										//short				m_nAlignment;   //  ������
};

