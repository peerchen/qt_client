//
// WANDSLLinkConfig.h
//
// Library: InternetGateway1
// Package: InternetGateway1
// Module:  WANDSLLinkConfig
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


#ifndef InternetGateway1_WANDSLLinkConfig_INCLUDED
#define InternetGateway1_WANDSLLinkConfig_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


//@ namespace="urn:schemas-upnp-org:service: WANDSLLinkConfig:1"
//@ remote
class InternetGateway1_API WANDSLLinkConfig
{
public:
	typedef Poco::SharedPtr<WANDSLLinkConfig> Ptr;

	WANDSLLinkConfig();
		/// Creates a WANDSLLinkConfig.

	virtual ~WANDSLLinkConfig();
		/// Destroys the WANDSLLinkConfig.

	//@ $newATMEncapsulation={name="NewATMEncapsulation", direction=out}
	//@ name=GetATMEncapsulation
	//@ optional=true
	//@ replyName=GetATMEncapsulationResponse
	virtual void getATMEncapsulation(std::string& newATMEncapsulation) = 0;

	//@ $newAutoConfig={name="NewAutoConfig", direction=out}
	//@ name=GetAutoConfig
	//@ replyName=GetAutoConfigResponse
	virtual void getAutoConfig(bool& newAutoConfig) = 0;

	//@ $newLinkStatus={name="NewLinkStatus", direction=out}
	//@ $newLinkType={name="NewLinkType", direction=out}
	//@ name=GetDSLLinkInfo
	//@ replyName=GetDSLLinkInfoResponse
	virtual void getDSLLinkInfo(std::string& newLinkType, std::string& newLinkStatus) = 0;

	//@ $newDestinationAddress={name="NewDestinationAddress", direction=out}
	//@ name=GetDestinationAddress
	//@ optional=true
	//@ replyName=GetDestinationAddressResponse
	virtual void getDestinationAddress(std::string& newDestinationAddress) = 0;

	//@ $newFCSPreserved={name="NewFCSPreserved", direction=out}
	//@ name=GetFCSPreserved
	//@ optional=true
	//@ replyName=GetFCSPreservedResponse
	virtual void getFCSPreserved(bool& newFCSPreserved) = 0;

	//@ $newModulationType={name="NewModulationType", direction=out}
	//@ name=GetModulationType
	//@ optional=true
	//@ replyName=GetModulationTypeResponse
	virtual void getModulationType(std::string& newModulationType) = 0;

	//@ $newATMEncapsulation={name="NewATMEncapsulation"}
	//@ name=SetATMEncapsulation
	//@ optional=true
	//@ replyName=SetATMEncapsulationResponse
	virtual void setATMEncapsulation(const std::string& newATMEncapsulation) = 0;

	//@ $newLinkType={name="NewLinkType"}
	//@ name=SetDSLLinkType
	//@ replyName=SetDSLLinkTypeResponse
	virtual void setDSLLinkType(const std::string& newLinkType) = 0;

	//@ $newDestinationAddress={name="NewDestinationAddress"}
	//@ name=SetDestinationAddress
	//@ optional=true
	//@ replyName=SetDestinationAddressResponse
	virtual void setDestinationAddress(const std::string& newDestinationAddress) = 0;

	//@ $newFCSPreserved={name="NewFCSPreserved"}
	//@ name=SetFCSPreserved
	//@ optional=true
	//@ replyName=SetFCSPreservedResponse
	virtual void setFCSPreserved(bool newFCSPreserved) = 0;

	//@ name=AutoConfig
	//@ oneway=true
	Poco::BasicEvent<const bool> autoConfigChanged;
	//@ name=LinkStatus
	//@ oneway=true
	Poco::BasicEvent<const std::string> linkStatusChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANDSLLinkConfig_INCLUDED

