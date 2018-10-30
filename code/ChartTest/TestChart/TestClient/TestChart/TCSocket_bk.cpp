// TCSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestChart.h"
#include "TCSocket.h"



// CTCSocket

CTCSocket::CTCSocket()
{
	m_pServerdlg =NULL;
	m_IsConnected = false;
}

CTCSocket::~CTCSocket()
{
	m_pServerdlg =NULL;
}


// CTCSocket ��Ա����
 void CTCSocket::OnReceive( int nErrorCode )
 {
	 if(NULL != m_pServerdlg)
	 {
		 m_pServerdlg->OnReceive(nErrorCode);
	 }
 }

 void CTCSocket::OnSend( int nErrorCode )
 {
	  if(NULL != m_pServerdlg)
	 {
		 m_pServerdlg->OnSend(nErrorCode);
	 }
 }

 void CTCSocket::OnOutOfBandData(int nErrorCode)
 {
	 /* if(NULL != m_pServerdlg)
	 {
		 m_pServerdlg->OnOutOfBandData(nErrorCode);
	 }*/
 }

 void CTCSocket::CloseConnect()
 {
	m_IsConnected = false;
	ShutDown(2);
	Close();
	m_hSocket   = INVALID_SOCKET;

 }

 void CTCSocket::OnClose( int nErrorCode )
 {
	 m_IsConnected = false;
	  if(NULL != m_pServerdlg)
	 {
		 m_pServerdlg->OnClose(nErrorCode);
	 }
 }

 void CTCSocket::OnConnect( int nErrorCode )
 {
	 m_IsConnected = true;
	  if(NULL != m_pServerdlg)
	 {
		 m_pServerdlg->OnConnect(nErrorCode);
	 }
 }

 bool  CTCSocket::Create()
  {
	  if(!m_IsConnected)
	  {
		  	if(CAsyncSocket::Create(0, SOCK_STREAM, FD_CONNECT | FD_CLOSE | FD_READ | FD_WRITE) != TRUE)
			{
				return false;
			}
	  }

	  //send������Ϊ0����������  kenny 20171011
	  //�������ݰ�Ĭ������Nagle�㷨��Ҫ�������͵Ļ������÷��ͻ���������ֹ�ӳ�����
	  int nZero = 0;
	  int bValue = 1*1024*1024;
	  CAsyncSocket::SetSockOpt(SO_SNDBUF,(const void *)&nZero,(int)(sizeof(nZero)), SOL_SOCKET);
	 // CAsyncSocket::SetSockOpt(TCP_NODELAY, (const void *)&bValue, (int)sizeof(BOOL), IPPROTO_TCP);

	  return  true;
  }

  bool  CTCSocket::IsConnected()
  {
	  return m_IsConnected;
  }

 void CTCSocket::setTestChartDlg(CTestChartDlg* pServerdlg)
 {
	 m_pServerdlg = pServerdlg;
 }