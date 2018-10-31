//
// ConnectionManager1Proxy.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1Proxy
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


#ifndef MediaServer1_ConnectionManager1Proxy_INCLUDED
#define MediaServer1_ConnectionManager1Proxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/MediaServer1/IConnectionManager1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ConnectionManager1Proxy: public UPnPS::MediaServer1::IConnectionManager1, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<ConnectionManager1Proxy> Ptr;

	ConnectionManager1Proxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a ConnectionManager1Proxy.

	virtual ~ConnectionManager1Proxy();
		/// Destroys the ConnectionManager1Proxy.

	virtual void connectionComplete(Poco::Int32 connectionID);

	virtual void getCurrentConnectionIDs(std::string& connectionIDs);

	virtual void getCurrentConnectionInfo(Poco::Int32 connectionID, Poco::Int32& rcsID, Poco::Int32& aVTransportID, std::string& protocolInfo, std::string& peerConnectionManager, Poco::Int32& peerConnectionID, std::string& direction, std::string& status);

	virtual void getProtocolInfo(std::string& source, std::string& sink);

	virtual void prepareForConnection(const std::string& remoteProtocolInfo, const std::string& peerConnectionManager, Poco::Int32 peerConnectionID, const std::string& direction, Poco::Int32& connectionID, Poco::Int32& aVTransportID, Poco::Int32& rcsID);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ConnectionManager1Proxy::remoting__typeId() const
{
	return IConnectionManager1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ConnectionManager1Proxy_INCLUDED

