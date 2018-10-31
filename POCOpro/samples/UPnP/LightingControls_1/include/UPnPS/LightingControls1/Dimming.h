//
// Dimming.h
//
// Library: LightingControls1
// Package: LightingControls1
// Module:  Dimming
//
// This file has been generated on 2012-10-29 10:08:38 UTC.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef LightingControls1_Dimming_INCLUDED
#define LightingControls1_Dimming_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


//@ namespace="urn:schemas-upnp-org:service:Dimming:1"
//@ remote
class LightingControls1_API Dimming
{
public:
	typedef Poco::SharedPtr<Dimming> Ptr;

	Dimming();
		/// Creates a Dimming.

	virtual ~Dimming();
		/// Destroys the Dimming.

	//@ $retIsRamping={name="retIsRamping", direction=out}
	//@ name=GetIsRamping
	//@ optional=true
	//@ replyName=GetIsRampingResponse
	virtual void getIsRamping(bool& retIsRamping) = 0;

	//@ $retLoadlevelStatus={name="retLoadlevelStatus", direction=out}
	//@ name=GetLoadLevelStatus
	//@ replyName=GetLoadLevelStatusResponse
	virtual void getLoadLevelStatus(Poco::UInt8& retLoadlevelStatus) = 0;

	//@ $getLoadlevelTarget={name="GetLoadlevelTarget", direction=out}
	//@ name=GetLoadLevelTarget
	//@ replyName=GetLoadLevelTargetResponse
	virtual void getLoadLevelTarget(Poco::UInt8& getLoadlevelTarget) = 0;

	//@ $retOnEffect={name="retOnEffect", direction=out}
	//@ $retOnEffectLevel={name="retOnEffectLevel", direction=out}
	//@ name=GetOnEffectParameters
	//@ optional=true
	//@ replyName=GetOnEffectParametersResponse
	virtual void getOnEffectParameters(std::string& retOnEffect, Poco::UInt8& retOnEffectLevel) = 0;

	//@ $retRampPaused={name="retRampPaused", direction=out}
	//@ name=GetRampPaused
	//@ optional=true
	//@ replyName=GetRampPausedResponse
	virtual void getRampPaused(bool& retRampPaused) = 0;

	//@ $retRampRate={name="retRampRate", direction=out}
	//@ name=GetRampRate
	//@ optional=true
	//@ replyName=GetRampRateResponse
	virtual void getRampRate(Poco::UInt8& retRampRate) = 0;

	//@ $retRampTime={name="retRampTime", direction=out}
	//@ name=GetRampTime
	//@ optional=true
	//@ replyName=GetRampTimeResponse
	virtual void getRampTime(Poco::UInt32& retRampTime) = 0;

	//@ $retStepDelta={name="retStepDelta", direction=out}
	//@ name=GetStepDelta
	//@ optional=true
	//@ replyName=GetStepDeltaResponse
	virtual void getStepDelta(Poco::UInt8& retStepDelta) = 0;

	//@ name=PauseRamp
	//@ optional=true
	//@ replyName=PauseRampResponse
	virtual void pauseRamp() = 0;

	//@ name=ResumeRamp
	//@ optional=true
	//@ replyName=ResumeRampResponse
	virtual void resumeRamp() = 0;

	//@ $newLoadlevelTarget={name="newLoadlevelTarget"}
	//@ name=SetLoadLevelTarget
	//@ replyName=SetLoadLevelTargetResponse
	virtual void setLoadLevelTarget(Poco::UInt8 newLoadlevelTarget) = 0;

	//@ $newOnEffect={name="newOnEffect"}
	//@ name=SetOnEffect
	//@ optional=true
	//@ replyName=SetOnEffectResponse
	virtual void setOnEffect(const std::string& newOnEffect) = 0;

	//@ $newOnEffectLevel={name="newOnEffectLevel"}
	//@ name=SetOnEffectLevel
	//@ optional=true
	//@ replyName=SetOnEffectLevelResponse
	virtual void setOnEffectLevel(Poco::UInt8 newOnEffectLevel) = 0;

	//@ $newRampRate={name="newRampRate"}
	//@ name=SetRampRate
	//@ optional=true
	//@ replyName=SetRampRateResponse
	virtual void setRampRate(Poco::UInt8 newRampRate) = 0;

	//@ $newStepDelta={name="newStepDelta"}
	//@ name=SetStepDelta
	//@ optional=true
	//@ replyName=SetStepDeltaResponse
	virtual void setStepDelta(Poco::UInt8 newStepDelta) = 0;

	//@ name=StartRampDown
	//@ optional=true
	//@ replyName=StartRampDownResponse
	virtual void startRampDown() = 0;

	//@ $newLoadLevelTarget={name="newLoadLevelTarget"}
	//@ $newRampTime={name="newRampTime"}
	//@ name=StartRampToLevel
	//@ optional=true
	//@ replyName=StartRampToLevelResponse
	virtual void startRampToLevel(Poco::UInt8 newLoadLevelTarget, Poco::UInt32 newRampTime) = 0;

	//@ name=StartRampUp
	//@ optional=true
	//@ replyName=StartRampUpResponse
	virtual void startRampUp() = 0;

	//@ name=StepDown
	//@ optional=true
	//@ replyName=StepDownResponse
	virtual void stepDown() = 0;

	//@ name=StepUp
	//@ optional=true
	//@ replyName=StepUpResponse
	virtual void stepUp() = 0;

	//@ name=StopRamp
	//@ optional=true
	//@ replyName=StopRampResponse
	virtual void stopRamp() = 0;

	//@ name=IsRamping
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const bool> isRampingChanged;
	//@ name=LoadLevelStatus
	//@ oneway=true
	Poco::BasicEvent<const Poco::UInt8> loadLevelStatusChanged;
	//@ name=RampPaused
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const bool> rampPausedChanged;
	//@ name=RampRate
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const Poco::UInt8> rampRateChanged;
	//@ name=StepDelta
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const Poco::UInt8> stepDeltaChanged;
};


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_Dimming_INCLUDED

