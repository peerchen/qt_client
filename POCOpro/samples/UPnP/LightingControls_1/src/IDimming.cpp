//
// IDimming.cpp
//
// Library: LightingControls1
// Package: Generated
// Module:  IDimming
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


#include "UPnPS/LightingControls1/IDimming.h"


namespace UPnPS {
namespace LightingControls1 {


IDimming::IDimming():
	Poco::RefCountedObject(),
	isRampingChanged(),
	loadLevelStatusChanged(),
	rampPausedChanged(),
	rampRateChanged(),
	stepDeltaChanged()
{
}


IDimming::~IDimming()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IDimming::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("UPnPS.LightingControls1.Dimming");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace LightingControls1
} // namespace UPnPS

