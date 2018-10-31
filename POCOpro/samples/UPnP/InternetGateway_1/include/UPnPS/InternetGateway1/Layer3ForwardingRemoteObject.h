//
// Layer3ForwardingRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  Layer3ForwardingRemoteObject
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


#ifndef InternetGateway1_Layer3ForwardingRemoteObject_INCLUDED
#define InternetGateway1_Layer3ForwardingRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/ILayer3Forwarding.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API Layer3ForwardingRemoteObject: public UPnPS::InternetGateway1::ILayer3Forwarding, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<Layer3ForwardingRemoteObject> Ptr;

	Layer3ForwardingRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> pServiceObject);
		/// Creates a Layer3ForwardingRemoteObject.

	virtual ~Layer3ForwardingRemoteObject();
		/// Destroys the Layer3ForwardingRemoteObject.

	virtual void getDefaultConnectionService(std::string& newDefaultConnectionService);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setDefaultConnectionService(const std::string& newDefaultConnectionService);

protected:
	void event__defaultConnectionServiceChanged(const std::string& data);

private:
	Poco::SharedPtr<UPnPS::InternetGateway1::Layer3Forwarding> _pServiceObject;
};


inline void Layer3ForwardingRemoteObject::getDefaultConnectionService(std::string& newDefaultConnectionService)
{
	_pServiceObject->getDefaultConnectionService(newDefaultConnectionService);
}


inline const Poco::RemotingNG::Identifiable::TypeId& Layer3ForwardingRemoteObject::remoting__typeId() const
{
	return ILayer3Forwarding::remoting__typeId();
}


inline void Layer3ForwardingRemoteObject::setDefaultConnectionService(const std::string& newDefaultConnectionService)
{
	_pServiceObject->setDefaultConnectionService(newDefaultConnectionService);
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_Layer3ForwardingRemoteObject_INCLUDED

