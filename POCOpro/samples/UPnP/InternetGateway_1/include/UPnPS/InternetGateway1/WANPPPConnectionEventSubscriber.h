//
// WANPPPConnectionEventSubscriber.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANPPPConnectionEventSubscriber
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


#ifndef InternetGateway1_WANPPPConnectionEventSubscriber_INCLUDED
#define InternetGateway1_WANPPPConnectionEventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANPPPConnectionProxy.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANPPPConnectionEventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	WANPPPConnectionEventSubscriber(const std::string& uri, WANPPPConnectionProxy* pProxy);
		/// Creates a WANPPPConnectionEventSubscriber.

	virtual ~WANPPPConnectionEventSubscriber();
		/// Destroys the WANPPPConnectionEventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__connectionStatusChanged(const std::string& data);

	void event__externalIPAddressChanged(const std::string& data);

	void event__portMappingNumberOfEntriesChanged(const Poco::UInt16& data);

	void event__possibleConnectionTypesChanged(const std::string& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANPPPConnectionEventSubscriber::remoting__typeId() const
{
	return IWANPPPConnection::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANPPPConnectionEventSubscriber_INCLUDED

