//
// DimmingEventSubscriber.cpp
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


#include "UPnPS/LightingControls1/DimmingEventSubscriber.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingEvent__isRampingChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	DimmingEvent__isRampingChangedMethodHandler(DimmingProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"IsRamping","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->isRampingChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	DimmingProxy* _pProxy;
};


class LightingControls1_API DimmingEvent__loadLevelStatusChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	DimmingEvent__loadLevelStatusChangedMethodHandler(DimmingProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"LoadLevelStatus","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		Poco::UInt8 data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->loadLevelStatusChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	DimmingProxy* _pProxy;
};


class LightingControls1_API DimmingEvent__rampPausedChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	DimmingEvent__rampPausedChangedMethodHandler(DimmingProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"RampPaused","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->rampPausedChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	DimmingProxy* _pProxy;
};


class LightingControls1_API DimmingEvent__rampRateChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	DimmingEvent__rampRateChangedMethodHandler(DimmingProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"RampRate","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		Poco::UInt8 data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->rampRateChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	DimmingProxy* _pProxy;
};


class LightingControls1_API DimmingEvent__stepDeltaChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	DimmingEvent__stepDeltaChangedMethodHandler(DimmingProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"StepDelta","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		Poco::UInt8 data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->stepDeltaChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	DimmingProxy* _pProxy;
};


DimmingEventSubscriber::DimmingEventSubscriber(const std::string& uri, DimmingProxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("IsRamping", new UPnPS::LightingControls1::DimmingEvent__isRampingChangedMethodHandler(pProxy));
	addMethodHandler("LoadLevelStatus", new UPnPS::LightingControls1::DimmingEvent__loadLevelStatusChangedMethodHandler(pProxy));
	addMethodHandler("RampPaused", new UPnPS::LightingControls1::DimmingEvent__rampPausedChangedMethodHandler(pProxy));
	addMethodHandler("RampRate", new UPnPS::LightingControls1::DimmingEvent__rampRateChangedMethodHandler(pProxy));
	addMethodHandler("StepDelta", new UPnPS::LightingControls1::DimmingEvent__stepDeltaChangedMethodHandler(pProxy));
}


DimmingEventSubscriber::~DimmingEventSubscriber()
{
}


void DimmingEventSubscriber::event__isRampingChanged(const bool& data)
{
}


void DimmingEventSubscriber::event__loadLevelStatusChanged(const Poco::UInt8& data)
{
}


void DimmingEventSubscriber::event__rampPausedChanged(const bool& data)
{
}


void DimmingEventSubscriber::event__rampRateChanged(const Poco::UInt8& data)
{
}


void DimmingEventSubscriber::event__stepDeltaChanged(const Poco::UInt8& data)
{
}


const std::string DimmingEventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:Dimming:1");
} // namespace LightingControls1
} // namespace UPnPS

