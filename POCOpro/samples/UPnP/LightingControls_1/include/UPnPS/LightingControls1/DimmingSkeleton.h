//
// DimmingSkeleton.h
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingSkeleton
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


#ifndef LightingControls1_DimmingSkeleton_INCLUDED
#define LightingControls1_DimmingSkeleton_INCLUDED


#include "Poco/RemotingNG/Skeleton.h"
#include "UPnPS/LightingControls1/DimmingRemoteObject.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingSkeleton: public Poco::RemotingNG::Skeleton
{
public:
	DimmingSkeleton();
		/// Creates a DimmingSkeleton.

	virtual ~DimmingSkeleton();
		/// Destroys a DimmingSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& DimmingSkeleton::remoting__typeId() const
{
	return IDimming::remoting__typeId();
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_DimmingSkeleton_INCLUDED

