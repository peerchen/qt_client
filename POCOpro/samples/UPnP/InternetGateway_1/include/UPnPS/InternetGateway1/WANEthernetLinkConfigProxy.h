//
// WANEthernetLinkConfigProxy.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANEthernetLinkConfigProxy
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


#ifndef InternetGateway1_WANEthernetLinkConfigProxy_INCLUDED
#define InternetGateway1_WANEthernetLinkConfigProxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/InternetGateway1/IWANEthernetLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANEthernetLinkConfigProxy: public UPnPS::InternetGateway1::IWANEthernetLinkConfig, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<WANEthernetLinkConfigProxy> Ptr;

	WANEthernetLinkConfigProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a WANEthernetLinkConfigProxy.

	virtual ~WANEthernetLinkConfigProxy();
		/// Destroys the WANEthernetLinkConfigProxy.

	virtual void getEthernetLinkStatus(std::string& newEthernetLinkStatus);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANEthernetLinkConfigProxy::remoting__typeId() const
{
	return IWANEthernetLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANEthernetLinkConfigProxy_INCLUDED

