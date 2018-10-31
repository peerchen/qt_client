
#include "Gess.h"

#include "Encode.h"

#include "Base643Des.h"
#include <openssl/evp.h>
#include <fstream>
#include <fcntl.h>
#define  BUFFER_SIZE (1024*3)

#define  FILE_IV_PLACE  (10)
#define  FILE_KEY_PLACE  (300)
#define  FILE_CIPHER_PLACE  (1024)

#define  SLEEP_TIME (0.1)
#ifndef _MAX_PATH
#define _MAX_PATH PATH_MAX
#endif
//static char chDesIV[9] = "12345678"; 

//using namespace OfferConst;

Base643Des::Base643Des()
{
}

Base643Des::~Base643Des()
{
}


string Base643Des::BuildRand(int nLen)
{
	srand((unsigned)time(NULL));
	string strKey ="";
	for(int n=0;n<nLen;n++)
	{
		char val  = 48 +(int) rand() %10;
		//strKey += val;
		strKey.append(&val,1);
	}
	//strKey += '\0';
	return strKey;
}

// 根据指定获取文件名获取3DES 明文Key及密钥密文
///fileName 文件名
///pIvData 向量
///pKeyData 密钥
///outBuffer 加密之后密文
int Base643Des::ReadFileKey(const char *fileName,char *pIvData,char *pKeyData,char *psrcData)
{
	char *data = new char[BUFFER_SIZE+1];
	memset(data,0,BUFFER_SIZE);

	ifstream pFile;
	pFile.open(fileName,ios::binary);
	if (!pFile.is_open())
	{
		return -1;
	}
	pFile.seekg(0,ios::beg);
	pFile.read(data,BUFFER_SIZE);
	
	int  nIvLength   = 0;
	int  nKeyLength  =0;
	int  nTextLength =0;

	char *ivData  = NULL;
	char *keyData = NULL;
	char *srcData = NULL;


	//打开隐藏密钥
	int j=0,z=0,n=0;
	for(int i=0;  i< BUFFER_SIZE;  ++i)
	{
		if ((i>= FILE_IV_PLACE) && (i%2 == 0) && (n <= nIvLength))
		{
			if (n==0)
			{
				nIvLength = data[i];
				ivData = new char[nIvLength+1];
			}
			else
				ivData[n-1] = data[i];
			++n;
		}
		if ((i>= FILE_KEY_PLACE) && (i%3 == 0) && (j<=nKeyLength))
		{
			if (j==0)
			{
				nKeyLength = data[i];
				keyData = new char[nKeyLength+1];
			}
			else
				keyData[j-1] = data[i];
			++j;
		}

		if ((i>= FILE_CIPHER_PLACE) && (i%2 == 0) && (z<=nTextLength))
		{
			if (z==0)
			{
				nTextLength = data[i];
				srcData  = new char[nTextLength+1];
			}
			else
				srcData[z-1] = data[i];
			++z;
		}
	}
	pFile.close();
	strncpy(pIvData,ivData,nIvLength);
	strncpy(pKeyData,keyData,nKeyLength);
	strncpy(psrcData,srcData,nTextLength);

	pIvData[nIvLength] = 0;
	pKeyData[nKeyLength] = 0;
	psrcData[nTextLength] = 0;

	delete[] ivData;
	delete[] keyData;
	delete[] srcData;
	delete[] data;

	ivData = NULL;
	data =NULL;
    keyData = NULL;
    srcData = NULL;
	return 0; 
}

// 根据指定文件名写3DES 明文Key及密钥密文
///fileName 文件名
///pIvData 向量
///pKeyData 密钥
///outBuffer 加密之后密文
int Base643Des::WriteFileKey(const char *fileName,char *pIvData,char *pKeyData,char *psrcData)
{
	char *data = new char[BUFFER_SIZE];
	memset(data,0,BUFFER_SIZE);

	fstream pFile;
	pFile.open(fileName,ios::out|ios::binary);
	if (!pFile.is_open())
	{
		//cout << "打开文件失败" << fileName << endl;
		return -1;
	}

	int  nIvLength   = strlen(pIvData);
	int  nKeyLength  = strlen(pKeyData);
	int  nTextLength = strlen(psrcData);

	
	//打开隐藏密钥
	int j=0,z=0,n=0;
	for(int i=0;  i<BUFFER_SIZE;  ++i)
	{
		if ((i>= FILE_IV_PLACE) && (i%2 == 0) && (n <= nIvLength))
		{
			if (n==0)
			{
				data[i] = nIvLength;
			}
			else
				data[i] = pIvData[n-1];
			++n;
		}

		if ((i>= FILE_KEY_PLACE) && (i%3 == 0) && (j<=nKeyLength))
		{
			if (j==0)
			{
				data[i] = nKeyLength;
			}
			else
				data[i] = pKeyData[j-1];
			++j;
		}

		if ((i>= FILE_CIPHER_PLACE) && (i%2 == 0) && (z<=nTextLength))
		{
			if (z==0)
			{
				data[i] = nTextLength;
			}
			else
				data[i] = psrcData[z-1];
			++z;
		}
	}
	pFile.write(data,BUFFER_SIZE);
	pFile.flush();
	pFile.close();

	delete[] data;
	data =NULL;
	return 0; 
}



// 根据指定字符串、key按3DES加密
///pszSrc 明文
///pdesIv 加密向量
///pdesKey 加密密钥
///outBuffer 加密之后明文
int Base643Des::Des3Encrypt(char *pszSrc,char *pChDesIV,char *pDesKey,unsigned char *outBuffer)
{
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_des_ede3_cbc(), NULL, (const unsigned char*)pDesKey,(const unsigned char*)pChDesIV);


	unsigned int uiLen = strlen(pszSrc);
	unsigned char* pEccrypted = new unsigned char[uiLen+64];	
	memset(pEccrypted,0,sizeof(pEccrypted));

	int nEncryptedLen = 0;
	int nRtn = EVP_EncryptUpdate(&ctx,pEccrypted,&nEncryptedLen,(const unsigned char*)pszSrc,uiLen);
	if (nRtn <0)
	{
		delete[] pEccrypted;
		return -1;
	}

	int nTmpLen = 0;
	nRtn = EVP_EncryptFinal_ex(&ctx, pEccrypted + nEncryptedLen, &nTmpLen);
	if(nRtn <0)
	{
		delete[] pEccrypted;
		return -1;
	}	
	nEncryptedLen += nTmpLen;
	pEccrypted[nEncryptedLen] =0;
	memcpy(outBuffer,pEccrypted,nEncryptedLen);
//	strcpy(outBuffer,pEccrypted);
    delete[] pEccrypted;
	return nEncryptedLen;
}


// 根据指定密码文、key按3DES解密
///pszSrc 密文
///pdesIv 解密向量
///pdesKey 解密密钥
///outBuffer 解密之后明文
int Base643Des::Des3UnEncrypt(char *pszSrc,char *pChDesIV,char *desKey,unsigned char *outBuffer,int uiLen)
{

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit_ex(&ctx, EVP_des_ede3_cbc(), NULL, (const unsigned char*)desKey,(const unsigned char*)pChDesIV);

//	int uiLen = strlen(pszSrc);
	unsigned char* pDecrypted = new unsigned char[uiLen + 128];
	int nDecryptedLen = 0;
	int nRtn = 0;

	memset(pDecrypted,0,sizeof(pDecrypted));

	nRtn = EVP_DecryptUpdate(&ctx,pDecrypted,&nDecryptedLen,(const unsigned char*)pszSrc,uiLen);
	if(nRtn <0)
	{
		delete[] pDecrypted;
		return -1;
	}

	int nTmpLen = 0;
	nRtn = EVP_DecryptFinal_ex(&ctx, pDecrypted + nDecryptedLen, &nTmpLen);
	nDecryptedLen += nTmpLen;

	pDecrypted[nDecryptedLen] =0;
	
	memcpy(outBuffer,pDecrypted,nDecryptedLen);
	outBuffer[nDecryptedLen] =0;
	
	delete []pDecrypted;
	return nDecryptedLen;

}


//根据指定明文字符串、key 选进行3DES加密后进行Base64编码
///pBufPwd 加密之后密文
///pBufSrc 明文
///pdesIv  加密向量
///pdesKey 加密密钥
int Base643Des::Des3Base64Enc(char *pBufPwd,char *pBufSrc,char *pdesIv, char *pdesKey)
{
	int rtn =0,n =0;
	memset(pBufPwd,0,sizeof(pBufPwd));

	rtn = Des3Encrypt(pBufSrc,pdesIv,pdesKey,(unsigned char*)pBufPwd);
	if(rtn < 0)
		return -1;

//    n  = strlen(pBufPwd);

	char *pPwdBase63 = new char[255];
	rtn = CEncode::enbase64(pBufPwd,rtn,pPwdBase63);
	if(rtn < 0)
		return -1;

	strcpy(pBufPwd,pPwdBase63);	
	delete[] pPwdBase63;
	pPwdBase63 = NULL;
	return 0;
}


//根据指定3DES字符串、向量、key,先进行解码后进行解密
///pBufSrcData 解密之后明文
///pBufEncoded 密文
///pdesIv 解密向量
///pdesKey 解密密钥	
int Base643Des::Base64Dec3Des(unsigned char *pBufSrcData,char *pBufEncoded,char *pdesIv,char *pdesKey)
{
	int nBase64EncLen = strlen(pBufEncoded);

	char *pBase64Dec = new char[nBase64EncLen/4*3+1];
	unsigned char *pBufData   = new unsigned char[nBase64EncLen/4*3+1+128];
	
	int nBase64DecLen = CEncode::unbase64(pBufEncoded,nBase64EncLen,pBase64Dec);

	pBase64Dec[nBase64DecLen] = 0;
    memset(pBufData,0,sizeof(pBufData));
	int nRtn = Des3UnEncrypt(pBase64Dec,pdesIv,pdesKey,pBufData,nBase64DecLen);
	if (nRtn < 0)
	{
		delete []pBase64Dec;
		delete []pBufData;
		return -1;
	}
	pBufData[nRtn] =0;
	memcpy(pBufSrcData,pBufData,nRtn);
	pBufSrcData[nRtn] =0;

	delete []pBase64Dec;
	delete []pBufData;
    return nRtn;
}

//
//int	Base643Des::enbase64(char *buf, int n, char *outbuf)
//{
//	int	ch, cnt=0;
//	char	*p;
//
//	for (p = buf; n > 0; n -= 3, p += 3) {
//		ch = *p >> 2;
//		ch = ENC64(ch);
//		outbuf[cnt++] = ch;
//
//		ch = ((*p << 4) & 060) | ((p[1] >> 4) & 017);
//		ch = ENC64(ch);
//		outbuf[cnt++] = ch;
//
//		ch = ((p[1] << 2) & 074) | ((p[2] >> 6) & 03);
//		ch = (n < 2) ? '=' : ENC64(ch);
//		outbuf[cnt++] = ch;
//
//		ch = p[2] & 077;
//		ch = (n < 3) ? '=' : ENC64(ch);
//		outbuf[cnt++] = ch;
//	}
//
//	outbuf[cnt] = 0;
//
//	return	cnt;
//}
//
//int	Base643Des::DEC64(char c)
//{
//	if (c=='+')
//		return	62;
//	if (c=='/')
//		return	63;
//	if (isdigit(c))
//		return	52+(c-0x30);
//	if (isupper(c))
//		return	(c-0x41);
//	if (islower(c))
//		return	26+(c-0x61);
//
//	return	-1;
//}
//
//int	Base643Des::unbase64(char *buf, int n, char *outbuf)
//{
//	int	ch, cnt=0;
//	char	*p;
//
//	while ('=' == buf[n-1])
//		n--;
//
//	for (p=buf ; n > 0; p += 4, n -= 4)
//		if (n > 3) {
//			ch = (DEC64(p[0]) << 2) | (DEC64(p[1]) >> 4);
//			outbuf[cnt++] = ch;
//			ch = (DEC64(p[1]) << 4) | (DEC64(p[2]) >> 2);
//			outbuf[cnt++] = ch;
//			ch = (DEC64(p[2]) << 6) | DEC64(p[3]);
//			outbuf[cnt++] = ch;
//		}
//		else {
//			if (n > 1) {
//				ch = (DEC64(p[0]) << 2) | (DEC64(p[1]) >> 4);
//				outbuf[cnt++] = ch;
//			}
//			if (n > 2) {
//				ch = (DEC64(p[1]) << 4) | (DEC64(p[2]) >> 2);
//				outbuf[cnt++] = ch;
//			}
//		}
//		return	cnt;
//}
//从加密文件sFileName中读取出解密后的字段sStr(string)(使用读共享方式)
//如果返回-1，代表打开文件失败，如果返回-2，代表解密出错。
int Base643Des::GetStrFromCodeFile(string sFileName,string & sStr)
{
	char ivData[100]  = {0}; 
	char key[1024] = {0};
	char src[1024] = {0};
	//从文件中获得密钥和密文
	int ret = ReadFileKey_DENYWR(sFileName.c_str(),ivData, key, src);
	if( -1 == ret)
	{
//		CRLog(E_ERROR,"打开[%s]文件失败!",sFileName.c_str());
		return -1;
	}
	char *pBufData   = new char[_MAX_PATH+128];
	memset(pBufData,0,sizeof(pBufData));

	//解密，获得明文，返回失败或明文长度
	ret = Base64Dec3Des((unsigned char*)pBufData,src,ivData,key);
	if(-1 == ret)
	{
//		CRLog(E_ERROR,"文件[%s]解密密码出错!",sFileName.c_str());
		return -2;
	}
	sStr=pBufData;
	delete[] pBufData;
	return 0;
};
//将字段sStr（char*）加密后写入加密文件sFileName(使用独占文件模式)
//如果返回-1，代表写入文件失败，如果返回-2，代表加密出错。
int Base643Des::SetStrToCodeFile(string sFileName,char * sStr)
{
	char fileNewPassword[1024] = {0};
	//随机生成密钥
	char cIvData[9];
	char cKey[25];
	string strKey = Base643Des::BuildRand(24);
	strcpy(cKey,strKey.c_str());
	strKey = Base643Des::BuildRand(8);
	strcpy(cIvData,strKey.c_str());

	int ret = Base643Des::Des3Base64Enc(fileNewPassword,sStr,cIvData,cKey);
	if (-1 == ret)
	{
//		CRLog(E_ERROR,"加密文件新密码出错!");
		return -2;
	}
	ret = Base643Des::WriteFileKey_DENYRW(sFileName.c_str(),cIvData,cKey,fileNewPassword);
	if (0 != ret)
	{
//		CRLog(E_ERROR,"新密码写文件错误!");
		return -1;
	}
	return 0;
}

// 根据指定获取文件名获取3DES 明文Key及密钥密文 ，用读共享的方式打开文件（拒绝写模式）
///fileName 文件名
///pIvData 向量
///pKeyData 密钥
///outBuffer 加密之后密文
int Base643Des::ReadFileKey_DENYWR(const char *fileName,char *pIvData,char *pKeyData,char *psrcData)
{
	char *data = new char[BUFFER_SIZE+1];
	memset(data,0,BUFFER_SIZE);

#ifdef _WIN32
	ifstream pFile;
	pFile.open(fileName,ios::binary,_SH_DENYWR);
	int tempN=0;
	while (!pFile.is_open() &&tempN<10)
	{
		pFile.clear();
		msleep(SLEEP_TIME);
		++tempN;
		pFile.open(fileName,ios::binary,_SH_DENYWR);

	}
	if (!pFile.is_open())
	{
		return -1;
	}
	pFile.seekg(0,ios::beg);
	pFile.read(data,BUFFER_SIZE);
	pFile.close();



#else
	int pFile;
	int tempN=0;
	pFile = open(fileName,  O_RDONLY);

	if(pFile == -1)
	{
		msleep(SLEEP_TIME);
		pFile = open(fileName, O_RDONLY);
	}
	struct flock lock;
	memset(&lock, 0,sizeof(lock));
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	while(fcntl(pFile, F_SETLK, &lock) !=0 && tempN<10)
	{
		msleep(SLEEP_TIME);
		++tempN;
	}
	if (tempN >= 10)
	{
		return -1;
	}
	lseek(pFile,0L,SEEK_SET);
	read(pFile,data,BUFFER_SIZE);
	lock.l_type = F_UNLCK;
	tempN = 0;
	while(fcntl(pFile, F_SETLK, &lock) !=0 && tempN<10)
	{
		msleep(SLEEP_TIME);
		++tempN;
	}
	if (tempN >= 10)
	{
		return -1;
	}
	close(pFile);
#endif
	int  nIvLength   = 0;
	int  nKeyLength  =0;
	int  nTextLength =0;

	char *ivData  = NULL;
	char *keyData = NULL;
	char *srcData = NULL;
	//打开隐藏密钥
	int j=0,z=0,n=0;
	for(int i=0;  i< BUFFER_SIZE;  ++i)
	{
		if ((i>= FILE_IV_PLACE) && (i%2 == 0) && (n <= nIvLength))
		{
			if (n==0)
			{
				nIvLength = data[i];
				ivData = new char[nIvLength+1];
			}
			else
				ivData[n-1] = data[i];
			++n;
		}
		if ((i>= FILE_KEY_PLACE) && (i%3 == 0) && (j<=nKeyLength))
		{
			if (j==0)
			{
				nKeyLength = data[i];
				keyData = new char[nKeyLength+1];
			}
			else
				keyData[j-1] = data[i];
			++j;
		}

		if ((i>= FILE_CIPHER_PLACE) && (i%2 == 0) && (z<=nTextLength))
		{
			if (z==0)
			{
				nTextLength = data[i];
				srcData  = new char[nTextLength+1];
			}
			else
				srcData[z-1] = data[i];
			++z;
		}
	}

	strncpy(pIvData,ivData,nIvLength);
	strncpy(pKeyData,keyData,nKeyLength);
	strncpy(psrcData,srcData,nTextLength);

	pIvData[nIvLength] = 0;
	pKeyData[nKeyLength] = 0;
	psrcData[nTextLength] = 0;

	delete[] ivData;
	delete[] keyData;
	delete[] srcData;
	delete[] data;

	ivData = NULL;
	data =NULL;
	keyData = NULL;
	srcData = NULL;
	return 0; 
}

// 根据指定文件名写3DES 明文Key及密钥密文，用文件独占方式打开文件（拒绝读写模式）
///fileName 文件名
///pIvData 向量
///pKeyData 密钥
///outBuffer 加密之后密文
int Base643Des::WriteFileKey_DENYRW(const char *fileName,char *pIvData,char *pKeyData,char *psrcData)
{
	char *data = new char[BUFFER_SIZE];
	memset(data,0,BUFFER_SIZE);
	int  nIvLength   = strlen(pIvData);
	int  nKeyLength  = strlen(pKeyData);
	int  nTextLength = strlen(psrcData);


	//打开隐藏密钥
	int j=0,z=0,n=0;
	for(int i=0;  i<BUFFER_SIZE;  ++i)
	{
		if ((i>= FILE_IV_PLACE) && (i%2 == 0) && (n <= nIvLength))
		{
			if (n==0)
			{
				data[i] = nIvLength;
			}
			else
				data[i] = pIvData[n-1];
			++n;
		}

		if ((i>= FILE_KEY_PLACE) && (i%3 == 0) && (j<=nKeyLength))
		{
			if (j==0)
			{
				data[i] = nKeyLength;
			}
			else
				data[i] = pKeyData[j-1];
			++j;
		}

		if ((i>= FILE_CIPHER_PLACE) && (i%2 == 0) && (z<=nTextLength))
		{
			if (z==0)
			{
				data[i] = nTextLength;
			}
			else
				data[i] = psrcData[z-1];
			++z;
		}
	}

#ifdef _WIN32
	fstream pFile;
	pFile.open(fileName,ios::out|ios::binary|ios::trunc,_SH_DENYRW);
	int tempN=0;
	while (!pFile.is_open() &&tempN<10)
	{
		pFile.clear();
		msleep(SLEEP_TIME);
		++tempN;
		pFile.open(fileName,ios::out|ios::binary|ios::trunc,_SH_DENYRW);
		
	}
	if (!pFile.is_open())
	{
		//cout << "打开文件失败" << fileName << endl;
		return -1;
	}
	pFile.write(data,BUFFER_SIZE);
	pFile.flush();
	pFile.close();
#else
	int pFile;
	int tempN=0;
	pFile = open(fileName, O_CREAT | O_TRUNC | O_RDWR ,0644);

	if(pFile == -1)
	{
		msleep(SLEEP_TIME);
		pFile = open(fileName, O_CREAT | O_TRUNC | O_RDWR ,0644);
	}
	struct flock lock;
	memset(&lock, 0,sizeof(lock));
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	while(fcntl(pFile, F_SETLK, &lock) !=0 && tempN<10)
	{
		msleep(SLEEP_TIME);
		++tempN;
	}
	if (tempN >= 10)
	{
		return -1;
	}
	lseek(pFile,0L,SEEK_END);
	write(pFile,data,BUFFER_SIZE);
	lock.l_type = F_UNLCK;
	tempN = 0;
	while(fcntl(pFile, F_SETLK, &lock) !=0 && tempN<10)
	{
		msleep(SLEEP_TIME);
		++tempN;
	}
	if (tempN >= 10)
	{
		return -1;
	}
	close(pFile);
#endif

	delete[] data;
	data =NULL;
	return 0; 
}

