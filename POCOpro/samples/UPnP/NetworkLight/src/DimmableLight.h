//
// DimmableLight.h
//
// $Id: //poco/1.7/UPnP/samples/NetworkLight/src/DimmableLight.h#1 $
//
// Copyright (c) 2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef DimmableLight_INCLUDED
#define DimmableLight_INCLUDED


#include "Poco/Logger.h"


class DimmableLight
{
public:
	DimmableLight();
		/// Creates a DimmableLightImpl.

	~DimmableLight();
		/// Destroys the DimmableLightImpl.

	void on();
		/// Turns the light on.
		
	void off();
		/// Turns the light off.
		
	bool isOn() const;
		/// Returns true iff the light is on.
		
	void setLevel(Poco::UInt8 percent);
		/// Sets the level in percent (0 - 100).
		
	Poco::UInt8 getLevel() const;
		/// Returns the level in percent (0 - 100).

private:
	bool _on;
	Poco::UInt8 _level;
	Poco::Logger& _logger;
};


//
// inlines
//
inline bool DimmableLight::isOn() const
{
	return _on;
}


inline Poco::UInt8 DimmableLight::getLevel() const
{
	return _level;
}


#endif // DimmableLight_INCLUDED
