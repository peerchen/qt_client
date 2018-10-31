//
// WANPPPConnectionRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPPPConnectionRemoteObject
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


#ifndef InternetGateway1_WANPPPConnectionRemoteObject_INCLUDED
#define InternetGateway1_WANPPPConnectionRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/IWANPPPConnection.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANPPPConnectionRemoteObject: public UPnPS::InternetGateway1::IWANPPPConnection, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<WANPPPConnectionRemoteObject> Ptr;

	WANPPPConnectionRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> pServiceObject);
		/// Creates a WANPPPConnectionRemoteObject.

	virtual ~WANPPPConnectionRemoteObject();
		/// Destroys the WANPPPConnectionRemoteObject.

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

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void requestConnection();

	virtual void requestTermination();

	virtual void setAutoDisconnectTime(Poco::UInt32 newAutoDisconnectTime);

	virtual void setConnectionType(const std::string& newConnectionType);

	virtual void setIdleDisconnectTime(Poco::UInt32 newIdleDisconnectTime);

	virtual void setWarnDisconnectDelay(Poco::UInt32 newWarnDisconnectDelay);

protected:
	void event__connectionStatusChanged(const std::string& data);

	void event__externalIPAddressChanged(const std::string& data);

	void event__portMappingNumberOfEntriesChanged(const Poco::UInt16& data);

	void event__possibleConnectionTypesChanged(const std::string& data);

private:
	Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> _pServiceObject;
};


inline void WANPPPConnectionRemoteObject::addPortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16 newInternalPort, const std::string& newInternalClient, bool newEnabled, const std::string& newPortMappingDescription, Poco::UInt32 newLeaseDuration)
{
	_pServiceObject->addPortMapping(newRemoteHost, newExternalPort, newProtocol, newInternalPort, newInternalClient, newEnabled, newPortMappingDescription, newLeaseDuration);
}


inline void WANPPPConnectionRemoteObject::configureConnection(const std::string& newUserName, const std::string& newPassword)
{
	_pServiceObject->configureConnection(newUserName, newPassword);
}


inline void WANPPPConnectionRemoteObject::deletePortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol)
{
	_pServiceObject->deletePortMapping(newRemoteHost, newExternalPort, newProtocol);
}


inline void WANPPPConnectionRemoteObject::forceTermination()
{
	_pServiceObject->forceTermination();
}


inline void WANPPPConnectionRemoteObject::getAutoDisconnectTime(Poco::UInt32& newAutoDisconnectTime)
{
	_pServiceObject->getAutoDisconnectTime(newAutoDisconnectTime);
}


inline void WANPPPConnectionRemoteObject::getConnectionTypeInfo(std::string& newConnectionType, std::string& newPossibleConnectionTypes)
{
	_pServiceObject->getConnectionTypeInfo(newConnectionType, newPossibleConnectionTypes);
}


inline void WANPPPConnectionRemoteObject::getExternalIPAddress(std::string& newExternalIPAddress)
{
	_pServiceObject->getExternalIPAddress(newExternalIPAddress);
}


inline void WANPPPConnectionRemoteObject::getGenericPortMappingEntry(Poco::UInt16 newPortMappingIndex, std::string& newRemoteHost, Poco::UInt16& newExternalPort, std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration)
{
	_pServiceObject->getGenericPortMappingEntry(newPortMappingIndex, newRemoteHost, newExternalPort, newProtocol, newInternalPort, newInternalClient, newEnabled, newPortMappingDescription, newLeaseDuration);
}


inline void WANPPPConnectionRemoteObject::getIdleDisconnectTime(Poco::UInt32& newIdleDisconnectTime)
{
	_pServiceObject->getIdleDisconnectTime(newIdleDisconnectTime);
}


inline void WANPPPConnectionRemoteObject::getLinkLayerMaxBitRates(Poco::UInt32& newUpstreamMaxBitRate, Poco::UInt32& newDownstreamMaxBitRate)
{
	_pServiceObject->getLinkLayerMaxBitRates(newUpstreamMaxBitRate, newDownstreamMaxBitRate);
}


inline void WANPPPConnectionRemoteObject::getNATRSIPStatus(bool& newRSIPAvailable, bool& newNATEnabled)
{
	_pServiceObject->getNATRSIPStatus(newRSIPAvailable, newNATEnabled);
}


inline void WANPPPConnectionRemoteObject::getPPPAuthenticationProtocol(std::string& newPPPAuthenticationProtocol)
{
	_pServiceObject->getPPPAuthenticationProtocol(newPPPAuthenticationProtocol);
}


inline void WANPPPConnectionRemoteObject::getPPPCompressionProtocol(std::string& newPPPCompressionProtocol)
{
	_pServiceObject->getPPPCompressionProtocol(newPPPCompressionProtocol);
}


inline void WANPPPConnectionRemoteObject::getPPPEncryptionProtocol(std::string& newPPPEncryptionProtocol)
{
	_pServiceObject->getPPPEncryptionProtocol(newPPPEncryptionProtocol);
}


inline void WANPPPConnectionRemoteObject::getPassword(std::string& newPassword)
{
	_pServiceObject->getPassword(newPassword);
}


inline void WANPPPConnectionRemoteObject::getSpecificPortMappingEntry(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration)
{
	_pServiceObject->getSpecificPortMappingEntry(newRemoteHost, newExternalPort, newProtocol, newInternalPort, newInternalClient, newEnabled, newPortMappingDescription, newLeaseDuration);
}


inline void WANPPPConnectionRemoteObject::getStatusInfo(std::string& newConnectionStatus, std::string& newLastConnectionError, Poco::UInt32& newUptime)
{
	_pServiceObject->getStatusInfo(newConnectionStatus, newLastConnectionError, newUptime);
}


inline void WANPPPConnectionRemoteObject::getUserName(std::string& newUserName)
{
	_pServiceObject->getUserName(newUserName);
}


inline void WANPPPConnectionRemoteObject::getWarnDisconnectDelay(Poco::UInt32& newWarnDisconnectDelay)
{
	_pServiceObject->getWarnDisconnectDelay(newWarnDisconnectDelay);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WANPPPConnectionRemoteObject::remoting__typeId() const
{
	return IWANPPPConnection::remoting__typeId();
}


inline void WANPPPConnectionRemoteObject::requestConnection()
{
	_pServiceObject->requestConnection();
}


inline void WANPPPConnectionRemoteObject::requestTermination()
{
	_pServiceObject->requestTermination();
}


inline void WANPPPConnectionRemoteObject::setAutoDisconnectTime(Poco::UInt32 newAutoDisconnectTime)
{
	_pServiceObject->setAutoDisconnectTime(newAutoDisconnectTime);
}


inline void WANPPPConnectionRemoteObject::setConnectionType(const std::string& newConnectionType)
{
	_pServiceObject->setConnectionType(newConnectionType);
}


inline void WANPPPConnectionRemoteObject::setIdleDisconnectTime(Poco::UInt32 newIdleDisconnectTime)
{
	_pServiceObject->setIdleDisconnectTime(newIdleDisconnectTime);
}


inline void WANPPPConnectionRemoteObject::setWarnDisconnectDelay(Poco::UInt32 newWarnDisconnectDelay)
{
	_pServiceObject->setWarnDisconnectDelay(newWarnDisconnectDelay);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANPPPConnectionRemoteObject_INCLUDED

