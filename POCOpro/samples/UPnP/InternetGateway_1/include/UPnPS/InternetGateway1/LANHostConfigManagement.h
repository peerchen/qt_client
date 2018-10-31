//
// LANHostConfigManagement.h
//
// Library: InternetGateway1
// Package: InternetGateway1
// Module:  LANHostConfigManagement
//
// This file has been generated on 2012-10-29 11:09:02 UTC.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef InternetGateway1_LANHostConfigManagement_INCLUDED
#define InternetGateway1_LANHostConfigManagement_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


//@ namespace="urn:schemas-upnp-org:service:LANHostConfigManagement:1"
//@ remote
class InternetGateway1_API LANHostConfigManagement
{
public:
	typedef Poco::SharedPtr<LANHostConfigManagement> Ptr;

	LANHostConfigManagement();
		/// Creates a LANHostConfigManagement.

	virtual ~LANHostConfigManagement();
		/// Destroys the LANHostConfigManagement.

	//@ $newDNSServers={name="NewDNSServers"}
	//@ name=DeleteDNSServer
	//@ replyName=DeleteDNSServerResponse
	virtual void deleteDNSServer(const std::string& newDNSServers) = 0;

	//@ $newIPRouters={name="NewIPRouters"}
	//@ name=DeleteIPRouter
	//@ replyName=DeleteIPRouterResponse
	virtual void deleteIPRouter(const std::string& newIPRouters) = 0;

	//@ $newReservedAddresses={name="NewReservedAddresses"}
	//@ name=DeleteReservedAddress
	//@ replyName=DeleteReservedAddressResponse
	virtual void deleteReservedAddress(const std::string& newReservedAddresses) = 0;

	//@ $newMaxAddress={name="NewMaxAddress", direction=out}
	//@ $newMinAddress={name="NewMinAddress", direction=out}
	//@ name=GetAddressRange
	//@ replyName=GetAddressRangeResponse
	virtual void getAddressRange(std::string& newMinAddress, std::string& newMaxAddress) = 0;

	//@ $newDHCPRelay={name="NewDHCPRelay", direction=out}
	//@ name=GetDHCPRelay
	//@ replyName=GetDHCPRelayResponse
	virtual void getDHCPRelay(bool& newDHCPRelay) = 0;

	//@ $newDHCPServerConfigurable={name="NewDHCPServerConfigurable", direction=out}
	//@ name=GetDHCPServerConfigurable
	//@ replyName=GetDHCPServerConfigurableResponse
	virtual void getDHCPServerConfigurable(bool& newDHCPServerConfigurable) = 0;

	//@ $newDNSServers={name="NewDNSServers", direction=out}
	//@ name=GetDNSServers
	//@ replyName=GetDNSServersResponse
	virtual void getDNSServers(std::string& newDNSServers) = 0;

	//@ $newDomainName={name="NewDomainName", direction=out}
	//@ name=GetDomainName
	//@ replyName=GetDomainNameResponse
	virtual void getDomainName(std::string& newDomainName) = 0;

	//@ $newIPRouters={name="NewIPRouters", direction=out}
	//@ name=GetIPRoutersList
	//@ replyName=GetIPRoutersListResponse
	virtual void getIPRoutersList(std::string& newIPRouters) = 0;

	//@ $newReservedAddresses={name="NewReservedAddresses", direction=out}
	//@ name=GetReservedAddresses
	//@ replyName=GetReservedAddressesResponse
	virtual void getReservedAddresses(std::string& newReservedAddresses) = 0;

	//@ $newSubnetMask={name="NewSubnetMask", direction=out}
	//@ name=GetSubnetMask
	//@ replyName=GetSubnetMaskResponse
	virtual void getSubnetMask(std::string& newSubnetMask) = 0;

	//@ $newMaxAddress={name="NewMaxAddress"}
	//@ $newMinAddress={name="NewMinAddress"}
	//@ name=SetAddressRange
	//@ replyName=SetAddressRangeResponse
	virtual void setAddressRange(const std::string& newMinAddress, const std::string& newMaxAddress) = 0;

	//@ $newDHCPRelay={name="NewDHCPRelay"}
	//@ name=SetDHCPRelay
	//@ replyName=SetDHCPRelayResponse
	virtual void setDHCPRelay(bool newDHCPRelay) = 0;

	//@ $newDHCPServerConfigurable={name="NewDHCPServerConfigurable"}
	//@ name=SetDHCPServerConfigurable
	//@ replyName=SetDHCPServerConfigurableResponse
	virtual void setDHCPServerConfigurable(bool newDHCPServerConfigurable) = 0;

	//@ $newDNSServers={name="NewDNSServers"}
	//@ name=SetDNSServer
	//@ replyName=SetDNSServerResponse
	virtual void setDNSServer(const std::string& newDNSServers) = 0;

	//@ $newDomainName={name="NewDomainName"}
	//@ name=SetDomainName
	//@ replyName=SetDomainNameResponse
	virtual void setDomainName(const std::string& newDomainName) = 0;

	//@ $newIPRouters={name="NewIPRouters"}
	//@ name=SetIPRouter
	//@ replyName=SetIPRouterResponse
	virtual void setIPRouter(const std::string& newIPRouters) = 0;

	//@ $newReservedAddresses={name="NewReservedAddresses"}
	//@ name=SetReservedAddress
	//@ replyName=SetReservedAddressResponse
	virtual void setReservedAddress(const std::string& newReservedAddresses) = 0;

	//@ $newSubnetMask={name="NewSubnetMask"}
	//@ name=SetSubnetMask
	//@ replyName=SetSubnetMaskResponse
	virtual void setSubnetMask(const std::string& newSubnetMask) = 0;

};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_LANHostConfigManagement_INCLUDED

