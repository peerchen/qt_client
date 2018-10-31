//
// DimmingEventDispatcher.h
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingEventDispatcher
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


#ifndef LightingControls1_DimmingEventDispatcher_INCLUDED
#define LightingControls1_DimmingEventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/LightingControls1/DimmingRemoteObject.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	DimmingEventDispatcher(DimmingRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a DimmingEventDispatcher.

	virtual ~DimmingEventDispatcher();
		/// Destroys the DimmingEventDispatcher.

	void event__isRampingChanged(const void* pSender, const bool& data);

	void event__loadLevelStatusChanged(const void* pSender, const Poco::UInt8& data);

	void event__rampPausedChanged(const void* pSender, const bool& data);

	void event__rampRateChanged(const void* pSender, const Poco::UInt8& data);

	void event__stepDeltaChanged(const void* pSender, const Poco::UInt8& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__isRampingChangedImpl(const std::string& subscriberURI, const bool& data);

	void event__loadLevelStatusChangedImpl(const std::string& subscriberURI, const Poco::UInt8& data);

	void event__rampPausedChangedImpl(const std::string& subscriberURI, const bool& data);

	void event__rampRateChangedImpl(const std::string& subscriberURI, const Poco::UInt8& data);

	void event__stepDeltaChangedImpl(const std::string& subscriberURI, const Poco::UInt8& data);

	static const std::string DEFAULT_NS;
	DimmingRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DimmingEventDispatcher::remoting__typeId() const
{
	return IDimming::remoting__typeId();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_DimmingEventDispatcher_INCLUDED

