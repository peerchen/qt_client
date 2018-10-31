// CWebUpdate.h : header file
//

#ifndef _CWEBUPDATE_H
#define _CWEBUPDATE_H

#include "XmlDocument.h"
#define WM_MAILNEWS WM_USER + 500 
#include "winsock2.h"
#include <afxinet.h>

#include <vector>
using namespace std;

struct UpdateFileStru
{
	CString strFileName; // �ļ��������Ǹ�Ŀ¼�Ļ�����·����
	CString strDate;     // ��������
};


class CWebUpdate
{
public:
	CWebUpdate();
	~CWebUpdate();
    
	// ���ݱ������������ļ�����ȡ���ӷ������������Ϣ�ͱ��ذ汾���Լ�������Ϣ
	void InitUpdate(); 
    // ����ͨ��Ini�ļ��ԱȰ汾�ţ������Ҫ���£������CheckUpdateFile��������ȡҪ���ص��ļ���Ϣ
	int CheckUpdate();
	// ͨ���Ա�xml�ļ��������Ҫ��������Ҫ���ص��ļ���Ϣ��ӵ����������xml�����طŵ�����ȥ�ˣ��е��ң���ʱ�������
	BOOL CheckUpdateFile();
	// ����һ���ļ����ƽ�һ���ļ����ص��������������������ļ�д�뵽��ʱĿ¼
	bool HttpDownloadFiles(CString strFileName);
	// ��һ���ļ����ص�����������HttpDownloadFiles��������
	BOOL ConnectServerFile(CString UpdateFile,CHttpConnection *pHttp = NULL);
	// �ӻ�����д�뵽��ʱĿ¼
	void  WriteBufferToTemp(const CString &strFileName);
	// ������xml����Ϣ���ص�Vector
	void LoadXMLToVec(vector<UpdateFileStru> &vecFile, CString &strFilePath);
	// ͨ���ȽϿͻ��˺ͷ���˵�xml�ļ�������Ҫ���ص��ļ�����Ϣ
	void GetDownLoadFile(const vector<UpdateFileStru> &vecClient, const vector<UpdateFileStru> &vecServer);
	// ͨ����ȡ���ص�ini�ļ�����ȡ���ذ汾��
	CString GetClientVersion(void);

private:
	// ���غͷ�����������Ϣ������
	DWORD m_dwType;
	CHttpFile* m_pFile;         // �����ļ�
	DWORD m_dwHttpRequestFlags; // http��������
	INTERNET_PORT m_dwPort;     // �˿ں�
	CString m_strServer;        // ������
	CString m_ServerPath;       // �������ļ�·��
	
	CInternetSession m_cis;
	CHttpConnection *m_pHttp;
	CString m_strServerByDomain;
	CString m_strStatus;

private:
	float m_fVersion;         // ���صİ汾��

	// ������Ϣ
	bool  m_bProxy;        // �Ƿ���Ҫ����
	char  m_cUserName[64]; // �����½���û���
	char  m_cPsw[64];      // �����½������     
	bool  m_bLogon;        // ��½����ʱ�Ƿ���Ҫ�û���������
public:
	CString m_strSerVersion;  // �������汾��
	vector<DLFileInfo> m_vecDLFiles; // Ҫ���ص��ļ����嵥

   
	
};

#endif
