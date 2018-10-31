//
// ConnectionManager1EventSubscriber.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1EventSubscriber
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


#include "UPnPS/MediaServer1/ConnectionManager1EventSubscriber.h"
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


class MediaServer1_API ConnectionManager1Event__currentConnectionIDsChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	ConnectionManager1Event__currentConnectionIDsChangedMethodHandler(ConnectionManager1Proxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"CurrentConnectionIDs","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->currentConnectionIDsChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	ConnectionManager1Proxy* _pProxy;
};


class MediaServer1_API ConnectionManager1Event__sinkProtocolInfoChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	ConnectionManager1Event__sinkProtocolInfoChangedMethodHandler(ConnectionManager1Proxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"SinkProtocolInfo","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->sinkProtocolInfoChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	ConnectionManager1Proxy* _pProxy;
};


class MediaServer1_API ConnectionManager1Event__sourceProtocolInfoChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	ConnectionManager1Event__sourceProtocolInfoChangedMethodHandler(ConnectionManager1Proxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"SourceProtocolInfo","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->sourceProtocolInfoChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	ConnectionManager1Proxy* _pProxy;
};


ConnectionManager1EventSubscriber::ConnectionManager1EventSubscriber(const std::string& uri, ConnectionManager1Proxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("CurrentConnectionIDs", new UPnPS::MediaServer1::ConnectionManager1Event__currentConnectionIDsChangedMethodHandler(pProxy));
	addMethodHandler("SinkProtocolInfo", new UPnPS::MediaServer1::ConnectionManager1Event__sinkProtocolInfoChangedMethodHandler(pProxy));
	addMethodHandler("SourceProtocolInfo", new UPnPS::MediaServer1::ConnectionManager1Event__sourceProtocolInfoChangedMethodHandler(pProxy));
}


ConnectionManager1EventSubscriber::~ConnectionManager1EventSubscriber()
{
}


void ConnectionManager1EventSubscriber::event__currentConnectionIDsChanged(const std::string& data)
{
}


void ConnectionManager1EventSubscriber::event__sinkProtocolInfoChanged(const std::string& data)
{
}


void ConnectionManager1EventSubscriber::event__sourceProtocolInfoChanged(const std::string& data)
{
}


const std::string ConnectionManager1EventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:ConnectionManager:1");
} // namespace MediaServer1
} // namespace UPnPS

