//
// WANCommonInterfaceConfigEventDispatcher.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigEventDispatcher
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


#ifndef InternetGateway1_WANCommonInterfaceConfigEventDispatcher_INCLUDED
#define InternetGateway1_WANCommonInterfaceConfigEventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCommonInterfaceConfigEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	WANCommonInterfaceConfigEventDispatcher(WANCommonInterfaceConfigRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a WANCommonInterfaceConfigEventDispatcher.

	virtual ~WANCommonInterfaceConfigEventDispatcher();
		/// Destroys the WANCommonInterfaceConfigEventDispatcher.

	void event__enabledForInternetChanged(const void* pSender, const bool& data);

	void event__numberOfActiveConnectionsChanged(const void* pSender, const Poco::UInt16& data);

	void event__physicalLinkStatusChanged(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__enabledForInternetChangedImpl(const std::string& subscriberURI, const bool& data);

	void event__numberOfActiveConnectionsChangedImpl(const std::string& subscriberURI, const Poco::UInt16& data);

	void event__physicalLinkStatusChangedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	WANCommonInterfaceConfigRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANCommonInterfaceConfigEventDispatcher::remoting__typeId() const
{
	return IWANCommonInterfaceConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCommonInterfaceConfigEventDispatcher_INCLUDED

