//
// SwitchPowerRemoteObject.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerRemoteObject
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


#include "UPnPS/LightingControls1/SwitchPowerRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/LightingControls1/SwitchPowerEventDispatcher.h"


namespace UPnPS {
namespace LightingControls1 {


SwitchPowerRemoteObject::SwitchPowerRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> pServiceObject):
	UPnPS::LightingControls1::ISwitchPower(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->statusChanged += Poco::delegate(this, &SwitchPowerRemoteObject::event__statusChanged);
}


SwitchPowerRemoteObject::~SwitchPowerRemoteObject()
{
	try
	{
		_pServiceObject->statusChanged -= Poco::delegate(this, &SwitchPowerRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string SwitchPowerRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void SwitchPowerRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new SwitchPowerEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool SwitchPowerRemoteObject::remoting__hasEvents() const
{
	return true;
}


void SwitchPowerRemoteObject::event__statusChanged(const bool& data)
{
	statusChanged(this, data);
}


} // namespace LightingControls1
} // namespace UPnPS

