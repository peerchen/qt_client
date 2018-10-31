#ifndef _AP_CONSTANT_H_
#define _AP_CONSTANT_H_

#include <string>
using namespace std;

#define GESS_FLD_SEPERATOR  "#"  //�ֶηָ�
#define GESS_VAL_SEPERATOR  "="  //��ֵ�ָ�
#define GESS_NODE_TYPE  "NodeType"     //�������KeyΨһ��ʶ
#define GESS_NODE_ID  "NodeID"     //�������KeyΨһ��ʶ
#define GESS_API_NAME  "ApiName"   //�����������
#define GESS_DATA_TYPE "DataType"  //�������һ���ṹ����
#define GESS_ROOT_ID  "RootID"     //�������KeyΨһ��ʶ
#define SIGEX_BP_Hello  "BroadcastHello"   //���ʰ��Աǰ�õĹ㲥��½

#define GTP_MAX_PACKET_BODY_LENGTH	4096

#define DEFAULT_IDLE_TIMEOUT						16
#define DEFAULT_HELLO_RESEND_INTERVAL				6
#define DEFAULT_HELLO_RESEND_COUNT					8
//�������Ķ�ʱ����ʱ����
#define DEFAULT_HELLO_TIME					2
//�ֶηָ� ԭ����ϵͳ��'#'�ָ�
#define GTP_FLD_C_SEPERATOR  ','
#define GTP_FLD_SEPERATOR  ","
//��ֵ�ָ�
#define GTP_VAL_SEPERATOR  "="

#define GTP_API_NAME  "MsgType"   //���������������
//GTPType
#define GTP_TYPE_NONE		0
#define GTP_TYPE_STRING		1
#define GTP_TYPE_BINARY		2
#define GTP_TYPE_COMPRESSED	3
#define GTP_TYPE_ENCRYPT	4
//GTP TAG
#define GTP_TAG_KEEPALIVE	5
namespace ApConst 
{

	//ArrayListMsg/HashtableMsg	
	//֧�ֵ������
	const int SEPARATOR_MAX_LEVEL = 4;							
	//�༶�ָ���
	const string SEPARATOR_RECORD[SEPARATOR_MAX_LEVEL] = { "��", "��", "��","��"};
}
#endif