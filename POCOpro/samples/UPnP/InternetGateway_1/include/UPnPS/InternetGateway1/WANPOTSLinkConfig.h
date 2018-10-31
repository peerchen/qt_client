//
// WANPOTSLinkConfig.h
//
// Library: InternetGateway1
// Package: InternetGateway1
// Module:  WANPOTSLinkConfig
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


#ifndef InternetGateway1_WANPOTSLinkConfig_INCLUDED
#define InternetGateway1_WANPOTSLinkConfig_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


//@ namespace="urn:schemas-upnp-org:service:WANPOTSLinkConfig:1"
//@ remote
class InternetGateway1_API WANPOTSLinkConfig
{
public:
	typedef Poco::SharedPtr<WANPOTSLinkConfig> Ptr;

	WANPOTSLinkConfig();
		/// Creates a WANPOTSLinkConfig.

	virtual ~WANPOTSLinkConfig();
		/// Destroys the WANPOTSLinkConfig.

	//@ $newDelayBetweenRetries={name="NewDelayBetweenRetries", direction=out}
	//@ $newNumberOfRetries={name="NewNumberOfRetries", direction=out}
	//@ name=GetCallRetryInfo
	//@ replyName=GetCallRetryInfoResponse
	virtual void getCallRetryInfo(Poco::UInt32& newNumberOfRetries, Poco::UInt32& newDelayBetweenRetries) = 0;

	//@ $newDataCompression={name="NewDataCompression", direction=out}
	//@ name=GetDataCompression
	//@ optional=true
	//@ replyName=GetDataCompressionResponse
	virtual void getDataCompression(std::string& newDataCompression) = 0;

	//@ $newDataModulationSupported={name="NewDataModulationSupported", direction=out}
	//@ name=GetDataModulationSupported
	//@ optional=true
	//@ replyName=GetDataModulationSupportedResponse
	virtual void getDataModulationSupported(std::string& newDataModulationSupported) = 0;

	//@ $newDataProtocol={name="NewDataProtocol", direction=out}
	//@ name=GetDataProtocol
	//@ optional=true
	//@ replyName=GetDataProtocolResponse
	virtual void getDataProtocol(std::string& newDataProtocol) = 0;

	//@ $newFclass={name="NewFclass", direction=out}
	//@ name=GetFclass
	//@ optional=true
	//@ replyName=GetFclassResponse
	virtual void getFclass(std::string& newFclass) = 0;

	//@ $newISPInfo={name="NewISPInfo", direction=out}
	//@ $newISPPhoneNumber={name="NewISPPhoneNumber", direction=out}
	//@ $newLinkType={name="NewLinkType", direction=out}
	//@ name=GetISPInfo
	//@ replyName=GetISPInfoResponse
	virtual void getISPInfo(std::string& newISPPhoneNumber, std::string& newISPInfo, std::string& newLinkType) = 0;

	//@ $newPlusVTRCommandSupported={name="NewPlusVTRCommandSupported", direction=out}
	//@ name=GetPlusVTRCommandSupported
	//@ optional=true
	//@ replyName=GetPlusVTRCommandSupportedResponse
	virtual void getPlusVTRCommandSupported(bool& newPlusVTRCommandSupported) = 0;

	//@ $newDelayBetweenRetries={name="NewDelayBetweenRetries"}
	//@ $newNumberOfRetries={name="NewNumberOfRetries"}
	//@ name=SetCallRetryInfo
	//@ optional=true
	//@ replyName=SetCallRetryInfoResponse
	virtual void setCallRetryInfo(Poco::UInt32 newNumberOfRetries, Poco::UInt32 newDelayBetweenRetries) = 0;

	//@ $newISPInfo={name="NewISPInfo"}
	//@ $newISPPhoneNumber={name="NewISPPhoneNumber"}
	//@ $newLinkType={name="NewLinkType"}
	//@ name=SetISPInfo
	//@ optional=true
	//@ replyName=SetISPInfoResponse
	virtual void setISPInfo(const std::string& newISPPhoneNumber, const std::string& newISPInfo, const std::string& newLinkType) = 0;

};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANPOTSLinkConfig_INCLUDED

