/*******************************************************************************
 * Copyright (c)2003, www.ylink.cn 雁联计算系统有限公司
 * All rights reserved.
 *
 * 文件名称：HSDes.cpp
 * 文件标识：改进DES加密算法实现类
 * 描    述：此类改自交易部用户管理的加密算法
 * 函数列表：CString MakeSerial(CString Source, CString Key); - 产生一个密码(32BIT)
 *
 * 当前版本：V4.03
 * 作    者：雁联计算系统有限公司
 * 完成日期：2004-08-25
 *
 * 备	 注：
 * 修改记录：
 * 作    者：
 * 修改日期：
 * 修改内容：
 *******************************************************************************/
#include "stdafx.h"
#include "HSDes.h"

BYTE CHSDes::GetBit(BYTE* Data, BYTE Index)
{  
	return  (Data[Index / 8 ] & (128 >> (Index % 8))) > 0 ? 1 : 0;	  
}

void CHSDes::SetBit(BYTE* Data, BYTE Index, BYTE Value)
{
	BYTE Bit = 0;
	Bit = 128 >> (Index % 8);
	if(Value == 0)
	{
		Data[Index / 8] &= (~ Bit);
	}
	else	if(Value == 1)
	{
		Data[Index / 8] |=  Bit;
	}
	else
	{
	}
}

void CHSDes::Translate(BYTE* FR, BYTE* FK, BYTE* TotalOut)
{
	const BYTE E[48] = {  32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1};

	const BYTE SBoxes[8][4][16] =
	{
		{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

		{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

		{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

		{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

		{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

		{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

		{{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

		{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
	};

	const BYTE P[32] = { 16, 7, 20, 21,
		29, 12, 28, 17,
		1, 15, 23, 26,
		5, 18, 31, 10,
		2, 8, 24, 14,
		32, 27, 3, 9,
		19, 13, 30, 6,
		22, 11, 4, 25};

	BYTE Temp1[48];
	BYTE Temp2[32];
	int n, h, i, j, Row, Column;

	for( n = 0 ; n <  48 ; n++)
		Temp1[n] = FR[ E[n] - 1 ] ^ FK[n];

	for(n = 0; n < 8; n++)
	{
		i = n * 6;
		j = n * 4;
		Row = Temp1[i ] * 2 + Temp1[i + 5];
		Column = Temp1[i + 1] * 8 + Temp1[i + 2] * 4 + Temp1[i + 3] * 2 + Temp1[i + 4];

		for(h = 0; h < 4; h++)
		{
			if(h == 0)
			{
				Temp2[j + h] = (SBoxes[n][Row][Column] & 8) / 8;
			}
			else if(h ==1)
			{
				Temp2[j + h] = (SBoxes[n][ Row][ Column] & 4) / 4;
			}
			else if(h == 2)
			{
				Temp2[j + h] = (SBoxes[n][ Row][ Column] & 2) / 2;
			}
			else if(h == 3)
			{
				Temp2[j + h] = (SBoxes[n][ Row][ Column] & 1);
			}
		}
	}

	for( n = 0 ; n < 32; n++)
		TotalOut[n] = Temp2[ P[n] - 1];

}

void CHSDes::Shift(BYTE* SKP/*28*/)
{ 
	BYTE n, b;  
	b = SKP[0];
	for( n = 0 ; n <  27; n++)
		SKP[n] = SKP[n + 1];
	SKP[27] = b;  
}

void CHSDes::SubKey(BYTE Round, BYTE* SK/*48*/)
{
	const BYTE PC_2[48] = { 14, 17, 11, 24, 1, 5,
		3, 28, 15, 6, 21, 10,
		23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32};
	const BYTE ShiftTable[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

	BYTE  n, b;
	for( n = 1; n <= ShiftTable[Round] ; n++)
	{
		Shift(C);
		Shift(D);
	}

	for( n = 0 ; n <  48; n++)
	{
		b = PC_2[n] - 1;

		if( b < 28) 
			SK[n] = C[b] ;
		else
			SK[n] = D[b - 28];
	}
}

void CHSDes::HSDES(BYTE* Input, BYTE* Output, BYTE* Key, bool Encrypt)
{
	const BYTE IP[64] = 
	{ 58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};

	const BYTE InvIP[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25};

	const BYTE PC_1[56] = { 57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4};

	BYTE InputValue[64];
	BYTE OutputValue[64];

	BYTE RoundKeys[16][48];

	BYTE L[32], R[32], FunctionResult[32];


	BYTE n,  b, Round,tmp;
	
	for(n = 0 ; n < 64; n++)
		InputValue[n] = GetBit(Input, n);

	for(n = 0 ; n < 28; n++)
	{
		C[n] = GetBit(Key, PC_1[n] - 1);
		D[n] = GetBit(Key, PC_1[n + 28] - 1);
	}

	for(n = 0 ; n < 16; n++) 
		SubKey(n, RoundKeys[n]);

	for(n = 0 ; n < 64; n++)
	{
		if( n < 32) 
			L[n] = InputValue[ IP[n] - 1 ] ;
		else 
			R[n - 32] = InputValue[ IP[n] - 1];
	}

	for(Round = 0 ; Round < 16; Round++)	
	{
		if (Encrypt )
			Translate(R, RoundKeys[Round], FunctionResult);
		else
			Translate(R, RoundKeys[15 - Round], FunctionResult);

		for( n = 0 ; n < 32; n++)
			FunctionResult[n] ^= L[n];
		
		for(tmp = 0 ; tmp < 32; tmp ++)
		{
			L[tmp] = R[tmp];
			R[tmp] = FunctionResult[tmp];
		}
	}

	for( n = 0; n < 64 ; n++)
	{
		b = InvIP[n] - 1;

		if (b < 32) 
			OutputValue[n] = R[b] ;
		else 
			OutputValue[n] = L[b - 32];
	}

	for( n = 0 ; n < 64; n++) 
		SetBit(Output, n, OutputValue[n]);
}

CString CHSDes::Addspac(CString ch, int Tlens, int Tflag)
{
	int j, n;
	CString spac;
	CString result = ch;
	n = ch.GetLength();
	for( j = 0 ; j < (Tlens - n); j++)
	{
		spac += " ";
	}

	return Tflag == 0  ? spac + result: result + spac;  
}

void CHSDes::LbDES(const BYTE* source, BYTE* Destinate, const BYTE* Key, bool En) // Use Procedure
{
  BYTE a[8], b[8], aKey[8];
  int i, j, Num;
  memset(aKey, 0, 8);
  Num =1;
  for( i = 1; i < Num + 1 ; i++) 
  {
      for( j = 0 ; j <  8 ; j++)
	  {
		  a[j] = source[(i - 1) * 8 + j];
	  }
      
	  memcpy(aKey, Key, 8); 

      HSDES(a, b, aKey, En);

      for(j = 0 ; j <= 7 ; j++)
		  Destinate[(i - 1) * 8 + j] = b[j];    
  }
}
CString CHSDes::ToHex(int num)
{
		CString strText;
	BYTE c = 'A';
  if( num <= 9 )
  {
	  strText.Format("%d", num);
  }
  else
  {
	  strText = char('A' + num - 10);
  }
  return strText;
}

CString CHSDes::AsciitoHex(BYTE source)
{
	int n;
	int  n1, n2;

	n = int(source);
	n1 = n / 16;
	n2 = n % 16;
	return ToHex(n1) + ToHex(n2);
}

CString CHSDes::MakeSerial(CString Source, CString Key)
{
 	CString s1,Result;      
	BYTE key1[9] ;
	BYTE a1[17];
	BYTE b1[9], b2[9];
	BYTE c1[9], c2[9];
	memset(key1, 0, 9);
	memset(a1, 0, 17);
	memset(b1, 0, 9);
	memset(b2, 0, 9);
	memset(c1, 0, 9);
	memset(c2, 0, 9);
	
	bool Flag;
	int i;

	if( Source.GetLength() > 16)
	{
		s1 = Source.Left(16);
	}
	else
	{
		s1 = Addspac(Source, 16, 1);
	}

	//strcpy(a1, s1);
	for( i = 0; i < 16; i++)
	{
		a1[i] = s1[i];
	}

	for( i = 0; i < 8; i++)
	{
		b1[i] = a1[i];
		c1[i] = a1[i + 8];
		//gbcedit
		key1[i + 1] = Key[i];
		//gbcedit
	}

	Flag = false;
	LbDES(b1, b2, key1, Flag);
	LbDES(c1, c2, b2, Flag);
	LbDES(b1, b2, c2, Flag);
	Result.Empty();

	for( i = 0; i < 8; i++)
		Result += AsciitoHex(b2[i]) + AsciitoHex(c2[i]);
	return Result;
}