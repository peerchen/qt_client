//
// WANCableLinkConfig.h
//
// Library: InternetGateway1
// Package: InternetGateway1
// Module:  WANCableLinkConfig
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


#ifndef InternetGateway1_WANCableLinkConfig_INCLUDED
#define InternetGateway1_WANCableLinkConfig_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


//@ namespace="urn:schemas-upnp-org:service:WANCableLinkConfig:1"
//@ remote
class InternetGateway1_API WANCableLinkConfig
{
public:
	typedef Poco::SharedPtr<WANCableLinkConfig> Ptr;

	WANCableLinkConfig();
		/// Creates a WANCableLinkConfig.

	virtual ~WANCableLinkConfig();
		/// Destroys the WANCableLinkConfig.

	//@ $newBPIEncryptionEnabled={name="NewBPIEncryptionEnabled", direction=out}
	//@ name=GetBPIEncryptionEnabled
	//@ optional=true
	//@ replyName=GetBPIEncryptionEnabledResponse
	virtual void getBPIEncryptionEnabled(bool& newBPIEncryptionEnabled) = 0;

	//@ $newCableLinkConfigState={name="NewCableLinkConfigState", direction=out}
	//@ $newLinkType={name="NewLinkType", direction=out}
	//@ name=GetCableLinkConfigInfo
	//@ replyName=GetCableLinkConfigInfoResponse
	virtual void getCableLinkConfigInfo(std::string& newCableLinkConfigState, std::string& newLinkType) = 0;

	//@ $newConfigFile={name="NewConfigFile", direction=out}
	//@ name=GetConfigFile
	//@ optional=true
	//@ replyName=GetConfigFileResponse
	virtual void getConfigFile(std::string& newConfigFile) = 0;

	//@ $newDownstreamFrequency={name="NewDownstreamFrequency", direction=out}
	//@ name=GetDownstreamFrequency
	//@ optional=true
	//@ replyName=GetDownstreamFrequencyResponse
	virtual void getDownstreamFrequency(Poco::UInt32& newDownstreamFrequency) = 0;

	//@ $newDownstreamModulation={name="NewDownstreamModulation", direction=out}
	//@ name=GetDownstreamModulation
	//@ optional=true
	//@ replyName=GetDownstreamModulationResponse
	virtual void getDownstreamModulation(std::string& newDownstreamModulation) = 0;

	//@ $newTFTPServer={name="NewTFTPServer", direction=out}
	//@ name=GetTFTPServer
	//@ optional=true
	//@ replyName=GetTFTPServerResponse
	virtual void getTFTPServer(std::string& newTFTPServer) = 0;

	//@ $newUpstreamChannelID={name="NewUpstreamChannelID", direction=out}
	//@ name=GetUpstreamChannelID
	//@ optional=true
	//@ replyName=GetUpstreamChannelIDResponse
	virtual void getUpstreamChannelID(Poco::UInt32& newUpstreamChannelID) = 0;

	//@ $newUpstreamFrequency={name="NewUpstreamFrequency", direction=out}
	//@ name=GetUpstreamFrequency
	//@ optional=true
	//@ replyName=GetUpstreamFrequencyResponse
	virtual void getUpstreamFrequency(Poco::UInt32& newUpstreamFrequency) = 0;

	//@ $newUpstreamModulation={name="NewUpstreamModulation", direction=out}
	//@ name=GetUpstreamModulation
	//@ optional=true
	//@ replyName=GetUpstreamModulationResponse
	virtual void getUpstreamModulation(std::string& newUpstreamModulation) = 0;

	//@ $newUpstreamPowerLevel={name="NewUpstreamPowerLevel", direction=out}
	//@ name=GetUpstreamPowerLevel
	//@ optional=true
	//@ replyName=GetUpstreamPowerLevelResponse
	virtual void getUpstreamPowerLevel(Poco::UInt32& newUpstreamPowerLevel) = 0;

	//@ name=BPIEncryptionEnabled
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const bool> bPIEncryptionEnabledChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCableLinkConfig_INCLUDED

