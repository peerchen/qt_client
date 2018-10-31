//
// DimmingImpl.h
//
// $Id: //poco/1.7/UPnP/samples/NetworkLight/src/DimmingImpl.h#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef DimmingImpl_INCLUDED
#define DimmingImpl_INCLUDED


#include "UPnPS/LightingControls1/Dimming.h"
#include "Poco/UPnP/GENA/EventedStateVariable.h"
#include "Poco/UPnP/GENA/EventModerationPolicy.h"
#include "Poco/UPnP/GENA/StateProvider.h"
#include "Poco/Util/Timer.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"


class DimmableLight;


class DimmingImpl: public UPnPS::LightingControls1::Dimming, public Poco::UPnP::GENA::StateProvider
{
public:
	DimmingImpl(DimmableLight& dimmableLight);
		/// Creates a DimmingImpl.

	virtual ~DimmingImpl();
		/// Destroys the DimmingImpl.

	// Dimming
	void getIsRamping(bool& retIsRamping);
	void getLoadLevelStatus(Poco::UInt8& retLoadlevelStatus);
	void getLoadLevelTarget(Poco::UInt8& getLoadlevelTarget);
	void getOnEffectParameters(std::string& retOnEffect, Poco::UInt8& retOnEffectLevel);
	void getRampPaused(bool& retRampPaused);
	void getRampRate(Poco::UInt8& retRampRate);
	void getRampTime(Poco::UInt32& retRampTime);
	void getStepDelta(Poco::UInt8& retStepDelta);
	void pauseRamp();
	void resumeRamp();
	void setLoadLevelTarget(Poco::UInt8 newLoadlevelTarget);
	void setOnEffect(const std::string& newOnEffect);
	void setOnEffectLevel(Poco::UInt8 newOnEffectLevel);
	void setRampRate(Poco::UInt8 newRampRate);
	void setStepDelta(Poco::UInt8 newStepDelta);
	void startRampDown();
	void startRampToLevel(Poco::UInt8 newLoadLevelTarget, Poco::UInt32 newRampTime);
	void startRampUp();
	void stepDown();
	void stepUp();
	void stopRamp();
	
	// StateProvider
	Poco::UPnP::GENA::StateProvider::StateVec currentState() const;
	
protected:
	static const std::string ON_EFFECT_LEVEL;
	static const std::string ON_EFFECT_LAST_SETTING;
	static const std::string ON_EFFECT_DEFAULT;

	void onTimer(Poco::Util::TimerTask& timerTask);

private:
	Poco::UPnP::GENA::EventedStateVariable<bool, Poco::UPnP::GENA::NoModerationPolicy<bool> > _isRamping;
	Poco::UPnP::GENA::EventedStateVariable<Poco::UInt8, Poco::UPnP::GENA::NoModerationPolicy<Poco::UInt8> > _loadLevelStatus;
	Poco::UPnP::GENA::EventedStateVariable<bool, Poco::UPnP::GENA::NoModerationPolicy<bool> > _rampPaused;
	Poco::UPnP::GENA::EventedStateVariable<Poco::UInt8, Poco::UPnP::GENA::NoModerationPolicy<Poco::UInt8> > _rampRate;
	Poco::UPnP::GENA::EventedStateVariable<Poco::UInt8, Poco::UPnP::GENA::NoModerationPolicy<Poco::UInt8> > _stepDelta;
	Poco::UInt8 _loadLevelTarget;
	Poco::UInt8 _onEffectLevel;
	std::string _onEffect;

	DimmableLight& _dimmableLight;
	Poco::Util::Timer _timer;
	Poco::Logger& _logger;
	Poco::FastMutex _mutex;
};


#endif // DimmingImpl_INCLUDED
