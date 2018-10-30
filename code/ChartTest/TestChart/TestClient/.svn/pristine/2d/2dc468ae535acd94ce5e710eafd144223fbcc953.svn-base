
#ifndef _ConvertDFX_H
#define _ConvertDFX_H

// 分析家财务数据结构
struct FxjCaiWu
{
	char   cType[2];
	char   cUnknow[2];
	char   cCode[STOCK_CODE_SIZE];
	float  fCwdata[39];
	char   cNext[1];
};

struct ZxCaiWu
{
	char	cCode[STOCK_CODE_SIZE];
	char	cName[8];
	long	date;
	float	fCwdata[34];
};

// 分析家除权数据结构
struct FxjChuQuan
{
	char   cCode[8];
	int	   nUnknow[2];
	char   cNext[1];
};

struct FxjChuQuanDataItem
{
	int   nTime;
	float fSg;
	float fPg;
	float fPgPrice;
	float fGive;
};

class ConvertDFX
{
public:
	ConvertDFX(void);
	~ConvertDFX(void);

	// 输入源文件名称和目的文件名称
	bool ConvertFin(const char* sfile, const char* dfile);
	
	// 输入源文件名称, 目标路径, 同时指定上海和深圳的子目录名称
	bool ConvertWeight(const char* sfile, const char* shwgt = "sh", const char* szwgt = "sz");

protected:
	long ConvertDate(long date);
	int  DeConvertDate(int date, int hour, int min);
};

#endif
