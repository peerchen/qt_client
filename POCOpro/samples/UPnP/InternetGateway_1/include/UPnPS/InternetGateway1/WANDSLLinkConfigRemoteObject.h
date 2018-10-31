//
// WANDSLLinkConfigRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigRemoteObject
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


#ifndef InternetGateway1_WANDSLLinkConfigRemoteObject_INCLUDED
#define InternetGateway1_WANDSLLinkConfigRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/IWANDSLLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANDSLLinkConfigRemoteObject: public UPnPS::InternetGateway1::IWANDSLLinkConfig, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<WANDSLLinkConfigRemoteObject> Ptr;

	WANDSLLinkConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> pServiceObject);
		/// Creates a WANDSLLinkConfigRemoteObject.

	virtual ~WANDSLLinkConfigRemoteObject();
		/// Destroys the WANDSLLinkConfigRemoteObject.

	virtual void getATMEncapsulation(std::string& newATMEncapsulation);

	virtual void getAutoConfig(bool& newAutoConfig);

	virtual void getDSLLinkInfo(std::string& newLinkType, std::string& newLinkStatus);

	virtual void getDestinationAddress(std::string& newDestinationAddress);

	virtual void getFCSPreserved(bool& newFCSPreserved);

	virtual void getModulationType(std::string& newModulationType);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setATMEncapsulation(const std::string& newATMEncapsulation);

	virtual void setDSLLinkType(const std::string& newLinkType);

	virtual void setDestinationAddress(const std::string& newDestinationAddress);

	virtual void setFCSPreserved(bool newFCSPreserved);

protected:
	void event__autoConfigChanged(const bool& data);

	void event__linkStatusChanged(const std::string& data);

private:
	Poco::SharedPtr<UPnPS::InternetGateway1::WANDSLLinkConfig> _pServiceObject;
};


inline void WANDSLLinkConfigRemoteObject::getATMEncapsulation(std::string& newATMEncapsulation)
{
	_pServiceObject->getATMEncapsulation(newATMEncapsulation);
}


inline void WANDSLLinkConfigRemoteObject::getAutoConfig(bool& newAutoConfig)
{
	_pServiceObject->getAutoConfig(newAutoConfig);
}


inline void WANDSLLinkConfigRemoteObject::getDSLLinkInfo(std::string& newLinkType, std::string& newLinkStatus)
{
	_pServiceObject->getDSLLinkInfo(newLinkType, newLinkStatus);
}


inline void WANDSLLinkConfigRemoteObject::getDestinationAddress(std::string& newDestinationAddress)
{
	_pServiceObject->getDestinationAddress(newDestinationAddress);
}


inline void WANDSLLinkConfigRemoteObject::getFCSPreserved(bool& newFCSPreserved)
{
	_pServiceObject->getFCSPreserved(newFCSPreserved);
}


inline void WANDSLLinkConfigRemoteObject::getModulationType(std::string& newModulationType)
{
	_pServiceObject->getModulationType(newModulationType);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WANDSLLinkConfigRemoteObject::remoting__typeId() const
{
	return IWANDSLLinkConfig::remoting__typeId();
}


inline void WANDSLLinkConfigRemoteObject::setATMEncapsulation(const std::string& newATMEncapsulation)
{
	_pServiceObject->setATMEncapsulation(newATMEncapsulation);
}


inline void WANDSLLinkConfigRemoteObject::setDSLLinkType(const std::string& newLinkType)
{
	_pServiceObject->setDSLLinkType(newLinkType);
}


inline void WANDSLLinkConfigRemoteObject::setDestinationAddress(const std::string& newDestinationAddress)
{
	_pServiceObject->setDestinationAddress(newDestinationAddress);
}


inline void WANDSLLinkConfigRemoteObject::setFCSPreserved(bool newFCSPreserved)
{
	_pServiceObject->setFCSPreserved(newFCSPreserved);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANDSLLinkConfigRemoteObject_INCLUDED

