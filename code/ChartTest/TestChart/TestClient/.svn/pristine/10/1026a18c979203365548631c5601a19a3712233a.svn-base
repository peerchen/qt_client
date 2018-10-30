//#pragma once

//#ifdef	HS_SUPPORT_UNIX
//#include <tgmath.h>
//#endif

#include <math.h>

// 字符串小数转换到整数型
static long GetLongValue(const char* pData,int nLen,int nPriceUnit)
{
	char szValue[128];
	memset(szValue,0,sizeof(szValue));
	memcpy(szValue,pData,min(nLen,127));

	if( nPriceUnit > 0 )
		return ((atof(szValue) + (float)1 / nPriceUnit * 0.1) * nPriceUnit);

	return ((atof(szValue) + (float)1 / 1 * 0.1) * 1);

#if 0
	if( pData == NULL || nLen <= 0 )
		return 0;

	if( nPriceUnit == 0 )
		nPriceUnit = 1;

	int nNum = log10((double)nPriceUnit);
	static const char* strDelimit = ".";

	long lRet = 0;

	char szValue[128];
	memset(szValue,0,sizeof(szValue));
	memcpy(szValue,pData,min(nLen,127));

	char* token = strtok( szValue,strDelimit );
	if( token )
	{
		// 整数部分
		lRet = atol(token) * nPriceUnit; 

		// 小数部分
		if( nNum > 0 )
		{
			token = strtok( NULL, strDelimit );
			if( token )
			{
				nLen = nNum - strlen(token);
				if( nLen > 0 )
					lRet += atol(token) * pow((float)10,nLen);
				else
					lRet += atol(token) / pow((float)10,abs(nLen));
			}
		}
	}

	return lRet;
#endif

}

static long GetLongValue2(const char* pData,int nPriceUnit)
{
	if( nPriceUnit > 0 )
		return ((atof(pData) + (float)1 / nPriceUnit * 0.1) * nPriceUnit);

	return ((atof(pData) + (float)1 / 1 * 0.1) * 1);

#if 0
	if( pData == NULL )
		return 0;

	if( nPriceUnit == 0 )
		nPriceUnit = 1;

	int nNum = log10((double)nPriceUnit);
	static const char* strDelimit = ".";

	long lRet = 0;

	char* pBeginData = (char*)pData;
	char* pEndData = pBeginData + strlen(pData);
	char* pCurData = pBeginData;
	while(pBeginData < pEndData)
	{
		if( *pBeginData == '.' )
		{			
			*pBeginData = '\0';
			pBeginData++;
			break;
		}
		else
		{
			pBeginData++;
		}
	}

	// 没有找到小数位
	if( pBeginData >= pEndData )
		return atol(pData) * nPriceUnit;

	// 整数部分
	lRet = atol(pCurData) * nPriceUnit;

	// 小数部分
	if( nNum > 0 )
	{
		int nLen = nNum - strlen(pBeginData);
		if( nLen > 0 )
			lRet += atol(pBeginData) * pow((float)10,nLen);
		else
			lRet += atol(pBeginData) / pow((float)10,abs(nLen));
	}

	return lRet;
#endif
}

static long GetLongValue(float fValue,int nPriceUnit)
{
	if( fValue == 0 )
		return 0;

	char szValue[128];
	sprintf(szValue,"%f",fValue);

	return GetLongValue(szValue,strlen(szValue),nPriceUnit);
}

static long GetLongValue3(float fValue,int nPriceUnit)
{
	if( fValue == 0 )
		return 0;

	if( nPriceUnit > 0 )
		return ((fValue + (float)1 / nPriceUnit * 0.1) * nPriceUnit);

	return ((fValue + (float)1 / 1 * 0.1) * 1);
	
}


