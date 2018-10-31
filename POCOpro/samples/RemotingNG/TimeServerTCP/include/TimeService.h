//
// TimeService.h
//
// $Id: //poco/1.7/RemotingNG/samples/TimeServerTCP/include/TimeService.h#1 $
//
// Definition of the TimeService class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef TimeService_INCLUDED
#define TimeService_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/BasicEvent.h"
#include "Poco/DateTime.h"
#include "Poco/Util/Timer.h"


namespace Services {


//@ remote
class TimeService
{
public:
	TimeService();
		/// Creates the TimeService.

	~TimeService();
		/// Destroys the TimeService.
		
	Poco::BasicEvent<const std::string> wakeUp;
	
	Poco::DateTime currentTime() const;
		/// Returns the current date and time.
		
	void wakeMeUp(const Poco::DateTime& time, const std::string& message);
		/// Schedules a wakeup call.
		///
		/// Fires the wakeUp event at the given time, passing
		/// the given message as argument.
		
private:
	Poco::Util::Timer _timer;
};


} // namespace Services


#endif // TimeService_INCLUDED
