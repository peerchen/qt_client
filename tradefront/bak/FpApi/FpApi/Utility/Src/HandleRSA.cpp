#include "HandleRSA.h"

#include <openssl/ossl_typ.h>
#include <openssl/pkcs12.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <iostream>
using namespace std;
string CHandleRSA::m_sCrtPwd = "";
int CHandleRSA::HandleRsaEncrypt( char *&pEncryptBuf, 
							 unsigned int &uiEncryptLen, 
							 const char* pOrgBuf,      // 
							 unsigned int uiOrgLen, // uiOrgLen
							 const string &csCertFilePath )
{
	BIO      *in           = NULL;//从文件读取信息(公钥私钥等)
	X509     *x509Pem      = NULL;//
	EVP_PKEY * pKeyPem = NULL;
	//char tempkey[7] = "123412";
	PKCS12 * p12 = NULL;
	STACK_OF(X509) *ca =NULL;	
	if ((in = BIO_new_file (csCertFilePath.c_str(), "r")) == 0)
	{
		return -1;
	}
	OpenSSL_add_all_algorithms();
	p12 = d2i_PKCS12_bio(in,NULL);
	BIO_free(in);
	PKCS12_parse(p12,m_sCrtPwd.c_str(),&pKeyPem,&x509Pem,&ca);
	if (pKeyPem == 0) 
	{
		if (x509Pem) 
		{
			X509_free(x509Pem);
		}
		return -1;
	}
	else if (pKeyPem->pkey.rsa == 0)
	{
		if (x509Pem) 
		{
			X509_free(x509Pem);
		}
		return -1;
	}

	const char * pData = pOrgBuf;

	// 分配存储密文的缓存区
	unsigned int uiTotalSize = (uiOrgLen/128 + 2) * 128;
	pEncryptBuf = new char[uiTotalSize];
	memset(pEncryptBuf, 0, uiTotalSize);

	// 分配用来存储一段加密的临时缓冲区
	unsigned int nRsaSize = RSA_size(pKeyPem->pkey.rsa); // 获得临时缓存区的长度
	unsigned char* pEncrpted = new unsigned char[nRsaSize];
	unsigned char ** ppE = &pEncrpted;
	int nInLen = 0;  // 需要加密的段的长度
	uiEncryptLen = 0; // 加密缓冲区的已经加密的长度
	for (size_t n = 128; n - 128 < uiOrgLen; n += 128)
	{
		// 获得这次加密的明文的长度（一般为100，除了最后一段）
		nInLen = uiOrgLen / n == 0 ? uiOrgLen - (n - 128) : 128;

		// 给这段明文加密到pEncrpted缓冲区，并获得加密后的实际长度
		int nTmp = RSA_private_decrypt(nInLen,(unsigned char*)pData,pEncrpted,pKeyPem->pkey.rsa,RSA_PKCS1_PADDING);

		// 复制加密后的密文到加密缓存区
		memcpy(pEncryptBuf + uiEncryptLen, pEncrpted, nTmp);

		// 获得加密缓冲区的下一次加密的起始位置
		uiEncryptLen += nTmp;

		// 更新未加密的明文的起始位置
		pData += nInLen;
	}

	if (x509Pem) 
	{
		X509_free(x509Pem);
	}

	delete []pEncrpted;

	return 0;
}

void CHandleRSA::SetCrtPwd(string pwd)
{
	m_sCrtPwd = pwd;
}

int CHandleRSA::HandleRsaPublicEncrypt(char *&pEncryptBuf, unsigned int &uiEncryptLen, const char* pOrgBuf, unsigned int uiOrgLen, const string &csCertFilePath)
{
	BIO *in = NULL;
	EVP_PKEY * pKeyPem = NULL;
	X509 *x509Pem = NULL;
	PKCS12 * p12 = NULL;
	STACK_OF(X509) *ca =NULL;
	if ((in = BIO_new_file (csCertFilePath.c_str(), "r")) == 0)
	{
		return -1;
	}
	x509Pem = d2i_X509_bio (in, NULL);

	//d2i_RSA_PUBKEY_fp( fopen(csCertFilePath.c_str(), "r"),  )
	pKeyPem = X509_get_pubkey(x509Pem);

	if (pKeyPem == 0) 
	{
		if (x509Pem) 
		{
			X509_free(x509Pem);
		}
		return -1;
	}
	else if (pKeyPem->pkey.rsa == 0)
	{
		if (x509Pem) 
		{
			X509_free(x509Pem);
		}
		return -1;
	}

	const char * pData = pOrgBuf;

	// 分配存储密文的缓存区
	unsigned int uiTotalSize = (uiOrgLen/100 + 2) * 128;
	pEncryptBuf = new char[uiTotalSize];
	memset(pEncryptBuf, 0, uiTotalSize);

	// 分配用来存储一段加密的临时缓冲区
	unsigned int nRsaSize = RSA_size(pKeyPem->pkey.rsa); // 获得临时缓存区的长度
	unsigned char* pEncrpted = new unsigned char[nRsaSize];
	unsigned char ** ppE = &pEncrpted;
	int nInLen = 0;  // 需要加密的段的长度
	uiEncryptLen = 0; // 加密缓冲区的已经加密的长度
	for (size_t n = 100; n - 100 < uiOrgLen; n += 100)
	{
		// 获得这次加密的明文的长度（一般为100，除了最后一段）
		nInLen = uiOrgLen / n == 0 ? uiOrgLen - (n - 100) : 100;

		// 给这段明文加密到pEncrpted缓冲区，并获得加密后的实际长度
		int	nTmp = RSA_public_encrypt(nInLen,(unsigned char*)pData,pEncrpted,pKeyPem->pkey.rsa,RSA_PKCS1_PADDING );

		// 复制加密后的密文到加密缓存区
		memcpy(pEncryptBuf + uiEncryptLen, pEncrpted, nTmp);

		// 获得加密缓冲区的下一次加密的起始位置
		uiEncryptLen += nTmp;

		// 更新未加密的明文的起始位置
		pData += nInLen;
	}

	if (x509Pem) 
	{
		X509_free(x509Pem);
	}

	delete []pEncrpted;

	return 0;

}
