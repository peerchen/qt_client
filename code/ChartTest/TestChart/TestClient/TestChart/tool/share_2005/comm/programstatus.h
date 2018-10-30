
#ifndef programstatus_h
#define programstatus_h

#pragma	pack(1)

// ��ǰ��������
struct CurCommflux
{
	long m_nRecieve;  // ��������
	long m_nSend;	  // ��������

	void Empty()
	{
		m_nRecieve = 0;
		m_nSend = 0;
	}
};

struct HS_EverySend
{
	long m_lCpu;			// cpu
};


struct HS_EveryReciev
{
	long m_lDiskSize;		// Ӳ�̴�С
};


struct HS_EverySever
{
	long m_lCpu;			// cpu

	long m_lCurConnect;		// ��ǰ������

	long m_lMemTotal;		// ���ڴ�
	long m_lMemVar;			// �����ڴ�	
};

struct HS_PacketStatus
{
	double	m_dPacketCounts;		// ������ȴ����͵����ݰ�����
	double	m_dQuitCounts;			// ����(û�з���)�����ݰ�����

	double	m_dSendPacketCounts;	// �ܷ��Ͱ���

	double  m_dFenshiPacket;		// ��ʱ���ݰ�
	double  m_dDayPacket;			// �������ݰ�
	double  m_dSortPacket61;		// 61~66�������ݰ�
	double  m_dSortPacket81;		// 81~86�������ݰ�
	double  m_dInfoPacket;			// �������ݰ�
	double  m_dPricePacket;			// �������ݰ�
	double  m_dEveryPacket;			// �������ݰ�


	void Empty()
	{
		memset(this,0,sizeof(HS_PacketStatus));
	}
};

struct HS_EveryTimeData
{
	long m_lTime;  // CTime ��ǰʱ��

	union
	{
		HS_EverySend	m_send;
		HS_EveryReciev	m_rec;
		HS_EverySever   m_srv;
	};

	CurCommflux m_sFlux;

	union
	{
		HS_PacketStatus m_packet;

		char m_lreserve[100];    // ����
	};

	char m_szError[50];    // ������Ϣ
};

#pragma	pack()

#endif

