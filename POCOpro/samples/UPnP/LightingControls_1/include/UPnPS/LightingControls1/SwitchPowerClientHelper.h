//
// SwitchPowerClientHelper.h
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerClientHelper
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


#ifndef LightingControls1_SwitchPowerClientHelper_INCLUDED
#define LightingControls1_SwitchPowerClientHelper_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "UPnPS/LightingControls1/ISwitchPower.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API SwitchPowerClientHelper
{
public:
	SwitchPowerClientHelper();
		/// Creates a SwitchPowerClientHelper.

	~SwitchPowerClientHelper();
		/// Destroys the SwitchPowerClientHelper.

	static ISwitchPower::Ptr find(const std::string& uri);
		/// Return an interface for the service object identified by the given URI.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// The URI must have the following format: <scheme>://<authority>/<protocol>/<typeId>/<objectId>

	static ISwitchPower::Ptr find(const std::string& uri, const std::string& protocol);
		/// Return a Proxy for the service object identified by the given URI.
		///
		/// The given protocol name is used to determine the Transport used by
		/// the Proxy. This is used for objects identified by URIs that do not
		/// follow the standard Remoting URI structure.

private:
	ISwitchPower::Ptr findImpl(const std::string& uri);

	ISwitchPower::Ptr findImpl(const std::string& uri, const std::string& protocol);

	static SwitchPowerClientHelper& instance();

	Poco::RemotingNG::ORB* _pORB;
};


inline ISwitchPower::Ptr SwitchPowerClientHelper::find(const std::string& uri)
{
	return SwitchPowerClientHelper::instance().findImpl(uri);
}


inline ISwitchPower::Ptr SwitchPowerClientHelper::find(const std::string& uri, const std::string& protocol)
{
	return SwitchPowerClientHelper::instance().findImpl(uri, protocol);
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_SwitchPowerClientHelper_INCLUDED

