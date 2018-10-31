//
// WANPPPConnectionServerHelper.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPPPConnectionServerHelper
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


#ifndef InternetGateway1_WANPPPConnectionServerHelper_INCLUDED
#define InternetGateway1_WANPPPConnectionServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/InternetGateway1/IWANPPPConnection.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANPPPConnection.h"
#include "UPnPS/InternetGateway1/WANPPPConnectionRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANPPPConnectionServerHelper
{
public:
	typedef UPnPS::InternetGateway1::WANPPPConnection Service;

	WANPPPConnectionServerHelper();
		/// Creates a WANPPPConnectionServerHelper.

	~WANPPPConnectionServerHelper();
		/// Destroys the WANPPPConnectionServerHelper.

	static Poco::AutoPtr<UPnPS::InternetGateway1::WANPPPConnectionRemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::InternetGateway1::WANPPPConnection instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::InternetGateway1::WANPPPConnection instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::WANPPPConnectionRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::InternetGateway1::WANPPPConnection from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::InternetGateway1::WANPPPConnectionRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static WANPPPConnectionServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANPPPConnectionRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::InternetGateway1::WANPPPConnectionRemoteObject> WANPPPConnectionServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return WANPPPConnectionServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void WANPPPConnectionServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	WANPPPConnectionServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string WANPPPConnectionServerHelper::registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANPPPConnection> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return WANPPPConnectionServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string WANPPPConnectionServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::WANPPPConnectionRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return WANPPPConnectionServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void WANPPPConnectionServerHelper::unregisterObject(const std::string& uri)
{
	WANPPPConnectionServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace InternetGateway1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::InternetGateway1, WANPPPConnection)


#endif // InternetGateway1_WANPPPConnectionServerHelper_INCLUDED

