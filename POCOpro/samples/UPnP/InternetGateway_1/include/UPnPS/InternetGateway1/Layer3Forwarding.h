//
// Layer3Forwarding.h
//
// Library: InternetGateway1
// Package: InternetGateway1
// Module:  Layer3Forwarding
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


#ifndef InternetGateway1_Layer3Forwarding_INCLUDED
#define InternetGateway1_Layer3Forwarding_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


//@ namespace="urn:schemas-upnp-org:service:Layer3Forwarding:1"
//@ remote
class InternetGateway1_API Layer3Forwarding
{
public:
	typedef Poco::SharedPtr<Layer3Forwarding> Ptr;

	Layer3Forwarding();
		/// Creates a Layer3Forwarding.

	virtual ~Layer3Forwarding();
		/// Destroys the Layer3Forwarding.

	//@ $newDefaultConnectionService={name="NewDefaultConnectionService", direction=out}
	//@ name=GetDefaultConnectionService
	//@ replyName=GetDefaultConnectionServiceResponse
	virtual void getDefaultConnectionService(std::string& newDefaultConnectionService) = 0;

	//@ $newDefaultConnectionService={name="NewDefaultConnectionService"}
	//@ name=SetDefaultConnectionService
	//@ replyName=SetDefaultConnectionServiceResponse
	virtual void setDefaultConnectionService(const std::string& newDefaultConnectionService) = 0;

	//@ name=DefaultConnectionService
	//@ oneway=true
	Poco::BasicEvent<const std::string> defaultConnectionServiceChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_Layer3Forwarding_INCLUDED

