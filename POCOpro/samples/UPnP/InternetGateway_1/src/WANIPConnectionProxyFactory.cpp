//
// WANIPConnectionProxyFactory.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANIPConnectionProxyFactory
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


#include "UPnPS/InternetGateway1/WANIPConnectionProxyFactory.h"


namespace UPnPS {
namespace InternetGateway1 {


WANIPConnectionProxyFactory::WANIPConnectionProxyFactory():
	Poco::RemotingNG::ProxyFactory()

{
}


WANIPConnectionProxyFactory::~WANIPConnectionProxyFactory()
{
}


Poco::RemotingNG::Proxy* WANIPConnectionProxyFactory::createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const
{
	return new UPnPS::InternetGateway1::WANIPConnectionProxy(oid);
}


} // namespace InternetGateway1
} // namespace UPnPS

