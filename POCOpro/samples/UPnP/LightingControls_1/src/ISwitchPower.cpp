//
// ISwitchPower.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  ISwitchPower
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


#include "UPnPS/LightingControls1/ISwitchPower.h"


namespace UPnPS {
namespace LightingControls1 {


ISwitchPower::ISwitchPower():
	Poco::RefCountedObject(),
	statusChanged()
{
}


ISwitchPower::~ISwitchPower()
{
}


const Poco::RemotingNG::Identifiable::TypeId& ISwitchPower::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("UPnPS.LightingControls1.SwitchPower");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace LightingControls1
} // namespace UPnPS

