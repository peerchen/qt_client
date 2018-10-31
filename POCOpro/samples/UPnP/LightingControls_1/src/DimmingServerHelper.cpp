//
// DimmingServerHelper.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingServerHelper
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


#include "UPnPS/LightingControls1/DimmingServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/LightingControls1/DimmingEventDispatcher.h"
#include "UPnPS/LightingControls1/DimmingSkeleton.h"


namespace UPnPS {
namespace LightingControls1 {


namespace
{
	static Poco::SingletonHolder<DimmingServerHelper> shDimmingServerHelper;
}


DimmingServerHelper::DimmingServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


DimmingServerHelper::~DimmingServerHelper()
{
}


void DimmingServerHelper::shutdown()
{
	DimmingServerHelper::instance().unregisterSkeleton();
	shDimmingServerHelper.reset();
}


Poco::AutoPtr<UPnPS::LightingControls1::DimmingRemoteObject> DimmingServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::LightingControls1::Dimming> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new DimmingRemoteObject(oid, pServiceObject);
}


void DimmingServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<DimmingRemoteObject> pRemoteObject = pIdentifiable.cast<DimmingRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


DimmingServerHelper& DimmingServerHelper::instance()
{
	return *shDimmingServerHelper.get();
}


std::string DimmingServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::LightingControls1::DimmingRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void DimmingServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.LightingControls1.Dimming", new DimmingSkeleton);
}


void DimmingServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void DimmingServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.LightingControls1.Dimming", true);
}


} // namespace LightingControls1
} // namespace UPnPS

