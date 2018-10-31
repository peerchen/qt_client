//
// SwitchPowerImpl.cpp
//
// $Id: //poco/1.7/UPnP/samples/NetworkLight/src/SwitchPowerImpl.cpp#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#include "SwitchPowerImpl.h"
#include "DimmableLight.h"
#include "Poco/Logger.h"


SwitchPowerImpl::SwitchPowerImpl(DimmableLight& dimmableLight):
	_status("Status", false, Poco::UPnP::GENA::NoModerationPolicy<bool>(statusChanged)),
	_dimmableLight(dimmableLight),
	_logger(Poco::Logger::get("SwitchPowerImpl"))
{
}


SwitchPowerImpl::~SwitchPowerImpl()
{
}


void SwitchPowerImpl::getStatus(bool& resultStatus)
{
	_logger.debug("Entering SwitchPowerImpl::getStatus()");
	resultStatus = _dimmableLight.isOn();
}


void SwitchPowerImpl::getTarget(bool& retTargetValue)
{
	_logger.debug("Entering SwitchPowerImpl::getTarget()");
	retTargetValue = _dimmableLight.isOn();
}


void SwitchPowerImpl::setTarget(bool newTargetValue)
{
	_logger.debug(Poco::format("Entering SwitchPowerImpl::setTarget(%b)", newTargetValue));

	if (newTargetValue)
		_dimmableLight.on();
	else
		_dimmableLight.off();
	_status.set(newTargetValue);
}


Poco::UPnP::GENA::StateProvider::StateVec SwitchPowerImpl::currentState() const
{
	Poco::UPnP::GENA::StateProvider::StateVec state;
	state.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair(_status.name(), _status.toString()));
	return state;
}
