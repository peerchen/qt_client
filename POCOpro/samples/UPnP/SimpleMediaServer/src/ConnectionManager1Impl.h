//
// ConnectionManager1Impl.h
//
// $Id: //poco/1.7/UPnP/samples/SimpleMediaServer/src/ConnectionManager1Impl.h#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef MediaServer1_ConnectionManager1Impl_INCLUDED
#define MediaServer1_ConnectionManager1Impl_INCLUDED


#include "UPnPS/MediaServer1/ConnectionManager1.h"
#include "Poco/UPnP/GENA/StateProvider.h"
#include "Poco/Logger.h"


class ConnectionManager1Impl: public UPnPS::MediaServer1::ConnectionManager1, public Poco::UPnP::GENA::StateProvider
{
public:
	ConnectionManager1Impl();
		/// Creates a ConnectionManager1Impl.

	virtual ~ConnectionManager1Impl();
		/// Destroys the ConnectionManager1Impl.

	// ConnectionManager1
	void connectionComplete(Poco::Int32 connectionID);
	void getCurrentConnectionIDs(std::string& connectionIDs);
	void getCurrentConnectionInfo(Poco::Int32 connectionID, Poco::Int32& rcsID, Poco::Int32& aVTransportID, std::string& protocolInfo, std::string& peerConnectionManager, Poco::Int32& peerConnectionID, std::string& direction, std::string& status);
	void getProtocolInfo(std::string& source, std::string& sink);
	void prepareForConnection(const std::string& remoteProtocolInfo, const std::string& peerConnectionManager, Poco::Int32 peerConnectionID, const std::string& direction, Poco::Int32& connectionID, Poco::Int32& aVTransportID, Poco::Int32& rcsID);

	// StateProvider
	Poco::UPnP::GENA::StateProvider::StateVec currentState() const;

private:
	Poco::Logger& _logger;
};


#endif // MediaServer1_ConnectionManager1Impl_INCLUDED
