#include "StdAfx.h"
#include "Language.h"

const static char* g_sXMLFileName = "Lang.xml";
CLanguage::CLanguage(void)
{  
	initXML((char*)g_sXMLFileName);
}


CLanguage::~CLanguage(void)
{
	m_mapLang.clear();
}
 
//////////////////////////////////////////////////////////////////////////
//	Function	: CLanguage::SetLanguage
//	Description	: 设置语言种类：0--默认为英文，1--简体中文，2--香港繁体中文，3--台湾繁体中文
//	Input  args	: int nLanguageType → 如上  
//	Output args	: 
//	Return type	: void  
//////////////////////////////////////////////////////////////////////////
void CLanguage::SetLanguage(int nLanguageType)
{ 
	if (m_sLanguageType != GetLangString( nLanguageType ))
		m_sLanguageType = GetLangString( nLanguageType );
	else
		return;

	//////////////////////////////////////////////////////////////////////////
	//保存当前修改的语言到XML
	CMarkupSTL xml; 
	if (!xml.Load( GetXmlFileName( (char*)g_sXMLFileName ).c_str() ))// 解析XML文档
	{
		return;
	}       

	// 重置 position
	xml.ResetPos();
	// 查找存储语言配置节点
	xml.FindChildElem("language");
	// 重新设置当前语言配置
	xml.SetAttrib("selected", m_sLanguageType.c_str());
	// 将更新的XML写入文件
	xml.Save( GetXmlFileName( (char*)g_sXMLFileName ).c_str() );
	
	//////////////////////////////////////////////////////////////////////////
	//重新加载并刷新所有的语言
	m_mapLang.clear();				// 清楚缓存
	initXML((char*)g_sXMLFileName);	// 重新加载
	
	// 发送消息通知刷新界面，最好用广播方式通知
	for(RegHwnd::iterator it=m_RegHwnd.begin();it!=m_RegHwnd.end();it++)
	{
		::SendMessageA((HWND)(*it), WM_LANGUAGE_CHANG, 0, 0);
	}
}

std::string CLanguage::GetLangString(int nLanguageType)
{
	std::string sLangString("");

	switch(nLanguageType)
	{
	case 0:
		sLangString = "EN_US";
		break;
	case 1:
		sLangString = "ZH_CN";
		break;
	case 2:
		sLangString = "ZH_HK";
		break;
	case 3:
		sLangString = "ZH_TW";
		break;
	default:
		sLangString = "ZH_CN";
		break;
	}

	return sLangString;
}

//////////////////////////////////////////////////////////////////////////
//	Function	: CLanguage::GetString
//	Description	: 获取KEY对应的语言描述文字 
//	Input  args	: LPCTSTR lpKey → 语言字段的KEY  
//	Output args	: 
//	Return type	: void  
//////////////////////////////////////////////////////////////////////////
std::string CLanguage::GetString(std::string sKey)
{ 
	return m_mapLang[ sKey ];
}

//////////////////////////////////////////////////////////////////////////
//	Function	: CLanguage::initXML
//	Description	: 读取本地XML文件到存储对象
//	Input  args	: LPCTSTR lpFileName → 本地XML的不含路径的文件名（含扩展名）
//	Output args	: 
//	Return type	: BOOL  → TRUE-成功，FALSE-失败
//////////////////////////////////////////////////////////////////////////
BOOL CLanguage::initXML(char* szFileName)
{ 
	// 先清除map
	m_mapLang.clear();

	CMarkupSTL xml; 
	
	if (!xml.Load( GetXmlFileName(szFileName).c_str() ))// 解析XML文档
	{
		return FALSE;
	}   

	// 开始查找 language 节点
	xml.FindChildElem("language");
	 
	std::string sName, sValue;
	
	// 取当前节点的属性，即当前语言使用的种类
	m_sLanguageType = xml.GetAttrib(xml.GetAttribName(0).c_str());

	// 重置Position
	xml.ResetPos();
	// 如果未找到任何子节点则直接返回
	if ( ! xml.FindChildElem() )
		return FALSE;
	 
	// 进入当前节点
	xml.IntoElem();

	// 取当前节点的节点标识
	std::string sTag = xml.GetTagName();
			 
	BOOL bFound = TRUE;

	if (sTag == "lang")
	{
		while(bFound)
		{
			sName = xml.GetAttribName(0);			// 当前节点的语言
			sValue= xml.GetAttrib(sName.c_str());

			// 找到配置的语言种类，并实行加载
			if (sValue == m_sLanguageType)
			{
				bFound = xml.FindChildElem();

				if (bFound)
				{
					xml.IntoElem(); // 进入子节点
				  
					while(bFound)
					{  
						// id
						sName= xml.GetAttrib(xml.GetAttribName(0).c_str()); 
						// Value
						sValue= xml.GetAttrib(xml.GetAttribName(1).c_str()); 
						 
						m_mapLang[ sName ] = sValue;//添加到map中

						bFound = xml.FindElem("content");// 查找下一个 content
					}
					
					return TRUE;// 已经将可用的信息读取到map中，则退出
				}
			}

			bFound = xml.FindElem("lang");// 查找下一个 lang
		} 

		return FALSE;
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//	Function	: CLanguage::GetXmlFile
//	Description	: 
//	Input  args	: char *pFileName → 文件名
//	Output args	: 
//	Return type	: std::string  → 文件体内容
//////////////////////////////////////////////////////////////////////////
std::string CLanguage::GetXmlFileName(char *szFileName) 
{
    const long nPathSize = 2048;
    char sCurrentFile[nPathSize];
    GetModuleFileNameA(NULL, sCurrentFile, nPathSize);
    std::string sCurrentDir = sCurrentFile;
    long pos = (long)sCurrentDir.rfind("\\");
    sCurrentDir = sCurrentDir.substr(0, pos);
    sCurrentDir += "\\";
    sCurrentDir += szFileName;

	return sCurrentDir; 
}

//////////////////////////////////////////////////////////////////////////
//	Function	: CLanguage::Reg
//	Description	: 
//	Input  args	: HWND hWnd → 被注册窗体的hwnd
//	Output args	: 
//	Return type	: NULL
//////////////////////////////////////////////////////////////////////////
void CLanguage::Reg(HWND hWnd)
{
	m_RegHwnd.push_back(hWnd);
}