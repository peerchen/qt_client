//
// WANDSLLinkConfigProxy.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigProxy
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


#ifndef InternetGateway1_WANDSLLinkConfigProxy_INCLUDED
#define InternetGateway1_WANDSLLinkConfigProxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/InternetGateway1/IWANDSLLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANDSLLinkConfigProxy: public UPnPS::InternetGateway1::IWANDSLLinkConfig, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<WANDSLLinkConfigProxy> Ptr;

	WANDSLLinkConfigProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a WANDSLLinkConfigProxy.

	virtual ~WANDSLLinkConfigProxy();
		/// Destroys the WANDSLLinkConfigProxy.

	virtual void getATMEncapsulation(std::string& newATMEncapsulation);

	virtual void getAutoConfig(bool& newAutoConfig);

	virtual void getDSLLinkInfo(std::string& newLinkType, std::string& newLinkStatus);

	virtual void getDestinationAddress(std::string& newDestinationAddress);

	virtual void getFCSPreserved(bool& newFCSPreserved);

	virtual void getModulationType(std::string& newModulationType);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setATMEncapsulation(const std::string& newATMEncapsulation);

	virtual void setDSLLinkType(const std::string& newLinkType);

	virtual void setDestinationAddress(const std::string& newDestinationAddress);

	virtual void setFCSPreserved(bool newFCSPreserved);

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANDSLLinkConfigProxy::remoting__typeId() const
{
	return IWANDSLLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANDSLLinkConfigProxy_INCLUDED

