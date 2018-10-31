//
// SwitchPowerSkeleton.h
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerSkeleton
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


#ifndef LightingControls1_SwitchPowerSkeleton_INCLUDED
#define LightingControls1_SwitchPowerSkeleton_INCLUDED


#include "Poco/RemotingNG/Skeleton.h"
#include "UPnPS/LightingControls1/LightingControls1.h"
#include "UPnPS/LightingControls1/SwitchPowerRemoteObject.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API SwitchPowerSkeleton: public Poco::RemotingNG::Skeleton
{
public:
	SwitchPowerSkeleton();
		/// Creates a SwitchPowerSkeleton.

	virtual ~SwitchPowerSkeleton();
		/// Destroys a SwitchPowerSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchPowerSkeleton::remoting__typeId() const
{
	return ISwitchPower::remoting__typeId();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_SwitchPowerSkeleton_INCLUDED

