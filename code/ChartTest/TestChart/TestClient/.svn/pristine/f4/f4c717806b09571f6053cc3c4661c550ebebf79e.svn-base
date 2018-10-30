/*******************************************************************************
* Copyright (c)2003, 雁联计算系统有限公司
* All rights reserved.
*
* 文件名称：*.h
* 文件标识：
* 摘    要：
*
* 当前版本：YLink1.2
* 作    者：YLink王工
* 完成日期：2005
*
* 备    注：
*
* 修改记录：
*
*******************************************************************************/



#ifndef YlsWinDef_h_
#define YlsWinDef_h_

struct __POSITION {};
typedef __POSITION* POSITION;

// Standard constants
#undef FALSE
#undef TRUE
#undef NULL

#define FALSE   0
#define TRUE    1
#define NULL    0

#ifndef BEFORE_START_POSITION
#define BEFORE_START_POSITION ((POSITION)-1L)
#endif


#define far
#define near

//
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
//typedef CONST void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

#define INFINITE            0xFFFFFFFF  // Infinite timeout

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#endif

typedef unsigned int UINT_PTR, *PUINT_PTR;
typedef unsigned long ULONG_PTR, *PULONG_PTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;

typedef unsigned long ULONGLONG;

typedef unsigned long ULONG;

typedef unsigned int  SIZE_T;// *PSIZE_T;
typedef unsigned long SSIZE_T;// *PSSIZE_T;

typedef int INT_PTR, *PINT_PTR;

typedef const char *	LPCTSTR;


#define ERROR_SUCCESS            0L
#define ERROR_ALREADY_EXISTS   183L

#define ERROR_DELETE            100L // 删除后再创建,对于linux


typedef unsigned int             WPARAM;
typedef unsigned long            LPARAM;
typedef unsigned long            LRESULT;

#define LONGLONG time_t

#ifndef _MAX_PATH
#	define _MAX_PATH   260 // 256 //260 /* max. length of full pathname */
#	define _MAX_DRIVE  3   /* max. length of drive component */
#	define _MAX_DIR    256 /* max. length of path component */
#	define _MAX_FNAME  256 /* max. length of file name component */
#	define _MAX_EXT    256 /* max. length of extension component */
#endif


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define INVALID_HANDLE_VALUE  ((int)(-1))

typedef UINT_PTR        SOCKET;

#define WINAPI

typedef void *HANDLE;

typedef char *	LPSTR;

typedef unsigned int size_t;

typedef const CHAR* LPCSTR;

typedef WORD WCHAR;

typedef const WCHAR * LPCWSTR;

//#ifndef		strncasecmp
//#define		strncasecmp	strnicmp
//#endif

#define ASSERT(f)          (f)
#define ATLASSERT(f)	   (f)
#define ASSERT_VALID(pOb)  (pOb)
#define ASSERT_KINDOF(class_name, object)

#ifndef ULONG_MAX
#define ULONG_MAX     0xffffffffUL
#endif

#define FILE_SHARE_READ						0x00000001  
#define FILE_SHARE_WRITE					0x00000002  
#define FILE_SHARE_DELETE					0x00000004  
#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_DEVICE               0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME;

#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))

#endif
