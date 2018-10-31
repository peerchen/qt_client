//
// WANCableLinkConfigServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigServerHelper
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


#include "UPnPS/InternetGateway1/WANCableLinkConfigServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANCableLinkConfigEventDispatcher.h"
#include "UPnPS/InternetGateway1/WANCableLinkConfigSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANCableLinkConfigServerHelper> shWANCableLinkConfigServerHelper;
}


WANCableLinkConfigServerHelper::WANCableLinkConfigServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


WANCableLinkConfigServerHelper::~WANCableLinkConfigServerHelper()
{
}


void WANCableLinkConfigServerHelper::shutdown()
{
	WANCableLinkConfigServerHelper::instance().unregisterSkeleton();
	shWANCableLinkConfigServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::WANCableLinkConfigRemoteObject> WANCableLinkConfigServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANCableLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WANCableLinkConfigRemoteObject(oid, pServiceObject);
}


void WANCableLinkConfigServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<WANCableLinkConfigRemoteObject> pRemoteObject = pIdentifiable.cast<WANCableLinkConfigRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


WANCableLinkConfigServerHelper& WANCableLinkConfigServerHelper::instance()
{
	return *shWANCableLinkConfigServerHelper.get();
}


std::string WANCableLinkConfigServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANCableLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WANCableLinkConfigServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.WANCableLinkConfig", new WANCableLinkConfigSkeleton);
}


void WANCableLinkConfigServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void WANCableLinkConfigServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.WANCableLinkConfig", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

