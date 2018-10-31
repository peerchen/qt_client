//
// TimeService.cpp
//
// $Id: //poco/1.7/RemotingNG/samples/TimeServerTCP/src/TimeService.cpp#1 $
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "TimeService.h"
#include "Poco/Util/TimerTask.h"


namespace Services {


class WakeUpTask: public Poco::Util::TimerTask
{
public:
	WakeUpTask(TimeService& owner, const std::string& message):
		_owner(owner),
		_message(message)
	{
	}
	
	void run()
	{
		_owner.wakeUp(this, _message);
	}
	
private:
	TimeService& _owner;
	std::string _message;
};


TimeService::TimeService()
{
}


TimeService::~TimeService()
{
}


Poco::DateTime TimeService::currentTime() const
{
	Poco::DateTime now;
	return now;
}


void TimeService::wakeMeUp(const Poco::DateTime& time, const std::string& message)
{
	_timer.schedule(new WakeUpTask(*this, message), time.timestamp());
}


} // namespace Services
