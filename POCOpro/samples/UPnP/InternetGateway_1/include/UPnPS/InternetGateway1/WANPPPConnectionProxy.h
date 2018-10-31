//
// WANPPPConnectionProxy.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPPPConnectionProxy
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


#ifndef InternetGateway1_WANPPPConnectionProxy_INCLUDED
#define InternetGateway1_WANPPPConnectionProxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/InternetGateway1/IWANPPPConnection.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANPPPConnectionProxy: public UPnPS::InternetGateway1::IWANPPPConnection, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<WANPPPConnectionProxy> Ptr;

	WANPPPConnectionProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a WANPPPConnectionProxy.

	virtual ~WANPPPConnectionProxy();
		/// Destroys the WANPPPConnectionProxy.

	virtual void addPortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16 newInternalPort, const std::string& newInternalClient, bool newEnabled, const std::string& newPortMappingDescription, Poco::UInt32 newLeaseDuration);

	virtual void configureConnection(const std::string& newUserName, const std::string& newPassword);

	virtual void deletePortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol);

	virtual void forceTermination();

	virtual void getAutoDisconnectTime(Poco::UInt32& newAutoDisconnectTime);

	virtual void getConnectionTypeInfo(std::string& newConnectionType, std::string& newPossibleConnectionTypes);

	virtual void getExternalIPAddress(std::string& newExternalIPAddress);

	virtual void getGenericPortMappingEntry(Poco::UInt16 newPortMappingIndex, std::string& newRemoteHost, Poco::UInt16& newExternalPort, std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration);

	virtual void getIdleDisconnectTime(Poco::UInt32& newIdleDisconnectTime);

	virtual void getLinkLayerMaxBitRates(Poco::UInt32& newUpstreamMaxBitRate, Poco::UInt32& newDownstreamMaxBitRate);

	virtual void getNATRSIPStatus(bool& newRSIPAvailable, bool& newNATEnabled);

	virtual void getPPPAuthenticationProtocol(std::string& newPPPAuthenticationProtocol);

	virtual void getPPPCompressionProtocol(std::string& newPPPCompressionProtocol);

	virtual void getPPPEncryptionProtocol(std::string& newPPPEncryptionProtocol);

	virtual void getPassword(std::string& newPassword);

	virtual void getSpecificPortMappingEntry(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration);

	virtual void getStatusInfo(std::string& newConnectionStatus, std::string& newLastConnectionError, Poco::UInt32& newUptime);

	virtual void getUserName(std::string& newUserName);

	virtual void getWarnDisconnectDelay(Poco::UInt32& newWarnDisconnectDelay);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void requestConnection();

	virtual void requestTermination();

	virtual void setAutoDisconnectTime(Poco::UInt32 newAutoDisconnectTime);

	virtual void setConnectionType(const std::string& newConnectionType);

	virtual void setIdleDisconnectTime(Poco::UInt32 newIdleDisconnectTime);

	virtual void setWarnDisconnectDelay(Poco::UInt32 newWarnDisconnectDelay);

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANPPPConnectionProxy::remoting__typeId() const
{
	return IWANPPPConnection::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANPPPConnectionProxy_INCLUDED

