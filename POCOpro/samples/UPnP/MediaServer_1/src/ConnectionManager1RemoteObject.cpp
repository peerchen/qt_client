//
// ConnectionManager1RemoteObject.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1RemoteObject
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


#include "UPnPS/MediaServer1/ConnectionManager1RemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/MediaServer1/ConnectionManager1EventDispatcher.h"


namespace UPnPS {
namespace MediaServer1 {


ConnectionManager1RemoteObject::ConnectionManager1RemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> pServiceObject):
	UPnPS::MediaServer1::IConnectionManager1(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->currentConnectionIDsChanged += Poco::delegate(this, &ConnectionManager1RemoteObject::event__currentConnectionIDsChanged);
	_pServiceObject->sinkProtocolInfoChanged += Poco::delegate(this, &ConnectionManager1RemoteObject::event__sinkProtocolInfoChanged);
	_pServiceObject->sourceProtocolInfoChanged += Poco::delegate(this, &ConnectionManager1RemoteObject::event__sourceProtocolInfoChanged);
}


ConnectionManager1RemoteObject::~ConnectionManager1RemoteObject()
{
	try
	{
		_pServiceObject->currentConnectionIDsChanged -= Poco::delegate(this, &ConnectionManager1RemoteObject::event__currentConnectionIDsChanged);
		_pServiceObject->sinkProtocolInfoChanged -= Poco::delegate(this, &ConnectionManager1RemoteObject::event__sinkProtocolInfoChanged);
		_pServiceObject->sourceProtocolInfoChanged -= Poco::delegate(this, &ConnectionManager1RemoteObject::event__sourceProtocolInfoChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string ConnectionManager1RemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void ConnectionManager1RemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new ConnectionManager1EventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool ConnectionManager1RemoteObject::remoting__hasEvents() const
{
	return true;
}


void ConnectionManager1RemoteObject::event__currentConnectionIDsChanged(const std::string& data)
{
	currentConnectionIDsChanged(this, data);
}


void ConnectionManager1RemoteObject::event__sinkProtocolInfoChanged(const std::string& data)
{
	sinkProtocolInfoChanged(this, data);
}


void ConnectionManager1RemoteObject::event__sourceProtocolInfoChanged(const std::string& data)
{
	sourceProtocolInfoChanged(this, data);
}


} // namespace MediaServer1
} // namespace UPnPS

