//
// WANIPConnectionRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANIPConnectionRemoteObject
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


#include "UPnPS/InternetGateway1/WANIPConnectionRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/WANIPConnectionEventDispatcher.h"


namespace UPnPS {
namespace InternetGateway1 {


WANIPConnectionRemoteObject::WANIPConnectionRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANIPConnection> pServiceObject):
	UPnPS::InternetGateway1::IWANIPConnection(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->connectionStatusChanged += Poco::delegate(this, &WANIPConnectionRemoteObject::event__connectionStatusChanged);
	_pServiceObject->externalIPAddressChanged += Poco::delegate(this, &WANIPConnectionRemoteObject::event__externalIPAddressChanged);
	_pServiceObject->portMappingNumberOfEntriesChanged += Poco::delegate(this, &WANIPConnectionRemoteObject::event__portMappingNumberOfEntriesChanged);
	_pServiceObject->possibleConnectionTypesChanged += Poco::delegate(this, &WANIPConnectionRemoteObject::event__possibleConnectionTypesChanged);
}


WANIPConnectionRemoteObject::~WANIPConnectionRemoteObject()
{
	try
	{
		_pServiceObject->connectionStatusChanged -= Poco::delegate(this, &WANIPConnectionRemoteObject::event__connectionStatusChanged);
		_pServiceObject->externalIPAddressChanged -= Poco::delegate(this, &WANIPConnectionRemoteObject::event__externalIPAddressChanged);
		_pServiceObject->portMappingNumberOfEntriesChanged -= Poco::delegate(this, &WANIPConnectionRemoteObject::event__portMappingNumberOfEntriesChanged);
		_pServiceObject->possibleConnectionTypesChanged -= Poco::delegate(this, &WANIPConnectionRemoteObject::event__possibleConnectionTypesChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WANIPConnectionRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void WANIPConnectionRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new WANIPConnectionEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool WANIPConnectionRemoteObject::remoting__hasEvents() const
{
	return true;
}


void WANIPConnectionRemoteObject::event__connectionStatusChanged(const std::string& data)
{
	connectionStatusChanged(this, data);
}


void WANIPConnectionRemoteObject::event__externalIPAddressChanged(const std::string& data)
{
	externalIPAddressChanged(this, data);
}


void WANIPConnectionRemoteObject::event__portMappingNumberOfEntriesChanged(const Poco::UInt16& data)
{
	portMappingNumberOfEntriesChanged(this, data);
}


void WANIPConnectionRemoteObject::event__possibleConnectionTypesChanged(const std::string& data)
{
	possibleConnectionTypesChanged(this, data);
}


} // namespace InternetGateway1
} // namespace UPnPS

