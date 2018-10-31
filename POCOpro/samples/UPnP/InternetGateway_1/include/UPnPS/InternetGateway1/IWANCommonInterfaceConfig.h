//
// IWANCommonInterfaceConfig.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  IWANCommonInterfaceConfig
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


#ifndef InternetGateway1_IWANCommonInterfaceConfig_INCLUDED
#define InternetGateway1_IWANCommonInterfaceConfig_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANCommonInterfaceConfig.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API IWANCommonInterfaceConfig: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IWANCommonInterfaceConfig> Ptr;

	IWANCommonInterfaceConfig();
		/// Creates a IWANCommonInterfaceConfig.

	virtual ~IWANCommonInterfaceConfig();
		/// Destroys the IWANCommonInterfaceConfig.

	virtual void getActiveConnection(Poco::UInt16 newActiveConnectionIndex, std::string& newActiveConnDeviceContainer, std::string& newActiveConnectionServiceID) = 0;

	virtual void getCommonLinkProperties(std::string& newWANAccessType, Poco::UInt32& newLayer1UpstreamMaxBitRate, Poco::UInt32& newLayer1DownstreamMaxBitRate, std::string& newPhysicalLinkStatus) = 0;

	virtual void getEnabledForInternet(bool& newEnabledForInternet) = 0;

	virtual void getMaximumActiveConnections(Poco::UInt16& newMaximumActiveConnections) = 0;

	virtual void getTotalBytesReceived(Poco::UInt32& newTotalBytesReceived) = 0;

	virtual void getTotalBytesSent(Poco::UInt32& newTotalBytesSent) = 0;

	virtual void getTotalPacketsReceived(Poco::UInt32& newTotalPacketsReceived) = 0;

	virtual void getTotalPacketsSent(Poco::UInt32& newTotalPacketsSent) = 0;

	virtual void getWANAccessProvider(std::string& newWANAccessProvider) = 0;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void setEnabledForInternet(bool newEnabledForInternet) = 0;

	Poco::BasicEvent < const bool > enabledForInternetChanged;
	Poco::BasicEvent < const Poco::UInt16 > numberOfActiveConnectionsChanged;
	Poco::BasicEvent < const std::string > physicalLinkStatusChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_IWANCommonInterfaceConfig_INCLUDED

