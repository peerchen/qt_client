
#include "stdafx.h"

#include "tool.h"
#include "ylsfile.h"
#include "ylstime.h"

#include "convertdfx.h"


ConvertDFX::ConvertDFX(void)
{
}

ConvertDFX::~ConvertDFX(void)
{
}

long ConvertDFX::ConvertDate(long date)
{
	CYlsTime time(date);
	long l = time.GetYear() * 10000 + time.GetMonth() * 100 + time.GetDay();
	return l;
}

int ConvertDFX::DeConvertDate(int date, int hour, int min)
{
	int year = date / 10000;
	int month = date % 10000 / 100;
	int day = date % 100;

	int result = year << 20;
	result += month << 16;
	result += day << 11;
	result += hour << 6;
	result += min;
	return result;
}

bool ConvertDFX::ConvertFin(const char* sfile, const char* dfile)
{	
	
	return true;

}

bool ConvertDFX::ConvertWeight(const char* sfile,
							   const char* shwgt, 
							   const char* szwgt)
{
	
	return true;
}
