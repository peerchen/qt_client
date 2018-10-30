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
//	Description	: �����������ࣺ0--Ĭ��ΪӢ�ģ�1--�������ģ�2--��۷������ģ�3--̨�己������
//	Input  args	: int nLanguageType �� ����  
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
	//���浱ǰ�޸ĵ����Ե�XML
	CMarkupSTL xml; 
	if (!xml.Load( GetXmlFileName( (char*)g_sXMLFileName ).c_str() ))// ����XML�ĵ�
	{
		return;
	}       

	// ���� position
	xml.ResetPos();
	// ���Ҵ洢�������ýڵ�
	xml.FindChildElem("language");
	// �������õ�ǰ��������
	xml.SetAttrib("selected", m_sLanguageType.c_str());
	// �����µ�XMLд���ļ�
	xml.Save( GetXmlFileName( (char*)g_sXMLFileName ).c_str() );
	
	//////////////////////////////////////////////////////////////////////////
	//���¼��ز�ˢ�����е�����
	m_mapLang.clear();				// �������
	initXML((char*)g_sXMLFileName);	// ���¼���
	
	// ������Ϣ֪ͨˢ�½��棬����ù㲥��ʽ֪ͨ
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
//	Description	: ��ȡKEY��Ӧ�������������� 
//	Input  args	: LPCTSTR lpKey �� �����ֶε�KEY  
//	Output args	: 
//	Return type	: void  
//////////////////////////////////////////////////////////////////////////
std::string CLanguage::GetString(std::string sKey)
{ 
	return m_mapLang[ sKey ];
}

//////////////////////////////////////////////////////////////////////////
//	Function	: CLanguage::initXML
//	Description	: ��ȡ����XML�ļ����洢����
//	Input  args	: LPCTSTR lpFileName �� ����XML�Ĳ���·�����ļ���������չ����
//	Output args	: 
//	Return type	: BOOL  �� TRUE-�ɹ���FALSE-ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CLanguage::initXML(char* szFileName)
{ 
	// �����map
	m_mapLang.clear();

	CMarkupSTL xml; 
	
	if (!xml.Load( GetXmlFileName(szFileName).c_str() ))// ����XML�ĵ�
	{
		return FALSE;
	}   

	// ��ʼ���� language �ڵ�
	xml.FindChildElem("language");
	 
	std::string sName, sValue;
	
	// ȡ��ǰ�ڵ�����ԣ�����ǰ����ʹ�õ�����
	m_sLanguageType = xml.GetAttrib(xml.GetAttribName(0).c_str());

	// ����Position
	xml.ResetPos();
	// ���δ�ҵ��κ��ӽڵ���ֱ�ӷ���
	if ( ! xml.FindChildElem() )
		return FALSE;
	 
	// ���뵱ǰ�ڵ�
	xml.IntoElem();

	// ȡ��ǰ�ڵ�Ľڵ��ʶ
	std::string sTag = xml.GetTagName();
			 
	BOOL bFound = TRUE;

	if (sTag == "lang")
	{
		while(bFound)
		{
			sName = xml.GetAttribName(0);			// ��ǰ�ڵ������
			sValue= xml.GetAttrib(sName.c_str());

			// �ҵ����õ��������࣬��ʵ�м���
			if (sValue == m_sLanguageType)
			{
				bFound = xml.FindChildElem();

				if (bFound)
				{
					xml.IntoElem(); // �����ӽڵ�
				  
					while(bFound)
					{  
						// id
						sName= xml.GetAttrib(xml.GetAttribName(0).c_str()); 
						// Value
						sValue= xml.GetAttrib(xml.GetAttribName(1).c_str()); 
						 
						m_mapLang[ sName ] = sValue;//��ӵ�map��

						bFound = xml.FindElem("content");// ������һ�� content
					}
					
					return TRUE;// �Ѿ������õ���Ϣ��ȡ��map�У����˳�
				}
			}

			bFound = xml.FindElem("lang");// ������һ�� lang
		} 

		return FALSE;
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//	Function	: CLanguage::GetXmlFile
//	Description	: 
//	Input  args	: char *pFileName �� �ļ���
//	Output args	: 
//	Return type	: std::string  �� �ļ�������
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
//	Input  args	: HWND hWnd �� ��ע�ᴰ���hwnd
//	Output args	: 
//	Return type	: NULL
//////////////////////////////////////////////////////////////////////////
void CLanguage::Reg(HWND hWnd)
{
	m_RegHwnd.push_back(hWnd);
}