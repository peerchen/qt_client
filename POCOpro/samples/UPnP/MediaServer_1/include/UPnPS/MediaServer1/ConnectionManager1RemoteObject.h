//
// ConnectionManager1RemoteObject.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1RemoteObject
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


#ifndef MediaServer1_ConnectionManager1RemoteObject_INCLUDED
#define MediaServer1_ConnectionManager1RemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/MediaServer1/IConnectionManager1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ConnectionManager1RemoteObject: public UPnPS::MediaServer1::IConnectionManager1, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<ConnectionManager1RemoteObject> Ptr;

	ConnectionManager1RemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> pServiceObject);
		/// Creates a ConnectionManager1RemoteObject.

	virtual ~ConnectionManager1RemoteObject();
		/// Destroys the ConnectionManager1RemoteObject.

	virtual void connectionComplete(Poco::Int32 connectionID);

	virtual void getCurrentConnectionIDs(std::string& connectionIDs);

	virtual void getCurrentConnectionInfo(Poco::Int32 connectionID, Poco::Int32& rcsID, Poco::Int32& aVTransportID, std::string& protocolInfo, std::string& peerConnectionManager, Poco::Int32& peerConnectionID, std::string& direction, std::string& status);

	virtual void getProtocolInfo(std::string& source, std::string& sink);

	virtual void prepareForConnection(const std::string& remoteProtocolInfo, const std::string& peerConnectionManager, Poco::Int32 peerConnectionID, const std::string& direction, Poco::Int32& connectionID, Poco::Int32& aVTransportID, Poco::Int32& rcsID);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

protected:
	void event__currentConnectionIDsChanged(const std::string& data);

	void event__sinkProtocolInfoChanged(const std::string& data);

	void event__sourceProtocolInfoChanged(const std::string& data);

private:
	Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> _pServiceObject;
};


inline void ConnectionManager1RemoteObject::connectionComplete(Poco::Int32 connectionID)
{
	_pServiceObject->connectionComplete(connectionID);
}


inline void ConnectionManager1RemoteObject::getCurrentConnectionIDs(std::string& connectionIDs)
{
	_pServiceObject->getCurrentConnectionIDs(connectionIDs);
}


inline void ConnectionManager1RemoteObject::getCurrentConnectionInfo(Poco::Int32 connectionID, Poco::Int32& rcsID, Poco::Int32& aVTransportID, std::string& protocolInfo, std::string& peerConnectionManager, Poco::Int32& peerConnectionID, std::string& direction, std::string& status)
{
	_pServiceObject->getCurrentConnectionInfo(connectionID, rcsID, aVTransportID, protocolInfo, peerConnectionManager, peerConnectionID, direction, status);
}


inline void ConnectionManager1RemoteObject::getProtocolInfo(std::string& source, std::string& sink)
{
	_pServiceObject->getProtocolInfo(source, sink);
}


inline void ConnectionManager1RemoteObject::prepareForConnection(const std::string& remoteProtocolInfo, const std::string& peerConnectionManager, Poco::Int32 peerConnectionID, const std::string& direction, Poco::Int32& connectionID, Poco::Int32& aVTransportID, Poco::Int32& rcsID)
{
	_pServiceObject->prepareForConnection(remoteProtocolInfo, peerConnectionManager, peerConnectionID, direction, connectionID, aVTransportID, rcsID);
}


inline const Poco::RemotingNG::Identifiable::TypeId& ConnectionManager1RemoteObject::remoting__typeId() const
{
	return IConnectionManager1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ConnectionManager1RemoteObject_INCLUDED

