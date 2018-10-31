//
// IWANIPConnection.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  IWANIPConnection
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


#ifndef InternetGateway1_IWANIPConnection_INCLUDED
#define InternetGateway1_IWANIPConnection_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANIPConnection.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API IWANIPConnection: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IWANIPConnection> Ptr;

	IWANIPConnection();
		/// Creates a IWANIPConnection.

	virtual ~IWANIPConnection();
		/// Destroys the IWANIPConnection.

	virtual void addPortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16 newInternalPort, const std::string& newInternalClient, bool newEnabled, const std::string& newPortMappingDescription, Poco::UInt32 newLeaseDuration) = 0;

	virtual void deletePortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol) = 0;

	virtual void forceTermination() = 0;

	virtual void getAutoDisconnectTime(Poco::UInt32& newAutoDisconnectTime) = 0;

	virtual void getConnectionTypeInfo(std::string& newConnectionType, std::string& newPossibleConnectionTypes) = 0;

	virtual void getExternalIPAddress(std::string& newExternalIPAddress) = 0;

	virtual void getGenericPortMappingEntry(Poco::UInt16 newPortMappingIndex, std::string& newRemoteHost, Poco::UInt16& newExternalPort, std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration) = 0;

	virtual void getIdleDisconnectTime(Poco::UInt32& newIdleDisconnectTime) = 0;

	virtual void getNATRSIPStatus(bool& newRSIPAvailable, bool& newNATEnabled) = 0;

	virtual void getSpecificPortMappingEntry(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration) = 0;

	virtual void getStatusInfo(std::string& newConnectionStatus, std::string& newLastConnectionError, Poco::UInt32& newUptime) = 0;

	virtual void getWarnDisconnectDelay(Poco::UInt32& newWarnDisconnectDelay) = 0;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void requestConnection() = 0;

	virtual void requestTermination() = 0;

	virtual void setAutoDisconnectTime(Poco::UInt32 newAutoDisconnectTime) = 0;

	virtual void setConnectionType(const std::string& newConnectionType) = 0;

	virtual void setIdleDisconnectTime(Poco::UInt32 newIdleDisconnectTime) = 0;

	virtual void setWarnDisconnectDelay(Poco::UInt32 newWarnDisconnectDelay) = 0;

	Poco::BasicEvent < const std::string > connectionStatusChanged;
	Poco::BasicEvent < const std::string > externalIPAddressChanged;
	Poco::BasicEvent < const Poco::UInt16 > portMappingNumberOfEntriesChanged;
	Poco::BasicEvent < const std::string > possibleConnectionTypesChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_IWANIPConnection_INCLUDED

