//
// WANDSLLinkConfigRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigRemoteObject
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


#include "UPnPS/InternetGateway1/WANDSLLinkConfigRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfigEventDispatcher.h"


namespace UPnPS {
namespace InternetGateway1 {


WANDSLLinkConfigRemoteObject::WANDSLLinkConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> pServiceObject):
	UPnPS::InternetGateway1::IWANDSLLinkConfig(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->autoConfigChanged += Poco::delegate(this, &WANDSLLinkConfigRemoteObject::event__autoConfigChanged);
	_pServiceObject->linkStatusChanged += Poco::delegate(this, &WANDSLLinkConfigRemoteObject::event__linkStatusChanged);
}


WANDSLLinkConfigRemoteObject::~WANDSLLinkConfigRemoteObject()
{
	try
	{
		_pServiceObject->autoConfigChanged -= Poco::delegate(this, &WANDSLLinkConfigRemoteObject::event__autoConfigChanged);
		_pServiceObject->linkStatusChanged -= Poco::delegate(this, &WANDSLLinkConfigRemoteObject::event__linkStatusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WANDSLLinkConfigRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void WANDSLLinkConfigRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new WANDSLLinkConfigEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool WANDSLLinkConfigRemoteObject::remoting__hasEvents() const
{
	return true;
}


void WANDSLLinkConfigRemoteObject::event__autoConfigChanged(const bool& data)
{
	autoConfigChanged(this, data);
}


void WANDSLLinkConfigRemoteObject::event__linkStatusChanged(const std::string& data)
{
	linkStatusChanged(this, data);
}


} // namespace InternetGateway1
} // namespace UPnPS

