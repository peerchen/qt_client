

#ifndef _HQJYShareStruct_h
#define _HQJYShareStruct_h

//消息id "YLLLSHS"

static unsigned int HQJY_ExchangeMsgID = ::RegisterWindowMessage("YLLLSHS");


// 消息id
#define HQJY_OpenKeyboard		0x0001 // 打开键盘

#define HQJY_RequestCodeData	0x0002 // 请求实时代码数据
#define HQJY_RequestMaiDanData  0x0004 // 请求埋单行情数据


// 
struct HQJY_Header	// 数据交换头
{
   int  m_nMsg;			// 指向消息类型,参见HQJY_*定义
   int  m_nSize;		// 指向数据长度
   char m_szData[1];	// 实际数据指真
};

struct HQJY_MSG  // 是 windows MSG 子集
{
    HWND				hwnd;		
    unsigned int		message;	
    unsigned int        wParam;
    unsigned long       lParam;
};

struct HQJY_CodeInfo
{
	short	m_cCodeType;	// 证券类型（可以指向市场大类）
	char	m_cCode[6];		// 证券代码
};


/*
说明：

1、m_nMsg == HQJY_OpenKeyboard 时
m_szData 指向HQJY_MSG结构

2、m_nMsg == HQJY_RequestCodeData,HQJY_RequestMaiDanData 时
m_szData 指向一组HQJY_CodeInfo结构,多少由m_nSize指定


*/

#endif // _HQJYShareStruct_h

