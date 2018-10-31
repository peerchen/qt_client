#ifndef _NM_CONSTANT_H_
#define _NM_CONSTANT_H_

#include <string>
using namespace std;

namespace NmConst
{
	const int gc_nQuolityGood				= 0;				//质量属性Good
	const int gc_nQuolityBad				= 1;				//质量属性Bad
	const int gc_nQuolityUncertain			= 2;				//质量属性Uncertain

	const string gc_nItemTypeDigital		= "0";				//数字型监控项(值随时间离散变化)
	const string gc_nItemTypeAnalog			= "1";				//模拟型监控项(值随时间连续变化)
	const string gc_nItemTypeConfig			= "2";				//配置项(值不随时间变化)

	const int gc_nValueTypeInt				= 0;				//int数值类型
	const int gc_nValueTypeDbl				= 1;				//double数值类型
	const int gc_nValueTypeStr				= 2;				//string数值类型

	const int gc_nEvtSimple					= 0;				//简单事件
	const int gc_nEvtTrack					= 1;				//track事件

	const int gc_nAlmGrade0					= 0;				//正常
	const int gc_nAlmGrade1					= 1;				//一般告警
	const int gc_nAlmGrade2					= 2;				//重要转移

	const int gc_nAlmNtfNew					= 0;				//新增告警
	const int gc_nAlmNtfEnd					= 1;				//告警结束
	const int gc_nAlmNtfChg					= 2;				//告警转移
}

#endif