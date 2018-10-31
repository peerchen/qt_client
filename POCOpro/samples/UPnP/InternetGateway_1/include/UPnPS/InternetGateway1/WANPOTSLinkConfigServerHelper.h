//
// WANPOTSLinkConfigServerHelper.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPOTSLinkConfigServerHelper
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


#ifndef InternetGateway1_WANPOTSLinkConfigServerHelper_INCLUDED
#define InternetGateway1_WANPOTSLinkConfigServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/InternetGateway1/IWANPOTSLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANPOTSLinkConfig.h"
#include "UPnPS/InternetGateway1/WANPOTSLinkConfigRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANPOTSLinkConfigServerHelper
{
public:
	typedef UPnPS::InternetGateway1::WANPOTSLinkConfig Service;

	WANPOTSLinkConfigServerHelper();
		/// Creates a WANPOTSLinkConfigServerHelper.

	~WANPOTSLinkConfigServerHelper();
		/// Destroys the WANPOTSLinkConfigServerHelper.

	static Poco::AutoPtr<UPnPS::InternetGateway1::WANPOTSLinkConfigRemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::InternetGateway1::WANPOTSLinkConfig instance.

	static std::string registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::InternetGateway1::WANPOTSLinkConfig instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::WANPOTSLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::InternetGateway1::WANPOTSLinkConfig from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::InternetGateway1::WANPOTSLinkConfigRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	static WANPOTSLinkConfigServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANPOTSLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::InternetGateway1::WANPOTSLinkConfigRemoteObject> WANPOTSLinkConfigServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return WANPOTSLinkConfigServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline std::string WANPOTSLinkConfigServerHelper::registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANPOTSLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return WANPOTSLinkConfigServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string WANPOTSLinkConfigServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::WANPOTSLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return WANPOTSLinkConfigServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void WANPOTSLinkConfigServerHelper::unregisterObject(const std::string& uri)
{
	WANPOTSLinkConfigServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace InternetGateway1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::InternetGateway1, WANPOTSLinkConfig)


#endif // InternetGateway1_WANPOTSLinkConfigServerHelper_INCLUDED

