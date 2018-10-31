//
// ConnectionManager1EventDispatcher.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1EventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef MediaServer1_ConnectionManager1EventDispatcher_INCLUDED
#define MediaServer1_ConnectionManager1EventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/MediaServer1/ConnectionManager1RemoteObject.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ConnectionManager1EventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	ConnectionManager1EventDispatcher(ConnectionManager1RemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a ConnectionManager1EventDispatcher.

	virtual ~ConnectionManager1EventDispatcher();
		/// Destroys the ConnectionManager1EventDispatcher.

	void event__currentConnectionIDsChanged(const void* pSender, const std::string& data);

	void event__sinkProtocolInfoChanged(const void* pSender, const std::string& data);

	void event__sourceProtocolInfoChanged(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__currentConnectionIDsChangedImpl(const std::string& subscriberURI, const std::string& data);

	void event__sinkProtocolInfoChangedImpl(const std::string& subscriberURI, const std::string& data);

	void event__sourceProtocolInfoChangedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	ConnectionManager1RemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ConnectionManager1EventDispatcher::remoting__typeId() const
{
	return IConnectionManager1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ConnectionManager1EventDispatcher_INCLUDED

