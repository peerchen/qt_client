//
// SwitchPowerEventSubscriber.h
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerEventSubscriber
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


#ifndef LightingControls1_SwitchPowerEventSubscriber_INCLUDED
#define LightingControls1_SwitchPowerEventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/LightingControls1/LightingControls1.h"
#include "UPnPS/LightingControls1/SwitchPowerProxy.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API SwitchPowerEventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	SwitchPowerEventSubscriber(const std::string& uri, SwitchPowerProxy* pProxy);
		/// Creates a SwitchPowerEventSubscriber.

	virtual ~SwitchPowerEventSubscriber();
		/// Destroys the SwitchPowerEventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__statusChanged(const bool& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchPowerEventSubscriber::remoting__typeId() const
{
	return ISwitchPower::remoting__typeId();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_SwitchPowerEventSubscriber_INCLUDED

