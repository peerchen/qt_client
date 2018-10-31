//
// ContentDirectory1.h
//
// Library: MediaServer1
// Package: MediaServer1
// Module:  ContentDirectory1
//
// This file has been generated on 2012-10-29 11:42:20 UTC.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2011-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
// 
//


#ifndef MediaServer1_ContentDirectory1_INCLUDED
#define MediaServer1_ContentDirectory1_INCLUDED


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "UPnPS/MediaServer1/MediaServer1.h"


namespace UPnPS {
namespace MediaServer1 {


//@ namespace="urn:schemas-upnp-org:service:ContentDirectory:1"
//@ remote
class MediaServer1_API ContentDirectory1
{
public:
	typedef Poco::SharedPtr<ContentDirectory1> Ptr;

	ContentDirectory1();
		/// Creates a ContentDirectory1.

	virtual ~ContentDirectory1();
		/// Destroys the ContentDirectory1.

	//@ $browseFlag={name="BrowseFlag"}
	//@ $filter={name="Filter"}
	//@ $numberReturned={name="NumberReturned", direction=out}
	//@ $objectID={name="ObjectID"}
	//@ $requestedCount={name="RequestedCount"}
	//@ $result={name="Result", direction=out}
	//@ $sortCriteria={name="SortCriteria"}
	//@ $startingIndex={name="StartingIndex"}
	//@ $totalMatches={name="TotalMatches", direction=out}
	//@ $updateID={name="UpdateID", direction=out}
	//@ name=Browse
	//@ replyName=BrowseResponse
	virtual void browse(const std::string& objectID, const std::string& browseFlag, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID) = 0;

	//@ $containerID={name="ContainerID"}
	//@ $elements={name="Elements"}
	//@ $objectID={name="ObjectID", direction=out}
	//@ $result={name="Result", direction=out}
	//@ name=CreateObject
	//@ optional=true
	//@ replyName=CreateObjectResponse
	virtual void createObject(const std::string& containerID, const std::string& elements, std::string& objectID, std::string& result) = 0;

	//@ $containerID={name="ContainerID"}
	//@ $newID={name="NewID", direction=out}
	//@ $objectID={name="ObjectID"}
	//@ name=CreateReference
	//@ optional=true
	//@ replyName=CreateReferenceResponse
	virtual void createReference(const std::string& containerID, const std::string& objectID, std::string& newID) = 0;

	//@ $resourceURI={name="ResourceURI"}
	//@ name=DeleteResource
	//@ optional=true
	//@ replyName=DeleteResourceResponse
	virtual void deleteResource(const Poco::URI& resourceURI) = 0;

	//@ $objectID={name="ObjectID"}
	//@ name=DestroyObject
	//@ optional=true
	//@ replyName=DestroyObjectResponse
	virtual void destroyObject(const std::string& objectID) = 0;

	//@ $destinationURI={name="DestinationURI"}
	//@ $sourceURI={name="SourceURI"}
	//@ $transferID={name="TransferID", direction=out}
	//@ name=ExportResource
	//@ optional=true
	//@ replyName=ExportResourceResponse
	virtual void exportResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID) = 0;

	//@ $searchCaps={name="SearchCaps", direction=out}
	//@ name=GetSearchCapabilities
	//@ replyName=GetSearchCapabilitiesResponse
	virtual void getSearchCapabilities(std::string& searchCaps) = 0;

	//@ $sortCaps={name="SortCaps", direction=out}
	//@ name=GetSortCapabilities
	//@ replyName=GetSortCapabilitiesResponse
	virtual void getSortCapabilities(std::string& sortCaps) = 0;

	//@ $id={name="Id", direction=out}
	//@ name=GetSystemUpdateID
	//@ replyName=GetSystemUpdateIDResponse
	virtual void getSystemUpdateID(Poco::UInt32& id) = 0;

	//@ $transferID={name="TransferID"}
	//@ $transferLength={name="TransferLength", direction=out}
	//@ $transferStatus={name="TransferStatus", direction=out}
	//@ $transferTotal={name="TransferTotal", direction=out}
	//@ name=GetTransferProgress
	//@ optional=true
	//@ replyName=GetTransferProgressResponse
	virtual void getTransferProgress(Poco::UInt32 transferID, std::string& transferStatus, std::string& transferLength, std::string& transferTotal) = 0;

	//@ $destinationURI={name="DestinationURI"}
	//@ $sourceURI={name="SourceURI"}
	//@ $transferID={name="TransferID", direction=out}
	//@ name=ImportResource
	//@ optional=true
	//@ replyName=ImportResourceResponse
	virtual void importResource(const Poco::URI& sourceURI, const Poco::URI& destinationURI, Poco::UInt32& transferID) = 0;

	//@ $containerID={name="ContainerID"}
	//@ $filter={name="Filter"}
	//@ $numberReturned={name="NumberReturned", direction=out}
	//@ $requestedCount={name="RequestedCount"}
	//@ $result={name="Result", direction=out}
	//@ $searchCriteria={name="SearchCriteria"}
	//@ $sortCriteria={name="SortCriteria"}
	//@ $startingIndex={name="StartingIndex"}
	//@ $totalMatches={name="TotalMatches", direction=out}
	//@ $updateID={name="UpdateID", direction=out}
	//@ name=Search
	//@ optional=true
	//@ replyName=SearchResponse
	virtual void search(const std::string& containerID, const std::string& searchCriteria, const std::string& filter, Poco::UInt32 startingIndex, Poco::UInt32 requestedCount, const std::string& sortCriteria, std::string& result, Poco::UInt32& numberReturned, Poco::UInt32& totalMatches, Poco::UInt32& updateID) = 0;

	//@ $transferID={name="TransferID"}
	//@ name=StopTransferResource
	//@ optional=true
	//@ replyName=StopTransferResourceResponse
	virtual void stopTransferResource(Poco::UInt32 transferID) = 0;

	//@ $currentTagValue={name="CurrentTagValue"}
	//@ $newTagValue={name="NewTagValue"}
	//@ $objectID={name="ObjectID"}
	//@ name=UpdateObject
	//@ optional=true
	//@ replyName=UpdateObjectResponse
	virtual void updateObject(const std::string& objectID, const std::string& currentTagValue, const std::string& newTagValue) = 0;

	//@ name=ContainerUpdateIDs
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const std::string> containerUpdateIDsChanged;
	//@ name=SystemUpdateID
	//@ oneway=true
	Poco::BasicEvent<const Poco::UInt32> systemUpdateIDChanged;
	//@ name=TransferIDs
	//@ oneway=true
	//@ optional=true
	Poco::BasicEvent<const std::string> transferIDsChanged;
};


} // namespace MediaServer1
} // namespace UPnPS


#endif // MediaServer1_ContentDirectory1_INCLUDED

