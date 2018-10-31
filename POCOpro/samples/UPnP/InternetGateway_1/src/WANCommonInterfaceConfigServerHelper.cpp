//
// WANCommonInterfaceConfigServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigServerHelper
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


#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigEventDispatcher.h"
#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANCommonInterfaceConfigServerHelper> shWANCommonInterfaceConfigServerHelper;
}


WANCommonInterfaceConfigServerHelper::WANCommonInterfaceConfigServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


WANCommonInterfaceConfigServerHelper::~WANCommonInterfaceConfigServerHelper()
{
}


void WANCommonInterfaceConfigServerHelper::shutdown()
{
	WANCommonInterfaceConfigServerHelper::instance().unregisterSkeleton();
	shWANCommonInterfaceConfigServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject> WANCommonInterfaceConfigServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANCommonInterfaceConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WANCommonInterfaceConfigRemoteObject(oid, pServiceObject);
}


void WANCommonInterfaceConfigServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<WANCommonInterfaceConfigRemoteObject> pRemoteObject = pIdentifiable.cast<WANCommonInterfaceConfigRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


WANCommonInterfaceConfigServerHelper& WANCommonInterfaceConfigServerHelper::instance()
{
	return *shWANCommonInterfaceConfigServerHelper.get();
}


std::string WANCommonInterfaceConfigServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WANCommonInterfaceConfigServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.WANCommonInterfaceConfig", new WANCommonInterfaceConfigSkeleton);
}


void WANCommonInterfaceConfigServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void WANCommonInterfaceConfigServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.WANCommonInterfaceConfig", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

