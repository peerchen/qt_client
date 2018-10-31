//
// SwitchPower.h
//
// Library: LightingControls1
// Package: LightingControls1
// Module:  SwitchPower
//
// This file has been generated on 2012-10-29 10:08:38 UTC.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef LightingControls1_SwitchPower_INCLUDED
#define LightingControls1_SwitchPower_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


//@ namespace="urn:schemas-upnp-org:service:SwitchPower:1"
//@ remote
class LightingControls1_API SwitchPower
{
public:
	typedef Poco::SharedPtr<SwitchPower> Ptr;

	SwitchPower();
		/// Creates a SwitchPower.

	virtual ~SwitchPower();
		/// Destroys the SwitchPower.

	//@ $resultStatus={name="ResultStatus", direction=out}
	//@ name=GetStatus
	//@ replyName=GetStatusResponse
	virtual void getStatus(bool& resultStatus) = 0;

	//@ $retTargetValue={name="RetTargetValue", direction=out}
	//@ name=GetTarget
	//@ replyName=GetTargetResponse
	virtual void getTarget(bool& retTargetValue) = 0;

	//@ $newTargetValue={name="newTargetValue"}
	//@ name=SetTarget
	//@ replyName=SetTargetResponse
	virtual void setTarget(bool newTargetValue) = 0;

	//@ name=Status
	//@ oneway=true
	Poco::BasicEvent<const bool> statusChanged;
};


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_SwitchPower_INCLUDED

