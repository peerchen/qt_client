//
// AVTransport1ServerHelper.h
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1ServerHelper
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


#ifndef MediaServer1_AVTransport1ServerHelper_INCLUDED
#define MediaServer1_AVTransport1ServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/MediaServer1/AVTransport1.h"
#include "UPnPS/MediaServer1/AVTransport1RemoteObject.h"
#include "UPnPS/MediaServer1/IAVTransport1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API AVTransport1ServerHelper
{
public:
	typedef UPnPS::MediaServer1::AVTransport1 Service;

	AVTransport1ServerHelper();
		/// Creates a AVTransport1ServerHelper.

	~AVTransport1ServerHelper();
		/// Destroys the AVTransport1ServerHelper.

	static Poco::AutoPtr<UPnPS::MediaServer1::AVTransport1RemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::MediaServer1::AVTransport1 instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::MediaServer1::AVTransport1 instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::MediaServer1::AVTransport1RemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::MediaServer1::AVTransport1 from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::MediaServer1::AVTransport1RemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static AVTransport1ServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::MediaServer1::AVTransport1RemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::MediaServer1::AVTransport1RemoteObject> AVTransport1ServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return AVTransport1ServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void AVTransport1ServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	AVTransport1ServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string AVTransport1ServerHelper::registerObject(Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return AVTransport1ServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string AVTransport1ServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::MediaServer1::AVTransport1RemoteObject> pRemoteObject, const std::string& listenerId)
{
	return AVTransport1ServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void AVTransport1ServerHelper::unregisterObject(const std::string& uri)
{
	AVTransport1ServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace MediaServer1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::MediaServer1, AVTransport1)


#endif // MediaServer1_AVTransport1ServerHelper_INCLUDED

