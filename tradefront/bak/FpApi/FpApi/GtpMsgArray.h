#ifndef _GTP_MSG_ARRAY_H_
#define _GTP_MSG_ARRAY_H_
#include <string>
#include <vector>
#include "strutils.h"
using namespace std;
//GTPЭ���ж������Ϣ�����ʽ�Ľ���
//��Ϣ������ͣ�srcStr����[k={ka=va1,kb=vb1,kc=vc1},k={ka=va2,kb=vb2,kc=vc2},k={ka=va3,kb=vb3,kc=vc3}]
//�����ÿ��value
class CGtpMsgArray
{
public:
	CGtpMsgArray(string srcStr);
	CGtpMsgArray();
	~CGtpMsgArray();
	static string PrintArrayStr(vector<string> &vArray);
	string GetValueByKeyIndex(string sKey,int index);
	void GetParameterVal(string sKey,char *sValue,size_t sizeValue,int index = 0);
	void GetParameterVal(string sKey,int &nValue,int index = 0);
	void GetParameterVal(string sKey,double &dlValue,int index = 0);
	void GetParameterVal(string sKey,char &cValue,int index = 0);
	int GetArraySize(){return m_nArraySize;}
	//���Ƕ�׵���Ϣ����
	//CGtpMsgArray GetMsgArrayByKeyIndex(string sKey,int index);
	//�������������Ϊ�ָ�������ͨ����
	//vector<string> GetArrayByKeyIndex(string sKey,int index);
private:
	map<string,string> m_mapValue;
	int m_nArraySize;
};
#endif