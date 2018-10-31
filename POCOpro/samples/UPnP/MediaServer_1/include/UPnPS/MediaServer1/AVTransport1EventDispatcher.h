//
// AVTransport1EventDispatcher.h
//
// Library: MediaServer1
// Package: Generated
// Module:  AVTransport1EventDispatcher
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


#ifndef MediaServer1_AVTransport1EventDispatcher_INCLUDED
#define MediaServer1_AVTransport1EventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/MediaServer1/AVTransport1RemoteObject.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API AVTransport1EventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	AVTransport1EventDispatcher(AVTransport1RemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a AVTransport1EventDispatcher.

	virtual ~AVTransport1EventDispatcher();
		/// Destroys the AVTransport1EventDispatcher.

	void event__lastChangeChanged(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__lastChangeChangedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	AVTransport1RemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& AVTransport1EventDispatcher::remoting__typeId() const
{
	return IAVTransport1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_AVTransport1EventDispatcher_INCLUDED

