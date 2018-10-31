//
// ILANHostConfigManagement.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  ILANHostConfigManagement
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


#ifndef InternetGateway1_ILANHostConfigManagement_INCLUDED
#define InternetGateway1_ILANHostConfigManagement_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/LANHostConfigManagement.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API ILANHostConfigManagement: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<ILANHostConfigManagement> Ptr;

	ILANHostConfigManagement();
		/// Creates a ILANHostConfigManagement.

	virtual ~ILANHostConfigManagement();
		/// Destroys the ILANHostConfigManagement.

	virtual void deleteDNSServer(const std::string& newDNSServers) = 0;

	virtual void deleteIPRouter(const std::string& newIPRouters) = 0;

	virtual void deleteReservedAddress(const std::string& newReservedAddresses) = 0;

	virtual void getAddressRange(std::string& newMinAddress, std::string& newMaxAddress) = 0;

	virtual void getDHCPRelay(bool& newDHCPRelay) = 0;

	virtual void getDHCPServerConfigurable(bool& newDHCPServerConfigurable) = 0;

	virtual void getDNSServers(std::string& newDNSServers) = 0;

	virtual void getDomainName(std::string& newDomainName) = 0;

	virtual void getIPRoutersList(std::string& newIPRouters) = 0;

	virtual void getReservedAddresses(std::string& newReservedAddresses) = 0;

	virtual void getSubnetMask(std::string& newSubnetMask) = 0;

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void setAddressRange(const std::string& newMinAddress, const std::string& newMaxAddress) = 0;

	virtual void setDHCPRelay(bool newDHCPRelay) = 0;

	virtual void setDHCPServerConfigurable(bool newDHCPServerConfigurable) = 0;

	virtual void setDNSServer(const std::string& newDNSServers) = 0;

	virtual void setDomainName(const std::string& newDomainName) = 0;

	virtual void setIPRouter(const std::string& newIPRouters) = 0;

	virtual void setReservedAddress(const std::string& newReservedAddresses) = 0;

	virtual void setSubnetMask(const std::string& newSubnetMask) = 0;

};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_ILANHostConfigManagement_INCLUDED

