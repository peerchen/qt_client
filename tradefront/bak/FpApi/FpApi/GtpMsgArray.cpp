#include "GtpMsgArray.h"
CGtpMsgArray::CGtpMsgArray(string srcStr):m_nArraySize(0)
{
	int nRtn = strutils::stripBracket(srcStr);
	std::vector<string> vResult;
	vResult = strutils::explodeGTP(',',srcStr);
	m_nArraySize = vResult.size();
// 	if (m_nArraySize <1)
// 	{
// 		return;
// 	}
	for (int i = 0;i<m_nArraySize;i++)
	{
		std::string &sParameter = vResult.at(i);
		string::size_type iPos;
		iPos = strutils::findFirstOf('=',sParameter);
		if (iPos != string::npos)
		{
			//ȡvalueֵ   k={ka=va1,kb=vb1,kc=vc1}
			sParameter = sParameter.substr(iPos + 1);
			//ȥ��������  {ka=va1,kb=vb1,kc=vc1}
			strutils::stripBrace(sParameter);
			//�õ�k=v     ka=va1,kb=vb1,kc=vc1
			std::vector<string> vSResult;
			vSResult = strutils::explodeGTP(',',sParameter);
			//ȡvalue
			int nSSize = vSResult.size();
			for (int j = 0;j<nSSize;j++)
			{
				string &sSpar = vSResult.at(j);
				if (sSpar == "")
				{
					continue;
				}
				string sKey;
				string sValue;
				string::size_type iSPos;
				iSPos = strutils::findFirstOf('=',sSpar);
				if (iSPos != string::npos)
				{
					sKey = sSpar.substr(0,iSPos);
					sValue = sSpar.substr(iSPos+1);
				}
				//���벻����Ƕ���������ʹ�ù����з�����Ƕ�����飬���û������ٴ���һ�����������ʹ��
				string nKey = strutils::ToString<int>(i);
				sKey = sKey + "-" + nKey;
				//����ǰ��ֵ�����˽�ת�壨���value��Ƕ�������򲻽���ת�壩
				if (sValue.size() < 2 ||sValue.at(0) != '[' || sValue.at(sValue.size()-1) != ']')
				{
					sValue = strutils::delTransStr(sValue);
				}
				m_mapValue[sKey] = sValue;
			}
		}
	}
}
CGtpMsgArray::CGtpMsgArray():m_nArraySize(0)
{
}
CGtpMsgArray::~CGtpMsgArray()
{
	m_mapValue.clear();
}
string CGtpMsgArray::PrintArrayStr(vector<string> &vArray)
{
	string sResult;
	sResult = "[";
	int nSize = vArray.size();
	if (nSize == 0 )
	{
		return "[]";
	}
	string sPara = vArray.at(0);
	//ת�� Ĭ����Ϊ��������Ҫת��
	//sPara = strutils::addTransStr(sPara);
	sResult += sPara;
	sResult += "={";
	for (int i = 1;i<nSize;i++)
	{
		if (vArray[i] == sPara)
		{
			sResult += "},";
			sResult += sPara;
			sResult += "={";
		}else
		{
			sResult += vArray[i];
			sResult += "=";
			i += 1;
			string value = vArray[i];
			if (value.size() < 2 || value.at(0)!= '[' || value.at(value.size()-1) != ']')
			{
				value = strutils::addTransStr(value);
			}
			sResult += value;
			sResult += ",";
		}
	}
	sResult += "}]";
	return sResult;
}
string CGtpMsgArray::GetValueByKeyIndex(string sKey,int index)
{
	string sNKey = strutils::ToString<int>(index);
	sKey = sKey +"-"+ sNKey;
	map<string,string>::iterator it;
	it = m_mapValue.find(sKey);
	if (it != m_mapValue.end())
	{
		return it->second;
	}
	return "";
}
void CGtpMsgArray::GetParameterVal(string sKey,char *sValue,size_t sizeValue,int index)
{
	string sStr = GetValueByKeyIndex(sKey,index);
	if (sStr == "")
	{
		*sValue = '\0';
	}else
	{
		strncpy(sValue,sStr.c_str(),sizeValue);
		sValue[sizeValue -1] = '\0';
	}

}
void CGtpMsgArray::GetParameterVal(string sKey,int &nValue,int index)
{
	string sStr = GetValueByKeyIndex(sKey,index);
	if (sStr == "")
	{
		nValue = 0;
	}else
	{
		nValue = strutils::FromString<int>(sStr);
	}
}
void CGtpMsgArray::GetParameterVal(string sKey,double &dlValue,int index)
{
	string sStr = GetValueByKeyIndex(sKey,index);
	if (sStr == "")
	{
		dlValue = 0.00;
	}else
	{
		dlValue = strutils::FromString<double>(sStr);
	}
}
void CGtpMsgArray::GetParameterVal(string sKey,char &cValue,int index)
{
	string sStr = GetValueByKeyIndex(sKey,index);
	if (sStr == "")
	{
		cValue = 0;
	}else
	{
		cValue = sStr.at(0);
	}
}