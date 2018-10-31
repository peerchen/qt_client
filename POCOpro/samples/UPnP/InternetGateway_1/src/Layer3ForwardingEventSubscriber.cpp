//
// Layer3ForwardingEventSubscriber.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingEventSubscriber
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


#include "UPnPS/InternetGateway1/Layer3ForwardingEventSubscriber.h"
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


class InternetGateway1_API Layer3ForwardingEvent__defaultConnectionServiceChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	Layer3ForwardingEvent__defaultConnectionServiceChangedMethodHandler(Layer3ForwardingProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"DefaultConnectionService","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->defaultConnectionServiceChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	Layer3ForwardingProxy* _pProxy;
};


Layer3ForwardingEventSubscriber::Layer3ForwardingEventSubscriber(const std::string& uri, Layer3ForwardingProxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("DefaultConnectionService", new UPnPS::InternetGateway1::Layer3ForwardingEvent__defaultConnectionServiceChangedMethodHandler(pProxy));
}


Layer3ForwardingEventSubscriber::~Layer3ForwardingEventSubscriber()
{
}


void Layer3ForwardingEventSubscriber::event__defaultConnectionServiceChanged(const std::string& data)
{
}


const std::string Layer3ForwardingEventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:Layer3Forwarding:1");
} // namespace InternetGateway1
} // namespace UPnPS

