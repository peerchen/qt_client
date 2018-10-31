//
// WANEthernetLinkConfigEventDispatcher.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANEthernetLinkConfigEventDispatcher
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


#include "UPnPS/InternetGateway1/WANEthernetLinkConfigEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace UPnPS {
namespace InternetGateway1 {


WANEthernetLinkConfigEventDispatcher::WANEthernetLinkConfigEventDispatcher(WANEthernetLinkConfigRemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->ethernetLinkStatusChanged += Poco::delegate(this, &WANEthernetLinkConfigEventDispatcher::event__ethernetLinkStatusChanged);
}


WANEthernetLinkConfigEventDispatcher::~WANEthernetLinkConfigEventDispatcher()
{
	try
	{
		_pRemoteObject->ethernetLinkStatusChanged -= Poco::delegate(this, &WANEthernetLinkConfigEventDispatcher::event__ethernetLinkStatusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void WANEthernetLinkConfigEventDispatcher::event__ethernetLinkStatusChanged(const void* pSender, const std::string& data)
{
	if (pSender)
	{
		Poco::Clock now;
		Poco::FastMutex::ScopedLock lock(_mutex);
		SubscriberMap::iterator it = _subscribers.begin();
		while (it != _subscribers.end())
		{
			if (it->second->expireTime != 0 && it->second->expireTime < now)
			{
				SubscriberMap::iterator itDel(it++);
				_subscribers.erase(itDel);
			}
			else
			{
				try
				{
					event__ethernetLinkStatusChangedImpl(it->first, data);
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void WANEthernetLinkConfigEventDispatcher::event__ethernetLinkStatusChangedImpl(const std::string& subscriberURI, const std::string& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"EthernetLinkStatus","subscriberURI","data"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = transportForSubscriber(subscriberURI);
	Poco::ScopedLock<Poco::RemotingNG::Transport> remoting__lock(remoting__trans);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], data, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.sendMessage(_pRemoteObject->remoting__objectId(), _pRemoteObject->remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);
}


const std::string WANEthernetLinkConfigEventDispatcher::DEFAULT_NS("urn:schemas-upnp-org:service:WANEthernetLinkConfig:1");
} // namespace InternetGateway1
} // namespace UPnPS

