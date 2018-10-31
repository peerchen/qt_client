//
// Layer3ForwardingProxy.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingProxy
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


#ifndef InternetGateway1_Layer3ForwardingProxy_INCLUDED
#define InternetGateway1_Layer3ForwardingProxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/InternetGateway1/ILayer3Forwarding.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API Layer3ForwardingProxy: public UPnPS::InternetGateway1::ILayer3Forwarding, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<Layer3ForwardingProxy> Ptr;

	Layer3ForwardingProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a Layer3ForwardingProxy.

	virtual ~Layer3ForwardingProxy();
		/// Destroys the Layer3ForwardingProxy.

	virtual void getDefaultConnectionService(std::string& newDefaultConnectionService);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setDefaultConnectionService(const std::string& newDefaultConnectionService);

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& Layer3ForwardingProxy::remoting__typeId() const
{
	return ILayer3Forwarding::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_Layer3ForwardingProxy_INCLUDED

