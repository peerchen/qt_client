//
// WANEthernetLinkConfigRemoteObject.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANEthernetLinkConfigRemoteObject
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


#ifndef InternetGateway1_WANEthernetLinkConfigRemoteObject_INCLUDED
#define InternetGateway1_WANEthernetLinkConfigRemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/InternetGateway1/IWANEthernetLinkConfig.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANEthernetLinkConfigRemoteObject: public UPnPS::InternetGateway1::IWANEthernetLinkConfig, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<WANEthernetLinkConfigRemoteObject> Ptr;

	WANEthernetLinkConfigRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> pServiceObject);
		/// Creates a WANEthernetLinkConfigRemoteObject.

	virtual ~WANEthernetLinkConfigRemoteObject();
		/// Destroys the WANEthernetLinkConfigRemoteObject.

	virtual void getEthernetLinkStatus(std::string& newEthernetLinkStatus);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

protected:
	void event__ethernetLinkStatusChanged(const std::string& data);

private:
	Poco::SharedPtr<UPnPS::InternetGateway1::WANEthernetLinkConfig> _pServiceObject;
};


inline void WANEthernetLinkConfigRemoteObject::getEthernetLinkStatus(std::string& newEthernetLinkStatus)
{
	_pServiceObject->getEthernetLinkStatus(newEthernetLinkStatus);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WANEthernetLinkConfigRemoteObject::remoting__typeId() const
{
	return IWANEthernetLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANEthernetLinkConfigRemoteObject_INCLUDED

