#pragma once

// CTCSocket 命令目标
#include "TestChartDlg.h"

class CTCSocket : public CAsyncSocket
{
public:
	CTCSocket();
	virtual ~CTCSocket();

	 virtual void OnReceive( int nErrorCode );

	 virtual void OnSend( int nErrorCode );

	 virtual void OnOutOfBandData(int nErrorCode);

	 virtual void OnClose( int nErrorCode );

	 virtual void OnConnect( int nErrorCode );
 
	 bool  Create();

	 bool  IsConnected();

	 virtual void setTestChartDlg(CTestChartDlg* pServerdlg);//

	 void  CloseConnect();
private:
 
    bool m_IsConnected;
    CTestChartDlg* m_pServerdlg;//回调窗体指针

};


