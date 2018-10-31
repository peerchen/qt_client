//
// Layer3ForwardingClientHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingClientHelper
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


#include "UPnPS/InternetGateway1/Layer3ForwardingClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/Layer3ForwardingProxyFactory.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<Layer3ForwardingClientHelper> shLayer3ForwardingClientHelper;
}


Layer3ForwardingClientHelper::Layer3ForwardingClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.InternetGateway1.Layer3Forwarding", new Layer3ForwardingProxyFactory);
}


Layer3ForwardingClientHelper::~Layer3ForwardingClientHelper()
{
}


ILayer3Forwarding::Ptr Layer3ForwardingClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<ILayer3Forwarding>();
}


ILayer3Forwarding::Ptr Layer3ForwardingClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, ILayer3Forwarding::remoting__typeId(), protocol);
	return pInterface.cast<ILayer3Forwarding>();
}


Layer3ForwardingClientHelper& Layer3ForwardingClientHelper::instance()
{
	return *shLayer3ForwardingClientHelper.get();
}


} // namespace InternetGateway1
} // namespace UPnPS

