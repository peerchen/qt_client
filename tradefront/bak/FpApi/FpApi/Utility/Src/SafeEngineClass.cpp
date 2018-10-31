#include "SafeEngineClass.h"


SafeEngineClass *SafeEngineClass::m_instance = NULL;

SafeEngineClass *SafeEngineClass::GetInstance()
{
	if( m_instance == NULL )
	{
		m_instance = new SafeEngineClass;
	}
	return m_instance;
}
void SafeEngineClass::ReleaseInstance()
{
	if( m_instance != NULL )
	{
		delete m_instance;
		m_instance = NULL;
	}
}

SafeEngineClass::SafeEngineClass(void)
:m_SafeEngineDll(NULL)
,m_HSE(NULL)
,m_PublicKeyLen(0)
,m_CertLen(0)
,m_Init(false)
,SEH_InitialSession(NULL)
,SEH_ClearSession(NULL)
,SEH_SignData(NULL)
,SEH_VerifySignData(NULL)
,SEH_GetSelfCertificate(NULL)
,SafeEngine_GetCertDetail(NULL)
,SEH_AsynEncryptDataByPubkey(NULL)
,SEH_AsynDecryptDataByPrikey(NULL)
{
	memset( m_Cert,      0, sizeof( m_Cert ) );
	memset( m_PublicKey, 0, sizeof( m_PublicKey ) );
}

SafeEngineClass::~SafeEngineClass(void)
{	
	ClearDll();
}

int SafeEngineClass::Init( char *cert_chain, char *private_key, char *private_password, char *public_cert )
{
	unsigned char  cert[2048];
	unsigned short certlen = 2048;


	if( InitDll() < 0 )
	{
		ClearDll();
		return -1;
	}

	long ret = SEH_InitialSession(&m_HSE, 2, private_key, private_password, 0, 2, cert_chain, "");

	if( ret != 0 )
	{
		ClearDll();
		printf( "SEH_InitialSession Error %d", ret );
		return ret;
	}

	m_CertLen = sizeof( m_Cert );
	ret = SEH_GetSelfCertificate(m_HSE, 2, public_cert, "", m_Cert, &m_CertLen);
	if( ret != 0 )
	{
		ClearDll();
		printf( "SEH_GetSelfCertificate Error %d\n", ret );
		return ret;
	}

	m_PublicKeyLen = sizeof( m_PublicKey );
	ret = SafeEngine_GetCertDetail(m_HSE, m_Cert, m_CertLen, 20, m_PublicKey, &m_PublicKeyLen);
	if( ret != 0 )
	{
		ClearDll();
		printf( "SafeEngine_GetCertDetail Error %d", ret );
		return ret;
	}

	m_Init = true;
	return 0;
}

int SafeEngineClass::EncryptDataByPubkey( unsigned char *data, int len, unsigned char *encode_data, int *encode_datalen )
{
	if( m_Init == false || SEH_AsynDecryptDataByPrikey == NULL )
		return -1;

	int ret         = 0;
	int size        = m_PublicKeyLen/128*128;
	int total_size  = (*encode_datalen);
	int encode_size = 0;

	unsigned char * point_date        = new unsigned char[(len/128+1)*128];
	unsigned char * point_encode_date = encode_data;
	
	memset( point_date, 0, (len/128+1)*128 );
	memcpy( point_date, data, len );

	(*encode_datalen) = 0;
	while( (*encode_datalen) < len )
	{
		encode_size = total_size - (*encode_datalen);
		ret = SEH_AsynEncryptDataByPubkey( m_HSE, point_date, size, point_encode_date, &encode_size, m_PublicKey, m_PublicKeyLen );
		if( ret != 0 )
		{
			size = 100;
			ret = SEH_AsynEncryptDataByPubkey( m_HSE, point_date, size, point_encode_date, &encode_size, m_PublicKey, m_PublicKeyLen );
			if( ret != 0 )
			{
				//ClearDll();
				return ret;
			}
		}

		point_date        += size;
		point_encode_date += encode_size;
		(*encode_datalen) += encode_size;
	}
	return ret;
}
int SafeEngineClass::DecryptDataByPrikey( unsigned char *data, int len, unsigned char *decode_data, int *decode_datalen )
{
	if( m_Init == false || SEH_AsynDecryptDataByPrikey == NULL )
		return -1;


	int ret;
	int size        = m_PublicKeyLen/128*128;
	int decode_size = 0;

	unsigned char * point_date        = data;
	unsigned char * point_decode_date = decode_data;

	while( point_date < data + len )
	{
		ret = SEH_AsynDecryptDataByPrikey( m_HSE, point_date, size, point_decode_date, &decode_size  );
		if( ret != 0 )
		{
			//ClearDll();
			return ret;
		}
		point_date        += size;
		point_decode_date += decode_size;
	}
	(*decode_datalen) = strlen( (char *)decode_data );
	return ret;
}

int SafeEngineClass::GetCert( unsigned char *cert, unsigned short *cert_len  )
{
	if( m_Init == false )
		return -1;

	memcpy( cert, m_Cert, m_CertLen );
	(*cert_len) = m_CertLen;
	return 0;
}

int SafeEngineClass::Sign( unsigned char *data, int len, unsigned short way, unsigned char *sign_data, unsigned long *sign_datalen )
{
	if( m_Init == false || SEH_SignData == NULL )
		return -1;

	int ret = SEH_SignData( m_HSE, data, len, way, sign_data, sign_datalen);
	if( ret != 0 )
	{
		//ClearDll();
		return ret;
	}
	return ret;
}


int SafeEngineClass::VerifySign( unsigned char *data, int len, unsigned short way, unsigned char *sign_data, int sign_datalen, unsigned char *cert, unsigned short cert_len )
{
	if( m_Init == false  || SEH_VerifySignData == NULL )
		return -1;

	int ret = SEH_VerifySignData( m_HSE, data, len, way, sign_data, sign_datalen,cert,cert_len );
	if( ret != 0 )
	{
		//ClearDll();
		return ret;
	}
	return ret;
}

int SafeEngineClass::InitDll()
{

	if( ( m_SafeEngineDll = loadlibrary(SAFEENGINE_DLL_NAME)) == NULL)
	{
		printf("Load library error.\n");
		ClearDll();
		return -1;
	}
	if( (SEH_InitialSession=(SEH_InitialSessionProc)getprocaddress(m_SafeEngineDll, ("SEH_InitialSession"))) == NULL)
	{
		printf("Load library error.SEH_InitialSession\n");
		ClearDll();
		return -1;
	}
	if( (SEH_ClearSession=(SEH_ClearSessionProc)getprocaddress(m_SafeEngineDll, ("SEH_ClearSession"))) == NULL)
	{
		printf("Load library error.SEH_ClearSession\n");
		ClearDll();
		return -1;
	}
	if( (SEH_SignData=(SEH_SignDataProc)getprocaddress(m_SafeEngineDll, ("SEH_SignData"))) == NULL)
	{
		printf("Load library error.SEH_SignData\n");
		ClearDll();
		return -1;
	}
	if( (SEH_VerifySignData=(SEH_VerifySignDataProc)getprocaddress(m_SafeEngineDll, ("SEH_VerifySignData"))) == NULL)
	{
		printf("Load library error.SEH_VerifySignData\n");
		ClearDll();
		return -1;
	}
	if( (SEH_GetSelfCertificate=(SEH_GetSelfCertificateProc)getprocaddress(m_SafeEngineDll, ("SEH_GetSelfCertificate"))) == NULL)
	{
		printf("Load library error.SEH_GetSelfCertificate\n");
		ClearDll();
		return -1;
	}
	if( (SafeEngine_GetCertDetail=(SEH_GetCertDetailProc)getprocaddress(m_SafeEngineDll, ("SEH_GetCertDetail"))) == NULL)
	{
		printf("Load library error.SafeEngine_GetCertDetail\n");
		ClearDll();
		return -1;
	}
	if( (SEH_AsynEncryptDataByPubkey=(SEH_AsynEncryptDataByPubkeyProc)getprocaddress(m_SafeEngineDll, ("SEH_AsynEncryptDataByPubkey"))) == NULL)
	{
		printf("Load library error.SEH_AsynEncryptDataByPubkey\n");
		ClearDll();
		return -1;
	}
	if( (SEH_AsynDecryptDataByPrikey=(SEH_AsynDecryptDataByPrikeyProc)getprocaddress(m_SafeEngineDll, ("SEH_AsynDecryptDataByPrikey"))) == NULL)
	{
		printf("Load library error.SEH_AsynDecryptDataByPrikey\n");
		ClearDll();
		return -1;
	}
	return 0;
}


void SafeEngineClass::ClearDll()
{

	if( m_HSE != NULL )
	{
		SEH_ClearSession( m_HSE );
		m_HSE = NULL;
	}

	if( m_SafeEngineDll != NULL )
	{
		freelibrary( m_SafeEngineDll );
		m_SafeEngineDll = NULL;
		SEH_InitialSession          = NULL;
		SEH_ClearSession            = NULL;
		SEH_SignData                = NULL;
		SEH_VerifySignData          = NULL;
		SEH_GetSelfCertificate      = NULL;
		SafeEngine_GetCertDetail    = NULL;
		SEH_AsynEncryptDataByPubkey = NULL;
		SEH_AsynDecryptDataByPrikey = NULL;
	}

	m_Init = false;
}