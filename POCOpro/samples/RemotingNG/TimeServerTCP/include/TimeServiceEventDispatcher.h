//
// TimeServiceEventDispatcher.h
//
// Package: Generated
// Module:  TimeServiceEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
//


#ifndef TimeServiceEventDispatcher_INCLUDED
#define TimeServiceEventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "TimeServiceRemoteObject.h"


namespace Services {


class TimeServiceEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	TimeServiceEventDispatcher(TimeServiceRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a TimeServiceEventDispatcher.

	virtual ~TimeServiceEventDispatcher();
		/// Destroys the TimeServiceEventDispatcher.

	void event__wakeUp(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__wakeUpImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	TimeServiceRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& TimeServiceEventDispatcher::remoting__typeId() const
{
	return ITimeService::remoting__typeId();
}


} // namespace Services


#endif // TimeServiceEventDispatcher_INCLUDED

