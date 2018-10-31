// NameValue.cpp: implementation of the CNameValue class.
//
//////////////////////////////////////////////////////////////////////

#include "NameValue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CNameValue::CNameValue()
{

}

CNameValue::~CNameValue()
{

}

bool CNameValue::FillString(char *buf, char mark)
{
	int ret;
	int rec;
	int rec2;
	

	Cpubstrtime publog1;
	Cpubstrtime publog2;

	memset(m_dataBuf,0,sizeof(m_dataBuf));
	
	ret = strlen(buf);
	if (ret>=MAXAPIBUFLEN)
	{
		return false;
	}
	strcpy(m_dataBuf,buf);
	m_dataBuf[ret] = mark;
	m_dataBuf[ret+1] =0;
	if (publog1.FillStrings(m_dataBuf,mark)<0)
	{
		return false;
	}
	m_nvList.clear();
	rec = publog1.GetCount();
	for (int i=0;i<rec;i++)
	{
		memset(m_itemData,0,sizeof(m_itemData));
		publog1.GetAt(i,m_itemData,true);
		publog1.trim(m_itemData);
		strcat(m_itemData,"=");
		if (strlen(m_itemData)<1)
		{
			continue;
		}
		if (publog2.FillStrings(m_itemData,'=')<0)
		{
			continue;
		}
		rec2 = publog2.GetCount();
		if (rec2!=2)
		{
			continue;
		}
		_NAMEVALUE nv;
		memset(m_itemData2,0,sizeof(m_itemData2));
		publog2.GetAt(0,m_itemData2,true);
		if (strlen(m_itemData2)<1)
		{
			continue;
		}
		else
		{
			nv.name = m_itemData2;
			memset(m_itemData2,0,sizeof(m_itemData2));
			publog2.GetAt(1,m_itemData2,true);
			nv.value = m_itemData2;
			m_nvList.push_back(nv);
		}
		
	}

	return true;
}

bool CNameValue::FillString(char *buf, int mark)
{
	char cmark;
	cmark = mark;
	return FillString(buf,cmark);
}

bool CNameValue::GetValueByName(const char *name, char *value)
{
	int ret;
	for (int i=0;i<m_nvList.size();i++)
	{
		ret = m_nvList[i].name.length();
		if (strncmp(name,m_nvList[i].name.c_str(),ret) == 0)
		{
			strcpy(value,m_nvList[i].value.c_str());
			return true;
		}
	}
	return false;
}

bool CNameValue::GetValueByName(string name, string &value)
{
	for (int i=0;i<m_nvList.size();i++)
	{
		if (name.compare(m_nvList[i].name) == 0)
		{
			value = m_nvList[i].value;
			return true;
		}
	}
	return false;
}
bool CNameValue::GetValueByName(string name, int &value)
{
	for (int i=0;i<m_nvList.size();i++)
	{
		if (name.compare(m_nvList[i].name) == 0)
		{
			value = atoi(m_nvList[i].value.c_str());
			return true;
		}
	}
	return false;
}
bool CNameValue::GetValueByName(string name, long &value)
{
	for (int i=0;i<m_nvList.size();i++)
	{
		if (name.compare(m_nvList[i].name) == 0)
		{
			value = atol(m_nvList[i].value.c_str());
			return true;
		}
	}
	return false;
}
bool CNameValue::GetValueByName(string name, double &value)
{
	for (int i=0;i<m_nvList.size();i++)
	{
		if (name.compare(m_nvList[i].name) == 0)
		{
			value = atof(m_nvList[i].value.c_str());
			return true;
		}
	}
	return false;
}
string CNameValue::GetValueByName(string name)
{
	for (int i=0;i<m_nvList.size();i++)
	{
		if (name.compare(m_nvList[i].name) == 0)
		{
			return m_nvList[i].value;
		}
	}
	return "";
}

void CNameValue::NewPackage()
{
	m_nvList.clear();
}

int CNameValue::SetValueName(string name, string value)
{
	for (int i=0;i<m_nvList.size();i++)
	{
		if (m_nvList[i].name.compare(name) == 0 )
		{
			m_nvList[i].value = value;
			return 0;
		}
	}
	_NAMEVALUE nv;
	nv.name = name;
	nv.value = value;
	m_nvList.push_back(nv);
	return 1;
}
int CNameValue::SetValueName(string name, int value)
{
	char tmpchar[20];
	sprintf(tmpchar,"%d",value);
	return SetValueName(name,tmpchar);
}
int CNameValue::SetValueName(string name, long value)
{
	char tmpchar[20];
	sprintf(tmpchar,"%ld",value);
	return SetValueName(name,tmpchar);
}
int CNameValue::SetValueName(string name, double value)
{
	char tmpchar[20];
	sprintf(tmpchar,"%.2f",value);
	return SetValueName(name,tmpchar);
}
int CNameValue::GetBuffer(char *buf, char mark)
{
	string buffer;
	GetBuffer(buffer,mark);
	memcpy(buf,buffer.c_str(),buffer.length());
	return buffer.length();
}
int CNameValue::GetBuffer(string &buf, char mark)
{
	char tmpchar[2];
	tmpchar[0]=mark;
	tmpchar[1]=0;
	buf = tmpchar;
	for (int i=0;i<m_nvList.size();i++)
	{
		buf= buf +m_nvList[i].name;
		buf = buf +"=";
		buf = buf +m_nvList[i].value;
		buf = buf+tmpchar;
	}
	
	return buf.length();
}