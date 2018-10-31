//
// LANHostConfigManagementSkeleton.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  LANHostConfigManagementSkeleton
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


#ifndef InternetGateway1_LANHostConfigManagementSkeleton_INCLUDED
#define InternetGateway1_LANHostConfigManagementSkeleton_INCLUDED


#include "Poco/RemotingNG/Skeleton.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/LANHostConfigManagementRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API LANHostConfigManagementSkeleton: public Poco::RemotingNG::Skeleton
{
public:
	LANHostConfigManagementSkeleton();
		/// Creates a LANHostConfigManagementSkeleton.

	virtual ~LANHostConfigManagementSkeleton();
		/// Destroys a LANHostConfigManagementSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& LANHostConfigManagementSkeleton::remoting__typeId() const
{
	return ILANHostConfigManagement::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_LANHostConfigManagementSkeleton_INCLUDED

