//
// LANHostConfigManagementServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  LANHostConfigManagementServerHelper
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


#include "UPnPS/InternetGateway1/LANHostConfigManagementServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/LANHostConfigManagementSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<LANHostConfigManagementServerHelper> shLANHostConfigManagementServerHelper;
}


LANHostConfigManagementServerHelper::LANHostConfigManagementServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


LANHostConfigManagementServerHelper::~LANHostConfigManagementServerHelper()
{
}


void LANHostConfigManagementServerHelper::shutdown()
{
	LANHostConfigManagementServerHelper::instance().unregisterSkeleton();
	shLANHostConfigManagementServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::LANHostConfigManagementRemoteObject> LANHostConfigManagementServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new LANHostConfigManagementRemoteObject(oid, pServiceObject);
}


LANHostConfigManagementServerHelper& LANHostConfigManagementServerHelper::instance()
{
	return *shLANHostConfigManagementServerHelper.get();
}


std::string LANHostConfigManagementServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::LANHostConfigManagementRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void LANHostConfigManagementServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.LANHostConfigManagement", new LANHostConfigManagementSkeleton);
}


void LANHostConfigManagementServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void LANHostConfigManagementServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.LANHostConfigManagement", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

