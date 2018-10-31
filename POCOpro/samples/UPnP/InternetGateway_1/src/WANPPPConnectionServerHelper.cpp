//
// WANPPPConnectionServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPPPConnectionServerHelper
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


#include "UPnPS/InternetGateway1/WANPPPConnectionServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANPPPConnectionEventDispatcher.h"
#include "UPnPS/InternetGateway1/WANPPPConnectionSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANPPPConnectionServerHelper> shWANPPPConnectionServerHelper;
}


WANPPPConnectionServerHelper::WANPPPConnectionServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


WANPPPConnectionServerHelper::~WANPPPConnectionServerHelper()
{
}


void WANPPPConnectionServerHelper::shutdown()
{
	WANPPPConnectionServerHelper::instance().unregisterSkeleton();
	shWANPPPConnectionServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::WANPPPConnectionRemoteObject> WANPPPConnectionServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WANPPPConnectionRemoteObject(oid, pServiceObject);
}


void WANPPPConnectionServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<WANPPPConnectionRemoteObject> pRemoteObject = pIdentifiable.cast<WANPPPConnectionRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


WANPPPConnectionServerHelper& WANPPPConnectionServerHelper::instance()
{
	return *shWANPPPConnectionServerHelper.get();
}


std::string WANPPPConnectionServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANPPPConnectionRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WANPPPConnectionServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.WANPPPConnection", new WANPPPConnectionSkeleton);
}


void WANPPPConnectionServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void WANPPPConnectionServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.WANPPPConnection", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

