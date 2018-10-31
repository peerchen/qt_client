//
// Layer3ForwardingSkeleton.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingSkeleton
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


#ifndef InternetGateway1_Layer3ForwardingSkeleton_INCLUDED
#define InternetGateway1_Layer3ForwardingSkeleton_INCLUDED


#include "Poco/RemotingNG/Skeleton.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/Layer3ForwardingRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API Layer3ForwardingSkeleton: public Poco::RemotingNG::Skeleton
{
public:
	Layer3ForwardingSkeleton();
		/// Creates a Layer3ForwardingSkeleton.

	virtual ~Layer3ForwardingSkeleton();
		/// Destroys a Layer3ForwardingSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& Layer3ForwardingSkeleton::remoting__typeId() const
{
	return ILayer3Forwarding::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_Layer3ForwardingSkeleton_INCLUDED

