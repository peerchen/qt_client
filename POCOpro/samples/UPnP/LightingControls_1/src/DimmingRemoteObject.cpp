//
// DimmingRemoteObject.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingRemoteObject
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


#include "UPnPS/LightingControls1/DimmingRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/LightingControls1/DimmingEventDispatcher.h"


namespace UPnPS {
namespace LightingControls1 {


DimmingRemoteObject::DimmingRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::LightingControls1::Dimming> pServiceObject):
	UPnPS::LightingControls1::IDimming(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->isRampingChanged += Poco::delegate(this, &DimmingRemoteObject::event__isRampingChanged);
	_pServiceObject->loadLevelStatusChanged += Poco::delegate(this, &DimmingRemoteObject::event__loadLevelStatusChanged);
	_pServiceObject->rampPausedChanged += Poco::delegate(this, &DimmingRemoteObject::event__rampPausedChanged);
	_pServiceObject->rampRateChanged += Poco::delegate(this, &DimmingRemoteObject::event__rampRateChanged);
	_pServiceObject->stepDeltaChanged += Poco::delegate(this, &DimmingRemoteObject::event__stepDeltaChanged);
}


DimmingRemoteObject::~DimmingRemoteObject()
{
	try
	{
		_pServiceObject->isRampingChanged -= Poco::delegate(this, &DimmingRemoteObject::event__isRampingChanged);
		_pServiceObject->loadLevelStatusChanged -= Poco::delegate(this, &DimmingRemoteObject::event__loadLevelStatusChanged);
		_pServiceObject->rampPausedChanged -= Poco::delegate(this, &DimmingRemoteObject::event__rampPausedChanged);
		_pServiceObject->rampRateChanged -= Poco::delegate(this, &DimmingRemoteObject::event__rampRateChanged);
		_pServiceObject->stepDeltaChanged -= Poco::delegate(this, &DimmingRemoteObject::event__stepDeltaChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string DimmingRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void DimmingRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new DimmingEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool DimmingRemoteObject::remoting__hasEvents() const
{
	return true;
}


void DimmingRemoteObject::event__isRampingChanged(const bool& data)
{
	isRampingChanged(this, data);
}


void DimmingRemoteObject::event__loadLevelStatusChanged(const Poco::UInt8& data)
{
	loadLevelStatusChanged(this, data);
}


void DimmingRemoteObject::event__rampPausedChanged(const bool& data)
{
	rampPausedChanged(this, data);
}


void DimmingRemoteObject::event__rampRateChanged(const Poco::UInt8& data)
{
	rampRateChanged(this, data);
}


void DimmingRemoteObject::event__stepDeltaChanged(const Poco::UInt8& data)
{
	stepDeltaChanged(this, data);
}


} // namespace LightingControls1
} // namespace UPnPS

