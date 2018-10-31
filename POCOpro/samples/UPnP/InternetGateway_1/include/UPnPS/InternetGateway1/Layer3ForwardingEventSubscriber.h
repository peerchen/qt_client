//
// Layer3ForwardingEventSubscriber.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingEventSubscriber
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


#ifndef InternetGateway1_Layer3ForwardingEventSubscriber_INCLUDED
#define InternetGateway1_Layer3ForwardingEventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/Layer3ForwardingProxy.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API Layer3ForwardingEventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	Layer3ForwardingEventSubscriber(const std::string& uri, Layer3ForwardingProxy* pProxy);
		/// Creates a Layer3ForwardingEventSubscriber.

	virtual ~Layer3ForwardingEventSubscriber();
		/// Destroys the Layer3ForwardingEventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__defaultConnectionServiceChanged(const std::string& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& Layer3ForwardingEventSubscriber::remoting__typeId() const
{
	return ILayer3Forwarding::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_Layer3ForwardingEventSubscriber_INCLUDED

