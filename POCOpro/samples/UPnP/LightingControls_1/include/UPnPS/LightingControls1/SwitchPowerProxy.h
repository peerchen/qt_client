//
// SwitchPowerProxy.h
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerProxy
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


#ifndef LightingControls1_SwitchPowerProxy_INCLUDED
#define LightingControls1_SwitchPowerProxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/LightingControls1/ISwitchPower.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API SwitchPowerProxy: public UPnPS::LightingControls1::ISwitchPower, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<SwitchPowerProxy> Ptr;

	SwitchPowerProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a SwitchPowerProxy.

	virtual ~SwitchPowerProxy();
		/// Destroys the SwitchPowerProxy.

	virtual void getStatus(bool& resultStatus);

	virtual void getTarget(bool& retTargetValue);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setTarget(bool newTargetValue);

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchPowerProxy::remoting__typeId() const
{
	return ISwitchPower::remoting__typeId();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_SwitchPowerProxy_INCLUDED

