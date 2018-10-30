#pragma once
#include <map>
#include <vector>
#include "MarkupSTL.h"
using namespace std;

#define WM_LANGUAGE_CHANG WM_USER+3000 // �������Ϣ����֪ͨ�����л�

class CLanguage
{
public:
	CLanguage(void);
	~CLanguage(void);
	
	typedef map<std::string , std::string > mapLang;
	typedef vector< HWND > RegHwnd;

private:
	mapLang m_mapLang;			// ���ڴ洢����ֵ
	std::string m_sLanguageType;//��ǰ����������
	RegHwnd m_RegHwnd;

private:
	BOOL initXML(char* szFileName);
	std::string GetXmlFileName(char* szFileName);
	std::string GetLangString(int nLanguageType);

public:
	/// �����������ࣺ0--Ĭ��ΪӢ�ģ�1--�������ģ�2--��۷������ģ�3--̨�己������
	void SetLanguage(int nLanguageType);

	/// ��ȡ key ��Ӧ����������
	std::string GetString(std::string lpKey);

	/// ע�ᴰ�嵽������ģ�飬������Ϣ֪ͨ
	void Reg(HWND hWnd);
};

