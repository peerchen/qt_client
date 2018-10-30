
#if !defined(_ZiXunData_h_)
#define _ZiXunData_h_

#include "ylsfile.h"
#include "tool.h"

#ifndef HS_SUPPORT_UNIX

struct InfoIndex;
class ZiXunData
{
public:
	ZiXunData(const char* szMarketName);
	virtual ~ZiXunData();

protected:
	char m_szMarketName[128];
	char m_szFlag[16];

public:
	int Add(ZMRecordTickData* pZMRecordTickData);
	int Add(ZMRecordNewsData* pZMRecordTickData);

	int EmptyFileSize(CYlsFile& szFile,int nIndexCount,int nFileLen);

	int  AddIndex(InfoIndex* pInfo,						
		const char* pText,
		int nLen,
		const char* szFileName,
		const char* szPath,
		const char* szExt = ".HK",
		long lDate = -1,
		long lTime = -1,
		BOOL bFind = FALSE,  // 查找
		BOOL bEmpty = FALSE, // 清空到指定长度 
		BOOL bDelOld = FALSE // 总是删除原有数据
		);

};
#endif


class CCDPManager
{
public:
	CCDPManager();
	virtual ~CCDPManager();

protected:
	CHqDataBuffer	   m_StockCdpDataBuffer;
	CYlsMapStringToPtr m_mapCDPData;

public:
	BOOL	  AddToCDP(CodeInfo* pCode,StockCdp* psCdp);
	StockCdp* GetCDP(LPCTSTR key);
	StockCdp* GetCDP(CodeInfo* pCode);

	void	  LoadCDP(const char* szFileName);

	static CYlsFile* GetFile(const char* strFileName,UINT nOpenMode);
	static BOOL		 MyReadFile(const char* szFileName,CHqDataBuffer& buffer,int nStructSize = -1);
};

#endif
