//
// IWANEthernetLinkConfig.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  IWANEthernetLinkConfig
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


#ifndef InternetGateway1_IWANEthernetLinkConfig_INCLUDED
#define InternetGateway1_IWANEthernetLinkConfig_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANEthernetLinkConfig.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API IWANEthernetLinkConfig: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IWANEthernetLinkConfig> Ptr;

	IWANEthernetLinkConfig();
		/// Creates a IWANEthernetLinkConfig.

	virtual ~IWANEthernetLinkConfig();
		/// Destroys the IWANEthernetLinkConfig.

	virtual void getEthernetLinkStatus(std::string& newEthernetLinkStatus) = 0;

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

	Poco::BasicEvent < const std::string > ethernetLinkStatusChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_IWANEthernetLinkConfig_INCLUDED

