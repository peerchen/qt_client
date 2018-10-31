//
// WANCommonInterfaceConfigClientHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigClientHelper
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


#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigProxyFactory.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANCommonInterfaceConfigClientHelper> shWANCommonInterfaceConfigClientHelper;
}


WANCommonInterfaceConfigClientHelper::WANCommonInterfaceConfigClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.InternetGateway1.WANCommonInterfaceConfig", new WANCommonInterfaceConfigProxyFactory);
}


WANCommonInterfaceConfigClientHelper::~WANCommonInterfaceConfigClientHelper()
{
}


IWANCommonInterfaceConfig::Ptr WANCommonInterfaceConfigClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IWANCommonInterfaceConfig>();
}


IWANCommonInterfaceConfig::Ptr WANCommonInterfaceConfigClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IWANCommonInterfaceConfig::remoting__typeId(), protocol);
	return pInterface.cast<IWANCommonInterfaceConfig>();
}


WANCommonInterfaceConfigClientHelper& WANCommonInterfaceConfigClientHelper::instance()
{
	return *shWANCommonInterfaceConfigClientHelper.get();
}


} // namespace InternetGateway1
} // namespace UPnPS

