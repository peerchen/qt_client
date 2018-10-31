//
// WANPPPConnectionEventSubscriber.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPPPConnectionEventSubscriber
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


#include "UPnPS/InternetGateway1/WANPPPConnectionEventSubscriber.h"
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


class InternetGateway1_API WANPPPConnectionEvent__connectionStatusChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANPPPConnectionEvent__connectionStatusChangedMethodHandler(WANPPPConnectionProxy* pProxy)
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
	WANPPPConnectionProxy* _pProxy;
};


class InternetGateway1_API WANPPPConnectionEvent__externalIPAddressChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANPPPConnectionEvent__externalIPAddressChangedMethodHandler(WANPPPConnectionProxy* pProxy)
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
	WANPPPConnectionProxy* _pProxy;
};


class InternetGateway1_API WANPPPConnectionEvent__portMappingNumberOfEntriesChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANPPPConnectionEvent__portMappingNumberOfEntriesChangedMethodHandler(WANPPPConnectionProxy* pProxy)
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
	WANPPPConnectionProxy* _pProxy;
};


class InternetGateway1_API WANPPPConnectionEvent__possibleConnectionTypesChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANPPPConnectionEvent__possibleConnectionTypesChangedMethodHandler(WANPPPConnectionProxy* pProxy)
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
	WANPPPConnectionProxy* _pProxy;
};


WANPPPConnectionEventSubscriber::WANPPPConnectionEventSubscriber(const std::string& uri, WANPPPConnectionProxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("ConnectionStatus", new UPnPS::InternetGateway1::WANPPPConnectionEvent__connectionStatusChangedMethodHandler(pProxy));
	addMethodHandler("ExternalIPAddress", new UPnPS::InternetGateway1::WANPPPConnectionEvent__externalIPAddressChangedMethodHandler(pProxy));
	addMethodHandler("PortMappingNumberOfEntries", new UPnPS::InternetGateway1::WANPPPConnectionEvent__portMappingNumberOfEntriesChangedMethodHandler(pProxy));
	addMethodHandler("PossibleConnectionTypes", new UPnPS::InternetGateway1::WANPPPConnectionEvent__possibleConnectionTypesChangedMethodHandler(pProxy));
}


WANPPPConnectionEventSubscriber::~WANPPPConnectionEventSubscriber()
{
}


void WANPPPConnectionEventSubscriber::event__connectionStatusChanged(const std::string& data)
{
}


void WANPPPConnectionEventSubscriber::event__externalIPAddressChanged(const std::string& data)
{
}


void WANPPPConnectionEventSubscriber::event__portMappingNumberOfEntriesChanged(const Poco::UInt16& data)
{
}


void WANPPPConnectionEventSubscriber::event__possibleConnectionTypesChanged(const std::string& data)
{
}


const std::string WANPPPConnectionEventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:WANPPPConnection:1");
} // namespace InternetGateway1
} // namespace UPnPS

