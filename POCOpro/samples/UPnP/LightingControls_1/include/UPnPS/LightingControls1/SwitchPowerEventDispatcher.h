//
// SwitchPowerEventDispatcher.h
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerEventDispatcher
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


#ifndef LightingControls1_SwitchPowerEventDispatcher_INCLUDED
#define LightingControls1_SwitchPowerEventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/LightingControls1/LightingControls1.h"
#include "UPnPS/LightingControls1/SwitchPowerRemoteObject.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API SwitchPowerEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	SwitchPowerEventDispatcher(SwitchPowerRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a SwitchPowerEventDispatcher.

	virtual ~SwitchPowerEventDispatcher();
		/// Destroys the SwitchPowerEventDispatcher.

	void event__statusChanged(const void* pSender, const bool& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__statusChangedImpl(const std::string& subscriberURI, const bool& data);

	static const std::string DEFAULT_NS;
	SwitchPowerRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchPowerEventDispatcher::remoting__typeId() const
{
	return ISwitchPower::remoting__typeId();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_SwitchPowerEventDispatcher_INCLUDED

