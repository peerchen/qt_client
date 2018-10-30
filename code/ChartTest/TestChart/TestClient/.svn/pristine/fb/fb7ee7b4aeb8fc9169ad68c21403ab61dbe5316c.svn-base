
#pragma once

#if !defined(__CCharConver_H__)
#define __CCharConver_H__

#ifndef HS_SUPPORT_UNIX

#include "atlenc.h"

class CCharConver
{
public:
	static CString HexToBin(CString string)//将16进制数转换成2进制
	{
		if( string == "0") return "0000";
		if( string == "1") return "0001";
		if( string == "2") return "0010";
		if( string == "3") return "0011";
		if( string == "4") return "0100";
		if( string == "5") return "0101";
		if( string == "6") return "0110";
		if( string == "7") return "0111";
		if( string == "8") return "1000";
		if( string == "9") return "1001";
		if( string == "a") return "1010";
		if( string == "b") return "1011";
		if( string == "c") return "1100";
		if( string == "d") return "1101";
		if( string == "e") return "1110";
		if( string == "f") return "1111";

		return "";
	}

	static CString BinToHex(CString BinString)//将2进制数转换成16进制
	{
		if( BinString == "0000") return "0";
		if( BinString == "0001") return "1";
		if( BinString == "0010") return "2";
		if( BinString == "0011") return "3";
		if( BinString == "0100") return "4";
		if( BinString == "0101") return "5";
		if( BinString == "0110") return "6";
		if( BinString == "0111") return "7";
		if( BinString == "1000") return "8";
		if( BinString == "1001") return "9";
		if( BinString == "1010") return "a";
		if( BinString == "1011") return "b";
		if( BinString == "1100") return "c";
		if( BinString == "1101") return "d";
		if( BinString == "1110") return "e";
		if( BinString == "1111") return "f";

		return "";
	}

	static int BinToInt(CString string)//2进制字符数据转换成10进制整型
	{
		int len =0;
		int tempInt = 0;
		int strInt = 0;
		for(int i =0 ;i < string.GetLength() ;i ++)
		{
			tempInt = 1;
			strInt = (int)string.GetAt(i)-48;
			for(int k =0 ;k < 7-i ; k++)
			{
				tempInt = 2*tempInt;
			}
			len += tempInt*strInt;
		}
		return len;
	}      

	static WCHAR * Gb2312ToUnicode(char *gbBuffer)  //GB2312 转换成　Unicode
	{ 
		WCHAR *uniChar;
		uniChar = new WCHAR[1];
		::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,uniChar,1);

		return uniChar;
	}

	static char * UnicodeToUTF_8(WCHAR *UniChar) // Unicode 转换成UTF-8
	{
		char *buffer;
		CString strOne;
		CString strTwo;
		CString strThree;
		CString strFour;
		CString strAnd;
		buffer = new char[3];
		int hInt,lInt;
		hInt = (int)((*UniChar)/256);
		lInt = (*UniChar)%256;
		CString string ;
		string.Format("%x",hInt);
		strTwo = HexToBin(string.Right(1));
		string = string.Left(string.GetLength() - 1);
		strOne = HexToBin(string.Right(1));
		string.Format("%x",lInt);
		strFour = HexToBin(string.Right(1));
		string = string.Left(string.GetLength() -1);
		strThree = HexToBin(string.Right(1));
		strAnd = strOne +strTwo + strThree + strFour;
		strAnd.Insert(0,"1110");
		strAnd.Insert(8,"10");
		strAnd.Insert(16,"10");
		strOne = strAnd.Left(8);
		strAnd = strAnd.Right(16);
		strTwo = strAnd.Left(8);
		strThree = strAnd.Right(8);
		*buffer = (char)BinToInt(strOne);
		buffer[1] = (char)BinToInt(strTwo);
		buffer[2] = (char)BinToInt(strThree);
		return buffer;
	}  

	static LPWSTR Gb2312ToUnicode(char *xmlStream, int len, int& nOutLen) 
	{
		int size = strlen(xmlStream) + 1;
        int destSize = MultiByteToWideChar(CP_ACP, 0, xmlStream, size, NULL, 0);

		LPWSTR clsidStringW = new WCHAR[destSize];
		memset(clsidStringW,0,sizeof(WCHAR)*destSize);
       
        if (MultiByteToWideChar(CP_ACP, 0, xmlStream, size, clsidStringW, destSize) == 0) {
            return 0;
        }

		nOutLen = destSize;

		return clsidStringW;
	}

	static char* translateCharToUTF_8(char *xmlStream, int len, int& nOutLen) 
	{
		int size = strlen(xmlStream) + 1;
        int destSize = MultiByteToWideChar(CP_ACP, 0, xmlStream, size, NULL, 0);

		LPWSTR clsidStringW = new WCHAR[destSize];
		memset(clsidStringW,0,sizeof(WCHAR)*destSize);
       
        if (MultiByteToWideChar(CP_ACP, 0, xmlStream, size, clsidStringW, destSize) == 0) {
            return 0;
        }

		// convert to UTF8
		nOutLen = AtlUnicodeToUTF8(clsidStringW, destSize, NULL, 0);
		char* szUTF8 = new char[nOutLen+1];
		memset(szUTF8,0,nOutLen+1);

		nOutLen = AtlUnicodeToUTF8(clsidStringW, destSize, szUTF8, nOutLen);
		szUTF8[nOutLen] = '\0';

		delete[] clsidStringW;

		return szUTF8;

#if 0
		int newCharLen = 0 ;
		int oldCharLen = 0;
		int revCharLen = len;
		char* newCharBuffer;
		char* finalCharBuffer;
		char *buffer ;
		CString string;
		//buffer  = new char[sizeof(WCHAR)];
		newCharBuffer = new char[int(2.5*revCharLen)];//设置最大的一个缓冲区
		memset(newCharBuffer,'\0',int(2.5*revCharLen));
		while(oldCharLen < revCharLen)
		{
			if( *(xmlStream + oldCharLen) >= 0)
			{
				*(newCharBuffer+newCharLen) = *(xmlStream +oldCharLen);
				newCharLen ++;
				oldCharLen ++;
			}
			//如果是英文直接复制就可以
			else
			{
				WCHAR *pbuffer = Gb2312ToUnicode(xmlStream+oldCharLen);
				buffer = UnicodeToUTF_8(pbuffer);
				*(newCharBuffer+newCharLen) = *buffer;
				*(newCharBuffer +newCharLen +1) = *(buffer + 1);
				*(newCharBuffer +newCharLen +2) = *(buffer + 2);
				newCharLen += 3;
				oldCharLen += 2;

				delete[] buffer;
				delete[] pbuffer;
			}
		}

		//newCharBuffer[newCharLen] = '\0';
		//CString string1 ;
		//string1.Format("%s",newCharBuffer);
		finalCharBuffer = new char[newCharLen+1];
		memset(finalCharBuffer,0,newCharLen+1);

		memcpy(finalCharBuffer,newCharBuffer,newCharLen);

		delete[] newCharBuffer;
		//delete[] buffer;

		return finalCharBuffer;
#endif

	}

};

#endif // HS_SUPPORT_UNIX

#endif // __CCharConver_H__
