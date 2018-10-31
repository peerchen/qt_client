/****************************************************************/
/*																*/
/*  XmlDocument.cpp												*/
/*																*/
/*  Implementation of the CXmlDocument class.					*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2003						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 09 February 2003								*/
/*																*/
/****************************************************************/

#include "stdafx.h"
#include "XmlDocument.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CXmlElement::GetValue(CString attribute)
{
	CString ret = m_strAttributes;
	int pos = m_strAttributes.Find(attribute + "=");
	if (pos>=0)
	{
		ret.Delete(0,pos+attribute.GetLength()+2);
		int n=ret.Find("\"");
		if (n>=0)
			ret = ret.Left(n);
	}
	else 
		ret = "";
	
	return ret;	
}

BOOL CXmlElement::SetValue(CString attribute, CString value)
{
	CString ret = m_strAttributes;
	int pos = m_strAttributes.Find(attribute + "=");
	if(pos >= 0)
	{
		ret.Delete(0,pos+attribute.GetLength()+2);
		int n= ret.Find("\"");
		if(n>=0)
			ret = ret.Left(n);
	}
	else
		ret ="";
	if(ret!="")
	{
		m_strAttributes.Replace(ret,value);
		return TRUE;
	}
	else
		return FALSE;
}

CXmlDocument::CXmlDocument()
{
	m_nLevel = -1;
}

CXmlDocument::~CXmlDocument()
{

}


/********************************************************************/
/*																	*/
/* Function name : DeleteContents									*/
/* Description   : Initialize variables to their initial values.	*/
/*																	*/
/********************************************************************/
void CXmlDocument::DeleteContents()
{
	// clean up any previous data
	while(!m_RootElement.m_ChildElements.IsEmpty())
	{
		delete m_RootElement.m_ChildElements.RemoveHead();
	}
	m_pCurElement = &m_RootElement;
	m_pCurElement->m_pParentElement = NULL;
	m_RootElement.m_strName = "";
	m_RootElement.m_strData = "";
	m_RootElement.m_strAttributes = "";
	m_RootElement.m_strFind = "";
	m_RootElement.m_posFind = NULL;
}


/********************************************************************/
/*																	*/
/* Function name : Parse											*/
/* Description   : Parse XML data.									*/
/*																	*/
/********************************************************************/
BOOL CXmlDocument::Parse(LPCTSTR lpszString)
{
	// clean previous document data
	DeleteContents();

	// save string
	m_strXml = lpszString;

	BOOL bInsideTag = FALSE;

	CString strTag, strData, strResult;

	for(int i=0; i<m_strXml.GetLength(); i++)
    {
        TCHAR ch;
        
		// begin of tag ?
		if(strData.Find("<![CDATA[") !=-1)
		{
			for(;i<m_strXml.GetLength();i++)
			{
				ch = m_strXml[i];
				strData+=ch;
				if(ch=='>' && m_strXml[i-1]==']' && m_strXml[i-2]==']')
				{
					i++;
					break;
				}
			}			
		}
		ch= m_strXml[i];
		if(ch == '<'/* && m_strXml[i+1]!='!' */)//del by shaken20050729
        {
			strTag += ch;

			// add data to element
			m_pCurElement->m_strData = strData;
			m_pCurElement->m_strData.Replace("<![CDATA[","");
			m_pCurElement->m_strData.Replace("]]>","");
			// trim spaces
			m_pCurElement->m_strData.TrimLeft();
			m_pCurElement->m_strData.TrimRight();

			// clear data
            strData = "";
            
			// processing tag...
			bInsideTag = TRUE;
            continue;        
        }
		// end of tag ?
        if(ch == '>' && m_strXml[i-1]!=']')
        {
            strTag += ch;

			// determine type and name of the tag
			int nType = ValidateTag(strTag, strResult);

			// clear tag
            strTag = "";

			// skip errors/comments/declaration
			if (nType == -1)
			{
				bInsideTag = FALSE;//modify by shaken　觉得加上此句就可正确解析注释20050729
				continue;
			}

			// start or start-end tag -> add new element
			if(nType == 0 || nType == 2)
			{
				// currently processing root element ?
				if (m_RootElement.m_strName.IsEmpty())
				{
					// split name and attributes
					int nPos = strResult.Find(' ');
					if (nPos != -1)
					{
						// set properties of root element
						m_RootElement.m_strName = strResult.Left(nPos);
						m_RootElement.m_strAttributes = strResult.Mid(nPos+1);
						// trim spaces
						m_RootElement.m_strAttributes.TrimLeft();
						m_RootElement.m_strAttributes.TrimRight();
					}
					else
					{
						m_RootElement.m_strName = strResult;
					}
				}
				else
				{
					// create new element
					CXmlElement *pElement = new CXmlElement;

					pElement->m_pParentElement = m_pCurElement;
					
					// split name and attributes
					int nPos = strResult.Find(' ');
					if (nPos != -1)
					{
						// set properties of current element
						pElement->m_strName = strResult.Left(nPos);
						pElement->m_strAttributes = strResult.Mid(nPos+1);
						// trim spaces
						pElement->m_strAttributes.TrimLeft();
						pElement->m_strAttributes.TrimRight();
					}
					else
					{
						pElement->m_strName = strResult;
					}
					m_pCurElement->m_ChildElements.AddTail(pElement);
					m_pCurElement = pElement;
				}
			}

			// end or start-end tag -> finished with current tag
			if(nType == 1 || nType == 2)
			{
				// go back to parent level
				if (m_pCurElement->m_pParentElement != NULL)
					m_pCurElement = m_pCurElement->m_pParentElement;
			}

			// processing data...
			bInsideTag = FALSE;
            continue;
        }
        
		if(bInsideTag)
		{
			// append character to tag
            strTag += ch;
		}
        else
        {
			// append character to data
			strData += ch;
        }
    }
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : ValidateTag										*/
/* Description   : Determine type and name of the tag.				*/
/*				   0 = start tag									*/
/*				   1 = end tag										*/
/*				   2 = start-end tag								*/
/*				   -1 = comments or declaration						*/
/*																	*/
/********************************************************************/
int CXmlDocument::ValidateTag(CString &strTag, CString &strResult)
{
	strResult = "";

	if (strTag.IsEmpty())
		return -1;

    TCHAR ch;
	TCHAR chPrevious = '0';
	
	int nResult = 0;
	int nCount = 0;

	// determine tag type
    while(nCount <strTag.GetLength())
    {
        // get next character
		ch = strTag[nCount++];

		// skip comments '<!' and declaration '<?'
        if ((chPrevious == '<' && ch == '!')/*||(chPrevious == '<' && ch == '?')*/)
		{
            return -1;
		}
        else
		// is it an end-tag '</' ?
        if(chPrevious =='<' && ch == '/') 
        {
            nResult = 1;
        }
        else
		// is it a start-end-tag '<..../>' ?
        if(chPrevious =='/' && ch == '>') 
        {
            nResult = 2;
			// remove last character
			strResult.Delete(strResult.GetLength()-1, 1);
        }
        else 
		if(ch != '<' && ch != '>')
		{
			// add character
            strResult += ch;
        }
        chPrevious = ch;
    }
	return nResult;
}



/********************************************************************/
/*																	*/
/* Function name : GetFirstChild									*/
/* Description   : Get first child of element.						*/
/*																	*/
/********************************************************************/
CXmlElement *CXmlDocument::GetFirstChild(CXmlElement *pElement) 
{
	pElement->m_posFind = NULL;
	
	POSITION pos = pElement->m_ChildElements.GetHeadPosition();
	if (pos != NULL)
	{
		CXmlElement *pResult = (CXmlElement *)pElement->m_ChildElements.GetNext(pos);
		pElement->m_posFind = pos;
		return pResult;
	}
	return NULL;
}


/********************************************************************/
/*																	*/
/* Function name : GetNextSibling									*/
/* Description   : Get next child of specified element.				*/
/*																	*/
/********************************************************************/
CXmlElement *CXmlDocument::GetNextSibling(CXmlElement *pElement) 
{
	if (pElement->m_posFind)
		return (CXmlElement *)pElement->m_ChildElements.GetNext(pElement->m_posFind);
	else
		return NULL;
}


/********************************************************************/
/*																	*/
/* Function name : FindElement										*/
/* Description   : Find first occurence of specified tag.			*/
/*																	*/
/********************************************************************/
CXmlElement *CXmlDocument::FindElement(CXmlElement *pElement, LPCTSTR lpszName) 
{
	pElement->m_posFind = NULL;
	
	pElement->m_strFind = lpszName;
	
	POSITION pos = pElement->m_ChildElements.GetHeadPosition();
	while (pos != NULL)
	{
		CXmlElement *pResult = (CXmlElement *)pElement->m_ChildElements.GetNext(pos);
		if (pResult->m_strName==lpszName)
		{
			pElement->m_posFind = pos;
			return pResult;
		}
	}
	return NULL;
}


/********************************************************************/
/*																	*/
/* Function name : FindNextElement									*/
/* Description   : Find next occurence of specified tag				*/
/*																	*/
/********************************************************************/
CXmlElement *CXmlDocument::FindNextElement(CXmlElement *pElement) 
{
	while(pElement->m_posFind != NULL)
	{
		CXmlElement *pResult = (CXmlElement *)pElement->m_ChildElements.GetNext(pElement->m_posFind);
		if (pResult->m_strName.CompareNoCase(pElement->m_strFind) == 0)
		{
			return pResult;
		}
	}
	return NULL;
}


/********************************************************************/
/*																	*/
/* Function name : AddElement										*/
/* Description   : Add new element									*/
/*																	*/
/********************************************************************/
CXmlElement *CXmlDocument::AddElement(CXmlElement *pElement, LPCTSTR lpszName, LPCTSTR lpszData, LPCTSTR lpszAttributes) 
{
	CXmlElement *pNewElement = new CXmlElement;

	pNewElement->m_strName = lpszName;
	pNewElement->m_strName.TrimLeft();
	pNewElement->m_strName.TrimRight();

	if (lpszData)
	{
		pNewElement->m_strData = lpszData;
		pNewElement->m_strData.Replace("&", "&amp;");
		pNewElement->m_strData.Replace("<", "&lt;");
		pNewElement->m_strData.Replace(">", "&gt;");
	}
	if (lpszAttributes)
		pNewElement->m_strAttributes = lpszAttributes;
	
	pElement->m_ChildElements.AddTail(pNewElement);

	return pNewElement;
}


/********************************************************************/
/*																	*/
/* Function name : Generate											*/
/* Description   : Generate a XML string from elements				*/
/*																	*/
/********************************************************************/
CString CXmlDocument::Generate()
{
	CString strResult="";

//	strResult = "<?xml version=\"1.0\"?>\r\n";

	CString strTag;

	m_nLevel = -1;
	CreateTag(&m_RootElement, strTag);

	strResult += strTag;
	return strResult;
}


/********************************************************************/
/*																	*/
/* Function name : CreateTag										*/
/* Description   : Create tag and tags from all child elements		*/
/*																	*/
/********************************************************************/
BOOL CXmlDocument::CreateTag(CXmlElement *pElement, CString &strResult)
{
	int i;

	m_nLevel++;

	// make sure we start empty
	strResult = "";

	// add spaces before start-tag
	for (i=0; i<m_nLevel; i++)
		strResult += " ";

	// add start-tag
	strResult += "<";
	strResult += pElement->m_strName;

	if (!pElement->m_strAttributes.IsEmpty())
	{
		strResult += " ";
		strResult += pElement->m_strAttributes;
	}
	
	strResult += ">";

	if (!pElement->m_strData.IsEmpty())
	{
		strResult += pElement->m_strData;
	}
	else
	{
		strResult += "\r\n";
	}

	// process child elements
	POSITION pos = pElement->m_ChildElements.GetHeadPosition();
	while (pos != NULL)
	{
		CXmlElement *pChildElement = (CXmlElement *)pElement->m_ChildElements.GetNext(pos);

		CString strTag;
		CreateTag(pChildElement, strTag);
		strResult += strTag;
	}
	
	if (pElement->m_strData.IsEmpty())
	{
		// add spaces before end tag
		for (i=0; i<m_nLevel; i++)
			strResult += " ";
	}

	// add end-tag
	if(pElement->m_strName!= "?xml")
	{
	strResult += "</";
	strResult += pElement->m_strName;
	strResult += ">\r\n";
	}

	m_nLevel--;
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : Load												*/
/* Description   : Load document from file							*/
/*																	*/
/********************************************************************/
BOOL CXmlDocument::Load(LPCTSTR lpszFileName)
{
	CWaitCursor waitCursor;

	CString strXML;

	try
	{
		CFile inputFile(lpszFileName, CFile::modeRead);
	
		DWORD dwLength = inputFile.GetLength();

		inputFile.Read(strXML.GetBuffer(dwLength), dwLength);
//		strXML.ReleaseBuffer();

		inputFile.Close();
	}
	catch(CFileException *ex)
	{
		TRACE("CXmlDocument::Load");
		ex->Delete();
		return FALSE;
	}
	return Parse(strXML);
}


/********************************************************************/
/*																	*/
/* Function name : Store											*/
/* Description   : Save document to file							*/
/*																	*/
/********************************************************************/
BOOL CXmlDocument::Store(LPCTSTR lpszFileName)
{
	CWaitCursor waitCursor;

	CString strXML = Generate();

	try
	{
		CFile outputFile(lpszFileName, CFile::modeCreate | CFile::modeWrite);
		outputFile.Write(strXML, strXML.GetLength());
		outputFile.Close();
	}
	catch(CFileException *ex)
	{
		TRACE("CXmlDocument::Store");
		ex->Delete();
		return FALSE;
	}
	return TRUE;
}


