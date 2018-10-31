//
// AVTransport1EventSubscriber.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1EventSubscriber
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


#include "UPnPS/MediaServer1/AVTransport1EventSubscriber.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API AVTransport1Event__lastChangeChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	AVTransport1Event__lastChangeChangedMethodHandler(AVTransport1Proxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"LastChange","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->lastChangeChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	AVTransport1Proxy* _pProxy;
};


AVTransport1EventSubscriber::AVTransport1EventSubscriber(const std::string& uri, AVTransport1Proxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("LastChange", new UPnPS::MediaServer1::AVTransport1Event__lastChangeChangedMethodHandler(pProxy));
}


AVTransport1EventSubscriber::~AVTransport1EventSubscriber()
{
}


void AVTransport1EventSubscriber::event__lastChangeChanged(const std::string& data)
{
}


const std::string AVTransport1EventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:AVTransport:1");
} // namespace MediaServer1
} // namespace UPnPS

