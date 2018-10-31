//
// IWANCableLinkConfig.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  IWANCableLinkConfig
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


#ifndef InternetGateway1_IWANCableLinkConfig_INCLUDED
#define InternetGateway1_IWANCableLinkConfig_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANCableLinkConfig.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API IWANCableLinkConfig: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IWANCableLinkConfig> Ptr;

	IWANCableLinkConfig();
		/// Creates a IWANCableLinkConfig.

	virtual ~IWANCableLinkConfig();
		/// Destroys the IWANCableLinkConfig.

	virtual void getBPIEncryptionEnabled(bool& newBPIEncryptionEnabled) = 0;

	virtual void getCableLinkConfigInfo(std::string& newCableLinkConfigState, std::string& newLinkType) = 0;

	virtual void getConfigFile(std::string& newConfigFile) = 0;

	virtual void getDownstreamFrequency(Poco::UInt32& newDownstreamFrequency) = 0;

	virtual void getDownstreamModulation(std::string& newDownstreamModulation) = 0;

	virtual void getTFTPServer(std::string& newTFTPServer) = 0;

	virtual void getUpstreamChannelID(Poco::UInt32& newUpstreamChannelID) = 0;

	virtual void getUpstreamFrequency(Poco::UInt32& newUpstreamFrequency) = 0;

	virtual void getUpstreamModulation(std::string& newUpstreamModulation) = 0;

	virtual void getUpstreamPowerLevel(Poco::UInt32& newUpstreamPowerLevel) = 0;

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

	Poco::BasicEvent < const bool > bPIEncryptionEnabledChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_IWANCableLinkConfig_INCLUDED

