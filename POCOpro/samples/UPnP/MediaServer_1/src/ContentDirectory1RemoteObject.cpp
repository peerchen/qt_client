//
// ContentDirectory1RemoteObject.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1RemoteObject
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


#include "UPnPS/MediaServer1/ContentDirectory1RemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/MediaServer1/ContentDirectory1EventDispatcher.h"


namespace UPnPS {
namespace MediaServer1 {


ContentDirectory1RemoteObject::ContentDirectory1RemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::MediaServer1::ContentDirectory1> pServiceObject):
	UPnPS::MediaServer1::IContentDirectory1(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->containerUpdateIDsChanged += Poco::delegate(this, &ContentDirectory1RemoteObject::event__containerUpdateIDsChanged);
	_pServiceObject->systemUpdateIDChanged += Poco::delegate(this, &ContentDirectory1RemoteObject::event__systemUpdateIDChanged);
	_pServiceObject->transferIDsChanged += Poco::delegate(this, &ContentDirectory1RemoteObject::event__transferIDsChanged);
}


ContentDirectory1RemoteObject::~ContentDirectory1RemoteObject()
{
	try
	{
		_pServiceObject->containerUpdateIDsChanged -= Poco::delegate(this, &ContentDirectory1RemoteObject::event__containerUpdateIDsChanged);
		_pServiceObject->systemUpdateIDChanged -= Poco::delegate(this, &ContentDirectory1RemoteObject::event__systemUpdateIDChanged);
		_pServiceObject->transferIDsChanged -= Poco::delegate(this, &ContentDirectory1RemoteObject::event__transferIDsChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string ContentDirectory1RemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void ContentDirectory1RemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new ContentDirectory1EventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool ContentDirectory1RemoteObject::remoting__hasEvents() const
{
	return true;
}


void ContentDirectory1RemoteObject::event__containerUpdateIDsChanged(const std::string& data)
{
	containerUpdateIDsChanged(this, data);
}


void ContentDirectory1RemoteObject::event__systemUpdateIDChanged(const Poco::UInt32& data)
{
	systemUpdateIDChanged(this, data);
}


void ContentDirectory1RemoteObject::event__transferIDsChanged(const std::string& data)
{
	transferIDsChanged(this, data);
}


} // namespace MediaServer1
} // namespace UPnPS

