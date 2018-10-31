//
// WANCommonInterfaceConfigProxy.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigProxy
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


#ifndef InternetGateway1_WANCommonInterfaceConfigProxy_INCLUDED
#define InternetGateway1_WANCommonInterfaceConfigProxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/InternetGateway1/IWANCommonInterfaceConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCommonInterfaceConfigProxy: public UPnPS::InternetGateway1::IWANCommonInterfaceConfig, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<WANCommonInterfaceConfigProxy> Ptr;

	WANCommonInterfaceConfigProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a WANCommonInterfaceConfigProxy.

	virtual ~WANCommonInterfaceConfigProxy();
		/// Destroys the WANCommonInterfaceConfigProxy.

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

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setEnabledForInternet(bool newEnabledForInternet);

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANCommonInterfaceConfigProxy::remoting__typeId() const
{
	return IWANCommonInterfaceConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCommonInterfaceConfigProxy_INCLUDED

