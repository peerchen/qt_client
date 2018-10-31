//
// ConnectionManager1ProxyFactory.h
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


#ifndef MediaServer1_ConnectionManager1ProxyFactory_INCLUDED
#define MediaServer1_ConnectionManager1ProxyFactory_INCLUDED


#include "Poco/RemotingNG/ProxyFactory.h"
#include "UPnPS/MediaServer1/ConnectionManager1Proxy.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ConnectionManager1ProxyFactory: public Poco::RemotingNG::ProxyFactory
{
public:
	ConnectionManager1ProxyFactory();
		/// Creates a ConnectionManager1ProxyFactory.

	~ConnectionManager1ProxyFactory();
		/// Destroys the ConnectionManager1ProxyFactory.

	Poco::RemotingNG::Proxy* createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const;
		/// Creates and returns a new Proxy object.

};


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ConnectionManager1ProxyFactory_INCLUDED

