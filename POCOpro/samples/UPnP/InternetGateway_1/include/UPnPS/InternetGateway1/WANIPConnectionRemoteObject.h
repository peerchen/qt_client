//
// WANIPConnectionRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANIPConnectionRemoteObject
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


#ifndef InternetGateway1_WANIPConnectionRemoteObject_INCLUDED
#define InternetGateway1_WANIPConnectionRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/IWANIPConnection.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANIPConnectionRemoteObject: public UPnPS::InternetGateway1::IWANIPConnection, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<WANIPConnectionRemoteObject> Ptr;

	WANIPConnectionRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANIPConnection> pServiceObject);
		/// Creates a WANIPConnectionRemoteObject.

	virtual ~WANIPConnectionRemoteObject();
		/// Destroys the WANIPConnectionRemoteObject.

	virtual void addPortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16 newInternalPort, const std::string& newInternalClient, bool newEnabled, const std::string& newPortMappingDescription, Poco::UInt32 newLeaseDuration);

	virtual void deletePortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol);

	virtual void forceTermination();

	virtual void getAutoDisconnectTime(Poco::UInt32& newAutoDisconnectTime);

	virtual void getConnectionTypeInfo(std::string& newConnectionType, std::string& newPossibleConnectionTypes);

	virtual void getExternalIPAddress(std::string& newExternalIPAddress);

	virtual void getGenericPortMappingEntry(Poco::UInt16 newPortMappingIndex, std::string& newRemoteHost, Poco::UInt16& newExternalPort, std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration);

	virtual void getIdleDisconnectTime(Poco::UInt32& newIdleDisconnectTime);

	virtual void getNATRSIPStatus(bool& newRSIPAvailable, bool& newNATEnabled);

	virtual void getSpecificPortMappingEntry(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration);

	virtual void getStatusInfo(std::string& newConnectionStatus, std::string& newLastConnectionError, Poco::UInt32& newUptime);

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
	Poco::SharedPtr<UPnPS::InternetGateway1::WANIPConnection> _pServiceObject;
};


inline void WANIPConnectionRemoteObject::addPortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16 newInternalPort, const std::string& newInternalClient, bool newEnabled, const std::string& newPortMappingDescription, Poco::UInt32 newLeaseDuration)
{
	_pServiceObject->addPortMapping(newRemoteHost, newExternalPort, newProtocol, newInternalPort, newInternalClient, newEnabled, newPortMappingDescription, newLeaseDuration);
}


inline void WANIPConnectionRemoteObject::deletePortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol)
{
	_pServiceObject->deletePortMapping(newRemoteHost, newExternalPort, newProtocol);
}


inline void WANIPConnectionRemoteObject::forceTermination()
{
	_pServiceObject->forceTermination();
}


inline void WANIPConnectionRemoteObject::getAutoDisconnectTime(Poco::UInt32& newAutoDisconnectTime)
{
	_pServiceObject->getAutoDisconnectTime(newAutoDisconnectTime);
}


inline void WANIPConnectionRemoteObject::getConnectionTypeInfo(std::string& newConnectionType, std::string& newPossibleConnectionTypes)
{
	_pServiceObject->getConnectionTypeInfo(newConnectionType, newPossibleConnectionTypes);
}


inline void WANIPConnectionRemoteObject::getExternalIPAddress(std::string& newExternalIPAddress)
{
	_pServiceObject->getExternalIPAddress(newExternalIPAddress);
}


inline void WANIPConnectionRemoteObject::getGenericPortMappingEntry(Poco::UInt16 newPortMappingIndex, std::string& newRemoteHost, Poco::UInt16& newExternalPort, std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration)
{
	_pServiceObject->getGenericPortMappingEntry(newPortMappingIndex, newRemoteHost, newExternalPort, newProtocol, newInternalPort, newInternalClient, newEnabled, newPortMappingDescription, newLeaseDuration);
}


inline void WANIPConnectionRemoteObject::getIdleDisconnectTime(Poco::UInt32& newIdleDisconnectTime)
{
	_pServiceObject->getIdleDisconnectTime(newIdleDisconnectTime);
}


inline void WANIPConnectionRemoteObject::getNATRSIPStatus(bool& newRSIPAvailable, bool& newNATEnabled)
{
	_pServiceObject->getNATRSIPStatus(newRSIPAvailable, newNATEnabled);
}


inline void WANIPConnectionRemoteObject::getSpecificPortMappingEntry(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration)
{
	_pServiceObject->getSpecificPortMappingEntry(newRemoteHost, newExternalPort, newProtocol, newInternalPort, newInternalClient, newEnabled, newPortMappingDescription, newLeaseDuration);
}


inline void WANIPConnectionRemoteObject::getStatusInfo(std::string& newConnectionStatus, std::string& newLastConnectionError, Poco::UInt32& newUptime)
{
	_pServiceObject->getStatusInfo(newConnectionStatus, newLastConnectionError, newUptime);
}


inline void WANIPConnectionRemoteObject::getWarnDisconnectDelay(Poco::UInt32& newWarnDisconnectDelay)
{
	_pServiceObject->getWarnDisconnectDelay(newWarnDisconnectDelay);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WANIPConnectionRemoteObject::remoting__typeId() const
{
	return IWANIPConnection::remoting__typeId();
}


inline void WANIPConnectionRemoteObject::requestConnection()
{
	_pServiceObject->requestConnection();
}


inline void WANIPConnectionRemoteObject::requestTermination()
{
	_pServiceObject->requestTermination();
}


inline void WANIPConnectionRemoteObject::setAutoDisconnectTime(Poco::UInt32 newAutoDisconnectTime)
{
	_pServiceObject->setAutoDisconnectTime(newAutoDisconnectTime);
}


inline void WANIPConnectionRemoteObject::setConnectionType(const std::string& newConnectionType)
{
	_pServiceObject->setConnectionType(newConnectionType);
}


inline void WANIPConnectionRemoteObject::setIdleDisconnectTime(Poco::UInt32 newIdleDisconnectTime)
{
	_pServiceObject->setIdleDisconnectTime(newIdleDisconnectTime);
}


inline void WANIPConnectionRemoteObject::setWarnDisconnectDelay(Poco::UInt32 newWarnDisconnectDelay)
{
	_pServiceObject->setWarnDisconnectDelay(newWarnDisconnectDelay);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANIPConnectionRemoteObject_INCLUDED

