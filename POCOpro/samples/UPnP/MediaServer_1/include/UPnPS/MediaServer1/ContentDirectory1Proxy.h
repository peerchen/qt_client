//
// ContentDirectory1Proxy.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1Proxy
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


#ifndef MediaServer1_ContentDirectory1Proxy_INCLUDED
#define MediaServer1_ContentDirectory1Proxy_INCLUDED


#include "Poco/RemotingNG/EventListener.h"
#include "Poco/RemotingNG/EventSubscriber.h"
#include "Poco/RemotingNG/Proxy.h"
#include "UPnPS/MediaServer1/IContentDirectory1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ContentDirectory1Proxy: public UPnPS::MediaServer1::IContentDirectory1, public Poco::RemotingNG::Proxy
{
public:
	typedef Poco::AutoPtr<ContentDirectory1Proxy> Ptr;

	ContentDirectory1Proxy(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a ContentDirectory1Proxy.

	virtual ~ContentDirectory1Proxy();
		/// Destroys the ContentDirectory1Proxy.

	virtual void browse(const std::string& objectID, const std::string& browseFlag, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID);

	virtual void createObject(const std::string& containerID, const std::string& elements, std::string& objectID, std::string& result);

	virtual void createReference(const std::string& containerID, const std::string& objectID, std::string& newID);

	virtual void deleteResource(const Poco::URI& resourceURI);

	virtual void destroyObject(const std::string& objectID);

	virtual void exportResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID);

	virtual void getSearchCapabilities(std::string& searchCaps);

	virtual void getSortCapabilities(std::string& sortCaps);

	virtual void getSystemUpdateID(Poco::UInt32& id);

	virtual void getTransferProgress(Poco::UInt32 transferID, std::string& transferStatus, std::string& transferLength, std::string& transferTotal);

	virtual void importResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID);

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void search(const std::string& containerID, const std::string& searchCriteria, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID);

	virtual void stopTransferResource(Poco::UInt32 transferID);

	virtual void updateObject(const std::string& objectID, const std::string& currentTagValue, const std::string& newTagValue);

private:
	static const std::string DEFAULT_NS;
	Poco::RemotingNG::EventListener::Ptr _pEventListener;
	Poco::RemotingNG::EventSubscriber::Ptr _pEventSubscriber;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ContentDirectory1Proxy::remoting__typeId() const
{
	return IContentDirectory1::remoting__typeId();
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ContentDirectory1Proxy_INCLUDED

