//
// AVTransport1ClientHelper.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1ClientHelper
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


#include "UPnPS/MediaServer1/AVTransport1ClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/MediaServer1/AVTransport1ProxyFactory.h"


namespace UPnPS {
namespace MediaServer1 {


namespace
{
	static Poco::SingletonHolder<AVTransport1ClientHelper> shAVTransport1ClientHelper;
}


AVTransport1ClientHelper::AVTransport1ClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.MediaServer1.AVTransport1", new AVTransport1ProxyFactory);
}


AVTransport1ClientHelper::~AVTransport1ClientHelper()
{
}


IAVTransport1::Ptr AVTransport1ClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IAVTransport1>();
}


IAVTransport1::Ptr AVTransport1ClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IAVTransport1::remoting__typeId(), protocol);
	return pInterface.cast<IAVTransport1>();
}


AVTransport1ClientHelper& AVTransport1ClientHelper::instance()
{
	return *shAVTransport1ClientHelper.get();
}


} // namespace MediaServer1
} // namespace UPnPS

