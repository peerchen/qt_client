//
// ContentDirectory1EventSubscriber.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1EventSubscriber
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


#ifndef MediaServer1_ContentDirectory1EventSubscriber_INCLUDED
#define MediaServer1_ContentDirectory1EventSubscriber_INCLUDED


#include "Poco/RemotingNG/EventSubscriber.h"
#include "UPnPS/MediaServer1/ContentDirectory1Proxy.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ContentDirectory1EventSubscriber: public Poco::RemotingNG::EventSubscriber
{
public:
	ContentDirectory1EventSubscriber(const std::string& uri, ContentDirectory1Proxy* pProxy);
		/// Creates a ContentDirectory1EventSubscriber.

	virtual ~ContentDirectory1EventSubscriber();
		/// Destroys the ContentDirectory1EventSubscriber.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__containerUpdateIDsChanged(const std::string& data);

	void event__systemUpdateIDChanged(const Poco::UInt32& data);

	void event__transferIDsChanged(const std::string& data);

public:
	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ContentDirectory1EventSubscriber::remoting__typeId() const
{
	return IContentDirectory1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ContentDirectory1EventSubscriber_INCLUDED

