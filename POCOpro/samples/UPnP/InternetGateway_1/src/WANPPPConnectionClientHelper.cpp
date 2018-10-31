//
// WANPPPConnectionClientHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPPPConnectionClientHelper
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


#include "UPnPS/InternetGateway1/WANPPPConnectionClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANPPPConnectionProxyFactory.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANPPPConnectionClientHelper> shWANPPPConnectionClientHelper;
}


WANPPPConnectionClientHelper::WANPPPConnectionClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.InternetGateway1.WANPPPConnection", new WANPPPConnectionProxyFactory);
}


WANPPPConnectionClientHelper::~WANPPPConnectionClientHelper()
{
}


IWANPPPConnection::Ptr WANPPPConnectionClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IWANPPPConnection>();
}


IWANPPPConnection::Ptr WANPPPConnectionClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IWANPPPConnection::remoting__typeId(), protocol);
	return pInterface.cast<IWANPPPConnection>();
}


WANPPPConnectionClientHelper& WANPPPConnectionClientHelper::instance()
{
	return *shWANPPPConnectionClientHelper.get();
}


} // namespace InternetGateway1
} // namespace UPnPS

