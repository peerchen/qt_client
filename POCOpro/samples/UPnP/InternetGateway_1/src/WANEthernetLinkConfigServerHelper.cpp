//
// WANEthernetLinkConfigServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANEthernetLinkConfigServerHelper
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


#include "UPnPS/InternetGateway1/WANEthernetLinkConfigServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANEthernetLinkConfigEventDispatcher.h"
#include "UPnPS/InternetGateway1/WANEthernetLinkConfigSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANEthernetLinkConfigServerHelper> shWANEthernetLinkConfigServerHelper;
}


WANEthernetLinkConfigServerHelper::WANEthernetLinkConfigServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


WANEthernetLinkConfigServerHelper::~WANEthernetLinkConfigServerHelper()
{
}


void WANEthernetLinkConfigServerHelper::shutdown()
{
	WANEthernetLinkConfigServerHelper::instance().unregisterSkeleton();
	shWANEthernetLinkConfigServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::WANEthernetLinkConfigRemoteObject> WANEthernetLinkConfigServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WANEthernetLinkConfigRemoteObject(oid, pServiceObject);
}


void WANEthernetLinkConfigServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<WANEthernetLinkConfigRemoteObject> pRemoteObject = pIdentifiable.cast<WANEthernetLinkConfigRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


WANEthernetLinkConfigServerHelper& WANEthernetLinkConfigServerHelper::instance()
{
	return *shWANEthernetLinkConfigServerHelper.get();
}


std::string WANEthernetLinkConfigServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANEthernetLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WANEthernetLinkConfigServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.WANEthernetLinkConfig", new WANEthernetLinkConfigSkeleton);
}


void WANEthernetLinkConfigServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void WANEthernetLinkConfigServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.WANEthernetLinkConfig", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

