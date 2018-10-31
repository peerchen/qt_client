//
// WANPOTSLinkConfigRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPOTSLinkConfigRemoteObject
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


#include "UPnPS/InternetGateway1/WANPOTSLinkConfigRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


WANPOTSLinkConfigRemoteObject::WANPOTSLinkConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> pServiceObject):
	UPnPS::InternetGateway1::IWANPOTSLinkConfig(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


WANPOTSLinkConfigRemoteObject::~WANPOTSLinkConfigRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


} // namespace InternetGateway1
} // namespace UPnPS

