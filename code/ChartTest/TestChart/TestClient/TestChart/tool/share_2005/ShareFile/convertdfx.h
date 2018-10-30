
#ifndef _ConvertDFX_H
#define _ConvertDFX_H

// �����Ҳ������ݽṹ
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

// �����ҳ�Ȩ���ݽṹ
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

	// ����Դ�ļ����ƺ�Ŀ���ļ�����
	bool ConvertFin(const char* sfile, const char* dfile);
	
	// ����Դ�ļ�����, Ŀ��·��, ͬʱָ���Ϻ������ڵ���Ŀ¼����
	bool ConvertWeight(const char* sfile, const char* shwgt = "sh", const char* szwgt = "sz");

protected:
	long ConvertDate(long date);
	int  DeConvertDate(int date, int hour, int min);
};

#endif
