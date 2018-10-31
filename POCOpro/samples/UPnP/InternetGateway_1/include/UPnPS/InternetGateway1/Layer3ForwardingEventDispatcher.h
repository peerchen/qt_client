//
// Layer3ForwardingEventDispatcher.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingEventDispatcher
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


#ifndef InternetGateway1_Layer3ForwardingEventDispatcher_INCLUDED
#define InternetGateway1_Layer3ForwardingEventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/Layer3ForwardingRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API Layer3ForwardingEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	Layer3ForwardingEventDispatcher(Layer3ForwardingRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a Layer3ForwardingEventDispatcher.

	virtual ~Layer3ForwardingEventDispatcher();
		/// Destroys the Layer3ForwardingEventDispatcher.

	void event__defaultConnectionServiceChanged(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__defaultConnectionServiceChangedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	Layer3ForwardingRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& Layer3ForwardingEventDispatcher::remoting__typeId() const
{
	return ILayer3Forwarding::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_Layer3ForwardingEventDispatcher_INCLUDED

