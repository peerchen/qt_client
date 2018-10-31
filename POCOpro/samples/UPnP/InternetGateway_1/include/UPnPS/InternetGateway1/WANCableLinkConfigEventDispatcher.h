//
// WANCableLinkConfigEventDispatcher.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANCableLinkConfigEventDispatcher
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


#ifndef InternetGateway1_WANCableLinkConfigEventDispatcher_INCLUDED
#define InternetGateway1_WANCableLinkConfigEventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANCableLinkConfigRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANCableLinkConfigEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	WANCableLinkConfigEventDispatcher(WANCableLinkConfigRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a WANCableLinkConfigEventDispatcher.

	virtual ~WANCableLinkConfigEventDispatcher();
		/// Destroys the WANCableLinkConfigEventDispatcher.

	void event__bPIEncryptionEnabledChanged(const void* pSender, const bool& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__bPIEncryptionEnabledChangedImpl(const std::string& subscriberURI, const bool& data);

	static const std::string DEFAULT_NS;
	WANCableLinkConfigRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANCableLinkConfigEventDispatcher::remoting__typeId() const
{
	return IWANCableLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANCableLinkConfigEventDispatcher_INCLUDED

