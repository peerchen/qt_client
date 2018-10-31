// 3des.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
/************************************************************************ 
* DES/3DESԭ�� 
*  1-1���任��Կ 
*  1-1-1��ȡ��64λ����Կ��ÿ����8λ��Ϊ��żУ��λ�������������κβ��� 
* 
*  1-2���任��Կ 
*  1-2-1������64λ��Կ�е���żУ��λ�������±�PC-1��������Կ�任����λ���õ�56λ����Կ���ڱ任�У���żУ��λ������ 
* 
*  Permuted Choice 1 (PC-1)�������ʾ�������±��1��ʼ�����ת��ʱ��Ҫ��PC1_Table[i]-1 
*    57, 49, 41, 33, 25, 17,  9, 
*    1, 58, 50, 42, 34, 26, 18, 
*    10,  2, 59, 51, 43, 35, 27, 
*    19, 11,  3, 60, 52, 44, 36, 
*    63, 55, 47, 39, 31, 23, 15, 
*    7, 62, 54, 46, 38, 30, 22, 
*    14,  6, 61, 53, 45, 37, 29, 
*    21, 13,  5, 28, 20, 12,  4 
* 
*  1-2-2�����任�����Կ��Ϊ�������֣���ʼ��28λ��ΪC[0]������28λ��ΪD[0] 
*  1-2-3������16������Կ, I = 1��<�������IΪ������Կ�����������Ļ����Ǵ�1��ʼ����IȡֵΪ 1 �C 16 > 
*  1-2-3-1��ͬʱ��C[I]��D[I]����1λ��2λ������Iֵ�������Ƶ�λ�������±� 
*           I�� 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
*           ����λ���� 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 
*           <ÿ����λ�����C[I] D[I]��Ϊ��һ����λʱ�����C[I] D[I] 
*            �����и��ؼ��㣬���н���ʱ�����������ƣ�������I = 1ʱ������λ������ 
*            ����λ���� 0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 
*            ����ʱҲֻ������Ҳ�����������ĵط��ͼ�����һ���ģ�DES�㷨�ĺܶ໻λ���ǻ����ģ����������� 
*            ��1��λ����ñ�2�ٻ�һ����ֺ�ԭʼֵһ����> 
*  1-2-3-2����C[I]D[I]��Ϊһ�����尴�±�PC-2���任���õ�48λ��K[I] 
* 
*  Permuted Choice 2 (PC-2)�������ʾ�������±��1��ʼ�����ת��ʱ��Ҫ��PC2_Table[i]-1 
*    14, 17, 11, 24,  1,  5, 
*    3, 28, 15,  6, 21, 10, 
*    23, 19, 12,  4, 26,  8, 
*    16,  7, 27, 20, 13,  2, 
*    41, 52, 31, 37, 47, 55, 
*    30, 40, 51, 45, 33, 48, 
*    44, 49, 39, 56, 34, 53, 
*    46, 42, 50, 36, 29, 32 
* 
*  1-2-3-3����1-2-3-1��ѭ��ִ�У�ֱ��K[16]��������� 
* 
*  2������64λ������ 
*  2-1��ȡ��64λ�����ݣ�������ݳ��Ȳ���64λ��Ӧ�ý�����չΪ64λ�����粹�㣩 
*       <��ʲôҪ���������ݣ�ֻ�ܲ�����ȡֵ��Χ����ַ����������ȡֵ��Χ��0x00 �C 0XFF���һ�����64λ���������Ǿ�Ҫ����취������������ǰ����ϳ���ʲô��> 
*  2-2����64λ���ݰ��±�任��IP�� 
* 
*  Initial Permutation (IP)�������ʾ�������±��1��ʼ�����ת��ʱ��Ҫ��IP_Table[i]-1 
*    58, 50, 42, 34, 26, 18, 10, 2, 
*    60, 52, 44, 36, 28, 20, 12, 4, 
*    62, 54, 46, 38, 30, 22, 14, 6, 
*    64, 56, 48, 40, 32, 24, 16, 8, 
*    57, 49, 41, 33, 25, 17,  9, 1, 
*    59, 51, 43, 35, 27, 19, 11, 3, 
*    61, 53, 45, 37, 29, 21, 13, 5, 
*    63, 55, 47, 39, 31, 23, 15, 7 
* 
*  2-3�����任������ݷ�Ϊ�����֣���ʼ��32λ��ΪL[0]������32λ��ΪR[0] 
*  2-4����16������Կ�������ݣ���ʼI=1 
*  2-4-1����32λ��R[I-1]���±�E����չΪ48λ��E[I-1] 
*  Expansion (E)�������ʾ�������±��1��ʼ�����ת��ʱ��Ҫ��E_Table[i]-1 
*    32,  1,  2,  3,  4,  5, 
*    4,  5,  6,  7,  8,  9, 
*    8,  9, 10, 11, 12, 13, 
*    12, 13, 14, 15, 16, 17, 
*    16, 17, 18, 19, 20, 21, 
*    20, 21, 22, 23, 24, 25, 
*    24, 25, 26, 27, 28, 29, 
*    28, 29, 30, 31, 32,  1 
* 
*  2-4-2�����E[I-1]��K[I]����E[I-1] XOR K[I] <�������ɵ�16������Կ�����������õ���> 
*  2-4-3��������Ľ����Ϊ8��6λ���Ĳ��֣���1λ����6λ��ΪB[1]����7λ����12λ��ΪB[2]���������ƣ���43λ����48λ��ΪB[8] 
*  2-4-4����S��任���е�B[J]����ʼJ=1��������S���ֵ��������4λ���ȴ��� 
*  2-4-4-1����B[J]�ĵ�1λ�͵�6λ���Ϊһ��2λ���ȵı���M��M��Ϊ��S[J]�е��к� 
*  2-4-4-2����B[J]�ĵ�2λ����5λ��ϣ���Ϊһ��4λ���ȵı���N��N��Ϊ��S[J]�е��к� 
*  2-4-4-3����S[J][M][N]��ȡ��B[J] 
* 
*  Substitution Box 
*    S[1] 
*    14 4 13 1 2 15 11 8 3 10 6 12 5 9 0 7 
*    0 15 7 4 14 2 13 1 10 6 12 11 9 5 3 8 
*    4 1 14 8 13 6 2 11 15 12 9 7 3 10 5 0 
*    15 12 8 2 4 9 1 7 5 11 3 14 10 0 6 13 
* 
*    S[2] 
*    15 1 8 14 6 11 3 4 9 7 2 13 12 0 5 10 
*    3 13 4 7 15 2 8 14 12 0 1 10 6 9 11 5 
*    0 14 7 11 10 4 13 1 5 8 12 6 9 3 2 15 
*    13 8 10 1 3 15 4 2 11 6 7 12 0 5 14 9 
* 
*    S[3] 
*    10 0 9 14 6 3 15 5 1 13 12 7 11 4 2 8 
*    13 7 0 9 3 4 6 10 2 8 5 14 12 11 15 1 
*    13 6 4 9 8 15 3 0 11 1 2 12 5 10 14 7 
*    1 10 13 0 6 9 8 7 4 15 14 3 11 5 2 12 
* 
*    S[4] 
*    7 13 14 3 0 6 9 10 1 2 8 5 11 12 4 15 
*    13 8 11 5 6 15 0 3 4 7 2 12 1 10 14 9 
*    10 6 9 0 12 11 7 13 15 1 3 14 5 2 8 4 
*    3 15 0 6 10 1 13 8 9 4 5 11 12 7 2 14 
* 
*    S[5] 
*    2 12 4 1 7 10 11 6 8 5 3 15 13 0 14 9 
*    14 11 2 12 4 7 13 1 5 0 15 10 3 9 8 6 
*    4 2 1 11 10 13 7 8 15 9 12 5 6 3 0 14 
*    11 8 12 7 1 14 2 13 6 15 0 9 10 4 5 3 
* 
*    S[6] 
*    12 1 10 15 9 2 6 8 0 13 3 4 14 7 5 11 
*    10 15 4 2 7 12 9 5 6 1 13 14 0 11 3 8 
*    9 14 15 5 2 8 12 3 7 0 4 10 1 13 11 6 
*    4 3 2 12 9 5 15 10 11 14 1 7 6 0 8 13 
* 
*    S[7] 
*    4 11 2 14 15 0 8 13 3 12 9 7 5 10 6 1 
*    13 0 11 7 4 9 1 10 14 3 5 12 2 15 8 6 
*    1 4 11 13 12 3 7 14 10 15 6 8 0 5 9 2 
*    6 11 13 8 1 4 10 7 9 5 0 15 14 2 3 12 
* 
*    S[8] 
*    13 2 8 4 6 15 11 1 10 9 3 14 5 0 12 7 
*    1 15 13 8 10 3 7 4 12 5 6 11 0 14 9 2 
*    7 11 4 1 9 12 14 2 0 6 10 13 15 3 5 8 
*    2 1 14 7 4 10 8 13 15 12 9 0 3 5 6 11 
* 
*  2-4-4-4����2-4-4-1��ѭ��ִ�У�ֱ��B[8]�������� 
*  2-4-4-5����B[1]��B[8]��ϣ����±�P���任���õ�P <B[1]��B[8]���һ��32λ������> 
* 
*  Permutation P 
*    16, 7, 20, 21, 
*    29, 12, 28, 17, 
*    1,  15, 23, 26, 
*    5,  18, 31, 10, 
*    2,  8, 24, 14, 
*    32, 27, 3,  9, 
*    19, 13, 30, 6, 
*    22, 11, 4,  25 
* 
*  2-4-6�����P��L[I-1]�������R[I]����R[I] = P XOR L[I - 1] 
*  2-4-7��L[I] = R[I - 1] 
*  2-4-8����2-4-1����ʼѭ��ִ�У�ֱ��K[16]���任��� 
*  2-4-5����ϱ任���R[16]L[16]��ע�⣺R��Ϊ��ʼ��32λ�������±�IP-1���任�õ����Ľ�� 
*         <����Ҫע���ˣ��Ƕ�R[16]L[16]��������L[16]R[16] ������Ҫ������32λ����32λ����һ��λ��, �����±����16��ָ����������λ��> 
* 
*  Final Permutation (IP**-1) 
*    40, 8, 48, 16, 56, 24, 64, 32, 
*    39, 7, 47, 15, 55, 23, 63, 31, 
*    38, 6, 46, 14, 54, 22, 62, 30, 
*    37, 5, 45, 13, 53, 21, 61, 29, 
*    36, 4, 44, 12, 52, 20, 60, 28, 
*    35, 3, 43, 11, 51, 19, 59, 27, 
*    34, 2, 42, 10, 50, 18, 58, 26, 
*    33, 1, 41,  9, 49, 17, 57, 25 
* 
*  3DES���㷽�����£� 
*    3DES(����) = DES(key1, ����) DES(key2, ����)  DES(key3, ����) 
*    3DES(����) = DES(key3, ����) DES(key2, ����)  DES(key1, ����) 
*    ÿ��KEYΪ64λ���ܹ�������192λ��KEY, ��һ�㶼ֻʹ��128λ��key 
*    ���ֻ��128λ��Կ����key3 = key1 
* 
*************************************************************************/  
  
#include "3des.h"  
//#include <stdlib.h>  
//#include <stdio.h>  
#include <memory.h>  
#include <string.h>  
//#include <ctype.h>  

static char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char IP_Table[64] =  
{  
    58, 50, 42, 34, 26, 18, 10, 2,  
    60, 52, 44, 36, 28, 20, 12, 4,  
    62, 54, 46, 38, 30, 22, 14, 6,  
    64, 56, 48, 40, 32, 24, 16, 8,  
    57, 49, 41, 33, 25, 17,  9, 1,  
    59, 51, 43, 35, 27, 19, 11, 3,  
    61, 53, 45, 37, 29, 21, 13, 5,  
    63, 55, 47, 39, 31, 23, 15, 7  
};  
  
const char IPR_Table[64] =  
{  
    40, 8, 48, 16, 56, 24, 64, 32,  
    39, 7, 47, 15, 55, 23, 63, 31,  
    38, 6, 46, 14, 54, 22, 62, 30,  
    37, 5, 45, 13, 53, 21, 61, 29,  
    36, 4, 44, 12, 52, 20, 60, 28,  
    35, 3, 43, 11, 51, 19, 59, 27,  
    34, 2, 42, 10, 50, 18, 58, 26,  
    33, 1, 41,  9, 49, 17, 57, 25  
};  
  
const char E_Table[48] =  
{  
    32,  1,  2,  3,  4,  5,  
    4,  5,  6,  7,  8,  9,  
    8,  9, 10, 11, 12, 13,  
    12, 13, 14, 15, 16, 17,  
    16, 17, 18, 19, 20, 21,  
    20, 21, 22, 23, 24, 25,  
    24, 25, 26, 27, 28, 29,  
    28, 29, 30, 31, 32,  1  
};  
  
const char P_Table[32] =  
{  
    16, 7, 20, 21,  
    29, 12, 28, 17,  
    1,  15, 23, 26,  
    5,  18, 31, 10,  
    2,  8, 24, 14,  
    32, 27, 3,  9,  
    19, 13, 30, 6,  
    22, 11, 4,  25  
};  
  
const char PC1_Table[56] =  
{  
    57, 49, 41, 33, 25, 17,  9,  
     1, 58, 50, 42, 34, 26, 18,  
    10,  2, 59, 51, 43, 35, 27,  
    19, 11,  3, 60, 52, 44, 36,  
    63, 55, 47, 39, 31, 23, 15,  
     7, 62, 54, 46, 38, 30, 22,  
    14,  6, 61, 53, 45, 37, 29,  
    21, 13,  5, 28, 20, 12,  4  
};  
  
const char PC2_Table[48] =  
{  
    14, 17, 11, 24,  1,  5,  
     3, 28, 15,  6, 21, 10,  
    23, 19, 12,  4, 26,  8,  
    16,  7, 27, 20, 13,  2,  
    41, 52, 31, 37, 47, 55,  
    30, 40, 51, 45, 33, 48,  
    44, 49, 39, 56, 34, 53,  
    46, 42, 50, 36, 29, 32  
};  
  
const char LOOP_Table[16] =  
{  
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1  
};  
  
const char S_Box[8][4][16] =  
{  
    {  
        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},  
        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},  
        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},  
        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}  
    },  
  
    {  
        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},  
        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},  
        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},  
        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}  
    },  
  
    {  
        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},  
        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},  
        {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},  
        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}  
    },  
  
    {  
        { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},  
        {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},  
        {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},  
        { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}  
    },  
  
    {  
        { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},  
        {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},  
        { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},  
        {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}  
    },  
  
    {  
        {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},  
        {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},  
        { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},  
        { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}  
    },  
  
    {  
        { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},  
        {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},  
        { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},  
        { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}  
    },  
  
    {  
        {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},  
        { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},  
        { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},  
        { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}  
    }  
};
  
  
  
static void ByteToBit(char *Out, const char *In, int bits);  
static void BitToByte(char *Out, const char *In, int bits);  
static void RotateL(char *In, int len, int loop);  
static void Xor(char *InA, const char *InB, int len);  
static void Transform(char *Out, const char *In, const char *Table, int len);  
static void S_func(char Out[32], const char In[48]);  
static void F_func(char In[32], const char Ki[48]);  
static void SetSubKey(PSubKey pSubKey, const char Key[8]);  
static void DES(char Out[8], const char In[8], const PSubKey pSubKey, int Type);  
  
  
  
/******************************************************************* 
  �� �� �� ��:  ByteToBit 
  �� �� �� ����  ��BYTEת��ΪBit�� 
  �� �� ˵ ����  Out:    �����Bit��[in][out] 
                In:     �����BYTE��[in] 
                bits:   Bit���ĳ���[in] 
 
  ����ֵ ˵����   void 
*******************************************************************/  
static void ByteToBit(char *Out, const char *In, int bits)  
{  
    int i;  
    for (i=0; i<bits; ++i)  
        Out[i] = (In[i>>3]>>(7 - i&7)) & 1;  
}  
  
/******************************************************************* 
  �� �� �� ��:  BitToByte 
  �� �� �� ����  ��Bitת��ΪByte�� 
  �� �� ˵ ����  Out:    �����BYTE��[in][out] 
                In:     �����Bit��[in] 
                bits:   Bit���ĳ���[in] 
 
  ����ֵ ˵����   void 
  ��       ��:    huangjf 
  �� �� �� �ڣ�  2009.6.17 
*******************************************************************/  
static void BitToByte(char *Out, const char *In, int bits)  
{  
    int i;  
    memset(Out, 0, bits>>3);  
    for (i=0; i<bits; ++i) Out[i>>3] |= In[i]<<(7 - i&7);  
}  
  
/******************************************************************* 
  �� �� �� ��:  RotateL 
  �� �� �� ����  ��BIT����λ������� 
  �� �� ˵ ����  In:     �����Bit��[in][out] 
                len:    Bit���ĳ���[in] 
                loop:   ��������ĳ��� 
 
  ����ֵ ˵����   void 
  ��       ��:    huangjf 
  �� �� �� �ڣ�  2009.6.17 
*******************************************************************/  
static void RotateL(char *In, int len, int loop)  
{  
    char szTmp[256] = {0};  
  
    if (len >= 256) return;  
    if (loop==0 || loop>=256) return;  
  
    memset(szTmp, 0x00, sizeof(szTmp));  
  
    memcpy(szTmp, In, loop);  
    memmove(In, In+loop, len-loop);  
    memcpy(In+len-loop, szTmp, loop);  
}  
  
/******************************************************************* 
  �� �� �� ��:  Xor 
  �� �� �� ����  ������Bit��������� 
  �� �� ˵ ����  InA:    �����Bit��[in][out] 
                InB:    �����Bit��[in] 
                loop:   Bit���ĳ��� 
 
  ����ֵ ˵����   void 
  ��       ��:    huangjf 
  �� �� �� �ڣ�  2009.6.17 
*******************************************************************/  
static void Xor(char *InA, const char *InB, int len)  
{  
    int i;  
    for (i=0; i<len; ++i) InA[i] ^= InB[i];  
}  
  
/******************************************************************* 
  �� �� �� ��:  Transform 
  �� �� �� ����  ������Bit���������λת�� 
  �� �� ˵ ����  Out:    �����Bit��[out] 
                In:     �����Bit��[in] 
                Table:  ת����Ҫ�ı�ָ�� 
                len:    ת����ĳ��� 
 
  ����ֵ ˵����   void 
  ��       ��:    huangjf 
  �� �� �� �ڣ�  2009.6.17 
*******************************************************************/  
static void Transform(char *Out, const char *In, const char *Table, int len)  
{  
    char szTmp[256] = {0};  
    int i;  
  
    if (!Out || !In || !Table) return;  
    if (len >= 256) return;  
  
    memset(szTmp, 0x00, sizeof(szTmp));  
    for (i=0; i<len; ++i) szTmp[i] = In[Table[i]-1];  
  
    memcpy(Out, szTmp, len);  
}  
  
/******************************************************************* 
  �� �� �� ��:  S_func 
  �� �� �� ����  ʵ�����ݼ���S BOXģ�� 
  �� �� ˵ ����  Out:    �����32Bit[out] 
                In:     �����48Bit[in] 
 
  ����ֵ ˵����   void 
  ��       ��:    huangjf 
  �� �� �� �ڣ�  2009.6.17 
*******************************************************************/  
static void S_func(char Out[32], const char In[48])  
{  
    int i,j,k,l;  
    for (i=0,j=0,k=0; i<8; ++i,In+=6,Out+=4)  
    {  
        j = (In[0]<<1) + In[5];  
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];  
  
        for ( l=0; l<4; ++l)  
            Out[l] = (S_Box[i][j][k]>>(3 - l)) & 1;  
    }  
}  
  
/******************************************************************* 
  �� �� �� ��:  F_func 
  �� �� �� ����  ʵ�����ݼ��ܵ����P 
  �� �� ˵ ����  Out:    �����32Bit[out] 
                In:     �����48Bit[in] 
 
  ����ֵ ˵����   void 
  ��       ��:    huangjf 
  �� �� �� �ڣ�  2009.6.17 
*******************************************************************/  
static void F_func(char In[32], const char Ki[48])  
{  
    char MR[48] = {0};  
    memset(MR, 0x00, sizeof(MR));  
  
    Transform(MR, In, E_Table, 48);  
    Xor(MR, Ki, 48);  
    S_func(In, MR);  
    Transform(In, In, P_Table, 32);  
}  
  
/******************************************************************* 
  �� �� �� ��:  SetSubKey 
  �� �� �� ����  �任����λ��8�ֽ���Կ������16������Կ 
  �� �� ˵ ����  pSubKey:    ת�����ɵ�16������Կ[out] 
                Key:        �����8�ֽ�64Bit��Կ[in] 
 
  ����ֵ ˵����   void 
  ��       ��:    huangjf 
  �� �� �� �ڣ�  2009.6.17 
*******************************************************************/  
static void SetSubKey(PSubKey pSubKey, const char Key[8])  
{  
    int i;  
    char K[64] = {0}, *KL=&K[0], *KR=&K[28];  
  
    ByteToBit(K, Key, 64);  
  
    Transform(K, K, PC1_Table, 56);  
  
    for ( i=0; i<16; ++i)  
    {  
        RotateL(KL, 28, LOOP_Table[i]);  
        RotateL(KR, 28, LOOP_Table[i]);  
        Transform((*pSubKey)[i], K, PC2_Table, 48);  
    }  
}  
  
/******************************************************************* 
�� �� �� ��:    DES 
�� �� �� ����    ����8�ֽ�64λ������ 
�� �� ˵ ����    Out:        �����8�ֽ�[out] 
                In:         �����8�ֽڴ�����[in] 
                pSubKey:    ת�����16��48λ����Կ 
                Type:       ���ͣ�����ENCRYPT������DECRYPT 
 
����ֵ ˵���� void 
��       ��:  huangjf 
�� �� �� �ڣ�    2009.6.17 
*******************************************************************/  
static void DES(char Out[8], const char In[8], const PSubKey pSubKey, int Type)  
{  
    int i;  
    char M[64] = {0}, *ML=&M[0], *MR=&M[32], szTmp[32] = {0};  
  
    ByteToBit(M, In, 64);  
    Transform(M, M, IP_Table, 64);  
  
    if (Type == ENCRYPT)  
    {  
        for (i=0; i<16; ++i)  
        {  
            memcpy(szTmp, MR, 32);  
            F_func(MR, (*pSubKey)[i]);  
            Xor(MR, ML, 32);  
            memcpy(ML, szTmp, 32);  
        }  
    }  
    else  
    {  
        for (i=15; i>=0; --i)  
        {  
            memcpy(szTmp, MR, 32);  
            F_func(MR, (*pSubKey)[i]);  
            Xor(MR, ML, 32);  
            memcpy(ML, szTmp, 32);  
        }  
    }  
    RotateL(M, 64, 32);  
    Transform(M, M, IPR_Table, 64);  
    BitToByte(Out, M, 64);  
}  
  
/************************************************************************************************************************************************/  
/************************************************************************************************************************************************/  
  
/******************************************************************* 
�� �� �� ��:    Run1Des 
�� �� �� ����    ִ�е�DES�㷨���ı��ӽ��� 
�� �� ˵ ����    bType   :���ͣ�����ENCRYPT������DECRYPT 
                bMode   :ģʽ��ECB,CBC 
                In      :�����ܴ�ָ�� 
                in_len  :�����ܴ��ĳ��ȣ�ͬʱOut�Ļ�������СӦ���ڻ��ߵ���in_len 
                Key     :��Կ(��Ϊ8λ,16λ,24λ)֧��3��Կ 
                key_len :��Կ���ȣ����24λ���ֽ����Զ��ü� 
                Out     :�������ָ�� 
                out_len :��������С 
                cvecstr :8�ֽ��漴�ַ��� 
 
��       ��:  huangjf 
�� �� �� �ڣ�    2009.6.17 
 
����ֵ ˵���� int     :�Ƿ���ܳɹ���1���ɹ���0��ʧ�� 
*******************************************************************/  
int Run1Des(int bType, int bMode, const char *In, unsigned int in_len, const char *Key, unsigned int key_len, char* Out, unsigned int out_len, const char cvecstr[8])  
{  
    int i,j,k;  
    char m_SubKey[16][48] = {0};  
  
    /*�������Ϸ�*/  
    if (!In || !Key || !Out) return 0;  
  
    /*��Կ���ȣ���DESֻ֧��8�ֽڣ�64λ����Կ��ÿ����8λ��Ϊ��żУ��λ��������8�ֽڵ��Զ��ü�*/  
    if (key_len & 0x00000007) return 0;  
  
    /*���������ݳ��ȣ�����Ϊ8�ֽڵı����������8�ı���������RunPad()������λ*/  
    if (in_len & 0x00000007) return 0;  
  
    /*��������С�ж�*/  
    if (out_len < in_len) return 0;  
  
    /*����16������Կ*/  
    memset(m_SubKey, 0x00, sizeof(m_SubKey));  
    SetSubKey(&m_SubKey, Key);  
  
    if (bMode == ECB)  
    {  
        /*ÿ8�ֽڼ���*/  
        for (i=0,j=in_len>>3; i<j; ++i,Out+=8,In+=8)  
        {  
            DES(Out, In, &m_SubKey, bType);  
        }  
    }  
    else if (bMode == CBC)  
    {  
        if (cvecstr == NULL) return 0;  
  
        char cvec[8] = {0};  
        char cvin[8] = {0};  
  
        memcpy(cvec, cvecstr, 8);  
  
        for (i=0,j=in_len>>3; i<j; ++i,Out+=8,In+=8)  
        {  
            if (bType == ENCRYPT)  
            {  
                for ( k=0; k<8; ++k)  
                {  
                    cvin[k] = In[k] ^ cvec[k];  
                }  
            }  
            else  
            {  
                memcpy(cvin, In, 8);  
            }  
  
            DES(Out, cvin, &m_SubKey, bType);  
  
            if (bType == ENCRYPT)  
            {  
                memcpy(cvec, Out, 8);  
            }  
            else  
            {  
                for (k=0; k<8; ++k)  
                {  
                    Out[k] = Out[k] ^ cvec[k];  
                }  
                memcpy(cvec, cvin, 8);  
            }  
        }  
    }  
    else  
    {  
        return 0;  
    }  
  
    return 1;  
}  
  
/******************************************************************* 
  �� �� �� ��:  Run3Des 
  �� �� �� ����  ִ��3DES�㷨���ı��ӽ��� 
  �� �� ˵ ����  bType   :���ͣ�����ENCRYPT������DECRYPT 
                bMode   :ģʽ��ECB,CBC 
                In      :�����ܴ�ָ�� 
                in_len  :�����ܴ��ĳ��ȣ�ͬʱOut�Ļ�������СӦ���ڻ��ߵ���in_len 
                Key     :��Կ(��Ϊ8λ,16λ,24λ)֧��3��Կ 
                key_len :��Կ���ȣ����24λ���ֽ����Զ��ü� 
                Out     :�������ָ�� 
                out_len :��������С 
                cvecstr :8�ֽ��漴�ַ��� 
 
  ����ֵ ˵����   int     :�Ƿ���ܳɹ���1���ɹ���0��ʧ�� 
 
  ��       ��:    huangjf 
  �� �� �� �ڣ�  2009.6.17 
 
  3DES(����) = DES(key1, ����) DES(key2, ����) DES(key3, ����) 
  3DES(����) = DES(key3, ����) DES(key2, ����) DES(key1, ����) 
  ÿ��KEYΪ64λ���ܹ�������192λ��KEY, ��һ�㶼ֻʹ��128λ��key 
  ���ֻ��128λ��Կ����key3 = key1 
 
*******************************************************************/  
int Run3Des(int bType, int bMode, const char *In, unsigned int in_len, const char *Key, unsigned int key_len, char* Out, unsigned int out_len, const char cvecstr[8])  
{  
    int i,j,k;  
    char m_SubKey[3][16][48] = {0};  
    unsigned char nKey;  
  
    /*�������Ϸ�*/  
    if (!In || !Key || !Out) return 0;  
  
    /*���������ݳ��ȣ�����Ϊ8�ֽڵı����������8�ı���������RunPad()������λ*/  
    if (in_len & 0x00000007) return 0;  
  
    /*��Կ���ȣ�3DESֻ֧��8��16��24�ֽڣ�192λ����Կ��ʵ��ʹ��128λ��ÿ����8λ��Ϊ��żУ��λ��������24�ֽڵ��Զ��ü�*/  
    if (key_len & 0x00000007) return 0;  
  
    /*��������С�ж�*/  
    if (out_len < in_len) return 0;  
  
    /*����16������Կ*/  
    nKey = (key_len>>3)>3 ? 3 : (key_len>>3);  
    memset(m_SubKey, 0x00, sizeof(m_SubKey));  
    for ( i=0; i<nKey; i++)  
    {  
        SetSubKey(&m_SubKey[i], &Key[i<<3]);  
    }  
  
    if (bMode == ECB)  
    {  
        if (nKey == 1)  
        {  
            /*ÿ8�ֽڼ���*/  
            for (i=0,j=in_len>>3; i<j; ++i,Out+=8,In+=8)  
            {  
                DES(Out, In, &m_SubKey[0], bType);  
            }  
        }  
        else if (nKey == 2)  
        {  
            for (i=0,j=in_len>>3; i<j; ++i,Out+=8,In+=8)  
            {  
                DES(Out, In,  &m_SubKey[0], bType);  
                DES(Out, Out, &m_SubKey[1], bType==ENCRYPT?DECRYPT:ENCRYPT);  
                DES(Out, Out, &m_SubKey[0], bType);  
            }  
        }  
        else if (nKey == 3)  
        {  
            for (i=0,j=in_len>>3; i<j; ++i,Out+=8,In+=8)  
            {  
                DES(Out, In,  &m_SubKey[bType?2:0], bType);  
                DES(Out, Out, &m_SubKey[1],         bType==ENCRYPT?DECRYPT:ENCRYPT);  
                DES(Out, Out, &m_SubKey[bType?0:2], bType);  
            }  
        }  
        else  
        {  
            /*��Կ���Ȳ���*/  
            return 0;  
        }  
    }  
    else if (bMode == CBC)  
    {  
        if (cvecstr == NULL) return 0;  
  
        char cvec[8] = {0};  
        char cvin[8] = {0};  
  
        memcpy(cvec, cvecstr, 8);  
  
        if (nKey == 1)  
        {  
            for (i=0,j=in_len>>3; i<j; ++i,Out+=8,In+=8)  
            {  
                if (bType == ENCRYPT)  
                {  
                    for (k=0; k<8; ++k)  
                    {  
                        cvin[k] = In[k] ^ cvec[k];  
                    }  
                }  
                else  
                {  
                    memcpy(cvin, In, 8);  
                }  
  
                DES(Out, cvin, &m_SubKey[0], bType);  
  
                if (bType == ENCRYPT)  
                {  
                    memcpy(cvec, Out, 8);  
                }  
                else  
                {  
                    for (k=0; k<8; ++k)  
                    {  
                        Out[k] = Out[k] ^ cvec[k];  
                    }  
                    memcpy(cvec, cvin, 8);  
                }  
            }  
        }  
        else if (nKey == 2)  
        {  
            for (i=0,j=in_len>>3; i<j; ++i,Out+=8,In+=8)  
            {  
                if (bType == ENCRYPT)  
                {  
                    for ( k=0; k<8; ++k)  
                    {  
                        cvin[k] = In[k] ^ cvec[k];  
                    }  
                }  
                else  
                {  
                    memcpy(cvin, In, 8);  
                }  
  
                DES(Out, cvin, &m_SubKey[0], bType);  
                DES(Out, Out,  &m_SubKey[1], bType==ENCRYPT?DECRYPT:ENCRYPT);  
                DES(Out, Out,  &m_SubKey[0], bType);  
  
                if (bType == ENCRYPT)  
                {  
                    memcpy(cvec, Out, 8);  
                }  
                else  
                {  
                    for (k=0; k<8; ++k)  
                    {  
                        Out[k] = Out[k] ^ cvec[k];  
                    }  
                    memcpy(cvec, cvin, 8);  
                }  
            }  
        }  
        else if (nKey == 3)  
        {  
  
            for (i=0,j=in_len>>3; i<j; ++i,Out+=8,In+=8)  
            {  
                if (bType == ENCRYPT)  
                {  
                    for (k=0; k<8; ++k)  
                    {  
                        cvin[k] = In[k] ^ cvec[k];  
                    }  
                }  
                else  
                {  
                    memcpy(cvin, In, 8);  
                }  
  
                DES(Out, cvin, &m_SubKey[bType?2:0], bType);  
                DES(Out, Out,  &m_SubKey[1],         bType==ENCRYPT?DECRYPT:ENCRYPT);  
                DES(Out, Out,  &m_SubKey[bType?0:2], bType);  
  
                if (bType == ENCRYPT)  
                {  
                    memcpy(cvec, Out, 8);  
                }  
                else  
                {  
                    for (k=0; k<8; ++k)  
                    {  
                        Out[k] = Out[k] ^ cvec[k];  
                    }  
                    memcpy(cvec, cvin, 8);  
                }  
            }  
        }  
        else  
        {  
            /*��Կ���Ȳ���*/  
            return 0;  
        }  
    }  
    else  
    {  
        return 0;  
    }  
  
    return 1;  
}

int	ENC64(int ch)
{
	ch &= 0x3f;
	return	base64[ch];
}

int enbase64(char *buf, int n, char *outbuf)
{
	int	ch, cnt=0;
	char	*p;

	for (p = buf; n > 0; n -= 3, p += 3) {
		ch = *p >> 2;
		ch = ENC64(ch);
		outbuf[cnt++] = ch;

		ch = ((*p << 4) & 060) | ((p[1] >> 4) & 017);
		ch = ENC64(ch);
		outbuf[cnt++] = ch;

		ch = ((p[1] << 2) & 074) | ((p[2] >> 6) & 03);
		ch = (n < 2) ? '=' : ENC64(ch);
		outbuf[cnt++] = ch;

		ch = p[2] & 077;
		ch = (n < 3) ? '=' : ENC64(ch);
		outbuf[cnt++] = ch;
	}

	outbuf[cnt] = 0;

	return	cnt;
}

// ������: Crypt_3Des
// ����  : ʵ��3DES�ļ���
int Crypt_3Des(char* in, int in_len, char *out, int &out_len, char* key,int key_len, char* vi)
{
	
	if( in == 0 || out == 0 || in_len <= 0 || key ==0 || vi == 0 )
	{
		return -1;
	}

	if( out_len < ( ( ( in_len + 10 ) / 3 ) << 2 ) )//3DES��չ(+8)
	{
		return -2;
	}

	if( key_len != 8 && key_len != 16 && key_len != 24 || strlen( vi ) != 8 )
	{
		return -3;
	}

	int len = ((in_len) >> 3 << 3 )+ 8;//����Ϊ8�ı���
	char *data   = new char[len];
	memset( data, len-in_len, len );
	memcpy( data, in, in_len );

	if( Run3Des(ENCRYPT,CBC,data,len,key,key_len,out,out_len,vi) )
	{
		out_len = len;
		return out_len;
	}
	else
	{
		return 0;
	}
}


int	DEC64(char c)
{
	if (c=='+')
		return	62;
	if (c=='/')
		return	63;
	if ( c >= '0' && c <= '9' )
		return	52+(c-0x30);
	if ( c >= 'A' && c <= 'Z' )
		return	(c-0x41);
	if ( c >= 'a' && c <= 'z' )
		return	26+(c-0x61);

	return	-1;
}

int	unbase64(char *buf, int n, char *outbuf)
{
	int	ch, cnt=0;
	char	*p;

	while ('=' == buf[n-1])
		n--;

	for (p=buf ; n > 0; p += 4, n -= 4)
		if (n > 3) {
			ch = (DEC64(p[0]) << 2) | (DEC64(p[1]) >> 4);
			outbuf[cnt++] = ch;
			ch = (DEC64(p[1]) << 4) | (DEC64(p[2]) >> 2);
			outbuf[cnt++] = ch;
			ch = (DEC64(p[2]) << 6) | DEC64(p[3]);
			outbuf[cnt++] = ch;
		}
		else {
			if (n > 1) {
				ch = (DEC64(p[0]) << 2) | (DEC64(p[1]) >> 4);
				outbuf[cnt++] = ch;
			}
			if (n > 2) {
				ch = (DEC64(p[1]) << 4) | (DEC64(p[2]) >> 2);
				outbuf[cnt++] = ch;
			}
		}

		return	cnt;
}

// ������: DCrypt_3Des
// ����  : ʵ��3DES�Ľ���
int DCrypt_3Des(char* in, int in_len, char *out, int &out_len, char* key,int key_len, char* vi)
{	
	if( in == 0 || out == 0 || in_len <= 0 || key ==0 || vi == 0 )
	{
		return -1;
	}

	if( in_len > out_len )
	{
		return -2;
	}

	if( key_len != 8 && key_len != 16 && key_len != 24 && strlen( vi ) != 8 )
	{
		return -3;
	}

	if( Run3Des(DECRYPT,CBC,in,in_len,key,key_len,out,out_len,vi) )
	{
		out_len = in_len - out[in_len-1];
		out[out_len] = '\0';
		return out_len;
	}
	else
	{
		return 0;
	}
}


int  Crypt_3DesWithBase64(char* in, int in_len, char *out, int &out_len, char* key,int key_len, char* vi)
{

	if( in == 0 || out == 0 || in_len <= 0 || key ==0 || vi == 0 )
	{
		return -1;
	}

	if( out_len < ( ( ( in_len + 10 ) / 3 ) << 2 ) )//3DES��չ(+8)��BASE64ת��(*4/3)
	{
		return -2;
	}

	if( key_len != 8 && key_len != 16 && key_len != 24 || strlen( vi ) != 8 )
	{
		return -3;
	}


	char *data;
	char *encode;
	int encode_len;

	encode_len = ((in_len - 1) >> 3 << 3 )+ 8;//����Ϊ8�ı���
	data   = new char[encode_len];
	encode = new char[encode_len];
	memset(   data, encode_len-in_len, encode_len );
	memset( encode, 0, encode_len );

	memcpy( data, in, in_len );

	if( Run3Des(ENCRYPT,CBC,data,encode_len,key,key_len,encode,encode_len,vi) )
	{
		memset(    out, 0,    out_len );
		out_len = enbase64( encode, encode_len, out );
		delete []data;
		delete []encode;
		data   = NULL;
		encode = NULL;
		return out_len;
	}
	else
	{
		delete []data;
		delete []encode;
		data   = NULL;
		encode = NULL;
		return 0;
	}
}
int DCrypt_3DesWithBase64(char* in, int in_len, char *out, int &out_len, char* key,int key_len, char* vi)
{

	if( in == 0 || out == 0 || in_len <= 0 || key ==0 || vi == 0 )
	{
		return -1;
	}

	if( in_len > out_len )
	{
		return -2;
	}

	if( key_len != 8 && key_len != 16 && key_len != 24 && strlen( vi ) != 8 )
	{
		return -3;
	}

	char *decode = new char[in_len];
	int decode_len = 0;

	decode_len = unbase64( in, in_len, decode );


	if( Run3Des(DECRYPT,CBC,decode,decode_len,key,key_len,out,out_len,vi) )
	{
		out[decode_len -  out[decode_len-1] ] = '\0';
		out_len = strlen( out );
		delete decode;
		decode = NULL;
		return out_len;
	}
	else
	{
		delete decode;
		decode = NULL;
		return 0;
	}
}