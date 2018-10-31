//
// ConnectionManager1ClientHelper.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1ClientHelper
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


#ifndef MediaServer1_ConnectionManager1ClientHelper_INCLUDED
#define MediaServer1_ConnectionManager1ClientHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/MediaServer1/IConnectionManager1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ConnectionManager1ClientHelper
{
public:
	ConnectionManager1ClientHelper();
		/// Creates a ConnectionManager1ClientHelper.

	~ConnectionManager1ClientHelper();
		/// Destroys the ConnectionManager1ClientHelper.

	static IConnectionManager1::Ptr find(const std::string& uri);
		/// Return an interface for the service object identified by the given URI.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// The URI must have the following format: <scheme>://<authority>/<protocol>/<typeId>/<objectId>

	static IConnectionManager1::Ptr find(const std::string& uri, const std::string& protocol);
		/// Return a Proxy for the service object identified by the given URI.
		///
		/// The given protocol name is used to determine the Transport used by
		/// the Proxy. This is used for objects identified by URIs that do not
		/// follow the standard Remoting URI structure.

private:
	IConnectionManager1::Ptr findImpl(const std::string& uri);

	IConnectionManager1::Ptr findImpl(const std::string& uri, const std::string& protocol);

	static ConnectionManager1ClientHelper& instance();

	Poco::RemotingNG::ORB* _pORB;
};


inline IConnectionManager1::Ptr ConnectionManager1ClientHelper::find(const std::string& uri)
{
	return ConnectionManager1ClientHelper::instance().findImpl(uri);
}


inline IConnectionManager1::Ptr ConnectionManager1ClientHelper::find(const std::string& uri, const std::string& protocol)
{
	return ConnectionManager1ClientHelper::instance().findImpl(uri, protocol);
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ConnectionManager1ClientHelper_INCLUDED

