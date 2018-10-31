//
// ISwitchPower.h
//
// Library: LightingControls1
// Package: Generated
// Module:  ISwitchPower
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


#ifndef LightingControls1_ISwitchPower_INCLUDED
#define LightingControls1_ISwitchPower_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/LightingControls1/LightingControls1.h"
#include "UPnPS/LightingControls1/SwitchPower.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API ISwitchPower: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<ISwitchPower> Ptr;

	ISwitchPower();
		/// Creates a ISwitchPower.

	virtual ~ISwitchPower();
		/// Destroys the ISwitchPower.

	virtual void getStatus(bool& resultStatus) = 0;

	virtual void getTarget(bool& retTargetValue) = 0;

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

	virtual void setTarget(bool newTargetValue) = 0;

	Poco::BasicEvent < const bool > statusChanged;
};


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_ISwitchPower_INCLUDED

