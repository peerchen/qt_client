//
// WANDSLLinkConfigEventDispatcher.h
//
// Library: InternetGateway1
// Package: Generated
// Module:  WANDSLLinkConfigEventDispatcher
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


#ifndef InternetGateway1_WANDSLLinkConfigEventDispatcher_INCLUDED
#define InternetGateway1_WANDSLLinkConfigEventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/InternetGateway1/InternetGateway1.h"
#include "UPnPS/InternetGateway1/WANDSLLinkConfigRemoteObject.h"


namespace UPnPS {
namespace InternetGateway1 {


class InternetGateway1_API WANDSLLinkConfigEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	WANDSLLinkConfigEventDispatcher(WANDSLLinkConfigRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a WANDSLLinkConfigEventDispatcher.

	virtual ~WANDSLLinkConfigEventDispatcher();
		/// Destroys the WANDSLLinkConfigEventDispatcher.

	void event__autoConfigChanged(const void* pSender, const bool& data);

	void event__linkStatusChanged(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__autoConfigChangedImpl(const std::string& subscriberURI, const bool& data);

	void event__linkStatusChangedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	WANDSLLinkConfigRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& WANDSLLinkConfigEventDispatcher::remoting__typeId() const
{
	return IWANDSLLinkConfig::remoting__typeId();
}


} // namespace InternetGateway1
} // namespace UPnPS


#endif // InternetGateway1_WANDSLLinkConfigEventDispatcher_INCLUDED

