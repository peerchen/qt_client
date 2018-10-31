//
// WANCommonInterfaceConfigSkeleton.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigSkeleton
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


#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigSkeleton.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCommonInterfaceConfigGetActiveConnectionMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetActiveConnection","NewActiveConnectionIndex","NewActiveConnDeviceContainer","NewActiveConnectionServiceID"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt16 newActiveConnectionIndex;
			std::string newActiveConnDeviceContainer;
			std::string newActiveConnectionServiceID;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[1], true, remoting__deser, newActiveConnectionIndex);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getActiveConnection(newActiveConnectionIndex, newActiveConnDeviceContainer, newActiveConnectionServiceID);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetActiveConnectionResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], newActiveConnDeviceContainer, remoting__ser);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], newActiveConnectionServiceID, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigGetCommonLinkPropertiesMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetCommonLinkProperties","NewWANAccessType","NewLayer1UpstreamMaxBitRate","NewLayer1DownstreamMaxBitRate","NewPhysicalLinkStatus"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string newWANAccessType;
			Poco::UInt32 newLayer1UpstreamMaxBitRate;
			Poco::UInt32 newLayer1DownstreamMaxBitRate;
			std::string newPhysicalLinkStatus;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getCommonLinkProperties(newWANAccessType, newLayer1UpstreamMaxBitRate, newLayer1DownstreamMaxBitRate, newPhysicalLinkStatus);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetCommonLinkPropertiesResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], newWANAccessType, remoting__ser);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[2], newLayer1UpstreamMaxBitRate, remoting__ser);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[3], newLayer1DownstreamMaxBitRate, remoting__ser);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[4], newPhysicalLinkStatus, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigGetEnabledForInternetMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetEnabledForInternet","NewEnabledForInternet"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			bool newEnabledForInternet;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getEnabledForInternet(newEnabledForInternet);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetEnabledForInternetResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<bool >::serialize(REMOTING__NAMES[1], newEnabledForInternet, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigGetMaximumActiveConnectionsMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetMaximumActiveConnections","NewMaximumActiveConnections"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt16 newMaximumActiveConnections;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getMaximumActiveConnections(newMaximumActiveConnections);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetMaximumActiveConnectionsResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[1], newMaximumActiveConnections, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigGetTotalBytesReceivedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetTotalBytesReceived","NewTotalBytesReceived"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt32 newTotalBytesReceived;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getTotalBytesReceived(newTotalBytesReceived);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetTotalBytesReceivedResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[1], newTotalBytesReceived, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigGetTotalBytesSentMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetTotalBytesSent","NewTotalBytesSent"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt32 newTotalBytesSent;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getTotalBytesSent(newTotalBytesSent);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetTotalBytesSentResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[1], newTotalBytesSent, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigGetTotalPacketsReceivedMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetTotalPacketsReceived","NewTotalPacketsReceived"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt32 newTotalPacketsReceived;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getTotalPacketsReceived(newTotalPacketsReceived);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetTotalPacketsReceivedResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[1], newTotalPacketsReceived, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigGetTotalPacketsSentMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetTotalPacketsSent","NewTotalPacketsSent"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			Poco::UInt32 newTotalPacketsSent;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getTotalPacketsSent(newTotalPacketsSent);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetTotalPacketsSentResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<Poco::UInt32 >::serialize(REMOTING__NAMES[1], newTotalPacketsSent, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigGetWANAccessProviderMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"GetWANAccessProvider","NewWANAccessProvider"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			std::string newWANAccessProvider;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->getWANAccessProvider(newWANAccessProvider);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("GetWANAccessProviderResponse");
			remoting__staticInitEnd(REMOTING__REPLY_NAME);
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], newWANAccessProvider, remoting__ser);
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


class InternetGateway1_API WANCommonInterfaceConfigSetEnabledForInternetMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"SetEnabledForInternet","NewEnabledForInternet"};
		remoting__staticInitEnd(REMOTING__NAMES);
		bool remoting__requestSucceeded = false;
		try
		{
			bool newEnabledForInternet;
			remoting__deser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<bool >::deserialize(REMOTING__NAMES[1], true, remoting__deser, newEnabledForInternet);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			remoting__deser.popProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE);
			UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject* remoting__pCastedRO = static_cast<UPnPS::InternetGateway1::WANCommonInterfaceConfigRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setEnabledForInternet(newEnabledForInternet);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.pushProperty(Poco::RemotingNG::SerializerBase::PROP_NAMESPACE, WANCommonInterfaceConfigSkeleton::DEFAULT_NS);
			remoting__staticInitBegin(REMOTING__REPLY_NAME);
			static const std::string REMOTING__REPLY_NAME("SetEnabledForInternetResponse");
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


WANCommonInterfaceConfigSkeleton::WANCommonInterfaceConfigSkeleton():
	Poco::RemotingNG::Skeleton()

{
	addMethodHandler("GetActiveConnection", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetActiveConnectionMethodHandler);
	addMethodHandler("GetCommonLinkProperties", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetCommonLinkPropertiesMethodHandler);
	addMethodHandler("GetEnabledForInternet", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetEnabledForInternetMethodHandler);
	addMethodHandler("GetMaximumActiveConnections", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetMaximumActiveConnectionsMethodHandler);
	addMethodHandler("GetTotalBytesReceived", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetTotalBytesReceivedMethodHandler);
	addMethodHandler("GetTotalBytesSent", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetTotalBytesSentMethodHandler);
	addMethodHandler("GetTotalPacketsReceived", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetTotalPacketsReceivedMethodHandler);
	addMethodHandler("GetTotalPacketsSent", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetTotalPacketsSentMethodHandler);
	addMethodHandler("GetWANAccessProvider", new UPnPS::InternetGateway1::WANCommonInterfaceConfigGetWANAccessProviderMethodHandler);
	addMethodHandler("SetEnabledForInternet", new UPnPS::InternetGateway1::WANCommonInterfaceConfigSetEnabledForInternetMethodHandler);
}


WANCommonInterfaceConfigSkeleton::~WANCommonInterfaceConfigSkeleton()
{
}


const std::string WANCommonInterfaceConfigSkeleton::DEFAULT_NS("urn:schemas-upnp-org:service:WANCommonInterfaceConfig:1");
} // namespace InternetGateway1
} // namespace UPnPS

