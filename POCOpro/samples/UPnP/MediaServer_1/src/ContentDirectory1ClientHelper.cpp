//
// ContentDirectory1ClientHelper.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1ClientHelper
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


#include "UPnPS/MediaServer1/ContentDirectory1ClientHelper.h"
#include "Poco/SingletonHolder.h"
#include "UPnPS/MediaServer1/ContentDirectory1ProxyFactory.h"


namespace UPnPS {
namespace MediaServer1 {


namespace
{
	static Poco::SingletonHolder<ContentDirectory1ClientHelper> shContentDirectory1ClientHelper;
}


ContentDirectory1ClientHelper::ContentDirectory1ClientHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerProxyFactory("UPnPS.MediaServer1.ContentDirectory1", new ContentDirectory1ProxyFactory);
}


ContentDirectory1ClientHelper::~ContentDirectory1ClientHelper()
{
}


IContentDirectory1::Ptr ContentDirectory1ClientHelper::findImpl(const std::string& uri)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri);
	return pInterface.cast<IContentDirectory1>();
}


IContentDirectory1::Ptr ContentDirectory1ClientHelper::findImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pInterface = _pORB->findObject(uri, IContentDirectory1::remoting__typeId(), protocol);
	return pInterface.cast<IContentDirectory1>();
}


ContentDirectory1ClientHelper& ContentDirectory1ClientHelper::instance()
{
	return *shContentDirectory1ClientHelper.get();
}


} // namespace MediaServer1
} // namespace UPnPS

