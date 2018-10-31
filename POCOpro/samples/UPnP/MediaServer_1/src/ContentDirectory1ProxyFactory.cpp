//
// ContentDirectory1ProxyFactory.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1ProxyFactory
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


#include "UPnPS/MediaServer1/ContentDirectory1ProxyFactory.h"


namespace UPnPS {
namespace MediaServer1 {


ContentDirectory1ProxyFactory::ContentDirectory1ProxyFactory():
	Poco::RemotingNG::ProxyFactory()

{
}


ContentDirectory1ProxyFactory::~ContentDirectory1ProxyFactory()
{
}


Poco::RemotingNG::Proxy* ContentDirectory1ProxyFactory::createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const
{
	return new UPnPS::MediaServer1::ContentDirectory1Proxy(oid);
}


} // namespace MediaServer1
} // namespace UPnPS

