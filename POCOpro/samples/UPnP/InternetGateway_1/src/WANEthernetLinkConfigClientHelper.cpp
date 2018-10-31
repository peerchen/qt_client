//
// WANEthernetLinkConfigClientHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANEthernetLinkConfigClientHelper
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


#include "UPnPS/InternetGateway1/WANEthernetLinkConfigClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANEthernetLinkConfigProxyFactory.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANEthernetLinkConfigClientHelper> shWANEthernetLinkConfigClientHelper;
}


WANEthernetLinkConfigClientHelper::WANEthernetLinkConfigClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.InternetGateway1.WANEthernetLinkConfig", new WANEthernetLinkConfigProxyFactory);
}


WANEthernetLinkConfigClientHelper::~WANEthernetLinkConfigClientHelper()
{
}


IWANEthernetLinkConfig::Ptr WANEthernetLinkConfigClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IWANEthernetLinkConfig>();
}


IWANEthernetLinkConfig::Ptr WANEthernetLinkConfigClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IWANEthernetLinkConfig::remoting__typeId(), protocol);
	return pInterface.cast<IWANEthernetLinkConfig>();
}


WANEthernetLinkConfigClientHelper& WANEthernetLinkConfigClientHelper::instance()
{
	return *shWANEthernetLinkConfigClientHelper.get();
}


} // namespace InternetGateway1
} // namespace UPnPS

