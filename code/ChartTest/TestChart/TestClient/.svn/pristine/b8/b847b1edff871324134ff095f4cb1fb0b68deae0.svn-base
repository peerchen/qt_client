
#ifndef HS_WINCESTRUCT_H
#define HS_WINCESTRUCT_H

#pragma	pack(1)

#include "hsstruct.h"
#include "hscommunication.h"


// 参见文件：hscommunication.h

//// wince 相关
//#define RT_WINCE_FIND					0x0E01 // 查找代码
//#define RT_WINCE_UPDATE					0x0E02 // CE版本升级
//
//#define RT_WINCE_ZIXUN					0x0E03 // CE资讯请求
//
//
//// wince 客户端使用的协议
//#define Session_Socket 0x0001 // socket
//#define Session_Http   0x0002 // http
//
//#define WINCEZixun_StockInfo 0x1000 // 个股资讯
//
//// 公告信息配置
//#define Notice_Option_WinCE    0x0001 // 公告信息只对WinCE用户//
//#define Notice_Option_SaveSrv  0x0002 // 公告信息在服务器自动保存。
//#define Login_Option_Password  0x0004 // 登陆时使用新的加密方式。
//#define Login_Option_NotCheck  0x0008 // 不检测用户。

// ip 地址,端口
struct WINCEIPAddr
{
	BYTE	a;
	BYTE	b;
	BYTE	c;
	BYTE	d;

	short	nPort;		// socket端口
	short	nHttpPort;	// http端口
};

// 服务器信息,通过登陆成功返回
struct WINCESrvInfo
{
	BYTE		m_bVersion;     // 版本信息
	BYTE		m_cVersionSize; // 版本信息大小
	BYTE		m_cDataSize;	// BDZ1.2信息大小
	BYTE		m_bCount;		// 个数
	WINCEIPAddr m_sAddr[1];
	char		m_cData[1];
};

// wince 登陆参数
struct WINCELoggin
{

};


//#define RT_WINCE_ZIXUN					0x0E03 // CE资讯请求
struct WINCEZixunReq
{
	short    m_nUsedHttp;   //		使用什么协议请求

	short    Startpos;      //		开始条数
	short    Maxcount;      //		取几条
	CodeInfo Stockcode;     //      股票代码
	char	 menu_id[6];       //		资讯菜单号
	char     mobilecode[64];//		手机号码,13957160686

	WINCEZixunReq()
	{
		Startpos = 0;
		Maxcount = 100;
		memset(menu_id,0,sizeof(menu_id));
	}
};

struct WINCEZixunAns
{
	 DataHead m_dhHead;	// 数据报头

	 int	  m_nMenu;  // 是否为菜单
	 int	  m_nSize;
	 char     m_cData[1];
};


struct TPacketHeader
{	
    WORD m_HeaderSig;
    int  m_Length;
	char m_cData[1];
	TPacketHeader()
	{
		m_HeaderSig = 1974;
		m_Length = 0;
	}

	int IsValid() { return (m_HeaderSig == 1974 && m_Length > 0); }
};

// http 组织相关 

#define Http_Request_Head		"YLSHundsun"		// http 请求标志
#define Http_Request_CETest		"_CETest_"			// http 测试
#define Http_Request_CEHtml		"_CEYlsHtml_"	    // 使用html通讯
#define Http_Request_QPDecode	"CEYlsQPDecode"	    // 使用加密方式

#define Http_Request_GIF		"wwwhq.dll?"		// gif图请求标志
//#define Http_Request_YLS		"wwwhq_yls_"		// gif图请求标志2
#define Http_Request_YLS		"wwwhq.jsp?"		// gif图请求标志2




#define ATLSMTP_MAX_QP_LINE_LENGTH       76

inline int QPEncodeGetRequiredLength(int nSrcLen) throw()
{
	int nRet = 3*((3*nSrcLen)/(ATLSMTP_MAX_QP_LINE_LENGTH-8));
	nRet += 3*nSrcLen;
	nRet += 3;
	return nRet;
}

//Get the required length to hold this encoding based on nSrcLen
inline int QEncodeGetRequiredLength(int nSrcLen, int nCharsetLen) throw()
{
	return QPEncodeGetRequiredLength(nSrcLen)+7+nCharsetLen;
}


#define ATLSMTP_QPENCODE_DOT 1
#define ATLSMTP_QPENCODE_TRAILING_SOFT 2

inline BOOL QPEncode(BYTE* pbSrcData, int nSrcLen, LPSTR szDest, int* pnDestLen, DWORD dwFlags = 0) throw()
{
	//The hexadecimal character set
	static const char s_chHexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
								'A', 'B', 'C', 'D', 'E', 'F'};

	if (!pbSrcData || !szDest || !pnDestLen)
	{
		return FALSE;
	}

	if( *pnDestLen < QPEncodeGetRequiredLength(nSrcLen) )
		return FALSE;

	int nRead = 0, nWritten = 0, nLineLen = 0;
	char ch;
	while (nRead < nSrcLen)
	{
		ch = *pbSrcData++;
		nRead++;
		if (nLineLen == 0 && ch == '.' && (dwFlags & ATLSMTP_QPENCODE_DOT))
		{
			*szDest++ = '.';
			nWritten++;
			nLineLen++;
		}
		if ((ch > 32 && ch < 61) || (ch > 61 && ch < 127))
		{
			*szDest++ = ch;
			nWritten++;
			nLineLen++;
		}
		else if ((ch == ' ' || ch == '\t') && (nLineLen < (ATLSMTP_MAX_QP_LINE_LENGTH-12)))
		{
			*szDest++ = ch;
			nWritten++;
			nLineLen++;
		}	
		else
		{
			*szDest++ = '=';
			*szDest++ = s_chHexChars[(ch >> 4) & 0x0F];
			*szDest++ = s_chHexChars[ch & 0x0F];
			nWritten += 3;
			nLineLen += 3;
		}
		if (nLineLen >= (ATLSMTP_MAX_QP_LINE_LENGTH-11))
		{
			*szDest++ = '=';
			*szDest++ = '\r';
			*szDest++ = '\n';
			nLineLen = 0;
			nWritten += 3;
		}
	}
	if (dwFlags & ATLSMTP_QPENCODE_TRAILING_SOFT)
	{
		*szDest++ = '=';
		*szDest++ = '\r';
		*szDest++ = '\n';
		nWritten += 3;
	}

	*pnDestLen = nWritten;

	return TRUE;
}


inline BOOL QPDecode(BYTE* pbSrcData, int nSrcLen, LPSTR szDest, int* pnDestLen, DWORD dwFlags = 0) throw()
{
	if (!pbSrcData || !szDest || !pnDestLen)
	{
		return FALSE;
	}

	int nRead = 0, nWritten = 0, nLineLen = -1;
	char ch;
	while (nRead <= nSrcLen)
	{
		ch = *pbSrcData++;
		nRead++;
		nLineLen++;
		if (ch == '=')
		{
			//if the next character is a digit or a character, convert
			if (nRead < nSrcLen && (isdigit(*pbSrcData) || isalpha(*pbSrcData)))
			{
				char szBuf[5];
				szBuf[0] = *pbSrcData++;
				szBuf[1] = *pbSrcData++;
				szBuf[2] = '\0';
				char* tmp = '\0';
				*szDest++ = (BYTE)strtoul(szBuf, &tmp, 16);
				nWritten++;
				nRead += 2;
				continue;
			}
			//if the next character is a carriage return or line break, eat it
			if (nRead < nSrcLen && *pbSrcData == '\r' && (nRead+1 < nSrcLen) && *(pbSrcData+1)=='\n')
			{
				pbSrcData++;
				nRead++;
				nLineLen = -1;
				continue;
			}
			return FALSE;
		}
		if (ch == '\r' || ch == '\n')
		{
			nLineLen = -1;
			continue;
		}
		if ((dwFlags & ATLSMTP_QPENCODE_DOT) && ch == '.' && nLineLen == 0)
		{
			continue;
		}
		*szDest++ = ch;
		nWritten++;
	}

	*pnDestLen = nWritten-1;
	return TRUE;
}


#define ATL_BASE64_FLAG_NONE	0
#define ATL_BASE64_FLAG_NOPAD	1
#define ATL_BASE64_FLAG_NOCRLF  2

inline int Base64EncodeGetRequiredLength(int nSrcLen, DWORD dwFlags=ATL_BASE64_FLAG_NONE) throw()
{
	int nRet = nSrcLen*4/3;

	if ((dwFlags & ATL_BASE64_FLAG_NOPAD) == 0)
		nRet += nSrcLen % 3;

	int nCRLFs = nRet / 76 + 1;
	int nOnLastLine = nRet % 76;

	if (nOnLastLine)
	{
		if (nOnLastLine % 4)
			nRet += 4-(nOnLastLine % 4);
	}

	nCRLFs *= 2;

	if ((dwFlags & ATL_BASE64_FLAG_NOCRLF) == 0)
		nRet += nCRLFs;

	return nRet;
}

inline BOOL Base64Encode(
	const BYTE *pbSrcData,
	int nSrcLen,
	LPSTR szDest,
	int *pnDestLen,
	DWORD dwFlags=ATL_BASE64_FLAG_NONE) throw()
{
	static const char s_chBase64EncodingTable[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
		'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',	'h',
		'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
		'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-'};//'/' };

	if (!pbSrcData || !szDest || !pnDestLen)
	{
		return FALSE;
	}

	if(*pnDestLen < Base64EncodeGetRequiredLength(nSrcLen, dwFlags))
		return FALSE;

	int nWritten( 0 );
	int nLen1( (nSrcLen/3)*4 );
	int nLen2( nLen1/76 );
	int nLen3( 19 );

	for (int i=0; i<=nLen2; i++)
	{
		if (i==nLen2)
			nLen3 = (nLen1%76)/4;

		for (int j=0; j<nLen3; j++)
		{
			DWORD dwCurr(0);
			for (int n=0; n<3; n++)
			{
				dwCurr |= *pbSrcData++;
				dwCurr <<= 8;
			}
			for (int k=0; k<4; k++)
			{
				BYTE b = (BYTE)(dwCurr>>26);
				*szDest++ = s_chBase64EncodingTable[b];
				dwCurr <<= 6;
			}
		}
		nWritten+= nLen3*4;

		if ((dwFlags & ATL_BASE64_FLAG_NOCRLF)==0)
		{
			*szDest++ = '\r';
			*szDest++ = '\n';
			nWritten+= 2;
		}
	}

	if (nWritten && (dwFlags & ATL_BASE64_FLAG_NOCRLF)==0)
	{
		szDest-= 2;
		nWritten -= 2;
	}

	nLen2 = nSrcLen%3 ? nSrcLen%3 + 1 : 0;
	if (nLen2)
	{
		DWORD dwCurr(0);
		for (int n=0; n<3; n++)
		{
			if (n<(nSrcLen%3))
				dwCurr |= *pbSrcData++;
			dwCurr <<= 8;
		}
		for (int k=0; k<nLen2; k++)
		{
			BYTE b = (BYTE)(dwCurr>>26);
			*szDest++ = s_chBase64EncodingTable[b];
			dwCurr <<= 6;
		}
		nWritten+= nLen2;
		if ((dwFlags & ATL_BASE64_FLAG_NOPAD)==0)
		{
			nLen3 = nLen2 ? 4-nLen2 : 0;
			for (int j=0; j<nLen3; j++)
			{
				*szDest++ = '=';
			}
			nWritten+= nLen3;
		}
	}

	*pnDestLen = nWritten;
	return TRUE;
}

inline int DecodeBase64Char(unsigned int ch) throw()
{
	// returns -1 if the character is invalid
	// or should be skipped
	// otherwise, returns the 6-bit code for the character
	// from the encoding table
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 0;	// 0 range starts at 'A'
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 26;	// 26 range starts at 'a'
	if (ch >= '0' && ch <= '9')
		return ch - '0' + 52;	// 52 range starts at '0'
	if (ch == '+')
		return 62;
	if (ch == '-')// '/')
		return 63;
	return -1;
}

inline BOOL Base64Decode(LPCSTR szSrc, int nSrcLen, BYTE *pbDest, int *pnDestLen) throw()
{
	// walk the source buffer
	// each four character sequence is converted to 3 bytes
	// CRLFs and =, and any characters not in the encoding table
	// are skiped

	if (!szSrc || !pbDest || !pnDestLen)
	{
		return FALSE;
	}

	LPCSTR szSrcEnd = szSrc + nSrcLen;
	int nWritten = 0;
	while (szSrc < szSrcEnd)
	{
		DWORD dwCurr = 0;
		int i;
		int nBits = 0;
		for (i=0; i<4; i++)
		{
			if (szSrc >= szSrcEnd)
				break;
			int nCh = DecodeBase64Char(*szSrc);
			szSrc++;
			if (nCh == -1)
			{
				// skip this char
				i--;
				continue;
			}
			dwCurr <<= 6;
			dwCurr |= nCh;
			nBits += 6;
		}
		// dwCurr has the 3 bytes to write to the output buffer
		// left to right
		dwCurr <<= 24-nBits;
		for (i=0; i<nBits/8; i++)
		{
			*pbDest = (BYTE) ((dwCurr & 0x00ff0000) >> 16);
			dwCurr <<= 8;
			pbDest++;
			nWritten++;
		}
	}

	*pnDestLen = nWritten;
	return TRUE;
}

inline BOOL StringToHex(const char *pbSrcData, int nSrcLen,char*& szDest,int& pnDestLen)
{
	pnDestLen = Base64EncodeGetRequiredLength(nSrcLen);
	szDest = new char[pnDestLen+1];
	memset(szDest,0,pnDestLen+1);

	return Base64Encode((BYTE*)pbSrcData,nSrcLen, (LPSTR)szDest, &pnDestLen);
}

inline BOOL HexToString(const char *pszSrc, int nSrcCount,char*& pszDest,int& nDesCount)
{	
	if( pszSrc == NULL || nSrcCount <= 0 )
		return FALSE;

	pszDest = new char[nSrcCount + 1];
	memset(pszDest,0,nSrcCount + 1);

	nDesCount = 0;
	return Base64Decode(pszSrc, nSrcCount, (BYTE*)pszDest, &nDesCount);
}

//
inline void ConvertHexToString(const char *pszSrc, int nSrcCount,char*& pszDest,int& nDesCount)
{
	if( pszSrc == NULL || nSrcCount <= 0 )
		return;

	nDesCount = nSrcCount / 2;
	pszDest = new char[nDesCount + 1];

	int i;
	for (i = 0; (2 * i) < nSrcCount /*&& pszSrc[2 * i] != '\0'*/ && i < nDesCount; i++)
	{
		int n1 = pszSrc[2 * i] - 'A';
		int n2 = pszSrc[2 * i + 1]  - 'A';
		pszDest[i] = n2 * 16 + n1;
	}
	pszDest[i] = '\0';

}

inline void ConvertStringToHex(const char *pszSrc, int nCount,char*& pszDest,int& nDesCount)
{
	char *p = new char[2 * nCount + 1];
	int i;
	for (i = 0; i < nCount; i++)
	{
		int n1 = pszSrc[i] % 16;
		int n2 = pszSrc[i] / 16;
		p[2 * i] = 'A' + n1;
		p[2 * i + 1] = 'A' + n2;
	}
	p[2 * i] = '\0';

	pszDest = p;
	nDesCount = 2 * nCount + 1;
}

#pragma	pack()

#endif // HS_WINCESTRUCT_H
