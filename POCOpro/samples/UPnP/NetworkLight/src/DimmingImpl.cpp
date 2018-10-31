//
// DimmingImpl.cpp
//
// Module:  DimmingImpl
//
// This file has been generated on 2011-03-28 15:51:59 UTC.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#include "DimmingImpl.h"
#include "DimmableLight.h"
#include "Poco/UPnP/UPnPException.h"
#include "Poco/Util/TimerTaskAdapter.h"


const std::string DimmingImpl::ON_EFFECT_LEVEL("OnEffectLevel");
const std::string DimmingImpl::ON_EFFECT_LAST_SETTING("LastSetting");
const std::string DimmingImpl::ON_EFFECT_DEFAULT("Default");


DimmingImpl::DimmingImpl(DimmableLight& dimmableLight):
	_isRamping("IsRamping", false, Poco::UPnP::GENA::NoModerationPolicy<bool>(isRampingChanged)),
	_loadLevelStatus("LoadLevelStatus", 100, Poco::UPnP::GENA::NoModerationPolicy<Poco::UInt8>(loadLevelStatusChanged)),
	_rampPaused("RampPaused", false, Poco::UPnP::GENA::NoModerationPolicy<bool>(rampPausedChanged)),
	_rampRate("RampRate", 20, Poco::UPnP::GENA::NoModerationPolicy<Poco::UInt8>(rampRateChanged)),
	_stepDelta("StepDelta", 10, Poco::UPnP::GENA::NoModerationPolicy<Poco::UInt8>(stepDeltaChanged)),
	_loadLevelTarget(100),
	_onEffectLevel(100),
	_onEffect(ON_EFFECT_LEVEL),
	_dimmableLight(dimmableLight),
	_logger(Poco::Logger::get("DimmingImpl"))
{
	_timer.scheduleAtFixedRate(new Poco::Util::TimerTaskAdapter<DimmingImpl>(*this, &DimmingImpl::onTimer), 1000, 1000);
}


DimmingImpl::~DimmingImpl()
{
}


void DimmingImpl::getIsRamping(bool& retIsRamping)
{
	_logger.debug("Entering DimmingImpl::getIsRamping()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	retIsRamping = _isRamping.get();
}


void DimmingImpl::getLoadLevelStatus(Poco::UInt8& retLoadlevelStatus)
{
	_logger.debug("Entering DimmingImpl::getLoadLevelStatus()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	retLoadlevelStatus = _loadLevelStatus.get();
}


void DimmingImpl::getLoadLevelTarget(Poco::UInt8& retLoadlevelTarget)
{
	_logger.debug("Entering DimmingImpl::getLoadLevelTarget()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	retLoadlevelTarget = _loadLevelTarget;
}


void DimmingImpl::getOnEffectParameters(std::string& retOnEffect, Poco::UInt8& retOnEffectLevel)
{
	_logger.debug("Entering DimmingImpl::getOnEffectParameters()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	retOnEffect = _onEffect;
	retOnEffectLevel = _onEffectLevel;
}


void DimmingImpl::getRampPaused(bool& retRampPaused)
{
	_logger.debug("Entering DimmingImpl::getRampPaused()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	retRampPaused = _rampPaused.get();
}


void DimmingImpl::getRampRate(Poco::UInt8& retRampRate)
{
	_logger.debug("Entering DimmingImpl::getRampRate()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	retRampRate = _rampRate.get();
}


void DimmingImpl::getRampTime(Poco::UInt32& retRampTime)
{
	_logger.debug("Entering DimmingImpl::getRampTime()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	retRampTime = 0;
}


void DimmingImpl::getStepDelta(Poco::UInt8& retStepDelta)
{
	_logger.debug("Entering DimmingImpl::getStepDelta()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	retStepDelta = _stepDelta.get();
}


void DimmingImpl::pauseRamp()
{
	_logger.debug("Entering DimmingImpl::pauseRamp()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_rampPaused.set(true);
}


void DimmingImpl::resumeRamp()
{
	_logger.debug("Entering DimmingImpl::resumeRamp()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_rampPaused.set(false);
}


void DimmingImpl::setLoadLevelTarget(Poco::UInt8 newLoadlevelTarget)
{
	_logger.debug("Entering DimmingImpl::setLoadLevelTarget()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (newLoadlevelTarget <= 100)
	{
		_loadLevelTarget = newLoadlevelTarget;
	}
	else throw Poco::UPnP::UPnPException("newLoadlevelTarget must be <= 100", Poco::UPnP::UPnPException::CODE_INVALID_ARGS);
}


void DimmingImpl::setOnEffect(const std::string& newOnEffect)
{
	_logger.debug("Entering DimmingImpl::setOnEffect()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (newOnEffect == ON_EFFECT_DEFAULT || newOnEffect == ON_EFFECT_LEVEL)
		_onEffect = ON_EFFECT_LEVEL;
	else if (newOnEffect == ON_EFFECT_LAST_SETTING)
		_onEffect = ON_EFFECT_LAST_SETTING;
	else throw Poco::UPnP::UPnPException("invalid value for newOnEffect", Poco::UPnP::UPnPException::CODE_INVALID_ARGS);
}


void DimmingImpl::setOnEffectLevel(Poco::UInt8 newOnEffectLevel)
{
	_logger.debug("Entering DimmingImpl::setOnEffectLevel()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (newOnEffectLevel <= 100)
	{
		_onEffectLevel = newOnEffectLevel;
	}
	else throw Poco::UPnP::UPnPException("newOnEffectLevel must be <= 100", Poco::UPnP::UPnPException::CODE_INVALID_ARGS);
}


void DimmingImpl::setRampRate(Poco::UInt8 newRampRate)
{
	_logger.debug("Entering DimmingImpl::setRampRate()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (newRampRate <= 100)
	{
		_rampRate.set(newRampRate);
	}
	else throw Poco::UPnP::UPnPException("newRampRate must be <= 100", Poco::UPnP::UPnPException::CODE_INVALID_ARGS);
}


void DimmingImpl::setStepDelta(Poco::UInt8 newStepDelta)
{
	_logger.debug("Entering DimmingImpl::setStepDelta()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (newStepDelta <= 100)
	{
		_stepDelta.set(newStepDelta);
	}
	else throw Poco::UPnP::UPnPException("newStepDelta must be <= 100", Poco::UPnP::UPnPException::CODE_INVALID_ARGS);
}


void DimmingImpl::startRampDown()
{
	_logger.debug("Entering DimmingImpl::startRampDown()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_loadLevelTarget = 0;
	_isRamping.set(true);
}


void DimmingImpl::startRampToLevel(Poco::UInt8 newLoadLevelTarget, Poco::UInt32 newRampTime)
{
	_logger.debug("Entering DimmingImpl::startRampToLevel()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	throw Poco::UPnP::UPnPException("StartRampToLevel", Poco::UPnP::UPnPException::CODE_OPTIONAL_ACTION_NOT_IMPLEMENTED);
}


void DimmingImpl::startRampUp()
{
	_logger.debug("Entering DimmingImpl::startRampUp()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_loadLevelTarget = 100;
	_isRamping.set(true);
}


void DimmingImpl::stepDown()
{
	_logger.debug("Entering DimmingImpl::stepDown()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_isRamping.set(false);
	Poco::UInt8 level = _dimmableLight.getLevel();
	if (level > _stepDelta.get())
		level -= _stepDelta.get();
	else
		level = 0;
	_dimmableLight.setLevel(level);
	_loadLevelTarget = level;
	_loadLevelStatus.set(level);
}


void DimmingImpl::stepUp()
{
	_logger.debug("Entering DimmingImpl::stepUp()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_isRamping.set(false);
	Poco::UInt8 level = _dimmableLight.getLevel();
	if (level <= 100 - _stepDelta.get())
		level += _stepDelta.get();
	else
		level = 100;
	_dimmableLight.setLevel(level);
	_loadLevelTarget = level;
	_loadLevelStatus.set(level);
}


void DimmingImpl::stopRamp()
{
	_logger.debug("Entering DimmingImpl::stopRamp()");
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	if (_isRamping.get())
	{
		Poco::UInt8 level = _dimmableLight.getLevel();
		_loadLevelTarget = level;
		_loadLevelStatus.set(level);
		_isRamping.set(false);
	}
}


Poco::UPnP::GENA::StateProvider::StateVec DimmingImpl::currentState() const
{
	Poco::UPnP::GENA::StateProvider::StateVec state;
	state.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair(_isRamping.name(), _isRamping.toString()));
	state.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair(_loadLevelStatus.name(), _loadLevelStatus.toString()));
	state.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair(_rampPaused.name(), _rampPaused.toString()));
	state.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair(_rampRate.name(), _rampRate.toString()));
	state.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair(_stepDelta.name(), _stepDelta.toString()));
	return state;
}


void DimmingImpl::onTimer(Poco::Util::TimerTask& timerTask)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (_isRamping.get() && !_rampPaused.get())
	{
		Poco::UInt8 level = _dimmableLight.getLevel();
		if (level < _loadLevelTarget)
		{
			if (level + _rampRate.get() < _loadLevelTarget)
			{
				level += _rampRate.get();
			}
			else
			{
				level = _loadLevelTarget;
				_loadLevelStatus.set(level);
				_isRamping.set(false);
			}
		}
		else if (level > _loadLevelTarget)
		{
			if (level > _rampRate.get() && level - _rampRate.get() > _loadLevelTarget)
			{
				level -= _rampRate.get();
			}
			else
			{
				level = _loadLevelTarget;
				_loadLevelStatus.set(level);
				_isRamping.set(false);
			}
		}
		else
		{
			_isRamping.set(false);
		}
		_dimmableLight.setLevel(level);
	}
}
