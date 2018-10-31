//
// IDimming.h
//
// Library: LightingControls1
// Package: Generated
// Module:  IDimming
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


#ifndef LightingControls1_IDimming_INCLUDED
#define LightingControls1_IDimming_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/LightingControls1/Dimming.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API IDimming: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IDimming> Ptr;

	IDimming();
		/// Creates a IDimming.

	virtual ~IDimming();
		/// Destroys the IDimming.

	virtual void getIsRamping(bool& retIsRamping) = 0;

	virtual void getLoadLevelStatus(Poco::UInt8& retLoadlevelStatus) = 0;

	virtual void getLoadLevelTarget(Poco::UInt8& getLoadlevelTarget) = 0;

	virtual void getOnEffectParameters(std::string& retOnEffect, Poco::UInt8& retOnEffectLevel) = 0;

	virtual void getRampPaused(bool& retRampPaused) = 0;

	virtual void getRampRate(Poco::UInt8& retRampRate) = 0;

	virtual void getRampTime(Poco::UInt32& retRampTime) = 0;

	virtual void getStepDelta(Poco::UInt8& retStepDelta) = 0;

	virtual void pauseRamp() = 0;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void resumeRamp() = 0;

	virtual void setLoadLevelTarget(Poco::UInt8 newLoadlevelTarget) = 0;

	virtual void setOnEffect(const std::string& newOnEffect) = 0;

	virtual void setOnEffectLevel(Poco::UInt8 newOnEffectLevel) = 0;

	virtual void setRampRate(Poco::UInt8 newRampRate) = 0;

	virtual void setStepDelta(Poco::UInt8 newStepDelta) = 0;

	virtual void startRampDown() = 0;

	virtual void startRampToLevel(Poco::UInt8 newLoadLevelTarget, Poco::UInt32 newRampTime) = 0;

	virtual void startRampUp() = 0;

	virtual void stepDown() = 0;

	virtual void stepUp() = 0;

	virtual void stopRamp() = 0;

	Poco::BasicEvent < const bool > isRampingChanged;
	Poco::BasicEvent < const Poco::UInt8 > loadLevelStatusChanged;
	Poco::BasicEvent < const bool > rampPausedChanged;
	Poco::BasicEvent < const Poco::UInt8 > rampRateChanged;
	Poco::BasicEvent < const Poco::UInt8 > stepDeltaChanged;
};


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_IDimming_INCLUDED

