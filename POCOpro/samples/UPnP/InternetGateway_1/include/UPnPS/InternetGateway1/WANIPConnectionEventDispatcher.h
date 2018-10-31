//
// WANIPConnectionEventDispatcher.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANIPConnectionEventDispatcher
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


#ifndef InternetGateway1_WANIPConnectionEventDispatcher_INCLUDED
#define InternetGateway1_WANIPConnectionEventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANIPConnectionRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANIPConnectionEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	WANIPConnectionEventDispatcher(WANIPConnectionRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a WANIPConnectionEventDispatcher.

	virtual ~WANIPConnectionEventDispatcher();
		/// Destroys the WANIPConnectionEventDispatcher.

	void event__connectionStatusChanged(const void* pSender, const std::string& data);

	void event__externalIPAddressChanged(const void* pSender, const std::string& data);

	void event__portMappingNumberOfEntriesChanged(const void* pSender, const Poco::UInt16& data);

	void event__possibleConnectionTypesChanged(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__connectionStatusChangedImpl(const std::string& subscriberURI, const std::string& data);

	void event__externalIPAddressChangedImpl(const std::string& subscriberURI, const std::string& data);

	void event__portMappingNumberOfEntriesChangedImpl(const std::string& subscriberURI, const Poco::UInt16& data);

	void event__possibleConnectionTypesChangedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	WANIPConnectionRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANIPConnectionEventDispatcher::remoting__typeId() const
{
	return IWANIPConnection::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANIPConnectionEventDispatcher_INCLUDED

