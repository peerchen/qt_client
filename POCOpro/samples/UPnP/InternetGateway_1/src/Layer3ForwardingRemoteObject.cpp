//
// Layer3ForwardingRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingRemoteObject
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


#include "UPnPS/InternetGateway1/Layer3ForwardingRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/Layer3ForwardingEventDispatcher.h"


namespace UPnPS {
namespace InternetGateway1 {


Layer3ForwardingRemoteObject::Layer3ForwardingRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> pServiceObject):
	UPnPS::InternetGateway1::ILayer3Forwarding(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->defaultConnectionServiceChanged += Poco::delegate(this, &Layer3ForwardingRemoteObject::event__defaultConnectionServiceChanged);
}


Layer3ForwardingRemoteObject::~Layer3ForwardingRemoteObject()
{
	try
	{
		_pServiceObject->defaultConnectionServiceChanged -= Poco::delegate(this, &Layer3ForwardingRemoteObject::event__defaultConnectionServiceChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string Layer3ForwardingRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void Layer3ForwardingRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new Layer3ForwardingEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool Layer3ForwardingRemoteObject::remoting__hasEvents() const
{
	return true;
}


void Layer3ForwardingRemoteObject::event__defaultConnectionServiceChanged(const std::string& data)
{
	defaultConnectionServiceChanged(this, data);
}


} // namespace InternetGateway1
} // namespace UPnPS

