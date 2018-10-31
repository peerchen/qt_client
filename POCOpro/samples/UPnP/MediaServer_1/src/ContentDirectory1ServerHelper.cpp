//
// ContentDirectory1ServerHelper.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1ServerHelper
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


#include "UPnPS/MediaServer1/ContentDirectory1ServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/MediaServer1/ContentDirectory1EventDispatcher.h"
#include "UPnPS/MediaServer1/ContentDirectory1Skeleton.h"


namespace UPnPS {
namespace MediaServer1 {


namespace
{
	static Poco::SingletonHolder<ContentDirectory1ServerHelper> shContentDirectory1ServerHelper;
}


ContentDirectory1ServerHelper::ContentDirectory1ServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


ContentDirectory1ServerHelper::~ContentDirectory1ServerHelper()
{
}


void ContentDirectory1ServerHelper::shutdown()
{
	ContentDirectory1ServerHelper::instance().unregisterSkeleton();
	shContentDirectory1ServerHelper.reset();
}


Poco::AutoPtr<UPnPS::MediaServer1::ContentDirectory1RemoteObject> ContentDirectory1ServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::MediaServer1::ContentDirectory1> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new ContentDirectory1RemoteObject(oid, pServiceObject);
}


void ContentDirectory1ServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<ContentDirectory1RemoteObject> pRemoteObject = pIdentifiable.cast<ContentDirectory1RemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


ContentDirectory1ServerHelper& ContentDirectory1ServerHelper::instance()
{
	return *shContentDirectory1ServerHelper.get();
}


std::string ContentDirectory1ServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::MediaServer1::ContentDirectory1RemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void ContentDirectory1ServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.MediaServer1.ContentDirectory1", new ContentDirectory1Skeleton);
}


void ContentDirectory1ServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void ContentDirectory1ServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.MediaServer1.ContentDirectory1", true);
}


} // namespace MediaServer1
} // namespace UPnPS

