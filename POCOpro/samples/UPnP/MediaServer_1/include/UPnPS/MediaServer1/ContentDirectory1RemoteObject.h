//
// ContentDirectory1RemoteObject.h
//
// Library: MediaServer1
// Package: Generated
// Module:  ContentDirectory1RemoteObject
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


#ifndef MediaServer1_ContentDirectory1RemoteObject_INCLUDED
#define MediaServer1_ContentDirectory1RemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"
#include "UPnPS/MediaServer1/IContentDirectory1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API ContentDirectory1RemoteObject: public UPnPS::MediaServer1::IContentDirectory1, public Poco::RemotingNG::RemoteObject
{
public:
	typedef Poco::AutoPtr<ContentDirectory1RemoteObject> Ptr;

	ContentDirectory1RemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<UPnPS::MediaServer1::ContentDirectory1> pServiceObject);
		/// Creates a ContentDirectory1RemoteObject.

	virtual ~ContentDirectory1RemoteObject();
		/// Destroys the ContentDirectory1RemoteObject.

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

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void search(const std::string& containerID, const std::string& searchCriteria, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID);

	virtual void stopTransferResource(Poco::UInt32 transferID);

	virtual void updateObject(const std::string& objectID, const std::string& currentTagValue, const std::string& newTagValue);

protected:
	void event__containerUpdateIDsChanged(const std::string& data);

	void event__systemUpdateIDChanged(const Poco::UInt32& data);

	void event__transferIDsChanged(const std::string& data);

private:
	Poco::SharedPtr<UPnPS::MediaServer1::ContentDirectory1> _pServiceObject;
};


inline void ContentDirectory1RemoteObject::browse(const std::string& objectID, const std::string& browseFlag, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID)
{
	_pServiceObject->browse(objectID, browseFlag, filter, startingIndex, requestedCount, sortCriteria, result, numberReturned, totalMatches, updateID);
}


inline void ContentDirectory1RemoteObject::createObject(const std::string& containerID, const std::string& elements, std::string& objectID, std::string& result)
{
	_pServiceObject->createObject(containerID, elements, objectID, result);
}


inline void ContentDirectory1RemoteObject::createReference(const std::string& containerID, const std::string& objectID, std::string& newID)
{
	_pServiceObject->createReference(containerID, objectID, newID);
}


inline void ContentDirectory1RemoteObject::deleteResource(const Poco::URI& resourceURI)
{
	_pServiceObject->deleteResource(resourceURI);
}


inline void ContentDirectory1RemoteObject::destroyObject(const std::string& objectID)
{
	_pServiceObject->destroyObject(objectID);
}


inline void ContentDirectory1RemoteObject::exportResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID)
{
	_pServiceObject->exportResource(sourceURI, destinationURI, transferID);
}


inline void ContentDirectory1RemoteObject::getSearchCapabilities(std::string& searchCaps)
{
	_pServiceObject->getSearchCapabilities(searchCaps);
}


inline void ContentDirectory1RemoteObject::getSortCapabilities(std::string& sortCaps)
{
	_pServiceObject->getSortCapabilities(sortCaps);
}


inline void ContentDirectory1RemoteObject::getSystemUpdateID(Poco::UInt32& id)
{
	_pServiceObject->getSystemUpdateID(id);
}


inline void ContentDirectory1RemoteObject::getTransferProgress(Poco::UInt32 transferID, std::string& transferStatus, std::string& transferLength, std::string& transferTotal)
{
	_pServiceObject->getTransferProgress(transferID, transferStatus, transferLength, transferTotal);
}


inline void ContentDirectory1RemoteObject::importResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID)
{
	_pServiceObject->importResource(sourceURI, destinationURI, transferID);
}


inline const Poco::RemotingNG::Identifiable::TypeId& ContentDirectory1RemoteObject::remoting__typeId() const
{
	return IContentDirectory1::remoting__typeId();
}


inline void ContentDirectory1RemoteObject::search(const std::string& containerID, const std::string& searchCriteria, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID)
{
	_pServiceObject->search(containerID, searchCriteria, filter, startingIndex, requestedCount, sortCriteria, result, numberReturned, totalMatches, updateID);
}


inline void ContentDirectory1RemoteObject::stopTransferResource(Poco::UInt32 transferID)
{
	_pServiceObject->stopTransferResource(transferID);
}


inline void ContentDirectory1RemoteObject::updateObject(const std::string& objectID, const std::string& currentTagValue, const std::string& newTagValue)
{
	_pServiceObject->updateObject(objectID, currentTagValue, newTagValue);
}


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ContentDirectory1RemoteObject_INCLUDED

