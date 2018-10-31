//
// WANIPConnectionProxyFactory.h
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


#ifndef InternetGateway1_WANIPConnectionProxyFactory_INCLUDED
#define InternetGateway1_WANIPConnectionProxyFactory_INCLUDED


#include "Poco/RemotingNG/ProxyFactory.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANIPConnectionProxy.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANIPConnectionProxyFactory: public Poco::RemotingNG::ProxyFactory
{
public:
	WANIPConnectionProxyFactory();
		/// Creates a WANIPConnectionProxyFactory.

	~WANIPConnectionProxyFactory();
		/// Destroys the WANIPConnectionProxyFactory.

	Poco::RemotingNG::Proxy* createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const;
		/// Creates and returns a new Proxy object.

};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANIPConnectionProxyFactory_INCLUDED

