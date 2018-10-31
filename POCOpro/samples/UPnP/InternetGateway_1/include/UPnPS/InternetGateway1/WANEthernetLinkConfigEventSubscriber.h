//
// WANEthernetLinkConfigEventSubscriber.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANEthernetLinkConfigEventSubscriber
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


#ifndef InternetGateway1_WANEthernetLinkConfigEventSubscriber_INCLUDED
#define InternetGateway1_WANEthernetLinkConfigEventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANEthernetLinkConfigProxy.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANEthernetLinkConfigEventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	WANEthernetLinkConfigEventSubscriber(const std::string& uri, WANEthernetLinkConfigProxy* pProxy);
		/// Creates a WANEthernetLinkConfigEventSubscriber.

	virtual ~WANEthernetLinkConfigEventSubscriber();
		/// Destroys the WANEthernetLinkConfigEventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__ethernetLinkStatusChanged(const std::string& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANEthernetLinkConfigEventSubscriber::remoting__typeId() const
{
	return IWANEthernetLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANEthernetLinkConfigEventSubscriber_INCLUDED

