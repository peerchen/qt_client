//
// WANCableLinkConfigRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigRemoteObject
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


#ifndef InternetGateway1_WANCableLinkConfigRemoteObject_INCLUDED
#define InternetGateway1_WANCableLinkConfigRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/IWANCableLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCableLinkConfigRemoteObject: public UPnPS::InternetGateway1::IWANCableLinkConfig, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<WANCableLinkConfigRemoteObject> Ptr;

	WANCableLinkConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANCableLinkConfig> pServiceObject);
		/// Creates a WANCableLinkConfigRemoteObject.

	virtual ~WANCableLinkConfigRemoteObject();
		/// Destroys the WANCableLinkConfigRemoteObject.

	virtual void getBPIEncryptionEnabled(bool& newBPIEncryptionEnabled);

	virtual void getCableLinkConfigInfo(std::string& newCableLinkConfigState, std::string& newLinkType);

	virtual void getConfigFile(std::string& newConfigFile);

	virtual void getDownstreamFrequency(Poco::UInt32& newDownstreamFrequency);

	virtual void getDownstreamModulation(std::string& newDownstreamModulation);

	virtual void getTFTPServer(std::string& newTFTPServer);

	virtual void getUpstreamChannelID(Poco::UInt32& newUpstreamChannelID);

	virtual void getUpstreamFrequency(Poco::UInt32& newUpstreamFrequency);

	virtual void getUpstreamModulation(std::string& newUpstreamModulation);

	virtual void getUpstreamPowerLevel(Poco::UInt32& newUpstreamPowerLevel);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

protected:
	void event__bPIEncryptionEnabledChanged(const bool& data);

private:
	Poco::SharedPtr<UPnPS::InternetGateway1::WANCableLinkConfig> _pServiceObject;
};


inline void WANCableLinkConfigRemoteObject::getBPIEncryptionEnabled(bool& newBPIEncryptionEnabled)
{
	_pServiceObject->getBPIEncryptionEnabled(newBPIEncryptionEnabled);
}


inline void WANCableLinkConfigRemoteObject::getCableLinkConfigInfo(std::string& newCableLinkConfigState, std::string& newLinkType)
{
	_pServiceObject->getCableLinkConfigInfo(newCableLinkConfigState, newLinkType);
}


inline void WANCableLinkConfigRemoteObject::getConfigFile(std::string& newConfigFile)
{
	_pServiceObject->getConfigFile(newConfigFile);
}


inline void WANCableLinkConfigRemoteObject::getDownstreamFrequency(Poco::UInt32& newDownstreamFrequency)
{
	_pServiceObject->getDownstreamFrequency(newDownstreamFrequency);
}


inline void WANCableLinkConfigRemoteObject::getDownstreamModulation(std::string& newDownstreamModulation)
{
	_pServiceObject->getDownstreamModulation(newDownstreamModulation);
}


inline void WANCableLinkConfigRemoteObject::getTFTPServer(std::string& newTFTPServer)
{
	_pServiceObject->getTFTPServer(newTFTPServer);
}


inline void WANCableLinkConfigRemoteObject::getUpstreamChannelID(Poco::UInt32& newUpstreamChannelID)
{
	_pServiceObject->getUpstreamChannelID(newUpstreamChannelID);
}


inline void WANCableLinkConfigRemoteObject::getUpstreamFrequency(Poco::UInt32& newUpstreamFrequency)
{
	_pServiceObject->getUpstreamFrequency(newUpstreamFrequency);
}


inline void WANCableLinkConfigRemoteObject::getUpstreamModulation(std::string& newUpstreamModulation)
{
	_pServiceObject->getUpstreamModulation(newUpstreamModulation);
}


inline void WANCableLinkConfigRemoteObject::getUpstreamPowerLevel(Poco::UInt32& newUpstreamPowerLevel)
{
	_pServiceObject->getUpstreamPowerLevel(newUpstreamPowerLevel);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WANCableLinkConfigRemoteObject::remoting__typeId() const
{
	return IWANCableLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCableLinkConfigRemoteObject_INCLUDED

