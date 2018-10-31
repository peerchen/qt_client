//
// DimmingClientHelper.h
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


#ifndef LightingControls1_DimmingClientHelper_INCLUDED
#define LightingControls1_DimmingClientHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/LightingControls1/IDimming.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingClientHelper
{
public:
	DimmingClientHelper();
		/// Creates a DimmingClientHelper.

	~DimmingClientHelper();
		/// Destroys the DimmingClientHelper.

	static IDimming::Ptr find(const std::string& uri);
		/// Return an interface for the service object identified by the given URI.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// The URI must have the following format: <scheme>://<authority>/<protocol>/<typeId>/<objectId>

	static IDimming::Ptr find(const std::string& uri, const std::string& protocol);
		/// Return a Proxy for the service object identified by the given URI.
		///
		/// The given protocol name is used to determine the Transport used by
		/// the Proxy. This is used for objects identified by URIs that do not
		/// follow the standard Remoting URI structure.

private:
	IDimming::Ptr findImpl(const std::string& uri);

	IDimming::Ptr findImpl(const std::string& uri, const std::string& protocol);

	static DimmingClientHelper& instance();

	Poco::RemotingNG::ORB* _pORB;
};


inline IDimming::Ptr DimmingClientHelper::find(const std::string& uri)
{
	return DimmingClientHelper::instance().findImpl(uri);
}


inline IDimming::Ptr DimmingClientHelper::find(const std::string& uri, const std::string& protocol)
{
	return DimmingClientHelper::instance().findImpl(uri, protocol);
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_DimmingClientHelper_INCLUDED

