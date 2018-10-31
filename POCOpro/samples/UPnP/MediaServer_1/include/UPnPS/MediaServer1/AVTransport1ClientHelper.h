//
// AVTransport1ClientHelper.h
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1ClientHelper
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


#ifndef MediaServer1_AVTransport1ClientHelper_INCLUDED
#define MediaServer1_AVTransport1ClientHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/MediaServer1/IAVTransport1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API AVTransport1ClientHelper
{
public:
	AVTransport1ClientHelper();
		/// Creates a AVTransport1ClientHelper.

	~AVTransport1ClientHelper();
		/// Destroys the AVTransport1ClientHelper.

	static IAVTransport1::Ptr find(const std::string& uri);
		/// Return an interface for the service object identified by the given URI.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// The URI must have the following format: <scheme>://<authority>/<protocol>/<typeId>/<objectId>

	static IAVTransport1::Ptr find(const std::string& uri, const std::string& protocol);
		/// Return a Proxy for the service object identified by the given URI.
		///
		/// The given protocol name is used to determine the Transport used by
		/// the Proxy. This is used for objects identified by URIs that do not
		/// follow the standard Remoting URI structure.

private:
	IAVTransport1::Ptr findImpl(const std::string& uri);

	IAVTransport1::Ptr findImpl(const std::string& uri, const std::string& protocol);

	static AVTransport1ClientHelper& instance();

	Poco::RemotingNG::ORB* _pORB;
};


inline IAVTransport1::Ptr AVTransport1ClientHelper::find(const std::string& uri)
{
	return AVTransport1ClientHelper::instance().findImpl(uri);
}


inline IAVTransport1::Ptr AVTransport1ClientHelper::find(const std::string& uri, const std::string& protocol)
{
	return AVTransport1ClientHelper::instance().findImpl(uri, protocol);
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_AVTransport1ClientHelper_INCLUDED

