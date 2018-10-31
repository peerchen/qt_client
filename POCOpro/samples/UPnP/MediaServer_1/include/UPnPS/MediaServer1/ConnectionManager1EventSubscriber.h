//
// ConnectionManager1EventSubscriber.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1EventSubscriber
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


#ifndef MediaServer1_ConnectionManager1EventSubscriber_INCLUDED
#define MediaServer1_ConnectionManager1EventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/MediaServer1/ConnectionManager1Proxy.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ConnectionManager1EventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	ConnectionManager1EventSubscriber(const std::string& uri, ConnectionManager1Proxy* pProxy);
		/// Creates a ConnectionManager1EventSubscriber.

	virtual ~ConnectionManager1EventSubscriber();
		/// Destroys the ConnectionManager1EventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__currentConnectionIDsChanged(const std::string& data);

	void event__sinkProtocolInfoChanged(const std::string& data);

	void event__sourceProtocolInfoChanged(const std::string& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ConnectionManager1EventSubscriber::remoting__typeId() const
{
	return IConnectionManager1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ConnectionManager1EventSubscriber_INCLUDED

