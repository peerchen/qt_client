//
// WANPOTSLinkConfigServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPOTSLinkConfigServerHelper
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


#include "UPnPS/InternetGateway1/WANPOTSLinkConfigServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANPOTSLinkConfigSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANPOTSLinkConfigServerHelper> shWANPOTSLinkConfigServerHelper;
}


WANPOTSLinkConfigServerHelper::WANPOTSLinkConfigServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


WANPOTSLinkConfigServerHelper::~WANPOTSLinkConfigServerHelper()
{
}


void WANPOTSLinkConfigServerHelper::shutdown()
{
	WANPOTSLinkConfigServerHelper::instance().unregisterSkeleton();
	shWANPOTSLinkConfigServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::WANPOTSLinkConfigRemoteObject> WANPOTSLinkConfigServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WANPOTSLinkConfigRemoteObject(oid, pServiceObject);
}


WANPOTSLinkConfigServerHelper& WANPOTSLinkConfigServerHelper::instance()
{
	return *shWANPOTSLinkConfigServerHelper.get();
}


std::string WANPOTSLinkConfigServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANPOTSLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WANPOTSLinkConfigServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.WANPOTSLinkConfig", new WANPOTSLinkConfigSkeleton);
}


void WANPOTSLinkConfigServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void WANPOTSLinkConfigServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.WANPOTSLinkConfig", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

