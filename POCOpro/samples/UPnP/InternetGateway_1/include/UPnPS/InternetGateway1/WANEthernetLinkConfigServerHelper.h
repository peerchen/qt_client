//
// WANEthernetLinkConfigServerHelper.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANEthernetLinkConfigServerHelper
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


#ifndef InternetGateway1_WANEthernetLinkConfigServerHelper_INCLUDED
#define InternetGateway1_WANEthernetLinkConfigServerHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include "UPnPS/InternetGateway1/IWANEthernetLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANEthernetLinkConfig.h"
#include "UPnPS/InternetGateway1/WANEthernetLinkConfigRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANEthernetLinkConfigServerHelper
{
public:
	typedef UPnPS::InternetGateway1::WANEthernetLinkConfig Service;

	WANEthernetLinkConfigServerHelper();
		/// Creates a WANEthernetLinkConfigServerHelper.

	~WANEthernetLinkConfigServerHelper();
		/// Destroys the WANEthernetLinkConfigServerHelper.

	static Poco::AutoPtr<UPnPS::InternetGateway1::WANEthernetLinkConfigRemoteObject> createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given UPnPS::InternetGateway1::WANEthernetLinkConfig instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given UPnPS::InternetGateway1::WANEthernetLinkConfig instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::WANEthernetLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for UPnPS::InternetGateway1::WANEthernetLinkConfig from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<UPnPS::InternetGateway1::WANEthernetLinkConfigRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static WANEthernetLinkConfigServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::WANEthernetLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<UPnPS::InternetGateway1::WANEthernetLinkConfigRemoteObject> WANEthernetLinkConfigServerHelper::createRemoteObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return WANEthernetLinkConfigServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void WANEthernetLinkConfigServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	WANEthernetLinkConfigServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string WANEthernetLinkConfigServerHelper::registerObject(Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return WANEthernetLinkConfigServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string WANEthernetLinkConfigServerHelper::registerRemoteObject(Poco::AutoPtr<UPnPS::InternetGateway1::WANEthernetLinkConfigRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return WANEthernetLinkConfigServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void WANEthernetLinkConfigServerHelper::unregisterObject(const std::string& uri)
{
	WANEthernetLinkConfigServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace InternetGateway1
} // namespace UPnPS


REMOTING_SPECIALIZE_SERVER_HELPER(UPnPS::InternetGateway1, WANEthernetLinkConfig)


#endif // InternetGateway1_WANEthernetLinkConfigServerHelper_INCLUDED

