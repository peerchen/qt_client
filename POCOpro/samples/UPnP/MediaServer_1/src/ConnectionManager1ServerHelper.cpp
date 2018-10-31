//
// ConnectionManager1ServerHelper.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1ServerHelper
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


#include "UPnPS/MediaServer1/ConnectionManager1ServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/MediaServer1/ConnectionManager1EventDispatcher.h"
#include "UPnPS/MediaServer1/ConnectionManager1Skeleton.h"


namespace UPnPS {
namespace MediaServer1 {


namespace
{
	static Poco::SingletonHolder<ConnectionManager1ServerHelper> shConnectionManager1ServerHelper;
}


ConnectionManager1ServerHelper::ConnectionManager1ServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


ConnectionManager1ServerHelper::~ConnectionManager1ServerHelper()
{
}


void ConnectionManager1ServerHelper::shutdown()
{
	ConnectionManager1ServerHelper::instance().unregisterSkeleton();
	shConnectionManager1ServerHelper.reset();
}


Poco::AutoPtr<UPnPS::MediaServer1::ConnectionManager1RemoteObject> ConnectionManager1ServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::MediaServer1::ConnectionManager1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new ConnectionManager1RemoteObject(oid, pServiceObject);
}


void ConnectionManager1ServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<ConnectionManager1RemoteObject> pRemoteObject = pIdentifiable.cast<ConnectionManager1RemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


ConnectionManager1ServerHelper& ConnectionManager1ServerHelper::instance()
{
	return *shConnectionManager1ServerHelper.get();
}


std::string ConnectionManager1ServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::MediaServer1::ConnectionManager1RemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void ConnectionManager1ServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.MediaServer1.ConnectionManager1", new ConnectionManager1Skeleton);
}


void ConnectionManager1ServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void ConnectionManager1ServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.MediaServer1.ConnectionManager1", true);
}


} // namespace MediaServer1
} // namespace UPnPS

