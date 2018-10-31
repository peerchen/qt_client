//
// ContentDirectory1EventSubscriber.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1EventSubscriber
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


#include "UPnPS/MediaServer1/ContentDirectory1EventSubscriber.h"
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


class MediaServer1_API ContentDirectory1Event__containerUpdateIDsChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	ContentDirectory1Event__containerUpdateIDsChangedMethodHandler(ContentDirectory1Proxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"ContainerUpdateIDs","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->containerUpdateIDsChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	ContentDirectory1Proxy* _pProxy;
};


class MediaServer1_API ContentDirectory1Event__systemUpdateIDChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	ContentDirectory1Event__systemUpdateIDChangedMethodHandler(ContentDirectory1Proxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"SystemUpdateID","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		Poco::UInt32 data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->systemUpdateIDChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	ContentDirectory1Proxy* _pProxy;
};


class MediaServer1_API ContentDirectory1Event__transferIDsChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	ContentDirectory1Event__transferIDsChangedMethodHandler(ContentDirectory1Proxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"TransferIDs","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->transferIDsChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	ContentDirectory1Proxy* _pProxy;
};


ContentDirectory1EventSubscriber::ContentDirectory1EventSubscriber(const std::string& uri, ContentDirectory1Proxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("ContainerUpdateIDs", new UPnPS::MediaServer1::ContentDirectory1Event__containerUpdateIDsChangedMethodHandler(pProxy));
	addMethodHandler("SystemUpdateID", new UPnPS::MediaServer1::ContentDirectory1Event__systemUpdateIDChangedMethodHandler(pProxy));
	addMethodHandler("TransferIDs", new UPnPS::MediaServer1::ContentDirectory1Event__transferIDsChangedMethodHandler(pProxy));
}


ContentDirectory1EventSubscriber::~ContentDirectory1EventSubscriber()
{
}


void ContentDirectory1EventSubscriber::event__containerUpdateIDsChanged(const std::string& data)
{
}


void ContentDirectory1EventSubscriber::event__systemUpdateIDChanged(const Poco::UInt32& data)
{
}


void ContentDirectory1EventSubscriber::event__transferIDsChanged(const std::string& data)
{
}


const std::string ContentDirectory1EventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:ContentDirectory:1");
} // namespace MediaServer1
} // namespace UPnPS

