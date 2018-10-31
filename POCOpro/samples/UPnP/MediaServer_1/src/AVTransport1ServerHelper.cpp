//
// AVTransport1ServerHelper.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1ServerHelper
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


#include "UPnPS/MediaServer1/AVTransport1ServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/MediaServer1/AVTransport1EventDispatcher.h"
#include "UPnPS/MediaServer1/AVTransport1Skeleton.h"


namespace UPnPS {
namespace MediaServer1 {


namespace
{
	static Poco::SingletonHolder<AVTransport1ServerHelper> shAVTransport1ServerHelper;
}


AVTransport1ServerHelper::AVTransport1ServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


AVTransport1ServerHelper::~AVTransport1ServerHelper()
{
}


void AVTransport1ServerHelper::shutdown()
{
	AVTransport1ServerHelper::instance().unregisterSkeleton();
	shAVTransport1ServerHelper.reset();
}


Poco::AutoPtr<UPnPS::MediaServer1::AVTransport1RemoteObject> AVTransport1ServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::MediaServer1::AVTransport1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new AVTransport1RemoteObject(oid, pServiceObject);
}


void AVTransport1ServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<AVTransport1RemoteObject> pRemoteObject = pIdentifiable.cast<AVTransport1RemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


AVTransport1ServerHelper& AVTransport1ServerHelper::instance()
{
	return *shAVTransport1ServerHelper.get();
}


std::string AVTransport1ServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::MediaServer1::AVTransport1RemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void AVTransport1ServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.MediaServer1.AVTransport1", new AVTransport1Skeleton);
}


void AVTransport1ServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void AVTransport1ServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.MediaServer1.AVTransport1", true);
}


} // namespace MediaServer1
} // namespace UPnPS

