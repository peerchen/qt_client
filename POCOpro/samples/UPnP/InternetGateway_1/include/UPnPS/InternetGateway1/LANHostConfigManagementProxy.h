//
// LANHostConfigManagementProxy.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  LANHostConfigManagementProxy
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


#ifndef InternetGateway1_LANHostConfigManagementProxy_INCLUDED
#define InternetGateway1_LANHostConfigManagementProxy_INCLUDED


#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/InternetGateway1/ILANHostConfigManagement.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API LANHostConfigManagementProxy: public UPnPS::InternetGateway1::ILANHostConfigManagement, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<LANHostConfigManagementProxy> Ptr;

	LANHostConfigManagementProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a LANHostConfigManagementProxy.

	virtual ~LANHostConfigManagementProxy();
		/// Destroys the LANHostConfigManagementProxy.

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
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& LANHostConfigManagementProxy::remoting__typeId() const
{
	return ILANHostConfigManagement::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_LANHostConfigManagementProxy_INCLUDED

