//
// DimmableLight.cpp
//
// $Id: //poco/1.7/UPnP/samples/NetworkLight/src/DimmableLight.cpp#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#include "DimmableLight.h"
#include "Poco/Format.h"


DimmableLight::DimmableLight():
	_on(false),
	_level(100),
	_logger(Poco::Logger::get("DimmableLight"))
{
}


DimmableLight::~DimmableLight()
{
}


void DimmableLight::on()
{
	_on = true;
	_logger.information("The light is now ON");
}

	
void DimmableLight::off()
{
	_on = false;
	_logger.information("The light is now OFF");
}

	
void DimmableLight::setLevel(Poco::UInt8 percent)
{
	_level = percent;
	_logger.information(Poco::format("Level is now %u %%", static_cast<unsigned>(_level)));
}
