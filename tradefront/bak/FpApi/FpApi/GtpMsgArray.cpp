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
			//取value值   k={ka=va1,kb=vb1,kc=vc1}
			sParameter = sParameter.substr(iPos + 1);
			//去除花括号  {ka=va1,kb=vb1,kc=vc1}
			strutils::stripBrace(sParameter);
			//得到k=v     ka=va1,kb=vb1,kc=vc1
			std::vector<string> vSResult;
			vSResult = strutils::explodeGTP(',',sParameter);
			//取value
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
				//代码不考虑嵌套情况，在使用过程中发现是嵌套数组，则用户主动再创建一个数组类进行使用
				string nKey = strutils::ToString<int>(i);
				sKey = sKey + "-" + nKey;
				//放入前对值进行了解转义（如果value是嵌套数组则不进行转义）
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
	//转义 默认认为域名不需要转义
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