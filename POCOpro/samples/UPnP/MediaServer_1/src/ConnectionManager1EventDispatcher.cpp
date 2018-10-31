//
// ConnectionManager1EventDispatcher.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1EventDispatcher
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


#include "UPnPS/MediaServer1/ConnectionManager1EventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"


namespace UPnPS {
namespace MediaServer1 {


ConnectionManager1EventDispatcher::ConnectionManager1EventDispatcher(ConnectionManager1RemoteObject* pRemoteObject, const std::string& protocol):
	Poco::RemotingNG::EventDispatcher(protocol),
	_pRemoteObject(pRemoteObject)
{
	_pRemoteObject->currentConnectionIDsChanged += Poco::delegate(this, &ConnectionManager1EventDispatcher::event__currentConnectionIDsChanged);
	_pRemoteObject->sinkProtocolInfoChanged += Poco::delegate(this, &ConnectionManager1EventDispatcher::event__sinkProtocolInfoChanged);
	_pRemoteObject->sourceProtocolInfoChanged += Poco::delegate(this, &ConnectionManager1EventDispatcher::event__sourceProtocolInfoChanged);
}


ConnectionManager1EventDispatcher::~ConnectionManager1EventDispatcher()
{
	try
	{
		_pRemoteObject->currentConnectionIDsChanged -= Poco::delegate(this, &ConnectionManager1EventDispatcher::event__currentConnectionIDsChanged);
		_pRemoteObject->sinkProtocolInfoChanged -= Poco::delegate(this, &ConnectionManager1EventDispatcher::event__sinkProtocolInfoChanged);
		_pRemoteObject->sourceProtocolInfoChanged -= Poco::delegate(this, &ConnectionManager1EventDispatcher::event__sourceProtocolInfoChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void ConnectionManager1EventDispatcher::event__currentConnectionIDsChanged(const void* pSender, const std::string& data)
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
					event__currentConnectionIDsChangedImpl(it->first, data);
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void ConnectionManager1EventDispatcher::event__sinkProtocolInfoChanged(const void* pSender, const std::string& data)
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
					event__sinkProtocolInfoChangedImpl(it->first, data);
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void ConnectionManager1EventDispatcher::event__sourceProtocolInfoChanged(const void* pSender, const std::string& data)
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
					event__sourceProtocolInfoChangedImpl(it->first, data);
				}
				catch (Poco::Exception&)
				{
				}
				++it;
			}
		}
	}
}


void ConnectionManager1EventDispatcher::event__currentConnectionIDsChangedImpl(const std::string& subscriberURI, const std::string& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"CurrentConnectionIDs","subscriberURI","data"};
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


void ConnectionManager1EventDispatcher::event__sinkProtocolInfoChangedImpl(const std::string& subscriberURI, const std::string& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"SinkProtocolInfo","subscriberURI","data"};
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


void ConnectionManager1EventDispatcher::event__sourceProtocolInfoChangedImpl(const std::string& subscriberURI, const std::string& data)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"SourceProtocolInfo","subscriberURI","data"};
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


const std::string ConnectionManager1EventDispatcher::DEFAULT_NS("urn:schemas-upnp-org:service:ConnectionManager:1");
} // namespace MediaServer1
} // namespace UPnPS

