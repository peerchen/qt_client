//
// WANCommonInterfaceConfigRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigRemoteObject
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


#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigEventDispatcher.h"


namespace UPnPS {
namespace InternetGateway1 {


WANCommonInterfaceConfigRemoteObject::WANCommonInterfaceConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANCommonInterfaceConfig> pServiceObject):
	UPnPS::InternetGateway1::IWANCommonInterfaceConfig(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->enabledForInternetChanged += Poco::delegate(this, &WANCommonInterfaceConfigRemoteObject::event__enabledForInternetChanged);
	_pServiceObject->numberOfActiveConnectionsChanged += Poco::delegate(this, &WANCommonInterfaceConfigRemoteObject::event__numberOfActiveConnectionsChanged);
	_pServiceObject->physicalLinkStatusChanged += Poco::delegate(this, &WANCommonInterfaceConfigRemoteObject::event__physicalLinkStatusChanged);
}


WANCommonInterfaceConfigRemoteObject::~WANCommonInterfaceConfigRemoteObject()
{
	try
	{
		_pServiceObject->enabledForInternetChanged -= Poco::delegate(this, &WANCommonInterfaceConfigRemoteObject::event__enabledForInternetChanged);
		_pServiceObject->numberOfActiveConnectionsChanged -= Poco::delegate(this, &WANCommonInterfaceConfigRemoteObject::event__numberOfActiveConnectionsChanged);
		_pServiceObject->physicalLinkStatusChanged -= Poco::delegate(this, &WANCommonInterfaceConfigRemoteObject::event__physicalLinkStatusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WANCommonInterfaceConfigRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void WANCommonInterfaceConfigRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new WANCommonInterfaceConfigEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool WANCommonInterfaceConfigRemoteObject::remoting__hasEvents() const
{
	return true;
}


void WANCommonInterfaceConfigRemoteObject::event__enabledForInternetChanged(const bool& data)
{
	enabledForInternetChanged(this, data);
}


void WANCommonInterfaceConfigRemoteObject::event__numberOfActiveConnectionsChanged(const Poco::UInt16& data)
{
	numberOfActiveConnectionsChanged(this, data);
}


void WANCommonInterfaceConfigRemoteObject::event__physicalLinkStatusChanged(const std::string& data)
{
	physicalLinkStatusChanged(this, data);
}


} // namespace InternetGateway1
} // namespace UPnPS

