//
// IWANDSLLinkConfig.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  IWANDSLLinkConfig
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


#ifndef InternetGateway1_IWANDSLLinkConfig_INCLUDED
#define InternetGateway1_IWANDSLLinkConfig_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfig.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API IWANDSLLinkConfig: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IWANDSLLinkConfig> Ptr;

	IWANDSLLinkConfig();
		/// Creates a IWANDSLLinkConfig.

	virtual ~IWANDSLLinkConfig();
		/// Destroys the IWANDSLLinkConfig.

	virtual void getATMEncapsulation(std::string& newATMEncapsulation) = 0;

	virtual void getAutoConfig(bool& newAutoConfig) = 0;

	virtual void getDSLLinkInfo(std::string& newLinkType, std::string& newLinkStatus) = 0;

	virtual void getDestinationAddress(std::string& newDestinationAddress) = 0;

	virtual void getFCSPreserved(bool& newFCSPreserved) = 0;

	virtual void getModulationType(std::string& newModulationType) = 0;

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

	virtual void setATMEncapsulation(const std::string& newATMEncapsulation) = 0;

	virtual void setDSLLinkType(const std::string& newLinkType) = 0;

	virtual void setDestinationAddress(const std::string& newDestinationAddress) = 0;

	virtual void setFCSPreserved(bool newFCSPreserved) = 0;

	Poco::BasicEvent < const bool > autoConfigChanged;
	Poco::BasicEvent < const std::string > linkStatusChanged;
};


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_IWANDSLLinkConfig_INCLUDED

