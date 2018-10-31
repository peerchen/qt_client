//
// WANPPPConnectionRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPPPConnectionRemoteObject
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


#include "UPnPS/InternetGateway1/WANPPPConnectionRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/WANPPPConnectionEventDispatcher.h"


namespace UPnPS {
namespace InternetGateway1 {


WANPPPConnectionRemoteObject::WANPPPConnectionRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> pServiceObject):
	UPnPS::InternetGateway1::IWANPPPConnection(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->connectionStatusChanged += Poco::delegate(this, &WANPPPConnectionRemoteObject::event__connectionStatusChanged);
	_pServiceObject->externalIPAddressChanged += Poco::delegate(this, &WANPPPConnectionRemoteObject::event__externalIPAddressChanged);
	_pServiceObject->portMappingNumberOfEntriesChanged += Poco::delegate(this, &WANPPPConnectionRemoteObject::event__portMappingNumberOfEntriesChanged);
	_pServiceObject->possibleConnectionTypesChanged += Poco::delegate(this, &WANPPPConnectionRemoteObject::event__possibleConnectionTypesChanged);
}


WANPPPConnectionRemoteObject::~WANPPPConnectionRemoteObject()
{
	try
	{
		_pServiceObject->connectionStatusChanged -= Poco::delegate(this, &WANPPPConnectionRemoteObject::event__connectionStatusChanged);
		_pServiceObject->externalIPAddressChanged -= Poco::delegate(this, &WANPPPConnectionRemoteObject::event__externalIPAddressChanged);
		_pServiceObject->portMappingNumberOfEntriesChanged -= Poco::delegate(this, &WANPPPConnectionRemoteObject::event__portMappingNumberOfEntriesChanged);
		_pServiceObject->possibleConnectionTypesChanged -= Poco::delegate(this, &WANPPPConnectionRemoteObject::event__possibleConnectionTypesChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WANPPPConnectionRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void WANPPPConnectionRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new WANPPPConnectionEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool WANPPPConnectionRemoteObject::remoting__hasEvents() const
{
	return true;
}


void WANPPPConnectionRemoteObject::event__connectionStatusChanged(const std::string& data)
{
	connectionStatusChanged(this, data);
}


void WANPPPConnectionRemoteObject::event__externalIPAddressChanged(const std::string& data)
{
	externalIPAddressChanged(this, data);
}


void WANPPPConnectionRemoteObject::event__portMappingNumberOfEntriesChanged(const Poco::UInt16& data)
{
	portMappingNumberOfEntriesChanged(this, data);
}


void WANPPPConnectionRemoteObject::event__possibleConnectionTypesChanged(const std::string& data)
{
	possibleConnectionTypesChanged(this, data);
}


} // namespace InternetGateway1
} // namespace UPnPS

