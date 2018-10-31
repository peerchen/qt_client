//
// ConnectionManager1ServerHelper.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1ServerHelper
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


#ifndef MediaServer1_ConnectionManager1ServerHelper_INCLUDED
#define MediaServer1_ConnectionManager1ServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/MediaServer1/ConnectionManager1.h"
#include "UPnPS/MediaServer1/ConnectionManager1RemoteObject.h"
#include "UPnPS/MediaServer1/IConnectionManager1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ConnectionManager1ServerHelper
{
public:
	typedef UPnPS::MediaServer1::ConnectionManager1 Service;

	ConnectionManager1ServerHelper();
		/// Creates a ConnectionManager1ServerHelper.

	~ConnectionManager1ServerHelper();
		/// Destroys the ConnectionManager1ServerHelper.

	static Poco::AutoPtr<UPnPS::MediaServer1::ConnectionManager1RemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::MediaServer1::ConnectionManager1 instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::MediaServer1::ConnectionManager1 instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::MediaServer1::ConnectionManager1RemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::MediaServer1::ConnectionManager1 from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::MediaServer1::ConnectionManager1RemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static ConnectionManager1ServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::MediaServer1::ConnectionManager1RemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::MediaServer1::ConnectionManager1RemoteObject> ConnectionManager1ServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return ConnectionManager1ServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void ConnectionManager1ServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	ConnectionManager1ServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string ConnectionManager1ServerHelper::registerObject(Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return ConnectionManager1ServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string ConnectionManager1ServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::MediaServer1::ConnectionManager1RemoteObject> pRemoteObject, const std::string& listenerId)
{
	return ConnectionManager1ServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void ConnectionManager1ServerHelper::unregisterObject(const std::string& uri)
{
	ConnectionManager1ServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace MediaServer1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::MediaServer1, ConnectionManager1)


#endif // MediaServer1_ConnectionManager1ServerHelper_INCLUDED

