//
// SwitchPowerServerHelper.h
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerServerHelper
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


#ifndef LightingControls1_SwitchPowerServerHelper_INCLUDED
#define LightingControls1_SwitchPowerServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/LightingControls1/ISwitchPower.h"
#include "UPnPS/LightingControls1/LightingControls1.h"
#include "UPnPS/LightingControls1/SwitchPower.h"
#include "UPnPS/LightingControls1/SwitchPowerRemoteObject.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API SwitchPowerServerHelper
{
public:
	typedef UPnPS::LightingControls1::SwitchPower Service;

	SwitchPowerServerHelper();
		/// Creates a SwitchPowerServerHelper.

	~SwitchPowerServerHelper();
		/// Destroys the SwitchPowerServerHelper.

	static Poco::AutoPtr<UPnPS::LightingControls1::SwitchPowerRemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::LightingControls1::SwitchPower instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::LightingControls1::SwitchPower instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::LightingControls1::SwitchPowerRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::LightingControls1::SwitchPower from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::LightingControls1::SwitchPowerRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static SwitchPowerServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::LightingControls1::SwitchPowerRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::LightingControls1::SwitchPowerRemoteObject> SwitchPowerServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return SwitchPowerServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void SwitchPowerServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	SwitchPowerServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string SwitchPowerServerHelper::registerObject(Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return SwitchPowerServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string SwitchPowerServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::LightingControls1::SwitchPowerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return SwitchPowerServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void SwitchPowerServerHelper::unregisterObject(const std::string& uri)
{
	SwitchPowerServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace LightingControls1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::LightingControls1, SwitchPower)


#endif // LightingControls1_SwitchPowerServerHelper_INCLUDED

