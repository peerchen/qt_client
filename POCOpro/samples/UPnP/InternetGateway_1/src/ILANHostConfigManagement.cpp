//
// ILANHostConfigManagement.cpp
//
// Library: InternetGateway1
// Package: Generated
// Module:  ILANHostConfigManagement
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


#include "UPnPS/InternetGateway1/ILANHostConfigManagement.h"


namespace UPnPS {
namespace InternetGateway1 {


ILANHostConfigManagement::ILANHostConfigManagement():
	Poco::RefCountedObject()

{
}


ILANHostConfigManagement::~ILANHostConfigManagement()
{
}


const Poco::RemotingNG::Identifiable::TypeId& ILANHostConfigManagement::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("UPnPS.InternetGateway1.LANHostConfigManagement");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace InternetGateway1
} // namespace UPnPS
