//
// WANDSLLinkConfigEventSubscriber.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigEventSubscriber
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


#include "UPnPS/InternetGateway1/WANDSLLinkConfigEventSubscriber.h"
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


class InternetGateway1_API WANDSLLinkConfigEvent__autoConfigChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANDSLLinkConfigEvent__autoConfigChangedMethodHandler(WANDSLLinkConfigProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"AutoConfig","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->autoConfigChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANDSLLinkConfigProxy* _pProxy;
};


class InternetGateway1_API WANDSLLinkConfigEvent__linkStatusChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANDSLLinkConfigEvent__linkStatusChangedMethodHandler(WANDSLLinkConfigProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"LinkStatus","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->linkStatusChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANDSLLinkConfigProxy* _pProxy;
};


WANDSLLinkConfigEventSubscriber::WANDSLLinkConfigEventSubscriber(const std::string& uri, WANDSLLinkConfigProxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("AutoConfig", new UPnPS::InternetGateway1::WANDSLLinkConfigEvent__autoConfigChangedMethodHandler(pProxy));
	addMethodHandler("LinkStatus", new UPnPS::InternetGateway1::WANDSLLinkConfigEvent__linkStatusChangedMethodHandler(pProxy));
}


WANDSLLinkConfigEventSubscriber::~WANDSLLinkConfigEventSubscriber()
{
}


void WANDSLLinkConfigEventSubscriber::event__autoConfigChanged(const bool& data)
{
}


void WANDSLLinkConfigEventSubscriber::event__linkStatusChanged(const std::string& data)
{
}


const std::string WANDSLLinkConfigEventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service: WANDSLLinkConfig:1");
} // namespace InternetGateway1
} // namespace UPnPS

