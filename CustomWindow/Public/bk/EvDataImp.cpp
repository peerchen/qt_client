//#include "stdafx.h"
#include "EvDataImp.h"


CEvDataImp::CEvDataImp(eventData* data)
{
	assert(data);
	m_data = data;
}


CEvDataImp::~CEvDataImp()
{
	CTraderManager::instance()->Recyle(m_data);
}


int CEvDataImp::Release()
{
	if (_Countor <= 0) return 0;
	if (0 == --_Countor)
	{
		_Countor = 0;
		delete this;

	}

	return _Countor;

}
void CEvDataImp::Reset()
{
	Countor::Reset();
}

const eventData* CEvDataImp::ReadData()
{
	return m_data;
}
int CEvDataImp::GetValInt(int index, const char* valname)
{
	return 0;
}
unsigned int CEvDataImp::GetValUInt(int index, const char* valname)
{
	return 0;
}
double CEvDataImp::GetValDouble(int index, const char* valname)
{
	return 0;
}
string CEvDataImp::GetValString(int index, const char* valname)
{
	return "";
}

eventData* CEvDataImp::WriteData()
{
	return m_data;
}
int CEvDataImp::SetValInt(int index, const char* valname, int val)
{
	return 0;
}
int CEvDataImp::SetValUInt(int index, const char* valname, unsigned int val)
{
	return 0;
}
int CEvDataImp::SetValDouble(int index, const char* valname, double val)
{
	return 0;
}
int CEvDataImp::SetValString(int index, const char* valname, const char* val)
{
	return 0;
}
