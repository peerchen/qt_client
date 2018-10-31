//
// WANCableLinkConfigRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigRemoteObject
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


#include "UPnPS/InternetGateway1/WANCableLinkConfigRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/WANCableLinkConfigEventDispatcher.h"


namespace UPnPS {
namespace InternetGateway1 {


WANCableLinkConfigRemoteObject::WANCableLinkConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANCableLinkConfig> pServiceObject):
	UPnPS::InternetGateway1::IWANCableLinkConfig(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->bPIEncryptionEnabledChanged += Poco::delegate(this, &WANCableLinkConfigRemoteObject::event__bPIEncryptionEnabledChanged);
}


WANCableLinkConfigRemoteObject::~WANCableLinkConfigRemoteObject()
{
	try
	{
		_pServiceObject->bPIEncryptionEnabledChanged -= Poco::delegate(this, &WANCableLinkConfigRemoteObject::event__bPIEncryptionEnabledChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WANCableLinkConfigRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void WANCableLinkConfigRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new WANCableLinkConfigEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool WANCableLinkConfigRemoteObject::remoting__hasEvents() const
{
	return true;
}


void WANCableLinkConfigRemoteObject::event__bPIEncryptionEnabledChanged(const bool& data)
{
	bPIEncryptionEnabledChanged(this, data);
}


} // namespace InternetGateway1
} // namespace UPnPS

