//
// LANHostConfigManagementRemoteObject.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  LANHostConfigManagementRemoteObject
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


#include "UPnPS/InternetGateway1/LANHostConfigManagementRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


LANHostConfigManagementRemoteObject::LANHostConfigManagementRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> pServiceObject):
	UPnPS::InternetGateway1::ILANHostConfigManagement(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


LANHostConfigManagementRemoteObject::~LANHostConfigManagementRemoteObject()
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

