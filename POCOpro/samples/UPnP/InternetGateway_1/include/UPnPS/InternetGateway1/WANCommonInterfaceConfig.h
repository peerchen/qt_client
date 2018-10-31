//
// WANCommonInterfaceConfig.h
//
// Library: InternetGateway1
// Package: InternetGateway1
// Module:  WANCommonInterfaceConfig
//
// This file has been generated on 2012-10-29 11:09:03 UTC.
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


#ifndef InternetGateway1_WANCommonInterfaceConfig_INCLUDED
#define InternetGateway1_WANCommonInterfaceConfig_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


//@ namespace="urn:schemas-upnp-org:service:WANCommonInterfaceConfig:1"
//@ remote
class InternetGateway1_API WANCommonInterfaceConfig
{
public:
	typedef Poco::SharedPtr<WANCommonInterfaceConfig> Ptr;

	WANCommonInterfaceConfig();
		/// Creates a WANCommonInterfaceConfig.

	virtual ~WANCommonInterfaceConfig();
		/// Destroys the WANCommonInterfaceConfig.

	//@ $newActiveConnDeviceContainer={name="NewActiveConnDeviceContainer", direction=out}
	//@ $newActiveConnectionIndex={name="NewActiveConnectionIndex"}
	//@ $newActiveConnectionServiceID={name="NewActiveConnectionServiceID", direction=out}
	//@ name=GetActiveConnection
	//@ optional=true
	//@ replyName=GetActiveConnectionResponse
	virtual void getActiveConnection(Poco::UInt16 newActiveConnectionIndex, std::string& newActiveConnDeviceContainer, std::string& newActiveConnectionServiceID) = 0;

	//@ $newLayer1DownstreamMaxBitRate={name="NewLayer1DownstreamMaxBitRate", direction=out}
	//@ $newLayer1UpstreamMaxBitRate={name="NewLayer1UpstreamMaxBitRate", direction=out}
	//@ $newPhysicalLinkStatus={name="NewPhysicalLinkStatus", direction=out}
	//@ $newWANAccessType={name="NewWANAccessType", direction=out}
	//@ name=GetCommonLinkProperties
	//@ replyName=GetCommonLinkPropertiesResponse
	virtual void getCommonLinkProperties(std::string& newWANAccessType, Poco::UInt32& newLayer1UpstreamMaxBitRate, Poco::UInt32& newLayer1DownstreamMaxBitRate, std::string& newPhysicalLinkStatus) = 0;

	//@ $newEnabledForInternet={name="NewEnabledForInternet", direction=out}
	//@ name=GetEnabledForInternet
	//@ optional=true
	//@ replyName=GetEnabledForInternetResponse
	virtual void getEnabledForInternet(bool& newEnabledForInternet) = 0;

	//@ $newMaximumActiveConnections={name="NewMaximumActiveConnections", direction=out}
	//@ name=GetMaximumActiveConnections
	//@ optional=true
	//@ replyName=GetMaximumActiveConnectionsResponse
	virtual void getMaximumActiveConnections(Poco::UInt16& newMaximumActiveConnections) = 0;

	//@ $newTotalBytesReceived={name="NewTotalBytesReceived", direction=out}
	//@ name=GetTotalBytesReceived
	//@ optional=true
	//@ replyName=GetTotalBytesReceivedResponse
	virtual void getTotalBytesReceived(Poco::UInt32& newTotalBytesReceived) = 0;

	//@ $newTotalBytesSent={name="NewTotalBytesSent", direction=out}
	//@ name=GetTotalBytesSent
	//@ optional=true
	//@ replyName=GetTotalBytesSentResponse
	virtual void getTotalBytesSent(Poco::UInt32& newTotalBytesSent) = 0;

	//@ $newTotalPacketsReceived={name="NewTotalPacketsReceived", direction=out}
	//@ name=GetTotalPacketsReceived
	//@ optional=true
	//@ replyName=GetTotalPacketsReceivedResponse
	virtual void getTotalPacketsReceived(Poco::UInt32& newTotalPacketsReceived) = 0;

	//@ $newTotalPacketsSent={name="NewTotalPacketsSent", direction=out}
	//@ name=GetTotalPacketsSent
	//@ optional=true
	//@ replyName=GetTotalPacketsSentResponse
	virtual void getTotalPacketsSent(Poco::UInt32& newTotalPacketsSent) = 0;

	//@ $newWANAccessProvider={name="NewWANAccessProvider", direction=out}
	//@ name=GetWANAccessProvider
	//@ optional=true
	//@ replyName=GetWANAccessProviderResponse
	virtual void getWANAccessProvider(std::string& newWANAccessProvider) = 0;

	//@ $newEnabledForInternet={name="NewEnabledForInternet"}
	//@ name=SetEnabledForInternet
	//@ optional=true
	//@ replyName=SetEnabledForInternetResponse
	virtual void setEnabledForInternet(bool newEnabledForInternet) = 0;

	//@ name=EnabledForInternet
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const bool> enabledForInternetChanged;
	//@ name=NumberOfActiveConnections
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const Poco::UInt16> numberOfActiveConnectionsChanged;
	//@ name=PhysicalLinkStatus
	//@ oneway=true
	Poco::BasicEvent<const std::string> physicalLinkStatusChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCommonInterfaceConfig_INCLUDED

