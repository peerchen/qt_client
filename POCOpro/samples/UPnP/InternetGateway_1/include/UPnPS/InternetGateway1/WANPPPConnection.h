//
// WANPPPConnection.h
//
// Library: InternetGateway1
// Package: InternetGateway1
// Module:  WANPPPConnection
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


#ifndef InternetGateway1_WANPPPConnection_INCLUDED
#define InternetGateway1_WANPPPConnection_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


//@ namespace="urn:schemas-upnp-org:service:WANPPPConnection:1"
//@ remote
class InternetGateway1_API WANPPPConnection
{
public:
	typedef Poco::SharedPtr<WANPPPConnection> Ptr;

	WANPPPConnection();
		/// Creates a WANPPPConnection.

	virtual ~WANPPPConnection();
		/// Destroys the WANPPPConnection.

	//@ $newEnabled={name="NewEnabled"}
	//@ $newExternalPort={name="NewExternalPort"}
	//@ $newInternalClient={name="NewInternalClient"}
	//@ $newInternalPort={name="NewInternalPort"}
	//@ $newLeaseDuration={name="NewLeaseDuration"}
	//@ $newPortMappingDescription={name="NewPortMappingDescription"}
	//@ $newProtocol={name="NewProtocol"}
	//@ $newRemoteHost={name="NewRemoteHost"}
	//@ name=AddPortMapping
	//@ replyName=AddPortMappingResponse
	virtual void addPortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16 newInternalPort, const std::string& newInternalClient, bool newEnabled, const std::string& newPortMappingDescription, Poco::UInt32 newLeaseDuration) = 0;

	//@ $newPassword={name="NewPassword"}
	//@ $newUserName={name="NewUserName"}
	//@ name=ConfigureConnection
	//@ optional=true
	//@ replyName=ConfigureConnectionResponse
	virtual void configureConnection(const std::string& newUserName, const std::string& newPassword) = 0;

	//@ $newExternalPort={name="NewExternalPort"}
	//@ $newProtocol={name="NewProtocol"}
	//@ $newRemoteHost={name="NewRemoteHost"}
	//@ name=DeletePortMapping
	//@ replyName=DeletePortMappingResponse
	virtual void deletePortMapping(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol) = 0;

	//@ name=ForceTermination
	//@ replyName=ForceTerminationResponse
	virtual void forceTermination() = 0;

	//@ $newAutoDisconnectTime={name="NewAutoDisconnectTime", direction=out}
	//@ name=GetAutoDisconnectTime
	//@ optional=true
	//@ replyName=GetAutoDisconnectTimeResponse
	virtual void getAutoDisconnectTime(Poco::UInt32& newAutoDisconnectTime) = 0;

	//@ $newConnectionType={name="NewConnectionType", direction=out}
	//@ $newPossibleConnectionTypes={name="NewPossibleConnectionTypes", direction=out}
	//@ name=GetConnectionTypeInfo
	//@ replyName=GetConnectionTypeInfoResponse
	virtual void getConnectionTypeInfo(std::string& newConnectionType, std::string& newPossibleConnectionTypes) = 0;

	//@ $newExternalIPAddress={name="NewExternalIPAddress", direction=out}
	//@ name=GetExternalIPAddress
	//@ replyName=GetExternalIPAddressResponse
	virtual void getExternalIPAddress(std::string& newExternalIPAddress) = 0;

	//@ $newEnabled={name="NewEnabled", direction=out}
	//@ $newExternalPort={name="NewExternalPort", direction=out}
	//@ $newInternalClient={name="NewInternalClient", direction=out}
	//@ $newInternalPort={name="NewInternalPort", direction=out}
	//@ $newLeaseDuration={name="NewLeaseDuration", direction=out}
	//@ $newPortMappingDescription={name="NewPortMappingDescription", direction=out}
	//@ $newPortMappingIndex={name="NewPortMappingIndex"}
	//@ $newProtocol={name="NewProtocol", direction=out}
	//@ $newRemoteHost={name="NewRemoteHost", direction=out}
	//@ name=GetGenericPortMappingEntry
	//@ replyName=GetGenericPortMappingEntryResponse
	virtual void getGenericPortMappingEntry(Poco::UInt16 newPortMappingIndex, std::string& newRemoteHost, Poco::UInt16& newExternalPort, std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration) = 0;

	//@ $newIdleDisconnectTime={name="NewIdleDisconnectTime", direction=out}
	//@ name=GetIdleDisconnectTime
	//@ optional=true
	//@ replyName=GetIdleDisconnectTimeResponse
	virtual void getIdleDisconnectTime(Poco::UInt32& newIdleDisconnectTime) = 0;

	//@ $newDownstreamMaxBitRate={name="NewDownstreamMaxBitRate", direction=out}
	//@ $newUpstreamMaxBitRate={name="NewUpstreamMaxBitRate", direction=out}
	//@ name=GetLinkLayerMaxBitRates
	//@ replyName=GetLinkLayerMaxBitRatesResponse
	virtual void getLinkLayerMaxBitRates(Poco::UInt32& newUpstreamMaxBitRate, Poco::UInt32& newDownstreamMaxBitRate) = 0;

	//@ $newNATEnabled={name="NewNATEnabled", direction=out}
	//@ $newRSIPAvailable={name="NewRSIPAvailable", direction=out}
	//@ name=GetNATRSIPStatus
	//@ replyName=GetNATRSIPStatusResponse
	virtual void getNATRSIPStatus(bool& newRSIPAvailable, bool& newNATEnabled) = 0;

	//@ $newPPPAuthenticationProtocol={name="NewPPPAuthenticationProtocol", direction=out}
	//@ name=GetPPPAuthenticationProtocol
	//@ optional=true
	//@ replyName=GetPPPAuthenticationProtocolResponse
	virtual void getPPPAuthenticationProtocol(std::string& newPPPAuthenticationProtocol) = 0;

	//@ $newPPPCompressionProtocol={name="NewPPPCompressionProtocol", direction=out}
	//@ name=GetPPPCompressionProtocol
	//@ optional=true
	//@ replyName=GetPPPCompressionProtocolResponse
	virtual void getPPPCompressionProtocol(std::string& newPPPCompressionProtocol) = 0;

	//@ $newPPPEncryptionProtocol={name="NewPPPEncryptionProtocol", direction=out}
	//@ name=GetPPPEncryptionProtocol
	//@ optional=true
	//@ replyName=GetPPPEncryptionProtocolResponse
	virtual void getPPPEncryptionProtocol(std::string& newPPPEncryptionProtocol) = 0;

	//@ $newPassword={name="NewPassword", direction=out}
	//@ name=GetPassword
	//@ optional=true
	//@ replyName=GetPasswordResponse
	virtual void getPassword(std::string& newPassword) = 0;

	//@ $newEnabled={name="NewEnabled", direction=out}
	//@ $newExternalPort={name="NewExternalPort"}
	//@ $newInternalClient={name="NewInternalClient", direction=out}
	//@ $newInternalPort={name="NewInternalPort", direction=out}
	//@ $newLeaseDuration={name="NewLeaseDuration", direction=out}
	//@ $newPortMappingDescription={name="NewPortMappingDescription", direction=out}
	//@ $newProtocol={name="NewProtocol"}
	//@ $newRemoteHost={name="NewRemoteHost"}
	//@ name=GetSpecificPortMappingEntry
	//@ replyName=GetSpecificPortMappingEntryResponse
	virtual void getSpecificPortMappingEntry(const std::string& newRemoteHost, Poco::UInt16 newExternalPort, const std::string& newProtocol, Poco::UInt16& newInternalPort, std::string& newInternalClient, bool& newEnabled, std::string& newPortMappingDescription, Poco::UInt32& newLeaseDuration) = 0;

	//@ $newConnectionStatus={name="NewConnectionStatus", direction=out}
	//@ $newLastConnectionError={name="NewLastConnectionError", direction=out}
	//@ $newUptime={name="NewUptime", direction=out}
	//@ name=GetStatusInfo
	//@ replyName=GetStatusInfoResponse
	virtual void getStatusInfo(std::string& newConnectionStatus, std::string& newLastConnectionError, Poco::UInt32& newUptime) = 0;

	//@ $newUserName={name="NewUserName", direction=out}
	//@ name=GetUserName
	//@ optional=true
	//@ replyName=GetUserNameResponse
	virtual void getUserName(std::string& newUserName) = 0;

	//@ $newWarnDisconnectDelay={name="NewWarnDisconnectDelay", direction=out}
	//@ name=GetWarnDisconnectDelay
	//@ optional=true
	//@ replyName=GetWarnDisconnectDelayResponse
	virtual void getWarnDisconnectDelay(Poco::UInt32& newWarnDisconnectDelay) = 0;

	//@ name=RequestConnection
	//@ replyName=RequestConnectionResponse
	virtual void requestConnection() = 0;

	//@ name=RequestTermination
	//@ optional=true
	//@ replyName=RequestTerminationResponse
	virtual void requestTermination() = 0;

	//@ $newAutoDisconnectTime={name="NewAutoDisconnectTime"}
	//@ name=SetAutoDisconnectTime
	//@ optional=true
	//@ replyName=SetAutoDisconnectTimeResponse
	virtual void setAutoDisconnectTime(Poco::UInt32 newAutoDisconnectTime) = 0;

	//@ $newConnectionType={name="NewConnectionType"}
	//@ name=SetConnectionType
	//@ replyName=SetConnectionTypeResponse
	virtual void setConnectionType(const std::string& newConnectionType) = 0;

	//@ $newIdleDisconnectTime={name="NewIdleDisconnectTime"}
	//@ name=SetIdleDisconnectTime
	//@ optional=true
	//@ replyName=SetIdleDisconnectTimeResponse
	virtual void setIdleDisconnectTime(Poco::UInt32 newIdleDisconnectTime) = 0;

	//@ $newWarnDisconnectDelay={name="NewWarnDisconnectDelay"}
	//@ name=SetWarnDisconnectDelay
	//@ optional=true
	//@ replyName=SetWarnDisconnectDelayResponse
	virtual void setWarnDisconnectDelay(Poco::UInt32 newWarnDisconnectDelay) = 0;

	//@ name=ConnectionStatus
	//@ oneway=true
	Poco::BasicEvent<const std::string> connectionStatusChanged;
	//@ name=ExternalIPAddress
	//@ oneway=true
	Poco::BasicEvent<const std::string> externalIPAddressChanged;
	//@ name=PortMappingNumberOfEntries
	//@ oneway=true
	Poco::BasicEvent<const Poco::UInt16> portMappingNumberOfEntriesChanged;
	//@ name=PossibleConnectionTypes
	//@ oneway=true
	Poco::BasicEvent<const std::string> possibleConnectionTypesChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANPPPConnection_INCLUDED

