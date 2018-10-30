
/*******************************************************************************
 * Copyright (c)2003, Ѷ��������޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ�BaseDefine.h
 * �ļ���ʶ�����ú궨��
 * ժ    Ҫ�����ú궨��
 *
 * ��ǰ�汾��dfx2003
 * ��    �ߣ�Ѷ������
 * ������ڣ�2003-08-26
 *
 * ȡ���汾��2.0
 * ԭ �� �ߣ�Ѷ������
 * ������ڣ�2003-04-01
 * ��	 ע��
 *******************************************************************************/

#ifndef YLS_BASEDEFINE_H
#define YLS_BASEDEFINE_H
#pragma	pack(1)


// ��ͬ�����ڴ潻��
enum YlsAllocType {charType,InfoIndexType,InfoIndexSubType,YlsDrawOtherDataType,HSDoubleType,HSCString,HSCStringCopy};
typedef void* ( *YlsExternAlloc )( long nCurSize,int nType /*= 0*/ );
typedef void  ( *YlsExternFree )( void* pData, int nType /*= 0*/ );

#define _delObject(p)    { if(p) {delete p;   p = NULL; } }
#define _delArray(p)	 { if(p) {delete[] p; p = NULL; } }
#define _delArrayObj(p)  { for(int i = p.GetSize() - 1; i >= 0; i--) { delete p.GetAt(i); } p.RemoveAll(); }

#define YlsInvalidateMinValues 0x80000000
#define YlsInvalidateMaxValues 0x7fffffff

#ifndef PERIOD_TYPE_DAY
#define PERIOD_TYPE_DAY			0x0010		//�������ڣ���
#define PERIOD_TYPE_MINUTE1		0x00C0		//�������ڣ�1����
#define PERIOD_TYPE_MINUTE5		0x0030		//�������ڣ�5����
#define PERIOD_TYPE_SECOND1		0x00E0		//�������ڣ�1����
#endif	/*PERIOD_TYPE_DAY*/

#define PERIOD_TYPE_MINUTE15	0x0040		//�������ڣ�15����
#define HISDAY					0x0020		//�������ڣ���
#define MINUTE30				0x0050		//�������ڣ�30����
#define MINUTE60				0x0060		//�������ڣ�60����
#define PERIOD_TYPE_MINUTE120	0x0070		//�������ڣ�120����
#define WEEK					0x0080		//�������ڣ���
#define MONTH					0x0090		//�������ڣ���

#define PERIOD_TYPE_DAY_ANY		0x00A0		//������������
#define MINUTE_ANY				0x00B0		//������������
#define SECOND_ANY				0x00D0		//����������

//��ֵ
#ifndef SS_MINTIME
#define SS_MINTIME		100000000		//��Сʱ��
#endif

#define SI_VERSION			0xFF
#define SD_VERSION			1

#define PH_REPLY			0x8000		//Ӧ��
#define PH_ASK				0x4000		//����
#define PH_ZIP				0x2000		//ѹ������
#define PH_HTML				0x1000		//���ı�

//��������ʱ����ѹ���������󳤶ȣ������˳��Ⱥ󣬾���ѹ����
#define TS_MAXUNZIPSIZE		(1024 * 5)

#define TEXTDATA				0x0B00		//�ı���Ϣ
#define SHATEXTDATA				0x0B01		//�Ϻ�֤������Ϣ
#define SZNTEXTDATA				0x0B02		//����֤������Ϣ
#define QLTEXTDATA				0x0B03		//Ǭ¡��Ϣ
#define QSTEXTDATA				0x0B04		//ȯ����Ϣ
#define ZLTEXTDATA				0x0B05		//��������
#define QTTEXTDATA				0x0B06		//��������

#define DISKDATA				0x0C10		//�û��˴���DISK�����ݽṹ
#define WRITEDATA				0x0C11		//�û��˽��յ���վ���ݺ󣬴���DISK�����ݽṹ
#define ASKDATA					0x0C12		//�û�����DISK��������
#define PREASKDATA				0x0C13		//������վ���ӵ������, �û�����DISK��������

#define ST_BUCKETSIZE	    1000 // ��ϸȱʡ��С
#define HBS_BUCKETSIZE		100  // ���������ݴ�С
#define MAX_TRACE			10   // ��ʷ�ɽ���ϸ���ݽṹ

#pragma	pack()
#endif // YLS_BASEDEFINE_H
