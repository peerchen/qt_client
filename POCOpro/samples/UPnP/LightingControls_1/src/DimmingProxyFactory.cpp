//
// DimmingProxyFactory.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingProxyFactory
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


#include "UPnPS/LightingControls1/DimmingProxyFactory.h"


namespace UPnPS {
namespace LightingControls1 {


DimmingProxyFactory::DimmingProxyFactory():
	Poco::RemotingNG::ProxyFactory()

{
}


DimmingProxyFactory::~DimmingProxyFactory()
{
}


Poco::RemotingNG::Proxy* DimmingProxyFactory::createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const
{
	return new UPnPS::LightingControls1::DimmingProxy(oid);
}


} // namespace LightingControls1
} // namespace UPnPS

