//
// WANIPConnectionServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANIPConnectionServerHelper
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


#include "UPnPS/InternetGateway1/WANIPConnectionServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANIPConnectionEventDispatcher.h"
#include "UPnPS/InternetGateway1/WANIPConnectionSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANIPConnectionServerHelper> shWANIPConnectionServerHelper;
}


WANIPConnectionServerHelper::WANIPConnectionServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


WANIPConnectionServerHelper::~WANIPConnectionServerHelper()
{
}


void WANIPConnectionServerHelper::shutdown()
{
	WANIPConnectionServerHelper::instance().unregisterSkeleton();
	shWANIPConnectionServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::WANIPConnectionRemoteObject> WANIPConnectionServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANIPConnection> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WANIPConnectionRemoteObject(oid, pServiceObject);
}


void WANIPConnectionServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<WANIPConnectionRemoteObject> pRemoteObject = pIdentifiable.cast<WANIPConnectionRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


WANIPConnectionServerHelper& WANIPConnectionServerHelper::instance()
{
	return *shWANIPConnectionServerHelper.get();
}


std::string WANIPConnectionServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANIPConnectionRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WANIPConnectionServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.WANIPConnection", new WANIPConnectionSkeleton);
}


void WANIPConnectionServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void WANIPConnectionServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.WANIPConnection", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

