//
// WANCableLinkConfigProxy.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigProxy
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


#ifndef InternetGateway1_WANCableLinkConfigProxy_INCLUDED
#define InternetGateway1_WANCableLinkConfigProxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/InternetGateway1/IWANCableLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCableLinkConfigProxy: public UPnPS::InternetGateway1::IWANCableLinkConfig, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<WANCableLinkConfigProxy> Ptr;

	WANCableLinkConfigProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a WANCableLinkConfigProxy.

	virtual ~WANCableLinkConfigProxy();
		/// Destroys the WANCableLinkConfigProxy.

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

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANCableLinkConfigProxy::remoting__typeId() const
{
	return IWANCableLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCableLinkConfigProxy_INCLUDED

