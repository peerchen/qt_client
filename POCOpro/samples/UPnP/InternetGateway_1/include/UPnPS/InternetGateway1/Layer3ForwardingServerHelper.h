//
// Layer3ForwardingServerHelper.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingServerHelper
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


#ifndef InternetGateway1_Layer3ForwardingServerHelper_INCLUDED
#define InternetGateway1_Layer3ForwardingServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/InternetGateway1/ILayer3Forwarding.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/Layer3Forwarding.h"
#include "UPnPS/InternetGateway1/Layer3ForwardingRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API Layer3ForwardingServerHelper
{
public:
	typedef UPnPS::InternetGateway1::Layer3Forwarding Service;

	Layer3ForwardingServerHelper();
		/// Creates a Layer3ForwardingServerHelper.

	~Layer3ForwardingServerHelper();
		/// Destroys the Layer3ForwardingServerHelper.

	static Poco::AutoPtr<UPnPS::InternetGateway1::Layer3ForwardingRemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::InternetGateway1::Layer3Forwarding instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::InternetGateway1::Layer3Forwarding instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::Layer3ForwardingRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::InternetGateway1::Layer3Forwarding from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::InternetGateway1::Layer3ForwardingRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static Layer3ForwardingServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::Layer3ForwardingRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::InternetGateway1::Layer3ForwardingRemoteObject> Layer3ForwardingServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return Layer3ForwardingServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void Layer3ForwardingServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	Layer3ForwardingServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string Layer3ForwardingServerHelper::registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return Layer3ForwardingServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string Layer3ForwardingServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::Layer3ForwardingRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return Layer3ForwardingServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void Layer3ForwardingServerHelper::unregisterObject(const std::string& uri)
{
	Layer3ForwardingServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace InternetGateway1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::InternetGateway1, Layer3Forwarding)


#endif // InternetGateway1_Layer3ForwardingServerHelper_INCLUDED

