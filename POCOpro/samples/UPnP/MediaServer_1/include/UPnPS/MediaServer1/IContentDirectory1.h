//
// IContentDirectory1.h
//
// Library: MediaServer1
// Package: Generated
// Module:  IContentDirectory1
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


#ifndef MediaServer1_IContentDirectory1_INCLUDED
#define MediaServer1_IContentDirectory1_INCLUDED


#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"
#include "UPnPS/MediaServer1/ContentDirectory1.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


class MediaServer1_API IContentDirectory1: public virtual Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<IContentDirectory1> Ptr;

	IContentDirectory1();
		/// Creates a IContentDirectory1.

	virtual ~IContentDirectory1();
		/// Destroys the IContentDirectory1.

	virtual void browse(const std::string& objectID, const std::string& browseFlag, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID) = 0;

	virtual void createObject(const std::string& containerID, const std::string& elements, std::string& objectID, std::string& result) = 0;

	virtual void createReference(const std::string& containerID, const std::string& objectID, std::string& newID) = 0;

	virtual void deleteResource(const Poco::URI& resourceURI) = 0;

	virtual void destroyObject(const std::string& objectID) = 0;

	virtual void exportResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID) = 0;

	virtual void getSearchCapabilities(std::string& searchCaps) = 0;

	virtual void getSortCapabilities(std::string& sortCaps) = 0;

	virtual void getSystemUpdateID(Poco::UInt32& id) = 0;

	virtual void getTransferProgress(Poco::UInt32 transferID, std::string& transferStatus, std::string& transferLength, std::string& transferTotal) = 0;

	virtual void importResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID) = 0;

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void search(const std::string& containerID, const std::string& searchCriteria, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID) = 0;

	virtual void stopTransferResource(Poco::UInt32 transferID) = 0;

	virtual void updateObject(const std::string& objectID, const std::string& currentTagValue, const std::string& newTagValue) = 0;

	Poco::BasicEvent < const std::string > containerUpdateIDsChanged;
	Poco::BasicEvent < const Poco::UInt32 > systemUpdateIDChanged;
	Poco::BasicEvent < const std::string > transferIDsChanged;
};


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_IContentDirectory1_INCLUDED

