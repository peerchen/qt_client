//
// AVTransport1RemoteObject.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1RemoteObject
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


#include "UPnPS/MediaServer1/AVTransport1RemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/MediaServer1/AVTransport1EventDispatcher.h"


namespace UPnPS {
namespace MediaServer1 {


AVTransport1RemoteObject::AVTransport1RemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> pServiceObject):
	UPnPS::MediaServer1::IAVTransport1(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->lastChangeChanged += Poco::delegate(this, &AVTransport1RemoteObject::event__lastChangeChanged);
}


AVTransport1RemoteObject::~AVTransport1RemoteObject()
{
	try
	{
		_pServiceObject->lastChangeChanged -= Poco::delegate(this, &AVTransport1RemoteObject::event__lastChangeChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string AVTransport1RemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void AVTransport1RemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new AVTransport1EventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool AVTransport1RemoteObject::remoting__hasEvents() const
{
	return true;
}


void AVTransport1RemoteObject::event__lastChangeChanged(const std::string& data)
{
	lastChangeChanged(this, data);
}


} // namespace MediaServer1
} // namespace UPnPS

