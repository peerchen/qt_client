//
// WANDSLLinkConfigEventSubscriber.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigEventSubscriber
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


#ifndef InternetGateway1_WANDSLLinkConfigEventSubscriber_INCLUDED
#define InternetGateway1_WANDSLLinkConfigEventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfigProxy.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANDSLLinkConfigEventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	WANDSLLinkConfigEventSubscriber(const std::string& uri, WANDSLLinkConfigProxy* pProxy);
		/// Creates a WANDSLLinkConfigEventSubscriber.

	virtual ~WANDSLLinkConfigEventSubscriber();
		/// Destroys the WANDSLLinkConfigEventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__autoConfigChanged(const bool& data);

	void event__linkStatusChanged(const std::string& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANDSLLinkConfigEventSubscriber::remoting__typeId() const
{
	return IWANDSLLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANDSLLinkConfigEventSubscriber_INCLUDED

