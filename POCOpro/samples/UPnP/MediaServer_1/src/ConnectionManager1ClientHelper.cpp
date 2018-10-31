//
// ConnectionManager1ClientHelper.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ConnectionManager1ClientHelper
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


#include "UPnPS/MediaServer1/ConnectionManager1ClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/MediaServer1/ConnectionManager1ProxyFactory.h"


namespace UPnPS {
namespace MediaServer1 {


namespace
{
	static Poco::SingletonHolder<ConnectionManager1ClientHelper> shConnectionManager1ClientHelper;
}


ConnectionManager1ClientHelper::ConnectionManager1ClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.MediaServer1.ConnectionManager1", new ConnectionManager1ProxyFactory);
}


ConnectionManager1ClientHelper::~ConnectionManager1ClientHelper()
{
}


IConnectionManager1::Ptr ConnectionManager1ClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IConnectionManager1>();
}


IConnectionManager1::Ptr ConnectionManager1ClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IConnectionManager1::remoting__typeId(), protocol);
	return pInterface.cast<IConnectionManager1>();
}


ConnectionManager1ClientHelper& ConnectionManager1ClientHelper::instance()
{
	return *shConnectionManager1ClientHelper.get();
}


} // namespace MediaServer1
} // namespace UPnPS

