//
// WANIPConnectionClientHelper.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANIPConnectionClientHelper
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


#ifndef InternetGateway1_WANIPConnectionClientHelper_INCLUDED
#define InternetGateway1_WANIPConnectionClientHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/IWANIPConnection.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANIPConnectionClientHelper
{
public:
	WANIPConnectionClientHelper();
		/// Creates a WANIPConnectionClientHelper.

	~WANIPConnectionClientHelper();
		/// Destroys the WANIPConnectionClientHelper.

	static IWANIPConnection::Ptr find(const std::string& uri);
		/// Return an interface for the service object identified by the given URI.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// The URI must have the following format: <scheme>://<authority>/<protocol>/<typeId>/<objectId>

	static IWANIPConnection::Ptr find(const std::string& uri, const std::string& protocol);
		/// Return a Proxy for the service object identified by the given URI.
		///
		/// The given protocol name is used to determine the Transport used by
		/// the Proxy. This is used for objects identified by URIs that do not
		/// follow the standard Remoting URI structure.

private:
	IWANIPConnection::Ptr findImpl(const std::string& uri);

	IWANIPConnection::Ptr findImpl(const std::string& uri, const std::string& protocol);

	static WANIPConnectionClientHelper& instance();

	Poco::RemotingNG::ORB* _pORB;
};


inline IWANIPConnection::Ptr WANIPConnectionClientHelper::find(const std::string& uri)
{
	return WANIPConnectionClientHelper::instance().findImpl(uri);
}


inline IWANIPConnection::Ptr WANIPConnectionClientHelper::find(const std::string& uri, const std::string& protocol)
{
	return WANIPConnectionClientHelper::instance().findImpl(uri, protocol);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANIPConnectionClientHelper_INCLUDED

