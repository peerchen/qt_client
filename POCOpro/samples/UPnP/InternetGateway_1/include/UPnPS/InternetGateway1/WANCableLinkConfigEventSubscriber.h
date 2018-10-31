//
// WANCableLinkConfigEventSubscriber.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigEventSubscriber
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


#ifndef InternetGateway1_WANCableLinkConfigEventSubscriber_INCLUDED
#define InternetGateway1_WANCableLinkConfigEventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANCableLinkConfigProxy.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCableLinkConfigEventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	WANCableLinkConfigEventSubscriber(const std::string& uri, WANCableLinkConfigProxy* pProxy);
		/// Creates a WANCableLinkConfigEventSubscriber.

	virtual ~WANCableLinkConfigEventSubscriber();
		/// Destroys the WANCableLinkConfigEventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__bPIEncryptionEnabledChanged(const bool& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANCableLinkConfigEventSubscriber::remoting__typeId() const
{
	return IWANCableLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCableLinkConfigEventSubscriber_INCLUDED

