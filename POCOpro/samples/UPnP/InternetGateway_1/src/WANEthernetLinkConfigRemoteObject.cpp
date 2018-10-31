//
// WANEthernetLinkConfigRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANEthernetLinkConfigRemoteObject
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


#include "UPnPS/InternetGateway1/WANEthernetLinkConfigRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/WANEthernetLinkConfigEventDispatcher.h"


namespace UPnPS {
namespace InternetGateway1 {


WANEthernetLinkConfigRemoteObject::WANEthernetLinkConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> pServiceObject):
	UPnPS::InternetGateway1::IWANEthernetLinkConfig(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->ethernetLinkStatusChanged += Poco::delegate(this, &WANEthernetLinkConfigRemoteObject::event__ethernetLinkStatusChanged);
}


WANEthernetLinkConfigRemoteObject::~WANEthernetLinkConfigRemoteObject()
{
	try
	{
		_pServiceObject->ethernetLinkStatusChanged -= Poco::delegate(this, &WANEthernetLinkConfigRemoteObject::event__ethernetLinkStatusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WANEthernetLinkConfigRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void WANEthernetLinkConfigRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new WANEthernetLinkConfigEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool WANEthernetLinkConfigRemoteObject::remoting__hasEvents() const
{
	return true;
}


void WANEthernetLinkConfigRemoteObject::event__ethernetLinkStatusChanged(const std::string& data)
{
	ethernetLinkStatusChanged(this, data);
}


} // namespace InternetGateway1
} // namespace UPnPS

