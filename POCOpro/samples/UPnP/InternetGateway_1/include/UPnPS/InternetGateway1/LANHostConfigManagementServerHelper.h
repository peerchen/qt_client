//
// LANHostConfigManagementServerHelper.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  LANHostConfigManagementServerHelper
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


#ifndef InternetGateway1_LANHostConfigManagementServerHelper_INCLUDED
#define InternetGateway1_LANHostConfigManagementServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/InternetGateway1/ILANHostConfigManagement.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/LANHostConfigManagement.h"
#include "UPnPS/InternetGateway1/LANHostConfigManagementRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API LANHostConfigManagementServerHelper
{
public:
	typedef UPnPS::InternetGateway1::LANHostConfigManagement Service;

	LANHostConfigManagementServerHelper();
		/// Creates a LANHostConfigManagementServerHelper.

	~LANHostConfigManagementServerHelper();
		/// Destroys the LANHostConfigManagementServerHelper.

	static Poco::AutoPtr<UPnPS::InternetGateway1::LANHostConfigManagementRemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::InternetGateway1::LANHostConfigManagement instance.

	static std::string registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::InternetGateway1::LANHostConfigManagement instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::LANHostConfigManagementRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::InternetGateway1::LANHostConfigManagement from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::InternetGateway1::LANHostConfigManagementRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static LANHostConfigManagementServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::LANHostConfigManagementRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::InternetGateway1::LANHostConfigManagementRemoteObject> LANHostConfigManagementServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return LANHostConfigManagementServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string LANHostConfigManagementServerHelper::registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::LANHostConfigManagement> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return LANHostConfigManagementServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string LANHostConfigManagementServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::LANHostConfigManagementRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return LANHostConfigManagementServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void LANHostConfigManagementServerHelper::unregisterObject(const std::string& uri)
{
	LANHostConfigManagementServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace InternetGateway1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::InternetGateway1, LANHostConfigManagement)


#endif // InternetGateway1_LANHostConfigManagementServerHelper_INCLUDED

