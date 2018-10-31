//
// WANCommonInterfaceConfigRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigRemoteObject
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


#ifndef InternetGateway1_WANCommonInterfaceConfigRemoteObject_INCLUDED
#define InternetGateway1_WANCommonInterfaceConfigRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/IWANCommonInterfaceConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCommonInterfaceConfigRemoteObject: public UPnPS::InternetGateway1::IWANCommonInterfaceConfig, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<WANCommonInterfaceConfigRemoteObject> Ptr;

	WANCommonInterfaceConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANCommonInterfaceConfig> pServiceObject);
		/// Creates a WANCommonInterfaceConfigRemoteObject.

	virtual ~WANCommonInterfaceConfigRemoteObject();
		/// Destroys the WANCommonInterfaceConfigRemoteObject.

	virtual void getActiveConnection(Poco::UInt16 newActiveConnectionIndex, std::string& newActiveConnDeviceContainer, std::string& newActiveConnectionServiceID);

	virtual void getCommonLinkProperties(std::string& newWANAccessType, Poco::UInt32& newLayer1UpstreamMaxBitRate, Poco::UInt32& newLayer1DownstreamMaxBitRate, std::string& newPhysicalLinkStatus);

	virtual void getEnabledForInternet(bool& newEnabledForInternet);

	virtual void getMaximumActiveConnections(Poco::UInt16& newMaximumActiveConnections);

	virtual void getTotalBytesReceived(Poco::UInt32& newTotalBytesReceived);

	virtual void getTotalBytesSent(Poco::UInt32& newTotalBytesSent);

	virtual void getTotalPacketsReceived(Poco::UInt32& newTotalPacketsReceived);

	virtual void getTotalPacketsSent(Poco::UInt32& newTotalPacketsSent);

	virtual void getWANAccessProvider(std::string& newWANAccessProvider);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setEnabledForInternet(bool newEnabledForInternet);

protected:
	void event__enabledForInternetChanged(const bool& data);

	void event__numberOfActiveConnectionsChanged(const Poco::UInt16& data);

	void event__physicalLinkStatusChanged(const std::string& data);

private:
	Poco::SharedPtr<UPnPS::InternetGateway1::WANCommonInterfaceConfig> _pServiceObject;
};


inline void WANCommonInterfaceConfigRemoteObject::getActiveConnection(Poco::UInt16 newActiveConnectionIndex, std::string& newActiveConnDeviceContainer, std::string& newActiveConnectionServiceID)
{
	_pServiceObject->getActiveConnection(newActiveConnectionIndex, newActiveConnDeviceContainer, newActiveConnectionServiceID);
}


inline void WANCommonInterfaceConfigRemoteObject::getCommonLinkProperties(std::string& newWANAccessType, Poco::UInt32& newLayer1UpstreamMaxBitRate, Poco::UInt32& newLayer1DownstreamMaxBitRate, std::string& newPhysicalLinkStatus)
{
	_pServiceObject->getCommonLinkProperties(newWANAccessType, newLayer1UpstreamMaxBitRate, newLayer1DownstreamMaxBitRate, newPhysicalLinkStatus);
}


inline void WANCommonInterfaceConfigRemoteObject::getEnabledForInternet(bool& newEnabledForInternet)
{
	_pServiceObject->getEnabledForInternet(newEnabledForInternet);
}


inline void WANCommonInterfaceConfigRemoteObject::getMaximumActiveConnections(Poco::UInt16& newMaximumActiveConnections)
{
	_pServiceObject->getMaximumActiveConnections(newMaximumActiveConnections);
}


inline void WANCommonInterfaceConfigRemoteObject::getTotalBytesReceived(Poco::UInt32& newTotalBytesReceived)
{
	_pServiceObject->getTotalBytesReceived(newTotalBytesReceived);
}


inline void WANCommonInterfaceConfigRemoteObject::getTotalBytesSent(Poco::UInt32& newTotalBytesSent)
{
	_pServiceObject->getTotalBytesSent(newTotalBytesSent);
}


inline void WANCommonInterfaceConfigRemoteObject::getTotalPacketsReceived(Poco::UInt32& newTotalPacketsReceived)
{
	_pServiceObject->getTotalPacketsReceived(newTotalPacketsReceived);
}


inline void WANCommonInterfaceConfigRemoteObject::getTotalPacketsSent(Poco::UInt32& newTotalPacketsSent)
{
	_pServiceObject->getTotalPacketsSent(newTotalPacketsSent);
}


inline void WANCommonInterfaceConfigRemoteObject::getWANAccessProvider(std::string& newWANAccessProvider)
{
	_pServiceObject->getWANAccessProvider(newWANAccessProvider);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WANCommonInterfaceConfigRemoteObject::remoting__typeId() const
{
	return IWANCommonInterfaceConfig::remoting__typeId();
}


inline void WANCommonInterfaceConfigRemoteObject::setEnabledForInternet(bool newEnabledForInternet)
{
	_pServiceObject->setEnabledForInternet(newEnabledForInternet);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCommonInterfaceConfigRemoteObject_INCLUDED

