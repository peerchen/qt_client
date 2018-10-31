//
// WANEthernetLinkConfig.h
//
// Library: InternetGateway1
// Package: InternetGateway1
// Module:  WANEthernetLinkConfig
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


#ifndef InternetGateway1_WANEthernetLinkConfig_INCLUDED
#define InternetGateway1_WANEthernetLinkConfig_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


//@ namespace="urn:schemas-upnp-org:service:WANEthernetLinkConfig:1"
//@ remote
class InternetGateway1_API WANEthernetLinkConfig
{
public:
	typedef Poco::SharedPtr<WANEthernetLinkConfig> Ptr;

	WANEthernetLinkConfig();
		/// Creates a WANEthernetLinkConfig.

	virtual ~WANEthernetLinkConfig();
		/// Destroys the WANEthernetLinkConfig.

	//@ $newEthernetLinkStatus={name="NewEthernetLinkStatus", direction=out}
	//@ name=GetEthernetLinkStatus
	//@ replyName=GetEthernetLinkStatusResponse
	virtual void getEthernetLinkStatus(std::string& newEthernetLinkStatus) = 0;

	//@ name=EthernetLinkStatus
	//@ oneway=true
	Poco::BasicEvent<const std::string> ethernetLinkStatusChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANEthernetLinkConfig_INCLUDED

