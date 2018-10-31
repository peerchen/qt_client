//
// SwitchPowerImpl.h
//
// $Id: //poco/1.7/UPnP/samples/NetworkLight/src/SwitchPowerImpl.h#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef SwitchPowerImpl_INCLUDED
#define SwitchPowerImpl_INCLUDED


#include "UPnPS/LightingControls1/SwitchPower.h"
#include "Poco/UPnP/GENA/EventedStateVariable.h"
#include "Poco/UPnP/GENA/EventModerationPolicy.h"
#include "Poco/UPnP/GENA/StateProvider.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"


class DimmableLight;


class SwitchPowerImpl: public UPnPS::LightingControls1::SwitchPower, public Poco::UPnP::GENA::StateProvider
{
public:
	SwitchPowerImpl(DimmableLight& dimmableLight);
		/// Creates a SwitchPowerImpl.

	virtual ~SwitchPowerImpl();
		/// Destroys the SwitchPowerImpl.

	// SwitchPower
	void getStatus(bool& resultStatus);
	void getTarget(bool& retTargetValue);
	void setTarget(bool newTargetValue);

	// StateProvider
	Poco::UPnP::GENA::StateProvider::StateVec currentState() const;

private:
	Poco::UPnP::GENA::EventedStateVariable<bool, Poco::UPnP::GENA::NoModerationPolicy<bool> > _status;

	DimmableLight& _dimmableLight;
	Poco::Logger& _logger;
	Poco::FastMutex _mutex;
};


#endif // SwitchPowerImpl_INCLUDED
