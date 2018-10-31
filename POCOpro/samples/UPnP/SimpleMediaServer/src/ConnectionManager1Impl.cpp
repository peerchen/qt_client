//
// ConnectionManager1Impl.cpp
//
// $Id: //poco/1.7/UPnP/samples/SimpleMediaServer/src/ConnectionManager1Impl.cpp#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#include "ConnectionManager1Impl.h"


ConnectionManager1Impl::ConnectionManager1Impl():
	_logger(Poco::Logger::get("ConnectionManager1Impl"))
{
}


ConnectionManager1Impl::~ConnectionManager1Impl()
{
}


void ConnectionManager1Impl::connectionComplete(Poco::Int32 connectionID)
{
	_logger.debug("Entering UPnPS::MediaServer1::ConnectionManager1Impl::connectionComplete()");
}


void ConnectionManager1Impl::getCurrentConnectionIDs(std::string& connectionIDs)
{
	_logger.debug("Entering UPnPS::MediaServer1::ConnectionManager1Impl::getCurrentConnectionIDs()");
	
	connectionIDs.clear();
}


void ConnectionManager1Impl::getCurrentConnectionInfo(Poco::Int32 connectionID, Poco::Int32& rcsID, Poco::Int32& aVTransportID, std::string& protocolInfo, std::string& peerConnectionManager, Poco::Int32& peerConnectionID, std::string& direction, std::string& status)
{
	_logger.debug("Entering UPnPS::MediaServer1::ConnectionManager1Impl::getCurrentConnectionInfo()");
	
	rcsID                 = -1;
	aVTransportID         = -1;
	protocolInfo          = "http-get:*:*:*";
	peerConnectionManager = "";
	peerConnectionID      = -1;
	direction             = "Output";
	status                = "OK";
}


void ConnectionManager1Impl::getProtocolInfo(std::string& source, std::string& sink)
{
	_logger.debug("Entering UPnPS::MediaServer1::ConnectionManager1Impl::getProtocolInfo()");
	
	source = "http-get:*:*:*";
	sink   = "";
}


void ConnectionManager1Impl::prepareForConnection(const std::string& remoteProtocolInfo, const std::string& peerConnectionManager, Poco::Int32 peerConnectionID, const std::string& direction, Poco::Int32& connectionID, Poco::Int32& aVTransportID, Poco::Int32& rcsID)
{
	_logger.debug("Entering UPnPS::MediaServer1::ConnectionManager1Impl::prepareForConnection()");
	
	connectionID = 0;
	aVTransportID = -1;
	rcsID = -1;
}


Poco::UPnP::GENA::StateProvider::StateVec ConnectionManager1Impl::currentState() const
{
	Poco::UPnP::GENA::StateProvider::StateVec result;
	result.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair("CurrentConnectionIDs", ""));
	result.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair("SinkProtocolInfo", ""));
	result.push_back(Poco::UPnP::GENA::StateProvider::NameValuePair("SourceProtocolInfo", "http-get:*:*:*"));
	return result;
}
