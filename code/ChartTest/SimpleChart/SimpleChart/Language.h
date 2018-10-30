#pragma once
#include <map>
#include <vector>
#include "MarkupSTL.h"
using namespace std;

#define WM_LANGUAGE_CHANG WM_USER+3000 // 定义该消息用于通知语言切换

class CLanguage
{
public:
	CLanguage(void);
	~CLanguage(void);
	
	typedef map<std::string , std::string > mapLang;
	typedef vector< HWND > RegHwnd;

private:
	mapLang m_mapLang;			// 用于存储语言值
	std::string m_sLanguageType;//当前的语言种类
	RegHwnd m_RegHwnd;

private:
	BOOL initXML(char* szFileName);
	std::string GetXmlFileName(char* szFileName);
	std::string GetLangString(int nLanguageType);

public:
	/// 设置语言种类：0--默认为英文，1--简体中文，2--香港繁体中文，3--台湾繁体中文
	void SetLanguage(int nLanguageType);

	/// 获取 key 对应的语言种类
	std::string GetString(std::string lpKey);

	/// 注册窗体到本语言模块，用于消息通知
	void Reg(HWND hWnd);
};

