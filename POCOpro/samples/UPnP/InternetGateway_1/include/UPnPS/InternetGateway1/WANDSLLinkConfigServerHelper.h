//
// WANDSLLinkConfigServerHelper.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigServerHelper
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


#ifndef InternetGateway1_WANDSLLinkConfigServerHelper_INCLUDED
#define InternetGateway1_WANDSLLinkConfigServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/InternetGateway1/IWANDSLLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfig.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfigRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANDSLLinkConfigServerHelper
{
public:
	typedef UPnPS::InternetGateway1::WANDSLLinkConfig Service;

	WANDSLLinkConfigServerHelper();
		/// Creates a WANDSLLinkConfigServerHelper.

	~WANDSLLinkConfigServerHelper();
		/// Destroys the WANDSLLinkConfigServerHelper.

	static Poco::AutoPtr<UPnPS::InternetGateway1::WANDSLLinkConfigRemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::InternetGateway1::WANDSLLinkConfig instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::InternetGateway1::WANDSLLinkConfig instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::WANDSLLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::InternetGateway1::WANDSLLinkConfig from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::InternetGateway1::WANDSLLinkConfigRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static WANDSLLinkConfigServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANDSLLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::InternetGateway1::WANDSLLinkConfigRemoteObject> WANDSLLinkConfigServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return WANDSLLinkConfigServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void WANDSLLinkConfigServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	WANDSLLinkConfigServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string WANDSLLinkConfigServerHelper::registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return WANDSLLinkConfigServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string WANDSLLinkConfigServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::WANDSLLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return WANDSLLinkConfigServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void WANDSLLinkConfigServerHelper::unregisterObject(const std::string& uri)
{
	WANDSLLinkConfigServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace InternetGateway1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::InternetGateway1, WANDSLLinkConfig)


#endif // InternetGateway1_WANDSLLinkConfigServerHelper_INCLUDED

