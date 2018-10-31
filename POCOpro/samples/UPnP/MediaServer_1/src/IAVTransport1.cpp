//
// IAVTransport1.cpp
//
// Library: MediaServer1
// Package: Generated
// Module:  IAVTransport1
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


#include "UPnPS/MediaServer1/IAVTransport1.h"


namespace UPnPS {
namespace MediaServer1 {


IAVTransport1::IAVTransport1():
	Poco::RefCountedObject(),
	lastChangeChanged()
{
}


IAVTransport1::~IAVTransport1()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IAVTransport1::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("UPnPS.MediaServer1.AVTransport1");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace MediaServer1
} // namespace UPnPS

