#pragma once
#include "TraderManager.h"
class CEvDataImp :
	public IEvDataReadWrite
{
public:
	CEvDataImp(eventData* data);
	~CEvDataImp();

	virtual int Release();
	virtual void Reset();
	virtual const eventData* ReadData();
	virtual int GetValInt(int index, const char* valname);
	virtual unsigned int GetValUInt(int index, const char* valname);
	virtual double GetValDouble(int index, const char* valname);
	virtual string GetValString(int index, const char* valname);

	virtual eventData* WriteData();
	virtual int SetValInt(int index, const char* valname, int val);
	virtual int SetValUInt(int index, const char* valname, unsigned int val);
	virtual int SetValDouble(int index, const char* valname, double val);
	virtual int SetValString(int index, const char* valname, const char* val);

	
private:
	CEvDataImp() = delete;
	eventData* m_data;
};

