//
// OrderCollectionEndpointClientHelper.h
//
// Package: Generated
// Module:  OrderCollectionEndpointClientHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
//


#ifndef OrderCollectionEndpointClientHelper_INCLUDED
#define OrderCollectionEndpointClientHelper_INCLUDED


#include "Pizzeria/IOrderCollectionEndpoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"


namespace Pizzeria {


class OrderCollectionEndpointClientHelper
{
public:
	OrderCollectionEndpointClientHelper();
		/// Creates a OrderCollectionEndpointClientHelper.

	~OrderCollectionEndpointClientHelper();
		/// Destroys the OrderCollectionEndpointClientHelper.

	static IOrderCollectionEndpoint::Ptr find(const std::string& uri);
		/// Return an interface for the service object identified by the given URI.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// The URI must have the following format: <scheme>://<authority>/<protocol>/<typeId>/<objectId>

	static IOrderCollectionEndpoint::Ptr find(const std::string& uri, const std::string& protocol);
		/// Return a Proxy for the service object identified by the given URI.
		///
		/// The given protocol name is used to determine the Transport used by
		/// the Proxy. This is used for objects identified by URIs that do not
		/// follow the standard Remoting URI structure.

private:
	IOrderCollectionEndpoint::Ptr findImpl(const std::string& uri);

	IOrderCollectionEndpoint::Ptr findImpl(const std::string& uri, const std::string& protocol);

	static OrderCollectionEndpointClientHelper& instance();

	Poco::RemotingNG::ORB* _pORB;
};


inline IOrderCollectionEndpoint::Ptr OrderCollectionEndpointClientHelper::find(const std::string& uri)
{
	return OrderCollectionEndpointClientHelper::instance().findImpl(uri);
}


inline IOrderCollectionEndpoint::Ptr OrderCollectionEndpointClientHelper::find(const std::string& uri, const std::string& protocol)
{
	return OrderCollectionEndpointClientHelper::instance().findImpl(uri, protocol);
}


} // namespace Pizzeria


#endif // OrderCollectionEndpointClientHelper_INCLUDED

