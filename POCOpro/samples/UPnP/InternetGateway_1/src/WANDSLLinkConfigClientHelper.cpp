//
// WANDSLLinkConfigClientHelper.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigClientHelper
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


#include "UPnPS/InternetGateway1/WANDSLLinkConfigClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfigProxyFactory.h"


namespace UPnPS {
namespace InternetGateway1 {


namespace
{
	static Poco::SingletonHolder<WANDSLLinkConfigClientHelper> shWANDSLLinkConfigClientHelper;
}


WANDSLLinkConfigClientHelper::WANDSLLinkConfigClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.InternetGateway1.WANDSLLinkConfig", new WANDSLLinkConfigProxyFactory);
}


WANDSLLinkConfigClientHelper::~WANDSLLinkConfigClientHelper()
{
}


IWANDSLLinkConfig::Ptr WANDSLLinkConfigClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IWANDSLLinkConfig>();
}


IWANDSLLinkConfig::Ptr WANDSLLinkConfigClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IWANDSLLinkConfig::remoting__typeId(), protocol);
	return pInterface.cast<IWANDSLLinkConfig>();
}


WANDSLLinkConfigClientHelper& WANDSLLinkConfigClientHelper::instance()
{
	return *shWANDSLLinkConfigClientHelper.get();
}


} // namespace InternetGateway1
} // namespace UPnPS

