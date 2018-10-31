//
// ContentDirectory1EventDispatcher.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1EventDispatcher
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


#ifndef MediaServer1_ContentDirectory1EventDispatcher_INCLUDED
#define MediaServer1_ContentDirectory1EventDispatcher_INCLUDED


#include "Poco/RemotingNG/EventDispatcher.h"
#include "UPnPS/MediaServer1/ContentDirectory1RemoteObject.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ContentDirectory1EventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	ContentDirectory1EventDispatcher(ContentDirectory1RemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a ContentDirectory1EventDispatcher.

	virtual ~ContentDirectory1EventDispatcher();
		/// Destroys the ContentDirectory1EventDispatcher.

	void event__containerUpdateIDsChanged(const void* pSender, const std::string& data);

	void event__systemUpdateIDChanged(const void* pSender, const Poco::UInt32& data);

	void event__transferIDsChanged(const void* pSender, const std::string& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__containerUpdateIDsChangedImpl(const std::string& subscriberURI, const std::string& data);

	void event__systemUpdateIDChangedImpl(const std::string& subscriberURI, const Poco::UInt32& data);

	void event__transferIDsChangedImpl(const std::string& subscriberURI, const std::string& data);

	static const std::string DEFAULT_NS;
	ContentDirectory1RemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ContentDirectory1EventDispatcher::remoting__typeId() const
{
	return IContentDirectory1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ContentDirectory1EventDispatcher_INCLUDED

