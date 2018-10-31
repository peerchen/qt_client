
#ifndef AFX_ENCODE_H__BASE643DES_40D9_86DC_F4D25F73E58E__INCLUDED_
#define AFX_ENCODE_H__BASE643DES_40D9_86DC_F4D25F73E58E__INCLUDED_





class UTIL_CLASS Base643Des
{
public:
	Base643Des();

public:
	~Base643Des();
	
	///生成指定长度随机数字字符串
	static string BuildRand(int nLen);

	// 根据指定获取文件名获取3DES 明文Key及密钥密文
	///fileName 文件名
	///pIvData 向量
	///pKeyData 密钥
	///outBuffer 加密之后密文
	static int ReadFileKey(const char *fileName,char *pIvData,char *pKeyData,char *psrcData);

	// 根据指定文件名写3DES 明文Key及密钥密文
	///fileName 文件名
	///pIvData 向量
	///pKeyData 密钥
	///outBuffer 加密之后密文
	static int WriteFileKey(const char *fileName,char *pIvData,char *pKeyData,char *psrcData);

	// 根据指定获取文件名获取3DES 明文Key及密钥密文 ，用读共享的方式打开文件（拒绝写模式）
	///fileName 文件名
	///pIvData 向量
	///pKeyData 密钥
	///outBuffer 加密之后密文
	static int ReadFileKey_DENYWR(const char *fileName,char *pIvData,char *pKeyData,char *psrcData);

	// 根据指定文件名写3DES 明文Key及密钥密文，用文件独占方式打开文件（拒绝读写模式）
	///fileName 文件名
	///pIvData 向量
	///pKeyData 密钥
	///outBuffer 加密之后密文
	static int WriteFileKey_DENYRW(const char *fileName,char *pIvData,char *pKeyData,char *psrcData);

	// 根据指定字符串、key按3DES加密
	///pszSrc 明文
	///pdesIv 加密向量
	///pdesKey 加密密钥
	///outBuffer 加密之后明文
	static int Des3Encrypt(char *pszSrc,char *pChDesIV,char *desKey,unsigned char *outBuffer);

	// 根据指定密码文、key按3DES解密
	///pszSrc 密文
	///pdesIv 解密向量
	///pdesKey 解密密钥
	///outBuffer 解密之后明文
	static int Des3UnEncrypt(char *pszSrc,char *pChDesIV,char *desKey,unsigned char *outBuffer,int uiLen);

	//根据指定明文字符串、key 选进行3DES加密后进行Base64编码
	///pBufPwd 加密之后密文
	///pBufSrc 明文
	///pdesIv  加密向量
	///pdesKey 加密密钥
	static int Des3Base64Enc(char *pBufPwd,char *pBufSrc,char *pdesIv,char *pdesKey);

	//根据指定3DES字符串、向量、key,先进行解码后进行解密
	///pBufSrcData 解密之后明文
	///pBufEncoded 密文
	///pdesIv 解密向量
	///pdesKey 解密密钥	
	static int Base64Dec3Des(unsigned char *pBufSrcData,char *pBufEncoded,char *pdesIv,char *pdesKey);

	//static int enBASE64(char *buf, int n, char *outbuf);

	//static int unBase64(char *buf, int n, char *outbuf);

	//private:
	//	static int	ENC64(int ch);
	//	static int	DEC64(char c);

	//从加密文件sFileName中读取出解密后的字段sStr(string)(使用读共享方式)
	//如果返回-1，代表打开文件失败，如果返回-2，代表解密出错。
	static int GetStrFromCodeFile(string sFileName,string & sStr);
	//将字段sStr（char*）加密后写入加密文件sFileName(使用独占文件模式)
	//如果返回-1，代表写入文件失败，如果返回-2，代表加密出错。
	static int SetStrToCodeFile(string sFileName,char * sStr);
};

#endif
