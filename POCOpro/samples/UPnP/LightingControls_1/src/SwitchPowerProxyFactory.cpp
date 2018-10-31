//
// SwitchPowerProxyFactory.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerProxyFactory
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


#include "UPnPS/LightingControls1/SwitchPowerProxyFactory.h"


namespace UPnPS {
namespace LightingControls1 {


SwitchPowerProxyFactory::SwitchPowerProxyFactory():
	Poco::RemotingNG::ProxyFactory()

{
}


SwitchPowerProxyFactory::~SwitchPowerProxyFactory()
{
}


Poco::RemotingNG::Proxy* SwitchPowerProxyFactory::createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const
{
	return new UPnPS::LightingControls1::SwitchPowerProxy(oid);
}


} // namespace LightingControls1
} // namespace UPnPS

