//
// WANCableLinkConfigClientHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigClientHelper
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


#include "UPnPS/InternetGateway1/WANCableLinkConfigClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANCableLinkConfigProxyFactory.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANCableLinkConfigClientHelper> shWANCableLinkConfigClientHelper;
}


WANCableLinkConfigClientHelper::WANCableLinkConfigClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.InternetGateway1.WANCableLinkConfig", new WANCableLinkConfigProxyFactory);
}


WANCableLinkConfigClientHelper::~WANCableLinkConfigClientHelper()
{
}


IWANCableLinkConfig::Ptr WANCableLinkConfigClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IWANCableLinkConfig>();
}


IWANCableLinkConfig::Ptr WANCableLinkConfigClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IWANCableLinkConfig::remoting__typeId(), protocol);
	return pInterface.cast<IWANCableLinkConfig>();
}


WANCableLinkConfigClientHelper& WANCableLinkConfigClientHelper::instance()
{
	return *shWANCableLinkConfigClientHelper.get();
}


} // namespace InternetGateway1
} // namespace UPnPS

