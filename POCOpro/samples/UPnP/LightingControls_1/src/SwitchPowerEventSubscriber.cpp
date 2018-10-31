//
// SwitchPowerEventSubscriber.cpp
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


#include "UPnPS/LightingControls1/SwitchPowerEventSubscriber.h"
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


class LightingControls1_API SwitchPowerEvent__statusChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	SwitchPowerEvent__statusChangedMethodHandler(SwitchPowerProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"Status","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->statusChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	SwitchPowerProxy* _pProxy;
};


SwitchPowerEventSubscriber::SwitchPowerEventSubscriber(const std::string& uri, SwitchPowerProxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("Status", new UPnPS::LightingControls1::SwitchPowerEvent__statusChangedMethodHandler(pProxy));
}


SwitchPowerEventSubscriber::~SwitchPowerEventSubscriber()
{
}


void SwitchPowerEventSubscriber::event__statusChanged(const bool& data)
{
}


const std::string SwitchPowerEventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:SwitchPower:1");
} // namespace LightingControls1
} // namespace UPnPS

