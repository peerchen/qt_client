//
// DimmingProxyFactory.h
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


#ifndef LightingControls1_DimmingProxyFactory_INCLUDED
#define LightingControls1_DimmingProxyFactory_INCLUDED


#include "Poco/RemotingNG/ProxyFactory.h"
#include "UPnPS/LightingControls1/DimmingProxy.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingProxyFactory: public Poco::RemotingNG::ProxyFactory
{
public:
	DimmingProxyFactory();
		/// Creates a DimmingProxyFactory.

	~DimmingProxyFactory();
		/// Destroys the DimmingProxyFactory.

	Poco::RemotingNG::Proxy* createProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid) const;
		/// Creates and returns a new Proxy object.

};


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_DimmingProxyFactory_INCLUDED

