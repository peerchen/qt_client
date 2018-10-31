#ifndef _HANDLE_RSA_H
#define _HANDLE_RSA_H
#include <string>
#include <string.h>
#include "Gess.h"
using namespace std;
class CHandleRSA
{
public:
	CHandleRSA();
	~CHandleRSA();
public:
	/*
	HandleRsaPrivateDecrypt HandleRsaPublicEncrypt 这两个函数成对使用，公钥加密，私钥解密。

	*/
	
	static int HandleRsaEncrypt(char *&pEncryptBuf, unsigned int &uiEncryptLen, const char* pOrgBuf, unsigned int uiOrgLen, const string &csCertFilePath);
	static int HandleRsaPublicEncrypt(char *&pEncryptBuf, unsigned int &uiEncryptLen, const char* pOrgBuf, unsigned int uiOrgLen, const string &csCertFilePath);
	static void SetCrtPwd(string pwd);

private:
	static string m_sCrtPwd;
};
#endif