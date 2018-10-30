/*******************************************************************************
 * Copyright (c)2003, www.ylink.cn 雁联计算系统有限公司
 * All rights reserved.
 *
 * 文件名称：HSDes.h
 * 文件标识：改进DES加密算法实现类
 * 摘    要：此类改自交易部用户管理的加密算法
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

#pragma once
class CHSDes
{
public:
	CHSDes(){};
private:
	BYTE C[28], D[28];
private:
	// 设置二进制位
	BYTE GetBit(BYTE* Data, BYTE Index);
	void SetBit(BYTE* Data, BYTE Index, BYTE Value);
	// 加密转换
	void Translate(BYTE* FR, BYTE* FK, BYTE* TotalOut);
	// 颠倒数组
	void Shift(BYTE* SKP/*28*/);
	// 颠倒数组
	void SubKey(BYTE Round, BYTE* SK/*48*/);
	// DES加密
	void HSDES(BYTE* Input, BYTE* Output, BYTE* Key, bool Encrypt);
	// 转换成十六进制
	CString AsciitoHex(BYTE source);
	// 转换成十六进制
	CString ToHex(int num);
	// 改进型加密算法
	void LbDES(const BYTE* source, BYTE* Destinate, const BYTE* Key, bool En); // Use Procedure
	// 添加空格
	CString Addspac(CString ch, int Tlens, int Tflag);
public:
	// 产生加密秘文
	CString MakeSerial(CString Source, CString Key = "haowangjiao");
};