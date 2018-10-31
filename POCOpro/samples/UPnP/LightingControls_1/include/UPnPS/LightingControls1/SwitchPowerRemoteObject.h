//
// SwitchPowerRemoteObject.h
//
// Library: LightingControls1
// Package: Generated
// Module:  SwitchPowerRemoteObject
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


#ifndef LightingControls1_SwitchPowerRemoteObject_INCLUDED
#define LightingControls1_SwitchPowerRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/LightingControls1/ISwitchPower.h"
#include "UPnPS/LightingControls1/LightingControls1.h"


namespace UPnPS {
namespace LightingControls1 {


class LightingControls1_API SwitchPowerRemoteObject: public UPnPS::LightingControls1::ISwitchPower, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<SwitchPowerRemoteObject> Ptr;

	SwitchPowerRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> pServiceObject);
		/// Creates a SwitchPowerRemoteObject.

	virtual ~SwitchPowerRemoteObject();
		/// Destroys the SwitchPowerRemoteObject.

	virtual void getStatus(bool& resultStatus);

	virtual void getTarget(bool& retTargetValue);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setTarget(bool newTargetValue);

protected:
	void event__statusChanged(const bool& data);

private:
	Poco::SharedPtr<UPnPS::LightingControls1::SwitchPower> _pServiceObject;
};


inline void SwitchPowerRemoteObject::getStatus(bool& resultStatus)
{
	_pServiceObject->getStatus(resultStatus);
}


inline void SwitchPowerRemoteObject::getTarget(bool& retTargetValue)
{
	_pServiceObject->getTarget(retTargetValue);
}


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchPowerRemoteObject::remoting__typeId() const
{
	return ISwitchPower::remoting__typeId();
}


inline void SwitchPowerRemoteObject::setTarget(bool newTargetValue)
{
	_pServiceObject->setTarget(newTargetValue);
}


} // namespace LightingControls1
} // namespace UPnPS


#endif // LightingControls1_SwitchPowerRemoteObject_INCLUDED

