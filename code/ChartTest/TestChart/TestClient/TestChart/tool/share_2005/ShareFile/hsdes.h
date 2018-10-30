/*******************************************************************************
 * Copyright (c)2003, ��������ϵͳ���޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ�HSDes.h
 * �ļ���ʶ��YLink�Ľ�DES�����㷨ʵ����
 * ժ    Ҫ��������Խ��ײ��û�����ļ����㷨
 *
 * ��ǰ�汾��V4.03
 * ��    �ߣ�YLink����
 * ������ڣ�2004-08-25
 *
 * ��	 ע��
 * �޸ļ�¼��
 * ��    �ߣ�
 * �޸����ڣ�
 * �޸����ݣ�
 *******************************************************************************/

#if !defined(CHSDes_H_)
#define CHSDes_H_

#include "tool.h"


class CHSDes
{
public:
	CHSDes(){};
private:
	BYTE C[28], D[28];
private:
	// ���ö�����λ
	BYTE GetBit(BYTE* Data, BYTE Index);
	void SetBit(BYTE* Data, BYTE Index, BYTE Value);
	// ����ת��
	void Translate(BYTE* FR, BYTE* FK, BYTE* TotalOut);
	// �ߵ�����
	void Shift(BYTE* SKP/*28*/);
	// �ߵ�����
	void SubKey(BYTE Round, BYTE* SK/*48*/);
	// DES����
	void HSDES(BYTE* Input, BYTE* Output, BYTE* Key, bool Encrypt);
	// ת����ʮ������
	char* AsciitoHex(CHqDataBuffer& buffer,BYTE source);
	// ת����ʮ������
	char* ToHex(CHqDataBuffer& buffer,int num);
	// �Ľ��ͼ����㷨
	void LbDES(const BYTE* source, BYTE* Destinate, const BYTE* Key, bool En); // Use Procedure
	// ��ӿո�
	char* Addspac(CHqDataBuffer& buffer,CHqDataBuffer& ch, int Tlens, int Tflag);

public:
	// ������������
	char* MakeSerial(CHqDataBuffer& ret,CHqDataBuffer& Source, const char* Key = "haowangjiao");

		//���ַ���ת��Ϊ16���Ƶ��ַ���
	static char* ConvertStringToHex(const char *pszSrc, int nCount,CHqDataBuffer& buffer);

		//16���Ƶ��ַ���ת��Ϊ��ͨ�ַ���
	static void    ConvertHexToString(const char *pszSrc, char* pszDest);
	static void    ConvertHexToString(const char *pszSrc, int nSrcCount,char* pszDest,int nDesCount);
	
		//����һ������ַ�
	static char    GenRandomChar();

	//	���������
	static char* EncodeStringEx(CHqDataBuffer& buffer,const char *pszSrc);
	static char* DecodeStringEx(CHqDataBuffer& buffer,const char *pszSrc);
	static char* EncodeString(CHqDataBuffer& buffer,const char *pszSrc);
	static char* DecodeString(CHqDataBuffer& buffer,const char *pszSrc);
};

#endif // CHSDes_H_

