#ifndef __SAFE_ENGINE_CLASS_H__
#define __SAFE_ENGINE_CLASS_H__

#include "SafeEngine.h"

#ifdef _WINDOWS
	#define handle        HINSTANCE
	#define loadlibrary( dll_file )                LoadLibrary( dll_file )
	#define freelibrary( dll_handle )              FreeLibrary( dll_handle )
	#define getprocaddress( dll_handle, funcname ) GetProcAddress( dll_handle, funcname )
#else
	#include <dlfcn.h>
	#include <string.h>
	#define handle      void *
	#define loadlibrary( dll_file )                dlopen( dll_file, RTLD_NOW )
	#define freelibrary( dll_handle )              dlclose( dll_handle )
	#define getprocaddress( dll_handle, funcname ) dlsym( dll_handle, funcname )
#endif

class SafeEngineClass
{
private:
	SafeEngineClass(void);
	~SafeEngineClass(void);
public:
	static SafeEngineClass *GetInstance();
	static void ReleaseInstance();
public:
	int Init( char *cert_chain, char *private_key, char *private_password, char *public_cert );
	int EncryptDataByPubkey( unsigned char *data, int len, unsigned char *encode_data, int *encode_datalen );
	int DecryptDataByPrikey( unsigned char *data, int len, unsigned char *decode_data, int *decode_datalen );
	int GetCert( unsigned char *cert, unsigned short *cert_len  );
	int Sign( unsigned char *data, int len, unsigned short way, unsigned char *sign_data, unsigned long *sign_datalen );
	int VerifySign( unsigned char *data, int len, unsigned short way, unsigned char *sign_data, int sign_datalen, unsigned char *cert, unsigned short cert_len );
private:
	int InitDll();
	void ClearDll();
public:
	handle m_SafeEngineDll;
	HSE    m_HSE;

	unsigned char  m_Cert[2048];
	unsigned short m_CertLen;
	unsigned char  m_PublicKey[2048];
	unsigned short m_PublicKeyLen;

	bool m_Init;
private:
	static SafeEngineClass *m_instance;

private:
	typedef long(*SEH_InitialSessionProc)(HSE *hSE, unsigned long privatekeydevicetype,  char *privatekeydeviceparameter, char *privatekeypassword,  unsigned long privatekeytimeout,  unsigned long certchaindevicetype,  char *certchaindeviceparameter,  char *certchainpassword );
	typedef long(*SEH_ClearSessionProc)(HSE hSE);
	typedef long(*SEH_SignDataProc)(HSE hSE, unsigned char *origindata, unsigned long length, unsigned short signmethod, unsigned char *signeddata, unsigned long *signedlength);
	typedef long(*SEH_VerifySignDataProc)(HSE hSE, unsigned char *origindata, unsigned long originlength, unsigned short signmethod, unsigned char *signeddata, unsigned long signedlength, unsigned char *certificate, unsigned short certlength);
	typedef long(*SEH_GetSelfCertificateProc)(HSE hSE, unsigned long devicetype, char *deviceparameter, char *password, unsigned char *certificate, unsigned short *certificatelength);
	typedef long(*SEH_GetCertDetailProc)(HSE hSE, unsigned char *DerCert, unsigned short DerCertLen, unsigned short ItemNo, unsigned char *ItemValue, unsigned short *ItemLength);
	typedef long(*SEH_AsynEncryptDataByPubkeyProc)(HSE hSE, unsigned char *indata, int indatalen, unsigned char *outdata, int *outdatalen, unsigned char *Pubkey, int PubkeyLen);
	typedef long(*SEH_AsynDecryptDataByPrikeyProc)(HSE hSE, unsigned char *indata, int indatalen, unsigned char *outdata, int *outdatalen);

	SEH_InitialSessionProc            SEH_InitialSession;
	SEH_ClearSessionProc              SEH_ClearSession;
	SEH_SignDataProc                  SEH_SignData;
	SEH_VerifySignDataProc            SEH_VerifySignData;
	SEH_GetSelfCertificateProc        SEH_GetSelfCertificate;
	SEH_GetCertDetailProc             SafeEngine_GetCertDetail;
	SEH_AsynEncryptDataByPubkeyProc   SEH_AsynEncryptDataByPubkey;
	SEH_AsynDecryptDataByPrikeyProc   SEH_AsynDecryptDataByPrikey;
};

#endif