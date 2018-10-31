//
// WANIPConnectionEventSubscriber.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANIPConnectionEventSubscriber
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


#include "UPnPS/InternetGateway1/WANIPConnectionEventSubscriber.h"
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


class InternetGateway1_API WANIPConnectionEvent__connectionStatusChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANIPConnectionEvent__connectionStatusChangedMethodHandler(WANIPConnectionProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"ConnectionStatus","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->connectionStatusChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANIPConnectionProxy* _pProxy;
};


class InternetGateway1_API WANIPConnectionEvent__externalIPAddressChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANIPConnectionEvent__externalIPAddressChangedMethodHandler(WANIPConnectionProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"ExternalIPAddress","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->externalIPAddressChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANIPConnectionProxy* _pProxy;
};


class InternetGateway1_API WANIPConnectionEvent__portMappingNumberOfEntriesChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANIPConnectionEvent__portMappingNumberOfEntriesChangedMethodHandler(WANIPConnectionProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"PortMappingNumberOfEntries","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		Poco::UInt16 data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->portMappingNumberOfEntriesChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANIPConnectionProxy* _pProxy;
};


class InternetGateway1_API WANIPConnectionEvent__possibleConnectionTypesChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANIPConnectionEvent__possibleConnectionTypesChangedMethodHandler(WANIPConnectionProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"PossibleConnectionTypes","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		std::string data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->possibleConnectionTypesChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANIPConnectionProxy* _pProxy;
};


WANIPConnectionEventSubscriber::WANIPConnectionEventSubscriber(const std::string& uri, WANIPConnectionProxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("ConnectionStatus", new UPnPS::InternetGateway1::WANIPConnectionEvent__connectionStatusChangedMethodHandler(pProxy));
	addMethodHandler("ExternalIPAddress", new UPnPS::InternetGateway1::WANIPConnectionEvent__externalIPAddressChangedMethodHandler(pProxy));
	addMethodHandler("PortMappingNumberOfEntries", new UPnPS::InternetGateway1::WANIPConnectionEvent__portMappingNumberOfEntriesChangedMethodHandler(pProxy));
	addMethodHandler("PossibleConnectionTypes", new UPnPS::InternetGateway1::WANIPConnectionEvent__possibleConnectionTypesChangedMethodHandler(pProxy));
}


WANIPConnectionEventSubscriber::~WANIPConnectionEventSubscriber()
{
}


void WANIPConnectionEventSubscriber::event__connectionStatusChanged(const std::string& data)
{
}


void WANIPConnectionEventSubscriber::event__externalIPAddressChanged(const std::string& data)
{
}


void WANIPConnectionEventSubscriber::event__portMappingNumberOfEntriesChanged(const Poco::UInt16& data)
{
}


void WANIPConnectionEventSubscriber::event__possibleConnectionTypesChanged(const std::string& data)
{
}


const std::string WANIPConnectionEventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:WANIPConnection:1");
} // namespace InternetGateway1
} // namespace UPnPS

