//
// WANCableLinkConfigEventSubscriber.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigEventSubscriber
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


#include "UPnPS/InternetGateway1/WANCableLinkConfigEventSubscriber.h"
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


class InternetGateway1_API WANCableLinkConfigEvent__bPIEncryptionEnabledChangedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	WANCableLinkConfigEvent__bPIEncryptionEnabledChangedMethodHandler(WANCableLinkConfigProxy* pProxy)
	{
		_pProxy = pProxy;
	}

	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"BPIEncryptionEnabled","data"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool data;
		remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, remoting__deser, data);
		remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
		try
		{
			_pProxy->bPIEncryptionEnabledChanged(0, data);
		}
		catch (...)
		{
		}
	}

private:
	WANCableLinkConfigProxy* _pProxy;
};


WANCableLinkConfigEventSubscriber::WANCableLinkConfigEventSubscriber(const std::string& uri, WANCableLinkConfigProxy* pProxy):
	Poco::RemotingNG::EventSubscriber(uri)

{
	addMethodHandler("BPIEncryptionEnabled", new UPnPS::InternetGateway1::WANCableLinkConfigEvent__bPIEncryptionEnabledChangedMethodHandler(pProxy));
}


WANCableLinkConfigEventSubscriber::~WANCableLinkConfigEventSubscriber()
{
}


void WANCableLinkConfigEventSubscriber::event__bPIEncryptionEnabledChanged(const bool& data)
{
}


const std::string WANCableLinkConfigEventSubscriber::DEFAULT_NS("urn:schemas-upnp-org:service:WANCableLinkConfig:1");
} // namespace InternetGateway1
} // namespace UPnPS

