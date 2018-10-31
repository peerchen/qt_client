//
// ConnectionManager1.h
//
// Library: MediaServer1
// Package: MediaServer1
// Module:  ConnectionManager1
//
// This file has been generated on 2012-10-29 11:42:20 UTC.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef MediaServer1_ConnectionManager1_INCLUDED
#define MediaServer1_ConnectionManager1_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


//@ namespace="urn:schemas-upnp-org:service:ConnectionManager:1"
//@ remote
class MediaServer1_API ConnectionManager1
{
public:
	typedef Poco::SharedPtr<ConnectionManager1> Ptr;

	ConnectionManager1();
		/// Creates a ConnectionManager1.

	virtual ~ConnectionManager1();
		/// Destroys the ConnectionManager1.

	//@ $connectionID={name="ConnectionID"}
	//@ name=ConnectionComplete
	//@ optional=true
	//@ replyName=ConnectionCompleteResponse
	virtual void connectionComplete(Poco::Int32 connectionID) = 0;

	//@ $connectionIDs={name="ConnectionIDs", direction=out}
	//@ name=GetCurrentConnectionIDs
	//@ replyName=GetCurrentConnectionIDsResponse
	virtual void getCurrentConnectionIDs(std::string& connectionIDs) = 0;

	//@ $aVTransportID={name="AVTransportID", direction=out}
	//@ $connectionID={name="ConnectionID"}
	//@ $direction={name="Direction", direction=out}
	//@ $peerConnectionID={name="PeerConnectionID", direction=out}
	//@ $peerConnectionManager={name="PeerConnectionManager", direction=out}
	//@ $protocolInfo={name="ProtocolInfo", direction=out}
	//@ $rcsID={name="RcsID", direction=out}
	//@ $status={name="Status", direction=out}
	//@ name=GetCurrentConnectionInfo
	//@ replyName=GetCurrentConnectionInfoResponse
	virtual void getCurrentConnectionInfo(Poco::Int32 connectionID, Poco::Int32& rcsID, Poco::Int32& aVTransportID, std::string& protocolInfo, std::string& peerConnectionManager, Poco::Int32& peerConnectionID, std::string& direction, std::string& status) = 0;

	//@ $sink={name="Sink", direction=out}
	//@ $source={name="Source", direction=out}
	//@ name=GetProtocolInfo
	//@ replyName=GetProtocolInfoResponse
	virtual void getProtocolInfo(std::string& source, std::string& sink) = 0;

	//@ $aVTransportID={name="AVTransportID", direction=out}
	//@ $connectionID={name="ConnectionID", direction=out}
	//@ $direction={name="Direction"}
	//@ $peerConnectionID={name="PeerConnectionID"}
	//@ $peerConnectionManager={name="PeerConnectionManager"}
	//@ $rcsID={name="RcsID", direction=out}
	//@ $remoteProtocolInfo={name="RemoteProtocolInfo"}
	//@ name=PrepareForConnection
	//@ optional=true
	//@ replyName=PrepareForConnectionResponse
	virtual void prepareForConnection(const std::string& remoteProtocolInfo, const std::string& peerConnectionManager, Poco::Int32 peerConnectionID, const std::string& direction, Poco::Int32& connectionID, Poco::Int32& aVTransportID, Poco::Int32& rcsID) = 0;

	//@ name=CurrentConnectionIDs
	//@ oneway=true
	Poco::BasicEvent<const std::string> currentConnectionIDsChanged;
	//@ name=SinkProtocolInfo
	//@ oneway=true
	Poco::BasicEvent<const std::string> sinkProtocolInfoChanged;
	//@ name=SourceProtocolInfo
	//@ oneway=true
	Poco::BasicEvent<const std::string> sourceProtocolInfoChanged;
};


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ConnectionManager1_INCLUDED

