//
// WANCableLinkConfigClientHelper.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigClientHelper
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


#ifndef InternetGateway1_WANCableLinkConfigClientHelper_INCLUDED
#define InternetGateway1_WANCableLinkConfigClientHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/InternetGateway1/IWANCableLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCableLinkConfigClientHelper
{
public:
	WANCableLinkConfigClientHelper();
		/// Creates a WANCableLinkConfigClientHelper.

	~WANCableLinkConfigClientHelper();
		/// Destroys the WANCableLinkConfigClientHelper.

	static IWANCableLinkConfig::Ptr find(const std::string& uri);
		/// Return an interface for the service object identified by the given URI.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// The URI must have the following format: <scheme>://<authority>/<protocol>/<typeId>/<objectId>

	static IWANCableLinkConfig::Ptr find(const std::string& uri, const std::string& protocol);
		/// Return a Proxy for the service object identified by the given URI.
		///
		/// The given protocol name is used to determine the Transport used by
		/// the Proxy. This is used for objects identified by URIs that do not
		/// follow the standard Remoting URI structure.

private:
	IWANCableLinkConfig::Ptr findImpl(const std::string& uri);

	IWANCableLinkConfig::Ptr findImpl(const std::string& uri, const std::string& protocol);

	static WANCableLinkConfigClientHelper& instance();

	Poco::RemotingNG::ORB* _pORB;
};


inline IWANCableLinkConfig::Ptr WANCableLinkConfigClientHelper::find(const std::string& uri)
{
	return WANCableLinkConfigClientHelper::instance().findImpl(uri);
}


inline IWANCableLinkConfig::Ptr WANCableLinkConfigClientHelper::find(const std::string& uri, const std::string& protocol)
{
	return WANCableLinkConfigClientHelper::instance().findImpl(uri, protocol);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCableLinkConfigClientHelper_INCLUDED
