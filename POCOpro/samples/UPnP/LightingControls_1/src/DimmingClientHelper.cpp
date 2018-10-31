//
// DimmingClientHelper.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingClientHelper
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


#include "UPnPS/LightingControls1/DimmingClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/LightingControls1/DimmingProxyFactory.h"


namespace UPnPS {
namespace LightingControls1 {


namespace
{
	static Poco::SingletonHolder<DimmingClientHelper> shDimmingClientHelper;
}


DimmingClientHelper::DimmingClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.LightingControls1.Dimming", new DimmingProxyFactory);
}


DimmingClientHelper::~DimmingClientHelper()
{
}


IDimming::Ptr DimmingClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IDimming>();
}


IDimming::Ptr DimmingClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IDimming::remoting__typeId(), protocol);
	return pInterface.cast<IDimming>();
}


DimmingClientHelper& DimmingClientHelper::instance()
{
	return *shDimmingClientHelper.get();
}


} // namespace LightingControls1
} // namespace UPnPS

