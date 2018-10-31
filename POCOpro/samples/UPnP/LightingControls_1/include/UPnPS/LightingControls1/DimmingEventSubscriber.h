//
// DimmingEventSubscriber.h
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingEventSubscriber
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


#ifndef LightingControls1_DimmingEventSubscriber_INCLUDED
#define LightingControls1_DimmingEventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/LightingControls1/DimmingProxy.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingEventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	DimmingEventSubscriber(const std::string& uri, DimmingProxy* pProxy);
		/// Creates a DimmingEventSubscriber.

	virtual ~DimmingEventSubscriber();
		/// Destroys the DimmingEventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__isRampingChanged(const bool& data);

	void event__loadLevelStatusChanged(const Poco::UInt8& data);

	void event__rampPausedChanged(const bool& data);

	void event__rampRateChanged(const Poco::UInt8& data);

	void event__stepDeltaChanged(const Poco::UInt8& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DimmingEventSubscriber::remoting__typeId() const
{
	return IDimming::remoting__typeId();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_DimmingEventSubscriber_INCLUDED

