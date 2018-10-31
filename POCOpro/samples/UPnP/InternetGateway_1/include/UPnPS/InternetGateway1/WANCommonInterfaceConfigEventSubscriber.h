//
// WANCommonInterfaceConfigEventSubscriber.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCommonInterfaceConfigEventSubscriber
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


#ifndef InternetGateway1_WANCommonInterfaceConfigEventSubscriber_INCLUDED
#define InternetGateway1_WANCommonInterfaceConfigEventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANCommonInterfaceConfigProxy.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCommonInterfaceConfigEventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	WANCommonInterfaceConfigEventSubscriber(const std::string& uri, WANCommonInterfaceConfigProxy* pProxy);
		/// Creates a WANCommonInterfaceConfigEventSubscriber.

	virtual ~WANCommonInterfaceConfigEventSubscriber();
		/// Destroys the WANCommonInterfaceConfigEventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__enabledForInternetChanged(const bool& data);

	void event__numberOfActiveConnectionsChanged(const Poco::UInt16& data);

	void event__physicalLinkStatusChanged(const std::string& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANCommonInterfaceConfigEventSubscriber::remoting__typeId() const
{
	return IWANCommonInterfaceConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCommonInterfaceConfigEventSubscriber_INCLUDED

