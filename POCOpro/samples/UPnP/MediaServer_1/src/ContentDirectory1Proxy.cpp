//
// ContentDirectory1Proxy.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1Proxy
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


#include "UPnPS/MediaServer1/ContentDirectory1Proxy.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "UPnPS/MediaServer1/ContentDirectory1EventSubscriber.h"


namespace UPnPS {
namespace MediaServer1 {


ContentDirectory1Proxy::ContentDirectory1Proxy(const Poco::RemotingNG::Identifiable::ObjectId& oid):
	UPnPS::MediaServer1::IContentDirectory1(),
	Poco::RemotingNG::Proxy(oid),
	_pEventListener(),
	_pEventSubscriber()
{
}


ContentDirectory1Proxy::~ContentDirectory1Proxy()
{
	if (_pEventListener)
	{
		try
		{
			_pEventListener->unsubscribeFromEvents(_pEventSubscriber);
		}
		catch (...)
		{
		}
		_pEventSubscriber = 0;
		_pEventListener = 0;
	}
}


void ContentDirectory1Proxy::browse(const std::string& objectID, const std::string& browseFlag, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"Browse","ObjectID","BrowseFlag","Filter","StartingIndex","RequestedCount","SortCriteria","Result","NumberReturned","TotalMatches","UpdateID"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], objectID, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], browseFlag, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], filter, remoting__ser);
	Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[4], startingIndex, remoting__ser);
	Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[5], requestedCount, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[6], sortCriteria, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("BrowseResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[7], true, remoting__deser, result);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[8], true, remoting__deser, numberReturned);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[9], true, remoting__deser, totalMatches);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[10], true, remoting__deser, updateID);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::createObject(const std::string& containerID, const std::string& elements, std::string& objectID, std::string& result)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"CreateObject","ContainerID","Elements","ObjectID","Result"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], containerID, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], elements, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("CreateObjectResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, remoting__deser, objectID);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[4], true, remoting__deser, result);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::createReference(const std::string& containerID, const std::string& objectID, std::string& newID)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"CreateReference","ContainerID","ObjectID","NewID"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], containerID, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], objectID, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("CreateReferenceResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, remoting__deser, newID);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::deleteResource(const Poco::URI& resourceURI)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"DeleteResource","ResourceURI"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Poco::URI >::serialize(REMOTING__NAMES[1], resourceURI, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("DeleteResourceResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::destroyObject(const std::string& objectID)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"DestroyObject","ObjectID"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], objectID, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("DestroyObjectResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::exportResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"ExportResource","SourceURI","DestinationURI","TransferID"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Poco::URI >::serialize(REMOTING__NAMES[1], sourceURI, remoting__ser);
	Poco::RemotingNG::TypeSerializer<Poco::URI >::serialize(REMOTING__NAMES[2], destinationURI, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("ExportResourceResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[3], true, remoting__deser, transferID);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::getSearchCapabilities(std::string& searchCaps)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"GetSearchCapabilities","SearchCaps"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("GetSearchCapabilitiesResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, searchCaps);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::getSortCapabilities(std::string& sortCaps)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"GetSortCapabilities","SortCaps"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("GetSortCapabilitiesResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, sortCaps);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::getSystemUpdateID(Poco::UInt32& id)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"GetSystemUpdateID","Id"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("GetSystemUpdateIDResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, id);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::getTransferProgress(Poco::UInt32 transferID, std::string& transferStatus, std::string& transferLength, std::string& transferTotal)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"GetTransferProgress","TransferID","TransferStatus","TransferLength","TransferTotal"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[1], transferID, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("GetTransferProgressResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, transferStatus);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, remoting__deser, transferLength);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[4], true, remoting__deser, transferTotal);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::importResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"ImportResource","SourceURI","DestinationURI","TransferID"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Poco::URI >::serialize(REMOTING__NAMES[1], sourceURI, remoting__ser);
	Poco::RemotingNG::TypeSerializer<Poco::URI >::serialize(REMOTING__NAMES[2], destinationURI, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("ImportResourceResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[3], true, remoting__deser, transferID);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


std::string ContentDirectory1Proxy::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	std::string subscriberURI;
	if ((_pEventListener && !enable) || (!_pEventListener && enable))
	{
		Poco::RemotingNG::EventListener::Ptr pEventListener = pListener.cast<Poco::RemotingNG::EventListener>();
		if (pEventListener)
		{
			if (enable)
			{
				std::string eventURI = remoting__getEventURI().empty() ? remoting__getURI().toString() : remoting__getEventURI().toString();
				_pEventSubscriber = new ContentDirectory1EventSubscriber(eventURI, this);
				subscriberURI = pEventListener->subscribeToEvents(_pEventSubscriber);
				_pEventListener = pEventListener;
			}
			else if (_pEventListener == pEventListener)
			{
				try
				{
					_pEventListener->unsubscribeFromEvents(_pEventSubscriber);
				}
				catch (...)
				{
					_pEventSubscriber = 0;
					_pEventListener = 0;
					throw;
				}
				_pEventSubscriber = 0;
				_pEventListener = 0;
			}
			else throw Poco::RemotingNG::RemotingException("EventListener mismatch");
		}
		else throw Poco::RemotingNG::RemotingException("Listener is not an EventListener");
	}
	return subscriberURI;
}


void ContentDirectory1Proxy::search(const std::string& containerID, const std::string& searchCriteria, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"Search","ContainerID","SearchCriteria","Filter","StartingIndex","RequestedCount","SortCriteria","Result","NumberReturned","TotalMatches","UpdateID"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], containerID, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], searchCriteria, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], filter, remoting__ser);
	Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[4], startingIndex, remoting__ser);
	Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[5], requestedCount, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[6], sortCriteria, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("SearchResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[7], true, remoting__deser, result);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[8], true, remoting__deser, numberReturned);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[9], true, remoting__deser, totalMatches);
	Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[10], true, remoting__deser, updateID);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::stopTransferResource(Poco::UInt32 transferID)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"StopTransferResource","TransferID"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[1], transferID, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("StopTransferResourceResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


void ContentDirectory1Proxy::updateObject(const std::string& objectID, const std::string& currentTagValue, const std::string& newTagValue)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"UpdateObject","ObjectID","CurrentTagValue","NewTagValue"};
	remoting__staticInitEnd(REMOTING__NAMES);
	const std::string& remoting__namespace(DEFAULT_NS);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	remoting__trans.setAttribute(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, remoting__namespace);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], objectID, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], currentTagValue, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], newTagValue, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, DEFAULT_NS);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("UpdateObjectResponse");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
	remoting__trans.endRequest();
}


const std::string ContentDirectory1Proxy::DEFAULT_NS("urn:schemas-upnp-org:service:ContentDirectory:1");
} // namespace MediaServer1
} // namespace UPnPS

