//
// IConnectionManager1.h
//
// Library: MediaServer1
// Package: Generated
// Module:  IConnectionManager1
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


#ifndef MediaServer1_IConnectionManager1_INCLUDED
#define MediaServer1_IConnectionManager1_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/MediaServer1/ConnectionManager1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API IConnectionManager1: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IConnectionManager1> Ptr;

	IConnectionManager1();
		/// Creates a IConnectionManager1.

	virtual ~IConnectionManager1();
		/// Destroys the IConnectionManager1.

	virtual void connectionComplete(Poco::Int32 connectionID) = 0;

	virtual void getCurrentConnectionIDs(std::string& connectionIDs) = 0;

	virtual void getCurrentConnectionInfo(Poco::Int32 connectionID, Poco::Int32& rcsID, Poco::Int32& aVTransportID, std::string& protocolInfo, std::string& peerConnectionManager, Poco::Int32& peerConnectionID, std::string& direction, std::string& status) = 0;

	virtual void getProtocolInfo(std::string& source, std::string& sink) = 0;

	virtual void prepareForConnection(const std::string& remoteProtocolInfo, const std::string& peerConnectionManager, Poco::Int32 peerConnectionID, const std::string& direction, Poco::Int32& connectionID, Poco::Int32& aVTransportID, Poco::Int32& rcsID) = 0;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	Poco::BasicEvent < const std::string > currentConnectionIDsChanged;
	Poco::BasicEvent < const std::string > sinkProtocolInfoChanged;
	Poco::BasicEvent < const std::string > sourceProtocolInfoChanged;
};


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_IConnectionManager1_INCLUDED

