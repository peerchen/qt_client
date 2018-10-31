//
// SwitchPowerServerHelper.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerServerHelper
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


#include "UPnPS/LightingControls1/SwitchPowerServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/LightingControls1/SwitchPowerEventDispatcher.h"
#include "UPnPS/LightingControls1/SwitchPowerSkeleton.h"


namespace UPnPS {
namespace LightingControls1 {


namespace
{
	static Poco::SingletonHolder<SwitchPowerServerHelper> shSwitchPowerServerHelper;
}


SwitchPowerServerHelper::SwitchPowerServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


SwitchPowerServerHelper::~SwitchPowerServerHelper()
{
}


void SwitchPowerServerHelper::shutdown()
{
	SwitchPowerServerHelper::instance().unregisterSkeleton();
	shSwitchPowerServerHelper.reset();
}


Poco::AutoPtr<UPnPS::LightingControls1::SwitchPowerRemoteObject> SwitchPowerServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new SwitchPowerRemoteObject(oid, pServiceObject);
}


void SwitchPowerServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<SwitchPowerRemoteObject> pRemoteObject = pIdentifiable.cast<SwitchPowerRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


SwitchPowerServerHelper& SwitchPowerServerHelper::instance()
{
	return *shSwitchPowerServerHelper.get();
}


std::string SwitchPowerServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::LightingControls1::SwitchPowerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void SwitchPowerServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.LightingControls1.SwitchPower", new SwitchPowerSkeleton);
}


void SwitchPowerServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void SwitchPowerServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.LightingControls1.SwitchPower", true);
}


} // namespace LightingControls1
} // namespace UPnPS

