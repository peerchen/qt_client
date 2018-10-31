//
// WANDSLLinkConfigServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigServerHelper
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


#include "UPnPS/InternetGateway1/WANDSLLinkConfigServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfigEventDispatcher.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfigSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANDSLLinkConfigServerHelper> shWANDSLLinkConfigServerHelper;
}


WANDSLLinkConfigServerHelper::WANDSLLinkConfigServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


WANDSLLinkConfigServerHelper::~WANDSLLinkConfigServerHelper()
{
}


void WANDSLLinkConfigServerHelper::shutdown()
{
	WANDSLLinkConfigServerHelper::instance().unregisterSkeleton();
	shWANDSLLinkConfigServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::WANDSLLinkConfigRemoteObject> WANDSLLinkConfigServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WANDSLLinkConfigRemoteObject(oid, pServiceObject);
}


void WANDSLLinkConfigServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<WANDSLLinkConfigRemoteObject> pRemoteObject = pIdentifiable.cast<WANDSLLinkConfigRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


WANDSLLinkConfigServerHelper& WANDSLLinkConfigServerHelper::instance()
{
	return *shWANDSLLinkConfigServerHelper.get();
}


std::string WANDSLLinkConfigServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANDSLLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WANDSLLinkConfigServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.WANDSLLinkConfig", new WANDSLLinkConfigSkeleton);
}


void WANDSLLinkConfigServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void WANDSLLinkConfigServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.WANDSLLinkConfig", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

