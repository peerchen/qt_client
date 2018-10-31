//
// ConnectionManager1ProxyFactory.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1ProxyFactory
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


#include "UPnPS/MediaServer1/ConnectionManager1ProxyFactory.h"


namespace UPnPS {
namespace MediaServer1 {


ConnectionManager1ProxyFactory::ConnectionManager1ProxyFactory():
	Poco::RemotingNG::ProxyFactory()

{
}


ConnectionManager1ProxyFactory::~ConnectionManager1ProxyFactory()
{
}


Poco::RemotingNG::Proxy* ConnectionManager1ProxyFactory::createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const
{
	return new UPnPS::MediaServer1::ConnectionManager1Proxy(oid);
}


} // namespace MediaServer1
} // namespace UPnPS

