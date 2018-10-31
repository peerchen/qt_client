//
// DimmingProxy.h
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingProxy
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


#ifndef LightingControls1_DimmingProxy_INCLUDED
#define LightingControls1_DimmingProxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/LightingControls1/IDimming.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingProxy: public UPnPS::LightingControls1::IDimming, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<DimmingProxy> Ptr;

	DimmingProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a DimmingProxy.

	virtual ~DimmingProxy();
		/// Destroys the DimmingProxy.

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

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DimmingProxy::remoting__typeId() const
{
	return IDimming::remoting__typeId();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_DimmingProxy_INCLUDED

