//
// SwitchPowerClientHelper.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerClientHelper
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


#include "UPnPS/LightingControls1/SwitchPowerClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/LightingControls1/SwitchPowerProxyFactory.h"


namespace UPnPS {
namespace LightingControls1 {


namespace
{
	static Poco::SingletonHolder<SwitchPowerClientHelper> shSwitchPowerClientHelper;
}


SwitchPowerClientHelper::SwitchPowerClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.LightingControls1.SwitchPower", new SwitchPowerProxyFactory);
}


SwitchPowerClientHelper::~SwitchPowerClientHelper()
{
}


ISwitchPower::Ptr SwitchPowerClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<ISwitchPower>();
}


ISwitchPower::Ptr SwitchPowerClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, ISwitchPower::remoting__typeId(), protocol);
	return pInterface.cast<ISwitchPower>();
}


SwitchPowerClientHelper& SwitchPowerClientHelper::instance()
{
	return *shSwitchPowerClientHelper.get();
}


} // namespace LightingControls1
} // namespace UPnPS

