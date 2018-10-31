//
// Layer3ForwardingServerHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingServerHelper
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


#include "UPnPS/InternetGateway1/Layer3ForwardingServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/Layer3ForwardingEventDispatcher.h"
#include "UPnPS/InternetGateway1/Layer3ForwardingSkeleton.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<Layer3ForwardingServerHelper> shLayer3ForwardingServerHelper;
}


Layer3ForwardingServerHelper::Layer3ForwardingServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


Layer3ForwardingServerHelper::~Layer3ForwardingServerHelper()
{
}


void Layer3ForwardingServerHelper::shutdown()
{
	Layer3ForwardingServerHelper::instance().unregisterSkeleton();
	shLayer3ForwardingServerHelper.reset();
}


Poco::AutoPtr<UPnPS::InternetGateway1::Layer3ForwardingRemoteObject> Layer3ForwardingServerHelper::createRemoteObjectImpl(Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new Layer3ForwardingRemoteObject(oid, pServiceObject);
}


void Layer3ForwardingServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<Layer3ForwardingRemoteObject> pRemoteObject = pIdentifiable.cast<Layer3ForwardingRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


Layer3ForwardingServerHelper& Layer3ForwardingServerHelper::instance()
{
	return *shLayer3ForwardingServerHelper.get();
}


std::string Layer3ForwardingServerHelper::registerObjectImpl(Poco::AutoPtr<UPnPS::InternetGateway1::Layer3ForwardingRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void Layer3ForwardingServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("UPnPS.InternetGateway1.Layer3Forwarding", new Layer3ForwardingSkeleton);
}


void Layer3ForwardingServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void Layer3ForwardingServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("UPnPS.InternetGateway1.Layer3Forwarding", true);
}


} // namespace InternetGateway1
} // namespace UPnPS

