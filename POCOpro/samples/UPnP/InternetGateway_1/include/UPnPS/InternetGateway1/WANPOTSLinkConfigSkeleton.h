//
// WANPOTSLinkConfigSkeleton.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPOTSLinkConfigSkeleton
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


#ifndef InternetGateway1_WANPOTSLinkConfigSkeleton_INCLUDED
#define InternetGateway1_WANPOTSLinkConfigSkeleton_INCLUDED


#include "Poco/RemotingNG/Skeleton.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANPOTSLinkConfigRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANPOTSLinkConfigSkeleton: public Poco::RemotingNG::Skeleton
{
public:
	WANPOTSLinkConfigSkeleton();
		/// Creates a WANPOTSLinkConfigSkeleton.

	virtual ~WANPOTSLinkConfigSkeleton();
		/// Destroys a WANPOTSLinkConfigSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANPOTSLinkConfigSkeleton::remoting__typeId() const
{
	return IWANPOTSLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANPOTSLinkConfigSkeleton_INCLUDED

