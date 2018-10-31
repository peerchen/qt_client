//
// LANHostConfigManagementRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  LANHostConfigManagementRemoteObject
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


#ifndef InternetGateway1_LANHostConfigManagementRemoteObject_INCLUDED
#define InternetGateway1_LANHostConfigManagementRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/ILANHostConfigManagement.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API LANHostConfigManagementRemoteObject: public UPnPS::InternetGateway1::ILANHostConfigManagement, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<LANHostConfigManagementRemoteObject> Ptr;

	LANHostConfigManagementRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> pServiceObject);
		/// Creates a LANHostConfigManagementRemoteObject.

	virtual ~LANHostConfigManagementRemoteObject();
		/// Destroys the LANHostConfigManagementRemoteObject.

	virtual void deleteDNSServer(const std::string& newDNSServers);

	virtual void deleteIPRouter(const std::string& newIPRouters);

	virtual void deleteReservedAddress(const std::string& newReservedAddresses);

	virtual void getAddressRange(std::string& newMinAddress, std::string& newMaxAddress);

	virtual void getDHCPRelay(bool& newDHCPRelay);

	virtual void getDHCPServerConfigurable(bool& newDHCPServerConfigurable);

	virtual void getDNSServers(std::string& newDNSServers);

	virtual void getDomainName(std::string& newDomainName);

	virtual void getIPRoutersList(std::string& newIPRouters);

	virtual void getReservedAddresses(std::string& newReservedAddresses);

	virtual void getSubnetMask(std::string& newSubnetMask);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setAddressRange(const std::string& newMinAddress, const std::string& newMaxAddress);

	virtual void setDHCPRelay(bool newDHCPRelay);

	virtual void setDHCPServerConfigurable(bool newDHCPServerConfigurable);

	virtual void setDNSServer(const std::string& newDNSServers);

	virtual void setDomainName(const std::string& newDomainName);

	virtual void setIPRouter(const std::string& newIPRouters);

	virtual void setReservedAddress(const std::string& newReservedAddresses);

	virtual void setSubnetMask(const std::string& newSubnetMask);

private:
	Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> _pServiceObject;
};


inline void LANHostConfigManagementRemoteObject::deleteDNSServer(const std::string& newDNSServers)
{
	_pServiceObject->deleteDNSServer(newDNSServers);
}


inline void LANHostConfigManagementRemoteObject::deleteIPRouter(const std::string& newIPRouters)
{
	_pServiceObject->deleteIPRouter(newIPRouters);
}


inline void LANHostConfigManagementRemoteObject::deleteReservedAddress(const std::string& newReservedAddresses)
{
	_pServiceObject->deleteReservedAddress(newReservedAddresses);
}


inline void LANHostConfigManagementRemoteObject::getAddressRange(std::string& newMinAddress, std::string& newMaxAddress)
{
	_pServiceObject->getAddressRange(newMinAddress, newMaxAddress);
}


inline void LANHostConfigManagementRemoteObject::getDHCPRelay(bool& newDHCPRelay)
{
	_pServiceObject->getDHCPRelay(newDHCPRelay);
}


inline void LANHostConfigManagementRemoteObject::getDHCPServerConfigurable(bool& newDHCPServerConfigurable)
{
	_pServiceObject->getDHCPServerConfigurable(newDHCPServerConfigurable);
}


inline void LANHostConfigManagementRemoteObject::getDNSServers(std::string& newDNSServers)
{
	_pServiceObject->getDNSServers(newDNSServers);
}


inline void LANHostConfigManagementRemoteObject::getDomainName(std::string& newDomainName)
{
	_pServiceObject->getDomainName(newDomainName);
}


inline void LANHostConfigManagementRemoteObject::getIPRoutersList(std::string& newIPRouters)
{
	_pServiceObject->getIPRoutersList(newIPRouters);
}


inline void LANHostConfigManagementRemoteObject::getReservedAddresses(std::string& newReservedAddresses)
{
	_pServiceObject->getReservedAddresses(newReservedAddresses);
}


inline void LANHostConfigManagementRemoteObject::getSubnetMask(std::string& newSubnetMask)
{
	_pServiceObject->getSubnetMask(newSubnetMask);
}


inline const Poco::RemotingNG::Identifiable::TypeId& LANHostConfigManagementRemoteObject::remoting__typeId() const
{
	return ILANHostConfigManagement::remoting__typeId();
}


inline void LANHostConfigManagementRemoteObject::setAddressRange(const std::string& newMinAddress, const std::string& newMaxAddress)
{
	_pServiceObject->setAddressRange(newMinAddress, newMaxAddress);
}


inline void LANHostConfigManagementRemoteObject::setDHCPRelay(bool newDHCPRelay)
{
	_pServiceObject->setDHCPRelay(newDHCPRelay);
}


inline void LANHostConfigManagementRemoteObject::setDHCPServerConfigurable(bool newDHCPServerConfigurable)
{
	_pServiceObject->setDHCPServerConfigurable(newDHCPServerConfigurable);
}


inline void LANHostConfigManagementRemoteObject::setDNSServer(const std::string& newDNSServers)
{
	_pServiceObject->setDNSServer(newDNSServers);
}


inline void LANHostConfigManagementRemoteObject::setDomainName(const std::string& newDomainName)
{
	_pServiceObject->setDomainName(newDomainName);
}


inline void LANHostConfigManagementRemoteObject::setIPRouter(const std::string& newIPRouters)
{
	_pServiceObject->setIPRouter(newIPRouters);
}


inline void LANHostConfigManagementRemoteObject::setReservedAddress(const std::string& newReservedAddresses)
{
	_pServiceObject->setReservedAddress(newReservedAddresses);
}


inline void LANHostConfigManagementRemoteObject::setSubnetMask(const std::string& newSubnetMask)
{
	_pServiceObject->setSubnetMask(newSubnetMask);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_LANHostConfigManagementRemoteObject_INCLUDED

