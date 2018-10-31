//
// WANCommonInterfaceConfigEventSubscriber.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigEventSubscriber
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


#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigEventSubscriber.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCommonInterfaceConfigEvent__enabledForInternetChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANCommonInterfaceConfigEvent__enabledForInternetChangedMethodHandler(WANCommonInterfaceConfigProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"EnabledForInternet","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->enabledForInternetChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANCommonInterfaceConfigProxy* _pProxy;
};


class InternetGateway1_API WANCommonInterfaceConfigEvent__numberOfActiveConnectionsChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANCommonInterfaceConfigEvent__numberOfActiveConnectionsChangedMethodHandler(WANCommonInterfaceConfigProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"NumberOfActiveConnections","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		Poco::UInt16 data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->numberOfActiveConnectionsChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANCommonInterfaceConfigProxy* _pProxy;
};


class InternetGateway1_API WANCommonInterfaceConfigEvent__physicalLinkStatusChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANCommonInterfaceConfigEvent__physicalLinkStatusChangedMethodHandler(WANCommonInterfaceConfigProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"PhysicalLinkStatus","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->physicalLinkStatusChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANCommonInterfaceConfigProxy* _pProxy;
};


WANCommonInterfaceConfigEventSubscriber::WANCommonInterfaceConfigEventSubscriber(const std::string& uri, WANCommonInterfaceConfigProxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("EnabledForInternet", new UPnPS::InternetGateway1::WANCommonInterfaceConfigEvent__enabledForInternetChangedMethodHandler(pProxy));
	addMethodHandler("NumberOfActiveConnections", new UPnPS::InternetGateway1::WANCommonInterfaceConfigEvent__numberOfActiveConnectionsChangedMethodHandler(pProxy));
	addMethodHandler("PhysicalLinkStatus", new UPnPS::InternetGateway1::WANCommonInterfaceConfigEvent__physicalLinkStatusChangedMethodHandler(pProxy));
}


WANCommonInterfaceConfigEventSubscriber::~WANCommonInterfaceConfigEventSubscriber()
{
}


void WANCommonInterfaceConfigEventSubscriber::event__enabledForInternetChanged(const bool& data)
{
}


void WANCommonInterfaceConfigEventSubscriber::event__numberOfActiveConnectionsChanged(const Poco::UInt16& data)
{
}


void WANCommonInterfaceConfigEventSubscriber::event__physicalLinkStatusChanged(const std::string& data)
{
}


const std::string WANCommonInterfaceConfigEventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:WANCommonInterfaceConfig:1");
} // namespace InternetGateway1
} // namespace UPnPS

