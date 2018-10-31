//
// IConnectionManager1.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  IConnectionManager1
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


#include "UPnPS/MediaServer1/IConnectionManager1.h"


namespace UPnPS {
namespace MediaServer1 {


IConnectionManager1::IConnectionManager1():
	Poco::RefCountedObject(),
	currentConnectionIDsChanged(),
	sinkProtocolInfoChanged(),
	sourceProtocolInfoChanged()
{
}


IConnectionManager1::~IConnectionManager1()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IConnectionManager1::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("UPnPS.MediaServer1.ConnectionManager1");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace MediaServer1
} // namespace UPnPS

