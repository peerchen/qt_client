//
// ContentDirectory1Skeleton.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1Skeleton
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


#include "UPnPS/MediaServer1/ContentDirectory1Skeleton.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ContentDirectory1BrowseMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"Browse","ObjectID","BrowseFlag","Filter","StartingIndex","RequestedCount","SortCriteria","Result","NumberReturned","TotalMatches","UpdateID"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string objectID;
			std::string browseFlag;
			std::string filter;
			Poco::UInt32 startingIndex;
			Poco::UInt32 requestedCount;
			std::string sortCriteria;
			std::string result;
			Poco::UInt32 numberReturned;
			Poco::UInt32 totalMatches;
			Poco::UInt32 updateID;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, objectID);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, browseFlag);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, remoting__deser, filter);
			Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[4], true, remoting__deser, startingIndex);
			Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[5], true, remoting__deser, requestedCount);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[6], true, remoting__deser, sortCriteria);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->browse(objectID, browseFlag, filter, startingIndex, requestedCount, sortCriteria, result, numberReturned, totalMatches, updateID);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("BrowseResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[7], result, remoting__ser);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[8], numberReturned, remoting__ser);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[9], totalMatches, remoting__ser);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[10], updateID, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1CreateObjectMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"CreateObject","ContainerID","Elements","ObjectID","Result"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string containerID;
			std::string elements;
			std::string objectID;
			std::string result;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, containerID);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, elements);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->createObject(containerID, elements, objectID, result);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("CreateObjectResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], objectID, remoting__ser);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[4], result, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1CreateReferenceMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"CreateReference","ContainerID","ObjectID","NewID"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string containerID;
			std::string objectID;
			std::string newID;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, containerID);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, objectID);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->createReference(containerID, objectID, newID);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("CreateReferenceResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], newID, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1DeleteResourceMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"DeleteResource","ResourceURI"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::URI resourceURI;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<Poco::URI >::deserialize(REMOTING__NAMES[1], true, remoting__deser, resourceURI);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->deleteResource(resourceURI);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("DeleteResourceResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1DestroyObjectMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"DestroyObject","ObjectID"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string objectID;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, objectID);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->destroyObject(objectID);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("DestroyObjectResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1ExportResourceMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"ExportResource","SourceURI","DestinationURI","TransferID"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::URI sourceURI;
			Poco::URI destinationURI;
			Poco::UInt32 transferID;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<Poco::URI >::deserialize(REMOTING__NAMES[1], true, remoting__deser, sourceURI);
			Poco::RemotingNG::TypeDeserializer<Poco::URI >::deserialize(REMOTING__NAMES[2], true, remoting__deser, destinationURI);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->exportResource(sourceURI, destinationURI, transferID);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("ExportResourceResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[3], transferID, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1GetSearchCapabilitiesMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetSearchCapabilities","SearchCaps"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string searchCaps;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getSearchCapabilities(searchCaps);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetSearchCapabilitiesResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], searchCaps, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1GetSortCapabilitiesMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetSortCapabilities","SortCaps"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string sortCaps;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getSortCapabilities(sortCaps);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetSortCapabilitiesResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], sortCaps, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1GetSystemUpdateIDMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetSystemUpdateID","Id"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt32 id;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getSystemUpdateID(id);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetSystemUpdateIDResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[1], id, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1GetTransferProgressMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetTransferProgress","TransferID","TransferStatus","TransferLength","TransferTotal"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt32 transferID;
			std::string transferStatus;
			std::string transferLength;
			std::string transferTotal;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, transferID);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getTransferProgress(transferID, transferStatus, transferLength, transferTotal);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetTransferProgressResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], transferStatus, remoting__ser);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], transferLength, remoting__ser);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[4], transferTotal, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1ImportResourceMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"ImportResource","SourceURI","DestinationURI","TransferID"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::URI sourceURI;
			Poco::URI destinationURI;
			Poco::UInt32 transferID;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<Poco::URI >::deserialize(REMOTING__NAMES[1], true, remoting__deser, sourceURI);
			Poco::RemotingNG::TypeDeserializer<Poco::URI >::deserialize(REMOTING__NAMES[2], true, remoting__deser, destinationURI);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->importResource(sourceURI, destinationURI, transferID);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("ImportResourceResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[3], transferID, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1SearchMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"Search","ContainerID","SearchCriteria","Filter","StartingIndex","RequestedCount","SortCriteria","Result","NumberReturned","TotalMatches","UpdateID"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string containerID;
			std::string searchCriteria;
			std::string filter;
			Poco::UInt32 startingIndex;
			Poco::UInt32 requestedCount;
			std::string sortCriteria;
			std::string result;
			Poco::UInt32 numberReturned;
			Poco::UInt32 totalMatches;
			Poco::UInt32 updateID;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, containerID);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, searchCriteria);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, remoting__deser, filter);
			Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[4], true, remoting__deser, startingIndex);
			Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[5], true, remoting__deser, requestedCount);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[6], true, remoting__deser, sortCriteria);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->search(containerID, searchCriteria, filter, startingIndex, requestedCount, sortCriteria, result, numberReturned, totalMatches, updateID);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("SearchResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[7], result, remoting__ser);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[8], numberReturned, remoting__ser);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[9], totalMatches, remoting__ser);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[10], updateID, remoting__ser);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1StopTransferResourceMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"StopTransferResource","TransferID"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt32 transferID;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<Poco::UInt32 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, transferID);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->stopTransferResource(transferID);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("StopTransferResourceResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class MediaServer1_API ContentDirectory1UpdateObjectMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"UpdateObject","ObjectID","CurrentTagValue","NewTagValue"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string objectID;
			std::string currentTagValue;
			std::string newTagValue;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, objectID);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, currentTagValue);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, remoting__deser, newTagValue);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::MediaServer1::ContentDirectory1RemoteObject* remoting__pCastedRO = static_cast<UPnPS::MediaServer1::ContentDirectory1RemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->updateObject(objectID, currentTagValue, newTagValue);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, ContentDirectory1Skeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("UpdateObjectResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
		}
		catch (Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc(e.what());
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				Poco::Exception exc("Unknown Exception");
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


ContentDirectory1Skeleton::ContentDirectory1Skeleton():
	Poco::RemotingNG::Skeleton()

{
	addMethodHandler("Browse", new UPnPS::MediaServer1::ContentDirectory1BrowseMethodHandler);
	addMethodHandler("CreateObject", new UPnPS::MediaServer1::ContentDirectory1CreateObjectMethodHandler);
	addMethodHandler("CreateReference", new UPnPS::MediaServer1::ContentDirectory1CreateReferenceMethodHandler);
	addMethodHandler("DeleteResource", new UPnPS::MediaServer1::ContentDirectory1DeleteResourceMethodHandler);
	addMethodHandler("DestroyObject", new UPnPS::MediaServer1::ContentDirectory1DestroyObjectMethodHandler);
	addMethodHandler("ExportResource", new UPnPS::MediaServer1::ContentDirectory1ExportResourceMethodHandler);
	addMethodHandler("GetSearchCapabilities", new UPnPS::MediaServer1::ContentDirectory1GetSearchCapabilitiesMethodHandler);
	addMethodHandler("GetSortCapabilities", new UPnPS::MediaServer1::ContentDirectory1GetSortCapabilitiesMethodHandler);
	addMethodHandler("GetSystemUpdateID", new UPnPS::MediaServer1::ContentDirectory1GetSystemUpdateIDMethodHandler);
	addMethodHandler("GetTransferProgress", new UPnPS::MediaServer1::ContentDirectory1GetTransferProgressMethodHandler);
	addMethodHandler("ImportResource", new UPnPS::MediaServer1::ContentDirectory1ImportResourceMethodHandler);
	addMethodHandler("Search", new UPnPS::MediaServer1::ContentDirectory1SearchMethodHandler);
	addMethodHandler("StopTransferResource", new UPnPS::MediaServer1::ContentDirectory1StopTransferResourceMethodHandler);
	addMethodHandler("UpdateObject", new UPnPS::MediaServer1::ContentDirectory1UpdateObjectMethodHandler);
}


ContentDirectory1Skeleton::~ContentDirectory1Skeleton()
{
}


const std::string ContentDirectory1Skeleton::DEFAULT_NS("urn:schemas-upnp-org:service:ContentDirectory:1");
} // namespace MediaServer1
} // namespace UPnPS

