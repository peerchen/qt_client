//
// DimmingServerHelper.h
//
// Library: LightingControls1
// Package: Generated
// Module:  DimmingServerHelper
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


#ifndef LightingControls1_DimmingServerHelper_INCLUDED
#define LightingControls1_DimmingServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/LightingControls1/Dimming.h"
#include "UPnPS/LightingControls1/DimmingRemoteObject.h"
#include "UPnPS/LightingControls1/IDimming.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API DimmingServerHelper
{
public:
	typedef UPnPS::LightingControls1::Dimming Service;

	DimmingServerHelper();
		/// Creates a DimmingServerHelper.

	~DimmingServerHelper();
		/// Destroys the DimmingServerHelper.

	static Poco::AutoPtr<UPnPS::LightingControls1::DimmingRemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::LightingControls1::Dimming> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::LightingControls1::Dimming instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<UPnPS::LightingControls1::Dimming> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::LightingControls1::Dimming instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::LightingControls1::DimmingRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::LightingControls1::Dimming from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::LightingControls1::DimmingRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::LightingControls1::Dimming> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static DimmingServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::LightingControls1::DimmingRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::LightingControls1::DimmingRemoteObject> DimmingServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::LightingControls1::Dimming> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return DimmingServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void DimmingServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	DimmingServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string DimmingServerHelper::registerObject(Poco::SharedPtr<UPnPS::LightingControls1::Dimming> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return DimmingServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string DimmingServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::LightingControls1::DimmingRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return DimmingServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void DimmingServerHelper::unregisterObject(const std::string& uri)
{
	DimmingServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace LightingControls1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::LightingControls1, Dimming)


#endif // LightingControls1_DimmingServerHelper_INCLUDED

