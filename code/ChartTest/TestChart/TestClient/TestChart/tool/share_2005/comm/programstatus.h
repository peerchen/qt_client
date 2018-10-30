
#ifndef programstatus_h
#define programstatus_h

#pragma	pack(1)

// 当前流量计数
struct CurCommflux
{
	long m_nRecieve;  // 接收总数
	long m_nSend;	  // 发送总数

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
	long m_lDiskSize;		// 硬盘大小
};


struct HS_EverySever
{
	long m_lCpu;			// cpu

	long m_lCurConnect;		// 当前连接数

	long m_lMemTotal;		// 总内存
	long m_lMemVar;			// 可用内存	
};

struct HS_PacketStatus
{
	double	m_dPacketCounts;		// 队列里等待发送的数据包总数
	double	m_dQuitCounts;			// 放弃(没有发送)的数据包总数

	double	m_dSendPacketCounts;	// 总发送包数

	double  m_dFenshiPacket;		// 分时数据包
	double  m_dDayPacket;			// 日线数据包
	double  m_dSortPacket61;		// 61~66排名数据包
	double  m_dSortPacket81;		// 81~86排名数据包
	double  m_dInfoPacket;			// 资料数据包
	double  m_dPricePacket;			// 报价数据包
	double  m_dEveryPacket;			// 主推数据包


	void Empty()
	{
		memset(this,0,sizeof(HS_PacketStatus));
	}
};

struct HS_EveryTimeData
{
	long m_lTime;  // CTime 当前时间

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

		char m_lreserve[100];    // 保留
	};

	char m_szError[50];    // 错误信息
};

#pragma	pack()

#endif

