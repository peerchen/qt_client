//
// DimmingRemoteObject.h
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


#ifndef LightingControls1_DimmingRemoteObject_INCLUDED
#define LightingControls1_DimmingRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/LightingControls1/IDimming.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingRemoteObject: public UPnPS::LightingControls1::IDimming, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<DimmingRemoteObject> Ptr;

	DimmingRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::LightingControls1::Dimming> pServiceObject);
		/// Creates a DimmingRemoteObject.

	virtual ~DimmingRemoteObject();
		/// Destroys the DimmingRemoteObject.

	virtual void getIsRamping(bool& retIsRamping);

	virtual void getLoadLevelStatus(Poco::UInt8& retLoadlevelStatus);

	virtual void getLoadLevelTarget(Poco::UInt8& getLoadlevelTarget);

	virtual void getOnEffectParameters(std::string& retOnEffect, Poco::UInt8& retOnEffectLevel);

	virtual void getRampPaused(bool& retRampPaused);

	virtual void getRampRate(Poco::UInt8& retRampRate);

	virtual void getRampTime(Poco::UInt32& retRampTime);

	virtual void getStepDelta(Poco::UInt8& retStepDelta);

	virtual void pauseRamp();

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void resumeRamp();

	virtual void setLoadLevelTarget(Poco::UInt8 newLoadlevelTarget);

	virtual void setOnEffect(const std::string& newOnEffect);

	virtual void setOnEffectLevel(Poco::UInt8 newOnEffectLevel);

	virtual void setRampRate(Poco::UInt8 newRampRate);

	virtual void setStepDelta(Poco::UInt8 newStepDelta);

	virtual void startRampDown();

	virtual void startRampToLevel(Poco::UInt8 newLoadLevelTarget, Poco::UInt32 newRampTime);

	virtual void startRampUp();

	virtual void stepDown();

	virtual void stepUp();

	virtual void stopRamp();

protected:
	void event__isRampingChanged(const bool& data);

	void event__loadLevelStatusChanged(const Poco::UInt8& data);

	void event__rampPausedChanged(const bool& data);

	void event__rampRateChanged(const Poco::UInt8& data);

	void event__stepDeltaChanged(const Poco::UInt8& data);

private:
	Poco::SharedPtr<UPnPS::LightingControls1::Dimming> _pServiceObject;
};


inline void DimmingRemoteObject::getIsRamping(bool& retIsRamping)
{
	_pServiceObject->getIsRamping(retIsRamping);
}


inline void DimmingRemoteObject::getLoadLevelStatus(Poco::UInt8& retLoadlevelStatus)
{
	_pServiceObject->getLoadLevelStatus(retLoadlevelStatus);
}


inline void DimmingRemoteObject::getLoadLevelTarget(Poco::UInt8& getLoadlevelTarget)
{
	_pServiceObject->getLoadLevelTarget(getLoadlevelTarget);
}


inline void DimmingRemoteObject::getOnEffectParameters(std::string& retOnEffect, Poco::UInt8& retOnEffectLevel)
{
	_pServiceObject->getOnEffectParameters(retOnEffect, retOnEffectLevel);
}


inline void DimmingRemoteObject::getRampPaused(bool& retRampPaused)
{
	_pServiceObject->getRampPaused(retRampPaused);
}


inline void DimmingRemoteObject::getRampRate(Poco::UInt8& retRampRate)
{
	_pServiceObject->getRampRate(retRampRate);
}


inline void DimmingRemoteObject::getRampTime(Poco::UInt32& retRampTime)
{
	_pServiceObject->getRampTime(retRampTime);
}


inline void DimmingRemoteObject::getStepDelta(Poco::UInt8& retStepDelta)
{
	_pServiceObject->getStepDelta(retStepDelta);
}


inline void DimmingRemoteObject::pauseRamp()
{
	_pServiceObject->pauseRamp();
}


inline const Poco::RemotingNG::Identifiable::TypeId& DimmingRemoteObject::remoting__typeId() const
{
	return IDimming::remoting__typeId();
}


inline void DimmingRemoteObject::resumeRamp()
{
	_pServiceObject->resumeRamp();
}


inline void DimmingRemoteObject::setLoadLevelTarget(Poco::UInt8 newLoadlevelTarget)
{
	_pServiceObject->setLoadLevelTarget(newLoadlevelTarget);
}


inline void DimmingRemoteObject::setOnEffect(const std::string& newOnEffect)
{
	_pServiceObject->setOnEffect(newOnEffect);
}


inline void DimmingRemoteObject::setOnEffectLevel(Poco::UInt8 newOnEffectLevel)
{
	_pServiceObject->setOnEffectLevel(newOnEffectLevel);
}


inline void DimmingRemoteObject::setRampRate(Poco::UInt8 newRampRate)
{
	_pServiceObject->setRampRate(newRampRate);
}


inline void DimmingRemoteObject::setStepDelta(Poco::UInt8 newStepDelta)
{
	_pServiceObject->setStepDelta(newStepDelta);
}


inline void DimmingRemoteObject::startRampDown()
{
	_pServiceObject->startRampDown();
}


inline void DimmingRemoteObject::startRampToLevel(Poco::UInt8 newLoadLevelTarget, Poco::UInt32 newRampTime)
{
	_pServiceObject->startRampToLevel(newLoadLevelTarget, newRampTime);
}


inline void DimmingRemoteObject::startRampUp()
{
	_pServiceObject->startRampUp();
}


inline void DimmingRemoteObject::stepDown()
{
	_pServiceObject->stepDown();
}


inline void DimmingRemoteObject::stepUp()
{
	_pServiceObject->stepUp();
}


inline void DimmingRemoteObject::stopRamp()
{
	_pServiceObject->stopRamp();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_DimmingRemoteObject_INCLUDED

